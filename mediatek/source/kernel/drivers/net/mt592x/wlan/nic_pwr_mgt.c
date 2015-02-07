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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/nic_pwr_mgt.c#2 $
*/

/*! \file   "nic_pwr_mgt.c"
    \brief  The NIC layer file, which placed function for power management
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
** $Log: nic_pwr_mgt.c $
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\74 2009-08-06 16:44:05 GMT mtk01090
**  Use GPIO0 and GPIO2 to control antenna switch and remove obsolete compile flag CFG_SUPPORT_SINGLE_ANTENNA
**  \main\maintrunk.MT5921\73 2009-07-16 15:01:57 GMT mtk01104
**  Remove compiling warning in Linux debug mode
**  \main\maintrunk.MT5921\72 2009-07-13 14:47:42 GMT mtk01090
**  Correct watchdog timeout value calculation.
**  Ignore DTIM Period and wake up every N * TBTT if wake up interval is too large to let network application run smoothly.
**  Switch back to CAM mode for this AP connection if LP has problems for ship build.
**  \main\maintrunk.MT5921\71 2009-06-29 10:31:34 GMT mtk01090
**  Add debug message for CR01837 assertion fail
**  \main\maintrunk.MT5921\70 2009-05-14 20:46:49 GMT mtk01104
**  Return status of slow clock in nicpmRegInit()
**  \main\maintrunk.MT5921\69 2009-02-18 16:44:22 GMT mtk01084
**  Enhancement of the BT SCO voico quality when MT5921 enter LP
**  \main\maintrunk.MT5921\68 2009-02-16 17:56:18 GMT mtk01084
**  modify for controlling beacon lost detection function
**  \main\maintrunk.MT5921\67 2009-02-11 19:51:58 GMT mtk01084
**  Fix the LP watchdog, due to U-APSD service period
**  \main\maintrunk.MT5921\66 2009-02-05 21:42:35 GMT mtk01084
**  PS-related parameters modification for BT/WiFi coexistence optimization
**  \main\maintrunk.MT5921\65 2009-01-05 10:11:16 GMT mtk01725
**  Add a variable for setting DTIM period according to different SLT mode.
**  \main\maintrunk.MT5921\64 2008-12-01 13:56:22 GMT mtk01461
**  Remove Warning 613: Possible use of null pointer from lint
**  \main\maintrunk.MT5921\63 2008-09-24 10:58:16 GMT mtk01084
**  add single antenna related support function
**  \main\maintrunk.MT5921\62 2008-09-08 11:25:00 GMT mtk01084
**  modify for the LP instruction programming
**  \main\maintrunk.MT5921\61 2008-09-05 17:09:55 GMT mtk01084
**  modify LP instruction programming for the requirement from single antenna selection
**  \main\maintrunk.MT5921\60 2008-09-04 14:44:34 GMT mtk01084
**  modify the LP programming parts
**  \main\maintrunk.MT5921\59 2008-08-30 10:14:34 GMT mtk01084
**  use macro instead of number directly
**  \main\maintrunk.MT5921\58 2008-08-11 21:31:36 GMT mtk01084
**  modify for coding rule conformance
**  \main\maintrunk.MT5921\57 2008-07-15 22:36:16 GMT mtk01084
**  modify for the IBSS-PS related issue
**  \main\maintrunk.MT5921\56 2008-07-07 20:22:17 GMT mtk01084
**  workaround for HEC 6173 for different chip versions
**  \main\maintrunk.MT5921\55 2008-06-19 15:52:52 GMT mtk01084
**  fix compiler warning
**  \main\maintrunk.MT5921\54 2008-06-18 20:45:17 GMT mtk01084
**  revise beacon timeout handling procedure
**  \main\maintrunk.MT5921\53 2008-05-21 16:51:10 GMT mtk01084
**  wakeup at every TBTT when LP_SLT is performed
**  \main\maintrunk.MT5921\52 2008-05-12 15:40:48 GMT mtk01084
**  1. set beacon timeout by referencing beacon interval
**  2. modify the usage of halpmConfigLowPowerSettingInAdhoc
**  \main\maintrunk.MT5921\51 2008-05-03 14:36:14 GMT mtk01461
**  Update coding style
**  \main\maintrunk.MT5921\50 2008-04-28 21:59:04 GMT mtk01084
**  modify the lines in programming pattern filter
**  \main\maintrunk.MT5921\49 2008-04-28 17:27:33 GMT mtk01084
**  minor change for configuring ad hoc related function
**  \main\maintrunk.MT5921\48 2008-04-11 17:21:33 GMT mtk01084
**  modify the procedure to create IBSS for setting next TBTT
**  \main\maintrunk.MT5921\47 2008-04-10 20:09:04 GMT mtk01084
**  Add TX throughput into PS mode switching criterion under PSP-fast mode.
**  \main\maintrunk.MT5921\46 2008-03-31 15:39:22 GMT mtk01084
**  not to reset TSF whenever transition from scan to ibss alone
**  \main\maintrunk.MT5921\45 2008-03-26 23:41:17 GMT mtk01084
**  modify the method to set IP address for pattern search
**  \main\maintrunk.MT5921\44 2008-03-25 21:59:15 GMT mtk01084
**  workaround on the function to set IP address into pattern search
**  \main\maintrunk.MT5921\43 2008-03-20 11:58:15 GMT mtk01084
**  set the ARP pattern search only when IP address is valid
**  \main\maintrunk.MT5921\42 2008-03-14 20:41:05 GMT mtk01084
**  set to use basic rate for HW transmitted packets
**  \main\maintrunk.MT5921\41 2008-03-12 15:33:10 GMT mtk01084
**  remove un-necessary assert
**  \main\maintrunk.MT5921\40 2008-03-06 22:26:26 GMT mtk01084
**  add function description
**  \main\maintrunk.MT5921\39 2008-03-03 18:10:32 GMT mtk01084
**  modify function description comments
**  \main\maintrunk.MT5921\38 2008-02-21 23:22:59 GMT mtk01084
**  rename function call
**  \main\maintrunk.MT5921\37 2008-02-18 17:24:16 GMT mtk01084
**  add function description
**  \main\maintrunk.MT5921\36 2008-02-15 19:20:41 GMT mtk01084
**  revise function name
**  \main\maintrunk.MT5921\35 2008-02-14 09:56:56 GMT mtk01084
**  add function to set pattern
**  \main\maintrunk.MT5921\34 2008-02-04 21:00:06 GMT mtk01084
**  do the turn on clock recovery once LP fail to own back
**  \main\maintrunk.MT5921\33 2008-01-16 20:49:27 GMT mtk01084
**  only to enable pattern search related function when IBSS network is connected
**  \main\maintrunk.MT5921\32 2008-01-03 21:32:35 GMT mtk01084
**  only to enable TSF drift detection while in connected state
**  \main\maintrunk.MT5921\31 2007-12-20 15:46:32 GMT mtk01084
**  Modify lines in setting the Null frame tyoe
**  \main\maintrunk.MT5921\30 2007-12-16 19:26:41 GMT mtk01084
**  enable TSF drift detection function
**  \main\maintrunk.MT5921\29 2007-12-11 14:54:26 GMT mtk01084
**  modify the arguments of programming LP instructions
**  \main\maintrunk.MT5921\28 2007-11-30 20:17:57 GMT mtk01084
**  program pattern search register by profile setting
**  \main\maintrunk.MT5921\27 2007-11-30 19:45:41 GMT mtk01084
**  modify clock calibration function parameters
**  \main\maintrunk.MT5921\26 2007-11-29 09:45:37 GMT mtk01084
**  remove un-used lines
**  \main\maintrunk.MT5921\25 2007-11-27 11:57:00 GMT mtk01084
**  modify lines in setting ARP packet filter
**  \main\maintrunk.MT5921\24 2007-11-22 22:19:22 GMT mtk01084
**  modify variable name
**  \main\maintrunk.MT5921\23 2007-11-21 10:31:26 GMT mtk01084
**  modify LP instruction programming
**  \main\maintrunk.MT5921\22 2007-11-20 17:34:47 GMT mtk01084
**  modify function name
**  \main\maintrunk.MT5921\21 2007-11-20 16:20:54 GMT mtk01084
**  add pattern search related function
**  \main\maintrunk.MT5921\20 2007-11-19 12:14:55 GMT mtk01084
**  modify halpmConfigPattern() input argument
**  \main\maintrunk.MT5921\19 2007-11-13 18:04:00 GMT mtk01084
**  use HAL functions instead of register access
**  \main\maintrunk.MT5921\18 2007-11-08 14:03:47 GMT mtk01084
**  reset TSF when creating IBSS
**  \main\maintrunk.MT5921\17 2007-11-02 01:01:50 GMT mtk01461
**  Unify TX Path for Normal and IBSS Power Save + IBSS neighbor learning
**  \main\maintrunk.MT5921\16 2007-10-31 21:31:56 GMT mtk01084
**  add nicpmEnableTimeoutCounter/ nicpmDisableTimeoutCounter function
**  \main\maintrunk.MT5921\15 2007-10-31 16:09:44 GMT mtk01084
**  add lines to check if it is locating in ATIM window
**  \main\maintrunk.MT5921\14 2007-10-30 20:13:56 GMT mtk01084
**  modify place to disable LP function
**  \main\maintrunk.MT5921\13 2007-10-26 19:07:19 GMT mtk01084
**  remove duplicated beacon timeout handler
**  \main\maintrunk.MT5921\12 2007-10-26 10:28:29 GMT mtk01084
**  add ACPI power control
**  \main\maintrunk.MT5921\11 2007-10-25 18:06:26 GMT mtk01461
**  Add VOIP SCAN Support  & Refine Roaming
** Revision 1.2  2007/07/13 05:18:08  MTK01084
** update for few nic function
**
** Revision 1.1  2007/07/05 14:06:38  MTK01084
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
* \brief This routine is used to switch PS mode.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
* \param[in] fgIsPwrSave Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
nicpmSwitchPwrMgtMode (
    IN P_ADAPTER_T prAdapter,
    IN BOOLEAN fgIsPwrSave
    )
{
    ASSERT(prAdapter);

    halpmSwitchPwrMgtBit(prAdapter, fgIsPwrSave);
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to set HW to enter low power state.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
* \param[in] fgEnableGlobalInt Indicate whether to enable GINT or not.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
nicpmEnterLowPower (
    IN P_ADAPTER_T prAdapter,
    IN BOOLEAN     fgEnableGlobalInt
    )
{
    ASSERT(prAdapter);

    halpmEnterLowPower(prAdapter, fgEnableGlobalInt);
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to set HW exit from low power state.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
nicpmLeaveLowPower (
    IN P_ADAPTER_T prAdapter
    )
{
    P_PM_INFO_T prPmInfo;

    ASSERT(prAdapter);

    prPmInfo = &prAdapter->rPmInfo;

    if (!halpmLeaveLowPower(prAdapter, prPmInfo->u2GuardTimePhase2 + 1000)) {
        /* Recovery procedure when clock is not ready */
        nicpmPowerOn(prAdapter);
    }
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to setup all the necessary configurations used for
*        creating or joining an IBSS network.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
* \param[in] prPmConnSetupInfo Pointer of the structure of PM configurations.
* \param[in] fgCreateIbss Boolean flag to indicate if it is going to create an IBSS.
*
* \retval TRUE
*/
/*----------------------------------------------------------------------------*/
BOOLEAN
nicpmSetupPmInfoInAdhoc (
    IN P_ADAPTER_T              prAdapter,
    IN P_PM_CONN_SETUP_INFO_T   prPmConnSetupInfo,
    IN BOOLEAN                  fgCreateIbss
    )
{
    P_PM_INFO_T prPmInfo;
    P_PM_PROFILE_SETUP_INFO_T prPmProfSetupInfo;


    ASSERT(prAdapter);
    ASSERT(prPmConnSetupInfo);

    prPmInfo = &prAdapter->rPmInfo;
    prPmProfSetupInfo = &prPmInfo->rPmProfSetupInfo;

    /* Initialize LP instruction number, all of the extra instruction need to be re-programmed again */
    prPmInfo->ucNumOfInstSleep = 0;
    prPmInfo->ucNumOfInstAwake = 0;
    prPmInfo->ucNumOfInstOn = 0;

    /* program beacon search timeout */
#if CFG_IBSS_POWER_SAVE
    if (prPmConnSetupInfo->u2AtimWindow) {
        /* it is reasonable that beacon timeout is lager than ATIM window
        */
        halpmSetBeaconTimeout(prAdapter,
                              0,
                              prPmConnSetupInfo->u2AtimWindow,
                              FALSE,
                              TRUE,
                              BEACON_TIMEOUT_COUNT_ADHOC);
    } else
#endif /* CFG_IBSS_POWER_SAVE */
    {
        halpmSetBeaconTimeout(prAdapter,
                              BEACON_MIN_TIMEOUT_VALUE,
                              prPmConnSetupInfo->u2BcnIntv - 4,//BEACON_MAX_TIMEOUT_VALUE,
                              TRUE,
                              TRUE,
                              BEACON_TIMEOUT_COUNT_ADHOC);
    }


    if (fgCreateIbss) {
        /* To create a new IBSS
        */

        /* Reset local TSF timer to 0, and next TBTT timer will be updated/ calculated by
           halpmConfigLowPowerSettingInAdhoc()
        */
        halpmResetTSFTimer(prAdapter);
    }
    else {
        /* To merge with an IBSS
        */

        // Enable TSF drift detection, and value set to 1 TU
        halpmSetTsfDriftWindow(prAdapter, DEFAULT_TSF_DRIFT_WINDOW_TU);

        // Enable Service period
        nicpmSetupServicePeriodMechanism(prAdapter, SP_BEACON, 0);

        // Setup ARP pattern search for allowing only our ARP request/ response match our IP address
        nicpmPatternConfigArpFilter(prAdapter, &prPmInfo->u4IpAddress);

        // Enable pattern search function
        nicpmConfigPatternSearchFunc(prAdapter,
                                     prPmProfSetupInfo->fgBcPtrnSrchEn,
                                     prPmProfSetupInfo->fgMcPtrnSrchEn,
                                     prPmProfSetupInfo->fgUcPtrnSrchEn,
                                     prPmProfSetupInfo->fgBcPtrnMatchRcv,
                                     prPmProfSetupInfo->fgMcPtrnMatchRcv,
                                     prPmProfSetupInfo->fgUcPtrnMatchRcv,
                                     FALSE);
    }

    halpmConfigLowPowerSettingInAdhoc(prAdapter,
                                      prPmConnSetupInfo->u2BcnIntv,
                                      prPmConnSetupInfo->u2AtimWindow,
                                      1,    //prPmProfSetupInfo->ucMultiTbttWake,
                                      prPmProfSetupInfo->u2HwTxLifeTime,
                                      (fgCreateIbss) ? FALSE : TRUE);


    // Enable HW function(s)
    halpmEnableLowPowerFunctionsInAdhoc(prAdapter, fgCreateIbss);

    return TRUE;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to setup all the necessary configurations used for
*        joining an INFRASTRUCTURE network.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
* \param[in] prPmConnSetupInfo Pointer of the structure of PM configurations.
*
* \retval TRUE
*/
/*----------------------------------------------------------------------------*/
BOOLEAN
nicpmSetupPmInfoInBss (
    IN P_ADAPTER_T              prAdapter,
    IN P_PM_CONN_SETUP_INFO_T   prPmConnSetupInfo
    )
{
    P_PM_INFO_T prPmInfo;
    P_PM_PROFILE_SETUP_INFO_T prPmProfSetupInfo;
    P_BSS_INFO_T prBssInfo;
    UINT_8 ucDtimPeriod;
    UINT_32 u4SleepPeriodTU;

    DEBUGFUNC("nicpmSetupPmInfoInBss");

    ASSERT(prAdapter);
    ASSERT(prPmConnSetupInfo);

    prPmInfo = &prAdapter->rPmInfo;
    prPmProfSetupInfo = &prPmInfo->rPmProfSetupInfo;
    prBssInfo = &prAdapter->rBssInfo;

    /* Initialize LP instruction number, all of the extra instruction need to be re-programmed again */
    prPmInfo->ucNumOfInstSleep = 0;
    prPmInfo->ucNumOfInstAwake = 0;
    prPmInfo->ucNumOfInstOn = 0;

#if DBG
    /* prevent divide by 0 */
    if (prPmConnSetupInfo->ucDtimPeriod == 0) {
        prPmConnSetupInfo->ucDtimPeriod = 1;
        ASSERT(0);
    }
    if (prPmProfSetupInfo->ucMultiDtimWake == 0) {
        prPmProfSetupInfo->ucMultiDtimWake = 1;
        ASSERT(0);
    }
    if (prPmConnSetupInfo->u2BcnIntv == 0) {
        prPmConnSetupInfo->u2BcnIntv = 100;
        ASSERT(0);
    }
#endif

#if CFG_LP_PATTERN_SEARCH_SLT
    switch (prAdapter->eSLTModeSel) {
    case SLT_MODE_NORMAL:
        ucDtimPeriod = prPmConnSetupInfo->ucDtimPeriod;
        break;
    case SLT_MODE_LP:
        ucDtimPeriod = 1;
        break;
    case SLT_MODE_PATTERN_SEARCH:
    default:
        ucDtimPeriod = prPmConnSetupInfo->ucDtimPeriod;
    }
#else
    ucDtimPeriod = prPmConnSetupInfo->ucDtimPeriod;
#endif

    /* CR1853: Calculate sleep period in unit of TU */
    u4SleepPeriodTU = prPmProfSetupInfo->ucMultiDtimWake *
        ucDtimPeriod *
        prPmConnSetupInfo->u2BcnIntv;

    if (u4SleepPeriodTU > prPmProfSetupInfo->u2DtimIntvThr) {
        /* GeorgeKuo: It's a strange case that DL UC packets will be delayed
        * more than u2DtimIntvThr seconds (default:2s). Change behavior: wake up
        * every ucMultiTbttWake TBTT to get UC packets more quickly.
        */
        if ( (prPmProfSetupInfo->ucWorkaroundTbttCount * prPmConnSetupInfo->u2BcnIntv)
            > prPmProfSetupInfo->u2DtimIntvThr) {
            /* if workaround TBTT count or beacon interval are too large, wake
            * up every TBTT.
            */
            prPmProfSetupInfo->ucMultiTbttWake = 1;
        }
        else {
            /* else use workaround TBTT count (default:2) as multi TBTT count */
            prPmProfSetupInfo->ucMultiTbttWake = prPmProfSetupInfo->ucWorkaroundTbttCount;
        }
        DBGLOG(LP, INFO, ("u4SleepPeriodTU(%ld) > u2DtimIntvThr(%d), wake up every (%d) TBTT\n",
            u4SleepPeriodTU,
            prPmProfSetupInfo->u2DtimIntvThr,
            prPmProfSetupInfo->ucWorkaroundTbttCount));
    }
    else {
        prPmProfSetupInfo->ucMultiTbttWake = DEFAULT_MULTIPLE_TBTT_COUNT;
    }

//for fixed DTIMWakeUp
#if 1
{
    UINT_32 wakeUp = prPmProfSetupInfo->ucMultiDtimWake;

    if(gPlatformCfg.rWifiCustom.u4MultiDtimWake){
	wakeUp = gPlatformCfg.rWifiCustom.u4MultiDtimWake;
    do_div(wakeUp, prPmConnSetupInfo->u2BcnIntv);	

    if(wakeUp < 1)
	wakeUp = 1;
    else if(wakeUp > 7)
	wakeUp = 7; 	
    }


    halpmConfigLowPowerSettingInBss(prAdapter,
                                    prPmConnSetupInfo->u2AID,
                                    prPmConnSetupInfo->u2BcnIntv,
                                    ucDtimPeriod,
                                    (prPmConnSetupInfo->fgIsUapsdConn) ?
                                    prPmProfSetupInfo->bmfgApsdEnAc : 0,
                                    (UINT_8)wakeUp,
                                    prPmProfSetupInfo->ucMultiTbttWake,
                                    (prBssInfo->rWmmInfo.ucWmmFlag & WMM_FLAG_SUPPORT_WMM) ?
                                        prPmProfSetupInfo->fgUseAgeQoSNull : 0,
                                    prPmProfSetupInfo->ucAgeNullPeriod,
                                    prPmProfSetupInfo->ucQoSNullTid,
                                    prPmProfSetupInfo->ucTrgThr,
                                    prPmProfSetupInfo->u2HwTxLifeTime);
}
#else
    halpmConfigLowPowerSettingInBss(prAdapter,
                                    prPmConnSetupInfo->u2AID,
                                    prPmConnSetupInfo->u2BcnIntv,
                                    ucDtimPeriod,
                                    (prPmConnSetupInfo->fgIsUapsdConn) ?
                                        prPmProfSetupInfo->bmfgApsdEnAc : 0,
                                    prPmProfSetupInfo->ucMultiDtimWake,
                                    prPmProfSetupInfo->ucMultiTbttWake,
                                    (prBssInfo->rWmmInfo.ucWmmFlag & WMM_FLAG_SUPPORT_WMM) ?
                                        prPmProfSetupInfo->fgUseAgeQoSNull : 0,
                                    prPmProfSetupInfo->ucAgeNullPeriod,
                                    prPmProfSetupInfo->ucQoSNullTid,
                                    prPmProfSetupInfo->ucTrgThr,
                                    prPmProfSetupInfo->u2HwTxLifeTime);
#endif

    /* program beacon search timeout */
    halpmSetBeaconTimeout(prAdapter,
                          BEACON_MIN_TIMEOUT_VALUE,
                          prPmConnSetupInfo->u2BcnIntv - 4,//BEACON_MAX_TIMEOUT_VALUE,
                          TRUE,
                          TRUE,
                          BEACON_TIMEOUT_COUNT_INFRA);

    // Check the beacon earlier time transmitted by AP ahead from TBTT */
    halpmEnableBeaconEarlyCheck(prAdapter);

    // Enable TSF drift detection, and value set to 1 TU
    halpmSetTsfDriftWindow(prAdapter, DEFAULT_TSF_DRIFT_WINDOW_TU);

    // Enable Service period (with disable all first)
    nicpmSetupServicePeriodMechanism(prAdapter, 0, SP_ALL);
    nicpmSetupServicePeriodMechanism(prAdapter, SP_ALL, 0);

    // Setup ARP pattern search for allowing only our ARP request match our IP address
    nicpmPatternConfigArpFilter(prAdapter, &prPmInfo->u4IpAddress);

    // Enable pattern search function
    nicpmConfigPatternSearchFunc(prAdapter,
                                 prPmProfSetupInfo->fgBcPtrnSrchEn,
                                 prPmProfSetupInfo->fgMcPtrnSrchEn,
                                 prPmProfSetupInfo->fgUcPtrnSrchEn,
                                 prPmProfSetupInfo->fgBcPtrnMatchRcv,
                                 prPmProfSetupInfo->fgMcPtrnMatchRcv,
                                 prPmProfSetupInfo->fgUcPtrnMatchRcv,
                                 FALSE);

    // Enable HW function(s)
    halpmEnableLowPowerFunctionsInBss(prAdapter,
                                      ((prPmProfSetupInfo->ucMultiTbttWake) ? TRUE : FALSE));

    return TRUE;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to disable PM function, include register configurations.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
nicpmAbortPmFunc (
    IN P_ADAPTER_T prAdapter
    )
{
    P_PM_INFO_T prPmInfo;


    ASSERT(prAdapter);

    prPmInfo = &prAdapter->rPmInfo;

    /* Initialize LP instruction number, all of the extra instruction need to be re-programmed again */
    prPmInfo->ucNumOfInstSleep = 0;
    prPmInfo->ucNumOfInstAwake = 0;
    prPmInfo->ucNumOfInstOn = 0;

    // Restore ATIM window to 0 (disable the function)
    halpmSetAtimWindowValue(prAdapter, 0);

    // Disable all LP function
    halpmDisableLowPowerFunctions(prAdapter);

    // Disable TSF drift detection
    nicpmSetTsfDriftWindow(prAdapter, 0);

    // Disable pattern search function
    nicpmConfigPatternSearchFunc(prAdapter,
                                 FALSE,
                                 FALSE,
                                 FALSE,
                                 FALSE,
                                 FALSE,
                                 FALSE,
                                 FALSE);
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to initialize PM register configurations.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
*
* \return TRUE  Success
*         FALSE Fail to do slow clock calibration
*/
/*----------------------------------------------------------------------------*/
BOOLEAN
nicpmRegInit (
    IN P_ADAPTER_T prAdapter
    )
{
    P_PM_INFO_T prPmInfo;
    BOOLEAN fgStatus;

    ASSERT(prAdapter);

    prPmInfo = &prAdapter->rPmInfo;

    // Low power related register initialization
    halpmRegInit(prAdapter);

    /* Set OSC stable time */
    halpmSetOscStableTime(prAdapter, prAdapter->rEEPROMCtrl.u2OscStableTimeUs);

    // Calibrate 32K slow clock
    fgStatus = nicpmCalSlowClock(prAdapter, &prAdapter->rPmInfo.rSlowClkCnt);

    if (fgStatus) {
        /* Low Power instructions */
        if (prAdapter->ucRevID == MTK_CHIP_MP_REVERSION_ID) {
            prPmInfo->au4LowPowerInst_sleep[prPmInfo->ucNumOfInstSleep++] =
                LP_INST_DELAY(25, FALSE, FALSE);
        }
        // Low power instruction programming
        NIC_PM_PROGRAM_LP_INSRUCTION(prAdapter, FALSE);

        // Program wakeup guard time
        nicpmSetupWakeupGuardTime(prAdapter, &prAdapter->rPmInfo.rSlowClkCnt);
    }

    nicSetHwTxByBasicRate(prAdapter, TRUE);

    return fgStatus;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to setup HW service period guard function.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
* \param[in] u4ValidateSP The valid service period to be guard.
* \param[in] u4InvalidateSP The invalid service period not to be guard.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
nicpmSetupServicePeriodMechanism (
    IN P_ADAPTER_T  prAdapter,
    IN UINT_32      u4ValidateSP,
    IN UINT_32      u4InvalidateSP
    )
{
    ASSERT(prAdapter);

    halpmSetupServicePeriodMechanism(prAdapter, u4ValidateSP, u4InvalidateSP);
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to setup HW service period guard function.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
* \param[out] prSlowClkCnt Pointer to the time of calibrated 32K clock period.
*
* \retval TRUE
* \retval FALSE
*/
/*----------------------------------------------------------------------------*/
BOOLEAN
nicpmCalSlowClock (
    IN P_ADAPTER_T prAdapter,
    OUT P_PM_SLOW_CLOCK_COUNT_T prSlowClkCnt
    )
{
    ASSERT(prAdapter);
    ASSERT(prSlowClkCnt);

    return halpmCalSlowClock(prAdapter,
                             &prSlowClkCnt->uc32kSlowCount,
                             &prSlowClkCnt->uc32kSlowCount_10,
                             &prSlowClkCnt->uc32kSlowCount_100,
                             &prSlowClkCnt->uc32kSlowCount_1000);

}   /* nicpmSlowClockCal */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to setup HW service period guard function.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
* \param[in] prSlowClkCnt Pointer to the time of calibrated 32K clock period.
*
* \retval TRUE
* \retval FALSE
*/
/*----------------------------------------------------------------------------*/
VOID
nicpmSetupWakeupGuardTime (
    IN P_ADAPTER_T prAdapter,
    IN P_PM_SLOW_CLOCK_COUNT_T prSlowClkCnt
    )
{
    P_PM_INFO_T prPmInfo;

    ASSERT(prAdapter);
    ASSERT(prSlowClkCnt);

    prPmInfo = &prAdapter->rPmInfo;

    halpmCalculateGuardTime(prAdapter,
                            prSlowClkCnt->uc32kSlowCount,
                            prSlowClkCnt->uc32kSlowCount_10,
                            prSlowClkCnt->uc32kSlowCount_100,
                            prSlowClkCnt->uc32kSlowCount_1000,
                            &prPmInfo->u2GuardTimePhase2,
                            &prPmInfo->u2GuardTimePhase3);

    halpmSetupWakeupGuardTime(prAdapter,
                              prPmInfo->u2GuardTimePhase2,
                              prPmInfo->u2GuardTimePhase3);
}   /* nicpmSetupWakeupGuardTime */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to adjust HW wake up guard time by the beacon
*        ealier time.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
* \param[in] u2BeaconEarlyOffset Value of the beacon earlier time.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
nicpmAdjustWakeupGuardTime (
    IN P_ADAPTER_T prAdapter,
    IN UINT_16 u2BeaconEarlyOffset
    )
{
    P_PM_INFO_T prPmInfo;

    ASSERT(prAdapter);

    prPmInfo = &prAdapter->rPmInfo;

    prPmInfo->u2GuardTimePhase2 += u2BeaconEarlyOffset;
    prPmInfo->u2GuardTimePhase3 += u2BeaconEarlyOffset;

    halpmSetupWakeupGuardTime(prAdapter,
                              prPmInfo->u2GuardTimePhase2,
                              prPmInfo->u2GuardTimePhase3);
}   /* nicpmAdjustWakeupGuardTime */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to get the beacon earlier time.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
*
* \retval UINT_16 Value of the beacon earlier time
*/
/*----------------------------------------------------------------------------*/
UINT_16
nicpmGetBeaconEarlyValue (
    IN P_ADAPTER_T prAdapter
    )
{
    ASSERT(prAdapter);

    return halpmGetBeaconEarlyValue(prAdapter);
}   /* nicpmGetBeaconEarlyValue */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to process the TBTT interrupt event.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
nicProcessTbttInterrupt (
    IN P_ADAPTER_T      prAdapter
    )
{

#if CFG_IBSS_POWER_SAVE

    ASSERT(prAdapter);

    if (!PM_IS_UNDER_IBSS_POWER_SAVE_MODE(prAdapter)) {
        return;
    }

    PM_SET_FLAG_UNDER_ATIM_WINDOW(prAdapter);

    DBGLOG(LP, INFO, (" \n"));

    nicTxDisableTxQueueActiveState(prAdapter);

    /* Flush and reclaim TX active chain, send wait queue into STA wait queue */
    nicTxReclaimTxPackets(prAdapter);

    /* clear IBSS STA awake state recorded by station record */
    pmClearAllStationAwakeState(prAdapter);

    /* Enable AC4 for ATIM */
    nicTxStartQueues(prAdapter, TXQ_MGMT_MASK);
#endif /* CFG_IBSS_POWER_SAVE */

    return;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to process the BEACON_TR_OK interrupt event.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
nicProcessBeaconTxRxOkInterrupt (
    IN P_ADAPTER_T      prAdapter
    )
{

#if CFG_IBSS_POWER_SAVE
    UINT_32 i;
    UINT_8 aucBCAddr[] = BC_MAC_ADDR;
    P_STA_INFO_T prStaInfo;
    BOOLEAN fgIsGcStaWaitQueueNotEmpty = FALSE;
    UINT_8 aucMacAddrArray[MAC_ADDR_LEN * CFG_MAX_NUM_STA_RECORD];
    UINT_32 u4NumSta;


    ASSERT(prAdapter);
    prStaInfo = &prAdapter->rStaInfo;

    if (!PM_IS_UNDER_IBSS_POWER_SAVE_MODE(prAdapter)) {
        return;
    }

    if (prAdapter->rArbInfo.eCurrentState == ARB_STATE_SCAN) {
        return;
    }

    DBGLOG(LP, INFO, ("\n"));

    /* Send broadcast ATIM to let all station keep awake,
       if there's any broadcast or multicast entries
       (do we need to send unicast ATIM anyway?)
    */
    for (i = TC0; i <= TC3; i++) {
        if (QUEUE_IS_NOT_EMPTY(&prStaInfo->arGcStaWaitQueue[i])) {
            fgIsGcStaWaitQueueNotEmpty = TRUE;
            break;
        }
    }


    if (fgIsGcStaWaitQueueNotEmpty) {
        pmSendAtimFrame(prAdapter,
                         aucBCAddr,
                         arbSetAdhocAllStaAwake);

    }
    else {
        if (pmGetBufferedTxInfoInStaRec(prAdapter,
                                        aucMacAddrArray,
                                        sizeof(aucMacAddrArray),
                                        &u4NumSta)) {

            /* Send unicast ATIM frames by station wait queue */
            for (i = 0; i < u4NumSta; i++) {

                pmSendAtimFrame(prAdapter,
                                 &aucMacAddrArray[i * MAC_ADDR_LEN],
                                 arbSetAdhocStaAwake);
            }
        }
        else {
            ASSERT(0);
        }
    }

#endif /* CFG_IBSS_POWER_SAVE */

    return;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to process the ATIM window timeout interrupt event.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
nicProcessAtimWindowTimeoutInterrupt (
    IN P_ADAPTER_T      prAdapter
    )
{
#if CFG_IBSS_POWER_SAVE

    ASSERT(prAdapter);

    if (!PM_IS_UNDER_IBSS_POWER_SAVE_MODE(prAdapter)) {
        return;
    }

    PM_SET_FLAG_OUTSIDE_ATIM_WINDOW(prAdapter);

    DBGLOG(LP, INFO, ("\n"));

    nicTxDisableTxQueueActiveState(prAdapter);

    /* flush AC4 for in-completed ATIM packets */
    nicTxFlushStopQueues(prAdapter, TXQ_MGMT_MASK, TXQ_MGMT_MASK);

    /* Enable AC0~3, AC4 (for out-of-bound MGMT frame) */
    nicTxStartQueues(prAdapter, TXQ_DATA_MASK | TXQ_MGMT_MASK);

    /* Trigger TX actions */
    if (nicTxRetransmitOfStaWaitQue(prAdapter)) {
        pmDisableIbssPsTx(prAdapter);
    }

#endif /* CFG_IBSS_POWER_SAVE */

    return;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to check if it is an ad hoc master currently.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
BOOLEAN
nicpmIfAdhocStaMaster (
    IN P_ADAPTER_T      prAdapter
    )
{
    ASSERT(prAdapter);

    return halpmIfAdhocStaMaster(prAdapter);
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to process the POWER ON procedure.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
nicpmPowerOn (
    IN P_ADAPTER_T prAdapter
    )
{
    ASSERT(prAdapter);

    halpmPowerOn(prAdapter, prAdapter->rPmInfo.rSlowClkCnt.uc32kSlowCount);
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to process the POWER OFF procedure.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
nicpmPowerOff (
    IN P_ADAPTER_T prAdapter
    )
{
    ASSERT(prAdapter);

    halpmPowerOff(prAdapter);
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to ENABLE the HW mechanism of the timeout counter.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
nicpmEnableTimeoutCounter (
    IN P_ADAPTER_T prAdapter
    )
{
    ASSERT(prAdapter);

    halpmEnableTimeoutCounter(prAdapter);
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to DISABLE the HW mechanism of the timeout counter.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
nicpmDisableTimeoutCounter (
    IN P_ADAPTER_T prAdapter
    )
{
    ASSERT(prAdapter);

    halpmDisableTimeoutCounter(prAdapter);
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to set the value of the TSF drift window.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
* \param[in] ucDriftWindow Value of the TSF drift window.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
nicpmSetTsfDriftWindow (
    IN P_ADAPTER_T prAdapter,
    IN UINT_8    ucDriftWindow
    )
{
    ASSERT(prAdapter);

    halpmSetTsfDriftWindow(prAdapter, ucDriftWindow);
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to configure the IP address of the
*        ARP request/ response frame used for pattern search function.
*        Note: it is a special handler for the pattern search configuration, and
*              will always configure it to index 0.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
* \param[in] aucIpAddr Pointer of the IP address (LSB -> MSB).
*
* \retval TRUE
*/
/*----------------------------------------------------------------------------*/
BOOLEAN
nicpmPatternConfigArpFilter (
    IN P_ADAPTER_T  prAdapter,
    IN PUINT_32     pu4IpAddr
    )
{
    UINT_8 i;
    P_PM_INFO_T prPmInfo;

    ASSERT(prAdapter);
    ASSERT(pu4IpAddr);

    prPmInfo = &prAdapter->rPmInfo;

    if (!prPmInfo->fgIpAddressIsValid) {
        return FALSE;
    }


    /* This pattern include UC/ BC/ MC ARP request and response.
     * It will configure index 0 always, and keep others empty.
     */
    nicpmConfigPattern(prAdapter,
                       0,       // Use index 0 now
                       TRUE,
                       TRUE,
                       TRUE,
                       FALSE,
                       FALSE,
                       FALSE,
                       TRUE,
                       FALSE,   // Use OR now
                       FALSE,
                       BITS(0, 3),
                       0x20,
                       pu4IpAddr);

#if 1 // overwrite other entries to zero
    for (i = 1; i < HW_PATTERN_SEARCH_SET_NUMBER; i++) {
        nicpmConfigPattern(prAdapter,
                           i,   // entry index
                           FALSE,
                           FALSE,
                           FALSE,
                           FALSE,
                           FALSE,
                           FALSE,
                           FALSE,
                           FALSE,
                           FALSE,
                           0,
                           0,
                           NULL);
    }
#endif

    return TRUE;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to configure the pattern used for pattern search.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
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
nicpmConfigPattern (
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
    P_PM_INFO_T prPmInfo;

    ASSERT(prAdapter);

    prPmInfo = &prAdapter->rPmInfo;

    halpmConfigPattern(prAdapter,
                       ucIndex,
                       fgCheckBcA1,
                       fgCheckMcA1,
                       fgCheckUcA1,
                       fgIpv4Ip,
                       fgIpv6Icmp,
                       fgGarpIpEqual,
                       fgArpCtrl,
                       fgAndOp,
                       fgNotOp,
                       ucPatternMask,
                       ucPatternOffset,
                       pu4Pattern);


    if (fgCheckBcA1 && ucPatternMask) {
        prPmInfo->u4BcPatternXIsValid |= (UINT_32)(1 << ucIndex);
    }
    else {
        prPmInfo->u4BcPatternXIsValid &= ~((UINT_32)(1 << ucIndex));
    }
    if (fgCheckMcA1 && ucPatternMask) {
        prPmInfo->u4McPatternXIsValid |= (UINT_32)(1 << ucIndex);
    }
    else {
        prPmInfo->u4McPatternXIsValid &= ~((UINT_32)(1 << ucIndex));
    }
    if (fgCheckUcA1 && ucPatternMask) {
        prPmInfo->u4UcPatternXIsValid |= (UINT_32)(1 << ucIndex);
    }
    else {
        prPmInfo->u4UcPatternXIsValid &= ~((UINT_32)(1 << ucIndex));
    }
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to configure the function used for pattern search.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
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
nicpmConfigPatternSearchFunc (
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
    P_PM_INFO_T prPmInfo;
    P_PM_PROFILE_SETUP_INFO_T prPmProfSetupInfo;

    ASSERT(prAdapter);

    prPmInfo = &prAdapter->rPmInfo;
    prPmProfSetupInfo = &prPmInfo->rPmProfSetupInfo;

    /* It should check the pattern validation,
       if intending to ENABLE pattern search function.
     */
    if (!prPmInfo->u4BcPatternXIsValid && fgBcA1En) {
        fgBcA1En = FALSE;
    }
    if (!prPmInfo->u4McPatternXIsValid && fgMcA1En) {
        fgMcA1En = FALSE;
    }
    if (!prPmInfo->u4UcPatternXIsValid && fgUcA1En) {
        fgUcA1En = FALSE;
    }

    /* Note: It will over-write the setting in the PM profile */

#if 0 // Application should always invoke this function after connected
    // Backup the setting which is duplicated in "prPmProfSetupInfo"
    prPmProfSetupInfo->fgBcPtrnSrchEn = fgBcA1En;
    prPmProfSetupInfo->fgMcPtrnSrchEn = fgMcA1En;
    prPmProfSetupInfo->fgUcPtrnSrchEn = fgUcA1En;
    prPmProfSetupInfo->fgBcPtrnMatchRcv = fgBcA1MatchDrop;
    prPmProfSetupInfo->fgMcPtrnMatchRcv = fgMcA1MatchDrop;
    prPmProfSetupInfo->fgUcPtrnMatchRcv = fgUcA1MatchDrop;
#endif

    // Enable pattern search function
    halpmConfigPatternSearchFunction(prAdapter,
                                     fgBcA1En,
                                     fgMcA1En,
                                     fgUcA1En,
                                     fgBcA1MatchDrop,
                                     fgMcA1MatchDrop,
                                     fgUcA1MatchDrop,
                                     fgIpv6MatchCtrl);

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
nicpmResetTSFTimer (
    IN P_ADAPTER_T prAdapter
    )
{
   halpmResetTSFTimer(prAdapter);
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
nicpmSetToBeaconTimeoutStep (
    IN P_ADAPTER_T              prAdapter,
    IN ENUM_PM_BCN_TO_STEPS_T   eStep
    )
{
    P_PM_INFO_T prPmInfo;
    P_BSS_INFO_T prBssInfo;
    UINT_8          ucMinTimeoutValue = 0;
    UINT_16         u2MaxTimeoutValue = 0;
    BOOLEAN         fgMinTimeoutValid = FALSE;
    BOOLEAN         fgMaxTimeoutValid = FALSE;

    ASSERT(prAdapter);

    prPmInfo = &prAdapter->rPmInfo;
    prBssInfo = &prAdapter->rBssInfo;


    if (eStep >= BCN_TO_STEP_NUM) {
        ASSERT(0);
        return;
    }

    switch (eStep) {
    case BCN_TO_STEP_0:
        ucMinTimeoutValue = BEACON_MIN_TIMEOUT_VALUE;
        u2MaxTimeoutValue = prBssInfo->u2BeaconInterval - 4;
        fgMinTimeoutValid = TRUE;
        fgMaxTimeoutValid = TRUE;
        break;
    case BCN_TO_STEP_1:
        ucMinTimeoutValue = 15;
        u2MaxTimeoutValue = prBssInfo->u2BeaconInterval - 4;
        fgMinTimeoutValid = TRUE;
        fgMaxTimeoutValid = TRUE;
        break;
    case BCN_TO_STEP_2:
        ucMinTimeoutValue = 31;
        u2MaxTimeoutValue = prBssInfo->u2BeaconInterval - 4;
        fgMinTimeoutValid = TRUE;
        fgMaxTimeoutValid = TRUE;
        break;
    case BCN_TO_STEP_3:
        ucMinTimeoutValue = 63;
        u2MaxTimeoutValue = prBssInfo->u2BeaconInterval - 4;
        fgMinTimeoutValid = TRUE;
        fgMaxTimeoutValid = TRUE;
        break;
    case BCN_TO_STEP_4:
        ucMinTimeoutValue = 0;
        u2MaxTimeoutValue = prBssInfo->u2BeaconInterval - 4;
        fgMinTimeoutValid = FALSE;
        fgMaxTimeoutValid = TRUE;
        break;
    default:
        break;
    }

    /* program beacon search timeout */
    halpmSetBeaconTimeout(prAdapter,
                          ucMinTimeoutValue,
                          u2MaxTimeoutValue,
                          fgMinTimeoutValid,
                          fgMaxTimeoutValid,
                          BEACON_TIMEOUT_COUNT_INFRA);

    prPmInfo->eBeaconTimeoutTuningStep = eStep;

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
BOOLEAN
nicpmStepBeaconTimeout (
    IN P_ADAPTER_T prAdapter,
    IN BOOLEAN fgStepUp
    )
{
    P_PM_INFO_T prPmInfo;
    BOOLEAN         fgStatus = TRUE;

    ASSERT(prAdapter);

    prPmInfo = &prAdapter->rPmInfo;

    if (fgStepUp) {
        DBGLOG(INIT, INFO, ("Step Up (%d)\n", prPmInfo->eBeaconTimeoutTuningStep));
    } else {
        DBGLOG(INIT, INFO, ("Step Down (%d)\n", prPmInfo->eBeaconTimeoutTuningStep));
    }

    if (fgStepUp) {
        /* Stepping UP */
        switch (prPmInfo->eBeaconTimeoutTuningStep) {
        case BCN_TO_STEP_0:
            nicpmSetToBeaconTimeoutStep(prAdapter, BCN_TO_STEP_1);
            break;
        case BCN_TO_STEP_1:
            nicpmSetToBeaconTimeoutStep(prAdapter, BCN_TO_STEP_2);
            break;
        case BCN_TO_STEP_2:
            nicpmSetToBeaconTimeoutStep(prAdapter, BCN_TO_STEP_3);
            break;
        case BCN_TO_STEP_3:
            nicpmSetToBeaconTimeoutStep(prAdapter, BCN_TO_STEP_4);
            break;
        case BCN_TO_STEP_4:
            fgStatus = FALSE;
            break;
        default:
            break;
        }
    }
    else {
        /* Stepping DOWN */
        switch (prPmInfo->eBeaconTimeoutTuningStep) {
        case BCN_TO_STEP_0:
            ASSERT(0);
            break;
        case BCN_TO_STEP_1:
            nicpmSetToBeaconTimeoutStep(prAdapter, BCN_TO_STEP_0);
            fgStatus = FALSE;
            break;
        case BCN_TO_STEP_2:
            nicpmSetToBeaconTimeoutStep(prAdapter, BCN_TO_STEP_1);
            break;
        case BCN_TO_STEP_3:
            nicpmSetToBeaconTimeoutStep(prAdapter, BCN_TO_STEP_2);
            break;
        case BCN_TO_STEP_4:
            nicpmSetToBeaconTimeoutStep(prAdapter, BCN_TO_STEP_3);
            break;
        default:
            break;
        }
    }

    return fgStatus;
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
nicpmResetBeaconContentCheck (
    IN P_ADAPTER_T prAdapter
    )
{
    halpmSetupBeaconContentCheck(prAdapter, FALSE);
    halpmSetupBeaconContentCheck(prAdapter, TRUE);
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
nicpmSetupMoreDataTrigger (
    IN P_ADAPTER_T  prAdapter,
    IN BOOLEAN      fgEnable
    )
{
    ASSERT(prAdapter);

    halpmSetupMoreDataTrigger(prAdapter, fgEnable);
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
nicpmSetupBeaconTimeoutDetection (
    IN P_ADAPTER_T  prAdapter,
    IN BOOLEAN      fgEnable
    )
{
    ASSERT(prAdapter);

    halpmSetupBeaconTimeoutDetection(prAdapter, fgEnable);
}

