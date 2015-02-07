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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/wlan_oid.h#2 $
*/

/*! \file   "wlan_oid.h"
    \brief This file contains the declairation file of the WLAN OID processing routines
           of Windows driver for MediaTek Inc. 802.11 Wireless LAN Adapters.
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
** $Log: wlan_oid.h $
 *
 * 07 10 2010 renbang.jiang
 * [ALPS00121785][Need Patch] [Volunteer Patch] use NVRAM to save Wi-Fi custom data 
 * .
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\83 2009-09-22 22:52:04 GMT mtk01089
**  Use PTA_NEW_BOARD_DESIGN to seperate 1.26 code
**  \main\maintrunk.MT5921\82 2009-09-12 13:45:35 GMT mtk01089
**  BWCS add more constant for single antenna
**  \main\maintrunk.MT5921\81 2009-07-08 14:52:44 GMT mtk01088
**  rename the wapi variable pre-fix 
**  \main\maintrunk.MT5921\80 2009-07-06 20:30:30 GMT mtk01088
**  adding related structure and function declaration for wapi mode
**  \main\maintrunk.MT5921\79 2009-04-24 09:08:57 GMT mtk01088
**  mark the code not used at linux supplicant v0.6.7
**  \main\maintrunk.MT5921\78 2009-04-06 15:37:12 GMT mtk01088
**  add the function declaration to set the disable AP selection for privacy check, for wps open networking.
**  \main\maintrunk.MT5921\77 2009-02-18 20:08:52 GMT mtk01084
**  remove redundent variable
**  \main\maintrunk.MT5921\76 2009-02-17 17:32:44 GMT mtk01084
**  add new registry for configuring polling interval when there's no WiFi traffic
**  \main\maintrunk.MT5921\75 2009-02-16 17:56:25 GMT mtk01084
**  modify for controlling beacon lost detection function
**  \main\maintrunk.MT5921\74 2009-01-15 13:51:41 GMT mtk01104
**  Add new profile "BT_PROFILE_NO_CONNECTION"
**  \main\maintrunk.MT5921\73 2009-01-07 17:39:19 GMT mtk01425
**  1.Add  wlanoidQueryBtSingleAntenna, wlanoidQueryPta, wlanoidSetBtSingleAntenna and wlanoidSetPta
**  \main\maintrunk.MT5921\72 2009-01-05 10:05:48 GMT mtk01725
**  Add new function declaration of SLT mode change.
**  \main\maintrunk.MT5921\71 2008-12-01 12:27:48 GMT mtk01425
**  1. update the variable name to fit the type of it (_PTA_IPC_T)
**  \main\maintrunk.MT5921\70 2008-11-24 21:05:16 GMT mtk01425
**  1. Add PTA_ENABLED flag
**  \main\maintrunk.MT5921\69 2008-11-19 11:48:41 GMT mtk01088
**  rename some variable with pre-fix to avoid the misunderstanding
**  \main\maintrunk.MT5921\68 2008-10-31 14:03:06 GMT mtk01425
**  1. Add BT_PROFILE_PARAM_LEN
**
**  2. Add types: ENUM_BT_CMD_T, ENUM_BT_PROFILE_T, PTA_PROFILE_T, ENUM_BT_PROFILE_PARAM_T and PARAM_PTA_IPC_T
**
**  3. Add the declarations of functions: wlanoidSetBT, wlanoidQueryBT and wlanoidQueryContinuousPollInterval
**  \main\maintrunk.MT5921\67 2008-10-27 14:24:46 GMT mtk01084
**  supporting continuous polling mode
**  \main\maintrunk.MT5921\66 2008-09-03 13:38:51 GMT mtk01084
**  modify for coding rule conformance
**  \main\maintrunk.MT5921\65 2008-08-05 01:51:50 GMT mtk01461
**  Add support for linux statistics
**  \main\maintrunk.MT5921\64 2008-08-04 16:48:28 GMT mtk01461
**  Remove redundant function declaration
**  \main\maintrunk.MT5921\63 2008-08-02 16:20:00 GMT mtk01104
**  GPIO2_MODE_EEPROM definiton replaces original GPIO2_MODE_GPI
**  \main\maintrunk.MT5921\62 2008-07-16 15:26:42 GMT mtk01104
**  Add type "ENUM_PARAM_GPIO2_MODE_T"
**  \main\maintrunk.MT5921\61 2008-07-15 17:43:14 GMT mtk01084
**  rename variable used under WMM-PS
**  \main\maintrunk.MT5921\60 2008-07-14 13:45:57 GMT mtk01104
**  PARAM_CUSTOM_BT_COEXIST_T replaces PARAM_CUSTOM_PTA_T
**  \main\maintrunk.MT5921\59 2008-07-10 16:38:08 GMT mtk01084
**  support 802.11d related functions
**  \main\maintrunk.MT5921\58 2008-07-01 10:54:28 GMT mtk01084
**  add wlanoidSetWiFiWmmPsTest definition
**  \main\maintrunk.MT5921\57 2008-06-26 21:09:13 GMT mtk01084
**  add custom OID for WMM-PS test
**  \main\maintrunk.MT5921\56 2008-06-19 10:13:25 GMT mtk01084
**  support OID for more detail about PTA settings
**  \main\maintrunk.MT5921\55 2008-06-12 20:28:29 GMT mtk01461
**  Remove AD_HOC_MODE_11B_WIFI definition
**  \main\maintrunk.MT5921\54 2008-06-10 19:47:49 GMT MTK01088
**  add wlanoidSetTest() function declaration
**  \main\maintrunk.MT5921\53 2008-06-03 20:21:48 GMT mtk01104
**  Change BTCR1[30:29] mode definition
**  \main\maintrunk.MT5921\52 2008-06-02 22:56:33 GMT mtk01461
**  Rename some functions for Linux Proc
**  \main\maintrunk.MT5921\51 2008-06-02 20:20:19 GMT mtk01461
**  Remove MCR Read / Write function declarations for Linux
**  \main\maintrunk.MT5921\50 2008-06-01 17:33:35 GMT mtk01084
**  remove un-used function
**  \main\maintrunk.MT5921\49 2008-05-31 00:16:07 GMT mtk01104
**  Remove PTA query function
**  \main\maintrunk.MT5921\48 2008-05-30 23:07:13 GMT mtk01104
**  Re-define _PARAM_CUSTOM_PTA_T
**  \main\maintrunk.MT5921\47 2008-05-30 18:47:17 GMT mtk01461
**  Remove wlanoidSetCSUMOffloadForLinux()
**  \main\maintrunk.MT5921\46 2008-05-30 18:44:37 GMT mtk01461
**  Remove wlanoidSetCSUMOffloadForLinux()
**  \main\maintrunk.MT5921\45 2008-05-30 16:07:59 GMT mtk01084
**  modify wlan_oid naming
**  \main\maintrunk.MT5921\44 2008-05-29 14:18:12 GMT mtk01084
**  modify IP address setting OID
**  \main\maintrunk.MT5921\43 2008-05-29 14:16:33 GMT mtk01084
**  \main\maintrunk.MT5921\42 2008-05-20 10:35:38 GMT mtk01084
**  add wlanoidQueryLowPowerSltResult() for SLT test
**  \main\maintrunk.MT5921\41 2008-05-03 13:09:43 GMT mtk01461
**  Remove declaration of OID Media Connection Status
**  \main\maintrunk.MT5921\40 2008-04-24 22:46:08 GMT mtk01461
**  Add define of param filter from typedef.h
**  \main\maintrunk.MT5921\39 2008-04-23 14:12:36 GMT mtk01461
**  Add QueryDesiredRateSet OID
**  \main\maintrunk.MT5921\38 2008-04-17 23:06:20 GMT mtk01461
**  Add function declaration of Query/Set AdHocMode
**  \main\maintrunk.MT5921\37 2008-04-13 21:17:08 GMT mtk01461
**  Revise GEN Link Speed OID
**  \main\maintrunk.MT5921\36 2008-03-31 13:49:23 GMT mtk01461
**  Add priv oid to turn on/off roaming
**  \main\maintrunk.MT5921\35 2008-03-28 10:40:07 GMT mtk01461
**  Add wlanoidSetDesiredRates and remove tempoaray desired rate setting path in linux
**  \main\maintrunk.MT5921\34 2008-03-26 15:33:33 GMT mtk01461
**  Add set MAC Address for Linux
**  Add CSUM offload priv ioctl for Linux
**  \main\maintrunk.MT5921\33 2008-03-19 15:21:27 GMT mtk01461
**  Add CFG_TCP_IP_CHKSUM_OFFLOAD flag if set to 0
**  \main\maintrunk.MT5921\32 2008-03-18 11:52:19 GMT mtk01084
**  add PM related definition which is removed from pwr_mgt.h
**  \main\maintrunk.MT5921\31 2008-03-11 14:50:49 GMT mtk01461
**  Add set Beacon Interval function declaration
**  \main\maintrunk.MT5921\30 2008-03-10 15:42:08 GMT mtk01385
**  1. add MAX RSSI level definition for WHQL test.
**  \main\maintrunk.MT5921\29 2008-03-07 10:50:05 GMT mtk01084
**  support function to addTS, delTS
**  \main\maintrunk.MT5921\28 2008-02-29 16:56:54 GMT mtk01088
**  add function declaration
**  \main\maintrunk.MT5921\27 2008-02-25 16:10:03 GMT mtk01385
**  1. add 11b only phy type.
**  2. add set network type function.
**  \main\maintrunk.MT5921\26 2008-02-21 22:55:38 GMT mtk01084
**  add set TCP task offload related function
**  \main\maintrunk.MT5921\25 2008-02-14 09:52:15 GMT mtk01084
**  add structure and function declairation for pattern search related function
**  \main\maintrunk.MT5921\24 2008-02-12 23:42:02 GMT mtk01461
**  Add Set Frequency & Channel oid support for Linux
**  \main\maintrunk.MT5921\23 2008-02-12 22:59:49 GMT mtk01461
**  Add TX auto fragmentation for BT support
**  \main\maintrunk.MT5921\22 2008-02-04 17:05:41 GMT mtk01461
**  Refine ARB_IF_IN_RFTEST_STATE
**  \main\maintrunk.MT5921\21 2008-01-22 21:09:42 GMT mtk01084
**  add new function to set BG SSID scan parameters
**  \main\maintrunk.MT5921\20 2008-01-09 17:57:02 GMT mtk01084
**  support diassociation OID
**  \main\maintrunk.MT5921\19 2008-01-07 15:05:39 GMT mtk01461
**  Add SDIO Enhance Support
**  Add PhyType & AdHocMode Selection Support
**  \main\maintrunk.MT5921\18 2007-11-28 21:37:08 GMT mtk01385
**  1. Fix linux compiling error in query Statistics.
**  \main\maintrunk.MT5921\17 2007-11-26 21:36:19 GMT mtk01385
**  1. add statistics related functions.
**  \main\maintrunk.MT5921\16 2007-11-26 19:32:54 GMT mtk01461
**  Add RTS parameter
**  \main\maintrunk.MT5921\15 2007-11-19 10:19:17 GMT mtk01385
**  1. add EEProm definitions.
**  2. add RF test tx/rx status definitions.
**  \main\maintrunk.MT5921\14 2007-11-17 15:17:46 GMT mtk01385
**  1. modify MCR read/write access method.
**  2. add 802.11 configuration query function.
**  \main\maintrunk.MT5921\13 2007-11-13 15:13:06 GMT mtk01088
**  add the function declaration for CETK 1c_OIDs
**  \main\maintrunk.MT5921\12 2007-11-08 14:00:14 GMT mtk01084
**  update functions for supporting admission control
**  \main\maintrunk.MT5921\11 2007-11-07 18:34:38 GMT mtk01461
**  Add Tx Fragmentation Support
**  \main\maintrunk.MT5921\10 2007-11-06 20:00:45 GMT mtk01088
**  add WPS code
**  \main\maintrunk.MT5921\9 2007-10-25 20:52:51 GMT mtk01084
**  add ACPI related functions
**  \main\maintrunk.MT5921\8 2007-10-25 17:56:20 GMT mtk01461
**  Add MCR R/W support for Linux Proc
** Revision 1.8  2007/07/17 12:56:21  MTK01088
** add enum and structure for pmkid and remove key
**
** Revision 1.7  2007/07/16 02:37:19  MTK01088
** add the _T at ENUM define
**
** Revision 1.6  2007/07/05 07:25:31  MTK01461
** Add Linux initial code, modify doc, add 11BB, RF init code
**
** Revision 1.5  2007/07/04 12:55:24  MTK01088
** modify the ENUM define
**
** Revision 1.4  2007/07/04 10:14:30  MTK01088
** add null and bc addr define
**
** Revision 1.3  2007/06/27 06:23:35  MTK01088
** add the sec related structure define
**
** Revision 1.2  2007/06/25 06:16:23  MTK01461
** Update illustrations, gl_init.c, gl_kal.c, gl_kal.h, gl_os.h and RX API
**
*/
#ifndef _WLAN_OID_H
#define _WLAN_OID_H

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

#define PARAM_MAX_LEN_SSID                      32

#define PARAM_MAC_ADDR_LEN                      6

#define ETHERNET_HEADER_SZ                      14
#define ETHERNET_MIN_PKT_SZ                     60
#define ETHERNET_MAX_PKT_SZ                     1514

#define PARAM_MAX_LEN_RATES                     8
#define PARAM_MAX_LEN_RATES_EX                  16

#define PARAM_AUTH_REQUEST_REAUTH               0x01
#define PARAM_AUTH_REQUEST_KEYUPDATE            0x02
#define PARAM_AUTH_REQUEST_PAIRWISE_ERROR       0x06
#define PARAM_AUTH_REQUEST_GROUP_ERROR          0x0E

#define PARAM_EEPROM_READ_METHOD_READ           1
#define PARAM_EEPROM_READ_METHOD_GETSIZE        0

#define PARAM_WHQL_RSSI_MAX_DBM                 (-10)


/* Packet filter bit definitioin (UINT_32 bit-wise definition) */
#define PARAM_PACKET_FILTER_DIRECTED            0x00000001
#define PARAM_PACKET_FILTER_MULTICAST           0x00000002
#define PARAM_PACKET_FILTER_ALL_MULTICAST       0x00000004
#define PARAM_PACKET_FILTER_BROADCAST           0x00000008
#define PARAM_PACKET_FILTER_PROMISCUOUS         0x00000020
#define PARAM_PACKET_FILTER_ALL_LOCAL           0x00000080


#define PARAM_PACKET_FILTER_SUPPORTED   (PARAM_PACKET_FILTER_DIRECTED | \
                                         PARAM_PACKET_FILTER_MULTICAST | \
                                         PARAM_PACKET_FILTER_BROADCAST | \
                                         PARAM_PACKET_FILTER_ALL_MULTICAST)


#define BT_PROFILE_PARAM_LEN        8
/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/
typedef UINT_8          PARAM_MAC_ADDRESS[PARAM_MAC_ADDR_LEN];

typedef UINT_32         PARAM_KEY_INDEX;
typedef UINT_64         PARAM_KEY_RSC;
typedef INT_32          PARAM_RSSI;

typedef UINT_32         PARAM_FRAGMENTATION_THRESHOLD;
typedef UINT_32         PARAM_RTS_THRESHOLD;

typedef UINT_8          PARAM_RATES[PARAM_MAX_LEN_RATES];
typedef UINT_8          PARAM_RATES_EX[PARAM_MAX_LEN_RATES_EX];

typedef enum _ENUM_PARAM_PHY_TYPE_T {
    PHY_TYPE_802_11ABG = 0,             /*!< Can associated with 802.11abg AP, Scan dual band. */
    PHY_TYPE_802_11BG,                  /*!< Can associated with 802_11bg AP, Scan single band and not report 802_11a BSSs. */
    PHY_TYPE_802_11G,                   /*!< Can associated with 802_11g only AP, Scan single band and not report 802_11ab BSSs. */
    PHY_TYPE_802_11A,                   /*!< Can associated with 802_11a only AP, Scan single band and not report 802_11bg BSSs. */
    PHY_TYPE_802_11B,                   /*!< Can associated with 802_11b only AP, Scan single band and not report 802_11ag BSSs. */
    PHY_TYPE_NUM // 5
} ENUM_PARAM_PHY_TYPE_T, *P_ENUM_PARAM_PHY_TYPE_T;


typedef enum _ENUM_PARAM_AD_HOC_MODE_T {
    AD_HOC_MODE_11B = 0,           /*!< Create 11b IBSS if we support 802.11abg/802.11bg. */
    AD_HOC_MODE_MIXED_11BG,             /*!< Create 11bg mixed IBSS if we support 802.11abg/802.11bg/802.11g. */
    AD_HOC_MODE_11G,                    /*!< Create 11g only IBSS if we support 802.11abg/802.11bg/802.11g. */
    AD_HOC_MODE_11A,                    /*!< Create 11a only IBSS if we support 802.11abg. */
    AD_HOC_MODE_NUM // 4
} ENUM_PARAM_AD_HOC_MODE_T, *P_ENUM_PARAM_AD_HOC_MODE_T;


typedef enum _ENUM_PARAM_OP_MODE_T {
    NET_TYPE_IBSS = 0,                  /*!< Try to merge/establish an AdHoc, do periodic SCAN for merging. */
    NET_TYPE_INFRA,                     /*!< Try to join an Infrastructure, do periodic SCAN for joining. */
    NET_TYPE_AUTO_SWITCH,               /*!< Try to join an Infrastructure, if fail then try to merge or
                                         establish an AdHoc, do periodic SCAN for joining or merging. */
    NET_TYPE_DEDICATED_IBSS,            /*!< Try to merge an AdHoc first, if fail then establish AdHoc permanently, no more SCAN. */
    NET_TYPE_NUM // 4
} ENUM_PARAM_OP_MODE_T, *P_ENUM_PARAM_OP_MODE_T;


typedef enum _ENUM_PARAM_PREAMBLE_TYPE_T {
    PREAMBLE_TYPE_LONG = 0,
    PREAMBLE_TYPE_SHORT,
    PREAMBLE_TYPE_AUTO                  /*!< Try preamble short first, if fail tray preamble long. */
} ENUM_PARAM_PREAMBLE_TYPE_T, *P_ENUM_PARAM_PREAMBLE_TYPE_T;

typedef struct _PARAM_SSID_T {
    UINT_32  u4SsidLen;      /*!< SSID length in bytes. Zero length is broadcast(any) SSID */
    UINT_8   aucSsid[PARAM_MAX_LEN_SSID];
} PARAM_SSID_T, *P_PARAM_SSID_T;


typedef enum _ENUM_PARAM_MEDIA_STATE_T {
    PARAM_MEDIA_STATE_CONNECTED,
    PARAM_MEDIA_STATE_DISCONNECTED
} ENUM_PARAM_MEDIA_STATE_T, *P_ENUM_PARAM_MEDIA_STATE_T;


typedef enum _ENUM_PARAM_NETWORK_TYPE_T {
    NETWORK_TYPE_FH,
    NETWORK_TYPE_DS,
    NETWORK_TYPE_OFDM5,
    NETWORK_TYPE_OFDM24,
    NETWORK_TYPE_AUTOMODE,
    NETWORK_TYPE_NUM                    /*!< Upper bound, not real case */
} ENUM_PARAM_NETWORK_TYPE_T, *P_ENUM_PARAM_NETWORK_TYPE_T;


typedef struct _PARAM_NETWORK_TYPE_LIST {
    UINT_32                     NumberOfItems;      /*!< At least 1 */
    ENUM_PARAM_NETWORK_TYPE_T   eNetworkType [1];
} PARAM_NETWORK_TYPE_LIST, *PPARAM_NETWORK_TYPE_LIST;

typedef enum _ENUM_PARAM_AUTH_MODE_T
{
    AUTH_MODE_OPEN,                     /*!< Open system */
    AUTH_MODE_SHARED,                   /*!< Shared key */
    AUTH_MODE_AUTO_SWITCH,              /*!< Either open system or shared key */
    AUTH_MODE_WPA,
    AUTH_MODE_WPA_PSK,
    AUTH_MODE_WPA_NONE,                 /*!< For Ad hoc */
    AUTH_MODE_WPA2,
    AUTH_MODE_WPA2_PSK,
    AUTH_MODE_NUM                       /*!< Upper bound, not real case */
} ENUM_PARAM_AUTH_MODE_T, *P_ENUM_PARAM_AUTH_MODE_T;

/* Encryption types */
typedef enum _ENUM_WEP_STATUS_T
{
    ENUM_WEP_ENABLED,
    ENUM_ENCRYPTION1_ENABLED = ENUM_WEP_ENABLED,
    ENUM_WEP_DISABLED,
    ENUM_ENCRYPTION_DISABLED = ENUM_WEP_DISABLED,
    ENUM_WEP_KEY_ABSENT,
    ENUM_ENCRYPTION1_KEY_ABSENT = ENUM_WEP_KEY_ABSENT,
    ENUM_WEP_NOT_SUPPORTED,
    ENUM_ENCRYPTION_NOT_SUPPORTED = ENUM_WEP_NOT_SUPPORTED,
    ENUM_ENCRYPTION2_ENABLED,
    ENUM_ENCRYPTION2_KEY_ABSENT,
    ENUM_ENCRYPTION3_ENABLED,
    ENUM_ENCRYPTION3_KEY_ABSENT
} ENUM_ENCRYPTION_STATUS_T, *P_ENUM_ENCRYPTION_STATUS_T;

typedef enum _ENUM_RELOAD_DEFAULTS
{
    ENUM_RELOAD_WEP_KEYS
} PARAM_RELOAD_DEFAULTS, *P_PARAM_RELOAD_DEFAULTS;

#if SUPPORT_WPS
/* Management frame type to which application IE is added */
enum {
       IEEE80211_APPIE_FRAME_BEACON            = 0,
       IEEE80211_APPIE_FRAME_PROBE_REQ         = 1,
       IEEE80211_APPIE_FRAME_PROBE_RESP        = 2,
       IEEE80211_APPIE_FRAME_ASSOC_REQ         = 3,
       IEEE80211_APPIE_FRAME_ASSOC_RESP        = 4,
       IEEE80211_APPIE_NUM_OF_FRAME            = 5
};
#endif

typedef enum _ENUM_PARAM_GPIO2_MODE_T
{
    GPIO2_MODE_EEPROM = 0,          /*!< Follow EEPROM GPIO2 setting */
    GPIO2_MODE_INT,                 /*!< 2.8 voltage interrupt, INT_N */
    GPIO2_MODE_DAISY_INPUT          /*!< Input of daisy chain for OSC_EN */
} ENUM_PARAM_GPIO2_MODE_T, *P_ENUM_PARAM_GPIO2_MODE_T;

/*--------------------------------------------------------------*/
/*! \brief Struct definition to indicate specific event.                */
/*--------------------------------------------------------------*/
typedef enum _ENUM_STATUS_TYPE_T
{
    ENUM_STATUS_TYPE_AUTHENTICATION,
    ENUM_STATUS_TYPE_MEDIA_STREAM_MODE,
    ENUM_STATUS_TYPE_CANDIDATE_LIST,
    ENUM_STATUS_TYPE_NUM              /*!< Upper bound, not real case */
} ENUM_STATUS_TYPE_T, *P_ENUM_STATUS_TYPE_T;


typedef struct _PARAM_802_11_CONFIG_FH_T {
    UINT_32                  u4Length;         /*!< Length of structure */
    UINT_32                  u4HopPattern;     /*!< Defined as 802.11 */
    UINT_32                  u4HopSet;         /*!< to one if non-802.11 */
    UINT_32                  u4DwellTime;      /*!< In unit of Kusec */
} PARAM_802_11_CONFIG_FH_T, *P_PARAM_802_11_CONFIG_FH_T;

typedef struct _PARAM_802_11_CONFIG_T {
    UINT_32                  u4Length;         /*!< Length of structure */
    UINT_32                  u4BeaconPeriod;   /*!< In unit of Kusec */
    UINT_32                  u4ATIMWindow;     /*!< In unit of Kusec */
    UINT_32                  u4DSConfig;       /*!< Channel frequency in unit of kHz */
    PARAM_802_11_CONFIG_FH_T rFHConfig;
} PARAM_802_11_CONFIG_T, *P_PARAM_802_11_CONFIG_T;

typedef struct _PARAM_STATUS_INDICATION_T
{
    ENUM_STATUS_TYPE_T   eStatusType;
} PARAM_STATUS_INDICATION_T, *P_PARAM_STATUS_INDICATION_T;

typedef struct _PARAM_AUTH_REQUEST_T
{
    UINT_32             u4Length;             /*!< Length of this struct */
    PARAM_MAC_ADDRESS   arBssid;
    UINT_32             u4Flags;              /*!< Definitions are as follows */
} PARAM_AUTH_REQUEST_T, *P_PARAM_AUTH_REQUEST_T;

typedef struct _PARAM_AUTH_EVENT_T
{
    PARAM_STATUS_INDICATION_T   rStatus;
    PARAM_AUTH_REQUEST_T        arRequest[1];
} PARAM_AUTH_EVENT_T, *P_PARAM_AUTH_EVENT_T;

/*! \brief Capabilities, privacy, rssi and IEs of each BSSID */
typedef struct _PARAM_BSSID_EX_T {
    UINT_32                         u4Length;             /*!< Length of structure */
    PARAM_MAC_ADDRESS               arMacAddress;         /*!< BSSID */
    UINT_8                          Reserved[2];
    PARAM_SSID_T                    rSsid;               /*!< SSID */
    UINT_32                         u4Privacy;            /*!< Need WEP encryption */
    PARAM_RSSI                      rRssi;               /*!< in dBm */
    ENUM_PARAM_NETWORK_TYPE_T       eNetworkTypeInUse;
    PARAM_802_11_CONFIG_T           rConfiguration;
    ENUM_PARAM_OP_MODE_T            eOpMode;
    PARAM_RATES_EX                  rSupportedRates;
    UINT_32                         u4IELength;
    //PUINT_8                         pucIEWPA;
    //PUINT_8                         pucIERSN;
    UINT_8                          aucIEs[1];
} PARAM_BSSID_EX_T, *P_PARAM_BSSID_EX_T;

typedef struct _PARAM_BSSID_LIST_EX {
    UINT_32                         u4NumberOfItems;      /*!< at least 1 */
    PARAM_BSSID_EX_T                arBssid[1];
} PARAM_BSSID_LIST_EX_T, *P_PARAM_BSSID_LIST_EX_T;


typedef struct _PARAM_WEP_T
{
    UINT_32             u4Length;             /*!< Length of structure */
    UINT_32             u4KeyIndex;           /*!< 0: pairwise key, others group keys */
    UINT_32             u4KeyLength;          /*!< Key length in bytes */
    UINT_8              aucKeyMaterial[1];    /*!< Key content by above setting */
} PARAM_WEP_T, *P_PARAM_WEP_T;

/*! \brief Key mapping of BSSID */
typedef struct _PARAM_KEY_T
{
    UINT_32             u4Length;             /*!< Length of structure */
    UINT_32             u4KeyIndex;           /*!< KeyID */
    UINT_32             u4KeyLength;          /*!< Key length in bytes */
    PARAM_MAC_ADDRESS   arBSSID;              /*!< MAC address */
    PARAM_KEY_RSC       rKeyRSC;
    UINT_8              aucKeyMaterial[1];    /*!< Key content by above setting */
} PARAM_KEY_T, *P_PARAM_KEY_T;

typedef struct _PARAM_REMOVE_KEY_T
{
    UINT_32             u4Length;             /*!< Length of structure */
    UINT_32             u4KeyIndex;           /*!< KeyID */
    PARAM_MAC_ADDRESS   arBSSID;               /*!< MAC address */
} PARAM_REMOVE_KEY_T, *P_PARAM_REMOVE_KEY_T;


typedef enum _PARAM_POWER_MODE
{
    Param_PowerModeCAM,
    Param_PowerModeMAX_PSP,
    Param_PowerModeFast_PSP,
    Param_PowerModeMax                      /* Upper bound, not real case */
} PARAM_POWER_MODE, *PPARAM_POWER_MODE;

typedef enum _PARAM_DEVICE_POWER_STATE
{
    ParamDeviceStateUnspecified = 0,
    ParamDeviceStateD0,
    ParamDeviceStateD1,
    ParamDeviceStateD2,
    ParamDeviceStateD3,
    ParamDeviceStateMaximum
} PARAM_DEVICE_POWER_STATE, *PPARAM_DEVICE_POWER_STATE;

#if CFG_SUPPORT_802_11D

/*! \brief The enumeration definitions for OID_IPN_MULTI_DOMAIN_CAPABILITY */
typedef enum _PARAM_MULTI_DOMAIN_CAPABILITY {
    ParamMultiDomainCapDisabled,
    ParamMultiDomainCapEnabled
} PARAM_MULTI_DOMAIN_CAPABILITY, *P_PARAM_MULTI_DOMAIN_CAPABILITY;
#endif

typedef struct _COUNTRY_STRING_ENTRY {
    UINT_8  aucCountryCode[2];
    UINT_8  aucEnvironmentCode[2];
} COUNTRY_STRING_ENTRY, *P_COUNTRY_STRING_ENTRY;

/* Power management related definition and enumerations */
#define UAPSD_NONE                              0
#define UAPSD_AC0                               (BIT(0) | BIT(4))
#define UAPSD_AC1                               (BIT(1) | BIT(5))
#define UAPSD_AC2                               (BIT(2) | BIT(6))
#define UAPSD_AC3                               (BIT(3) | BIT(7))
#define UAPSD_ALL                               (UAPSD_AC0 | UAPSD_AC1 | UAPSD_AC2 | UAPSD_AC3)

typedef enum _ENUM_POWER_SAVE_PROFILE_T
{
    ENUM_PSP_CONTINUOUS_ACTIVE = 0,
    ENUM_PSP_CONTINUOUS_POWER_SAVE,
    ENUM_PSP_FAST_SWITCH,
    ENUM_PSP_NUM
} ENUM_POWER_SAVE_PROFILE_T, *PENUM_POWER_SAVE_PROFILE_T;


/*--------------------------------------------------------------*/
/*! \brief Set/Query testing type.                              */
/*--------------------------------------------------------------*/
typedef struct _PARAM_802_11_TEST_T
{
    UINT_32             u4Length;
    UINT_32             u4Type;
    union
    {
        PARAM_AUTH_EVENT_T  AuthenticationEvent;
        PARAM_RSSI          RssiTrigger;
    } u;
} PARAM_802_11_TEST_T, *P_PARAM_802_11_TEST_T;

/*--------------------------------------------------------------*/
/*! \brief Set/Query authentication and encryption capability.  */
/*--------------------------------------------------------------*/
typedef struct _PARAM_AUTH_ENCRYPTION_T
{
    ENUM_PARAM_AUTH_MODE_T      eAuthModeSupported;
    ENUM_ENCRYPTION_STATUS_T    eEncryptStatusSupported;
} PARAM_AUTH_ENCRYPTION_T, *P_PARAM_AUTH_ENCRYPTION_T;

typedef struct _PARAM_CAPABILITY_T
{
     UINT_32                  u4Length;
     UINT_32                  u4Version;
     UINT_32                  u4NoOfPMKIDs;
     UINT_32                  u4NoOfAuthEncryptPairsSupported;
     PARAM_AUTH_ENCRYPTION_T  arAuthenticationEncryptionSupported[1];
} PARAM_CAPABILITY_T, *P_PARAM_CAPABILITY_T;

typedef UINT_8   PARAM_PMKID_VALUE[16];

typedef struct _PARAM_BSSID_INFO_T
{
    PARAM_MAC_ADDRESS   arBSSID;
    PARAM_PMKID_VALUE   arPMKID;
} PARAM_BSSID_INFO_T, *P_PARAM_BSSID_INFO_T;

typedef struct _PARAM_PMKID_T
{
    UINT_32             u4Length;
    UINT_32             u4BSSIDInfoCount;
    PARAM_BSSID_INFO_T  arBSSIDInfo[1];
} PARAM_PMKID_T, *P_PARAM_PMKID_T;

/*! \brief PMKID candidate lists. */
typedef struct _PARAM_PMKID_CANDIDATE_T {
    PARAM_MAC_ADDRESS   arBSSID;
    UINT_32             u4Flags;
} PARAM_PMKID_CANDIDATE_T, *P_PARAM_PMKID_CANDIDATE_T;

/* Flags for PMKID Candidate list structure */
#define PARAM_PMKID_CANDIDATE_PREAUTH_ENABLED   0x01

typedef struct _PARAM_PMKID_CANDIDATE_LIST_T
{
    UINT_32                   u4Version;            /*!< Version */
    UINT_32                   u4NumCandidates;      /*!< How many candidates follow */
    PARAM_PMKID_CANDIDATE_T   arCandidateList[1];
} PARAM_PMKID_CANDIDATE_LIST_T, *P_PARAM_PMKID_CANDIDATE_LIST_T;


typedef struct _PARAM_CUSTOM_MCR_RW_STRUC_T {
    UINT_32             u4McrOffset;
    UINT_32             u4McrData;
} PARAM_CUSTOM_MCR_RW_STRUC_T, *P_PARAM_CUSTOM_MCR_RW_STRUC_T;


typedef struct _PARAM_CUSTOM_EEPROM_RW_STRUC_T {
    UINT_8              ucEepromMethod; /* For read only read: 1, query size: 0*/
    UINT_8              ucEepromIndex;
    UINT_8              reserved;
    UINT_16            u2EepromData;
} PARAM_CUSTOM_EEPROM_RW_STRUC_T, *P_PARAM_CUSTOM_EEPROM_RW_STRUC_T;

typedef struct _PARAM_CUSTOM_WMM_PS_TEST_STRUC_T {
    UINT_8  bmfgApsdEnAc;           /* b0~3: trigger-en AC0~3. b4~7: delivery-en AC0~3 */
    UINT_8  ucIsEnterPsAtOnce;      /* enter PS immediately without 5 second guard after connected */
    UINT_8  ucIsDisableUcTrigger;   /* not to trigger UC on beacon TIM is matched (under U-APSD) */
    UINT_8  reserved;
} PARAM_CUSTOM_WMM_PS_TEST_STRUC_T, *P_PARAM_CUSTOM_WMM_PS_TEST_STRUC_T;

/*  RF Test for rx status */
typedef struct  _PARAM_CUSTOM_RFTEST_RX_STATUS_STRUC_T {
    UINT_32             u4IntRxOk;            /*!< number of packets that Rx ok from interrupt */
    UINT_32             u4IntCrcErr;          /*!< number of packets that CRC error from interrupt */
    UINT_32             u4IntShort;           /*!< number of packets that is short preamble from interrupt */
    UINT_32             u4IntLong;            /*!< number of packets that is long preamble from interrupt */
    UINT_32             u4PauRxPktCount;      /*!< number of packets that Rx ok from PAU */
    UINT_32             u4PauCrcErrCount;     /*!< number of packets that CRC error from PAU */
    UINT_32             u4PauRxFifoFullCount; /*!< number of packets that is short preamble from PAU */
    UINT_32             u4PauCCACount;        /*!< CCA rising edge count */
} PARAM_CUSTOM_RFTEST_RX_STATUS_STRUC_T, *P_PARAM_CUSTOM_RFTEST_RX_STATUS_STRUC_T;

/* Renbang : ++ (20100319)*/
typedef struct  _PARAM_CUSTOM_RFTEST_RX_STATUS_EX_STRUC_T {
	PARAM_CUSTOM_RFTEST_RX_STATUS_STRUC_T rRxStatus;

    /* Renbang : RSSI record */
#if 1	
    UINT_32 			u4RssiMax;
    UINT_32 			u4RssiMin;
    UINT_32 			u4RssiAvg;
    UINT_32 			u4RssiVar;
#endif	
} PARAM_CUSTOM_RFTEST_RX_STATUS_EX_STRUC_T, *P_PARAM_CUSTOM_RFTEST_RX_STATUS_EX_STRUC_T;
/* Renbang : -- (20100319)*/

/*  RF Test for tx status */
typedef struct _PARAM_CUSTOM_RFTEST_TX_STATUS_STRUC_T {
    UINT_32             u4PktSentStatus;
    UINT_32             u4PktSentCount;
    UINT_16             u2AvgAlc;
    UINT_8              ucCckGainControl;
    UINT_8              ucOfdmGainControl;
} PARAM_CUSTOM_RFTEST_TX_STATUS_STRUC_T, *P_PARAM_CUSTOM_RFTEST_TX_STATUS_STRUC_T;

typedef struct _PTA_PARAM_T {
    UINT_32     u4BtCR0;  /*BTCER0*/
    UINT_32     u4BtCR1;  /*BTCER1, Bit[30,29]: 2'b00: 1-wire, 2'b01: 2-wire,
                                                2'b10: 3-wire, 2'b11: 4-wire */
    UINT_32     u4BtCR2;  /*BTCER2*/
    UINT_32     u4BtCR3;  /*BTCER3*/
} PTA_PARAM_T, *P_PTA_PARAM_T;

typedef struct _PARAM_CUSTOM_BT_COEXIST_T {
    PTA_PARAM_T         rPtaParam;

    UINT_32             u4IsEnableTxAutoFragmentForBT;
    UINT_32             eBTCoexistWindowType;
} PARAM_CUSTOM_BT_COEXIST_T, *P_PARAM_CUSTOM_BT_COEXIST_T;


typedef struct _PARAM_QOS_TSINFO {
    UINT_8           ucTrafficType;         /* Traffic Type: 1 for isochronous 0 for asynchronous */
    UINT_8           ucTid;                 /* TSID: must be between 8 ~ 15 */
    UINT_8           ucDirection;           /* direction */
    UINT_8           ucAccessPolicy;        /* access policy */
    UINT_8           ucAggregation;         /* aggregation */
    UINT_8           ucApsd;                /* APSD */
    UINT_8           ucuserPriority;        /* user priority */
    UINT_8           ucTsInfoAckPolicy;     /* TSINFO ACK policy */
    UINT_8           ucSchedule;            /* Schedule */
} PARAM_QOS_TSINFO, *P_PARAM_QOS_TSINFO;

typedef struct _PARAM_QOS_TSPEC {
    PARAM_QOS_TSINFO rTsInfo;               /* TS info field */
    UINT_16          u2NominalMSDUSize;     /* nominal MSDU size */
    UINT_16          u2MaxMSDUsize;         /* maximum MSDU size */
    UINT_32          u4MinSvcIntv;          /* minimum service interval */
    UINT_32          u4MaxSvcIntv;          /* maximum service interval */
    UINT_32          u4InactIntv;           /* inactivity interval */
    UINT_32          u4SpsIntv;             /* suspension interval */
    UINT_32          u4SvcStartTime;        /* service start time */
    UINT_32          u4MinDataRate;         /* minimum Data rate */
    UINT_32          u4MeanDataRate;        /* mean data rate */
    UINT_32          u4PeakDataRate;        /* peak data rate */
    UINT_32          u4MaxBurstSize;        /* maximum burst size */
    UINT_32          u4DelayBound;          /* delay bound */
    UINT_32          u4MinPHYRate;          /* minimum PHY rate */
    UINT_16          u2Sba;                 /* surplus bandwidth allowance */
    UINT_16          u2MediumTime;          /* medium time */
} PARAM_QOS_TSPEC, *P_PARAM_QOS_TSPEC;

typedef struct _PARAM_QOS_ADDTS_REQ_INFO {
    PARAM_QOS_TSPEC             rTspec;
} PARAM_QOS_ADDTS_REQ_INFO, *P_PARAM_QOS_ADDTS_REQ_INFO;

typedef struct _PARAM_VOIP_CONFIG {
    UINT_32         u4VoipTrafficInterval;  /* 0: disable VOIP configuration */
} PARAM_VOIP_CONFIG, *P_PARAM_VOIP_CONFIG;

/*802.11 Statistics Struct*/
typedef struct _PARAM_802_11_STATISTICS_STRUCT_T {
    UINT_32         u4Length;             // Length of structure
    LARGE_INTEGER   rTransmittedFragmentCount;
    LARGE_INTEGER   rMulticastTransmittedFrameCount;
    LARGE_INTEGER   rFailedCount;
    LARGE_INTEGER   rRetryCount;
    LARGE_INTEGER   rMultipleRetryCount;
    LARGE_INTEGER   rRTSSuccessCount;
    LARGE_INTEGER   rRTSFailureCount;
    LARGE_INTEGER   rACKFailureCount;
    LARGE_INTEGER   rFrameDuplicateCount;
    LARGE_INTEGER   rReceivedFragmentCount;
    LARGE_INTEGER   rMulticastReceivedFrameCount;
    LARGE_INTEGER   rFCSErrorCount;
} PARAM_802_11_STATISTICS_STRUCT_T, *P_PARAM_802_11_STATISTICS_STRUCT_T;

/* Linux Network Device Statistics Struct */
typedef struct _PARAM_LINUX_NETDEV_STATISTICS_T {
    UINT_32         u4RxPackets;
    UINT_32         u4TxPackets;
    UINT_32         u4RxBytes;
    UINT_32         u4TxBytes;
    UINT_32         u4RxErrors;
    UINT_32         u4TxErrors;
    UINT_32         u4Multicast;
} PARAM_LINUX_NETDEV_STATISTICS_T, *P_PARAM_LINUX_NETDEV_STATISTICS_T;


typedef enum _ENUM_PARAM_BT_COEXIST_WINDOW_T {
    BT_COEXIST_WINDOW_650 = 0,
    BT_COEXIST_WINDOW_1250,
    BT_COEXIST_WINDOW_2500,
    BT_COEXIST_WINDOW_TYPE_NUM
} ENUM_PARAM_BT_COEXIST_WINDOW_T, *P_ENUM_PARAM_BT_COEXIST_WINDOW_T;

/*  Pattern search relate configurations */
typedef struct  _PARAM_CUSTOM_PATTERN_SEARCH_CONFIG_STRUC_T {
    struct {
        BOOLEAN fgBcPatternMatchEnable;
        BOOLEAN fgMcPatternMatchEnable;
        BOOLEAN fgUcPatternMatchEnable;
        BOOLEAN fgBcPatternMatchOperation;
        BOOLEAN fgMcPatternMatchOperation;
        BOOLEAN fgUcPatternMatchOperation;
        BOOLEAN fgIpv6MatchCtrl;
    } rFunc;
    struct {
        IN UINT_8       ucIndex;
        IN BOOLEAN      fgCheckBcA1;
        IN BOOLEAN      fgCheckMcA1;
        IN BOOLEAN      fgCheckUcA1;
        IN BOOLEAN      fgIpv4Ip;
        IN BOOLEAN      fgIpv6Icmp;
        IN BOOLEAN      fgGarpIpEqual;
        IN BOOLEAN      fgArpCtrl;
        IN BOOLEAN      fgAndOp;
        IN BOOLEAN      fgNotOp;
        IN UINT_8       ucPatternMask;
        IN UINT_8       ucPatternOffset;
        IN UINT_32      au4Pattern[2];
    } arPattern[32];
} PARAM_CUSTOM_PATTERN_SEARCH_CONFIG_STRUC_T, *P_PARAM_CUSTOM_PATTERN_SEARCH_CONFIG_STRUC_T;


/* For Continuous Poll Profile Struct */
typedef struct _PARAM_CONTINUOUS_POLL_T {
    UINT_32         u4PollInterval; // 0: disable poll, else: enable with specific interval
} PARAM_CONTINUOUS_POLL_T, *P_PARAM_CONTINUOUS_POLL_T;

#if PTA_ENABLED

typedef enum _ENUM_BT_CMD_T {
    BT_CMD_PROFILE = 0,
    BT_CMD_UPDATE,
    BT_CMD_NUM
} ENUM_BT_CMD_T;

typedef enum _ENUM_BT_PROFILE_T {
    BT_PROFILE_CUSTOM = 0,
    BT_PROFILE_SCO,
    BT_PROFILE_ACL,
    BT_PROFILE_MIXED,
    BT_PROFILE_NO_CONNECTION,
    BT_PROFILE_NUM
} ENUM_BT_PROFILE_T;
#if PTA_NEW_BOARD_DESIGN
#define BTPPARAM_PTA_MODE_OFFSET  6
#define BTPPARAM_PTA_MODE_VALID   BIT(0)
#define BTPPARAM_PTA_MODE_SINGLE  0
#define BTPPARAM_PTA_MODE_DUAL    BIT(1)
#endif
typedef struct _PTA_PROFILE_T {
    ENUM_BT_PROFILE_T eBtProfile;
    union {
        UINT_8 aucBTPParams[BT_PROFILE_PARAM_LEN];
                                /*  0: sco reserved slot time,
                                    1: sco idle slot time,
                                    2: acl throughput,
                                    3: bt tx power,
                                    4: bt rssi
                                    5: VoIP interval
                                    6: BIT(0) Use this field, BIT(1) 0 apply single/ 1 dual PTA setting. 
                                */
        UINT_32 au4Btcr[4];
    } u;
} PTA_PROFILE_T, *P_PTA_PROFILE_T;



typedef enum _ENUM_BT_PROFILE_PARAM_T {
    BTP_PARAM_SCO_RESERVED_TIME = 0,
    BTP_PARAM_SCO_IDLE_TIME,
    BTP_PARAM_ACL_THROUGHPUT,
    BTP_PARAM_ACL_TX_POWER,
    BTP_PARAM_ACL_RX_POWER,
    BTP_PARAM_VOIP_INTERVAL,
    BTP_PARAM_NUM
} ENUM_BT_PROFILE_PARAM_T;

typedef struct _PTA_IPC_T {
    UINT_8      ucCmd;
    UINT_8      ucLen;
    union {
        PTA_PROFILE_T rProfile;
        UINT_8      aucBTPParams[BT_PROFILE_PARAM_LEN];
    } u;
} PARAM_PTA_IPC_T, *P_PARAM_PTA_IPC_T, PTA_IPC_T, *P_PTA_IPC_T;

#endif

/* Renbang : ++ (20100319)*/
typedef enum _ENUM_CFG_SRC_TYPE_T {
    CFG_SRC_TYPE_EEPROM,
    CFG_SRC_TYPE_NVRAM,
    CFG_SRC_TYPE_UNKNOWN,
    CFG_SRC_TYPE_NUM                    /*!< Upper bound, not real case */
} ENUM_CFG_SRC_TYPE_T, *P_ENUM_CFG_SRC_TYPE_T;

typedef enum _ENUM_EEPROM_TYPE_T {
    EEPROM_TYPE_NO,
    EEPROM_TYPE_PRESENT,
    EEPROM_TYPE_NUM                    /*!< Upper bound, not real case */
} ENUM_EEPROM_TYPE_T, *P_ENUM_EEPROM_TYPE_T;
/* Renbang : -- (20100319)*/
#if 0 /* SUPPORT_WAPI */
#define MAX_TURTLENECK_NUMBER       16
#define BKID_LEN                    16

typedef struct _WPI_BKID{
    UINT_8       ucBKIDIdentify[BKID_LEN];
} WPI_BKID;

typedef struct _PARAM_WAPI_ASSOC_INFO_T {
    UINT_8       ucElementID;
    UINT_8       ucLength;
    UINT_16      u2Version;
    UINT_16      u2AKMNum;
    UINT_32      u4AKMList[MAX_TURTLENECK_NUMBER];
    UINT_16      u2SingleCodeNum;
    UINT_32      u4SingleCodeList[MAX_TURTLENECK_NUMBER];
    UINT_32      u4MultiCode;
    UINT_16      u2WapiAbility;
    UINT_16      u2BKIDNumber;
    WPI_BKID     BKIDList[MAX_TURTLENECK_NUMBER];
} PARAM_WAPI_ASSOC_INFO_T, *P_PARAM_WAPI_ASSOC_INFO_T;
#endif

#if SUPPORT_WAPI
typedef enum _ENUM_KEY_TYPE {
    ENUM_WPI_PAIRWISE_KEY = 0,
    ENUM_WPI_GROUP_KEY
} ENUM_KEY_TYPE; 

typedef enum _ENUM_WPI_PROTECT_TYPE
{
    ENUM_WPI_NONE,
    ENUM_WPI_RX,
    ENUM_WPI_TX,
    ENUM_WPI_RX_TX
} ENUM_WPI_PROTECT_TYPE;

typedef struct _PARAM_WPI_KEY_T {
    ENUM_KEY_TYPE           eKeyType;
    ENUM_WPI_PROTECT_TYPE   eDirection;
    UINT_8                  ucKeyID;
    UINT_8                  aucRsv[3];
    UINT_8                  aucAddrIndex[12];
    UINT_32                 u4LenWPIEK;
    UINT_8                  aucWPIEK[256];
    UINT_32                 u4LenWPICK;
    UINT_8                  aucWPICK[256];
    UINT_8                  aucPN[16];
} PARAM_WPI_KEY_T, *P_PARAM_WPI_KEY_T;

#endif
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
/*--------------------------------------------------------------*/
/* Routines to set parameters or query information.             */
/*--------------------------------------------------------------*/
/***** Routines in wlan_oid.c *****/
WLAN_STATUS
wlanoidQueryNetworkTypesSupported(
    IN  P_ADAPTER_T       prAdapter,
    OUT PVOID             pvQueryBuffer,
    IN  UINT_32           u4QueryBufferLen,
    OUT PUINT_32          pu4QueryInfoLen
    );

WLAN_STATUS
wlanoidQueryNetworkTypeInUse(
    IN  P_ADAPTER_T       prAdapter,
    OUT PVOID             pvQueryBuffer,
    IN  UINT_32           u4QueryBufferLen,
    OUT PUINT_32          pu4QueryInfoLen
    );

WLAN_STATUS
wlanoidSetNetworkTypeInUse (
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID             pvSetBuffer,
    IN  UINT_32           u4SetBufferLen,
    OUT PUINT_32          pu4SetInfoLen
    );

WLAN_STATUS
wlanoidQueryBssid(
    IN  P_ADAPTER_T       prAdapter,
    OUT PVOID             pvQueryBuffer,
    IN  UINT_32           u4QueryBufferLen,
    OUT PUINT_32          pu4QueryInfoLen
    );

WLAN_STATUS
wlanoidSetBssidListScan(
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID             pvSetBuffer,
    IN  UINT_32           u4SetBufferLen,
    OUT PUINT_32          pu4SetInfoLen
    );

WLAN_STATUS
wlanoidQueryBssidList(
    IN  P_ADAPTER_T       prAdapter,
    OUT PVOID             pvQueryBuffer,
    IN  UINT_32           u4QueryBufferLen,
    OUT PUINT_32          pu4QueryInfoLen
    );

WLAN_STATUS
wlanoidSetBssid(
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID             pvSetBuffer,
    IN  UINT_32           u4SetBufferLen,
    OUT PUINT_32          pu4SetInfoLen
    );

WLAN_STATUS
wlanoidSetSsid(
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID             pvSetBuffer,
    IN  UINT_32           u4SetBufferLen,
    OUT PUINT_32          pu4SetInfoLen
    );

WLAN_STATUS
wlanoidQuerySsid(
    IN  P_ADAPTER_T       prAdapter,
    OUT PVOID             pvQueryBuffer,
    IN  UINT_32           u4QueryBufferLen,
    OUT PUINT_32          pu4QueryInfoLen
    );

WLAN_STATUS
wlanoidQueryInfrastructureMode(
    IN  P_ADAPTER_T       prAdapter,
    OUT PVOID             pvQueryBuffer,
    IN  UINT_32           u4QueryBufferLen,
    OUT PUINT_32          pu4QueryInfoLen
    );

WLAN_STATUS
wlanoidSetInfrastructureMode(
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID             pvSetBuffer,
    IN  UINT_32           u4SetBufferLen,
    OUT PUINT_32          pu4SetInfoLen
    );

WLAN_STATUS
wlanoidQueryAuthMode(
    IN  P_ADAPTER_T       prAdapter,
    OUT PVOID             pvQueryBuffer,
    IN  UINT_32           u4QueryBufferLen,
    OUT PUINT_32          pu4QueryInfoLen
    );

WLAN_STATUS
wlanoidSetAuthMode(
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID             pvSetBuffer,
    IN  UINT_32           u4SetBufferLen,
    OUT PUINT_32          pu4SetInfoLen
    );

WLAN_STATUS
wlanoidSetEncryptionStatus(
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID             pvSetBuffer,
    IN  UINT_32           u4SetBufferLen,
    OUT PUINT_32          pu4SetInfoLen
    );

WLAN_STATUS
wlanoidQueryEncryptionStatus(
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID             pvQueryBuffer,
    IN  UINT_32           u4QueryBufferLen,
    OUT PUINT_32          pu4QueryInfoLen
    );

WLAN_STATUS
wlanoidSetAddWep(
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID    pvSetBuffer,
    IN  UINT_32  u4SetBufferLen,
    OUT PUINT_32 pu4SetInfoLen
    );

WLAN_STATUS
wlanoidSetRemoveWep(
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID             pvSetBuffer,
    IN  UINT_32           u4SetBufferLen,
    OUT PUINT_32          pu4SetInfoLen
    );

WLAN_STATUS
wlanoidSetAddKey(
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID             pvSetBuffer,
    IN  UINT_32           u4SetBufferLen,
    OUT PUINT_32          pu4SetInfoLen
    );

WLAN_STATUS
wlanoidSetRemoveKey(
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID    pvSetBuffer,
    IN  UINT_32  u4SetBufferLen,
    OUT PUINT_32 pu4SetInfoLen
    );

WLAN_STATUS
wlanoidSetReloadDefaults(
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID             pvSetBuffer,
    IN  UINT_32           u4SetBufferLen,
    OUT PUINT_32          pu4SetInfoLen
    );

WLAN_STATUS
wlanoidSetTest(
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID             pvSetBuffer,
    IN  UINT_32           u4SetBufferLen,
    OUT PUINT_32          pu4SetInfoLen
    );

WLAN_STATUS
wlanoidQueryCapability(
    IN  P_ADAPTER_T       prAdapter,
    OUT PVOID             pvQueryBuffer,
    IN  UINT_32           u4QueryBufferLen,
    OUT PUINT_32          pu4QueryInfoLen
    );

WLAN_STATUS
wlanoidQueryFrequency (
    IN  P_ADAPTER_T prAdapter,
    OUT PVOID       pvQueryBuffer,
    IN  UINT_32     u4QueryBufferLen,
    OUT PUINT_32    pu4QueryInfoLen
    );

WLAN_STATUS
wlanoidSetFrequency (
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID             pvSetBuffer,
    IN  UINT_32           u4SetBufferLen,
    OUT PUINT_32          pu4SetInfoLen
    );


WLAN_STATUS
wlanoidQueryAtimWindow (
    IN  P_ADAPTER_T prAdapter,
    OUT PVOID       pvQueryBuffer,
    IN  UINT_32     u4QueryBufferLen,
    OUT PUINT_32    pu4QueryInfoLen
    );

WLAN_STATUS
wlanoidSetAtimWindow (
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID             pvSetBuffer,
    IN  UINT_32           u4SetBufferLen,
    OUT PUINT_32          pu4SetInfoLen
    );


WLAN_STATUS
wlanoidSetChannel (
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID             pvSetBuffer,
    IN  UINT_32           u4SetBufferLen,
    OUT PUINT_32          pu4SetInfoLen
    );

WLAN_STATUS
wlanoidQueryRssi(
    IN  P_ADAPTER_T       prAdapter,
    OUT PVOID             pvQueryBuffer,
    IN  UINT_32           u4QueryBufferLen,
    OUT PUINT_32          pu4QueryInfoLen
    );

WLAN_STATUS
wlanoidQueryRssiTrigger(
    IN  P_ADAPTER_T       prAdapter,
    OUT PVOID             pvQueryBuffer,
    IN  UINT_32           u4QueryBufferLen,
    OUT PUINT_32          pu4QueryInfoLen
    );

WLAN_STATUS
wlanoidSetRssiTrigger(
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID             pvSetBuffer,
    IN  UINT_32           u4SetBufferLen,
    OUT PUINT_32          pu4SetInfoLen
    );

WLAN_STATUS
wlanoidQueryRtsThreshold (
    IN  P_ADAPTER_T prAdapter,
    OUT PVOID       pvQueryBuffer,
    IN  UINT_32     u4QueryBufferLen,
    OUT PUINT_32    pu4QueryInfoLen
    );

WLAN_STATUS
wlanoidSetRtsThreshold (
    IN  P_ADAPTER_T prAdapter,
    IN  PVOID       pvSetBuffer,
    IN  UINT_32     u4SetBufferLen,
    OUT PUINT_32    pu4SetInfoLen
    );

WLAN_STATUS
wlanoidSetPatternConfig (
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID             pvSetBuffer,
    IN  UINT_32           u4SetBufferLen,
    OUT PUINT_32          pu4SetInfoLen
    );

WLAN_STATUS
wlanoidSetPwrMgmtProfParam (
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID             pvSetBuffer,
    IN  UINT_32           u4SetBufferLen,
    OUT PUINT_32          pu4SetInfoLen
    );

WLAN_STATUS
wlanoidQueryPwrMgmtProfParam (
    IN  P_ADAPTER_T prAdapter,
    OUT PVOID       pvQueryBuffer,
    IN  UINT_32     u4QueryBufferLen,
    OUT PUINT_32    pu4QueryInfoLen
    );

WLAN_STATUS
wlanoidQuery802dot11PowerSaveProfile (
    IN  P_ADAPTER_T prAdapter,
    IN  PVOID       pvQueryBuffer,
    IN  UINT_32     u4QueryBufferLen,
    OUT PUINT_32    pu4QueryInfoLen
    );

WLAN_STATUS
wlanoidSet802dot11PowerSaveProfile (
    IN  P_ADAPTER_T prAdapter,
    IN  PVOID       prSetBuffer,
    IN  UINT_32     u4SetBufferLen,
    OUT PUINT_32    pu4SetInfoLen
    );

WLAN_STATUS
wlanoidQueryPmkid(
    IN  P_ADAPTER_T       prAdapter,
    OUT PVOID             pvQueryBuffer,
    IN  UINT_32           u4QueryBufferLen,
    OUT PUINT_32          pu4QueryInfoLen
    );

WLAN_STATUS
wlanoidSetPmkid(
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID             pvSetBuffer,
    IN  UINT_32           u4SetBufferLen,
    OUT PUINT_32          pu4SetInfoLen
    );

WLAN_STATUS
wlanoidQuerySupportedRates(
    IN  P_ADAPTER_T       prAdapter,
    OUT PVOID             pvQueryBuffer,
    IN  UINT_32           u4QueryBufferLen,
    OUT PUINT_32          pu4QueryInfoLen
    );

WLAN_STATUS
wlanoidQueryDesiredRates (
    IN  P_ADAPTER_T prAdapter,
    OUT PVOID       pvQueryBuffer,
    IN  UINT_32     u4QueryBufferLen,
    OUT PUINT_32    pu4QueryInfoLen
    );

WLAN_STATUS
wlanoidSetDesiredRates (
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID             pvSetBuffer,
    IN  UINT_32           u4SetBufferLen,
    OUT PUINT_32          pu4SetInfoLen
    );

WLAN_STATUS
wlanoidQueryPermanentAddr (
    IN P_ADAPTER_T  prAdapter,
    IN  PVOID    pvQueryBuf,
    IN  UINT_32  u4QueryBufLen,
    OUT PUINT_32 pu4QueryInfoLen
    );

WLAN_STATUS
wlanoidQueryCurrentAddr (
    IN P_ADAPTER_T  prAdapter,
    IN  PVOID    pvQueryBuf,
    IN  UINT_32  u4QueryBufLen,
    OUT PUINT_32 pu4QueryInfoLen
    );

WLAN_STATUS
wlanoidQueryPermanentAddr (
    IN P_ADAPTER_T  prAdapter,
    IN  PVOID    pvQueryBuf,
    IN  UINT_32  u4QueryBufLen,
    OUT PUINT_32 pu4QueryInfoLen
    );

WLAN_STATUS
wlanoidQueryLinkSpeed(
    IN P_ADAPTER_T  prAdapter,
    IN  PVOID    pvQueryBuffer,
    IN  UINT_32  u4QueryBufferLen,
    OUT PUINT_32 pu4QueryInfoLen
    );

WLAN_STATUS
wlanoidQueryMcrRead (
    IN P_ADAPTER_T  prAdapter,
    IN  PVOID    pvQueryBuffer,
    IN  UINT_32  u4QueryBufferLen,
    OUT PUINT_32 pu4QueryInfoLen
    );

WLAN_STATUS
wlanoidSetMcrWrite (
    IN P_ADAPTER_T  prAdapter,
    IN  PVOID    pvSetBuffer,
    IN  UINT_32  u4SetBufferLen,
    OUT PUINT_32 pu4SetInfoLen
    );

WLAN_STATUS
wlanoidOidTest(
    IN P_ADAPTER_T  prAdapter,
    IN  PVOID    pvSetBuffer,
    IN  UINT_32  u4SetBufferLen,
    OUT PUINT_32 pu4SetInfoLen
    );


WLAN_STATUS
wlanoidQueryEepromRead (
    IN  P_ADAPTER_T  prAdapter,
    IN  PVOID        pvQueryBuffer,
    IN  UINT_32      u4QueryBufferLen,
    OUT PUINT_32     pu4QueryInfoLen
    );

WLAN_STATUS
wlanoidSetEepromWrite (
    IN P_ADAPTER_T  prAdapter,
    IN  PVOID       pvSetBuffer,
    IN  UINT_32     u4SetBufferLen,
    OUT PUINT_32    pu4SetInfoLen
    );

WLAN_STATUS
wlanoidQueryRfTestRxStatus (
    IN  P_ADAPTER_T  prAdapter,
    IN  PVOID        pvQueryBuffer,
    IN  UINT_32      u4QueryBufferLen,
    OUT PUINT_32     pu4QueryInfoLen
    );

WLAN_STATUS
wlanoidQueryRfTestTxStatus (
    IN  P_ADAPTER_T  prAdapter,
    IN  PVOID        pvQueryBuffer,
    IN  UINT_32      u4QueryBufferLen,
    OUT PUINT_32     pu4QueryInfoLen
    );

WLAN_STATUS
wlanoidQueryOidInterfaceVersion (
    IN P_ADAPTER_T  prAdapter,
    IN  PVOID    pvQueryBuffer,
    IN  UINT_32  u4QueryBufferLen,
    OUT PUINT_32 pu4QueryInfoLen
    );

WLAN_STATUS
wlanoidQueryVendorId(
    IN  P_ADAPTER_T       prAdapter,
    OUT PVOID             pvQueryBuffer,
    IN  UINT_32           u4QueryBufferLen,
    OUT PUINT_32          pu4QueryInfoLen
    );

WLAN_STATUS
wlanoidQueryMulticastList(
    IN  P_ADAPTER_T prAdapter,
    OUT PVOID       pvQueryBuffer,
    IN  UINT_32     u4QueryBufferLen,
    OUT PUINT_32    pu4QueryInfoLen
    );

WLAN_STATUS
wlanoidSetMulticastList(
    IN  P_ADAPTER_T prAdapter,
    IN  PVOID       pvSetBuffer,
    IN  UINT_32     u4SetBufferLen,
    OUT PUINT_32    pu4SetInfoLen
    );

WLAN_STATUS
wlanoidQueryRcvError (
    IN  P_ADAPTER_T     prAdapter,
    IN  PVOID           pvQueryBuffer,
    IN  UINT_32         u4QueryBufferLen,
    OUT PUINT_32        pu4QueryInfoLen
    );

WLAN_STATUS
wlanoidQueryRcvNoBuffer (
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID             pvQueryBuffer,
    IN  UINT_32           u4QueryBufferLen,
    OUT PUINT_32          pu4QueryInfoLen
    );

WLAN_STATUS
wlanoidQueryRcvCrcError (
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID             pvQueryBuffer,
    IN  UINT_32           u4QueryBufferLen,
    OUT PUINT_32          pu4QueryInfoLen
    );

WLAN_STATUS
wlanoidQueryStatistics (
    IN  P_ADAPTER_T     prAdapter,
    IN  PVOID           pvQueryBuffer,
    IN  UINT_32         u4QueryBufferLen,
    OUT PUINT_32        pu4QueryInfoLen
    );

WLAN_STATUS
wlanoidQueryStatisticsForLinux (
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID             pvQueryBuffer,
    IN  UINT_32           u4QueryBufferLen,
    OUT PUINT_32          pu4QueryInfoLen
    );

WLAN_STATUS
wlanoidQueryRcvOk(
    IN P_ADAPTER_T  prAdapter,
    IN  PVOID           pvQueryBuffer,
    IN  UINT_32         u4QueryBufferLen,
    OUT PUINT_32        pu4QueryInfoLen
    );

WLAN_STATUS
wlanoidQueryXmitOk(
    IN P_ADAPTER_T  prAdapter,
    IN  PVOID       pvQueryBuffer,
    IN  UINT_32     u4QueryBufferLen,
    OUT PUINT_32    pu4QueryInfoLen
    );

WLAN_STATUS
wlanoidQueryXmitError (
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID           pvQueryBuffer,
    IN  UINT_32         u4QueryBufferLen,
    OUT PUINT_32          pu4QueryInfoLen
    );

WLAN_STATUS
wlanoidQueryXmitOneCollision (
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID           pvQueryBuffer,
    IN  UINT_32         u4QueryBufferLen,
    OUT PUINT_32          pu4QueryInfoLen
    );

WLAN_STATUS
wlanoidQueryXmitMoreCollisions (
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID           pvQueryBuffer,
    IN  UINT_32         u4QueryBufferLen,
    OUT PUINT_32          pu4QueryInfoLen
    );

WLAN_STATUS
wlanoidQueryXmitMaxCollisions (
    IN  P_ADAPTER_T       prAdapter,
    IN   PVOID           pvQueryBuffer,
    IN   UINT_32         u4QueryBufferLen,
    OUT PUINT_32          pu4QueryInfoLen
    );


WLAN_STATUS
wlanoidSetCurrentPacketFilter(
    IN P_ADAPTER_T  prAdapter,
    IN  PVOID    pvSetBuffer,
    IN  UINT_32  u4SetBufferLen,
    OUT PUINT_32 pu4SetInfoLen
    );

WLAN_STATUS
wlanoidQueryCurrentPacketFilter (
    IN P_ADAPTER_T prAdapter,
    IN  PVOID      pvQueryBuffer,
    IN  UINT_32    u4QueryBufferLen,
    OUT PUINT_32   pu4QueryInfoLen
    );

#if PTA_ENABLED
WLAN_STATUS
wlanoidSetBtCoexistCtrl (
    IN  P_ADAPTER_T  prAdapter,
    IN  PVOID    pvSetBuffer,
    IN  UINT_32  u4SetBufferLen,
    OUT PUINT_32 pu4SetInfoLen
    );
#endif


WLAN_STATUS
wlanoidSetAcpiDevicePowerState (
    IN P_ADAPTER_T prAdapter,
    IN  PVOID    pvSetBuffer,
    IN  UINT_32  u4SetBufferLen,
    OUT PUINT_32 pu4SetInfoLen
    );

WLAN_STATUS
wlanoidQueryAcpiDevicePowerState (
    IN P_ADAPTER_T prAdapter,
    IN  PVOID       pvQueryBuffer,
    IN  UINT_32     u4QueryBufferLen,
    OUT PUINT_32    pu4QueryInfoLen
    );

#if 0 /* SUPPORT_WPS */
WLAN_STATUS
wlanoidSetAppIE(
    IN P_ADAPTER_T        prAdapter,
    IN  PVOID             pvSetBuffer,
    IN  UINT_32           u4SetBufferLen,
    OUT PUINT_32          pu4SetInfoLen
    );

WLAN_STATUS
wlanoidSetFrameFilter(
    IN P_ADAPTER_T        prAdapter,
    IN  PVOID             pvSetBuffer,
    IN  UINT_32           u4SetBufferLen,
    OUT PUINT_32          pu4SetInfoLen
    );
#endif


WLAN_STATUS
wlanoidSetDisassociate (
    IN P_ADAPTER_T        prAdapter,
    IN  PVOID             pvSetBuffer,
    IN  UINT_32           u4SetBufferLen,
    OUT PUINT_32          pu4SetInfoLen
    );

WLAN_STATUS
wlanoidQueryFragThreshold (
    IN  P_ADAPTER_T prAdapter,
    OUT PVOID       pvQueryBuffer,
    IN  UINT_32     u4QueryBufferLen,
    OUT PUINT_32    pu4QueryInfoLen
    );

WLAN_STATUS
wlanoidSetFragThreshold (
    IN  P_ADAPTER_T prAdapter,
    IN  PVOID       pvSetBuffer,
    IN  UINT_32     u4SetBufferLen,
    OUT PUINT_32    pu4SetInfoLen
    );

WLAN_STATUS
wlanoidSetVoipConnectionStatus (
    IN P_ADAPTER_T  prAdapter,
    IN  PVOID    pvSetBuffer,
    IN  UINT_32  u4SetBufferLen,
    OUT PUINT_32 pu4SetInfoLen
    );

WLAN_STATUS
wlanoidQueryVoipConnectionStatus (
    IN P_ADAPTER_T  prAdapter,
    IN  PVOID    pvQueryBuf,
    IN  UINT_32  u4QueryBufLen,
    OUT PUINT_32 pu4QueryInfoLen
    );

WLAN_STATUS
wlanoidSetBgSsidParam (
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID             pvSetBuffer,
    IN  UINT_32           u4SetBufferLen,
    OUT PUINT_32          pu4SetInfoLen
    );

WLAN_STATUS
wlanoidAddTS (
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID             pvSetBuffer,
    IN  UINT_32           u4SetBufferLen,
    OUT PUINT_32          pu4SetInfoLen
    );

WLAN_STATUS
wlanoidDelTS (
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID             pvSetBuffer,
    IN  UINT_32           u4SetBufferLen,
    OUT PUINT_32          pu4SetInfoLen
    );

WLAN_STATUS
wlanoidQueryRoamingFunction (
    IN  P_ADAPTER_T prAdapter,
    OUT PVOID       pvQueryBuffer,
    IN  UINT_32     u4QueryBufferLen,
    OUT PUINT_32    pu4QueryInfoLen
    );

WLAN_STATUS
wlanoidSetRoamingFunction (
    IN  P_ADAPTER_T prAdapter,
    IN  PVOID       pvSetBuffer,
    IN  UINT_32     u4SetBufferLen,
    OUT PUINT_32    pu4SetInfoLen
    );

WLAN_STATUS
wlanoidSetWiFiWmmPsTest (
    IN  P_ADAPTER_T prAdapter,
    IN  PVOID       pvSetBuffer,
    IN  UINT_32     u4SetBufferLen,
    OUT PUINT_32    pu4SetInfoLen
    );

WLAN_STATUS
wlanoidQueryAdHocMode (
    IN  P_ADAPTER_T prAdapter,
    OUT PVOID       pvQueryBuffer,
    IN  UINT_32     u4QueryBufferLen,
    OUT PUINT_32    pu4QueryInfoLen
    );

WLAN_STATUS
wlanoidSetAdHocMode (
    IN  P_ADAPTER_T prAdapter,
    IN  PVOID       pvSetBuffer,
    IN  UINT_32     u4SetBufferLen,
    OUT PUINT_32    pu4SetInfoLen
    );

WLAN_STATUS
wlanoidQueryBeaconInterval (
    IN  P_ADAPTER_T prAdapter,
    OUT PVOID       pvQueryBuffer,
    IN  UINT_32     u4QueryBufferLen,
    OUT PUINT_32    pu4QueryInfoLen
    );

WLAN_STATUS
wlanoidSetBeaconInterval (
    IN  P_ADAPTER_T prAdapter,
    IN  PVOID       pvSetBuffer,
    IN  UINT_32     u4SetBufferLen,
    OUT PUINT_32    pu4SetInfoLen
    );

WLAN_STATUS
wlanoidSetCurrentAddr (
    IN  P_ADAPTER_T prAdapter,
    IN  PVOID       pvSetBuffer,
    IN  UINT_32     u4SetBufferLen,
    OUT PUINT_32    pu4SetInfoLen
    );

#if CFG_TCP_IP_CHKSUM_OFFLOAD
WLAN_STATUS
wlanoidSetCSUMOffload (
    IN  P_ADAPTER_T prAdapter,
    IN  PVOID       pvSetBuffer,
    IN  UINT_32     u4SetBufferLen,
    OUT PUINT_32    pu4SetInfoLen
);
#endif /* CFG_TCP_IP_CHKSUM_OFFLOAD */

#if CFG_LP_PATTERN_SEARCH_SLT
WLAN_STATUS
wlanoidQuerySltResult(
    IN P_ADAPTER_T  prAdapter,
    OUT  PVOID    pvQueryBuf,
    IN  UINT_32  u4QueryBufLen,
    OUT PUINT_32 pu4QueryInfoLen
    );


WLAN_STATUS
wlanoidSetSltMode(
    IN P_ADAPTER_T  prAdapter,
    IN  PVOID    pvSetBuffer,
    IN  UINT_32  u4SetBufferLen,
    OUT PUINT_32 pu4SetInfoLen
    );
#endif /* CFG_LP_PATTERN_SEARCH_SLT */

WLAN_STATUS
wlanoidSetIpAddress (
    IN  P_ADAPTER_T prAdapter,
    IN  PVOID       pvSetBuffer,
    IN  UINT_32     u4SetBufferLen,
    OUT PUINT_32    pu4SetInfoLen
    );

WLAN_STATUS
wlanoidQueryCurrentCountry (
    IN P_ADAPTER_T prAdapter,
    IN PVOID pvQueryBuffer,
    IN UINT_32 u4QueryBufferLen,
    OUT PUINT_32 pu4QueryInfoLen
    );

WLAN_STATUS
wlanoidSetCurrentCountry (
    IN P_ADAPTER_T prAdapter,
    IN PVOID pvSetBuffer,
    IN UINT_32 u4SetBufferLen,
    OUT PUINT_32 pu4SetInfoLen
    );

#if CFG_SUPPORT_802_11D
WLAN_STATUS
wlanoidQueryMultiDomainCap (
    IN  P_ADAPTER_T prAdapter,
    OUT PVOID       pvQueryBuffer,
    IN  UINT_32     u4QueryBufferLen,
    OUT PUINT_32    pu4QueryInfoLen
    );

WLAN_STATUS
wlanoidSetMultiDomainCap (
    IN  P_ADAPTER_T prAdapter,
    IN  PVOID       pvSetBuffer,
    IN  UINT_32     u4SetBufferLen,
    OUT PUINT_32    pu4SetInfoLen
    );
#endif

WLAN_STATUS
wlanoidSetGPIO2Mode (
    IN  P_ADAPTER_T  prAdapter,
    IN  PVOID    pvSetBuffer,
    IN  UINT_32  u4SetBufferLen,
    OUT PUINT_32 pu4SetInfoLen
    );

WLAN_STATUS
wlanoidSetContinuousPollProfile (
    IN  P_ADAPTER_T  prAdapter,
    IN  PVOID    pvSetBuffer,
    IN  UINT_32  u4SetBufferLen,
    OUT PUINT_32 pu4SetInfoLen
    );

WLAN_STATUS
wlanoidSetDisableBeaconDetectionFunc (
    IN  P_ADAPTER_T prAdapter,
    IN  PVOID       pvSetBuffer,
    IN  UINT_32     u4SetBufferLen,
    OUT PUINT_32    pu4SetInfoLen
    );

WLAN_STATUS
wlanoidQueryDisableBeaconDetectionFunc (
    IN  P_ADAPTER_T prAdapter,
    OUT PVOID       pvQueryBuffer,
    IN  UINT_32     u4QueryBufferLen,
    OUT PUINT_32    pu4QueryInfoLen
    );

#if defined(LINUX)
VOID
wlanoidQueryDrvStatusForLinuxProc (
    IN P_ADAPTER_T prAdapter,
    IN PUINT_8 pucBuffer,
    OUT PUINT_32 pu4Count
    );

VOID
wlanoidQueryRxStatisticsForLinuxProc (
    IN P_ADAPTER_T prAdapter,
    IN PUINT_8 pucBuffer,
    OUT PUINT_32 pu4Count
    );

VOID
wlanoidSetRxStatisticsForLinuxProc (
    IN P_ADAPTER_T prAdapter
    );

VOID
wlanoidQueryTxStatisticsForLinuxProc (
    IN P_ADAPTER_T prAdapter,
    IN PUINT_8 pucBuffer,
    OUT PUINT_32 pu4Count
    );

VOID
wlanoidSetTxStatisticsForLinuxProc (
    IN P_ADAPTER_T prAdapter
    );
#endif
#if PTA_ENABLED
WLAN_STATUS
wlanoidSetBT (
    IN  P_ADAPTER_T prAdapter,
    IN  PVOID       pvSetBuffer,
    IN  UINT_32     u4SetBufferLen,
    OUT PUINT_32    pu4SetInfoLen
    );


WLAN_STATUS
wlanoidQueryBT (
    IN  P_ADAPTER_T prAdapter,
    OUT PVOID       pvQueryBuffer,
    IN  UINT_32     u4QueryBufferLen,
    OUT PUINT_32    pu4QueryInfoLen
    );
WLAN_STATUS
wlanoidQueryBtSingleAntenna (
    IN  P_ADAPTER_T prAdapter,
    OUT PVOID       pvQueryBuffer,
    IN  UINT_32     u4QueryBufferLen,
    OUT PUINT_32    pu4QueryInfoLen
    );

WLAN_STATUS
wlanoidQueryPta (
    IN  P_ADAPTER_T prAdapter,
    OUT PVOID       pvQueryBuffer,
    IN  UINT_32     u4QueryBufferLen,
    OUT PUINT_32    pu4QueryInfoLen
    );

WLAN_STATUS
wlanoidSetBtSingleAntenna (
    IN  P_ADAPTER_T prAdapter,
    IN  PVOID       pvSetBuffer,
    IN  UINT_32     u4SetBufferLen,
    OUT PUINT_32    pu4SetInfoLen
    );

WLAN_STATUS
wlanoidSetPta (
    IN  P_ADAPTER_T prAdapter,
    IN  PVOID       pvSetBuffer,
    IN  UINT_32     u4SetBufferLen,
    OUT PUINT_32    pu4SetInfoLen
    );

WLAN_STATUS
wlanoidSetFixedRxGain (
    IN  P_ADAPTER_T prAdapter,
    IN  PVOID       pvSetBuffer,
    IN  UINT_32     u4SetBufferLen,
    OUT PUINT_32    pu4SetInfoLen
    );

WLAN_STATUS
wlanoidSetPta (
    IN  P_ADAPTER_T prAdapter,
    IN  PVOID       pvSetBuffer,
    IN  UINT_32     u4SetBufferLen,
    OUT PUINT_32    pu4SetInfoLen
    );
#endif

WLAN_STATUS
wlanoidSetDisablePriavcyCheck (
    IN  P_ADAPTER_T   prAdapter,
    IN  PVOID         pvSetBuffer,
    IN  UINT_32       u4SetBufferLen,
    OUT PUINT_32      pu4SetInfoLen
    );


WLAN_STATUS
wlanoidQueryContinuousPollInterval (
    IN  P_ADAPTER_T prAdapter,
    OUT PVOID       pvQueryBuffer,
    IN  UINT_32     u4QueryBufferLen,
    OUT PUINT_32    pu4QueryInfoLen
    );
#if CFG_SUPPORT_EXT_CONFIG

WLAN_STATUS
wlanoidQueryNvramRead (
    IN  P_ADAPTER_T       prAdapter,
    OUT PVOID             pvQueryBuffer,
    IN  UINT_32           u4QueryBufferLen,
    OUT PUINT_32          pu4QueryInfoLen
    );
WLAN_STATUS
wlanoidSetNvramWrite (
    IN P_ADAPTER_T  prAdapter,
    IN  PVOID       pvSetBuffer,
    IN  UINT_32     u4SetBufferLen,
    OUT PUINT_32    pu4SetInfoLen
    );
#endif   

WLAN_STATUS
wlanoidQueryCfgSrcType(
    IN  P_ADAPTER_T       prAdapter,
    OUT PVOID             pvQueryBuffer,
    IN  UINT_32           u4QueryBufferLen,
    OUT PUINT_32          pu4QueryInfoLen
  );    
  
WLAN_STATUS
wlanoidQueryEepromType(
    IN  P_ADAPTER_T       prAdapter,
    OUT PVOID             pvQueryBuffer,
    IN  UINT_32           u4QueryBufferLen,
    OUT PUINT_32          pu4QueryInfoLen
  );     
#if SUPPORT_WAPI
WLAN_STATUS
wlanoidSetWapiMode(
    IN  P_ADAPTER_T   prAdapter,
    IN  PVOID         pvSetBuffer,
    IN  UINT_32       u4SetBufferLen,
    OUT PUINT_32      pu4SetInfoLen
    );

WLAN_STATUS
wlanoidSetWapiAssocInfo(
    IN  P_ADAPTER_T   prAdapter,
    IN  PVOID         pvSetBuffer,
    IN  UINT_32       u4SetBufferLen,
    OUT PUINT_32      pu4SetInfoLen
    );
#endif

#if SUPPORT_WAPI
WLAN_STATUS
wlanoidSetWapiKey(
    IN  P_ADAPTER_T   prAdapter,
    IN  PVOID         pvSetBuffer,
    IN  UINT_32       u4SetBufferLen,
    OUT PUINT_32      pu4SetInfoLen
    );
#endif
#if PTA_NEW_BOARD_DESIGN
WLAN_STATUS
wlanoidSetPreferredAnt (
    IN  P_ADAPTER_T   prAdapter,
    IN  PVOID         pvSetBuffer,
    IN  UINT_32       u4SetBufferLen,
    OUT PUINT_32      pu4SetInfoLen
    );

WLAN_STATUS
wlanoidQueryPreferredAnt (
    IN  P_ADAPTER_T prAdapter,
    OUT PVOID       pvQueryBuffer,
    IN  UINT_32     u4QueryBufferLen,
    OUT PUINT_32    pu4QueryInfoLen
    );
#endif

WLAN_STATUS
wlanoidQueryWmmPsMode(
    IN  P_ADAPTER_T       prAdapter,
    OUT PVOID             pvQueryBuffer,
    IN  UINT_32           u4QueryBufferLen,
    OUT PUINT_32          pu4QueryInfoLen
    );

WLAN_STATUS
wlanoidSetWmmPsMode (
    IN P_ADAPTER_T  prAdapter,
    IN  PVOID       pvSetBuffer,
    IN  UINT_32     u4SetBufferLen,
    OUT PUINT_32    pu4SetInfoLen
    );

/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/

#endif /* _WLAN_OID_H */

