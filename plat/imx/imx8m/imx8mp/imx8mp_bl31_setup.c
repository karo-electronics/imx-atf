/*
 * Copyright 2019-2020 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <assert.h>
#include <stdbool.h>

#include <platform_def.h>

#include <arch_helpers.h>
#include <common/bl_common.h>
#include <common/debug.h>
#include <context.h>
#include <drivers/arm/tzc380.h>
#include <drivers/console.h>
#include <drivers/generic_delay_timer.h>
#include <lib/el3_runtime/context_mgmt.h>
#include <lib/mmio.h>
#include <lib/xlat_tables/xlat_tables_v2.h>
#include <plat_private.h>
#include <plat/common/platform.h>

#include <dram.h>
#include <gpc.h>
#include <imx_aipstz.h>
#include <imx_uart.h>
#include <imx_rdc.h>
#include <imx8m_caam.h>
#include <imx8m_csu.h>
#include <plat_imx8.h>

#define TRUSTY_PARAMS_LEN_BYTES      (4096*2)

static const mmap_region_t imx_mmap[] = {
	MAP_REGION_FLAT(IMX_GIC_BASE, IMX_GIC_SIZE, MT_DEVICE | MT_RW),
	MAP_REGION_FLAT(IMX_AIPS_BASE, IMX_AIPS_SIZE, MT_DEVICE | MT_RW), /* AIPS map */
	MAP_REGION_FLAT(OCRAM_S_BASE, OCRAM_S_SIZE, MT_DEVICE | MT_RW), /* OCRAM_S */
	MAP_REGION_FLAT(IMX_DDRPHY_BASE, IMX_DDR_IPS_SIZE, MT_DEVICE | MT_RW), /* DDRMIX */
	MAP_REGION_FLAT(IMX_CAAM_RAM_BASE, IMX_CAAM_RAM_SIZE, MT_MEMORY | MT_RW), /* CAMM RAM */
	MAP_REGION_FLAT(IMX_NS_OCRAM_BASE, IMX_NS_OCRAM_SIZE, MT_MEMORY | MT_RW), /* NS OCRAM */
	MAP_REGION_FLAT(IMX_ROM_BASE, IMX_ROM_SIZE, MT_MEMORY | MT_RO), /* ROM code */
	MAP_REGION_FLAT(IMX_DRAM_BASE, IMX_DRAM_SIZE, MT_MEMORY | MT_RW | MT_NS), /* DRAM */
	MAP_REGION_FLAT(IMX_NOC_BASE, IMX_NOC_SIZE, MT_DEVICE | MT_RW), /* NOC QoS */
	{0},
};

/* AIPSTZ5 resides in Audiomix, it will be init along with audiomix power domain */
static const struct aipstz_cfg aipstz[] = {
	{IMX_AIPSTZ1, 0x77777777, 0x77777777, .opacr = {0x0, 0x0, 0x0, 0x0, 0x0}, },
	{IMX_AIPSTZ2, 0x77777777, 0x77777777, .opacr = {0x0, 0x0, 0x0, 0x0, 0x0}, },
	{IMX_AIPSTZ3, 0x77777777, 0x77777777, .opacr = {0x0, 0x0, 0x0, 0x0, 0x0}, },
	{IMX_AIPSTZ4, 0x77777777, 0x77777777, .opacr = {0x0, 0x0, 0x0, 0x0, 0x0}, },
	{0},
};

static const struct imx_rdc_cfg rdc[] = {
	/* Master domain assignment */
	RDC_MDAn(RDC_MDA_M7, DID1),

	/* peripherals domain permission */
	RDC_PDAPn(RDC_PDAP_UART2, D0R | D0W),

	/* memory region */

	/* Sentinel */
	{0},
};

static const struct imx_csu_cfg csu_cfg[] = {
	/* peripherals csl setting */
	CSU_CSLx(CSU_CSL_OCRAM, CSU_SEC_LEVEL_2, UNLOCKED),
	CSU_CSLx(CSU_CSL_OCRAM_S, CSU_SEC_LEVEL_2, UNLOCKED),

	/* master HP0~1 */

	/* SA setting */

	/* HP control setting */

	/* Sentinel */
	{0}
};

static entry_point_info_t bl32_image_ep_info;
static entry_point_info_t bl33_image_ep_info;

#if defined (CSU_RDC_TEST)
static void csu_rdc_test(void);
#endif

/* get SPSR for BL33 entry */
static uint32_t get_spsr_for_bl33_entry(void)
{
	unsigned long el_status;
	unsigned long mode;
	uint32_t spsr;

	/* figure out what mode we enter the non-secure world */
	el_status = read_id_aa64pfr0_el1() >> ID_AA64PFR0_EL2_SHIFT;
	el_status &= ID_AA64PFR0_ELX_MASK;

	mode = (el_status) ? MODE_EL2 : MODE_EL1;

	spsr = SPSR_64(mode, MODE_SP_ELX, DISABLE_ALL_EXCEPTIONS);
	return spsr;
}

static void bl31_tzc380_setup(void)
{
	unsigned int val;

	val = mmio_read_32(IMX_IOMUX_GPR_BASE + 0x28);
	if ((val & GPR_TZASC_EN) != GPR_TZASC_EN)
		return;

	tzc380_init(IMX_TZASC_BASE);

	/*
	 * Need to substact offset 0x40000000 from CPU address when
	 * programming tzasc region for i.mx8mm.
	 */

	/* Enable 1G-5G S/NS RW */
	tzc380_configure_region(0, 0x00000000, TZC_ATTR_REGION_SIZE(TZC_REGION_SIZE_4G) |
				TZC_ATTR_REGION_EN_MASK | TZC_ATTR_SP_ALL);
}

void bl31_early_platform_setup2(u_register_t arg0, u_register_t arg1,
		u_register_t arg2, u_register_t arg3)
{
	static console_uart_t console;
	int i;

	/* Enable CSU NS access permission */
	for (i = 0; i < 64; i++) {
		mmio_write_32(IMX_CSU_BASE + i * 4, 0x00ff00ff);
	}

	imx_aipstz_init(aipstz);

	imx_rdc_init(rdc);

	imx_csu_init(csu_cfg);

	/* config the ocram memory range for secure access */
	mmio_write_32(IMX_IOMUX_GPR_BASE + 0x2c, 0xc1);

	imx8m_caam_init();

	imx_params_early_setup(arg1);
	console_imx_uart_register(imx_get_uart_base(), imx_get_uart_clock(),
				  imx_get_uart_baudrate(), &console);

	/* This console is only used for boot stage */
#if DEBUG
	console_set_scope(&console.console,
			  CONSOLE_FLAG_BOOT | CONSOLE_FLAG_RUNTIME);
#else
	console_set_scope(&console.console, CONSOLE_FLAG_BOOT);
#endif
	/*
	 * tell BL3-1 where the non-secure software image is located
	 * and the entry state information.
	 */
	bl33_image_ep_info.pc = PLAT_NS_IMAGE_OFFSET;
	bl33_image_ep_info.spsr = get_spsr_for_bl33_entry();
	SET_SECURITY_STATE(bl33_image_ep_info.h.attr, NON_SECURE);

#if defined(SPD_opteed) || defined(SPD_trusty)
	/* Populate entry point information for BL32 */
	SET_PARAM_HEAD(&bl32_image_ep_info, PARAM_EP, VERSION_1, 0);
	SET_SECURITY_STATE(bl32_image_ep_info.h.attr, SECURE);
	bl32_image_ep_info.pc = BL32_BASE;
	bl32_image_ep_info.spsr = 0;

	/* Pass TEE base and size to bl33 */
	bl33_image_ep_info.args.arg1 = BL32_BASE;
	bl33_image_ep_info.args.arg2 = BL32_SIZE;

#ifdef SPD_trusty
	bl32_image_ep_info.args.arg0 = BL32_SIZE;
	bl32_image_ep_info.args.arg1 = BL32_BASE;
#else
	/* Make sure memory is clean */
	mmio_write_32(BL32_FDT_OVERLAY_ADDR, 0);
	bl33_image_ep_info.args.arg3 = BL32_FDT_OVERLAY_ADDR;
	bl32_image_ep_info.args.arg3 = BL32_FDT_OVERLAY_ADDR;
#endif
#endif

	bl31_tzc380_setup();

#if defined (CSU_RDC_TEST)
	csu_rdc_test();
#endif
}

void bl31_plat_arch_setup(void)
{
	mmap_add_region(BL31_BASE, BL31_BASE, (BL31_LIMIT - BL31_BASE),
		MT_MEMORY | MT_RW | MT_SECURE);
	mmap_add_region(BL_CODE_BASE, BL_CODE_BASE, (BL_CODE_END - BL_CODE_BASE),
		MT_MEMORY | MT_RO | MT_SECURE);
#if USE_COHERENT_MEM
	mmap_add_region(BL_COHERENT_RAM_BASE, BL_COHERENT_RAM_BASE,
		(BL_COHERENT_RAM_END - BL_COHERENT_RAM_BASE),
		MT_DEVICE | MT_RW | MT_SECURE);
#endif
	// Map TEE memory
	mmap_add_region(BL32_BASE, BL32_BASE, BL32_SIZE, MT_MEMORY | MT_RW);

	mmap_add(imx_mmap);

	init_xlat_tables();

	enable_mmu_el3(0);
}

void bl31_platform_setup(void)
{
	generic_delay_timer_init();

	/* select the CKIL source to 32K OSC */
	mmio_write_32(IMX_ANAMIX_BASE + ANAMIX_MISC_CTL, 0x1);

	/* Init the dram info */
	dram_info_init(SAVED_DRAM_TIMING_BASE);

	plat_gic_driver_init();
	plat_gic_init();

	imx_gpc_init();

	/* Enable and reset M7 */
	mmio_setbits_32(IMX_SRC_BASE + 0xc,  SRC_SCR_M4_ENABLE_MASK);
	mmio_clrbits_32(IMX_SRC_BASE + 0xc, SRC_SCR_M4C_NON_SCLR_RST_MASK);
}

entry_point_info_t *bl31_plat_get_next_image_ep_info(unsigned int type)
{
	if (type == NON_SECURE)
		return &bl33_image_ep_info;
	if (type == SECURE)
		return &bl32_image_ep_info;

	return NULL;
}

unsigned int plat_get_syscnt_freq2(void)
{
	return COUNTER_FREQUENCY;
}

#ifdef SPD_trusty
void plat_trusty_set_boot_args(aapcs64_params_t *args) {
	args->arg0 = BL32_SIZE;
	args->arg1 = BL32_BASE;
	args->arg2 = TRUSTY_PARAMS_LEN_BYTES;
}
#endif

#if defined (CSU_RDC_TEST)
static const struct imx_rdc_cfg rdc_for_test[] = {
	/* Master domain assignment */

	/* peripherals domain permission */

	RDC_PDAPn(RDC_PDAP_CSU, D2R | D2W),

	/* memory region */

	/* Sentinel */
	{0},
};

static const struct imx_csu_cfg csu_cfg_for_test[] = {
	/* peripherals csl setting */
	CSU_CSLx(CSU_CSL_RDC, CSU_SEC_LEVEL_4, LOCKED),
	CSU_CSLx(CSU_CSL_CSU, CSU_SEC_LEVEL_4, LOCKED),
	/* master HP0~1 */

	/* SA setting */

	/* HP control setting */

	/* Sentinel */
	{0}
};

static void csu_rdc_test(void)
{
	imx_csu_init(csu_cfg_for_test);
	imx_rdc_init(rdc_for_test);
}
#endif
