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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/gl_os.h#2 $
*/

/*! \file   gl_os.h
    \brief  List the external reference to OS for GLUE Layer.

    In this file we define the data structure - GLUE_INFO_T to store those objects
    we acquired from OS - e.g. TIMER, SPINLOCK, NET DEVICE ... . And all the
    external reference (header file, extern func() ..) to OS for GLUE Layer should
    also list down here.
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
** $Log: gl_os.h $
 *
 * 07 29 2010 renbang.jiang
 * [ALPS00122638] [Power] Popup kernel panic exception when copy files from SD card to other SD card.
 * .
 *
 * 07 10 2010 renbang.jiang
 * [ALPS00121785][Need Patch] [Volunteer Patch] use NVRAM to save Wi-Fi custom data 
 * .
 *
 * 06 18 2010 renbang.jiang
 * [ALPS00008357][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for support Rx/Tx indication led 
 * .
 *
 * 06 13 2010 renbang.jiang
 * [ALPS00008206][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for fixing build warning 
 * .
 *
 * 06 02 2010 george.kuo
 * [ALPS00005405][Certification][Wi-Fi] Device auto reboot while start to connect AP(qa2_wireless_test) for the first time 
 * Fix CR5405 for the kernel panic problem
 *
 * 05 28 2010 george.kuo
 * [ALPS00001866][Certification][WIFI] WMM function Fail . 
 * [WIFI][WMM]Enlarge GL threshold for passing B mode WMM internal contention test items.
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\29 2009-10-08 10:33:33 GMT mtk01090
**  Avoid accessing private data of net_device directly. Replace with netdev_priv(). Add more checking for input parameters and pointers.
**  \main\maintrunk.MT5921\28 2009-09-28 20:19:26 GMT mtk01090
**  Add private ioctl to carry OID structures. Restructure public/private ioctl interfaces to Linux kernel.
**  \main\maintrunk.MT5921\27 2009-08-18 22:57:12 GMT mtk01090
**  Add Linux SDIO (with mmc core) support.
**  Add Linux 2.6.21, 2.6.25, 2.6.26.
**  Fix compile warning in Linux.
**  \main\maintrunk.MT5921\26 2009-07-06 21:42:25 GMT mtk01088
**  fixed the compiling error at linux
**  \main\maintrunk.MT5921\25 2009-07-06 20:51:46 GMT mtk01088
**  adding the wapi 1x ether type define
**  \main\maintrunk.MT5921\24 2009-06-23 23:19:18 GMT mtk01090
**  Add build option BUILD_USE_EEPROM and compile option CFG_SUPPORT_EXT_CONFIG for NVRAM support
**  \main\maintrunk.MT5921\23 2009-02-07 15:05:06 GMT mtk01088
**  add the privacy flag to ingo driver the supplicant selected ap's security
**  \main\maintrunk.MT5921\22 2009-02-05 15:34:09 GMT mtk01088
**  fixed the compiling error for using bits marco for only one parameter
**  \main\maintrunk.MT5921\21 2009-01-22 13:02:13 GMT mtk01088
**  data frame is or not 802.1x value share with tid, using the same reserved byte, provide the function to set and get
**  \main\maintrunk.MT5921\20 2008-10-24 12:04:16 GMT mtk01088
**  move the config.h from precomp.h to here for lint check
**  \main\maintrunk.MT5921\19 2008-09-22 23:19:02 GMT mtk01461
**  Update driver for code review
**  \main\maintrunk.MT5921\18 2008-09-05 17:25:13 GMT mtk01461
**  Update Driver for Code Review
**  \main\maintrunk.MT5921\17 2008-08-01 13:32:47 GMT mtk01084
**  Prevent redundent driver assertion in driver logic when BUS is detached
**  \main\maintrunk.MT5921\16 2008-05-30 14:41:43 GMT mtk01461
**  Remove WMM Assoc Flag in KAL
**  \main\maintrunk.MT5921\15 2008-05-29 14:16:25 GMT mtk01084
**  remoev un-used variable
**  \main\maintrunk.MT5921\14 2008-05-03 15:17:14 GMT mtk01461
**  Add Media Status variable in Glue Layer
**  \main\maintrunk.MT5921\13 2008-04-24 11:58:41 GMT mtk01461
**  change threshold to 256
**  \main\maintrunk.MT5921\12 2008-03-11 14:51:05 GMT mtk01461
**  Remove redundant GL_CONN_INFO_T
**  \main\maintrunk.MT5921\11 2008-01-07 15:07:41 GMT mtk01461
**  Adjust the netif stop threshold to 150
**  \main\maintrunk.MT5921\10 2007-11-26 19:43:46 GMT mtk01461
**  Add OS_TIMESTAMP macro
**
**  \main\maintrunk.MT5921\9 2007-11-07 18:38:38 GMT mtk01461
**  Move definition
**  \main\maintrunk.MT5921\8 2007-11-02 01:04:00 GMT mtk01461
**  Unify TX Path for Normal and IBSS Power Save + IBSS neighbor learning
** Revision 1.5  2007/07/12 11:04:28  MTK01084
** update macro to delay for ms order
**
** Revision 1.4  2007/07/05 07:25:34  MTK01461
** Add Linux initial code, modify doc, add 11BB, RF init code
**
** Revision 1.3  2007/06/27 02:18:51  MTK01461
** Update SCAN_FSM, Initial(Can Load Module), Proc(Can do Reg R/W), TX API
**
** Revision 1.2  2007/06/25 06:16:24  MTK01461
** Update illustrations, gl_init.c, gl_kal.c, gl_kal.h, gl_os.h and RX API
**
*/

#ifndef _GL_OS_H
#define _GL_OS_H

/*******************************************************************************
*                         C O M P I L E R   F L A G S
********************************************************************************
*/
/*------------------------------------------------------------------------------
 * Flags for LINUX(OS) dependent
 *------------------------------------------------------------------------------
 */
#define CFG_MAX_WLAN_DEVICES                1 /* number of wlan card will coexist*/

#define CFG_USE_SPIN_LOCK_BOTTOM_HALF       1 /* 1: Enable use of SPIN LOCK Bottom Half for LINUX
                                                 0: Disable - use SPIN LOCK IRQ SAVE instead */

#define CFG_TX_PADDING_SMALL_ETH_PACKET     0 /* 1: Enable - Drop ethernet packet if it < 14 bytes.
                                                             And pad ethernet packet with dummy 0 if it < 60 bytes.
                                                 0: Disable */

#define CFG_TX_STOP_NETIF_QUEUE_THRESHOLD   2048 /* packets */


#define ETH_P_1X                            0x888E
#define IPTOS_PREC_OFFSET                   5
#define USER_PRIORITY_DEFAULT               0

//#if SUPPORT_WAPI
#define ETH_WPI_1X                         0x88B4
//#endif

#define DRV_NAME    "[MT5921]: "

/*******************************************************************************
*                    E X T E R N A L   R E F E R E N C E S
********************************************************************************
*/
#include <linux/version.h>      /* constant of kernel version */

#include <linux/kernel.h>       /* bitops.h */

#include <linux/timer.h>        /* struct timer_list */
#include <linux/jiffies.h>      /* jiffies */
#include <linux/delay.h>        /* udelay and mdelay macro */

#include <linux/irq.h>          /* IRQT_FALLING */

#include <linux/netdevice.h>    /* struct net_device, struct net_device_stats */
#include <linux/etherdevice.h>  /* for eth_type_trans() function */
#include <linux/wireless.h>     /* struct iw_statistics */
#include <linux/if_arp.h>

#include <linux/ip.h>           /* struct iphdr */

#include <linux/string.h>       /* for memcpy()/memset() function */
#include <linux/stddef.h>       /* for offsetof() macro */

#include <linux/proc_fs.h>      /* The proc filesystem constants/structures */

#include <linux/rtnetlink.h>    /* for rtnl_lock() and rtnl_unlock() */
#include <linux/kthread.h>      /* kthread_should_stop(), kthread_run() */
#include <linux/vmalloc.h>

#include <linux/inetdevice.h>

#include <asm/uaccess.h>        /* for copy_from_user() */

#include <asm/io.h>             /* readw and writew */

#include <asm/div64.h>           /* for division */

extern void panic(const char * fmt, ...);                       /* See kernel/panic.c */
extern int printk(const char * fmt, ...);                       /* See kernel/printk.c */
extern int sprintf(char *buf, const char *fmt, ...);            /* See lib/vsprintf.c */
extern int sscanf(const char * buf, const char * fmt, ...);     /* See lib/vsprintf.c */

#if WIRELESS_EXT > 12
#include <net/iw_handler.h>
#endif

#include "version.h"

#include "config.h"

#include "gl_typedef.h"
#include "typedef.h"
#include "queue.h"
#include "gl_kal.h"
#include "hif.h"


#include "debug.h"

#include "wlan_lib.h"
#include "wlan_oid.h"
#include "wlan_oid_rftest.h"

#include "../platform.h"

extern BOOLEAN fgIsBusAccessFailed;

/*******************************************************************************
*                              C O N S T A N T S
********************************************************************************
*/

/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/
typedef struct _GL_WPA_INFO_T {
    UINT_32 u4WpaVersion;
    UINT_32 u4KeyMgmt;
    UINT_32 u4CipherGroup;
    UINT_32 u4CipherPairwise;
    UINT_32 u4AuthAlg;
    BOOLEAN fgPrivacyInvoke;
} GL_WPA_INFO_T, *P_GL_WPA_INFO_T;


struct _GLUE_INFO_T {
    /* Device handle */
    struct net_device *prDevHandler;

    /* Device Index(index of arWlanDevInfo[]) */
    INT_32 i4DevIdx;

    /* Device statistics */
    struct net_device_stats rNetDevStats;

    /* Tasklet struct used for deferred task */
    struct tasklet_struct tasklet;

    /* The master timer event (only one) */
    struct timer_list rMasterTimer;


    /* Wireless statistics struct net_device */
    struct iw_statistics rIwStats;

    /* spinlock to sync power save mechanism */
    spinlock_t rSpinLock[SPIN_LOCK_NUM];

    /* Number of pending frames, also used for debuging if any frame is
     * missing during the process of unloading Driver.
     *
     * NOTE(Kevin): In Linux, we also use this variable as the threshold
     * for manipulating the netif_stop(wake)_queue() func.
     */
    UINT_32         u4TxPendingFrameNum;

    /* Host interface related information */
    /* defined in related hif header file */
    GL_HIF_INFO_T   rHifInfo;

    /*! \brief wext wpa related information */
    GL_WPA_INFO_T   rWpaInfo;

    /* Pointer to ADAPTER_T - main data structure of internal protocol stack */
    P_ADAPTER_T prAdapter;

#ifdef WLAN_INCLUDE_PROC
    struct proc_dir_entry *pProcRoot;
#endif /* WLAN_INCLUDE_PROC */

    /* Indicated media state */
    ENUM_PARAM_MEDIA_STATE_T eParamMediaStateIndicated;

    /* Device power state D0~D3 */
    PARAM_DEVICE_POWER_STATE ePowerState;

#if CFG_SUPPORT_EXT_CONFIG
    UINT_16                 au2ExtCfg[256];  /* NVRAM data buffer */
    UINT_32                 u4ExtCfgLength;  /* 0 means data is NOT valid */
    ENUM_CFG_SRC_TYPE_T     eCfgSrcType;
#endif

#if SUPPORT_WAPI
    /* Should be large than the PARAM_WAPI_ASSOC_INFO_T */
    UINT_8                  aucWapiAssocInfoIEs[42];
    UINT_16                 u2WapiAssocInfoIESz;
#endif
    BOOL    fgRadioOn; /* driver radio on/off state */
   
    /* LED Support Usage */
    UINT_16            u2LedBlinkMode;
    UINT_32            u4LedBlinkOnTime;
    UINT_32            u4LedBlinkOffTime;
    UINT_32            u4LedSetting;

};

#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 0)
    /* linux 2.4 */
    typedef void (*PFN_WLANISR)(int irq, void *dev_id, struct pt_regs *regs);
#else
    typedef irqreturn_t (*PFN_WLANISR)(int irq, void *dev_id, struct pt_regs *regs);
#endif

typedef void (*PFN_LINUX_TIMER_FUNC)(unsigned long);

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
/* Macros of SPIN LOCK operations for using in Glue Layer                     */
/*----------------------------------------------------------------------------*/
#if CFG_USE_SPIN_LOCK_BOTTOM_HALF
    #define GLUE_SPIN_LOCK_DECLARATION()
    #define GLUE_ACQUIRE_SPIN_LOCK(prGlueInfo, rLockCategory)   \
            { \
                if (rLockCategory < SPIN_LOCK_NUM) \
                spin_lock_bh(&(prGlueInfo->rSpinLock[rLockCategory])); \
            }
    #define GLUE_RELEASE_SPIN_LOCK(prGlueInfo, rLockCategory)   \
            { \
                if (rLockCategory < SPIN_LOCK_NUM) \
                spin_unlock_bh(&(prGlueInfo->rSpinLock[rLockCategory])); \
            }
#else /* !CFG_USE_SPIN_LOCK_BOTTOM_HALF */
    #define GLUE_SPIN_LOCK_DECLARATION()                        UINT_32 __u4Flags = 0
    #define GLUE_ACQUIRE_SPIN_LOCK(prGlueInfo, rLockCategory)   \
            { \
                if (rLockCategory < SPIN_LOCK_NUM) \
                spin_lock_irqsave(&(prGlueInfo)->rSpinLock[rLockCategory], __u4Flags); \
            }
    #define GLUE_RELEASE_SPIN_LOCK(prGlueInfo, rLockCategory)   \
            { \
                if (rLockCategory < SPIN_LOCK_NUM) \
                spin_unlock_irqrestore(&(prGlueInfo->rSpinLock[rLockCategory]), __u4Flags); \
            }
#endif /* !CFG_USE_SPIN_LOCK_BOTTOM_HALF */


/*----------------------------------------------------------------------------*/
/* Macros for accessing Reserved Fields of native packet                      */
/*----------------------------------------------------------------------------*/
#define GLUE_GET_PKT_QUEUE_ENTRY(_p)    \
            (&( ((struct sk_buff *)(_p))->cb[0] ))

#define GLUE_GET_PKT_DESCRIPTOR(_prQueueEntry)  \
            ((P_NATIVE_PACKET) ((UINT_32)_prQueueEntry - offsetof(struct sk_buff, cb[0])) )


#define GLUE_SET_PKT_TID_IS1X(_p, _tid, _is1x)  \
            (*((PUINT_8) &( ((struct sk_buff *)(_p))->cb[4] )) = (((UINT_8)((_tid) & (BITS(0,6)))) | ((UINT_8)((_is1x) << 7))))

#define GLUE_GET_PKT_TID(_p)        \
            ((*((PUINT_8) &( ((struct sk_buff *)(_p))->cb[4] )) ) & (BITS(0,6)))

#define GLUE_GET_PKT_IS1X(_p)        \
            (((*((PUINT_8) &( ((struct sk_buff *)(_p))->cb[4] ))) & (BIT(7))) >> 7 )

#define GLUE_SET_PKT_HEADER_LEN(_p, _ucMacHeaderLen)    \
            (*((PUINT_8) &( ((struct sk_buff *)(_p))->cb[5] )) = (UINT_8)(_ucMacHeaderLen))

#define GLUE_GET_PKT_HEADER_LEN(_p) \
            (*((PUINT_8) &( ((struct sk_buff *)(_p))->cb[5] )) )


#define GLUE_SET_PKT_PAYLOAD_LEN(_p, _u2PayloadLen) \
            (*((PUINT_16) &( ((struct sk_buff *)(_p))->cb[6] )) = (UINT_16)(_u2PayloadLen))

#define GLUE_GET_PKT_PAYLOAD_LEN(_p)    \
            (*((PUINT_16) &( ((struct sk_buff *)(_p))->cb[6] )) )


#define GLUE_SET_PKT_ARRIVAL_TIME(_p, _rSysTime) \
            (*((POS_SYSTIME) &( ((struct sk_buff *)(_p))->cb[8] )) = (OS_SYSTIME)(_rSysTime))

#define GLUE_GET_PKT_ARRIVAL_TIME(_p)    \
            (*((POS_SYSTIME) &( ((struct sk_buff *)(_p))->cb[8] )) )

/* Check validity of prDev, private data, and pointers */
#define GLUE_CHK_DEV(prDev) \
    ((prDev && netdev_priv(prDev)) ? TRUE : FALSE)

#define GLUE_CHK_PR2(prDev, pr2) \
    ((GLUE_CHK_DEV(prDev) && pr2) ? TRUE : FALSE)

#define GLUE_CHK_PR3(prDev, pr2, pr3) \
    ((GLUE_CHK_PR2(prDev, pr2) && pr3) ? TRUE : FALSE)

#define GLUE_CHK_PR4(prDev, pr2, pr3, pr4) \
    ((GLUE_CHK_PR3(prDev, pr2, pr3) && pr4) ? TRUE : FALSE)


/*******************************************************************************
*                  F U N C T I O N   D E C L A R A T I O N S
********************************************************************************
*/
#ifdef WLAN_INCLUDE_PROC
INT_32
procRemoveProcfs (
    struct net_device *prDev,
    char *pucDevName
    );

INT_32
procInitProcfs (
    struct net_device *prDev,
    char *pucDevName
    );
#endif /* WLAN_INCLUDE_PROC */

#if defined(_HIF_SDIO)
extern WLAN_STATUS
sdio_io_ctrl (IN P_GLUE_INFO_T        prGlueInfo,
    IN PFN_OID_HANDLER_FUNC pfnOidHandler,
    IN PVOID                pvInfoBuf,
    IN UINT_32              u4InfoBufLen,
    IN BOOL                 fgRead,
    IN BOOL                 fgWaitResp,
    OUT PUINT_32            pu4QryInfoLen
    );
#endif
extern WIFI_CFG_DATA gPlatformCfg;


#if !BUILD_USE_EEPROM
extern bool
cfgDataRead16( void * prAdapter,unsigned char ucWordOffset, unsigned short * pu2Data );
extern bool
cfgDataWrite16( void * prAdapter,unsigned char ucWordOffset,unsigned short u2Data );

#if 0
extern bool
platformNvramRead16( void * prAdapter,unsigned char ucWordOffset, unsigned short * pu2Data );

extern bool
platformNvramWrite16( void * prAdapter,unsigned char ucWordOffset,unsigned short u2Data );
#endif
#endif

extern bool
customDataRead8( void * prAdapter,unsigned char ucByteOffset, unsigned char * pucData );

extern bool
customDataWrite8( void * prAdapter,unsigned char ucByteOffset,unsigned char ucData );

extern int platform_init(void);
extern void platform_deinit(void);


/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/


#endif /* _GL_OS_H */

