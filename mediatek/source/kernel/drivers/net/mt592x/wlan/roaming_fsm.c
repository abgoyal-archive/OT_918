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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/roaming_fsm.c#2 $
*/

/*! \file   "roaming_fsm.c"
    \brief  This file defines the "FSM STEP" and state transition function of ROAMING Module.

    "FSM STEP" and State Transition function of ROAMING Module.
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
** $Log: roaming_fsm.c $
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\28 2009-10-09 17:12:59 GMT mtk01088
**  The privacycheck is now enable for WAPI
**  \main\maintrunk.MT5921\27 2009-07-07 18:40:58 GMT mtk01088
**  let driver can roaming while at wapi mode
**  \main\maintrunk.MT5921\26 2009-04-27 11:29:40 GMT mtk01088
**  adjust the define for privacy check support at WPS
**  \main\maintrunk.MT5921\25 2009-04-07 18:02:40 GMT mtk01088
**  Use the compiling flag for WPS support
**  \main\maintrunk.MT5921\24 2009-04-06 15:44:20 GMT mtk01088
**  For CR1486, re-schedule the timer to do roaming, until key install, and for wps, re-schedule the timer, but the key never install, so while at wps mode, disable the roaming
**  \main\maintrunk.MT5921\23 2008-12-01 18:18:33 GMT mtk01088
**  fixed the lint "possible using null pointer" warning
**  \main\maintrunk.MT5921\22 2008-11-28 16:49:32 GMT mtk01088
**  fixed the lint warning
**  \main\maintrunk.MT5921\21 2008-10-22 10:58:54 GMT mtk01461
**  Update for lint diagnosis support
**  \main\maintrunk.MT5921\20 2008-10-16 15:56:09 GMT mtk01461
**  Update driver to fix lint warning
**  \main\maintrunk.MT5921\19 2008-08-25 09:45:22 GMT mtk01461
**  Update for Driver Review
**  \main\maintrunk.MT5921\18 2008-07-08 11:25:52 GMT mtk01461
**  Fix the problem of try to do SCAN if roaming fail during join process.
**  \main\maintrunk.MT5921\17 2008-07-07 13:40:04 GMT mtk01461
**  Increase the roaming discovery check time from 100 to 300 to redue the host effort.
**  \main\maintrunk.MT5921\16 2008-07-01 20:09:50 GMT mtk01084
**  rename the scan method
**  \main\maintrunk.MT5921\15 2008-07-01 10:54:35 GMT mtk01084
**  modifications for replacing previous VoIP scan under CAM for existing method for VoIP scan
**  \main\maintrunk.MT5921\14 2008-06-12 20:29:53 GMT mtk01461
**  Add dwell min/ext time definition of SCAN parameters. And remove unused compile flag of SCAN module which is work around for MPW.
**  \main\maintrunk.MT5921\13 2008-05-16 10:39:13 GMT mtk01461
**  Revise RCPI related function for RSSI OID & Roaming
**  \main\maintrunk.MT5921\12 2008-03-20 00:02:30 GMT mtk01461
**  Fix typo of a scan query func
**  \main\maintrunk.MT5921\11 2008-03-19 15:21:56 GMT mtk01461
**  Add adjust a smaller threshold bar for boundary case
**  \main\maintrunk.MT5921\10 2008-03-14 19:01:24 GMT mtk01084
**  modify VoIP related variables
**  \main\maintrunk.MT5921\9 2008-03-13 14:29:00 GMT mtk01461
**  Revise Roaming Module - FSM and new scheme for new high threshold design
**
**  \main\maintrunk.MT5921\7 2008-02-01 09:59:22 GMT mtk01385
**  1. Fix WinCE 4.2 compiling error.
**  \main\maintrunk.MT5921\6 2007-11-22 21:42:42 GMT mtk01385
**  1. updat RR register comply with DataSheet v0.26.
**  \main\maintrunk.MT5921\5 2007-11-12 16:16:13 GMT mtk01084
**  modify scan dwell time length from 16 bit to 8 bit
**  \main\maintrunk.MT5921\4 2007-11-02 00:57:15 GMT mtk01461
**  Unify TX Path for Normal and IBSS Power Save + IBSS neighbor learning
**  \main\maintrunk.MT5921\3 2007-11-01 14:46:45 GMT mtk01084
**  modify variable naming of the u4ScanDwellTimeMax to u4ScanDwellTimeExt
**  \main\maintrunk.MT5921\2 2007-10-25 18:05:12 GMT mtk01461
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
static PUINT_8 apucDebugRoamingState[ROAMING_STATE_NUM] = {
    DISP_STRING("ROAMING_STATE_IDLE"),
    DISP_STRING("ROAMING_STATE_DECISION"),
    DISP_STRING("ROAMING_STATE_DISCOVERY"),
    DISP_STRING("ROAMING_STATE_ROAM"),
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

/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/
/*----------------------------------------------------------------------------*/
/*!
* \brief This function will do action part while in STATE transition of
*        DECISION to IDLE.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ VOID
roamingFsmTransAction_DECISION_to_IDLE (
    IN P_ADAPTER_T prAdapter
    )
{
    P_ROAMING_INFO_T prRoamingInfo;


    ASSERT(prAdapter);
    prRoamingInfo = &prAdapter->rRoamingInfo;

    /* NOTE(Kevin): Cancel Timer & Event INT. */

    /* Stop RCPI threshold immediately */
    nicRRTriggerDisable(prAdapter);

    prRoamingInfo->fgIsRCPIEventEnabled = FALSE;

    ARB_CANCEL_TIMER(prAdapter,
                     prRoamingInfo->rRoamingDecisionTimer);

    return;
} /* end of roamingFsmTransAction_DECISION_to_IDLE() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will do action part while in STATE transition of
*        DISCOVERY to IDLE.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ VOID
roamingFsmTransAction_DISCOVERY_to_IDLE (
    IN P_ADAPTER_T prAdapter
    )
{
    P_ROAMING_INFO_T prRoamingInfo;


    ASSERT(prAdapter);
    prRoamingInfo = &prAdapter->rRoamingInfo;

    /* NOTE(Kevin): Cancel Timer but No Event INT. */
    ARB_CANCEL_TIMER(prAdapter,
                     prRoamingInfo->rRoamingDiscoveryTimer);


    prRoamingInfo->fgIsScanTriggered = FALSE;
    prRoamingInfo->fgIsScanCompleted = FALSE;

    return;
} /* end of roamingFsmTransAction_DISCOVERY_to_IDLE() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will do action part while in STATE transition of
*        ROAM to IDLE.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ VOID
roamingFsmTransAction_ROAM_to_IDLE (
    IN P_ADAPTER_T prAdapter
    )
{
    ASSERT(prAdapter);

    /* NOTE(Kevin): No Timer & No Event INT to cancel. */
    return;
} /* end of roamingFsmTransAction_ROAM_to_IDLE() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will do action part while in STATE transition of
*        DECISION to DISCOVERY.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ VOID
roamingFsmTransAction_DECISION_to_DISCOVERY (
    IN P_ADAPTER_T prAdapter
    )
{
    ASSERT(prAdapter);

    return;
} /* end of roamingFsmTransAction_DECISION_to_DISCOVERY() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will do action part while in STATE transition of
*        DISCOVERY to ROAM.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ VOID
roamingFsmTransAction_DISCOVERY_to_ROAM (
    IN P_ADAPTER_T prAdapter
    )
{
    ASSERT(prAdapter);

    return;
} /* end of roamingFsmTransAction_DISCOVERY_to_ROAM() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function is used to initial the data structure of ROAMING FSM.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
roamingFsmInit (
    IN P_ADAPTER_T prAdapter
    )
{
    P_ROAMING_INFO_T prRoamingInfo;


    ASSERT(prAdapter);
    prRoamingInfo = &prAdapter->rRoamingInfo;

    prRoamingInfo->eCurrentState = ROAMING_STATE_IDLE;


    prRoamingInfo->rRoamingDiscoveryUpdateTime = 0;

    prRoamingInfo->fgIsScanTriggered = FALSE;
    prRoamingInfo->fgIsScanCompleted = FALSE;
    prRoamingInfo->fgIsRCPIEventEnabled = FALSE;
    prRoamingInfo->fgIsRoamingFail = FALSE;

    ARB_INIT_TIMER(prAdapter,
                   prRoamingInfo->rRoamingDecisionTimer,
                   arbFsmRunEventRoamingDecision,
                   TRUE);

    ARB_INIT_TIMER(prAdapter,
                   prRoamingInfo->rRoamingDiscoveryTimer,
                   arbFsmRunEventRoamingDiscovery,
                   TRUE);

    return;
} /* end of roamingFsmInit() */


/*----------------------------------------------------------------------------*/
/*!
* \brief The Core FSM engine of ROAMING Module.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
* \param[in] eNextState The next STATE we should go.
*
* \retval WLAN_STATUS_PENDING               Pending for waiting next trigger event.
* \retval WLAN_STATUS_ROAM_DISCOVERY        Try to do scan and update scan result.
* \retval WLAN_STATUS_ROAM_OUT_FIND_BEST    Try to roam out if have candidate.
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
roamingFsmSteps (
    IN P_ADAPTER_T prAdapter,
    IN ENUM_ROAMING_STATE_T eNextState
    )
{
    P_ROAMING_INFO_T prRoamingInfo;
    P_BSS_INFO_T prBssInfo;
    P_BSS_DESC_T prBssDesc;
    BOOLEAN fgIsTransition = (BOOLEAN)FALSE;
    /* If the signal of AP is stable and good, the default STATUS is PENDING */
    WLAN_STATUS rStatus = WLAN_STATUS_PENDING;
    P_CONNECTION_SETTINGS_T prConnSettings;

    DEBUGFUNC("roamingFsmSteps");


    ASSERT(prAdapter);
    prBssInfo = &prAdapter->rBssInfo;
    prRoamingInfo = &prAdapter->rRoamingInfo;

    prConnSettings = &prAdapter->rConnSettings;

    do {
        DBGLOG(ROAMING, STATE, ("TRANSITION: [%s] -> [%s]\n",
                                apucDebugRoamingState[prRoamingInfo->eCurrentState],
                                apucDebugRoamingState[eNextState]));

        prRoamingInfo->eCurrentState = eNextState;


        fgIsTransition = (BOOLEAN)FALSE;
        switch (prRoamingInfo->eCurrentState) {

        case ROAMING_STATE_DECISION:
            {
                OS_SYSTIME rCurrentTime;
                RCPI rRcpi;

                do {
                    GET_CURRENT_SYSTIME(&rCurrentTime);

                    DBGLOG(ROAMING, INFO, ("rCurrentTime = %08lx, prBssInfo->rRoamingStableExpirationTime = %08lx\n",
                        rCurrentTime, prBssInfo->rRoamingStableExpirationTime));

                    //4 <1> Check if we has sufficient stable time
                    /* Do ROAMING decision after the Stable Timer timeout to avoid frequently roaming. */
                    if (!CHECK_FOR_EXPIRATION(rCurrentTime,
                            prBssInfo->rRoamingStableExpirationTime)) {

                        DBGLOG(ROAMING, INFO, ("Set stable period after roaming in BSS.\n"));

                        nicRRTriggerDisable(prAdapter);
                        prRoamingInfo->fgIsRCPIEventEnabled = FALSE;


                        /* TODO(Kevin): The stable time also can be adjustable according some external conditions
                         * - eg. temperature or current channel load.
                         */
                        ARB_SET_TIMER(prAdapter,
                                      prRoamingInfo->rRoamingDecisionTimer,
                                      SEC_TO_MSEC(ROAMING_STABLE_TIMEOUT_SEC));

                        prRoamingInfo->fgIsRoamingFail = FALSE;
                        break;
                    }


#if SUPPORT_WPS
                    /* CR1486, CR1640 */
                    /* Notice, at WPS mode, no key set, so the wzc profile control the connection */
                    if (
#if 0//SUPPORT_WAPI
                        (!prAdapter->fgUseWapi) &&
#endif
                        (prAdapter->rSecInfo.fgPrivacyCheckDisable) &&
                        (prAdapter->rConnSettings.eAuthMode < AUTH_MODE_WPA) &&
                        (prAdapter->rConnSettings.eOPMode == NET_TYPE_INFRA)) {

                        DBGLOG(RSN, TRACE, ("Disable roaming while at wps mode!!\n"));
                        ARB_SET_TIMER(prAdapter,
                                      prRoamingInfo->rRoamingDecisionTimer,
                                      SEC_TO_MSEC(ROAMING_STABLE_TIMEOUT_SEC));
                        break;
                    }
#endif
                    if (privacyRsnKeyHandshakeEnabled(prAdapter) &&
                        !privacyTransmitKeyExist(prAdapter)) {

                        DBGLOG(ROAMING, INFO, ("Reschedule timer because wpa handshake not complete!!\n"));

                        ARB_SET_TIMER(prAdapter,
                                      prRoamingInfo->rRoamingDecisionTimer,
                                      SEC_TO_MSEC(ROAMING_STABLE_TIMEOUT_SEC));
                        break;
                    }

                    //4 <2> Get Current RCPI value.
                    nicRRGetRCPI(prAdapter, &rRcpi);


                    //4 <3> Check if previous roaming was failed
                    if (prRoamingInfo->fgIsRoamingFail) {
                        RCPI rRcpiHighBound, rRcpiLowBound;
                        RCPI rLowBoundStep;

                        /* NOTE: When we do association, fgIsRCPIEventEnabled should
                         * be FALSE to reduce RCPI INT noise.
                         */
                        ASSERT(!prRoamingInfo->fgIsRCPIEventEnabled);

                        if (rRcpi == RCPI_MEASUREMENT_NOT_AVAILABLE) {

                            ASSERT(0);

                            /* Use previous RCPI value */
                            rRcpi = prBssInfo->rRcpi;
                        }
                        else {
                            //4 <3.A> Also update RCPI /RSSI to BSS_INFO_T for information
                            prBssInfo->rRcpi = rRcpi;
                            prBssInfo->rRssi = RCPI_TO_dBm(rRcpi);
                            GET_CURRENT_SYSTIME(&prBssInfo->rRssiLastUpdateTime);

                            //4 <3.B> Also update RCPI to P_BSS_DESC_T for compare
                            if ((prBssDesc = scanSearchBssDescByBssid(prAdapter,
                                    prBssInfo->aucBSSID)) != (P_BSS_DESC_T)NULL) {
                                prBssDesc->rRcpi = rRcpi;
                                prBssDesc->rUpdateTime = prBssInfo->rRssiLastUpdateTime;
                            }
                        }

                        rRcpiHighBound = rRcpi + ROAMING_RCPI_STEP;

                        rLowBoundStep = ((rRcpi - ROAMING_RCPI_STEP) <= ROAMING_WLAN_RCPI_BOUNDARY_THRESHOLD) ? \
                                        ROAMING_RCPI_BOUNDARY_STEP : ROAMING_RCPI_STEP;

                        rRcpiLowBound = ((rRcpi - rLowBoundStep) > RCPI_LOW_BOUND) ? \
                                        (rRcpi - rLowBoundStep) : \
                                        RCPI_LOW_BOUND;

                        DBGLOG(ROAMING, INFO, ("<1> Current RCPI = %d, RSSI = %ld\n",
                            prBssInfo->rRcpi, prBssInfo->rRssi));

                        /* NOTE: (The RCPI INT will arise sooner or later) */

                        /* Enable both High and Low Threshold */
                        nicRRTriggerEnable(prAdapter,
                                           rRcpiHighBound,
                                           rRcpiLowBound);

                        prRoamingInfo->fgIsRCPIEventEnabled = TRUE;

                        prRoamingInfo->fgIsRoamingFail = FALSE;
                        break;
                    }


                    //4 <4> Error handling of RCPI value.
                    if (rRcpi == RCPI_MEASUREMENT_NOT_AVAILABLE) {

                        ASSERT(0);

                        /* NOTE: To read RCPI value again later.
                         * If RCPI Event was enabled, RCPI INT will still come in.
                         * If RCPI Event was NOT enabled, set timer to read it later.
                         * (e.g. The Decision Event after Roaming Stable Timeout.)
                         */
                        if (!prRoamingInfo->fgIsRCPIEventEnabled) {
                            ARB_SET_TIMER(prAdapter,
                                          prRoamingInfo->rRoamingDecisionTimer,
                                          ROAMING_DECISION_INVALID_RCPI_TIMEOUT_MSEC);
                            break;
                        }
                    }


                    //4 <5.A> Update RCPI /RSSI to BSS_INFO_T
                    ASSERT(rRcpi <= RCPI_HIGH_BOUND);

                    prBssInfo->rRcpi = rRcpi;
                    prBssInfo->rRssi = RCPI_TO_dBm(rRcpi);
                    GET_CURRENT_SYSTIME(&prBssInfo->rRssiLastUpdateTime);

                    //4 <5.B> Also update RCPI to P_BSS_DESC_T for compare
                    if ((prBssDesc = scanSearchBssDescByBssid(prAdapter,
                            prBssInfo->aucBSSID)) != (P_BSS_DESC_T)NULL) {
                        prBssDesc->rRcpi = rRcpi;
                        prBssDesc->rUpdateTime = prBssInfo->rRssiLastUpdateTime;
                    }

                    DBGLOG(ROAMING, INFO, ("<2> Current RCPI = %d, RSSI = %ld\n",
                        prBssInfo->rRcpi, prBssInfo->rRssi));


                    //4 <6> Good Signal Field
                    if (prBssInfo->rRcpi >= ROAMING_WLAN_RCPI_THRESHOLD) {

                        DBGLOG(ROAMING, INFO, ("Good Signal Field, Set RCPI threshold = [%d/%d].\n",
                            ROAMING_WLAN_RCPI_THRESHOLD, RCPI_HIGH_BOUND));

                        /* Enable Low Threshold */
                        nicRRTriggerEnable(prAdapter,
                                           RCPI_HIGH_BOUND,
                                           ROAMING_WLAN_RCPI_THRESHOLD);

                        prRoamingInfo->fgIsRCPIEventEnabled = TRUE;
                    }
                    //4 <7> Poor Signal Field
                    else {

                        DBGLOG(ROAMING, INFO, ("Poor Signal Field, Disable RCPI threshold for SCAN.\n"));

                        /* NOTE: (The INT will not arise, but still average RR) */

                        /* Disable both High and Low Threshold, try to Scan and Join */
                        nicRRTriggerDisable(prAdapter);

                        prRoamingInfo->fgIsRCPIEventEnabled = FALSE;

                        /* GSM/WLAN dual band roaming indication */
                        if (prAdapter->fgIsEnableRoamingGsm) {
                            if (prBssInfo->rRcpi >= ROAMING_GSM_RCPI_HIGH_THRESHOLD) {
                                /* TODO(Kevin): call kal() Functions to suggest roam back to WLAN */
                            }
                            else if (prBssInfo->rRcpi <= ROAMING_GSM_RCPI_LOW_THRESHOLD) {
                                /* TODO(Kevin): call kal() Functions to suggest roam back to GSM */
                            }
                        }

                        ASSERT(!prRoamingInfo->fgIsScanTriggered);
                        ASSERT(!prRoamingInfo->fgIsScanCompleted);

#if 0 /* NOTE(Kevin): now we won't check for TimeOut, always apply Scan Request */
                        if (!CHECK_FOR_TIMEOUT(rCurrentTime,
                                              prRoamingInfo->rRoamingDiscoveryUpdateTime,
                                              SEC_TO_SYSTIME(ROAMING_DISCOVERY_TIMEOUT_SEC))) {
                            ROAMING_STATE_TRANSITION(prAdapter, DECISION, ROAM);
                        }
                        else
#endif
                        {
                            ROAMING_STATE_TRANSITION(prAdapter, DECISION, DISCOVERY);
                        }
                    }

                }
                while (FALSE);

            }
            break;

        case ROAMING_STATE_DISCOVERY:
            {
                P_SCAN_REQ_CONFIG_T prScanReqConfig = &prRoamingInfo->rScanReqConfig;

                /* Wait for SCAN completed */
                if (prRoamingInfo->fgIsScanTriggered) {

                    if (prRoamingInfo->fgIsScanCompleted) {
                        ROAMING_STATE_TRANSITION(prAdapter, DISCOVERY, ROAM);
                    }
                    else {
                        /* We will wait another 300 msec to check for SCAN result.
                         */
                        prRoamingInfo->u2DiscoveryTimeoutMillisecond = 300;

                        ARB_SET_TIMER(prAdapter,
                                      prRoamingInfo->rRoamingDiscoveryTimer,
                                      prRoamingInfo->u2DiscoveryTimeoutMillisecond);
                    }
                }
                /* Request for SCAN */
                else {
                    if (PM_IS_VOIP_POLLING_ENABLED(prAdapter)) {
                        prScanReqConfig->eScanMethod = SCAN_METHOD_VOIP_ONLINE_SCAN;

                        /* 12 milliseconds. If detect the air activity by MDRDY,
                         * this is the transmission time of 1Mbps with 1536 Bytes.
                         */
                        prScanReqConfig->ucChnlDwellTimeMin = SCAN_CHANNEL_DWELL_TIME_MIN;

                        /* 20 milliseconds for VOIP application, N = 20 - Min(12) = 8 milliseconds */
                        prScanReqConfig->ucChnlDwellTimeExt = VOIP_SCAN_CHANNEL_DWELL_TIME_EXT;
                    }
                    else if (prConnSettings->fgIsVoipConn) {

                        prScanReqConfig->eScanMethod = SCAN_METHOD_VOIP_ONLINE_SCAN;

                        /* 12 milliseconds. If detect the air activity by MDRDY,
                         * this is the transmission time of 1Mbps with 1536 Bytes.
                         */
                        prScanReqConfig->ucChnlDwellTimeMin = SCAN_CHANNEL_DWELL_TIME_MIN;

                        /* 20 milliseconds for VOIP application, N = 20 - Min(12) = 8 milliseconds */
                        prScanReqConfig->ucChnlDwellTimeExt = VOIP_SCAN_CHANNEL_DWELL_TIME_EXT;
                    }
                    else {
                        prScanReqConfig->eScanMethod = SCAN_METHOD_ONLINE_SCAN;

                        /* 12 milliseconds. If detect the air activity by MDRDY,
                         * this is the transmission time of 1Mbps with 1536 Bytes.
                         */
                        prScanReqConfig->ucChnlDwellTimeMin = SCAN_CHANNEL_DWELL_TIME_MIN;

                        /* N milliseconds = 100TU(Beacon Interval) - min + 10TU
                         * (if Beacon Drift) = 98TU(round down to millisecond).
                         */
                        prScanReqConfig->ucChnlDwellTimeExt = SCAN_CHANNEL_DWELL_TIME_EXT;
                    }

                    prScanReqConfig->ucNumOfPrbReq = ROAMING_SCAN_TOTAL_PROBE_REQ_NUM;
                    prScanReqConfig->ucNumOfSpecifiedSsidPrbReq = \
                        ((prAdapter->rConnSettings.eConnectionPolicy == CONNECT_BY_SSID_ANY) ?
                             0 : ROAMING_SCAN_SPECIFIC_PROBE_REQ_NUM);

                    /* To increase roaming speed, we use following timeout to check
                     * if SCAN was completed.
                     */

                    /* The shortest time to complete SCAN will be
                     * 12 msec x 14 Channels = 168 msec.
                     * So at least we should wait for 300 msec to check SCAN result.
                     */
                    prRoamingInfo->u2DiscoveryTimeoutMillisecond = 300;

                    ARB_SET_TIMER(prAdapter,
                                  prRoamingInfo->rRoamingDiscoveryTimer,
                                  prRoamingInfo->u2DiscoveryTimeoutMillisecond);

                    GET_CURRENT_SYSTIME(&prRoamingInfo->rRoamingDiscoveryUpdateTime);

                    rStatus = WLAN_STATUS_ROAM_DISCOVERY;

                }
            }
            break;

        case ROAMING_STATE_ROAM:
            {
                prRoamingInfo->fgIsScanTriggered = FALSE;
                prRoamingInfo->fgIsScanCompleted = FALSE;

                rStatus = WLAN_STATUS_ROAM_OUT_FIND_BEST;

            }
            break;

        case ROAMING_STATE_IDLE:
            break;

        default:
            ASSERT(0);
            break;
        }


    }
    while (fgIsTransition);


    return rStatus;

} /* end of roamingFsmSteps() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will send START Event to ROAMING FSM.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \retval WLAN_STATUS_FAILURE   If the START Event was not accepted
* \retval WLAN_STATUS_PENDING   Pending for waiting Auth2/4 or AssocResp frame.
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
roamingFsmRunEventStart (
    IN P_ADAPTER_T prAdapter
    )
{
    P_ROAMING_INFO_T prRoamingInfo;
    P_BSS_INFO_T prBssInfo;
    P_SCAN_REQ_CONFIG_T prScanReqConfig;

    DEBUGFUNC("roamingFsmRunEventStart");


    ASSERT(prAdapter);
    prRoamingInfo = &prAdapter->rRoamingInfo;
    prBssInfo = &prAdapter->rBssInfo;
    prScanReqConfig = &prRoamingInfo->rScanReqConfig;

    DBGLOG(ROAMING, EVENT, ("roamingFsmRunEventStart\n"));


    //4 <1> Validation of ROAMING Start Event
    if ((prAdapter->eConnectionState == MEDIA_STATE_DISCONNECTED) ||
        (prBssInfo->eBSSType == BSS_TYPE_IBSS)) {
        DBGLOG(ROAMING, ERROR, ("We should connect to an AP first before enabling the Roaming Module.\n"));
        return WLAN_STATUS_FAILURE;
    }

    //4 <2.A> Start from IDLE, this should be the 1st time JOIN.
    if (prRoamingInfo->eCurrentState == ROAMING_STATE_IDLE) {

        //4 <3> Update local SCAN Request Configuration Structure.
        kalMemZero(&prScanReqConfig->rSpecifiedSsid,
                   sizeof(PARAM_SSID_T));

        COPY_SSID(prScanReqConfig->rSpecifiedSsid.aucSsid,
                  prScanReqConfig->rSpecifiedSsid.u4SsidLen,
                  prBssInfo->aucSSID,
                  (UINT_32)prBssInfo->ucSSIDLen);

        prScanReqConfig->eScanType = SCAN_TYPE_ACTIVE_SCAN;

        prScanReqConfig->pfScanDoneHandler = roamingDiscoveryScanDoneHandler;
    }
    //4 <2.B> Start from ROAM, successfully roaming to other BSS.
    else if (prRoamingInfo->eCurrentState == ROAMING_STATE_ROAM) {
        /* NOTE: There are 2 cases from JOIN to NORMAL_TR.
         * 1. Do transition of JOIN to NORMAL_TR after joinComplete().
         *    So we'll update the rRoamingStableExpirationTime.
         *    If Roaming Stable was not expired, will set the fgIsRoamingFail to FALSE.
         * 2. Event of JOIN fail (e.g. JoinTxTimeOut()).
         *    So we'll set the fgIsRoamingFail = TRUE;
         */
        prRoamingInfo->fgIsRoamingFail = TRUE;
    }
    //4 <2.C> The previous ROAMING process is hanging in other STATE ?
    else {
        DBGLOG(ROAMING, ERROR, ("ROAMING Module is hanging in %s.\n",
            ((prRoamingInfo->eCurrentState == ROAMING_STATE_DECISION) ?
             "ROAMING_STATE_DECISION" : "ROAMING_STATE_ROAM")));
        ASSERT(0);
        return WLAN_STATUS_FAILURE;
    }


    /* NOTE(Kevin): The number of RF channels we intend to scan will be setup after
     * receiving the Roaming Start Event each time.
     *     prScanReqConfig->arChnlInfoList[];
     *     prScanReqConfig->ucNumOfScanChnl;
     */

    {
        UINT_32 i, j, u4ScanIndex = 0;
        UINT_32 u4NumOfElem = 0;

        if (sizeof(prScanReqConfig->arChnlInfoList[0]) != 0) {
            u4NumOfElem = sizeof(prScanReqConfig->arChnlInfoList) /
                sizeof(prScanReqConfig->arChnlInfoList[0]);
        }

        prScanReqConfig->ucNumOfScanChnl = (UINT_8)prAdapter->u2NicOpChnlNum;

        for (j = 0; j < INTERLACED_SCAN_CHANNEL_GROUPS_NUM; j++) {

            for (i = j; i < prScanReqConfig->ucNumOfScanChnl;
                i += INTERLACED_SCAN_CHANNEL_GROUPS_NUM, u4ScanIndex++) {
                /* add boundary checking */
                if ((u4ScanIndex < u4NumOfElem) && (i < MAXIMUM_OPERATION_CHANNEL_LIST)) {
                    prScanReqConfig->arChnlInfoList[u4ScanIndex].ucChannelNum =
                        prAdapter->arNicOpChnList[i].ucChannelNum;

                    prScanReqConfig->arChnlInfoList[u4ScanIndex].eBand =
                        prAdapter->arNicOpChnList[i].eBand;
                }
                else {
                    ERRORLOG(("boundary checking fail: u4ScanIndex(%ld) < u4NumOfElem(%ld), i(%ld) < MAXIMUM_OPERATION_CHANNEL_LIST(%d)",
                        u4ScanIndex, u4NumOfElem, i, MAXIMUM_OPERATION_CHANNEL_LIST));
                    ASSERT(FALSE);
                }
            }
        }
    }

    /* Trigger ROAMING MODULE */
    return roamingFsmSteps(prAdapter, ROAMING_STATE_DECISION);

} /* end of roamingFsmRunEventStart() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will send ROAMING FAIL Event to ROAMING FSM.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
roamingFsmRunEventRoamFail (
    IN P_ADAPTER_T prAdapter
    )
{
    P_ROAMING_INFO_T prRoamingInfo;

    DEBUGFUNC("roamingFsmRunEventStart");


    ASSERT(prAdapter);
    prRoamingInfo = &prAdapter->rRoamingInfo;

    DBGLOG(ROAMING, EVENT, ("\n\nroamingFsmRunEventRoamFail\n\n"));

    if (prRoamingInfo->eCurrentState == ROAMING_STATE_ROAM) {

        prRoamingInfo->fgIsRoamingFail = TRUE;

        /* Trigger ROAMING MODULE */
        roamingFsmSteps(prAdapter, ROAMING_STATE_DECISION);
    }

    return;
} /* end of roamingFsmRunEventRoamFail() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will send ABORT Event to ROAMING FSM.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
roamingFsmRunEventAbort (
    IN P_ADAPTER_T prAdapter
    )
{
    P_ROAMING_INFO_T prRoamingInfo;
    ENUM_ROAMING_STATE_T eNextState;
    BOOLEAN fgIsTransition = (BOOLEAN)FALSE;

    DEBUGFUNC("roamingFsmRunEventAbort");


    ASSERT(prAdapter);
    prRoamingInfo = &prAdapter->rRoamingInfo;
    eNextState = prRoamingInfo->eCurrentState;

    DBGLOG(ROAMING, EVENT, ("roamingFsmRunEventAbort\n"));

    //4 <1> Do abort event.
    switch(prRoamingInfo->eCurrentState) {

    case ROAMING_STATE_DECISION:
        {
            ROAMING_STATE_TRANSITION(prAdapter, DECISION, IDLE);
        }
        break;

    case ROAMING_STATE_DISCOVERY:
        {
            ROAMING_STATE_TRANSITION(prAdapter, DISCOVERY, IDLE);
        }
        break;

    case ROAMING_STATE_ROAM:
        {
            ROAMING_STATE_TRANSITION(prAdapter, ROAM, IDLE);
        }
        break;

    default:
        break;
    }

    /* Call arbFsmSteps() when we are going to change ARB STATE */
    if (prRoamingInfo->eCurrentState != eNextState) {
        roamingFsmSteps(prAdapter, eNextState);
    }

    return;
} /* end of roamingFsmRunEventAbort() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will send RCPI Event(exceed the RCPI threshold) to ROAMING FSM.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \retval WLAN_STATUS_PENDING               Pending for waiting next trigger event.
* \retval WLAN_STATUS_ROAM_DISCOVERY        Try to do scan and update scan result.
* \retval WLAN_STATUS_ROAM_OUT_FIND_BEST    Try to roam out if have candidate.
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
roamingFsmRunEventRCPI (
    IN P_ADAPTER_T prAdapter
    )
{
    P_ROAMING_INFO_T prRoamingInfo;
    ENUM_ROAMING_STATE_T eNextState;
    WLAN_STATUS rStatus = WLAN_STATUS_PENDING;

    DEBUGFUNC("roamingFsmRunEventRCPI");


    ASSERT(prAdapter);
    prRoamingInfo = &prAdapter->rRoamingInfo;
    eNextState = prRoamingInfo->eCurrentState;

    DBGLOG(ROAMING, EVENT, ("roamingFsmRunEventRCPI\n"));

    if (prRoamingInfo->eCurrentState == ROAMING_STATE_DECISION) {

        rStatus = roamingFsmSteps(prAdapter, eNextState);
    }
#if DBG
    else {
        ASSERT(0);
    }
#endif

    return rStatus;

} /* end of roamingFsmRunEventRCPI() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will send DECISION Event(Request by Timer) to ROAMING FSM.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \retval WLAN_STATUS_PENDING               Pending for waiting next trigger event.
* \retval WLAN_STATUS_ROAM_DISCOVERY        Try to do scan and update scan result.
* \retval WLAN_STATUS_ROAM_OUT_FIND_BEST    Try to roam out if have candidate.
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
roamingFsmRunEventDecision (
    IN P_ADAPTER_T prAdapter
    )
{
    P_ROAMING_INFO_T prRoamingInfo;
    ENUM_ROAMING_STATE_T eNextState;
    WLAN_STATUS rStatus = WLAN_STATUS_PENDING;

    DEBUGFUNC("roamingFsmRunEventDecision");


    ASSERT(prAdapter);
    prRoamingInfo = &prAdapter->rRoamingInfo;
    eNextState = prRoamingInfo->eCurrentState;

    DBGLOG(ROAMING, EVENT, ("roamingFsmRunEventDecision\n"));

    if (prRoamingInfo->eCurrentState == ROAMING_STATE_DECISION) {

        rStatus = roamingFsmSteps(prAdapter, eNextState);
    }
#if DBG
    else {
        ASSERT(0);
    }
#endif

    return rStatus;

} /* end of roamingFsmRunEventDecision() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will send DISCOVERY Event(Request by Timer) to ROAMING FSM.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \retval WLAN_STATUS_PENDING               Pending for waiting next trigger event.
* \retval WLAN_STATUS_ROAM_DISCOVERY        Try to do scan and update scan result.
* \retval WLAN_STATUS_ROAM_OUT_FIND_BEST    Try to roam out if have candidate.
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
roamingFsmRunEventDiscovery (
    IN P_ADAPTER_T prAdapter
    )
{
    P_ROAMING_INFO_T prRoamingInfo;
    ENUM_ROAMING_STATE_T eNextState;
    WLAN_STATUS rStatus = WLAN_STATUS_PENDING;

    DEBUGFUNC("roamingFsmRunEventDiscovery");


    ASSERT(prAdapter);
    prRoamingInfo = &prAdapter->rRoamingInfo;
    eNextState = prRoamingInfo->eCurrentState;

    DBGLOG(ROAMING, EVENT, ("roamingFsmRunEventDiscovery\n"));

    if (prRoamingInfo->eCurrentState == ROAMING_STATE_DISCOVERY) {

        rStatus = roamingFsmSteps(prAdapter, eNextState);
    }
#if DBG
    else {
        ASSERT(0);
    }
#endif

    return rStatus;

} /* end of roamingFsmRunEventDiscovery() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function is used for SCAN DONE Handler to know that SCAN was completed.
*        So we can try to do roaming.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
roamingDiscoveryScanDoneHandler (
    IN P_ADAPTER_T prAdapter,
    IN WLAN_STATUS rStatus
    )
{
    P_ROAMING_INFO_T prRoamingInfo;


    DEBUGFUNC("roamingDiscoveryScanDoneHandler");


    ASSERT(prAdapter);
    prRoamingInfo = &prAdapter->rRoamingInfo;

    DBGLOG(ROAMING, EVENT, ("roamingDiscoveryScanDoneHandler: %s\n",
        ((rStatus == WLAN_STATUS_SUCCESS) ? "WLAN_STATUS_SUCCESS" : "WLAN_STATUS_FAILURE" )));

    prRoamingInfo->fgIsScanCompleted = TRUE;

    return;
} /* end of roamingDiscoveryScanDoneHandler() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function is used for error handling, if ARB cannot process the ROAMING
*        DECISION Event, schedule a timer to do such event again in a later time.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
roamingReTriggerEventDecision (
    IN P_ADAPTER_T prAdapter
    )
{
    P_ROAMING_INFO_T prRoamingInfo;

    DEBUGFUNC("roamingReTriggerEventDecision");


    ASSERT(prAdapter);
    prRoamingInfo = &prAdapter->rRoamingInfo;

    DBGLOG(ROAMING, EVENT, ("roamingReTriggerEventDecision\n"));

    ARB_SET_TIMER(prAdapter,
                  prRoamingInfo->rRoamingDecisionTimer,
                  SEC_TO_MSEC(ROAMING_DECISION_TIMEOUT_SEC));

    return;
} /* end of roamingReTriggerEventDecision() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function is used for error handling, if ARB cannot process the ROAMING
*        DISCOVERY Event, schedule a timer to do such event again in a later time.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
roamingReTriggerEventDiscovery (
    IN P_ADAPTER_T prAdapter
    )
{
    P_ROAMING_INFO_T prRoamingInfo;

    DEBUGFUNC("roamingReTriggerEventDiscovery");


    ASSERT(prAdapter);
    prRoamingInfo = &prAdapter->rRoamingInfo;

    DBGLOG(ROAMING, EVENT, ("roamingReTriggerEventDiscovery\n"));

    ARB_SET_TIMER(prAdapter,
                  prRoamingInfo->rRoamingDiscoveryTimer,
                  prRoamingInfo->u2DiscoveryTimeoutMillisecond);

    return;
} /* end of roamingReTriggerEventDiscovery() */


