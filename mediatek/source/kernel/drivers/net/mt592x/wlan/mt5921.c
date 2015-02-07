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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/mt5921.c#1 $
*/

/*! \file   "mt5921.c"
    \brief  The collection of MT5921-specific hw functions

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
** $Log: mt5921.c $
 *
 * 07 10 2010 renbang.jiang
 * [ALPS00121785][Need Patch] [Volunteer Patch] use NVRAM to save Wi-Fi custom data 
 * .
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\12 2008-11-13 20:34:17 GMT mtk01104
**  Set xtal trim to correct default value if EEPROM is invalid
**  \main\maintrunk.MT5921\11 2008-10-29 10:59:59 GMT mtk01088
**  update coding style for lint warning
**  \main\maintrunk.MT5921\10 2008-08-22 17:24:23 GMT mtk01088
**  remove non-used function call declaration
**  \main\maintrunk.MT5921\9 2008-06-12 20:28:46 GMT mtk01461
**  Add 11A PHY capability to MT5921
**  \main\maintrunk.MT5921\8 2008-04-11 00:22:52 GMT mtk01385
**  1. adopt EEPROM version 3 setting.
**  \main\maintrunk.MT5921\7 2008-03-31 00:32:45 GMT mtk01385
**  1. set vga gain/thermo sensor slopes default value to eeprom control info object.
**  \main\maintrunk.MT5921\6 2008-03-28 10:11:53 GMT mtk01461
**  Add default setting for MCR_BCWR
**  \main\maintrunk.MT5921\5 2008-03-18 13:56:17 GMT mtk01088
**  add code from MPW branch
**  \main\maintrunk.MT5921\4 2008-02-25 16:15:13 GMT mtk01385
**  1. set default band select value to 11G mode.
**  \main\maintrunk.MT5921\3 2008-01-07 15:07:13 GMT mtk01461
**  Add PhyType & AdHocMode Selection Support
**  \main\maintrunk.MT5921\2 2007-11-06 19:59:53 GMT mtk01088
**  just check in the code, not compiler at this config
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
REG_ENTRY_T arMACInitValue[] = {
    {MCR_BCWR,         0x0000001f}, /* NOTE(2008/03/27): CR412 - Set to 0x1f for WiFi */
    {MCR_OFPR,         0x22222222},
    {MCR_CFPR,         0x00000020},
    {MCR_ACDR2,        0xC0000000}
};

extern WIFI_CFG_DATA gPlatformCfg;

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
    IN P_ADAPTER_T       prAdapter
    )
{
    UINT_16 u2Idx = 0;
    UINT_16 u2Size = sizeof(arMACInitValue)/sizeof(REG_ENTRY_T);

    ASSERT(prAdapter);

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
    ASSERT(prEEPROMCtrl);

    prEEPROMCtrl->u4RegulationDomain = REGULATION_DOMAIN_FCC;
    prEEPROMCtrl->ucBandSelect = EEPROM_PHY_MODE_G;
    prEEPROMCtrl->ucVgaGainSlop = DEFAULT_VAG_GAIN_SLOPE;
    prEEPROMCtrl->ucThermoSensorSlop = DEFAULT_THERMO_SLOPE;
    prEEPROMCtrl->cAbsTemp = EEPROM_V3_THERMO_INFO_ABS_TEMP_DEFAULT;
    prEEPROMCtrl->ucThermoValue = EEPROM_V3_THERMO_INFO_THERMO_VAL_DEFAULT;
    prEEPROMCtrl->ucXtalTrim = EEPROM_XTAL_TRIM_VAL_DEFAULT;
    prEEPROMCtrl->u2OscStableTimeUs = EEPROM_OSC_STABLE_TIME_VAL_DEFAULT;
    prEEPROMCtrl->fgAlcUseThermoEn = EEPROM_ALC_USE_THERMO_EN_VAL_DEFAULT;
    prEEPROMCtrl->fgLnaUseThermoEn = EEPROM_LNA_USE_THERMO_EN_VAL_DEFAULT;
    prEEPROMCtrl->ucDaisyChain = gPlatformCfg.rWifiCustom.u4DaisyChainEnable;
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
    ASSERT(pu2PhyTypeSet);

    *pu2PhyTypeSet = (UINT_16)(PHY_TYPE_BIT_HR_DSSS | PHY_TYPE_BIT_ERP | PHY_TYPE_BIT_OFDM);

    return;
}





