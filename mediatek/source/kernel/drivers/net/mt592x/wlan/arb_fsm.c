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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/arb_fsm.c#2 $
*/

/*! \file   "arb_fsm.c"
    \brief  This is the arbiter among various WLAN modules.

    In arbiter, it makes decision of state transition, in arbiter's FSM(Finite
    State Machine) will describe the cause and effect according to various
    conditions in detail.
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
** $Log: arb_fsm.c $
 *
 * 01 20 2011 enlai.chu
 * [ALPS00029717] [Need Patch] [Volunteer Patch][Merge ALPS to ALPS2.3_DEV]For BT and BWCS and WiFi check-in
 * .
 *
 * 06 10 2010 jim.zhang
 * [ALPS00008051]change mt592x to UNGPL version 
 * .
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\226 2009-09-30 23:05:02 GMT mtk01090
**  In standby state, transit to POWER_OFF state if D3 is set. If D3 is not set but rf test mode is, transit to RF_TEST state. 
**  When handling Abort Event, take RF_TEST state into consideration to stop tx/rx. 
**  \main\maintrunk.MT5921\225 2009-08-18 22:56:06 GMT mtk01090
**  Add Linux SDIO (with mmc core) support.
**  Add Linux 2.6.21, 2.6.25, 2.6.26.
**  Fix compile warning in Linux.
**  \main\maintrunk.MT5921\224 2009-08-04 11:52:13 GMT mtk01090
**  Initialize STA RECORD list for META mode
**  \main\maintrunk.MT5921\223 2009-07-16 11:32:47 GMT mtk01461
**  Update last scan request time for SEARCH->SCAN
**  \main\maintrunk.MT5921\222 2009-07-06 20:32:33 GMT mtk01088
**  adding the code for wpi packet handler
**  \main\maintrunk.MT5921\221 2009-06-22 21:23:17 GMT mtk01088
**  add a variable to clear the fifo empty event signal 
**  \main\maintrunk.MT5921\220 2009-06-11 17:52:57 GMT mtk01725
**  Return IO pin test result directly. Because there are two set of pin test, thus we need two bits to represent the result.
**  \main\maintrunk.MT5921\219 2009-05-25 22:47:05 GMT mtk01090
**  \main\maintrunk.MT5921\218 2009-05-23 14:48:50 GMT mtk01088
**  send de-auth frame for class error by using AC3
**  \main\maintrunk.MT5921\217 2009-05-23 14:44:18 GMT mtk01088
**  send a de-auth frame at arbiter abort path,for oid set ssid
**  \main\maintrunk.MT5921\216 2009-05-14 20:02:13 GMT mtk01104
**  In arbFsmInit() and arbFsmTransAction_RESET_to_STANDBY,
**  set test mode if wrong EEPROM or slow clock
**  \main\maintrunk.MT5921\215 2009-05-11 13:07:27 GMT mtk01088
**  enable the ALC function while arbiter transition from IDLE to standby and disable at transition from IDLE to standby
**  \main\maintrunk.MT5921\214 2009-04-03 14:47:26 GMT mtk01461
**  Add remove the Scan Record of Current BSS for beacon timeout case
**  \main\maintrunk.MT5921\213 2009-04-01 16:49:25 GMT mtk01104
**  Invoke ptaFsmInit() in last order to let BT own antenna for a longer tme
**  \main\maintrunk.MT5921\212 2009-03-20 01:05:53 GMT mtk01461
**  Merge the ConnectionReqEvent into AbortEvent, so that we can do abort IDLE and go to STANDBY for the issue of setting D3 at IDLE STATE
**  \main\maintrunk.MT5921\211 2009-03-09 20:48:16 GMT mtk01461
**  Add a timeout function to check if we can leave AdHoc Protection Mode
**  \main\maintrunk.MT5921\210 2009-02-25 16:11:00 GMT mtk01084
**  handle beacon timeout when continuous 10 HW TX excessive retry fail
**  \main\maintrunk.MT5921\209 2009-02-16 23:44:34 GMT mtk01461
**  Fix the error handling part of CR1377 patch which may release TX Buffer twice and cause Access Violation
**  \main\maintrunk.MT5921\208 2009-02-06 19:51:34 GMT mtk01725
**  After packet TX event timeout, add condition check for current rftest state. Only tx packet when rftest state is in autotest TX.
**  \main\maintrunk.MT5921\207 2009-02-06 16:24:16 GMT mtk01725
**  Chancel packet tx timer when stop packet tx.
**  \main\maintrunk.MT5921\206 2009-02-06 10:49:13 GMT mtk01725
**  Change Packet Tx method under META mode.
**  Schdule a timer to continue TX rftest packet instead of doing it in TX done interrupt.
**  Initial HW timer when reset.
**  add a timeout event to do rftestTX().
**  cancel this timer in arbAbort.
**  \main\maintrunk.MT5921\205 2009-02-05 21:42:28 GMT mtk01084
**  modify OSC daisy chain related function in META mode
**  \main\maintrunk.MT5921\204 2009-02-05 17:41:06 GMT mtk01084
**  fix lines regarding chip reset will clear OSC daisy chain related setting during ACPI D3
**  \main\maintrunk.MT5921\203 2009-02-05 17:24:55 GMT mtk01725
**  Change function "arbFsmInit(), arbFsmUnInit(), arbFsmTransAction_RESET_to_STANDBY(), arbFsmSteps()" for META. Add one more switch case for arbFsmRunEventAbort() for META.
**  FSM would not leave test mode under META.
**  \main\maintrunk.MT5921\202 2009-02-02 14:26:37 GMT mtk01084
**  modify continuous polling mechanism, with not to do extra poll when no WiFi downlink traffic
**  \main\maintrunk.MT5921\201 2009-01-22 12:53:07 GMT mtk01088
**  add the code to translate the Legacy 802.1x frame to 802.11 format and using mgmt method to send out
**  \main\maintrunk.MT5921\200 2009-01-05 10:06:39 GMT mtk01725
**  Change compiling flag.
**  \main\maintrunk.MT5921\199 2008-12-10 17:25:56 GMT mtk01084
**  disable GINT whenever switch to IDLE state
**  \main\maintrunk.MT5921\198 2008-12-01 19:05:12 GMT mtk01084
**  prevent Lint warning
**  \main\maintrunk.MT5921\197 2008-12-01 13:56:07 GMT mtk01461
**  Remove Warning 611: Suspicious cast
**  \main\maintrunk.MT5921\196 2008-11-28 14:40:50 GMT mtk01088
**  fixed some lint warning
**
**  \main\maintrunk.MT5921\195 2008-11-25 21:11:00 GMT mtk01725
**  \main\maintrunk.MT5921\194 2008-11-24 21:04:43 GMT mtk01425
**  1. Add PTA_ENABLED flag
**  \main\maintrunk.MT5921\193 2008-11-21 23:59:01 GMT mtk01725
**  \main\maintrunk.MT5921\192 2008-11-21 23:16:08 GMT mtk01725
**  \main\maintrunk.MT5921\191 2008-11-04 23:02:25 GMT mtk01725
**  Bug Fix
**  \main\maintrunk.MT5921\190 2008-10-29 20:49:32 GMT mtk01084
**  prevent the asstion in set timer
**  \main\maintrunk.MT5921\189 2008-10-27 15:01:51 GMT mtk01084
**  supporting continuous polling mode
**  \main\maintrunk.MT5921\188 2008-10-24 13:46:38 GMT mtk01084
**  modify input argument of caller to nicSetupOpChnlList()
**  \main\maintrunk.MT5921\187 2008-10-22 10:57:44 GMT mtk01461
**  Update for lint diagnosis support
**  \main\maintrunk.MT5921\186 2008-09-12 11:24:01 GMT mtk01461
**  Refine code - remove unnecessary ASSERT()
**  \main\maintrunk.MT5921\185 2008-09-02 22:20:57 GMT mtk01461
**  Revise TX Aggregation to support TX Fragmentation
**  \main\maintrunk.MT5921\184 2008-09-02 21:04:22 GMT mtk01461
**  Remove ASSERT for Linux in arbFsmInit()
**  \main\maintrunk.MT5921\183 2008-08-25 20:41:16 GMT mtk01088
**  fixed the process disassociate request frame queue operation error
**  \main\maintrunk.MT5921\182 2008-08-25 09:45:12 GMT mtk01461
**  Update for Driver Review
**  \main\maintrunk.MT5921\181 2008-08-16 11:46:11 GMT mtk01088
**  adjust the input paramter
**  \main\maintrunk.MT5921\180 2008-08-12 10:45:27 GMT mtk01084
**  Refine BG SSID scan request in arbFsmStep()
**  \main\maintrunk.MT5921\179 2008-08-12 09:57:27 GMT mtk01461
**  Fix Error handling in arbFsmInit() if nicReadConfig() or nicAllocateAdapterMemory() was fail.
**  delete arbFsmRunEventLogicReset(), arbFsmTransAction_IDLE_to_SCAN()/SCAN_to_IDLE().
**
**  \main\maintrunk.MT5921\178 2008-08-02 16:23:52 GMT mtk01104
**  Invoke nicSetGPIO1Mode() when state is changed to standby from reset
**  \main\maintrunk.MT5921\177 2008-07-25 17:05:34 GMT mtk01461
**  Add TX FIFO Aggregate Function to improve TX throughput
**  \main\maintrunk.MT5921\176 2008-07-16 15:26:03 GMT mtk01104
**  1. Support GPIO2 mode  2. Compile option "BUILD_PTA"
**  \main\maintrunk.MT5921\175 2008-07-15 19:18:15 GMT mtk01104
**  Remove compiling warning for Windows
**  \main\maintrunk.MT5921\174 2008-07-14 13:52:37 GMT mtk01104
**  Update fgIsEnableTxAutoFragmentForBT in function arbFsmTransAction_RESET_to_STANDBY()
**  \main\maintrunk.MT5921\173 2008-07-11 17:33:11 GMT mtk01084
**  modify the default operational channel
**  \main\maintrunk.MT5921\172 2008-07-11 09:45:28 GMT mtk01084
**  Always append the country information whenever creating IBSS (if multi-domain is disabled)
**  \main\maintrunk.MT5921\171 2008-07-11 09:35:51 GMT mtk01088
**  adjust the 1x used ac while assoc with wmm ap
**  \main\maintrunk.MT5921\170 2008-07-10 21:11:49 GMT mtk01084
**  bypass redundent assert
**  \main\maintrunk.MT5921\169 2008-07-10 17:13:28 GMT mtk01088
**  if pairwise key not exist, use AC4 to send 802.1x packet, other use AC3
**  \main\maintrunk.MT5921\168 2008-07-10 16:37:41 GMT mtk01084
**  support 802.11d related functions
**  \main\maintrunk.MT5921\167 2008-07-08 11:25:58 GMT mtk01461
**  Update comments
**  \main\maintrunk.MT5921\166 2008-07-07 15:45:18 GMT mtk01084
**  fix the fail issue that caused by rLastScanRequestTime is not initial
**  \main\maintrunk.MT5921\165 2008-07-07 13:38:04 GMT mtk01461
**  Revise the timing of enable TXQ under WPA2 auth mode for roaming to prevent unencrypted frame before EAPOL frame.
**  \main\maintrunk.MT5921\164 2008-07-01 20:09:46 GMT mtk01084
**  apply timeout when doing scan request
**  \main\maintrunk.MT5921\163 2008-07-01 17:39:23 GMT mtk01088
**  remove the pmk cache while driver do media disconnect
**  \main\maintrunk.MT5921\162 2008-07-01 10:59:05 GMT mtk01425
**  1. Add assertion for rftest
**  2. Correct the layer of the rftest
**  \main\maintrunk.MT5921\161 2008-07-01 10:54:15 GMT mtk01084
**  switch back to the PS or ACTIVE mode based on the mode before scan
**  \main\maintrunk.MT5921\160 2008-06-18 20:44:59 GMT mtk01084
**  revise beacon timeout handling procedure
**  \main\maintrunk.MT5921\159 2008-06-17 16:28:41 GMT mtk01425
**  1. Queue packet to OsSendQueue if there is packet in any AC queues
**  \main\maintrunk.MT5921\158 2008-06-16 16:33:36 GMT mtk01084
**  fix compiler flag about supporting 11A issue
**  \main\maintrunk.MT5921\157 2008-06-16 16:10:37 GMT mtk01084
**  support whether to support SSID recover state by compiler flag
**  \main\maintrunk.MT5921\156 2008-06-14 11:15:53 GMT MTK01088
**  Assign the 802.1x frame send via TCM, and assert for no msdu resource
**  \main\maintrunk.MT5921\155 2008-06-13 01:06:39 GMT mtk01461
**  Do not delay Media Disconnect Even Indication for IBSS
**  \main\maintrunk.MT5921\154 2008-06-12 21:01:02 GMT mtk01084
**  modify scan channel list ordering
**  \main\maintrunk.MT5921\153 2008-06-12 20:30:23 GMT mtk01461
**  Add dwell min/ext time definition of SCAN parameters f
**  \main\maintrunk.MT5921\152 2008-06-11 09:49:32 GMT MTK01088
**  for cetk one_card 12,13 test item, not clear the scan result at enter D3 path, and move the scan result descriptor at reset to standby path, let the driver can direct use the scan result and connect to AP by connection setting,
**  \main\maintrunk.MT5921\151 2008-06-10 22:45:50 GMT mtk01084
**  initialize supported channel list
**  \main\maintrunk.MT5921\150 2008-06-02 11:57:44 GMT MTK01084
**  remove un-used function
**  \main\maintrunk.MT5921\149 2008-06-01 14:01:49 GMT mtk01084
**  modify arbFsmRunEventIST() interface
**
**  \main\maintrunk.MT5921\148 2008-05-30 15:49:18 GMT mtk01461
**  Add check WMM Assoc Flag
**  \main\maintrunk.MT5921\147 2008-05-30 15:14:36 GMT mtk01084
**  modify in the place transition by ACPI D3
**  \main\maintrunk.MT5921\146 2008-05-29 14:15:08 GMT mtk01084
**  modify arbFsmInit() init path
**  \main\maintrunk.MT5921\145 2008-05-23 20:56:03 GMT mtk01084
**  set it to ARB_STATE_POWER_OFF when it's under ACPI_STATE_D3
**  \main\maintrunk.MT5921\144 2008-05-23 10:10:55 GMT mtk01084
**  interrupt control during in-out IDLE state
**  \main\maintrunk.MT5921\143 2008-05-22 13:41:41 GMT mtk01461
**  Fix compile error
**  \main\maintrunk.MT5921\142 2008-05-22 10:52:38 GMT mtk01461
**  Zero BSS_INFO_T when uninitial
**  \main\maintrunk.MT5921\141 2008-05-20 13:20:57 GMT mtk01084
**  update RCPI variance check under SLT
**  \main\maintrunk.MT5921\140 2008-05-16 20:11:35 GMT mtk01461
**  Add scan result aging function in the path from SEARCH to SCAN when driver disconnect
**  \main\maintrunk.MT5921\139 2008-05-16 14:50:09 GMT mtk01461
**  Add more condition in SEARCH state for the case if we can't find any candidate for Roaming.
**  \main\maintrunk.MT5921\138 2008-05-16 10:45:49 GMT mtk01461
**  Revise RCPI related function for RSSI OID & Roaming
**  \main\maintrunk.MT5921\137 2008-05-15 14:04:36 GMT mtk01461
**  Fix compile warning in Linux
**  \main\maintrunk.MT5921\136 2008-05-13 22:14:34 GMT mtk01084
**  aborting PM function when aborting from IBSS_ALONE
**  \main\maintrunk.MT5921\135 2008-05-13 22:06:05 GMT mtk01084
**  not to do TSF reset on arbFsmTransAction_IBSS_MERGE_to_NORMAL_TR
**  \main\maintrunk.MT5921\134 2008-05-12 16:00:56 GMT mtk01084
**  modify rWaitBeaconWatchdogTimer from rArbInfo to rPmInfo
**  \main\maintrunk.MT5921\133 2008-05-03 18:53:20 GMT mtk01461
**  Add nicExistIBSS() for change operation mode when leave IBSS
**  \main\maintrunk.MT5921\132 2008-05-03 14:13:08 GMT mtk01461
**  Update comment
**  \main\maintrunk.MT5921\131 2008-05-03 13:14:58 GMT mtk01461
**  Return all pending TX frames after DISCONNECT indicated.
**  \main\maintrunk.MT5921\130 2008-04-28 17:15:17 GMT mtk01084
**  scan 14 channels under BG SSID scan
**  \main\maintrunk.MT5921\129 2008-04-24 14:34:46 GMT mtk01084
**  modify BG SSID scan channel list
**  \main\maintrunk.MT5921\128 2008-04-22 15:46:56 GMT mtk01084
**  remove logic reset on disabling BG SSID scan path
**  \main\maintrunk.MT5921\127 2008-04-16 15:22:00 GMT mtk01461
**  Add logic reset after leave BG_SSID_SCAN
**  Fix Scan for Hidden SSID.
**  \main\maintrunk.MT5921\126 2008-04-13 22:06:26 GMT mtk01461
**  Fix 1c wlan bssid fail after disassociate OID issued
**  \main\maintrunk.MT5921\125 2008-04-11 17:11:50 GMT mtk01461
**  Fix EAPOL packet retry due to RX queue off/on
**  \main\maintrunk.MT5921\124 2008-04-10 23:58:52 GMT mtk01385
**  1. fix lose disconnect indicate event when enter test mode.
**  \main\maintrunk.MT5921\123 2008-04-10 20:08:53 GMT mtk01084
**  Add TX throughput into PS mode switching criterion under PSP-fast mode.
**  \main\maintrunk.MT5921\122 2008-04-07 22:14:36 GMT mtk01084
**  use LP-IOT index for printing debug message under LP-IOT
**  \main\maintrunk.MT5921\121 2008-04-02 20:44:01 GMT mtk01084
**  Support for RCPI variance histogram
**  \main\maintrunk.MT5921\120 2008-03-31 13:49:31 GMT mtk01461
**  Move the roaming enable flag to rConnSetting
**  \main\maintrunk.MT5921\119 2008-03-31 09:52:32 GMT mtk01461
**  Add send deauth/disassoc for class error
**  \main\maintrunk.MT5921\118 2008-03-30 22:00:50 GMT mtk01084
**  add RCPI check in LP-IOT
**  \main\maintrunk.MT5921\117 2008-03-25 22:46:00 GMT mtk01084
**  modify logic reset procedure
**  \main\maintrunk.MT5921\116 2008-03-25 21:45:40 GMT mtk01084
**  modify the callback function prototype on change PS mode
**  \main\maintrunk.MT5921\115 2008-03-23 20:37:13 GMT mtk01461
**  Fix the issue that can't create new IBSS after disconnect previous IBSS
**  \main\maintrunk.MT5921\114 2008-03-23 15:18:08 GMT mtk01084
**  move reset scan_done event procedure to reset.c
**  \main\maintrunk.MT5921\113 2008-03-21 18:15:18 GMT mtk01084
**  reset SCAN_DONE event on logic reset
**  \main\maintrunk.MT5921\112 2008-03-20 11:54:03 GMT mtk01084
**  clear the scan done event when doing logic reset
**  \main\maintrunk.MT5921\111 2008-03-18 09:56:27 GMT mtk01088
**  adjust the code to update and clean the pmkid candidate
**  \main\maintrunk.MT5921\110 2008-03-14 19:06:53 GMT mtk01084
**  modify background SSID scan lines
**  \main\maintrunk.MT5921\109 2008-03-13 15:45:36 GMT mtk01084
**  modify the BG SSID initial setting
**  \main\maintrunk.MT5921\108 2008-03-13 15:31:47 GMT mtk01461
**  Refine the relationship between SCAN result and STA record, lifetime, aging policy etc
**  \main\maintrunk.MT5921\107 2008-03-13 14:28:13 GMT mtk01461
**  Revise functions for Roaming Module
**  Rename IsValidSSID to IsConnReqIssued
**  \main\maintrunk.MT5921\106 2008-03-12 09:52:02 GMT mtk01461
**  Add Connection diagnostic function
**  Remove type case in MSDU_INFO_OBJ_INIT
**  \main\maintrunk.MT5921\105 2008-03-11 13:36:00 GMT mtk01084
**  modify arbFsmRunEventScanRequest() function argument
**  \main\maintrunk.MT5921\104 2008-03-07 19:36:22 GMT mtk01084
**  add the function argument for send null frame function
**  \main\maintrunk.MT5921\103 2008-03-07 10:51:34 GMT mtk01084
**  add function description
**  \main\maintrunk.MT5921\102 2008-03-06 22:25:27 GMT mtk01084
**  rename PM related function
**  \main\maintrunk.MT5921\101 2008-03-04 21:51:06 GMT mtk01385
**  1. modify arbFsm Run event Join Disassoc Tx Done and arbFsm Run Event Sec Deauth Done function parameters.
**  \main\maintrunk.MT5921\100 2008-03-03 21:53:47 GMT mtk01385
**  1. "move scan result" action  move from before scan request to after scan request setup complete.
**  \main\maintrunk.MT5921\99 2008-03-03 18:09:55 GMT mtk01084
**  halpmEnableLowPowerFunctionsInBss
**  \main\maintrunk.MT5921\98 2008-02-29 15:52:03 GMT mtk01088
**  add send disassociate handle function
**  \main\maintrunk.MT5921\97 2008-02-29 15:15:56 GMT mtk01088
**  add rsn check at Tx path
**  \main\maintrunk.MT5921\96 2008-02-29 12:58:21 GMT mtk01088
**  refine the sec module related code
**  also fixed the ASSERT for arbiter Transition from JOIN to SEARCH while rcv disassociation frame
**  \main\maintrunk.MT5921\95 2008-02-27 12:12:13 GMT mtk01461
**  Revise code to use macro instead of kalMemCopy
**  \main\maintrunk.MT5921\94 2008-02-21 23:13:00 GMT mtk01084
**  do not abort PM function on this transition
**  \main\maintrunk.MT5921\93 2008-02-20 10:14:41 GMT mtk01461
**  STANDBY to IDLE will set RadioOff = TRUE, vise versa(RadioOff = FALSE)
**  \main\maintrunk.MT5921\92 2008-02-18 17:23:19 GMT mtk01084
**  add function description
**  \main\maintrunk.MT5921\91 2008-02-15 19:19:38 GMT mtk01084
**  revise function name
**  \main\maintrunk.MT5921\90 2008-02-12 23:26:47 GMT mtk01461
**  Add debug level - Event
**  \main\maintrunk.MT5921\89 2008-02-12 23:00:27 GMT mtk01461
**  Add TX auto fragmentation for BT support
**  \main\maintrunk.MT5921\88 2008-02-04 17:03:46 GMT mtk01461
**  Refine ARB_IF_IN_RFTEST_STATE
**  \main\maintrunk.MT5921\87 2008-02-01 14:03:36 GMT mtk01385
**  1. add thermo and statistics UnInit function to arbFsm UnInit.
**  \main\maintrunk.MT5921\86 2008-02-01 09:23:05 GMT mtk01385
**  1. Fix WinCE 4.2 compiling error.
**  \main\maintrunk.MT5921\85 2008-01-31 17:40:55 GMT mtk01385
**  1. add thermo init function
**  \main\maintrunk.MT5921\84 2008-01-24 14:12:15 GMT mtk01088
**  remove non-used code
**  \main\maintrunk.MT5921\83 2008-01-22 22:48:24 GMT mtk01084
**  invoke macros for control PM under TX path
**  \main\maintrunk.MT5921\82 2008-01-22 15:51:08 GMT mtk01084
**  set default packet filter on initialization path
**  \main\maintrunk.MT5921\81 2008-01-16 20:54:11 GMT mtk01084
**  setting up the LP related register on the transition from IBSS_MERGE to normal_TR
**  \main\maintrunk.MT5921\80 2008-01-07 15:17:04 GMT mtk01461
**  Fix Warnning Message of unused variable
**  \main\maintrunk.MT5921\79 2008-01-07 15:06:23 GMT mtk01461
**  Add SDIO Enhance Support
**  Add PhyType & AdHocMode Selection Support
**  \main\maintrunk.MT5921\78 2008-01-03 20:52:34 GMT mtk01084
**  remove lines in setting RF configuration
**  \main\maintrunk.MT5921\77 2007-12-29 16:15:01 GMT mtk01385
**  1. Move h/w queue memory test from Chip reset function to arb init function.
**  \main\maintrunk.MT5921\76 2007-12-27 13:57:07 GMT mtk01088
**  adjust the sec fsm and wlan table init timing
**  \main\maintrunk.MT5921\75 2007-12-26 20:23:17 GMT mtk01088
**  do pmkid clear while media disconnect
**  \main\maintrunk.MT5921\74 2007-12-26 19:48:49 GMT mtk01084
**  force scan abort on BG SSID SCAN state to SEARCH state
**  \main\maintrunk.MT5921\73 2007-12-25 23:33:55 GMT mtk01084
**  remove SCAN <--> BG SSID Scan state transition
**  \main\maintrunk.MT5921\72 2007-12-24 18:15:38 GMT mtk01088
**  Let ssid invalid while do uninit
**
**  \main\maintrunk.MT5921\71 2007-12-24 11:43:39 GMT mtk01084
**  determine if it is able to do scan by the request
**  \main\maintrunk.MT5921\70 2007-12-20 16:57:43 GMT mtk01084
**  cancel VoIP timer on ARB unitialization routine
**  \main\maintrunk.MT5921\69 2007-12-20 15:25:32 GMT mtk01084
**  move the place to initialize timer for VoIP from arbFsmInit() to arbTransitionFromResetToStandby()
**  \main\maintrunk.MT5921\68 2007-12-20 14:56:14 GMT mtk01461
**  Fix at PS_VOIP_PARTIAL_SCAN mode will still trigger unexpected partial scan after the whole SCAN Sequence was completed.
**  \main\maintrunk.MT5921\67 2007-12-11 14:03:51 GMT mtk01088
**  Fixed error while processing deauth frame not release Queue issue
**
**  \main\maintrunk.MT5921\66 2007-12-11 00:09:50 GMT mtk01461
**  Add Disassoc/Deauth Event handler, Fix Disconnect Indication Timing, Fix TX flush after Disconnect.
**  \main\maintrunk.MT5921\65 2007-12-07 17:40:43 GMT mtk01084
**  not to do clock on/ off during ARB state transition
**  \main\maintrunk.MT5921\64 2007-12-07 11:26:36 GMT mtk01084
**  disable RX filter about DIFF_BSSID beacon and probe response
**  \main\maintrunk.MT5921\63 2007-12-04 18:09:21 GMT mtk01461
**  Update MSDU_INFO_T init process & Scan Stop
**  \main\maintrunk.MT5921\62 2007-11-30 19:45:03 GMT mtk01084
**  invoke pmFsmAbort on arbFsmAbort
**  \main\maintrunk.MT5921\61 2007-11-30 16:43:10 GMT mtk01425
**  1. Fix bugs an warnings
**  \main\maintrunk.MT5921\60 2007-11-29 20:35:31 GMT mtk01385
**  1. skip low power own back when in RF test mode.
**  \main\maintrunk.MT5921\59 2007-11-29 18:19:55 GMT mtk01461
**  Fix arbFsmRunEventAbort() eNextState to STANDBY
**  \main\maintrunk.MT5921\58 2007-11-27 19:56:28 GMT mtk01084
**  add arbUnInit() function
**  \main\maintrunk.MT5921\57 2007-11-27 17:48:57 GMT mtk01084
**  turn clock on/ off during transition from idle/ scan, standby/ idle
**  \main\maintrunk.MT5921\56 2007-11-26 22:09:10 GMT mtk01385
**  1. When os call set/query 802.11 configuration, return success directly. but need to implement detail later.
**  \main\maintrunk.MT5921\55 2007-11-26 21:45:38 GMT mtk01385
**  1. add statistics init.
**  2. fix compiling warning.
**  \main\maintrunk.MT5921\54 2007-11-26 19:38:37 GMT mtk01461
**  Unify SCAN
**  \main\maintrunk.MT5921\53 2007-11-22 22:27:05 GMT mtk01084
**  change parameter to send NULL
**  \main\maintrunk.MT5921\52 2007-11-21 11:41:57 GMT mtk01084
**  fix Linux compiler warning
**  \main\maintrunk.MT5921\51 2007-11-20 19:04:06 GMT mtk01084
**  change function name
**  \main\maintrunk.MT5921\50 2007-11-19 11:38:21 GMT mtk01084
**  move VoIP timer setup from PM module to ARB
**  \main\maintrunk.MT5921\49 2007-11-17 15:15:30 GMT mtk01385
**  1. add Rf test mode related functions.
**  \main\maintrunk.MT5921\48 2007-11-15 11:18:47 GMT mtk01088
**  move the enable globale int to arb reset to stanby transition
**  \main\maintrunk.MT5921\47 2007-11-13 18:22:55 GMT mtk01084
**  clear the variable to indicate it is connected with AP but no beacon is received
**  \main\maintrunk.MT5921\46 2007-11-12 20:37:15 GMT mtk01084
**  modify function name pmFsmRunEventOnDisconnectt(prAdapter) to pmFsmRunEventAbort(prAdapter)
**
**
**  \main\maintrunk.MT5921\45 2007-11-12 16:16:05 GMT mtk01084
**  modify scan dwell time length from 16 bit to 8 bit
**  \main\maintrunk.MT5921\44 2007-11-09 12:47:44 GMT mtk01084
**  modify parameters in pmFsmRunEventEnterPowerSaveModeDecision()
**  \main\maintrunk.MT5921\43 2007-11-07 18:36:46 GMT mtk01461
**  Update TX
**  \main\maintrunk.MT5921\42 2007-11-06 20:21:35 GMT mtk01088
**  move the pre-auth indicate
**  \main\maintrunk.MT5921\41 2007-11-05 17:00:55 GMT mtk01425
**  1. Modify for chip reset
**  \main\maintrunk.MT5921\40 2007-11-02 00:57:07 GMT mtk01461
**  Unify TX Path for Normal and IBSS Power Save + IBSS neighbor learning
**  \main\maintrunk.MT5921\39 2007-11-01 14:45:26 GMT mtk01084
**  modify variable naming of the u4ScanDwellTimeMax to u4ScanDwellTimeExt
**  \main\maintrunk.MT5921\38 2007-10-30 20:12:24 GMT mtk01084
**  fix compiling errors
**  \main\maintrunk.MT5921\37 2007-10-30 19:26:21 GMT mtk01084
**  modify lines to create IBSS
**  \main\maintrunk.MT5921\36 2007-10-30 10:07:15 GMT mtk01425
**  1. Refine for reset
**  \main\maintrunk.MT5921\35 2007-10-29 10:02:37 GMT mtk01084
**  support BG SSID Scan
**  \main\maintrunk.MT5921\34 2007-10-26 19:22:37 GMT mtk01084
**  modify scan related variable naming
**  \main\maintrunk.MT5921\33 2007-10-26 09:27:51 GMT mtk01084
**  add BG SSID scan handlers
**  \main\maintrunk.MT5921\32 2007-10-26 09:26:11 GMT mtk01084
**  add BG SSiD scan related functions
**  \main\maintrunk.MT5921\31 2007-10-25 18:05:07 GMT mtk01461
**  Add VOIP SCAN Support  & Refine Roaming
** Revision 1.17  2007/07/16 02:41:28  MTK01088
** remove non-used code
**
** Revision 1.16  2007/07/13 05:17:00  MTK01084
** modify function pointer typedef
**
** Revision 1.15  2007/07/12 06:18:48  MTK01084
** update IST routines to meet PM related requirements
**
** Revision 1.14  2007/07/11 07:29:03  MTK01084
** place PM timer callback event in ARB
**
** Revision 1.13  2007/07/09 07:36:16  MTK01084
** temporarily check-in scan/PM part of lines
**
** Revision 1.12  2007/07/09 06:37:40  MTK01088
** update the function related with security fsm
**
** Revision 1.11  2007/07/05 07:25:32  MTK01461
** Add Linux initial code, modify doc, add 11BB, RF init code
**
** Revision 1.10  2007/07/04 12:50:37  MTK01088
** modify the ENUM define
**
** Revision 1.9  2007/07/04 10:15:39  MTK01088
** change the function for sec fsm
**
** Revision 1.8  2007/07/03 08:22:02  MTK01088
** remove the sec related state from arb fsm
** add the port control, add key, counter measure event for security module
**
** Revision 1.7  2007/06/29 12:11:52  MTK01088
** fixed the compilg error
**
** Revision 1.6  2007/06/27 12:35:39  MTK01088
** add the PTK installed event for arb (use this to trigger the sec fsm)
** adjust sec related code
**
** Revision 1.5  2007/06/27 06:02:51  MTK01088
** add the arb sec check state and event for sec check
**
** Revision 1.4  2007/06/27 02:18:29  MTK01461
** Update SCAN_FSM, Initial(Can Load Module), Proc(Can do Reg R/W), TX API
**
** Revision 1.3  2007/06/26 08:38:14  MTK01084
** add two function to acquire/ restore LP control
**
** Revision 1.2  2007/06/25 06:16:23  MTK01461
** Update illustrations, gl_init.c, gl_kal.c, gl_kal.h, gl_os.h and RX API
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
/* Static convert the Priority Parameter(User Priority/TS Identifier) to Traffic Class */
extern const UINT_8 aucPriorityParam2TC[];

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
#if DBG
/*lint -save -e64 Type mismatch */
static PUINT_8 apucDebugArbState[ARB_STATE_NUM] = {
    DISP_STRING("ARB_STATE_POWER_OFF"),
    DISP_STRING("ARB_STATE_RESET"),
    DISP_STRING("ARB_STATE_RF_TEST"),
    DISP_STRING("ARB_STATE_STANDBY"),
    DISP_STRING("ARB_STATE_IDLE"),
    DISP_STRING("ARB_STATE_SEARCH"),
    DISP_STRING("ARB_STATE_BG_SSID_SCAN"),
    DISP_STRING("ARB_STATE_JOIN"),
    DISP_STRING("ARB_STATE_IBSS_ALONE"),
    DISP_STRING("ARB_STATE_IBSS_MERGE"),
    DISP_STRING("ARB_STATE_NORMAL_TR"),
    DISP_STRING("ARB_STATE_SCAN"),
    DISP_STRING("ARB_STATE_DEDICATED_MEASUREMEMT"),
};

static PUINT_8 apucDebugOpMode[OP_MODE_NUM] = {
    DISP_STRING("OP_MODE_INFRASTRUCTURE"),
    DISP_STRING("OP_MODE_IBSS"),
    DISP_STRING("OP_MODE_RESERVED"),
};
/*lint -restore */
#endif /* DBG */

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
#if CFG_SDIO_DEVICE_DRIVER_WO_NDIS
/*----------------------------------------------------------------------------*/
/*!
* \brief This function will do initialization of Arbiter FSM and all variables in
*        ARB_INFO_T.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
* \param[in] prRegInfo  Pointer to the Registry structure from Glue Layer.
*
* \retval WLAN_STATUS_SUCCESS   Successful initiailization.
* \retval WLAN_STATUS_FAILURE   Card was not found.
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
arbFsmInit (
    IN P_ADAPTER_T prAdapter
    )
{
    P_ARB_INFO_T prArbInfo;
    WLAN_STATUS u4Status = WLAN_STATUS_SUCCESS;
    P_CONNECTION_SETTINGS_T prConnSettings;

    DEBUGFUNC("arbFsmInit");


    ASSERT(prAdapter);

    prArbInfo = &prAdapter->rArbInfo;
    prConnSettings = &prAdapter->rConnSettings;

    prArbInfo->ePreviousState = ARB_STATE_POWER_OFF;
    prArbInfo->eCurrentState  = ARB_STATE_POWER_OFF;

    prArbInfo->fgTestMode = TRUE;
    prArbInfo->fgTryFullScan = FALSE;

    prArbInfo->prTargetBssDesc = (P_BSS_DESC_T)NULL;

    do {

        //4 <1> Load default value of Connection Settings.
        nicInitializeConnectionSettings(prAdapter);

        //4 <2> Try to read previous or default configurations
        if ( (u4Status = nicReadConfig(prAdapter, FALSE)) != WLAN_STATUS_SUCCESS ) {
            DBGLOG(INIT, ERROR, ("nicReadConfig Error!\n"));
            u4Status = WLAN_STATUS_FAILURE;
            break;
        }

        // TODO: frog
        /* We are not read any configuration from registry. */
        //4 <3> Apply registry default setting

        //4 <4> Try to allocate Host Memory
        if ( (u4Status = nicAllocateAdapterMemory(prAdapter)) != WLAN_STATUS_SUCCESS ) {
            DBGLOG(INIT, ERROR, ("nicAllocateAdapterMemory Error!\n"));
            u4Status = WLAN_STATUS_FAILURE;
            break;
        }

        // TODO: frog
        /* We don't need scan, also we don't have BSS cache. */
        //4 <5> Initialize BSS Descriptor List


        //4 <5> Set the default packet filter used by OS
        prAdapter->u4OsPacketFilter = PARAM_PACKET_FILTER_SUPPORTED;

        //4 <6> Set supported channel list (by the country code)
#if CFG_SUPPORT_802_11D
        if (prConnSettings->fgMultiDomainCapabilityEnabled) {
            nicSetupOpChnlList(prAdapter, COUNTRY_CODE_NULL, TRUE);
        }
        else {
            nicSetupOpChnlList(prAdapter, prConnSettings->u2CountryCode, TRUE);
        }
#else
        nicSetupOpChnlList(prAdapter, prConnSettings->u2CountryCode, TRUE);
#endif /* CFG_SUPPORT_802_11D */

    }
    while (FALSE);

    return u4Status;

} /* end of arbFsmInit() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will do un-initialization of Arbiter FSM.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
arbFsmUnInit (
    P_ADAPTER_T prAdapter
    )
{
    ASSERT(prAdapter);

    //4 <1> Abort any WLAN Activity.
    prAdapter->rConnSettings.fgIsConnReqIssued = FALSE;
    arbFsmRunEventAbort(prAdapter, FALSE);
    /* Uninit RFTest */
    rftestUnInit(prAdapter);

    //4 <2> Disable Thermo Function(Timer).
    nicThermoUnInit(prAdapter);

    //4 <3> Disable Statistics Function(Timer).
    statisticsUnInit(prAdapter);

    //4 <4> Disable Root Timer.
    timerUnInitialize(prAdapter);

    //4 <5> Unregister VOIP Timer.
    nichtCancelTimer(prAdapter, VOIP_POLL_TIMER);

    //4 <6> Power Off.
    pmFsmUnInit(prAdapter);

    return;
} /* end of arbFsmUnInit() */

/*----------------------------------------------------------------------------*/
/*!
* \brief This function will do action part while in STATE transition of
*        RESET to STANDBY.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ VOID
arbFsmTransAction_RESET_to_STANDBY (
    IN P_ADAPTER_T prAdapter
    )
{
    P_CONNECTION_SETTINGS_T prConnSettings;

    ASSERT(prAdapter);
    prConnSettings = &prAdapter->rConnSettings;

    //4 <0> Initialize the Adapter
    nicInitializeAdapter(prAdapter);

    //4 <1> Initialize Tx
    nicTxInitialize(prAdapter);

    //4 <2> Initialize Rx
    nicRxInitialize(prAdapter);

    //4 <3> Initialize Management Frame Buffer

    //4 <4> Initialize STA Record List
    staRecInitialize(prAdapter);

    //4 <5> Initialize BSS Descriptor List

    //4 <6> Initialize Timer List
    timerInitialize(prAdapter, arbFsmRunEventRootTimerHandler);

    //4 <7> Initialize chip(MAC/BB/RF), setup hardware according to the software setting in nicInitializeAdapter().
    nicInitializeChip(prAdapter);

    //4 <8> Initialize default channel to operational channel index 0
    nicSwitchChannel(prAdapter,
                     prAdapter->arNicOpChnList[0].eBand,
                     prAdapter->arNicOpChnList[0].ucChannelNum,
                     CFG_INIT_TX_POWER_LIMIT);

    //4 <9> Initialize each module's FSM.

    //4 <10> Initialize roaming FSM.

    //4 <11> Initialize PM FSM.

    //4 <12> Initialize scan FSM.

    //4 <13> Initialize security FSM.

    /* Renbang (20100120): move setting of GPIO1 to nicInitializeChip, in case of re-setting */
    //4 <10> Set GPIO1 based on EEPROM.
    //nicSetGPIO1Mode(prAdapter);

    //4 <11> Set PTA.
    
    /* Renbang (20100120): move setting of GPIO1 to nicInitializeChip, in case of re-setting */
    //4 <12> Set GPIO2 according to Connection Setting.
    //nicSetGPIO2Mode(prAdapter, prConnSettings->eGPIO2_Mode);

    //4 <13> Init Statistics Function.
    statisticsInit(prAdapter);

    //4 <14> Init Thermo Function.
    nicThermoInit(prAdapter);

    //4 <15> Register VOIP Timer(use HW timer).

    //4 <15.5> Initial a timer for TX test.
    ARB_INIT_TIMER(prAdapter,
           prAdapter->rTxCtrl.rPktTxIntervalTimer,
           arbFsmRunEventPacketTxIntervalTimeOut,
           TRUE);


    //4 <16> Enable Global Interrupt.
    nicEnableInterrupt(prAdapter);

    return;
} /* end of arbFsmTransAction_RESET_to_STANDBY() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will indicate an Event of "IBSS ALONE Time-Out" to ARB FSM.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
arbFsmRunEventPacketTxIntervalTimeOut (
    IN P_ADAPTER_T prAdapter
    )
{
    P_RFTEST_INFO_T prRFATInfo;

    ASSERT(prAdapter);
    prRFATInfo = &prAdapter->rRFTestInfo;

    if (prRFATInfo->eCurrentState == RF_AUTOTEST_STATE_TX) {
        rftestTx(prAdapter);
    }
    return;
} /* end of arbFsmRunEventPacketTxIntervalTimeOut() */

#else
/*----------------------------------------------------------------------------*/
/*!
* \brief This function will do initialization of Arbiter FSM and all variables in
*        ARB_INFO_T.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
* \param[in] prRegInfo  Pointer to the Registry structure from Glue Layer.
*
* \retval WLAN_STATUS_SUCCESS   Successful initiailization.
* \retval WLAN_STATUS_FAILURE   Card was not found.
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
arbFsmInit (
    IN P_ADAPTER_T prAdapter,
    IN P_REG_INFO_T prRegInfo
    )
{
    P_ARB_INFO_T prArbInfo;
    WLAN_STATUS u4Status = WLAN_STATUS_SUCCESS;
    P_CONNECTION_SETTINGS_T prConnSettings;

    DEBUGFUNC("arbFsmInit");


    ASSERT(prAdapter);

    prArbInfo = &prAdapter->rArbInfo;
    prConnSettings = &prAdapter->rConnSettings;

    prArbInfo->ePreviousState = ARB_STATE_POWER_OFF;
    prArbInfo->eCurrentState  = ARB_STATE_POWER_OFF;

    prArbInfo->fgTestMode = FALSE;
    prArbInfo->fgTryFullScan = FALSE;

    prArbInfo->prTargetBssDesc = (P_BSS_DESC_T)NULL;

    ARB_INIT_TIMER(prAdapter,
                   prArbInfo->rIbssAloneTimer,
                   arbFsmRunEventIbssAloneTimeOut,
                   TRUE);

    ARB_INIT_TIMER(prAdapter,
                   prArbInfo->rIndicationOfDisconnectTimer,
                   arbFsmRunEventIndicationOfDisconnectTimeOut,
                   TRUE);

    ARB_INIT_TIMER(prAdapter,
                   prArbInfo->rProtectionTimerForAdHoc,
                   arbFsmRunEventIbssProtectionTimeOut,
                   TRUE);


    do {

        //4 <1> Load default value of Connection Settings.
        nicInitializeConnectionSettings(prAdapter);

        //4 <2> Try to read previous or default configurations
        if ( (u4Status = nicReadConfig(prAdapter, FALSE)) != WLAN_STATUS_SUCCESS ) {
            DBGLOG(INIT, ERROR, ("nicReadConfig Error!\n"));
            u4Status = WLAN_STATUS_FAILURE;
            break;
        }
        /* If EEPROM is not present or checksum error, enter test mode
         * to avoid normal operation. So we can know something wrong.
         */
        if (prAdapter->rEEPROMCtrl.fgIsEepromValid == FALSE) {
            prArbInfo->fgTestMode = TRUE;
        }

        //4 <3> Apply registry default setting
        nicSetConnectionSettingsByGlueParam(prAdapter, prRegInfo);

        //4 <4> Try to allocate Host Memory
        if ( (u4Status = nicAllocateAdapterMemory(prAdapter)) != WLAN_STATUS_SUCCESS ) {
            DBGLOG(INIT, ERROR, ("nicAllocateAdapterMemory Error!\n"));
            u4Status = WLAN_STATUS_FAILURE;
            break;
        }

        //4 <5> Initialize BSS Descriptor List
        scanInitialize(prAdapter);

        //4 <5> Set the default packet filter used by OS
        prAdapter->u4OsPacketFilter = PARAM_PACKET_FILTER_SUPPORTED;

        //4 <6> Set supported channel list (by the country code)
#if CFG_SUPPORT_802_11D
        if (prConnSettings->fgMultiDomainCapabilityEnabled) {
            nicSetupOpChnlList(prAdapter, COUNTRY_CODE_NULL, TRUE);
        }
        else {
            nicSetupOpChnlList(prAdapter, prConnSettings->u2CountryCode, TRUE);
        }
#else
        nicSetupOpChnlList(prAdapter, prConnSettings->u2CountryCode, TRUE);
#endif /* CFG_SUPPORT_802_11D */

    }
    while (FALSE);

    return u4Status;

} /* end of arbFsmInit() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will do un-initialization of Arbiter FSM.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
arbFsmUnInit (
    P_ADAPTER_T prAdapter
    )
{
    ASSERT(prAdapter);

    //4 <1> Abort any WLAN Activity.
    prAdapter->rConnSettings.fgIsConnReqIssued = FALSE;
    arbFsmRunEventAbort(prAdapter, FALSE);
    /* Uninit RFTest */
    rftestUnInit(prAdapter);

    //4 <2> Disable Thermo Function(Timer).
    nicThermoUnInit(prAdapter);

    //4 <3> Disable Statistics Function(Timer).
    statisticsUnInit(prAdapter);

    //4 <4> Disable Root Timer.
    timerUnInitialize(prAdapter);

    //4 <5> Unregister VOIP Timer.
    nichtCancelTimer(prAdapter, VOIP_POLL_TIMER);

    //4 <6> Power Off.
    pmFsmUnInit(prAdapter);

    return;
} /* end of arbFsmUnInit() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will do action part while in STATE transition of
*        RESET to STANDBY.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ VOID
arbFsmTransAction_RESET_to_STANDBY (
    IN P_ADAPTER_T prAdapter
    )
{
    P_CONNECTION_SETTINGS_T prConnSettings;

    ASSERT(prAdapter);
    prConnSettings = &prAdapter->rConnSettings;

    //4 <0> Initialize the Adapter
    nicInitializeAdapter(prAdapter);

    //4 <1> Initialize Tx
    nicTxInitialize(prAdapter);

    //4 <2> Initialize Rx
    nicRxInitialize(prAdapter);

    //4 <3> Initialize Management Frame Buffer
    mgtBufInitialize(prAdapter);

    //4 <4> Initialize STA Record List
    staRecInitialize(prAdapter);

    //4 <5> Initialize BSS Descriptor List
    /* NOTE: Adjust the code for D3 back to D0 path, for CETK one_card 12,13 issue.
     * Keep the scan result, let the D3->D0 path can use the old record.
     */
    //scanInitialize(prAdapter);

    //4 <6> Initialize Timer List
    timerInitialize(prAdapter, arbFsmRunEventRootTimerHandler);

    //4 <7> Initialize chip(MAC/BB/RF), setup hardware according to the software setting in nicInitializeAdapter().
    nicInitializeChip(prAdapter);

    //4 <8> Initialize default channel to operational channel index 0
    nicSwitchChannel(prAdapter,
                     prAdapter->arNicOpChnList[0].eBand,
                     prAdapter->arNicOpChnList[0].ucChannelNum,
                     CFG_INIT_TX_POWER_LIMIT);

    //4 <9> Initialize each module's FSM.
    joinFsmInit(prAdapter);

    roamingFsmInit(prAdapter);

    /* If calibration of slow clock fails, enter test mode
     * to avoid normal operation. So we can know something wrong.
     */
    if (!pmFsmInit(prAdapter)) {
        prAdapter->rArbInfo.fgTestMode = TRUE;
    }

    scanFsmInit(prAdapter);

    secFsmInit(prAdapter);
    
    /* Renbang (20100120): move setting of GPIO1 to nicInitializeChip, in case of re-setting */
    //4 <10> Set GPIO1 based on EEPROM.
    //nicSetGPIO1Mode(prAdapter);
    
    /* Renbang (20100120): move setting of GPIO1 to nicInitializeChip, in case of re-setting */
    //4 <11> Set GPIO2 according to Connection Setting.
    //nicSetGPIO2Mode(prAdapter, prConnSettings->eGPIO2_Mode);

    //4 <12> Init Statistics Function.
    statisticsInit(prAdapter);

    //4 <13> Init Thermo Function.
    nicThermoInit(prAdapter);

    //4 <14> Register VOIP Timer(use HW timer).
    nichtTimerInit(prAdapter, VOIP_POLL_TIMER, arbFsmRunEventTimeupVoipInterval);

#if PTA_ENABLED
    //4 <15> Init PTA function
    /* Invoke this function as the last one, in which the single antenna
     * setting will be restored to HW control
     */
    ptaFsmInit(prAdapter);

#if CFG_TX_FRAGMENT
    /* Judge if TX auto-fragment is applied for BT-coexist after
     * ptaFsmRunEventSetConfig() or ptaFsmInit() is invoked
     */
    prConnSettings->fgIsEnableTxAutoFragmentForBT =
            (prConnSettings->fgIsEnableTxFragment &&
             prAdapter->rPtaInfo.eCurrentState == PTA_STATE_ON) ?
            prConnSettings->fgTryTxAutoFragmentForBT : FALSE;
#endif
#endif /* end of PTA_ENABLED */

    //4 <16> Enable Global Interrupt.
    nicEnableInterrupt(prAdapter);

    return;
} /* end of arbFsmTransAction_RESET_to_STANDBY() */


#endif /* CFG_SDIO_DEVICE_DRIVER_WO_NDIS */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will do action part while in STATE transition of
*        STANDBY to RF_TEST.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ VOID
arbFsmTransAction_STANDBY_to_RF_TEST (
    IN P_ADAPTER_T prAdapter
    )
{
    ASSERT(prAdapter);

    return;
} /* end of arbFsmTransAction_STANDBY_to_RF_TEST() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will do action part while in STATE transition of
*        STANDBY to IDLE.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ VOID
arbFsmTransAction_STANDBY_to_IDLE (
    IN P_ADAPTER_T prAdapter
    )
{
    ASSERT(prAdapter);
	
    //Renbang (20100417) : when enter IDLE, set prefer ant to BT 
    //<0>set prefer ant to BT
    if (prAdapter->rPtaInfo.fgSingleAntenna) {
#if PTA_NEW_BOARD_DESIGN		
        nicPtaSetAnt(prAdapter, FALSE);    
#endif
    }

    /* NOTE:
       There's no clock control here due to clock control is done in OS entry and exit.
       (e.g. ARB_RECLAIM_POWER_CONTROL_TO_PM/ARB_ACQUIRE_POWER_CONTROL_FROM_PM)
       Now it is assumed that clock is keeping consistent whether how the ARB state
       transition. The only exception is RESET function, it will always try to let
       system clock ON for subsequent processing.
    */
#if 0
    nicpmPowerOff(prAdapter);
#endif

    //4 <1> Do not receive any packets.
    nicRxFlushStopQueue(prAdapter, TRUE, TRUE);

    //4 <2> Release pending TX frames.
    nicTxRelease(prAdapter);

    /* NOTE: Not to clear the scan result while enter IDLE
     * Keep the scan result and let the driver can choose the AP
     * meet the connection setting, for cetk one_card 12,13 test item
     */
    //scanRemoveBssDescsByPolicy(prAdapter, SCAN_RM_POLICY_ENTIRE);

    //4 <3> Disabled the ALC function
    DBGLOG(NIC, TRACE, ("Disable ALC\n"));
    NIC_ALC_DISABLE(prAdapter);

    return;
} /* end of arbFsmTransAction_STANDBY_to_IDLE() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will do action part while in STATE transition of
*        STANDBY to SCAN.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ VOID
arbFsmTransAction_STANDBY_to_SCAN (
    IN P_ADAPTER_T prAdapter
    )
{
    ASSERT(prAdapter);

    nicRxAcquirePrivilegeOfRxQue(prAdapter,
                                 (BOOLEAN)TRUE,
                                 (BOOLEAN)FALSE,
                                 (BOOLEAN)FALSE);

    nicTxAcquirePrivilegeOfTxQue(prAdapter,
                                 0x0, /*(UINT_8)NULL*/
                                 (UINT_8)TXQ_ALL_MASK,
                                 (UINT_8)TXQ_MGMT_MASK);

    return;
} /* end of arbFsmTransAction_STANDBY_to_SCAN() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will do action part while in STATE transition of
*        STANDBY to SEARCH.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ VOID
arbFsmTransAction_STANDBY_to_SEARCH (
    IN P_ADAPTER_T prAdapter
    )
{
    P_ARB_INFO_T prArbInfo;

    ASSERT(prAdapter);
    prArbInfo = &prAdapter->rArbInfo;

    prArbInfo->fgTryFullScan = TRUE;

    return;
} /* end of arbFsmTransAction_STANDBY_to_SEARCH() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will do action part while in STATE transition of
*        STANDBY to POWER_OFF.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ VOID
arbFsmTransAction_STANDBY_to_POWER_OFF (
    IN P_ADAPTER_T prAdapter
    )
{
    ASSERT(prAdapter);

    return;
} /* end of arbFsmTransAction_STANDBY_to_POWER_OFF() */

/*----------------------------------------------------------------------------*/
/*!
* \brief This function will do action part while in STATE transition of
*        IDLE to STANDBY.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ VOID
arbFsmTransAction_IDLE_to_STANDBY (
    IN P_ADAPTER_T prAdapter
    )
{
    ASSERT(prAdapter);

    /* NOTE:
       There's no clock control here due to clock control is done in OS entry and exit.
       (e.g. ARB_RECLAIM_POWER_CONTROL_TO_PM/ARB_ACQUIRE_POWER_CONTROL_FROM_PM)
       Now it is assumed that clock is keeping consistent whether how the ARB state
       transition. The only exception is RESET function, it will always try to let
       system clock ON for subsequent processing.
    */
#if 0
    nicpmPowerOn(prAdapter);
#endif

    nicEnableInterrupt(prAdapter);

    //Renbang (20100417) : when qiut from IDLE, set prefer ant to WiFi 
    //<0>set prefer ant to WiFi
    if (prAdapter->rPtaInfo.fgSingleAntenna) {
#if PTA_NEW_BOARD_DESIGN		
        nicPtaSetAnt(prAdapter, TRUE);    
#endif
    }

    return;
} /* end of arbFsmTransAction_IDLE_to_STANDBY() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will do action part while in STATE transition of
*        SEARCH to BG_SSID_SCAN.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ VOID
arbFsmTransAction_SEARCH_to_BG_SSID_SCAN (
    IN P_ADAPTER_T prAdapter
    )
{
    ASSERT(prAdapter);

    nicRxAcquirePrivilegeOfRxQue(prAdapter,
                                 (BOOLEAN)TRUE,
                                 (BOOLEAN)FALSE,
                                 (BOOLEAN)FALSE);

    nicTxAcquirePrivilegeOfTxQue(prAdapter,
                                 0x0, /*(UINT_8)NULL*/
                                 (UINT_8)TXQ_ALL_MASK,
                                 (UINT_8)TXQ_MGMT_MASK);

    return;
} /* end of arbFsmTransAction_SEARCH_to_BG_SSID_SCAN() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will do action part while in STATE transition of
*        SEARCH to SCAN.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ VOID
arbFsmTransAction_SEARCH_to_SCAN (
    IN P_ADAPTER_T prAdapter
    )
{
    ASSERT(prAdapter);

    nicRxAcquirePrivilegeOfRxQue(prAdapter,
                                 (BOOLEAN)TRUE,
                                 (BOOLEAN)FALSE,
                                 (BOOLEAN)FALSE);

    nicTxAcquirePrivilegeOfTxQue(prAdapter,
                                 0x0, /*(UINT_8)NULL*/
                                 (UINT_8)TXQ_ALL_MASK,
                                 (UINT_8)TXQ_MGMT_MASK);

    return;
} /* end of arbFsmTransAction_SEARCH_to_SCAN() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will do action part while in STATE transition of
*        SEARCH to JOIN.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ VOID
arbFsmTransAction_SEARCH_to_JOIN (
    IN P_ADAPTER_T prAdapter
    )
{
    ASSERT(prAdapter);

    /* TODO(Kevin 2007/03/30): The roaming path is mixed with the normal path
     * so we should stop quiet here.
     */

    return;
} /* end of arbFsmTransAction_SEARCH_to_JOIN() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will do action part while in STATE transition of
*        SEARCH to IBSS_ALONE.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ VOID
arbFsmTransAction_SEARCH_to_IBSS_ALONE (
    IN P_ADAPTER_T prAdapter
    )
{
    ASSERT(prAdapter);

    nicTxStartQueues(prAdapter, TXQ_DATA_MASK | TXQ_MGMT_MASK);
    nicRxStartQueue(prAdapter);

    return;
} /* end of arbFsmTransAction_SEARCH_to_IBSS_ALONE() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will do action part while in STATE transition of
*        SEARCH to IBSS_MERGE.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ VOID
arbFsmTransAction_SEARCH_to_IBSS_MERGE (
    IN P_ADAPTER_T prAdapter
    )
{
    ASSERT(prAdapter);

    nicTxStartQueues(prAdapter, TXQ_DATA_MASK);
    nicRxStartQueue(prAdapter);

    return;
} /* end of arbFsmTransAction_SEARCH_to_IBSS_MERGE() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will do action part while in STATE transition of
*        SEARCH to NORMAL_TR.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ VOID
arbFsmTransAction_SEARCH_to_NORMAL_TR (
    IN P_ADAPTER_T prAdapter
    )
{
    ASSERT(prAdapter);

    return;
} /* end of arbFsmTransAction_SEARCH_to_NORMAL_TR() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will do action part while in STATE transition of
*        IBSS_ALONE to IBSS_MERGE.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ VOID
arbFsmTransAction_IBSS_ALONE_to_IBSS_MERGE (
    IN P_ADAPTER_T prAdapter
    )
{
    ASSERT(prAdapter);

    return;
} /* end of arbFsmTransAction_IBSS_ALONE_to_IBSS_MERGE() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will do action part while in STATE transition of
*        IBSS_ALONE to SEARCH.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ VOID
arbFsmTransAction_IBSS_ALONE_to_SEARCH (
    IN P_ADAPTER_T prAdapter
    )
{
    ASSERT(prAdapter);

    nicTxFlushStopQueues(prAdapter, 0x0 /*(UINT_8)NULL*/, TXQ_DATA_MASK | TXQ_MGMT_MASK);
    nicRxFlushStopQueue(prAdapter, FALSE, TRUE);

    return;
} /* end of arbFsmTransAction_IBSS_ALONE_to_SEARCH() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will do action part while in STATE transition of
*        IBSS_ALONE to SCAN.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ VOID
arbFsmTransAction_IBSS_ALONE_to_SCAN (
    IN P_ADAPTER_T prAdapter
    )
{
    ASSERT(prAdapter);

    nicPauseBeacon(prAdapter);

    nicRxAcquirePrivilegeOfRxQue(prAdapter,
                                 (BOOLEAN)TRUE,
                                 (BOOLEAN)FALSE,
                                 (BOOLEAN)FALSE);

    nicTxAcquirePrivilegeOfTxQue(prAdapter,
                                 0x0, /*(UINT_8)NULL*/
                                 (UINT_8)TXQ_ALL_MASK,
                                 (UINT_8)TXQ_MGMT_MASK);

    return;
} /* end of arbFsmTransAction_IBSS_ALONE_to_SCAN() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will do action part while in STATE transition of
*        IBSS_MERGE to SEARCH.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ VOID
arbFsmTransAction_IBSS_MERGE_to_SEARCH (
    IN P_ADAPTER_T prAdapter
    )
{
    ASSERT(prAdapter);

    return;
} /* end of arbFsmTransAction_IBSS_MERGE_to_SEARCH() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will do action part while in STATE transition of
*        IBSS_MERGE to IBSS_ALONE.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ VOID
arbFsmTransAction_IBSS_MERGE_to_IBSS_ALONE (
    IN P_ADAPTER_T prAdapter
    )
{
    ASSERT(prAdapter);

    return;
} /* end of arbFsmTransAction_IBSS_MERGE_to_IBSS_ALONE() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will do action part while in STATE transition of
*        IBSS_MERGE to NORMAL_TR.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ VOID
arbFsmTransAction_IBSS_MERGE_to_NORMAL_TR (
    IN P_ADAPTER_T prAdapter
    )
{
    P_PM_INFO_T prPmInfo;

    ASSERT(prAdapter);
    prPmInfo = &prAdapter->rPmInfo;

    //4 <1> Get current OS time for recording the connected time with BSS.
    GET_CURRENT_SYSTIME(&prAdapter->rLastConnectedTime);


    //4 <2> Check point for LP Module.
#if 1
    prAdapter->fgBeaconReceivedAfterConnected = FALSE;

    /* Setup a timer to prevent state machine hang due to beacon
       is not able to be received.

       This timer will be canceled when the 1st beacon after connected
       is received.
    */
    ARB_SET_TIMER(prAdapter,
                  prPmInfo->rWaitBeaconWatchdogTimer,
                  WAIT_BEACON_ON_CONNECTED_MSEC);


#else
    /* inidcate PM module for the connection status */
    pmFsmRunEventOnConnect(prAdapter,
                           0, //prBssInfo->u2AssocId,
                           prBssInfo->u2BeaconInterval,
                           0, //prBssInfo->ucDtimPeriod,
                           prBssInfo->u2ATIMWindow);
#endif

    //4 <3> Enable RCPI Moving Average.
    nicRRAverageEnable(prAdapter);

    return;
} /* end of arbFsmTransAction_IBSS_MERGE_to_NORMAL_TR() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will do action part while in STATE transition of
*        NORMAL_TR to SCAN.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ VOID
arbFsmTransAction_NORMAL_TR_to_SCAN (
    IN P_ADAPTER_T prAdapter
    )
{
    P_CONNECTION_SETTINGS_T     prConnSettings;

    ASSERT(prAdapter);

    prConnSettings = &prAdapter->rConnSettings;

    nicRxAcquirePrivilegeOfRxQue(prAdapter,
                                 (BOOLEAN)TRUE,
                                 (BOOLEAN)FALSE,
                                 (BOOLEAN)FALSE);

    nicTxAcquirePrivilegeOfTxQue(prAdapter,
                                 0x0, /*(UINT_8)NULL*/
                                 (UINT_8)TXQ_ALL_MASK,
                                 (UINT_8)TXQ_MGMT_MASK);

    NIC_UNSET_INT_EVENT(prAdapter, INT_EVENT_BEACON_TIMEOUT);
    NIC_UNSET_INT_EVENT(prAdapter, INT_EVENT_RCPI);

    /* Suspend continuous polling function (keep original PS mode),
       for preventing excessive PS-poll (trigger frame) during scan */
    if (prConnSettings->u4ContPollIntv) {
        pmSuspendContinuousPollingFunc(prAdapter);
    }

    return;
} /* end of arbFsmTransAction_NORMAL_TR_to_SCAN() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will do action part while in STATE transition of
*        NORMAL_TR to IBSS_MERGE.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ VOID
arbFsmTransAction_NORMAL_TR_to_IBSS_MERGE (
    IN P_ADAPTER_T prAdapter
    )
{
    ASSERT(prAdapter);

    return;
} /* end of arbFsmTransAction_NORMAL_TR_to_IBSS_MERGE() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will do action part while in STATE transition of
*        NORMAL_TR to SEARCH.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ VOID
arbFsmTransAction_NORMAL_TR_to_SEARCH (
    IN P_ADAPTER_T prAdapter
    )
{
    ASSERT(prAdapter);

    return;
} /* end of arbFsmTransAction_NORMAL_TR_to_SEARCH() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will do action part while in STATE transition of
*        JOIN to SEARCH.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ VOID
arbFsmTransAction_JOIN_to_SEARCH (
    IN P_ADAPTER_T prAdapter
    )
{
    ASSERT(prAdapter);

    return;
} /* end of arbFsmTransAction_JOIN_to_SEARCH() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will do action part while in STATE transition of
*        JOIN to NORMAL_TR.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ VOID
arbFsmTransAction_JOIN_to_NORMAL_TR (
    IN P_ADAPTER_T prAdapter
    )
{
    P_PM_INFO_T prPmInfo;

    ASSERT(prAdapter);
    prPmInfo = &prAdapter->rPmInfo;

    //4 <1> Get current OS time for recording the connected time with BSS.
    GET_CURRENT_SYSTIME(&prAdapter->rLastConnectedTime);

    //4 <2> Check point for LP Module.
    prAdapter->fgBeaconReceivedAfterConnected = FALSE;

    /* Setup a timer to prevent state machine hang due to beacon
       is not able to be received.

       This timer will be canceled when the 1st beacon after connected
       is received.
    */
    ARB_SET_TIMER(prAdapter,
                  prPmInfo->rWaitBeaconWatchdogTimer,
                  WAIT_BEACON_ON_CONNECTED_MSEC);

    prAdapter->fgIsBlockToScan = TRUE;


    //4 <3> Enable RCPI Moving Average.
    nicRRAverageEnable(prAdapter);

    //4 <4> Trigger Roaming FSM.
    if (prAdapter->rConnSettings.fgIsEnableRoaming) {
        WLAN_STATUS rStatus;


        rStatus = roamingFsmRunEventStart(prAdapter);

        /* Assert if we can't start Roaming Module */
        ASSERT(rStatus != WLAN_STATUS_FAILURE);

        /* Assert if Roaming Module request to find a candidate */
        ASSERT(rStatus != WLAN_STATUS_ROAM_OUT_FIND_BEST);

        /* Assert if Roaming Module request to SCAN immediately */
        ASSERT(rStatus != WLAN_STATUS_ROAM_DISCOVERY);
    }

#if CFG_PEEK_RCPI_VALUE_PERIOD_SEC
    {
        ARB_SET_TIMER(prAdapter,
                      prAdapter->rRcpiDiagnostic,
                      SEC_TO_MSEC(CFG_PEEK_RCPI_VALUE_PERIOD_SEC));
    }
#endif /* CFG_PEEK_RCPI_VALUE_PERIOD_SEC */

#if CFG_LP_IOT
    NIC_SET_INT_EVENT(prAdapter, INT_EVENT_RCPI);
    HAL_MCR_WR(prAdapter, MCR_RR, 0);
    HAL_MCR_WR(prAdapter, MCR_RR, RR_ENABLE_MA/* | RR_RCPI_HIGH_THRESHOLD_MASK*/);
    DBGLOG(LP_IOT, INFO, ("[LP-IOT] Init MCR_RR: 0x%x\n", RR_ENABLE_MA ));
#endif /* CFG_LP_IOT */

#if (CFG_DBG_BEACON_RCPI_MEASUREMENT || CFG_LP_PATTERN_SEARCH_SLT)
    /* Clear the RSSI and link quality records. */
    rxRssiClearRssiLinkQualityRecords(prAdapter);
#endif /* (CFG_DBG_BEACON_RCPI_MEASUREMENT || CFG_LP_PATTERN_SEARCH_SLT) */

    return;
} /* end of arbFsmTransAction_JOIN_to_NORMAL_TR() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will do action part while in STATE transition of
*        SCAN to NORMAL_TR.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ VOID
arbFsmTransAction_SCAN_to_NORMAL_TR (
    IN P_ADAPTER_T prAdapter
    )
{
    P_CONNECTION_SETTINGS_T     prConnSettings;

    ASSERT(prAdapter);

    prConnSettings = &prAdapter->rConnSettings;

    nicRxReleasePrivilegeOfRxQue(prAdapter,
                                 FALSE,
                                 FALSE);

    nicTxReleasePrivilegeOfTxQue(prAdapter,
                                 (UINT_8)TXQ_MGMT_MASK);


    NIC_SET_INT_EVENT(prAdapter, INT_EVENT_BEACON_TIMEOUT);
    NIC_SET_INT_EVENT(prAdapter, INT_EVENT_RCPI);

    /* Resume continuous polling function (on switching from scan to normal TR) */
    if (prConnSettings->u4ContPollIntv) {
        pmResumeContinuousPollingFunc(prAdapter);
    }

    return;
} /* end of arbFsmTransAction_SCAN_to_NORMAL_TR() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will do action part while in STATE transition of
*        SCAN to IBSS_ALONE.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ VOID
arbFsmTransAction_SCAN_to_IBSS_ALONE (
    IN P_ADAPTER_T prAdapter
    )
{
    ASSERT(prAdapter);

    nicRxReleasePrivilegeOfRxQue(prAdapter,
                                 FALSE,
                                 FALSE);

    nicTxReleasePrivilegeOfTxQue(prAdapter,
                                 (UINT_8)TXQ_MGMT_MASK);

    nicResumeBeacon(prAdapter);

    return;
} /* end of arbFsmTransAction_SCAN_to_IBSS_ALONE() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will do action part while in STATE transition of
*        SCAN to SEARCH.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ VOID
arbFsmTransAction_SCAN_to_SEARCH (
    IN P_ADAPTER_T prAdapter
    )
{
    ASSERT(prAdapter);

    nicRxReleasePrivilegeOfRxQue(prAdapter,
                                 FALSE,
                                 FALSE);

    nicTxReleasePrivilegeOfTxQue(prAdapter,
                                 (UINT_8)TXQ_MGMT_MASK);

    return;
} /* end of arbFsmTransAction_SCAN_to_SEARCH() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will do action part while in STATE transition of
*        SCAN to STANDBY.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ VOID
arbFsmTransAction_SCAN_to_STANDBY (
    IN P_ADAPTER_T prAdapter
    )
{
    ASSERT(prAdapter);

    nicRxReleasePrivilegeOfRxQue(prAdapter,
                                 FALSE,
                                 FALSE);

    nicTxReleasePrivilegeOfTxQue(prAdapter,
                                 (UINT_8)TXQ_MGMT_MASK);

    return;
} /* end of arbFsmTransAction_SCAN_to_STANDBY() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will do action part while in STATE transition of
*        BG_SSID_SCAN to SEARCH.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ VOID
arbFsmTransAction_BG_SSID_SCAN_to_SEARCH (
    IN P_ADAPTER_T prAdapter
    )
{
    ASSERT(prAdapter);

    nicRxReleasePrivilegeOfRxQue(prAdapter,
                                 FALSE,
                                 FALSE);

    nicTxReleasePrivilegeOfTxQue(prAdapter,
                                 (UINT_8)TXQ_MGMT_MASK);

    /* this two RX filter is enabled during BG SSID scan state */
    NIC_UNSET_RX_FILTER(prAdapter, RXFILTER_RXDIFFBSSIDPRORESP);
    NIC_UNSET_RX_FILTER(prAdapter, RXFILTER_RXDIFFBSSIDBCN);

    scanFsmRunEventScanAbort(prAdapter);

    //resetLogicReset(prAdapter);

    return;
} /* end of arbFsmTransAction_BG_SSID_SCAN_to_SEARCH() */

#if CFG_SDIO_DEVICE_DRIVER_WO_NDIS
/*----------------------------------------------------------------------------*/
/*!
* \brief The Core FSM engine of ARB(Arbiter).
*
* \param[in] prAdapter  Pointer to the Adapter structure.
* \param[in] eNextState Enum value of next ARB STATE
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
arbFsmSteps (
    P_ADAPTER_T prAdapter,
    ENUM_ARB_STATE_T eNextState
    )
{
    P_ARB_INFO_T prArbInfo;
    BOOLEAN fgIsTransition = (BOOLEAN)FALSE;

    DEBUGFUNC("arbFsmSteps");

    ASSERT(prAdapter);
    prArbInfo = &prAdapter->rArbInfo;

    do {
        /* Do entering Next State */
        prArbInfo->ePreviousState = prArbInfo->eCurrentState;
        DBGLOG(ARB, STATE, ("\nTRANSITION: [%s] -> [%s]\n\n",
                            apucDebugArbState[prArbInfo->eCurrentState],
                            apucDebugArbState[eNextState]));

        /* NOTE(Kevin): This is the only place to change the eCurrentState(except initial) */
        prArbInfo->eCurrentState = eNextState;

        fgIsTransition = (BOOLEAN)FALSE;

        /* Do tasks of the State that we just entered */
        switch (prArbInfo->eCurrentState) {
        case ARB_STATE_POWER_OFF:
            {
                prAdapter->fgIsRadioOff = TRUE;
#if 0
                /* Clear all interrupt status with disabling GINT */
                nicChipReset(prAdapter);
#endif
                /* Not allow interrupt to be trigger during idle state,
                   whenever clock is turned off */
                nicDisableInterrupt(prAdapter);

                nicpmPowerOff(prAdapter);
            }
            break;
        case ARB_STATE_RESET:
            {
                /* Note:
                   Move the HW reset before SW reset. If the order is reversed, SW may check few bits failed
                   on the abortion function.
                   (ex: if clock is off during HW scan is enable, the scan_busy bit will be asserted always,
                        and it is unable for SW to abort scan. In this case, SW assertion will be arised)
                */

                /* HW reset */
                nicChipReset(prAdapter);

                /* SW modules reset */
                nicTxRelease(prAdapter);

                nicRxUninitialize(prAdapter);

                prArbInfo->fgTestMode = TRUE;

                ARB_STATE_TRANSITION(prAdapter, RESET, STANDBY);
            }
            break;
        case ARB_STATE_STANDBY:
            {
                /* Disable all processes */

                prArbInfo->fgIsDiagnosingConnection = FALSE;

                prAdapter->fgIsRadioOff = FALSE;

                if (prAdapter->fgIsEnterD3ReqIssued) {
                    ARB_STATE_TRANSITION(prAdapter, STANDBY, POWER_OFF);

                    prAdapter->fgIsEnterD3ReqIssued = FALSE;
                }
                else {
                    ARB_STATE_TRANSITION(prAdapter, STANDBY, RF_TEST);
                }
            }
            break;
        case ARB_STATE_RF_TEST:
            {
                /* Do nothing in this State */
                if (rftestInit(prAdapter) != WLAN_STATUS_SUCCESS) {
                    DBGLOG(ARB, ERROR, ("Rf Test Init fail.\n"));
                }
            }
            break;
        }
    } while (fgIsTransition);

    return;
} /* arbFsmSteps */
#else

/*----------------------------------------------------------------------------*/
/*!
* \brief The Core FSM engine of ARB(Arbiter).
*
* \param[in] prAdapter  Pointer to the Adapter structure.
* \param[in] eNextState Enum value of next ARB STATE
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
arbFsmSteps (
    P_ADAPTER_T prAdapter,
    ENUM_ARB_STATE_T eNextState
    )
{
    P_ARB_INFO_T prArbInfo;
    BOOLEAN fgIsTransition = (BOOLEAN)FALSE;

    DEBUGFUNC("arbFsmSteps");

    ASSERT(prAdapter);
    prArbInfo = &prAdapter->rArbInfo;

    do {
        /* Do entering Next State */
        prArbInfo->ePreviousState = prArbInfo->eCurrentState;
        DBGLOG(ARB, STATE, ("\nTRANSITION: [%s] -> [%s]\n\n",
                            apucDebugArbState[prArbInfo->eCurrentState],
                            apucDebugArbState[eNextState]));

        /* NOTE(Kevin): This is the only place to change the eCurrentState(except initial) */
        prArbInfo->eCurrentState = eNextState;

        fgIsTransition = (BOOLEAN)FALSE;

        /* Do tasks of the State that we just entered */
        switch (prArbInfo->eCurrentState) {
        /* NOTE(Kevin 2007/3/30): we don't have to rearrange the sequence of following
         * switch case. Instead I would like to use a common lookup table of array
         * of function pointer to speed up state search.
         */
        case ARB_STATE_POWER_OFF:
            {
                prAdapter->fgIsRadioOff = TRUE;

                timerUnInitialize(prAdapter);
#if 0
                /* Clear all interrupt status with disabling GINT */
                nicChipReset(prAdapter);
#endif
                /* Not allow interrupt to be trigger during idle state,
                   whenever clock is turned off */
                nicDisableInterrupt(prAdapter);

                nicpmPowerOff(prAdapter);
            }
            break;

        case ARB_STATE_RESET:
            {
                /* Note:
                   Move the HW reset before SW reset. If the order is reversed, SW may check few bits failed
                   on the abortion function.
                   (ex: if clock is off during HW scan is enable, the scan_busy bit will be asserted always,
                        and it is unable for SW to abort scan. In this case, SW assertion will be arised)
                */

                /* HW reset */
                nicChipReset(prAdapter);

                /* SW modules reset */
                nicTxRelease(prAdapter);

                nicRxUninitialize(prAdapter);

                secFsmRunEventAbort(prAdapter);

                timerUnInitialize(prAdapter);
                nichtCancelTimer(prAdapter, VOIP_POLL_TIMER);

                pmFsmRunEventAbort(prAdapter);

                scanFsmRunEventScanAbort(prAdapter);

                ARB_STATE_TRANSITION(prAdapter, RESET, STANDBY);
            }
            break;

        case ARB_STATE_STANDBY:
            {
                /* Disable all processes */

                prArbInfo->fgIsDiagnosingConnection = FALSE;

                prAdapter->fgIsRadioOff = FALSE;

                if (prAdapter->fgIsEnterD3ReqIssued) {

                    ARB_STATE_TRANSITION(prAdapter, STANDBY, POWER_OFF);

                    prAdapter->fgIsEnterD3ReqIssued = FALSE;
                }
                else if (prArbInfo->fgTestMode) {

                    ARB_STATE_TRANSITION(prAdapter, STANDBY, RF_TEST);
                }
                else if (prAdapter->rConnSettings.fgIsConnReqIssued) {

                    if (prAdapter->fgCounterMeasure == FALSE) {
                        ARB_STATE_TRANSITION(prAdapter, STANDBY, SEARCH);
                    }
                }
#if !CFG_SUPPORT_SSID_RECOVER_STATE
                else if (prAdapter->fgRemoveBGScan) {
                    prAdapter->fgRemoveBGScan = FALSE;
                }
#endif
                else {

                    ARB_STATE_TRANSITION(prAdapter, STANDBY, IDLE);
                }

            }
            break;

        case ARB_STATE_RF_TEST:
            {
                if (rftestInit(prAdapter) != WLAN_STATUS_SUCCESS) {
                    DBGLOG(ARB, ERROR, ("Rf Test Init fail.\n"));
                }
            }
            break;

        case ARB_STATE_SEARCH:
            {
                P_CONNECTION_SETTINGS_T prConnSettings = &prAdapter->rConnSettings;
                P_BSS_DESC_T prBssDesc = (P_BSS_DESC_T)NULL;


                //4 <1> Search for a matched candidate and save it to prTargetBssDesc.
                prBssDesc = scanSearchBssDescByPolicy(prAdapter);

                //4 <2> We are not under Roaming Condition.
                if (prAdapter->eConnectionState == MEDIA_STATE_DISCONNECTED) {

                    //4 <2A> If we have the matched one
                    if (prBssDesc) {

                        //4 <2A.1> Record the target BSS_DESC_T for next STATE.
                        prArbInfo->prTargetBssDesc = prBssDesc;
                        COPY_MAC_ADDR(prAdapter->rConnSettings.aucBSSID, prBssDesc->aucBSSID);


                        //4 <2A.2> Do STATE transition and update current Operation Mode.
                        if (prBssDesc->eBSSType == BSS_TYPE_INFRASTRUCTURE) {

                            prAdapter->eCurrentOPMode = OP_MODE_INFRASTRUCTURE;

                            ARB_STATE_TRANSITION(prAdapter, SEARCH, JOIN);
                        }
                        else if (prBssDesc->eBSSType == BSS_TYPE_IBSS) {

                            prAdapter->eCurrentOPMode = OP_MODE_IBSS;

                            ARB_STATE_TRANSITION(prAdapter, SEARCH, IBSS_MERGE);
                        }
                        else {
                            /* Reserve for supporting proprietary BSS */

                            prAdapter->eCurrentOPMode = OP_MODE_RESERVED;

                            ASSERT(0);
                        }
                    }
                    //4 <2B> If we don't have the matched one
                    else {
                        prArbInfo->prTargetBssDesc = NULL;

                        //4 <2B.1> Try to SCAN
                        if (prArbInfo->fgTryFullScan) {
                            SCAN_REQ_CONFIG_T rScanReqConfig;


                            /* Only try to do fully scan once. */
                            prArbInfo->fgTryFullScan = FALSE;

                            rScanReqConfig.eScanMethod = SCAN_METHOD_FULL_SCAN;
                            /* 12 milliseconds. If detect the air activity by MDRDY,
                             * this is the transmission time of 1Mbps with 1536 Bytes.
                             */
                            rScanReqConfig.ucChnlDwellTimeMin = SCAN_CHANNEL_DWELL_TIME_MIN;

                            /* N milliseconds = 100TU(Beacon Interval) - min + 10TU
                             * (if Beacon Drift) = 98TU(round down to millisecond).
                             */
                            rScanReqConfig.ucChnlDwellTimeExt = SCAN_CHANNEL_DWELL_TIME_EXT;

                            rScanReqConfig.ucNumOfPrbReq = FULL_SCAN_TOTAL_PROBE_REQ_NUM;

                            if (prAdapter->rConnSettings.eConnectionPolicy != CONNECT_BY_SSID_ANY) {
                                COPY_SSID(rScanReqConfig.rSpecifiedSsid.aucSsid,
                                          rScanReqConfig.rSpecifiedSsid.u4SsidLen,
                                          prAdapter->rConnSettings.aucSSID,
                                          prAdapter->rConnSettings.ucSSIDLen);

                                DBGLOG(ARB, TRACE, ("Scan SSID:%s SSID Len:%d\n",
                                    prAdapter->rConnSettings.aucSSID,
                                    prAdapter->rConnSettings.ucSSIDLen));

                                rScanReqConfig.ucNumOfSpecifiedSsidPrbReq = FULL_SCAN_SPECIFIC_PROBE_REQ_NUM;
                            }
                            else {
                                kalMemZero(&rScanReqConfig.rSpecifiedSsid,
                                           sizeof(PARAM_SSID_T));

                                rScanReqConfig.ucNumOfSpecifiedSsidPrbReq = 0;
                            }


                            rScanReqConfig.eScanType = SCAN_TYPE_ACTIVE_SCAN;

                            rScanReqConfig.pfScanDoneHandler = (PFN_SCAN_DONE_HANDLER)0;

                            {
                                UINT_32 i, j, u4ScanIndex = 0;

                                rScanReqConfig.ucNumOfScanChnl = (UINT_8)prAdapter->u2NicOpChnlNum;

                                for (j = 0; j < INTERLACED_SCAN_CHANNEL_GROUPS_NUM; j++) {

                                    for (i = j; i < rScanReqConfig.ucNumOfScanChnl;
                                        i += INTERLACED_SCAN_CHANNEL_GROUPS_NUM, u4ScanIndex++) {

                                        rScanReqConfig.arChnlInfoList[u4ScanIndex].ucChannelNum =
                                            prAdapter->arNicOpChnList[i].ucChannelNum;

                                        rScanReqConfig.arChnlInfoList[u4ScanIndex].eBand =
                                            prAdapter->arNicOpChnList[i].eBand;
                                    }
                                }
                            }

                            if (scanFsmRunEventScanReqSetup(prAdapter, &rScanReqConfig) != WLAN_STATUS_SUCCESS) {

                                if (prConnSettings->eOPMode == NET_TYPE_INFRA) {

                                    /* We don't update eCurrentOpMode here, because it will back to SEARCH STATE later.
                                     * or ARB ABORT Event.
                                     */
#if CFG_SUPPORT_SSID_RECOVER_STATE
                                    ARB_STATE_TRANSITION(prAdapter, SEARCH, BG_SSID_SCAN);
#else
                                    prAdapter->fgRemoveBGScan = TRUE;
                                    eNextState = ARB_STATE_STANDBY;
                                    fgIsTransition = TRUE;
#endif
                                }
                                else {
                                    /* TODO(Kevin): add retry count ? */
                                    prAdapter->eCurrentOPMode = OP_MODE_IBSS;

                                    ARB_STATE_TRANSITION(prAdapter, SEARCH, IBSS_ALONE);
                                }

                                ASSERT(0);
                            }
                            else {
                                /* NOTE(Kevin): Because we'll enter SCAN_STATE soon, so we
                                 * should do aging here to purge old scan records.
                                 */
                                scanRemoveBssDescsByPolicy(prAdapter, (SCAN_RM_POLICY_EXCLUDE_CONNECTED | \
                                                                       SCAN_RM_POLICY_TIMEOUT) );

                                GET_CURRENT_SYSTIME(&prArbInfo->rLastScanRequestTime);
                                ARB_STATE_TRANSITION(prAdapter, SEARCH, SCAN);
                            }

                        }
                        //4 <2B.2> We've do SCAN already, now wait in some STATE.
                        else {
                            if (prConnSettings->eOPMode == NET_TYPE_INFRA) {

                                /* We don't update eCurrentOpMode here, because it will back to SEARCH STATE later.
                                 * or ARB ABORT Event.
                                 */
#if CFG_SUPPORT_SSID_RECOVER_STATE
                                ARB_STATE_TRANSITION(prAdapter, SEARCH, BG_SSID_SCAN);
#else
                                prAdapter->fgRemoveBGScan = TRUE;
                                eNextState = ARB_STATE_STANDBY;
                                fgIsTransition = TRUE;
#endif
                            }
                            else {
                                /* TODO(Kevin): add retry count ? */
                                prAdapter->eCurrentOPMode = OP_MODE_IBSS;

                                ARB_STATE_TRANSITION(prAdapter, SEARCH, IBSS_ALONE);
                            }
                        }
                    }

                }
                //4 <3> We are under Roaming Condition.
                else { // prAdapter->eConnectionState == MEDIA_STATE_CONNECTED.

                    //4 <3A> This BSS_DESC_T is our AP.
                    /* NOTE(Kevin 2008/05/16): Following cases will go back to NORMAL_TR.
                     * CASE I: During Roaming, APP(WZC/NDISTEST) change the connection
                     *         settings. That make we can NOT match the original AP, so the
                     *         prBssDesc is NULL.
                     * CASE II: The same reason as CASE I. Because APP change the
                     *          eOPMode to NET_TYPE_IBSS of connection setting, so
                     *          the BssDesc become the IBSS node.
                     * (For CASE I/II, before WZC/NDISTEST set the OID_SSID, it will change
                     * other parameters in connection setting first. So if we do roaming
                     * at the same time, it will hit these cases.)
                     *
                     * CASE III: Normal case, we can't find other candidate to roam
                     * out, so only the current AP will be matched.
                     */
                    if ((!prBssDesc) || /* CASE I */
                        (prBssDesc->eBSSType == BSS_TYPE_IBSS) || /* CASE II */
                        (prBssDesc->fgIsConnected) /* CASE III */) {

#if DBG
                        if ((prBssDesc) &&
                            (prBssDesc->fgIsConnected)) {
                            ASSERT(EQUAL_MAC_ADDR(prBssDesc->aucBSSID, prAdapter->rBssInfo.aucBSSID));
                        }
#endif /* DBG */
                        /* We already associated with it, go back to NORMAL_TR */
                        roamingFsmRunEventRoamFail(prAdapter);

                        ARB_STATE_TRANSITION(prAdapter, SEARCH, NORMAL_TR);
                    }
                    //4 <3B> Try to roam out for JOIN this BSS_DESC_T.
                    else {

#if DBG
                        ASSERT(UNEQUAL_MAC_ADDR(prBssDesc->aucBSSID, prAdapter->rBssInfo.aucBSSID));
#endif /* DBG */

                        //4 <3B.1> Record the target BSS_DESC_T for next STATE.
                        prArbInfo->prTargetBssDesc = prBssDesc;

                        /* Do JOIN - (Auth + ReAssoc) Process to roam out */
                        ARB_STATE_TRANSITION(prAdapter, SEARCH, JOIN);
                    }
                }

                DBGLOG(ARB, INFO, ("Check current Operation Mode: %s.\n",
                     apucDebugOpMode[prAdapter->eCurrentOPMode]));
            }
            break;

        case ARB_STATE_BG_SSID_SCAN:
            {

                {
                    P_SCAN_CONFIG_T prScanCfg = &prAdapter->rScanInfo.rScanConfig;
                    UINT_32 i;


                    prScanCfg->eScanType = SCAN_TYPE_ACTIVE_SCAN;

                    for (i = 0; i < prAdapter->u2NicOpChnlNum; i++) {

                        prScanCfg->arChnlInfoList[i].ucChannelNum = prAdapter->arNicOpChnList[i].ucChannelNum;
                        prScanCfg->arChnlInfoList[i].eBand = prAdapter->arNicOpChnList[i].eBand;
                    }

                    prScanCfg->ucNumOfScanChnl = (UINT_8)prAdapter->u2NicOpChnlNum;
                    prScanCfg->ucChnlDwellTimeMin = SCAN_CHANNEL_DWELL_TIME_MIN;
                    prScanCfg->ucChnlDwellTimeExt = SCAN_CHANNEL_DWELL_TIME_EXT;
                    prScanCfg->u2RxFifoThreshold = 0;
                    prScanCfg->ucNumOfPrbReq = FULL_SCAN_TOTAL_PROBE_REQ_NUM;

                    if (!prScanCfg->rBgScanCfg.fgIsFromUserSetting) {
                        if (prAdapter->rConnSettings.eConnectionPolicy != CONNECT_BY_SSID_ANY) {
                            prScanCfg->rBgScanCfg.rScanCandidate.ucNumHwSsidScanEntry = 1;

                            COPY_SSID(prScanCfg->rBgScanCfg.rScanCandidate.arHwSsidScanEntry[0].aucSsid,
                                      prScanCfg->rBgScanCfg.rScanCandidate.arHwSsidScanEntry[0].u4SsidLen,
                                      prAdapter->rConnSettings.aucSSID,
                                      prAdapter->rConnSettings.ucSSIDLen);

                            DBGLOG(ARB, TRACE, ("Scan SSID:%s SSID Len:%d\n",
                                prAdapter->rConnSettings.aucSSID,
                                prAdapter->rConnSettings.ucSSIDLen));

                            prScanCfg->ucNumOfSpecifiedSsidPrbReq = FULL_SCAN_SPECIFIC_PROBE_REQ_NUM;
                        }
                        else {
                            prScanCfg->ucNumOfSpecifiedSsidPrbReq = 0;
                        }
                    }
                }

                /* <NOTE> Kevin: the way to leave this state is SCAN Done/OID: SCAN event */
                scanFsmRunEventStart(prAdapter, ENUM_HW_SCAN_BG_SSID_SCAN);
            }
            break;

        case ARB_STATE_JOIN:
            {   WLAN_STATUS rStatus;


                nicRxStartQueue(prAdapter);
                nicTxFlushStopQueues(prAdapter, (UINT_8)TXQ_MGMT_MASK, (UINT_8)TXQ_DATA_MASK);
                nicTxStartQueues(prAdapter, (UINT_8)TXQ_MGMT_MASK);

                /* Auth, assoc, adopt parameter */
                rStatus = joinFsmRunEventStart(prAdapter, prArbInfo->prTargetBssDesc);

                /* NOTE: We only can get two kind of WLAN_STATUS here - FAILURE or PENDING. */
                if (rStatus == WLAN_STATUS_FAILURE) {
                    if (prAdapter->eConnectionState == MEDIA_STATE_DISCONNECTED) {
                        ARB_STATE_TRANSITION(prAdapter, JOIN, SEARCH);
                    }
                    else { /* Roaming fail, back to NORMAL_TR */
                        ARB_STATE_TRANSITION(prAdapter, JOIN, NORMAL_TR);
                    }
                }
            }
            break;

        case ARB_STATE_SCAN:
            {
                /* Do nothing in this State from VISIO diagram */

                /* <NOTE> Kevin: the way to leave this state is SCAN Done/OID: SCAN event */
                //DBGLOG(ARB, INFO, ("Setup Original Channel = %d, Band = %d\n",
                    //prAdapter->rRFInfo.ucChannelNum, prAdapter->rRFInfo.eBand));

                scanSetupOriginalChannel(prAdapter,
                                         prAdapter->rRFInfo.ucChannelNum,
                                         prAdapter->rRFInfo.eBand);

                scanFsmRunEventStart(prAdapter, ENUM_HW_SCAN_NORMAL_SCAN);
            }
            break;

        case ARB_STATE_IBSS_ALONE:
            {   WLAN_STATUS rStatus;
                P_BSS_INFO_T prBssInfo = &prAdapter->rBssInfo;

#if CFG_SUPPORT_802_11D
                /* NOTE:
                   It may break the rule by IEEE802.11 Chapter 7.2.3.1 Beacon frame format, due to there
                   may be no country information before creating IBSS:
                   If the dot11MultiDomainCapabilityEnabled attribute is true,
                   a STA shall include a Country information element in the transmission of Beacon frames.
                */
#endif

                /* Do create AdHoc */
                rStatus = ibssStartIBSS(prAdapter);

                pmFsmRunEventOnCreateIbss(prAdapter,
                                          prBssInfo->u2BeaconInterval);

                /* NOTE: We only can get two kind of WLAN_STATUS here - FAILURE or SUCCESS. */
                if (rStatus != WLAN_STATUS_SUCCESS) {
                    ASSERT(0);
                }

                ARB_SET_TIMER(prAdapter,
                              prArbInfo->rIbssAloneTimer,
                              TU_TO_MSEC(IBSS_ALONE_TIMEOUT_BEACON_INTERVAL *
                                  DOT11_BEACON_PERIOD_DEFAULT));

                /* The way to leave this state is
                 * 1. Time-Out back to SEARCH & SCAN.
                 * 2. OID: SCAN Req Event from User.
                 * 3. Rx Beacon Event from a potential member.
                 */
            }
            break;

        case ARB_STATE_IBSS_MERGE:
            {
                WLAN_STATUS rStatus;

                /* Do merge different IBSS by adopting other IBSS paramete */
                rStatus = ibssMergeIBSS(prAdapter, prArbInfo->prTargetBssDesc);

                if (rStatus == WLAN_STATUS_SUCCESS) {
                    ARB_STATE_TRANSITION(prAdapter, IBSS_MERGE, NORMAL_TR);
                }
                else {

                    switch (prArbInfo->ePreviousState) {
                    case ARB_STATE_SEARCH:
                        ARB_STATE_TRANSITION(prAdapter, IBSS_MERGE, SEARCH);
                        break;

                    case ARB_STATE_NORMAL_TR:
                        ARB_STATE_TRANSITION(prAdapter, IBSS_MERGE, NORMAL_TR);
                        break;

                    case ARB_STATE_IBSS_ALONE:
                        ARB_STATE_TRANSITION(prAdapter, IBSS_MERGE, IBSS_ALONE);
                        break;

                    default:
                        /* Shouldn't happen */
                        ASSERT(0);
                        break;

                    }
                }
            }
            break;

        case ARB_STATE_NORMAL_TR:
            {
                /* NOTE(Kevin): Once we enter to NORMAL_TR, we enable the corresponding TXQ
                 * for transmission of DATA Frame.
                 */
                if (
                    #if SUPPORT_WAPI
                    privacyRsnKeyHandshakeEnabled(prAdapter) &&
                    #endif
                    (prAdapter->rSecInfo.fgBlockOnlyAPTraffic) &&
                    (prAdapter->rSecInfo.fgBlockTxTraffic)) {
                    nicTxStartQueues(prAdapter, TXQ_MGMT_MASK);
                }
                else {
                    UINT_8 ucStartQues;
#if CFG_TX_AGGREGATE_HW_FIFO
                    P_TX_CTRL_T prTxCtrl = &prAdapter->rTxCtrl;

                    if (prTxCtrl->fgAggregateTxFifo) {

                        ucStartQues = TXQ_MGMT_MASK | BIT(TXQ_AC1) | BIT(TXQ_AC3);
                    }
                    else
#endif /* CFG_TX_AGGREGATE_HW_FIFO */
                    {
                        ucStartQues = TXQ_MGMT_MASK | TXQ_DATA_MASK;

                    }

                    nicTxStartQueues(prAdapter, ucStartQues );
                }

                nicRxStartQueue(prAdapter);

            }
            break;

        case ARB_STATE_DEDICATED_MEASUREMEMT:
            {
                /* TODO(Kevin) */
            }
            break;

        case ARB_STATE_IDLE:
            {
                prAdapter->fgIsRadioOff = TRUE;

                /* Not allow interrupt to be trigger during idle state,
                   whenever clock is turned off */
                nicDisableInterrupt(prAdapter);

                /* NOTE:
                   There's no clock control here due to clock control is done in OS entry and exit.
                   Now it is assumed that clock is keeping consistent whether how the ARB state
                   transition. The only exception is RESET function, it will always try to let
                   system clock ON for subsequent processing.
                */
#if 0
                nicpmPowerOff(prAdapter);
#endif
            }
            break;

        default:
            ASSERT(0); /* Make sure we have handle all STATEs */

        }
    }
    while (fgIsTransition);

    return;

} /* end of arbFsmSteps() */

#endif /* CFG_SDIO_DEVICE_DRIVER_WO_NDIS */




/*----------------------------------------------------------------------------*/
/*!
* \brief This function will indicate an Event of "IST" to ARB FSM.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
BOOLEAN
arbFsmRunEventIST (
    IN P_ADAPTER_T  prAdapter
    )
{
    BOOLEAN fgStatus = TRUE;


    ASSERT(prAdapter);

    ARB_ACQUIRE_POWER_CONTROL_FROM_PM_IN_IST(prAdapter);

    /* Call nicProcessIST here */
    if (nicProcessIST(prAdapter) == WLAN_STATUS_ADAPTER_NOT_READY) {
        fgStatus = FALSE;
    }

    ARB_RECLAIM_POWER_CONTROL_TO_PM_IN_IST(prAdapter);

    return fgStatus;

} /* end of arbFsmRunEventIST() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will indicate an Event of "Root Timer Timeout" to ARB FSM.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
arbFsmRunEventRootTimerHandler (
    IN P_ADAPTER_T  prAdapter
    )
{
    ASSERT(prAdapter);

    timerDoTimeOutCheck(prAdapter);

    return;
} /* end of arbFsmRunEventRootTimerHandler() */


/*----------------------------------------------------------------------------*/
/*!
* \brief An EVENT to force ARB FSM to enter ARB_STATE_RESET anyway.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
arbFsmRunEventReset (
    IN P_ADAPTER_T  prAdapter
    )
{
    DEBUGFUNC("arbFsmRunEventReset");


    ASSERT(prAdapter);

    DBGLOG(ARB, EVENT, ("\n\nARB EVENT: Reset.\n\n"));

    /* Force the ARB to enter RESET state */
    arbFsmSteps(prAdapter, ARB_STATE_RESET);

    return;
} /* end of arbFsmRunEventReset() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will indicate an Event of "Abort" to ARB FSM. ARB will
*        restart from ARB_STATE_STANDBY.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
arbFsmRunEventAbort (
    IN P_ADAPTER_T prAdapter,
    IN BOOLEAN fgIsDelayMediaStateIndication
    )
{
    P_ARB_INFO_T prArbInfo;
    ENUM_ARB_STATE_T eNextState;
#if CFG_SUPPORT_802_11D
    P_CONNECTION_SETTINGS_T prConnSettings;
#endif
    P_RFTEST_INFO_T prRFATInfo;

    ASSERT(prAdapter);
    prArbInfo = &prAdapter->rArbInfo;
    eNextState = prArbInfo->eCurrentState;
    prRFATInfo = &prAdapter->rRFTestInfo;

#if CFG_SUPPORT_802_11D
    prConnSettings = &prAdapter->rConnSettings;
#endif

    DBGLOG(ARB, EVENT, ("\n\nARB EVENT: Abort.\n\n"));

    //4 <1> Clear all previous JOIN Status Code in current SCAN_RESULT.
    //scanClearJoinStatusCodeOfBssDescs(prAdapter); Kevin: remove later.
    staRecClearStatusAndReasonCode(prAdapter);

    //4 <2> Do abort event.
    switch(prArbInfo->eCurrentState) {

    case ARB_STATE_SCAN:
        {
            /* abort scan */
            scanFsmRunEventScanAbort(prAdapter);

            /* abort associated PM functions (especially during online scan) */
            pmFsmRunEventAbort(prAdapter);

            nicRxReleasePrivilegeOfRxQue(prAdapter,
                                         FALSE,
                                         FALSE);

            nicTxReleasePrivilegeOfTxQue(prAdapter,
                                         (UINT_8)TXQ_MGMT_MASK);


            eNextState = ARB_STATE_STANDBY;
        }
        break;

    case ARB_STATE_NORMAL_TR:
        {
            pmFsmRunEventAbort(prAdapter);

            prAdapter->fgIsBlockToScan = FALSE;

            eNextState = ARB_STATE_STANDBY;
        }
        break;

    case ARB_STATE_JOIN:
        {
            joinFsmRunEventAbort(prAdapter);

            eNextState = ARB_STATE_STANDBY;
        }
        break;

    case ARB_STATE_IBSS_ALONE:
        {
            pmFsmRunEventAbort(prAdapter);

            ARB_CANCEL_TIMER(prAdapter,
                             prArbInfo->rIbssAloneTimer);

            eNextState = ARB_STATE_STANDBY;
        }
        break;

    case ARB_STATE_DEDICATED_MEASUREMEMT:
        {
            /* TODO(Kevin):
             * 1. Issue Stop Measurement Event
             */

            eNextState = ARB_STATE_STANDBY;
        }
        break;

    case ARB_STATE_BG_SSID_SCAN:
        {
            scanFsmRunEventScanAbort(prAdapter);

            nicRxReleasePrivilegeOfRxQue(prAdapter,
                                         FALSE,
                                         FALSE);

            nicTxReleasePrivilegeOfTxQue(prAdapter,
                                         (UINT_8)TXQ_MGMT_MASK);


            //resetLogicReset(prAdapter);

            eNextState = ARB_STATE_STANDBY;
        }
        break;

    case ARB_STATE_RF_TEST:
        {
            if (prRFATInfo->eCurrentState == RF_AUTOTEST_STATE_TX) {
    #if CFG_SDIO_DEVICE_DRIVER_WO_NDIS
                ARB_CANCEL_TIMER(prAdapter,
                             prAdapter->rTxCtrl.rPktTxIntervalTimer);
    #endif
                rftestTxStopTx(prAdapter);

                DBGLOG(RFTEST, TRACE, ("RF_AT_COMMAND_STOPTEST TX\n"));
            }
            else if (prRFATInfo->eCurrentState == RF_AUTOTEST_STATE_RX) {
                rftestRxStopRx(prAdapter);

                DBGLOG(RFTEST, TRACE, ("RF_AT_COMMAND_STOPTEST RX\n"));
            }
            else if (prRFATInfo->eCurrentState == RF_AUTOTEST_STATE_RESET) {
                DBGLOG(RFTEST, WARN, ("Try to stop test while resetting"));
            }

            eNextState = ARB_STATE_STANDBY;
        }
        break;

    case ARB_STATE_IDLE:
        {
            P_THERMO_INFO_T     prThermoInfo;
            ALC_VAL             rAlcIniVal;

            DBGLOG(NIC, TRACE, ("Enable ALC\n"));

            prThermoInfo = &prAdapter->rThermoInfo;
            halALCREnable(prAdapter, prThermoInfo->u4AlcArParam, 0x00, 0x3F, 0x00);
            halALCRTriggerALC(prAdapter);
            halALCRGetRawValue(prAdapter, &rAlcIniVal);
            halALCREnable(prAdapter, prThermoInfo->u4AlcArParam, 0x00, 0x3F, rAlcIniVal);

            nicEnableInterrupt(prAdapter);

            //Renbang (20100417) : when quit from IDLE, set prefer ant to Wi-Fi 
            //<0>set prefer ant to WiFi
            if (prAdapter->rPtaInfo.fgSingleAntenna) {
#if PTA_NEW_BOARD_DESIGN		
                nicPtaSetAnt(prAdapter, TRUE);    
#endif
            }

            eNextState = ARB_STATE_STANDBY;
        }
        break;

    default:
        break;
    }


    if (prAdapter->rConnSettings.fgIsEnableRoaming) {
        roamingFsmRunEventAbort(prAdapter);
    }


#if CFG_TX_AGGREGATE_HW_FIFO
    if (prAdapter->rTxCtrl.fgAggregateTxFifo) {
        nicTxAggregateTXQ(prAdapter, FALSE);
    }
#endif /* CFG_TX_AGGREGATE_HW_FIFO */


    /* NOTE(Kevin): We need to abort whole PARTIAL SCAN sequence, even
     * the state of Arbiter is not in ARB_STATE_SCAN.
     */
    scanFsmRunEventScanReqCleanUp(prAdapter);


    prAdapter->fgBypassPortCtrlForRoaming = FALSE;

    if (prAdapter->eConnectionState == MEDIA_STATE_CONNECTED) {

        authSendDeauthFrame(prAdapter,
                            prAdapter->rBssInfo.aucBSSID,
                            REASON_CODE_DEAUTH_LEAVING_BSS,
                            AC4,
                            NULL);
        kalMdelay(2);

        if (prAdapter->fgCounterMeasure == FALSE) {
            secFsmRunEventAbort(prAdapter);
        }

        prAdapter->eConnectionState = MEDIA_STATE_DISCONNECTED;

        if (fgIsDelayMediaStateIndication) {

            ARB_SET_TIMER(prAdapter,
                          prArbInfo->rIndicationOfDisconnectTimer,
                          SEC_TO_MSEC(CONNECTION_LOST_INDICATION_TIMEOUT_SEC));

            /* NOTE(Kevin 2008/01/03):
             * 3. If we lost connection in NORMAL_TR STATE under OP_MODE_IBSS,
             *    we shouldn't clear the fgIsIBSSActive flag. So that if ARB enter
             *    IBSS ALONE STATE later, we'll keep the same setting as NORMAL_TR.
             */
            if (prAdapter->eCurrentOPMode != OP_MODE_IBSS) {
                prAdapter->fgIsIBSSActive = FALSE;
            }
        }
        else {
            /* Indicate the protocol that the media state was changed */

            prAdapter->eConnectionStateIndicated = MEDIA_STATE_DISCONNECTED;

            nicTxFlushStopQueues(prAdapter, TXQ_DATA_MASK, 0);

            nicTxCleanUpSendWaitQue(prAdapter);

            nicTxCleanUpOsSendQue(prAdapter);

#if CFG_IBSS_POWER_SAVE
            nicTxCleanUpStaWaitQue(prAdapter);
#endif /* CFG_IBSS_POWER_SAVE */

            /* Clear the pmkid cache while do media disconnect */
            if (prAdapter->rConnSettings.eAuthMode == AUTH_MODE_WPA2)
                privacyClearPmkid(prAdapter);

	   kalMemZero(prConnSettings->aucSSID, sizeof(prConnSettings->aucSSID)); 
            kalIndicateStatusAndComplete(prAdapter->prGlueInfo,
                                         WLAN_STATUS_MEDIA_DISCONNECT,
                                         NULL,
                                         0);
            /* NOTE(Kevin 2008/01/03):
             * 1. The first time we create an IBSS, we'll generate the BSSID from
             *    random number generator once. If ARB leave the IBSS ALONE STATE
             *    for SCAN, we'll keep the same BSSID after ARB back to ALONE STATE.
             * 2. If User issue another OID REQ - e.g. SSID, we'll clean the
             *    fgIsIBSSActive flag for renew a new BSSID.
             */
            prAdapter->fgIsIBSSActive = FALSE;
        }
    }
    else {

        /* We just do Abort Event before and is waiting for DISCONNECT indication */
        if (prAdapter->eConnectionStateIndicated == MEDIA_STATE_CONNECTED) {

            if (fgIsDelayMediaStateIndication) {
                /* Do nothing, still wait for DISCONNECT event */
            }
            else {
                prAdapter->eConnectionStateIndicated = MEDIA_STATE_DISCONNECTED;

                nicTxFlushStopQueues(prAdapter, TXQ_DATA_MASK, 0);

                nicTxCleanUpSendWaitQue(prAdapter);

                nicTxCleanUpOsSendQue(prAdapter);

#if CFG_IBSS_POWER_SAVE
                nicTxCleanUpStaWaitQue(prAdapter);
#endif /* CFG_IBSS_POWER_SAVE */

		kalMemZero(prConnSettings->aucSSID, sizeof(prConnSettings->aucSSID)); 

                kalIndicateStatusAndComplete(prAdapter->prGlueInfo,
                                             WLAN_STATUS_MEDIA_DISCONNECT,
                                             NULL,
                                             0);
                ARB_CANCEL_TIMER(prAdapter,
                                 prArbInfo->rIndicationOfDisconnectTimer);
            }
        }

        /* NOTE(Kevin 2008/03/21):
         * When eConnectionState is DISCONNECTED, we'll always restart the IBSS
         * according to the information in rConnSettings.
         */
        prAdapter->fgIsIBSSActive = FALSE;
    }
    prAdapter->fgIsIBSSBeaconTimeoutAlarm = FALSE;

    if (prAdapter->eCurrentOPMode == OP_MODE_INFRASTRUCTURE) {
        bssLeave(prAdapter);
    }
    else if (prAdapter->eCurrentOPMode == OP_MODE_IBSS) {
        ibssLeave(prAdapter);
    }

#if CFG_SUPPORT_802_11D
    /* Invalid the country information */
    prAdapter->rBssInfo.fgIsCountryInfoPresent = FALSE;
    if (prConnSettings->fgMultiDomainCapabilityEnabled) {
        nicSetupOpChnlList(prAdapter, COUNTRY_CODE_NULL, FALSE);
    } else {
        nicSetupOpChnlList(prAdapter, prConnSettings->u2CountryCode, FALSE);
    }
#endif

#if CFG_LP_IOT
    {
    UINT_32 u4RegValue;
    HAL_MCR_RD(prAdapter, MCR_RR, &u4RegValue);
//    HAL_MCR_WR(prAdapter, MCR_RR, u4RegValue & ~RR_ENABLE_MA);
    u4RegValue &= ~(RR_RCPI_HIGH_THRESHOLD_MASK | RR_RCPI_LOW_THRESHOLD_MASK);
    u4RegValue |= /*RR_RCPI_HIGH_THRESHOLD_MASK  |*/ ((0)  << 8) | RR_RCPI_PARM_1_OF_16;
    HAL_MCR_WR(prAdapter, MCR_RR, RR_ENABLE_MA | u4RegValue);
    DBGLOG(LP_IOT, WARN, ("[LP-IOT] un-Init RCPI settings: 0x%x (MCR_RR=0x%08X)\n", u4RegValue & BITS(0, 7), u4RegValue));
    }
    NIC_UNSET_INT_EVENT(prAdapter, INT_EVENT_RCPI);
#endif

    /* Call arbFsmSteps() when we are going to change ARB STATE */
    if (prArbInfo->eCurrentState != eNextState) {
        arbFsmSteps(prAdapter, eNextState);
    }

    return;
} /* end of arbFsmRunEventAbort() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will indicate an Event of "TX Packet from OS" to ARB FSM.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
* \param[in] prPacketInfo   Pointer to the Packet Info structure.
*
* \retval WLAN_STATUS_PENDING   : MSDU can send to HW TX FIFO without sendComplete
*                                 (pending for TX_DONE event).
*                                 or wait in arTxQPara[].rSendWaitQueue.
* \retval WLAN_STATUS_FAILURE   : Get failure while access HW TX FIFO or rejected.
* \retval WLAN_STATUS_RESOURCES : ARB is not ready to send, please wait.
* \retval WLAN_STATUS_SUCCESS   : MSDU was send to HW TX FIFO and also do sendComplete
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
arbFsmRunEventTxMsduFromOs (
    IN P_ADAPTER_T      prAdapter,
    IN P_PACKET_INFO_T  prPacketInfo
    )
{
    P_TX_CTRL_T prTxCtrl;
    P_MSDU_INFO_T prMsduInfo;
    UINT_8 ucTC; /* "Traffic Class" SW(Driver) resource classification */
    P_QUE_T prOsSendQueue;
    P_QUE_ENTRY_T prQueueEntry;
#if CFG_IBSS_POWER_SAVE
    P_STA_RECORD_T prStaRec = (P_STA_RECORD_T)NULL;
#endif /* CFG_IBSS_POWER_SAVE */
    UINT_8 ucControlFlag = MSDU_INFO_CTRL_FLAG_NONE;
    WLAN_STATUS rStatus = WLAN_STATUS_FAILURE;
    P_MGT_PACKET_T prMgtPacket;
    UINT_8 ucWlanHeaderLen;
    UINT_32 u2EstimatedFrameLen;

    ASSERT(prAdapter);
    ASSERT(prPacketInfo);
    prTxCtrl = &prAdapter->rTxCtrl;

    do {
        /* Use the eConnectionStateIndicated to keep synchronization with OS */
        if (prAdapter->eConnectionStateIndicated == MEDIA_STATE_CONNECTED &&
            rsnTxProcessMSDU(prAdapter, prPacketInfo)) {

            TX_INC_CNT(prTxCtrl, TX_OS_MSDU_COUNT);

            prMsduInfo = (P_MSDU_INFO_T)NULL;


            //4 <1> Convert the Priority Parameter/TID (User Priority/TSID) to Traffic Class(TC).
/* Kevin[2006/11/08]: Convert the User Priority/TS Identifier to Traffic Class(TC)
 * "Traffic Class" is a terminology which is used to classify SW(driver) resource,
 * it is NOT "Traffic Category" which metioned on 802.11e.
 *
 * The mapping of convention is :
 *
 *  aucPriorityParam2TC(UP/TSID) -> Traffic Class(TC) -> AC/TS Queue
 *  ^^^^^^^^^^^^^^^^^^^^^^^^^^^^    ^^^^^^^^^^^^^^^^^    ^^^^^^^^^^^
 *          Classifier                SW Resource          HW Queue
 */
            if ((prPacketInfo->fgIs1x) &&
                (!privacyTransmitKeyExist(prAdapter))) {
                ucTC = TCM; /* The 802.1x packet before group key handshake, use AC4 */
            }
            else{
                if (prAdapter->rBssInfo.fgIsWmmAssoc) {
                    ucTC = aucPriorityParam2TC[prPacketInfo->ucTID];
                }
                else {
                    ucTC = TC1; /* When associated with non-QoS AP, set ucTC to TC1 for all packets. */
                }
            }

#if CFG_IBSS_POWER_SAVE
            //4 <2> If we are in IBSS and also in Power Save Mode.
            if (PM_IS_UNDER_IBSS_POWER_SAVE_MODE(prAdapter)) { /* If IBSS-PS is applied */
                P_STA_INFO_T prStaInfo = &prAdapter->rStaInfo;

                /*  =============================================================
                 *      Acquire Power Control within the submodule.
                 *
                 *    This is done for solely optimization for power consumption,
                 *  and modules need to concern whether to acquire power control
                 *  or not for their operation depends on if HW access is needed.
                 *  =============================================================
                 */
                ARB_TEST_AND_GET_POWER_CONTROL_FROM_PM_IN_TX_PATH(prAdapter);


                // notice mgmt layer for TX request, few PS-related operation should
                // be done beforehand
                pmEnableIbssPsTx(prAdapter);

                ASSERT(ucTC != TCS0); // NOTE(Kevin): not support TSPEC for AdHoc yet.

                //4 <2.A> Enqueue Process for B/MCAST frame.
                if ((prPacketInfo->pucDestAddr) &&
                    IS_BMCAST_MAC_ADDR(prPacketInfo->pucDestAddr)) {
                    // May acquire Spin Lock here.

                    ucControlFlag |= MSDU_INFO_CTRL_FLAG_BMCAST;

                    if ((!prStaInfo->fgIsAllAdhocStaAwake) ||
                        QUEUE_IS_NOT_EMPTY(&prStaInfo->arGcStaWaitQueue[ucTC]) ||
                        ((prMsduInfo = nicTxAllocMsduInfo(prAdapter, ucTC)) == (P_MSDU_INFO_T)NULL) ) {

                        prQueueEntry = (P_QUE_ENTRY_T)
                            KAL_GET_PKT_QUEUE_ENTRY(prPacketInfo->prPacket);

                        QUEUE_INSERT_TAIL(&prStaInfo->arGcStaWaitQueue[ucTC],
                                          prQueueEntry);
                    }
                    // May release Spin Lock here.
                }
                //4 <2.B> Enqueue Process for UCAST frame of IBSS member
                else if ((prStaRec = staRecGetStaRecordByAddr(prAdapter, prPacketInfo->pucDestAddr)) !=
                    (P_STA_RECORD_T)NULL) {


                    // May acquire Spin Lock here.
                    if (!(prStaRec->fgIsAdhocStaAwake || prStaInfo->fgIsAllAdhocStaAwake) ||
                        QUEUE_IS_NOT_EMPTY(&prStaRec->arStaWaitQueue[ucTC]) ||
                        ((prMsduInfo = nicTxAllocMsduInfo(prAdapter, ucTC)) == (P_MSDU_INFO_T)NULL) ) {

                        prQueueEntry = (P_QUE_ENTRY_T)
                            KAL_GET_PKT_QUEUE_ENTRY(prPacketInfo->prPacket);

                        QUEUE_INSERT_TAIL(&prStaRec->arStaWaitQueue[ucTC],
                                          prQueueEntry);
                    }
                    // May release Spin Lock here.
                }
                //4 <2.C> Enqueue Process for UCAST frame of unknown IBSS member
                else {
                    /* Try to send this packet anyway unless lack of SW resource */
                    prOsSendQueue = &prTxCtrl->arTcQPara[ucTC].rOsSendQueue;


                    // May acquire Spin Lock here.
                    if (QUEUE_IS_NOT_EMPTY(prOsSendQueue) ||
                        ((prMsduInfo = nicTxAllocMsduInfo(prAdapter, ucTC)) == (P_MSDU_INFO_T)NULL)) {

                        prQueueEntry = (P_QUE_ENTRY_T)
                            KAL_GET_PKT_QUEUE_ENTRY(prPacketInfo->prPacket);

                        QUEUE_INSERT_TAIL(prOsSendQueue, prQueueEntry);

                        prTxCtrl->fgIsPacketInOsSendQueue = TRUE;
                    }
                    // May release Spin Lock here.
                }
            }
            //4 <3> If we are in IBSS but not in Power Save Mode
            //4 <4> If we are in INFRASTRUCTURE
            else
#endif /* CFG_IBSS_POWER_SAVE */
            {
                prOsSendQueue = &prTxCtrl->arTcQPara[ucTC].rOsSendQueue;

/* Beginning of Session of SW Resource Allocation */
                if (QUEUE_IS_NOT_EMPTY(prOsSendQueue) ||
                    ((ucTC != TCM) && (prTxCtrl->ucTxNonEmptyACQ & BITS(AC0, AC3))) ||
                    ((prMsduInfo = nicTxAllocMsduInfo(prAdapter, ucTC)) == (P_MSDU_INFO_T)NULL)) {

                    prQueueEntry = (P_QUE_ENTRY_T)
                        KAL_GET_PKT_QUEUE_ENTRY(prPacketInfo->prPacket);

                    QUEUE_INSERT_TAIL(prOsSendQueue, prQueueEntry);

                    prTxCtrl->fgIsPacketInOsSendQueue = TRUE;
                }
/* End of Session of SW Resource Allocation */

            }

            /* We put "break" outside above if() condition for adding SPIN_LOCK for
             * ATOMIC operation if necessary.
             * ATOMIC - "Check Queue, Acquire MSDU_INFO and Enqueue Operation."
             */
            if (!prMsduInfo) {

                if (ucTC == TCM) {
                    /* Ideally the 802.1x frame and mgmt frame should < CFG_MAX_NUM_MSDU_INFO_FOR_TCM,
                     * assert if no msduInfo for 802.1x.
                     */
                    ASSERT(0);
                }

                rStatus = WLAN_STATUS_PENDING;
                break;
            }

            if (
#if SUPPORT_WAPI
                (!prAdapter->fgUseWapi) &&
#endif
                (prPacketInfo->fgIs1x) && (prAdapter->rConnSettings.eAuthMode <= AUTH_MODE_AUTO_SWITCH)){
                    ucControlFlag |= MSDU_INFO_CTRL_FLAG_DISABLE_PRIVACY_BIT;

                if (prAdapter->rBssInfo.fgIsWmmAssoc) {
                    u2EstimatedFrameLen = WLAN_MAC_HEADER_QOS_LEN + \
                                          LLC_LEN + \
                                          prPacketInfo->u2PayloadLength;
                }
                else {
                    u2EstimatedFrameLen = WLAN_MAC_HEADER_LEN + \
                                          LLC_LEN + \
                                          prPacketInfo->u2PayloadLength;
                }

                prMgtPacket = mgtBufAllocateMgtPacket(prAdapter, u2EstimatedFrameLen);
                if (!prMgtPacket) {
                    /* Do assert here for advance check ??? */
                    //WARNLOG(("No buffer for NULL frame\n"));
                    nicTxReturnMsduInfo(prAdapter, prMsduInfo);

                    prOsSendQueue = &prTxCtrl->arTcQPara[ucTC].rOsSendQueue;

                    prQueueEntry = (P_QUE_ENTRY_T)
                        KAL_GET_PKT_QUEUE_ENTRY(prPacketInfo->prPacket);

                    QUEUE_INSERT_TAIL(prOsSendQueue, prQueueEntry);

                    prTxCtrl->fgIsPacketInOsSendQueue = TRUE;

                    rStatus = WLAN_STATUS_PENDING;
                    break;
                }

                nicCompose802_11DataFrame(prAdapter,
                                          MGT_PACKET_GET_BUFFER(prMgtPacket),
                                          prPacketInfo->ucTID,
                                          FALSE,
                                          prPacketInfo->prPacket,
                                          &ucWlanHeaderLen);

                mgtPacketPut(prMgtPacket, u2EstimatedFrameLen);

                prPacketInfo->fgIs802_11 = TRUE;

                MSDU_INFO_OBJ_INIT(prMsduInfo, \
                                   TRUE, \
                                   TRUE, \
                                   (PVOID)prMgtPacket, \
                                   prPacketInfo->ucTID, \
                                   ucTC, \
                                   (UINT_8)ucWlanHeaderLen, \
                                   LLC_LEN + prPacketInfo->u2PayloadLength, \
                                   ucControlFlag, \
                                   NULL, \
                                   KAL_GET_PKT_ARRIVAL_TIME(prPacketInfo->prPacket), \
                                   prStaRec \
                                   );

                kalSendComplete(prAdapter->prGlueInfo, prPacketInfo->prPacket, WLAN_STATUS_SUCCESS);
                prPacketInfo->prPacket = NULL;

                if ((rStatus = arbFsmRunEventTxMmpdu(prAdapter,prMsduInfo)) != WLAN_STATUS_PENDING) {

                    if(rStatus != WLAN_STATUS_SUCCESS){
                        mgtBufFreeMgtPacket(prAdapter, prMgtPacket);

                        nicTxReturnMsduInfo(prAdapter, prMsduInfo);

                        DBGLOG(TX, ERROR, ("Send Legacy 802.1x frame fail.\n"));

                        /* NOTE(Kevin): here we need to return SUCCESS instead of FAILURE
                         * because we already do kalSendComplete() earlier.
                         */
                        rStatus = WLAN_STATUS_SUCCESS;
                    }
                }
            }
            else {
                #if SUPPORT_WAPI
                if (prAdapter->fgUseWapi) {
                    prPacketInfo->fgIs802_11 = TRUE;
                    if (prPacketInfo->fgIs1x)
                        ucControlFlag |= MSDU_INFO_CTRL_FLAG_DISABLE_PRIVACY_BIT;
                }
                #endif
                //4 <5> Initialization of MSDU_INFO_T.
                MSDU_INFO_OBJ_INIT(prMsduInfo, \
                                   prPacketInfo->fgIs802_11, \
                                   FALSE, \
                                   (PVOID)prPacketInfo->prPacket, \
                                   prPacketInfo->ucTID, \
                                   ucTC, \
                                   prPacketInfo->ucMacHeaderLength, \
                                   prPacketInfo->u2PayloadLength, \
                                   ucControlFlag, \
                                   NULL, \
                                   KAL_GET_PKT_ARRIVAL_TIME(prPacketInfo->prPacket), \
                                   prStaRec \
                                   );

                //4 <6> Process MSDU Integrity Protection & Fragmentation
                if ((rStatus = txProcessMSDU(prAdapter, prMsduInfo)) == WLAN_STATUS_FAILURE) {
                    nicTxReturnMsduInfo(prAdapter, prMsduInfo);
                    break;
                }


                //4 <7> Forward MSDU_INFO_T to NIC Layer
#if CFG_SDIO_TX_ENHANCE
                rStatus = nicTxService(prAdapter, prMsduInfo, FALSE);
#else
                rStatus = nicTxService(prAdapter, prMsduInfo);
#endif /* CFG_SDIO_TX_ENHANCE */
            }
        }
        else {
           TX_INC_CNT(prTxCtrl, TX_OS_MSDU_DROP_COUNT);
        }

    }
    while (FALSE);


    return rStatus;
} /* end of arbFsmRunEventTxMsduFromOs() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will indicate an Event of "TX Packet from Internal Protocol
*        Stack" to ARB FSM.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
* \param[in] prMsduInfo     Pointer of MSDU_INFO_T.
*
* \retval WLAN_STATUS_PENDING   : MSDU can send to HW TX FIFO without sendComplete
*                                 (pending for TX_DONE event).
*                                 or wait in arTxQPara[].rSendWaitQueue.
* \retval WLAN_STATUS_FAILURE   : Get failure while access HW TX FIFO or rejected.
* \retval WLAN_STATUS_RESOURCES : ARB is not ready to send, please wait.
* \retval WLAN_STATUS_SUCCESS   : MSDU was send to HW TX FIFO and also do sendComplete
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
arbFsmRunEventTxMmpdu (
    IN P_ADAPTER_T      prAdapter,
    IN P_MSDU_INFO_T    prMsduInfo
    )
{
    //P_ARB_INFO_T prArbInfo = &prAdapter->rArbInfo;
    P_TX_CTRL_T prTxCtrl;
    WLAN_STATUS rStatus;

    ASSERT(prAdapter);
    ASSERT(prMsduInfo);

    prTxCtrl = &prAdapter->rTxCtrl;

    do {

        TX_INC_CNT(prTxCtrl, TX_INTERNAL_MSDU_MMPDU_COUNT);

        /* Process MSDU Integrity Protection & Fragmentation */
        if ((rStatus = txProcessMSDU(prAdapter, prMsduInfo)) == WLAN_STATUS_FAILURE) {
            break;
        }

#if CFG_SDIO_TX_ENHANCE
        rStatus = nicTxService(prAdapter, prMsduInfo, FALSE);
#else
        rStatus = nicTxService(prAdapter, prMsduInfo);
#endif /* CFG_SDIO_TX_ENHANCE */

    }
    while (FALSE);

    return rStatus;

} /* end of arbFsmRunEventTxMmpdu() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will indicate an Event of "Connection Test" to ARB_FSM.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
arbFsmRunEventConnectionTest (
    IN P_ADAPTER_T prAdapter
    )
{
    P_ARB_INFO_T prArbInfo;
    P_BSS_INFO_T prBssInfo;

    ASSERT(prAdapter);
    prArbInfo = &prAdapter->rArbInfo;
    prBssInfo = &prAdapter->rBssInfo;

    if (prAdapter->eCurrentOPMode == OP_MODE_INFRASTRUCTURE) {
        if (!prArbInfo->fgIsDiagnosingConnection) {
            prArbInfo->fgIsDiagnosingConnection = TRUE;

            DBGLOG(ARB, EVENT, ("\n\nARB EVENT: Beacon Timeout - Begin diagnosing Connection Quality.\n\n"));

            if (pmBeaconTimeoutHandler(prAdapter, arbFsmRunEventConnectionDiagnosis) != WLAN_STATUS_SUCCESS) {
                arbFsmRunEventAbort(prAdapter, FALSE);
            }
        }
    }
    else if (prAdapter->eCurrentOPMode == OP_MODE_IBSS) {

        if (prAdapter->eConnectionState == MEDIA_STATE_CONNECTED) {

            if (!prAdapter->fgIsIBSSBeaconTimeoutAlarm) {
                GET_CURRENT_SYSTIME(&prAdapter->rIBSSLastBeaconTimeout);

                prAdapter->fgIsIBSSBeaconTimeoutAlarm = TRUE;

                DBGLOG(ARB, EVENT, ("\n\nARB EVENT: First Beacon Timeout Alarm!\n\n"));

            }
            else {
                OS_SYSTIME rCurrentTime;
                OS_SYSTIME rTimeout;


                GET_CURRENT_SYSTIME(&rCurrentTime);

                rTimeout = (TU_TO_SYSTIME(prAdapter->rBssInfo.u2BeaconInterval * BEACON_TIMEOUT_COUNT_ADHOC) +
                            SEC_TO_SYSTIME(BEACON_TIMEOUT_GUARD_TIME_SEC));

                if (CHECK_FOR_TIMEOUT(rCurrentTime,
                                      prAdapter->rIBSSLastBeaconTimeout,
                                      rTimeout)) {

                    prAdapter->rIBSSLastBeaconTimeout = rCurrentTime;

                    DBGLOG(ARB, EVENT, ("\n\nARB EVENT: Another Beacon Timeout Alarm - Detect next Alarm!\n\n"));
                }
                else {

                    DBGLOG(ARB, EVENT, ("\n\nARB EVENT: Continuous Beacon Timeout Alarm - do Abort immediately for Ad-Hoc!\n\n"));

                    /* CR1790: only remove this record when beacon lost is confirmed */
                    scanRemoveBssDescByBssid(prAdapter, prBssInfo->aucBSSID);

                    /* The Event of Beacon lost was confirmed, indicate that media state
                     * is disconnected immediately.
                     * http://msdn.microsoft.com/en-us/library/aa504134.aspx
                     */
                    arbFsmRunEventAbort(prAdapter, FALSE);
                }
            }
        }
    }

    return;
} /* end of arbFsmRunEventConnectionTest() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will indicate an Event of "Connection Diagnosis" to ARB_FSM
*        for checking the result of Connection Diagnosis.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
* \param[in] prMsduInfo     Pointer of MSDU_INFO_T.
* \param[in] rStatus        WLAN_STATUS of TX Done.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
arbFsmRunEventConnectionDiagnosis (
    IN P_ADAPTER_T prAdapter,
    IN P_MSDU_INFO_T prMsduInfo,
    IN WLAN_STATUS rStatus
    )
{
    P_ARB_INFO_T prArbInfo;
    P_BSS_INFO_T prBssInfo;
    P_WLAN_MAC_HEADER_T prWlanFrame;

    ASSERT(prAdapter);
    ASSERT(prMsduInfo);

    prArbInfo = &prAdapter->rArbInfo;
    prBssInfo = &prAdapter->rBssInfo;

    if (rStatus == WLAN_STATUS_FAILURE) {
        if (prAdapter->eConnectionState == MEDIA_STATE_CONNECTED) {

            /* NOTE(Kevin): during roaming, we may encounter Beacon Lost Event from
             * previous AP. So we should check the BSSID again, to avoid such event
             * after we connect to the new AP.
             */
            if (prMsduInfo->fgIsFromInternalProtocolStack) {
                prWlanFrame = (P_WLAN_MAC_HEADER_T)(MGT_PACKET_GET_BUFFER(prMsduInfo->pvPacket));

                if (EQUAL_MAC_ADDR(prWlanFrame->aucAddr3, prBssInfo->aucBSSID)) {

                    DBGLOG(ARB, EVENT, ("\n\nARB EVENT: Beacon Timeout - Connection Quality is poor, do Abort !\n\n"));

                    /* The Event of Beacon lost was confirmed, delay the media state
                     * indication if connected.
                     */
                    // NOTE: CM suggest to remove current associated one to avoid redundant Auth retry.
                    scanRemoveBssDescByBssid(prAdapter, prBssInfo->aucBSSID);

                    arbFsmRunEventAbort(prAdapter, TRUE);
                }
            }
#if DBG
            else {
                DBGLOG(ARB, ERROR,
                    ("This NULL Frame is not from Internal Protocol Stack.\n"));
                ASSERT(0);
                return;
            }
#endif /* DBG */

        }
    }
#if DBG
    else {
        DBGLOG(ARB, EVENT, ("\n\nARB EVENT: Beacon Timeout False Alarm - Connection Quality is OK!\n\n"));
    }
#endif /* DBG */

    prArbInfo->fgIsDiagnosingConnection = FALSE;

    return;
} /* end of arbFsmRunEventConnectionDiagnosis() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will indicate an Event of "Rx Class Error" to ARB_FSM for
*        JOIN Module.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
* \param[in] prStaRec       Pointer to STA_RECORD_T.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
arbFsmRunEventJoinRxClassError (
    IN P_ADAPTER_T prAdapter,
    IN P_STA_RECORD_T prStaRec
    )
{
    ASSERT(prAdapter);
    ASSERT(prStaRec);

    DBGLOG(ARB, EVENT, ("\n\nARB EVENT: Rx Class Error.\n\n"));

    if (prStaRec->ucStaState == STA_STATE_1) {
        authSendDeauthFrame(prAdapter,
                            prStaRec->aucMacAddr,
                            REASON_CODE_CLASS_3_ERR,
                            AC3,
                            (PFN_TX_DONE_HANDLER)0);
    }
    else {
        assocSendDisAssocFrame(prAdapter,
                               prStaRec->aucMacAddr,
                               REASON_CODE_CLASS_3_ERR,
                               (PFN_TX_DONE_HANDLER)0);
    }

    return;
} /* end of arbFsmRunEventJoinRxClassError() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will indicate an Event of "RX Authentication/Association Frame"
*        to ARB FSM for JOIN Module.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
* \param[in] prSwRfb        Pointer to RX Buffer.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
arbFsmRunEventJoinRxAuthAssoc (
    IN P_ADAPTER_T prAdapter,
    IN P_SW_RFB_T prSwRfb
    )
{
    P_ARB_INFO_T prArbInfo;
    ENUM_ARB_STATE_T eNextState;
    BOOLEAN fgIsTransition = (BOOLEAN)FALSE;

    ASSERT(prAdapter);
    ASSERT(prSwRfb);

    prArbInfo = &prAdapter->rArbInfo;
    eNextState = prArbInfo->eCurrentState;

    DBGLOG(ARB, EVENT, ("\n\nARB EVENT: Join - Rx done of Auth /Assoc Frame.\n\n"));

    switch(prArbInfo->eCurrentState) {
    case ARB_STATE_JOIN:
        {   WLAN_STATUS rStatus;

            rStatus = joinFsmRunEventRxAuthAssoc(prAdapter, prSwRfb);

            if (rStatus == WLAN_STATUS_FAILURE) {

                if (prAdapter->eConnectionState == MEDIA_STATE_DISCONNECTED) {
                    ARB_STATE_TRANSITION(prAdapter, JOIN, SEARCH);
                }
                else {
                    ARB_STATE_TRANSITION(prAdapter, JOIN, NORMAL_TR);
                }
            }
            else if (rStatus == WLAN_STATUS_SUCCESS) {
                P_CONNECTION_SETTINGS_T prConnSettings = &prAdapter->rConnSettings;

                /* NOTE(Kevin): Once we've joined with an AP, update the eOPMode
                 * for avoiding to switch to IBSS Mode later and also speedup Roaming.
                 */
                prConnSettings->eOPMode = NET_TYPE_INFRA;

                ARB_STATE_TRANSITION(prAdapter, JOIN, NORMAL_TR);

                //secFsmRunEventAbort(prAdapter);
            }
        }
        break;

    default:
        break;
    }

    /* Call arbFsmSteps() when we are going to change ARB STATE */
    if (prArbInfo->eCurrentState != eNextState) {
        arbFsmSteps(prAdapter, eNextState);
    }

    return;
} /* end of arbFsmRunEventJoinRxAuthAssoc() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will indicate an Event of "RX Auth/Assoc Response Frame Time-Out"
*        to ARB FSM for JOIN Module.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
arbFsmRunEventJoinRxTimeOut (
    IN P_ADAPTER_T prAdapter
    )
{
    P_ARB_INFO_T prArbInfo;
    ENUM_ARB_STATE_T eNextState;
    BOOLEAN fgIsTransition = (BOOLEAN)FALSE;

    ASSERT(prAdapter);

    prArbInfo = &prAdapter->rArbInfo;
    eNextState = prArbInfo->eCurrentState;

    DBGLOG(ARB, EVENT, ("\n\nARB EVENT: Join - Rx timeout of Auth/Assoc Frame.\n\n"));

    if (prArbInfo->eCurrentState == ARB_STATE_JOIN) {
        WLAN_STATUS rStatus;

        rStatus = joinFsmRunEventRxRespTimeOut(prAdapter);

        if (rStatus == WLAN_STATUS_FAILURE) {

            if (prAdapter->eConnectionState == MEDIA_STATE_DISCONNECTED) {
                ARB_STATE_TRANSITION(prAdapter, JOIN, SEARCH);
            }
            else {
                ARB_STATE_TRANSITION(prAdapter, JOIN, NORMAL_TR);
            }
        }
    }

    /* Call arbFsmSteps() when we are going to change ARB STATE */
    if (prArbInfo->eCurrentState != eNextState) {
        arbFsmSteps(prAdapter, eNextState);
    }

    return;
} /* end of arbFsmRunEventJoinRxTimeOut() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will indicate an Event of "TX Auth/Assoc Frame Time-Out"
*        to ARB FSM for JOIN Module.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
arbFsmRunEventJoinTxTimeOut (
    IN P_ADAPTER_T prAdapter
    )
{
    P_ARB_INFO_T prArbInfo;
    ENUM_ARB_STATE_T eNextState;
    BOOLEAN fgIsTransition = (BOOLEAN)FALSE;

    ASSERT(prAdapter);

    prArbInfo = &prAdapter->rArbInfo;
    eNextState = prArbInfo->eCurrentState;

    DBGLOG(ARB, EVENT, ("\n\nARB EVENT: Join - Tx timeout of Auth/Assoc Frame.\n\n"));

    if (prArbInfo->eCurrentState == ARB_STATE_JOIN) {
        WLAN_STATUS rStatus;

        rStatus = joinFsmRunEventTxReqTimeOut(prAdapter);

        if (rStatus == WLAN_STATUS_FAILURE) {

            if (prAdapter->eConnectionState == MEDIA_STATE_DISCONNECTED) {
                ARB_STATE_TRANSITION(prAdapter, JOIN, SEARCH);
            }
            else {
                ARB_STATE_TRANSITION(prAdapter, JOIN, NORMAL_TR);
            }
        }
    }

    /* Call arbFsmSteps() when we are going to change ARB STATE */
    if (prArbInfo->eCurrentState != eNextState) {
        arbFsmSteps(prAdapter, eNextState);
    }

    return;
} /* end of arbFsmRunEventJoinTxTimeOut() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will indicate an Event of "TX Auth/Assoc Frame Done"
*        to ARB FSM for JOIN Module.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
* \param[in] prMsduInfo     Pointer of MSDU_INFO_T.
* \param[in] rTxDoneStatus  WLAN_STATUS of TX Done.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
arbFsmRunEventJoinTxDone (
    IN P_ADAPTER_T  prAdapter,
    IN P_MSDU_INFO_T prMsduInfo,
    IN WLAN_STATUS rTxDoneStatus
    )
{
    P_ARB_INFO_T prArbInfo;
    ENUM_ARB_STATE_T eNextState;
    BOOLEAN fgIsTransition = (BOOLEAN)FALSE;

    ASSERT(prAdapter);
    ASSERT(prMsduInfo);

    prArbInfo = &prAdapter->rArbInfo;
    eNextState = prArbInfo->eCurrentState;

    DBGLOG(ARB, EVENT, ("\n\nARB EVENT: Join - Tx done of Auth/Assoc Frame.\n\n"));

    if (prArbInfo->eCurrentState == ARB_STATE_JOIN) {
        WLAN_STATUS rStatus;

        rStatus = joinFsmRunEventTxDone(prAdapter, prMsduInfo, rTxDoneStatus);

        if (rStatus == WLAN_STATUS_FAILURE) {

            if (prAdapter->eConnectionState == MEDIA_STATE_DISCONNECTED) {
                ARB_STATE_TRANSITION(prAdapter, JOIN, SEARCH);
            }
            else {
                ARB_STATE_TRANSITION(prAdapter, JOIN, NORMAL_TR);
            }
        }
    }


    /* Call arbFsmSteps() when we are going to change ARB STATE */
    if (prArbInfo->eCurrentState != eNextState) {
        arbFsmSteps(prAdapter, eNextState);
    }

    return;
} /* end of arbFsmRunEventJoinTxDone() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will indicate an Event of "Join Time-Out" to ARB FSM for
*        JOIN Module.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
arbFsmRunEventJoinFailureTimeOut (
    IN P_ADAPTER_T prAdapter
    )
{
    P_ARB_INFO_T prArbInfo;
    ENUM_ARB_STATE_T eNextState;
    BOOLEAN fgIsTransition = (BOOLEAN)FALSE;

    ASSERT(prAdapter);

    prArbInfo = &prAdapter->rArbInfo;
    eNextState = prArbInfo->eCurrentState;

    DBGLOG(ARB, EVENT, ("\n\nARB EVENT: Join process Time Out.\n\n"));

    if (prArbInfo->eCurrentState == ARB_STATE_JOIN) {
        WLAN_STATUS rStatus;

        rStatus = joinFsmRunEventJoinTimeOut(prAdapter);

        if (rStatus == WLAN_STATUS_FAILURE) {

            if (prAdapter->eConnectionState == MEDIA_STATE_DISCONNECTED) {
                ARB_STATE_TRANSITION(prAdapter, JOIN, SEARCH);
            }
            else {
                ARB_STATE_TRANSITION(prAdapter, JOIN, NORMAL_TR);
            }
        }
    }

    /* Call arbFsmSteps() when we are going to change ARB STATE */
    if (prArbInfo->eCurrentState != eNextState) {
        arbFsmSteps(prAdapter, eNextState);
    }

    return;
} /* end of arbFsmRunEventJoinFailureTimeOut() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will indicate an Event of "Set Disassociation" to ARB FSM for
*        JOIN Module from OID.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
arbFsmRunEventJoinDisassoc (
    IN P_ADAPTER_T prAdapter
    )
{
    P_ARB_INFO_T prArbInfo;
    ENUM_ARB_STATE_T eNextState;

    DEBUGFUNC("arbFsmRunEventJoinDisassoc");

    ASSERT(prAdapter);
    prArbInfo = &prAdapter->rArbInfo;
    eNextState = prArbInfo->eCurrentState;

    DBGLOG(ARB, EVENT, ("\n\nARB EVENT: Disassociate !.\n\n"));

    switch(prArbInfo->eCurrentState) {

    case ARB_STATE_SCAN:
        {
            ASSERT(prArbInfo->ePreviousState == ARB_STATE_NORMAL_TR);

            /* abort scan */
            scanFsmRunEventScanAbort(prAdapter);

            /* abort associated PM functions (especially during online scan) */
            pmFsmRunEventAbort(prAdapter);

            nicRxReleasePrivilegeOfRxQue(prAdapter,
                                         FALSE,
                                         FALSE);

            nicTxReleasePrivilegeOfTxQue(prAdapter,
                                         (UINT_8)TXQ_MGMT_MASK);

            eNextState = ARB_STATE_NORMAL_TR;
        }
        break;

    case ARB_STATE_JOIN:
        {
            joinFsmRunEventAbort(prAdapter);

            eNextState = ARB_STATE_NORMAL_TR;
        }
        break;

    case ARB_STATE_DEDICATED_MEASUREMEMT:
        {
            /* TODO(Kevin):
             * 1. Issue Stop Measurement Event
             */
            ASSERT(prArbInfo->ePreviousState == ARB_STATE_NORMAL_TR);

            eNextState = ARB_STATE_NORMAL_TR;
        }
        break;

    default:
        break;
    }

    /* Call arbFsmSteps() when we are going to change ARB STATE */
    if (prArbInfo->eCurrentState != eNextState) {
        arbFsmSteps(prAdapter, eNextState);
    }

    /* Flush TX Queue in order to send Disassociate frame */
    nicTxFlushStopQueues(prAdapter, TXQ_DATA_MASK | TXQ_MGMT_MASK, 0x0 /*(UINT_8)NULL*/);

    assocSendDisAssocFrame(prAdapter,
                               prAdapter->rBssInfo.aucBSSID,
                               REASON_CODE_DEAUTH_LEAVING_BSS,
                               (PFN_TX_DONE_HANDLER)0);

    /* Wait for disassoc frame tx done */
    kalMdelay(2);

    prAdapter->rConnSettings.fgIsConnReqIssued = FALSE;
    arbFsmRunEventAbort(prAdapter, FALSE);

    return;

} /* end of arbFsmRunEventJoinDisassoc() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will indicate an Event of "Pairwise key installed" to SEC FSM.
*
* \param[in] prAdapter      Pointer of Adapter Data Structure
* \param[in] prKey          Pointer of Pairewise Key
*
* \retval WLAN_STATUS_SUCCESS The key can be installed to HW
* \retval WLAN_STATUS_INVALID_DATA The key can not be installed to HW
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
arbFsmRunEventSecKeyInstalled (
    IN P_ADAPTER_T          prAdapter,
    IN P_PARAM_KEY_T        prKey
    )
{
    ASSERT(prAdapter);
    ASSERT(prKey);

    DBGLOG(ARB, EVENT, ("\n\nARB EVENT: Security - Key installed.\n\n"));

    return privacySetKeyEntry(prAdapter, prKey);

} /* end of arbFsmRunEventSecKeyInstalled() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will indicate an Event of "Deauth callback".
*        The sec fsm will compose a de-auth frame and
*        register the callback function
*
* \param[in] prAdapter      Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
arbFsmRunEventSecDeauthDone (
    IN P_ADAPTER_T      prAdapter,
    IN P_MSDU_INFO_T    prMsduInfo,
    IN WLAN_STATUS      rTxDoneStatus
    )
{
    DEBUGFUNC("arbFsmRunEventSecDeauthDone");


    ASSERT(prAdapter);
    ASSERT(prMsduInfo);

    DBGLOG(ARB, EVENT, ("\n\nARB EVENT: Security - Tx done of Deauth Frame.\n\n"));

    secFsmRunEventDeauthTxDone(prAdapter);

    return;
} /* end of arbFsmRunEventSecDeauthDone() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will indicate an Event of "End of Counter Measure" to ARB FSM.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
arbFsmRunEventConnectionEndOfCounterMeasure (
    IN P_ADAPTER_T  prAdapter
    )
{
    P_ARB_INFO_T     prArbInfo;
    ENUM_ARB_STATE_T eNextState;

    ASSERT(prAdapter);

    prArbInfo = &prAdapter->rArbInfo;
    eNextState = prArbInfo->eCurrentState;

    DBGLOG(ARB, EVENT, ("\n\nARB EVENT: Security - End of Counter Measure.\n\n"));

    ASSERT(prArbInfo->eCurrentState == ARB_STATE_STANDBY);

    prAdapter->fgCounterMeasure = FALSE;

    arbFsmSteps(prAdapter, eNextState);

    return;
} /* end of arbFsmRunEventConnectionEndOfCounterMeasure() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will indicate an Event of "Counter Measure" to ARB FSM.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
*
* \return (none)
*
* \note after sec fsm run over the counter Measure handle (from deauth to idle)
*       use this to info the arbiter add the sta to black list for 60 sec
*/
/*----------------------------------------------------------------------------*/
VOID
arbFsmRunEventConnectionStartCounterMeasure (
    IN P_ADAPTER_T  prAdapter
    )
{
    ASSERT(prAdapter);

    DBGLOG(ARB, EVENT, ("\n\nARB EVENT: Security - Begin of Counter Measure.\n\n"));

    if (prAdapter->eConnectionState == MEDIA_STATE_CONNECTED) {
        /* This do almost the same as becon lost, rcv deauth,
           spicial add the ap to black list for 60 sec */
        /* <Todo> The event is send to os by arbiter */

        prAdapter->fgCounterMeasure = TRUE;
        arbFsmRunEventAbort(prAdapter, FALSE);
    }
    else {
        ASSERT(FALSE);
    }

    return;
} /* end of arbFsmRunEventConnectionStartCounterMeasure() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will indicate an Event of "Tx Flow Control for Port Control"
*        to ARB FSM to prevent encrypting the EAPOL frame of GROUP KEY UPDATE.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
* \param[in] fgClearSignal  Det TRUE to clear the signal at nicTxSetSignalWhenFifoNonEmpty
*
* \retval TRUE The outgoing EAPOL frame may still in TX FIFO, wait for it empty.
* \retval FALSE TX FIFO is alreay empty.
*/
/*----------------------------------------------------------------------------*/
BOOLEAN
arbFsmRunEventSecTxFlowControl (
    IN P_ADAPTER_T  prAdapter,
    IN BOOLEAN      fgClearSignal
    )
{
    ASSERT(prAdapter);

    DBGLOG(ARB, EVENT, ("\n\nARB EVENT: Security - Tx Flow Control.\n\n"));

    return nicTxSetSignalWhenFifoNonEmpty(prAdapter, FALSE);

} /* end of arbFsmRunEventSecTxFlowControl() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will indicate an Event of "Tx FIFO Empty for Port Control"
*        to ARB FSM to know the EAPOL Group Key handshaking was complete.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
arbFsmRunEventSecTxFIFOEmpty (
    IN P_ADAPTER_T  prAdapter
    )
{
    ASSERT(prAdapter);

    DBGLOG(ARB, EVENT, ("\n\nARB EVENT: Security - Tx Fifo empty.\n\n"));

    if (TRUE /* check state */) {
        secFsmRunEventFifoEmpty(prAdapter);
    }

    return;
} /* end of arbFsmRunEventSecTxFIFOEmpty() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function is called to abort the wait EAPoL frame
*
* \param[in] prAdapter      Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
arbFsmRunEventSecCancelEAPoLTimer (
    IN P_ADAPTER_T          prAdapter
    )
{
    ASSERT(prAdapter);

    DBGLOG(ARB, EVENT, ("\n\nARB EVENT: Security - Wait EAPoL Timeout.\n\n"));

    secFsmRunEventEapolTxDone(prAdapter);

    return;
} /* end of arbFsmRunEventSecCancelEAPoLTimer() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function is called to wait a duration to indicate the pre-auth AP candicate
*
* \param[in] prAdapter      Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
arbFsmRunEventSecIndicatePmkidCand (
    IN P_ADAPTER_T          prAdapter
    )
{
    ASSERT(prAdapter);

    DBGLOG(ARB, EVENT, ("\n\nARB EVENT: Security - Time to indicate the PMKID cand.\n\n"));

    /* Todo: use function */
    //4   pmkid indicate
    /* If the authentication mode is WPA2 and indication PMKID flag
       is available, then we indicate the PMKID candidate list to NDIS and
       clear the flag, indicatePMKID */

    if (prAdapter->rConnSettings.eAuthMode == AUTH_MODE_WPA2 &&
        prAdapter->rSecInfo.fgIndicatePMKID) {
        prAdapter->rSecInfo.fgIndicatePMKID = FALSE;
        rsnGeneratePmkidIndication(prAdapter, 0);
    }

    return;
} /* end of arbFsmRunEventSecIndicatePmkidCand() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function is called while the 60 sec passed after "Counter Measure"
*
* \param[in] prAdapter      Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
arbFsmRunEventSecCounterMeasureDone (
    IN P_ADAPTER_T          prAdapter
    )
{
    ASSERT(prAdapter);

    DBGLOG(ARB, EVENT, ("\n\nARB EVENT: Security - Counter Measure period End.\n\n"));

    secFsmRunEventEndOfCounterMeasure(prAdapter);

    return;
} /* end of arbFsmRunEventSecCounterMeasureDone() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function is used to do scan request.
*
* \param[in] prAdapter Pointer of Adapter Data Structure
* \param[in] prScanReqConfig Pointer of all the necessary parameter for scan request
* \param[in] fgForceToScanInActiveMode force to do scan even it is under active mode
*                                  in infrastructure mode
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_FAILURE
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
arbFsmRunEventScanRequest (
    IN P_ADAPTER_T prAdapter,
    IN P_SCAN_REQ_CONFIG_T prScanReqConfig,
    IN BOOLEAN fgForceToScanInActiveMode
    )
{
    P_ARB_INFO_T prArbInfo;
    P_SCAN_INFO_T prScanInfo;
    P_SCAN_CONFIG_T prScanCfg;
    BOOLEAN fgIsTransition = (BOOLEAN)FALSE;
    ENUM_ARB_STATE_T eNextState;
    BOOLEAN fgIsUnderActiveModeBeforeScan = FALSE;
    OS_SYSTIME rCurrentSysTime;

    DEBUGFUNC("arbFsmRunEventScanRequest");

    ASSERT(prAdapter);

    prArbInfo = &prAdapter->rArbInfo;
    prScanInfo = &prAdapter->rScanInfo;
    prScanCfg = &prScanInfo->rScanConfig;
    eNextState = prArbInfo->eCurrentState;

    DBGLOG(ARB, EVENT, ("\n\nARB EVENT: Scan request.\n\n"));

    /* Check if it is able to perform scan first.
    */
    if (prAdapter->fgIsBlockToScan) {
		kalIndicateStatusAndComplete(prAdapter->prGlueInfo,
            WLAN_STATUS_SCAN_COMPLETE,
            NULL,
            0);
        return WLAN_STATUS_FAILURE;
    }

    /* Pull it to ARB_STATE_SEARCH first when it's under ARB_STATE_BG_SSID_SCAN.
       This is for WZC scan request
    */
    if (prArbInfo->eCurrentState == ARB_STATE_BG_SSID_SCAN) {
        prArbInfo->fgTryFullScan = TRUE;

        ARB_STATE_TRANSITION(prAdapter, BG_SSID_SCAN, SEARCH);

        /* Call arbFsmSteps() when we are going to change ARB STATE */
        if (prArbInfo->eCurrentState != eNextState) {
            arbFsmSteps(prAdapter, eNextState);
        }
        return WLAN_STATUS_SUCCESS;
    }

    GET_CURRENT_SYSTIME(&rCurrentSysTime);

    /* Force to abort in-completed scan request, and start a new one */
    if (prArbInfo->eCurrentState == ARB_STATE_SCAN) {

        if (CHECK_FOR_TIMEOUT(rCurrentSysTime,
                              prArbInfo->rLastScanRequestTime,
                              SCAN_REQUEST_TIMEOUT_MSEC) && prArbInfo->rLastScanRequestTime) {
            DBGLOG(ARB, WARN, ("Scan is blocked for over %d ms!\n", SCAN_REQUEST_TIMEOUT_MSEC));

            /* it is expected that full scan will break into pieces
               when doing online scan only */
//            ASSERT(prArbInfo->ePreviousState == ARB_STATE_NORMAL_TR);

            if (prArbInfo->ePreviousState == ARB_STATE_NORMAL_TR) {
                scanFsmRunEventScanAbort(prAdapter);

                scanFsmRunEventScanReqCleanUp(prAdapter);

                // switch back to previous state
                ARB_STATE_TRANSITION(prAdapter, SCAN, NORMAL_TR);
            } else {
                DBGLOG(ARB, WARN, ("ARB prevState: %d\n", prArbInfo->ePreviousState));
            }
        }
    }

    /* Only following state can make transition to ARB_STATE_SCAN state */
    if ((prArbInfo->eCurrentState != ARB_STATE_NORMAL_TR) &&
        (prArbInfo->eCurrentState != ARB_STATE_IBSS_ALONE) &&
        (prArbInfo->eCurrentState != ARB_STATE_STANDBY) &&
        (prArbInfo->eCurrentState != ARB_STATE_IDLE)) {
        return WLAN_STATUS_FAILURE;
    }

    if (scanFsmRunEventScanReqSetup(prAdapter, prScanReqConfig) != WLAN_STATUS_SUCCESS) {
        return WLAN_STATUS_FAILURE;
    }


    /* NOTE(Kevin 2007/11/22):
     * The parameter prScanReqConfig is very important to this function call.
     * When prScanReqConfig != NULL, then this event is triggered from OID/IOCTL directly.
     * When prScanReqConfig == NULL, then this event is triggered from
     *     1. Power Save State indication.
     *     2. SCAN Module for "Partial SCAN" & "PS VOIP Partial SCAN method".
     * When this event is triggered from internal, we should already accepted a
     * SCAN request previously.
     */

    //Housekeeping for SCAN result aging func, do it only when (prScanReqConfig != NULL).
    if (prScanReqConfig) {
        scanRemoveBssDescsByPolicy(prAdapter, (SCAN_RM_POLICY_EXCLUDE_CONNECTED | \
                                               SCAN_RM_POLICY_TIMEOUT) );
    }

    switch (prArbInfo->eCurrentState) {
    case ARB_STATE_NORMAL_TR:
        /* If current Operation Mode is Infrastructure mode */
        if (prAdapter->eCurrentOPMode == OP_MODE_INFRASTRUCTURE) {

            if (prScanCfg->eScanMethod == SCAN_METHOD_VOIP_ONLINE_SCAN) {

                /* Trigger from OID/IOCTL directly */
                if (prScanReqConfig != (P_SCAN_REQ_CONFIG_T)NULL) {

                    if (!PM_IS_UNDER_POWER_SAVE_MODE(prAdapter)) {

                        /* Change to PS mode */
                        pmFsmRunEventEnterPowerSaveModeReq(prAdapter,
                            arbFsmRunEventScanSetPsVoipTrap);

                        fgIsUnderActiveModeBeforeScan = TRUE;
                    }
                    else {

                        DBGLOG(ARB, INFO, ("Enable traps for PS VOIP SCAN\n"));

                        NIC_TX_SET_VOIP_SCAN_TRIGGER_EVENT(prAdapter);

                    }
                }
                else { /* Trigger from VOIP SCAN traps */

                    ASSERT(PM_IS_UNDER_POWER_SAVE_MODE(prAdapter));

                    DBGLOG(ARB, INFO, ("Disable traps for PS VOIP SCAN\n"));

                    NIC_TX_UNSET_VOIP_SCAN_TRIGGER_EVENT(prAdapter);

                    /* Trigger SCAN state machine */
                    ARB_STATE_TRANSITION(prAdapter, NORMAL_TR, SCAN);
                }
            }
            else { /* !SCAN_METHOD_VOIP_ONLINE_SCAN */

                if (fgForceToScanInActiveMode) {
                    /* Special considerations of the exception handler on the transmission fail
                       of NULL for entering PS, which allow it to do scan procedure anyway */
                    ARB_STATE_TRANSITION(prAdapter, NORMAL_TR, SCAN);
                }
                else if (!PM_IS_UNDER_POWER_SAVE_MODE(prAdapter)) {
                    /* Change to PS mode */
                    pmFsmRunEventEnterPowerSaveModeReq(prAdapter,
                        arbFsmRunEventScanRequest);

                    fgIsUnderActiveModeBeforeScan = TRUE;
                }
                else {
                    /* Trigger SCAN state machine */
                    ARB_STATE_TRANSITION(prAdapter, NORMAL_TR, SCAN);
                }
            }
        }
        else if (prAdapter->eCurrentOPMode == OP_MODE_IBSS) {
            /* if it is under IBSS mode and not under PS mode */
            if (!PM_IS_UNDER_POWER_SAVE_MODE(prAdapter)) {

                /* Trigger SCAN state machine */
                ARB_STATE_TRANSITION(prAdapter, NORMAL_TR, SCAN);

                fgIsUnderActiveModeBeforeScan = TRUE;
            }
            else {

                /* Trigger SCAN state machine */
                ARB_STATE_TRANSITION(prAdapter, NORMAL_TR, SCAN);
            }
        }
        break;

    case ARB_STATE_IBSS_ALONE:
        /* Trigger SCAN state machine */
        ARB_STATE_TRANSITION(prAdapter, IBSS_ALONE, SCAN);
        break;

    /* NOTE(Kevin): For case if WZC do SCAN while CounterMeasure */
    case ARB_STATE_STANDBY:
        /* Trigger SCAN state machine */
        ARB_STATE_TRANSITION(prAdapter, STANDBY, SCAN);
        break;

    default:
        break;
    }


    /* Call arbFsmSteps() when we are going to change ARB STATE */
    if (prArbInfo->eCurrentState != eNextState) {
        arbFsmSteps(prAdapter, eNextState);
    }

    /* Update the PS mode if it is not a partial scan request */
    if (prScanReqConfig) {
        prArbInfo->fgIsUnderActiveModeBeforeScan = fgIsUnderActiveModeBeforeScan;
    }

    if (prArbInfo->eCurrentState == ARB_STATE_SCAN) {
        GET_CURRENT_SYSTIME(&prArbInfo->rLastScanRequestTime);
    }

    return WLAN_STATUS_SUCCESS;

} /* end of arbFsmRunEventScanRequest() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function is used to do scan request for VOIP SCAN after VOIP Packet was
*        TX Done.
*
* \param[in] prAdapter Pointer of Adapter Data Structure
* \param[in] prScanReqConfig Pointer of all the necessary parameter for scan request
* \param[in] fgForceToScanInActiveMode force to do scan even it is under active mode
*                                  in infrastructure mode
*
* \retval WLAN_STATUS_SUCCESS
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
arbFsmRunEventScanSetPsVoipTrap (
    IN P_ADAPTER_T prAdapter,
    IN P_SCAN_REQ_CONFIG_T prScanReqConfig,
    IN BOOLEAN fgForceToScanInActiveMode
    )
{
    DEBUGFUNC("arbFsmRunEventScanSetPsVoipTrap");


    ASSERT(prAdapter);
    ASSERT(!prScanReqConfig); /* It should be NULL */

    DBGLOG(ARB, EVENT, ("\n\nARB EVENT: Scan - Enable traps for VOIP SCAN.\n\n"));

    NIC_TX_SET_VOIP_SCAN_TRIGGER_EVENT(prAdapter);

    return WLAN_STATUS_SUCCESS;

} /* end of arbFsmRunEventScanSetPsVoipTrap() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will indicate an Event of "Partial SCAN" to ARB FSM for
*        triggering scan in PARTIAL SCAN SEQUENCE.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
arbFsmRunEventScanPartialScanTimeOut (
    IN P_ADAPTER_T prAdapter
    )
{
#if DBG
    P_SCAN_INFO_T prScanInfo;
#endif /* DBG */
    DEBUGFUNC("arbFsmRunEventScanPartialScanTimeOut");

    ASSERT(prAdapter);

#if DBG
    prScanInfo = &prAdapter->rScanInfo;

    DBGLOG(ARB, EVENT, ("\n\nARB EVENT: Scan - Partial scan timeout. %d/%d\n\n",
        prScanInfo->rScanConfig.ucNumOfScanChnl, prScanInfo->rScanConfig.ucTotalScanChannelCount));
#endif

    if (arbFsmRunEventScanRequest(prAdapter, (P_SCAN_REQ_CONFIG_T)NULL, FALSE) !=
        WLAN_STATUS_SUCCESS) {
        DBGLOG(ARB, ERROR, ("Unable to perform next PARTIAL SCAN request.\n"));
    }
    /* NOTE(Kevin): If we have problem to deal with PARTIAL SCAN,
     * do nothing to stop the PARTIAL SCAN sequence.
     */

    return;
} /* end of arbFsmRunEventScanPartialScanTimeOut() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is the scan done timeout watchdog event handler.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
arbFsmRunEventScanCheckForHangTimeOut (
    IN P_ADAPTER_T  prAdapter
    )
{
    P_ARB_INFO_T prArbInfo;
    ENUM_ARB_STATE_T eNextState;
    BOOLEAN fgIsTransition = (BOOLEAN)FALSE;
    P_SCAN_INFO_T prScanInfo;

    ASSERT(prAdapter);
    prArbInfo = &prAdapter->rArbInfo;
    eNextState = prArbInfo->eCurrentState;

    prScanInfo = &prAdapter->rScanInfo;

    if (prArbInfo->eCurrentState == ARB_STATE_SCAN) {
        DBGLOG(ARB, EVENT, ("\n\nARB EVENT: Scan - Check for hang timeout.\n\n"));

        scanFsmRunEventScanAbort(prAdapter);

#if 0
        printk("##### SCAN ABORT!! #####\n");
        HAL_CLICK_GPIO0(prAdapter);
        HAL_CLICK_GPIO0(prAdapter);
        HAL_CLICK_GPIO0(prAdapter);
        HAL_CLICK_GPIO0(prAdapter);
#endif

        /* NOTE(Kevin): If the "SCAN Check For Hang Timer" was timeout,
         * we will abort whole PARTIAL SCAN sequence.
         */
        scanFsmRunEventScanReqCleanUp(prAdapter);

        switch(prArbInfo->ePreviousState) {
        case ARB_STATE_NORMAL_TR:
            ARB_STATE_TRANSITION(prAdapter, SCAN, NORMAL_TR);

            /* Return to original PS mode */
            if (prArbInfo->fgIsUnderActiveModeBeforeScan &&
                !prScanInfo->fgIsScanReqProceeding) {
                pmFsmRunEventEnterActiveModeReq(prAdapter, NULL);
            }

            break;

        case ARB_STATE_SEARCH:
            ARB_STATE_TRANSITION(prAdapter, SCAN, SEARCH);
            break;

        case ARB_STATE_IBSS_ALONE:
            ARB_STATE_TRANSITION(prAdapter, SCAN, IBSS_ALONE);
            break;

        case ARB_STATE_STANDBY:
            ARB_STATE_TRANSITION(prAdapter, SCAN, STANDBY);
            break;

        default:
            ASSERT(0);
            break;
        }

    }
    else if (prArbInfo->eCurrentState == ARB_STATE_BG_SSID_SCAN) {
        DBGLOG(ARB, EVENT, ("\n\nARB EVENT: Scan - Check for hang timeout.\n\n"));

        scanFsmRunEventScanAbort(prAdapter);

#if 0 // there's no SCAN Check For Hang Timer under BG SSID scan state
        /* NOTE(Kevin): If the "SCAN Check For Hang Timer" was timeout,
         * we will abort whole PARTIAL SCAN sequence.
         */
        scanFsmRunEventScanReqCleanUp(prAdapter);
#endif

        switch(prArbInfo->ePreviousState) {
        case ARB_STATE_SEARCH:
            ARB_STATE_TRANSITION(prAdapter, BG_SSID_SCAN, SEARCH);
            break;

        default:
            ASSERT(0);
            break;
        }

    }

    /* Call arbFsmSteps() when we are going to change ARB STATE */
    if (prArbInfo->eCurrentState != eNextState) {
        arbFsmSteps(prAdapter, eNextState);
    }

    return;
} /* end of arbFsmRunEventScanCheckForHangTimeOut() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is the scan done event handler.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
arbFsmRunEventScanDone (
    IN P_ADAPTER_T  prAdapter
    )
{
    P_ARB_INFO_T prArbInfo;
//    P_SCAN_INFO_T prScanInfo = &prAdapter->rScanInfo;
    ENUM_ARB_STATE_T eNextState;
    BOOLEAN fgIsTransition = (BOOLEAN)FALSE;
    P_SCAN_INFO_T prScanInfo;

    ASSERT(prAdapter);
    prArbInfo = &prAdapter->rArbInfo;
    eNextState = prArbInfo->eCurrentState;
    prScanInfo = &prAdapter->rScanInfo;

    DBGLOG(ARB, EVENT, ("\n\nARB EVENT: Scan done.\n\n"));

    if (prArbInfo->eCurrentState == ARB_STATE_SCAN) {
        scanFsmRunEventScanDone(prAdapter);

        switch(prArbInfo->ePreviousState) {
        case ARB_STATE_NORMAL_TR:

            ARB_STATE_TRANSITION(prAdapter, SCAN, NORMAL_TR);

            /* Return to original PS mode */
            if (prArbInfo->fgIsUnderActiveModeBeforeScan &&
                !prScanInfo->fgIsScanReqProceeding) {
                pmFsmRunEventEnterActiveModeReq(prAdapter, NULL);
            }

            break;

        case ARB_STATE_SEARCH:
            ARB_STATE_TRANSITION(prAdapter, SCAN, SEARCH);
            break;

        case ARB_STATE_IBSS_ALONE:
            ARB_STATE_TRANSITION(prAdapter, SCAN, IBSS_ALONE);
            break;

        case ARB_STATE_STANDBY:
            ARB_STATE_TRANSITION(prAdapter, SCAN, STANDBY);
            break;

        default:
            DBGLOG(SCAN, ERROR, ("Error! Not supported prevState: %d\n",
                                  prArbInfo->ePreviousState));
            ASSERT(0);
            break;
        }
    }
    else if (prArbInfo->eCurrentState == ARB_STATE_BG_SSID_SCAN) {
        scanFsmRunEventScanDone(prAdapter);

        switch(prArbInfo->ePreviousState) {
        case ARB_STATE_SEARCH:
            ARB_STATE_TRANSITION(prAdapter, BG_SSID_SCAN, SEARCH);
            break;

        default:
            DBGLOG(SCAN, ERROR, ("Error! Not supported prevState: %d\n",
                                  prArbInfo->ePreviousState));
            ASSERT(0);
            break;
        }
    }

    /* Call arbFsmSteps() when we are going to change ARB STATE */
    if (prArbInfo->eCurrentState != eNextState) {
        arbFsmSteps(prAdapter, eNextState);
    }

    return;
} /* end of arbFsmRunEventScanDone() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to stop SCAN for continue processing VOIP Packets.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
arbFsmRunEventScanPsVoipPartialScanStop (
    IN P_ADAPTER_T prAdapter
    )
{
    P_ARB_INFO_T prArbInfo;
    ENUM_ARB_STATE_T eNextState;
    BOOLEAN  fgIsTransition = (BOOLEAN)FALSE;
    P_SCAN_INFO_T prScanInfo;

    ASSERT(prAdapter);
    prArbInfo = &prAdapter->rArbInfo;
    eNextState = prArbInfo->eCurrentState;
    prScanInfo = &prAdapter->rScanInfo;

    DBGLOG(ARB, EVENT, ("\n\nARB EVENT: Scan - Stop PS VOIP Partial scan.\n\n"));

    if (prArbInfo->eCurrentState == ARB_STATE_SCAN) {
        switch(prArbInfo->ePreviousState) {
        case ARB_STATE_NORMAL_TR:
            //printk("s");
            scanFsmRunEventScanStop(prAdapter);

            /* Return to original PS mode */
            if (prArbInfo->fgIsUnderActiveModeBeforeScan &&
                !prScanInfo->fgIsScanReqProceeding) {
                pmFsmRunEventEnterActiveModeReq(prAdapter, NULL);
            }

            ARB_STATE_TRANSITION(prAdapter, SCAN, NORMAL_TR);
            break;

        default:
            ASSERT(0);
            break;
        }
    }

    /* Call arbFsmSteps() when we are going to change ARB STATE */
    if (prArbInfo->eCurrentState != eNextState) {
        arbFsmSteps(prAdapter, eNextState);
    }

    return;
} /* end of arbFsmRunEventScanPsVoipPartialScanStop() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is a timer callback function, which is used under
*        infrastructure mode, and will be triggered after a specific number of
*        time after connected with AP.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \retval WLAN_STATUS_SUCCESS
*/
/*----------------------------------------------------------------------------*/
extern UINT_8  PER_FLAG;
VOID
arbFsmRunEventOnConnectDeferredTimer (
    IN P_ADAPTER_T  prAdapter
    )
{
    ASSERT(prAdapter);

    DBGLOG(ARB, EVENT, ("\n\nARB EVENT: PM - Enter Power Save request.\n\n"));

    if(!PER_FLAG)	
    pmFsmRunEventOnConnectDeferredTask(prAdapter);

    return;
} /* end of arbFsmRunEventOnConnectDeferredTimer() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to change the PM state by the RX traffic throughtput.
*        It is used under the ENUM_PSP_FAST_SWITCH profile, and will trigger
*        PM state machine to enter PS mode once RX throughtput less than the
*        threshold.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
arbFsmRunEventTimerPowerSaveSwitch (
    IN P_ADAPTER_T  prAdapter
    )
{
    ASSERT(prAdapter);

    DBGLOG(ARB, EVENT, ("\n\nARB EVENT: PM - Power Save Mode switch decision.\n\n"));

    pmFsmRunEventEnterPowerSaveModeDecision(prAdapter);

    return;
} /* end of arbFsmRunEventTimerPowerSaveSwitch() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used as the VoIP HW timer callback function, which is
*        used for VoIP talking and scan function under Power Saving mode.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
arbFsmRunEventTimeupVoipInterval (
    IN P_ADAPTER_T prAdapter
    )
{
    P_ARB_INFO_T prArbInfo;
    P_BSS_INFO_T prBssInfo;

    ASSERT(prAdapter);
    prArbInfo = &prAdapter->rArbInfo;
    prBssInfo = &prAdapter->rBssInfo;

    /* To resume TX/ RX VoIP traffic */
    //if (prArbInfo->eCurrentState == ARB_STATE_NORMAL_TR &&
    if (PM_IS_VOIP_POLLING_ENABLED(prAdapter)) {

        if (prArbInfo->eCurrentState == ARB_STATE_SCAN) {
            arbFsmRunEventScanPsVoipPartialScanStop(prAdapter);
        }

        /* If buffered VO packet in the send wait queue, resume queue operation */
        if (NIC_TX_IS_BUFFER_VOICE_PACKET(prAdapter)) {
            nicTxVoipFlowCtrlResumePendingFrames(prAdapter);
        }
        else {
            /* no packets queued in VO Send Wait Queue */
            if (prBssInfo->rWmmInfo.ucWmmFlag & WMM_FLAG_SUPPORT_UAPSD) {

                NIC_TX_SET_VOIP_FLOW_CONTROL_RESUME(prAdapter);
                pmSendNullFrame(prAdapter,
                                7,
                                prAdapter->rPmInfo.fgPwrMode_PS,
                                FALSE,
                                (PFN_TX_DONE_HANDLER)0);
            }
            else {
                /* If it is work under VoIP polling, and connected with legacy PS.
                   When there's no buffered TX packets, trigger scan at once! */
                nicTxVoipFlowCtrlCheckForSuspend(prAdapter);
            }
        }
    }

    return;
} /* end of arbFsmRunEventTimeupVoipInterval() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will indicate an Event of "IBSS ALONE Time-Out" to ARB FSM.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
arbFsmRunEventIbssAloneTimeOut (
    IN P_ADAPTER_T prAdapter
    )
{
    P_ARB_INFO_T prArbInfo;
    ENUM_ARB_STATE_T eNextState;
    BOOLEAN fgIsTransition = (BOOLEAN)FALSE;

    ASSERT(prAdapter);
    prArbInfo = &prAdapter->rArbInfo;
    eNextState = prArbInfo->eCurrentState;

    DBGLOG(ARB, EVENT, ("\n\nARB EVENT: IBSS alone timeout.\n\n"));

    switch(prArbInfo->eCurrentState) {
    case ARB_STATE_IBSS_ALONE:

        /* There is no one participate in our AdHoc during this TIMEOUT Interval
         * so give up our AdHoc and go back to search for a valid BSS(IBSS) again.
         */
        ibssStopIBSS(prAdapter);

        prArbInfo->fgTryFullScan = TRUE;

        /* Pull back to SEARCH to find candidate again */
        ARB_STATE_TRANSITION(prAdapter, IBSS_ALONE, SEARCH);

        break;

    default:
        break;
    }

    /* Call arbFsmSteps() when we are going to change ARB STATE */
    if (prArbInfo->eCurrentState != eNextState) {
        arbFsmSteps(prAdapter, eNextState);
    }

    return;
} /* end of arbFsmRunEventIbssAloneTimeOut() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will check if we can leave protection mode in AdHoc.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
arbFsmRunEventIbssProtectionTimeOut (
    IN P_ADAPTER_T prAdapter
    )
{
    P_BSS_INFO_T prBssInfo;
    P_STA_INFO_T prStaInfo;
    P_LINK_T prValidStaRecList;
    P_STA_RECORD_T prStaRec;
    P_STA_RECORD_T prStaRecNext;
    OS_SYSTIME rCurrentTime;
    BOOLEAN fgContinueProtection = FALSE;
    UINT_32 i;


    ASSERT(prAdapter);

    prBssInfo = &prAdapter->rBssInfo;
    prStaInfo = &prAdapter->rStaInfo;


    GET_CURRENT_SYSTIME(&rCurrentTime);


    if ((prAdapter->eConnectionState == MEDIA_STATE_CONNECTED) &&
        (prAdapter->eCurrentOPMode == OP_MODE_IBSS)) {

        if (prBssInfo->fgIsERPPresent) {
            if (prBssInfo->fgIsProtection) {

                for (i = 0;(i < STA_RECORD_HASH_NUM) && (!fgContinueProtection); i++) {
                    prValidStaRecList = &prStaInfo->arValidStaRecList[i];

                    LINK_FOR_EACH_ENTRY_SAFE(prStaRec, prStaRecNext, prValidStaRecList, rLinkEntry, STA_RECORD_T) {

                        STA_RECORD_CHK_GUID(prStaRec);

                        if (!prStaRec->fgIsLegacy) {
                            continue;
                        }

                        if (!CHECK_FOR_TIMEOUT(rCurrentTime, prStaRec->rUpdateTime,
                            SEC_TO_SYSTIME(IBSS_PROTECTION_TIMEOUT_CHECK_SEC))) {

                            fgContinueProtection = TRUE;
                            break;
                        }
                    }
                }

                if (fgContinueProtection) {
                    ARB_SET_TIMER(prAdapter,
                                  prAdapter->rArbInfo.rProtectionTimerForAdHoc,
                                  SEC_TO_MSEC(IBSS_PROTECTION_TIMEOUT_CHECK_SEC));
                }
                else {
                    prBssInfo->fgIsProtection = FALSE;

                    nicRateDisableProtection(prAdapter);

                    prBssInfo->ucERP &= ~(ERP_INFO_NON_ERP_PRESENT | ERP_INFO_USE_PROTECTION);

                    kalMemZero(prBssInfo->aucBcnContent, sizeof(prBssInfo->aucBcnContent));
                    prBssInfo->u2BcnLen = 0;

                    ibssPrepareBeaconFrame(prAdapter,
                                           sizeof(prBssInfo->aucBcnContent),
                                           prBssInfo->aucBcnContent,
                                           &prBssInfo->u2BcnLen);

                    nicStartBeacon(prAdapter);
                }
            }
        }
    }


    return;
}


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will indicate an Event of "IBSS Merge" to ARB FSM if an
*        available BSS_DESC_T was found.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
* \param[in] prBssDesc  Pointer to the BSS Descriptor.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
arbFsmRunEventIbssMerge (
    IN P_ADAPTER_T prAdapter,
    IN P_BSS_DESC_T prBssDesc
    )
{
    P_ARB_INFO_T prArbInfo;
    ENUM_ARB_STATE_T eNextState;
    BOOLEAN fgIsTransition = (BOOLEAN)FALSE;

    ASSERT(prAdapter);
    prArbInfo = &prAdapter->rArbInfo;
    eNextState = prArbInfo->eCurrentState;

    DBGLOG(ARB, EVENT, ("\n\nARB EVENT: IBSS merge.\n\n"));

    switch(prArbInfo->eCurrentState) {
    case ARB_STATE_IBSS_ALONE:
        {
            prArbInfo->prTargetBssDesc = prBssDesc;

            ARB_STATE_TRANSITION(prAdapter, IBSS_ALONE, IBSS_MERGE);

            ARB_CANCEL_TIMER(prAdapter,
                             prArbInfo->rIbssAloneTimer);

        }
        break;

    case ARB_STATE_NORMAL_TR:
        {
            prArbInfo->prTargetBssDesc = prBssDesc;

            ARB_STATE_TRANSITION(prAdapter, NORMAL_TR, IBSS_MERGE);
        }
        break;

    default:
        break;
    }

    /* Call arbFsmSteps() when we are going to change ARB STATE */
    if (prArbInfo->eCurrentState != eNextState) {
        arbFsmSteps(prAdapter, eNextState);
    }

    return;
} /* end of arbFsmRunEventIbssMerge() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will indicate an Event of "RX Deauthentication Frame" to ARB FSM.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
* \param[in] prSwRfb    Pointer to RX Buffer.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
arbFsmRunEventProcessDeauth (
    IN P_ADAPTER_T prAdapter,
    IN P_SW_RFB_T prSwRfb
    )
{
    P_ARB_INFO_T prArbInfo;
    ENUM_ARB_STATE_T eNextState;
#if DBG
    P_WLAN_DEAUTH_FRAME_T prDeauthFrame;
#endif /* DBG */

    ASSERT(prAdapter);
    ASSERT(prSwRfb);
    prArbInfo = &prAdapter->rArbInfo;
    eNextState = prArbInfo->eCurrentState;

#if DBG
    prDeauthFrame = (P_WLAN_DEAUTH_FRAME_T) prSwRfb->pvHeader;

    DBGLOG(ARB, EVENT, ("\n\nARB EVENT: Rx Deauth frame from BSSID=["MACSTR"].\n\n",
        MAC2STR(prDeauthFrame->aucBSSID)));
#endif /* DBG */

    if (prAdapter->eConnectionState == MEDIA_STATE_CONNECTED) {
        P_BSS_INFO_T prBssInfo = &prAdapter->rBssInfo;
        UINT_16 u2ReasonCode;

        if (authProcessRxDeauthFrame(prAdapter,
                                     prSwRfb,
                                     prBssInfo->aucBSSID,
                                     &u2ReasonCode) == WLAN_STATUS_SUCCESS) {

            DBGLOG(ARB, TRACE, ("RX Deauthentication Frame: Reason Code = %04x\n",
                u2ReasonCode));

            DBGLOG(ARB, TRACE, ("Issue ARB Abort !\n"));

						arbFsmRunEventAbort(prAdapter, TRUE);

#if CFG_LP_IOT // used for emulation/ IOT field try only
            {
            OS_SYSTIME rCurrentSysTime;
            GET_CURRENT_SYSTIME(&rCurrentSysTime);
            DBGLOG(LP_IOT, INFO, ("[LP-IOT] Disauthenticated on connect!: %d ms\n",
                                rCurrentSysTime));
            }
#endif
        }
    }
    else if (prArbInfo->eCurrentState == ARB_STATE_JOIN) {
        P_PEER_BSS_INFO_T prPeerBssInfo = &prAdapter->rPeerBssInfo;
        UINT_16 u2ReasonCode;

        if (authProcessRxDeauthFrame(prAdapter,
                                     prSwRfb,
                                     prPeerBssInfo->aucBSSID,
                                     &u2ReasonCode) == WLAN_STATUS_SUCCESS) {

            DBGLOG(ARB, TRACE, ("RX Deauthentication Frame during JOIN: Reason Code = %04x\n",
                u2ReasonCode));

            DBGLOG(ARB, TRACE, ("Issue JOIN Abort !\n"));

            joinFsmRunEventAbort(prAdapter);

            eNextState = ARB_STATE_SEARCH;
        }

        /* Call arbFsmSteps() when we are going to change ARB STATE */
        if (prArbInfo->eCurrentState != eNextState) {
            arbFsmSteps(prAdapter, eNextState);
        }
    }

    return;
} /* end of arbFsmRunEventProcessDeauth() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will indicate an Event of "RX Disassociation Frame" to ARB FSM.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
* \param[in] prSwRfb    Pointer to RX Buffer.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
arbFsmRunEventProcessDisassoc (
    IN P_ADAPTER_T prAdapter,
    IN P_SW_RFB_T prSwRfb
    )
{
    P_ARB_INFO_T prArbInfo;
    ENUM_ARB_STATE_T eNextState;

    ASSERT(prAdapter);
    ASSERT(prSwRfb);
    prArbInfo = &prAdapter->rArbInfo;
    eNextState = prArbInfo->eCurrentState;

    DBGLOG(ARB, EVENT, ("\n\nARB EVENT: Rx Disassoc frame.\n\n"));

    if (prAdapter->eConnectionState == MEDIA_STATE_CONNECTED) {
        P_BSS_INFO_T prBssInfo = &prAdapter->rBssInfo;
        UINT_16 u2ReasonCode;

        if (assocProcessRxDisassocFrame(prAdapter,
                                        prSwRfb,
                                        prBssInfo->aucBSSID,
                                        &u2ReasonCode) == WLAN_STATUS_SUCCESS) {

            DBGLOG(ARB, TRACE, ("RX Disassociation Frame: Reason Code = %04x\n",
                u2ReasonCode));

            DBGLOG(ARB, TRACE, ("Issue ARB Abort !\n"));

            arbFsmRunEventAbort(prAdapter, TRUE);

#if CFG_LP_IOT // used for emulation/ IOT field try only
            {
            OS_SYSTIME rCurrentSysTime;
            GET_CURRENT_SYSTIME(&rCurrentSysTime);
            DBGLOG(LP_IOT, INFO, ("[LP-IOT] Disassociated on connect!: %d ms\n",
                                rCurrentSysTime));
            }
#endif
        }
    }
    else if (prArbInfo->eCurrentState == ARB_STATE_JOIN) {
        P_PEER_BSS_INFO_T prPeerBssInfo = &prAdapter->rPeerBssInfo;
        UINT_16 u2ReasonCode;
        BOOLEAN fgIsTransition = (BOOLEAN)FALSE;

        if (assocProcessRxDisassocFrame(prAdapter,
                                        prSwRfb,
                                        prPeerBssInfo->aucBSSID,
                                        &u2ReasonCode) == WLAN_STATUS_SUCCESS) {

            DBGLOG(ARB, TRACE, ("RX Disassociation Frame during JOIN: Reason Code = %04x\n",
                u2ReasonCode));

            DBGLOG(ARB, TRACE, ("Issue JOIN Abort !\n"));

            joinFsmRunEventAbort(prAdapter);

            ARB_STATE_TRANSITION(prAdapter, JOIN, SEARCH);
        }

        /* Call arbFsmSteps() when we are going to change ARB STATE */
        if (prArbInfo->eCurrentState != eNextState) {
            arbFsmSteps(prAdapter, eNextState);
        }
    }

    return;
} /* end of arbFsmRunEventProcessDisassoc() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will indicate an Event of "RX ProbeRequest Frame" to ARB FSM.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
* \param[in] prSwRfb    Pointer to RX Buffer.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
arbFsmRunEventProcessProbeReq (
    IN P_ADAPTER_T prAdapter,
    IN P_SW_RFB_T prSwRfb
    )
{
    P_ARB_INFO_T prArbInfo;

    ASSERT(prAdapter);
    ASSERT(prSwRfb);
    prArbInfo = &prAdapter->rArbInfo;

    switch(prArbInfo->eCurrentState) {
    case ARB_STATE_NORMAL_TR:
        if (prAdapter->eCurrentOPMode != OP_MODE_IBSS) {
            break;
        }
        /* NOTE(Kevin): Pass through */

    case ARB_STATE_IBSS_ALONE:
        ibssProcessProbeRequest(prAdapter, prSwRfb);
        break;

    default:
        break;
    }

    return;
} /* end of arbFsmRunEventProcessProbeReq() */


#if CFG_IBSS_POWER_SAVE
/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to signal correspond IBSS STA for the MSDU INFO
*        is awake.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
* \param[in] prMsduInfo     Pointer to the MSDU INFO which is used to get the STA record
* \param[in] rTxDoneStatus  Value of the return TX status of the ATIM frame
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
arbSetAdhocStaAwake (
    IN P_ADAPTER_T prAdapter,
    IN P_MSDU_INFO_T prMsduInfo,
    IN WLAN_STATUS rTxDoneStatus
    )
{
    DEBUGFUNC("arbSetAdhocStaAwake");


    ASSERT(prAdapter);
    ASSERT(prMsduInfo);

    DBGLOG(LP, INFO, ("\n"));
    if (prAdapter->eConnectionState == MEDIA_STATE_CONNECTED &&
        PM_IS_UNDER_IBSS_POWER_SAVE_MODE(prAdapter)) {

        pmSetAdhocStaAwake(prAdapter, prMsduInfo, rTxDoneStatus);
    }
    else {
        ASSERT(0);
    }

    return;
} /* end of arbSetAdhocStaAwake() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to signal ALL IBSS STA is awake.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
* \param[in] prMsduInfo     Pointer to the MSDU INFO which is used to get the STA record
* \param[in] rTxDoneStatus  Value of the return TX status of the ATIM frame
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
arbSetAdhocAllStaAwake (
    IN P_ADAPTER_T prAdapter,
    IN P_MSDU_INFO_T prMsduInfo,
    IN WLAN_STATUS rTxDoneStatus
    )
{
    DEBUGFUNC("arbSetAdhocAllStaAwake");


    ASSERT(prAdapter);
    ASSERT(prMsduInfo);

    DBGLOG(LP, INFO, ("\n"));

    if (prAdapter->eConnectionState == MEDIA_STATE_CONNECTED &&
        PM_IS_UNDER_IBSS_POWER_SAVE_MODE(prAdapter)) {

        pmSetAdhocAllStaAwake(prAdapter, prMsduInfo, rTxDoneStatus);
    }
    else {
        ASSERT(0);
    }

    return;
} /* end of arbSetAdhocAllStaAwake() */
#endif /* CFG_IBSS_POWER_SAVE */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will indicate an Event of "RCPI Interrupt" to ARB FSM for
*        ROAMING Module.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
arbFsmRunEventRoamingRCPI (
    IN P_ADAPTER_T prAdapter
    )
{
    P_ARB_INFO_T prArbInfo;
    ENUM_ARB_STATE_T eNextState;
    BOOLEAN fgIsTransition = (BOOLEAN)FALSE;


    ASSERT(prAdapter);
    prArbInfo = &prAdapter->rArbInfo;
    eNextState = prArbInfo->eCurrentState;

    DBGLOG(ARB, EVENT, ("\n\nARB EVENT: Roaming - RCPI INT.\n\n"));

    if (prArbInfo->eCurrentState == ARB_STATE_NORMAL_TR) {
        WLAN_STATUS rStatus;

        rStatus = roamingFsmRunEventRCPI(prAdapter);

        if (rStatus == WLAN_STATUS_ROAM_OUT_FIND_BEST) {

            prArbInfo->fgTryFullScan = FALSE;

            ARB_STATE_TRANSITION(prAdapter, NORMAL_TR, SEARCH);

            arbFsmSteps(prAdapter, eNextState);
        }
        else if (rStatus == WLAN_STATUS_ROAM_DISCOVERY) {

            P_ROAMING_INFO_T prRoamingInfo = &prAdapter->rRoamingInfo;
            P_SCAN_REQ_CONFIG_T prScanReqConfig = &prRoamingInfo->rScanReqConfig;


            if ((rStatus = arbFsmRunEventScanRequest(prAdapter, prScanReqConfig, FALSE)) ==
                WLAN_STATUS_FAILURE) {

                prRoamingInfo->fgIsScanTriggered = FALSE;

                DBGLOG(ARB, TRACE, ("ROAMING Discovery was refused due to another SCAN is proceeding.\n"));
            }
            else {
                prRoamingInfo->fgIsScanTriggered = TRUE;
            }
        }
    }

    /* NOTE(Kevin): if this event was not handled, this INT will be generated again
     * right after receiving next beacon.
     */

    return;
} /* end of arbFsmRunEventRoamingRCPI() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will indicate an Event of "Roaming Decision Time-Out" to ARB FSM for
*        ROAMING Module to check the RCPI value.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
arbFsmRunEventRoamingDecision (
    IN P_ADAPTER_T prAdapter
    )
{
    P_ARB_INFO_T prArbInfo;
    ENUM_ARB_STATE_T eNextState;
    BOOLEAN fgIsTransition = (BOOLEAN)FALSE;

    ASSERT(prAdapter);
    prArbInfo = &prAdapter->rArbInfo;
    eNextState = prArbInfo->eCurrentState;

    DBGLOG(ARB, EVENT, ("\n\nARB EVENT: Roaming - Decision.\n\n"));

   if (prArbInfo->eCurrentState == ARB_STATE_NORMAL_TR) {
        WLAN_STATUS rStatus;

        rStatus = roamingFsmRunEventDecision(prAdapter);

        if (rStatus == WLAN_STATUS_ROAM_OUT_FIND_BEST) {

            prArbInfo->fgTryFullScan = FALSE;

            ARB_STATE_TRANSITION(prAdapter, NORMAL_TR, SEARCH);

            arbFsmSteps(prAdapter, eNextState);
        }
        else if (rStatus == WLAN_STATUS_ROAM_DISCOVERY) {
            P_ROAMING_INFO_T prRoamingInfo = &prAdapter->rRoamingInfo;
            P_SCAN_REQ_CONFIG_T prScanReqConfig = &prRoamingInfo->rScanReqConfig;


            if ((rStatus = arbFsmRunEventScanRequest(prAdapter, prScanReqConfig, FALSE)) ==
                WLAN_STATUS_FAILURE) {

                prRoamingInfo->fgIsScanTriggered = FALSE;

                DBGLOG(ARB, TRACE, ("ROAMING Discovery was refused due to another SCAN is proceeding.\n"));
            }
            else {

                prRoamingInfo->fgIsScanTriggered = TRUE;

            }
        }

    }
    else {
        /* Event was not handled, re-trigger event again */
        roamingReTriggerEventDecision(prAdapter);
    }

    return;
} /* end of arbFsmRunEventRoamingDecision() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will indicate an Event of "Roaming Discovery" to ARB FSM for
*        ROAMING Module to perform scan.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
arbFsmRunEventRoamingDiscovery (
    IN P_ADAPTER_T prAdapter
    )
{
    P_ARB_INFO_T prArbInfo;
    ENUM_ARB_STATE_T eNextState;
    BOOLEAN fgIsTransition = (BOOLEAN)FALSE;

    ASSERT(prAdapter);
    prArbInfo = &prAdapter->rArbInfo;
    eNextState = prArbInfo->eCurrentState;

    DBGLOG(ARB, EVENT, ("\n\nARB EVENT: Roaming - Discovery.\n\n"));

    if (prArbInfo->eCurrentState == ARB_STATE_NORMAL_TR) {
        WLAN_STATUS rStatus;

        rStatus = roamingFsmRunEventDiscovery(prAdapter);

        if (rStatus == WLAN_STATUS_ROAM_OUT_FIND_BEST) {

            prArbInfo->fgTryFullScan = FALSE;

            ARB_STATE_TRANSITION(prAdapter, NORMAL_TR, SEARCH);

            arbFsmSteps(prAdapter, eNextState);
        }
        else if (rStatus == WLAN_STATUS_ROAM_DISCOVERY) {
            P_ROAMING_INFO_T prRoamingInfo = &prAdapter->rRoamingInfo;
            P_SCAN_REQ_CONFIG_T prScanReqConfig = &prRoamingInfo->rScanReqConfig;


            if ((rStatus = arbFsmRunEventScanRequest(prAdapter, prScanReqConfig, FALSE)) ==
                WLAN_STATUS_FAILURE) {

                prRoamingInfo->fgIsScanTriggered = FALSE;

                DBGLOG(ARB, TRACE, ("ROAMING Discovery was refused due to another SCAN is proceeding.\n"));
            }
            else {

                prRoamingInfo->fgIsScanTriggered = TRUE;

            }
        }
    }
    else {
        /* Event was not handled, re-trigger event again */
        roamingReTriggerEventDiscovery(prAdapter);
    }

    return;
} /* end of arbFsmRunEventRoamingDiscovery() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will indicate an Event of "Media Disconnect" to ARB FSM.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
arbFsmRunEventIndicationOfDisconnectTimeOut (
    IN P_ADAPTER_T prAdapter
    )
{
    ASSERT(prAdapter);

    /* To indicate the Disconnect Event only if current media state is
     * disconnected and we didn't do indication yet.
     */
    if ((prAdapter->eConnectionState == MEDIA_STATE_DISCONNECTED) &&
        (prAdapter->eConnectionState != prAdapter->eConnectionStateIndicated)) {

        DBGLOG(ARB, EVENT, ("\n\nARB EVENT: Indication of Media Disconnect.\n\n"));

        prAdapter->eConnectionStateIndicated = MEDIA_STATE_DISCONNECTED;

        nicTxFlushStopQueues(prAdapter, TXQ_DATA_MASK, 0x0);

        nicTxCleanUpSendWaitQue(prAdapter);

        nicTxCleanUpOsSendQue(prAdapter);

#if CFG_IBSS_POWER_SAVE
        nicTxCleanUpStaWaitQue(prAdapter);
#endif /* CFG_IBSS_POWER_SAVE */

        privacyClearPmkid(prAdapter);

	kalMemZero(prAdapter->rConnSettings.aucSSID, sizeof(prAdapter->rConnSettings.aucSSID));

        kalIndicateStatusAndComplete(prAdapter->prGlueInfo,
                                     WLAN_STATUS_MEDIA_DISCONNECT,
                                     NULL,
                                     0);
    }

    return;
} /* end of arbFsmRunEventIndicationOfDisconnectTimeOut() */


//3 /* --------------- RF TEST mode related functions --------------- */
/*----------------------------------------------------------------------------*/
/*!
* \brief Set the driver to test mode
*
* \param[in] prAdapter          Pointer to the Adapter structure.
* \param[in] pucEepromBuf       Buffer of eeprom
* \param[in] u4EepromBufByteLen The length of eeprom buffer
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
arbFsmRunEventRftestEnterTestMode (
    IN  P_ADAPTER_T       prAdapter,
    IN  PUINT_8           pucEepromBuf,
    IN  UINT_32           u4EepromBufByteLen
    )
{
    ASSERT(prAdapter);
    //ASSERT(pucEepromBuf); // Set to NULL in wlanoidRftestSetTestMode().

    DBGLOG(ARB, EVENT, ("\n\nARB EVENT: RF Test - Enter test mode.\n\n"));
    
    /* If system had been in RF test mode because EEPROM error or 32Khz error,
     * just exit.
     */
    if (IS_ARB_IN_RFTEST_STATE(prAdapter)) {
        return;
    }

    /* Disable the device's interrupt line. */
    nicDisableInterrupt(prAdapter);
    DBGLOG(RFTEST, TRACE, ("Interrupt disabled\n"));

    nicTxRelease(prAdapter);
    DBGLOG(RFTEST, TRACE, ("Tx Resource released\n"));

    nicRxUninitialize(prAdapter);
    DBGLOG(RFTEST, TRACE, ("Rx Resource released\n"));

    if (prAdapter->eConnectionState == MEDIA_STATE_CONNECTED) {

        prAdapter->eConnectionState = MEDIA_STATE_DISCONNECTED;
        prAdapter->eConnectionStateIndicated = MEDIA_STATE_DISCONNECTED;

        nicTxFlushStopQueues(prAdapter, TXQ_DATA_MASK, 0x0);

        nicTxCleanUpSendWaitQue(prAdapter);

        nicTxCleanUpOsSendQue(prAdapter);

#if CFG_IBSS_POWER_SAVE
        nicTxCleanUpStaWaitQue(prAdapter);
#endif /* CFG_IBSS_POWER_SAVE */

	kalMemZero(prAdapter->rConnSettings.aucSSID, sizeof(prAdapter->rConnSettings.aucSSID));

        kalIndicateStatusAndComplete(prAdapter->prGlueInfo,
                                  WLAN_STATUS_MEDIA_DISCONNECT,
                                  NULL,
                                  0);
    }
    prAdapter->rArbInfo.fgTestMode = TRUE;

    arbFsmRunEventReset(prAdapter);

    return;
} /* end of arbFsmRunEventRftestEnterTestMode() */


/*----------------------------------------------------------------------------*/
/*!
* \brief Abort the test mode and set the driver to the idle state.
*
* \param[in] prAdapter          Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
arbFsmRunEventRftestAbortTestMode (
    IN  P_ADAPTER_T       prAdapter
    )
{
    ASSERT(prAdapter);

    DBGLOG(ARB, EVENT, ("\n\nARB EVENT: RF Test - Abort test mode.\n\n"));

    /* Disable the device's interrupt line. */
    nicDisableInterrupt(prAdapter);
    DBGLOG(RFTEST, TRACE, ("Interrupt disabled\n"));

#if !CFG_SDIO_DEVICE_DRIVER_WO_NDIS
    prAdapter->rArbInfo.fgTestMode = FALSE;

    rftestUnInit(prAdapter);

    /* If EEPROM is not present or checksum error, enter test mode
     * to avoid normal operation. So we can know something wrong.
     * In rftestUnInit(), the EEPROM is reloaded again.
     */
    if (prAdapter->rEEPROMCtrl.fgIsEepromValid == FALSE) {
        prAdapter->rArbInfo.fgTestMode = TRUE;
    }
#endif

    arbFsmRunEventReset(prAdapter);

    return;
} /* end of arbFsmRunEventRftestAbortTestMode() */


/*----------------------------------------------------------------------------*/
/*!
* \brief Set Auto Test for RF_TEST.
*
* \param[in] prAdapter          Pointer to the Adapter structure.
* \param[in] prRfATCfg          Pointer to the Wi-Fi Test structure.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_FAILURE
* \retval WLAN_STATUS_NOT_SUPPORTED
* \retval WLAN_STATUS_INVALID_DATA
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
arbFsmRunEventRftestSetAutoTest (
    IN P_ADAPTER_T                   prAdapter,
    IN P_PARAM_MTK_WIFI_TEST_STRUC_T prRfATCfg
    )
{
    UINT_16     u2PktContentOffset;
    P_RFTEST_INFO_T prRFATInfo;
    WLAN_STATUS rStatus = WLAN_STATUS_SUCCESS;
    UINT_32  u4TempRandom = 0;

    ASSERT(prAdapter);
    ASSERT(prRfATCfg);
    prRFATInfo = &prAdapter->rRFTestInfo;

    DBGLOG(ARB, EVENT, ("\n\nARB EVENT: RF Test - Set auto test.\n\n"));

    switch (prRfATCfg->u4FuncIndex) {
    case RF_AT_FUNCID_COMMAND:
        switch ((ENUM_RF_AT_COMMAND_T)prRfATCfg->u4FuncData) {
        case RF_AT_COMMAND_STOPTEST:
            if (prRFATInfo->eCurrentState == RF_AUTOTEST_STATE_TX) {
#if CFG_SDIO_DEVICE_DRIVER_WO_NDIS
                ARB_CANCEL_TIMER(prAdapter,
                             prAdapter->rTxCtrl.rPktTxIntervalTimer);
#endif

                rftestTxStopTx(prAdapter);
/*
                //4 2008/6/30, mikewu, restore the fgIsRfTestTxMode
                prAdapter->rTxCtrl.fgIsRfTestTxMode = FALSE;
                prRFATInfo->eCurrentState = RF_AUTOTEST_STATE_STANDBY;
*/
                DBGLOG(RFTEST, TRACE, ("RF_AT_COMMAND_STOPTEST TX\n"));
            }
            else if (prRFATInfo->eCurrentState == RF_AUTOTEST_STATE_RX) {
                rftestRxStopRx(prAdapter);
/*
                //4 2008/6/30, mikewu, restore the fgIsRfTestRxMode
                prAdapter->rRxCtrl.fgIsRfTestRxMode = FALSE;
                prRFATInfo->eCurrentState = RF_AUTOTEST_STATE_STANDBY;
*/
                DBGLOG(RFTEST, TRACE, ("RF_AT_COMMAND_STOPTEST RX\n"));
            }
            else if (prRFATInfo->eCurrentState == RF_AUTOTEST_STATE_RESET) {
                DBGLOG(RFTEST, WARN, ("Try to stop test while resetting"));
            }
            nicDisableInterrupt(prAdapter);
            break;

        case RF_AT_COMMAND_STARTTX:
            //ASSERT(!prAdapter->rRxCtrl.fgIsRfTestRxMode);
            ASSERT(prRFATInfo->eCurrentState == RF_AUTOTEST_STATE_STANDBY);
            if (/*prAdapter->rRxCtrl.fgIsRfTestRxMode || */prRFATInfo->eCurrentState != RF_AUTOTEST_STATE_STANDBY) {
                //rftestRxStopRx(prAdapter);
                //nicDisableInterrupt(prAdapter);
                //4 2008/06/30, mikewu, just let it does not work
                return WLAN_STATUS_FAILURE;
            }
            prAdapter->rTxCtrl.fgIsRfTestTxMode = TRUE;
            rStatus = rftestTxModeInit(prAdapter);
            if (rStatus != WLAN_STATUS_SUCCESS) {
                return WLAN_STATUS_FAILURE;
            }

            /*Enable interrupt*/
            nicEnableInterrupt(prAdapter);
            rftestTx(prAdapter);
            break;

        case RF_AT_COMMAND_STARTRX:
            //ASSERT(!prAdapter->rTxCtrl.fgIsRfTestTxMode);
            ASSERT(prRFATInfo->eCurrentState == RF_AUTOTEST_STATE_STANDBY);
            if (/*prAdapter->rTxCtrl.fgIsRfTestTxMode || */prRFATInfo->eCurrentState != RF_AUTOTEST_STATE_STANDBY) {
                //4 2008/06/30, mikewu, just let it does not work
                //rftestTxStopTx(prAdapter);
                //nicDisableInterrupt(prAdapter);
                return WLAN_STATUS_FAILURE;
            }
            prAdapter->rRxCtrl.fgIsRfTestRxMode = TRUE;
            rStatus = rftestRxModeInit(prAdapter);
            if (rStatus != WLAN_STATUS_SUCCESS) {
                return WLAN_STATUS_FAILURE;
            }

            /*Enable interrupt*/
            nicEnableInterrupt(prAdapter);
            break;

        case RF_AT_COMMAND_RESET:
            if (prRFATInfo->eCurrentState == RF_AUTOTEST_STATE_STANDBY) {
                prRFATInfo->eCurrentState = RF_AUTOTEST_STATE_RESET;
                rftestSetSWDefaultValue(prAdapter);
                prRFATInfo->eCurrentState = RF_AUTOTEST_STATE_STANDBY;
            }
            else {
                DBGLOG(RFTEST, WARN, ("Try to reset in state %d",\
                    prRFATInfo->eCurrentState));
            }
            break;

        default:
            DBGLOG(RFTEST, ERROR, ("Command id %ld is not support\n",\
            prRfATCfg->u4FuncData));
            return WLAN_STATUS_NOT_SUPPORTED;

        }
        break;

    case RF_AT_FUNCID_POWER:
        if ( prRfATCfg->u4FuncData > RF_AT_PARAM_POWER_MAX) {
            DBGLOG(RFTEST, ERROR, ("Power :%ld is exceed max value\n",\
            prRfATCfg->u4FuncData));
            return WLAN_STATUS_INVALID_DATA;

        }
        prRFATInfo->rSetting.ucTxPowerGain =
          (UINT_8)(  prRfATCfg->u4FuncData & RF_AT_PARAM_POWER_MASK);
        break;

    case RF_AT_FUNCID_RATE:
        if ( prRfATCfg->u4FuncData & RF_AT_PARAM_RATE_MCS_MASK) {
            DBGLOG(RFTEST, ERROR, ("MCS data rate: %ld does not support.\n",\
            prRfATCfg->u4FuncData));
            return WLAN_STATUS_INVALID_DATA;

        }
        prRFATInfo->rSetting.ucTxRate =
          (UINT_8)(  prRfATCfg->u4FuncData & RF_AT_PARAM_RATE_MASK);
        break;

    case RF_AT_FUNCID_PREAMBLE:
        if ( ((ENUM_RF_AT_PREAMBLE_T) prRfATCfg->u4FuncData)
             >= RF_AT_PREAMBLE_NUM) {
            DBGLOG(RFTEST, ERROR, ("Preamble type: %ld does not support.\n",\
            prRfATCfg->u4FuncData));
            return WLAN_STATUS_INVALID_DATA;

        }

        prRFATInfo->rSetting.ePreamble =
          (ENUM_RF_AT_PREAMBLE_T)(  prRfATCfg->u4FuncData );
        break;

    case RF_AT_FUNCID_ANTENNA:
        if ( ( prRfATCfg->u4FuncData) > RF_AT_PARAM_ANTENNA_ID_MAX) {
            DBGLOG(RFTEST, ERROR, ("Antenna ID: %ld does not support.\n",\
            prRfATCfg->u4FuncData));
            return WLAN_STATUS_INVALID_DATA;

        }
        prRFATInfo->rSetting.ucAntenna=
          (UINT_8)(  prRfATCfg->u4FuncData );

        break;

    case RF_AT_FUNCID_PKTLEN:
        if ( ( prRfATCfg->u4FuncData) >= (RF_AT_PARAM_TX_PKTLEN_BYTE_MAX)) {
            DBGLOG(RFTEST, ERROR, ("Packet length %ld does not support.\n",\
            prRfATCfg->u4FuncData));
            return WLAN_STATUS_INVALID_DATA;

        }
        prRFATInfo->rSetting.u4PacketLen =  prRfATCfg->u4FuncData;
        break;

    case RF_AT_FUNCID_PKTCNT:
        prRFATInfo->rSetting.u4PacketCnt=  prRfATCfg->u4FuncData;
        break;

    case RF_AT_FUNCID_PKTINTERVAL:
        prRFATInfo->rSetting.u4PacketIntervalUs =
                    prRfATCfg->u4FuncData;
        break;

    case RF_AT_FUNCID_ALC:
        prRFATInfo->rSetting.fgALCEn =
            (prRfATCfg->u4FuncData != 0) ? TRUE: FALSE;
        break;

    case RF_AT_FUNCID_TXOPLIMIT:
        prRFATInfo->rSetting.u4QueTxop=
                    prRfATCfg->u4FuncData;
        break;

    case RF_AT_FUNCID_ACKPOLICY:

        if ( !( prRFATInfo->rSetting.u4QueTxop & RF_AT_PARAM_TXOPQUE_TMASK)) {
            DBGLOG(REQ, ERROR, ("TXOP is disabled, Ack policy will not support.\n"));
            return WLAN_STATUS_INVALID_DATA;
        }
        if ( ((ENUM_RF_AT_ACK_POLICY_T) prRfATCfg->u4FuncData)
             > RF_AT_ACK_POLICY_NOACK) {
            DBGLOG(REQ, ERROR, ("Ack policy type %ld does not support.\n",\
            prRfATCfg->u4FuncData));
            return WLAN_STATUS_INVALID_DATA;
        }

        prRFATInfo->rSetting.eAckPolicy=
          (ENUM_RF_AT_ACK_POLICY_T)(  prRfATCfg->u4FuncData );
        break;

    case RF_AT_FUNCID_PKTCONTENT:
    {
        u2PktContentOffset = RF_AT_PKT_CONTENT_GET_OFFSET(prRfATCfg->u4FuncData);
        if (  u2PktContentOffset >= (RF_AT_PARAM_TX_PKTLEN_BYTE_MAX - 1) ) {
            DBGLOG(RFTEST, ERROR, ("Packet offset %d is out of ranget.\n",\
                    u2PktContentOffset));
            return WLAN_STATUS_INVALID_DATA;
        }
	      for(; u2PktContentOffset < RF_AT_PARAM_TX_PKTLEN_BYTE_MAX - 1; u2PktContentOffset+=2)
	      {
        	u4TempRandom = random32();
        	prRFATInfo->rSetting.aucPktContent[u2PktContentOffset] =
            		RF_AT_PKT_CONTENT_GET_OFFSET_BYTE(u4TempRandom);

        	prRFATInfo->rSetting.aucPktContent[u2PktContentOffset+1] =
            		RF_AT_PKT_CONTENT_GET_OFFSET_PLUS1_BYTE(u4TempRandom);
	      }
    }
        break;

    case RF_AT_FUNCID_RETRYLIMIT:
        if ( (prRfATCfg->u4FuncData) > RF_AT_PARAM_TX_RETRY_MAX) {
            DBGLOG(RFTEST, ERROR, ("Retry limit %ld is out of range.\n",\
            prRfATCfg->u4FuncData));
            return WLAN_STATUS_INVALID_DATA;
        }
        prRFATInfo->rSetting.ucRetryLimit=
                (UINT_8)(  prRfATCfg->u4FuncData );
        break;

    case RF_AT_FUNCID_QUEUE:
        if ( (prRfATCfg->u4FuncData) > ENUM_QUEUE_ID_AC4) {
            DBGLOG(RFTEST, ERROR, ("Queue Id %ld is out of range.\n",\
            prRfATCfg->u4FuncData));
            return WLAN_STATUS_INVALID_DATA;
        }
        prRFATInfo->rSetting.ucTxQue=
                (UINT_8)(  prRfATCfg->u4FuncData );
        break;

    case RF_AT_FUNCID_IO_PIN_TEST:

        if (!IS_ARB_IN_RFTEST_STATE(prAdapter)) {
            return WLAN_STATUS_FAILURE;
        }
        else {
            UINT_32 u4RegMptcr = 0;
#if CFG_TEST_IO_PIN
            prAdapter->fgIntVarified = FALSE;
            prAdapter->u4IntIORslt = 0;
#endif
            /* get register value */
            HAL_MCR_RD(prAdapter, MCR_MPTCR, &u4RegMptcr);

            /* disable timer */
            HAL_MCR_WR(prAdapter, MCR_MPTCR, u4RegMptcr & ~(BIT(ENUM_TIMER_3+ 17)));

            /* Install the timer */
            HAL_MCR_WR(prAdapter,
                    MCR_TDR,
                    ((UINT_32)ENUM_TIMER_3 << 30) |
                    (TDR_TIME_VALUE_CTRL_PERIOD) |
                    (TDR_TIMEUP_ENABLE) |
                    (64 & TDR_TIME_VALUE_MASK));   /* Generate Interrupt in 100 us? */

            /* enable timer */
            HAL_MCR_WR(prAdapter, MCR_MPTCR, u4RegMptcr | BIT(ENUM_TIMER_3 + 17));

            NIC_SET_INT_EVENT(prAdapter, INT_EVENT_T3_TIMEUP);
        }
        break;

    case RF_AT_FUNCID_VERSION:
    case RF_AT_FUNCID_BANDWIDTH:
    case RF_AT_FUNCID_GI:
    case RF_AT_FUNCID_STBC:
    default:
        DBGLOG(RFTEST, ERROR, ("Function id %ld is not support\n",\
        prRfATCfg->u4FuncIndex));
        return WLAN_STATUS_NOT_SUPPORTED;
    }

    return WLAN_STATUS_SUCCESS;

} /* end of arbFsmRunEventRftestSetAutoTest() */


/*----------------------------------------------------------------------------*/
/*!
* \brief Query Auto Test for RF_TEST.
*
* \param[in] prAdapter          Pointer to the Adapter structure.
* \param[in] prRfATStatus       Pointer to the Wi-Fi Test structure.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_NOT_SUPPORTED
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
arbFsmRunEventRftestQueryAutoTest (
    IN P_ADAPTER_T                   prAdapter,
    IN P_PARAM_MTK_WIFI_TEST_STRUC_T prRfATStatus
    )
{
    P_RFTEST_INFO_T prRFATInfo;

    ASSERT(prAdapter);
    ASSERT(prRfATStatus);

    prRFATInfo = &prAdapter->rRFTestInfo;

    DBGLOG(ARB, EVENT, ("\n\nARB EVENT: RF Test - Query auto test.\n\n"));

    switch(prRfATStatus->u4FuncIndex){
    case RF_AT_FUNCID_VERSION:
        prRfATStatus->u4FuncData = RF_AUTO_TEST_FUNCTION_TABLE_VERSION;
        break;

    case RF_AT_FUNCID_COMMAND:
        prRfATStatus->u4FuncData =
            (UINT_32) prRFATInfo->eCurrentState;
        DBGLOG(REQ, TRACE, ("RF Auto Test in state %d\n",\
            prRFATInfo->eCurrentState));
        break;

    case RF_AT_FUNCID_POWER:
        prRfATStatus->u4FuncData =
            (UINT_32) prRFATInfo->rSetting.ucTxPowerGain;
        break;

    case RF_AT_FUNCID_RATE:
        prRfATStatus->u4FuncData =
            (UINT_32) prRFATInfo->rSetting.ucTxRate;
        break;

    case RF_AT_FUNCID_PREAMBLE:
        prRfATStatus->u4FuncData =
            (UINT_32) prRFATInfo->rSetting.ePreamble;
        break;

    case RF_AT_FUNCID_ANTENNA:
        prRfATStatus->u4FuncData =
            (UINT_32) prRFATInfo->rSetting.ucAntenna;
        break;

    case RF_AT_FUNCID_PKTLEN:
        prRfATStatus->u4FuncData =
                      prRFATInfo->rSetting.u4PacketLen;
        break;

    case RF_AT_FUNCID_PKTINTERVAL:
        prRfATStatus->u4FuncData =
                      prRFATInfo->rSetting.u4PacketIntervalUs;
        break;

    case RF_AT_FUNCID_TXOPLIMIT:
        prRfATStatus->u4FuncData =
                      prRFATInfo->rSetting.u4QueTxop;
        break;

    case RF_AT_FUNCID_ACKPOLICY:
        prRfATStatus->u4FuncData =
             (UINT_32)prRFATInfo->rSetting.eAckPolicy;
        break;

    case RF_AT_FUNCID_RETRYLIMIT:
        prRfATStatus->u4FuncData =
             (UINT_32)prRFATInfo->rSetting.ucRetryLimit;
        break;

    case RF_AT_FUNCID_QUEUE:
        prRfATStatus->u4FuncData =
             (UINT_32)prRFATInfo->rSetting.ucTxQue;
        break;

    case RF_AT_FUNCID_IO_PIN_TEST:
        //4 <1> Set some interrupt, timer can be the one.
        /* Temperory assume that there is always interrupt */
        //4 <2> Wait for the ready event.
        /* Read the result directly. */
        //4 <3> Read the result and report it back.
#if CFG_TEST_IO_PIN
        if (!IS_ARB_IN_RFTEST_STATE(prAdapter)) {
            prRfATStatus->u4FuncData = 0;
            return WLAN_STATUS_FAILURE;
        }
        else {
            if (prAdapter->fgIntVarified) {
                prRfATStatus->u4FuncData = prAdapter->u4IntIORslt;
            }
            else {
                prRfATStatus->u4FuncData = 0;
                return WLAN_STATUS_FAILURE;
            }
        }
#endif
        break;

    case RF_AT_FUNCID_PKTCNT:
    case RF_AT_FUNCID_ALC:
    case RF_AT_FUNCID_PKTCONTENT:
    case RF_AT_FUNCID_BANDWIDTH:
    case RF_AT_FUNCID_GI:
    case RF_AT_FUNCID_STBC:
    default:
        DBGLOG(REQ, ERROR, ("Function id %ld is not support\n",\
        prRfATStatus->u4FuncIndex));
        return WLAN_STATUS_NOT_SUPPORTED;
    }

    return WLAN_STATUS_SUCCESS;

} /* end of arbFsmRunEventRftestQueryAutoTest() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to prevent state machine hang due to beacon
*        is not able to be received.
*        This timer will be canceled when the 1st beacon after connected
*        is received.
*
* \param[in] prAdapter          Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
arbFsmRunEventAbortOnWaitBeaconTimeOut (
    IN P_ADAPTER_T prAdapter
    )
{
    ASSERT(prAdapter);

    DBGLOG(ARB, EVENT, ("\n\nARB EVENT: Wait Beacon Timeout.\n\n"));

    arbFsmRunEventAbort(prAdapter, FALSE);

    return;
} /* end of arbFsmRunEventAbortOnWaitBeaconTimeOut() */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to handle beacon timeout mechanism for stepping
*        down the beacon timeout value process.
*
* \param[in] prAdapter          Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
arbFsmRunEventContiPollingCheckHandling (
    IN P_ADAPTER_T prAdapter
    )
{
    ASSERT(prAdapter);

    DBGLOG(ARB, EVENT, ("\n\nARB EVENT: Continuous polling check timeout.\n\n"));

    pmHandleContiPollingCheck(prAdapter);

    return;
} /* end of arbFsmRunEventContiPollingCheckHandling() */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to handle beacon timeout mechanism for stepping
*        down the beacon timeout value process.
*
* \param[in] prAdapter          Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
arbFsmRunEventContiHwTxFailCheckHandling (
    IN P_ADAPTER_T prAdapter
    )
{
    P_PM_INFO_T                 prPmInfo;

    ASSERT(prAdapter);

    DBGLOG(ARB, EVENT, ("\n\nARB EVENT: Continuous HW TX fail check timeout.\n\n"));
    DBGLOG(SW3, INFO, ("arbFsmRunEventContiHwTxFailCheckHandling\n"));

    prPmInfo = &prAdapter->rPmInfo;
    prPmInfo->u4ContiHwTxFail = 0;

    return;
} /* end of arbFsmRunEventContiHwTxFailCheckHandling() */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to handle beacon timeout mechanism for stepping
*        down the beacon timeout value process.
*
* \param[in] prAdapter          Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
arbFsmRunEventBeaconTimeoutStepDownHandling (
    IN P_ADAPTER_T prAdapter
    )
{
    P_PM_INFO_T prPmInfo;

    ASSERT(prAdapter);
    prPmInfo = &prAdapter->rPmInfo;

    DBGLOG(ARB, EVENT, ("\n\nARB EVENT: Beacon Timeout step down.\n\n"));

    if (!nicpmStepBeaconTimeout(prAdapter, FALSE)) {
        ARB_CANCEL_TIMER(prAdapter, prPmInfo->rBeaconTimeoutHandlingTimer);
    }

    return;
} /* end of arbFsmRunEventBeaconTimeoutStepDownHandling() */


#if CFG_PEEK_RCPI_VALUE_PERIOD_SEC
/*----------------------------------------------------------------------------*/
/*!
* \brief This function will periodically read the RCPI value for debuging the trend
*        of RCPI change.
*
* \param[in] prAdapter          Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
arbFsmRunEventRcpiDiagnostic (
    IN P_ADAPTER_T prAdapter
    )
{
    RCPI rRcpi;

    ASSERT(prAdapter);

    if (prAdapter->eConnectionState == MEDIA_STATE_CONNECTED) {

        nicRRGetRCPI(prAdapter, &rRcpi);

        DBGLOG(ROAMING, EVENT,
            ("arbFsmRunEventRcpiDiagnostic: Current RCPI = %d\n", rRcpi));

        ARB_SET_TIMER(prAdapter,
                      prAdapter->rRcpiDiagnostic,
                      SEC_TO_MSEC(CFG_PEEK_RCPI_VALUE_PERIOD_SEC));

    }

    return;
} /* end of arbFsmRunEventRcpiDiagnostic() */

#endif /* CFG_PEEK_RCPI_VALUE_PERIOD_SEC */



