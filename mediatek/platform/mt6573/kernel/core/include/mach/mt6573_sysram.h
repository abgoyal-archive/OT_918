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

#ifndef _MT6573SYSRAM_H
#define _MT6573SYSRAM_H

#include <linux/ioctl.h>

#define SYSRAM_DEV_NAME         "mt6573-SYSRAM"
#define MT6573_SYSRAMMAGICNO    'p'
#define MT6573_SYSRAM_DEV_MAJOR_NUMBER 251

typedef enum {
    MT6573SYSRAMUSR_ROTDMA0 = 0,
    MT6573SYSRAMUSR_ROTDMA1,
    MT6573SYSRAMUSR_ROTDMA2,
    MT6573SYSRAMUSR_ROTDMA3,
    MT6573SYSRAMUSR_TVROT,
    MT6573SYSRAMUSR_TVC,
    MT6573SYSRAMUSR_RDMA0,
    MT6573SYSRAMUSR_RDMA1,
    MT6573SYSRAMUSR_JPGDMA,
    MT6573SYSRAMUSR_JPGDECODER,
    MT6573SYSRAMUSR_MFLEXVIDEO,
    MT6573SYSRAMUSR_BRZ,
    MT6573SYSRAMUSR_CAM_FLICKER, 
    MT6573SYSRAMUSR_CAM_DEFECT, 
    MT6573SYSRAMUSR_CAM_SHADING_PREVIEW, 
    MT6573SYSRAMUSR_CAM_SHADING_CAPTURE, 
    MT6573SYSRAMUSR_CAM_LCE0, 
    MT6573SYSRAMUSR_CAM_LCE1, 
    MT6573SYSRAMUSR_CAM_PCA, 
    MT6573SYSRAMUSR_EIS,
    MT6573SYSRAMUSR_VRZ,
    MT6573SYSRAMUSR_G2D_RMMU, 
    MT6573SYSRAMUSR_SPI_DMA, 
    MT6573SYSRAMUSR_CNT,
    MT6573SYSRAMUSR_NONE = -1
}MT6573_SYSRAM_USR;

//IOCTRL(inode * ,file * ,cmd * ,arg * )
typedef struct {
    unsigned long u4Alignment;  // In : alignment in bytes
    unsigned long u4Size;       // In : Size in bytes
    MT6573_SYSRAM_USR u4Owner;  // In : Owner
    unsigned long u4Addr;       // In/Out : address
    unsigned long u4TimeoutInMS;// In : millisecond
} stSysramParam;

/*******************************************************************************
* IOCTL commnad
********************************************************************************/
//Lock User
#define SYSRAM_X_USRALLOC_TIMEOUT   _IOWR(MT6573_SYSRAMMAGICNO, 0, stSysramParam)
#define SYSRAM_X_USRALLOC           _IOWR(MT6573_SYSRAMMAGICNO, 1, stSysramParam)

//Unlock User
#define SYSRAM_S_USRFREE            _IOW(MT6573_SYSRAMMAGICNO, 2, stSysramParam)

//Dump memory layout
#define SYSRAM_T_DUMPLAYOUT         _IO(MT6573_SYSRAMMAGICNO, 3)

//
//Lock User
#define MT6573MDP_X_SYSRAMALLOC_TIMEOUT SYSRAM_X_USRALLOC_TIMEOUT
#define MT6573MDP_X_SYSRAMALLOC         SYSRAM_X_USRALLOC
//
//Unlock User
#define MT6573MDP_S_SYSRAMFREE          SYSRAM_S_USRFREE
//
//Dump memory layout
#define MT6573MDP_T_DUMPLAYOUT          SYSRAM_T_DUMPLAYOUT
//

unsigned long MT6573_SYSRAM_ALLOC_TIMEOUT(MT6573_SYSRAM_USR const eOwner, unsigned long const u4Size, unsigned long u4Alignment, unsigned long const u4TimeoutInMS);
unsigned long MT6573_SYSRAM_ALLOC(MT6573_SYSRAM_USR eOwner , unsigned long u4Size, unsigned long u4Alignment);
void MT6573_SYSRAM_FREE(MT6573_SYSRAM_USR eOwner);

#else
#endif
