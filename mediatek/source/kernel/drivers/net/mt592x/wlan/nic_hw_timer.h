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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/nic_hw_timer.h#2 $
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
** $Log: nic_hw_timer.h $
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\15 2009-05-14 21:09:52 GMT mtk01104
**  Remove compiling warning in Linux
**  \main\maintrunk.MT5921\14 2009-05-13 15:26:55 GMT mtk01084
**  change another workaround to fix WPD00001530 HEC issue
**  \main\maintrunk.MT5921\13 2009-04-14 19:53:32 GMT mtk01084
**  do logic reset before scan is enabled
**  \main\maintrunk.MT5921\12 2008-10-27 14:24:49 GMT mtk01084
**  supporting continuous polling mode
**  \main\maintrunk.MT5921\11 2008-10-16 15:56:39 GMT mtk01461
**  Update driver to fix lint warning
**  \main\maintrunk.MT5921\10 2008-09-22 23:31:33 GMT mtk01461
**  Fix compile error in Linux
**  \main\maintrunk.MT5921\9 2008-08-18 09:21:29 GMT mtk01084
**  modification for coding rules conformance
**  \main\maintrunk.MT5921\8 2007-12-11 00:08:19 GMT mtk01461
**  Update function declarations
**  \main\maintrunk.MT5921\7 2007-10-25 21:42:18 GMT mtk01084
**  modfiy NIC_HW_TIMER_UNSET_VOIP_POLL_TIMER
**
*/

#ifndef _NIC_HW_TIMER_H
#define _NIC_HW_TIMER_H

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
#define WLAN_ROOT_TIMER     ENUM_TIMER_2
#define WLAN_ROOT_TIMER_INT INT_EVENT_T2_TIMEUP

#define VOIP_POLL_TIMER     ENUM_TIMER_3
#define VOIP_POLL_TIMER_INT INT_EVENT_T3_TIMEUP


/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/

/*******************************************************************************
*                            P U B L I C   D A T A
********************************************************************************
*/
/* Alternative function of Timers */
typedef enum _HW_TIMER_FUNC_E {
    HW_TIMER_FUNC_TSF_FREE_RUN,
    HW_TIMER_FUNC_TX_TRG_FRM,
    HW_TIMER_FUNC_TX_PS_POLL,
    HW_TIMER_FUNC_SAPSD,
    HW_TIMER_FUNC_TS,
    NUM_HW_TIMER_FUNCS
} HW_TIMER_FUNC_E, *P_HW_TIMER_FUNC_E;

/* Timers trigger mode */
typedef enum _HW_TIMER_MODE_E {
    HW_TIMER_MODE_ONE_SHOT,
    HW_TIMER_MODE_PERIODIC,
    NUM_HW_TIMER_MODES
} HW_TIMER_MODE_E, *P_HW_TIMER_MODE_E;

/* Timers unit */
typedef enum _HW_TIMER_UNIT_E {
    HW_TIMER_UNIT_1_US,
    HW_TIMER_UNIT_1_TU,
    NUM_HW_TIMER_UNITS
} HW_TIMER_UNIT_E, *P_HW_TIMER_UNIT_E;




//3 /* Session for CONNECTION SETTINGS */
typedef enum _ENUM_HW_TIMER_T {
    ENUM_TIMER_0,
    ENUM_TIMER_1,
    ENUM_TIMER_2,
    ENUM_TIMER_3,
    ENUM_TIMER_NUM
} ENUM_HW_TIMER_T, *P_ENUM_HW_TIMER_T;


typedef struct _TIMER_INFO_T {

    PFN_TIMER_CALLBACK apfHwTimerHandler[ENUM_TIMER_NUM];
    BOOLEAN     afgHwTimerInUsed[ENUM_TIMER_NUM];

} TIMER_INFO_T, *P_TIMER_INFO_T;


/*******************************************************************************
*                           P R I V A T E   D A T A
********************************************************************************
*/

/*******************************************************************************
*                                 M A C R O S
********************************************************************************
*/
#define NIC_HW_TIMER_SET_VOIP_POLL_TIMER(prAdapter, eFunc, u4Period, fgTimeupIntEn) \
    { \
        nichtSetTimer(prAdapter, \
                      VOIP_POLL_TIMER, \
                      HW_TIMER_MODE_PERIODIC, \
                      eFunc, \
                      fgTimeupIntEn, \
                      HW_TIMER_UNIT_1_TU, \
                      u4Period); \
        NIC_SET_INT_EVENT(prAdapter, VOIP_POLL_TIMER_INT); \
    }

#define NIC_HW_TIMER_UNSET_VOIP_POLL_TIMER(prAdapter) \
    { \
        UINT_32 u4Value; \
        HAL_MCR_RD(prAdapter, MCR_MPTCR, &u4Value); \
        u4Value |= (SPCR_PSPOLL_SP_INVALID_MASK | SPCR_TRIGGER_SP_INVALID_MASK); \
        HAL_MCR_WR(prAdapter, MCR_MPTCR, u4Value); \
        u4Value &= ~(SPCR_PSPOLL_SP_INVALID_MASK | SPCR_TRIGGER_SP_INVALID_MASK); \
        HAL_MCR_WR(prAdapter, MCR_MPTCR, u4Value); \
        nichtKillTimer(prAdapter, \
                      VOIP_POLL_TIMER); \
        NIC_UNSET_INT_EVENT(prAdapter, VOIP_POLL_TIMER_INT); \
    }
        /* Old work around method about WPD00001530, add logic reset
         * nicLogicReset(prAdapter) in above macro
         * NIC_HW_TIMER_UNSET_VOIP_POLL_TIMER()
         */


/*******************************************************************************
*                   F U N C T I O N   D E C L A R A T I O N S
********************************************************************************
*/
VOID
nichtTimerInit (
    IN P_ADAPTER_T prAdapter,
    IN ENUM_HW_TIMER_T rTimerId,
    IN PFN_TIMER_CALLBACK prfnTimeout
    );

VOID
nichtCancelTimer (
    IN P_ADAPTER_T prAdapter,
    IN ENUM_HW_TIMER_T rTimerId
    );

BOOL
nichtSetTimer (
    IN P_ADAPTER_T      prAdapter,
    IN ENUM_HW_TIMER_T  rTimerId,
    IN HW_TIMER_MODE_E  rMode,
    IN HW_TIMER_FUNC_E  rAltFunc,
    IN BOOLEAN          fgTimeupEn,
    IN HW_TIMER_UNIT_E  rUnit,
    IN UINT_32          u4Count
    );

BOOL
nichtSetTsfTimer (
    IN P_ADAPTER_T prAdapter,
    IN ENUM_HW_TIMER_T rTimerId,
    IN HW_TIMER_MODE_E  rMode,
    IN HW_TIMER_FUNC_E rAltFunc,
    IN BOOLEAN fgTimeupEn,
    IN UINT_32 u4StartTime,
    IN UINT_32 u4Period
    );

VOID
nichtKillTimer (
    IN P_ADAPTER_T prAdapter,
    IN ENUM_HW_TIMER_T rTimerId
    );

VOID
nicProcesT0TimeupInterrupt (
    IN P_ADAPTER_T      prAdapter
    );

VOID
nicProcesT1TimeupInterrupt (
    IN P_ADAPTER_T      prAdapter
    );

VOID
nicProcesT2TimeupInterrupt (
    IN P_ADAPTER_T      prAdapter
    );

VOID
nicProcesT3TimeupInterrupt (
    IN P_ADAPTER_T      prAdapter
    );

/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/
#endif /* _NIC_HW_TIMER_H */


