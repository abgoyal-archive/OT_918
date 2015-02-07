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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/statistics.c#1 $
*/

/*! \file   "statistics.c"
    \brief  This file contains the statistics routines

    This file contains the reset routines.
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
** $Log: statistics.c $
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\9 2008-10-30 11:15:28 GMT mtk01088
**  remove the lint warning
**  \main\maintrunk.MT5921\8 2008-08-28 21:07:04 GMT mtk01088
**  add function declaration
**  \main\maintrunk.MT5921\7 2008-05-03 14:28:02 GMT mtk01461
**  Update debug level of debug message
**  \main\maintrunk.MT5921\6 2008-03-12 09:52:21 GMT mtk01461
**  Fix compile warning in Linux
**  \main\maintrunk.MT5921\5 2008-02-01 16:11:32 GMT mtk01385
**  1. add statistics int function.
**  2. add statistics Uninit function.
**  3. fix 64 bit printf issue on Winodws.
**  \main\maintrunk.MT5921\4 2007-12-11 00:10:24 GMT mtk01461
**  Update postfix of statistic time out define
**  \main\maintrunk.MT5921\3 2007-11-30 17:21:10 GMT mtk01425
**  1. Fix compiling error
**
**  \main\maintrunk.MT5921\2 2007-11-30 16:48:20 GMT mtk01425
**  1. Fix compiling warning
**
**  \main\maintrunk.MT5921\1 2007-11-26 22:03:15 GMT mtk01385
**  1. init version.
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

/*----------------------------------------------------------------------------*/
/*!
* \brief The Statistics Function init entry
*
* \param prAdapter      Pointer of Adapter Data Structure
*
* \return -
*/
/*----------------------------------------------------------------------------*/
VOID
statisticsInit (
    IN P_ADAPTER_T prAdapter
    )
{

    DEBUGFUNC("statisticsInit");

    ASSERT(prAdapter);

    DBGLOG(INIT, TRACE, ("\n"));

#if CFG_STATISTICS_TIMER_EN
    statisticsTimerInit(prAdapter);
#else
    statisticsIntInit(prAdapter);
#endif
    return;
}


/*----------------------------------------------------------------------------*/
/*!
* \brief Use a Periodic Timer to get the Statistics value
*
* \param prAdapter      Pointer of Adapter Data Structure
*
* \return -
*/
/*----------------------------------------------------------------------------*/
VOID
statisticsTimerInit (
    IN P_ADAPTER_T prAdapter
    )
{
    P_STATISTICS_INFO_T       prStatisInfo;


    DEBUGFUNC("statisticsTimerInit");

    ASSERT(prAdapter);

    DBGLOG(INIT, TRACE, ("\n"));

    prStatisInfo = &prAdapter->rStatisticsInfo;

    ARB_INIT_TIMER(prAdapter,
                   prStatisInfo->rPeekTimer,
                   statisticsTimerTimeOut,
                   TRUE);

    ARB_SET_TIMER(prAdapter,
                  prStatisInfo->rPeekTimer,
                  CFG_TIMER_PEEK_HW_COUNTERS_PERIOD_MSEC);
    
    prStatisInfo->fgUseTimerTrig = TRUE;
    prStatisInfo->fgEn = TRUE;

    return;
}


/*----------------------------------------------------------------------------*/
/*!
* \brief Use a Interrupt to get the Statistics value
*
* \param prAdapter      Pointer of Adapter Data Structure
*
* \return -
*/
/*----------------------------------------------------------------------------*/
VOID
statisticsIntInit (
    IN P_ADAPTER_T prAdapter
    )
{
    P_STATISTICS_INFO_T       prStatisInfo;


    DEBUGFUNC("statisticsIntInit");

    ASSERT(prAdapter);

    DBGLOG(INIT, TRACE, ("\n"));

    prStatisInfo = &prAdapter->rStatisticsInfo;
    prStatisInfo->fgUseTimerTrig = FALSE;
    prStatisInfo->fgEn = TRUE;

    return;
}


/*----------------------------------------------------------------------------*/
/*!
* \brief Unint the Interrupt for Statistics 
*
* \param prAdapter      Pointer of Adapter Data Structure
*
* \return -
*/
/*----------------------------------------------------------------------------*/
VOID
statisticsUnInit (
    IN P_ADAPTER_T prAdapter
    )
{

    DEBUGFUNC("statisticsUnInit");

    ASSERT(prAdapter);

    DBGLOG(INIT, TRACE, ("\n"));

#if CFG_STATISTICS_TIMER_EN
    statisticsTimerUnInit(prAdapter);
#else
    statisticsIntUnInit(prAdapter);
#endif
    return;
}



/*----------------------------------------------------------------------------*/
/*!
* \brief Uninit the Timer for Statistics 
*
* \param prAdapter      Pointer of Adapter Data Structure
*
* \return -
*/
/*----------------------------------------------------------------------------*/
VOID
statisticsTimerUnInit (
    IN P_ADAPTER_T prAdapter
    )
{
    P_STATISTICS_INFO_T       prStatisInfo;


    DEBUGFUNC("statisticsTimerUnInit");

    ASSERT(prAdapter);

    DBGLOG(INIT, TRACE, ("\n"));

    prStatisInfo = &prAdapter->rStatisticsInfo;
    prStatisInfo->fgEn = FALSE;
    ARB_CANCEL_TIMER(prAdapter,
                  prStatisInfo->rPeekTimer);

    return;
}


/*----------------------------------------------------------------------------*/
/*!
* \brief Unint the Interrupt for Statistics 
*
* \param prAdapter      Pointer of Adapter Data Structure
*
* \return -
*/
/*----------------------------------------------------------------------------*/
VOID
statisticsIntUnInit (
    IN P_ADAPTER_T prAdapter
    )
{
    P_STATISTICS_INFO_T       prStatisInfo;


    DEBUGFUNC("statisticsIntUnInit");

    ASSERT(prAdapter);

    DBGLOG(INIT, TRACE, ("\n"));

    prStatisInfo = &prAdapter->rStatisticsInfo;
    prStatisInfo->fgEn = TRUE;

    return;
}


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will call the statisticsPeekHWCounter to get value
*
* \param prAdapter      Pointer of Adapter Data Structure
*
* \return -
*/
/*----------------------------------------------------------------------------*/
VOID
statisticsTimerTimeOut (
    IN P_ADAPTER_T prAdapter
    )
{
    P_STATISTICS_INFO_T       prStatisInfo;


    DEBUGFUNC("statisticsTimerTimeOut");

    ASSERT(prAdapter);

    DBGLOG(REQ, TRACE, ("\n"));

    statisticsPeekHWCounter(prAdapter);

    prStatisInfo = &prAdapter->rStatisticsInfo;
    ARB_SET_TIMER(prAdapter,
                  prStatisInfo->rPeekTimer,
                  CFG_TIMER_PEEK_HW_COUNTERS_PERIOD_MSEC);
    return;
}


/*----------------------------------------------------------------------------*/
/*!
* \brief This function is trigger by each time any interrupt occur,
*        check the time to do the statistics
*
* \param prAdapter      Pointer of Adapter Data Structure
*
* \return -
*/
/*----------------------------------------------------------------------------*/
VOID
statisticsIntEevnt (
    IN P_ADAPTER_T prAdapter
    )
{
    P_STATISTICS_INFO_T       prStatisInfo;
    OS_SYSTIME                rCurrentSysTime;

    DEBUGFUNC("statisticsIntEevnt");

    ASSERT(prAdapter);

    prStatisInfo = &prAdapter->rStatisticsInfo;

    if(prStatisInfo->fgEn == TRUE && prStatisInfo->fgUseTimerTrig == FALSE) {
        DBGLOG(REQ, TEMP, ("\n"));
        GET_CURRENT_SYSTIME(&rCurrentSysTime);
        if (CHECK_FOR_TIMEOUT(rCurrentSysTime,
                prStatisInfo->rLastIntPeekTime,
                MSEC_TO_SYSTIME(CFG_INT_PEEK_HW_COUNTERS_TIMEOUT_MSEC))) {
            DBGLOG(REQ, INFO, ("Int Event timeout\n"));
            DBGLOG(REQ, INFO, ("Current time = %ld, Previous time = %ld\n", \
                (UINT_32)rCurrentSysTime, (UINT_32)prStatisInfo->rLastIntPeekTime));
            statisticsPeekHWCounter(prAdapter);
            COPY_SYSTIME(prStatisInfo->rLastIntPeekTime, rCurrentSysTime);
        }
    }
    return;
}


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will set the MIBSCR and got related mib value from MIBSDR
*
* \param prAdapter      Pointer of Adapter Data Structure
*
* \return -
*/
/*----------------------------------------------------------------------------*/
VOID
statisticsPeekHWCounter (
    IN P_ADAPTER_T  prAdapter
    )
{
    P_TX_CTRL_T         prTxCtrl;
    P_RX_CTRL_T         prRxCtrl;
    UINT_32                 u4Tmp;

    DEBUGFUNC("statisticsPeekHWCounter");

    DBGLOG(REQ, LOUD, ("\n"));

    ASSERT(prAdapter);

    prTxCtrl = &prAdapter->rTxCtrl;
    prRxCtrl = &prAdapter->rRxCtrl;

    /* Query from MCR. */
    HAL_MCR_RD(prAdapter, MCR_MIBSCR, &u4Tmp);
    u4Tmp &= ~MIBSCR_INDEX_MASK;
    u4Tmp |= (MIBSCR_TX_COUNT_INDEX);
    HAL_MCR_WR(prAdapter, MCR_MIBSCR, u4Tmp);

    /* MIBSCR_TX_COUNT_INDEX */
    HAL_MCR_RD(prAdapter, MCR_MIBSDR, &u4Tmp);

   /* MIBSCR_BEACON_TX_COUNT_INDEX */
    HAL_MCR_RD(prAdapter, MCR_MIBSDR, &u4Tmp);
    TX_ADD_CNT(prTxCtrl, TX_BEACON_MMPDU_COUNT, u4Tmp);
    DBGLOG(REQ, LOUD, ("Beacon Tx count: %"DBG_PRINTF_64BIT_DEC", this time = %ld\n",\
        prTxCtrl->au8Statistics[TX_BEACON_MMPDU_COUNT], u4Tmp ));

    /* MIBSCR_FRAME_RETRY_COUNT_INDEX */
    HAL_MCR_RD(prAdapter, MCR_MIBSDR, &u4Tmp);

    /* MIBSCR_RTS_RETRY_COUNT_INDEX */
    HAL_MCR_RD(prAdapter, MCR_MIBSDR, &u4Tmp);

    HAL_MCR_RD(prAdapter, MCR_MIBSCR, &u4Tmp);
    u4Tmp &= ~MIBSCR_INDEX_MASK;
    u4Tmp |= (MIBSCR_RX_FCS_ERROR_COUNT_INDEX);
    HAL_MCR_WR(prAdapter, MCR_MIBSCR, u4Tmp);

    /* MIBSCR_RX_FCS_ERROR_COUNT_INDEX */
    HAL_MCR_RD(prAdapter, MCR_MIBSDR, &u4Tmp);
    RX_ADD_CNT(prRxCtrl, RX_BB_FCS_ERROR_COUNT, u4Tmp);
    DBGLOG(REQ, LOUD, ("pauCrcErr: %"DBG_PRINTF_64BIT_DEC", this time = %ld\n",\
        prRxCtrl->au8Statistics[RX_BB_FCS_ERROR_COUNT], u4Tmp ));

    /* MIBSCR_RX_FIFO_FULL_COUNT_INDEX */
    HAL_MCR_RD(prAdapter, MCR_MIBSDR, &u4Tmp);
    RX_ADD_CNT(prRxCtrl, RX_BB_FIFO_FULL_COUNT, u4Tmp);
    DBGLOG(REQ, LOUD, ("pauRxFifoFull: %"DBG_PRINTF_64BIT_DEC", this time = %ld\n",\
        prRxCtrl->au8Statistics[RX_BB_FIFO_FULL_COUNT], u4Tmp));

    /* MIBSCR_RX_MPDU_COUNT_INDEX */
    HAL_MCR_RD(prAdapter, MCR_MIBSDR, &u4Tmp);
    RX_ADD_CNT(prRxCtrl, RX_BB_MPDU_COUNT, u4Tmp);
    DBGLOG(REQ, LOUD, ("pauRxPkt: %"DBG_PRINTF_64BIT_DEC", this time = %ld\n",\
         prRxCtrl->au8Statistics[RX_BB_MPDU_COUNT], u4Tmp));

    /* MIBSCR_CHANNEL_IDLE_COUNT_INDEX */
    HAL_MCR_RD(prAdapter, MCR_MIBSDR, &u4Tmp);
    RX_ADD_CNT(prRxCtrl, RX_BB_CHANNEL_IDLE_COUNT, u4Tmp);
    DBGLOG(REQ, LOUD, ("pauChannelidle: %"DBG_PRINTF_64BIT_DEC", this time = %ld\n",\
         prRxCtrl->au8Statistics[RX_BB_CHANNEL_IDLE_COUNT], u4Tmp));

//Skip CCA and CCA/NAV/TX for 11h and 11k

    HAL_MCR_RD(prAdapter, MCR_MIBSCR, &u4Tmp);
    u4Tmp &= ~MIBSCR_INDEX_MASK;
    u4Tmp |= (MIBSCR_BEACON_TIMEOUT_COUNT_INDEX);
    HAL_MCR_WR(prAdapter, MCR_MIBSCR, u4Tmp);

    /* MIBSCR_BEACON_TIMEOUT_COUNT_INDEX */
    HAL_MCR_RD(prAdapter, MCR_MIBSDR, &u4Tmp);
    RX_ADD_CNT(prRxCtrl, RXTX_BEACON_TIMEOUT_COUNT, u4Tmp);
    DBGLOG(REQ, LOUD, ("Beacon Timeout : %"DBG_PRINTF_64BIT_DEC", this time = %ld\n",\
         prRxCtrl->au8Statistics[RXTX_BEACON_TIMEOUT_COUNT], u4Tmp));

}
