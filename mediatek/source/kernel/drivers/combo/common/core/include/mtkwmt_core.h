/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. and/or its licensors.
 * Without the prior written permission of MediaTek inc. and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 *
 * MediaTek Inc. (C) 2010. All rights reserved.
 *
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
 * RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER ON
 * AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 * The following software/firmware and/or related documentation ("MediaTek Software")
 * have been modified by MediaTek Inc. All revisions are subject to any receiver's
 * applicable license agreements with MediaTek Inc.
 */


/*! \file   mtkwmt_core.h
    \brief  WMT header

    Define WMT internals.
*/

/*******************************************************************************
* Copyright (c) 2009 MediaTek Inc.
*
* All rights reserved. Copying, compilation, modification, distribution
* or any other use whatsoever of this material is strictly prohibited
* except in accordance with a Software License Agreement with
* MediaTek Inc.
********************************************************************************
*/

/*******************************************************************************
* LEGAL DISCLAIMER
*
* BY OPENING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND
* AGREES THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK
* SOFTWARE") RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE
* PROVIDED TO BUYER ON AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY
* DISCLAIMS ANY AND ALL WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT
* LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
* PARTICULAR PURPOSE OR NONINFRINGEMENT. NEITHER DOES MEDIATEK PROVIDE
* ANY WARRANTY WHATSOEVER WITH RESPECT TO THE SOFTWARE OF ANY THIRD PARTY
* WHICH MAY BE USED BY, INCORPORATED IN, OR SUPPLIED WITH THE MEDIATEK
* SOFTWARE, AND BUYER AGREES TO LOOK ONLY TO SUCH THIRD PARTY FOR ANY
* WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE
* FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S SPECIFICATION OR TO
* CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
*
* BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE
* LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL
* BE, AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT
* ISSUE, OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY
* BUYER TO MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
*
* THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE
* WITH THE LAWS OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT
* OF LAWS PRINCIPLES.  ANY DISPUTES, CONTROVERSIES OR CLAIMS ARISING
* THEREOF AND RELATED THERETO SHALL BE SETTLED BY ARBITRATION IN SAN
* FRANCISCO, CA, UNDER THE RULES OF THE INTERNATIONAL CHAMBER OF COMMERCE
* (ICC).
********************************************************************************
*/

#ifndef _MTKWMT_CORE_H_
#define _MTKWMT_CORE_H_

/*******************************************************************************
*                         C O M P I L E R   F L A G S
********************************************************************************
*/


/*******************************************************************************
*                    E X T E R N A L   R E F E R E N C E S
********************************************************************************
*/
#include "mtkwmt.h"

/*******************************************************************************
*                              C O N S T A N T S
********************************************************************************
*/

#define WMT_STP_HDR_TLR_LEN (6) /* header and trailer length */

#define WMT_HDR_LEN (4) /* header length */
#define WMT_STS_LEN (1)/* status length */
#define WMT_FLAG_LEN (1)
#define WMT_HIF_UART_INFO_LEN (4)
#define WMT_FUNC_CTRL_PARAM_LEN (1)

#define STP_BIT(x) (0x1UL << x)
/* STP features byte 0 */
#define STP_B0_EN STP_BIT(0)
#define STP_B0_CHIP_TLR_EN STP_BIT(1) /* trailer enable */
#define STP_B0_HOST_TLR_EN STP_BIT(2) /* trailer enable */
#define STP_B0_TLR_CRC16 STP_BIT(3) /* CRC16 in trailer */
#define STP_B0_TLR_CKS 0 /* checksum in trailer */
#define STP_B0_MDT_EN STP_BIT(4) /* mandatory parts */
#define STP_B0_NAK_EN STP_BIT(5)
#define STP_B0_SEQ_ACK_EN STP_BIT(6) /* check seq/ack fields, send ack/nak frames */
#define STP_B0_HDR_CKS_EN STP_BIT(7) /* check CKS field in header */

/* default valuds: */
#define STP_B0_DFT_UART (STP_B0_EN |\
    STP_B0_CHIP_TLR_EN | \
    STP_B0_HOST_TLR_EN | \
    STP_B0_TLR_CRC16 | \
    STP_B0_MDT_EN | \
    STP_B0_SEQ_ACK_EN | \
    STP_B0_HDR_CKS_EN)
#define STP_B0_DFT_SDIO (STP_B0_EN | \
    STP_B0_MDT_EN)

/* STP features byte 1 */
#define STP_B1_DLM_EN STP_BIT(0) /* enable delimiter for packet except ACK/NAK/RESYNC */
#define STP_B1_WIN_SIZE(x) ((x & 0x7) << 1)

#define STP_B1_UART_DFT (STP_B1_WIN_SIZE(7))
#define STP_B1_SDIO_DFT (STP_B1_WIN_SIZE(7))

/* STP features byte2 & 3: retry timeout */
#define STP_TIMEOUT_MS(x) (UINT16)(x & 0xFFFF)

#define STP_TIMEOUT_DFT (360)

#define WMT_SET (MTK_WCN_BOOL_TRUE)
#define WMT_QUERY (MTK_WCN_BOOL_FALSE)
#define WMT_PKT_FMT_RAW (MTK_WCN_BOOL_TRUE)
#define WMT_PKT_FMT_STP (MTK_WCN_BOOL_FALSE)

#define WMT_FUNC_CTRL_ON (MTK_WCN_BOOL_TRUE)
#define WMT_FUNC_CTRL_OFF (MTK_WCN_BOOL_FALSE)

#define WMT_PWRON_RTY_DFT (2)

/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/

typedef enum _ENUM_DRV_STS {
    DRV_STS_INVALID = 0,
    DRV_STS_UNREG = 1, /* Initial State */
    DRV_STS_POWER_OFF = 2, /* POWER_OFF EVENT Notified */
    //DRV_STS_POWER_ON = 3, /* POWER_ON EVENT Notified */
    DRV_STS_FUNC_ON = 4, /* FUNC ON Notified  */
    DRV_STS_MAX
} ENUM_DRV_STS, *P_ENUM_DRV_STS;

/* WMT Packet Format */
typedef enum _ENUM_PKT_TYPE {
    PKT_TYPE_INVALID = 0,
    PKT_TYPE_CMD = 1,
    PKT_TYPE_EVENT = 2,
    PKT_TYPE_MAX
} ENUM_PKT_TYPE, *P_ENUM_PKT_TYPE;

typedef enum _ENUM_OPCODE {
    OPCODE_INVALID = 0,
    OPCODE_PATCH = 1,
    OPCODE_TEST = 2,
    OPCODE_WAKEUP = 3,
    OPCODE_HIF = 4,
    OPCODE_STRAP_CONF = 5,
    OPCODE_FUNC_CTRL = 6,
    OPCODE_RESET = 7,
    OPCODE_INT = 8,
    OPCODE_MAX
} ENUM_OPCODE, *P_ENUM_OPCODE;

typedef enum _ENUM_OPCODEEST {
    OPCODE_TEST_INVALID = 0,
    OPCODE_TEST_MEM = 1,
    OPCODE_TEST_DMA = 2,
    OPCODE_TEST_PATCH = 3,
    OPCODE_TEST_GPT = 4,
    OPCODE_TEST_CIRQ = 5,
    OPCODE_TEST_UART = 6,
    OPCODE_TEST_MAX
} ENUM_OPCODEEST, *P_ENUM_OPCODEEST;

typedef enum _ENUM_OPCODE_WAKEUP {
    OPCODE_WAKEUP_INVALID = 0,
    OPCODE_WAKEUP_ALLOW = 1,
    OPCODE_WAKEUP_AWAKE = 2,
    OPCODE_WAKEUP_WAKE = 3,
    OPCODE_WAKEUP_MAX
} ENUM_OPCODE_WAKEUP, *P_ENUM_OPCODE_WAKEUP;

typedef enum _ENUM_OPCODE_HIF {
    OPCODE_HIF_INVALID = 0,
    OPCODE_HIF_SET_UART = 1,
    OPCODE_HIF_QUERY_UART = 2,
    OPCODE_HIF_SET_STP = 3,
    OPCODE_HIF_QUERY_STP = 4,
    OPCODE_HIF_MAX
} ENUM_OPCODE_HIF, *P_ENUM_OPCODE_HIF;

typedef struct _WMT_CTX
{
    ENUM_DRV_STS eDrvStatus[DRV_TYPE_MAX]; /* Controlled driver status */
    MTK_WCN_MUTEX wmt_mutex; /* Mutex for WMT */
    MTK_WCN_TIMER wmt_timer; /* Timer for WMT */

    UINT32 wmt_info_bit; /* valid info bit */
    WMT_HIF_CONF wmt_hif_conf; /* HIF information */
} WMT_CTX, *P_WMT_CTX;

typedef struct _WMT_PKT {
    UINT8 eType; // PKT_TYPE_*
    UINT8 eOpCode; // OPCODE_*
    UINT16 u2SduLen; // 2 bytes length, little endian
    UINT8 aucParam[32];
} WMT_PKT, *P_WMT_PKT;

// Pseudo data type: CRC is appended at the end of variable-length rPkt
typedef struct _WMT_PKT_RAW {
    UINT8 ucSync;
    UINT8 ucTypeLenH;
    UINT8 ucLenL;
    UINT8 ucCS;
    WMT_PKT rPkt;
    UINT8 aucCrc[2];
    UINT8 aucUncused[2];
} WMT_PKT_RAW, *P_WMT_PKT_RAW;

typedef struct _WMT_STP_OPT {
    UINT8 ucStpOp[2];
    UINT16 u2TimeOutMs; /* timeout in ms */
} WMT_STP_OPT, *P_WMT_STP_OPT;

typedef struct _WMT_PATCH {
    UINT8 ucDateTime[16];
    UINT8 ucPLat[4];
    UINT16 u2HwVer;
    UINT16 u2SwVer;
    UINT32 u4PatchVer;
} WMT_PATCH, *P_WMT_PATCH;

/*******************************************************************************
*                            P U B L I C   D A T A
********************************************************************************
*/

/*******************************************************************************
*                           P R I V A T E   D A T A
********************************************************************************
*/

/*******************************************************************************
*                                 M A C R O S
********************************************************************************
*/

/*******************************************************************************
*                  F U N C T I O N   D E C L A R A T I O N S
********************************************************************************
*/

#endif /* _MTKWMT_CORE_H_ */

