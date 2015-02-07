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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/rftest.c#2 $
*/

/*! \file   "rftest.c"
    \brief  This file contains the RF test routines

    This file contains the RF test routines.
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
** $Log: rftest.c $
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\28 2009-09-30 23:06:14 GMT mtk01090
**  Remove redundant initialization. Correct log message.
**  \main\maintrunk.MT5921\27 2009-09-30 15:31:27 GMT mtk01104
**  Not zero pucTxCached when initialize rRFTestInfo
**  \main\maintrunk.MT5921\26 2009-05-14 20:41:23 GMT mtk01104
**  In rftestUnInit(), EEPROM shall be reloaded before reading
**  \main\maintrunk.MT5921\25 2009-01-19 11:51:15 GMT mtk01725
**  If rftest tx cached has been allocated, skip the allocation.
**  \main\maintrunk.MT5921\24 2009-01-19 11:45:40 GMT mtk01725
**  \main\maintrunk.MT5921\23 2008-12-08 21:29:37 GMT mtk01461
**  Remove Lint warning - out-of-bounds pointer
**  \main\maintrunk.MT5921\22 2008-12-01 18:18:12 GMT mtk01088
**  fixed the lint "possible using null pointer" warning
**  \main\maintrunk.MT5921\21 2008-10-13 02:09:16 GMT mtk01461
**  Fix compile warning for ADS v1.2 build env
**  \main\maintrunk.MT5921\20 2008-08-25 23:08:18 GMT mtk01104
**  Add comments to all functions
**  \main\maintrunk.MT5921\19 2008-07-01 10:55:35 GMT mtk01425
**  1. Add rftest assertion
**  2. Make the rftest layer correct
**  \main\maintrunk.MT5921\18 2008-05-26 13:27:20 GMT mtk01385
**  1. move reload EEPROM action from rftestInit() to rftestUninit().
**  \main\maintrunk.MT5921\17 2008-04-20 11:16:55 GMT mtk01385
**  1. fix RFCR_9 write issue for thermo control.
**  2. fix compiling warning.
**  \main\maintrunk.MT5921\16 2008-04-11 00:04:08 GMT mtk01385
**  1. add update BB/RF Rx setting based on thermo info function.
**  2. remove ALC trigger action while TxDone or RxDone.
**  \main\maintrunk.MT5921\15 2008-03-28 14:23:35 GMT mtk01385
**  1. fix ALC algorithm init error.
**  \main\maintrunk.MT5921\14 2008-03-12 09:52:16 GMT mtk01461
**  Remove type case in MSDU_INFO_OBJ_INIT
**
**  \main\maintrunk.MT5921\13 2008-02-01 13:34:06 GMT mtk01385
**  1. Will not do ALC trigger while Thermo Timer and Fake Thermo Value is enable.
**  2. Use Thermo Init/UnInit function instead ALC EN/Disable function.
**  3. Reload eeprom setting when enter rftest mode.
**  4. fix 64 bit printf issue on Winodws.
**  \main\maintrunk.MT5921\12 2008-02-01 09:50:18 GMT mtk01385
**  1. Fix WinCE 4.2 compiling error.
**  \main\maintrunk.MT5921\11 2008-01-31 17:49:11 GMT mtk01385
**  1. addThermo Init function init in Tx/Rx mode.
**  2.  ignore Tx power gain config when ALC is enabled.
**  \main\maintrunk.MT5921\10 2008-01-05 19:26:04 GMT mtk01385
**  1. fix -  Rf test Tx mode will no return back to No Tx/ No Rx mode if it is stopped when TxDone count equal to target tx packet count.
**
**  \main\maintrunk.MT5921\9 2007-12-29 16:42:33 GMT mtk01385
**  1. add ALC control to RFtestTx process function.
**  2.                   MACTX    MACRX
**    RF test init:        X             X
**    RF TX:                V             V
**    RF RX:                X             V
**  \main\maintrunk.MT5921\8 2007-12-26 14:15:16 GMT mtk01385
**  1. Fix rftest mode display rx packet count issue.
**  \main\maintrunk.MT5921\7 2007-12-04 18:09:40 GMT mtk01461
**  Update MSDU_INFO_T init process
**  \main\maintrunk.MT5921\6 2007-11-30 21:18:55 GMT mtk01385
**  1. fix bug : add counter at DBGLOG().
**  \main\maintrunk.MT5921\5 2007-11-30 16:44:39 GMT mtk01425
**  1. Fix compiling warnings
**  \main\maintrunk.MT5921\4 2007-11-29 16:27:06 GMT mtk01385
**  1. fix bug : add counter at DBGLOG().
**  \main\maintrunk.MT5921\3 2007-11-26 21:48:14 GMT mtk01385
**  1. call the h/w mib counter peek function provided by statistics module.
**  2. Cancel statistics timer when enter RF test mode.
**  \main\maintrunk.MT5921\2 2007-11-20 14:27:24 GMT mtk01385
**  1. %f can not be used in Linux and Big Windows.
**  \main\maintrunk.MT5921\1 2007-11-19 10:20:54 GMT mtk01385
**  Init version.
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
const UINT_8 aucRftestDefPktCont[] = {
        0x08, //Data
        0x02,
        0x00,
        0x00,
        0xFF, //DA
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0x00, //SA
        0x0C,
        0xE7,
        0x59,
        0x21,
        0x01,
        0x00, //BSSID
        0x0C,
        0xE7,
        0x59,
        0x21,
        0x01,
        0x00,
        0x00
    };

const UINT_8 aucRftestRateMapTable[] = {
        RATE_CCK_1M_LONG, //RF_AT_PARAM_RATE_1M
        RATE_CCK_2M_LONG, //RF_AT_PARAM_RATE_2M
        RATE_CCK_5_5M_LONG, //RF_AT_PARAM_RATE_5_5M
        RATE_CCK_11M_LONG, //RF_AT_PARAM_RATE_11M
        RATE_OFDM_6M, //RF_AT_PARAM_RATE_6M
        RATE_OFDM_9M, //RF_AT_PARAM_RATE_9M
        RATE_OFDM_12M, //RF_AT_PARAM_RATE_12M
        RATE_OFDM_18M, //RF_AT_PARAM_RATE_18M
        RATE_OFDM_24M, //RF_AT_PARAM_RATE_24M
        RATE_OFDM_36M, //RF_AT_PARAM_RATE_36M
        RATE_OFDM_48M, //RF_AT_PARAM_RATE_48M
        RATE_OFDM_54M  //RF_AT_PARAM_RATE_54M
    };

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

#define RFTEST_ALLOCATE_MEMORY(pucMem, u4Size, pucComment) \
        { \
            DBGLOG(INIT, INFO, ("Allocating %ld bytes for %s.\n", u4Size, pucComment)); \
            if ((pucMem = (PUINT_8)kalMemAlloc(u4Size)) == (PUINT_8)NULL) { \
                DBGLOG(RFTEST, ERROR, ("Could not allocate %ld bytes for %s.\n", u4Size, pucComment)); \
                break; \
            } \
            ASSERT(((UINT_32)pucMem % 4) == 0); \
            DBGLOG(RFTEST, INFO, ("Virtual Address = %08lx for %s.\n", (UINT_32)pucMem, pucComment)); \
            kalMemZero((PVOID) pucMem, u4Size); \
        }


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
* \brief Allocate Frame Buffer Descriptor for Test Frame
*
* \param[in] prAdapter      Pointer of Adapter Data Structure
*
* \return Pointer of Buffer Descriptor
*/
/*----------------------------------------------------------------------------*/
P_RFTEST_TXBUF_T
rftestBufAllocateRFTestBuf (
    IN P_ADAPTER_T prAdapter
    )
{
    P_RFTEST_TXBUF_T            prTxBufEntry;
    P_QUE_T                     prTxBufQue;


    DEBUGFUNC("rftestBufAllocateRFTestBuf");

    ASSERT(prAdapter);

    prTxBufQue = &prAdapter->rRFTestInfo.rTxBufFreeQueue;

    QUEUE_REMOVE_HEAD(prTxBufQue, prTxBufEntry, P_RFTEST_TXBUF_T);

    return prTxBufEntry;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This function will return buffer descriptor to free queue
*
* \param[in] prAdapter      Pointer of Adapter Data Structure
*
* \return none
*/
/*----------------------------------------------------------------------------*/
VOID
rftestBufFreeRFTestBuf (
    IN P_ADAPTER_T      prAdapter,
    IN P_RFTEST_TXBUF_T prTxBufEntry
    )
{
    P_QUE_T                     prTxBufQue;


    DEBUGFUNC("rftestBufFreeRFTestBuf");

    ASSERT(prAdapter);
    ASSERT(prTxBufEntry);


    prTxBufQue = &prAdapter->rRFTestInfo.rTxBufFreeQueue;

    if (prTxBufEntry) {
        QUEUE_INSERT_TAIL(prTxBufQue, &prTxBufEntry->rQueEntry);
    }

    return;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief Calculate TX done count of RF test mode
*
* \param[in] prAdapter      Pointer of Adapter Data Structure
*
* \return none
*/
/*----------------------------------------------------------------------------*/
VOID
rftestProcessTxDone (
    IN P_ADAPTER_T prAdapter,
    IN P_MSDU_INFO_T prMsduInfo,
    IN WLAN_STATUS rStatus
    )
{
    P_RFTEST_STATUS_STRUC_T     prStatus;
    P_RFTEST_INFO_T             prRfTestInfo;
    P_RFTEST_SETTING_STRUC_T    prSetting;

    DEBUGFUNC("rftestProcessTxDone");

    ASSERT(prAdapter);

    prRfTestInfo = &prAdapter->rRFTestInfo;
    prStatus = &prRfTestInfo->rStatus;
    prSetting = &prRfTestInfo->rSetting;
    if (prRfTestInfo->eCurrentState == RF_AUTOTEST_STATE_TX) {
        prStatus->u4TxDoneCnt++;

        DBGLOG(RFTEST, INFO, ("Get TxDone %ld.\n", prStatus->u4TxDoneCnt));
    }
    else {
        DBGLOG(RFTEST, ERROR, ("Get TxDone when in non Tx State\n"));
    }
}

/*----------------------------------------------------------------------------*/
/*!
* \brief A routine for RF test mode to send more packets to HW queue
*
* \param[in] prAdapter      Pointer of Adapter Data Structure
*
* \retvalue WLAN_STATUS_SUCCESS   success
* \retvalue WLAN_STATUS_RESOURCES msdu_info or frame buffer is not available
* \retvalue WLAN_STATUS_FAILURE   fail to send some one packet
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
rftestSendTxFrames (
    IN P_ADAPTER_T prAdapter
    )
{
    P_MSDU_INFO_T               prMsduInfo;
    P_RFTEST_INFO_T             prRfTestInfo;
    P_RFTEST_SETTING_STRUC_T    prSetting;
    P_RFTEST_STATUS_STRUC_T     prStatus;
    P_RFTEST_TXBUF_T            prTxBufEntry;
    P_QUE_T                     prTxBufQue;
    UINT_32                     u4WlanHeaderLen;
    UINT_32                     u4WlanBodyLen;
    UINT_8                      ucTmpControlFlag;
    PUINT_8                     pucBuffer;
    UINT_32                     u4PacketLen;
    WLAN_STATUS                 rStatus = WLAN_STATUS_SUCCESS;


    DEBUGFUNC("rftestSendTxFrames");

    ASSERT(prAdapter);
    prRfTestInfo = &prAdapter->rRFTestInfo;
    prSetting = &prRfTestInfo->rSetting;
    prStatus =  &prRfTestInfo->rStatus;
    prTxBufQue = &prRfTestInfo->rTxBufFreeQueue;


    while ( (prStatus->u4TxedPacketCnt < prSetting->u4PacketCnt) || \
        (prSetting->u4PacketCnt == RF_AT_PARAM_PACKET_UNLIMITED) ) {
        /* Attempt to allocate a buffer to compose a Tx frame. */

        //4 <1> Allocate MSDU_INFO_T
        prMsduInfo = nicTxAllocMsduInfo(prAdapter, prSetting->ucTxQue);
        if (prMsduInfo == (P_MSDU_INFO_T)NULL) {
            DBGLOG(RFTEST, WARN, ("Not enough buffers to send Packet\n"));
            return WLAN_STATUS_RESOURCES;
        }

        //4 <2> Allocate Frame Buffer Descriptor for Test Frame
        prTxBufEntry = rftestBufAllocateRFTestBuf(prAdapter);
        if (prTxBufEntry == (P_RFTEST_TXBUF_T)NULL) {
            nicTxReturnMsduInfo(prAdapter, prMsduInfo);
            DBGLOG(RFTEST, ERROR, ("Not enough RF Test buffers to send Packet\n"));
            return WLAN_STATUS_RESOURCES;
        }

        if (prSetting->u4PacketLen > RF_AT_PARAM_TX_PKTLEN_BYTE_MAX) {
            u4PacketLen = RF_AT_PARAM_TX_PKTLEN_BYTE_MAX;
        }
        else {
            u4PacketLen = prSetting->u4PacketLen;
        }

        pucBuffer = &prTxBufEntry->aucData[0];

/*lint -save -e416 creation of out-of-bounds pointer ('12' beyond end of data) */
        kalMemCopy(&pucBuffer[TFCB_SIZE],
                    prSetting->aucPktContent,
                    u4PacketLen);
/*lint -restore */

#if 0 // NOTE(Kevin): Following code will have out-of-bound warning ! in ADS v1.2
        kalMemCopy(&prTxBufEntry->aucData[TFCB_SIZE], prSetting->aucPktContent,
                        prSetting->u4PacketLen);
#endif

        //4 <5> Update information in MSDU_INFO_T for TX Module.
        /*ToDo: how to check header length*/
        u4WlanHeaderLen = RF_AT_PARAM_TX_80211HDR_BYTE_DEFAULT; /*cannot be 0, this setting is not valid for SEC */
        ASSERT(u4PacketLen > u4WlanHeaderLen);
        u4WlanBodyLen = u4PacketLen - u4WlanHeaderLen ;
        ucTmpControlFlag = MSDU_INFO_CTRL_FLAG_SPECIFY_AC | MSDU_INFO_CTRL_FLAG_LIFETIME_NEVER_EXPIRE;
        if (prSetting->eAckPolicy == RF_AT_ACK_POLICY_NOACK) {
            ucTmpControlFlag |= MSDU_INFO_CTRL_FLAG_NO_ACK;
            DBGLOG(RFTEST, LOUD, ("ACK policy MSDU_INFO_CTRL_FLAG_NO_ACK set to MSDU_INFO\n"));
        }
        else {
            DBGLOG(RFTEST, LOUD, ("ACK policy Normal ACK set to MSDU_INFO\n"));
        }


        MSDU_INFO_OBJ_INIT(prMsduInfo, \
                           TRUE, \
                           FALSE, \
                           (PVOID)prTxBufEntry, \
                           0, \
                           prSetting->ucTxQue, \
                           (UINT_8)u4WlanHeaderLen, \
                           (UINT_16)u4WlanBodyLen, \
                           ucTmpControlFlag, \
                           rftestProcessTxDone, \
                           (OS_SYSTIME) 0, \
                           NULL \
                           );


        //4 <6> Inform ARB to send this frame.
        if ((rStatus = arbFsmRunEventTxMmpdu(prAdapter, prMsduInfo)) != WLAN_STATUS_PENDING) {

            rftestBufFreeRFTestBuf(prAdapter, prTxBufEntry);

            nicTxReturnMsduInfo(prAdapter, prMsduInfo);

            rStatus = WLAN_STATUS_FAILURE;

            break; /* Break the outer WHILE statement once we encounter ERROR. */
        }

        prStatus->u4TxedPacketCnt++;
	kalUdelay(1000);	
        DBGLOG(RFTEST, INFO, ("Pakcet send to s/w queue = %ld\n",
            prStatus->u4TxedPacketCnt));
    }

    return rStatus;
}   /* scanSendProbeReqFrames */

/*----------------------------------------------------------------------------*/
/*!
* \brief Based TX configuration, set adequate parameters to HW
*
* \param[in] prAdapter      Pointer of Adapter Data Structure
*
* \retvalue WLAN_STATUS_SUCCESS      success
* \retvalue WLAN_STATUS_INVALID_DATA wrong TXOP Queue or fail to set wlan table
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
rftestUpdateTxConfigToHw (
    IN P_ADAPTER_T prAdapter
    )
{
    P_RFTEST_INFO_T             prRfTestInfo;
    P_RFTEST_SETTING_STRUC_T    prSetting;
    P_RFTEST_STATUS_STRUC_T     prStatus;

    WT_CTRL_STRUC_T             rWTCtrl;
    SW_KEY_STRUC_T              rSwKey;
    WLAN_STATUS                 rStatus = WLAN_STATUS_SUCCESS;

    DEBUGFUNC("rftestUpdateTxConfigToHw");

    ASSERT(prAdapter);
    prRfTestInfo = &prAdapter->rRFTestInfo;
    prSetting = &prRfTestInfo->rSetting;
    prStatus =  &prRfTestInfo->rStatus;

    //4 <1> TxPowerGain
    do {
	    if (prSetting->fgALCEn == TRUE) {
	        DBGLOG(RFTEST, TRACE, ("ALC function is enabled. Tx power gain parameter is ignored\n"));
	        break;
	    }
	    switch(prSetting->ucTxRate) {
	    case RF_AT_PARAM_RATE_48M:
	    case RF_AT_PARAM_RATE_54M:
	        RFTEST_SET_TX_POWER_GAIN(prAdapter, \
	            MCR_OFPR, prSetting->ucTxPowerGain,\
	            OFPR_48_54_FRAME_POWER_MASK , OFPR_48_54_FRAME_POWER_STARTBIT);
	        break;

	    case RF_AT_PARAM_RATE_36M:
	    case RF_AT_PARAM_RATE_24M:
	        RFTEST_SET_TX_POWER_GAIN(prAdapter, \
	            MCR_OFPR, prSetting->ucTxPowerGain,\
	            OFPR_24_36_FRAME_POWER_MASK , OFPR_24_36_FRAME_POWER_STARTBIT);
	        break;

	    case RF_AT_PARAM_RATE_18M:
	    case RF_AT_PARAM_RATE_12M:
	        RFTEST_SET_TX_POWER_GAIN(prAdapter, \
	            MCR_OFPR, prSetting->ucTxPowerGain,\
	            OFPR_12_18_FRAME_POWER_MASK , OFPR_12_18_FRAME_POWER_STARTBIT);
	        break;

	    case RF_AT_PARAM_RATE_9M:
	    case RF_AT_PARAM_RATE_6M:
	        RFTEST_SET_TX_POWER_GAIN(prAdapter, \
	            MCR_OFPR, prSetting->ucTxPowerGain,\
	            OFPR_6_9_FRAME_POWER_MASK , OFPR_6_9_FRAME_POWER_STARTBIT);
	        break;
	    case RF_AT_PARAM_RATE_11M:
	    case RF_AT_PARAM_RATE_5_5M:
	    case RF_AT_PARAM_RATE_2M:
	    case RF_AT_PARAM_RATE_1M:
	        RFTEST_SET_TX_POWER_GAIN(prAdapter, \
	            MCR_CFPR, prSetting->ucTxPowerGain,\
	            CFPR_FRAME_POWER_MASK , CFPR_FRAME_POWER_STARTBIT);
	        break;
	    default:
	        DBGLOG(RFTEST, ERROR, ("TxRate Index %d is not supported. Can not set Tx Power Gain\n",
	            prSetting->ucTxRate));
	        return WLAN_STATUS_INVALID_DATA;
	    }
    } while (FALSE);

    //4 <2> Retry limit
    HAL_MCR_WR(prAdapter, MCR_MTCLR, MTCLR_DISABLE_ALL_RATES);
    RFTEST_SET_TX_CNT_LIMIT(prAdapter, MCR_MTCLR, prSetting->ucRetryLimit+1,\
            MTCLR_RATE1_MASK, MTCLR_RATE1_OFFSET);

    //4 <3> TXOP
    switch((prSetting->u4QueTxop & RF_AT_PARAM_TXOPQUE_QMASK)) {
    case RF_AT_PARAM_TXOPQUE_AC0:
        RFTEST_SET_TXOP_LIMIT(prAdapter, \
            MCR_ACTXOPLR0, (prSetting->u4QueTxop & RF_AT_PARAM_TXOPQUE_TMASK),\
            ACTXOPLR0_AC0_LIMIT_MASK , ACTXOPLR0_AC0_LIMIT_OFFSET);
        break;

    case RF_AT_PARAM_TXOPQUE_AC1:
        RFTEST_SET_TXOP_LIMIT(prAdapter, \
            MCR_ACTXOPLR0, (prSetting->u4QueTxop & RF_AT_PARAM_TXOPQUE_TMASK),\
            ACTXOPLR0_AC1_LIMIT_MASK , ACTXOPLR0_AC1_LIMIT_OFFSET);
        break;


    case RF_AT_PARAM_TXOPQUE_AC2:
        RFTEST_SET_TXOP_LIMIT(prAdapter, \
            MCR_ACTXOPLR1, (prSetting->u4QueTxop & RF_AT_PARAM_TXOPQUE_TMASK),\
            ACTXOPLR1_AC2_LIMIT_MASK , ACTXOPLR1_AC2_LIMIT_OFFSET);
        break;

    case RF_AT_PARAM_TXOPQUE_AC3:
        RFTEST_SET_TXOP_LIMIT(prAdapter, \
            MCR_ACTXOPLR1, (prSetting->u4QueTxop & RF_AT_PARAM_TXOPQUE_TMASK),\
            ACTXOPLR1_AC3_LIMIT_MASK , ACTXOPLR1_AC3_LIMIT_OFFSET);
        break;
    default:
        DBGLOG(RFTEST, ERROR, ("Queue Index %ld is not supported. Can not set TXOP limit.\n",
            (prSetting->u4QueTxop & RF_AT_PARAM_TXOPQUE_QMASK)>>RF_AT_PARAM_TXOPQUE_QOFFSET));
        return WLAN_STATUS_INVALID_DATA;
    }

    //4 <4> TxRate, Preamble,Tx Antenna    /*Init Wlan Table*/

    nicPrivacyInitialize(prAdapter);
    kalMemZero(&rWTCtrl, sizeof(WT_CTRL_STRUC_T));
    kalMemZero(&rSwKey, sizeof(SW_KEY_STRUC_T));

    rWTCtrl.fgTV = TRUE;
    rWTCtrl.fgRV = TRUE;
    rWTCtrl.fgAntenna = (BOOLEAN)prSetting->ucAntenna;
    rWTCtrl.ucRate1 = aucRftestRateMapTable[prSetting->ucTxRate];
    if (prSetting->ucTxRate <= RF_AT_PARAM_RATE_11M) {
        if (prSetting->ePreamble == RF_AT_PREAMBLE_CCK_SHORT) {
             rWTCtrl.ucRate1 |= RATE_CCK_SHORT_PREAMBLE;
        }
    }

    if ( nicPrivacySetWlanTable( prAdapter, 0, NULL, &rWTCtrl, &rSwKey) == FALSE){

        DBGLOG(RFTEST, ERROR, ("Set Wlan Table failed.\n"));
        return WLAN_STATUS_INVALID_DATA;
    }

    //4 <5> ALC, u4PacketIntervalUs
    if (prSetting->fgALCEn) {
        DBGLOG(RFTEST, TRACE, ("ALC function is enabled. call Thermo Init\n"));
        nicThermoInit(prAdapter);
        rftestAdoptBbRfByThermo( prAdapter);
    }
    else {
        nicThermoUnInit(prAdapter);
    }
    //4 <6> TxQueue, AckPolicy in msduinfo, no need


    /*Enable MAC Tx/Rx*/
    NIC_MAC_TX_RX_CONTROL(prAdapter, TRUE, TRUE);

    /*Start tx Queue*/
    nicTxStartQueues(prAdapter, (UINT_8) BIT(prSetting->ucTxQue));

    return rStatus;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief Routine to process RF test TX packets function. It should be invoked
*        when initialize TX packet testing and TX done.
*
* \param[in] prAdapter      Pointer of Adapter Data Structure
*
* \return none
*/
/*----------------------------------------------------------------------------*/
VOID
rftestTx (
    IN P_ADAPTER_T prAdapter
    )
{
    P_RFTEST_INFO_T             prRfTestInfo;
    P_RFTEST_STATUS_STRUC_T     prStatus;
    P_RFTEST_SETTING_STRUC_T    prSetting;

    DEBUGFUNC("rftestTx");

    ASSERT(prAdapter);

    prRfTestInfo= &prAdapter->rRFTestInfo;
    prStatus = &prRfTestInfo->rStatus;
    prSetting = &prRfTestInfo->rSetting;

    if (prRfTestInfo->eCurrentState == RF_AUTOTEST_STATE_STANDBY) {
        DBGLOG(RFTEST, WARN, ("Enter this function while in RF_AUTOTEST_STATE_STANDBY state.\n"));
        return;
    }
    else if (prSetting->u4PacketCnt == RF_AT_PARAM_PACKET_UNLIMITED){
        /*Check tx complete or not*/
        rftestSendTxFrames(prAdapter);
    }
    else if (prStatus->u4TxDoneCnt == prSetting->u4PacketCnt) {
        prStatus->u4TxDoneCnt = 0;
        prRfTestInfo->eCurrentState = RF_AUTOTEST_STATE_STANDBY;
        nicTxFlushStopQueues(prAdapter, (UINT_8)BIT(prSetting->ucTxQue), (UINT_8)BIT(prSetting->ucTxQue));
        /*Change FSM state*/
        //prAdapter->rTxCtrl.fgIsRfTestTxMode = FALSE;
        /*Stop MAC Tx/Rx*/
        NIC_MAC_TX_RX_CONTROL(prAdapter, FALSE, FALSE);
        /*Stop ALC*/
        nicThermoUnInit(prAdapter);
    }
    else if (prStatus->u4TxedPacketCnt == prSetting->u4PacketCnt) {
          DBGLOG(RFTEST, INFO, ("There are %ld TxDone do not comeback.\n",\
              prSetting->u4PacketCnt - prStatus->u4TxDoneCnt));
    }
    else {
        rftestSendTxFrames(prAdapter);
    }

    return;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This function will do initialization of RF test Tx Mode and all
*        variables in RFTEST_INFO_T.
*
* \param[in] prAdapter      Pointer of Adapter Data Structure
*
* \return The result of the rftestInit
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
rftestTxModeInit (
    IN P_ADAPTER_T prAdapter
    )
{
    P_RFTEST_INFO_T             prRfTestInfo;
    P_RFTEST_STATUS_STRUC_T     prStatus;
    WLAN_STATUS                 rStatus ;

    DEBUGFUNC("rftestTxModeInit");

    ASSERT(prAdapter);

    prRfTestInfo= &prAdapter->rRFTestInfo;
    prStatus = &prRfTestInfo->rStatus;
    /*Init Variable buffer*/
    kalMemZero(prStatus, sizeof(RFTEST_STATUS_STRUC_T));

    /*rftestUpdateTxConfig*/
    rStatus = rftestUpdateTxConfigToHw(prAdapter);
    if (rStatus != WLAN_STATUS_SUCCESS) {
        DBGLOG(RFTEST, ERROR, ("rftestUpdateTxConfig return failed.\n"));
        return rStatus;
    }

    prRfTestInfo->eCurrentState = RF_AUTOTEST_STATE_TX;

    return rStatus;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This function stop Tx process of RF testing mode
*
* \param[in] prAdapter      Pointer of Adapter Data Structure
*
* \return none
*/
/*----------------------------------------------------------------------------*/
VOID
rftestTxStopTx (
    IN P_ADAPTER_T prAdapter
    )
{
    P_RFTEST_SETTING_STRUC_T    prSetting;
    P_RFTEST_STATUS_STRUC_T     prStatus;
    P_RFTEST_INFO_T             prRFATInfo;

    DEBUGFUNC("rftestTxStopTx");

    ASSERT(prAdapter);
    DBGLOG(RFTEST, TRACE, ("\n"));

    prRFATInfo = &prAdapter->rRFTestInfo;

    prSetting = &prAdapter->rRFTestInfo.rSetting;
    prStatus  = &prAdapter->rRFTestInfo.rStatus;

    /*Stop Tx, clear s/w h/w queue*/
    nicTxFlushStopQueues(prAdapter, (UINT_8)BIT(prSetting->ucTxQue), (UINT_8)BIT(prSetting->ucTxQue));

    DBGLOG(RFTEST, INFO, ("Pakcet send to SW queue = %ld, TxDone %ld come back\n",
        prStatus->u4TxedPacketCnt,prStatus->u4TxDoneCnt));

    /*Stop MAC Tx/Rx*/
    NIC_MAC_TX_RX_CONTROL(prAdapter, FALSE, FALSE);
    /*Stop ALC*/
    nicThermoUnInit(prAdapter);
    //4 2008/06/30, mikewu, moved for appropriate layer
    prAdapter->rTxCtrl.fgIsRfTestTxMode = FALSE;
    prRFATInfo->eCurrentState = RF_AUTOTEST_STATE_STANDBY;

    return;
}


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is responsible for the allocation of the data structures
*        inside the rftest structure, include:
*        1. Memory pool for RF test Tx.
*
* \param[in] prAdapter Pointer of Adapter Data Structure
*
* \retval WLAN_STATUS_SUCCESS - Has enough memory.
* \retval WLAN_STATUS_RESOURCES - Memory is not enough.
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
rftestAllocateMemory (
    IN P_ADAPTER_T prAdapter
    )
{
    P_RFTEST_INFO_T     prRfTestInfo;
    WLAN_STATUS         rStatus;

    DEBUGFUNC("rftestAllocateMemory");

    ASSERT(prAdapter);
    prRfTestInfo = &prAdapter->rRFTestInfo;

    if (prRfTestInfo->pucTxCached != (PUINT_8)NULL) {
        ASSERT(prRfTestInfo->u4TxCachedSize ==
                RF_AT_TX_BUFFER_NUM_MAX * RF_AT_TX_BUFFER_SIZE);
        return WLAN_STATUS_SUCCESS;
    }

    do {
        //4 <0> Reset all Memory Handler
        prRfTestInfo->pucTxCached = (PUINT_8)NULL;

        //4 <1> Memory for TX Buffer
        /* Allocate memory for the transmit data structures. */
        prRfTestInfo->u4TxCachedSize =
                RF_AT_TX_BUFFER_NUM_MAX * RF_AT_TX_BUFFER_SIZE;

        RFTEST_ALLOCATE_MEMORY(prRfTestInfo->pucTxCached,
                                  prRfTestInfo->u4TxCachedSize,
                                  "RFTEST TX BUFFER");
    } while (FALSE);

    rStatus = prRfTestInfo->pucTxCached ?
                WLAN_STATUS_SUCCESS : WLAN_STATUS_RESOURCES;

    return rStatus;
}   /* end of rftestAllocateMemory() */

/*----------------------------------------------------------------------------*/
/*!
* \brief Free RF Test Allocated Memory
*
* \param[in] prAdapter Pointer of Adapter Data Structure
*
* \return none
*/
/*----------------------------------------------------------------------------*/
VOID
rftestFreeMemory (
    IN P_ADAPTER_T prAdapter
    )
{

    P_RFTEST_INFO_T             prRfTestInfo;

    DEBUGFUNC("rftestFreeMemory");

    ASSERT(prAdapter);
    prRfTestInfo = &prAdapter->rRFTestInfo;
    DBGLOG(RFTEST, TRACE, ("\n"));

    if (!prRfTestInfo->pucTxCached) {
        DBGLOG(RFTEST, WARN, ("Buffer Pointer is NULL.\n"));
        return;
    }

    kalMemFree(prRfTestInfo->pucTxCached, prRfTestInfo->u4TxCachedSize);

    DBGLOG(RFTEST, INFO, ("Tx Memory Released\n"));
    return;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief Initialize the RFTEST Tx Frame Queue
*
* \param[in] prAdapter pointer to the Adapter handler
*
* \return none
*/
/*----------------------------------------------------------------------------*/
VOID
rftestTxInitialize (
    IN P_ADAPTER_T prAdapter
    )
{
    P_RFTEST_INFO_T             prRfTestInfo;
    PUINT_8                     pucMemHandle;
    P_RFTEST_TXBUF_T            prBufEntry;
    P_QUE_T                     prTxQue;
    UINT_32                     i;

    DEBUGFUNC("rftestTxInitialize");

    ASSERT(prAdapter);

    prRfTestInfo = &prAdapter->rRFTestInfo;
    prTxQue = &prRfTestInfo->rTxBufFreeQueue;

    QUEUE_INITIALIZE(prTxQue);
    pucMemHandle = prRfTestInfo->pucTxCached;
    for (i = 0; i < RF_AT_TX_BUFFER_NUM_MAX; i++) {
        prBufEntry = (P_RFTEST_TXBUF_T)pucMemHandle;

        QUEUE_INSERT_TAIL(prTxQue, &prBufEntry->rQueEntry)
        pucMemHandle += RF_AT_TX_BUFFER_SIZE;
    }

    /* Check if the memory allocation consist with this initialization function */
    ASSERT((UINT_32)(pucMemHandle - prRfTestInfo->pucTxCached) == prRfTestInfo->u4TxCachedSize);

}/* rftestTxInitialize */

/*----------------------------------------------------------------------------*/
/*!
* \brief This function will do initialization of RF test Rx Mode and all
*        variables in RFTEST_INFO_T.
*
* \param[in] prAdapter      Pointer of Adapter Data Structure
*
* \return The result of the rftestInit
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
rftestRxModeInit (
    IN P_ADAPTER_T prAdapter
    )
{
    P_RFTEST_INFO_T             prRfTestInfo;
    P_RFTEST_STATUS_STRUC_T     prStatus;

    DEBUGFUNC("rftestRxModeInit");
    ASSERT(prAdapter);

    prRfTestInfo= &prAdapter->rRFTestInfo;
    prStatus = &prRfTestInfo->rStatus;
    /*Init Variable buffer*/
    kalMemZero(prStatus, sizeof(P_RFTEST_STATUS_STRUC_T));

    /*Update G0,1,2 flag before start Queue*/
    rftestRxCheckHwConfig(prAdapter);

    /*rftestUpdateRxConfig*/
    rftestUpdateRxConfigToHw(prAdapter);

    prRfTestInfo->eCurrentState = RF_AUTOTEST_STATE_RX;

    return WLAN_STATUS_SUCCESS;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief For RX testing, set adequate parameters to HW
*
* \param[in] prAdapter      Pointer of Adapter Data Structure
*
* \return none
*/
/*----------------------------------------------------------------------------*/
VOID
rftestUpdateRxConfigToHw (
    IN P_ADAPTER_T prAdapter
    )
{
    P_RFTEST_INFO_T             prRfTestInfo;
    P_RFTEST_SETTING_STRUC_T    prSetting;
    P_RFTEST_STATUS_STRUC_T     prStatus;
    UINT_32                     u4McrTmp;

    DEBUGFUNC("rftestUpdateRxConfigToHw");

    ASSERT(prAdapter);
    prRfTestInfo = &prAdapter->rRFTestInfo;
    prSetting = &prRfTestInfo->rSetting;
    prStatus =  &prRfTestInfo->rStatus;

    //4 <1> RxQueue
    /*Start Rx Queue*/
    nicRxStartQueue(prAdapter);

    //4 <2> MIB counters
    u4McrTmp = MIBSCR_RX_FCS_ERROR_COUNT_EN | MIBSCR_CCATIME_EN\
            | MIBSCR_RX_FIFO_FULL_COUNT_EN | MIBSCR_RX_MPDU_COUNT_EN ;
    HAL_MCR_WR(prAdapter, MCR_MIBSCR, u4McrTmp);

    //4 <3> ALC
    if (prSetting->fgALCEn) {
        nicThermoInit(prAdapter);
        rftestAdoptBbRfByThermo( prAdapter);
    }
    else {
        nicThermoUnInit(prAdapter);
    }
    //4 <4> Enable MAC Tx/Rx
    NIC_MAC_TX_RX_CONTROL(prAdapter, FALSE, TRUE);

    return;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief Update G0,1,2 flag before start Queue
*
* \param[in] prAdapter      Pointer of Adapter Data Structure
*
* \return none
*/
/*----------------------------------------------------------------------------*/
VOID
rftestRxCheckHwConfig (
    IN P_ADAPTER_T prAdapter
    )
{
    P_RX_CTRL_T     prRxCtrl;

    DEBUGFUNC("rftestRxCheckHwConfig");

    ASSERT(prAdapter);

    prRxCtrl = &prAdapter->rRxCtrl;


    //4 <1> Rx Extension Field
    NIC_QUERY_RX_G0_EN(prAdapter, &prRxCtrl->fgIsRxStatusG0);
    NIC_QUERY_RX_G1_EN(prAdapter, &prRxCtrl->fgIsRxStatusG1);
    NIC_QUERY_RX_G2_EN(prAdapter, &prRxCtrl->fgIsRxStatusG2);
    NIC_QUERY_RX_G0_RSSI(prAdapter, &prRxCtrl->fgIsRxStatusG0Rssi);

    return;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief In RFTEST RX mode, any received packet (RFB) is processed
*        by this function.
*
* \param[in] prAdapter      Pointer of Adapter Data Structure
*
* \return none
*/
/*----------------------------------------------------------------------------*/
VOID
rftestProcessRxMPDU (
    IN P_ADAPTER_T prAdapter,
    IN OUT PP_SW_RFB_T pprSWRfb
    )
{
    P_RFTEST_STATUS_STRUC_T     prStatus;
    P_RFTEST_INFO_T             prRfTestInfo;
    P_RX_CTRL_T                 prRxCtrl;
    P_SW_RFB_T                  prSWRfb;
    P_RFTEST_SETTING_STRUC_T    prSetting;


    DEBUGFUNC("rftestProcessRxMPDU");

    ASSERT(prAdapter);
    ASSERT(pprSWRfb);

    prRfTestInfo = &prAdapter->rRFTestInfo;
    prStatus = &prRfTestInfo->rStatus;
    prSetting = &prRfTestInfo->rSetting;
    prRxCtrl = &prAdapter->rRxCtrl;
    prSWRfb = *pprSWRfb;

    if (prRfTestInfo->eCurrentState == RF_AUTOTEST_STATE_RX) {
        prStatus->u8RxedPacketCnt++;

#if defined(LINUX) || defined (WINDOWS_DDK)
        DBGLOG(RFTEST, INFO, ("Get Rx Packets %"DBG_PRINTF_64BIT_DEC". RCPI= %#02X,\n",\
             prStatus->u8RxedPacketCnt, \
             (prSWRfb->prRxStatus->ucRCPI)));
#else // WinCE
        DBGLOG(RFTEST, INFO, ("Get Rx Packets %"DBG_PRINTF_64BIT_DEC", RCPI= %fdBm,\n", \
	         prStatus->u8RxedPacketCnt,\
	         (prSWRfb->prRxStatus->ucRCPI/2.0 - 110)\
             ));
#endif
    }
    else {
        DBGLOG(RFTEST, ERROR, ("Get Rx Packets when in non Rx State\n"));
    }

    if (prRxCtrl->fgIsRxStatusG0) {
        DBGLOG(RFTEST, INFO, ("G0 TSF:%#08lx_%#08lx.\n", \
            prSWRfb->prG0->u4TimestampHigh, prSWRfb->prG0->u4TimestampLow));
    }

    if (prRxCtrl->fgIsRxStatusG1) {
        if (prRxCtrl->fgIsRxStatusG0Rssi) {
            DBGLOG(RFTEST, INFO, ("G1 RSSI = %#02lX, Noise = %#02lX, PostAGC=%#04lX\n", \
                    ((prSWRfb->prG1->u4CRC & BITS(24, 31)) >> 24),
                    ((prSWRfb->prG1->u4CRC & BITS(16, 23)) >> 16),
                    ((prSWRfb->prG1->u4CRC & BITS(0, 15)) >> 0)
                ));
        }
        else {
            DBGLOG(RFTEST, INFO, ("G1 CRC:%#08lx.\n", \
                prSWRfb->prG1->u4CRC));
        }
    }

    if (prRxCtrl->fgIsRxStatusG2) {
        DBGLOG(RFTEST, INFO, ("G2 LQ0 = %#02X, LQ1 = %#02X, LQ2 = %#02X,\n"
                              "   LQ3 = %#02X, LQ4 = %#02X, LQ5 = %#02X,\n",\
                  prSWRfb->prG2->ucLQ0, prSWRfb->prG2->ucLQ1, prSWRfb->prG2->ucLQ2,\
                  prSWRfb->prG2->ucLQ3, prSWRfb->prG2->ucLQ4, prSWRfb->prG2->ucLQ5\
            ));

        #if defined(LINUX) || defined (WINDOWS_DDK)
        DBGLOG(RFTEST, INFO, ("   Rate = %#02lX, Noise Floor = %#03lX,\n",
                  ((prSWRfb->prG2->u2NFRate & BITS(0, 5)) >> 0),
                  ((prSWRfb->prG2->u2NFRate & BITS(6, 15)) >> 6)
            ));
        #else // Window and WinCE
        DBGLOG(RFTEST, INFO, ("   Rate = %#02lX, Noise Floor = %fdBm,\n",
                  ((prSWRfb->prG2->u2NFRate & BITS(0, 5)) >> 0),
                  ((prSWRfb->prG2->u2NFRate & BITS(6, 15)) >> 6)/2.0-110
               ));
        #endif
    }
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This function stop Rx process of RF test
*
* \param[in] prAdapter      Pointer of Adapter Data Structure
*
* \return none
*/
/*----------------------------------------------------------------------------*/
VOID
rftestRxStopRx (
    IN P_ADAPTER_T prAdapter
    )
{
    P_RFTEST_SETTING_STRUC_T    prSetting;
    P_RFTEST_STATUS_STRUC_T     prStatus;
    P_RX_CTRL_T                 prRxCtrl;
    P_RFTEST_INFO_T             prRFATInfo;

    DEBUGFUNC("rftestRxStopRx");

    ASSERT(prAdapter);
    DBGLOG(RFTEST, TRACE, ("\n"));

    prSetting = &prAdapter->rRFTestInfo.rSetting;
    prStatus  = &prAdapter->rRFTestInfo.rStatus;
    prRxCtrl = &prAdapter->rRxCtrl;
    prRFATInfo = &prAdapter->rRFTestInfo;
    /*Stop Rx, clear s/w h/w queue*/
    nicRxFlushStopQueue(prAdapter, TRUE, TRUE);

    DBGLOG(RFTEST, INFO, ("Pakcet received = %"DBG_PRINTF_64BIT_DEC", Packet showed = %"DBG_PRINTF_64BIT_DEC".\n", \
        prRxCtrl->au8Statistics[RX_MPDU_TOTAL_COUNT],\
        prStatus->u8RxedPacketCnt));
    /*Stop MAC Tx/Rx*/
    NIC_MAC_TX_RX_CONTROL(prAdapter, FALSE, FALSE);
    //4 2008/06/30, mikewu, moved for appropriate layer
    prAdapter->rRxCtrl.fgIsRfTestRxMode = FALSE;
    prRFATInfo->eCurrentState = RF_AUTOTEST_STATE_STANDBY;

    return;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This function will do initialization of RF test module and all
*        variables in RFTEST_INFO_T.
*
* \param[in] prAdapter      Pointer of Adapter Data Structure
*
* \return The result of the rftestInit
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
rftestInit (
    IN P_ADAPTER_T prAdapter
    )
{
    P_RFTEST_INFO_T             prRfTestInfo;
    WLAN_STATUS                 rStatus;

    DEBUGFUNC("rftestUpdateTxConfig");
    ASSERT(prAdapter);

    DBGLOG(RFTEST, TRACE, ("\n"));

    prRfTestInfo = &prAdapter->rRFTestInfo;

    /*1. Init Variable */
    prRfTestInfo->eCurrentState = RF_AUTOTEST_STATE_STANDBY;
    rftestSetSWDefaultValue(prAdapter);

    /*2. Allocate buffer*/
    rStatus = rftestAllocateMemory(prAdapter);
    if (rStatus != WLAN_STATUS_SUCCESS) {
        return rStatus;
    }

    /*3. Init rftest tx queue*/
    rftestTxInitialize(prAdapter);

    /*4. Disable Adapter default setting.*/
    nicARDisable(prAdapter);
    ARB_CANCEL_TIMER(prAdapter, prAdapter->rStatisticsInfo.rPeekTimer);

    /*5. Disable MAC Tx/Rx.*/
    NIC_MAC_TX_RX_CONTROL(prAdapter, FALSE, FALSE);
    DBGLOG(RFTEST, INFO, ("rftest init , ThermoInfo state = %d\n",\
        prAdapter->rThermoInfo.rState));

    return rStatus;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This function will set the default RF testing related variables
*
* \param[in] prAdapter Pointer of Adapter Data Structure
*
* \return none
*/
/*----------------------------------------------------------------------------*/
VOID
rftestSetSWDefaultValue (
    IN P_ADAPTER_T prAdapter
    )
{
    P_RFTEST_INFO_T             prRfTestInfo;
    P_RFTEST_SETTING_STRUC_T    prSetting;
    P_RFTEST_STATUS_STRUC_T     prStatus;

    DEBUGFUNC("rftestSetSWDefaultValue");
    ASSERT(prAdapter);

    DBGLOG(RFTEST, TRACE, ("\n"));

    prRfTestInfo = &prAdapter->rRFTestInfo;
    prSetting = &prRfTestInfo->rSetting;
    prStatus = &prRfTestInfo->rStatus;

    /* Initize variables */
    kalMemZero(prSetting, sizeof(RFTEST_SETTING_STRUC_T));
    kalMemZero(prStatus, sizeof(RFTEST_STATUS_STRUC_T));
    kalMemCopy(prSetting->aucPktContent, \
      (PVOID)  aucRftestDefPktCont, sizeof(aucRftestDefPktCont));
    prSetting->u4PacketLen = RF_AT_PARAM_TX_PKTLEN_BYTE_DEFAULT;
    prSetting->u4PacketCnt = RF_AT_PARAM_TX_PKTCNT_DEFAULT;
    prSetting->u4PacketIntervalUs = RF_AT_PARAM_TX_PKT_INTERVAL_US_DEFAULT;

    /* Reset all Adapter Rx/Tx modules */
    RX_RESET_ALL_CNTS((&prAdapter->rRxCtrl));
    TX_RESET_ALL_CNTS((&prAdapter->rTxCtrl));

    return;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief Follow OID setting struct to set RF channel
*
* \param[in] prAdapter      Pointer of Adapter Data Structure
*
* \retvalue WLAN_STATUS_SUCCESS successful to set channel
* \retvalue WLAN_STATUS_FAILURE fail to get channel by frequency
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
rftestSet80211Configuration (
    IN P_ADAPTER_T prAdapter,
    IN P_PARAM_802_11_CONFIG_T prNewConfig
    )
{
    P_RFTEST_STATUS_STRUC_T     prStatus;
    WLAN_STATUS                 rStatus;
    ENUM_BAND_T                 eBand;
    UINT_8                      ucChannelNum;

    DEBUGFUNC("rftestSet80211Configuration");
    ASSERT(prAdapter);
    ASSERT(prNewConfig);

    DBGLOG(RFTEST, TRACE, ("\n"));

    prStatus = &prAdapter->rRFTestInfo.rStatus;

    rStatus = nicGetChannelBandFromFreq(
                    prAdapter,
                    prNewConfig->u4DSConfig,
                    &eBand,
                    &ucChannelNum);

    if (rStatus == WLAN_STATUS_SUCCESS) {
        nicSwitchChannel(
             prAdapter,
             eBand,
             ucChannelNum,
             CFG_INIT_TX_POWER_LIMIT);

        DBGLOG(RFTEST, INFO, ("Change to channel:%d, Band:%d.\n",\
                eBand,ucChannelNum));
        prStatus->u4DSConfig = prNewConfig->u4DSConfig;
    }
    else {
        DBGLOG(RFTEST, ERROR, ("Can not switch RF channel\n"));
    }

    return rStatus;
}

#if 0
/*----------------------------------------------------------------------------*/
/*!
* \brief
*
* \param prAdapter      Pointer of Adapter Data Structure
*
* \return
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
rftestQuery80211Configuration (
    IN P_ADAPTER_T prAdapter,
    IN P_PARAM_802_11_CONFIG_T       prQueryConfig
    )
{

    P_RFTEST_STATUS_STRUC_T     prStatus;
    WLAN_STATUS                 rStatus= WLAN_STATUS_SUCCESS;

    DEBUGFUNC("rftestGet80211Configuration");
    ASSERT(prAdapter);
    ASSERT(prQueryConfig);

    DBGLOG(RFTEST, TRACE, ("\n"));

    prStatus = &prAdapter->rRFTestInfo.rStatus;

    prQueryConfig->u4DSConfig = prStatus->u4DSConfig;

    return rStatus;
}
#endif

/*----------------------------------------------------------------------------*/
/*!
* \brief This function will do un-initialization of RF test module and all
*        variables in RFTEST_INFO_T.
*
* \param[in] prAdapter      Pointer of Adapter Data Structure
*
* \retvalue WLAN_STATUS_SUCCESS success
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
rftestUnInit (
    IN P_ADAPTER_T prAdapter
    )
{
    P_RFTEST_INFO_T     prRfTestInfo;

    DEBUGFUNC("rftestUnInit");
    ASSERT(prAdapter);

    DBGLOG(RFTEST, TRACE, ("\n"));

    prRfTestInfo = &prAdapter->rRFTestInfo;

    /* Return buffer */
    rftestFreeMemory(prAdapter);

    /*Initize variables */
    kalMemZero(prRfTestInfo, sizeof(RFTEST_INFO_T));

    /* Need to recall eeprom for its size and checksum */
    if (nicReadConfig(prAdapter, TRUE) != WLAN_STATUS_SUCCESS ) {
        DBGLOG(RFTEST, ERROR, ("nicReadConfig return error, eeprom load failed.\n"));
    }

    return WLAN_STATUS_SUCCESS;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This function based on thermo value to update related BB/RF setting.
*
* \param[in] prAdapter      Pointer of Adapter Data Structure
*
* \return none
*/
/*----------------------------------------------------------------------------*/
VOID
rftestAdoptBbRfByThermo (
    IN P_ADAPTER_T prAdapter
    )
{
    UINT_8                      ucTmp;
    ALC_VAL                     rAlcCalVal;

    DEBUGFUNC("rftestAdoptBbRfByThermo");

    ASSERT(prAdapter);

    DBGLOG(RFTEST, TRACE, ("\n"));

    for (ucTmp =0 ; ucTmp < 8 ; ucTmp++) {
         NIC_ALC_TRIGGER(prAdapter);
    }

    NIC_ALC_GET_CAL_VALUE(prAdapter, &rAlcCalVal);
    DBGLOG(RFTEST, TRACE, ("Calculated Value = 0x%X\n", rAlcCalVal));

    NIC_THERMO_UPDATE_TX_GAIN(
         prAdapter,
         prAdapter->rRFInfo.ucChannelNum,
         prAdapter->rRFInfo.eBand,
         rAlcCalVal);

    NIC_THERMO_UPDATE_RX_SETTING(
        prAdapter,
        rAlcCalVal);

    return;
}


