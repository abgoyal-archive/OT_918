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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/nic_rate.c#1 $
*/

/*! \file   nic_rate.c
    \brief  Functions that provide rate operation in NIC's (Network Interface Card) point of view.

    This file includes functions which unite multiple hal(Hardware) operations
    and also take the responsibility of Software Resource Management in order
    to keep the synchronization with Hardware Manipulation.
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
** $Log: nic_rate.c $
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\11 2008-12-01 18:21:31 GMT mtk01088
**  \main\maintrunk.MT5921\10 2008-11-28 17:36:51 GMT mtk01088
**  fixed the lint warning
**  \main\maintrunk.MT5921\9 2008-08-31 11:54:28 GMT mtk01104
**  Modify code alignment and comments
**  \main\maintrunk.MT5921\8 2008-07-08 22:36:00 GMT mtk01104
**  To modify weighting parameters, modify several functions.
**  \main\maintrunk.MT5921\7 2008-03-18 12:03:56 GMT mtk01084
**  add function for AR to set the Fail Down Count Limit
**  \main\maintrunk.MT5921\6 2008-02-12 23:00:48 GMT mtk01461
**  Add TX auto fragmentation for BT support
**  \main\maintrunk.MT5921\5 2007-12-24 15:59:25 GMT mtk01425
**  1. Revise Autorate function
*/

/*******************************************************************************
*                         C O M P I L E R   F L A G S
********************************************************************************
*/

/*******************************************************************************
*                    E X T E R N A L   R E F E R E N C E S
********************************************************************************
*/
#include "precomp.h"


/*******************************************************************************
*                              C O N S T A N T S
********************************************************************************
*/

const AR_PROFILE_T arARProfileSetting[AR_PROFILE_NUM] = {
    /* Profie Index       , up_limit, down_limit, RC,  PER,  reserve, reserve */
    {AR_PROFILE_THROUGHPUT, 0x0217,   0x0FFF,    0x03, 0x03, {0x00,    0x00}},
    {AR_PROFILE_VOIP,       0x0217,   0x09C4,    0x03, 0x03, {0x00,    0x00}}
};

/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/

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

/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/

/*----------------------------------------------------------------------------*/
/*!
* \brief Initialize autorate variables
*
* \param[in] prAdapter      a pointer to adapter private data structure.
*
* \return N/A
*/
/*----------------------------------------------------------------------------*/
VOID
nicARInit (
    IN  P_ADAPTER_T prAdapter
    )
{
    nicARDisable(prAdapter);
    halARInitialize(prAdapter);

    nicARSetProfile(prAdapter, AR_PROFILE_THROUGHPUT);
}

/*----------------------------------------------------------------------------*/
/*!
* \brief Enable Autorate function
*
* \param[in] prAdapter      pointer to adapter private data structure.
* \param[in] fgIsHWAR       TRUE: HW autorate, FALSE: SW autorate
*
* \return N/A
*/
/*----------------------------------------------------------------------------*/
VOID
nicAREnable (
    IN P_ADAPTER_T prAdapter,
    IN BOOLEAN fgIsHWAR /* TRUE: Hardware Autorate, FALSE: Software Autorate */
    )
{
    P_AR_CTRL_T     prARCtrl;
    P_AR_PROFILE_T  prAR_Setting;

    ASSERT(prAdapter);
    prARCtrl = &prAdapter->rARCtrl;
    prAR_Setting = prARCtrl->prAR_Profile;

    if (fgIsHWAR) {
        prARCtrl->eType = AR_HW;

        ASSERT(prAR_Setting);
        if (prAR_Setting) {
            halARSetParam(prAdapter, prAR_Setting->u2FailCount_up_limit,
                prAR_Setting->u2FailCount_down_limit, prAR_Setting->ucRCParam,
                prAR_Setting->ucPERParam);
        }
    }
    else {
        prARCtrl->eType = AR_SW;
    }
}

/*----------------------------------------------------------------------------*/
/*!
* \brief Disable autorate function
*
* \param[in] prAdapter      a pointer to adapter private data structure.
*
* \return N/A
*/
/*----------------------------------------------------------------------------*/
VOID
nicARDisable (
    IN  P_ADAPTER_T prAdapter
    )
{
    ASSERT(prAdapter);
    
    prAdapter->rARCtrl.eType = AR_DISABLE;
    halARSetParam(prAdapter, 0, 0, 0, 0);
}

/*----------------------------------------------------------------------------*/
/*!
* \brief Set rate for a specific entry
*
* \param[in] prAdapter      a pointer to adapter private data structure.
* \param[in] u2RateSet      Rateset for ucWlanIdx entry
* \param[in] fgIsShortPreamble  TRUE: the setting apply short preamble,
*                               FALSE: the setting apply long preamble
* \param[in] ucWlanIdx      the index of the wlan table for the setting
*
* \return N/A
*/
/*----------------------------------------------------------------------------*/
VOID
nicARSetRate (
    IN P_ADAPTER_T prAdapter,
    IN UINT_16 u2RateSet,
    IN BOOLEAN fgIsShortPreamble,
    IN UINT_8 ucRate1,
    IN UINT_8 ucWlanIdx,
    IN BOOLEAN fgIsRate1Assigned
    )
{

    UINT_8      i = 0;

    ASSERT(prAdapter);

    if (!fgIsRate1Assigned) {
        for (i= 0; i < RATE_NUM; i++) {
            if (u2RateSet & BIT(i)) {
                if (ucRate1 < i) {
                    ucRate1 = i;
                 }
            }
        }
    }

    halARSetRate(prAdapter, ucWlanIdx, u2RateSet, fgIsShortPreamble, ucRate1);
}

/*----------------------------------------------------------------------------*/
/*!
* \brief Reset autorate function for a specific entry
*
* \param[in]    prAdapter a pointer to adapter private data structure.
* \param[in]    ucWlanIdx the index of wlan table whose autorate function
*               is to be reset
*
* \return N/A
*/
/*----------------------------------------------------------------------------*/
VOID
nicARReset (
    IN P_ADAPTER_T prAdapter,
    IN UINT_8 ucWlanIdx
    )
{
    ASSERT(prAdapter);

    halARReset(prAdapter, ucWlanIdx);
}

/*----------------------------------------------------------------------------*/
/*!
* \brief Set the autorate parameters by the profile
*
* \param[in] prAdapter      a pointer to adapter private data structure.
* \param[in] eARProfile     the pre-defined profile
*
* \return N/A
*/
/*----------------------------------------------------------------------------*/
VOID
nicARSetProfile (
    IN P_ADAPTER_T prAdapter,
    IN ENUM_AUTORATE_PROFILE_T eARProfile
    )
{
    P_AR_CTRL_T     prARCtrl;
    P_AR_PROFILE_T  prAR_Setting;

    ASSERT(prAdapter);
    prARCtrl = &prAdapter->rARCtrl;

    ASSERT(eARProfile < AR_PROFILE_NUM);

    prAR_Setting = (P_AR_PROFILE_T) &arARProfileSetting[eARProfile];
    prARCtrl->prAR_Profile = prAR_Setting;

    if (prARCtrl->eType == AR_HW) {
        halARSetParam(prAdapter, prAR_Setting->u2FailCount_up_limit,
            prAR_Setting->u2FailCount_down_limit, prAR_Setting->ucRCParam,
            prAR_Setting->ucPERParam);
    }

    return;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief Enable protection mode and set the type
*
* \param[in] prAdapter          a pointer to adapter private data structure.
* \param[in] ucProtectionMode   the type of protection mode,
*                               CTS_PROTECTION_TYPE_802_11 or
*                               CTS_PROTECTION_TYPE_PROPRIETARY
*
* \return N/A
*/
/*----------------------------------------------------------------------------*/
VOID
nicRateEnableProtection (
    IN P_ADAPTER_T prAdapter,
    IN UINT_8 ucProtectionMode
    )
{
    P_RATE_INFO_T prRateInfo;


    ASSERT(prAdapter);
    prRateInfo = &prAdapter->rRateInfo;

    prRateInfo->fgCTSProtectionEnabled = TRUE;
    prRateInfo->ucCTSProtectionMode = ucProtectionMode;

    halEnableCTSProtectionMode(prAdapter, ucProtectionMode);

    return;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief Disable protection mode and set the type
*
* \param[in] prAdapter      a pointer to adapter private data structure.
* \para[in]m ucProtectionMode   the type of protection mode,
*                               CTS_PROTECTION_TYPE_802_11 or
*                               CTS_PROTECTION_TYPE_PROPRIETARY
*
* \return N/A
*/
/*----------------------------------------------------------------------------*/
VOID
nicRateDisableProtection (
    IN P_ADAPTER_T prAdapter
    )
{
    P_RATE_INFO_T prRateInfo;

    ASSERT(prAdapter);
    prRateInfo = &prAdapter->rRateInfo;

    halDisableCTSProtectionMode(prAdapter);
    prRateInfo->fgCTSProtectionEnabled = FALSE;
}


/*----------------------------------------------------------------------------*/
/*!
* \brief Set the CTS and RTS Rate
*
* \param[in] prAdapter          a pointer to adapter private data structure.
* \param[in] ucRateIndex        the new CTS/RTS rate
* \param[in] fgIsShortPreamble  indicate to use long or short preamble
*
* \return N/A
*/
/*----------------------------------------------------------------------------*/
VOID
nicRateSetCTSRTSRate (
    IN P_ADAPTER_T prAdapter,
    IN UINT_8 ucRateIndex,
    IN BOOLEAN fgIsShortPreamble
    )
{
    P_RATE_INFO_T prRateInfo;


    ASSERT(prAdapter);
    prRateInfo = &prAdapter->rRateInfo;

    prRateInfo->ucRTSCTSRateIndex = ucRateIndex;
    prRateInfo->fgIsRTSCTSRateShortPreamble = fgIsShortPreamble;
    halSetCTSRTSRate(prAdapter, ucRateIndex, fgIsShortPreamble);

    return;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief Set the Basic Rate
*
* \param[in] prAdapter      a pointer to adapter private data structure.
* \param[in] ucRateIndex    the new basic rate
* \param[in] fgIsShortPreamble  indicate to use long or short preamble
*
* \return N/A
*/
/*----------------------------------------------------------------------------*/
VOID
nicRateSetBasicRate (
    IN P_ADAPTER_T prAdapter,
    IN UINT_8 ucRateIndex,
    IN BOOLEAN fgIsShortPreamble
    )
{
    P_RATE_INFO_T prRateInfo;


    ASSERT(prAdapter);
    prRateInfo = &prAdapter->rRateInfo;

    prRateInfo->fgIsBasicRateShortPreamble = fgIsShortPreamble;
    prRateInfo->ucBasicRateIndex = ucRateIndex;
    halSetBasicRate(prAdapter, ucRateIndex, fgIsShortPreamble);

    return;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief Set the RTS threshold
*
* \param[in] prAdapter      a pointer to adapter private data structure.
* \param[in] u2RTSThreshold New RTS threshold
*
* \return N/A
*/
/*----------------------------------------------------------------------------*/
VOID
nicRateSetRTSThreshold (
    IN P_ADAPTER_T prAdapter,
    IN UINT_16 u2RTSThreshold
    )
{
    P_RATE_INFO_T prRateInfo;


    ASSERT(prAdapter);
    ASSERT(u2RTSThreshold);
    prRateInfo = &prAdapter->rRateInfo;

    prRateInfo->u2RTSThreshold = u2RTSThreshold;
    halSetRTSThreshold(prAdapter, u2RTSThreshold);

    return;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief Set response rate of ack and cts
*
* \param[in] prAdapter          a pointer to adapter private data structure.
* \param[in] aucAckCtsRateIndex array to store response rate inform of each rate
* \param[in] fgIsShortPreamble  short preambel is used or not
*
* \return N/A
*/
/*----------------------------------------------------------------------------*/
VOID
nicRateSetAckCtsRate(
    IN P_ADAPTER_T prAdapter,
    IN UINT_8 aucAckCtsRateIndex[],
    IN BOOLEAN fgIsShortPreamble
    )
{
    P_RATE_INFO_T   prRateInfo;
    UINT_8          i = 0;


    ASSERT(prAdapter);
    ASSERT(aucAckCtsRateIndex);
    prRateInfo = &prAdapter->rRateInfo;

    for (i = 0; i < RATE_NUM; i++) {
        prRateInfo->aucAckCtsRateIndex[i] = aucAckCtsRateIndex[i];
    }
    prRateInfo->fgIsAckCtsRateShortPreamble = fgIsShortPreamble;
    halSetAckCtsRate(prAdapter, aucAckCtsRateIndex, fgIsShortPreamble);

    return;
}


