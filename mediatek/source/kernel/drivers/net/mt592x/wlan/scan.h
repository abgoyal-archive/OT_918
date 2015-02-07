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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/scan.h#2 $
*/

/*! \file   "scan.h"
    \brief  In this file we define the data structure used by scan.

    The SCAN_INFO_T contains all the parameters, FSM State variable and SCAN
    results for SCAN Module.
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
** $Log: scan.h $
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\38 2009-04-03 00:07:07 GMT mtk01461
**  Extend the life cycle of SCAN result from 5 -> 10 sec, and also add new remove policy - oldest hidden & smart weakest
**  \main\maintrunk.MT5921\37 2008-10-13 10:20:11 GMT mtk01461
**  Remove define of minimum life time
**  \main\maintrunk.MT5921\36 2008-09-02 10:37:13 GMT mtk01461
**  Update driver for code review
**  \main\maintrunk.MT5921\35 2008-08-20 17:46:40 GMT mtk01084
**  Modify for coding rule conformance
**  \main\maintrunk.MT5921\34 2008-08-12 09:55:15 GMT mtk01461
**  Update for Driver Review - MAXIMUM_OPERATION_CHANNEL_LIST
**  \main\maintrunk.MT5921\33 2008-08-04 16:50:58 GMT mtk01461
**  Enable Link List ASSERT during QA debug
**  \main\maintrunk.MT5921\32 2008-07-01 23:29:18 GMT mtk01084
**  Workaround for the case that the scan is continuously blocked in scan initial phase
**  \main\maintrunk.MT5921\31 2008-07-01 20:04:54 GMT mtk01084
**  modify the scan method name
**  \main\maintrunk.MT5921\30 2008-07-01 10:54:25 GMT mtk01084
**  remove un-used scan profile
**  \main\maintrunk.MT5921\29 2008-05-03 13:08:30 GMT mtk01461
**  Update SCAN Result according to TA & BSSID instead of BSSID only
**  \main\maintrunk.MT5921\28 2008-04-17 22:07:59 GMT mtk01084
**  modify send probe request function
**  \main\maintrunk.MT5921\27 2008-03-29 13:50:19 GMT mtk01461
**  Add MAGIC GUID for Link List
**  \main\maintrunk.MT5921\26 2008-03-23 22:48:51 GMT mtk01461
**  add function declaration
**  \main\maintrunk.MT5921\25 2008-03-20 00:01:50 GMT mtk01461
**  Add comment and fix typo
**  \main\maintrunk.MT5921\24 2008-03-13 15:45:51 GMT mtk01084
**  modify structure for BG SSID scan
**  \main\maintrunk.MT5921\23 2008-03-13 15:31:44 GMT mtk01461
**  Refine the relationship between SCAN result and STA record, lifetime, aging policy etc
**  \main\maintrunk.MT5921\22 2008-03-13 14:27:47 GMT mtk01461
**  Revise SCAN call back function prototype for Roaming Module
**  \main\maintrunk.MT5921\21 2008-03-11 13:32:49 GMT mtk01084
**  remove un-used lines
**  \main\maintrunk.MT5921\20 2008-02-27 12:12:10 GMT mtk01461
**  Revise the lifetime of SCAN result to 5 sec
**  \main\maintrunk.MT5921\19 2008-02-18 17:40:21 GMT mtk01084
**  modify structure
**  \main\maintrunk.MT5921\18 2008-02-18 17:38:30 GMT mtk01084
**  modify structure naming
**  \main\maintrunk.MT5921\17 2007-12-11 00:07:54 GMT mtk01461
**  Refine SCAN Remove Policy - definitions
**  \main\maintrunk.MT5921\16 2007-12-08 22:28:44 GMT mtk01084
**  add comment
**  \main\maintrunk.MT5921\15 2007-11-26 19:26:02 GMT mtk01461
**  Unify SCAN
**  \main\maintrunk.MT5921\14 2007-11-13 17:57:36 GMT mtk01084
**  change function name scanProcessBcnAndPrbRspFrame()
**  \main\maintrunk.MT5921\13 2007-11-12 16:11:29 GMT mtk01084
**  modify scan dwell time length from 16 bit to 8 bit
**  \main\maintrunk.MT5921\12 2007-11-01 14:52:43 GMT mtk01084
**  modify variable naming of the u4ScanDwellTimeMax to u4ScanDwellTimeExt
**  \main\maintrunk.MT5921\11 2007-10-25 21:34:15 GMT mtk01084
**  update BG SSID scan functions
**  \main\maintrunk.MT5921\10 2007-10-25 17:59:23 GMT mtk01461
**  Add VOIP SCAN & Refine Roaming
**
*/

#ifndef _SCAN_H
#define _SCAN_H

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
#define BSS_DESC_TIMEOUT_SEC                5 // Second, used by Roaming and AdHoc, to get the newest as could as we can.
#define BSS_DESC_REMOVE_TIMEOUT_SEC         10 // Second.

#define BSS_DESC_GUID                       0x5A5A1461 /* Magic debug values */
#if DBG || BUILD_QA_DBG
#define BSS_DESC_SET_GUID(_prBssDesc)       {(_prBssDesc)->u4Magic = BSS_DESC_GUID;}
#define BSS_DESC_CHK_GUID(_prBssDesc)       ASSERT((_prBssDesc)->u4Magic == BSS_DESC_GUID)
#else
#define BSS_DESC_SET_GUID(_prBssDesc)
#define BSS_DESC_CHK_GUID(_prBssDesc)
#endif /* DBG || BUILD_QA_DBG */

#define SCAN_RM_POLICY_EXCLUDE_CONNECTED    BIT(0) // Remove SCAN result except the connected one.
#define SCAN_RM_POLICY_TIMEOUT              BIT(1) // Remove the timeout one
#define SCAN_RM_POLICY_OLDEST               BIT(2) // Remove the oldest one
#define SCAN_RM_POLICY_WEAKEST              BIT(3) // Remove the weakest rssi
#define SCAN_RM_POLICY_OLDEST_HIDDEN        BIT(4) // Remove the oldest one with hidden ssid
#define SCAN_RM_POLICY_SMART_WEAKEST        BIT(5) /* If there are more than half BSS which has the 
                                                    * same ssid as connection setting, remove the weakest one from them
                                                    * Else remove the weakest one.
                                                    */
#define SCAN_RM_POLICY_ENTIRE               BIT(6) // Remove entire SCAN result


/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/
typedef VOID (*PFN_SCAN_DONE_HANDLER)(IN P_ADAPTER_T,
                                      IN WLAN_STATUS);

typedef enum _ENUM_SCAN_TYPE_T
{
    SCAN_TYPE_PASSIVE_SCAN = 0,
    SCAN_TYPE_ACTIVE_SCAN,
    SCAN_TYPE_NUM
} ENUM_SCAN_TYPE_T, *P_ENUM_SCAN_TYPE_T;

typedef enum _ENUM_SCAN_METHOD_T
{
    SCAN_METHOD_FULL_SCAN = 0,
    SCAN_METHOD_ONLINE_SCAN,
    SCAN_METHOD_VOIP_ONLINE_SCAN,
    SCAN_METHOD_NUM
} ENUM_SCAN_METHOD_T, *P_ENUM_SCAN_METHOD_T;


struct _SCAN_REQ_CONFIG_T {
    ENUM_SCAN_METHOD_T      eScanMethod;

    ENUM_SCAN_TYPE_T        eScanType;

    PARAM_SSID_T            rSpecifiedSsid;

    RF_CHANNEL_INFO_T       arChnlInfoList[32];
    UINT_8                  ucNumOfScanChnl;

    UINT_8                  ucChnlDwellTimeMin;
    UINT_8                  ucChnlDwellTimeExt;

    UINT_8                  ucNumOfPrbReq;
    UINT_8                  ucNumOfSpecifiedSsidPrbReq;

    PFN_SCAN_DONE_HANDLER   pfScanDoneHandler;
};

typedef struct _BG_SCAN_SSID_CANDIDATE_T {
    UINT_8          ucNumHwSsidScanEntry;
    PARAM_SSID_T  arHwSsidScanEntry[16];
} BG_SCAN_SSID_CANDIDATE_T, *P_BG_SCAN_SSID_CANDIDATE_T;

typedef struct _BG_SCAN_CONFIG_T {
    BG_SCAN_SSID_CANDIDATE_T    rScanCandidate;
    UINT_16                     u2BaseWakePeriod;
    UINT_8                      ucBgScanStepOfWakePeriod;
    UINT_8                      ucBgScanMinRcpiThr;
    BOOLEAN                     fgIsFromUserSetting;
} BG_SCAN_CONFIG_T, *P_BG_SCAN_CONFIG_T;


typedef struct _SCAN_CONFIG_T {
    ENUM_SCAN_METHOD_T      eScanMethod;

    ENUM_SCAN_TYPE_T        eScanType;
    RF_CHANNEL_INFO_T       rOrgChnlInfo;
    UINT_16                 u2RxFifoThreshold;
    PARAM_SSID_T            rSpecifiedSsid;
    UINT_8                  ucNumOfPrbReq;
    UINT_8                  ucNumOfSpecifiedSsidPrbReq;
    UINT_8                  ucChnlDwellTimeMin;
    UINT_8                  ucChnlDwellTimeExt;
    BOOLEAN                 fgToHonorServicePeriod;
    BOOLEAN                 fgToEnableTriggerEvent;
    UINT_8                  ucNumOfScanChnl;
    RF_CHANNEL_INFO_T       arChnlInfoList[MAXIMUM_OPERATION_CHANNEL_LIST];

    UINT_8                  ucTotalScanChannelCount; /* For VOIP SCAN */
    UINT_8                  ucFinishedChannelCount;
    UINT_8                  ucNumOfPassiveScanInVoIP;


    BG_SCAN_CONFIG_T        rBgScanCfg;

    PFN_SCAN_DONE_HANDLER   pfScanDoneHandler;
} SCAN_CONFIG_T, *P_SCAN_CONFIG_T;


typedef struct _SCAN_INFO_T {
    UINT_32             u4BSSCachedSize;
    PUINT_8             pucBSSCached;

    ENUM_SCAN_STATE_T   eCurrentState;
    ENUM_HW_SCAN_MODE_T eCurrentHwScanMode;

    UINT_8              ucScanBlockInInitialPhaseCount;
    BOOLEAN             fgIsScanReqProceeding;

    SCAN_CONFIG_T       rScanConfig;

    SCAN_STATUS_T       rScanStatus;

    BACKUP_REGISTER_VALUE_T rBkupRegValue;

    LINK_T              rBSSDescList;

    LINK_T              rFreeBSSDescList;

    TIMER_T             rScanCheckForHangTimer;

    TIMER_T             rPartialScanTimer;

    OS_SYSTIME          rScanCompletedTime;

} SCAN_INFO_T, *P_SCAN_INFO_T;

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
VOID
scanInitialize (
    IN P_ADAPTER_T prAdapter
    );

P_BSS_DESC_T
scanSearchBssDescByPolicy(
    IN P_ADAPTER_T prAdapter
    );

P_BSS_DESC_T
scanSearchBssDescByBssid (
    IN P_ADAPTER_T prAdapter,
    IN UINT_8 aucBSSID[]
    );

P_BSS_DESC_T
scanSearchBssDescOrAddIfNotExist (
    IN P_ADAPTER_T prAdapter,
    IN ENUM_BSS_TYPE_T eBSSType,
    IN UINT_8 aucBSSID[],
    IN UINT_8 aucSrcAddr[]
    );

VOID
scanRemoveBssDescsByPolicy (
    IN P_ADAPTER_T prAdapter,
    IN UINT_32 u4RemovePolicy
    );

VOID
scanRemoveBssDescByBssid (
    IN P_ADAPTER_T prAdapter,
    IN UINT_8 aucBSSID[]
    );

VOID
scanRemoveConnectionFlagOfBssDescByBssid (
    IN P_ADAPTER_T prAdapter,
    IN UINT_8 aucBSSID[]
    );

VOID
scanProcessBeaconAndProbeResp (
    IN P_ADAPTER_T prAdapter,
    IN P_SW_RFB_T prSWRfb
    );

WLAN_STATUS
scanSendProbeReqFrames (
    IN P_ADAPTER_T prAdapter,
    IN PUINT_8     pucSsid,
    IN UINT_32     u4SsidLen,
    IN UINT_8      ucNumOfPrbReq,
    IN UINT_8      ucNumOfSpecifiedSsidPrbReq
    );
#endif /* _SCAN_H */

