/*
 * Copyright (C) Lothar Waßmann <LW@KARO-electronics.de>
 *
 * based on: plat/rockchip/common/include/plat_private.h
 * Copyright (c) 2014-2019, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef PLAT_PRIVATE_H
#define PLAT_PRIVATE_H

#ifndef __ASSEMBLER__

uint32_t imx_get_uart_base(void);
uint32_t imx_get_uart_baudrate(void);
uint32_t imx_get_uart_clock(void);

void imx_params_early_setup(u_register_t plat_param_from_bl2);

#endif /* __ASSEMBLER__ */

#endif /* PLAT_PRIVATE_H */
