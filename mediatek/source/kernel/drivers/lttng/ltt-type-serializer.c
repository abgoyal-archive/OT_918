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

/**
 * ltt-type-serializer.c
 *
 * LTTng specialized type serializer.
 *
 * Copyright Mathieu Desnoyers, 2008.
 *
 * Dual LGPL v2.1/GPL v2 license.
 */
#include <linux/module.h>

#include "ltt-type-serializer.h"
#include "ltt-relay-lockless.h"

notrace
void _ltt_specialized_trace(const struct marker *mdata, void *probe_data,
		void *serialize_private, unsigned int data_size,
		unsigned int largest_align)
{
	int ret;
	uint16_t eID;
	size_t slot_size;
	unsigned int chan_index;
	struct ltt_chanbuf *buf;
	struct ltt_chan *chan;
	struct ltt_trace *trace;
	uint64_t tsc;
	long buf_offset;
	int cpu;
	unsigned int rflags;

	/*
	 * If we get here, it's probably because we have useful work to do.
	 */
	if (unlikely(ltt_traces.num_active_traces == 0))
		return;

	rcu_read_lock_sched_notrace();
	cpu = smp_processor_id();
	__get_cpu_var(ltt_nesting)++;
	/*
	 * asm volatile and "memory" clobber prevent the compiler from moving
	 * instructions out of the ltt nesting count. This is required to ensure
	 * that probe side-effects which can cause recursion (e.g. unforeseen
	 * traps, divisions by 0, ...) are triggered within the incremented
	 * nesting count section.
	 */
	barrier();
	eID = mdata->event_id;
	chan_index = mdata->channel_id;

	/*
	 * Iterate on each trace, typically small number of active traces,
	 * list iteration with prefetch is usually slower.
	 */
	__list_for_each_entry_rcu(trace, &ltt_traces.head, list) {
		if (unlikely(!trace->active))
			continue;
		if (unlikely(!ltt_run_filter(trace, eID)))
			continue;
#ifdef LTT_DEBUG_EVENT_SIZE
		rflags = LTT_RFLAG_ID_SIZE;
#else
		if (unlikely(eID >= LTT_FREE_EVENTS))
			rflags = LTT_RFLAG_ID;
		else
			rflags = 0;
#endif
		/*
		 * Skip channels added after trace creation.
		 */
		if (unlikely(chan_index >= trace->nr_channels))
			continue;
		chan = &trace->channels[chan_index];
		if (!chan->active)
			continue;

		/* reserve space : header and data */
		ret = ltt_reserve_slot(chan, trace, data_size, largest_align,
				       cpu, &buf, &slot_size, &buf_offset, &tsc,
				       &rflags);
		if (unlikely(ret < 0))
			continue; /* buffer full */

		/* Out-of-order write : header and data */
		buf_offset = ltt_write_event_header(&buf->a, &chan->a,
						    buf_offset, eID, data_size,
						    tsc, rflags);
		if (data_size) {
			buf_offset += ltt_align(buf_offset, largest_align);
			ltt_relay_write(&buf->a, &chan->a, buf_offset,
					serialize_private, data_size);
			buf_offset += data_size;
		}
		/* Out-of-order commit */
		ltt_commit_slot(buf, chan, buf_offset, data_size, slot_size);
	}
	/*
	 * asm volatile and "memory" clobber prevent the compiler from moving
	 * instructions out of the ltt nesting count. This is required to ensure
	 * that probe side-effects which can cause recursion (e.g. unforeseen
	 * traps, divisions by 0, ...) are triggered within the incremented
	 * nesting count section.
	 */
	barrier();
	__get_cpu_var(ltt_nesting)--;
	rcu_read_unlock_sched_notrace();
}
EXPORT_SYMBOL_GPL(_ltt_specialized_trace);

MODULE_LICENSE("GPL and additional rights");
MODULE_AUTHOR("Mathieu Desnoyers");
MODULE_DESCRIPTION("LTT type serializer");
