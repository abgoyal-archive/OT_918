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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/gl_wext.h#2 $
*/

/*! \file   gl_wext.h
    \brief  This file is for Portable Driver linux wireless extension support.
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
** $Log: gl_wext.h $
 *
 * 06 13 2010 renbang.jiang
 * [ALPS00008206][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for fixing build warning 
 * .
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\11 2009-09-28 20:19:28 GMT mtk01090
**  Add private ioctl to carry OID structures. Restructure public/private ioctl interfaces to Linux kernel.
**  \main\maintrunk.MT5921\10 2009-09-03 12:12:35 GMT mtk01088
**  adding the function declaration
**  \main\maintrunk.MT5921\9 2009-08-18 22:57:17 GMT mtk01090
**  Add Linux SDIO (with mmc core) support.
**  Add Linux 2.6.21, 2.6.25, 2.6.26.
**  Fix compile warning in Linux.
**  \main\maintrunk.MT5921\8 2008-08-29 16:59:07 GMT mtk01088
**  fixed compiling error
**  \main\maintrunk.MT5921\7 2008-08-29 14:13:28 GMT mtk01088
**  adjust the header file for code refine
**  \main\maintrunk.MT5921\6 2008-03-28 10:40:31 GMT mtk01461
**  Add set desired rate in Linux STD IOCTL
**  \main\maintrunk.MT5921\5 2008-03-11 14:51:08 GMT mtk01461
**  Refine private IOCTL functions
**  \main\maintrunk.MT5921\4 2008-02-12 23:45:45 GMT mtk01461
**  Add Set Frequency & Channel oid support for Linux
**  \main\maintrunk.MT5921\3 2007-11-06 19:36:19 GMT mtk01088
**  add the WPS related code
*/

#ifndef _GL_WEXT_H
#define _GL_WEXT_H

#ifdef WIRELESS_EXT
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
#define RATE_5_5M     (11)  /* 5.5M */

/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/
typedef struct _PARAM_FIXED_IEs {
    UINT_8   aucTimestamp[8];
    UINT_16  u2BeaconInterval;
    UINT_16  u2Capabilities;
} PARAM_FIXED_IEs;

typedef struct _PARAM_VARIABLE_IE_T {
    UINT_8  ucElementID;
    UINT_8  ucLength;
    UINT_8  aucData[1];
} PARAM_VARIABLE_IE_T, *P_PARAM_VARIABLE_IE_T;

enum {
    IEEE80211_FILTER_TYPE_BEACON            = 1<<0,
    IEEE80211_FILTER_TYPE_PROBE_REQ         = 1<<1,
    IEEE80211_FILTER_TYPE_PROBE_RESP        = 1<<2,
    IEEE80211_FILTER_TYPE_ASSOC_REQ         = 1<<3,
    IEEE80211_FILTER_TYPE_ASSOC_RESP        = 1<<4,
    IEEE80211_FILTER_TYPE_AUTH              = 1<<5,
    IEEE80211_FILTER_TYPE_DEAUTH            = 1<<6,
    IEEE80211_FILTER_TYPE_DISASSOC          = 1<<7,
    IEEE80211_FILTER_TYPE_ALL               = 0xFF  /* used to check the valid filter bits */
};

#if SUPPORT_WAPI
#define IW_AUTH_WAPI_ENABLED     0x20
#define IW_ENCODE_ALG_SMS4  0x20
#endif


/*******************************************************************************
*                            P U B L I C   D A T A
********************************************************************************
*/
extern const struct iw_handler_def wext_handler_def;

/*******************************************************************************
*                           P R I V A T E   D A T A
********************************************************************************
*/

/*******************************************************************************
*                                 M A C R O S
********************************************************************************
*/

/*******************************************************************************
*                  F U N C T I O N   D E C L A R A T I O N S
********************************************************************************
*/
/* wireless extensions' ioctls */
int
wext_support_ioctl(
    IN struct net_device *prDev,
    IN struct ifreq *prIfReq,
    IN int i4Cmd
    );

int
wext_set_rate (
    IN struct net_device *prNetDev,
    IN struct iw_request_info *prIwReqInfo,
    IN struct iw_param *prRate,
    IN char *pcExtra
    );

void
wext_indicate_wext_event(
    IN P_GLUE_INFO_T prGlueInfo,
    IN unsigned int u4Cmd,
    IN unsigned char *pucData,
    IN unsigned int u4DataLen
    );

struct iw_statistics *
wext_get_wireless_stats (
    struct net_device *prDev
    );

int
wext_get_priv (
    IN struct net_device *prNetDev,
    IN struct ifreq *prIfReq
    );

/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/

#endif /* WIRELESS_EXT */

#endif /* _GL_WEXT_H */

