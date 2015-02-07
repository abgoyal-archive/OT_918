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
#ifndef STP_BTM_H
#define STP_BTM_H

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

/* OP command ring buffer : must be power of 2 */
#define STP_BTM_OP_BUF_SIZE (64)

typedef enum {
    BTM_RST_OP = 0,
    BTM_DMP_OP = 1,
    BTM_MAX_OP,
}MTKSTP_BTM_WMT_OP_T;

typedef struct _STP_BTM_OP {
    unsigned int opId; // Event ID
    unsigned int u4InfoBit; // Reserved
    unsigned int au4OpData[8]; // OP Data
} STP_BTM_OP, *P_STP_BTM_OP;

typedef struct _STP_BTM_LXOP {
    STP_BTM_OP op;
    unsigned int u4WaitMs;
    int result;
    struct completion comp;
} STP_BTM_LXOP, *P_STP_BTM_LXOP;

typedef struct _STP_BTM_LXOP_Q {
    struct mutex lock;
    unsigned int write;
    unsigned int read;
    unsigned int size;
    P_STP_BTM_LXOP queue[STP_BTM_OP_BUF_SIZE];
} STP_BTM_LXOP_Q, *P_STP_BTM_LXOP_Q;


typedef struct mtk_stp_btm{
    struct task_struct *pSTPd;   /* main thread (wmtd) handle */
    wait_queue_head_t rSTPdWq;  /*WMTd command wait queue */
    STP_BTM_LXOP_Q rFreeOpQ; /* free op queue */
    STP_BTM_LXOP_Q rActiveOpQ; /* active op queue */
    STP_BTM_LXOP arQue[STP_BTM_OP_BUF_SIZE]; /* real op instances */
    struct completion comp;
    spinlock_t        wq_spinlock;

    /*wmt_notify*/
    int (*wmt_notify)(int);
}MTKSTP_BTM_T;

typedef int (*btm_notify_wmt_t)(int);
int stp_btm_unregister_wmt_cb(MTKSTP_BTM_T *stp_btm);
int stp_btm_register_wmt_cb(MTKSTP_BTM_T *stp_btm, btm_notify_wmt_t wmt_cb);
int stp_btm_notify_wmt_rst_wq(MTKSTP_BTM_T *stp_btm);
int stp_btm_notify_stp_retry_wq(MTKSTP_BTM_T *stp_btm);
int stp_btm_notify_wmt_dmp_wq(MTKSTP_BTM_T *stp_btm);

MTKSTP_BTM_T *stp_btm_init(void);
int stp_btm_deinit(MTKSTP_BTM_T *stp_btm);


#endif

