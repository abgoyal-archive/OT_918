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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/ibss.c#2 $
*/

/*! \file   "ibss.c"
    \brief  This file contains the functions for IBSS(Ad-Hoc).

    This file contains the functions for IBSS(Ad-Hoc). We may create an IBSS
    network, or merge with exist IBSS network depending on current SCAN Result.
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
** $Log: ibss.c $
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\66 2009-05-25 22:47:14 GMT mtk01090
**  \main\maintrunk.MT5921\65 2009-03-09 20:50:06 GMT mtk01461
**  Add Beacon content change detection for AdHoc
**  Add Protection detection if a Legacy STA move into our IBSS
**  Set default entry's desire rate set to BSS's Basic Rate Set
**  \main\maintrunk.MT5921\64 2009-02-18 19:17:51 GMT mtk01461
**  \main\maintrunk.MT5921\63 2009-02-16 15:51:18 GMT mtk01461
**  Revise code to flush scan result while performing ABORT event
**  \main\maintrunk.MT5921\62 2008-12-01 13:56:10 GMT mtk01461
**  Remove Warning 613: Possible use of null pointer from lint
**  \main\maintrunk.MT5921\61 2008-11-28 12:03:27 GMT mtk01088
**  fixed some lint warning
**  \main\maintrunk.MT5921\60 2008-10-24 13:46:45 GMT mtk01084
**  modify input argument of caller to nicSetupOpChnlList()
**  \main\maintrunk.MT5921\59 2008-09-12 11:24:24 GMT mtk01461
**  Refine code - Add CFG_TX_FRAGMENT
**  \main\maintrunk.MT5921\58 2008-09-03 09:29:06 GMT mtk01084
**  move domain selection to the beginning when starting IBSS
**  \main\maintrunk.MT5921\57 2008-08-29 11:57:35 GMT mtk01084
**  fix compiler error
**  \main\maintrunk.MT5921\56 2008-08-20 17:46:46 GMT mtk01084
**  modify for coding rule conformance
**  \main\maintrunk.MT5921\55 2008-07-30 22:31:41 GMT mtk01084
**  modify the mechanism on determining obscured regulation domain
**  \main\maintrunk.MT5921\54 2008-07-14 13:38:10 GMT mtk01084
**  fix compiling warning on Linux
**  \main\maintrunk.MT5921\53 2008-07-11 10:49:12 GMT mtk01084
**  update comments
**  \main\maintrunk.MT5921\52 2008-07-11 10:47:27 GMT mtk01084
**  add few lines to check whether to append country code when multi-domain is not enabled
**  \main\maintrunk.MT5921\51 2008-07-11 09:45:32 GMT mtk01084
**  Always append the country information whenever creating IBSS (if multi-domain is disabled)
**  \main\maintrunk.MT5921\50 2008-07-10 20:48:23 GMT mtk01084
**  During creating IBSS, append country information when it is available by other BSS
**  \main\maintrunk.MT5921\49 2008-07-10 16:37:47 GMT mtk01084
**  support 802.11d related functions
**  \main\maintrunk.MT5921\48 2008-06-17 16:36:47 GMT mtk01425
**  1. Modify nicTxService for SDIO Tx Aggregation
**  \main\maintrunk.MT5921\47 2008-06-12 20:30:15 GMT mtk01461
**  Remove AD_HOC_MODE_11B_WIFI definition
**  \main\maintrunk.MT5921\46 2008-05-29 14:16:19 GMT mtk01084
**  get the intial ATIM window from connection seting
**  \main\maintrunk.MT5921\45 2008-05-15 14:05:12 GMT mtk01461
**  Add CFG_SW_TCL flag
**  \main\maintrunk.MT5921\44 2008-05-13 22:04:20 GMT mtk01084
**  Reset TSF due to IBSS is in-active (never enter IBSS-alone), and it should always sync other's TSF
**  \main\maintrunk.MT5921\43 2008-05-03 18:53:14 GMT mtk01461
**  Add nicExistIBSS() for change operation mode when leave IBSS
**  \main\maintrunk.MT5921\42 2008-04-23 14:13:49 GMT mtk01461
**  Select the lowest rate from desired rate set for error handling
**  \main\maintrunk.MT5921\41 2008-04-17 23:06:26 GMT mtk01461
**  Can reply more ProbeResp by reduce the memory consumption of ProbeResp frame
**  \main\maintrunk.MT5921\40 2008-04-07 22:59:09 GMT mtk01084
**  setting VoIP access TX queue based on WMM assoication or not
**  \main\maintrunk.MT5921\39 2008-04-02 21:08:12 GMT mtk01084
**  prevent type mismatch compiler warning
**  \main\maintrunk.MT5921\38 2008-04-01 23:52:53 GMT mtk01461
**  Clear rWmmInfo for PM when fgIsWmmAssoc is False
**  \main\maintrunk.MT5921\37 2008-04-01 10:56:05 GMT mtk01461
**  Update comments
**  \main\maintrunk.MT5921\36 2008-03-31 15:39:08 GMT mtk01084
**  not to reset TSF whenever transition from scan to ibss alone
**  \main\maintrunk.MT5921\35 2008-03-29 13:53:41 GMT mtk01461
**  Remove workaround for TCL
**  \main\maintrunk.MT5921\34 2008-03-23 22:48:53 GMT mtk01461
**  Fix STA_RECORD_T process of Beacon Lost Event for IBSS
**  \main\maintrunk.MT5921\33 2008-03-23 20:37:17 GMT mtk01461
**  Fix the synchronization issue of STA_RECORD_T and fgIsIBSSActive
**  \main\maintrunk.MT5921\32 2008-03-13 15:31:52 GMT mtk01461
**  Refine the relationship between SCAN result and STA record, lifetime, aging policy etc
**  \main\maintrunk.MT5921\31 2008-03-13 14:28:45 GMT mtk01461
**  Fix typo
**  \main\maintrunk.MT5921\30 2008-03-12 09:52:10 GMT mtk01461
**  Remove type case in MSDU_INFO_OBJ_INIT
**
**  \main\maintrunk.MT5921\29 2008-03-04 14:19:52 GMT mtk01084
**  not to associated with BSS with IBSS-PS function if this function is disabled
**  \main\maintrunk.MT5921\28 2008-02-29 13:02:13 GMT mtk01088
**  trigger the security fsm for ibss
**  \main\maintrunk.MT5921\27 2008-02-27 12:12:22 GMT mtk01461
**  Use COPY_SSID macro instead of kalMemCopy
**  \main\maintrunk.MT5921\26 2008-02-21 15:01:33 GMT mtk01461
**  Add initial rate according rx signal quality support
**  \main\maintrunk.MT5921\25 2008-02-12 23:00:33 GMT mtk01461
**  Add TX auto fragmentation for BT support
**  \main\maintrunk.MT5921\24 2008-02-01 09:31:19 GMT mtk01385
**  1. Fix WinCE 4.2 compiling error.
**  \main\maintrunk.MT5921\23 2008-01-07 15:06:33 GMT mtk01461
**  Add PhyType & AdHocMode Selection Support
**  \main\maintrunk.MT5921\22 2007-12-04 18:09:36 GMT mtk01461
**  Update MSDU_INFO_T init process
**  \main\maintrunk.MT5921\21 2007-11-21 15:28:27 GMT mtk01088
**  by encrypt status to decide the privacy bit at cap field
**  \main\maintrunk.MT5921\20 2007-11-08 13:48:13 GMT mtk01461
**  Fix TX Fragmentaion with IBSS - lost txFragInfoUpdate()
**  \main\maintrunk.MT5921\19 2007-11-02 00:57:12 GMT mtk01461
**  Unify TX Path for Normal and IBSS Power Save + IBSS neighbor learning
**  \main\maintrunk.MT5921\18 2007-10-31 16:07:44 GMT mtk01084
**  check ATIM capability under IBSS
**  \main\maintrunk.MT5921\17 2007-10-30 10:08:23 GMT mtk01425
**  1. Refine code
**  \main\maintrunk.MT5921\16 2007-10-25 18:05:09 GMT mtk01461
**  Add VOIP SCAN Support  & Refine Roaming
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
extern ADHOC_MODE_ATTRIBUTE_T rAdHocModeAttributes[];

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
* \brief This function is used to compose the Capability Info Field which will be
*        carried in Beacon or ProbeResponse Frame.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \retval Capability Info Field
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ UINT_16
ibssBuildCapabilityInfo (
    IN P_ADAPTER_T prAdapter
    )
{
    P_BSS_INFO_T prBssInfo;
    UINT_16 u2CapInfo;


    ASSERT(prAdapter);
    prBssInfo = &prAdapter->rBssInfo;

    u2CapInfo = CAP_INFO_IBSS;

    if (privacyEnabled(prAdapter)) {
        u2CapInfo |= CAP_INFO_PRIVACY;
    }

    if (prBssInfo->fgIsShortPreambleAllowed) {
        u2CapInfo |= CAP_INFO_SHORT_PREAMBLE;
    }

    if (prBssInfo->fgUseShortSlotTime) {
        u2CapInfo |= CAP_INFO_SHORT_SLOT_TIME;
    }

    return u2CapInfo;

} /* end of ibssBuildCapabilityInfo() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function is used to compose Information Elements for Beacon and
*        Probe Response Frame.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
* \param[in] pucBuffer  Pointer to the frame buffer.
*
* \retval Total IE length
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ UINT_16
ibssBuildBeaconProbeRespFrameIEs (
    IN P_ADAPTER_T prAdapter,
    IN PUINT_8 pucBuffer
    )
{
    P_BSS_INFO_T prBssInfo;
    UINT_8 aucAllSupportedRates[RATE_NUM] = {0};
    UINT_8 ucAllSupportedRatesLen;
    UINT_8 ucSupRatesLen;
    UINT_8 ucExtSupRatesLen;
    UINT_16 u2IeTotalLen = 0;
    UINT_8 ucIeLength;
#if CFG_SUPPORT_802_11D
    UINT_8 ucCountryInfoLen;
    P_CONNECTION_SETTINGS_T prConnSettings;
#endif

    ASSERT(prAdapter);
    ASSERT(pucBuffer);
    prBssInfo = &prAdapter->rBssInfo;

#if CFG_SUPPORT_802_11D
    prConnSettings = &prAdapter->rConnSettings;
#endif

    //4 <1> Fill the SSID element. ID:0
    SSID_IE(pucBuffer)->ucId = ELEM_ID_SSID;

    COPY_SSID(SSID_IE(pucBuffer)->aucSSID,
              SSID_IE(pucBuffer)->ucLength,
              prBssInfo->aucSSID,
              prBssInfo->ucSSIDLen);

    pucBuffer += ELEM_HDR_LEN + prBssInfo->ucSSIDLen;
    u2IeTotalLen += ELEM_HDR_LEN + prBssInfo->ucSSIDLen;


    //4 <2> Fill the Supported Rates element. ID:1
    rateGetDataRatesFromRateSet(prBssInfo->u2OperationalRateSet,
                                prBssInfo->u2BSSBasicRateSet,
                                aucAllSupportedRates,
                                &ucAllSupportedRatesLen);

    ucSupRatesLen = ((ucAllSupportedRatesLen > ELEM_MAX_LEN_SUP_RATES) ?
                     ELEM_MAX_LEN_SUP_RATES : ucAllSupportedRatesLen);

    ucExtSupRatesLen = ucAllSupportedRatesLen - ucSupRatesLen;

    if (ucSupRatesLen) {
        SUP_RATES_IE(pucBuffer)->ucId = ELEM_ID_SUP_RATES;
        SUP_RATES_IE(pucBuffer)->ucLength = ucSupRatesLen;
        kalMemCopy(SUP_RATES_IE(pucBuffer)->aucSupportedRates,
                   aucAllSupportedRates,
                   ucSupRatesLen);

        pucBuffer += ELEM_HDR_LEN + ucSupRatesLen;
        u2IeTotalLen += ELEM_HDR_LEN + ucSupRatesLen;
    }


    //4 <3> Fill the DS Parameter Set element. ID:3
    DS_PARAM_IE(pucBuffer)->ucId = ELEM_ID_DS_PARAM_SET;
    DS_PARAM_IE(pucBuffer)->ucLength = ELEM_MAX_LEN_DS_PARAMETER_SET;
    DS_PARAM_IE(pucBuffer)->ucCurrChnl = prBssInfo->ucChnl;

    pucBuffer += ELEM_HDR_LEN + ELEM_MAX_LEN_DS_PARAMETER_SET;
    u2IeTotalLen += ELEM_HDR_LEN + ELEM_MAX_LEN_DS_PARAMETER_SET;


    //4 <4> IBSS Parameter Set element, ID: 6
    IBSS_PARAM_IE(pucBuffer)->ucId = ELEM_ID_IBSS_PARAM_SET;
    IBSS_PARAM_IE(pucBuffer)->ucLength = ELEM_MAX_LEN_IBSS_PARAMETER_SET;
    WLAN_SET_FIELD_16(&(IBSS_PARAM_IE(pucBuffer)->u2ATIMWindow), prBssInfo->u2ATIMWindow);

    pucBuffer += ELEM_HDR_LEN + ELEM_MAX_LEN_IBSS_PARAMETER_SET;
    u2IeTotalLen += ELEM_HDR_LEN + ELEM_MAX_LEN_IBSS_PARAMETER_SET;

    //4 5. Country Information Element, ID: 7, for 11H or 11D
#if CFG_SUPPORT_802_11D
    /* Set the Country Information element. (ID: 10) */
    if (prConnSettings->fgMultiDomainCapabilityEnabled) {
        if (prBssInfo->fgIsCountryInfoPresent) {
            domainConstructCountryInfoElem(prAdapter, pucBuffer, &ucCountryInfoLen);

            pucBuffer += ELEM_HDR_LEN + ucCountryInfoLen;
            u2IeTotalLen += ELEM_HDR_LEN + ucCountryInfoLen;
        }
    }
#endif
#if 0//
    /*
    NOTE:
        Following section is not enabled, by the statement of IEEE802.11,
        Chapter 10.3.2.2.2 "Semantics of the service primitive":
        Country information is only present only when TPC functionality is
        required, as specified in 11.8, or when dot11MultiDomainCapabilityEnabled
        is true.
    */
    if (prBssInfo->fgIsCountryInfoPresent) {
        domainConstructCountryInfoElem(prAdapter, pucBuffer, &ucCountryInfoLen);

        pucBuffer += ELEM_HDR_LEN + ucCountryInfoLen;
        u2IeTotalLen += ELEM_HDR_LEN + ucCountryInfoLen;
    }
#endif

    /*
    //4 6. BSS Load, ID: 11

    //4 7. Power Constraint, ID: 32, for 11H

    //4 8. TPC Report, ID: 35, for 11H

    //4 9. Channel Switch Anouncement, ID: 37, for 11H

    //4 10. Quiet, ID: 40, for 11H

    //4 11. IBSS DFS, ID: 41, for 11H
*/

    //4 <12> ERP Information, ID: 42
    if (prBssInfo->fgIsERPPresent) {
        ERP_INFO_IE(pucBuffer)->ucId = ELEM_ID_ERP_INFO;
        ERP_INFO_IE(pucBuffer)->ucLength = ELEM_MAX_LEN_ERP;
        ERP_INFO_IE(pucBuffer)->ucERP = prBssInfo->ucERP;

        pucBuffer += ELEM_HDR_LEN + ELEM_MAX_LEN_ERP;
        u2IeTotalLen += ELEM_HDR_LEN + ELEM_MAX_LEN_ERP;
    }

    //4 <13> Extended Supported Rates element ID: 42
    if (ucExtSupRatesLen) {

        EXT_SUP_RATES_IE(pucBuffer)->ucId = ELEM_ID_EXTENDED_SUP_RATES;
        EXT_SUP_RATES_IE(pucBuffer)->ucLength = ucExtSupRatesLen;

        kalMemCopy(EXT_SUP_RATES_IE(pucBuffer)->aucExtSupportedRates,
                   &aucAllSupportedRates[ucSupRatesLen],
                   ucExtSupRatesLen);

        pucBuffer += ELEM_HDR_LEN + ucExtSupRatesLen;
        u2IeTotalLen += ELEM_HDR_LEN + ucExtSupRatesLen;
    }

    //4 <14> RSN, ID: 48

    //4 <15> WPA NONE , ID: 221
    ucIeLength = rsnGenerateWpaNoneIE(prAdapter, pucBuffer);

    pucBuffer += ucIeLength;
    u2IeTotalLen += ucIeLength;


    //4 <16> WMM

    return u2IeTotalLen;

} /* end of ibssBuildBeaconProbeRespFrameIEs() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will compose the Beacon or Probe Response frame.
*
* \param[in] prAdapter          Pointer to the Adapter structure.
* \param[in] pucBuffer          Pointer to the frame buffer.
* \param[in] pucDestAddr        Pointer to the Destination Address, if NULL, means Beacon.
* \param[out] pu2WlanHeaderLen  Pointer to store the result of frame header length.
* \param[out] pu2WlanBodyLen    Pointer to store the result of frame body length.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
ibssComposeBeaconProbeRespFrame (
    IN P_ADAPTER_T  prAdapter,
    IN PUINT_8      pucBuffer,
    IN PUINT_8      pucDestAddr,
    OUT PUINT_16    pu2WlanHeaderLen,
    OUT PUINT_16    pu2WlanBodyLen
    )
{
    P_WLAN_BEACON_FRAME_T prBeaconHdr;
    P_BSS_INFO_T prBssInfo;
    UINT_8 aucBCAddr[] = BC_MAC_ADDR;
    UINT_16 u2FrameCtrl;
    UINT_16 u2CapInfo;
    UINT_16 u2WlanBodyLen;


    ASSERT(prAdapter);
    ASSERT(pucBuffer);
    ASSERT(pu2WlanHeaderLen);
    ASSERT(pu2WlanBodyLen);

    prBeaconHdr = (P_WLAN_BEACON_FRAME_T)pucBuffer;
    prBssInfo = &prAdapter->rBssInfo;

    //4 <1> Compose the frame header of the Beacon /ProbeResp frame.
    /* Fill the Frame Control field. */
    if (pucDestAddr) {
        u2FrameCtrl = MAC_FRAME_PROBE_RSP;
    } else {
        u2FrameCtrl = MAC_FRAME_BEACON;
        pucDestAddr = aucBCAddr;
    }
    WLAN_SET_FIELD_16(&prBeaconHdr->u2FrameCtrl, u2FrameCtrl);

    /* Fill the DA field with BCAST MAC ADDR or TA of ProbeReq. */
    COPY_MAC_ADDR(prBeaconHdr->aucDestAddr, pucDestAddr);

    /* Fill the SA field with our MAC Address. */
    COPY_MAC_ADDR(prBeaconHdr->aucSrcAddr, prAdapter->aucMacAddress);

    /* Fill the BSSID field with current BSSID. */
    COPY_MAC_ADDR(prBeaconHdr->aucBSSID, prBssInfo->aucBSSID);

    /* Clear the SEQ/FRAG_NO field(HW won't overide the FRAG_NO, so we need to clear it). */
    prBeaconHdr->u2SeqCtrl = 0;


    //4 <2> Compose the frame body's common fixed field part of the Beacon /ProbeResp frame.
    /* MAC will update TimeStamp field */

    /* Fill the Beacon Interval field. */
    WLAN_SET_FIELD_16(&prBeaconHdr->u2BeaconInterval, prBssInfo->u2BeaconInterval);

    u2CapInfo = ibssBuildCapabilityInfo(prAdapter);

    /* Fill the Capability Information field. */
    WLAN_SET_FIELD_16(&prBeaconHdr->u2CapInfo, u2CapInfo);


    //4 <3> Update the MAC header/body length.
    *pu2WlanHeaderLen = WLAN_MAC_MGMT_HEADER_LEN;
    u2WlanBodyLen = TIMESTAMP_FIELD_LEN +
                    BEACON_INTERVAL_FIELD_LEN +
                    CAP_INFO_FIELD_LEN;

    //4 <4> Compose the frame body's IEs of the Beacon /ProbeResp frame.
    u2WlanBodyLen += ibssBuildBeaconProbeRespFrameIEs(prAdapter, prBeaconHdr->aucInfoElem);

    *pu2WlanBodyLen = u2WlanBodyLen;

    return;
} /* end of ibssComposeBeaconProbeRespFrame() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will send the (Re)Association Request frame
*
* \param[in] prAdapter          Pointer to the Adapter structure.
* \param[in] u4MaxContentLen    The acceptable maximum length of Beacon Frame Buffer.
* \param[out] pucBeaconContent  Pointer to the beacon frame buffer.
* \param[out] pu2ContentLen     Pointer to store the result of beacon frame length.
*
* \retval WLAN_STATUS_INVALID_LENGTH    No available free space for frame composing.
* \retval WLAN_STATUS_SUCCESS           Successfully send frame to TX Module
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
ibssPrepareBeaconFrame (
    IN P_ADAPTER_T prAdapter,
    IN UINT_32 u4MaxContentLen,
    OUT PUINT_8 pucBeaconContent,
    OUT PUINT_16 pu2ContentLen
    )
{
    UINT_16 u2WlanHeaderLen;
    UINT_16 u2WlanBodyLen;
    UINT_16 u2EstimatedFrameLen;


    ASSERT(prAdapter);
    ASSERT(pucBeaconContent);
    ASSERT(pu2ContentLen);

    u2EstimatedFrameLen = WLAN_MAC_MGMT_HEADER_LEN + \
                          TIMESTAMP_FIELD_LEN + \
                          BEACON_INTERVAL_FIELD_LEN + \
                          CAP_INFO_FIELD_LEN + \
                          (ELEM_HDR_LEN + ELEM_MAX_LEN_SSID) + \
                          (ELEM_HDR_LEN + ELEM_MAX_LEN_SUP_RATES) + \
                          (ELEM_HDR_LEN + (RATE_NUM - ELEM_MAX_LEN_SUP_RATES)) + \
                          (ELEM_HDR_LEN + ELEM_MAX_LEN_DS_PARAMETER_SET) + \
                          (ELEM_HDR_LEN + ELEM_MAX_LEN_IBSS_PARAMETER_SET) + \
                          (ELEM_HDR_LEN + ELEM_MAX_LEN_ERP) + \
                          (ELEM_HDR_LEN + ELEM_MAX_LEN_WPA_RSN) + \
                          (ELEM_HDR_LEN + ELEM_MAX_LEN_WMM_INFO);

    if (u4MaxContentLen < u2EstimatedFrameLen) {
        return WLAN_STATUS_INVALID_LENGTH;
    }

    ibssComposeBeaconProbeRespFrame(prAdapter,
                                    pucBeaconContent,
                                    (PUINT_8)NULL,
                                    &u2WlanHeaderLen,
                                    &u2WlanBodyLen);

    ASSERT(u4MaxContentLen >= (UINT_32)(u2WlanHeaderLen + u2WlanBodyLen));

    *pu2ContentLen = (u2WlanHeaderLen + u2WlanBodyLen);

    return WLAN_STATUS_SUCCESS;

} /* end of ibssPrepareBeaconFrame() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will parse and process the incoming Probe Request Frame
*        and decide to send back the Probe Response Frame. if the SSID was matched
*        or not specified.
*
* \param[in] prAdapter          Pointer to the Adapter structure.
* \param[in] prSwRfb            Pointer to SW RFB data structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
ibssProcessProbeRequest (
    IN P_ADAPTER_T prAdapter,
    IN P_SW_RFB_T prSwRfb
    )
{
    P_BSS_INFO_T prBssInfo;

    P_WLAN_MAC_MGMT_HEADER_T prMgtHdr;
    PUINT_8 pucIEBuf;

    P_IE_SSID_T prSSID = NULL;
    P_MSDU_INFO_T prMsduInfo = NULL;
    P_MGT_PACKET_T prMgtPacket = NULL;
    OS_SYSTIME rArrivalTime;
    UINT_16 u2WlanHeaderLen;
    UINT_16 u2WlanBodyLen;
    UINT_16 u2EstimatedFrameLen;
    UINT_32 u4Status = WLAN_STATUS_SUCCESS;
    DEBUGFUNC("ibssProcessProbeRequest");


    ASSERT(prAdapter);
    ASSERT(prSwRfb);

    prBssInfo = &prAdapter->rBssInfo;
    prMgtHdr = (P_WLAN_MAC_MGMT_HEADER_T)prSwRfb->pvHeader;
    pucIEBuf = (PUINT_8)prSwRfb->pvHeader + sizeof(WLAN_MAC_MGMT_HEADER_T);

    if (!nicpmIfAdhocStaMaster(prAdapter)) {
        return;
    }

    //4 <1> Check SSID
    prSSID = SSID_IE(pucIEBuf);
    if (prSSID->ucLength) {
        if (UNEQUAL_SSID(prBssInfo->aucSSID, prBssInfo->ucSSIDLen, prSSID->aucSSID, prSSID->ucLength)) {
            DBGLOG(MGT, LOUD, ("SSID not matched\n"));
            return;
        }
    }

    //4 <2> Allocate MSDU_INFO_T
    prMsduInfo = nicTxAllocMsduInfo(prAdapter, TCM);
    if (prMsduInfo == (P_MSDU_INFO_T)NULL) {
        DBGLOG(MGT, WARN, ("No MSDU_INFO_T to send Probe Response.\n"));
        return;
    }

    //4 <3> Allocate Frame Buffer (in MGT_PACKET_T) for ProbeResp Frame
    u2EstimatedFrameLen = WLAN_MAC_MGMT_HEADER_LEN + \
                          TIMESTAMP_FIELD_LEN + \
                          BEACON_INTERVAL_FIELD_LEN + \
                          CAP_INFO_FIELD_LEN + \
                          (ELEM_HDR_LEN + ELEM_MAX_LEN_SSID) + \
                          (ELEM_HDR_LEN + ELEM_MAX_LEN_SUP_RATES) + \
                          (ELEM_HDR_LEN + (RATE_NUM - ELEM_MAX_LEN_SUP_RATES)) + \
                          (ELEM_HDR_LEN + ELEM_MAX_LEN_DS_PARAMETER_SET) + \
                          (ELEM_HDR_LEN + ELEM_MAX_LEN_IBSS_PARAMETER_SET) + \
                          (ELEM_HDR_LEN + ELEM_MAX_LEN_ERP);

    if (prAdapter->rConnSettings.eAuthMode == AUTH_MODE_WPA_NONE) {
        u2EstimatedFrameLen += (ELEM_HDR_LEN + ELEM_MAX_LEN_WPA_RSN);
    }

    if (prBssInfo->fgIsWmmAssoc) {
        u2EstimatedFrameLen += (ELEM_HDR_LEN + ELEM_MAX_LEN_WMM_INFO);
    }

    prMgtPacket = mgtBufAllocateMgtPacket(prAdapter, (UINT_32)u2EstimatedFrameLen);
    if (prMgtPacket == (P_MGT_PACKET_T)NULL) {
        nicTxReturnMsduInfo(prAdapter, prMsduInfo);
        DBGLOG(MGT, WARN, ("No buffer to send Probe Response, required = %d.\n", u2EstimatedFrameLen));
        return;
    }

    //4 <4> Compose Association Request frame in MGT_PACKET_T.
    ibssComposeBeaconProbeRespFrame(prAdapter,
                                    MGT_PACKET_GET_BUFFER(prMgtPacket),
                                    prMgtHdr->aucSrcAddr,
                                    &u2WlanHeaderLen,
                                    &u2WlanBodyLen);
    //4 <5> Update the frame length to the packet descriptor (MGT_PACKET_T).
    mgtPacketPut(prMgtPacket, (u2WlanHeaderLen + u2WlanBodyLen));

    //4 <6> Update information in MSDU_INFO_T for TX Module.
    GET_CURRENT_SYSTIME(&rArrivalTime);

    MSDU_INFO_OBJ_INIT(prMsduInfo, \
                       TRUE, \
                       TRUE, \
                       (PVOID)prMgtPacket, \
                       0, \
                       TXQ_TCM, \
                       (UINT_8)u2WlanHeaderLen, \
                       u2WlanBodyLen, \
                       MSDU_INFO_CTRL_FLAG_SPECIFY_AC | MSDU_INFO_CTRL_FLAG_BASIC_RATE | MSDU_INFO_CTRL_FLAG_NO_ACK, \
                       (PFN_TX_DONE_HANDLER)0, \
                       rArrivalTime, \
                       NULL \
                       );

    //4 <7> Inform ARB to send this Authentication Request frame.
    DBGLOG(MGT, LOUD, ("Send Probe Response frame\n"));
    if ((u4Status = arbFsmRunEventTxMmpdu(prAdapter,prMsduInfo)) != WLAN_STATUS_PENDING) {

        if(u4Status != WLAN_STATUS_SUCCESS) {
            mgtBufFreeMgtPacket(prAdapter, prMgtPacket);

            nicTxReturnMsduInfo(prAdapter, prMsduInfo);

            DBGLOG(MGT, ERROR, ("Send Probe Response fail.\n"));
        }


        //return WLAN_STATUS_FAILURE;
    }

    return;
} /* end of ibssProcessProbeRequest() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will check the Capability for Ad-Hoc to decide if we are
*        able to merge with(same capability).
*
* \param[in] prAdapter          Pointer to the Adapter structure.
* \param[in] prBSSDesc  Pointer to the BSS Descriptor.
*
* \retval WLAN_STATUS_FAILURE   Can't pass the check of Capability.
* \retval WLAN_STATUS_SUCCESS   Pass the check of Capability.
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
ibssCheckCapabilityForAdHocMode (
    IN P_ADAPTER_T prAdapter,
    IN P_BSS_DESC_T prBssDesc
    )
{
    P_CONNECTION_SETTINGS_T prConnSettings;
    WLAN_STATUS rStatus = WLAN_STATUS_FAILURE;

    DEBUGFUNC("ibssCheckCapabilityForAdHocMode");


    ASSERT(prAdapter);
    ASSERT(prBssDesc);
    prConnSettings = &prAdapter->rConnSettings;

    do {
        //4 <1> Check the BSS Basic Rate Set for current AdHoc Mode
        if ((prConnSettings->eAdHocMode == AD_HOC_MODE_11B) &&
            (prBssDesc->u2BSSBasicRateSet & ~RATE_SET_HR_DSSS)) {
            break;
        }
#if 0 // Enable 11A if RF support.
        else if ((prConnSettings->eAdHocMode == AD_HOC_MODE_11A) &&
            (prBssDesc->u2BSSBasicRateSet & ~RATE_SET_OFDM)) {
            break;
        }
#endif

        //4 <2> Check the Short Slot Time.
#if 0 // Do not check ShortSlotTime until Wi-Fi define such policy        
        if (prConnSettings->eAdHocMode == AD_HOC_MODE_11G) {
            if (((prConnSettings->fgIsShortSlotTimeOptionEnable) &&
                 !(prBssDesc->u2CapInfo & CAP_INFO_SHORT_SLOT_TIME)) ||
                (!(prConnSettings->fgIsShortSlotTimeOptionEnable) &&
                 (prBssDesc->u2CapInfo & CAP_INFO_SHORT_SLOT_TIME))) {
                break;
            }
        }
#endif

#if CFG_IBSS_POWER_SAVE
        //4 <3> Check the ATIM window setting.
        if (prBssDesc->u2ATIMWindow) {
            if (!PM_IS_ADHOC_POWER_SAVE_CAPABLE(prAdapter)) {
                DBGLOG(LP, INFO, ("No Ad hoc PS capability (recvd ATIM window: %d)\n",
                    prBssDesc->u2ATIMWindow));
                break;
            }
        }
#else
        //4 <3> Check the ATIM window setting.
        if (prBssDesc->u2ATIMWindow) {
            break;
        }
#endif /* CFG_IBSS_POWER_SAVE */


        //4 <4> Check the Security setting.
        if (!rsnPerformPolicySelection(prAdapter, prBssDesc)) {
            break;
        }
        
        rStatus = WLAN_STATUS_SUCCESS;
    }
    while (FALSE);

    return rStatus;

} /* end of ibssCheckCapabilityForAdHocMode() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function is used to process Beacons from current Ad-Hoc network peers.
*        We also process Beacons from other Ad-Hoc network during SCAN. If it has
*        the same SSID and we'll decide to merge into it if it has a larger TSF.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
* \param[in] prBSSDesc  Pointer to the BSS Descriptor.
* \param[in] prSWRfb    Pointer to the receiving frame buffer.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
ibssProcessBeacon (
    IN P_ADAPTER_T prAdapter,
    IN P_BSS_DESC_T prBSSDesc,
    IN P_SW_RFB_T prSwRfb
    )
{
    P_BSS_INFO_T prBssInfo;
    P_WLAN_BEACON_FRAME_T prWlanBeaconFrame;
    P_STA_RECORD_T prStaRec = NULL;
    BOOLEAN fgIsCheckCapability = FALSE;
    BOOLEAN fgIsCheckTSF = FALSE;
    BOOLEAN fgIsGoingMerging = FALSE;
    BOOLEAN fgIsGoingChangeDetection = FALSE;
    BOOLEAN fgIsSameBSSID = FALSE;
    BOOLEAN fgIsSameSSID = FALSE;

    DEBUGFUNC("ibssProcessBeacon");


    ASSERT(prAdapter);
    ASSERT(prBSSDesc);
    ASSERT(prSwRfb);

    prBssInfo = &prAdapter->rBssInfo;
    prWlanBeaconFrame = (P_WLAN_BEACON_FRAME_T)prSwRfb->pvHeader;

    //4 <1> Check if the BSS_DESC_T is IBSS.
    if (prBSSDesc->eBSSType != BSS_TYPE_IBSS) {
        return;
    }

    //4 <2> Process IBSS Beacon only after we create or merge with other IBSS.
    if (!prAdapter->fgIsIBSSActive) {
        return;
    }


    //4 <3> Get the STA_RECORD_T of TA.
    prStaRec = staRecGetStaRecordByAddr(prAdapter, prWlanBeaconFrame->aucSrcAddr);

    fgIsSameBSSID = UNEQUAL_MAC_ADDR(prBssInfo->aucBSSID, prBSSDesc->aucBSSID) ? FALSE : TRUE;
    
    fgIsSameSSID = UNEQUAL_SSID(prBssInfo->aucSSID, prBssInfo->ucSSIDLen,
                                prBSSDesc->aucSSID, prBSSDesc->ucSSIDLen) ? FALSE : TRUE;


    //4 <4> Change detection for Abort Event
    if ((prStaRec) && fgIsSameBSSID) {

        //4 <4.1> Check if the BSS_DESC_T's SSID is identical to mine.
        if (!fgIsSameSSID) {
            /* NOTE(Kevin): If remote peer change its SSID suddenly, but still has same BSSID,
             * we should leave this IBSS immediately. We'll do scan after calling
             * the ABORT event and check if there exist any valid peers (same SSID).
             */
             
            arbFsmRunEventAbort(prAdapter, TRUE);
        }

        //4 <4.2> Check if the BSS_DESC_T's Privacy in CAP_FIELD and WPA_NONE is identical to mine.
        if (!rsnPerformPolicySelection(prAdapter, prBSSDesc)) {
            /* NOTE(Kevin): If remote peer change its Security Setting suddenly, but still has same BSSID,
             * we should leave this IBSS immediately. We'll do scan after calling
             * the ABORT event and check if there exist any valid peers (same SSID).
             */
             
            arbFsmRunEventAbort(prAdapter, TRUE);
        }

        //4 <4.3> Check if the BSS_DESC_T's Channel is identical to mine.
        if (prBssInfo->ucChnl != prBSSDesc->ucChannelNum) {
            /* NOTE(Kevin): If remote peer change its channel suddenly, but still has same BSSID,
             * we should leave this IBSS immediately. We'll do scan after calling
             * the ABORT event and check if there exist any valid peers (same SSID).
             */
             
            arbFsmRunEventAbort(prAdapter, TRUE);
        }
    }


    //4 <5> Check if the BSS_DESC_T's SSID is identical to mine.
    if (!fgIsSameSSID) {
        return;
    }


    //4 <6> IBSS Merge Decision Flow for Processing Beacon.
    if (fgIsSameBSSID) {

        /* Same BSSID:
         * Case I.  This is a new TA and it has decide to merged with us.
         * Case II. This is an old TA and we've already merged together.
         */

        if (!prStaRec) {
            /* For Case I - Check this IBSS's capability first before adding this Sta Record. */
            fgIsCheckCapability = TRUE;

            /* If check is passed, then we perform merging with this new IBSS */
            fgIsGoingMerging = TRUE;

        }
        else {
            /* For Case II - Update rExpirationTime of Sta Record */
            GET_CURRENT_SYSTIME(&prStaRec->rUpdateTime);

            fgIsGoingChangeDetection = TRUE; /* We need to check if this STA is 11b */
        }
    }
    else {

        /* Unequal BSSID:
         * Case III. This is a new TA and we need to compare the TSF and get the winner.
         * Case IV.  This is an old TA and it merge into a new IBSS before we do the same thing.
         *           We need to compare the TSF to get the winner.
         * Case V.   This is an old TA and it restart a new IBSS. We also need to
         *           compare the TSF to get the winner.
         */

        /* For Case III, IV & V - We'll always check this new IBSS's capability first
         * before merging into new IBSS.
         */
        fgIsCheckCapability = TRUE;

        /* If check is passed, we need to perform TSF check to decide the major BSSID */
        fgIsCheckTSF = TRUE;

        /* For Case IV & V - We won't update rExpirationTime of Sta Record */
    }


    //4 <7> Check this BSS_DESC_T's capability.
    if (fgIsCheckCapability) {
        BOOLEAN fgIsCapabilityMatched = FALSE;


        do {
            if (!(BIT(prBSSDesc->ePhyType) & prAdapter->u2AvailablePhyTypeSet)) {

                DBGLOG(MGT, TRACE, ("Ignore BSS DESC MAC: "MACSTR", PhyType = %s not supported\n",
                    MAC2STR(prBSSDesc->aucBSSID),
                    ((prBSSDesc->ePhyType == PHY_TYPE_ERP_INDEX) ? "PHY_TYPE_ERP" :
                     ((prBSSDesc->ePhyType == PHY_TYPE_HR_DSSS_INDEX) ? "PHY_TYPE_HR_DSSS" : "PHY_TYPE_OFDM") ) ));

                break;
            }

            if ((prBSSDesc->u2BSSBasicRateSet &
                 ~(rPhyAttributes[prBSSDesc->ePhyType].u2SupportedRateSet)) ||
                prBSSDesc->fgIsUnknownBssBasicRate) {

                break;
            }

            if (ibssCheckCapabilityForAdHocMode(prAdapter, prBSSDesc) == WLAN_STATUS_FAILURE) {

                DBGLOG(MGT, TRACE,
                    ("Ignore BSS DESC MAC: "MACSTR", Capability is not supported for current AdHoc Mode.\n",
                     MAC2STR(prBSSDesc->aucBSSID)));

                break;
            }

            fgIsCapabilityMatched = TRUE;
        }
        while (FALSE);

        if (!fgIsCapabilityMatched) {

            if (prStaRec) {
                /* For Case II - We merge this STA_RECORD in RX Path.
                 *     Case IV & V - They change their BSSID after we merge with them.
                 */

                DBGLOG(MGT, WARN,
                    ("We merge a BSS DESC MAC: "MACSTR" which its Capability is not match with us.\n",
                     MAC2STR(prBSSDesc->aucBSSID)));
            }

            return;
        }
    }


    if (fgIsCheckTSF) {
#if !CFG_SW_TCL // NOTE(Kevin 2008/03/29): Use TCL in RFB
        if (prBSSDesc->fgIsLargerTSF) {
            fgIsGoingMerging = TRUE;
        }
        else {
            return;
        }
#else /* CFG_SW_TCL */
        ULARGE_INTEGER rCurrentTsf;

        NIC_GET_CURRENT_TSF(prAdapter, &rCurrentTsf);

        DBGLOG(SCAN, TRACE,
            ("\n\nCurrent TSF : %08lx-%08lx\n\n",
                rCurrentTsf.u.HighPart, rCurrentTsf.u.LowPart));

        if (rCurrentTsf.QuadPart > prBSSDesc->u8TimeStamp.QuadPart) {
            DBGLOG(SCAN, TRACE,
                ("Ignore BSS DESC MAC: ["MACSTR"], Current BSSID: ["MACSTR"].\n",
                    MAC2STR(prBSSDesc->aucBSSID), MAC2STR(prBssInfo->aucBSSID)));

            DBGLOG(SCAN, TRACE,
                ("\n\nBSS's TSF : %08lx-%08lx\n\n",
                    prBSSDesc->u8TimeStamp.u.HighPart, prBSSDesc->u8TimeStamp.u.LowPart));

            prBSSDesc->fgIsLargerTSF = FALSE;
            return;
        }
        else {
            prBSSDesc->fgIsLargerTSF = TRUE;
            fgIsGoingMerging = TRUE;
        }
#endif /* CFG_SW_TCL */
    }


    if (fgIsGoingMerging) {
        /* Inform ARB to do STATE TRANSITION
         * For Case I - If ARB in IBSS_ALONE, let it jump to NORMAL_TR after we know the new member.
         * For Case III, IV - Now this new BSSID wins the TSF, follow it.
         */
        arbFsmRunEventIbssMerge(prAdapter, prBSSDesc);
    }
    else if (fgIsGoingChangeDetection) {

        //4 <9> Protection of 11b member
        if (prBssInfo->fgIsERPPresent) {
            if ((!prBssInfo->fgIsProtection) && 
                (prBSSDesc->ePhyType == PHY_TYPE_HR_DSSS_INDEX)) {

                prBssInfo->fgIsProtection = TRUE;

                nicRateEnableProtection(prAdapter, CTS_PROTECTION_TYPE_802_11);

                prBssInfo->ucERP |= (ERP_INFO_NON_ERP_PRESENT | ERP_INFO_USE_PROTECTION);

                ARB_SET_TIMER(prAdapter,
                              prAdapter->rArbInfo.rProtectionTimerForAdHoc,
                              SEC_TO_MSEC(IBSS_PROTECTION_TIMEOUT_CHECK_SEC));

                kalMemZero(prBssInfo->aucBcnContent, sizeof(prBssInfo->aucBcnContent));
                prBssInfo->u2BcnLen = 0;

                ibssPrepareBeaconFrame(prAdapter,
                                       sizeof(prBssInfo->aucBcnContent),
                                       prBssInfo->aucBcnContent,
                                       &prBssInfo->u2BcnLen);

                nicStartBeacon(prAdapter);
            }
        }        
    }

    return;
} /* end of ibssProcessBeacon() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will start an Ad-Hoc network and send Beacon Frames.
*
* \param[in] prAdapter          Pointer to the Adapter structure.
*
* \retval WLAN_STATUS_INVALID_LENGTH    No available free space for frame composing.
* \retval WLAN_STATUS_SUCCESS           Successfully send frame to TX Module
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
ibssStartIBSS (
    IN P_ADAPTER_T prAdapter
    )
{
    P_CONNECTION_SETTINGS_T prConnSettings;
    P_BSS_INFO_T prBssInfo;
    P_STA_RECORD_T prStaRec = (P_STA_RECORD_T)NULL;
    WLAN_STATUS rStatus = WLAN_STATUS_SUCCESS;
    P_TX_CTRL_T prTxCtrl;

    DEBUGFUNC("ibssStartIBSS");


    ASSERT(prAdapter);
    prConnSettings = &prAdapter->rConnSettings;
    prBssInfo = &prAdapter->rBssInfo;
    prTxCtrl = &prAdapter->rTxCtrl;

    //4 <1> After STANDBY STATE, we only create IBSS once
    if (!prAdapter->fgIsIBSSActive) {

    //4 <2> Update BSS_INFO_T from CONNECTION_SETTINGS_T
        //4 <2.A> PHY Type (Corresponding to 2.A in joinComplete() )
        prBssInfo->ePhyType =
            rAdHocModeAttributes[prConnSettings->eAdHocMode].ePhyTypeIndex;

        prAdapter->eCurrentPhyType = prBssInfo->ePhyType;

        //4 <2.B> Country Information
#if CFG_SUPPORT_802_11D
        if (prConnSettings->fgMultiDomainCapabilityEnabled) {
            if (domainGetDomainInfoByScanResult(prAdapter, &prBssInfo->rDomainInfo)) {

                /* use the domain get from the scan result */
                prBssInfo->fgIsCountryInfoPresent = TRUE;
                nicSetupOpChnlList(prAdapter, prBssInfo->rDomainInfo.u2CountryCode, FALSE);
            }
        }
#endif

        //4 <2.C> BSS Type
        prBssInfo->eBSSType = BSS_TYPE_IBSS;

        //4 <2.D> BSSID
        {
            UINT_8 aucBSSID[MAC_ADDR_LEN];
            PUINT_16 pu2BSSID = (PUINT_16)&aucBSSID[0];
            UINT_32 i;

            for (i = 0; i < sizeof(aucBSSID)/sizeof(UINT_16); i++) {
                nicGetRandomNumber(prAdapter, &pu2BSSID[i]);
            }

            aucBSSID[0] &= ~0x01; // 7.1.3.3.3 - The individual/group bit of the address is set to 0.
            aucBSSID[0] |= 0x02; // 7.1.3.3.3 - The universal/local bit of the address is set to 1.

            COPY_MAC_ADDR(prBssInfo->aucBSSID, aucBSSID);
        }

        //4 <2.E> SSID
        COPY_SSID(prBssInfo->aucSSID,
                  prBssInfo->ucSSIDLen,
                  prAdapter->rConnSettings.aucSSID,
                  prAdapter->rConnSettings.ucSSIDLen);

        //4 <2.F> Channel / Band information
        prBssInfo->eBand = (ENUM_BAND_T)prConnSettings->ucChannelBand;
        prBssInfo->ucChnl = prConnSettings->ucChannelNum;


        //4 <2.G> RSN/WPA information - Not needed in AdHoc(W.H)

        //4 <2.H> Beacon interval
        prBssInfo->u2BeaconInterval = prConnSettings->u2BeaconPeriod;

        //4 <2.I> ATIM Window (Corresponding to DTIM)
        prBssInfo->u2ATIMWindow = prConnSettings->u2AtimWindow;

        //4 <2.J> ERP Information
        if (prBssInfo->ePhyType == PHY_TYPE_ERP_INDEX) {
            prBssInfo->fgIsERPPresent = TRUE;
        }
        else { /* Some AP, may send ProbeResp without ERP IE. Thus prBssDesc->fgIsERPPresent is FALSE. */
            prBssInfo->fgIsERPPresent = FALSE;
        }
        prBssInfo->ucERP = 0;

        DBGLOG(MGT, INFO, ("prBssInfo->fgIsERPPresent = %d, prBssInfo->ucERP = %02x\n",
            prBssInfo->fgIsERPPresent, prBssInfo->ucERP));

    //4 <3> NIC RATE FUNC
        //4 <3.B > WMM Infomation - Setup Variables
        if (prAdapter->fgIsEnableWMM && prConnSettings->fgIsAdHocQoSEnable) {
            prBssInfo->fgIsWmmAssoc = TRUE;
            prTxCtrl->rTxQForVoipAccess = TXQ_AC3;
        }
        else {
            prBssInfo->fgIsWmmAssoc = FALSE;
            prTxCtrl->rTxQForVoipAccess = TXQ_AC1;

            kalMemZero(&prBssInfo->rWmmInfo, sizeof(WMM_INFO_T));
        }

        //4 <3.C> Operational Rate Set & BSS Basic Rate Set
        prBssInfo->u2OperationalRateSet =
            rPhyAttributes[prBssInfo->ePhyType].u2SupportedRateSet;

        prBssInfo->u2BSSBasicRateSet =
            rAdHocModeAttributes[prConnSettings->eAdHocMode].u2BSSBasicRateSet;

        //4 <3.D> Short Preamble
        if ( rPhyAttributes[prBssInfo->ePhyType].fgIsShortPreambleOptionImplemented &&
            ((prConnSettings->ePreambleType == PREAMBLE_TYPE_SHORT) || /* Short Preamble Option Enable is TRUE */
             (prConnSettings->ePreambleType == PREAMBLE_TYPE_AUTO)) ) {

            prBssInfo->fgIsShortPreambleAllowed = TRUE;
            prBssInfo->fgUseShortPreamble = TRUE;
        }
        else {
            prBssInfo->fgIsShortPreambleAllowed = FALSE;
            prBssInfo->fgUseShortPreamble = FALSE;
        }

        //4 <3.D> Update ERP after Short Preamble.
        if (prBssInfo->fgIsERPPresent) {
            if (!prBssInfo->fgUseShortPreamble) {
                prBssInfo->ucERP |= ERP_INFO_BARKER_PREAMBLE_MODE;
            }
        }

        //4 <3.E> Short Slot Time
        // 7.3.1.4 For IBSS, the Short Slot Time subfield shall be set to 0.
        prBssInfo->fgUseShortSlotTime = FALSE;

        DBGLOG(MGT, INFO, ("prBssInfo->fgUseShortSlotTime = %d\n",
            prBssInfo->fgUseShortSlotTime));

        nicSetSlotTime(prAdapter,
                       prBssInfo->ePhyType,
                       FALSE);


        //4 <3.F> Update Tx Rate for Control Frame
        bssUpdateTxRateForControlFrame(prAdapter);

        //4 <3.G> Save the available Auth Types during Roaming  - Not needed in AdHoc.

        //4 <3.H> Update Parameter for TX Fragmentation Threshold
#if CFG_TX_FRAGMENT
        txFragInfoUpdate(prAdapter);
#endif /* CFG_TX_FRAGMENT */


    //4 <4> Update Default STA_RECORD_T
        {
            UINT_16 u2DesiredRateSet;


            /* We create a new BSS, so remove entire old records. */
            staRecRemoveStaRecordByPolicy(prAdapter, STA_RECORD_RM_POLICY_ENTIRE);

            /* Add a STA Record for default entry */
            prStaRec = staRecGetStaRecordByAddrOrAddIfNotExist(prAdapter,
                           prBssInfo->aucBSSID);

            /* **NOTE(Kevin): This is the default entry(BSSID), we use STATE_3 to avoid
             * been clean up by aging func.
             */
            prStaRec->ucStaState = STA_STATE_3;

            prStaRec->rRcpi = RCPI_HIGH_BOUND;

            /* Update the record activity time. */
            GET_CURRENT_SYSTIME(&prStaRec->rUpdateTime);


            //4 <4.A> Desired Rate Set, use BasicRateSet for default(BMCAST) entry
            u2DesiredRateSet = (prConnSettings->u2DesiredRateSet &
                                    prBssInfo->u2BSSBasicRateSet);
            if (u2DesiredRateSet) {
                prStaRec->u2DesiredRateSet = u2DesiredRateSet;
            }
            else {
                /* For Error Handling - The Desired Rate Set is not covered in Operational Rate Set. */
                prStaRec->u2DesiredRateSet = prBssInfo->u2OperationalRateSet;
            }

            /* Try to set the best initial rate for default entry */
            if (!rateGetBestInitialRateIndex(prStaRec->u2DesiredRateSet,
                                             prStaRec->rRcpi,
                                             &prStaRec->ucCurrRate1Index)) {

                if (!rateGetLowestRateIndexFromRateSet(prStaRec->u2DesiredRateSet,
                                                       &prStaRec->ucCurrRate1Index)) {
                    ASSERT(0);
                }
            }

            DBGLOG(MGT, TRACE, ("Initial Rate Index for entry ["MACSTR"] = %d\n",
                MAC2STR(prStaRec->aucMacAddr), prStaRec->ucCurrRate1Index));

            //4 <4.B> Preamble Mode
            prStaRec->fgIsShortPreambleOptionEnable =
                prBssInfo->fgUseShortPreamble;

            //4 <4.C> QoS Flag set to FALSE for default entry (BMCAST frames)
            prStaRec->fgIsQoS = FALSE;

            //4 <4.D> Update WLAN Table for default Entry.
            if (nicSetHwBySta(prAdapter, prStaRec) == FALSE) {
                ASSERT(FALSE);
            }

            //4 <4.E> Update Desired Rate Set for BT.
#if CFG_TX_FRAGMENT
            if (prConnSettings->fgIsEnableTxAutoFragmentForBT) {
                txRateSetInitForBT(prAdapter, prStaRec);
            }
#endif /* CFG_TX_FRAGMENT */

            //4 <4.F> Legacy Flag
            prStaRec->fgIsLegacy = FALSE; /* Set to FALSE for default entry */

        }


    //4 <5> Compose Beacon
        kalMemZero(prBssInfo->aucBcnContent, sizeof(prBssInfo->aucBcnContent));
        prBssInfo->u2BcnLen = 0;

        rStatus = ibssPrepareBeaconFrame(prAdapter,
                                         sizeof(prBssInfo->aucBcnContent),
                                         prBssInfo->aucBcnContent,
                                         &prBssInfo->u2BcnLen);



//        prAdapter->fgIsIBSSActive = TRUE;
    }


//4 <6> Update NIC
    //4 <6.A> Update BSSID & Operation Mode
    nicSetupBSS(prAdapter, prBssInfo);

    //4 <6.B> TX AC Parameter and TX/RX Queue Control
    if (prBssInfo->fgIsWmmAssoc) {
        qosWmmInfoInit(&prBssInfo->rWmmInfo,
                       (prBssInfo->ePhyType == PHY_TYPE_HR_DSSS_INDEX) ? TRUE : FALSE);

        qosUpdateWMMParametersAndAssignAllowedACI(prAdapter, &prBssInfo->rWmmInfo);
        ASSERT(0); /* NOTE(Kevin): Not test yet */
    }
    else {
        kalMemZero(&prBssInfo->rWmmInfo, sizeof(WMM_INFO_T));

        nicTxNonQoSAssignDefaultAdmittedTXQ(prAdapter);

        nicTxNonQoSUpdateTXQParameters(prAdapter,
                                       prBssInfo->ePhyType);
    }

    //4 <6.C> Setup IBSS' Frequency(Band/Channel)
    nicSwitchChannel(prAdapter, prBssInfo->eBand, prBssInfo->ucChnl, 0);


//4 <7> Start to sending Beacons.
    nicStartBeacon(prAdapter);

    return rStatus;

} /* end of ibssStartIBSS() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will merge to an exist Ad-Hoc network and send Beacon Frames.
*
* \param[in] prAdapter          Pointer to the Adapter structure.
* \param[in] prBssDesc          Pointer to the BSS Descriptor.
*
* \retval WLAN_STATUS_INVALID_LENGTH    No available free space for frame composing.
* \retval WLAN_STATUS_SUCCESS           Successfully send frame to TX Module
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
ibssMergeIBSS (
    IN P_ADAPTER_T prAdapter,
    IN P_BSS_DESC_T prBssDesc
    )
{
    P_CONNECTION_SETTINGS_T prConnSettings;
    P_BSS_INFO_T prBssInfo;
    P_STA_RECORD_T prStaRec = (P_STA_RECORD_T)NULL;
    BOOLEAN fgIsGoingMergingOut = FALSE;
    WLAN_STATUS rStatus = WLAN_STATUS_SUCCESS;
    P_TX_CTRL_T prTxCtrl;
#if CFG_SUPPORT_802_11D
    P_IE_COUNTRY_T          prIECountry;
#endif

    DEBUGFUNC("ibssMergeIBSS");


    ASSERT(prAdapter);
    ASSERT(prBssDesc);
    prConnSettings = &prAdapter->rConnSettings;
    prBssInfo = &prAdapter->rBssInfo;
    prTxCtrl = &prAdapter->rTxCtrl;

    //4 <1> IBSS Merge Decision Flow for IBSS MERGE STATE.
    if (!prAdapter->fgIsIBSSActive) {
        fgIsGoingMergingOut = TRUE;

        /* Reset TSF due to IBSS is in-active (never enter IBSS-alone),
           and it should always sync other's TSF */
        nicpmResetTSFTimer(prAdapter);
    }
    else {
        /* Merge In */
        if (UNEQUAL_MAC_ADDR(prBssInfo->aucBSSID, prBssDesc->aucBSSID)) {
            if (prBssDesc->fgIsLargerTSF) {
                fgIsGoingMergingOut = TRUE;
            }
            else {
                ASSERT(0); /* Such case should be blocked in ibssProcessBeacon() */
            }
        }
    }

    if (fgIsGoingMergingOut) {

    //4 <2> Update BSS_INFO_T from CONNECTION_SETTINGS_T
        //4 <2.A> PHY Type (Corresponding to 2.A in joinComplete() )
        prBssInfo->ePhyType = prBssDesc->ePhyType;

        prAdapter->eCurrentPhyType = prBssInfo->ePhyType;

        //4 <2.B> BSS Type
        prBssInfo->eBSSType = BSS_TYPE_IBSS;

        //4 <2.C> BSSID
        COPY_MAC_ADDR(prBssInfo->aucBSSID, prBssDesc->aucBSSID);

        //4 <2.D> SSID
        COPY_SSID(prBssInfo->aucSSID,
                  prBssInfo->ucSSIDLen,
                  prBssDesc->aucSSID,
                  prBssDesc->ucSSIDLen);

        //4 <2.E> Channel / Band information
        prBssInfo->eBand = prBssDesc->eBand;
        prBssInfo->ucChnl = prBssDesc->ucChannelNum;

        //4 <2.F> RSN/WPA information
        secFsmRunEventStart(prAdapter);

        //4 <2.G> Beacon interval
        prBssInfo->u2BeaconInterval = prBssDesc->u2BeaconInterval;

        //4 <2.H> ATIM Window (Corresponding to DTIM)
        prBssInfo->u2ATIMWindow = prBssDesc->u2ATIMWindow;

        //4 <2.I> ERP Information
        if ((prBssInfo->ePhyType == PHY_TYPE_ERP_INDEX) && // Our BSS's PHY_TYPE is ERP now.
            (prBssDesc->fgIsERPPresent)) {

            prBssInfo->fgIsERPPresent = TRUE;
            prBssInfo->ucERP = prBssDesc->ucERP; /* Save the ERP for later check */
        }
        else { /* Some AP, may send ProbeResp without ERP IE. Thus prBssDesc->fgIsERPPresent is FALSE. */
            prBssInfo->fgIsERPPresent = FALSE;
            prBssInfo->ucERP = 0;
        }

        DBGLOG(MGT, INFO, ("prBssInfo->fgIsERPPresent = %d, prBssInfo->ucERP = %02x\n",
            prBssInfo->fgIsERPPresent, prBssInfo->ucERP));

#if CFG_SUPPORT_802_11D
        //4 <2.J> Country inforamtion of the associated AP
        if (prConnSettings->fgMultiDomainCapabilityEnabled) {
            DOMAIN_INFO_ENTRY   rDomainInfo;
            if (domainGetDomainInfoByScanResult(prAdapter, &rDomainInfo)) {
                if (prBssDesc->prIECountry) {
                    prIECountry = prBssDesc->prIECountry;

                    domainParseCountryInfoElem(prIECountry, &prBssInfo->rDomainInfo);

                    /* use the domain get from the BSS info */
                    prBssInfo->fgIsCountryInfoPresent = TRUE;
                    nicSetupOpChnlList(prAdapter, prBssInfo->rDomainInfo.u2CountryCode, FALSE);
                } else {
                    /* use the domain get from the scan result */
                    prBssInfo->fgIsCountryInfoPresent = TRUE;
                    nicSetupOpChnlList(prAdapter, rDomainInfo.u2CountryCode, FALSE);
                }
            }
        }
#endif

    //4 <3> NIC RATE FUNC
        //4 <3.B > WMM Infomation - Setup Variables
#if 0 /* TODO */
        if (prAdapter->fgIsEnableWMM && prConnSettings->fgIsAdHocQoSEnable) {
            prBssInfo->fgIsWmmAssoc = TRUE;
            prTxCtrl->rTxQForVoipAccess = TXQ_AC3;
        }
        else
#endif
        {
            prBssInfo->fgIsWmmAssoc = FALSE;
            prTxCtrl->rTxQForVoipAccess = TXQ_AC1;

            kalMemZero(&prBssInfo->rWmmInfo, sizeof(WMM_INFO_T));
        }

        //4 <3.C> Operational Rate Set & BSS Basic Rate Set
        prBssInfo->u2OperationalRateSet = prBssDesc->u2OperationalRateSet;
        prBssInfo->u2BSSBasicRateSet = prBssDesc->u2BSSBasicRateSet;

        //4 <3.D> Short Preamble
#if 0 /* TODO */
        if ( rPhyAttributes[prBssInfo->ePhyType].fgIsShortPreambleOptionImplemented &&
            ((prConnSettings->ePreambleType == PREAMBLE_TYPE_SHORT) || /* Short Preamble Option Enable is TRUE */
             (prConnSettings->ePreambleType == PREAMBLE_TYPE_AUTO)) ) {

            prBssInfo->fgIsShortPreambleAllowed = TRUE;
            prBssInfo->fgUseShortPreamble = TRUE;
        }
        else
#endif
        {
            if (prBssDesc->u2CapInfo & CAP_INFO_SHORT_PREAMBLE) {
                prBssInfo->fgIsShortPreambleAllowed = TRUE;
                prBssInfo->fgUseShortPreamble = TRUE; /* TODO */
            }
            else {
                prBssInfo->fgIsShortPreambleAllowed = FALSE;
                prBssInfo->fgUseShortPreamble = FALSE;
            }
        }

        //4 <3.D'> Update ERP after Short Preamble.
        if (prBssInfo->fgIsERPPresent) {
            if (!prBssInfo->fgUseShortPreamble) {
                prBssInfo->ucERP |= ERP_INFO_BARKER_PREAMBLE_MODE;
            }
        }

        //4 <3.E> Short Slot Time
        // 7.3.1.4 For IBSS, the Short Slot Time subfield shall be set to 0.
        prBssInfo->fgUseShortSlotTime = FALSE;

        DBGLOG(MGT, INFO, ("prBssInfo->fgUseShortSlotTime = %d\n",
            prBssInfo->fgUseShortSlotTime));

        nicSetSlotTime(prAdapter,
                       prBssInfo->ePhyType,
                       FALSE);


        //4 <3.F> Update Tx Rate for Control Frame
        bssUpdateTxRateForControlFrame(prAdapter);

        //4 <3.G> Save the available Auth Types during Roaming  - Not needed in AdHoc.

        //4 <3.H> Update Parameter for TX Fragmentation Threshold
#if CFG_TX_FRAGMENT
        txFragInfoUpdate(prAdapter);
#endif /* CFG_TX_FRAGMENT */


    //4 <4> Update Default STA_RECORD_T
        {
            UINT_16 u2OperationalRateSet, u2DesiredRateSet;


            /* We merge into a new BSS, so remove entire old records. */
            staRecRemoveStaRecordByPolicy(prAdapter, STA_RECORD_RM_POLICY_ENTIRE);

            /* Add a STA Record for default entry */
            prStaRec = staRecGetStaRecordByAddrOrAddIfNotExist(prAdapter,
                           prBssInfo->aucBSSID);

            /* **NOTE(Kevin): This is the default entry(BSSID), we use STATE_3 to avoid
             * been clean up by aging func.
             */
            prStaRec->ucStaState = STA_STATE_3;

            prStaRec->rRcpi = RCPI_HIGH_BOUND;

            /* Update the record activity time. */
            GET_CURRENT_SYSTIME(&prStaRec->rUpdateTime);

            //4 <4.A> Desired Rate Set, use BasicRateSet for default(BMCAST) entry
            u2OperationalRateSet = (rPhyAttributes[prBssInfo->ePhyType].u2SupportedRateSet &
                                    prBssInfo->u2BSSBasicRateSet);

            u2DesiredRateSet = (u2OperationalRateSet & prConnSettings->u2DesiredRateSet);
            if (u2DesiredRateSet) {
                prStaRec->u2DesiredRateSet = u2DesiredRateSet;
            }
            else {
                /* For Error Handling - The Desired Rate Set is not covered in Operational Rate Set. */
                prStaRec->u2DesiredRateSet = u2OperationalRateSet;
            }

            /* Try to set the best initial rate for default entry */
            if (!rateGetBestInitialRateIndex(prStaRec->u2DesiredRateSet,
                                             prStaRec->rRcpi,
                                             &prStaRec->ucCurrRate1Index)) {

                if (!rateGetLowestRateIndexFromRateSet(prStaRec->u2DesiredRateSet,
                                                       &prStaRec->ucCurrRate1Index)) {
                    ASSERT(0);
                }
            }

            DBGLOG(MGT, TRACE, ("Initial Rate Index for entry ["MACSTR"] = %d\n",
                MAC2STR(prStaRec->aucMacAddr), prStaRec->ucCurrRate1Index));

            //4 <4.B> Preamble Mode
            prStaRec->fgIsShortPreambleOptionEnable =
                prBssInfo->fgUseShortPreamble;

            //4 <4.C> QoS Flag set to FALSE for default entry (BMCAST frames)
            prStaRec->fgIsQoS = FALSE;

            //4 <4.D> Update WLAN Table for default Entry.
            if (nicSetHwBySta(prAdapter, prStaRec) == FALSE) {
                ASSERT(FALSE);
            }

            //4 <4.E> Update Desired Rate Set for BT.
#if CFG_TX_FRAGMENT
            if (prConnSettings->fgIsEnableTxAutoFragmentForBT) {
                txRateSetInitForBT(prAdapter, prStaRec);
            }
#endif /* CFG_TX_FRAGMENT */

            //4 <4.F> Legacy Flag
            prStaRec->fgIsLegacy = FALSE; /* Set to FALSE for default entry */

        }


    //4 <5> Compose Beacon
        kalMemZero(prBssInfo->aucBcnContent, sizeof(prBssInfo->aucBcnContent));
        prBssInfo->u2BcnLen = 0;

        rStatus = ibssPrepareBeaconFrame(prAdapter,
                                         sizeof(prBssInfo->aucBcnContent),
                                         prBssInfo->aucBcnContent,
                                         &prBssInfo->u2BcnLen);

//        prAdapter->fgIsIBSSActive = TRUE;
    }


//4 <6> Update NIC
    //4 <6.A> Update BSSID & Operation Mode
    nicSetupBSS(prAdapter, prBssInfo);

    //4 <6.B> TX AC Parameter and TX/RX Queue Control
    if (prBssInfo->fgIsWmmAssoc) {
        qosWmmInfoInit(&prBssInfo->rWmmInfo,
                       (prBssInfo->ePhyType == PHY_TYPE_HR_DSSS_INDEX) ? TRUE : FALSE);

        qosUpdateWMMParametersAndAssignAllowedACI(prAdapter, &prBssInfo->rWmmInfo);
        ASSERT(0); /* NOTE(Kevin): Not test yet */
    }
    else {
        nicTxNonQoSAssignDefaultAdmittedTXQ(prAdapter);

        nicTxNonQoSUpdateTXQParameters(prAdapter,
                                       prBssInfo->ePhyType);
    }

    //4 <6.C> Setup IBSS' Frequency(Band/Channel)
    nicSwitchChannel(prAdapter, prBssInfo->eBand, prBssInfo->ucChnl, 0);


    //4 <7> Update Peer STA_RECORD_T
    {
        UINT_16 u2OperationalRateSet, u2DesiredRateSet;


        //4 <7.A> Add a STA Record first.
        prStaRec = staRecGetStaRecordByAddrOrAddIfNotExist(prAdapter,
                       prBssDesc->aucSrcAddr);

        /* **NOTE(Kevin): This is not the default entry(BSSID), we won't use STATE_3 to avoid
         * been clean up by aging func.
         */

        /* Update received RCPI */
        prStaRec->rRcpi = prBssDesc->rRcpi;

        /* Update the record activity time. */
        GET_CURRENT_SYSTIME(&prStaRec->rUpdateTime);


        //4 <7.B> Desired Rate Set, use Peer's OperationalRateSet for AdHoc entry
        u2OperationalRateSet = (rPhyAttributes[prBssInfo->ePhyType].u2SupportedRateSet &
                                prBssDesc->u2OperationalRateSet);

        u2DesiredRateSet = (u2OperationalRateSet & prConnSettings->u2DesiredRateSet);
        if (u2DesiredRateSet) {
            prStaRec->u2DesiredRateSet = u2DesiredRateSet;
        }
        else {
            /* For Error Handling - The Desired Rate Set is not covered in Operational Rate Set. */
            prStaRec->u2DesiredRateSet = u2OperationalRateSet;
        }

        /* Try to set the best initial rate for this entry */
        if (!rateGetBestInitialRateIndex(prStaRec->u2DesiredRateSet,
                                         prStaRec->rRcpi,
                                         &prStaRec->ucCurrRate1Index)) {

            if (!rateGetLowestRateIndexFromRateSet(prStaRec->u2DesiredRateSet,
                                                   &prStaRec->ucCurrRate1Index)) {
                ASSERT(0);
            }
        }

        DBGLOG(MGT, TRACE, ("Initial Rate Index for entry ["MACSTR"] = %d\n",
            MAC2STR(prStaRec->aucMacAddr), prStaRec->ucCurrRate1Index));

        //4 <7.C> Preamble Mode
        prStaRec->fgIsShortPreambleOptionEnable =
            prBssInfo->fgUseShortPreamble;

        //4 <7.D> QoS Flag
        prStaRec->fgIsQoS = prBssInfo->fgIsWmmAssoc;

        //4 <7.E> Update WLAN Table for default Entry.
        if (nicSetHwBySta(prAdapter, prStaRec) == FALSE) {
            ASSERT(FALSE);
        }

        //4 <7.F> Update Desired Rate Set for BT.
#if CFG_TX_FRAGMENT
        if (prConnSettings->fgIsEnableTxAutoFragmentForBT) {
            txRateSetInitForBT(prAdapter, prStaRec);
        }
#endif /* CFG_TX_FRAGMENT */


        //4 <7.G> Legacy Flag
        prStaRec->fgIsLegacy =
            (prBssDesc->ePhyType == PHY_TYPE_HR_DSSS_INDEX) ? TRUE : FALSE;
    }


//4 <8> Start to sending Beacons.
    nicStartBeacon(prAdapter);


//4 <9> Indicate media status connect.
    if (prAdapter->eConnectionState != MEDIA_STATE_CONNECTED) {

        prAdapter->eConnectionState = MEDIA_STATE_CONNECTED;
        prAdapter->eConnectionStateIndicated = MEDIA_STATE_CONNECTED;

        kalIndicateStatusAndComplete(prAdapter->prGlueInfo,
            WLAN_STATUS_MEDIA_CONNECT,
            (PVOID)0,
            0);
        }

    return rStatus;

} /* end of ibssMergeIBSS() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will stop sending Beacon Frames.
*
* \param[in] prAdapter          Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
ibssStopIBSS (
    IN P_ADAPTER_T prAdapter
    )
{
    ASSERT(prAdapter);


    nicStopBeacon(prAdapter);

    return;
} /* end of ibssStopIBSS() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function is used to handle BSS Descriptors and STA Records when we
*        leave current IBSS.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
ibssLeave (
    IN P_ADAPTER_T prAdapter
    )
{
    P_BSS_INFO_T prBssInfo;


    ASSERT(prAdapter);
    prBssInfo = &prAdapter->rBssInfo;

#if 0 /* CR1790: only remove this record when beacon lost is confirmed */
    //4 <1> Remove current BSS' BSS_DESC
    /* Because there is no any association process for Ad-Hoc, thus we should remove
     * this Scan Record immediately and scan for a new IBSS after back to SEARCH
     * State.
     */
    scanRemoveBssDescByBssid(prAdapter, prBssInfo->aucBSSID);
#endif
#if 0
    //4 <1> Flush all BSS_DESC_T including current BSS's BSS_DESC_T
    scanRemoveBssDescsByPolicy(prAdapter, SCAN_RM_POLICY_ENTIRE);
#endif

    //4 <2> Remove all PEER STA_RECORDs
    staRecRemoveStaRecordForIBSS(prAdapter);

    //4 <3> Remove STATE_3 flag of all the associated STA_RECORD_Ts (AP, DLSs)
    if (!prAdapter->fgIsIBSSActive) {
        staRecRemoveStateFlagOfAllStaRecords(prAdapter);
    }

    //4 <3> Stop sending Beacon and change Operation Mode to Infrastructure Mode.
    nicExistIBSS(prAdapter);

    return;
} /* end of ibssLeave() */



