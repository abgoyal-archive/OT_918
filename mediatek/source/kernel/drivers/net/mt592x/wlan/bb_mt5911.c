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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/bb_mt5911.c#1 $
*/

/*! \file   "bb_mt5911.c"
    \brief  The operation of MT5911 baseband

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
** $Log: bb_mt5911.c $
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\18 2008-10-29 11:04:17 GMT mtk01088
**  update code for lint warning
**  \main\maintrunk.MT5921\17 2008-08-22 17:57:15 GMT mtk01088
**  remove un-used code
**  \main\maintrunk.MT5921\16 2008-08-18 19:27:32 GMT mtk01088
**  remove non-used code
**  \main\maintrunk.MT5921\15 2008-04-11 00:25:01 GMT mtk01385
**  1. add update BB Rx setting based on thermo info function.
**  \main\maintrunk.MT5921\14 2008-04-07 23:22:45 GMT mtk01084
**  modify lines in setting MCR_IOPCR, which will set ant_p/n to input mode
**  \main\maintrunk.MT5921\13 2008-02-21 15:01:48 GMT mtk01461
**  Add comment tn CR3 setting
**  \main\maintrunk.MT5921\12 2008-02-12 23:00:58 GMT mtk01461
**  Fix 0x6c wrong definition problem
**  \main\maintrunk.MT5921\11 2008-02-01 10:47:42 GMT mtk01385
**  1. Fix WinCE 4.2 compiling error.
**  \main\maintrunk.MT5921\10 2007-11-30 17:00:11 GMT mtk01425
**  1. Fix compiling error
**  \main\maintrunk.MT5921\9 2007-11-07 16:32:35 GMT mtk01088
**  add the initial value
**  \main\maintrunk.MT5921\8 2007-11-06 21:01:15 GMT mtk01088
**  remove non-used include
**  \main\maintrunk.MT5921\7 2007-11-06 19:59:04 GMT mtk01088
**  Now 5911BB not use MTK RF
**  \main\maintrunk.MT5921\6 2007-10-30 20:09:06 GMT mtk01084
**  fix compiling errors
**  \main\maintrunk.MT5921\5 2007-10-30 10:39:03 GMT mtk01425
**  1. Modify BB-related architecture
**  \main\maintrunk.MT5921\4 2007-10-26 11:53:21 GMT mtk01425
**  1. Move some BB initialize code here
** Revision 1.2  2007/07/05 07:25:32  MTK01461
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
#include "bb_mt5911.h"

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

REG_ENTRY_T arBBInitTableForAiroha2236[] = {
    {81,  0x1b},  // bandgap current
    {83,  0xfb},  // TX DAC buffer current
    {84,  0x15},  // DAC common mode/gain mode
    {92,  0x41},  // RX ADC gain mode 1V
    {93,  0xa8},  // RX ADC bias current
    {94,  0x40},  // RX ADC common mode
    {45,  0x54},  // Target 1
    {46,  0x1c},
    {45,  0x55},  // Target 2
    {46,  0x1d},
    {45,  0x51},  // LNA thr  : G1 & G2 switch
    {46,  0x1f},
    {45,  0x52},  // LNA thr2 : low & middle switch
    {46,  0x1f},
    {45,  0x53},  // LNA thr3 : high & middle switch
    {46,  0x1b},
    {45,  0x56},  // G1 & G2
    {46,  0x90},
    {45,  0x57},  // G2 & G3
    {46,  0x10},
    {45,  0x58},  // G4 : for middle gain
    {46,  0x0b},
    {45,  0x00},  // op mode
    {46,  0x22},
    {45,  0x01},  // T1 , T2
    {46,  0xf4},
    {45,  0x02},  // T3 , T4
    {46,  0x60},
    {45,  0x03},  // T5 , T6
    {46,  0x64},
    {45,  0x04},  // T7 , T8
    {46,  0x64},
/* for adjacent channel */
    {49,  0x05},  // SQ1
    {50,  0x84},  // SQ2
    {77,  0x94},  // OFDM OSD

    {45,  0x4b},  // Ed thr
    {46,  0x18},
    {45,  0x78},  // CCK thr
    {46,  0x07},
    {45,  0x79},  // OFDM thr
    {46,  0x07},
    {45,  0x77},  // CCK AR & OFDM AR
    {46,  0xa7},
    {45,  0x83},  // jmp_down_thr & jump_up_thr
    {46,  0x63},
    {45,  0x7d},  // LNA gain
    {46,  0x11},
    {45,  0x84},  // LNA middle gain
    {46,  0xe7},
    {45,  0x5b},  // ZC threshold
    {46,  0x10},
    {45,  0x82},  // IQ accumulation time
    {46,  0x12},
    {03,  0x21}     // CR3, T/RX configure-2: (RX antenna: fixed antenna 0, Bit[0]: reserved).
};


const REG_ENTRY_T arOFDMTXBackOff[] = {
    {39, 0x00},
    {40, 0x65},
    {39, 0x01},
    {40, 0xf7},
    {39, 0x02},
    {40, 0xdf},
    {39, 0x03},
    {40, 0x65},
    {39, 0x04},
    {40, 0xf7},
    {39, 0x05},
    {40, 0xdf}
};

/* OFDM TX backoff setting for Japan */
const REG_ENTRY_T arOFDMTXBackOffforJapan[] = {
    {39, 0x00},
    {40, 0x65},
    {39, 0x01},
    {40, 0xf7},
    {39, 0x02},
    {40, 0xdf},
    {39, 0x03},
    {40, 0x65},
    {39, 0x04},
    {40, 0xf7},
    {39, 0x05},
    {40, 0xdf},
};


TABLE_ENTRY_T arBBInitTableByRF[] = {
    {arBBInitTableForAiroha2236, sizeof(arBBInitTableForAiroha2236)/sizeof(REG_ENTRY_T)}
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
    IN P_ADAPTER_T       prAdapter
    )
{
    UINT_16              u2Idx = 0;
    TABLE_ENTRY_T        rBBInitTable = arBBInitTableByRF[halGetRFType(prAdapter)];
    UINT_16              u2Size = rBBInitTable.u2Size;
    P_REG_ENTRY_T        parBBInitTable = rBBInitTable.pu4TablePtr;

    DEBUGFUNC("halBBInit");

    ASSERT(prAdapter);
    
    if (halGetRFType(prAdapter) == RF_TYPE_AL2236) {
        HAL_MCR_WR(prAdapter, MCR_IOPCR, IO_SET_TRAP_PIN_DEFAULT_ATTR | IO_SET_DBG_PORT_SEL);
        HAL_MCR_WR(prAdapter, 0x130, 0x001e);
        HAL_MCR_WR(prAdapter, MCR_RSCR, 0x11421222);
    }

    for(u2Idx = 0; u2Idx < u2Size; u2Idx++) {
        DBGLOG(INIT, TRACE, ("Set %#08lx = %#08lx\n", parBBInitTable[u2Idx].u4Offset, parBBInitTable[u2Idx].u4Value));
        HAL_BBCR_WR(prAdapter, parBBInitTable[u2Idx].u4Offset, parBBInitTable[u2Idx].u4Value);
    }

    //4 2007/07/04, mikewu, we just give it a default value
    halBBSetTxBackOff(prAdapter, prAdapter->rEEPROMCtrl.u4RegulationDomain);

    //4 2007/07/04, mikewu, now we use the value in the default config
    halBBSetDACOffset(prAdapter,
        prAdapter->rEEPROMCtrl.ucID,
        prAdapter->rEEPROMCtrl.ucQD);


}


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to set the OFDM TX Power Backoff according to
*        the regulation domain.
*
* \param prAdapter           a pointer to adapter private data structure.
* \param u4RegulationDomain  Regulation Domain
* \return -
*/
/*----------------------------------------------------------------------------*/
VOID
halBBSetTxBackOff (
    IN P_ADAPTER_T      prAdapter,
    IN UINT_32          u4RegulationDomain
    )
{
    UINT_16 u2Idx = 0;
    UINT_16 u2Size = 0;

    ASSERT(prAdapter);

    if (u4RegulationDomain == REGULATION_DOMAIN_JAPAN) {
        u2Size = sizeof(arOFDMTXBackOffforJapan)/sizeof(REG_ENTRY_T);
        for(u2Idx = 0; u2Idx < u2Size; u2Idx++) {
            HAL_BBCR_WR(prAdapter, arOFDMTXBackOffforJapan[u2Idx].u4Offset, arOFDMTXBackOffforJapan[u2Idx].u4Value);
        }
    }
    else {
        u2Size = sizeof(arOFDMTXBackOff)/sizeof(REG_ENTRY_T);
        for(u2Idx = 0; u2Idx < u2Size; u2Idx++) {
            HAL_BBCR_WR(prAdapter, arOFDMTXBackOff[u2Idx].u4Offset, arOFDMTXBackOff[u2Idx].u4Value);
        }
    }
}


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to set DAC offset
*
* \param prAdapter          Pointer to the Adapter structure
* \param ucID               I channel
* \param ucQD               Q channel
*
* \return -
*/
/*----------------------------------------------------------------------------*/
VOID
halBBSetDACOffset (
    IN P_ADAPTER_T prAdapter,
    IN UINT_8      ucID,
    IN UINT_8      ucQD
    )
{
    UINT_32 u4CR81, u4CR83, u4CR84;

    ASSERT(prAdapter);

    HAL_BBCR_RD(prAdapter, 81, &u4CR81);
    HAL_BBCR_RD(prAdapter, 83, &u4CR83);
    HAL_BBCR_RD(prAdapter, 84, &u4CR84);

    u4CR81 &= ~BITS(0,1);
    u4CR83 &= ~BITS(0,1);
    u4CR83 &= ~BITS(4,7);
    u4CR84 &= ~BITS(0,1);

    if (ucID & BIT(4)) { u4CR84 |= BIT(1); }
    if (ucID & BIT(3)) { u4CR81 |= BIT(0); }
    if (ucID & BIT(2)) { u4CR81 |= BIT(1); }
    if (ucID & BIT(1)) { u4CR83 |= BIT(6); }
    if (ucID & BIT(0)) { u4CR83 |= BIT(7); }
    if (ucQD & BIT(4)) { u4CR84 |= BIT(0); }
    if (ucQD & BIT(3)) { u4CR83 |= BIT(0); }
    if (ucQD & BIT(2)) { u4CR83 |= BIT(1); }
    if (ucQD & BIT(1)) { u4CR83 |= BIT(4); }
    if (ucQD & BIT(0)) { u4CR83 |= BIT(5); }

    HAL_BBCR_WR(prAdapter, 81, u4CR81);
    HAL_BBCR_WR(prAdapter, 83, u4CR83);
    HAL_BBCR_WR(prAdapter, 84, u4CR84);

}


/*----------------------------------------------------------------------------*/
/*!
* \brief Change MT5911BB band setting
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
    UINT_32 u4BBCR3 = 0;

    ASSERT(prAdapter);

    HAL_BBCR_RD(prAdapter, BBCR_CR3, &u4BBCR3);
    if(eBand == BAND_5G) {
        u4BBCR3 |=  CR3_BAND_5G_EN | CR3_RX_CCK_DIS;
    }
    else { /* BAND 2.4G */
        u4BBCR3 &= ~(CR3_BAND_5G_EN | CR3_RX_CCK_DIS);
    }

    HAL_BBCR_WR(prAdapter, BBCR_CR3, u4BBCR3);
}


/*----------------------------------------------------------------------------*/
/*!
* \brief Apply different temperature setting for MT5922BB
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
 
    DEBUGFUNC("halBBAdoptTempChange");

}


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
