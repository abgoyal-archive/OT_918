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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/mib.c#1 $
*/

/*! \file   "mib.c"
    \brief  This file includes the mib default vale and functions.
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
** $Log: mib.c $
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\7 2008-08-15 19:35:13 GMT mtk01088
**  remove the doxygen style for structure, and add assert for function
**  \main\maintrunk.MT5921\6 2008-06-12 20:30:09 GMT mtk01461
**  Update comments
**  \main\maintrunk.MT5921\5 2008-05-22 19:43:08 GMT MTK01088
**  move the mib to connection setting structure
**  \main\maintrunk.MT5921\4 2008-01-07 15:06:38 GMT mtk01461
**  Add PhyType & AdHocMode Selection Support
** Revision 1.2  2007/07/17 12:56:50  MTK01088
** add mib.c
**
**
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

/* Initial values for the NIC's 802.11 MIB */
static const IEEE_802_11_MIB_T initIeee80211Mib = {

    /* dot11PrivacyTable (dot11smt 5) */
    0,                      /* dot11WEPDefaultKeyID */
    FALSE,                  /* dot11PariwiseKeyAvailable */
    0,                      /* dot11WEPICVErrorCount */
    0,                      /* dot11WEPExcludedCount */

    /*! dot11RSNAConfigTable (dot11smt 8) */
    WPA_CIPHER_SUITE_NONE,      /* dot11RSNAConfigGroupCipher */

    {
        { WPA_CIPHER_SUITE_WEP40,    FALSE },     /* WPA WEP-40         */
        { WPA_CIPHER_SUITE_TKIP,     FALSE },     /* WPA TKIP           */
        { WPA_CIPHER_SUITE_CCMP,     FALSE },     /* WPA CCMP           */
        { WPA_CIPHER_SUITE_WEP104,   FALSE },     /* WPA WEP-104        */
        { RSN_CIPHER_SUITE_WEP40,    FALSE },     /* WPA2 WEP-40        */
        { RSN_CIPHER_SUITE_TKIP,     FALSE },     /* WPA2 TKIP          */
        { RSN_CIPHER_SUITE_CCMP,     FALSE },     /* WPA2 CCMP          */
        { RSN_CIPHER_SUITE_WEP104,   FALSE }      /* WPA2 WEP-104       */
    },

    {
        { WPA_AKM_SUITE_NONE,        FALSE },    /* None        */
        { WPA_AKM_SUITE_802_1X,      FALSE },    /* 802.1X      */
        { WPA_AKM_SUITE_PSK,         FALSE },    /* PSK         */
        { RSN_AKM_SUITE_NONE,        FALSE },    /* None        */
        { RSN_AKM_SUITE_802_1X,      FALSE },    /* 802.1X      */
        { RSN_AKM_SUITE_PSK,         FALSE },    /* PSK         */
    }
};


PHY_ATTRIBUTE_T rPhyAttributes[PHY_TYPE_INDEX_NUM] = {
    {RATE_SET_ERP,          TRUE,           TRUE},  /* For PHY_TYPE_ERP_INDEX(0) */
    {RATE_SET_HR_DSSS,      TRUE,           FALSE}, /* For PHY_TYPE_HR_DSSS_INDEX(1) */
    {RATE_SET_OFDM,         FALSE,          FALSE}, /* For PHY_TYPE_OFDM_INDEX(2) */
};


ADHOC_MODE_ATTRIBUTE_T rAdHocModeAttributes[AD_HOC_MODE_NUM] = {
    {PHY_TYPE_HR_DSSS_INDEX,    BASIC_RATE_SET_HR_DSSS},        /* For AD_HOC_MODE_11B(0) */
    {PHY_TYPE_ERP_INDEX,        BASIC_RATE_SET_HR_DSSS_ERP},    /* For AD_HOC_MODE_MIXED_11BG(1) */
    {PHY_TYPE_ERP_INDEX,        BASIC_RATE_SET_ERP},            /* For AD_HOC_MODE_11G(2) */
    {PHY_TYPE_OFDM_INDEX,       BASIC_RATE_SET_OFDM},           /* For AD_HOC_MODE_11A(3) */
};

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
* \brief This routine is called to initialize all of the IEEE
*        802.11 MIB attributes in the Adapter structure.
*
* \param[in] prAdapter Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
mibInitializeAttributes (
    IN P_ADAPTER_T    prAdapter
    )
{
    ASSERT(prAdapter);
    
    /* Initialize the NIC's IEEE 802.11 MIB */
    kalMemCopy((PVOID)&prAdapter->rConnSettings.rMib,
        (PVOID)&initIeee80211Mib,
        sizeof(IEEE_802_11_MIB_T));

} /* mibInitializeAttributes */


