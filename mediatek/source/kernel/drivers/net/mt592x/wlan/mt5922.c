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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/mt5922.c#1 $
*/

/*! \file   "mt5922.c"
    \brief  The collection of MT5922-specific hw functions

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
** $Log: mt5922.c $
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\15 2008-11-13 20:34:31 GMT mtk01104
**  Set xtal trim to correct default value if EEPROM is invalid
**  \main\maintrunk.MT5921\14 2008-08-22 17:58:12 GMT mtk01088
**  add function declaration
**  \main\maintrunk.MT5921\13 2008-04-11 00:26:12 GMT mtk01385
**  1. adopt EEPROM version 3 setting.
**  \main\maintrunk.MT5921\12 2008-03-31 00:33:32 GMT mtk01385
**  1. set vga gain/thermo sensor slopes default value to eeprom control info object.
**  \main\maintrunk.MT5921\11 2008-03-28 10:12:04 GMT mtk01461
**  Add default setting for MCR_BCWR
**  \main\maintrunk.MT5921\10 2008-02-25 16:15:49 GMT mtk01385
**  1. set default band select value to 11G mode.
**  \main\maintrunk.MT5921\9 2008-02-21 15:01:51 GMT mtk01461
**  Remove wrongly update to MCR 0x0100
**  \main\maintrunk.MT5921\8 2008-01-07 15:07:16 GMT mtk01461
**  Add PhyType & AdHocMode Selection Support
**  \main\maintrunk.MT5921\7 2007-11-29 15:51:15 GMT mtk01461
**  Update MCR 0x100, for duration cover next frame in TXOP
**  \main\maintrunk.MT5921\6 2007-11-07 16:33:30 GMT mtk01088
**  add the initial value
**  \main\maintrunk.MT5921\5 2007-11-06 19:53:03 GMT mtk01088
**  The CW is different for different RF
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

/*******************************************************************************
*                              C O N S T A N T S
********************************************************************************
*/
REG_ENTRY_T arMACInitValue[] = {
    {MCR_BCWR,       0x0000001f}, /* NOTE(2008/03/27): CR412 - Set to 0x1f for WiFi */
    {0x114,         0x2a2a2a2a},
    {0x118,         0x0000002a},

#if 0 //SUPPORT_802_11A
    {MCR_RICR,      0x001E0E00},
#else
    {MCR_RICR,      0x001C0E00},
#endif
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

/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/

/*----------------------------------------------------------------------------*/
/*!
* \brief This function use to set the default mcr value. and maybe update by
*        following procedure, like EEPROM
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
halMCRChipInit (
    IN P_ADAPTER_T prAdapter
    )
{
    UINT_16 u2Idx = 0;
    UINT_16 u2Size = sizeof(arMACInitValue)/sizeof(REG_ENTRY_T);

    for (u2Idx = 0; u2Idx < u2Size; u2Idx++) {
        HAL_MCR_WR(prAdapter, arMACInitValue[u2Idx].u4Offset, arMACInitValue[u2Idx].u4Value);
    }
}


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will use to set the default setting if EEPROM not present.
*
* \param[in] prEEPROMCtrl  Pointer to the EEPROM container.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
halGetDefaultEEPROMCfg (
    IN P_EEPROM_CTRL_T prEEPROMCtrl
    )
{
    prEEPROMCtrl->u4RegulationDomain = REGULATION_DOMAIN_FCC;
    prEEPROMCtrl->ucID = DEFAULT_DAC_OFFSET_ID;
    prEEPROMCtrl->ucQD = DEFAULT_DAC_OFFSET_QD;
    prEEPROMCtrl->ucBandSelect = EEPROM_PHY_MODE_G;
    prEEPROMCtrl->ucVgaGainSlop = DEFAULT_VAG_GAIN_SLOPE;
    prEEPROMCtrl->ucThermoSensorSlop = DEFAULT_THERMO_SLOPE;
    prEEPROMCtrl->cAbsTemp = EEPROM_V3_THERMO_INFO_ABS_TEMP_DEFAULT;
    prEEPROMCtrl->ucThermoValue = EEPROM_V3_THERMO_INFO_THERMO_VAL_DEFAULT;
    prEEPROMCtrl->ucXtalTrim = EEPROM_XTAL_TRIM_VAL_DEFAULT;
    prEEPROMCtrl->u2OscStableTimeUs = EEPROM_OSC_STABLE_TIME_VAL_DEFAULT;
    prEEPROMCtrl->fgAlcUseThermoEn = EEPROM_ALC_USE_THERMO_EN_VAL_DEFAULT;
    prEEPROMCtrl->fgLnaUseThermoEn = EEPROM_LNA_USE_THERMO_EN_VAL_DEFAULT;
    prEEPROMCtrl->ucDaisyChain = EEPROM_DAISY_CHAIN_VAL_DEFAULT;

    halRFSetInitTable(prEEPROMCtrl);
}


/*----------------------------------------------------------------------------*/
/*!
* \brief This function use to get the chip supported phy type.
*
* \param[in] pu2PhyTypeSet  Pointer to input phy type.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
halGetSupportedPhyTypeSet (
    IN PUINT_16 pu2PhyTypeSet
    )
{
    *pu2PhyTypeSet = (UINT_16)(PHY_TYPE_BIT_HR_DSSS | PHY_TYPE_BIT_ERP);

    return;
}

