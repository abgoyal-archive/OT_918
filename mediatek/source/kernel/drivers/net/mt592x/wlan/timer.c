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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/timer.c#1 $
*/

/*! \file   "timer.c"
    \brief  This file include all the root timer and timer list implementation.


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
** $Log: timer.c $
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\25 2008-10-27 14:24:30 GMT mtk01084
**  fix the LINT warning
**  \main\maintrunk.MT5921\24 2008-10-01 11:26:13 GMT mtk01084
**  fix the timer stop function
**  \main\maintrunk.MT5921\23 2008-09-16 11:46:50 GMT mtk01084
**  modify interface on timerInitialize()
**  \main\maintrunk.MT5921\22 2008-08-11 14:07:41 GMT mtk01084
**  modify driver to meeting coding rules
**  \main\maintrunk.MT5921\21 2008-04-24 14:39:55 GMT mtk01084
**  add comments
**  \main\maintrunk.MT5921\20 2008-04-22 18:24:58 GMT mtk01084
**  add function to handle timer recovery on logic reset
**  \main\maintrunk.MT5921\19 2008-03-17 12:56:17 GMT mtk01084
**  refine the timer utility function
**  \main\maintrunk.MT5921\18 2008-02-27 12:11:27 GMT mtk01461
**  Update comment
**  \main\maintrunk.MT5921\17 2008-02-21 22:48:30 GMT mtk01084
**  return values in related function
**  \main\maintrunk.MT5921\16 2008-01-31 22:24:57 GMT mtk01385
**  1. Fix CE 4.2 compiling error.
**  \main\maintrunk.MT5921\15 2007-11-27 20:03:57 GMT mtk01084
**  fix Lint warning
**  \main\maintrunk.MT5921\14 2007-11-27 19:57:14 GMT mtk01084
**  update timer unitialization function
**  \main\maintrunk.MT5921\13 2007-11-20 10:34:50 GMT mtk01084
**  modify debug message
**  \main\maintrunk.MT5921\12 2007-10-25 14:26:25 GMT mtk01084
**  prevent ownback again when HW root timer is used
** Revision 1.2  2007/07/12 06:09:35  MTK01084
** update timer functions to meet PM related requirements
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
/*----------------------------------------------------------------------------*/
/*!
* \brief This routines is called to initialize a root timer.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[in] pvfnTimerHandler Pointer to the callback timer handler.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
timerInitialize (
    IN P_ADAPTER_T          prAdapter,
    IN PFN_TIMER_CALLBACK   prfnTimerHandler
    )
{
    ASSERT(prAdapter);
    ASSERT(prfnTimerHandler);

    LINK_INITIALIZE(&prAdapter->rTimerList);

#if CFG_USE_SW_ROOT_TIMER
    kalOsTimerInitialize(prAdapter->prGlueInfo, (PVOID)prfnTimerHandler);
#else
    nichtTimerInit(prAdapter, WLAN_ROOT_TIMER, prfnTimerHandler);

    NIC_SET_INT_EVENT(prAdapter, WLAN_ROOT_TIMER_INT);
#endif

    return;
} /* end of timerInitialize() */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routines is called to initialize a root timer.
*
* \param[in] *prAdapter Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
timerUnInitialize (
    IN P_ADAPTER_T  prAdapter
    )
{
    ASSERT(prAdapter);

    LINK_INITIALIZE(&prAdapter->rTimerList);

#if CFG_USE_SW_ROOT_TIMER
    /* <TODO> to reclaim the resource */

#else
    nichtCancelTimer(prAdapter, WLAN_ROOT_TIMER);

    NIC_UNSET_INT_EVENT(prAdapter, WLAN_ROOT_TIMER_INT);

    nichtKillTimer(prAdapter, WLAN_ROOT_TIMER);
#endif

    return;
} /* end of timerInitialize() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routines is called to initialize a timer.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[in] prTimer Pointer to a timer structure.
* \param[in] pfnFunc Pointer to the call back function.
* \param[in] u4Data Parameter for call back function.
* \param[in] fgNeedHwAccess Parameter for indicating the requirement of HW access.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
timerInitTimer (
    IN P_ADAPTER_T              prAdapter,
    IN P_TIMER_T                prTimer,
    IN PFN_MGMT_TIMEOUT_FUNC    pfFunc,
    IN UINT_32                  u4Data,
    IN BOOLEAN                  fgNeedHwAccess
    )
{
    ASSERT(prAdapter);
    ASSERT(prTimer);
    ASSERT(pfFunc);

    LINK_ENTRY_INITIALIZE(&prTimer->rLinkEntry);
    prTimer->pfMgmtTimeOutFunc  = pfFunc;
    prTimer->u4Data             = u4Data;
    prTimer->fgNeedHwAccess     = fgNeedHwAccess;

    return;

} /* end of timerInitTimer() */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to set the time to do the time out check.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
* \param[in] rTimeout Time out interval from current time.
*
* \retval TRUE Success.
*
*/
/*----------------------------------------------------------------------------*/
BOOL
timerSetTimer (
    IN P_ADAPTER_T prAdapter,
    IN OS_SYSTIME  rTimeout
    )
{
    ASSERT(prAdapter);

#if CFG_USE_SW_ROOT_TIMER

    return kalSetTimer(prAdapter->prGlueInfo, rTimeout);

#else
    /* milli-second to TU, and include the OS timer resolution */
    return nichtSetTimer(prAdapter,
                         WLAN_ROOT_TIMER,
                         HW_TIMER_MODE_ONE_SHOT,
                         HW_TIMER_FUNC_TSF_FREE_RUN,
                         TRUE,
                         HW_TIMER_UNIT_1_TU,
                         SYSTIME_TO_TU(rTimeout) + (MSEC_PER_SEC / KAL_HZ));
#endif
} /* end of kalSetTimer() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routines is called to stop a timer.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[in] prTimer Pointer to a timer structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
timerStopTimer (
    IN P_ADAPTER_T              prAdapter,
    IN P_TIMER_T                prTimer

    )
{
    ASSERT(prAdapter);
    ASSERT(prTimer);

    if (timerPendingTimer(prTimer)) {
        P_LINK_T prTimerList = &prAdapter->rTimerList;

        LINK_REMOVE_KNOWN_ENTRY(prTimerList, &prTimer->rLinkEntry);

#if (!CFG_USE_SW_ROOT_TIMER)
        /* When using HW timer,
           kill the HW timer source if no pending tasks to serve */
        if (prTimerList->u4NumElem == 0) {
            nichtKillTimer(prAdapter,
                           WLAN_ROOT_TIMER);
        }
#endif
    }
} /* timerStopTimer */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routines is called to start a timer.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[in] prTimer Pointer to a timer structure.
* \param[in] u4TimeoutMs Timeout to issue the timer and call back function (unit: ms).
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
timerStartTimer (
    IN P_ADAPTER_T              prAdapter,
    IN P_TIMER_T                prTimer,
    IN UINT_32                  u4TimeoutMs
    )
{
    P_LINK_T prTimerList;
    OS_SYSTIME rExpiredSysTime;

    ASSERT(prAdapter);
    ASSERT(prTimer);

    prTimerList= &prAdapter->rTimerList;

    /* To avoid infinite loop in function wlanDoTimeOutCheck(),
     * zero interval is not permitted.
     */
    if (u4TimeoutMs == 0) {
        u4TimeoutMs = 1;
    }

    rExpiredSysTime = kalGetTimeTick() + MSEC_TO_SYSTIME(u4TimeoutMs);

    /* If no timer pending or the fast time interval is used. */
    if (prTimerList->prNext == (P_LINK_ENTRY_T)prTimerList ||
        TIME_BEFORE(rExpiredSysTime, prAdapter->rNextExpiredSysTime)) {
        if (timerSetTimer(prAdapter, MSEC_TO_SYSTIME(u4TimeoutMs))) {
            prAdapter->rNextExpiredSysTime = rExpiredSysTime;
        }
    }

    /* Add this timer to checking list */
    prTimer->rExpiredSysTime = rExpiredSysTime;

    if (!timerPendingTimer(prTimer)) {
        LINK_INSERT_TAIL(prTimerList, &prTimer->rLinkEntry);
    }

    return;
} /* timerStartTimer */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routines is called to check the timer list.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
timerDoTimeOutCheck (
    IN P_ADAPTER_T  prAdapter
    )
{
    P_LINK_T prTimerList;
    P_LINK_ENTRY_T prLinkEntry;
    P_TIMER_T prTimer;
    OS_SYSTIME rCurSysTime;

    DEBUGFUNC("timerDoTimeOutCheck");

    ASSERT(prAdapter);

    prTimerList= &prAdapter->rTimerList;

    GET_CURRENT_SYSTIME(&rCurSysTime);

    /* Set the permitted max timeout value for new one */
    prAdapter->rNextExpiredSysTime = rCurSysTime + MGMT_MAX_TIMEOUT_INTERVAL;

    LINK_FOR_EACH(prLinkEntry, prTimerList) {
        prTimer = LINK_ENTRY(prLinkEntry, TIMER_T, rLinkEntry);

        /* Check if this entry is timeout. */
        if (!TIME_BEFORE(rCurSysTime, prTimer->rExpiredSysTime)) {
            timerStopTimer(prAdapter, prTimer);

#if CFG_USE_SW_ROOT_TIMER
            if (prTimer->fgNeedHwAccess) {
                ARB_ACQUIRE_POWER_CONTROL_FROM_PM(prAdapter);


                DBGLOG(INIT, INFO, ("Timer Handler: ->%s(): SYS_TIME = %ld\n",
                    prTimer->aucDbgString, u4CurTime));

                (prTimer->pfMgmtTimeOutFunc)(prTimer->u4Data); // It may add timer there.

                DBGLOG(INIT, INFO, ("Timer Handler: <-%s()\n", prTimer->aucDbgString));

                ARB_RECLAIM_POWER_CONTROL_TO_PM(prAdapter);
            }
            else
#endif
            {

                DBGLOG(INIT, INFO, ("(NO HW ACCESS)Timer Handler: ->%s(): SYS_TIME = %ld\n",
                    prTimer->aucDbgString, rCurSysTime));


                (prTimer->pfMgmtTimeOutFunc)(prTimer->u4Data); // It may add timer there.

                DBGLOG(INIT, INFO, ("(NO HW ACCESS)Timer Handler: <-%s()\n", prTimer->aucDbgString));
            }

            /* Search entire list again because of nest del and add timers
             * and current MGMT_TIMER could be volatile after stopped
             */
            prLinkEntry = (P_LINK_ENTRY_T)prTimerList;
        }
        else if (TIME_BEFORE(prTimer->rExpiredSysTime, prAdapter->rNextExpiredSysTime)) {
            prAdapter->rNextExpiredSysTime = prTimer->rExpiredSysTime;
        }
    } /* end of for loop */

    /* Setup the prNext timeout event. It is possible the timer was already
     * set in the above timeout callback function.
     */
    if (!LINK_IS_EMPTY(prTimerList)) {
        ASSERT(TIME_AFTER(prAdapter->rNextExpiredSysTime, rCurSysTime));

        if (!timerSetTimer(prAdapter,
                           (OS_SYSTIME)((INT_32)prAdapter->rNextExpiredSysTime - (INT_32)rCurSysTime))) {
            /* If fail to set timer, set max value to permit new one */
            prAdapter->rNextExpiredSysTime = rCurSysTime + MGMT_MAX_TIMEOUT_INTERVAL;
        }
    }

} /* end of wlanDoTimeOutCheck() */

#if !CFG_USE_SW_ROOT_TIMER
/*----------------------------------------------------------------------------*/
/*!
* \brief This routines is called to check the timer list.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
timerDoTimeOutCheckOnLogicReset (
    IN P_ADAPTER_T  prAdapter
    )
{
    P_LINK_T prTimerList;
    P_LINK_ENTRY_T prLinkEntry;
    P_TIMER_T prTimer;
    OS_SYSTIME rCurSysTime;

    DEBUGFUNC("timerDoTimeOutCheckOnLogicReset");

    ASSERT(prAdapter);

    prTimerList= &prAdapter->rTimerList;

    GET_CURRENT_SYSTIME(&rCurSysTime);

    /* Set the permitted max timeout value for new one */
    prAdapter->rNextExpiredSysTime = rCurSysTime + MGMT_MAX_TIMEOUT_INTERVAL;

    LINK_FOR_EACH(prLinkEntry, prTimerList) {
        prTimer = LINK_ENTRY(prLinkEntry, TIMER_T, rLinkEntry);

        /* Check if this entry is timeout. */
        if (!TIME_BEFORE(rCurSysTime, prTimer->rExpiredSysTime)) {

            /* not to do timer callback due to it will also cause another nested state transition,
               which is not allowed in current architecture */

            prAdapter->rNextExpiredSysTime = rCurSysTime + 1;
            break;
        }
        else if (TIME_BEFORE(prTimer->rExpiredSysTime, prAdapter->rNextExpiredSysTime)) {
            prAdapter->rNextExpiredSysTime = prTimer->rExpiredSysTime;
        }
    } /* end of for loop */

    /* Setup the prNext timeout event. It is possible the timer was already
     * set in the above timeout callback function.
     */
    if (!LINK_IS_EMPTY(prTimerList)) {
        ASSERT(TIME_AFTER(prAdapter->rNextExpiredSysTime, rCurSysTime));

        if (!timerSetTimer(prAdapter,
                           (OS_SYSTIME)((INT_32)prAdapter->rNextExpiredSysTime - (INT_32)rCurSysTime))) {
            /* If fail to set timer, set max value to permit new one */
            prAdapter->rNextExpiredSysTime = rCurSysTime + MGMT_MAX_TIMEOUT_INTERVAL;
        }
    }

} /* end of wlanDoTimeOutCheck() */
#endif

