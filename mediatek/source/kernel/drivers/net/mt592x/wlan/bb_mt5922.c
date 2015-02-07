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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/bb_mt5922.c#1 $
*/

/*! \file   "bb_mt5922.c"
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
** $Log: bb_mt5922.c $
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\13 2008-10-29 11:04:43 GMT mtk01088
**  \main\maintrunk.MT5921\12 2008-08-18 19:27:24 GMT mtk01088
**  remove non-used code
**  \main\maintrunk.MT5921\11 2008-04-11 00:25:40 GMT mtk01385
**  1. add update BB Rx setting based on thermo info function.
**  \main\maintrunk.MT5921\10 2008-04-07 23:22:52 GMT mtk01084
**  modify lines in setting MCR_IOPCR, which will set ant_p/n to input mode
**  \main\maintrunk.MT5921\9 2008-02-12 23:01:01 GMT mtk01461
**  Fix 0x6c wrong definition problem
**  \main\maintrunk.MT5921\8 2008-02-05 14:15:51 GMT mtk01088
**  update BB default setting by MT5921 FPGA BB RF configuration v0.1
**  \main\maintrunk.MT5921\7 2008-02-01 10:48:45 GMT mtk01385
**  1. Fix WinCE 4.2 compiling error.
**  \main\maintrunk.MT5921\6 2007-11-22 22:14:45 GMT mtk01084
**  update BB initial value
**  \main\maintrunk.MT5921\5 2007-11-19 22:01:52 GMT mtk01084
**  update BB initial table for RF A60105
**  \main\maintrunk.MT5921\4 2007-11-06 21:36:36 GMT mtk01088
**  fixed compiler error
**  \main\maintrunk.MT5921\3 2007-11-06 19:58:06 GMT mtk01088
**  Different RF use dirrerent CW setting
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
#include "bb_mt5922.h"

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
    {   1, 0x00000631}, //
    {  16, 0x0000d160}, //
    {  17, 0x00009090}, //
    {  18, 0x00007766}, //
    {  48, 0x00001992}, //
    {  46, 0x0000143a}, //
    {  49, 0x000066ee}, //
    {  24, 0x00001e1d}, //
    {  25, 0x0000197f}, //
    { 126, 0x0000d0bf}, //
    { 127, 0x0000da57}, //
    {  26, 0x00006cb8}, //
    {  27, 0x0000d889}, //
    {  29, 0x00001339}, //
    {  15, 0x00003f09}, //
    {  23, 0x00000070}, //
    {  62, 0x00000303}, //
    {  28, 0x00006039}, //
    {  21, 0x000018d1}, //
    {  43, 0x0000b90d}, //
    {  44, 0x000007a2}, //
    {  72, 0x0000e8b2}, //
    {  63, 0x00009b9b}, //
    {  74, 0x00003665}, //
    {  75, 0x00008a53}, //
    { 121, 0x00000800}, //
    {  67, 0x00002080}, //
    {  64, 0x00005821}, //
    {  65, 0x000008a5}, //
    { 125, 0x00000537}, //
    {  47, 0x0000340a}, //
    {  19, 0x0000340D}, //
    { 103, 0x000000AB}, //
    {  13, 0x00004318}, //
    {  4, 0x00006596}, //
    {  5, 0x00005965}, //
    {  6, 0x00009659}, //
};

REG_ENTRY_T arBBInitTableForAiroha2236[] = {
    // left blank here, for solving compiler warning, take a dummy register here
    {0, 0x00}, //CR0 is write only
};

TABLE_ENTRY_T arBBInitTableByRF[] = {
    {arBBInitTableForAiroha2236, sizeof(arBBInitTableForAiroha2236)/sizeof(REG_ENTRY_T)},
    {arBBInitTableForMTK60105, sizeof(arBBInitTableForMTK60105)/sizeof(REG_ENTRY_T)}
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
    IN P_ADAPTER_T        prAdapter
    )
{
    UINT_16 u2Idx = 0;
    TABLE_ENTRY_T rBBInitTable = arBBInitTableByRF[halGetRFType(prAdapter)];
    //UINT_16 u2Size = sizeof(arBBInitTableForAiroha2236)/sizeof(REG_ENTRY_T);
    UINT_16 u2Size = rBBInitTable.u2Size;
    P_REG_ENTRY_T parBBInitTable = rBBInitTable.pu4TablePtr;

    DEBUGFUNC("halBBInit");

    ASSERT(prAdapter);

    HAL_MCR_WR(prAdapter, MCR_IOPCR, IO_SET_TRAP_PIN_DEFAULT_ATTR | IO_SET_DBG_PORT_SEL);
    HAL_MCR_WR(prAdapter, 0x130, 0x001e);

    if (halGetRFType(prAdapter) == RF_TYPE_AL2236) {
        HAL_MCR_WR(prAdapter, MCR_RSCR, 0x11421222);
    }
    else if (halGetRFType(prAdapter) == RF_TYPE_MTK60105) {
        HAL_MCR_WR(prAdapter, MCR_RSCR, 0x1182F22F);
    }

    for(u2Idx = 0; u2Idx < u2Size; u2Idx++) {
        DBGLOG(INIT, TRACE, ("Set %#x = %#x\n", parBBInitTable[u2Idx].u4Offset, parBBInitTable[u2Idx].u4Value));
        DBGLOG(MIKE, TRACE, ("Set %#x = %#x\n", parBBInitTable[u2Idx].u4Offset, parBBInitTable[u2Idx].u4Value));
        HAL_BBCR_WR(prAdapter, parBBInitTable[u2Idx].u4Offset, parBBInitTable[u2Idx].u4Value);
    }

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


