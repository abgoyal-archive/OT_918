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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/nic_eeprom.c#2 $
*/

/*! \file   nic_eeprom.c
    \brief  Functions that provide eeprom operation in NIC's (Network Interface Card) point of view.

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
** $Log: nic_eeprom.c $
 *
 * 07 10 2010 renbang.jiang
 * [ALPS00121785][Need Patch] [Volunteer Patch] use NVRAM to save Wi-Fi custom data 
 * .
 *
 * 06 13 2010 renbang.jiang
 * [ALPS00008206][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for fixing build warning 
 * .
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * [ALPS00007371] [Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license
 * .
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\14 2009-06-23 23:18:44 GMT mtk01090
**  Add build option BUILD_USE_EEPROM and compile option CFG_SUPPORT_EXT_CONFIG for NVRAM support
**  \main\maintrunk.MT5921\13 2009-01-19 12:11:55 GMT mtk01088
**  move the clock initialize function from read eeprom to normal path, avoid  the driver that not use eeprom not doing  the clock initialize
**  \main\maintrunk.MT5921\12 2008-12-01 13:56:19 GMT mtk01461
**  Remove Warning 613: Possible use of null pointer from lint
**  \main\maintrunk.MT5921\11 2008-10-16 15:55:37 GMT mtk01461
**  Update driver to fix lint warning
**  \main\maintrunk.MT5921\10 2008-08-31 11:54:06 GMT mtk01104
**  Modify some comments
**  \main\maintrunk.MT5921\9 2008-08-02 16:17:30 GMT mtk01104
**  Add assert that u2EepromSizeByte must be even number
**  \main\maintrunk.MT5921\8 2008-06-18 20:45:14 GMT mtk01084
**  fix compiling warning
**  \main\maintrunk.MT5921\7 2008-06-13 10:40:24 GMT MTK01088
**  update the 5.G Tx power for each channel, and mark some code for hard code channel 1 - 14 for g band
**  \main\maintrunk.MT5921\6 2008-04-11 00:14:57 GMT mtk01385
**  1. adopt EEPROM version 3 setting.
**  \main\maintrunk.MT5921\5 2008-03-25 22:33:22 GMT mtk01084
**  modify the power on sequence
**  \main\maintrunk.MT5921\4 2008-02-25 16:13:48 GMT mtk01385
**  1. Available phy type set honor eeprom band setting.
**  \main\maintrunk.MT5921\3 2008-02-01 10:18:07 GMT mtk01385
**  1. Fix compiling warning on Linux.
**  \main\maintrunk.MT5921\2 2008-01-31 17:58:23 GMT mtk01385
**  1. init version.
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
#if CFG_ONLY_802_11A
EEPROM_CHANNEL_CFG_ENTRY arNicEepromChannelTable[] = {
    {    0,          0,(ENUM_BAND_T)0,  {{ 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00}}, 0 },
    { CH_240,	 4920000,     BAND_5G, {{ 0x2B, 0x00, 0x00 }, { 0x2B, 0x00, 0x00 }, { 0x2B, 0x00, 0x00 }, { 0x2B, 0x00, 0x00 }, { 0x2B, 0x00, 0x00}}, 0 },
    { CH_244,	 4940000,     BAND_5G, {{ 0x2B, 0x00, 0x00 }, { 0x2B, 0x00, 0x00 }, { 0x2B, 0x00, 0x00 }, { 0x2B, 0x00, 0x00 }, { 0x2B, 0x00, 0x00}}, 0 },
    { CH_248,	 4960000,     BAND_5G, {{ 0x2A, 0x00, 0x00 }, { 0x2A, 0x00, 0x00 }, { 0x2A, 0x00, 0x00 }, { 0x2A, 0x00, 0x00 }, { 0x2A, 0x00, 0x00}}, 0 },
    { CH_252,	 4980000,     BAND_5G, {{ 0x2A, 0x00, 0x00 }, { 0x2A, 0x00, 0x00 }, { 0x2A, 0x00, 0x00 }, { 0x2A, 0x00, 0x00 }, { 0x2A, 0x00, 0x00}}, 0 },
    { CH_8, 	 5040000,     BAND_5G, {{ 0x25, 0x00, 0x00 }, { 0x25, 0x00, 0x00 }, { 0x25, 0x00, 0x00 }, { 0x25, 0x00, 0x00 }, { 0x25, 0x00, 0x00}}, 0 },
    { CH_12,	 5060000,     BAND_5G, {{ 0x25, 0x00, 0x00 }, { 0x25, 0x00, 0x00 }, { 0x25, 0x00, 0x00 }, { 0x25, 0x00, 0x00 }, { 0x25, 0x00, 0x00}}, 0 },
    { CH_16,	 5080000,     BAND_5G, {{ 0x25, 0x00, 0x00 }, { 0x25, 0x00, 0x00 }, { 0x25, 0x00, 0x00 }, { 0x25, 0x00, 0x00 }, { 0x25, 0x00, 0x00}}, 0 },
    { CH_34,	 5170000,     BAND_5G, {{ 0x27, 0x00, 0x00 }, { 0x27, 0x00, 0x00 }, { 0x27, 0x00, 0x00 }, { 0x27, 0x00, 0x00 }, { 0x27, 0x00, 0x00}}, 0 },
    { CH_36,	 5180000,     BAND_5G, {{ 0x28, 0x00, 0x00 }, { 0x28, 0x00, 0x00 }, { 0x28, 0x00, 0x00 }, { 0x28, 0x00, 0x00 }, { 0x28, 0x00, 0x00}}, 0 },
    { CH_38,	 5190000,     BAND_5G, {{ 0x29, 0x00, 0x00 }, { 0x29, 0x00, 0x00 }, { 0x29, 0x00, 0x00 }, { 0x29, 0x00, 0x00 }, { 0x29, 0x00, 0x00}}, 0 },
    { CH_40,	 5200000,     BAND_5G, {{ 0x2A, 0x00, 0x00 }, { 0x2A, 0x00, 0x00 }, { 0x2A, 0x00, 0x00 }, { 0x2A, 0x00, 0x00 }, { 0x2A, 0x00, 0x00}}, 0 },
    { CH_42,	 5210000,     BAND_5G, {{ 0x2A, 0x00, 0x00 }, { 0x2A, 0x00, 0x00 }, { 0x2A, 0x00, 0x00 }, { 0x2A, 0x00, 0x00 }, { 0x2A, 0x00, 0x00}}, 0 },
    { CH_44,	 5220000,     BAND_5G, {{ 0x2A, 0x00, 0x00 }, { 0x2A, 0x00, 0x00 }, { 0x2A, 0x00, 0x00 }, { 0x2A, 0x00, 0x00 }, { 0x2A, 0x00, 0x00}}, 0 },
    { CH_46,	 5230000,     BAND_5G, {{ 0x2E, 0x00, 0x00 }, { 0x2E, 0x00, 0x00 }, { 0x2E, 0x00, 0x00 }, { 0x2E, 0x00, 0x00 }, { 0x2E, 0x00, 0x00}}, 0 },
    { CH_48,	 5240000,     BAND_5G, {{ 0x2E, 0x00, 0x00 }, { 0x2E, 0x00, 0x00 }, { 0x2E, 0x00, 0x00 }, { 0x2E, 0x00, 0x00 }, { 0x2E, 0x00, 0x00}}, 0 },
    { CH_52,	 5260000,     BAND_5G, {{ 0x30, 0x00, 0x00 }, { 0x30, 0x00, 0x00 }, { 0x30, 0x00, 0x00 }, { 0x30, 0x00, 0x00 }, { 0x30, 0x00, 0x00}}, 0 },
    { CH_56,	 5280000,     BAND_5G, {{ 0x30, 0x00, 0x00 }, { 0x30, 0x00, 0x00 }, { 0x30, 0x00, 0x00 }, { 0x30, 0x00, 0x00 }, { 0x30, 0x00, 0x00}}, 0 },
    { CH_58,	 5300000,     BAND_5G, {{ 0x30, 0x00, 0x00 }, { 0x30, 0x00, 0x00 }, { 0x30, 0x00, 0x00 }, { 0x30, 0x00, 0x00 }, { 0x30, 0x00, 0x00}}, 0 },
    { CH_60,	 5320000,     BAND_5G, {{ 0x30, 0x00, 0x00 }, { 0x30, 0x00, 0x00 }, { 0x30, 0x00, 0x00 }, { 0x30, 0x00, 0x00 }, { 0x30, 0x00, 0x00}}, 0 },
    { CH_100,	 5500000,     BAND_5G, {{ 0x30, 0x00, 0x00 }, { 0x30, 0x00, 0x00 }, { 0x30, 0x00, 0x00 }, { 0x30, 0x00, 0x00 }, { 0x30, 0x00, 0x00}}, 0 },
    { CH_104,	 5520000,     BAND_5G, {{ 0x30, 0x00, 0x00 }, { 0x30, 0x00, 0x00 }, { 0x30, 0x00, 0x00 }, { 0x30, 0x00, 0x00 }, { 0x30, 0x00, 0x00}}, 0 },
    { CH_108,	 5540000,     BAND_5G, {{ 0x30, 0x00, 0x00 }, { 0x30, 0x00, 0x00 }, { 0x30, 0x00, 0x00 }, { 0x30, 0x00, 0x00 }, { 0x30, 0x00, 0x00}}, 0 },
    { CH_112,	 5560000,     BAND_5G, {{ 0x2F, 0x00, 0x00 }, { 0x2F, 0x00, 0x00 }, { 0x2F, 0x00, 0x00 }, { 0x2F, 0x00, 0x00 }, { 0x2F, 0x00, 0x00}}, 0 },
    { CH_116,	 5580000,     BAND_5G, {{ 0x30, 0x00, 0x00 }, { 0x30, 0x00, 0x00 }, { 0x30, 0x00, 0x00 }, { 0x30, 0x00, 0x00 }, { 0x30, 0x00, 0x00}}, 0 },
    { CH_120,	 5600000,     BAND_5G, {{ 0x30, 0x00, 0x00 }, { 0x30, 0x00, 0x00 }, { 0x30, 0x00, 0x00 }, { 0x30, 0x00, 0x00 }, { 0x30, 0x00, 0x00}}, 0 },
    { CH_124,	 5620000,     BAND_5G, {{ 0x2F, 0x00, 0x00 }, { 0x2F, 0x00, 0x00 }, { 0x2F, 0x00, 0x00 }, { 0x2F, 0x00, 0x00 }, { 0x2F, 0x00, 0x00}}, 0 },
    { CH_128,	 5640000,     BAND_5G, {{ 0x2F, 0x00, 0x00 }, { 0x2F, 0x00, 0x00 }, { 0x2F, 0x00, 0x00 }, { 0x2F, 0x00, 0x00 }, { 0x2F, 0x00, 0x00}}, 0 },
    { CH_132,	 5660000,     BAND_5G, {{ 0x2E, 0x00, 0x00 }, { 0x2E, 0x00, 0x00 }, { 0x2E, 0x00, 0x00 }, { 0x2E, 0x00, 0x00 }, { 0x2E, 0x00, 0x00}}, 0 },
    { CH_136,	 5680000,     BAND_5G, {{ 0x2E, 0x00, 0x00 }, { 0x2E, 0x00, 0x00 }, { 0x2E, 0x00, 0x00 }, { 0x2E, 0x00, 0x00 }, { 0x2E, 0x00, 0x00}}, 0 },
    { CH_140,	 5700000,     BAND_5G, {{ 0x2E, 0x00, 0x00 }, { 0x2E, 0x00, 0x00 }, { 0x2E, 0x00, 0x00 }, { 0x2E, 0x00, 0x00 }, { 0x2E, 0x00, 0x00}}, 0 },
    { CH_149,	 5745000,     BAND_5G, {{ 0x2E, 0x00, 0x00 }, { 0x2E, 0x00, 0x00 }, { 0x2E, 0x00, 0x00 }, { 0x2E, 0x00, 0x00 }, { 0x2E, 0x00, 0x00}}, 0 },
    { CH_153,	 5765000,     BAND_5G, {{ 0x2E, 0x00, 0x00 }, { 0x2E, 0x00, 0x00 }, { 0x2E, 0x00, 0x00 }, { 0x2E, 0x00, 0x00 }, { 0x2E, 0x00, 0x00}}, 0 },
    { CH_157,	 5785000,     BAND_5G, {{ 0x2E, 0x00, 0x00 }, { 0x2E, 0x00, 0x00 }, { 0x2E, 0x00, 0x00 }, { 0x2E, 0x00, 0x00 }, { 0x2E, 0x00, 0x00}}, 0 },
    { CH_161,	 5805000,     BAND_5G, {{ 0x2E, 0x00, 0x00 }, { 0x2E, 0x00, 0x00 }, { 0x2E, 0x00, 0x00 }, { 0x2E, 0x00, 0x00 }, { 0x2E, 0x00, 0x00}}, 0 }
};
#else
EEPROM_CHANNEL_CFG_ENTRY arNicEepromChannelTable[] = {
    {    0,          0,(ENUM_BAND_T)0, {{ 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00}}, 0 },
    { CH_1,    2412000,     BAND_24G, {{ 0x20, 0x0F, 0x1C }, { 0x22, 0x0D, 0x1C }, { 0x22, 0x0D, 0x1C }, { 0x22, 0x0D, 0x1C }, { 0x22, 0x0D, 0x1C}}, 0 },
    { CH_2,    2417000,     BAND_24G, {{ 0x20, 0x0F, 0x1C }, { 0x22, 0x0D, 0x1C }, { 0x22, 0x0D, 0x1C }, { 0x22, 0x0D, 0x1C }, { 0x22, 0x0D, 0x1C}}, 0 },
    { CH_3,    2422000,     BAND_24G, {{ 0x20, 0x0F, 0x1C }, { 0x22, 0x0D, 0x1C }, { 0x22, 0x0D, 0x1C }, { 0x22, 0x0D, 0x1C }, { 0x22, 0x0D, 0x1C}}, 0 },
    { CH_4,    2427000,     BAND_24G, {{ 0x20, 0x0F, 0x1C }, { 0x22, 0x0D, 0x1C }, { 0x22, 0x0D, 0x1C }, { 0x22, 0x0D, 0x1C }, { 0x22, 0x0D, 0x1C}}, 0 },
    { CH_5,    2432000,     BAND_24G, {{ 0x20, 0x0F, 0x1C }, { 0x22, 0x0D, 0x1C }, { 0x22, 0x0D, 0x1C }, { 0x22, 0x0D, 0x1C }, { 0x22, 0x0D, 0x1C}}, 0 },
    { CH_6,    2437000,     BAND_24G, {{ 0x20, 0x0F, 0x1C }, { 0x22, 0x0D, 0x1C }, { 0x22, 0x0D, 0x1C }, { 0x22, 0x0D, 0x1C }, { 0x22, 0x0D, 0x1C}}, 0 },
    { CH_7,    2442000,     BAND_24G, {{ 0x20, 0x0F, 0x1C }, { 0x22, 0x0D, 0x1C }, { 0x22, 0x0D, 0x1C }, { 0x22, 0x0D, 0x1C }, { 0x22, 0x0D, 0x1C}}, 0 },
    { CH_8,    2447000,     BAND_24G, {{ 0x20, 0x0F, 0x1C }, { 0x22, 0x0D, 0x1C }, { 0x22, 0x0D, 0x1C }, { 0x22, 0x0D, 0x1C }, { 0x22, 0x0D, 0x1C}}, 0 },
    { CH_9,    2452000,     BAND_24G, {{ 0x20, 0x0F, 0x1C }, { 0x22, 0x0D, 0x1C }, { 0x22, 0x0D, 0x1C }, { 0x22, 0x0D, 0x1C }, { 0x22, 0x0D, 0x1C}}, 0 },
    { CH_10,   2457000,     BAND_24G, {{ 0x20, 0x0F, 0x1C }, { 0x22, 0x0D, 0x1C }, { 0x22, 0x0D, 0x1C }, { 0x22, 0x0D, 0x1C }, { 0x22, 0x0D, 0x1C}}, 0 },
    { CH_11,   2462000,     BAND_24G, {{ 0x20, 0x0F, 0x1C }, { 0x22, 0x0D, 0x1C }, { 0x22, 0x0D, 0x1C }, { 0x22, 0x0D, 0x1C }, { 0x22, 0x0D, 0x1C}}, 0 },
    { CH_12,   2467000,     BAND_24G, {{ 0x20, 0x0F, 0x1C }, { 0x22, 0x0D, 0x1C }, { 0x22, 0x0D, 0x1C }, { 0x22, 0x0D, 0x1C }, { 0x22, 0x0D, 0x1C}}, 0 },
    { CH_13,   2472000,     BAND_24G, {{ 0x20, 0x0F, 0x1C }, { 0x22, 0x0D, 0x1C }, { 0x22, 0x0D, 0x1C }, { 0x22, 0x0D, 0x1C }, { 0x22, 0x0D, 0x1C}}, 0 },
    { CH_14,   2484000,     BAND_24G, {{ 0x20, 0x0F, 0x1C }, { 0x22, 0x0D, 0x1C }, { 0x22, 0x0D, 0x1C }, { 0x22, 0x0D, 0x1C }, { 0x22, 0x0D, 0x1C}}, 0 }
};
#endif

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

#if CFG_SUPPORT_EXT_CONFIG
/*----------------------------------------------------------------------------*/
/*!
* \brief Read configuration data external storage (ex. NVRAM or file)
*
* \param[in]  prAdapter      a pointer to adapter private data structure.
* \param[out] prEEPROMCtrl   a pointer to stored EEProm control data structure
*
* \retval WLAN_STATUS_SUCCESS The configuration is read completely.
* \retval WLAN_STATUS_FAILURE Fail to read correct EERPOM content
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
nicExtReadCfg (
    IN P_ADAPTER_T prAdapter,
    OUT P_EEPROM_CTRL_T prEEPROMCtrl
    )
{
    P_GLUE_INFO_T prGlueInfo;
    PUINT_16         pau2EepBuf = NULL;
    UINT_32         u4EepSizeByte;
    UINT_16         u2EepValue;
    WLAN_STATUS     rStatus = WLAN_STATUS_FAILURE;

    DEBUGFUNC("nicEepromReadCfg");

    ASSERT(prAdapter);
    ASSERT(prEEPROMCtrl);

    prGlueInfo = prAdapter->prGlueInfo;
    ASSERT(prGlueInfo);

    prEEPROMCtrl->pu4EepromChCfgTable_24 =(PUINT_32)&arNicEepromChannelTable[0];

    do {
        //4 <1> Check size
        u4EepSizeByte = kalReadExtCfg(prGlueInfo);

        if (0 == u4EepSizeByte) {
            //DBGLOG(HAL, WARN, ("Get external configuration size fail\n"));
            printk("[MT5921][nicExtReadCfg]Get external configuration size fail\n");
            break;
        }

        //4 <2> Allocate Memory Size
        //4 <3> Read configuration
        pau2EepBuf = (PUINT_16)&prGlueInfo->au2ExtCfg[0];
#if 0
        //4 <4>Verify EEPROM checksum
        if (nicEepromVerify(prAdapter, (PUINT_8)pau2EepBuf) == FALSE) {
            //ERRORLOG(("Fail to verify external configuration data\n"));
            printk("[MT5921][nicExtReadCfg]Fail to verify external configuration data\n");            
            break;
        }
#endif
        //4 <5> Map the configuration to the P_ADAPTER_P structure:
        //4 (1) Tx Power setting
        //4 (2) RF Calibration setting
        //4 (3) Other configuration
        u2EepValue = pau2EepBuf[EEPROM_CLK_CFG_VERSION];
        if ( (u2EepValue & EEPROM_LAYOUT_VERSION_MASK)
                == EEPROM_LAYOUT_VERSION_2 ) {
            if (nicEepromStoreCfgV2(prAdapter, pau2EepBuf,
                                    prEEPROMCtrl) == FALSE) {
                //DBGLOG(INIT, ERROR, ("nicEepromStoreCfgV2 return failed\n"));
                printk("[MT5921][nicExtReadCfg]nicEepromStoreCfgV2 return failed\n");                 
            }
            else {
                rStatus = WLAN_STATUS_SUCCESS;
            }
        }
        else if ( (u2EepValue & EEPROM_LAYOUT_VERSION_MASK)
                == EEPROM_LAYOUT_VERSION_3 ) {
            if (nicEepromStoreCfgV3(prAdapter, pau2EepBuf,
                                    prEEPROMCtrl) == FALSE) {
                //DBGLOG(INIT, ERROR, ("nicEepromStoreCfgV3 return failed\n"));
                printk("[MT5921][nicExtReadCfg]nicEepromStoreCfgV3 return failed\n");                    
            }
            else {
                rStatus = WLAN_STATUS_SUCCESS;
            }
        }
        else {
            //DBGLOG(INIT, ERROR, ("NVRAM version %d does not support.\n", 
            // (u2EepValue >> EEPROM_LAYOUT_VERSION_OFFSET)));
            printk("[MT5921][nicExtReadCfg]NVRAM version does not support.\n");                
        }
    } while(FALSE);

    return rStatus;
}
#endif /* CFG_SUPPORT_EXT_CONFIG */

/*----------------------------------------------------------------------------*/
/*!
* \brief Read configuration data from EEPROM and store into specified area
*
* \param[in]  prAdapter      a pointer to adapter private data structure.
* \param[out] prEEPROMCtrl   a pointer to stored EEProm control data structure
*
* \retval WLAN_STATUS_SUCCESS The configuration is read completely.
* \retval WLAN_STATUS_FAILURE Fail to read correct EERPOM content
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
nicEepromReadCfg (
    IN P_ADAPTER_T prAdapter,
    OUT P_EEPROM_CTRL_T prEEPROMCtrl
    )
{
    UINT_16         u2EepSizeByte;
    PUINT_8         paucEepBuf = NULL;
    UINT_16         u2EepValue;
    WLAN_STATUS     rStatus = WLAN_STATUS_FAILURE;

    DEBUGFUNC("nicEepromReadCfg");

    ASSERT(prAdapter);
    ASSERT(prEEPROMCtrl);

    prEEPROMCtrl->pu4EepromChCfgTable_24 =(PUINT_32)&arNicEepromChannelTable[0];

    do {
        //4 <1> Check EEPROM size
        u2EepSizeByte = halEepromGetSize( prAdapter);

        if (u2EepSizeByte == 0) {
            DBGLOG(HAL, WARN, ("Get EEPROM size fail\n"));
            break;
        }

        //4 <2> Allocate Memory Size for EEPROM
        paucEepBuf = (PUINT_8) kalMemAlloc((UINT_32)u2EepSizeByte);
        if (!paucEepBuf) {
            DBGLOG(HAL, WARN, ("Memory allocate failed. size = %d bytes\n",\
                u2EepSizeByte));
            break;
        }


        //4 <3> Read configuration from EEPROM
        if (nicEepromLoad(prAdapter, paucEepBuf, u2EepSizeByte) == 0) {
            ERRORLOG(("Fail to load EEPROM\n"));
            break;
        }

        //4 <4>Verify EEPROM
        if (nicEepromVerify(prAdapter, paucEepBuf) == FALSE) {
            ERRORLOG(("Fail to verify EEPROM\n"));
            break;

        }

    //4 <5> Map the configuration to the P_ADAPTER_P structure:
    //4 (1) Tx Power setting
    //4 (2) RF Calibration setting
    //4 (3) Other configuration


        u2EepValue = ((PUINT_16)paucEepBuf)[EEPROM_CLK_CFG_VERSION];
        if ( (u2EepValue & EEPROM_LAYOUT_VERSION_MASK)
                == EEPROM_LAYOUT_VERSION_2 ) {
            if (nicEepromStoreCfgV2(prAdapter, (PUINT_16)paucEepBuf,
                                    prEEPROMCtrl) == FALSE) {
                DBGLOG(INIT, ERROR, ("nicEepromStoreCfgV2 return failed\n"));
            }
            else {
                rStatus = WLAN_STATUS_SUCCESS;
            }
        }
        else if ( (u2EepValue & EEPROM_LAYOUT_VERSION_MASK)
                == EEPROM_LAYOUT_VERSION_3 ) {
            if (nicEepromStoreCfgV3(prAdapter, (PUINT_16)paucEepBuf,
                                    prEEPROMCtrl) == FALSE) {
                DBGLOG(INIT, ERROR, ("nicEepromStoreCfgV3 return failed\n"));
            }
            else {
                rStatus = WLAN_STATUS_SUCCESS;
            }
        }
        else {
            DBGLOG(INIT, ERROR, ("EEPROM version %d does not support.\n", \
             (u2EepValue >> EEPROM_LAYOUT_VERSION_OFFSET)));
        }
    //4 (4) MAC address
    } while(FALSE);

    if (paucEepBuf != NULL) {
        kalMemFree((PVOID)paucEepBuf, u2EepSizeByte);
    }

    return rStatus;
}


/*----------------------------------------------------------------------------*/
/*!
* \brief Load eeprom content from NIC card to S/W buffer.
*
* \param[in]  prAdapter      a pointer to adapter private data structure.
* \param[out] paucEeprom     Pointer to the EEPROM output buffer
* \param[in]  u2EepromSz     max given eeprom buffer size in unit of byte
*
* \return non-zero - EEPROM size in unit of byte
*             zero - error or EEPROM non-present
*/
/*----------------------------------------------------------------------------*/
UINT_16
nicEepromLoad (
    IN  P_ADAPTER_T prAdapter,
    OUT PUINT_8     paucEeprom,
    IN  UINT_16     u2EepromSzIn
    )
{
    UINT_16  u2I, u2EepromValue, u2EepromSizeByte = 0, u2EepromWordLen;


    ASSERT(prAdapter);
    ASSERT(paucEeprom);

    u2EepromSizeByte = halEepromGetSize(prAdapter);

    ASSERT((u2EepromSizeByte & 0x0001) == 0);

    if (u2EepromSzIn < u2EepromSizeByte) {
        return 0;
    }

    u2EepromWordLen = (u2EepromSizeByte/2);

    for (u2I =0; u2I < u2EepromWordLen; u2I ++) {
        halEepromRead16(prAdapter, (UINT_8)u2I, &u2EepromValue);
        #if 0
        paucEeprom[2 * u2I    ] = (UINT_8)u2EepromValue;
        paucEeprom[2 * u2I + 1] = (UINT_8)(u2EepromValue >> 8);
        #else
        /*what will it be if use memcpy, ok in x86 platform*/
        kalMemCopy(&paucEeprom[2 * u2I], &u2EepromValue, sizeof(u2EepromValue));
        #endif
    }

    return u2EepromSizeByte;
} /* nicEepromLoad */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine calculates the 8-bit checksum of a memory block.
*
* \param[in]  paucEepromBuf      The starting address of the memory block to
*                               calculate checksum
* \param[in]  u2LenByte          The length of the given memory block
* \param[out] pucRetChksum       Pointer to the 8-bit calculated checksum
*
* \return NONE
*/
/*----------------------------------------------------------------------------*/
VOID
nicEepromCalculateChecksumByte (
    IN  PUINT_8 paucEepromBuf,
    IN  UINT_16 u2LenByte,
    OUT PUINT_8 pucRetChksum
    )
{
    UINT_16   u2I;
    PUINT_8   pucBuf;


    ASSERT(paucEepromBuf);
    ASSERT(pucRetChksum);

    *pucRetChksum = 0;
    pucBuf = paucEepromBuf;
    for (u2I = 0; u2I < u2LenByte; u2I++, pucBuf++) {
        *pucRetChksum += *pucBuf;
    }

    return;
} /* nicEepromCalculateChecksumByte */

/*----------------------------------------------------------------------------*/
/*!
* \brief Run NIC dependent EEPROM content verification. This does not
*        include HIF and CIS's checksum.
*
* \param[in] prAdapter       Pointer to the Adapter structure
* \param[in] paucEepromBuf   given eeprom buffer
*
* \return TRUE  - NIC EEPROM setting is valid
*         FALSE - NIC EEPROM setting is invalid
*/
/*----------------------------------------------------------------------------*/
BOOL
nicEepromVerify (
    IN  P_ADAPTER_T prAdapter,
    IN  PUINT_8     paucEepromBuf
    )
{
    UINT_8  ucChksum;
    UINT_16 u2Len;

    DEBUGFUNC("nicEepromVerify");


    ASSERT(prAdapter);
    ASSERT(paucEepromBuf);

    u2Len = (EEPROM_NIC_CHKSUM_ADD_DW - EEPROM_NIC_CHKSUM_START_ADD_DW + 1) * 2;

    /* 5921 Start NIC EEPROM Checksum from 0x0D ~ 0x9F */
    nicEepromCalculateChecksumByte(
        &paucEepromBuf[EEPROM_NIC_CHKSUM_START_ADD_DW *2],
        u2Len, &ucChksum);

    DBGLOG(INIT, INFO, ("EEPROM length: %d, Checksum: %2x\n", u2Len, ucChksum));

    if (ucChksum != 0xFF) {
        return FALSE;
    }
    else {
        return TRUE;
    }
} /* nicEepromVerify */


/*----------------------------------------------------------------------------*/
/*!
* \brief store version 2 eeprom content to Adapter sturcture.
*        This function should be phase out soon.
*
* \param[in] prAdapter      a pointer to adapter private data structure.
* \param[in] pau2Eeprom     Pointer to the EEPROM buffer in UINT_16 format
* \param[out] prEEPROMCtrl  a pointer to stored EEProm control data structure
*
* \return TRUE  - NIC EEPROM setting store ok
*         FALSE - NIC EEPROM setting store failed.
*/
/*----------------------------------------------------------------------------*/
BOOL
nicEepromStoreCfgV2 (
    IN  P_ADAPTER_T prAdapter,
    IN  PUINT_16       pau2Eeprom,
    OUT P_EEPROM_CTRL_T prEEPROMCtrl
    )
{
    PUINT_8 paucEeprom;
    UINT_16 u2EepValue;
    UINT_16 u2I;
#if !CFG_ONLY_802_11A
    UINT_16 u2J;
    UINT_16 ucByteOffset;
#endif
    P_EEPROM_CHANNEL_CFG_ENTRY prEepChCfg;

    DEBUGFUNC("nicEepromStoreCfgV2");

    ASSERT(prAdapter);
    ASSERT(prEEPROMCtrl);
    ASSERT(pau2Eeprom);


    paucEeprom = (PUINT_8)pau2Eeprom;

    /*Domain*/
    u2EepValue = pau2Eeprom[EEPROM_REG_DOMAIN];
    DBGLOG(INIT, INFO, ("EEPROM word offset 0x%02x: 0x%04x (reg domain)\n",\
                    EEPROM_REG_DOMAIN, u2EepValue));

    /* Domain is put as byte string in EEPROM.
    ** Therefore, the lower byte is the first character
    ** But, driver put the the first character in higher byte. */
    prEEPROMCtrl->u4RegulationDomain= (u2EepValue & BITS(0,7)) <<8;
    prEEPROMCtrl->u4RegulationDomain |= (((u2EepValue ) >> 8)&BITS(0,7)) ;

    /*OSC StableTime*/
    prEEPROMCtrl->u2OscStableTimeUs = pau2Eeprom[EEPROM_OSC_STABLE_TIME];


    u2EepValue = pau2Eeprom[EEPROM_LED_MODE_XTAL_FREQ_TRIM];
    /*LED Blink Mode*/
    prEEPROMCtrl->ucLedBlinkMode =
            (UINT_8) (u2EepValue & EEPROM_LED_MODE_MASK) ;
    /*store XTAL*/
    prEEPROMCtrl->ucXtalTrim =
      (UINT_8)( (u2EepValue & EEPROM_XTAL_FREQ_MASK ) >> EEPROM_XTAL_FREQ_OFFSET);

    /*Slow Clock Config*/
    u2EepValue = pau2Eeprom[EEPROM_CLK_CFG_VERSION];
    prEEPROMCtrl->ucSlowClkCfg =
             (UINT_8) (u2EepValue & EEPROM_SLOW_CLK_CFG_MASK );

    /*MAC Address*/
    for (u2I = 0; u2I< 3; u2I++) {
        u2EepValue = pau2Eeprom[EEPROM_MAC_ADDR_BYTE_1_0 + u2I];
        DBGLOG(INIT, INFO, ("EEPROM word offset 0x%02x: 0x%04x\n",
            (UINT_8) (EEPROM_MAC_ADDR_BYTE_1_0 + u2I), u2EepValue));
        prEEPROMCtrl->aucMacAddress[u2I * 2] =
            (UINT_8) (u2EepValue & 0x00FF);
        prEEPROMCtrl->aucMacAddress[u2I * 2 + 1] =
            (UINT_8) (u2EepValue >> 8);
    }

    u2EepValue = pau2Eeprom[EEPROM_THERMO_USAGE_BAND_SEL];

#if CFG_ONLY_802_11A
    /*Band Select*/
    prEEPROMCtrl->ucBandSelect = EEPROM_PHY_MODE_A;
    /*Thermo-Sensor Usage*/
    prEEPROMCtrl->fgAlcUseThermoEn = FALSE;
    prEEPROMCtrl->fgLnaUseThermoEn = FALSE;
#else
    /*Band Select*/
    prEEPROMCtrl->ucBandSelect =
             (UINT_8) (u2EepValue & EEPROM_BAND_MODE_MASK);
    /*Thermo-Sensor Usage*/
    prEEPROMCtrl->fgAlcUseThermoEn =
        ( (u2EepValue & EEPROM_THERMO_ALC_EN_MASK) ==  EEPROM_THERMO_ALC_EN) ? \
                TRUE: FALSE;
    prEEPROMCtrl->fgLnaUseThermoEn =
        ( (u2EepValue & EEPROM_THERMO_LNA_EN_MASK) ==  EEPROM_THERMO_LNA_EN) ? \
                TRUE: FALSE;
#endif
    /*VGA & Thermo slop*/
    u2EepValue = pau2Eeprom[EEPROM_THERMO_VGA_SLOPE];
    prEEPROMCtrl->ucVgaGainSlop =
            (UINT_8)( (u2EepValue & EEPROM_VGA_SLOPE_MASK) >> EEPROM_VGA_SLOPE_OFFSET );
    prEEPROMCtrl->ucThermoSensorSlop =
            (UINT_8)( (u2EepValue & EEPROM_THERMO_SLOPE_MASK) >> EEPROM_THERMO_SLOPE_OFFSET );

    if( prEEPROMCtrl->ucThermoSensorSlop == 0) {
        prEEPROMCtrl->ucThermoSensorSlop = EEPROM_THERMO_SLOPE_DEFAULT_VALUE;
        DBGLOG(INIT, ERROR, ("Thermo Slop value is 0 and it cause /0 error, set to defaul value %d.\n",
            prEEPROMCtrl->ucThermoSensorSlop));

    }


    /*PerChannel{gain , EIRP, thermo-value}*/
    prEepChCfg = (P_EEPROM_CHANNEL_CFG_ENTRY)prEEPROMCtrl->pu4EepromChCfgTable_24;
#if CFG_ONLY_802_11A
#else

    for ( u2I = EEPROM_RATE_GROUP_CCK; u2I <= EEPROM_RATE_GROUP_OFDM_48_54M; u2I++) {
        for ( u2J = CH_1; u2J <= CH_14; u2J++ ) {
            ucByteOffset = ( EEPROM_2G_CCK_TXPWR_GAIN_START + \
                (EEPROM_2G_CCK_TXPWR_GAIN_END - EEPROM_2G_CCK_TXPWR_GAIN_START +1)*u2I )*2 + \
                  (u2J-1)*3;
            prEepChCfg[u2J].rTxCfg[u2I].ucPowerGain =
                paucEeprom[ucByteOffset+ 0];
            prEepChCfg[u2J].rTxCfg[u2I].ucEIRP =
                paucEeprom[ucByteOffset+ 1];
            prEepChCfg[u2J].rTxCfg[u2I].ucThermoVal=
                paucEeprom[ucByteOffset+ 2];
        }
    }
#endif
    /*LNA*/
    prEEPROMCtrl->cAbsTemp = EEPROM_V3_THERMO_INFO_ABS_TEMP_DEFAULT;
    prEEPROMCtrl->ucThermoValue = EEPROM_V3_THERMO_INFO_THERMO_VAL_DEFAULT;
    /*PerChannel RCPI offset*/

    return TRUE;

} /* nicEepromStoreCfgV2 */

/*----------------------------------------------------------------------------*/
/*!
* \brief init u2AvailablePhyTypeSet value base on eeprom content.
*
* \param[in]  prEEPROMCtrl  a pointer to stored EEProm control data structure
* \param[out] pu2AvailablePhyTypeSet Pointer to AvailablePhyTypeSet variable
*
* \return None
*/
/*----------------------------------------------------------------------------*/
VOID
nicEepromGetAvailablePhyTypeSet (
    IN P_EEPROM_CTRL_T prEEPROMCtrl,
    OUT PUINT_16       pu2AvailablePhyTypeSet
    )
{
    DEBUGFUNC("nicEepromSetAvailablePhyTypeSet");


    ASSERT(prEEPROMCtrl);
    ASSERT(pu2AvailablePhyTypeSet);

    switch(prEEPROMCtrl->ucBandSelect) {
    case EEPROM_PHY_MODE_G:
        *pu2AvailablePhyTypeSet = (UINT_16)PHY_TYPE_SET_802_11BG;
        break;
    case EEPROM_PHY_MODE_A_G:
        *pu2AvailablePhyTypeSet = (UINT_16)PHY_TYPE_SET_802_11ABG;
        break;
    case EEPROM_PHY_MODE_A:
        *pu2AvailablePhyTypeSet = (UINT_16)PHY_TYPE_SET_802_11A;
        break;
    default:
        *pu2AvailablePhyTypeSet = (UINT_16)PHY_TYPE_SET_802_11ABG;
        break;

    }

    return;
} /* end of nicEepromSetAvailablePhyTypeSet() */

/*----------------------------------------------------------------------------*/
/*!
* \brief store version 3 eeprom content to Adapter sturcture.
*        Note: this function is only for little-endian now.
*
* \param[in]  prAdapter      a pointer to adapter private data structure.
* \param[in]  pau2Eeprom     Pointer to the EEPROM buffer in UINT_16 format
* \param[out] prEEPROMCtrl   a pointer to stored EEProm control data structure
*
* \return TRUE  - NIC EEPROM setting store ok
*         FALSE - NIC EEPROM setting store failed.
*/
/*----------------------------------------------------------------------------*/
BOOL
nicEepromStoreCfgV3 (
    IN  P_ADAPTER_T prAdapter,
    IN  PUINT_16       pau2Eeprom,
    OUT P_EEPROM_CTRL_T prEEPROMCtrl
    )
{
    PUINT_8 paucEeprom;
    UINT_16 u2EepValue;
    UINT_16 u2I;
#if !CFG_ONLY_802_11A
    UINT_16 u2J;
    UINT_16 ucByteOffset;
#endif
    P_EEPROM_CHANNEL_CFG_ENTRY prEepChCfg;

    DEBUGFUNC("nicEepromStoreCfgV3");

    ASSERT(prAdapter);
    ASSERT(prEEPROMCtrl);
    ASSERT(pau2Eeprom);

    paucEeprom = (PUINT_8)pau2Eeprom;

    /* Domain */
    u2EepValue = pau2Eeprom[EEPROM_REG_DOMAIN];
    DBGLOG(INIT, INFO, ("EEPROM word offset 0x%02x: 0x%04x (reg domain)\n",\
                    EEPROM_REG_DOMAIN, u2EepValue));

    /* Domain is put as byte string in EEPROM.
     * Therefore, the lower byte is the first character
     * But, driver put the the first character in higher byte.
     */
    prEEPROMCtrl->u4RegulationDomain= (u2EepValue & BITS(0,7)) << 8;
    prEEPROMCtrl->u4RegulationDomain |= (((u2EepValue ) >> 8) & BITS(0,7)) ;

    /* OSC StableTime */
    prEEPROMCtrl->u2OscStableTimeUs = pau2Eeprom[EEPROM_OSC_STABLE_TIME];

    /* LED Blink Mode */
    u2EepValue = pau2Eeprom[EEPROM_LED_MODE_XTAL_FREQ_TRIM];
    prEEPROMCtrl->ucLedBlinkMode =
            (UINT_8) (u2EepValue & EEPROM_LED_MODE_MASK) ;

    /* Store XTAL */
    prEEPROMCtrl->ucXtalTrim =
      (UINT_8)((u2EepValue & EEPROM_XTAL_FREQ_MASK) >> EEPROM_XTAL_FREQ_OFFSET);

    /* Slow Clock Config */
    u2EepValue = pau2Eeprom[EEPROM_CLK_CFG_VERSION];
    prEEPROMCtrl->ucSlowClkCfg =
             (UINT_8) (u2EepValue & EEPROM_SLOW_CLK_CFG_MASK );

    /* MAC Address */
    for (u2I = 0; u2I< 3; u2I++) {
        u2EepValue = pau2Eeprom[EEPROM_MAC_ADDR_BYTE_1_0 + u2I];
        DBGLOG(INIT, INFO, ("EEPROM word offset 0x%02x: 0x%04x\n",
            (UINT_8) (EEPROM_MAC_ADDR_BYTE_1_0 + u2I), u2EepValue));
        prEEPROMCtrl->aucMacAddress[u2I * 2] =
            (UINT_8) (u2EepValue & 0x00FF);
        prEEPROMCtrl->aucMacAddress[u2I * 2 + 1] =
            (UINT_8) (u2EepValue >> 8);
    }

    u2EepValue = pau2Eeprom[EEPROM_THERMO_USAGE_BAND_SEL];
#if CFG_ONLY_802_11A
    /* Band Select */
    prEEPROMCtrl->ucBandSelect = EEPROM_PHY_MODE_A;
    /* Thermo-Sensor Usage */
    prEEPROMCtrl->fgAlcUseThermoEn = FALSE;
    prEEPROMCtrl->fgLnaUseThermoEn = FALSE;
#else
    /* Band Select */
    prEEPROMCtrl->ucBandSelect =
             (UINT_8) (u2EepValue & EEPROM_BAND_MODE_MASK);
    /* Thermo-Sensor Usage */
    prEEPROMCtrl->fgAlcUseThermoEn =
        ((u2EepValue & EEPROM_THERMO_ALC_EN_MASK) ==  EEPROM_THERMO_ALC_EN) ? \
                TRUE: FALSE;
    prEEPROMCtrl->fgLnaUseThermoEn =
        ((u2EepValue & EEPROM_THERMO_LNA_EN_MASK) ==  EEPROM_THERMO_LNA_EN) ? \
                TRUE: FALSE;
#endif

    /* VGA & Thermo slope */
    u2EepValue = pau2Eeprom[EEPROM_THERMO_VGA_SLOPE];
    prEEPROMCtrl->ucVgaGainSlop =
            (UINT_8)( (u2EepValue & EEPROM_VGA_SLOPE_MASK) >> EEPROM_VGA_SLOPE_OFFSET );
    prEEPROMCtrl->ucThermoSensorSlop =
            (UINT_8)( (u2EepValue & EEPROM_THERMO_SLOPE_MASK) >> EEPROM_THERMO_SLOPE_OFFSET );

    if (prEEPROMCtrl->ucThermoSensorSlop == 0) {
        prEEPROMCtrl->ucThermoSensorSlop = EEPROM_THERMO_SLOPE_DEFAULT_VALUE;
        DBGLOG(INIT, ERROR, ("Thermo Slop value is 0 and it cause /0 error, set to defaul value %d.\n",
            prEEPROMCtrl->ucThermoSensorSlop));
    }

    /* PerChannel{gain , EIRP, thermo-value} */
    prEepChCfg = (P_EEPROM_CHANNEL_CFG_ENTRY)
                    prEEPROMCtrl->pu4EepromChCfgTable_24;

#if CFG_ONLY_802_11A
#else
    for ( u2I = EEPROM_RATE_GROUP_CCK; u2I <= EEPROM_RATE_GROUP_OFDM_48_54M; u2I++) {
        for ( u2J = CH_1; u2J <= CH_14; u2J++ ) {
            ucByteOffset = ( EEPROM_2G_CCK_TXPWR_GAIN_START + \
                (EEPROM_2G_CCK_TXPWR_GAIN_END - EEPROM_2G_CCK_TXPWR_GAIN_START +1)*u2I )*2 + \
                  (u2J-1)*3;
            prEepChCfg[u2J].rTxCfg[u2I].ucPowerGain =
                paucEeprom[ucByteOffset+ 0];
            prEepChCfg[u2J].rTxCfg[u2I].ucEIRP =
                paucEeprom[ucByteOffset+ 1];
            prEepChCfg[u2J].rTxCfg[u2I].ucThermoVal=
                paucEeprom[ucByteOffset+ 2];
        }
    }
#endif

    /* LNA */
    u2EepValue = pau2Eeprom[EEPROM_V3_THERMO_INFO];
    prEEPROMCtrl->cAbsTemp =
            (UINT_8)( (u2EepValue & EEPROM_V3_THERMO_INFO_ABS_TEMP_MASK) >> EEPROM_V3_THERMO_INFO_ABS_TEMP_OFFSET);
    prEEPROMCtrl->ucThermoValue =
            (UINT_8)( (u2EepValue & EEPROM_V3_THERMO_INFO_THERMO_VALUE_MASK) >> EEPROM_V3_THERMO_INFO_THERMO_VALUE_OFFSET);

    /*PerChannel RCPI offset*/

    /* Daisy chain config for shared OSC */
    u2EepValue = pau2Eeprom[EEPROM_DAISY];
    //prEEPROMCtrl->ucDaisyChain = (UINT_8)(u2EepValue >> 8);
    prEEPROMCtrl->ucDaisyChain = gPlatformCfg.rWifiCustom.u4DaisyChainEnable;

    return TRUE;
} /* nicEepromStoreCfgV3 */

