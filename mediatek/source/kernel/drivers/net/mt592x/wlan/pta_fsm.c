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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/pta_fsm.c#2 $
*/

/*! \file   "pta_fsm.c"
    \brief  This is the file implement PTA state machine.

    In PTA module, the state machine handle state transition
    and set the related configuration to hardware.
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
** $Log: pta_fsm.c $
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\19 2009-09-22 22:52:44 GMT mtk01089
**  Use PTA_NEW_BOARD_DESIGN to seperate 1.26 code
**  \main\maintrunk.MT5921\18 2009-09-12 13:46:05 GMT mtk01089
**  BWCS changes it's OID structure information.
**  \main\maintrunk.MT5921\17 2009-08-06 16:43:25 GMT mtk01090
**  Use GPIO0 and GPIO2 to control antenna switch and remove obsolete compile flag CFG_SUPPORT_SINGLE_ANTENNA
**  \main\maintrunk.MT5921\16 2009-02-18 16:44:16 GMT mtk01084
**  Enhancement of the BT SCO voico quality when MT5921 enter LP
**  \main\maintrunk.MT5921\15 2009-01-07 17:41:17 GMT mtk01425
**  1. Use prPtaInfo->fgEnabled to decide to enable PTA function
**  \main\maintrunk.MT5921\14 2008-12-01 18:30:18 GMT mtk01088
**  Suspicious use of &
**  \main\maintrunk.MT5921\13 2008-11-28 15:24:53 GMT mtk01088
**  fixed lint warning
**  \main\maintrunk.MT5921\12 2008-11-24 21:04:34 GMT mtk01425
**  1. Add PTA_ENABLED flag
**  \main\maintrunk.MT5921\11 2008-11-13 20:43:28 GMT mtk01104
**  Fix some lint warning
**  \main\maintrunk.MT5921\10 2008-10-31 16:08:12 GMT mtk01425
**  1. Modify ptaFsmInit to use nicPtaSetProfile to configure PTA
**  2. Move MCR operations from ptaFsmRunEventSetConfig to nicPtaSetConfig
**  \main\maintrunk.MT5921\9 2008-10-16 15:56:23 GMT mtk01461
**  Update driver to fix lint warning
**  \main\maintrunk.MT5921\8 2008-09-10 15:57:13 GMT mtk01104
**  Set input/output mode of ant_sel_p and ant_sel_n based on single antenna is used or not.
**  \main\maintrunk.MT5921\7 2008-09-08 19:55:01 GMT mtk01104
**  Invoke new function prototype nicPTASetConfig()
**  \main\maintrunk.MT5921\6 2008-09-05 21:06:06 GMT mtk01104
**  Invoke NIC_PM_PROGRAM_LP_INSRUCTION() to support single antenna
**  \main\maintrunk.MT5921\5 2008-08-14 09:25:50 GMT mtk01104
**  Change function prototype of ptaFsmRunEventSetConfig()
**  \main\maintrunk.MT5921\4 2008-07-14 13:53:34 GMT mtk01104
**  Fix bug: Restore input BTCR1 in ptaFsmRunEventSetConfig()
**  \main\maintrunk.MT5921\3 2008-05-30 23:39:43 GMT mtk01104
**  Define and process wire mode
** Revision 1.2  2007/07/04 07:02:34  MTK01385
** modify code to apply coding rule.
**
** Revision 1.1  2007/07/04 01:37:55  MTK01385
** add PTA FSM functions
**
**
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
#if PTA_ENABLED

/*----------------------------------------------------------------------------*/
/*!
* \brief This function will do initialization of PTA FSM.
*
* \param[in] prAdapter      Pointer of Adapter Data Structure
*
* \return none
*/
/*----------------------------------------------------------------------------*/
VOID
ptaFsmInit (
    IN P_ADAPTER_T prAdapter
    )
{
    P_PTA_INFO_T        prPtaInfo;

    ASSERT(prAdapter);

    prPtaInfo = &prAdapter->rPtaInfo;
    prPtaInfo->eCurrentState = PTA_STATE_IDLE;

    kalMemCopy(prPtaInfo->rBtProfile.u.au4Btcr, &prPtaInfo->rPtaParam, sizeof(PTA_PARAM_T));
#if PTA_NEW_BOARD_DESIGN
    /*  BWCS changes OID structure information. need to specify dual or single setting */
    prPtaInfo->rBtProfile.u.aucBTPParams[BTPPARAM_PTA_MODE_OFFSET] = 
        BTPPARAM_PTA_MODE_VALID | BTPPARAM_PTA_MODE_DUAL;
#endif
    nicPTASetProfile(prAdapter, (P_PTA_PROFILE_T)&prPtaInfo->rBtProfile);

    return;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief The Core FSM engine of PTA module.
*
* \param[in] prAdapter      Pointer of Adapter Data Structure
* \param[in] rNextState     Enum value of next sec STATE
*
* \return -
*/
/*----------------------------------------------------------------------------*/
VOID
ptaFsmSteps (
    IN P_ADAPTER_T      prAdapter,
    IN ENUM_PTA_STATE_T eNextState
    )
{
    P_PTA_INFO_T     prPtaInfo;

    ASSERT(prAdapter);
    prPtaInfo = &prAdapter->rPtaInfo;
    prPtaInfo->eCurrentState = eNextState;
    return;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This function processes the Event of "SetConfig" to PTA FSM.
*        And record single or dual antenna setting, too.
*
* \param[in] prAdapter   Pointer of Adapter Data Structure
* \param[in] prPtaParam  Pointer to the PTA control parameters
*
* \retval none
*/
/*----------------------------------------------------------------------------*/
VOID
ptaFsmRunEventSetConfig (
    IN P_ADAPTER_T          prAdapter,
    IN P_PTA_PARAM_T        prPtaParam
    )
{
    P_PTA_INFO_T        prPtaInfo;
    ENUM_PTA_STATE_T    eNextState;
    P_CONNECTION_SETTINGS_T prConnSettings;
    P_PM_INFO_T                 prPmInfo;


    ASSERT(prAdapter && prPtaParam);
    prPtaInfo = &prAdapter->rPtaInfo;
    eNextState = prPtaInfo->eCurrentState;
    prConnSettings = &prAdapter->rConnSettings;
    prPmInfo = &prAdapter->rPmInfo;

    kalMemCopy(&prConnSettings->rPtaParam, prPtaParam, sizeof(PTA_PARAM_T));
    kalMemCopy(&prPtaInfo->rPtaParam, prPtaParam, sizeof(PTA_PARAM_T));

    if (prPtaInfo->fgEnabled) {
        prPtaParam->u4BtCR0 |= PTA_BTCER0_COEXIST_EN;
    } else {
        prPtaParam->u4BtCR0 &= ~PTA_BTCER0_COEXIST_EN;
    }

    nicPTASetConfig(prAdapter, prPtaParam, &prPtaInfo->u4PTAWireMode);

    switch(prPtaInfo->eCurrentState) {
    case PTA_STATE_IDLE:
        if (prPtaParam->u4BtCR0 & PTA_BTCER0_COEXIST_EN) {
            PTA_STATE_TRANSITION(prAdapter, IDLE, ON);
        }
        break;

    case PTA_STATE_ON:
        if ( !(prPtaParam->u4BtCR0 & PTA_BTCER0_COEXIST_EN)) {
            PTA_STATE_TRANSITION(prAdapter, ON, IDLE);
        }
        break;

    default:
        ASSERT(0);
    }

    /* Call ptaFsmSteps() when we are going to change PTA STATE */
    if (prPtaInfo->eCurrentState != eNextState) {
        ptaFsmSteps(prAdapter, eNextState);
    }

    /* Notify LP module to modify LP instruction */
    NIC_PM_PROGRAM_LP_INSRUCTION(prAdapter, prPmInfo->fgIsContinousPollingEnabled);
#if PTA_NEW_BOARD_DESIGN
    /* no need to specify antenna here. BWCS will set OID */
#else
    /* GeorgeKuo(20090805): new single-antenna design */
    if (prPtaInfo->fgSingleAntenna) {
        nicPtaSetAnt(prAdapter, FALSE);
    }
    else {
        nicPtaSetAnt(prAdapter, TRUE);
    }
#endif
    return;
}

#endif
