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

    .text

    .global enable_arm11_perf_mon
enable_arm11_perf_mon:
    MRC p15, 0, r0, c15, c12, 0
    ORR r0, r0, #1
    MCR p15, 0, r0, c15, c12, 0
    BX lr

    .global disable_arm11_perf_mon
disable_arm11_perf_mon:
    MRC p15, 0, r0, c15, c12, 0
    BIC r0, r0, #1
    MCR p15, 0, r0, c15, c12, 0
    BX lr

    .global reset_arm11_perf_mon_cnt
reset_arm11_perf_mon_cnt:
    MRC p15, 0, r0, c15, c12, 0
    ORR r0, r0, #6
    MCR p15, 0, r0, c15, c12, 0
    BX lr

    .global get_arm11_perf_mon_cyc_cnt
get_arm11_perf_mon_cyc_cnt:
    MRC p15, 0, r0, c15, c12, 1 
    BX lr

    .global set_arm11_perf_mon_cyc_cnt
set_arm11_perf_mon_cyc_cnt:
    MCR p15, 0, r0, c15, c12, 1 
    BX lr

    .global get_arm11_perf_mon_cnt0
get_arm11_perf_mon_cnt0:
    MRC p15, 0, r0, c15, c12, 2 
    BX lr

    .global set_arm11_perf_mon_cnt0
set_arm11_perf_mon_cnt0:
    MCR p15, 0, r0, c15, c12, 2 
    BX lr

    .global get_arm11_perf_mon_cnt1
get_arm11_perf_mon_cnt1:
    MRC p15, 0, r0, c15, c12, 3 
    BX lr

    .global set_arm11_perf_mon_cnt1
set_arm11_perf_mon_cnt1:
    MCR p15, 0, r0, c15, c12, 3 
    BX lr

    .global set_arm11_perf_mon_cnt0_evt
set_arm11_perf_mon_cnt0_evt:
    MOV r2, #0xff
    MRC p15, 0, r1, c15, c12, 0
    BIC r1, r1, r2, lsl #20
    ORR r1, r1, r0, lsl #20
    MCR p15, 0, r1, c15, c12, 0
    BX lr

    .global set_arm11_perf_mon_cnt1_evt
set_arm11_perf_mon_cnt1_evt:
    MOV r2, #0xff
    MRC p15, 0, r1, c15, c12, 0
    BIC r1, r1, r2, lsl #12
    ORR r1, r1, r0, lsl #12
    MCR p15, 0, r1, c15, c12, 0
    BX lr

    .end

