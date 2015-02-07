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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/scan.c#2 $
*/

/*! \file   "scan.c"
    \brief  In this file we define the operation of SCAN result processing.

    Various process of SCAN result are defined here - all the behavior of add /
    remove / query / selection / sort / update an element to SCAN result.
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
** $Log: scan.c $
 *
 * 07 04 2010 enlai.chu
 * [ALPS00121369][Need Patch] [Volunteer Patch][WiFi] Avoid abnormal becaon 
 * .
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\87 2009-10-09 17:13:51 GMT mtk01088
**  Adding the WAPI AP policy check
**  \main\maintrunk.MT5921\86 2009-08-18 22:56:21 GMT mtk01090
**  Add Linux SDIO (with mmc core) support.
**  Add Linux 2.6.21, 2.6.25, 2.6.26.
**  Fix compile warning in Linux.
**  \main\maintrunk.MT5921\85 2009-07-16 11:37:20 GMT mtk01461
**  Fix - Skip wrong RCPI when receiving Beacon/ProbeResp from adjacent channel
**  \main\maintrunk.MT5921\84 2009-06-15 17:30:08 GMT mtk01725
**  Only update RSSI to a larger value in each SCAN request.
**  By comparing last beacon update time, last scan request time and current beacon received time, if last scan request time is newer than last beacon update time, update RSSI of current received Beacon, else update RSSI only if RSSI is larger.
**  \main\maintrunk.MT5921\83 2009-04-03 00:08:05 GMT mtk01461
**  Add new remove policy - oldest hidden & smart weakest
**  \main\maintrunk.MT5921\82 2009-02-18 19:17:23 GMT mtk01461
**  Do not update scan record during join
**  Add ROAMING_NO_SWING_RCPI_STEP for coding rule
**  \main\maintrunk.MT5921\81 2009-02-18 19:08:52 GMT mtk01461
**  Do not update SCAN Record during JOIN
**  \main\maintrunk.MT5921\80 2009-01-05 10:09:28 GMT mtk01725
**  Change compiling flag.
**  \main\maintrunk.MT5921\79 2008-12-19 17:20:16 GMT mtk01461
**  Fix the problem that do not parse the Supported Rate IE if its length > 8
**  \main\maintrunk.MT5921\78 2008-12-08 16:17:26 GMT mtk01461
**  Remove Lint Warning 613: Possible use of null pointer 'prStaRec' and Warning 572: Excessive shift value (precision 8 shifted)
**  \main\maintrunk.MT5921\77 2008-12-01 18:18:54 GMT mtk01088
**  fixed the lint "possible using null pointer" warning
**  \main\maintrunk.MT5921\76 2008-12-01 13:56:16 GMT mtk01461
**  Remove Warning 613: Possible use of null pointer from lint
**  \main\maintrunk.MT5921\75 2008-11-28 15:24:00 GMT mtk01088
**  fixed lint warning
**  \main\maintrunk.MT5921\74 2008-10-13 10:21:40 GMT mtk01461
**  Remove MSDU_INFO_CTRL_FLAG_MINIMUM_LIFETIME & Fix compile warning for ADS v1.2 build env
**  \main\maintrunk.MT5921\73 2008-09-02 10:41:01 GMT mtk01461
**  Update driver for code review
**
**  \main\maintrunk.MT5921\72 2008-08-20 17:46:50 GMT mtk01084
**  Modify for coding rule conformance
**  \main\maintrunk.MT5921\71 2008-08-06 09:16:08 GMT mtk01088
**  remove non-used code
**  \main\maintrunk.MT5921\70 2008-07-16 22:48:42 GMT mtk01461
**  Add error handling of buffer overflow - do not copy extreme large Beacon/ProbeResp frame to Scan Result's IE Buffer.
**  \main\maintrunk.MT5921\69 2008-07-14 20:55:48 GMT mtk01461
**  Fix the warning message from PREfast
**  \main\maintrunk.MT5921\68 2008-07-11 17:33:15 GMT mtk01084
**  add comments
**  \main\maintrunk.MT5921\67 2008-07-10 16:37:53 GMT mtk01084
**  support 802.11d related functions
**  \main\maintrunk.MT5921\66 2008-07-07 13:43:52 GMT mtk01461
**  Fix the bug - still can join problem when Join excessive retry. Fix the swing problem of roaming. Fix try to join an old record problem of roaming. Fix the average RCPI issue of roaming.
**  \main\maintrunk.MT5921\65 2008-06-18 20:45:08 GMT mtk01084
**  revise beacon timeout handling procedure
**  \main\maintrunk.MT5921\64 2008-06-17 16:49:35 GMT mtk01425
**  1. Modify the return value of arbFsmRunEventTxMmpdu
**  \main\maintrunk.MT5921\63 2008-06-16 16:11:08 GMT mtk01084
**  support the function to get the channel/ band information from HW
**  \main\maintrunk.MT5921\62 2008-06-13 15:56:40 GMT mtk01461
**  Revise the procedures of process incoming Beacon for updating SCAN result
**  \main\maintrunk.MT5921\61 2008-06-02 20:21:26 GMT mtk01461
**  Add Invalid List check for error handling if LIST was not initialized
**  \main\maintrunk.MT5921\60 2008-05-20 13:21:10 GMT mtk01084
**  update RCPI variance check under SLT
**  \main\maintrunk.MT5921\59 2008-05-15 14:05:44 GMT mtk01461
**  Add Set BSSID OID Support, CFG_SW_TCL flag
**  \main\maintrunk.MT5921\58 2008-05-12 16:04:21 GMT mtk01084
**  modify rWaitBeaconWatchdogTimer from rArbInfo to rPmInfo
**  \main\maintrunk.MT5921\57 2008-05-12 14:04:44 GMT mtk01084
**  force to receive at least 1 beacon on merging with IBSS
**  \main\maintrunk.MT5921\56 2008-05-03 20:30:44 GMT mtk01461
**  Fix compile warning in linux
**  \main\maintrunk.MT5921\55 2008-05-03 14:28:09 GMT mtk01461
**  Update the SCAN result according to BSSID and TA for IBSS.
**  Do not select the IBSS Candidate if it was expired > 5 sec.
**  \main\maintrunk.MT5921\54 2008-04-28 17:14:26 GMT mtk01084
**  add CFG_WORKAROUND_BG_SSID_SCAN_DONE for trigger BG SSID scan done when
**  matched SSID existed in the beacon/ probe response
**  \main\maintrunk.MT5921\53 2008-04-18 11:19:49 GMT mtk01084
**  prevent assertion false alarm
**  \main\maintrunk.MT5921\52 2008-04-17 22:12:41 GMT mtk01084
**  modify argument naming
**  \main\maintrunk.MT5921\51 2008-04-17 22:07:05 GMT mtk01084
**  modify send probe request function
**  \main\maintrunk.MT5921\50 2008-04-07 22:18:44 GMT mtk01084
**  use LP-IOT index for printing debug message under LP-IOT
**  \main\maintrunk.MT5921\49 2008-04-02 20:44:12 GMT mtk01084
**  Support for RCPI variance histogram
**  \main\maintrunk.MT5921\48 2008-04-01 23:53:09 GMT mtk01461
**  Update QoS function call for typo
**  \main\maintrunk.MT5921\47 2008-03-30 22:01:02 GMT mtk01084
**  add RCPI check in LP-IOT
**  \main\maintrunk.MT5921\46 2008-03-29 13:55:36 GMT mtk01461
**  Add MAGIC GUID for Link List
**  Remove workaround for TCL
**  \main\maintrunk.MT5921\45 2008-03-23 22:48:59 GMT mtk01461
**  Add remove Scan Record by BSSID for IBSS
**  \main\maintrunk.MT5921\44 2008-03-23 20:37:23 GMT mtk01461
**  Revise the reference to the fgIsIBSSActive flag
**  \main\maintrunk.MT5921\43 2008-03-20 00:03:10 GMT mtk01461
**  Add comments and fix typo
**  \main\maintrunk.MT5921\42 2008-03-19 15:22:01 GMT mtk01461
**  Add Status Code comparison while choosing candidate
**  \main\maintrunk.MT5921\41 2008-03-18 10:11:53 GMT mtk01088
**  modify the pmkid candidate indicate method, by BSS Desc and also update by scan
**  \main\maintrunk.MT5921\40 2008-03-13 15:32:01 GMT mtk01461
**  Refine the relationship between SCAN result and STA record, lifetime, aging policy etc
**  \main\maintrunk.MT5921\39 2008-03-12 09:52:19 GMT mtk01461
**  Remove type case in MSDU_INFO_OBJ_INIT
**
**  \main\maintrunk.MT5921\38 2008-02-27 12:12:39 GMT mtk01461
**  Add Hidden SSID Support
**  \main\maintrunk.MT5921\37 2008-02-01 10:04:25 GMT mtk01385
**  1. Fix WinCE 4.2 compiling error.
**  \main\maintrunk.MT5921\36 2008-01-17 17:47:01 GMT mtk01084
**  only to set LP related register at the 1st beacon received after connected under infrastructure mode
**  \main\maintrunk.MT5921\35 2008-01-16 20:55:11 GMT mtk01084
**  only the delay setting up LP related register under Infrastructure mode (not in IBSS mode)
**  \main\maintrunk.MT5921\34 2008-01-07 15:06:52 GMT mtk01461
**  Add PhyType & AdHocMode Selection Support
**  \main\maintrunk.MT5921\33 2007-12-26 20:25:54 GMT mtk01088
**  the wpa2 rsn cap must store for pre-authentication
**  \main\maintrunk.MT5921\32 2007-12-20 15:41:50 GMT mtk01084
**  add debug messages for IOT
**  \main\maintrunk.MT5921\31 2007-12-16 19:24:33 GMT mtk01084
**  add lines for printing debug message when doing LP IOT
**  \main\maintrunk.MT5921\30 2007-12-11 00:10:19 GMT mtk01461
**  Refine Remove SCAN Result wording
**  \main\maintrunk.MT5921\29 2007-12-04 18:09:41 GMT mtk01461
**  Unify the SCAN Status Process for both MPW and new scheme after 11/27
**  \main\maintrunk.MT5921\28 2007-11-30 19:58:11 GMT mtk01084
**  apply PM setting on our beacon
**  \main\maintrunk.MT5921\27 2007-11-30 17:47:06 GMT mtk01461
**  Update comment in scan.c for WMM IE & WMM Param IE
**  \main\maintrunk.MT5921\26 2007-11-29 01:55:26 GMT mtk01461
**  Fix Scan Result - reset WMM/WPA variable
**  \main\maintrunk.MT5921\25 2007-11-26 19:38:29 GMT mtk01461
**  Update comment
**  \main\maintrunk.MT5921\24 2007-11-21 17:59:12 GMT mtk01084
**  Update DTIM period store in BSS Info
**  \main\maintrunk.MT5921\23 2007-11-13 18:18:13 GMT mtk01084
**  to nidcate PM module for the connection status when 1st beacon is received after connected
**  \main\maintrunk.MT5921\22 2007-11-08 20:35:12 GMT mtk01088
**  remove non-used code
**  \main\maintrunk.MT5921\21 2007-11-06 20:26:44 GMT mtk01088
**  got the privacy bit from scan result
**  \main\maintrunk.MT5921\20 2007-11-02 00:57:19 GMT mtk01461
**  Unify TX Path for Normal and IBSS Power Save + IBSS neighbor learning
**  \main\maintrunk.MT5921\19 2007-10-25 18:05:13 GMT mtk01461
**  Add VOIP SCAN Support  & Refine Roaming
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
* \brief Initialize the list head of BSS Descriptor and free list.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
scanInitialize (
    IN P_ADAPTER_T prAdapter
    )
{
    P_SCAN_INFO_T prScanInfo;
    PUINT_8 pucBSSBuff;
    P_BSS_DESC_T prBSSDesc = (P_BSS_DESC_T)NULL;
    UINT_32 i;


    ASSERT(prAdapter);
    prScanInfo =  &prAdapter->rScanInfo;
    pucBSSBuff = prScanInfo->pucBSSCached;

    //4 <0> Clear allocated memory.
    kalMemZero((PVOID) prScanInfo->pucBSSCached, prScanInfo->u4BSSCachedSize);

    LINK_INITIALIZE(&prScanInfo->rFreeBSSDescList);
    LINK_INITIALIZE(&prScanInfo->rBSSDescList);

    for (i = 0; i < CFG_MAX_NUM_BSS_LIST; i++) {

        prBSSDesc = (P_BSS_DESC_T)pucBSSBuff;

        BSS_DESC_SET_GUID(prBSSDesc);

        LINK_INSERT_TAIL(&prScanInfo->rFreeBSSDescList, &prBSSDesc->rLinkEntry);

        pucBSSBuff += ALIGN_4(sizeof(BSS_DESC_T));
    }
    /* Check if the memory allocation consist with this initialization function */
    ASSERT((UINT_32)(pucBSSBuff - prScanInfo->pucBSSCached) == prScanInfo->u4BSSCachedSize);

    return;

} /* end of scanInitialize() */


/*----------------------------------------------------------------------------*/
/*!
* \brief Search the Candidate of BSS Descriptor for JOIN(Infrastructure) or
*        MERGE(AdHoc) according to current Connection Policy.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return   Pointer to BSS Descriptor, if found. NULL, if not found
*/
/*----------------------------------------------------------------------------*/
P_BSS_DESC_T
scanSearchBssDescByPolicy (
    IN P_ADAPTER_T prAdapter
    )
{
    P_CONNECTION_SETTINGS_T prConnSettings;
    P_BSS_INFO_T prBssInfo;
    P_SCAN_INFO_T prScanInfo;
    P_LINK_T prBSSDescList;
    P_BSS_DESC_T prBssDesc = (P_BSS_DESC_T)NULL;
    P_BSS_DESC_T prPrimaryBssDesc;
    P_BSS_DESC_T prCandidateBssDesc = (P_BSS_DESC_T)NULL;

    P_STA_RECORD_T prStaRec = (P_STA_RECORD_T)NULL;
    P_STA_RECORD_T prPrimaryStaRec;
    P_STA_RECORD_T prCandidateStaRec = (P_STA_RECORD_T)NULL;

    /* The first one reach the check point will be our candidate */
    BOOLEAN fgIsFindFirst = (BOOLEAN)FALSE;

    BOOLEAN fgIsFindBestRSSI = (BOOLEAN)FALSE;
    BOOLEAN fgIsFindBestEncryptionLevel = (BOOLEAN)FALSE;
    BOOLEAN fgIsFindMinChannelLoad = (BOOLEAN)FALSE;

#if CFG_SW_TCL /* Compare the TSF counter by SW */
    BOOLEAN fgIsLocalTSFRead = (BOOLEAN)FALSE;
    ULARGE_INTEGER rCurrentTsf;
#endif /* CFG_SW_TCL */

    /* TODO(Kevin): Support Min Channel Load */
    //UINT_8 aucChannelLoad[CHANNEL_NUM] = {0};

    DEBUGFUNC("scanSearchBssDescByPolicy");


    ASSERT(prAdapter);
    prConnSettings = &prAdapter->rConnSettings;
    prBssInfo = &prAdapter->rBssInfo;
    prScanInfo =  &prAdapter->rScanInfo;
    prBSSDescList = &prScanInfo->rBSSDescList;

    /* Check if such BSS Descriptor exists in a valid list */
    DBGLOG(SCAN, TRACE, ("Number Of SCAN Result = %ld\n",
        prBSSDescList->u4NumElem));

    //4 <1> The outer loop to search for a candidate.
    LINK_FOR_EACH_ENTRY(prBssDesc, prBSSDescList, rLinkEntry, BSS_DESC_T) {

        BSS_DESC_CHK_GUID(prBssDesc);

        /* TODO(Kevin): Update Minimum Channel Load Information here */
        DBGLOG(SCAN, TRACE, ("BSS DESC(%#lx): MAC: "MACSTR"\n",
            (UINT_32)prBssDesc, MAC2STR(prBssDesc->aucBSSID)));

        //4 <2> Check various conditions for mismatch.
        //4 <2.A> Check Previous Status Code from JOIN result first.
        /* NOTE(Kevin): STA_RECORD_T is recorded by TA. */
        prStaRec = staRecGetStaRecordByAddr(prAdapter,
                                            prBssDesc->aucSrcAddr);

        if (prStaRec) {
            /* NOTE(Kevin):
             * The Status Code is the result of a Previous Connection Request, we use this as SCORE for choosing a proper
             * candidate (Used for compare see <6>)
             * The Reason Code is an indication of the reason why AP reject us, we use this Code for "Reject"
             * a SCAN result to become our candidate(Like a blacklist).
             */
            if (prStaRec->u2ReasonCode != REASON_CODE_RESERVED) {
                DBGLOG(SCAN, TRACE, ("Ignore BSS DESC MAC: "MACSTR", JOIN Reason Code = %d\n",
                    MAC2STR(prBssDesc->aucBSSID), prStaRec->u2ReasonCode));
                continue;
            }
            else if (prStaRec->u2StatusCode != STATUS_CODE_SUCCESSFUL) {

                if (prStaRec->ucJoinFailureCount < JOIN_MAX_RETRY_FAILURE_COUNT) {
                    OS_SYSTIME rCurrentTime;


                    GET_CURRENT_SYSTIME(&rCurrentTime);

                    /* NOTE(Kevin): greedy association - after timeout, we'll still
                     * try to associate to the AP whose STATUS of conection attempt
                     * was not success.
                     * We may also use (ucJoinFailureCount x JOIN_RETRY_INTERVAL_SEC) for
                     * time bound.
                     */
                    if (CHECK_FOR_TIMEOUT(rCurrentTime,
                                          prStaRec->rLastJoinTime,
                                          SEC_TO_SYSTIME(JOIN_RETRY_INTERVAL_SEC))) {

#if DBG
                        if ((prStaRec->u2StatusCode == STATUS_CODE_JOIN_TIMEOUT) ||
                            (prStaRec->u2StatusCode == STATUS_CODE_AUTH_TIMEOUT) ||
                            (prStaRec->u2StatusCode == STATUS_CODE_ASSOC_TIMEOUT)) {
                            DBGLOG(SCAN, TRACE, ("Accept BSS DESC MAC: "MACSTR", but previous JOIN Status Code = %s\n",
                                MAC2STR(prBssDesc->aucBSSID),
                                ((prStaRec->u2StatusCode == STATUS_CODE_JOIN_TIMEOUT) ? "JOIN_TIMEOUT" :
                                 ((prStaRec->u2StatusCode == STATUS_CODE_AUTH_TIMEOUT) ? "AUTH_TIMEOUT" : "ASSOC_TIMEOUT") ) ) );
                        }
                        else {
                            DBGLOG(SCAN, TRACE, ("Accpet BSS DESC MAC: "MACSTR", but previous JOIN Status Code = %d\n",
                                MAC2STR(prBssDesc->aucBSSID), prStaRec->u2StatusCode));
                        }
#endif /* DBG */
                    }
                    else {
                        DBGLOG(SCAN, TRACE, ("Ignore BSS DESC MAC: "MACSTR", JOIN Status Code = %d\n",
                            MAC2STR(prBssDesc->aucBSSID), prStaRec->u2StatusCode));
                        continue;
                    }
                }
                else {
                    DBGLOG(SCAN, TRACE, ("* Ignore BSS DESC MAC: "MACSTR", JOIN Status Code = %d\n",
                        MAC2STR(prBssDesc->aucBSSID), prStaRec->u2StatusCode));
                    continue;
                }
            }
        }


        //4 <2.B> Check BSS Type for the corresponding Operation Mode in Connection Setting
        /* NOTE(Kevin): For NET_TYPE_AUTO_SWITCH, we will always pass following check. */
        if (((prConnSettings->eOPMode == NET_TYPE_INFRA) &&
             (prBssDesc->eBSSType != BSS_TYPE_INFRASTRUCTURE)) ||
            (((prConnSettings->eOPMode == NET_TYPE_IBSS) ||
              (prConnSettings->eOPMode == NET_TYPE_DEDICATED_IBSS)) &&
             (prBssDesc->eBSSType != BSS_TYPE_IBSS))) {

            DBGLOG(SCAN, TRACE, ("Ignore BSS DESC MAC: "MACSTR", eBSSType = %s\n",
                MAC2STR(prBssDesc->aucBSSID), ((prBssDesc->eBSSType == BSS_TYPE_INFRASTRUCTURE) ?
                    "BSS_TYPE_INFRASTRUCTURE" : "BSS_TYPE_IBSS")));
            continue;
        }


        //4 <2.C> Check if this SCAN record has been updated recently for IBSS.
        /* NOTE(Kevin): Because some STA may change its BSSID frequently after it
         * create the IBSS, so we need to make sure we get the new one.
         * For BSS, if the old record was matched, however it won't be able to pass
         * the Join Process later.
         */
        if (prBssDesc->eBSSType == BSS_TYPE_IBSS) {
            OS_SYSTIME rCurrentTime;

            GET_CURRENT_SYSTIME(&rCurrentTime);
            if (CHECK_FOR_TIMEOUT(rCurrentTime, prBssDesc->rUpdateTime,
                                  SEC_TO_SYSTIME(BSS_DESC_TIMEOUT_SEC))) {
                DBGLOG(SCAN, TRACE, ("Skip old record of BSS Descriptor - BSSID:["MACSTR"]\n\n",
                          MAC2STR(prBssDesc->aucBSSID)));
                continue;
            }
        }

        if ((prBssDesc->eBSSType == BSS_TYPE_INFRASTRUCTURE) &&
            (prAdapter->eConnectionState == MEDIA_STATE_CONNECTED)) {
            OS_SYSTIME rCurrentTime;

            GET_CURRENT_SYSTIME(&rCurrentTime);
            if (CHECK_FOR_TIMEOUT(rCurrentTime, prBssDesc->rUpdateTime,
                                  SEC_TO_SYSTIME(BSS_DESC_TIMEOUT_SEC))) {
                DBGLOG(SCAN, TRACE, ("Skip old record of BSS Descriptor - BSSID:["MACSTR"]\n\n",
                          MAC2STR(prBssDesc->aucBSSID)));
                continue;
            }
        }


        //4 <2.D> Check Unsupported BSS PHY Type
        if (!(BIT(prBssDesc->ePhyType) & prAdapter->u2AvailablePhyTypeSet)) {

            DBGLOG(SCAN, TRACE, ("Ignore BSS DESC MAC: "MACSTR", PhyType = %s not supported\n",
                MAC2STR(prBssDesc->aucBSSID),
                ((prBssDesc->ePhyType == PHY_TYPE_ERP_INDEX) ? "PHY_TYPE_ERP" :
                 ((prBssDesc->ePhyType == PHY_TYPE_HR_DSSS_INDEX) ? "PHY_TYPE_HR_DSSS" : "PHY_TYPE_OFDM") ) ));
            continue;
        }


        //4 <2.E> Check AP's BSSID if OID_802_11_BSSID has been set.
        if ((prConnSettings->fgIsConnByBssidIssued) &&
            (prBssDesc->eBSSType == BSS_TYPE_INFRASTRUCTURE)) {

            if (UNEQUAL_MAC_ADDR(prConnSettings->aucBSSID, prBssDesc->aucBSSID)) {

                DBGLOG(SCAN, TRACE, ("Ignore BSS DESC MAC: "MACSTR", Expected BSSID :"MACSTR"\n",
                    MAC2STR(prBssDesc->aucBSSID), MAC2STR(prConnSettings->aucBSSID)));
                continue;
            }
        }


        prPrimaryBssDesc = (P_BSS_DESC_T)NULL;

        //4 <3> Check current Connection Policy.
        switch (prConnSettings->eConnectionPolicy) {
        case CONNECT_BY_SSID_BEST_RSSI:
            /* Choose Hidden SSID to join only if the `fgIsEnableJoin...` is TRUE */
            if (prAdapter->fgIsEnableJoinToHiddenSSID && prBssDesc->fgIsHiddenSSID) {
                /* NOTE(Kevin): following if () statement means that
                 * If Target is hidden, then we won't connect when user specify SSID_ANY policy.
                 */
                if (prConnSettings->ucSSIDLen) {
                    prPrimaryBssDesc = prBssDesc;

                    fgIsFindBestRSSI = TRUE;
                }

            }
            else if (EQUAL_SSID(prBssDesc->aucSSID,
                                prBssDesc->ucSSIDLen,
                                prConnSettings->aucSSID,
                                prConnSettings->ucSSIDLen)) {
                prPrimaryBssDesc = prBssDesc;

                fgIsFindBestRSSI = TRUE;
            }
            break;

        case CONNECT_BY_SSID:
            /* Choose Hidden SSID to join only if the `fgIsEnableJoin...` is TRUE */
            if (prAdapter->fgIsEnableJoinToHiddenSSID && prBssDesc->fgIsHiddenSSID) {
                /* NOTE(Kevin): following if () statement means that
                 * If Target is hidden, then we won't connect when user specify SSID_ANY policy.
                 */
                if (prConnSettings->ucSSIDLen) {
                    prPrimaryBssDesc = prBssDesc;
                }
            }
            else if (EQUAL_SSID(prBssDesc->aucSSID,
                                prBssDesc->ucSSIDLen,
                                prConnSettings->aucSSID,
                                prConnSettings->ucSSIDLen)) {
                prPrimaryBssDesc = prBssDesc;

                fgIsFindFirst = TRUE;
            }
            break;

        case CONNECT_BY_SSID_ANY:
            /* NOTE(Kevin): In this policy, we don't know the desired
             * SSID from user, so we should exclude the Hidden SSID from candidacy.
             * And because we refuse to connect to Hidden SSID node at the beginning, so
             * when the JOIN Module deal with a BSS_DESC_T which has fgIsHiddenSSID == TRUE,
             * then the Connection Settings must be valid without doubt.
             */
            if (!prBssDesc->fgIsHiddenSSID) {
                prPrimaryBssDesc = prBssDesc;

                fgIsFindFirst = TRUE;
            }
            break;

        case CONNECT_BY_SSID_BEST_RSSI_MIN_CH_LOAD:
            /* Choose Hidden SSID to join only if the `fgIsEnableJoin...` is TRUE */
            if (prAdapter->fgIsEnableJoinToHiddenSSID && prBssDesc->fgIsHiddenSSID) {
                /* NOTE(Kevin): following if () statement means that
                 * If Target is hidden, then we won't connect when user specify SSID_ANY policy.
                 */
                if (prConnSettings->ucSSIDLen) {
                    prPrimaryBssDesc = prBssDesc;

                    fgIsFindBestRSSI = TRUE;
                    fgIsFindMinChannelLoad = TRUE;
                }
            }
            else if (EQUAL_SSID(prBssDesc->aucSSID,
                                prBssDesc->ucSSIDLen,
                                prConnSettings->aucSSID,
                                prConnSettings->ucSSIDLen)) {
                prPrimaryBssDesc = prBssDesc;

                fgIsFindBestRSSI = TRUE;
                fgIsFindMinChannelLoad = TRUE;
            }
            break;

        default:
            break;
        }


        /* Primary Candidate was not found */
        if (prPrimaryBssDesc == NULL) {
            continue;
        }

        prPrimaryStaRec = prStaRec;

        //4 <4> Validate this primary Scan Record.
        //4 <4A> Check the Unknown or Unsupported BSS Basic Rate Set.
        /* Skip if one or more BSS Basic Rate are not supported or unknown */
        if ((prPrimaryBssDesc->u2BSSBasicRateSet &
             ~(rPhyAttributes[prPrimaryBssDesc->ePhyType].u2SupportedRateSet)) ||
            prPrimaryBssDesc->fgIsUnknownBssBasicRate) {

            continue;
        }

        //4 <4B> Check for IBSS AdHoc Mode.
        /* Skip if one or more BSS Basic Rate are not supported by current AdHocMode */
        if (prPrimaryBssDesc->eBSSType == BSS_TYPE_IBSS) {
            //4 <4B.1> Check if match the Capability of current IBSS AdHoc Mode.
            if (ibssCheckCapabilityForAdHocMode(prAdapter, prPrimaryBssDesc) == WLAN_STATUS_FAILURE) {

                DBGLOG(SCAN, TRACE,
                    ("Ignore BSS DESC MAC: "MACSTR", Capability is not supported for current AdHoc Mode.\n",
                    MAC2STR(prPrimaryBssDesc->aucBSSID)));

                continue;
            }


            //4 <4B.2> IBSS Merge Decision Flow for SEARCH STATE.
            if (prAdapter->fgIsIBSSActive &&
                UNEQUAL_MAC_ADDR(prBssInfo->aucBSSID, prPrimaryBssDesc->aucBSSID)) {

#if !CFG_SW_TCL // NOTE(Kevin 2008/03/29): Use TCL in RFB.
                DBGLOG(SCAN, TRACE,
                    ("prPrimaryBssDesc->fgIsLargerTSF = %d\n",
                        prPrimaryBssDesc->fgIsLargerTSF));

                if (!prPrimaryBssDesc->fgIsLargerTSF) {
                    DBGLOG(SCAN, TRACE,
                        ("Ignore BSS DESC MAC: ["MACSTR"], Current BSSID: ["MACSTR"].\n",
                            MAC2STR(prPrimaryBssDesc->aucBSSID), MAC2STR(prBssInfo->aucBSSID)));
                    continue;
                }
#else /* CFG_SW_TCL */
                if (!fgIsLocalTSFRead) {
                    NIC_GET_CURRENT_TSF(prAdapter, &rCurrentTsf);

                    DBGLOG(SCAN, TRACE,
                        ("\n\nCurrent TSF : %08lx-%08lx\n\n",
                            rCurrentTsf.u.HighPart, rCurrentTsf.u.LowPart));
                }

                if (rCurrentTsf.QuadPart > prPrimaryBssDesc->u8TimeStamp.QuadPart) {
                    DBGLOG(SCAN, TRACE,
                        ("Ignore BSS DESC MAC: ["MACSTR"], Current BSSID: ["MACSTR"].\n",
                            MAC2STR(prPrimaryBssDesc->aucBSSID), MAC2STR(prBssInfo->aucBSSID)));

                    DBGLOG(SCAN, TRACE,
                        ("\n\nBSS's TSF : %08lx-%08lx\n\n",
                            prPrimaryBssDesc->u8TimeStamp.u.HighPart, prPrimaryBssDesc->u8TimeStamp.u.LowPart));

                    prPrimaryBssDesc->fgIsLargerTSF = FALSE;
                    continue;
                }
                else {
                    prPrimaryBssDesc->fgIsLargerTSF = TRUE;
                }
#endif /* CFG_SW_TCL */

            }
        }

        //4 <5> Check the Encryption Status.
#if SUPPORT_WAPI
        if (prAdapter->fgUseWapi) {
            DBGLOG(WAPI, INFO, ("wapiPerformPolicySelection\n"));
            if (wapiPerformPolicySelection(prAdapter, prPrimaryBssDesc)) {
                fgIsFindFirst = TRUE;
            }
            else {
                /* Can't pass the Encryption Status Check, get next one */
                continue;
            }       
        }
        else
#endif          
        if (rsnPerformPolicySelection(prAdapter, prPrimaryBssDesc)) {

            if (prPrimaryBssDesc->ucEncLevel > 0) {
                fgIsFindBestEncryptionLevel = TRUE;

                fgIsFindFirst = FALSE;
            }
        }
        else {
            /* Can't pass the Encryption Status Check, get next one */
            continue;
        }

        /* For RSN Pre-authentication, update the PMKID canidate list for
           same SSID and encrypt status */
        /* Update PMKID candicate list. */
        if (prAdapter->rConnSettings.eAuthMode == AUTH_MODE_WPA2) {
            rsnUpdatePmkidCandidateList(prAdapter,	prPrimaryBssDesc);
            if (prAdapter->rSecInfo.u4PmkidCandicateCount) {
                prAdapter->rSecInfo.fgIndicatePMKID = rsnCheckPmkidCandicate(prAdapter);
            }
        }

        //4 <6> Compare the Candidate and the Primary Scan Record.
        if (!prCandidateBssDesc) {
            prCandidateBssDesc = prPrimaryBssDesc;
            prCandidateStaRec = prPrimaryStaRec;

            //4 <6A> Condition - Get the first matched one.
            if (fgIsFindFirst) {
                break;
            }
        }
        else {
            //4 <6B> Condition - Choose the one with best Encryption Score.
            if (fgIsFindBestEncryptionLevel) {
                if (prCandidateBssDesc->ucEncLevel <
                    prPrimaryBssDesc->ucEncLevel) {

                    prCandidateBssDesc = prPrimaryBssDesc;
                    prCandidateStaRec = prPrimaryStaRec;
                    continue;
                }
            }

            /* If reach here, that means they have the same Encryption Score.
             */

            //4 <6C> Condition - Give opportunity to the one we didn't connect before.
            // For roaming, only compare the candidates other than current associated BSSID.
            if (!prCandidateBssDesc->fgIsConnected && !prPrimaryBssDesc->fgIsConnected) {
                if ((prCandidateStaRec != (P_STA_RECORD_T)NULL) &&
                    (prCandidateStaRec->u2StatusCode != STATUS_CODE_SUCCESSFUL)) {

                    DBGLOG(SCAN, TRACE, ("So far -BSS DESC MAC: "MACSTR" has nonzero Status Code = %d\n",
                        MAC2STR(prCandidateBssDesc->aucBSSID), prCandidateStaRec->u2StatusCode));

                    if (prPrimaryStaRec != (P_STA_RECORD_T)NULL) {
                        if (prPrimaryStaRec->u2StatusCode != STATUS_CODE_SUCCESSFUL) {

                            /* Give opportunity to the one with smaller rLastJoinTime */
                            if (TIME_BEFORE(prCandidateStaRec->rLastJoinTime,
                                                        prPrimaryStaRec->rLastJoinTime)) {
                                continue;
                            }
                            /* We've connect to CANDIDATE recently, let us try PRIMARY now */
                            else {
                                prCandidateBssDesc = prPrimaryBssDesc;
                                prCandidateStaRec = prPrimaryStaRec;
                                continue;
                            }
                        }
                        /* PRIMARY's u2StatusCode = 0 */
                        else {
                            prCandidateBssDesc = prPrimaryBssDesc;
                            prCandidateStaRec = prPrimaryStaRec;
                            continue;
                        }
                    }
                    /* PRIMARY has no StaRec - We didn't connet to PRIMARY before */
                    else {
                        prCandidateBssDesc = prPrimaryBssDesc;
                        prCandidateStaRec = prPrimaryStaRec;
                        continue;
                    }
                }
                else {
                    if ((prPrimaryStaRec != (P_STA_RECORD_T)NULL) &&
                        (prPrimaryStaRec->u2StatusCode != STATUS_CODE_SUCCESSFUL)) {
                        continue;
                    }
                }
            }


            //4 <6D> Condition - Visible SSID win Hidden SSID.
            if (prCandidateBssDesc->fgIsHiddenSSID) {
                if (!prPrimaryBssDesc->fgIsHiddenSSID) {
                    prCandidateBssDesc = prPrimaryBssDesc; /* The non Hidden SSID win. */
                    prCandidateStaRec = prPrimaryStaRec;
                    continue;
                }
            }
            else {
                if (prPrimaryBssDesc->fgIsHiddenSSID) {
                    continue;
                }
            }


            //4 <6E> Condition - Choose the one with better RCPI(RSSI).
            if (fgIsFindBestRSSI) {
                /* TODO(Kevin): We shouldn't compare the actual value, we should
                 * allow some acceptable tolerance of some RSSI percentage here.
                 */
                DBGLOG(SCAN, TRACE, ("Candidate ["MACSTR"]: RCPI = %d, Primary ["MACSTR"]: RCPI = %d\n",
                    MAC2STR(prCandidateBssDesc->aucBSSID), prCandidateBssDesc->rRcpi,
                    MAC2STR(prPrimaryBssDesc->aucBSSID), prPrimaryBssDesc->rRcpi));

                ASSERT(!(prCandidateBssDesc->fgIsConnected &&
                         prPrimaryBssDesc->fgIsConnected));

                /* NOTE: To prevent SWING, we do roaming only if target AP has at least 5dBm larger than us. */
                if (prCandidateBssDesc->fgIsConnected) {
                    if (prCandidateBssDesc->rRcpi + ROAMING_NO_SWING_RCPI_STEP <= prPrimaryBssDesc->rRcpi) {

                        prCandidateBssDesc = prPrimaryBssDesc;
                        prCandidateStaRec = prPrimaryStaRec;
                        continue;
                    }
                }
                else if (prPrimaryBssDesc->fgIsConnected) {
                    if (prCandidateBssDesc->rRcpi < prPrimaryBssDesc->rRcpi + ROAMING_NO_SWING_RCPI_STEP) {

                        prCandidateBssDesc = prPrimaryBssDesc;
                        prCandidateStaRec = prPrimaryStaRec;
                        continue;
                    }
                }
                else if (prCandidateBssDesc->rRcpi < prPrimaryBssDesc->rRcpi) {
                    prCandidateBssDesc = prPrimaryBssDesc;
                    prCandidateStaRec = prPrimaryStaRec;
                    continue;
                }
            }

            /* If reach here, that means they have the same Encryption Score, and
             * both RSSI value are close too.
             */
            //4 <6F> Seek the minimum Channel Load for less interference.
            if (fgIsFindMinChannelLoad) {

                /* TODO(Kevin): Check which one has minimum channel load in its channel */
            }
        }
    }


#if DBG
    if (prCandidateBssDesc) {
        DBGLOG(SCAN, TRACE, ("CANDIDATE BSS DESC(%#lx): MAC: "MACSTR", CH: %d, RSSI: %d\n",
            (UINT_32)prCandidateBssDesc, MAC2STR(prCandidateBssDesc->aucBSSID),
            prCandidateBssDesc->ucChannelNum, prCandidateBssDesc->rRcpi));
    }
#endif /* DBG */

    return prCandidateBssDesc;

} /* end of scanSearchBssDescByPolicy() */


/*----------------------------------------------------------------------------*/
/*!
* \brief Find the corresponding BSS Descriptor according to given BSSID
*
* \param[in] prAdapter  Pointer to the Adapter structure.
* \param[in] aucBSSID   Given BSSID.
*
* \return   Pointer to BSS Descriptor, if found. NULL, if not found
*/
/*----------------------------------------------------------------------------*/
P_BSS_DESC_T
scanSearchBssDescByBssid (
    IN P_ADAPTER_T prAdapter,
    IN UINT_8 aucBSSID[]
    )
{
    P_SCAN_INFO_T prScanInfo;
    P_LINK_T prBSSDescList;
    P_BSS_DESC_T prBssDesc;

    DEBUGFUNC("scanSearchBssDescByBssid");


    ASSERT(prAdapter);
    ASSERT(aucBSSID);
    prScanInfo = &prAdapter->rScanInfo;
    prBSSDescList = &prScanInfo->rBSSDescList;

    //4 <1> Search BSS Desc from current SCAN result list.
    LINK_FOR_EACH_ENTRY(prBssDesc, prBSSDescList, rLinkEntry, BSS_DESC_T) {

        BSS_DESC_CHK_GUID(prBssDesc);

        if (EQUAL_MAC_ADDR(prBssDesc->aucBSSID, aucBSSID)) {
            return prBssDesc;
        }
    }

    return (P_BSS_DESC_T)NULL;

} /* end of scanSearchBssDescByBssid() */


/*----------------------------------------------------------------------------*/
/*!
* \brief Find the corresponding BSS Descriptor according to given BSSID and TA,
*        try to allocate a new one if not found.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
* \param[in] eBSSType   BSS Type of incoming Beacon/ProbeResp frame.
* \param[in] aucBSSID   Given BSSID of Beacon/ProbeResp frame.
* \param[in] aucSrcAddr Given TA of Beacon/ProbeResp frame.
*
* \return   Pointer to BSS Descriptor
*/
/*----------------------------------------------------------------------------*/
P_BSS_DESC_T
scanSearchBssDescOrAddIfNotExist (
    IN P_ADAPTER_T prAdapter,
    IN ENUM_BSS_TYPE_T eBSSType,
    IN UINT_8 aucBSSID[],
    IN UINT_8 aucSrcAddr[]
    )
{
    P_SCAN_INFO_T prScanInfo;
    P_LINK_T prBSSDescList;
    P_LINK_T prFreeBSSDescList;
    P_BSS_DESC_T prBssDesc;
    P_BSS_DESC_T prIBssDesc = (P_BSS_DESC_T)NULL;

    DEBUGFUNC("scanSearchBssDescByBssidOrAddIfNotExist");


    ASSERT(prAdapter);
    ASSERT(aucBSSID);
    ASSERT(aucSrcAddr);
    prScanInfo = &prAdapter->rScanInfo;
    prBSSDescList = &prScanInfo->rBSSDescList;
    prFreeBSSDescList = &prScanInfo->rFreeBSSDescList;

    //4 <1> Search BSS Desc from current SCAN result list.
    /* NOTE(Kevin):
     * Rules to maintain the BSSID List:
     * 1. Every BSS/IBSS will map to a single entry of BSSID Descriptor. Because
     *    we report the SCAN result per BSSID(check PARAM_BSSID_EX_T).
     * 2. For Infrastructure - Use same BSSID entry if it exist.
     * 3. For AdHoc -
     *    CASE I ¡V We have TA1(BSSID1), but it change its BSSID to BSSID2
     *              -> Update TA1 entry's BSSID.
     *    CASE II ¡V We have TA1(BSSID1), and get TA1(BSSID1) again
     *              -> Update TA1 entry's contain.
     *    CASE III ¡V We have a SCAN result TA1(BSSID1), and TA2(BSSID2). Sooner or
     *               later, TA2 merge into TA1, we get TA2(BSSID1)
     *              -> Remove TA2 first and then replace TA1 entry's TA with TA2, Still have only one entry of BSSID.
     *    CASE IV ¡V We have a SCAN result TA1(BSSID1), and another TA2 also merge into BSSID1.
     *              -> Replace TA1 entry's TA with TA2, Still have only one entry.
     */
    LINK_FOR_EACH_ENTRY(prBssDesc, prBSSDescList, rLinkEntry, BSS_DESC_T) {

        BSS_DESC_CHK_GUID(prBssDesc);

        if (EQUAL_MAC_ADDR(prBssDesc->aucBSSID, aucBSSID)) {
            if (eBSSType == BSS_TYPE_INFRASTRUCTURE) {
                return prBssDesc;
            }
            else {
                prIBssDesc = prBssDesc;
                break;
            }
        }
    }

    if (eBSSType == BSS_TYPE_IBSS) {
        P_BSS_DESC_T prBSSDescNext;

        LINK_FOR_EACH_ENTRY_SAFE(prBssDesc, prBSSDescNext, prBSSDescList, rLinkEntry, BSS_DESC_T) {

            BSS_DESC_CHK_GUID(prBssDesc);

            if (EQUAL_MAC_ADDR(prBssDesc->aucSrcAddr, aucSrcAddr)) {

                if ((!prIBssDesc) || // CASE I
                    (prBssDesc == prIBssDesc)) { // CASE II

                    return prBssDesc;
                }
                else { // CASE III
                    /* Remove this BSS Desc from the BSS Desc list */
                    LINK_REMOVE_KNOWN_ENTRY(prBSSDescList, prBssDesc);

                    /* Return this BSS Desc to the free BSS Desc list. */
                    LINK_INSERT_TAIL(&prScanInfo->rFreeBSSDescList, &prBssDesc->rLinkEntry);

                    return prIBssDesc;
                }
            }
        }

        if (prIBssDesc) { // CASE IV
            return prIBssDesc;
        }
    }


    //4 <2> No such Record, try to alloc an entry of BSS Desc for this new BSS.
    do {
        LINK_REMOVE_HEAD(prFreeBSSDescList, prBssDesc, P_BSS_DESC_T);
        if (prBssDesc) {
            break;
        }

        //4 <2.1> Hidden is useless, remove the oldest hidden ssid.
        scanRemoveBssDescsByPolicy(prAdapter, (SCAN_RM_POLICY_EXCLUDE_CONNECTED | \
                                               SCAN_RM_POLICY_OLDEST_HIDDEN) );

        //4 <2.2> Try to get an entry again.
        LINK_REMOVE_HEAD(prFreeBSSDescList, prBssDesc, P_BSS_DESC_T);
        if (prBssDesc) {
            break;
        }
        
#if 1
        //4 <2.3> Remove the weakest one
        /* If there are more than half of BSS which has the same ssid as connection
         * setting, remove the weakest one from them. 
         * Else remove the weakest one.
         */
        scanRemoveBssDescsByPolicy(prAdapter, (SCAN_RM_POLICY_EXCLUDE_CONNECTED | \
                                               SCAN_RM_POLICY_SMART_WEAKEST) );

        //4 <2.4> Try to get an entry again.
        LINK_REMOVE_HEAD(prFreeBSSDescList, prBssDesc, P_BSS_DESC_T);
        if (prBssDesc) {
            break;
        }
#else
        //4 <2.3> Remove the weakest one
        scanRemoveBssDescsByPolicy(prAdapter, (SCAN_RM_POLICY_EXCLUDE_CONNECTED | \
                                               SCAN_RM_POLICY_WEAKEST) );

        //4 <2.4> Try to get an entry again.
        LINK_REMOVE_HEAD(prFreeBSSDescList, prBssDesc, P_BSS_DESC_T);
        if (prBssDesc) {
            break;
        }
#endif

        ASSERT(prBssDesc);
    }
    while (FALSE);

    //4 <3> Clear the content of this new SCAN record.
    if (prBssDesc) {
        kalMemZero(prBssDesc, sizeof(BSS_DESC_T));

        BSS_DESC_SET_GUID(prBssDesc);

        //4 <4> Insert this BSS Desc into SCAN result.
        /* Return this BSS Desc to the current BSS Desc list. */
        LINK_INSERT_TAIL(prBSSDescList, &prBssDesc->rLinkEntry);
    }

    return prBssDesc;

} /* end of scanSearchBssDescOrAddIfNotExist() */


/*----------------------------------------------------------------------------*/
/*!
* \brief Delete BSS Descriptors from current list according to given Remove Policy.
*
* \param[in] prAdapter          Pointer to the Adapter structure.
* \param[in] u4RemovePolicy     Remove Policy.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
scanRemoveBssDescsByPolicy (
    IN P_ADAPTER_T prAdapter,
    IN UINT_32 u4RemovePolicy
    )
{
    P_CONNECTION_SETTINGS_T prConnSettings;
    P_SCAN_INFO_T prScanInfo;
    P_LINK_T prBSSDescList;
    P_BSS_DESC_T prBssDesc;

    DEBUGFUNC("scanRemoveBssDescsByPolicy");


    ASSERT(prAdapter);
    prConnSettings = &prAdapter->rConnSettings;
    prScanInfo =  &prAdapter->rScanInfo;
    prBSSDescList = &prScanInfo->rBSSDescList;

    //DBGLOG(SCAN, TRACE, ("Before Remove - Number Of SCAN Result = %ld\n",
        //prBSSDescList->u4NumElem));

    if (u4RemovePolicy & SCAN_RM_POLICY_TIMEOUT) {
        P_BSS_DESC_T prBSSDescNext;
        OS_SYSTIME rCurrentTime;


        GET_CURRENT_SYSTIME(&rCurrentTime);

        LINK_FOR_EACH_ENTRY_SAFE(prBssDesc, prBSSDescNext, prBSSDescList, rLinkEntry, BSS_DESC_T) {

            BSS_DESC_CHK_GUID(prBssDesc);

            if ((u4RemovePolicy & SCAN_RM_POLICY_EXCLUDE_CONNECTED) &&
                (prBssDesc->fgIsConnected || prBssDesc->fgIsConnecting)) {
                /* Don't remove the one currently we are connected. */
                continue;
            }

            if (CHECK_FOR_TIMEOUT(rCurrentTime, prBssDesc->rUpdateTime,
                SEC_TO_SYSTIME(BSS_DESC_REMOVE_TIMEOUT_SEC))) {

                //DBGLOG(SCAN, TRACE, ("Remove TIMEOUT BSS DESC(%#x): MAC: "MACSTR", Current Time = %08lx, Update Time = %08lx\n",
                    //prBssDesc, MAC2STR(prBssDesc->aucBSSID), rCurrentTime, prBssDesc->rUpdateTime));

                /* Remove this BSS Desc from the BSS Desc list */
                LINK_REMOVE_KNOWN_ENTRY(prBSSDescList, prBssDesc);

                /* Return this BSS Desc to the free BSS Desc list. */
                LINK_INSERT_TAIL(&prScanInfo->rFreeBSSDescList, &prBssDesc->rLinkEntry);
            }
        }
    }
    else if (u4RemovePolicy & SCAN_RM_POLICY_OLDEST) {
        P_BSS_DESC_T prBssDescOldest = (P_BSS_DESC_T)NULL;


        LINK_FOR_EACH_ENTRY(prBssDesc, prBSSDescList, rLinkEntry, BSS_DESC_T) {

            BSS_DESC_CHK_GUID(prBssDesc);

            if ((u4RemovePolicy & SCAN_RM_POLICY_EXCLUDE_CONNECTED) &&
                (prBssDesc->fgIsConnected || prBssDesc->fgIsConnecting)) {
                /* Don't remove the one currently we are connected. */
                continue;
            }

            if (!prBssDescOldest) { /* 1st element */
                prBssDescOldest = prBssDesc;
                continue;
            }

            if (TIME_BEFORE(prBssDesc->rUpdateTime, prBssDescOldest->rUpdateTime)) {
                prBssDescOldest = prBssDesc;
            }
        }

        if (prBssDescOldest) {

            //DBGLOG(SCAN, TRACE, ("Remove OLDEST BSS DESC(%#x): MAC: "MACSTR", Update Time = %08lx\n",
                //prBssDescOldest, MAC2STR(prBssDescOldest->aucBSSID), prBssDescOldest->rUpdateTime));

            /* Remove this BSS Desc from the BSS Desc list */
            LINK_REMOVE_KNOWN_ENTRY(prBSSDescList, prBssDescOldest);

            /* Return this BSS Desc to the free BSS Desc list. */
            LINK_INSERT_TAIL(&prScanInfo->rFreeBSSDescList, &prBssDescOldest->rLinkEntry);
        }
    }
    else if (u4RemovePolicy & SCAN_RM_POLICY_WEAKEST) {
        P_BSS_DESC_T prBssDescWeakest = (P_BSS_DESC_T)NULL;


        LINK_FOR_EACH_ENTRY(prBssDesc, prBSSDescList, rLinkEntry, BSS_DESC_T) {

            BSS_DESC_CHK_GUID(prBssDesc);

            if ((u4RemovePolicy & SCAN_RM_POLICY_EXCLUDE_CONNECTED) &&
                (prBssDesc->fgIsConnected || prBssDesc->fgIsConnecting)) {
                /* Don't remove the one currently we are connected. */
                continue;
            }

            if (!prBssDescWeakest) { /* 1st element */
                prBssDescWeakest = prBssDesc;
                continue;
            }

            if (prBssDesc->rRcpi < prBssDescWeakest->rRcpi) {
                prBssDescWeakest = prBssDesc;
            }
        }

        if (prBssDescWeakest) {

            //DBGLOG(SCAN, TRACE, ("Remove WEAKEST BSS DESC(%#x): MAC: "MACSTR", Update Time = %08lx\n",
                //prBssDescOldest, MAC2STR(prBssDescOldest->aucBSSID), prBssDescOldest->rUpdateTime));

            /* Remove this BSS Desc from the BSS Desc list */
            LINK_REMOVE_KNOWN_ENTRY(prBSSDescList, prBssDescWeakest);

            /* Return this BSS Desc to the free BSS Desc list. */
            LINK_INSERT_TAIL(&prScanInfo->rFreeBSSDescList, &prBssDescWeakest->rLinkEntry);
        }
    }
    else if (u4RemovePolicy & SCAN_RM_POLICY_OLDEST_HIDDEN) {
        P_BSS_DESC_T prBssDescOldest = (P_BSS_DESC_T)NULL;


        LINK_FOR_EACH_ENTRY(prBssDesc, prBSSDescList, rLinkEntry, BSS_DESC_T) {

            BSS_DESC_CHK_GUID(prBssDesc);

            if ((u4RemovePolicy & SCAN_RM_POLICY_EXCLUDE_CONNECTED) &&
                (prBssDesc->fgIsConnected || prBssDesc->fgIsConnecting)) {
                /* Don't remove the one currently we are connected. */
                continue;
            }

            if (!prBssDesc->fgIsHiddenSSID) {
                continue;
            }

            if (!prBssDescOldest) { /* 1st element */
                prBssDescOldest = prBssDesc;
                continue;
            }

            if (TIME_BEFORE(prBssDesc->rUpdateTime, prBssDescOldest->rUpdateTime)) {
                prBssDescOldest = prBssDesc;
            }
        }

        if (prBssDescOldest) {

            //DBGLOG(SCAN, TRACE, ("Remove OLDEST BSS DESC(%#x): MAC: "MACSTR", Update Time = %08lx\n",
                //prBssDescOldest, MAC2STR(prBssDescOldest->aucBSSID), prBssDescOldest->rUpdateTime));

            /* Remove this BSS Desc from the BSS Desc list */
            LINK_REMOVE_KNOWN_ENTRY(prBSSDescList, prBssDescOldest);

            /* Return this BSS Desc to the free BSS Desc list. */
            LINK_INSERT_TAIL(&prScanInfo->rFreeBSSDescList, &prBssDescOldest->rLinkEntry);
        }
    }
    else if (u4RemovePolicy & SCAN_RM_POLICY_SMART_WEAKEST) {
        P_BSS_DESC_T prBssDescWeakest = (P_BSS_DESC_T)NULL;
        P_BSS_DESC_T prBssDescWeakestSameSSID = (P_BSS_DESC_T)NULL;
        UINT_32 u4SameSSIDCount = 0;

        LINK_FOR_EACH_ENTRY(prBssDesc, prBSSDescList, rLinkEntry, BSS_DESC_T) {

            BSS_DESC_CHK_GUID(prBssDesc);

            if ((u4RemovePolicy & SCAN_RM_POLICY_EXCLUDE_CONNECTED) &&
                (prBssDesc->fgIsConnected || prBssDesc->fgIsConnecting)) {
                /* Don't remove the one currently we are connected. */
                continue;
            }

            if ((!prBssDesc->fgIsHiddenSSID) &&
                (EQUAL_SSID(prBssDesc->aucSSID,
                           prBssDesc->ucSSIDLen,
                           prConnSettings->aucSSID,
                           prConnSettings->ucSSIDLen))) {

                u4SameSSIDCount++;
                
                if (!prBssDescWeakestSameSSID) {
                    prBssDescWeakestSameSSID = prBssDesc;
                }
                else if (prBssDesc->rRcpi < prBssDescWeakestSameSSID->rRcpi) {
                    prBssDescWeakestSameSSID = prBssDesc;
                }
            }

            if (!prBssDescWeakest) { /* 1st element */
                prBssDescWeakest = prBssDesc;
                continue;
            }

            if (prBssDesc->rRcpi < prBssDescWeakest->rRcpi) {
                prBssDescWeakest = prBssDesc;
            }
        }

        if ((u4SameSSIDCount >= (CFG_MAX_NUM_BSS_LIST / 2)) &&
            (prBssDescWeakestSameSSID)) {
            prBssDescWeakest = prBssDescWeakestSameSSID;
        }

        if (prBssDescWeakest) {

            //DBGLOG(SCAN, TRACE, ("Remove WEAKEST BSS DESC(%#x): MAC: "MACSTR", Update Time = %08lx\n",
                //prBssDescOldest, MAC2STR(prBssDescOldest->aucBSSID), prBssDescOldest->rUpdateTime));

            /* Remove this BSS Desc from the BSS Desc list */
            LINK_REMOVE_KNOWN_ENTRY(prBSSDescList, prBssDescWeakest);

            /* Return this BSS Desc to the free BSS Desc list. */
            LINK_INSERT_TAIL(&prScanInfo->rFreeBSSDescList, &prBssDescWeakest->rLinkEntry);
        }
    }
    else if (u4RemovePolicy & SCAN_RM_POLICY_ENTIRE) {
        P_BSS_DESC_T prBSSDescNext;

        LINK_FOR_EACH_ENTRY_SAFE(prBssDesc, prBSSDescNext, prBSSDescList, rLinkEntry, BSS_DESC_T) {

            BSS_DESC_CHK_GUID(prBssDesc);

            if ((u4RemovePolicy & SCAN_RM_POLICY_EXCLUDE_CONNECTED) &&
                (prBssDesc->fgIsConnected || prBssDesc->fgIsConnecting)) {
                /* Don't remove the one currently we are connected. */
                continue;
            }

            /* Remove this BSS Desc from the BSS Desc list */
            LINK_REMOVE_KNOWN_ENTRY(prBSSDescList, prBssDesc);

            /* Return this BSS Desc to the free BSS Desc list. */
            LINK_INSERT_TAIL(&prScanInfo->rFreeBSSDescList, &prBssDesc->rLinkEntry);
        }
    }

    //DBGLOG(SCAN, TRACE, ("After Remove - Number Of SCAN Result = %ld\n",
        //prBSSDescList->u4NumElem));

    return;

} /* end of scanRemoveBssDescsByPolicy() */


/*----------------------------------------------------------------------------*/
/*!
* \brief Delete BSS Descriptors from current list according to given BSSID.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
* \param[in] aucBSSID   Given BSSID.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
scanRemoveBssDescByBssid (
    IN P_ADAPTER_T prAdapter,
    IN UINT_8 aucBSSID[]
    )
{
    P_SCAN_INFO_T prScanInfo;
    P_LINK_T prBSSDescList;
    P_BSS_DESC_T prBssDesc = (P_BSS_DESC_T)NULL;
    P_BSS_DESC_T prBSSDescNext;

    DEBUGFUNC("scanRemoveBssDescByBssid");


    ASSERT(prAdapter);
    ASSERT(aucBSSID);
    prScanInfo =  &prAdapter->rScanInfo;
    prBSSDescList = &prScanInfo->rBSSDescList;

    /* Check if such BSS Descriptor exists in a valid list */
    LINK_FOR_EACH_ENTRY_SAFE(prBssDesc, prBSSDescNext, prBSSDescList, rLinkEntry, BSS_DESC_T) {

        BSS_DESC_CHK_GUID(prBssDesc);

        if (EQUAL_MAC_ADDR(prBssDesc->aucBSSID, aucBSSID)) {
            /* Remove this BSS Desc from the BSS Desc list */
            LINK_REMOVE_KNOWN_ENTRY(prBSSDescList, prBssDesc);

            /* Return this BSS Desc to the free BSS Desc list. */
            LINK_INSERT_TAIL(&prScanInfo->rFreeBSSDescList, &prBssDesc->rLinkEntry);
            return;
        }
    }

    return;

} /* end of scanRemoveBssDescByBssid() */


/*----------------------------------------------------------------------------*/
/*!
* \brief Clear the CONNECTION FLAG of a specified BSS Descriptor.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
* \param[in] aucBSSID   Given BSSID.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
scanRemoveConnectionFlagOfBssDescByBssid (
    IN P_ADAPTER_T prAdapter,
    IN UINT_8 aucBSSID[]
    )
{
    P_SCAN_INFO_T prScanInfo;
    P_LINK_T prBSSDescList;
    P_BSS_DESC_T prBssDesc = (P_BSS_DESC_T)NULL;

    DEBUGFUNC("scanRemoveConnectionFlagOfBssDescByBssid");


    ASSERT(prAdapter);
    ASSERT(aucBSSID);
    prScanInfo =  &prAdapter->rScanInfo;
    prBSSDescList = &prScanInfo->rBSSDescList;

    /* Check if such BSS Descriptor exists in a valid list */
    if (LINK_IS_VALID(prBSSDescList)) {
        LINK_FOR_EACH_ENTRY(prBssDesc, prBSSDescList, rLinkEntry, BSS_DESC_T) {

            BSS_DESC_CHK_GUID(prBssDesc);

            if (EQUAL_MAC_ADDR(prBssDesc->aucBSSID, aucBSSID)) {
                prBssDesc->fgIsConnected = FALSE;
                prBssDesc->fgIsConnecting = FALSE;
                break;
            }
        }
    }

    return;

} /* end of scanRemoveConnectionFlagOfBssDescByBssid() */


/*----------------------------------------------------------------------------*/
/*!
* \brief Parse the content of given Beacon or ProbeResp Frame.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
* \param[in] prSWRfb        Pointer to the receiving frame buffer.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
scanProcessBeaconAndProbeResp (
    IN P_ADAPTER_T prAdapter,
    IN P_SW_RFB_T prSWRfb
    )
{
    P_BSS_DESC_T prBSSDesc = NULL;
    PUINT_8 pucIE = NULL;

    UINT_16 u2Offset = 0;
    P_WLAN_MAC_HEADER_T prWLANHdr;
    P_WLAN_BEACON_FRAME_T prWlanBeaconFrame;

    P_IE_SUPPORTED_RATE_T prIeSupportedRate = (P_IE_SUPPORTED_RATE_T)NULL;
    P_IE_EXT_SUPPORTED_RATE_T prIeExtSupportedRate = (P_IE_EXT_SUPPORTED_RATE_T)NULL;
    UINT_16 u2CapInfo;

    UINT_8 ucHwChannelNum = 0; /* Channel Information from MAC */
    ENUM_BAND_T eHwBand = BAND_24G; /* Channel Information from MAC */

    ENUM_BSS_TYPE_T eBSSType;
    RCPI rRcpi;

    DEBUGFUNC("scanProcessBeaconAndProbeResp");


    ASSERT(prAdapter);
    ASSERT(prSWRfb);
    prWLANHdr = (P_WLAN_MAC_HEADER_T)prSWRfb->pvHeader;
    prWlanBeaconFrame = (P_WLAN_BEACON_FRAME_T)prWLANHdr;

    //DBGLOG_MEM8(RX, TRACE, prWlanBeaconFrame, prSWRfb->u2FrameLength);
    //DBGLOG_MEM32(RX, TRACE, (PUINT_32)prSWRfb->prRxStatus,
        //DWORD_TO_BYTE((prSWRfb->prRxStatus->u2OverallBufferLengthDW & RX_STATUS_BUFFER_LENGTH_MASK) - 1));

    if (prSWRfb->u2FrameLength < (WLAN_MAC_MGMT_HEADER_LEN +
                                  TIMESTAMP_FIELD_LEN +
                                  BEACON_INTERVAL_FIELD_LEN +
                                  CAP_INFO_FIELD_LEN)) {
        ASSERT(0);
        return;
    }

    WLAN_GET_FIELD_16(&prWlanBeaconFrame->u2CapInfo,
                        &u2CapInfo);

    switch (u2CapInfo & CAP_INFO_BSS_TYPE) {
    case CAP_INFO_ESS:
        eBSSType = BSS_TYPE_INFRASTRUCTURE;
        break;

    case CAP_INFO_IBSS:
        eBSSType = BSS_TYPE_IBSS;
        break;

    default:
        DBGLOG(MGT, LOUD, ("Invalid ESS and IBSS bits in Cap Info field\n"));
        return;
    }

    //4 <1> Get a record or create one if it isn't exist.
    prBSSDesc = scanSearchBssDescOrAddIfNotExist(prAdapter,
                                                 eBSSType,
                                                 (PUINT_8)prWlanBeaconFrame->aucBSSID,
                                                 (PUINT_8)prWlanBeaconFrame->aucSrcAddr);
    /* NOTE: Keep consistency of Scan Record during JOIN process */
    if (prBSSDesc->fgIsConnecting) {
        return;
    }

    //4 <2> Get information from Fixed Fields
    COPY_MAC_ADDR(prBSSDesc->aucSrcAddr, prWlanBeaconFrame->aucSrcAddr);

    COPY_MAC_ADDR(prBSSDesc->aucBSSID, prWlanBeaconFrame->aucBSSID);

    WLAN_GET_FIELD_64(&prWlanBeaconFrame->au4Timestamp[0], &prBSSDesc->u8TimeStamp);

    WLAN_GET_FIELD_16(&prWlanBeaconFrame->u2BeaconInterval,
                        &prBSSDesc->u2BeaconInterval);

    prBSSDesc->u2CapInfo = u2CapInfo;
    prBSSDesc->eBSSType = eBSSType;

    prBSSDesc->u2ATIMWindow = 0;
    prBSSDesc->fgIsERPPresent = FALSE;
    prBSSDesc->ucERP = 0x0; /*(UINT_8)NULL; */
    prBSSDesc->ucWmmFlag = 0;
    prBSSDesc->prIEWPA = WPA_IE(NULL);
    prBSSDesc->prIERSN = RSN_IE(NULL);
    prBSSDesc->prIeWmmParamElem = WMM_PARAM_IE(NULL);

    prBSSDesc->u2IELength = prSWRfb->u2FrameLength - WLAN_MAC_HEADER_LEN;

    if (prBSSDesc->u2IELength > CFG_IE_BUFFER_SIZE) {
        prBSSDesc->u2IELength = CFG_IE_BUFFER_SIZE;
    }

    kalMemCopy(prBSSDesc->aucIEBuf,
               (PUINT_8)prSWRfb->pvBody,
               prBSSDesc->u2IELength);

    //4 <3> Get information from IEs
    pucIE = ((P_WLAN_BEACON_FRAME_BODY_T)prBSSDesc->aucIEBuf)->aucInfoElem;

    IE_FOR_EACH(pucIE,
                (prBSSDesc->u2IELength - OFFSET_OF(WLAN_BEACON_FRAME_BODY_T, aucInfoElem)),
                u2Offset) {

        switch (IE_ID(pucIE)) {
        case ELEM_ID_SSID:
            if (IE_LEN(pucIE) <= ELEM_MAX_LEN_SSID) {
                BOOLEAN fgIsHiddenSSID = FALSE;
                UINT_32 i;
                UINT_8 ucSSIDChar = '\0';

                /* D-Link DWL-900AP+ */
                if (IE_LEN(pucIE) == 0) {
                    fgIsHiddenSSID = TRUE;
                }
#if 0 /* NOTE(Kevin 2008/02/25): Which AP ?, we should not include such case in my opinion. */
                else if ((IE_LEN(pucIE) == 1) && (SSID_IE(pucIE)->aucSSID[0] == 0x20)) {
                    fgIsHiddenSSID = TRUE;
                }
#endif
                /* Cisco AP1230A - (IE_LEN(pucIE) == 1) && (SSID_IE(pucIE)->aucSSID[0] == '\0') */
                /* Linksys WRK54G/ASUS WL520g - (IE_LEN(pucIE) == n) && (SSID_IE(pucIE)->aucSSID[0~(n-1)] == '\0') */
                else {
                    for (i = 0; i < IE_LEN(pucIE); i++) {
                        ucSSIDChar |= SSID_IE(pucIE)->aucSSID[i];
                    }

                    if (!ucSSIDChar) {
                        fgIsHiddenSSID = TRUE;
                    }
                }

                /* Update SSID to BSS Descriptor only if SSID is not hidden. */
                if (!fgIsHiddenSSID) {
                    COPY_SSID(prBSSDesc->aucSSID,
                              prBSSDesc->ucSSIDLen,
                              SSID_IE(pucIE)->aucSSID,
                              SSID_IE(pucIE)->ucLength);
                }

                /* Update Flag of Hidden SSID for used in SEARCH STATE. */
                /* NOTE(Kevin): in current driver, the ucSSIDLen == 0 represent
                 * all cases of hidden SSID.
                 * If the fgIsHiddenSSID == TRUE, it means we didn't get the ProbeResp with
                 * valid SSID.
                 */
                if (prBSSDesc->ucSSIDLen == 0) {
                    prBSSDesc->fgIsHiddenSSID = TRUE;
                }
                else {
                    prBSSDesc->fgIsHiddenSSID = FALSE;
                }

            }
            break;

        case ELEM_ID_SUP_RATES:
            /* NOTE(Kevin): Buffalo WHR-G54S's supported rate set IE exceed 8.
             * IE_LEN(pucIE) == 12, "1(B), 2(B), 5.5(B), 6(B), 9(B), 11(B),
             * 12(B), 18(B), 24(B), 36(B), 48(B), 54(B)"
             */
            // if (IE_LEN(pucIE) <= ELEM_MAX_LEN_SUP_RATES) {            
            if (IE_LEN(pucIE) <= RATE_NUM) {
                prIeSupportedRate = SUP_RATES_IE(pucIE);
            }
            break;

        case ELEM_ID_DS_PARAM_SET:
            if (IE_LEN(pucIE) == ELEM_MAX_LEN_DS_PARAMETER_SET) {
                prBSSDesc->ucChannelNum = DS_PARAM_IE(pucIE)->ucCurrChnl;
            }
            break;

        case ELEM_ID_TIM:
            if (IE_LEN(pucIE) <= ELEM_MAX_LEN_TIM) {
                prBSSDesc->ucDTIMPeriod = TIM_IE(pucIE)->ucDTIMPeriod;
            }
            break;

        case ELEM_ID_IBSS_PARAM_SET:
            if (IE_LEN(pucIE) == ELEM_MAX_LEN_IBSS_PARAMETER_SET){
                prBSSDesc->u2ATIMWindow = IBSS_PARAM_IE(pucIE)->u2ATIMWindow;
            }
            break;
#if CFG_SUPPORT_802_11D
        case ELEM_ID_COUNTRY_INFO:
            prBSSDesc->prIECountry = (P_IE_COUNTRY_T)pucIE;
            break;
#endif

        case ELEM_ID_ERP_INFO:
            if (IE_LEN(pucIE) == ELEM_MAX_LEN_ERP) {
                prBSSDesc->fgIsERPPresent = TRUE;
                prBSSDesc->ucERP = ERP_INFO_IE(pucIE)->ucERP;
            }
            break;

        case ELEM_ID_RSN:
            if (IE_LEN(pucIE) <= ELEM_MAX_LEN_RSN_IE) {
            RSN_INFO_T  rRsnInfo;

            prBSSDesc->prIERSN = RSN_IE(pucIE);
            if (rsnParseRsnIE(prBSSDesc->prIERSN, &rRsnInfo)) {
                prBSSDesc->u2RsnCap = rRsnInfo.u2RsnCap;
                rsnCheckPmkidCache(prAdapter, prBSSDesc);
            }
            }
        break;

        case ELEM_ID_EXTENDED_SUP_RATES:
            prIeExtSupportedRate = EXT_SUP_RATES_IE(pucIE);
            break;

#if SUPPORT_WAPI
        case ELEM_ID_WAPI:
            prBSSDesc->prIEWAPI = WAPI_IE(pucIE);
            break;
#endif

        case ELEM_ID_VENDOR:
            /* Try to Get WPA IE */
            {   UINT_8 ucOuiType;
                UINT_16 u2SubTypeVersion;

                if (parseCheckForWFAInfoElem(pucIE, &ucOuiType, &u2SubTypeVersion)) {
                    if ((ucOuiType == VENDOR_OUI_TYPE_WPA) &&
                        (u2SubTypeVersion == VERSION_WPA)) {

                        prBSSDesc->prIEWPA = WPA_IE(pucIE);

                    }
                    /* Setup WMM capability */
                    /* NOTE(Kevin 2007/11/30):
                     * From WMM Specification 1.1
                     *     Beacon will have either a WMM IE or WMM PARAM IE.
                     *     ProbeResp(AP) will have WMM PARAM IE.
                     *     ProbeResp(IBSS) will have WMM PARAM IE if the ProbeReq is
                     *         from the same IBSS.
                     */
                    else if ((ucOuiType == VENDOR_OUI_TYPE_WMM) &&
                             (u2SubTypeVersion == VENDOR_OUI_SUBTYPE_VERSION_WMM_INFO)) {
                        UINT_8 ucWmmFlag = 0;

                        if (qosCheckQoSCapabilityByWMMInfoElem(pucIE, &ucWmmFlag)) {
                            prBSSDesc->ucWmmFlag = ucWmmFlag;
                        }
                    }
                    else if ((ucOuiType == VENDOR_OUI_TYPE_WMM) &&
                             (u2SubTypeVersion == VENDOR_OUI_SUBTYPE_VERSION_WMM_PARAM)) {
                        UINT_8 ucWmmFlag = 0;

                        prBSSDesc->prIeWmmParamElem = WMM_PARAM_IE(pucIE);

                        if (qosCheckQoSCapabilityByWMMParamElem(pucIE, &ucWmmFlag)) {
                            prBSSDesc->ucWmmFlag = ucWmmFlag;
                        }
                    }
                }
            }
            break;

        default:
        break;
        }
    }

    //4 <4> Check information in those IEs.
    if (prIeSupportedRate || prIeExtSupportedRate) {
        rateGetRateSetFromIEs(prIeSupportedRate,
                              prIeExtSupportedRate,
                              &prBSSDesc->u2OperationalRateSet,
                              &prBSSDesc->u2BSSBasicRateSet,
                              &prBSSDesc->fgIsUnknownBssBasicRate);
    }


    /* NOTE(Kevin): The TCL has bug, we'll update fgIsLargerTSF with correct info
     * laterly.
     */
    prBSSDesc->fgIsLargerTSF = NIC_RFB_IS_TCL(prSWRfb);


    /* TODO(Kevin): Add code to check PHY TYPE - OFDM here according to the band info from RFB. */
    if ((prBSSDesc->u2OperationalRateSet & RATE_SET_OFDM) ||
        prBSSDesc->fgIsERPPresent) {
        prBSSDesc->ePhyType = PHY_TYPE_ERP_INDEX;
        prBSSDesc->eBand = BAND_24G;
    }
    else {
        prBSSDesc->ePhyType = PHY_TYPE_HR_DSSS_INDEX;
        prBSSDesc->eBand = BAND_24G;
    }

    /* Need to get the channel/ band information from HW */
    nicHwScanScannedChnlFreqBand(prAdapter,
                                 prSWRfb->prRxStatus->u2QoSCtrl,
                                 &ucHwChannelNum,
                                 &eHwBand);

    /* Update RCPI only for Beacon/ProResp frames received in the right channel */
    rRcpi = NIC_RFB_GET_RCPI(prSWRfb);

    if (prBSSDesc->ucChannelNum == ucHwChannelNum) {

#if 0
        if (prBSSDesc->fgIsConnected) {
            UINT_32 u4Rcpi = (UINT_32)prBSSDesc->rRcpi;


            DBGLOG(SCAN, INFO, ("Org prBSSDesc->rRcpi = %d, rRcpi = %d\n", prBSSDesc->rRcpi, rRcpi));

            u4Rcpi = u4Rcpi * 7 + (UINT_32)rRcpi;
            u4Rcpi = u4Rcpi / 8; // NOTE: Follow the same rule of RR_RCPI_PARM_1_OF_8.

            prBSSDesc->rRcpi = (RCPI)u4Rcpi;

            DBGLOG(SCAN, INFO, ("New prBSSDesc->rRcpi = %d\n", prBSSDesc->rRcpi));

        }
        else
#endif        
        {
            prBSSDesc->rRcpi = rRcpi;
            //DBGLOG(SCAN, INFO, ("prBSSDesc->rRcpi = %d\n", prBSSDesc->rRcpi));  
        }
    }
    else if ((!prBSSDesc->rRcpi) ||
            (rRcpi > prBSSDesc->rRcpi)) {
        /* Update for 1st Time Scan and larger RCPI value even it come from other channel */
        prBSSDesc->rRcpi = rRcpi;
    }

#if 0 // NOTE(Kevin) removed */
    if (prBSSDesc->fgIsConnected) {
        RCPI rRcpi = NIC_RFB_GET_RCPI(prSWRfb);
        UINT_32 u4Rcpi = (UINT_32)prBSSDesc->rRcpi;


        DBGLOG(SCAN, INFO, ("Org prBSSDesc->rRcpi = %d, rRcpi = %d\n", prBSSDesc->rRcpi, rRcpi));

        u4Rcpi = u4Rcpi * 7 + (UINT_32)rRcpi;
        u4Rcpi = u4Rcpi / 8; // NOTE: Follow the same rule of RR_RCPI_PARM_1_OF_8.

        prBSSDesc->rRcpi = (RCPI)u4Rcpi;

        DBGLOG(SCAN, INFO, ("New prBSSDesc->rRcpi = %d\n", prBSSDesc->rRcpi));

    }
    else {

#if CFG_LP_PATTERN_SEARCH_SLT
        if (TIME_AFTER(prBSSDesc->rUpdateTime, prAdapter->rArbInfo.rLastScanRequestTime)) {
            if (prBSSDesc->rRcpi < NIC_RFB_GET_RCPI(prSWRfb)) {
                prBSSDesc->rRcpi = NIC_RFB_GET_RCPI(prSWRfb);
            }
        }
        else {
            prBSSDesc->rRcpi = NIC_RFB_GET_RCPI(prSWRfb);
        }
#else
        prBSSDesc->rRcpi = NIC_RFB_GET_RCPI(prSWRfb);
        //DBGLOG(SCAN, INFO, ("prBSSDesc->rRcpi = %d\n", prBSSDesc->rRcpi));
#endif

    }
#endif

/* NOTE(Kevin 2009/07/15): We need to check following code if need to support abg */
#if CFG_ONLY_802_11A
        /* Need to get the channel/ band information from HW */
        nicHwScanScannedChnlFreqBand(prAdapter,
                                     prSWRfb->prRxStatus->u2QoSCtrl,
                                     &prBSSDesc->ucChannelNum,
                                     &prBSSDesc->eBand);
#endif


    //4 Update BSS_DESC_T's Last Update TimeStamp.
    GET_CURRENT_SYSTIME(&prBSSDesc->rUpdateTime);

    //4 <n> Handle the Beacon/ ProbeResp Frame for a specific Operation Mode.
    if ((prAdapter->eCurrentOPMode == OP_MODE_INFRASTRUCTURE) &&
        (prAdapter->eConnectionState == MEDIA_STATE_CONNECTED)) {
        bssProcessBeacon(prAdapter, prBSSDesc, prSWRfb);
    }
    else if (prAdapter->eCurrentOPMode == OP_MODE_IBSS) {
        /* For the case of IBSS ALONE, the ConnectionState != CONNECTED */
        ibssProcessBeacon(prAdapter, prBSSDesc, prSWRfb);
    }
#if 0 /* TODO(Kevin): for customer */
    else if (prAdapter->eCurrentOPMode == OP_MODE_RESERVED) {
        ASSERT(0);
    }
#endif


#if CFG_LP_IOT
    {
    P_BSS_INFO_T prBssInfo = &prAdapter->rBssInfo;
    OS_SYSTIME rCurrentSysTime;
    if (prAdapter->eConnectionState == MEDIA_STATE_CONNECTED) {
        GET_CURRENT_SYSTIME(&rCurrentSysTime);
        if (EQUAL_MAC_ADDR(prBssInfo->aucBSSID, prBSSDesc->aucBSSID)) {
            if ((prWLANHdr->u2FrameCtrl & MASK_FC_SUBTYPE) == MAC_FRAME_BEACON) {
                DBGLOG(LP_IOT, INFO, ("[LP-IOT] Beacon with the same BSSID is received\n"));
                dumpMemory8(prSWRfb->pvHeader, prSWRfb->u2FrameLength);
            } else {
                DBGLOG(LP_IOT, INFO, ("[LP-IOT] probe response with the same BSSID is received\n"));
                dumpMemory8(prSWRfb->pvHeader, prSWRfb->u2FrameLength);
            }
        } else {
            if ((prWLANHdr->u2FrameCtrl & MASK_FC_SUBTYPE) == MAC_FRAME_BEACON) {
                DBGLOG(LP_IOT, INFO, ("[LP-IOT] Beacon with different BSSID is received\n"));
                dumpMemory8(prSWRfb->pvHeader, prSWRfb->u2FrameLength);
            } else {
                DBGLOG(LP_IOT, INFO, ("[LP-IOT] probe response with different BSSID is received\n"));
                dumpMemory8(prSWRfb->pvHeader, prSWRfb->u2FrameLength);
            }
        }
    }
    }
#endif


    /* indicate PM module for the received of beacon, if it is the 1st time after connected */
    if (prAdapter->fgBeaconReceivedAfterConnected == FALSE) {
        P_BSS_INFO_T prBssInfo = &prAdapter->rBssInfo;
        P_PM_INFO_T prPmInfo = &prAdapter->rPmInfo;

        if ((prAdapter->eConnectionState == MEDIA_STATE_CONNECTED) &&
            /*(prBssInfo->eBSSType == BSS_TYPE_INFRASTRUCTURE) &&*/
            ((prWLANHdr->u2FrameCtrl & MASK_FC_SUBTYPE) == MAC_FRAME_BEACON) &&
            EQUAL_MAC_ADDR(prBssInfo->aucBSSID, prBSSDesc->aucBSSID)) {

            /* Update DTIM period store in BSS Info, which is updated in joinComplete() */
            prBssInfo->ucDtimPeriod = prBSSDesc->ucDTIMPeriod;

            /* inidcate PM module for the connection status */
            pmFsmRunEventOnConnect(prAdapter,
                                   prBssInfo->u2AssocId,
                                   prBssInfo->u2BeaconInterval,
                                   prBssInfo->ucDtimPeriod,
                                   prBssInfo->u2ATIMWindow);

            prAdapter->fgBeaconReceivedAfterConnected = TRUE;

            ARB_CANCEL_TIMER(prAdapter,
                             prPmInfo->rWaitBeaconWatchdogTimer);

        }
    }

    /* This is to ensure at least one beacon is received after beacon lost event (for TSF sync) */
    if (prAdapter->fgWaitOneBeaconForTsfRecovery) {
        P_BSS_INFO_T prBssInfo = &prAdapter->rBssInfo;
        P_PM_INFO_T prPmInfo = &prAdapter->rPmInfo;

        if (((prWLANHdr->u2FrameCtrl & MASK_FC_SUBTYPE) == MAC_FRAME_BEACON) &&
            EQUAL_MAC_ADDR(prBssInfo->aucBSSID, prBSSDesc->aucBSSID)) {

            prAdapter->fgWaitOneBeaconForTsfRecovery = FALSE;

            ARB_CANCEL_TIMER(prAdapter, prPmInfo->rWaitBeaconWatchdogTimer);
        }
    }

#if CFG_WORKAROUND_BG_SSID_SCAN_DONE
    if (IS_ARB_IN_BG_SSID_SCAN_STATE(prAdapter)) {
        P_BG_SCAN_SSID_CANDIDATE_T prBgSsidCandidate;
        UINT_8 i;

        prBgSsidCandidate = &prAdapter->rScanInfo.rScanConfig.rBgScanCfg.rScanCandidate;

        /* Check SSID under BG SSID SCAN state, and signal SCAN DONE interrupt when SSID is matched
        */
        for (i = 0; i < prBgSsidCandidate->ucNumHwSsidScanEntry; i++) {

            if (prBgSsidCandidate->arHwSsidScanEntry[i].u4SsidLen == prBSSDesc->ucSSIDLen) {

                if (!kalMemCmp(prBSSDesc->aucSSID,
                               prBgSsidCandidate->arHwSsidScanEntry[i].aucSsid,
                               prBgSsidCandidate->arHwSsidScanEntry[i].u4SsidLen)) {

                    NIC_ADD_INT_SCAN_DONE_EVENT(prAdapter);
                    break;
                }
            }
        }
    }
#endif


#if (CFG_DBG_BEACON_RCPI_MEASUREMENT || CFG_LP_PATTERN_SEARCH_SLT)
    {
    P_BSS_INFO_T prBssInfo = &prAdapter->rBssInfo;
    if (EQUAL_MAC_ADDR(prBssInfo->aucBSSID, prBSSDesc->aucBSSID)) {
        rxBcnRcpiMeasure(prAdapter, prSWRfb);
    }
    }
#endif

    return;

} /* end of scanProcessBeaconAndProbeResp() */


/*----------------------------------------------------------------------------*/
/*!
* \brief Compose the ProbeReq Frame.
*
* \param[in] prAdapter          Pointer to the Adapter structure.
* \param[in] pucBuffer          Pointer to the frame buffer.
* \param[in] pucDesiredSsid     Pointer to the SSID.
* \param[in] u4DesiredSsidLen   Length of the SSID.
* \param[out] pu4WlanHeaderLen  Length of WLAN header after compose.
* \param[out] pu4WlanBodyLen    Length of WLAN body after compose.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ VOID
scanComposeProbeReqFrame (
    IN P_ADAPTER_T  prAdapter,
    IN PUINT_8      pucBuffer,
    IN PUINT_8      pucDesiredSsid,
    IN UINT_32      u4DesiredSsidLen,
    OUT PUINT_32    pu4WlanHeaderLen,
    OUT PUINT_32    pu4WlanBodyLen
    )
{
    P_WLAN_MAC_MGMT_HEADER_T prMacHeader;
    UINT_8 aucDestAddr[] = BC_MAC_ADDR;
    UINT_8 aucBSSID[] = BC_BSSID;
    UINT_8 aucAllSupportedRates[RATE_NUM] = {0};
    UINT_8 ucAllSupportedRatesLen;
    UINT_8 ucSupRatesLen;
    UINT_8 ucExtSupRatesLen;

    PUINT_8 pucFrameBody;
    UINT_32 u4FrameBodyLen;
    UINT_16 u2FrameCtrl = MAC_FRAME_PROBE_REQ;

    DEBUGFUNC("scanComposeProbeReqFrame");


    ASSERT(prAdapter);
    ASSERT(pucBuffer);
    ASSERT(pu4WlanHeaderLen);
    ASSERT(pu4WlanBodyLen);
    prMacHeader = (P_WLAN_MAC_MGMT_HEADER_T)pucBuffer;


    //4 <1> Compose the frame header of the (Re)Association Request  frame.
    /* Fill the Frame Control field. */
    WLAN_SET_FIELD_16(&prMacHeader->u2FrameCtrl, u2FrameCtrl);

    /* Fill the DA field with broadcast address. */
    COPY_MAC_ADDR(prMacHeader->aucDestAddr, aucDestAddr);

    /* Fill the SA field. */
    COPY_MAC_ADDR(prMacHeader->aucSrcAddr, prAdapter->aucMacAddress);

    /* Fill the BSSID field with the desired BSSID. */
    COPY_MAC_ADDR(prMacHeader->aucBSSID, aucBSSID);

    /* Clear the SEQ/FRAG_NO field(HW won't overide the FRAG_NO, so we need to clear it). */
    prMacHeader->u2SeqCtrl = 0;


    //4 <2> Update the MAC header/body length.
    /* Set the MAC header length. */
    *pu4WlanHeaderLen = WLAN_MAC_MGMT_HEADER_LEN;
    u4FrameBodyLen = 0;


    /* Compose the frame body of the Probe Request frame. */
    pucFrameBody = pucBuffer + WLAN_MAC_MGMT_HEADER_LEN;

    /* Fill the SSID element. */
    SSID_IE(pucFrameBody)->ucId = ELEM_ID_SSID;
    SSID_IE(pucFrameBody)->ucLength = (UINT_8) u4DesiredSsidLen;
    if (u4DesiredSsidLen) {
        ASSERT(pucDesiredSsid);
        kalMemCopy(SSID_IE(pucFrameBody)->aucSSID, pucDesiredSsid, u4DesiredSsidLen);
    }
    pucFrameBody += ELEM_HDR_LEN + u4DesiredSsidLen;
    u4FrameBodyLen += ELEM_HDR_LEN + u4DesiredSsidLen;


    /* TODO(Kevin): Maybe we can put the aucSupportedRates in SCAN_INFO */
    rateGetDataRatesFromRateSet(rPhyAttributes[prAdapter->eCurrentPhyType].u2SupportedRateSet,
                                0x0, /*(UINT_16)NULL*/
                                aucAllSupportedRates,
                                &ucAllSupportedRatesLen);


    ucSupRatesLen = ((ucAllSupportedRatesLen > ELEM_MAX_LEN_SUP_RATES) ?
                     ELEM_MAX_LEN_SUP_RATES : ucAllSupportedRatesLen);

    ucExtSupRatesLen = ucAllSupportedRatesLen - ucSupRatesLen;

    /* Fill the Supported Rates element. */
    if (ucSupRatesLen) {
        SUP_RATES_IE(pucFrameBody)->ucId = ELEM_ID_SUP_RATES;
        SUP_RATES_IE(pucFrameBody)->ucLength = ucSupRatesLen;
        kalMemCopy(SUP_RATES_IE(pucFrameBody)->aucSupportedRates,
                   aucAllSupportedRates,
                   ucSupRatesLen);

        pucFrameBody += ELEM_HDR_LEN + ucSupRatesLen;
        u4FrameBodyLen += ELEM_HDR_LEN + ucSupRatesLen;
    }

    /* Fill the Extended Supported Rates element. */
    if (ucExtSupRatesLen) {

        EXT_SUP_RATES_IE(pucFrameBody)->ucId = ELEM_ID_EXTENDED_SUP_RATES;
        EXT_SUP_RATES_IE(pucFrameBody)->ucLength = ucExtSupRatesLen;

        kalMemCopy(EXT_SUP_RATES_IE(pucFrameBody)->aucExtSupportedRates,
                   &aucAllSupportedRates[ucSupRatesLen],
                   ucExtSupRatesLen);

        pucFrameBody += ELEM_HDR_LEN + ucExtSupRatesLen;
        u4FrameBodyLen += ELEM_HDR_LEN + ucExtSupRatesLen;
    }

    *pu4WlanBodyLen = u4FrameBodyLen;

    return;
} /* end of scanComposeProbeReqFrame() */


/*----------------------------------------------------------------------------*/
/*!
* \brief Send the ProbeReq Frame
*
* \param[in] prAdapter                  Pointer to the Adapter structure.
* \param[in] pucSsid                    Pointer to the SSID
* \param[in] u4SsidLen                  Length of the SSID.
* \param[in] ucNumOfPrbReq              Number of ProbeReq frames.
* \param[in] ucNumOfSpecifiedSsidPrbReq Number of ProbeReq frames with specified SSID.
*
* \retval WLAN_STATUS_RESOURCES         No available resources to send frame.
* \retval WLAN_STATUS_FAILURE           Unable to send frame(Bus access fail).
* \retval WLAN_STATUS_PENDING           Frame is in TX FIFO or TX SendWaitQueue.
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
scanSendProbeReqFrames (
    IN P_ADAPTER_T prAdapter,
    IN PUINT_8     pucSsid,
    IN UINT_32     u4SsidLen,
    IN UINT_8      ucNumOfPrbReq,
    IN UINT_8      ucNumOfSpecifiedSsidPrbReq
    )
{
    P_MSDU_INFO_T prMsduInfo;
    P_MGT_PACKET_T prMgtPacket;
    UINT_32 u4WlanHeaderLen;
    UINT_32 u4WlanBodyLen;
    UINT_16 u2EstimatedFrameLen;
    UINT_32 i;
    WLAN_STATUS rStatus = WLAN_STATUS_PENDING;

    DEBUGFUNC("scanSendProbeReqFrames");


    ASSERT(prAdapter);
    if (u4SsidLen) {
        ASSERT(pucSsid);
    }

    DBGLOG(SCAN, INFO, ("ucNumOfPrbReq = %d, ucNumOfSpecifiedSsidPrbReq = %d\n",
        ucNumOfPrbReq, ucNumOfSpecifiedSsidPrbReq));

    ASSERT(ucNumOfPrbReq);

    for (i = 0; i < ucNumOfPrbReq; i++) {
        /* Attempt to allocate a buffer to compose a Probe Request frame. */

        //4 <1> Allocate MSDU_INFO_T
        prMsduInfo = nicTxAllocMsduInfo(prAdapter, TCM);
        if (prMsduInfo == (P_MSDU_INFO_T)NULL) {
#if DBG
            if (i == 0) {
                DBGLOG(SCAN, WARN, ("No buffer to send Probe Req\n"));
            }
            else {
                DBGLOG(SCAN, WARN, ("Not enough buffers to send Probe Req\n"));
            }
#endif
            return WLAN_STATUS_RESOURCES;
        }

        //4 <2> Allocate Frame Buffer (in MGT_PACKET_T) for (Re)Association Frame
        u2EstimatedFrameLen = WLAN_MAC_MGMT_HEADER_LEN + \
                              (ELEM_HDR_LEN + ELEM_MAX_LEN_SSID) + \
                              (ELEM_HDR_LEN + ELEM_MAX_LEN_SUP_RATES) + \
                              /* TODO(Kevin): Request IE */
                              (ELEM_HDR_LEN + (RATE_NUM - ELEM_MAX_LEN_SUP_RATES));

        prMgtPacket = mgtBufAllocateMgtPacket(prAdapter, (UINT_32)u2EstimatedFrameLen);
        if (prMgtPacket == (P_MGT_PACKET_T)NULL) {
            DBGLOG(SCAN, WARN, ("No buffer for Probe Request frame\n"));
            nicTxReturnMsduInfo(prAdapter, prMsduInfo);
            return WLAN_STATUS_RESOURCES;
        }

        //4 <3> Compose Association Request frame in MGT_PACKET_T.
        /* Compose the Probe Request frame. We send the frame with the
         * user-specific SSID first to solve the hidden SSID problem, and
         * send left frames with Broadcast(Wildcard) SSID.
         */
        if (ucNumOfSpecifiedSsidPrbReq > i) {
            scanComposeProbeReqFrame(prAdapter,
                                     MGT_PACKET_GET_BUFFER(prMgtPacket),
                                     pucSsid,
                                     u4SsidLen,
                                     &u4WlanHeaderLen,
                                     &u4WlanBodyLen);
        }
        else {
            UINT_8 aucBcSsid[] = BC_SSID;

            scanComposeProbeReqFrame(prAdapter,
                                     MGT_PACKET_GET_BUFFER(prMgtPacket),
                                     &aucBcSsid[0],
                                     BC_SSID_LEN,
                                     &u4WlanHeaderLen,
                                     &u4WlanBodyLen);
        }

        //4 <4> Update the frame length to the packet descriptor (MGT_PACKET_T).
        mgtPacketPut(prMgtPacket, (u4WlanHeaderLen + u4WlanBodyLen));

        //4 <5> Update information in MSDU_INFO_T for TX Module.
        MSDU_INFO_OBJ_INIT(prMsduInfo, \
                           TRUE, \
                           TRUE, \
                           (PVOID)prMgtPacket, \
                           0, \
                           TXQ_TCM, \
                           (UINT_8)u4WlanHeaderLen, \
                           (UINT_16)u4WlanBodyLen, \
                           (UINT_8)(MSDU_INFO_CTRL_FLAG_SPECIFY_AC | \
                                    MSDU_INFO_CTRL_FLAG_BASIC_RATE | \
                                    MSDU_INFO_CTRL_FLAG_LIFETIME_NEVER_EXPIRE), \
                           (PFN_TX_DONE_HANDLER)0, \
                           (OS_SYSTIME)NULL, \
                           NULL \
                           );

        //4 <6> Inform ARB to send this Authentication Request frame.
        if ((rStatus = arbFsmRunEventTxMmpdu(prAdapter, prMsduInfo)) != WLAN_STATUS_PENDING) {

            if(rStatus != WLAN_STATUS_SUCCESS) {
                mgtBufFreeMgtPacket(prAdapter, prMgtPacket);

                nicTxReturnMsduInfo(prAdapter, prMsduInfo);

                rStatus = WLAN_STATUS_FAILURE;

                break; /* Kevin: Break the outer FOR statement once we encounter ERROR. */
            }

        }
    }

    return rStatus;
} /* end of scanSendProbeReqFrames() */



