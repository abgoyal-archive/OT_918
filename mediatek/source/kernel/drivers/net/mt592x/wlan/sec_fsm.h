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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/sec_fsm.h#2 $
*/

/*! \file   sec_fsm.h
    \brief  Declaration of functions and finite state machine for SECURITY Module.

    Function declaration for privacy.c and SEC_STATE for SECURITY FSM.
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
** $Log: sec_fsm.h $
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\14 2009-04-06 15:35:47 GMT mtk01088
**  add the variable to set the disable AP selection for privacy check, for wps open networking.
**  \main\maintrunk.MT5921\13 2008-11-19 11:46:01 GMT mtk01088
**  rename some variable with pre-fix to avoid the misunderstanding
**  \main\maintrunk.MT5921\12 2008-08-28 20:37:11 GMT mtk01088
**  remove non-used code
**  
**  \main\maintrunk.MT5921\11 2008-03-18 09:51:52 GMT mtk01088
**  Add function declaration for timer to indicate pmkid candidate
**  \main\maintrunk.MT5921\10 2008-02-29 15:12:08 GMT mtk01088
**  add variable for sw port control
**  \main\maintrunk.MT5921\9 2008-02-29 12:37:30 GMT mtk01088
**  rename the security related function declaration
**  \main\maintrunk.MT5921\8 2007-12-27 13:59:08 GMT mtk01088
**  adjust the wlan table and sec fsm init timing
**  \main\maintrunk.MT5921\7 2007-11-20 10:39:49 GMT mtk01088
**  add function timer for wait EAPoL Error timeout 
**  \main\maintrunk.MT5921\6 2007-11-06 20:39:08 GMT mtk01088
**  rename the counter measure timer
**  \main\maintrunk.MT5921\5 2007-11-06 20:14:31 GMT mtk01088
**  add a abort function
** Revision 1.5  2007/07/16 02:33:42  MTK01088
** change the ENUM declaration structure prefix from r to e
**
** Revision 1.4  2007/07/09 06:23:10  MTK01088
** update
**
** Revision 1.3  2007/07/04 10:09:04  MTK01088
** adjust the state for security fsm
** change function name
**
** Revision 1.2  2007/07/03 08:13:22  MTK01088
** change the sec fsm state
** add the event for sec fsm
**
** Revision 1.1  2007/06/27 06:20:35  MTK01088
** add the sec fsm header file
**
**
*/
#ifndef _SEC_FSM_H
#define _SEC_FSM_H

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

/* TKIP CounterMeasure interval for Rejoin to Network. */
#define COUNTER_MEASURE_TIMEOUT_INTERVAL_SEC        60

/* Timeout to wait the EAPoL Error Report frame Send out. */
#define EAPOL_REPORT_SEND_TIMEOUT_INTERVAL_SEC       1

/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/
typedef UINT_32             SEC_STATUS, *P_SEC_STATUS;

typedef enum _ENUM_SEC_STATE_T {
    SEC_STATE_IDLE = 0,
    SEC_STATE_PORT_CONTROL,
    SEC_STATE_FIFO_BUSY,
    SEC_STATE_CHECK_OK,
    SEC_STATE_SEND_EAPOL,
    SEC_STATE_SEND_DEAUTH,
    SEC_STATE_NUM
} ENUM_SEC_STATE_T;

/* WPA2 PMKID candicate structure */
typedef struct _PMKID_CANDICATE_T {
    PARAM_MAC_ADDRESS   arBssid;
    UINT_32             u4PreAuthFlags;
} PMKID_CANDICATE_T, *P_PMKID_CANDICATE_T;

/* WPA2 PMKID cache structure */
typedef struct _PMKID_ENTRY_T {
    PARAM_BSSID_INFO_T  rBssidInfo;
    BOOLEAN             fgPmkidExist;
} PMKID_ENTRY_T, *P_PMKID_ENTRY_T;

typedef struct _SEC_INFO_T {
    ENUM_SEC_STATE_T   eCurrentState;

    /* Stored the current bss wpa rsn cap filed, used for roaming policy */
    BOOLEAN                 fgWpaCapPresent;
    UINT_16                 u2WpaCap;
    UINT_16                 u2RsnCap;
    
    /* While Do CounterMeasure procedure, check the EAPoL Error report have send out */
    BOOLEAN                 fgCheckEAPoLTxDone;

    UINT_32                 u4RsnaLastMICFailTime;

    /* Boolean flag to let port control check only T/R AP or include DLS */
    BOOLEAN                 fgBlockOnlyAPTraffic;

    BOOLEAN                 fgBlockTxTraffic;
    BOOLEAN                 fgBlockRxTraffic;

    /* By the flow chart of 802.11i, 
               wait 60 sec before associating to same AP 
               or roaming to a new AP
               or sending data in IBSS,
               keep a timer for handle the 60 sec counterMeasure */
    TIMER_T                 rRsnaBlockTrafficTimer;
#if DBG
    BOOLEAN                 fgRsnaEAPoLReportState;
#endif
    TIMER_T                 rRsnaEAPoLReportTimeoutTimer;

    TIMER_T                 rPreauthenticationTimer;

    /* Buffer for WPA2 PMKID */
    /* The PMKID cache lifetime is expire by media_disconnect_indication */
    UINT_32                 u4PmkidCandicateCount;
    PMKID_CANDICATE_T       arPmkidCandicate[CFG_MAX_PMKID_CACHE];
    UINT_32                 u4PmkidCacheCount;
    PMKID_ENTRY_T           arPmkidCache[CFG_MAX_PMKID_CACHE];
    BOOLEAN                 fgIndicatePMKID;

    /* CR1486, CR1640 */
    /* for WPS, disable the privacy check for AP selection policy */
    BOOLEAN                 fgPrivacyCheckDisable;
} SEC_INFO_T, *P_SEC_INFO_T;


typedef SEC_STATUS (*PFN_SEC_FSM_STATE_HANDLER)(IN P_ADAPTER_T);


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
#define SEC_STATE_TRANSITION_FLAG   fgIsTransition
#define SEC_NEXT_STATE_VAR          eNextState

#define SEC_STATE_TRANSITION(prAdapter, eFromState, eToState) \
                { secFsmTransAction_ ## eFromState ## _to_ ## eToState((P_ADAPTER_T)prAdapter); \
                  SEC_NEXT_STATE_VAR = SEC_STATE_ ## eToState; \
                  SEC_STATE_TRANSITION_FLAG = (BOOLEAN)TRUE; \
                }

/*******************************************************************************
*                  F U N C T I O N   D E C L A R A T I O N S
********************************************************************************
*/

/*--------------------------------------------------------------*/
/* Routines to handle the sec check                             */
/*--------------------------------------------------------------*/
/***** Routines in sec_fsm.c *****/
VOID
secFsmInit(
    IN P_ADAPTER_T          prAdapter
    );

VOID
secFsmRunEventInit(
    IN P_ADAPTER_T          prAdapter
    );

VOID
secFsmRunEventStart(
    IN P_ADAPTER_T          prAdapter
    );

VOID
secFsmRunEventAbort(
    IN P_ADAPTER_T          prAdapter
    );

BOOLEAN
secFsmRunEventPTKInstalled(
    IN P_ADAPTER_T          prAdapter,
    IN PUINT_8              pucBssid,
    IN PUINT_8              pucKeyMaterial,
    IN UINT_8               ucKeyLen,
    IN UINT_8               ucCipherMode,
    IN UINT_8               ucTxMicOffset,
    IN UINT_8               ucRxMicOffset
    );

VOID
secFsmRunEventFifoEmpty(
    IN P_ADAPTER_T          prAdapter
    );

VOID
secFsmRunEventEapolTxDone(
    IN P_ADAPTER_T           prAdapter

    );

VOID
secFsmRunEventDeauthTxDone(
    IN P_ADAPTER_T           prAdapter

    );

VOID
secFsmRunEventStartCounterMeasure(
    IN P_ADAPTER_T           prAdapter
    );

VOID
secFsmRunEventEndOfCounterMeasure(
    IN P_ADAPTER_T          prAdapter
    );

/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/
#endif /* _SEC_FSM_H */


