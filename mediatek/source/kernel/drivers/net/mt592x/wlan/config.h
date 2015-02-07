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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/config.h#2 $
*/

/*! \file   "config.h"
    \brief  This file includes the various configurable parameters for customers

    This file ncludes the configurable parameters except the paramters indicate the turning-on/off of some features
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
** $Log: config.h $
 *
 * 09 03 2010 enlai.chu
 * [ALPS00003550] [YuSu]WAPI feature
 * For WAPI feature
 *
 * 06 18 2010 renbang.jiang
 * [ALPS00008357][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for support Rx/Tx indication led 
 * .
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\101 2009-10-09 17:08:25 GMT mtk01088
**  using a compiling flag to choose the wpi encrypt using local buffer or global buffer, default is local
**  \main\maintrunk.MT5921\100 2009-09-28 22:24:23 GMT mtk01090
**  Fix compile warning in Linux driver
**  \main\maintrunk.MT5921\99 2009-09-22 23:10:35 GMT mtk01089
**  Add SUPPORT_NEW_PTA_BOARD comiling definition
**  \main\maintrunk.MT5921\98 2009-09-12 13:45:29 GMT mtk01089
**  Add PTA_NEW_BOARD_DESIGN
**  \main\maintrunk.MT5921\97 2009-08-06 16:42:32 GMT mtk01090
**  Use GPIO0 and GPIO2 to control antenna switch and remove obsolete compile flag CFG_SUPPORT_SINGLE_ANTENNA
**  \main\maintrunk.MT5921\96 2009-07-09 18:54:37 GMT mtk01088
**  remove the wapi option compiling flag
**  \main\maintrunk.MT5921\95 2009-07-06 20:27:14 GMT mtk01088
**  adding the wapi config setting, default is disable, enable at this version
**  \main\maintrunk.MT5921\94 2009-06-23 22:11:07 GMT mtk01090
**  Add build option BUILD_USE_EEPROM and compile option CFG_SUPPORT_EXT_CONFIG for NVRAM support
**  \main\maintrunk.MT5921\93 2009-06-11 11:24:47 GMT mtk01088
**  add the CR1809 workaround flag
**  \main\maintrunk.MT5921\92 2009-04-24 09:13:54 GMT mtk01088
**  add a compiling flag for support WPS related code
**  \main\maintrunk.MT5921\91 2009-04-22 18:50:02 GMT mtk01088
**  add a compiling flag for stream io function enable/disable
**  \main\maintrunk.MT5921\90 2009-03-20 11:42:37 GMT mtk01461
**  add testing initial flag for WMM VI
**  \main\maintrunk.MT5921\89 2009-02-06 17:03:00 GMT mtk01090
**  Add PATHRU support. Enabled only in Windows CE SDIO driver case.
**  \main\maintrunk.MT5921\88 2009-02-04 16:59:07 GMT mtk01725
**  Add a configure flag for BUILD_META support.
**  \main\maintrunk.MT5921\87 2009-01-11 23:21:11 GMT mtk01461
**  Revise some default setting for release build
**  \main\maintrunk.MT5921\86 2009-01-05 09:51:59 GMT mtk01725
**  Change configuration flag for LP & pattern search SLT
**  \main\maintrunk.MT5921\85 2008-12-08 16:17:41 GMT mtk01461
**  Remove Lint Warning 553: Undefined preprocessor variable
**  \main\maintrunk.MT5921\84 2008-12-01 16:33:16 GMT mtk01461
**  #define CFG_FAKE_THERMO_VALUE_DBG_EN = 0 in config.h for removing Warning 553: Undefined preprocessor variable
**  \main\maintrunk.MT5921\83 2008-11-24 21:04:57 GMT mtk01425
**  1. Add PTA_ENABLED flag
**  \main\maintrunk.MT5921\82 2008-11-21 23:57:23 GMT mtk01725
**  \main\maintrunk.MT5921\81 2008-11-21 23:14:27 GMT mtk01725
**  \main\maintrunk.MT5921\80 2008-10-27 14:24:33 GMT mtk01084
**  supporting continuous polling mode
**  \main\maintrunk.MT5921\79 2008-10-22 10:55:24 GMT mtk01461
**  Update for lint diagnosis support
**  \main\maintrunk.MT5921\78 2008-10-16 18:54:28 GMT mtk01084
**  workaround HEC6796
**  \main\maintrunk.MT5921\77 2008-10-13 02:08:17 GMT mtk01461
**  Adjust the order of CFG_LP_SLT flag to fix compile warning
**  \main\maintrunk.MT5921\76 2008-09-24 10:58:47 GMT mtk01084
**  add single antenna related macro define
**  \main\maintrunk.MT5921\75 2008-09-05 17:24:38 GMT mtk01461
**  Update Driver for Code Review
**  \main\maintrunk.MT5921\74 2008-09-02 22:19:15 GMT mtk01461
**  Revise TX Aggregation to support TX Fragmentation
**  \main\maintrunk.MT5921\73 2008-08-21 00:16:18 GMT mtk01461
**  Update for Driver Review
**  \main\maintrunk.MT5921\72 2008-08-11 14:07:48 GMT mtk01084
**  modify driver to meeting coding rules
**  \main\maintrunk.MT5921\71 2008-07-25 17:16:17 GMT mtk01461
**  Add TX FIFO Aggregate Function to improve TX throughput
**  Add Flush TX after join complete for WM7 options
**  \main\maintrunk.MT5921\70 2008-07-22 10:05:48 GMT mtk01084
**  enhancement for TX/RX performance on IBSS-PS
**  \main\maintrunk.MT5921\69 2008-07-14 10:35:11 GMT mtk01084
**  enable 802.11d function
**  \main\maintrunk.MT5921\68 2008-07-10 16:37:18 GMT mtk01084
**  support 802.11d related functions
**  \main\maintrunk.MT5921\67 2008-06-25 17:44:27 GMT mtk01425
**  1. Add CFG_TX_RET_TX_CTRL_EARLY
**  2. Change CFG_IST_LOOP_COUNT to 3 for Windows CE SDIO
**  \main\maintrunk.MT5921\66 2008-06-24 10:24:40 GMT mtk01088
**  add flag for workaround HEC 5988
**  \main\maintrunk.MT5921\65 2008-06-19 15:44:16 GMT mtk01425
**  1. Make CFG_SDIO_TX_ENHANCE to 0 as default
**
**  \main\maintrunk.MT5921\64 2008-06-17 16:10:01 GMT mtk01425
**  1. Add configuration for SDIO Tx performance
**  \main\maintrunk.MT5921\63 2008-06-16 15:49:44 GMT mtk01084
**  use compiler flag to distinguish whether to support SSID recover state
**  \main\maintrunk.MT5921\62 2008-06-14 11:07:56 GMT MTK01088
**  change the default band for 11a
**  \main\maintrunk.MT5921\61 2008-06-13 19:33:50 GMT MTK01088
**  set default support 802.11A is disable
**  \main\maintrunk.MT5921\60 2008-06-13 10:32:51 GMT MTK01088
**  Add compiling flag for CFG_ONLY_802_11A
**  \main\maintrunk.MT5921\59 2008-06-12 20:28:21 GMT mtk01461
**  Remove unused compile flag of SCAN module which is work around for MPW.
**  \main\maintrunk.MT5921\58 2008-06-10 22:58:25 GMT mtk01084
**  set default country code to NULL
**  \main\maintrunk.MT5921\57 2008-05-30 18:44:43 GMT mtk01461
**  Add CFG_ROAMING flag
**  \main\maintrunk.MT5921\56 2008-05-23 10:02:44 GMT mtk01084
**  modify CFG_KEEP_ACTIVE_DWELL_TIME_ON_CONNECT_MSEC setting under SLT
**  \main\maintrunk.MT5921\55 2008-05-22 10:18:07 GMT mtk01461
**  \main\maintrunk.MT5921\54 2008-05-22 00:18:26 GMT mtk01461
**  Revise compile flag of INT LOOP Count for SDIO
**  \main\maintrunk.MT5921\53 2008-05-20 10:35:13 GMT mtk01084
**  add define for LP_SLT
**  \main\maintrunk.MT5921\52 2008-05-15 14:02:50 GMT mtk01461
**  Add CFG_SW_TCL flag
**  \main\maintrunk.MT5921\51 2008-05-13 10:17:48 GMT mtk01084
**  disable pattern search filter by default (CFG_L3_PATTERN_MATCH_WAKEUP = 0)
**  \main\maintrunk.MT5921\50 2008-04-28 17:22:40 GMT mtk01084
**  add definition of CFG_WORKAROUND_BG_SSID_SCAN_DONE
**  \main\maintrunk.MT5921\49 2008-04-21 13:45:23 GMT mtk01084
**  add compiler flag for workaround HEC 5512
**  \main\maintrunk.MT5921\48 2008-04-17 23:06:17 GMT mtk01461
**  Add AdHocMode default value
**  \main\maintrunk.MT5921\47 2008-04-17 19:37:03 GMT mtk01461
**  Add Data Port Test Code for SDIO Block/Byte Access
**  \main\maintrunk.MT5921\46 2008-04-02 20:45:40 GMT mtk01084
**  disable CFG_DBG_BEACON_RCPI_MEASUREMENT by default
**  \main\maintrunk.MT5921\45 2008-04-02 20:43:36 GMT mtk01084
**  Support for RCPI variance histogram
**  \main\maintrunk.MT5921\44 2008-04-01 23:52:40 GMT mtk01461
**  Update comments
**  \main\maintrunk.MT5921\43 2008-03-31 11:03:51 GMT mtk01461
**  Change back RX partial retain threshold to 2
**  \main\maintrunk.MT5921\42 2008-03-29 20:30:31 GMT mtk01461
**  Move the CFG_IBSS_POWER_SAVE to top for reference by others
**  \main\maintrunk.MT5921\41 2008-03-25 22:57:24 GMT mtk01084
**  add CFG_WORKAROUND_HEC_5269
**  \main\maintrunk.MT5921\40 2008-03-20 11:43:28 GMT mtk01084
**  add low power L3 compiler flag
**  \main\maintrunk.MT5921\39 2008-03-19 15:21:24 GMT mtk01461
**  Set disable RCPI check function as default
**  \main\maintrunk.MT5921\38 2008-03-18 11:52:00 GMT mtk01084
**  add PM related definition which is removed from pwr_mgt.h
**  \main\maintrunk.MT5921\37 2008-03-14 17:55:54 GMT mtk01385
**  1. Set all Rx packets to be retained to do WHQL test.
**  \main\maintrunk.MT5921\36 2008-03-13 14:27:13 GMT mtk01461
**  Add RCPI debug option
**  \main\maintrunk.MT5921\35 2008-02-12 23:26:40 GMT mtk01461
**  Add debug option - Packet Order for Linux
**  \main\maintrunk.MT5921\34 2008-02-12 15:51:39 GMT mtk01088
**  Add a flag to enable/disable TKIP TXOP 48M and 54M at FPGA issue
**  \main\maintrunk.MT5921\33 2008-02-05 12:06:48 GMT mtk01084
**  modify line order
**  \main\maintrunk.MT5921\32 2008-02-01 14:01:29 GMT mtk01385
**  1. add config for statistics counters.
**  \main\maintrunk.MT5921\31 2008-02-01 13:30:39 GMT mtk01385
**  1. change thermo timer default setting to disable fake thermo value.
**  \main\maintrunk.MT5921\30 2008-01-31 17:36:21 GMT mtk01385
**  1. add Thermo timer and initerrupt config flag.
**  2. add Thermo config flags, timer period, fake thermo value debug flag.
**
**  \main\maintrunk.MT5921\29 2008-01-31 16:16:57 GMT mtk01461
**  Update default value for some config
**  \main\maintrunk.MT5921\28 2008-01-21 16:26:25 GMT mtk01088
**  let the Rx packet is max 4x512 size
**  \main\maintrunk.MT5921\27 2008-01-07 15:05:30 GMT mtk01461
**  Add SDIO Enhance Support
**  \main\maintrunk.MT5921\26 2007-12-24 10:35:36 GMT mtk01084
**  disable IBSS_PS function by default
**  \main\maintrunk.MT5921\25 2007-12-11 14:53:06 GMT mtk01084
**  add definition for enabling workaround for FPGA
**  \main\maintrunk.MT5921\24 2007-12-11 00:08:58 GMT mtk01461
**  Update the Postfix of some define
**  \main\maintrunk.MT5921\23 2007-11-30 18:05:57 GMT mtk01088
**  move the define CETK_NDIS_PERFORMANCE_WORKAROUND from precomp.h to here
**
**  \main\maintrunk.MT5921\22 2007-11-26 21:34:42 GMT mtk01385
**  1. add statistics period timer period definitions.
**  \main\maintrunk.MT5921\21 2007-11-26 19:32:51 GMT mtk01461
**  Unify SCAN
**  \main\maintrunk.MT5921\20 2007-11-09 12:46:00 GMT mtk01084
**  re-arrange definition
**  \main\maintrunk.MT5921\19 2007-11-07 18:34:34 GMT mtk01461
**  Add Tx Fragmentation Support
**  \main\maintrunk.MT5921\18 2007-11-05 16:59:08 GMT mtk01425
**  1. Add CFG_INIT_TX_POWER_LIMIT
**  \main\maintrunk.MT5921\17 2007-11-02 00:50:47 GMT mtk01461
**  Unify TX Path for Normal and IBSS Power Save + IBSS neighbor learning
**  \main\maintrunk.MT5921\16 2007-11-01 16:45:23 GMT mtk01084
**  update for LP IOT test for beacon timeout function
**  \main\maintrunk.MT5921\15 2007-10-26 19:24:00 GMT mtk01084
**  modify IBSS-PS definition
**  \main\maintrunk.MT5921\14 2007-10-25 20:38:46 GMT mtk01084
**  update SCAN related configurations
**  \main\maintrunk.MT5921\13 2007-10-25 17:54:38 GMT mtk01461
**  Add IBSS POWER SAVE SUPPORT FLAG
** Revision 1.4  2007/06/27 02:22:58  MTK01461
** Fix typo
**
** Revision 1.3  2007/06/27 02:18:49  MTK01461
** Update SCAN_FSM, Initial(Can Load Module), Proc(Can do Reg R/W), TX API
**
** Revision 1.2  2007/06/25 06:16:23  MTK01461
** Update illustrations, gl_init.c, gl_kal.c, gl_kal.h, gl_os.h and RX API
**
*/

#ifndef _CONFIG_H
#define _CONFIG_H
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
#ifdef	MTK_WAPI_SUPPORT
	#define SUPPORT_WAPI 1
#else
	#define SUPPORT_WAPI 0
#endif
//2 Flags for OS capability
#define CFG_TCP_IP_CHKSUM_OFFLOAD               1 /* 1: Enable TCP/IP header checksum offload
                                                     0: Disable */

//2 Flags for Driver Features
#define CFG_TX_FRAGMENT                         1 /* 1: Enable TX fragmentation
                                                     0: Disable */

#define CFG_ROAMING                             1 /* 1(default): Enable Roaming
                                                     0: Disable */

#define CFG_IBSS_POWER_SAVE                     1 /* 1(default): Enable IBSS Power Save
                                                     0: Disable */

#define CFG_COUNTRY_CODE                        NULL //"US"

#define CFG_SUPPORT_802_11D                     1 /* 1(default): Enable 802.11d
                                                     0: Disable */

#define CFG_IBSS_POWER_SAVE_WITH_THROUGHPUT_ENHANCE  1 /* 1(default): Enable IBSS Power Save with
                                                                      throughput enhancement.
                                                          0: Disable */

#if BUILD_USE_EEPROM
#define CFG_SUPPORT_EXT_CONFIG      0 /* 1: Enable external configuration support (ex. NVRAM or file)
                                         0: Disable. Use EEPROM configuration. */
#else
#define CFG_SUPPORT_EXT_CONFIG      1 /* 1: Enable external configuration support (ex. NVRAM or file)
                                         0: Disable. Use EEPROM configuration. */
#endif

#if BUILD_META
#define CFG_SDIO_DEVICE_DRIVER_WO_NDIS                         1    /* 1: Enable: compile MT5921 to be a SDIO device I/O driver.
                                                                                 0: Disabled: compile MT5921 to be a miniport driver as usual. */
#else
#define CFG_SDIO_DEVICE_DRIVER_WO_NDIS                         0    /* 1: Enable: compile MT5921 to be a SDIO device I/O driver.
                                                                                 0: Disabled: compile MT5921 to be a miniport driver as usual. */
#endif

//2 Flags for Driver Parameters
/*------------------------------------------------------------------------------
 * Flags for EHPI Interface in Colibri Platform
 *------------------------------------------------------------------------------
 */
#define CFG_EHPI_FASTER_BUS_TIMING              0 /* 1: Do workaround for faster bus timing
                                                     0(default): Disable */

/*------------------------------------------------------------------------------
 * Flags for SDIO Interface
 *------------------------------------------------------------------------------
 */
#if defined(_HIF_SDIO)
    #define CFG_SDIO_STATUS_ENHANCE                 1 /* 1(default): Enable SDIO ISR & TX/RX status enhance mode
                                                         0: Disable */
    #define CFG_SDIO_TX_ENHANCE                     0 /* 1: Enable SDIO TX enhance mode(Multiple frames in single BLOCK CMD)
                                                         0(default): Disable */
    #define CFG_SDIO_RX_ENHANCE                     0 /* 1: Enable SDIO RX enhance mode(Multiple frames in single BLOCK CMD)
                                                         0(default): Disable */

    #if CFG_SDIO_TX_ENHANCE || CFG_SDIO_RX_ENHANCE
        #define CFG_SDIO_STATUS_ENHANCE             1
    #endif /* CFG_SDIO_TX_ENHANCE || CFG_SDIO_RX_ENHANCE */

    #define CFG_SDIO_DEBUG_AGGREGATING_RATIO        0 /* 1: Enable SDIO counter to check aggregating ratio
                                                         0(default): Disable */

    #define CFG_SDIO_FAST_BLOCK_CALCULATION_MODE    0 /* 1: Enable fast block calculation(No division).
                                                         0(default): Disable */

    #ifdef WINDOWS_CE
    #define CFG_SDIO_PATHRU_MODE                    1 /* 1: Suport pass through (PATHRU) mode
                                                         0: Disable */
    #else
    #define CFG_SDIO_PATHRU_MODE                    0 /* 0: Always disable if WINDOWS_CE is not defined */
    #endif
#else /* NOT SDIO */

    #define CFG_SDIO_STATUS_ENHANCE                 0 /* 0: Always disable if !_HIF_SDIO */
    #define CFG_SDIO_TX_ENHANCE                     0 /* 0: Always disable if !_HIF_SDIO */
    #define CFG_SDIO_RX_ENHANCE                     0 /* 0: Always disable if !_HIF_SDIO */
    #define CFG_SDIO_DEBUG_AGGREGATING_RATIO        0 /* 0: Always disable if !_HIF_SDIO */
    #define CFG_SDIO_PATHRU_MODE                    0 /* 0: Always disable if !_HIF_SDIO */

#endif /* _HIF_SDIO */

#define  CFG_EINT_HANDLED_IN_WLAN   1
//#undef   CFG_EINT_HANDLED_IN_WLAN	
/*------------------------------------------------------------------------------
 * Flags for TX path which are OS dependent
 *------------------------------------------------------------------------------
 */
/* NOTE(Kevin): If the Network buffer is non-scatter-gather like structure(without
 * NETIF_F_FRAGLIST in LINUX), then we can set CFG_TX_BUFFER_IS_SCATTER_LIST to "0"
 * for zero copy TX packets.
 * For scatter-gather like structure, we set "1", driver will do copy frame to
 * internal coalescing buffer before write it to FIFO.
 */
#if defined(LINUX)
    #define CFG_TX_BUFFER_IS_SCATTER_LIST       0 /* 1: Do frame copy before write to TX FIFO.
                                                        Used when Network buffer is scatter-gather.
                                                     0(default): Do not copy frame */
#else /* WINDOWS/WINCE */
    #define CFG_TX_BUFFER_IS_SCATTER_LIST       1
#endif /* LINUX */


/* NOTE: We copy frame to coalescing buffer before doing fragment process. */
#if CFG_TX_FRAGMENT
    #define CFG_FRAGMENT_COALESCING_BUFFER_SIZE 2048
#else
    #define CFG_FRAGMENT_COALESCING_BUFFER_SIZE 0
#endif /* CFG_TX_FRAGMENT  */


/* NOTE: The definition of CFG_COALESCING_BUFFER_SIZE is dependent. */
#if CFG_SDIO_TX_ENHANCE
    #define CFG_COALESCING_BUFFER_SIZE          8192
#elif CFG_TX_BUFFER_IS_SCATTER_LIST && !CFG_TX_FRAGMENT
    #define CFG_COALESCING_BUFFER_SIZE          2048
#else
    #define CFG_COALESCING_BUFFER_SIZE          0
#endif /* CFG_SDIO_TX_ENHANCE  */



/*------------------------------------------------------------------------------
 * Flags and Parameters for TX path
 *------------------------------------------------------------------------------
 */
/* <TODO> Kevin: alternatively we may set following definition in GLUE Layer,
 * and then let nicAllocateAdapterMemory() using those variables fed from GLUE
 * Layer instead of using definition directly for allocating memory.
 */
/* Maximum number of SW MSDU_INFO_T(Native Packet descriptor) for individual Traffic Class */
#define CFG_MAX_NUM_MSDU_INFO_FOR_TC0           10 /* number */
#define CFG_MAX_NUM_MSDU_INFO_FOR_TC1           10
#define CFG_MAX_NUM_MSDU_INFO_FOR_TC2           10
#define CFG_MAX_NUM_MSDU_INFO_FOR_TC3           10
#define CFG_MAX_NUM_MSDU_INFO_FOR_TS0           10
#if CFG_IBSS_POWER_SAVE
    /* NOTE(Kevin): Send ATIM by using TCM class of SW resource.
     */
    #define CFG_MAX_NUM_MSDU_INFO_FOR_TCM       24
#else
    #define CFG_MAX_NUM_MSDU_INFO_FOR_TCM       10
#endif /* CFG_IBSS_POWER_SAVE */

/* Maximum length of acceptable TX packet, if a frame from OS(MSDU)
 * or Protocol Layer(MMPDU) exceed this value, drop it directly to avoid coalescing
 * buffer overflow.
 */
/* TODO(Kevin): Will refine this value with the size of coalescing buffer */
#define CFG_TX_MAX_PKT_SIZE                     1600


#define CFG_TX_RET_TX_CTRL_EARLY                1 /* 1(default): Free the original TX buffer immediately
                                                        once it copy to coalescing buffer.
                                                     0: Free the original TX buffer after TX DONE */

#define CFG_TX_AGGREGATE_HW_FIFO                0 /* 1: When associated to Legacy AP(nonQoS),
                                                        do aggregate AC0/1/2 to AC2.
                                                     0(default): Arrange TX FIFO in QoS Style */

#define CFG_TX_STOP_WRITE_TX_FIFO_UNTIL_JOIN    0 /* 1: During roaming, stop write packets to HW
                                                        FIFO after join complete.
                                                        When join complete, packets in HW TX FIFO will
                                                        be flushed first, and then enable the flag to
                                                        allow packets to be writen to HW FIFO.

                                                        NOTE(Kevin): We should set to 1 for WM7. 
                                                          Because it use Native 802.11 frame format, thus
                                                          the packets in HW FIFO before join complete still
                                                          has RA equal to previous AP while roaming.

                                                     0: Packet can write to HW FIFO during JOIN.

                                                        NOTE(Kevin): Consider the roaming case for VOIP - If
                                                          we set to 0, we will still buffer VOIP datagram
                                                          to HW FIFO, however if it may takes long time to
                                                          finish the EAPOL to new AP and those VOIP datagram
                                                          will timeout by Application. So we may feel that 
                                                          set to 1 to this flag may has better performance
                                                          for roaming VOIP.
                                                          <TODO> Apply different lifetime to differ HW Queue */


/*------------------------------------------------------------------------------
 * Flags and Parameters for RX path
 *------------------------------------------------------------------------------
 */
/* Maximum number of SW RX packet buffer */
#define CFG_RX_MAX_PKT_NUM                      10

/* A threshold to retain RX packet buffer */
#define CFG_RX_MGMT_PKT_NUM_THRESHOLD           3

/* Maximum RX packet size, if exceed this value, drop incoming packet */
#define CFG_RX_MAX_PKT_SIZE                     2048

/* Minimum RX packet size, if lower than this value, drop incoming packet */
#define CFG_RX_MIN_PKT_SIZE                     10 /* 802.11 Control Frame is 10 bytes */


/*------------------------------------------------------------------------------
 * Flags and Parameters for Protocol Stack
 *------------------------------------------------------------------------------
 */
/* Maximum number of BSS in the SCAN list */
#define CFG_MAX_NUM_BSS_LIST                    48

/* Maximum size of IE buffer of each SCAN record */
#define CFG_IE_BUFFER_SIZE                      512

/* Maximum number of STA records */
#define CFG_MAX_NUM_STA_RECORD                  32


/*------------------------------------------------------------------------------
 * Flags and Parameters for Power management
 *------------------------------------------------------------------------------
 */
#define CFG_LP_PATTERN_SEARCH_SLT                                  1   /* 1: Enable LP SLT test
                                                           0: Disable LP SLT test */

/* The dwell time for staying in ACTIVE mode when connected to AP */
#if CFG_LP_PATTERN_SEARCH_SLT
#define CFG_KEEP_ACTIVE_DWELL_TIME_ON_CONNECT_MSEC  500
#else
#define CFG_KEEP_ACTIVE_DWELL_TIME_ON_CONNECT_MSEC  5000
#endif

#define CFG_USE_SW_ROOT_TIMER                       0

#define CFG_LOW_POWER_INST_START_ADDR               0

#define CFG_LP_IOT                                  0   /* 1: Enable LP IOT test
                                                           0: Disable LP IOT test */

#define CFG_IBSS_ATIM_WINDOW                        0   /* 0: Creating IBSS without PS function
                                                           non-0: create IBSS with PS function */

#define CFG_INIT_UAPSD_AC                           UAPSD_ALL//UAPSD_NONE//

#define CFG_INIT_POWER_SAVE_PROF                    ENUM_PSP_FAST_SWITCH

#define CFG_INIT_VOIP_INTERVAL                      0   /* > 0: Enable VOIP
                                                             0: Disable */

#define CFG_INIT_POLL_INTERVAL                      0   /* > 0: Enable CONTINUOUS POLL
                                                             0: Disable */

#if CFG_LP_PATTERN_SEARCH_SLT
#define CFG_L3_PATTERN_MATCH_WAKEUP                 1   /* 1: Enable L3 pattern search function
                                                           0: Disable L3 pattern search function */
#else
#define CFG_L3_PATTERN_MATCH_WAKEUP                 0   /* 1: Enable L3 pattern search function
                                                           0: Disable L3 pattern search function */
#endif

/* This should only be enabled under FPGA version, shall not be enabled under ASIC version */
#define CFG_FPGA_COMPENSATE_HALF_T_FOR_GUARD_TIME_HEC_4489   0

#define CFG_WORKAROUND_HEC_5269                     1
#define CFG_WORKAROUND_HEC_5512                     1

#define CFG_WORKAROUND_BG_SSID_SCAN_DONE            1

#define CFG_WORKAROUND_HEC_5988                     1

#define CFG_WORKAROUND_HEC_6796                     1



/*------------------------------------------------------------------------------
 * 802.11i RSN Pre-authentication PMKID cahce maximun number
 *------------------------------------------------------------------------------
 */
#define CFG_MAX_PMKID_CACHE                     16      /* max number of PMKID cache 
                                                           16(default) : The Max PMKID cache */

/*------------------------------------------------------------------------------
 * Flags and Parameters for Ad-Hoc
 *------------------------------------------------------------------------------
 */
#define CFG_INIT_ADHOC_MODE                     AD_HOC_MODE_MIXED_11BG


/*------------------------------------------------------------------------------
 * Flags and Parameters for Load Setup Default
 *------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
 * Flags for enable 802.11A Band setting
 *------------------------------------------------------------------------------
 */
#define CFG_ONLY_802_11A                        0 /* 1: Enable this will let driver run
                                                    at 802.11a only, disable 11g */


#define CFG_INIT_TX_POWER_LIMIT                 10


#if CFG_ONLY_802_11A
#define CFG_SUPPORT_SSID_RECOVER_STATE          0 /* 1: Support ARB SSID recover state
                                                     0: Do not support ARB SSID recover state */
#else
#define CFG_SUPPORT_SSID_RECOVER_STATE          1 /* 1: Support ARB SSID recover state
                                                     0: Do not support ARB SSID recover state */
#endif

/*------------------------------------------------------------------------------
 * Flags and Parameters for Interrupt Process
 *------------------------------------------------------------------------------
 */
#if defined(_HIF_SDIO) && defined(WINDOWS_CE)
    #define CFG_IST_LOOP_COUNT                  3
#else
    #define CFG_IST_LOOP_COUNT                  3
#endif /* _HIF_SDIO */

#define CFG_INT_WRITE_CLEAR                     0

#define CFG_TEST_IO_PIN 1 /* 1: Enable INT_N and GPIO_0 Pin test.
                                                             0: Disable */

//2 Flags for Driver Debug Options
/*------------------------------------------------------------------------------
 * Flags of TX Debug Option. NOTE(Kevin): Confirm with SA before modifying following flags.
 *------------------------------------------------------------------------------
 */
#define CFG_TX_DBG_TFCB_CHKSUM                  0 /* 1: Enable diagnosing TX by using TFCB Checksum by
                                                        halTxEnableDebugOption().
                                                     0: Disable */

#define CFG_TX_DBG_INCREASED_PID                0
/* 1: Enable diagnosing TX by using PID
 * 0: Disable
 *    Assign a progressively increased number to PID field of TFCB,
 * we may set it by a "Packet Count per TX Queue", and then check PID
 * field in TX_STATUS.
 */

#define CFG_TX_DBG_FIXED_PID                    0
/* 1: Enable diagnosing TX by using PID
 * 0: Disable
 *   Assign a fixed number to PID field of TFCB, we may set it by a
 * "Fixed TX Queue ID", and then check PID field in TX_STATUS.
 * <NOTE> Conflict with CFG_TX_INCREASED_PID
 */

#if (CFG_TX_DBG_INCREASED_PID && CFG_TX_DBG_FIXED_PID)
    #error Conflict of compiler flags.
#endif /* (CFG_TX_DBG_INCREASED_PID && CFG_TX_DBG_FIXED_PID) */

#define CFG_TX_DBG_SEQ_NUM                      0 /* 1: Enable tracing of TX SEQ_NUM from
                                                        TX_STATUS.
                                                     0: Disable */

#define CFG_TX_DBG_INT_FALSE_ALARM              0 /* 1: Enable diagnose TX_DONE INT False Alarm
                                                        (Need DBG == 1 for ASSERT()).
                                                     0(default): Disable */


#if DBG || BUILD_QA_DBG
#define CFG_TX_DBG_MGT_BUF                      1 /* 1: Enable diagnosing maximum depth
                                                        of allocated TX Management Buffer.
                                                     0: Disable */
#else
#define CFG_TX_DBG_MGT_BUF                      0
#endif /* DBG || BUILD_QA_DBG */


#define CFG_TX_DBG_PACKET_ORDER                 0 /* 1: Enable diagnosing Packet Order
                                                        to make sure they are first-in-first-out
                                                        if belong to the same TID(Linux only).
                                                     0(default): Disable */

/*------------------------------------------------------------------------------
 * Flags for debugging Protocol Stacks
 *------------------------------------------------------------------------------
 */
#if DBG || BUILD_QA_DBG
#define CFG_DBG_STA_RECORD                      1 /* 1: Enable diagnosing STA_RECORD.
                                                     0(default): Disable */
#else
#define CFG_DBG_STA_RECORD                      0
#endif /* DBG || BUILD_QA_DBG */

/*------------------------------------------------------------------------------
 * Flags for Internal 32K Memory Test
 *------------------------------------------------------------------------------
 */
#define CFG_INTERNAL_MEMORY_TEST                0 /* 1: Enable diagnose internal memory(HW FIFO).
                                                     0(default): Disable */

#define CFG_DATA_PORT_ACCESS_TEST               0 /* 1: Enable diagnose internal memory(HW FIFO).
                                                     0(default): Disable */

/*------------------------------------------------------------------------------
 * Flags for Statistics
 *------------------------------------------------------------------------------
 */
#define CFG_STATISTICS_TIMER_EN                 0 /* 1: Get Statistics from MCR in Timer.
                                                     0(default): Get Statistics from MCR in INT. */

#define CFG_TIMER_PEEK_HW_COUNTERS_PERIOD_MSEC        1677720  //Millisecond, for timer use
#define CFG_INT_PEEK_HW_COUNTERS_TIMEOUT_MSEC         1677720  //Millisecond, for int use
                                                      /* 2^24(bit) * 100us ~= 1677second */
/*------------------------------------------------------------------------------
 * Flags for Workaround
 *------------------------------------------------------------------------------
 */
#define CETK_NDIS_PERFORMANCE_WORKAROUND        1 /* Workaround CETK NDIS Performance
                                                     Protocol Reserved filed no clear issue
                                                     1 (default) : Enabled the workaround */

/*------------------------------------------------------------------------------
 * Flags for Thermo
 *------------------------------------------------------------------------------
 */
#define CFG_THERMO_INT_EN                       1
#define CFG_THERMO_TIMER_EN                     0  /* 1: Enable Thermo Timer
                                                      0: Disable */
#if (CFG_THERMO_INT_EN && CFG_THERMO_TIMER_EN)
    #error Conflict of compiler flags, Thermo.
#endif /* (CFG_THERMO_INT_EN && CFG_THERMO_TIMER_EN) */

#if CFG_THERMO_TIMER_EN
//#define CFG_PEEK_THERMO_PERIOD_MSEC             5000 // Millisecond
#define CFG_PEEK_THERMO_PERIOD_MSEC             1000 // Millisecond
#define CFG_FAKE_THERMO_VALUE_DBG_EN            0  /* 1: Enable debug fake therm value.
                                                      0: Disable */
#else
#define CFG_FAKE_THERMO_VALUE_DBG_EN            0  /* 0: Always disable if TIMER_EN == 0 */
#endif /* CFG_THERMO_TIMER_EN */


/*------------------------------------------------------------------------------
 * Flags for debugging RCPI report value
 *------------------------------------------------------------------------------
 */
#define CFG_PEEK_RCPI_VALUE_PERIOD_SEC          0 // Seconds
                                                  /* > 0: Enable debug RCPI value
                                                       0: Disable */

/*------------------------------------------------------------------------------
 * Flags for debugging RCPI report value
 *------------------------------------------------------------------------------
 */
#define CFG_DBG_BEACON_RCPI_MEASUREMENT         0 /* 1: Enable
                                                     0: Disable */

/*------------------------------------------------------------------------------
 * Flags for comparing TSF by using SW
 *------------------------------------------------------------------------------
 */
#define CFG_SW_TCL                              0 /* 1: Using SW to compare the TSF.
                                                     0(default): Use HW from RFB. */

/*------------------------------------------------------------------------------
 * Flags for LINT
 *------------------------------------------------------------------------------
 */
#define LINT_SAVE_AND_DISABLE                   /*lint -save -e* */

#define LINT_RESTORE                            /*lint -restore */

#define LINT_EXT_HEADER_BEGIN                   LINT_SAVE_AND_DISABLE

#define LINT_EXT_HEADER_END                     LINT_RESTORE

/*------------------------------------------------------------------------------
 * Flags for PTA
 *------------------------------------------------------------------------------
 */
#define PTA_ENABLED                             1
#if PTA_ENABLED 
#if SUPPORT_NEW_PTA_BOARD
#define PTA_NEW_BOARD_DESIGN                    1
#else
#define PTA_NEW_BOARD_DESIGN                    0
#endif
#endif
/*------------------------------------------------------------------------------
 * Flags for testing WMM VI
 *------------------------------------------------------------------------------
 */
#define CFG_INIT_VI_AIFS_BIAS                   0

#define CFG_INIT_VI_MAX_TXOP_LIMIT              0xFFFF

/*------------------------------------------------------------------------------
 * Flags for enabled the stream io function, which used to provide 
 * a extern ioctl function control the MT5921 power source 
 *------------------------------------------------------------------------------
 */
#define SUPPORT_STREAM_IO                       0 /* default: disable */

/*------------------------------------------------------------------------------
 * Flags for enabled the code support for WPS 
 *------------------------------------------------------------------------------
 */
#define SUPPORT_WPS                             1 /* default: enable */

#define SUPPORT_CR1809_WPS_AP_WORKAROUND        1 /* default: enable */

/*------------------------------------------------------------------------------
 * Flags for enabled the code support for China WAPI
 *------------------------------------------------------------------------------
 */
#if SUPPORT_WAPI
/* Have to enable this for header translation */
#undef CFG_TX_FRAGMENT
#define CFG_TX_FRAGMENT                         1 /* 1: Enable TX fragmentation
                                                                                            0: Disable */

#define SUPPORT_WPI_AVOID_LOCAL_BUFFER          1 /* 0: use local buffer,
                                                     1: Default Use adapter buffer alloc at driver init */

#endif

/*------------------------------------------------------------------------------
 * MODE for LED support
 *------------------------------------------------------------------------------
 */
#define CFG_LED_MODE_NONE   0
#define CFG_LED_MODE_TX     1
#define CFG_LED_MODE_RX     2
#define CFG_LED_MODE_TX_RX  3

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
#endif /* _CONFIG_H */


