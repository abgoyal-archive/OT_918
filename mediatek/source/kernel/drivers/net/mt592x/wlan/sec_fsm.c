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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/sec_fsm.c#2 $
*/

/*! \file   "sec_fsm.c"
    \brief  This is the file implement security check state machine.

    In security module, do the port control check after success join to an AP,
    and the path to NORMAL TR, the state machine handle these state transition.
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
** $Log: sec_fsm.c $
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\43 2009-07-06 20:37:26 GMT mtk01088
**  adding the code to handle the wapi related variable
**  \main\maintrunk.MT5921\42 2009-06-22 21:26:01 GMT mtk01088
**  add a variable to clear the fifo empty event signal 
**  \main\maintrunk.MT5921\41 2009-05-23 14:46:31 GMT mtk01088
**  send the de-auth frame for countermeasure by using AC3
**  \main\maintrunk.MT5921\40 2009-03-19 22:03:57 GMT mtk01088
**  move the sec state enter idle after reset the send eapol timer
**  \main\maintrunk.MT5921\39 2008-10-29 11:13:18 GMT mtk01088
**  fixed the compiling error
**  \main\maintrunk.MT5921\38 2008-10-27 18:52:12 GMT mtk01088
**  adjust the code for avoid lint warnning
**  \main\maintrunk.MT5921\37 2008-10-22 10:59:15 GMT mtk01461
**  Update for lint diagnosis support
**  \main\maintrunk.MT5921\36 2008-08-28 20:47:24 GMT mtk01088
**  add assert check
**  \main\maintrunk.MT5921\35 2008-08-28 20:43:04 GMT mtk01088
**  add assert check. remove non-used code
**  \main\maintrunk.MT5921\34 2008-07-11 09:38:41 GMT mtk01088
**  adjust the clear default tranmsite key for only rsn
**  \main\maintrunk.MT5921\33 2008-07-10 16:43:58 GMT mtk01088
**  cleat the txTransmitKey flag to flase, let the following 1x flag use AC4 to send until oid add pairwise key
**  \main\maintrunk.MT5921\32 2008-07-10 00:48:05 GMT mtk01461
**  Fix the missing part of Enable TXQ at another path of port control after FIFO empty for Roaming CR
**  \main\maintrunk.MT5921\31 2008-07-07 13:44:25 GMT mtk01461
**  Enable TXQ right after privacy key been set.
**  \main\maintrunk.MT5921\30 2008-06-17 14:46:42 GMT MTK01088
**  adjust the rsnLastMicError time location
**  \main\maintrunk.MT5921\29 2008-06-05 15:53:18 GMT MTK01088
**  only the key that is not needed handshake needed to restore
**  \main\maintrunk.MT5921\28 2008-06-01 14:25:05 GMT mtk01088
**  fixed compiling error
**  \main\maintrunk.MT5921\27 2008-06-01 12:34:36 GMT mtk01088
**  AT WHQL Standby test, driver do chip reset on the way to D3, While driver back from D3, no infrastructure and key will set, driver neede to resotore the key exist in prAdapter->arWlanCtrl to HW
**  \main\maintrunk.MT5921\26 2008-05-22 19:47:43 GMT MTK01088
**  not to do privacy init to clear mib for sec init, thus will cause D3 -> D0 clear the old setting (WPA-None AES)
**  \main\maintrunk.MT5921\25 2008-05-12 19:56:28 GMT mtk01088
**  Fixed the office roaming issue, let the key is clear at roaming path
**  \main\maintrunk.MT5921\24 2008-03-31 09:54:20 GMT mtk01461
**  add callback func for authSendDeauthFrame
**  \main\maintrunk.MT5921\23 2008-03-30 16:49:13 GMT mtk01461
**  Update for change prototype of send Deauth frame
**  \main\maintrunk.MT5921\22 2008-03-18 10:14:11 GMT mtk01088
**  do the initial pmkid candidate and cache at sec module init
**  \main\maintrunk.MT5921\21 2008-03-06 16:26:27 GMT mtk01088
**  Clear the last rsn mic error time while start the countermeasure
**  \main\maintrunk.MT5921\20 2008-03-03 14:21:19 GMT mtk01088
**  avoid compiling warning
**  \main\maintrunk.MT5921\19 2008-02-29 15:28:42 GMT mtk01088
**  add rsn port control check at rx path
**  \main\maintrunk.MT5921\18 2008-02-29 13:16:16 GMT mtk01088
**  refine the function name and delete non-used code
**  \main\maintrunk.MT5921\17 2008-02-01 10:08:59 GMT mtk01385
**  1. Fix WinCE 4.2 compiling error.
**  \main\maintrunk.MT5921\16 2007-12-27 13:58:10 GMT mtk01088
**  adjust the sec fsm and wlan table init timing
**  \main\maintrunk.MT5921\15 2007-12-25 10:43:07 GMT mtk01088
**  do sec fsm abort while driver re-conncet by itself
**  \main\maintrunk.MT5921\14 2007-12-24 18:42:28 GMT mtk01088
**  remove DLS rx port control
**  \main\maintrunk.MT5921\13 2007-12-21 11:09:43 GMT mtk01088
**  not doing rx port control for let fragment TLS packet can be received
**  \main\maintrunk.MT5921\12 2007-11-21 15:32:56 GMT mtk01088
**  do the wlan table initial at chip reset
**  \main\maintrunk.MT5921\11 2007-11-20 11:01:28 GMT mtk01088
**  add function for wait EAPoL error pkt timeout
**  remove non-used code
**  \main\maintrunk.MT5921\10 2007-11-06 20:38:08 GMT mtk01088
**  \main\maintrunk.MT5921\9 2007-11-06 20:27:22 GMT mtk01088
**  add abort function
** Revision 1.7  2007/07/16 02:47:14  MTK01088
** the ENUM prefix use e instead of r
**
** Revision 1.6  2007/07/09 06:41:02  MTK01088
** update the function related with security fsm
**
** Revision 1.5  2007/07/04 10:17:41  MTK01088
** update sec fsm function
**
** Revision 1.4  2007/07/03 08:27:55  MTK01088
** the sec fsm keep it's own fsm
** all the oid need pass arbiter, add the event
**
** Revision 1.3  2007/06/28 13:07:56  MTK01088
** use the new privacy prefix name
**
** Revision 1.2  2007/06/27 12:39:42  MTK01088
** add the code for operation the Stop Tx/ FIFO empty / wlan table access / Start Tx
**
** Revision 1.1  2007/06/27 06:10:44  MTK01088
** add the security module fsm
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
#if DBG
/*lint -save -e64 Type mismatch */
static PUINT_8 apucDebugSecState[SEC_STATE_NUM] = {
    DISP_STRING("SEC_STATE_IDLE"),
    DISP_STRING("SEC_STATE_PORT_CONTROL"),
    DISP_STRING("SEC_STATE_FIFO_BUSY"),
    DISP_STRING("SEC_STATE_CHECK_OK"),
    DISP_STRING("SEC_STATE_SEND_EAPOL"),
    DISP_STRING("SEC_STATE_SEND_DEAUTH"),
};
/*lint -restore */
#endif /* DBG */

/*******************************************************************************
*                                 M A C R O S
********************************************************************************
*/

/*******************************************************************************
*                   F U N C T I O N   D E C L A R A T I O N S
********************************************************************************
*/
VOID
secFsmRunEventFifoEmpty(
    IN P_ADAPTER_T          prAdapter
    );

/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/

/*----------------------------------------------------------------------------*/
/*!
* \brief This function will do initialization of Security FSM and all variables in
*        SEC_INFO_T.
*
* \param[in] prAdapter      Pointer of Adapter Data Structure
*
* \return none
*/
/*----------------------------------------------------------------------------*/
VOID
secFsmInit (
    IN P_ADAPTER_T prAdapter
    )
{
    P_SEC_INFO_T prSecInfo;
    UINT_8       i;

    ASSERT(prAdapter);

    prSecInfo = &prAdapter->rSecInfo;
    ASSERT(prSecInfo);

    //AT WHQL Standby test, driver do chip reset on the way to D3,
    //While driver back from D3, no infrastructure and key will set,
    //driver needed to resotore the key exist in prAdapter->arWlanCtrl to HW
    if (!privacyRsnKeyHandshakeEnabled(prAdapter)) {
        for (i = 0; i < WLAN_TABLE_SIZE; i++) {
            if (prAdapter->arWlanCtrl[i].fgUsed) {
                if (!nicPrivacySetWlanTable(prAdapter, i, NULL,
                    &prAdapter->arWlanCtrl[i].rCtrl,
                    &prAdapter->arWlanCtrl[i].rSWKey)){
                    DBGLOG(RSN, TRACE, ("secFsmInit fail!\n"));
                    return;
                }
            }
        }
    }

    privacyClearPmkid(prAdapter);
    nicPrivacyEnableHwTxPortControl(prAdapter);

    prSecInfo->fgBlockOnlyAPTraffic = TRUE;
    prSecInfo->fgBlockTxTraffic = FALSE;
    prSecInfo->fgBlockRxTraffic = FALSE;

    prSecInfo->fgCheckEAPoLTxDone = FALSE;

    prSecInfo->eCurrentState = SEC_STATE_IDLE;

    ARB_INIT_TIMER(prAdapter,
                   prSecInfo->rRsnaEAPoLReportTimeoutTimer,
                   arbFsmRunEventSecCancelEAPoLTimer,
                   TRUE);

    ARB_INIT_TIMER(prAdapter,
                   prSecInfo->rRsnaBlockTrafficTimer,
                   arbFsmRunEventSecCounterMeasureDone,
                   TRUE);

    ARB_INIT_TIMER(prAdapter,
                   prSecInfo->rPreauthenticationTimer,
                   arbFsmRunEventSecIndicatePmkidCand,
                   TRUE);

    return;
}


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will do action part while in STATE transition of
*        IDLE to PORT_CONTROL.
*
* \param[in] prAdapter      Pointer of Adapter Data Structure
*
* \return - none
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ VOID
secFsmTransAction_IDLE_to_PORT_CONTROL (
    IN P_ADAPTER_T prAdapter
    )
{

    ASSERT(prAdapter);

    nicPrivacyPortControl(prAdapter, prAdapter->rBssInfo.aucBSSID, TRUE, TRUE);

    return;
}


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will do action part while in STATE transition of
*        IDLE to CHECK_OK.
*
* \param[in] prAdapter      Pointer of Adapter Data Structure
*
* \return - none
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ VOID
secFsmTransAction_IDLE_to_CHECK_OK (
    IN P_ADAPTER_T prAdapter
    )
{
    ASSERT(prAdapter);

    ASSERT((prAdapter->arWlanCtrl[0].rCtrl.fgT1X == FALSE) &&
        (prAdapter->arWlanCtrl[0].rCtrl.fgR1X == FALSE));
    return;
}


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will do action part while in STATE transition of
*        PORT_CONTROL to FIFO_BUSY.
*
* \param[in] prAdapter      Pointer of Adapter Data Structure
*
* \return - none
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ VOID
secFsmTransAction_PORT_CONTROL_to_FIFO_BUSY (
    IN P_ADAPTER_T prAdapter
    )
{
    return;
 }


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will do action part while in STATE transition of
*        PORT_CONTROL to CHECK_OK.
*
* \param[in] prAdapter      Pointer of Adapter Data Structure
*
* \return - none
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ VOID
secFsmTransAction_PORT_CONTROL_to_CHECK_OK (
    IN P_ADAPTER_T          prAdapter
    )
{

    ASSERT(prAdapter);

    nicPrivacyPortControl(prAdapter, prAdapter->rBssInfo.aucBSSID, FALSE, FALSE);

    prAdapter->fgBypassPortCtrlForRoaming = FALSE;

    nicTxStartQueues(prAdapter, (TXQ_DATA_MASK | TXQ_MGMT_MASK) );

    DBGLOG(ARB, TRACE, ("secFsmTransAction_PORT_CONTROL_to_CHECK_OK\n"));
    return;
}


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will do action part while in STATE transition of
*        FIFO_BUSY to CHECK_OK.
*
* \param[in] prAdapter      Pointer of Adapter Data Structure
*
* \return - none
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ VOID
secFsmTransAction_FIFO_BUSY_to_CHECK_OK (
    IN P_ADAPTER_T prAdapter
    )
{
    ASSERT(prAdapter);

    prAdapter->fgBypassPortCtrlForRoaming = FALSE;

    nicTxStartQueues(prAdapter, (TXQ_DATA_MASK | TXQ_MGMT_MASK) );

    return;
}


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will do action part while in STATE transition of
*        CHECK_OK to FIFO_BUSY.
*
* \param[in] prAdapter      Pointer of Adapter Data Structure
*
* \return -
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ VOID
secFsmTransAction_CHECK_OK_to_SEND_EAPOL (
    IN P_ADAPTER_T prAdapter
    )
{
    P_SEC_INFO_T   prSecInfo;

    ASSERT(prAdapter);

    prSecInfo = &prAdapter->rSecInfo;
    ASSERT(prSecInfo);

    prSecInfo->fgCheckEAPoLTxDone = TRUE;

    ARB_SET_TIMER(prAdapter,
                  prSecInfo->rRsnaEAPoLReportTimeoutTimer,
                  SEC_TO_MSEC(EAPOL_REPORT_SEND_TIMEOUT_INTERVAL_SEC));

    return;
}


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will do action part while in STATE transition of
*        CHECK_OK to SEND_EAPOL.
*
* \param[in] prAdapter      Pointer of Adapter Data Structure
*
* \return - none
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ VOID
secFsmTransAction_CHECK_OK_to_FIFO_BUSY (
    IN P_ADAPTER_T prAdapter
    )
{
    return;
}


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will do action part while in STATE transition of
*        SEND_EAPOL to SEND_DEAUTH.
*
* \param[in] prAdapter      Pointer of Adapter Data Structure
*
* \return - none
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ VOID
secFsmTransAction_SEND_EAPOL_to_SEND_DEAUTH (
    IN P_ADAPTER_T prAdapter
    )
{
    ASSERT(prAdapter);

    /* Compose deauth frame to AP, a call back function for tx done */
    if (authSendDeauthFrame(prAdapter,
                            prAdapter->rBssInfo.aucBSSID,
                            REASON_CODE_MIC_FAILURE,
                            AC3,
                            arbFsmRunEventSecDeauthDone) != WLAN_STATUS_SUCCESS) {
        ASSERT(FALSE);
    }
}


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will do action part while in STATE transition of
*        SEND_DEAUTH to IDLE.
*
* \param[in] prAdapter      Pointer of Adapter Data Structure
*
* \return -
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ VOID
secFsmTransAction_SEND_DEAUTH_to_IDLE (
    IN P_ADAPTER_T prAdapter
    )
{

    return;
}


/*----------------------------------------------------------------------------*/
/*!
* \brief The Core FSM engine of security module.
*
* \param[in] prAdapter      Pointer of Adapter Data Structure
* \param[in] eNextState     Enum value of next sec STATE
*
* \return -
*/
/*----------------------------------------------------------------------------*/
VOID
secFsmSteps (
    IN P_ADAPTER_T          prAdapter,
    IN ENUM_SEC_STATE_T     eNextState
    )
{
    P_SEC_INFO_T            prSecInfo;
    BOOLEAN                 fgIsTransition = (BOOLEAN)FALSE;

    ASSERT(prAdapter);

    prSecInfo = &prAdapter->rSecInfo;
    ASSERT(prSecInfo);

    DEBUGFUNC("secFsmSteps");
    do {
        /* Do entering Next State */
        DBGLOG(RSN, STATE, ("\nTRANSITION: [%s] -> [%s]\n\n",
                            apucDebugSecState[prSecInfo->eCurrentState],
                            apucDebugSecState[eNextState]));

        prSecInfo->eCurrentState = eNextState;

        /* Do nothing at this State */

    }
    while (fgIsTransition);

    return;

}


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will do initialization of Security FSM and all variables in
*        SEC_INFO_T.
*
* \param[in] prAdapter      Pointer of Adapter Data Structure
*
* \return none
*/
/*----------------------------------------------------------------------------*/
VOID
secFsmRunEventStart (
    IN P_ADAPTER_T          prAdapter
    )
{
    P_SEC_INFO_T            prSecInfo;
    BOOLEAN                 fgIsTransition = (BOOLEAN)FALSE;
    ENUM_SEC_STATE_T        eNextState;

    DBGLOG(RSN, TRACE, ("secFsmRunEventStart\n"));

    ASSERT(prAdapter);

    prSecInfo = &prAdapter->rSecInfo;
    eNextState = prSecInfo->eCurrentState;

    if (prSecInfo == NULL)
        return;

    prAdapter->rSecInfo.u4RsnaLastMICFailTime = 0;

    arbFsmRunEventSecTxFlowControl(prAdapter, TRUE);

    if (privacyRsnKeyHandshakeEnabled(prAdapter) == TRUE) {
        prAdapter->rConnSettings.rMib.dot11TranmitKeyAvailable = FALSE;
        nicPrivacyInitialize(prAdapter);
        SEC_STATE_TRANSITION(prAdapter, IDLE, PORT_CONTROL);
    }
    else {
#if SUPPORT_WAPI
        prAdapter->rConnSettings.rMib.fgWapiKeyInstalled = FALSE;
#endif
        SEC_STATE_TRANSITION(prAdapter, IDLE, CHECK_OK);
    }

    secFsmSteps(prAdapter, eNextState);

    return;
} /* secFsmRunEventStart */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function called by reset procedure to force the sec fsm enter
*        idle state
*
* \param[in] prAdapter      Pointer of Adapter Data Structure
*
* \return none
*/
/*----------------------------------------------------------------------------*/
VOID
secFsmRunEventAbort (
    IN P_ADAPTER_T          prAdapter
    )
{
    P_SEC_INFO_T            prSecInfo;

    DBGLOG(RSN, TRACE, ("secFsmRunEventAbort\n"));

    ASSERT(prAdapter);

    prSecInfo = &prAdapter->rSecInfo;

    if (prSecInfo == NULL)
        return;

    if (prSecInfo->eCurrentState == SEC_STATE_SEND_EAPOL) {
        if (prSecInfo->fgCheckEAPoLTxDone == FALSE) {
            DBGLOG(RSN, TRACE, ("EAPOL STATE not match the flag\n"));
            ARB_CANCEL_TIMER(prAdapter, prSecInfo->rRsnaEAPoLReportTimeoutTimer);
        }
    }

    prSecInfo->fgBlockTxTraffic = FALSE;
    prSecInfo->fgBlockRxTraffic = FALSE;

#if SUPPORT_WAPI
    prAdapter->rConnSettings.rMib.fgWapiKeyInstalled = FALSE;
    if (prAdapter->fgUseWapi && prAdapter->fgWapiMode) {
        prSecInfo->fgBlockTxTraffic = TRUE;
        prSecInfo->fgBlockRxTraffic = TRUE;
    }
#endif
    prSecInfo->eCurrentState = SEC_STATE_IDLE;

}


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will indicate an Event of "Pairwise key installed" to SEC FSM.
*
* \param[in] prAdapter      Pointer of Adapter Data Structure
* \param[in] pucBssid       The mac address to be set, can be AP,DLS, BC, MC
* \param[in] pucKeyMaterial The key material
* \param[in] ucKeyLen       The key length
* \param[in] ucCipherMode   The Cipher mode to encrypt / decrypt
* \param[in] ucTxMicOffset  The TKIP Tx mic offset from key material
* \param[in] ucRxMicOffset  The TKIP Rx mic offset from key material
*
* \retval TRUE The key can be installed to HW
* \retval FALSE The kay conflict with the current key, abort it
*/
/*----------------------------------------------------------------------------*/
BOOLEAN
secFsmRunEventPTKInstalled (
    IN P_ADAPTER_T          prAdapter,
    IN PUINT_8              pucBssid,
    IN PUINT_8              pucKeyMaterial,
    IN UINT_8               ucKeyLen,
    IN UINT_8               ucCipherMode,
    IN UINT_8               ucTxMicOffset,
    IN UINT_8               ucRxMicOffset
    )
{
    P_SEC_INFO_T            prSecInfo;
    ENUM_SEC_STATE_T        eNextState;
    BOOLEAN                 fgStatus = TRUE;
    BOOLEAN                 fgIsTransition = (BOOLEAN)FALSE;

    ASSERT(prAdapter);

    prSecInfo = &prAdapter->rSecInfo;
    eNextState = prSecInfo->eCurrentState;

    switch(prSecInfo->eCurrentState) {
    case SEC_STATE_PORT_CONTROL:
        if (arbFsmRunEventSecTxFlowControl(prAdapter, FALSE)==FALSE){
            if (!nicPrivacySetKeyEntry(prAdapter,
                TRUE,
                pucBssid,
                0,
                pucKeyMaterial,
                ucKeyLen,
                ucCipherMode,
                ucTxMicOffset,
                ucRxMicOffset)){
                DBGLOG(RSN, TRACE, ("secFsmRunEventPTKInstalled fail!\n"));
            }
            SEC_STATE_TRANSITION(prAdapter, PORT_CONTROL, CHECK_OK);
        }
        else {
            nicPrivacySetKeyToTemplateEntry(prAdapter,
                pucBssid,
                pucKeyMaterial,
                ucKeyLen,
                ucCipherMode,
                ucTxMicOffset,
                ucRxMicOffset);
            nicPrivacyInvalidEntryRx(prAdapter, pucBssid);
            SEC_STATE_TRANSITION(prAdapter, PORT_CONTROL, FIFO_BUSY);
        }
        break;

    case SEC_STATE_FIFO_BUSY:
        /* Keep at this state */
        /* oid query this and return TRUE or FALSE to
           Overwrite or do nothing for add PTK */
        fgStatus = FALSE;                      
        break;

    case SEC_STATE_CHECK_OK:
        if (arbFsmRunEventSecTxFlowControl(prAdapter, FALSE)==FALSE ||
            prAdapter->eConnectionState != MEDIA_STATE_CONNECTED){
            if (!nicPrivacySetKeyEntry(prAdapter,
                    TRUE,
                    pucBssid,
                    0,
                    pucKeyMaterial,
                    ucKeyLen,
                    ucCipherMode,
                    ucTxMicOffset,
                    ucRxMicOffset)) {
                DBGLOG(RSN, TRACE, ("secFsmRunEventPTKInstalled fail!\n"));
            }
            /* Not Transition at this state */
        }
        else {
            nicPrivacySetKeyToTemplateEntry(prAdapter,
                pucBssid,
                pucKeyMaterial,
                ucKeyLen,
                ucCipherMode,
                ucTxMicOffset,
                ucRxMicOffset);
            nicPrivacyInvalidEntryRx(prAdapter, pucBssid);
            SEC_STATE_TRANSITION(prAdapter, CHECK_OK, FIFO_BUSY);
        }
        break;

    default:

        if (!nicPrivacySetKeyEntry(prAdapter,
                                  TRUE,
                                  pucBssid,
                                  0,
                                  pucKeyMaterial,
                                  ucKeyLen,
                                  ucCipherMode,
                                  ucTxMicOffset,
                                  ucRxMicOffset)){
            fgStatus = FALSE;                      
        }

        break;
    }

    if (prSecInfo->eCurrentState != eNextState) {
        secFsmSteps(prAdapter, eNextState);
    }

    return fgStatus;

} /* end of secFsmRunEventPTKInstalled() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will indicate an Event of "FIFO EMPTY" to SEC FSM.
*
* \param[in] prAdapter      Pointer of Adapter Data Structure
*
* \return
*/
/*----------------------------------------------------------------------------*/
VOID
secFsmRunEventFifoEmpty (
    IN P_ADAPTER_T          prAdapter
    )
{
    P_SEC_INFO_T            prSecInfo;
    ENUM_SEC_STATE_T        eNextState;
    BOOLEAN                 fgIsTransition = (BOOLEAN)FALSE;

    ASSERT(prAdapter);
    
    prSecInfo = &prAdapter->rSecInfo;
    ASSERT(prSecInfo);
    
    eNextState = prSecInfo->eCurrentState;

    switch(prSecInfo->eCurrentState) {
    case SEC_STATE_PORT_CONTROL:
        /* Copy entry from template entry */
        if (nicPrivacyCopyFromTemplateEntry(prAdapter) == FALSE){
            break;
        }
        nicPrivacyInvalidTemplateEntry(prAdapter);
        SEC_STATE_TRANSITION(prAdapter, PORT_CONTROL, CHECK_OK);
        break;

    case SEC_STATE_FIFO_BUSY:

        /* Copy entry from template entry */
        if (nicPrivacyCopyFromTemplateEntry(prAdapter) == FALSE){
            break;
        }
        nicPrivacyInvalidTemplateEntry(prAdapter);
        SEC_STATE_TRANSITION(prAdapter, FIFO_BUSY, CHECK_OK);
        break;

    case SEC_STATE_CHECK_OK:
        DBGLOG(RSN, TRACE, ("Do nothing while at this state!\n"));
        break;
        
    default:
        ERRORLOG(("Called at un-expected state [%s]\n ", apucDebugSecState[prSecInfo->eCurrentState]));
        break;
    }

    if (prSecInfo->eCurrentState != eNextState) {
        secFsmSteps(prAdapter, eNextState);
    }

    return;
} /* end of secFsmRunEventFifoEmpty() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will indicate an Event of "Counter Measure" to SEC FSM.
*
* \param prAdapter      Pointer of Adapter Data Structure
*
* \return -
*/
/*----------------------------------------------------------------------------*/
VOID
secFsmRunEventStartCounterMeasure (
    IN P_ADAPTER_T          prAdapter
    )
{
    P_SEC_INFO_T            prSecInfo;
    ENUM_SEC_STATE_T        eNextState;
    BOOLEAN                 fgIsTransition = (BOOLEAN)FALSE;

    DEBUGFUNC("secFsmRunEventStartCounterMeasure");

    ASSERT(prAdapter);

    prSecInfo = &prAdapter->rSecInfo;
    eNextState = prSecInfo->eCurrentState;

    DBGLOG(RSN, TRACE, ("Sec state %s\n", apucDebugSecState[prSecInfo->eCurrentState]));

    prAdapter->rSecInfo.u4RsnaLastMICFailTime = 0;

    switch(prSecInfo->eCurrentState) {
    case SEC_STATE_CHECK_OK:
        {
            //<Todo> dls port control
            SEC_STATE_TRANSITION(prAdapter, CHECK_OK, SEND_EAPOL);
        }
        break;

    default:
        break;
    }

    /* Call arbFsmSteps() when we are going to change ARB STATE */
    if (prSecInfo->eCurrentState != eNextState) {
        secFsmSteps(prAdapter, eNextState);
    }

    return;

} /* secFsmRunEventStartCounterMeasure */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will indicate an Event of "802.1x EAPoL Tx Done" to Sec FSM.
*
* \param[in] prAdapter      Pointer of Adapter Data Structure
*
* \return -
*/
/*----------------------------------------------------------------------------*/
VOID
secFsmRunEventEapolTxDone (
    IN P_ADAPTER_T          prAdapter

    )
{
    P_SEC_INFO_T            prSecInfo;
    ENUM_SEC_STATE_T        eNextState;
    BOOLEAN                 fgIsTransition = (BOOLEAN)FALSE;

    DEBUGFUNC("secFsmRunEventEapolTxDone");

    ASSERT(prAdapter);
    prSecInfo = &prAdapter->rSecInfo;
    eNextState = prSecInfo->eCurrentState;

    DBGLOG(RSN, TRACE, ("Sec state %s\n", apucDebugSecState[prSecInfo->eCurrentState]));

    switch(prSecInfo->eCurrentState) {
    case SEC_STATE_SEND_EAPOL:
        if (prSecInfo->fgCheckEAPoLTxDone == FALSE) {
            ASSERT(0);
        }

        prSecInfo->fgCheckEAPoLTxDone = FALSE;
        ARB_CANCEL_TIMER(prAdapter, prSecInfo->rRsnaEAPoLReportTimeoutTimer);

        SEC_STATE_TRANSITION(prAdapter, SEND_EAPOL, SEND_DEAUTH);
        break;
    default:
        break;
    }

    if (prSecInfo->eCurrentState != eNextState) {
        secFsmSteps(prAdapter, eNextState);
    }

    return;

}/* secFsmRunEventEapolTxDone */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will indicate an Event of "Deauth frame Tx Done" to Sec FSM.
*
* \param[in] prAdapter      Pointer of Adapter Data Structure
*
* \return -
*
* \note after receive deauth frame, callback function call this
*/
/*----------------------------------------------------------------------------*/
VOID
secFsmRunEventDeauthTxDone (
    IN P_ADAPTER_T  prAdapter

    )
{
    P_SEC_INFO_T     prSecInfo;

    DEBUGFUNC("secFsmRunEventDeauthTxDone");

    ASSERT(prAdapter);
    
    prSecInfo = &prAdapter->rSecInfo;
    DBGLOG(RSN, TRACE, ("Sec state %s\n", apucDebugSecState[prSecInfo->eCurrentState]));

    switch(prSecInfo->eCurrentState) {
    case SEC_STATE_SEND_DEAUTH:

        DBGLOG(RSN, TRACE, ("Set timer %d\n", COUNTER_MEASURE_TIMEOUT_INTERVAL_SEC));

        arbFsmRunEventConnectionStartCounterMeasure(prAdapter);
        ARB_SET_TIMER(prAdapter,
                      prSecInfo->rRsnaBlockTrafficTimer,
                      SEC_TO_MSEC(COUNTER_MEASURE_TIMEOUT_INTERVAL_SEC));
        break;

    default:
        ASSERT(0);
        break;
    }

    return;
}/* secFsmRunEventDeauthTxDone */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will stop the counterMeasure duration.
*
* \param prAdapter      Pointer of Adapter Data Structure
*
* \return -
*/
/*----------------------------------------------------------------------------*/
VOID
secFsmRunEventEndOfCounterMeasure (
    IN P_ADAPTER_T          prAdapter
    )
{
    P_SEC_INFO_T            prSecInfo;
    ENUM_SEC_STATE_T        eNextState;
    BOOLEAN                 fgIsTransition = (BOOLEAN)FALSE;

    DEBUGFUNC("secFsmRunEventEndOfCounterMeasure");

    ASSERT(prAdapter);
    prSecInfo = &prAdapter->rSecInfo;
    eNextState = prSecInfo->eCurrentState;
    
    DBGLOG(RSN, TRACE, ("Sec state %s\n", apucDebugSecState[prSecInfo->eCurrentState]));

    switch(prSecInfo->eCurrentState) {
    case SEC_STATE_SEND_DEAUTH:
        {
            SEC_STATE_TRANSITION(prAdapter, SEND_DEAUTH, IDLE);

            //info the arb change from NORMAL_TR to SEARCH
            //delay to 60 sec timeout event
            arbFsmRunEventConnectionEndOfCounterMeasure(prAdapter);
        }
        break;

    default:
        ASSERT(0);
    }

    /* Call arbFsmSteps() when we are going to change ARB STATE */
    if (prSecInfo->eCurrentState != eNextState) {
        secFsmSteps(prAdapter, eNextState);
    }

    return;
}/* end of secFsmRunEventEndOfCounterMeasure */

