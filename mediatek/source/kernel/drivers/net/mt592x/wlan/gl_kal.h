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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/gl_kal.h#2 $
*/

/*! \file   gl_kal.h
    \brief  Declaration of KAL functions - kal*() which is provided by GLUE Layer.

    Any definitions in this file will be shared among GLUE Layer and internal Driver Stack.
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
** $Log: gl_kal.h $
 *
 * 07 29 2010 renbang.jiang
 * [ALPS00122638] [Power] Popup kernel panic exception when copy files from SD card to other SD card.
 * .
 *
 * 07 29 2010 renbang.jiang
 * [ALPS00122638] [Power] Popup kernel panic exception when copy files from SD card to other SD card.
 * .
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\41 2009-09-28 20:19:23 GMT mtk01090
**  Add private ioctl to carry OID structures. Restructure public/private ioctl interfaces to Linux kernel.
**  \main\maintrunk.MT5921\40 2009-08-18 22:57:09 GMT mtk01090
**  Add Linux SDIO (with mmc core) support.
**  Add Linux 2.6.21, 2.6.25, 2.6.26.
**  Fix compile warning in Linux.
**  \main\maintrunk.MT5921\39 2009-06-23 23:19:15 GMT mtk01090
**  Add build option BUILD_USE_EEPROM and compile option CFG_SUPPORT_EXT_CONFIG for NVRAM support
**  \main\maintrunk.MT5921\38 2009-02-09 14:03:17 GMT mtk01090
**  Add KAL function kalDevSetPowerState(). It is not implemented yet. Only add an empty macro.
**
**  \main\maintrunk.MT5921\37 2009-01-22 13:05:59 GMT mtk01088
**  new defeine to got 1x value at packet reserved field
**  \main\maintrunk.MT5921\36 2008-12-08 16:15:02 GMT mtk01461
**  Add kalQueryValidBufferLength() macro
**  \main\maintrunk.MT5921\35 2008-11-13 20:33:15 GMT mtk01104
**  Remove lint warning
**  \main\maintrunk.MT5921\34 2008-10-22 11:05:52 GMT mtk01461
**  Remove unused macro
**  \main\maintrunk.MT5921\33 2008-10-16 15:48:17 GMT mtk01461
**  Update driver to fix lint warning
**  \main\maintrunk.MT5921\32 2008-09-02 11:50:51 GMT mtk01461
**  SPIN_LOCK_SDIO_DDK_TX_QUE
**  \main\maintrunk.MT5921\31 2008-08-29 15:58:30 GMT mtk01088
**  remove non-used function for code refine
**  \main\maintrunk.MT5921\30 2008-08-21 00:33:29 GMT mtk01461
**  Update for Driver Review
**  \main\maintrunk.MT5921\29 2008-06-19 13:29:14 GMT mtk01425
**  1. Add declaration of SPIN_LOCK_SDIO_DDK_TX_QUE and SPIN_LOCK_SDIO_DDK_RX_QUE
**  \main\maintrunk.MT5921\28 2008-05-30 20:27:34 GMT mtk01461
**  Rename KAL function
**  \main\maintrunk.MT5921\27 2008-05-30 14:42:05 GMT mtk01461
**  Remove WMM Assoc Flag in KAL
**  \main\maintrunk.MT5921\26 2008-05-29 14:15:18 GMT mtk01084
**  remove un-used function
**  \main\maintrunk.MT5921\25 2008-04-23 14:02:20 GMT mtk01084
**  modify KAL port access function prototype
**  \main\maintrunk.MT5921\24 2008-04-17 23:06:41 GMT mtk01461
**  Add iwpriv support for AdHocMode setting
**  \main\maintrunk.MT5921\23 2008-04-08 15:38:50 GMT mtk01084
**  add KAL function to setting pattern search function enable/ disable
**  \main\maintrunk.MT5921\22 2008-03-26 15:34:48 GMT mtk01461
**  Add update MAC address func
**  \main\maintrunk.MT5921\21 2008-03-18 15:56:15 GMT mtk01084
**  update ENUM_NIC_INITIAL_PARAM_E
**  \main\maintrunk.MT5921\20 2008-03-18 11:49:28 GMT mtk01084
**  update function for initial value access
**  \main\maintrunk.MT5921\19 2008-03-18 10:21:31 GMT mtk01088
**  use kal update associate request at linux
**  \main\maintrunk.MT5921\18 2008-03-14 18:03:41 GMT mtk01084
**  refine register and port access function
**  \main\maintrunk.MT5921\17 2008-03-11 14:51:02 GMT mtk01461
**  Add copy_to(from)_user macro
**  \main\maintrunk.MT5921\16 2008-03-06 23:42:21 GMT mtk01385
**  1. add Query Registry Mac address function.
**  \main\maintrunk.MT5921\15 2008-02-26 09:48:04 GMT mtk01084
**  modify KAL set network address/ checksum offload part
**  \main\maintrunk.MT5921\14 2008-01-09 17:54:58 GMT mtk01084
**  Modify the argument of kalQueryPacketInfo
**  \main\maintrunk.MT5921\13 2007-11-29 02:05:20 GMT mtk01461
**  Fix Windows RX multiple packet retain problem
**  \main\maintrunk.MT5921\12 2007-11-26 19:43:45 GMT mtk01461
**  Add OS_TIMESTAMP macro
**
**  \main\maintrunk.MT5921\11 2007-11-09 16:36:15 GMT mtk01425
**  1. Modify for CSUM offloading with Tx Fragment
**  \main\maintrunk.MT5921\10 2007-11-07 18:38:37 GMT mtk01461
**  Add Tx Fragmentation Support
**  \main\maintrunk.MT5921\9 2007-11-06 19:36:50 GMT mtk01088
**  add the WPS related code
**  \main\maintrunk.MT5921\8 2007-11-02 01:03:57 GMT mtk01461
**  Unify TX Path for Normal and IBSS Power Save + IBSS neighbor learning
** Revision 1.4  2007/07/05 07:25:33  MTK01461
** Add Linux initial code, modify doc, add 11BB, RF init code
**
** Revision 1.3  2007/06/27 02:18:50  MTK01461
** Update SCAN_FSM, Initial(Can Load Module), Proc(Can do Reg R/W), TX API
**
** Revision 1.2  2007/06/25 06:16:23  MTK01461
** Update illustrations, gl_init.c, gl_kal.c, gl_kal.h, gl_os.h and RX API
**
*/


#ifndef _GL_KAL_H
#define _GL_KAL_H


/*******************************************************************************
*                         C O M P I L E R   F L A G S
********************************************************************************
*/

/*******************************************************************************
*                    E X T E R N A L   R E F E R E N C E S
********************************************************************************
*/
#include "config.h"
#include "gl_typedef.h"
#include "gl_os.h"
#include "wlan_lib.h"

#if DBG
extern int allocatedMemSize;
#endif

/*******************************************************************************
*                              C O N S T A N T S
********************************************************************************
*/

/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/
typedef enum _ENUM_SPIN_LOCK_CATEGORY_E {
    SPIN_LOCK_FSM = 0,
    SPIN_LOCK_TX,
    SPIN_LOCK_IO_REQ,
    SPIN_LOCK_INT,
    SPIN_LOCK_NUM
} ENUM_SPIN_LOCK_CATEGORY_E;

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
/*----------------------------------------------------------------------------*/
/* Macros of SPIN LOCK operations for using in Driver Layer                   */
/*----------------------------------------------------------------------------*/
#define KAL_SPIN_LOCK_DECLARATION()             UINT_32 __u4Flags

#define KAL_ACQUIRE_SPIN_LOCK(_prAdapter, _rLockCategory)   \
            kalAcquireSpinLock(((P_ADAPTER_T)_prAdapter)->prGlueInfo, _rLockCategory, &__u4Flags)

#define KAL_RELEASE_SPIN_LOCK(_prAdapter, _rLockCategory)   \
            kalReleaseSpinLock(((P_ADAPTER_T)_prAdapter)->prGlueInfo, _rLockCategory, __u4Flags)

/*----------------------------------------------------------------------------*/
/* Macros for accessing Reserved Fields of native packet                      */
/*----------------------------------------------------------------------------*/
#define KAL_GET_PKT_QUEUE_ENTRY(_p)             GLUE_GET_PKT_QUEUE_ENTRY(_p)
#define KAL_GET_PKT_DESCRIPTOR(_prQueueEntry)   GLUE_GET_PKT_DESCRIPTOR(_prQueueEntry)
#define KAL_GET_PKT_TID(_p)                     GLUE_GET_PKT_TID(_p)
#define KAL_GET_PKT_IS1X(_p)                    GLUE_GET_PKT_IS1X(_p)
#define KAL_GET_PKT_HEADER_LEN(_p)              GLUE_GET_PKT_HEADER_LEN(_p)
#define KAL_GET_PKT_PAYLOAD_LEN(_p)             GLUE_GET_PKT_PAYLOAD_LEN(_p)
#define KAL_GET_PKT_ARRIVAL_TIME(_p)            GLUE_GET_PKT_ARRIVAL_TIME(_p)

#define kalUpdateReAssocRspInfo(prGlueInfo, pucFrameBody, u4FrameBodyLen)

/*----------------------------------------------------------------------------*/
/*!
* \brief Cache memory allocation
*
* \param[in] u4Size Required memory size.
*
* \return Pointer to allocated memory
*         or NULL
*/
/*----------------------------------------------------------------------------*/
#if DBG
#define kalMemAlloc(u4Size) ({    \
    void *pvAddr = kmalloc(u4Size, GFP_NOWAIT);   \
    if (pvAddr) {   \
        allocatedMemSize += u4Size;   \
        printk(KERN_INFO DRV_NAME "0x%p(%ld) allocated (%s:%s)\n", \
            pvAddr, (UINT_32)u4Size, __FILE__, __FUNCTION__);  \
    }   \
    pvAddr; \
    })
#else
#define kalMemAlloc(u4Size)                         kmalloc(u4Size, GFP_NOWAIT) //kmalloc(u4Size, GFP_ATOMIC)
#endif

/*----------------------------------------------------------------------------*/
/*!
* \brief Free allocated cache memory
*
* \param[in] pvAddr Required memory size.
* \param[in] u4Size Allocated memory size.
*
* \return -
*/
/*----------------------------------------------------------------------------*/
#if DBG
#define kalMemFree(pvAddr, u4Size)  \
    {   \
        if (pvAddr) {   \
            allocatedMemSize -= u4Size; \
            printk(KERN_INFO DRV_NAME "0x%p(%ld) freed (%s:%s)\n", \
                pvAddr, (UINT_32)u4Size, __FILE__, __FUNCTION__);  \
        }   \
        kfree(pvAddr);  \
    }
#else
#define kalMemFree(pvAddr, u4Size)                  kfree(pvAddr)
#endif

#define kalUdelay(u4USec)                           udelay(u4USec)

#define kalMdelay(u4MSec)                           mdelay(u4MSec)

/* Copy memory from user space to kernel space */
#define kalMemCopyFromUser(_pvTo, _pvFrom, _u4N)    copy_from_user(_pvTo, _pvFrom, _u4N)

/* Copy memory from kernel space to user space */
#define kalMemCopyToUser(_pvTo, _pvFrom, _u4N)      copy_to_user(_pvTo, _pvFrom, _u4N)

/* Copy memory block with specific size */
#define kalMemCopy(pvDst, pvSrc, u4Size)            memcpy(pvDst, pvSrc, u4Size)

/* Set memory block with specific pattern */
#define kalMemSet(pvAddr, ucPattern, u4Size)        memset(pvAddr, ucPattern, u4Size)

/* Compare two memory block with specific length.
 * Return zero if they are the same.
 */
#define kalMemCmp(pvAddr1, pvAddr2, u4Size)         memcmp(pvAddr1, pvAddr2, u4Size)

/* Zero specific memory block */
#define kalMemZero(pvAddr, u4Size)                  memset(pvAddr, 0, u4Size)

/* defined for wince sdio driver only */
#if defined(_HIF_SDIO)
#define kalDevSetPowerState(prGlueInfo, ePowerMode) glSetPowerState(prGlueInfo, ePowerMode)
#else
#define kalDevSetPowerState(prGlueInfo, ePowerMode)
#endif

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
#define kalSendComplete(prGlueInfo, pvPacket, status)   \
            kalSendCompleteAndAwakeQueue(prGlueInfo, pvPacket)


/*----------------------------------------------------------------------------*/
/*!
* \brief This function is used to locate the starting address of incoming ethernet
*        frame for skb.
*
* \param[in] prGlueInfo     Pointer of GLUE Data Structure
* \param[in] pvPacket       Pointer of Packet Handle
*
* \return starting address of ethernet frame buffer.
*/
/*----------------------------------------------------------------------------*/
#define kalQueryBufferPointer(prGlueInfo, pvPacket)     \
            ((PUINT_8)((struct sk_buff *)pvPacket)->data)


/*----------------------------------------------------------------------------*/
/*!
* \brief This function is used to query the length of valid buffer which is accessible during
*         port read/write.
*
* \param[in] prGlueInfo     Pointer of GLUE Data Structure
* \param[in] pvPacket       Pointer of Packet Handle
*
* \return starting address of ethernet frame buffer.
*/
/*----------------------------------------------------------------------------*/
#define kalQueryValidBufferLength(prGlueInfo, pvPacket)     \
            ((UINT_32)((struct sk_buff *)pvPacket)->end -  \
             (UINT_32)((struct sk_buff *)pvPacket)->data)

/*----------------------------------------------------------------------------*/
/*!
* \brief This function is used to copy the entire frame from skb to the destination
*        address in the input parameter.
*
* \param[in] prGlueInfo     Pointer of GLUE Data Structure
* \param[in] pvPacket       Pointer of Packet Handle
* \param[in] pucDestBuffer  Destination Address
*
* \return -
*/
/*----------------------------------------------------------------------------*/
#define kalCopyFrame(prGlueInfo, pvPacket, pucDestBuffer)   \
            {struct sk_buff *skb = (struct sk_buff *)pvPacket; \
             memcpy(pucDestBuffer, skb->data, skb->len);}


/*----------------------------------------------------------------------------*/
/*!
* \brief This function returns the current OS_SYSTIME that have elapsed since
*        elapsed since the system was booted. The unit of OS_SYSTIME is OS
*        dependent.
*
* \param -
*
* \return The LSB 32-bits of the system uptime
*/
/*----------------------------------------------------------------------------*/
#define kalGetTimeTick()                            jiffies

#define kalPrint                                    printk

#define kalBreakPoint() \
    do { \
        BUG(); \
        panic("Oops"); \
    } while(0)

#define PRINTF_ARG(...)                             __VA_ARGS__
#define SPRINTF(buf, arg)                           {buf += sprintf((char *)(buf), PRINTF_ARG arg);}

/*******************************************************************************
*                  F U N C T I O N   D E C L A R A T I O N S
********************************************************************************
*/
/*----------------------------------------------------------------------------*/
/* Routines in gl_kal.c                                                       */
/*----------------------------------------------------------------------------*/
VOID
kalAcquireSpinLock(
    IN P_GLUE_INFO_T                prGlueInfo,
    IN ENUM_SPIN_LOCK_CATEGORY_E    rLockCategory,
    OUT PUINT_32                    pu4Flags
    );

VOID
kalReleaseSpinLock(
    IN P_GLUE_INFO_T                prGlueInfo,
    IN ENUM_SPIN_LOCK_CATEGORY_E    rLockCategory,
    IN UINT_32                      u4Flags
    );

VOID
kalUpdateMACAddress(
    IN P_GLUE_INFO_T    prGlueInfo,
    IN PUINT_8          pucMacAddr
    );

VOID
kalPacketFree(
    IN  P_GLUE_INFO_T    prGlueInfo,
    IN PVOID             pvPacket
    );

PVOID
kalPacketAlloc(
    IN P_GLUE_INFO_T     prGlueInfo,
    IN UINT_32           u4Size,
    OUT PUINT_8          *ppucData
    );

VOID
kalOsTimerInitialize(
    IN P_GLUE_INFO_T     prGlueInfo,
    IN PVOID             prTimerHandler
    );

BOOL
kalSetTimer(
    IN P_GLUE_INFO_T      prGlueInfo,
    IN OS_SYSTIME         rInterval
    );

WLAN_STATUS
kalProcessRxPacket(
    IN P_GLUE_INFO_T      prGlueInfo,
    IN PVOID              pvPacket,
    IN PUINT_8            pucPacketStart,
    IN UINT_32            u4PacketLen,
    IN PBOOLEAN           pfgIsRetain,
    IN ENUM_CSUM_RESULT_T aeCSUM[]
    );

WLAN_STATUS
kalRxIndicatePkts(
    IN P_GLUE_INFO_T prGlueInfo,
    IN PVOID         apvPkts[],
    IN UINT_8        ucPktNum
    );

VOID
kalIndicateStatusAndComplete(
    IN P_GLUE_INFO_T prGlueInfo,
    IN WLAN_STATUS   eStatus,
    IN PVOID         pvBuf,
    IN UINT_32       u4BufLen
    );

VOID
kalUpdateReAssocReqInfo(
    IN P_GLUE_INFO_T prGlueInfo,
    IN PUINT_8       pucFrameBody,
    IN UINT_32       u4FrameBodyLen,
    IN BOOLEAN       fgReassocRequest
    );

#if CFG_TX_FRAGMENT
BOOLEAN
kalQueryTxPacketHeader(
    IN P_GLUE_INFO_T prGlueInfo,
    IN PVOID         pvPacket,
    OUT PUINT_16     pu2EtherTypeLen,
    OUT PUINT_8      pucEthDestAddr
    );
#endif /* CFG_TX_FRAGMENT */

VOID
kalSendCompleteAndAwakeQueue(
    IN P_GLUE_INFO_T  prGlueInfo,
    IN PVOID          pvPacket
    );

#if CFG_TCP_IP_CHKSUM_OFFLOAD
VOID
kalQueryTxChksumOffloadParam(
    IN  PVOID     pvPacket,
    OUT PUINT_8   pucFlag);

VOID
kalUpdateRxCSUMOffloadParam(
    IN PVOID               pvPacket,
    IN ENUM_CSUM_RESULT_T  eCSUM[]
    );
#endif /* CFG_TCP_IP_CHKSUM_OFFLOAD */


/*----------------------------------------------------------------------------*/
/* Routines in interface - ehpi/sdio.c                                                       */
/*----------------------------------------------------------------------------*/
BOOL
kalDevRegRead(
    IN  P_GLUE_INFO_T  prGlueInfo,
    IN  UINT_32        u4Register,
    OUT PUINT_32       pu4Value
    );

BOOL
kalDevRegWrite(
    P_GLUE_INFO_T  prGlueInfo,
    IN UINT_32     u4Register,
    IN UINT_32     u4Value
    );

BOOL
kalDevPortRead(
    IN  P_GLUE_INFO_T   prGlueInfo,
    IN  UINT_16         u2Port,
    IN  UINT_16         u2Len,
    OUT PUINT_8         pucBuf,
    IN  UINT_16         u2ValidOutBufSize
    );

BOOL
kalDevPortWrite(
    P_GLUE_INFO_T  prGlueInfo,
    IN UINT_16     u2Port,
    IN UINT_16     u2Len,
    IN PUINT_8     pucBuf,
    IN UINT_16     u2ValidInBufSize
    );

void 
kalDevEnableIrq();

void 
kalDevDisableIrq();

    #if CFG_SUPPORT_EXT_CONFIG
UINT_32
kalReadExtCfg (
    IN P_GLUE_INFO_T prGlueInfo
    );
    #endif

/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/

#endif /* _GL_KAL_H */

