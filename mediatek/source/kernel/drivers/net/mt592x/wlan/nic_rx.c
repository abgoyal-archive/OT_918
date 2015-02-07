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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/nic_rx.c#1 $
*/

/*! \file   nic_rx.c
    \brief  Functions that provide many rx-related functions

    This file includes the functions used to process RFB and dispatch RFBs to
    the appropriate related rx functions for protocols.
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
** $Log: nic_rx.c $
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\56 2009-02-04 17:09:12 GMT mtk01725
**  Change nicRxSetupRFB() and nicRxReturnRFB() for META.
**  \main\maintrunk.MT5921\55 2009-02-02 14:26:46 GMT mtk01084
**  modify continuous polling mechanism, with not to do extra poll when no WiFi downlink traffic
**  \main\maintrunk.MT5921\54 2009-01-05 10:12:23 GMT mtk01725
**  Change compiling flag.
**  \main\maintrunk.MT5921\53 2008-12-01 17:53:58 GMT mtk01461
**  Fix warning
**  \main\maintrunk.MT5921\52 2008-12-01 13:56:25 GMT mtk01461
**  Remove Warning 613: Possible use of null pointer from lint
**  \main\maintrunk.MT5921\51 2008-11-28 17:38:22 GMT mtk01088
**  fixed the lint warning
**  \main\maintrunk.MT5921\50 2008-09-05 17:25:01 GMT mtk01461
**  Update Driver for Code Review
**  \main\maintrunk.MT5921\49 2008-08-25 18:23:01 GMT mtk01088
**  during whql test, at bssidlist item, at unload driver call halt, the rx packets not return for unknown reason, use retain to workaround this, use windows_ddk for xp only
**  \main\maintrunk.MT5921\48 2008-08-21 00:29:07 GMT mtk01461
**  Update for Driver Review
**  \main\maintrunk.MT5921\47 2008-08-05 01:53:04 GMT mtk01461
**  Add RX counter to support linux statistics
**  \main\maintrunk.MT5921\46 2008-06-12 20:29:40 GMT mtk01461
**  Remove unused compile flag of SCAN module which is work around for MPW
**  \main\maintrunk.MT5921\45 2008-05-30 20:28:25 GMT mtk01461
**  Rename KAL function
**  \main\maintrunk.MT5921\44 2008-05-21 16:50:44 GMT mtk01084
**  enable G0/G1/G2 in RX status when SLT is performed
**  \main\maintrunk.MT5921\43 2008-05-12 13:10:43 GMT mtk01084
**  remove the clear multicast address procedure when setting multicast as current packet filter
**  \main\maintrunk.MT5921\42 2008-04-24 12:02:30 GMT mtk01461
**  Add comment and alter the MC_TYPE enum of set multicast func
**  \main\maintrunk.MT5921\41 2008-04-11 17:13:18 GMT mtk01461
**  Fix EAPOL packet retry due to RX queue off/on
**  \main\maintrunk.MT5921\40 2008-04-02 20:48:34 GMT mtk01084
**  enable RX status for G0/ G1/ G2 when CFG_DBG_BEACON_RCPI_MEASUREMENT is enabled
**  \main\maintrunk.MT5921\39 2008-03-31 11:03:58 GMT mtk01461
**  Fix rx packet retain issue for XP
**  \main\maintrunk.MT5921\38 2008-03-19 15:22:10 GMT mtk01461
**  Add defragment buffer clean up point in nicProcessRxInterrupt
**  \main\maintrunk.MT5921\37 2008-03-11 13:40:25 GMT mtk01084
**  modify arbFsmRunEventScanRequest() function arguement
**  \main\maintrunk.MT5921\36 2008-02-01 10:22:46 GMT mtk01385
**  1. Fix WinCE 4.2 compiling error.
**  \main\maintrunk.MT5921\35 2008-01-31 16:17:10 GMT mtk01461
**  Add flush Queue process for NIC layer
**  \main\maintrunk.MT5921\34 2008-01-07 15:07:03 GMT mtk01461
**  Add SDIO Enhance Support
**  Add PhyType & AdHocMode Selection Support
**  \main\maintrunk.MT5921\33 2007-12-24 15:17:25 GMT mtk01425
**  1. Revise the rxfilter setting
**  \main\maintrunk.MT5921\32 2007-12-11 00:10:46 GMT mtk01461
**  Fix nicRxReleasePrivilege
**  \main\maintrunk.MT5921\31 2007-12-03 17:42:03 GMT mtk01084
**  do not receive probe response and beacon from other BSS except during scan state
**  \main\maintrunk.MT5921\30 2007-11-30 17:25:38 GMT mtk01425
**  1. Move promiscuous mode variable
**  \main\maintrunk.MT5921\29 2007-11-30 16:57:02 GMT mtk01425
**  1. Refine Rx path
**
**  \main\maintrunk.MT5921\28 2007-11-29 01:56:30 GMT mtk01461
**  Fix Windows RX multiple packet retain problem
**  \main\maintrunk.MT5921\27 2007-11-27 14:39:18 GMT mtk01385
**  1. Fix compiling error in linux.
**  \main\maintrunk.MT5921\26 2007-11-26 19:40:36 GMT mtk01461
**  Unify SCAN
**
**  \main\maintrunk.MT5921\25 2007-11-20 11:15:20 GMT mtk01084
**  filter out probe response/ beacon from different BSSID
**  \main\maintrunk.MT5921\24 2007-11-17 15:11:33 GMT mtk01385
**  1. Add Rf test mode Rx processing code.
**  \main\maintrunk.MT5921\23 2007-11-15 16:31:32 GMT mtk01088
**  add code for workaround CETK ndis performance
**  \main\maintrunk.MT5921\22 2007-11-13 17:08:32 GMT mtk01461
**  Fix the unexpected assert after chip reset - add memzero to rx initial
**  \main\maintrunk.MT5921\21 2007-11-13 16:24:54 GMT mtk01461
**  Fix the nicRxAcquirePrivilege() Assert after chip reset - sw flag not clear after chip reset
**  \main\maintrunk.MT5921\20 2007-11-08 20:39:45 GMT mtk01088
**  template let 1x always retain to let WZC got pkt
**  \main\maintrunk.MT5921\19 2007-11-06 18:31:51 GMT mtk01425
**  1. Change kalRxComputeCSUM to utilRxComputeCSUM
**  \main\maintrunk.MT5921\18 2007-11-05 17:06:06 GMT mtk01425
**  1. Refine Rx path, remove windows-specific kal function
**  2. Add nicRxUninitialize
**  \main\maintrunk.MT5921\17 2007-10-30 11:58:26 GMT MTK01425
**  1. Fix compiling warning
**  \main\maintrunk.MT5921\16 2007-10-30 10:29:16 GMT mtk01425
**  1. Refine multicast list code
** Revision 1.3  2007/07/05 07:25:32  MTK01461
** Add Linux initial code, modify doc, add 11BB, RF init code
**
** Revision 1.2  2007/06/27 02:18:50  MTK01461
** Update SCAN_FSM, Initial(Can Load Module), Proc(Can do Reg R/W), TX API
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
/*----------------------------------------------------------------------------*/
/*!
* \brief Initialize the RFBs
*
* \param[in] prAdapter      Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
nicRxInitialize (
    IN P_ADAPTER_T prAdapter
    )
{
    P_RX_CTRL_T prRxCtrl;
    PUINT_8 pucMemHandle;
    P_SW_RFB_T prRfb = (P_SW_RFB_T)NULL;
    INT_32 i;


    ASSERT(prAdapter);
    prRxCtrl = &prAdapter->rRxCtrl;

    //4 <0> Clear allocated memory.
    kalMemZero((PVOID) prRxCtrl->pucRxCached, prRxCtrl->u4RxCachedSize);

    //4 <1> Initialize the RFB lists
    QUEUE_INITIALIZE(&prRxCtrl->rFreeRFBWithBuffList);
    QUEUE_INITIALIZE(&prRxCtrl->rFreeRFBWOBuffList);
    QUEUE_INITIALIZE(&prRxCtrl->rReceivedRFBList);

    pucMemHandle = prRxCtrl->pucRxCached;
    for (i = CFG_RX_MAX_PKT_NUM; i != 0; i--) {
        prRfb = (P_SW_RFB_T)pucMemHandle;

        nicRxSetupRFB(prAdapter, prRfb);

        nicRxReturnRFB(prAdapter, prRfb);

        pucMemHandle += ALIGN_4(sizeof(SW_RFB_T));
    }

    ASSERT(prRxCtrl->rFreeRFBWithBuffList.u4NumElem == CFG_RX_MAX_PKT_NUM);

    /* Check if the memory allocation consist with this initialization function */
    ASSERT((UINT_32)(pucMemHandle - prRxCtrl->pucRxCached) == prRxCtrl->u4RxCachedSize);


    //4 <2> Initialization of RX Queue Status.
    prRxCtrl->fgIsDefragQueNonEmpty = FALSE;
    prRxCtrl->fgIsRxQueActive = FALSE;
    prRxCtrl->fgIsRxQueSuspend = FALSE;
    prRxCtrl->fgIsRfTestRxMode = FALSE;
#if (CFG_DBG_BEACON_RCPI_MEASUREMENT || CFG_LP_PATTERN_SEARCH_SLT)
    prRxCtrl->fgIsRxStatusG0 = TRUE;
    prRxCtrl->fgIsRxStatusG1 = TRUE;
    prRxCtrl->fgIsRxStatusG2 = TRUE;
    prRxCtrl->fgIsRxStatusG0Rssi = TRUE;
#else
    prRxCtrl->fgIsRxStatusG0 = FALSE;
    prRxCtrl->fgIsRxStatusG1 = FALSE;
    prRxCtrl->fgIsRxStatusG2 = FALSE;
    prRxCtrl->fgIsRxStatusG0Rssi = FALSE;
#endif

    //4 <3> Clear all RX counters
    RX_RESET_ALL_CNTS(prRxCtrl);


    //4 <4> Rx filter default value
    NIC_SET_RX_FILTER(prAdapter, RXFILTER_RXSAMEBSSIDPRORESP);
    NIC_UNSET_RX_FILTER(prAdapter, RXFILTER_RXDIFFBSSIDPRORESP);
    NIC_SET_RX_FILTER(prAdapter, RXFILTER_RXSAMEBSSIDBCN);
    NIC_UNSET_RX_FILTER(prAdapter, RXFILTER_RXDIFFBSSIDBCN);
    NIC_SET_RX_FILTER(prAdapter, RXFILTER_RXNOACK);
    NIC_SET_RX_FILTER(prAdapter, RXFILTER_DROPVERSIONNOT0);
    NIC_SET_RX_FILTER(prAdapter, RXFILTER_DROPA3OWNSA);
    NIC_SET_RX_FILTER(prAdapter, RXFILTER_DROPDIFFBSSIDA3);
    NIC_SET_RX_FILTER(prAdapter, RXFILTER_DROPDIFFBSSIDA2);
    NIC_SET_RX_FILTER(prAdapter, RXFILTER_RXMCFRAME);
    NIC_SET_RX_FILTER(prAdapter, RXFILTER_RXBCFRAME);
    NIC_SET_RX_FILTER(prAdapter, RXFILTER_DROPFCS);
    NIC_UNSET_RX_FILTER(prAdapter, RXFILTER_RXSAMEBSSIDNULL); //090202 juji
    NIC_UNSET_RX_FILTER(prAdapter, RXFILTER_RXDIFFBSSIDNULL); //090202 juji

    return;
} /* end of nicRxInitialize() */


/*----------------------------------------------------------------------------*/
/*!
* \brief Uninitialize the RFBs
*
* \param[in] prAdapter      Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
nicRxUninitialize (
    IN P_ADAPTER_T prAdapter
    )
{
    P_RX_CTRL_T prRxCtrl;
    P_SW_RFB_T prRfb = (P_SW_RFB_T)NULL;


    ASSERT(prAdapter);
    prRxCtrl = &prAdapter->rRxCtrl;

    if (prRxCtrl) {

        do {

            QUEUE_REMOVE_HEAD(&prRxCtrl->rReceivedRFBList, prRfb, P_SW_RFB_T);
            if (!prRfb) {
                break;
            }

            if (prRfb->pvPacket) {
                kalPacketFree(prAdapter->prGlueInfo, prRfb->pvPacket);
            }
            prRfb->pvPacket= NULL;
        }
        while (TRUE);

        do {

            QUEUE_REMOVE_HEAD(&prRxCtrl->rFreeRFBWithBuffList, prRfb, P_SW_RFB_T);
            if (!prRfb) {
                break;
            }

            if (prRfb->pvPacket) {
                kalPacketFree(prAdapter->prGlueInfo, prRfb->pvPacket);
            }
            prRfb->pvPacket= NULL;
        }
        while (TRUE);

    }

    return;
} /* end of nicRxUninitialize() */


/*----------------------------------------------------------------------------*/
/*!
* \brief nicProcessRFBs is used to process RFBs in the rReceivedRFBList queue.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
nicRxProcessRFBs (
    IN  P_ADAPTER_T prAdapter
    )
{
    P_RX_CTRL_T prRxCtrl;
    P_QUE_T prReceivedRFBList;
    P_SW_RFB_T prSWRfb = NULL;
    UINT_32 u4CurrentRxBufferCount;
    BOOLEAN fgIsRetained = FALSE;

    DEBUGFUNC("nicRxProcessRFBs");


    ASSERT(prAdapter);
    prRxCtrl = &prAdapter->rRxCtrl;
    prReceivedRFBList = &prRxCtrl->rReceivedRFBList;

    prRxCtrl->ucNumIndPacket = 0;
    u4CurrentRxBufferCount = prRxCtrl->rFreeRFBWithBuffList.u4NumElem +
                             prReceivedRFBList->u4NumElem;

    //4 <1> Remove SW_RFB from rReceivedRFBList Queue
    do {

        QUEUE_REMOVE_HEAD(prReceivedRFBList, prSWRfb, P_SW_RFB_T);
        if (!prSWRfb) {
            break;
        }

        if (prRxCtrl->fgIsRfTestRxMode) {
            rftestProcessRxMPDU(prAdapter, &prSWRfb);
            nicRxReturnRFB(prAdapter, prSWRfb);
            continue;
        }

        /* Process MPDU */
        if (rxProcessMPDU(prAdapter, &prSWRfb) != WLAN_STATUS_SUCCESS) {

            DBGLOG(RX, TRACE, ("Process MPDU error\n"));

            if (prSWRfb) {
                nicRxReturnRFB(prAdapter, prSWRfb);
            }
            continue;
        }

        /* Process MSDU */
        if (rxProcessMSDU(prAdapter, prSWRfb)) {
            DBGLOG(RX, TRACE, ("Process MSDU error\n"));

            nicRxReturnRFB(prAdapter, prSWRfb);
            continue;
        }

        if (prSWRfb->fgIsDataFrame &&
            (prAdapter->eConnectionStateIndicated == MEDIA_STATE_CONNECTED)) {

            if (rxProcessDataFrame(prAdapter, prSWRfb)) { /*rxProcessDataFrame failed*/

                nicRxReturnRFB(prAdapter, prSWRfb);
            }
            else {/*rxProcessDataFrame success*/

                #if defined (WINDOWS_DDK) /* CR1088 */
                fgIsRetained = TRUE;
                #else
                fgIsRetained = ((u4CurrentRxBufferCount < CFG_RX_MGMT_PKT_NUM_THRESHOLD) ?
                                TRUE : FALSE);
                #endif

                if (kalProcessRxPacket(prAdapter->prGlueInfo,
                                       prSWRfb->pvPacket,
                                       prSWRfb->pvHeader,
                                       prSWRfb->u2FrameLength,
                                       &fgIsRetained, prSWRfb->aeCSUM) != WLAN_STATUS_SUCCESS) {
                    DBGLOG(NIC, ERROR, ("kalProcessRxPacket return value != WLAN_STATUS_SUCCESS\n"));
                    ASSERT(0);

                    nicRxReturnRFB(prAdapter, prSWRfb);
                    continue;
                }
                else {
                    UINT_64 u8FrameLength;


                    u8FrameLength = (UINT_64)prSWRfb->u2FrameLength;

                    RX_ADD_CNT(prRxCtrl, RX_MSDU_BYTES_COUNT, u8FrameLength);


                    prRxCtrl->apvIndPacket[prRxCtrl->ucNumIndPacket++] = prSWRfb->pvPacket;
                }

                if (fgIsRetained) {
                    /* TODO : error handling of nicRxSetupRFB */
                    nicRxSetupRFB(prAdapter, prSWRfb);
                    nicRxReturnRFB(prAdapter, prSWRfb);
                }
                else{
                    u4CurrentRxBufferCount--;

                    prSWRfb->pvPacket = NULL;
                    nicRxReturnRFB(prAdapter, prSWRfb);
                }
            }

        }
        else {
            rxProcessMgmtFrame(prAdapter, prSWRfb);
            nicRxReturnRFB(prAdapter, prSWRfb);
        }

    }
    while (TRUE);

    if (prRxCtrl->ucNumIndPacket > 0) {
        DBGLOG(RX, TRACE, ("%d packets will be indicated\n", prRxCtrl->ucNumIndPacket));

        RX_ADD_CNT(prRxCtrl, RX_DATA_INDICATION_COUNT, prRxCtrl->ucNumIndPacket);

        if (kalRxIndicatePkts(prAdapter->prGlueInfo,
                              prRxCtrl->apvIndPacket,
                              prRxCtrl->ucNumIndPacket)) {/* Deal with the current RFB */
            DBGLOG(RX, TRACE, ("Indicate MSDUs error\n"));
        }
    }

    return;

} /* end of nicRxProcessRFBs() */


#if !CFG_SDIO_STATUS_ENHANCE
/*----------------------------------------------------------------------------*/
/*!
* \brief nicReceiveRFBs is used to read frames from the data port, fill RFB
*        and put each frame into the rReceivedRFBList queue.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
nicRxReceiveRFBs (
    IN P_ADAPTER_T  prAdapter
    )
{
    P_RX_CTRL_T prRxCtrl;
    P_QUE_T prFreeRFBWithBuffList;
    P_QUE_T prReceivedRFBList;
    P_SW_RFB_T prSWRfb = NULL;


    ASSERT(prAdapter);
    prRxCtrl = &prAdapter->rRxCtrl;
    prFreeRFBWithBuffList = &prRxCtrl->rFreeRFBWithBuffList;
    prReceivedRFBList = &prRxCtrl->rReceivedRFBList;

    do {

        QUEUE_REMOVE_HEAD(prFreeRFBWithBuffList, prSWRfb, P_SW_RFB_T);
        /* The "RFB with Buffer" list is empty */
        if (!prSWRfb) {
            P_QUE_T prFreeRFBWOBuffList = &prRxCtrl->rFreeRFBWOBuffList;
            P_SW_RFB_T prSWRfbWOBuff;

            do {
                /* Try to get the RFB from "RFB without Buffer" list */
                QUEUE_REMOVE_HEAD(prFreeRFBWOBuffList, prSWRfbWOBuff, P_SW_RFB_T);
                if (!prSWRfbWOBuff) {
                    break;
                }

                if (nicRxSetupRFB(prAdapter, prSWRfbWOBuff) != WLAN_STATUS_SUCCESS) {
                    QUEUE_INSERT_HEAD(prFreeRFBWOBuffList, &prSWRfbWOBuff->rQueEntry);
                    break;
                }
                else {
                    QUEUE_INSERT_HEAD(prFreeRFBWithBuffList, &prSWRfbWOBuff->rQueEntry);
                }
            }
            while (TRUE);

            QUEUE_REMOVE_HEAD(prFreeRFBWithBuffList, prSWRfb, P_SW_RFB_T);
            /* The "RFB with Buffer" list is still empty ! */
            if (!prSWRfb) {
                DBGLOG(RX, TRACE, ("No More RFB\n"));
                break; /* Break outter do {} while loop */
            }
        }

        ASSERT(prSWRfb);

        if (halRxFillRFB(prAdapter, prSWRfb)) {
            DBGLOG(RX, TRACE, ("halRxFillRFB failed\n"));
            nicRxReturnRFB(prAdapter, prSWRfb);
            break;
        }

        QUEUE_INSERT_TAIL(prReceivedRFBList, &prSWRfb->rQueEntry);

        RX_INC_CNT(prRxCtrl, RX_MPDU_TOTAL_COUNT);

    }
    while (HAL_IS_MORE_RX_PKT(prSWRfb->prRxStatus));

    return;

} /* end of nicReceiveRFBs() */

#else

/*----------------------------------------------------------------------------*/
/*!
* \brief nicRxSDIOReceiveRFBs is used to read frames from the data port for SDIO
*        I/F, fill RFB and put each frame into the rReceivedRFBList queue.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
nicRxSDIOReceiveRFBs (
    IN  P_ADAPTER_T prAdapter
    )
{
    P_RX_CTRL_T prRxCtrl;
    P_QUE_T prFreeRFBWithBuffList;
    P_QUE_T prReceivedRFBList;
    P_SW_RFB_T prSWRfb = (P_SW_RFB_T)NULL;
    P_SDIO_CTRL_T prSDIOCtrl;
    UINT_32 i;

    DEBUGFUNC("nicRxSDIOReceiveRFBs");


    ASSERT(prAdapter);
    prRxCtrl = &prAdapter->rRxCtrl;
    prFreeRFBWithBuffList = &prRxCtrl->rFreeRFBWithBuffList;
    prReceivedRFBList = &prRxCtrl->rReceivedRFBList;
    prSDIOCtrl = &prAdapter->rSDIOCtrl;

    for (i = 0; i < SDIO_MAXIMUM_RX_STATUS; i++) {

        if (!(prSDIOCtrl->au2RxLengthDW[i])) {
            break;
        }

        QUEUE_REMOVE_HEAD(prFreeRFBWithBuffList, prSWRfb, P_SW_RFB_T);
        /* The "RFB with Buffer" list is empty */
        if (!prSWRfb) {
            P_QUE_T prFreeRFBWOBuffList = &prRxCtrl->rFreeRFBWOBuffList;
            P_SW_RFB_T prSWRfbWOBuff;

            do {
                /* Try to get the RFB from "RFB without Buffer" list */
                QUEUE_REMOVE_HEAD(prFreeRFBWOBuffList, prSWRfbWOBuff, P_SW_RFB_T);
                if (!prSWRfbWOBuff) {
                    break;
                }

                if (nicRxSetupRFB(prAdapter, prSWRfbWOBuff) != WLAN_STATUS_SUCCESS) {
                    QUEUE_INSERT_HEAD(prFreeRFBWOBuffList, &prSWRfbWOBuff->rQueEntry);
                    break;
                }
                else {
                    QUEUE_INSERT_HEAD(prFreeRFBWithBuffList, &prSWRfbWOBuff->rQueEntry);
                }
            }
            while (TRUE);

            QUEUE_REMOVE_HEAD(prFreeRFBWithBuffList, prSWRfb, P_SW_RFB_T);
            /* The "RFB with Buffer" list is still empty ! */
            if (!prSWRfb) {
                DBGLOG(RX, TRACE, ("No More RFB\n"));
                break; /* Break outter for loop */
            }
        }

        ASSERT(prSWRfb);

        if (halSDIORxFillRFB(prAdapter, prSDIOCtrl->au2RxLengthDW[i], prSWRfb) == WLAN_STATUS_FAILURE) {
            DBGLOG(RX, TRACE, ("halRxFillRFB failed\n"));
            nicRxReturnRFB(prAdapter, prSWRfb);
            break;
        }

        //Clear RX STATUS in STATUS Buffer.
        prSDIOCtrl->au2RxLengthDW[i] = 0;

        QUEUE_INSERT_TAIL(prReceivedRFBList, &prSWRfb->rQueEntry);

        RX_INC_CNT(prRxCtrl, RX_MPDU_TOTAL_COUNT);
    }

    return;
}/* end of nicRxSDIOReceiveRFBs() */

#endif /* CFG_SDIO_STATUS_ENHANCE */

#if CFG_SDIO_DEVICE_DRIVER_WO_NDIS

/*----------------------------------------------------------------------------*/
/*!
* \brief Setup a RFB and allocate the os packet to the RFB
*
* \param[in] prAdapter      Pointer to the Adapter structure.
* \param[in] prRfb          Pointer to the RFB
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_RESOURCES
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
nicRxSetupRFB (
    IN P_ADAPTER_T prAdapter,
    IN P_SW_RFB_T  prRfb
    )
{
    P_GLUE_INFO_T prGlueInfo;


    ASSERT(prAdapter);
    ASSERT(prRfb);

    prGlueInfo = prAdapter->prGlueInfo;

    kalMemZero(((PUINT_8)prRfb + OFFSET_OF(SW_RFB_T, prRxStatus)),
                   (sizeof(SW_RFB_T)-OFFSET_OF(SW_RFB_T, prRxStatus)));


    if (prRfb->pucRecvBuff == NULL) {
        if (prGlueInfo->u4PayloadPoolSz >= CFG_RX_MAX_PKT_SIZE) {
            prGlueInfo->u4PayloadPoolSz -= CFG_RX_MAX_PKT_SIZE;
            prRfb->pucRecvBuff = prGlueInfo->pucPayloadPool;
            prGlueInfo->pucPayloadPool += CFG_RX_MAX_PKT_SIZE;
        }
    }

    prRfb->prRxStatus = (P_RX_STATUS_T)(prRfb->pucRecvBuff);

    return WLAN_STATUS_SUCCESS;

} /* end of nicRxSetupRFB() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to put a RFB back onto the "RFB with Buffer" list
*        or "RFB without buffer" list according to pvPacket.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
* \param[in] prRfb          Pointer to the RFB
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
nicRxReturnRFB (
    IN P_ADAPTER_T prAdapter,
    IN P_SW_RFB_T  prRfb
    )
{
    P_RX_CTRL_T prRxCtrl;
    P_QUE_ENTRY_T prQueEntry;
     P_QUE_T prFreeRFBWithBuffList;


    ASSERT(prAdapter);
    ASSERT(prRfb);
    prRxCtrl = &prAdapter->rRxCtrl;
    prQueEntry = &prRfb->rQueEntry;

    /* The processing on this RFB is done, so put it back on the tail of
       our list */
    prFreeRFBWithBuffList = &prRxCtrl->rFreeRFBWithBuffList;

    QUEUE_INSERT_TAIL(prFreeRFBWithBuffList, prQueEntry);


    return;
} /* end of nicRxReturnRFB() */


#else


/*----------------------------------------------------------------------------*/
/*!
* \brief Setup a RFB and allocate the os packet to the RFB
*
* \param[in] prAdapter      Pointer to the Adapter structure.
* \param[in] prRfb          Pointer to the RFB
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_RESOURCES
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
nicRxSetupRFB (
    IN P_ADAPTER_T prAdapter,
    IN P_SW_RFB_T  prRfb
    )
{
    PVOID   pvPacket;
    PUINT_8 pucRecvBuff;


    ASSERT(prAdapter);
    ASSERT(prRfb);

    if (!prRfb->pvPacket) {
        kalMemZero(prRfb, sizeof(SW_RFB_T));

        pvPacket = kalPacketAlloc(prAdapter->prGlueInfo,
                                  CFG_RX_MAX_PKT_SIZE,
                                  &pucRecvBuff);

        if (pvPacket == NULL) {
            return WLAN_STATUS_RESOURCES;
        }

        prRfb->pvPacket = pvPacket;
        //4 2006/10/17, mikewu, use pvRecvBuff instead of receiveBuffer_p

        ASSERT(IS_ALIGN_4((UINT_32)pucRecvBuff));

        prRfb->pucRecvBuff= pucRecvBuff;
    }
    else {
        kalMemZero(((PUINT_8)prRfb + OFFSET_OF(SW_RFB_T, prRxStatus)),
                   (sizeof(SW_RFB_T)-OFFSET_OF(SW_RFB_T, prRxStatus)));
    }

    prRfb->prRxStatus = (P_RX_STATUS_T)(prRfb->pucRecvBuff);

    return WLAN_STATUS_SUCCESS;

} /* end of nicRxSetupRFB() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to put a RFB back onto the "RFB with Buffer" list
*        or "RFB without buffer" list according to pvPacket.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
* \param[in] prRfb          Pointer to the RFB
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
nicRxReturnRFB (
    IN P_ADAPTER_T prAdapter,
    IN P_SW_RFB_T  prRfb
    )
{
    P_RX_CTRL_T prRxCtrl;
    P_QUE_ENTRY_T prQueEntry;


    ASSERT(prAdapter);
    ASSERT(prRfb);
    prRxCtrl = &prAdapter->rRxCtrl;
    prQueEntry = &prRfb->rQueEntry;

    /* The processing on this RFB is done, so put it back on the tail of
       our list */
    if (prRfb->pvPacket) {
        P_QUE_T prFreeRFBWithBuffList = &prRxCtrl->rFreeRFBWithBuffList;

        QUEUE_INSERT_TAIL(prFreeRFBWithBuffList, prQueEntry);
    }
    else {
        P_QUE_T prFreeRFBWOBuffList = &prRxCtrl->rFreeRFBWOBuffList;

        QUEUE_INSERT_TAIL(prFreeRFBWOBuffList, prQueEntry);
    }

    return;
} /* end of nicRxReturnRFB() */

#endif /* CFG_SDIO_DEVICE_DRIVER_WO_NDIS */

/*----------------------------------------------------------------------------*/
/*!
* \brief nicProcessRxInterrupt is used to process rx interrupt. When the rx
*        Interrupt is asserted, it means there are frames in queue.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
nicProcessRxInterrupt (
    IN  P_ADAPTER_T prAdapter
    )
{
    P_RX_CTRL_T prRxCtrl;


    ASSERT(prAdapter);
    prRxCtrl = &prAdapter->rRxCtrl;

    if (prRxCtrl->fgIsDefragQueNonEmpty) {
        staRecCheckDefragBufOfAllStaRecords(prAdapter);
    }

    //DBGLOG(RX, TRACE, ("Enter RX\n"));

    //4 2007/06/20, collect RFB into RxRoughQueue
#if !CFG_SDIO_STATUS_ENHANCE
    nicRxReceiveRFBs(prAdapter);
#else
    nicRxSDIOReceiveRFBs(prAdapter);
#endif /* CFG_SDIO_STATUS_ENHANCE */

    nicRxProcessRFBs(prAdapter);

    return;

} /* end of nicProcessRxInterrupt() */


/*----------------------------------------------------------------------------*/
/*!
* \brief Start RX Queue
*
* \param[in] prAdapter      Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
nicRxStartQueue (
    IN P_ADAPTER_T prAdapter
    )
{
    P_RX_CTRL_T prRxCtrl;


    ASSERT(prAdapter);
    prRxCtrl = &prAdapter->rRxCtrl;

    /* Start it only when it was disabled. */
    if (!prRxCtrl->fgIsRxQueActive) {
        prRxCtrl->fgIsRxQueActive = TRUE;

        halStartQueues(prAdapter, BIT(RXQ));
    }

    return;
} /* end of nicRxStartQueue() */


/*----------------------------------------------------------------------------*/
/*!
* \brief Flush and Stop RX Queue
*
* \param[in] prAdapter      Pointer to the Adapter structure.
* \param[in] fgIsFlushRxQue Set TRUE to flush RX Queue.
* \param[in] fgIsStopRxQue  Set TRUE to stop RX Queue.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
nicRxFlushStopQueue (
    IN P_ADAPTER_T prAdapter,
    IN BOOLEAN fgIsFlushRxQue,
    IN BOOLEAN fgIsStopRxQue
    )
{
    P_RX_CTRL_T prRxCtrl;


    ASSERT(prAdapter);
    prRxCtrl = &prAdapter->rRxCtrl;

    if (fgIsFlushRxQue || fgIsStopRxQue) {

        if (fgIsStopRxQue) {
            prRxCtrl->fgIsRxQueActive = FALSE;
        }

        halFlushStopQueues(prAdapter,
            (fgIsFlushRxQue ? BIT(RXQ) : 0),
            (fgIsStopRxQue ? BIT(RXQ) : 0));

#if CFG_SDIO_STATUS_ENHANCE
        if (fgIsFlushRxQue) {
            P_SDIO_CTRL_T prSDIOCtrl = &prAdapter->rSDIOCtrl;

            kalMemZero(prSDIOCtrl->au2RxLengthDW, sizeof(prSDIOCtrl->au2RxLengthDW));
        }
#endif /* CFG_SDIO_STATUS_ENHANCE */

    }

    return;
} /* end of nicRxFlushStopQueue() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function is used by ARB to stop/start/flush RX Queue during ARB
*        STATE transition. It will also save current RX queue status for later recovery.
*        (Set start & stop at the same time means stop first and then start)
*
* \param[in] prAdapter      Pointer to the Adapter structure.
* \param[in] fgIsStartRxQue Set TRUE to start RX Queue.
* \param[in] fgIsStopRxQue  Set TRUE to stop RX Queue.
* \param[in] fgIsFlushRxQue Set TRUE to flush RX Queue.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
nicRxAcquirePrivilegeOfRxQue (
    IN P_ADAPTER_T prAdapter,
    IN BOOLEAN fgIsStartRxQue,
    IN BOOLEAN fgIsStopRxQue,
    IN BOOLEAN fgIsFlushRxQue
    )
{
    P_RX_CTRL_T prRxCtrl;


    ASSERT(prAdapter);
    prRxCtrl = &prAdapter->rRxCtrl;

    ASSERT(prRxCtrl->fgIsRxQueSuspend == (BOOLEAN)FALSE);

    /* Backup the flag of RX Queue's activity for resuming the RX after the Privilege was released. */
    prRxCtrl->fgIsRxQueSuspend = prRxCtrl->fgIsRxQueActive;

    /* NOTE(Kevin): For most cases, we'll not issue fgIsStartRxQue and fgIsStopRxQue
     * at the same time. But we won't exclude this condition that "Stop & Flush" firstly
     * before Start it if we need such combination one day.
     */

    /* Flush and stop the RX Queue first */
    nicRxFlushStopQueue(prAdapter, fgIsFlushRxQue, fgIsStopRxQue);

    /* Start the R Queue */
    if (fgIsStartRxQue) {
        nicRxStartQueue(prAdapter);
    }

    return;
} /* end of nicRxAcquirePrivilegeOfRxQue() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function is used by ARB to flush RX Queue during ARB STATE transition.
*        And it will also restore previous RX queue status.
*
* \param[in] prAdapter          Pointer to the Adapter structure.
* \param[in] fgIsFlushRxQue     Set TRUE to flush RX Queue.
* \param[in] fgIsKeepRxActive   Set TRUE to keep RX Queue active.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
nicRxReleasePrivilegeOfRxQue (
    IN P_ADAPTER_T prAdapter,
    IN BOOLEAN fgIsFlushRxQue,
    IN BOOLEAN fgIsKeepRxActive
    )
{
    P_RX_CTRL_T prRxCtrl;
    BOOLEAN fgIsStartRxQue;
    BOOLEAN fgIsStopRxQue;


    ASSERT(prAdapter);
    prRxCtrl = &prAdapter->rRxCtrl;

    /* fgIsKeepRxActive can set to TRUE if only if
     * 1. We know RX is enabled in current STATE.
     * 2. We need to let RX keep enabled in next STATE.
     */
    if (fgIsKeepRxActive) {
        prRxCtrl->fgIsRxQueSuspend = TRUE;
    }

    /* Restore the original activity of RX Queue after the Privilege was released. */
    fgIsStartRxQue = ((prRxCtrl->fgIsRxQueSuspend && (!prRxCtrl->fgIsRxQueActive)) ? TRUE : FALSE);
    fgIsStopRxQue = (((!prRxCtrl->fgIsRxQueSuspend) && prRxCtrl->fgIsRxQueActive) ? TRUE : FALSE);
    //fgIsStopRxQue = ((prRxCtrl->fgIsRxQueActive) ? TRUE : FALSE); // (force it to stop for SW/HW sync just in case)

    /* NOTE(Kevin 2007/12/7): Truth Table.
     * fgIsRxQueSuspend fgIsRxQueActive fgIsStartRxQue fgIsStopRxQue
     * TRUE             FALSE           TRUE           FALSE
     * FALSE            TRUE            FALSE          TRUE
     * TRUE             TRUE            FALSE          FALSE//-->TRUE(force it to stop for SW/HW sync)
     * FALSE            FALSE           FALSE          FALSE
     */

    /* Clear the flag of Suspend RX Queue. */
    prRxCtrl->fgIsRxQueSuspend = FALSE;

    /* Flush and stop the RX Queue first */
    nicRxFlushStopQueue(prAdapter, fgIsFlushRxQue, fgIsStopRxQue);

    /* Start the RX Queue */
    if (fgIsStartRxQue) {
        nicRxStartQueue(prAdapter);
    }

    return;
} /* end of nicRxReleasePrivilegeOfRxQue() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function is used to query current status of RX Module.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
* \param[in] pucBuffer      Pointer to the message buffer.
* \param[out] pu4Count      Pointer to the buffer of message length count.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
nicRxQueryStatus (
    IN P_ADAPTER_T prAdapter,
    IN PUINT_8 pucBuffer,
    OUT PUINT_32 pu4Count
    )
{
    P_RX_CTRL_T prRxCtrl;
    PUINT_8 pucCurrBuf = pucBuffer;


    ASSERT(prAdapter);
    prRxCtrl = &prAdapter->rRxCtrl;
    if (pucBuffer) {} /* For Windows, we'll print directly instead of sprintf() */
    ASSERT(pu4Count);

    SPRINTF(pucCurrBuf, ("\n\nRX CTRL STATUS:"));
    SPRINTF(pucCurrBuf, ("\n==============="));
    SPRINTF(pucCurrBuf, ("\nFREE RFB w/i BUF LIST :%9ld", prRxCtrl->rFreeRFBWithBuffList.u4NumElem));
    SPRINTF(pucCurrBuf, ("\nFREE RFB w/o BUF LIST :%9ld", prRxCtrl->rFreeRFBWOBuffList.u4NumElem));
    SPRINTF(pucCurrBuf, ("\nRECEIVED RFB LIST     :%9ld", prRxCtrl->rReceivedRFBList.u4NumElem));

    SPRINTF(pucCurrBuf, ("\n\n"));

    *pu4Count = (UINT_32)((UINT_32)pucCurrBuf - (UINT_32)pucBuffer);

    return;
} /* end of nicRxQueryStatus() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function is used to query current statistics of RX Module.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
* \param[in] pucBuffer      Pointer to the message buffer.
* \param[out] pu4Count      Pointer to the buffer of message length count.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
nicRxQueryStatistics (
    IN P_ADAPTER_T prAdapter,
    IN PUINT_8 pucBuffer,
    OUT PUINT_32 pu4Count
    )
{
    P_RX_CTRL_T prRxCtrl;
    PUINT_8 pucCurrBuf = pucBuffer;


    ASSERT(prAdapter);
    prRxCtrl = &prAdapter->rRxCtrl;
    if (pucBuffer) {} /* For Windows, we'll print directly instead of sprintf() */
    ASSERT(pu4Count);

#define SPRINTF_RX_COUNTER(eCounter) \
    SPRINTF(pucCurrBuf, ("%-30s : %ld\n", #eCounter, (UINT_32)prRxCtrl->au8Statistics[eCounter]))


    SPRINTF_RX_COUNTER(RX_MPDU_TOTAL_COUNT);

    SPRINTF_RX_COUNTER(RX_DATA_FRAME_COUNT);
    SPRINTF_RX_COUNTER(RX_UCAST_DATA_FRAME_COUNT);
    SPRINTF_RX_COUNTER(RX_BMCAST_DATA_FRAME_COUNT);

    SPRINTF_RX_COUNTER(RX_MGMT_FRAME_COUNT);
    SPRINTF_RX_COUNTER(RX_UCAST_MGMT_FRAME_COUNT);
    SPRINTF_RX_COUNTER(RX_BMCAST_MGMT_FRAME_COUNT);

    SPRINTF_RX_COUNTER(RX_CTRL_FRAME_COUNT);

    SPRINTF_RX_COUNTER(RX_FIFO_FULL_DROP_COUNT);
    SPRINTF_RX_COUNTER(RX_SIZE_ERR_DROP_COUNT);

    SPRINTF_RX_COUNTER(RX_ERROR_DROP_COUNT);
    SPRINTF_RX_COUNTER(RX_FCS_ERR_DROP_COUNT);
    SPRINTF_RX_COUNTER(RX_FORMAT_ERR_DROP_COUNT);
    SPRINTF_RX_COUNTER(RX_ICV_ERR_DROP_COUNT);
    SPRINTF_RX_COUNTER(RX_KEY_ERR_DROP_COUNT);
    SPRINTF_RX_COUNTER(RX_TKIP_ERR_DROP_COUNT);

    SPRINTF_RX_COUNTER(RX_RETRY_FRAME_COUNT);
    SPRINTF_RX_COUNTER(RX_DUPLICATE_DROP_COUNT);

    SPRINTF_RX_COUNTER(RX_DATA_CLASS_ERR_DROP_COUNT);
    SPRINTF_RX_COUNTER(RX_DATA_PORT_CTRL_DROP_COUNT);

    SPRINTF_RX_COUNTER(RX_DATA_INDICATION_COUNT);

#if CFG_TCP_IP_CHKSUM_OFFLOAD
    SPRINTF_RX_COUNTER(RX_CSUM_TCP_FAILED_COUNT);
    SPRINTF_RX_COUNTER(RX_CSUM_UDP_FAILED_COUNT);
    SPRINTF_RX_COUNTER(RX_CSUM_IP_FAILED_COUNT);
    SPRINTF_RX_COUNTER(RX_CSUM_TCP_SUCCESS_COUNT);
    SPRINTF_RX_COUNTER(RX_CSUM_UDP_SUCCESS_COUNT);
    SPRINTF_RX_COUNTER(RX_CSUM_IP_SUCCESS_COUNT);
    SPRINTF_RX_COUNTER(RX_CSUM_UNKNOWN_L4_PKT_COUNT);
    SPRINTF_RX_COUNTER(RX_CSUM_UNKNOWN_L3_PKT_COUNT);
    SPRINTF_RX_COUNTER(RX_IP_V6_PKT_CCOUNT);
#endif

    SPRINTF_RX_COUNTER(RX_MSDU_BYTES_COUNT);

    *pu4Count = (UINT_32)((UINT_32)pucCurrBuf - (UINT_32)pucBuffer);

    return;
} /* end of nicRxQueryStatistics() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function is used to clear statistics of RX Module.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
nicRxSetStatistics (
    IN P_ADAPTER_T prAdapter
    )
{
    P_RX_CTRL_T prRxCtrl;


    ASSERT(prAdapter);
    prRxCtrl = &prAdapter->rRxCtrl;

    RX_RESET_ALL_CNTS(prRxCtrl);

    return;
} /* end of nicRxSetStatistics() */


#if CFG_TCP_IP_CHKSUM_OFFLOAD
/*----------------------------------------------------------------------------*/
/*!
* \brief This function is used to update IP/TCP/UDP checksum statistics of RX Module.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
* \param[in] aeCSUM     The array of checksum result.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
nicRxUpdateCSUMStatistics (
    IN P_ADAPTER_T prAdapter,
    IN ENUM_CSUM_RESULT_T aeCSUM[]
    )
{
    P_RX_CTRL_T prRxCtrl;


    ASSERT(prAdapter);
    ASSERT(aeCSUM);
    prRxCtrl = &prAdapter->rRxCtrl;

    if ((aeCSUM[CSUM_TYPE_IPV4] == CSUM_RES_SUCCESS) ||
        (aeCSUM[CSUM_TYPE_IPV6] == CSUM_RES_SUCCESS)) {

        RX_INC_CNT(prRxCtrl, RX_CSUM_IP_SUCCESS_COUNT);
    }
    else if ((aeCSUM[CSUM_TYPE_IPV4] == CSUM_RES_FAILED) ||
             (aeCSUM[CSUM_TYPE_IPV6] == CSUM_RES_FAILED)) {

        RX_INC_CNT(prRxCtrl, RX_CSUM_IP_FAILED_COUNT);
    }
    else if ((aeCSUM[CSUM_TYPE_IPV4] == CSUM_RES_NONE) &&
             (aeCSUM[CSUM_TYPE_IPV6] == CSUM_RES_NONE)) {

        RX_INC_CNT(prRxCtrl, RX_CSUM_UNKNOWN_L3_PKT_COUNT);
    }
    else {
        ASSERT(0);
    }

    if (aeCSUM[CSUM_TYPE_TCP] == CSUM_RES_SUCCESS) {
        RX_INC_CNT(prRxCtrl, RX_CSUM_TCP_SUCCESS_COUNT);
    }
    else if (aeCSUM[CSUM_TYPE_TCP] == CSUM_RES_FAILED) {
        RX_INC_CNT(prRxCtrl, RX_CSUM_TCP_FAILED_COUNT);
    }
    else if (aeCSUM[CSUM_TYPE_UDP] == CSUM_RES_SUCCESS) {
        RX_INC_CNT(prRxCtrl, RX_CSUM_UDP_SUCCESS_COUNT);
    }
    else if (aeCSUM[CSUM_TYPE_UDP] == CSUM_RES_FAILED) {
        RX_INC_CNT(prRxCtrl, RX_CSUM_UDP_FAILED_COUNT);
    }
    else if ((aeCSUM[CSUM_TYPE_UDP] == CSUM_RES_NONE) &&
             (aeCSUM[CSUM_TYPE_TCP] == CSUM_RES_NONE)) {

        RX_INC_CNT(prRxCtrl, RX_CSUM_UNKNOWN_L4_PKT_COUNT);
    }
    else {
        ASSERT(0);
    }

    return;
} /* end of nicRxUpdateCSUMStatistics() */
#endif /* CFG_TCP_IP_CHKSUM_OFFLOAD */


/*----------------------------------------------------------------------------*/
/*!
* \brief Set filter to enable Promiscuous Mode
*
* \param[in] prAdapter          Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
nicRxEnablePromiscuousMode (
    IN P_ADAPTER_T prAdapter
    )
{
    P_RX_CTRL_T prRxCtrl;


    ASSERT(prAdapter);
    prRxCtrl = &prAdapter->rRxCtrl;

    if (!prRxCtrl->fgEnablePromiscuousMode) {
        nicRxFlushStopQueue(prAdapter, TRUE, TRUE);
        nicTxFlushStopQueues(prAdapter, TXQ_DATA_MASK | TXQ_MGMT_MASK, TXQ_DATA_MASK | TXQ_MGMT_MASK);
        halSetRxHeaderTranslation(prAdapter, FALSE);
        NIC_SET_RX_FILTER(prAdapter, RXFILTER_RXPROMISCUOUSFRAME);
        prRxCtrl->fgEnablePromiscuousMode = TRUE;
        nicRxStartQueue(prAdapter);
    }

    return;
} /* end of nicRxEnablePromiscuousMode() */


/*----------------------------------------------------------------------------*/
/*!
* \brief Set filter to disable Promiscuous Mode
*
* \param[in] prAdapter          Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
nicRxDisablePromiscuousMode (
    IN P_ADAPTER_T prAdapter
    )
{
    P_RX_CTRL_T prRxCtrl;


    ASSERT(prAdapter);
    prRxCtrl = &prAdapter->rRxCtrl;

    if (prRxCtrl->fgEnablePromiscuousMode) {
        nicRxFlushStopQueue(prAdapter, TRUE, TRUE);

        NIC_UNSET_RX_FILTER(prAdapter, RXFILTER_RXPROMISCUOUSFRAME);
        halSetRxHeaderTranslation(prAdapter, TRUE);

        prRxCtrl->fgEnablePromiscuousMode = FALSE;

        nicRxStartQueue(prAdapter);
    }

    return;
} /* end of nicRxDisablePromiscuousMode() */


/*----------------------------------------------------------------------------*/
/*!
* \brief Set multicast MAC Addresses from given list according current MC rule.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
* \param[in] eMCType        Given MC rule.
* \param[in] prMCAddrList   Pointer to the Multicast Address List.
* \param[in] ucNum          Number of Multicast Addresses.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
nicRxSetMulticast (
    IN P_ADAPTER_T prAdapter,
    IN ENUM_RX_MULTICAST_TYPE_T eMCType,
    IN PUINT_8 prMCAddrList,
    IN UINT_8 ucNum
    )
{
    P_RX_CTRL_T prRxCtrl;


    ASSERT(prAdapter);
    prRxCtrl = &prAdapter->rRxCtrl;

    if (ucNum > 0) {
        ASSERT(prMCAddrList);
    }

    switch (eMCType) {
    case MC_TYPE_DENY_ALL:
        prRxCtrl->fgRxMulticastPkt = FALSE;
        prRxCtrl->fgRxMulticastPktByTable = FALSE;
        NIC_UNSET_RX_FILTER(prAdapter, RXFILTER_RXMCFRAME);
        nicSetMulticastAddrList(prAdapter, (PUINT_8)NULL, 0);
        break;

    case MC_TYPE_ALLOW_LIST:
        prRxCtrl->fgRxMulticastPkt = TRUE;
        NIC_SET_RX_FILTER(prAdapter, RXFILTER_RXMCFRAME);
        prRxCtrl->fgRxMulticastPktByTable = TRUE;
        NIC_UNSET_RX_FILTER(prAdapter, RXFILTER_MCTABLENOCHK);
        break;

    case MC_TYPE_ALLOW_ALL:
        prRxCtrl->fgRxMulticastPkt = TRUE;
        NIC_SET_RX_FILTER(prAdapter, RXFILTER_RXMCFRAME);
        prRxCtrl->fgRxMulticastPktByTable = FALSE;
        NIC_SET_RX_FILTER(prAdapter, RXFILTER_MCTABLENOCHK);
        /* We still have Multicast Address List */
        break;

    case MC_TYPE_UPDATE_LIST_ONLY:
        nicSetMulticastAddrList(prAdapter, prMCAddrList, ucNum);
        break;

    default:
        break;
    }

    return;
} /* end of nicRxSetMulticast() */


/*----------------------------------------------------------------------------*/
/*!
* \brief Set filter to enable receiving broadcast frame.
*
* \param[in] prAdapter          Pointer to the Adapter structure.
* \param[in] fgEnableBroadcast  Set TRUE to enable Broadcast Frame.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
nicRxSetBroadcast (
    IN P_ADAPTER_T prAdapter,
    IN BOOLEAN fgEnableBroadcast
    )
{
    ASSERT(prAdapter);

    if (fgEnableBroadcast) {
        NIC_SET_RX_FILTER(prAdapter, RXFILTER_RXBCFRAME);
    }
    else {
        NIC_UNSET_RX_FILTER(prAdapter, RXFILTER_RXBCFRAME);
    }

    return;
} /* end of nicRxSetBroadcast() */


