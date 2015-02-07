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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/hal_pwr_mgt.c#2 $
*/

/*! \file   "hal_pwr_mgt.c"
    \brief  The HAL layer file, which placed function for power management
            related methods.

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
** $Log: hal_pwr_mgt.c $
 *
 * 06 19 2010 renbang.jiang
 * [ALPS00008357][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for support Rx/Tx indication led 
 * .
 *
 * 06 18 2010 renbang.jiang
 * [ALPS00008357][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for support Rx/Tx indication led 
 * .
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\92 2009-09-22 22:54:55 GMT mtk01089
**  Use PTA_NEW_BOARD_DESIGN to seperate 1.26 code
**  \main\maintrunk.MT5921\91 2009-09-12 13:49:34 GMT mtk01089
**  Because antenna is controlled by GPIO0 & GPIO2 now. There is no need to program IOPCR any more.
**  \main\maintrunk.MT5921\90 2009-08-18 22:56:36 GMT mtk01090
**  Add Linux SDIO (with mmc core) support.
**  Add Linux 2.6.21, 2.6.25, 2.6.26.
**  Fix compile warning in Linux.
**  \main\maintrunk.MT5921\89 2009-08-06 16:44:11 GMT mtk01090
**  Use GPIO0 and GPIO2 to control antenna switch and remove obsolete compile flag CFG_SUPPORT_SINGLE_ANTENNA
**  \main\maintrunk.MT5921\88 2009-07-13 14:47:45 GMT mtk01090
**  Correct watchdog timeout value calculation.
**  Ignore DTIM Period and wake up every N * TBTT if wake up interval is too large to let network application run smoothly.
**  Switch back to CAM mode for this AP connection if LP has problems for ship build.
**  \main\maintrunk.MT5921\87 2009-03-18 10:20:19 GMT mtk01084
**  control the HW service period setting on configuring HW beacon timeout function
**  \main\maintrunk.MT5921\86 2009-03-05 20:57:09 GMT mtk01084
**  modify for continuous polling interval issue
**  \main\maintrunk.MT5921\85 2009-02-24 22:52:56 GMT mtk01084
**  remove the LP for SW antenna control, due to BT SCO
**  \main\maintrunk.MT5921\84 2009-02-18 16:44:26 GMT mtk01084
**  Enhancement of the BT SCO voico quality when MT5921 enter LP
**  \main\maintrunk.MT5921\83 2009-02-16 17:56:21 GMT mtk01084
**  modify for controlling beacon lost detection function
**  \main\maintrunk.MT5921\82 2009-02-11 19:52:05 GMT mtk01084
**  Fix the LP watchdog, due to U-APSD service period
**  \main\maintrunk.MT5921\81 2009-02-05 21:42:39 GMT mtk01084
**  PS-related parameters modification for BT/WiFi coexistence optimization
**  \main\maintrunk.MT5921\80 2009-02-05 17:41:11 GMT mtk01084
**  fix lines regarding chip reset will clear OSC daisy chain related setting during ACPI D3
**  \main\maintrunk.MT5921\79 2009-01-05 10:18:17 GMT mtk01725
**  When pattern search SLT is enabled, always enable pattern search even in WLAN_ON state.
**  \main\maintrunk.MT5921\78 2008-12-08 21:31:07 GMT mtk01461
**  Avoid Lint Warning - Excessive shift value to constant
**  \main\maintrunk.MT5921\77 2008-12-08 20:58:40 GMT mtk01084
**  prevent lint warning
**  \main\maintrunk.MT5921\76 2008-12-01 18:37:50 GMT mtk01088
**  fixed the "possible use of null pointer" by lint check
**  \main\maintrunk.MT5921\75 2008-11-27 16:06:56 GMT mtk01084
**  prevent assertion false alarm
**  \main\maintrunk.MT5921\74 2008-11-24 21:04:07 GMT mtk01425
**  1. Add PTA_ENABLED flag
**  \main\maintrunk.MT5921\73 2008-09-30 19:07:32 GMT mtk01084
**  fix part in LP instruction programming
**  \main\maintrunk.MT5921\72 2008-09-24 10:58:22 GMT mtk01084
**  add single antenna related support function
**  \main\maintrunk.MT5921\71 2008-09-17 10:51:18 GMT mtk01084
**  modify LP instruction programming method
**  \main\maintrunk.MT5921\70 2008-09-16 19:26:53 GMT mtk01084
**  prevent compiler warning
**  \main\maintrunk.MT5921\69 2008-09-08 21:01:00 GMT mtk01084
**  support PTA/ single antenna related function on power on/ off
**  \main\maintrunk.MT5921\68 2008-09-08 09:30:31 GMT mtk01084
**  modify for single antenna support
**  \main\maintrunk.MT5921\67 2008-09-03 14:14:46 GMT mtk01084
**  add LP instruction related variables
**  \main\maintrunk.MT5921\66 2008-09-03 13:39:09 GMT mtk01084
**  add the control of the antenna selection pin
**  \main\maintrunk.MT5921\65 2008-08-11 21:31:41 GMT mtk01084
**  modify for coding rule conformance
**  \main\maintrunk.MT5921\64 2008-07-15 22:31:49 GMT mtk01084
**  modify chip power on procedure (do not power down the OSC_EN)
**  \main\maintrunk.MT5921\63 2008-07-14 11:36:10 GMT mtk01084
**  modify logic and
**  \main\maintrunk.MT5921\62 2008-07-14 11:21:38 GMT mtk01084
**  check the PS connection state and disable HW to respond trigger frame for buffered UC indication by beacon
**  \main\maintrunk.MT5921\61 2008-07-07 20:22:00 GMT mtk01084
**  workaround HEC 6173 for different chip version
**  \main\maintrunk.MT5921\60 2008-07-07 10:06:11 GMT mtk01084
**  revise pattern search related register setting
**  \main\maintrunk.MT5921\59 2008-06-26 21:08:49 GMT mtk01084
**  add WMM-PS test related customizations
**  \main\maintrunk.MT5921\58 2008-06-18 20:45:23 GMT mtk01084
**  revise beacon timeout handling procedure
**  \main\maintrunk.MT5921\57 2008-06-10 09:38:56 GMT mtk01084
**  qualify the LED mode in the connection setting for LED blink mode
**  \main\maintrunk.MT5921\56 2008-05-23 10:25:40 GMT mtk01084
**  modify IO_SET_TRAP_PIN_INPUT_DIR naming
**  \main\maintrunk.MT5921\55 2008-05-21 16:53:18 GMT mtk01084
**  wakeup host on beacon is received when SLT is performed
**  \main\maintrunk.MT5921\54 2008-05-13 22:02:26 GMT mtk01084
**  always do SW TBTT compansation on IBSS merge
**  \main\maintrunk.MT5921\53 2008-05-12 13:28:52 GMT mtk01084
**  modify the next TBTT by compansating 1 beacon interval when merging with IBSS
**  \main\maintrunk.MT5921\52 2008-04-11 18:08:59 GMT mtk01084
**  prevent compiler warning
**  \main\maintrunk.MT5921\51 2008-04-11 17:21:40 GMT mtk01084
**  modify the procedure to create IBSS for setting next TBTT
**  \main\maintrunk.MT5921\50 2008-04-10 20:09:32 GMT mtk01084
**  modify the use of macro to set beacon timeout
**  \main\maintrunk.MT5921\49 2008-04-07 23:23:01 GMT mtk01084
**  modify lines in setting MCR_IOPCR, which will set ant_p/n to input mode
**  \main\maintrunk.MT5921\48 2008-04-02 20:49:57 GMT mtk01084
**  enable beacon pass to driver when RCPI histogram is enabled
**  \main\maintrunk.MT5921\47 2008-04-02 20:44:19 GMT mtk01084
**  Support for RCPI variance histogram
**  \main\maintrunk.MT5921\46 2008-03-23 15:17:37 GMT mtk01084
**  modify the OSC stable time to workaround IC issue now
**  \main\maintrunk.MT5921\45 2008-03-18 19:44:55 GMT mtk01084
**  modify the macro naming
**  \main\maintrunk.MT5921\44 2008-03-06 22:26:17 GMT mtk01084
**  add SW assertion
**  \main\maintrunk.MT5921\43 2008-03-03 18:09:36 GMT mtk01084
**  modify comments and halpmEnableLowPowerFunctionsInBss() arguments
**  \main\maintrunk.MT5921\42 2008-02-21 23:28:16 GMT mtk01084
**  reset TBTT on creating IBSS
**  \main\maintrunk.MT5921\41 2008-02-18 17:24:56 GMT mtk01084
**  add function description
**  \main\maintrunk.MT5921\40 2008-02-14 09:58:59 GMT mtk01084
**  modify set pattern routine
**  \main\maintrunk.MT5921\39 2008-02-13 10:22:21 GMT mtk01084
**  refine code with using macro
**  \main\maintrunk.MT5921\38 2008-02-04 22:25:20 GMT mtk01084
**  modify LP instruction and halpmLeaveLowPower()
**  \main\maintrunk.MT5921\37 2008-02-01 10:42:25 GMT mtk01385
**  1. Fix WinCE 4.2 compiling error.
**  \main\maintrunk.MT5921\36 2008-01-11 19:21:16 GMT mtk01084
**  modify the procedure of turning off clock sources
**  \main\maintrunk.MT5921\35 2008-01-08 10:38:50 GMT mtk01084
**  remove the place to init TSF drift detection
**  \main\maintrunk.MT5921\34 2007-12-28 10:00:35 GMT mtk01084
**  fix register ATCR setting
**  \main\maintrunk.MT5921\33 2007-12-25 22:37:18 GMT mtk01084
**  update the LP instruction by the latest formula
**  \main\maintrunk.MT5921\32 2007-12-20 15:48:47 GMT mtk01084
**  fix compiler warning and use MACRO define instead of bit define
**  \main\maintrunk.MT5921\31 2007-12-16 19:34:53 GMT mtk01084
**  Enable 32K slow clock source before doing calibration
**  \main\maintrunk.MT5921\30 2007-12-11 14:51:50 GMT MTK01084
**  modify the method programming LP instructions
**  \main\maintrunk.MT5921\29 2007-12-08 22:34:46 GMT mtk01084
**  add comments
**  \main\maintrunk.MT5921\28 2007-12-03 17:43:04 GMT mtk01084
**  remove one assertion
**  \main\maintrunk.MT5921\27 2007-11-30 19:40:49 GMT mtk01084
**  modify clock on parameters
**  \main\maintrunk.MT5921\26 2007-11-29 12:13:45 GMT mtk01084
**  modify LP instruction about configuring pattern search funcion
**  \main\maintrunk.MT5921\25 2007-11-28 14:38:40 GMT mtk01084
**  update halpmEnableBeaconEarlyCheck() to meet new register definiton
**  \main\maintrunk.MT5921\24 2007-11-27 18:06:06 GMT mtk01084
**  control trap pin direction between LP/ ON state
**  \main\maintrunk.MT5921\23 2007-11-27 11:59:12 GMT mtk01084
**  fix compiler warning on Linux compilter
**  \main\maintrunk.MT5921\22 2007-11-26 19:44:27 GMT mtk01084
**  Modify lines in setting reserved mask for setting MPTCR
**  \main\maintrunk.MT5921\21 2007-11-26 19:36:04 GMT mtk01084
**  not to disable T2 timer function during when abort HW function (reserved for SW root timer)
**  \main\maintrunk.MT5921\20 2007-11-22 22:18:23 GMT mtk01084
**  modify lines in config pattern search function, and initial value
**  \main\maintrunk.MT5921\19 2007-11-21 11:25:17 GMT mtk01084
**  fix Linux compiler warning
**  \main\maintrunk.MT5921\18 2007-11-21 10:32:18 GMT mtk01084
**  modify LP instruction programming for pattern search function
**  \main\maintrunk.MT5921\17 2007-11-20 16:21:50 GMT mtk01084
**  add pattern search related function
**  \main\maintrunk.MT5921\16 2007-11-19 22:25:14 GMT mtk01084
**  set trap pin direction within LP instructions
**  \main\maintrunk.MT5921\15 2007-11-19 12:17:06 GMT mtk01084
**  modify halpmConfigPattern() input argument
**  \main\maintrunk.MT5921\14 2007-11-13 18:06:51 GMT mtk01084
**  ensure the clock on delay time will not under-run
**  \main\maintrunk.MT5921\13 2007-11-12 20:24:14 GMT mtk01084
**  modify power on/ off sequence
**  \main\maintrunk.MT5921\12 2007-11-08 13:58:55 GMT mtk01084
**  modify LP register setting
**  \main\maintrunk.MT5921\11 2007-10-26 19:20:39 GMT mtk01084
**  1. enable packet search function in IBSS-PS
**  2. add Power ON function
** Revision 1.1  2007/07/05 14:07:20  MTK01084
** Initial version
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
#define USE_INTERNAL_32K_RING_OSC   0
#define USE_DEBUG_LED_SIGNAL_FOR_LOW_POWER      0

#define OSC_STABLE_TIME_US          1900//2000//1000
#define RF_SX_STABLE_TIME_US        120
#define PLL_STABLE_TIME_US          30

static UINT_16 u2OscStableTime      = (UINT_16)OSC_STABLE_TIME_US;
static UINT_16 u2RfSxStableTime     = (UINT_16)RF_SX_STABLE_TIME_US;
static UINT_16 u2PllStableTime      = (UINT_16)PLL_STABLE_TIME_US;


/******************************************************************************
*                             D A T A   T Y P E S
*******************************************************************************
*/

/******************************************************************************
*                            P U B L I C   D A T A
*******************************************************************************
*/
/* DEALAY time in each of the clock procedures, with also consider the
   case of 32K slow clock time greater than the component stable time
*/
#define LP_CLOCK_ON_DELAY_P1_US(_32kCcrSlowCnt)      \
            (u2OscStableTime > (UINT_16)_32kCcrSlowCnt) ? \
            (u2OscStableTime - (UINT_16)_32kCcrSlowCnt) : 0

#define LP_CLOCK_ON_DELAY_P2_US(_32kCcrSlowCnt)      \
            (u2RfSxStableTime > (UINT_16)_32kCcrSlowCnt) ? \
            (u2RfSxStableTime - (UINT_16)_32kCcrSlowCnt) : 0

#define LP_CLOCK_ON_DELAY_P3_US(_32kCcrSlowCnt)      \
            (u2PllStableTime + (UINT_16)_32kCcrSlowCnt)

/* unit: 64 us, Set to 256 us (> preamble).
   NOTE: This value should be set to a non-zero value for HW to transmit beacon!!
*/
#define PRE_TBTT_INTERVAL           4

/******************************************************************************
*                           P R I V A T E   D A T A
*******************************************************************************
*/

/******************************************************************************
*                                 M A C R O S
*******************************************************************************
*/
#define MPTCR_INFRASTRUCTURE_STA_SETTING_CONNECTED      \
                   (MPTCR_BMC_TIMEOUT_EN |              \
                    MPTCR_MORE_TRIG_EN |                \
                    MPTCR_TX_PSPOLL_TIMEOUT_EN |        \
                    MPTCR_BCN_CONTENT_CHK_EN |          \
                    MPTCR_APSD_TIMEOUT_EN |             \
                    MPTCR_BCN_TIMEOUT_EN |              \
                    MPTCR_TBTT_PERIOD_TIMER_EN |        \
                    MPTCR_BCN_UC_EN |                   \
                    MPTCR_TX_NULL_EN |                  \
                    MPTCR_BCN_BMC_EN |                  \
                    MPTCR_BCN_PARSE_TIM_EN |            \
                    MPTCR_RX_BMC_MGT_EN |               \
                    MPTCR_PREDTIM_TRIG_EN)

#define MPTCR_AD_HOC_STA_SETTING_CONNECTED              \
                   (MPTCR_BCN_CONTENT_CHK_EN |          \
                    MPTCR_BCN_TIMEOUT_EN |              \
                    MPTCR_TBTT_PERIOD_TIMER_EN |        \
                    MPTCR_PRETBTT_TRIG_EN)

#define MPTCR_AD_HOC_STA_SETTING_CREATE                 \
                   (MPTCR_TBTT_PERIOD_TIMER_EN)

#define HAL_SETUP_LOW_POWER_FUNC_FOR_BSS(_prAdapter, _pfgIsIbssMaster) \
    { \
        UINT_32 u4RegCir; \
        HAL_MCR_RD(_prAdapter, MCR_CIR, &u4RegCir); \
        *_pfgIsIbssMaster = ((u4RegCir & CIR_IBSS_MASTER) ? TRUE : FALSE); \
    }

/* NOTE: ASSERTION of the _Base value should be done outside the macro
*/
#define CEILING(_Value, _Base)    \
        (((UINT_32)(_Value) + (UINT_32)((_Base) - 1)) / (UINT_32)(_Base))

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
* \brief This routine is used to program Low Power Instructions.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[in] uc32kSlowCount The 32K slow clock count in unit of micro-second
* \param[in] ucNumExtraSleepEntry The number of extra LP instruction used when switching to SLEEP
* \param[in] ucNumExtraWakeEntry The number of extra LP instruction used when switching to WLAN_ON
* \param[in] ucNumExtraOnEntry The number of extra LP instruction used when switching to ON
* \param[in] au4ExtraLowPowerInst_sleep Extra LP instruction used when switching to SLEEP
* \param[in] au4ExtraLowPowerInst_wake Extra LP instruction used when switching to WLAN_ON
* \param[in] au4ExtraLowPowerInst_full_on Extra LP instruction used when switching to ON
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
halpmProgLowPwrInst (
    IN P_ADAPTER_T  prAdapter,
    IN UINT_8       uc32kSlowCount,
    IN UINT_8       ucNumExtraSleepEntry,
    IN UINT_8       ucNumExtraWakeEntry,
    IN UINT_8       ucNumExtraOnEntry,
    IN UINT_32      au4ExtraLowPowerInst_sleep[],
    IN UINT_32      au4ExtraLowPowerInst_wake[],
    IN UINT_32      au4ExtraLowPowerInst_full_on[],
    IN BOOLEAN      fgForBtCoexist
    )
{
    UINT_32 u4LpInstSleepStartAddr = CFG_LOW_POWER_INST_START_ADDR;
    UINT_32 u4LpInstWakeStartAddr, u4LpInstOnStartAddr;
    UINT_32 i;
    UINT_32 u4NumOfSleepEntry = 0, u4NumOfWakeEntry = 0, u4NumOfOnEntry = 0;
#if USE_DEBUG_LED_SIGNAL_FOR_LOW_POWER
    P_CONNECTION_SETTINGS_T prConnSettings;
#endif
    /* Low Power instructions */
    UINT_32 au4LowPowerInst_sleep[10];
    UINT_32 au4LowPowerInst_wake[10];
    UINT_32 au4LowPowerInst_full_on[5];
//    UINT_32 u4Value;

    DEBUGFUNC("halpmProgLowPwrInst");

    ASSERT(prAdapter);
    if (ucNumExtraSleepEntry) {
        ASSERT(au4ExtraLowPowerInst_sleep);
    }
    if (ucNumExtraWakeEntry) {
        ASSERT(au4ExtraLowPowerInst_wake);
    }
    if (ucNumExtraOnEntry) {
        ASSERT(au4ExtraLowPowerInst_full_on);
    }
    ASSERT(ucNumExtraSleepEntry <= NUM_OF_MAX_LP_INSTRUCTIONS);
    ASSERT(ucNumExtraWakeEntry <= NUM_OF_MAX_LP_INSTRUCTIONS);
    ASSERT(ucNumExtraOnEntry <= NUM_OF_MAX_LP_INSTRUCTIONS);


    /* ********************** */
    /* Low Power instructions */
    /* ********************** */
    /* --- sleep --- */

#if USE_DEBUG_LED_SIGNAL_FOR_LOW_POWER
/*lint -save -e572 Excessive shift value (precision 1 shifted right by 16) */
    au4LowPowerInst_sleep[u4NumOfSleepEntry++] =
        LP_INST_MCR_WR_HALF_WORD(MCR_LCR, TRUE, (0 >> 16));    // LED off
/*lint -restore */
#else
    au4LowPowerInst_sleep[u4NumOfSleepEntry++] =
        LP_INST_MCR_WR_HALF_WORD(MCR_LCR, TRUE, (0 >> 16));    // LED off
#endif

#if PTA_ENABLED
    #if PTA_NEW_BOARD_DESIGN
    /* single antenna does not need to use ANT_P/ANT_N */
    au4LowPowerInst_sleep[u4NumOfSleepEntry++] =
        LP_INST_MCR_WR_HALF_WORD(MCR_IOPCR,
                                 FALSE,
                                 IO_SET_TRAP_PIN_INPUT_DIR |
                                 IO_SET_DBG_PORT_SEL);   // trap pin set to input mode
    #else
        au4LowPowerInst_sleep[u4NumOfSleepEntry++] =
            LP_INST_MCR_WR_HALF_WORD(MCR_IOPCR,
                                     FALSE,
                                     IO_SET_TRAP_PIN_INPUT_DIR |

                                     ((prAdapter->rPtaInfo.fgSingleAntenna) ?
                                      (IOPCR_IO_ANT_SEL_P_DIR | IOPCR_IO_ANT_SEL_N_DIR |
                                       IOPCR_IO_TR_SW_P_DIR | IOPCR_IO_TR_SW_N_DIR) : 0) |
                                     IO_SET_DBG_PORT_SEL);   // trap pin set to input mode

    #endif
#else
    au4LowPowerInst_sleep[u4NumOfSleepEntry++] =
        LP_INST_MCR_WR_HALF_WORD(MCR_IOPCR,
                                 FALSE,
                                 IO_SET_TRAP_PIN_INPUT_DIR |
                                 IO_SET_DBG_PORT_SEL);   // trap pin set to input mode

#endif
        /* Note: place the instruction if GPIO or other pin need to be pull high/ low or
                 set to input mode for preventing current leakage here...
        */
        /* 31            27       24    23      20     19       16     15                                         0 */
    au4LowPowerInst_sleep[u4NumOfSleepEntry++] =
        LP_INST_CLOCK_OFF(0, 0, 1, 0,   0, 0, 0, 0,     0, 0, 0, 1);

    /* --- wake --- */
    au4LowPowerInst_wake[u4NumOfWakeEntry++] =
        /* 31           27       24    23       20     19       16     15                                         0 */
        LP_INST_CLOCK_ON(0, 0, 1, 0,    0, 0, 1, 0,     0, 0, 0, 1,     1, 0, LP_CLOCK_ON_DELAY_P1_US(uc32kSlowCount));
    au4LowPowerInst_wake[u4NumOfWakeEntry++] =
        LP_INST_CLOCK_ON(0, 0, 1, 0,    1, 1, 1, 0,     0, 1, 0, 1,     0, 0, LP_CLOCK_ON_DELAY_P2_US(uc32kSlowCount));
    au4LowPowerInst_wake[u4NumOfWakeEntry++] =
        LP_INST_CLOCK_ON(0, 0, 1, 0,    1, 1, 1, 1,     0, 1, 0, 0,     0, 0, LP_CLOCK_ON_DELAY_P3_US(uc32kSlowCount));
        /* Note: Here restore the pin attribute if it is changed for preventing current leakage before enter LP...
        */
#if PTA_ENABLED
    #if PTA_NEW_BOARD_DESIGN
        /* single antenna does not use ant_p/ant_n as output */
    au4LowPowerInst_wake[u4NumOfWakeEntry++] =
        LP_INST_MCR_WR_HALF_WORD(MCR_IOPCR,
                                 FALSE,
                                 IO_SET_TRAP_PIN_DEFAULT_ATTR |
                                 IO_SET_DBG_PORT_SEL); // trap pin set to output mode
    #else
    au4LowPowerInst_wake[u4NumOfWakeEntry++] =
        LP_INST_MCR_WR_HALF_WORD(MCR_IOPCR,
                                 FALSE,
                                 IO_SET_TRAP_PIN_DEFAULT_ATTR |
                                 ((prAdapter->rPtaInfo.fgSingleAntenna) ?
                                  (IOPCR_IO_ANT_SEL_P_DIR | IOPCR_IO_ANT_SEL_N_DIR |
                                   IOPCR_IO_TR_SW_P_DIR | IOPCR_IO_TR_SW_N_DIR) : 0) |
                                 IO_SET_DBG_PORT_SEL); // trap pin set to output mode
    #endif
#else
    au4LowPowerInst_wake[u4NumOfWakeEntry++] =
        LP_INST_MCR_WR_HALF_WORD(MCR_IOPCR,
                                 FALSE,
                                 IO_SET_TRAP_PIN_DEFAULT_ATTR |
                                 IO_SET_DBG_PORT_SEL); // trap pin set to output mode
#endif




    /* --- on --- */
#if PTA_ENABLED
#if 0
    if (fgForBtCoexist & prAdapter->rPtaInfo.fgSingleAntenna) {
        /* set single antenna by BTCER1.bit[28] */
        HAL_MCR_RD(prAdapter, MCR_BTCER1, &u4Value);
        au4LowPowerInst_full_on[u4NumOfOnEntry++] =
            LP_INST_MCR_WR_HALF_WORD(MCR_BTCER1,
                                     TRUE,
                                     (u4Value | PTA_BTCER1_SINGLE_ANT)>>16);

        /* set antenna HW mode by RICR.bits[24:21] and RICR.bit[8], RICR.bit[6] */
        /* enable TX_PE/RX_PE  by RICR.bit[8] */
        HAL_MCR_RD(prAdapter, MCR_RICR, &u4Value);
        u4Value &= ~(RICR_ANT_SEL_N_SW_MODE |
                     RICR_ANT_SEL_P_SW_MODE |
                     RICR_SWANT_SEL_N_HIGH |
                     RICR_SWANT_SEL_P_HIGH |
                     RICR_RF_SW_MODE |
                     RICR_SW_TR_SW_N |
                     RICR_SW_TR_SW_P |
                     RICR_SW_RF_TX |
                     RICR_SW_RF_RX |
                     RICR_SW_TX_PE |
                     RICR_SW_RX_PE);
        au4LowPowerInst_full_on[u4NumOfOnEntry++] =
            LP_INST_MCR_WR_HALF_WORD(MCR_RICR,
                                     TRUE,
                                     u4Value>>16);
        au4LowPowerInst_full_on[u4NumOfOnEntry++] =
            LP_INST_MCR_WR_HALF_WORD(MCR_RICR,
                                     FALSE,
                                     u4Value);
    }
#endif
#endif

#if USE_DEBUG_LED_SIGNAL_FOR_LOW_POWER
    prConnSettings = &prAdapter->rConnSettings;
    au4LowPowerInst_full_on[u4NumOfOnEntry++] =
        LP_INST_MCR_WR_HALF_WORD(MCR_LCR, TRUE, (prConnSettings->ucLedBlinkMode != 0) ? (LCR_LED_OUTPUT >> 16) : 0x0000);    // LED on
#else
    au4LowPowerInst_full_on[u4NumOfOnEntry++] =
        LP_INST_MCR_WR_HALF_WORD(MCR_LCR, TRUE, prAdapter->prGlueInfo->u4LedSetting >> 16);    // LED on
#endif

    ASSERT(u4NumOfSleepEntry < (sizeof(au4LowPowerInst_sleep) / sizeof(UINT_32)));
    ASSERT(u4NumOfWakeEntry < (sizeof(au4LowPowerInst_wake) / sizeof(UINT_32)));
    ASSERT(u4NumOfOnEntry < (sizeof(au4LowPowerInst_full_on) / sizeof(UINT_32)));
    /* ***************************** */
    /* End of Low Power instructions */
    /* ***************************** */


    /* program the 1K WLAN FIFO start address */
    HAL_MCR_WR(prAdapter, MCR_HFCR, HFCR_SELECT_WLAN_FIFO | HFCR_FIFO_WRITE | u4LpInstSleepStartAddr);

    /* program for the "extra" SLEEP section */
    for (i = 0; i < ucNumExtraSleepEntry; i++) {
        ASSERT(au4ExtraLowPowerInst_sleep);
        HAL_MCR_WR(prAdapter, MCR_HFDR, au4ExtraLowPowerInst_sleep[i]);
        DBGLOG(LP, LOUD, ("Sleep %ld: 0x%08lx\n", i, au4ExtraLowPowerInst_sleep[i]));
    }
    /* program for the SLEEP section */
    for (i = 0; i < u4NumOfSleepEntry; i++) {
        HAL_MCR_WR(prAdapter, MCR_HFDR, au4LowPowerInst_sleep[i]);
        DBGLOG(LP, LOUD, ("Sleep %ld: 0x%08lx\n", i, au4LowPowerInst_sleep[i]));
    }

    /* Summation for the total entry number for entering SLEEP */
    u4NumOfSleepEntry += ucNumExtraSleepEntry;

    /* program the start/ end address of WLAN_on to Sleep, Initial to Sleep */
    HAL_MCR_WR(prAdapter, MCR_LPWSAR,
                LP_INST_WLAN_ON_to_SLEEP_ADDR(u4LpInstSleepStartAddr, u4NumOfSleepEntry) |
                LP_INST_INITIAL_to_SLEEP_ADDR(u4LpInstSleepStartAddr, u4NumOfSleepEntry)
                );

    DBGLOG(LP, INFO, ("LP inst (Sleep): %ld -> %ld (extra: %d)\n",
                        u4LpInstSleepStartAddr,
                        u4LpInstSleepStartAddr + u4NumOfSleepEntry - 1,
                        ucNumExtraSleepEntry));

    /* advance the start address */
    u4LpInstWakeStartAddr = u4LpInstSleepStartAddr + u4NumOfSleepEntry;

    /* program for the WAKE section */
    for (i = 0; i < u4NumOfWakeEntry; i++) {
        HAL_MCR_WR(prAdapter, MCR_HFDR, au4LowPowerInst_wake[i]);
        DBGLOG(LP, LOUD, ("Wake %ld: 0x%08lx\n", i, au4LowPowerInst_wake[i]));
    }
    /* program for the "extra" WAKE section */
    for (i = 0; i < ucNumExtraWakeEntry; i++) {
        ASSERT(au4ExtraLowPowerInst_wake);
        HAL_MCR_WR(prAdapter, MCR_HFDR, au4ExtraLowPowerInst_wake[i]);
        DBGLOG(LP, LOUD, ("Wake %ld: 0x%08lx\n", i, au4ExtraLowPowerInst_wake[i]));
    }

    /* Summation for the total entry number for entering AWAKE */
    u4NumOfWakeEntry += ucNumExtraWakeEntry;

    DBGLOG(LP, INFO, ("LP inst (wake): %ld -> %ld (extra: %d)\n",
                        u4LpInstWakeStartAddr,
                        u4LpInstWakeStartAddr + u4NumOfWakeEntry - 1,
                        ucNumExtraWakeEntry));

    /* advance the start address */
    u4LpInstOnStartAddr = u4LpInstWakeStartAddr + u4NumOfWakeEntry;

    /* program for the ON section */
    for (i = 0; i < u4NumOfOnEntry; i++) {
        HAL_MCR_WR(prAdapter, MCR_HFDR, au4LowPowerInst_full_on[i]);
        DBGLOG(LP, LOUD, ("On %ld: 0x%08lx\n", i, au4LowPowerInst_full_on[i]));
    }
    /* program for the "extra" ON section */
    for (i = 0; i < ucNumExtraOnEntry; i++) {
        ASSERT(au4ExtraLowPowerInst_full_on);
        HAL_MCR_WR(prAdapter, MCR_HFDR, au4ExtraLowPowerInst_full_on[i]);
        DBGLOG(LP, LOUD, ("On %ld: 0x%08lx\n", i, au4ExtraLowPowerInst_full_on[i]));
    }

    /* Summation for the total entry number for entering ON */
    u4NumOfOnEntry += ucNumExtraOnEntry;

    DBGLOG(LP, INFO, ("LP inst (on): %ld -> %ld (extra: %d)\n",
                        u4LpInstOnStartAddr,
                        u4LpInstOnStartAddr + u4NumOfOnEntry - 1,
                        ucNumExtraOnEntry));

    /* program the start/ end address of Sleep to WLAN_on, WLAN_on to ON */
    HAL_MCR_WR(prAdapter, MCR_LPOSAR,
                LP_INST_SLEEP_to_WLAN_ON_ADDR(u4LpInstWakeStartAddr, u4NumOfWakeEntry) |
                LP_INST_WLAN_ON_to_ON_ADDR(u4LpInstOnStartAddr, u4NumOfOnEntry)
                );

}   /* halpmProgLowPwrInst */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to program Low Power Instructions.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[in] uc32kSlowCount The 32K slow clock count in unit of micro-second
* \param[in] uc32kSlowCount_10 The under 1 decimal place of 32K slow clock count in unit of micro-second
* \param[in] uc32kSlowCount_100 The under 2 decimal place of 32K slow clock count in unit of micro-second
* \param[in] uc32kSlowCount_1000 The under 3 decimal place of 32K slow clock count in unit of micro-second
* \param[out] pu2GuardTimePhase2 Pointer to the wakeup guard time used for Low Power Phase 2
* \param[out] pu2GuardTimePhase3 Pointer to the wakeup guard time used for Low Power Phase 3
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
halpmCalculateGuardTime (
    IN P_ADAPTER_T prAdapter,
    IN UINT_8 uc32kSlowCount,
    IN UINT_8 uc32kSlowCount_10,
    IN UINT_8 uc32kSlowCount_100,
    IN UINT_8 uc32kSlowCount_1000,
    OUT PUINT_16 pu2GuardTimePhase2,
    OUT PUINT_16 pu2GuardTimePhase3
    )
{
    UINT_32 u4X1, u4Y1, u4Z1;
    UINT_32 u4G1, u4L1;
    UINT_32 u4Value;

    ASSERT(prAdapter);
    ASSERT(pu2GuardTimePhase2);
    ASSERT(pu2GuardTimePhase3);
    ASSERT(uc32kSlowCount);

    /* The 32K should have a non-zero value for setting guard time */
    if (uc32kSlowCount == 0) {
        return;
    }

    /* NOTE: Here we do not include the non-clock relavent LP instruction write into the
             calculation of guard, which costs 50ns * 2 (with pipe-line) for each instrucion.
    */

    u4X1 = CEILING(LP_CLOCK_ON_DELAY_P1_US(uc32kSlowCount), uc32kSlowCount);
    u4Y1 = CEILING(LP_CLOCK_ON_DELAY_P2_US(uc32kSlowCount), uc32kSlowCount);
    u4Z1 = CEILING(LP_CLOCK_ON_DELAY_P3_US(uc32kSlowCount), uc32kSlowCount);

    u4G1 = (2 + 1 + 3 + u4X1 + 1 + u4Y1 + 1 + u4Z1);
    u4L1 = (7 + 1 + u4Y1 + 1 + u4Z1);

    // phase 2 guard time
    u4Value = (u4G1 +
               CEILING((u4G1 / 10)   * (UINT_32)uc32kSlowCount_10,   uc32kSlowCount) +
               CEILING((u4G1 / 100)  * (UINT_32)uc32kSlowCount_100,  uc32kSlowCount) +
               CEILING((u4G1 / 1000) * (UINT_32)uc32kSlowCount_1000, uc32kSlowCount)) *
               (UINT_32)uc32kSlowCount;
    *pu2GuardTimePhase2 = (UINT_16)u4Value;

    // phase 3 guard time
    u4Value = (u4L1 +
               CEILING((u4L1 / 10)   * (UINT_32)uc32kSlowCount_10,   uc32kSlowCount) +
               CEILING((u4L1 / 100)  * (UINT_32)uc32kSlowCount_100,  uc32kSlowCount) +
               CEILING((u4L1 / 1000) * (UINT_32)uc32kSlowCount_1000, uc32kSlowCount)) *
               (UINT_32)uc32kSlowCount;
    *pu2GuardTimePhase3 = (UINT_16)u4Value;

}   /* halpmCalculateGuardTime */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to do register initialization.
*
* \param[in] prAdapter Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
halpmRegInit (
    IN P_ADAPTER_T prAdapter
    )
{
    UINT_32 u4Tstr;

    ASSERT(prAdapter);

    /* Use CCA to decide whether to extend the timeout */
    HAL_MCR_WR(prAdapter, MCR_SSCR, SSCR_EXT_TIME_CTRL);

    halpmSetBeaconTimeout(prAdapter,
                          BEACON_MIN_TIMEOUT_VALUE,
                          BEACON_MAX_TIMEOUT_VALUE,
                          BEACON_MIN_TIMEOUT_VALID,
                          BEACON_MAX_TIMEOUT_VALID,
                          BEACON_TIMEOUT_COUNT_INFRA);
    halpmSetNullTimeout(prAdapter,
                        NULL_MIN_TIMEOUT_VALUE,
                        NULL_MAX_TIMEOUT_VALUE,
                        NULL_MIN_TIMEOUT_VALID,
                        NULL_MAX_TIMEOUT_VALID,
                        NULL_TIMEOUT_COUNT);
    halpmSetTimeout(prAdapter,
                    MIN_TIMEOUT_VALUE,
                    MAX_TIMEOUT_VALUE,
                    MIN_TIMEOUT_VALID,
                    MAX_TIMEOUT_VALID,
                    TIMEOUT_COUNT);

    /*  TSTR (0x1a8) */
    // NOTICE: pre-tbtt interval is necessary in current ASIC design for transmitting beacon!
    HAL_MCR_RD(prAdapter, MCR_TSTR, &u4Tstr);
    u4Tstr &= ~TSTR_PRETBTT_INTERVAL_MASK;
    u4Tstr |= ((PRE_TBTT_INTERVAL << 24) & TSTR_PRETBTT_INTERVAL_MASK);
    HAL_MCR_WR(prAdapter, MCR_TSTR, u4Tstr);


#if USE_DEBUG_LED_SIGNAL_FOR_LOW_POWER
    {
    /*  LCR (0x94) */
    P_CONNECTION_SETTINGS_T prConnSettings = &prAdapter->rConnSettings;
    if (prConnSettings->ucLedBlinkMode) {
        HAL_MCR_WR(prAdapter, MCR_LCR, LCR_LED_OUTPUT);   // LED on, mode 0
    }
    }
#endif

}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to do setup the 20MHz oscillator stable time.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[in] u2OscStableTimeUs The 20MHz oscillator stable time.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
halpmSetOscStableTime (
    IN P_ADAPTER_T  prAdapter,
    IN UINT_16      u2OscStableTimeUs
    )
{
    ASSERT(prAdapter);

    /* Use the default value unless the setting is not 0 carried from EEPROM */
    if (u2OscStableTimeUs) {

        /* Due to HEC 5300, it is limited that OSC stable time cannot greater
           than 1900 for one CLK_ON LP instruction */
        ASSERT(u2OscStableTimeUs <= 1900);

        u2OscStableTime = u2OscStableTimeUs;
    }
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to setup HW service period guard function.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[in] u4ValidateSP The valid service period to be guard.
* \param[in] u4InvalidateSP The invalid service period not to be guard.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
halpmSetupServicePeriodMechanism (
    IN P_ADAPTER_T  prAdapter,
    IN UINT_32      u4ValidateSP,
    IN UINT_32      u4InvalidateSP
    )
{
    UINT_32 u4Spcr;

    ASSERT(prAdapter);

    /* Force to disable/ enable service period */
    HAL_MCR_RD(prAdapter, MCR_SPCR, &u4Spcr);

    // enable SP
    if (u4ValidateSP & SP_BEACON) {
        u4Spcr &= ~SPCR_BEACON_SP_INVALID_MASK;
    }
    if (u4ValidateSP & SP_BMC) {
        u4Spcr &= ~SPCR_BMC_SP_INVALID_MASK;
    }
    if (u4ValidateSP & SP_QOS_CFPOLL) {
        u4Spcr &= ~SPCR_QOS_CFPOLL_SP_INVALID_MASK;
    }
    if (u4ValidateSP & SP_PS_POLL) {
        u4Spcr &= ~SPCR_PSPOLL_SP_INVALID_MASK;
    }
    if (u4ValidateSP & SP_APSD) {
        u4Spcr &= ~SPCR_TRIGGER_SP_INVALID_MASK;
    }
    // disable SP
    if (u4InvalidateSP & SP_BEACON) {
        u4Spcr |= SPCR_BEACON_SP_INVALID_MASK;
    }
    if (u4InvalidateSP & SP_BMC) {
        u4Spcr |= SPCR_BMC_SP_INVALID_MASK;
    }
    if (u4InvalidateSP & SP_QOS_CFPOLL) {
        u4Spcr |= SPCR_QOS_CFPOLL_SP_INVALID_MASK;
    }
    if (u4InvalidateSP & SP_PS_POLL) {
        u4Spcr |= SPCR_PSPOLL_SP_INVALID_MASK;
    }
    if (u4InvalidateSP & SP_APSD) {
        u4Spcr |= SPCR_TRIGGER_SP_INVALID_MASK;
    }
    HAL_MCR_WR(prAdapter, MCR_SPCR, u4Spcr);

}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to enable the function of checking beacon earlier time.
*
* \param[in] prAdapter Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
halpmEnableBeaconEarlyCheck (
    IN P_ADAPTER_T prAdapter
    )
{
    UINT_32 u4RegValue;

    ASSERT(prAdapter);

    HAL_MCR_RD(prAdapter, MCR_BEIR, &u4RegValue);

    u4RegValue &= BEIR_BCN_LOST_THRESHOLD;

    /* Set a rising edge of the enable bit for HW to reset the value also */
    HAL_MCR_WR(prAdapter, MCR_BEIR, u4RegValue);
    HAL_MCR_WR(prAdapter, MCR_BEIR, u4RegValue | BEIR_BEI_CAL_EN);

}   /* halpmEnableBeaconEarlyCheck */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to get the beacon earlier time.
*
* \param[in] prAdapter Pointer to the Adapter structure.
*
* \retval UINT_16 Value of the beacon earlier time
*/
/*----------------------------------------------------------------------------*/
UINT_16
halpmGetBeaconEarlyValue (
    IN P_ADAPTER_T prAdapter
    )
{
    UINT_32 u4EarlyTimeTu;

    ASSERT(prAdapter);

    /* Set a rising edge of the enable bit for HW to reset the value also */
    HAL_MCR_RD(prAdapter, MCR_BEIR, &u4EarlyTimeTu);
    u4EarlyTimeTu &= BEIR_BCN_EARLIER_INTERVAL_MASK;
    u4EarlyTimeTu *= 2;

    return (UINT_16)u4EarlyTimeTu;
}   /* halpmGetBeaconEarlyValue */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to setup the timeout checking mechanism.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[in] ucMinTimeoutValue The minimum timeout value.
* \param[in] u2MaxTimeoutValue The maximum timeout value.
* \param[in] fgMinTimeoutValid Validate the minimum timeout value.
* \param[in] fgMaxTimeoutValid Validate the maximum timeout value.
* \param[in] ucTimeoutCount The number of timeout count contimuous to trigger interrupt.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
halpmSetTimeout (
    IN P_ADAPTER_T  prAdapter,
    IN UINT_8       ucMinTimeoutValue,
    IN UINT_16      u2MaxTimeoutValue,
    IN BOOLEAN      fgMinTimeoutValid,
    IN BOOLEAN      fgMaxTimeoutValid,
    IN UINT_8       ucTimeoutCount
    )
{
    UINT_32 u4RegTr, u4RegAtcr;

    ASSERT(prAdapter);

    // Max timeout is in unit of 4 TU
    u2MaxTimeoutValue = (UINT_16)CEILING(u2MaxTimeoutValue, 4);// unconditional rounding

    if (u2MaxTimeoutValue > BITS(0, 7)) {
        u2MaxTimeoutValue = BITS(0, 7);
        ASSERT(0);
    }
    if (ucMinTimeoutValue > BITS(0, 5)) {
        ucMinTimeoutValue = BITS(0, 5);
        ASSERT(0);
    }


    HAL_MCR_RD(prAdapter, MCR_TR, &u4RegTr);
    u4RegTr &= ~TR_MIN_MAX_TIME_LIMIT_MASK;
    u4RegTr |= (((ucMinTimeoutValue << 0) & TR_MIN_TIME_LIMIT_MASK) |
                ((u2MaxTimeoutValue << 8) & TR_MAX_TIME_LIMIT_MASK) |
                (fgMinTimeoutValid ? TR_MIN_TIME_LIMIT_VALID : 0) |
                (fgMaxTimeoutValid ? TR_MAX_TIME_LIMIT_VALID : 0));
    HAL_MCR_WR(prAdapter, MCR_TR, u4RegTr);

    HAL_MCR_RD(prAdapter, MCR_ATCR, &u4RegAtcr);
    u4RegAtcr &= ~ATCR_TIMEOUT_COUNT_LIMIT;
    u4RegAtcr |= ((ucTimeoutCount << 4) & ATCR_TIMEOUT_COUNT_LIMIT);
    HAL_MCR_WR(prAdapter, MCR_ATCR, u4RegAtcr);
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to setup the beacon timeout checking mechanism.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[in] ucMinTimeoutValue The minimum timeout value.
* \param[in] u2MaxTimeoutValue The maximum timeout value.
* \param[in] fgMinTimeoutValid Validate the minimum timeout value.
* \param[in] fgMaxTimeoutValid Validate the maximum timeout value.
* \param[in] ucTimeoutCount The number of timeout count contimuous to trigger interrupt.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
halpmSetBeaconTimeout (
    IN P_ADAPTER_T  prAdapter,
    UINT_8          ucMinTimeoutValue,
    UINT_16         u2MaxTimeoutValue,
    BOOLEAN         fgMinTimeoutValid,
    BOOLEAN         fgMaxTimeoutValid,
    UINT_8          ucTimeoutCount
    )
{
    UINT_32 u4RegTr, u4RegAtcr;

    ASSERT(prAdapter);

    // Max timeout is in unit of 4 TU
    u2MaxTimeoutValue = (UINT_16)CEILING(u2MaxTimeoutValue, 4);// unconditional rounding

    if (u2MaxTimeoutValue > BITS(0, 7)) {
        u2MaxTimeoutValue = BITS(0, 7);
        ASSERT(0);
    }
    if (ucMinTimeoutValue > BITS(0, 5)) {
        ucMinTimeoutValue = BITS(0, 5);
        ASSERT(0);
    }

    HAL_MCR_RD(prAdapter, MCR_TR, &u4RegTr);
    u4RegTr &= ~TR_BCN_MIN_MAX_TIME_LIMIT_MASK;
    u4RegTr |= (((ucMinTimeoutValue << 16) & TR_BCN_MIN_TIME_LIMIT_MASK) |
                ((u2MaxTimeoutValue << 24) & TR_BCN_MAX_TIME_LIMIT_MASK) |
                (fgMinTimeoutValid ? TR_BCN_MIN_TIME_LIMIT_VALID : 0) |
                (fgMaxTimeoutValid ? TR_BCN_MAX_TIME_LIMIT_VALID : 0));
    HAL_MCR_WR(prAdapter, MCR_TR, u4RegTr);

    HAL_MCR_RD(prAdapter, MCR_ATCR, &u4RegAtcr);
    u4RegAtcr &= ~ATCR_BCN_TIMEOUT_COUNT_LIMIT;
    u4RegAtcr |= (ucTimeoutCount & ATCR_BCN_TIMEOUT_COUNT_LIMIT);
    HAL_MCR_WR(prAdapter, MCR_ATCR, u4RegAtcr);
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to setup the Null timeout checking mechanism.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[in] ucMinTimeoutValue The minimum timeout value.
* \param[in] u2MaxTimeoutValue The maximum timeout value.
* \param[in] fgMinTimeoutValid Validate the minimum timeout value.
* \param[in] fgMaxTimeoutValid Validate the maximum timeout value.
* \param[in] ucTimeoutCount The number of timeout count contimuous to trigger interrupt.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
halpmSetNullTimeout (
    IN P_ADAPTER_T  prAdapter,
    UINT_8          ucMinTimeoutValue,
    UINT_16         u2MaxTimeoutValue,
    BOOLEAN         fgMinTimeoutValid,
    BOOLEAN         fgMaxTimeoutValid,
    UINT_8          ucTimeoutCount
    )
{
    UINT_32 u4Value;

    ASSERT(prAdapter);

    // Max timeout is in unit of 4 TU
    u2MaxTimeoutValue = (UINT_16)CEILING(u2MaxTimeoutValue, 4);// unconditional rounding

    if (u2MaxTimeoutValue > BITS(0, 7)) {
        u2MaxTimeoutValue = BITS(0, 7);
        ASSERT(0);
    }
    if (ucMinTimeoutValue > BITS(0, 5)) {
        ucMinTimeoutValue = BITS(0, 5);
        ASSERT(0);
    }

    HAL_MCR_RD(prAdapter, MCR_SPCR, &u4Value);
    u4Value &= ~SPCR_NULL_MIN_MAX_TIME_LIMIT_MASK;

    HAL_MCR_WR(prAdapter,
               MCR_SPCR,
               u4Value |
               ucMinTimeoutValue << 16 |
               ucMinTimeoutValue << 22 |
               fgMinTimeoutValid << 23 |
               u2MaxTimeoutValue << 24);

}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to set the PS bit carried in the frame control field.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[in] fgPwrMgtBit The PS bit boolean value.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
halpmSwitchPwrMgtBit (
    IN P_ADAPTER_T prAdapter,
    IN BOOLEAN fgPwrMgtBit
    )
{
    UINT_32 u4Value;

    ASSERT(prAdapter);

    HAL_MCR_RD(prAdapter, MCR_TXCR, &u4Value);
    u4Value &= ~TXCR_PWRMGT_SET;
    u4Value |= fgPwrMgtBit ? TXCR_PWRMGT_SET : 0;
    HAL_MCR_WR(prAdapter, MCR_TXCR, u4Value);
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to set the HW into LP state.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[in] fgEnableGlobalInt Whether to enable GINT or not.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
halpmEnterLowPower (
    IN P_ADAPTER_T prAdapter,
    IN BOOLEAN     fgEnableGlobalInt
    )
{
    ASSERT(prAdapter);

    if (fgEnableGlobalInt) {

#if 0 // NOTE(Kevin 2007/10/18): There is only one place to enable GINT - end of IST processing.
        prAdapter->fgIsIntEnable = TRUE; // NOTE(Kevin): Must placed before MCR GINT write.

        HAL_MCR_WR(prAdapter, MCR_HLPCR, HLPCR_ENABLE_GINT | HLPCR_LP_OWN_SET);
#endif
        prAdapter->fgIsIntEnableWithLPOwnSet = TRUE;

    }
    else {
        HAL_MCR_WR(prAdapter, MCR_HLPCR, HLPCR_LP_OWN_SET);
    }
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to set the HW exit from LP state.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[in] u4LpOwnBackPollTimeUs The number of loop used to wait LP been own back.
*
* \retval TRUE Success doing LP own back
* \retval FALSE HW function fail while doing LP own back
*/
/*----------------------------------------------------------------------------*/
BOOLEAN
halpmLeaveLowPower (
    IN P_ADAPTER_T prAdapter,
    IN UINT_32 u4LpOwnBackPollTimeUs
    )
{
#define LP_OWN_BACK_LOOP_DELAY_US   8   //exponential of 2

    UINT_32 i;
    UINT_32 u4RegValue;
    BOOLEAN fgStatus = TRUE;
    UINT_32 u4LoopCnt = u4LpOwnBackPollTimeUs / LP_OWN_BACK_LOOP_DELAY_US;

    ASSERT(prAdapter);

    /* Software get LP ownership */
    HAL_MCR_WR(prAdapter, MCR_HLPCR, HLPCR_LP_OWN_CLR);

    /* Delay for LP engine to complete its operation. */
    for (i = 0; i < u4LoopCnt; i++) {
        HAL_MCR_RD(prAdapter, MCR_CIR, &u4RegValue);
        if ((u4RegValue & (CIR_LP_STATE | CIR_PLL_READY)) != CIR_PLL_READY) {
            kalUdelay(LP_OWN_BACK_LOOP_DELAY_US);
        }
        else {
            break;
        }
    }
    if (i == u4LoopCnt) {
        fgStatus = FALSE;

        ERRORLOG(("LP cannot be own back (%ld)", u4LoopCnt));
        /* check the time of LP instructions need to perform from Sleep to On */
        //ASSERT(0);
    }

    return fgStatus;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to calibrate 32K slow clock.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[out] uc32kSlowCount The 32K slow clock count in unit of micro-second
* \param[out] uc32kSlowCount_10 The under 1 decimal place of 32K slow clock count in unit of micro-second
* \param[out] uc32kSlowCount_100 The under 2 decimal place of 32K slow clock count in unit of micro-second
* \param[out] uc32kSlowCount_1000 The under 3 decimal place of 32K slow clock count in unit of micro-second
*
* \retval TRUE
* \retval FALSE
*/
/*----------------------------------------------------------------------------*/
BOOLEAN
halpmCalSlowClock (
    IN P_ADAPTER_T prAdapter,
    OUT PUINT_8 pucSlowClockCount,
    OUT PUINT_8 pucSlowClockCount_10,
    OUT PUINT_8 pucSlowClockCount_100,
    OUT PUINT_8 pucSlowClockCount_1000
    )
{
#define WAIT_32K_CAL_READY_LOOP_COUNT 10

    UINT_32 i;
    UINT_32 u4RegValue;
    BOOLEAN fgStatus = FALSE;

    ASSERT(prAdapter);
    ASSERT(pucSlowClockCount);
    ASSERT(pucSlowClockCount_10);
    ASSERT(pucSlowClockCount_100);
    ASSERT(pucSlowClockCount_1000);

#if USE_INTERNAL_32K_RING_OSC
    HAL_MCR_WR(prAdapter, MCR_32KCCR, X32KCCR_CLK_SEL_RING_OSC);
    HAL_MCR_WR(prAdapter, MCR_HLPCR, HLPCR_INTERNAL_32K_EN);
    HAL_MCR_WR(prAdapter, MCR_32KCCR, X32KCCR_CLK_SEL_RING_OSC | X32KCCR_CAL_START);
#else
    HAL_MCR_WR(prAdapter, MCR_HLPCR, HLPCR_EXTERNAL_32K_EN);
    HAL_MCR_WR(prAdapter, MCR_32KCCR, X32KCCR_CAL_START);
#endif

    for (i = 0; i < WAIT_32K_CAL_READY_LOOP_COUNT; i++) {
        HAL_MCR_RD(prAdapter, MCR_32KCCR, &u4RegValue);
        if (!(u4RegValue & X32KCCR_CAL_START)) {
            fgStatus = TRUE;
            break;
        }
        kalMdelay(50);
    }

    /* Calculate the slow clock interval in unit of nano-seconds */
    *pucSlowClockCount_1000     = (UINT_8)((u4RegValue & BITS(24, 27)) >> 24);
    *pucSlowClockCount_100      = (UINT_8)((u4RegValue & BITS(20, 23)) >> 20);
    *pucSlowClockCount_10       = (UINT_8)((u4RegValue & BITS(16, 19)) >> 16);
    *pucSlowClockCount          = (UINT_8)((u4RegValue & BITS(0, 5))   >> 0);

    if (*pucSlowClockCount == 0) {
        fgStatus = FALSE;
        DBGLOG(HAL, ERROR, ("Slow clock period = 0 (need to ensure 32K clock is correctly provided)\n"));
        ASSERT(*pucSlowClockCount);
    }

    return fgStatus;
}   /* halpmCalSlowClock */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to configure Low Power related setting under
*        INFRASTRURE STA.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[in] u2AID The AID value after associated
* \param[in] u2BcnIntv The beacon interval value after associated
* \param[in] ucDtimPeriod The DTIM period value after associated
* \param[in] bmfgApsdEnAc The value of UAPSD-enabled AC
* \param[in] ucMultiDtimWake The count of DTIM period to cause wake-up event
* \param[in] ucMultiTbttWake The count of TBTT to cause wake-up event
* \param[in] fgUseAgeQoSNull Whether to use QoS-NULL or NULL for aging prevention
* \param[in] ucAgeNullPeriod The period to trigger NULL packet for aging prevention
* \param[in] ucQoSNullTid The TID value set inside QoS-NULL
* \param[in] ucTrgThr The trigger threshold in unit of byte
* \param[in] u2HwTxLifeTime The lifetime for HW transmitted packets
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
halpmConfigLowPowerSettingInBss (
    IN P_ADAPTER_T prAdapter,
    IN UINT_16     u2AID,
    IN UINT_16     u2BcnIntv,
    IN UINT_8      ucDtimPeriod,
    IN UINT_8      bmfgApsdEnAc,
    IN UINT_8      ucMultiDtimWake,
    IN UINT_8      ucMultiTbttWake,
    IN BOOLEAN     fgUseAgeQoSNull,
    IN UINT_8      ucAgeNullPeriod,
    IN UINT_8      ucQoSNullTid,
    IN UINT_8      ucTrgThr,
    IN UINT_16     u2HwTxLifeTime
    )
{
#define CLEAR_PSPOLL_TIMEOUT_BY_RECEIVED_BEACON     0
#define CLEAR_APSD_TIMEOUT_BY_RECEIVED_BEACON       0
#define RESTART_PSPOLL_WITHIN_PSPOLL_TIMEOUT        0
#define RESTART_TRIGGER_FRAME_WITHIN_APSD_TIMEOUT   0

    UINT_32 u4Lpcr, u4Ttpcr, u4Atcr, u4Txcr;
    BOOLEAN fgBcnRspPspoll = TRUE;
    BOOLEAN fgTxNullReset = TRUE;
    UINT_32 u4RegDbgr, u4SleepTimeout;
    P_PM_INFO_T prPmInfo;

    DEBUGFUNC("halpmConfigLowPowerSettingInBss");

    ASSERT(prAdapter);
    ASSERT(ucMultiDtimWake);
    ASSERT(u2BcnIntv);
    prPmInfo = &prAdapter->rPmInfo;

    // Setup AID, HW TX lifetime
    HAL_MCR_RD(prAdapter, MCR_LPCR, &u4Lpcr);
    u4Lpcr &= ~(LPCR_AID_MASK | LPCR_TX_LIFE_TIME_MASK);
    HAL_MCR_WR(prAdapter,
                MCR_LPCR,
                u4Lpcr |
                (u2AID << 0) |
                (u2HwTxLifeTime << 12));

    // Setup beacon interval, wakeup period
#if 0
    HAL_MCR_RD(prAdapter, MCR_TTPCR, &u4Ttpcr);
    u4Ttpcr = (u4Ttpcr & TTPCR_TBTT_CAL_ENABLE) |
              TTPCR_TBTT_CAL_ENABLE |
              ((ucMultiDtimWake << 28) & TTPCR_DTIM_WAKE_PERIOD_MASK) |
              ((ucMultiTbttWake << 24) & TTPCR_TBTT_WAKE_PERIOD_MASK) |
              ((ucDtimPeriod << 16) & TTPCR_DTIM_PERIOD_MASK) |
              (u2BcnIntv & TTPCR_BEACON_PERIOD_MASK);
#else
    u4Ttpcr = TTPCR_TBTT_CAL_ENABLE |
              ((ucMultiDtimWake << 28) & TTPCR_DTIM_WAKE_PERIOD_MASK) |
              ((ucMultiTbttWake << 24) & TTPCR_TBTT_WAKE_PERIOD_MASK) |
              ((ucDtimPeriod << 16) & TTPCR_DTIM_PERIOD_MASK) |
              (u2BcnIntv & TTPCR_BEACON_PERIOD_MASK);
    HAL_MCR_WR(prAdapter, MCR_TTPCR, u4Ttpcr);
#endif

    /* Change TID for trigger frame */
    if (!(bmfgApsdEnAc & BIT(AC3))) {
        ucQoSNullTid = bmfgApsdEnAc & BITS(0, 3);
    }

    // Setup U-APSD configurations and aging NULL frame type (QoS-Null)
    HAL_MCR_RD(prAdapter, MCR_TXCR, &u4Txcr);
    u4Txcr &= ~(TXCR_NULL_TYPE_QOS | TXCR_QOS_NULL_TID | TXCR_PWRMGT_SET |
                TXCR_AC_TRIG_ENABLED_MASK | TXCR_AC_DLVR_ENABLED_MASK |
                TXCR_AC_TRIG_FUNCTION_ENABLE);
    u4Txcr |=
        (fgUseAgeQoSNull ? TXCR_NULL_TYPE_QOS : 0) |
        ((ucQoSNullTid << 20) & TXCR_QOS_NULL_TID);
    if (bmfgApsdEnAc) {
        u4Txcr |=
            ((GET_TRIG_EN_AC_INFO_FROM_APSD_BMP(bmfgApsdEnAc) << 12) & TXCR_AC_TRIG_ENABLED_MASK) |
            ((GET_DLVR_EN_AC_INFO_FROM_APSD_BMP(bmfgApsdEnAc) << 4)  & TXCR_AC_DLVR_ENABLED_MASK) |
            TXCR_AC_TRIG_FUNCTION_ENABLE;

        /* Use trigger packet for buffered UC indication in beacon */
        if (GET_DLVR_EN_AC_INFO_FROM_APSD_BMP(bmfgApsdEnAc) == BITS(0, 3)) {
            // All the AC are delivery-enabled, use trigger frame
            fgBcnRspPspoll = FALSE;
        }
    }
    HAL_MCR_WR(prAdapter, MCR_TXCR, u4Txcr);

    prPmInfo->ucWmmPsConnWithTrig = fgBcnRspPspoll ? FALSE : TRUE;

    // Setup aging NULL type, NULL period, DTIM period, beacon interval...
    HAL_MCR_RD(prAdapter, MCR_ATCR, &u4Atcr);
    u4Atcr &= (ATCR_BCN_TIMEOUT_COUNT_LIMIT | ATCR_TIMEOUT_COUNT_LIMIT);
    u4Atcr |=
#if CLEAR_PSPOLL_TIMEOUT_BY_RECEIVED_BEACON
             (ATCR_PSPOLL_END_SP_EN) |
#endif
#if CLEAR_APSD_TIMEOUT_BY_RECEIVED_BEACON
             (ATCR_TRIGGER_END_SP_EN) |
#endif
#if RESTART_PSPOLL_WITHIN_PSPOLL_TIMEOUT
             (ATCR_PSPOLL_NEW_SP_EN) |
#endif
#if RESTART_TRIGGER_FRAME_WITHIN_APSD_TIMEOUT
             (ATCR_TRIGGER_NEW_SP_EN) |
#endif
             ((GET_DLVR_EN_AC_INFO_FROM_APSD_BMP(bmfgApsdEnAc) & BIT(AC3)) ?
                    0 : ATCR_MNGT_PSPOLL_EN) |
             ((((ucAgeNullPeriod * 1000) /
                (ucMultiDtimWake *
                 ucDtimPeriod *
                 u2BcnIntv)) << 16) & ATCR_TX_NULL_INTERVAL) |
             (fgTxNullReset ? ATCR_TX_NULL_RESET_CTRL : 0) |
             (fgBcnRspPspoll ? 0 : ATCR_BCN_POLL_QOS_NULL) |
             ((ucTrgThr << 8) & ATCR_TRIGGER_THRESHOLD);
    HAL_MCR_WR(prAdapter, MCR_ATCR, u4Atcr);

    /* Modify the sleep timeout for LP watchdog */
    u4SleepTimeout = ucMultiDtimWake * ucDtimPeriod * u2BcnIntv;
    u4SleepTimeout >>= 10; // in unit of 1024 TU
    u4SleepTimeout += 2;//u4SleepTimeout += 1;
    DBGLOG(LP, INFO, ("ucMultiTbttWake(%d), ucMultiDtimWake(%d), ucDtimPeriod(%d), u2BcnIntv(%d), u4SleepTimeout(%ld*1024TU)\n",
        ucMultiTbttWake, ucMultiDtimWake, ucDtimPeriod, u2BcnIntv, u4SleepTimeout));

    ASSERT(u4SleepTimeout <= DBGR_SLEEP_TIMEOUT_COUNT);
    u4SleepTimeout &= DBGR_SLEEP_TIMEOUT_COUNT;

    HAL_MCR_RD(prAdapter, MCR_DBGR, &u4RegDbgr);
    u4RegDbgr &= ~DBGR_SLEEP_TIMEOUT_COUNT;
    u4RegDbgr |= DBGR_SLEEP_TIMEOUT_UNIT_1024_TU;
    HAL_MCR_WR(prAdapter, MCR_DBGR, u4RegDbgr | u4SleepTimeout);

}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to configure Low Power related setting under IBSS.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[in] u2BcnIntv The beacon interval value after associated
* \param[in] u2AtimWindow The ATIM window value after associated
* \param[in] ucMultiTbttWake The count of TBTT to cause wake-up event
* \param[in] u2HwTxLifeTime The count of DTIM period to cause wake-up event
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
halpmConfigLowPowerSettingInAdhoc (
    IN P_ADAPTER_T  prAdapter,
    IN UINT_16      u2BcnIntv,
    IN UINT_16      u2AtimWindow,
    IN UINT_8       ucMultiTbttWake,
    IN UINT_16      u2HwTxLifeTime,
    IN BOOLEAN      fgTbttCalCompansate
    )
{
    UINT_32 u4Ttpcr, u4Txcr, u4Tstr;
    UINT_16 u2NextTbtt;
    UINT_32 u4RegDbgr, u4SleepTimeout;

    ASSERT(prAdapter);

    ASSERT(ucMultiTbttWake);
    ASSERT(u2BcnIntv);

    // Setup beacon interval, wakeup period, with also update next TBTT by current TSF
    HAL_MCR_RD(prAdapter, MCR_TTPCR, &u4Ttpcr);
    HAL_MCR_WR(prAdapter, MCR_TTPCR, 0);
    u4Ttpcr = (u4Ttpcr & TTPCR_TBTT_CAL_ENABLE) |
              TTPCR_TBTT_CAL_ENABLE |
              ((/*prIbssPmInfo->ucMultipleDtimWake*/0 << 28) & TTPCR_DTIM_WAKE_PERIOD_MASK) |
              ((ucMultiTbttWake << 24) & TTPCR_TBTT_WAKE_PERIOD_MASK) |
              ((/*prIbssPmInfo->ucDtimPeriod*/0 << 16) & TTPCR_DTIM_PERIOD_MASK) |
              (u2BcnIntv & TTPCR_BEACON_PERIOD_MASK);
    HAL_MCR_WR(prAdapter, MCR_TTPCR, u4Ttpcr);

#if 0
    if (fgTbttCalCompansate) {
#else
    // Always do SW compansation in the calibration procedure
    {
#endif
        HAL_MCR_RD(prAdapter, MCR_TSTR, &u4Tstr);
        u2NextTbtt = (UINT_16)u4Tstr + u2BcnIntv;
        HAL_MCR_WR(prAdapter, MCR_TSTR, ((u4Tstr & ~TSTR_TBTTSTARTTIME_MASK) |
                                         (UINT_32)u2NextTbtt));
    }

    if (u2AtimWindow == 0) {
        halpmSetAtimWindowValue(prAdapter, 0);

        HAL_MCR_RD(prAdapter, MCR_TXCR, &u4Txcr);
        u4Txcr &= ~TXCR_IBSS_Q_STOP;
        HAL_MCR_WR(prAdapter, MCR_TXCR, u4Txcr);
    }
    else {
        halpmSetAtimWindowValue(prAdapter, u2AtimWindow);

        HAL_MCR_RD(prAdapter, MCR_TXCR, &u4Txcr);
        u4Txcr |= TXCR_IBSS_Q_STOP;
        HAL_MCR_WR(prAdapter, MCR_TXCR, u4Txcr);
    }

    /* Modify the sleep timeout for LP watchdog */
    u4SleepTimeout = ucMultiTbttWake * u2BcnIntv;
    u4SleepTimeout >>= 10; // in unit of 1024 TU
    u4SleepTimeout += 2;

    ASSERT(u4SleepTimeout <= DBGR_SLEEP_TIMEOUT_COUNT);
    u4SleepTimeout &= DBGR_SLEEP_TIMEOUT_COUNT;

    HAL_MCR_RD(prAdapter, MCR_DBGR, &u4RegDbgr);
    u4RegDbgr &= ~DBGR_SLEEP_TIMEOUT_COUNT;
    u4RegDbgr |= DBGR_SLEEP_TIMEOUT_UNIT_1024_TU;
    HAL_MCR_WR(prAdapter, MCR_DBGR, u4RegDbgr | u4SleepTimeout);

}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to enable Low Power related function under
*        INFRASTRURE STA.
*
* \param[in] prAdapter Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
halpmEnableLowPowerFunctionsInBss (
    IN P_ADAPTER_T  prAdapter,
    IN BOOLEAN      fgNeedTbttWakeup
    )
{
    UINT_32 u4Mptcr;
    P_PM_INFO_T prPmInfo;

    ASSERT(prAdapter);
    prPmInfo = &prAdapter->rPmInfo;

    HAL_MCR_RD(prAdapter, MCR_MPTCR, &u4Mptcr);
    if (fgNeedTbttWakeup) {
        u4Mptcr |= (MPTCR_INFRASTRUCTURE_STA_SETTING_CONNECTED |
                    MPTCR_PRETBTT_TRIG_EN);
    }
    else {
        u4Mptcr |= MPTCR_INFRASTRUCTURE_STA_SETTING_CONNECTED;
    }

    // For WMM-PS test workaround (for full-UAPSD connection)
    if (prPmInfo->ucWmmPsDisableUcPoll && prPmInfo->ucWmmPsConnWithTrig) {
        u4Mptcr &= ~MPTCR_BCN_UC_EN;
    }

#if CFG_DBG_BEACON_RCPI_MEASUREMENT
    /* disable beacon content check, and allow beacon pass to driver */
    u4Mptcr &= ~MPTCR_BCN_CONTENT_CHK_EN;
#endif

#if CFG_LP_PATTERN_SEARCH_SLT
    /* 1. disable beacon content check, and allow beacon pass to driver
       2. wakeup host on beacon is received
    */
    if (prAdapter->eSLTModeSel == SLT_MODE_LP) {
        u4Mptcr &= ~(MPTCR_BCN_CONTENT_CHK_EN | MPTCR_BCN_PARSE_TIM_EN);
    }
#endif

    HAL_MCR_WR(prAdapter, MCR_MPTCR, u4Mptcr);
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to enable Low Power related function under IBSS.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[in] fgCreateIbss To create or to join an IBSS.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
halpmEnableLowPowerFunctionsInAdhoc (
    IN P_ADAPTER_T  prAdapter,
    IN BOOLEAN      fgCreateIbss
    )
{
    UINT_32 u4Mptcr;

    ASSERT(prAdapter);

    HAL_MCR_RD(prAdapter, MCR_MPTCR, &u4Mptcr);
    if (fgCreateIbss) {
        u4Mptcr |= MPTCR_AD_HOC_STA_SETTING_CREATE;
    }
    else {
        u4Mptcr |= MPTCR_AD_HOC_STA_SETTING_CONNECTED;
    }
    HAL_MCR_WR(prAdapter, MCR_MPTCR, u4Mptcr);
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to disable Low Power related functions.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[in] fgCreateIbss To create or to join IBSS.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
halpmDisableLowPowerFunctions (
    IN P_ADAPTER_T prAdapter
    )
{
    UINT_32 u4RegValue;
    UINT_32 u4RegReservedMask = 0;

    ASSERT(prAdapter);

    /* disable AC trigger function, which might cause APSD-SP if trigger frame
       is transmitted successfully */
    HAL_MCR_RD(prAdapter, MCR_TXCR, &u4RegValue);
    HAL_MCR_WR(prAdapter, MCR_TXCR, u4RegValue & ~TXCR_AC_TRIG_FUNCTION_ENABLE);


    /* Disable all of the LP function (except few reserved bits) */
    HAL_MCR_RD(prAdapter, MCR_MPTCR, &u4RegValue);

#if !CFG_USE_SW_ROOT_TIMER
    u4RegReservedMask |= MPTCR_T2_TIMER_EN;   //T2 is reserved to SW root timer
#endif

    /* Note: SCAN may also be aborted if it is ongoing, due to it's not able to
             keep this function on/off with other bit changed in the register
    */
#if 0 //Reserved GPIO control?
    u4RegReservedMask |= (MPTCR_GPIO0_TRIGGER |
                          MPTCR_GPIO1_TRIGGER |
                          MPTCR_GPIO2_TRIGGER);
#endif

    HAL_MCR_WR(prAdapter, MCR_MPTCR, u4RegValue & u4RegReservedMask);
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to setup Low Power Wakeup Guard Time.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[in] u2GuardTimePhase2 Wakeup guard time used for Low Power Phase 2
* \param[in] u2GuardTimePhase3 Wakeup guard time used for Low Power Phase 3
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
halpmSetupWakeupGuardTime (
    IN P_ADAPTER_T prAdapter,
    IN UINT_16 u2GuardTimePhase2,
    IN UINT_16 u2GuardTimePhase3
    )
{
    UINT_32 u4Tstr, u4Lpcr;

#if CFG_FPGA_COMPENSATE_HALF_T_FOR_GUARD_TIME_HEC_4489
    // for the 1/2 T compansation (25.6 us for 1 T)
    u2GuardTimePhase2 += 13;
    u2GuardTimePhase3 += 13;
#endif

    ASSERT(prAdapter);

    /* calculate TSTR.guard_interval */
    HAL_MCR_RD(prAdapter, MCR_TSTR, &u4Tstr);
    u4Tstr &= ~TSTR_GUARD_INTERVAL_MASK;
    u4Tstr |= (CEILING(u2GuardTimePhase2, 64) << 16) & TSTR_GUARD_INTERVAL_MASK;
    HAL_MCR_WR(prAdapter, MCR_TSTR, u4Tstr);

    /* calculate LPCR.LPStableTime */
    HAL_MCR_RD(prAdapter, MCR_LPCR, &u4Lpcr);
    u4Lpcr &= ~LPCR_LP_STABLE_TIME_MASK;
    u4Lpcr |= (CEILING(u2GuardTimePhase3, 8) << 24) & LPCR_LP_STABLE_TIME_MASK;
    HAL_MCR_WR(prAdapter, MCR_LPCR, u4Lpcr);

}   /* nicpmGetLowPowerStableTime */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to configure the pattern used for pattern search.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[in] ucIndex Pattern index
* \param[in] fgCheckBcA1 If to check the broadcast packet
* \param[in] fgCheckMcA1 If to check the multicast packet
* \param[in] fgCheckUcA1 If to check the unicast packet
* \param[in] fgIpv4Ip If to check it is IPv4 packet
* \param[in] fgIpv6Icmp If to check it is IPv6 packet for ICMP
* \param[in] fgGarpIpEqual If to check it the IP is equal for GARP packet
* \param[in] fgArpCtrl If to check it is ARP packet
* \param[in] fgAndOp Use AND or OR operand for this and next pattern
* \param[in] fgNotOp Use NOT operand for this pattern
* \param[in] ucPatternMask Pattern mask
* \param[in] ucPatternOffset Pattern offset
* \param[in] pu4Pattern Pointer for the pattern value
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
halpmConfigPattern (
    IN P_ADAPTER_T  prAdapter,
    IN UINT_8       ucIndex,
    IN BOOLEAN      fgCheckBcA1,
    IN BOOLEAN      fgCheckMcA1,
    IN BOOLEAN      fgCheckUcA1,
    IN BOOLEAN      fgIpv4Ip,
    IN BOOLEAN      fgIpv6Icmp,
    IN BOOLEAN      fgGarpIpEqual,
    IN BOOLEAN      fgArpCtrl,
    IN BOOLEAN      fgAndOp,
    IN BOOLEAN      fgNotOp,
    IN UINT_8       ucPatternMask,
    IN UINT_8       ucPatternOffset,
    IN PUINT_32     pu4Pattern
    )
{
    UINT_32 u4Pir;
    UINT_32 u4TransShift;
    UINT_8  ucTransPatternMask;
    UINT_32 pu4TransPattern[2];
    UINT_32 u4Value;

    ASSERT(prAdapter);

    if (!pu4Pattern) {
        // NOT TO USE assert here!
        return;
    }

    /* NOTE:
       SW need to reorder the ucPatternMask and pu4Pattern due to HW optimization
       of the pattern search engine by ucPatternOffset
    */
    u4TransShift = (UINT_32)ucPatternOffset % 8;
    if (u4TransShift) {
        ucTransPatternMask =
            (ucPatternMask << u4TransShift) |
            (ucPatternMask >> (8 - u4TransShift));
        kalMemCopy(pu4TransPattern,
                   (PUINT_8)((UINT_32)pu4Pattern + u4TransShift),
                   8 - u4TransShift);
        kalMemCopy((PUINT_8)((UINT_32)pu4TransPattern + u4TransShift),
                   pu4Pattern,
                   u4TransShift);
    }
    else {
        ucTransPatternMask = ucPatternMask;
        kalMemCopy(pu4TransPattern, pu4Pattern, 8);
    }

    // index
    HAL_MCR_RD(prAdapter, MCR_PIR, &u4Pir);
    u4Pir &= ~PIR_PATTERN_INDEX;
    HAL_MCR_WR(prAdapter, MCR_PIR, u4Pir | PIR_PATTERN_WRITE_MODE | ucIndex);

    // opeations
    u4Value = 0;
    u4Value = fgCheckBcA1         << 24 |
              fgCheckMcA1         << 23 |
              fgCheckUcA1         << 22 |
              fgIpv4Ip            << 21 |
              fgIpv6Icmp          << 20 |
              fgGarpIpEqual       << 19 |
              fgArpCtrl           << 18 |
              fgAndOp             << 17 |
              fgNotOp             << 16 |
              ucTransPatternMask  <<  8 |
              ucPatternOffset     <<  0;
    HAL_MCR_WR(prAdapter, MCR_PMR, u4Value);

    // pattern
    HAL_MCR_WR(prAdapter, MCR_PPR, pu4TransPattern[0]);
    HAL_MCR_WR(prAdapter, MCR_PPR, pu4TransPattern[1]);
}

#if 1
/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to configure the function used for pattern search.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[in] fgBcA1En If to enable the broadcast packet check
* \param[in] fgMcA1En If to enable the multicast packet check
* \param[in] fgUcA1En If to enable the unicast packet check
* \param[in] fgBcA1MatchDrop Use black or white list for the matched broadcast packet
* \param[in] fgMcA1MatchDrop Use black or white list for the matched multicast packet
* \param[in] fgUcA1MatchDrop Use black or white list for the matched unicast packet
* \param[in] fgIpv6MatchCtrl To enable IPv6 packet check
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
halpmConfigPatternSearchFunction (
    IN P_ADAPTER_T  prAdapter,
    IN BOOLEAN      fgBcA1En,
    IN BOOLEAN      fgMcA1En,
    IN BOOLEAN      fgUcA1En,
    IN BOOLEAN      fgBcA1MatchDrop,
    IN BOOLEAN      fgMcA1MatchDrop,
    IN BOOLEAN      fgUcA1MatchDrop,
    IN BOOLEAN      fgIpv6MatchCtrl
    )
{
    UINT_32 u4InstSleep = 0;
    UINT_32 u4InstOn = 0;
    UINT_32 u4Value;
    P_PM_INFO_T prPmInfo;

    ASSERT(prAdapter);

    prPmInfo = &prAdapter->rPmInfo;


    /* NOTE:
        Currently, it is assume that pattern search is enabled during LP (WLAN_on),
        and is disabled in ON state. This includes patterns with different A1 (UC/ BC/ MC),
        with disregarding whether to drop or receive for the matched packets or not.
    */

    HAL_MCR_RD(prAdapter, MCR_PIR, &u4Value);
    u4Value &= ~(PIR_BC_PATTERN_SRCH_EN |
                 PIR_MC_PATTERN_SRCH_EN |
                 PIR_UC_PATTERN_SRCH_EN |
                 PIR_BC_MATCHING_OPERATION |
                 PIR_MC_MATCHING_OPERATION |
                 PIR_UC_MATCHING_OPERATION |
                 PIR_IPV6_FRAME_MATCH_CTRL);
    if (fgIpv6MatchCtrl) {
        u4Value |= PIR_IPV6_FRAME_MATCH_CTRL;
    }
    HAL_MCR_WR(prAdapter, MCR_PIR, u4Value);

    u4InstSleep = (fgBcA1En << 22) |
                  (fgMcA1En << 21) |
                  (fgUcA1En << 20) |
                  (fgBcA1MatchDrop << 18) |
                  (fgMcA1MatchDrop << 17) |
                  (fgUcA1MatchDrop << 16);

    if (prPmInfo->ucNumOfInstSleep < NUM_OF_MAX_LP_INSTRUCTIONS) {
        prPmInfo->au4LowPowerInst_sleep[prPmInfo->ucNumOfInstSleep++] =
            LP_INST_MCR_WR_HALF_WORD(MCR_PIR, TRUE, (UINT_16)(u4InstSleep >> 16));
    }
    else {
        ERRORLOG(("NUM_OF_MAX_LP_INSTRUCTIONS(%d), prPmInfo->ucNumOfInstSleep(%d)\n",
            NUM_OF_MAX_LP_INSTRUCTIONS,
            prPmInfo->ucNumOfInstSleep));
        ASSERT(FALSE);
    }

    if (prAdapter->ucRevID == MTK_CHIP_MP_REVERSION_ID) {
        if (prPmInfo->ucNumOfInstSleep < NUM_OF_MAX_LP_INSTRUCTIONS) {
            prPmInfo->au4LowPowerInst_sleep[prPmInfo->ucNumOfInstSleep++] = LP_INST_DELAY(25, FALSE, FALSE);
        }
        else {
            ERRORLOG(("MTK_CHIP_MP_REVERSION_ID NUM_OF_MAX_LP_INSTRUCTIONS(%d), prPmInfo->ucNumOfInstSleep(%d)\n",
                NUM_OF_MAX_LP_INSTRUCTIONS,
                prPmInfo->ucNumOfInstSleep));
            ASSERT(FALSE);
        }
    }

#if CFG_LP_PATTERN_SEARCH_SLT
    if (prAdapter->eSLTModeSel == SLT_MODE_PATTERN_SEARCH) {
        /* Originally pattern search function is only enabled in sleep mode instruction.
          * Currentlly we would enable pattern search function in WLAN_ON instruction.
          */
        prPmInfo->au4LowPowerInst_on[prPmInfo->ucNumOfInstOn++] =
            LP_INST_MCR_WR_HALF_WORD(MCR_PIR, TRUE, (UINT_16)(u4InstSleep >> 16));
    }
    else {
        prPmInfo->au4LowPowerInst_on[prPmInfo->ucNumOfInstOn++] =
            LP_INST_MCR_WR_HALF_WORD(MCR_PIR, TRUE, (UINT_16)(u4InstOn >> 16));
    }
#else
    prPmInfo->au4LowPowerInst_on[prPmInfo->ucNumOfInstOn++] =
        LP_INST_MCR_WR_HALF_WORD(MCR_PIR, TRUE, (UINT_16)(u4InstOn >> 16));
#endif

    // Low power instruction programming
    NIC_PM_PROGRAM_LP_INSRUCTION(prAdapter, prPmInfo->fgIsContinousPollingEnabled);

#if CFG_LP_PATTERN_SEARCH_SLT
    if (prAdapter->eSLTModeSel == SLT_MODE_PATTERN_SEARCH) {
        HAL_MCR_WR(prAdapter, MCR_PIR, u4Value | u4InstSleep);
    }
#endif

} /* halpmConfigPatternSearchFunction */
#else
/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to configure the function used for pattern search.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[in] fgBcA1En If to enable the broadcast packet check
* \param[in] fgMcA1En If to enable the multicast packet check
* \param[in] fgUcA1En If to enable the unicast packet check
* \param[in] fgBcA1MatchDrop Use black or white list for the matched broadcast packet
* \param[in] fgMcA1MatchDrop Use black or white list for the matched multicast packet
* \param[in] fgUcA1MatchDrop Use black or white list for the matched unicast packet
* \param[in] fgIpv6MatchCtrl To enable IPv6 packet check
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
halpmConfigPatternSearchFunction (
    IN P_ADAPTER_T  prAdapter,
    IN BOOLEAN      fgBcA1En,
    IN BOOLEAN      fgMcA1En,
    IN BOOLEAN      fgUcA1En,
    IN BOOLEAN      fgBcA1MatchDrop,
    IN BOOLEAN      fgMcA1MatchDrop,
    IN BOOLEAN      fgUcA1MatchDrop,
    IN BOOLEAN      fgIpv6MatchCtrl
    )
{
    UINT_32 u4InstSleep = 0;
    UINT_32 u4InstOn = 0;
    UINT_32 u4Value;
    P_PM_INFO_T prPmInfo;

    ASSERT(prAdapter);

    prPmInfo = &prAdapter->rPmInfo;


    /* NOTE:
        Currently, it is assume that pattern search is enabled during LP (WLAN_on),
        and is disabled in ON state. This includes patterns with different A1 (UC/ BC/ MC),
        with disregarding whether to drop or receive for the matched packets or not.
    */

    HAL_MCR_RD(prAdapter, MCR_PIR, &u4Value);
    u4Value &= ~(PIR_BC_PATTERN_SRCH_EN |
                 PIR_MC_PATTERN_SRCH_EN |
                 PIR_UC_PATTERN_SRCH_EN |
                 PIR_BC_MATCHING_OPERATION |
                 PIR_MC_MATCHING_OPERATION |
                 PIR_UC_MATCHING_OPERATION |
                 PIR_IPV6_FRAME_MATCH_CTRL);
    if (fgIpv6MatchCtrl) {
        u4Value |= PIR_IPV6_FRAME_MATCH_CTRL;
    }
    HAL_MCR_WR(prAdapter, MCR_PIR, u4Value);

    u4InstSleep = (fgBcA1En << 22) |
                  (fgMcA1En << 21) |
                  (fgUcA1En << 20) |
                  (fgBcA1MatchDrop << 18) |
                  (fgMcA1MatchDrop << 17) |
                  (fgUcA1MatchDrop << 16);
    prPmInfo->au4LowPowerInst_sleep[prPmInfo->ucNumOfInstSleep++] =
        LP_INST_MCR_WR_HALF_WORD(MCR_PIR, TRUE, (UINT_16)(u4InstSleep >> 16));

    if (prAdapter->ucRevID == MTK_CHIP_MP_REVERSION_ID) {
        prPmInfo->au4LowPowerInst_sleep[prPmInfo->ucNumOfInstSleep++] = LP_INST_DELAY(25, FALSE, FALSE);
    }

    prPmInfo->au4LowPowerInst_on[prPmInfo->ucNumOfInstOn++] =
        LP_INST_MCR_WR_HALF_WORD(MCR_PIR, TRUE, (UINT_16)(u4InstOn >> 16));

    // Low power instruction programming
    NIC_PM_PROGRAM_LP_INSRUCTION(prAdapter);

} /* halpmConfigPatternSearchFunction */
#endif
/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to check if is an IBSS master right now.
*
* \param[in] prAdapter Pointer to the Adapter structure.
*
* \retval TRUE
* \retval FALSE
*/
/*----------------------------------------------------------------------------*/
BOOLEAN
halpmIfAdhocStaMaster (
    IN P_ADAPTER_T prAdapter
    )
{
    UINT_32 u4Value;

    ASSERT(prAdapter);

    HAL_MCR_RD(prAdapter, MCR_CIR, &u4Value);

    return ((u4Value & CIR_IBSS_MASTER) ? TRUE : FALSE);
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to process the POWER ON procedure.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[in] uc32kSlowCount The 32K slow clock count in unit of micro-second
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
halpmPowerOn (
    IN P_ADAPTER_T prAdapter,
    IN UINT_8 uc32kSlowCount
    )
{
    UINT_32 u4RegValue = 0;

    ASSERT(prAdapter);

    /* NOTE:
       Now uc32kSlowCount is used for calculating the delay time for different phases,
       and this value might be 0 on initial,
       if 32KHz clock is not calibrated before nor the clock is off.
    */
    //ASSERT(uc32kSlowCount);   // remove the assertion in purpose!

    /* NOTE:
       We should gate PLL first and then disable PLL.
       MCR_CIR.PLL_ready reflects current PLL gating status (not the PLL enable status).
    */
    // Enable PLL gating and disable all clock source (except OSC_en)
    HAL_MCR_WR(prAdapter, MCR_HLPCR, HLPCR_OSC_OUT_PD |         // bit14
                                     HLPCR_BG_PD |              // bit13
                                     HLPCR_PLL_PD |             // bit12
                                     HLPCR_ADC_BUFFER_PD |      // bit11
                                     HLPCR_INTERNAL_32K_PD |    // bit10
                                     HLPCR_EXTERNAL_32K_PD |    // bit9
                                     HLPCR_RF_SX_PD |           // bit8
                                     HLPCR_PLL_CLOCK_GATED);

    // logic reset (HIFMAC: bit 29, BB: B25)
    HAL_MCR_WR(prAdapter, MCR_HLPCR,
                HLPCR_PLL_CLOCK_GATED |
                HLPCR_BB_LOGRST | HLPCR_HIFMAC_LOGRST | HLPCR_LP_OWN_CLR);
    HAL_MCR_WR(prAdapter, MCR_HLPCR,
                HLPCR_PLL_CLOCK_GATED | HLPCR_OSC_EN);
    kalUdelay((UINT_32)LP_CLOCK_ON_DELAY_P1_US(uc32kSlowCount));
#if USE_INTERNAL_32K_RING_OSC
    HAL_MCR_WR(prAdapter, MCR_HLPCR,
                HLPCR_PLL_CLOCK_GATED |
                HLPCR_BG_EN | HLPCR_INTERNAL_32K_EN | HLPCR_RF_SX_EN);// BG/ 32K/ RF
#else
    HAL_MCR_WR(prAdapter, MCR_HLPCR,
                HLPCR_PLL_CLOCK_GATED |
                HLPCR_BG_EN | HLPCR_EXTERNAL_32K_EN | HLPCR_RF_SX_EN);// BG/ 32K/ RF
#endif
    kalUdelay((UINT_32)LP_CLOCK_ON_DELAY_P2_US(uc32kSlowCount));
    HAL_MCR_WR(prAdapter, MCR_HLPCR,
                HLPCR_PLL_CLOCK_GATED |
                HLPCR_OSC_OUT_EN | HLPCR_PLL_EN | HLPCR_ADC_BUFFER_EN);
    kalUdelay((UINT_32)LP_CLOCK_ON_DELAY_P3_US(uc32kSlowCount));
    HAL_MCR_WR(prAdapter, MCR_HLPCR, 0);// disable CLOCK gating


    // restore trap pin to output mode
    HAL_MCR_RD(prAdapter, MCR_IOPCR, &u4RegValue);
    u4RegValue |= (IO_SET_TRAP_PIN_DEFAULT_ATTR | IO_SET_DBG_PORT_SEL);
#if PTA_ENABLED
    #if PTA_NEW_BOARD_DESIGN
    HAL_MCR_WR(prAdapter,
               MCR_IOPCR,
               u4RegValue);
    #else
    HAL_MCR_WR(prAdapter,
               MCR_IOPCR,
               u4RegValue
                |(prAdapter->rPtaInfo.fgSingleAntenna) ? (IOPCR_IO_ANT_SEL_P_DIR | IOPCR_IO_ANT_SEL_N_DIR |
                                                     IOPCR_IO_TR_SW_P_DIR | IOPCR_IO_TR_SW_N_DIR) : 0);
    #endif
#else
    HAL_MCR_WR(prAdapter,
               MCR_IOPCR,
               u4RegValue);

#endif
#if PTA_ENABLED
    if (prAdapter->rPtaInfo.fgSingleAntenna) {
        if (prAdapter->rPtaInfo.u4PTAWireMode == PTA_SW_1_WIRE_MODE) {
            /* IOUDR */
            HAL_MCR_RD(prAdapter, MCR_IOUDR, &u4RegValue);
            u4RegValue &= ~(IOUDR_BT_PRI_PD | IOUDR_BT_PRI_PU);
            HAL_MCR_WR(prAdapter, MCR_IOUDR, u4RegValue);
        }

        /* RICR */
        HAL_MCR_RD(prAdapter, MCR_RICR, &u4RegValue);
        u4RegValue &= ~(RICR_RF_SW_MODE         |
                        RICR_ANT_SEL_P_SW_MODE  |
                        RICR_ANT_SEL_N_SW_MODE);

        u4RegValue |= (RICR_PA2EN               |
                       RICR_PA5EN);
        HAL_MCR_WR(prAdapter, MCR_RICR, u4RegValue);

        if (prAdapter->rPtaInfo.eCurrentState == PTA_STATE_ON) {
            /* BTCER0 */
            HAL_MCR_RD(prAdapter, MCR_BTCER0, &u4RegValue);
            u4RegValue |= (PTA_BTCER0_COEXIST_EN);
            HAL_MCR_WR(prAdapter, MCR_BTCER0, u4RegValue);

#if !PTA_NEW_BOARD_DESIGN
            /* GeorgeKuo(20090805): new single-antenna design. */
            nicPtaSetAnt(prAdapter, FALSE);
#endif
        }
        else {
#if !PTA_NEW_BOARD_DESIGN
            /* GeorgeKuo(20090805): new single-antenna design. */
            nicPtaSetAnt(prAdapter, TRUE);
#endif
        }
    }
    else { /* Dual antenna */

        if (prAdapter->rPtaInfo.u4PTAWireMode == PTA_SW_1_WIRE_MODE) {
            /* IOUDR */
            HAL_MCR_RD(prAdapter, MCR_IOUDR, &u4RegValue);
            u4RegValue &= ~(IOUDR_BT_PRI_PD | IOUDR_BT_PRI_PU);
            HAL_MCR_WR(prAdapter, MCR_IOUDR, u4RegValue);
        }
        if (prAdapter->rPtaInfo.eCurrentState == PTA_STATE_ON) {
            /* BTCER0 */
            HAL_MCR_RD(prAdapter, MCR_BTCER0, &u4RegValue);
            u4RegValue |= (PTA_BTCER0_COEXIST_EN);
            HAL_MCR_WR(prAdapter, MCR_BTCER0, u4RegValue);
        }
    }
#endif
    /* Note: place the instruction if GPIO or other pin need to be pull high/ low or
             set to input mode for preventing current leakage here...
    */


    /* turn on LED */
#if USE_DEBUG_LED_SIGNAL_FOR_LOW_POWER
    {
        P_CONNECTION_SETTINGS_T prConnSettings = &prAdapter->rConnSettings;
        if (prConnSettings->ucLedBlinkMode) {
            HAL_MCR_RD(prAdapter, MCR_LCR, &u4RegValue);
            HAL_MCR_WR(prAdapter, MCR_LCR, u4RegValue | (LCR_LED_OUTPUT));
        }
    }
#else
    /* LED Control */
    u4RegValue = 0;   
    u4RegValue &= ~LCR_LED_POLARITY; /* Active High */

    /* set LED timing */
    u4RegValue |= ((prAdapter->prGlueInfo->u4LedBlinkOnTime << 8) & LCR_LED_ON_CONT) |
                  (prAdapter->prGlueInfo->u4LedBlinkOffTime & LCR_LED_OFF_CONT);    

    /* set LED Mode */
  
    switch(prAdapter->prGlueInfo->u2LedBlinkMode)
    {
        case CFG_LED_MODE_NONE :
            u4RegValue = 0;
            break;
        case CFG_LED_MODE_TX :
            u4RegValue |= LCR_LED_MODE_TX_WO_BEACON | LCR_LED_MODE_TX_BEACON;
            break;
        case CFG_LED_MODE_RX :
            u4RegValue |= LCR_LED_MODE_RX_EX_RFCR_BEACON | LCR_LED_MODE_RX_RFCR_BEACON;
            break;
        case CFG_LED_MODE_TX_RX :
            u4RegValue |= LCR_LED_MODE_TX_WO_BEACON | LCR_LED_MODE_TX_BEACON | LCR_LED_MODE_RX_EX_RFCR_BEACON | LCR_LED_MODE_RX_RFCR_BEACON;
            break;    
        default :
            u4RegValue = 0;
            break;            
    }
    
    prAdapter->prGlueInfo->u4LedSetting = u4RegValue;

    //u4RegValue |= LCR_LED_MODE_TX_WO_BEACON | LCR_LED_MODE_TX_BEACON | LCR_LED_MODE_RX_EX_RFCR_BEACON | LCR_LED_MODE_RX_RFCR_BEACON;
    //kal_prompt_trace(MOD_WNDRV, "halpmPowerOn MCR_LCR : %x", u4RegValue);
    HAL_MCR_WR(prAdapter, MCR_LCR, u4RegValue);
#endif    

    /* clear interrupt status, due to logic reset is done in previous step
       (halpmPowerOn) */
    HAL_MCR_RD(prAdapter, MCR_HISR, &u4RegValue);
    HAL_MCR_RD(prAdapter, MCR_HSCISR, &u4RegValue);

}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to process the POWER OFF procedure.
*
* \param[in] prAdapter Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
halpmPowerOff (
    IN P_ADAPTER_T prAdapter
    )
{
    UINT_32 u4RegValue;

    ASSERT(prAdapter);

    /* turn off LED */
#if USE_DEBUG_LED_SIGNAL_FOR_LOW_POWER
    HAL_MCR_RD(prAdapter, MCR_LCR, &u4RegValue);
    HAL_MCR_WR(prAdapter, MCR_LCR, u4RegValue & ~LCR_LED_OUTPUT);
#else    
    u4RegValue = 0;
    HAL_MCR_WR(prAdapter, MCR_LCR, u4RegValue);
#endif

    /* Note: place the instruction if GPIO or other pin need to be pull high/ low or
             set to input mode for preventing current leakage here...
    */
#if PTA_ENABLED
    if (prAdapter->rPtaInfo.fgSingleAntenna) {
        /* RICR */
        HAL_MCR_RD(prAdapter, MCR_RICR, &u4RegValue);
        u4RegValue &= ~(RICR_SWANT_SEL_N_HIGH   |
                        RICR_PA2EN              |
                        RICR_PA5EN              |
                        RICR_SW_TR_SW_N         |
                        RICR_SW_RXADC_DCCAL_EN  |
                        RICR_SW_RF_TX           |
                        RICR_SW_RF_RX           |
                        RICR_SW_TR_SW_P         |
                        RICR_SW_TX_PE           |
                        RICR_SW_RX_PE);

        u4RegValue |= (RICR_RF_SW_MODE          |
                       RICR_ANT_SEL_P_SW_MODE   |
                       RICR_ANT_SEL_N_SW_MODE   |
                       RICR_SWANT_SEL_P_HIGH);
        HAL_MCR_WR(prAdapter, MCR_RICR, u4RegValue);

        /* BTCER1 */
        HAL_MCR_RD(prAdapter, MCR_BTCER1, &u4RegValue);
        u4RegValue &= ~(PTA_BTCER1_SINGLE_ANT);
        HAL_MCR_WR(prAdapter, MCR_BTCER1, u4RegValue);

        if (prAdapter->rPtaInfo.eCurrentState == PTA_STATE_ON) {
            /* BTCER0 */
            HAL_MCR_RD(prAdapter, MCR_BTCER0, &u4RegValue);
            u4RegValue &= ~(PTA_BTCER0_COEXIST_EN);
            HAL_MCR_WR(prAdapter, MCR_BTCER0, u4RegValue);
        }

        if (prAdapter->rPtaInfo.u4PTAWireMode == PTA_SW_1_WIRE_MODE) {
            /* IOUDR */
            HAL_MCR_RD(prAdapter, MCR_IOUDR, &u4RegValue);
            u4RegValue &= ~(IOUDR_BT_PRI_PD | IOUDR_BT_PRI_PU);
            u4RegValue |= IOUDR_BT_PRI_PD;
            HAL_MCR_WR(prAdapter, MCR_IOUDR, u4RegValue);
        }
    }
    else { /* Dual antenna */
        if (prAdapter->rPtaInfo.eCurrentState == PTA_STATE_ON) {
            /* BTCER0 */
            HAL_MCR_RD(prAdapter, MCR_BTCER0, &u4RegValue);
            u4RegValue &= ~(PTA_BTCER0_COEXIST_EN);
            HAL_MCR_WR(prAdapter, MCR_BTCER0, u4RegValue);
        }

        if (prAdapter->rPtaInfo.u4PTAWireMode == PTA_SW_1_WIRE_MODE) {
            /* IOUDR */
            HAL_MCR_RD(prAdapter, MCR_IOUDR, &u4RegValue);
            u4RegValue &= ~(IOUDR_BT_PRI_PD | IOUDR_BT_PRI_PU);
            u4RegValue |= IOUDR_BT_PRI_PD;
            HAL_MCR_WR(prAdapter, MCR_IOUDR, u4RegValue);
        }
    }
#endif
    /* set all trap pin to input mode to prevent current leakage.
     * (keep AntSel as the user configured value)
     */
    HAL_MCR_RD(prAdapter, MCR_IOPCR, &u4RegValue);
    u4RegValue &= ~IOPCR_ALL_TRAP_PIN_OUTPUT_EN;
#if PTA_ENABLED
    #if PTA_NEW_BOARD_DESIGN
    HAL_MCR_WR(prAdapter,
               MCR_IOPCR,
               u4RegValue);
    #else
    HAL_MCR_WR(prAdapter,
               MCR_IOPCR,
               u4RegValue |
               (prAdapter->rPtaInfo.fgSingleAntenna) ? (IOPCR_IO_ANT_SEL_P_DIR | IOPCR_IO_ANT_SEL_N_DIR |
                                                     IOPCR_IO_TR_SW_P_DIR | IOPCR_IO_TR_SW_N_DIR) : 0);
    #endif
#else
    HAL_MCR_WR(prAdapter,
               MCR_IOPCR,
               u4RegValue);
#endif

    /* NOTE:
       32KHz clock (internal/ external) is turned off in this procedure.
       But slow clock calibration procedure is only done in PM module initialization
       procedure now.
    */

    /* NOTE:
       We should gate PLL first and then disable PLL.
       MCR_CIR.PLL_ready reflects current PLL gating status (not the PLL enable status).
    */
    // Enable PLL gating and disable RF SX
    HAL_MCR_WR(prAdapter, MCR_HLPCR, HLPCR_RF_SX_PD | HLPCR_PLL_CLOCK_GATED);
    // Disable all clock sources, and enable PLL gating
    HAL_MCR_WR(prAdapter, MCR_HLPCR, HLPCR_PD_ALL | HLPCR_PLL_CLOCK_GATED);
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to enable the timeout counter.
*
* \param[in] prAdapter Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
halpmEnableTimeoutCounter (
    IN P_ADAPTER_T prAdapter
    )
{
    UINT_32 u4RegSpcr;

    ASSERT(prAdapter);

    HAL_MCR_RD(prAdapter, MCR_SPCR, &u4RegSpcr);
    HAL_MCR_WR(prAdapter, MCR_SPCR, u4RegSpcr & ~SPCR_TO_COUNTER_RESET_CTRL);
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to disable the timeout counter.
*
* \param[in] prAdapter Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
halpmDisableTimeoutCounter (
    IN P_ADAPTER_T prAdapter
    )
{
    UINT_32 u4RegSpcr;

    ASSERT(prAdapter);

    HAL_MCR_RD(prAdapter, MCR_SPCR, &u4RegSpcr);
    HAL_MCR_WR(prAdapter, MCR_SPCR, u4RegSpcr | SPCR_TO_COUNTER_RESET_CTRL);
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to set the TSF drift window.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[in] ucDriftWindow The value of the TSF drift window.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
halpmSetTsfDriftWindow (
    IN P_ADAPTER_T prAdapter,
    IN UINT_8    ucDriftWindow
    )
{
    UINT_32 u4RegValue;

    ASSERT(prAdapter);

    HAL_MCR_RD(prAdapter, MCR_TTAR, &u4RegValue);
    u4RegValue &= ~TTAR_TSF_TSF_DRIFT_WINDOW ;
    HAL_MCR_WR(prAdapter, MCR_TTAR, u4RegValue | (ucDriftWindow << 16));

    HAL_MCR_RD(prAdapter, MCR_LPCR, &u4RegValue);
    u4RegValue &= ~LPCR_TSF_DRIFT_INTR_EN;
    u4RegValue |= (ucDriftWindow == 0) ? 0 : LPCR_TSF_DRIFT_INTR_EN;
    HAL_MCR_WR(prAdapter, MCR_LPCR, u4RegValue);
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to set the TSF drift window.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[in] u2AtimWindow The value of the ATIM window.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
halpmSetAtimWindowValue (
    IN P_ADAPTER_T prAdapter,
    IN UINT_16    u2AtimWindow
    )
{
    ASSERT(prAdapter);

    HAL_MCR_WR(prAdapter, MCR_ACWR, u2AtimWindow);
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to reset the TSF timer
*
* \param[in] prAdapter Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
halpmResetTSFTimer (
    IN P_ADAPTER_T prAdapter
    )
{
    ASSERT(prAdapter);

    HAL_MCR_WR(prAdapter, MCR_UTTR0, 0);
    HAL_MCR_WR(prAdapter, MCR_UTTR1, 0);
    HAL_MCR_WR(prAdapter, MCR_TTAR, TTAR_TSF_TIMER_VALUE_CHANGE);

}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to setup beacon content check function
*
* \param[in] prAdapter Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
halpmSetupBeaconContentCheck (
    IN P_ADAPTER_T prAdapter,
    IN BOOLEAN fgEnable
    )
{
    UINT_32 u4RegValue;

    ASSERT(prAdapter);

    HAL_MCR_RD(prAdapter, MCR_MPTCR, &u4RegValue);
    u4RegValue &= ~MPTCR_BCN_CONTENT_CHK_EN;
    u4RegValue |= (fgEnable) ? MPTCR_BCN_CONTENT_CHK_EN : 0;
    HAL_MCR_WR(prAdapter, MCR_MPTCR, u4RegValue);
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to reset the TSF timer
*
* \param[in] pvAdapter Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
halpmSetupMoreDataTrigger (
    IN P_ADAPTER_T  prAdapter,
    IN BOOLEAN      fgEnable
    )
{
    UINT_32 u4RegValue;

    ASSERT(prAdapter);

    HAL_MCR_RD(prAdapter, MCR_MPTCR, &u4RegValue);
    u4RegValue &= ~MPTCR_MORE_TRIG_EN;
    u4RegValue |= (fgEnable) ? MPTCR_MORE_TRIG_EN : 0;
    HAL_MCR_WR(prAdapter, MCR_MPTCR, u4RegValue);
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to reset the TSF timer
*
* \param[in] pvAdapter Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
halpmSetupBeaconTimeoutDetection (
    IN P_ADAPTER_T  prAdapter,
    IN BOOLEAN      fgEnable
    )
{
    BOOLEAN fgBcnSpInvalid;
    UINT_32 u4RegValue;

    ASSERT(prAdapter);

    /* invalid SP before setting beacon timeout disable */
    HAL_MCR_RD(prAdapter, MCR_SPCR, &u4RegValue);
    fgBcnSpInvalid = (u4RegValue & SPCR_BEACON_SP_INVALID_MASK) ? TRUE : FALSE;
    HAL_MCR_WR(prAdapter, MCR_SPCR, u4RegValue | SPCR_BEACON_SP_INVALID_MASK);

    HAL_MCR_RD(prAdapter, MCR_MPTCR, &u4RegValue);
    u4RegValue &= ~MPTCR_BCN_TIMEOUT_EN;
    u4RegValue |= (fgEnable) ? MPTCR_BCN_TIMEOUT_EN : 0;
    HAL_MCR_WR(prAdapter, MCR_MPTCR, u4RegValue);

    /* restore SP before setting beacon timeout disable */
    HAL_MCR_RD(prAdapter, MCR_SPCR, &u4RegValue);
    if (!fgBcnSpInvalid) {
        u4RegValue &= ~SPCR_BEACON_SP_INVALID_MASK;
    }
    HAL_MCR_WR(prAdapter, MCR_SPCR, u4RegValue);

    /* reset timeout counter */
    HAL_MCR_RD(prAdapter, MCR_SPCR, &u4RegValue);
    HAL_MCR_WR(prAdapter, MCR_SPCR, u4RegValue | SPCR_TO_COUNTER_RESET_CTRL);
    HAL_MCR_WR(prAdapter, MCR_SPCR, u4RegValue & ~SPCR_TO_COUNTER_RESET_CTRL);
}

