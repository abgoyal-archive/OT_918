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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/wlan_oid.c#2 $
*/

/*! \file wlanoid.c
    \brief This file contains the WLAN OID processing routines of Windows driver for
           MediaTek Inc. 802.11 Wireless LAN Adapters.
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
** $Log: wlan_oid.c $
 *
 * 07 10 2010 renbang.jiang
 * [ALPS00121785][Need Patch] [Volunteer Patch] use NVRAM to save Wi-Fi custom data 
 * .
 *
 * 06 13 2010 renbang.jiang
 * [ALPS00008206][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for fixing build warning 
 * .
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\205 2009-10-09 16:59:30 GMT mtk01088
**  save the desired wapi security setting to connection setting for later ap policy selection
**  \main\maintrunk.MT5921\204 2009-10-02 16:57:12 GMT mtk01089
**  add single antenna board design check when setting preferred antenna
**  \main\maintrunk.MT5921\203 2009-09-30 23:00:15 GMT mtk01090
**  Allow ACPI D3/D0 to be set in RFTEST mode.
**  \main\maintrunk.MT5921\202 2009-09-30 15:33:27 GMT mtk01104
**  Add checking of ARB_STATE_RF_TEST in some wlanoidSet...() functions
**  \main\maintrunk.MT5921\201 2009-09-29 16:48:53 GMT mtk01090
**  Fix compile warning
**  \main\maintrunk.MT5921\200 2009-09-28 22:25:11 GMT mtk01090
**  Fix compile error in Linux driver
**  \main\maintrunk.MT5921\199 2009-09-12 13:45:56 GMT mtk01089
**  Add ANTENAA selection OIDs
**  \main\maintrunk.MT5921\198 2009-09-11 20:42:37 GMT mtk01089
**  Add WAPI capability handler
**  \main\maintrunk.MT5921\197 2009-09-09 13:02:13 GMT mtk01089
**  Fix wlanoidQueryWapiCap's comments
**  \main\maintrunk.MT5921\196 2009-09-09 11:28:39 GMT mtk01089
**  \main\maintrunk.MT5921\195 2009-08-18 22:55:53 GMT mtk01090
**  Add Linux SDIO (with mmc core) support.
**  Add Linux 2.6.21, 2.6.25, 2.6.26.
**  Fix compile warning in Linux.
**  \main\maintrunk.MT5921\194 2009-07-12 19:43:11 GMT mtk01090
**  CR1858: Set flag to FALSE to avoid automatic reconnection after switching from D3 to D0 state for non-WinXP cases.
**  \main\maintrunk.MT5921\193 2009-07-08 14:51:56 GMT mtk01088
**  rename the variale pre-fix
**  \main\maintrunk.MT5921\192 2009-07-06 20:17:48 GMT mtk01088
**  adding the related ioctl function for wapi
**  \main\maintrunk.MT5921\191 2009-06-23 22:02:35 GMT mtk01090
**  Correct a comment
**  \main\maintrunk.MT5921\190 2009-04-28 18:55:59 GMT mtk01088
**  move the cipher update for wpa-none to set ssid
**  \main\maintrunk.MT5921\189 2009-04-27 16:55:49 GMT mtk01088
**  While the encrypt status with TKIP or CCMP, use this as data cipher to fixed the add key TKIP/CCMP always with 32 bytes key length issue
**  \main\maintrunk.MT5921\188 2009-04-24 09:08:19 GMT mtk01088
**  mark the code not used at linux supplicant v0.6.7
**  \main\maintrunk.MT5921\187 2009-04-06 15:34:03 GMT mtk01088
**  add the function to set the disable AP selection for privacy check, for wps open networking.
**  \main\maintrunk.MT5921\186 2009-04-03 00:09:11 GMT mtk01461
**  Don't remove scan result, if scan request was not accept after JOIN process in 5 seconds (due to LP func)
**  \main\maintrunk.MT5921\185 2009-03-20 01:03:38 GMT mtk01461
**  Merge the ConnectionReqEvent into AbortEvent
**  \main\maintrunk.MT5921\184 2009-03-09 13:08:28 GMT mtk01461
**  Update query ATIM Window OID
**  \main\maintrunk.MT5921\183 2009-03-09 12:19:59 GMT mtk01461
**  Add Abort event to set Channel(Frequency) / Beacon Interval / ATIM Window for AdHoc Mode
**  \main\maintrunk.MT5921\182 2009-02-16 17:55:54 GMT mtk01084
**  modify for controlling beacon lost detection function
**  \main\maintrunk.MT5921\181 2009-02-09 13:56:17 GMT mtk01090
**  Add kalDevSetPowerState() call in power state change handler function
**  \main\maintrunk.MT5921\180 2009-02-07 15:08:41 GMT mtk01088
**  avoid compiling warning
**  \main\maintrunk.MT5921\179 2009-01-12 15:49:42 GMT mtk01104
**  Fix some wlanoidxxx() function lose the checking of ACPI_D3 state
**  \main\maintrunk.MT5921\178 2009-01-12 14:43:25 GMT mtk01104
**  Mark some lines for compiling error and warning in Linux
**  \main\maintrunk.MT5921\177 2009-01-07 17:32:33 GMT mtk01425
**  1. Add wlanoidQueryBtSingleAntenna, wlanoidQueryPta, wlanoidSetBtSingleAntenna, wlanoidSetPta
**  \main\maintrunk.MT5921\176 2009-01-05 09:58:48 GMT mtk01725
**  Add a function call for setting SLT mode.
**  \main\maintrunk.MT5921\175 2008-12-08 21:27:17 GMT mtk01461
**  Fix lint warning - Null Pointer
**  \main\maintrunk.MT5921\174 2008-12-08 17:06:11 GMT mtk01425
**  1. Fill the command and length into the query buffer in wlanoidQueryBT
**  \main\maintrunk.MT5921\173 2008-12-01 18:14:44 GMT mtk01088
**  fixed the possible use null pointer lint warning
**  \main\maintrunk.MT5921\172 2008-12-01 14:37:27 GMT mtk01425
**  Update variable name
**  \main\maintrunk.MT5921\171 2008-12-01 14:07:39 GMT mtk01461
**  Remove Warning 611: Suspicious cast
**  \main\maintrunk.MT5921\170 2008-12-01 13:09:36 GMT mtk01425
**  1. Add the description of PTA-related functions
**  \main\maintrunk.MT5921\169 2008-12-01 10:06:38 GMT mtk01425
**  1. Add length checking in wlanoidQueryBT and wlanoidQueryContinuousPollInterval
**  \main\maintrunk.MT5921\168 2008-11-24 20:54:30 GMT mtk01425
**  1. Add PTA_ENABLED flag
**  \main\maintrunk.MT5921\167 2008-11-19 11:43:46 GMT mtk01088
**  fixed some lint warning, and rename some variable with pre-fix to avoid the misunderstanding
**  \main\maintrunk.MT5921\166 2008-10-31 14:04:34 GMT mtk01425
**  1. Add function definitions: wlanoidSetBT, wlanoidQueryBT and wlanoidQueryContinuousPollInterval
**  \main\maintrunk.MT5921\165 2008-10-27 15:08:03 GMT mtk01084
**  support continuous polling mode
**  \main\maintrunk.MT5921\164 2008-10-27 14:25:39 GMT mtk01084
**  supporting continuous polling mode
**  \main\maintrunk.MT5921\163 2008-10-24 13:46:27 GMT mtk01084
**  modify input argument of caller to nicSetupOpChnlList()
**  \main\maintrunk.MT5921\162 2008-10-22 10:54:47 GMT mtk01461
**  Update for lint diagnosis support
**  \main\maintrunk.MT5921\161 2008-10-13 10:18:21 GMT mtk01461
**  Fix compile warning in wlanoidQueryCapabilit() for ADS v1.2 build env
**  \main\maintrunk.MT5921\160 2008-10-13 02:05:55 GMT mtk01461
**  Fix compile warning when CFG_TX_FRAGMENT = 0
**  \main\maintrunk.MT5921\159 2008-10-06 14:14:53 GMT mtk01088
**  update the ps profile for mcr test function
**  \main\maintrunk.MT5921\158 2008-10-03 14:56:01 GMT mtk01088
**  add some test code for WMM-PS test engine
**  \main\maintrunk.MT5921\157 2008-10-02 10:23:03 GMT mtk01084
**  enable HW register immediately on WMMPS test OID request
**  \main\maintrunk.MT5921\156 2008-09-12 11:22:40 GMT mtk01461
**  Refine code - Add CFG_TX_FRAGMENT and fix compile warning
**  \main\maintrunk.MT5921\155 2008-09-08 11:24:50 GMT mtk01084
**  modify for the LP instruction programming
**  \main\maintrunk.MT5921\154 2008-08-29 19:38:47 GMT mtk01088
**  fixed the compiling error for bc_address
**  \main\maintrunk.MT5921\153 2008-08-29 18:02:54 GMT mtk01088
**  use define instead of value
**  \main\maintrunk.MT5921\152 2008-08-27 17:42:07 GMT mtk01461
**  Update for driver review
**  \main\maintrunk.MT5921\151 2008-08-27 09:36:47 GMT mtk01084
**  modify for coding rules conformance
**  \main\maintrunk.MT5921\150 2008-08-05 01:51:31 GMT mtk01461
**  Add support for linux statistics
**  \main\maintrunk.MT5921\149 2008-08-01 13:28:57 GMT mtk01084
**  restore comments
**  \main\maintrunk.MT5921\148 2008-07-24 20:13:25 GMT mtk01088
**  flush all pmk cache while oid set number + exist pmk cache count > CFG_MAX_PMKID_COUNT
**  \main\maintrunk.MT5921\147 2008-07-16 15:33:15 GMT mtk01104
**  Add function wlanoidSetGPIO2Mode()
**  \main\maintrunk.MT5921\146 2008-07-15 19:43:32 GMT mtk01104
**  Sync with v144
**  \main\maintrunk.MT5921\145 2008-07-15 19:19:02 GMT mtk01104
**  Remove compiling warning for Windows
**  \main\maintrunk.MT5921\144 2008-07-15 17:53:59 GMT mtk01084
**  rename for WMM-PS test variable
**  \main\maintrunk.MT5921\143 2008-07-15 17:43:07 GMT mtk01084
**  rename variable used under WMM-PS test
**  \main\maintrunk.MT5921\142 2008-07-14 20:54:42 GMT mtk01461
**  Fix the warning message from PREfast
**  \main\maintrunk.MT5921\141 2008-07-14 13:44:43 GMT mtk01104
**  1. wlanoidSetBtCoexistCtrl() replaces wlanoidSetPTAControl()
**  2. Modify fragment flag after completing PTA setting
**  \main\maintrunk.MT5921\140 2008-07-14 11:22:45 GMT mtk01084
**  rename variable name
**  \main\maintrunk.MT5921\139 2008-07-11 17:33:04 GMT mtk01084
**  modify country setting function
**  \main\maintrunk.MT5921\138 2008-07-11 09:29:13 GMT mtk01084
**  fix compiler warning on linux
**  \main\maintrunk.MT5921\137 2008-07-10 16:37:14 GMT mtk01084
**  support 802.11d related functions
**  \main\maintrunk.MT5921\136 2008-07-08 22:31:44 GMT mtk01104
**  Set auto-rate profile instead to set only downLlimit
**  \main\maintrunk.MT5921\135 2008-07-01 20:03:08 GMT mtk01084
**  rename the scan method
**  \main\maintrunk.MT5921\134 2008-07-01 10:54:01 GMT mtk01084
**  revise the VoIP scan procedure under active mode
**  \main\maintrunk.MT5921\133 2008-06-26 21:09:03 GMT mtk01084
**  Add custom OID for WMM-PS tests
**  \main\maintrunk.MT5921\132 2008-06-19 10:13:11 GMT mtk01084
**  support OID for more detail about PTA settings
**  \main\maintrunk.MT5921\131 2008-06-12 21:01:09 GMT mtk01084
**  modify scan channel list ordering
**  \main\maintrunk.MT5921\130 2008-06-12 20:26:57 GMT mtk01461
**  Add dwell min/ext time definition of SCAN parameters
**  \main\maintrunk.MT5921\129 2008-06-12 09:09:36 GMT mtk01104
**  Fix compiling error in Linux
**  \main\maintrunk.MT5921\128 2008-06-10 18:45:49 GMT MTK01088
**  enable wlanoidSetTest function
**  \main\maintrunk.MT5921\127 2008-06-02 22:56:21 GMT mtk01461
**  Rename some functions for Linux Proc
**  \main\maintrunk.MT5921\126 2008-06-02 20:19:22 GMT mtk01461
**  Remove MCR Read / Write functions for Linux, and unify with windows
**  \main\maintrunk.MT5921\125 2008-06-02 11:18:34 GMT mtk01461
**  Update error handling for MCRRead
**  \main\maintrunk.MT5921\124 2008-06-02 10:03:45 GMT MTK01084
**  modify function comments
**  \main\maintrunk.MT5921\123 2008-06-01 17:32:45 GMT mtk01084
**  remove un-used function
**  \main\maintrunk.MT5921\122 2008-05-30 23:07:55 GMT mtk01104
**  Support PTA setting
**  \main\maintrunk.MT5921\121 2008-05-30 19:30:25 GMT mtk01461
**  Update QUERY VOIP STATUS OID to query voip delay
**  \main\maintrunk.MT5921\120 2008-05-30 18:44:50 GMT mtk01461
**  Remove wlanoidSetCSUMOffloadForLinux()
**  \main\maintrunk.MT5921\119 2008-05-30 15:14:20 GMT mtk01084
**  add set/query ATIM, beacon interval, frequency related OID
**  \main\maintrunk.MT5921\118 2008-05-29 14:13:32 GMT mtk01084
**  add task offload and IP address setting related OID
**  \main\maintrunk.MT5921\117 2008-05-23 09:59:39 GMT mtk01084
**  Return status of NOT READY when it is under ACPI D3 under all OID handlers with HW access
**  \main\maintrunk.MT5921\116 2008-05-22 19:38:20 GMT MTK01088
**  Move the mib to connection setting
**  \main\maintrunk.MT5921\115 2008-05-22 10:49:01 GMT mtk01461
**  Change RCV_ERROR OID to withoutHWAccess to reduce the frequence of HW Access
**  \main\maintrunk.MT5921\114 2008-05-21 21:25:02 GMT mtk01084
**  return not_ready status on query SLT result when it is disconnected
**  \main\maintrunk.MT5921\113 2008-05-20 10:32:19 GMT mtk01084
**  add wlanoidQueryLowPowerSltResult() for SLT test for LP
**  \main\maintrunk.MT5921\112 2008-05-16 20:11:01 GMT mtk01461
**  Add scan result aging function at the end of OID_SCAN
**  \main\maintrunk.MT5921\111 2008-05-16 10:31:26 GMT mtk01461
**  Revise RCPI related function for RSSI OID & Roaming
**  \main\maintrunk.MT5921\110 2008-05-15 14:03:31 GMT mtk01461
**  Add Set BSSID OID Support
**  \main\maintrunk.MT5921\109 2008-05-12 16:14:46 GMT mtk01084
**  OID exception handling for the ACPI state and Radio On/ Off state
**  \main\maintrunk.MT5921\108 2008-05-12 15:53:17 GMT mtk01084
**  Modify the place to check ¡§media connect status¡¨ for using the status reported to OS but not driver inside status
**  \main\maintrunk.MT5921\107 2008-05-03 20:21:37 GMT mtk01461
**  Limit the Query RSSI < -10
**  \main\maintrunk.MT5921\106 2008-05-03 12:03:57 GMT mtk01461
**  Fix [WHQL] 2c_PerformanceBlast, move MediaConnect OID to Glue Layer, revise OID_GEN_LINK_SPEED to query SW variable.
**  \main\maintrunk.MT5921\105 2008-04-29 12:00:41 GMT mtk01084
**  add new test function under MCR write path
**  \main\maintrunk.MT5921\104 2008-04-24 22:44:04 GMT mtk01461
**  Add comment to query/set multicast oid, revise set current filter oid
**  \main\maintrunk.MT5921\103 2008-04-24 14:43:25 GMT mtk01084
**  adjust the index for test power mode
**  \main\maintrunk.MT5921\102 2008-04-24 12:06:46 GMT mtk01461
**  Add comment and rename the MC_TYPE enum
**  \main\maintrunk.MT5921\101 2008-04-23 14:11:58 GMT mtk01461
**  Add QueryDesiredRateSet OID
**
**  \main\maintrunk.MT5921\100 2008-04-17 23:06:11 GMT mtk01461
**  Add OID of AdHocMode support
**  \main\maintrunk.MT5921\99 2008-04-13 22:06:18 GMT mtk01461
**  Fix 1c wlan bssid fail after disassociate OID issued
**  \main\maintrunk.MT5921\98 2008-04-13 21:17:03 GMT mtk01461
**  Revise GEN Link Speed OID
**  \main\maintrunk.MT5921\97 2008-04-10 11:43:50 GMT mtk01084
**  fix the issue on return value of the connection status to OS
**  \main\maintrunk.MT5921\96 2008-04-01 23:52:23 GMT mtk01461
**  \main\maintrunk.MT5921\95 2008-03-31 21:00:17 GMT mtk01461
**  Update ASSERT position for some OID
**  \main\maintrunk.MT5921\94 2008-03-31 18:09:57 GMT mtk01461
**  Fix compile error for release build
**  \main\maintrunk.MT5921\93 2008-03-31 13:49:15 GMT mtk01461
**  Add priv oid to turn on/off roaming
**  \main\maintrunk.MT5921\92 2008-03-31 09:47:31 GMT mtk01461
**  Add callback func for assocSendDisAssocFrame
**  \main\maintrunk.MT5921\91 2008-03-30 21:49:53 GMT mtk01084
**  modify for the lengh check issue
**  \main\maintrunk.MT5921\90 2008-03-30 16:49:01 GMT mtk01461
**  Update for change prototype of send Disassoc frame
**  \main\maintrunk.MT5921\89 2008-03-29 13:49:24 GMT mtk01461
**  Add MAGIC GUID for Link List
**  \main\maintrunk.MT5921\88 2008-03-28 10:40:02 GMT mtk01461
**  Add wlanoidSetDesiredRates and remove tempoaray desired rate setting path in linux
**  \main\maintrunk.MT5921\87 2008-03-26 15:32:36 GMT mtk01461
**  Add set MAC Address for Linux
**  Add CSUM offload priv ioctl for Linux
**  \main\maintrunk.MT5921\86 2008-03-20 00:00:15 GMT mtk01461
**  Revise Query BSSID List
**  \main\maintrunk.MT5921\85 2008-03-19 15:21:17 GMT mtk01461
**  Add CFG_TCP_IP_CHKSUM_OFFLOAD flag if set to 0
**  \main\maintrunk.MT5921\84 2008-03-19 11:16:21 GMT mtk01088
**  Not assert for the pvQueryBuffer is NULL, check the length first
**  \main\maintrunk.MT5921\83 2008-03-18 19:56:29 GMT mtk01084
**  add custom function support
**  \main\maintrunk.MT5921\82 2008-03-18 12:00:12 GMT mtk01084
**  modify the AR fail down count parameter when VoIP talking is applied
**  \main\maintrunk.MT5921\81 2008-03-18 09:43:55 GMT mtk01088
**  clear all pmkid candidate and cache for pmkid oid set number is 0
**  \main\maintrunk.MT5921\80 2008-03-14 17:47:00 GMT mtk01385
**  1. return correct length when set OID_802_11_BSSID_LIST_SCAN.
**  2. return correct length when set OID_802_11_BSSID.
**  \main\maintrunk.MT5921\79 2008-03-14 17:29:01 GMT mtk01084
**  modify VoIP related lines
**  \main\maintrunk.MT5921\78 2008-03-13 14:27:02 GMT mtk01461
**  Rename IsValidSSID to IsConnReqIssued
**  \main\maintrunk.MT5921\77 2008-03-11 15:26:06 GMT mtk01461
**  Fix set SSID oid for support RECONNECT
**  \main\maintrunk.MT5921\76 2008-03-11 14:50:20 GMT mtk01461
**  Add Set Beacon Interval oid for adhoc, refine oid for Support WPS
**  \main\maintrunk.MT5921\75 2008-03-11 13:32:25 GMT mtk01084
**  modify arbFsmRunEventScanRequest() function argument
**  \main\maintrunk.MT5921\74 2008-03-10 16:50:00 GMT mtk01088
**  not check the authmode for the oid query and set for pmkid
**  \main\maintrunk.MT5921\73 2008-03-10 15:41:10 GMT mtk01385
**  1. For WHQL test, Rssi should be in range -10 ~ -200 dBm in the reported BSSID list.
**  \main\maintrunk.MT5921\72 2008-03-07 10:49:38 GMT mtk01084
**  add more function description
**  \main\maintrunk.MT5921\71 2008-03-06 09:25:45 GMT mtk01385
**  1. always return success when application issue scan request via OID path.
**  \main\maintrunk.MT5921\70 2008-03-03 21:52:01 GMT mtk01385
**  1. "move scan result" action  move from before scan request to after scan request setup complete.
**  \main\maintrunk.MT5921\69 2008-02-29 13:57:25 GMT mtk01088
**  send disassociate to AP, while do WHQL 2c wpa test, buffalo AP needed STA send disassociate frame, other wise test case will fail
**  \main\maintrunk.MT5921\68 2008-02-29 13:31:41 GMT mtk01088
**  add reloaddefault function support
**  \main\maintrunk.MT5921\67 2008-02-27 12:11:36 GMT mtk01461
**  Change the Time of SCAN aging func and coding style
**  \main\maintrunk.MT5921\66 2008-02-25 17:23:40 GMT mtk01385
**  1. set to Radio Off when disassociation OID issued.
**  \main\maintrunk.MT5921\65 2008-02-25 17:21:48 GMT mtk01385
**  1. Fix Invalid NetworkTypeInUse value in BSSID list.
**  \main\maintrunk.MT5921\64 2008-02-25 16:05:41 GMT mtk01385
**  1. Add network type query/set functions.
**  \main\maintrunk.MT5921\63 2008-02-25 15:49:50 GMT mtk01385
**  1. fix OID retrun length.
**  \main\maintrunk.MT5921\62 2008-02-21 22:47:44 GMT mtk01084
**  use KAL function in related OIDs
**  \main\maintrunk.MT5921\61 2008-02-20 10:14:25 GMT mtk01461
**  Revise BSSID List, get 0 BSSID when Radio is Off
**  \main\maintrunk.MT5921\60 2008-02-19 18:48:30 GMT mtk01461
**  Update SSID OID for adding  eConnectionPolicy - CONNECT_BY_ANY_SSID
**  \main\maintrunk.MT5921\59 2008-02-15 19:18:40 GMT mtk01084
**  revise function name
**  \main\maintrunk.MT5921\58 2008-02-14 09:51:06 GMT mtk01084
**  add OID handlers for PM profiles, pattern search
**  \main\maintrunk.MT5921\57 2008-02-12 23:38:26 GMT mtk01461
**  Add Set Frequency & Channel oid support for Linux
**  \main\maintrunk.MT5921\56 2008-02-12 23:08:58 GMT mtk01461
**  Add TX auto fragmentation for BT support and fix RTS threshold OID.
**
**  \main\maintrunk.MT5921\55 2008-02-12 20:56:29 GMT mtk01084
**  fix the length check error
**  \main\maintrunk.MT5921\54 2008-02-04 17:04:40 GMT mtk01461
**  Refine ARB_IF_IN_RFTEST_STATE
**  \main\maintrunk.MT5921\53 2008-02-01 16:36:07 GMT mtk01385
**  1. fix 64 bit printf issue on Winodws.
**  \main\maintrunk.MT5921\52 2008-01-31 22:36:38 GMT mtk01385
**  1. Fix WinCE 4.2 compiling error.
**  \main\maintrunk.MT5921\51 2008-01-24 14:58:09 GMT mtk01461
**  Fix compile warnning
**  \main\maintrunk.MT5921\50 2008-01-24 12:42:42 GMT mtk01088
**  not clear the pmkid cache for odyssey not set the old AP pmkid cache at doing pre-authentication
**  \main\maintrunk.MT5921\49 2008-01-24 11:58:01 GMT mtk01461
**  Modify the oidQueryConfiguration - if () check the wrong variable
**  \main\maintrunk.MT5921\48 2008-01-22 17:05:31 GMT mtk01084
**  support set/ query packet filter handler
**  \main\maintrunk.MT5921\47 2008-01-09 17:56:25 GMT mtk01084
**  support disassociation OID
**  \main\maintrunk.MT5921\46 2008-01-07 15:04:46 GMT mtk01461
**  Update PhyType/AdHocMode Selection Support
**  \main\maintrunk.MT5921\45 2008-01-03 20:51:44 GMT mtk01084
**  modify lines in setting/ querying RF configuration
**  \main\maintrunk.MT5921\44 2007-12-26 14:24:17 GMT mtk01385
**  1. add ALC value to RFTest Tx Status.
**  \main\maintrunk.MT5921\43 2007-12-24 18:26:46 GMT mtk01088
**  Clear the key while encrypt status set disable
**  \main\maintrunk.MT5921\42 2007-12-16 19:14:07 GMT mtk01084
**  not to do online scan when doing LP IOT
**  \main\maintrunk.MT5921\41 2007-12-04 09:31:36 GMT mtk01425
**  1. Fix bug, wrong parameter at #5149
**  \main\maintrunk.MT5921\40 2007-12-03 18:17:02 GMT mtk01425
**  1. Fix bugs
**  \main\maintrunk.MT5921\39 2007-11-30 17:45:49 GMT mtk01461
**  Fix WZC press Connect button, driver shouldn't indicate disconnect event
**  \main\maintrunk.MT5921\37 2007-11-30 16:30:07 GMT mtk01425
**  1. Fix print modifier warning
**  2. Fix FilterReceive fail
**
**  \main\maintrunk.MT5921\36 2007-11-29 20:31:04 GMT mtk01385
**  1. skip oid execution when arbitor is in RFTEST mode.
**  \main\maintrunk.MT5921\35 2007-11-28 21:36:25 GMT mtk01385
**  1. Fix linux compiling error in query Statistics.
**  \main\maintrunk.MT5921\34 2007-11-26 21:15:51 GMT mtk01385
**  1. add statistics functions.
**  \main\maintrunk.MT5921\33 2007-11-26 19:22:08 GMT mtk01461
**  Unify SCAN of OID Set BSSID, add OID for RTS threshold
**  \main\maintrunk.MT5921\32 2007-11-21 15:23:25 GMT mtk01088
**  remove the printk
**  \main\maintrunk.MT5921\31 2007-11-21 10:29:46 GMT mtk01084
**  update test OID
**  \main\maintrunk.MT5921\30 2007-11-19 10:08:32 GMT mtk01385
**  1. add EEPROM read/write function.
**  2. add Rftest tx/rx status query function.
**  \main\maintrunk.MT5921\29 2007-11-17 15:36:32 GMT mtk01385
**  1. modify MCR read write method.
**  2. add 802.11 configuration query function.
**  \main\maintrunk.MT5921\28 2007-11-13 15:11:56 GMT mtk01088
**  add the code for CETK 1c_OIDs
**  \main\maintrunk.MT5921\27 2007-11-12 16:35:50 GMT mtk01084
**  modify the scan dwell time length from 16 bit to 8 bit
**  \main\maintrunk.MT5921\26 2007-11-09 12:44:56 GMT mtk01084
**  fix compiler error in when define CFG_TX_FRAGMENT == 0
**  \main\maintrunk.MT5921\25 2007-11-08 20:50:58 GMT mtk01088
**  add WPS code
**  \main\maintrunk.MT5921\24 2007-11-08 13:53:08 GMT mtk01084
**  modify for VoIP connection check
**  \main\maintrunk.MT5921\23 2007-11-07 18:34:12 GMT mtk01461
**  Add Tx Fragmentation Support
**  \main\maintrunk.MT5921\22 2007-11-05 16:56:03 GMT mtk01425
**  1. remove DBG flag@3966, @3968
**  \main\maintrunk.MT5921\21 2007-11-01 16:45:14 GMT mtk01084
**  update for LP IOT test for beacon timeout function
**  \main\maintrunk.MT5921\20 2007-11-01 14:53:51 GMT mtk01084
**  1. modify the profile naming
**  2. modify variable naming of the u4ScanDwellTimeMax to u4ScanDwellTimeExt
**  \main\maintrunk.MT5921\19 2007-10-30 09:19:30 GMT mtk01425
**  1. Refine code for multicast list
**  \main\maintrunk.MT5921\18 2007-10-25 20:37:11 GMT mtk01084
**  update ACPI related functions
**  \main\maintrunk.MT5921\17 2007-10-25 17:49:25 GMT mtk01461
**  Modify Internal SCAN Request Interface
** Revision 1.5  2007/07/17 12:51:27  MTK01088
** add oid for security
**
** Revision 1.4  2007/07/04 12:47:57  MTK01088
** update the add wep oid
**
** Revision 1.3  2007/07/04 10:05:36  MTK01088
** The oid enter arbiter to follow the design arch
**
** Revision 1.2  2007/06/27 06:12:04  MTK01088
** add the add wep, add key api
**
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

extern PHY_ATTRIBUTE_T rPhyAttributes[];
extern const UINT_8 aucDataRate[];

/******************************************************************************
*                              C O N S T A N T S
*******************************************************************************
*/
#if DBG
/*lint -save -e64 Type mismatch */
static PUINT_8 apucDebugRateIndex[] = {
            "1M",
            "2M",
            "5_5M",
            "11M",
            "22M",
            "33M",
            "6M",
            "9M",
            "12M",
            "18M",
            "24M",
            "36M",
            "48M",
            "54M"};
/*lint -restore */
#endif /* DBG */

ENUM_POWER_SAVE_PROFILE_T aPowerModeToPwrSaveProfMapping[] =
{
    ENUM_PSP_CONTINUOUS_ACTIVE,     //Param_PowerModeCAM
    ENUM_PSP_CONTINUOUS_POWER_SAVE, //Param_PowerModeMAX_PSP
    ENUM_PSP_FAST_SWITCH            //Param_PowerModeFast_PSP
};

/******************************************************************************
*                             D A T A   T Y P E S
*******************************************************************************
*/

/******************************************************************************
*                            P U B L I C   D A T A
*******************************************************************************
*/
#if DBG
extern UINT_8  aucDebugModule[DBG_MODULE_NUM];
extern UINT_32 u4DebugModule;
UINT_32 u4DebugModuleTemp;
#endif /* DBG */

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
* \brief This routine is called to query the supported physical layer network
*        type that can be used by the driver.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[out] pvQueryBuffer A pointer to the buffer that holds the result of
*                           the query.
* \param[in] u4QueryBufferLen The length of the query buffer.
* \param[out] pu4QueryInfoLen If the call is successful, returns the number of
*                            bytes written into the query buffer. If the call
*                            failed due to invalid length of the query buffer,
*                            returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_LENGTH
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidQueryNetworkTypesSupported (
    IN  P_ADAPTER_T       prAdapter,
    OUT PVOID             pvQueryBuffer,
    IN  UINT_32           u4QueryBufferLen,
    OUT PUINT_32          pu4QueryInfoLen
    )
{
    UINT_32 u4NumItem = 0;
    ENUM_PARAM_NETWORK_TYPE_T eSupportedNetworks[NETWORK_TYPE_NUM];
    PPARAM_NETWORK_TYPE_LIST prSupported;

    /* The array of all physical layer network subtypes that the driver supports. */

    DEBUGFUNC("wlanoidQueryNetworkTypesSupported");

    ASSERT(prAdapter);
    ASSERT(pu4QueryInfoLen);
    ASSERT(pvQueryBuffer);

    /* Init. */
    for (u4NumItem = 0; u4NumItem < NETWORK_TYPE_NUM; u4NumItem++) {
        eSupportedNetworks[u4NumItem] = 0;
    }

    u4NumItem = 0;

    eSupportedNetworks[u4NumItem] = NETWORK_TYPE_DS;
    u4NumItem ++;

    eSupportedNetworks[u4NumItem] = NETWORK_TYPE_OFDM24;
    u4NumItem ++;

    *pu4QueryInfoLen =
        (UINT_32)OFFSET_OF(PARAM_NETWORK_TYPE_LIST, eNetworkType) +
        (u4NumItem * sizeof(ENUM_PARAM_NETWORK_TYPE_T));

    if (u4QueryBufferLen < *pu4QueryInfoLen) {
        return WLAN_STATUS_INVALID_LENGTH;
    }

    prSupported = (PPARAM_NETWORK_TYPE_LIST)pvQueryBuffer;
    prSupported->NumberOfItems = u4NumItem;
    kalMemCopy(prSupported->eNetworkType,
        eSupportedNetworks,
        u4NumItem * sizeof(ENUM_PARAM_NETWORK_TYPE_T));

    DBGLOG(REQ,
        TRACE,
        ("NDIS supported network type list: %ld\n",
        prSupported->NumberOfItems));
    DBGLOG_MEM8(REQ, INFO, prSupported, *pu4QueryInfoLen);

    return WLAN_STATUS_SUCCESS;
} /* wlanoidQueryNetworkTypesSupported */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to query the current physical layer network
*        type used by the driver.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[out] pvQueryBuffer A pointer to the buffer that holds the result of
*             the query.
* \param[in] u4QueryBufferLen The length of the query buffer.
* \param[out] pu4QueryInfoLen If the call is successful, returns the number of
*                             bytes written into the query buffer. If the
*                             call failed due to invalid length of the query
*                             buffer, returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_BUFFER_TOO_SHORT
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidQueryNetworkTypeInUse (
    IN  P_ADAPTER_T       prAdapter,
    OUT PVOID             pvQueryBuffer,
    IN  UINT_32           u4QueryBufferLen,
    OUT PUINT_32          pu4QueryInfoLen
    )
{
    P_BSS_INFO_T prCurrentBss;
    ENUM_PARAM_NETWORK_TYPE_T rCurrentNetworkTypeInUse = NETWORK_TYPE_OFDM24;

    DEBUGFUNC("wlanoidQueryNetworkTypeInUse");

    ASSERT(prAdapter);
    ASSERT(pu4QueryInfoLen);
    if (u4QueryBufferLen) {
        ASSERT(pvQueryBuffer);
    }

    if (u4QueryBufferLen < sizeof(ENUM_PARAM_NETWORK_TYPE_T)) {
        *pu4QueryInfoLen = sizeof(ENUM_PARAM_NETWORK_TYPE_T);
        return WLAN_STATUS_BUFFER_TOO_SHORT;
    }

    prCurrentBss = &prAdapter->rBssInfo;


    if (prAdapter->eConnectionState == MEDIA_STATE_CONNECTED) {
        switch (prCurrentBss->ePhyType) {
        case PHY_TYPE_ERP_INDEX:
            rCurrentNetworkTypeInUse = NETWORK_TYPE_OFDM24;
            DBGLOG(REQ,
                INFO,
                ("Current network type in use: OFDM24 (connected)\n"));
            break;

        case PHY_TYPE_HR_DSSS_INDEX:
            rCurrentNetworkTypeInUse = NETWORK_TYPE_DS;
                DBGLOG(REQ,
                    INFO,
                ("Current network type in use: DS (connected)\n"));
            break;

        case PHY_TYPE_OFDM_INDEX:
            rCurrentNetworkTypeInUse = NETWORK_TYPE_OFDM5;
                DBGLOG(REQ,
                    INFO,
                ("Current network type in use: OFDM5 (connected)\n"));
            break;

        default:
            ASSERT(0); /* Make sure we have handle all STATEs */

        }
    }
    else {
        //kent below line for test
        switch (prAdapter->rConnSettings.eDesiredPhyType) {
        case PHY_TYPE_802_11ABG:
            rCurrentNetworkTypeInUse = NETWORK_TYPE_AUTOMODE;
            DBGLOG(REQ, INFO, ("Current network type in use: AUTO Mode\n"));
            break;
        case PHY_TYPE_802_11BG:
        case PHY_TYPE_802_11G:
            rCurrentNetworkTypeInUse = NETWORK_TYPE_OFDM24;
            DBGLOG(REQ, INFO, ("Current network type in use: OFDM24 Mode\n"));
            break;
        case PHY_TYPE_802_11A:
            rCurrentNetworkTypeInUse = NETWORK_TYPE_OFDM5;
            DBGLOG(REQ, INFO, ("Current network type in use: OFDM5 Mode\n"));
            break;
        case PHY_TYPE_802_11B:
            rCurrentNetworkTypeInUse = NETWORK_TYPE_DS;
            DBGLOG(REQ, INFO, ("Current network type in use: DS Mode\n"));
            break;
        default:
            DBGLOG(REQ, INFO, ("Current network type in use: Unknown\n"));
        }
    }

    ASSERT(pvQueryBuffer);
    *(P_ENUM_PARAM_NETWORK_TYPE_T)pvQueryBuffer = rCurrentNetworkTypeInUse;
    *pu4QueryInfoLen = sizeof(ENUM_PARAM_NETWORK_TYPE_T);

    DBGLOG(REQ, TRACE, ("Network type in use: %d\n", rCurrentNetworkTypeInUse));

    return WLAN_STATUS_SUCCESS;
} /* wlanoidQueryNetworkTypeInUse */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to set the physical layer network type used
*        by the driver.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
* \param[in] pvSetBuffer A pointer to the buffer that holds the data to be set.
* \param[in] u4SetBufferLen The length of the set buffer.
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*                          bytes read from the set buffer. If the call failed
*                          due to invalid length of the set buffer, returns the
*                          amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS The given network type is supported and accepted.
* \retval WLAN_STATUS_INVALID_DATA The given network type is not in the
*                                  supported list.
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidSetNetworkTypeInUse (
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID             pvSetBuffer,
    IN  UINT_32           u4SetBufferLen,
    OUT PUINT_32          pu4SetInfoLen
    )
{
    ENUM_PARAM_NETWORK_TYPE_T eNewNetworkType;
    ENUM_PARAM_PHY_TYPE_T ePhyType = PHY_TYPE_802_11ABG;
    WLAN_STATUS rStatus = WLAN_STATUS_SUCCESS;
    DEBUGFUNC("wlanoidSetNetworkTypeInUse");

    ASSERT(prAdapter);
    ASSERT(pvSetBuffer);
    ASSERT(pu4SetInfoLen);

    if (u4SetBufferLen < sizeof(ENUM_PARAM_NETWORK_TYPE_T)) {
        *pu4SetInfoLen = sizeof(ENUM_PARAM_NETWORK_TYPE_T);
        return WLAN_STATUS_INVALID_LENGTH;
    }

    eNewNetworkType = *(P_ENUM_PARAM_NETWORK_TYPE_T)pvSetBuffer;
    *pu4SetInfoLen = sizeof(ENUM_PARAM_NETWORK_TYPE_T);

    DBGLOG(REQ,
        INFO,
        ("New network type: %d mode\n", eNewNetworkType));

    switch (eNewNetworkType) {

    case NETWORK_TYPE_DS:
        ePhyType = PHY_TYPE_802_11B;
        rStatus = nicCheckAvailablePhyTypeSet(prAdapter, ePhyType);
        break;

    case NETWORK_TYPE_OFDM5:
        ePhyType = PHY_TYPE_802_11A;
        rStatus = nicCheckAvailablePhyTypeSet(prAdapter, ePhyType);
        break;

    case NETWORK_TYPE_OFDM24:
        ePhyType = PHY_TYPE_802_11G;
        rStatus = nicCheckAvailablePhyTypeSet(prAdapter, ePhyType);
        break;

    case NETWORK_TYPE_AUTOMODE:
        ePhyType = PHY_TYPE_802_11ABG;
        rStatus = nicCheckAvailablePhyTypeSet(prAdapter, ePhyType);
        break;

    case NETWORK_TYPE_FH:
        DBGLOG(REQ, INFO, ("Not support network type: %d\n", eNewNetworkType));
        rStatus = WLAN_STATUS_NOT_SUPPORTED;
        break;

    default:
        DBGLOG(REQ, INFO, ("Unknown network type: %d\n", eNewNetworkType));
        rStatus = WLAN_STATUS_INVALID_DATA;
        break;
    }

    /* Verify if we support the new network type. */
    if (rStatus != WLAN_STATUS_SUCCESS) {
        DBGLOG(REQ, WARN, ("Unknown network type: %d\n", eNewNetworkType));
    }
    else {
        /* Save  network type in use. */
        prAdapter->rConnSettings.eDesiredPhyType = ePhyType;
        nicSetAvailablePhyTypeSet(prAdapter);
    }

    return rStatus;
} /* wlanoidSetNetworkTypeInUse */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to query the current BSSID.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[out] pvQueryBuffer A pointer to the buffer that holds the result of
*                           the query.
* \param[in] u4QueryBufferLen The length of the query buffer.
* \param[out] pu4QueryInfoLen If the call is successful, returns the number of
*                             bytes written into the query buffer. If the call
*                             failed due to invalid length of the query buffer,
*                             returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_ADAPTER_NOT_READY
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidQueryBssid (
    IN  P_ADAPTER_T       prAdapter,
    OUT PVOID             pvQueryBuffer,
    IN  UINT_32           u4QueryBufferLen,
    OUT PUINT_32          pu4QueryInfoLen
    )
{
    WLAN_STATUS rStatus = WLAN_STATUS_SUCCESS;

    DEBUGFUNC("wlanoidQueryBssid");

    ASSERT(prAdapter);
    ASSERT(pu4QueryInfoLen);

    *pu4QueryInfoLen = MAC_ADDR_LEN;

    if (u4QueryBufferLen < MAC_ADDR_LEN) {
        ASSERT(pu4QueryInfoLen);
        return WLAN_STATUS_BUFFER_TOO_SHORT;
    }

    ASSERT(u4QueryBufferLen >= MAC_ADDR_LEN);
    ASSERT(pvQueryBuffer);
    ASSERT(pu4QueryInfoLen);

    if (IS_ARB_IN_RFTEST_STATE(prAdapter)) {
        return rStatus;
    }

    if (prAdapter->eConnectionStateIndicated == MEDIA_STATE_CONNECTED) {
        COPY_MAC_ADDR(pvQueryBuffer, prAdapter->rBssInfo.aucBSSID);

        DBGLOG(REQ,
            TRACE,
            ("Associated BSSID: "MACSTR"\n",
            MAC2STR(prAdapter->rBssInfo.aucBSSID)));
    }
    else if (prAdapter->rConnSettings.eOPMode == NET_TYPE_IBSS) {
        UINT_8 aucTemp[MAC_ADDR_LEN] = {0};
        // return IBSS MAC Address as described by MSDN
        if (!kalMemCmp(prAdapter->rBssInfo.aucBSSID, aucTemp, MAC_ADDR_LEN)) {
            /* all 0 */
            COPY_MAC_ADDR(aucTemp, prAdapter->aucMacAddress);
            aucTemp[0] &= ~BIT(0); // 7.1.3.3.3 - The individual/group bit of the address is set to 0.
            aucTemp[0] |= BIT(1); // 7.1.3.3.3 - The universal/local bit of the address is set to 1.
            COPY_MAC_ADDR(pvQueryBuffer, aucTemp);
        }
        else {
            COPY_MAC_ADDR(pvQueryBuffer, prAdapter->rBssInfo.aucBSSID);
        }
        DBGLOG(REQ,
            TRACE,
            ("Current BSSID in: "MACSTR" (MAC addr)\n",
            MAC2STR(pvQueryBuffer)));

    }
    else {
        DBGLOG(REQ, TRACE, ("The NIC is not associated with an access point.\n"));
        rStatus = WLAN_STATUS_ADAPTER_NOT_READY;
    }

    return rStatus;
} /* wlanoidQueryBssid */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to build up the BSSID list according to
*        scan result.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[out] pvDest Pointer to the buffer to put the BSSID list.
* \param[in] u4MaxBufLen The length of the buffer.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
BOOLEAN
wlanoidBuildBssListFromScanResult (
    IN  P_ADAPTER_T       prAdapter,
    OUT PVOID             pvDest,
    IN  UINT_32           u4MaxBufLen
    )
{
    P_PARAM_BSSID_EX_T prBssidEx;
    P_PARAM_BSSID_LIST_EX_T prList;
    P_SCAN_INFO_T prScanInfo;
    P_LINK_T prBSSDescList;
    P_BSS_DESC_T prScanResult = (P_BSS_DESC_T)NULL;
    PUINT_8 cp;
    UINT_32 tmpLen = 0;
    UINT_32 u4BssRecLen;
    UINT_8 rateLen;

    DEBUGFUNC("wlanoidBuildBssListFromScanResult");

    ASSERT(prAdapter);
    ASSERT(pvDest);

    prScanInfo =  &prAdapter->rScanInfo;
    prBSSDescList = &prScanInfo->rBSSDescList;

    prList = (P_PARAM_BSSID_LIST_EX_T)pvDest;
    cp = (PUINT_8)&prList->arBssid[0];

    tmpLen = OFFSET_OF(PARAM_BSSID_LIST_EX_T, arBssid);

    prList->u4NumberOfItems = 0;

    /* Maximum report CFG_MAX_NUM_BSS_LIST */
    ASSERT(prAdapter->rScanInfo.rBSSDescList.u4NumElem <= CFG_MAX_NUM_BSS_LIST);

    /* Refresh the list of BSSIDs with the newest scan results. */
    LINK_FOR_EACH_ENTRY(prScanResult, prBSSDescList, rLinkEntry, BSS_DESC_T) {

        BSS_DESC_CHK_GUID(prScanResult);

        DBGLOG(REQ,
            INFO,
            ("SSID: %s Channel: %d BCN Interval: %d\n",
            prScanResult->aucSSID,
            prScanResult->ucChannelNum,
            prScanResult->u2BeaconInterval));

        /* Update PARAM_BSSID_EX */
        prBssidEx = (P_PARAM_BSSID_EX_T)cp;

        /* Calculate this BSS's record length and make sure buffer is enough
        * This may happen when scan is not complete and OS query scan result.
        */
        u4BssRecLen = ((UINT_32)OFFSET_OF(PARAM_BSSID_EX_T, aucIEs) +
            prScanResult->u2IELength + 3) & 0xfffffffc;

        if (tmpLen + u4BssRecLen > u4MaxBufLen)
            break;


        /* Fill in the BSSID list with the scan result. */
        COPY_MAC_ADDR((PVOID)prBssidEx->arMacAddress, prScanResult->aucBSSID);

        COPY_SSID(prBssidEx->rSsid.aucSsid,
                  prBssidEx->rSsid.u4SsidLen,
                  prScanResult->aucSSID,
                  (UINT_32)prScanResult->ucSSIDLen);

        if (prScanResult->u2CapInfo & CAP_INFO_PRIVACY) {
            prBssidEx->u4Privacy = 1;
        }
        else {
            prBssidEx->u4Privacy = 0;
        }

        prBssidEx->rRssi = RCPI_TO_dBm(prScanResult->rRcpi);

        /*For WHQL test, Rssi should be in range -10 ~ -200 dBm*/
        if(prBssidEx->rRssi > PARAM_WHQL_RSSI_MAX_DBM) {
            prBssidEx->rRssi = PARAM_WHQL_RSSI_MAX_DBM;
        }

        if (prScanResult->ePhyType == PHY_TYPE_ERP_INDEX) {
            prBssidEx->eNetworkTypeInUse = NETWORK_TYPE_OFDM24;
        }
        else if (prScanResult->ePhyType == PHY_TYPE_HR_DSSS_INDEX) {
            prBssidEx->eNetworkTypeInUse = NETWORK_TYPE_DS;
        }
        else {
            ASSERT(prScanResult->ePhyType == PHY_TYPE_OFDM_INDEX);
            prBssidEx->eNetworkTypeInUse = NETWORK_TYPE_OFDM5;
        }

        prBssidEx->rConfiguration.u4Length = sizeof(PARAM_802_11_CONFIG_T);
        prBssidEx->rConfiguration.u4BeaconPeriod =
            (UINT_32)prScanResult->u2BeaconInterval;
        prBssidEx->rConfiguration.u4ATIMWindow =
            (UINT_32)prScanResult->u2ATIMWindow;

        {
            P_RF_CHANNEL_PROG_ENTRY prChProgEntry;

            prChProgEntry =
                halRFGetRFChnlProgEntry(prAdapter,
                                        (UINT_8)prScanResult->ucChannelNum ,
                                        prScanResult->eBand);
            if (prChProgEntry) {
                prBssidEx->rConfiguration.u4DSConfig = prChProgEntry->u4ChannelFreq;
            }
        }

        prBssidEx->rConfiguration.rFHConfig.u4Length =
            sizeof(PARAM_802_11_CONFIG_FH_T);

        if (prScanResult->eBSSType == BSS_TYPE_INFRASTRUCTURE) {
            prBssidEx->eOpMode = NET_TYPE_INFRA;
        }
        else {
            prBssidEx->eOpMode = NET_TYPE_IBSS;
        }

        /* Build supRates from rate set */
        rateGetDataRatesFromRateSet(
            prScanResult->u2OperationalRateSet,
            0x0, /*(UINT_16)NULL*/
            prBssidEx->rSupportedRates,
            &rateLen);

        DBGLOG(REQ,
            TRACE,
            ("Rate Len:%d Scan BSS:0x%08x\n",
            rateLen,
            prScanResult->u2OperationalRateSet));
#if DBG
        DBGLOG(REQ,
            INFO,
            ("Rates %d %d %d %d %d %d %d %d - %d %d %d %d %d %d %d %d\n",
            prBssidEx->rSupportedRates[0],
            prBssidEx->rSupportedRates[1],
            prBssidEx->rSupportedRates[2],
            prBssidEx->rSupportedRates[3],
            prBssidEx->rSupportedRates[4],
            prBssidEx->rSupportedRates[5],
            prBssidEx->rSupportedRates[6],
            prBssidEx->rSupportedRates[7],
            prBssidEx->rSupportedRates[8],
            prBssidEx->rSupportedRates[9],
            prBssidEx->rSupportedRates[10],
            prBssidEx->rSupportedRates[11],
            prBssidEx->rSupportedRates[12],
            prBssidEx->rSupportedRates[13],
            prBssidEx->rSupportedRates[14],
            prBssidEx->rSupportedRates[15]));
#endif

        prBssidEx->u4IELength = prScanResult->u2IELength;
        kalMemCopy((PVOID)prBssidEx->aucIEs,
            (PVOID)prScanResult->aucIEBuf,
            prScanResult->u2IELength);

        prBssidEx->u4Length = ALIGN_4((UINT_32)OFFSET_OF(PARAM_BSSID_EX_T, aucIEs) + prBssidEx->u4IELength);

        DBGLOG(RSN, INFO, DUMPVAR(prBssidEx->u4Length, "%ld"));
        DBGLOG(RSN, INFO, DUMPVAR(prBssidEx->u4IELength, "%ld"));

        cp += prBssidEx->u4Length;

        tmpLen += prBssidEx->u4Length;
        prList->u4NumberOfItems ++;
    }

    DBGLOG(REQ, TRACE, ("Result:%ld total len:%ld\n", prList->u4NumberOfItems, tmpLen));

    ASSERT(prList->u4NumberOfItems <= CFG_MAX_NUM_BSS_LIST);

    return TRUE;
} /* wlanoidBuildBssListFromScanResult */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to query the list of all BSSIDs detected by
*        the driver.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[out] pvQueryBuffer A pointer to the buffer that holds the result of
*                           the query.
* \param[in] u4QueryBufferLen The length of the query buffer.
* \param[out] pu4QueryInfoLen If the call is successful, returns the number of
*                             bytes written into the query buffer. If the call
*                             failed due to invalid length of the query buffer,
*                             returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_LENGTH
* \retval WLAN_STATUS_ADAPTER_NOT_READY
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidQueryBssidList (
    IN  P_ADAPTER_T       prAdapter,
    OUT PVOID             pvQueryBuffer,
    IN  UINT_32           u4QueryBufferLen,
    OUT PUINT_32          pu4QueryInfoLen
    )
{
    P_SCAN_INFO_T prScanInfo;
    P_LINK_T prBSSDescList;
    P_BSS_DESC_T prBssDesc = (P_BSS_DESC_T)NULL;
    UINT_32 u4BssidListExLen;

    DEBUGFUNC("wlanoidQueryBssidList");


    ASSERT(prAdapter);
    ASSERT(pu4QueryInfoLen);
    if (u4QueryBufferLen) {
        ASSERT(pvQueryBuffer);
    }

    prScanInfo =  &prAdapter->rScanInfo;
    prBSSDescList = &prScanInfo->rBSSDescList;

    DBGLOG(REQ, INFO, DUMPVAR(prBSSDescList->u4NumElem, "%lu"));

    if (prAdapter->rAcpiState == ACPI_STATE_D3) {
        DBGLOG(REQ, WARN, ("Fail in qeury BSSID list! (Adapter not ready). ACPI=D%d, Radio=%d\n",
                    prAdapter->rAcpiState, prAdapter->fgIsRadioOff));
        u4BssidListExLen = sizeof(PARAM_BSSID_LIST_EX_T);
        return WLAN_STATUS_ADAPTER_NOT_READY;
    }

#if !defined(LINUX)
    if (prAdapter->fgIsRadioOff) {
        u4BssidListExLen = sizeof(PARAM_BSSID_LIST_EX_T);
    }
    else
#endif /* LINUX */
    {
        u4BssidListExLen = 0;

        if (LINK_IS_VALID(prBSSDescList)) {
            LINK_FOR_EACH_ENTRY(prBssDesc, prBSSDescList, rLinkEntry, BSS_DESC_T) {

                BSS_DESC_CHK_GUID(prBssDesc);

                u4BssidListExLen += (sizeof(PARAM_BSSID_EX_T) - 1 +
                    ALIGN_4(prBssDesc->u2IELength));
            }
        }

        if (u4BssidListExLen) {
            u4BssidListExLen += 4; // u4NumberOfItems.
        }
        else {
            u4BssidListExLen = sizeof(PARAM_BSSID_LIST_EX_T);
        }
    }

    *pu4QueryInfoLen = u4BssidListExLen;

    if (u4QueryBufferLen < *pu4QueryInfoLen) {
        return WLAN_STATUS_INVALID_LENGTH;
    }

    /* Clear the buffer */
    kalMemZero(pvQueryBuffer, u4BssidListExLen);

    /* Build up BSSID list from scan result */
#if !defined(LINUX)
    if (!prAdapter->fgIsRadioOff)
#endif /* LINUX */
    {
        if (prBSSDescList->u4NumElem) {
            wlanoidBuildBssListFromScanResult(prAdapter, pvQueryBuffer, u4QueryBufferLen);
        }
    }

    DBGLOG(REQ, LOUD, ("NDIS extended BSSID list:\n"));
    DBGLOG_MEM8(REQ, LOUD, pvQueryBuffer, *pu4QueryInfoLen);

    return WLAN_STATUS_SUCCESS;
} /* wlanoidQueryBssidList */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to request the driver to perform
*        scanning.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[in] pvSetBuffer Pointer to the buffer that holds the data to be set.
* \param[in] u4SetBufferLen The length of the set buffer.
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*                          bytes read from the set buffer. If the call failed
*                          due to invalid length of the set buffer, returns
*                          the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_ADAPTER_NOT_READY
* \retval WLAN_STATUS_FAILURE
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidSetBssidListScan (
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID             pvSetBuffer,
    IN  UINT_32           u4SetBufferLen,
    OUT PUINT_32          pu4SetInfoLen
    )
{
    SCAN_REQ_CONFIG_T rScanReqConfig;
    BOOLEAN fgIsSpecifiedSSID = FALSE;
    WLAN_STATUS rStatus;
    P_CONNECTION_SETTINGS_T prConnSettings;

    DEBUGFUNC("wlanoidSetBssidListScan");

    ASSERT(prAdapter);
    ASSERT(pu4SetInfoLen);

    *pu4SetInfoLen = u4SetBufferLen;

    prConnSettings = &prAdapter->rConnSettings;

    if (IS_ARB_IN_RFTEST_STATE(prAdapter)) {
        return WLAN_STATUS_SUCCESS;
    }

#if CFG_LP_IOT
    if (prAdapter->eConnectionState == MEDIA_STATE_CONNECTED) {
        return WLAN_STATUS_SUCCESS;
    }
#endif

    if (prAdapter->rAcpiState == ACPI_STATE_D3) {
        DBGLOG(REQ, WARN, ("Fail in set BSSID list scan! (Adapter not ready). ACPI=D%d, Radio=%d\n",
                    prAdapter->rAcpiState, prAdapter->fgIsRadioOff));
        return WLAN_STATUS_ADAPTER_NOT_READY;
    }

    if (prAdapter->fgIsRadioOff) {
        DBGLOG(REQ, WARN, ("Return from BSSID list scan! (radio off). ACPI=D%d, Radio=%d\n",
                    prAdapter->rAcpiState, prAdapter->fgIsRadioOff));
        return WLAN_STATUS_SUCCESS;
    }

    kalMemZero(&rScanReqConfig.rSpecifiedSsid,
               sizeof(PARAM_SSID_T));

    if ((prAdapter->rConnSettings.fgIsConnReqIssued) &&
        (prAdapter->rConnSettings.eConnectionPolicy != CONNECT_BY_SSID_ANY)) {
		//add by mtk80743
		if(pvSetBuffer != NULL && u4SetBufferLen != 0){
			COPY_SSID(prAdapter->rConnSettings.aucSSID,
					  prAdapter->rConnSettings.ucSSIDLen,
						pvSetBuffer,
						u4SetBufferLen);

		}else{//end mtk80743
        COPY_SSID(rScanReqConfig.rSpecifiedSsid.aucSsid,
                  rScanReqConfig.rSpecifiedSsid.u4SsidLen,
                  prAdapter->rConnSettings.aucSSID,
                  prAdapter->rConnSettings.ucSSIDLen);
		}

        fgIsSpecifiedSSID = TRUE;

        DBGLOG(REQ, TRACE, ("Scan SSID:%s SSID Len:%d\n",
            prAdapter->rConnSettings.aucSSID,
            prAdapter->rConnSettings.ucSSIDLen));
    }

    if (prAdapter->eConnectionState == MEDIA_STATE_DISCONNECTED) {

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
        rScanReqConfig.ucNumOfSpecifiedSsidPrbReq =
            fgIsSpecifiedSSID ? FULL_SCAN_SPECIFIC_PROBE_REQ_NUM : 0;
    }
    else {

        if (PM_IS_VOIP_POLLING_ENABLED(prAdapter)) {
            rScanReqConfig.eScanMethod = SCAN_METHOD_VOIP_ONLINE_SCAN;

            /* 12 milliseconds. If detect the air activity by MDRDY,
             * this is the transmission time of 1Mbps with 1536 Bytes.
             */
            rScanReqConfig.ucChnlDwellTimeMin = SCAN_CHANNEL_DWELL_TIME_MIN;

            /* 20 milliseconds for VOIP application, N = 20 - Min(12) = 8 milliseconds */
            rScanReqConfig.ucChnlDwellTimeExt = VOIP_SCAN_CHANNEL_DWELL_TIME_EXT;

            rScanReqConfig.ucNumOfPrbReq = PS_VOIP_PARTIAL_SCAN_TOTAL_PROBE_REQ_NUM;
            rScanReqConfig.ucNumOfSpecifiedSsidPrbReq = PS_VOIP_PARTIAL_SCAN_SPECIFIC_PROBE_REQ_NUM;
        }
        else if (prConnSettings->fgIsVoipConn) {
            rScanReqConfig.eScanMethod = SCAN_METHOD_VOIP_ONLINE_SCAN;

            /* 12 milliseconds. If detect the air activity by MDRDY,
             * this is the transmission time of 1Mbps with 1536 Bytes.
             */
            rScanReqConfig.ucChnlDwellTimeMin = SCAN_CHANNEL_DWELL_TIME_MIN;

            /* 20 milliseconds for VOIP application, N = 20 - Min(12) = 8 milliseconds */
            rScanReqConfig.ucChnlDwellTimeExt = VOIP_SCAN_CHANNEL_DWELL_TIME_EXT;

            rScanReqConfig.ucNumOfPrbReq = VOIP_PARTIAL_SCAN_TOTAL_PROBE_REQ_NUM;
            rScanReqConfig.ucNumOfSpecifiedSsidPrbReq = VOIP_PARTIAL_SCAN_SPECIFIC_PROBE_REQ_NUM;
        }
        else {
            rScanReqConfig.eScanMethod = SCAN_METHOD_ONLINE_SCAN;

            /* 12 milliseconds. If detect the air activity by MDRDY,
             * this is the transmission time of 1Mbps with 1536 Bytes.
             */
            rScanReqConfig.ucChnlDwellTimeMin = SCAN_CHANNEL_DWELL_TIME_MIN;

            /* N milliseconds = 100TU(Beacon Interval) - min + 10TU
             * (if Beacon Drift) = 98TU(round down to millisecond).
             */
            rScanReqConfig.ucChnlDwellTimeExt = SCAN_CHANNEL_DWELL_TIME_EXT;

            rScanReqConfig.ucNumOfPrbReq = PARTIAL_SCAN_TOTAL_PROBE_REQ_NUM;
            rScanReqConfig.ucNumOfSpecifiedSsidPrbReq =
                fgIsSpecifiedSSID ? PARTIAL_SCAN_SPECIFIC_PROBE_REQ_NUM : 0;
        }
    }

    rScanReqConfig.eScanType = SCAN_TYPE_ACTIVE_SCAN;

    rScanReqConfig.pfScanDoneHandler = (PFN_SCAN_DONE_HANDLER)0;

    {
        UINT_32 i, j, u4ScanIndex = 0;

        rScanReqConfig.ucNumOfScanChnl = (UINT_8)prAdapter->u2NicOpChnlNum;

        for (j = 0; j < INTERLACED_SCAN_CHANNEL_GROUPS_NUM; j++) {
            for (i = j;
                 ((i < rScanReqConfig.ucNumOfScanChnl)
                    && (i < MAXIMUM_OPERATION_CHANNEL_LIST)
                    && (u4ScanIndex < sizeof(rScanReqConfig.arChnlInfoList) /sizeof(rScanReqConfig.arChnlInfoList[0])));
                 i += INTERLACED_SCAN_CHANNEL_GROUPS_NUM, u4ScanIndex++) {

                rScanReqConfig.arChnlInfoList[u4ScanIndex].ucChannelNum =
                    prAdapter->arNicOpChnList[i].ucChannelNum;
                rScanReqConfig.arChnlInfoList[u4ScanIndex].eBand =
                    prAdapter->arNicOpChnList[i].eBand;
            }
        }
    }

    if ((rStatus = arbFsmRunEventScanRequest(prAdapter, &rScanReqConfig, FALSE)) ==
        WLAN_STATUS_FAILURE) {
        DBGLOG(REQ, TRACE, ("Scan Request was failed due to another SCAN is proceeding.\n"));

        rStatus = WLAN_STATUS_SUCCESS;
        /* NOTE(Kevin): What will happen if reply the WLAN_STATUS_FAILURE to OID */
    }
    else {
        /* NOTE(Kevin): Because we always return SUCCESS, so we should do aging at
         * least for OID_SCAN.
         */
        scanRemoveBssDescsByPolicy(prAdapter, (SCAN_RM_POLICY_EXCLUDE_CONNECTED | \
                                               SCAN_RM_POLICY_TIMEOUT) );
    }

    return rStatus;
} /* wlanoidSetBssidListScan */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine will initiate the join procedure to attempt to associate
*        with the specified BSSID.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
* \param[in] pvSetBuffer A pointer to the buffer that holds the data to be set.
* \param[in] u4SetBufferLen The length of the set buffer.
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*                          bytes read from the set buffer. If the call failed
*                          due to invalid length of the set buffer, returns
*                          the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_LENGTH
* \retval WLAN_STATUS_INVALID_DATA
* \retval WLAN_STATUS_ADAPTER_NOT_READY
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidSetBssid (
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID             pvSetBuffer,
    IN  UINT_32           u4SetBufferLen,
    OUT PUINT_32          pu4SetInfoLen
    )
{
    P_CONNECTION_SETTINGS_T prConnSettings;
    UINT_8 aucAnyBSSID[] = BC_BSSID;
    UINT_8 aucNullBSSID[] = NULL_MAC_ADDR;
    PUINT_8 pucNewBSSID;
    BOOLEAN fgTryToAssociate = FALSE;


    ASSERT(prAdapter);
    ASSERT(pu4SetInfoLen);
    prConnSettings = &prAdapter->rConnSettings;

    DBGLOG(REQ, TRACE, ("\n"));

    *pu4SetInfoLen = MAC_ADDR_LEN;

    if (u4SetBufferLen != MAC_ADDR_LEN) {
        return WLAN_STATUS_INVALID_LENGTH;
    }

    if (IS_ARB_IN_RFTEST_STATE(prAdapter)) {
        return WLAN_STATUS_SUCCESS;
    }

    if (prAdapter->fgIsRadioOff || (prAdapter->rAcpiState == ACPI_STATE_D3)) {
        DBGLOG(REQ, WARN, ("Fail in set BSSID! (Adapter not ready). ACPI=D%d, Radio=%d\n",
                    prAdapter->rAcpiState, prAdapter->fgIsRadioOff));
        return WLAN_STATUS_ADAPTER_NOT_READY;
    }

    ASSERT(pvSetBuffer);
    pucNewBSSID = (PUINT_8)pvSetBuffer;

    if (EQUAL_MAC_ADDR(pucNewBSSID, aucNullBSSID)) {
        DBGLOG(REQ, TRACE, ("Can't accept null BSSID\n"));
        return WLAN_STATUS_INVALID_DATA;
    }

    /* NOTE(Kevin): We do association or reassociation only if the desired BSSID
     * is changed. We don't care if it is not changed from MSDN.
     */
    if (UNEQUAL_MAC_ADDR(prConnSettings->aucBSSID, pucNewBSSID)) {

        fgTryToAssociate = TRUE;

        /* Update the BSSID in Connection Settings */
        COPY_MAC_ADDR(prConnSettings->aucBSSID, pucNewBSSID);

        /* Update the related flags */
        if (EQUAL_MAC_ADDR(prConnSettings->aucBSSID, aucAnyBSSID)) {
            prConnSettings->fgIsConnByBssidIssued = FALSE;
            prConnSettings->fgIsEnableRoaming = TRUE;
        }
        else {
            prConnSettings->fgIsConnByBssidIssued = TRUE;
            prConnSettings->fgIsEnableRoaming = FALSE;
        }
    }


    /* NOTE(Kevin): We only do association within the current Extended Service Set.
     * Which means we should know the connection policy of SSID first.
     */
    if ((fgTryToAssociate) &&
        (prConnSettings->fgIsConnReqIssued)) {

        //Housekeeping for STA_RECORD_T aging func, do it only at Connection Req Event.
        staRecRemoveStaRecordByPolicy(prAdapter, STA_RECORD_RM_POLICY_TIMEOUT);

        /* Send the "Abort" event to arbiter. Always TRUE for delaying Disconnect
         * Indication.
         */
        arbFsmRunEventAbort(prAdapter, TRUE); /* Reset to STANDBY */
    }

    /* TODO(Kevin): Driver should attempt to associate with the BSSID even if the
     * BSSID is not in the BSSID scan list.
     */

    return WLAN_STATUS_SUCCESS;

} /* end of wlanoidSetBssid() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine will initiate the join procedure to attempt
*        to associate with the new SSID. If the previous scanning
*        result is aged, we will scan the channels at first.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[in] pvSetBuffer Pointer to the buffer that holds the data to be set.
* \param[in] u4SetBufferLen The length of the set buffer.
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*                           bytes read from the set buffer. If the call failed
*                           due to invalid length of the set buffer, returns
*                           the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_DATA
* \retval WLAN_STATUS_ADAPTER_NOT_READY
* \retval WLAN_STATUS_INVALID_LENGTH
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidSetSsid (
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID             pvSetBuffer,
    IN  UINT_32           u4SetBufferLen,
    OUT PUINT_32          pu4SetInfoLen
    )
{
    P_PARAM_SSID_T prNewSsid;
    P_CONNECTION_SETTINGS_T prConnSettings;
    BOOLEAN fgIsDelayMediaStateIndication = FALSE;
    P_SW_KEY_STRUC_T         prDefSwKey = NULL;

    DEBUGFUNC("wlanoidSetSsid");


    ASSERT(prAdapter);
    ASSERT(pu4SetInfoLen);
    prConnSettings = &prAdapter->rConnSettings;

    DBGLOG(REQ, TRACE, ("\n"));

    *pu4SetInfoLen = sizeof(PARAM_SSID_T);

    if (u4SetBufferLen < *pu4SetInfoLen) {
        DBGLOG(REQ, WARN, ("Invalid length %lu\n", u4SetBufferLen));
        return WLAN_STATUS_INVALID_LENGTH;
    }

    if (IS_ARB_IN_RFTEST_STATE(prAdapter)) {
        return WLAN_STATUS_SUCCESS;
    }

    if (prAdapter->rAcpiState == ACPI_STATE_D3) {
        DBGLOG(REQ, WARN, ("Fail in set SSID! (Adapter not ready). ACPI=D%d, Radio=%d\n",
                    prAdapter->rAcpiState, prAdapter->fgIsRadioOff));
        return WLAN_STATUS_ADAPTER_NOT_READY;
    }

    ASSERT(pvSetBuffer);
    prNewSsid = (P_PARAM_SSID_T)pvSetBuffer;

    /* Verify the length of the new SSID. */
    if (prNewSsid->u4SsidLen > PARAM_MAX_LEN_SSID) {
        DBGLOG(REQ,
            TRACE,
            ("Invalid SSID length %lu\n",
            prNewSsid->u4SsidLen));
        return WLAN_STATUS_INVALID_DATA;
    }

    /* WPA-NONE, at Windows Mobile 6.x, the encryption status is set after the key,
           For TKIP/AES, key length is always 32, so we needed to update the cipher at here,
           to let the data path can work */
    if (prConnSettings->eAuthMode == AUTH_MODE_WPA_NONE) {

        prDefSwKey = (P_SW_KEY_STRUC_T)&prAdapter->arWlanCtrl[WLAN_TABLE_DEFAULT_ENTRY].rSWKey;

        if (prConnSettings->eEncStatus == ENUM_ENCRYPTION2_ENABLED) {
            prDefSwKey->ucCipher = CIPHER_SUITE_TKIP;
        }
        else if (prConnSettings->eEncStatus == ENUM_ENCRYPTION3_ENABLED) {
            prDefSwKey->ucCipher = CIPHER_SUITE_CCMP;
        }

        if (prDefSwKey->ucCipher == CIPHER_SUITE_TKIP ||
            prDefSwKey->ucCipher == CIPHER_SUITE_CCMP) {
            nicPrivacyDumpWlanTable(prAdapter, WLAN_TABLE_DEFAULT_ENTRY);

            halWlanTableAccess(prAdapter,
                               (PVOID)prDefSwKey,
                                WLAN_TABLE_DEFAULT_ENTRY,
                                HWTDR_UPDATE_MODE_3);     /* Set key into H/W key table */
        }
    }

    if (EQUAL_SSID(prConnSettings->aucSSID, prConnSettings->ucSSIDLen,
            prNewSsid->aucSsid, (UINT_8)prNewSsid->u4SsidLen)) {
        fgIsDelayMediaStateIndication = TRUE;
    }
    else {
        fgIsDelayMediaStateIndication = FALSE;

        /* Set the SSID with the specified value or set it to any SSID if the SSID
           is not specified. */
        kalMemZero(prConnSettings->aucSSID, sizeof(prConnSettings->aucSSID));
        COPY_SSID(prConnSettings->aucSSID,
                  prConnSettings->ucSSIDLen,
                  prNewSsid->aucSsid,
                  (UINT_8)prNewSsid->u4SsidLen);
    }

    DBGLOG(REQ, INFO, ("New SSID:%s SSID Len:%d\n",
        prConnSettings->aucSSID, prConnSettings->ucSSIDLen));

    prConnSettings->fgIsConnReqIssued = TRUE;

    if (prConnSettings->ucSSIDLen) {
        prConnSettings->eConnectionPolicy = CONNECT_BY_SSID_BEST_RSSI;
    }
    else {
        prConnSettings->eConnectionPolicy = CONNECT_BY_SSID_ANY;
    }


    //Housekeeping for STA_RECORD_T aging func, do it only at Connection Req Event.
    staRecRemoveStaRecordByPolicy(prAdapter, STA_RECORD_RM_POLICY_TIMEOUT);

    /* Send the "Abort" event to arbiter. */
    arbFsmRunEventAbort(prAdapter, fgIsDelayMediaStateIndication); /* Reset to STANDBY */

    return WLAN_STATUS_SUCCESS;

} /* end of wlanoidSetSsid() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to query the currently associated SSID.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[in] pvQueryBuffer Pointer to the buffer that holds the result of
*                           the query.
* \param[in] u4QueryBufferLen The length of the query buffer.
* \param[out] pu4QueryInfoLen If the call is successful, returns the number of
*                             bytes written into the query buffer. If the call
*                             failed due to invalid length of the query buffer,
*                             returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_LENGTH
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidQuerySsid (
    IN  P_ADAPTER_T       prAdapter,
    OUT PVOID             pvQueryBuffer,
    IN  UINT_32           u4QueryBufferLen,
    OUT PUINT_32          pu4QueryInfoLen
    )
{
    P_PARAM_SSID_T prAssociatedSsid;

    DEBUGFUNC("wlanoidQuerySsid");

    ASSERT(prAdapter);
    ASSERT(pu4QueryInfoLen);

    if (u4QueryBufferLen) {
        ASSERT(pvQueryBuffer);
    }

    *pu4QueryInfoLen = sizeof(PARAM_SSID_T);

    /* Check for query buffer length */
    if (u4QueryBufferLen < *pu4QueryInfoLen) {
        DBGLOG(REQ, WARN, ("Invalid length %lu\n", u4QueryBufferLen));
        return WLAN_STATUS_INVALID_LENGTH;
    }

    ASSERT(pvQueryBuffer);
    prAssociatedSsid = (P_PARAM_SSID_T)pvQueryBuffer;

    kalMemZero(prAssociatedSsid->aucSsid, sizeof(prAssociatedSsid->aucSsid));

    if (prAdapter->eConnectionStateIndicated == MEDIA_STATE_CONNECTED) {
        prAssociatedSsid->u4SsidLen = (UINT_32)prAdapter->rConnSettings.ucSSIDLen;

        if (prAdapter->rConnSettings.ucSSIDLen) {
            kalMemCopy(prAssociatedSsid->aucSsid,
                prAdapter->rConnSettings.aucSSID,
                prAdapter->rConnSettings.ucSSIDLen);
        }

        DBGLOG(REQ,
            TRACE,
            ("Currently associated SSID: \"%s\"\n",
            prAdapter->rConnSettings.aucSSID));
    }
    else {
        prAssociatedSsid->u4SsidLen = 0;

        DBGLOG(REQ, TRACE, ("Null SSID\n"));
    }

    return WLAN_STATUS_SUCCESS;
} /* wlanoidQuerySsid */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to query the current 802.11 network type.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[in] pvQueryBuffer Pointer to the buffer that holds the result of
*                           the query.
* \param[in] u4QueryBufferLen The length of the query buffer.
* \param[out] pu4QueryInfoLen If the call is successful, returns the number of
*                             bytes written into the query buffer. If the call
*                             failed due to invalid length of the query buffer,
*                             returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_BUFFER_TOO_SHORT
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidQueryInfrastructureMode (
    IN  P_ADAPTER_T       prAdapter,
    OUT PVOID             pvQueryBuffer,
    IN  UINT_32           u4QueryBufferLen,
    OUT PUINT_32          pu4QueryInfoLen
    )
{
    DEBUGFUNC("wlanoidQueryInfrastructureMode");

    ASSERT(prAdapter);
    ASSERT(pu4QueryInfoLen);

    *pu4QueryInfoLen = sizeof(ENUM_PARAM_OP_MODE_T);

    if (u4QueryBufferLen < sizeof(ENUM_PARAM_OP_MODE_T)) {
        return WLAN_STATUS_BUFFER_TOO_SHORT;
    }

    ASSERT(pvQueryBuffer);

    *(P_ENUM_PARAM_OP_MODE_T)pvQueryBuffer =
        prAdapter->rConnSettings.eOPMode;

    /*
    ** According to OID_802_11_INFRASTRUCTURE_MODE
    ** If there is no prior OID_802_11_INFRASTRUCTURE_MODE,
    ** NDIS_STATUS_ADAPTER_NOT_READY shall be returned.
    */
#if DBG
    switch (*(P_ENUM_PARAM_OP_MODE_T)pvQueryBuffer) {
        case NET_TYPE_IBSS:
             DBGLOG(REQ, INFO, ("IBSS mode\n"));
             break;
        case NET_TYPE_INFRA:
             DBGLOG(REQ, INFO, ("Infrastructure mode\n"));
             break;
        default:
             DBGLOG(REQ, INFO, ("Automatic mode\n"));
    }
#endif

    return WLAN_STATUS_SUCCESS;
}   /* wlanoidQueryInfrastructureMode */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to set mode to infrastructure or
*        IBSS, or automatic switch between the two.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[in] pvSetBuffer Pointer to the buffer that holds the data to be set.
* \param[in] u4SetBufferLen The length of the set buffer.
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*             bytes read from the set buffer. If the call failed due to invalid
*             length of the set buffer, returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_DATA
* \retval WLAN_STATUS_ADAPTER_NOT_READY
* \retval WLAN_STATUS_INVALID_LENGTH
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidSetInfrastructureMode (
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID             pvSetBuffer,
    IN  UINT_32           u4SetBufferLen,
    OUT PUINT_32          pu4SetInfoLen
    )
{
    ENUM_PARAM_OP_MODE_T eOpMode;

    DEBUGFUNC("wlanoidSetInfrastructureMode");

    ASSERT(prAdapter);
    ASSERT(pvSetBuffer);
    ASSERT(pu4SetInfoLen);

    *pu4SetInfoLen = sizeof(ENUM_PARAM_OP_MODE_T);

    if (u4SetBufferLen < sizeof(ENUM_PARAM_OP_MODE_T)) {
        DBGLOG(REQ, WARN, ("Invalid length %lu\n", u4SetBufferLen));
        return WLAN_STATUS_INVALID_LENGTH;
    }

    if (IS_ARB_IN_RFTEST_STATE(prAdapter)) {
        return WLAN_STATUS_SUCCESS;
    }

    if (prAdapter->rAcpiState == ACPI_STATE_D3) {
        DBGLOG(REQ, WARN, ("Fail in set infrastructure mode! (Adapter not ready). ACPI=D%d, Radio=%d\n",
                    prAdapter->rAcpiState, prAdapter->fgIsRadioOff));
        return WLAN_STATUS_ADAPTER_NOT_READY;
    }

    eOpMode = *(P_ENUM_PARAM_OP_MODE_T)pvSetBuffer;
    /* Verify the new infrastructure mode. */
    if (eOpMode >= NET_TYPE_NUM) {
        DBGLOG(REQ, TRACE, ("Invalid mode value 0x%x (0x%p)\n", eOpMode, pvSetBuffer));
        return WLAN_STATUS_INVALID_DATA;
    }

#if DBG
    switch (eOpMode) {
        case NET_TYPE_IBSS:
             DBGLOG(REQ, INFO, ("New mode: IBSS mode\n"));
             break;

        case NET_TYPE_INFRA:
             DBGLOG(REQ, INFO, ("New mode: Infrastructure mode\n"));
             break;

        default:
             DBGLOG(REQ, INFO, ("New mode: Automatic mode\n"));
    }
#endif

    /* Save the new infrastructure mode setting. */
    prAdapter->rConnSettings.eOPMode = eOpMode;

    /* Clean S/W and H/W key table */
    privacyInitialize(prAdapter);

    return WLAN_STATUS_SUCCESS;
}   /* wlanoidSetInfrastructureMode */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to query the current 802.11 authentication
*        mode.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[out] pvQueryBuffer A pointer to the buffer that holds the result of
*                           the query.
* \param[in] u4QueryBufferLen The length of the query buffer.
* \param[out] pu4QueryInfoLen If the call is successful, returns the number of
*                            bytes written into the query buffer. If the call
*                            failed due to invalid length of the query buffer,
*                            returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_BUFFER_TOO_SHORT
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidQueryAuthMode (
    IN  P_ADAPTER_T       prAdapter,
    OUT PVOID             pvQueryBuffer,
    IN  UINT_32           u4QueryBufferLen,
    OUT PUINT_32          pu4QueryInfoLen
    )
{
    DEBUGFUNC("wlanoidQueryAuthMode");

    ASSERT(prAdapter);

    ASSERT(pvQueryBuffer);
    ASSERT(pu4QueryInfoLen);

    *pu4QueryInfoLen = sizeof(ENUM_PARAM_AUTH_MODE_T);

    if (u4QueryBufferLen < sizeof(ENUM_PARAM_AUTH_MODE_T)) {
        return WLAN_STATUS_BUFFER_TOO_SHORT;
    }

    *(P_ENUM_PARAM_AUTH_MODE_T)pvQueryBuffer = prAdapter->rConnSettings.eAuthMode;

#if DBG
    switch (*(P_ENUM_PARAM_AUTH_MODE_T)pvQueryBuffer) {
    case AUTH_MODE_OPEN:
        DBGLOG(REQ, INFO, ("Current auth mode: Open\n"));
        break;

    case AUTH_MODE_SHARED:
        DBGLOG(REQ, INFO, ("Current auth mode: Shared\n"));
        break;

    case AUTH_MODE_AUTO_SWITCH:
        DBGLOG(REQ, INFO, ("Current auth mode: Auto-switch\n"));
        break;

    case AUTH_MODE_WPA:
        DBGLOG(REQ, INFO, ("Current auth mode: WPA\n"));
        break;

    case AUTH_MODE_WPA_PSK:
        DBGLOG(REQ, INFO, ("Current auth mode: WPA PSK\n"));
        break;

    case AUTH_MODE_WPA_NONE:
        DBGLOG(REQ, INFO, ("Current auth mode: WPA None\n"));
        break;

    case AUTH_MODE_WPA2:
        DBGLOG(REQ, INFO, ("Current auth mode: WPA2\n"));
        break;

    case AUTH_MODE_WPA2_PSK:
        DBGLOG(REQ, INFO, ("Current auth mode: WPA2 PSK\n"));
        break;

    default:
        DBGLOG(REQ,
            INFO,
            ("Current auth mode: %d\n",
            *(P_ENUM_PARAM_AUTH_MODE_T)pvQueryBuffer));
    }
#endif
    return WLAN_STATUS_SUCCESS;
} /* wlanoidQueryAuthMode */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to set the IEEE 802.11 authentication mode
*        to the driver.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[in] pvSetBuffer A pointer to the buffer that holds the data to be set.
* \param[in] u4SetBufferLen The length of the set buffer.
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*                          bytes read from the set buffer. If the call failed
*                          due to invalid length of the set buffer, returns
*                          the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_DATA
* \retval WLAN_STATUS_INVALID_LENGTH
* \retval WLAN_STATUS_ADAPTER_NOT_READY
* \retval WLAN_STATUS_NOT_ACCEPTED
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidSetAuthMode (
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID             pvSetBuffer,
    IN  UINT_32           u4SetBufferLen,
    OUT PUINT_32          pu4SetInfoLen
    )
{
    UINT_32               u4AkmSuite, i;
    P_DOT11_RSNA_CONFIG_AUTHENTICATION_SUITES_ENTRY prEntry;

    DEBUGFUNC("wlanoidSetAuthMode");

    ASSERT(prAdapter);
    ASSERT(pu4SetInfoLen);
    ASSERT(pvSetBuffer);

    *pu4SetInfoLen = sizeof(ENUM_PARAM_AUTH_MODE_T);

    if (u4SetBufferLen < sizeof(ENUM_PARAM_AUTH_MODE_T)) {
        return WLAN_STATUS_INVALID_LENGTH;
    }

    if (IS_ARB_IN_RFTEST_STATE(prAdapter)) {
        return WLAN_STATUS_SUCCESS;
    }

    if (prAdapter->rAcpiState == ACPI_STATE_D3) {
        DBGLOG(REQ, WARN, ("Fail in set Authentication mode! (Adapter not ready). ACPI=D%d, Radio=%d\n",
                    prAdapter->rAcpiState, prAdapter->fgIsRadioOff));
        return WLAN_STATUS_ADAPTER_NOT_READY;
    }

    /* Check if the new authentication mode is valid. */
    if (*(P_ENUM_PARAM_AUTH_MODE_T)pvSetBuffer >= AUTH_MODE_NUM) {
        DBGLOG(REQ,
            TRACE,
            ("Invalid auth mode %d\n",
            *(P_ENUM_PARAM_AUTH_MODE_T)pvSetBuffer));
        return WLAN_STATUS_INVALID_DATA;
    }

    switch (*(P_ENUM_PARAM_AUTH_MODE_T)pvSetBuffer) {
    case AUTH_MODE_WPA:
    case AUTH_MODE_WPA_PSK:
    case AUTH_MODE_WPA2:
    case AUTH_MODE_WPA2_PSK:
        /* infrastructure mode only */
        if (prAdapter->rConnSettings.eOPMode != NET_TYPE_INFRA) {
            return WLAN_STATUS_NOT_ACCEPTED;
        }
        break;

    case AUTH_MODE_WPA_NONE:
    /* ad hoc mode only */
        if (prAdapter->rConnSettings.eOPMode != NET_TYPE_IBSS) {
            return WLAN_STATUS_NOT_ACCEPTED;
        }
        break;

    default:
        ;
    }

    /* Save the new authentication mode. */
    prAdapter->rConnSettings.eAuthMode = *(P_ENUM_PARAM_AUTH_MODE_T)pvSetBuffer;

    if (prAdapter->rConnSettings.eAuthMode >= AUTH_MODE_WPA) {
        switch(prAdapter->rConnSettings.eAuthMode) {
        case AUTH_MODE_WPA:
            u4AkmSuite = WPA_AKM_SUITE_802_1X;
            break;

        case AUTH_MODE_WPA_PSK:
            u4AkmSuite = WPA_AKM_SUITE_PSK;
            break;

        case AUTH_MODE_WPA_NONE:
            u4AkmSuite = WPA_AKM_SUITE_NONE;
            break;

        case AUTH_MODE_WPA2:
            u4AkmSuite = RSN_AKM_SUITE_802_1X;
            break;

        case AUTH_MODE_WPA2_PSK:
            u4AkmSuite = RSN_AKM_SUITE_PSK;
            break;

        default:
            u4AkmSuite = 0;
        }
    }
    else {
        u4AkmSuite = 0;
    }

    /* Enable the specific AKM suite only. */
    for (i = 0; i < MAX_NUM_SUPPORTED_AKM_SUITES; i++) {
        prEntry = &prAdapter->rConnSettings.rMib.dot11RSNAConfigAuthenticationSuitesTable[i];

        if (prEntry->dot11RSNAConfigAuthenticationSuite == u4AkmSuite) {
            prEntry->dot11RSNAConfigAuthenticationSuiteEnabled = TRUE;
        }
        else {
            prEntry->dot11RSNAConfigAuthenticationSuiteEnabled = FALSE;
        }
    }

#if DBG
    switch (prAdapter->rConnSettings.eAuthMode) {
    case AUTH_MODE_OPEN:
        DBGLOG(REQ, INFO, ("New auth mode: open\n"));
        break;

    case AUTH_MODE_SHARED:
        DBGLOG(REQ, INFO, ("New auth mode: shared\n"));
        break;

    case AUTH_MODE_AUTO_SWITCH:
        DBGLOG(REQ, INFO, ("New auth mode: auto-switch\n"));
        break;

    case AUTH_MODE_WPA:
        DBGLOG(REQ, INFO, ("New auth mode: WPA\n"));
        break;

    case AUTH_MODE_WPA_PSK:
        DBGLOG(REQ, INFO, ("New auth mode: WPA PSK\n"));
        break;

    case AUTH_MODE_WPA_NONE:
        DBGLOG(REQ, INFO, ("New auth mode: WPA None\n"));
        break;

    case AUTH_MODE_WPA2:
        DBGLOG(REQ, INFO, ("New auth mode: WPA2\n"));
        break;

    case AUTH_MODE_WPA2_PSK:
        DBGLOG(REQ, INFO, ("New auth mode: WPA2 PSK\n"));
        break;

    default:
        DBGLOG(REQ,
            INFO,
            ("New auth mode: unknown (%d)\n",
            prAdapter->rConnSettings.eAuthMode));
    }
#endif
    return WLAN_STATUS_SUCCESS;
} /* wlanoidSetAuthMode */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to reload the available default settings for
*        the specified type field.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[in] pvSetBuffer A pointer to the buffer that holds the data to be set.
* \param[in] u4SetBufferLen The length of the set buffer.
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*                          bytes read from the set buffer. If the call failed
*                          due to invalid length of the set buffer, returns
*                          the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_ADAPTER_NOT_READY
* \retval WLAN_STATUS_INVALID_DATA
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidSetReloadDefaults (
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID             pvSetBuffer,
    IN  UINT_32           u4SetBufferLen,
    OUT PUINT_32          pu4SetInfoLen
    )
{
    WLAN_STATUS           rStatus = WLAN_STATUS_SUCCESS;
    ENUM_PARAM_NETWORK_TYPE_T    eNetworkType;
    UINT_32               u4Len;

    DEBUGFUNC("wlanoidSetReloadDefaults");

    ASSERT(prAdapter);

    ASSERT(pu4SetInfoLen);
    *pu4SetInfoLen = sizeof(PARAM_RELOAD_DEFAULTS);

    if (IS_ARB_IN_RFTEST_STATE(prAdapter)) {
        return WLAN_STATUS_SUCCESS;
    }

    if (prAdapter->rAcpiState == ACPI_STATE_D3) {
        DBGLOG(REQ, WARN, ("Fail in set Reload default! (Adapter not ready). ACPI=D%d, Radio=%d\n",
                    prAdapter->rAcpiState, prAdapter->fgIsRadioOff));
        return WLAN_STATUS_ADAPTER_NOT_READY;
    }

    ASSERT(pvSetBuffer);
    /* Verify the available reload options and reload the settings. */
    switch (*(P_PARAM_RELOAD_DEFAULTS)pvSetBuffer) {
    case ENUM_RELOAD_WEP_KEYS:
        /* Reload available default WEP keys from the permanent
            storage. */
        privacyReloadDefaultWepKeys(prAdapter);
        break;

    default:
        DBGLOG(REQ,
            TRACE,
            ("Invalid reload option %d\n",
            *(P_PARAM_RELOAD_DEFAULTS)pvSetBuffer));
        rStatus = WLAN_STATUS_INVALID_DATA;
    }

    /* OID_802_11_RELOAD_DEFAULTS requiest to reset to auto mode */
    eNetworkType = NETWORK_TYPE_AUTOMODE;
    wlanoidSetNetworkTypeInUse(prAdapter, &eNetworkType, sizeof(eNetworkType), &u4Len);

    return rStatus;
} /* wlanoidSetReloadDefaults */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to set a WEP key to the driver.
*
* \param[in]  prAdapter Pointer to the Adapter structure.
* \param[in]  pvSetBuffer A pointer to the buffer that holds the data to be set.
* \param[in]  u4SetBufferLen The length of the set buffer.
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*                          bytes read from the set buffer. If the call failed
*                          due to invalid length of the set buffer, returns
*                          the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_LENGTH
* \retval WLAN_STATUS_INVALID_DATA
* \retval WLAN_STATUS_ADAPTER_NOT_READY
* \retval WLAN_STATUS_BUFFER_TOO_SHORT
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidSetAddWep (
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID    pvSetBuffer,
    IN  UINT_32  u4SetBufferLen,
    OUT PUINT_32 pu4SetInfoLen
    )
{
    P_PARAM_WEP_T prNewWepKey;
    UINT_32       u4KeyId, u4SetLen;
    UINT_8        keyBuffer[sizeof(PARAM_KEY_T) + LEGACY_KEY_MAX_LEN];
    P_PARAM_KEY_T prParamKey = (P_PARAM_KEY_T)keyBuffer;
    UINT_8        aucBCAddr[] = BC_MAC_ADDR;

    DEBUGFUNC("wlanoidSetAddWep");

    ASSERT(prAdapter);

    *pu4SetInfoLen = OFFSET_OF(PARAM_WEP_T, aucKeyMaterial);

    if (u4SetBufferLen < OFFSET_OF(PARAM_WEP_T, aucKeyMaterial)) {
        ASSERT(pu4SetInfoLen);
        return WLAN_STATUS_BUFFER_TOO_SHORT;
    }

    ASSERT(pvSetBuffer);
    ASSERT(pu4SetInfoLen);

    if (IS_ARB_IN_RFTEST_STATE(prAdapter)) {
        return WLAN_STATUS_SUCCESS;
    }

    if (prAdapter->rAcpiState == ACPI_STATE_D3) {
        DBGLOG(REQ, WARN, ("Fail in set add WEP! (Adapter not ready). ACPI=D%d, Radio=%d\n",
                    prAdapter->rAcpiState, prAdapter->fgIsRadioOff));
        return WLAN_STATUS_ADAPTER_NOT_READY;
    }

    prNewWepKey = (P_PARAM_WEP_T)pvSetBuffer;

    /* Verify the total buffer for minimum length. */
    if (u4SetBufferLen < OFFSET_OF(PARAM_WEP_T, aucKeyMaterial) + prNewWepKey->u4KeyLength) {
        DBGLOG(RSN, WARN, ("Invalid total buffer length (%d) than minimum length (%d)\n",
                          (UINT_8)u4SetBufferLen,
                          (UINT_8)OFFSET_OF(PARAM_WEP_T, aucKeyMaterial)));

        *pu4SetInfoLen = OFFSET_OF(PARAM_WEP_T, aucKeyMaterial);
        return WLAN_STATUS_INVALID_DATA;
    }

    /* Verify the key structure length. */
    if (prNewWepKey->u4Length > u4SetBufferLen) {
        DBGLOG(RSN, WARN, ("Invalid key structure length (%d) greater than total buffer length (%d)\n",
                          (UINT_8)prNewWepKey->u4Length,
                          (UINT_8)u4SetBufferLen));

        *pu4SetInfoLen = u4SetBufferLen;
        return WLAN_STATUS_INVALID_DATA;
    }

    /* Verify the key material length for maximum key material length:16 */
    if (prNewWepKey->u4KeyLength > LEGACY_KEY_MAX_LEN) {
        DBGLOG(RSN, WARN, ("Invalid key material length (%d) greater than maximum key material length (16)\n",
            (UINT_8)prNewWepKey->u4KeyLength));

        *pu4SetInfoLen = u4SetBufferLen;
        return WLAN_STATUS_INVALID_DATA;
    }

    *pu4SetInfoLen = u4SetBufferLen;

    u4KeyId = prNewWepKey->u4KeyIndex & WEP_KEY_ID_FIELD;

    /* Verify whether key index is valid or not, current version
       driver support only 4 global WEP keys setting by this OID */
    if (u4KeyId > MAX_KEY_NUM - 1) {
        DBGLOG(RSN, ERROR, ("Error, invalid WEP key ID: %d\n", (UINT_8)u4KeyId));
        return WLAN_STATUS_INVALID_DATA;
    }

    prParamKey->u4KeyIndex = u4KeyId;

    /* Transmit key */
    if (prNewWepKey->u4KeyIndex & IS_TRANSMIT_KEY) {
        prParamKey->u4KeyIndex |= IS_TRANSMIT_KEY;
    }

    /* Per client key */
    if (prNewWepKey->u4KeyIndex & IS_UNICAST_KEY) {
        prParamKey->u4KeyIndex |= IS_UNICAST_KEY;
    }

    prParamKey->u4KeyLength = prNewWepKey->u4KeyLength;

    kalMemCopy(prParamKey->arBSSID, aucBCAddr, MAC_ADDR_LEN);

    kalMemCopy(prParamKey->aucKeyMaterial,
        prNewWepKey->aucKeyMaterial,
        prNewWepKey->u4KeyLength);

    prParamKey->u4Length = OFFSET_OF(PARAM_KEY_T, aucKeyMaterial) + prNewWepKey->u4KeyLength;

    wlanoidSetAddKey(prAdapter,
        (PVOID)prParamKey,
        prParamKey->u4Length,
        &u4SetLen);

    return WLAN_STATUS_SUCCESS;
} /* wlanoidSetAddWep */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to request the driver to remove the WEP key
*          at the specified key index.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[in] pvSetBuffer A pointer to the buffer that holds the data to be set.
* \param[in] u4SetBufferLen The length of the set buffer.
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*                          bytes read from the set buffer. If the call failed
*                          due to invalid length of the set buffer, returns
*                          the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_DATA
* \retval WLAN_STATUS_INVALID_LENGTH
* \retval WLAN_STATUS_ADAPTER_NOT_READY
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidSetRemoveWep (
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID             pvSetBuffer,
    IN  UINT_32           u4SetBufferLen,
    OUT PUINT_32          pu4SetInfoLen
    )
{
    UINT_32               u4KeyId, u4SetLen;
    PARAM_REMOVE_KEY_T    rRemoveKey;
    UINT_8                aucBCAddr[] = BC_MAC_ADDR;

    DEBUGFUNC("wlanoidSetRemoveWep");

    ASSERT(prAdapter);
    ASSERT(pu4SetInfoLen);

    *pu4SetInfoLen = sizeof(PARAM_KEY_INDEX);

    if (u4SetBufferLen < sizeof(PARAM_KEY_INDEX)) {
        return WLAN_STATUS_INVALID_LENGTH;
    }

    ASSERT(pvSetBuffer);
    u4KeyId = *(PUINT_32)pvSetBuffer;

    /* Dump PARAM_WEP content. */
    DBGLOG(REQ, INFO, ("Set: Dump PARAM_KEY_INDEX content\n"));
    DBGLOG(REQ, INFO, ("Index : 0x%08lx\n", u4KeyId));

    if (IS_ARB_IN_RFTEST_STATE(prAdapter)) {
        return WLAN_STATUS_SUCCESS;
    }

    if (prAdapter->rAcpiState == ACPI_STATE_D3) {
        DBGLOG(REQ, WARN, ("Fail in set remove WEP! (Adapter not ready). ACPI=D%d, Radio=%d\n",
                    prAdapter->rAcpiState, prAdapter->fgIsRadioOff));
        return WLAN_STATUS_ADAPTER_NOT_READY;
    }

    if (u4KeyId & IS_TRANSMIT_KEY) {
        /* Bit 31 should not be set */
        DBGLOG(RSN, ERROR, ("Invalid WEP key index: 0x%08lx\n", u4KeyId));
        return WLAN_STATUS_INVALID_DATA;
    }

    u4KeyId &= BITS(0,7);

    /* Verify whether key index is valid or not. Current version
        driver support only 4 global WEP keys. */
    if (u4KeyId > MAX_KEY_NUM - 1) {
        DBGLOG(RSN, ERROR, ("invalid WEP key ID %lu\n", u4KeyId));
        return WLAN_STATUS_INVALID_DATA;
    }

    rRemoveKey.u4Length = sizeof(PARAM_REMOVE_KEY_T);
    rRemoveKey.u4KeyIndex = *(PUINT_32)pvSetBuffer;

    kalMemCopy(rRemoveKey.arBSSID, aucBCAddr, MAC_ADDR_LEN);

    wlanoidSetRemoveKey(prAdapter,
        (PVOID)&rRemoveKey,
        sizeof(PARAM_REMOVE_KEY_T),
        &u4SetLen);

    return WLAN_STATUS_SUCCESS;
} /* wlanoidSetRemoveWep */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to set a key to the driver.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[in] pvSetBuffer A pointer to the buffer that holds the data to be set.
* \param[in] u4SetBufferLen The length of the set buffer.
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*                          bytes read from the set buffer. If the call failed
*                          due to invalid length of the set buffer, returns
*                          the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_ADAPTER_NOT_READY
* \retval WLAN_STATUS_INVALID_LENGTH
* \retval WLAN_STATUS_INVALID_DATA
*
* \note The setting buffer PARAM_KEY_T, which is set by NDIS, is unpacked.
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidSetAddKey (
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID    pvSetBuffer,
    IN  UINT_32  u4SetBufferLen,
    OUT PUINT_32 pu4SetInfoLen
    )
{
    P_PARAM_KEY_T prNewKey;

    DEBUGFUNC("wlanoidSetAddKey");
    DBGLOG(RSN, INFO, ("\n"));

    ASSERT(prAdapter);
    ASSERT(pvSetBuffer);
    ASSERT(pu4SetInfoLen);

    if (IS_ARB_IN_RFTEST_STATE(prAdapter)) {
        return WLAN_STATUS_SUCCESS;
    }

    if (prAdapter->rAcpiState == ACPI_STATE_D3) {
        DBGLOG(REQ, WARN, ("Fail in set add key! (Adapter not ready). ACPI=D%d, Radio=%d\n",
                    prAdapter->rAcpiState, prAdapter->fgIsRadioOff));
        return WLAN_STATUS_ADAPTER_NOT_READY;
    }

    prNewKey = (P_PARAM_KEY_T) pvSetBuffer;

    /* Verify the key structure length. */
    if (prNewKey->u4Length > u4SetBufferLen) {
        DBGLOG(RSN, WARN, ("Invalid key structure length (%d) greater than total buffer length (%d)\n",
                          (UINT_8)prNewKey->u4Length,
                          (UINT_8)u4SetBufferLen));

        *pu4SetInfoLen = u4SetBufferLen;
        return WLAN_STATUS_INVALID_LENGTH;
    }

    /* Verify the key material length for key material buffer */
    if (prNewKey->u4KeyLength > prNewKey->u4Length - OFFSET_OF(PARAM_KEY_T, aucKeyMaterial)) {
        DBGLOG(RSN, WARN, ("Invalid key material length (%d)\n", (UINT_8)prNewKey->u4KeyLength));
        *pu4SetInfoLen = u4SetBufferLen;
        return WLAN_STATUS_INVALID_DATA;
    }

    /* Exception check */
    if (prNewKey->u4KeyIndex & 0x0fffff00) {
        return WLAN_STATUS_INVALID_DATA;
    }

    if (!(prNewKey->u4KeyLength == WEP_40_LEN  || prNewKey->u4KeyLength == WEP_104_LEN ||
          prNewKey->u4KeyLength == CCMP_KEY_LEN|| prNewKey->u4KeyLength == TKIP_KEY_LEN))
    {
        return WLAN_STATUS_INVALID_DATA;
    }

    *pu4SetInfoLen = u4SetBufferLen;

    /* Dump PARAM_KEY content. */
    DBGLOG(REQ, INFO, ("Set: Dump PARAM_KEY content\n"));
    DBGLOG(REQ, INFO, ("Length    : 0x%08lx\n", prNewKey->u4Length));
    DBGLOG(REQ, INFO, ("Key Index : 0x%08lx\n", prNewKey->u4KeyIndex));
    DBGLOG(REQ, INFO, ("Key Length: 0x%08lx\n", prNewKey->u4KeyLength));
    DBGLOG(REQ, INFO, ("BSSID:\n"));
    DBGLOG_MEM8(REQ, INFO, prNewKey->arBSSID, sizeof(PARAM_MAC_ADDRESS));
    DBGLOG(REQ, INFO, ("Key RSC:\n"));
    DBGLOG_MEM8(REQ, INFO, &prNewKey->rKeyRSC, sizeof(PARAM_KEY_RSC));
    DBGLOG(REQ, INFO, ("Key Material:\n"));
    DBGLOG_MEM8(REQ, INFO, prNewKey->aucKeyMaterial, prNewKey->u4KeyLength);

    if (arbFsmRunEventSecKeyInstalled(prAdapter, prNewKey) != WLAN_STATUS_SUCCESS)
        return WLAN_STATUS_INVALID_DATA;

    return WLAN_STATUS_SUCCESS;
} /* wlanoidSetAddKey */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to request the driver to remove the key at
*        the specified key index.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[in] pvSetBuffer A pointer to the buffer that holds the data to be set.
* \param[in] u4SetBufferLen The length of the set buffer.
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*                          bytes read from the set buffer. If the call failed
*                          due to invalid length of the set buffer, returns
*                          the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_DATA
* \retval WLAN_STATUS_INVALID_LENGTH
* \retval WLAN_STATUS_ADAPTER_NOT_READY
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidSetRemoveKey (
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID             pvSetBuffer,
    IN  UINT_32           u4SetBufferLen,
    OUT PUINT_32          pu4SetInfoLen
    )
{
    P_PARAM_REMOVE_KEY_T  prRemovedKey;
    UINT_32               u4KeyId;
    PUINT_8               pucBssid;
    SW_KEY_STRUC_T        rSwKey;

    DEBUGFUNC("wlanoidSetRemoveKey");

    ASSERT(prAdapter);
    ASSERT(pu4SetInfoLen);

    *pu4SetInfoLen = sizeof(PARAM_REMOVE_KEY_T);

    if (u4SetBufferLen < sizeof(PARAM_REMOVE_KEY_T)) {
        return WLAN_STATUS_INVALID_LENGTH;
    }

    if (IS_ARB_IN_RFTEST_STATE(prAdapter)) {
        return WLAN_STATUS_SUCCESS;
    }

    if (prAdapter->rAcpiState == ACPI_STATE_D3) {
        DBGLOG(REQ, WARN, ("Fail in set remove key! (Adapter not ready). ACPI=D%d, Radio=%d\n",
                    prAdapter->rAcpiState, prAdapter->fgIsRadioOff));
        return WLAN_STATUS_ADAPTER_NOT_READY;
    }

    ASSERT(pvSetBuffer);
    prRemovedKey = (P_PARAM_REMOVE_KEY_T)pvSetBuffer;

    /* Dump PARAM_REMOVE_KEY content. */
    DBGLOG(REQ, INFO, ("Set: Dump PARAM_REMOVE_KEY content\n"));
    DBGLOG(REQ, INFO, ("Length    : 0x%08lx\n", prRemovedKey->u4Length));
    DBGLOG(REQ, INFO, ("Key Index : 0x%08lx\n", prRemovedKey->u4KeyIndex));
    DBGLOG(REQ, INFO, ("BSSID:\n"));
    DBGLOG_MEM8(REQ, INFO, prRemovedKey->arBSSID, MAC_ADDR_LEN);

    /* Check bit 31: this bit should always 0 */
    if (prRemovedKey->u4KeyIndex & IS_TRANSMIT_KEY) {
        /* Bit 31 should not be set */
        DBGLOG(RSN, ERROR, ("invalid key index: 0x%08lx\n",
            prRemovedKey->u4KeyIndex));
        return WLAN_STATUS_INVALID_DATA;
    }

    /* Check bits 8 ~ 29 should always be 0 */
    if (prRemovedKey->u4KeyIndex & BITS(8, 29)) {
        /* Bit 31 should not be set */
        DBGLOG(RSN, ERROR, ("invalid key index: 0x%08lx\n",
            prRemovedKey->u4KeyIndex));
        return WLAN_STATUS_INVALID_DATA;
    }

    kalMemZero(&rSwKey, sizeof(SW_KEY_STRUC_T));
    u4KeyId = prRemovedKey->u4KeyIndex & 0x000000ff;
    pucBssid = (PUINT_8)prRemovedKey->arBSSID;

    ASSERT(u4KeyId < MAX_KEY_NUM);

    /* Pairwise key */
    switch (prRemovedKey->u4KeyIndex & IS_UNICAST_KEY) {
    case IS_UNICAST_KEY:
        privacyClearKeyEntry(prAdapter, TRUE, pucBssid, (UINT_8)u4KeyId);
        break;

    case 0: /* Group key */
        privacyClearKeyEntry(prAdapter, FALSE, pucBssid, (UINT_8)u4KeyId);
        break;
    } /* switch() */

    return WLAN_STATUS_SUCCESS;
} /* wlanoidSetRemoveKey */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to query the current encryption status.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[out] pvQueryBuffer A pointer to the buffer that holds the result of
*                           the query.
* \param[in] u4QueryBufferLen The length of the query buffer.
* \param[out] pu4QueryInfoLen If the call is successful, returns the number of
*                            bytes written into the query buffer. If the call
*                            failed due to invalid length of the query buffer,
*                            returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidQueryEncryptionStatus (
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID             pvQueryBuffer,
    IN  UINT_32           u4QueryBufferLen,
    OUT PUINT_32          pu4QueryInfoLen
    )
{
    BOOLEAN                 fgTransmitKeyAvailable = FALSE;
    ENUM_ENCRYPTION_STATUS_T  eEncStatus = 0;

    DEBUGFUNC("wlanoidQueryEncryptionStatus");

    ASSERT(prAdapter);
    ASSERT(pu4QueryInfoLen);

    *pu4QueryInfoLen = sizeof(ENUM_ENCRYPTION_STATUS_T);

    fgTransmitKeyAvailable = privacyTransmitKeyExist(prAdapter);

    switch (prAdapter->rConnSettings.eEncStatus) {
    case ENUM_ENCRYPTION3_ENABLED:
        if (fgTransmitKeyAvailable) {
            eEncStatus = ENUM_ENCRYPTION3_ENABLED;
        }
        else {
            eEncStatus = ENUM_ENCRYPTION3_KEY_ABSENT;
        }
        break;

    case ENUM_ENCRYPTION2_ENABLED:
        if (fgTransmitKeyAvailable) {
            eEncStatus = ENUM_ENCRYPTION2_ENABLED;
            break;
        }
        else {
            eEncStatus = ENUM_ENCRYPTION2_KEY_ABSENT;
        }
        break;

    case ENUM_ENCRYPTION1_ENABLED:
        if (fgTransmitKeyAvailable) {
            eEncStatus = ENUM_ENCRYPTION1_ENABLED;
        }
        else {
            eEncStatus = ENUM_ENCRYPTION1_KEY_ABSENT;
        }
        break;

    case ENUM_ENCRYPTION_DISABLED:
        eEncStatus = ENUM_ENCRYPTION_DISABLED;
        break;

    default:
        DBGLOG(RSN, ERROR, ("Unknown Encryption Status Setting:%d\n",
            prAdapter->rConnSettings.eEncStatus));
    }

#if DBG
    DBGLOG(REQ,
        INFO,
        ("Encryption status: %d Return:%d\n",
        prAdapter->rConnSettings.eEncStatus,
        eEncStatus));
#endif
    ASSERT(pvQueryBuffer);

    *(P_ENUM_ENCRYPTION_STATUS_T)pvQueryBuffer = eEncStatus;

    return WLAN_STATUS_SUCCESS;
} /* wlanoidQueryEncryptionStatus */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to set the encryption status to the driver.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[in] pvSetBuffer A pointer to the buffer that holds the data to be set.
* \param[in] u4SetBufferLen The length of the set buffer.
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*                          bytes read from the set buffer. If the call failed
*                          due to invalid length of the set buffer, returns
*                          the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_ADAPTER_NOT_READY
* \retval WLAN_STATUS_NOT_SUPPORTED
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidSetEncryptionStatus (
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID             pvSetBuffer,
    IN  UINT_32           u4SetBufferLen,
    OUT PUINT_32          pu4SetInfoLen
    )
{
    WLAN_STATUS           rStatus = WLAN_STATUS_SUCCESS;
    ENUM_ENCRYPTION_STATUS_T eEewEncrypt;

    DEBUGFUNC("wlanoidSetEncryptionStatus");

    /* <Todo> the oid follow the set_encryption_status then add key ?
              this make the tx/rx key material for wpa_none,
              expect the upper layer make sure this */

    ASSERT(prAdapter);
    ASSERT(pvSetBuffer);
    ASSERT(pu4SetInfoLen);

    *pu4SetInfoLen = sizeof(ENUM_ENCRYPTION_STATUS_T);

    if (IS_ARB_IN_RFTEST_STATE(prAdapter)) {
        return WLAN_STATUS_SUCCESS;
    }

    if (prAdapter->rAcpiState == ACPI_STATE_D3) {
        DBGLOG(REQ, WARN, ("Fail in set encryption status! (Adapter not ready). ACPI=D%d, Radio=%d\n",
                    prAdapter->rAcpiState, prAdapter->fgIsRadioOff));
        return WLAN_STATUS_ADAPTER_NOT_READY;
    }

    eEewEncrypt = *(P_ENUM_ENCRYPTION_STATUS_T)pvSetBuffer;
    DBGLOG(REQ, TRACE, ("ENCRYPTION_STATUS %d\n", eEewEncrypt));

    switch (eEewEncrypt) {
    case ENUM_ENCRYPTION_DISABLED: /* Disable WEP, TKIP, AES */
        DBGLOG(REQ, INFO, ("Disable Encryption\n"));
        /* 1595. Do we still need to support shared key without encryption. */
        privacySetCipherSuite(prAdapter,
            CIPHER_FLAG_WEP40  |
            CIPHER_FLAG_WEP104 |
            CIPHER_FLAG_WEP128);
       /* Odyssey will set a key even using open auth and no sec,
          clear the setting key at this mode */
        nicPrivacyInitialize(prAdapter);
        break;

    case ENUM_ENCRYPTION1_ENABLED: /* Enable WEP. Disable TKIP, AES */
        DBGLOG(REQ, INFO, ("Enable Encryption1\n"));
        privacySetCipherSuite(prAdapter,
            CIPHER_FLAG_WEP40  |
            CIPHER_FLAG_WEP104 |
            CIPHER_FLAG_WEP128);
        break;

    case ENUM_ENCRYPTION2_ENABLED: /* Enable WEP, TKIP. Disable AES */
        DBGLOG(REQ, INFO, ("Enable Encryption2\n"));
        privacySetCipherSuite(prAdapter,
            CIPHER_FLAG_WEP40  |
            CIPHER_FLAG_WEP104 |
            CIPHER_FLAG_WEP128 |
            CIPHER_FLAG_TKIP);
        break;

    case ENUM_ENCRYPTION3_ENABLED: /* Enable WEP, TKIP, AES */
        DBGLOG(REQ, INFO, ("Enable Encryption3\n"));
        privacySetCipherSuite(prAdapter,
            CIPHER_FLAG_WEP40  |
            CIPHER_FLAG_WEP104 |
            CIPHER_FLAG_WEP128 |
            CIPHER_FLAG_TKIP   |
            CIPHER_FLAG_CCMP);
        break;

    default:
        DBGLOG(RSN, WARN, ("Unacceptible encryption status: %d\n",
            *(P_ENUM_ENCRYPTION_STATUS_T)pvSetBuffer));

        privacySetCipherSuite(prAdapter, CIPHER_FLAG_NONE);

        rStatus = WLAN_STATUS_NOT_SUPPORTED;
    }

    if (rStatus == WLAN_STATUS_SUCCESS) {
        /* Save the new encryption status. */
        prAdapter->rConnSettings.eEncStatus =
            *(P_ENUM_ENCRYPTION_STATUS_T)pvSetBuffer;
    }

    return rStatus;
} /* wlanoidSetEncryptionStatus */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to test the driver.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[in] pvSetBuffer A pointer to the buffer that holds the data to be set.
* \param[in] u4SetBufferLen The length of the set buffer.
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*                          bytes read from the set buffer. If the call failed
*                          due to invalid length of the set buffer, returns
*                          the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_LENGTH
* \retval WLAN_STATUS_INVALID_DATA
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidSetTest (
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID             pvSetBuffer,
    IN  UINT_32           u4SetBufferLen,
    OUT PUINT_32          pu4SetInfoLen
    )
{
    P_PARAM_802_11_TEST_T prTest;
    PVOID                 pvTestData;
    PVOID                 pvStatusBuffer;
    UINT_32               u4StatusBufferSize;

    DEBUGFUNC("wlanoidSetTest");

    ASSERT(prAdapter);

    ASSERT(pu4SetInfoLen);
    ASSERT(pvSetBuffer);

    *pu4SetInfoLen = u4SetBufferLen;

    prTest = (P_PARAM_802_11_TEST_T)pvSetBuffer;

    DBGLOG(REQ, TRACE, ("Test - Type %ld\n", prTest->u4Type));

    switch (prTest->u4Type) {
    case 1:     /* Type 1: generate an authentication event */
        pvTestData = (PVOID)&prTest->u.AuthenticationEvent;
        pvStatusBuffer = (PVOID)prAdapter->aucIndicationEventBuffer;
        u4StatusBufferSize = prTest->u4Length - 8;
        break;

    case 2:     /* Type 2: generate an RSSI status indication */
        pvTestData = (PVOID)&prTest->u.RssiTrigger;
        pvStatusBuffer = (PVOID)&prAdapter->rBssInfo.rRssi;
        u4StatusBufferSize = sizeof(PARAM_RSSI);
        break;

    default:
        return WLAN_STATUS_INVALID_DATA;
    }

    ASSERT(u4StatusBufferSize <= 180);
    if (u4StatusBufferSize > 180) {
        return WLAN_STATUS_INVALID_LENGTH;
    }

    /* Get the contents of the StatusBuffer from the test structure. */
    kalMemCopy(pvStatusBuffer, pvTestData, u4StatusBufferSize);

    kalIndicateStatusAndComplete(prAdapter->prGlueInfo,
        WLAN_STATUS_MEDIA_SPECIFIC_INDICATION,
        pvStatusBuffer,
        u4StatusBufferSize);

    return WLAN_STATUS_SUCCESS;
} /* wlanoidSetTest */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to query the driver's WPA2 status.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[out] pvQueryBuffer A pointer to the buffer that holds the result of
*                           the query.
* \param[in] u4QueryBufferLen The length of the query buffer.
* \param[out] pu4QueryInfoLen If the call is successful, returns the number of
*                            bytes written into the query buffer. If the call
*                            failed due to invalid length of the query buffer,
*                            returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_LENGTH
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidQueryCapability (
    IN  P_ADAPTER_T       prAdapter,
    OUT PVOID             pvQueryBuffer,
    IN  UINT_32           u4QueryBufferLen,
    OUT PUINT_32          pu4QueryInfoLen
    )
{
    P_PARAM_CAPABILITY_T  prCap;
    P_PARAM_AUTH_ENCRYPTION_T prAuthenticationEncryptionSupported;

    DEBUGFUNC("wlanoidQueryCapability");

    ASSERT(prAdapter);
    ASSERT(pu4QueryInfoLen);
    if (u4QueryBufferLen) {
        ASSERT(pvQueryBuffer);
    }

    *pu4QueryInfoLen = 4 * sizeof(UINT_32) + 14 * sizeof(PARAM_AUTH_ENCRYPTION_T);

    if (u4QueryBufferLen < *pu4QueryInfoLen) {
        return WLAN_STATUS_INVALID_LENGTH;
    }

    ASSERT(pvQueryBuffer);

    prCap = (P_PARAM_CAPABILITY_T)pvQueryBuffer;

    prCap->u4Length = *pu4QueryInfoLen;
    prCap->u4Version = 2; /* WPA2 */
    prCap->u4NoOfPMKIDs = CFG_MAX_PMKID_CACHE;
    prCap->u4NoOfAuthEncryptPairsSupported = 14;

    prAuthenticationEncryptionSupported =
        &prCap->arAuthenticationEncryptionSupported[0];

    prAuthenticationEncryptionSupported[0].eAuthModeSupported =
        AUTH_MODE_OPEN;
    prAuthenticationEncryptionSupported[0].eEncryptStatusSupported =
        ENUM_ENCRYPTION_DISABLED;

    prAuthenticationEncryptionSupported[1].eAuthModeSupported =
        AUTH_MODE_OPEN;
    prAuthenticationEncryptionSupported[1].eEncryptStatusSupported =
        ENUM_ENCRYPTION1_ENABLED;

    prAuthenticationEncryptionSupported[2].eAuthModeSupported =
        AUTH_MODE_SHARED;
    prAuthenticationEncryptionSupported[2].eEncryptStatusSupported =
        ENUM_ENCRYPTION_DISABLED;

    prAuthenticationEncryptionSupported[3].eAuthModeSupported =
        AUTH_MODE_SHARED;
    prAuthenticationEncryptionSupported[3].eEncryptStatusSupported =
        ENUM_ENCRYPTION1_ENABLED;

    prAuthenticationEncryptionSupported[4].eAuthModeSupported =
        AUTH_MODE_WPA;
    prAuthenticationEncryptionSupported[4].eEncryptStatusSupported =
        ENUM_ENCRYPTION2_ENABLED;

    prAuthenticationEncryptionSupported[5].eAuthModeSupported =
        AUTH_MODE_WPA;
    prAuthenticationEncryptionSupported[5].eEncryptStatusSupported =
        ENUM_ENCRYPTION3_ENABLED;

    prAuthenticationEncryptionSupported[6].eAuthModeSupported =
        AUTH_MODE_WPA_PSK;
    prAuthenticationEncryptionSupported[6].eEncryptStatusSupported =
        ENUM_ENCRYPTION2_ENABLED;

    prAuthenticationEncryptionSupported[7].eAuthModeSupported =
        AUTH_MODE_WPA_PSK;
    prAuthenticationEncryptionSupported[7].eEncryptStatusSupported =
        ENUM_ENCRYPTION3_ENABLED;

    prAuthenticationEncryptionSupported[8].eAuthModeSupported =
        AUTH_MODE_WPA_NONE;
    prAuthenticationEncryptionSupported[8].eEncryptStatusSupported =
        ENUM_ENCRYPTION2_ENABLED;

    prAuthenticationEncryptionSupported[9].eAuthModeSupported =
        AUTH_MODE_WPA_NONE;
    prAuthenticationEncryptionSupported[9].eEncryptStatusSupported =
        ENUM_ENCRYPTION3_ENABLED;

    prAuthenticationEncryptionSupported[10].eAuthModeSupported =
        AUTH_MODE_WPA2;
    prAuthenticationEncryptionSupported[10].eEncryptStatusSupported =
        ENUM_ENCRYPTION2_ENABLED;

    prAuthenticationEncryptionSupported[11].eAuthModeSupported =
        AUTH_MODE_WPA2;
    prAuthenticationEncryptionSupported[11].eEncryptStatusSupported =
        ENUM_ENCRYPTION3_ENABLED;

    prAuthenticationEncryptionSupported[12].eAuthModeSupported =
        AUTH_MODE_WPA2_PSK;
    prAuthenticationEncryptionSupported[12].eEncryptStatusSupported =
        ENUM_ENCRYPTION2_ENABLED;

    prAuthenticationEncryptionSupported[13].eAuthModeSupported =
        AUTH_MODE_WPA2_PSK;
    prAuthenticationEncryptionSupported[13].eEncryptStatusSupported =
        ENUM_ENCRYPTION3_ENABLED;

    return WLAN_STATUS_SUCCESS;

} /* wlanoidQueryCapability */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to query the PMKID in the PMK cache.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[out] pvQueryBuffer A pointer to the buffer that holds the result of
*                           the query.
* \param[in] u4QueryBufferLen The length of the query buffer.
* \param[out] pu4QueryInfoLen If the call is successful, returns the number of
*                             bytes written into the query buffer. If the call
*                             failed due to invalid length of the query buffer,
*                             returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_LENGTH
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidQueryPmkid (
    IN  P_ADAPTER_T       prAdapter,
    OUT PVOID             pvQueryBuffer,
    IN  UINT_32           u4QueryBufferLen,
    OUT PUINT_32          pu4QueryInfoLen
    )
{
    UINT_32               i;
    P_PARAM_PMKID_T       prPmkid;

    DEBUGFUNC("wlanoidQueryPmkid");

    ASSERT(prAdapter);
    ASSERT(pu4QueryInfoLen);
    if (u4QueryBufferLen) {
        ASSERT(pvQueryBuffer);
    }

    *pu4QueryInfoLen = OFFSET_OF(PARAM_PMKID_T, arBSSIDInfo) +
        prAdapter->rSecInfo.u4PmkidCacheCount * sizeof(PARAM_BSSID_INFO_T);

    if (u4QueryBufferLen < *pu4QueryInfoLen) {
        return WLAN_STATUS_INVALID_LENGTH;
    }

    ASSERT(pvQueryBuffer);
    prPmkid = (P_PARAM_PMKID_T)pvQueryBuffer;

    prPmkid->u4Length = *pu4QueryInfoLen;
    prPmkid->u4BSSIDInfoCount = prAdapter->rSecInfo.u4PmkidCacheCount;

    for (i = 0; i < prAdapter->rSecInfo.u4PmkidCacheCount; i++) {
        kalMemCopy(prPmkid->arBSSIDInfo[i].arBSSID,
            prAdapter->rSecInfo.arPmkidCache[i].rBssidInfo.arBSSID,
            sizeof(PARAM_MAC_ADDRESS));
        kalMemCopy(prPmkid->arBSSIDInfo[i].arPMKID,
            prAdapter->rSecInfo.arPmkidCache[i].rBssidInfo.arPMKID,
            sizeof(PARAM_PMKID_VALUE));
    }

    return WLAN_STATUS_SUCCESS;

} /* wlanoidQueryPmkid */



/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to set the PMKID to the PMK cache in the driver.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[in] pvSetBuffer A pointer to the buffer that holds the data to be set.
* \param[in] u4SetBufferLen The length of the set buffer.
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*                           bytes read from the set buffer. If the call failed
*                           due to invalid length of the set buffer, returns
*                           the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_BUFFER_TOO_SHORT
* \retval WLAN_STATUS_INVALID_DATA
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidSetPmkid (
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID             pvSetBuffer,
    IN  UINT_32           u4SetBufferLen,
    OUT PUINT_32          pu4SetInfoLen
    )
{
    UINT_32               i, j;
    P_PARAM_PMKID_T       prPmkid;

    DEBUGFUNC("wlanoidSetPmkid");

    ASSERT(prAdapter);
    ASSERT(pu4SetInfoLen);

    *pu4SetInfoLen = u4SetBufferLen;

    /* It's possibble BSSIDInfoCount is zero, because OS wishes to clean PMKID */
    if (u4SetBufferLen < OFFSET_OF(PARAM_PMKID_T, arBSSIDInfo)) {
        return WLAN_STATUS_BUFFER_TOO_SHORT;
    }

    if (IS_ARB_IN_RFTEST_STATE(prAdapter)) {
        return WLAN_STATUS_SUCCESS;
    }

    ASSERT(pvSetBuffer);
    prPmkid = (P_PARAM_PMKID_T)pvSetBuffer;

    if (u4SetBufferLen <
            ((prPmkid->u4BSSIDInfoCount * sizeof(PARAM_BSSID_INFO_T)) +
            OFFSET_OF(PARAM_PMKID_T, arBSSIDInfo))) {
        return WLAN_STATUS_INVALID_DATA;
    }

    if (prPmkid->u4BSSIDInfoCount > CFG_MAX_PMKID_CACHE) {
        return WLAN_STATUS_INVALID_DATA;
    }

    DBGLOG(REQ, INFO, ("Count %lu\n", prPmkid->u4BSSIDInfoCount));

    /* This OID replace everything in the PMKID cache. */
    if (prPmkid->u4BSSIDInfoCount == 0) {
        prAdapter->rSecInfo.u4PmkidCacheCount = 0;
        kalMemZero(prAdapter->rSecInfo.arPmkidCache, sizeof(PMKID_ENTRY_T) * CFG_MAX_PMKID_CACHE);
    }
    if ((prAdapter->rSecInfo.u4PmkidCacheCount + prPmkid->u4BSSIDInfoCount > CFG_MAX_PMKID_CACHE)) {
        prAdapter->rSecInfo.u4PmkidCacheCount = 0;
        kalMemZero(prAdapter->rSecInfo.arPmkidCache, sizeof(PMKID_ENTRY_T) * CFG_MAX_PMKID_CACHE);
    }

    /*
    The driver can only clear its PMKID cache whenever it make a media disconnect
    indication. Otherwise, it must change the PMKID cache only when set through this OID.
    */

    for (i = 0; i < prPmkid->u4BSSIDInfoCount; i++) {
        /* Search for desired BSSID. If desired BSSID is found,
            then set the PMKID */
        if (!rsnSearchPmkidEntry(prAdapter,
                (PUINT_8)prPmkid->arBSSIDInfo[i].arBSSID,
                &j)) {
            /* No entry found for the specified BSSID, so add one entry */
            if (prAdapter->rSecInfo.u4PmkidCacheCount < CFG_MAX_PMKID_CACHE - 1) {
                j = prAdapter->rSecInfo.u4PmkidCacheCount;
                kalMemCopy(prAdapter->rSecInfo.arPmkidCache[j].rBssidInfo.arBSSID,
                    prPmkid->arBSSIDInfo[i].arBSSID,
                    sizeof(PARAM_MAC_ADDRESS));
                prAdapter->rSecInfo.u4PmkidCacheCount++;
            }
            else {
                j = CFG_MAX_PMKID_CACHE;
            }
        }

        if (j < CFG_MAX_PMKID_CACHE) {
            kalMemCopy(prAdapter->rSecInfo.arPmkidCache[j].rBssidInfo.arPMKID,
                prPmkid->arBSSIDInfo[i].arPMKID,
                sizeof(PARAM_PMKID_VALUE));
            prAdapter->rSecInfo.arPmkidCache[j].fgPmkidExist = TRUE;
        }
    }

    return WLAN_STATUS_SUCCESS;

} /* wlanoidSetPmkid */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to query the set of supported data rates that
*          the radio is capable of running
*
* \param[in] prAdapter Pointer to the Adapter structure
* \param[out] pvQueryBuffer A pointer to the buffer that holds the result of
*                           the query
* \param[in] u4QueryBufferLen The length of the query buffer
* \param[out] pu4QueryInfoLen If the call is successful, returns the number
*                             of bytes written into the query buffer. If the
*                             call failed due to invalid length of the query
*                             buffer, returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_LENGTH
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidQuerySupportedRates (
    IN  P_ADAPTER_T       prAdapter,
    OUT PVOID             pvQueryBuffer,
    IN  UINT_32           u4QueryBufferLen,
    OUT PUINT_32          pu4QueryInfoLen
    )
{
    PARAM_RATES_EX rSupportedRates = {0};  /* supported rates for this STA in a BSS */
    UINT_8 ucSupportedRatesLen;
    UINT_16 u2SupportedRateSet = 0;
    ENUM_PHY_TYPE_INDEX_T ePhyTypeIndex;

    DEBUGFUNC("wlanoidQuerySupportedRates");

    ASSERT(prAdapter);
    ASSERT(pu4QueryInfoLen);
    if (u4QueryBufferLen) {
        ASSERT(pvQueryBuffer);
    }

    for (ePhyTypeIndex = PHY_TYPE_ERP_INDEX; ePhyTypeIndex < PHY_TYPE_INDEX_NUM; ePhyTypeIndex++) {
        if (prAdapter->u2AvailablePhyTypeSet & BIT(ePhyTypeIndex)) {
            u2SupportedRateSet |= rPhyAttributes[ePhyTypeIndex].u2SupportedRateSet;
        }
    }

    /* Initialize the supported rates of the NIC by the MIB. */
    rateGetDataRatesFromRateSet(u2SupportedRateSet,
                                0x0, /*(UINT_16)NULL*/
                                rSupportedRates,
                                &ucSupportedRatesLen);

    *pu4QueryInfoLen = sizeof(PARAM_RATES_EX);

    if (u4QueryBufferLen < *pu4QueryInfoLen ) {
        DBGLOG(REQ, WARN, ("Invalid length %ld\n", u4QueryBufferLen));
        return WLAN_STATUS_INVALID_LENGTH;
    }

    ASSERT(pvQueryBuffer);

    kalMemCopy(pvQueryBuffer,
               (PVOID)&rSupportedRates[0],
               sizeof(PARAM_RATES_EX));

    DBGLOG(REQ, INFO,
        ("Current supported rates: 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\n",
         *(PUINT_8) pvQueryBuffer, *((PUINT_8) pvQueryBuffer + 1),
         *((PUINT_8) pvQueryBuffer + 2), *((PUINT_8) pvQueryBuffer + 3),
         *((PUINT_8) pvQueryBuffer + 4), *((PUINT_8) pvQueryBuffer + 5),
         *((PUINT_8) pvQueryBuffer + 6), *((PUINT_8) pvQueryBuffer + 7)));
    DBGLOG(REQ, INFO,
        ("                         0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\n",
         *((PUINT_8) pvQueryBuffer + 8), *((PUINT_8) pvQueryBuffer + 9),
         *((PUINT_8) pvQueryBuffer + 10), *((PUINT_8) pvQueryBuffer + 11),
         *((PUINT_8) pvQueryBuffer + 12), *((PUINT_8) pvQueryBuffer + 13),
         *((PUINT_8) pvQueryBuffer + 14), *((PUINT_8) pvQueryBuffer + 15)));

    return WLAN_STATUS_SUCCESS;
} /* end of wlanoidQuerySupportedRates() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to query current desired rates.
*
* \param[in] prAdapter          Pointer to the Adapter structure.
* \param[in] pvQueryBuffer      Pointer to the buffer that holds the result of
*                               the query.
* \param[in] u4QueryBufferLen   The length of the query buffer.
* \param[out] pu4QueryInfoLen   If the call is successful, returns the number of
*                               bytes written into the query buffer. If the call
*                               failed due to invalid length of the query buffer,
*                               returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_LENGTH
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidQueryDesiredRates (
    IN  P_ADAPTER_T prAdapter,
    OUT PVOID       pvQueryBuffer,
    IN  UINT_32     u4QueryBufferLen,
    OUT PUINT_32    pu4QueryInfoLen
    )
{
    P_CONNECTION_SETTINGS_T prConnSettings;
    PARAM_RATES_EX rDesiredRates = {0}; /* supported rates for this STA in a BSS */
    UINT_8 ucDesiredRatesLen;

    DEBUGFUNC("wlanoidQueryDesiredRates");

    ASSERT(prAdapter);
    ASSERT(pu4QueryInfoLen);
    if (u4QueryBufferLen) {
        ASSERT(pvQueryBuffer);
    }

    DBGLOG(REQ, INFO, ("\n"));

    prConnSettings = &prAdapter->rConnSettings;

    rateGetDataRatesFromRateSet(prConnSettings->u2DesiredRateSet,
                                0x0, /*(UINT_16)NULL*/
                                rDesiredRates,
                                &ucDesiredRatesLen);

    *pu4QueryInfoLen = (UINT_32)ucDesiredRatesLen;

    if (u4QueryBufferLen < *pu4QueryInfoLen) {
        return WLAN_STATUS_INVALID_LENGTH;
    }

    ASSERT(pvQueryBuffer);

    kalMemCopy(pvQueryBuffer,
               (PVOID)&rDesiredRates[0],
               ucDesiredRatesLen);

    return WLAN_STATUS_SUCCESS;

} /* end of wlanoidQueryDesiredRates() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to Set the desired rates.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
* \param[in] pvSetBuffer    Pointer to the buffer that holds the data to be set.
* \param[in] u4SetBufferLen The length of the set buffer.
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*                           bytes read from the set buffer. If the call failed
*                           due to invalid length of the set buffer, returns
*                           the amount of storage needed.
*
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_LENGTH
* \retval WLAN_STATUS_INVALID_DATA
* \retval WLAN_STATUS_ADAPTER_NOT_READY
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidSetDesiredRates (
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID             pvSetBuffer,
    IN  UINT_32           u4SetBufferLen,
    OUT PUINT_32          pu4SetInfoLen
    )
{
    P_CONNECTION_SETTINGS_T prConnSettings;
    P_BSS_INFO_T prBssInfo;
    PUINT_8 pucNewRate;
    UINT_16 u2UserDesiredRateSet;
    P_STA_RECORD_T prStaRec;
#if DBG
    UINT_32 i;
#endif /* DBG */

    ASSERT(prAdapter);
    ASSERT(pu4SetInfoLen);

    prConnSettings = &prAdapter->rConnSettings;
    prBssInfo = &prAdapter->rBssInfo;

    *pu4SetInfoLen = sizeof(PARAM_RATES);

    if ((u4SetBufferLen != sizeof(PARAM_RATES)) &&
        (u4SetBufferLen != sizeof(PARAM_RATES_EX))) {

        return WLAN_STATUS_INVALID_LENGTH;
    }

    if (IS_ARB_IN_RFTEST_STATE(prAdapter)) {
        return WLAN_STATUS_SUCCESS;
    }

    if (prAdapter->rAcpiState == ACPI_STATE_D3) {
        DBGLOG(REQ, WARN, ("Fail in set desired rate! (Adapter not ready). ACPI=D%d, Radio=%d\n",
                    prAdapter->rAcpiState, prAdapter->fgIsRadioOff));
        return WLAN_STATUS_ADAPTER_NOT_READY;
    }

    ASSERT(pvSetBuffer);
    pucNewRate = (PUINT_8)pvSetBuffer;

    rateGetRateSetFromDataRates(pucNewRate,
                                (UINT_8)u4SetBufferLen,
                                &u2UserDesiredRateSet);

    if (u2UserDesiredRateSet) {
        prConnSettings->u2DesiredRateSet = u2UserDesiredRateSet;
#if DBG
        DBGLOG(REQ, TRACE, ("Update User Desire Rate Set : "));
        for (i = RATE_1M_INDEX; i < RATE_NUM; i++) {
            if (BIT(i) & prConnSettings->u2DesiredRateSet) {
                DBGLOG(REQ, TRACE, ("%s, ", apucDebugRateIndex[i]));
            }
        }
        DBGLOG(REQ, TRACE, ("\n"));
#endif /* DBG */
    }
    else {
        return WLAN_STATUS_INVALID_DATA;
    }

    *pu4SetInfoLen = u4SetBufferLen;

    if (prAdapter->eConnectionState == MEDIA_STATE_CONNECTED) {

        /* Get a Station Record if possible */
        prStaRec = staRecGetStaRecordByAddr(prAdapter,
                                            prBssInfo->aucBSSID);

        if (prStaRec) {
            UINT_16 u2OperationalRateSet, u2DesiredRateSet;

            u2OperationalRateSet = (rPhyAttributes[prBssInfo->ePhyType].u2SupportedRateSet &
                                    prBssInfo->u2OperationalRateSet);

            u2DesiredRateSet = (u2OperationalRateSet & prConnSettings->u2DesiredRateSet);
            if (u2DesiredRateSet) {
                prStaRec->u2DesiredRateSet = u2DesiredRateSet;
            }
            else {
                /* For Error Handling - The Desired Rate Set is not covered in Operational Rate Set. */
                prStaRec->u2DesiredRateSet = u2OperationalRateSet;
            }

            /* Try to set the best initial rate for this entry */
            if (!rateGetBestInitialRateIndex(prStaRec->u2DesiredRateSet,
                                             prStaRec->rRcpi,
                                             &prStaRec->ucCurrRate1Index)) {

                if (!rateGetLowestRateIndexFromRateSet(prStaRec->u2DesiredRateSet,
                                                       &prStaRec->ucCurrRate1Index)) {
                    ASSERT(0);
                }
            }

            if (nicSetHwBySta(prAdapter, prStaRec) == FALSE) {
                ASSERT(FALSE);
            }

#if CFG_TX_FRAGMENT
            if (prConnSettings->fgIsEnableTxAutoFragmentForBT) {
                txRateSetInitForBT(prAdapter, prStaRec);
            }
#endif /* CFG_TX_FRAGMENT */
        }
    }

    return WLAN_STATUS_SUCCESS;

} /* end of wlanoidSetDesiredRates() */



/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to query the maximum frame size in bytes,
*        not including the header.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[out] pvQueryBuffer A pointer to the buffer that holds the result of
*                           the query.
* \param[in] u4QueryBufferLen The length of the query buffer.
* \param[out] pu4QueryInfoLen If the call is successful, returns the number of
*                               bytes written into the query buffer. If the
*                               call failed due to invalid length of the query
*                               buffer, returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_LENGTH
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidQueryMaxFrameSize (
    IN  P_ADAPTER_T       prAdapter,
    OUT PVOID             pvQueryBuffer,
    IN  UINT_32           u4QueryBufferLen,
    OUT PUINT_32          pu4QueryInfoLen
    )
{
    DEBUGFUNC("wlanoidQueryMaxFrameSize");


    ASSERT(prAdapter);
    ASSERT(pu4QueryInfoLen);

    if (u4QueryBufferLen < sizeof(UINT_32)) {
        *pu4QueryInfoLen = sizeof(UINT_32);
        return WLAN_STATUS_INVALID_LENGTH;
    }

    ASSERT(pvQueryBuffer);

    *(PUINT_32)pvQueryBuffer = ETHERNET_MAX_PKT_SZ - ETHERNET_HEADER_SZ;
    *pu4QueryInfoLen = sizeof(UINT_32);

    return WLAN_STATUS_SUCCESS;
} /* wlanoidQueryMaxFrameSize */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to query the maximum total packet length
*        in bytes.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[out] pvQueryBuffer A pointer to the buffer that holds the result of
*                           the query.
* \param[in] u4QueryBufferLen The length of the query buffer.
* \param[out] pu4QueryInfoLen If the call is successful, returns the number of
*                            bytes written into the query buffer. If the call
*                            failed due to invalid length of the query buffer,
*                            returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_LENGTH
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidQueryMaxTotalSize (
    IN  P_ADAPTER_T       prAdapter,
    OUT PVOID             pvQueryBuffer,
    IN  UINT_32           u4QueryBufferLen,
    OUT PUINT_32          pu4QueryInfoLen
    )
{
    DEBUGFUNC("wlanoidQueryMaxTotalSize");

    ASSERT(prAdapter);
    ASSERT(pu4QueryInfoLen);

    if (u4QueryBufferLen < sizeof(UINT_32)) {
        *pu4QueryInfoLen = sizeof(UINT_32);
        return WLAN_STATUS_INVALID_LENGTH;
    }

    ASSERT(pvQueryBuffer);

    *(PUINT_32)pvQueryBuffer = ETHERNET_MAX_PKT_SZ;
    *pu4QueryInfoLen = sizeof(UINT_32);

    return WLAN_STATUS_SUCCESS;
} /* wlanoidQueryMaxTotalSize */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to query the vendor ID of the NIC.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[out] pvQueryBuffer A pointer to the buffer that holds the result of
*                           the query.
* \param[in] u4QueryBufferLen The length of the query buffer.
* \param[out] pu4QueryInfoLen If the call is successful, returns the number of
*                            bytes written into the query buffer. If the call
*                            failed due to invalid length of the query buffer,
*                            returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_LENGTH
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidQueryVendorId (
    IN  P_ADAPTER_T       prAdapter,
    OUT PVOID             pvQueryBuffer,
    IN  UINT_32           u4QueryBufferLen,
    OUT PUINT_32          pu4QueryInfoLen
    )
{
#if DBG
    PUINT_8               cp;
#endif
    DEBUGFUNC("wlanoidQueryVendorId");

    ASSERT(prAdapter);
    ASSERT(pu4QueryInfoLen);

    if (u4QueryBufferLen < sizeof(UINT_32)) {
        *pu4QueryInfoLen = sizeof(UINT_32);
        return WLAN_STATUS_INVALID_LENGTH;
    }

    ASSERT(pvQueryBuffer);

    kalMemCopy(pvQueryBuffer, prAdapter->aucMacAddress, 3);
    *((PUINT_8)pvQueryBuffer + 3) = 1;
    *pu4QueryInfoLen = sizeof(UINT_32);

#if DBG
    cp = (PUINT_8)pvQueryBuffer;
    DBGLOG(REQ, LOUD, ("Vendor ID=%02x-%02x-%02x-%02x\n", cp[0], cp[1], cp[2], cp[3]));
#endif

    return WLAN_STATUS_SUCCESS;
} /* wlanoidQueryVendorId */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to query the current RSSI value.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[in] pvQueryBuffer Pointer to the buffer that holds the result of the query.
* \param[in] u4QueryBufferLen The length of the query buffer.
* \param[out] pu4QueryInfoLen If the call is successful, returns the number of
*   bytes written into the query buffer. If the call failed due to invalid length of
*   the query buffer, returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_BUFFER_TOO_SHORT
* \retval WLAN_STATUS_ADAPTER_NOT_READY
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidQueryRssi (
    IN  P_ADAPTER_T       prAdapter,
    OUT PVOID             pvQueryBuffer,
    IN  UINT_32           u4QueryBufferLen,
    OUT PUINT_32          pu4QueryInfoLen
    )
{
    PARAM_RSSI rRssi;
    DEBUGFUNC("wlanoidQueryRssi");


    ASSERT(prAdapter);
    ASSERT(pu4QueryInfoLen);

    *pu4QueryInfoLen = sizeof(PARAM_RSSI);

    /* Check for query buffer length */
    if (u4QueryBufferLen < *pu4QueryInfoLen) {
        DBGLOG(REQ, WARN, ("Too short length %ld\n", u4QueryBufferLen));
        return WLAN_STATUS_BUFFER_TOO_SHORT;
    }

    if (prAdapter->eConnectionStateIndicated == MEDIA_STATE_DISCONNECTED) {
        return WLAN_STATUS_ADAPTER_NOT_READY;
    }

    rxUpdateRssi(prAdapter);

    rRssi = prAdapter->rBssInfo.rRssi;

    /*For WHQL test, Rssi should be in range -10 ~ -200 dBm*/
    if (rRssi > PARAM_WHQL_RSSI_MAX_DBM) {
        rRssi = PARAM_WHQL_RSSI_MAX_DBM;
    }

    ASSERT(pvQueryBuffer);

    *(PINT_32)pvQueryBuffer = rRssi;

    DBGLOG(REQ, INFO, ("Current RSSI: %ld dBm\n", *(PINT_32)pvQueryBuffer));

    return WLAN_STATUS_SUCCESS;

} /* end of wlanoidQueryRssi() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to query the current RSSI trigger value.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[in] pvQueryBuffer Pointer to the buffer that holds the result of the query.
* \param[in] u4QueryBufferLen The length of the query buffer.
* \param[out] pu4QueryInfoLen If the call is successful, returns the number of
*   bytes written into the query buffer. If the call failed due to invalid length of
*   the query buffer, returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_BUFFER_TOO_SHORT
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidQueryRssiTrigger (
    IN  P_ADAPTER_T       prAdapter,
    OUT PVOID             pvQueryBuffer,
    IN  UINT_32           u4QueryBufferLen,
    OUT PUINT_32          pu4QueryInfoLen
    )
{
    DEBUGFUNC("wlanoidQueryRssiTrigger");

    ASSERT(prAdapter);
    ASSERT(pu4QueryInfoLen);

    *pu4QueryInfoLen = sizeof(PARAM_RSSI);

    /* Check for query buffer length */
    if (u4QueryBufferLen < *pu4QueryInfoLen) {
        DBGLOG(REQ, WARN, ("Too short length %ld\n", u4QueryBufferLen));
        return WLAN_STATUS_BUFFER_TOO_SHORT;
    }

    ASSERT(pvQueryBuffer);
    *(PINT_32) pvQueryBuffer = prAdapter->rRssiTriggerValue;

    DBGLOG(REQ, INFO, ("RSSI trigger: %ld dBm\n", *(PINT_32) pvQueryBuffer));

    return WLAN_STATUS_SUCCESS;
}   /* wlanoidQueryRssiTrigger */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to set a trigger value of the RSSI event.
*
* \param[in] prAdapter Pointer to the Adapter structure
* \param[in] pvSetBuffer A pointer to the buffer that holds the data to be set.
* \param[in] u4SetBufferLen The length of the set buffer.
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*                          bytes read from the set buffer. If the call failed
*                          due to invalid length of the set buffer, returns the
*                          amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
*
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidSetRssiTrigger (
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID             pvSetBuffer,
    IN  UINT_32           u4SetBufferLen,
    OUT PUINT_32          pu4SetInfoLen
    )
{
    DEBUGFUNC("wlanoidSetRssiTrigger");

    ASSERT(prAdapter);
    ASSERT(pvSetBuffer);
    ASSERT(pu4SetInfoLen);

    *pu4SetInfoLen = sizeof(PARAM_RSSI);

    /* Save the RSSI trigger value to the Adapter structure */
    prAdapter->rRssiTriggerValue = *(PINT_32) pvSetBuffer;

    /* If the RSSI trigger value is equal to the current RSSI value, the
       indication triggers immediately. We need to indicate the protocol
       that an RSSI status indication event triggers. */
    if (prAdapter->rRssiTriggerValue == prAdapter->rBssInfo.rRssi) {
        kalIndicateStatusAndComplete(prAdapter->prGlueInfo,
            WLAN_STATUS_MEDIA_SPECIFIC_INDICATION,
            (PVOID) &prAdapter->rBssInfo.rRssi, sizeof(PARAM_RSSI));
    }

    return WLAN_STATUS_SUCCESS;
}   /* wlanoidSetRssiTrigger */



/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to set a suggested value for the number of
*        bytes of received packet data that will be indicated to the protocol
*        driver. We just accept the set and ignore this value.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[in] pvSetBuffer A pointer to the buffer that holds the data to be set.
* \param[in] u4SetBufferLen The length of the set buffer.
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*                          bytes read from the set buffer. If the call failed
*                          due to invalid length of the set buffer, returns
*                          the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_LENGTH
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidSetCurrentLookahead (
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID             pvSetBuffer,
    IN  UINT_32           u4SetBufferLen,
    OUT PUINT_32          pu4SetInfoLen
    )
{
    DEBUGFUNC("wlanoidSetCurrentLookahead");

    ASSERT(prAdapter);
    ASSERT(pvSetBuffer);
    ASSERT(pu4SetInfoLen);

    if (u4SetBufferLen < sizeof(UINT_32)) {
        *pu4SetInfoLen = sizeof(UINT_32);
        return WLAN_STATUS_INVALID_LENGTH;
    }

    *pu4SetInfoLen = sizeof(UINT_32);
    return WLAN_STATUS_SUCCESS;
} /* wlanoidSetCurrentLookahead */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to query the number of frames that the driver
*        receives but does not indicate to the protocols due to errors.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
* \param[out] pvQueryBuf A pointer to the buffer that holds the result of
*                           the query.
* \param[in] u4QueryBufLen The length of the query buffer.
* \param[out] pu4QueryInfoLen If the call is successful, returns the number of
*                            bytes written into the query buffer. If the call
*                            failed due to invalid length of the query buffer,
*                            returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_LENGTH
* \retval WLAN_STATUS_ADAPTER_NOT_READY
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidQueryRcvError (
    IN  P_ADAPTER_T         prAdapter,
    IN  PVOID               pvQueryBuffer,
    IN  UINT_32             u4QueryBufferLen,
    OUT PUINT_32            pu4QueryInfoLen
    )
{
    P_RX_CTRL_T         prRxCtrl;
    WLAN_STATUS      rStatus = WLAN_STATUS_SUCCESS;
    UINT_64                  u8Tmp;

    DEBUGFUNC("wlanoidQueryRcvError");
    DBGLOG(REQ, TRACE, ("\n"));

    ASSERT(prAdapter);
    ASSERT(pu4QueryInfoLen);

    if (u4QueryBufferLen < sizeof(UINT_32)) {
        *pu4QueryInfoLen = sizeof(UINT_32);
        return WLAN_STATUS_INVALID_LENGTH;
    }

    if (pvQueryBuffer == NULL) {
        ASSERT(FALSE);
        return WLAN_STATUS_INVALID_LENGTH;
    }

    if (prAdapter->rAcpiState == ACPI_STATE_D3) {
        DBGLOG(REQ, WARN, ("Fail in query receive error! (Adapter not ready). ACPI=D%d, Radio=%d\n",
                    prAdapter->rAcpiState, prAdapter->fgIsRadioOff));
        *pu4QueryInfoLen = sizeof(UINT_32);
        return WLAN_STATUS_ADAPTER_NOT_READY;
    }

    /* NOTE(Kevin): WZC query RCV_ERROR often, so don't query HW Counter Here.
     * Thus we can return SUCCESS instead of PENDING for WinXP when WZC Query RCV_ERROR.
     */
    //statisticsPeekHWCounter(prAdapter);

    prRxCtrl = &prAdapter->rRxCtrl;
    u8Tmp = prRxCtrl->au8Statistics[RX_ERROR_DROP_COUNT] + \
                   prRxCtrl->au8Statistics[RX_FIFO_FULL_DROP_COUNT] -\
                   prRxCtrl->au8Statistics[RX_FCS_ERR_DROP_COUNT] +\
                   prRxCtrl->au8Statistics[RX_BB_FCS_ERROR_COUNT];

    if (u4QueryBufferLen == sizeof(UINT_32)) {
        /* Return a 32-bit counter. */
        *(PUINT_32)pvQueryBuffer = (UINT_32)u8Tmp;

        DBGLOG(REQ, LOUD, ("Rx Error: %ld\n", *(PUINT_32)pvQueryBuffer));
    }
    else if (u4QueryBufferLen < sizeof(UINT_64)) {
        /* Not enough room for the query information. */
        rStatus = WLAN_STATUS_INVALID_LENGTH;
    }
    else {
        /* Return a 64-bit counter. */
        *(PUINT_64)pvQueryBuffer = u8Tmp;

        DBGLOG(REQ, LOUD, ("Rx Error: %"DBG_PRINTF_64BIT_DEC"\n", *(PUINT_64)pvQueryBuffer));
    }

    *pu4QueryInfoLen = sizeof(UINT_64);

    return rStatus;
} /* wlanoidQueryRcvError */


/*----------------------------------------------------------------------------*/
/*! \brief This routine is called to query the number of frames that the NIC
*          cannot receive due to lack of NIC receive buffer space.
*
* \param[in] pvAdapter Pointer to the Adapter structure
* \param[in] pvQueryBuf A pointer to the buffer that holds the result of the
*                          query buffer
* \param[in] u4QueryBufLen The length of the query buffer
* \param[out] pu4QueryInfoLen If the call is successful, returns the number of
*                            bytes written into the query buffer. If the call
*                            failed due to invalid length of the query buffer,
*                            returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS If success;
* \retval WLAN_STATUS_INVALID_LENGTH
* \retval WLAN_STATUS_ADAPTER_NOT_READY
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidQueryRcvNoBuffer (
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID             pvQueryBuffer,
    IN  UINT_32           u4QueryBufferLen,
    OUT PUINT_32          pu4QueryInfoLen
    )
{
    P_RX_CTRL_T         prRxCtrl;
    WLAN_STATUS      rStatus = WLAN_STATUS_SUCCESS;

    DEBUGFUNC("wlanoidQueryRcvNoBuffer");
    DBGLOG(REQ, TRACE, ("\n"));

    ASSERT(prAdapter);
    ASSERT(pu4QueryInfoLen);

    if (u4QueryBufferLen < sizeof(UINT_32)) {
        *pu4QueryInfoLen = sizeof(UINT_32);
        return WLAN_STATUS_INVALID_LENGTH;
    }

    if (pvQueryBuffer == NULL) {
        ASSERT(FALSE);
        return WLAN_STATUS_INVALID_LENGTH;
    }

    if (prAdapter->rAcpiState == ACPI_STATE_D3) {
        DBGLOG(REQ, WARN, ("Fail in query receive no buffer! (Adapter not ready). ACPI=D%d, Radio=%d\n",
                    prAdapter->rAcpiState, prAdapter->fgIsRadioOff));
        *pu4QueryInfoLen = sizeof(UINT_32);
        return WLAN_STATUS_ADAPTER_NOT_READY;
    }

    statisticsPeekHWCounter(prAdapter);

    prRxCtrl = &prAdapter->rRxCtrl;

    if (u4QueryBufferLen == sizeof(UINT_32)) {
        /* Return a 32-bit counter. */
        *(PUINT_32)pvQueryBuffer = (UINT_32)prRxCtrl->au8Statistics[RX_FIFO_FULL_DROP_COUNT];

        DBGLOG(REQ, LOUD, ("Rx FIFO full drop count: %ld\n", *(PUINT_32)pvQueryBuffer));
    }
    else if (u4QueryBufferLen < sizeof(UINT_64)) {
        /* Not enough room for the query information. */
        rStatus = WLAN_STATUS_INVALID_LENGTH;
    }
    else {
        /* Return a 64-bit counter. */
        *(PUINT_64)pvQueryBuffer = prRxCtrl->au8Statistics[RX_FIFO_FULL_DROP_COUNT];

        DBGLOG(REQ, LOUD, ("Rx FIFO full drop count: %"DBG_PRINTF_64BIT_DEC"\n", *(PUINT_64)pvQueryBuffer));
    }

    *pu4QueryInfoLen = sizeof(UINT_64);

    return rStatus;
}   /* wlanoidQueryRcvNoBuffer */

/*----------------------------------------------------------------------------*/
/*! \brief This routine is called to query the number of frames that the NIC
*          received and it is CRC error.
*
* \param[in] pvAdapter Pointer to the Adapter structure
* \param[in] pvQueryBuf A pointer to the buffer that holds the result of the
*                          query buffer
* \param[in] u4QueryBufLen The length of the query buffer
* \param[out] pu4QueryInfoLen If the call is successful, returns the number of
*                            bytes written into the query buffer. If the call
*                            failed due to invalid length of the query buffer,
*                            returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS If success;
* \retval WLAN_STATUS_INVALID_LENGTH
* \retval WLAN_STATUS_ADAPTER_NOT_READY
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidQueryRcvCrcError (
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID             pvQueryBuffer,
    IN  UINT_32           u4QueryBufferLen,
    OUT PUINT_32          pu4QueryInfoLen
    )
{
    P_RX_CTRL_T         prRxCtrl;
    WLAN_STATUS      rStatus = WLAN_STATUS_SUCCESS;

    DEBUGFUNC("wlanoidQueryRcvCrcError");
    DBGLOG(REQ, TRACE, ("\n"));

    ASSERT(prAdapter);
    ASSERT(pu4QueryInfoLen);

    if (u4QueryBufferLen < sizeof(UINT_32)) {
        *pu4QueryInfoLen = sizeof(UINT_32);
        return WLAN_STATUS_INVALID_LENGTH;
    }

    if (pvQueryBuffer == NULL) {
        ASSERT(FALSE);
        return WLAN_STATUS_INVALID_LENGTH;
    }

    if (prAdapter->rAcpiState == ACPI_STATE_D3) {
        DBGLOG(REQ, WARN, ("Fail in query receive crc error! (Adapter not ready). ACPI=D%d, Radio=%d\n",
                    prAdapter->rAcpiState, prAdapter->fgIsRadioOff));
        *pu4QueryInfoLen = sizeof(UINT_32);
        return WLAN_STATUS_ADAPTER_NOT_READY;
    }
    statisticsPeekHWCounter(prAdapter);

    prRxCtrl = &prAdapter->rRxCtrl;

    if (u4QueryBufferLen == sizeof(UINT_32)) {
        /* Return a 32-bit counter. */
        *(PUINT_32)pvQueryBuffer = (UINT_32)prRxCtrl->au8Statistics[RX_BB_FCS_ERROR_COUNT];

        DBGLOG(REQ, LOUD, ("Rx Crc error count: %ld\n", *(PUINT_32)pvQueryBuffer));
    }
    else if (u4QueryBufferLen < sizeof(UINT_64)) {
        /* Not enough room for the query information. */
        rStatus = WLAN_STATUS_INVALID_LENGTH;
    }
    else {
        /* Return a 64-bit counter. */
        *(PUINT_64)pvQueryBuffer = prRxCtrl->au8Statistics[RX_BB_FCS_ERROR_COUNT];

        DBGLOG(REQ, LOUD, ("Rx Crc error count: %"DBG_PRINTF_64BIT_DEC"\n", *(PUINT_64)pvQueryBuffer));
    }

    *pu4QueryInfoLen = sizeof(UINT_64);

    return rStatus;
}   /* wlanoidQueryRcvCrcError */


/*----------------------------------------------------------------------------*/
/*! \brief  This routine is called to query the current 802.11 statistics.
*
* \param[in] pvAdapter Pointer to the Adapter structure
* \param[in] pvQueryBuf A pointer to the buffer that holds the result of the
*                          query buffer
* \param[in] u4QueryBufLen The length of the query buffer
* \param[out] pu4QueryInfoLen If the call is successful, returns the number of
*                            bytes written into the query buffer. If the call
*                            failed due to invalid length of the query buffer,
*                            returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_LENGTH
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidQueryStatistics (
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID             pvQueryBuffer,
    IN  UINT_32           u4QueryBufferLen,
    OUT PUINT_32          pu4QueryInfoLen
    )
{
    P_RX_CTRL_T                             prRxCtrl;
    P_TX_CTRL_T                             prTxCtrl;
    P_PARAM_802_11_STATISTICS_STRUCT_T      prStatistics;
    WLAN_STATUS      rStatus = WLAN_STATUS_SUCCESS;

    DEBUGFUNC("wlanoidQueryStatistics");
    DBGLOG(REQ, TRACE, ("\n"));

    ASSERT(prAdapter);
    ASSERT(pvQueryBuffer);
    ASSERT(pu4QueryInfoLen);

    *pu4QueryInfoLen = sizeof(PARAM_802_11_STATISTICS_STRUCT_T);

    if (u4QueryBufferLen < sizeof(PARAM_802_11_STATISTICS_STRUCT_T)) {
        return WLAN_STATUS_INVALID_LENGTH;
    }

    if (prAdapter->rAcpiState == ACPI_STATE_D3) {
        DBGLOG(REQ, WARN, ("Fail in query statistics! (Adapter not ready). ACPI=D%d, Radio=%d\n",
                    prAdapter->rAcpiState, prAdapter->fgIsRadioOff));
        return WLAN_STATUS_ADAPTER_NOT_READY;
    }

    statisticsPeekHWCounter(prAdapter);

    prRxCtrl = &prAdapter->rRxCtrl;
    prTxCtrl = &prAdapter->rTxCtrl;

    prStatistics = (P_PARAM_802_11_STATISTICS_STRUCT_T) pvQueryBuffer;

    prStatistics->u4Length =  sizeof(PARAM_802_11_STATISTICS_STRUCT_T);

    /* Tx Counters */
    prStatistics->rTransmittedFragmentCount.QuadPart =
        prTxCtrl->au8Statistics[TX_MPDU_OK_COUNT];

    prStatistics->rMulticastTransmittedFrameCount.QuadPart =
        prTxCtrl->au8Statistics[TX_BMCAST_MPDU_OK_COUNT];

    prStatistics->rFailedCount.QuadPart =
        prTxCtrl->au8Statistics[TX_MPDU_ALL_ERR_COUNT];

    prStatistics->rRetryCount.QuadPart =
        prTxCtrl->au8Statistics[TX_MPDU_TX_TWICE_OK_COUNT] +
        prTxCtrl->au8Statistics[TX_MPDU_TX_MORE_TWICE_OK_COUNT];

    prStatistics->rMultipleRetryCount.QuadPart =
        prTxCtrl->au8Statistics[TX_MPDU_TX_MORE_TWICE_OK_COUNT];

    /* Ctrl Frame Counters */
    prStatistics->rRTSSuccessCount.QuadPart =
        prTxCtrl->au8Statistics[TX_MPDU_RTS_OK_COUNT];

    prStatistics->rRTSFailureCount.QuadPart =
        prTxCtrl->au8Statistics[TX_MPDU_RTS_FAIL_COUNT];

    prStatistics->rACKFailureCount.QuadPart =
        prTxCtrl->au8Statistics[TX_MPDU_TOTAL_RETRY_COUNT] -
        prTxCtrl->au8Statistics[TX_MPDU_OK_COUNT];
        /* prTxCtrl->au8Statistics[TX_MPDU_MPDU_RETRY_ERR_COUNT]; */

    /* Rx Counters */
    prStatistics->rFrameDuplicateCount.QuadPart =
        prRxCtrl->au8Statistics[RX_DUPLICATE_DROP_COUNT];

    prStatistics->rReceivedFragmentCount.QuadPart =
        prRxCtrl->au8Statistics[RX_MPDU_TOTAL_COUNT];

    prStatistics->rMulticastReceivedFrameCount.QuadPart = \
        prRxCtrl->au8Statistics[RX_BMCAST_DATA_FRAME_COUNT] + \
        prRxCtrl->au8Statistics[RX_BMCAST_MGMT_FRAME_COUNT] ;

    prStatistics->rFCSErrorCount.QuadPart =
        prRxCtrl->au8Statistics[RX_BB_FCS_ERROR_COUNT];

    return rStatus;
}   /* wlanoidQueryStatistics */

/*----------------------------------------------------------------------------*/
/*! \brief  This routine is called to query the network device statistics for Linux.
*
* \param[in] prAdapter          Pointer to the Adapter structure.
* \param[in] pvQueryBuffer      Pointer to the buffer that holds the result of
*                               the query.
* \param[in] u4QueryBufferLen   The length of the query buffer.
* \param[out] pu4QueryInfoLen   If the call is successful, returns the number of
*                               bytes written into the query buffer. If the call
*                               failed due to invalid length of the query buffer,
*                               returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_LENGTH
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidQueryStatisticsForLinux (
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID             pvQueryBuffer,
    IN  UINT_32           u4QueryBufferLen,
    OUT PUINT_32          pu4QueryInfoLen
    )
{
    P_RX_CTRL_T prRxCtrl;
    P_TX_CTRL_T prTxCtrl;
    P_PARAM_LINUX_NETDEV_STATISTICS_T prCustomNetDevStat;

    DEBUGFUNC("wlanoidQueryStatisticsForLinux");


    ASSERT(prAdapter);
    ASSERT(pu4QueryInfoLen);

    DBGLOG(REQ, INFO, ("\n"));

    *pu4QueryInfoLen = sizeof(PARAM_LINUX_NETDEV_STATISTICS_T);

    if (u4QueryBufferLen < sizeof(PARAM_LINUX_NETDEV_STATISTICS_T)) {
        return WLAN_STATUS_INVALID_LENGTH;
    }

    prRxCtrl = &prAdapter->rRxCtrl;
    prTxCtrl = &prAdapter->rTxCtrl;

    ASSERT(pvQueryBuffer);

    prCustomNetDevStat = (P_PARAM_LINUX_NETDEV_STATISTICS_T)pvQueryBuffer;

    prCustomNetDevStat->u4RxPackets = (UINT_32)prRxCtrl->au8Statistics[RX_DATA_INDICATION_COUNT];
    prCustomNetDevStat->u4TxPackets = (UINT_32)prTxCtrl->au8Statistics[TX_MSDU_OK_COUNT];
    prCustomNetDevStat->u4RxBytes   = (UINT_32)prRxCtrl->au8Statistics[RX_MSDU_BYTES_COUNT];
    prCustomNetDevStat->u4TxBytes   = (UINT_32)prTxCtrl->au8Statistics[TX_MSDU_BYTES_COUNT];
    prCustomNetDevStat->u4RxErrors  = (UINT_32)prRxCtrl->au8Statistics[RX_ERROR_DROP_COUNT];
    prCustomNetDevStat->u4TxErrors  = (UINT_32)prTxCtrl->au8Statistics[TX_MSDU_FAIL_COUNT];
    prCustomNetDevStat->u4Multicast = (UINT_32)prTxCtrl->au8Statistics[RX_BMCAST_DATA_FRAME_COUNT];

    return WLAN_STATUS_SUCCESS;

}

/*----------------------------------------------------------------------------*/
/*! \brief  This routine is called to query the permanent MAC address of the NIC.
*
* \param[in] pvAdapter Pointer to the Adapter structure
* \param[in] pvQueryBuf A pointer to the buffer that holds the result of the
*                          query buffer
* \param[in] u4QueryBufLen The length of the query buffer
* \param[out] pu4QueryInfoLen If the call is successful, returns the number of
*                            bytes written into the query buffer. If the call
*                            failed due to invalid length of the query buffer,
*                            returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidQueryPermanentAddr (
    IN P_ADAPTER_T  prAdapter,
    IN  PVOID    pvQueryBuf,
    IN  UINT_32  u4QueryBufLen,
    OUT PUINT_32 pu4QueryInfoLen
    )
{

    DEBUGFUNC("wlanoidQueryPermanentAddr");

    ASSERT(prAdapter);
    ASSERT(pu4QueryInfoLen);

    if (u4QueryBufLen != 0) {
        ASSERT(pvQueryBuf);
#if 0
    kalMemCopy(pvQueryBuf, prAdapter->permanentMacAddress, MAC_ADDR_LEN);
#else
    kalMemCopy(pvQueryBuf, prAdapter->rEEPROMCtrl.aucMacAddress, MAC_ADDR_LEN);
#endif
    *pu4QueryInfoLen = MAC_ADDR_LEN;
    }

    return WLAN_STATUS_SUCCESS;
}   /* wlanoidQueryPermanentAddr */


/*----------------------------------------------------------------------------*/
/*! \brief  This routine is called to query the MAC address the NIC is currently using.
*
* \param[in] pvAdapter Pointer to the Adapter structure
* \param[in] pvQueryBuf A pointer to the buffer that holds the result of the
*                          query buffer
* \param[in] u4QueryBufLen The length of the query buffer
* \param[out] pu4QueryInfoLen If the call is successful, returns the number of
*                            bytes written into the query buffer. If the call
*                            failed due to invalid length of the query buffer,
*                            returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_BUFFER_TOO_SHORT
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidQueryCurrentAddr (
    IN P_ADAPTER_T  prAdapter,
    IN  PVOID    pvQueryBuffer,
    IN  UINT_32  u4QueryBufferLen,
    OUT PUINT_32 pu4QueryInfoLen
    )
{

    DEBUGFUNC("wlanoidQueryCurrentAddr");

    ASSERT(prAdapter);
    ASSERT(pu4QueryInfoLen);

    *pu4QueryInfoLen = MAC_ADDR_LEN;

    if (u4QueryBufferLen < MAC_ADDR_LEN) {
        return WLAN_STATUS_BUFFER_TOO_SHORT;
    }

    ASSERT(pvQueryBuffer);

    kalMemCopy(pvQueryBuffer, prAdapter->aucMacAddress, MAC_ADDR_LEN);

    return WLAN_STATUS_SUCCESS;
}   /* wlanoidQueryCurrentAddr */


/*----------------------------------------------------------------------------*/
/*! \brief  This routine is called to query NIC link speed.
*
* \param[in] pvAdapter Pointer to the Adapter structure
* \param[in] pvQueryBuf A pointer to the buffer that holds the result of the
*                          query buffer
* \param[in] u4QueryBufLen The length of the query buffer
* \param[out] pu4QueryInfoLen If the call is successful, returns the number of
*                            bytes written into the query buffer. If the call
*                            failed due to invalid length of the query buffer,
*                            returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_BUFFER_TOO_SHORT
*
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidQueryLinkSpeed(
    IN P_ADAPTER_T  prAdapter,
    IN  PVOID    pvQueryBuffer,
    IN  UINT_32  u4QueryBufferLen,
    OUT PUINT_32 pu4QueryInfoLen
    )
{
    UINT_8 ucCurrTxDataRate;

    DEBUGFUNC("wlanoidQueryLinkSpeed");


    ASSERT(prAdapter);
    ASSERT(pu4QueryInfoLen);

    *pu4QueryInfoLen = sizeof(UINT_32);

    if (u4QueryBufferLen < sizeof(UINT_32)) {
        return WLAN_STATUS_BUFFER_TOO_SHORT;
    }

    ASSERT(pvQueryBuffer);

    if (prAdapter->eConnectionState == MEDIA_STATE_CONNECTED) {
        ucCurrTxDataRate = aucDataRate[prAdapter->rTxCtrl.ucCurrRateIndex];
    }
    else {
        ucCurrTxDataRate = RATE_1M;
    }

    *(PUINT_32)pvQueryBuffer = (UINT_32)((UINT_32)ucCurrTxDataRate * 5000);

    DBGLOG(REQ, LOUD,
        ("Link speed = %dMbps\n", ucCurrTxDataRate / 2));

    return WLAN_STATUS_SUCCESS;
} /* end of wlanoidQueryLinkSpeed() */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to query MCR value.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
* \param[out] pvQueryBuf A pointer to the buffer that holds the result of
*                           the query.
* \param[in] u4QueryBufLen The length of the query buffer.
* \param[out] pu4QueryInfoLen If the call is successful, returns the number of
*                            bytes written into the query buffer. If the call
*                            failed due to invalid length of the query buffer,
*                            returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_LENGTH
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidQueryMcrRead (
    IN P_ADAPTER_T  prAdapter,
    IN  PVOID    pvQueryBuffer,
    IN  UINT_32  u4QueryBufferLen,
    OUT PUINT_32 pu4QueryInfoLen
    )
{
    P_PARAM_CUSTOM_MCR_RW_STRUC_T prMcrRdInfo;

    DEBUGFUNC("wlanoidQueryMcrRead");


    ASSERT(prAdapter);
    ASSERT(pu4QueryInfoLen);

    *pu4QueryInfoLen = sizeof(PARAM_CUSTOM_MCR_RW_STRUC_T);

    if (u4QueryBufferLen < sizeof(PARAM_CUSTOM_MCR_RW_STRUC_T)) {
        return WLAN_STATUS_INVALID_LENGTH;
    }

    ASSERT(pvQueryBuffer);

    prMcrRdInfo = (P_PARAM_CUSTOM_MCR_RW_STRUC_T)pvQueryBuffer;

    HAL_MCR_RD(prAdapter,
               prMcrRdInfo->u4McrOffset & BITS(2,31), //address is in DWORD unit
               &prMcrRdInfo->u4McrData);

    DBGLOG(REQ, INFO, ("MCR Read: Offset = %#08lx, Data = %#08lx\n",
        prMcrRdInfo->u4McrOffset, prMcrRdInfo->u4McrData));

    return WLAN_STATUS_SUCCESS;

} /* end of wlanoidQueryMcrRead() */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to wlanoidOid  testing.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[in] pvSetBuffer A pointer to the buffer that holds the data to be set.
* \param[in] u4SetBufferLen The length of the set buffer.
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*                           bytes read from the set buffer. If the call failed
*                           due to invalid length of the set buffer, returns
*                           the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_LENGTH
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidOidTest(
    IN P_ADAPTER_T  prAdapter,
    IN  PVOID    pvSetBuffer,
    IN  UINT_32  u4SetBufferLen,
    OUT PUINT_32 pu4SetInfoLen
    )
{
	PVOID	pContent = NULL;
	PVOID   pTemp = NULL;
	UINT_32 index = 0;
	CHAR    indexTemp[10];
	
	ASSERT(pvSetBuffer);

	DBGLOG(REQ, INFO, ("%s :%s\n", __FUNCTION__, pvSetBuffer));
	pTemp = strchr(pvSetBuffer, ' ');

	if(pTemp == NULL){
		DBGLOG(REQ, INFO, ("%s: get pTemp NULL\n", __FUNCTION__));
		return WLAN_STATUS_INVALID_LENGTH;
	}
	else
		DBGLOG(REQ, INFO,("%s get pTemp 0x%x~0x%x\n", __FUNCTION__, pTemp, pvSetBuffer));
	
	if(pTemp - pvSetBuffer > 9)
		return WLAN_STATUS_INVALID_LENGTH;
	else{
		strncpy(indexTemp, pvSetBuffer, pTemp - pvSetBuffer); 
		indexTemp[pTemp - pvSetBuffer] = '\0';
		DBGLOG(REQ, INFO, ("%s: indexTemp %s\n", __FUNCTION__, indexTemp));
		sscanf(indexTemp, "%d", &index);
		DBGLOG(REQ, INFO,("%s get Index %d\n", __FUNCTION__, index));
	}	

	pContent = pTemp + 1;
	switch (index){
		case 1:
		{
			UINT_8	u8Ip[4];
			UINT_32 u32Ip[4];				

#if 0
			if(4 == sscanf(pContent, "%d.%d.%d.%d", u32Ip + 3, u32Ip + 2, u32Ip + 1, u32Ip)){
#else
			if(4 == sscanf(pContent, "%d.%d.%d.%d", u32Ip, u32Ip + 1, u32Ip + 2, u32Ip + 3)){
#endif
				kalMemZero(u8Ip, sizeof(u8Ip));
				u8Ip [0] = u32Ip[0]&0xff,u8Ip [1] = u32Ip[1]&0xff,
				u8Ip [2] = u32Ip[2]&0xff,u8Ip [3] = u32Ip[3]&0xff;
				DBGLOG(REQ, INFO,("%s get IP %d.%d.%d.%d \n", __FUNCTION__, 
						*u8Ip, *(u8Ip + 1), *(u8Ip + 2), *(u8Ip + 3)));
				wlanoidSetIpAddress(prAdapter,
							&u8Ip,
							sizeof(u8Ip),
							pu4SetInfoLen);
			}else
				DBGLOG(REQ, INFO, ("%s sscanf failed\n", __FUNCTION__));
				
		}
			break;

		case 2:
		{
			UINT_32 on = 55;
			
			if(1 == sscanf(pContent, "%d", &on)){
				DBGLOG(REQ, INFO,("%s get ON %d\n", __FUNCTION__, on));

				if(1 == on)
					wlanRxSetBroadcast(prAdapter, 1);
				else if(0 == on)
					wlanRxSetBroadcast(prAdapter, 0);

			}


		}
			break;

		case 3:
		{
			P_GLUE_INFO_T pGlue = prAdapter->prGlueInfo;
			struct net_device *prNetDev = to_net_dev(pGlue);
			struct in_device *prIn;
			struct in_ifaddr *prIfaddr;
			UINT_32  ip;
			
			DBGLOG(REQ, INFO,("%s get %s\n", __FUNCTION__, 
				prNetDev->name));	
			prIn = (struct in_device *)(prNetDev->ip_ptr);
			DBGLOG(REQ, INFO,("%s 0x%x  get  prIn->dev 0x%x\n", __FUNCTION__, 
				prNetDev, prIn->dev));	
#if 0
			ASSERT(prIn);
			prIfaddr = prIn->ifa_list;
			ASSERT(prIfaddr);
			ip = prIfaddr->ifa_local;
			//ip = prIn->ifa_list->ifa_local;
			DBGLOG(REQ, INFO,("%s get %s ipv4 0x%x\n", __FUNCTION__, 
				prNetDev->name,	ip));	
#endif
		}
			break;
	}

	return  WLAN_STATUS_SUCCESS;

}
/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to write MCR and enable specific function.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[in] pvSetBuffer A pointer to the buffer that holds the data to be set.
* \param[in] u4SetBufferLen The length of the set buffer.
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*                           bytes read from the set buffer. If the call failed
*                           due to invalid length of the set buffer, returns
*                           the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_LENGTH
*/
/*----------------------------------------------------------------------------*/
UINT_8  PER_FLAG = 0;

WLAN_STATUS
wlanoidSetMcrWrite (
    IN P_ADAPTER_T  prAdapter,
    IN  PVOID    pvSetBuffer,
    IN  UINT_32  u4SetBufferLen,
    OUT PUINT_32 pu4SetInfoLen
    )
{
    P_PARAM_CUSTOM_MCR_RW_STRUC_T prMcrWrInfo;
    UINT_32 u4Tmp;

    DEBUGFUNC("wlanoidSetMcrWrite");


    ASSERT(prAdapter);
    ASSERT(pu4SetInfoLen);

    *pu4SetInfoLen = sizeof(PARAM_CUSTOM_MCR_RW_STRUC_T);

    if (u4SetBufferLen < sizeof(PARAM_CUSTOM_MCR_RW_STRUC_T)) {
        return WLAN_STATUS_INVALID_LENGTH;
    }

    ASSERT(pvSetBuffer);

    prMcrWrInfo = (P_PARAM_CUSTOM_MCR_RW_STRUC_T)pvSetBuffer;

    DBGLOG(REQ, INFO, ("MCR Write: Offset = %#08lx, Data = %#08lx\n",
        prMcrWrInfo->u4McrOffset, prMcrWrInfo->u4McrData));

#if 1
    if (prMcrWrInfo->u4McrOffset >= 0x500) {
        /* Backdoor configurations functions,
           this is used for debugging only.
        */

        PARAM_VOIP_CONFIG rVoipCfg;
        UINT_32 u4LenIn, u4LenOut;

        switch (prMcrWrInfo->u4McrOffset) {
        case 0x500:
            pmFsmRunEventSetPowerSaveProfile(prAdapter, ENUM_PSP_CONTINUOUS_ACTIVE);
            break;
        case 0x501:
            pmFsmRunEventSetPowerSaveProfile(prAdapter, ENUM_PSP_CONTINUOUS_POWER_SAVE);
            break;
        case 0x502:
            pmFsmRunEventSetPowerSaveProfile(prAdapter, ENUM_PSP_FAST_SWITCH);
            break;
        case 0x503: /* Enable VoIP polling function (20ms) */
            rVoipCfg.u4VoipTrafficInterval = 20;
            u4LenIn = sizeof(PARAM_VOIP_CONFIG);
            wlanoidSetVoipConnectionStatus(prAdapter, &rVoipCfg, u4LenIn, &u4LenOut);
            break;
        case 0x504: /* Disable VoIP polling function */
            rVoipCfg.u4VoipTrafficInterval = 0;
            u4LenIn = sizeof(PARAM_VOIP_CONFIG);
            wlanoidSetVoipConnectionStatus(prAdapter, &rVoipCfg, u4LenIn, &u4LenOut);
            break;
#if DBG
        /* Configuration of debug message (module/ level) */
        case 0x505:
            u4DebugModuleTemp = prMcrWrInfo->u4McrData;
            break;
        case 0x506:
            aucDebugModule[u4DebugModuleTemp] = (UINT_8)prMcrWrInfo->u4McrData;
            break;
#endif
        case 0x510:
            prAdapter->eConnectionState = MEDIA_STATE_CONNECTED;
            prAdapter->eConnectionStateIndicated = MEDIA_STATE_CONNECTED;

            kalIndicateStatusAndComplete(prAdapter->prGlueInfo,
                WLAN_STATUS_MEDIA_CONNECT, (PVOID) 0, 0);
            break;
        case 0x511:
            prAdapter->eConnectionState = MEDIA_STATE_DISCONNECTED;
            kalIndicateStatusAndComplete(prAdapter->prGlueInfo,
                WLAN_STATUS_MEDIA_DISCONNECT, (PVOID) 0, 0);
            break;
        case 0x512: /* Disable to respond UC indication for passing WiFi under full U-APSD case */
            {
            UINT_32 u4RegValue;
            HAL_MCR_RD(prAdapter, MCR_MPTCR, &u4RegValue);
            HAL_MCR_WR(prAdapter, MCR_MPTCR, u4RegValue & ~MPTCR_BCN_UC_EN);
            }
            break;
        case 0x520: /* Query debug TX/ RX counters */
            nicTxQueryStatus(prAdapter,
                (PUINT_8)NULL,&u4Tmp);
            nicTxQueryStatistics(prAdapter,
                (PUINT_8)NULL,&u4Tmp);
            nicRxQueryStatus(prAdapter,
                (PUINT_8)NULL,&u4Tmp);
            nicRxQueryStatistics(prAdapter,
                (PUINT_8)NULL,&u4Tmp);
            break;
        case 0x530: /* Set to ACPI D0 state */
            pmSetAcpiPowerD0(prAdapter);
            break;
        case 0x531: /* Set to ACPI D3 state */
            pmSetAcpiPowerD3(prAdapter);
            break;
        case 0x532: /*Setting up ATIM window under IBSS */
            {
            P_PM_INFO_T prPmInfo;
            P_PM_PROFILE_SETUP_INFO_T prPmProfSetupInfo;
            prPmInfo = &prAdapter->rPmInfo;
            prPmProfSetupInfo = &prPmInfo->rPmProfSetupInfo;
            prAdapter->rConnSettings.u2AtimWindow = (UINT_16)prMcrWrInfo->u4McrData;
            }
            break;
        case 0x533: /* Configure U-APSD AC function */
            {
            P_PM_INFO_T prPmInfo;
            P_PM_PROFILE_SETUP_INFO_T prPmProfSetupInfo;
            prPmInfo = &prAdapter->rPmInfo;
            prPmProfSetupInfo = &prPmInfo->rPmProfSetupInfo;
            prPmProfSetupInfo->bmfgApsdEnAc = (UINT_8)prMcrWrInfo->u4McrData;
            }
            break;
        case 0x534: /* Restore pattern search function */
            {
            P_PM_INFO_T prPmInfo;
            P_PM_PROFILE_SETUP_INFO_T prPmProfSetupInfo;
            prPmInfo = &prAdapter->rPmInfo;
            prPmProfSetupInfo = &prPmInfo->rPmProfSetupInfo;

            /* Initialize LP instruction number, all of the extra instruction need to be re-programmed again */
            prPmInfo->ucNumOfInstSleep = 0;
            prPmInfo->ucNumOfInstAwake = 0;
            prPmInfo->ucNumOfInstOn = 0;

            nicpmConfigPatternSearchFunc(prAdapter,
                                         prPmProfSetupInfo->fgBcPtrnSrchEn,
                                         prPmProfSetupInfo->fgMcPtrnSrchEn,
                                         prPmProfSetupInfo->fgUcPtrnSrchEn,
                                         prPmProfSetupInfo->fgBcPtrnMatchRcv,
                                         prPmProfSetupInfo->fgMcPtrnMatchRcv,
                                         prPmProfSetupInfo->fgUcPtrnMatchRcv,
                                         FALSE);
            }
            break;
        case 0x535: /* Disable pattern search function */
            {
            P_PM_INFO_T prPmInfo;
            P_PM_PROFILE_SETUP_INFO_T prPmProfSetupInfo;
            prPmInfo = &prAdapter->rPmInfo;
            prPmProfSetupInfo = &prPmInfo->rPmProfSetupInfo;

            /* Initialize LP instruction number, all of the extra instruction need to be re-programmed again */
            prPmInfo->ucNumOfInstSleep = 0;
            prPmInfo->ucNumOfInstAwake = 0;
            prPmInfo->ucNumOfInstOn = 0;

            nicpmConfigPatternSearchFunc(prAdapter,
                                         FALSE,
                                         FALSE,
                                         FALSE,
                                         FALSE,
                                         FALSE,
                                         FALSE,
                                         FALSE);
            }
            break;


        case 0x540: /* WMMPS B.K disable UC PSPoll */
            {
                P_PM_INFO_T prPmInfo;
                prPmInfo = &prAdapter->rPmInfo;
                prPmInfo->ucWmmPsDisableUcPoll = (UINT_8)prMcrWrInfo->u4McrData;

                if (prPmInfo->ucWmmPsDisableUcPoll && prPmInfo->ucWmmPsConnWithTrig) {
                    NIC_PM_WMM_PS_DISABLE_UC_TRIG(prAdapter, TRUE);
                }
                else {
                    NIC_PM_WMM_PS_DISABLE_UC_TRIG(prAdapter, FALSE);
                }
            }
            break;

        case 0x541:
            /* Save the new power mode. */
            prAdapter->rConnSettings.rPwrMode = (PARAM_POWER_MODE)prMcrWrInfo->u4McrData;

            if (prAdapter->rConnSettings.rPwrMode == Param_PowerModeCAM) {

                pmFsmRunEventSetPowerSaveProfile(
                    prAdapter,
                    aPowerModeToPwrSaveProfMapping[prAdapter->rConnSettings.rPwrMode]);

            }
            else {
                P_PM_INFO_T prPmInfo;
                prPmInfo = &prAdapter->rPmInfo;

                pmFsmRunEventSetPowerSaveProfile(
                        prAdapter,
                        aPowerModeToPwrSaveProfMapping[prAdapter->rConnSettings.rPwrMode]);

                prPmInfo->ucWmmPsEnterPsAtOnce  = 1;
            }
            break;

        case 0x542:
            {
                UINT_32 u4PacketFilter = 0;
                UINT_8 ucMCAddrList[6] = {0x01, 0x00, 0x5e, 0x00, 0x00, 0x01};

                UINT_32 u4SetInfoLen;

                u4PacketFilter |= PARAM_PACKET_FILTER_MULTICAST;

                wlanSetInformation(prAdapter,
                                   wlanoidSetCurrentPacketFilter,
                                   &u4PacketFilter,
                                   sizeof(u4PacketFilter),
                                   &u4SetInfoLen);

                wlanSetInformation(prAdapter,
                                   wlanoidSetMulticastList,
                                   &ucMCAddrList[0],
                                   (6),
                                   &u4SetInfoLen);
            }
		    break;
        case 0x543:
            {
				UINT_32 u4SetInfoLen;

				printk("[MT5921] MCR write wlanoidSetWmmPsMode, %d\n",prMcrWrInfo->u4McrData);
                wlanSetInformation(prAdapter,
                                   wlanoidSetWmmPsMode,
                                   &prMcrWrInfo->u4McrData,
                                   sizeof(prMcrWrInfo->u4McrData),
                                   &u4SetInfoLen);
            }		
		    break;
	case 0x545:
	    {
		PER_FLAG = prMcrWrInfo->u4McrData;
		printk("[MT5921] MCR write PER_FLAG %d\n", prMcrWrInfo->u4McrData);	

	    }
		break;				

        }
    }
    else {
        HAL_MCR_WR(prAdapter,
                   (prMcrWrInfo->u4McrOffset & BITS(2,31)), //address is in DWORD unit
                   prMcrWrInfo->u4McrData);
    }
#else
        HAL_MCR_WR(prAdapter,
                  prMcrWrInfo->u4McrOffset & 0xfffc,
                  prMcrWrInfo->u4McrData);
#endif


    return WLAN_STATUS_SUCCESS;
}   /* wlanoidSetMcrWrite */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to query EEPROM value.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
* \param[out] pvQueryBuf A pointer to the buffer that holds the result of
*                           the query.
* \param[in] u4QueryBufLen The length of the query buffer.
* \param[out] pu4QueryInfoLen If the call is successful, returns the number of
*                            bytes written into the query buffer. If the call
*                            failed due to invalid length of the query buffer,
*                            returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_FAILURE
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidQueryEepromRead (
    IN  P_ADAPTER_T  prAdapter,
    IN  PVOID        pvQueryBuffer,
    IN  UINT_32      u4QueryBufferLen,
    OUT PUINT_32     pu4QueryInfoLen
    )
{

    P_PARAM_CUSTOM_EEPROM_RW_STRUC_T prEepromRdInfo;
    UINT_16     u2Data;
    BOOLEAN     fgStatus;
    WLAN_STATUS rStatus = WLAN_STATUS_SUCCESS;

    DEBUGFUNC("wlanoidQueryEepromRead");

    ASSERT(prAdapter);
    ASSERT(pvQueryBuffer);
    ASSERT(pu4QueryInfoLen);

    prEepromRdInfo = (P_PARAM_CUSTOM_EEPROM_RW_STRUC_T) pvQueryBuffer;

    if(prEepromRdInfo->ucEepromMethod == PARAM_EEPROM_READ_METHOD_READ) {
        fgStatus = nicEepromRead16(prAdapter,
                            prEepromRdInfo->ucEepromIndex,
                            &u2Data
                            );
        if(fgStatus){
            prEepromRdInfo->u2EepromData = u2Data;
            DBGLOG(REQ, INFO, ("EEPROM Read: index=%#X, data=%#02X\n",
                    prEepromRdInfo->ucEepromIndex, u2Data));
        }
        else{
            DBGLOG(REQ, ERROR, ("EEPROM Read Failed: index=%#x.\n",
                    prEepromRdInfo->ucEepromIndex));
            rStatus = WLAN_STATUS_FAILURE;
        }
    }
    else if (prEepromRdInfo->ucEepromMethod == PARAM_EEPROM_READ_METHOD_GETSIZE) {
        prEepromRdInfo->u2EepromData = nicEepromGetSize( prAdapter);
        DBGLOG(REQ, INFO, ("EEPROM size =%d\n", prEepromRdInfo->u2EepromData));
    }

    *pu4QueryInfoLen = sizeof(PARAM_CUSTOM_EEPROM_RW_STRUC_T);


    return rStatus;
}   /* wlanoidQueryEepromRead */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to write EEPROM value.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[in] pvSetBuffer A pointer to the buffer that holds the data to be set.
* \param[in] u4SetBufferLen The length of the set buffer.
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*                           bytes read from the set buffer. If the call failed
*                           due to invalid length of the set buffer, returns
*                           the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_FAILURE
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidSetEepromWrite (
    IN P_ADAPTER_T  prAdapter,
    IN  PVOID       pvSetBuffer,
    IN  UINT_32     u4SetBufferLen,
    OUT PUINT_32    pu4SetInfoLen
    )
{
    P_PARAM_CUSTOM_EEPROM_RW_STRUC_T prEepromWrInfo;
    BOOLEAN     fgStatus;
    WLAN_STATUS rStatus = WLAN_STATUS_SUCCESS;

    DEBUGFUNC("wlanoidSetEepromWrite");

    ASSERT(prAdapter);
    ASSERT(pvSetBuffer);
    ASSERT(pu4SetInfoLen);

    *pu4SetInfoLen = sizeof(PARAM_CUSTOM_EEPROM_RW_STRUC_T);

    prEepromWrInfo = (P_PARAM_CUSTOM_EEPROM_RW_STRUC_T) pvSetBuffer;

    DBGLOG(REQ, INFO, ("EEPROM Write: index=0x%x, data=0x%x\n",
        prEepromWrInfo->ucEepromIndex, prEepromWrInfo->u2EepromData));

    fgStatus = nicEepromWrite16(prAdapter,
                                prEepromWrInfo->ucEepromIndex,
                                prEepromWrInfo->u2EepromData
                                );
    if(fgStatus == FALSE){
        DBGLOG(REQ, ERROR, ("EEPROM Write Failed.\n"));
        rStatus = WLAN_STATUS_FAILURE;
    }
    return rStatus;
}   /* wlanoidSetEepromWrite */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to query RX related statistics for RF test.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
* \param[out] pvQueryBuf A pointer to the buffer that holds the result of
*                           the query.
* \param[in] u4QueryBufLen The length of the query buffer.
* \param[out] pu4QueryInfoLen If the call is successful, returns the number of
*                            bytes written into the query buffer. If the call
*                            failed due to invalid length of the query buffer,
*                            returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_LENGTH
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidQueryRfTestRxStatus (
    IN  P_ADAPTER_T  prAdapter,
    IN  PVOID        pvQueryBuffer,
    IN  UINT_32      u4QueryBufferLen,
    OUT PUINT_32     pu4QueryInfoLen
    )
{
    P_PARAM_CUSTOM_RFTEST_RX_STATUS_STRUC_T prRxStatus;
    P_RX_CTRL_T                 prRxCtrl;
    UINT_32                     u4Tmp;

    DEBUGFUNC("wlanoidQueryRfTestRxStatus");

    ASSERT(prAdapter);
    ASSERT(pu4QueryInfoLen);

    prRxCtrl= &prAdapter->rRxCtrl;

    *pu4QueryInfoLen = sizeof(PARAM_CUSTOM_RFTEST_RX_STATUS_STRUC_T);

    /* Check for query buffer length */
    if (u4QueryBufferLen < *pu4QueryInfoLen) {
        DBGLOG(REQ, WARN, ("Invalid length %ld\n", u4QueryBufferLen));
        return WLAN_STATUS_INVALID_LENGTH;
    }

    ASSERT(pvQueryBuffer);
    prRxStatus = (P_PARAM_CUSTOM_RFTEST_RX_STATUS_STRUC_T) pvQueryBuffer;

    /* Query from interrupt result. */
    prRxStatus->u4IntRxOk = (UINT_32)prRxCtrl->au8Statistics[RX_MPDU_TOTAL_COUNT];
    prRxStatus->u4IntCrcErr= (UINT_32)prRxCtrl->au8Statistics[RX_FCS_ERR_DROP_COUNT];
    prRxStatus->u4IntShort= (UINT_32)prRxCtrl->au8Statistics[RX_MPDU_CCK_SHORT_PREAMBLE_COUNT];
    prRxStatus->u4IntLong= (UINT_32)prRxCtrl->au8Statistics[RX_MPDU_CCK_LONG_PREAMBLE_COUNT];

    DBGLOG(REQ, INFO, ("intRxOk: %ld\n", prRxStatus->u4IntRxOk));
    DBGLOG(REQ, INFO, ("intCrcErr: %ld\n", prRxStatus->u4IntCrcErr));
    DBGLOG(REQ, INFO, ("intLong: %ld\n", prRxStatus->u4IntShort));
    DBGLOG(REQ, INFO, ("intShort: %ld\n", prRxStatus->u4IntLong));

    statisticsPeekHWCounter(prAdapter);
    prRxStatus->u4PauCrcErrCount = (UINT_32) prRxCtrl->au8Statistics[RX_BB_FCS_ERROR_COUNT];
    prRxStatus->u4PauRxFifoFullCount = (UINT_32) prRxCtrl->au8Statistics[RX_BB_FIFO_FULL_COUNT];
    prRxStatus->u4PauRxPktCount = (UINT_32) prRxCtrl->au8Statistics[RX_BB_MPDU_COUNT];

    //For CCA time, we need to query it by ourselves.
    HAL_MCR_RD(prAdapter, MCR_MIBSCR, &u4Tmp);
    u4Tmp &= ~MIBSCR_INDEX_MASK;
    u4Tmp |= (MIBSCR_CCATIME_INDEX);
    HAL_MCR_WR(prAdapter, MCR_MIBSCR, u4Tmp);

    HAL_MCR_RD(prAdapter, MCR_MIBSDR, &u4Tmp);
    RX_ADD_CNT(prRxCtrl, RX_BB_CCA_TIME_COUNT, u4Tmp);
    prRxStatus->u4PauCCACount = (UINT_32) prRxCtrl->au8Statistics[RX_BB_CCA_TIME_COUNT];

    return WLAN_STATUS_SUCCESS;
}   /* rftestQueryTestRxStatus */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to query the number of the TX status from the
*        RF test.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
* \param[out] pvQueryBuf A pointer to the buffer that holds the result of
*                           the query.
* \param[in] u4QueryBufLen The length of the query buffer.
* \param[out] pu4QueryInfoLen If the call is successful, returns the number of
*                            bytes written into the query buffer. If the call
*                            failed due to invalid length of the query buffer,
*                            returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_LENGTH
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidQueryRfTestTxStatus (
    IN  P_ADAPTER_T  prAdapter,
    IN  PVOID        pvQueryBuffer,
    IN  UINT_32      u4QueryBufferLen,
    OUT PUINT_32     pu4QueryInfoLen
    )
{
    P_PARAM_CUSTOM_RFTEST_TX_STATUS_STRUC_T prTxStatus;
    P_TX_CTRL_T                 prTxCtrl;
    P_RFTEST_SETTING_STRUC_T    prSetting;
    ALC_VAL                     rAlcVal;

    DEBUGFUNC("wlanoidQueryRfTestTxStatus");


    ASSERT(prAdapter);
    ASSERT(pu4QueryInfoLen);

    prTxCtrl= &prAdapter->rTxCtrl;
    prSetting = &prAdapter->rRFTestInfo.rSetting;
    *pu4QueryInfoLen = sizeof(PARAM_CUSTOM_RFTEST_TX_STATUS_STRUC_T);

    /* Check for query buffer length */
    if (u4QueryBufferLen < *pu4QueryInfoLen) {
        DBGLOG(REQ, WARN, ("Invalid length %ld\n", u4QueryBufferLen));
        return WLAN_STATUS_INVALID_LENGTH;
    }

    ASSERT(pvQueryBuffer);
    prTxStatus = (P_PARAM_CUSTOM_RFTEST_TX_STATUS_STRUC_T) pvQueryBuffer;

    /* Query from interrupt result */
    prTxStatus->u4PktSentCount = (UINT_32)prTxCtrl->au8Statistics[TX_MPDU_TOTAL_COUNT];
    prTxStatus->u4PktSentStatus = (UINT_32)prTxCtrl->au8Statistics[TX_MPDU_OK_COUNT];
    if(prSetting->fgALCEn) {
        NIC_ALC_GET_CAL_VALUE(prAdapter, &rAlcVal);
        prTxStatus->u2AvgAlc = rAlcVal;
    }
    else{
        prTxStatus->u2AvgAlc = 0 ;
    }
    if ( prSetting->ucTxRate <= RF_AT_PARAM_RATE_11M ) {
        prTxStatus->ucCckGainControl = prSetting->ucTxPowerGain;
        prTxStatus->ucOfdmGainControl = 0;
    }
    else {
        prTxStatus->ucCckGainControl = 0;
        prTxStatus->ucOfdmGainControl = prSetting->ucTxPowerGain;
    }

    DBGLOG(REQ, INFO, ("pktSentCount = %ld\n", prTxStatus->u4PktSentCount));
    return WLAN_STATUS_SUCCESS;
}   /* rftestQueryTestRxStatus */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to query the number of the successfully transmitted
*        packets.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
* \param[out] pvQueryBuf A pointer to the buffer that holds the result of
*                           the query.
* \param[in] u4QueryBufLen The length of the query buffer.
* \param[out] pu4QueryInfoLen If the call is successful, returns the number of
*                            bytes written into the query buffer. If the call
*                            failed due to invalid length of the query buffer,
*                            returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_LENGTH
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidQueryXmitOk (
    IN  P_ADAPTER_T prAdapter,
    IN  PVOID       pvQueryBuffer,
    IN  UINT_32     u4QueryBufferLen,
    OUT PUINT_32    pu4QueryInfoLen
    )
{
    P_TX_CTRL_T     prTxCtrl;
    WLAN_STATUS     rStatus = WLAN_STATUS_SUCCESS;

    DEBUGFUNC("wlanoidQueryXmitOk");
    DBGLOG(REQ, TRACE, ("\n"));

    ASSERT(prAdapter);
    ASSERT(pu4QueryInfoLen);

    if (u4QueryBufferLen < sizeof(UINT_32)) {
        *pu4QueryInfoLen = sizeof(UINT_64);
        return WLAN_STATUS_INVALID_LENGTH;
    }

    if (pvQueryBuffer == NULL) {
        ASSERT(FALSE);
        return WLAN_STATUS_INVALID_LENGTH;
    }

    prTxCtrl = &prAdapter->rTxCtrl;
    if (u4QueryBufferLen == sizeof(UINT_32)) {
        /* Return a 32-bit counter. */
        *(PUINT_32) pvQueryBuffer = (UINT_32) prTxCtrl->au8Statistics[TX_MPDU_OK_COUNT];

        DBGLOG(REQ, LOUD, ("Tx OK: %ld\n", *(PUINT_32) pvQueryBuffer));
    }
    else if (u4QueryBufferLen < sizeof(UINT_64)) {
        /* Not enough room for the query information. */
        rStatus = WLAN_STATUS_INVALID_LENGTH;
    }
    else {
        /* Return a 64-bit counter. */
        *(PUINT_64) pvQueryBuffer =  prTxCtrl->au8Statistics[TX_MPDU_OK_COUNT];

        DBGLOG(REQ, LOUD, ("Tx OK: %"DBG_PRINTF_64BIT_DEC"\n", *(PUINT_64) pvQueryBuffer));
    }
    *pu4QueryInfoLen = sizeof(UINT_64);


    return rStatus;
}   /* wlanoidQueryXmitOk */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to query the number of the successfully received
*        packets.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
* \param[out] pvQueryBuf A pointer to the buffer that holds the result of
*                           the query.
* \param[in] u4QueryBufLen The length of the query buffer.
* \param[out] pu4QueryInfoLen If the call is successful, returns the number of
*                            bytes written into the query buffer. If the call
*                            failed due to invalid length of the query buffer,
*                            returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_LENGTH
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidQueryRcvOk (
    IN  P_ADAPTER_T     prAdapter,
    IN  PVOID           pvQueryBuffer,
    IN  UINT_32         u4QueryBufferLen,
    OUT PUINT_32        pu4QueryInfoLen
    )
{
    P_RX_CTRL_T     prRxCtrl;
    WLAN_STATUS     rStatus = WLAN_STATUS_SUCCESS;

    DEBUGFUNC("wlanoidQueryRcvOk");
    DBGLOG(REQ, TRACE, ("\n"));

    ASSERT(prAdapter);
    ASSERT(pu4QueryInfoLen);

    if (u4QueryBufferLen < sizeof(UINT_32)) {
        *pu4QueryInfoLen = sizeof(UINT_64);
        return WLAN_STATUS_INVALID_LENGTH;
    }

    if (pvQueryBuffer == NULL) {
        ASSERT(FALSE);
        return WLAN_STATUS_INVALID_LENGTH;
    }

    prRxCtrl = &prAdapter->rRxCtrl;
    if (u4QueryBufferLen == sizeof(UINT_32)) {
        /* Return a 32-bit counter. */
        *(PUINT_32) pvQueryBuffer = (UINT_32) prRxCtrl->au8Statistics[RX_DATA_INDICATION_COUNT];
        DBGLOG(REQ, LOUD, ("Rx OK: %ld\n", *(PUINT_32) pvQueryBuffer));
    }
    else if (u4QueryBufferLen < sizeof(UINT_64)) {
        /* Not enough room for the query information. */
        rStatus = WLAN_STATUS_INVALID_LENGTH;
    }
    else {
        /* Return a 64-bit counter. */
        *(PUINT_64) pvQueryBuffer =  prRxCtrl->au8Statistics[RX_DATA_INDICATION_COUNT];
        DBGLOG(REQ, LOUD, ("Rx OK: %"DBG_PRINTF_64BIT_DEC"\n", *(PUINT_64) pvQueryBuffer));
    }

    *pu4QueryInfoLen = sizeof(UINT_64);

    return rStatus;
}   /* wlanoidQueryRcvOk */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to query the number of frames that the driver
*        fails to transmit.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
* \param[out] pvQueryBuf A pointer to the buffer that holds the result of
*                           the query.
* \param[in] u4QueryBufLen The length of the query buffer.
* \param[out] pu4QueryInfoLen If the call is successful, returns the number of
*                            bytes written into the query buffer. If the call
*                            failed due to invalid length of the query buffer,
*                            returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_LENGTH
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidQueryXmitError (
    IN  P_ADAPTER_T     prAdapter,
    IN  PVOID           pvQueryBuffer,
    IN  UINT_32         u4QueryBufferLen,
    OUT PUINT_32        pu4QueryInfoLen
    )
{
    P_TX_CTRL_T     prTxCtrl;
    WLAN_STATUS     rStatus = WLAN_STATUS_SUCCESS;

    DEBUGFUNC("wlanoidQueryXmitError");
    DBGLOG(REQ, TRACE, ("\n"));

    ASSERT(prAdapter);
    ASSERT(pu4QueryInfoLen);

    prTxCtrl = &prAdapter->rTxCtrl;

    if (u4QueryBufferLen < sizeof(UINT_32)) {
        *pu4QueryInfoLen = sizeof(UINT_32);
        return WLAN_STATUS_INVALID_LENGTH;
    }

    if (pvQueryBuffer == NULL) {
        ASSERT(FALSE);
        return WLAN_STATUS_INVALID_LENGTH;
    }

    if (u4QueryBufferLen == sizeof(UINT_32)) {
        /* Return a 32-bit counter. */
        *(PUINT_32)pvQueryBuffer = (UINT_32)prTxCtrl->au8Statistics[TX_MPDU_ALL_ERR_COUNT];

        DBGLOG(REQ, LOUD, ("Tx Error: %ld\n", *(PUINT_32)pvQueryBuffer));
    }
    else if (u4QueryBufferLen < sizeof(UINT_64)) {
        /* Not enough room for the query information. */
       rStatus = WLAN_STATUS_INVALID_LENGTH;
    }
    else {
        /* Return a 64-bit counter. */
        *(PUINT_64)pvQueryBuffer = prTxCtrl->au8Statistics[TX_MPDU_ALL_ERR_COUNT];

        DBGLOG(REQ, LOUD, ("Tx Error: %"DBG_PRINTF_64BIT_DEC"\n", *(PUINT_64)pvQueryBuffer));
    }

    *pu4QueryInfoLen = sizeof(UINT_64);

    return rStatus;
} /* wlanoidQueryXmitError */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to query the number of frames successfully
*        transmitted after exactly one collision.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[out] pvQueryBuf A pointer to the buffer that holds the result of
*                           the query.
* \param[in] u4QueryBufLen The length of the query buffer.
* \param[out] pu4QueryInfoLen If the call is successful, returns the number of
*                            bytes written into the query buffer. If the call
*                            failed due to invalid length of the query buffer,
*                            returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_LENGTH
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidQueryXmitOneCollision (
    IN  P_ADAPTER_T     prAdapter,
    IN  PVOID           pvQueryBuffer,
    IN  UINT_32         u4QueryBufferLen,
    OUT PUINT_32        pu4QueryInfoLen
    )
{
    P_TX_CTRL_T     prTxCtrl;
    WLAN_STATUS     rStatus = WLAN_STATUS_SUCCESS;

    DEBUGFUNC("wlanoidQueryXmitOneCollision");
    DBGLOG(REQ, TRACE, ("\n"));

    ASSERT(prAdapter);
    ASSERT(pu4QueryInfoLen);

    prTxCtrl = &prAdapter->rTxCtrl;

    if (u4QueryBufferLen < sizeof(UINT_32)) {
        *pu4QueryInfoLen = sizeof(UINT_32);
        return WLAN_STATUS_INVALID_LENGTH;
    }

    if (pvQueryBuffer == NULL) {
        ASSERT(FALSE);
        return WLAN_STATUS_INVALID_LENGTH;
    }

    if (u4QueryBufferLen == sizeof(UINT_32)) {
        /* Return a 32-bit counter. */
        *(PUINT_32)pvQueryBuffer = (UINT_32)prTxCtrl->au8Statistics[TX_MPDU_TX_TWICE_OK_COUNT];

        DBGLOG(REQ, LOUD, ("Tx one retry and get ACK: %ld\n", *(PUINT_32)pvQueryBuffer));
    }
    else if (u4QueryBufferLen < sizeof(UINT_64)) {
        /* Not enough room for the query information. */
       rStatus = WLAN_STATUS_INVALID_LENGTH;
    }
    else {
        /* Return a 64-bit counter. */
        *(PUINT_64)pvQueryBuffer = prTxCtrl->au8Statistics[TX_MPDU_TX_TWICE_OK_COUNT];

        DBGLOG(REQ, LOUD, ("Tx one retry and get ACK: %"DBG_PRINTF_64BIT_DEC"\n", *(PUINT_64)pvQueryBuffer));
    }

    *pu4QueryInfoLen = sizeof(UINT_64);
    return rStatus;

} /* wlanoidQueryXmitOneCollision */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to query the number of frames successfully
*        transmitted after more than one collision.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[out] pvQueryBuf A pointer to the buffer that holds the result of
*                           the query.
* \param[in] u4QueryBufLen The length of the query buffer.
* \param[out] pu4QueryInfoLen If the call is successful, returns the number of
*                            bytes written into the query buffer. If the call
*                            failed due to invalid length of the query buffer,
*                            returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_LENGTH
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidQueryXmitMoreCollisions (
    IN  P_ADAPTER_T     prAdapter,
    IN  PVOID           pvQueryBuffer,
    IN  UINT_32         u4QueryBufferLen,
    OUT PUINT_32        pu4QueryInfoLen
    )
{
    P_TX_CTRL_T     prTxCtrl;
    WLAN_STATUS     rStatus = WLAN_STATUS_SUCCESS;

    DEBUGFUNC("wlanoidQueryXmitMoreCollisions");
    DBGLOG(REQ, TRACE, ("\n"));

    ASSERT(prAdapter);
    ASSERT(pu4QueryInfoLen);

    prTxCtrl = &prAdapter->rTxCtrl;

    if (u4QueryBufferLen < sizeof(UINT_32)) {
        *pu4QueryInfoLen = sizeof(UINT_32);
        return WLAN_STATUS_INVALID_LENGTH;
    }

    if (pvQueryBuffer == NULL) {
        ASSERT(FALSE);
        return WLAN_STATUS_INVALID_LENGTH;
    }

    if (u4QueryBufferLen == sizeof(UINT_32)) {
        /* Return a 32-bit counter. */
        *(PUINT_32)pvQueryBuffer = (UINT_32)prTxCtrl->au8Statistics[TX_MPDU_TX_MORE_TWICE_OK_COUNT];

        DBGLOG(REQ, LOUD, ("Tx more than 2 retry and get ACK: %ld\n", *(PUINT_32)pvQueryBuffer));
    }
    else if (u4QueryBufferLen < sizeof(UINT_64)) {
        /* Not enough room for the query information. */
       rStatus = WLAN_STATUS_INVALID_LENGTH;
    }
    else {
        /* Return a 64-bit counter. */
        *(PUINT_64)pvQueryBuffer = prTxCtrl->au8Statistics[TX_MPDU_TX_MORE_TWICE_OK_COUNT];

        DBGLOG(REQ, LOUD, ("Tx more than 2 retry and get ACK: %"DBG_PRINTF_64BIT_DEC"\n", *(PUINT_64)pvQueryBuffer));
    }

    *pu4QueryInfoLen = sizeof(UINT_64);
    return rStatus;

} /* wlanoidQueryXmitMoreCollisions */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to query the number of frames
*                not transmitted due to excessive collisions.
*
* \param[in] prAdapter          Pointer to the Adapter structure.
* \param[in] pvQueryBuffer      Pointer to the buffer that holds the result of
*                               the query.
* \param[in] u4QueryBufferLen   The length of the query buffer.
* \param[out] pu4QueryInfoLen   If the call is successful, returns the number of
*                               bytes written into the query buffer. If the call
*                               failed due to invalid length of the query buffer,
*                               returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_LENGTH
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidQueryXmitMaxCollisions (
    IN   P_ADAPTER_T     prAdapter,
    IN   PVOID           pvQueryBuffer,
    IN   UINT_32         u4QueryBufferLen,
    OUT  PUINT_32        pu4QueryInfoLen
    )
{
    P_TX_CTRL_T     prTxCtrl;
    WLAN_STATUS     rStatus = WLAN_STATUS_SUCCESS;

    DEBUGFUNC("wlanoidQueryXmitMaxCollisions");
    DBGLOG(REQ, TRACE, ("\n"));

    ASSERT(prAdapter);
    ASSERT(pu4QueryInfoLen);

    prTxCtrl = &prAdapter->rTxCtrl;

    if (u4QueryBufferLen < sizeof(UINT_32)) {
        *pu4QueryInfoLen = sizeof(UINT_32);
        return WLAN_STATUS_INVALID_LENGTH;
    }

    if (pvQueryBuffer == NULL) {
        ASSERT(FALSE);
        return WLAN_STATUS_INVALID_LENGTH;
    }

    if (u4QueryBufferLen == sizeof(UINT_32)) {
        /* Return a 32-bit counter. */
        *(PUINT_32)pvQueryBuffer = (UINT_32)prTxCtrl->au8Statistics[TX_MPDU_MPDU_EXCESS_RETRY_ERR_COUNT];

        DBGLOG(REQ, LOUD, ("Tx max collisions and abort: %ld\n", *(PUINT_32)pvQueryBuffer));
    }
    else if (u4QueryBufferLen < sizeof(UINT_64)) {
        /* Not enough room for the query information. */
       rStatus = WLAN_STATUS_INVALID_LENGTH;
    }
    else {
        /* Return a 64-bit counter. */
        *(PUINT_64)pvQueryBuffer = prTxCtrl->au8Statistics[TX_MPDU_MPDU_EXCESS_RETRY_ERR_COUNT];

        DBGLOG(REQ, LOUD, ("Tx max collisions and abort: %"DBG_PRINTF_64BIT_DEC"\n", *(PUINT_64)pvQueryBuffer));
    }

    *pu4QueryInfoLen = sizeof(UINT_64);
    return rStatus;
}   /* wlanoidQueryXmitMaxCollisions */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to query current the OID interface version,
*        which is the interface between the application and driver.
*
* \param[in] prAdapter          Pointer to the Adapter structure.
* \param[in] pvQueryBuffer      Pointer to the buffer that holds the result of
*                               the query.
* \param[in] u4QueryBufferLen   The length of the query buffer.
* \param[out] pu4QueryInfoLen   If the call is successful, returns the number of
*                               bytes written into the query buffer. If the call
*                               failed due to invalid length of the query buffer,
*                               returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidQueryOidInterfaceVersion (
    IN P_ADAPTER_T  prAdapter,
    IN  PVOID    pvQueryBuffer,
    IN  UINT_32  u4QueryBufferLen,
    OUT PUINT_32 pu4QueryInfoLen)
{
    DEBUGFUNC("wlanoidQueryOidInterfaceVersion");


    ASSERT(prAdapter);
    ASSERT(pvQueryBuffer);
    ASSERT(pu4QueryInfoLen);

    *(PUINT_32) pvQueryBuffer = MTK_CUSTOM_OID_INTERFACE_VERSION ;
    *pu4QueryInfoLen = sizeof(UINT_32);

    DBGLOG(REQ, INFO, ("Custom OID interface version: %#08lX\n",
        *(PUINT_32) pvQueryBuffer));

    return WLAN_STATUS_SUCCESS;
}   /* wlanoidQueryOidInterfaceVersion */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to query current Multicast Address List.
*
* \param[in] prAdapter          Pointer to the Adapter structure.
* \param[in] pvQueryBuffer      Pointer to the buffer that holds the result of
*                               the query.
* \param[in] u4QueryBufferLen   The length of the query buffer.
* \param[out] pu4QueryInfoLen   If the call is successful, returns the number of
*                               bytes written into the query buffer. If the call
*                               failed due to invalid length of the query buffer,
*                               returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_BUFFER_TOO_SHORT
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidQueryMulticastList(
    IN  P_ADAPTER_T prAdapter,
    OUT PVOID       pvQueryBuffer,
    IN  UINT_32     u4QueryBufferLen,
    OUT PUINT_32    pu4QueryInfoLen
    )
{
    ASSERT(prAdapter);
    ASSERT(pu4QueryInfoLen);

    ASSERT(prAdapter->ucMulticastAddrNum <= MAX_NUM_GROUP_ADDR);

    *pu4QueryInfoLen = (UINT_32)prAdapter->ucMulticastAddrNum * MAC_ADDR_LEN;

    /* Check if the query buffer is large enough to hold all the query
       information. */
    if (u4QueryBufferLen < *pu4QueryInfoLen) {
        /* Not enough room for the query information. */
        return WLAN_STATUS_BUFFER_TOO_SHORT;
    }

    ASSERT(pvQueryBuffer);

    kalMemCopy(pvQueryBuffer,
               prAdapter->aucMulticastAddr,
               *pu4QueryInfoLen);

    return WLAN_STATUS_SUCCESS;

} /* end of wlanoidQueryMulticastList() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to set Multicast Address List.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
* \param[in] pvSetBuffer    Pointer to the buffer that holds the data to be set.
* \param[in] u4SetBufferLen The length of the set buffer.
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*                           bytes read from the set buffer. If the call failed
*                           due to invalid length of the set buffer, returns
*                           the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_LENGTH
* \retval WLAN_STATUS_ADAPTER_NOT_READY
* \retval WLAN_STATUS_MULTICAST_FULL
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidSetMulticastList(
    IN  P_ADAPTER_T prAdapter,
    IN  PVOID       pvSetBuffer,
    IN  UINT_32     u4SetBufferLen,
    OUT PUINT_32    pu4SetInfoLen
    )
{
    ASSERT(prAdapter);
    ASSERT(pu4SetInfoLen);

    /* The data must be a multiple of the Ethernet address size. */
    if (u4SetBufferLen % MAC_ADDR_LEN != 0) {
        DBGLOG(REQ, WARN, ("Invalid MC list length %ld\n", u4SetBufferLen));

        *pu4SetInfoLen = ((u4SetBufferLen + MAC_ADDR_LEN - 1) /
            MAC_ADDR_LEN) * MAC_ADDR_LEN;

        return WLAN_STATUS_INVALID_LENGTH;
    }

    *pu4SetInfoLen = u4SetBufferLen;

    /* Verify if we can support so many multicast addresses. */
    if (u4SetBufferLen / MAC_ADDR_LEN > MAX_NUM_GROUP_ADDR) {
        DBGLOG(REQ, WARN, ("Too many MC addresses\n"));

        return WLAN_STATUS_MULTICAST_FULL;
    }

    /* NOTE(Kevin): Windows may set u4SetBufferLen == 0 &&
     * pvSetBuffer == NULL to clear exist Multicast List.
     */
    if (u4SetBufferLen) {
        ASSERT(pvSetBuffer);
    }

    if (IS_ARB_IN_RFTEST_STATE(prAdapter)) {
        return WLAN_STATUS_SUCCESS;
    }

    if (prAdapter->rAcpiState == ACPI_STATE_D3) {
        DBGLOG(REQ, WARN, ("Fail in set multicast list! (Adapter not ready). ACPI=D%d, Radio=%d\n",
                    prAdapter->rAcpiState, prAdapter->fgIsRadioOff));
        return WLAN_STATUS_ADAPTER_NOT_READY;
    }

    nicRxSetMulticast(prAdapter,
                      MC_TYPE_UPDATE_LIST_ONLY,
                      pvSetBuffer,
                      (UINT_8)(u4SetBufferLen / MAC_ADDR_LEN));

    return WLAN_STATUS_SUCCESS;

} /* end of wlanoidSetMulticastList() */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to set Packet Filter.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
* \param[in] pvSetBuffer    Pointer to the buffer that holds the data to be set.
* \param[in] u4SetBufferLen The length of the set buffer.
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*                           bytes read from the set buffer. If the call failed
*                           due to invalid length of the set buffer, returns
*                           the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_LENGTH
* \retval WLAN_STATUS_NOT_SUPPORTED
* \retval WLAN_STATUS_ADAPTER_NOT_READY
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidSetCurrentPacketFilter (
    IN P_ADAPTER_T  prAdapter,
    IN  PVOID    pvSetBuffer,
    IN  UINT_32  u4SetBufferLen,
    OUT PUINT_32 pu4SetInfoLen
    )
{
    UINT_32 u4NewPacketFilter;
    //UINT_32 u4FilterChanges;
    WLAN_STATUS rStatus = WLAN_STATUS_SUCCESS;

    DEBUGFUNC("wlanoidSetCurrentPacketFilter");

    ASSERT(prAdapter);
    ASSERT(pu4SetInfoLen);

    *pu4SetInfoLen = sizeof(UINT_32);

    if (u4SetBufferLen < sizeof(UINT_32)) {
        return WLAN_STATUS_INVALID_LENGTH;
    }
    ASSERT(pvSetBuffer);

    /* Set the new packet filter. */
    u4NewPacketFilter = *(PUINT_32) pvSetBuffer;

    DBGLOG(REQ, INFO, ("New packet filter: %#08lx\n", u4NewPacketFilter));

    if (IS_ARB_IN_RFTEST_STATE(prAdapter)) {
        return WLAN_STATUS_SUCCESS;
    }

    if (prAdapter->rAcpiState == ACPI_STATE_D3) {
        DBGLOG(REQ, WARN, ("Fail in set current packet filter! (Adapter not ready). ACPI=D%d, Radio=%d\n",
                    prAdapter->rAcpiState, prAdapter->fgIsRadioOff));
        return WLAN_STATUS_ADAPTER_NOT_READY;
    }

    do {
        /* Verify the bits of the new packet filter. If any bits are set that
           we don't support, leave. */
        if (u4NewPacketFilter & ~(PARAM_PACKET_FILTER_SUPPORTED)) {
            DBGLOG(RSN, WARN, ("Filter Type %#08lx not supported\n", u4NewPacketFilter));
            rStatus = WLAN_STATUS_NOT_SUPPORTED;
            break;
        }

        /* Need to enable or disable promiscuous support depending on the new
           filter. */

        if (u4NewPacketFilter & PARAM_PACKET_FILTER_PROMISCUOUS) {
            DBGLOG(REQ, INFO, ("Enable promiscuous mode\n"));
            //4 2007/11/27, mikewu, <<TODO>> Enable Promiscuous mode
            wlanSetPromiscuousMode(prAdapter, TRUE);
        }
        else {
            DBGLOG(REQ, INFO, ("Disable promiscuous mode\n"));
            //4 2007/11/27, mikewu, <<TODO>> Disable Promiscuous mode
            wlanSetPromiscuousMode(prAdapter, FALSE);
        }

        if (u4NewPacketFilter & PARAM_PACKET_FILTER_ALL_MULTICAST) {
            DBGLOG(REQ, INFO, ("Enable all-multicast mode\n"));
            //4 2007/11/27, mikewu, <<TODO>> Enable all multicast mode
            nicRxSetMulticast(prAdapter, MC_TYPE_ALLOW_ALL, (PUINT_8)NULL, 0);
        }
        else if (u4NewPacketFilter & PARAM_PACKET_FILTER_MULTICAST) {
            DBGLOG(REQ, INFO, ("Enable multicast\n"));

            /* Set multicast address table by calling regChangeMCAddress. */
            //4 2007/11/27, mikewu, <<TODO>>Check MC address list
            /* NOTE(Kevin): it also clear the Multicast List */
            nicRxSetMulticast(prAdapter, MC_TYPE_ALLOW_LIST, (PUINT_8)NULL, 0);
        }
        else {
            DBGLOG(REQ, INFO, ("Disable multicast\n"));
            //4 2007/11/27, mikewu, <<TODO>> Disable multicast
            nicRxSetMulticast(prAdapter, MC_TYPE_DENY_ALL, (PUINT_8)NULL, 0);
        }

        if (u4NewPacketFilter & PARAM_PACKET_FILTER_BROADCAST) {
            DBGLOG(REQ, INFO, ("Enable Broadcast\n"));
            //4 2007/11/27, mikewu, <<TODO>> Enable Broadcast
            wlanRxSetBroadcast(prAdapter, TRUE);
        }
        else {
            DBGLOG(REQ, INFO, ("Disable Broadcast\n"));
            //4 2007/11/27, mikewu, <<TODO>> Disable Broadcast
            wlanRxSetBroadcast(prAdapter, FALSE);
        }

    } while (FALSE);

    // Store the packet filter
    prAdapter->u4OsPacketFilter = u4NewPacketFilter;

    return rStatus;
}   /* wlanoidSetCurrentPacketFilter */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to query current packet filter.
*
* \param[in] prAdapter          Pointer to the Adapter structure.
* \param[in] pvQueryBuffer      Pointer to the buffer that holds the result of
*                               the query.
* \param[in] u4QueryBufferLen   The length of the query buffer.
* \param[out] pu4QueryInfoLen   If the call is successful, returns the number of
*                               bytes written into the query buffer. If the call
*                               failed due to invalid length of the query buffer,
*                               returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidQueryCurrentPacketFilter (
    IN P_ADAPTER_T  prAdapter,
    OUT PVOID       pvQueryBuffer,
    IN  UINT_32     u4QueryBufferLen,
    OUT PUINT_32    pu4QueryInfoLen
    )
{
    DEBUGFUNC("wlanoidQueryCurrentPacketFilter");
    ASSERT(prAdapter);
    ASSERT(pu4QueryInfoLen);

    *pu4QueryInfoLen = sizeof(UINT_32);

    if (u4QueryBufferLen >= sizeof(UINT_32)) {
        ASSERT(pvQueryBuffer);
        *(PUINT_32) pvQueryBuffer = prAdapter->u4OsPacketFilter;
    }

    return WLAN_STATUS_SUCCESS;
}   /* wlanoidQueryCurrentPacketFilter */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to query device ACPI power capability instead of
*   state.
*
* \param[in] prAdapter          Pointer to the Adapter structure.
* \param[in] pvQueryBuffer      Pointer to the buffer that holds the result of
*                               the query.
* \param[in] u4QueryBufferLen   The length of the query buffer.
* \param[out] pu4QueryInfoLen   If the call is successful, returns the number of
*                               bytes written into the query buffer. If the call
*                               failed due to invalid length of the query buffer,
*                               returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidQueryAcpiDevicePowerState (
    IN P_ADAPTER_T prAdapter,
    IN  PVOID       pvQueryBuffer,
    IN  UINT_32     u4QueryBufferLen,
    OUT PUINT_32    pu4QueryInfoLen
    )
{
#if DBG
    PPARAM_DEVICE_POWER_STATE prPowerState;
#endif

    DEBUGFUNC("wlanoidQueryAcpiDevicePowerState");
    ASSERT(prAdapter);
    ASSERT(pu4QueryInfoLen);

    *pu4QueryInfoLen = sizeof(PARAM_DEVICE_POWER_STATE);

    ASSERT(pvQueryBuffer);
#if DBG
    prPowerState = (PPARAM_DEVICE_POWER_STATE) pvQueryBuffer;
    switch (*prPowerState) {
    case ParamDeviceStateD0:
        DBGLOG(REQ, INFO, ("Query Power State: D0\n"));
        break;
    case ParamDeviceStateD1:
        DBGLOG(REQ, INFO, ("Query Power State: D1\n"));
        break;
    case ParamDeviceStateD2:
        DBGLOG(REQ, INFO, ("Query Power State: D2\n"));
        break;
    case ParamDeviceStateD3:
        DBGLOG(REQ, INFO, ("Query Power State: D3\n"));
        break;
    default:
        break;
    }
#endif

    *(PPARAM_DEVICE_POWER_STATE) pvQueryBuffer = ParamDeviceStateD3;
    DBGLOG(REQ, INFO, ("Ready to transition to D3\n"));

    return WLAN_STATUS_SUCCESS;
}   /* wlanoidQueryAcpiDevicePowerState */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to set ACPI device power state.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
* \param[in] pvSetBuffer A pointer to the buffer that holds the data to be set.
* \param[in] u4SetBufferLen The length of the set buffer.
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*                          bytes read from the set buffer. If the call failed
*                          due to invalid length of the set buffer, returns
*                          the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidSetAcpiDevicePowerState (
    IN P_ADAPTER_T prAdapter,
    IN  PVOID    pvSetBuffer,
    IN  UINT_32  u4SetBufferLen,
    OUT PUINT_32 pu4SetInfoLen
    )
{
    PPARAM_DEVICE_POWER_STATE prPowerState;

    DEBUGFUNC("wlanoidSetAcpiDevicePowerState");
    ASSERT(prAdapter);
    ASSERT(pu4SetInfoLen);

    *pu4SetInfoLen = sizeof(PARAM_DEVICE_POWER_STATE);

    ASSERT(pvSetBuffer);
    prPowerState = (PPARAM_DEVICE_POWER_STATE) pvSetBuffer;
    switch (*prPowerState) {
    case ParamDeviceStateD0:
        DBGLOG(REQ, INFO, ("Set Power State: D0\n"));
        kalDevSetPowerState(prAdapter->prGlueInfo, (UINT_32)ParamDeviceStateD0);
        pmSetAcpiPowerD0(prAdapter);
        break;
    case ParamDeviceStateD1:
        DBGLOG(REQ, INFO, ("Set Power State: D1\n"));
        /* no break here */
    case ParamDeviceStateD2:
        DBGLOG(REQ, INFO, ("Set Power State: D2\n"));
        /* no break here */
    case ParamDeviceStateD3:
        DBGLOG(REQ, INFO, ("Set Power State: D3\n"));
        pmSetAcpiPowerD3(prAdapter);
        kalDevSetPowerState(prAdapter->prGlueInfo, (UINT_32)ParamDeviceStateD3);
#if !defined(WINDOWS_DDK)
        /* CR01858: set flag to FALSE to avoid automatic reconnection after
        * switching from D3 to D0 state.
        */
        DBGLOG(REQ, INFO, ("Clear fgIsConnReqIssued\n"));
        prAdapter->rConnSettings.fgIsConnReqIssued = FALSE;
        //DBGLOG(REQ, INFO, ("Set fgScanListPending = TRUE\n"));
        //prAdapter->prGlueInfo->fgScanListPending = TRUE;
        //prAdapter->rScanInfo->fgFullScanDone = FALSE;
#endif
        break;
    default:
        break;
    }

    return WLAN_STATUS_SUCCESS;
} /* end of wlanoidSetAcpiDevicePowerState() */



/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to query the current fragmentation threshold.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
* \param[out] pvQueryBuffer A pointer to the buffer that holds the result of
*                           the query.
* \param[in] u4QueryBufferLen The length of the query buffer.
* \param[out] pu4QueryInfoLen If the call is successful, returns the number of
*                            bytes written into the query buffer. If the call
*                            failed due to invalid length of the query buffer,
*                            returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_BUFFER_TOO_SHORT
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidQueryFragThreshold (
    IN  P_ADAPTER_T prAdapter,
    OUT PVOID       pvQueryBuffer,
    IN  UINT_32     u4QueryBufferLen,
    OUT PUINT_32    pu4QueryInfoLen
    )
{
    DEBUGFUNC("wlanoidQueryFragThreshold");

    ASSERT(prAdapter);
    ASSERT(pvQueryBuffer);
    ASSERT(pu4QueryInfoLen);

    DBGLOG(REQ, INFO, ("\n"));

#if CFG_TX_FRAGMENT
    if (u4QueryBufferLen < sizeof(PARAM_FRAGMENTATION_THRESHOLD)) {
        *pu4QueryInfoLen = sizeof(PARAM_FRAGMENTATION_THRESHOLD);
        return WLAN_STATUS_BUFFER_TOO_SHORT;
    }

    *(PUINT_32)pvQueryBuffer = (UINT_32)prAdapter->rConnSettings.u2FragmentationThreshold;
    *pu4QueryInfoLen = sizeof(PARAM_FRAGMENTATION_THRESHOLD);

    DBGLOG(REQ, INFO, ("Current fragmentation threshold: %d\n",
        prAdapter->rConnSettings.u2FragmentationThreshold));

    return WLAN_STATUS_SUCCESS;

#else

    return WLAN_STATUS_NOT_SUPPORTED;
#endif /* CFG_TX_FRAGMENT */

} /* end of wlanoidQueryFragThreshold() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to set a new fragmentation threshold to the
*        driver.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
* \param[in] pvSetBuffer A pointer to the buffer that holds the data to be set.
* \param[in] u4SetBufferLen The length of the set buffer.
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*                          bytes read from the set buffer. If the call failed
*                          due to invalid length of the set buffer, returns
*                          the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_DATA
* \retval WLAN_STATUS_INVALID_LENGTH
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidSetFragThreshold (
    IN  P_ADAPTER_T prAdapter,
    IN  PVOID       pvSetBuffer,
    IN  UINT_32     u4SetBufferLen,
    OUT PUINT_32    pu4SetInfoLen
    )
{
#if CFG_TX_FRAGMENT
    P_CONNECTION_SETTINGS_T prConnSettings;
    UINT_32 u4NewFragThreshold;

    DEBUGFUNC("wlanoidSetFragThreshold");

    ASSERT(prAdapter);
    ASSERT(pvSetBuffer);
    ASSERT(pu4SetInfoLen);

    prConnSettings = &prAdapter->rConnSettings;

    if (IS_ARB_IN_RFTEST_STATE(prAdapter)) {
        return WLAN_STATUS_SUCCESS;
    }


    DBGLOG(REQ, INFO, ("\n"));

    if (u4SetBufferLen < sizeof(PARAM_FRAGMENTATION_THRESHOLD)) {
        *pu4SetInfoLen = sizeof(PARAM_FRAGMENTATION_THRESHOLD);
        return WLAN_STATUS_INVALID_LENGTH;
    }

    u4NewFragThreshold = *(PUINT_32)pvSetBuffer;
    *pu4SetInfoLen = sizeof(PARAM_FRAGMENTATION_THRESHOLD);


    /* Verify the new fragmentation threshold. */
    /* Zero means to disable fragmentation.
      Refer to OID_802_11_FRAGMENTATION_THRESHOLD
    */
    if ((u4NewFragThreshold != 0) &&
        ((u4NewFragThreshold < DOT11_FRAGMENTATION_THRESHOLD_MIN) ||
         (u4NewFragThreshold > DOT11_FRAGMENTATION_THRESHOLD_MAX) ||
         (u4NewFragThreshold & 0x01))) {

        DBGLOG(REQ, TRACE, ("Invalid fragmentation threshold %ld\n",
            u4NewFragThreshold));
        return WLAN_STATUS_INVALID_DATA;
    }

    /* Save the new fragmentation threshold to the MIB. */

    prConnSettings->u2FragmentationThreshold = (UINT_16)u4NewFragThreshold;

    if (prConnSettings->u2FragmentationThreshold) {
        prConnSettings->fgIsEnableTxFragment = TRUE;

        if (prAdapter->eConnectionState ==
            MEDIA_STATE_CONNECTED) {
            txFragInfoUpdate(prAdapter);
        }
    }
    else {
        prConnSettings->fgIsEnableTxFragment = FALSE;
        prConnSettings->fgIsEnableTxAutoFragmentForBT = FALSE;
    }

    return WLAN_STATUS_SUCCESS;

#else

    return WLAN_STATUS_NOT_SUPPORTED;
#endif /* CFG_TX_FRAGMENT */

} /* end of wlanoidSetFragThreshold() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to query the current RTS threshold.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
* \param[out] pvQueryBuffer A pointer to the buffer that holds the result of
*                           the query.
* \param[in] u4QueryBufferLen The length of the query buffer.
* \param[out] pu4QueryInfoLen If the call is successful, returns the number of
*                            bytes written into the query buffer. If the call
*                            failed due to invalid length of the query buffer,
*                            returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_BUFFER_TOO_SHORT
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidQueryRtsThreshold (
    IN  P_ADAPTER_T prAdapter,
    OUT PVOID       pvQueryBuffer,
    IN  UINT_32     u4QueryBufferLen,
    OUT PUINT_32    pu4QueryInfoLen
    )
{
    DEBUGFUNC("wlanoidQueryRtsThreshold");

    ASSERT(prAdapter);
    ASSERT(pvQueryBuffer);
    ASSERT(pu4QueryInfoLen);

    DBGLOG(REQ, INFO, ("\n"));

    if (u4QueryBufferLen < sizeof(PARAM_RTS_THRESHOLD)) {
        *pu4QueryInfoLen = sizeof(PARAM_RTS_THRESHOLD);
        return WLAN_STATUS_BUFFER_TOO_SHORT;
    }

    *(PUINT_32)pvQueryBuffer = (UINT_32)prAdapter->rConnSettings.u2RTSThreshold;
    *pu4QueryInfoLen = sizeof(PARAM_RTS_THRESHOLD);

    DBGLOG(REQ, INFO, ("Current RTS threshold: %d\n", prAdapter->rConnSettings.u2RTSThreshold));

    return WLAN_STATUS_SUCCESS;

} /* wlanoidQueryRtsThreshold */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to set a new RTS threshold to the driver.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
* \param[in] pvSetBuffer A pointer to the buffer that holds the data to be set.
* \param[in] u4SetBufferLen The length of the set buffer.
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*                          bytes read from the set buffer. If the call failed
*                          due to invalid length of the set buffer, returns
*                          the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_DATA
* \retval WLAN_STATUS_INVALID_LENGTH
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidSetRtsThreshold (
    IN  P_ADAPTER_T prAdapter,
    IN  PVOID       pvSetBuffer,
    IN  UINT_32     u4SetBufferLen,
    OUT PUINT_32    pu4SetInfoLen
    )
{
    UINT_16 u2NewRTSThreshold;

    DEBUGFUNC("wlanoidSetRtsThreshold");

    ASSERT(prAdapter);
    ASSERT(pvSetBuffer);
    ASSERT(pu4SetInfoLen);

    DBGLOG(REQ, INFO, ("\n"));

    *pu4SetInfoLen = sizeof(PARAM_RTS_THRESHOLD);

    if (u4SetBufferLen < sizeof(PARAM_RTS_THRESHOLD)) {
        return WLAN_STATUS_INVALID_LENGTH;
    }

    if (IS_ARB_IN_RFTEST_STATE(prAdapter)) {
        return WLAN_STATUS_SUCCESS;
    }

    u2NewRTSThreshold = (UINT_16)(*(PUINT_32)pvSetBuffer);

    /* Verify the new RTS threshold. */
    if (u2NewRTSThreshold > DOT11_RTS_THRESHOLD_MAX) {

        DBGLOG(REQ, TRACE, ("Invalid RTS threshold %d\n",
            u2NewRTSThreshold));
        return WLAN_STATUS_INVALID_DATA;
    }

    /* Save the new RTS threshold to the MIB. */
    prAdapter->rConnSettings.u2RTSThreshold = u2NewRTSThreshold;

    nicRateSetRTSThreshold(prAdapter, u2NewRTSThreshold);

    return WLAN_STATUS_SUCCESS;

} /* wlanoidSetRtsThreshold */


#if PTA_ENABLED
/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to get the PTA configuration data.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
* \param[in] pvSetBuffer A pointer to the buffer that holds the data to be set.
* \param[in] u4SetBufferLen The length of the set buffer.
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*                          bytes read from the set buffer. If the call failed
*                          due to invalid length of the set buffer, returns
*                          the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_LENGTH
* \retval WLAN_STATUS_INVALID_DATA
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidSetBtCoexistCtrl (
    IN  P_ADAPTER_T  prAdapter,
    IN  PVOID    pvSetBuffer,
    IN  UINT_32  u4SetBufferLen,
    OUT PUINT_32 pu4SetInfoLen
    )
{
    P_PARAM_CUSTOM_BT_COEXIST_T prBtSetting;
#if CFG_TX_FRAGMENT
    P_CONNECTION_SETTINGS_T     prConnSettings;
#endif /* CFG_TX_FRAGMENT */

    DEBUGFUNC("wlanoidSetBtCoexistCtrl");

    ASSERT(prAdapter);
    ASSERT(pu4SetInfoLen);

    *pu4SetInfoLen = sizeof(PARAM_CUSTOM_BT_COEXIST_T);

    if (u4SetBufferLen != sizeof(PARAM_CUSTOM_BT_COEXIST_T)) {
        return WLAN_STATUS_INVALID_LENGTH;
    }
    ASSERT(pvSetBuffer);
    prBtSetting = (P_PARAM_CUSTOM_BT_COEXIST_T) pvSetBuffer;

#if CFG_TX_FRAGMENT
    prConnSettings = &prAdapter->rConnSettings;
    if (prBtSetting->eBTCoexistWindowType >= BT_COEXIST_WINDOW_TYPE_NUM) {
        return WLAN_STATUS_INVALID_DATA;
    }
#endif /* CFG_TX_FRAGMENT */

    if (IS_ARB_IN_RFTEST_STATE(prAdapter)) {
        return WLAN_STATUS_SUCCESS;
    }

    if (prAdapter->rAcpiState == ACPI_STATE_D3) {
        DBGLOG(REQ, WARN, ("Fail to set BT setting because of ACPI_D3\n"));
        return WLAN_STATUS_ADAPTER_NOT_READY;
    }

    /* Store parameters to connSetting for chip reset path */
    kalMemCopy((PVOID) &prAdapter->rConnSettings.rPtaParam,
            &prBtSetting->rPtaParam, sizeof(PTA_PARAM_T));

    ptaFsmRunEventSetConfig(prAdapter, &prBtSetting->rPtaParam);

#if CFG_TX_FRAGMENT
    /* Judge if TX auto-fragment is applied for BT-coexist after
     * ptaFsmRunEventSetConfig() or ptaFsmInit() is invoked
     */
    prConnSettings->fgTryTxAutoFragmentForBT =
            prBtSetting->u4IsEnableTxAutoFragmentForBT ? TRUE : FALSE;
    prConnSettings->eBTCoexistWindowType =
        (ENUM_PARAM_BT_COEXIST_WINDOW_T) prBtSetting->eBTCoexistWindowType;

    prConnSettings->fgIsEnableTxAutoFragmentForBT =
            (prConnSettings->fgIsEnableTxFragment &&
             prAdapter->rPtaInfo.eCurrentState == PTA_STATE_ON) ?
            prConnSettings->fgTryTxAutoFragmentForBT : FALSE;
#endif /* CFG_TX_FRAGMENT */

    return WLAN_STATUS_SUCCESS;

} /* wlanoidSetBtCoexistCtrl */
#endif /* end of PTA_ENABLED */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to do ADDTS request, with supply the TSPEC info..
*
* \param[in] pvAdapter Pointer to the Adapter structure.
* \param[in] pvSetBuffer A pointer to the buffer that holds the data to be set.
* \param[in] u4SetBufferLen The length of the set buffer.
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*                          bytes read from the set buffer. If the call failed
*                          due to invalid length of the set buffer, returns
*                          the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidAddTS (
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID             pvSetBuffer,
    IN  UINT_32           u4SetBufferLen,
    OUT PUINT_32          pu4SetInfoLen
    )
{
    ASSERT(prAdapter);

    if (prAdapter->rAcpiState == ACPI_STATE_D3) {
        DBGLOG(REQ, WARN, ("Fail in Add TS! (Adapter not ready). ACPI=D%d, Radio=%d\n",
                    prAdapter->rAcpiState, prAdapter->fgIsRadioOff));
        return WLAN_STATUS_ADAPTER_NOT_READY;
    }

    // NOT IMPLEMENTED YET!
    ASSERT(0);

    return WLAN_STATUS_SUCCESS;

}   /* wlanoidAddTS */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to do DELTS request.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
* \param[in] pvSetBuffer A pointer to the buffer that holds the data to be set.
* \param[in] u4SetBufferLen The length of the set buffer.
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*                          bytes read from the set buffer. If the call failed
*                          due to invalid length of the set buffer, returns
*                          the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_ADAPTER_NOT_READY
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidDelTS (
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID             pvSetBuffer,
    IN  UINT_32           u4SetBufferLen,
    OUT PUINT_32          pu4SetInfoLen
    )
{
    ASSERT(prAdapter);

    if (prAdapter->rAcpiState == ACPI_STATE_D3) {
        DBGLOG(REQ, WARN, ("Fail in Del TS! (Adapter not ready). ACPI=D%d, Radio=%d\n",
                    prAdapter->rAcpiState, prAdapter->fgIsRadioOff));
        return WLAN_STATUS_ADAPTER_NOT_READY;
    }

    // NOT IMPLEMENTED YET!
    ASSERT(0);

    return WLAN_STATUS_SUCCESS;

}   /* wlanoidDelTS */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to query VoIP connection status, which includes
*        the VoIP interval.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[out] pvQueryBuf A pointer to the buffer that holds the result of
*                           the query.
* \param[in] u4QueryBufLen The length of the query buffer.
* \param[out] pu4QueryInfoLen If the call is successful, returns the number of
*                            bytes written into the query buffer. If the call
*                            failed due to invalid length of the query buffer,
*                            returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_BUFFER_TOO_SHORT
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidQueryVoipConnectionStatus (
    IN P_ADAPTER_T  prAdapter,
    OUT  PVOID    pvQueryBuf,
    IN  UINT_32  u4QueryBufLen,
    OUT PUINT_32 pu4QueryInfoLen
    )
{
    P_CONNECTION_SETTINGS_T prConnSettings;

    DEBUGFUNC("wlanoidQueryVoipConnectionStatus");


    ASSERT(prAdapter);
    ASSERT(pu4QueryInfoLen);

    *pu4QueryInfoLen = sizeof(UINT_32);

    if (u4QueryBufLen < sizeof(UINT_32)) {
        return WLAN_STATUS_BUFFER_TOO_SHORT;
    }

    prConnSettings = &prAdapter->rConnSettings;

    ASSERT(pvQueryBuf);

    *((PUINT_32)pvQueryBuf) = prConnSettings->u4VoipTrafficInterval;

    return WLAN_STATUS_SUCCESS;

} /* end of wlanoidQueryVoipConnectionStatus() */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to set VoIP connection status, which includes
*        the VoIP interval.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
* \param[in] pvSetBuffer A pointer to the buffer that holds the data to be set.
* \param[in] u4SetBufferLen The length of the set buffer.
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*                          bytes read from the set buffer. If the call failed
*                          due to invalid length of the set buffer, returns
*                          the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_LENGTH
* \retval WLAN_STATUS_ADAPTER_NOT_READY
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidSetVoipConnectionStatus (
    IN P_ADAPTER_T  prAdapter,
    IN  PVOID       pvSetBuffer,
    IN  UINT_32     u4SetBufferLen,
    OUT PUINT_32    pu4SetInfoLen
    )
{
    P_PARAM_VOIP_CONFIG prVoipCfg;
    P_CONNECTION_SETTINGS_T prConnSettings;


    ASSERT(prAdapter);
    ASSERT(pu4SetInfoLen);

    *pu4SetInfoLen = sizeof(PARAM_VOIP_CONFIG);

    if (u4SetBufferLen < sizeof(PARAM_VOIP_CONFIG)) {
        return WLAN_STATUS_INVALID_LENGTH;
    }

    if (IS_ARB_IN_RFTEST_STATE(prAdapter)) {
        return WLAN_STATUS_SUCCESS;
    }

    if (prAdapter->rAcpiState == ACPI_STATE_D3) {
        DBGLOG(REQ, WARN, ("Fail in set VoIP polling! (Adapter not ready). ACPI=D%d, Radio=%d\n",
                    prAdapter->rAcpiState, prAdapter->fgIsRadioOff));
        return WLAN_STATUS_ADAPTER_NOT_READY;
    }

    prConnSettings = &prAdapter->rConnSettings;

    ASSERT(pvSetBuffer);
    prVoipCfg = (P_PARAM_VOIP_CONFIG)pvSetBuffer;

    if (prVoipCfg->u4VoipTrafficInterval) {
        prConnSettings->fgIsVoipConn = TRUE;
        prConnSettings->u4VoipTrafficInterval = prVoipCfg->u4VoipTrafficInterval;

        /* Setup for SCAN module */

        /* Setup for PM module */
        // Setup timer for VOIP application
        pmEnableVoipPollingFunc(prAdapter);
    }
    else {
        prConnSettings->fgIsVoipConn = FALSE;
        prConnSettings->u4VoipTrafficInterval = 0;

        pmDisableVoipPollingFunc(prAdapter);
    }

    return WLAN_STATUS_SUCCESS;

} /* end of wlanoidSetVoipConnectionStatus() */


#if 0 /* SUPPORT_WPS */
/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to store the app append ie for mgmt freme.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[in] pvSetBuffer pointer to the buffer that holds the data to be set
* \param[in] u4SetBufferLen The length of the set buffer
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*   bytes read from the set buffer. If the call failed due to invalid length of
*   the set buffer, returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_LENGTH
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidSetAppIE(
    IN P_ADAPTER_T        prAdapter,
    IN  PVOID             pvSetBuffer,
    IN  UINT_32           u4SetBufferLen,
    OUT PUINT_32          pu4SetInfoLen
    )
{
    UINT_32     u4Buffer[2];
    UINT_32     u4MgmtType;
    UINT_32     u4Len;
    PUINT_8     pucBuf;

    DEBUGFUNC("wlanoidSetAppIE");


    ASSERT(prAdapter);
    ASSERT(pvSetBuffer);
    ASSERT(pu4SetInfoLen);

    kalMemCopyFromUser(u4Buffer, pvSetBuffer, sizeof(u4Buffer));
    u4MgmtType = u4Buffer[0];
    u4Len = u4Buffer[1];

    *pu4SetInfoLen = u4SetBufferLen;


    if (u4MgmtType > IEEE80211_APPIE_NUM_OF_FRAME || (u4Len > 300)) {
        return WLAN_STATUS_INVALID_LENGTH;
    }

    pucBuf = (PUINT_8)((UINT_32)pvSetBuffer + sizeof(u4Buffer));

    kalMemCopyFromUser(prAdapter->aucAppIE[u4MgmtType], pucBuf, u4Len);
    prAdapter->aucAppIELen[u4MgmtType] = u4Len;

    return WLAN_STATUS_SUCCESS;

} /* end of wlanoidSetAppIE() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to set the app frame filter for mgmt freme.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[in] pvSetBuffer pointer to the buffer that holds the data to be set
* \param[in] u4SetBufferLen The length of the set buffer
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*   bytes read from the set buffer. If the call failed due to invalid length of
*   the set buffer, returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidSetFrameFilter(
    IN P_ADAPTER_T        prAdapter,
    IN  PVOID             pvSetBuffer,
    IN  UINT_32           u4SetBufferLen,
    OUT PUINT_32          pu4SetInfoLen
    )
{
    UINT_32     u4Buffer[2];
    UINT_32     u4MgmtType;
    UINT_32     u4Len;
    //PUINT_8     pucBuf;

    DEBUGFUNC("wlanoidSetFrameFilter");


    ASSERT(prAdapter);
    ASSERT(pvSetBuffer);
    ASSERT(pu4SetInfoLen);

    kalMemCopyFromUser(u4Buffer, pvSetBuffer, sizeof(u4Buffer));
    u4MgmtType = u4Buffer[0];
    u4Len = u4Buffer[1];

    *pu4SetInfoLen = u4SetBufferLen;

    /* Todo: the filter */
    if (u4MgmtType == 0) {
        prAdapter->fgIndMgt = FALSE;
    }
    else if (u4MgmtType != 0) {
        prAdapter->fgIndMgt = TRUE;
    }

    return WLAN_STATUS_SUCCESS;
}   /* wlanoidSetFrameFilter */
#endif /* SUPPORT_WPS */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to turn radio off.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
* \param[in] pvSetBuffer A pointer to the buffer that holds the data to be set.
* \param[in] u4SetBufferLen The length of the set buffer.
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*                          bytes read from the set buffer. If the call failed
*                          due to invalid length of the set buffer, returns
*                          the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_ADAPTER_NOT_READY
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidSetDisassociate (
    IN P_ADAPTER_T        prAdapter,
    IN  PVOID             pvSetBuffer,
    IN  UINT_32           u4SetBufferLen,
    OUT PUINT_32          pu4SetInfoLen
    )
{

    DEBUGFUNC("wlanoidSetDisassociate");

    ASSERT(prAdapter);
    ASSERT(pu4SetInfoLen);

    *pu4SetInfoLen = 0;

    if (IS_ARB_IN_RFTEST_STATE(prAdapter)) {
        return WLAN_STATUS_SUCCESS;
    }

    if (prAdapter->rAcpiState == ACPI_STATE_D3) {
        DBGLOG(REQ, WARN, ("Fail in set disassociate! (Adapter not ready). ACPI=D%d, Radio=%d\n",
                    prAdapter->rAcpiState, prAdapter->fgIsRadioOff));
        return WLAN_STATUS_ADAPTER_NOT_READY;
    }

    if (prAdapter->eConnectionState == MEDIA_STATE_CONNECTED) {
        arbFsmRunEventJoinDisassoc(prAdapter);
    }
    else {
        prAdapter->rConnSettings.fgIsConnReqIssued = FALSE;
        arbFsmRunEventAbort(prAdapter, FALSE);

//        prAdapter->fgIsRadioOff = TRUE;
    }

    return WLAN_STATUS_SUCCESS;
} /* wlanoidSetDisassociate */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to query the power save profile.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[out] pvQueryBuf A pointer to the buffer that holds the result of
*                           the query.
* \param[in] u4QueryBufLen The length of the query buffer.
* \param[out] pu4QueryInfoLen If the call is successful, returns the number of
*                            bytes written into the query buffer. If the call
*                            failed due to invalid length of the query buffer,
*                            returns the amount of storage needed.
*
* \return WLAN_STATUS_SUCCESS
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidQuery802dot11PowerSaveProfile (
    IN  P_ADAPTER_T prAdapter,
    IN  PVOID       pvQueryBuffer,
    IN  UINT_32     u4QueryBufferLen,
    OUT PUINT_32    pu4QueryInfoLen
    )
{
    DEBUGFUNC("wlanoidQuery802dot11PowerSaveProfile");

    ASSERT(prAdapter);
    ASSERT(pu4QueryInfoLen);

    if (u4QueryBufferLen!=0) {
        ASSERT(pvQueryBuffer);
    *(PPARAM_POWER_MODE) pvQueryBuffer = prAdapter->rConnSettings.rPwrMode;
    *pu4QueryInfoLen = sizeof(PARAM_POWER_MODE);
    }
    return WLAN_STATUS_SUCCESS;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to set the power save profile.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
* \param[in] pvSetBuffer A pointer to the buffer that holds the data to be set.
* \param[in] u4SetBufferLen The length of the set buffer.
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*                          bytes read from the set buffer. If the call failed
*                          due to invalid length of the set buffer, returns
*                          the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_LENGTH
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidSet802dot11PowerSaveProfile (
    IN  P_ADAPTER_T prAdapter,
    IN  PVOID       prSetBuffer,
    IN  UINT_32     u4SetBufferLen,
    OUT PUINT_32    pu4SetInfoLen
    )
{
    DEBUGFUNC("wlanoidSet802dot11PowerSaveProfile");

    ASSERT(prAdapter);
    ASSERT(pu4SetInfoLen);

    *pu4SetInfoLen = sizeof(PARAM_POWER_MODE);

    ASSERT(prSetBuffer);

    /* Check if the new power mode is valid. */
    if (*(PPARAM_POWER_MODE) prSetBuffer >= Param_PowerModeMax) {
        WARNLOG(("Invalid power mode %d\n",
            *(PPARAM_POWER_MODE) prSetBuffer));
        return WLAN_STATUS_INVALID_DATA;
    }

    if (IS_ARB_IN_RFTEST_STATE(prAdapter)) {
        return WLAN_STATUS_SUCCESS;
    }

    /* Save the new power mode. */
    prAdapter->rConnSettings.rPwrMode = *(PPARAM_POWER_MODE) prSetBuffer;

    pmFsmRunEventSetPowerSaveProfile(
            prAdapter,
            aPowerModeToPwrSaveProfMapping[prAdapter->rConnSettings.rPwrMode]);

    return WLAN_STATUS_SUCCESS;

} /* end of wlanoidSetAcpiDevicePowerStateMode() */



/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to set BG SSID related parameters.
*
* \param[in] prAdapter Pointer to the Adapter structure
* \param[in] pvSetBuffer A pointer to the buffer that holds the data to be set.
* \param[in] u4SetBufferLen The length of the set buffer.
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*                          bytes read from the set buffer. If the call failed
*                          due to invalid length of the set buffer, returns the
*                          amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_LENGTH
*
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidSetBgSsidParam (
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID             pvSetBuffer,
    IN  UINT_32           u4SetBufferLen,
    OUT PUINT_32          pu4SetInfoLen
    )
{
    P_SCAN_CONFIG_T     prScanCfg;

    DEBUGFUNC("wlanoidSetBgSsidParam");

    ASSERT(prAdapter);
    ASSERT(pvSetBuffer);
    ASSERT(pu4SetInfoLen);

    if (u4SetBufferLen != sizeof(BG_SCAN_CONFIG_T)) {
        return WLAN_STATUS_INVALID_LENGTH;
    }

    prScanCfg = &prAdapter->rScanInfo.rScanConfig;

    *pu4SetInfoLen = sizeof(BG_SCAN_CONFIG_T);

    if (prScanCfg->rBgScanCfg.rScanCandidate.ucNumHwSsidScanEntry) {
        kalMemCopy(
            &prScanCfg->rBgScanCfg,
            pvSetBuffer,
            sizeof(BG_SCAN_CONFIG_T));

        prScanCfg->rBgScanCfg.fgIsFromUserSetting = TRUE;
    }
    else {
        kalMemZero(
            &prScanCfg->rBgScanCfg,
            sizeof(BG_SCAN_CONFIG_T));
    }

    return WLAN_STATUS_SUCCESS;
}   /* wlanoidSetBgSsidParam */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to set the pattern search related configuration.
*
*        NOTE: The configuration here will "over-write" the setting in
*        PM_PROFILE_SETUP_INFO_T, which is a basic setup of Power Management Profile.
*
*
* \param[in] prAdapter Pointer to the Adapter structure
* \param[in] pvSetBuffer A pointer to the buffer that holds the data to be set.
* \param[in] u4SetBufferLen The length of the set buffer.
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*                          bytes read from the set buffer. If the call failed
*                          due to invalid length of the set buffer, returns the
*                          amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_ADAPTER_NOT_READY
*
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidSetPatternConfig (
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID             pvSetBuffer,
    IN  UINT_32           u4SetBufferLen,
    OUT PUINT_32          pu4SetInfoLen
    )
{
    P_PARAM_CUSTOM_PATTERN_SEARCH_CONFIG_STRUC_T prPtrnCfg;
    UINT_32 i;
    P_PM_INFO_T prPmInfo;

    DEBUGFUNC("wlanoidSetPatternConfig");

    ASSERT(prAdapter);
    ASSERT(pvSetBuffer);
    ASSERT(pu4SetInfoLen);

    prPtrnCfg = (P_PARAM_CUSTOM_PATTERN_SEARCH_CONFIG_STRUC_T) pvSetBuffer;
    *pu4SetInfoLen = sizeof(PARAM_CUSTOM_PATTERN_SEARCH_CONFIG_STRUC_T);

    if (IS_ARB_IN_RFTEST_STATE(prAdapter)) {
        return WLAN_STATUS_SUCCESS;
    }

    if (prAdapter->rAcpiState == ACPI_STATE_D3) {
        DBGLOG(REQ, WARN, ("Fail in set pattern search function! (Adapter not ready). ACPI=D%d, Radio=%d\n",
                    prAdapter->rAcpiState, prAdapter->fgIsRadioOff));
        return WLAN_STATUS_ADAPTER_NOT_READY;
    }

    prPmInfo = &prAdapter->rPmInfo;

    /* Initialize LP instruction number, all of the extra instruction need to be re-programmed again */
    prPmInfo->ucNumOfInstSleep = 0;
    prPmInfo->ucNumOfInstAwake = 0;
    prPmInfo->ucNumOfInstOn = 0;

    // setup the pattern (total 32 patterns in HW engine)
    for (i = 0; i < HW_PATTERN_SEARCH_SET_NUMBER; i++) {
        nicpmConfigPattern(prAdapter,
                           prPtrnCfg->arPattern[i].ucIndex,
                           prPtrnCfg->arPattern[i].fgCheckBcA1,
                           prPtrnCfg->arPattern[i].fgCheckMcA1,
                           prPtrnCfg->arPattern[i].fgCheckUcA1,
                           prPtrnCfg->arPattern[i].fgIpv4Ip,
                           prPtrnCfg->arPattern[i].fgIpv6Icmp,
                           prPtrnCfg->arPattern[i].fgGarpIpEqual,
                           prPtrnCfg->arPattern[i].fgArpCtrl,
                           prPtrnCfg->arPattern[i].fgAndOp,
                           prPtrnCfg->arPattern[i].fgNotOp,
                           prPtrnCfg->arPattern[i].ucPatternMask,
                           prPtrnCfg->arPattern[i].ucPatternOffset,
                           prPtrnCfg->arPattern[i].au4Pattern);
    }

    // setup the function
    nicpmConfigPatternSearchFunc(prAdapter,
                                 prPtrnCfg->rFunc.fgBcPatternMatchEnable,
                                 prPtrnCfg->rFunc.fgMcPatternMatchEnable,
                                 prPtrnCfg->rFunc.fgUcPatternMatchEnable,
                                 prPtrnCfg->rFunc.fgBcPatternMatchOperation,
                                 prPtrnCfg->rFunc.fgMcPatternMatchOperation,
                                 prPtrnCfg->rFunc.fgUcPatternMatchOperation,
                                 prPtrnCfg->rFunc.fgIpv6MatchCtrl);


    return WLAN_STATUS_SUCCESS;
}   /* wlanoidSetPatternConfig */

/*----------------------------------------------------------------------------*/
/*!
* \brief This is used to set power management advanced parameters
*
* \param[in] prAdapter Pointer to the Adapter structure
* \param[in] pvSetBuffer A pointer to the buffer that holds the data to be set.
* \param[in] u4SetBufferLen The length of the set buffer.
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*                          bytes read from the set buffer. If the call failed
*                          due to invalid length of the set buffer, returns the
*                          amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_LENGTH
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidSetPwrMgmtProfParam (
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID             pvSetBuffer,
    IN  UINT_32           u4SetBufferLen,
    OUT PUINT_32          pu4SetInfoLen
    )
{
    P_PM_INFO_T prPmInfo;
    P_PM_PROFILE_SETUP_INFO_T prPmProfSetupInfo;

    DEBUGFUNC("wlanoidSetPwrMgmtProfParam");


    ASSERT(prAdapter);
    ASSERT(pu4SetInfoLen);

    *pu4SetInfoLen = sizeof(PM_PROFILE_SETUP_INFO_T);
    if (u4SetBufferLen != sizeof(PM_PROFILE_SETUP_INFO_T)) {
        return WLAN_STATUS_INVALID_LENGTH;
    }

    ASSERT(pvSetBuffer);

    prPmInfo = &prAdapter->rPmInfo;
    prPmProfSetupInfo = &prPmInfo->rPmProfSetupInfo;

    kalMemCopy(
        prPmProfSetupInfo,
        pvSetBuffer,
        sizeof(PM_PROFILE_SETUP_INFO_T));

    return WLAN_STATUS_SUCCESS;
}   /* wlanoidSetPwrMgmtProfParam */


/*----------------------------------------------------------------------------*/
/*!
* \brief This is used to query power management advanced parameters
*
* \param[in] prAdapter Pointer to the Adapter structure
* \param[in] pvSetBuffer A pointer to the buffer that holds the data to be set.
* \param[in] u4SetBufferLen The length of the set buffer.
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*                          bytes read from the set buffer. If the call failed
*                          due to invalid length of the set buffer, returns the
*                          amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_LENGTH
*
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidQueryPwrMgmtProfParam (
    IN P_ADAPTER_T  prAdapter,
    IN  PVOID    pvQueryBuf,
    IN  UINT_32  u4QueryBufLen,
    OUT PUINT_32 pu4QueryInfoLen
    )
{
    P_PM_INFO_T prPmInfo;
    P_PM_PROFILE_SETUP_INFO_T prPmProfSetupInfo;

    DEBUGFUNC("wlanoidQueryPwrMgmtProfParam");


    ASSERT(prAdapter);
    ASSERT(pu4QueryInfoLen);

    *pu4QueryInfoLen = sizeof(PM_PROFILE_SETUP_INFO_T);

    if (u4QueryBufLen != sizeof(PM_PROFILE_SETUP_INFO_T)) {
        return WLAN_STATUS_INVALID_LENGTH;
    }

    ASSERT(pvQueryBuf);


    prPmInfo = &prAdapter->rPmInfo;
    prPmProfSetupInfo = &prPmInfo->rPmProfSetupInfo;

    kalMemCopy(
        pvQueryBuf,
        prPmProfSetupInfo,
        sizeof(PM_PROFILE_SETUP_INFO_T));


    return WLAN_STATUS_SUCCESS;
}   /* wlanoidQueryPwrMgmtProfParam */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to query current status of Roaming function.
*
* \param[in] prAdapter          Pointer to the Adapter structure.
* \param[in] pvQueryBuffer      Pointer to the buffer that holds the result of
*                               the query.
* \param[in] u4QueryBufferLen   The length of the query buffer.
* \param[out] pu4QueryInfoLen   If the call is successful, returns the number of
*                               bytes written into the query buffer. If the call
*                               failed due to invalid length of the query buffer,
*                               returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_BUFFER_TOO_SHORT
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidQueryRoamingFunction (
    IN  P_ADAPTER_T prAdapter,
    OUT PVOID       pvQueryBuffer,
    IN  UINT_32     u4QueryBufferLen,
    OUT PUINT_32    pu4QueryInfoLen
    )
{
    DEBUGFUNC("wlanoidQueryRoamingFunction");


    ASSERT(prAdapter);
    ASSERT(pu4QueryInfoLen);

    DBGLOG(REQ, INFO, ("\n"));

    *pu4QueryInfoLen = sizeof(UINT_32);

    if (u4QueryBufferLen < sizeof(UINT_32)) {
        return WLAN_STATUS_BUFFER_TOO_SHORT;
    }

    ASSERT(pvQueryBuffer);

    *(PUINT_32)pvQueryBuffer = (UINT_32)prAdapter->rConnSettings.fgIsEnableRoaming;

    DBGLOG(REQ, INFO, ("Current Roaming Status: %d\n",
        prAdapter->rConnSettings.fgIsEnableRoaming));

    return WLAN_STATUS_SUCCESS;

}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to turn on/off Roaming function.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
* \param[in] pvSetBuffer    Pointer to the buffer that holds the data to be set.
* \param[in] u4SetBufferLen The length of the set buffer.
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*                           bytes read from the set buffer. If the call failed
*                           due to invalid length of the set buffer, returns
*                           the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_LENGTH
* \retval WLAN_STATUS_INVALID_DATA
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidSetRoamingFunction (
    IN  P_ADAPTER_T prAdapter,
    IN  PVOID       pvSetBuffer,
    IN  UINT_32     u4SetBufferLen,
    OUT PUINT_32    pu4SetInfoLen
    )
{
    DEBUGFUNC("wlanoidSetRoamingFunction");


    ASSERT(prAdapter);
    ASSERT(pu4SetInfoLen);

    *pu4SetInfoLen = sizeof(UINT_32);

    if (u4SetBufferLen < sizeof(UINT_32)) {
        return WLAN_STATUS_INVALID_LENGTH;
    }

    if (IS_ARB_IN_RFTEST_STATE(prAdapter)) {
        return WLAN_STATUS_SUCCESS;
    }

    ASSERT(pvSetBuffer);

    if (*(PUINT_32)pvSetBuffer == 1) { /* Turn on Roaming */
        if (!prAdapter->rConnSettings.fgIsEnableRoaming) {

            prAdapter->rConnSettings.fgIsEnableRoaming = TRUE;

            roamingFsmRunEventStart(prAdapter);
        }
    }
    else if (*(PUINT_32)pvSetBuffer == 0) { /* Turn off Roaming */

        if (prAdapter->rConnSettings.fgIsEnableRoaming) {

            roamingFsmRunEventAbort(prAdapter);

            prAdapter->rConnSettings.fgIsEnableRoaming = FALSE;
        }
    }
    else {
        return WLAN_STATUS_INVALID_DATA;
    }

    return WLAN_STATUS_SUCCESS;

}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to query current status of AdHoc Mode.
*
* \param[in] prAdapter          Pointer to the Adapter structure.
* \param[in] pvQueryBuffer      Pointer to the buffer that holds the result of
*                               the query.
* \param[in] u4QueryBufferLen   The length of the query buffer.
* \param[out] pu4QueryInfoLen   If the call is successful, returns the number of
*                               bytes written into the query buffer. If the call
*                               failed due to invalid length of the query buffer,
*                               returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_BUFFER_TOO_SHORT
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidQueryAdHocMode (
    IN  P_ADAPTER_T prAdapter,
    OUT PVOID       pvQueryBuffer,
    IN  UINT_32     u4QueryBufferLen,
    OUT PUINT_32    pu4QueryInfoLen
    )
{
    DEBUGFUNC("wlanoidQueryAdHocMode");


    ASSERT(prAdapter);
    ASSERT(pu4QueryInfoLen);

    DBGLOG(REQ, INFO, ("\n"));

    *pu4QueryInfoLen = sizeof(UINT_32);

    if (u4QueryBufferLen < sizeof(UINT_32)) {
        return WLAN_STATUS_BUFFER_TOO_SHORT;
    }

    ASSERT(pvQueryBuffer);

    *(PUINT_32)pvQueryBuffer = (UINT_32)prAdapter->rConnSettings.eAdHocMode;

    DBGLOG(REQ, INFO, ("Current AdHoc Mode: %d\n",
        prAdapter->rConnSettings.eAdHocMode));

    return WLAN_STATUS_SUCCESS;

} /* end of wlanoidQueryAdHocMode() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to set AdHoc Mode.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
* \param[in] pvSetBuffer    Pointer to the buffer that holds the data to be set.
* \param[in] u4SetBufferLen The length of the set buffer.
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*                           bytes read from the set buffer. If the call failed
*                           due to invalid length of the set buffer, returns
*                           the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_LENGTH
* \retval WLAN_STATUS_INVALID_DATA
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidSetAdHocMode (
    IN  P_ADAPTER_T prAdapter,
    IN  PVOID       pvSetBuffer,
    IN  UINT_32     u4SetBufferLen,
    OUT PUINT_32    pu4SetInfoLen
    )
{
    DEBUGFUNC("wlanoidSetAdHocMode");


    ASSERT(prAdapter);
    ASSERT(pu4SetInfoLen);

    *pu4SetInfoLen = sizeof(UINT_32);

    if (u4SetBufferLen < sizeof(UINT_32)) {
        return WLAN_STATUS_INVALID_LENGTH;
    }

    ASSERT(pvSetBuffer);

    switch(*(PUINT_32)pvSetBuffer) {
    case AD_HOC_MODE_11B:
    case AD_HOC_MODE_MIXED_11BG:
    case AD_HOC_MODE_11G:
    case AD_HOC_MODE_11A:
        prAdapter->rConnSettings.eAdHocMode =
            (ENUM_PARAM_AD_HOC_MODE_T)(*(PUINT_32)pvSetBuffer);
        break;

    default:
        return WLAN_STATUS_INVALID_DATA;
    }

    return WLAN_STATUS_SUCCESS;

} /* end of wlanoidSetAdHocMode() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to query RF frequency.
*
* \param[in] prAdapter          Pointer to the Adapter structure.
* \param[in] pvQueryBuffer      Pointer to the buffer that holds the result of
*                               the query.
* \param[in] u4QueryBufferLen   The length of the query buffer.
* \param[out] pu4QueryInfoLen   If the call is successful, returns the number of
*                               bytes written into the query buffer. If the call
*                               failed due to invalid length of the query buffer,
*                               returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_BUFFER_TOO_SHORT
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidQueryFrequency (
    IN  P_ADAPTER_T prAdapter,
    OUT PVOID       pvQueryBuffer,
    IN  UINT_32     u4QueryBufferLen,
    OUT PUINT_32    pu4QueryInfoLen
    )
{
    P_RF_INFO_T prRFInfo;

    DEBUGFUNC("wlanoidQueryFrequency");


    ASSERT(prAdapter);
    ASSERT(pu4QueryInfoLen);

    prRFInfo = &prAdapter->rRFInfo;

    DBGLOG(REQ, INFO, ("\n"));

    *pu4QueryInfoLen = sizeof(UINT_32);

    if (u4QueryBufferLen < sizeof(UINT_32)) {
        return WLAN_STATUS_BUFFER_TOO_SHORT;
    }

    ASSERT(pvQueryBuffer);

    *(PUINT_32)pvQueryBuffer =
        nicGetFreqByChannelNum(prRFInfo->ucChannelNum,
                               prRFInfo->eBand);

    DBGLOG(REQ, INFO, ("Current RF frequency: %ld\n",
                        *(PUINT_32)pvQueryBuffer));

    return WLAN_STATUS_SUCCESS;

} /* end of wlanoidQueryFrequency() */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to set RF frequency by User Settings.
*
* \param[in] prAdapter          Pointer to the Adapter structure.
* \param[in] pvQueryBuffer      Pointer to the buffer that holds the result of
*                               the query.
* \param[in] u4QueryBufferLen   The length of the query buffer.
* \param[out] pu4QueryInfoLen   If the call is successful, returns the number of
*                               bytes written into the query buffer. If the call
*                               failed due to invalid length of the query buffer,
*                               returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_LENGTH
* \retval WLAN_STATUS_INVALID_DATA
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidSetFrequency (
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID             pvSetBuffer,
    IN  UINT_32           u4SetBufferLen,
    OUT PUINT_32          pu4SetInfoLen
    )
{
    WLAN_STATUS  rStatus = WLAN_STATUS_SUCCESS;
    PUINT_32 pu4FreqInKHz;
    UINT_8 ucChannelNum;
    ENUM_BAND_T eBand;


    ASSERT(prAdapter);
    ASSERT(pu4SetInfoLen);

    *pu4SetInfoLen = sizeof(UINT_32);

    if (u4SetBufferLen < sizeof(UINT_32)) {
        return WLAN_STATUS_INVALID_LENGTH;
    }

    ASSERT(pvSetBuffer);
    pu4FreqInKHz = (PUINT_32)pvSetBuffer;

    if (!nicGetChannelNumByFreq(*pu4FreqInKHz, &ucChannelNum, &eBand)) {
        DBGLOG(REQ, TRACE, ("Invalid Frequency = %ld\n", *pu4FreqInKHz));
        return WLAN_STATUS_INVALID_DATA;
    }

    if (IS_ARB_IN_RFTEST_STATE(prAdapter)) {
        PARAM_802_11_CONFIG_T rNewConfig = {0};
        rNewConfig.u4DSConfig = *(PUINT_32)pu4FreqInKHz;
        rStatus =
            rftestSet80211Configuration(
                prAdapter,
                &rNewConfig
                );
        if(rStatus == WLAN_STATUS_SUCCESS)
        {
            DBGLOG(REQ, INFO, ("Change channel successfully.\n"));
        }
        else{
            DBGLOG(REQ, ERROR, ("Can not switch RF channel\n"));

        }
    }
    else {
        prAdapter->rConnSettings.ucChannelNum = ucChannelNum;
        prAdapter->rConnSettings.ucChannelBand = (UINT_8)eBand;
        prAdapter->rConnSettings.u4FreqInKHz = *pu4FreqInKHz;

        if (prAdapter->rConnSettings.eOPMode != NET_TYPE_INFRA) {
            /* Send the "Abort" event to arbiter. */
            arbFsmRunEventAbort(prAdapter, TRUE); /* Reset to STANDBY */
        }
    }

    return WLAN_STATUS_SUCCESS;

} /* end of wlanoidSetFrequency() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to set 802.11 channel of the radio frequency.
*        This is a proprietary function call to Linux currently.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
* \param[in] pvSetBuffer A pointer to the buffer that holds the data to be set.
* \param[in] u4SetBufferLen The length of the set buffer.
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*                          bytes read from the set buffer. If the call failed
*                          due to invalid length of the set buffer, returns
*                          the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_LENGTH
* \retval WLAN_STATUS_INVALID_DATA
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidSetChannel (
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID             pvSetBuffer,
    IN  UINT_32           u4SetBufferLen,
    OUT PUINT_32          pu4SetInfoLen
    )
{
    PUINT_32 pu4ChannelNum;
    UINT_8 ucChannelNum;
    UINT_32 u4FreqInKHz;


    ASSERT(prAdapter);
    ASSERT(pu4SetInfoLen);

    *pu4SetInfoLen = sizeof(UINT_32);

    if (u4SetBufferLen < sizeof(UINT_32)) {
        return WLAN_STATUS_INVALID_LENGTH;
    }

    if (IS_ARB_IN_RFTEST_STATE(prAdapter)) {
        return WLAN_STATUS_SUCCESS;
    }

    ASSERT(pvSetBuffer);
    pu4ChannelNum = (PUINT_32)pvSetBuffer;

    ucChannelNum = (UINT_8)*pu4ChannelNum;

    /* TODO(Kevin) : Consider 802.11a according to PhyType Selection */
    u4FreqInKHz = nicGetFreqByChannelNum(ucChannelNum, BAND_24G);
    if (u4FreqInKHz == 0) {

        DBGLOG(REQ, TRACE, ("Invalid Channel Number = %d\n", ucChannelNum));
        return WLAN_STATUS_INVALID_DATA;
    }

    prAdapter->rConnSettings.ucChannelNum = ucChannelNum;
    prAdapter->rConnSettings.ucChannelBand = (UINT_8)BAND_24G;
    prAdapter->rConnSettings.u4FreqInKHz = u4FreqInKHz;

    if (prAdapter->rConnSettings.eOPMode != NET_TYPE_INFRA) {
        /* Send the "Abort" event to arbiter. */
        arbFsmRunEventAbort(prAdapter, TRUE); /* Reset to STANDBY */
    }


    return WLAN_STATUS_SUCCESS;
}


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to query the Beacon Interval from User Settings.
*
* \param[in] prAdapter          Pointer to the Adapter structure.
* \param[in] pvQueryBuffer      Pointer to the buffer that holds the result of
*                               the query.
* \param[in] u4QueryBufferLen   The length of the query buffer.
* \param[out] pu4QueryInfoLen   If the call is successful, returns the number of
*                               bytes written into the query buffer. If the call
*                               failed due to invalid length of the query buffer,
*                               returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_BUFFER_TOO_SHORT
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidQueryBeaconInterval (
    IN  P_ADAPTER_T prAdapter,
    OUT PVOID       pvQueryBuffer,
    IN  UINT_32     u4QueryBufferLen,
    OUT PUINT_32    pu4QueryInfoLen
    )
{
    DEBUGFUNC("wlanoidQueryBeaconInterval");


    ASSERT(prAdapter);
    ASSERT(pu4QueryInfoLen);

    DBGLOG(REQ, INFO, ("\n"));

    *pu4QueryInfoLen = sizeof(UINT_32);

    if (u4QueryBufferLen < sizeof(UINT_32)) {
        return WLAN_STATUS_BUFFER_TOO_SHORT;
    }

    ASSERT(pvQueryBuffer);

    if (prAdapter->eConnectionState== MEDIA_STATE_CONNECTED) {
        *(PUINT_32)pvQueryBuffer =
            (UINT_32)prAdapter->rBssInfo.u2BeaconInterval;
    }
    else {
        if (prAdapter->rConnSettings.eOPMode == NET_TYPE_INFRA) {
            *(PUINT_32)pvQueryBuffer = 0;
        }
        else {
            *(PUINT_32)pvQueryBuffer =
                (UINT_32)prAdapter->rConnSettings.u2BeaconPeriod;
        }
    }

    DBGLOG(REQ, INFO, ("Current beacon interval: %ld\n",
                        *(PUINT_32)pvQueryBuffer));

    return WLAN_STATUS_SUCCESS;

} /* end of wlanoidQueryBeaconInterval() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to set the Beacon Interval to User Settings.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
* \param[in] pvSetBuffer    Pointer to the buffer that holds the data to be set.
* \param[in] u4SetBufferLen The length of the set buffer.
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*                           bytes read from the set buffer. If the call failed
*                           due to invalid length of the set buffer, returns
*                           the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_LENGTH
* \retval WLAN_STATUS_INVALID_DATA
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidSetBeaconInterval (
    IN  P_ADAPTER_T prAdapter,
    IN  PVOID       pvSetBuffer,
    IN  UINT_32     u4SetBufferLen,
    OUT PUINT_32    pu4SetInfoLen
    )
{
    PUINT_32 pu4BeaconInterval;

    DEBUGFUNC("wlanoidSetBeaconInterval");


    ASSERT(prAdapter);
    ASSERT(pu4SetInfoLen);

    *pu4SetInfoLen = sizeof(UINT_32);

    if (u4SetBufferLen < sizeof(UINT_32)) {
        return WLAN_STATUS_INVALID_LENGTH;
    }

    if (IS_ARB_IN_RFTEST_STATE(prAdapter)) {
        return WLAN_STATUS_SUCCESS;
    }

    ASSERT(pvSetBuffer);
    pu4BeaconInterval = (PUINT_32)pvSetBuffer;

    /* TODO(Kevin) : Consider 802.11a according to PhyType Selection */
    if ((*pu4BeaconInterval < DOT11_BEACON_PERIOD_MIN) ||
        (*pu4BeaconInterval > DOT11_BEACON_PERIOD_MAX)) {
        DBGLOG(REQ, TRACE, ("Invalid Beacon Interval = %ld\n", *pu4BeaconInterval));
        return WLAN_STATUS_INVALID_DATA;
    }

    prAdapter->rConnSettings.u2BeaconPeriod = (UINT_16)*pu4BeaconInterval;

    DBGLOG(REQ, INFO, ("Set beacon interval: %d\n",
        prAdapter->rConnSettings.u2BeaconPeriod));


    if (prAdapter->rConnSettings.eOPMode != NET_TYPE_INFRA) {
        /* Send the "Abort" event to arbiter. */
        arbFsmRunEventAbort(prAdapter, TRUE); /* Reset to STANDBY */
    }

    return WLAN_STATUS_SUCCESS;

} /* end of wlanoidSetBeaconInterval() */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to query the ATIM window from User Settings.
*
* \param[in] prAdapter          Pointer to the Adapter structure.
* \param[in] pvQueryBuffer      Pointer to the buffer that holds the result of
*                               the query.
* \param[in] u4QueryBufferLen   The length of the query buffer.
* \param[out] pu4QueryInfoLen   If the call is successful, returns the number of
*                               bytes written into the query buffer. If the call
*                               failed due to invalid length of the query buffer,
*                               returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_BUFFER_TOO_SHORT
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidQueryAtimWindow (
    IN  P_ADAPTER_T prAdapter,
    OUT PVOID       pvQueryBuffer,
    IN  UINT_32     u4QueryBufferLen,
    OUT PUINT_32    pu4QueryInfoLen
    )
{
    DEBUGFUNC("wlanoidQueryAtimWindow");


    ASSERT(prAdapter);
    ASSERT(pu4QueryInfoLen);

    DBGLOG(REQ, INFO, ("\n"));

    *pu4QueryInfoLen = sizeof(UINT_32);

    if (u4QueryBufferLen < sizeof(UINT_32)) {
        return WLAN_STATUS_BUFFER_TOO_SHORT;
    }

    ASSERT(pvQueryBuffer);

    if (prAdapter->rConnSettings.eOPMode == NET_TYPE_IBSS) {

        if (prAdapter->eConnectionState== MEDIA_STATE_CONNECTED) {
            *(PUINT_32)pvQueryBuffer =
                (UINT_32)prAdapter->rBssInfo.u2ATIMWindow;
        }
        else {
            *(PUINT_32)pvQueryBuffer =
                (UINT_32)prAdapter->rConnSettings.u2AtimWindow;
        }
    }
    else {
        *(PUINT_32)pvQueryBuffer = 0;
    }

    DBGLOG(REQ, INFO, ("Current ATIM window: %ld\n",
                        *(PUINT_32)pvQueryBuffer));

    return WLAN_STATUS_SUCCESS;

} /* end of wlanoidQueryAtimWindow() */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to set the ATIM window to User Settings.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
* \param[in] pvSetBuffer    Pointer to the buffer that holds the data to be set.
* \param[in] u4SetBufferLen The length of the set buffer.
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*                           bytes read from the set buffer. If the call failed
*                           due to invalid length of the set buffer, returns
*                           the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_LENGTH
* \retval WLAN_STATUS_INVALID_DATA
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidSetAtimWindow (
    IN  P_ADAPTER_T prAdapter,
    IN  PVOID       pvSetBuffer,
    IN  UINT_32     u4SetBufferLen,
    OUT PUINT_32    pu4SetInfoLen
    )
{
    PUINT_32 pu4AtimWindow;

    DEBUGFUNC("wlanoidSetAtimWindow");


    ASSERT(prAdapter);
    ASSERT(pu4SetInfoLen);

    *pu4SetInfoLen = sizeof(UINT_32);

    if (u4SetBufferLen < sizeof(UINT_32)) {
        return WLAN_STATUS_INVALID_LENGTH;
    }

    if (IS_ARB_IN_RFTEST_STATE(prAdapter)) {
        return WLAN_STATUS_SUCCESS;
    }

    ASSERT(pvSetBuffer);
    pu4AtimWindow = (PUINT_32)pvSetBuffer;

    prAdapter->rConnSettings.u2AtimWindow= (UINT_16)*pu4AtimWindow;

    DBGLOG(REQ, INFO, ("Set ATIM window: %d\n",
        prAdapter->rConnSettings.u2AtimWindow));


    if (prAdapter->rConnSettings.eOPMode != NET_TYPE_INFRA) {
        /* Send the "Abort" event to arbiter. */
        arbFsmRunEventAbort(prAdapter, TRUE); /* Reset to STANDBY */
    }

    return WLAN_STATUS_SUCCESS;

} /* end of wlanoidSetAtimWindow() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to Set the MAC address which is currently used by the NIC.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
* \param[in] pvSetBuffer    Pointer to the buffer that holds the data to be set.
* \param[in] u4SetBufferLen The length of the set buffer.
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*                           bytes read from the set buffer. If the call failed
*                           due to invalid length of the set buffer, returns
*                           the amount of storage needed.
*
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_LENGTH
* \retval WLAN_STATUS_INVALID_DATA
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidSetCurrentAddr (
    IN  P_ADAPTER_T prAdapter,
    IN  PVOID       pvSetBuffer,
    IN  UINT_32     u4SetBufferLen,
    OUT PUINT_32    pu4SetInfoLen
    )
{
    PUINT_8 pucNewMacAddr;
    UINT_8 aucZeroMacAddr[MAC_ADDR_LEN] = {0,0,0,0,0,0};
    DEBUGFUNC("wlanoidSetCurrentAddrForLinux");


    ASSERT(prAdapter);
    ASSERT(pu4SetInfoLen);

    *pu4SetInfoLen = PARAM_MAC_ADDR_LEN;

    if (u4SetBufferLen < PARAM_MAC_ADDR_LEN) {
        return WLAN_STATUS_INVALID_LENGTH;
    }

    if (IS_ARB_IN_RFTEST_STATE(prAdapter)) {
        return WLAN_STATUS_SUCCESS;
    }

    ASSERT(pvSetBuffer);
    pucNewMacAddr = (PUINT_8)pvSetBuffer;

    if (IS_BMCAST_MAC_ADDR(pucNewMacAddr)) {
        return WLAN_STATUS_INVALID_DATA;
    }

    /* Accept the change request only when the NEW MAC Address is different from
     * current User Setting.
     */
    if (UNEQUAL_MAC_ADDR(prAdapter->rConnSettings.aucMacAddress, pucNewMacAddr)) {

        /* Update MAC Address in Connection Settings */
        COPY_MAC_ADDR(prAdapter->rConnSettings.aucMacAddress, pucNewMacAddr);

        /* If the input MAC Address is NULL, use the MAC Address from EEPROM. */
        if (EQUAL_MAC_ADDR(pucNewMacAddr, aucZeroMacAddr)) {

            COPY_MAC_ADDR(prAdapter->aucMacAddress, prAdapter->rEEPROMCtrl.aucMacAddress);
        }
        else {
            COPY_MAC_ADDR(prAdapter->aucMacAddress, pucNewMacAddr);
        }

        nicSetUnicastAddr(prAdapter);

        /* Do ABORT because we change our MAC Address. */
        arbFsmRunEventAbort(prAdapter, FALSE);
    }

    return WLAN_STATUS_SUCCESS;

} /* end of wlanoidSetCurrentAddr() */


#if CFG_TCP_IP_CHKSUM_OFFLOAD
/*----------------------------------------------------------------------------*/
/*!
* \brief Setting the checksum offload function.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
* \param[in] pvSetBuffer    Pointer to the buffer that holds the data to be set.
* \param[in] u4SetBufferLen The length of the set buffer.
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*                           bytes read from the set buffer. If the call failed
*                           due to invalid length of the set buffer, returns
*                           the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_LENGTH
* \retval WLAN_STATUS_ADAPTER_NOT_READY
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidSetCSUMOffload (
    IN  P_ADAPTER_T prAdapter,
    IN  PVOID       pvSetBuffer,
    IN  UINT_32     u4SetBufferLen,
    OUT PUINT_32    pu4SetInfoLen
    )
{
    UINT_32 u4CSUMFlags;


    ASSERT(prAdapter);
    ASSERT(pu4SetInfoLen);

    *pu4SetInfoLen = sizeof(UINT_32);

    if (u4SetBufferLen < sizeof(UINT_32)) {
        return WLAN_STATUS_INVALID_LENGTH;
    }

    if (IS_ARB_IN_RFTEST_STATE(prAdapter)) {
        return WLAN_STATUS_SUCCESS;
    }

    if (prAdapter->rAcpiState == ACPI_STATE_D3) {
        DBGLOG(REQ, WARN, ("Fail in set TCP/ IP checksum offload! (Adapter not ready). ACPI=D%d, Radio=%d\n",
                    prAdapter->rAcpiState, prAdapter->fgIsRadioOff));
        return WLAN_STATUS_ADAPTER_NOT_READY;
    }

    ASSERT(pvSetBuffer);

    u4CSUMFlags = *(PUINT_32)pvSetBuffer;

    nicSetCSUMOffload(prAdapter, u4CSUMFlags);

    return WLAN_STATUS_SUCCESS;

}
#endif /* CFG_TCP_IP_CHKSUM_OFFLOAD */


#if CFG_LP_PATTERN_SEARCH_SLT
/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to query the result from Low power SLT.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[out] pvQueryBuf A pointer to the buffer that holds the result of
*                           the query.
* \param[in] u4QueryBufLen The length of the query buffer.
* \param[out] pu4QueryInfoLen If the call is successful, returns the number of
*                            bytes written into the query buffer. If the call
*                            failed due to invalid length of the query buffer,
*                            returns the amount of storage needed.
*
* \return WLAN_STATUS_SUCCESS
* \return WLAN_STATUS_ADAPTER_NOT_READY
* \return WLAN_STATUS_BUFFER_TOO_SHORT
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidQuerySltResult (
    IN P_ADAPTER_T  prAdapter,
    OUT  PVOID    pvQueryBuf,
    IN  UINT_32  u4QueryBufLen,
    OUT PUINT_32 pu4QueryInfoLen
    )
{
    DEBUGFUNC("wlanoidQuerySltResult");


    ASSERT(prAdapter);
    ASSERT(pu4QueryInfoLen);

    if (prAdapter->eSLTModeSel == SLT_MODE_PATTERN_SEARCH) {
        *pu4QueryInfoLen = sizeof(UINT_32);
    }
    else {
        *pu4QueryInfoLen = sizeof(BEACON_RCPI_RECORED_T);
    }

    if (prAdapter->eConnectionStateIndicated != MEDIA_STATE_CONNECTED) {
        DBGLOG(REQ, TRACE, ("Query LP SLT result fail under disconnected state!\n"));
        return WLAN_STATUS_ADAPTER_NOT_READY;
    }


    if (prAdapter->eSLTModeSel == SLT_MODE_PATTERN_SEARCH) {
        if (u4QueryBufLen < sizeof(UINT_32)) {
            return WLAN_STATUS_BUFFER_TOO_SHORT;
        }
        else {
            ASSERT(pvQueryBuf);
            kalMemCopy(pvQueryBuf, &prAdapter->fgPatternSearchMatch, sizeof(BOOLEAN));
        }
    }
    else {
        if (u4QueryBufLen < sizeof(BEACON_RCPI_RECORED_T)) {
            return WLAN_STATUS_BUFFER_TOO_SHORT;
        }
        else {
            ASSERT(pvQueryBuf);
            kalMemCopy(pvQueryBuf, &prAdapter->rBcnRCPIRecord, sizeof(BEACON_RCPI_RECORED_T));
        }
    }

    return WLAN_STATUS_SUCCESS;

} /* end of wlanoidQuerySltResult() */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to set the SLT for Low power test or pattern search test.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[out] pvSetBuffer A pointer to the buffer that holds the data of
*                           the set.
* \param[in] u4SetBufferLen The length of the set buffer.
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*                            bytes read into the query buffer. If the call
*                            failed due to invalid length of the set buffer,
*                            returns the amount of storage needed.
*
* \return WLAN_STATUS_SUCCESS
* \return WLAN_STATUS_ADAPTER_NOT_READY
* \return WLAN_STATUS_BUFFER_TOO_SHORT
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidSetSltMode (
    IN P_ADAPTER_T  prAdapter,
    IN  PVOID    pvSetBuffer,
    IN  UINT_32  u4SetBufferLen,
    OUT PUINT_32 pu4SetInfoLen
)
{
    P_ENUM_SLT_MODE_T peSltMode;
    PARAM_SSID_T rOriSsid;
    UINT_32 u4SetInfoLen;
    DEBUGFUNC("wlanoidSetSltMode");

    ASSERT(prAdapter);
    ASSERT(pvSetBuffer);
    ASSERT(pu4SetInfoLen);

    if (u4SetBufferLen < sizeof(ENUM_SLT_MODE_T)) {
        return WLAN_STATUS_INVALID_LENGTH;
    }
    else {
        *pu4SetInfoLen = sizeof(ENUM_SLT_MODE_T);
    }

    peSltMode = (P_ENUM_SLT_MODE_T)pvSetBuffer;

    switch (*peSltMode) {
    case SLT_MODE_NORMAL:
    case SLT_MODE_LP:
    case SLT_MODE_PATTERN_SEARCH:
        prAdapter->fgPatternSearchMatch = FALSE;
        break;
    default:
        return WLAN_STATUS_INVALID_DATA;
    }

    prAdapter->eSLTModeSel = *peSltMode;
    /* Send the "Abort" event to arbiter. Always TRUE for delaying Disconnect
     * Indication.
     */

     rOriSsid.u4SsidLen = prAdapter->rConnSettings.ucSSIDLen;
     kalMemCopy(rOriSsid.aucSsid,
                prAdapter->rConnSettings.aucSSID,
                rOriSsid.u4SsidLen);


    wlanoidSetDisassociate(prAdapter,
                    NULL,
                    0,
                    &u4SetInfoLen);

    wlanoidSetSsid(prAdapter,
                    &rOriSsid,
                    sizeof(PARAM_SSID_T),
                    &u4SetInfoLen);

//    arbFsmRunEventAbort(prAdapter, FALSE); /* Reset to STANDBY */

//    arbFsmRunEventConnectionReq(prAdapter); /* Reconnected to AP */


    return WLAN_STATUS_SUCCESS;
} /* end of wlanSetSltMode() */

#endif /* CFG_LP_PATTERN_SEARCH_SLT */


/*----------------------------------------------------------------------------*/
/*!
* \brief Setting the IP address for pattern search function.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[in] pvSetBuffer A pointer to the buffer that holds the data to be set.
* \param[in] u4SetBufferLen The length of the set buffer.
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*                           bytes read from the set buffer. If the call failed
*                           due to invalid length of the set buffer, returns
*                           the amount of storage needed.
*
* \return WLAN_STATUS_SUCCESS
* \return WLAN_STATUS_ADAPTER_NOT_READY
* \return WLAN_STATUS_INVALID_LENGTH
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidSetIpAddress (
    IN  P_ADAPTER_T prAdapter,
    IN  PVOID       pvSetBuffer,
    IN  UINT_32     u4SetBufferLen,
    OUT PUINT_32    pu4SetInfoLen
    )
{
    PUINT_8 pucIpAddress;

    ASSERT(prAdapter);
    ASSERT(pvSetBuffer);
    ASSERT(pu4SetInfoLen);

    pucIpAddress = (PUINT_8)pvSetBuffer;

    if (u4SetBufferLen < sizeof(UINT_32)) {
        return WLAN_STATUS_INVALID_LENGTH;
    }

    if (IS_ARB_IN_RFTEST_STATE(prAdapter)) {
        return WLAN_STATUS_SUCCESS;
    }

    if (prAdapter->rAcpiState == ACPI_STATE_D3) {
        DBGLOG(REQ, WARN, ("Fail in set IP Address! (Adapter not ready). ACPI=D%d, Radio=%d\n",
                    prAdapter->rAcpiState, prAdapter->fgIsRadioOff));
        return WLAN_STATUS_ADAPTER_NOT_READY;
    }

    pmSetIpAddress(prAdapter, pucIpAddress);

    return WLAN_STATUS_SUCCESS;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to configure PS related settings for WMM-PS test.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[in] pvSetBuffer A pointer to the buffer that holds the data to be set.
* \param[in] u4SetBufferLen The length of the set buffer.
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*                           bytes read from the set buffer. If the call failed
*                           due to invalid length of the set buffer, returns
*                           the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidSetWiFiWmmPsTest (
    IN P_ADAPTER_T  prAdapter,
    IN  PVOID       pvSetBuffer,
    IN  UINT_32     u4SetBufferLen,
    OUT PUINT_32    pu4SetInfoLen
    )
{
    P_PARAM_CUSTOM_WMM_PS_TEST_STRUC_T prWmmPsTestInfo;
    WLAN_STATUS rStatus = WLAN_STATUS_SUCCESS;
    P_PM_INFO_T prPmInfo;
    P_PM_PROFILE_SETUP_INFO_T prPmProfSetupInfo;

    DEBUGFUNC("wlanoidSetWiFiWmmPsTest");

    ASSERT(prAdapter);
    ASSERT(pvSetBuffer);
    ASSERT(pu4SetInfoLen);

    prPmInfo = &prAdapter->rPmInfo;
    prPmProfSetupInfo = &prPmInfo->rPmProfSetupInfo;

    *pu4SetInfoLen = sizeof(P_PARAM_CUSTOM_WMM_PS_TEST_STRUC_T);

    if (IS_ARB_IN_RFTEST_STATE(prAdapter)) {
        return WLAN_STATUS_SUCCESS;
    }

    prWmmPsTestInfo = (P_PARAM_CUSTOM_WMM_PS_TEST_STRUC_T) pvSetBuffer;

    prPmInfo->ucWmmPsEnterPsAtOnce  = prWmmPsTestInfo->ucIsEnterPsAtOnce;
    prPmInfo->ucWmmPsDisableUcPoll = prWmmPsTestInfo->ucIsDisableUcTrigger;

    /* it will apply the disable trig or not immediately */
    if (prPmInfo->ucWmmPsDisableUcPoll && prPmInfo->ucWmmPsConnWithTrig) {
        NIC_PM_WMM_PS_DISABLE_UC_TRIG(prAdapter, TRUE);
    }
    else {
        NIC_PM_WMM_PS_DISABLE_UC_TRIG(prAdapter, FALSE);
    }

    prPmProfSetupInfo->bmfgApsdEnAc = prWmmPsTestInfo->bmfgApsdEnAc;

    return rStatus;
}   /* wlanoidSetEepromWrite */

/*----------------------------------------------------------------------------*/
/*!
* \brief Query the current regulation domain
*
* \param[in] pvAdapter Pointer to the Adapter structure
* \param[in] pvQueryBuffer A pointer to the buffer that holds the result of the
*   query
* \param[in] u4QueryBufferLen The length of the query buffer
* \param[out] pu4QueryInfoLen If the call is successful, returns the number of
*   bytes written into the query buffer. If the call failed due to invalid
*   length of the query buffer, returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_LENGTH
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidQueryCurrentCountry (
    IN P_ADAPTER_T prAdapter,
    IN PVOID pvQueryBuffer,
    IN UINT_32 u4QueryBufferLen,
    OUT PUINT_32 pu4QueryInfoLen
    )
{
    P_COUNTRY_STRING_ENTRY pCountryStr;
    P_CONNECTION_SETTINGS_T prConnSettings;

    DEBUGFUNC("domainQueryCurrentCountry");

    ASSERT(prAdapter);
    ASSERT(pu4QueryInfoLen);

    prConnSettings = &prAdapter->rConnSettings;

    *pu4QueryInfoLen = sizeof(COUNTRY_STRING_ENTRY);

    /* Check for query buffer length */
    if (u4QueryBufferLen < *pu4QueryInfoLen) {
        WARNLOG(("Invalid length %ld\n", u4QueryBufferLen));
        return WLAN_STATUS_INVALID_LENGTH;
    }

    ASSERT(pvQueryBuffer);
    pCountryStr = (P_COUNTRY_STRING_ENTRY)pvQueryBuffer;

    pCountryStr->aucCountryCode[0] = (UINT_8)(prConnSettings->u2CountryCode >> 8);
    pCountryStr->aucCountryCode[1] =
        (UINT_8)(prConnSettings->u2CountryCode & 0x00FF);

    pCountryStr->aucEnvironmentCode[0] = ' ';
    pCountryStr->aucEnvironmentCode[0] = '\0';

#if DBG
    if (pCountryStr->aucCountryCode[0] >= 0x20 &&
        pCountryStr->aucCountryCode[1] >= 0x20) {
        DBGLOG(REQ,
            INFO,
            ("Current country: %c%c\n",
            pCountryStr->aucCountryCode[0],
            pCountryStr->aucCountryCode[1]));
    }
    else {
        DBGLOG(REQ,
            INFO,
            ("Current country: 0x%02x%02x\n",
            pCountryStr->aucCountryCode[0],
            pCountryStr->aucCountryCode[1]));
    }
#endif

    return WLAN_STATUS_SUCCESS;
} /* domainQueryCurrentCountry */

/*----------------------------------------------------------------------------*/
/*!
* \brief To set the regulation domain from I/O control method
*
* \param[in] pvAdapter Pointer to the adapter structure
* \param[in] pvSetBuffer pointer to the buffer that holds the data to be set
* \param[in] u4SetBufferLen The length of the set buffer
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*   bytes read from the set buffer. If the call failed due to invalid length of
*   the set buffer, returns the amount of storage needed.
*
* \retval WLAN_STATUS_INVALID_LENGTH If set buffer length is too small.
* \retval WLAN_STATUS_INVALID_DATA If the country code is not supported.
* \retval WLAN_STATUS_SUCCESS The new country code is accepted or unchanged.
*
* \note The control program has to disconnect with network before issuing this
*   OID and restart connecting procedure again. Multi domain support will also
*   be disabled.
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidSetCurrentCountry (
    IN P_ADAPTER_T prAdapter,
    IN PVOID pvSetBuffer,
    IN UINT_32 u4SetBufferLen,
    OUT PUINT_32 pu4SetInfoLen
    )
{
    P_COUNTRY_STRING_ENTRY pCountryStr;
    UINT_16 countryCode;
    P_CONNECTION_SETTINGS_T prConnSettings;

    DEBUGFUNC("domainSetCurrentCountry");

    ASSERT(prAdapter);
    ASSERT(pu4SetInfoLen);
    prConnSettings = &prAdapter->rConnSettings;

    if (u4SetBufferLen < 2) {
        WARNLOG(("Invalid length %ld\n", u4SetBufferLen));
        return WLAN_STATUS_INVALID_LENGTH;
    }

    *pu4SetInfoLen = sizeof(COUNTRY_STRING_ENTRY);

    ASSERT(pvSetBuffer);
    pCountryStr = (P_COUNTRY_STRING_ENTRY)pvSetBuffer;

    countryCode = ((UINT_16)pCountryStr->aucCountryCode[0] << 8) |
                   (UINT_16)pCountryStr->aucCountryCode[1];

    DBGLOG(REQ,
        INFO,
        ("New regulatory domain: %c%c\n",
        pCountryStr->aucCountryCode[0],
        pCountryStr->aucCountryCode[1]));

#if CFG_SUPPORT_802_11D
    if (prConnSettings->fgMultiDomainCapabilityEnabled) {
        prConnSettings->u2CountryCode = countryCode;
        /* Not to apply country setting!! */
    }
    else {
        prConnSettings->u2CountryCode = countryCode;
        nicSetupOpChnlList(prAdapter, prConnSettings->u2CountryCode, FALSE);
    }
#else
    prConnSettings->u2CountryCode = countryCode;
    nicSetupOpChnlList(prAdapter, prConnSettings->u2CountryCode, FALSE);
#endif

    return WLAN_STATUS_SUCCESS;
} /* domainSetCurrentCountry */


#if CFG_SUPPORT_802_11D
/*----------------------------------------------------------------------------*/
/*!
* \brief To query the current multi-domain capability.
*
* \param[in] pvAdapter Pointer to the MP_ADAPTER structure
* \param[in] pvQueryBuffer A pointer to the buffer that holds the result of the
*   query
* \param[in] u4QueryBufferLen The length of the query buffer
* \param[out] pu4QueryInfoLen If the call is successful, returns the number of
*   bytes written into the query buffer. If the call failed due to invalid
*   length of the query buffer, returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_LENGTH
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidQueryMultiDomainCap (
    IN  P_ADAPTER_T prAdapter,
    OUT PVOID       pvQueryBuffer,
    IN  UINT_32     u4QueryBufferLen,
    OUT PUINT_32    pu4QueryInfoLen
    )
{
    P_CONNECTION_SETTINGS_T prConnSettings;

    DEBUGFUNC("domainQueryMultiDomainCap");

    ASSERT(prAdapter);
    ASSERT(pu4QueryInfoLen);

    prConnSettings = &prAdapter->rConnSettings;

    *pu4QueryInfoLen = sizeof(PARAM_MULTI_DOMAIN_CAPABILITY);

    /* Check for query buffer length */
    if (u4QueryBufferLen < *pu4QueryInfoLen) {
        WARNLOG(("Invalid length %ld\n", u4QueryBufferLen));
        return WLAN_STATUS_INVALID_LENGTH;
    }

    ASSERT(pvQueryBuffer);
    if (FALSE != prConnSettings->fgMultiDomainCapabilityEnabled) {
        DBGLOG(REQ, INFO, ("Current multi-domain cap: Enabled\n"));
        *(P_PARAM_MULTI_DOMAIN_CAPABILITY)pvQueryBuffer =
            ParamMultiDomainCapEnabled;
    }
    else {
        DBGLOG(REQ, INFO, ("Current multi-domain cap: Disabled\n"));
        *(P_PARAM_MULTI_DOMAIN_CAPABILITY)pvQueryBuffer =
            ParamMultiDomainCapDisabled;
    }

    return WLAN_STATUS_SUCCESS;
} /* domainQueryMultiDomainCap */

/*----------------------------------------------------------------------------*/
/*!
* \brief Set the multi-domain capability
*
* \param[in] pvAdapter Pointer to the Adapter structure
* \param[in] pvSetBuffer A pointer to the buffer that holds the data to be set
* \param[in] u4SetBufferLen The length of the set buffer
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*   bytes read from the set buffer. If the call failed due to invalid length of
*   the set buffer, returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_DATA If new setting value is wrong.
* \retval WLAN_STATUS_INVALID_LENGTH
*
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidSetMultiDomainCap (
    IN  P_ADAPTER_T prAdapter,
    IN  PVOID       pvSetBuffer,
    IN  UINT_32     u4SetBufferLen,
    OUT PUINT_32    pu4SetInfoLen
    )
{
    PARAM_MULTI_DOMAIN_CAPABILITY paramMultiDomain;
    P_CONNECTION_SETTINGS_T prConnSettings;

    DEBUGFUNC("domainSetMultiDomainCap");

    ASSERT(prAdapter);
    ASSERT(pu4SetInfoLen);

    prConnSettings = &prAdapter->rConnSettings;

    *pu4SetInfoLen = sizeof(PARAM_MULTI_DOMAIN_CAPABILITY);

    /* Check for set buffer length */
    if (u4SetBufferLen < *pu4SetInfoLen) {
        WARNLOG(("Invalid length %ld\n", u4SetBufferLen));
        return WLAN_STATUS_INVALID_LENGTH;
    }

    ASSERT(pvSetBuffer);
    paramMultiDomain = *(P_PARAM_MULTI_DOMAIN_CAPABILITY)pvSetBuffer;

    if (ParamMultiDomainCapEnabled == paramMultiDomain) {
        if (FALSE != prConnSettings->fgMultiDomainCapabilityEnabled) {
            /* The same as current setting, return SUCCESS. */
            return WLAN_STATUS_SUCCESS;
        }
    }
    else if (ParamMultiDomainCapDisabled == paramMultiDomain){
        if (FALSE == prConnSettings->fgMultiDomainCapabilityEnabled) {
            /* The same as current setting, return SUCCESS. */
            return WLAN_STATUS_SUCCESS;
        }
    }
    else {
        DBGLOG(REQ,
            TRACE,
            ("Invalid multi-domain cap: %ld\n",
            *(PUINT_32)pvSetBuffer));

        return WLAN_STATUS_INVALID_DATA;
    }

    if (ParamMultiDomainCapEnabled == paramMultiDomain) {
        DBGLOG(REQ, INFO, ("New multi-domain cap: Enabled\n"));

        prConnSettings->fgMultiDomainCapabilityEnabled = TRUE;
    }
    else {
        ASSERT(ParamMultiDomainCapDisabled == paramMultiDomain);
        DBGLOG(REQ, INFO, ("New multi-domain cap: Disabled\n"));

        prConnSettings->fgMultiDomainCapabilityEnabled = FALSE;
    }

    return WLAN_STATUS_SUCCESS;
} /* domainSetMultiDomainCap */
#endif

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to set GPIO2 as gpi, INT_N or daisy chain.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
* \param[in] pvSetBuffer A pointer to the buffer that holds the data to be set.
* \param[in] u4SetBufferLen The length of the set buffer.
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*                          bytes read from the set buffer. If the call failed
*                          due to invalid length of the set buffer, returns
*                          the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_LENGTH
* \retval WLAN_STATUS_INVALID_DATA
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidSetGPIO2Mode (
    IN  P_ADAPTER_T  prAdapter,
    IN  PVOID    pvSetBuffer,
    IN  UINT_32  u4SetBufferLen,
    OUT PUINT_32 pu4SetInfoLen
    )
{
    P_CONNECTION_SETTINGS_T     prConnSettings;

    DEBUGFUNC("wlanoidSetGPIO2Mode");

    ASSERT(prAdapter);
    ASSERT(pu4SetInfoLen);

    prConnSettings = &prAdapter->rConnSettings;

    *pu4SetInfoLen = sizeof(ENUM_PARAM_GPIO2_MODE_T);

    if (u4SetBufferLen != sizeof(ENUM_PARAM_GPIO2_MODE_T)) {
        return WLAN_STATUS_INVALID_LENGTH;
    }

    ASSERT(pvSetBuffer);
    if (*(P_ENUM_PARAM_GPIO2_MODE_T)pvSetBuffer > GPIO2_MODE_DAISY_INPUT) {
        return WLAN_STATUS_INVALID_DATA;
    }

    if (prAdapter->rAcpiState == ACPI_STATE_D3) {
        DBGLOG(REQ, WARN, ("Fail to set GPIO2 setting because of ACPI_D3\n"));
        return WLAN_STATUS_ADAPTER_NOT_READY;
    }

    /* Store parameters to connSetting for chip reset path */
    prConnSettings->eGPIO2_Mode = *(P_ENUM_PARAM_GPIO2_MODE_T) pvSetBuffer;
    nicSetGPIO2Mode(prAdapter, prConnSettings->eGPIO2_Mode);

    return WLAN_STATUS_SUCCESS;

} /* wlanoidSetGPIO2Mode */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to set the continuous poll profile, which is
*        designed for BT/ Wi-Fi coexistence mechanism.
*        Driver will issue poll packet on every poll interval.
*
*        Note:
*        It will oversede "power save profile" and "VoIP profile" setting.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
* \param[in] pvSetBuffer A pointer to the buffer that holds the data to be set.
* \param[in] u4SetBufferLen The length of the set buffer.
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*                          bytes read from the set buffer. If the call failed
*                          due to invalid length of the set buffer, returns
*                          the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_LENGTH
* \retval WLAN_STATUS_INVALID_DATA
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidSetContinuousPollProfile (
    IN  P_ADAPTER_T  prAdapter,
    IN  PVOID    pvSetBuffer,
    IN  UINT_32  u4SetBufferLen,
    OUT PUINT_32 pu4SetInfoLen
    )
{
    P_CONNECTION_SETTINGS_T     prConnSettings;

    DEBUGFUNC("wlanoidSetContinuousPollProfile");

    ASSERT(prAdapter);
    ASSERT(pu4SetInfoLen);

    prConnSettings = &prAdapter->rConnSettings;

    *pu4SetInfoLen = sizeof(PARAM_CONTINUOUS_POLL_T);

    if (u4SetBufferLen != sizeof(PARAM_CONTINUOUS_POLL_T)) {
        return WLAN_STATUS_INVALID_LENGTH;
    }

    if (IS_ARB_IN_RFTEST_STATE(prAdapter)) {
        return WLAN_STATUS_SUCCESS;
    }

    if (prAdapter->rAcpiState == ACPI_STATE_D3) {
        DBGLOG(REQ, WARN, ("Fail to set continuous poll because of ACPI_D3\n"));
        return WLAN_STATUS_ADAPTER_NOT_READY;
    }

    ASSERT(pvSetBuffer);
    /* Store parameters to connSetting */
    prConnSettings->u4ContPollIntv = *(PUINT_32) pvSetBuffer;

    if (prConnSettings->u4ContPollIntv) {
        pmEnableContinuousPollingFunc(prAdapter);
    }
    else {
        pmDisableContinuousPollingFunc(prAdapter);
    }

    return WLAN_STATUS_SUCCESS;

} /* wlanoidSetContinuousPollProfile */

#if defined(LINUX)
VOID
wlanoidQueryDrvStatusForLinuxProc (
    IN P_ADAPTER_T prAdapter,
    IN PUINT_8 pucBuffer,
    OUT PUINT_32 pu4Count
    )
{
    UINT_32 u4TotalCount = 0;
    UINT_32 u4Count;

    ASSERT(prAdapter);

    nicTxQueryStatus(prAdapter, pucBuffer, &u4Count);
    u4TotalCount += u4Count;

    pucBuffer += u4Count;
    nicRxQueryStatus(prAdapter, pucBuffer, &u4Count);
    u4TotalCount += u4Count;

#if CFG_TX_DBG_MGT_BUF
    pucBuffer += u4Count;
    mgtBufQueryStatus(prAdapter, pucBuffer, &u4Count);
    u4TotalCount += u4Count;
#endif /* CFG_TX_DBG_MGT_BUF */

#if CFG_DBG_STA_RECORD
    pucBuffer += u4Count;
    staRecQueryStatus(prAdapter, pucBuffer, &u4Count);
    u4TotalCount += u4Count;
#endif /* CFG_DBG_STA_RECORD */

    *pu4Count = u4TotalCount;

    return;
}

VOID
wlanoidQueryRxStatisticsForLinuxProc (
    IN P_ADAPTER_T prAdapter,
    IN PUINT_8 pucBuffer,
    OUT PUINT_32 pu4Count
    )
{
    UINT_32 u4Count;

    ASSERT(prAdapter);

    nicRxQueryStatistics(prAdapter, pucBuffer, &u4Count);

    *pu4Count = u4Count;

    return;
}


VOID
wlanoidSetRxStatisticsForLinuxProc (
    IN P_ADAPTER_T prAdapter
    )
{

    ASSERT(prAdapter);

    nicRxSetStatistics(prAdapter);

    return;
}


VOID
wlanoidQueryTxStatisticsForLinuxProc (
    IN P_ADAPTER_T prAdapter,
    IN PUINT_8 pucBuffer,
    OUT PUINT_32 pu4Count
    )
{
    UINT_32 u4Count;

    ASSERT(prAdapter);

    nicTxQueryStatistics(prAdapter, pucBuffer, &u4Count);

    *pu4Count = u4Count;

    return;
}


VOID
wlanoidSetTxStatisticsForLinuxProc (
    IN P_ADAPTER_T prAdapter
    )
{

    ASSERT(prAdapter);
    nicTxSetStatistics(prAdapter);

    return;
}

#endif
#if PTA_ENABLED
/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to set BT profile or BT information and the
*        driver will set the built-in PTA configuration into chip.
*
*
* \param[in] prAdapter      Pointer to the Adapter structure.
* \param[in] pvSetBuffer A pointer to the buffer that holds the data to be set.
* \param[in] u4SetBufferLen The length of the set buffer.
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*                          bytes read from the set buffer. If the call failed
*                          due to invalid length of the set buffer, returns
*                          the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_LENGTH
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidSetBT (
    IN  P_ADAPTER_T prAdapter,
    IN  PVOID       pvSetBuffer,
    IN  UINT_32     u4SetBufferLen,
    OUT PUINT_32    pu4SetInfoLen
    )
{

    P_PTA_IPC_T   prPtaIpc;


    DEBUGFUNC("wlanoidSetBT");

    ASSERT(prAdapter);
    ASSERT(pu4SetInfoLen);

    *pu4SetInfoLen = sizeof(PTA_IPC_T);
    if (u4SetBufferLen != sizeof(PTA_IPC_T)) {
        WARNLOG(("Invalid length %ld\n", u4SetBufferLen));
        return WLAN_STATUS_INVALID_LENGTH;
    }

    if (IS_ARB_IN_RFTEST_STATE(prAdapter)) {
        return WLAN_STATUS_SUCCESS;
    }

    if (prAdapter->rAcpiState == ACPI_STATE_D3) {
        DBGLOG(REQ, WARN, ("Fail to set BT profile because of ACPI_D3\n"));
        return WLAN_STATUS_ADAPTER_NOT_READY;
    }

    ASSERT(pvSetBuffer);
    prPtaIpc = (P_PTA_IPC_T)pvSetBuffer;

    switch (prPtaIpc->ucCmd) {
    case BT_CMD_PROFILE:
        nicPTASetProfile(prAdapter, &prPtaIpc->u.rProfile);
        break;

    case BT_CMD_UPDATE:
        nicPTAUpdateParams(prAdapter, prPtaIpc->u.aucBTPParams);
        break;

    default:
        ASSERT(0);
        break;
    }

    return WLAN_STATUS_SUCCESS;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to query current BT profile and BTCR values
*
* \param[in] prAdapter          Pointer to the Adapter structure.
* \param[in] pvQueryBuffer      Pointer to the buffer that holds the result of
*                               the query.
* \param[in] u4QueryBufferLen   The length of the query buffer.
* \param[out] pu4QueryInfoLen   If the call is successful, returns the number of
*                               bytes written into the query buffer. If the call
*                               failed due to invalid length of the query buffer,
*                               returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_LENGTH
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidQueryBT (
    IN  P_ADAPTER_T prAdapter,
    OUT PVOID       pvQueryBuffer,
    IN  UINT_32     u4QueryBufferLen,
    OUT PUINT_32    pu4QueryInfoLen
    )
{
    P_PARAM_PTA_IPC_T prPtaIpc;
    UINT_32 u4QueryBuffLen;

    ASSERT(prAdapter);
    ASSERT(pu4QueryInfoLen);
    if (u4QueryBufferLen) {
        ASSERT(pvQueryBuffer);
    }

    *pu4QueryInfoLen = sizeof(PARAM_PTA_IPC_T);

    /* Check for query buffer length */
    if (u4QueryBufferLen != sizeof(PARAM_PTA_IPC_T)) {
        DBGLOG(REQ, WARN, ("Invalid length %lu\n", u4QueryBufferLen));
        return WLAN_STATUS_INVALID_LENGTH;
    }

    ASSERT(pvQueryBuffer);
    prPtaIpc = (P_PARAM_PTA_IPC_T)pvQueryBuffer;
    prPtaIpc->ucCmd = BT_CMD_PROFILE;
    prPtaIpc->ucLen = sizeof(prPtaIpc->u);
    nicPtaGetProfile(prAdapter, (PUINT_8)&prPtaIpc->u, &u4QueryBuffLen);

    return WLAN_STATUS_SUCCESS;
}


WLAN_STATUS
wlanoidQueryBtSingleAntenna (
    IN  P_ADAPTER_T prAdapter,
    OUT PVOID       pvQueryBuffer,
    IN  UINT_32     u4QueryBufferLen,
    OUT PUINT_32    pu4QueryInfoLen
    )
{
    P_PTA_INFO_T prPtaInfo;
    PUINT_32 pu4SingleAntenna;

    ASSERT(prAdapter);
    ASSERT(pu4QueryInfoLen);
    if (u4QueryBufferLen) {
        ASSERT(pvQueryBuffer);
    }

    *pu4QueryInfoLen = sizeof(UINT_32);

    /* Check for query buffer length */
    if (u4QueryBufferLen != sizeof(UINT_32)) {
        DBGLOG(REQ, WARN, ("Invalid length %lu\n", u4QueryBufferLen));
        return WLAN_STATUS_INVALID_LENGTH;
    }

    ASSERT(pvQueryBuffer);

    prPtaInfo = &prAdapter->rPtaInfo;
    pu4SingleAntenna = (PUINT_32)pvQueryBuffer;

    if(prPtaInfo->fgSingleAntenna) {
        //printk(KERN_WARNING DRV_NAME"Q Single Ant = 1\r\n");
        *pu4SingleAntenna = 1;
    } else {
        //printk(KERN_WARNING DRV_NAME"Q Single Ant = 0\r\n");
        *pu4SingleAntenna = 0;
    }

    return WLAN_STATUS_SUCCESS;
}

WLAN_STATUS
wlanoidQueryPta (
    IN  P_ADAPTER_T prAdapter,
    OUT PVOID       pvQueryBuffer,
    IN  UINT_32     u4QueryBufferLen,
    OUT PUINT_32    pu4QueryInfoLen
    )
{
    P_PTA_INFO_T prPtaInfo;
    PUINT_32 pu4Pta;

    ASSERT(prAdapter);
    ASSERT(pu4QueryInfoLen);
    if (u4QueryBufferLen) {
        ASSERT(pvQueryBuffer);
    }

    *pu4QueryInfoLen = sizeof(UINT_32);

    /* Check for query buffer length */
    if (u4QueryBufferLen != sizeof(UINT_32)) {
        DBGLOG(REQ, WARN, ("Invalid length %lu\n", u4QueryBufferLen));
        return WLAN_STATUS_INVALID_LENGTH;
    }

    ASSERT(pvQueryBuffer);

    prPtaInfo = &prAdapter->rPtaInfo;
    pu4Pta = (PUINT_32)pvQueryBuffer;

    if(prPtaInfo->fgEnabled) {
        //printk(KERN_WARNING DRV_NAME"PTA = 1\r\n");
        *pu4Pta = 1;
    } else {
        //printk(KERN_WARNING DRV_NAME"PTA = 0\r\n");
        *pu4Pta = 0;
    }

    return WLAN_STATUS_SUCCESS;
}

WLAN_STATUS
wlanoidSetBtSingleAntenna (
    IN  P_ADAPTER_T prAdapter,
    IN  PVOID       pvSetBuffer,
    IN  UINT_32     u4SetBufferLen,
    OUT PUINT_32    pu4SetInfoLen
    )
{

    PUINT_32        pu4SingleAntenna;
    UINT_32         u4SingleAntenna;
    P_PTA_INFO_T    prPtaInfo;

    ASSERT(prAdapter);
    ASSERT(pu4SetInfoLen);

    prPtaInfo = &prAdapter->rPtaInfo;

    *pu4SetInfoLen = sizeof(UINT_32);
    if (u4SetBufferLen != sizeof(UINT_32)) {
        return WLAN_STATUS_INVALID_LENGTH;
    }

    if (IS_ARB_IN_RFTEST_STATE(prAdapter)) {
        return WLAN_STATUS_SUCCESS;
    }

    if (prAdapter->rAcpiState == ACPI_STATE_D3) {
        DBGLOG(REQ, WARN, ("Fail to set antenna because of ACPI_D3\n"));
        return WLAN_STATUS_ADAPTER_NOT_READY;
    }

    ASSERT(pvSetBuffer);
    pu4SingleAntenna = (PUINT_32)pvSetBuffer;
    u4SingleAntenna = *pu4SingleAntenna;

    if (u4SingleAntenna == 0) {
        //printk(KERN_WARNING DRV_NAME"Set Single Ant = 0\r\n");
        prPtaInfo->fgSingleAntenna = FALSE;
    } else {
        //printk(KERN_WARNING DRV_NAME"Set Single Ant = 1\r\n");
        prPtaInfo->fgSingleAntenna = TRUE;
    }
    ptaFsmRunEventSetConfig(prAdapter, &prPtaInfo->rPtaParam);

    return WLAN_STATUS_SUCCESS;
}

WLAN_STATUS
wlanoidSetPta (
    IN  P_ADAPTER_T prAdapter,
    IN  PVOID       pvSetBuffer,
    IN  UINT_32     u4SetBufferLen,
    OUT PUINT_32    pu4SetInfoLen
    )
{
    PUINT_32    pu4PtaCtrl;
    UINT_32     u4PtaCtrl;

    ASSERT(prAdapter);
    ASSERT(pu4SetInfoLen);

    *pu4SetInfoLen = sizeof(UINT_32);
    if (u4SetBufferLen != sizeof(UINT_32)) {
        return WLAN_STATUS_INVALID_LENGTH;
    }

    if (IS_ARB_IN_RFTEST_STATE(prAdapter)) {
        return WLAN_STATUS_SUCCESS;
    }

    if (prAdapter->rAcpiState == ACPI_STATE_D3) {
        DBGLOG(REQ, WARN, ("Fail to set BT setting because of ACPI_D3\n"));
        return WLAN_STATUS_ADAPTER_NOT_READY;
    }

    ASSERT(pvSetBuffer);
    pu4PtaCtrl = (PUINT_32)pvSetBuffer;
    u4PtaCtrl = *pu4PtaCtrl;

    if (u4PtaCtrl == 0) {
        //printk(KERN_WARNING DRV_NAME"Set Pta= 0\r\n");
        nicPtaSetFunc(prAdapter, FALSE);
    } else {
        //printk(KERN_WARNING DRV_NAME"Set Pta= 1\r\n");
        nicPtaSetFunc(prAdapter, TRUE);
    }

    return WLAN_STATUS_SUCCESS;
}
/* Renbang : ++ (20100319)*/
#if 1
WLAN_STATUS
wlanoidSetFixedRxGain (
    IN  P_ADAPTER_T prAdapter,
    IN  PVOID       pvSetBuffer,
    IN  UINT_32     u4SetBufferLen,
    OUT PUINT_32    pu4SetInfoLen
    )
{
    PUINT_32    pu4RxFixedGain;
    UINT_32     u4RxFixedGain;

    ASSERT(prAdapter);
    ASSERT(pu4SetInfoLen);

    *pu4SetInfoLen = sizeof(UINT_32);
    if (u4SetBufferLen != sizeof(UINT_32)) {
        return WLAN_STATUS_INVALID_LENGTH;
    }

    if (prAdapter->rAcpiState == ACPI_STATE_D3) {
        DBGLOG(REQ, WARN, ("Fail to set BT setting because of ACPI_D3\r\n"));
        return WLAN_STATUS_ADAPTER_NOT_READY;
    }

    ASSERT(pvSetBuffer);
    pu4RxFixedGain = (PUINT_32)pvSetBuffer;
    u4RxFixedGain = *pu4RxFixedGain;

    if (u4RxFixedGain == 0) {
        printk(KERN_WARNING DRV_NAME"[BWCS]Disable RX fixed gain\r\n");
        halBBEnableFixedRxGain(prAdapter, FALSE);
    } else {
        printk(KERN_WARNING DRV_NAME"[BWCS]Enable RX fixed gain\r\n");
        halBBEnableFixedRxGain(prAdapter, TRUE);
    }

    return WLAN_STATUS_SUCCESS;
}
#endif
#endif
/* Renbang : -- (20100319)*/

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to query current value of continuous poll
*        interval
*
* \param[in] prAdapter          Pointer to the Adapter structure.
* \param[in] pvQueryBuffer      Pointer to the buffer that holds the result of
*                               the query.
* \param[in] u4QueryBufferLen   The length of the query buffer.
* \param[out] pu4QueryInfoLen   If the call is successful, returns the number of
*                               bytes written into the query buffer. If the call
*                               failed due to invalid length of the query buffer,
*                               returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_LENGTH
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidQueryContinuousPollInterval (
    IN  P_ADAPTER_T prAdapter,
    OUT PVOID       pvQueryBuffer,
    IN  UINT_32     u4QueryBufferLen,
    OUT PUINT_32    pu4QueryInfoLen
    )
{
    P_CONNECTION_SETTINGS_T prConnSetting;
    PUINT_32 pu4ContPollIntv;


    ASSERT(prAdapter);
    ASSERT(pu4QueryInfoLen);
    if (u4QueryBufferLen) {
        ASSERT(pvQueryBuffer);
    }

    *pu4QueryInfoLen = sizeof(UINT_32);

    /* Check for query buffer length */
    if (u4QueryBufferLen < *pu4QueryInfoLen) {
        DBGLOG(REQ, WARN, ("Invalid length %lu\n", u4QueryBufferLen));
        return WLAN_STATUS_INVALID_LENGTH;
    }

    ASSERT(pvQueryBuffer);

    prConnSetting = &prAdapter->rConnSettings;
    pu4ContPollIntv = (PUINT_32)pvQueryBuffer;


    *pu4ContPollIntv = prConnSetting->u4ContPollIntv;
    *pu4QueryInfoLen = sizeof(UINT_32);
    return WLAN_STATUS_SUCCESS;

}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to query beacon detection function enable/disable state
*        This is mainly designed for usage under BT inquiry state (disable function).
*
* \param[in] prAdapter          Pointer to the Adapter structure.
* \param[in] pvQueryBuffer      Pointer to the buffer that holds the result of
*                               the query.
* \param[in] u4QueryBufferLen   The length of the query buffer.
* \param[out] pu4QueryInfoLen   If the call is successful, returns the number of
*                               bytes written into the query buffer. If the call
*                               failed due to invalid length of the query buffer,
*                               returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_LENGTH
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidQueryDisableBeaconDetectionFunc (
    IN  P_ADAPTER_T prAdapter,
    OUT PVOID       pvQueryBuffer,
    IN  UINT_32     u4QueryBufferLen,
    OUT PUINT_32    pu4QueryInfoLen
    )
{
    P_PM_INFO_T                 prPmInfo;
    PUINT_32                    pu4IsBeaconTimeoutDetectionDisabled;

    ASSERT(prAdapter);
    ASSERT(pu4QueryInfoLen);
    if (u4QueryBufferLen) {
        ASSERT(pvQueryBuffer);
    }

    *pu4QueryInfoLen = sizeof(UINT_32);

    /* Check for query buffer length */
    if (u4QueryBufferLen < *pu4QueryInfoLen) {
        DBGLOG(REQ, WARN, ("Invalid length %lu\n", u4QueryBufferLen));
        return WLAN_STATUS_INVALID_LENGTH;
    }

    ASSERT(pvQueryBuffer);

    prPmInfo = &prAdapter->rPmInfo;
    pu4IsBeaconTimeoutDetectionDisabled = (PUINT_32)pvQueryBuffer;

    *pu4IsBeaconTimeoutDetectionDisabled = (UINT_32)prPmInfo->fgIsBeaconTimeoutDetectionDisabled;

    return WLAN_STATUS_SUCCESS;
} /* wlanoidQueryBeaconDetectionFunc */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to set beacon detection function enable/disable state
*        This is mainly designed for usage under BT inquiry state (disable function).
*
* \param[in] pvAdapter Pointer to the Adapter structure
* \param[in] pvSetBuffer A pointer to the buffer that holds the data to be set
* \param[in] u4SetBufferLen The length of the set buffer
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*   bytes read from the set buffer. If the call failed due to invalid length of
*   the set buffer, returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_DATA If new setting value is wrong.
* \retval WLAN_STATUS_INVALID_LENGTH
*
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidSetDisableBeaconDetectionFunc (
    IN  P_ADAPTER_T prAdapter,
    IN  PVOID       pvSetBuffer,
    IN  UINT_32     u4SetBufferLen,
    OUT PUINT_32    pu4SetInfoLen
    )
{
    PBOOLEAN pfgDisableBeaconDection;
    P_CONNECTION_SETTINGS_T prConnectionSetting;

    ASSERT(prAdapter);
    ASSERT(pvSetBuffer);
    ASSERT(pu4SetInfoLen);

    pfgDisableBeaconDection = (PBOOLEAN)pvSetBuffer;
    prConnectionSetting = &prAdapter->rConnSettings;

    if (u4SetBufferLen < sizeof(UINT_32)) {
        return WLAN_STATUS_INVALID_LENGTH;
    }

    if (IS_ARB_IN_RFTEST_STATE(prAdapter)) {
        return WLAN_STATUS_SUCCESS;
    }

    if (prAdapter->rAcpiState == ACPI_STATE_D3) {
        DBGLOG(REQ, WARN, ("Fail in set beacon timeout detection! (Adapter not ready). ACPI=D%d, Radio=%d\n",
                    prAdapter->rAcpiState, prAdapter->fgIsRadioOff));
        return WLAN_STATUS_ADAPTER_NOT_READY;
    }

    if (*pfgDisableBeaconDection == TRUE) {
        /* Enter PSP-MAX mode */
        pmFsmRunEventSetPowerSaveProfile(prAdapter, ENUM_PSP_CONTINUOUS_POWER_SAVE);

        /* Control the function of beacon timeout detection */
        pmDisableBeaconTimeoutDetectionFunc(prAdapter, TRUE);
    } else {
        /* Restore to original PSP mode */
        pmFsmRunEventSetPowerSaveProfile(prAdapter,
                                         aPowerModeToPwrSaveProfMapping[prConnectionSetting->rPwrMode]);

        /* Control the function of beacon timeout detection */
        pmDisableBeaconTimeoutDetectionFunc(prAdapter, FALSE);
    }

    return WLAN_STATUS_SUCCESS;
} /* wlanoidSetBeaconDetectionFunc */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to disable/enable the AP selection policy
*          For WPS handshake, if the AP set open networking, the wzc profile have modify as WEP
*          Thus, 802.1x can select for EAP type.
*          This is a workaround method, even the encrypt status set enable, but the flag will skip
*          the privacy check, use open networking method to progress the WPS handshake.
*
* \param[in] prAdapter Pointer to the Adapter structure
* \param[in] pvSetBuffer A pointer to the buffer that holds the data to be set
* \param[in] u4SetBufferLen The length of the set buffer
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*   bytes read from the set buffer. If the call failed due to invalid length of
*   the set buffer, returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_DATA If new setting value is wrong.
* \retval WLAN_STATUS_INVALID_LENGTH
*
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidSetDisablePriavcyCheck (
    IN  P_ADAPTER_T   prAdapter,
    IN  PVOID         pvSetBuffer,
    IN  UINT_32       u4SetBufferLen,
    OUT PUINT_32      pu4SetInfoLen
    )
{
    UINT_32           u4Value;

    ASSERT(prAdapter);
    ASSERT(pvSetBuffer);
    ASSERT(pu4SetInfoLen);

    u4Value = *(PUINT_32)pvSetBuffer;

    if (u4Value >= 1)
        prAdapter->rSecInfo.fgPrivacyCheckDisable = TRUE;
    else
        prAdapter->rSecInfo.fgPrivacyCheckDisable = FALSE;

    return WLAN_STATUS_SUCCESS;
}    
/* Renbang : ++ (20100319)*/
#if CFG_SUPPORT_EXT_CONFIG
/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to query EEPROM value.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
* \param[out] pvQueryBuf A pointer to the buffer that holds the result of
*                           the query.
* \param[in] u4QueryBufLen The length of the query buffer.
* \param[out] pu4QueryInfoLen If the call is successful, returns the number of
*                            bytes written into the query buffer. If the call
*                            failed due to invalid length of the query buffer,
*                            returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_FAILURE
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidQueryNvramRead (
    IN  P_ADAPTER_T       prAdapter,
    OUT PVOID             pvQueryBuffer,
    IN  UINT_32           u4QueryBufferLen,
    OUT PUINT_32          pu4QueryInfoLen
    )
{

    P_PARAM_CUSTOM_EEPROM_RW_STRUC_T prEepromRdInfo;
    UINT_16     u2Data;
    BOOLEAN     fgStatus;
    WLAN_STATUS rStatus = WLAN_STATUS_SUCCESS;

    DEBUGFUNC("wlanoidQueryEepromRead");

    ASSERT(prAdapter);
    ASSERT(pvQueryBuffer);
    ASSERT(pu4QueryInfoLen);

    prEepromRdInfo = (P_PARAM_CUSTOM_EEPROM_RW_STRUC_T) pvQueryBuffer;

	if( prAdapter->prGlueInfo->eCfgSrcType != CFG_SRC_TYPE_NVRAM )
	{
        DBGLOG(REQ, ERROR, ("NVRAM is not current cfg src!!\r\n"));
		return WLAN_STATUS_FAILURE;
	}

	if(prEepromRdInfo->ucEepromMethod == PARAM_EEPROM_READ_METHOD_READ) {
        fgStatus = cfgDataRead16(prAdapter,
                            prEepromRdInfo->ucEepromIndex,
                            &u2Data
                            );
        if(fgStatus){
            prEepromRdInfo->u2EepromData = u2Data;
            DBGLOG(REQ, INFO, ("NVRAM Read: index=%#X, data=%#02X\r\n",
                    prEepromRdInfo->ucEepromIndex, u2Data));
        }
        else{
            DBGLOG(REQ, ERROR, ("NVRAM Read Failed: index=%#x.\r\n",
                    prEepromRdInfo->ucEepromIndex));
            rStatus = WLAN_STATUS_FAILURE;
        }
    }
    else if (prEepromRdInfo->ucEepromMethod == PARAM_EEPROM_READ_METHOD_GETSIZE) {
        prEepromRdInfo->u2EepromData = (UINT_16)(prAdapter->prGlueInfo->u4ExtCfgLength);
        DBGLOG(REQ, INFO, ("EEPROM size =%d\r\n", prEepromRdInfo->u2EepromData));
        DBGLOG(REQ, INFO, ("EEPROM size =%d\r\n", prAdapter->prGlueInfo->u4ExtCfgLength));
    }

    *pu4QueryInfoLen = sizeof(PARAM_CUSTOM_EEPROM_RW_STRUC_T);


    return rStatus;
}   /* wlanoidQueryNvramRead */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to write EEPROM value.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[in] pvSetBuffer A pointer to the buffer that holds the data to be set.
* \param[in] u4SetBufferLen The length of the set buffer.
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*                           bytes read from the set buffer. If the call failed
*                           due to invalid length of the set buffer, returns
*                           the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_FAILURE
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidSetNvramWrite (
    IN P_ADAPTER_T  prAdapter,
    IN  PVOID       pvSetBuffer,
    IN  UINT_32     u4SetBufferLen,
    OUT PUINT_32    pu4SetInfoLen
    )
{
    P_PARAM_CUSTOM_EEPROM_RW_STRUC_T prEepromWrInfo;
    BOOLEAN     fgStatus;
    WLAN_STATUS rStatus = WLAN_STATUS_SUCCESS;

    DEBUGFUNC("wlanoidSetEepromWrite");
    ASSERT(prAdapter);
    ASSERT(pvSetBuffer);
    ASSERT(pu4SetInfoLen);

    *pu4SetInfoLen = sizeof(PARAM_CUSTOM_EEPROM_RW_STRUC_T);

	if( prAdapter->prGlueInfo->eCfgSrcType != CFG_SRC_TYPE_NVRAM )
	{
        DBGLOG(REQ, ERROR, ("NVRAM is not current cfg src!!\r\n"));
		return WLAN_STATUS_FAILURE;
	}

    prEepromWrInfo = (P_PARAM_CUSTOM_EEPROM_RW_STRUC_T) pvSetBuffer;

    DBGLOG(REQ, INFO, ("NVRAM Write: index=0x%x, data=0x%x\r\n",
        prEepromWrInfo->ucEepromIndex, prEepromWrInfo->u2EepromData));

    fgStatus = cfgDataWrite16(prAdapter,
                                prEepromWrInfo->ucEepromIndex,
                                prEepromWrInfo->u2EepromData
                                );
    if(fgStatus == FALSE){
        DBGLOG(REQ, ERROR, ("NVRAM Write Failed.\r\n"));
        rStatus = WLAN_STATUS_FAILURE;
    }
    return rStatus;
}   /* wlanoidSetEepromWrite */

#endif

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to get the config data source type.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[in] pvSetBuffer A pointer to the buffer that holds the data to be set.
* \param[in] u4SetBufferLen The length of the set buffer.
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*                           bytes read from the set buffer. If the call failed
*                           due to invalid length of the set buffer, returns
*                           the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_FAILURE
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidQueryCfgSrcType(
    IN  P_ADAPTER_T       prAdapter,
    OUT PVOID             pvQueryBuffer,
    IN  UINT_32           u4QueryBufferLen,
    OUT PUINT_32          pu4QueryInfoLen
  )
{
	  ASSERT( prAdapter );

#if CFG_SUPPORT_EXT_CONFIG        
    *( P_ENUM_CFG_SRC_TYPE_T )pvQueryBuffer = prAdapter->prGlueInfo->eCfgSrcType;
#else 
    *( P_ENUM_CFG_SRC_TYPE_T )pvQueryBuffer = CFG_SRC_TYPE_EEPROM;
#endif  
    
    *pu4QueryInfoLen = sizeof(ENUM_CFG_SRC_TYPE_T);

    return WLAN_STATUS_SUCCESS;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to get the config data source type.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[in] pvSetBuffer A pointer to the buffer that holds the data to be set.
* \param[in] u4SetBufferLen The length of the set buffer.
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*                           bytes read from the set buffer. If the call failed
*                           due to invalid length of the set buffer, returns
*                           the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_FAILURE
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidQueryEepromType(
    IN  P_ADAPTER_T       prAdapter,
    OUT PVOID             pvQueryBuffer,
    IN  UINT_32           u4QueryBufferLen,
    OUT PUINT_32          pu4QueryInfoLen
  )
{
	  ASSERT( prAdapter );

    if ( nicEepromGetSize( prAdapter ) )
    {
        DBGLOG(REQ, INFO, ("EEPROM : present!\r\n"));
        *( P_ENUM_EEPROM_TYPE_T) pvQueryBuffer = EEPROM_TYPE_PRESENT;       
    }
    else
    {
        DBGLOG(REQ, INFO, ("EEPROM : not present!\r\n"));
        *( P_ENUM_EEPROM_TYPE_T )pvQueryBuffer = EEPROM_TYPE_NO;
    
    }    
    
    *pu4QueryInfoLen = sizeof(P_ENUM_EEPROM_TYPE_T);

    return WLAN_STATUS_SUCCESS;
}
/* Renbang : -- (20100319)*/

#if SUPPORT_WAPI
/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called by WAPI ui to set wapi mode, which is needed to info the the driver
*          to operation at WAPI mode while driver initialize.
*
* \param[in] prAdapter Pointer to the Adapter structure
* \param[in] pvSetBuffer A pointer to the buffer that holds the data to be set
* \param[in] u4SetBufferLen The length of the set buffer
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*   bytes read from the set buffer. If the call failed due to invalid length of
*   the set buffer, returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_DATA If new setting value is wrong.
* \retval WLAN_STATUS_INVALID_LENGTH
*
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidSetWapiMode (
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID             pvSetBuffer,
    IN  UINT_32           u4SetBufferLen,
    OUT PUINT_32          pu4SetInfoLen
    )
{
    ASSERT(prAdapter);
    ASSERT(pvSetBuffer);
    ASSERT(pu4SetInfoLen);

    DEBUGFUNC("wlanoidSetWapiMode");
    DBGLOG(WAPI, TRACE, ("\r\n"));

    if (*(PUINT_32)pvSetBuffer) {
        prAdapter->fgWapiMode = TRUE;
        prAdapter->rSecInfo.fgBlockTxTraffic = TRUE;
        prAdapter->rSecInfo.fgBlockRxTraffic = TRUE;
    }
    else {
        prAdapter->fgWapiMode = FALSE;
        prAdapter->rSecInfo.fgBlockTxTraffic = FALSE;
        prAdapter->rSecInfo.fgBlockRxTraffic = FALSE;
    }
    return WLAN_STATUS_SUCCESS;
}


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called by WAPI to set the assoc info, which is needed to add to
*          Association request frame while join WAPI AP.
*
* \param[in] prAdapter Pointer to the Adapter structure
* \param[in] pvSetBuffer A pointer to the buffer that holds the data to be set
* \param[in] u4SetBufferLen The length of the set buffer
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*   bytes read from the set buffer. If the call failed due to invalid length of
*   the set buffer, returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_DATA If new setting value is wrong.
* \retval WLAN_STATUS_INVALID_LENGTH
*
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidSetWapiAssocInfo (
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID             pvSetBuffer,
    IN  UINT_32           u4SetBufferLen,
    OUT PUINT_32          pu4SetInfoLen
    )
{
    P_WAPI_INFO_ELEM_T    prWapiInfo;
    PUINT_8               cp;
    UINT_16               u2AuthSuiteCount = 0;
    UINT_16               u2PairSuiteCount = 0;
    UINT_32               u4AuthKeyMgtSuite = 0;
    UINT_32               u4PairSuite = 0;
    UINT_32               u4GroupSuite = 0;
    
    ASSERT(prAdapter);
    ASSERT(pvSetBuffer);
    ASSERT(pu4SetInfoLen);

    DEBUGFUNC("wlanoidSetWapiAssocInfo");
    DBGLOG(WAPI, TRACE, ("\r\n"));

    prWapiInfo = (P_WAPI_INFO_ELEM_T)pvSetBuffer;
    if (u4SetBufferLen < 20 /* From EID to Group cipher */)
        return WLAN_STATUS_INVALID_LENGTH;
    
    if (prWapiInfo->ucElemId != ELEM_ID_WAPI)
        DBGLOG(WAPI, WARN, ("Not WAPI IE ?!\n"));

    if (prWapiInfo->ucLength < 18)
        return WLAN_STATUS_INVALID_LENGTH;
        
    /* Skip Version check */
    cp = (PUINT_8)&prWapiInfo->u2AuthKeyMgtSuiteCount;
    
    WLAN_GET_FIELD_16(cp, &u2AuthSuiteCount);

    if (u2AuthSuiteCount>1)
        return WLAN_STATUS_INVALID_LENGTH;

    cp += 2;
    WLAN_GET_FIELD_32(cp, &u4AuthKeyMgtSuite);

    DBGLOG(WAPI, TRACE,
        ("WAPI: Assoc Info auth mgt suite [%d]: %02x-%02x-%02x-%02x\n",
        u2AuthSuiteCount,
        (UCHAR) (u4AuthKeyMgtSuite & 0x000000FF),
        (UCHAR) ((u4AuthKeyMgtSuite >> 8) & 0x000000FF),
        (UCHAR) ((u4AuthKeyMgtSuite >> 16) & 0x000000FF),
        (UCHAR) ((u4AuthKeyMgtSuite >> 24) & 0x000000FF)));

    if (u4AuthKeyMgtSuite != WAPI_AKM_SUITE_802_1X &&
        u4AuthKeyMgtSuite != WAPI_AKM_SUITE_PSK)
        ASSERT(FALSE);
    
    cp += 4;
    WLAN_GET_FIELD_16(cp, &u2PairSuiteCount);
    if (u2PairSuiteCount>1)
        return WLAN_STATUS_INVALID_LENGTH;
            
    cp += 2;
    WLAN_GET_FIELD_32(cp, &u4PairSuite);
    DBGLOG(WAPI, TRACE,
        ("WAPI: Assoc Info pairwise cipher suite [%d]: %02x-%02x-%02x-%02x\n",
        u2PairSuiteCount,
        (UCHAR) (u4PairSuite & 0x000000FF),
        (UCHAR) ((u4PairSuite >> 8) & 0x000000FF),
        (UCHAR) ((u4PairSuite >> 16) & 0x000000FF),
        (UCHAR) ((u4PairSuite >> 24) & 0x000000FF)));

    if (u4PairSuite != WAPI_CIPHER_SUITE_WPI)
        ASSERT(FALSE);

    cp += 4;
    WLAN_GET_FIELD_32(cp, &u4GroupSuite);
    DBGLOG(WAPI, TRACE,
        ("WAPI: Assoc Info group cipher suite : %02x-%02x-%02x-%02x\n",
        (UCHAR) (u4GroupSuite & 0x000000FF),
        (UCHAR) ((u4GroupSuite >> 8) & 0x000000FF),
        (UCHAR) ((u4GroupSuite >> 16) & 0x000000FF),
        (UCHAR) ((u4GroupSuite >> 24) & 0x000000FF)));

    if (u4GroupSuite != WAPI_CIPHER_SUITE_WPI)
        ASSERT(FALSE);
    
    prAdapter->rConnSettings.u4WapiSelectedAKMSuite = u4AuthKeyMgtSuite;
    prAdapter->rConnSettings.u4WapiSelectedPairwiseCipher = u4PairSuite;
    prAdapter->rConnSettings.u4WapiSelectedGroupCipher = u4GroupSuite;
    
    kalMemCopy(prAdapter->prGlueInfo->aucWapiAssocInfoIEs,  pvSetBuffer, u4SetBufferLen);
    prAdapter->prGlueInfo->u2WapiAssocInfoIESz = (UINT_16)u4SetBufferLen;
    DBGLOG(WAPI, TRACE, ("Assoc Info IE sz %ld\n", u4SetBufferLen));

    return WLAN_STATUS_SUCCESS;

}


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to set the wpi key to the driver.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[in] pvSetBuffer A pointer to the buffer that holds the data to be set.
* \param[in] u4SetBufferLen The length of the set buffer.
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*                          bytes read from the set buffer. If the call failed
*                          due to invalid length of the set buffer, returns
*                          the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_ADAPTER_NOT_READY
* \retval WLAN_STATUS_INVALID_LENGTH
* \retval WLAN_STATUS_INVALID_DATA
*
* \note The setting buffer P_PARAM_WPI_KEY, which is set by NDIS, is unpacked.
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidSetWapiKey (
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID             pvSetBuffer,
    IN  UINT_32           u4SetBufferLen,
    OUT PUINT_32          pu4SetInfoLen
    )
{
    P_PARAM_WPI_KEY_T prNewKey;
    P_IEEE_802_11_MIB_T prMib;
    PUINT_8             pc;
    DEBUGFUNC("wlanoidSetWapiKey");
    DBGLOG(WAPI, TRACE, ("\r\n"));

    ASSERT(prAdapter);
    ASSERT(pvSetBuffer);
    ASSERT(pu4SetInfoLen);

    prMib = &prAdapter->rConnSettings.rMib;

    if (IS_ARB_IN_RFTEST_STATE(prAdapter)) {
        return WLAN_STATUS_SUCCESS;
    }
    prNewKey = (P_PARAM_WPI_KEY_T) pvSetBuffer;

    if (prAdapter->rAcpiState == ACPI_STATE_D3) {
        DBGLOG(WAPI, WARN, ("Fail in set add key! (Adapter not ready). ACPI=D%d, Radio=%d\r\n",
                    prAdapter->rAcpiState, prAdapter->fgIsRadioOff));
        return WLAN_STATUS_ADAPTER_NOT_READY;
    }

    DBGLOG_MEM8(WAPI, TRACE, (PUINT_8)pvSetBuffer, 560);
    pc = (PUINT_8)pvSetBuffer;

    /* Verify the key structure length. */
    //if (sizeof(PARAM_WPI_KEY_T)!= u4SetBufferLen) {
        //DBGLOG(WAPI, ERROR, ("Invalid key structure length (%d) not equal the total buffer length (%d)\r\n",
        //                  (UINT_16)sizeof(PARAM_WPI_KEY_T),
        //                  (UINT_16)u4SetBufferLen));

    //   *pu4SetInfoLen = u4SetBufferLen;
    //    return WLAN_STATUS_INVALID_LENGTH;
    //}

    /* Exception check */
    if (prNewKey->ucKeyID != 0x1 ||
        prNewKey->ucKeyID != 0x0) {
        DBGLOG(WAPI, ERROR, ("Invalid key ID (%d)\r\n", prNewKey->ucKeyID));
        prNewKey->ucKeyID = prNewKey->ucKeyID & BIT(0);
        //return WLAN_STATUS_INVALID_DATA;
    }

#if 0
    /* Verify the key material length for key material buffer */
    if (prNewKey->u4KeyLength > prNewKey->u4Length - OFFSET_OF(PARAM_KEY_T, aucKeyMaterial)) {
        DBGLOG(RSN, WARN, ("Invalid key material length (%d)\n", (UINT_8)prNewKey->u4KeyLength));
        *pu4SetInfoLen = u4SetBufferLen;
        return WLAN_STATUS_INVALID_DATA;
    }

    /* Exception check */
    if (prNewKey->u4KeyIndex & 0x0fffff00) {
        return WLAN_STATUS_INVALID_DATA;
    }

    if (!(prNewKey->u4KeyLength == WEP_40_LEN  || prNewKey->u4KeyLength == WEP_104_LEN ||
          prNewKey->u4KeyLength == CCMP_KEY_LEN|| prNewKey->u4KeyLength == TKIP_KEY_LEN))
    {
        return WLAN_STATUS_INVALID_DATA;
    }
#endif

    *pu4SetInfoLen = u4SetBufferLen;

    /* Dump P_PARAM_WPI_KEY_T content. */
    DBGLOG(WAPI, TRACE, ("Set: Dump P_PARAM_WPI_KEY_T content\r\n"));
    DBGLOG(WAPI, TRACE, ("TYPE      : %d\r\n", prNewKey->eKeyType));
    DBGLOG(WAPI, TRACE, ("Direction : %d\r\n", prNewKey->eDirection));
    DBGLOG(WAPI, TRACE, ("KeyID     : %d\r\n", prNewKey->ucKeyID));
    DBGLOG(WAPI, TRACE, ("AddressIndex:\r\n"));
    DBGLOG_MEM8(WAPI, TRACE, prNewKey->aucAddrIndex, 12);
    prNewKey->u4LenWPIEK = 16;

    SMS4KeyExt(prNewKey->aucWPIEK,  (PUINT_32)prNewKey->aucWPIEK, 0);
    //kalMemCopy((PUINT_8)prNewKey->aucWPIEK, (PUINT_8)&pc[25], prNewKey->u4LenWPIEK);
    DBGLOG(WAPI, TRACE, ("EN Key(%d): %x %x %x %x\r\n", (UINT_8)prNewKey->u4LenWPIEK,
        pc[25],pc[26],pc[27],pc[28]));
    DBGLOG_MEM8(WAPI, TRACE, (PUINT_8)prNewKey->aucWPIEK, (UINT_8)prNewKey->u4LenWPIEK);
    prNewKey->u4LenWPICK = 16;

    SMS4KeyExt(prNewKey->aucWPICK,  (PUINT_32)prNewKey->aucWPICK, 0);

    //kalMemCopy((PUINT_8)prNewKey->aucWPICK, (PUINT_8)&pc[25+256+4], prNewKey->u4LenWPICK);
    DBGLOG(WAPI, TRACE, ("CK Key(%d):\r\n", (UINT_8)prNewKey->u4LenWPICK));
    DBGLOG_MEM8(WAPI, TRACE, (PUINT_8)prNewKey->aucWPICK, (UINT_8)prNewKey->u4LenWPICK);
    DBGLOG(WAPI, TRACE, ("PN:\r\n"));
    if (prNewKey->eKeyType == 0){
            prNewKey->aucPN[0] = 0x5c;
            prNewKey->aucPN[1] = 0x36;
            prNewKey->aucPN[2] = 0x5c;
            prNewKey->aucPN[3] = 0x36;
            prNewKey->aucPN[4] = 0x5c;
            prNewKey->aucPN[5] = 0x36;
            prNewKey->aucPN[6] = 0x5c;
            prNewKey->aucPN[7] = 0x36;
            prNewKey->aucPN[8] = 0x5c;
            prNewKey->aucPN[9] = 0x36;
            prNewKey->aucPN[10] = 0x5c;
            prNewKey->aucPN[11] = 0x36;
            prNewKey->aucPN[12] = 0x5c;
            prNewKey->aucPN[13] = 0x36;
            prNewKey->aucPN[14] = 0x5c;
            prNewKey->aucPN[15] = 0x36;
    }

    DBGLOG_MEM8(WAPI, TRACE, (PUINT_8)prNewKey->aucPN, PN_LEN);


    if (prNewKey->eKeyType == ENUM_WPI_PAIRWISE_KEY) {
        kalMemCopy(&prMib->rWapiPairwiseKey[prNewKey->ucKeyID], prNewKey, sizeof(PARAM_WPI_KEY_T));
        prMib->fgPairwiseKeyUsed[prNewKey->ucKeyID] = TRUE;
        prMib->ucWpiActivedPWKey = prNewKey->ucKeyID;
    }
    else if (prNewKey->eKeyType == ENUM_WPI_GROUP_KEY) {
        prAdapter->rConnSettings.rMib.fgWapiKeyInstalled = TRUE;
        kalMemCopy(&prMib->rWapiGroupKey[prNewKey->ucKeyID], prNewKey, sizeof(PARAM_WPI_KEY_T));
        prMib->fgGroupKeyUsed[prNewKey->ucKeyID] = TRUE;
        //prMib->fgGroupKeyEnabled[prNewKey->ucKeyID] = TRUE;
        prAdapter->rSecInfo.fgBlockTxTraffic = FALSE;
        prAdapter->rSecInfo.fgBlockRxTraffic = FALSE;
     }
    else
        ASSERT(FALSE);

    return WLAN_STATUS_SUCCESS;
} /* wlanoidSetAddKey */
#endif
#if PTA_NEW_BOARD_DESIGN
/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to disable/enable the AP selection policy
*          For WPS handshake, if the AP set open networking, the wzc profile have modify as WEP
*          Thus, 802.1x can select for EAP type.
*          This is a workaround method, even the encrypt status set enable, but the flag will skip
*          the privacy check, use open networking method to progress the WPS handshake.
*
* \param[in] prAdapter Pointer to the Adapter structure
* \param[in] pvSetBuffer A pointer to the buffer that holds the data to be set
* \param[in] u4SetBufferLen The length of the set buffer
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*   bytes read from the set buffer. If the call failed due to invalid length of
*   the set buffer, returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_DATA If new setting value is wrong.
* \retval WLAN_STATUS_INVALID_LENGTH
*
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidSetPreferredAnt (
    IN  P_ADAPTER_T   prAdapter,
    IN  PVOID         pvSetBuffer,
    IN  UINT_32       u4SetBufferLen,
    OUT PUINT_32      pu4SetInfoLen
    )
{
    UINT_32           u4Value;

    ASSERT(prAdapter);
    ASSERT(pvSetBuffer);
    ASSERT(pu4SetInfoLen);

    u4Value = *(PUINT_32)pvSetBuffer;

    if(prAdapter->rPtaInfo.fgSingleAntenna == FALSE){
        /* for dual antenna board there is no need to setup preferred antenna path */
        return WLAN_STATUS_SUCCESS;
    }

    switch(u4Value){
        case 0:/* WiFi */
            printk(KERN_WARNING DRV_NAME"%s %d\n", __FUNCTION__, __LINE__);
            nicPtaSetAnt(prAdapter, TRUE);
            break;
        case 1:/* BT */
            printk(KERN_WARNING DRV_NAME"%s %d\n", __FUNCTION__, __LINE__);
            nicPtaSetAnt(prAdapter, FALSE);
            break;
        default:
            printk(KERN_WARNING DRV_NAME"Unexpected antenna %ld\n", u4Value);
            return WLAN_STATUS_INVALID_DATA;
            break;
    }
    return WLAN_STATUS_SUCCESS;

}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to query current value of continuous poll
*        interval
*
* \param[in] prAdapter          Pointer to the Adapter structure.
* \param[in] pvQueryBuffer      Pointer to the buffer that holds the result of
*                               the query.
* \param[in] u4QueryBufferLen   The length of the query buffer.
* \param[out] pu4QueryInfoLen   If the call is successful, returns the number of
*                               bytes written into the query buffer. If the call
*                               failed due to invalid length of the query buffer,
*                               returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_LENGTH
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidQueryPreferredAnt (
    IN  P_ADAPTER_T prAdapter,
    OUT PVOID       pvQueryBuffer,
    IN  UINT_32     u4QueryBufferLen,
    OUT PUINT_32    pu4QueryInfoLen
    )
{
    PUINT_32 pu4PrefAnt;
    BOOL    fgPreferWiFi;


    ASSERT(prAdapter);
    ASSERT(pu4QueryInfoLen);
    if (u4QueryBufferLen) {
        ASSERT(pvQueryBuffer);
    }

    *pu4QueryInfoLen = sizeof(UINT_32);

    /* Check for query buffer length */
    if (u4QueryBufferLen < *pu4QueryInfoLen) {
        DBGLOG(REQ, WARN, ("Invalid length %lu\n", u4QueryBufferLen));
        return WLAN_STATUS_INVALID_LENGTH;
    }

    ASSERT(pvQueryBuffer);
    
    pu4PrefAnt = (PUINT_32)pvQueryBuffer;
    
    if(prAdapter->rPtaInfo.fgSingleAntenna == FALSE){
        /* for dual antenna board there is preferred antenna path */
        *pu4PrefAnt = 0;/* WiFi */
        *pu4QueryInfoLen = sizeof(UINT_32);
        return WLAN_STATUS_SUCCESS;
    }

    nicPtaGetAnt(prAdapter, &fgPreferWiFi);

    if(fgPreferWiFi){
        *pu4PrefAnt = 0;/* WiFi */
    }else{
        *pu4PrefAnt = 1;/* BT */
    }

    *pu4QueryInfoLen = sizeof(UINT_32);
    return WLAN_STATUS_SUCCESS;

}
#endif


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to query current WMMPS status. 0: disabled. 1:enabled
*
* \param[in] pvAdapter Pointer to the Adapter structure.
* \param[out] pvQueryBuf A pointer to the buffer that holds the result of
*                           the query.
* \param[in] u4QueryBufLen The length of the query buffer.
* \param[out] pu4QueryInfoLen If the call is successful, returns the number of
*                            bytes written into the query buffer. If the call
*                            failed due to invalid length of the query buffer,
*                            returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_FAILURE
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidQueryWmmPsMode(
    IN  P_ADAPTER_T       prAdapter,
    OUT PVOID             pvQueryBuffer,
    IN  UINT_32           u4QueryBufferLen,
    OUT PUINT_32          pu4QueryInfoLen
    )
{
    WLAN_STATUS rStatus = WLAN_STATUS_SUCCESS;

    DEBUGFUNC("wlanoidQueryWMMPS");

    ASSERT(prAdapter);
    ASSERT(pvQueryBuffer);
    ASSERT(pu4QueryInfoLen);

    *(PUINT_8)pvQueryBuffer = gPlatformCfg.rWifiCustom.ucWmmPsEnable;
    *pu4QueryInfoLen = sizeof(UINT_8);

    return rStatus;
}   /* wlanoidQueryNvramRead */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to set WMMPS status. 0: disabled. 1:enabled
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[in] pvSetBuffer A pointer to the buffer that holds the data to be set.
* \param[in] u4SetBufferLen The length of the set buffer.
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*                           bytes read from the set buffer. If the call failed
*                           due to invalid length of the set buffer, returns
*                           the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_FAILURE
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidSetWmmPsMode (
    IN P_ADAPTER_T  prAdapter,
    IN  PVOID       pvSetBuffer,
    IN  UINT_32     u4SetBufferLen,
    OUT PUINT_32    pu4SetInfoLen
    )
{
    BOOLEAN     fgStatus;
    WLAN_STATUS rStatus = WLAN_STATUS_SUCCESS;
    UINT_8 ucWmmPsEn = 0;


    DEBUGFUNC("wlanoidSetEepromWrite");
    ASSERT(prAdapter);
    ASSERT(pvSetBuffer);
    ASSERT(pu4SetInfoLen);

    ucWmmPsEn = *(PUINT_8)pvSetBuffer;
    *pu4SetInfoLen = sizeof(UINT_8);

    if(ucWmmPsEn > 1){
	    printk("[MT5921][wlanoidSetWMMPS] invalid WMMPS status %d\n",ucWmmPsEn);
        return WLAN_STATUS_FAILURE;
    }
    
    fgStatus = customDataWrite8(prAdapter,
                                OFFSET_OF(WIFI_CUSTOM_PARAM_STRUCT, ucWmmPsEnable),
                                ucWmmPsEn
                                );
    if(fgStatus == FALSE){
	    printk("[MT5921][wlanoidSetWMMPS] Write WMMPS status failed\n");
        rStatus = WLAN_STATUS_FAILURE;
    }
    return rStatus;
}   /* wlanoidSetEepromWrite */
