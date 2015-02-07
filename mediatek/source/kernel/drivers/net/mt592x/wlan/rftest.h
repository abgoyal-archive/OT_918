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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/rftest.h#1 $
*/

/*! \file   "rftest.h"
    \brief  -

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
** $Log: rftest.h $
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\7 2009-02-04 16:53:12 GMT mtk01725
**  update RF AT packet TX buffer size to RF_AT_PARAM_TX_PKTLEN_BYTE_MAX. (2048 + header length)
**  \main\maintrunk.MT5921\6 2008-11-21 23:11:24 GMT mtk01725
**  \main\maintrunk.MT5921\5 2008-09-22 10:47:22 GMT mtk01461
**  Fix compile warnning in MAUI
**  \main\maintrunk.MT5921\4 2008-08-25 23:07:33 GMT mtk01104
**  Modify some function prototypes.
**  \main\maintrunk.MT5921\3 2008-04-10 23:43:46 GMT mtk01385
**  1.add update BB/RF Rx setting based on thermo info function.
**  \main\maintrunk.MT5921\2 2007-12-26 14:09:53 GMT mtk01385
**  1. Fix rftest mode display rx packet count issue..
**
**  \main\maintrunk.MT5921\1 2007-11-19 10:10:51 GMT mtk01385
**  init version.
**
*/
#ifndef _RFTEST_H
#define _RFTEST_H

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
#define MTK_CUSTOM_OID_INTERFACE_VERSION     0x00005921    // for WPDWifi DLL
#define RF_AUTO_TEST_FUNCTION_TABLE_VERSION  0x01000000

#define RF_AT_PARAM_TX_80211HDR_BYTE_MAX     32
#define RF_AT_PARAM_TX_80211HDR_BYTE_DEFAULT 24

#define RF_AT_PARAM_TX_80211PAYLOAD_BYTE_MAX (2048) //can not >= this length

#define RF_AT_PARAM_POWER_MASK      BITS(0,7)
#define RF_AT_PARAM_POWER_MAX       RF_AT_PARAM_POWER_MASK
#define RF_AT_PARAM_RATE_MCS_MASK   BIT(31)
#define RF_AT_PARAM_RATE_MASK       BITS(0,7)
#define RF_AT_PARAM_RATE_CCK_MAX    3
#define RF_AT_PARAM_RATE_1M         0
#define RF_AT_PARAM_RATE_2M         1
#define RF_AT_PARAM_RATE_5_5M       2
#define RF_AT_PARAM_RATE_11M        3
#define RF_AT_PARAM_RATE_6M         4
#define RF_AT_PARAM_RATE_9M         5
#define RF_AT_PARAM_RATE_12M        6
#define RF_AT_PARAM_RATE_18M        7
#define RF_AT_PARAM_RATE_24M        8
#define RF_AT_PARAM_RATE_36M        9
#define RF_AT_PARAM_RATE_48M        10
#define RF_AT_PARAM_RATE_54M        11

#define RF_AT_PARAM_TXOPQUE_QMASK   BITS(16,31)
#define RF_AT_PARAM_TXOPQUE_TMASK   BITS(0,15)
#define RF_AT_PARAM_TXOPQUE_AC0     (0<<16)
#define RF_AT_PARAM_TXOPQUE_AC1     (1<<16)
#define RF_AT_PARAM_TXOPQUE_AC2     (2<<16)
#define RF_AT_PARAM_TXOPQUE_AC3     (3<<16)
#define RF_AT_PARAM_TXOPQUE_QOFFSET 16



#define RF_AT_PARAM_ANTENNA_ID_MAX  1

#define RF_AT_PARAM_PACKET_UNLIMITED  0

#define RF_AT_PARAM_TX_PKTLEN_BYTE_DEFAULT  1024
#define RF_AT_PARAM_TX_PKTLEN_BYTE_MAX  \
    ((UINT_16)(RF_AT_PARAM_TX_80211HDR_BYTE_DEFAULT +RF_AT_PARAM_TX_80211PAYLOAD_BYTE_MAX ))
#define RF_AT_PARAM_TX_DATA_STRUCT_MAX  \
                ((UINT_16)(RF_AT_PARAM_TX_PKTLEN_BYTE_MAX+ (TFCB_SIZE)))

#define RF_AT_PARAM_TX_PKTCNT_DEFAULT       1000
#define RF_AT_PARAM_TX_PKT_INTERVAL_US_DEFAULT  50


#define RF_AT_PARAM_TX_RETRY_MAX    6

#define RF_AT_TX_BUFFER_SIZE        (RF_AT_PARAM_TX_DATA_STRUCT_MAX + sizeof(QUE_ENTRY_T)) //4K+12 = 4060+32+12+4
#define RF_AT_TX_BUFFER_NUM_MAX     CFG_MAX_NUM_MSDU_INFO_FOR_TC0

/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/
typedef enum _ENUM_RF_AT_COMMAND_T {
    RF_AT_COMMAND_STOPTEST = 0,
    RF_AT_COMMAND_STARTTX,
    RF_AT_COMMAND_STARTRX,
    RF_AT_COMMAND_RESET,
    RF_AT_COMMAND_NUM
} ENUM_RF_AT_COMMAND_T;


typedef enum _ENUM_RF_AT_FUNCID_T {
    RF_AT_FUNCID_VERSION = 0,
    RF_AT_FUNCID_COMMAND,
    RF_AT_FUNCID_POWER,
    RF_AT_FUNCID_RATE,
    RF_AT_FUNCID_PREAMBLE,
    RF_AT_FUNCID_ANTENNA,
    RF_AT_FUNCID_PKTLEN,
    RF_AT_FUNCID_PKTCNT,
    RF_AT_FUNCID_PKTINTERVAL,
    RF_AT_FUNCID_ALC,
    RF_AT_FUNCID_TXOPLIMIT,
    RF_AT_FUNCID_ACKPOLICY,
    RF_AT_FUNCID_PKTCONTENT,
    RF_AT_FUNCID_RETRYLIMIT,
    RF_AT_FUNCID_QUEUE,
    RF_AT_FUNCID_BANDWIDTH,
    RF_AT_FUNCID_GI,
    RF_AT_FUNCID_STBC,
    RF_AT_FUNCID_IO_PIN_TEST,
    RF_AT_FUNCID_NUM
} ENUM_RF_AT_FUNCID_T;

typedef enum _ENUM_RF_AT_PREAMBLE_T {
    RF_AT_PREAMBLE_NORMAL = 0,
    RF_AT_PREAMBLE_CCK_SHORT,
    RF_AT_PREAMBLE_11N_MM,
    RF_AT_PREAMBLE_11N_GF,
    RF_AT_PREAMBLE_NUM
} ENUM_RF_AT_PREAMBLE_T;

typedef enum _ENUM_RF_AT_ACK_POLICY_T {
    RF_AT_ACK_POLICY_NORMAL = 0,
    RF_AT_ACK_POLICY_NOACK,
    RF_AT_ACK_POLICY_NOEXPLICTACK,
    RF_AT_ACK_POLICY_BLOCKACK,
    RF_AT_ACK_POLICY_NUM
} ENUM_RF_AT_ACK_POLICY_T;

typedef enum _ENUM_RF_AUTOTEST_STATE_T {
    RF_AUTOTEST_STATE_STANDBY = 0,
    RF_AUTOTEST_STATE_TX,
    RF_AUTOTEST_STATE_RX,
    RF_AUTOTEST_STATE_RESET,
    RF_AUTOTEST_STATE_NUM
} ENUM_RF_AUTOTEST_STATE_T;


typedef struct _RFTEST_SETTING_STRUC_T {
    UINT_8                  ucTxPowerGain;
    UINT_8                  ucAntenna;
    UINT_8                  ucRetryLimit;
    UINT_8                  ucTxQue;
    UINT_8                  ucTxRate;
    BOOLEAN                 fgALCEn;
    ENUM_RF_AT_PREAMBLE_T   ePreamble;
    ENUM_RF_AT_ACK_POLICY_T eAckPolicy;
    UINT_32                 u4PacketLen;
    UINT_32                 u4PacketCnt;
    UINT_32                 u4PacketIntervalUs;
    UINT_32                 u4QueTxop;
    UINT_8                  aucPktContent[RF_AT_PARAM_TX_PKTLEN_BYTE_MAX];
} RFTEST_SETTING_STRUC_T, *P_RFTEST_SETTING_STRUC_T;

typedef struct _RFTEST_STATUS_STRUC_T {
    UINT_32                 u4TxedPacketCnt; /* Packet send to s/w queue */
    UINT_32                 u4TxDoneCnt;     /* TxDone Comeback number */
    UINT_32                 u4DSConfig;      /* Channel frequency in unit of kHz */
    UINT_64                 u8RxedPacketCnt; /* RxDone Comeback number */

} RFTEST_STATUS_STRUC_T, *P_RFTEST_STATUS_STRUC_T;


typedef struct _RFTEST_INFO_T {
    ENUM_RF_AUTOTEST_STATE_T    eCurrentState;
    RFTEST_SETTING_STRUC_T      rSetting;
    RFTEST_STATUS_STRUC_T       rStatus;

    /* TX */
    UINT_32                     u4TxCachedSize;
    PUINT_8                     pucTxCached;     /* Memory handler */

    QUE_T                       rTxBufFreeQueue; /* Packet Queue */

    /* RX */
} RFTEST_INFO_T, *P_RFTEST_INFO_T;


typedef struct _RFTEST_TXBUF_T {
    QUE_ENTRY_T     rQueEntry;
    UINT_8          aucData[1];
} RFTEST_TXBUF_T, *P_RFTEST_TXBUF_T;


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

/* The macro to set the txpower gain to OFPR or CFPR. */
#define RFTEST_SET_TX_POWER_GAIN(_pAdapter, _register, _txGain, _setMask, _setOffset) \
            RFTEST_SET_SUBFIELD_WITH_VALUE(_pAdapter, _register, _txGain, _setMask, _setOffset)

/* The macro to set the Tx count limit to MTCLR. */
#define RFTEST_SET_TX_CNT_LIMIT(_pAdapter, _register, _limit, _setMask, _setOffset) \
                RFTEST_SET_SUBFIELD_WITH_VALUE(_pAdapter, _register, _limit, _setMask, _setOffset)

/* The macro to set the TXOP limit to ACTXOPLR0~1. */
#define RFTEST_SET_TXOP_LIMIT(_pAdapter, _register, _txopLimit, _setMask, _setOffset) \
                RFTEST_SET_SUBFIELD_WITH_VALUE(_pAdapter, _register, _txopLimit, _setMask, _setOffset)


/* The macro to set the sub filed value to specific MCR. */
#define RFTEST_SET_SUBFIELD_WITH_VALUE(_pAdapter, _register, _value, _fieldMask, _fieldOffset) \
        { \
            UINT_32 u4MCR; \
            HAL_MCR_RD((_pAdapter), (_register), (&u4MCR)); \
            u4MCR = (u4MCR & ~ (_fieldMask)) | (((_value)<< (_fieldOffset)) &(_fieldMask) ); \
            HAL_MCR_WR((_pAdapter), (_register), (u4MCR));\
        }

#define RFTEST_BUFENT_GET_BUFFER(_prBufEntry)  \
        (((P_RFTEST_TXBUF_T)(_prBufEntry))->aucData)


/*******************************************************************************
*                   F U N C T I O N   D E C L A R A T I O N S
********************************************************************************
*/
/***** Routines in rftest.c *****/

WLAN_STATUS
rftestInit (
    IN P_ADAPTER_T prAdapter
    );

WLAN_STATUS
rftestTxModeInit (
    IN P_ADAPTER_T prAdapter
    );

VOID
rftestTx (
    IN P_ADAPTER_T prAdapter
    );

VOID
rftestBufFreeRFTestBuf (
    IN P_ADAPTER_T      prAdapter,
    IN P_RFTEST_TXBUF_T prTxBufEntry
    );

WLAN_STATUS
rftestSet80211Configuration (
    IN P_ADAPTER_T prAdapter,
    IN P_PARAM_802_11_CONFIG_T prNewConfig
    );


WLAN_STATUS
rftestQuery80211Configuration (
    IN P_ADAPTER_T prAdapter,
    IN P_PARAM_802_11_CONFIG_T prQueryConfig
    );

WLAN_STATUS
rftestUnInit (
    IN P_ADAPTER_T prAdapter
    );

VOID
rftestTxStopTx (
    IN P_ADAPTER_T prAdapter
    );

VOID
rftestSetSWDefaultValue (
    IN P_ADAPTER_T prAdapter
    );

VOID
rftestUpdateRxConfigToHw (
    IN P_ADAPTER_T prAdapter
    );

WLAN_STATUS
rftestRxModeInit (
    IN P_ADAPTER_T prAdapter
    );

VOID
rftestRxStopRx (
    IN P_ADAPTER_T prAdapter
    );

VOID
rftestProcessRxMPDU (
    IN P_ADAPTER_T prAdapter,
    IN OUT PP_SW_RFB_T pprSWRfb
    );

VOID
rftestRxCheckHwConfig (
    IN P_ADAPTER_T prAdapter
    );

VOID
rftestAdoptBbRfByThermo (
    IN P_ADAPTER_T prAdapter
    );

#endif /* _RFTEST_H */



