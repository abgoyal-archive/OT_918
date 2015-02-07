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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/nic_rate.h#1 $
*/

/*! \file   "nic_rate.h"
    \brief  The declaration of the nic rate functions

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
** $Log: nic_rate.h $
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\8 2008-08-31 11:53:01 GMT mtk01104
**  Modify comments about profile and change function prototype
**  nicARSetProfile()
**  \main\maintrunk.MT5921\7 2008-08-25 09:39:36 GMT mtk01461
**  \main\maintrunk.MT5921\6 2008-07-08 22:32:57 GMT mtk01104
**  Modify AR_profile and AR_control structures
**  \main\maintrunk.MT5921\5 2008-03-18 11:55:37 GMT mtk01084
**  add new function for modify AR fail down count parameter
**  \main\maintrunk.MT5921\4 2008-02-12 23:00:12 GMT mtk01461
**  Update the naming of AR function's parameter
**  \main\maintrunk.MT5921\3 2007-12-24 15:30:24 GMT mtk01425
**  1. Revise the code of AUTORATE
**
*/
#ifndef _NIC_RATE_H
#define _NIC_RATE_H

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
#define CTS_PROTECTION_TYPE_802_11          0
#define CTS_PROTECTION_TYPE_PROPRIETARY     1

/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/
typedef enum _ENUM_AUTORATE_TYPE_T {
    AR_DISABLE = 0, /* No Autorate */
    AR_HW,          /* Hardware Autorate */
    AR_SW           /* Software Autorate */
} ENUM_AUTORATE_TYPE_T, *P_ENUM_AUTORATE_TYPE_T;

typedef enum _ENUM_AUTORATE_PROFILE_T {
    AR_PROFILE_THROUGHPUT = 0, /* Throughput is major index */
    AR_PROFILE_VOIP,           /* VoIP application */
    AR_PROFILE_NUM
} ENUM_AUTORATE_PROFILE_T, *P_ENUM_AUTORATE_PROFILE_T;

typedef struct _AR_PROFILE_T {
    ENUM_AUTORATE_PROFILE_T eProfile;
    UINT_16                 u2FailCount_up_limit;
    UINT_16                 u2FailCount_down_limit;
    UINT_8                  ucRCParam;
    UINT_8                  ucPERParam;
    UINT_8                  aucReserved[2]; /* Just for alignment */
} AR_PROFILE_T, *P_AR_PROFILE_T;

/* Autorate configuration type structure by *Mike* */
typedef struct _AR_CTRL_T {
    ENUM_AUTORATE_TYPE_T    eType;
    P_AR_PROFILE_T          prAR_Profile;
    UINT_8                  aucARRate1Index[WLAN_TABLE_SIZE];
    UINT_8                  aucReserved2[3]; /* Just for alignment */
    UINT_16                 au2ARBits[WLAN_TABLE_SIZE];
    UINT_8                  aucReserved3[2]; /* Just for alignment */
} AR_CTRL_T, *P_AR_CTRL_T;

typedef struct _RATE_INFO_T {
    BOOLEAN     fgCTSProtectionEnabled;
    UINT_8      ucCTSProtectionMode;

    UINT_8      ucRTSCTSRateIndex;
    BOOLEAN     fgIsRTSCTSRateShortPreamble;

    UINT_8      ucBasicRateIndex;
    BOOLEAN     fgIsBasicRateShortPreamble;

    UINT_16     u2RTSThreshold;

    UINT_8      aucAckCtsRateIndex[RATE_NUM];
    BOOLEAN     fgIsAckCtsRateShortPreamble;
} RATE_INFO_T, *P_RATE_INFO_T;

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
*                   F U N C T I O N   D E C L A R A T I O N S
********************************************************************************
*/
VOID
nicARInit (
    IN  P_ADAPTER_T prAdapter
    );

VOID
nicAREnable (
    IN P_ADAPTER_T prAdapter,
    IN BOOLEAN fgIsHWAR /* TRUE: Hardware Autorate, FALSE: Software Autorate */
    );

VOID
nicARDisable (
    IN  P_ADAPTER_T prAdapter
    );

VOID
nicARSetRate (
    IN P_ADAPTER_T prAdapter,
    IN UINT_16 u2RateSet,
    IN BOOLEAN fgIsShortPreamble,
    IN UINT_8 ucRate1,
    IN UINT_8 ucWlanIdx,
    IN BOOLEAN fgIsRate1Assigned
    );

VOID
nicARReset (
    IN P_ADAPTER_T prAdapter,
    IN UINT_8 ucWlanIdx
    );

VOID
nicARSetProfile (
    IN P_ADAPTER_T prAdapter,
    IN ENUM_AUTORATE_PROFILE_T eARProfile
    );

VOID
nicRateEnableProtection (
    IN P_ADAPTER_T prAdapter,
    IN UINT_8 ucProtectionMode
    );

VOID
nicRateDisableProtection (
    IN P_ADAPTER_T prAdapter
    );

VOID
nicRateSetCTSRTSRate (
    IN P_ADAPTER_T prAdapter,
    IN UINT_8 ucRateIndex,
    IN BOOLEAN fgIsShortPreamble
    );

VOID
nicRateSetBasicRate (
    IN P_ADAPTER_T prAdapter,
    IN UINT_8 ucRateIndex,
    IN BOOLEAN fgIsShortPreamble
    );

VOID
nicRateSetRTSThreshold (
    IN P_ADAPTER_T prAdapter,
    IN UINT_16 u2RTSThreshold
    );

VOID
nicRateSetAckCtsRate(
    IN P_ADAPTER_T prAdapter,
    UINT_8 aucAckCtsRateIndex[],
    BOOLEAN fgIsShortPreamble
    );

#endif /* _NIC_RATE_H */


