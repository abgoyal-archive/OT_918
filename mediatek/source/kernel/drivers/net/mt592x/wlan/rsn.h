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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/rsn.h#1 $
*/

/*! \file   rsn.h
    \brief  The wpa/rsn related define, macro and structure are described here.
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
** $Log: rsn.h $
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\11 2008-10-22 10:56:46 GMT mtk01461
**  Update for lint diagnosis support
**  \main\maintrunk.MT5921\10 2008-08-16 11:40:34 GMT mtk01088
**  \main\maintrunk.MT5921\9 2008-05-28 14:44:32 GMT mtk01088
**  adjust the type of input parameter
**  \main\maintrunk.MT5921\8 2008-03-18 09:50:16 GMT mtk01088
**  Add function declaration for pmkid candidate and cache
**  \main\maintrunk.MT5921\7 2008-02-29 15:08:02 GMT mtk01088
**  add rsn function for tx and rx path
** Revision 1.3  2007/07/17 12:52:59  MTK01088
** add define for pre-auth
**
** Revision 1.2  2007/06/27 06:20:01  MTK01088
** initialize the rsn define
**
**
*/

#ifndef _RSN_H
#define _RSN_H

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
/* ----- Definitions for Cipher Suite Selectors ----- */
#define RSN_CIPHER_SUITE_USE_GROUP_KEY  0x00AC0F00
#define RSN_CIPHER_SUITE_WEP40          0x01AC0F00
#define RSN_CIPHER_SUITE_TKIP           0x02AC0F00
#define RSN_CIPHER_SUITE_CCMP           0x04AC0F00
#define RSN_CIPHER_SUITE_WEP104         0x05AC0F00

#define WPA_CIPHER_SUITE_NONE           0x00F25000
#define WPA_CIPHER_SUITE_WEP40          0x01F25000
#define WPA_CIPHER_SUITE_TKIP           0x02F25000
#define WPA_CIPHER_SUITE_CCMP           0x04F25000
#define WPA_CIPHER_SUITE_WEP104         0x05F25000

/* ----- Definitions for Authentication and Key Management Suite Selectors ----- */
#define RSN_AKM_SUITE_NONE              0x00AC0F00
#define RSN_AKM_SUITE_802_1X            0x01AC0F00
#define RSN_AKM_SUITE_PSK               0x02AC0F00

#define WPA_AKM_SUITE_NONE              0x00F25000
#define WPA_AKM_SUITE_802_1X            0x01F25000
#define WPA_AKM_SUITE_PSK               0x02F25000

#define ELEM_ID_RSN_LEN_FIXED           20  /* The RSN IE len for associate request */

#define ELEM_ID_WPA_LEN_FIXED           22  /* The RSN IE len for associate request */

#define MASK_RSNIE_CAP_PREAUTH          BIT(0)

#define GET_SELECTOR_TYPE(x)           ((UINT_8)(((x) >> 24) & 0x000000FF))
#define SET_SELECTOR_TYPE(x, y)         x = (((x) & 0x00FFFFFF) | (((UINT_32)(y) << 24) & 0xFF000000))

/* Cihpher suite flags */
#define CIPHER_FLAG_NONE                        0x00000000
#define CIPHER_FLAG_WEP40                       0x00000001 /* BIT 1 */
#define CIPHER_FLAG_TKIP                        0x00000002 /* BIT 2 */
#define CIPHER_FLAG_CCMP                        0x00000008 /* BIT 4 */
#define CIPHER_FLAG_WEP104                      0x00000010 /* BIT 5 */
#define CIPHER_FLAG_WEP128                      0x00000020 /* BIT 6 */

#define WAIT_TIME_IND_PMKID_CANDICATE_SEC       10 /* seconds */
#define TKIP_COUNTERMEASURE_SEC                 60 /* seconds */

/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/
/* Structure of RSN Information */
typedef struct _RSN_INFO_T {
    UINT_8          ucElemId;
    UINT_16         u2Version;
    UINT_32         u4GroupKeyCipherSuite;
    UINT_32         u4PairwiseKeyCipherSuiteCount;
    UINT_32         au4PairwiseKeyCipherSuite[MAX_NUM_SUPPORTED_CIPHER_SUITES];
    UINT_32         u4AuthKeyMgtSuiteCount;
    UINT_32         au4AuthKeyMgtSuite[MAX_NUM_SUPPORTED_CIPHER_SUITES];
    UINT_16         u2RsnCap;
    BOOLEAN         fgRsnCapPresent;
} RSN_INFO_T, *P_RSN_INFO_T;

/* RSN Information element format */
typedef struct _RSN_INFO_ELEM_T {
    UCHAR           ucElemId;
    UCHAR           ucLength;
    UINT_16         u2Version;
    UINT_32         u4GroupKeyCipherSuite;
    UINT_16         u2PairwiseKeyCipherSuiteCount;
    UCHAR           aucPairwiseKeyCipherSuite1[4];
} RSN_INFO_ELEM_T, *P_RSN_INFO_ELEM_T;

/* WPA Information element format */
typedef struct _WPA_INFO_ELEM_T {
    UCHAR       ucElemId;
    UCHAR       ucLength;
    UCHAR       aucOui[3];
    UCHAR       ucOuiType;
    UINT_16     u2Version;
    UINT_32     u4GroupKeyCipherSuite;
    UINT_16     u2PairwiseKeyCipherSuiteCount;
    UCHAR       aucPairwiseKeyCipherSuite1[4];
} WPA_INFO_ELEM_T, *P_WPA_INFO_ELEM_T;

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
#define RSN_IE(fp)              ((P_RSN_INFO_ELEM_T) fp)
#define WPA_IE(fp)              ((P_WPA_INFO_ELEM_T) fp)


/*******************************************************************************
*                  F U N C T I O N   D E C L A R A T I O N S
********************************************************************************
*/
BOOLEAN
rsnRxProcessMSDU(
    IN P_ADAPTER_T          prAdapter,
    IN P_SW_RFB_T           prSWRfb
    );

BOOLEAN
rsnTxProcessMSDU(
    IN P_ADAPTER_T          prAdapter,
    IN P_PACKET_INFO_T      prPacketInfo
    );

BOOLEAN
rsnParseRsnIE(
    IN  P_RSN_INFO_ELEM_T   prInfoElem,
    OUT P_RSN_INFO_T        prRsnInfo
    );

BOOLEAN
rsnParseWpaIE(
    IN  P_WPA_INFO_ELEM_T   prInfoElem,
    OUT P_RSN_INFO_T        prWpaInfo
    );

BOOLEAN
rsnSearchSupportedCipher(
    IN  P_ADAPTER_T         prAdapter,
    IN  UINT_32             u4Cipher,
    OUT PUINT_32            pu4Index
    );

BOOLEAN
rsnSearchAKMSuite(
    IN  P_ADAPTER_T         prAdapter,
    IN  UINT_32             u4AkmSuite,
    OUT PUINT_32            pu4Index
    );

BOOLEAN
rsnPerformPolicySelection(
    IN  P_ADAPTER_T         prAdapter,
    IN  P_BSS_DESC_T        prBss
    );

UINT_8
rsnGenerateWPARSNIE(
    IN  P_ADAPTER_T         prAdapter,
    IN  P_BSS_DESC_T        prCurrentBss,
    IN  PUINT_8             pucIeStartAddr
    );

UINT_8
rsnGenerateWpaNoneIE(
    IN  P_ADAPTER_T         prAdapter,
    IN  PUINT_8             pucIeStartAddr
    );

VOID
rsnGenerateAuthReqEvent(
    IN  P_ADAPTER_T         prAdapter,
    IN BOOLEAN              fgFlags
    );

VOID
rsnTkipHandleMICFailure(
    IN P_ADAPTER_T          prAdapter,
    IN  BOOLEAN             fgErrorKeyType
    );

VOID
rsnSelectPmkidCandidateList(
    IN P_ADAPTER_T          prAdapter,
    IN P_BSS_DESC_T         prBssDesc
    );

VOID
rsnUpdatePmkidCandidateList(
    IN P_ADAPTER_T          prAdapter,
    IN P_BSS_DESC_T         prBssDesc
    );

BOOLEAN
rsnSearchPmkidEntry(
    IN P_ADAPTER_T          prAdapter,
    IN PUINT_8              pucBssid,
    OUT PUINT_32            pu4EntryIndex
    );

BOOLEAN
rsnCheckPmkidCandicate(
    IN P_ADAPTER_T          prAdapter
   );

VOID
rsnCheckPmkidCache(
    IN P_ADAPTER_T          prAdapter,
    IN P_BSS_DESC_T         prBss
    );

VOID
rsnGeneratePmkidIndication(
    IN P_ADAPTER_T          prAdapter,
    IN UINT_32              u4Flags
    );

/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/

#endif /* _RSN_H */

