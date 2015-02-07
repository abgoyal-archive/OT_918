/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. and/or its licensors.
 * Without the prior written permission of MediaTek inc. and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 */
/* MediaTek Inc. (C) 2010. All rights reserved.
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

/*
** $Id:
*/

/*! \file   "mgt_buf.h"
    \brief  In this file we define the structure for Management Frame Buffer.

		Before transmitting any MMPDU from Protocol Stack, we need to allocate a
	frame buffer and compose the MMPDU frame body on it. After TX done event, this
	frame buffer should also be return to the management function.
        The structure MGT_PACKET_T is the Mgmt Frame Buffer handler, and the
    structure MGT_BUF_INFO_T is the control unit for the buffer allocation & releasing
    functions.
*/

/*******************************************************************************
* Copyright (c) 2007 MediaTek Inc.
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

/*
** $Log:
*/

#ifndef _MGT_BUF_H
#define _MGT_BUF_H

/*******************************************************************************
*                         C O M P I L E R   F L A G S
********************************************************************************
*/

/*******************************************************************************
*                    E X T E R N A L   R E F E R E N C E S
********************************************************************************
*/

/*******************************************************************************
*                              C O N S T A N T S
********************************************************************************
*/
#define POWER_OF_2(n)                           BIT(n)

/* Size of a basic management buffer block in power of 2 */
#define MGT_BUF_BLOCK_SIZE_IN_POWER_OF_2        7 /* 7 to the power of 2 = 128 */

/* Size of a basic management buffer block */
#define MGT_BUF_BLOCK_SIZE                      POWER_OF_2(MGT_BUF_BLOCK_SIZE_IN_POWER_OF_2)

/* Total size of (n) basic management buffer blocks */
#define MGT_BUF_BLOCKS_SIZE(n)                  ((UINT_32)(n) << MGT_BUF_BLOCK_SIZE_IN_POWER_OF_2)

/* Number of management buffer block */
#define MAX_NUM_OF_MGT_BUF_BLOCKS               32 /* Range: 1~32, currently use 32*128=4K Bytes */

/* Number of management frame control unit */
#define MAX_NUM_OF_MGT_PACKETS                  CFG_MAX_NUM_MSDU_INFO_FOR_TCM /* packets */

/* Size of overall management frame buffer */
#define MGT_BUFFER_SIZE                         (MAX_NUM_OF_MGT_BUF_BLOCKS * MGT_BUF_BLOCK_SIZE)

/* Size of all management frame descriptors */
#define MGT_PACKET_DESCRIPTORS_SIZE             (MAX_NUM_OF_MGT_PACKETS * ALIGN_4(sizeof(MGT_PACKET_T)))

/* Reserve some size in every MGT_PACKET's buffer */
#define MGT_PACKET_RESERVED_SIZE                ALIGN_4(TFCB_SIZE)


/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/
#if ((MAX_NUM_OF_MGT_BUF_BLOCKS > 32) || (MAX_NUM_OF_MGT_BUF_BLOCKS <= 0))
    #error > #define MAX_NUM_OF_MGT_BUF_BLOCKS : Out of boundary !
#elif MAX_NUM_OF_MGT_BUF_BLOCKS > 16
    typedef UINT_32 BUF_BITMAP;
#elif MAX_NUM_OF_MGT_BUF_BLOCKS > 8
    typedef UINT_16 BUF_BITMAP;
#else
    typedef UINT_8 BUF_BITMAP;
#endif /* MAX_NUM_OF_MGT_BUF_BLOCKS */

/* Control variable of TX management memory pool */
typedef struct _MGT_BUF_INFO_T {
    UINT_32     u4MgtBufCachedSize;
    PUINT_8     pucMgtBufCached;
    PUINT_8     pucMgtBufPoolCached;

    QUE_T       rFreeMgtPacketList;
#if CFG_TX_DBG_MGT_BUF
    UINT_8      ucMaxAllocatedDepth;
#endif /* CFG_TX_DBG_MGT_BUF */
    BUF_BITMAP  rFreeMgtBufBlocksBitmap;
    BUF_BITMAP  rMgtBufBlocksToBitsTable[MAX_NUM_OF_MGT_BUF_BLOCKS + 1];
} MGT_BUF_INFO_T, *P_MGT_BUF_INFO_T;

typedef struct _MGT_PACKET_T {
    QUE_ENTRY_T rQueEntry;
    BUF_BITMAP  rAllocatedMgtBufBlocksBitmap;
    PUINT_8     pucHead;
    PUINT_8     pucData;
    PUINT_8     pucTail;
    PUINT_8     pucEnd;
} MGT_PACKET_T, *P_MGT_PACKET_T;


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
#define MGT_PACKET_GET_BUFFER(prMgtPacket)  \
    (((P_MGT_PACKET_T)(prMgtPacket))->pucData)

#define MGT_PACKET_GET_LENGTH(prMgtPacket)  \
    ((UINT_32)((UINT_32)((P_MGT_PACKET_T)(prMgtPacket))->pucTail - \
                (UINT_32)((P_MGT_PACKET_T)(prMgtPacket))->pucData))

/*******************************************************************************
*                   F U N C T I O N   D E C L A R A T I O N S
********************************************************************************
*/
VOID
mgtBufInitialize (
    IN P_ADAPTER_T prAdapter
    );

P_MGT_PACKET_T
mgtBufAllocateMgtPacket (
    IN P_ADAPTER_T prAdapter,
    IN UINT_32 u4Length
    );

VOID
mgtBufFreeMgtPacket (
    IN P_ADAPTER_T prAdapter,
    IN P_MGT_PACKET_T prMgtPacket
    );

#if CFG_TX_DBG_MGT_BUF
VOID
mgtBufQueryStatus (
    IN P_ADAPTER_T prAdapter,
    IN PUINT_8 pucBuffer,
    OUT PUINT_32 pu4Count
    );
#endif /* CFG_TX_DBG_MGT_BUF */

BOOLEAN
mgtPacketCheckHeadroom (
    IN P_MGT_PACKET_T prMgtPacket,
    IN UINT_32 u4Length
    );

PUINT_8
mgtPacketPut (
    IN P_MGT_PACKET_T prMgtPacket,
    IN UINT_32 u4Length
    );

#if 0 /* RESERVE */
PUINT_8
mgtPacketPush (
    IN P_MGT_PACKET_T prMgtPacket,
    IN UINT_32 u4Length
    );

BOOLEAN
mgtPacketReserveHeadroom (
    IN P_MGT_PACKET_T prMgtPacket,
    IN UINT_32 u4Length
    );

UINT_32
mgtPacketHeadroomLength (
    IN P_MGT_PACKET_T prMgtPacket
    );

UINT_32
mgtPacketLength (
    IN P_MGT_PACKET_T prMgtPacket
    );
#endif

/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/
#endif /* _MGT_BUF_H */


