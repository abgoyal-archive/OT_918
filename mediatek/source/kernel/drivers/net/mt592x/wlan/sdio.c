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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/sdio.c#3 $
*/

/*! \file   "sdio.c"
    \brief  This file includes the operation of sdio interface

    Detail description.
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
** $Log: sdio.c $
 *
 * 07 02 2010 renbang.jiang
 * [ALPS00121201][WIFI][OPPO] The WIFI can't turn on after downlaoding a new load. 
 * .
 *
 * 06 13 2010 renbang.jiang
 * [ALPS00008206][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for fixing build warning 
 * .
 *
 * 06 13 2010 renbang.jiang
 * [ALPS00008206][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for fixing build warning 
 * .
 *
 * 06 10 2010 jim.zhang
 * [ALPS00008051]change mt592x to UNGPL version 
 * .
 *
 * 06 02 2010 george.kuo
 * [ALPS00005405][Certification][Wi-Fi] Device auto reboot while start to connect AP(qa2_wireless_test) for the first time 
 * Fix CR5405 for the kernel panic problem
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
 *
 * 05 14 2010 renbang.jiang
 * [ALPS00005812][FactoryMode] Device power off when enter WIFI 
 * .
**  \main\maintrunk.MT5921\4 2009-10-08 10:33:30 GMT mtk01090
**  Avoid accessing private data of net_device directly. Replace with netdev_priv(). Add more checking for input parameters and pointers.
**  \main\maintrunk.MT5921\3 2009-09-28 20:19:17 GMT mtk01090
**  Add private ioctl to carry OID structures. Restructure public/private ioctl interfaces to Linux kernel.
**  \main\maintrunk.MT5921\2 2009-08-18 22:57:02 GMT mtk01090
**  Add Linux SDIO (with mmc core) support.
**  Add Linux 2.6.21, 2.6.25, 2.6.26.
**  Fix compile warning in Linux.
**  \main\maintrunk.MT5921\8 2008-09-22 23:17:33 GMT mtk01461
**  Update driver for code review
**  \main\maintrunk.MT5921\7 2008-09-05 17:25:10 GMT mtk01461
**  Update Driver for Code Review
**  \main\maintrunk.MT5921\6 2008-04-22 22:57:34 GMT mtk01084
**  modify port access function prototype
**  \main\maintrunk.MT5921\5 2008-03-20 15:47:42 GMT mtk01088
**  fixed the EHPI-8 comiling error, and add function declaration
**  \main\maintrunk.MT5921\4 2008-03-14 18:03:47 GMT mtk01084
**  refine register and port access function
**  \main\maintrunk.MT5921\3 2008-01-07 15:07:35 GMT mtk01461
**  Adjust EHPI timing
** Revision 1.4  2007/07/05 07:25:33  MTK01461
** Add Linux initial code, modify doc, add 11BB, RF init code
**
** Revision 1.3  2007/06/27 02:18:51  MTK01461
** Update SCAN_FSM, Initial(Can Load Module), Proc(Can do Reg R/W), TX API
**
** Revision 1.2  2007/06/25 06:16:24  MTK01461
** Update illustrations, gl_init.c, gl_kal.c, gl_kal.h, gl_os.h and RX API
**
*/



/*******************************************************************************
*                         C O M P I L E R   F L A G S
********************************************************************************
*/

/*******************************************************************************
*                    E X T E R N A L   R E F E R E N C E S
********************************************************************************
*/

#include "gl_os.h"
#include "gl_typedef.h"
#include <linux/mmc/card.h>
#include <linux/mmc/host.h>
#include <linux/mmc/sdio.h>
//#include <linux/mmc/protocol.h>

#include <linux/mmc/sdio_func.h> /* sdio_readl(), etc */
#include <linux/mmc/sdio_ids.h> /* SDIO_CLASS_WLAN */

#include <asm/memory.h>
#include <linux/mm.h>

#include <linux/firmware.h>
#include <linux/module.h>
#include <linux/sched.h>
/*******************************************************************************
*                              C O N S T A N T S
********************************************************************************
*/
static const int MAX_IOREQ_NUM = 60;

/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/
/*******************************************************************************
*                            P U B L I C   D A T A
********************************************************************************
*/

PVOID pPreAllocedBSSCached = NULL;

static struct MT5921_ops mt5921_ops;
static struct SDIOBUS_ops sdiobus_ops;
/*******************************************************************************
*                           P R I V A T E   D A T A
********************************************************************************
*/
static UINT_32 gu4Dummy = 0;

/*******************************************************************************
*                                 M A C R O S
********************************************************************************
*/
#define PRE_ALLOC_MEM_SIZE (32*1024)
/*******************************************************************************
*                   F U N C T I O N   D E C L A R A T I O N S
********************************************************************************
*/
extern void
sdioHardStartXmit (
    struct sk_buff *prSkb,
    struct net_device *prDev
    );

extern int
hifRegisterBus (
    struct MT5921_ops * mtops,
    struct SDIOBUS_ops * busops
    );


extern VOID
hifUnregisterBus(
    remove_card pfRemove
    );


extern BOOL
hifBusInit (
    PVOID pvData
    );
    
extern VOID
hifBusRelease (
    PVOID pvData
    );
    
extern int
hifBusSetIrq (
    void * pvData,
    void * pfnIsr
    );

extern VOID
hifBusFreeIrq (
    void * pvData
    );    

#if 0
extern BOOL
hifDevRegRead (
    IN  void *          pHif,
    IN  unsigned long         u4Register,
    OUT unsigned long *       pu4Value
    );

extern BOOL
hifDevRegWrite (
    IN  void *          pHif,
    IN unsigned long        u4Register,
    IN unsigned long        u4Value
    );
    
                                
extern BOOL
hifDevPortRead (
    IN  void *          pHif,
    IN  unsigned short         u2Port,
    IN  unsigned short         u2Len,
    OUT unsigned char *        pucBuf,
    IN  unsigned short         u2ValidOutBufSize
    );

extern BOOL
hifDevPortWrite (
    IN void *         pHif,
    IN unsigned short        u2Port,
    IN unsigned short        u2Len,
    IN unsigned char *       pucBuf,
    IN unsigned short        u2ValidInBufSize
    );
#endif
    
extern void sdio_irq_func(void * pHif);

extern void hifSetInfo(void * pHif, void *prGlueInfo);
/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/
//static void mt5921_irq_func(struct sdio_func *func)
static int mt5921_irq_func(struct sdio_func *func)
{
    P_GLUE_INFO_T prGlueInfo = NULL;
    prGlueInfo = sdio_get_drvdata(func);
    ASSERT(prGlueInfo);
    ASSERT(prGlueInfo->prAdapter);
	
    //printk(KERN_INFO DRV_NAME"++ mt5921_irq_func ++ \n");
	
    GLUE_ACQUIRE_SPIN_LOCK(prGlueInfo, SPIN_LOCK_INT); // GeorgeKuo_modify:
    prGlueInfo->rHifInfo.u4ReqFlag |= REQ_FLAG_INT;
    GLUE_RELEASE_SPIN_LOCK(prGlueInfo, SPIN_LOCK_INT); // GeorgeKuo_modify:

    wake_up_interruptible(&prGlueInfo->rHifInfo.waitq);
    //printk(KERN_INFO DRV_NAME"-- mt5921_irq_func -- \n");
    return 0;
}


WLAN_STATUS
sdio_io_ctrl (IN P_GLUE_INFO_T        prGlueInfo,
    IN PFN_OID_HANDLER_FUNC pfnOidHandler,
    IN PVOID                pvInfoBuf,
    IN UINT_32              u4InfoBufLen,
    IN BOOL                 fgRead,
    IN BOOL                 fgWaitResp,
    OUT PUINT_32            pu4QryInfoLen
    )
{
    P_GL_IO_REQ_T prIoReq = NULL;
    P_GL_HIF_INFO_T prHifInfo = NULL;
    P_QUE_T prIOReqQueue = NULL;
    P_QUE_T prFreeIOReqQueue = NULL;
    WLAN_STATUS ret = WLAN_STATUS_SUCCESS;

    /* Sanity check */
    ASSERT(prGlueInfo);
    ASSERT(pfnOidHandler);
    if (!prGlueInfo || !pfnOidHandler) {
        printk(KERN_WARNING DRV_NAME"sdio_io_ctrl invalid parameters: 0x%p, 0x%p\n",
            prGlueInfo, pfnOidHandler);
        return WLAN_STATUS_INVALID_DATA;
    }

    if (FALSE != fgRead) { /* Sanity check for read */
        ASSERT(pvInfoBuf);
        ASSERT(u4InfoBufLen);
        ASSERT(pu4QryInfoLen);
        ASSERT(FALSE != fgWaitResp); /* Caller must wait for read opeartion */
        if (!pvInfoBuf || !u4InfoBufLen || (FALSE == fgWaitResp) || !pu4QryInfoLen) {
            printk(KERN_WARNING DRV_NAME"sdio_io_ctrl read with invalid parameters: 0x%p, 0x%lx, 0x%x, 0x%p\n",
                pvInfoBuf, u4InfoBufLen, fgWaitResp, pu4QryInfoLen);
            return WLAN_STATUS_INVALID_DATA;
        }
    }

    if (FALSE == fgWaitResp) { /* Sanity check for NO-wait */
        /* If Caller does NOT wait for results, input pu4QryInfoLen must be NULL
         * or it WILL cause problem when being updated by thread sdiod.
         */
        ASSERT(NULL == pu4QryInfoLen);
        if (NULL != pu4QryInfoLen) {
            printk(KERN_WARNING DRV_NAME"pu4QryInfoLen shall be NULL if fgWaitResp if FALSE \n");
            return WLAN_STATUS_INVALID_DATA;
        }
    }

    prHifInfo = &prGlueInfo->rHifInfo;
    prIOReqQueue = &prHifInfo->rIOReqQueue;
    prFreeIOReqQueue = &prHifInfo->rFreeIOReqQueue;

    GLUE_ACQUIRE_SPIN_LOCK(prGlueInfo, SPIN_LOCK_IO_REQ);
    QUEUE_REMOVE_HEAD(prFreeIOReqQueue, prIoReq, P_GL_IO_REQ_T);
    GLUE_RELEASE_SPIN_LOCK(prGlueInfo, SPIN_LOCK_IO_REQ);

    ASSERT(prIoReq);
    if (NULL == prIoReq) {
        printk(KERN_WARNING DRV_NAME"prIoReq allocate fail from rFreeIOReqQueue(%ld %p %p)\n",
            prFreeIOReqQueue->u4NumElem,
            prFreeIOReqQueue->prHead,
            prFreeIOReqQueue->prTail);
        return WLAN_STATUS_RESOURCES;
    }

    /* TODO: if fgWaitResp is false, pvInfoBuf may be invalid after this
    ** function return.
    */
    prIoReq->prAdapter = prGlueInfo->prAdapter;
    prIoReq->pfnOidHandler = pfnOidHandler;
    prIoReq->pvInfoBuf = pvInfoBuf;
    prIoReq->u4InfoBufLen = u4InfoBufLen;
    prIoReq->pu4QryInfoLen = (FALSE != fgWaitResp) ? pu4QryInfoLen : &gu4Dummy;
    prIoReq->fgRead = fgRead;
    prIoReq->fgWaitResp= fgWaitResp;
    prIoReq->u4Flag = 0;

    GLUE_ACQUIRE_SPIN_LOCK(prGlueInfo, SPIN_LOCK_IO_REQ);
    QUEUE_INSERT_TAIL(prIOReqQueue, &prIoReq->rQueEntry);
    GLUE_RELEASE_SPIN_LOCK(prGlueInfo, SPIN_LOCK_IO_REQ);

    wake_up_interruptible(&prHifInfo->waitq);

    if (fgWaitResp) {
        might_sleep();
        BUG_ON(in_interrupt()); //ASSERT(!in_interrupt());
        wait_event_interruptible(prIoReq->cmdwait_q, (prIoReq->u4Flag != 0));
        ret = prIoReq->rStatus;
        GLUE_ACQUIRE_SPIN_LOCK(prGlueInfo, SPIN_LOCK_IO_REQ);
        QUEUE_INSERT_TAIL(prFreeIOReqQueue, &prIoReq->rQueEntry);
        GLUE_RELEASE_SPIN_LOCK(prGlueInfo, SPIN_LOCK_IO_REQ);
    }

    return ret;
}


static int mtk_sdiod_thread(void *data)
{
    struct net_device *dev = data;
    P_GLUE_INFO_T prGlueInfo = (P_GLUE_INFO_T)netdev_priv(dev);
    P_GL_HIF_INFO_T prHifInfo = &prGlueInfo->rHifInfo;

    P_QUE_ENTRY_T       prQueueEntry;
    P_GL_IO_REQ_T       prIoReq;
    P_QUE_T             prSendQueue;
    P_QUE_T             prIOReqQueue;
    struct sk_buff      *prSkb;

    int ret = 0;

    /* GeorgeKuo(20090731): set to no freeze. mtk_sdiod will be stopped before
    ** entering suspend state.
    */
    current->flags |= PF_NOFREEZE;

    printk(KERN_INFO DRV_NAME"mtk_sdiod starts running... \n");

    set_user_nice(current, -10);
  	
    for (;;) {
#if 1
        ret = wait_event_interruptible(prHifInfo->waitq,
            (kthread_should_stop() ||
                QUEUE_IS_NOT_EMPTY(&prGlueInfo->rHifInfo.rIOReqQueue) ||
                QUEUE_IS_NOT_EMPTY(&prGlueInfo->rHifInfo.rSendQueue) ||
                (prGlueInfo->rHifInfo.u4ReqFlag != 0)));
#else
        add_wait_queue(&prHifInfo->waitq, &wait);
        printk("after add_wait_queue\n");
        set_current_state(TASK_INTERRUPTIBLE);
        printk("after set_current_state\n");
        schedule();
        printk("after schedule\n");
        set_current_state(TASK_RUNNING);
        printk("after set_current_state\n");
        remove_wait_queue(&prHifInfo->waitq, &wait);
        printk("after remove_wait_queue\n");
#endif

#if 0 /* GeorgeKuo(20090731): freeze here will block kthread_stop() call. */
        try_to_freeze();
#endif

        if (kthread_should_stop()) {
            printk(KERN_INFO DRV_NAME"mtk_sdiod should stop now...\n");
            prHifInfo->fgStopThread = TRUE;
        }

        /* Handle I/O Request */
        while (TRUE) {
            prIOReqQueue = &prGlueInfo->rHifInfo.rIOReqQueue;
            GLUE_ACQUIRE_SPIN_LOCK(prGlueInfo, SPIN_LOCK_IO_REQ);
            QUEUE_REMOVE_HEAD(prIOReqQueue, prIoReq, P_GL_IO_REQ_T);
            GLUE_RELEASE_SPIN_LOCK(prGlueInfo, SPIN_LOCK_IO_REQ);

            if (NULL == prIoReq) {
                //printk(KERN_INFO DRV_NAME"No IO Req\n");
                break;
            }

            if (FALSE == prHifInfo->fgStopThread) {
                if (FALSE == prIoReq->fgRead) {
                    prIoReq->rStatus = wlanSetInformation(
                        prIoReq->prAdapter,
                        prIoReq->pfnOidHandler,
                        prIoReq->pvInfoBuf,
                        prIoReq->u4InfoBufLen,
                        prIoReq->pu4QryInfoLen);
                }
                else {
                    prIoReq->rStatus = wlanQueryInformation(
                        prIoReq->prAdapter,
                        prIoReq->pfnOidHandler,
                        prIoReq->pvInfoBuf,
                        prIoReq->u4InfoBufLen,
                        prIoReq->pu4QryInfoLen);
                }
            }
            else {
                /* Should stop now... return which status? */
                prIoReq->rStatus = WLAN_STATUS_ADAPTER_NOT_READY;
                printk(KERN_INFO DRV_NAME"clean pending IO_REQ\n");
            }

            if (prIoReq->fgWaitResp) {
                prIoReq->u4Flag = 1;
                wake_up_interruptible(&prIoReq->cmdwait_q);
            }
            else {
                GLUE_ACQUIRE_SPIN_LOCK(prGlueInfo, SPIN_LOCK_IO_REQ);
                QUEUE_INSERT_TAIL(&prHifInfo->rFreeIOReqQueue, &prIoReq->rQueEntry);
                GLUE_RELEASE_SPIN_LOCK(prGlueInfo, SPIN_LOCK_IO_REQ);
            }
        }

		    //printk(KERN_INFO DRV_NAME"%ld, %d\n", prGlueInfo->rHifInfo.u4ReqFlag, prHifInfo->fgStopThread);
        /* Handle Interrupt */
        GLUE_ACQUIRE_SPIN_LOCK(prGlueInfo, SPIN_LOCK_INT);
        if (prGlueInfo->rHifInfo.u4ReqFlag & REQ_FLAG_INT) {
            prGlueInfo->rHifInfo.u4ReqFlag &= ~REQ_FLAG_INT;
            GLUE_RELEASE_SPIN_LOCK(prGlueInfo, SPIN_LOCK_INT);

            if (FALSE == prHifInfo->fgStopThread) {
                wlanISR(prGlueInfo->prAdapter, TRUE);
                wlanIST(prGlueInfo->prAdapter);
		#ifdef CFG_EINT_HANDLED_IN_WLAN
		sdiobus_ops.DevEnableEint();	
		#endif
            }
            else {
                /* Should stop now... skip pending interrupt */
                printk(KERN_INFO DRV_NAME"ignore pending interrupt\n");
            }
        }
        else {
            GLUE_RELEASE_SPIN_LOCK(prGlueInfo, SPIN_LOCK_INT);
        }

        /* Handle Packet Tx */
        while (TRUE) {
            prSendQueue = &prGlueInfo->rHifInfo.rSendQueue;
            GLUE_ACQUIRE_SPIN_LOCK(prGlueInfo, SPIN_LOCK_TX);
            QUEUE_REMOVE_HEAD(prSendQueue, prQueueEntry, P_QUE_ENTRY_T);
            GLUE_RELEASE_SPIN_LOCK(prGlueInfo, SPIN_LOCK_TX);

            if (NULL == prQueueEntry) {
                //printk(KERN_INFO DRV_NAME"No Tx Packet\n");
                break;
            }

            prSkb = (struct sk_buff *)GLUE_GET_PKT_DESCRIPTOR(prQueueEntry);
            ASSERT(prSkb);
            if (NULL == prSkb) {
                printk(KERN_WARNING DRV_NAME"prSkb == NULL in tx\n");
            }
            else {
                if (FALSE == prHifInfo->fgStopThread) {
                    //printk(KERN_INFO DRV_NAME"Process Tx\n");
                    sdioHardStartXmit(prSkb, prGlueInfo->prDevHandler);
                }
                else {
                    /* Should stop now... skip pending tx packets */
                    printk(KERN_INFO DRV_NAME"clean pending tx skb\n");
                    dev_kfree_skb(prSkb);
                }
            }
        }

        if (FALSE != prHifInfo->fgStopThread) {
            break;
        }
    }

    printk(KERN_INFO DRV_NAME"mtk_sdiod stops\n");
    return 0;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This function will register ehpi bus to the os
*
* \param[in] pfProbe    Function pointer to detect card
* \param[in] pfRemove   Function pointer to remove card
*
* \return The result of registering ehpi bus
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
glRegisterBus (
    probe_card pfProbe,
    remove_card pfRemove
    )
{
	mt5921_ops.inthandler	= mt5921_irq_func;
	mt5921_ops.probe		= pfProbe;
	mt5921_ops.remove		= pfRemove;
	  /* Renbang 20100702 allocate memory when module insert, 
    * in case of that there is no availiable 32k physical memory when initialization
    */
    pPreAllocedBSSCached = kalMemAlloc(PRE_ALLOC_MEM_SIZE);
    if (pPreAllocedBSSCached == NULL) {
        printk(KERN_NOTICE "[wifi] no memory for pPreAllocedBSSCached\n");
    }else
        printk(KERN_NOTICE "[wifi] pPreAllocedBSSCached 0x%lx, size %d\n",pPreAllocedBSSCached, PRE_ALLOC_MEM_SIZE);
    
    return hifRegisterBus(&mt5921_ops, &sdiobus_ops);
} /* end of glRegisterBus() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will unregister ehpi bus to the os
*
* \param[in] pfRemove   Function pointer to remove card
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
glUnregisterBus(
    remove_card pfRemove
    )
{
    //printk(KERN_INFO DRV_NAME"++glUnregisterBus++\n");
    ASSERT(pfRemove);
    
    if(pPreAllocedBSSCached){
        kalMemFree(pPreAllocedBSSCached, PRE_ALLOC_MEM_SIZE);
        pPreAllocedBSSCached = NULL;
    }
    hifUnregisterBus(pfRemove);

    //printk(KERN_INFO DRV_NAME"--glUnregisterBus--\n");
    return;
} /* end of glUnregisterBus() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function stores hif related info, which is initialized before.
*
* \param[in] prGlueInfo Pointer to glue info structure
* \param[in] u4Cookie   Pointer to UINT_32 memory base variable for _HIF_HPI
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
glSetHifInfo (
    P_GLUE_INFO_T prGlueInfo,
    UINT_32 u4Cookie
    )
{
    P_GL_HIF_INFO_T prHif = NULL;
    PUINT_8         pucMemHandle = NULL;
    P_GL_IO_REQ_T prIOReq = NULL;
    int i = 0;

    //printk(KERN_INFO DRV_NAME"++glSetHifInfo++\n");
    prHif = &prGlueInfo->rHifInfo;
    prHif->func = (struct sdio_func*)u4Cookie;

    init_waitqueue_head(&prHif->waitq);

    printk(KERN_INFO DRV_NAME"prHif->func->dev = 0x%p\n", &prHif->func->dev);
    printk(KERN_INFO DRV_NAME"prHif->func->vendor = 0x%04X\n", prHif->func->vendor);
    printk(KERN_INFO DRV_NAME"prHif->func->device = 0x%04X\n", prHif->func->device);

    hifSetInfo(prHif->func, prGlueInfo);
    //sdio_set_drvdata(prHif->func, prGlueInfo);

    /* GeorgeKuo: all drivers registering to a bus driver have to set this
     * linking.
     */
    SET_NETDEV_DEV(prGlueInfo->prDevHandler, &prHif->func->dev);

    QUEUE_INITIALIZE(&prHif->rSendQueue);
    QUEUE_INITIALIZE(&prHif->rIOReqQueue);
    QUEUE_INITIALIZE(&prHif->rFreeIOReqQueue);

    prHif->pucIOReqBuff = kalMemAlloc(sizeof(GL_IO_REQ_T)*MAX_IOREQ_NUM);

    pucMemHandle = prHif->pucIOReqBuff;
    for (i = 0; i < MAX_IOREQ_NUM; i++) {
        prIOReq = (P_GL_IO_REQ_T)pucMemHandle;
        init_waitqueue_head(&prIOReq->cmdwait_q);
        QUEUE_INSERT_TAIL(&prHif->rFreeIOReqQueue, &prIOReq->rQueEntry);
        pucMemHandle += ALIGN_4(sizeof(GL_IO_REQ_T));
    }

    prHif->fgStopThread = FALSE;

    /* Start mtk_sdiod thread */
    prHif->main_thread = kthread_run(mtk_sdiod_thread, prGlueInfo->prDevHandler, "mtk_sdiod");

    return;
} /* end of glSetHifInfo() */

/*----------------------------------------------------------------------------*/
/*!
* \brief This function clears hif related info.
*
* \param[in] prGlueInfo Pointer to glue info structure
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
glClearHifInfo (
    P_GLUE_INFO_T prGlueInfo
    )
{
    P_GL_HIF_INFO_T prHif = NULL;

    ASSERT(prGlueInfo);
    prHif = &prGlueInfo->rHifInfo;

    printk(KERN_INFO DRV_NAME"mtk_sdiod (0x%p, 0x%p)\n", prHif, prHif->main_thread);
    kthread_stop(prHif->main_thread);
    printk(KERN_INFO DRV_NAME"mtk_sdiod stopped\n");

    kalMemFree(prHif->pucIOReqBuff, sizeof(GL_IO_REQ_T)*MAX_IOREQ_NUM);

    return;
} /* end of glClearHifInfo() */


/*----------------------------------------------------------------------------*/
/*!
* \brief Initialize bus operation and hif related information, request resources.
*
* \param[out] pvData    A pointer to HIF-specific data type buffer.
*                       For eHPI, pvData is a pointer to UINT_32 type and stores a
*                       mapped base address.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
BOOL
glBusInit (
    PVOID pvData
    )
{
    struct sdio_func *func = NULL;

    printk(KERN_INFO DRV_NAME"++glBusInit ++ pvData = 0x%p\n", pvData);
    ASSERT(pvData);

    func = (struct sdio_func *)pvData;
    printk(KERN_INFO DRV_NAME"--glBusInit -- \n");
    return hifBusInit(func);
} /* end of glBusInit() */


/*----------------------------------------------------------------------------*/
/*!
* \brief Stop bus operation and release resources.
*
* \param[in] pvData A pointer to struct net_device.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
glBusRelease (
    PVOID pvData
    )
{

    return;
} /* end of glBusRelease() */


/*----------------------------------------------------------------------------*/
/*!
* \brief Setup bus interrupt operation and interrupt handler for os.
*
* \param[in] pvData     A pointer to struct net_device.
* \param[in] pfnIsr     A pointer to interrupt handler function.
* \param[in] pvCookie   Private data for pfnIsr function.
*
* \retval WLAN_STATUS_SUCCESS   if success
*         NEGATIVE_VALUE   if fail
*/
/*----------------------------------------------------------------------------*/
INT_32
glBusSetIrq (
    PVOID pvData,
    PVOID pfnIsr,
    PVOID pvCookie
    )
{
    struct net_device *prNetDevice = NULL;
    P_GLUE_INFO_T prGlueInfo = NULL;
    P_GL_HIF_INFO_T prHifInfo = NULL;
    int ret = 0;

    ASSERT(pvData);
    if (!pvData) {
        return -1;
    }
    prNetDevice = (struct net_device *)pvData;

    prGlueInfo = (P_GLUE_INFO_T)netdev_priv(prNetDevice);
    ASSERT(prGlueInfo);
    if (!prGlueInfo) {
        return -1;
    }

    prHifInfo = &prGlueInfo->rHifInfo;

    ret = hifBusSetIrq(prHifInfo->func, sdiobus_ops.DevIrq);
    printk(KERN_INFO DRV_NAME"%s hifBusSetIrq ret=%d \n", __FUNCTION__, ret);
    return ret;
} /* end of glBusSetIrq() */


/*----------------------------------------------------------------------------*/
/*!
* \brief Stop bus interrupt operation and disable interrupt handling for os.
*
* \param[in] pvData     A pointer to struct net_device.
* \param[in] pvCookie   Private data for pfnIsr function.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
glBusFreeIrq (
    PVOID pvData,
    PVOID pvCookie
    )
{
    struct net_device *prNetDevice = NULL;
    P_GLUE_INFO_T prGlueInfo = NULL;
    P_GL_HIF_INFO_T prHifInfo = NULL;

    ASSERT(pvData);
    if (!pvData) {
        printk(KERN_INFO DRV_NAME"%s null pvData\n", __FUNCTION__);
        return;
    }
    prNetDevice = (struct net_device *)pvData;

    prGlueInfo = (P_GLUE_INFO_T)netdev_priv(prNetDevice);
    ASSERT(prGlueInfo);
    if (!prGlueInfo) {
        printk(KERN_INFO DRV_NAME"%s no glue info\n", __FUNCTION__);
        return;
    }

    prHifInfo = &prGlueInfo->rHifInfo;

    hifBusFreeIrq(prHifInfo->func);

    return;
} /* end of glBusreeIrq() */


/*----------------------------------------------------------------------------*/
/*!
* \brief Read a 32-bit device register
*
* \param[in] prGlueInfo Pointer to the GLUE_INFO_T structure.
* \param[in] u4Register Register offset
* \param[in] pu4Value   Pointer to variable used to store read value
*
* \retval TRUE          operation success
* \retval FALSE         operation fail
*/
/*----------------------------------------------------------------------------*/
BOOL
kalDevRegRead (
    IN  P_GLUE_INFO_T   prGlueInfo,
    IN  UINT_32         u4Register,
    OUT PUINT_32        pu4Value
    )
{

    //printk(KERN_INFO DRV_NAME"++kalDevRegRead++ buf:0x%p, reg:0x%x\n", pu4Value, u4Register);
    ASSERT(prGlueInfo);
    ASSERT(pu4Value);

    //return hifDevRegRead(prGlueInfo->rHifInfo.func, u4Register, pu4Value);
    return sdiobus_ops.DevRegRead(prGlueInfo->rHifInfo.func, u4Register, pu4Value);

} /* end of kalDevRegRead() */


/*----------------------------------------------------------------------------*/
/*!
* \brief Write a 32-bit device register
*
* \param[in] prGlueInfo Pointer to the GLUE_INFO_T structure.
* \param[in] u4Register Register offset
* \param[in] u4Value    Value to be written
*
* \retval TRUE          operation success
* \retval FALSE         operation fail
*/
/*----------------------------------------------------------------------------*/
BOOL
kalDevRegWrite (
    IN P_GLUE_INFO_T  prGlueInfo,
    IN UINT_32        u4Register,
    IN UINT_32        u4Value
    )
{
    int ret = 0;

    //printk(KERN_INFO DRV_NAME"--kalDevRegWrite-- reg:0x%x, val:0x%x\n", u4Register, u4Value);
    ASSERT(prGlueInfo);

    sdiobus_ops.DevRegWrite(prGlueInfo->rHifInfo.func, u4Register, u4Value);

    //printk(KERN_INFO DRV_NAME"kalDevRegWrite MCR(%#x) = %#x, %d\n", u4Register, u4Value, ret);

    //printk(KERN_INFO DRV_NAME"--kalDevRegWrite--\n");

    return (ret) ? FALSE : TRUE;
} /* end of kalDevRegWrite() */


/*----------------------------------------------------------------------------*/
/*!
* \brief Read device I/O port
*
* \param[in] prGlueInfo         Pointer to the GLUE_INFO_T structure.
* \param[in] u2Port             I/O port offset
* \param[in] u2Len              Length to be read
* \param[out] pucBuf            Pointer to read buffer
* \param[in] u2ValidOutBufSize  Length of the buffer valid to be accessed
*
* \retval TRUE          operation success
* \retval FALSE         operation fail
*/
/*----------------------------------------------------------------------------*/
BOOL
kalDevPortRead (
    IN  P_GLUE_INFO_T   prGlueInfo,
    IN  UINT_16         u2Port,
    IN  UINT_16         u2Len,
    OUT PUINT_8         pucBuf,
    IN  UINT_16         u2ValidOutBufSize
    )
{
    P_GL_HIF_INFO_T prHifInfo = NULL;
    struct sdio_func *prSdioFunc = NULL;
    int ret = 0;

    //printk(KERN_INFO DRV_NAME"++kalDevPortRead++ buf:0x%p, port:0x%x, length:%d\n", pucBuf, u2Port, u2Len);
    ASSERT(prGlueInfo);
    prHifInfo = &prGlueInfo->rHifInfo;
    prSdioFunc = prHifInfo->func;

    ret = sdiobus_ops.DevPortRead(prSdioFunc, u2Port, u2Len, pucBuf, u2ValidOutBufSize);

    if (ret == FALSE) {
        ERRORLOG(("sdio_readsb() reports error: %x", ret));
    }

    //printk(KERN_INFO DRV_NAME"-- kalDevPortRead-- ret=%d\n", ret);
    return ret;
} /* end of kalDevPortRead() */
/*----------------------------------------------------------------------------*/
/*!
* \brief Write device I/O port
*
* \param[in] prGlueInfo         Pointer to the GLUE_INFO_T structure.
* \param[in] u2Port             I/O port offset
* \param[in] u2Len              Length to be write
* \param[in] pucBuf             Pointer to write buffer
* \param[in] u2ValidInBufSize   Length of the buffer valid to be accessed
*
* \retval TRUE          operation success
* \retval FALSE         operation fail
*/
/*----------------------------------------------------------------------------*/
BOOL
kalDevPortWrite (
    IN P_GLUE_INFO_T  prGlueInfo,
    IN UINT_16        u2Port,
    IN UINT_16        u2Len,
    IN PUINT_8        pucBuf,
    IN UINT_16        u2ValidInBufSize
    )
{
    P_GL_HIF_INFO_T prHifInfo = NULL;
    struct sdio_func *prSdioFunc = NULL;
    int ret = 0;

    //printk(KERN_INFO DRV_NAME"++kalDevPortWrite++ buf:0x%p, port:0x%x, length:%d\n", pucBuf, u2Port, u2Len);
    ASSERT(prGlueInfo);
    prHifInfo = &prGlueInfo->rHifInfo;
    prSdioFunc = prHifInfo->func;
	
	ASSERT(pucBuf);
	ASSERT(u2Len <= u2ValidInBufSize);
	ASSERT(prSdioFunc->cur_blksize > 0);

    ret = sdiobus_ops.DevPortWrite(prSdioFunc, u2Port, u2Len, pucBuf, u2ValidInBufSize);

    if (ret == FALSE) {
        ERRORLOG(("hifDevPortWrite() reports error: %x", ret));
    }

    //printk(KERN_INFO DRV_NAME"-- kalDevPortWrite-- ret=%d\n", ret);
    return ret;
} /* end of kalDevPortWrite() */


void kalDevEnableIrq()
{
	if(NULL != sdiobus_ops.DevEnableEint)
		sdiobus_ops.DevEnableEint();
	else
		ERRORLOG(("sdiobus_ops.DevEnableEint = NULL.\n"));
}

void kalDevDisableIrq()
{
	if(NULL != sdiobus_ops.DevDisableEint)
		sdiobus_ops.DevDisableEint();
	else
		ERRORLOG(("sdiobus_ops.DevDisableEint = NULL\n"));
}


VOID
glSetPowerState (
    IN P_GLUE_INFO_T  prGlueInfo,
    IN UINT_32 ePowerMode
    )
{
#if 0
    struct sdio_func *prSdioFunc = NULL;
    struct mmc_host *prMmcHost = NULL;
    struct mmc_command cmd;

    ASSERT(prGlueInfo);

    prSdioFunc = prGlueInfo->rHifInfo.func;
    ASSERT(prSdioFunc);

    prMmcHost = prSdioFunc->card->host;
    ASSERT(prMmcHost);
    if (ParamDeviceStateD0 == ePowerMode) {
        /* Test CMD5 */
        memset(&cmd, 0, sizeof(struct mmc_command));

        cmd.opcode = SD_IO_SEND_OP_COND;
        cmd.arg = 0;
        cmd.flags = MMC_RSP_SPI_R4 | MMC_RSP_R4 | MMC_CMD_BCR;

        mmc_wait_for_cmd(prMmcHost, &cmd, 3);
    }
#endif
    return;
}
