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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/wlan_lib.h#2 $
*/

/*! \file   "wlan_lib.h"
    \brief  The declaration of the functions of the wlanAdpater objects

    Detail description.
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
** $Log: wlan_lib.h $
 *
 * 09 03 2010 enlai.chu
 * [ALPS00003550] [YuSu]WAPI feature
 * For WAPI feature
 *
 * 07 10 2010 renbang.jiang
 * [ALPS00121785][Need Patch] [Volunteer Patch] use NVRAM to save Wi-Fi custom data 
 * .
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\46 2009-09-22 22:52:00 GMT mtk01089
**  Use PTA_NEW_BOARD_DESIGN to seperate 1.26 code
**  \main\maintrunk.MT5921\45 2009-09-18 19:48:38 GMT mtk01089
**  Add a new registry. Original BTSingleAnt is left for MT6611 driver  to read only. board design is updated by BoardSingleAnt
**  \main\maintrunk.MT5921\44 2009-09-12 13:45:33 GMT mtk01089
**  BWCS needs two sets of PTA settings.
**  \main\maintrunk.MT5921\43 2009-09-09 11:28:49 GMT mtk01089
**  \main\maintrunk.MT5921\42 2009-09-03 11:34:55 GMT mtk01088
**  adding the wapi function declaration
**  \main\maintrunk.MT5921\41 2009-07-06 20:29:26 GMT mtk01088
**  adding variable and function declaration for wapi
**  \main\maintrunk.MT5921\40 2009-04-28 22:59:31 GMT mtk01104
**  Add registry of u4InitDelayInd
**  \main\maintrunk.MT5921\39 2009-03-20 11:43:35 GMT mtk01461
**  Add variable for VI AIFSN/TXOP testing registry
**  \main\maintrunk.MT5921\38 2009-02-17 17:32:30 GMT mtk01084
**  add new registry for configuring polling interval when there's no WiFi traffic
**  \main\maintrunk.MT5921\37 2009-01-07 17:38:12 GMT mtk01425
**  1. Add new variables for registry
**  \main\maintrunk.MT5921\36 2008-11-24 21:05:11 GMT mtk01425
**  1. Add PTA_ENABLED flag
**  \main\maintrunk.MT5921\35 2008-10-31 13:57:49 GMT mtk01425
**  1. Add u4SingleAntenna and u4BtProfile to the type REG_INFO_T
**  \main\maintrunk.MT5921\34 2008-10-27 14:24:37 GMT mtk01084
**  supporting continuous polling mode
**  \main\maintrunk.MT5921\33 2008-09-10 15:02:29 GMT mtk01088
**  use card eject function instead the hw error check function
**  \main\maintrunk.MT5921\32 2008-08-11 15:12:05 GMT mtk01084
**  prevent compiler error on array size define
**  \main\maintrunk.MT5921\31 2008-08-11 14:07:53 GMT mtk01084
**  modify driver to meeting coding rules
**  \main\maintrunk.MT5921\30 2008-08-01 18:05:26 GMT mtk01088
**  add function to test hw error and released tx queue while hw error
**  \main\maintrunk.MT5921\29 2008-07-16 15:27:59 GMT mtk01104
**  Add member "u4GPIO2_Mode" in REG_INFO_T
**  \main\maintrunk.MT5921\28 2008-07-10 16:37:24 GMT mtk01084
**  support 802.11d related functions
**  \main\maintrunk.MT5921\27 2008-06-19 10:13:15 GMT mtk01084
**  support registry for more detail about PTA settings
**  \main\maintrunk.MT5921\26 2008-06-10 22:56:03 GMT mtk01084
**  add country related variable
**  \main\maintrunk.MT5921\25 2008-06-10 10:04:52 GMT mtk01084
**  add members in reg_info_t
**  \main\maintrunk.MT5921\24 2008-06-05 15:37:05 GMT mtk01104
**  Unify name to u4BtCR0 from u4BTCER0 in REG_INFO_T
**  \main\maintrunk.MT5921\23 2008-06-01 17:33:29 GMT mtk01084
**  remove un-used function
**  \main\maintrunk.MT5921\22 2008-05-30 18:46:31 GMT mtk01461
**  Update REG_INFO_T for RoamingEn
**  \main\maintrunk.MT5921\21 2008-05-29 14:14:20 GMT mtk01084
**  modify wlanAdapterStart() interface
**  \main\maintrunk.MT5921\20 2008-05-23 10:01:22 GMT mtk01084
**  modify wlanISR interface for preventing queued ISR to be processed after entered D3
**  \main\maintrunk.MT5921\19 2008-04-24 22:46:43 GMT mtk01461
**  Remove function declaration of wlanRxMulticast related functions
**  \main\maintrunk.MT5921\18 2008-03-20 11:42:52 GMT mtk01084
**  modify set IP address function arguments
**  \main\maintrunk.MT5921\17 2007-11-30 16:41:17 GMT mtk01425
**  1. Add wlanRxSetBroadcast
**  \main\maintrunk.MT5921\16 2007-11-22 19:04:46 GMT mtk01425
**  1. Add wlanSetCSUMOffload
**  \main\maintrunk.MT5921\15 2007-11-02 00:50:50 GMT mtk01461
**  Unify TX Path for Normal and IBSS Power Save + IBSS neighbor learning
**  \main\maintrunk.MT5921\14 2007-10-30 11:56:08 GMT MTK01425
**  1. Add MAX_NUM_GROUP_ADDR
**  \main\maintrunk.MT5921\13 2007-10-30 10:01:13 GMT mtk01425
**  1. Add declaration of MAX_NUM_GROUP_ADDR
**  2. Add declaration of wlanRxSetMulticastList, wlanRxNoMulticast, wlanRxAllMulticast and wlanSetPromiscuousMode
**  \main\maintrunk.MT5921\12 2007-10-29 22:23:43 GMT mtk01084
**  modify wlanSetInformation/ wlanQueryInformation interface
**  \main\maintrunk.MT5921\11 2007-10-25 17:55:40 GMT mtk01461
**  Remove old IBSS Power Save Support Flag
** Revision 1.7  2007/07/09 06:35:25  MTK01088
** delete non-used define
**
** Revision 1.6  2007/07/05 07:25:31  MTK01461
** Add Linux initial code, modify doc, add 11BB, RF init code
**
** Revision 1.5  2007/06/28 13:10:57  MTK01088
** remove non-define function
**
** Revision 1.4  2007/06/27 12:43:22  MTK01088
** add function declaration for privacy.c
**
** Revision 1.3  2007/06/27 06:24:46  MTK01088
** add the sec related structure define
**
** Revision 1.2  2007/06/27 02:18:49  MTK01461
** Update SCAN_FSM, Initial(Can Load Module), Proc(Can do Reg R/W), TX API
**
*/
#ifndef _WLAN_LIB_H
#define _WLAN_LIB_H
#include "../platform.h"
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

#define MAX_NUM_GROUP_ADDR                      32      /* max number of group addresses */



#define TX_CS_TCP_UDP_GEN        BIT(1)
#define TX_CS_IP_GEN             BIT(0)
#if SUPPORT_WAPI
#define TX_WPI_OPEN              BIT(6) /* At WAPI, send data frame as 802.11 format and no encrypt */
#define TX_WPI_ENCRYPT           BIT(7)
#endif

#define CSUM_OFFLOAD_EN_TX_TCP      BIT(0)
#define CSUM_OFFLOAD_EN_TX_UDP      BIT(1)
#define CSUM_OFFLOAD_EN_TX_IP       BIT(2)
#define CSUM_OFFLOAD_EN_RX_TCP      BIT(3)
#define CSUM_OFFLOAD_EN_RX_UDP      BIT(4)
#define CSUM_OFFLOAD_EN_RX_IPv4     BIT(5)
#define CSUM_OFFLOAD_EN_RX_IPv6     BIT(6)
#define CSUM_OFFLOAD_EN_TX_MASK     BITS(0,2)
#define CSUM_OFFLOAD_EN_ALL         BITS(0,6)

/* TCP, UDP, IP Checksum */
#define RX_CS_TYPE_UDP           BIT(7)
#define RX_CS_TYPE_TCP           BIT(6)
#define RX_CS_TYPE_IPv6          BIT(5)
#define RX_CS_TYPE_IPv4          BIT(4)

#define RX_CS_STATUS_UDP         BIT(3)
#define RX_CS_STATUS_TCP         BIT(2)
#define RX_CS_STATUS_IP          BIT(0)

#define CSUM_NOT_SUPPORTED      0x0
/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/
typedef WLAN_STATUS (*PFN_OID_HANDLER_FUNC) (
    IN  P_ADAPTER_T prAdapter,
    IN  PVOID       pvBuf,
    IN  UINT_32     u4BufLen,
    OUT PUINT_32    pu4OutInfoLen
    );

typedef enum _ENUM_CSUM_TYPE_T {
    CSUM_TYPE_IPV4,
    CSUM_TYPE_IPV6,
    CSUM_TYPE_TCP,
    CSUM_TYPE_UDP,
    CSUM_TYPE_NUM
} ENUM_CSUM_TYPE_T, *P_ENUM_CSUM_TYPE_T;

typedef enum _ENUM_CSUM_RESULT_T {
    CSUM_RES_NONE,
    CSUM_RES_SUCCESS,
    CSUM_RES_FAILED,
    CSUM_RES_NUM
} ENUM_CSUM_RESULT_T, *P_ENUM_CSUM_RESULT_T;

#if 0
/* For storing driver initialization value from glue layer */
typedef struct _REG_INFO_T {
    UINT_32     u4SdBlockSize;      /* SDIO block size */
    UINT_32     u4SdBusWidth;       /* SDIO bus width. 1 or 4 */
    UINT_32     u4SdClockRate;      /* SDIO clock rate. (in unit of HZ) */
#if PTA_ENABLED
    UINT_32     u4BTCoexistWindowType; /*  */
    UINT_32     u4EnableTxAutoFragmentForBT; /*  */
    UINT_32     u4BtCR0;            /* BTCR0 value (correcspondent to register setting) */
    UINT_32     u4BtCR1;            /* BTCR1 value (correcspondent to register setting) */
    UINT_32     u4BtCR2;            /* BTCR2 value (correcspondent to register setting) */
    UINT_32     u4BtCR3;            /* BTCR3 value (correcspondent to register setting) */
#if PTA_NEW_BOARD_DESIGN
    UINT_32     u4SingleAclBtCR0;            /* BTCR0 value (correcspondent to register setting) */
    UINT_32     u4SingleAclBtCR1;            /* BTCR1 value (correcspondent to register setting) */
    UINT_32     u4SingleAclBtCR2;            /* BTCR2 value (correcspondent to register setting) */
    UINT_32     u4SingleAclBtCR3;            /* BTCR3 value (correcspondent to register setting) */

    UINT_32     u4SingleMixBtCR0;            /* BTCR0 value (correcspondent to register setting) */
    UINT_32     u4SingleMixBtCR1;            /* BTCR1 value (correcspondent to register setting) */
    UINT_32     u4SingleMixBtCR2;            /* BTCR2 value (correcspondent to register setting) */
    UINT_32     u4SingleMixBtCR3;            /* BTCR3 value (correcspondent to register setting) */

    UINT_32     u4DualAclBtCR0;            /* BTCR0 value (correcspondent to register setting) */
    UINT_32     u4DualAclBtCR1;            /* BTCR1 value (correcspondent to register setting) */
    UINT_32     u4DualAclBtCR2;            /* BTCR2 value (correcspondent to register setting) */
    UINT_32     u4DualAclBtCR3;            /* BTCR3 value (correcspondent to register setting) */

    UINT_32     u4DualMixBtCR0;            /* BTCR0 value (correcspondent to register setting) */
    UINT_32     u4DualMixBtCR1;            /* BTCR1 value (correcspondent to register setting) */
    UINT_32     u4DualMixBtCR2;            /* BTCR2 value (correcspondent to register setting) */
    UINT_32     u4DualMixBtCR3;            /* BTCR3 value (correcspondent to register setting) */

    UINT_32     u4BTSetting;        /* useless for BT only */
#else
    UINT_32     u4ScoBtCR0;            /* BTCR0 value (correcspondent to register setting) */
    UINT_32     u4ScoBtCR1;            /* BTCR1 value (correcspondent to register setting) */
    UINT_32     u4ScoBtCR2;            /* BTCR2 value (correcspondent to register setting) */
    UINT_32     u4ScoBtCR3;            /* BTCR3 value (correcspondent to register setting) */
    
    UINT_32     u4AclBtCR0;            /* BTCR0 value (correcspondent to register setting) */
    UINT_32     u4AclBtCR1;            /* BTCR1 value (correcspondent to register setting) */
    UINT_32     u4AclBtCR2;            /* BTCR2 value (correcspondent to register setting) */
    UINT_32     u4AclBtCR3;            /* BTCR3 value (correcspondent to register setting) */
    
    UINT_32     u4MixBtCR0;            /* BTCR0 value (correcspondent to register setting) */
    UINT_32     u4MixBtCR1;            /* BTCR1 value (correcspondent to register setting) */
    UINT_32     u4MixBtCR2;            /* BTCR2 value (correcspondent to register setting) */
    UINT_32     u4MixBtCR3;            /* BTCR3 value (correcspondent to register setting) */
#endif
    UINT_32     u4SingleAntenna;    /* 0: Not single antenna, 1: Single antenna */
    UINT_32     u4BtProfile;        /* 0: No PTA, 1: SCO, 2: A2DP(ACL), 3: See btcr0-3 */
    UINT_32     u4PtaEnabled;
#endif
    UINT_8      aucMacAddr[6];      /* MAC address */
    UINT_16     aucCountryCode[4];  /* Country code (in ISO 3166-1 expression, ex: "US", "TW")  */
    UINT_32     u4UapsdAc;          /* UAPSD AC (in bitwise OR of: a. 0x11-AC0, b. 0x22-AC1, a. 0x44-AC0, a. 0x88-AC0) */
    UINT_32     u4PowerMode;        /* Power mode (0: CAM, 1: MAX, 2: FAST) */
    UINT_32     u4AtimWindow;       /* ATIM Window value (in unit of TU) */
    UINT_32     u4VoipInterval;     /* VoIP interval (in unit of ms) */
    UINT_32     u4PollInterval;     /* Poll interval (in unit of ms) */
    UINT_32     u4PollIntervalB;    /* Poll interval, if Wi-Fi no traffic (in unit of ms) */
    UINT_32     u4L3PktFilterEn;    /* Enable pattern search for broadcast ARP filter */
    UINT_32     u4AdHocMode;        /* Adhoc mode */
    UINT_32     u4RoamingEn;        /* Enable Roaming function */
    UINT_32     u4LedBlinkMode;     /* LED blink mode (0: disable) */
#if CFG_SUPPORT_802_11D
    UINT_32     u4MultiDomainCap;   /* Multi-domain capability */
#endif
    UINT_32     u4GPIO2_Mode;       /* GPIO2 mode (0: GPI, 1: INT, 2: Daisy) */

    UINT_32     u4ViAifsnBias;      /* Define VI AIFSN BIAS (Default: 0, 0~15) */
                                        /* Actual AIFSN = AIFSN from AP + AIFSN Bias */
    UINT_32     u4ViMaxTxopLimit;   /* Define VI MAX TXOP LIMIT(A upper bound) (Default: 0xFFFF, 0~0xFFFF) */

    UINT_32     u4InitDelayInd;     /* Define how many MS to indicate DISCONNECTION after initialized */

#if SUPPORT_WAPI
    UINT_32     u4UseWapi;          /* Define use at wapi mode, control by wapi ui (Default: 0 disable, 1~0xFFFFFFFF: enable) */
#endif

} REG_INFO_T, *P_REG_INFO_T;
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
P_ADAPTER_T
wlanAdapterCreate (
    IN P_GLUE_INFO_T prGlueInfo
    );

VOID
wlanAdapterDestroy (
    IN P_ADAPTER_T prAdapter
    );

VOID
wlanCardEjected(
    IN P_ADAPTER_T         prAdapter
    );

WLAN_STATUS
wlanSendPacket (
    IN P_ADAPTER_T          prAdapter,
    IN P_PACKET_INFO_T      prPacketInfo
    );

VOID
wlanIST (
    IN P_ADAPTER_T prAdapter
    );

BOOL
wlanISR (
    IN P_ADAPTER_T prAdapter,
    IN BOOLEAN fgGlobalIntrCtrl
    );

VOID
wlanReturnPacket (
    IN P_ADAPTER_T prAdapter,
    IN PVOID pvPacket
    );

WLAN_STATUS
wlanQueryInformation (
    IN P_ADAPTER_T          prAdapter,
    IN PFN_OID_HANDLER_FUNC pfOidQryHandler,
    IN PVOID                pvInfoBuf,
    IN UINT_32              u4InfoBufLen,
    OUT PUINT_32            pu4QryInfoLen
    );

WLAN_STATUS
wlanSetInformation (
    IN P_ADAPTER_T          prAdapter,
    IN PFN_OID_HANDLER_FUNC pfOidSetHandler,
    IN PVOID                pvInfoBuf,
    IN UINT_32              u4InfoBufLen,
    OUT PUINT_32            pu4SetInfoLen
    );

VOID
wlanoidSetTxStatistics (
    IN P_ADAPTER_T prAdapter
    );


VOID
wlanDoTimeOutCheck (
    IN P_ADAPTER_T  prAdapter
    );


WLAN_STATUS
wlanAdapterStart (
    IN P_ADAPTER_T  prAdapter,
    IN P_REG_INFO_T prRegInfo
    );

WLAN_STATUS
wlanAdapterStop (
    IN P_ADAPTER_T prAdapter
    );

VOID
wlanReturnRxPacket (
    IN PVOID pvAdapter,
    IN PVOID pvPacket
    );

VOID
wlanSetPromiscuousMode (
    IN P_ADAPTER_T  prAdapter,
    IN BOOLEAN      fgEnablePromiscuousMode
    );

VOID
wlanRxSetBroadcast (
    IN P_ADAPTER_T  prAdapter,
    IN BOOLEAN      fgEnableBroadcast
    );

#if SUPPORT_WAPI
VOID
wlanSetWapiMode(
    IN P_ADAPTER_T          prAdapter,
    IN UINT_32              u4UseWapi
    );

BOOLEAN
wlanQueryWapiMode(
    IN P_ADAPTER_T          prAdapter
    );
#if 0
WLAN_STATUS
wlanoidQueryWapiCap (
    IN  P_ADAPTER_T prAdapter,
    OUT PVOID       pvQueryBuffer,
    IN  UINT_32     u4QueryBufferLen,
    OUT PUINT_32    pu4QueryInfoLen
    );
#endif
#endif

#endif /* _WLAN_LIB_H */

