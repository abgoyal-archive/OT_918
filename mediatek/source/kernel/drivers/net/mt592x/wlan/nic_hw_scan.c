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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/nic_hw_scan.c#2 $
*/

/*! \file   "nic_hw_scan.c"
    \brief  The NIC layer file, which placed function for HW scan related methods.

    Detail description.
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
** $Log: nic_hw_scan.c $
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\23 2009-07-16 11:38:22 GMT mtk01461
**  Fix - convert the RFB channel index to channel mapping function
**  \main\maintrunk.MT5921\22 2008-12-01 18:20:37 GMT mtk01088
**  fixed the lint "possible using null pointer" warning
**  \main\maintrunk.MT5921\21 2008-08-19 10:30:00 GMT mtk01084
**  modification for coding rule conformance
**  \main\maintrunk.MT5921\20 2008-06-16 22:20:03 GMT mtk01084
**  Not to apply the channel index setting when the HW scan index is not valid
**  \main\maintrunk.MT5921\19 2008-06-16 16:11:01 GMT mtk01084
**  add new function to get channel/ band index during scan
**  \main\maintrunk.MT5921\18 2008-05-12 15:24:06 GMT mtk01084
**  force to set MAC to infrastructure mode before entering BG SSID scan state
**  \main\maintrunk.MT5921\17 2008-03-25 22:20:54 GMT mtk01084
**  modify lines in BG SSID scan setting
**  \main\maintrunk.MT5921\16 2008-03-03 18:10:27 GMT mtk01084
**  modify function description comments
**  \main\maintrunk.MT5921\15 2008-02-18 17:23:59 GMT mtk01084
**  add function description
**  \main\maintrunk.MT5921\14 2007-12-08 22:32:12 GMT mtk01084
**  use register configuration for setting to honor service period or trigger events
**  \main\maintrunk.MT5921\13 2007-12-07 10:17:47 GMT mtk01084
**  not to reset scan done event on disabling scan
**  \main\maintrunk.MT5921\12 2007-11-14 11:55:13 GMT mtk01084
**  update lines to do input argument check
**  \main\maintrunk.MT5921\11 2007-11-13 18:03:18 GMT mtk01084
**  code refinement
**  \main\maintrunk.MT5921\10 2007-11-13 10:35:23 GMT mtk01084
**  remove unused lines
**  \main\maintrunk.MT5921\9 2007-11-12 16:18:08 GMT mtk01084
**  modify nicHwScanConfig()
**  \main\maintrunk.MT5921\8 2007-11-12 15:08:44 GMT mtk01084
**  clear SCAN_DONE event when disabling scan function
**  \main\maintrunk.MT5921\7 2007-10-31 21:32:50 GMT mtk01084
**  enable/ disable beacon timeout counter when switching between scan state
**  \main\maintrunk.MT5921\6 2007-10-26 10:26:39 GMT mtk01084
**  disable Beacon timeout during scan
**  \main\maintrunk.MT5921\5 2007-10-25 18:06:25 GMT mtk01461
**  Add VOIP SCAN Support  & Refine Roaming
** Revision 1.1  2007/07/05 14:06:38  MTK01084
** Initial version
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

/******************************************************************************
*                              C O N S T A N T S
*******************************************************************************
*/

/******************************************************************************
*                             D A T A   T Y P E S
*******************************************************************************
*/

/******************************************************************************
*                            P U B L I C   D A T A
*******************************************************************************
*/

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
* \brief This routine is used to setup the scan parameters.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
* \param[in] prScanCfg The scan parameters.
* \param[in] eScanMode To do NORMAL scan or BG SSID scan.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
nicHwScanConfig (
    IN P_ADAPTER_T prAdapter,
    IN P_SCAN_CONFIG_T prScanCfg,
    IN ENUM_HW_SCAN_MODE_T eScanMode
    )
{
    ASSERT(prAdapter);
    ASSERT(prScanCfg);

    halHwScanSetInitialInst(prAdapter, prScanCfg, eScanMode);

    halHwScanSetTerminateInst(prAdapter, prScanCfg, eScanMode);

    halHwScanRegisterInit(prAdapter,
                          prScanCfg,
                          eScanMode);

    if (eScanMode == ENUM_HW_SCAN_BG_SSID_SCAN) {
        P_BSS_INFO_T prBssInfo = &prAdapter->rBssInfo;
        kalMemZero(prBssInfo->aucBSSID, MAC_ADDR_LEN);
        prBssInfo->eBSSType = BSS_TYPE_INFRASTRUCTURE;
        nicSetupBSS(prAdapter, prBssInfo);
    }
}   /* nicHwScanConfig */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to restore the setting after scan.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
* \param[in] prScanCfg The scan parameters.
* \param[in] eScanMode To do NORMAL scan or BG SSID scan.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
nicHwScanConfigRestore (
    IN P_ADAPTER_T prAdapter,
    IN P_SCAN_CONFIG_T prScanCfg,
    IN ENUM_HW_SCAN_MODE_T eScanMode
    )
{
    ASSERT(prAdapter);
    ASSERT(prScanCfg);

    halHwScanRegisterUnInit(prAdapter,
                            prScanCfg,
                            eScanMode);
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to enable the HW scan function.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
* \param[in] eScanMode To do NORMAL scan or BG SSID scan.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
nicHwScanEnable (
    IN P_ADAPTER_T prAdapter,
    IN ENUM_HW_SCAN_MODE_T eScanMode
    )
{
    ASSERT(prAdapter);

    halHwScanEnable(prAdapter, eScanMode);

}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to disable the HW scan function.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
* \param[in] eScanMode To do NORMAL scan or BG SSID scan.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
nicHwScanDisable (
    IN P_ADAPTER_T prAdapter,
    IN ENUM_HW_SCAN_MODE_T eScanMode
    )
{
    ASSERT(prAdapter);

    /* Disable function and polling until function is disabled */
    halHwScanDisable(prAdapter, eScanMode);

    // NOTE: not to unmask scan done interrupt due to this procedure will
    //       always be invoked in BG SSID scan
//    NIC_RESET_INT_EVENT(prAdapter, INT_EVENT_SCAN_DONE);

} /* nicHwScanDisable */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to get the last channel been scanned.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
* \param[out] pucChnlIdx The last channel index been scanned.
* \param[out] pucBandIdx The last band index been scanned.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
nicHwScanGetLastScannedChnlFreq (
    IN  P_ADAPTER_T prAdapter,
    OUT PUINT_8     pucChnlIdx,
    OUT PUINT_8     pucBandIdx
    )
{
    UINT_32 u4RegValue;

    ASSERT(prAdapter);
    ASSERT(pucChnlIdx);
    ASSERT(pucBandIdx);

    /* read the HW register for the scanned channel/ band index information */
    HAL_MCR_RD(prAdapter, MCR_BSSSAR, &u4RegValue);

    /* get the last scanned channel and band index */
    *pucChnlIdx = (UINT_8)((u4RegValue & BSSSAR_CHNL_INDEX_MASK) >> BSSSAR_CHNL_INDEX_OFFSET);
    *pucBandIdx = (UINT_8)((u4RegValue & BSSSAR_BAND_INDEX_MASK) >> BSSSAR_BAND_INDEX_OFFSET);

}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to get the frequency during scan.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
* \param[in] u2QoSCtrlInfo the HW RFB, which carried the frequency information.
* \param[out] pucChnlNum The channel index been scanned.
* \param[out] prBandNum The band index been scanned.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
nicHwScanScannedChnlFreqBand (
    IN  P_ADAPTER_T     prAdapter,
    IN  UINT_16         u2ChnlBandInfo,
    OUT PUINT_8         pucChnlNum,
    OUT P_ENUM_BAND_T   prBandNum
    )
{
    P_SCAN_CONFIG_T prScanCfg;
    UINT_8  ucChnlIdx, ucBandIdx;

    ASSERT(prAdapter);
    ASSERT(pucChnlNum);
    ASSERT(prBandNum);

    prScanCfg = &prAdapter->rScanInfo.rScanConfig;

    /* Not to apply the channel index setting when the HW scan index is not valid */
    if ((u2ChnlBandInfo & ~BIT(7)) == 0) {
        P_RF_INFO_T prRFInfo;

        /* Use current channel information if RFB's channel info is 0 */
        prRFInfo = &prAdapter->rRFInfo;        
        *pucChnlNum = prRFInfo->ucChannelNum;
        *prBandNum = prRFInfo->eBand;
        return;
    }

    ucChnlIdx = (UINT_8)((u2ChnlBandInfo & BITS(8, 15)) >> 8) - 1;
    ucBandIdx = (UINT_8)(u2ChnlBandInfo & BITS(0, 6)) - 1;

#if DBG & 0
    if (ucChnlIdx > (sizeof(prScanCfg->arChnlInfoList) / sizeof(RF_CHANNEL_INFO_T)) ||
        ucBandIdx > (sizeof(prScanCfg->arChnlInfoList) / sizeof(RF_CHANNEL_INFO_T))) {
        ucChnlIdx = 0;
        ucBandIdx = 0;
    }
#endif

    if (ucChnlIdx < MAXIMUM_OPERATION_CHANNEL_LIST) {
        *pucChnlNum = prScanCfg->arChnlInfoList[ucChnlIdx].ucChannelNum;
        *prBandNum = prScanCfg->arChnlInfoList[ucChnlIdx].eBand;
    }

    DBGLOG(SCAN, INFO, ("Channel Num: %d, Band: %s (CH Index: %d, BAND Index: %d)\n",
                        *pucChnlNum, (*prBandNum) ? "5GHz" : "2.4GHz",
                        ucChnlIdx, ucBandIdx));

    return;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to process the scan done interrupt.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
nicProcesScanDoneInterrupt(
    IN P_ADAPTER_T      prAdapter
    )
{
    ASSERT(prAdapter);

    arbFsmRunEventScanDone(prAdapter);
}


