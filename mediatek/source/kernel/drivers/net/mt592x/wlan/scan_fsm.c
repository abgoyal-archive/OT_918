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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/scan_fsm.c#2 $
*/

/*! \file   "scan_fsm.c"
    \brief  This file defines the state transition function for SCAN FSM.

    The SCAN FSM is responsible for performing SCAN behavior when the Arbiter enter
    ARB_STATE_SCAN. The STATE and EVENT for SCAN FSM are defined here with detail 
    description.

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
** $Log: scan_fsm.c $
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\55 2009-08-20 16:55:00 GMT mtk01090
**  Correct debug message level in scan complete indication
**  \main\maintrunk.MT5921\54 2009-08-18 22:56:24 GMT mtk01090
**  Add Linux SDIO (with mmc core) support.
**  Add Linux 2.6.21, 2.6.25, 2.6.26.
**  Fix compile warning in Linux.
**  \main\maintrunk.MT5921\53 2009-07-24 16:01:07 GMT mtk01090
**  Rewrite to shorten then line number of duplication
**  \main\maintrunk.MT5921\52 2008-12-01 18:19:24 GMT mtk01088
**  fixed the lint "possible using null pointer" warning
**  \main\maintrunk.MT5921\51 2008-10-22 10:59:04 GMT mtk01461
**  Update for lint diagnosis support
**  \main\maintrunk.MT5921\50 2008-10-13 10:22:09 GMT mtk01461
**  Remove define of minimum life time
**  \main\maintrunk.MT5921\49 2008-09-02 11:29:02 GMT mtk01084
**  Workaround CR1097, driver will always disable scan function for preventing SW/ HW state un-synchronized issue.
**  \main\maintrunk.MT5921\48 2008-08-11 09:40:10 GMT mtk01461
**  Update for Driver Review
**  \main\maintrunk.MT5921\47 2008-07-21 12:01:54 GMT mtk01084
**  modify parameters on  scan dwell time
**  \main\maintrunk.MT5921\46 2008-07-10 16:37:56 GMT mtk01084
**  support 802.11d related functions
**  \main\maintrunk.MT5921\45 2008-07-02 09:13:40 GMT mtk01084
**  Workaround for the case that the scan is continuously blocked in scan initial phase
**  \main\maintrunk.MT5921\44 2008-07-01 20:10:35 GMT mtk01084
**  rename the scan method
**  \main\maintrunk.MT5921\43 2008-07-01 10:54:22 GMT mtk01084
**  modifications for replacing previous VoIP scan under CAM for existing method for VoIP scan
**  \main\maintrunk.MT5921\42 2008-06-17 17:47:12 GMT mtk01425
**  1. Miss declaration of variable
**  \main\maintrunk.MT5921\41 2008-06-17 16:48:46 GMT mtk01425
**  1. Modify return of scanSendProbeReqFrames
**  \main\maintrunk.MT5921\40 2008-06-12 20:29:47 GMT mtk01461
**  Remove unused compile flag of SCAN module which is work around for MPW
**  \main\maintrunk.MT5921\39 2008-06-01 14:03:31 GMT mtk01084
**  sanity check on the scan type
**  \main\maintrunk.MT5921\38 2008-04-28 17:09:35 GMT mtk01084
**  use logic reset instead of send a dummy probe request to workaround HEC 5512
**  \main\maintrunk.MT5921\37 2008-04-21 13:46:44 GMT mtk01084
**  not to enable packet lifetime when transmitting probe request on workaround of HEC 5512
**  \main\maintrunk.MT5921\36 2008-04-17 22:09:35 GMT mtk01084
**  modify send probe request argument
**  \main\maintrunk.MT5921\35 2008-04-16 15:22:03 GMT mtk01461
**  Remove Cancel check for hang timer of SCAN module when leave BG_SSID_SCAN
**  \main\maintrunk.MT5921\34 2008-03-26 18:31:11 GMT mtk01084
**  flush AC4 after scan is done
**  \main\maintrunk.MT5921\33 2008-03-25 22:55:25 GMT mtk01084
**  add workaround lines for prevent TX done false alarm during scan
**  \main\maintrunk.MT5921\32 2008-03-21 18:16:12 GMT mtk01084
**  reset scan done event on scan abort
**  \main\maintrunk.MT5921\31 2008-03-19 15:22:04 GMT mtk01461
**  Set SCAN interval to 1 active + 1 passive + 1 active + 1 passive for VOIP
**  \main\maintrunk.MT5921\30 2008-03-18 19:39:13 GMT mtk01084
**  unset the scan done event when aborting scan function
**  \main\maintrunk.MT5921\29 2008-03-13 15:32:05 GMT mtk01461
**  Refine the relationship between SCAN result and STA record, lifetime, aging policy etc
**  \main\maintrunk.MT5921\28 2008-03-03 18:10:22 GMT mtk01084
**  modify function description comments
**  \main\maintrunk.MT5921\27 2008-02-18 17:45:39 GMT mtk01084
**  add the missed return status
**  \main\maintrunk.MT5921\26 2008-02-18 17:41:42 GMT mtk01084
**  modify structure naming
**  \main\maintrunk.MT5921\25 2008-02-18 17:23:25 GMT mtk01084
**  add function description
**  \main\maintrunk.MT5921\24 2008-02-01 10:07:53 GMT mtk01385
**  1. Fix WinCE 4.2 compiling error.
**  \main\maintrunk.MT5921\23 2007-12-25 23:35:00 GMT mtk01084
**  only to get the last scan channel index when it's under normal scan
**  \main\maintrunk.MT5921\22 2007-12-11 14:57:09 GMT MTK01084
**  restore deleted lines by previous version
**  \main\maintrunk.MT5921\21 2007-12-11 00:10:21 GMT mtk01461
**  Update postfix of SCAN Guard Time define
**  \main\maintrunk.MT5921\20 2007-12-10 20:17:20 GMT mtk01084
**  invoke reset SCAN DONE event on scan start request
**  \main\maintrunk.MT5921\19 2007-12-08 22:30:59 GMT mtk01084
**  modify scan procedure
**  \main\maintrunk.MT5921\18 2007-12-04 18:09:43 GMT mtk01461
**  Unify the SCAN Status Process for both MPW and new scheme after 11/27
**  \main\maintrunk.MT5921\17 2007-11-29 01:55:28 GMT mtk01461
**  Add new SCAN result support (after 11/27 bit file)
**  \main\maintrunk.MT5921\16 2007-11-27 15:13:34 GMT mtk01084
**  modify last scan channel check to meet latest data sheet definition
**  \main\maintrunk.MT5921\15 2007-11-26 19:38:31 GMT mtk01461
**  Unify SCAN
**  \main\maintrunk.MT5921\14 2007-11-21 11:41:22 GMT mtk01084
**  modify to meet Lint requirement
**  \main\maintrunk.MT5921\13 2007-11-13 10:34:34 GMT mtk01084
**  control RX filters under scan state, and do code refinement
**  \main\maintrunk.MT5921\12 2007-11-12 16:16:20 GMT mtk01084
**  modify scan dwell time length from 16 bit to 8 bit
**  \main\maintrunk.MT5921\11 2007-11-09 12:49:48 GMT mtk01084
**  modify initial macro naming
**  \main\maintrunk.MT5921\10 2007-11-08 13:57:37 GMT mtk01084
**  force to invalid service period when starting BG SSID scan
**  \main\maintrunk.MT5921\9 2007-11-01 14:47:03 GMT mtk01084
**  modify variable naming of the u4ScanDwellTimeMax to u4ScanDwellTimeExt
**  \main\maintrunk.MT5921\8 2007-10-26 10:13:59 GMT mtk01084
**  support BG SSID scan state machine
**  \main\maintrunk.MT5921\7 2007-10-25 18:05:14 GMT mtk01461
**  Add VOIP SCAN Support  & Refine Roaming
** Revision 1.4  2007/07/05 14:15:10  MTK01084
** temporarily remark off the implementations
**
** Revision 1.3  2007/07/05 14:10:35  MTK01084
** update transition paths in scan FSM
**
** Revision 1.2  2007/06/27 02:14:00  MTK01461
** Update SCAN_FSM, Initial(Can Load Module), Proc(Can do Reg R/W), TX API
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
static PUINT_8 apucDebugScanState[SCAN_STATE_NUM] = {
    DISP_STRING("SCAN_STATE_IDLE"),
    DISP_STRING("SCAN_STATE_ACTIVE"),
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
* \brief This routine is used to initialize scan FSM.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
scanFsmInit (
    P_ADAPTER_T prAdapter
    )
{
    P_SCAN_INFO_T prScanInfo;
    P_SCAN_CONFIG_T prScanConfig;


    ASSERT(prAdapter);

    prScanInfo = &prAdapter->rScanInfo;
    prScanConfig = &prScanInfo->rScanConfig;

    prScanInfo->eCurrentState = SCAN_STATE_IDLE;

    ARB_INIT_TIMER(prAdapter,
                   prScanInfo->rScanCheckForHangTimer,
                   arbFsmRunEventScanCheckForHangTimeOut,
                   TRUE);

    ARB_INIT_TIMER(prAdapter,
                   prScanInfo->rPartialScanTimer,
                   arbFsmRunEventScanPartialScanTimeOut,
                   TRUE);


    /* Initial the scan config */
    prScanConfig->eScanType                     = DEFAULT_SCAN_TYPE;
    prScanConfig->ucChnlDwellTimeMin            = DEFAULT_SCAN_PER_CHNL_MIN_DWELL_TIME;
    prScanConfig->ucChnlDwellTimeExt            = DEFAULT_SCAN_PER_CHNL_EXT_DWELL_TIME;
    prScanConfig->u2RxFifoThreshold             = DEFAULT_SCAN_RX_FIFO_THRESHOLD;
    prScanConfig->ucNumOfPrbReq                 = DEFAULT_SCAN_NUM_OF_PROBE_REQUEST;
    prScanConfig->ucNumOfSpecifiedSsidPrbReq    = DEFAULT_SCAN_NUM_OF_SPECIFIED_PROBE_REQ;
    prScanConfig->fgToHonorServicePeriod        = DEFAULT_SCAN_HONOR_SERVICE_PERIOD;
    prScanConfig->fgToEnableTriggerEvent        = DEFAULT_SCAN_ENABLE_TRIGGER_EVENT;

    prScanConfig->rBgScanCfg.u2BaseWakePeriod   = BG_SSID_SCAN_BASE_WAKEUP_PERIOD;
    prScanConfig->rBgScanCfg.ucBgScanStepOfWakePeriod = BG_SSID_SCAN_WAKEUP_PERIOD_STEPS;
    prScanConfig->rBgScanCfg.ucBgScanMinRcpiThr = BG_SSID_SCAN_WAKEUP_MIN_RCPI;

    prScanInfo->fgIsScanReqProceeding           = FALSE;

    return;
}


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is the transition from IDLE to ACTIVE.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ VOID
scanFsmTransAction_IDLE_to_ACTIVE (
    IN P_ADAPTER_T prAdapter
    )
{
    P_SCAN_INFO_T prScanInfo;
    P_SCAN_CONFIG_T prScanCfg;
    UINT_32 rStatus = WLAN_STATUS_SUCCESS;
#if CFG_SUPPORT_802_11D
    P_CONNECTION_SETTINGS_T prConnSettings;
#endif

    ASSERT(prAdapter);

#if CFG_SUPPORT_802_11D
    prConnSettings = &prAdapter->rConnSettings;
#endif

    prScanInfo = &prAdapter->rScanInfo;
    prScanCfg = &prScanInfo->rScanConfig;

    /* For the state transition from BG SSID scan to SCAN, scan done interrupt
       will be generated from the exit of BG SSID scan (LP own back).
       So clearing the scan done interrupt status is to prevent the confusion
       whether the scan done is generated by SCAN or BG SSID scan.
    */
    NIC_RESET_INT_EVENT(prAdapter, INT_EVENT_SCAN_DONE);

#if CFG_WORKAROUND_HEC_5269
    /* Unset TX_DONE event */
    NIC_UNSET_INT_EVENT(prAdapter, INT_EVENT_TX);
#endif

    if (prScanCfg->ucNumOfPrbReq == 0) {
        if (prScanCfg->eScanType == SCAN_TYPE_ACTIVE_SCAN) {
            prScanCfg->eScanType = SCAN_TYPE_PASSIVE_SCAN;
            ASSERT(0);
        }
    }

#if CFG_SUPPORT_802_11D
    /*   Force to use Passive Scan if multi-domain function is enabled and
     * domain information is not available.
     *   Only one scan dwell time is applied, which is combined min. and max.
     * scan dwell time.
     */
    if (prConnSettings->fgMultiDomainCapabilityEnabled) {
        if (prAdapter->eConnectionState == MEDIA_STATE_DISCONNECTED) {
            prScanCfg->eScanType = SCAN_TYPE_PASSIVE_SCAN;
            prScanCfg->ucChnlDwellTimeMin += prScanCfg->ucChnlDwellTimeExt;
            prScanCfg->ucChnlDwellTimeExt = 0;
        } else {
            P_BSS_INFO_T prBssInfo = &prAdapter->rBssInfo;
            if (!prBssInfo->fgIsCountryInfoPresent) {
                prScanCfg->eScanType = SCAN_TYPE_PASSIVE_SCAN;
                prScanCfg->ucChnlDwellTimeMin += prScanCfg->ucChnlDwellTimeExt;
                prScanCfg->ucChnlDwellTimeExt = 0;
            }
        }
    }
#endif

    /* Submit probe request frame(s) if Active Scan is applied */
    if (prScanCfg->eScanType == SCAN_TYPE_ACTIVE_SCAN) {
        if ((rStatus = scanSendProbeReqFrames(prAdapter,
                                   prScanCfg->rSpecifiedSsid.aucSsid,
                                   prScanCfg->rSpecifiedSsid.u4SsidLen,
                                   prScanCfg->ucNumOfPrbReq,
                                   prScanCfg->ucNumOfSpecifiedSsidPrbReq)) != WLAN_STATUS_PENDING) {

            if(rStatus != WLAN_STATUS_SUCCESS) {
            ASSERT(0);
            }
            //error handling ?

            return;
        }
    }

    /* Configure HW scan parameters, which is through share memory input */
    nicHwScanConfig(prAdapter, prScanCfg, prScanInfo->eCurrentHwScanMode);

    /* Disable beacon timeout counter during scan */
    nicpmDisableTimeoutCounter(prAdapter);

    /* Set RX filter to receive beacon from different BSSID */
    NIC_SET_RX_FILTER(prAdapter, RXFILTER_RXDIFFBSSIDBCN);

    /* Set RX filter to receive probe response from different BSSID */
    NIC_SET_RX_FILTER(prAdapter, RXFILTER_RXDIFFBSSIDPRORESP);


    /* Enable HW scan */
    nicHwScanEnable(prAdapter, prScanInfo->eCurrentHwScanMode);

    return;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is the transition from ACTIVE to IDLE_DONE.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ VOID
scanFsmTransAction_ACTIVE_to_IDLE_DONE (
    IN P_ADAPTER_T prAdapter
    )
{
    /* This is to workaround CR1097.
     * Driver will always disable scan function for preventing SW/ HW state
     * un-synchronized issue.
     */
    P_SCAN_INFO_T prScanInfo;

    ASSERT(prAdapter);

    prScanInfo = &prAdapter->rScanInfo;

    nicHwScanDisable(
        prAdapter,
        prScanInfo->eCurrentHwScanMode);

    return;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is the transition from ACTIVE to IDLE_ABORT.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ VOID
scanFsmTransAction_ACTIVE_to_IDLE_ABORT (
    IN P_ADAPTER_T prAdapter
    )
{
    P_SCAN_INFO_T prScanInfo;

    ASSERT(prAdapter);

    prScanInfo = &prAdapter->rScanInfo;

    nicHwScanDisable(
        prAdapter,
        prScanInfo->eCurrentHwScanMode);

    return;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is the state machine step function.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
* \param[in] eNextState The state value to be stepped into.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
scanFsmStep (
    IN P_ADAPTER_T          prAdapter,
    IN ENUM_SCAN_STATE_T    eNextState
    )
{
    P_SCAN_INFO_T prScanInfo;
    P_SCAN_STATUS_T prScanStatus;

    DEBUGFUNC("scanFsmStep");

    ASSERT(prAdapter);

    prScanInfo = &prAdapter->rScanInfo;
    prScanStatus = &prScanInfo->rScanStatus;


    DBGLOG(SCAN, STATE, ("TRANSITION: [%s] -> [%s]\n",
                         apucDebugScanState[prScanInfo->eCurrentState],
                         apucDebugScanState[eNextState]));

    prScanInfo->eCurrentState = eNextState;

    /* Do tasks of the State that we just entered */
    switch (prScanInfo->eCurrentState) {
    case SCAN_STATE_IDLE:
        /* Enable beacon timeout counter, which is disabled during scan */
        nicpmEnableTimeoutCounter(prAdapter);

        /* Set RX filter for not to receive beacon from different BSSID */
        NIC_UNSET_RX_FILTER(prAdapter, RXFILTER_RXDIFFBSSIDBCN);

        /* Set RX filter for not to receive probe response from different BSSID */
        NIC_UNSET_RX_FILTER(prAdapter, RXFILTER_RXDIFFBSSIDPRORESP);

#if CFG_WORKAROUND_HEC_5269
        /* Flush AC4 before set TX_DONE event */
        nicTxFlushStopQueues(prAdapter, TXQ_MGMT_MASK, 0x0 /*(UINT_8)NULL*/);

        /* Set TX_DONE event */
        NIC_SET_INT_EVENT(prAdapter, INT_EVENT_TX);
#endif

        nicHwScanConfigRestore(prAdapter,
                               &prScanInfo->rScanConfig,
                               prScanInfo->eCurrentHwScanMode);

        if (prScanInfo->eCurrentHwScanMode == ENUM_HW_SCAN_NORMAL_SCAN) {
            DBGLOG(SCAN, INFO, (">>ucLastScanChnlIdx = %d,  ucLastScanBandIdx = %d.\n",
                prScanStatus->ucLastScanChnlIdx, prScanStatus->ucLastScanBandIdx));

            nicHwScanGetLastScannedChnlFreq(
                prAdapter,
                &prScanStatus->ucLastScanChnlIdx,
                &prScanStatus->ucLastScanBandIdx);

            DBGLOG(SCAN, INFO, ("<<ucLastScanChnlIdx = %d,  ucLastScanBandIdx = %d.\n",
                prScanStatus->ucLastScanChnlIdx, prScanStatus->ucLastScanBandIdx));

            DBGLOG(SCAN, INFO, ("ucNumOfScanChnl = %d\n", prScanInfo->rScanConfig.ucNumOfScanChnl));
        }
        break;

    case SCAN_STATE_ACTIVE:
        break;

    default:
        ASSERT(0); /* Make sure we have handle all STATEs */
    }

    return;

}


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to setup the necessary information for scan request.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
* \param[in] prScanReqConfig Pointer to the scan request configurations.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_FAILURE
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
scanFsmRunEventScanReqSetup (
    IN P_ADAPTER_T prAdapter,
    IN P_SCAN_REQ_CONFIG_T prScanReqConfig
    )
{
    P_SCAN_INFO_T prScanInfo;
    P_SCAN_CONFIG_T prScanCfg;

    DEBUGFUNC("scanFsmRunEventScanReqSetup");

    ASSERT(prAdapter);

    prScanInfo = &prAdapter->rScanInfo;
    prScanCfg = &prScanInfo->rScanConfig;

    // New SCAN Request.
    if (prScanReqConfig) {

        // Previous SCAN is finished.
        if (!prScanInfo->fgIsScanReqProceeding) {

            //4 <1> Setup the SCAN Config - Basic Parameters
            /* Update SCAN Type */
            prScanCfg->eScanType = prScanReqConfig->eScanType;

            /* Update SCAN Channel List */
            DBGLOG(SCAN, TRACE, ("prScanReqConfig->ucNumOfScanChnl = %d\n",
                prScanReqConfig->ucNumOfScanChnl));

            kalMemCopy(&prScanCfg->arChnlInfoList[0],
                       &prScanReqConfig->arChnlInfoList[0],
                       prScanReqConfig->ucNumOfScanChnl * sizeof(RF_CHANNEL_INFO_T));

#if DBG
            {
                UINT_32 i;

                for (i = 0; i < prScanReqConfig->ucNumOfScanChnl; i++) {
                    DBGLOG(SCAN, TRACE, ("prScanCfg->arChnlInfoList[%ld].ucChannelNum = %d, eBand = %d\n",
                        i, prScanCfg->arChnlInfoList[i].ucChannelNum, prScanCfg->arChnlInfoList[i].eBand));
                }
            }
#endif /* DBG */

            /* Update total SCAN Channel number */
            prScanCfg->ucTotalScanChannelCount = prScanReqConfig->ucNumOfScanChnl;
            prScanCfg->ucFinishedChannelCount = 0;

            /* Update MinChannelTime
             *        ExtChannelTime = (MaxChannelTime - MinChannelTime) in TU.
             */
            prScanCfg->ucChnlDwellTimeMin = prScanReqConfig->ucChnlDwellTimeMin;
            prScanCfg->ucChnlDwellTimeExt = prScanReqConfig->ucChnlDwellTimeExt;

            DBGLOG(SCAN, TRACE, ("prScanCfg->u2ChnlDwellTimeMin = %d, prScanCfg->u2ChnlDwellTimeExt = %d\n",
                prScanCfg->ucChnlDwellTimeMin, prScanCfg->ucChnlDwellTimeExt));

            prScanCfg->rSpecifiedSsid = prScanReqConfig->rSpecifiedSsid;

            /* Specify number of ProbeReq for Active SCAN */
            prScanCfg->ucNumOfPrbReq = prScanReqConfig->ucNumOfPrbReq;
            prScanCfg->ucNumOfSpecifiedSsidPrbReq = prScanReqConfig->ucNumOfSpecifiedSsidPrbReq;

            /* Update SCAN DONE call back handler */
            prScanCfg->pfScanDoneHandler = prScanReqConfig->pfScanDoneHandler;


            //4 <2> Setup the SCAN Config - Advanced Parameters
            /* Update SCAN Method */
            prScanCfg->eScanMethod = prScanReqConfig->eScanMethod;
            if (prScanReqConfig->eScanMethod == SCAN_METHOD_FULL_SCAN) {
                /* Update SCAN Priority */
                prScanCfg->fgToHonorServicePeriod = FALSE;
                prScanCfg->fgToEnableTriggerEvent = FALSE;

                /* Try to scan all channel in a request */
                prScanCfg->ucNumOfScanChnl = prScanCfg->ucTotalScanChannelCount;
                prScanCfg->ucNumOfPassiveScanInVoIP = 0;
            }
            else if (prScanReqConfig->eScanMethod == SCAN_METHOD_ONLINE_SCAN) {
                /* Update SCAN Priority */
                prScanCfg->fgToHonorServicePeriod = TRUE;
                prScanCfg->fgToEnableTriggerEvent = TRUE;

                /* Try to scan all channel in a request */
                prScanCfg->ucNumOfScanChnl = prScanCfg->ucTotalScanChannelCount;
                prScanCfg->ucNumOfPassiveScanInVoIP = 0;
            }
            else if (prScanReqConfig->eScanMethod == SCAN_METHOD_VOIP_ONLINE_SCAN) {
                /* Update SCAN Priority */
                prScanCfg->fgToHonorServicePeriod = TRUE;
                prScanCfg->fgToEnableTriggerEvent = TRUE;

                /* Try to scan 1 channel in a request */
                prScanCfg->ucNumOfScanChnl = 1;
                prScanCfg->ucNumOfPassiveScanInVoIP = SCAN_VOIP_PASSIVE_SCAN_INTERVAL;
            }
            else {
                ASSERT(0);
            }

            /* Update RX Fifo Threshold */
            prScanCfg->u2RxFifoThreshold = 0;


            //4 <3> Clear previous SCAN status
            prScanInfo->rScanStatus.ucLastScanChnlIdx = 0;
            prScanInfo->rScanStatus.ucLastScanBandIdx = 0;


            //4 <4> Update SCAN proceeding flag
            prScanInfo->fgIsScanReqProceeding = TRUE;

        }
        else {
            return WLAN_STATUS_FAILURE; /* Previous SCAN was not finished yet */
        }
    }
    else {
        if (!prScanInfo->fgIsScanReqProceeding) {
            ASSERT(0);
            return WLAN_STATUS_FAILURE; /* We didn't have proper SCAN Config for PARTIAL SCAN. */
        }
    }

    ASSERT(prScanInfo->fgIsScanReqProceeding);

    return WLAN_STATUS_SUCCESS;

}


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to do scan request clean up procedure.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
scanFsmRunEventScanReqCleanUp (
    IN P_ADAPTER_T prAdapter
    )
{
    P_SCAN_INFO_T prScanInfo;
    P_SCAN_CONFIG_T prScanCfg;

    DEBUGFUNC("scanFsmRunEventScanReqCleanUp");

    ASSERT(prAdapter);
    prScanInfo = &prAdapter->rScanInfo;
    prScanCfg = &prScanInfo->rScanConfig;

    /* We should call Scan Abort before doing "Request Clean Up" */
    if (prScanInfo->fgIsScanReqProceeding) {
        ASSERT(prScanInfo->eCurrentState == SCAN_STATE_IDLE);

        if (prScanCfg->eScanMethod == SCAN_METHOD_ONLINE_SCAN) {
            ARB_CANCEL_TIMER(prAdapter, prScanInfo->rPartialScanTimer);
        }
        else if (prScanCfg->eScanMethod == SCAN_METHOD_VOIP_ONLINE_SCAN) {

            DBGLOG(SCAN, INFO, ("Disable traps for PS VOIP SCAN\n"));

            NIC_TX_UNSET_VOIP_SCAN_TRIGGER_EVENT(prAdapter);
        }

        prScanInfo->fgIsScanReqProceeding = FALSE;
    }

    return;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to run SCAN start procedure.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
* \param[in] eHwScanMode To do NORMAL scan or BG SSID scan.
*
* \retval WLAN_STATUS_SUCCESS
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
scanFsmRunEventStart (
    IN P_ADAPTER_T  prAdapter,
    IN ENUM_HW_SCAN_MODE_T eHwScanMode
    )
{
    P_SCAN_CONFIG_T prScanCfg;
    P_SCAN_INFO_T prScanInfo;
    ENUM_SCAN_STATE_T eNextState;
    WLAN_STATUS rStatus = WLAN_STATUS_SUCCESS;

    DEBUGFUNC("scanFsmRunEventStart");
    DBGLOG(SCAN, INFO, ("scanFsmRunEventStart\n"));

    ASSERT(prAdapter);

    prScanInfo = &prAdapter->rScanInfo;
    prScanCfg = &prScanInfo->rScanConfig;
    eNextState = prScanInfo->eCurrentState;


    if (prScanInfo->eCurrentState != SCAN_STATE_ACTIVE) {
        prScanInfo->eCurrentHwScanMode = eHwScanMode;

        SCAN_STATE_TRANSITION(prAdapter, IDLE, ACTIVE);

        if (eHwScanMode == ENUM_HW_SCAN_NORMAL_SCAN) {
            /* Set the timeout function with additional 1 second guard for service period */
            ARB_SET_TIMER(prAdapter,
                          prScanInfo->rScanCheckForHangTimer,
                          (SCAN_CHECK_FOR_HANG_GUARD_TIME_MSEC +
                           (prScanCfg->ucNumOfScanChnl *
                            (prScanCfg->ucChnlDwellTimeMin + prScanCfg->ucChnlDwellTimeExt))) );
        }
    }

    return rStatus;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to run SCAN done procedure.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
*
* \retval WLAN_STATUS_SUCCESS
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
scanFsmRunEventScanDone (
    IN P_ADAPTER_T  prAdapter
    )
{
    P_SCAN_INFO_T prScanInfo;
    ENUM_SCAN_STATE_T eNextState;
    WLAN_STATUS rStatus = WLAN_STATUS_SUCCESS;

    DEBUGFUNC("scanFsmRunEventScanDone");
    DBGLOG(SCAN, INFO, ("scanFsmRunEventScanDone\n"));

    ASSERT(prAdapter);

    prScanInfo = &prAdapter->rScanInfo;
    eNextState = prScanInfo->eCurrentState;

    if (prScanInfo->eCurrentState != SCAN_STATE_IDLE) {
        //4 <1> Make state transition to SCAN_STATE_IDLE
        SCAN_STATE_TRANSITION1(prAdapter, ACTIVE, IDLE, DONE);

        //4 <2> Check SCAN Status for issuing Next Partial SCAN or completing the whole SCAN sequence.
        if (prScanInfo->eCurrentHwScanMode == ENUM_HW_SCAN_NORMAL_SCAN) {
            //4 <3> Cancel SCAN Timeout Timer.
            ARB_CANCEL_TIMER(prAdapter, prScanInfo->rScanCheckForHangTimer);

            scanCheckScanStatus(prAdapter);
        }
    }

    return rStatus;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to run SCAN abort procedure.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
*
* \retval WLAN_STATUS_SUCCESS
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
scanFsmRunEventScanAbort (
    IN P_ADAPTER_T  prAdapter
    )
{
    P_SCAN_INFO_T prScanInfo;
    ENUM_SCAN_STATE_T eNextState;
    WLAN_STATUS rStatus = WLAN_STATUS_SUCCESS;

    DEBUGFUNC("scanFsmRunEventScanAbort");
    DBGLOG(SCAN, INFO, ("scanFsmRunEventScanAbort\n"));

    ASSERT(prAdapter);

    prScanInfo = &prAdapter->rScanInfo;
    eNextState = prScanInfo->eCurrentState;

    if (prScanInfo->eCurrentState != SCAN_STATE_IDLE) {
        //4 <1> Make state transition to SCAN_STATE_IDLE
        SCAN_STATE_TRANSITION1(prAdapter, ACTIVE, IDLE, ABORT);

        //4 <2> Cancel SCAN Timeout Timer.
        ARB_CANCEL_TIMER(prAdapter, prScanInfo->rScanCheckForHangTimer);

        //4 <3> Do call back function.
        if (prScanInfo->rScanConfig.pfScanDoneHandler) {
            prScanInfo->rScanConfig.pfScanDoneHandler(prAdapter, WLAN_STATUS_FAILURE);
        }

#if CFG_WORKAROUND_HEC_5512
        //4 <4> Recover from aborting from BG SSID scan state
        if (prScanInfo->eCurrentHwScanMode == ENUM_HW_SCAN_BG_SSID_SCAN) {
#if 0
            DBGLOG(SCAN, INFO, ("Recover from aborting from BG SSID scan state\n"));

            nicTxFlushStopQueues(prAdapter, TXQ_MGMT_MASK, 0x0 /*(UINT_8)NULL*/);

            nicTxStartQueues(prAdapter, TXQ_MGMT_MASK);

            scanSendProbeReqFrames(prAdapter,
                                   NULL,
                                   0,
                                   1,
                                   0,
                                   FALSE);

            kalMdelay(10);
#else
            nicLogicReset(prAdapter);
#endif
        }
#endif
    }

    NIC_RESET_INT_EVENT(prAdapter, INT_EVENT_SCAN_DONE);

    return rStatus;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to run SCAN stop procedure.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
*
* \retval WLAN_STATUS_SUCCESS
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
scanFsmRunEventScanStop (
    IN P_ADAPTER_T  prAdapter
    )
{
    P_SCAN_INFO_T prScanInfo;
    ENUM_SCAN_STATE_T eNextState;
    WLAN_STATUS rStatus = WLAN_STATUS_SUCCESS;

    DEBUGFUNC("scanFsmRunEventScanStop");

    ASSERT(prAdapter);

    DBGLOG(SCAN, INFO, ("scanFsmRunEventScanStop\n"));

    prScanInfo = &prAdapter->rScanInfo;
    eNextState = prScanInfo->eCurrentState;

    if (prScanInfo->eCurrentState != SCAN_STATE_IDLE) {
        //4 <1> Make state transition to SCAN_STATE_IDLE
        SCAN_STATE_TRANSITION1(prAdapter, ACTIVE, IDLE, ABORT);

        //4 <2> Cancel SCAN Timeout Timer.
        ARB_CANCEL_TIMER(prAdapter, prScanInfo->rScanCheckForHangTimer);

        //4 <3> Check SCAN Status for issuing Next Partial SCAN or completing the whole SCAN sequence.
        if (prScanInfo->eCurrentHwScanMode == ENUM_HW_SCAN_NORMAL_SCAN) {
            scanCheckScanStatus(prAdapter);
        }

#if CFG_WORKAROUND_HEC_5512
        //4 <4> Recover from aborting from BG SSID scan state
        if (prScanInfo->eCurrentHwScanMode == ENUM_HW_SCAN_BG_SSID_SCAN) {
#if 0
            DBGLOG(SCAN, INFO, ("Recover from stopping from BG SSID scan state\n"));

            nicTxFlushStopQueues(prAdapter, TXQ_MGMT_MASK, 0x0 /*(UINT_8)NULL*/);

            nicTxStartQueues(prAdapter, TXQ_MGMT_MASK);

            scanSendProbeReqFrames(prAdapter,
                                   NULL,
                                   0,
                                   1,
                                   0,
                                   FALSE);
            kalMdelay(10);
#else
            nicLogicReset(prAdapter);
#endif
        }
#endif
    }

    return rStatus;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief
*
* \param[in] pvAdapter Pointer to the Adapter structure.
*
* \retval WLAN_STATUS_SUCCESS
*/
/*----------------------------------------------------------------------------*/
VOID
scanCheckScanStatus (
    IN P_ADAPTER_T prAdapter
    )
{
    P_SCAN_INFO_T prScanInfo;
    P_SCAN_CONFIG_T prScanCfg;
    P_SCAN_STATUS_T prScanStatus;

    DEBUGFUNC("scanCheckScanStatus");

    ASSERT(prAdapter);

    prScanInfo = &prAdapter->rScanInfo;
    prScanCfg = &prScanInfo->rScanConfig;
    prScanStatus = &prScanInfo->rScanStatus;

    //4 <1> Check if the SCAN Channel Number is valid.
    ASSERT(prScanCfg->ucNumOfScanChnl);

    //4 <2> Check if the SCAN Status is valid.
    if (prScanStatus->ucLastScanChnlIdx > prScanCfg->ucNumOfScanChnl) {
    /* NOTE(Kevin):
     * For MPW, if we encounter such case, which means the ucLastScanChnlIdx
     * didn't be cleared off while enabling HW SCAN.(has been identified and do bug fixed)
     * For HW version after MPW, this is normal case which means the HW SCAN have
     * finished.
     */
#if DBG & 0 /* According above two reasons, we don't do ASSERT() anymore */
        DBGLOG(SCAN, ERROR, ("ucLastScanChnlIdx: %d > ucNumOfScanChnl: %d\n",
            prScanStatus->ucLastScanChnlIdx,
            prScanCfg->ucNumOfScanChnl));
        ASSERT(0);
#endif /* DBG */

        prScanStatus->ucLastScanChnlIdx = prScanCfg->ucNumOfScanChnl;
    }

//#if DBG
    if (prScanStatus->ucLastScanChnlIdx == 0) {
        DBGLOG(SCAN, WARN, ("Didn't SCAN, ucLastScanChnlIdx == 0.\n"));

        /* NOTE:
           Workaround for the case that the scan is continuously blocked in scan initial phase,
           which may be blocked by polling for unlimited RX packet (more data always asserted).
           This may be happened when testing WPA2 5.2.2.4.

           In this workaround, it will repeat for the same procedure for at most 2 times.
        */
        if (prScanInfo->ucScanBlockInInitialPhaseCount++ == 2) {
            prScanStatus->ucLastScanChnlIdx = 1;
        }
    } else {
        prScanInfo->ucScanBlockInInitialPhaseCount = 0;
    }
//#endif /* DBG */

    //4 <3> Update the Finished Channel Count if necessary.
    if (!prScanCfg->ucNumOfPassiveScanInVoIP) {
        prScanCfg->ucFinishedChannelCount +=
            prScanStatus->ucLastScanChnlIdx;
    }

    //4 <4> Check if SCAN is completed.
    if (prScanCfg->ucFinishedChannelCount > prScanCfg->ucTotalScanChannelCount) {
#if DBG
        DBGLOG(SCAN, ERROR, ("ucFinishedChannelCount: %d > ucTotalScanChannelCount: %d\n",
            prScanCfg->ucFinishedChannelCount,
            prScanCfg->ucTotalScanChannelCount));
        ASSERT(0);
#endif /* DBG */
        prScanCfg->ucFinishedChannelCount = prScanCfg->ucTotalScanChannelCount;
    }


    if (prScanCfg->ucFinishedChannelCount == prScanCfg->ucTotalScanChannelCount &&
        prScanCfg->ucNumOfPassiveScanInVoIP == 0) {

        //4 <4.1> Call the CALL_BACK_FUNC to indicate SCAN was completed.
        if (prScanCfg->pfScanDoneHandler) {
            prScanCfg->pfScanDoneHandler(prAdapter, WLAN_STATUS_SUCCESS);
        }

        prScanCfg->ucTotalScanChannelCount = 0;
        prScanCfg->ucFinishedChannelCount = 0;
        prScanCfg->ucNumOfPassiveScanInVoIP = 0;

        prScanInfo->fgIsScanReqProceeding = FALSE;

        /* GeorgeKuo: */
        DBGLOG(SCAN, INFO, ("Indicate SCAN COMPLETE in scanCheckScanStatus()\n"));
        kalIndicateStatusAndComplete(prAdapter->prGlueInfo,
            WLAN_STATUS_SCAN_COMPLETE,
            NULL,
            0);
    }
    else { /* SCAN is not completed. */

        //4 <4.2> Check follow-up action of each SCAN Method.
        if (prScanCfg->eScanMethod == SCAN_METHOD_FULL_SCAN) {
#if DBG
            DBGLOG(SCAN, ERROR, ("Finished %d < Total %d\n", prScanCfg->ucFinishedChannelCount,
                prScanCfg->ucTotalScanChannelCount));
            ASSERT(0);
#endif /* DBG */
        }
        else if (prScanCfg->eScanMethod == SCAN_METHOD_ONLINE_SCAN) {

            /* Update the Number of Scan Channel */
            prScanCfg->ucNumOfScanChnl = prScanCfg->ucTotalScanChannelCount -
                                               prScanCfg->ucFinishedChannelCount;

            DBGLOG(SCAN, INFO, ("Schedule Next Partial Scan: Left Channel Number = %d, Total = %d\n",
                prScanCfg->ucNumOfScanChnl, prScanCfg->ucTotalScanChannelCount));

            /* Shift the Channel List */
            if (prScanStatus->ucLastScanChnlIdx) {
                if (prScanStatus->ucLastScanChnlIdx < MAXIMUM_OPERATION_CHANNEL_LIST) {
                    kalMemCopy(&prScanCfg->arChnlInfoList[0],
                               &prScanCfg->arChnlInfoList[prScanStatus->ucLastScanChnlIdx],
                               prScanCfg->ucNumOfScanChnl * sizeof(RF_CHANNEL_INFO_T));
                }
                else {
                    DBGLOG(SCAN, ERROR, ("Abnormal last scan channel index %d (> %d)\n",
                        prScanStatus->ucLastScanChnlIdx,
                        MAXIMUM_OPERATION_CHANNEL_LIST));
                    ASSERT(0);
                }
            }

            ARB_SET_TIMER(prAdapter,
                          prScanInfo->rPartialScanTimer,
                          PARTIAL_SCAN_TIMEOUT_MSEC);


        }
        else if (prScanCfg->eScanMethod == SCAN_METHOD_VOIP_ONLINE_SCAN) {

            /* Update the Number of Scan Channel */
            prScanCfg->ucNumOfScanChnl = 1;

            /* Shift the Channel List */
            if (prScanStatus->ucLastScanChnlIdx) {
                if (prScanCfg->ucNumOfPassiveScanInVoIP == 0) {

                    prScanCfg->eScanType = SCAN_TYPE_ACTIVE_SCAN;

                    prScanCfg->arChnlInfoList[0] = prScanCfg->arChnlInfoList[prScanCfg->ucFinishedChannelCount];

                    DBGLOG(SCAN, TRACE, ("Scan Next Channel = %d)\n",
                        prScanCfg->arChnlInfoList[0].ucChannelNum));

                    prScanCfg->ucNumOfPassiveScanInVoIP = SCAN_VOIP_PASSIVE_SCAN_INTERVAL;
                }
                else {
                    prScanCfg->eScanType = SCAN_TYPE_PASSIVE_SCAN;

                    DBGLOG(SCAN, TRACE, ("Passive Scan - Channel = %d)\n",
                        prScanCfg->arChnlInfoList[0].ucChannelNum));

                    if (prScanCfg->ucNumOfPassiveScanInVoIP == 2) {
                        prScanCfg->eScanType = SCAN_TYPE_ACTIVE_SCAN;
                    }

                    prScanCfg->ucNumOfPassiveScanInVoIP--;
                }
            }
            else {
                DBGLOG(SCAN, TRACE, ("Try Scan Again - Channel = %d)\n",
                    prScanCfg->arChnlInfoList[0].ucChannelNum));
            }

            NIC_TX_SET_VOIP_SCAN_TRIGGER_EVENT(prAdapter);

        }
    }

    return;
}


/*----------------------------------------------------------------------------*/
/*!
* \brief
*
* \param[in] pvAdapter Pointer to the Adapter structure.
*
* \retval WLAN_STATUS_SUCCESS
*/
/*----------------------------------------------------------------------------*/
VOID
scanSetupOriginalChannel (
    IN P_ADAPTER_T prAdapter,
    IN UINT_8      ucChannelNum,
    IN ENUM_BAND_T eBand
    )
{
    P_SCAN_INFO_T prScanInfo;
    P_SCAN_CONFIG_T prScanCfg;

    ASSERT(prAdapter);

    prScanInfo = &prAdapter->rScanInfo;
    prScanCfg = &prScanInfo->rScanConfig;


    prScanCfg->rOrgChnlInfo.ucChannelNum = ucChannelNum;
    prScanCfg->rOrgChnlInfo.eBand = eBand;

    return;
}

