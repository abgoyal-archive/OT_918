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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/nic_rx.h#1 $
*/

/*! \file   "nic_rx.h"
    \brief  The declaration of the nic rx functions

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
** $Log: nic_rx.h $
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\30 2008-09-05 17:24:52 GMT mtk01461
**  Update Driver for Code Review
**  \main\maintrunk.MT5921\29 2008-08-29 19:12:42 GMT mtk01104
**  Remove not used conditional compiler flag
**  \main\maintrunk.MT5921\28 2008-08-21 00:21:26 GMT mtk01461
**  Update for Driver Review
**  \main\maintrunk.MT5921\27 2008-08-05 01:52:24 GMT mtk01461
**  Add RX counter to support linux statistics
**  \main\maintrunk.MT5921\26 2008-06-12 20:29:18 GMT mtk01461
**  Remove unused compile flag of SCAN module which is work around for MPW. Add CFG_TX_DBG_SEQ_NUM compile flag.
**
**  \main\maintrunk.MT5921\25 2008-04-24 12:03:58 GMT mtk01461
**  Rename the MC_TYPE enum
**  \main\maintrunk.MT5921\24 2008-04-11 17:16:21 GMT mtk01461
**  Fix EAPOL packet retry due to RX queue off/on
**  \main\maintrunk.MT5921\23 2008-03-31 09:51:09 GMT mtk01461
**  Remove useless variable
**  \main\maintrunk.MT5921\22 2008-03-19 15:21:50 GMT mtk01461
**  Add fgIsDefragQueNonEmpty to RX_CTRL_T
**  \main\maintrunk.MT5921\21 2008-01-07 15:06:02 GMT mtk01461
**  Add SDIO Enhance Support
**  Add PhyType & AdHocMode Selection Support
**  \main\maintrunk.MT5921\20 2007-11-30 16:39:05 GMT mtk01425
**  1. Add nicRxSetBroadcast
**  \main\maintrunk.MT5921\19 2007-11-30 16:34:27 GMT mtk01425
**  1. Add fgEnablePromiscuousMode
**  \main\maintrunk.MT5921\18 2007-11-26 21:24:29 GMT mtk01385
**  1. add RX BB related counters.
**  2. Change counter from 32 bits to 64 bits.
**  \main\maintrunk.MT5921\17 2007-11-26 19:30:32 GMT mtk01461
**  Unify SCAN
**
**  \main\maintrunk.MT5921\16 2007-11-19 10:17:09 GMT mtk01385
**  1. add rx cck short/long preamble counters.
**  \main\maintrunk.MT5921\15 2007-11-17 15:22:01 GMT mtk01385
**  1. add Rf test mode flag to Rx control.
**  2. add G0, G1, G2 flag to Rx control.
**  \main\maintrunk.MT5921\14 2007-11-05 16:58:35 GMT mtk01425
**  1. Add nicRxUninitialize declaration
**  \main\maintrunk.MT5921\13 2007-11-02 00:52:56 GMT mtk01461
**  Unify TX Path for Normal and IBSS Power Save + IBSS neighbor learning
**  \main\maintrunk.MT5921\12 2007-10-30 09:52:57 GMT mtk01425
**  1. Add ENUM_RX_MULTICAST_TYPE_T type
**  2. Add fgRxMulticastPkt and fgRxMulticastPktByTable to Rx ctrl variable
**  2. Add declaration of nicRxEnablePromiscuousMode, nicRxDisablePromiscuousMode and nicRxSetMulticast
**  \main\maintrunk.MT5921\11 2007-10-25 18:00:43 GMT mtk01461
**  Add VOIP SCAN Support  & Refine Roaming
** Revision 1.3  2007/07/05 07:25:31  MTK01461
** Add Linux initial code, modify doc, add 11BB, RF init code
**
** Revision 1.2  2007/06/27 02:18:49  MTK01461
** Update SCAN_FSM, Initial(Can Load Module), Proc(Can do Reg R/W), TX API
**
*/
#ifndef _NIC_RX_H
#define _NIC_RX_H

/*******************************************************************************
*                         C O M P I L E R   F L A G S
********************************************************************************
*/

/*******************************************************************************
*                    E X T E R N A L   R E F E R E N C E S
********************************************************************************
*/
extern RX_FILTER_MAP_T arRxFilterMapTable[];

/*******************************************************************************
*                              C O N S T A N T S
********************************************************************************
*/

/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/
typedef enum _ENUM_RX_STATISTIC_COUNTER_T {
    RX_MPDU_TOTAL_COUNT = 0,                /* TOTAL = MGMT + DATA + CTRL */
    RX_DATA_FRAME_COUNT,                    /* DATA = BMCAST_DATA + UCAST_DATA */
    RX_UCAST_DATA_FRAME_COUNT,
    RX_BMCAST_DATA_FRAME_COUNT,

    RX_MGMT_FRAME_COUNT,                    /* MGMT = BMCAST_MGMT + UCAST_MGMT */
    RX_UCAST_MGMT_FRAME_COUNT,
    RX_BMCAST_MGMT_FRAME_COUNT,

    RX_CTRL_FRAME_COUNT,                    /* No BMCAST in this category */

    RX_FIFO_FULL_DROP_COUNT,                /* FIFO_FULL is not included in TOTAL */
    RX_SIZE_ERR_DROP_COUNT,

    RX_ERROR_DROP_COUNT,                    /* ERROR(FCS/ICV/Format/Key) are not included in TOTAL */
    RX_FCS_ERR_DROP_COUNT,
    RX_FORMAT_ERR_DROP_COUNT,
    RX_ICV_ERR_DROP_COUNT,
    RX_KEY_ERR_DROP_COUNT,

    RX_TKIP_ERR_DROP_COUNT,                 /* TKIP ERROR is included in TOTAL */

    RX_RETRY_FRAME_COUNT,
    RX_DUPLICATE_DROP_COUNT,                /* Duplicate is included in TOTAL (* Only check UCAST frames) */

    RX_DATA_CLASS_ERR_DROP_COUNT,
    RX_DATA_PORT_CTRL_DROP_COUNT,

    RX_DATA_INDICATION_COUNT,               /* Null Data Frame will not be included in this category */

#if CFG_TCP_IP_CHKSUM_OFFLOAD
    RX_CSUM_TCP_FAILED_COUNT,
    RX_CSUM_UDP_FAILED_COUNT,
    RX_CSUM_IP_FAILED_COUNT,
    RX_CSUM_TCP_SUCCESS_COUNT,
    RX_CSUM_UDP_SUCCESS_COUNT,
    RX_CSUM_IP_SUCCESS_COUNT,
    RX_CSUM_UNKNOWN_L4_PKT_COUNT,
    RX_CSUM_UNKNOWN_L3_PKT_COUNT,
    RX_IP_V6_PKT_CCOUNT,
#endif

    RX_MPDU_CCK_SHORT_PREAMBLE_COUNT,       /* CCK short preamble packet in TOTAL */
    RX_MPDU_CCK_LONG_PREAMBLE_COUNT,        /* CCK long preamble packet in TOTAL */
    RX_BB_FCS_ERROR_COUNT,                  /* BB rx MPDU with FCS error in TOTAL */
    RX_BB_FIFO_FULL_COUNT,                  /* BB rx MPDU with FCS correct but is dicarded due to Fifo full in TOTAL */
    RX_BB_MPDU_COUNT,                       /* BB rx MPDU number in TOTAL */
    RX_BB_CHANNEL_IDLE_COUNT,               /*Channel idle count in unit of slot*/
    RX_BB_CCA_TIME_COUNT,                   /* BB CCA active timer in unit of us in TOTAL */
    RX_BB_CCANAVTX_TIME_COUNT,              /* BB CCA/NAV/Tx active timer in unit of us in TOTAL */
    RXTX_BEACON_TIMEOUT_COUNT,              /* Beacon timeout count in TOTAL */

    RX_MSDU_BYTES_COUNT,                    /* MSDU Rx Bytes count */


    RX_STATISTIC_COUNTER_NUM
} ENUM_RX_STATISTIC_COUNTER_T;

typedef enum _ENUM_RX_MULTICAST_TYPE_T {
    MC_TYPE_DENY_ALL,
    MC_TYPE_ALLOW_LIST,
    MC_TYPE_ALLOW_ALL,
    MC_TYPE_UPDATE_LIST_ONLY,
    MC_TYPE_NUM
} ENUM_RX_MULTICAST_TYPE_T, *P_ENUM_RX_MULTICAST_TYPE_T;


struct _SW_RFB_T {
    QUE_ENTRY_T             rQueEntry;
    PVOID                   pvPacket;     /* ptr to rx Packet Descriptor */
    PUINT_8                 pucRecvBuff; /* ptr to receive data buffer */

    P_RX_STATUS_T           prRxStatus;         /* ptr to rx status */
    P_STA_RECORD_T          prStaRec;           /* SwRfb_p's frame's source station record. */

    PVOID                   pvHeader;
    PVOID                   pvBody;

    UINT_16                 u2FrameLength;    /* total size of receive frame */
    UINT_16                 u2MACHeaderLength;/* MAC header length of received frame */

    BOOLEAN                 fgIs8023;           /* flag of 802.3 */
    BOOLEAN                 fgIsDataFrame;
    BOOLEAN                 fgIsNullData;
    BOOLEAN                 fgFragmented;

    ENUM_CSUM_RESULT_T      aeCSUM[CSUM_TYPE_NUM];

    UINT_8                  ucRxFlags;        /* QoS, A4 */
    UINT_8                  ucQosTID;         /* if QoS frame, this is TID in QoS Control Field */

    P_RX_STATUS_G0_T        prG0;
    P_RX_STATUS_G1_T        prG1;
    P_RX_STATUS_G2_T        prG2;
};


/* RX configuration type structure by *Mike* */
typedef struct _RX_CTRL_T {
    UINT_32                 u4RxCachedSize;
    PUINT_8                 pucRxCached;

    QUE_T                   rFreeRFBWithBuffList; /* RFB list with buffers */
    QUE_T                   rFreeRFBWOBuffList;   /* RFB list without buffers */
    QUE_T                   rReceivedRFBList;

    PVOID                   apvIndPacket[CFG_RX_MAX_PKT_NUM];
    UINT_8                  ucNumIndPacket;

    BOOLEAN                 fgIsDefragQueNonEmpty;

    BOOLEAN                 fgIsRxQueActive;
    BOOLEAN                 fgIsRxQueSuspend;

    UINT_64                 au8Statistics[RX_STATISTIC_COUNTER_NUM]; /* RX Counters */

    BOOLEAN                 fgRxFilter[RXFILTER_NUM];
    UINT_32                 u4RxFilterReg;

    BOOLEAN                 fgRxMulticastPkt;
    BOOLEAN                 fgRxMulticastPktByTable;


    BOOLEAN                 fgIsRxStatusG0; //TRUE when G0 field is enabled.
    BOOLEAN                 fgIsRxStatusG1;
    BOOLEAN                 fgIsRxStatusG2;
    BOOLEAN                 fgIsRxStatusG0Rssi; /*TRUE when G0 field is
                                            show RSSI group */

    BOOLEAN                 fgIsRfTestRxMode;
                           /* When TRUE, In RFTest mode*/

	BOOLEAN                 fgEnablePromiscuousMode;
} RX_CTRL_T, *P_RX_CTRL_T;


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
#define RX_INC_CNT(prRxCtrl, eCounter)              \
    {((P_RX_CTRL_T)prRxCtrl)->au8Statistics[eCounter]++;}

#define RX_ADD_CNT(prRxCtrl, eCounter, u8Amount)    \
    {((P_RX_CTRL_T)prRxCtrl)->au8Statistics[eCounter] += (UINT_64)u8Amount;}

#define RX_GET_CNT(prRxCtrl, eCounter)              \
    (((P_RX_CTRL_T)prRxCtrl)->au8Statistics[eCounter])

#define RX_RESET_ALL_CNTS(prRxCtrl)                 \
    {kalMemZero(&prRxCtrl->au8Statistics[0], sizeof(prRxCtrl->au8Statistics));}

#define NIC_RFB_IS_QOS(_prSWRfb)            \
            HAL_RX_STATUS_IS_QOS( ((P_SW_RFB_T)(_prSWRfb))->prRxStatus)

#define NIC_RFB_GET_SEQCTRL(_prSWRfb)       \
            HAL_RX_STATUS_GET_SEQCTRL( ((P_SW_RFB_T)(_prSWRfb))->prRxStatus)

#define NIC_RFB_IS_RETRY(_prSWRfb)          \
            HAL_RX_STATUS_IS_RETRY( ((P_SW_RFB_T)(_prSWRfb))->prRxStatus)

#define NIC_RFB_GET_RCPI(_prSWRfb)          \
            ( (RCPI)HAL_RX_STATUS_GET_RCPI( ((P_SW_RFB_T)(_prSWRfb))->prRxStatus) )

#define NIC_RFB_BSSID_MATCHED(_prSWRfb)     \
            HAL_RX_STATUS_BSSID_MATCHED( ((P_SW_RFB_T)(_prSWRfb))->prRxStatus)

#define NIC_RFB_GET_TA(_prSWRfb)            \
            HAL_RX_STATUS_GET_TA( ((P_SW_RFB_T)(_prSWRfb))->prRxStatus)

#define NIC_RFB_IS_TCL(_prSWRfb)            \
            HAL_RX_STATUS_IS_TCL( ((P_SW_RFB_T)(_prSWRfb))->prRxStatus)

/*******************************************************************************
*                   F U N C T I O N   D E C L A R A T I O N S
********************************************************************************
*/
VOID
nicRxInitialize (
    IN P_ADAPTER_T prAdapter
    );

VOID
nicRxUninitialize (
    IN P_ADAPTER_T prAdapter
    );

VOID
nicRxProcessRFBs (
    IN  P_ADAPTER_T prAdapter
    );

#if !CFG_SDIO_STATUS_ENHANCE
VOID
nicRxReceiveRFBs (
    IN  P_ADAPTER_T prAdapter
    );
#else
VOID
nicRxSDIOReceiveRFBs (
    IN  P_ADAPTER_T prAdapter
    );
#endif /* CFG_SDIO_STATUS_ENHANCE */

WLAN_STATUS
nicRxSetupRFB (
    IN P_ADAPTER_T prAdapter,
    IN P_SW_RFB_T  prRfb
    );

VOID
nicRxReturnRFB (
    IN P_ADAPTER_T prAdapter,
    IN P_SW_RFB_T  prRfb
    );

VOID
nicProcessRxInterrupt (
    IN  P_ADAPTER_T prAdapter
    );

VOID
nicRxStartQueue (
    IN P_ADAPTER_T prAdapter
    );

VOID
nicRxFlushStopQueue (
    IN P_ADAPTER_T prAdapter,
    BOOLEAN fgIsFlushRxQue,
    BOOLEAN fgIsStopRxQue
    );

VOID
nicRxAcquirePrivilegeOfRxQue (
    IN P_ADAPTER_T prAdapter,
    IN BOOLEAN fgIsStartRxQue,
    IN BOOLEAN fgIsStopRxQue,
    IN BOOLEAN fgIsFlushRxQue
    );

VOID
nicRxReleasePrivilegeOfRxQue (
    IN P_ADAPTER_T prAdapter,
    IN BOOLEAN fgIsFlushRxQue,
    IN BOOLEAN fgIsKeepRxActive
    );

VOID
nicRxQueryStatus (
    IN P_ADAPTER_T prAdapter,
    IN PUINT_8 pucBuffer,
    OUT PUINT_32 pu4Count
    );

VOID
nicRxQueryStatistics (
    IN P_ADAPTER_T prAdapter,
    IN PUINT_8 pucBuffer,
    OUT PUINT_32 pu4Count
    );

VOID
nicRxSetStatistics (
    IN P_ADAPTER_T prAdapter
    );

#if CFG_TCP_IP_CHKSUM_OFFLOAD
VOID
nicRxUpdateCSUMStatistics (
    IN P_ADAPTER_T prAdapter,
    IN ENUM_CSUM_RESULT_T aeCSUM[]
    );
#endif /* CFG_TCP_IP_CHKSUM_OFFLOAD */

VOID
nicRxEnablePromiscuousMode (
    IN P_ADAPTER_T prAdapter
    );
VOID
nicRxDisablePromiscuousMode (
    IN P_ADAPTER_T prAdapter
    );

VOID
nicRxSetMulticast (
    IN P_ADAPTER_T prAdapter,
    IN ENUM_RX_MULTICAST_TYPE_T eMCType,
    IN PUINT_8 prMCAddrList,
    IN UINT_8 ucNum
    );

void
nicRxSetBroadcast (
    IN P_ADAPTER_T prAdapter,
    IN BOOLEAN fgEnableBroadcast
    );

#endif /* _NIC_RX_H */

