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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/hal_hw_scan.c#1 $
*/

/*! \file   "hal_hw_scan.c"
    \brief  The HAL layer file, which placed function for HW scan related methods.

    Detail description.
*/

/******************************************************************************
* Copyright (c) 2007 MediaTek Inc.
*
* All rights reserved. Copying, compilation, modification, distribution
* or any other use whatsoever of this material is strictly prohibited
* except in accordance with a Software License Agreement with
* MediaTek Inc.
*******************************************************************************
*/

/******************************************************************************
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
*******************************************************************************
*/

/*
** $Log: hal_hw_scan.c $
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\47 2009-02-11 19:52:02 GMT mtk01084
**  Fix the LP watchdog, due to U-APSD service period
**  \main\maintrunk.MT5921\46 2008-12-08 20:58:38 GMT mtk01084
**  prevent lint warning
**  \main\maintrunk.MT5921\45 2008-11-13 14:49:30 GMT mtk01088
**  fixed the compiling warning
**  \main\maintrunk.MT5921\44 2008-11-13 11:52:40 GMT mtk01088
**  update the scan function for switch channel, for check the bb setting while at JP and CH14
**  \main\maintrunk.MT5921\43 2008-10-15 15:55:58 GMT mtk01084
**  add logic reset for workaround HEC6796
**  \main\maintrunk.MT5921\42 2008-09-16 19:26:47 GMT mtk01084
**  prevent compiler warning
**  \main\maintrunk.MT5921\41 2008-08-18 10:07:21 GMT mtk01084
**  conformance for coding rule conformance
**  \main\maintrunk.MT5921\40 2008-08-03 17:18:55 GMT mtk01084
**  remove compiler warning on Linux compiler
**  \main\maintrunk.MT5921\39 2008-07-21 12:01:45 GMT mtk01084
**  add SW assert for sanity check
**  \main\maintrunk.MT5921\38 2008-07-01 23:32:03 GMT mtk01084
**  allow to poll for more data during scan initial phase
**  \main\maintrunk.MT5921\37 2008-06-26 21:08:18 GMT mtk01084
**  not to ps-poll for more data during scan
**  \main\maintrunk.MT5921\36 2008-06-12 14:39:56 GMT mtk01084
**  optimize scan instruction setting when doing HW scan
**  \main\maintrunk.MT5921\35 2008-04-21 13:40:32 GMT mtk01084
**  set OP mode to infrastructure when going to BG ssid scan
**  \main\maintrunk.MT5921\34 2008-04-11 00:19:46 GMT mtk01385
**  1. modify halSetTxPowerGain function name.
**  \main\maintrunk.MT5921\33 2008-03-30 22:20:10 GMT mtk01084
**  fix low power sleep interval under watchdog issue
**  \main\maintrunk.MT5921\32 2008-03-25 22:25:27 GMT mtk01084
**  workaround for the HEC 5269, which is TX done false alarm during scan
**  \main\maintrunk.MT5921\31 2008-03-25 22:20:47 GMT mtk01084
**  modify lines in BG SSID scan setting
**  \main\maintrunk.MT5921\30 2008-03-20 12:05:26 GMT mtk01084
**  modify the lines in setting sleep timeout
**  \main\maintrunk.MT5921\29 2008-03-18 19:44:19 GMT mtk01084
**  modify the sleep timeout used for WDT, which aligns with BG SSID scan maximum interval
**  \main\maintrunk.MT5921\28 2008-03-03 18:10:39 GMT mtk01084
**  modify function description comments
**  \main\maintrunk.MT5921\27 2008-02-21 23:28:40 GMT mtk01084
**  modify format
**  \main\maintrunk.MT5921\26 2008-02-18 17:24:51 GMT mtk01084
**  add function description
**  \main\maintrunk.MT5921\25 2008-02-01 13:42:40 GMT mtk01385
**  1. add tx power gain update to hw scan instructions.
**  \main\maintrunk.MT5921\24 2008-02-01 10:36:42 GMT mtk01385
**  1. Fix WinCE 4.2 compiling error.
**  \main\maintrunk.MT5921\23 2008-01-08 10:34:47 GMT mtk01084
**  sanity check for the control of Normal/ BG SSID scan
**  \main\maintrunk.MT5921\22 2007-12-29 16:21:39 GMT mtk01385
**  1. Modify RICR definitions.
**  \main\maintrunk.MT5921\21 2007-12-08 22:33:43 GMT mtk01084
**  use register configuration for setting to honor service period or trigger events
**  \main\maintrunk.MT5921\20 2007-12-07 17:41:24 GMT mtk01084
**  modify the register setting when setting HW scan not to honor service period
**  \main\maintrunk.MT5921\19 2007-12-07 12:13:52 GMT mtk01084
**  remove unused line
**  \main\maintrunk.MT5921\18 2007-12-07 10:39:13 GMT mtk01084
**  modify register setting for BG SSID SCan
**  \main\maintrunk.MT5921\17 2007-11-22 22:17:41 GMT mtk01084
**  monor modify
**  \main\maintrunk.MT5921\16 2007-11-21 18:24:23 GMT mtk01084
**  remove scan_busy bit check after scan is enabled
**  \main\maintrunk.MT5921\15 2007-11-21 11:25:09 GMT mtk01084
**  fix Linux compiler warning
**  \main\maintrunk.MT5921\14 2007-11-19 17:37:14 GMT mtk01084
**  modify halScanAbort()
**  \main\maintrunk.MT5921\13 2007-11-14 11:55:21 GMT mtk01084
**  update lines to do input argument check
**  \main\maintrunk.MT5921\12 2007-11-12 16:20:01 GMT mtk01084
**  code refine
**  \main\maintrunk.MT5921\11 2007-11-12 15:07:53 GMT mtk01084
**  code refine
**  \main\maintrunk.MT5921\10 2007-11-01 14:44:50 GMT mtk01084
**  modify variable naming of the u4ScanDwellTimeMax to u4ScanDwellTimeExt
**  \main\maintrunk.MT5921\9 2007-10-30 20:54:55 GMT mtk01084
**  modify place to honor service period or not
**  \main\maintrunk.MT5921\8 2007-10-29 13:35:07 GMT mtk01084
**  use compiling flag to seperate the flag to indicate interrupt may false alarm case
**  \main\maintrunk.MT5921\7 2007-10-26 19:16:02 GMT mtk01084
**  modify halHwScanDisable() function
**  \main\maintrunk.MT5921\6 2007-10-25 18:07:07 GMT mtk01461
**  Add VOIP SCAN Support  & Refine Roaming
**
*/

/******************************************************************************
*                         C O M P I L E R   F L A G S
*******************************************************************************
*/

/******************************************************************************
*                    E X T E R N A L   R E F E R E N C E S
*******************************************************************************
*/
#include "precomp.h"


/******************************************************************************
*                              C O N S T A N T S
*******************************************************************************
*/

/******************************************************************************
*                             D A T A   T Y P E S
*******************************************************************************
*/

/******************************************************************************
*                            P U B L I C   D A T A
*******************************************************************************
*/

/******************************************************************************
*                           P R I V A T E   D A T A
*******************************************************************************
*/
UINT_32 u4ScanInstCount;
BOOLEAN fgScanInited = FALSE;

/******************************************************************************
*                                 M A C R O S
*******************************************************************************
*/

/******************************************************************************
*                   F U N C T I O N   D E C L A R A T I O N S
*******************************************************************************
*/

/******************************************************************************
*                              F U N C T I O N S
*******************************************************************************
*/

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to enable HW scan function.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
* \param[in] eScanMode To do NORMAL scan or BG SSID scan.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
halHwScanEnable (
    IN P_ADAPTER_T prAdapter,
    IN ENUM_HW_SCAN_MODE_T eScanMode
    )
{
    UINT_32 u4RegMptcr;

    ASSERT(prAdapter);

    /* start HW scan function */
    HAL_MCR_RD(prAdapter, MCR_MPTCR, &u4RegMptcr);

    if (eScanMode == ENUM_HW_SCAN_NORMAL_SCAN) {
        /* HW scan does not worried about if AC0~AC4 will be stopped by
           HW for IBSS-PS (ATIM window != 0 & IBSS mode)
        */

        /* Sanity check for the HW scan state and configuration */
        if (u4RegMptcr & MPTCR_SSID_SRCH) {
            u4RegMptcr &= ~MPTCR_SSID_SRCH;
            ASSERT(0);
        }

        HAL_MCR_WR(prAdapter, MCR_MPTCR, u4RegMptcr | MPTCR_SCAN_EN);
    }
    else if (eScanMode == ENUM_HW_SCAN_BG_SSID_SCAN) {
        u4RegMptcr &= ~(MPTCR_PRETBTT_TRIG_EN | MPTCR_PREDTIM_TRIG_EN);

        /* Sanity check for the HW scan state and configuration */
        if (u4RegMptcr & MPTCR_SCAN_EN) {
            u4RegMptcr &= ~MPTCR_SCAN_EN;
            ASSERT(0);
        }

        /* enable SSID search function */
        HAL_MCR_WR(prAdapter,
                    MCR_MPTCR,
                    u4RegMptcr |
                    MPTCR_SSID_SRCH |
                    MPTCR_TBTT_PERIOD_TIMER_EN);
    }
    else {
        ASSERT(0);
    }
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to disable HW scan function.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
* \param[in] eScanMode To do NORMAL scan or BG SSID scan.
*
* \retval TRUE  HW scan function is disabled successfully
* \retval FALSE HW scan function is disabled abnormally
*/
/*----------------------------------------------------------------------------*/
BOOLEAN
halHwScanDisable (
    IN P_ADAPTER_T prAdapter,
    IN ENUM_HW_SCAN_MODE_T eScanMode
    )
{
#define POLLING_LOOP_COUNT  100

    UINT_32 i, u4RegValue;

    ASSERT(prAdapter);

    /* Disable function */
    HAL_MCR_RD(prAdapter, MCR_MPTCR, &u4RegValue);

    if (eScanMode == ENUM_HW_SCAN_NORMAL_SCAN) {
        HAL_MCR_WR(prAdapter, MCR_MPTCR, u4RegValue & ~MPTCR_SCAN_EN);

        /* polling until scan is disabled */
        for (i = 0; i < POLLING_LOOP_COUNT; i ++) {
            HAL_MCR_RD(prAdapter, MCR_CIR, &u4RegValue);
            if (u4RegValue & CIR_SCAN_BUSY) {
                kalUdelay(10);
            }
            else {
                break;
            }
        }
        if (i == POLLING_LOOP_COUNT) {
            ASSERT(0);
            return FALSE;
        }
    }
    else if (eScanMode == ENUM_HW_SCAN_BG_SSID_SCAN) {
        HAL_MCR_WR(prAdapter,
                   MCR_MPTCR,
                   u4RegValue & ~(MPTCR_SSID_SRCH | MPTCR_TBTT_PERIOD_TIMER_EN));

        /* Basically, this function is disabled automatically when LP ownback */
    }
    else {
        ASSERT(0);
    }
    return TRUE;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to configure HW BG SSID scan parameters.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
* \param[in] prBgScanCfg The parameters used for BG SSID scan.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
halHwScanSetBgScanParam (
    IN P_ADAPTER_T          prAdapter,
    IN P_BG_SCAN_CONFIG_T   prBgScanCfg
    )
{
#if CFG_WORKAROUND_HEC_5269
    UINT_32 u4RegMptcr;
#endif
    UINT_32 u4RegDbgr;
    UINT_32 u4RegAtcr;
    UINT_32 u4RegSscr;
    UINT_32 u4RegTtpcr;
    UINT_32 i, j;
    P_PARAM_SSID_T prSsidEntry;
    UINT_8 ucDtimPeriod;
    P_BG_SCAN_SSID_CANDIDATE_T  prScanCandidate;
    UINT_16 u2BaseWakePeriod;
    UINT_8 ucStepOfWakePeriod;
    UINT_32 u4SleepTimeout;

    DEBUGFUNC("halHwScanSetBgScanParam");

    ASSERT(prAdapter);
    ASSERT(prBgScanCfg);

    prScanCandidate = &prBgScanCfg->rScanCandidate;
    u2BaseWakePeriod = prBgScanCfg->u2BaseWakePeriod;
    ucStepOfWakePeriod = prBgScanCfg->ucBgScanStepOfWakePeriod;

    /* return if NULL SSID entry */
    if (prScanCandidate->ucNumHwSsidScanEntry == 0) {
        DBGLOG(SCAN, ERROR, ("NULL SSID entry\n\r"));
        return;
    }
    else if (prScanCandidate->ucNumHwSsidScanEntry > HAL_HW_SCAN_ENTRY_NUMBER) {
        prScanCandidate->ucNumHwSsidScanEntry = HAL_HW_SCAN_ENTRY_NUMBER; //maximum 16 entries
    }

    /* set NULL interval to 0 for disabling DTIM wakeup function to trigger INT */
    HAL_MCR_RD(prAdapter, MCR_ATCR, &u4RegAtcr);
    u4RegAtcr &= ~ATCR_TX_NULL_INTERVAL;
    HAL_MCR_WR(prAdapter, MCR_ATCR, u4RegAtcr);

    /* program background scan period and its exponential */
    if (ucStepOfWakePeriod > 7) {
        ucStepOfWakePeriod = 7;
    }
    ucDtimPeriod = 128 >> ucStepOfWakePeriod;
    u2BaseWakePeriod /= ucDtimPeriod;

    u4RegTtpcr = (u2BaseWakePeriod | (ucDtimPeriod << 16) | (1 << 28));
    HAL_MCR_WR(prAdapter, MCR_TTPCR, u4RegTtpcr);

#if CFG_WORKAROUND_HEC_6796
    /* do this logic reset for preventing HEC6796, which is may cause SW fail to program
       the SSID entry in few cases.
    */
    nicLogicReset(prAdapter);
#endif

    HAL_MCR_RD(prAdapter, MCR_SSCR, &u4RegSscr);
    u4RegSscr &= ~SSCR_SSID_NUMBER;
    HAL_MCR_WR(prAdapter, MCR_SSCR,
                u4RegSscr |
                (prBgScanCfg->ucBgScanMinRcpiThr << 24) |
                (prScanCandidate->ucNumHwSsidScanEntry & SSCR_SSID_NUMBER) |
                SSCR_SSID_START);

    /* program SSIDs */
    for (i = 0; i < prScanCandidate->ucNumHwSsidScanEntry; i++) {
        /* get the entry of SSID history */
        prSsidEntry = &prScanCandidate->arHwSsidScanEntry[i];

        HAL_MCR_WR(prAdapter, MCR_SDR, prSsidEntry->u4SsidLen);

        for (j = 0; j < ((prSsidEntry->u4SsidLen + 3) >> 2); j++) {
            HAL_MCR_WR(prAdapter, MCR_SDR,
                        ((PUINT_32)prSsidEntry->aucSsid)[j]);
        }
    }

#if DBG
    /* check if SSID program completed */
    HAL_MCR_RD(prAdapter, MCR_SSCR, &u4RegSscr);
    if (u4RegSscr & SSCR_SSID_START) {
        DBGLOG(SCAN, ERROR, ("polling timeout\n\r"));
        ASSERT(0);
    }
#endif

#if CFG_WORKAROUND_HEC_5269
    /* prevent TX done status cause HW fail to enter sleep or wakeup */
    HAL_MCR_RD(prAdapter, MCR_MPTCR, &u4RegMptcr);
    HAL_MCR_WR(prAdapter, MCR_MPTCR, u4RegMptcr | MPTCR_TX_DONE_SLEEP_CTRL);
#endif

    /* Modify the sleep timeout for LP watchdog */
    u4SleepTimeout = prBgScanCfg->u2BaseWakePeriod << (ucStepOfWakePeriod + 1);
    u4SleepTimeout >>= 10; // in unit of 1024 TU
    u4SleepTimeout += 1;

    ASSERT(u4SleepTimeout <= DBGR_SLEEP_TIMEOUT_COUNT);
    u4SleepTimeout &= DBGR_SLEEP_TIMEOUT_COUNT;

    HAL_MCR_RD(prAdapter, MCR_DBGR, &u4RegDbgr);
    u4RegDbgr &= ~DBGR_SLEEP_TIMEOUT_COUNT;
    u4RegDbgr |= DBGR_SLEEP_TIMEOUT_UNIT_1024_TU;
    HAL_MCR_WR(prAdapter, MCR_DBGR, u4RegDbgr | u4SleepTimeout);

    /* Set to infrastructure mode */
    halSetOPMode(prAdapter, OP_MODE_INFRASTRUCTURE);

} /* nicHwScanSetBgScanParam */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to configure LP instructions for switching channel.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
* \param[in] prChnlInfoList The channel information.
* \param[out] pu4ChSwInstNum The number of instructions when switching a channel.
*
* \retval WLAN_STATUS_SUCCESS
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
halHwScanSetPerChnlInst (
    IN P_ADAPTER_T          prAdapter,
    IN P_RF_CHANNEL_INFO_T  prChnlInfoList,
    OUT PUINT_32            pu4ChSwInstNum
    )
{
    UINT_32 u4FifoWrPtr = 0;
    UINT_32 u4McrCfpr;
    UINT_32 u4McrOfpr;
    BOOLEAN fgTxFilterForJp;

    ASSERT(prAdapter);
    ASSERT(prChnlInfoList);
    ASSERT(pu4ChSwInstNum);

    /* Initial process for recording the number of instruction
       for channel switch */
    HAL_HW_SCAN_GET_INST_NUMBER_INIT(prAdapter, &u4FifoWrPtr);

    fgTxFilterForJp = nicSetTxFilterForJP(prAdapter,
                                          prChnlInfoList->ucChannelNum,
                                          prChnlInfoList->eBand);

    if (halSetRFSwitchChnlInst(prAdapter,
                            prChnlInfoList->ucChannelNum,
                            prChnlInfoList->eBand,
                            fgTxFilterForJp) != WLAN_STATUS_SUCCESS) {

        return WLAN_STATUS_NOT_ACCEPTED;
    }

    /* Stall 100 us for synthesizer stable. */
    HAL_HW_SCAN_SET_INST_DELAY(prAdapter, 100, FALSE);

    /* Program TX power gain */
    if (halSetTxPowerGain(prAdapter,
                          prChnlInfoList->ucChannelNum,
                          prChnlInfoList->eBand,
                          &u4McrCfpr,
                          &u4McrOfpr) == WLAN_STATUS_SUCCESS) {

        HAL_HW_SCAN_SET_INST_MCR_WR(prAdapter,
                                    MCR_CFPR,
                                    u4McrCfpr,
                                    FALSE,
                                    TRUE);
        HAL_HW_SCAN_SET_INST_MCR_WR(prAdapter,
                                    MCR_OFPR,
                                    u4McrOfpr,
                                    TRUE,
                                    TRUE);
    }

    /* Record the number of instruction for channel switch
       at the end of the LP instruction programming */
    HAL_HW_SCAN_GET_INST_NUMBER_END(prAdapter, u4FifoWrPtr, pu4ChSwInstNum);

    return WLAN_STATUS_SUCCESS;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to configure LP instructions for switching channel.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
* \param[in] parChnlInfoList The channel list used for scan.
* \param[in] ucNumOfScanChnl The number of channels used for scan.
* \param[in] eScanType To do ACTIVE scan or PASSIVE scan.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
halHwScanSetScanCtrlInst (
    IN P_ADAPTER_T          prAdapter,
    IN P_RF_CHANNEL_INFO_T  parChnlInfoList,
    IN UINT_8               ucNumOfScanChnl,
    IN ENUM_SCAN_TYPE_T     eScanType
    )
{
    UINT_32 i;
    UINT_32 u4ScanCtrlWrPr = 0;
    UINT_32 u4ChnlSwInstNum = 0, u4BandSwInstNum = 0;
#if DBG
    UINT_32 u4ChnlSwLastInstNum = 0;
#endif

    DEBUGFUNC("halHwScanSetScanCtrlInst");

    ASSERT(prAdapter);
    ASSERT(parChnlInfoList);

    /* Note: A band support should be considered later, it only consider BG band
             currently */

    /* program preamble scan ctrl - reserve the slot for the instruction */
    HAL_HW_SCAN_PRESERVE_INST_SCAN_CTRL(prAdapter, &u4ScanCtrlWrPr);

    for (i = 0; i < ucNumOfScanChnl; i++) {
        halHwScanSetPerChnlInst(prAdapter,
                                &parChnlInfoList[i],
                                &u4ChnlSwInstNum);

#if DBG
        /* note: we do not check if 'u4ChSwInstNum' are identical for
                 each channel currently
        */
        if ((i != 0) && (u4ChnlSwLastInstNum != u4ChnlSwInstNum)) {
            DBGLOG(SCAN, TRACE, ("u4ChnlSwLastInstNum: %ld, u4ChnlSwInstNum: %ld",
                u4ChnlSwLastInstNum, u4ChnlSwInstNum));
            ASSERT(0);
        }
        else {
            u4ChnlSwLastInstNum = u4ChnlSwInstNum;
        }
#endif
    }

    /* program preamble scan ctrl - by the instructions for each channel switch */
    HAL_HW_SCAN_RESTORE_INST_SCAN_CTRL(prAdapter,
                                       eScanType,
                                       ucNumOfScanChnl,
                                       u4BandSwInstNum,
                                       u4ChnlSwInstNum,
                                       u4ScanCtrlWrPr);
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to setup the scan parameters for doing multi-channel
         scan.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
* \param[in] prScanCfg The scan parameters.
* \param[in] eScanMode To do NORMAL scan or BG SSID scan.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
halHwScanSetInitialInst (
    IN P_ADAPTER_T prAdapter,
    IN P_SCAN_CONFIG_T prScanCfg,
    IN ENUM_HW_SCAN_MODE_T eScanMode
    )
{
    UINT_32 u4QueueDwStart = 0xffffffff;
    UINT_32 u4DwSize;

    DEBUGFUNC("halHwScanSetInitialInst");

    ASSERT(prAdapter);
    ASSERT(prScanCfg);

    /* find scan queue start address */
    if (!halGetQueueInfo(prAdapter, ENUM_QUEUE_ID_SCAN, &u4QueueDwStart, &u4DwSize)) {
        DBGLOG(SCAN, ERROR, ("Cannot find the scan queue within memory map!"));
        ASSERT(0);
        return;
    }

    HAL_HW_SCAN_INST_START(prAdapter, u4QueueDwStart);

    /* Program parameters for channel switch */
    halHwScanSetScanCtrlInst(prAdapter,
                             prScanCfg->arChnlInfoList,
                             prScanCfg->ucNumOfScanChnl,
                             prScanCfg->eScanType);

    /* Program the end address */
    HAL_HW_SCAN_INST_END(prAdapter,
                         (UINT_32)ENUM_QUEUE_ID_SCAN,
                         u4QueueDwStart,
                         u4DwSize);


}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to setup the scan parameters for switching back
*        to original channel.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
* \param[in] prScanCfg The scan parameters.
* \param[in] eScanMode To do NORMAL scan or BG SSID scan.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
halHwScanSetTerminateInst (
    IN P_ADAPTER_T prAdapter,
    IN P_SCAN_CONFIG_T prScanCfg,
    IN ENUM_HW_SCAN_MODE_T eScanMode
    )
{
    UINT_32 u4QueueDwStart = 0xffffffff;
    UINT_32 u4DwSize;
    UINT_32 u4ChnlSwInstNum;

    DEBUGFUNC("halHwScanSetTerminateInst");

    ASSERT(prAdapter);
    ASSERT(prScanCfg);


    if (eScanMode == ENUM_HW_SCAN_BG_SSID_SCAN) {
        // there's no this function under BG SSID SCAN
        return;
    }

    /* find scan ctrl queue start address */
    if (!halGetQueueInfo(prAdapter, ENUM_QUEUE_ID_SCAN_CTRL, &u4QueueDwStart, &u4DwSize)) {
        DBGLOG(SCAN, ERROR, ("Cannot find the scan control queue within memory map!"));
        ASSERT(0);
        return;
    }

    HAL_HW_SCAN_INST_START(prAdapter, u4QueueDwStart);

    halHwScanSetPerChnlInst(prAdapter,
                            &prScanCfg->rOrgChnlInfo,
                            &u4ChnlSwInstNum);

    HAL_HW_SCAN_INST_END(prAdapter,
                         (UINT_32)ENUM_QUEUE_ID_SCAN_CTRL,
                         u4QueueDwStart,
                         u4DwSize);
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to initialize the register setting for HW scan.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
* \param[in] prScanCfg The scan parameters.
* \param[in] eScanMode To do NORMAL scan or BG SSID scan.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
halHwScanRegisterInit (
    IN P_ADAPTER_T prAdapter,
    IN P_SCAN_CONFIG_T prScanCfg,
    IN ENUM_HW_SCAN_MODE_T eScanMode
    )
{
    UINT_32 u4RegValue;
    P_SCAN_INFO_T prScanInfo;
    P_BACKUP_REGISTER_VALUE_T prBkupReg;

    ASSERT(prAdapter);
    ASSERT(prScanCfg);

    prScanInfo = &prAdapter->rScanInfo;
    prBkupReg = &prScanInfo->rBkupRegValue;

    /* program scan channel idle time */
    HAL_MCR_RD(prAdapter, MCR_SSCR, &u4RegValue);
    HAL_MCR_WR(prAdapter, MCR_SSCR,
               (u4RegValue & ~(SSCR_MIN_SCAN_TIME | SSCR_EXT_SCAN_TIME)) |
               (prScanCfg->ucChnlDwellTimeExt << 16) |
               (prScanCfg->ucChnlDwellTimeMin << 8));

    if (eScanMode == ENUM_HW_SCAN_NORMAL_SCAN) {
        HAL_MCR_RD(prAdapter, MCR_MPTCR, &prBkupReg->u4RegOrgLpEnFunc);
        u4RegValue = prBkupReg->u4RegOrgLpEnFunc;

        // Honor the trigger event during scan?
        if (!prScanCfg->fgToEnableTriggerEvent) {
            /* for the TBTT timer */
            u4RegValue &= ~MPTCR_PRETBTT_PREDTIM_TRIG_EN;

            /* <TODO> for the VoIP timer (T3), change to free run timer */
        }
        HAL_MCR_WR(prAdapter, MCR_MPTCR, u4RegValue);

        // Honor service period before scan?
        if (!prScanCfg->fgToHonorServicePeriod) {
            HAL_MCR_RD(prAdapter, MCR_SPCR, &prBkupReg->u4RegSpcr);

            // Disable Service period
            halpmSetupServicePeriodMechanism(prAdapter, 0, SP_ALL);
        }

        // RFIFO threshold
        if (prScanCfg->u2RxFifoThreshold) {
            HAL_MCR_RD(prAdapter, MCR_HITR, &u4RegValue);
            u4RegValue = (UINT_32)prScanCfg->u2RxFifoThreshold & HFCR_RX_INT_THRESHOLD;
            HAL_MCR_WR(prAdapter, MCR_HITR, u4RegValue);
        }
    }
    else if (eScanMode == ENUM_HW_SCAN_BG_SSID_SCAN) {
        /* program BG SSID specific parameters */
        halHwScanSetBgScanParam(prAdapter, &prScanCfg->rBgScanCfg);

        // Disable Service period
        halpmSetupServicePeriodMechanism(prAdapter, 0, SP_ALL);
    }

}


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to un-initialize the register setting for HW scan.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
* \param[in] prScanCfg The scan parameters.
* \param[in] eScanMode To do NORMAL scan or BG SSID scan.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
halHwScanRegisterUnInit (
    IN P_ADAPTER_T prAdapter,
    IN P_SCAN_CONFIG_T prScanCfg,
    IN ENUM_HW_SCAN_MODE_T eScanMode
    )
{
    P_SCAN_INFO_T prScanInfo;
    P_BACKUP_REGISTER_VALUE_T prBkupReg;
    UINT_32 u4RegMptcr;

    ASSERT(prAdapter);
    ASSERT(prScanCfg);

    prScanInfo = &prAdapter->rScanInfo;
    prBkupReg = &prScanInfo->rBkupRegValue;

    /* ----------------------------------------------------------- */
    /* Program LP instruction to restore original register setting */
    /* ----------------------------------------------------------- */

    if (eScanMode == ENUM_HW_SCAN_NORMAL_SCAN) {
        // RFIFO threshold
        if (prScanCfg->u2RxFifoThreshold) {
            HAL_MCR_WR(prAdapter, MCR_HITR, prBkupReg->u4RegOrgRxFifoThr);
        }

        // Honor service period before scan? (and Reset timeout count)
        if (prScanCfg->fgToHonorServicePeriod == FALSE) {
            HAL_MCR_WR(prAdapter, MCR_SPCR, prBkupReg->u4RegSpcr);
        }

        // Honor the trigger event during scan?
        HAL_MCR_WR(prAdapter, MCR_MPTCR, prBkupReg->u4RegOrgLpEnFunc);
    }
    else if (eScanMode == ENUM_HW_SCAN_BG_SSID_SCAN) {
        HAL_MCR_RD(prAdapter, MCR_MPTCR, &u4RegMptcr);
        u4RegMptcr &= ~(MPTCR_SSID_SRCH |
#if CFG_WORKAROUND_HEC_5269
                        MPTCR_TX_DONE_SLEEP_CTRL |
#endif
                        MPTCR_TBTT_PERIOD_TIMER_EN);
        HAL_MCR_WR(prAdapter, MCR_MPTCR, u4RegMptcr);
    }
}



