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

#ifndef _MTKSTP_H_
#define _MTKSTP_H_

#include "mtk_porting.h"

#define BT_TASK_INDX        (0)
#define FM_TASK_INDX        (1)
#define GPS_TASK_INDX       (2)
#define WIFI_TASK_INDX      (3)
#define WMT_TASK_INDX       (4)
#define STP_TASK_INDX       (5)
#define INFO_TASK_INDX      (6)
#define MTKSTP_MAX_TASK_NUM (7)

#define MTKSTP_UART_FULL_MODE 0x01
#define MTKSTP_UART_MAND_MODE 0x02
#define MTKSTP_SDIO_MODE      0x04

#define MTKSTP_BUFFER_SIZE  (16384) //(8192)

/*To check function driver's status by the the interface*/
/*Operation definition*/
#define OP_FUNCTION_ACTIVE  0

/*Driver's status*/
#define STATUS_OP_INVALID          0
#define STATUS_FUNCTION_INVALID    1

#define STATUS_FUNCTION_ACTIVE     31
#define STATUS_FUNCTION_INACTIVE   32


/* common interface */
typedef INT32 (*IF_TX)(const UINT8 *data, UINT32 size, UINT32 *written_size);
/* event/signal */
typedef INT32 (*EVENT_SET)(UINT8 function_type);
typedef INT32 (*EVENT_TX_RESUME)(UINT8 winspace);
typedef INT32 (*FUNCTION_STATUS)(UINT8 type, UINT8 op);

typedef struct
{
    /* mutex */
    MUTEX_CREATE    cb_mutex_create;
    MUTEX_DESTROY   cb_mutex_destroy;
    MUTEX_LOCK      cb_mutex_lock;
    MUTEX_UNLOCK    cb_mutex_unlock;

    /* debug */
    DBG_PRINT       cb_dbg_print;
    DBG_ASSERT      cb_dbg_assert;
    DBG_ASSERT_AEE  cb_dbg_assert_aee;
    /* timer */
    TIMER_CREATE    cb_timer_create;
    TIMER_DESTROY   cb_timer_destroy;
    TIMER_START     cb_timer_start;
    TIMER_STOP      cb_timer_stop;

    /* common interface */
    IF_TX           cb_if_tx;

    /* event/signal */
    EVENT_SET       cb_event_set;
    EVENT_TX_RESUME cb_event_tx_resume;
    FUNCTION_STATUS cb_check_funciton_status;

    /* kernel lib */
    SYS_MEMCPY      cb_memcpy;
    SYS_MEMSET      cb_memset;
    SYS_MEMCMP      cb_memcmp;
    SYS_SPRINTF     cb_sprintf;
}mtkstp_callback;

typedef int (*WMT_NOTIFY_FUNC_T)(UINT32 action);
typedef int (*BTM_NOTIFY_WMT_FUNC_T)(INT32);

/* exported functions */
/*****************************************************************************
* FUNCTION
*  mtk_wcn_stp_init
* DESCRIPTION
*  init STP kernel
* PARAMETERS
*  cb_func      [IN] function pointers of system APIs
* RETURNS
*  INT32    0 = success, others = failure
*****************************************************************************/
extern INT32 mtk_wcn_stp_init(const mtkstp_callback * const cb_func);

/*****************************************************************************
* FUNCTION
*  mtk_wcn_stp_deinit
* DESCRIPTION
*  deinit STP kernel
* PARAMETERS
*  void
* RETURNS
*  INT32    0 = success, others = failure
*****************************************************************************/
extern INT32 mtk_wcn_stp_deinit(void);

/*****************************************************************************
* FUNCTION
*  mtk_wcn_stp_parser_data
* DESCRIPTION
*  push data to serial transport protocol parser engine
* PARAMETERS
*  buffer      [IN]        data buffer
*  length      [IN]        data buffer length
* RETURNS
*  void
*****************************************************************************/
extern int mtk_wcn_stp_parser_data(UINT8 *buffer, UINT32 length);

/*****************************************************************************
* FUNCTION
*  mtk_wcn_stp_enable
* DESCRIPTION
*  enable/disable STP
* PARAMETERS
*  value        [IN]        0 = disable, others = enable
* RETURNS
*  INT32    0 = success, others = error
*****************************************************************************/
extern INT32 mtk_wcn_stp_enable(INT32 value);

/*****************************************************************************
* FUNCTION
*  mtk_wcn_stp_ready
* DESCRIPTION
*  ready/non-ready STP
* PARAMETERS
*  value        [IN]        0 = non-ready, others = ready
* RETURNS
*  INT32    0 = success, others = error
*****************************************************************************/
extern INT32 mtk_wcn_stp_ready(INT32 value);

/*****************************************************************************
* FUNCTION
*  mtk_wcn_stp_send_data
* DESCRIPTION
*  subfunction send data through STP
* PARAMETERS
*  buffer      [IN]        data buffer
*  length      [IN]        data buffer length
*  type        [IN]        subfunction type
* RETURNS
*  INT32    >= 0: length transmitted; < 0: error
*****************************************************************************/
extern INT32 mtk_wcn_stp_send_data(UINT8 *buffer, UINT32 length, UINT8 type);

/*****************************************************************************
* FUNCTION
*  mtk_wcn_stp_send_data_raw
* DESCRIPTION
*  send raw data to common interface, bypass STP
* PARAMETERS
*  buffer      [IN]        data buffer
*  length      [IN]        data buffer length
*  type        [IN]        subfunction type
* RETURNS
*  INT32    length transmitted
*****************************************************************************/
extern INT32 mtk_wcn_stp_send_data_raw(UINT8 *buffer, UINT32 length, UINT8 type);

/*****************************************************************************
* FUNCTION
*  mtk_wcn_stp_receive_data
* DESCRIPTION
*  receive data from serial protocol engine
* PARAMETERS
*  buffer      [IN]        data buffer
*  length      [IN]        data buffer length
* RETURNS
*  INT32    >= 0: size of data received; < 0: error
*****************************************************************************/
extern INT32 mtk_wcn_stp_receive_data(UINT8 *buffer, UINT32 length, UINT8 type);

/*****************************************************************************
* FUNCTION
*  mtk_wcn_stp_is_rxqueue_empty
* DESCRIPTION
*  Is certain rx queue empty?
* PARAMETERS
*  type        [IN]        subfunction type
* RETURNS
*  INT32    0: queue is NOT empyt; !0: queue is empty
*****************************************************************************/
extern MTK_WCN_BOOL mtk_wcn_stp_is_rxqueue_empty(UINT8 type);

/*****************************************************************************
* FUNCTION
*  mtk_wcn_stp_set_sdio_mode
* DESCRIPTION
*  Set stp for SDIO mode
* PARAMETERS
*  sdio_flag  [IN]        sdio mode flag (TRUE:SDIO mode, FALSE:UART mode)
* RETURNS
*  void
*****************************************************************************/
extern void mtk_wcn_stp_set_mode(UINT32 sdio_flag);

/*****************************************************************************
* FUNCTION
*  mtk_wcn_stp_is_uart_fullset_mode
* DESCRIPTION
*  Is stp use UART Fullset  mode?
* PARAMETERS
*  none.
* RETURNS
*  MTK_WCN_BOOL    TRUE:UART Fullset, FALSE:UART Fullset
*****************************************************************************/
extern MTK_WCN_BOOL mtk_wcn_stp_is_uart_fullset_mode(void);

/*****************************************************************************
* FUNCTION
*  mtk_wcn_stp_is_uart_mand_mode
* DESCRIPTION
*  Is stp use UART Mandatory  mode?
* PARAMETERS
*  none.
* RETURNS
*  MTK_WCN_BOOL    TRUE:UART Mandatory, FALSE:UART Mandatory
*****************************************************************************/
extern MTK_WCN_BOOL mtk_wcn_stp_is_uart_mand_mode(void);


/*****************************************************************************
* FUNCTION
*  mtk_wcn_stp_is_sdio_mode
* DESCRIPTION
*  Is stp use SDIO mode?
* PARAMETERS
*  none.
* RETURNS
*  MTK_WCN_BOOL    TRUE:SDIO mode, FALSE:UART mode
*****************************************************************************/
extern MTK_WCN_BOOL mtk_wcn_stp_is_sdio_mode(void);


/*****************************************************************************
* FUNCTION
*  stp_send_inband_reset
* DESCRIPTION
*  To sync to oringnal stp state with f/w stp
* PARAMETERS
*  none.
* RETURNS
*  none
*****************************************************************************/
extern void mtk_wcn_stp_inband_reset(void);

/*****************************************************************************
* FUNCTION
*  stp_send_inband_reset
* DESCRIPTION
*  To send testing command to chip
* PARAMETERS
*  none.
* RETURNS
*  none
*****************************************************************************/
extern void mtk_wcn_stp_test_cmd(INT32 no);

/*****************************************************************************
* FUNCTION
*  stp_send_inband_reset
* DESCRIPTION
* To control STP debugging mechanism
* PARAMETERS
*  func_no: function control, func_op: dumpping filer, func_param: dumpping parameter
* RETURNS
*  none
*****************************************************************************/
extern void mtk_wcn_stp_debug_ctrl(INT32 func_no, INT32 func_op, INT32 func_param);
/*****************************************************************************
* FUNCTION
*  mtk_wcn_stp_flush
* DESCRIPTION
*  flush all stp context
* PARAMETERS
*  none.
* RETURNS
*  none
*****************************************************************************/
extern void mtk_wcn_stp_flush_context(void);

/*****************************************************************************
* FUNCTION
*  mtk_wcn_stp_rx_queue
* DESCRIPTION
*  flush all stp rx queue
* PARAMETERS
*  none.
* RETURNS
*  none
*****************************************************************************/
extern void mtk_wcn_stp_flush_rx_queue(UINT32 type);

/*****************************************************************************
* FUNCTION
*  mtk_wcn_stp_is_enable
* DESCRIPTION
*  Is STP ready?
* PARAMETERS
*  none.
* RETURNS
*  MTK_WCN_BOOL    TRUE:ready, FALSE:not ready
*****************************************************************************/
extern MTK_WCN_BOOL mtk_wcn_stp_is_ready(void);

/*****************************************************************************
* FUNCTION
*  set_bluetooth_rx_interface
* DESCRIPTION
*  Set bluetooth rx interface
* PARAMETERS
*  rx interface type
* RETURNS
*  void
*****************************************************************************/
extern void mtk_wcn_stp_set_bluez(MTK_WCN_BOOL sdio_flag);


/*****************************************************************************
* FUNCTION
*  set stp debugging mdoe
* DESCRIPTION
*  set stp debugging mdoe
* PARAMETERS
* dbg_mode: switch to dbg mode ?
* RETURNS
*  void
*****************************************************************************/
extern void mtk_wcn_stp_set_dbg_mode(MTK_WCN_BOOL dbg_mode);

/*****************************************************************************
* FUNCTION
*  set stp auto reset mdoe
* DESCRIPTION
*  set stp auto reset mdoe
* PARAMETERS
* auto_rst: switch to auto reset mode ?
* RETURNS
*  void
*****************************************************************************/
extern void mtk_wcn_stp_set_auto_rst(MTK_WCN_BOOL auto_rst);

/*stp_psm support*/

/*****************************************************************************
* FUNCTION
*  mtk_wcn_stp_psm_do_wakeup
* DESCRIPTION
*  Force to wake up STP
* PARAMETERS
*
* RETURNS
*  0: Success , negative value: Fail
*****************************************************************************/
extern int mtk_wcn_stp_psm_do_wakeup(void);

/*****************************************************************************
* FUNCTION
*  mtk_wcn_stp_psm_get_state
* DESCRIPTION
*  Get the state of power saving handling
* PARAMETERS
*
* RETURNS
*  INACT/ACT/ACT_INACT/INACT_ACT
*****************************************************************************/
extern int mtk_wcn_stp_psm_get_state(void);


/*****************************************************************************
* FUNCTION
*  mtk_stp_psm_register_wmt_cb
* DESCRIPTION
*  register WMT stp_psm callback
* PARAMETERS
*  WMT power saving handler callback
* RETURNS
*  0: Sccuess  Negative value: Fail
*****************************************************************************/
extern int mtk_wcn_stp_psm_register_wmt_cb(WMT_NOTIFY_FUNC_T wmt_cb);

/*****************************************************************************
* FUNCTION
*  mtk_stp_psm_register_wmt_cb
* DESCRIPTION
*  unregister WMT stp_psm callback
* PARAMETERS
*  WMT power saving handler callback
* RETURNS
*  0: Sccuess  Negative value: Fail
*****************************************************************************/
extern int mtk_wcn_stp_psm_unregister_wmt_cb(void);

/*****************************************************************************
* FUNCTION
*  mtk_wcn_stp_psm_notify_stp
* DESCRIPTION
*  WMT notification to STP that power saving job is done or not
* PARAMETERS
*
* RETURNS
*  0: Sccuess  Negative value: Fail
*****************************************************************************/
extern int mtk_wcn_stp_psm_notify_stp(const UINT32 action);


/*****************************************************************************
* FUNCTION
*  mtk_wcn_stp_psm_enabla
* DESCRIPTION
*  enable STP PSM
* PARAMETERS
*  int idle_time_to_sleep: IDLE time to sleep
* RETURNS
*  0: Sccuess  Negative value: Fail
*****************************************************************************/
extern int mtk_wcn_stp_psm_enable(int idle_time_to_sleep);

/*****************************************************************************
* FUNCTION
*  mtk_wcn_stp_psm_disable
* DESCRIPTION
*  disable STP PSM
* PARAMETERS
*  void
* RETURNS
*  0: Sccuess  Negative value: Fail
*****************************************************************************/
extern int mtk_wcn_stp_psm_disable(void);

/*****************************************************************************
* FUNCTION
*  mtk_wcn_stp_psm_reset
* DESCRIPTION
*  reset STP PSM (used on whole chip reset)
* PARAMETERS
*  void
* RETURNS
*  0: Sccuess  Negative value: Fail
*****************************************************************************/
extern int mtk_wcn_stp_psm_reset(void);
extern void stp_do_tx_timeout(void);

/*****************************************************************************
* FUNCTION
*  mtk_wcn_stp_btm_register_wmt_cb
* DESCRIPTION
*  Register stp_btm WMT Callback Function
* PARAMETERS
*  wmt_cb
* RETURNS
*   0: Success Negative Value: Fail
*****************************************************************************/
extern int mtk_wcn_stp_btm_register_wmt_cb(BTM_NOTIFY_WMT_FUNC_T wmt_cb);

/*****************************************************************************
* FUNCTION
*  mtk_wcn_stp_btm_unregister_wmt_cb
* DESCRIPTION
*  Unregister stp_btm WMT Callback Function
* PARAMETERS
*  void
* RETURNS
*   0: Success Negative Value: Fail
*****************************************************************************/
extern int mtk_wcn_stp_btm_unregister_wmt_cb(void);

/*****************************************************************************
* FUNCTION
*  mtk_wcn_stp_btm_get_dmp
* DESCRIPTION
*  get stp dump related information
* PARAMETERS
*  buffer: dump placement, len: dump size
* RETURNS
*   0: Success Negative Value: Fail
*****************************************************************************/
extern int mtk_wcn_stp_btm_get_dmp(char *buf, int *len);

extern int mtk_wcn_stp_dbg_enable(void);
extern int mtk_wcn_stp_dbg_disable(void);
#endif

