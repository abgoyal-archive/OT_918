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

#ifndef MFV_DRV_BASE_H
#define MFV_DRV_BASE_H

#include "val_types.h"

#define LOAD_INSTRUCTION_AUTO

#ifdef __cplusplus
extern "C" {
#endif

typedef struct __MFV_DRV_CMD_T *P_MFV_DRV_CMD_T;
typedef struct __MFV_DRV_CMD_T
{
    VAL_UINT32_T type;      // enum MFV_DRV_CMD_TYPE
    VAL_UINT32_T address;   // phisical address
    VAL_UINT32_T value;     // 1. Value. 2. to be "Virtual address" in Read_xxx_CMD destination. 3. to be type in LOADxxx or ENABLExxx/DISABLExxx.
    VAL_UINT32_T mask;
} MFV_DRV_CMD_T;

typedef struct __MFV_DRV_CMD_QUEUE_T *P_MFV_DRV_CMD_QUEUE_T;
typedef struct __MFV_DRV_CMD_QUEUE_T
{
    VAL_UINT32_T        CmdNum;
    P_MFV_DRV_CMD_T     pCmd;
} MFV_DRV_CMD_QUEUE_T;

typedef enum
{
    LOAD_INST_START_CMD,
    LOAD_INST_END_CMD,
    LOAD_INST_CMD,
    ENABLE_HW_CMD,
    DISABLE_HW_CMD,
    CACHE_FLUSH, //cache invalidate
    CACHE_CLEAN, //write cache to memory
    WRITE_REG_CMD,
    READ_REG_CMD,
    WRITE_SYSRAM_CMD,
    READ_SYSRAM_CMD,
    POLL_CMD,
    SETUP_ISR_CMD,
	WAIT_ISR_CMD,	
    TIMEOUT_CMD,
	LOAD_RV9_TABLE,
	READ_INST_PACKET,
    WRITE_SYSRAM_RANGE_CMD,
    END_CMD
} MFV_DRV_CMD_TYPE;


#ifdef __cplusplus
}
#endif

#endif /* MFV_DRV_BASE_H */
