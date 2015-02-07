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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/rf_al2236.c#1 $
*/

/*! \file   "rf_al2236.c"
    \brief  The collection of AL2236-specific hw functions

    N/A
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
** $Log: rf_al2236.c $
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\13 2008-08-22 18:03:13 GMT mtk01088
**  add function declaration, add assert check
**  \main\maintrunk.MT5921\12 2008-04-11 17:32:40 GMT mtk01461
**  Fix compile error - miss /
**  \main\maintrunk.MT5921\11 2008-04-11 00:27:21 GMT mtk01385
**  1. add update RF Rx setting based on thermo info function.
**  \main\maintrunk.MT5921\10 2008-03-12 09:52:34 GMT mtk01461
**  Fix compile warning in Linux
**  \main\maintrunk.MT5921\9 2007-12-29 16:39:51 GMT mtk01385
**  1. remove RICR_RF_START definition
**  \main\maintrunk.MT5921\8 2007-11-17 15:05:49 GMT mtk01385
**  1. add halRFGetRFChnlProgEntryFromChannelFreq function.
**  \main\maintrunk.MT5921\7 2007-11-06 19:42:21 GMT mtk01088
**  The different RF have different set channel method
**  \main\maintrunk.MT5921\6 2007-10-30 10:40:26 GMT mtk01425
**  1. Add halGetRFType
**
** Revision 1.2  2007/07/05 07:25:33  MTK01461
** Add Linux initial code, modify doc, add 11BB, RF init code
**
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

extern UINT_32 u4ScanInstCount;
extern BOOLEAN fgScanInited;

/*******************************************************************************
*                              C O N S T A N T S
********************************************************************************
*/

const UINT_32 au4RFInitTableForAiroha2236_24[] = {
    0x800116C7,
    0x8000B802,
    0x8000E7F3,
    0x800105A4,
    0x800F4DC5,
    0x800805B6,
    0x800A0688,
    0x800543B9,
    0x80001BBA,
    0x80000F9B,
    0x80039D8C,
    0x8008000D,
    0x8000587F
};


/* AL2236 channel table for 2.4 GHz band, 20 Mhz reference clock */
const RF_CHANNEL_PROG_ENTRY arRFChannelTableForAH2236[] = {
    {   0,  0, 0, 0, {0,0,0,0}},
    { CH_1,    2412000,     BAND_24G, 2,  { 0x8001F790, 0x80033331, 0, 0 } },
    { CH_2,    2417000,     BAND_24G, 2,  { 0x8001F790, 0x800B3331, 0, 0 } },
    { CH_3,    2422000,     BAND_24G, 2,  { 0x8001E790, 0x80033331, 0, 0 } },
    { CH_4,    2427000,     BAND_24G, 2,  { 0x8001E790, 0x800B3331, 0, 0 } },
    { CH_5,    2432000,     BAND_24G, 2,  { 0x8001F7A0, 0x80033331, 0, 0 } },
    { CH_6,    2437000,     BAND_24G, 2,  { 0x8001F7A0, 0x800B3331, 0, 0 } },
    { CH_7,    2442000,     BAND_24G, 2,  { 0x8001E7A0, 0x80033331, 0, 0 } },
    { CH_8,    2447000,     BAND_24G, 2,  { 0x8001E7A0, 0x800B3331, 0, 0 } },
    { CH_9,    2452000,     BAND_24G, 2,  { 0x8001F7B0, 0x80033331, 0, 0 } },
    { CH_10,   2457000,     BAND_24G, 2,  { 0x8001F7B0, 0x800B3331, 0, 0 } },
    { CH_11,   2462000,     BAND_24G, 2,  { 0x8001E7B0, 0x80033331, 0, 0 } },
    { CH_12,   2467000,     BAND_24G, 2,  { 0x8001E7B0, 0x800B3331, 0, 0 } },
    { CH_13,   2472000,     BAND_24G, 2,  { 0x8001F7C0, 0x80033331, 0, 0 } },
    { CH_14,   2484000,     BAND_24G, 2,  { 0x8001E7C0, 0x80066661, 0, 0 } }
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

/*******************************************************************************
*                   F U N C T I O N   D E C L A R A T I O N S
********************************************************************************
*/

VOID
halRFCalibrateAH2236(
    IN P_ADAPTER_T prAdapter
    );

/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/

/*----------------------------------------------------------------------------*/
/*!
* \brief Set the default RF initial table to EEPROM configuration
*
* \param prEEPROMCtrl      a pointer to the EEPROM configuration
*
* \return N/A
*/
/*----------------------------------------------------------------------------*/

VOID
halRFSetInitTable (
    IN P_EEPROM_CTRL_T prEEPROMCtrl
    )
{
    prEEPROMCtrl->pu4RFInitTable_24 = (PUINT_32)&au4RFInitTableForAiroha2236_24[0];
    prEEPROMCtrl->u4RFInitTable_24_Size = sizeof(au4RFInitTableForAiroha2236_24) / sizeof(UINT_32);

}


/*----------------------------------------------------------------------------*/
/*!
* \brief Initialize the RF
*
* \param prAdapter          a pointer to the adapter handler
* \param prEEPROMCtrl      a pointer to the EEPROM configuration
*
* \return N/A
*/
/*----------------------------------------------------------------------------*/
VOID
halRFInit (
    IN P_ADAPTER_T     prAdapter,
    IN P_EEPROM_CTRL_T prEEPROMCtrl
    )
{
    UINT_32 u4Index = 0;
    BOOLEAN fgStatus = FALSE;
    
    ASSERT(prAdapter);
    ASSERT(prEEPROMCtrl);

    for (u4Index = 0; u4Index < prEEPROMCtrl->u4RFInitTable_24_Size; u4Index++) {
        HAL_MCR_WR_AND_WAIT(prAdapter, MCR_RSDR, prEEPROMCtrl->pu4RFInitTable_24[u4Index],
            RSDR_SYNT_PROG_START, 2, 5, fgStatus);

        kalUdelay(20);
    }

    /* post process for some RF init */
    halRFCalibrateAH2236(prAdapter);

}


/*----------------------------------------------------------------------------*/
/*!
* \brief Calibrate the AL2236 RF chip
*
* \param prAdapter          a pointer to the adapter handler
*
*
* \return N/A
*/
/*----------------------------------------------------------------------------*/
VOID
halRFCalibrateAH2236 (
    IN P_ADAPTER_T prAdapter
    )
{
    UINT_32    i;
    BOOLEAN fgStatus;
    UINT_32 u4BBCR84 = 0, u4BBCR82 = 0, u4BBCR88 = 0;

    ASSERT(prAdapter);

    /* power on calibration */
    HAL_MCR_WR(prAdapter, MCR_HLPCR, HLPCR_RF_SX_EN);

    for (i = 0; i < 3; i++) {
        kalUdelay(50);
    }

    HAL_BBCR_RD(prAdapter, 84, &u4BBCR84);
    HAL_BBCR_RD(prAdapter, 82, &u4BBCR82);
    HAL_BBCR_RD(prAdapter, 88, &u4BBCR88);

    HAL_BBCR_WR(prAdapter, 85, 0x00);
    HAL_BBCR_WR(prAdapter, 8, 0x80);
    HAL_BBCR_WR(prAdapter, 82, 0x80);
    HAL_BBCR_WR(prAdapter, 84, u4BBCR84 | BIT(7));
    HAL_BBCR_WR(prAdapter, 88, u4BBCR88 | BIT(7));
    HAL_BBCR_WR(prAdapter, 88, u4BBCR88);

    /* TXDCOC */
    HAL_MCR_WR_AND_WAIT(prAdapter, MCR_RSDR, 0x8000D80F,
        RSDR_SYNT_PROG_START, 2, 5, fgStatus);
    kalUdelay(50);

    /* IQ imbalance */
    HAL_MCR_WR_AND_WAIT(prAdapter, MCR_RSDR, 0x8000780F,
        RSDR_SYNT_PROG_START, 2, 5, fgStatus);
    kalUdelay(50);

    HAL_MCR_WR_AND_WAIT(prAdapter, MCR_RSDR, 0x8000580F,
        RSDR_SYNT_PROG_START, 2, 5, fgStatus);

    HAL_BBCR_WR(prAdapter, 84, u4BBCR84);
    HAL_BBCR_WR(prAdapter, 82, u4BBCR82);

}


/*----------------------------------------------------------------------------*/
/*!
* \brief Program RF by platform, get the channel table by input channel number and band.
*
* \param[in] prAdapter pointer to the Adapter handler
* \param[in] ucChannelNum the channel number to query
* \param[in] eBand the band to query
*
* \return The Channel table entry
*
*/
/*----------------------------------------------------------------------------*/
P_RF_CHANNEL_PROG_ENTRY
halRFGetRFChnlProgEntry (
    IN P_ADAPTER_T prAdapter,
    IN UINT_8      ucChannelNum,
    IN ENUM_BAND_T eBand
    )
{
    UINT_32 u4Idx = 0;
    BOOLEAN fgFound = FALSE;

    for(u4Idx = 0; u4Idx < sizeof(arRFChannelTableForAH2236)/sizeof(RF_CHANNEL_PROG_ENTRY); u4Idx++) {
        if ( ucChannelNum == arRFChannelTableForAH2236[u4Idx].ucChannelNum &&
            arRFChannelTableForAH2236[u4Idx].eBand == eBand ){
            fgFound = TRUE;
            break;
        }

    }

    if (fgFound) {
        return (P_RF_CHANNEL_PROG_ENTRY)&arRFChannelTableForAH2236[u4Idx];
    } 
    else {
        return NULL;
    }
}


/*----------------------------------------------------------------------------*/
/*!
* \brief Program RF by platform, because RF does not know how to write RICR, so
*        we pass the configuration to HAL layer and let it set the RF.
*
* \param[in] prAdapter pointer to the Adapter handler
* \param[in] pu4SynthProgWords the word needs to be set in RF
* \param[in] u4NumWords number of words to be set
*
* \return N/A
*
*/
/*----------------------------------------------------------------------------*/
VOID
halRFSetProg (
    IN P_ADAPTER_T prAdapter,
    IN PUINT_32    pu4SynthProgWords,
    IN UINT_32     u4NumWords
    )
{
    UINT_32 u4Idx;
    BOOLEAN fgStatus = FALSE;

    for (u4Idx = 0; u4Idx < u4NumWords; u4Idx++) {
        HAL_MCR_WR_AND_WAIT(prAdapter, MCR_RSDR, pu4SynthProgWords[u4Idx],
            RSDR_SYNT_PROG_START, 2, 5, fgStatus);
    }
}


/*----------------------------------------------------------------------------*/
/*!
* \brief Do RF switch channel, call this function while driver not yet enter low power
*
* \param[in] prAdapter pointer to the Adapter handler
* \param[in] ucChannelNum The channel to switch
* \param[in] eBand The band to switch

* \return The channel and band can accept to switch or not
*
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
halRFSwitchChannel (
    IN P_ADAPTER_T prAdapter,
    IN UINT_8      ucChannelNum,
    IN ENUM_BAND_T eBand
    )
{
    P_RF_CHANNEL_PROG_ENTRY prRfChnlProgEntry;

    ASSERT(prAdapter);

    if ((prRfChnlProgEntry = halRFGetRFChnlProgEntry(prAdapter, ucChannelNum, eBand)) != NULL) {
        halRFSetProg(prAdapter,
                     prRfChnlProgEntry->au4SynthProgWords,
                     prRfChnlProgEntry->u4NumSynthProgWords);
        return WLAN_STATUS_SUCCESS;
    } 
    else {
        return WLAN_STATUS_NOT_ACCEPTED;
    }

}


/*----------------------------------------------------------------------------*/
/*!
* \brief Do RF switch channel at low power instruction, call this function while driver
*        make scan at low power
*
* \param[in] prAdapter pointer to the Adapter handler
* \param[in] ucChannelNum The channel to switch
* \param[in] eBand The band to switch

* \return The channel and band can accept to switch or not
*
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
halSetRFSwitchChnlInst (
    IN P_ADAPTER_T prAdapter,
    IN UINT_8      ucChannelNum,
    IN ENUM_BAND_T eBand
    )
{
    P_RF_CHANNEL_PROG_ENTRY prChProgEntry;
    UINT_32 i;

    ASSERT(prAdapter);

    if ((prChProgEntry = halRFGetRFChnlProgEntry(prAdapter, ucChannelNum, eBand)) != NULL) {
        /* Program the synthesizer. */
        for (i = 0; i < prChProgEntry->u4NumSynthProgWords; i++) {
             HAL_HW_SCAN_SET_INST_RFCR_WR(prAdapter,
                                         prChProgEntry->au4SynthProgWords[i]);
        }
        return WLAN_STATUS_SUCCESS;
    } 
    else {
        return WLAN_STATUS_NOT_ACCEPTED;
    }

}


/*----------------------------------------------------------------------------*/
/*!
* \brief To identity the RF type.
*
* \param[in] prAdapter pointer to the Adapter handler
*
* \return The RF type
*
*/
/*----------------------------------------------------------------------------*/
ENUM_RF_TYPE_T
halGetRFType (
    IN P_ADAPTER_T prAdapter
    )
{
    return RF_TYPE_AL2236;
}


/*----------------------------------------------------------------------------*/
/*!
* \brief Program RF by platform, get the channel table by input channel frequency.
*
* \param[in] prAdapter pointer to the Adapter handler
* \param[in] u4ChannelFreq the channel frequency to query
*
* \return The Channel table entry
*
*/
/*----------------------------------------------------------------------------*/
P_RF_CHANNEL_PROG_ENTRY
halRFGetRFChnlProgEntryFromChannelFreq (
    IN P_ADAPTER_T prAdapter,
    IN UINT_32     u4ChannelFreq
    )
{
    UINT_32 u4Idx = 0;
    BOOLEAN fgFound = FALSE;

    DEBUGFUNC("nicGetChannelBandFromFreq");

    ASSERT(prAdapter);

    for(u4Idx = 0; u4Idx < sizeof(arRFChannelTableForAH2236)/sizeof(RF_CHANNEL_PROG_ENTRY); u4Idx++) {
        if ( u4ChannelFreq == arRFChannelTableForAH2236[u4Idx].u4ChannelFreq  ){
            fgFound = TRUE;
            break;
        }

    }

    if (fgFound) {
        return (P_RF_CHANNEL_PROG_ENTRY)&arRFChannelTableForAH2236[u4Idx];
    } 
    else {
        return NULL;
    }
}


/*----------------------------------------------------------------------------*/
/*!
* \brief Apply different temperature setting for AL2236RF
*
* \param prAdapter          Pointer to the Adapter structure
* \param rState             Current Temperature state
*
* \return -
*/
/*----------------------------------------------------------------------------*/
VOID
halRFAdoptTempChange (
    IN P_ADAPTER_T          prAdapter,
    IN ENUM_THERMO_STATE_T  rState
    )
{
 
    DEBUGFUNC("halRFAdoptTempChange");
}

