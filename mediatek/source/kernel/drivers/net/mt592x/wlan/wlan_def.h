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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/wlan_def.h#2 $
*/

/*! \file   "wlan_def.h"
    \brief  This file includes the basic definition of WLAN

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
** $Log: wlan_def.h $
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\27 2009-07-06 20:22:49 GMT mtk01088
**  adding the marco for processing wpi frame
**  \main\maintrunk.MT5921\26 2009-05-23 14:42:03 GMT mtk01088
**  add a queue assign for sending de-auth frame
**  \main\maintrunk.MT5921\25 2008-10-16 15:54:39 GMT mtk01461
**  Update driver to fix lint warning
**  \main\maintrunk.MT5921\24 2008-08-29 19:02:02 GMT mtk01104
**  Remove doxygen comment format
**  \main\maintrunk.MT5921\23 2008-04-20 11:01:05 GMT mtk01385
**  1. add UNDEF_TEMP state to thermo state.
**  \main\maintrunk.MT5921\22 2008-04-10 23:44:39 GMT mtk01385
**  1. add thermo state enum definitions.
**  \main\maintrunk.MT5921\21 2008-04-02 20:44:26 GMT mtk01084
**  Support for RCPI variance histogram
**  \main\maintrunk.MT5921\20 2008-03-31 21:00:27 GMT mtk01461
**  Refine the sequence of function declaration
**  \main\maintrunk.MT5921\19 2008-03-31 09:50:35 GMT mtk01461
**  Add callback func for authSendDeauthFrame & assocSendDisAssocFrame
**  \main\maintrunk.MT5921\18 2008-03-30 16:49:05 GMT mtk01461
**  Update for change prototype of send Deauth & Disassoc frame
**  \main\maintrunk.MT5921\17 2008-03-28 10:40:10 GMT mtk01461
**  Add rateGetRateSetFromDataRates() for set desired rate OID
**  \main\maintrunk.MT5921\16 2008-03-26 09:16:12 GMT mtk01461
**  Revise function prototype of ateSetAckCtsDataRatesFromRateSet()
**  \main\maintrunk.MT5921\15 2008-02-25 16:06:35 GMT mtk01385
**  1. add 11b only phy type.
**  \main\maintrunk.MT5921\14 2008-02-21 15:01:29 GMT mtk01461
**  Add definition for initial rate selection support
**  \main\maintrunk.MT5921\13 2008-02-12 23:00:02 GMT mtk01461
**  Align tab with version of MPW
**  \main\maintrunk.MT5921\12 2008-01-07 15:05:56 GMT mtk01461
**  Add PhyType & AdHocMode Selection Support
**  \main\maintrunk.MT5921\11 2007-12-29 17:02:04 GMT mtk01385
**  1. add ALC_VAL type define.
**  \main\maintrunk.MT5921\10 2007-12-11 00:07:58 GMT mtk01461
**  Add function declarations
**  \main\maintrunk.MT5921\9 2007-11-08 20:11:00 GMT mtk01088
**  add disassociation function declaration
**  \main\maintrunk.MT5921\8 2007-10-25 17:59:24 GMT mtk01461
**  Add VOIP SCAN & Refine Roaming
** Revision 1.8  2007/07/17 12:56:21  MTK01088
** add enum and structure for pmkid and remove key
**
** Revision 1.7  2007/07/16 02:37:19  MTK01088
** add the _T at ENUM define
**
** Revision 1.6  2007/07/05 07:25:31  MTK01461
** Add Linux initial code, modify doc, add 11BB, RF init code
**
** Revision 1.5  2007/07/04 12:55:24  MTK01088
** modify the ENUM define
**
** Revision 1.4  2007/07/04 10:14:30  MTK01088
** add null and bc addr define
**
** Revision 1.3  2007/06/27 06:23:35  MTK01088
** add the sec related structure define
**
** Revision 1.2  2007/06/25 06:16:23  MTK01461
** Update illustrations, gl_init.c, gl_kal.c, gl_kal.h, gl_os.h and RX API
**
*/

#ifndef _WLAN_DEF_H
#define _WLAN_DEF_H

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
/* PHY TYPE bit definitions */
#define PHY_TYPE_BIT_ERP        BIT(PHY_TYPE_ERP_INDEX)     /* ERP PHY (clause 19) */
//#define PHY_TYPE_BIT_DSSS       BIT(PHY_TYPE_DSSS_INDEX)    /* DSSS PHY (clause 15) */
#define PHY_TYPE_BIT_HR_DSSS    BIT(PHY_TYPE_HR_DSSS_INDEX) /* HR/DSSS PHY (clause 18) */
#define PHY_TYPE_BIT_OFDM       BIT(PHY_TYPE_OFDM_INDEX)    /* OFDM 5 GHz PHY (clause 17) */

/* PHY TYPE set definitions */
#define PHY_TYPE_SET_802_11ABG  (PHY_TYPE_BIT_OFDM | \
                                 PHY_TYPE_BIT_HR_DSSS | \
                                 PHY_TYPE_BIT_ERP)

#define PHY_TYPE_SET_802_11BG   (PHY_TYPE_BIT_HR_DSSS | \
                                 PHY_TYPE_BIT_ERP)

#define PHY_TYPE_SET_802_11A    (PHY_TYPE_BIT_OFDM)

#define PHY_TYPE_SET_802_11G    (PHY_TYPE_BIT_ERP)

#define PHY_TYPE_SET_802_11B    (PHY_TYPE_BIT_HR_DSSS)


/* Rate set bit definitions */
#define RATE_SET_BIT_1M         BIT(RATE_1M_INDEX)      /* Bit 0: 1M */
#define RATE_SET_BIT_2M         BIT(RATE_2M_INDEX)      /* Bit 1: 2M */
#define RATE_SET_BIT_5_5M       BIT(RATE_5_5M_INDEX)    /* Bit 2: 5.5M */
#define RATE_SET_BIT_11M        BIT(RATE_11M_INDEX)     /* Bit 3: 11M */
#define RATE_SET_BIT_22M        BIT(RATE_22M_INDEX)     /* Bit 4: 22M */
#define RATE_SET_BIT_33M        BIT(RATE_33M_INDEX)     /* Bit 5: 33M */
#define RATE_SET_BIT_6M         BIT(RATE_6M_INDEX)      /* Bit 8: 6M */
#define RATE_SET_BIT_9M         BIT(RATE_9M_INDEX)      /* Bit 9: 9M */
#define RATE_SET_BIT_12M        BIT(RATE_12M_INDEX)     /* Bit 10: 12M */
#define RATE_SET_BIT_18M        BIT(RATE_18M_INDEX)     /* Bit 11: 18M */
#define RATE_SET_BIT_24M        BIT(RATE_24M_INDEX)     /* Bit 12: 24M */
#define RATE_SET_BIT_36M        BIT(RATE_36M_INDEX)     /* Bit 13: 36M */
#define RATE_SET_BIT_48M        BIT(RATE_48M_INDEX)     /* Bit 14: 48M */
#define RATE_SET_BIT_54M        BIT(RATE_54M_INDEX)     /* Bit 15: 54M */

/* Rate set definitions */
#define RATE_SET_HR_DSSS            (RATE_SET_BIT_1M | \
                                     RATE_SET_BIT_2M | \
                                     RATE_SET_BIT_5_5M | \
                                     RATE_SET_BIT_11M)

#define RATE_SET_ERP                (RATE_SET_BIT_1M | \
                                     RATE_SET_BIT_2M | \
                                     RATE_SET_BIT_5_5M | \
                                     RATE_SET_BIT_11M | \
                                     RATE_SET_BIT_6M | \
                                     RATE_SET_BIT_9M | \
                                     RATE_SET_BIT_12M | \
                                     RATE_SET_BIT_18M | \
                                     RATE_SET_BIT_24M | \
                                     RATE_SET_BIT_36M | \
                                     RATE_SET_BIT_48M | \
                                     RATE_SET_BIT_54M)

#define RATE_SET_OFDM               (RATE_SET_BIT_6M | \
                                     RATE_SET_BIT_9M | \
                                     RATE_SET_BIT_12M | \
                                     RATE_SET_BIT_18M | \
                                     RATE_SET_BIT_24M | \
                                     RATE_SET_BIT_36M | \
                                     RATE_SET_BIT_48M | \
                                     RATE_SET_BIT_54M)

#define RATE_SET_ALL                 RATE_SET_ERP

#define BASIC_RATE_SET_HR_DSSS      (RATE_SET_BIT_1M | \
                                     RATE_SET_BIT_2M)

#define BASIC_RATE_SET_HR_DSSS_ERP  (RATE_SET_BIT_1M | \
                                     RATE_SET_BIT_2M | \
                                     RATE_SET_BIT_5_5M | \
                                     RATE_SET_BIT_11M)

#define BASIC_RATE_SET_ERP          (RATE_SET_BIT_1M | \
                                     RATE_SET_BIT_2M | \
                                     RATE_SET_BIT_5_5M | \
                                     RATE_SET_BIT_11M | \
                                     RATE_SET_BIT_6M | \
                                     RATE_SET_BIT_12M | \
                                     RATE_SET_BIT_24M)

#define BASIC_RATE_SET_OFDM         (RATE_SET_BIT_6M | \
                                     RATE_SET_BIT_12M | \
                                     RATE_SET_BIT_24M)

#define INITIAL_RATE_SET_RCPI_100    RATE_SET_ALL

#define INITIAL_RATE_SET_RCPI_80    (RATE_SET_BIT_1M | \
                                     RATE_SET_BIT_2M | \
                                     RATE_SET_BIT_5_5M | \
                                     RATE_SET_BIT_11M | \
                                     RATE_SET_BIT_6M | \
                                     RATE_SET_BIT_9M | \
                                     RATE_SET_BIT_12M | \
                                     RATE_SET_BIT_24M)

#define INITIAL_RATE_SET_RCPI_60    (RATE_SET_BIT_1M | \
                                     RATE_SET_BIT_2M | \
                                     RATE_SET_BIT_5_5M | \
                                     RATE_SET_BIT_11M | \
                                     RATE_SET_BIT_6M)

#define INITIAL_RATE_SET(_rcpi)     (INITIAL_RATE_SET_ ## _rcpi)

#define RCPI_100                    100 /* -60 dBm */
#define RCPI_80                     80  /* -70 dBm */
#define RCPI_60                     60  /* -80 dBm */


/* The number of RCPI records used to calculate their average value */
#define MAX_NUM_RCPI_RECORDS                    10

/* The number of RCPI records used to calculate their average value */
#define NO_RCPI_RECORDS                         -128
#define MAX_RCPI_DBM                            0
#define MIN_RCPI_DBM                            -100

/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/
typedef UINT_16                 PHY_TYPE, *P_PHY_TYPE;
typedef UINT_8                  RCPI, *P_RCPI;
typedef UINT_8                  ALC_VAL, *P_ALC_VAL;

/* NOTE(Kevin): We may design proprietary Operation Mode if a BSS carry some particular IE */
typedef enum _ENUM_OP_MODE_T {
    OP_MODE_INFRASTRUCTURE = 0,         /* Infrastructure */
    OP_MODE_IBSS,                       /* AdHoc */
    OP_MODE_RESERVED,                   /* Reserved */
    OP_MODE_NUM
} ENUM_OP_MODE_T, *P_ENUM_OP_MODE_T;

typedef enum _ENUM_MEDIA_STATE_T {
    MEDIA_STATE_DISCONNECTED = 0,
    MEDIA_STATE_CONNECTED
} ENUM_MEDIA_STATE, *P_ENUM_MEDIA_STATE;

typedef enum _ENUM_BSS_TYPE_T {
    BSS_TYPE_INFRASTRUCTURE = 1,
    BSS_TYPE_IBSS
} ENUM_BSS_TYPE_T, *P_ENUM_BSS_TYPE_T;

typedef enum _ENUM_PHY_TYPE_INDEX_T {
    PHY_TYPE_ERP_INDEX = 0,     /* ERP PHY (clause 19) */
    PHY_TYPE_HR_DSSS_INDEX,     /* HR/DSSS PHY (clause 18) */
    PHY_TYPE_OFDM_INDEX,        /* OFDM 5 GHz PHY (clause 17) */
    //PHY_TYPE_DSSS_INDEX,        /* DSSS PHY (clause 15) */ /* NOTE(Kevin): We don't use this now */
    PHY_TYPE_INDEX_NUM // 3
} ENUM_PHY_TYPE_INDEX_T, *P_ENUM_PHY_TYPE_INDEX_T;

typedef enum _ENUM_RATE_INDEX_T {
    RATE_1M_INDEX = 0,      /* 1M */
    RATE_2M_INDEX,          /* 2M */
    RATE_5_5M_INDEX,        /* 5.5M */
    RATE_11M_INDEX,         /* 11M */
    RATE_22M_INDEX,         /* 22M */
    RATE_33M_INDEX,         /* 33M */
    RATE_6M_INDEX,          /* 6M */
    RATE_9M_INDEX,          /* 9M */
    RATE_12M_INDEX,         /* 12M */
    RATE_18M_INDEX,         /* 18M */
    RATE_24M_INDEX,         /* 24M */
    RATE_36M_INDEX,         /* 36M */
    RATE_48M_INDEX,         /* 48M */
    RATE_54M_INDEX,         /* 54M */
    RATE_NUM // 14
} ENUM_RATE_INDEX_T, *P_ENUM_RATE_INDEX_T;

/* Used for HAL */
typedef enum _ENUM_PREMABLE_OPTION_T {
    PREAMBLE_DEFAULT_LONG_NONE = 0, /* LONG for PHY_TYPE_HR_DSSS, NONE for PHY_TYPE_OFDM */
    PREAMBLE_OPTION_SHORT, /* SHORT mandatory for PHY_TYPE_ERP, SHORT option for PHY_TYPE_HR_DSSS */
    PREAMBLE_OPTION_NUM
} ENUM_PREMABLE_OPTION_T, *P_ENUM_PREMABLE_OPTION_T;



typedef enum _ENUM_ADHOC_TYPE_T {
    ADHOC_TYPE_NONE,
    ADHOC_TYPE_11B,
    ADHOC_TYPE_11BG,
    ADHOC_TYPE_11G,
    ADHOC_TYPE_NUM
} ENUM_ADHOC_TYPE_T, *P_ENUM_ADHOC_TYPE_T;


typedef enum _ENUM_BAND_T {
    BAND_24G = 0,                       /* 2.4G */
    BAND_5G,                            /* 5G */
    BAND_TYPE_NUM
} ENUM_BAND_T, *P_ENUM_BAND_T;

typedef struct _RF_CHANNEL_INFO_T {
    UINT_8          ucChannelNum;
    ENUM_BAND_T     eBand;
} RF_CHANNEL_INFO_T, *P_RF_CHANNEL_INFO_T;

typedef struct _RF_INFO_T {
    ENUM_BAND_T     eBand;
    UINT_8          ucChannelNum;
    UINT_8          ucaSlotTime;
} RF_INFO_T, *P_RF_INFO_T;

/* Session for Thermo function */
typedef enum _ENUM_THERMO_STATE_T {
    UNDEF_TEMP = 0,
    LOW_TEMP,
    NORMAL_TEMP,
    HIGH_TEMP
} ENUM_THERMO_STATE_T, *P_ENUM_THERMO_STATE_T;

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
/* Macros to get and set the wireless LAN frame fields those are 16/32 bits in
   length. */
#define WLAN_GET_FIELD_16(_memAddr_p, _value_p) \
        { \
            PUINT_8 __cp = (PUINT_8) (_memAddr_p); \
            *(PUINT_16)(_value_p) = ((UINT_16) __cp[0]) | ((UINT_16) __cp[1] << 8); \
        }

#define WLAN_GET_FIELD_32(_memAddr_p, _value_p) \
        { \
            PUINT_8 __cp = (PUINT_8) (_memAddr_p); \
            *(PUINT_32)(_value_p) = ((UINT_32) __cp[0])       | ((UINT_32) __cp[1] << 8) | \
                                    ((UINT_32) __cp[2] << 16) | ((UINT_32) __cp[3] << 24); \
        }

#define WLAN_GET_FIELD_64(_memAddr_p, _value_p) \
        { \
            PUINT_8 __cp = (PUINT_8) (_memAddr_p); \
            *(PUINT_64)(_value_p) = \
                ((UINT_64) __cp[0])       | ((UINT_64) __cp[1] << 8)  | \
                ((UINT_64) __cp[2] << 16) | ((UINT_64) __cp[3] << 24) | \
                ((UINT_64) __cp[4] << 32) | ((UINT_64) __cp[5] << 40) | \
                ((UINT_64) __cp[6] << 48) | ((UINT_64) __cp[7] << 56); \
        }

#define WLAN_SET_FIELD_16(_memAddr_p, _value) \
        { \
            PUINT_8 __cp = (PUINT_8) (_memAddr_p); \
            __cp[0] = (UINT_8) (_value); \
            __cp[1] = (UINT_8) ((_value) >> 8); \
        }

#define WLAN_SET_FIELD_32(_memAddr_p, _value) \
        { \
            PUINT_8 __cp = (PUINT_8) (_memAddr_p); \
            __cp[0] = (UINT_8) (_value); \
            __cp[1] = (UINT_8) ((_value) >> 8); \
            __cp[2] = (UINT_8) ((_value) >> 16); \
            __cp[3] = (UINT_8) ((_value) >> 24); \
        }

#ifdef SUPPORT_WAPI
#define WLAN_SET_FIELD_16_BE(_memAddr_p, _value) \
        { \
            PUINT_8 __cp = (PUINT_8) (_memAddr_p); \
            __cp[0] = (UINT_8) ((_value) >> 8); \
            __cp[1] = (UINT_8) (_value); \
        }

/* This macro increase 128-bit value by index */
#define INC_128_BITS(value_p) \
    {\
        *((PUINT_8)(value_p) + 0) += 1; \
        if (*((PUINT_8)(value_p) + 0) == 0) { \
            *((PUINT_8)(value_p) + 1) += 1; \
            if (*((PUINT_8)(value_p) + 1) == 0) { \
                *((PUINT_8)(value_p) + 2) += 1; \
                if (*((PUINT_8)(value_p) + 2) == 0) { \
                    *((PUINT_8)(value_p) + 3) += 1; \
                    if (*((PUINT_8)(value_p) + 3) == 0) { \
                        *((PUINT_8)(value_p) + 4) += 1; \
                        if (*((PUINT_8)(value_p) + 4) == 0) { \
                            *((PUINT_8)(value_p) + 5) += 1; \
                            if (*((PUINT_8)(value_p) + 5) == 0) { \
                                *((PUINT_8)(value_p) + 6) += 1; \
                                if (*((PUINT_8)(value_p) + 6) == 0) { \
                                    *((PUINT_8)(value_p) + 7) += 1; \
                                    if (*((PUINT_8)(value_p) + 7) == 0) { \
                                        *((PUINT_8)(value_p) + 8) += 1; \
                                        if (*((PUINT_8)(value_p) + 8) == 0) { \
                                            *((PUINT_8)(value_p) + 9) += 1; \
                                            if (*((PUINT_8)(value_p) + 9) == 0) { \
                                                *((PUINT_8)(value_p) + 10) += 1; \
                                                if (*((PUINT_8)(value_p) + 10) == 0) { \
                                                    *((PUINT_8)(value_p) + 11) += 1; \
                                                    if (*((PUINT_8)(value_p) + 11) == 0) { \
                                                        *((PUINT_8)(value_p) + 12) += 1; \
                                                        if (*((PUINT_8)(value_p) + 12) == 0) { \
                                                            *((PUINT_8)(value_p) + 13) += 1; \
                                                            if (*((PUINT_8)(value_p) + 13) == 0) { \
                                                                *((PUINT_8)(value_p) + 14) += 1; \
                                                                if (*((PUINT_8)(value_p) + 14) == 0) { \
                                                                    *((PUINT_8)(value_p) + 15) += 1; \
                                                                } \
                                                            } \
                                                        } \
                                                    } \
                                                } \
                                            } \
                                        } \
                                    } \
                                } \
                            } \
                        } \
                    } \
                } \
            } \
        } \
    }
#endif

/*******************************************************************************
*                   F U N C T I O N   D E C L A R A T I O N S
********************************************************************************
*/
/*----------------------------------------------------------------------------*/
/* Routines in assoc.c                                                        */
/*----------------------------------------------------------------------------*/
WLAN_STATUS
assocSendReAssocReqFrame (
    IN P_ADAPTER_T prAdapter,
    IN P_BSS_DESC_T prBssDesc,
    IN BOOLEAN fgIsReAssoc
    );

WLAN_STATUS
assocSendDisAssocFrame(
    IN P_ADAPTER_T prAdapter,
    IN UINT_8 aucBSSID[],
    IN UINT_16 u2ReasonCode,
    IN PFN_TX_DONE_HANDLER pfTxDoneHandler
    );

WLAN_STATUS
assocCheckTxReAssocReqFrame (
    IN P_ADAPTER_T prAdapter,
    IN P_MSDU_INFO_T prMsduInfo,
    IN BOOLEAN fgIsReAssoc
    );

WLAN_STATUS
assocProcessRxReAssocRspFrame (
    IN P_ADAPTER_T prAdapter,
    IN P_SW_RFB_T prSwRfb,
    IN P_PEER_BSS_INFO_T prPeerBssInfo,
    IN BOOLEAN fgIsReAssoc,
    OUT PUINT_16 pu2StatusCode
    );

WLAN_STATUS
assocProcessRxDisassocFrame (
    IN P_ADAPTER_T prAdapter,
    IN P_SW_RFB_T prSwRfb,
    IN UINT_8 aucBSSID[],
    OUT PUINT_16 pu2ReasonCode
    );

/*----------------------------------------------------------------------------*/
/* Routines in auth.c                                                         */
/*----------------------------------------------------------------------------*/
WLAN_STATUS
authSendAuthFrame (
    IN P_ADAPTER_T prAdapter,
    IN P_PEER_BSS_INFO_T prPeerBssInfo,
    IN UINT_16 u2AuthAlgNum,
    IN UINT_16 u2TransactionSeqNum
    );

WLAN_STATUS
authSendDeauthFrame (
    IN P_ADAPTER_T prAdapter,
    IN UINT_8 aucBSSID[],
    IN UINT_16 u2ReasonCode,
    IN UINT_8 ucTQ,
    IN PFN_TX_DONE_HANDLER pfTxDoneHandler
    );

WLAN_STATUS
authCheckTxAuthFrame (
    IN P_ADAPTER_T  prAdapter,
    IN P_MSDU_INFO_T prMsduInfo,
    IN UINT_16 u2AuthAlgNum,
    IN UINT_16 u2TransactionSeqNum
    );

WLAN_STATUS
authProcessRxAuthFrame (
    IN P_ADAPTER_T prAdapter,
    IN P_SW_RFB_T prSwRfb,
    IN P_PEER_BSS_INFO_T prPeerBssInfo,
    IN UINT_16 u2AuthAlgNum,
    IN UINT_16 u2TransactionSeqNum,
    OUT PUINT_16 pu2StatusCode
    );

WLAN_STATUS
authProcessRxDeauthFrame (
    IN P_ADAPTER_T prAdapter,
    IN P_SW_RFB_T prSwRfb,
    IN UINT_8 aucBSSID[],
    OUT PUINT_16 pu2ReasonCode
    );



/*----------------------------------------------------------------------------*/
/* Routines in bss.c                                                          */
/*----------------------------------------------------------------------------*/
VOID
bssProcessBeacon (
    IN P_ADAPTER_T prAdapter,
    IN P_BSS_DESC_T prBSSDesc,
    IN P_SW_RFB_T prSwRfb
    );

VOID
bssUpdateTxRateForControlFrame (
    IN P_ADAPTER_T prAdapter
    );

VOID
bssLeave (
    IN P_ADAPTER_T prAdapter
    );

/*----------------------------------------------------------------------------*/
/* Routines in parse.c                                                        */
/*----------------------------------------------------------------------------*/
BOOLEAN
parseCheckForWFAInfoElem (
    IN PUINT_8 pucBuf,
    OUT PUINT_8 pucOuiType,
    OUT PUINT_16 pu2SubTypeVersion
    );

/*----------------------------------------------------------------------------*/
/* Routines in rate.c                                                         */
/*----------------------------------------------------------------------------*/
VOID
rateGetRateSetFromIEs (
    IN P_IE_SUPPORTED_RATE_T prIeSupportedRate,
    IN P_IE_EXT_SUPPORTED_RATE_T prIeExtSupportedRate,
    OUT PUINT_16 pu2OperationalRateSet,
    OUT PUINT_16 pu2BSSBasicRateSet,
    OUT PBOOLEAN pfgIsUnknownBSSBasicRate
    );

VOID
rateGetDataRatesFromRateSet (
    IN UINT_16 u2OperationalRateSet,
    IN UINT_16 u2BSSBasicRateSet,
    OUT PUINT_8 pucDataRates,
    OUT PUINT_8 pucDataRatesLen
    );

VOID
rateGetRateSetFromDataRates (
    IN PUINT_8 pucDataRates,
    IN UINT_8 ucDataRatesLen,
    OUT PUINT_16 pu2RateSet
    );

VOID
rateSetAckCtsDataRatesFromRateSet (
    IN UINT_16 u2OperationalRateSet,
    IN UINT_16 u2BSSBasicRateSet,
    IN OUT UINT_8 aucAckCtsRateIndex[]
    );

BOOLEAN
rateGetHighestRateIndexFromRateSet (
    IN UINT_16 u2RateSet,
    OUT PUINT_8 pucHighestRateIndex
    );

BOOLEAN
rateGetLowestRateIndexFromRateSet (
    IN UINT_16 u2RateSet,
    OUT PUINT_8 pucLowestRateIndex
    );

BOOLEAN
rateGetBestInitialRateIndex (
    IN UINT_16 u2RateSet,
    IN RCPI rRcpi,
    OUT PUINT_8 pucInitialRateIndex
    );

/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/

#endif /* _WLAN_DEF_H */

