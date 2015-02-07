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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/precomp.h#2 $
*/

/*! \file   precomp.h
    \brief  Collection of most compiler flags are described here.

    In this file we collect all compiler flags and detail the driver behavior if
    enable/disable such switch or adjust numeric parameters.
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
** $Log: precomp.h $
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\33 2009-10-09 17:09:26 GMT mtk01088
**  add a wapi.h for related variable define
**  \main\maintrunk.MT5921\32 2009-07-09 18:55:16 GMT mtk01088
**  remove the non-used reference header file
**  \main\maintrunk.MT5921\31 2009-07-06 20:28:37 GMT mtk01088
**  adding the related header for supporting wapi 
**  \main\maintrunk.MT5921\30 2008-11-24 21:05:04 GMT mtk01425
**  1. Add PTA_ENABLED flag
**  \main\maintrunk.MT5921\29 2008-10-24 12:05:59 GMT mtk01088
**  move the config.h from precomp.h to gl_os.h for lint check
**  \main\maintrunk.MT5921\28 2008-09-05 17:24:43 GMT mtk01461
**  Update Driver for Code Review
**  \main\maintrunk.MT5921\27 2008-08-11 09:33:05 GMT mtk01461
**  Remove reset.h
**  \main\maintrunk.MT5921\26 2008-07-10 16:37:21 GMT mtk01084
**  support 802.11d related functions
**  \main\maintrunk.MT5921\25 2008-03-31 09:48:49 GMT mtk01461
**  Adjust the include sequence in order to add callback func for assocSendDisAssocFrame
**  \main\maintrunk.MT5921\24 2008-01-31 17:38:55 GMT mtk01385
**  1. add nic eeprom header file.
**  \main\maintrunk.MT5921\23 2008-01-07 15:05:33 GMT mtk01461
**  Add SDIO Enhance Support
**  \main\maintrunk.MT5921\22 2007-12-11 00:09:03 GMT mtk01461
**  Remove redundant include header file
**  \main\maintrunk.MT5921\21 2007-11-30 18:04:59 GMT mtk01088
**  move the define CETK_NDIS_PERFORMANCE_WORKAROUND to global define config.h
**
**  \main\maintrunk.MT5921\20 2007-11-26 21:34:33 GMT mtk01385
**  1. add statistics header file.
**  \main\maintrunk.MT5921\19 2007-11-17 15:18:46 GMT mtk01385
**  1. add wlan_oid_rftest.h and rftest.h.
**  \main\maintrunk.MT5921\18 2007-11-15 16:26:35 GMT mtk01088
**  add a flag for workaround CETK ndis performance
**  \main\maintrunk.MT5921\17 2007-11-08 20:19:50 GMT mtk01088
**  add tkip_mic.h
**  \main\maintrunk.MT5921\16 2007-10-30 11:56:04 GMT MTK01425
**  1. Adjust sequence of include files
**  \main\maintrunk.MT5921\15 2007-10-30 09:56:52 GMT mtk01425
**  1. Add just the sequence of include files
**  \main\maintrunk.MT5921\14 2007-10-25 17:54:58 GMT mtk01461
**  Remove old IBSS Power Save Support Flag
**
** Revision 1.10  2007/07/16 02:36:30  MTK01088
** add mac.h and mib.h
**
** Revision 1.9  2007/07/12 07:01:08  MTK01084
** include "timer.h"
**
** Revision 1.8  2007/07/04 12:49:01  MTK01088
** modify the ENUM define
**
** Revision 1.7  2007/07/04 10:14:03  MTK01088
** add rsn.h
**
** Revision 1.6  2007/07/03 08:17:28  MTK01088
** add privacy.h
**
** Revision 1.5  2007/06/28 13:14:39  MTK01088
** change the hal.h location
**
** Revision 1.4  2007/06/28 13:10:01  MTK01088
** add the hal.h
**
** Revision 1.3  2007/06/27 06:19:15  MTK01088
** add the sec fsm.h
**
** Revision 1.2  2007/06/27 02:18:49  MTK01461
** Update SCAN_FSM, Initial(Can Load Module), Proc(Can do Reg R/W), TX API
**
** Revision 1.1.1.1  2007/06/22 08:09:05  MTK01461
** no message
**
*/

#ifndef _PRECOMP_H
#define _PRECOMP_H

/*******************************************************************************
*                         C O M P I L E R   F L A G S
********************************************************************************
*/

/*******************************************************************************
*                    E X T E R N A L   R E F E R E N C E S
********************************************************************************
*/
#include "gl_os.h"

#include "debug.h"
#include "queue.h"
#include "link.h"
#include "timer.h"

#include "mac.h"
#include "qos_enhance.h"

#include "tx.h"

#include "wlan_def.h"

#include "wlan_lib.h"
#include "wlan_oid.h"
#include "wlan_oid_rftest.h"


#include "rftest.h"


#include "join_fsm.h"
#if PTA_ENABLED
#include "pta_fsm.h"
#endif
#include "ibss.h"

#include "sec_fsm.h"


#include "mgt_buf.h"
#include "rx.h"


#include "statistics.h"
#include "mib.h"
#include "privacy.h"
#include "rsn.h"
#include "scan_fsm.h"
#include "scan.h"
#include "pwr_mgt_fsm.h"

#include "arb_fsm.h"

#include "roaming_fsm.h"

#if defined(MT5921)
#include "mt592x_reg.h"
#include "mt592x_hw.h"
#include "mt5921.h"
#endif /* MT5921 */

#if defined(MT5922)
#include "mt592x_reg.h"
#include "mt592x_hw.h"
#include "mt5922.h"
#endif /* MT5922 */

#include "nic.h"
#include "nic_rate.h"
#include "nic_rx.h"
#include "nic_tx.h"
#include "nic_privacy.h"
#include "nic_hw_timer.h"
#if PTA_ENABLED
#include "nic_pta.h"
#endif
#include "nic_eeprom.h"

#include "hal.h"

#include "util.h"

#include "tkip_mic.h"

#if SUPPORT_WAPI
#include "wapi.h"
#include "sms4.h"
#endif

#include "adapter.h"

#if CFG_SUPPORT_802_11D
#include "domain.h"
#endif

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

/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/

#endif /* _PRECOMP_H */


