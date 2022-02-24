#
# Copyright (c) 2021, Markus Bauer <mb@karo-electronics.com>
#
# SPDX-License-Identifier: BSD-3-Clause
#

DDR_SOURCES +=  plat/renesas/rz/soc/${PLAT}/drivers/ddr/param_mc_txrz.c \
		plat/renesas/rz/common/drivers/ddr/param_swizzle_txrz.c

DDR_PLL4    := 1333
$(eval $(call add_define,DDR_PLL4))
