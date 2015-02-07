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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/nic_privacy.h#1 $
*/

/*! \file   "nic_privacy.h"
    \brief  The declaration of nic privacy functions

    Detail description.
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
** $Log: nic_privacy.h $
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\7 2008-10-27 18:55:38 GMT mtk01088
**  adjust the function declaration
**  \main\maintrunk.MT5921\6 2008-09-01 16:53:30 GMT mtk01088
**  adjust the code for code review 
**  \main\maintrunk.MT5921\5 2008-02-29 12:38:57 GMT mtk01088
**  \main\maintrunk.MT5921\4 2008-02-12 23:00:09 GMT mtk01461
**  Add TX auto fragmentation for BT support
**  \main\maintrunk.MT5921\3 2007-11-20 10:46:40 GMT mtk01088
**  add function for invalid key while countermeasure
**  \main\maintrunk.MT5921\2 2007-11-08 20:19:25 GMT mtk01088
**  add macthed function by keyid
*/
#ifndef _NIC_PRIVACY_H
#define _NIC_PRIVACY_H

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

/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/
/*! \brief key structure for NIC key configuration */
typedef struct _SW_KEY_STRUC_T {
    UCHAR               ucRCA1;               /* check U/B/M of A1 */
    BOOLEAN             fgRCA2;               /* check address 2 */
    BOOLEAN             fgRCID;               /* check key ID */
    UINT_8              ucKeyId;              /* key ID, range: 0~3 */
    UINT_8              ucCipher;             /* cipher, range: 0~6 */
    BOOLEAN             fgIKV;
    UINT_8              aucAddr[MAC_ADDR_LEN]; /* mapping address */
    UINT_8              aucKeyMaterial[TKIP_KEY_LEN - (2 * MIC_KEY_LEN)];   /* key material */
    UINT_8              aucRxMicMaterial[MIC_KEY_LEN];  /* Rx MIC key material */
    UINT_8              aucTxMicMaterial[MIC_KEY_LEN];  /* Tx MIC key material */
} SW_KEY_STRUC_T, *P_SW_KEY_STRUC_T;

/*! \brief wlan table setting exclude key structure */
typedef struct _WT_CTRL_STRUC_T {
    BOOLEAN             fgTV;                 /*!< Tx Entry valid */
    BOOLEAN             fgTKV;                /*!< Tx Key valid */
    BOOLEAN             fgRV;                 /*!< Rx Entry valid */
    BOOLEAN             fgRKV;                /*!< Rx Key valid */
    BOOLEAN             fgT1X;                /*!< Tx Port Control bit */
    BOOLEAN             fgR1X;                /*!< Rx Port Control bit */
    UINT_8              ucMuar;               /*!< the index for rx a1 muar match */
    BOOLEAN             fgQoS;                /*!< QoS setting bit */
    BOOLEAN             fgAntenna;            /*!< Antenna setting bit */
    UINT_8              ucRate1;              /*!< Rate 1 setting */
    UINT_8              ucRate2;              /*!< Rate 2 setting */
    UINT_8              ucRate3;              /*!< Rate 3 setting */
    UINT_8              ucRate4;              /*!< Rate 4 setting */
} WT_CTRL_STRUC_T, *P_WT_CTRL_STRUC_T;

/*! \brief key entry configuration structure */
typedef struct _WLAN_ENTRY_CTRL_T {
    BOOLEAN             fgUsed;
    P_STA_RECORD_T      prSta;
    WT_CTRL_STRUC_T     rCtrl;
    SW_KEY_STRUC_T      rSWKey;
} WLAN_ENTRY_CTRL_T, *P_WLAN_ENTRY_CTRL_T;

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
nicPrivacyEnableHwTxPortControl(
    IN P_ADAPTER_T          prAdapter
    );

VOID
nicPrivacyInitialize(
    IN P_ADAPTER_T          prAdapter
    );

BOOLEAN
nicPrivacyInvalidKey(
    IN P_ADAPTER_T          prAdapter,
    IN PUINT_8              pucBssid
   );

VOID
nicPrivacyPortControl(
    IN P_ADAPTER_T          prAdapter,
    IN PUINT_8              pucBssid,
    IN BOOLEAN              fgTxPort,
    IN BOOLEAN              fgRxPort
   );

BOOLEAN
nicPrivacySetKeyEntry(
    IN P_ADAPTER_T           prAdapter,
    IN BOOLEAN               fgTxKey,
    IN PUINT_8               pucBssid,
    IN UINT_8                ucKeyId,
    IN PUINT_8               pucKeyMaterial,
    IN UINT_8                ucKeyLen,
    IN UINT_8                ucCipherMode,
    IN UINT_8                ucTxMicOffset,
    IN UINT_8                ucRxMicOffset
    );

BOOLEAN
nicPrivacyMatchForEntry(
    IN  P_ADAPTER_T         prAdapter,
    IN  PUINT_8             pucBssid,
    IN  UINT_8              ucKeyId,
    OUT PUINT_8             pucEntryIndex
    );

BOOLEAN
nicPrivacyUpdateBySta(
    IN P_ADAPTER_T           prAdapter,
    IN PUINT_8               pucBSSID,
    IN P_STA_RECORD_T        prSta,
    IN PBOOLEAN              pfgQoS,
    IN PBOOLEAN              pfgAntenna,
    IN PUINT_8               pucMuar,
    IN PUINT_8               pucRate1,
    IN PUINT_8               pucRate2,
    IN PUINT_8               pucRate3,
    IN PUINT_8               pucRate4
    );

VOID
nicPrivacySetKeyToTemplateEntry (
    IN P_ADAPTER_T           prAdapter,
    IN PUINT_8               pucBssid,
    IN PUINT_8               pucKeyMaterial,
    IN UINT_8                ucKeyLen,
    IN UINT_8                ucCipherMode,
    IN UINT_8                ucTxMicOffset,
    IN UINT_8                ucRxMicOffset
    );

P_STA_RECORD_T
nicPrivacyGetWlanIndexByAddr(
    IN  P_ADAPTER_T          prAdapter,
    IN  PUINT_8              pucBssid,
    OUT PUINT_8              pucWlanIndex
    );

P_STA_RECORD_T
nicPrivacyGetStaRecordByWlanIndex(
    IN  P_ADAPTER_T         prAdapter,
    IN  UINT_8              ucWlanIndex
    );

BOOLEAN
nicPrivacyCopyFromTemplateEntry(
    IN P_ADAPTER_T           prAdapter
    );

VOID
nicPrivacyInvalidEntryRx(
    IN P_ADAPTER_T           prAdapter,
    IN PUINT_8               pucBssid
    );

VOID
nicPrivacyInvalidTemplateEntry(
    IN P_ADAPTER_T           prAdapter
    );

BOOLEAN
nicPrivacySetWlanTable(
    IN  P_ADAPTER_T          prAdapter,
    IN  UINT_8               ucEntry,
    IN  P_STA_RECORD_T       prSta,
    IN  P_WT_CTRL_STRUC_T    prWTCtrl,
    IN  P_SW_KEY_STRUC_T     prSwKey
    );

BOOLEAN
nicPrivacyClearWlanTable(
    IN  P_ADAPTER_T          prAdapter,
    IN  UINT_8               ucEntry
    );

VOID
nicPrivacyDumpWlanTable(
    IN  P_ADAPTER_T          prAdapter,
    IN  UINT_8               ucEntry
    );

#endif /* _NIC_PRIVACY_H */

