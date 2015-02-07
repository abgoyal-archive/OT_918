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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/rx.h#2 $
*/

/*! \file   "rx.h"
    \brief  The declaration of the rx 802.11 protocol functions

    N/A.
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
** $Log: rx.h $
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\12 2009-07-09 18:53:17 GMT mtk01088
**  adding the wpi rx function declaration
**  \main\maintrunk.MT5921\11 2009-01-05 10:01:13 GMT mtk01725
**  Change compiling flag.
**  \main\maintrunk.MT5921\10 2008-08-21 00:19:57 GMT mtk01461
**  Update for Driver Review
**  \main\maintrunk.MT5921\9 2008-05-21 22:05:29 GMT mtk01084
**  combine CFG_LP_SLT in beacon RCPI measurement function
**  \main\maintrunk.MT5921\8 2008-05-16 10:33:40 GMT mtk01461
**  Add rxUpdateRssi() for RSSI OID
**  \main\maintrunk.MT5921\7 2008-04-02 20:43:56 GMT mtk01084
**  Support for RCPI variance histogram
**  \main\maintrunk.MT5921\6 2008-03-19 15:21:45 GMT mtk01461
**  Change FRAG_Q_STRUC_T to FRAG_INFO_T in STA_RECORD_T
**  \main\maintrunk.MT5921\5 2007-11-30 16:36:32 GMT mtk01425
**  1. Modify rxWlanHeaderTranslation declaration
**  \main\maintrunk.MT5921\4 2007-11-06 20:15:18 GMT mtk01088
**  add WPS funcion declaration. indicate mgmt
** Revision 1.2  2007/06/27 02:12:08  MTK01461
** Update SCAN_FSM, Initial(Can Load Module), Proc(Can do Reg R/W), TX API
**
*/
#ifndef _RX_H_
#define _RX_H_

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
#define MAX_NUM_CONCURRENT_FRAGMENTED_MSDUS     3

#define UPDATE_BSS_RSSI_INTERVAL_SEC            3 // Seconds

/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/
/* Fragment information structure */
typedef struct _FRAG_INFO_T {
    UINT_16                 u2NextFragSeqCtrl;
    PUINT_8                 pucNextFragStart;
    P_SW_RFB_T              pr1stFrag;
    OS_SYSTIME              rReceiveLifetimeLimit; /* The receive time of 1st fragment */
} FRAG_INFO_T, *P_FRAG_INFO_T;


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
WLAN_STATUS
rxProcessMSDU (
    IN P_ADAPTER_T prAdapter,
    IN P_SW_RFB_T prSWRfb
);

WLAN_STATUS
rxProcessMPDU (
    IN P_ADAPTER_T prAdapter,
    IN OUT PP_SW_RFB_T prSWRfb
);

#if SUPPORT_WPS
WLAN_STATUS
rxIndicateMgt(
    IN P_ADAPTER_T  prAdapter,
    IN P_SW_RFB_T   prSWRfb,
    IN UINT_8       ucFrameType
    );
#endif

WLAN_STATUS
rxProcessMgmtFrame (
    IN P_ADAPTER_T prAdapter,
    IN P_SW_RFB_T prSWRfb
    );

WLAN_STATUS
rxProcessDataFrame (
    IN P_ADAPTER_T prAdapter,
    IN P_SW_RFB_T prSWRfb
    );

WLAN_STATUS
rxFilterRecvPacket (
    IN P_ADAPTER_T prAdapter,
    IN P_SW_RFB_T prSWRfb
    );

BOOLEAN
rxIsDuplicateFrame (
    IN P_ADAPTER_T prAdapter,
    IN P_SW_RFB_T prSWRfb
    );

WLAN_STATUS
rxProcessMPDUSecurity (
    IN P_ADAPTER_T prAdapter,
    IN P_SW_RFB_T prSWRfb
    );

#if SUPPORT_WAPI
WLAN_STATUS
rxProcessMPDUWpiSecurity (
    IN P_ADAPTER_T prAdapter,
    IN P_SW_RFB_T prSWRfb
    );
#endif

P_SW_RFB_T
rxDefragMPDU(
    IN P_ADAPTER_T prAdapter,
    IN P_SW_RFB_T prSWRfb
    );

WLAN_STATUS
rxWlanHeaderTranslation (
    IN  P_ADAPTER_T prAdapter,
    IN  P_SW_RFB_T  prSwRfb
    );

VOID
rxUpdateRssi (
    IN P_ADAPTER_T  prAdapter
    );

#if (CFG_DBG_BEACON_RCPI_MEASUREMENT || CFG_LP_PATTERN_SEARCH_SLT)
VOID
rxRssiClearRssiLinkQualityRecords (
    IN  P_ADAPTER_T prAdapter
    );

INT_32
rxGetAverageRssi(
    IN  P_ADAPTER_T prAdapter,
    IN  INT_32      i4NewRssi
    );

BOOL
rxBcnRcpiMeasure (
    IN  P_ADAPTER_T prAdapter,
    IN  P_SW_RFB_T  prSwRfb
    );
#endif /* CFG_DBG_BEACON_RCPI_MEASUREMENT || CFG_LP_PATTERN_SEARCH_SLT */

#endif /* _RX_H_ */

