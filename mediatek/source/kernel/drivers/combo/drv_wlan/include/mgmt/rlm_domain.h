/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. and/or its licensors.
 * Without the prior written permission of MediaTek inc. and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 *
 * MediaTek Inc. (C) 2010. All rights reserved.
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
** $Id: //Department/DaVinci/BRANCHES/MT6620_WIFI_DRIVER_V1_2/include/mgmt/rlm_domain.h#1 $
*/

/*! \file   "rlm_domain.h"
    \brief
*/

/*******************************************************************************
* Copyright (c) 2009 MediaTek Inc.
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
** $Log: rlm_domain.h $
 *
 * 02 09 2011 cp.wu
 * [WCXRP00000430] [MT6620 Wi-Fi][Firmware][Driver] Create V1.2 branch for MT6620E1 and MT6620E3
 * create V1.2 driver branch based on label MT6620_WIFI_DRIVER_V1_2_110209_1031 
 * with BOW and P2P enabled as default
 *
 * 12 07 2010 cm.chang
 * [WCXRP00000238] MT6620 Wi-Fi][Driver][FW] Support regulation domain setting from NVRAM and supplicant
 * 1. Country code is from NVRAM or supplicant
 * 2. Change band definition in CMD/EVENT.
 *
 * 07 08 2010 cp.wu
 *
 * [WPD00003833] [MT6620 and MT5931] Driver migration - move to new repository.
 *
 * 06 28 2010 cm.chang
 * [WPD00003841][LITE Driver] Migrate RLM/CNM to host driver
 * 1st draft code for RLM module
 *
 * 02 23 2010 kevin.huang
 * [BORA00000603][WIFISYS] [New Feature] AAA Module Support
 * Add support scan channel 1~14 and update scan result's frequency infou1rwduu`wvpghlqg|n`slk+mpdkb
 *
 * 01 13 2010 cm.chang
 * [BORA00000018]Integrate WIFI part into BORA for the 1st time
 * Provide query function about full channle list.
 *
 * Dec 1 2009 mtk01104
 * [BORA00000018] Integrate WIFI part into BORA for the 1st time
 * Declare public rDomainInfo
 *
**
*/

#ifndef _RLM_DOMAIN_H
#define _RLM_DOMAIN_H

/*******************************************************************************
*                         C O M P I L E R   F L A G S
********************************************************************************
*/

/*******************************************************************************
*                    E X T E R N A L   R E F E R E N C E S
********************************************************************************
*/

/*******************************************************************************
*                              C O N S T A N T S
********************************************************************************
*/
#define MAX_SUBBAND_NUM     6


#define COUNTRY_CODE_NULL               ((UINT_16)0x0)

/* ISO/IEC 3166-1 two-character country codes */
#define COUNTRY_CODE_AT (((UINT_16) 'A' << 8) | (UINT_16) 'T') /* Austria       */
#define COUNTRY_CODE_AU (((UINT_16) 'A' << 8) | (UINT_16) 'U') /* Australia     */
#define COUNTRY_CODE_BE (((UINT_16) 'B' << 8) | (UINT_16) 'E') /* Belgium       */
#define COUNTRY_CODE_CA (((UINT_16) 'C' << 8) | (UINT_16) 'A') /* Canada        */
#define COUNTRY_CODE_CH (((UINT_16) 'C' << 8) | (UINT_16) 'H') /* Switzerland   */
#define COUNTRY_CODE_CN (((UINT_16) 'C' << 8) | (UINT_16) 'N') /* China         */
#define COUNTRY_CODE_DE (((UINT_16) 'D' << 8) | (UINT_16) 'E') /* Germany       */
#define COUNTRY_CODE_DK (((UINT_16) 'D' << 8) | (UINT_16) 'K') /* Denmark       */
#define COUNTRY_CODE_ES (((UINT_16) 'E' << 8) | (UINT_16) 'S') /* Spain         */
#define COUNTRY_CODE_EU (((UINT_16) 'E' << 8) | (UINT_16) 'U') /* ETSI (Europe) */
#define COUNTRY_CODE_FI (((UINT_16) 'F' << 8) | (UINT_16) 'I') /* Finland       */
#define COUNTRY_CODE_FR (((UINT_16) 'F' << 8) | (UINT_16) 'R') /* France        */
#define COUNTRY_CODE_GB (((UINT_16) 'G' << 8) | (UINT_16) 'B') /* United Kingdom */
#define COUNTRY_CODE_GR (((UINT_16) 'G' << 8) | (UINT_16) 'R') /* Greece        */
#define COUNTRY_CODE_IE (((UINT_16) 'I' << 8) | (UINT_16) 'E') /* Ireland       */
#define COUNTRY_CODE_IL (((UINT_16) 'I' << 8) | (UINT_16) 'L') /* Israel        */
#define COUNTRY_CODE_IS (((UINT_16) 'I' << 8) | (UINT_16) 'S') /* Iceland       */
#define COUNTRY_CODE_IT (((UINT_16) 'I' << 8) | (UINT_16) 'T') /* Italy         */
#define COUNTRY_CODE_JO (((UINT_16) 'J' << 8) | (UINT_16) 'O') /* Jordan        */
#define COUNTRY_CODE_JP (((UINT_16) 'J' << 8) | (UINT_16) 'P') /* Japan         */
#define COUNTRY_CODE_KR (((UINT_16) 'K' << 8) | (UINT_16) 'R') /* Korea         */
#define COUNTRY_CODE_LI (((UINT_16) 'L' << 8) | (UINT_16) 'I') /* Liechtenstein */
#define COUNTRY_CODE_LU (((UINT_16) 'L' << 8) | (UINT_16) 'U') /* Luxembourg    */
#define COUNTRY_CODE_NL (((UINT_16) 'N' << 8) | (UINT_16) 'L') /* Netherlands   */
#define COUNTRY_CODE_NO (((UINT_16) 'N' << 8) | (UINT_16) 'O') /* Norway        */
#define COUNTRY_CODE_PT (((UINT_16) 'P' << 8) | (UINT_16) 'T') /* Portugal      */
#define COUNTRY_CODE_SE (((UINT_16) 'S' << 8) | (UINT_16) 'E') /* Sweden        */
#define COUNTRY_CODE_SG (((UINT_16) 'S' << 8) | (UINT_16) 'G') /* Singapore     */
#define COUNTRY_CODE_TW (((UINT_16) 'T' << 8) | (UINT_16) 'W') /* Taiwan        */
#define COUNTRY_CODE_TH (((UINT_16) 'T' << 8) | (UINT_16) 'H') /* Thailand      */
#define COUNTRY_CODE_US (((UINT_16) 'U' << 8) | (UINT_16) 'S') /* United States */

/* dot11RegDomainsSupportValue */
#define MIB_REG_DOMAIN_FCC              0x10    /* FCC (US) */
#define MIB_REG_DOMAIN_IC               0x20    /* IC or DOC (Canada) */
#define MIB_REG_DOMAIN_ETSI             0x30    /* ETSI (Europe) */
#define MIB_REG_DOMAIN_SPAIN            0x31    /* Spain */
#define MIB_REG_DOMAIN_FRANCE           0x32    /* France */
#define MIB_REG_DOMAIN_JAPAN            0x40    /* MPHPT (Japan) */
#define MIB_REG_DOMAIN_OTHER            0x00    /* other */


/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/

/* Define channel offset in unit of 5MHz bandwidth */
typedef enum _ENUM_CHNL_SPAN_T {
    CHNL_SPAN_5     = 1,
    CHNL_SPAN_10    = 2,
    CHNL_SPAN_20    = 4,
    CHNL_SPAN_40    = 8
} ENUM_CHNL_SPAN_T, *P_ENUM_CHNL_SPAN_T;

/* Define BSS operating bandwidth */
typedef enum _ENUM_CHNL_BW_T {
    CHNL_BW_20,
    CHNL_BW_20_40,
    CHNL_BW_10,
    CHNL_BW_5
} ENUM_CHNL_BW_T, *P_ENUM_CHNL_BW_T;

/* If channel width is CHNL_BW_20_40, the first channel will be SCA and
 * the second channel is SCB, then iteratively.
 * Note the final channel will not be SCA.
 */
typedef struct _DOMAIN_SUBBAND_INFO {
    UINT_8              ucRegClass;
    ENUM_BAND_T         eBand;
    ENUM_CHNL_SPAN_T    eChannelSpan;
    UINT_8              ucFirstChannelNum;
    UINT_8              ucNumChannels;
    ENUM_CHNL_BW_T      eChannelBw;
    BOOLEAN             fgDfsNeeded;
    BOOLEAN             fgIbssProhibited;
} DOMAIN_SUBBAND_INFO, *P_DOMAIN_SUBBAND_INFO;

/* Use it as all available channel list for STA */
typedef struct _DOMAIN_INFO_ENTRY {
    UINT_16             u2CountryCode;
    UINT_16             u2MibRegDomainValue;

    /* If different attributes, put them into different rSubBands.
     * For example, DFS shall be used or not.
     */
    DOMAIN_SUBBAND_INFO rSubBand[MAX_SUBBAND_NUM];
} DOMAIN_INFO_ENTRY, *P_DOMAIN_INFO_ENTRY;

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
P_DOMAIN_INFO_ENTRY
rlmDomainGetDomainInfo (
    P_ADAPTER_T     prAdapter
    );

VOID
rlmDomainGetChnlList (
    P_ADAPTER_T             prAdapter,
    ENUM_BAND_T             eSpecificBand,
    PUINT_8                 pucNumOfChannel,
    P_RF_CHANNEL_INFO_T     paucChannelList
    );

VOID
rlmDomainSendCmd (
    P_ADAPTER_T     prAdapter,
    BOOLEAN         fgIsOid
    );

BOOLEAN
rlmDomainIsLegalChannel (
    P_ADAPTER_T     prAdapter,
    ENUM_BAND_T     eBand,
    UINT_8          ucChannel
    );

/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/

#endif /* _RLM_DOMAIN_H */


