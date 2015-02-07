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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/pta_fsm.h#1 $
*/

/*! \file   "pta_fsm.h"
    \brief  In this file we define the STATE and EVENT for PTA FSM.

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
** $Log: pta_fsm.h $
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\14 2009-09-22 22:51:15 GMT mtk01089
**  Use PTA_NEW_BOARD_DESIGN to seperate 1.26 code
**  \main\maintrunk.MT5921\13 2009-09-12 13:45:48 GMT mtk01089
**  Two sets of PTA setting are available for BWCS to switch
**  \main\maintrunk.MT5921\12 2009-01-07 17:35:57 GMT mtk01425
**  1. Add fgEnabled, rScoPtaParam, rAclPtaParam and rMixPtaParam to PTA_INFO_T
**  \main\maintrunk.MT5921\11 2008-10-31 13:54:20 GMT mtk01425
**  1. Add rBtProfile and rPtaParam to type PTA_INFO_T
**  \main\maintrunk.MT5921\10 2008-09-08 19:54:15 GMT mtk01104
**  Add new member "u4PTAWireMode" in PTA_INFO_T
**  \main\maintrunk.MT5921\9 2008-09-05 17:00:16 GMT mtk01104
**  Add "singleAntenna" member in PTA_INFO_T
**  \main\maintrunk.MT5921\8 2008-08-14 09:23:30 GMT mtk01104
**  Change function prototype of ptaFsmRunEventSetConfig()
**  \main\maintrunk.MT5921\7 2008-07-14 13:48:44 GMT mtk01104
**  Remove PTA_CTRL_STRUC_T to file wlan_oid.h
**  \main\maintrunk.MT5921\6 2008-06-19 10:13:18 GMT mtk01084
**  support OID for more detail about PTA settings
**  \main\maintrunk.MT5921\5 2008-06-03 20:21:01 GMT mtk01104
**  Define PTA_SW_WIRE_MODE
**  \main\maintrunk.MT5921\4 2008-05-30 23:11:31 GMT mtk01104
**  Define several types
** Revision 1.1  2007/07/04 01:20:23  MTK01385
** pta FSM related definition
**
**
*/

#ifndef _PTA_FSM_H
#define _PTA_FSM_H

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

/* BTCER1[30:29]=> 2'b00: 1-wire, 2'b01: 2-wire, 2'b10: 3-wire, 2'b11: 4-wire */
#define PTA_SW_WIRE_MODE        PTA_BTCER1_WIRE_MODE
#define PTA_SW_1_WIRE_MODE      0x00000000
#define PTA_SW_2_WIRE_MODE      BIT(29)
#define PTA_SW_3_WIRE_MODE      BIT(30)
#define PTA_SW_4_WIRE_MODE      (BIT(30) | BIT(29))

/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/

typedef enum _ENUM_PTA_STATE_T {
    PTA_STATE_IDLE = 0,
    PTA_STATE_ON,
    PTA_STATE_NUM
} ENUM_PTA_STATE_T;

typedef struct _PTA_INFO_T {
    ENUM_PTA_STATE_T    eCurrentState;
    UINT_32             u4PTAWireMode;      /* PTA_SW_1_WIRE_MODE and so on */
    BOOLEAN             fgSingleAntenna;
    BOOLEAN             fgEnabled;
    PTA_PROFILE_T       rBtProfile;
    PTA_PARAM_T	        rPtaParam;
    /* new board setting takes two sets of PTA settings */
#if PTA_NEW_BOARD_DESIGN
    PTA_PARAM_T	        rDualAclPtaParam;
    PTA_PARAM_T	        rDualMixPtaParam;
    PTA_PARAM_T	        rSingleAclPtaParam;
    PTA_PARAM_T	        rSingleMixPtaParam;
#else
    PTA_PARAM_T	        rScoPtaParam;
    PTA_PARAM_T	        rAclPtaParam;
    PTA_PARAM_T	        rMixPtaParam;
#endif
} PTA_INFO_T, *P_PTA_INFO_T;

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

#define PTA_STATE_TRANSITION(prAdapter, rFromState, rToState) \
            { /* ptaFsmTransAction_ ## rFromState ## _to_ ## rToState((P_ADAPTER_T)prAdapter);*/ \
              eNextState = PTA_STATE_ ## rToState; \
              DBGLOG(INIT, TRACE, (("PTA STATE TRANSITION: [%s] --> [%s]\n"), \
                                   #rFromState, #rToState)); \
            }

/*******************************************************************************
*                   F U N C T I O N   D E C L A R A T I O N S
********************************************************************************
*/

/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/

VOID
ptaFsmInit (
    IN P_ADAPTER_T prAdapter
    );

VOID
ptaFsmRunEventSetConfig (
    IN P_ADAPTER_T          prAdapter,
    IN P_PTA_PARAM_T        prPtaParam
    );

#endif /* _PTA_FSM_H */


