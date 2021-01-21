/*
 * Copyright (c) 2016-2019, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <assert.h>
#include <errno.h>
#include <string.h>

#include <lib/bl_aux_params/bl_aux_params.h>
#include <common/bl_common.h>
#include <common/debug.h>
#include <drivers/console.h>
#include <drivers/gpio.h>
#include <libfdt.h>
#include <lib/mmio.h>
#include <plat/common/platform.h>

#include <plat_params.h>
#include <plat_private.h>

static uint32_t imx_uart_base = IMX_BOOT_UART_BASE;
static uint32_t imx_uart_baudrate = IMX_CONSOLE_BAUDRATE;
static uint32_t imx_uart_clock = IMX_BOOT_UART_CLK_IN_HZ;

#if LOG_LEVEL >= LOG_LEVEL_VERBOSE
static inline void print_tabs(int num)
{
	while (num--)
		printf("\t");
}

static const char *str_props[] = {
	"model",
	"compatible",
	"status",
	"clock-output-names",
	"stdout-path",
	NULL,
};

static const char *hex_props[] = {
	"reg",
	"phandle",
	NULL,
};

static const char *dec_props[] = {
	"clock-frequency",
	NULL,
};

enum {
      PROP_TYPE_ANY,
      PROP_TYPE_STR,
      PROP_TYPE_INT,
      PROP_TYPE_HEX,
      PROP_TYPE_PTR,
} prop_type;

static int find_prop(const char *name, const char **list)
{
	while (*list) {
		if (strcmp(name, *list) == 0)
			return 1;
		list++;
	}
	return 0;
}

static void print_property(const char *name, const void *prop, int len,
			   int type)
{
	int i;

	printf("%s = ", name);
	if (type == PROP_TYPE_ANY) {
		if (find_prop(name, hex_props))
			type = PROP_TYPE_HEX;
		else if (find_prop(name, str_props))
			type = PROP_TYPE_STR;
		else if (find_prop(name, dec_props) || name[0] == '#')
			type = PROP_TYPE_INT;
		else
			type = PROP_TYPE_PTR;
	}

	switch (type) {
	case PROP_TYPE_HEX:
		if (len % 4 == 0) {
			const uint32_t *p = prop;

			printf("<");
			for (i = 0; i < len / 4; i++) {
				int val = fdt32_to_cpu(p[i]);
				if (i)
					printf(" ");
				printf("0x%08x", val);
			}
			printf(">");
		} else {
			printf("<%p>", prop);
		}
		break;
	case PROP_TYPE_STR:
		printf("\"%s\"", (const char *)prop);
		break;
	case PROP_TYPE_INT:
		printf("<%d>", fdt32_to_cpu(*(uint32_t *)prop));
		break;
	default:
		printf("<%p>", prop);
	}
	printf(";\n");
}

static int dump_props(const void *fdt, int node, int lvl, int type)
{
	int offs;
	int num = 0;

	fdt_for_each_property_offset(offs, fdt, node) {
		const void *prop;
		const char *name;
		int len;

		prop = fdt_getprop_by_offset(fdt, offs, &name, &len);
		print_tabs(lvl);
		if (len)
			print_property(name, prop, len, type);
		else
			printf("%s;\n", name);
		num++;
	}
	return num;
}

static void dump_subnodes(const void *fdt, int root, int lvl);
static void dump_subnodes(const void *fdt, int root, int lvl)
{
	int node;
	int nl;

	if (strcmp(fdt_get_name(fdt, root, NULL), "aliases") == 0)
		nl = dump_props(fdt, root, lvl, PROP_TYPE_STR);
	else
		nl = dump_props(fdt, root, lvl, PROP_TYPE_ANY);

	fdt_for_each_subnode(node, fdt, root) {
		if (!nl)
			nl = 1;
		else
			printf("\n");
		print_tabs(lvl);
		printf("%s {\n", fdt_get_name(fdt, node, NULL));
		lvl++;
		dump_subnodes(fdt, node, lvl);
		lvl--;
		print_tabs(lvl);
		printf("};\n");
	}
}
#endif

void dump_fdt(const void *fdt)
{
#if LOG_LEVEL >= LOG_LEVEL_VERBOSE
	int root = fdt_path_offset(fdt, "/");

	printf("/ {\n");
	dump_subnodes(fdt, root, 1);
	printf("};\n");
#endif
}

static void plat_imx_dt_process_fdt_uart(void *fdt)
{
	const char *path_name = "/chosen";
	const char *prop_name = "stdout-path";
	int node_offset;
	int stdout_path_len;
	const char *stdout_path;
	const char *separator;
	const char *baud_start;
	uint32_t uart_base;
	uint32_t baud;

	node_offset = fdt_path_offset(fdt, path_name);
	if (node_offset < 0) {
		ERROR("No 'chosen' node found in DTB: %d\n",
		      node_offset);
		return;
	}

	dump_fdt(fdt);
	stdout_path = fdt_getprop(fdt, node_offset, prop_name,
				  &stdout_path_len);
	if (stdout_path == NULL) {
		ERROR("'stdout-path' not found in DTB\n");
		return;
	}

	int len;
	int offs;
	const void *prop;
	separator = strchr(stdout_path, ':');
	if (strchr(stdout_path, '/') != stdout_path) {
		if (separator) {
			const char *alias;

			len = separator - stdout_path;
			offs = fdt_path_offset(fdt, "/aliases");
			if (offs < 0)
				ERROR("No '/aliases' node in DT: %d\n", offs);
			alias = fdt_get_alias_namelen(fdt, stdout_path, len);
			if (alias)
				INFO("alias '%s'='%s'\n",
				     stdout_path, alias);
			else
				ERROR("Could not resolve alias '%s'(%u)\n",
				      stdout_path, len);
			stdout_path = alias;
		} else {
			len = strlen(stdout_path);
		}
	} else {
		len = strlen(stdout_path);
	}

	offs = fdt_path_offset(fdt, stdout_path);
	if (offs <= 0) {
		ERROR("Failed to find '%s' node\n", stdout_path);
		return;
	}
	prop = fdt_getprop(fdt, offs, "reg", &len);
	if (prop) {
		uart_base = fdt32_to_cpu(*((const uint32_t *)prop));
		INFO("uart_base set to %08x from '%s' node\n",
		     uart_base, stdout_path);
	} else {
		ERROR("'reg' property not found in '%s'\n",
		      stdout_path);
		return;
	}

	INFO("%s@%d: setting uart_base=%08x from FDT\n", __func__, __LINE__,
	     uart_base);
	imx_uart_base = uart_base;

	if (!separator)
		return;

	baud = 0;
	baud_start = separator + 1;
	while (*baud_start != '\0') {
		/*
		 * uart binding is <baud>{<parity>{<bits>{...}}}
		 * So the baudrate either is the whole string, or
		 * we end in the parity characters.
		 */
		if (*baud_start == 'n' || *baud_start == 'o' ||
		    *baud_start == 'e')
			break;

		baud = baud * 10 + (*baud_start - '0');
		baud_start++;
	}

	INFO("%s@%d: setting uart_baudrate=%u from FDT\n", __func__, __LINE__,
	     baud);
	imx_uart_baudrate = baud;
}

static int dt_process_fdt(u_register_t param_from_bl2)
{
	plat_imx_dt_process_fdt_uart((void *)param_from_bl2);
	return 0;
}

uint32_t imx_get_uart_base(void)
{
	INFO("%s@%d: UART_BASE=%08x\n", __func__, __LINE__, imx_uart_base);
	return imx_uart_base;
}

uint32_t imx_get_uart_baudrate(void)
{
	return imx_uart_baudrate;
}

uint32_t imx_get_uart_clock(void)
{
	return imx_uart_clock;
}

void imx_params_early_setup(u_register_t plat_param_from_bl2)
{
	/*
	 * Test if this is a FDT passed as a platform-specific parameter
	 * block.
	 */
	dt_process_fdt(plat_param_from_bl2);
}
