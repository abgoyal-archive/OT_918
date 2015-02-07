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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/nic_hw_timer.c#1 $
*/

/*************************************************************************
* Copyright (c) 2006 MediaTek Inc.
*
* All rights reserved. Copying, compilation, modification, distribution
* or any other use whatsoever of this material is strictly prohibited
* except in accordance with a Software License Agreement with
* MediaTek Inc.
**************************************************************************/

/*************************************************************************
GENERAL DESCRIPTION
********************
This file contains the ISR routines of the MediaTek 802.11 Wireless LAN
SoC.
*/

/*
** $Log: nic_hw_timer.c $
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\16 2008-12-01 20:42:29 GMT mtk01084
**  fix Lint warning
**  \main\maintrunk.MT5921\15 2008-12-01 19:05:16 GMT mtk01084
**  prevent Lint warning
**  \main\maintrunk.MT5921\14 2008-09-16 19:25:02 GMT mtk01084
**  modify interface on nichtTimerInit()
**  \main\maintrunk.MT5921\13 2008-08-18 09:21:05 GMT mtk01084
**  modification for coding rules conformance
**  \main\maintrunk.MT5921\12 2008-07-10 16:38:05 GMT mtk01084
**  support 802.11d related functions
**  \main\maintrunk.MT5921\11 2008-03-12 09:52:28 GMT mtk01461
**  Fix compile warning in Linux
**  \main\maintrunk.MT5921\10 2008-02-01 10:19:50 GMT mtk01385
**  1. Fix WinCE 4.2 compiling error.
**  \main\maintrunk.MT5921\9 2008-01-16 20:50:02 GMT mtk01084
**  add lines for checking timer period in register length
**  \main\maintrunk.MT5921\8 2007-10-26 10:26:55 GMT mtk01084
**  remove un-necessary line
** Revision 1.1  2007/07/05 14:06:38  MTK01084
** Initial version
**
** Revision 1.5  2007/02/15 07:37:36  MTK01084
** modify coding syntax
**
** Revision 1.4  2006/12/19 01:45:34  MTK01084
** modify routine in setting up timer due to the spec change
**
** Revision 1.3  2006/11/01 13:06:47  MTK01104
** To avoid compile warning.
**
** Revision 1.2  2006/11/01 12:55:44  MTK01084
** initialize HW timer to basic mode once initial
**
** Revision 1.1  2006/10/31 06:59:06  MTK01084
** update HW timer utility functions
**
*/

/************************************************************************
*                E X T E R N A L   R E F E R E N C E S
*************************************************************************
*/
#include "precomp.h"


/************************************************************************
*                          F U N C T I O N S
*************************************************************************
*/
/*----------------------------------------------------------------------------*/
/*!
* \brief Initial the registration of the HW timer
*
* \param[in] pvAdapter Pointer to the Adapter structure.
* \param[in] rTimerId HW timer ID.
* \param[in] pvfnTimeout Timeout callback function.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
nichtTimerInit (
    IN P_ADAPTER_T prAdapter,
    IN ENUM_HW_TIMER_T rTimerId,
    IN PFN_TIMER_CALLBACK prfnTimeout
    )
{
    P_TIMER_INFO_T prTimerInfo;

    DEBUGFUNC("htInitTimer");

    ASSERT(prAdapter);
    ASSERT(prfnTimeout);

    prTimerInfo = &prAdapter->rTimerInfo;

    if (prTimerInfo->afgHwTimerInUsed[rTimerId]) {
        WARNLOG(("Duplicated GP-Timer allocated"));
    }

    /* register the timer callback function */
    prTimerInfo->apfHwTimerHandler[rTimerId] = prfnTimeout;
    prTimerInfo->afgHwTimerInUsed[rTimerId] = TRUE;

}

/*----------------------------------------------------------------------------*/
/*!
* \brief Cancel the registration of the HW timer
*
* \param[in] pvAdapter Pointer to the Adapter structure.
* \param[in] rTimerId HW timer ID.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
nichtCancelTimer (
    IN P_ADAPTER_T prAdapter,
    IN ENUM_HW_TIMER_T rTimerId
    )
{
    P_TIMER_INFO_T prTimerInfo;

    ASSERT(prAdapter);

    prTimerInfo = &prAdapter->rTimerInfo;

    /* de-register the timer callback function */
    prTimerInfo->apfHwTimerHandler[rTimerId] = NULL;
    prTimerInfo->afgHwTimerInUsed[rTimerId] = FALSE;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief Start HW timer
*
* \param[in] pvAdapter Pointer to the Adapter structure.
* \param[in] rTimerId HW timer ID.
* \param[in] rMode Timer is single-shot or periodically mode.
* \param[in] rAltFunc Timer is bound with alternative function.
* \param[in] fgTimeupEn Timer will issue interrupt on timeup event.
* \param[in] rUnit The unit of the timer (us/ TU).
* \param[in] u4Count The period of time for this timer.
*
* \retval TRUE Setup timer successfully
* \retval FALSE Fail to setup timer
*/
/*----------------------------------------------------------------------------*/
BOOL
nichtSetTimer (
    IN P_ADAPTER_T      prAdapter,
    IN ENUM_HW_TIMER_T  rTimerId,
    IN HW_TIMER_MODE_E  rMode,
    IN HW_TIMER_FUNC_E  rAltFunc,
    IN BOOLEAN          fgTimeupEn,
    IN HW_TIMER_UNIT_E  rUnit,
    IN UINT_32          u4Count
    )
{
    P_TIMER_INFO_T prTimerInfo;
    UINT_32 u4RegMptcr;

    DEBUGFUNC("htSetTimer");

    ASSERT(prAdapter);

    prTimerInfo = &prAdapter->rTimerInfo;

    /* timer should be initialized at first */
    if (!prTimerInfo->afgHwTimerInUsed[rTimerId]) {
        return FALSE;
    }

    if ((rTimerId != ENUM_TIMER_2) && (rTimerId != ENUM_TIMER_3)) {
        ASSERT(0);
        return FALSE;
    }

    if (u4Count == 0) {
        ASSERT(u4Count);
        return FALSE;
    }

    if (u4Count > TDR_TIME_VALUE_MAX_T2_T3) {
        DBGLOG(NIC, ERROR, ("timer counter overflow: 0x%lx (only 16 bit is available)\n", u4Count));
        ASSERT(0);
        u4Count = TDR_TIME_VALUE_MAX_T2_T3;
    }

#if DBG
    if (!prTimerInfo->apfHwTimerHandler[rTimerId]) {
        DBGLOG(NIC, WARN, ("Install timer:%d without handler", rTimerId));
    }
#endif

    /* get register value */
    HAL_MCR_RD(prAdapter, MCR_MPTCR, &u4RegMptcr);

    /* disable timer */
    HAL_MCR_WR(prAdapter, MCR_MPTCR, u4RegMptcr & ~BIT(rTimerId + 17));

    /* Install the timer */
    HAL_MCR_WR(prAdapter,
                MCR_TDR,
                ((UINT_32)rTimerId << 30) |
                (TDR_TIME_VALUE_CTRL_PERIOD) |
                (fgTimeupEn ? TDR_TIMEUP_ENABLE : 0) |
                (rAltFunc << 24) |
                ((rMode == HW_TIMER_MODE_PERIODIC) ? TDR_TIMER_MODE_AUTO_REPEAT : 0) |
                ((rUnit == HW_TIMER_UNIT_1_TU) ? TDR_TIMER_COUNT_UNIT_TU : 0) |
                (u4Count & TDR_TIME_VALUE_MASK));

    /* enable timer */
    HAL_MCR_WR(prAdapter, MCR_MPTCR, u4RegMptcr | BIT(rTimerId + 17));

    return TRUE;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief Start HW TSF timer
*
* \param[in] pvAdapter Pointer to the Adapter structure.
* \param[in] rTimerId HW timer ID.
* \param[in] rMode Timer is single-shot or periodically mode.
* \param[in] rAltFunc Timer is bound with alternative function.
* \param[in] fgTimeupEn Timer will issue interrupt on timeup event.
* \param[in] u4StartTime The start time of the TSF timer.
* \param[in] u4Period The period for the TSF timer.
*
* \retval TRUE Setup timer successfully
* \retval FALSE Fail to setup timer
*/
/*----------------------------------------------------------------------------*/
BOOL
nichtSetTsfTimer (
    IN P_ADAPTER_T prAdapter,
    IN ENUM_HW_TIMER_T rTimerId,
    IN HW_TIMER_MODE_E rMode,
    IN HW_TIMER_FUNC_E rAltFunc,
    IN BOOLEAN fgTimeupEn,
    IN UINT_32 u4StartTime,
    IN UINT_32 u4Period
    )
{
    UINT_32 u4RegMptcr;
    P_TIMER_INFO_T prTimerInfo;

    DEBUGFUNC("nichtSetTsfTimer");

    ASSERT(prAdapter);

    prTimerInfo = &prAdapter->rTimerInfo;

    /* timer should be initialized at first */
    if (!prTimerInfo->afgHwTimerInUsed[rTimerId]) {
        return FALSE;
    }

    if ((rTimerId != ENUM_TIMER_0) && (rTimerId != ENUM_TIMER_1)) {
        ASSERT(0);
        return FALSE;
    }

    if (!prTimerInfo->apfHwTimerHandler[rTimerId]) {
        DBGLOG(NIC, WARN, ("Install timer:%d without handler", rTimerId));
    }

    if ((u4StartTime >= TDR_TIME_VALUE_MAX_T0_T1)) {
        DBGLOG(NIC, ERROR, ("timer start time counter overflow: 0x%lx (only 22 bit is available)\n", u4StartTime));
        ASSERT(0);
        u4StartTime = TDR_TIME_VALUE_MAX_T0_T1;
    }
    if ((u4Period >= TDR_TIME_VALUE_MAX_T0_T1)) {
        DBGLOG(NIC, ERROR, ("timer period counter overflow: 0x%lx (only 22 bit is available)\n", u4Period));
        ASSERT(0);
        u4Period = TDR_TIME_VALUE_MAX_T0_T1;
    }

    /* get register value */
    HAL_MCR_RD(prAdapter, MCR_MPTCR, &u4RegMptcr);

    /* disable timer */
    HAL_MCR_WR(prAdapter, MCR_MPTCR, u4RegMptcr & ~BIT(rTimerId + 17));

    /* Install the timer */
    //start time
    HAL_MCR_WR(prAdapter,
                MCR_TDR,
                ((UINT_32)rTimerId << 30) |
                (fgTimeupEn ? TDR_TIMEUP_ENABLE : 0) |
                (rAltFunc << 24) |
                ((rMode == HW_TIMER_MODE_PERIODIC) ? TDR_TIMER_MODE_AUTO_REPEAT : 0) |
                (u4StartTime & TDR_TIME_VALUE_MASK));

    //period
    HAL_MCR_WR(prAdapter,
                MCR_TDR,
                ((UINT_32)rTimerId << 30) |
                TDR_TIME_VALUE_CTRL_PERIOD |
                (fgTimeupEn ? TDR_TIMEUP_ENABLE : 0) |
                (rAltFunc << 24) |
                ((rMode == HW_TIMER_MODE_PERIODIC) ? TDR_TIMER_MODE_AUTO_REPEAT : 0) |
                (u4StartTime & TDR_TIME_VALUE_MASK));

    /* enable timer */
    HAL_MCR_WR(prAdapter, MCR_MPTCR, u4RegMptcr | BIT(rTimerId + 17));

    return TRUE;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief Stop HW timer
*
* \param[in] pvAdapter Pointer to the Adapter structure.
* \param[in] rTimerId HW timer ID.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
nichtKillTimer (
    IN P_ADAPTER_T prAdapter,
    IN ENUM_HW_TIMER_T rTimerId
    )
{
    UINT_32 u4RegValue;

    ASSERT(prAdapter);

    /* disable timer */
    HAL_MCR_RD(prAdapter, MCR_MPTCR, &u4RegValue);
    HAL_MCR_WR(prAdapter, MCR_MPTCR, u4RegValue & ~BIT(rTimerId + 17));

}

/*----------------------------------------------------------------------------*/
/*!
* \brief Procedure for HW T0 timer handler
*
* \param[in] pvAdapter Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
nicProcesT0TimeupInterrupt (
    IN P_ADAPTER_T      prAdapter
    )
{
    P_TIMER_INFO_T  prTimerInfo;

    ASSERT(prAdapter);

    prTimerInfo = &prAdapter->rTimerInfo;

    DEBUGFUNC("nicProcesT0TimeupInterrupt");

    DBGLOG(NIC, INFO, ("T0 timeup\n"));

    if (prTimerInfo->apfHwTimerHandler[ENUM_TIMER_0]) {
        prTimerInfo->apfHwTimerHandler[ENUM_TIMER_0](prAdapter);
    }
}

/*----------------------------------------------------------------------------*/
/*!
* \brief Procedure for HW T1 timer handler
*
* \param[in] pvAdapter Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
nicProcesT1TimeupInterrupt (
    IN P_ADAPTER_T      prAdapter
    )
{
    P_TIMER_INFO_T  prTimerInfo;

    ASSERT(prAdapter);

    prTimerInfo = &prAdapter->rTimerInfo;

    DEBUGFUNC("nicProcesT1TimeupInterrupt");

    DBGLOG(NIC, INFO, ("T1 timeup\n"));

    if (prTimerInfo->apfHwTimerHandler[ENUM_TIMER_1]) {
        prTimerInfo->apfHwTimerHandler[ENUM_TIMER_1](prAdapter);
    }
}

/*----------------------------------------------------------------------------*/
/*!
* \brief Procedure for HW T2 timer handler
*
* \param[in] pvAdapter Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
nicProcesT2TimeupInterrupt (
    IN P_ADAPTER_T      prAdapter
    )
{
    P_TIMER_INFO_T  prTimerInfo;

    ASSERT(prAdapter);

    prTimerInfo = &prAdapter->rTimerInfo;

    DEBUGFUNC("nicProcesT2TimeupInterrupt");

    DBGLOG(NIC, INFO, ("T2 timeup\n"));

    if (prTimerInfo->apfHwTimerHandler[ENUM_TIMER_2]) {
        prTimerInfo->apfHwTimerHandler[ENUM_TIMER_2](prAdapter);
    }
}

/*----------------------------------------------------------------------------*/
/*!
* \brief Procedure for HW T3 timer handler
*
* \param[in] pvAdapter Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
nicProcesT3TimeupInterrupt (
    IN P_ADAPTER_T      prAdapter
    )
{
    P_TIMER_INFO_T  prTimerInfo;

    ASSERT(prAdapter);

    prTimerInfo = &prAdapter->rTimerInfo;

    DEBUGFUNC("nicProcesT3TimeupInterrupt");

    DBGLOG(NIC, INFO, ("T3 timeup\n"));

    if (prTimerInfo->apfHwTimerHandler[ENUM_TIMER_3]) {
        prTimerInfo->apfHwTimerHandler[ENUM_TIMER_3](prAdapter);
    }
}


