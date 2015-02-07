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

#ifndef _MT6573MDP_H
#define _MT6573MDP_H

#include <linux/ioctl.h>

#define MT6573_MDP_DEV_MAJOR_NUMBER 252
#define MT6573_MDPMAGICNO 'g'

#define BRZ_FLAG (0x1)
#define RDMA0_FLAG (0x2)
//#define OVL_FLAG (0x4)
#define CRZ_IPP_OVL_FLAG (0x8)
#define PRZ0_FLAG (0x10)
#define VRZ_FLAG (0x20)
#define JPGDMA_FLAG (0x40)
#define RDMA1_PRZ1_ROTDMA3_FLAG (0x80)
#define ROTDMA0_FLAG (0x100)
#define ROTDMA1_FLAG (0x200)
#define ROTDMA2_FLAG (0x400)

//IOCTRL(inode * ,file * ,cmd * ,arg * )

typedef struct {
    unsigned long u4LockResTable;
    unsigned long u4IsTimeShared;// 0 : No, 1 : Time shared
    unsigned long u4TimeOutInms;
} stLockResParam;

typedef struct {
    unsigned long u4IrqNo;
    unsigned long u4TimeOutInms;
} stWaitIrqParam;

#define MT6573_ROTDMA0_BUFFCNT 16
typedef struct {
    unsigned long u4Sec[MT6573_ROTDMA0_BUFFCNT];
    unsigned long u4MicroSec[MT6573_ROTDMA0_BUFFCNT];
} stTimeStamp;

typedef struct {
    unsigned long u4StartAddr;//In : 
    unsigned long u4Size;
    unsigned long u4Result;// 0 : out of pmem range, 1 : inside pmem range, 2 : partially overlap with pmem range
} stPMEMRange;

typedef struct {
    unsigned long u4CFG;
    unsigned long u4SRCSZ;
    unsigned long u4CROPLR;
    unsigned long u4CROPTB;
    unsigned long u4HRATIO;
    unsigned long u4VRATIO;
} stZoomSetting;

//IOCTL commnad
//Lock NODES
#define MT6573MDP_T_LOCKRESOURCE _IOW(MT6573_MDPMAGICNO,0,stLockResParam)

//Unlock NODES
#define MT6573MDP_T_UNLOCKRESOURCE _IOW(MT6573_MDPMAGICNO,1,int)

//wait IRQ
#define MT6573MDP_X_WAITIRQ _IOW(MT6573_MDPMAGICNO,2,stWaitIrqParam)

//Clear IRQ flag
#define MT6573MDP_T_CLRIRQ _IOW(MT6573_MDPMAGICNO,3,int)

//Dump registers
#define MT6573MDP_T_DUMPREG _IO(MT6573_MDPMAGICNO,4)

//Get ROTDMA0 time stamp
#define MT6573MDP_G_TIMESTAMP _IOR(MT6573_MDPMAGICNO , 5 , stTimeStamp)

//Get pmem range
#define MT6573MDP_G_PMEMRANGE _IOR(MT6573_MDPMAGICNO , 6 , stPMEMRange)

//Set zoom ratio
#define MT6573MDP_T_SETZOOM _IOR(MT6573_MDPMAGICNO , 7 , stZoomSetting)

//HW reset ROTDMA and RMMU
#define MT6573MDP_T_HWRESET _IOW(MT6573_MDPMAGICNO , 8 , unsigned int)

#else
#endif
