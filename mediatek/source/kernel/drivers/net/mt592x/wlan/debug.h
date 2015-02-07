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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/debug.h#2 $
*/

/*! \file   debug.h
    \brief  Definition of SW debugging level.

    In this file, it describes the definition of various SW debugging levels and
    assert functions.
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
** $Log: debug.h $
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\26 2009-09-03 11:34:25 GMT mtk01088
**  define the wapi debug level
**  \main\maintrunk.MT5921\25 2009-07-06 20:27:49 GMT mtk01088
**  add a debug level for wapi
**  \main\maintrunk.MT5921\24 2008-12-09 23:00:13 GMT mtk01461
**  Change the order when call MessageBox() and kalBreakPoint()
**  \main\maintrunk.MT5921\23 2008-12-09 10:59:21 GMT mtk01461
**  Add MessageBox for BUILD_QA_DBG option in Windows CE
**  \main\maintrunk.MT5921\22 2008-10-22 10:56:32 GMT mtk01461
**  Update for lint diagnosis support
**  \main\maintrunk.MT5921\21 2008-10-20 22:14:12 GMT mtk01104
**  Move Windows OS-specific debug method to gl_kal.h
**  \main\maintrunk.MT5921\20 2008-10-16 15:46:35 GMT mtk01461
**  Update driver to fix lint warning
**  \main\maintrunk.MT5921\19 2008-08-04 16:47:24 GMT mtk01461
**  Add define of BUILD_QA_DBG for QA help to debug
**  \main\maintrunk.MT5921\18 2008-08-01 13:24:40 GMT mtk01084
**  Prevent redundent driver assertion in driver logic when BUS is detached
**  \main\maintrunk.MT5921\17 2008-07-11 17:33:08 GMT mtk01084
**  add new debug module
**  \main\maintrunk.MT5921\16 2008-04-07 22:09:04 GMT mtk01084
**  add DBG_RCPI_MEASURE_IDX
**  \main\maintrunk.MT5921\15 2008-04-07 18:40:51 GMT mtk01385
**  1. modify code to support MSG_DEBUG_MSG method.
**  \main\maintrunk.MT5921\14 2008-04-04 16:20:13 GMT mtk01084
**  add LP IOT index for debug
**  \main\maintrunk.MT5921\13 2008-02-12 23:26:44 GMT mtk01461
**  Add debug level - Event
**  \main\maintrunk.MT5921\12 2008-02-04 17:05:34 GMT mtk01461
**  Refine ARB_IF_IN_RFTEST_STATE
**  \main\maintrunk.MT5921\11 2008-02-01 11:48:53 GMT mtk01385
**  1. Fix "Debug message log to a file " compiling error.
**  \main\maintrunk.MT5921\10 2008-02-01 09:10:03 GMT mtk01385
**  1. Fix WinCE 4.2 compiling error.
**  \main\maintrunk.MT5921\9 2007-11-17 15:19:49 GMT mtk01385
**  1. add RF test mode debug module.
** Revision 1.4  2007/07/17 12:54:24  MTK01088
** add DEBUGFUNC
**
** Revision 1.3  2007/07/05 07:25:31  MTK01461
** Add Linux initial code, modify doc, add 11BB, RF init code
**
** Revision 1.2  2007/06/27 02:18:49  MTK01461
** Update SCAN_FSM, Initial(Can Load Module), Proc(Can do Reg R/W), TX API
**
** Revision 1.1.1.1  2007/06/22 08:09:05  MTK01461
** no message
**
*/

#ifndef _DEBUG_H
#define _DEBUG_H

/*******************************************************************************
*                         C O M P I L E R   F L A G S
********************************************************************************
*/

/*******************************************************************************
*                    E X T E R N A L   R E F E R E N C E S
********************************************************************************
*/
#include "gl_typedef.h"

extern UINT_8   aucDebugModule[];
extern UINT_32  u4DebugModule;

/*******************************************************************************
*                              C O N S T A N T S
********************************************************************************
*/
/* Define debug category (class):
 * (1) ERROR (2) WARN (3) STATE (4) EVENT (5) TRACE (6) INFO (7) LOUD (8) TEMP
 */
#define DBG_CLASS_ERROR         BIT(0)
#define DBG_CLASS_WARN          BIT(1)
#define DBG_CLASS_STATE         BIT(2)
#define DBG_CLASS_EVENT         BIT(3)
#define DBG_CLASS_TRACE         BIT(4)
#define DBG_CLASS_INFO          BIT(5)
#define DBG_CLASS_LOUD          BIT(6)
#define DBG_CLASS_TEMP          BIT(7)
#define DBG_CLASS_MASK          BITS(0,7)


#if defined(LINUX)
#define DBG_PRINTF_64BIT_DEC    "lld"

#else  //Windows
#define DBG_PRINTF_64BIT_DEC    "I64d"

#endif
/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/
/* Define debug module index */
typedef enum _ENUM_DBG_MODULE_T {
    DBG_INIT_IDX = 0,       /* For driver initial */
    DBG_ARB_IDX,            /* For Arbiter State Machine */
    DBG_TEST_IDX,           /* For ARB_STATE_RF_TEST */
    DBG_SCAN_IDX,           /* For ARB_STATE_SCAN */
    DBG_JOIN_IDX,           /* For ARB_STATE_JOIN */
    DBG_ROAMING_IDX,        /* For Roaming Module */
    DBG_NIC_IDX,            /* For NIC Layer */
    DBG_PHY_IDX,            /* For BB or RF */
    DBG_HAL_IDX,            /* For HAL(HW) Layer */
    DBG_INTR_IDX,           /* For Interrupt */
    DBG_TX_IDX,
    DBG_RX_IDX,
    DBG_REQ_IDX,
    DBG_MGT_IDX,
    DBG_RSN_IDX,
    DBG_LP_IDX,
    DBG_RFTEST_IDX,         /* For RF test mode*/
    DBG_LP_IOT_IDX,         /* For LP-IOT mode*/
    DBG_RCPI_MEASURE_IDX,   /* For debugging RCPI measurement */
    DBG_DOMAIN_IDX,         /* For debugging DOMAIN */
//#if SUPPORT_WAPI
    DBG_WAPI_IDX,           /* For debugging WAPI */
//#endif
    DBG_SW1_IDX,            /* Developer specific */
    DBG_SW2_IDX,            /* Developer specific */
    DBG_SW3_IDX,            /* Developer specific */
    DBG_SW4_IDX,            /* Developer specific */
    DBG_SW5_IDX,            /* Developer specific */
    DBG_SW6_IDX,            /* Developer specific */


    DBG_MODULE_NUM
} ENUM_DBG_MODULE_T;

/* Define who owns developer specific index */
#define DBG_WH_IDX              DBG_SW1_IDX
#define DBG_KEVIN_IDX           DBG_SW2_IDX
#define DBG_MIKE_IDX            DBG_SW3_IDX
#define DBG_KENT_IDX            DBG_SW4_IDX
#define DBG_GEORGE_IDX          DBG_SW5_IDX
#define DBG_CMC_IDX             DBG_SW6_IDX

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
/* Debug print format string for the OS system time */
#define OS_SYSTIME_DBG_FORMAT               "0x%08x"

/* Debug print argument for the OS system time */
#define OS_SYSTIME_DBG_ARGUMENT(systime)    (systime)

/* Debug print format string for the MAC Address */
#define MACSTR          "%02x:%02x:%02x:%02x:%02x:%02x"

/* Debug print argument for the MAC Address */
#define MAC2STR(a)      ((PUINT_8)a)[0], ((PUINT_8)a)[1], ((PUINT_8)a)[2], \
                        ((PUINT_8)a)[3], ((PUINT_8)a)[4], ((PUINT_8)a)[5]

/* The pre-defined format to dump the value of a varaible with its name shown. */
#define DUMPVAR(variable, format)           (#variable " = " format "\n", variable)

/* The pre-defined format to dump the MAC type value with its name shown. */
#define DUMPMACADDR(addr)                   (#addr " = " MACSTR "\n", MAC2STR(addr))


/* Basiclly, we just do renaming of KAL functions although they should
 * be defined as "Nothing to do" if DBG=0. But in some compiler, the macro
 * syntax does not support  #define LOG_FUNC(x,...)
 *
 * A caller shall not invoke these three macros when DBG=0.
 */
#define LOG_FUNC_TIME           kalPrint
#define LOG_FUNC                kalPrint

#if DBG

    /* If __FUNCTION__ is already defined by compiler, we just use it. */
    #if defined(__FUNCTION__)
        #define DEBUGFUNC(_Func)
    #else
        #define DEBUGFUNC(_Func) static const char __FUNCTION__[] = _Func;
    #endif

    /* The following macros are used for future debug message. */
    /* TODO(Kevin): We should remove INITLOG/ERRORLOG/WARNLOG macro sooner or later */
    #define INITLOG(_Fmt) \
    { \
        if (aucDebugModule[DBG_INIT_IDX] & DBG_CLASS_TRACE) { \
            LOG_FUNC("%s: ", __FUNCTION__); \
            LOG_FUNC _Fmt; \
        } \
    }

    #define ERRORLOG(_Fmt) \
    { \
        if (aucDebugModule[DBG_ARB_IDX] & DBG_CLASS_ERROR) { \
            LOG_FUNC("**Error[%s:%d]-", __FILE__, __LINE__); \
            LOG_FUNC _Fmt; \
        } \
    }

    #define WARNLOG(_Fmt) \
    { \
        if (aucDebugModule[DBG_ARB_IDX] & DBG_CLASS_WARN) { \
            LOG_FUNC("**Warning[%s:%d]-", __FILE__, __LINE__); \
            LOG_FUNC _Fmt; \
        } \
    }

    /*lint -save -e960 Multiple use of '#/##' */
    #define DBGLOG(_Module, _Class, _Fmt) \
        { \
            if (aucDebugModule[DBG_##_Module##_IDX] & DBG_CLASS_##_Class) { \
                if (DBG_CLASS_##_Class == DBG_CLASS_ERROR) { \
                    LOG_FUNC_TIME("**Error[%s:%d]-", __FILE__, __LINE__); \
                    LOG_FUNC("%s: (" #_Module " " #_Class ") ", __FUNCTION__); \
                } \
                else if (DBG_CLASS_##_Class == DBG_CLASS_WARN) { \
                    LOG_FUNC_TIME("**Warning[%s:%d]-", __FILE__, __LINE__); \
                    LOG_FUNC("%s: (" #_Module " " #_Class ") ", __FUNCTION__); \
                } \
                else if (DBG_CLASS_##_Class == DBG_CLASS_EVENT) { \
                } \
                else { \
                    LOG_FUNC_TIME("%s: (" #_Module " " #_Class ") ", __FUNCTION__); \
                } \
                LOG_FUNC _Fmt; \
            } \
        }

    #define DBGLOG_MEM8(_Module, _Class, _StartAddr, _Length) \
        { \
            if (aucDebugModule[DBG_##_Module##_IDX] & DBG_CLASS_##_Class) { \
                LOG_FUNC("%s: (" #_Module " " #_Class ")\n", __FUNCTION__); \
                dumpMemory8((PUINT_8) (_StartAddr), (UINT_32) (_Length)); \
            } \
        }

    #define DBGLOG_MEM32(_Module, _Class, _StartAddr, _Length) \
        { \
            if (aucDebugModule[DBG_##_Module##_IDX] & DBG_CLASS_##_Class) { \
                LOG_FUNC("%s: (" #_Module " " #_Class ")\n", __FUNCTION__); \
                dumpMemory32((PUINT_32) (_StartAddr), (UINT_32) (_Length)); \
            } \
        }
    /*lint -restore */

    /*lint -save -e961 use of '#undef' is discouraged */
    #undef ASSERT
    /*lint -restore */

    #ifdef _lint
    #define ASSERT(_exp) \
        { \
            if (!(_exp)) {do {} while (1);} \
        }
    #else
    #define ASSERT(_exp) \
        { \
            if (!(_exp) && !fgIsBusAccessFailed) { \
                LOG_FUNC("Assertion failed: %s:%d %s\n", __FILE__, __LINE__, #_exp); \
                kalBreakPoint(); \
            } \
        }
    #endif /* _lint */

    #define ASSERT_REPORT(_exp, _fmt) \
        { \
            if (!(_exp) && !fgIsBusAccessFailed) { \
                LOG_FUNC("Assertion failed: %s:%d %s\n", __FILE__, __LINE__, #_exp); \
                LOG_FUNC _fmt; \
                kalBreakPoint(); \
            } \
        }

    #define DISP_STRING(_str)       _str

#else /* !DBG */

    #define DEBUGFUNC(_Func)
    #define INITLOG(_Fmt)
    #define ERRORLOG(_Fmt)
    #define WARNLOG(_Fmt)
    #define DBGLOG(_Module, _Class, _Fmt)
    #define DBGLOG_MEM8(_Module, _Class, _StartAddr, _Length)
    #define DBGLOG_MEM32(_Module, _Class, _StartAddr, _Length)

    #undef ASSERT

#if BUILD_QA_DBG
    #if defined(LINUX) /* For debugging in Linux w/o GDB */
        #define ASSERT(_exp) \
            { \
                if (!(_exp) && !fgIsBusAccessFailed) { \
                    LOG_FUNC("Assertion failed: %s:%d (%s)\n", __FILE__, __LINE__, #_exp); \
                    kalBreakPoint(); \
                } \
            }

        #define ASSERT_REPORT(_exp, _fmt) \
            { \
                if (!(_exp) && !fgIsBusAccessFailed) { \
                    LOG_FUNC("Assertion failed: %s:%d (%s)\n", __FILE__, __LINE__, #_exp); \
                    LOG_FUNC _fmt; \
                    kalBreakPoint(); \
                } \
            }
    #else
        #ifdef WINDOWS_CE
            #define UNICODE_TEXT(_msg)  TEXT(_msg)
            #define ASSERT(_exp) \
                { \
                    if (!(_exp) && !fgIsBusAccessFailed) { \
                        TCHAR rUbuf[256]; \
                        kalBreakPoint(); \
                        _stprintf(rUbuf, TEXT("Assertion failed: %s:%d %s\n"), \
                            UNICODE_TEXT(__FILE__), \
                            __LINE__, \
                            UNICODE_TEXT(#_exp)); \
                        MessageBox(NULL, rUbuf, TEXT("ASSERT!"), MB_OK); \
                    } \
                }

            #define ASSERT_REPORT(_exp, _fmt) \
                { \
                    if (!(_exp) && !fgIsBusAccessFailed) { \
                        TCHAR rUbuf[256]; \
                        kalBreakPoint(); \
                        _stprintf(rUbuf, TEXT("Assertion failed: %s:%d %s\n"), \
                            UNICODE_TEXT(__FILE__), \
                            __LINE__, \
                            UNICODE_TEXT(#_exp)); \
                        MessageBox(NULL, rUbuf, TEXT("ASSERT!"), MB_OK); \
                    } \
                }
        #else
            #define ASSERT(_exp) \
                { \
                    if (!(_exp) && !fgIsBusAccessFailed) { \
                        kalBreakPoint(); \
                    } \
                }

            #define ASSERT_REPORT(_exp, _fmt) \
                { \
                    if (!(_exp) && !fgIsBusAccessFailed) { \
                        kalBreakPoint(); \
                    } \
                }
        #endif /* WINDOWS_CE */
    #endif /* LINUX */
#else
    #define ASSERT(_exp)
    #define ASSERT_REPORT(_exp, _fmt)
#endif /* BUILD_QA_DBG */

    #define DISP_STRING(_str)       ""

#endif /* DBG */


/* The following macro is used for debugging packed structures. */
#define DATA_STRUC_INSPECTING_ASSERT(expr)      switch (0) {case 0: case (expr): default:;}


/*******************************************************************************
*                  F U N C T I O N   D E C L A R A T I O N S
********************************************************************************
*/
#if DBG
VOID
dumpMemory8 (
    IN PUINT_8 pucStartAddr,
    IN UINT_32 u4Length
    );

VOID
dumpMemory32 (
    IN PUINT_32 pu4StartAddr,
    IN UINT_32  u4Length
    );
#endif /* DBG */

/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/
#endif /* _DEBUG_H */

