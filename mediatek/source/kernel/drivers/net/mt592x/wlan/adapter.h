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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/adapter.h#2 $
*/

/*! \file   adapter.h
    \brief  Definition of internal data structure for driver manipulation.

    In this file we define the internal data structure - ADAPTER_T which stands
    for MiniPort ADAPTER(From Windows point of view) or stands for Network ADAPTER.
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
** $Log: adapter.h $
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\122 2009-10-09 17:05:13 GMT mtk01088
**  alloc a 1600 bytes buffer for wpi encrypt and decrypt
**  \main\maintrunk.MT5921\121 2009-10-09 17:02:38 GMT mtk01088
**  add variable to save the desired wapi security mode
**  \main\maintrunk.MT5921\120 2009-09-22 22:51:10 GMT mtk01089
**  Use PTA_NEW_BOARD_DESIGN to seperate previous code.
**  \main\maintrunk.MT5921\119 2009-09-12 13:45:44 GMT mtk01089
**  Allows BWCS to control antenna path and PTA setting in single antenna board design.
**  \main\maintrunk.MT5921\118 2009-08-06 16:42:42 GMT mtk01090
**  Use GPIO0 and GPIO2 to control antenna switch and remove obsolete compile flag CFG_SUPPORT_SINGLE_ANTENNA
**  \main\maintrunk.MT5921\117 2009-07-06 20:20:17 GMT mtk01088
**  adding variable for wapi mode and use wapi 
**  \main\maintrunk.MT5921\116 2009-03-20 11:43:06 GMT mtk01461
**  Add variable for VI AIFSN/TXOP testing registry
**  \main\maintrunk.MT5921\115 2009-03-09 20:38:41 GMT mtk01461
**  Add a legacy flag in STA_RECORD_T for detecting leaving protection mode
**  \main\maintrunk.MT5921\114 2009-02-25 15:48:09 GMT mtk01461
**  Add fgIsPrivacyEnabled in PEER_BSS_INFO_T to check privacy consistency
**  \main\maintrunk.MT5921\113 2009-02-18 21:02:14 GMT mtk01461
**  Add variable for RSN/WPA IE change detection
**  \main\maintrunk.MT5921\112 2009-02-17 17:32:34 GMT mtk01084
**  add new registry for configuring polling interval when there's no WiFi traffic
**  \main\maintrunk.MT5921\111 2009-02-13 21:00:23 GMT mtk01461
**  Add u2CapInfo in BSS_INFO for capability change detection
**  \main\maintrunk.MT5921\110 2009-01-07 17:34:35 GMT mtk01425
**  1. Add rScoPtaParam, rAclPtaParam and rMixPtaParam to the CONNECTION_SETTINGS_T
**  \main\maintrunk.MT5921\109 2009-01-05 10:00:19 GMT mtk01725
**  Add a new ENUM for SLT mode. Add variable in ADAPTER_T for current SLT mode and SLT status.
**  \main\maintrunk.MT5921\108 2008-11-24 20:55:13 GMT mtk01425
**  1. Add PTA_ENABLED flag
**  \main\maintrunk.MT5921\107 2008-11-21 23:56:21 GMT mtk01725
**  \main\maintrunk.MT5921\106 2008-11-21 23:09:28 GMT mtk01725
**  \main\maintrunk.MT5921\105 2008-10-27 14:24:41 GMT mtk01084
**  supporting continuous polling mode
**  \main\maintrunk.MT5921\104 2008-10-16 18:55:01 GMT mtk01084
**  update for single antenna
**  \main\maintrunk.MT5921\103 2008-09-19 11:13:37 GMT mtk01088
**  change the SDIO enhance compiling flag to avoid the spi compiling error
**  \main\maintrunk.MT5921\102 2008-09-08 09:30:25 GMT mtk01084
**  remove un-used variable
**  \main\maintrunk.MT5921\101 2008-09-05 17:24:49 GMT mtk01461
**  Update Driver for Code Review
**  \main\maintrunk.MT5921\100 2008-09-03 13:39:27 GMT mtk01084
**  add the control of the antenna selection pin
**  \main\maintrunk.MT5921\99 2008-09-02 22:19:28 GMT mtk01461
**  Revise TX Aggregation to support TX Fragmentation
**  \main\maintrunk.MT5921\98 2008-09-02 11:57:31 GMT mtk01461
**  Update driver for code review
**  \main\maintrunk.MT5921\97 2008-09-02 11:43:29 GMT mtk01461
**  Update driver for code review - remove the SDIO status buffer
**  \main\maintrunk.MT5921\96 2008-08-27 17:05:10 GMT mtk01461
**  Update driver for Code Review
**  \main\maintrunk.MT5921\95 2008-08-12 09:54:19 GMT mtk01461
**  Update for Driver Review - MAXIMUM_OPERATION_CHANNEL_LIST
**  \main\maintrunk.MT5921\94 2008-08-11 09:34:39 GMT mtk01461
**  remove ENUM eResetType, remove fgChipInit
**  \main\maintrunk.MT5921\93 2008-08-10 18:59:16 GMT mtk01461
**  Update for Driver Review
**  \main\maintrunk.MT5921\92 2008-08-04 16:50:52 GMT mtk01461
**  Enable Link List ASSERT during QA debug
**  \main\maintrunk.MT5921\91 2008-07-24 20:19:53 GMT mtk01088
**  adjust the pmk candicate buffer to avoid overwrite adapter variable
**  \main\maintrunk.MT5921\90 2008-07-16 15:30:28 GMT mtk01104
**  Add member "eGPIO2_Mode" in CONNECTION_SETTINGS_T
**  \main\maintrunk.MT5921\89 2008-07-14 13:47:47 GMT mtk01104
**  1. Add new member "fgTryTxAutoFragmentForBT in conn_setting struct
**  2. Rename rPtaCtrl to rPtaParam
**  \main\maintrunk.MT5921\88 2008-07-11 10:56:30 GMT mtk01084
**  add rNicOpDomainInfo for recording current domain infor
**  \main\maintrunk.MT5921\87 2008-07-10 16:37:27 GMT mtk01084
**  support 802.11d related functions
**  \main\maintrunk.MT5921\86 2008-07-07 13:21:57 GMT mtk01461
**  Adding fgBypassPortCtrlForRoaming to skip check outgoing packet during 802.1x handshaking while roaming
**  \main\maintrunk.MT5921\85 2008-07-04 13:36:37 GMT mtk01088
**  add rev id variable at adapter
**  \main\maintrunk.MT5921\84 2008-06-18 20:44:35 GMT mtk01084
**  revise beacon timeout handling procedure
**  \main\maintrunk.MT5921\83 2008-06-16 16:33:28 GMT mtk01084
**  fix compiling flag about removing BG SSID scan issue
**  \main\maintrunk.MT5921\82 2008-06-16 16:11:18 GMT mtk01084
**  use compiler flag to distinguish whether to support SSID recover state
**  \main\maintrunk.MT5921\81 2008-06-12 20:28:54 GMT mtk01461
**  Remove unused compile flag of SCAN module which is work around for MPW.
**  \main\maintrunk.MT5921\80 2008-06-10 22:56:40 GMT mtk01084
**  add country code in connection setting
**  \main\maintrunk.MT5921\79 2008-06-10 09:40:11 GMT mtk01084
**  add LED mode control in connection setting structure
**  \main\maintrunk.MT5921\78 2008-05-30 23:10:08 GMT mtk01104
**  Add PTA_CTRL_STRUC_T in connecting setting
**  \main\maintrunk.MT5921\77 2008-05-30 18:52:21 GMT mtk01461
**  Remove staRecGetStaRecordByLastActivityForIBSS()
**  \main\maintrunk.MT5921\76 2008-05-30 15:14:30 GMT mtk01084
**  add fgIsEnterD3ReqIssued
**  \main\maintrunk.MT5921\75 2008-05-29 14:14:44 GMT mtk01084
**  add variables in _CONNECTION_SETTINGS_T
**  \main\maintrunk.MT5921\74 2008-05-22 19:39:36 GMT MTK01088
**  move the mib to connection setting
**  \main\maintrunk.MT5921\73 2008-05-20 10:38:53 GMT mtk01084
**  prepare the data structure used for SLT test
**  \main\maintrunk.MT5921\72 2008-05-16 10:32:41 GMT mtk01461
**  Revise RCPI related function for RSSI OID & Roaming
**  \main\maintrunk.MT5921\71 2008-05-15 14:02:41 GMT mtk01461
**  Add fgIsConnByBssidIssued for support SET BSSID OID.
**  \main\maintrunk.MT5921\70 2008-05-12 13:36:40 GMT mtk01084
**  add ACPI D0~D3 related variable
**  \main\maintrunk.MT5921\69 2008-04-24 11:58:20 GMT mtk01461
**  Fix multicast setting in Linux and add comment
**  \main\maintrunk.MT5921\68 2008-04-16 15:21:53 GMT mtk01461
**  Add SW detection of Beacon Timeout false alarm for Ad-Hoc
**  \main\maintrunk.MT5921\67 2008-04-10 23:40:43 GMT mtk01385
**  1. add update BB/RF Rx setting based on thermo info function.
**  2. fix typo fgUpdat'a'LnaFromAlcInt.
**  \main\maintrunk.MT5921\66 2008-04-02 20:43:50 GMT mtk01084
**  Support for RCPI variance histogram
**  \main\maintrunk.MT5921\65 2008-03-31 13:49:27 GMT mtk01461
**  Move roaming enable flag to rConnSetting
**  \main\maintrunk.MT5921\64 2008-03-29 13:49:55 GMT mtk01461
**  Add MAGIC GUID for Link List
**  \main\maintrunk.MT5921\63 2008-03-23 22:48:48 GMT mtk01461
**  Add function declaration
**  \main\maintrunk.MT5921\62 2008-03-23 20:37:10 GMT mtk01461
**  Move the fgIsIBSSActive flag from BSS_INFO_T to ADAPTER_T
**  \main\maintrunk.MT5921\61 2008-03-19 15:21:30 GMT mtk01461
**  Change FRAG_Q_STRUC_T to FRAG_INFO_T in STA_RECORD_T
**  \main\maintrunk.MT5921\60 2008-03-18 13:49:31 GMT mtk01088
**  add variable to record the RF frequency set
**  \main\maintrunk.MT5921\59 2008-03-17 12:56:44 GMT mtk01084
**  refine the timer utility function
**  \main\maintrunk.MT5921\58 2008-03-14 19:10:41 GMT mtk01084
**  Modify VoIP related lines
**  \main\maintrunk.MT5921\57 2008-03-13 15:31:35 GMT mtk01461
**  Refine the relationship between SCAN result and STA record, lifetime, aging policy etc
**  \main\maintrunk.MT5921\56 2008-03-13 14:27:19 GMT mtk01461
**  Rename IsValidSSID to IsConnReqIssued
**  Revise variable for Roaming Module
**  \main\maintrunk.MT5921\55 2008-02-27 12:11:58 GMT mtk01461
**  Add comment for fgIsHiddenSSID
**  \main\maintrunk.MT5921\54 2008-02-21 15:01:26 GMT mtk01461
**  Add rRcpi variable to STA_RECORD_T for initial Rate Selection
**  \main\maintrunk.MT5921\53 2008-02-20 10:14:34 GMT mtk01461
**  Add RadioOff flag
**  \main\maintrunk.MT5921\52 2008-02-15 19:18:54 GMT mtk01084
**  remove one un-used variable
**  \main\maintrunk.MT5921\51 2008-02-12 23:43:17 GMT mtk01461
**  Add Set Frequency & Channel oid support for Linux
**  \main\maintrunk.MT5921\50 2008-02-12 22:59:52 GMT mtk01461
**  Add TX auto fragmentation for BT support
**  \main\maintrunk.MT5921\49 2008-02-01 13:26:55 GMT mtk01385
**  1. add alc value and a flag to thermo info structure.
**  \main\maintrunk.MT5921\48 2008-01-31 17:05:44 GMT mtk01385
**  1. add Thermo info sturcture.
**  \main\maintrunk.MT5921\47 2008-01-22 22:46:36 GMT mtk01084
**  add variable to record current PM control status
**  \main\maintrunk.MT5921\46 2008-01-22 15:38:02 GMT mtk01084
**  add member to record current packet filter setting
**  \main\maintrunk.MT5921\45 2008-01-07 15:05:42 GMT mtk01461
**  Add SDIO Enhance Support
**  Add PhyType & AdHocMode Selection Support
**  \main\maintrunk.MT5921\44 2007-12-24 11:42:14 GMT mtk01084
**  add variable about block to scan or not
**  \main\maintrunk.MT5921\43 2007-12-20 15:14:43 GMT mtk01084
**  add variable rLastConnectedTime
**  \main\maintrunk.MT5921\42 2007-12-11 00:07:46 GMT mtk01461
**  Shrink structure of SCAN result - BSS_DESC_T
**  \main\maintrunk.MT5921\41 2007-12-07 11:30:13 GMT mtk01084
**  update the record of last RX UC packet time
**  \main\maintrunk.MT5921\40 2007-11-26 21:17:03 GMT mtk01385
**  1. add statistics infor to adapter.
**  \main\maintrunk.MT5921\39 2007-11-26 19:24:56 GMT mtk01461
**  Unify SCAN
**  \main\maintrunk.MT5921\38 2007-11-17 15:32:20 GMT mtk01385
**  1. add rftest info to adapter structure.
**  \main\maintrunk.MT5921\37 2007-11-13 17:55:33 GMT mtk01084
**  add new variable for check if beacon is received after connected
**  \main\maintrunk.MT5921\36 2007-11-08 20:04:00 GMT mtk01088
**  remove non-used variable
**  \main\maintrunk.MT5921\35 2007-11-08 13:53:42 GMT mtk01084
**  update VoIP related variables
**  \main\maintrunk.MT5921\34 2007-11-07 18:35:14 GMT mtk01461
**  Add Tx Fragmentation Support
**  \main\maintrunk.MT5921\33 2007-11-06 20:17:56 GMT mtk01088
**  add WPS need variable
**  \main\maintrunk.MT5921\32 2007-11-05 16:56:55 GMT mtk01425
**  1. Move fgIsRenewBSSID from _ARB_INFO_T
**  \main\maintrunk.MT5921\31 2007-11-02 00:52:03 GMT mtk01461
**  Unify TX Path for Normal and IBSS Power Save + IBSS neighbor learning
**  \main\maintrunk.MT5921\30 2007-10-30 09:21:17 GMT mtk01425
**  1. Add variables for reset procedure and multicast list
**
**  \main\maintrunk.MT5921\29 2007-10-29 13:41:09 GMT mtk01084
**  add flag to check if process IST is need to be redo
**  \main\maintrunk.MT5921\28 2007-10-26 19:25:13 GMT mtk01084
**  add new flag to check INT false alarm
**  \main\maintrunk.MT5921\27 2007-10-25 17:59:17 GMT mtk01461
**  Add VOIP SCAN & Refine Roaming
** Revision 1.14  2007/07/17 12:51:48  MTK01088
** add pmkid related parameter
**
** Revision 1.13  2007/07/16 02:29:58  MTK01088
** add mib structure
**
** Revision 1.12  2007/07/12 06:13:34  MTK01084
** update timer related routines
**
** Revision 1.11  2007/07/09 07:37:35  MTK01084
** temporarily remark-off place using SCAN structure
**
** Revision 1.10  2007/07/09 06:21:13  MTK01088
** change the wlan table control structure name
**
** Revision 1.9  2007/07/05 07:25:31  MTK01461
** Add Linux initial code, modify doc, add 11BB, RF init code
**
** Revision 1.8  2007/07/04 10:06:35  MTK01088
** add and remove the security related variable
**
** Revision 1.7  2007/07/04 01:19:16  MTK01385
** add pta related structure to adapter.
**
** Revision 1.6  2007/06/28 12:59:22  MTK01088
** add the sw maintain wlan table structure
**
** Revision 1.5  2007/06/27 12:41:48  MTK01088
** use the e for enum parameter,
** the authmode, encrypt status... set from oid save to connection structure
**
** Revision 1.4  2007/06/27 06:14:32  MTK01088
** add the sec fsm structure member to adapter
**
** Revision 1.3  2007/06/27 02:12:21  MTK01461
** Update SCAN_FSM, Initial(Can Load Module), Proc(Can do Reg R/W), TX API
**
** Revision 1.2  2007/06/25 06:16:23  MTK01461
** Update illustrations, gl_init.c, gl_kal.c, gl_kal.h, gl_os.h and RX API
**
** Revision 1.1.1.1  2007/06/22 08:09:05  MTK01461
** no message
**
*/

#ifndef _ADAPTER_H
#define _ADAPTER_H

/*******************************************************************************
*                         C O M P I L E R   F L A G S
********************************************************************************
*/

/*******************************************************************************
*                    E X T E R N A L   R E F E R E N C E S
********************************************************************************
*/

/*******************************************************************************
*                              C O N S T A N T S
********************************************************************************
*/
#define STA_RECORD_GUID                         0xA5A51461
#if DBG || BUILD_QA_DBG
#define STA_RECORD_SET_GUID(_prStaRec)          {(_prStaRec)->u4Magic = STA_RECORD_GUID;}
#define STA_RECORD_CHK_GUID(_prStaRec)          ASSERT((_prStaRec)->u4Magic == STA_RECORD_GUID)
#else
#define STA_RECORD_SET_GUID(_prStaRec)
#define STA_RECORD_CHK_GUID(_prStaRec)
#endif /* DBG || BUILD_QA_DBG */

#define STA_RECORD_HASH_BITS                    2
#define STA_RECORD_HASH_MASK                    BITS(0, (STA_RECORD_HASH_BITS - 1))
#define STA_RECORD_HASH_NUM                     BIT(STA_RECORD_HASH_BITS)

#define STA_RECORD_RM_POLICY_EXCLUDE_STATE_3    BIT(0) // Remove STA Record except the STATE_3 node(also imply the default entry for AdHoc Mode.)
#define STA_RECORD_RM_POLICY_TIMEOUT            BIT(1) // Remove the timeout one
#define STA_RECORD_RM_POLICY_OLDEST             BIT(2) // Remove the oldest one
#define STA_RECORD_RM_POLICY_ENTIRE             BIT(3) // Remove entire STA Record

/* The Lifetime of a Station Record if it is inactive */
#define STA_RECORD_TIMEOUT_SEC                  600 // Seconds


/* 11.3 STA Authentication and Association */
#define STA_STATE_1                             0 /* Accept Class 1 frames */
#define STA_STATE_2                             1 /* Accept Class 1 & 2 frames */
#define STA_STATE_3                             2 /* Accept Class 1,2 & 3 frames */



/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/
#if (CFG_DBG_BEACON_RCPI_MEASUREMENT || CFG_LP_PATTERN_SEARCH_SLT)
/* Beacon RCPI debug */
typedef struct _BEACON_RCPI_RECORED_T {
    UINT_32                 u4RcpiIndex;
    UINT_32                 u4RcpiMaxIndex;
    UINT_32                 u4RcpiMinIndex;
    INT_8                   acRcpiArray[MAX_NUM_RCPI_RECORDS];
    //INT_8                   cCurRcpi;        /*!< Current RCPI value (min. -200) */
    INT_8                   cCurAveRcpi;
    UINT_32                 u4BcnLostCnt;
    UINT_32                 u4BcnRecvCnt;    /*including false alarm one*/
    UINT_32                 u4RcpiFalseAlarmCnt;
    INT_8                   cRcpiMin;
    INT_8                   cRcpiMax;
    UINT_32                 u4Range0;
    UINT_32                 u4Range1;
    UINT_32                 u4Range2;
    INT_32                  i4AccuRCPI;
    UINT_32                 u4AccuNF;   /*max 2^32/2^10 packets*/
    ULARGE_INTEGER           rLastTbttCnt;
} BEACON_RCPI_RECORED_T, *P_BEACON_RCPI_RECORED_T;

/* SLT Testing Mode */
typedef enum _ENUM_SLT_MODE_T {
    SLT_MODE_NORMAL = 0,
    SLT_MODE_LP,
    SLT_MODE_PATTERN_SEARCH,
    SLT_MODE_NUM
} ENUM_SLT_MODE_T, *P_ENUM_SLT_MODE_T;

#endif

//3 /* Session for CONNECTION SETTINGS */
typedef enum _ENUM_CONNECTION_POLICY_T {
    CONNECT_BY_SSID = 0,
    CONNECT_BY_SSID_BEST_RSSI,
    CONNECT_BY_SSID_BEST_RSSI_MIN_CH_LOAD,
    CONNECT_BY_SSID_ANY,
    CONNECT_BY_CUSTOMIZED_RULE
} ENUM_CONNECTION_POLICY_T, *P_ENUM_CONNECTION_POLICY_T;


typedef struct _CONNECTION_SETTINGS_T {

    UINT_8                          aucMacAddress[MAC_ADDR_LEN];

    /* power mode */
    PARAM_POWER_MODE                rPwrMode;

    /* ARP filter enable */
    BOOLEAN                         fgArpFilterEn;

    /* ATIM windows using for IBSS power saving function */
    UINT_16                         u2AtimWindow;

    /* b0~3: trigger-en AC0~3. b4~7: delivery-en AC0~3 */
    UINT_8                          bmfgApsdEnAc;

    UINT_8                          aucBSSID[MAC_ADDR_LEN];
    BOOLEAN                         fgIsConnByBssidIssued;

    UINT_8                          ucSSIDLen;
    UINT_8                          aucSSID[ELEM_MAX_LEN_SSID];
    BOOLEAN                         fgIsConnReqIssued;

    BOOLEAN                         fgIsEnableRoaming;

    UINT_16                         u2BeaconPeriod;

    UINT_8                          ucChannelNum;
    UINT_8                          ucChannelBand;
    UINT_32                         u4FreqInKHz; /* TODO */

    ENUM_PARAM_PHY_TYPE_T           eDesiredPhyType;

    ENUM_PARAM_OP_MODE_T            eOPMode;

    ENUM_PARAM_AUTH_MODE_T          eAuthMode;

    ENUM_PARAM_AD_HOC_MODE_T        eAdHocMode;

    ENUM_ENCRYPTION_STATUS_T        eEncStatus;

#if SUPPORT_WAPI /* Set by assoc info */
    UINT_32                         u4WapiSelectedGroupCipher;
    UINT_32                         u4WapiSelectedPairwiseCipher;
    UINT_32                         u4WapiSelectedAKMSuite;
#endif

    /*! \brief MTK WLAN NIC driver IEEE 802.11 MIB */
    IEEE_802_11_MIB_T               rMib;

//    UINT_32                         u4BssRsnSelectedGroupCipher;
//    UINT_32                         u4BssRsnSelectedUnicastCipher;

    ENUM_CONNECTION_POLICY_T        eConnectionPolicy;

    ENUM_PARAM_PREAMBLE_TYPE_T      ePreambleType;

                                    /* User desired setting, but will honor the capability of AP */
    BOOLEAN                         fgIsShortSlotTimeOptionEnable;

    BOOLEAN                         fgIsAdHocQoSEnable;

    UINT_16                         u2DesiredRateSet; /* User desired setting */

    UINT_16                         u2RTSThreshold; /* User desired setting */

#if CFG_TX_FRAGMENT
    UINT_16                         u2FragmentationThreshold; /* User desired setting */

    BOOLEAN                         fgIsEnableTxFragment; /* User desired setting */

    BOOLEAN                         fgIsEnableTxAutoFragmentForBT;

    BOOLEAN                         fgTryTxAutoFragmentForBT; /* User desired setting */
    ENUM_PARAM_BT_COEXIST_WINDOW_T  eBTCoexistWindowType;
#endif /* CFG_TX_FRAGMENT */

    BOOLEAN                         fgIsVoipConn;
    UINT_32                         u4VoipTrafficInterval;  /* 0: disable VOIP configuration */

#if PTA_ENABLED
    PTA_PARAM_T                     rPtaParam;   /* PTA setting */

    /* new board design take two set of PTA parameters */
#if PTA_NEW_BOARD_DESIGN
    PTA_PARAM_T	                    rSingleAclPtaParam;
    PTA_PARAM_T	                    rSingleMixPtaParam;
    PTA_PARAM_T	                    rDualAclPtaParam;
    PTA_PARAM_T	                    rDualMixPtaParam;
#else
    PTA_PARAM_T	                    rScoPtaParam;
    PTA_PARAM_T	                    rAclPtaParam;
    PTA_PARAM_T	                    rMixPtaParam;
#endif
#endif

    UINT_16                         u2CountryCode;

    UINT_8                          ucLedBlinkMode;

#if CFG_SUPPORT_802_11D
    BOOLEAN                         fgMultiDomainCapabilityEnabled;
#endif /* CFG_SUPPORT_802_11D*/

    ENUM_PARAM_GPIO2_MODE_T         eGPIO2_Mode;

    UINT_32                         u4ContPollIntv; // 0: disable poll, else: enable with specific interval

    UINT_32                         u4ContPollIntvB; // 0: disable poll, else: enable with specific interval

    UINT_8                          ucViAifsnBias;      /* Define VI AIFSN bias (Default: 0, 0~15) */
                                                        /* Actual AIFSN = AIFSN from AP + AIFSN bias */
    UINT_16                         u2ViMaxTxopLimit;   /* Define VI MAX TXOP LIMIT(A upper bound) (Default: 0xFFFF, 0~0xFFFF) */

} CONNECTION_SETTINGS_T, *P_CONNECTION_SETTINGS_T;



//3 /* Session for STA RECORD */
struct _STA_RECORD_T {
    LINK_ENTRY_T        rLinkEntry;

    UINT_8              aucMacAddr[MAC_ADDR_LEN];
    UINT_8              ucStaState;
    BOOLEAN             fgIsQoS;
    BOOLEAN             fgIsLegacy;

#if CFG_IBSS_POWER_SAVE
    QUE_T               arStaWaitQueue[TC_NUM];

    /* remote STA power state (used under IBSS power save) */
    BOOLEAN             fgIsAdhocStaAwake;
#endif /* CFG_IBSS_POWER_SAVE */

    UINT_8              ucPowerMgtMode;

    /* Received RCPI from each RX frame */
    RCPI                rRcpi;

    /* Desired Rate Set after match with Operational Rate Set */
    UINT_16             u2DesiredRateSet;

    /* Current Rate1Index get from AutoRate Table */
    UINT_8              ucCurrRate1Index;

    /* Used for updating Rate Field's Preamble Mode of WLAN Table or Auto Rate Table */
    BOOLEAN             fgIsShortPreambleOptionEnable; /* Depend on STA's CAP_INFO */


    /* last rx Sequence Control field */
    UINT_16             u2LastRxSeqCtrl;

    /* last rx Sequence control field for each TID */
    UINT_16             u2TIDLastRxSeqCtrl[TID_NUM];

    UINT_16             u2StatusCode; /* Status of Auth/Assoc Req */
    UINT_16             u2ReasonCode; /* Reason that been Deauth/Disassoc */

    UINT_8              ucJoinFailureCount;

    OS_SYSTIME          rLastJoinTime;

    OS_SYSTIME          rUpdateTime;

    FRAG_INFO_T         rFragInfo[MAX_NUM_CONCURRENT_FRAGMENTED_MSDUS];

#if DBG || BUILD_QA_DBG
    UINT_32             u4Magic;
#endif /* DBG || BUILD_QA_DBG */

};

typedef struct _STA_INFO_T {
    UINT_32             u4StaRecCachedSize;
    PUINT_8             pucStaRecCached;

#if CFG_IBSS_POWER_SAVE
    QUE_T               arGcStaWaitQueue[TC_NUM];

    BOOLEAN             fgIsAllAdhocStaAwake;
#endif /* CFG_IBSS_POWER_SAVE */

    UINT_8              ucValidStaRecNum;
    LINK_T              rFreeStaRecList;
    LINK_T              arValidStaRecList[STA_RECORD_HASH_NUM];
} STA_INFO_T, *P_STA_INFO_T;

#if CFG_SDIO_STATUS_ENHANCE
//3 /* Session for SDIO ENHANCE MODE */
typedef struct _SDIO_CTRL_T {

    UINT_32         u4Hisr;
    UINT_16         au2RxLengthDW[SDIO_MAXIMUM_RX_STATUS];
    TX_STATUS_T     arTxStatus[SDIO_MAXIMUM_TX_STATUS];

    #if DBG
    UINT_8          ucMaxNumOfRxLen;
    UINT_8          ucMaxNumOfTxStatus;
    #endif /* DBG */

} SDIO_CTRL_T, *P_SDIO_CTRL_T;
#endif /* CFG_SDIO_STATUS_ENHANCE */

//3 /* Session for Thermo function */
typedef struct _THERMO_INFO_T {

        TIMER_T                 rTimer;
#if CFG_FAKE_THERMO_VALUE_DBG_EN
        UINT_8                  ucDbgThermoVal;
#endif
        UINT_8                  ucHwAlcValue;
        BOOL                    fgUpdateTxGainFromAlcInt;
        BOOL                    fgUpdateLnaFromAlcInt;
        UINT_32                 u4AlcArParam;
        ENUM_THERMO_STATE_T     rState;
} THERMO_INFO_T, *P_THERMO_INFO_T;



//3 /* BSS Descriptor structure */
struct _BSS_DESC_T {
    LINK_ENTRY_T            rLinkEntry;

    UINT_8                  aucBSSID[MAC_ADDR_LEN];
    UINT_8                  aucSrcAddr[MAC_ADDR_LEN]; /* For IBSS, the SrcAddr is different from BSSID */

    BOOLEAN                 fgIsConnecting; /* If we are going to connect to this BSS
                                             * (JOIN or ROAMING to another BSS), don't
                                             * remove this record from BSS List.
                                             */
    BOOLEAN                 fgIsConnected; /* If we have connected to this BSS (NORMAL_TR),
                                            * don't removed this record from BSS list.
                                            */

    BOOLEAN                 fgIsHiddenSSID; /* When this flag is TRUE, means the SSID
                                             * of this BSS is not known yet.
                                             */
    UINT_8                  ucSSIDLen;
    UINT_8                  aucSSID[ELEM_MAX_LEN_SSID];

    OS_SYSTIME              rUpdateTime;

    ENUM_BSS_TYPE_T         eBSSType;

    ENUM_PHY_TYPE_INDEX_T   ePhyType; /* PHY Type of this BSS_DESC_T */

    RCPI                    rRcpi;


    UINT_8                  ucWmmFlag; /* A flag to indicate this BSS's WMM capability */

    BOOLEAN                 fgPreAuthEnabled;

    BOOLEAN                 fgIsERPPresent;
    UINT_8                  ucERP;

    BOOLEAN                 fgIsLargerTSF; /* This BSS's TimeStamp is larger than us(TCL == 1 in RX_STATUS_T) */

    BOOLEAN                 fgIsUnknownBssBasicRate; /* Have unknown data rate which is not list in aucDataRate[] */

    UINT_16                 u2OperationalRateSet;
    UINT_16                 u2BSSBasicRateSet;

    UINT_8                  ucDTIMPeriod;

    UINT_8                  ucSupportedRatesLen;
    UINT_8                  aucSupportedRates[RATE_NUM];

    UINT_16                 u2CapInfo;
    UINT_16                 u2BeaconInterval;
    UINT_16                 u2ATIMWindow;

    P_WPA_INFO_ELEM_T       prIEWPA;
    P_RSN_INFO_ELEM_T       prIERSN;
#if SUPPORT_WAPI
    P_WAPI_INFO_ELEM_T	    prIEWAPI;
#endif

    P_IE_WMM_PARAM_ELEM_T   prIeWmmParamElem;

#if CFG_SUPPORT_802_11D
    P_IE_COUNTRY_T          prIECountry;
#endif

#if 0 // NOTE(Kevin): Useless for reporting SCAN Result, remove later.
    P_IE_COUNTRY_T                  prIECountry;
    P_IE_BSS_LOAD_T                 prIEBSSLoad;
    P_IE_POWER_CONSTRAINT_T         prIEPowerConstraint;
    P_IE_TPC_REPORT_T               prIETPCReport;
    P_IE_CHNL_SWITCH_ANNOUNCEMENT_T prIEChnlSwitchAnnouncement;
    P_IE_QUIET_T                    prIEQuiet;
    P_IE_IBSS_DFS_T                 prIEIBSSDFS;
#endif

    UINT_16                 u2IELength;

    UINT_8                  aucIEBuf[CFG_IE_BUFFER_SIZE];

//    UINT_16             u2WPAIEOffset;
//    UINT_16             u2RSNIEOffset;
//    UINT_16             u2WMMIEOffset;


    ULARGE_INTEGER          u8TimeStamp;

    ENUM_BAND_T             eBand;

    UINT_8                  ucChannelNum;


//    INT_32              rssi;
//    UINT_32             linkQuality;
//    UINT_16             lastMgtRespStatusCode;
//    UINT_16             requestRefusedStatusCode;
//    UINT                joinTimeoutCount;


    /*! \brief RSN parameters selected for connection */
    /*! \brief The Select score for final AP selection,
               0, no sec, 1,2,3 group cipher is WEP, TKIP, CCMP */
    UINT_8                  ucEncLevel;
    /*! \brief The srbiter Search State will matched the scan result,
               and saved the selected cipher and akm, and report the score,
               for arbiter join state, join module will carry this target BSS
               to rsn generate ie function, for gen wpa/rsn ie */
    UINT_32                 u4RsnSelectedGroupCipher;
    UINT_32                 u4RsnSelectedPairwiseCipher;
    UINT_32                 u4RsnSelectedAKMSuite;

    BOOLEAN                 fgWpaCapPresent;
    UINT_16                 u2WpaCap;
    UINT_16                 u2RsnCap;

#if DBG || BUILD_QA_DBG
    UINT_32                 u4Magic;
#endif /* DBG || BUILD_QA_DBG */

};


//3 /* Peer BSS' Information structure which we are going to JOIN with or MERGE into */
struct _PEER_BSS_INFO_T {

    UINT_8              aucBSSID[MAC_ADDR_LEN];


    UINT_16             u2AssocId;

    UINT_16             u2OperationalRateSet; /* Operational Rate Set of peer BSS */
    UINT_16             u2BSSBasicRateSet; /* Basic Rate Set of peer BSS */
    BOOLEAN             fgIsUnknownBSSBasicRate;

    BOOLEAN             fgIsShortPreambleAllowed; /* From Capability Info. */

    BOOLEAN             fgUseShortSlotTime; /* From Capability Info. */

    BOOLEAN             fgIsPrivacyEnabled; /* From Capability Info. */

    /* Save the Challenge Text from Auth Seq 2 Frame, before sending Auth Seq 3 Frame */
    IE_CHALLENGE_TEXT_T rIeChallengeText;

    WMM_INFO_T          rWmmInfo; /* Current WMM capability after associated with target AP */

};




//3 /* Current BSS' Information structure which we belong in this moment */
struct _BSS_INFO_T {

    ENUM_PHY_TYPE_INDEX_T   ePhyType;

    ENUM_BSS_TYPE_T     eBSSType;

    UINT_8              aucBSSID[MAC_ADDR_LEN];

    BOOLEAN             fgIsWmmAssoc; /* This flag is used to indicate that WMM is enable in current BSS */

    UINT_8              ucSSIDLen;
    UINT_8              aucSSID[ELEM_MAX_LEN_SSID];

    UINT_16             u2CapInfo;
    UINT_16             u2AssocId;

    BOOLEAN             fgIsERPPresent; /* This flag is used to indicate that we need sync the ERP with AP */
    UINT_8              ucERP;
    BOOLEAN             fgIsProtection;



    UINT_8              ucDtimPeriod;

    UINT_16             u2OperationalRateSet; /* Operational Rate Set of current BSS */
    UINT_16             u2BSSBasicRateSet; /* Basic Rate Set of current BSS */

    UINT_8              ucBasicRateIndex;

    UINT_8              ucRTSProtectionRateIndex; /* This is also the Rate Index of CTS_to_self */
    UINT_8              ucRTSRateIndex; /* This is also the Rate Index of CTS_to_self */

    BOOLEAN             fgIsShortPreambleAllowed; /* From Capability Info. of AssocResp Frame AND of Beacon/ProbeResp Frame */

    BOOLEAN             fgUseShortPreamble; /* Short Preamble is enabled in current BSS. */

    BOOLEAN             fgUseShortSlotTime; /* Short Slot Time is enabled in current BSS. */

    BOOLEAN             fgIsWPAorWPA2Enabled; /* WPA/WPA2 is enabled in current BSS. */

    /*! \brief RSN saved cipher for oid add key after associate and key handshake  */
    UINT_32             u4RsnSelectedGroupCipher;
    UINT_32             u4RsnSelectedPairwiseCipher;
    UINT_32             u4RsnSelectedAKMSuite;

    RCPI                rRcpi;
    PARAM_RSSI          rRssi;
    OS_SYSTIME          rRssiLastUpdateTime; /* The last time when update RSSI */


    //4 2007/10/01, mikewu, add for compose beacon
    UINT_16             u2ATIMWindow;
    UINT_8              ucChnl;
    ENUM_BAND_T         eBand;
    UINT_16             u2BeaconInterval;

    UINT_16             u2BcnLen;
    UINT_8              aucBcnContent[CFG_IE_BUFFER_SIZE] __KAL_ATTRIB_ALIGN_4__;
    //4 End by Mike

#if CFG_TX_FRAGMENT

    BOOLEAN             fgIsPrivacyEnable;
    BOOLEAN             fgRequireMICForFrag; /* Depend on TKIP Cipher Key was set */
    UINT_8              ucWlanDataFrameHeaderLen; /* Depend on WMM association */
    UINT_16             u2PayloadFragmentationThreshold; /* Current Fragmentation Threshold for payload which has
                                                              */
#endif /* CFG_TX_FRAGMENT */

    WMM_INFO_T          rWmmInfo;

    OS_SYSTIME          rRoamingStableExpirationTime;
    UINT_8              ucRoamingAuthTypes;

#if CFG_SUPPORT_802_11D
    BOOLEAN             fgIsCountryInfoPresent;
    DOMAIN_INFO_ENTRY   rDomainInfo;
#endif

};



//3 /* Major ADAPTER structure */
/* Major data structure for driver operation */
struct _ADAPTER_T {
    UINT_8                  ucRevID;

    RF_CHANNEL_INFO_T       arNicOpChnList[MAXIMUM_OPERATION_CHANNEL_LIST]; /*!< operation channel list for normal operation */
    UINT_16                 u2NicOpChnlNum;

    DOMAIN_INFO_ENTRY       rNicOpDomainInfo;

    LINK_T                  rTimerList;         /*!< Timer List for mgmt_timer.c */
    OS_SYSTIME              rNextExpiredSysTime;

    PM_CONN_SETUP_INFO_T    rPmConnSetupInfo;
//    BOOLEAN                 fgPowerControlAcquired;
    /* Driver feature control */

    BOOLEAN                 fgIsEnableWMM;
    //BOOLEAN                 fgIsEnableRoaming; /* Move to rConnSettings */
    BOOLEAN                 fgIsEnableRoamingGsm;
    BOOLEAN                 fgIsEnableJoinToHiddenSSID;

    UINT_32                 u4OsPacketFilter;     // packet filter used by OS

#if CFG_TCP_IP_CHKSUM_OFFLOAD
    UINT_32                 u4CSUMFlags;
#endif /* CFG_TCP_IP_CHKSUM_OFFLOAD */


    /* ADAPTER flags */
    UINT_32                 u4Flags;

    ARB_INFO_T              rArbInfo;

    JOIN_INFO_T             rJoinInfo;

    ROAMING_INFO_T          rRoamingInfo;

    SEC_INFO_T              rSecInfo;
#if PTA_ENABLED
    PTA_INFO_T              rPtaInfo;
#endif
    TIMER_INFO_T            rTimerInfo;

    MGT_BUF_INFO_T          rMgtBufInfo;

    WLAN_ENTRY_CTRL_T       arWlanCtrl[WLAN_TABLE_SIZE];

    /*! \brief Global flag to let arbiter stay at standby and not connect to any network */
    BOOLEAN                 fgCounterMeasure;

    BOOLEAN                 fgIsRadioOff;

    BOOLEAN                 fgIsEnterD3ReqIssued;

    ENUM_ACPI_STATE_T       rAcpiState;

#if !CFG_SUPPORT_SSID_RECOVER_STATE
    BOOLEAN fgRemoveBGScan;
#endif

    CONNECTION_SETTINGS_T   rConnSettings;

    /* Element for SCAN(BSS description) management */
    SCAN_INFO_T             rScanInfo;

    /* Element for power management */
    PM_INFO_T               rPmInfo;

    /* Element for STA record management */
    STA_INFO_T              rStaInfo;

    RF_INFO_T               rRFInfo;

    /* RF Test mode*/
    RFTEST_INFO_T           rRFTestInfo;

    STATISTICS_INFO_T       rStatisticsInfo;


    /* Temporary data collected from Peer BSS while doing JOIN proccess, such as Challenge Text */
    PEER_BSS_INFO_T         rPeerBssInfo;

    /* Current associated BSS or created / merged IBSS */
    BSS_INFO_T              rBssInfo;


    ENUM_OP_MODE_T          eCurrentOPMode;

    /* NOTE(Kevin): for windows, we may delay the Disconnect Event for 10 sec.
     * During this period, the eConnectionState == MEDIA_STATE_DISCONNECTED.
     * But the eConnectionStateIndicated == MEDIA_STATE_CONNECTED.
     */
    ENUM_MEDIA_STATE        eConnectionState;
    ENUM_MEDIA_STATE        eConnectionStateIndicated; /* The Media State that report to OS */

    BOOLEAN                 fgBypassPortCtrlForRoaming;
    /* NOTE(Kevin): Once we've create a new IBSS or merge with other IBSS, following
     * flag will be set to TRUE regardless of Connection State.
     */
    BOOLEAN                 fgIsIBSSActive;
    BOOLEAN                 fgIsIBSSBeaconTimeoutAlarm;
    OS_SYSTIME              rIBSSLastBeaconTimeout;


    UINT_8                  aucMacAddress[MAC_ADDR_LEN];
    UINT_8                  aucMulticastAddr[MAX_NUM_GROUP_ADDR][MAC_ADDR_LEN];
    UINT_8                  ucMulticastAddrNum;


    /* Driver default value according to HW capability */
    UINT_16                 u2SupportedPhyTypeSet; /* Supported PHY Types - HW dependent */

    UINT_16                 u2AvailablePhyTypeSet; /* Available PHY Types - HW dependent & User desired */

    ENUM_PHY_TYPE_INDEX_T   eCurrentPhyType; /* Current selection basing on the set of Available PHY Types */


    /* RF frequency set, only availabe at MT60105 ASIC  */
    ENUM_RF_FREQ_T          eRfFreqSet;


    PARAM_RSSI              rRssiTriggerValue;

#if CFG_COALESCING_BUFFER_SIZE
    UINT_32                 u4CoalescingBufCachedSize;
    PUINT_8                 pucCoalescingBufCached;
#endif /* CFG_COALESCING_BUFFER_SIZE */

#if CFG_FRAGMENT_COALESCING_BUFFER_SIZE
    UINT_32                 u4FragCoalescingBufCachedSize;
    PUINT_8                 pucFragCoalescingBufCached;
#endif /* CFG_FRAGMENT_COALESCING_BUFFER_SIZE */


    /* Element for TX PATH */
    TX_CTRL_T               rTxCtrl;

    /* Element for RX PATH */
    RX_CTRL_T               rRxCtrl;

#if CFG_SDIO_STATUS_ENHANCE || CFG_SDIO_TX_ENHANCE
    SDIO_CTRL_T             rSDIOCtrl;
#endif /* CFG_SDIO_STATUS_ENHANCE || CFG_SDIO_TX_ENHANCE */

    EEPROM_CTRL_T           rEEPROMCtrl;

    /* Buffer for Authentication Event */
    /* <Todo> Move to glue layer and refine the kal function */
    /* Reference to rsnGeneratePmkidIndication function at rsn.c */
    UINT_8                  aucIndicationEventBuffer[CFG_MAX_PMKID_CACHE * 20  + 8 ];

    //4 2007/06/20, mikewu, interrupt status
    UINT_32                 au4IntStatus[INT_NUM];
    UINT_32                 au4IntEnable[INT_NUM];
    BOOLEAN                 fgIsIntEnable;
    BOOLEAN                 fgIsIntEnableWithLPOwnSet;

#if DBG
    BOOLEAN                 fgIntrMayFalseAlarmFlag;
#endif
    BOOLEAN                 fgRedoProcessISTFlag;

    BOOLEAN                 fgEnableAverageRcpiFunc;

    //4 2007/09/20, mikewu, Autorate-related variables
    AR_CTRL_T               rARCtrl;

    RATE_INFO_T             rRateInfo;

    PARAM_CUSTOM_MCR_RW_STRUC_T rMcrRdWrInfo;

    P_GLUE_INFO_T           prGlueInfo;

#if SUPPORT_WPS
    BOOLEAN                 fgIndMgt;
    UINT_8                  aucAppIE[IEEE80211_APPIE_NUM_OF_FRAME][300];
    UINT_8                  aucAppIELen[IEEE80211_APPIE_NUM_OF_FRAME];
#endif


    OS_SYSTIME              rLastRxUcDataSysTime;
    OS_SYSTIME              rLastConnectedTime;

    BOOLEAN                 fgBeaconReceivedAfterConnected;
    BOOLEAN                 fgIsBlockToScan;


    THERMO_INFO_T           rThermoInfo;

#if CFG_PEEK_RCPI_VALUE_PERIOD_SEC
    TIMER_T                 rRcpiDiagnostic;
#endif /* CFG_PEEK_RCPI_VALUE_PERIOD_SEC */

#if (CFG_DBG_BEACON_RCPI_MEASUREMENT || CFG_LP_PATTERN_SEARCH_SLT)
    /* Beacon RCPI debug */
    BEACON_RCPI_RECORED_T   rBcnRCPIRecord;

    /* SLT Mode Selection */
    ENUM_SLT_MODE_T eSLTModeSel;

    BOOLEAN                 fgPatternSearchMatch;
#endif

    BOOLEAN                 fgWaitOneBeaconForTsfRecovery;

#if SUPPORT_WAPI
    BOOLEAN                 fgUseWapi; /* TRUE, The registry to set the driver init as wapi driver */
    BOOLEAN                 fgWapiMode; /* At WAI, the open set this value 0 and wapi mode set 1,
                                           and the oid encryption status is always ENUM_ENCRYPTION_DISABLED 
                                           needed this value to identify */ 
#if SUPPORT_WPI_AVOID_LOCAL_BUFFER
    UINT_8                  ucTemp[1600];
#endif
#endif
#if CFG_TEST_IO_PIN
    /* IO Pin Test */
    BOOLEAN fgIntVarified;
    UINT_32 u4IntIORslt;
#endif
};/* end of _ADAPTER_T */

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
#define STA_RECORD_HASH_FUNC(pucAddr)   \
    ((pucAddr[MAC_ADDR_LEN - 2]) & STA_RECORD_HASH_MASK)

/* The macro to set the expiration time of the station record with a specified
   timeout in units of seconds */
#define STA_RECORD_SET_EXPIRATION_TIME(prStaRec, u4TimeOutSecond) \
    SET_EXPIRATION_TIME((prStaRec)->rExpirationTime, \
        SEC_TO_SYSTIME(u4TimeOutSecond))

#define RCPI_TO_DBM(_rcpi)    ((INT_8)((_rcpi)/2 - 110))

#define ABS(_x)  ( (_x)>0 ? (_x):-(_x))



/*******************************************************************************
*                  F U N C T I O N   D E C L A R A T I O N S
********************************************************************************
*/
/*----------------------------------------------------------------------------*/
/* Routines in sta_record.c                                                   */
/*----------------------------------------------------------------------------*/
VOID
staRecInitialize (
    IN P_ADAPTER_T prAdapter
    );

P_STA_RECORD_T
staRecGetStaRecordByAddr (
    IN P_ADAPTER_T prAdapter,
    IN PUINT_8 pucStaAddr
    );

P_STA_RECORD_T
staRecGetStaRecordByAddrOrAddIfNotExist (
    IN P_ADAPTER_T prAdapter,
    IN PUINT_8 pucStaAddr
    );

VOID
staRecRemoveStaRecordByPolicy (
    IN P_ADAPTER_T prAdapter,
    IN UINT_32 u4RemovePolicy
    );

VOID
staRecRemoveStaRecordForIBSS (
    IN P_ADAPTER_T prAdapter
    );

VOID
staRecRemoveStateFlagOfAllStaRecords (
    IN P_ADAPTER_T prAdapter
    );

VOID
staRecClearStatusAndReasonCode (
    IN P_ADAPTER_T prAdapter
    );

VOID
staRecCheckDefragBufOfAllStaRecords (
    IN P_ADAPTER_T prAdapter
    );

#if CFG_DBG_STA_RECORD
VOID
staRecQueryStatus (
    IN P_ADAPTER_T prAdapter,
    IN PUINT_8 pucBuffer,
    OUT PUINT_32 pu4Count
    );
#endif /* CFG_DBG_STA_RECORD */

/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/
/* Kevin: we don't have to call following function to inspect the data structure.
 * It will check automatically while at compile time.
 */
__KAL_INLINE__ VOID
adapterDataTypeCheck (
    VOID
    )
{
#if CFG_SDIO_STATUS_ENHANCE
    #if DBG
    DATA_STRUC_INSPECTING_ASSERT(OFFSET_OF(SDIO_CTRL_T, ucMaxNumOfRxLen)
        == sizeof(ISAR_BIND_STATUS_T));
    #else
    DATA_STRUC_INSPECTING_ASSERT(sizeof(SDIO_CTRL_T)
        == sizeof(ISAR_BIND_STATUS_T));
    #endif /* DBG */
#endif /* CFG_SDIO_STATUS_ENHANCE */

    return;
}

#endif /* _ADAPTER_H */


