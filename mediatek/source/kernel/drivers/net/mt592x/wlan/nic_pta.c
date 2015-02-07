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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/nic_pta.c#2 $
*/

/*! \file   nic_pta.c
    \brief  Functions that provide PTA operation in NIC's point of view.

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
** $Log: nic_pta.c $
 *
 * 06 10 2010 jim.zhang
 * [ALPS00008051]change mt592x to UNGPL version 
 * .
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\27 2009-09-29 22:56:38 GMT mtk01090
**  Fix assert fail in single antenna disabled case.
**  \main\maintrunk.MT5921\26 2009-09-28 22:22:58 GMT mtk01090
**  Fix compile error in Linux driver
**  \main\maintrunk.MT5921\25 2009-09-22 23:24:17 GMT mtk01089
**  fix compiling error
**  \main\maintrunk.MT5921\24 2009-09-22 22:53:51 GMT mtk01089
**  Use PTA_NEW_BOARD_DESIGN to seperate 1.26 code
**  \main\maintrunk.MT5921\23 2009-09-22 17:45:35 GMT mtk01089
**  Fix ASSERT during initialization
**  \main\maintrunk.MT5921\22 2009-09-12 13:46:25 GMT mtk01089
**  Allow BWCS to control antenna path
**  \main\maintrunk.MT5921\21 2009-08-06 16:44:02 GMT mtk01090
**  Use GPIO0 and GPIO2 to control antenna switch and remove obsolete compile flag CFG_SUPPORT_SINGLE_ANTENNA
**  \main\maintrunk.MT5921\20 2009-04-01 16:44:55 GMT mtk01104
**  Restore ant_p and ant_n to HW control
**  \main\maintrunk.MT5921\19 2009-03-11 13:11:54 GMT mtk01104
**  Remove power saving mode and continuous polling in function
**  nicPTASetProfile()
**  \main\maintrunk.MT5921\18 2009-01-21 23:11:02 GMT mtk01104
**  Fix bug: wrong setting when registry BTCR1[28] is 1 and dual
**  antenna is used
**  \main\maintrunk.MT5921\17 2009-01-15 20:40:36 GMT mtk01104
**  Check u4ContPollIntv before calling pmEnableContinuousPollingFunc()
**  \main\maintrunk.MT5921\16 2009-01-15 14:04:54 GMT mtk01104
**  Process new profile BT_PROFILE_NO_CONNECTION and let system
**  disable continuous polling and restore PSP
**
**  \main\maintrunk.MT5921\15 2009-01-12 14:42:42 GMT mtk01104
**  1. Antenna output/input mode regardless of PTA state
**  2. Single antenna in BTCER1 shall be disabled if PTA is disabled
**  \main\maintrunk.MT5921\14 2009-01-07 17:30:20 GMT mtk01425
**  [BWCS Improvement]
**  1. Remove hard-coded PTA profile setting
**  2. Make the PTA on/off by the variable prPtaInfo->fgEnabled
**  3. Add nicPtaSetFunc
**  \main\maintrunk.MT5921\13 2008-12-08 21:29:31 GMT mtk01461
**  Remove Lint Warning
**  \main\maintrunk.MT5921\12 2008-12-08 17:23:01 GMT mtk01425
**  1. make the pta setting synchronized
**  \main\maintrunk.MT5921\11 2008-12-01 18:21:12 GMT mtk01088
**  fixed the lint "possible using null pointer" warning
**  \main\maintrunk.MT5921\10 2008-11-13 20:44:14 GMT mtk01104
**  Fix some lint warning
**  \main\maintrunk.MT5921\9 2008-10-31 14:16:32 GMT mtk01425
**  1. Add static data const PTA_PARAM_T arBtProfileSetting[] for built-in pta profile setting
**
**  2. Move MCR operations from ptaFsmEventSetConfig to nicPTASetConfig
**
**  3. Add new functions: nicPTASetProfile, nicPTAUpdateParams and nicPtaGetProfile
**  \main\maintrunk.MT5921\8 2008-09-08 19:55:31 GMT mtk01104
**  nicPTASetConfig() return wire-mode
**  \main\maintrunk.MT5921\7 2008-08-14 09:26:50 GMT mtk01104
**  Change function prototype of nicPTASetConfig()
**  \main\maintrunk.MT5921\6 2008-08-02 16:15:52 GMT mtk01104
**  Add assert to check if GPIO1 daisy chain and 4-wire PTA functions are
**  used simultaneously
**  \main\maintrunk.MT5921\5 2008-07-14 14:00:00 GMT mtk01104
**  Fix bug: restore input BTCR1 when invoking nicPTASetConfig()
**  \main\maintrunk.MT5921\4 2008-06-03 20:22:44 GMT mtk01104
**  Change BTCR1[30:29] mode definition
**  \main\maintrunk.MT5921\3 2008-05-30 23:41:41 GMT mtk01104
**  Define and process wire mode
** Revision 1.1  2007/07/04 01:38:46  MTK01385
** add PTA NIC layter function.
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
*                  F U N C T I O N   D E C L A R A T I O N S
********************************************************************************
*/

/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/

/*----------------------------------------------------------------------------*/
/*!
*
* \brief This routine is called to set PTA configuration to NIC.
*        BTCER0.CoExist_en bit will be set to 0.
*
* \param[in]  prAdapter         Pointer to the Adapter structure
* \param[in]  prPtaParam        Pointer to the PTA control parameters
* \param[out] pu4PTAWireMode    PTA 1/2/3/4 wire mode
*
* \retval none
*
* \note
*/
/*----------------------------------------------------------------------------*/
VOID
nicPTASetConfig (
    IN  P_ADAPTER_T         prAdapter,
    IN  P_PTA_PARAM_T       prPtaParam,
    OUT PUINT_32            pu4PTAWireMode
    )
{
    UINT_32         u4Ioudr, u4Scr, u4Mode, u4BtCR1;
    P_PTA_INFO_T    prPtaInfo;

    DEBUGFUNC("nicPTASetConfig");

    ASSERT(prAdapter && prPtaParam);
    ASSERT(pu4PTAWireMode);

    prPtaInfo = &prAdapter->rPtaInfo;

    *pu4PTAWireMode = PTA_SW_1_WIRE_MODE;

    /* When PTA is disabled, signle ant shall be set to 0 */
    prPtaParam->u4BtCR1 &= ~PTA_BTCER1_SINGLE_ANT;
    if (prPtaInfo->fgEnabled) {
        prPtaParam->u4BtCR0 |= PTA_BTCER0_COEXIST_EN;
    }
    else {
        prPtaParam->u4BtCR0 &= ~PTA_BTCER0_COEXIST_EN;
    }
    u4BtCR1 = prPtaParam->u4BtCR1;

    /* Disable PTA before any change */
    halPTACtrl(prAdapter, FALSE);

    HAL_MCR_RD(prAdapter, MCR_IOUDR, &u4Ioudr);
    HAL_MCR_RD(prAdapter, MCR_SCR, &u4Scr);
    u4Ioudr = (u4Ioudr & ~(IOUDR_BT_PRI_PU | IOUDR_BT_PRI_PD))
                | IOUDR_BT_PRI_PD; /* bt_pr: pull low */

	//Renbang : GPIO0 is used as single ant switch config, we should not config it here
    //u4Scr = u4Scr & ~(SCR_GPIO0_ENABLE_OUTPUT_MODE | SCR_BT_ACT_SEL |
    //        SCR_GPIO1_ENABLE_OUTPUT_MODE | SCR_BTFREQ_SEL); /* gpio0~1: GPI */
    u4Scr = u4Scr & ~( SCR_BT_ACT_SEL | SCR_GPIO1_ENABLE_OUTPUT_MODE | SCR_BTFREQ_SEL); /* gpio0~1: GPI */    

    /* Check if PTA will be in disabled mode */
    if (!prPtaInfo->fgEnabled) {
        HAL_MCR_WR(prAdapter, MCR_IOUDR, u4Ioudr);
        HAL_MCR_WR(prAdapter, MCR_SCR, u4Scr);
       // return;
    }
    else {
    /* Configure GPIO0~1 and BT_PRI based on PTA mode selection
     * SW define these two bits different from HW register definition
     * 2'b00: 1-wire, 2'b01: 2-wire, 2'b10: 3-wire, 2'b11: 4-wire
     */
        u4Mode = u4BtCR1 & PTA_SW_WIRE_MODE;
        prPtaParam->u4BtCR1 &= ~PTA_BTCER1_WIRE_MODE;    /* 1-wire */
        switch (u4Mode) {
        case (PTA_SW_4_WIRE_MODE):    /* 4 wire */
            ASSERT((prAdapter->rEEPROMCtrl.ucDaisyChain & EEPROM_DAISY_GPIO1_MASK)
               == EEPROM_DAISY_GPIO1_UNSPEC);
            /* GeorgeKuo(20090805): new single-antenna design. Single-antenna
             * uses GPIO0 to control antenna switch, which is incompatible with
             * PTA 4-wire mode.
             */
            ASSERT(prPtaInfo->fgSingleAntenna == FALSE);

            prPtaParam->u4BtCR1 |= PTA_BTCER1_4_WIRE_MODE;
            u4Scr = u4Scr | (SCR_BTFREQ_SEL | SCR_BT_ACT_SEL);
            break;

        case (PTA_SW_3_WIRE_MODE):         /* 3 wire (not defined in HW) */
            /* GeorgeKuo(20090805): new single-antenna design. Single-antenna
             * uses GPIO0 to control antenna switch, which is incompatible with
             * PTA 3-wire mode.
             */
            ASSERT(prPtaInfo->fgSingleAntenna == FALSE);
            prPtaParam->u4BtCR1 |= PTA_BTCER1_3_WIRE_MODE;
            u4Scr = u4Scr | SCR_BT_ACT_SEL;
            break;
        case (PTA_SW_2_WIRE_MODE):         /* 2 wire */
            /* GeorgeKuo(20090805): new single-antenna design. Single-antenna
             * uses GPIO0 and GPIO2 to control antenna switch.
             */
#if PTA_NEW_BOARD_DESIGN
            if(prPtaInfo->fgSingleAntenna){
            u4Scr |= SCR_GPIO0_ENABLE_OUTPUT_MODE | SCR_GPIO2_ENABLE_OUTPUT_MODE;
            }
#endif
            prPtaParam->u4BtCR1 |= PTA_BTCER1_2_WIRE_MODE;
            break;
        default:                /* 1 wire (00, 0x defined in HW) */
            /* GeorgeKuo(20090805): new single-antenna design. Single-antenna
             * uses GPIO0 and GPIO2 to control antenna switch.
             */
#if PTA_NEW_BOARD_DESIGN
            if(prPtaInfo->fgSingleAntenna){
            u4Scr |= SCR_GPIO0_ENABLE_OUTPUT_MODE | SCR_GPIO2_ENABLE_OUTPUT_MODE;
            }
#endif
            /* Not pull low/high */
            u4Ioudr &= ~(IOUDR_BT_PRI_PU | IOUDR_BT_PRI_PD);
            break;
        }
        *pu4PTAWireMode = u4Mode;

        HAL_MCR_WR(prAdapter, MCR_IOUDR, u4Ioudr);
        HAL_MCR_WR(prAdapter, MCR_SCR, u4Scr);
    }

    /* Set 4 BT registers including antenna, and PTA is still disabled */
    halPTASetConfig(prAdapter, prPtaParam);
    if (prPtaInfo->fgEnabled) {
        halPTACtrl(prAdapter, TRUE);
    }

    /* Restore input value of u4BtCR1 (important) */
    prPtaParam->u4BtCR1 = u4BtCR1;

#if PTA_NEW_BOARD_DESIGN
    /* ANT_SEL_P_N is no longer used to control ANT switch */
#else
    //4 2008/10/30, mikewu, moved here from fsm_pta.c
    HAL_MCR_RD(prAdapter, MCR_IOPCR, &u4Ioudr);
    if (prPtaInfo->fgSingleAntenna) { /* Single antenna */
        HAL_MCR_WR(prAdapter, MCR_IOPCR,
            u4Ioudr | (IOPCR_IO_ANT_SEL_P_DIR | IOPCR_IO_ANT_SEL_N_DIR));
    }
    else { /* Dual antenna */
        HAL_MCR_WR(prAdapter, MCR_IOPCR,
            u4Ioudr & ~(IOPCR_IO_ANT_SEL_P_DIR | IOPCR_IO_ANT_SEL_N_DIR));
    }
    /* Workaround for single antenna because initial time is long
     * The SW mode of antenna control is set in function nicInitializeChip().
     */
    /* GeorgeKuo(20090805): new single-antenna design. */
    if (prPtaInfo->fgSingleAntenna) { /* Single antenna */
        nicPtaSetAnt(prAdapter, FALSE);
    }
    else {
        nicPtaSetAnt(prAdapter, TRUE);
    }

#endif
    return;
}

/*----------------------------------------------------------------------------*/
/*!
*
* \brief This routine is called to set PTA Profile
*        The control of power saving mode and continuous polling is set
*        by corresponding OID from uppler layer. Remove them here.
*
* \param[in]  prAdapter         Pointer to the Adapter structure
* \param[in]  prPtaProfile      The profile setting
*
* \retval none
*
* \note
*/
/*----------------------------------------------------------------------------*/
VOID
nicPTASetProfile (
    IN  P_ADAPTER_T         prAdapter,
    IN  P_PTA_PROFILE_T     prPtaProfile
    )
{
    P_PTA_INFO_T            prPtaInfo;
    PTA_PARAM_T		        rPtaParam;
    P_CONNECTION_SETTINGS_T prConnSetting;

    ASSERT(prAdapter);
    prPtaInfo = &prAdapter->rPtaInfo;
    prConnSetting = &prAdapter->rConnSettings;

    /* Ignore unknown profile */
    if (prPtaProfile->eBtProfile >= BT_PROFILE_NUM) {
        return;
    }

    ASSERT(prPtaProfile);
    kalMemCopy(&prPtaInfo->rBtProfile, prPtaProfile, sizeof(PTA_PROFILE_T));

#if PTA_NEW_BOARD_DESIGN
    /* prPtaProfile->eBtProfile == BT_PROFILE_CUSTOM
     */
    if (prPtaProfile->eBtProfile == BT_PROFILE_CUSTOM) {
        ptaFsmRunEventSetConfig(prAdapter,
                                (P_PTA_PARAM_T)prPtaProfile->u.au4Btcr);
        return;
    }


    ASSERT((prPtaProfile->eBtProfile == BT_PROFILE_ACL) ||
        (prPtaProfile->eBtProfile == BT_PROFILE_MIXED));

    if (prPtaProfile->eBtProfile == BT_PROFILE_ACL) {
        //ASSERT(prPtaProfile->u.aucBTPParams[BTPPARAM_PTA_MODE_OFFSET] & BTPPARAM_PTA_MODE_VALID);

        //Find correct parameters
        if(prPtaProfile->u.aucBTPParams[BTPPARAM_PTA_MODE_OFFSET] & BTPPARAM_PTA_MODE_VALID){
            if((prPtaProfile->u.aucBTPParams[BTPPARAM_PTA_MODE_OFFSET] & BTPPARAM_PTA_MODE_DUAL) == BTPPARAM_PTA_MODE_DUAL){
                kalMemCopy(&rPtaParam, (PVOID)&prPtaInfo->rDualAclPtaParam, sizeof(PTA_PARAM_T));
            }

            if((prPtaProfile->u.aucBTPParams[BTPPARAM_PTA_MODE_OFFSET] & BTPPARAM_PTA_MODE_DUAL) == BTPPARAM_PTA_MODE_SINGLE){
                kalMemCopy(&rPtaParam, (PVOID)&prPtaInfo->rSingleAclPtaParam, sizeof(PTA_PARAM_T));
            }
        }
        kalMemCopy(&prPtaInfo->rBtProfile.u, &rPtaParam, sizeof(PTA_PARAM_T));
        ptaFsmRunEventSetConfig(prAdapter, &rPtaParam);

    }
    else if (prPtaProfile->eBtProfile == BT_PROFILE_MIXED) {
        ASSERT(prPtaProfile->u.aucBTPParams[BTPPARAM_PTA_MODE_OFFSET] & BTPPARAM_PTA_MODE_VALID);

        //Find correct parameters
        if(prPtaProfile->u.aucBTPParams[BTPPARAM_PTA_MODE_OFFSET] & BTPPARAM_PTA_MODE_VALID){
            if((prPtaProfile->u.aucBTPParams[BTPPARAM_PTA_MODE_OFFSET] & BTPPARAM_PTA_MODE_DUAL) == BTPPARAM_PTA_MODE_DUAL){
                kalMemCopy(&rPtaParam, (PVOID)&prPtaInfo->rDualMixPtaParam, sizeof(PTA_PARAM_T));
            }
            if((prPtaProfile->u.aucBTPParams[BTPPARAM_PTA_MODE_OFFSET] & BTPPARAM_PTA_MODE_DUAL) == BTPPARAM_PTA_MODE_SINGLE){
                kalMemCopy(&rPtaParam, (PVOID)&prPtaInfo->rSingleMixPtaParam, sizeof(PTA_PARAM_T));
            }
        }
        kalMemCopy(&prPtaInfo->rBtProfile.u, &rPtaParam, sizeof(PTA_PARAM_T));
        ptaFsmRunEventSetConfig(prAdapter, &rPtaParam);

    }
#else
    if (prPtaProfile->eBtProfile == BT_PROFILE_SCO) {
        //4 2008/10/29, mikewu <todo> enable new VoIP profile
        kalMemCopy(&rPtaParam, (PVOID)&prPtaInfo->rScoPtaParam, sizeof(PTA_PARAM_T));
        kalMemCopy(&prPtaInfo->rBtProfile.u, &rPtaParam, sizeof(PTA_PARAM_T));
        ptaFsmRunEventSetConfig(prAdapter, &rPtaParam);
    }
    else if (prPtaProfile->eBtProfile == BT_PROFILE_ACL) {
        //4 2008/10/29, mikewu <todo> need calculate the quota time limit
        kalMemCopy(&rPtaParam, (PVOID)&prPtaInfo->rAclPtaParam, sizeof(PTA_PARAM_T));
        kalMemCopy(&prPtaInfo->rBtProfile.u, &rPtaParam, sizeof(PTA_PARAM_T));
        ptaFsmRunEventSetConfig(prAdapter, &rPtaParam);
    }
    else if (prPtaProfile->eBtProfile == BT_PROFILE_MIXED) {
        //4 2008/10/29, mikewu <todo> need calculate the quota time limit
        kalMemCopy(&rPtaParam, (PVOID)&prPtaInfo->rMixPtaParam, sizeof(PTA_PARAM_T));
        kalMemCopy(&prPtaInfo->rBtProfile.u, &rPtaParam, sizeof(PTA_PARAM_T));
        ptaFsmRunEventSetConfig(prAdapter, &rPtaParam);
    }
    else {
        /* prPtaProfile->eBtProfile == BT_PROFILE_CUSTOM
         * or BT_PROFILE_NO_CONNECTION
         * BWCS shall issue this profile after end of ACL, SCO and Mix
         */
        if (prPtaProfile->eBtProfile == BT_PROFILE_CUSTOM) {
            ptaFsmRunEventSetConfig(prAdapter,
                                    (P_PTA_PARAM_T)prPtaProfile->u.au4Btcr);
        }
    }

#endif

}

/*----------------------------------------------------------------------------*/
/*!
*
* \brief This routine is called to update PTA parameters
*
* \param[in]  prAdapter         Pointer to the Adapter structure
* \param[in]  pBTPParams        PTA parameters
*
* \retval none
*
* \note
*/
/*----------------------------------------------------------------------------*/
VOID
nicPTAUpdateParams (
    IN  P_ADAPTER_T         prAdapter,
    IN  PUINT_8             pBTPParams
    )
{
    P_PTA_INFO_T prPtaInfo;

    ASSERT(prAdapter);
    ASSERT(pBTPParams);

    prPtaInfo = &prAdapter->rPtaInfo;
    kalMemCopy(prPtaInfo->rBtProfile.u.aucBTPParams, pBTPParams, BT_PROFILE_PARAM_LEN);
}

/*----------------------------------------------------------------------------*/
/*!
*
* \brief This routine is called to update PTA parameters
*
* \param[in]  prAdapter         Pointer to the Adapter structure
* \param[in]  pucBuffer         buffer to store the requested profile
* \param[out] pu4Count          buffer size written in the pucBuffer
*
* \retval none
*
* \note
*/
/*----------------------------------------------------------------------------*/
VOID
nicPtaGetProfile (
    IN  P_ADAPTER_T     prAdapter,
    IN  PUINT_8         pucBuffer,
    OUT PUINT_32        pu4Count
    )
{
    P_PTA_INFO_T        prPtaInfo;
    P_PTA_PROFILE_T     prPtaProfileBuf;
    P_PTA_PROFILE_T     prPtaProfile;

    ASSERT(prAdapter && pucBuffer);

    ASSERT(pu4Count);

    prPtaInfo = &prAdapter->rPtaInfo;
    prPtaProfileBuf = (P_PTA_PROFILE_T)pucBuffer;
    prPtaProfile = &prPtaInfo->rBtProfile;

    prPtaProfileBuf->eBtProfile = prPtaProfile->eBtProfile;

    kalMemCopy(&prPtaProfileBuf->u, &prPtaProfile->u, sizeof(PTA_PARAM_T));

    *pu4Count = sizeof(PTA_PROFILE_T);

}

/*----------------------------------------------------------------------------*/
/*!
*
* \brief This routine is called to enable/disable PTA function
*
* \param[in]  prAdapter         Pointer to the Adapter structure
* \param[in]  fgEnabled         TRUE: enable pta, FALSE: disable pta
* *
* \retval none
*
* \note
*/
/*----------------------------------------------------------------------------*/
VOID
nicPtaSetFunc (
    IN  P_ADAPTER_T     prAdapter,
    IN  BOOL            fgEnabled
    )
{
    P_PTA_INFO_T        prPtaInfo;

    ASSERT(prAdapter);

    prPtaInfo = &prAdapter->rPtaInfo;

    if (fgEnabled) {
        prPtaInfo->fgEnabled = TRUE;
    }
    else {
        prPtaInfo->fgEnabled = FALSE;
    }
    ptaFsmRunEventSetConfig(prAdapter, &prPtaInfo->rPtaParam);
}


/*----------------------------------------------------------------------------*/
/*!
*
* \brief This routine is called to set preferred antenna
*
* \param[in]  prAdapter         Pointer to the Adapter structure
* \param[in]  fgPrefWiFi         TRUE: set antenna toward WiFi, FALSE: set antenna toward BT
* *
* \retval none
*
* \note
*/
/*----------------------------------------------------------------------------*/
VOID
nicPtaSetAnt (
    IN  P_ADAPTER_T     prAdapter,
    IN  BOOL                 fgPrefWiFi
    )
{
    P_PTA_INFO_T        prPtaInfo;
    UINT_32                 u4ScrValue;

    ASSERT(prAdapter);

    prPtaInfo = &prAdapter->rPtaInfo;

    if (prAdapter->rPtaInfo.fgSingleAntenna == FALSE) {
        /* There is no need to set preferred antenna in dual antenna mode */
        return;
    }

    HAL_MCR_RD(prAdapter, MCR_SCR, &u4ScrValue);

    ASSERT(prAdapter->rPtaInfo.u4PTAWireMode != PTA_SW_3_WIRE_MODE);
    ASSERT(prAdapter->rPtaInfo.u4PTAWireMode != PTA_SW_4_WIRE_MODE);

    u4ScrValue &= ~(SCR_BT_ACT_SEL|
                   SCR_GPIO0_ENABLE_OUTPUT_MODE   |
                   SCR_GPIO0_CHAIN_SEL |
                   SCR_GPIO0_WDATA |
                   SCR_GPIO2_ENABLE_OUTPUT_MODE |
                   SCR_GPIO2_CHAIN_SEL |
                   SCR_GPIO2_WDATA);

    /* Set GPIO0 and GPIO2 as output */
    u4ScrValue |= SCR_GPIO0_ENABLE_OUTPUT_MODE | SCR_GPIO2_ENABLE_OUTPUT_MODE;

    if (fgPrefWiFi) {
        u4ScrValue |= SCR_GPIO0_WDATA;
    }
    else {
        u4ScrValue |= SCR_GPIO2_WDATA;
    }
    HAL_MCR_WR(prAdapter, MCR_SCR, u4ScrValue);
}
#if PTA_NEW_BOARD_DESIGN
/*----------------------------------------------------------------------------*/
/*!
*
* \brief This routine is called to set preferred antenna
*
* \param[in]  prAdapter         Pointer to the Adapter structure
* \param[in]  fgPrefWiFi         TRUE: set antenna toward WiFi, FALSE: set antenna toward BT
* *
* \retval none
*
* \note
*/
/*----------------------------------------------------------------------------*/
VOID
nicPtaGetAnt (
    IN  P_ADAPTER_T     prAdapter,
    IN  PBOOL           pfgPrefWiFi
    )
{
    UINT_32 u4ScrValue;

    ASSERT(prAdapter);

    ASSERT(prAdapter->rPtaInfo.fgSingleAntenna);
    ASSERT(prAdapter->rPtaInfo.u4PTAWireMode != PTA_SW_3_WIRE_MODE);
    ASSERT(prAdapter->rPtaInfo.u4PTAWireMode != PTA_SW_4_WIRE_MODE);

    if (prAdapter->rPtaInfo.fgSingleAntenna == FALSE) {
        /* There is no need to set preferred antenna in dual antenna mode */
        //RETAILMSG(TRUE, (L"nicPtaGetAnt queried in dual antenna \n"));
        *pfgPrefWiFi = TRUE;
        return;
    }

    HAL_MCR_RD(prAdapter, MCR_SCR, &u4ScrValue);

    u4ScrValue &=  SCR_GPIO0_WDATA | SCR_GPIO2_WDATA;

    if(u4ScrValue == SCR_GPIO0_WDATA){
        *pfgPrefWiFi = TRUE;
    }else if(u4ScrValue == SCR_GPIO2_WDATA){
        *pfgPrefWiFi = FALSE;
    }else{
        //RETAILMSG(TRUE, (L"nicPtaGetAnt strange 0x%08x\n", u4ScrValue));
    }

    return;
}

#endif
