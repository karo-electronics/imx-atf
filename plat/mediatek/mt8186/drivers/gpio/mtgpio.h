/*
 * Copyright (c) 2021, MediaTek Inc. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MT_GPIO_H
#define MT_GPIO_H

#include <mtgpio_common.h>

/* Enumeration for GPIO pin */
typedef enum GPIO_PIN {
	GPIO_UNSUPPORTED = -1,
	GPIO0, GPIO1, GPIO2, GPIO3, GPIO4, GPIO5, GPIO6,
	GPIO7, GPIO8, GPIO9, GPIO10, GPIO11, GPIO12, GPIO13, GPIO14,
	GPIO15, GPIO16, GPIO17, GPIO18, GPIO19, GPIO20, GPIO21, GPIO22,
	GPIO23, GPIO24, GPIO25, GPIO26, GPIO27, GPIO28, GPIO29, GPIO30,
	GPIO31, GPIO32, GPIO33, GPIO34, GPIO35, GPIO36, GPIO37, GPIO38,
	GPIO39, GPIO40, GPIO41, GPIO42, GPIO43, GPIO44, GPIO45, GPIO46,
	GPIO47, GPIO48, GPIO49, GPIO50, GPIO51, GPIO52, GPIO53, GPIO54,
	GPIO55, GPIO56, GPIO57, GPIO58, GPIO59, GPIO60, GPIO61, GPIO62,
	GPIO63, GPIO64, GPIO65, GPIO66, GPIO67, GPIO68, GPIO69, GPIO70,
	GPIO71, GPIO72, GPIO73, GPIO74, GPIO75, GPIO76, GPIO77, GPIO78,
	GPIO79, GPIO80, GPIO81, GPIO82, GPIO83, GPIO84, GPIO85, GPIO86,
	GPIO87, GPIO88, GPIO89, GPIO90, GPIO91, GPIO92, GPIO93, GPIO94,
	GPIO95, GPIO96, GPIO97, GPIO98, GPIO99, GPIO100, GPIO101, GPIO102,
	GPIO103, GPIO104, GPIO105, GPIO106, GPIO107, GPIO108, GPIO109, GPIO110,
	GPIO111, GPIO112, GPIO113, GPIO114, GPIO115, GPIO116, GPIO117, GPIO118,
	GPIO119, GPIO120, GPIO121, GPIO122, GPIO123, GPIO124, GPIO125, GPIO126,
	GPIO127, GPIO128, GPIO129, GPIO130, GPIO131, GPIO132, GPIO133, GPIO134,
	GPIO135, GPIO136, GPIO137, GPIO138, GPIO139, GPIO140, GPIO141, GPIO142,
	GPIO143, GPIO144, GPIO145, GPIO146, GPIO147, GPIO148, GPIO149, GPIO150,
	GPIO151, GPIO152, GPIO153, GPIO154, GPIO155, GPIO156, GPIO157, GPIO158,
	GPIO159, GPIO160, GPIO161, GPIO162, GPIO163, GPIO164, GPIO165, GPIO166,
	GPIO167, GPIO168, GPIO169, GPIO170, GPIO171, GPIO172, GPIO173, GPIO174,
	GPIO175, GPIO176, GPIO177, GPIO178, GPIO179, GPIO180, GPIO181, GPIO182,
	GPIO183, GPIO184,
	MT_GPIO_BASE_MAX
} GPIO_PIN;

static const struct mt_pin_info mt_pin_infos[] = {
	PIN(0, 0, 13, 0x16, 0x40),
	PIN(1, 0, 14, 0x16, 0x40),
	PIN(2, 0, 17, 0x16, 0x40),
	PIN(3, 0, 18, 0x16, 0x40),
	PIN(4, 0, 19, 0x16, 0x40),
	PIN(5, 0, 20, 0x16, 0x40),
	PIN(6, 0, 19, 0x24, 0x40),
	PIN(7, 0, 20, 0x24, 0x40),
	PIN(8, 0, 21, 0x24, 0x40),
	PIN(9, 0, 22, 0x24, 0x40),
	PIN(10, 0, 16, 0x24, 0x40),
	PIN(11, 0, 17, 0x24, 0x40),
	PIN(12, 0, 18, 0x24, 0x40),
	PIN(13, 0, 0, 0x23, 0x60),
	PIN(14, 0, 1, 0x23, 0x60),
	PIN(15, 0, 15, 0x16, 0x40),
	PIN(16, 0, 16, 0x16, 0x40),
	PIN(17, 0, 9, 0x25, 0x70),
	PIN(18, 0, 10, 0x25, 0x70),
	PIN(19, 0, 3, 0x25, 0x70),
	PIN(20, 0, 6, 0x25, 0x70),
	PIN(21, 0, 4, 0x25, 0x70),
	PIN(22, 0, 7, 0x25, 0x70),
	PIN(23, 0, 5, 0x25, 0x70),
	PIN(24, 0, 8, 0x25, 0x70),
	PIN(25, 0, 18, 0x25, 0x70),
	PIN(26, 0, 15, 0x25, 0x70),
	PIN(27, 0, 17, 0x25, 0x70),
	PIN(28, 0, 16, 0x25, 0x70),
	PIN(29, 0, 0, 0x16, 0x40),
	PIN(30, 0, 1, 0x16, 0x40),
	PIN(31, 0, 2, 0x16, 0x40),
	PIN(32, 0, 25, 0x12, 0x50),
	PIN(33, 0, 27, 0x12, 0x50),
	PIN(34, 0, 26, 0x12, 0x50),
	PIN(35, 0, 28, 0x12, 0x50),
	PIN(36, 0, 9, 0x12, 0x50),
	PIN(37, 0, 10, 0x12, 0x50),
	PIN(38, 0, 12, 0x12, 0x50),
	PIN(39, 0, 11, 0x12, 0x50),
	PIN(40, 0, 13, 0x12, 0x50),
	PIN(41, 0, 14, 0x12, 0x50),
	PIN(42, 0, 16, 0x12, 0x50),
	PIN(43, 0, 15, 0x12, 0x50),
	PIN(44, 0, 28, 0x25, 0x70),
	PIN(45, 0, 29, 0x25, 0x70),
	PIN(46, 0, 31, 0x25, 0x70),
	PIN(47, 0, 30, 0x25, 0x70),
	PIN(48, 0, 17, 0x12, 0x50),
	PIN(49, 0, 18, 0x12, 0x50),
	PIN(50, 0, 20, 0x12, 0x50),
	PIN(51, 0, 19, 0x12, 0x50),
	PIN(52, 0, 12, 0x23, 0x60),
	PIN(53, 0, 13, 0x23, 0x60),
	PIN(54, 0, 15, 0x23, 0x60),
	PIN(55, 0, 14, 0x23, 0x60),
	PIN(56, 0, 12, 0x25, 0x70),
	PIN(57, 0, 11, 0x25, 0x70),
	PIN(58, 0, 13, 0x25, 0x70),
	PIN(59, 0, 14, 0x25, 0x70),
	PIN(60, 0, 21, 0x23, 0x60),
	PIN(61, 0, 16, 0x23, 0x60),
	PIN(62, 0, 22, 0x23, 0x60),
	PIN(63, 0, 17, 0x23, 0x60),
	PIN(64, 0, 18, 0x23, 0x60),
	PIN(65, 0, 19, 0x23, 0x60),
	PIN(66, 0, 20, 0x23, 0x60),
	PIN(67, 1, 10, 0x21, 0x70),
	PIN(68, 1, 0, 0x21, 0x70),
	PIN(69, 1, 1, 0x21, 0x70),
	PIN(70, 1, 11, 0x21, 0x70),
	PIN(71, 1, 2, 0x21, 0x70),
	PIN(72, 1, 3, 0x21, 0x70),
	PIN(73, 1, 4, 0x21, 0x70),
	PIN(74, 1, 5, 0x21, 0x70),
	PIN(75, 1, 6, 0x21, 0x70),
	PIN(76, 1, 7, 0x21, 0x70),
	PIN(77, 1, 8, 0x21, 0x70),
	PIN(78, 1, 9, 0x21, 0x70),
	PIN(79, 1, 0, 0x25, 0x80),
	PIN(80, 1, 1, 0x25, 0x80),
	PIN(81, 1, 2, 0x25, 0x80),
	PIN(82, 1, 3, 0x25, 0x80),
	PIN(83, 0, 3, 0x16, 0x40),
	PIN(84, 1, 0, 0x23, 0x70),
	PIN(85, 1, 1, 0x23, 0x70),
	PIN(86, 1, 2, 0x23, 0x70),
	PIN(87, 1, 3, 0x23, 0x70),
	PIN(88, 1, 4, 0x23, 0x70),
	PIN(89, 1, 5, 0x23, 0x70),
	PIN(90, 0, 2, 0x23, 0x60),
	PIN(91, 0, 23, 0x23, 0x60),
	PIN(92, 0, 25, 0x23, 0x60),
	PIN(93, 0, 3, 0x23, 0x60),
	PIN(94, 0, 24, 0x23, 0x60),
	PIN(95, 0, 26, 0x23, 0x60),
	PIN(96, 0, 1, 0x12, 0x50),
	PIN(97, 0, 0, 0x12, 0x50),
	PIN(98, 0, 2, 0x12, 0x50),
	PIN(99, 0, 14, 0x24, 0x40),
	PIN(100, 0, 15, 0x24, 0x40),
	PIN(101, 0, 13, 0x24, 0x40),
	PIN(102, 0, 12, 0x24, 0x40),
	PIN(103, 0, 0, 0x24, 0x40),
	PIN(104, 0, 1, 0x24, 0x40),
	PIN(105, 0, 4, 0x24, 0x40),
	PIN(106, 0, 5, 0x24, 0x40),
	PIN(107, 0, 6, 0x24, 0x40),
	PIN(108, 0, 7, 0x24, 0x40),
	PIN(109, 0, 8, 0x24, 0x40),
	PIN(110, 0, 9, 0x24, 0x40),
	PIN(111, 0, 10, 0x24, 0x40),
	PIN(112, 0, 11, 0x24, 0x40),
	PIN(113, 0, 2, 0x24, 0x40),
	PIN(114, 0, 3, 0x24, 0x40),
	PIN(115, 0, 4, 0x23, 0x60),
	PIN(116, 0, 7, 0x23, 0x60),
	PIN(117, 0, 5, 0x23, 0x60),
	PIN(118, 0, 6, 0x23, 0x60),
	PIN(119, 0, 22, 0x25, 0x70),
	PIN(120, 0, 19, 0x25, 0x70),
	PIN(121, 0, 20, 0x25, 0x70),
	PIN(122, 0, 21, 0x25, 0x70),
	PIN(123, 0, 23, 0x25, 0x70),
	PIN(124, 0, 0, 0x25, 0x70),
	PIN(125, 0, 1, 0x25, 0x70),
	PIN(126, 0, 2, 0x25, 0x70),
	PIN(127, 0, 8, 0x23, 0x60),
	PIN(128, 0, 10, 0x23, 0x60),
	PIN(129, 0, 24, 0x25, 0x70),
	PIN(130, 0, 26, 0x25, 0x70),
	PIN(131, 0, 25, 0x25, 0x70),
	PIN(132, 0, 27, 0x25, 0x70),
	PIN(133, 0, 9, 0x21, 0x60),
	PIN(134, 0, 12, 0x21, 0x60),
	PIN(135, 0, 21, 0x16, 0x40),
	PIN(136, 0, 24, 0x16, 0x40),
	PIN(137, 0, 10, 0x21, 0x60),
	PIN(138, 0, 13, 0x21, 0x60),
	PIN(139, 0, 7, 0x12, 0x50),
	PIN(140, 0, 8, 0x12, 0x50),
	PIN(141, 0, 9, 0x23, 0x60),
	PIN(142, 0, 11, 0x23, 0x60),
	PIN(143, 0, 22, 0x16, 0x40),
	PIN(144, 0, 25, 0x16, 0x40),
	PIN(145, 0, 23, 0x16, 0x40),
	PIN(146, 0, 26, 0x16, 0x40),
	PIN(147, 0, 23, 0x24, 0x40),
	PIN(148, 0, 24, 0x24, 0x40),
	PIN(149, 0, 25, 0x24, 0x40),
	PIN(150, 0, 26, 0x24, 0x40),
	PIN(151, 0, 27, 0x24, 0x40),
	PIN(152, 0, 28, 0x24, 0x40),
	PIN(153, 0, 29, 0x24, 0x40),
	PIN(154, 0, 30, 0x24, 0x40),
	PIN(155, 0, 31, 0x24, 0x40),
	PIN(156, 0, 0, 0x24, 0x50),
	PIN(157, 0, 4, 0x12, 0x50),
	PIN(158, 0, 3, 0x12, 0x50),
	PIN(159, 0, 6, 0x12, 0x50),
	PIN(160, 0, 5, 0x12, 0x50),
	PIN(161, 0, 23, 0x12, 0x50),
	PIN(162, 0, 24, 0x12, 0x50),
	PIN(163, 0, 11, 0x21, 0x60),
	PIN(164, 0, 8, 0x21, 0x60),
	PIN(165, 0, 16, 0x21, 0x60),
	PIN(166, 0, 1, 0x21, 0x60),
	PIN(167, 0, 7, 0x21, 0x60),
	PIN(168, 0, 4, 0x21, 0x60),
	PIN(169, 0, 5, 0x21, 0x60),
	PIN(170, 0, 0, 0x21, 0x60),
	PIN(171, 0, 6, 0x21, 0x60),
	PIN(172, 0, 2, 0x21, 0x60),
	PIN(173, 0, 3, 0x21, 0x60),
	PIN(174, 0, 7, 0x16, 0x40),
	PIN(175, 0, 8, 0x16, 0x40),
	PIN(176, 0, 4, 0x16, 0x40),
	PIN(177, 0, 5, 0x16, 0x40),
	PIN(178, 0, 6, 0x16, 0x40),
	PIN(179, 0, 9, 0x16, 0x40),
	PIN(180, 0, 10, 0x16, 0x40),
	PIN(181, 0, 11, 0x16, 0x40),
	PIN(182, 0, 12, 0x16, 0x40),
	PIN(183, 0, 21, 0x12, 0x50),
	PIN(184, 0, 22, 0x12, 0x50),
};

#endif /* MT_GPIO_H */
