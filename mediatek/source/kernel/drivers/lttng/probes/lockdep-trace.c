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

/*
 * ltt/probes/lockdep-trace.c
 *
 * lockdep tracepoint probes.
 *
 * (C) Copyright 2009 - Mathieu Desnoyers <mathieu.desnoyers@polymtl.ca>
 * Dual LGPL v2.1/GPL v2 license.
 */

#include <linux/module.h>
#include <linux/lockdep.h>
#include <trace/lockdep.h>

void probe_lockdep_hardirqs_on(void *data, unsigned long retaddr)
{
	trace_mark_tp(lockdep, hardirqs_on, lockdep_hardirqs_on,
		probe_lockdep_hardirqs_on, "retaddr 0x%lX", retaddr);
}

void probe_lockdep_hardirqs_off(void *data, unsigned long retaddr)
{
	trace_mark_tp(lockdep, hardirqs_off, lockdep_hardirqs_off,
		probe_lockdep_hardirqs_off, "retaddr 0x%lX", retaddr);
}

void probe_lockdep_softirqs_on(void *data, unsigned long retaddr)
{
	trace_mark_tp(lockdep, softirqs_on, lockdep_softirqs_on,
		probe_lockdep_softirqs_on, "retaddr 0x%lX", retaddr);
}

void probe_lockdep_softirqs_off(void *data, unsigned long retaddr)
{
	trace_mark_tp(lockdep, softirqs_off, lockdep_softirqs_off,
		probe_lockdep_softirqs_off, "retaddr 0x%lX", retaddr);
}

void probe_lockdep_lock_acquire(void *data, unsigned long retaddr,
		unsigned int subclass, struct lockdep_map *lock, int trylock,
		int read, int hardirqs_off)
{
	trace_mark_tp(lockdep, lock_acquire, lockdep_lock_acquire,
		probe_lockdep_lock_acquire,
		"retaddr 0x%lX subclass %u lock %p trylock %d read %d "
		"hardirqs_off %d",
		retaddr, subclass, lock, trylock, read, hardirqs_off);
}

void probe_lockdep_lock_release(void *data, unsigned long retaddr,
		struct lockdep_map *lock, int nested)
{
	trace_mark_tp(lockdep, lock_release, lockdep_lock_release,
		probe_lockdep_lock_release,
		"retaddr 0x%lX lock %p nested %d",
		retaddr, lock, nested);
}

MODULE_LICENSE("GPL and additional rights");
MODULE_AUTHOR("Mathieu Desnoyers");
MODULE_DESCRIPTION("lockdep Tracepoint Probes");
