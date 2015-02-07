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

#ifndef DRV_COMMON_H
#define DRV_COMMON_H

#include "val_types.h"
#include "mfv_config.h"

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_ENABLE_MFV_INTERRUPT_)
#define WAITING_MODE VAL_INTERRUPT_MODE
#else
#define WAITING_MODE VAL_POLLING_MODE
#endif

#define ADD_QUEUE(queue, index, q_type, q_address, q_value, q_mask)       \
{                                                                         \
  queue[index].type     = q_type;                                         \
  queue[index].address  = q_address;                                      \
  queue[index].value    = q_value;                                        \
  queue[index].mask     = q_mask;                                         \
  index = index + 1;                                                      \
}

#define DO_MFV_REEST(cmd, index)                                                            \
{                                                                                           \
    ADD_QUEUE(cmd, index, WRITE_REG_CMD, MFV_RESET, 1, 0);                                  \
    ADD_QUEUE(cmd, index, WRITE_REG_CMD, MFV_RESET, 0, 0);                                  \
    ADD_QUEUE(cmd, index, TIMEOUT_CMD, 0, 0xFFFFFFFF, 0);                                   \
    ADD_QUEUE(cmd, index, POLL_CMD, MFV_RESET, 2, 2);                                       \
	ADD_QUEUE(cmd, index, SETUP_ISR_CMD, MFV_IRQ_STS, 0, WAITING_MODE);                     \
}

// load instruction packet                                                                
#define LOAD_INSTRUCTION_PACKET(cmd, index, driver_type, gmc_base)                          \
{                                                                                           \
  ADD_QUEUE(cmd, index, LOAD_INST_START_CMD, 0, driver_type, 0);                            \
  DO_MFV_REEST(cmd, index);                                                                 \
  ADD_QUEUE(cmd, index, LOAD_INST_CMD, MFV_IDMA_PAC_BASE, driver_type, 4);                  \
  ADD_QUEUE(cmd, index, LOAD_INST_CMD, MFV_MEM_SWITCH, driver_type, 1);                     \
  ADD_QUEUE(cmd, index, WRITE_REG_CMD, MFV_IDMA_GMC_BASE, (VAL_UINT32_T)gmc_base, 0);       \
  ADD_QUEUE(cmd, index, WRITE_REG_CMD, MFV_IDMA_STR, 1, 0);                                 \
  ADD_QUEUE(cmd, index, WAIT_ISR_CMD, MFV_IRQ_STS, 0, 2);                                   \
  ADD_QUEUE(cmd, index, WRITE_REG_CMD, MFV_IRQ_ACK, 2, 0);                                  \
  ADD_QUEUE(cmd, index, LOAD_INST_END_CMD, 0, driver_type, 0);                              \
}

#ifdef __cplusplus
}
#endif

#endif /* DRV_COMMON_H */
