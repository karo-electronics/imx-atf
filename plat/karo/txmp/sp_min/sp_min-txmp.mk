#
# Copyright (c) 2017-2018, ARM Limited and Contributors. All rights reserved.
#
# SPDX-License-Identifier: BSD-3-Clause
#

SP_MIN_WITH_SECURE_FIQ	:=	1

BL32_SOURCES		+=	plat/common/aarch32/platform_mp_stack.S		\
				drivers/st/clk/stm32mp1_calib.c			\
				drivers/st/etzpc/etzpc.c			\
				drivers/st/rng/stm32_rng.c			\
				drivers/st/rtc/stm32_rtc.c			\
				drivers/st/tamper/stm32_tamp.c			\
				drivers/st/timer/stm32_timer.c 			\
				plat/$(VENDOR)/$(PLAT)/sp_min/sp_min_setup.c		\
				plat/$(VENDOR)/$(PLAT)/stm32mp1_low_power.c		\
				plat/$(VENDOR)/$(PLAT)/stm32mp1_pm.c			\
				plat/$(VENDOR)/$(PLAT)/stm32mp1_power_config.c	\
				plat/$(VENDOR)/$(PLAT)/stm32mp1_topology.c
# Generic GIC v2
BL32_SOURCES		+=	drivers/arm/gic/common/gic_common.c	\
				drivers/arm/gic/v2/gicv2_helpers.c	\
				drivers/arm/gic/v2/gicv2_main.c		\
				plat/common/plat_gicv2.c		\
				plat/$(VENDOR)/$(PLAT)/stm32mp1_gic.c

# Generic PSCI
BL32_SOURCES		+=	plat/common/plat_psci_common.c

# stm32mp1 specific services
BL32_SOURCES		+=	plat/$(VENDOR)/$(PLAT)/services/bsec_svc.c		\
				plat/$(VENDOR)/$(PLAT)/services/low_power_svc.c	\
				plat/$(VENDOR)/$(PLAT)/services/pwr_svc.c		\
				plat/$(VENDOR)/$(PLAT)/services/rcc_svc.c		\
				plat/$(VENDOR)/$(PLAT)/services/stm32mp1_svc_setup.c
