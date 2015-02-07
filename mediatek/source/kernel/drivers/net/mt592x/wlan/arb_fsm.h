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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/arb_fsm.h#2 $
*/

/*! \file   "arb_fsm.h"
    \brief  In this file we define the STATE and EVENT for arbiter FSM.

    In arbiter, it makes decision of state transition. The STATE and EVENT for
    arbiter are defined here with detail description.
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
** $Log: arb_fsm.h $
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\76 2009-06-22 21:17:31 GMT mtk01088
**  add a variable to clear the fifo empty signal for abort case.
**  \main\maintrunk.MT5921\75 2009-03-20 01:04:04 GMT mtk01461
**  Remove the ConnectionReqEvent
**  \main\maintrunk.MT5921\74 2009-03-09 20:37:59 GMT mtk01461
**  Add a timer to check AdHoc protection mode
**  \main\maintrunk.MT5921\73 2009-02-25 16:10:49 GMT mtk01084
**  handle beacon timeout when continuous 10 HW TX excessive retry fail
**  \main\maintrunk.MT5921\72 2009-02-06 10:35:41 GMT mtk01725
**  Change Packet Tx method under META mode. Schdule a timer to continue TX rftest packet instead of doing it in TX done interrupt.
**  \main\maintrunk.MT5921\71 2009-02-04 16:51:30 GMT mtk01725
**  Update function declaration of arbFsmInit(). It is different under META mode.
**  \main\maintrunk.MT5921\70 2009-02-02 14:26:28 GMT mtk01084
**  modify continuous polling mechanism, with not to do extra poll when no WiFi downlink traffic
**  \main\maintrunk.MT5921\69 2008-08-12 16:04:53 GMT mtk01461
**  \main\maintrunk.MT5921\68 2008-08-12 11:01:25 GMT mtk01461
**  Update for Driver Review
**  \main\maintrunk.MT5921\67 2008-08-12 09:54:43 GMT mtk01461
**  Update for Driver Review
**  \main\maintrunk.MT5921\66 2008-08-11 09:38:10 GMT mtk01461
**  Update for Driver Review, remove ENUM eResetType
**  \main\maintrunk.MT5921\65 2008-07-10 16:37:30 GMT mtk01084
**  fix prefast warning
**  \main\maintrunk.MT5921\64 2008-07-07 13:22:42 GMT mtk01461
**  Revise MACRO to not switch PowerSave Mode during SCAN is proceeding
**  \main\maintrunk.MT5921\63 2008-07-01 20:03:56 GMT mtk01084
**  add record for the last scan time
**  \main\maintrunk.MT5921\62 2008-07-01 10:54:05 GMT mtk01084
**  switch back to the PS or ACTIVE mode based on the mode before scan
**  \main\maintrunk.MT5921\61 2008-06-18 20:44:41 GMT mtk01084
**  revise beacon timeout handling procedure
**  \main\maintrunk.MT5921\60 2008-06-01 14:03:25 GMT mtk01084
**  modify arbFsmRunEventIST() interface
**  \main\maintrunk.MT5921\59 2008-05-29 14:16:13 GMT mtk01084
**  modify arbFsmInit() interface and pass glue default value on initi
**  \main\maintrunk.MT5921\58 2008-05-16 10:34:42 GMT mtk01461
**  Reorder the function declarations
**  \main\maintrunk.MT5921\57 2008-05-12 15:57:16 GMT mtk01084
**  remove rWaitBeaconWatchdogTimer
**  \main\maintrunk.MT5921\56 2008-04-28 17:19:40 GMT mtk01084
**  modify PM control handling within BG SSID scan
**  \main\maintrunk.MT5921\55 2008-04-13 22:06:24 GMT mtk01461
**  Fix 1c wlan bssid fail after disassociate OID issued
**  \main\maintrunk.MT5921\54 2008-04-10 20:08:39 GMT mtk01084
**  Add TX throughput into PS mode switching criterion under PSP-fast mode.
**  \main\maintrunk.MT5921\53 2008-03-31 09:49:47 GMT mtk01461
**  Change prototype of arbFsmRunEventJoinRxClassError
**  \main\maintrunk.MT5921\52 2008-03-25 21:45:33 GMT mtk01084
**  modify the callback function prototype on change PS mode
**  \main\maintrunk.MT5921\51 2008-03-19 15:21:33 GMT mtk01461
**  Remove BEACON TIMEOUT macro
**  \main\maintrunk.MT5921\50 2008-03-18 09:46:32 GMT mtk01088
**  Add function declaration for check and indicate pmkid candidate
**  \main\maintrunk.MT5921\49 2008-03-13 14:27:27 GMT mtk01461
**  Revise Roaming Module
**  \main\maintrunk.MT5921\48 2008-03-12 09:51:53 GMT mtk01461
**  Add Connection diagnostic function
**  \main\maintrunk.MT5921\47 2008-03-11 22:39:50 GMT mtk01084
**  modify ARB_INDICATE_UC_DATA_FRAME_RECEICED() macro
**  \main\maintrunk.MT5921\46 2008-03-11 13:32:33 GMT mtk01084
**  modify arbFsmRunEventScanRequest() function argument
**  \main\maintrunk.MT5921\45 2008-03-07 10:47:28 GMT mtk01084
**  add define for the watchdog to prevent beacon is not received after connected to AP
**  \main\maintrunk.MT5921\44 2008-03-06 22:22:35 GMT mtk01084
**  modify the naming for the PM related function
**  \main\maintrunk.MT5921\43 2008-03-04 21:37:34 GMT mtk01385
**  1. modify arbFsm Run event Join Disassoc Tx Done and arbFsm Run Event Sec Deauth Done function parameters.
**  \main\maintrunk.MT5921\42 2008-02-29 15:49:09 GMT mtk01088
**  add funxtion for handle disassociate frame sen out
**  \main\maintrunk.MT5921\41 2008-02-29 12:27:47 GMT mtk01088
**  rename the sec related function declaration
**  \main\maintrunk.MT5921\40 2008-02-27 12:12:04 GMT mtk01461
**  Add default for switch case statement to avoid warning in Linux
**  \main\maintrunk.MT5921\39 2008-02-18 17:38:07 GMT mtk01084
**  remove un-used function
**  \main\maintrunk.MT5921\38 2008-02-15 19:19:19 GMT mtk01084
**  modify acquire PM control method
**  \main\maintrunk.MT5921\37 2008-02-12 22:59:55 GMT mtk01461
**  Refine ARB_IF_IN_RFTEST_STATE to IS_ARB_IN_RFTEST_STATE
**  \main\maintrunk.MT5921\36 2008-01-22 22:47:05 GMT mtk01084
**  add macros for control PM under TX path
**  \main\maintrunk.MT5921\35 2008-01-17 17:45:00 GMT mtk01084
**  add watchdog timer for waiting 1st beacon after connected
**  \main\maintrunk.MT5921\34 2008-01-03 20:51:09 GMT mtk01084
**  remove lines in setting/ querying RF configuration
**  \main\maintrunk.MT5921\33 2007-12-25 23:32:36 GMT mtk01084
**  handle scan done or not when own back from BG SSID SCAN state
**  \main\maintrunk.MT5921\32 2007-12-11 00:07:49 GMT mtk01461
**  Add function declarations
**  \main\maintrunk.MT5921\31 2007-12-07 11:31:01 GMT mtk01084
**  reocrd the last RX UC packet time
**  \main\maintrunk.MT5921\30 2007-12-03 18:02:09 GMT mtk01084
**  separate NORMAL_TR state from other in acquire/ release power control macros
**  \main\maintrunk.MT5921\29 2007-11-30 19:42:03 GMT mtk01084
**  modify PM control macros
**  \main\maintrunk.MT5921\28 2007-11-29 20:32:02 GMT mtk01385
**  1. add ARB RFTEST mode check macro.
**  \main\maintrunk.MT5921\27 2007-11-27 19:54:44 GMT mtk01084
**  add arbUnInit() function
**  \main\maintrunk.MT5921\26 2007-11-26 19:24:58 GMT mtk01461
**  Unify SCAN
**  \main\maintrunk.MT5921\25 2007-11-22 22:28:34 GMT mtk01084
**  update ARB macros
**  \main\maintrunk.MT5921\24 2007-11-20 19:03:15 GMT mtk01084
**  change function name
**  \main\maintrunk.MT5921\23 2007-11-17 15:33:06 GMT mtk01385
**  1. add Rf test mode related functions.
**  \main\maintrunk.MT5921\22 2007-11-13 17:56:55 GMT mtk01084
**  add new macro to handle the state wating the 1st beacon after conected
**  \main\maintrunk.MT5921\21 2007-11-09 12:45:30 GMT mtk01084
**  add new macro ARB_INDICATE_UC_DATA_FRAME_RECEICED( for FAST PS mode
**  \main\maintrunk.MT5921\20 2007-11-06 20:17:07 GMT mtk01088
**  add a flag for HW status check
**  \main\maintrunk.MT5921\19 2007-11-05 16:57:48 GMT mtk01425
**  1. Remove fgIsRenewBSSID from ARB_INFO_T
**  \main\maintrunk.MT5921\18 2007-11-02 00:52:05 GMT mtk01461
**  Unify TX Path for Normal and IBSS Power Save + IBSS neighbor learning
**  \main\maintrunk.MT5921\17 2007-10-30 09:22:57 GMT mtk01425
**  1. Add reset type paramter to arbFsmRunEventReset
**
**  \main\maintrunk.MT5921\16 2007-10-25 17:59:18 GMT mtk01461
**  Add VOIP SCAN & Refine Roaming
** Revision 1.10  2007/07/16 02:30:20  MTK01088
** fixed non-used function declaration
**
** Revision 1.9  2007/07/12 11:00:55  MTK01084
** function pointer for OID request
**
** Revision 1.8  2007/07/12 06:14:55  MTK01084
** update timer related routines
**
** Revision 1.7  2007/07/09 06:21:52  MTK01088
** add security needed function declaration
**
** Revision 1.6  2007/07/04 10:07:08  MTK01088
** change function name
**
** Revision 1.5  2007/07/03 07:41:39  MTK01088
** remove the sec state from arb fsm
** add the function declaration used for security module
**
** Revision 1.4  2007/06/27 06:15:32  MTK01088
** add the sec state at arb fsm
**
** Revision 1.3  2007/06/27 02:15:57  MTK01461
** Update SCAN_FSM, Initial(Can Load Module), Proc(Can do Reg R/W), TX API
**
** Revision 1.2  2007/06/26 08:39:03  MTK01084
** fixed typo
**
** Revision 1.1.1.1  2007/06/22 08:09:05  MTK01461
** no message
**
*/

#ifndef _ARB_FSM_H
#define _ARB_FSM_H
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
/* The maximum delay time of Media State Indication when any event of connection lost was
 * detected.
 */
#define CONNECTION_LOST_INDICATION_TIMEOUT_SEC              9 // Seconds

#define SCAN_REQUEST_TIMEOUT_MSEC                           20000 // msec

/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/
typedef enum _ENUM_ARB_STATE_T {
    ARB_STATE_POWER_OFF = 0,
    ARB_STATE_RESET,
    ARB_STATE_RF_TEST,
    ARB_STATE_STANDBY,
    ARB_STATE_IDLE,
    ARB_STATE_SEARCH,
    ARB_STATE_BG_SSID_SCAN,
    ARB_STATE_JOIN,
    ARB_STATE_IBSS_ALONE,
    ARB_STATE_IBSS_MERGE,
    ARB_STATE_NORMAL_TR,
    ARB_STATE_SCAN,
    ARB_STATE_DEDICATED_MEASUREMEMT,
    ARB_STATE_NUM
} ENUM_ARB_STATE_T;

typedef struct _ARB_INFO_T {
    ENUM_ARB_STATE_T    ePreviousState;
    ENUM_ARB_STATE_T    eCurrentState;

    BOOLEAN             fgTestMode;
    BOOLEAN             fgTryFullScan;
    BOOLEAN             fgIsDiagnosingConnection;

    P_BSS_DESC_T        prTargetBssDesc;

    TIMER_T             rIbssAloneTimer;

    TIMER_T             rIndicationOfDisconnectTimer;

    TIMER_T             rProtectionTimerForAdHoc;

    /* HW Error flag */
    UINT_32             u4Flag;

    /* Counter for Power Control Semaphore */
    UINT_32             u4PwrCtrlBlockCnt;

    BOOLEAN             fgIsUnderActiveModeBeforeScan;

    OS_SYSTIME          rLastScanRequestTime;

} ARB_INFO_T, *P_ARB_INFO_T;

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

#define ARB_STATE_TRANSITION_FLAG   fgIsTransition
#define ARB_NEXT_STATE_VAR          eNextState

#define ARB_STATE_TRANSITION(prAdapter, rFromState, rToState) \
            { arbFsmTransAction_ ## rFromState ## _to_ ## rToState((P_ADAPTER_T)prAdapter); \
              ARB_NEXT_STATE_VAR = ARB_STATE_ ## rToState; \
              ARB_STATE_TRANSITION_FLAG = (BOOLEAN)TRUE; \
            }

#if DBG
#define ARB_INIT_TIMER(_adapter_p, _timer, _callbackFunc, _fgNeedHwAccess) \
        { \
            kalMemCopy((_timer).aucDbgString, #_callbackFunc, \
                (sizeof((_timer).aucDbgString) < sizeof(#_callbackFunc) ? \
                sizeof((_timer).aucDbgString) : sizeof(#_callbackFunc))); \
            (_timer).aucDbgString[sizeof((_timer).aucDbgString) - 1] = 0; \
            timerInitTimer(_adapter_p, \
                           &(_timer), \
                           (PFN_MGMT_TIMEOUT_FUNC)_callbackFunc, \
                           (UINT_32)(_adapter_p), \
                           (BOOLEAN)(_fgNeedHwAccess)); \
        }
#else
#define ARB_INIT_TIMER(_adapter_p, _timer, _callbackFunc, _fgNeedHwAccess) \
        { \
            timerInitTimer(_adapter_p, \
                           &(_timer), \
                           (PFN_MGMT_TIMEOUT_FUNC)_callbackFunc, \
                           (UINT_32)(_adapter_p), \
                           (BOOLEAN)(_fgNeedHwAccess)); \
        }
#endif

#define ARB_SET_TIMER(_adapter_p, _timer, _timeout_ms) \
        { \
            timerStartTimer(_adapter_p, \
                            &(_timer), \
                            _timeout_ms); \
        }

#define ARB_CANCEL_TIMER(_adapter_p, _timer) \
        { \
            timerStopTimer(_adapter_p, &(_timer)); \
        }

#define ARB_INDICATE_PS_STATUS(_adapter_p, _fgPsState) \
        { \
            pmFsmRunEventPowerModeIndication(_adapter_p, _fgPsState); \
        }

#define ARB_INDICATE_UC_DATA_FRAME_RECEICED(_adapter_p, _fgMoreDataBit) \
        { \
            if ((_adapter_p->rArbInfo.eCurrentState == ARB_STATE_NORMAL_TR) && \
                (!_adapter_p->rScanInfo.fgIsScanReqProceeding)) { \
                pmIndicateUcDataFrameReceived(_adapter_p, _fgMoreDataBit); \
            } \
        }

#define ARB_INDICATE_DATA_FRAME_TRANSMITTED(_adapter_p, _u4DataPacketNum) \
        { \
            if ((_adapter_p->rArbInfo.eCurrentState == ARB_STATE_NORMAL_TR) && \
                (!_adapter_p->rScanInfo.fgIsScanReqProceeding)) { \
                pmIndicateDataFrameTransmitted(_adapter_p, _u4DataPacketNum); \
            } \
        }

#define ARB_FSM_SAVE_LAST_RX_UC_DATA_FRAME_SYSTIME(_prAdapter, _rCurSysTime) \
                    _prAdapter->rLastRxUcDataSysTime = _rCurSysTime;

#define ARB_FSM_GET_LAST_RX_UC_DATA_FRAME_SYSTIME(_prAdapter) \
                    _prAdapter->rLastRxUcDataSysTime

#define BEACON_TIMEOUT_GUARD_TIME_FROM_UC_DATA_MSEC         100 // milliseconds

#define WAIT_BEACON_ON_CONNECTED_MSEC                       2000 // milliseconds

#define CONTI_POLLING_SUSPEND_CHECK_MSEC                    500 // milliseconds

#if CFG_SDIO_DEVICE_DRIVER_WO_NDIS
#define RFTEST_PKT_TX_INTERVAL                                          1
#endif

#define ARB_ACQUIRE_POWER_CONTROL_FROM_PM_IN_OS_TX_PATH(_prAdapter) \
    { \
        P_ARB_INFO_T _prArbInfo = &_prAdapter->rArbInfo; \
        switch (_prArbInfo->eCurrentState) { \
        case ARB_STATE_BG_SSID_SCAN: \
            PM_DISABLE_BG_SSID_SCAN(_prAdapter); \
            break; \
        case ARB_STATE_IDLE: \
            nicpmPowerOn(_prAdapter); \
            break; \
        default: \
            break; \
        } \
        /* Increase Block to Enter Low Power Semaphore count */ \
        _prArbInfo->u4PwrCtrlBlockCnt++; \
    }

#define ARB_TEST_AND_GET_POWER_CONTROL_FROM_PM_IN_TX_PATH(_prAdapter) \
    { \
        P_ARB_INFO_T _prArbInfo = &_prAdapter->rArbInfo; \
        switch (_prArbInfo->eCurrentState) { \
        /* OS TX packets will be dropped directly if it is not under NORMAL_TR state */ \
        /* And it is already awake to MGMT TX packets */ \
        case ARB_STATE_NORMAL_TR: \
            PM_BLOCK_TO_ENTER_LOW_POWER(_prAdapter); \
            break; \
        default: \
            break; \
        } \
    }


#define ARB_ACQUIRE_POWER_CONTROL_FROM_PM(_prAdapter) \
    { \
        P_ARB_INFO_T _prArbInfo = &_prAdapter->rArbInfo; \
        switch (_prArbInfo->eCurrentState) { \
        case ARB_STATE_NORMAL_TR: \
            PM_BLOCK_TO_ENTER_LOW_POWER(_prAdapter); \
            break; \
        case ARB_STATE_BG_SSID_SCAN: \
            PM_DISABLE_BG_SSID_SCAN(_prAdapter); \
            break; \
        case ARB_STATE_IDLE: \
            nicpmPowerOn(_prAdapter); \
            break; \
        default: \
            break; \
        } \
        /* Increase Block to Enter Low Power Semaphore count */ \
        _prArbInfo->u4PwrCtrlBlockCnt++; \
    }

#define ARB_ACQUIRE_POWER_CONTROL_FROM_PM_IN_IST(_prAdapter) \
    { \
        P_ARB_INFO_T _prArbInfo = &_prAdapter->rArbInfo; \
        switch (_prArbInfo->eCurrentState) { \
        case ARB_STATE_NORMAL_TR: \
            PM_BLOCK_TO_ENTER_LOW_POWER(_prAdapter); \
            break; \
        case ARB_STATE_BG_SSID_SCAN: \
            PM_DISABLE_BG_SSID_SCAN(_prAdapter); \
            break; \
        case ARB_STATE_IDLE: \
            nicpmPowerOn(_prAdapter); \
            break; \
        default: \
            break; \
        } \
        /* Increase Block to Enter Low Power Semaphore count */ \
        _prArbInfo->u4PwrCtrlBlockCnt++; \
    }

#define ARB_RECLAIM_POWER_CONTROL_TO_PM(_prAdapter) \
    { \
        P_ARB_INFO_T _prArbInfo = &_prAdapter->rArbInfo; \
        ASSERT(_prArbInfo->u4PwrCtrlBlockCnt != 0); \
        /* Decrease Block to Enter Low Power Semaphore count */ \
        _prArbInfo->u4PwrCtrlBlockCnt--; \
        switch (_prArbInfo->eCurrentState) { \
        case ARB_STATE_NORMAL_TR: \
            /* Only performs subsequent procedure if \
               LP semaphore count equals to 0 */ \
            if (_prArbInfo->u4PwrCtrlBlockCnt == 0) { \
                PM_ABLE_TO_ENTER_LOW_POWER(_prAdapter, FALSE); \
            } \
            break; \
        case ARB_STATE_BG_SSID_SCAN: \
            PM_ENABLE_BG_SSID_SCAN(_prAdapter, FALSE); \
            break; \
        case ARB_STATE_IDLE: \
            nicpmPowerOff(_prAdapter); \
            break; \
        default: \
            break; \
        } \
    }

#define ARB_RECLAIM_POWER_CONTROL_TO_PM_IN_IST(_prAdapter) \
    { \
        P_ARB_INFO_T _prArbInfo = &_prAdapter->rArbInfo; \
        ASSERT(_prArbInfo->u4PwrCtrlBlockCnt != 0); \
        /* Decrease Block to Enter Low Power Semaphore count */ \
        _prArbInfo->u4PwrCtrlBlockCnt--; \
        switch (_prArbInfo->eCurrentState) { \
        case ARB_STATE_NORMAL_TR: \
            /* Only performs subsequent procedure if \
               LP semaphore count equals to 0 */ \
            if (_prArbInfo->u4PwrCtrlBlockCnt == 0) { \
                PM_ABLE_TO_ENTER_LOW_POWER(_prAdapter, TRUE); \
            } \
            break; \
        case ARB_STATE_BG_SSID_SCAN: \
            PM_ENABLE_BG_SSID_SCAN(_prAdapter, TRUE); \
            break; \
        case ARB_STATE_IDLE: \
            nicpmPowerOff(_prAdapter); \
            break; \
        default: \
            break; \
        } \
    }

#define IS_ARB_IN_RFTEST_STATE(_prAdapter) \
            ((BOOLEAN)(_prAdapter->rArbInfo.eCurrentState == ARB_STATE_RF_TEST))

#define IS_ARB_IN_BG_SSID_SCAN_STATE(_prAdapter) \
            ((BOOLEAN)(_prAdapter->rArbInfo.eCurrentState == ARB_STATE_BG_SSID_SCAN))


/*******************************************************************************
*                   F U N C T I O N   D E C L A R A T I O N S
********************************************************************************
*/
#if CFG_SDIO_DEVICE_DRIVER_WO_NDIS
WLAN_STATUS
arbFsmInit(
    IN P_ADAPTER_T prAdapter
    );

VOID
arbFsmRunEventPacketTxIntervalTimeOut(
    IN P_ADAPTER_T prAdapter
    );

#else
WLAN_STATUS
arbFsmInit(
    IN P_ADAPTER_T prAdapter,
    IN P_REG_INFO_T prRegInfo
    );
#endif
VOID
arbFsmUnInit (
    P_ADAPTER_T prAdapter
    );

VOID
arbFsmSteps (
    P_ADAPTER_T prAdapter,
    ENUM_ARB_STATE_T rNextState
    );

BOOLEAN
arbFsmRunEventIST (
    IN P_ADAPTER_T      prAdapter
    );

VOID
arbFsmRunEventRootTimerHandler (
    IN P_ADAPTER_T  prAdapter
    );

VOID
arbFsmRunEventReset (
    IN P_ADAPTER_T  prAdapter
    );

VOID
arbFsmRunEventAbort (
    IN P_ADAPTER_T prAdapter,
    IN BOOLEAN fgIsDelayMediaStateIndication
    );

WLAN_STATUS
arbFsmRunEventTxMsduFromOs (
    IN P_ADAPTER_T      prAdapter,
    IN P_PACKET_INFO_T  prPacketInfo
    );

WLAN_STATUS
arbFsmRunEventTxMmpdu (
    IN P_ADAPTER_T      prAdapter,
    IN P_MSDU_INFO_T    prMsduInfo
    );

VOID
arbFsmRunEventConnectionTest (
    IN P_ADAPTER_T prAdapter
    );

VOID
arbFsmRunEventConnectionDiagnosis (
    IN P_ADAPTER_T prAdapter,
    IN P_MSDU_INFO_T prMsduInfo,
    IN WLAN_STATUS rStatus
    );

VOID
arbFsmRunEventJoinRxClassError (
    IN P_ADAPTER_T prAdapter,
    IN P_STA_RECORD_T prStaRec
    );

VOID
arbFsmRunEventJoinRxAuthAssoc (
    IN P_ADAPTER_T prAdapter,
    IN P_SW_RFB_T prSwRfb
    );

VOID
arbFsmRunEventJoinRxTimeOut (
    IN P_ADAPTER_T prAdapter
    );

VOID
arbFsmRunEventJoinTxTimeOut (
    IN P_ADAPTER_T prAdapter
    );

VOID
arbFsmRunEventJoinTxDone (
    IN P_ADAPTER_T      prAdapter,
    IN P_MSDU_INFO_T    prMsduInfo,
    IN WLAN_STATUS      rTxDoneStatus
    );

VOID
arbFsmRunEventJoinFailureTimeOut (
    IN P_ADAPTER_T      prAdapter
    );

VOID
arbFsmRunEventJoinDisassoc (
    IN P_ADAPTER_T prAdapter
    );


WLAN_STATUS
arbFsmRunEventSecKeyInstalled(
    IN P_ADAPTER_T          prAdapter,
    IN P_PARAM_KEY_T        prKey
    );

VOID
arbFsmRunEventSecDeauthDone(
    IN P_ADAPTER_T      prAdapter,
    IN P_MSDU_INFO_T    prMsduInfo,
    IN WLAN_STATUS      rTxDoneStatus
    );

VOID
arbFsmRunEventConnectionEndOfCounterMeasure(
    IN P_ADAPTER_T  prAdapter
    );

VOID
arbFsmRunEventConnectionStartCounterMeasure(
    IN P_ADAPTER_T  prAdapter
    );

BOOLEAN
arbFsmRunEventSecTxFlowControl(
    IN P_ADAPTER_T  prAdapter,
    IN BOOLEAN      fgClearSignal
    );

VOID
arbFsmRunEventSecTxFIFOEmpty(
    IN P_ADAPTER_T  prAdapter
    );

VOID
arbFsmRunEventSecCancelEAPoLTimer(
    IN P_ADAPTER_T          prAdapter
    );

VOID
arbFsmRunEventSecIndicatePmkidCand(
    IN P_ADAPTER_T          prAdapter
    );

VOID
arbFsmRunEventSecCounterMeasureDone(
    IN P_ADAPTER_T          prAdapter
    );

WLAN_STATUS
arbFsmRunEventScanRequest (
    IN P_ADAPTER_T prAdapter,
    IN P_SCAN_REQ_CONFIG_T prScanReqConfig,
    IN BOOLEAN fgForceToScanInActiveMode
    );

WLAN_STATUS
arbFsmRunEventScanSetPsVoipTrap (
    IN P_ADAPTER_T prAdapter,
    IN P_SCAN_REQ_CONFIG_T prScanReqConfig,
    IN BOOLEAN fgForceToScanInActiveMode
    );

VOID
arbFsmRunEventScanPartialScanTimeOut (
    IN P_ADAPTER_T prAdapter
    );

VOID
arbFsmRunEventScanCheckForHangTimeOut (
    IN P_ADAPTER_T prAdapter
    );

VOID
arbFsmRunEventScanDone (
    IN P_ADAPTER_T  prAdapter
    );

VOID
arbFsmRunEventScanPsVoipPartialScanStop (
    IN P_ADAPTER_T prAdapter
    );

VOID
arbFsmRunEventOnConnectDeferredTimer (
    IN P_ADAPTER_T  prAdapter
    );

VOID
arbFsmRunEventTimerPowerSaveSwitch (
    IN P_ADAPTER_T  prAdapter
    );

VOID
arbFsmRunEventTimeupVoipInterval (
    IN P_ADAPTER_T  prAdapter
    );

VOID
arbFsmRunEventIbssAloneTimeOut (
    IN P_ADAPTER_T prAdapter
    );

VOID
arbFsmRunEventIbssProtectionTimeOut (
    IN P_ADAPTER_T prAdapter
    );

VOID
arbFsmRunEventIbssMerge (
    IN P_ADAPTER_T prAdapter,
    IN P_BSS_DESC_T prBssDesc
    );

VOID
arbFsmRunEventProcessDeauth (
    IN P_ADAPTER_T prAdapter,
    IN P_SW_RFB_T prSwRfb
    );

VOID
arbFsmRunEventProcessDisassoc (
    IN P_ADAPTER_T prAdapter,
    IN P_SW_RFB_T prSwRfb
    );

VOID
arbFsmRunEventProcessProbeReq (
    IN P_ADAPTER_T prAdapter,
    IN P_SW_RFB_T prSwRfb
    );

#if CFG_IBSS_POWER_SAVE
VOID
arbSetAdhocStaAwake (
    IN P_ADAPTER_T  prAdapter,
    IN P_MSDU_INFO_T prMsduInfo,
    IN WLAN_STATUS rTxDoneStatus
    );

VOID
arbSetAdhocAllStaAwake (
    IN P_ADAPTER_T  prAdapter,
    IN P_MSDU_INFO_T prMsduInfo,
    IN WLAN_STATUS rTxDoneStatus
    );
#endif /* CFG_IBSS_POWER_SAVE */

VOID
arbFsmRunEventRoamingRCPI (
    IN P_ADAPTER_T prAdapter
    );

VOID
arbFsmRunEventRoamingDecision (
    IN P_ADAPTER_T prAdapter
    );

VOID
arbFsmRunEventRoamingDiscovery (
    IN P_ADAPTER_T prAdapter
    );

VOID
arbFsmRunEventIndicationOfDisconnectTimeOut (
    IN P_ADAPTER_T prAdapter
    );

VOID
arbFsmRunEventRftestEnterTestMode (
    IN  P_ADAPTER_T       prAdapter,
    IN  PUINT_8           pucEepromBuf,
    IN  UINT_32           u4EepromBufByteLen
    );

VOID
arbFsmRunEventRftestAbortTestMode (
    IN  P_ADAPTER_T       prAdapter
    );

WLAN_STATUS
arbFsmRunEventRftestSetAutoTest (
    IN P_ADAPTER_T                   prAdapter,
    IN P_PARAM_MTK_WIFI_TEST_STRUC_T prRfATCfg
    );

WLAN_STATUS
arbFsmRunEventRftestQueryAutoTest (
    IN P_ADAPTER_T                   prAdapter,
    IN P_PARAM_MTK_WIFI_TEST_STRUC_T prRfATStatus
    );

VOID
arbFsmRunEventAbortOnWaitBeaconTimeOut (
    IN P_ADAPTER_T prAdapter
    );

VOID
arbFsmRunEventBeaconTimeoutStepDownHandling (
    IN P_ADAPTER_T prAdapter
    );

VOID
arbFsmRunEventContiPollingCheckHandling (
    IN P_ADAPTER_T prAdapter
    );

VOID
arbFsmRunEventContiHwTxFailCheckHandling (
    IN P_ADAPTER_T prAdapter
    );

#if CFG_PEEK_RCPI_VALUE_PERIOD_SEC
VOID
arbFsmRunEventRcpiDiagnostic (
    IN P_ADAPTER_T prAdapter
    );
#endif /* CFG_PEEK_RCPI_VALUE_PERIOD_SEC */

/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/

#endif /* _ARB_FSM_H */

