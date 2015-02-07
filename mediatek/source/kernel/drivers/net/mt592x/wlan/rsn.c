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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/rsn.c#2 $
*/

/*! \file   "rsn.c"
    \brief  This file including the 802.11i, wpa and wpa2(rsn) related function.

    This file provided the macros and functions library support the wpa/rsn ie parsing, 
    cipher and AKM check to help the AP seleced deciding, tkip mic error handler and rsn PMKID support.
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
** $Log: rsn.c $
 *
 * 11 14 2010 enlai.chu
 * [ALPS00135166] [WiFi] Failed to connect with the WAPI_PSK Secured AP when change connection between it and another AP
 * modify position of protocol type for  WAPI auth message.
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\34 2009-08-18 22:56:18 GMT mtk01090
**  Add Linux SDIO (with mmc core) support.
**  Add Linux 2.6.21, 2.6.25, 2.6.26.
**  Fix compile warning in Linux.
**  \main\maintrunk.MT5921\33 2009-07-06 20:34:33 GMT mtk01088
**  adding the code for wpi port control
**  \main\maintrunk.MT5921\32 2009-04-07 20:40:47 GMT mtk01088
**  add the compiling flag for wps support
**  \main\maintrunk.MT5921\31 2009-04-06 16:54:58 GMT mtk01088
**  add the privacy check at AP select policy for WPS authentication
**  \main\maintrunk.MT5921\30 2008-11-28 11:05:53 GMT mtk01088
**  fixed the lint warning
**  \main\maintrunk.MT5921\29 2008-11-19 11:51:23 GMT mtk01088
**  fixed some lint warning, and rename some variable with pre-fix to avoid the misunderstanding
**  \main\maintrunk.MT5921\28 2008-10-30 11:14:38 GMT mtk01088
**  fixed the lint warning message
**  \main\maintrunk.MT5921\27 2008-10-29 11:27:16 GMT mtk01088
**  avoid the assert check error
**  \main\maintrunk.MT5921\26 2008-10-29 10:49:31 GMT mtk01088
**  update code for lint warning
**  \main\maintrunk.MT5921\25 2008-10-27 18:16:44 GMT mtk01088
**  adjust the code for avoid the lint warnning
**  \main\maintrunk.MT5921\24 2008-08-16 11:44:12 GMT mtk01088
**  review the code for stage 1
**  \main\maintrunk.MT5921\23 2008-07-24 20:27:32 GMT mtk01088
**  check the count to avoid buffer over flow
**  \main\maintrunk.MT5921\22 2008-07-07 13:40:57 GMT mtk01461
**  Adding fgBypassPortCtrlForRoaming to skip check outgoing packet during 802.1x handshaking while roaming
**  
**  \main\maintrunk.MT5921\21 2008-07-01 20:33:42 GMT mtk01088
**  adjust the parse ether type as 1x location
**  \main\maintrunk.MT5921\20 2008-06-24 10:26:25 GMT mtk01088
**  add code to check the ether type for 0x888e, while AP use 802.1h, the rfb 1x bit will not set (HEC5988)
**  \main\maintrunk.MT5921\19 2008-06-14 12:14:52 GMT MTK01088
**  fixed the pointer error
**  \main\maintrunk.MT5921\18 2008-06-14 11:32:45 GMT MTK01088
**  Drop non-encrypted packet for non-802.1x frame while auth mode is > WPA
**  \main\maintrunk.MT5921\17 2008-05-22 19:46:03 GMT MTK01088
**  move the mib to connection setting structure
**  \main\maintrunk.MT5921\16 2008-04-30 14:19:18 GMT mtk01088
**  adjust the code for output message
**  \main\maintrunk.MT5921\15 2008-03-19 15:39:29 GMT mtk01088
**  using bssinfo bssid instead of connection setting
**  \main\maintrunk.MT5921\14 2008-03-18 10:06:36 GMT mtk01088
**  modify the pmkid add candidate rule, use the BSS Desc to add to list one by one, not use a list loop at function, also modiy the tab to space
**  \main\maintrunk.MT5921\13 2008-02-29 15:25:42 GMT mtk01088
**  add rsn sw port control tx and rx path function
**  \main\maintrunk.MT5921\12 2008-02-29 13:08:24 GMT mtk01088
**  refine the function name
**  \main\maintrunk.MT5921\11 2008-01-24 12:44:49 GMT mtk01088
**  fixed typo error
**  \main\maintrunk.MT5921\10 2008-01-09 21:05:01 GMT mtk01088
**  let the rsn and wpa cap filed is 0 at assoc request
**  \main\maintrunk.MT5921\9 2008-01-07 15:06:46 GMT mtk01461
**  Add PhyType & AdHocMode Selection Support
**  \main\maintrunk.MT5921\8 2007-12-21 09:17:32 GMT mtk01088
**  \main\maintrunk.MT5921\7 2007-11-20 10:56:14 GMT mtk01088
**  add invlide key path
**  \main\maintrunk.MT5921\6 2007-11-12 15:07:17 GMT mtk01088
**  the rsn cap should stoted to BSS desc
** Revision 1.6  2007/07/17 12:58:56  MTK01088
** adjust the pmkid code
**
** Revision 1.5  2007/07/16 02:44:11  MTK01088
** add code for rsn
**
** Revision 1.4  2007/07/04 12:50:27  MTK01088
** modify the ENUM define
**
** Revision 1.3  2007/07/04 10:16:51  MTK01088
** add {} for if
**
** Revision 1.2  2007/06/27 06:09:25  MTK01088
** add the 802.11i wpa/rsn function api
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

extern PHY_ATTRIBUTE_T rPhyAttributes[];

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
* \brief This routine is called to parse RSN IE.
*
* \param[in]  prInfoElem Pointer to the RSN IE
* \param[out] prRsnInfo Pointer to the BSSDescription structure to store the
**                  RSN information from the given RSN IE
*
* \retval TRUE - Succeeded
* \retval FALSE - Failed
*/
/*----------------------------------------------------------------------------*/
BOOLEAN
rsnParseRsnIE (
    IN  P_RSN_INFO_ELEM_T prInfoElem,
    OUT P_RSN_INFO_T      prRsnInfo
    )
{
    UINT_32               i;
    INT_32                u4RemainRsnIeLen;
    UINT_16               u2Version;
    UINT_16               u2Cap = 0;
    UINT_32               u4GroupSuite = RSN_CIPHER_SUITE_CCMP;
    UINT_16               u2PairSuiteCount= 0;
    UINT_16               u2AuthSuiteCount = 0;
    PUINT_8               pucPairSuite = NULL;
    PUINT_8               pucAuthSuite = NULL;
    PUINT_8               cp;

    DEBUGFUNC("rsnParseRsnIE");

    ASSERT(prInfoElem);
    ASSERT(prRsnInfo);

    /* Verify the length of the RSN IE. */
    if (prInfoElem->ucLength < 2) {
        DBGLOG(RSN, WARN, ("RSN IE length too short (length=%d)\n", prInfoElem->ucLength));
        return FALSE;
    }

    /* Check RSN version: currently, we only support version 1. */
    WLAN_GET_FIELD_16(&prInfoElem->u2Version, &u2Version);
    if (u2Version != 1) {
        DBGLOG(RSN, WARN,("Unsupported RSN IE version: %d\n", u2Version));
        return FALSE;
    }

    cp = (PUCHAR) &prInfoElem->u4GroupKeyCipherSuite;
    u4RemainRsnIeLen = (INT_32) prInfoElem->ucLength - 2;

    do {
        if (u4RemainRsnIeLen == 0) {
            break;
        }

        /* Parse the Group Key Cipher Suite field. */
        if (u4RemainRsnIeLen < 4) {
            DBGLOG(RSN, WARN,("Fail to parse RSN IE in group cipher suite (IE len: %d)\n",
                prInfoElem->ucLength));
            return FALSE;
        }

        WLAN_GET_FIELD_32(cp, &u4GroupSuite);
        cp += 4;
        u4RemainRsnIeLen -= 4;

        if (u4RemainRsnIeLen == 0) {
            break;
        }

        /* Parse the Pairwise Key Cipher Suite Count field. */
        if (u4RemainRsnIeLen < 2) {
            DBGLOG(RSN, WARN,("Fail to parse RSN IE in pairwise cipher suite count (IE len: %d)\n",
                prInfoElem->ucLength));
            return FALSE;
        }

        WLAN_GET_FIELD_16(cp, &u2PairSuiteCount);
        cp += 2;
        u4RemainRsnIeLen -= 2;

        /* Parse the Pairwise Key Cipher Suite List field. */
        i = (UINT_32) u2PairSuiteCount * 4;
        if (u4RemainRsnIeLen < (INT_32) i) {
            DBGLOG(RSN, WARN,("Fail to parse RSN IE in pairwise cipher suite list (IE len: %d)\n",
                prInfoElem->ucLength));
            return FALSE;
        }

        pucPairSuite = cp;

        cp += i;
        u4RemainRsnIeLen -= (INT_32) i;

        if (u4RemainRsnIeLen == 0) {
            break;
        }

        /* Parse the Authentication and Key Management Cipher Suite Count field. */
        if (u4RemainRsnIeLen < 2) {
            DBGLOG(RSN, WARN,("Fail to parse RSN IE in auth & key mgt suite count (IE len: %d)\n",
                prInfoElem->ucLength));
            return FALSE;
        }

        WLAN_GET_FIELD_16(cp, &u2AuthSuiteCount);
        cp += 2;
        u4RemainRsnIeLen -= 2;

        /* Parse the Authentication and Key Management Cipher Suite List
           field. */
        i = (UINT_32) u2AuthSuiteCount * 4;
        if (u4RemainRsnIeLen < (INT_32) i) {
            DBGLOG(RSN, WARN,("Fail to parse RSN IE in auth & key mgt suite list (IE len: %d)\n",
                prInfoElem->ucLength));
            return FALSE;
        }

        pucAuthSuite = cp;

        cp += i;
        u4RemainRsnIeLen -= (INT_32) i;

        if (u4RemainRsnIeLen == 0) {
            break;
        }

        /* Parse the RSN u2Capabilities field. */
        if (u4RemainRsnIeLen < 2) {
            DBGLOG(RSN, WARN,("Fail to parse RSN IE in RSN capabilities (IE len: %d)\n",
                prInfoElem->ucLength));
            return FALSE;
        }

        WLAN_GET_FIELD_16(cp, &u2Cap);
    } while (FALSE);

    /* Save the RSN information for the BSS. */
    prRsnInfo->ucElemId = ELEM_ID_RSN;

    prRsnInfo->u2Version = u2Version;

    prRsnInfo->u4GroupKeyCipherSuite = u4GroupSuite;

    DBGLOG(RSN, INFO,
        ("RSN: version %d, group key cipher suite %02x-%02x-%02x-%02x\n",
        u2Version, (UCHAR) (u4GroupSuite & 0x000000FF),
        (UCHAR) ((u4GroupSuite >> 8) & 0x000000FF),
        (UCHAR) ((u4GroupSuite >> 16) & 0x000000FF),
        (UCHAR) ((u4GroupSuite >> 24) & 0x000000FF)));

    if (pucPairSuite) {
        /* The information about the pairwise key cipher suites is present. */
        if (u2PairSuiteCount > MAX_NUM_SUPPORTED_CIPHER_SUITES) {
            u2PairSuiteCount = MAX_NUM_SUPPORTED_CIPHER_SUITES;
        }

        prRsnInfo->u4PairwiseKeyCipherSuiteCount = (UINT_32) u2PairSuiteCount;

        for (i = 0; i < (UINT_32) u2PairSuiteCount; i++) {
            WLAN_GET_FIELD_32(pucPairSuite,
                &prRsnInfo->au4PairwiseKeyCipherSuite[i]);
            pucPairSuite += 4;

            DBGLOG(RSN, INFO,
                ("RSN: pairwise key cipher suite [%d]: %02x-%02x-%02x-%02x\n",
                (UINT_8)i, (UCHAR) (prRsnInfo->au4PairwiseKeyCipherSuite[i] & 0x000000FF),
                (UCHAR) ((prRsnInfo->au4PairwiseKeyCipherSuite[i] >> 8) & 0x000000FF),
                (UCHAR) ((prRsnInfo->au4PairwiseKeyCipherSuite[i] >> 16) & 0x000000FF),
                (UCHAR) ((prRsnInfo->au4PairwiseKeyCipherSuite[i] >> 24) & 0x000000FF)));
        }
    }
    else {
        /* The information about the pairwise key cipher suites is not present.
           Use the default chipher suite for RSN: CCMP. */
        prRsnInfo->u4PairwiseKeyCipherSuiteCount = 1;
        prRsnInfo->au4PairwiseKeyCipherSuite[0] = RSN_CIPHER_SUITE_CCMP;

        DBGLOG(RSN, INFO,
            ("RSN: pairwise key cipher suite: %02x-%02x-%02x-%02x (default)\n",
            (UCHAR) (prRsnInfo->au4PairwiseKeyCipherSuite[0] & 0x000000FF),
            (UCHAR) ((prRsnInfo->au4PairwiseKeyCipherSuite[0] >> 8) & 0x000000FF),
            (UCHAR) ((prRsnInfo->au4PairwiseKeyCipherSuite[0] >> 16) & 0x000000FF),
            (UCHAR) ((prRsnInfo->au4PairwiseKeyCipherSuite[0] >> 24) & 0x000000FF)));
    }

    if (pucAuthSuite) {
        /* The information about the authentication and key management suites
           is present. */
        if (u2AuthSuiteCount > MAX_NUM_SUPPORTED_AKM_SUITES) {
            u2AuthSuiteCount = MAX_NUM_SUPPORTED_AKM_SUITES;
        }

        prRsnInfo->u4AuthKeyMgtSuiteCount = (UINT_32) u2AuthSuiteCount;

        for (i = 0; i < (UINT_32) u2AuthSuiteCount; i++) {
            WLAN_GET_FIELD_32(pucAuthSuite, &prRsnInfo->au4AuthKeyMgtSuite[i]);
            pucAuthSuite += 4;

            DBGLOG(RSN, INFO,
                ("RSN: AKM suite [%d]: %02x-%02x-%02x-%02x\n",
                (UINT_8)i, (UCHAR) (prRsnInfo->au4AuthKeyMgtSuite[i] & 0x000000FF),
                (UCHAR) ((prRsnInfo->au4AuthKeyMgtSuite[i] >> 8) & 0x000000FF),
                (UCHAR) ((prRsnInfo->au4AuthKeyMgtSuite[i] >> 16) & 0x000000FF),
                (UCHAR) ((prRsnInfo->au4AuthKeyMgtSuite[i] >> 24) & 0x000000FF)));
        }
    }
    else {
        /* The information about the authentication and key management suites
           is not present. Use the default AKM suite for RSN. */
        prRsnInfo->u4AuthKeyMgtSuiteCount = 1;
        prRsnInfo->au4AuthKeyMgtSuite[0] = RSN_AKM_SUITE_802_1X;

        DBGLOG(RSN, INFO,
            ("RSN: AKM suite: %02x-%02x-%02x-%02x (default)\n",
            (UCHAR) (prRsnInfo->au4AuthKeyMgtSuite[0] & 0x000000FF),
            (UCHAR) ((prRsnInfo->au4AuthKeyMgtSuite[0] >> 8) & 0x000000FF),
            (UCHAR) ((prRsnInfo->au4AuthKeyMgtSuite[0] >> 16) & 0x000000FF),
            (UCHAR) ((prRsnInfo->au4AuthKeyMgtSuite[0] >> 24) & 0x000000FF)));
    }

    prRsnInfo->u2RsnCap = u2Cap;

    DBGLOG(RSN, INFO, ("RSN cap: 0x%04x\n", prRsnInfo->u2RsnCap));

    return TRUE;
}   /* rsnParseRsnIE */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to parse WPA IE.
*
* \param[in]  prInfoElem Pointer to the WPA IE.
* \param[out] prWpaInfo Pointer to the BSSDescription structure to store the
*                       WPA information from the given WPA IE.
*
* \retval TRUE Succeeded.
* \retval FALSE Failed.
*/
/*----------------------------------------------------------------------------*/
BOOLEAN
rsnParseWpaIE (
    IN  P_WPA_INFO_ELEM_T prInfoElem,
    OUT P_RSN_INFO_T      prWpaInfo
    )
{
    UINT_32               i;
    INT_32                u4RemainWpaIeLen;
    UINT_16               u2Version;
    UINT_16               u2Cap = 0;
    UINT_32               u4GroupSuite = WPA_CIPHER_SUITE_TKIP;
    UINT_16               u2PairSuiteCount = 0;
    UINT_16               u2AuthSuiteCount = 0;
    PUCHAR                pucPairSuite = NULL;
    PUCHAR                pucAuthSuite = NULL;
    PUCHAR                cp;
    BOOLEAN               fgCapPresent = FALSE;

    DEBUGFUNC("rsnParseWpaIE");

    ASSERT(prInfoElem);
    ASSERT(prWpaInfo);

    /* Verify the length of the WPA IE. */
    if (prInfoElem->ucLength < 6) {
        DBGLOG(RSN, WARN,("WPA IE length too short (length=%d)\n", prInfoElem->ucLength));
        return FALSE;
    }

    /* Check WPA version: currently, we only support version 1. */
    WLAN_GET_FIELD_16(&prInfoElem->u2Version, &u2Version);
    if (u2Version != 1) {
        DBGLOG(RSN, WARN, ("Unsupported WPA IE version: %d\n", u2Version));
        return FALSE;
    }

    cp = (PUCHAR) &prInfoElem->u4GroupKeyCipherSuite;
    u4RemainWpaIeLen = (INT_32) prInfoElem->ucLength - 6;

    do {
        if (u4RemainWpaIeLen == 0) {
            break;
        }

        /* WPA_OUI      : 4
           Version      : 2
           GroupSuite   : 4
           PairwiseCount: 2
           PairwiseSuite: 4 * pairSuiteCount
           AuthCount    : 2
           AuthSuite    : 4 * authSuiteCount
           Cap          : 2 */

        /* Parse the Group Key Cipher Suite field. */
        if (u4RemainWpaIeLen < 4) {
            DBGLOG(RSN, WARN,(
                "Fail to parse WPA IE in group cipher suite (IE len: %d)\n",
                prInfoElem->ucLength));
            return FALSE;
        }

        WLAN_GET_FIELD_32(cp, &u4GroupSuite);
        cp += 4;
        u4RemainWpaIeLen -= 4;

        if (u4RemainWpaIeLen == 0) {
            break;
        }

        /* Parse the Pairwise Key Cipher Suite Count field. */
        if (u4RemainWpaIeLen < 2) {
            DBGLOG(RSN, WARN,(
                "Fail to parse WPA IE in pairwise cipher suite count (IE len: %d)\n",
                prInfoElem->ucLength));
            return FALSE;
        }

        WLAN_GET_FIELD_16(cp, &u2PairSuiteCount);
        cp += 2;
        u4RemainWpaIeLen -= 2;

        /* Parse the Pairwise Key Cipher Suite List field. */
        i = (UINT_32) u2PairSuiteCount * 4;
        if (u4RemainWpaIeLen < (INT_32) i) {
            DBGLOG(RSN, WARN,(
                "Fail to parse WPA IE in pairwise cipher suite list (IE len: %d)\n",
                prInfoElem->ucLength));
            return FALSE;
        }

        pucPairSuite = cp;

        cp += i;
        u4RemainWpaIeLen -= (INT_32) i;

        if (u4RemainWpaIeLen == 0) {
            break;
        }

        /* Parse the Authentication and Key Management Cipher Suite Count
           field. */
        if (u4RemainWpaIeLen < 2) {
            DBGLOG(RSN, WARN,(
                "Fail to parse WPA IE in auth & key mgt suite count (IE len: %d)\n",
                prInfoElem->ucLength));
            return FALSE;
        }

        WLAN_GET_FIELD_16(cp, &u2AuthSuiteCount);
        cp += 2;
        u4RemainWpaIeLen -= 2;

        /* Parse the Authentication and Key Management Cipher Suite List
           field. */
        i = (UINT_32) u2AuthSuiteCount * 4;
        if (u4RemainWpaIeLen < (INT_32) i) {
            DBGLOG(RSN, WARN, (
                "Fail to parse WPA IE in auth & key mgt suite list (IE len: %d)\n",
                prInfoElem->ucLength));
            return FALSE;
        }

        pucAuthSuite = cp;

        cp += i;
        u4RemainWpaIeLen -= (INT_32) i;

        if (u4RemainWpaIeLen == 0) {
            break;
        }

        /* Parse the WPA u2Capabilities field. */
        if (u4RemainWpaIeLen < 2) {
            DBGLOG(RSN, WARN, ("Fail to parse WPA IE in WPA capabilities (IE len: %d)\n",
                prInfoElem->ucLength));
            return FALSE;
        }

        fgCapPresent = TRUE;
        WLAN_GET_FIELD_16(cp, &u2Cap);
        u4RemainWpaIeLen -= 2;
    } while (FALSE);

    /* Save the WPA information for the BSS. */

    prWpaInfo->ucElemId = ELEM_ID_WPA;

    prWpaInfo->u2Version = u2Version;

    prWpaInfo->u4GroupKeyCipherSuite = u4GroupSuite;

    DBGLOG(RSN, LOUD,
        ("WPA: version %d, group key cipher suite %02x-%02x-%02x-%02x\n",
        u2Version, (UCHAR) (u4GroupSuite & 0x000000FF),
        (UCHAR) ((u4GroupSuite >> 8) & 0x000000FF),
        (UCHAR) ((u4GroupSuite >> 16) & 0x000000FF),
        (UCHAR) ((u4GroupSuite >> 24) & 0x000000FF)));

    if (pucPairSuite) {
        /* The information about the pairwise key cipher suites is present. */
        if (u2PairSuiteCount > MAX_NUM_SUPPORTED_CIPHER_SUITES) {
            u2PairSuiteCount = MAX_NUM_SUPPORTED_CIPHER_SUITES;
        }

        prWpaInfo->u4PairwiseKeyCipherSuiteCount = (UINT_32) u2PairSuiteCount;

        for (i = 0; i < (UINT_32) u2PairSuiteCount; i++) {
            WLAN_GET_FIELD_32(pucPairSuite,
                              &prWpaInfo->au4PairwiseKeyCipherSuite[i]);
            pucPairSuite += 4;

            DBGLOG(RSN, LOUD,
                ("WPA: pairwise key cipher suite [%d]: %02x-%02x-%02x-%02x\n",
                (UINT_8)i, (UCHAR) (prWpaInfo->au4PairwiseKeyCipherSuite[i] & 0x000000FF),
                (UCHAR) ((prWpaInfo->au4PairwiseKeyCipherSuite[i] >> 8) & 0x000000FF),
                (UCHAR) ((prWpaInfo->au4PairwiseKeyCipherSuite[i] >> 16) & 0x000000FF),
                (UCHAR) ((prWpaInfo->au4PairwiseKeyCipherSuite[i] >> 24) & 0x000000FF)));
        }
    }
    else {
        /* The information about the pairwise key cipher suites is not present.
           Use the default chipher suite for WPA: TKIP. */
        prWpaInfo->u4PairwiseKeyCipherSuiteCount = 1;
        prWpaInfo->au4PairwiseKeyCipherSuite[0] = WPA_CIPHER_SUITE_TKIP;

        DBGLOG(RSN, LOUD,
            ("WPA: pairwise key cipher suite: %02x-%02x-%02x-%02x (default)\n",
            (UCHAR) (prWpaInfo->au4PairwiseKeyCipherSuite[0] & 0x000000FF),
            (UCHAR) ((prWpaInfo->au4PairwiseKeyCipherSuite[0] >> 8) & 0x000000FF),
            (UCHAR) ((prWpaInfo->au4PairwiseKeyCipherSuite[0] >> 16) & 0x000000FF),
            (UCHAR) ((prWpaInfo->au4PairwiseKeyCipherSuite[0] >> 24) & 0x000000FF)));
    }

    if (pucAuthSuite) {
        /* The information about the authentication and key management suites
           is present. */
        if (u2AuthSuiteCount > MAX_NUM_SUPPORTED_AKM_SUITES) {
            u2AuthSuiteCount = MAX_NUM_SUPPORTED_AKM_SUITES;
        }

        prWpaInfo->u4AuthKeyMgtSuiteCount = (UINT_32) u2AuthSuiteCount;

        for (i = 0; i < (UINT_32) u2AuthSuiteCount; i++) {
            WLAN_GET_FIELD_32(pucAuthSuite, &prWpaInfo->au4AuthKeyMgtSuite[i]);
            pucAuthSuite += 4;

            DBGLOG(RSN, LOUD,
                ("WPA: AKM suite [%d]: %02x-%02x-%02x-%02x\n",
                (UINT_8)i, (UCHAR) (prWpaInfo->au4AuthKeyMgtSuite[i] & 0x000000FF),
                (UCHAR) ((prWpaInfo->au4AuthKeyMgtSuite[i] >> 8) & 0x000000FF),
                (UCHAR) ((prWpaInfo->au4AuthKeyMgtSuite[i] >> 16) & 0x000000FF),
                (UCHAR) ((prWpaInfo->au4AuthKeyMgtSuite[i] >> 24) & 0x000000FF)));
        }
    }
    else {
        /* The information about the authentication and key management suites
           is not present. Use the default AKM suite for WPA. */
        prWpaInfo->u4AuthKeyMgtSuiteCount = 1;
        prWpaInfo->au4AuthKeyMgtSuite[0] = WPA_AKM_SUITE_802_1X;

        DBGLOG(RSN, LOUD,
            ("WPA: AKM suite: %02x-%02x-%02x-%02x (default)\n",
            (UCHAR) (prWpaInfo->au4AuthKeyMgtSuite[0] & 0x000000FF),
            (UCHAR) ((prWpaInfo->au4AuthKeyMgtSuite[0] >> 8) & 0x000000FF),
            (UCHAR) ((prWpaInfo->au4AuthKeyMgtSuite[0] >> 16) & 0x000000FF),
            (UCHAR) ((prWpaInfo->au4AuthKeyMgtSuite[0] >> 24) & 0x000000FF)));
    }

    if (fgCapPresent) {
        prWpaInfo->fgRsnCapPresent = TRUE;
        prWpaInfo->u2RsnCap = u2Cap;
        DBGLOG(RSN, LOUD, ("WPA: RSN cap: 0x%04x\n", prWpaInfo->u2RsnCap));
    }
    else { 
        prWpaInfo->fgRsnCapPresent = FALSE;
        prWpaInfo->u2RsnCap = 0;
    }

    return TRUE;
}   /* rsnParseWpaIE */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to search the desired pairwise
*        cipher suite from the MIB Pairwise Cipher Suite
*        configuration table.
*
* \param[in] prAdapter Pointer to the adapter object data area.
* \param[in] u4Cipher The desired pairwise cipher suite to be searched
* \param[out] pu4Index Pointer to the index of the desired pairwise cipher in
*                      the table
*
* \retval TRUE - The desired pairwise cipher suite is found in the table.
* \retval FALSE - The desired pairwise cipher suite is not found in the
*                 table.
*/
/*----------------------------------------------------------------------------*/
BOOLEAN
rsnSearchSupportedCipher (
    IN  P_ADAPTER_T         prAdapter,
    IN  UINT_32             u4Cipher,
    OUT PUINT_32            pu4Index
    )
{
    UINT_8 i;
    P_DOT11_RSNA_CONFIG_PAIRWISE_CIPHERS_ENTRY prEntry;

    DEBUGFUNC("rsnSearchSupportedCipher");

    ASSERT(prAdapter);
    ASSERT(pu4Index);
    
    for (i = 0; i < MAX_NUM_SUPPORTED_CIPHER_SUITES; i++) {
        prEntry = &prAdapter->rConnSettings.rMib.dot11RSNAConfigPairwiseCiphersTable[i];
        if (prEntry->dot11RSNAConfigPairwiseCipher == u4Cipher &&
            prEntry->dot11RSNAConfigPairwiseCipherEnabled) {
            *pu4Index = i;
            return TRUE;
        }
    }
    return FALSE;
}   /* rsnSearchSupportedCipher */


/*----------------------------------------------------------------------------*/
/*!
*
* \brief This routine is called to search the desired
*        authentication and key management (AKM) suite from the
*        MIB Authentication and Key Management Suites table.
*
* \param[in]  prAdapter  Pointer to the Adapter structure
* \param[in]  u4AkmSuite The desired AKM suite to be searched
* \param[out] pu4Index   Pointer to the index of the desired AKM suite in the
*                        table
*
* \retval TRUE  The desired AKM suite is found in the table.
* \retval FALSE The desired AKM suite is not found in the table.
*
* \note
*/
/*----------------------------------------------------------------------------*/
BOOLEAN
rsnSearchAKMSuite (
    IN  P_ADAPTER_T         prAdapter,
    IN  UINT_32             u4AkmSuite,
    OUT PUINT_32            pu4Index
    )
{
    UINT_8 i;
    P_DOT11_RSNA_CONFIG_AUTHENTICATION_SUITES_ENTRY prEntry;

    DEBUGFUNC("rsnSearchAKMSuite");

    ASSERT(prAdapter);
    ASSERT(pu4Index);
    
    for (i = 0; i < MAX_NUM_SUPPORTED_AKM_SUITES; i++) {
        prEntry = &prAdapter->rConnSettings.rMib.dot11RSNAConfigAuthenticationSuitesTable[i];
        if (prEntry->dot11RSNAConfigAuthenticationSuite == u4AkmSuite &&
            prEntry->dot11RSNAConfigAuthenticationSuiteEnabled) {
            *pu4Index = i;
            return TRUE;
        }
    }
    return FALSE;
}   /* rsnSearchAKMSuite */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to perform RSNA or TSN policy
*        selection for a given BSS.
*
* \param[in]  prAdapter Pointer to the adapter object data area.
* \param[in]  prBss Pointer to the BSS description
*
* \retval TRUE - The RSNA/TSN policy selection for the given BSS is
*                successful. The selected pairwise and group cipher suites
*                are returned in the BSS description.
* \retval FALSE - The RSNA/TSN policy selection for the given BSS is failed.
*                 The driver shall not attempt to join the given BSS.
*
* \note The Encrypt status matched score will save to bss for final ap select.
*/
/*----------------------------------------------------------------------------*/
BOOLEAN
rsnPerformPolicySelection (
    IN  P_ADAPTER_T         prAdapter,
    IN  P_BSS_DESC_T        prBss
    )
{
    UINT_32                 i, j;
    BOOLEAN                 fgSuiteSupported;
    UINT_32                 u4PairwiseCipher = 0;
    UINT_32                 u4GroupCipher = 0;
    UINT_32                 u4AkmSuite = 0;
    RSN_INFO_T              rTmpRsnInfo;
    P_RSN_INFO_T            prBssRsnInfo;

    DEBUGFUNC("rsnPerformPolicySelection");

    ASSERT(prAdapter);
    ASSERT(prBss);
    
    prBss->u4RsnSelectedPairwiseCipher = 0;
    prBss->u4RsnSelectedGroupCipher = 0;
    prBss->u4RsnSelectedAKMSuite = 0;
    prBss->ucEncLevel = 0;

#if SUPPORT_WPS
    /* CR1640, disable the AP select privacy check */
    if ( prAdapter->rSecInfo.fgPrivacyCheckDisable &&
        (prAdapter->rConnSettings.eAuthMode < AUTH_MODE_WPA) &&
        (prAdapter->rConnSettings.eOPMode == NET_TYPE_INFRA)) {
        DBGLOG(RSN, TRACE,("-- Skip the Protected BSS check\n"));
        return TRUE;
    }
#endif
    
    /* Protection is not required in this BSS. */
    if ((prBss->u2CapInfo & CAP_INFO_PRIVACY) == 0 ) {

        if (privacyEnabled(prAdapter) == FALSE) {
            DBGLOG(RSN, TRACE,("-- No Protected BSS\n"));
            return TRUE;
        }
        else {
            DBGLOG(RSN, TRACE,("-- Protected BSS\n"));
            return FALSE;
        }
    }

    /* Protection is required in this BSS. */
    if ((prBss->u2CapInfo & CAP_INFO_PRIVACY) != 0) {
        if (privacyEnabled(prAdapter) == FALSE) {
            DBGLOG(RSN, TRACE,("-- Protected BSS\n"));
            return FALSE;
        }
    }

    if (prAdapter->rConnSettings.eAuthMode == AUTH_MODE_WPA ||
        prAdapter->rConnSettings.eAuthMode == AUTH_MODE_WPA_PSK ||
        prAdapter->rConnSettings.eAuthMode == AUTH_MODE_WPA_NONE) {

        if (prBss->prIEWPA != NULL) {
            if (!rsnParseWpaIE((P_WPA_INFO_ELEM_T)prBss->prIEWPA, &rTmpRsnInfo)) {
                DBGLOG(RSN, INFO, ("-- Policy selection fail for WPA IE .\n"));
                return FALSE;
            }
        }
        else {
            DBGLOG(RSN, INFO, ("WPA Information Element does not exist.\n"));
            return FALSE;
        }
    }
    else if (prAdapter->rConnSettings.eAuthMode == AUTH_MODE_WPA2 ||
        prAdapter->rConnSettings.eAuthMode == AUTH_MODE_WPA2_PSK) {

        if (prBss->prIERSN != NULL) {
            if (!rsnParseRsnIE((P_RSN_INFO_ELEM_T)prBss->prIERSN, &rTmpRsnInfo)) {
                DBGLOG(RSN, TRACE, ("-- Policy selection fail for RSN IE .\n"));
                return FALSE;
            }
        }
        else {
            DBGLOG(RSN, TRACE, ("RSN Information Element does not exist.\n"));
            return FALSE;
        }
    }
    else if (prAdapter->rConnSettings.eEncStatus != ENUM_ENCRYPTION1_ENABLED) {
        /* If the driver is configured to use WEP only, ignore this BSS. */
        DBGLOG(MGT, INFO, ("-- Not WEP-only legacy BSS\n"));
        return FALSE;
    }
    else if (prAdapter->rConnSettings.eEncStatus == ENUM_ENCRYPTION1_ENABLED) {
        /* If the driver is configured to use WEP only, use this BSS. */
        DBGLOG(MGT, INFO, ("-- WEP-only legacy BSS\n"));
        return TRUE;
    }

    prBssRsnInfo = &rTmpRsnInfo;

    if (prBssRsnInfo->u4PairwiseKeyCipherSuiteCount == 1 &&
        GET_SELECTOR_TYPE(prBssRsnInfo->au4PairwiseKeyCipherSuite[0]) ==
        CIPHER_SUITE_NONE) {
        /* Since the pairwise cipher use the same cipher suite as the group
           cipher in the BSS, we check the group cipher suite against the
           current encryption status. */
        fgSuiteSupported = FALSE;

        switch (prBssRsnInfo->u4GroupKeyCipherSuite) {
        case WPA_CIPHER_SUITE_CCMP:
        case RSN_CIPHER_SUITE_CCMP:
             if (prAdapter->rConnSettings.eEncStatus ==
                 ENUM_ENCRYPTION3_ENABLED) {
                 fgSuiteSupported = TRUE;
             }
             break;

        case WPA_CIPHER_SUITE_TKIP:
        case RSN_CIPHER_SUITE_TKIP:
             if (prAdapter->rConnSettings.eEncStatus ==
                 ENUM_ENCRYPTION2_ENABLED) {
                 fgSuiteSupported = TRUE;
             }
             break;

        case WPA_CIPHER_SUITE_WEP40:
        case WPA_CIPHER_SUITE_WEP104:
             if (prAdapter->rConnSettings.eEncStatus ==
                 ENUM_ENCRYPTION1_ENABLED) {
                 fgSuiteSupported = TRUE;
             }
             break;
        }

        if (fgSuiteSupported) {
            u4PairwiseCipher = WPA_CIPHER_SUITE_NONE;
            u4GroupCipher = prBssRsnInfo->u4GroupKeyCipherSuite;
        }
#if DBG
        else {
            DBGLOG(RSN, INFO,
                ("Inproper encryption status %d for group-key-only BSS\n",
                prAdapter->rConnSettings.eEncStatus));
        }
#endif
    }
    else {
        fgSuiteSupported = FALSE;

        /* Select pairwise/group ciphers */
        switch (prAdapter->rConnSettings.eEncStatus)
        {
        case ENUM_ENCRYPTION3_ENABLED:
             for (i = 0; i < prBssRsnInfo->u4PairwiseKeyCipherSuiteCount; i++) {
                 if (GET_SELECTOR_TYPE(prBssRsnInfo->au4PairwiseKeyCipherSuite[i])
                     == CIPHER_SUITE_CCMP) {
                     u4PairwiseCipher = prBssRsnInfo->au4PairwiseKeyCipherSuite[i];
                 }
             }
             u4GroupCipher = prBssRsnInfo->u4GroupKeyCipherSuite;
             break;

        case ENUM_ENCRYPTION2_ENABLED:
             for (i = 0; i < prBssRsnInfo->u4PairwiseKeyCipherSuiteCount; i++) {
                 if (GET_SELECTOR_TYPE(prBssRsnInfo->au4PairwiseKeyCipherSuite[i])
                     == CIPHER_SUITE_TKIP) {
                     u4PairwiseCipher = prBssRsnInfo->au4PairwiseKeyCipherSuite[i];
                 }
             }
             if (GET_SELECTOR_TYPE(prBssRsnInfo->u4GroupKeyCipherSuite) ==
                 CIPHER_SUITE_CCMP) {
                 DBGLOG(RSN, INFO, ("Cannot join CCMP BSS\n"));
             }
             else {
                 u4GroupCipher = prBssRsnInfo->u4GroupKeyCipherSuite;
             }
             break;

        case ENUM_ENCRYPTION1_ENABLED:
             for (i = 0; i < prBssRsnInfo->u4PairwiseKeyCipherSuiteCount; i++) {
                 if (GET_SELECTOR_TYPE(prBssRsnInfo->au4PairwiseKeyCipherSuite[i])
                     == CIPHER_SUITE_WEP40 ||
                     GET_SELECTOR_TYPE(prBssRsnInfo->au4PairwiseKeyCipherSuite[i])
                     == CIPHER_SUITE_WEP104) {
                     u4PairwiseCipher = prBssRsnInfo->au4PairwiseKeyCipherSuite[i];
                 }
             }
             if (GET_SELECTOR_TYPE(prBssRsnInfo->u4GroupKeyCipherSuite) ==
                 CIPHER_SUITE_CCMP ||
                 GET_SELECTOR_TYPE(prBssRsnInfo->u4GroupKeyCipherSuite) ==
                 CIPHER_SUITE_TKIP) {
                 DBGLOG(RSN, INFO, ("Cannot join CCMP/TKIP BSS\n"));
             }
             else {
                 u4GroupCipher = prBssRsnInfo->u4GroupKeyCipherSuite;
             }
             break;

        default:
             break;
        }
    }

    /* Exception handler */
    /* If we cannot find proper pairwise and group cipher suites to join the
       BSS, do not check the supported AKM suites. */
    if (u4PairwiseCipher == 0 || u4GroupCipher == 0) {
        DBGLOG(RSN, INFO,
            ("Failed to select pairwise/group cipher (0x%08lx/0x%08lx)\n",
            u4PairwiseCipher, u4GroupCipher));
        return FALSE;
    }

    /* Verify if selected pairwisse cipher is supported */
    fgSuiteSupported = rsnSearchSupportedCipher(prAdapter, u4PairwiseCipher, &i);

    /* Verify if selected group cipher is supported */
    if (fgSuiteSupported) {
        fgSuiteSupported = rsnSearchSupportedCipher(prAdapter, u4GroupCipher, &i);
    }

    if (!fgSuiteSupported) {
        DBGLOG(RSN, INFO,
            ("Failed to support selected pairwise/group cipher (0x%08lx/0x%08lx)\n",
            u4PairwiseCipher, u4GroupCipher));
        return FALSE;
    }

    /* Select AKM */
    /* If the driver cannot support any authentication suites advertised in
       the given BSS, we fail to perform RSNA policy selection. */
    /* Attempt to find any overlapping supported AKM suite. */
    for (i = 0; i < prBssRsnInfo->u4AuthKeyMgtSuiteCount; i++) {
        if (rsnSearchAKMSuite(prAdapter, prBssRsnInfo->au4AuthKeyMgtSuite[i],
            &j)) {
            u4AkmSuite = prBssRsnInfo->au4AuthKeyMgtSuite[i];
            break;
        }
    }

    if (u4AkmSuite == 0) {
        DBGLOG(RSN, INFO, ("Cannot support any AKM suites\n"));
        return FALSE;
    }

    DBGLOG(RSN, TRACE,
        ("Selected pairwise/group cipher: %02x-%02x-%02x-%02x/%02x-%02x-%02x-%02x\n",
        (UINT_8) (u4PairwiseCipher & 0x000000FF),
        (UINT_8) ((u4PairwiseCipher >> 8) & 0x000000FF),
        (UINT_8) ((u4PairwiseCipher >> 16) & 0x000000FF),
        (UINT_8) ((u4PairwiseCipher >> 24) & 0x000000FF),
        (UINT_8) (u4GroupCipher & 0x000000FF),
        (UINT_8) ((u4GroupCipher >> 8) & 0x000000FF),
        (UINT_8) ((u4GroupCipher >> 16) & 0x000000FF),
        (UINT_8) ((u4GroupCipher >> 24) & 0x000000FF)));

    DBGLOG(RSN, TRACE, ("Selected AKM suite: %02x-%02x-%02x-%02x\n",
        (UINT_8) (u4AkmSuite & 0x000000FF),
        (UINT_8) ((u4AkmSuite >> 8) & 0x000000FF),
        (UINT_8) ((u4AkmSuite >> 16) & 0x000000FF),
        (UINT_8) ((u4AkmSuite >> 24) & 0x000000FF)));

    if (GET_SELECTOR_TYPE(u4GroupCipher) == CIPHER_SUITE_CCMP){
        prBss->ucEncLevel = 3;
    }
    else if (GET_SELECTOR_TYPE(u4GroupCipher) == CIPHER_SUITE_TKIP){
        prBss->ucEncLevel = 2;
    }
    else if (GET_SELECTOR_TYPE(u4GroupCipher) == CIPHER_SUITE_WEP40 ||
        GET_SELECTOR_TYPE(u4GroupCipher) == CIPHER_SUITE_WEP104) {
        prBss->ucEncLevel = 1;
    }
    else {
        ASSERT(FALSE);
    }
    prBss->u4RsnSelectedPairwiseCipher = u4PairwiseCipher;
    prBss->u4RsnSelectedGroupCipher = u4GroupCipher;
    prBss->u4RsnSelectedAKMSuite = u4AkmSuite;

    return TRUE;

}  /* rsnPerformPolicySelection */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to generate WPA IE for beacon frame.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[in] pucIeStartAddr Pointer to put the generated WPA IE.
*
* \return The append WPA-None IE length
* \note
*      Called by: JOIN module, compose beacon IE
*/
/*----------------------------------------------------------------------------*/
UINT_8
rsnGenerateWpaNoneIE (
    IN  P_ADAPTER_T         prAdapter,
    IN  PUINT_8             pucIeStartAddr
    )
{
    UINT_32                 i;
    P_WPA_INFO_ELEM_T       prWpaIE;
    UINT_32                 u4Suite;
    UINT_16                 u2SuiteCount;
    PUINT_8                 cp, cp2;
    UINT_8                  ucExpendedLen = 0;

    DEBUGFUNC("rsnGenerateWpaNoneIE");

    ASSERT(prAdapter);
    ASSERT(pucIeStartAddr);

    if (prAdapter->rConnSettings.eAuthMode != AUTH_MODE_WPA_NONE) {
        return 0;
    }

    prWpaIE = (P_WPA_INFO_ELEM_T)pucIeStartAddr;

    /* Start to construct a WPA IE. */
    /* Fill the Element ID field. */
    prWpaIE->ucElemId = ELEM_ID_WPA;

    /* Fill the OUI and OUI Type fields. */
    prWpaIE->aucOui[0] = 0x00;
    prWpaIE->aucOui[1] = 0x50;
    prWpaIE->aucOui[2] = 0xF2;
    prWpaIE->ucOuiType = VENDOR_OUI_TYPE_WPA;

    /* Fill the Version field. */
    WLAN_SET_FIELD_16(&prWpaIE->u2Version, 1);    /* version 1 */
    ucExpendedLen = 6;

    /* Fill the Pairwise Key Cipher Suite List field. */
    u2SuiteCount = 0;
    cp = (PUINT_8)&prWpaIE->aucPairwiseKeyCipherSuite1[0];

    if (rsnSearchSupportedCipher(prAdapter, WPA_CIPHER_SUITE_CCMP, &i)) {
        u4Suite = WPA_CIPHER_SUITE_CCMP;
    }
    else if (rsnSearchSupportedCipher(prAdapter, WPA_CIPHER_SUITE_TKIP, &i)) {
        u4Suite = WPA_CIPHER_SUITE_TKIP;
    }
    else if (rsnSearchSupportedCipher(prAdapter, WPA_CIPHER_SUITE_WEP104, &i)) {
        u4Suite = WPA_CIPHER_SUITE_WEP104;
    }
    else if (rsnSearchSupportedCipher(prAdapter, WPA_CIPHER_SUITE_WEP40, &i)) {
        u4Suite = WPA_CIPHER_SUITE_WEP40;
    }
    else {
        u4Suite = WPA_CIPHER_SUITE_TKIP;
    }

    WLAN_SET_FIELD_32(cp, u4Suite);
    u2SuiteCount++;
    ucExpendedLen += 4;
    cp += 4;

    /* Fill the Group Key Cipher Suite field as the same in pair-wise key. */
    WLAN_SET_FIELD_32(&prWpaIE->u4GroupKeyCipherSuite, u4Suite);
    ucExpendedLen += 4;


    /* Fill the Pairwise Key Cipher Suite Count field. */
    WLAN_SET_FIELD_16(&prWpaIE->u2PairwiseKeyCipherSuiteCount, u2SuiteCount);
    ucExpendedLen += 2;

    cp2 = cp;

    /* Fill the Authentication and Key Management Suite List field. */
    u2SuiteCount = 0;
    cp += 2;

    if (rsnSearchAKMSuite(prAdapter, WPA_AKM_SUITE_802_1X, &i)) {
        u4Suite = WPA_AKM_SUITE_802_1X;
    }
    else if (rsnSearchAKMSuite(prAdapter, WPA_AKM_SUITE_PSK, &i)) {
        u4Suite = WPA_AKM_SUITE_PSK;
    }
    else {
        u4Suite = WPA_AKM_SUITE_NONE;
    }

    /* This shall be the only avaiable value for current implementation */
    ASSERT(u4Suite == WPA_AKM_SUITE_NONE);

    WLAN_SET_FIELD_32(cp, u4Suite);
    u2SuiteCount++;
    ucExpendedLen += 4;
    cp += 4;

    /* Fill the Authentication and Key Management Suite Count field. */
    WLAN_SET_FIELD_16(cp2, u2SuiteCount);
    ucExpendedLen += 2;

    /* Fill the Length field. */
    prWpaIE->ucLength = (UINT_8)ucExpendedLen;

    /* Increment the total IE length for the Element ID and Length fields. */
    ucExpendedLen += 2;

    return ucExpendedLen;
} /* rsnGenerateWpaNoneIE */


/*----------------------------------------------------------------------------*/
/*!
*
* \brief This routine is called to generate RSN or WPA IE for
*        associate request frame.
*
* \param[in]  prAdapter        Pointer to the Adapter structure
* \param[in]  prCurrentBss     The Selected BSS description
* \param[in]  pucIeStartAddr   Pointer to put the generated RSN or WPA IE
*
* \retval The append RSN or WPA IE length
*
* \note
*      Called by: JOIN module, Associate request
*/
/*----------------------------------------------------------------------------*/
UINT_8
rsnGenerateWPARSNIE (
    IN  P_ADAPTER_T         prAdapter,
    IN  P_BSS_DESC_T        prCurrentBss,
    IN  PUINT_8             pucIeStartAddr
    )
{
    UINT_32                 u4Entry;
    PUCHAR                  cp;
    UINT_8                  ucExpendedLen = 0;

    DEBUGFUNC("rsnGenerateWPARSNIE");

    ASSERT(prAdapter);
    ASSERT(prCurrentBss);
    ASSERT(pucIeStartAddr);
    
    if (privacyRsnKeyHandshakeEnabled(prAdapter))
    {
        if (prCurrentBss->prIERSN &&
            ((prAdapter->rConnSettings.eAuthMode == AUTH_MODE_WPA2) ||
            (prAdapter->rConnSettings.eAuthMode == AUTH_MODE_WPA2_PSK)))
        {
            /* Construct a RSN IE for association request frame. */
            RSN_IE(pucIeStartAddr)->ucElemId = ELEM_ID_RSN;
            RSN_IE(pucIeStartAddr)->ucLength = ELEM_ID_RSN_LEN_FIXED;
            WLAN_SET_FIELD_16(&RSN_IE(pucIeStartAddr)->u2Version, 1); // Version
            WLAN_SET_FIELD_32(&RSN_IE(pucIeStartAddr)->u4GroupKeyCipherSuite,
                prCurrentBss->u4RsnSelectedGroupCipher); // Group key suite
            cp = (PUCHAR) &RSN_IE(pucIeStartAddr)->aucPairwiseKeyCipherSuite1[0];
            WLAN_SET_FIELD_16(&RSN_IE(pucIeStartAddr)->u2PairwiseKeyCipherSuiteCount, 1);
            WLAN_SET_FIELD_32(cp, prCurrentBss->u4RsnSelectedPairwiseCipher);
            cp += 4;
            WLAN_SET_FIELD_16(cp, 1); // AKM suite count
            cp += 2;
            WLAN_SET_FIELD_32(cp, prCurrentBss->u4RsnSelectedAKMSuite); // AKM suite
            cp += 4;
            WLAN_SET_FIELD_16(cp, 0); // Capabilities
            cp += 2;
            if (rsnSearchPmkidEntry(prAdapter, prCurrentBss->aucBSSID, &u4Entry)) {
                if (prAdapter->rSecInfo.arPmkidCache[u4Entry].fgPmkidExist) {
                    RSN_IE(pucIeStartAddr)->ucLength = 38;
                    WLAN_SET_FIELD_16(cp, 1); // PMKID count
                    cp += 2;
                    kalMemCopy(cp, (PVOID)prAdapter->rSecInfo.arPmkidCache[u4Entry].rBssidInfo.arPMKID, 
                        sizeof(PARAM_PMKID_VALUE));
                    ucExpendedLen = 40;
                    pucIeStartAddr += 40;
                }
                else {
                    WLAN_SET_FIELD_16(cp, 0); // PMKID count
                    ucExpendedLen = ELEM_ID_RSN_LEN_FIXED + 2;
                    pucIeStartAddr += ELEM_ID_RSN_LEN_FIXED +2;
                }
            }
            else {
                WLAN_SET_FIELD_16(cp, 0); // PMKID count
                ucExpendedLen = ELEM_ID_RSN_LEN_FIXED + 2;
                pucIeStartAddr += ELEM_ID_RSN_LEN_FIXED +2;
            }
        }
        else if (prCurrentBss->prIEWPA)
        {
            /* Construct a WPA IE for association request frame. */
            WPA_IE(pucIeStartAddr)->ucElemId = ELEM_ID_WPA;
            WPA_IE(pucIeStartAddr)->ucLength = ELEM_ID_WPA_LEN_FIXED;
            WPA_IE(pucIeStartAddr)->aucOui[0] = 0x00;
            WPA_IE(pucIeStartAddr)->aucOui[1] = 0x50;
            WPA_IE(pucIeStartAddr)->aucOui[2] = 0xF2;
            WPA_IE(pucIeStartAddr)->ucOuiType = VENDOR_OUI_TYPE_WPA;
            WLAN_SET_FIELD_16(&WPA_IE(pucIeStartAddr)->u2Version, 1);

            WLAN_SET_FIELD_32(&WPA_IE(pucIeStartAddr)->u4GroupKeyCipherSuite,
                prCurrentBss->u4RsnSelectedGroupCipher);

            cp = (PUCHAR) &WPA_IE(pucIeStartAddr)->aucPairwiseKeyCipherSuite1[0];

            WLAN_SET_FIELD_16(&WPA_IE(pucIeStartAddr)->u2PairwiseKeyCipherSuiteCount, 1);
            WLAN_SET_FIELD_32(cp, prCurrentBss->u4RsnSelectedPairwiseCipher);
            cp += 4;

            WLAN_SET_FIELD_16(cp, 1);
            cp += 2;
            WLAN_SET_FIELD_32(cp, prCurrentBss->u4RsnSelectedAKMSuite);
            cp += 4;

            WPA_IE(pucIeStartAddr)->ucLength = ELEM_ID_WPA_LEN_FIXED;
            ucExpendedLen = ELEM_ID_WPA_LEN_FIXED + 2;
            pucIeStartAddr += ELEM_ID_WPA_LEN_FIXED + 2;
        }
    }
    return ucExpendedLen;
} /* rsnGenerateWPARSNIE */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to generate an authentication event to NDIS.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[in] u4Flags Authentication event: \n
*                     PARAM_AUTH_REQUEST_REAUTH 0x01 \n
*                     PARAM_AUTH_REQUEST_KEYUPDATE 0x02 \n
*                     PARAM_AUTH_REQUEST_PAIRWISE_ERROR 0x06 \n
*                     PARAM_AUTH_REQUEST_GROUP_ERROR 0x0E \n
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
rsnGenerateAuthReqEvent (
    IN P_ADAPTER_T       prAdapter,
    IN BOOLEAN           fgFlags
    )
{
    P_PARAM_AUTH_EVENT_T prAuthEvent;

    DEBUGFUNC("rsnGenerateAuthReqEvent");

    ASSERT(prAdapter);

    prAuthEvent = (P_PARAM_AUTH_EVENT_T)prAdapter->aucIndicationEventBuffer;

    /* Status type: Authentication Event */
    prAuthEvent->rStatus.eStatusType = ENUM_STATUS_TYPE_AUTHENTICATION;

    /* Authentication request */
    prAuthEvent->arRequest[0].u4Length = sizeof(PARAM_AUTH_REQUEST_T);
    kalMemCopy((PVOID)prAuthEvent->arRequest[0].arBssid, (PVOID)prAdapter->rBssInfo.aucBSSID, PARAM_MAC_ADDR_LEN);

    if (fgFlags == TRUE)
        prAuthEvent->arRequest[0].u4Flags = PARAM_AUTH_REQUEST_GROUP_ERROR;
    else
        prAuthEvent->arRequest[0].u4Flags = PARAM_AUTH_REQUEST_PAIRWISE_ERROR;

    kalIndicateStatusAndComplete(prAdapter->prGlueInfo,
        WLAN_STATUS_MEDIA_SPECIFIC_INDICATION,
        (PVOID)prAuthEvent,
        sizeof(PARAM_STATUS_INDICATION_T) + sizeof(PARAM_AUTH_REQUEST_T));

} /* rsnGenerateAuthReqEvent */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to handle The Tx Security process MSDU.
*
* \param[in] prAdapter Pointer to the adapter object data area.
* \param[in] prPacketInfo pointer to the packet info pointer
*
* \retval TRUE Accept the packet
* \retval FALSE Refuse the MSDU packet due port control
*
*/
/*----------------------------------------------------------------------------*/
BOOLEAN
rsnTxProcessMSDU (
    IN P_ADAPTER_T      prAdapter,
    IN P_PACKET_INFO_T  prPacketInfo
    )
{
    P_WLAN_ENTRY_CTRL_T parWlanCtrl = NULL;

    ASSERT(prAdapter);
    ASSERT(prPacketInfo);

    if (prAdapter->rSecInfo.fgBlockOnlyAPTraffic) {
        if (prAdapter->rSecInfo.fgBlockTxTraffic &&
            (prPacketInfo->fgIs1x == FALSE)) {

            if (prAdapter->fgBypassPortCtrlForRoaming) {
                DBGLOG(RSN, TRACE, ("Let non-1x packet bypass the Port Control!\n"));
            }
            else {
                DBGLOG(RSN, TRACE, ("Drop Tx packet due Port Control!\n"));
                return FALSE;
            }
        }
    }
    else {
        UINT_8 ucEntryIndex = WLAN_TABLE_SET_ALL;

        ASSERT(prPacketInfo->pucDestAddr); 
        
        if (nicPrivacyMatchForEntry(prAdapter, prPacketInfo->pucDestAddr, 0, &ucEntryIndex)) {
            if (ucEntryIndex < WLAN_TABLE_SIZE) {
                parWlanCtrl = &prAdapter->arWlanCtrl[ucEntryIndex];
                ASSERT(parWlanCtrl);
                if (parWlanCtrl->rCtrl.fgT1X &&
                    (prPacketInfo->fgIs1x == FALSE)) {
                    DBGLOG(RSN, TRACE, ("Drop Tx packet due Port Control!\n"));
                    return FALSE;
                }
            }
            else {
                ASSERT(0);
            }
        }
        else {
        }
    }

    return TRUE;
}


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to handle The Rx Security process MSDU.
*
* \param[in] adapter_p Pointer to the adapter object data area.
* \param[in] prSWRfb SW rfb pinter
*
* \retval TRUE Accept the packet
* \retval FALSE Refuse the MSDU packet due port control
*/
/*----------------------------------------------------------------------------*/
BOOLEAN
rsnRxProcessMSDU (
    IN P_ADAPTER_T prAdapter,
    IN P_SW_RFB_T  prSWRfb
    )
{

    ASSERT(prAdapter);
    ASSERT(prSWRfb);

    #if CFG_WORKAROUND_HEC_5988
    if (prSWRfb->fgIsDataFrame &&
        !RX_STATUS_IS_1X(prSWRfb->prRxStatus->u2StatusFlag)) {
        PUINT_8 pucOffset_ethertype;
        pucOffset_ethertype = (PUINT_8)prSWRfb->pvHeader;
        if ((pucOffset_ethertype[12] == (UINT_8)(ETH_P_1X >> 8)) &&
            (pucOffset_ethertype[13] == (UINT_8)(ETH_P_1X))) {
            prSWRfb->prRxStatus->u2StatusFlag |= RX_STATUS_FLAG_1X;
        }
    }
    #endif

    #if SUPPORT_WAPI
    if (prAdapter->fgUseWapi && prSWRfb->fgIsDataFrame) {
        PUINT_8 pucOffset_ethertype;
        pucOffset_ethertype = (PUINT_8)prSWRfb->pvHeader;
        if ((pucOffset_ethertype[12] == (UINT_8)(ETH_WPI_1X >> 8)) &&
            (pucOffset_ethertype[13] == (UINT_8)(ETH_WPI_1X))) {
            prSWRfb->prRxStatus->u2StatusFlag |= RX_STATUS_FLAG_1X;
        }
        else {
            if (prAdapter->rSecInfo.fgBlockRxTraffic) {
                DBGLOG(WAPI, WARN, ("WPI Drop rcv data due port control !\r\n"));
                DBGLOG_MEM8(WAPI, TRACE, (PUINT_8)prSWRfb->pvBody, 14);
                return FALSE;
            }
        }
    }
    #endif

     /* Drop received non-encrypted non-802.1x data packet for auth mode > wpa, 
        not handle open and shared key mode, issue shared key for only mgmt */
    if (prSWRfb->fgIsDataFrame &&
        (prAdapter->rConnSettings.eAuthMode >= AUTH_MODE_WPA) && 
        !RX_STATUS_IS_1X(prSWRfb->prRxStatus->u2StatusFlag)) {

        if (!RX_STATUS_IS_PROTECT(prSWRfb->prRxStatus)) {
            DBGLOG(RSN, WARN, ("Drop rcv non-encrypted data frame!\n"));
            return FALSE;
        }
    }

    if (prAdapter->rSecInfo.fgBlockOnlyAPTraffic) {
        if (prAdapter->rSecInfo.fgBlockRxTraffic &&
            !RX_STATUS_IS_1X(prSWRfb->prRxStatus->u2StatusFlag)) {
            DBGLOG(RSN, TRACE, ("Drop Rx packet due Port Control!\n"));
            return FALSE;
        }
    }
    else {
        UINT_8 ucEntryIndex;
        
        if (nicPrivacyMatchForEntry(prAdapter, prSWRfb->prRxStatus->aucTA, 0, &ucEntryIndex)) {
            if (ucEntryIndex < WLAN_TABLE_SIZE) {
                if (prAdapter->arWlanCtrl[ucEntryIndex].rCtrl.fgR1X && 
                    !RX_STATUS_IS_1X(prSWRfb->prRxStatus->u2StatusFlag)) {
                    DBGLOG(RSN, TRACE, ("Drop Rx packet due Port Control!\n"));
                    return FALSE;
                }
            }
            else {
                return TRUE;
            }
        }
    }
    
    return TRUE;
}


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to handle TKIP MIC failures.
*
* \param[in] adapter_p Pointer to the adapter object data area.
* \param[in] fgErrorKeyType type of error key
*
* \retval none
*/
/*----------------------------------------------------------------------------*/
VOID
rsnTkipHandleMICFailure (
    IN  P_ADAPTER_T         prAdapter,
    IN  BOOLEAN             fgErrorKeyType
    )
{
    UINT_32                 u4RsnaCurrentMICFailTime;

    DEBUGFUNC("rsnTkipHandleMICFailure");

    ASSERT(prAdapter);
    
    /* Record the MIC error occur time. */
    GET_CURRENT_SYSTIME(&u4RsnaCurrentMICFailTime);

    /* Generate authentication request event. */
    DBGLOG(RSN, LOUD, ("Generate TKIP MIC error event (type: 0%d)\n",
        fgErrorKeyType));

    /* If less than 60 seconds have passed since a previous TKIP MIC failure,
       disassociate from the AP and wait for 60 seconds before (re)associating
       with the same AP. */
    if (prAdapter->rSecInfo.u4RsnaLastMICFailTime != 0 && !CHECK_FOR_TIMEOUT(u4RsnaCurrentMICFailTime,
            prAdapter->rSecInfo.u4RsnaLastMICFailTime, SEC_TO_SYSTIME(TKIP_COUNTERMEASURE_SEC))) {
        /* If less than 60 seconds expired since last MIC error, we have to
           block traffic. */
        if (nicPrivacyInvalidKey(prAdapter, prAdapter->rBssInfo.aucBSSID) == FALSE) {
            DBGLOG(RSN, TRACE, ("Invalid key fail!!\n"));
        }

        DBGLOG(RSN, INFO, ("Start blocking traffic!\n"));
        rsnGenerateAuthReqEvent(prAdapter, fgErrorKeyType);

        secFsmRunEventStartCounterMeasure(prAdapter);
    }
    else {
        rsnGenerateAuthReqEvent(prAdapter, fgErrorKeyType);
        DBGLOG(RSN, WARN, ("First TKIP MIC error!\n"));
    }

    COPY_SYSTIME(prAdapter->rSecInfo.u4RsnaLastMICFailTime, u4RsnaCurrentMICFailTime);
}   /* rsnTkipHandleMICFailure */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function is called to select a list of BSSID from
*        the scan results for PMKID candidate list.
*
* \param[in] prAdapter Pointer to the adapter object data area.
* \param[in] prBssDesc the BSS Desc at scan result list
* \param[out] pu4CandidateCount Pointer to the number of selected candidates.
*                         It is set to zero if no BSSID matches our requirement.
*
* \retval none
*/
/*----------------------------------------------------------------------------*/
VOID
rsnSelectPmkidCandidateList (
    IN P_ADAPTER_T             prAdapter,
    IN P_BSS_DESC_T            prBssDesc
    )
{
    P_CONNECTION_SETTINGS_T    prConnSettings;
    P_BSS_INFO_T               prBssInfo;

    DEBUGFUNC("rsnSelectPmkidCandidateList");

    ASSERT(prAdapter);
    ASSERT(prBssDesc);

    prConnSettings = &prAdapter->rConnSettings;
    prBssInfo = &prAdapter->rBssInfo;

    ASSERT(prConnSettings);
    ASSERT(prBssDesc);

    /* Search a BSS with the same SSID from the given BSS description set. */
    DBGLOG(RSN, TRACE, ("Check scan result ["MACSTR"]\n",
        MAC2STR(prBssDesc->aucBSSID)));

    if (UNEQUAL_SSID(prBssDesc->aucSSID, prBssDesc->ucSSIDLen,
                   prConnSettings->aucSSID, prConnSettings->ucSSIDLen)) {
        DBGLOG(RSN, TRACE, ("-- SSID not matched\n"));
        return;
    }

    if ((prBssDesc->u2BSSBasicRateSet &
         ~(rPhyAttributes[prBssInfo->ePhyType].u2SupportedRateSet)) ||
        prBssDesc->fgIsUnknownBssBasicRate) {
        DBGLOG(RSN, TRACE, ("-- Rate set not matched\n"));
        return;
    }

    if (prBssDesc->u4RsnSelectedPairwiseCipher != prAdapter->rBssInfo.u4RsnSelectedPairwiseCipher ||
        prBssDesc->u4RsnSelectedGroupCipher != prAdapter->rBssInfo.u4RsnSelectedGroupCipher ||
        prBssDesc->u4RsnSelectedAKMSuite != prAdapter->rBssInfo.u4RsnSelectedAKMSuite) {
        DBGLOG(RSN, TRACE, ("-- Encrypt status not matched\n"));
        return;
    }

    rsnUpdatePmkidCandidateList(prAdapter, prBssDesc);

}   /* rsnSelectPmkidCandidateList */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function is called to select a list of BSSID from
*        the scan results for PMKID candidate list.
*
* \param[in] prAdapter Pointer to the adapter object data area.
* \param[in] prBssDesc the BSS DESC at scan result list
*
* \retval none
*/
/*----------------------------------------------------------------------------*/
VOID
rsnUpdatePmkidCandidateList (
    IN P_ADAPTER_T             prAdapter,
    IN P_BSS_DESC_T            prBssDesc
    )
{
    UINT_32                    i;
    P_CONNECTION_SETTINGS_T    prConnSettings;
    
    DEBUGFUNC("rsnUpdatePmkidCandidateList");

    ASSERT(prAdapter);
    ASSERT(prBssDesc);

    prConnSettings = &prAdapter->rConnSettings;
    ASSERT(prConnSettings);
    
    if (UNEQUAL_SSID(prBssDesc->aucSSID, prBssDesc->ucSSIDLen,
                   prConnSettings->aucSSID, prConnSettings->ucSSIDLen)) {
        DBGLOG(RSN, TRACE, ("-- SSID not matched\n"));
        return;
    }

    for (i = 0; i < CFG_MAX_PMKID_CACHE; i++) {
        if (EQUAL_MAC_ADDR(prBssDesc->aucBSSID, prAdapter->rSecInfo.arPmkidCandicate[i].arBssid))
            return;
    }

    /* If the number of selected BSSID exceed MAX_NUM_PMKID_CACHE(16),
       then we only store MAX_NUM_PMKID_CACHE(16) in PMKID cache */
    if ((prAdapter->rSecInfo.u4PmkidCandicateCount + 1)  > CFG_MAX_PMKID_CACHE) {
        prAdapter->rSecInfo.u4PmkidCandicateCount --;
    }

    i = prAdapter->rSecInfo.u4PmkidCandicateCount;

    COPY_MAC_ADDR((PVOID)prAdapter->rSecInfo.arPmkidCandicate[i].arBssid, 
        (PVOID)prBssDesc->aucBSSID);

    if (prBssDesc->u2RsnCap & MASK_RSNIE_CAP_PREAUTH) {
        prAdapter->rSecInfo.arPmkidCandicate[i].u4PreAuthFlags = 1;
        DBGLOG(RSN, TRACE, ("Add " MACSTR " with pre-auth to candidate list\n",
            MAC2STR(prAdapter->rSecInfo.arPmkidCandicate[i].arBssid)));
    }
    else {
        prAdapter->rSecInfo.arPmkidCandicate[i].u4PreAuthFlags = 0;
        DBGLOG(RSN, TRACE, ("Add " MACSTR " without pre-auth to candidate list\n",
            MAC2STR(prAdapter->rSecInfo.arPmkidCandicate[i].arBssid)));
    }

    prAdapter->rSecInfo.u4PmkidCandicateCount ++;

}   /* rsnUpdatePmkidCandidateList */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to search the desired entry in
*        PMKID cache according to the BSSID
*
* \param[in] prAdapter Pointer to the adapter object data area.
* \param[in] pucBssid Pointer to the BSSID
* \param[out] pu4EntryIndex Pointer to place the found entry index
*
* \retval TRUE, if found one entry for specified BSSID
* \retval FALSE, if not found
*/
/*----------------------------------------------------------------------------*/
BOOLEAN
rsnSearchPmkidEntry (
    IN P_ADAPTER_T             prAdapter,
    IN PUINT_8                 pucBssid,
    OUT PUINT_32               pu4EntryIndex
    )
{
    UINT_32 i;

    DEBUGFUNC("rsnSearchPmkidEntry");

    ASSERT(prAdapter);
    ASSERT(pucBssid);
    ASSERT(pu4EntryIndex);

    if (prAdapter->rSecInfo.u4PmkidCacheCount > CFG_MAX_PMKID_CACHE) {
        return FALSE;
    }
    
    ASSERT(prAdapter->rSecInfo.u4PmkidCacheCount <= CFG_MAX_PMKID_CACHE);
 
    /* Search for desired BSSID */
    for (i = 0; i < prAdapter->rSecInfo.u4PmkidCacheCount; i++) {
        if (!kalMemCmp(prAdapter->rSecInfo.arPmkidCache[i].rBssidInfo.arBSSID, pucBssid,
            sizeof(PARAM_MAC_ADDRESS))) {
            break;
        }
    }

    /* If desired BSSID is found, then set the PMKID */
    if (i < prAdapter->rSecInfo.u4PmkidCacheCount) {
        *pu4EntryIndex = i;

        return TRUE;
    }

    return FALSE;
}   /* rsnSearchPmkidEntry */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to check if there is difference
*        between PMKID candicate list and PMKID cache. If there
*        is new candicate that no cache entry is available, then
*        add a new entry for the new candicate in the PMKID cache
*        and set the PMKID indication flag to TRUE.
*
* \param[in] prAdapter Pointer to the adapter object data area.
*
* \retval TRUE, if new member in the PMKID candicate list
* \retval FALSe, if no new member in the PMKID candicate list
*/
/*----------------------------------------------------------------------------*/
BOOLEAN
rsnCheckPmkidCandicate (
    IN P_ADAPTER_T             prAdapter
   )
{
    UINT_32                    i; // Index for PMKID candicate
    UINT_32                    j; // Indix for PMKID cache
    BOOLEAN                    status = FALSE;

    DEBUGFUNC("rsnCheckPmkidCandicate");

    ASSERT(prAdapter);

    /* Check for each candicate */
    for (i = 0; i < prAdapter->rSecInfo.u4PmkidCandicateCount; i++) {
        for (j = 0; j < prAdapter->rSecInfo.u4PmkidCacheCount; j++) {
            if (!kalMemCmp(prAdapter->rSecInfo.arPmkidCache[j].rBssidInfo.arBSSID,
                    prAdapter->rSecInfo.arPmkidCandicate[i].arBssid,
                    PARAM_MAC_ADDR_LEN)) {
                break;
            }
        }

        /* No entry found in PMKID cache for the candicate, add new one */
        if (j == prAdapter->rSecInfo.u4PmkidCacheCount && prAdapter->rSecInfo.u4PmkidCacheCount < CFG_MAX_PMKID_CACHE) {
            kalMemCopy((PVOID)prAdapter->rSecInfo.arPmkidCache[prAdapter->rSecInfo.u4PmkidCacheCount].rBssidInfo.arBSSID,
                (PVOID)prAdapter->rSecInfo.arPmkidCandicate[i].arBssid,
                PARAM_MAC_ADDR_LEN);
            prAdapter->rSecInfo.arPmkidCache[prAdapter->rSecInfo.u4PmkidCacheCount].fgPmkidExist = FALSE;
            prAdapter->rSecInfo.u4PmkidCacheCount++;

            status = TRUE;
        }
    }

    return status;
} /* rsnCheckPmkidCandicate */



/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to check the BSS Desc at scan result 
*             with pre-auth cap at wpa2 mode. If there
*             is candicate that no cache entry is available, then
*             add a new entry for the new candicate in the PMKID cache
*             and set the PMKID indication flag to TRUE.
*
* \param[in] prAdapter Pointer to the adapter object data area.
* \param[in] prBss The BSS Desc at scan result
*
* \return none
*/
/*----------------------------------------------------------------------------*/
VOID
rsnCheckPmkidCache (
    IN P_ADAPTER_T          prAdapter,
    IN P_BSS_DESC_T         prBss
    )
{
    P_SEC_INFO_T            prSecInfo;
    DEBUGFUNC("rsnCheckPmkidCandicate");

    ASSERT(prAdapter);
    ASSERT(prBss);
    
    prSecInfo = &prAdapter->rSecInfo;

    ASSERT(prSecInfo);
    
    if ((prAdapter->eConnectionState == MEDIA_STATE_CONNECTED) &&
       (prAdapter->rConnSettings.eAuthMode == AUTH_MODE_WPA2)) {
        rsnSelectPmkidCandidateList(prAdapter, prBss);

        if (prSecInfo->u4PmkidCandicateCount && 
            (prSecInfo->fgIndicatePMKID == FALSE)) {
            /* Set indication flag of PMKID to TRUE, and then connHandleNetworkConnection()
               will indicate this later */
            prSecInfo->fgIndicatePMKID = rsnCheckPmkidCandicate(prAdapter);
            if (prSecInfo->fgIndicatePMKID) {
                if (!prSecInfo->arPmkidCache[prAdapter->rSecInfo.u4PmkidCacheCount].fgPmkidExist){
                    DBGLOG(RSN, WARN, ("Prepare a timer to indicate candidate "MACSTR"\n",
                        MAC2STR(prAdapter->rSecInfo.arPmkidCache[prAdapter->rSecInfo.u4PmkidCacheCount].rBssidInfo.arBSSID)));
                    prAdapter->rSecInfo.fgIndicatePMKID = TRUE;
                    ARB_CANCEL_TIMER(prAdapter, prSecInfo->rPreauthenticationTimer);
                    ARB_SET_TIMER(prAdapter,
                            prSecInfo->rPreauthenticationTimer,
                            SEC_TO_MSEC(WAIT_TIME_IND_PMKID_CANDICATE_SEC));
                }
            }
        }
    }
}
    

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to generate an PMKID candidate list
*        indication to NDIS.
*
* \param[in] prAdapter Pointer to the adapter object data area.
* \param[in] u4Flags PMKID candidate list event:
*                    PARAM_PMKID_CANDIDATE_PREAUTH_ENABLED 0x01
*
* \retval none
*/
/*----------------------------------------------------------------------------*/
VOID
rsnGeneratePmkidIndication (
    IN P_ADAPTER_T                 prAdapter,
    IN UINT_32                     u4Flags
    )
{
    P_PARAM_STATUS_INDICATION_T    prStatusEvent;
    P_PARAM_PMKID_CANDIDATE_LIST_T prPmkidEvent;
    UINT_8                         i, j = 0, count = 0;
    UINT_32                        u4LenOfUsedBuffer;
    P_SEC_INFO_T                   prSecInfo = NULL;

    DEBUGFUNC("rsnGeneratePmkidIndication");

    ASSERT(prAdapter);

    prStatusEvent =
        (P_PARAM_STATUS_INDICATION_T)prAdapter->aucIndicationEventBuffer;

    /* Status type: PMKID Candidatelist Event */
    prStatusEvent->eStatusType = ENUM_STATUS_TYPE_CANDIDATE_LIST;
    ASSERT(prStatusEvent);

    prPmkidEvent = (P_PARAM_PMKID_CANDIDATE_LIST_T)(&prStatusEvent->eStatusType + 1);
    ASSERT(prPmkidEvent);

    prSecInfo = &prAdapter->rSecInfo;
    ASSERT(prSecInfo);

    for (i = 0; i < prSecInfo->u4PmkidCandicateCount; i++) {
        for (j = 0; j < prSecInfo->u4PmkidCacheCount; j++) {
            if (EQUAL_MAC_ADDR( prSecInfo->arPmkidCache[j].rBssidInfo.arBSSID, 
                prSecInfo->arPmkidCandicate[i].arBssid) &&
                (prSecInfo->arPmkidCache[j].fgPmkidExist == TRUE)){
                break;
            }
        }
        if (count >= CFG_MAX_PMKID_CACHE) {
            break;
        }

        if (j == prSecInfo->u4PmkidCacheCount) {
            kalMemCopy((PVOID)prPmkidEvent->arCandidateList[count].arBSSID,
                (PVOID)prSecInfo->arPmkidCandicate[i].arBssid,
                PARAM_MAC_ADDR_LEN);
            prPmkidEvent->arCandidateList[count].u4Flags =
                prSecInfo->arPmkidCandicate[i].u4PreAuthFlags;
            count++;
        }
    }

    /* PMKID Candidate List */
    prPmkidEvent->u4Version = 1;
    prPmkidEvent->u4NumCandidates = count;

    u4LenOfUsedBuffer = sizeof(ENUM_STATUS_TYPE_T) + (2 * sizeof(UINT_32)) +
        (count * sizeof(PARAM_PMKID_CANDIDATE_LIST_T));

    kalIndicateStatusAndComplete(prAdapter->prGlueInfo,
        WLAN_STATUS_MEDIA_SPECIFIC_INDICATION,
        (PVOID) prAdapter->aucIndicationEventBuffer,
        u4LenOfUsedBuffer);

}   /* rsnGeneratePmkidIndication */

