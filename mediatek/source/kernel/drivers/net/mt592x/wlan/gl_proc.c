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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/gl_proc.c#2 $
*/

/*! \file   "gl_proc.c"
    \brief  This file defines the interface which can interact with users in /proc fs.

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
** $Log: gl_proc.c $
 *
 * 06 10 2010 jim.zhang
 * [ALPS00008051]change mt592x to UNGPL version 
 * .
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\21 2009-10-08 10:33:16 GMT mtk01090
**  Avoid accessing private data of net_device directly. Replace with netdev_priv(). Add more checking for input parameters and pointers.
**  \main\maintrunk.MT5921\20 2009-08-18 22:56:47 GMT mtk01090
**  Add Linux SDIO (with mmc core) support.
**  Add Linux 2.6.21, 2.6.25, 2.6.26.
**  Fix compile warning in Linux.
**  \main\maintrunk.MT5921\19 2008-09-02 21:08:37 GMT mtk01461
**  Fix the compile error of SPRINTF()
**  \main\maintrunk.MT5921\18 2008-08-10 18:48:28 GMT mtk01461
**  Update for Driver Review
**  \main\maintrunk.MT5921\17 2008-08-04 16:52:01 GMT mtk01461
**  Add proc dbg print message of DOMAIN_INDEX level
**  \main\maintrunk.MT5921\16 2008-07-10 00:45:16 GMT mtk01461
**  Remove the check of MCR offset, we may use the MCR address which is not align to DW boundary or proprietary usage.
**  \main\maintrunk.MT5921\15 2008-06-03 20:49:44 GMT mtk01461
**  \main\maintrunk.MT5921\14 2008-06-02 22:56:00 GMT mtk01461
**  Rename some functions for linux proc
**  \main\maintrunk.MT5921\13 2008-06-02 20:23:18 GMT mtk01461
**  Revise PROC mcr read / write for supporting TELNET
**  \main\maintrunk.MT5921\12 2008-03-28 10:40:25 GMT mtk01461
**  Remove temporary set desired rate in linux proc
**  \main\maintrunk.MT5921\11 2008-01-07 15:07:29 GMT mtk01461
**  Add User Update Desired Rate Set for QA in Linux
**  \main\maintrunk.MT5921\10 2007-12-11 00:11:14 GMT mtk01461
**  Fix SPIN_LOCK protection
**  \main\maintrunk.MT5921\9 2007-12-04 18:07:57 GMT mtk01461
**  Add additional debug category to proc
**  \main\maintrunk.MT5921\8 2007-11-02 01:03:23 GMT mtk01461
**  Unify TX Path for Normal and IBSS Power Save + IBSS neighbor learning
**  \main\maintrunk.MT5921\7 2007-10-25 18:08:14 GMT mtk01461
**  Add VOIP SCAN Support  & Refine Roaming
** Revision 1.3  2007/07/05 07:25:33  MTK01461
** Add Linux initial code, modify doc, add 11BB, RF init code
**
** Revision 1.2  2007/06/27 02:18:51  MTK01461
** Update SCAN_FSM, Initial(Can Load Module), Proc(Can do Reg R/W), TX API
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
#include "gl_kal.h"

#include "wlan_lib.h"
#include "debug.h"


/*******************************************************************************
*                              C O N S T A N T S
********************************************************************************
*/
#define PROC_MCR_ACCESS                         "mcr"
#define PROC_DRV_STATUS                         "status"
#define PROC_RX_STATISTICS                      "rx_statistics"
#define PROC_TX_STATISTICS                      "tx_statistics"
#define PROC_DBG_LEVEL                          "dbg_level"
#define PROC_DBG_OID							"dbg_oid"

#define PROC_MCR_ACCESS_MAX_USER_INPUT_LEN      20
#define PROC_RX_STATISTICS_MAX_USER_INPUT_LEN   10
#define PROC_TX_STATISTICS_MAX_USER_INPUT_LEN   10
#define PROC_DBG_LEVEL_MAX_USER_INPUT_LEN       20
#define PROC_DBG_LEVEL_MAX_DISPLAY_STR_LEN      30
#define PROC_OID_MAX_USER_INPUT_LEN 			50
#define PROC_OID_MAX_MAX_DISPLAY_LEN 			50


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
static UINT_32 u4McrOffset = 0;

/*******************************************************************************
*                                 M A C R O S
********************************************************************************
*/

/*******************************************************************************
*                   F U N C T I O N   D E C L A R A T I O N S
********************************************************************************
*/
extern struct proc_dir_entry * proc_net_mkdir_wrapper(
    struct net *net, 
    const char *name,
    struct proc_dir_entry *parent);
	
extern struct proc_dir_entry *create_proc_entry_wrapper(
    const char *name,
    mode_t mode, 
    struct proc_dir_entry *parent);
	
extern struct proc_dir_entry *create_proc_read_entry_wrapper(
    const char *name,
    mode_t mode, 
    struct proc_dir_entry *base, 
    read_proc_t *read_proc, 
    void * data) ;
	
extern void remove_proc_entry_wrapper(
    const char *name, 
    struct proc_dir_entry *parent);
/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/
/*----------------------------------------------------------------------------*/
/*!
* \brief The PROC function for reading MCR register to User Space, the offset of
*        the MCR is specified in u4McrOffset.
*
* \param[in] page       Buffer provided by kernel.
* \param[in out] start  Start Address to read(3 methods).
* \param[in] off        Offset.
* \param[in] count      Allowable number to read.
* \param[out] eof       End of File indication.
* \param[in] data       Pointer to the private data structure.
*
* \return number of characters print to the buffer from User Space.
*/
/*----------------------------------------------------------------------------*/
static int
procMCRRead (
    char *page,
    char **start,
    off_t off,
    int count,
    int *eof,
    void *data
    )
{
    P_GLUE_INFO_T prGlueInfo = NULL;
    PARAM_CUSTOM_MCR_RW_STRUC_T rMcrInfo;
    UINT_32 u4BufLen;
    char *p = page;
    UINT_32 u4Count;

    GLUE_SPIN_LOCK_DECLARATION();

    // Kevin: Apply PROC read method 1.
    if (off != 0) {
        return 0; // To indicate end of file.
    }

    ASSERT(page && eof && data);
    if (!data || !eof || !data) {
        printk(KERN_WARNING DRV_NAME"%s Invalid input data\n", __FUNCTION__);
        return -EINVAL;
    }

    prGlueInfo = (P_GLUE_INFO_T)netdev_priv((struct net_device *)data);
    if (!prGlueInfo) {
        printk(KERN_WARNING DRV_NAME"%s No glue info\n", __FUNCTION__);
        return -EINVAL;
    }

#if !defined(_HIF_SDIO)
    GLUE_ACQUIRE_SPIN_LOCK(prGlueInfo, SPIN_LOCK_FSM);
#endif

    rMcrInfo.u4McrOffset = u4McrOffset;

    //printk("Read MCR 0x%lx: 0x%lx\n",
        //rMcrInfo.u4McrOffset, rMcrInfo.mcrData);

#if defined(_HIF_SDIO)
   sdio_io_ctrl(prGlueInfo,
                     wlanoidQueryMcrRead,
                     (PVOID)&rMcrInfo,
                     sizeof(rMcrInfo),
                     TRUE,
                     TRUE,
                     &u4BufLen);
#else
    wlanQueryInformation(prGlueInfo->prAdapter,
                         wlanoidQueryMcrRead,
                         (PVOID)&rMcrInfo,
                         sizeof(rMcrInfo),
                         &u4BufLen);
#endif

#if !defined(_HIF_SDIO)
    GLUE_RELEASE_SPIN_LOCK(prGlueInfo, SPIN_LOCK_FSM);
#endif

    SPRINTF(p, ("MCR (%#04lxh): %#08lx\n",
        rMcrInfo.u4McrOffset, rMcrInfo.u4McrData));

    u4Count = (UINT_32)(p - page);

    *eof = 1;

    return (int)u4Count;

} /* end of procMCRRead() */


/*----------------------------------------------------------------------------*/
/*!
* \brief The PROC function for writing MCR register to HW or update u4McrOffset
*        for reading MCR later.
*
* \param[in] file   pointer to file.
* \param[in] buffer Buffer from user space.
* \param[in] count  Number of characters to write
* \param[in] data   Pointer to the private data structure.
*
* \return number of characters write from User Space.
*/
/*----------------------------------------------------------------------------*/
static int
procMCRWrite (
    struct file *file,
    const char *buffer,
    unsigned long count,
    void *data
    )
{
    P_GLUE_INFO_T prGlueInfo = NULL;
    char acBuf[PROC_MCR_ACCESS_MAX_USER_INPUT_LEN + 1]; // + 1 for "\0"
    UINT_32 u4CopySize;
    PARAM_CUSTOM_MCR_RW_STRUC_T rMcrInfo;
    UINT_32 u4BufLen;

    GLUE_SPIN_LOCK_DECLARATION();

    ASSERT(data);
    if (!data) {
        printk(KERN_WARNING DRV_NAME"%s Invalid input data\n", __FUNCTION__);
        return -EINVAL;
    }

    prGlueInfo = (P_GLUE_INFO_T)netdev_priv((struct net_device *)data);
    if (!prGlueInfo) {
        printk(KERN_WARNING DRV_NAME"%s No glue info\n", __FUNCTION__);
        return -EINVAL;
    }

    u4CopySize = (count < PROC_RX_STATISTICS_MAX_USER_INPUT_LEN)
        ? count : PROC_RX_STATISTICS_MAX_USER_INPUT_LEN;
    if (copy_from_user(acBuf, buffer, u4CopySize)) {
        printk(KERN_WARNING DRV_NAME"%s copy_from_user() fail\n", __FUNCTION__);
        return -EFAULT;
    }
    acBuf[u4CopySize] = '\0';

    switch (sscanf(acBuf, "0x%lx 0x%lx",
                   &rMcrInfo.u4McrOffset, &rMcrInfo.u4McrData)) {
    case 2:
        /* NOTE: Sometimes we want to test if bus will still be ok, after accessing
         * the MCR which is not align to DW boundary.
         */
        //if (IS_ALIGN_4(rMcrInfo.u4McrOffset))
        {
            u4McrOffset = rMcrInfo.u4McrOffset;

            //printk("Write 0x%lx to MCR 0x%04lx\n",
                //rMcrInfo.u4McrOffset, rMcrInfo.u4McrData);

#if defined(_HIF_SDIO)
            sdio_io_ctrl(prGlueInfo,
                               wlanoidSetMcrWrite,
                               (PVOID)&rMcrInfo,
                               sizeof(rMcrInfo),
                               FALSE,
                               TRUE,
                               &u4BufLen);
#else
            GLUE_ACQUIRE_SPIN_LOCK(prGlueInfo, SPIN_LOCK_FSM);

            wlanSetInformation(prGlueInfo->prAdapter,
                               wlanoidSetMcrWrite,
                               (PVOID)&rMcrInfo,
                               sizeof(rMcrInfo),
                               &u4BufLen);

            GLUE_RELEASE_SPIN_LOCK(prGlueInfo, SPIN_LOCK_FSM);
#endif
        }
        break;

    case 1:
        //if (IS_ALIGN_4(rMcrInfo.u4McrOffset))
        {
            u4McrOffset = rMcrInfo.u4McrOffset;
        }
        break;

    default:
        break;
    }

    return count;

} /* end of procMCRWrite() */


/*----------------------------------------------------------------------------*/
/*!
* \brief The PROC function for reading Driver Status to User Space.
*
* \param[in] page       Buffer provided by kernel.
* \param[in out] start  Start Address to read(3 methods).
* \param[in] off        Offset.
* \param[in] count      Allowable number to read.
* \param[out] eof       End of File indication.
* \param[in] data       Pointer to the private data structure.
*
* \return number of characters print to the buffer from User Space.
*/
/*----------------------------------------------------------------------------*/
static int
procDrvStatusRead (
    char *page,
    char **start,
    off_t off,
    int count,
    int *eof,
    void *data
    )
{
    P_GLUE_INFO_T prGlueInfo = NULL;
    char *p = page;
    UINT_32 u4Count;

    GLUE_SPIN_LOCK_DECLARATION();

    // Kevin: Apply PROC read method 1.
    if (off != 0) {
        return 0; // To indicate end of file.
    }

    ASSERT(page || eof || data);
    if (!data || !eof || !data) {
        printk(KERN_WARNING DRV_NAME"%s Invalid input data\n", __FUNCTION__);
        return -EINVAL;
    }

    prGlueInfo = (P_GLUE_INFO_T)netdev_priv((struct net_device *)data);
    if (!prGlueInfo) {
        printk(KERN_WARNING DRV_NAME"%s No glue info\n", __FUNCTION__);
        return -EINVAL;
    }

    SPRINTF(p, ("GLUE LAYER STATUS:"));
    SPRINTF(p, ("\n=================="));

    SPRINTF(p, ("\n* Number of Pending Frames: %ld\n",
        prGlueInfo->u4TxPendingFrameNum));

    GLUE_ACQUIRE_SPIN_LOCK(prGlueInfo, SPIN_LOCK_FSM);

    wlanoidQueryDrvStatusForLinuxProc(prGlueInfo->prAdapter, p, &u4Count);

    GLUE_RELEASE_SPIN_LOCK(prGlueInfo, SPIN_LOCK_FSM);

    u4Count += (UINT_32)(p - page);

    *eof = 1;

    return (int)u4Count;

} /* end of procDrvStatusRead() */


/*----------------------------------------------------------------------------*/
/*!
* \brief The PROC function for reading Driver RX Statistic Counters to User Space.
*
* \param[in] page       Buffer provided by kernel.
* \param[in out] start  Start Address to read(3 methods).
* \param[in] off        Offset.
* \param[in] count      Allowable number to read.
* \param[out] eof       End of File indication.
* \param[in] data       Pointer to the private data structure.
*
* \return number of characters print to the buffer from User Space.
*/
/*----------------------------------------------------------------------------*/
static int
procRxStatisticsRead (
    char *page,
    char **start,
    off_t off,
    int count,
    int *eof,
    void *data
    )
{
    P_GLUE_INFO_T prGlueInfo = NULL;
    char *p = page;
    UINT_32 u4Count;

    GLUE_SPIN_LOCK_DECLARATION();

    // Kevin: Apply PROC read method 1.
    if (off != 0) {
        return 0; // To indicate end of file.
    }

    ASSERT(page && eof && data);
    if (!data || !eof || !data) {
        printk(KERN_WARNING DRV_NAME"%s Invalid input data\n", __FUNCTION__);
        return -EINVAL;
    }

    prGlueInfo = (P_GLUE_INFO_T)netdev_priv((struct net_device *)data);
    if (!prGlueInfo) {
        printk(KERN_WARNING DRV_NAME"%s No glue info\n", __FUNCTION__);
        return -EINVAL;
    }

    SPRINTF(p, ("RX STATISTICS (Write 1 to clear):"));
    SPRINTF(p, ("\n=================================\n"));

    GLUE_ACQUIRE_SPIN_LOCK(prGlueInfo, SPIN_LOCK_FSM);

    wlanoidQueryRxStatisticsForLinuxProc(prGlueInfo->prAdapter, p, &u4Count);

    GLUE_RELEASE_SPIN_LOCK(prGlueInfo, SPIN_LOCK_FSM);

    u4Count += (UINT_32)(p - page);

    *eof = 1;

    return (int)u4Count;

} /* end of procRxStatisticsRead() */


/*----------------------------------------------------------------------------*/
/*!
* \brief The PROC function for reset Driver RX Statistic Counters.
*
* \param[in] file   pointer to file.
* \param[in] buffer Buffer from user space.
* \param[in] count  Number of characters to write
* \param[in] data   Pointer to the private data structure.
*
* \return number of characters write from User Space.
*/
/*----------------------------------------------------------------------------*/
static int
procRxStatisticsWrite (
    struct file *file,
    const char *buffer,
    unsigned long count,
    void *data
    )
{
    P_GLUE_INFO_T prGlueInfo = NULL;
    char acBuf[PROC_RX_STATISTICS_MAX_USER_INPUT_LEN + 1]; // + 1 for "\0"
    UINT_32 u4CopySize;
    UINT_32 u4ClearCounter;

    GLUE_SPIN_LOCK_DECLARATION();

    ASSERT(data);
    if (!data) {
        printk(KERN_WARNING DRV_NAME"%s Invalid input data\n", __FUNCTION__);
        return -EINVAL;
    }

    prGlueInfo = (P_GLUE_INFO_T)netdev_priv((struct net_device *)data);
    if (!prGlueInfo) {
        printk(KERN_WARNING DRV_NAME"%s No glue info\n", __FUNCTION__);
        return -EINVAL;
    }

    u4CopySize = (count < PROC_RX_STATISTICS_MAX_USER_INPUT_LEN)
        ? count : PROC_RX_STATISTICS_MAX_USER_INPUT_LEN;
    if (copy_from_user(acBuf, buffer, u4CopySize)) {
        printk(KERN_WARNING DRV_NAME"%s copy_from_user() fail\n", __FUNCTION__);
        return -EFAULT;
    }
    acBuf[u4CopySize] = '\0';

    if (sscanf(acBuf, "%ld", &u4ClearCounter) == 1) {
        if (u4ClearCounter == 1) {
            GLUE_ACQUIRE_SPIN_LOCK(prGlueInfo, SPIN_LOCK_FSM);

            wlanoidSetRxStatisticsForLinuxProc(prGlueInfo->prAdapter);

            GLUE_RELEASE_SPIN_LOCK(prGlueInfo, SPIN_LOCK_FSM);
        }
    }

    return count;

} /* end of procRxStatisticsWrite() */


/*----------------------------------------------------------------------------*/
/*!
* \brief The PROC function for reading Driver TX Statistic Counters to User Space.
*
* \param[in] page       Buffer provided by kernel.
* \param[in out] start  Start Address to read(3 methods).
* \param[in] off        Offset.
* \param[in] count      Allowable number to read.
* \param[out] eof       End of File indication.
* \param[in] data       Pointer to the private data structure.
*
* \return number of characters print to the buffer from User Space.
*/
/*----------------------------------------------------------------------------*/
static int
procTxStatisticsRead (
    char *page,
    char **start,
    off_t off,
    int count,
    int *eof,
    void *data
    )
{
    P_GLUE_INFO_T prGlueInfo = NULL;
    char *p = page;
    UINT_32 u4Count;

    GLUE_SPIN_LOCK_DECLARATION();

    // Kevin: Apply PROC read method 1.
    if (off != 0) {
        return 0; // To indicate end of file.
    }

    ASSERT(page && eof && data);
    if (!data || !eof || !data) {
        printk(KERN_WARNING DRV_NAME"%s Invalid input data\n", __FUNCTION__);
        return -EINVAL;
    }

    prGlueInfo = (P_GLUE_INFO_T)netdev_priv((struct net_device *)data);
    if (!prGlueInfo) {
        printk(KERN_WARNING DRV_NAME"%s No glue info\n", __FUNCTION__);
        return -EINVAL;
    }

    SPRINTF(p, ("TX STATISTICS (Write 1 to clear):"));
    SPRINTF(p, ("\n=================================\n"));

    GLUE_ACQUIRE_SPIN_LOCK(prGlueInfo, SPIN_LOCK_FSM);

    wlanoidQueryTxStatisticsForLinuxProc(prGlueInfo->prAdapter, p, &u4Count);

    GLUE_RELEASE_SPIN_LOCK(prGlueInfo, SPIN_LOCK_FSM);

    u4Count += (UINT_32)(p - page);

    *eof = 1;

    return (int)u4Count;

} /* end of procTxStatisticsRead() */


/*----------------------------------------------------------------------------*/
/*!
* \brief The PROC function for reset Driver TX Statistic Counters.
*
* \param[in] file   pointer to file.
* \param[in] buffer Buffer from user space.
* \param[in] count  Number of characters to write
* \param[in] data   Pointer to the private data structure.
*
* \return number of characters write from User Space.
*/
/*----------------------------------------------------------------------------*/
static int
procTxStatisticsWrite (
    struct file *file,
    const char *buffer,
    unsigned long count,
    void *data
    )
{
    P_GLUE_INFO_T prGlueInfo = NULL;
    char acBuf[PROC_RX_STATISTICS_MAX_USER_INPUT_LEN + 1]; // + 1 for "\0"
    UINT_32 u4CopySize;
    UINT_32 u4ClearCounter;

    GLUE_SPIN_LOCK_DECLARATION();

    ASSERT(data);
    if (!data) {
        printk(KERN_WARNING DRV_NAME"%s Invalid input data\n", __FUNCTION__);
        return -EINVAL;
    }

    prGlueInfo = (P_GLUE_INFO_T)netdev_priv((struct net_device *)data);
    if (!prGlueInfo) {
        printk(KERN_WARNING DRV_NAME"%s No glue info\n", __FUNCTION__);
        return -EINVAL;
    }

    u4CopySize = (count < PROC_RX_STATISTICS_MAX_USER_INPUT_LEN)
        ? count : PROC_RX_STATISTICS_MAX_USER_INPUT_LEN;
    if (copy_from_user(acBuf, buffer, u4CopySize)) {
        printk(KERN_WARNING DRV_NAME"%s copy_from_user() fail\n", __FUNCTION__);
        return -EFAULT;
    }
    acBuf[u4CopySize] = '\0';

    if (sscanf(acBuf, "%ld", &u4ClearCounter) == 1) {
        if (u4ClearCounter == 1) {
            GLUE_ACQUIRE_SPIN_LOCK(prGlueInfo, SPIN_LOCK_FSM);

            wlanoidSetTxStatisticsForLinuxProc(prGlueInfo->prAdapter);

            GLUE_RELEASE_SPIN_LOCK(prGlueInfo, SPIN_LOCK_FSM);
        }
    }

    return count;

} /* end of procTxStatisticsWrite() */


#if DBG
/*----------------------------------------------------------------------------*/
/*!
* \brief The PROC function for displaying current Debug Level.
*
* \param[in] page       Buffer provided by kernel.
* \param[in out] start  Start Address to read(3 methods).
* \param[in] off        Offset.
* \param[in] count      Allowable number to read.
* \param[out] eof       End of File indication.
* \param[in] data       Pointer to the private data structure.
*
* \return number of characters print to the buffer from User Space.
*/
/*----------------------------------------------------------------------------*/
static int
procDbgLevelRead (
    char *page,
    char **start,
    off_t off,
    int count,
    int *eof,
    void *data
    )
{
    char *p = page;
    int i;

    UINT_8 aucDbModuleName[][PROC_DBG_LEVEL_MAX_DISPLAY_STR_LEN] = {
        "DBG_INIT_IDX",
        "DBG_ARB_IDX",
        "DBG_TEST_IDX",
        "DBG_SCAN_IDX",
        "DBG_JOIN_IDX",
        "DBG_ROAMING_IDX",
        "DBG_NIC_IDX",
        "DBG_PHY_IDX",
        "DBG_HAL_IDX",
        "DBG_INTR_IDX",
        "DBG_TX_IDX",
        "DBG_RX_IDX",
        "DBG_REQ_IDX",
        "DBG_MGT_IDX",
        "DBG_RSN_IDX",
        "DBG_LP_IDX",
        "DBG_RFTEST_IDX",
        "DBG_LP_IOT_IDX",
        "DBG_RCPI_MEASURE_IDX",
        "DBG_DOMAIN_IDX",

        "DBG_WH_IDX",
        "DBG_KEVIN_IDX",
        "DBG_MIKE_IDX",
        "DBG_KENT_IDX",
        "DBG_GEORGE_IDX",
        "DBG_CMC_IDX"
        };


    // Kevin: Apply PROC read method 1.
    if (off != 0) {
        return 0; // To indicate end of file.
    }

    for (i = 0; i < (sizeof(aucDbModuleName)/PROC_DBG_LEVEL_MAX_DISPLAY_STR_LEN); i++) {
        SPRINTF(p, ("%c %-15s(0x%02x): %02x\n",
            ((i == u4DebugModule) ? '*' : ' '),
            &aucDbModuleName[i][0],
            i,
            aucDebugModule[i]));
    }

    *eof = 1;
    return (int)(p - page);
}


/*----------------------------------------------------------------------------*/
/*!
* \brief The PROC function for adjusting Debug Level to turn on/off debugging message.
*
* \param[in] file   pointer to file.
* \param[in] buffer Buffer from user space.
* \param[in] count  Number of characters to write
* \param[in] data   Pointer to the private data structure.
*
* \return number of characters write from User Space.
*/
/*----------------------------------------------------------------------------*/
static int
procDbgLevelWrite (
    struct file *file,
    const char *buffer,
    unsigned long count,
    void *data
    )
{
    char acBuf[PROC_DBG_LEVEL_MAX_USER_INPUT_LEN + 1]; // + 1 for "\0"
    UINT_32 u4CopySize;
    UINT_32 u4NewDbgModule, u4NewDbgLevel;


    u4CopySize = (count < (sizeof(acBuf) - 1)) ? count : (sizeof(acBuf) - 1);
    if (copy_from_user(acBuf, buffer, u4CopySize)) {
        printk(KERN_INFO DRV_NAME"procDbgLevelWrite copy_from_user() fail\n");
    }

    acBuf[u4CopySize] = '\0';

    if (sscanf(acBuf, "0x%lx 0x%lx", &u4NewDbgModule, &u4NewDbgLevel) == 2) {
        if (u4NewDbgModule < DBG_MODULE_NUM) {
            u4DebugModule = u4NewDbgModule;
            u4NewDbgLevel &= DBG_CLASS_MASK;
            aucDebugModule[u4DebugModule] = (UINT_8)u4NewDbgLevel;
        }
    }

    return count;
}
#endif /* DBG */

/*----------------------------------------------------------------------------*/
/*!
* \brief The PROC function for debuging the wlanoid function.
*
* \param[in] file   pointer to file.
* \param[in] buffer Buffer from user space.
* \param[in] count  Number of characters to write
* \param[in] data   Pointer to the private data structure.
*
* \return number of characters write from User Space.
*/
/*----------------------------------------------------------------------------*/
static int
procOidWrite(
	struct file *file,
	const char *buffer,
	unsigned long count,
	void *data
	)
{
	P_GLUE_INFO_T prGlueInfo = NULL;	
	char acBuf[PROC_OID_MAX_USER_INPUT_LEN + 1];//+1 for "\0"
	UINT_32 u4CopySize;
	UINT_8 u4Ip[4];
	UINT_32 u4BufLen;
	int i = 0;

	GLUE_SPIN_LOCK_DECLARATION();

	printk(KERN_INFO DRV_NAME "%s ++\n", __FUNCTION__);
	for(i = 0; i < count; i++)
		printk("%c", buffer[i]);
	printk(KERN_INFO DRV_NAME "\n");

	ASSERT(data);
	if(!data){
		printk(KERN_WARNING DRV_NAME"%s Invalid input data\n", __FUNCTION__);
		return -EINVAL;
	}

	prGlueInfo = (P_GLUE_INFO_T)netdev_priv((struct net_device *)data);
	
	if(!prGlueInfo){
		printk(KERN_WARNING DRV_NAME"%s NO glue info\n", __FUNCTION__);
		return -EINVAL;
	}
	
	u4CopySize = (count < (sizeof(acBuf) - 1))? count : (sizeof(acBuf) - 1);
    
	if(copy_from_user(acBuf, buffer, u4CopySize)){
		printk(KERN_INFO DRV_NAME"procOidWrite copy_from_user() failed\n");
	}

	acBuf[u4CopySize] = "\0";
	
	printk(KERN_INFO DRV_NAME "%s: %s\n", __FUNCTION__, acBuf);

#if 0
	if(4 == sscanf(acBuf, "%d.%d.%d.%d", u4Ip, u4Ip + 1, u4Ip + 2, u4Ip + 3)){

#if defined(_HIF_SDIO)
					sdio_io_ctrl(prGlueInfo,
								 wlanoidSetIpAddress,
								 (PVOID)&u4Ip,
								  sizeof(u4Ip),
								  FALSE,
								  TRUE,
								  &u4BufLen);
#else
					GLUE_ACQUIRE_SPIN_LOCK(prGlueInfo, SPIN_LOCK_FSM);
		
					wlanSetInformation(prGlueInfo->prAdapter,
									   wlanoidSetIpAddress,
									   (PVOID)&u4Ip,
									   sizeof(u4Ip),
									   &u4BufLen);
		
					GLUE_RELEASE_SPIN_LOCK(prGlueInfo, SPIN_LOCK_FSM);
#endif
	}
#endif


#if defined(_HIF_SDIO)
						sdio_io_ctrl(prGlueInfo,
									 wlanoidOidTest,
									 (PVOID)acBuf,
									  count,
									  FALSE,
									  TRUE,
									  &u4BufLen);
#else
						GLUE_ACQUIRE_SPIN_LOCK(prGlueInfo, SPIN_LOCK_FSM);
			
						wlanSetInformation(prGlueInfo->prAdapter,
										   wlanoidOidTest,
										   (PVOID)acBuf,
										   count,
										   &u4BufLen);
			
						GLUE_RELEASE_SPIN_LOCK(prGlueInfo, SPIN_LOCK_FSM);
#endif

	return count;	

}

/*----------------------------------------------------------------------------*/
/*!
* \brief This function create a PROC fs in linux /proc/net subdirectory.
*
* \param[in] prDev      Pointer to the struct net_device.
* \param[in] pucDevName Pointer to the name of net_device.
*
* \return N/A
*/
/*----------------------------------------------------------------------------*/
INT_32
procInitProcfs (
    struct net_device *prDev,
    char *pucDevName
    )
{
    P_GLUE_INFO_T prGlueInfo = NULL;
    struct proc_dir_entry *prEntry;

    struct proc_dir_entry *prKernelProcNet = init_net.proc_net;

    ASSERT(prDev);
    if (!prDev) {
        printk(KERN_WARNING DRV_NAME"%s Invalid input data\n", __FUNCTION__);
        return -EINVAL;
    }

    if (!prKernelProcNet) {
        printk("init proc fs fail: proc_net == NULL\n");
        return -ENOENT;
    }

    prGlueInfo = (P_GLUE_INFO_T)netdev_priv(prDev);
    if (!prGlueInfo) {
        printk(KERN_WARNING DRV_NAME"%s No glue info\n", __FUNCTION__);
        return -EINVAL;
    }

    /*
    /proc/net/wlan0
               |-- mcr              (PROC_MCR_ACCESS)
               |-- status           (PROC_DRV_STATUS)
               |-- rx_statistics    (PROC_RX_STATISTICS)
               |-- tx_statistics    (PROC_TX_STATISTICS)
               |-- dbg_level        (PROC_DBG_LEVEL)
               |-- (end)
     */

    /*
    * Directory: Root (/proc/net/wlan0)
    */

    prGlueInfo->pProcRoot = proc_mkdir(pucDevName, prKernelProcNet);

    if (prGlueInfo->pProcRoot == NULL) {
        return -ENOENT;
    }

    /* File Root/mcr (RW) */
    prEntry = create_proc_entry(PROC_MCR_ACCESS, 0, prGlueInfo->pProcRoot);
    if (prEntry) {
        prEntry->read_proc = procMCRRead;
        prEntry->write_proc = procMCRWrite;
        prEntry->data = (void *)prDev;
    }

    /* File Root/status (RW) */
    prEntry = create_proc_read_entry(PROC_DRV_STATUS, 0, prGlueInfo->pProcRoot,
                                     procDrvStatusRead, prDev);

    /* File Root/rx_statistics (RW) */
    prEntry = create_proc_entry(PROC_RX_STATISTICS, 0, prGlueInfo->pProcRoot);
    if (prEntry) {
        prEntry->read_proc = procRxStatisticsRead;
        prEntry->write_proc = procRxStatisticsWrite;
        prEntry->data = (void *)prDev;
    }

    /* File Root/tx_statistics (RW) */
    prEntry = create_proc_entry(PROC_TX_STATISTICS, 0, prGlueInfo->pProcRoot);
    if (prEntry) {
        prEntry->read_proc = procTxStatisticsRead;
        prEntry->write_proc = procTxStatisticsWrite;
        prEntry->data = (void *)prDev;
    }

#if DBG
    /* File Root/dbg_level (RW) */
    prEntry = create_proc_entry(PROC_DBG_LEVEL, 0644, prGlueInfo->pProcRoot);
    if (prEntry) {
        prEntry->read_proc = procDbgLevelRead;
        prEntry->write_proc = procDbgLevelWrite;
    }
#endif /* DBG */

	prEntry = create_proc_entry(PROC_DBG_OID, 0, prGlueInfo->pProcRoot);
	if(prEntry) {
		prEntry->write_proc = procOidWrite;
		prEntry->data = (void *)prDev;
	}

    return 0;

} /* end of procInitProcfs() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function clean up a PROC fs created by procInitProcfs().
*
* \param[in] prDev      Pointer to the struct net_device.
* \param[in] pucDevName Pointer to the name of net_device.
*
* \return N/A
*/
/*----------------------------------------------------------------------------*/
INT_32
procRemoveProcfs (
    struct net_device *prDev,
    char *pucDevName
    )
{
    P_GLUE_INFO_T prGlueInfo = NULL;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 24)
    struct proc_dir_entry *prKernelProcNet = init_net.proc_net;
#else
    struct proc_dir_entry *prKernelProcNet = proc_net;
#endif

    ASSERT(prDev);

    if (!prDev) {
        printk(KERN_WARNING DRV_NAME"%s Invalid input data\n", __FUNCTION__);
        return -EINVAL;
    }

    if (!prKernelProcNet) {
        printk(KERN_ALERT "remove proc fs fail: proc_net == NULL\n");
        return -ENOENT;
    }

    prGlueInfo = (P_GLUE_INFO_T)netdev_priv(prDev);
    if (!prGlueInfo || !prGlueInfo->pProcRoot) {
        printk(KERN_ALERT "The procfs root is NULL\n");
        return -ENOENT;
    }

#if DBG
    remove_proc_entry(PROC_DBG_LEVEL,       prGlueInfo->pProcRoot);
#endif /* DBG */
    remove_proc_entry(PROC_TX_STATISTICS,   prGlueInfo->pProcRoot);
    remove_proc_entry(PROC_RX_STATISTICS,   prGlueInfo->pProcRoot);
    remove_proc_entry(PROC_DRV_STATUS,      prGlueInfo->pProcRoot);
    remove_proc_entry(PROC_MCR_ACCESS,      prGlueInfo->pProcRoot);
    remove_proc_entry(PROC_DBG_OID, 	    prGlueInfo->pProcRoot);   

    /* remove root directory (proc/net/wlan0) */
    remove_proc_entry(pucDevName, prKernelProcNet);

    return 0;

} /* end of procRemoveProcfs() */


