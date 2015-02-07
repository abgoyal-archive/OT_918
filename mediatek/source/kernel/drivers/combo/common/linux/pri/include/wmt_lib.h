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


/*! \file   wmt_lib.h
    \brief  Declaration of library functions

    Any definitions in this file will be shared among GLUE Layer and internal Driver Stack.
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

#ifndef _WMT_LIB_H
#define _WMT_LIB_H

/*******************************************************************************
*                         C O M P I L E R   F L A G S
********************************************************************************
*/

#define CFG_WMT_PS_SUPPORT  1
#define CFG_WMT_PS_DEBUG_SUPPORT 0
#define CFG_WMT_GPIO_DBG_PIN 0 /* double check gpio assignment before enable it! */

/*******************************************************************************
*                    E X T E R N A L   R E F E R E N C E S
********************************************************************************
*/
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/wait.h>
#include <linux/string.h>
#include <linux/kthread.h>
#include <linux/sched.h>
#include <linux/jiffies.h>
#include <linux/limits.h>
#include <linux/firmware.h>
#include <linux/vmalloc.h>
#include <linux/slab.h>

#if CFG_WMT_PS_SUPPORT
#include <linux/proc_fs.h>
#include <linux/workqueue.h>
#include <linux/wait.h>
#include <linux/time.h>
#include <linux/delay.h>
#include <mach/mt_combo.h>
#endif

#include "config.h"
#include "mtkwmt.h"
#include "wmt_exp.h"
#include "mtkstp.h"
#include "stp_psm.h"

/* declared in stp_chrdev_wmt.c */
extern unsigned int gWmtDbgLvl;

/*******************************************************************************
*                              C O N S T A N T S
********************************************************************************
*/
#define WMT_DRIVER_NAME "mtk_stp_wmt"

/* OP command ring buffer for WMT_drv and WMTd: must be power of 2 */
#define WMT_OP_BUF_SIZE (16)

/* debug information */
#define PFX "[WMT]"
#define WMT_LOG_LOUD    4
#define WMT_LOG_DBG 	3
#define WMT_LOG_INFO    2
#define WMT_LOG_WARN    1
#define WMT_LOG_ERR 	0

/*
3(retry times) * 180 (STP retry time out) 
+ 10 (firmware process time) + 
10 (transmit time) + 
10 (uart process -> WMT response pool) + 
230 (others) 
*/
#define WMT_LIB_RX_TIMEOUT 2000/*800-->cover v1.2phone BT function on time (~830ms)*/	
/*
open wifi during wifi power on procedure 
(because wlan is insert to system after mtk_hif_sdio module, 
so wifi card is not registered to hif module 
when mtk_wcn_wmt_func_on is called by wifi through rfkill)
*/
#define MAX_WIFI_ON_TIME 5500

#ifndef WMT_PWRON_RTY_DFT
#define WMT_PWRON_RTY_DFT 2
#endif

#define MAX_RETRY_TIME_DUE_TO_RX_TIMEOUT WMT_PWRON_RTY_DFT * WMT_LIB_RX_TIMEOUT
#define MAX_EACH_FUNC_ON_WHEN_CHIP_POWER_ON_ALREADY WMT_LIB_RX_TIMEOUT /*each WMT command*/
#define MAX_FUNC_ON_TIME (MAX_WIFI_ON_TIME + MAX_RETRY_TIME_DUE_TO_RX_TIMEOUT + MAX_EACH_FUNC_ON_WHEN_CHIP_POWER_ON_ALREADY * 3)

#define MAX_EACH_FUNC_OFF WMT_LIB_RX_TIMEOUT + 1000 /*1000->WMT_LIB_RX_TIMEOUT + 1000, logical judgement*/
#define MAX_FUNC_OFF_TIME MAX_EACH_FUNC_OFF * 4

#define MAX_EACH_WMT_CMD WMT_LIB_RX_TIMEOUT + 1000 /*1000->WMT_LIB_RX_TIMEOUT + 1000, logical judgement*/

#define MTK_WMT_WAKELOCK_SUPPORT
/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/
/* Linux wrapper for WMT_OP */
typedef struct _WMT_LXOP {
    WMT_OP op;
    UINT32 u4WaitMs;
    INT32 result;
    struct completion comp;
} WMT_LXOP, *P_WMT_LXOP;

typedef struct _WMT_LXOP_Q {
    struct mutex lock;
    UINT32 write;
    UINT32 read;
    UINT32 size;
    P_WMT_LXOP queue[WMT_OP_BUF_SIZE];
} WMT_LXOP_Q, *P_WMT_LXOP_Q;

/* bit field offset definition */
typedef enum {
    WMT_STAT_PWR = 0, /* is powered on */
    WMT_STAT_STP_REG = 1, /* is STP driver registered: */
    WMT_STAT_STP_OPEN = 2, /* is STP opened: default FALSE*/
    WMT_STAT_STP_EN = 3, /* is STP enabled: default FALSE*/
    WMT_STAT_STP_RDY = 4, /* is STP ready for client: default FALSE*/
    WMT_STAT_RX = 5, /* is rx data available */
    WMT_STAT_CMD = 6, /* is cmd string to be read */
    WMT_STAT_SDIO1_ON = 7, /* is SDIO1 on */
    WMT_STAT_SDIO2_ON = 8, /* is SDIO2 on */
    WMT_STAT_SDIO_WIFI_ON = 9, /* is Wi-Fi SDIO function on */
    WMT_STAT_SDIO_STP_ON = 10, /* is STP SDIO function on */
    WMT_STAT_RST_ON = 11,
    WMT_STAT_MAX
} WMT_STAT;

typedef enum {
    WMT_IRQ_BGF = 0,
    WMT_IRQ_WIFI = 1,
    WMT_IRQ_ALL = 2,
    WMT_IRQ_MAX
} WMT_IRQ;

typedef void (*PF_STP_RX_CB)(void);
typedef int (*PF_STP_REG)(
    int type, /*  */
    PF_STP_RX_CB rxcb /*  */
    );
typedef INT32 (*PF_STP_TX)(
    UINT8 *buffer, /*  */
    UINT32 length, /*  */
    UINT8 type /*  */
    );
typedef INT32 (*PF_STP_RX)(
    UINT8 *buffer, /*  */
    UINT32 length, /*  */
    UINT8 type /*  */
    );
typedef void (*PF_STP_RX_FLUSH)(
    UINT32 type
    );
typedef INT32 (*PF_STP_CONF)(
    WMT_STP_CONF_TYPE type, /* enable, mode, ready */
    UINT32 value /* conf value */
    );

typedef struct {
    PF_STP_REG stp_reg; /* STP register function*/
    PF_STP_TX stp_tx; /* STP tx data function*/
    PF_STP_TX stp_tx_raw; /* STP tx raw data function*/
    PF_STP_RX stp_rx; /* STP rx data function*/
    PF_STP_RX_FLUSH stp_rx_flush;
    PF_STP_CONF stp_conf; /* STP config function*/
} WMT_STP_FUNC, *P_WMT_STP_FUNC;

typedef struct {
    PF_WMT_CB fdrv_rst[4];   
} WMT_FDRV_CB, *P_WMT_FDRV_CB;

typedef struct {
    UINT32 hw_ver;
    UINT32 fw_ver;
    UINT32 patch_ver;
} WMT_COMBO_VER, *P_WMT_COMBO_VER;

typedef struct {
    UINT32 btype;
} WMT_BOARD_INFO, *P_WMT_BOARD_INFO;

typedef struct _DEV_WMT {
    /* WMTd thread information */
    struct task_struct *pWmtd;   /* main thread (wmtd) handle */
    wait_queue_head_t rWmtdWq;  /*WMTd command wait queue */
    unsigned long state; /* bit field of WMT_STAT */

    /* STP context information */
    wait_queue_head_t rWmtRxWq;  /* STP Rx wait queue */
    WMT_STP_FUNC rStpFunc; /* STP functions */
    WMT_FDRV_CB  rFdrvCb;

    /* WMT Configurations */
    WMT_HIF_CONF  rWmtHifConf;
    WMT_GEN_CONF  rWmtGenConf;   
    
    /* Patch information */
    char cPatchName[NAME_MAX + 1];
	char cFullPatchName[NAME_MAX + 1];
    const struct firmware *pPatch;

    char cWmtcfgName[NAME_MAX + 1];
    const struct firmware *pWmtcfg;

    WMT_LXOP_Q rFreeOpQ; /* free op queue */
    WMT_LXOP_Q rActiveOpQ; /* active op queue */
    WMT_LXOP arQue[WMT_OP_BUF_SIZE]; /* real op instances */

    /* Registered Client Information */
    WMT_REGISTER_CLIENT arWmtClient[WMTDRV_TYPE_MAX];

    /* cmd str buffer */
    char cCmd[NAME_MAX + 1];
    int cmd_result;
    struct completion cmd_comp;
    wait_queue_head_t cmd_wq; /* read command queues */

    /* WMT loopback Thread Information */
    WMT_BOARD_INFO board_info;
    WMT_COMBO_VER combo_ver;
}DEV_WMT, *P_DEV_WMT;

typedef struct _COEX_BUF{
	UINT8 buffer[100];
	INT32 avail_size; 
}COEX_BUF, *P_COEX_BUF;
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

#define ENABLE_PSM_MONITOR() \
do{\
	if (g_psm_enable) {\
		mtk_wcn_stp_psm_enable(g_psm_idle_time_to_sleep);\
	}\
}while(0)


#define DISABLE_PSM_MONITOR() \
do{\
	if (g_psm_enable) {\
		mtk_wcn_stp_psm_disable();\
	}\
}while(0)

/* FIXME: apply KERN_* definition? */
#define WMT_LOUD_FUNC(fmt, arg...)    if (gWmtDbgLvl >= WMT_LOG_LOUD) { printk(DBG_NAME"%s:"  fmt, __FUNCTION__ ,##arg);}
#define WMT_DBG_FUNC(fmt, arg...)    if (gWmtDbgLvl >= WMT_LOG_DBG) { printk(DBG_NAME "%s:"  fmt, __FUNCTION__ ,##arg);}
#define WMT_INFO_FUNC(fmt, arg...)   if (gWmtDbgLvl >= WMT_LOG_INFO) { printk(DBG_NAME "%s:"  fmt, __FUNCTION__ ,##arg);}
#define WMT_WARN_FUNC(fmt, arg...)   if (gWmtDbgLvl >= WMT_LOG_WARN) { printk(DBG_NAME "%s:"  fmt, __FUNCTION__ ,##arg);}
#define WMT_ERR_FUNC(fmt, arg...)    if (gWmtDbgLvl >= WMT_LOG_ERR) { printk(DBG_NAME "%s(%d):"  fmt, __FUNCTION__ , __LINE__, ##arg);}
#define WMT_TRC_FUNC(f)              if (gWmtDbgLvl >= WMT_LOG_DBG) { printk(DBG_NAME "<%s> <%d>\n", __FUNCTION__, __LINE__);}

/*******************************************************************************
*                  F U N C T I O N   D E C L A R A T I O N S
********************************************************************************
*/

/* Library functions: for OS Glue Layer */
P_DEV_WMT wmt_drv_create (void);
VOID wmt_drv_destroy (P_DEV_WMT pWmtDev);

INT32 wmt_drv_init (P_DEV_WMT pWmtDev);
VOID wmt_drv_deinit (P_DEV_WMT pWmtDev);

INT32 wmt_drv_start (P_DEV_WMT pWmtDev);
VOID wmt_drv_stop (P_DEV_WMT pWmtDev);

/* Configuration functions: for wmt_lib use */
INT32 wmt_lib_conf_init (P_DEV_WMT pWmtDev);
INT32 wmt_lib_conf_file_init(P_DEV_WMT pWmtDev);
INT32 wmt_lib_conf_file_deinit(P_DEV_WMT pWmtDev);
    
/* Platform functions: for wmt_lib use */
INT32 wmt_lib_plat_init (P_DEV_WMT pWmtDev);
INT32 wmt_lib_plat_deinit (P_DEV_WMT pWmtDev);
INT32 wmt_lib_plat_power (P_DEV_WMT pWmtDev, UINT32 on);
INT32 wmt_lib_plat_irq (P_DEV_WMT pWmtDev,UINT32 src, UINT32 on);
INT32 wmt_lib_plat_sdio_slot (
    P_DEV_WMT pWmtDev,
    UINT32 u4On,
    UINT32 u4SlotNum);

INT32 wmt_lib_efuse_rw (UINT32 isWrite, UINT32 offset, PUINT32 pvalue, UINT32 mask);
INT32 wmt_lib_reg_rw (UINT32 isWrite, UINT32 offset, PUINT32 pvalue, UINT32 mask);
INT32 wmt_lib_bd_set(UINT32 idx, UINT32 value);
INT32 wmt_lib_bd_get(UINT32);
INT32 wmt_lib_rstmsg_snd(ENUM_WMTRSTMSG_TYPE_T);
INT32 wmt_lib_hw_rst(void);
INT32 wmt_lib_sw_rst(int baud_rst);
INT32 wmt_lib_baud_rst(void);
INT32 wmt_lib_stp_rst(int full_set);

MTK_WCN_BOOL
wmt_lib_put_act_lxop (P_DEV_WMT pWmtDev, P_WMT_LXOP pOp, UINT32 u4WaitMs);
/* LXOP functions: */
P_WMT_LXOP wmt_lib_get_free_lxop (P_DEV_WMT pWmtDev);

#if CFG_WMT_PS_SUPPORT
extern void wmt_psm_eirq_cb(void);
extern int wmt_psm_enable(int);
extern int wmt_psm_disable(void);
extern int g_psm_idle_time_to_sleep;
extern int g_psm_enable;
#endif
/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/
static inline UINT32
lxop_get_opid(P_WMT_LXOP lxop) {
    return (lxop) ? lxop->op.opId : 0xFFFFFFFF;
}

static inline MTK_WCN_BOOL
lxop_is_wait_comp(P_WMT_LXOP lxop) {
    return (lxop && lxop->u4WaitMs) ?  MTK_WCN_BOOL_TRUE : MTK_WCN_BOOL_FALSE;
}

static inline VOID
lxop_complete(P_WMT_LXOP lxop, INT32 result) {
    if (lxop) {
        lxop->result = result;
        complete(&lxop->comp);
    }
}

#endif /* _WMT_LIB_H */

