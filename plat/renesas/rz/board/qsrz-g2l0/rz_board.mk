#
# Copyright (c) 2022, Markus Bauer <mb@karo-electronics.com>
#
# SPDX-License-Identifier: BSD-3-Clause
#

DDR_SOURCES +=  plat/renesas/rz/soc/${PLAT}/drivers/ddr/param_mc_qsrz-g2l0.c \
		plat/renesas/rz/common/drivers/ddr/param_swizzle_qsrz-g2l0.c

DDR_PLL4    := 1333
$(eval $(call add_define,DDR_PLL4))
