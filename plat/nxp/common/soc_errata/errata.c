/*
 * Copyright 2018-2021 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include <platform_def.h>
#include <mmio.h>
#include <cci.h>
#include <plat_common.h>
#include <ls_interconnect.h>
#include <common/debug.h>

#include "dcfg.h"

#if ERRATA_SOC_A050426
static void erratum_a050426(void)
{
	uint32_t i, val3, val4;

	/* Enable BIST to access internal memory locations */
	val3 = mmio_read_32(0x700117E60);
	mmio_write_32(0x700117E60, (val3 | 0x80000001));
	val4 = mmio_read_32(0x700117E90);
	mmio_write_32(0x700117E90, (val4 & 0xFFDFFFFF));

	/* EDMA internal Memory*/
	for (i = 0; i < 5; i++)
		mmio_write_32(0x70a208000 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70a208800 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70a209000 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70a209800 + (i * 4), 0x55555555);

	/* QDMA internal Memory*/
	for (i = 0; i < 5; i++)
		mmio_write_32(0x70b008000 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70b00c000 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70b010000 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70b014000 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70b018000 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70b018400 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70b01a000 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70b01a400 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70b01c000 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70b01d000 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70b01e000 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70b01e800 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70b01f000 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70b01f800 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70b020000 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70b020400 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70b020800 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70b020c00 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70b022000 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70b022400 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70b024000 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70b024800 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70b025000 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70b025800 + (i * 4), 0x55555555);

	for (i = 0; i < 4; i++)
		mmio_write_32(0x70b026000 + (i * 4), 0x55555555);

	for (i = 0; i < 4; i++)
		mmio_write_32(0x70b026200 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70b028000 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70b028800 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70b029000 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70b029800 + (i * 4), 0x55555555);

	/* PEX1 internal Memory*/
	for (i = 0; i < 3; i++)
		mmio_write_32(0x70a508000 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70a520000 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70a528000 + (i * 4), 0x55555555);

	/* PEX2 internal Memory*/
	for (i = 0; i < 3; i++)
		mmio_write_32(0x70a608000 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70a620000 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70a628000 + (i * 4), 0x55555555);

	/* PEX4 internal Memory*/
	for (i = 0; i < 3; i++)
		mmio_write_32(0x70a808000 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70a820000 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70a828000 + (i * 4), 0x55555555);

	/* PEX6 internal Memory*/
	for (i = 0; i < 3; i++)
		mmio_write_32(0x70ab08000 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70ab20000 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70ab28000 + (i * 4), 0x55555555);

	/* PEX3 internal Memory*/
	for (i = 0; i < 5; i++)
		mmio_write_32(0x70a708000 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70a728000 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70a730000 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70a738000 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70a748000 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70a758000 + (i * 4), 0x55555555);

	/* PEX5 internal Memory*/
	for (i = 0; i < 5; i++)
		mmio_write_32(0x70aa08000 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70aa28000 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70aa30000 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70aa38000 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70aa48000 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70aa58000 + (i * 4), 0x55555555);

	/* lnx1_e1000#0 internal Memory*/
	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c00a000 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c00a200 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c00a400 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c00a600 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c00a800 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c00aa00 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c00ac00 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c00ae00 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c00b000 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c00b200 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c00b400 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c00b600 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c00b800 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c00ba00 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c00bc00 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c00be00 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70c00c000 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70c00c400 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70c00c800 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70c00cc00 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70c00d000 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70c00d400 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70c00d800 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70c00dc00 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c00e000 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c00f000 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c012000 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c012200 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c012400 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c012600 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c012800 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c012a00 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c012c00 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c012e00 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c013000 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c013200 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c013400 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c013600 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c013800 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c013a00 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c013c00 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c013e00 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70c014000 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70c014400 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70c014800 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70c014c00 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70c015000 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70c015400 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70c015800 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70c015c00 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c016000 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c017000 + (i * 4), 0x55555555);

	/* lnx1_xfi internal Memory*/
	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c108000 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c108200 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c10a000 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c10a400 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70c10c000 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70c10c400 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c10e000 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c10e200 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c110000 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c110400 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70c112000 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70c112400 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c114000 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c114200 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c116000 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c116400 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70c118000 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70c118400 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c11a000 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c11a200 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c11c000 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c11c400 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70c11e000 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70c11e400 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c120000 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c120200 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c122000 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c122400 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70c124000 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70c124400 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c126000 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c126200 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c128000 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c128400 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70c12a000 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70c12a400 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c12c000 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c12c200 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c12e000 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c12e400 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70c130000 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70c130400 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c132000 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c132200 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c134000 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c134400 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70c136000 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70c136400 + (i * 4), 0x55555555);

	/* lnx2_xfi internal Memory*/
	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c308000 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c308200 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c30a000 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c30a400 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70c30c000 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70c30c400 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c30e000 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c30e200 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c310000 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70c310400 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70c312000 + (i * 4), 0x55555555);

	for (i = 0; i < 5; i++)
		mmio_write_32(0x70c312400 + (i * 4), 0x55555555);

	/* wriop internal Memory*/

	for (i = 0; i < 4; i++)
		mmio_write_32(0x706312000 + (i * 4), 0x55555555);

	for (i = 0; i < 4; i++)
		mmio_write_32(0x706312400 + (i * 4), 0x55555555);

	for (i = 0; i < 4; i++)
		mmio_write_32(0x706312800 + (i * 4), 0x55555555);

	for (i = 0; i < 4; i++)
		mmio_write_32(0x706314000 + (i * 4), 0x55555555);

	for (i = 0; i < 4; i++)
		mmio_write_32(0x706314400 + (i * 4), 0x55555555);

	for (i = 0; i < 4; i++)
		mmio_write_32(0x706314800 + (i * 4), 0x55555555);

	for (i = 0; i < 4; i++)
		mmio_write_32(0x706314c00 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x706316000 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x706320000 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x706320400 + (i * 4), 0x55555555);

	for (i = 0; i < 2; i++)
		mmio_write_32(0x70640a000 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x706518000 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x706519000 + (i * 4), 0x55555555);

	for (i = 0; i < 4; i++)
		mmio_write_32(0x706522000 + (i * 4), 0x55555555);

	for (i = 0; i < 4; i++)
		mmio_write_32(0x706522800 + (i * 4), 0x55555555);

	for (i = 0; i < 4; i++)
		mmio_write_32(0x706523000 + (i * 4), 0x55555555);

	for (i = 0; i < 4; i++)
		mmio_write_32(0x706523800 + (i * 4), 0x55555555);

	for (i = 0; i < 4; i++)
		mmio_write_32(0x706524000 + (i * 4), 0x55555555);

	for (i = 0; i < 4; i++)
		mmio_write_32(0x706524800 + (i * 4), 0x55555555);

	for (i = 0; i < 4; i++)
		mmio_write_32(0x706608000 + (i * 4), 0x55555555);

	for (i = 0; i < 4; i++)
		mmio_write_32(0x706608800 + (i * 4), 0x55555555);

	for (i = 0; i < 4; i++)
		mmio_write_32(0x706609000 + (i * 4), 0x55555555);

	for (i = 0; i < 4; i++)
		mmio_write_32(0x706609800 + (i * 4), 0x55555555);

	for (i = 0; i < 4; i++)
		mmio_write_32(0x70660a000 + (i * 4), 0x55555555);

	for (i = 0; i < 4; i++)
		mmio_write_32(0x70660a800 + (i * 4), 0x55555555);

	for (i = 0; i < 4; i++)
		mmio_write_32(0x70660b000 + (i * 4), 0x55555555);

	for (i = 0; i < 4; i++)
		mmio_write_32(0x70660b800 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70660c000 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70660c800 + (i * 4), 0x55555555);

	for (i = 0; i < 2; i++)
		mmio_write_32(0x706718000 + (i * 4), 0x55555555);

	for (i = 0; i < 2; i++)
		mmio_write_32(0x706718800 + (i * 4), 0x55555555);

	mmio_write_32(0x706b0a000 + (i * 4), 0x55555555);

	for (i = 0; i < 4; i++)
		mmio_write_32(0x706b0e000 + (i * 4), 0x55555555);

	for (i = 0; i < 4; i++)
		mmio_write_32(0x706b0e800 + (i * 4), 0x55555555);

	for (i = 0; i < 2; i++)
		mmio_write_32(0x706b10000 + (i * 4), 0x55555555);

	for (i = 0; i < 2; i++)
		mmio_write_32(0x706b10400 + (i * 4), 0x55555555);

	for (i = 0; i < 4; i++)
		mmio_write_32(0x706b14000 + (i * 4), 0x55555555);

	for (i = 0; i < 4; i++)
		mmio_write_32(0x706b14800 + (i * 4), 0x55555555);

	for (i = 0; i < 4; i++)
		mmio_write_32(0x706b15000 + (i * 4), 0x55555555);

	for (i = 0; i < 4; i++)
		mmio_write_32(0x706b15800 + (i * 4), 0x55555555);

	mmio_write_32(0x706e12000 + (i * 4), 0x55555555);

	for (i = 0; i < 4; i++)
		mmio_write_32(0x706e14000 + (i * 4), 0x55555555);

	for (i = 0; i < 4; i++)
		mmio_write_32(0x706e14800 + (i * 4), 0x55555555);

	for (i = 0; i < 2; i++)
		mmio_write_32(0x706e16000 + (i * 4), 0x55555555);

	for (i = 0; i < 2; i++)
		mmio_write_32(0x706e16400 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x706e1a000 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x706e1a800 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x706e1b000 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x706e1b800 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x706e1c000 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x706e1c800 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x706e1e000 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x706e1e800 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x706e1f000 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x706e1f800 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x706e20000 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x706e20800 + (i * 4), 0x55555555);

	for (i = 0; i < 4; i++)
		mmio_write_32(0x707108000 + (i * 4), 0x55555555);

	for (i = 0; i < 4; i++)
		mmio_write_32(0x707109000 + (i * 4), 0x55555555);

	for (i = 0; i < 4; i++)
		mmio_write_32(0x70710a000 + (i * 4), 0x55555555);

	for (i = 0; i < 2; i++)
		mmio_write_32(0x70711c000 + (i * 4), 0x55555555);

	for (i = 0; i < 2; i++)
		mmio_write_32(0x70711c800 + (i * 4), 0x55555555);

	for (i = 0; i < 2; i++)
		mmio_write_32(0x70711d000 + (i * 4), 0x55555555);

	for (i = 0; i < 2; i++)
		mmio_write_32(0x70711d800 + (i * 4), 0x55555555);

	for (i = 0; i < 2; i++)
		mmio_write_32(0x70711e000 + (i * 4), 0x55555555);

	for (i = 0; i < 4; i++)
		mmio_write_32(0x707120000 + (i * 4), 0x55555555);

	for (i = 0; i < 4; i++)
		mmio_write_32(0x707121000 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x707122000 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70725a000 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70725b000 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70725c000 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70725e000 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70725e400 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70725e800 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70725ec00 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70725f000 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70725f400 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x707340000 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x707346000 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x707484000 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70748a000 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70748b000 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70748c000 + (i * 4), 0x55555555);

	for (i = 0; i < 3; i++)
		mmio_write_32(0x70748d000 + (i * 4), 0x55555555);

	/* Disable BIST */

	mmio_write_32(0x700117E60, val3);
	mmio_write_32(0x700117E90, val4);
}
#endif


#if ERRATA_SOC_A008850
static void erratum_a008850_early(void)
{
	/* part 1 of 2 */
	uintptr_t cci_base = NXP_CCI_ADDR;
	uint32_t val = mmio_read_32(cci_base + CTRL_OVERRIDE_REG);

	/* enabling forced barrier termination on CCI400 */
	mmio_write_32(cci_base + CTRL_OVERRIDE_REG,
		      (val | CCI_TERMINATE_BARRIER_TX));

}
#endif

#if ERRATA_SOC_A008850
void erratum_a008850_post(void)
{
	/* part 2 of 2 */
	uintptr_t cci_base = NXP_CCI_ADDR;
	uint32_t val = mmio_read_32(cci_base + CTRL_OVERRIDE_REG);

	/* Clear the BARRIER_TX bit */
	val = val & ~(CCI_TERMINATE_BARRIER_TX);

	/*
	 * Disable barrier termination on CCI400, allowing
	 * barriers to propagate across CCI
	 */
	mmio_write_32(cci_base + CTRL_OVERRIDE_REG, val);

	INFO("SoC workaround for Errata A008850 Post-Phase was applied\n");
}
#endif

#if ERRATA_SOC_A009660
static void erratum_a009660(void)
{
	mmio_write_32(NXP_SCFG_ADDR + 0x20c, 0x63b20042);
}
#endif

#if ERRATA_SOC_A010539
static void erratum_a010539(void)
{
	if (get_boot_dev() == BOOT_DEVICE_QSPI) {
		unsigned int *porsr1 = (void *)(NXP_DCFG_ADDR +
				DCFG_PORSR1_OFFSET);
		uint32_t val;

		val = (gur_in32(porsr1) & ~PORSR1_RCW_MASK);
		mmio_write_32((uint32_t)(NXP_DCSR_DCFG_ADDR +
				DCFG_DCSR_PORCR1_OFFSET), htobe32(val));
		mmio_write_32((uint32_t)(NXP_SCFG_ADDR + 0x1a8),
				htobe32(0xffffffff));
	}

}
#endif

void soc_errata(void)
{
#if ERRATA_SOC_A050426
	INFO("SoC workaround for Errata A050426 was applied\n");
	erratum_a050426();
#endif
#if ERRATA_SOC_A008850
	INFO("SoC workaround for Errata A008850 Early-Phase was applied\n");
	erratum_a008850_early();
#endif
#if ERRATA_SOC_A009660
	INFO("SoC workaround for Errata A009660 was applied\n");
	erratum_a009660();
#endif
#if ERRATA_SOC_A010539
	INFO("SoC workaround for Errata A010539 was applied\n");
	erratum_a010539();
#endif
	/*
	 * The following DDR Erratas workaround are implemented in DDR driver,
	 * but print information here.
	 */
#if ERRATA_DDR_A011396
	INFO("SoC workaround for DDR Errata A011396 was applied\n");
#endif
#if ERRATA_DDR_A050450
	INFO("SoC workaround for DDR Errata A050450 was applied\n");
#endif
#if ERRATA_DDR_A008511
	INFO("SoC workaround for DDR Errata A008511 was applied\n");
#endif
#if ERRATA_DDR_A009803
	INFO("SoC workaround for DDR Errata A009803 was applied\n");
#endif
#if ERRATA_DDR_A009942
	INFO("SoC workaround for DDR Errata A009942 was applied\n");
#endif
#if ERRATA_DDR_A010165
	INFO("SoC workaround for DDR Errata A010165 was applied\n");
#endif
#if ERRATA_DDR_A009663
	INFO("SoC workaround for DDR Errata A009663 was applied\n");
#endif
}
