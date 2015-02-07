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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/timer.h#1 $
*/

/*! \file   timer.h
    \brief  Declaration of timer obj and related timer macro for setup time out
            event.

    In this file we declare the timer object and provide several macro for Protocol
    functional blocks to setup their own time out event.
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
** $Log: timer.h $
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\19 2008-12-24 16:57:28 GMT mtk01461
**  Fix SYSTIME_TO_MSEC macro
**  \main\maintrunk.MT5921\18 2008-12-24 13:48:28 GMT mtk01084
**  \main\maintrunk.MT5921\17 2008-12-24 13:37:36 GMT mtk01084
**  fix SYSTIME_TO_MSEC macro under 1 compiler option
**  \main\maintrunk.MT5921\16 2008-12-01 13:56:01 GMT mtk01461
**  Remove Warning 613: Possible use of null pointer from lint
**  \main\maintrunk.MT5921\15 2008-10-27 14:21:22 GMT mtk01084
**  fix the LINT warning
**  \main\maintrunk.MT5921\14 2008-09-16 11:47:26 GMT mtk01084
**  modify interface on timerInitialize()
**  \main\maintrunk.MT5921\13 2008-04-22 18:24:50 GMT mtk01084
**  add function to handle timer recovery on logic reset
**  \main\maintrunk.MT5921\12 2008-03-17 12:56:32 GMT mtk01084
**  refine the timer utility function
**  \main\maintrunk.MT5921\11 2008-01-07 15:05:36 GMT mtk01461
**  Update debug message length
**  \main\maintrunk.MT5921\10 2007-12-11 00:09:05 GMT mtk01461
**  Fix systime to TU macro
**  \main\maintrunk.MT5921\9 2007-12-04 18:10:56 GMT mtk01461
**  Update TU related definition
**  \main\maintrunk.MT5921\8 2007-11-27 19:54:13 GMT mtk01084
**  support timer unitialization function
** Revision 1.2  2007/07/12 06:09:51  MTK01084
** update timer functions to meet PM related requirements
**
**
*/

#ifndef _TIMER_H
#define _TIMER_H

/*******************************************************************************
*                         C O M P I L E R   F L A G S
********************************************************************************
*/

/*******************************************************************************
*                    E X T E R N A L   R E F E R E N C E S
********************************************************************************
*/
#include "link.h"

/*******************************************************************************
*                              C O N S T A N T S
********************************************************************************
*/
#undef MSEC_PER_SEC
#define MSEC_PER_SEC                    1000
#undef USEC_PER_MSEC
#define USEC_PER_MSEC                   1000
#define USEC_PER_TU                     1024 /* microsecond */


#define MGMT_MAX_TIMEOUT_INTERVAL       ((UINT_32)0x7fffffff)


/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/
typedef VOID (*PFN_MGMT_TIMEOUT_FUNC)(UINT_32);

typedef struct _TIMER_T {
    LINK_ENTRY_T            rLinkEntry;
    OS_SYSTIME              rExpiredSysTime;
    UINT_32                 u4Data;
    BOOLEAN                 fgNeedHwAccess;
    PFN_MGMT_TIMEOUT_FUNC   pfMgmtTimeOutFunc;
#if DBG
    UINT_8                  aucDbgString[64];
#endif
} TIMER_T, *P_TIMER_T;



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
/* Check if time "a" is before time "b" */
/* In 32-bit variable, 0x00000001~0x7fffffff -> positive number,
 *                     0x80000000~0xffffffff -> negative number
 */
#define TIME_BEFORE(a,b)        ((UINT_32)((UINT_32)(a) - (UINT_32)(b)) > 0x7fffffff)

/* #define TIME_BEFORE(a,b)        ((INT_32)((INT_32)(b) - (INT_32)(a)) > 0)
 * may cause UNexpect result between Free build and Check build for WinCE
 */

#define TIME_AFTER(a,b)         TIME_BEFORE(b,a)


/* The macros to convert OS system time */
#if (KAL_HZ <= MSEC_PER_SEC) && !(MSEC_PER_SEC % KAL_HZ)
    #define SYSTIME_TO_MSEC(_systime)           ((_systime) * (MSEC_PER_SEC / KAL_HZ))
    #define MSEC_TO_SYSTIME(_msec)              (((_msec) + (MSEC_PER_SEC / KAL_HZ) - 1) / \
                                                 (MSEC_PER_SEC / KAL_HZ))
#elif (KAL_HZ > MSEC_PER_SEC) && !(KAL_HZ % MSEC_PER_SEC)
    #define SYSTIME_TO_MSEC(_systime)           (((_systime) + (KAL_HZ / MSEC_PER_SEC) - 1) / \
                                                 (KAL_HZ / MSEC_PER_SEC))
    #define MSEC_TO_SYSTIME(_msec)              ((_msec) * (KAL_HZ / MSEC_PER_SEC))
#else
    #define SYSTIME_TO_MSEC(_systime)           (((_systime) * MSEC_PER_SEC) / KAL_HZ)
    #define MSEC_TO_SYSTIME(_msec)              (((_msec) * KAL_HZ + MSEC_PER_SEC - 1) / \
                                                 MSEC_PER_SEC)
#endif

#define SYSTIME_TO_SEC(_systime)            ((_systime) / KAL_HZ)
#define SEC_TO_SYSTIME(_sec)                ((_sec) * KAL_HZ)


/* The macros to convert second & millisecond */
#define MSEC_TO_SEC(_msec)                  ((_msec) / MSEC_PER_SEC)
#define SEC_TO_MSEC(_sec)                   ((UINT_32)(_sec) * MSEC_PER_SEC)


/* The macros to convert millisecond & microsecond */
#define USEC_TO_MSEC(_usec)                 ((_usec) / USEC_PER_MSEC)
#define MSEC_TO_USEC(_msec)                 ((UINT_32)(_msec) * USEC_PER_MSEC)


/* The macros to convert TU & microsecond, TU & millisecond */
#define TU_TO_USEC(_tu)                     ((_tu) * USEC_PER_TU)
#define TU_TO_MSEC(_tu)                     USEC_TO_MSEC( TU_TO_USEC(_tu) )


/* The macros to convert TU & & OS system time, round up by 0.5 */
#define TU_TO_SYSTIME(_tu)                  MSEC_TO_SYSTIME( TU_TO_MSEC(_tu) )
#define SYSTIME_TO_TU(_systime)             \
    ((SYSTIME_TO_USEC(_systime) + ((USEC_PER_TU / 2) - 1)) / USEC_PER_TU)


/* The macros to convert OS system time & microsecond */
#define SYSTIME_TO_USEC(_systime)           (SYSTIME_TO_MSEC(_systime) * USEC_PER_MSEC)


/* The macro to get the current OS system time */
#define GET_CURRENT_SYSTIME(_systime_p)     {*(_systime_p) = kalGetTimeTick();}

/* The macro to copy the system time */
#define COPY_SYSTIME(_destTime, _srcTime)   (_destTime) = (_srcTime)

/* The macro to get the system time difference between t1 and t2 (t1 - t2) */
#define GET_SYSTIME_DIFFERENCE(_time1, _time2, _diffTime) \
        (_diffTime) = (_time1) - (_time2)

/* The macro to check for the expiration, if TRUE means _currentTime >= _expirationTime */
#define CHECK_FOR_EXPIRATION(_currentTime, _expirationTime) \
        ((UINT_32)(_currentTime) - (UINT_32)(_expirationTime) <= 0x7fffffffUL)

/* The macro to check for the timeout */
#define CHECK_FOR_TIMEOUT(_currentTime, _timeoutStartingTime, _timeout) \
    CHECK_FOR_EXPIRATION((_currentTime), ((_timeoutStartingTime) + (_timeout)))

/* The macro to set the expiration time with a specified timeout *//* Watch out for round up.*/
#define SET_EXPIRATION_TIME(_expirationTime, _timeout) \
        { \
            GET_CURRENT_SYSTIME(&(_expirationTime)); \
            (_expirationTime) += (OS_SYSTIME)(_timeout); \
        }

#define timerRenewTimer(adapter,tmr,interval) \
        timerStartTimer(adapter,tmr,interval,(tmr)->function,(tmr)->data)

#define timerCheckTimeout(eol) \
        ((INT_32)kalGetTimeTick() - (INT_32)(eol) >= 0)

#define MGMT_INIT_TIMER(_adapter_p, _timer, _callbackFunc) \
        timerInitTimer(_adapter_p, &(_timer), (UINT_32)(_callbackFunc))


/*******************************************************************************
*                  F U N C T I O N   D E C L A R A T I O N S
********************************************************************************
*/
VOID
timerInitialize (
    IN P_ADAPTER_T  prAdapter,
    IN PFN_TIMER_CALLBACK   prfnTimerHandler
    );

VOID
timerUnInitialize (
    IN P_ADAPTER_T  prAdapter
    );

VOID
timerInitTimer (
    IN P_ADAPTER_T              prAdapter,
    IN P_TIMER_T                prTimer,
    IN PFN_MGMT_TIMEOUT_FUNC    pfFunc,
    IN UINT_32                  u4Data,
    IN BOOLEAN                  fgNeedHwAccess
    );

VOID
timerStopTimer (
    IN P_ADAPTER_T              prAdapter,
    IN P_TIMER_T                prTimer
    );

VOID
timerStartTimer (
    IN P_ADAPTER_T              prAdapter,
    IN P_TIMER_T                prTimer,
    IN UINT_32                  u4TimeoutMs
    );

VOID
timerDoTimeOutCheck (
    IN P_ADAPTER_T  prAdapter
    );

#if !CFG_USE_SW_ROOT_TIMER
VOID
timerDoTimeOutCheckOnLogicReset (
    IN P_ADAPTER_T  prAdapter
    );
#endif

/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/
__KAL_INLINE__
INT_32
timerPendingTimer (
    IN P_TIMER_T prTimer
    )
{
    ASSERT(prTimer);

    return prTimer->rLinkEntry.prNext != NULL;
}

#endif /* _TIMER_H */

