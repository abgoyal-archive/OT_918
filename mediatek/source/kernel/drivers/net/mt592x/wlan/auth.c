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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/auth.c#2 $
*/

/*! \file   "auth.c"
    \brief  There is the collection of authentication-related functions

    This file includes the authentication-related functions.
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
** $Log: auth.c $
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\20 2009-05-23 14:45:38 GMT mtk01088
**  let the de-auth frame send as assigned AC 
**  \main\maintrunk.MT5921\19 2008-11-28 12:03:16 GMT mtk01088
**  fixed some lint warning
**  \main\maintrunk.MT5921\18 2008-07-16 22:47:34 GMT mtk01461
**  Add error handling for abnormal(small) mgmt frame.
**  \main\maintrunk.MT5921\17 2008-06-17 16:34:15 GMT mtk01425
**  1. Modify nicTxService for SDIO Tx Aggregation
**  \main\maintrunk.MT5921\16 2008-03-31 09:53:43 GMT mtk01461
**  Revise authSendDeauthFrame by adding callback func
**  \main\maintrunk.MT5921\15 2008-03-30 16:49:11 GMT mtk01461
**  Update all comments and change prototype of send Deauthframe
**  \main\maintrunk.MT5921\14 2008-03-13 14:28:38 GMT mtk01461
**  JOIN should handle status not sucess case instead of timeout event.
**  \main\maintrunk.MT5921\13 2008-03-12 09:52:07 GMT mtk01461
**  Remove type case in MSDU_INFO_OBJ_INIT
**
**  \main\maintrunk.MT5921\12 2008-02-01 09:27:46 GMT mtk01385
**  1. Fix WinCE 4.2 compiling error.
**  \main\maintrunk.MT5921\11 2007-12-11 00:09:54 GMT mtk01461
**  Add process of authentication frame
**  \main\maintrunk.MT5921\10 2007-12-04 18:09:24 GMT mtk01461
**  Update MSDU_INFO_T init process
**  \main\maintrunk.MT5921\9 2007-11-02 00:57:11 GMT mtk01461
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
* \brief This function will compose the Authentication frame
*
* \param[in] prAdapter              Pointer to the Adapter structure.
* \param[in] pucBuffer              Pointer to the frame buffer.
* \param[in] aucBSSID               Given BSSID.
* \param[in] u2AuthAlgNum           Authentication Algorithm Number
* \param[in] u2TransactionSeqNum    Transaction Sequence Number
* \param[in] u2StatusCode           Status Code
* \param[in] pucChallengeText       Pointer to the Challenge Text Buffer
* \param[in] ucChallengeTextLen     Length of the Challenge Text
* \param[out] pu2WlanHeaderLen      Pointer to store the result of frame header length.
* \param[out] pu2WlanBodyLen        Pointer to store the result of frame body length.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ VOID
authComposeAuthFrame (
    IN P_ADAPTER_T prAdapter,
    IN PUINT_8 pucBuffer,
    IN UINT_8 aucBSSID[],
    IN UINT_16 u2AuthAlgNum,
    IN UINT_16 u2TransactionSeqNum,
    IN UINT_16 u2StatusCode,
    IN PUINT_8 pucChallengeText,
    IN UINT_8 ucChallengeTextLen,
    OUT PUINT_16 pu2WlanHeaderLen,
    OUT PUINT_16 pu2WlanBodyLen
    )
{
    P_WLAN_AUTH_FRAME_T prAuthFrame;
    UINT_16 u2WlanBodyLen;
    UINT_16 u2FrameCtrl;


    ASSERT(prAdapter);
    ASSERT(pucBuffer);
    ASSERT(aucBSSID);
    ASSERT(pucChallengeText);
    ASSERT(pu2WlanHeaderLen);
    ASSERT(pu2WlanBodyLen);

    prAuthFrame = (P_WLAN_AUTH_FRAME_T)pucBuffer;

    //4 <1> Compose the frame header of the Authentication frame.
    /* Fill the Frame Control field. */
    u2FrameCtrl = MAC_FRAME_AUTH;

    /* If this frame is the third frame in the shared key authentication
     * sequence, it shall be encrypted.
     */
    if ((u2AuthAlgNum == AUTH_ALGORITHM_NUM_SHARED_KEY) &&
        (u2TransactionSeqNum == AUTH_TRANSACTION_SEQ_3) &&
        (pucChallengeText != NULL) &&
        (ucChallengeTextLen > 0)) {

        u2FrameCtrl |= MASK_FC_PROTECTED_FRAME; /* HW will also detect this bit for applying encryption */
    }
    WLAN_SET_FIELD_16(&prAuthFrame->u2FrameCtrl, u2FrameCtrl);

    /* Fill the DA field with Target BSSID. */
    COPY_MAC_ADDR(prAuthFrame->aucDestAddr, aucBSSID);

    /* Fill the SA field with our MAC Address. */
    COPY_MAC_ADDR(prAuthFrame->aucSrcAddr, prAdapter->aucMacAddress);

    /* Fill the BSSID field with Target BSSID. */
    COPY_MAC_ADDR(prAuthFrame->aucBSSID, aucBSSID);

    /* Clear the SEQ/FRAG_NO field(HW won't overide the FRAG_NO, so we need to clear it). */
    prAuthFrame->u2SeqCtrl = 0;


    //4 <2> Compose the frame body's fixed field part of the Authentication frame.
    /* Fill the Authentication Algorithm Number field. */
    WLAN_SET_FIELD_16(&prAuthFrame->u2AuthAlgNum, u2AuthAlgNum);

    /* Fill the Authentication Transaction Sequence Number field. */
    WLAN_SET_FIELD_16(&prAuthFrame->u2AuthTransSeqNo, u2TransactionSeqNum);

    /* Fill the Status Code field. */
    WLAN_SET_FIELD_16(&prAuthFrame->u2StatusCode, u2StatusCode);

    //4 <3> Update the MAC header/body length.
    *pu2WlanHeaderLen = WLAN_MAC_MGMT_HEADER_LEN;
    u2WlanBodyLen = AUTH_ALGORITHM_NUM_FIELD_LEN +
                    AUTH_TRANSACTION_SEQENCE_NUM_FIELD_LEN +
                    STATUS_CODE_FIELD_LEN;


    //4 <4> Compose the frame body's IEs part of the Authentication frame.
    /* Fill the Challenge Text field if the challenge text is provided by the
       caller. */
    if ((pucChallengeText != NULL) && (ucChallengeTextLen > 0)) {
        P_IE_CHALLENGE_TEXT_T prIeChallengeText =
            (P_IE_CHALLENGE_TEXT_T)&prAuthFrame->aucInfoElem[0];

        ASSERT(ucChallengeTextLen <= ELEM_MAX_LEN_CHALLENGE_TEXT);

        prIeChallengeText->ucId = ELEM_ID_CHALLENGE_TEXT;
        prIeChallengeText->ucLength = ucChallengeTextLen;

        kalMemCopy(prIeChallengeText->aucChallengeText,
                   pucChallengeText,
                   ucChallengeTextLen);

        u2WlanBodyLen += ELEM_HDR_LEN + (UINT_16)ucChallengeTextLen;
    }

    *pu2WlanBodyLen = u2WlanBodyLen;

    return;
} /* end of authComposeAuthFrame() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will send the Authenticiation frame
*
* \param[in] prAdapter              Pointer to the Adapter structure.
* \param[in] prPeerBssInfo          Pointer to the temporary BSS Information structure.
* \param[in] u2AuthAlgNum           Authentication Algorithm Number
* \param[in] u2TransactionSeqNum    Transaction Sequence Number
*
* \retval WLAN_STATUS_RESOURCES No available resource for frame composing.
* \retval WLAN_STATUS_FAILURE   If encounter BUS access failure, report from TX Module.
* \retval WLAN_STATUS_SUCCESS   Successfully send frame to TX Module
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
authSendAuthFrame (
    IN P_ADAPTER_T prAdapter,
    IN P_PEER_BSS_INFO_T prPeerBssInfo,
    IN UINT_16 u2AuthAlgNum,
    IN UINT_16 u2TransactionSeqNum
    )
{
    P_MSDU_INFO_T prMsduInfo;
    P_MGT_PACKET_T prMgtPacket;

    UINT_16 u2WlanHeaderLen;
    UINT_16 u2WlanBodyLen;
    UINT_16 u2EstimatedFrameLen;
    UINT_32 u4Status = WLAN_STATUS_SUCCESS;

    DEBUGFUNC("authSendAuthFrame");


    ASSERT(prAdapter);
    ASSERT(prPeerBssInfo);

    //4 <1> Allocate MSDU_INFO_T
    prMsduInfo = nicTxAllocMsduInfo(prAdapter, TCM);
    if (prMsduInfo == (P_MSDU_INFO_T)NULL) {
        DBGLOG(JOIN, WARN, ("No MSDU_INFO_T to send Auth Request.\n"));
        return WLAN_STATUS_RESOURCES;
    }

    //4 <2> Allocate Frame Buffer (in MGT_PACKET_T) for Authentication Frame
    /* Only consider SEQ_1 & SEQ_3 */
    if ((u2AuthAlgNum == AUTH_ALGORITHM_NUM_SHARED_KEY) &&
        (u2TransactionSeqNum == AUTH_TRANSACTION_SEQ_3)) {
        u2EstimatedFrameLen = (WLAN_MAC_MGMT_HEADER_LEN +
                               AUTH_ALGORITHM_NUM_FIELD_LEN +
                               AUTH_TRANSACTION_SEQENCE_NUM_FIELD_LEN +
                               STATUS_CODE_FIELD_LEN +
                               (ELEM_HDR_LEN + ELEM_MAX_LEN_CHALLENGE_TEXT));
    }
    else {
        u2EstimatedFrameLen = (WLAN_MAC_MGMT_HEADER_LEN +
                               AUTH_ALGORITHM_NUM_FIELD_LEN +
                               AUTH_TRANSACTION_SEQENCE_NUM_FIELD_LEN +
                               STATUS_CODE_FIELD_LEN);
    }

    prMgtPacket = mgtBufAllocateMgtPacket(prAdapter, (UINT_32)u2EstimatedFrameLen);
    if (prMgtPacket == (P_MGT_PACKET_T)NULL) {
        nicTxReturnMsduInfo(prAdapter, prMsduInfo);
        DBGLOG(JOIN, WARN, ("No buffer to send Auth Request.\n"));
        return WLAN_STATUS_RESOURCES;
    }


    //4 <3> Compose Authentication Request frame in MGT_PACKET_T.
    authComposeAuthFrame(prAdapter,
                         MGT_PACKET_GET_BUFFER(prMgtPacket),
                         prPeerBssInfo->aucBSSID,
                         u2AuthAlgNum,
                         u2TransactionSeqNum,
                         STATUS_CODE_SUCCESSFUL,
                         prPeerBssInfo->rIeChallengeText.aucChallengeText,
                         prPeerBssInfo->rIeChallengeText.ucLength,
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
    DBGLOG(JOIN, LOUD, ("Send Auth Request frame\n"));
    /* TODO(Kevin): We should handle the WLAN_STATUS_RESOURCE & WLAN_STATUS_FAILURE
     *       separately for BUS_ERROR.
     */
    if ( (u4Status = arbFsmRunEventTxMmpdu(prAdapter,prMsduInfo)) != WLAN_STATUS_PENDING) {

        if(u4Status != WLAN_STATUS_SUCCESS) {
            mgtBufFreeMgtPacket(prAdapter, prMgtPacket);

            nicTxReturnMsduInfo(prAdapter, prMsduInfo);

            DBGLOG(JOIN, ERROR, ("Send Auth Request frame fail.\n"));

            return WLAN_STATUS_FAILURE;

        }

    }

    return WLAN_STATUS_SUCCESS;

} /* end of authSendAuthFrame() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will compose the Deauthentication frame
*
* \param[in] prAdapter              Pointer to the Adapter structure.
* \param[in] pucBuffer              Pointer to the frame buffer.
* \param[in] aucBSSID               Given BSSID.
* \param[in] u2ReasonCode           A reason code to indicate why to leave BSS.
* \param[out] pu2WlanHeaderLen      Pointer to store the result of frame header length.
* \param[out] pu2WlanBodyLen        Pointer to store the result of frame body length.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ VOID
authComposeDeauthFrame (
    IN P_ADAPTER_T prAdapter,
    IN PUINT_8 pucBuffer,
    IN UINT_8 aucBSSID[],
    IN UINT_16 u2ReasonCode,
    OUT PUINT_16 pu2WlanHeaderLen,
    OUT PUINT_16 pu2WlanBodyLen
    )
{
    P_WLAN_DEAUTH_FRAME_T prDeauthFrame;
    UINT_16 u2FrameCtrl;


    ASSERT(prAdapter);
    ASSERT(pucBuffer);
    ASSERT(aucBSSID);
    ASSERT(pu2WlanHeaderLen);
    ASSERT(pu2WlanBodyLen);

    prDeauthFrame = (P_WLAN_DEAUTH_FRAME_T)pucBuffer;

    //4 <1> Compose the frame header of the Deauthentication frame.
    /* Fill the Frame Control field. */
    u2FrameCtrl = MAC_FRAME_DEAUTH;
    WLAN_SET_FIELD_16(&prDeauthFrame->u2FrameCtrl, u2FrameCtrl);

    /* Fill the DA field with Target BSSID. */
    COPY_MAC_ADDR(prDeauthFrame->aucDestAddr, aucBSSID);

    /* Fill the SA field with our MAC Address. */
    COPY_MAC_ADDR(prDeauthFrame->aucSrcAddr, prAdapter->aucMacAddress);

    /* Fill the BSSID field with Target BSSID. */
    COPY_MAC_ADDR(prDeauthFrame->aucBSSID, aucBSSID);

    /* Clear the SEQ/FRAG_NO field(HW won't overide the FRAG_NO, so we need to clear it). */
    prDeauthFrame->u2SeqCtrl = 0;


    //4 <2> Compose the frame body's fixed field part of the Authentication frame.
    /* Fill the Status Code field. */
    WLAN_SET_FIELD_16(&prDeauthFrame->u2ReasonCode, u2ReasonCode);

    //4 <3> Update the MAC header/body length.
    *pu2WlanHeaderLen = WLAN_MAC_MGMT_HEADER_LEN;
    *pu2WlanBodyLen = REASON_CODE_FIELD_LEN;

    return;
} /* end of authComposeDeauthFrame() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will send the Deauthenticiation frame
*
* \param[in] prAdapter          Pointer to the Adapter structure.
* \param[in] aucBSSID           Given BSSID.
* \param[in] u2ReasonCode       A reason code to indicate why to leave BSS.
* \param[in] ucTQ               Which Tx Queue to send frame.
* \param[in] pfTxDoneHandler    TX Done call back function
*
* \retval WLAN_STATUS_RESOURCES No available resource for frame composing.
* \retval WLAN_STATUS_FAILURE   If encounter BUS access failure, report from TX Module.
* \retval WLAN_STATUS_SUCCESS   Successfully send frame to TX Module
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
authSendDeauthFrame (
    IN P_ADAPTER_T prAdapter,
    IN UINT_8 aucBSSID[],
    IN UINT_16 u2ReasonCode,
    IN UINT_8 ucTQ,
    IN PFN_TX_DONE_HANDLER pfTxDoneHandler
    )
{
    P_MSDU_INFO_T prMsduInfo;
    P_MGT_PACKET_T prMgtPacket;

    UINT_16 u2WlanHeaderLen;
    UINT_16 u2WlanBodyLen;
    UINT_16 u2EstimatedFrameLen;
    UINT_32 u4Status = WLAN_STATUS_SUCCESS;

    DEBUGFUNC("authSendDeauthFrame");


    ASSERT(prAdapter);
    ASSERT(aucBSSID);

    //4 <1> Allocate MSDU_INFO_T
    prMsduInfo = nicTxAllocMsduInfo(prAdapter, ucTQ);
    if (prMsduInfo == (P_MSDU_INFO_T)NULL) {
        DBGLOG(JOIN, WARN, ("No MSDU_INFO_T to send Deauth Request.\n"));
        return WLAN_STATUS_RESOURCES;
    }

    //4 <2> Allocate Frame Buffer (in MGT_PACKET_T) for Deauthentication Frame
    u2EstimatedFrameLen = (WLAN_MAC_MGMT_HEADER_LEN + REASON_CODE_FIELD_LEN);

    prMgtPacket = mgtBufAllocateMgtPacket(prAdapter, (UINT_32)u2EstimatedFrameLen);
    if (prMgtPacket == (P_MGT_PACKET_T)NULL) {
        nicTxReturnMsduInfo(prAdapter, prMsduInfo);
        DBGLOG(JOIN, WARN, ("No buffer to send Deauth Request.\n"));
        return WLAN_STATUS_RESOURCES;
    }

    //4 <3> Compose Deauthentication Request frame in MGT_PACKET_T.
    authComposeDeauthFrame(prAdapter,
                           MGT_PACKET_GET_BUFFER(prMgtPacket),
                           aucBSSID,
                           u2ReasonCode,
                           &u2WlanHeaderLen,
                           &u2WlanBodyLen);

    //4 <4> Update the frame length to the packet descriptor (MGT_PACKET_T).
    mgtPacketPut(prMgtPacket, (u2WlanHeaderLen + u2WlanBodyLen));


    //4 <5> Update information in MSDU_INFO_T for TX Module.
    //4 <Todo> The callback function should become argument for module
    MSDU_INFO_OBJ_INIT(prMsduInfo, \
                       TRUE, \
                       TRUE, \
                       (PVOID)prMgtPacket, \
                       0, \
                       ucTQ, \
                       (UINT_8)u2WlanHeaderLen, \
                       u2WlanBodyLen, \
                       (MSDU_INFO_CTRL_FLAG_SPECIFY_AC | \
                        MSDU_INFO_CTRL_FLAG_BASIC_RATE | \
                        MSDU_INFO_CTRL_FLAG_LIFETIME_NEVER_EXPIRE), \
                       pfTxDoneHandler, \
                       (OS_SYSTIME)NULL, \
                       NULL \
                       );

    //4 <6> Inform ARB to send this Deauthentication Request frame.
    DBGLOG(JOIN, LOUD, ("Send Deauth Request frame\n"));
    /* TODO(Kevin): We should handle the WLAN_STATUS_RESOURCE & WLAN_STATUS_FAILURE
     *       separately for BUS_ERROR.
     */
    if ((u4Status = arbFsmRunEventTxMmpdu(prAdapter,prMsduInfo)) != WLAN_STATUS_PENDING) {

        if(u4Status != WLAN_STATUS_SUCCESS) {
            mgtBufFreeMgtPacket(prAdapter, prMgtPacket);

            nicTxReturnMsduInfo(prAdapter, prMsduInfo);

            DBGLOG(JOIN, ERROR, ("Send Deauth Request frame fail.\n"));

            return WLAN_STATUS_FAILURE;
        }


    }

    return WLAN_STATUS_SUCCESS;

} /* end of authSendDeauthFrame() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will check the TX Authentication frame for JOIN event
*        handling.
*
* \param[in] prAdapter              Pointer to the Adapter structure.
* \param[in] prMsduInfo             Pointer of MSDU_INFO_T
* \param[in] u2AuthAlgNum           Authentication Algorithm Number
* \param[in] u2TransactionSeqNum    Transaction Sequence Number
*
* \retval WLAN_STATUS_FAILURE   This is not the frame we should handle at current state.
* \retval WLAN_STATUS_SUCCESS   This is the frame we should handle.
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
authCheckTxAuthFrame (
    IN P_ADAPTER_T  prAdapter,
    IN P_MSDU_INFO_T prMsduInfo,
    IN UINT_16 u2AuthAlgNum,
    IN UINT_16 u2TransactionSeqNum
    )
{
    P_WLAN_AUTH_FRAME_T prAuthFrame;
    UINT_16 u2TxFrameCtrl;
    UINT_16 u2TxAuthAlgNum;
    UINT_16 u2TxTransactionSeqNum;

    DEBUGFUNC("authCheckTxAuthFrame");


    ASSERT(prAdapter);
    ASSERT(prMsduInfo);

    if (prMsduInfo->fgIsFromInternalProtocolStack) {
        prAuthFrame = (P_WLAN_AUTH_FRAME_T)(MGT_PACKET_GET_BUFFER(prMsduInfo->pvPacket));
    }
    else {
        DBGLOG(JOIN, WARN,
            ("An Authentication Frame is not from Internal Protocol Stack.\n"));
        ASSERT(0);
        return WLAN_STATUS_FAILURE;
    }

    WLAN_GET_FIELD_16(&prAuthFrame->u2FrameCtrl, &u2TxFrameCtrl)
    u2TxFrameCtrl &= MASK_FRAME_TYPE;
    if (u2TxFrameCtrl != MAC_FRAME_AUTH) {
        return WLAN_STATUS_FAILURE;
    }

    WLAN_GET_FIELD_16(&prAuthFrame->u2AuthAlgNum, &u2TxAuthAlgNum)
    if (u2TxAuthAlgNum != u2AuthAlgNum) {
        return WLAN_STATUS_FAILURE;
    }

    WLAN_GET_FIELD_16(&prAuthFrame->u2AuthTransSeqNo, &u2TxTransactionSeqNum)
    if (u2TxTransactionSeqNum != u2TransactionSeqNum) {
        return WLAN_STATUS_FAILURE;
    }

    return WLAN_STATUS_SUCCESS;

} /* end of authCheckTxAuthFrame() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will parse and process the incoming Authentication frame.
*
* \param[in] prAdapter              Pointer to the Adapter structure.
* \param[in] prSwRfb                Pointer to SW RFB data structure.
* \param[in] prPeerBssInfo          Pointer to the temporary BSS Information structure.
* \param[in] u2AuthAlgNum           Authentication Algorithm Number
* \param[in] u2TransactionSeqNum    Transaction Sequence Number
* \param[out] pu2StatusCode         Pointer to store the Status Code from Authentication.
*
* \retval WLAN_STATUS_FAILURE   This is not the frame we should handle at current state.
* \retval WLAN_STATUS_SUCCESS   This is the frame we should handle.
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
authProcessRxAuthFrame (
    IN P_ADAPTER_T prAdapter,
    IN P_SW_RFB_T prSwRfb,
    IN P_PEER_BSS_INFO_T prPeerBssInfo,
    IN UINT_16 u2AuthAlgNum,
    IN UINT_16 u2TransactionSeqNum,
    OUT PUINT_16 pu2StatusCode
    )
{
    P_WLAN_AUTH_FRAME_T prAuthFrame;
    UINT_16 u2RxFrameCtrl;
    UINT_16 u2RxAuthAlgNum;
    UINT_16 u2RxTransactionSeqNum;
    UINT_16 u2RxStatusCode;

    DEBUGFUNC("authProcessRxAuthFrame");


    ASSERT(prAdapter);
    ASSERT(prSwRfb);
    ASSERT(prPeerBssInfo);
    ASSERT(pu2StatusCode);

    //4 <1> locate the Authentication Frame.
    prAuthFrame = (P_WLAN_AUTH_FRAME_T) prSwRfb->pvHeader;

    //4 <2> Parse the Header of Authentication Frame.
    WLAN_GET_FIELD_16(&prAuthFrame->u2FrameCtrl, &u2RxFrameCtrl)
    u2RxFrameCtrl &= MASK_FRAME_TYPE;
    if (u2RxFrameCtrl != MAC_FRAME_AUTH) {
        return WLAN_STATUS_FAILURE;
    }

    if (prSwRfb->u2FrameLength < (WLAN_MAC_MGMT_HEADER_LEN +
                                  AUTH_ALGORITHM_NUM_FIELD_LEN +
                                  AUTH_TRANSACTION_SEQENCE_NUM_FIELD_LEN +
                                  STATUS_CODE_FIELD_LEN)) {
        ASSERT(0);
        return WLAN_STATUS_FAILURE;
    }

    /* Check if this Auth Frame is coming from Target BSSID */
    if (UNEQUAL_MAC_ADDR(prAuthFrame->aucSrcAddr, prPeerBssInfo->aucBSSID)) {
        DBGLOG(JOIN, LOUD, ("Ignore Auth Frame from other BSS ["MACSTR"]\n",
            MAC2STR(prAuthFrame->aucSrcAddr)));
        return WLAN_STATUS_FAILURE;
    }

    //4 <3> Parse the Fixed Fields of Authentication Frame Body.
    WLAN_GET_FIELD_16(&prAuthFrame->u2AuthAlgNum, &u2RxAuthAlgNum);
    if (u2RxAuthAlgNum != u2AuthAlgNum) {
        DBGLOG(JOIN, LOUD, ("Discard Auth frame with auth type = %d, current = %d\n",
            u2RxAuthAlgNum, u2AuthAlgNum));
        return WLAN_STATUS_FAILURE;
    }

    WLAN_GET_FIELD_16(&prAuthFrame->u2AuthTransSeqNo, &u2RxTransactionSeqNum);
    if (u2RxTransactionSeqNum != u2TransactionSeqNum) {
        DBGLOG(JOIN, LOUD, ("Discard Auth frame with Transaction Seq No = %d\n",
            u2RxTransactionSeqNum));
        return WLAN_STATUS_FAILURE;
    }

    WLAN_GET_FIELD_16(&prAuthFrame->u2StatusCode, &u2RxStatusCode);
    *pu2StatusCode = u2RxStatusCode;

    //4 <4> Ignore IE_CHALLENGE_TEXT part if the Status Code is not SUCCESSFUL.
    if (u2RxStatusCode != STATUS_CODE_SUCCESSFUL) {

        DBGLOG(JOIN, LOUD, ("Auth Failure - Status Code = %d.\n", u2RxStatusCode));
        /* NOTE(Kevin): We should return SUCCESS to indicate that the current frame
         * is parsed OK, the Status Code will be handled by JOIN FSM.
         */
        return WLAN_STATUS_SUCCESS;
    }

    //4 <5> Parse the Information Elements of Authentication Frame Body.
    if ((u2AuthAlgNum == AUTH_ALGORITHM_NUM_SHARED_KEY) &&
        (u2TransactionSeqNum == AUTH_TRANSACTION_SEQ_2)) {
        P_IE_CHALLENGE_TEXT_T prRxIeChallengeText =
            (P_IE_CHALLENGE_TEXT_T)&prAuthFrame->aucInfoElem[0];

        /* Check if there exist the Challenge Text IE */
        if ((prSwRfb->u2FrameLength < (WLAN_MAC_MGMT_HEADER_LEN +
                                      AUTH_ALGORITHM_NUM_FIELD_LEN +
                                      AUTH_TRANSACTION_SEQENCE_NUM_FIELD_LEN +
                                      STATUS_CODE_FIELD_LEN +
                                      (ELEM_HDR_LEN + ELEM_MIN_LEN_CHALLENGE_TEXT))) ||
            (prRxIeChallengeText->ucId != ELEM_ID_CHALLENGE_TEXT)) {

            DBGLOG(JOIN, LOUD, ("Discard Auth frame because the IE of Challenge Text was collapsed.\n"));
            return WLAN_STATUS_FAILURE;
        }

        /* Save the Challenge Text from Auth Seq 2 Frame, before sending Auth Seq 3 Frame */
        COPY_IE(&prPeerBssInfo->rIeChallengeText, prRxIeChallengeText);
    }


    return WLAN_STATUS_SUCCESS;

} /* end of authProcessRxAuthFrame() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will parse and process the incoming Deauthentication frame
*        if the given BSSID is matched.
*
* \param[in] prAdapter          Pointer to the Adapter structure.
* \param[in] prSwRfb            Pointer to SW RFB data structure.
* \param[in] aucBSSID           Given BSSID
* \param[out] pu2ReasonCode     Pointer to store the Reason Code from Deauthentication.
*
* \retval WLAN_STATUS_FAILURE   This is not the frame we should handle at current state.
* \retval WLAN_STATUS_SUCCESS   This is the frame we should handle.
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
authProcessRxDeauthFrame (
    IN P_ADAPTER_T prAdapter,
    IN P_SW_RFB_T prSwRfb,
    IN UINT_8 aucBSSID[],
    OUT PUINT_16 pu2ReasonCode
    )
{
    P_WLAN_DEAUTH_FRAME_T prDeauthFrame;
    UINT_16 u2RxFrameCtrl;
    UINT_16 u2RxReasonCode;

    DEBUGFUNC("authProcessRxDeauthFrame");


    ASSERT(prAdapter);
    ASSERT(prSwRfb);
    ASSERT(aucBSSID);
    ASSERT(pu2ReasonCode);

    //4 <1> locate the Deauthentication Frame.
    prDeauthFrame = (P_WLAN_DEAUTH_FRAME_T) prSwRfb->pvHeader;

    //4 <2> Parse the Header of Authentication Frame.
    WLAN_GET_FIELD_16(&prDeauthFrame->u2FrameCtrl, &u2RxFrameCtrl)
    u2RxFrameCtrl &= MASK_FRAME_TYPE;
    if (u2RxFrameCtrl != MAC_FRAME_DEAUTH) {
        return WLAN_STATUS_FAILURE;
    }

    if (prSwRfb->u2FrameLength < (WLAN_MAC_MGMT_HEADER_LEN +
                                  REASON_CODE_FIELD_LEN)) {
        ASSERT(0);
        return WLAN_STATUS_FAILURE;
    }

    /* Check if this Deauth Frame is coming from Target BSSID */
    if (UNEQUAL_MAC_ADDR(prDeauthFrame->aucSrcAddr, aucBSSID)) {
        DBGLOG(JOIN, LOUD, ("Ignore Deauth Frame from other BSS ["MACSTR"]\n",
            MAC2STR(prDeauthFrame->aucSrcAddr)));
        return WLAN_STATUS_FAILURE;
    }

    //4 <3> Parse the Fixed Fields of Deauthentication Frame Body.
    WLAN_GET_FIELD_16(&prDeauthFrame->u2ReasonCode, &u2RxReasonCode);
    *pu2ReasonCode = u2RxReasonCode;

    return WLAN_STATUS_SUCCESS;

} /* end of authProcessRxDeauthFrame() */


