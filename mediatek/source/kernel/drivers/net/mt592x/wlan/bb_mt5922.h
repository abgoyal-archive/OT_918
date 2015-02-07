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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/bb_mt5922.h#1 $
*/

/*! \file   "bb_mt5922.h"
    \brief  The definition and operations for MT5922 baseband

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
** $Log: bb_mt5922.h $
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\4 2008-08-18 19:29:37 GMT mtk01088
**  remove non-used and duplicate defined
**  \main\maintrunk.MT5921\3 2008-04-10 23:46:50 GMT mtk01385
**  1. add update BB Rx setting based on thermo info function.
** Revision 1.2  2007/07/05 07:25:31  MTK01461
** Add Linux initial code, modify doc, add 11BB, RF init code
**
**
*/

#ifndef _BB_MT5922_H
#define _BB_MT5922_H

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

/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/

/*******************************************************************************
*                            P U B L I C   D A T A
********************************************************************************
*/

/* MT5922 Baseband control register (BBCR) definition */
#define BBCR_CR0                        0
#define BBCR_CR1                        1
#define BBCR_CR2                        2
#define BBCR_CR3                        3
#define BBCR_CR4                        4
#define BBCR_CR5                        5
#define BBCR_CR6                        6
#define BBCR_CR7                        7
#define BBCR_CR8                        8
#define BBCR_CR9                        9
#define BBCR_CR10                       10
#define BBCR_CR11                       11
#define BBCR_CR12                       12
#define BBCR_CR13                       13
#define BBCR_CR14                       14
#define BBCR_CR15                       15
#define BBCR_CR16                       16
#define BBCR_CR17                       17
#define BBCR_CR18                       18
#define BBCR_CR19                       19
#define BBCR_CR20                       20
#define BBCR_CR21                       21
#define BBCR_CR22                       22
#define BBCR_CR23                       23
#define BBCR_CR24                       24
#define BBCR_CR25                       25
#define BBCR_CR26                       26
#define BBCR_CR27                       27
#define BBCR_CR28                       28
#define BBCR_CR29                       29
#define BBCR_CR30                       30
#define BBCR_CR31                       31
#define BBCR_CR32                       32
#define BBCR_CR33                       33
#define BBCR_CR34                       34
#define BBCR_CR35                       35
#define BBCR_CR36                       36
#define BBCR_CR37                       37
#define BBCR_CR38                       38
#define BBCR_CR39                       39
#define BBCR_CR45                       45
#define BBCR_CR46                       46
#define BBCR_CR80                       80
#define BBCR_CR81                       81
#define BBCR_CR82                       82
#define BBCR_CR83                       83
#define BBCR_CR84                       84
#define BBCR_CR85                       85
#define BBCR_CR86                       86
#define BBCR_CR87                       87
#define BBCR_CR88                       88
#define BBCR_CR89                       89
#define BBCR_CR90                       90
#define BBCR_CR91                       91
#define BBCR_CR92                       92
#define BBCR_CR93                       93
#define BBCR_CR94                       94
#define BBCR_CR95                       95
#define BBCR_CR96                       96
#define BBCR_CR97                       97
#define BBCR_CR98                       98
#define BBCR_CR99                       99
#define BBCR_CR100                      100
#define BBCR_CR101                      101
#define BBCR_CR102                      102
#define BBCR_CR103                      103
#define BBCR_CR104                      104
#define BBCR_CR105                      105
#define BBCR_CR106                      106
#define BBCR_CR107                      107
#define BBCR_CR108                      108
#define BBCR_CR109                      109
#define BBCR_CR110                      110
#define BBCR_CR111                      111
#define BBCR_CR112                      112
#define BBCR_CR113                      113
#define BBCR_CR114                      114
#define BBCR_CR115                      115
#define BBCR_CR116                      116
#define BBCR_CR117                      117
#define BBCR_CR118                      118
#define BBCR_CR119                      119
#define BBCR_CR120                      120
#define BBCR_CR121                      121
#define BBCR_CR122                      122
#define BBCR_CR123                      123
#define BBCR_CR124                      124
#define BBCR_CR125                      125
#define BBCR_CR126                      126
#define BBCR_CR127                      127
#define BBCR_CR128                      128
#define BBCR_CR129                      129

/*******************************************************************************
*                           P R I V A T E   D A T A
********************************************************************************
*/

/*******************************************************************************
*                                 M A C R O S
********************************************************************************
*/
/* Write MT5922 baseband */

#define HAL_BBCR_WR(prAdapter, u4Offset, u4Value) \
    HAL_MCR_WR(prAdapter, 0x200+u4Offset*4, u4Value)

/* Read MT5922 baseband */
#define HAL_BBCR_RD(prAdapter, u4Offset, pu4Value) \
    HAL_MCR_RD(prAdapter, 0x200+u4Offset*4, pu4Value)

/*******************************************************************************
*                   F U N C T I O N   D E C L A R A T I O N S
********************************************************************************
*/

VOID
halBBInit (
    IN P_ADAPTER_T prAdapter
    );

VOID
halBBChangeBand (
    IN P_ADAPTER_T prAdapter,
    IN ENUM_BAND_T eBand
    );

VOID
halBBAdoptTempChange (
    IN P_ADAPTER_T          prAdapter,
    IN ENUM_THERMO_STATE_T  rState
    );


#endif /* _BB_MT5922_H */

