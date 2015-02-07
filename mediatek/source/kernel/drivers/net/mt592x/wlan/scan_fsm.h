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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/scan_fsm.h#1 $
*/

/*! \file   "scan_fsm.h"
    \brief  In this file we define the STATE and EVENT for scan FSM.

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
** $Log: scan_fsm.h $
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\21 2008-08-25 09:44:58 GMT mtk01461
**  Update for Driver Review
**  \main\maintrunk.MT5921\20 2008-08-20 17:46:43 GMT mtk01084
**  Modify for coding rule conformance
**  \main\maintrunk.MT5921\19 2008-08-12 09:55:50 GMT mtk01461
**  Update for Driver Review - PRTIAL_SCAN_CHANNEL_GROUPS_NUM
**  \main\maintrunk.MT5921\18 2008-07-11 10:56:34 GMT mtk01084
**  remove un-used variable
**  \main\maintrunk.MT5921\17 2008-06-12 20:28:37 GMT mtk01461
**  Add dwell min/ext time definition of SCAN parameters
**  \main\maintrunk.MT5921\16 2008-03-20 11:48:43 GMT mtk01084
**  modify the initial value for the BG SSID scan steps
**  \main\maintrunk.MT5921\15 2008-03-19 15:21:47 GMT mtk01461
**  Increase the Passive Scan interval for VOIP
**  \main\maintrunk.MT5921\14 2008-03-13 14:27:52 GMT mtk01461
**  Revise partial scan interval from 200ms to 20ms for Roaming
**  \main\maintrunk.MT5921\13 2008-03-06 22:22:51 GMT mtk01084
**  modify BG SSID scan parameter
**  \main\maintrunk.MT5921\12 2008-02-18 17:39:09 GMT mtk01084
**  modify function return status
**  \main\maintrunk.MT5921\11 2007-12-11 00:07:56 GMT mtk01461
**  Update define naming
**  \main\maintrunk.MT5921\10 2007-12-08 22:29:17 GMT mtk01084
**  modify BACKUP_REGISTER_VALUE_T structure
**  \main\maintrunk.MT5921\9 2007-12-04 18:09:57 GMT mtk01461
**  Add function declarations
**  \main\maintrunk.MT5921\8 2007-11-26 19:26:03 GMT mtk01461
**  Unify SCAN
**  \main\maintrunk.MT5921\7 2007-11-09 12:49:15 GMT mtk01084
**  update new definition
**  \main\maintrunk.MT5921\6 2007-10-25 21:39:23 GMT mtk01084
**  modify scanStart argument
**  \main\maintrunk.MT5921\5 2007-10-25 17:59:23 GMT mtk01461
**  Add VOIP SCAN & Refine Roaming
** Revision 1.4  2007/07/09 07:38:05  MTK01084
** temporarily remark-off place using SCAN structure
**
** Revision 1.3  2007/07/05 14:11:11  MTK01084
** update scan FSM structures
**
** Revision 1.2  2007/06/27 02:12:08  MTK01461
** Update SCAN_FSM, Initial(Can Load Module), Proc(Can do Reg R/W), TX API
**
*/

#ifndef _SCAN_FSM_H
#define _SCAN_FSM_H

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

/* The dwell time for staying in ACTIVE mode when connected to AP (unit: ms) */
#define DEFAULT_SCAN_TYPE                           SCAN_TYPE_ACTIVE_SCAN
#define DEFAULT_SCAN_PER_CHNL_MIN_DWELL_TIME        20
#define DEFAULT_SCAN_PER_CHNL_EXT_DWELL_TIME        120
#define DEFAULT_SCAN_RX_FIFO_THRESHOLD              0
#define DEFAULT_SCAN_NUM_OF_PROBE_REQUEST           3
#define DEFAULT_SCAN_NUM_OF_SPECIFIED_PROBE_REQ     0
#define DEFAULT_SCAN_HONOR_SERVICE_PERIOD           0
#define DEFAULT_SCAN_ENABLE_TRIGGER_EVENT           0

#define BG_SSID_SCAN_BASE_WAKEUP_PERIOD             3000    // unit: TU (min: 1, max: 65535)
#define BG_SSID_SCAN_WAKEUP_PERIOD_STEPS            5       // steps of exp. growth (min: 0, max: 7)
#define BG_SSID_SCAN_WAKEUP_MIN_RCPI                0


#define SCAN_CHANNEL_DWELL_TIME_MIN                 12 // Millisecond
#define SCAN_CHANNEL_DWELL_TIME_EXT                 98 // Millisecond
#define VOIP_SCAN_CHANNEL_DWELL_TIME_EXT            8 // Millisecond

#define FULL_SCAN_TOTAL_PROBE_REQ_NUM               3 // Number of frame
#define FULL_SCAN_SPECIFIC_PROBE_REQ_NUM            1 // Number of frame

#define PARTIAL_SCAN_TOTAL_PROBE_REQ_NUM            2 // Number of frame
#define PARTIAL_SCAN_SPECIFIC_PROBE_REQ_NUM         1 // Number of frame

#define VOIP_PARTIAL_SCAN_TOTAL_PROBE_REQ_NUM       1 // Number of frame
#define VOIP_PARTIAL_SCAN_SPECIFIC_PROBE_REQ_NUM    0 // Number of frame

#define PS_VOIP_PARTIAL_SCAN_TOTAL_PROBE_REQ_NUM    1 // Number of frame
#define PS_VOIP_PARTIAL_SCAN_SPECIFIC_PROBE_REQ_NUM 0 // Number of frame

#define ROAMING_SCAN_TOTAL_PROBE_REQ_NUM            1 // Number of frame
#define ROAMING_SCAN_SPECIFIC_PROBE_REQ_NUM         1 // Number of frame

#define PARTIAL_SCAN_TIMEOUT_MSEC                   20 // Millisecond

#define VOIP_PARTIAL_SCAN_TIMEOUT_MSEC              20 // Millisecond

/* NOTE: For VOIP SCAN, we'll do Active(20msec) + Passive(20msec) +
 * Active(20msec) + Passive(20msec) for 1 channel.
 */
#define SCAN_VOIP_PASSIVE_SCAN_INTERVAL             3

#define SCAN_CHECK_FOR_HANG_GUARD_TIME_MSEC         1000 // Millisecond

#define INTERLACED_SCAN_CHANNEL_GROUPS_NUM          3 // Groups(e.g. 1/4/7/10, 2/5/8/11, 3/6/9)

/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/
typedef enum _ENUM_SCAN_STATE_T {
    SCAN_STATE_IDLE = 0,
    SCAN_STATE_ACTIVE,
    SCAN_STATE_NUM
} ENUM_SCAN_STATE_T;

typedef enum _ENUM_HW_SCAN_MODE_T
{
    ENUM_HW_SCAN_NORMAL_SCAN,
    ENUM_HW_SCAN_BG_SSID_SCAN
} ENUM_HW_SCAN_MODE_T, *PENUM_HW_SCAN_MODE_T;



typedef struct _SCAN_STATUS_T {
    UINT_8 ucLastScanChnlIdx;
    UINT_8 ucLastScanBandIdx;
} SCAN_STATUS_T, *P_SCAN_STATUS_T;

typedef struct _BACKUP_REGISTER_VALUE_T {
    UINT_32 u4RegSpcr;
    UINT_32 u4RegOrgRxFifoThr;
    UINT_32 u4RegOrgLpEnFunc;
} BACKUP_REGISTER_VALUE_T, *P_BACKUP_REGISTER_VALUE_T;

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

#define SCAN_NEXT_STATE_VAR          eNextState

#define SCAN_STATE_TRANSITION(prAdapter, rFromState, rToState) \
                { scanFsmTransAction_ ## rFromState ## _to_ ## rToState (prAdapter); \
                  SCAN_NEXT_STATE_VAR = SCAN_STATE_ ## rToState; \
                  DBGLOG(SCAN, TRACE, (("SCAN STATE TRANSITION: [%s] --> [%s]\n"), \
                                   #rFromState, #rToState)); \
                   scanFsmStep(prAdapter, SCAN_NEXT_STATE_VAR); \
                }

#define SCAN_STATE_TRANSITION1(prAdapter, rFromState, rToState, rPostFix) \
                { \
                  scanFsmTransAction_ ## rFromState ## _to_ ## rToState ## _ ## rPostFix(prAdapter); \
                  SCAN_NEXT_STATE_VAR = SCAN_STATE_ ## rToState; \
                  DBGLOG(SCAN, TRACE, (("SCAN STATE TRANSITION: [%s] --> [%s]\n"), \
                                   #rFromState, #rToState)); \
                   scanFsmStep(prAdapter, SCAN_NEXT_STATE_VAR); \
                }


/*******************************************************************************
*                   F U N C T I O N   D E C L A R A T I O N S
********************************************************************************
*/
VOID
scanFsmInit (
    P_ADAPTER_T prAdapter
    );

WLAN_STATUS
scanFsmRunEventScanReqSetup (
    IN P_ADAPTER_T prAdapter,
    IN P_SCAN_REQ_CONFIG_T prScanReqConfig
    );

VOID
scanFsmRunEventScanReqCleanUp (
    IN P_ADAPTER_T prAdapter
    );

WLAN_STATUS
scanFsmRunEventStart (
    IN P_ADAPTER_T  prAdapter,
    IN ENUM_HW_SCAN_MODE_T eHwScanMode
    );

WLAN_STATUS
scanFsmRunEventScanDone (
    IN P_ADAPTER_T  prAdapter
    );

WLAN_STATUS
scanFsmRunEventScanAbort (
    IN P_ADAPTER_T  prAdapter
    );

WLAN_STATUS
scanFsmRunEventScanStop (
    IN P_ADAPTER_T  prAdapter
    );

VOID
scanCheckScanStatus (
    IN P_ADAPTER_T prAdapter
    );

VOID
scanSetupOriginalChannel (
    IN P_ADAPTER_T prAdapter,
    IN UINT_8      ucChannelNum,
    IN ENUM_BAND_T eBand
    );

/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/
#endif /* _SCAN_FSM_H */

