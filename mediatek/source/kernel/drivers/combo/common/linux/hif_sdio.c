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
** $Id: $
*/

/*! \file   "hif_sdio.c"
 * \brief
 *
 * detailed description
*/

/*
** $Log: $
 *
 * 07 25 2010 george.kuo
 *
 * Move hif_sdio driver to linux directory.
 *
 * 07 23 2010 george.kuo
 *
 * Add MT6620 driver source tree
 * , including char device driver (wmt, bt, gps), stp driver, interface driver (tty ldisc and hif_sdio), and bt hci driver.
**
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

#include <linux/mmc/card.h>
#include <linux/mmc/host.h>
#include <linux/mmc/sdio_func.h>
#include <linux/mmc/sdio_ids.h>

#include <linux/mm.h>
#include <linux/firmware.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/vmalloc.h>

#include "hif_sdio.h"

extern void mmc_power_up_ext(struct mmc_host *host);
extern void mmc_power_off_ext(struct mmc_host *host);

/*******************************************************************************
*                              C O N S T A N T S
********************************************************************************
*/
#define DRV_NAME "[SDIO Client]"

/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/

/*******************************************************************************
*                                 M A C R O S
********************************************************************************
*/
/*!
 * \brief A macro used to generate hif_sdio client's context
 *
 * Generate a context for hif_sdio client based on the following input parameters
 * |<-card id (16bits)->|<-block size in unit of 256 bytes(8 bits)->|<-function number(4bits)->|<-index(4bits)->|
 *
 * \param manf      the 16 bit manufacturer id
 * \param card      the 16 bit card id
 * \param func      the 16 bit function number
 * \param b_sz    the 16 bit function block size
 */
#define CLTCTX(cid, func, blk_sz, idx) \
    (MTK_WCN_HIF_SDIO_CLTCTX)( (((UINT32)(cid) & 0xFFFFUL) << 16) | \
        (((UINT32)(func) & 0xFUL) << 4) | \
        (((UINT32)(blk_sz) & 0xFF00UL) << 0) | \
        (((UINT32)idx & 0xFUL) << 0) )

/*!
 * \brief A set of macros used to get information out of an hif_sdio client context
 *
 * Generate a context for hif_sdio client based on the following input parameters
 */
#define CLTCTX_CID(ctx) (((ctx) >> 16) & 0xFFFF)
#define CLTCTX_FUNC(ctx) (((ctx) >> 4) & 0xF)
#define CLTCTX_BLK_SZ(ctx) (((ctx) >> 0) & 0xFF00)
#define CLTCTX_IDX(ctx) ((ctx) & 0xF)

/*******************************************************************************
*                   F U N C T I O N   D E C L A R A T I O N S
********************************************************************************
*/
static int hif_sdio_probe (
    struct sdio_func *func,
    const struct sdio_device_id *id
    );

static void hif_sdio_remove (
    struct sdio_func *func
    );

static void hif_sdio_irq (
    struct sdio_func *func
    );

static void hif_sdio_clt_probe_func (
    MTK_WCN_HIF_SDIO_REGISTINFO *registinfo_p,
    INT8 probe_idx
    );

static void hif_sdio_clt_probe_worker(
    struct work_struct *work
    );

static int hif_sdio_find_probed_list_index_by_func(
    struct sdio_func *func
    );

static int hif_sdio_find_probed_list_index_by_clt_index(
    INT32 clt_index
    );

static int hif_sdio_find_probed_list_index_by_id_func(
    UINT16 vendor,
    UINT16 device,
    UINT16 func_num
    );

static void hif_sdio_init_clt_list(
    INT32 index
    );

static int hif_sdio_find_clt_list_index (
    UINT16 vendor,
    UINT16 device,
    UINT16 func_num
    );

static int hif_sdio_check_supported_sdio_id(
    UINT16 vendor,
    UINT16 device
    );

static int hif_sdio_check_duplicate_sdio_id(
    UINT16 vendor,
    UINT16 device,
    UINT16 func_num
    );

static int hif_sdio_add_clt_list(
    INT32*  clt_index_p,
    const MTK_WCN_HIF_SDIO_CLTINFO *pinfo,
    UINT32 tbl_index
    );

static INT32 hif_sdio_stp_on(
    void
    );

static INT32 hif_sdio_stp_off(
    void
    );

static INT32 hif_sdio_wifi_on(
    void
    );

static INT32 hif_sdio_wifi_off(
    void
    );

/*******************************************************************************
*                           P R I V A T E   D A T A
********************************************************************************
*/

/* Supported SDIO device table */
static const struct sdio_device_id mtk_sdio_id_tbl[] = {
    /* MT6618 */ /* Not an SDIO standard class device */
    { SDIO_DEVICE(0x037A, 0x018A) }, /* SDIO1:WIFI */
    { SDIO_DEVICE(0x037A, 0x018B) }, /* SDIO2:FUNC1:BT+FM */
    { SDIO_DEVICE(0x037A, 0x018C) }, /* 2-function (SDIO2:FUNC1:BT+FM, FUNC2:WIFI) */

    /* MT6619 */ /* Not an SDIO standard class device */
    { SDIO_DEVICE(0x037A, 0x6619) }, /* SDIO2:FUNC1:BT+FM+GPS */

    /* MT6620 */ /* Not an SDIO standard class device */
    { SDIO_DEVICE(0x037A, 0x020A) }, /* SDIO1:FUNC1:WIFI */
    { SDIO_DEVICE(0x037A, 0x020B) }, /* SDIO2:FUNC1:BT+FM+GPS */
    { SDIO_DEVICE(0x037A, 0x020C) }, /* 2-function (SDIO2:FUNC1:BT+FM+GPS, FUNC2:WIFI) */

    /* MT5921 */ /* Not an SDIO standard class device */
    { SDIO_DEVICE(0x037A, 0x5921) },
    { /* end: all zeroes */ },
};

static struct sdio_driver mtk_sdio_client_drv = {
    .name = "mtk_sdio_client", /* MTK SDIO Client Driver */
    .id_table = mtk_sdio_id_tbl, /* all supported struct sdio_device_id table */
    .probe = hif_sdio_probe,
    .remove = hif_sdio_remove,
};

/* Registered client driver list */
/* static list g_hif_sdio_clt_drv_list */
static MTK_WCN_HIF_SDIO_REGISTINFO g_hif_sdio_clt_drv_list[CFG_CLIENT_COUNT];

/* MMC probed function list */
/* static list g_hif_sdio_probed_func_list */
static MTK_WCN_HIF_SDIO_PROBEINFO g_hif_sdio_probed_func_list[CFG_CLIENT_COUNT];

/* spin lock info for g_hif_sdio_clt_drv_list and g_hif_sdio_probed_func_list */
static MTK_WCN_HIF_SDIO_LOCKINFO g_hif_sdio_lock_info;

/* reference count, debug information? */
static int gRefCount;

/*******************************************************************************
*                            P U B L I C   D A T A
********************************************************************************
*/
MODULE_LICENSE("GPL");
MODULE_AUTHOR("MediaTek Inc WCN_SE_CS3");
MODULE_DESCRIPTION("MediaTek MT6620 HIF SDIO Driver");

MODULE_DEVICE_TABLE(sdio, mtk_sdio_id_tbl);

/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/

/*!
 * \brief MTK hif sdio client registration function
 *
 * Client uses this function to register itself to hif_sdio driver
 *
 * \param pinfo a pointer of client's information
 *
 * \retval 0 register successfully
 * \retval < 0 list error code here
 */
INT32 mtk_wcn_hif_sdio_client_reg (
    const MTK_WCN_HIF_SDIO_CLTINFO *pinfo
    )
{
    INT32   ret = -HIF_SDIO_ERR_FAIL;
    INT32   clt_index = -1;
    UINT32  i   = 0;
    UINT32  j   = 0;
    MTK_WCN_HIF_SDIO_CLT_PROBE_WORKERINFO *clt_probe_worker_info = 0;

    printk(KERN_INFO DRV_NAME"%s start!\n", __FUNCTION__);

    //4 <1> check input pointer is valid
    HIF_SDIO_ASSERT( pinfo );

    //4 <2> check if input parameters are all supported and valid
    for ( i=0; i<pinfo->func_tbl_size; i++ )
    {
        ret = hif_sdio_check_supported_sdio_id( pinfo->func_tbl[i].manf_id, pinfo->func_tbl[i].card_id );
        if(ret)
        {
            printk(KERN_INFO DRV_NAME"%s:vendor id and device id of sdio_func are not supported in mtk_sdio_id_tbl!\n", __FUNCTION__);
            goto out;
        }
    }
    DPRINTK(KERN_INFO DRV_NAME"hif_sdio_check_supported_sdio_id() done!\n");

    //4 <3> check if the specific {manf id, card id, function number} tuple is
    //4 already resigstered
    for ( i=0; i<pinfo->func_tbl_size; i++ )
    {
        ret = hif_sdio_check_duplicate_sdio_id( pinfo->func_tbl[i].manf_id, pinfo->func_tbl[i].card_id, pinfo->func_tbl[i].func_num );
        if(ret)
        {
            printk(KERN_INFO DRV_NAME"%s:vendor id, device id, and fun_num of sdio_func are duplicated in g_hif_sdio_clt_drv_list!\n", __FUNCTION__);
            goto out;
        }
    }
    DPRINTK(KERN_INFO DRV_NAME"hif_sdio_check_duplicate_sdio_id() done!\n");

    //4 <4> add the specified {manf id, card id, function number} tuple to registered client list
    DPRINTK(KERN_INFO DRV_NAME"pinfo->func_tbl_size:%d\n", pinfo->func_tbl_size);
    for ( i=0; i<pinfo->func_tbl_size; i++ )
    {
        ret = hif_sdio_add_clt_list( &clt_index, pinfo, i );
        if(ret)
        {
            printk(KERN_INFO DRV_NAME"%s:client's info are added in registed client list failed (buffer is full)!\n", __FUNCTION__);
            goto out;
        }
        DPRINTK(KERN_INFO DRV_NAME"hif_sdio_add_clt_list() done (gRefCount=%d)!\n", gRefCount);

    //4 <5> if the specific {manf id, card id, function number} tuple has already
    //4 been probed by mmc, schedule another task to call client's .hif_clt_probe()
        for ( j=0; j<CFG_CLIENT_COUNT; j++ )
        {
            // probed spin lock
            spin_lock_bh( &g_hif_sdio_lock_info.probed_list_lock );
            if ( g_hif_sdio_probed_func_list[j].func == 0 )
            {
                // probed spin unlock
                spin_unlock_bh( &g_hif_sdio_lock_info.probed_list_lock );
                continue;
            }
            /* the function has been probed */
            if ( (g_hif_sdio_clt_drv_list[clt_index].func_info->manf_id == g_hif_sdio_probed_func_list[j].func->vendor) &&\
                 (g_hif_sdio_clt_drv_list[clt_index].func_info->card_id == g_hif_sdio_probed_func_list[j].func->device) &&\
                 (g_hif_sdio_clt_drv_list[clt_index].func_info->func_num == g_hif_sdio_probed_func_list[j].func->num) )
            {
                g_hif_sdio_probed_func_list[j].clt_idx = clt_index;
                // probed spin unlock
                spin_unlock_bh( &g_hif_sdio_lock_info.probed_list_lock );

                /* use worker thread to perform the client's .hif_clt_probe() */
                clt_probe_worker_info = vmalloc( sizeof(MTK_WCN_HIF_SDIO_CLT_PROBE_WORKERINFO) );
                INIT_WORK( &clt_probe_worker_info->probe_work, hif_sdio_clt_probe_worker );
                clt_probe_worker_info->registinfo_p = &g_hif_sdio_clt_drv_list[clt_index];
                clt_probe_worker_info->probe_idx = j;
                schedule_work( &clt_probe_worker_info->probe_work );

        //4 <5.1> remember to do claim_irq for the func if it's irq had been released.
                if ( !(g_hif_sdio_probed_func_list[j].func->irq_handler) )
                {
                    sdio_claim_host(g_hif_sdio_probed_func_list[j].func);
                    ret = sdio_claim_irq(g_hif_sdio_probed_func_list[j].func, hif_sdio_irq);
                    sdio_release_host(g_hif_sdio_probed_func_list[j].func);
                }
        //4 <5.2> Reset the block size of the function provided by client
                DPRINTK(KERN_INFO DRV_NAME"%s:Reset sdio block size: %d!\n", __FUNCTION__, g_hif_sdio_clt_drv_list[clt_index].func_info->blk_sz);
                sdio_claim_host(g_hif_sdio_probed_func_list[j].func);
                ret = sdio_set_block_size(g_hif_sdio_probed_func_list[j].func,\
                                        g_hif_sdio_clt_drv_list[clt_index].func_info->blk_sz);
                sdio_release_host(g_hif_sdio_probed_func_list[j].func);
            }
            else
            {
                // probed spin unlock
                spin_unlock_bh( &g_hif_sdio_lock_info.probed_list_lock );
            }
        }
        DPRINTK(KERN_INFO DRV_NAME"map g_hif_sdio_clt_drv_list to g_hif_sdio_probed_func_list done!\n");
    }
    ret = HIF_SDIO_ERR_SUCCESS;
    gRefCount++;

out:
    //4 <last> error handling

    printk(KERN_INFO DRV_NAME"%s end!\n", __FUNCTION__);
    return ret;
} /* end of mtk_wcn_hif_sdio_client_reg() */

/*!
 * \brief MTK hif sdio client un-registration function
 *
 * Client uses this function to un-register itself
 *
 * \param pinfo a pointer of client's information
 *
 * \retval 0    register successfully
 * \retval < 0  list error code here
 */
INT32 mtk_wcn_hif_sdio_client_unreg (
    const MTK_WCN_HIF_SDIO_CLTINFO *pinfo
    )
{
    INT32  ret = -HIF_SDIO_ERR_FAIL;
    INT32  clt_list_index = 0;
    UINT32 i = 0;
    UINT32 j = 0;

    printk(KERN_INFO DRV_NAME"%s start!\n", __FUNCTION__);

    //4 <1> check if input pointer is valid
    HIF_SDIO_ASSERT( pinfo );

    //4 <2> check if input parameters are all supported and valid
    for ( i=0; i<pinfo->func_tbl_size; i++ )
    {
        ret = hif_sdio_check_supported_sdio_id( pinfo->func_tbl[i].manf_id, pinfo->func_tbl[i].card_id );
        if(ret)
        {
            printk(KERN_INFO DRV_NAME"%s:vendor id and device id of sdio_func are not supported in mtk_sdio_id_tbl!\n", __FUNCTION__);
            goto out;
        }
    }

    //4 <3> check if the specific {manf id, card id, function number} tuple is already resigstered
    //4 and find the corresponding client ctx and call client's .hif_clt_remove() in THIS context
    for ( i=0; i<pinfo->func_tbl_size; i++ )
    {
        clt_list_index = hif_sdio_find_clt_list_index(pinfo->func_tbl[i].manf_id, pinfo->func_tbl[i].card_id, pinfo->func_tbl[i].func_num);
        if ( clt_list_index < 0 )
        {
            printk(KERN_INFO DRV_NAME"%s:client info is not in the client's registed list!\n", __FUNCTION__);
            ret = -HIF_SDIO_ERR_FAIL;
            goto out;
        }

    //4 <4> mark the specified {manf id, card id, function number} tuple as
    //4 un-registered and invalidate client's context
        hif_sdio_init_clt_list( clt_list_index );

        /* un-map g_hif_sdio_clt_drv_list index in g_hif_sdio_probed_func_list */
        for ( j=0; j<CFG_CLIENT_COUNT; j++ )
        {
            if ( g_hif_sdio_probed_func_list[j].clt_idx == clt_list_index )
            {
                g_hif_sdio_probed_func_list[j].clt_idx = -1;
            }
        }
    }
    gRefCount--;

    ret = HIF_SDIO_ERR_SUCCESS;
out:
    printk(KERN_INFO DRV_NAME"%s end (gRefCount=%d) !\n", __FUNCTION__, gRefCount);
    return ret;
}/* end of mtk_wcn_hif_sdio_client_unreg() */

/*!
 * \brief
 *
 * detailed descriptions
 *
 * \param ctx client's context variable
 *
 * \retval 0    register successfully
 * \retval < 0  list error code here
 */
INT32 mtk_wcn_hif_sdio_readb (
    MTK_WCN_HIF_SDIO_CLTCTX ctx,
    UINT32 offset,
    PUINT8 pvb
    )
{
    INT32 ret = -HIF_SDIO_ERR_FAIL;
    int probe_index = -1;
    struct sdio_func* func = 0;

    DPRINTK(KERN_INFO DRV_NAME"%s start!\n", __FUNCTION__);
    HIF_SDIO_ASSERT( pvb );

    //4 <1> check if ctx is valid, registered, and probed
    probe_index = CLTCTX_IDX(ctx);
    if( probe_index < 0 )   /* the function has not been probed */
    {
        printk(KERN_INFO DRV_NAME"%s: can't find client in probed list!\n", __FUNCTION__);
        ret = -HIF_SDIO_ERR_FAIL;
        goto out;
    }
    else
    {
        if ( g_hif_sdio_probed_func_list[probe_index].clt_idx < 0 )   /* the client has not been registered */
        {
            printk(KERN_INFO DRV_NAME"%s: can't find client in registered list!\n", __FUNCTION__);
            ret = -HIF_SDIO_ERR_FAIL;
            goto out;
        }
    }
    func = g_hif_sdio_probed_func_list[probe_index].func;

    //4 <2> 
    sdio_claim_host(func);
    *pvb = sdio_readb(func, offset, &ret);
    sdio_release_host(func);     

    //4 <3> check result code and return proper error code

out:
    DPRINTK(KERN_INFO DRV_NAME"%s end!\n", __FUNCTION__);
    return ret;
} /* end of mtk_wcn_hif_sdio_client_unreg() */

/*!
 * \brief
 *
 * detailed descriptions
 *
 * \param ctx client's context variable
 *
 * \retval 0    register successfully
 * \retval < 0  list error code here
 */
INT32 mtk_wcn_hif_sdio_writeb (
    MTK_WCN_HIF_SDIO_CLTCTX ctx,
    UINT32 offset,
    UINT8 vb
    )
{
    INT32 ret = -HIF_SDIO_ERR_FAIL;
    int probe_index = -1;
    struct sdio_func* func = 0;

    DPRINTK(KERN_INFO DRV_NAME"%s start!\n", __FUNCTION__);

    //4 <1> check if ctx is valid, registered, and probed
    probe_index = CLTCTX_IDX(ctx);
    if( probe_index < 0 )   /* the function has not been probed */
    {
        printk(KERN_INFO DRV_NAME"%s: can't find client in probed list!\n", __FUNCTION__);
        ret = -HIF_SDIO_ERR_FAIL;
        goto out;
    }
    else
    {
        if ( g_hif_sdio_probed_func_list[probe_index].clt_idx < 0 )   /* the client has not been registered */
        {
            printk(KERN_INFO DRV_NAME"%s: can't find client in probed list!\n", __FUNCTION__);
            ret = -HIF_SDIO_ERR_FAIL;
            goto out;
        }
    }
    func = g_hif_sdio_probed_func_list[probe_index].func;

    //4 <1.1> check if input parameters are valid

    //4 <2> 
    sdio_claim_host(func);
    sdio_writeb(func, vb, offset, &ret);
    sdio_release_host(func);

    //4 <3> check result code and return proper error code

out:
    DPRINTK(KERN_INFO DRV_NAME"%s end!\n", __FUNCTION__);
    return ret;
} /* end of mtk_wcn_hif_sdio_client_unreg() */

/*!
 * \brief
 *
 * detailed descriptions
 *
 * \param ctx client's context variable
 *
 * \retval 0    register successfully
 * \retval < 0  list error code here
 */
INT32 mtk_wcn_hif_sdio_readl (
    MTK_WCN_HIF_SDIO_CLTCTX ctx,
    UINT32 offset,
    PUINT32 pvl
    )
{
    INT32 ret = -HIF_SDIO_ERR_FAIL;
    int probe_index = -1;
    struct sdio_func* func = 0;

    DPRINTK(KERN_INFO DRV_NAME"%s start!\n", __FUNCTION__);
    HIF_SDIO_ASSERT( pvl );

    //4 <1> check if ctx is valid, registered, and probed
    probe_index = CLTCTX_IDX(ctx);
    if( probe_index < 0 )   /* the function has not been probed */
    {
        printk(KERN_INFO DRV_NAME"%s: can't find client in probed list!\n", __FUNCTION__);
        ret = -HIF_SDIO_ERR_FAIL;
        goto out;
    }
    else
    {
        if ( g_hif_sdio_probed_func_list[probe_index].clt_idx < 0 )   /* the client has not been registered */
        {
            printk(KERN_INFO DRV_NAME"%s: can't find client in registered list!\n", __FUNCTION__);
            ret = -HIF_SDIO_ERR_FAIL;
            goto out;
        }
    }
    func = g_hif_sdio_probed_func_list[probe_index].func;

    //4 <1.1> check if input parameters are valid

    //4 <2> 
    sdio_claim_host(func);
    *pvl = sdio_readl(func, offset, &ret);
    sdio_release_host(func);

    //4 <3> check result code and return proper error code

out:
    DPRINTK(KERN_INFO DRV_NAME"%s end!\n", __FUNCTION__);
    return ret;
} /* end of mtk_wcn_hif_sdio_client_unreg() */

/*!
 * \brief
 *
 * detailed descriptions
 *
 * \param ctx client's context variable
 *
 * \retval 0    register successfully
 * \retval < 0  list error code here
 */
INT32 mtk_wcn_hif_sdio_writel (
    MTK_WCN_HIF_SDIO_CLTCTX ctx,
    UINT32 offset,
    UINT32 vl
    )
{
    INT32 ret = -HIF_SDIO_ERR_FAIL;
    int probe_index = -1;
    struct sdio_func* func = 0;

    DPRINTK(KERN_INFO DRV_NAME"%s start!\n", __FUNCTION__);

    //4 <1> check if ctx is valid, registered, and probed
    probe_index = CLTCTX_IDX(ctx);
    if( probe_index < 0 )   /* the function has not been probed */
    {
        printk(KERN_INFO DRV_NAME"%s: can't find client in probed list!\n", __FUNCTION__);
        ret = -HIF_SDIO_ERR_FAIL;
        goto out;
    }
    else
    {
        if ( g_hif_sdio_probed_func_list[probe_index].clt_idx < 0 )   /* the client has not been registered */
        {
            printk(KERN_INFO DRV_NAME"%s: can't find client in probed list!\n", __FUNCTION__);
            ret = -HIF_SDIO_ERR_FAIL;
            goto out;
        }
    }
    func = g_hif_sdio_probed_func_list[probe_index].func;

    //4 <1.1> check if input parameters are valid

    //4 <2> 
    sdio_claim_host(func);
    sdio_writel(func, vl, offset, &ret);
    sdio_release_host(func);

    //4 <3> check result code and return proper error code

out:
    DPRINTK(KERN_INFO DRV_NAME"%s end!\n", __FUNCTION__);
    return ret;
} /* end of mtk_wcn_hif_sdio_client_unreg() */

/*!
 * \brief
 *
 * detailed descriptions
 *
 * \param ctx client's context variable
 *
 * \retval 0    register successfully
 * \retval < 0  list error code here
 */
INT32 mtk_wcn_hif_sdio_read_buf (
    MTK_WCN_HIF_SDIO_CLTCTX ctx,
    UINT32 offset,
    PUINT32 pbuf,
    UINT32 len
    )
{
    INT32 ret = -HIF_SDIO_ERR_FAIL;
    int probe_index = -1;
    struct sdio_func* func = 0;

    DPRINTK(KERN_INFO DRV_NAME"%s start!\n", __FUNCTION__);
    HIF_SDIO_ASSERT( pbuf );

    //4 <1> check if ctx is valid, registered, and probed
    probe_index = CLTCTX_IDX(ctx);
    if( probe_index < 0 )   /* the function has not been probed */
    {
        printk(KERN_INFO DRV_NAME"%s: can't find client in probed list!\n", __FUNCTION__);
        ret = -HIF_SDIO_ERR_FAIL;
        goto out;
    }
    else
    {
        if ( g_hif_sdio_probed_func_list[probe_index].clt_idx < 0 )   /* the client has not been registered */
        {
            printk(KERN_INFO DRV_NAME"%s: can't find client in registered list!\n", __FUNCTION__);
            ret = -HIF_SDIO_ERR_FAIL;
            goto out;
        }
    }
    func = g_hif_sdio_probed_func_list[probe_index].func;

    //4 <1.1> check if input parameters are valid

    //4 <2> 
    sdio_claim_host(func);
    ret = sdio_readsb(func, pbuf, offset, len);
    sdio_release_host(func);

    //4 <3> check result code and return proper error code

out:
    DPRINTK(KERN_INFO DRV_NAME"%s end!\n", __FUNCTION__);
    return ret;
} /* end of mtk_wcn_hif_sdio_read_buf() */


/*!
 * \brief
 *
 * detailed descriptions
 *
 * \param ctx client's context variable
 *
 * \retval 0    register successfully
 * \retval < 0  list error code here
 */
INT32 mtk_wcn_hif_sdio_write_buf (
    MTK_WCN_HIF_SDIO_CLTCTX ctx,
    UINT32 offset,
    PUINT32 pbuf,
    UINT32 len
    )
{
    INT32 ret = -HIF_SDIO_ERR_FAIL;
    int probe_index = -1;
    struct sdio_func* func = 0;

    DPRINTK(KERN_INFO DRV_NAME"%s start!\n", __FUNCTION__);
    HIF_SDIO_ASSERT( pbuf );

    //4 <1> check if ctx is valid, registered, and probed
    probe_index = CLTCTX_IDX(ctx);
    if( probe_index < 0 )   /* the function has not been probed */
    {
        printk(KERN_INFO DRV_NAME"%s: can't find client in probed list!\n", __FUNCTION__);
        ret = -HIF_SDIO_ERR_FAIL;
        goto out;
    }
    else
    {
        if ( g_hif_sdio_probed_func_list[probe_index].clt_idx < 0 )   /* the client has not been registered */
        {
            printk(KERN_INFO DRV_NAME"%s: can't find client in probed list!\n", __FUNCTION__);
            ret = -HIF_SDIO_ERR_FAIL;
            goto out;
        }
    }
    func = g_hif_sdio_probed_func_list[probe_index].func;

    //4 <1.1> check if input parameters are valid

    //4 <2> 
    sdio_claim_host(func);
    ret = sdio_writesb(func, offset, pbuf, len);
    sdio_release_host(func);

    //4 <3> check result code and return proper error code

out:
    DPRINTK(KERN_INFO DRV_NAME"%s: ret:%d, end!\n", __FUNCTION__, ret);
    return ret;
} /* end of mtk_wcn_hif_sdio_write_buf() */

/*!
 * \brief store client driver's private data function.
 *
 *
 * \param clent's MTK_WCN_HIF_SDIO_CLTCTX.
 *
 * \retval none.
 */
void mtk_wcn_hif_sdio_set_drvdata(
    MTK_WCN_HIF_SDIO_CLTCTX ctx,
    void* private_data_p
    )
{
    UINT8 probed_idx = CLTCTX_IDX(ctx);

    /* store client driver's private data to dev driver */
    g_hif_sdio_probed_func_list[probed_idx].private_data_p = private_data_p;
}

/*!
 * \brief get client driver's private data function.
 *
 *
 * \param clent's MTK_WCN_HIF_SDIO_CLTCTX.
 *
 * \retval private data pointer.
 */
void* mtk_wcn_hif_sdio_get_drvdata(
    MTK_WCN_HIF_SDIO_CLTCTX ctx
    )
{
    UINT8 probed_idx = CLTCTX_IDX(ctx);

    /* get client driver's private data to dev driver */
    if ( (probed_idx >= 0) && (probed_idx < CFG_CLIENT_COUNT) )
    {
        return g_hif_sdio_probed_func_list[probed_idx].private_data_p;
    }
    else
    {
        return 0;
    }
}

/*!
 * \brief control stp/wifi on/off from wmt.
 *
 *
 * \param (1)control function type, (2)on/off control.
 *
 * \retval (1)control results ,(2)unknow type: -5.
 */
INT32 mtk_wcn_hif_sdio_wmt_control(
    WMT_SDIO_FUNC_TYPE func_type,
    MTK_WCN_BOOL is_on
    )
{
    switch( func_type )
    {
        case WMT_SDIO_FUNC_STP:
            if ( is_on == MTK_WCN_BOOL_TRUE )
            {
                return hif_sdio_stp_on();
            }
            else
            {
                return hif_sdio_stp_off();
            }
            break;

        case WMT_SDIO_FUNC_WIFI:
            if ( is_on == MTK_WCN_BOOL_TRUE )
            {
                return hif_sdio_wifi_on();
            }
            else
            {
                return hif_sdio_wifi_off();
            }
            break;

        default:
            printk(KERN_INFO "mtk_wcn_hif_sdio_wmt_control(): unknown type: %d\n", func_type);
            return -5;
    }
}

/*!
 * \brief client's probe() worker.
 *
 *
 * \param work queue structure.
 *
 * \retval none.
 */
#if HIF_SDIO_DEBUG
static void hif_sdio_dump_probe_list
    ( void
    )
{
    int i = 0;

    DPRINTK(KERN_INFO DRV_NAME"%s: == DUMP probed list start ==\n", __FUNCTION__);

    for ( i=0; i<CFG_CLIENT_COUNT; i++ )
    {
        if ( g_hif_sdio_probed_func_list[i].func != 0 )
        {
            DPRINTK(KERN_INFO DRV_NAME"Index: %d\nFunc: 0x%p\nClt_idx:%d\nInterrupted:%d\n", i,\
                g_hif_sdio_probed_func_list[i].func, g_hif_sdio_probed_func_list[i].clt_idx,\
                g_hif_sdio_probed_func_list[i].interrupted );
        }
    }

    DPRINTK(KERN_INFO DRV_NAME"%s: == DUMP probed list end ==\n", __FUNCTION__);
}
#endif

/*!
 * \brief client's probe() function.
 *
 *
 * \param work queue structure.
 *
 * \retval none.
 */
static void hif_sdio_clt_probe_func (
    MTK_WCN_HIF_SDIO_REGISTINFO *registinfo_p,
    INT8 probe_idx
    )
{
    UINT16 card_id = 0;
    UINT16 func_num = 0;
    UINT16 blk_sz = 0;

    DPRINTK(KERN_INFO DRV_NAME"%s start!\n", __FUNCTION__);
    HIF_SDIO_ASSERT( registinfo_p );
    if (!registinfo_p) {
        printk(KERN_WARNING DRV_NAME"%s: registinfo_p NULL!!!\n", __FUNCTION__);
        return;
    }

    /* special case handling: if the clt's unregister is called during probe procedures */
    if ( !registinfo_p->func_info || !registinfo_p->sdio_cltinfo) {
        printk(KERN_WARNING DRV_NAME"%s: client's registinfo_p is cleared !!!\n", __FUNCTION__);
        return;
    }

    card_id = registinfo_p->func_info->card_id;
    func_num = registinfo_p->func_info->func_num;
    blk_sz = registinfo_p->func_info->blk_sz;
    registinfo_p->sdio_cltinfo->hif_clt_probe( CLTCTX(card_id, func_num, blk_sz, probe_idx),\
                                                            registinfo_p->func_info );

    DPRINTK(KERN_INFO DRV_NAME"card_id:%x\nfunc_num:%x\nblk_sz:%x\nprob_idx:%x\n", card_id, func_num, blk_sz, probe_idx);
    DPRINTK(KERN_INFO DRV_NAME"%s end!\n", __FUNCTION__);
}

/*!
 * \brief client's probe() worker.
 *
 *
 * \param work queue structure.
 *
 * \retval none.
 */
static void hif_sdio_clt_probe_worker(
    struct work_struct *work
    )
{
    MTK_WCN_HIF_SDIO_CLT_PROBE_WORKERINFO *clt_worker_info_p = 0;
    UINT16 card_id = 0;
    UINT16 func_num = 0;
    UINT16 blk_sz = 0;
    INT8   prob_idx = 0;

    DPRINTK(KERN_INFO DRV_NAME"%s start!\n", __FUNCTION__);

    HIF_SDIO_ASSERT( work );

    /* get client's information */
    clt_worker_info_p = container_of( work, MTK_WCN_HIF_SDIO_CLT_PROBE_WORKERINFO, probe_work );
    HIF_SDIO_ASSERT( clt_worker_info_p );
    HIF_SDIO_ASSERT( clt_worker_info_p->registinfo_p );

    /* special case handling: if the clt's unregister is called during probe procedures */
    if ( (clt_worker_info_p->registinfo_p->func_info == 0) || (clt_worker_info_p->registinfo_p->sdio_cltinfo==0) )
    {
        printk(KERN_WARNING DRV_NAME"%s: client's registinfo_p is cleared !!!\n", __FUNCTION__);
        vfree( clt_worker_info_p );
        return;
    }

    card_id = clt_worker_info_p->registinfo_p->func_info->card_id;
    func_num = clt_worker_info_p->registinfo_p->func_info->func_num;
    blk_sz = clt_worker_info_p->registinfo_p->func_info->blk_sz;
    prob_idx = clt_worker_info_p->probe_idx;

    /* Execute client's probe() func */
    clt_worker_info_p->registinfo_p->sdio_cltinfo->hif_clt_probe( CLTCTX(card_id, func_num, blk_sz, prob_idx),\
                                                        clt_worker_info_p->registinfo_p->func_info );

    vfree( clt_worker_info_p );

    DPRINTK(KERN_INFO DRV_NAME"card_id:%x\nfunc_num:%x\nblk_sz:%x\nprob_idx:%x\n", card_id, func_num, blk_sz, prob_idx);
    DPRINTK(KERN_INFO DRV_NAME"%s end!\n", __FUNCTION__);
}


/*!
 * \brief Initialize g_hif_sdio_probed_func_list
 *
 *
 * \param index of g_hif_sdio_probed_func_list.
 *
 * \retval none.
 */
static void hif_sdio_init_probed_list(
    INT32 index
    )
{
    if ( (index >= 0) && (index < CFG_CLIENT_COUNT) )
    {
        /* probed spin lock */
        spin_lock_bh( &g_hif_sdio_lock_info.probed_list_lock );
        g_hif_sdio_probed_func_list[index].func = 0;
        g_hif_sdio_probed_func_list[index].clt_idx = -1;
        g_hif_sdio_probed_func_list[index].interrupted = MTK_WCN_BOOL_FALSE;
        g_hif_sdio_probed_func_list[index].private_data_p = 0;
        g_hif_sdio_probed_func_list[index].on_by_wmt = MTK_WCN_BOOL_FALSE;
        g_hif_sdio_probed_func_list[index].off_by_wmt = MTK_WCN_BOOL_FALSE;
        /* probed spin unlock */
        spin_unlock_bh( &g_hif_sdio_lock_info.probed_list_lock );
    }
    else
    {
        printk(KERN_ERR DRV_NAME"%s:[ERROR]index is out of g_hif_sdio_probed_func_list[] boundary!\n", __FUNCTION__);
    }
}


/*!
 * \brief Initialize g_hif_sdio_clt_drv_list
 *
 *
 * \param index of g_hif_sdio_clt_drv_list.
 *
 * \retval none.
 */
static void hif_sdio_init_clt_list(
    INT32 index
    )
{
    // client list spin lock
    spin_lock_bh( &g_hif_sdio_lock_info.clt_list_lock );
    if ( (index >= 0) && (index < CFG_CLIENT_COUNT) )
    {
        g_hif_sdio_clt_drv_list[index].sdio_cltinfo = 0;
        g_hif_sdio_clt_drv_list[index].func_info = 0;
    }
    else
    {
        printk(KERN_ERR DRV_NAME"%s:[ERROR]index is out of g_hif_sdio_clt_drv_list[] boundary!\n", __FUNCTION__);
    }
    // client list spin unlock
    spin_unlock_bh( &g_hif_sdio_lock_info.clt_list_lock );
}


/*!
 * \brief find matched g_hif_sdio_probed_func_list index from sdio function handler
 *
 *
 * \param sdio function handler
 *
 * \retval -1    index not found
 * \retval >= 0  return found index
 */
static int hif_sdio_find_probed_list_index_by_func(
    struct sdio_func* func
    )
{
    int i = 0;

    HIF_SDIO_ASSERT( func );

    for( i=0; i<CFG_CLIENT_COUNT; i++ )
    {
        if ( g_hif_sdio_probed_func_list[i].func == func )
        {
            return i;
        }
    }

    return -1;
}

/*!
 * \brief find matched g_hif_sdio_probed_func_list from g_hif_sdio_clt_drv_list index
 *
 *
 * \param g_hif_sdio_clt_drv_list index.
 *
 * \retval -1    index not found
 * \retval >= 0  return found index
 */
static int hif_sdio_find_probed_list_index_by_clt_index(
    INT32 clt_index
    )
{
    int i = 0;

    for ( i=0; i<CFG_CLIENT_COUNT; i++ )
    {
        if ( g_hif_sdio_probed_func_list[i].clt_idx == clt_index )
        {
            return i;
        }
    }
    if ( i == CFG_CLIENT_COUNT )
    {
        printk(KERN_INFO DRV_NAME "Cannot find clt_index:%d, i=%d\n", clt_index, i);
        /* client func has not been probed */
        return -1;
    }
    return -1;
}

/*!
 * \brief find matched g_hif_sdio_probed_func_list from vendor_id, device_id, and function number
 *
 *
 * \param vendor id, device id, and function number of the sdio card.
 *
 * \retval -1    index not found
 * \retval >= 0  return found index
 */
static int hif_sdio_find_probed_list_index_by_id_func(
    UINT16 vendor,
    UINT16 device,
    UINT16 func_num
    )
{
    int i = 0;

    for ( i=0; i<CFG_CLIENT_COUNT; i++ )
    {
        if ( g_hif_sdio_probed_func_list[i].func == 0 )
        {
            continue;
        }
        else if ( (g_hif_sdio_probed_func_list[i].func->vendor == vendor) && 
            (g_hif_sdio_probed_func_list[i].func->device == device) && 
            (g_hif_sdio_probed_func_list[i].func->num == func_num)  )
        {
            return i;
        }
    }
    if ( i == CFG_CLIENT_COUNT )
    {
        printk(KERN_INFO DRV_NAME "Cannot find vendor:%d, device:%d, func_num:%d, i=%d\n",\
            vendor, device, func_num, i);
        /* client func has not been probed */
        return -1;
    }
    return -1;
}

/*!
 * \brief find matched g_hif_sdio_clt_drv_list index
 *
 * find the matched g_hif_sdio_clt_drv_list index from card_id and function number.
 *
 * \param vendor id, device id, and function number of the sdio card
 *
 * \retval -1    index not found
 * \retval >= 0  return found index
 */
static int hif_sdio_find_clt_list_index (
    UINT16 vendor,
    UINT16 device,
    UINT16 func_num
    )
{
    int i = 0;

    for( i=0; i<CFG_CLIENT_COUNT; i++ )
    {
        if ( g_hif_sdio_clt_drv_list[i].func_info != 0 )
        {
            if ( (g_hif_sdio_clt_drv_list[i].func_info->manf_id == vendor ) &&\
                (g_hif_sdio_clt_drv_list[i].func_info->card_id == device ) &&\
                (g_hif_sdio_clt_drv_list[i].func_info->func_num == func_num ) )
            {
                return i;
            }
        }
    }

    return -1;
}


/*!
 * \brief check if the vendor, device ids are supported in mtk_sdio_id_tbl.
 *
 *
 * \param vendor id and device id of the sdio card
 *
 * \retval (-HIF_SDIO_ERR_FAIL)  vendor, device ids are not suppported
 * \retval HIF_SDIO_ERR_SUCCESS  vendor, device ids are suppported
 */
static int hif_sdio_check_supported_sdio_id(
    UINT16 vendor,
    UINT16 device
    )
{
    int i = 0;

    for ( i=0; i<CFG_CLIENT_COUNT; i++ )
    {
        if ( (mtk_sdio_id_tbl[i].vendor == vendor) && (mtk_sdio_id_tbl[i].device == device) )
        {
            return HIF_SDIO_ERR_SUCCESS;  /* mtk_sdio_id is supported */
        }
    }
    return (-HIF_SDIO_ERR_FAIL);    /* mtk_sdio_id is not supported */
}


/*!
 * \brief check if the vendor, device ids are duplicated in g_hif_sdio_clt_drv_list.
 *
 *
 * \param vendor id, device id, and function number of the sdio card
 *
 * \retval (-HIF_SDIO_ERR_DUPLICATED)  vendor, device, func_num are duplicated
 * \retval HIF_SDIO_ERR_SUCCESS        vendor, device, func_num are not duplicated
 */
static int hif_sdio_check_duplicate_sdio_id(
    UINT16 vendor,
    UINT16 device,
    UINT16 func_num
    )
{
    int i = 0;

    for ( i=0; i<CFG_CLIENT_COUNT; i++ )
    {
        if( g_hif_sdio_clt_drv_list[i].func_info != 0 )
        {
            if ( ( g_hif_sdio_clt_drv_list[i].func_info->manf_id == vendor ) &&\
                ( g_hif_sdio_clt_drv_list[i].func_info->card_id == device ) &&\
                ( g_hif_sdio_clt_drv_list[i].func_info->func_num == func_num ) )
            {
                return (-HIF_SDIO_ERR_DUPLICATED);  /* duplicated */
            }
        }
    }
    return HIF_SDIO_ERR_SUCCESS;    /* Not duplicated */
}


/*!
 * \brief Add the client info into g_hif_sdio_clt_drv_list.
 *
 *
 * \param [output] client's index pointer.
 * \param MTK_WCN_HIF_SDIO_CLTINFO of client's contex.
 *
 * \retval (-HIF_SDIO_ERR_FAIL)  Add to clt_list successfully
 * \retval HIF_SDIO_ERR_SUCCESS  Add to clt_list failed (buffer is full)
 */
static int hif_sdio_add_clt_list(
    INT32*  clt_index_p,
    const MTK_WCN_HIF_SDIO_CLTINFO *pinfo,
    UINT32 tbl_index
    )
{
    int i = 0;

    HIF_SDIO_ASSERT( clt_index_p );
    HIF_SDIO_ASSERT( pinfo );

    for( i=0; i<CFG_CLIENT_COUNT; i++ )
    {
        // client list spin lock
        spin_lock_bh( &g_hif_sdio_lock_info.clt_list_lock );
        if( g_hif_sdio_clt_drv_list[i].func_info == 0 )
        {
            g_hif_sdio_clt_drv_list[i].func_info = &(pinfo->func_tbl[tbl_index]);
            g_hif_sdio_clt_drv_list[i].sdio_cltinfo = pinfo;
            // client list spin unlock
            spin_unlock_bh( &g_hif_sdio_lock_info.clt_list_lock );
            *clt_index_p = i;
            return HIF_SDIO_ERR_SUCCESS;    /* Add to client list successfully */
        }
        // client list spin unlock
        spin_unlock_bh( &g_hif_sdio_lock_info.clt_list_lock );
    }
    return (-HIF_SDIO_ERR_FAIL);    /* Add to client list failed (buffer is full) */
}


/*!
 * \brief hif_sdio probe function
 *
 * hif_sdio probe function called by mmc driver when any matched SDIO function
 * is detected by it.
 *
 * \param func
 * \param id
 *
 * \retval 0    register successfully
 * \retval < 0  list error code here
 */
static int hif_sdio_probe (
    struct sdio_func *func,
    const struct sdio_device_id *id
    )
{
    int ret = 0;
    int i = 0;
    MTK_WCN_HIF_SDIO_PROBEINFO* hif_sdio_probed_funcp = 0;
    INT32 probe_index = -1;
#if 0
    INT32 clt_index = -1;
    MTK_WCN_HIF_SDIO_CLT_PROBE_WORKERINFO *clt_probe_worker_info = 0;
#endif

    //printk(KERN_INFO DRV_NAME "%s \n", __FUNCTION__);
    HIF_SDIO_ASSERT( func );

    //4 <0> display debug information
    //printk(KERN_INFO DRV_NAME "Card information checking...\n");
    //printk(KERN_INFO DRV_NAME "func = 0x%p\n", func);
    printk(KERN_INFO DRV_NAME "vendor(0x%x) device(0x%x) num(0x%x)\n", func->vendor, func->device, func->num);
    //printk(KERN_INFO DRV_NAME "Number of info = %d:\n", func->card->num_info);
    for (i = 0;i < func->card->num_info;i++) {
        printk(KERN_INFO DRV_NAME "card->info[%d]: %s\n", i, func->card->info[i]);
    }

    //4 <1> Check if this  is supported by us (mtk_sdio_id_tbl)
    ret = hif_sdio_check_supported_sdio_id( func->vendor, func->device );
    if (ret) {
        printk(KERN_INFO DRV_NAME"vendor id and device id of sdio_func are not supported in mtk_sdio_id_tbl!\n");
        goto out;
    }

    //4 <2> Add this struct sdio_func *func to g_hif_sdio_probed_func_list
    for( i=0; i<CFG_CLIENT_COUNT; i++ )
    {
        /* probed spin lock */
        spin_lock_bh( &g_hif_sdio_lock_info.probed_list_lock );
        if ( g_hif_sdio_probed_func_list[i].func == 0 )
        {
            hif_sdio_probed_funcp = &g_hif_sdio_probed_func_list[i];
            hif_sdio_probed_funcp->func = func;
            hif_sdio_probed_funcp->clt_idx = hif_sdio_find_clt_list_index(func->vendor, func->device, func->num);
            hif_sdio_probed_funcp->interrupted = MTK_WCN_BOOL_FALSE;
            /* probed spin unlock */
            spin_unlock_bh( &g_hif_sdio_lock_info.probed_list_lock );
            probe_index = i;
            break;
        }
        else
        {
            /* probed spin unlock */
            spin_unlock_bh( &g_hif_sdio_lock_info.probed_list_lock );
        }
    }
    if ( (probe_index < 0) || (probe_index >= CFG_CLIENT_COUNT) )
    {
        printk(KERN_ERR DRV_NAME"[ERROR]probe function list if full!\n");
        goto out;
    }

    //4 <3> Initialize this function
    if ( g_hif_sdio_probed_func_list[probe_index].clt_idx < 0 )
    {
        for( i=0; i<CFG_CLIENT_COUNT; i++ )
        {
            // client list spin lock
            spin_lock_bh( &g_hif_sdio_lock_info.clt_list_lock );
            if ( g_hif_sdio_clt_drv_list[i].func_info == 0 )
            {
                // client list spin unlock
                spin_unlock_bh( &g_hif_sdio_lock_info.clt_list_lock );
                continue;
            }
            printk(KERN_INFO DRV_NAME"manf_id:%x, card_id:%x, func_num:%d\n", g_hif_sdio_clt_drv_list[i].func_info->manf_id, g_hif_sdio_clt_drv_list[i].func_info->card_id, g_hif_sdio_clt_drv_list[i].func_info->func_num );
            if ( (g_hif_sdio_clt_drv_list[i].func_info->manf_id == g_hif_sdio_probed_func_list[probe_index].func->vendor)&&\
                 (g_hif_sdio_clt_drv_list[i].func_info->card_id == g_hif_sdio_probed_func_list[probe_index].func->device)&&\
                 (g_hif_sdio_clt_drv_list[i].func_info->func_num == g_hif_sdio_probed_func_list[probe_index].func->num) )
            {
                g_hif_sdio_probed_func_list[probe_index].clt_idx = i;
                // client list spin unlock
                spin_unlock_bh( &g_hif_sdio_lock_info.clt_list_lock );
                break;
            }
            else
            {
                // client list spin unlock
                spin_unlock_bh( &g_hif_sdio_lock_info.clt_list_lock );
            }
        }
        printk(KERN_INFO DRV_NAME"map to g_hif_sdio_clt_drv_list[] done: %d\n", g_hif_sdio_probed_func_list[probe_index].clt_idx );
    }

    //4 <3.1> enable this function
    sdio_claim_host(func);
    ret = sdio_enable_func(func);
    sdio_release_host(func);
    if (ret) {
        printk(KERN_INFO DRV_NAME"sdio_enable_func failed!\n");
        goto out;
    }

    //4 <3.2> set block size according to the table storing function characteristics
    if ( hif_sdio_probed_funcp == 0 )
    {
        printk(KERN_ERR DRV_NAME"[ERROR]hif_sdio_probed_funcp is null!\n");
        goto out;
    }
    if ( hif_sdio_probed_funcp->clt_idx >= 0 )   /* The clt contex has been registed */
    {
        sdio_claim_host(func);
	    ret = sdio_set_block_size(func, g_hif_sdio_clt_drv_list[hif_sdio_probed_funcp->clt_idx].func_info->blk_sz);
	    sdio_release_host(func);
    }
    else    /* The clt contex has not been registed */
    {
        sdio_claim_host(func);
	    ret = sdio_set_block_size(func, HIF_DEFAULT_BLK_SIZE);
	    sdio_release_host(func);
    }
    if (ret) {
        printk(KERN_INFO DRV_NAME"set sdio block size failed!\n");
        goto out;
    }

    printk(KERN_INFO DRV_NAME"blksize: cur(%d) max(%d) \n",
        func->cur_blksize, func->max_blksize);
    printk(KERN_INFO DRV_NAME"host max: blk_size(%d) blk_count(%d) \n",
        func->card->host->max_blk_size, func->card->host->max_blk_count);

#if 0
    //4 <3.3> claim irq for this function
    sdio_claim_host(func);
    ret = sdio_claim_irq(func, hif_sdio_irq);
    sdio_release_host(func);
    printk(KERN_INFO "sdio_claim_irq ret=%d\n", ret);

    //4 <3.4> If this struct sdio_func *func is supported by any driver in
    //4 g_hif_sdio_clt_drv_list, schedule another task to call client's .hif_clt_probe()
    if ( (clt_index = g_hif_sdio_probed_func_list[probe_index].clt_idx) >= 0 )    /* the function has been registered */
    {
        /* use worker thread to perform the client's .hif_clt_probe() */
        clt_probe_worker_info = vmalloc( sizeof(MTK_WCN_HIF_SDIO_CLT_PROBE_WORKERINFO) );
        INIT_WORK( &clt_probe_worker_info->probe_work, hif_sdio_clt_probe_worker );
        clt_probe_worker_info->registinfo_p = &g_hif_sdio_clt_drv_list[clt_index];
        clt_probe_worker_info->probe_idx = probe_index;
        schedule_work( &clt_probe_worker_info->probe_work );
    }
#endif

#if HIF_SDIO_DEBUG
    hif_sdio_dump_probe_list();
#endif

out:
    //4 <last> error handling
    return ret;
}


/*!
 * \brief hif_sdio remove function
 *
 * hif_sdio probe function called by mmc driver when the probed func should be
 * removed.
 *
 * \param func
 *
 */
static void hif_sdio_remove (
    struct sdio_func *func
    )
{
    int probed_list_index = 0;
#if 0
    int registed_list_index = 0;
#endif

    printk(KERN_INFO DRV_NAME"%s\n", __FUNCTION__);
    HIF_SDIO_ASSERT( func );

    //4 <1> check input parameter is valid and has been probed previously
    if (func == NULL) {
        printk(KERN_WARNING DRV_NAME"%s error (%p)\n", __FUNCTION__, func);
        return;
    }

    //4 <2> if this function has been initialized by any client driver,
    //4 call client's .hif_clt_remove() call back in THIS context.
    probed_list_index = hif_sdio_find_probed_list_index_by_func( func );
    if ( probed_list_index < 0 )
    {
        printk(KERN_WARNING DRV_NAME"sdio function pointer is not in g_hif_sdio_probed_func_list!\n");
        return;
    }
#if 0
    registed_list_index = g_hif_sdio_probed_func_list[probed_list_index].clt_idx;
    if ( registed_list_index >= 0 )
    {
        g_hif_sdio_clt_drv_list[registed_list_index].sdio_cltinfo->hif_clt_remove( CLTCTX(func->device, func->num,\
                                                                            func->cur_blksize, probed_list_index) );
    }
#endif

    //4 <3> mark this function as de-initialized and invalidate client's context
    hif_sdio_init_probed_list(probed_list_index);

#if 0
    //4 <4> release irq for this function
    sdio_claim_host(func);
    sdio_release_irq(func);
    sdio_release_host(func);
#endif

    //4 <5> disable this function
    sdio_claim_host(func);
    sdio_disable_func(func);
    sdio_release_host(func);

    //4 <6> mark this function as removed

    printk(KERN_WARNING DRV_NAME"%s:sdio func(0x%p) is removed successfully!\n", __FUNCTION__, func);
}

/*!
 * \brief hif_sdio interrupt handler
 *
 * detailed descriptions
 *
 * \param ctx client's context variable
 *
 */
static void hif_sdio_irq (
    struct sdio_func *func
    )
{
    int probed_list_index = -1;
    int registed_list_index = -1;

    DPRINTK(KERN_INFO DRV_NAME"%s\n", __FUNCTION__);

    //4 <1> check if func is valid
    HIF_SDIO_ASSERT( func );
    
    //4 <2> if func has valid corresponding hif_sdio client's context, mark it
    //4 host-locked, use it to call client's .hif_clt_irq() callback function in
    //4 THIS context.
    probed_list_index = hif_sdio_find_probed_list_index_by_func( func );
    if ( (probed_list_index < 0) || (probed_list_index >= CFG_CLIENT_COUNT) )
    {
        printk(KERN_ERR DRV_NAME"%s: [ERROR]probed_list_index not found!\n", __FUNCTION__);
        return;
    }

    registed_list_index = g_hif_sdio_probed_func_list[probed_list_index].clt_idx;
    g_hif_sdio_probed_func_list[probed_list_index].interrupted = MTK_WCN_BOOL_TRUE;
    if ( registed_list_index >= 0 )
    {
        g_hif_sdio_clt_drv_list[registed_list_index].sdio_cltinfo->hif_clt_irq( CLTCTX(func->device,\
                                                                    func->num, func->cur_blksize, probed_list_index) );
    }
    else
    {
    //4 <3> if func has no VALID hif_sdio client's context, release irq for this
    //4 func and mark it in g_hif_sdio_probed_func_list (remember: donnot claim host in irq contex).
        printk(KERN_INFO DRV_NAME"%s: release irq (func:0x%p)\n", __FUNCTION__, func);
	    sdio_release_irq(func);
    }

    g_hif_sdio_probed_func_list[probed_list_index].interrupted = MTK_WCN_BOOL_FALSE;
    return;
}

/*!
 * \brief hif_sdio init function
 *
 * detailed descriptions
 *
 * \retval
 */
static int __init hif_sdio_init(void)
{
    int   ret = 0;
    INT32 i   = 0;
    printk(KERN_INFO DRV_NAME"%s start \n", __FUNCTION__);

    //4 <1> init all private variables
    /* init reference count to 0 */
    gRefCount = 0;

    /* init spin lock information */
#if 0
    g_hif_sdio_lock_info.probed_list_lock = SPIN_LOCK_UNLOCKED;
    g_hif_sdio_lock_info.clt_list_lock = SPIN_LOCK_UNLOCKED;
#endif
    spin_lock_init( &g_hif_sdio_lock_info.probed_list_lock );
    spin_lock_init( &g_hif_sdio_lock_info.clt_list_lock );

    /* init probed function list and g_hif_sdio_clt_drv_list */
    for ( i=0; i<CFG_CLIENT_COUNT; i++ )
    {
        hif_sdio_init_probed_list(i);
        hif_sdio_init_clt_list(i);
    }

    //4 <2> register to mmc driver
    ret = sdio_register_driver(&mtk_sdio_client_drv);
    printk(KERN_INFO DRV_NAME"sdio_register_driver() ret=%d\n", ret);

    printk(KERN_INFO DRV_NAME"%s end\n", __FUNCTION__);
    return ret;
}

/*!
 * \brief hif_sdio init function
 *
 * detailed descriptions
 *
 * \retval
 */
static VOID __exit hif_sdio_exit(void)
{
    printk(KERN_INFO DRV_NAME"%s start \n", __FUNCTION__);

    //4 <0> if client driver is not removed yet, we shall NOT be called...

    //4 <1> check reference count
    if ( gRefCount !=0  )
    {
        printk(KERN_WARNING DRV_NAME"%s Warnning: gRefCount=%d !!!\n", __FUNCTION__, gRefCount);
    }

    //4 <2> check if there is any hif_sdio-registered clients. There should be
    //4 no registered client...

    //4 <3> Reregister with mmc driver. Our remove handler hif_sdio_remove()
    //4 will be called later by mmc_core. Clean up driver resources there.
    sdio_unregister_driver(&mtk_sdio_client_drv);

    printk(KERN_INFO DRV_NAME"%s end\n", __FUNCTION__);
    return;
} /* end of exitWlan() */

/*!
 * \brief stp on by wmt (probe client driver).
 *
 *
 * \param none.
 *
 * \retval 0:success, -1:not registered, -2:not probed, -3:has been on by wmt.
 */
INT32 hif_sdio_stp_on(
    void
    )
{
#if 0
    MTK_WCN_HIF_SDIO_CLT_PROBE_WORKERINFO *clt_probe_worker_info = 0;
#endif    
    INT32 clt_index = -1;
    INT32 probe_index = -1;
    struct sdio_func *func = 0;
    int ret = -1;

    printk(KERN_INFO DRV_NAME "hif_sdio_stp_on()\n");

#if 1
    //4 <1> If stp client drv has not been probed, return error code
    /* MT6620 */
    if ( (probe_index = hif_sdio_find_probed_list_index_by_id_func(0x037A, 0x020B, 1)) >= 0 )
    {
        goto stp_on_exist;
    }
    if ( (probe_index = hif_sdio_find_probed_list_index_by_id_func(0x037A, 0x020C, 1)) >= 0 )
    {
        goto stp_on_exist;
    }

    /* MT6619 */
    if ( (probe_index = hif_sdio_find_probed_list_index_by_id_func(0x037A, 0x6619, 1)) >= 0 )
    {
        goto stp_on_exist;
    }

    /* MT6618 */
    if ( (probe_index = hif_sdio_find_probed_list_index_by_id_func(0x037A, 0x018B, 1)) >= 0 )
    {
        goto stp_on_exist;
    }
    if ( (probe_index = hif_sdio_find_probed_list_index_by_id_func(0x037A, 0x018C, 1)) >= 0 )
    {
        goto stp_on_exist;
    }
    else
    {
        //4 <2> If stp client drv has not been probed, return error code
        /* client func has not been probed */
        return -2;
    }
#else
    //4 <1> If stp client drv has not been registered, return error code
    /* MT6620 */
    if ( (clt_index = hif_sdio_find_clt_list_index(0x037A, 0x020B, 1)) >= 0 )
    {
        probe_index = hif_sdio_find_probed_list_index_by_clt_index( clt_index );
        if ( probe_index >= 0 )
        {
            goto stp_on_exist;
        }
    }
    if ( (clt_index = hif_sdio_find_clt_list_index(0x037A, 0x020C, 1)) >= 0 )
    {
        probe_index = hif_sdio_find_probed_list_index_by_clt_index( clt_index );
        if ( probe_index >= 0 )
        {
            goto stp_on_exist;
        }
    }

    /* MT6619 */
    if ( (clt_index = hif_sdio_find_clt_list_index(0x037A, 0x6619, 1)) >= 0 )
    {
        probe_index = hif_sdio_find_probed_list_index_by_clt_index( clt_index );
        if ( probe_index >= 0 )
        {
            goto stp_on_exist;
        }
    }

    /* MT6618 */
    if ( (clt_index = hif_sdio_find_clt_list_index(0x037A, 0x018B, 1)) >= 0 )
    {
        probe_index = hif_sdio_find_probed_list_index_by_clt_index( clt_index );
        if ( probe_index >= 0 )
        {
            goto stp_on_exist;
        }
    }
    if ( (clt_index = hif_sdio_find_clt_list_index(0x037A, 0x018C, 1)) >= 0 )
    {
        probe_index = hif_sdio_find_probed_list_index_by_clt_index( clt_index );
        if ( probe_index >= 0 )
        {
            goto stp_on_exist;
        }
    }
    else
    {
        return -1;
    }

    //4 <2> If stp client drv has not been probed, return error code
    /* client func has not been probed */
    return -2;
#endif    

stp_on_exist:
    //4 <3> If stp client drv has been on by wmt, return error code
    if ( g_hif_sdio_probed_func_list[probe_index].on_by_wmt )
    {
        return -3;
    }
    else
    {
        g_hif_sdio_probed_func_list[probe_index].on_by_wmt = MTK_WCN_BOOL_TRUE;
    }

    if ( (clt_index = g_hif_sdio_probed_func_list[probe_index].clt_idx) >= 0 )    /* the function has been registered */
    {
        //4 <4> claim irq for this function
        func = g_hif_sdio_probed_func_list[probe_index].func;
        sdio_claim_host(func);
        ret = sdio_claim_irq(func, hif_sdio_irq);
        sdio_release_host(func);
        printk(KERN_INFO "sdio_claim_irq ret=%d\n", ret);

        //4 <5> If this struct sdio_func *func is supported by any driver in
        //4 g_hif_sdio_clt_drv_list, schedule another task to call client's .hif_clt_probe()    
#if 1
        /* Call client's .hif_clt_probe() */
        hif_sdio_clt_probe_func(&g_hif_sdio_clt_drv_list[clt_index], probe_index);
#else
        /* use worker thread to perform the client's .hif_clt_probe() */
        clt_probe_worker_info = vmalloc( sizeof(MTK_WCN_HIF_SDIO_CLT_PROBE_WORKERINFO) );
        INIT_WORK( &clt_probe_worker_info->probe_work, hif_sdio_clt_probe_worker );
        clt_probe_worker_info->registinfo_p = &g_hif_sdio_clt_drv_list[clt_index];
        clt_probe_worker_info->probe_idx = probe_index;
        schedule_work( &clt_probe_worker_info->probe_work );
#endif
    }

    return 0;
}

/*!
 * \brief stp off by wmt (remove client driver).
 *
 *
 * \param none.
 *
 * \retval 0:success, -1:not registered, -2:not probed, -3:has been off by wmt.
 */
INT32 hif_sdio_stp_off(
    void
    )
{
    INT32 clt_index = -1;
    INT32 probe_index = -1;
    struct sdio_func *func = 0;
    int ret = -1;

    printk(KERN_INFO DRV_NAME "hif_sdio_stp_off()\n");

#if 1
    //4 <1> If stp client drv has not been probed, return error code
    /* MT6620 */
    if ( (probe_index = hif_sdio_find_probed_list_index_by_id_func(0x037A, 0x020B, 1)) >= 0 )
    {
        goto stp_off_exist;
    }
    if ( (probe_index = hif_sdio_find_probed_list_index_by_id_func(0x037A, 0x020C, 1)) >= 0 )
    {
        goto stp_off_exist;
    }

    /* MT6619 */
    if ( (probe_index = hif_sdio_find_probed_list_index_by_id_func(0x037A, 0x6619, 1)) >= 0 )
    {
        goto stp_off_exist;
    }

    /* MT6618 */
    if ( (probe_index = hif_sdio_find_probed_list_index_by_id_func(0x037A, 0x018B, 1)) >= 0 )
    {
        goto stp_off_exist;
    }
    if ( (probe_index = hif_sdio_find_probed_list_index_by_id_func(0x037A, 0x018C, 1)) >= 0 )
    {
        goto stp_off_exist;
    }
    else
    {
        //4 <2> If stp client drv has not been probed, return error code
        /* client func has not been probed */
        return -2;
    }
#else
    //4 <1> If stp client drv has not been registered, return error code
    /* MT6620 */
    if ( (clt_index = hif_sdio_find_clt_list_index(0x037A, 0x020B, 1)) >= 0 )
    {
        probe_index = hif_sdio_find_probed_list_index_by_clt_index( clt_index );
        if ( probe_index >= 0 )
        {
            goto stp_off_exist;
        }
    }
    if ( (clt_index = hif_sdio_find_clt_list_index(0x037A, 0x020C, 1)) >= 0 )
    {
        probe_index = hif_sdio_find_probed_list_index_by_clt_index( clt_index );
        if ( probe_index >= 0 )
        {
            goto stp_off_exist;
        }
    }

    /* MT6619 */
    if ( (clt_index = hif_sdio_find_clt_list_index(0x037A, 0x6619, 1)) >= 0 )
    {
        probe_index = hif_sdio_find_probed_list_index_by_clt_index( clt_index );
        if ( probe_index >= 0 )
        {
            goto stp_off_exist;
        }
    }

    /* MT6618 */
    if ( (clt_index = hif_sdio_find_clt_list_index(0x037A, 0x018B, 1)) >= 0 )
    {
        probe_index = hif_sdio_find_probed_list_index_by_clt_index( clt_index );
        if ( probe_index >= 0 )
        {
            goto stp_off_exist;
        }
    }
    if ( (clt_index = hif_sdio_find_clt_list_index(0x037A, 0x018C, 1)) >= 0 )
    {
        probe_index = hif_sdio_find_probed_list_index_by_clt_index( clt_index );
        if ( probe_index >= 0 )
        {
            goto stp_off_exist;
        }
    }
    else
    {
        return -1;
    }

    //4 <2> If stp client drv has not been probed, return error code
    /* client func has not been probed */
    return -2;
#endif

stp_off_exist:
    //4 <3> If stp client drv has been off by wmt, return error code
    if ( g_hif_sdio_probed_func_list[probe_index].off_by_wmt )
    {
        return -3;
    }
    else
    {
        g_hif_sdio_probed_func_list[probe_index].off_by_wmt = MTK_WCN_BOOL_TRUE;
    }

    //4 <4> release irq for this function
    func = g_hif_sdio_probed_func_list[probe_index].func;
    sdio_claim_host(func);
    ret = sdio_release_irq(func);
    sdio_release_host(func);
    printk(KERN_INFO "sdio_release_irq ret=%d\n", ret);

    if ( (clt_index = g_hif_sdio_probed_func_list[probe_index].clt_idx) >= 0 )    /* the function has been registered */
    {
        //4 <5> Callback to client driver's remove() func
        g_hif_sdio_clt_drv_list[clt_index].sdio_cltinfo->hif_clt_remove( CLTCTX(func->device, func->num,\
                                                                            func->cur_blksize, probe_index) );
    }

    return 0;
}

/*!
 * \brief wifi on by wmt (probe client driver).
 *
 *
 * \param none.
 *
 * \retval 0:success, -1:not registered, -2:not probed, -3:has been on by wmt.
 */
INT32 hif_sdio_wifi_on(
    void
    )
{
#if 0
    MTK_WCN_HIF_SDIO_CLT_PROBE_WORKERINFO *clt_probe_worker_info = 0;
#endif
    INT32 clt_index = -1;
    INT32 probe_index = -1;
    struct sdio_func *func = 0;
    int ret = -1;

    printk(KERN_INFO DRV_NAME "hif_sdio_wifi_on()\n");

#if 1
    //4 <1> If wifi client drv has not been probed, return error code
    /* MT6620 */
    if ( (probe_index = hif_sdio_find_probed_list_index_by_id_func(0x037A, 0x020A, 1)) >= 0 )
    {
        goto wifi_on_exist;
    }
    if ( (probe_index = hif_sdio_find_probed_list_index_by_id_func(0x037A, 0x020C, 2)) >= 0 )
    {
        goto wifi_on_exist;
    }

    /* MT6618 */
    if ( (probe_index = hif_sdio_find_probed_list_index_by_id_func(0x037A, 0x018A, 1)) >= 0 )
    {
        goto wifi_on_exist;
    }
    if ( (probe_index = hif_sdio_find_probed_list_index_by_id_func(0x037A, 0x018C, 2)) >= 0 )
    {
        goto wifi_on_exist;
    }
    else
    {
        //4 <2> If wifi client drv has not been probed, return error code
        /* client func has not been probed */
        return -2;
    }
#else
    //4 <1> If wifi client drv has not been registered, return error code
    /* MT6620 */
    if ( (clt_index = hif_sdio_find_clt_list_index(0x037A, 0x020A, 1)) >= 0 )
    {
        probe_index = hif_sdio_find_probed_list_index_by_clt_index( clt_index );
        if ( probe_index >= 0 )
        {
            goto wifi_on_exist;
        }
    }
    if ( (clt_index = hif_sdio_find_clt_list_index(0x037A, 0x020C, 2)) >= 0 )
    {
        probe_index = hif_sdio_find_probed_list_index_by_clt_index( clt_index );
        if ( probe_index >= 0 )
        {
            goto wifi_on_exist;
        }
    }

    /* MT6618 */
    if ( (clt_index = hif_sdio_find_clt_list_index(0x037A, 0x018A, 1)) >= 0 )
    {
        probe_index = hif_sdio_find_probed_list_index_by_clt_index( clt_index );
        if ( probe_index >= 0 )
        {
            goto wifi_on_exist;
        }
    }
    if ( (clt_index = hif_sdio_find_clt_list_index(0x037A, 0x018C, 2)) >= 0 )
    {
        probe_index = hif_sdio_find_probed_list_index_by_clt_index( clt_index );
        if ( probe_index >= 0 )
        {
            goto wifi_on_exist;
        }
    }
    else
    {
        return -1;
    }


    //4 <2> If wifi client drv has not been probed, return error code
    /* client func has not been probed */
    return -2;
#endif

wifi_on_exist:
    //4 <3> If wifi client drv has been on by wmt, return error code
    if ( g_hif_sdio_probed_func_list[probe_index].on_by_wmt )
    {
        return -3;
    }
    else
    {
        g_hif_sdio_probed_func_list[probe_index].on_by_wmt = MTK_WCN_BOOL_TRUE;
    }

    if ( (clt_index = g_hif_sdio_probed_func_list[probe_index].clt_idx) >= 0 )    /* the function has been registered */
    {
        //4 <4> claim irq for this function
        func = g_hif_sdio_probed_func_list[probe_index].func;
        sdio_claim_host(func);
        ret = sdio_claim_irq(func, hif_sdio_irq);
        sdio_release_host(func);
        printk(KERN_INFO "sdio_claim_irq ret=%d\n", ret);

        //4 <5> If this struct sdio_func *func is supported by any driver in
        //4 g_hif_sdio_clt_drv_list, schedule another task to call client's .hif_clt_probe()    
#if 1
        /* Call client's .hif_clt_probe() */
        hif_sdio_clt_probe_func(&g_hif_sdio_clt_drv_list[clt_index], probe_index);
#else
        /* use worker thread to perform the client's .hif_clt_probe() */
        clt_probe_worker_info = vmalloc( sizeof(MTK_WCN_HIF_SDIO_CLT_PROBE_WORKERINFO) );
        INIT_WORK( &clt_probe_worker_info->probe_work, hif_sdio_clt_probe_worker );
        clt_probe_worker_info->registinfo_p = &g_hif_sdio_clt_drv_list[clt_index];
        clt_probe_worker_info->probe_idx = probe_index;
        schedule_work( &clt_probe_worker_info->probe_work );
#endif
    }

    return 0;
}

/*!
 * \brief wifi off by wmt (remove client driver).
 *
 *
 * \param none.
 *
 * \retval 0:success, -1:not registered, -2:not probed, -3:has been off by wmt.
 */
INT32 hif_sdio_wifi_off(
    void
    )
{
    INT32 clt_index = -1;
    INT32 probe_index = -1;
    struct sdio_func *func = 0;
    int ret = -1;

    printk(KERN_INFO DRV_NAME "hif_sdio_wifi_off()\n");

#if 1
    //4 <1> If wifi client drv has not been probed, return error code
    /* MT6620 */
    if ( (probe_index = hif_sdio_find_probed_list_index_by_id_func(0x037A, 0x020A, 1)) >= 0 )
    {
        goto wifi_off_exist;
    }
    if ( (probe_index = hif_sdio_find_probed_list_index_by_id_func(0x037A, 0x020C, 2)) >= 0 )
    {
        goto wifi_off_exist;
    }

    /* MT6618 */
    if ( (probe_index = hif_sdio_find_probed_list_index_by_id_func(0x037A, 0x018A, 1)) >= 0 )
    {
        goto wifi_off_exist;
    }
    if ( (probe_index = hif_sdio_find_probed_list_index_by_id_func(0x037A, 0x018C, 2)) >= 0 )
    {
        goto wifi_off_exist;
    }
    else
    {
        //4 <2> If wifi client drv has not been probed, return error code
        /* client func has not been probed */
        return -2;
    }
#else
    //4 <1> If wifi client drv has not been registered, return error code
    /* MT6620 */
    if ( (clt_index = hif_sdio_find_clt_list_index(0x037A, 0x020A, 1)) >= 0 )
    {
        probe_index = hif_sdio_find_probed_list_index_by_clt_index( clt_index );
        if ( probe_index >= 0 )
        {
            goto wifi_off_exist;
        }
    }
    if ( (clt_index = hif_sdio_find_clt_list_index(0x037A, 0x020C, 2)) >= 0 )
    {
        probe_index = hif_sdio_find_probed_list_index_by_clt_index( clt_index );
        if ( probe_index >= 0 )
        {
            goto wifi_off_exist;
        }
    }

    /* MT6618 */
    if ( (clt_index = hif_sdio_find_clt_list_index(0x037A, 0x018A, 1)) >= 0 )
    {
        probe_index = hif_sdio_find_probed_list_index_by_clt_index( clt_index );
        if ( probe_index >= 0 )
        {
            goto wifi_off_exist;
        }
    }
    if ( (clt_index = hif_sdio_find_clt_list_index(0x037A, 0x018C, 2)) >= 0 )
    {
        probe_index = hif_sdio_find_probed_list_index_by_clt_index( clt_index );
        if ( probe_index >= 0 )
        {
            goto wifi_off_exist;
        }
    }
    else
    {
        return -1;
    }

    //4 <2> If wifi client drv has not been probed, return error code
    /* client func has not been probed */
    return -2;
#endif

wifi_off_exist:
    //4 <3> If wifi client drv has been off by wmt, return error code
    if ( g_hif_sdio_probed_func_list[probe_index].off_by_wmt )
    {
        return -3;
    }
    else
    {
        g_hif_sdio_probed_func_list[probe_index].off_by_wmt = MTK_WCN_BOOL_TRUE;
    }

    //4 <4> release irq for this function
    func = g_hif_sdio_probed_func_list[probe_index].func;
    sdio_claim_host(func);
    ret = sdio_release_irq(func);
    sdio_release_host(func);
    printk(KERN_INFO "sdio_release_irq ret=%d\n", ret);

    if ( (clt_index = g_hif_sdio_probed_func_list[probe_index].clt_idx) >= 0 )    /* the function has been registered */
    {
        //4 <5> Callback to client driver's remove() func
        g_hif_sdio_clt_drv_list[clt_index].sdio_cltinfo->hif_clt_remove( CLTCTX(func->device, func->num,\
                                                                            func->cur_blksize, probe_index) );
    }

    return 0;
}

/*!
 * \brief set mmc power up/off
 *
 * detailed descriptions
 *
 * \param: 1. ctx client's context variable, 2.power state: 1:power up, other:power off
 *
 * \retval 0:success, -1:fail
 */
INT32 mtk_wcn_hif_sdio_bus_set_power (
    MTK_WCN_HIF_SDIO_CLTCTX ctx,
    UINT32 pwrState
    )
{
    int probe_index = -1;    
    struct sdio_func *func = 0;
    
    printk(KERN_INFO DRV_NAME "turn Bus Power to: %d\n", pwrState);

    probe_index = CLTCTX_IDX(ctx);
    func = g_hif_sdio_probed_func_list[probe_index].func;

    if ( !func )
    {
        printk(KERN_WARNING DRV_NAME"%s Warnning: Cannot find sdio_func !!!\n", __FUNCTION__);
        return -1;
    }

    if ( 1 == pwrState )
    {
        sdio_claim_host( func );
        mmc_power_up_ext( func->card->host );
        sdio_release_host( func );
        printk(KERN_INFO DRV_NAME"%s SDIO BUS Power UP\n", __FUNCTION__);
    }
    else
    {
        sdio_claim_host( func );
        mmc_power_off_ext( func->card->host );
        sdio_release_host( func );
        printk(KERN_INFO DRV_NAME"%s SDIO BUS Power OFF\n", __FUNCTION__);
    }

    return 0;
}

module_init(hif_sdio_init);
module_exit(hif_sdio_exit);

EXPORT_SYMBOL(mtk_wcn_hif_sdio_client_reg);
EXPORT_SYMBOL(mtk_wcn_hif_sdio_client_unreg);
EXPORT_SYMBOL(mtk_wcn_hif_sdio_readb);
EXPORT_SYMBOL(mtk_wcn_hif_sdio_writeb);
EXPORT_SYMBOL(mtk_wcn_hif_sdio_readl);
EXPORT_SYMBOL(mtk_wcn_hif_sdio_writel);
EXPORT_SYMBOL(mtk_wcn_hif_sdio_read_buf);
EXPORT_SYMBOL(mtk_wcn_hif_sdio_write_buf);
EXPORT_SYMBOL(mtk_wcn_hif_sdio_set_drvdata);
EXPORT_SYMBOL(mtk_wcn_hif_sdio_get_drvdata);
EXPORT_SYMBOL(mtk_wcn_hif_sdio_wmt_control);
EXPORT_SYMBOL(mtk_wcn_hif_sdio_bus_set_power);

