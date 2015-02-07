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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/gl_kal.c#2 $
*/

/*! \file   gl_kal.c
    \brief  GLUE Layer will export the required procedures here for internal driver stack.

    This file contains all routines which are exported from GLUE Layer to internal
    driver stack.
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
** $Log: gl_kal.c $
 *
 * 07 10 2010 renbang.jiang
 * [ALPS00121785][Need Patch] [Volunteer Patch] use NVRAM to save Wi-Fi custom data 
 * .
 *
 * 06 13 2010 renbang.jiang
 * [ALPS00008206][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for fixing build warning 
 * .
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\50 2009-09-28 20:19:08 GMT mtk01090
**  Add private ioctl to carry OID structures. Restructure public/private ioctl interfaces to Linux kernel.
**  \main\maintrunk.MT5921\49 2009-08-18 22:56:44 GMT mtk01090
**  Add Linux SDIO (with mmc core) support.
**  Add Linux 2.6.21, 2.6.25, 2.6.26.
**  Fix compile warning in Linux.
**  \main\maintrunk.MT5921\48 2009-06-23 23:18:58 GMT mtk01090
**  Add build option BUILD_USE_EEPROM and compile option CFG_SUPPORT_EXT_CONFIG for NVRAM support
**  \main\maintrunk.MT5921\47 2008-11-19 11:55:43 GMT mtk01088
**  fixed some lint warning, and rename some variable with pre-fix to avoid the misunderstanding
**  \main\maintrunk.MT5921\46 2008-09-02 21:07:42 GMT mtk01461
**  Remove ASSERT(pvBuf) in kalIndicateStatusAndComplete(), this parameter can be NULL
**  \main\maintrunk.MT5921\45 2008-08-29 16:03:21 GMT mtk01088
**  remove non-used code for code review, add assert check
**  \main\maintrunk.MT5921\44 2008-08-21 00:32:49 GMT mtk01461
**  \main\maintrunk.MT5921\43 2008-05-30 20:27:02 GMT mtk01461
**  Rename KAL function
**  \main\maintrunk.MT5921\42 2008-05-30 15:47:29 GMT mtk01461
**  \main\maintrunk.MT5921\41 2008-05-30 15:13:04 GMT mtk01084
**  rename wlanoid
**  \main\maintrunk.MT5921\40 2008-05-29 14:15:14 GMT mtk01084
**  remove un-used KAL function
**  \main\maintrunk.MT5921\39 2008-05-03 15:17:30 GMT mtk01461
**  Move Query Media Status to GLUE
**  \main\maintrunk.MT5921\38 2008-04-24 11:59:44 GMT mtk01461
**  change awake queue threshold and remove code which mark #if 0
**  \main\maintrunk.MT5921\37 2008-04-17 23:06:35 GMT mtk01461
**  Add iwpriv support for AdHocMode setting
**  \main\maintrunk.MT5921\36 2008-04-08 15:38:56 GMT mtk01084
**  add KAL function to setting pattern search function enable/ disable
**  \main\maintrunk.MT5921\35 2008-04-01 23:53:13 GMT mtk01461
**  Add comment
**  \main\maintrunk.MT5921\34 2008-03-26 15:36:48 GMT mtk01461
**  Add update MAC Address for Linux
**  \main\maintrunk.MT5921\33 2008-03-18 11:49:34 GMT mtk01084
**  update function for initial value access
**  \main\maintrunk.MT5921\32 2008-03-18 10:25:22 GMT mtk01088
**  use kal update associate request at linux
**  \main\maintrunk.MT5921\31 2008-03-06 23:43:08 GMT mtk01385
**   1. add Query Registry Mac address function.
**  \main\maintrunk.MT5921\30 2008-02-26 09:47:57 GMT mtk01084
**  modify KAL set network address/ checksum offload part
**  \main\maintrunk.MT5921\29 2008-02-12 23:26:53 GMT mtk01461
**  Add debug option - Packet Order for Linux
**  \main\maintrunk.MT5921\28 2008-01-09 17:54:43 GMT mtk01084
**  modify the argument of kalQueryPacketInfo()
**  \main\maintrunk.MT5921\27 2007-12-24 16:02:03 GMT mtk01425
**  1. Revise csum offload
**  \main\maintrunk.MT5921\26 2007-11-30 17:03:36 GMT mtk01425
**  1. Fix bugs
**
**  \main\maintrunk.MT5921\25 2007-11-29 01:57:17 GMT mtk01461
**  Fix Windows RX multiple packet retain problem
**  \main\maintrunk.MT5921\24 2007-11-20 11:24:07 GMT mtk01088
**  <workaround> CR90, not doing the netif_carrier_off to let supplicant 1x pkt can be rcv at hardstattXmit
**  \main\maintrunk.MT5921\23 2007-11-09 16:36:44 GMT mtk01425
**  1. Modify for CSUM offloading with Tx Fragment
**  \main\maintrunk.MT5921\22 2007-11-07 18:37:39 GMT mtk01461
**  Add Tx Fragmentation Support
**  \main\maintrunk.MT5921\21 2007-11-06 19:34:06 GMT mtk01088
**  add the WPS code, indicate the mgmt frame to upper layer
**  \main\maintrunk.MT5921\20 2007-11-02 01:03:21 GMT mtk01461
**  Unify TX Path for Normal and IBSS Power Save + IBSS neighbor learning
**  \main\maintrunk.MT5921\19 2007-10-30 11:59:38 GMT MTK01425
**  1. Update wlanQueryInformation
**  \main\maintrunk.MT5921\18 2007-10-30 10:44:57 GMT mtk01425
**  1. Refine multicast list code
**  2. Refine TCP/IP csum offload code
**
** Revision 1.5  2007/07/17 13:01:18  MTK01088
** add associate req and rsp function
**
** Revision 1.4  2007/07/13 05:19:19  MTK01084
** provide timer set functions
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
#include "util.h"

#include "gl_wext.h"
#include "gl_wext_priv.h"

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
#if DBG
int allocatedMemSize = 0;
#endif

extern WIFI_CFG_DATA gPlatformCfg;

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
/*----------------------------------------------------------------------------*/
/*!
* \brief This function is provided by GLUE Layer for internal driver stack to acquire
*        OS SPIN_LOCK.
*
* \param[in] prGlueInfo     Pointer of GLUE Data Structure
* \param[in] rLockCategory  Specify which SPIN_LOCK
* \param[out] pu4Flags      Pointer of a variable for saving IRQ flags
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
kalAcquireSpinLock (
    IN P_GLUE_INFO_T                prGlueInfo,
    IN ENUM_SPIN_LOCK_CATEGORY_E    rLockCategory,
    OUT PUINT_32                    pu4Flags
    )
{
    UINT_32 u4Flags = 0;

    ASSERT(prGlueInfo);
    ASSERT(pu4Flags);

    if (rLockCategory < SPIN_LOCK_NUM) {

#if CFG_USE_SPIN_LOCK_BOTTOM_HALF
        spin_lock_bh(&prGlueInfo->rSpinLock[rLockCategory]);
#else /* !CFG_USE_SPIN_LOCK_BOTTOM_HALF */
        spin_lock_irqsave(&prGlueInfo->rSpinLock[rLockCategory], u4Flags);
#endif /* !CFG_USE_SPIN_LOCK_BOTTOM_HALF */

        *pu4Flags = u4Flags;
    }

    return;
} /* end of kalAcquireSpinLock() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function is provided by GLUE Layer for internal driver stack to release
*        OS SPIN_LOCK.
*
* \param[in] prGlueInfo     Pointer of GLUE Data Structure
* \param[in] rLockCategory  Specify which SPIN_LOCK
* \param[in] u4Flags        Saved IRQ flags
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
kalReleaseSpinLock (
    IN P_GLUE_INFO_T                prGlueInfo,
    IN ENUM_SPIN_LOCK_CATEGORY_E    rLockCategory,
    IN UINT_32                      u4Flags
    )
{
    ASSERT(prGlueInfo);

    if (rLockCategory < SPIN_LOCK_NUM) {

#if CFG_USE_SPIN_LOCK_BOTTOM_HALF
        spin_unlock_bh(&prGlueInfo->rSpinLock[rLockCategory]);
#else /* !CFG_USE_SPIN_LOCK_BOTTOM_HALF */
        spin_unlock_irqrestore(&prGlueInfo->rSpinLock[rLockCategory], u4Flags);
#endif /* !CFG_USE_SPIN_LOCK_BOTTOM_HALF */

    }

    return;
} /* end of kalReleaseSpinLock() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function is provided by GLUE Layer for internal driver stack to update
*        current MAC address.
*
* \param[in] prGlueInfo     Pointer of GLUE Data Structure
* \param[in] pucMacAddr     Pointer of current MAC address
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
kalUpdateMACAddress (
    IN P_GLUE_INFO_T prGlueInfo,
    IN PUINT_8 pucMacAddr
    )
{
    ASSERT(prGlueInfo);
    ASSERT(pucMacAddr);

    memcpy(prGlueInfo->prDevHandler->dev_addr, pucMacAddr, PARAM_MAC_ADDR_LEN);

    return;
}


#if CFG_TCP_IP_CHKSUM_OFFLOAD
/*----------------------------------------------------------------------------*/
/*!
* \brief To query the packet information for offload related parameters.
*
* \param[in] pvPacket Pointer to the packet descriptor.
* \param[in] pucFlag  Points to the offload related parameter.
*
* \return (none)
*
*/
/*----------------------------------------------------------------------------*/
VOID
kalQueryTxChksumOffloadParam (
    IN PVOID pvPacket,
    OUT PUINT_8 pucFlag
    )
{
    struct sk_buff *skb = (struct sk_buff *)pvPacket;
    UINT_8 ucFlag = 0;

    ASSERT(pvPacket);
    ASSERT(pucFlag);

#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 19)
    if (skb->ip_summed == CHECKSUM_HW)
#else
    if (skb->ip_summed == CHECKSUM_PARTIAL)
#endif
    {

#if DBG
        /* Kevin: do double check, we can remove this part in Normal Driver.
         * Because we register NIC feature with NETIF_F_IP_CSUM for MT5912B MAC, so
         * we'll process IP packet only.
         */
        if (skb->protocol != __constant_htons(ETH_P_IP)) {
            printk("Wrong skb->protocol( = %08x) for TX Checksum Offload.\n", skb->protocol);
        }
        else
#endif
        ucFlag |= (TX_CS_IP_GEN | TX_CS_TCP_UDP_GEN);
    }

    *pucFlag = ucFlag;

    return;
} /* kalQueryChksumOffloadParam */


//4 2007/10/8, mikewu, this is rewritten by Mike
/*----------------------------------------------------------------------------*/
/*!
* \brief To update the checksum offload status to the packet to be indicated to OS.
*
* \param[in] pvPacket Pointer to the packet descriptor.
* \param[in] pucFlag  Points to the offload related parameter.
*
* \return (none)
*
*/
/*----------------------------------------------------------------------------*/
VOID
kalUpdateRxCSUMOffloadParam (
    IN PVOID pvPacket,
    IN ENUM_CSUM_RESULT_T aeCSUM[]
    )
{
    struct sk_buff *skb = (struct sk_buff *)pvPacket;

    ASSERT(pvPacket);

    if ( (aeCSUM[CSUM_TYPE_IPV4] == CSUM_RES_SUCCESS || aeCSUM[CSUM_TYPE_IPV6] == CSUM_RES_SUCCESS)&&
        ( (aeCSUM[CSUM_TYPE_TCP] == CSUM_RES_SUCCESS) || (aeCSUM[CSUM_TYPE_UDP] == CSUM_RES_SUCCESS)) ) {
        skb->ip_summed = CHECKSUM_UNNECESSARY;
    }
    else {
        skb->ip_summed = CHECKSUM_NONE;
#if DBG
        if (aeCSUM[CSUM_TYPE_IPV4] == CSUM_RES_NONE && aeCSUM[CSUM_TYPE_IPV6] == CSUM_RES_NONE) {
            DBGLOG(RX, TRACE, ("RX: \"non-IPv4/IPv6\" Packet\n"));
        }
        else if (aeCSUM[CSUM_TYPE_IPV4] == CSUM_RES_FAILED) {
            DBGLOG(RX, TRACE, ("RX: \"bad IP Checksum\" Packet\n"));
        }
        else if (aeCSUM[CSUM_TYPE_TCP] == CSUM_RES_FAILED) {
            DBGLOG(RX, TRACE, ("RX: \"bad TCP Checksum\" Packet\n"));
        }
        else if (aeCSUM[CSUM_TYPE_UDP] == CSUM_RES_FAILED) {
            DBGLOG(RX, TRACE, ("RX: \"bad UDP Checksum\" Packet\n"));
        }
        else {

        }
#endif
    }

} /* kalUpdateRxCSUMOffloadParam */
#endif /* CFG_TCP_IP_CHKSUM_OFFLOAD */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function is called to free packet allocated from kalPacketAlloc.
*
* \param[in] prGlueInfo     Pointer of GLUE Data Structure
* \param[in] pvPacket       Pointer of the packet descriptor
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
kalPacketFree(
    IN P_GLUE_INFO_T   prGlueInfo,
    IN PVOID           pvPacket
    )
{
    dev_kfree_skb((struct sk_buff *)pvPacket);
}


/*----------------------------------------------------------------------------*/
/*!
* \brief Only handles driver own creating packet (coalescing buffer).
*
* \param prGlueInfo   Pointer of GLUE Data Structure
* \param u4Size       Pointer of Packet Handle
* \param ppucData     Status Code for OS upper layer
*
* \return NULL: Failed to allocate skb, Not NULL get skb
*/
/*----------------------------------------------------------------------------*/
PVOID
kalPacketAlloc (
    IN P_GLUE_INFO_T    prGlueInfo,
    IN UINT_32          u4Size,
    OUT PUINT_8         *ppucData
    )
{
    struct sk_buff  *prSkb = dev_alloc_skb(u4Size);

    if (prSkb) {
        *ppucData = (PUINT_8)(prSkb->data);
    }
#if DBG
{
    PUINT_32 pu4Head = (PUINT_32)&prSkb->cb[0];
    *pu4Head = (UINT_32)prSkb->head;
    DBGLOG(RX, TRACE, ("prSkb->head = %#lx, prSkb->cb = %#lx\n", (UINT_32)prSkb->head, *pu4Head));
}
#endif
    return (PVOID)prSkb;
}


#if CFG_USE_SW_ROOT_TIMER
/*----------------------------------------------------------------------------*/
/*!
* \brief Get the packet from swrfb and do something for retained packet.
*        There is nothing to do for Linux packet.
*
* \param[in] prGlueInfo Pointer to the Adapter structure.
* \param[in] prSWRfb The software RFB
* \param[in] pfgIsRetain Indicate that the packet of RFB is retained or not.
*
* \retval TRUE Success.
*
*/
/*----------------------------------------------------------------------------*/
VOID
kalOsTimerInitialize (
    IN P_GLUE_INFO_T prGlueInfo,
    IN PVOID         prTimerHandler
    )
{
    struct timer_list *prTimer = &prGlueInfo->rMasterTimer;

    /* Setup master timer. This master timer is the root timer for following
       management timers. */

    init_timer(prTimer);
    prTimer->function = (PFN_LINUX_TIMER_FUNC)prTimerHandler;
    prTimer->data = (unsigned long)(prGlueInfo->prAdapter);

    INITLOG(("Init SW master Timer -- OK\n"));
}


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to set the time to do the time out check.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
* \param[in] u4Interval Time out interval from current time.
*
* \retval TRUE Success.
*
*/
/*----------------------------------------------------------------------------*/
BOOL
kalSetTimer (
    IN P_GLUE_INFO_T prGlueInfo,
    IN OS_SYSTIME    rInterval
    )
{
    struct timer_list *prTimer = &prGlueInfo->rMasterTimer;

    del_timer(prTimer);

    prTimer->expires = jiffies + rInterval;

    add_timer(prTimer);

    return TRUE; /* success */
} /* end of kalSetTimer() */
#endif /* CFG_USE_SW_ROOT_TIMER */


/*----------------------------------------------------------------------------*/
/*!
* \brief Process the received packet for indicating to OS.
*
* \param[in] prGlueInfo     Pointer to the Adapter structure.
* \param[in] pvPacket       Pointer of the packet descriptor
* \param[in] pucPacketStart The starting address of the buffer of Rx packet.
* \param[in] u4PacketLen    The packet length.
* \param[in] pfgIsRetain    Is the packet to be retained.
* \param[in] aerCSUM        The result of TCP/ IP checksum offload.
*
* \retval WLAN_STATUS_SUCCESS.
* \retval WLAN_STATUS_FAILURE.
*
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
kalProcessRxPacket (
    IN P_GLUE_INFO_T      prGlueInfo,
    IN PVOID              pvPacket,
    IN PUINT_8            pucPacketStart,
    IN UINT_32            u4PacketLen,
    IN PBOOLEAN           pfgIsRetain,
    IN ENUM_CSUM_RESULT_T aerCSUM[]
    )
{
    WLAN_STATUS rStatus = WLAN_STATUS_SUCCESS;
    struct sk_buff *skb = (struct sk_buff *)pvPacket;

    skb->data = (unsigned char *)pucPacketStart;
    skb->tail = (unsigned char *)((UINT_32)pucPacketStart + u4PacketLen);
    skb->len = (unsigned int)u4PacketLen;

#if CFG_TCP_IP_CHKSUM_OFFLOAD
    kalUpdateRxCSUMOffloadParam(skb, aerCSUM);
#endif
    *pfgIsRetain = FALSE;

    return rStatus;
}


/*----------------------------------------------------------------------------*/
/*!
* \brief To indicate an array of received packets is available for higher
*        level protocol uses.
*
* \param[in] prGlueInfo Pointer to the Adapter structure.
* \param[in] apvPkts The packet array to be indicated
* \param[in] ucPktNum The number of packets to be indicated
*
* \retval TRUE Success.
*
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
kalRxIndicatePkts (
    IN P_GLUE_INFO_T    prGlueInfo,
    IN PVOID            apvPkts[],
    IN UINT_8           ucPktNum
    )
{
    UINT_8 ucIdx = 0;
    struct net_device *prNetDev = prGlueInfo->prDevHandler;
    struct sk_buff *prSkb = NULL;

    ASSERT(prGlueInfo);
    ASSERT(apvPkts);

    for(ucIdx = 0; ucIdx < ucPktNum; ucIdx++) {
        prSkb = apvPkts[ucIdx];
#if DBG
        do {
            PUINT_8 pu4Head = (PUINT_8)&prSkb->cb[0];
            UINT_32 u4HeadValue = 0;
            kalMemCopy(&u4HeadValue, pu4Head, sizeof(u4HeadValue));
            DBGLOG(RX, TRACE, ("prSkb->head = 0x%p, prSkb->cb = 0x%lx\n", pu4Head, u4HeadValue));
        } while (0);
#endif

        prNetDev->last_rx = jiffies;
        prSkb->protocol = eth_type_trans(prSkb, prNetDev);
        prSkb->dev = prNetDev;
        DBGLOG_MEM8(RX, TRACE, (PUINT_32)prSkb->data, prSkb->len);

        netif_rx(prSkb);
        wlanReturnPacket(prGlueInfo->prAdapter, NULL);
    }

    return WLAN_STATUS_SUCCESS;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief Called by driver to indicate event to upper layer, for example, the wpa
*        supplicant or wireless tools.
*
* \param[in] pvAdapter Pointer to the adapter descriptor.
* \param[in] eStatus Indicated status.
* \param[in] pvBuf Indicated message buffer.
* \param[in] u4BufLen Indicated message buffer size.
*
* \return (none)
*
*/
/*----------------------------------------------------------------------------*/
VOID
kalIndicateStatusAndComplete (
    IN P_GLUE_INFO_T    prGlueInfo,
    IN WLAN_STATUS      eStatus,
    IN PVOID            pvBuf,
    IN UINT_32          u4BufLen
    )
{
    UINT_32 bufLen;
    P_PARAM_STATUS_INDICATION_T pStatus = (P_PARAM_STATUS_INDICATION_T)pvBuf;
    P_PARAM_AUTH_EVENT_T pAuth = (P_PARAM_AUTH_EVENT_T)pStatus;
    P_PARAM_PMKID_CANDIDATE_LIST_T pPmkid =
        (P_PARAM_PMKID_CANDIDATE_LIST_T)(pStatus + 1);
    PARAM_MAC_ADDRESS arBssid;

    ASSERT(prGlueInfo);


    switch (eStatus) {
    case WLAN_STATUS_MEDIA_CONNECT:
        /* switch netif on */
        netif_carrier_on(prGlueInfo->prDevHandler);
		msleep(50);
        /* indicate assoc event */
        wlanQueryInformation(prGlueInfo->prAdapter,
            wlanoidQueryBssid,
            &arBssid[0],
            sizeof(arBssid),
            &bufLen);
        wext_indicate_wext_event(prGlueInfo, SIOCGIWAP, arBssid, bufLen);

        prGlueInfo->eParamMediaStateIndicated = PARAM_MEDIA_STATE_CONNECTED;

        do {
            /* print message on console */
            PARAM_SSID_T ssid;
            wlanQueryInformation(prGlueInfo->prAdapter,
                wlanoidQuerySsid,
                &ssid,
                sizeof(ssid),
                &bufLen);
            ssid.aucSsid[(ssid.u4SsidLen > PARAM_MAX_LEN_SSID) ?
                PARAM_MAX_LEN_SSID : ssid.u4SsidLen ] = '\0';
            printk(KERN_INFO "[wifi] %s netif_carrier_on [ssid:%s " MACSTR "]\n",
                prGlueInfo->prDevHandler->name,
                ssid.aucSsid,
                MAC2STR(arBssid));
        } while(0);
        break;

    case WLAN_STATUS_MEDIA_DISCONNECT:
        /* indicate disassoc event */
        wext_indicate_wext_event(prGlueInfo, SIOCGIWAP, NULL, 0);
        /* For CR 90 and CR99, While supplicant do reassociate, driver will do netif_carrier_off first,
           after associated success, at joinComplete(), do netif_carier_on,
           but for unknown reason, the supplicant 1x pkt will not called the driver
           hardStartXmit, for template workaround these bugs, add this compiling flag
        */
        /* switch netif off */
        netif_carrier_off(prGlueInfo->prDevHandler);

#if 1   /* CONSOLE_MESSAGE */
        printk(KERN_INFO "[wifi] %s netif_carrier_off\n", prGlueInfo->prDevHandler->name);
#endif

        prGlueInfo->eParamMediaStateIndicated = PARAM_MEDIA_STATE_DISCONNECTED;

        break;

    case WLAN_STATUS_SCAN_COMPLETE:
        /* indicate scan complete event */
        wext_indicate_wext_event(prGlueInfo, SIOCGIWSCAN, NULL, 0);
        break;

    case WLAN_STATUS_MSDU_OK:
        if (netif_running(prGlueInfo->prDevHandler)) {
            netif_wake_queue(prGlueInfo->prDevHandler);
        }
        break;

    case WLAN_STATUS_MEDIA_SPECIFIC_INDICATION:
        if (pStatus) {
            switch (pStatus->eStatusType) {
            case ENUM_STATUS_TYPE_AUTHENTICATION:
                /*
                printk(KERN_NOTICE "ENUM_STATUS_TYPE_AUTHENTICATION: L(%ld) [" MACSTR "] F:%lx\n",
                    pAuth->Request[0].Length,
                    MAC2STR(pAuth->Request[0].Bssid),
                    pAuth->Request[0].Flags);
                */
                /* indicate (UC/GC) MIC ERROR event only */
                if ((pAuth->arRequest[0].u4Flags ==
                        PARAM_AUTH_REQUEST_PAIRWISE_ERROR) ||
                        (pAuth->arRequest[0].u4Flags ==
                        PARAM_AUTH_REQUEST_GROUP_ERROR)) {
                    wext_indicate_wext_event(prGlueInfo,
                        IWEVMICHAELMICFAILURE,
                        (unsigned char *)&pAuth->arRequest[0],
                        pAuth->arRequest[0].u4Length);
                }
                break;

            case ENUM_STATUS_TYPE_CANDIDATE_LIST:
                /*
                printk(KERN_NOTICE "Param_StatusType_PMKID_CandidateList: Ver(%ld) Num(%ld)\n",
                    pPmkid->u2Version,
                    pPmkid->u4NumCandidates);
                if (pPmkid->u4NumCandidates > 0) {
                    printk(KERN_NOTICE "candidate[" MACSTR "] preAuth Flag:%lx\n",
                        MAC2STR(pPmkid->arCandidateList[0].rBSSID),
                        pPmkid->arCandidateList[0].fgFlags);
                }
                */
                {
                 UINT_32  i = 0;

                 P_PARAM_PMKID_CANDIDATE_T prPmkidCand = (P_PARAM_PMKID_CANDIDATE_T)&pPmkid->arCandidateList[0];

                 for (i=0; i<pPmkid->u4NumCandidates; i++) {
                    wext_indicate_wext_event(prGlueInfo,
                        IWEVPMKIDCAND,
                        (unsigned char *)&pPmkid->arCandidateList[i],
                        pPmkid->u4NumCandidates);
                    prPmkidCand += sizeof(PARAM_PMKID_CANDIDATE_T);
                }
                }
                break;

            default:
                /* case ENUM_STATUS_TYPE_MEDIA_STREAM_MODE */
                /*
                printk(KERN_NOTICE "unknown media specific indication type:%x\n",
                    pStatus->StatusType);
                */
                break;
            }
        }
        else {
            /*
            printk(KERN_WARNING "media specific indication buffer NULL\n");
            */
        }
        break;

    default:
        /*
        printk(KERN_WARNING "unknown indication:%lx\n", eStatus);
        */
        break;
    }
} /* kalIndicateStatusAndComplete */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to update the (re)association request
*        information to the structure used to query and set
*        OID_802_11_ASSOCIATION_INFORMATION.
*
* \param[in] prGlueInfo Pointer to the Glue structure.
* \param[in] pucFrameBody Pointer to the frame body of the last (Re)Association
*                         Request frame from the AP.
* \param[in] u4FrameBodyLen The length of the frame body of the last
*                           (Re)Association Request frame.
* \param[in] fgReassocRequest TRUE, if it is a Reassociation Request frame.
*
* \return (none)
*
*/
/*----------------------------------------------------------------------------*/
VOID
kalUpdateReAssocReqInfo (
    IN P_GLUE_INFO_T    prGlueInfo,
    IN PUINT_8          pucFrameBody,
    IN UINT_32          u4FrameBodyLen,
    IN BOOLEAN          fgReassocRequest
    )
{
    PUINT_8             cp;

    if (fgReassocRequest) {
        if (u4FrameBodyLen < 15) {
            /*
            printk(KERN_WARNING "frameBodyLen too short:%ld\n", frameBodyLen);
            */
            return;
        }
    }
    else {
        if (u4FrameBodyLen < 9) {
            /*
            printk(KERN_WARNING "frameBodyLen too short:%ld\n", frameBodyLen);
            */
            return;
        }
    }

    cp = pucFrameBody;

    if (fgReassocRequest) {
        /* Capability information field 2 */
        /* Listen interval field 2*/
        /* Current AP address 6 */
        cp += 10;
        u4FrameBodyLen -= 10;
    }
    else {
        /* Capability information field 2 */
        /* Listen interval field 2*/
        cp += 4;
        u4FrameBodyLen -= 4;
    }

    wext_indicate_wext_event(prGlueInfo, IWEVASSOCREQIE, cp, u4FrameBodyLen);
    return;
}



#if CFG_TX_FRAGMENT
/*----------------------------------------------------------------------------*/
/*!
* \brief This is to return the value of Ethernet type and the start address of
*        the Ethernet destination address by querying the packet information.
*
* \param[in] prGlueInfo      Pointer of GLUE Data Structure
* \param[in] pvPacket        Pointer of the packet descriptor
* \param[in] pu2EtherTypeLen the value of Ethernet type/ length field
* \param[in] pucEthDestAddr  the start address ofthe Ethernet destination address
*
* \return -
*/
/*----------------------------------------------------------------------------*/
BOOLEAN
kalQueryTxPacketHeader (
    IN P_GLUE_INFO_T prGlueInfo,
    IN PVOID         pvPacket,
    OUT PUINT_16     pu2EtherTypeLen,
    OUT PUINT_8      pucEthDestAddr
    )
{
    struct sk_buff *prSkb = (struct sk_buff *)pvPacket;

    *pu2EtherTypeLen = (UINT_16)ntohs(prSkb->protocol);
    memcpy(pucEthDestAddr, prSkb->data, PARAM_MAC_ADDR_LEN);

    return TRUE;
}
#endif /* CFG_TX_FRAGMENT */


#if CFG_TX_DBG_PACKET_ORDER
UINT_32 u4PacketIDOut[16] = {0};
#endif /* CFG_TX_DBG_PACKET_ORDER */


/*----------------------------------------------------------------------------*/
/*!
* \brief Notify OS with SendComplete event of the specific packet. Linux should
*        free packets here.
*
* \param[in] prGlueInfo     Pointer of GLUE Data Structure
* \param[in] pvPacket       Pointer of Packet Handle
* \param[in] status         Status Code for OS upper layer
*
* \return -
*/
/*----------------------------------------------------------------------------*/
VOID
kalSendCompleteAndAwakeQueue (
    IN P_GLUE_INFO_T prGlueInfo,
    IN PVOID pvPacket
    )
{
    ASSERT(pvPacket);
    ASSERT(prGlueInfo->u4TxPendingFrameNum);

#if CFG_TX_DBG_PACKET_ORDER
    {
        struct sk_buff *skb = (struct sk_buff *)pvPacket;
        UINT_8 ucTID = skb->cb[4];
        UINT_32 u4IDIn = *(PUINT_32)&skb->cb[12];

        ASSERT(ucTID <= 15);

        if (u4IDIn == u4PacketIDOut[ucTID]) {
            u4PacketIDOut[ucTID]++;
        }
        else {
            ASSERT(0);
        }
    }
#endif /* CFG_TX_DBG_PACKET_ORDER */

    dev_kfree_skb((struct sk_buff *)pvPacket);

    prGlueInfo->u4TxPendingFrameNum--;
    if (prGlueInfo->u4TxPendingFrameNum < CFG_TX_STOP_NETIF_QUEUE_THRESHOLD) {
        netif_wake_queue(prGlueInfo->prDevHandler);
    }

    return;
}


/*----------------------------------------------------------------------------*/
/*!
* \brief Copy Mac Address setting from registry. It's All Zeros in Linux.
*
* \param[in] prAdapter Pointer to the Adapter structure
*
* \param[out] paucMacAddr Pointer to the Mac Address buffer
*
* \retval WLAN_STATUS_SUCCESS
*
* \note
*/
/*----------------------------------------------------------------------------*/
VOID
kalQueryRegistryMacAddr (
    IN  P_GLUE_INFO_T   prGlueInfo,
    OUT PUINT_8        paucMacAddr
    )
{
    UINT_8 aucZeroMac[MAC_ADDR_LEN] = {0,0,0,0,0,0}
    DEBUGFUNC("kalQueryRegistryMacAddr");

    ASSERT(prGlueInfo);
    ASSERT(paucMacAddr);

    kalMemCopy((PVOID) paucMacAddr, (PVOID)aucZeroMac, MAC_ADDR_LEN);

    return;
} /* end of kalQueryRegistryMacAddr() */

#if CFG_SUPPORT_EXT_CONFIG
/*----------------------------------------------------------------------------*/
/*!
* \brief Read external configuration, ex. NVRAM or file
*
* \param[in] prGlueInfo     Pointer of GLUE Data Structure
*
* \return none
*/
/*----------------------------------------------------------------------------*/
UINT_32
kalReadExtCfg (
    IN P_GLUE_INFO_T prGlueInfo
    )
{
#if DBG
    int i;
#endif
    ASSERT(prGlueInfo);

    printk("[MT5921][kalReadExtCfg]NVRAM size %lu\n", gPlatformCfg.u4Cfglen);

    if( gPlatformCfg.u4Cfglen < sizeof(prGlueInfo->au2ExtCfg) ||
		sizeof(gPlatformCfg.rWifiNvram) < sizeof(prGlueInfo->au2ExtCfg) ) {
		prGlueInfo->u4ExtCfgLength = 0;
		return 0;
    }

    kalMemCopy( prGlueInfo->au2ExtCfg, (char *)&gPlatformCfg.rWifiNvram, sizeof(prGlueInfo->au2ExtCfg) );
#if DBG
    for( i = 0; i< sizeof(prGlueInfo->au2ExtCfg)/2; i++){
        printk("[MT5921][kalReadExtCfg]nvram cfg data[%d] 0x%x\n", i, prGlueInfo->au2ExtCfg[i]);
    }
#endif

    prGlueInfo->u4ExtCfgLength = sizeof(prGlueInfo->au2ExtCfg);

    return prGlueInfo->u4ExtCfgLength;
}

#endif

