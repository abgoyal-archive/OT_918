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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/bb_mt5921.c#2 $
*/

/*! \file   "bb_mt5921.c"
    \brief  The operation of MT5921 baseband

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
** $Log: bb_mt5921.c $
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\16 2009-04-01 16:43:42 GMT mtk01104
**  Keep ant_p and ant_n attributes for single antenna
**  \main\maintrunk.MT5921\15 2008-10-29 10:59:21 GMT mtk01088
**  update coding style for lint warning
**  \main\maintrunk.MT5921\14 2008-08-18 19:27:39 GMT mtk01088
**  remove non-used code
**  \main\maintrunk.MT5921\13 2008-06-13 10:44:25 GMT MTK01088
**  not adopt the temp change for 802.11A
**  \main\maintrunk.MT5921\12 2008-05-12 13:33:25 GMT mtk01084
**  modify debug message level
**  \main\maintrunk.MT5921\11 2008-05-03 20:32:09 GMT mtk01461
**  Fix compile warning
**  \main\maintrunk.MT5921\10 2008-04-30 13:57:41 GMT mtk01088
**  update the BB config by MT5921_BB_RF_Config V0.9
**  \main\maintrunk.MT5921\9 2008-04-11 00:22:14 GMT mtk01385
**  1. add update BB Rx setting based on thermo info function.
**  \main\maintrunk.MT5921\8 2008-04-07 23:23:08 GMT mtk01084
**  modify lines in setting MCR_IOPCR, which will set ant_p/n to input mode
**  \main\maintrunk.MT5921\7 2008-04-01 20:04:23 GMT mtk01088
**  Update the BB default setting by MT5921_BB_RF_Config v0.6
**  \main\maintrunk.MT5921\6 2008-03-28 19:15:22 GMT mtk01088
**  update the BB config setting by BB_RF_Config v.05
**  \main\maintrunk.MT5921\5 2008-03-19 20:09:58 GMT mtk01088
**  update BB default setting by MT5921MP_BB_RF_Config v0.2
**  \main\maintrunk.MT5921\4 2008-03-18 15:51:23 GMT mtk01088
**  avoid compiling warning
**  \main\maintrunk.MT5921\3 2008-03-18 13:55:18 GMT mtk01088
**  add BB default value from MPW branch
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
#include "bb_mt5921.h"

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
REG_ENTRY_T arBBInitTableForMTK60105[] = {
    {    1, 0x0631},
    {   16, 0xd190},
    {   17, 0x80a0},
    {   18, 0x6699},
    {   48, 0x1992},
    {   46, 0x143a},
    {   49, 0x66ee},
    {   24, 0x1c1f},
    {   25, 0x38ff},
    {  126, 0xd0bf},
    {  127, 0xda57},
    {   26, 0x6c98},
    {   27, 0x1029},
    {   29, 0x123b},
    {   15, 0x3f09},
    {   23, 0x0070},
    {   62, 0x1046},
    {   28, 0x603b},
    {   21, 0x14d1},
    {   43, 0xb90a},
    {   44, 0x07a2},
    {   72, 0xd0b9},
    {   63, 0x9b9b},
    {   74, 0x3669},
    {    4, 0x6596},
    {    5, 0x5965},
    {   75, 0x8a53},
    {  123, 0x039f},
    {  121, 0xf55c},
    {   67, 0x2080},
    {   64, 0x5821},
    {   65, 0x08a5},
    {  125, 0x0637},
    {   47, 0x340a},
    {   19, 0x260d},
    {  103, 0x00b7},
    {    6, 0x9659},
    {   13, 0x4018},
    {   61, 0x9908},
    {  124, 0x56b2},
};

const REG_ENTRY_T arOFDMTXBackOff[] = {
	// left blank here, for solving compiler warning, take a dummy register here
	{0, 0x00}, //CR0 is write only
};

/* OFDM TX backoff setting for Japan */
const REG_ENTRY_T arOFDMTXBackOffforJapan[] = {
	// left blank here, for solving compiler warning, take a dummy register here
	{0, 0x00}, //CR0 is write only
};

/* High Temperature setting (70)*/
static REG_ENTRY_T arHighTempSetting[] = {
    {   29, 0x1339},
    {   28, 0x6039},
    {   19, 0x2B0D},
    {  103, 0x00B2},
};

/* Normal Temperature setting (25)*/
static REG_ENTRY_T arNormalTempSetting[] = {
    {   29, 0x133B},
    {   28, 0x603B},
    {   19, 0x260D},
    {  103, 0x00B7},
};

/* Low Temperature setting (-20)*/
static REG_ENTRY_T arLowTempSetting[] = {
    {   29, 0x133C},
    {   28, 0x603C},
    {   19, 0x240D},
    {  103, 0x00B9},
};

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
* \brief Initialize the baseband
*
* \param prAdapter      a pointer to adapter private data structure.
*
* \return -
*/
/*----------------------------------------------------------------------------*/
VOID
halBBInit (
    IN P_ADAPTER_T          prAdapter
    )
{
    UINT_16 u2Idx = 0;
    UINT_16 u2Size = sizeof(arBBInitTableForMTK60105)/sizeof(REG_ENTRY_T);
    UINT_32 u4Tmp;

    DEBUGFUNC("halBBInit");

    ASSERT(prAdapter);

#if 1
    /* Keep antenna switch setting for single antenna application */
    HAL_MCR_RD(prAdapter, MCR_IOPCR, &u4Tmp);
    u4Tmp &= (IOPCR_IO_ANT_SEL_N_DIR | IOPCR_IO_ANT_SEL_P_DIR);
    HAL_MCR_WR(prAdapter, MCR_IOPCR,
        u4Tmp | IO_SET_TRAP_PIN_DEFAULT_ATTR | IO_SET_DBG_PORT_SEL);
#else
    HAL_MCR_WR(prAdapter, MCR_IOPCR, IO_SET_TRAP_PIN_DEFAULT_ATTR | IO_SET_DBG_PORT_SEL);
#endif

    for(u2Idx = 0; u2Idx < u2Size; u2Idx++) {
        DBGLOG(INIT, TRACE, ("Set %#lx = %#lx\n", arBBInitTableForMTK60105[u2Idx].u4Offset, arBBInitTableForMTK60105[u2Idx].u4Value));
        HAL_BBCR_WR(prAdapter, arBBInitTableForMTK60105[u2Idx].u4Offset, arBBInitTableForMTK60105[u2Idx].u4Value);
    }

    //CR 265 [BUG] TX RESP Antenna mode wrongly set to Antenna 1
    //Now use Rx Antenna 0
    HAL_BBCR_RD(prAdapter, 1, &u4Tmp);
    u4Tmp &= ~BITS(4,5);
    u4Tmp |= BIT(5);
    HAL_BBCR_WR(prAdapter, 1, u4Tmp);
    DBGLOG(HAL, TRACE,("BB Set Rx Antenna to 0!\n"));

}


/*----------------------------------------------------------------------------*/
/*!
* \brief Change MT5921BB band setting
*
* \param prAdapter          Pointer to the Adapter structure
* \param eBand              BAND, 2.4G or 5G
*
* \return -
*/
/*----------------------------------------------------------------------------*/
VOID
halBBChangeBand (
    IN P_ADAPTER_T prAdapter,
    IN ENUM_BAND_T eBand
    )
{

    DEBUGFUNC("halBBChangeBand");
    DBGLOG(HAL, TRACE,("BB change Band not support !!\n"));
}


/*----------------------------------------------------------------------------*/
/*!
* \brief Apply different temperature setting for MT5921BB
*
* \param prAdapter          Pointer to the Adapter structure
* \param rState             Current Temperature state
*
* \return -
*/
/*----------------------------------------------------------------------------*/
VOID
halBBAdoptTempChange (
    IN P_ADAPTER_T          prAdapter,
    IN ENUM_THERMO_STATE_T  rState
    )
{
#if CFG_ONLY_802_11A
#else
    UINT_16         u2Idx = 0;
    UINT_16         u2Size;
    P_REG_ENTRY_T   prTable;

    DEBUGFUNC("halBBAdoptTempChange");

    ASSERT(prAdapter);

    switch (rState) {
    case LOW_TEMP:
        u2Size = sizeof(arLowTempSetting)/sizeof(REG_ENTRY_T);
        prTable = &arLowTempSetting[0];
        break;
    case NORMAL_TEMP:
        u2Size = sizeof(arNormalTempSetting)/sizeof(REG_ENTRY_T);
        prTable = arNormalTempSetting;
        break;

    case HIGH_TEMP:
        u2Size = sizeof(arHighTempSetting)/sizeof(REG_ENTRY_T);
        prTable = arHighTempSetting;
        break;
    default:
        DBGLOG(HAL, ERROR, ("Temperature %d is not supported\n", rState));
        return;
    }

    for(u2Idx = 0; u2Idx < u2Size; u2Idx++) {
         DBGLOG(HAL, LOUD, ("Set BBCR_%ld = %#lx\n", prTable[u2Idx].u4Offset, prTable[u2Idx].u4Value));
         HAL_BBCR_WR(prAdapter, prTable[u2Idx].u4Offset, prTable[u2Idx].u4Value);
    }

    DBGLOG(HAL, TRACE, ("Temperature State is changed to %d\n", rState));
#endif
}

#if PTA_ENABLED
/*----------------------------------------------------------------------------*/
/*!
* \brief Set fixed RX gain for BT WiFi coexistence
*
* \param prAdapter             Pointer to the Adapter structure
* \param fgEnableFixedRxGain   Whether to use fixed RX gain
*
* \return -
*/
/*----------------------------------------------------------------------------*/
VOID
halBBEnableFixedRxGain (
    IN P_ADAPTER_T          prAdapter,
    IN BOOL                 fgEnableFixedRxGain
    )
{
    UINT_32 u4Size = sizeof(arBBInitTableForMTK60105)/sizeof(REG_ENTRY_T);
    UINT_32 u4CR24Index = 0xFFFFFFFF, u4CR25Index = 0xFFFFFFFF, index = 0;
    
    DEBUGFUNC("halBBEnableFixedRxGain");

    DBGLOG(HAL, TRACE, ("Use fixed RX gain? %d\r\n", fgEnableFixedRxGain));

    for(index = 0 ; index < u4Size ; index ++ ){
        if(arBBInitTableForMTK60105[index].u4Offset == BBCR_CR24){
            u4CR24Index = index;
        }
        if(arBBInitTableForMTK60105[index].u4Offset == BBCR_CR25){
            u4CR25Index = index;
        }
    }

    ASSERT(0xFFFFFFFF != u4CR24Index);
    ASSERT(0xFFFFFFFF != u4CR25Index);

    if((0xFFFFFFFF == u4CR24Index) || (0xFFFFFFFF == u4CR25Index)){
        return;
    }

    DBGLOG(HAL, TRACE, ("BBCR24 index %d BBCR25 index %d\r\n", u4CR24Index, u4CR25Index));

    DBGLOG(HAL, TRACE, ("CR24 value 0x%08x CR25 value 0x%08x\r\n", 
        arBBInitTableForMTK60105[u4CR24Index].u4Value,
        arBBInitTableForMTK60105[u4CR25Index].u4Value));

    if(fgEnableFixedRxGain){
        UINT_32 u4Value = 0;

        /* middle RX gain */
        u4Value = 0x001F;
        HAL_BBCR_WR(prAdapter, BBCR_CR24, u4Value);

        u4Value = arBBInitTableForMTK60105[u4CR25Index].u4Value;
        u4Value &= ~BITS(8, 12);//AGC_LNA_THR3
        u4Value &= ~BITS(5, 6);//Mid_low check en, High_mid check en 
        HAL_BBCR_WR(prAdapter, BBCR_CR25, u4Value);        

    }else{
        HAL_BBCR_WR(prAdapter, BBCR_CR24, 
            arBBInitTableForMTK60105[u4CR24Index].u4Value);

        HAL_BBCR_WR(prAdapter, BBCR_CR25, 
            arBBInitTableForMTK60105[u4CR25Index].u4Value);
    }
}
#endif
