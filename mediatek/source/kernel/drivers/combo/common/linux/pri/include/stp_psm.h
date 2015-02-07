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

/*STP Power Saving Module*/
#ifndef STP_PSM_H
#define STP_PSM_H

#include <linux/timer.h> 
#include <linux/workqueue.h> 
#include <linux/wait.h> 
#include <linux/kfifo.h>

#include <linux/init.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/sched.h>
#include <linux/wakelock.h>
#include <asm/current.h>
#include <asm/uaccess.h>


#define PSM_HANDLING 127


#define STP_PSM_WMT_PS_TASK_HANDLING_TIME  30   //20 milli-seconds
#define STP_PSM_IDLE_TIME_SLEEP           5000  
#define STP_PSM_WAIT_EVENT_TIMEOUT        6000  

#define STP_PSM_WMT_EVENT_SLEEP_EN                    1
#define STP_PSM_WMT_EVENT_WAKEUP_EN                   2
#define STP_PSM_BLOCK_DATA_EN                         4
#define STP_PSM_WMT_EVENT_DISABLE_MONITOR_INTERNAL    8 
#define STP_PSM_WMT_EVENT_DISABLE_MONITOR            16 
#define STP_PSM_WMT_EVENT_ROLL_BACK_EN              128

////////////////////////////////////////////////////////////////////////////

/* OP command ring buffer : must be power of 2 */
#define STP_OP_BUF_SIZE (16)

typedef struct _STP_OP {
    unsigned int opId; // Event ID
    unsigned int u4InfoBit; // Reserved
    unsigned int au4OpData[8]; // OP Data
} STP_OP, *P_STP_OP;

typedef struct _STP_LXOP {
    STP_OP op;
    unsigned int u4WaitMs;
    int result;
    struct completion comp;
} STP_LXOP, *P_STP_LXOP;

typedef struct _STP_LXOP_Q {
    struct mutex lock;
    unsigned int write;
    unsigned int read;
    unsigned int size;
    P_STP_LXOP queue[STP_OP_BUF_SIZE];
} STP_LXOP_Q, *P_STP_LXOP_Q;
///////////////////////////////////////////////////////////////////////////

typedef enum {
    ACT = 0,
    ACT_INACT,
    INACT,
    INACT_ACT,
    STP_PSM_MAX_STATE,
}MTKSTP_PSM_STATE_T;

typedef enum {
    MON=0,
    UNMON,
}MTKSTP_PSM_MONSTATE_T;

typedef enum {
    SLEEP = 0,
    HOST_AWAKE,
    WAKEUP,
    EIRQ,
    ROLL_BACK,
    STP_PSM_MAX_ACTION
}MTKSTP_PSM_ACTION_T;

typedef int (*wmt_notify_t)(MTKSTP_PSM_ACTION_T action);
typedef int (*stp_tx_cb_t)(unsigned  char*buffer, unsigned int length, unsigned char type);

typedef struct mtk_stp_psm{

///////////////////////////////////////////////////////////////
     /* STPd thread information */
    struct task_struct *pSTPd;   /* main thread (wmtd) handle */
    wait_queue_head_t rSTPdWq;  /*WMTd command wait queue */
    STP_LXOP_Q rFreeOpQ; /* free op queue */
    STP_LXOP_Q rActiveOpQ; /* active op queue */
    STP_LXOP arQue[STP_OP_BUF_SIZE]; /* real op instances */
    struct completion comp;
    spinlock_t    wq_spinlock;
///////////////////////////////////////////////////////////////

    MTKSTP_PSM_STATE_T  work_state; /*working state*/
    int                 flag;
    int                 idle_time_to_sleep;

    struct wake_lock    wake_lock;    
    struct timer_list   psm_timer;  /*monitor if active*/ 
    wait_queue_head_t	wait_wmt_q;    
    struct kfifo        *hold_fifo;
    unsigned char       *out_buf;
    spinlock_t          hold_fifo_spinlock;
    spinlock_t          hold_fifo_spinlock_global;
    struct semaphore    psctx_mtx;
    /*wmt callback*/
    int (*wmt_notify)(MTKSTP_PSM_ACTION_T action);
    int (*stp_tx_cb)(unsigned  char*buffer,unsigned int length, unsigned char type);
}MTKSTP_PSM_T;


/*stp-psm external function*/
int stp_psm_notify_stp(MTKSTP_PSM_T *stp_psm, const MTKSTP_PSM_ACTION_T action);
int stp_psm_notify_wmt_wakeup(MTKSTP_PSM_T *stp_psm);

int stp_psm_start_monitor(MTKSTP_PSM_T *stp_psm);
int stp_psm_get_state(MTKSTP_PSM_T *stp_psm);
int stp_psm_is_to_block_traffic(MTKSTP_PSM_T * stp_psm);
int stp_psm_is_disable(MTKSTP_PSM_T * stp_psm);
int stp_psm_has_pending_data(MTKSTP_PSM_T * stp_psm);
int stp_psm_release_data(MTKSTP_PSM_T *stp_psm);
int stp_psm_hold_data(MTKSTP_PSM_T *stp_psm, unsigned char *buffer, unsigned int len, unsigned char type);
int stp_psm_register_stp_tx_cb(MTKSTP_PSM_T *stp_psm, stp_tx_cb_t stp_tx_cb);
int stp_psm_do_wakeup(MTKSTP_PSM_T *stp_psm);

int stp_psm_register_wmt_cb(MTKSTP_PSM_T *stp_psm, wmt_notify_t wmt_cb);
int stp_psm_unregister_wmt_cb(MTKSTP_PSM_T *stp_psm);

int stp_psm_reset(MTKSTP_PSM_T *stp_psm);
int stp_psm_disable(MTKSTP_PSM_T *stp_psm);
int stp_psm_enable(MTKSTP_PSM_T *stp_psm, int idle_time_to_sleep);
struct mtk_stp_psm *stp_psm_init(void);
int stp_psm_deinit(MTKSTP_PSM_T *stp_psm);
bool mtk_wcn_stp_psm_dbg_level(unsigned int dbglevel);
#endif
