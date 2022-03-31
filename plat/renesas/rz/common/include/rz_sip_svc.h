/*
 * Copyright (c) 2020-2021, Renesas Electronics Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __RZ_SIP_SVC_H__
#define __RZ_SIP_SVC_H__

/* Function ID to get Device ID */
#define RZ_SIP_SVC_GET_DEVID		U(0x82000010)

/* Function ID to get Chip ID */
#define RZ_SIP_SVC_GET_CHIPID		U(0x82000011)

/* Function ID to read from OTP */
#define RZ_SIP_SVC_READ_OTP     	U(0x82000012)
#define RZ_SIP_SVC_WRITE_OTP     	U(0x82000013)

#endif /* __RZ_SIP_SVC_H__ */
