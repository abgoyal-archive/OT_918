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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/roaming_fsm.h#1 $
*/

/*! \file   roaming_fsm.h
    \brief  Declaration of functions and finite state machine for ROAMING Module.

    Function declaration for roaming_fsm.c and ROAMING_STATE for ROAMING FSM.
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
** $Log: roaming_fsm.h $
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\5 2009-02-18 19:16:45 GMT mtk01461
**  Add ROAMING_NO_SWING_RCPI_STEP for coding rule
**  \main\maintrunk.MT5921\4 2008-03-19 15:21:42 GMT mtk01461
**  Add adjust a smaller threshold bar for boundary case
**  \main\maintrunk.MT5921\3 2008-03-13 14:27:40 GMT mtk01461
**  Revise Roaming Module
**  \main\maintrunk.MT5921\2 2007-10-25 17:59:21 GMT mtk01461
**  Add VOIP SCAN & Refine Roaming
*/


#ifndef _ROAMING_FSM_H
#define _ROAMING_FSM_H

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
/* Roaming Stable timeout interval. */
#define ROAMING_STABLE_TIMEOUT_SEC                  7 // Seconds

/* Roaming Decision retry interval if the RCPI value was invalid */
#define ROAMING_DECISION_INVALID_RCPI_TIMEOUT_MSEC  100 // Milli Seconds.

/* Roaming Decision interval if we still can't handle the roaming decision request
 * after the Stable timeout or invalid RCPI timeout.
 */
#define ROAMING_DECISION_TIMEOUT_SEC                1 // Seconds.

/* Roaming Discovery interval, SCAN result need to be updated */
#define ROAMING_DISCOVERY_TIMEOUT_SEC               5 // Seconds.




/* Partial SCAN interval for Roaming Discovery */
#define ROAMING_PARTIAL_SCAN_TIMEOUT_MSEC           20 // Milliseconds.



/* Roaming Out retry interval if previous roaming out is failure or no available candidate. */
#define ROAMING_OUT_RETRY_TIMEOUT_SEC               20 // Second.


/* Roaming Out condition - In order to prevent SWING,
 * New AP's RCPI should better than current AP's RCPI, set a Step for it
 */
#define ROAMING_NO_SWING_RCPI_STEP                  10 // Step = 5dBm


// Received Channel Power Indicator
#define ROAMING_WLAN_RCPI_THRESHOLD                 80 // -70dBm, RCPI = (-70 + 110) x 2.
#define ROAMING_RCPI_STEP                           10 // Step = 5dBm

#define ROAMING_WLAN_RCPI_BOUNDARY_THRESHOLD        55 // -82.5dBm
#define ROAMING_RCPI_BOUNDARY_STEP                  4 // Step = 2dBm

#define ROAMING_GSM_RCPI_HIGH_THRESHOLD             74 // -73dBm, RCPI = (-73 + 110) x 2.
#define ROAMING_GSM_RCPI_LOW_THRESHOLD              70 // -75dBm, RCPI = (-75 + 110) x 2.


/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/
typedef enum _ENUM_ROAMING_STATE_T {
    ROAMING_STATE_IDLE = 0,
    ROAMING_STATE_DECISION,
    ROAMING_STATE_DISCOVERY,
    ROAMING_STATE_ROAM,
    ROAMING_STATE_NUM
} ENUM_ROAMING_STATE_T;


typedef struct _ROAMING_INFO_T {
    ENUM_ROAMING_STATE_T    eCurrentState;

    SCAN_REQ_CONFIG_T       rScanReqConfig;

    TIMER_T                 rRoamingDecisionTimer;

    TIMER_T                 rRoamingDiscoveryTimer;

    UINT_16                 u2DiscoveryTimeoutMillisecond;

    BOOLEAN                 fgIsScanTriggered;
    BOOLEAN                 fgIsScanCompleted;
    BOOLEAN                 fgIsRCPIEventEnabled;
    BOOLEAN                 fgIsRoamingFail;

    OS_SYSTIME              rRoamingDiscoveryUpdateTime;

} ROAMING_INFO_T, *P_ROAMING_INFO_T;

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
#define ROAMING_STATE_TRANSITION_FLAG   fgIsTransition
#define ROAMING_NEXT_STATE_VAR          eNextState

#define ROAMING_STATE_TRANSITION(prAdapter, eFromState, eToState) \
            { roamingFsmTransAction_ ## eFromState ## _to_ ## eToState((P_ADAPTER_T)prAdapter); \
              ROAMING_NEXT_STATE_VAR = ROAMING_STATE_ ## eToState; \
              ROAMING_STATE_TRANSITION_FLAG = (BOOLEAN)TRUE; \
            }

/*******************************************************************************
*                  F U N C T I O N   D E C L A R A T I O N S
********************************************************************************
*/
VOID
roamingFsmInit (
    IN P_ADAPTER_T prAdapter
    );

WLAN_STATUS
roamingFsmSteps (
    IN P_ADAPTER_T prAdapter,
    IN ENUM_ROAMING_STATE_T eNextState
    );

WLAN_STATUS
roamingFsmRunEventStart (
    IN P_ADAPTER_T prAdapter
    );

VOID
roamingFsmRunEventRoamFail (
    IN P_ADAPTER_T prAdapter
    );

VOID
roamingFsmRunEventAbort (
    IN P_ADAPTER_T prAdapter
    );

WLAN_STATUS
roamingFsmRunEventRCPI (
    IN P_ADAPTER_T prAdapter
    );

WLAN_STATUS
roamingFsmRunEventDecision (
    IN P_ADAPTER_T prAdapter
    );

WLAN_STATUS
roamingFsmRunEventDiscovery (
    IN P_ADAPTER_T prAdapter
    );

VOID
roamingDiscoveryScanDoneHandler (
    IN P_ADAPTER_T prAdapter,
    IN WLAN_STATUS rStatus
    );

VOID
roamingReTriggerEventDecision (
    IN P_ADAPTER_T prAdapter
    );

VOID
roamingReTriggerEventDiscovery (
    IN P_ADAPTER_T prAdapter
    );



/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/

#endif /* _ROAMING_FSM_H */

