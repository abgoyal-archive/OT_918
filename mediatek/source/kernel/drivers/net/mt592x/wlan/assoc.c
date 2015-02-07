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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/assoc.c#2 $
*/

/*! \file   "assoc.c"
    \brief  There is the collection of association-related functions

    This file includes the association-related functions.
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
** $Log: assoc.c $
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\34 2009-08-18 22:56:10 GMT mtk01090
**  Add Linux SDIO (with mmc core) support.
**  Add Linux 2.6.21, 2.6.25, 2.6.26.
**  Fix compile warning in Linux.
**  \main\maintrunk.MT5921\33 2009-07-06 20:33:07 GMT mtk01088
**  adding the code for wpi packet handler
**  \main\maintrunk.MT5921\32 2009-02-25 15:48:28 GMT mtk01461
**  Add fgIsPrivacyEnabled in PEER_BSS_INFO_T to check privacy consistency
**  \main\maintrunk.MT5921\31 2009-01-11 23:20:36 GMT mtk01461
**  Add assert if Basic Rate Set == 0
**  \main\maintrunk.MT5921\30 2008-12-19 17:18:50 GMT mtk01461
**  Fix the problem that assoc req frame may contain no Supported Rate IE.
**  \main\maintrunk.MT5921\29 2008-11-28 12:03:02 GMT mtk01088
**  fixed some lint warning
**  \main\maintrunk.MT5921\28 2008-08-10 18:48:13 GMT mtk01461
**  Update for Driver Review
**  \main\maintrunk.MT5921\27 2008-07-16 22:47:28 GMT mtk01461
**  Add error handling for abnormal(small) mgmt frame.
**  \main\maintrunk.MT5921\26 2008-06-17 16:32:33 GMT mtk01425
**  1. Modify nicTxService for Tx Enhancement
**  \main\maintrunk.MT5921\25 2008-03-31 09:53:09 GMT mtk01461
**  Revise assocSendDisAssocFrame by adding callback func
**  \main\maintrunk.MT5921\24 2008-03-30 16:49:08 GMT mtk01461
**  Update all comments and change prototype of send Disassoc frame
**  \main\maintrunk.MT5921\23 2008-03-13 14:28:19 GMT mtk01461
**  JOIN should handle status not sucess case instead of timeout event.
**  \main\maintrunk.MT5921\22 2008-03-12 09:52:05 GMT mtk01461
**  Remove type case in MSDU_INFO_OBJ_INIT
**
**  \main\maintrunk.MT5921\21 2008-02-29 15:53:46 GMT mtk01088
**  rename the function name
**  \main\maintrunk.MT5921\20 2008-02-29 15:19:06 GMT mtk01088
**  handle the send disassociate frame
**  \main\maintrunk.MT5921\19 2008-02-27 12:12:16 GMT mtk01461
**  Add Hidden SSID Support
**  \main\maintrunk.MT5921\18 2008-02-01 09:25:48 GMT mtk01385
**  1. Fix WinCE 4.2 compiling error.
**  \main\maintrunk.MT5921\17 2008-01-07 15:06:26 GMT mtk01461
**  Add SDIO Enhance Support
**  Add PhyType & AdHocMode Selection Support
**  \main\maintrunk.MT5921\16 2008-01-05 21:06:07 GMT mtk01084
**  use default Listen interval whenever TIM IE is not exist (DTIM period = 0)
**  \main\maintrunk.MT5921\15 2007-12-11 00:09:52 GMT mtk01461
**  Add process of disassoc frame
**  \main\maintrunk.MT5921\14 2007-12-04 18:09:23 GMT mtk01461
**  Update MSDU_INFO_T init process
**  \main\maintrunk.MT5921\13 2007-11-08 20:21:37 GMT mtk01088
**  add compose disassociation frame function
**  \main\maintrunk.MT5921\12 2007-11-06 20:22:27 GMT mtk01088
**  enable assoc privacy bit for join a privacy enabled AP
**  \main\maintrunk.MT5921\11 2007-11-02 00:57:09 GMT mtk01461
**  Unify TX Path for Normal and IBSS Power Save + IBSS neighbor learning
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
* \brief This function is used to compose the Capability Info Field.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
* \param[in] prBssDesc  Pointer to the BSS Descriptor.
*
* \retval Capability Info Field
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ UINT_16
assocBuildCapabilityInfo (
    IN P_ADAPTER_T prAdapter,
    IN P_BSS_DESC_T prBssDesc
    )
{
    P_CONNECTION_SETTINGS_T prConnSettings;
    UINT_16 u2CapInfo;

    DEBUGFUNC("assocBuildCapabilityInfo");

    ASSERT(prAdapter);
    ASSERT(prBssDesc);
    prConnSettings = &prAdapter->rConnSettings;

    /* Set up our requested capabilities. */
    u2CapInfo = CAP_INFO_ESS;
    u2CapInfo |= CAP_CF_STA_NOT_POLLABLE;

    /* 7.3.1.4 */
    if ( (rPhyAttributes[prBssDesc->ePhyType].fgIsShortPreambleOptionImplemented) &&
        ( (prConnSettings->ePreambleType == PREAMBLE_TYPE_SHORT) || /* Short Preamble Option Enable is TRUE */
         ((prConnSettings->ePreambleType == PREAMBLE_TYPE_AUTO) &&
          (prBssDesc->u2CapInfo & CAP_INFO_SHORT_PREAMBLE)) ) ) {

        /* Case I: Implemented == TRUE and Short Preamble Option Enable == TRUE.
         * Case II: Implemented == TRUE and Short Preamble == AUTO (depends on
         *          BSS_DESC_T's capability)
         */
        u2CapInfo |= CAP_INFO_SHORT_PREAMBLE;
    }

    if (rPhyAttributes[prBssDesc->ePhyType].fgIsShortSlotTimeOptionImplemented &&
        prConnSettings->fgIsShortSlotTimeOptionEnable) {
        u2CapInfo |= CAP_INFO_SHORT_SLOT_TIME;
    }

    if (prBssDesc->u2CapInfo & CAP_INFO_PRIVACY)
        u2CapInfo |= CAP_INFO_PRIVACY;

    DBGLOG(JOIN, INFO, ("Compose Capability = 0x%04x for Target BSS ["MACSTR"].\n",
        u2CapInfo, MAC2STR(prBssDesc->aucBSSID)));

    return u2CapInfo;

} /* end of assocBuildCapabilityInfo() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function is used to compose Information Elements for Association
*        Request Frame.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
* \param[in] prBssDesc  Pointer to the BSS Descriptor.
* \param[in] pucBuffer  Pointer to the frame buffer.
*
* \retval Total IE length
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ UINT_16
assocBuildReAssocReqFrameIEs (
    IN P_ADAPTER_T prAdapter,
    IN P_BSS_DESC_T prBssDesc,
    IN PUINT_8 pucBuffer
    )
{
    UINT_8 aucAllSupportedRates[RATE_NUM] = {0};
    UINT_8 ucAllSupportedRatesLen;
    UINT_8 ucSupRatesLen;
    UINT_8 ucExtSupRatesLen;
    UINT_16 u2IeTotalLen = 0;
    UINT_16 u2SupportedRateSet;
    UINT_8 ucIeLength;

    DEBUGFUNC("assocBuildReAssocReqFrameIEs");

    ASSERT(prAdapter);
    ASSERT(prBssDesc);
    ASSERT(pucBuffer);

    /* Fill the SSID element. */
    SSID_IE(pucBuffer)->ucId = ELEM_ID_SSID;

    if (prBssDesc->fgIsHiddenSSID) {
        /* NOTE(Kevin): This is for the case of Passive Scan and the target BSS didn't
         * broadcast SSID on its Beacon Frame.
         */
        COPY_SSID(SSID_IE(pucBuffer)->aucSSID,
                  SSID_IE(pucBuffer)->ucLength,
                  prAdapter->rConnSettings.aucSSID,
                  prAdapter->rConnSettings.ucSSIDLen);

        pucBuffer += ELEM_HDR_LEN + prAdapter->rConnSettings.ucSSIDLen;
        u2IeTotalLen += ELEM_HDR_LEN + prAdapter->rConnSettings.ucSSIDLen;
    }
    else {
        COPY_SSID(SSID_IE(pucBuffer)->aucSSID,
                  SSID_IE(pucBuffer)->ucLength,
                  prBssDesc->aucSSID,
                  prBssDesc->ucSSIDLen);

        pucBuffer += ELEM_HDR_LEN + prBssDesc->ucSSIDLen;
        u2IeTotalLen += ELEM_HDR_LEN + prBssDesc->ucSSIDLen;
    }


    /* NOTE(Kevin 2008/12/19): 16.3.6.3 MLME-ASSOCIATE.indication -
     * SupportedRates - The set of data rates that are supported by the STA
     * that is requesting association.
     * Original(Portable Driver): Only send the Rates that we'll support. 
     * New: Send the Phy Rates if the result of following & operation == NULL.
     */
    //rateGetDataRatesFromRateSet((prBssDesc->u2OperationalRateSet &
    //                             rPhyAttributes[prBssDesc->ePhyType].u2SupportedRateSet),

    u2SupportedRateSet = (prBssDesc->u2OperationalRateSet &
                          rPhyAttributes[prBssDesc->ePhyType].u2SupportedRateSet);

    ASSERT(u2SupportedRateSet);

    if (!u2SupportedRateSet) {
        u2SupportedRateSet = rPhyAttributes[prBssDesc->ePhyType].u2SupportedRateSet;
    }

    rateGetDataRatesFromRateSet(u2SupportedRateSet,
                                   0x0, /*(UINT_16)NULL*/
                                   aucAllSupportedRates,
                                   &ucAllSupportedRatesLen);

    ucSupRatesLen = ((ucAllSupportedRatesLen > ELEM_MAX_LEN_SUP_RATES) ?
                     ELEM_MAX_LEN_SUP_RATES : ucAllSupportedRatesLen);

    ucExtSupRatesLen = ucAllSupportedRatesLen - ucSupRatesLen;


    /* Fill the Supported Rates element. */
    if (ucSupRatesLen) {
        SUP_RATES_IE(pucBuffer)->ucId = ELEM_ID_SUP_RATES;
        SUP_RATES_IE(pucBuffer)->ucLength = ucSupRatesLen;
        kalMemCopy(SUP_RATES_IE(pucBuffer)->aucSupportedRates,
                   aucAllSupportedRates,
                   ucSupRatesLen);

        pucBuffer += ELEM_HDR_LEN + ucSupRatesLen;
        u2IeTotalLen += ELEM_HDR_LEN + ucSupRatesLen;
    }


    /* Fill the Extended Supported Rates element. */
    if (ucExtSupRatesLen) {

        EXT_SUP_RATES_IE(pucBuffer)->ucId = ELEM_ID_EXTENDED_SUP_RATES;
        EXT_SUP_RATES_IE(pucBuffer)->ucLength = ucExtSupRatesLen;

        kalMemCopy(EXT_SUP_RATES_IE(pucBuffer)->aucExtSupportedRates,
                   &aucAllSupportedRates[ucSupRatesLen],
                   ucExtSupRatesLen);

        pucBuffer += ELEM_HDR_LEN + ucExtSupRatesLen;
        u2IeTotalLen += ELEM_HDR_LEN + ucExtSupRatesLen;
    }

#if SUPPORT_WAPI
    /* ASSOC INFO IE ID: 0x68 */
    if (prAdapter->prGlueInfo->u2WapiAssocInfoIESz) {
        kalMemCopy(pucBuffer, prAdapter->prGlueInfo->aucWapiAssocInfoIEs, prAdapter->prGlueInfo->u2WapiAssocInfoIESz /* sizeof(PARAM_WAPI_ASSOC_INFO_T */);
        pucBuffer+= prAdapter->prGlueInfo->u2WapiAssocInfoIESz /* sizeof(PARAM_WAPI_ASSOC_INFO_T */;
        u2IeTotalLen += prAdapter->prGlueInfo->u2WapiAssocInfoIESz;
    }
#endif

    ucIeLength = rsnGenerateWPARSNIE(prAdapter, prBssDesc, pucBuffer);
    u2IeTotalLen += ucIeLength;
    pucBuffer += ucIeLength;

    /* Fill the WMM Information element, if the current AP supports WMM. */
    if (prAdapter->fgIsEnableWMM &&
        (prBssDesc->ucWmmFlag & WMM_FLAG_SUPPORT_WMM)) {


        DBGLOG(MGT, TRACE, ("WMM FLAG: 0x%02x\n", prBssDesc->ucWmmFlag));

        ucIeLength = qosConstructWMMInfoElem(prAdapter, prBssDesc->ucWmmFlag, pucBuffer);

        u2IeTotalLen += ucIeLength;
        pucBuffer += ucIeLength;
    }

    return u2IeTotalLen;

} /* end of assocBuildReAssocReqFrameIEs() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will compose the (Re)Association Request frame
*
* \param[in] prAdapter          Pointer to the Adapter structure.
* \param[in] prBssDesc          Pointer to the BSS Descriptor.
* \param[in] pucBuffer          Pointer to the frame buffer.
* \param[in] fgIsReAssoc        A flag to indicate to use Reassoc Req.
* \param[out] pu2WlanHeaderLen  Pointer to store the result of frame header length.
* \param[out] pu2WlanBodyLen    Pointer to store the result of frame body length.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ VOID
assocComposeReAssocReqFrame (
    IN P_ADAPTER_T prAdapter,
    IN P_BSS_DESC_T prBssDesc,
    IN PUINT_8 pucBuffer,
    IN BOOLEAN fgIsReAssoc,
    OUT PUINT_16 pu2WlanHeaderLen,
    OUT PUINT_16 pu2WlanBodyLen
    )
{
    P_WLAN_ASSOC_REQ_FRAME_T prAssocFrame;
    PUINT_8 pucIEsBuffer;
    UINT_16 u2FrameCtrl;
    UINT_16 u2CapInfo;
    UINT_16 u2ListenInterval;
    UINT_16 u2WlanBodyLen;

    DEBUGFUNC("assocComposeReAssocReqFrame");

    ASSERT(prAdapter);
    ASSERT(prBssDesc);
    ASSERT(pucBuffer);
    ASSERT(pu2WlanHeaderLen);
    ASSERT(pu2WlanBodyLen);

    prAssocFrame = (P_WLAN_ASSOC_REQ_FRAME_T)pucBuffer;

    //4 <1> Compose the frame header of the (Re)Association Request  frame.
    /* Fill the Frame Control field. */
    if (fgIsReAssoc) {
        u2FrameCtrl = MAC_FRAME_REASSOC_REQ;
    } else {
        u2FrameCtrl = MAC_FRAME_ASSOC_REQ;
    }
    WLAN_SET_FIELD_16(&prAssocFrame->u2FrameCtrl, u2FrameCtrl);

    /* Fill the DA field with Target BSSID. */
    COPY_MAC_ADDR(prAssocFrame->aucDestAddr, prBssDesc->aucBSSID);

    /* Fill the SA field with our MAC Address. */
    COPY_MAC_ADDR(prAssocFrame->aucSrcAddr, prAdapter->aucMacAddress);

    /* Fill the BSSID field with Target BSSID. */
    COPY_MAC_ADDR(prAssocFrame->aucBSSID, prBssDesc->aucBSSID);

    /* Clear the SEQ/FRAG_NO field(HW won't overide the FRAG_NO, so we need to clear it). */
    prAssocFrame->u2SeqCtrl = 0;


    //4 <2> Compose the frame body's common fixed field part of the (Re)Association Request  frame.
    u2CapInfo = assocBuildCapabilityInfo(prAdapter, prBssDesc);

    /* Fill the Capability Information field. */
    WLAN_SET_FIELD_16(&prAssocFrame->u2CapInfo, u2CapInfo);


    /* Calculate the listen interval for the maximum power mode. Currently, we
       set it to the value 2 times DTIM period. */
    if (prBssDesc->ucDTIMPeriod) {
        u2ListenInterval = prBssDesc->ucDTIMPeriod * DEFAULT_LISTEN_INTERVAL_BY_DTIM_PERIOD;
    }
    else{
        DBGLOG(MGT, TRACE, ("Use default listen interval\n"));
        u2ListenInterval = DEFAULT_LISTEN_INTERVAL;
    }

    /* Fill the Listen Interval field. */
    WLAN_SET_FIELD_16(&prAssocFrame->u2ListenInterval, u2ListenInterval);


    //4 <3> Update the MAC header/body length.
    *pu2WlanHeaderLen = WLAN_MAC_MGMT_HEADER_LEN;
    u2WlanBodyLen = CAP_INFO_FIELD_LEN +
                    LISTEN_INTERVAL_FIELD_LEN;

    //4 <4> Compose the Current AP Address field for ReAssociation Request  frame.
    /* Fill the Current AP Address field. */
    if (fgIsReAssoc) {
        P_BSS_INFO_T prBssInfo = &prAdapter->rBssInfo;

        P_WLAN_REASSOC_REQ_FRAME_T prReAssocFrame =
            (P_WLAN_REASSOC_REQ_FRAME_T)prAssocFrame;

        COPY_MAC_ADDR(prReAssocFrame->aucCurrentAPAddr, prBssInfo->aucBSSID);
        u2WlanBodyLen += CURR_AP_ADDR_FIELD_LEN;

        /* Update the Start Address of IEs Buffer */
        pucIEsBuffer = prReAssocFrame->aucInfoElem;
    }
    else {
        /* Update the Start Address of IEs Buffer */
        pucIEsBuffer = prAssocFrame->aucInfoElem;
    }

    //4 <5> Compose the frame body's IEs of the (Re)Association Request  frame.
    u2WlanBodyLen += assocBuildReAssocReqFrameIEs(prAdapter, prBssDesc, pucIEsBuffer);

    //4 <6> Update the Reassociation request information
    kalUpdateReAssocReqInfo(prAdapter->prGlueInfo,
                            (PUINT_8)&prAssocFrame->u2CapInfo,
                            u2WlanBodyLen,
                            fgIsReAssoc);

    *pu2WlanBodyLen = u2WlanBodyLen;

    return;
} /* end of assocComposeReAssocReqFrame() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will send the (Re)Association Request frame
*
* \param[in] prAdapter          Pointer to the Adapter structure.
* \param[in] prBssDesc          Pointer to the BSS Descriptor.
* \param[in] fgIsReAssoc        A flag to indicate to use Reassoc Req.
*
* \retval WLAN_STATUS_RESOURCES No available resource for frame composing.
* \retval WLAN_STATUS_FAILURE   If encounter BUS access failure, report from TX Module.
* \retval WLAN_STATUS_SUCCESS   Successfully send frame to TX Module
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
assocSendReAssocReqFrame (
    IN P_ADAPTER_T prAdapter,
    IN P_BSS_DESC_T prBssDesc,
    IN BOOLEAN fgIsReAssoc
    )
{
    P_MSDU_INFO_T prMsduInfo;
    P_MGT_PACKET_T prMgtPacket;
    UINT_16 u2WlanHeaderLen;
    UINT_16 u2WlanBodyLen;
    UINT_16 u2EstimatedFrameLen;
    UINT_32 u4Status = WLAN_STATUS_SUCCESS;

    DEBUGFUNC("assocSendReAssocReqFrame");


    ASSERT(prAdapter);
    ASSERT(prBssDesc);

    //4 <1> Allocate MSDU_INFO_T
    prMsduInfo = nicTxAllocMsduInfo(prAdapter, TCM);
    if (prMsduInfo == (P_MSDU_INFO_T)NULL) {
        DBGLOG(JOIN, WARN, ("No MSDU_INFO_T to send (Re)Association Request.\n"));
        return WLAN_STATUS_RESOURCES;
    }

    //4 <2> Allocate Frame Buffer (in MGT_PACKET_T) for (Re)Association Frame
    //4 whsu: notice WPS and 802.11r IE
#if SUPPORT_WAPI
    if (fgIsReAssoc) {
        u2EstimatedFrameLen = WLAN_MAC_MGMT_HEADER_LEN + \
                              CAP_INFO_FIELD_LEN + \
                              LISTEN_INTERVAL_FIELD_LEN + \
                              CURR_AP_ADDR_FIELD_LEN + \
                              (ELEM_HDR_LEN + ELEM_MAX_LEN_SSID) + \
                              (ELEM_HDR_LEN + ELEM_MAX_LEN_SUP_RATES) + \
                              (ELEM_HDR_LEN + (RATE_NUM - ELEM_MAX_LEN_SUP_RATES)) + \
                              (ELEM_HDR_LEN + ELEM_MAX_LEN_WAPI_ASSOC_INFO) + \
                              (ELEM_HDR_LEN + ELEM_MAX_LEN_WPA_RSN) + \
                              (ELEM_HDR_LEN + ELEM_MAX_LEN_WMM_INFO);
    }
    else {
        u2EstimatedFrameLen = WLAN_MAC_MGMT_HEADER_LEN + \
                              CAP_INFO_FIELD_LEN + \
                              LISTEN_INTERVAL_FIELD_LEN + \
                              (ELEM_HDR_LEN + ELEM_MAX_LEN_SSID) + \
                              (ELEM_HDR_LEN + ELEM_MAX_LEN_SUP_RATES) + \
                              (ELEM_HDR_LEN + (RATE_NUM - ELEM_MAX_LEN_SUP_RATES)) + \
                              (ELEM_MAX_LEN_WAPI_ASSOC_INFO) + \
                              (ELEM_HDR_LEN + ELEM_MAX_LEN_WPA_RSN) + \
                              (ELEM_HDR_LEN + ELEM_MAX_LEN_WMM_INFO);
    }
#else
    
    if (fgIsReAssoc) {
        u2EstimatedFrameLen = WLAN_MAC_MGMT_HEADER_LEN + \
                              CAP_INFO_FIELD_LEN + \
                              LISTEN_INTERVAL_FIELD_LEN + \
                              CURR_AP_ADDR_FIELD_LEN + \
                              (ELEM_HDR_LEN + ELEM_MAX_LEN_SSID) + \
                              (ELEM_HDR_LEN + ELEM_MAX_LEN_SUP_RATES) + \
                              (ELEM_HDR_LEN + (RATE_NUM - ELEM_MAX_LEN_SUP_RATES)) + \
                              (ELEM_HDR_LEN + ELEM_MAX_LEN_WPA_RSN) + \
                              (ELEM_HDR_LEN + ELEM_MAX_LEN_WMM_INFO);
    }
    else {
        u2EstimatedFrameLen = WLAN_MAC_MGMT_HEADER_LEN + \
                              CAP_INFO_FIELD_LEN + \
                              LISTEN_INTERVAL_FIELD_LEN + \
                              (ELEM_HDR_LEN + ELEM_MAX_LEN_SSID) + \
                              (ELEM_HDR_LEN + ELEM_MAX_LEN_SUP_RATES) + \
                              (ELEM_HDR_LEN + (RATE_NUM - ELEM_MAX_LEN_SUP_RATES)) + \
                              (ELEM_HDR_LEN + ELEM_MAX_LEN_WPA_RSN) + \
                              (ELEM_HDR_LEN + ELEM_MAX_LEN_WMM_INFO);
    }
#endif
    /* TODO(Kevin): Update u2EstimatedFrameLen according WPA/RSN/WMM(ok)/WMMSA status */


    prMgtPacket = mgtBufAllocateMgtPacket(prAdapter, (UINT_32)u2EstimatedFrameLen);
    if (prMgtPacket == (P_MGT_PACKET_T)NULL) {
        nicTxReturnMsduInfo(prAdapter, prMsduInfo);
        DBGLOG(JOIN, WARN, ("No buffer to send (Re)Association Request.\n"));
        return WLAN_STATUS_RESOURCES;
    }


    //4 <3> Compose Association Request frame in MGT_PACKET_T.
    assocComposeReAssocReqFrame(prAdapter,
                                prBssDesc,
                                MGT_PACKET_GET_BUFFER(prMgtPacket),
                                fgIsReAssoc,
                                &u2WlanHeaderLen,
                                &u2WlanBodyLen);

    //4 <4> Update the frame length to the packet descriptor (MGT_PACKET_T).
    mgtPacketPut(prMgtPacket, (u2WlanHeaderLen + u2WlanBodyLen));

    //4 <5> Update information in MSDU_INFO_T for TX Module.
    /* Bcz JOIN FSM will handle this frame, so set with lifetime never expire */
    MSDU_INFO_OBJ_INIT(prMsduInfo, \
                       TRUE, \
                       TRUE, \
                       (PVOID)prMgtPacket, \
                       0, \
                       TXQ_TCM, \
                       (UINT_8)u2WlanHeaderLen, \
                       u2WlanBodyLen, \
                       (MSDU_INFO_CTRL_FLAG_SPECIFY_AC | \
                        MSDU_INFO_CTRL_FLAG_BASIC_RATE | \
                        MSDU_INFO_CTRL_FLAG_LIFETIME_NEVER_EXPIRE), \
                       arbFsmRunEventJoinTxDone, \
                       (OS_SYSTIME)NULL, \
                       NULL \
                       );

    //4 <6> Inform ARB to send this Authentication Request frame.
    DBGLOG(JOIN, LOUD, ("Send Assocation Request frame\n"));
    /* TODO(Kevin): We should handle the WLAN_STATUS_RESOURCE & WLAN_STATUS_FAILURE
     *       separately for BUS_ERROR.
     */
    if ((u4Status = arbFsmRunEventTxMmpdu(prAdapter,prMsduInfo)) != WLAN_STATUS_PENDING) {

        if(u4Status != WLAN_STATUS_SUCCESS){
            mgtBufFreeMgtPacket(prAdapter, prMgtPacket);

            nicTxReturnMsduInfo(prAdapter, prMsduInfo);

            DBGLOG(JOIN, ERROR, ("Send Auth Request frame fail.\n"));

            return WLAN_STATUS_FAILURE;
        }
    }

    return WLAN_STATUS_SUCCESS;

} /* end of assocSendReAssocReqFrame() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will compose the Disassociation frame
*
* \param[in] prAdapter          Pointer to the Adapter structure.
* \param[in] pucBuffer          Pointer to the frame buffer.
* \param[in] aucBSSID           Given BSSID.
* \param[in] u2ReasonCode       A reason code to indicate why to leave BSS.
* \param[out] pu2WlanHeaderLen  Pointer to store the result of frame header length.
* \param[out] pu2WlanBodyLen    Pointer to store the result of frame body length.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ VOID
assocComposeDisAssocFrame (
    IN P_ADAPTER_T prAdapter,
    IN PUINT_8 pucBuffer,
    IN UINT_8 aucBSSID[],
    IN UINT_16 u2ReasonCode,
    OUT PUINT_16 pu2WlanHeaderLen,
    OUT PUINT_16 pu2WlanBodyLen
    )
{
    P_WLAN_DISASSOC_FRAME_T prDisAssocFrame;
    UINT_16 u2FrameCtrl;
    UINT_16 u2WlanBodyLen;


    ASSERT(prAdapter);
    ASSERT(pucBuffer);
    ASSERT(aucBSSID);
    ASSERT(pu2WlanHeaderLen);
    ASSERT(pu2WlanBodyLen);

    prDisAssocFrame = (P_WLAN_DISASSOC_FRAME_T)pucBuffer;

    //4 <1> Compose the frame header of the DisAssociation  frame.
    /* Fill the Frame Control field. */
    u2FrameCtrl = MAC_FRAME_DISASSOC;

    WLAN_SET_FIELD_16(&prDisAssocFrame->u2FrameCtrl, u2FrameCtrl);

    /* Fill the DA field with Target BSSID. */
    COPY_MAC_ADDR(prDisAssocFrame->aucDestAddr, aucBSSID);

    /* Fill the SA field with our MAC Address. */
    COPY_MAC_ADDR(prDisAssocFrame->aucSrcAddr, prAdapter->aucMacAddress);

    /* Fill the BSSID field with Target BSSID. */
    COPY_MAC_ADDR(prDisAssocFrame->aucBSSID, aucBSSID);

    /* Clear the SEQ/FRAG_NO field(HW won't overide the FRAG_NO, so we need to clear it). */
    prDisAssocFrame->u2SeqCtrl = 0;

    //4 <2> Compose the frame body's fixed field part of the Disassociation frame.
    /* Fill the Reason Code field. */
    WLAN_SET_FIELD_16(&prDisAssocFrame->u2ReasonCode, u2ReasonCode);

    //4 <3> Update the MAC header/body length.
    *pu2WlanHeaderLen = WLAN_MAC_MGMT_HEADER_LEN;
    u2WlanBodyLen = REASON_CODE_FIELD_LEN;

    *pu2WlanBodyLen = u2WlanBodyLen;

    return;
} /* end of assocComposeDisAssocFrame() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will send the Disassociation frame
*
* \param[in] prAdapter          Pointer to the Adapter structure.
* \param[in] aucBSSID           Given BSSID.
* \param[in] u2ReasonCode       A reason code to indicate why to leave BSS.
* \param[in] pfTxDoneHandler    TX Done call back function
*
* \retval WLAN_STATUS_RESOURCES No available resource for frame composing.
* \retval WLAN_STATUS_FAILURE   If encounter BUS access failure, report from TX Module.
* \retval WLAN_STATUS_SUCCESS   Successfully send frame to TX Module
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
assocSendDisAssocFrame (
    IN P_ADAPTER_T prAdapter,
    IN UINT_8 aucBSSID[],
    IN UINT_16 u2ReasonCode,
    IN PFN_TX_DONE_HANDLER pfTxDoneHandler
    )
{
    P_MSDU_INFO_T prMsduInfo;
    P_MGT_PACKET_T prMgtPacket;
    UINT_16 u2WlanHeaderLen;
    UINT_16 u2WlanBodyLen;
    UINT_16 u2EstimatedFrameLen;
    UINT_32 u4Status = WLAN_STATUS_SUCCESS;

    DEBUGFUNC("assocSendDisAssocFrame");


    ASSERT(prAdapter);
    ASSERT(aucBSSID);

    //4 <1> Allocate MSDU_INFO_T
    prMsduInfo = nicTxAllocMsduInfo(prAdapter, TCM);
    if (prMsduInfo == (P_MSDU_INFO_T)NULL) {
        DBGLOG(JOIN, WARN, ("No MSDU_INFO_T to send Disassociation frame.\n"));
        return WLAN_STATUS_RESOURCES;
    }

    //4 <2> Allocate Frame Buffer (in MGT_PACKET_T) for (Re)Association Frame
    //4 whsu: notice WPS and 802.11r IE
    u2EstimatedFrameLen = WLAN_MAC_MGMT_HEADER_LEN + REASON_CODE_FIELD_LEN;

    prMgtPacket = mgtBufAllocateMgtPacket(prAdapter, (UINT_32)u2EstimatedFrameLen);
    if (prMgtPacket == (P_MGT_PACKET_T)NULL) {
        nicTxReturnMsduInfo(prAdapter, prMsduInfo);
        DBGLOG(JOIN, WARN, ("No buffer to send Disassociation Request.\n"));
        return WLAN_STATUS_RESOURCES;
    }


    //4 <3> Compose Association Request frame in MGT_PACKET_T.
    assocComposeDisAssocFrame(prAdapter,
                              MGT_PACKET_GET_BUFFER(prMgtPacket),
                              aucBSSID,
                              u2ReasonCode,
                              &u2WlanHeaderLen,
                              &u2WlanBodyLen);

    //4 <4> Update the frame length to the packet descriptor (MGT_PACKET_T).
    mgtPacketPut(prMgtPacket, (u2WlanHeaderLen + u2WlanBodyLen));

    //4 <5> Update information in MSDU_INFO_T for TX Module.
    MSDU_INFO_OBJ_INIT(prMsduInfo, \
                       TRUE, \
                       TRUE, \
                       (PVOID)prMgtPacket, \
                       0, \
                       TXQ_AC3, \
                       (UINT_8)u2WlanHeaderLen, \
                       u2WlanBodyLen, \
                       (MSDU_INFO_CTRL_FLAG_SPECIFY_AC | \
                        MSDU_INFO_CTRL_FLAG_BASIC_RATE | \
                        MSDU_INFO_CTRL_FLAG_LIFETIME_NEVER_EXPIRE), \
                       pfTxDoneHandler, \
                       (OS_SYSTIME)NULL, \
                       NULL \
                       );

    //4 <6> Inform ARB to send this Disassociation frame.
    DBGLOG(JOIN, LOUD, ("Send DisAssocation frame\n"));
    /* TODO(Kevin): We should handle the WLAN_STATUS_RESOURCE & WLAN_STATUS_FAILURE
     *       separately for BUS_ERROR.
     */
    if ((u4Status = arbFsmRunEventTxMmpdu(prAdapter,prMsduInfo)) != WLAN_STATUS_PENDING) {

        if(u4Status != WLAN_STATUS_SUCCESS){
            mgtBufFreeMgtPacket(prAdapter, prMgtPacket);

            nicTxReturnMsduInfo(prAdapter, prMsduInfo);

            DBGLOG(JOIN, ERROR, ("Send Disassociation frame fail.\n"));

            return WLAN_STATUS_FAILURE;
        }

    }

    return WLAN_STATUS_SUCCESS;

} /* end of assocSendDisAssocFrame() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will check the TX (Re)Association Request frame for
*        JOIN event handling.
*
* \param[in] prAdapter          Pointer to the Adapter structure.
* \param[in] prMsduInfo         Pointer of MSDU_INFO_T
* \param[in] fgIsReAssoc        A flag to indicate to check for Reassoc Req.
*
* \retval WLAN_STATUS_FAILURE   This is not the frame we should handle at current state.
* \retval WLAN_STATUS_SUCCESS   This is the frame we should handle.
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
assocCheckTxReAssocReqFrame (
    IN P_ADAPTER_T prAdapter,
    IN P_MSDU_INFO_T prMsduInfo,
    IN BOOLEAN fgIsReAssoc
    )
{
    P_WLAN_ASSOC_REQ_FRAME_T prAssocFrame;
    UINT_16 u2TxFrameCtrl;

    DEBUGFUNC("assocCheckTxReAssocReqFrame");

    ASSERT(prAdapter);
    ASSERT(prMsduInfo);
    
    if (prMsduInfo->fgIsFromInternalProtocolStack) {
        prAssocFrame = (P_WLAN_ASSOC_REQ_FRAME_T)(MGT_PACKET_GET_BUFFER(prMsduInfo->pvPacket));
    }
    else {
        DBGLOG(JOIN, WARN,
            ("An Association Request Frame is not from Internal Protocol Stack.\n"));
        ASSERT(0);
        return WLAN_STATUS_FAILURE;
    }


    WLAN_GET_FIELD_16(&prAssocFrame->u2FrameCtrl, &u2TxFrameCtrl)
    u2TxFrameCtrl &= MASK_FRAME_TYPE;
    if (fgIsReAssoc) {
        if (u2TxFrameCtrl != MAC_FRAME_REASSOC_REQ) {
            return WLAN_STATUS_FAILURE;
        }
    }
    else {
        if (u2TxFrameCtrl != MAC_FRAME_ASSOC_REQ) {
            return WLAN_STATUS_FAILURE;
        }
    }

    return WLAN_STATUS_SUCCESS;

} /* end of assocCheckTxReAssocReqFrame() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will parse and process the incoming (Re)Association
*        Response frame.
*
* \param[in] prAdapter          Pointer to the Adapter structure.
* \param[in] prSwRfb            Pointer to SW RFB data structure.
* \param[in] prPeerBssInfo      Pointer to the temporary BSS Information structure.
* \param[in] fgIsReAssoc        A flag to indicate if we expect the Reassoc Respnse.
* \param[out] pu2StatusCode     Pointer to store the Status Code from (Re)Association Resp.
*
* \retval WLAN_STATUS_FAILURE   This is not the frame we should handle at current state.
* \retval WLAN_STATUS_SUCCESS   This is the frame we should handle.
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
assocProcessRxReAssocRspFrame (
    IN P_ADAPTER_T prAdapter,
    IN P_SW_RFB_T prSwRfb,
    IN P_PEER_BSS_INFO_T prPeerBssInfo,
    IN BOOLEAN fgIsReAssoc,
    OUT PUINT_16 pu2StatusCode
    )
{
    P_WLAN_ASSOC_RSP_FRAME_T prAssocRspFrame;
    P_IE_SUPPORTED_RATE_T prIeSupportedRate = (P_IE_SUPPORTED_RATE_T)NULL;
    P_IE_EXT_SUPPORTED_RATE_T prIeExtSupportedRate = (P_IE_EXT_SUPPORTED_RATE_T)NULL;
    UINT_16 u2RxFrameCtrl;
    UINT_16 u2RxCapInfo;
    UINT_16 u2RxStatusCode;
    UINT_16 u2RxAssocId;
    UINT_16 u2IEsLen;
    PUINT_8 pucIEsBuffer;
    UINT_16 u2Offset;

    DEBUGFUNC("assocProcessRxReAssocRspFrame");


    ASSERT(prAdapter);
    ASSERT(prSwRfb);
    ASSERT(prPeerBssInfo);
    ASSERT(pu2StatusCode);

    if (prSwRfb->u2FrameLength < (WLAN_MAC_MGMT_HEADER_LEN +
                                  CAP_INFO_FIELD_LEN +
                                  STATUS_CODE_FIELD_LEN +
                                  AID_FIELD_LEN)) {
        ASSERT(0);
        return WLAN_STATUS_FAILURE;
    }

    DBGLOG(JOIN, LOUD, ("prSwRfb->u2FrameLength = %d\n", prSwRfb->u2FrameLength));

    //4 <1> locate the (Re)Assocation Resp Frame.
    prAssocRspFrame = (P_WLAN_ASSOC_RSP_FRAME_T) prSwRfb->pvHeader;

    //4 <2> Parse the Header of (Re)Assocation Resp Frame.
    WLAN_GET_FIELD_16(&prAssocRspFrame->u2FrameCtrl, &u2RxFrameCtrl);
    u2RxFrameCtrl &= MASK_FRAME_TYPE;
    if (fgIsReAssoc) {
        if (u2RxFrameCtrl != MAC_FRAME_REASSOC_RSP) {
            return WLAN_STATUS_FAILURE;
        }
    }
    else {
        if (u2RxFrameCtrl != MAC_FRAME_ASSOC_RSP) {
            return WLAN_STATUS_FAILURE;
        }
    }

    /* Check if this Assoc Resp Frame is coming from Target BSSID */
    if (UNEQUAL_MAC_ADDR(prAssocRspFrame->aucSrcAddr, prPeerBssInfo->aucBSSID)) {
        DBGLOG(JOIN, TRACE, ("Ignore Assoc Resp Frame from other BSS ["MACSTR"]\n",
            MAC2STR(prAssocRspFrame->aucSrcAddr)));
        return WLAN_STATUS_FAILURE;
    }

    //4 <3> Parse the Fixed Fields of (Re)Assocation Resp Frame Body.
    WLAN_GET_FIELD_16(&prAssocRspFrame->u2StatusCode, &u2RxStatusCode);
    *pu2StatusCode = u2RxStatusCode;

    //4 <4> Ignore CAP_INFO, AID & IEs part if the Status Code is not SUCCESSFUL.
    if (u2RxStatusCode != STATUS_CODE_SUCCESSFUL) {

        DBGLOG(JOIN, LOUD, ("Assoc Failure - Status Code = %d.\n", u2RxStatusCode));

        /* NOTE(Kevin): We should return SUCCESS to indicate that the current frame
         * is parsed OK, the Status Code will be handled by JOIN FSM.
         */
        return WLAN_STATUS_SUCCESS;
    }

    //4 <5> Parse the Fixed Fields of (Re)Assocation Resp Frame Body.
    WLAN_GET_FIELD_16(&prAssocRspFrame->u2CapInfo, &u2RxCapInfo);
    if (u2RxCapInfo & CAP_INFO_PRIVACY) {
        prPeerBssInfo->fgIsPrivacyEnabled = TRUE;
    }
    else {
        prPeerBssInfo->fgIsPrivacyEnabled = FALSE;
    }

    if (u2RxCapInfo & CAP_INFO_SHORT_PREAMBLE) {
        prPeerBssInfo->fgIsShortPreambleAllowed = TRUE;
    }
    else {
        prPeerBssInfo->fgIsShortPreambleAllowed = FALSE;
    }

    if (u2RxCapInfo & CAP_INFO_SHORT_SLOT_TIME) {
        prPeerBssInfo->fgUseShortSlotTime = TRUE;
    }
    else {
        prPeerBssInfo->fgUseShortSlotTime = FALSE;
    }

    WLAN_GET_FIELD_16(&prAssocRspFrame->u2AssocId, &u2RxAssocId);
    /* Note: We didn't remove the AID MSB */
    if (u2RxAssocId < (AID_MIN_VALUE | AID_MSB) ||
        u2RxAssocId > (AID_MAX_VALUE | AID_MSB)) {
        DBGLOG(JOIN, WARN, ("Invalid AID: 0x%04x\n", u2RxAssocId));
    }
    prPeerBssInfo->u2AssocId = u2RxAssocId & AID_MASK;



    //4 <5> Parse the Information Elements of (Re)Assocation Resp Frame Body.
    pucIEsBuffer = &prAssocRspFrame->aucInfoElem[0];
    u2IEsLen = prSwRfb->u2FrameLength - (WLAN_MAC_MGMT_HEADER_LEN +
                                         CAP_INFO_FIELD_LEN +
                                         STATUS_CODE_FIELD_LEN +
                                         AID_FIELD_LEN);

    IE_FOR_EACH(pucIEsBuffer, u2IEsLen, u2Offset) {
        switch (IE_ID(pucIEsBuffer)) {
        case ELEM_ID_SUP_RATES:
            prIeSupportedRate = SUP_RATES_IE(pucIEsBuffer);
            break;

        case ELEM_ID_EXTENDED_SUP_RATES:
            prIeExtSupportedRate = EXT_SUP_RATES_IE(pucIEsBuffer);
            break;

        case ELEM_ID_VENDOR:
            /* NOTE(Kevin): Skip parse WMM in order to save some times if we know
             * we didn't enable the WMM at driver side.
             */
            if (prAdapter->fgIsEnableWMM) {
                UINT_8 ucOuiType;
                UINT_16 u2SubTypeVersion;

                if (parseCheckForWFAInfoElem(pucIEsBuffer, &ucOuiType, &u2SubTypeVersion)) {
                    /* Parse WMM capability */
                    if ((ucOuiType == VENDOR_OUI_TYPE_WMM) &&
                        (u2SubTypeVersion == VENDOR_OUI_SUBTYPE_VERSION_WMM_PARAM)) {

                        if (!qosParseWMMParamElem(pucIEsBuffer, &prPeerBssInfo->rWmmInfo)) {
                            /* Clear the WMM capability if parse error */
                            prPeerBssInfo->rWmmInfo.ucWmmFlag = 0;
                        }
                    }
                }
            }
            break;

        default:
            break;
        }
    }

    rateGetRateSetFromIEs(prIeSupportedRate,
                          prIeExtSupportedRate,
                          &prPeerBssInfo->u2OperationalRateSet,
                          &prPeerBssInfo->u2BSSBasicRateSet,
                          &prPeerBssInfo->fgIsUnknownBSSBasicRate);

    if (prPeerBssInfo->fgIsUnknownBSSBasicRate) {
        DBGLOG(JOIN, WARN, ("BSS has unknown BSS Basic Rate: Operational Rate Set = %04x, BSS Basic Rate Set = %04x\n",
            prPeerBssInfo->u2OperationalRateSet, prPeerBssInfo->u2BSSBasicRateSet));
    }


    /* TODO(Kevin): put the information into GLUE Layer ? */
    /* Update the information in the structure used to query and set
       OID_802_11_ASSOCIATION_INFORMATION. */
    kalUpdateReAssocRspInfo(prAdapter->prGlueInfo,
                           (PUINT_8)&prAssocRspFrame->u2CapInfo,
                           (UINT_32)(prSwRfb->u2FrameLength - WLAN_MAC_MGMT_HEADER_LEN));

    return WLAN_STATUS_SUCCESS;

} /* end of assocProcessRxReAssocRspFrame() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will parse and process the incoming Disassociation
*        frame if the given BSSID is matched.
*
* \param[in] prAdapter          Pointer to the Adapter structure.
* \param[in] prSwRfb            Pointer to SW RFB data structure.
* \param[in] aucBSSID           Given BSSID
* \param[out] pu2ReasonCode     Pointer to store the Reason Code from Disassociation.
*
* \retval WLAN_STATUS_FAILURE   This is not the frame we should handle at current state.
* \retval WLAN_STATUS_SUCCESS   This is the frame we should handle.
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
assocProcessRxDisassocFrame (
    IN P_ADAPTER_T prAdapter,
    IN P_SW_RFB_T prSwRfb,
    IN UINT_8 aucBSSID[],
    OUT PUINT_16 pu2ReasonCode
    )
{
    P_WLAN_DISASSOC_FRAME_T prDisassocFrame;
    UINT_16 u2RxFrameCtrl;
    UINT_16 u2RxReasonCode;

    DEBUGFUNC("assocProcessRxDisassocFrame");

    ASSERT(prAdapter);
    ASSERT(prSwRfb);
    ASSERT(aucBSSID);
    ASSERT(pu2ReasonCode);

    //4 <1> locate the Deauthentication Frame.
    prDisassocFrame = (P_WLAN_DISASSOC_FRAME_T) prSwRfb->pvHeader;

    //4 <2> Parse the Header of Authentication Frame.
    WLAN_GET_FIELD_16(&prDisassocFrame->u2FrameCtrl, &u2RxFrameCtrl)
    u2RxFrameCtrl &= MASK_FRAME_TYPE;
    if (u2RxFrameCtrl != MAC_FRAME_DISASSOC) {
        return WLAN_STATUS_FAILURE;
    }

    if (prSwRfb->u2FrameLength < (WLAN_MAC_MGMT_HEADER_LEN +
                                  REASON_CODE_FIELD_LEN)) {
        ASSERT(0);
        return WLAN_STATUS_FAILURE;
    }

    /* Check if this Disassoc Frame is coming from Target BSSID */
    if (UNEQUAL_MAC_ADDR(prDisassocFrame->aucSrcAddr, aucBSSID)) {
        DBGLOG(JOIN, LOUD, ("Ignore Disassoc Frame from other BSS ["MACSTR"]\n",
            MAC2STR(prDisassocFrame->aucSrcAddr)));
        return WLAN_STATUS_FAILURE;
    }

    //4 <3> Parse the Fixed Fields of Deauthentication Frame Body.
    WLAN_GET_FIELD_16(&prDisassocFrame->u2ReasonCode, &u2RxReasonCode);
    *pu2ReasonCode = u2RxReasonCode;

    return WLAN_STATUS_SUCCESS;

} /* end of assocProcessRxDisassocFrame() */

