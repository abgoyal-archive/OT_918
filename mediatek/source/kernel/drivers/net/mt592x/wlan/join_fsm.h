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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/join_fsm.h#1 $
*/

/*! \file   join_fsm.h
    \brief  Declaration of functions and finite state machine for JOIN Module.

    Function declaration for join.c and JOIN_STATE for JOIN FSM.
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
** $Log: join_fsm.h $
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\10 2008-08-10 18:48:03 GMT mtk01461
**  Update for Driver Review
**  \main\maintrunk.MT5921\9 2008-07-07 13:24:19 GMT mtk01461
**  Minimize the Authentication retry count during roaming to save some time of try and error.
**  \main\maintrunk.MT5921\8 2008-05-03 12:55:09 GMT mtk01461
**  Update comment
**  \main\maintrunk.MT5921\7 2008-03-19 15:21:36 GMT mtk01461
**  Add maximum Join Retry Count
**  \main\maintrunk.MT5921\6 2008-03-13 15:31:41 GMT mtk01461
**  Refine the relationship between SCAN result and STA record, lifetime, aging policy etc
**  \main\maintrunk.MT5921\5 2007-10-25 17:59:19 GMT mtk01461
**  Add VOIP SCAN & Refine Roaming
** Revision 1.1.1.1  2007/06/22 08:09:05  MTK01461
** no message
**
*/


#ifndef _JOIN_FSM_H
#define _JOIN_FSM_H

/*******************************************************************************
*                         C O M P I L E R   F L A G S
********************************************************************************
*/

/*******************************************************************************
*                    E X T E R N A L   R E F E R E N C E S
********************************************************************************
*/
#include "gl_typedef.h"

/*******************************************************************************
*                              C O N S T A N T S
********************************************************************************
*/
#define AUTH_TYPE_OPEN_SYSTEM                       BIT(AUTH_ALGORITHM_NUM_OPEN_SYSTEM)
#define AUTH_TYPE_SHARED_KEY                        BIT(AUTH_ALGORITHM_NUM_SHARED_KEY)
#define AUTH_TYPE_FAST_BSS_TRANSITION               BIT(AUTH_ALGORITHM_NUM_FAST_BSS_TRANSITION)


#define TX_AUTH_ASSOCI_RETRY_LIMIT                  2

#define TX_AUTH_ASSOCI_RETRY_LIMIT_FOR_ROAMING      1

/* Retry interval for retransmiting authentication-request MMPDU. */
#define TX_AUTHENTICATION_RETRY_TIMEOUT_TU          100 // TU.

/* Retry interval for retransmiting association-request MMPDU. */
#define TX_ASSOCIATION_RETRY_TIMEOUT_TU             100 // TU.

/* Wait for a response to a transmitted authentication-request MMPDU. */
#define DOT11_AUTHENTICATION_RESPONSE_TIMEOUT_TU    512 // TU.

/* Wait for a response to a transmitted association-request MMPDU. */
#define DOT11_ASSOCIATION_RESPONSE_TIMEOUT_TU       512 // TU.

/* The maximum time to wait for JOIN process complete. */
#define JOIN_FAILURE_TIMEOUT_BEACON_INTERVAL        20 // Beacon Interval, 20 * 100TU = 2 sec.

/* Retry interval for next JOIN request. */
#define JOIN_RETRY_INTERVAL_SEC                     5 // Seconds

/* Maximum Retry Count for accept a JOIN request. */
#define JOIN_MAX_RETRY_FAILURE_COUNT                4 // Times

/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/
typedef enum _ENUM_JOIN_STATE_T {
    JOIN_STATE_IDLE = 0,
    JOIN_STATE_INIT,
    JOIN_STATE_SEND_AUTH1,
    JOIN_STATE_WAIT_AUTH2,
    JOIN_STATE_SEND_AUTH3,
    JOIN_STATE_WAIT_AUTH4,
    JOIN_STATE_SEND_ASSOC1,
    JOIN_STATE_WAIT_ASSOC2,
    JOIN_STATE_COMPLETE,
    JOIN_STATE_NUM
} ENUM_JOIN_STATE_T;

typedef struct _JOIN_INFO_T {
    ENUM_JOIN_STATE_T   eCurrentState;

    /* This is the pointer to the BSS description of target BSS chosen from SCAN result */
    P_BSS_DESC_T        prBssDesc;

    UINT_8              ucAvailableAuthTypes;
    UINT_8              ucRoamingAuthTypes;
    UINT_8              ucCurrAuthAlgNum;
    UINT_8              ucTxAuthAssocRetryCount;

    UINT_8              ucTxAuthAssocRetryLimit;

    /* A flag to indicate if we are going to do roaming in JOIN Module by using
     * ReAssoc Req Frame.
     */
    BOOLEAN             fgIsReAssoc;

    /* A flag to indicate if we already adopt the parameter of targeted BSS */
    BOOLEAN             fgIsParameterAdopted;


    TIMER_T             rJoinTimer;
    TIMER_T             rTxRequestTimer;
    TIMER_T             rRxResponseTimer;

} JOIN_INFO_T, *P_JOIN_INFO_T;

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
#define JOIN_STATE_TRANSITION_FLAG  fgIsTransition
#define JOIN_NEXT_STATE_VAR         eNextState

#define JOIN_STATE_TRANSITION(prAdapter, eFromState, eToState) \
            { joinFsmTransAction_ ## eFromState ## _to_ ## eToState((P_ADAPTER_T)prAdapter); \
              JOIN_NEXT_STATE_VAR = JOIN_STATE_ ## eToState; \
              JOIN_STATE_TRANSITION_FLAG = (BOOLEAN)TRUE; \
            }

/*******************************************************************************
*                  F U N C T I O N   D E C L A R A T I O N S
********************************************************************************
*/
VOID
joinFsmInit (
    IN P_ADAPTER_T prAdapter
    );

WLAN_STATUS
joinFsmSteps (
    IN P_ADAPTER_T prAdapter,
    IN ENUM_JOIN_STATE_T eNextState
    );

WLAN_STATUS
joinFsmRunEventStart (
    IN P_ADAPTER_T prAdapter,
    IN P_BSS_DESC_T prBssDesc
    );

VOID
joinFsmRunEventAbort (
    IN P_ADAPTER_T prAdapter
    );

WLAN_STATUS
joinFsmRunEventTxDone (
    IN P_ADAPTER_T prAdapter,
    IN P_MSDU_INFO_T prMsduInfo,
    IN WLAN_STATUS rTxDoneStatus
    );

WLAN_STATUS
joinFsmRunEventTxReqTimeOut (
    IN P_ADAPTER_T  prAdapter
    );

WLAN_STATUS
joinFsmRunEventRxRespTimeOut (
    IN P_ADAPTER_T  prAdapter
    );

WLAN_STATUS
joinFsmRunEventRxAuthAssoc (
    IN P_ADAPTER_T prAdapter,
    IN P_SW_RFB_T prSwRfb
    );

WLAN_STATUS
joinFsmRunEventJoinTimeOut (
    IN P_ADAPTER_T prAdapter
    );

VOID
joinAdoptParametersFromPeerBss (
    IN P_ADAPTER_T prAdapter
    );

VOID
joinAdoptParametersFromCurrentBss (
    IN P_ADAPTER_T prAdapter
    );

VOID
joinComplete (
    IN P_ADAPTER_T prAdapter
    );

/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/

#endif /* _JOIN_FSM_H */




