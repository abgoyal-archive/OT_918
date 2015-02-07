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


/*! \file   mtkwmt.h
    \brief  WMT header

    Define functions provided by WMT task.
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

#ifndef _MTKWMT_H_
#define _MTKWMT_H_

/*******************************************************************************
*                         C O M P I L E R   F L A G S
********************************************************************************
*/


/*******************************************************************************
*                    E X T E R N A L   R E F E R E N C E S
********************************************************************************
*/

#include "mtk_porting.h"

/*******************************************************************************
*                              C O N S T A N T S
********************************************************************************
*/
// TODO:  default baud rate is dependent on Chip ID?
#define WMT_DEFAULT_BAUD_RATE   (115200)

typedef enum _ENUM_DRV_TYPE_T {
    DRV_TYPE_BT = 0,
    DRV_TYPE_FM = 1,
    DRV_TYPE_GPS = 2,
    DRV_TYPE_WIFI = 3,
    DRV_TYPE_WMT = 4,
    DRV_TYPE_STP = 5,
    DRV_TYPE_SDIO1 = 6,
    DRV_TYPE_SDIO2 = 7,
    DRV_TYPE_LPBK = 8,
    DRV_TYPE_MAX
} ENUM_DRV_TYPE_T, *P_ENUM_DRV_TYPE_T;

typedef enum _ENUM_WMT_HIF_T
{
    WMT_HIF_UART = 0,
    WMT_HIF_SDIO = 1,
    WMT_HIF_MAX
} ENUM_WMT_HIF_T, *P_ENUM_WMT_HIF_T;

typedef enum _ENUM_WMT_FM_T
{
    WMT_FM_INVALID = 0,
    WMT_FM_I2C = 1,
    WMT_FM_COMM = 2,
    WMT_FM_MAX
} ENUM_WMT_FM_T, *P_ENUM_WMT_FM_T;

typedef enum _ENUM_WMT_OPID_T {
    WMT_OPID_HIF_CONF = 0,
    WMT_OPID_POWER_ON = 1,
    WMT_OPID_POWER_OFF = 2,
    WMT_OPID_CLT_REG = 3, /* REG_CLIENT */
    WMT_OPID_CLT_UNREG = 4, /* UNREG_CLIENT */
    WMT_OPID_STP_READY = 5,
    WMT_OPID_FUNC_ON = 6,
    WMT_OPID_FUNC_OFF = 7,
    WMT_OPID_REG_RW = 8,
    WMT_OPID_EXIT = 9,
    WMT_OPID_POWER_SAVE = 10,
    WMT_OPID_DSNS = 11,
    WMT_OPID_LPBK = 12,
    WMT_OPID_CMD_TEST = 13,
    WMT_OPID_HW_RST = 14,
    WMT_OPID_SW_RST = 15,
    WMT_OPID_BAUD_RST = 16,
    WMT_OPID_STP_RST = 17,
    WMT_OPID_THERM_CTRL = 18,
    WMT_OPID_EFUSE_RW = 19,
    WMT_OPID_MAX
} ENUM_WMT_OPID_T, *P_ENUM_WMT_OPID_T;

typedef enum _ENUM_WMT_CTRL_T {
    WMT_CTRL_POWER_OFF = 0, /* whole chip power off */
    WMT_CTRL_POWER_ON = 1, /* whole chip power on */
    WMT_CTRL_STP_CLOSE = 2,
    WMT_CTRL_STP_OPEN = 3,
    WMT_CTRL_STP_CONF = 4,
    WMT_CTRL_FREE_PATCH = 5,
    WMT_CTRL_GET_PATCH = 6,
    WMT_CTRL_BAUDRATE = 7,
    WMT_CTRL_NOTIFY_POWER_ON = 8,
    WMT_CTRL_SDIO_SLOT = 9, /* enable/disable SDIO1/2 of MT6620 */
    WMT_CTRL_SDIO_FUNC = 10, /* probe/remove STP/Wi-Fi driver in SDIO1/2 of MT6620*/
    WMT_CTRL_HWVER_SET = 11, 
    WMT_CTRL_HWVER_GET = 12,
    WMT_CTRL_BOARD_SET = 13, 
    WMT_CTRL_BOARD_GET = 14,
    WMT_CTRL_STP_RST   = 15,
    WMT_CTRL_GET_WMT_CONF = 16,
    WMT_CTRL_MAX
} ENUM_WMT_CTRL_T, *P_ENUM_WMT_CTRL_T;

typedef enum {
    GPS_LNA_DISABLE = 0,
    GPS_LNA_ENABLE = 1,
    GPS_LNA_ENABLE_MAX
} WMT_GPS_LNA_CONF_TYPE;



typedef enum {
    WMT_STP_CONF_EN = 0,
    WMT_STP_CONF_RDY = 1,
    WMT_STP_CONF_MODE = 2,
    WMT_STP_CONF_MAX
} WMT_STP_CONF_TYPE;

typedef enum {
    WMT_SDIO_SLOT_INVALID = 0,
    WMT_SDIO_SLOT_SDIO1 = 1, /* Wi-Fi dedicated SDIO1*/
    WMT_SDIO_SLOT_SDIO2 = 2,
    WMT_SDIO_SLOT_MAX
} WMT_SDIO_SLOT_NUM;

typedef enum {
    WMT_SDIO_FUNC_STP = 0,
    WMT_SDIO_FUNC_WIFI = 1,
    WMT_SDIO_FUNC_MAX
} WMT_SDIO_FUNC_TYPE;

#define DWCNT_HIF_CONF  (4)
#define DWCNT_STRAP_CONF  (4)
#define DWCNT_RESERVED (8)
#define DWCNT_CTRL_DATA  (16)

#define BCNT_PATCH_BUF_HEADROOM (8)

#define WMT_OP_BIT(x) (0x1UL << x)
#define WMT_OP_HIF_BIT WMT_OP_BIT(0)

/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/
	typedef struct __combo_pin_setting
	{
		UINT32 regaddr;
		UINT32 value;
		UINT32 offset;
		UINT32 bitwidth;
	}combo_pin_setting;
	
	typedef struct __combo_lna_setting
	{
		combo_pin_setting PULLDN;
		combo_pin_setting PULLUP;
		combo_pin_setting IOMODE;
		combo_pin_setting OUTPIN;
	}combo_lna_setting;

typedef struct _WMT_HIF_CONF {
    UINT32 hifType; // HIF Type
    UINT32 au4HifConf[DWCNT_HIF_CONF]; // HIF Config
    UINT32 au4StrapConf[DWCNT_STRAP_CONF]; // Strap Config
} WMT_HIF_CONF, *P_WMT_HIF_CONF;

typedef struct _WMT_GEN_CONF {
    unsigned char cfg_exist;
    
    unsigned char coex_wmt_ant_mode;
    unsigned char coex_wmt_wifi_time_ctl;
    unsigned char coex_wmt_ext_pta_dev_on;

    unsigned char coex_bt_rssi_upper_limit;
    unsigned char coex_bt_rssi_mid_limit;
    unsigned char coex_bt_rssi_lower_limit;
    unsigned char coex_bt_pwr_high;
    unsigned char coex_bt_pwr_mid;
    unsigned char coex_bt_pwr_low;

    unsigned char coex_wifi_rssi_upper_limit;
    unsigned char coex_wifi_rssi_mid_limit;
    unsigned char coex_wifi_rssi_lower_limit;
    unsigned char coex_wifi_pwr_high;
    unsigned char coex_wifi_pwr_mid;
    unsigned char coex_wifi_pwr_low;

    unsigned char coex_ext_pta_hi_tx_tag;
    unsigned char coex_ext_pta_hi_rx_tag;
    unsigned char coex_ext_pta_lo_tx_tag;
    unsigned char coex_ext_pta_lo_rx_tag;
    unsigned short coex_ext_pta_sample_t1;
    unsigned short coex_ext_pta_sample_t2;
    unsigned char coex_ext_pta_wifi_bt_con_trx;

    unsigned int coex_misc_ext_pta_on;
    unsigned int coex_misc_ext_feature_set;
	unsigned char wmt_gps_lna_enable;
	unsigned char wmt_gps_lna_pin;
} WMT_GEN_CONF, *P_WMT_GEN_CONF;

typedef struct _WMT_OP {
    UINT32 opId; // Event ID
    UINT32 u4InfoBit; // Reserved
    UINT32 au4OpData[sizeof(WMT_HIF_CONF)/4 + DWCNT_RESERVED]; // OP Data
} WMT_OP, *P_WMT_OP;

typedef struct _WMT_CTRL_DATA {
    UINT32 ctrl;
    UINT32 au4CtrlData[DWCNT_CTRL_DATA];
} WMT_CTRL_DATA, *P_WMT_CTRL_DATA;

typedef INT32 (*PF_WMT_CTRL)(P_WMT_CTRL_DATA pWmtCtrl);
/* common interface */
typedef INT32 (*PF_WMT_TX)(UINT8 *data, UINT32 size, UINT32 *written_size);
typedef INT32 (*PF_WMT_RX)(UINT8 *data, UINT32 size, UINT32 *read_size);
typedef INT32 (*STP_PSM_CB)(INT32);
typedef void  (*STP_FLUSH_CB)(UINT32);
typedef struct
{
    PF_WMT_CTRL cb_wmt_ctrl;

    /* common interface */
    PF_WMT_TX cb_tx;
    PF_WMT_TX cb_tx_raw;
    PF_WMT_RX cb_rx;

    STP_FLUSH_CB       cb_flush_rx;

    /* mutex */
    MUTEX_CREATE    cb_mutex_create;
    MUTEX_DESTROY   cb_mutex_destroy;
    MUTEX_LOCK      cb_mutex_lock;
    MUTEX_UNLOCK    cb_mutex_unlock;

    /* debug */
    DBG_PRINT       cb_dbg_print;
    DBG_ASSERT      cb_dbg_assert;

    /* timer */
    TIMER_CREATE    cb_timer_create;
    TIMER_DESTROY   cb_timer_destroy;
    TIMER_START     cb_timer_start;
    TIMER_STOP      cb_timer_stop;

    /* kernel lib */
    SYS_MEMCPY      cb_memcpy;
    SYS_MEMSET      cb_memset;
    SYS_MEMCMP      cb_memcmp;
    SYS_SPRINTF     cb_sprintf;
}mtkwmt_callback;

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
/*****************************************************************************
* FUNCTION
*  mtk_wcn_wmt_init
* DESCRIPTION
*  init STP kernel
* PARAMETERS
*  cb_func      [IN] function pointers of system APIs
*  bStpReg      [IN] is stp driver registered (Linux: false, WinMo: true)
* RETURNS
*  INT32    0 = success, others = failure
*****************************************************************************/
extern INT32 mtk_wcn_wmt_init(const mtkwmt_callback * const cb_func, MTK_WCN_BOOL bStpReg);

/*****************************************************************************
* FUNCTION
*  mtk_wcn_wmt_deinit
* DESCRIPTION
*  deinit STP kernel
* PARAMETERS
*  void
* RETURNS
*  INT32    0 = success, others = failure
*****************************************************************************/
extern INT32 mtk_wcn_wmt_deinit(void);

/*****************************************************************************
* FUNCTION
*  mtk_wcn_wmt_handler
* DESCRIPTION
*  handle WMT_OP
* PARAMETERS
*  pWmtOp        [IN]        pointer to WMT_OP struct
* RETURNS
*  INT32    0 = success, others = error
*****************************************************************************/
extern INT32 mtk_wcn_wmt_handler(P_WMT_OP pWmtOp);

#endif /* _MTKWMT_H_ */

