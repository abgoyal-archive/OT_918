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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/pwr_mgt_fsm.h#2 $
*/

/*! \file   "pwr_mgt_fsm.h"
    \brief  In this file we define the STATE and EVENT for Power Management FSM.

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
** $Log: pwr_mgt_fsm.h $
 *
 * 07 07 2010 renbang.jiang
 * [ALPS00121568][WiFi][Need Resolve]AP disconnect/reconnect automatically all the time 
 * .
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\79 2009-07-13 14:47:34 GMT mtk01090
**  Correct watchdog timeout value calculation.
**  Ignore DTIM Period and wake up every N * TBTT if wake up interval is too large to let network application run smoothly.
**  Switch back to CAM mode for this AP connection if LP has problems for ship build.
**  \main\maintrunk.MT5921\78 2009-05-14 20:42:11 GMT mtk01104
**  Update function prototype of pmFsmInit()
**  \main\maintrunk.MT5921\77 2009-04-02 16:47:26 GMT mtk01084
**  fix issue that AP cannot report disconnect, when conti. polling is enabled, and BT set to ACL
**  \main\maintrunk.MT5921\76 2009-02-25 16:10:53 GMT mtk01084
**  handle beacon timeout when continuous 10 HW TX excessive retry fail
**  \main\maintrunk.MT5921\75 2009-02-16 17:56:00 GMT mtk01084
**  modify for controlling beacon lost detection function
**  \main\maintrunk.MT5921\74 2009-02-05 21:42:17 GMT mtk01084
**  PS-related parameters modification for BT/WiFi coexistence optimization
**  \main\maintrunk.MT5921\73 2009-02-02 14:26:33 GMT mtk01084
**  modify continuous polling mechanism, with not to do extra poll when no WiFi downlink traffic
**  \main\maintrunk.MT5921\72 2009-01-22 12:00:11 GMT mtk01084
**  modify the PSP-fast wakeup criterion by continuous RX in different wakeup intervals
**  \main\maintrunk.MT5921\71 2009-01-19 20:13:35 GMT mtk01084
**  modify PSP-fast parameter
**  \main\maintrunk.MT5921\70 2009-01-18 20:15:00 GMT mtk01084
**  modify the PSP-fast threshold number
**  \main\maintrunk.MT5921\69 2009-01-16 15:45:32 GMT mtk01084
**  modify the PSP-FAST mode decision operation to switch PS mode from Active to PS
**  \main\maintrunk.MT5921\68 2008-10-30 09:45:56 GMT mtk01084
**  modify for preventing Linux compiler error
**  \main\maintrunk.MT5921\67 2008-10-27 14:24:43 GMT mtk01084
**  supporting continuous polling mode
**  \main\maintrunk.MT5921\66 2008-09-08 11:24:54 GMT mtk01084
**  add coments
**  \main\maintrunk.MT5921\65 2008-09-03 14:15:14 GMT mtk01084
**  add LP instruction related variables
**  \main\maintrunk.MT5921\64 2008-08-11 21:33:40 GMT mtk01084
**  modify for coding rules conformance
**  \main\maintrunk.MT5921\63 2008-07-14 11:22:49 GMT mtk01084
**  add new variable to record the PS connection
**  \main\maintrunk.MT5921\62 2008-07-01 10:54:09 GMT mtk01084
**  add variable to record target/ current PS bit setting
**  \main\maintrunk.MT5921\61 2008-06-26 21:09:07 GMT mtk01084
**  add WMM-PS test only variables
**  \main\maintrunk.MT5921\60 2008-06-18 20:44:46 GMT mtk01084
**  revise beacon timeout handling procedure
**  \main\maintrunk.MT5921\59 2008-05-30 14:30:49 GMT mtk01461
**  Fix compile error
**  \main\maintrunk.MT5921\58 2008-05-29 14:15:02 GMT mtk01084
**  move the variable to connection setting structure
**  \main\maintrunk.MT5921\57 2008-05-21 21:36:50 GMT mtk01084
**  fine-tuning for the DEFAULT_ACTIVE_MODE_SWITCH_INTERVAL (from 500 to 1000ms)
**  \main\maintrunk.MT5921\56 2008-05-20 10:42:58 GMT mtk01084
**  1. extend the maximum timeout from 80 to 200 TU
**  2. delete scan done event on the procedure disabling BG SSID scan
**  \main\maintrunk.MT5921\55 2008-05-12 15:57:23 GMT mtk01084
**  add rWaitBeaconWatchdogTimer
**  \main\maintrunk.MT5921\54 2008-05-12 13:36:50 GMT mtk01084
**  add ACPI D0~D3 related define
**  \main\maintrunk.MT5921\53 2008-04-28 17:19:48 GMT mtk01084
**  modify PM control handling within BG SSID scan
**  \main\maintrunk.MT5921\52 2008-04-24 12:02:06 GMT mtk01084
**  fine tuning for the min/max timout value for passing WHQL 2c.sendRecv1
**  \main\maintrunk.MT5921\51 2008-04-20 20:30:22 GMT mtk01084
**  tune TX/RX threshold under PSP-fast and VoIP
**  \main\maintrunk.MT5921\50 2008-04-16 23:29:39 GMT mtk01084
**  modify the parameters used under PSP-fast mode,
**  for let it easier to keep it stay in ACTIVE mode under high traffic throughput
**  \main\maintrunk.MT5921\49 2008-04-16 15:21:57 GMT mtk01461
**  Change Default Beacon timeout count for Ad-Hoc, and add GuardTime for SW detection of Beacon Timeout false alarm
**  \main\maintrunk.MT5921\48 2008-04-10 20:08:47 GMT mtk01084
**  Add TX throughput into PS mode switching criterion under PSP-fast mode.
**  \main\maintrunk.MT5921\47 2008-04-10 11:47:42 GMT mtk01084
**  \main\maintrunk.MT5921\46 2008-03-26 23:50:23 GMT mtk01084
**  use DWORD size variable to record IP address
**  \main\maintrunk.MT5921\45 2008-03-26 15:34:18 GMT mtk01461
**  Rename the FUNC_CALLBACK_PS to avoid compile warnning
**  \main\maintrunk.MT5921\44 2008-03-25 22:41:22 GMT mtk01084
**  modify send null frame function
**  \main\maintrunk.MT5921\43 2008-03-25 21:45:27 GMT mtk01084
**  modify the callback function prototype on change PS mode
**  \main\maintrunk.MT5921\42 2008-03-20 11:49:01 GMT mtk01084
**  modify the set IP address arguments
**  \main\maintrunk.MT5921\41 2008-03-18 11:54:44 GMT mtk01084
**  remove parts of the define to wlan_lib.h for shared use with GL
**  \main\maintrunk.MT5921\40 2008-03-14 19:11:11 GMT mtk01084
**  modify PSP-fast mode
**  \main\maintrunk.MT5921\39 2008-03-11 22:40:35 GMT mtk01084
**  1. change the PSP-fast parameter, and
**  2. change pmIndicateUcDataFrameReceived() input arguments
**  \main\maintrunk.MT5921\38 2008-03-11 13:32:39 GMT mtk01084
**  modify arbFsmRunEventScanRequest() function argument
**  \main\maintrunk.MT5921\37 2008-03-06 22:23:12 GMT mtk01084
**  modify the PM related function name
**  \main\maintrunk.MT5921\36 2008-02-18 17:59:31 GMT mtk01084
**  add more comments
**  \main\maintrunk.MT5921\35 2008-02-15 19:19:32 GMT mtk01084
**  revise function name
**  \main\maintrunk.MT5921\34 2008-01-03 20:50:23 GMT mtk01084
**  modify macro defines
**  \main\maintrunk.MT5921\33 2007-12-25 23:32:46 GMT mtk01084
**  add routine handle scan done or not when own back from BG SSID SCAN state
**  \main\maintrunk.MT5921\32 2007-12-20 15:15:26 GMT mtk01084
**  update beacon timeout related configuration
**  \main\maintrunk.MT5921\31 2007-12-16 19:15:27 GMT mtk01084
**  set beacon timeout count to 6 (from 10)
**  \main\maintrunk.MT5921\30 2007-12-10 20:18:34 GMT mtk01084
**  modify disable BG SSID SCAN macro
**  \main\maintrunk.MT5921\29 2007-11-30 20:15:58 GMT mtk01084
**  add new member for pattern search
**  \main\maintrunk.MT5921\28 2007-11-30 19:42:24 GMT mtk01084
**  modify PM control macros
**  \main\maintrunk.MT5921\27 2007-11-27 17:47:48 GMT mtk01084
**  modify to meet its unit
**  \main\maintrunk.MT5921\26 2007-11-22 22:31:30 GMT mtk01084
**  modify definitions to send NULL frame
**  \main\maintrunk.MT5921\25 2007-11-12 20:32:06 GMT mtk01084
**  modify function name pmFsmRunEventOnDisconnect() to pmFsmRunEventAbort()
**  \main\maintrunk.MT5921\24 2007-11-09 12:46:38 GMT mtk01084
**  update members for FAST PSP
**  \main\maintrunk.MT5921\23 2007-11-08 14:11:26 GMT mtk01084
**  remove duplicated lines
**  \main\maintrunk.MT5921\22 2007-11-08 13:55:31 GMT mtk01084
**  modify PS profiles related definition
**  \main\maintrunk.MT5921\21 2007-11-02 00:52:08 GMT mtk01461
**  Unify TX Path for Normal and IBSS Power Save + IBSS neighbor learning
**  \main\maintrunk.MT5921\20 2007-11-01 16:45:32 GMT mtk01084
**  update for LP IOT test for beacon timeout function
**  \main\maintrunk.MT5921\19 2007-11-01 14:52:28 GMT mtk01084
**  modify profile setting
**  \main\maintrunk.MT5921\18 2007-10-31 16:10:54 GMT mtk01084
**  add lines to check if it is under ATIM window
**  \main\maintrunk.MT5921\17 2007-10-30 19:25:32 GMT mtk01084
**  modify argument to create IBSS
**  \main\maintrunk.MT5921\16 2007-10-30 09:25:21 GMT mtk01425
**  1. Fix compiling error
**  \main\maintrunk.MT5921\15 2007-10-29 10:43:07 GMT mtk01084
**  enable BG SSID Scan function
**  \main\maintrunk.MT5921\14 2007-10-25 21:26:33 GMT mtk01084
**  add BG scan/ ACPI related code
**  \main\maintrunk.MT5921\13 2007-10-25 17:59:21 GMT mtk01461
**  Add VOIP SCAN & Refine Roaming
** Revision 1.2  2007/07/12 11:02:24  MTK01084
** update macro and structures for PM
**
** Revision 1.1  2007/07/05 14:11:36  MTK01084
** Initial version
**
*/

#ifndef _PM_FSM_H
#define _PM_FSM_H
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

#define BEACON_TIMEOUT_STEP_DOWN_CHECK_INTERVAL 10000  /* in unit of ms */

#define DELAY_ENTER_PS_AFTER_CONNTECTED         5000  /* in unit of ms */

#define DEFAULT_TSF_DRIFT_WINDOW_TU             1

#define BEACON_TIMEOUT_COUNT_ADHOC              15
#define BEACON_TIMEOUT_COUNT_INFRA              10
#define BEACON_TIMEOUT_GUARD_TIME_SEC           1 /* Second */

#define BEACON_MAX_TIMEOUT_VALUE                100
#define BEACON_MIN_TIMEOUT_VALUE                5
#define BEACON_MAX_TIMEOUT_VALID                TRUE
#define BEACON_MIN_TIMEOUT_VALID                TRUE

#define NULL_TIMEOUT_COUNT                      10
#define NULL_MAX_TIMEOUT_VALUE                  10
#define NULL_MIN_TIMEOUT_VALUE                  5
#define NULL_MAX_TIMEOUT_VALID                  TRUE
#define NULL_MIN_TIMEOUT_VALID                  TRUE

#define TIMEOUT_COUNT                           10
#define MAX_TIMEOUT_VALUE                       200//80
#define MIN_TIMEOUT_VALUE                       8
#define MAX_TIMEOUT_VALID                       TRUE
#define MIN_TIMEOUT_VALID                       TRUE

#define DEFAULT_PS_MODE_SWITCH_INTERVAL         100         /* Used under PS mode, decide to switch to Active Mode. (need to > 100) in unit of ms */
#define DEFAULT_ACTIVE_MODE_SWITCH_INTERVAL     3000//500   /* Used under Active mode, decide to switch to PS Mode.(need to > 100) in unit of ms */
#define DEFAULT_FAST_ACTIVE_MEASURE_INTERVAL    3000        /* Used under Active mode, and use it as the window for counting TR packets number */

#define DEFAULT_PSP_SWITCH_TO_PS_RX_THRESHOLD   5       /* Used under Active mode, decide to switch to PS Mode. Unit: Num of Rx UC pkts */
#define DEFAULT_PSP_SWITCH_TO_ACT_RX_THRESHOLD  3       /* Used under PS mode, decide to switch to Active Mode. Unit: Num of Rx UC pkts per 100ms */
#define DEFAULT_PSP_SWITCH_TO_PS_TX_THRESHOLD   5       /* Used under Active mode, decide to switch to PS Mode. Unit: Num of TX data pkts */
#define DEFAULT_PSP_SWITCH_TO_ACT_TX_THRESHOLD  3       /* Used under PS mode, decide to switch to Active Mode. Unit: Num of TX data pkts per 100ms */
#define DEFAULT_PSP_CONSECUTE_RX_SWITCH_TO_ACT  3       /* Used under PS mode, decide to switch to Active Mode. Unit: Num of TX data pkts per 100ms */

#define DEFAULT_PSP_SWITCH_TO_PS_RX_THRESHOLD_VOIP  15  /* (< 2 calls + 5)  Unit: Num of Rx UC pkts per 100ms */
#define DEFAULT_PSP_SWITCH_TO_ACT_RX_THRESHOLD_VOIP 15  /* (> 2 calls + 10) Unit: Num of Rx UC pkts per 100ms */
#define DEFAULT_PSP_SWITCH_TO_PS_TX_THRESHOLD_VOIP  15  /* (< 2 calls + 5)  Unit: Num of TX data pkts per 100ms */
#define DEFAULT_PSP_SWITCH_TO_ACT_TX_THRESHOLD_VOIP 25  /* (> 2 calls + 15) Unit: Num of TX data pkts per 100ms */

#define DEFAULT_MULTIPLE_DTIM_COUNT             1
#define DEFAULT_MULTIPLE_TBTT_COUNT             0
#define DEFAULT_USE_AGING_QOS_NULL              1
#define DEFAULT_AGING_NULL_INTERVAL             30
#define DEFAULT_AGING_NULL_TID                  7
#define DEFAULT_UAPSD_SERVICE_PERIOD_NUM        WMM_MAX_SP_LENGTH_2//WMM_MAX_SP_LENGTH_ALL//0
#define DEFAULT_TRIGGER_THRESHOLD               (1500 / 64) // unit: 64 byte
#define DEFAULT_HW_TX_PACKET_LIFETIME           100

#define DEFAULT_CONTI_POLL_INTV_DURING_STEP_DOWN_MS     500

#define DEFAULT_CONTI_HW_TX_FAIL                5

/* In unit of TU. If DTIM period * beacon interval is larger than this value,
* wake up once every DEFAULT_WORKAROUND_TBTT_COUNT to keep application operating correctly.
*/
#define DEFAULT_DTIM_INTERVAL_THRESHOLD   2000
#define DEFAULT_WORKAROUND_TBTT_COUNT    2

/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/
/*! \brief TX done handler for PS mode change callback */
typedef WLAN_STATUS (*FUNC_CALLBACK_PS)(IN P_ADAPTER_T prAdapter,
                                        IN P_SCAN_REQ_CONFIG_T prScanReqConfig,
                                        IN BOOLEAN fgForceToScanInActiveMode);


#define GET_DLVR_EN_AC_INFO_FROM_APSD_BMP(_bmfgApsdEnAc) \
        (((_bmfgApsdEnAc) >> 4) & BITS(0, 3))

#define GET_TRIG_EN_AC_INFO_FROM_APSD_BMP(_bmfgApsdEnAc) \
        (((_bmfgApsdEnAc) >> 0) & BITS(0, 3))

/* Definition for service period set */
#define SP_BEACON                       BIT(0)
#define SP_BMC                          BIT(1)
#define SP_QOS_CFPOLL                   BIT(2)
#define SP_PS_POLL                      BIT(3)
#define SP_APSD                         BIT(4)
#define SP_ALL                          BITS(0, 4)

#define NUM_OF_MAX_LP_INSTRUCTIONS          8


typedef struct _PM_CONN_SETUP_INFO_T {
    UINT_16     u2AID;
    UINT_16     u2BcnIntv;
    UINT_8      ucDtimPeriod;
    UINT_16     u2AtimWindow;
    BOOLEAN     fgIsUapsdConn;
} PM_CONN_SETUP_INFO_T, *P_PM_CONN_SETUP_INFO_T;

typedef struct _PM_PROFILE_SETUP_INFO_T {
    /* Profile setup */
    UINT_8      ucMultiDtimWake;    /* Wakeup timer for multiple DTIM period */
    UINT_8      ucMultiTbttWake;    /* Wakeup timer for multiple TBTT period */
    UINT_8      ucQoSNullTid;       /* 0~15, includes QoS Null trigger frame and aging NULL */
    UINT_8      bmfgApsdEnAc;       /* b0~3: trigger-en AC0~3. b4~7: delivery-en AC0~3 */
    UINT_8      ucUapsdSp;          /* Number of triggered packets in UAPSD */
    UINT_8      ucTrgThr;           /* Trigger threshold. (unit: 64 byte) */
    UINT_8      ucAgeNullPeriod;    /* (QoS-) Null frame interval to keep connection. (unit: second) */
    BOOLEAN     fgUseAgeQoSNull;    /* Whether to use QoS NULL for aging prevention (1: QoS-NULL, 0: NULL) */
    BOOLEAN     fgAdhocPsCapability;/* Whether to enable IBSS power saving function */
    UINT_16     u2HwTxLifeTime;     /* Packet life time for the HW transmitted packets */

    UINT_16     u2TxThrSwToAct;     /* Unit: Num of TX pkts per 100 ms */
    UINT_16     u2TxThrSwToPs;      /* Unit: Num of TX pkts per 100 ms */
    UINT_16     u2RxThrSwToAct;     /* Unit: Num of Rx UC pkts per 100 ms */
    UINT_16     u2RxThrSwToPs;      /* Unit: Num of Rx UC pkts per 100 ms */
    UINT_16     u2PsModeSwIntv;     /* Interval used under PSP-fast, checking if to enter active mode. Unit: ms */
    UINT_16     u2ActModeSwIntv;    /* Interval used under PSP-fast, checking if to enter PS mode. Unit: ms */

    BOOLEAN     fgBcPtrnSrchEn;     /* BC pattern search function. */
    BOOLEAN     fgMcPtrnSrchEn;     /* MC pattern search function. */
    BOOLEAN     fgUcPtrnSrchEn;     /* UC pattern search function. */

    BOOLEAN     fgBcPtrnMatchRcv;   /* Filter for the matched BC packet. TRUE: black list, FALSE: white list */
    BOOLEAN     fgMcPtrnMatchRcv;   /* Filter for the matched MC packet. TRUE: black list, FALSE: white list */
    BOOLEAN     fgUcPtrnMatchRcv;   /* Filter for the matched UC packet. TRUE: black list, FALSE: white list */

    UINT_16     u2DtimIntvThr;  /* Dtim interval threshold in unit of TU */
    UINT_8      ucWorkaroundTbttCount;  /* Dtim interval threshold in unit of TU */
} PM_PROFILE_SETUP_INFO_T, *P_PM_PROFILE_SETUP_INFO_T;


typedef enum _ENUM_ACPI_STATE_T {
    ACPI_STATE_D0 = 0,
    ACPI_STATE_D1,
    ACPI_STATE_D2,
    ACPI_STATE_D3
} ENUM_ACPI_STATE_T;

typedef enum _ENUM_NULL_STATE_T {
    NULL_STATE_NONE = 0,
    NULL_STATE_SUCCESS,
    NULL_STATE_FAIL
} ENUM_NULL_STATE_T;

typedef enum _ENUM_PM_STATE_T {
    PM_STATE_ACTIVE_MODE = 0,
    PM_STATE_WAIT_POWER_SAVE_READY,
    PM_STATE_WAIT_ACTIVE_READY,
    PM_STATE_POWER_SAVE_AWAKE,
    PM_STATE_POWER_SAVE_DOZE,
    PM_STATE_NUM
} ENUM_PM_STATE_T;

typedef enum _ENUM_PM_BCN_TO_STEPS_T {
    BCN_TO_STEP_0 = 0,
    BCN_TO_STEP_1,
    BCN_TO_STEP_2,
    BCN_TO_STEP_3,
    BCN_TO_STEP_4,
    BCN_TO_STEP_NUM
} ENUM_PM_BCN_TO_STEPS_T;


typedef struct _PM_SLOW_CLOCK_COUNT_T {
    UINT_8 uc32kSlowCount;
    UINT_8 uc32kSlowCount_10;
    UINT_8 uc32kSlowCount_100;
    UINT_8 uc32kSlowCount_1000;
} PM_SLOW_CLOCK_COUNT_T, *P_PM_SLOW_CLOCK_COUNT_T;

typedef struct _PM_FAST_SWITCH_PARAM_T {
    UINT_32 u4TimeSlot;
    UINT_32 u4AccumRxUcPktNum;
    UINT_32 u4AccumTxDataPktNum;
    OS_SYSTIME rLastSwitchTime; /* last time switch to active mode */
    OS_SYSTIME rLastRxUcDataTime;
    UINT_32 u4ConsecutiveRxCount; /* consecutive Rx in STA wakeup intervals */
} PM_FAST_SWITCH_PARAM_T, *P_PM_FAST_SWITCH_PARAM_T;

typedef struct _PM_INFO_T {
    ENUM_PM_STATE_T    eCurrentState;

    FUNC_CALLBACK_PS pfnPsIndication;

    ENUM_PM_BCN_TO_STEPS_T  eBeaconTimeoutTuningStep;

    BOOLEAN         fgContiPollIsStepUp;

    TIMER_T         rContiHwTxFailCheckTimer;

    TIMER_T         rContiPollingCheckTimer;

    TIMER_T         rBeaconTimeoutHandlingTimer;

    TIMER_T         rWaitBeaconWatchdogTimer;

    TIMER_T         rPmOnConnectDeferredTimer;   /* timer for able to enter PS after connected */

    TIMER_T         rPmSwitchPsModeTimer;       /* timer used in ENUM_PSP_SWITCH to switch PS mode */

    ENUM_NULL_STATE_T rNullState;

    PM_PROFILE_SETUP_INFO_T rPmProfSetupInfo;

    ENUM_POWER_SAVE_PROFILE_T eCurPsProf;

    PM_SLOW_CLOCK_COUNT_T rSlowClkCnt;

    /* phase 2/ 3 guard time (unit: us) */
    UINT_16 u2GuardTimePhase2;
    UINT_16 u2GuardTimePhase3;

    BOOLEAN fgIpAddressIsValid;
    UINT_32 u4IpAddress;
    UINT_32 u4BcPatternXIsValid;
    UINT_32 u4McPatternXIsValid;
    UINT_32 u4UcPatternXIsValid;

#if CFG_LP_IOT // used only for emulation/ IOT field try
    TIMER_T         rPmReadBeaconTimeoutTimer;       /* timer used in ENUM_PSP_SWITCH to switch PS mode */
#endif

    PM_FAST_SWITCH_PARAM_T  rPmFastSwitchParam;

    UINT_8          u4ContiHwTxFail;
    BOOLEAN         fgIsContinousPollingEnabled;
    BOOLEAN         fgIsContinousPollingSuspended;
    BOOLEAN         fgIsVoipPollingEnabled;
    BOOLEAN         fgIsUnderPowerSave;

    BOOLEAN         fgFastSwitchInProgress;

    BOOLEAN         fgPwrMode_PS; /* target/ current PS bit setting */

    // For WMM-PS only
    UINT_8          ucWmmPsEnterPsAtOnce;
    UINT_8          ucWmmPsDisableUcPoll;
    UINT_8          ucWmmPsConnWithTrig;

    BOOLEAN         fgIsBeaconTimeoutDetectionDisabled;
    BOOLEAN         fgDtimTrigEn;

#if CFG_IBSS_POWER_SAVE
    BOOLEAN     fgIsIbssPsTxEnabled;
    BOOLEAN     fgIsOutsideAtimWondow;
#endif /* CFG_IBSS_POWER_SAVE */

    /* Variables for the "extra" LP instructions.
     * Modules should maintains the number and instruction content validation when progromming it.
     */
    UINT_8      ucNumOfInstSleep;
    UINT_8      ucNumOfInstAwake;
    UINT_8      ucNumOfInstOn;
    UINT_32     au4LowPowerInst_sleep[NUM_OF_MAX_LP_INSTRUCTIONS];
    UINT_32     au4LowPowerInst_awake[NUM_OF_MAX_LP_INSTRUCTIONS];
    UINT_32     au4LowPowerInst_on[NUM_OF_MAX_LP_INSTRUCTIONS];

    BOOLEAN     fgIsWatchDogTriggered;
    BOOLEAN     fgIsBcnTimeoutStep4;
} PM_INFO_T, *P_PM_INFO_T;
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
#define PM_NEXT_STATE_VAR          eNextState

#define PM_STATE_TRANSITION(_prAdapter, rFromState, rToState) \
                { pmFsmTransAction_ ## rFromState ## _to_ ## rToState (_prAdapter); \
                  PM_NEXT_STATE_VAR = PM_STATE_ ## rToState; \
                  DBGLOG(LP, TRACE, (("PM STATE TRANSITION: [%s] --> [%s]\n"), \
                                   #rFromState, #rToState)); \
                  pmFsmStep(_prAdapter, PM_NEXT_STATE_VAR); \
                }

#define PM_STATE_TRANSITION1(_prAdapter, rFromState, rToState, rPostFix) \
                { \
                  WLAN_STATUS u4Status; \
                  status = pmFsmTransAction_ ## rFromState ## _to_ ## rToState ## _ ## rPostFix(_prAdapter); \
                  PM_NEXT_STATE_VAR = PM_STATE_ ## rToState; \
                  DBGLOG(LP, TRACE, (("SCAN STATE TRANSITION: [%s] --> [%s]\n"), \
                                   #rFromState, #rToState)); \
                  pmFsmStep(_prAdapter, PM_NEXT_STATE_VAR); \
                }

#define PM_ENABLE_BG_SSID_SCAN(_prAdapter, _fgEnableInt) \
    { \
        nicHwScanEnable(_prAdapter, ENUM_HW_SCAN_BG_SSID_SCAN); \
        nicpmEnterLowPower(_prAdapter, _fgEnableInt); \
    }

/* NOTE1: HW will automaticaly disable SSID Search function when LP ownback and
          scan done generated by the SSID search, but it will not clear this function
          automatically when interrupt is triggered by other LP functions.
*/
/* NOTE2: Scan done event reset is done in scanFsmTransAction_IDLE_to_ACTIVE() */
#if CFG_WORKAROUND_BG_SSID_SCAN_DONE
#define PM_DISABLE_BG_SSID_SCAN(_prAdapter) \
    { \
        nicpmLeaveLowPower(_prAdapter); \
        nicHwScanDisable(_prAdapter, ENUM_HW_SCAN_BG_SSID_SCAN); \
        /*NIC_VALIDATE_BG_SSID_SCAN_DONE_INT_EVENT(_prAdapter);*/ \
        NIC_DEL_INT_SCAN_DONE_EVENT(_prAdapter); \
    }
#else
#define PM_DISABLE_BG_SSID_SCAN(_prAdapter) \
    { \
        nicpmLeaveLowPower(_prAdapter); \
        nicHwScanDisable(_prAdapter, ENUM_HW_SCAN_BG_SSID_SCAN); \
    }
#endif

#define PM_BLOCK_TO_ENTER_LOW_POWER(_prAdapter) \
    { \
        pmFsmRunEventEnterAwakeState(_prAdapter); \
    }

#define PM_ABLE_TO_ENTER_LOW_POWER(_prAdapter, _fgEnableInt) \
    { \
        pmFsmRunEventEnterDozeState(_prAdapter, _fgEnableInt); \
    }

#define PM_IS_AC_QUEUE_DELIVERY_AND_TRIGGER_ENABLED(_prAdapter, eQueNum) \
       ((_prAdapter->rPmInfo.rPmProfSetupInfo.bmfgApsdEnAc & ((BIT(0) | BIT(4)) << eQueNum)) == \
       ((BIT(0) | BIT(4)) << eQueNum))



#define PM_IS_ADHOC_POWER_SAVE_CAPABLE(_prAdapter) \
       (_prAdapter->rPmInfo.rPmProfSetupInfo.fgAdhocPsCapability)

#define PM_CHECK_IF_OUTSIDE_ATIM_WINDOW(_prAdapter) \
        (_prAdapter->rPmInfo.fgIsOutsideAtimWondow)

#define PM_SET_FLAG_OUTSIDE_ATIM_WINDOW(_prAdapter) \
        (_prAdapter->rPmInfo.fgIsOutsideAtimWondow = TRUE)

#define PM_SET_FLAG_UNDER_ATIM_WINDOW(_prAdapter) \
        (_prAdapter->rPmInfo.fgIsOutsideAtimWondow = FALSE)


#define PM_IS_UNDER_POWER_SAVE_MODE(_prAdapter) \
        (_prAdapter->rPmInfo.fgIsUnderPowerSave)

#define PM_IS_UNDER_IBSS_POWER_SAVE_MODE(_prAdapter) \
        ((_prAdapter->eCurrentOPMode == OP_MODE_IBSS) && \
         (_prAdapter->rPmInfo.fgIsUnderPowerSave))

#define PM_IS_USING_PS_PROFILE_CONTINUOUS_ACTIVE(_prAdapter) \
        (_prAdapter->rPmInfo.eCurPsProf == ENUM_PSP_CONTINUOUS_ACTIVE)

#define PM_IS_VOIP_POLLING_ENABLED(_prAdapter) \
        (_prAdapter->rPmInfo.fgIsVoipPollingEnabled)

/*******************************************************************************
*                   F U N C T I O N   D E C L A R A T I O N S
********************************************************************************
*/

/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/
BOOLEAN
pmFsmInit (
    P_ADAPTER_T prAdapter
    );

VOID
pmFsmUnInit (
    P_ADAPTER_T prAdapter
    );

WLAN_STATUS
pmFsmRunEventEnterPowerSaveModeReq (
    IN P_ADAPTER_T  prAdapter,
    IN FUNC_CALLBACK_PS pfnPsIndication
    );

WLAN_STATUS
pmFsmRunEventOnConnectDeferredTask (
    IN P_ADAPTER_T  prAdapter
    );

WLAN_STATUS
pmFsmRunEventEnterPowerSaveModeDecision (
    IN P_ADAPTER_T  prAdapter
    );

WLAN_STATUS
pmFsmRunEventEnterActiveModeReq (
    IN P_ADAPTER_T  prAdapter,
    IN FUNC_CALLBACK_PS pvPSCallBack
    );

WLAN_STATUS
pmFsmRunEventPowerModeIndication (
    IN P_ADAPTER_T  prAdapter,
    IN BOOLEAN fgPowerSaveMode
    );

VOID
pmFsmRunEventEnterAwakeState (
    IN P_ADAPTER_T prAdapter
    );

VOID
pmFsmRunEventEnterDozeState (
    IN P_ADAPTER_T prAdapter,
    IN BOOLEAN     fgEnableGlobalInt
    );

WLAN_STATUS
pmSendNullFrameForConnectionDiagnostic (
    IN P_ADAPTER_T          prAdapter,
    IN PFN_TX_DONE_HANDLER  prFuncCallback
    );

WLAN_STATUS
pmSendNullFrame (
    IN P_ADAPTER_T          prAdapter,
    IN UINT_8               ucTid,
    IN BOOLEAN              fgPsBit,
    IN BOOLEAN              fgUseBasicRate,
    IN PFN_TX_DONE_HANDLER  prFuncCallback
    );

WLAN_STATUS
pmFsmRunEventSetPowerSaveProfile (
    IN P_ADAPTER_T  prAdapter,
    IN ENUM_POWER_SAVE_PROFILE_T ePsProf
    );

WLAN_STATUS
pmFsmRunEventSetPowerSaveProfileWatchDog (
    IN P_ADAPTER_T  prAdapter,
    IN ENUM_POWER_SAVE_PROFILE_T ePsProf
    );

VOID
pmDisableBeaconTimeoutDetectionFunc (
    IN P_ADAPTER_T  prAdapter,
    IN BOOLEAN      fgDisable
    );

VOID
pmContinuousPollingFreqStepUp (
    IN P_ADAPTER_T  prAdapter,
    IN BOOLEAN      fgStepUp
    );

VOID
pmSetIpAddress (
    IN P_ADAPTER_T  prAdapter,
    IN PUINT_8      aucIpAddress
    );

WLAN_STATUS
pmFsmRunEventOnConnect (
    IN P_ADAPTER_T      prAdapter,
    IN  UINT_16         u2AID,
    IN  UINT_16         u2BcnIntv,
    IN  UINT_8          ucDtimPeriod,
    IN  UINT_16         u2AtimWindow
    );

WLAN_STATUS
pmFsmRunEventAbort (
    IN P_ADAPTER_T  prAdapter
    );

WLAN_STATUS
pmFsmRunEventOnCreateIbss (
    IN P_ADAPTER_T      prAdapter,
    IN  UINT_16         u2BcnIntv
    );

VOID
pmSetAdhocStaAwake (
    IN P_ADAPTER_T  prAdapter,
    IN P_MSDU_INFO_T prMsduInfo,
    IN WLAN_STATUS rTxDoneStatus
    );

VOID
pmSetAdhocAllStaAwake (
    IN P_ADAPTER_T  prAdapter,
    IN P_MSDU_INFO_T prMsduInfo,
    IN WLAN_STATUS rTxDoneStatus
    );

VOID
pmEnableIbssPsTx (
    IN  P_ADAPTER_T     prAdapter
    );

VOID
pmDisableIbssPsTx (
    IN  P_ADAPTER_T     prAdapter
    );

WLAN_STATUS
pmSendAtimFrame (
    IN P_ADAPTER_T          prAdapter,
    IN PUINT_8              pucDestAddr,
    IN PFN_TX_DONE_HANDLER  pfTxDoneHandler
    );

BOOLEAN
pmClearAllStationAwakeState (
    IN P_ADAPTER_T      prAdapter
    );

BOOLEAN
pmGetBufferedTxInfoInStaRec (
    IN      P_ADAPTER_T     prAdapter,
    IN OUT  PUINT_8         prStaAddrArray,
    IN      UINT_32         u4InBufferLen,
    OUT     PUINT_32        pu4StaNum
    );

VOID
pmSetAcpiPowerD0 (
    IN P_ADAPTER_T prAdapter
    );

VOID
pmSetAcpiPowerD3 (
    IN P_ADAPTER_T prAdapter
    );

#if CFG_LP_IOT // used only for emulation/ IOT field try
BOOLEAN
pmSetIotBeaconTimeoutCheck (
    IN P_ADAPTER_T prAdapter
    );

VOID
pmFsmRunEventReadBeaconTimeoutCount (
    IN P_ADAPTER_T  prAdapter
    );

#endif

VOID
pmEnableVoipPollingFunc (
    IN P_ADAPTER_T  prAdapter
    );

VOID
pmDisableVoipPollingFunc (
    IN P_ADAPTER_T  prAdapter
    );

VOID
pmIndicateUcDataFrameReceived (
    IN P_ADAPTER_T  prAdapter,
    IN BOOLEAN fgMoreData
    );

VOID
pmIndicateDataFrameTransmitted (
    IN P_ADAPTER_T  prAdapter,
    IN UINT_32      u4DataPacketNum
    );

BOOLEAN
pmIsAbleToEnterPowerSaveMode (
    IN P_ADAPTER_T  prAdapter
    );

WLAN_STATUS
pmBeaconTimeoutHandler (
    IN P_ADAPTER_T          prAdapter,
    IN PFN_TX_DONE_HANDLER  prFuncCallback
    );

VOID
pmEnableContinuousPollingFunc (
    IN P_ADAPTER_T  prAdapter
    );

VOID
pmDisableContinuousPollingFunc (
    IN P_ADAPTER_T  prAdapter
    );

VOID
pmResumeContinuousPollingFunc (
    IN P_ADAPTER_T  prAdapter
    );

VOID
pmSuspendContinuousPollingFunc (
    IN P_ADAPTER_T  prAdapter
    );

VOID
pmHandleContiPollingCheck (
    IN P_ADAPTER_T prAdapter
    );

#endif /* _PM_FSM_H */

