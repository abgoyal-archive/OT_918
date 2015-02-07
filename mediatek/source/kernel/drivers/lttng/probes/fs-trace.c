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
 * ltt/probes/fs-trace.c
 *
 * FS tracepoint probes.
 *
 * (C) Copyright 2009 - Mathieu Desnoyers <mathieu.desnoyers@polymtl.ca>
 * Dual LGPL v2.1/GPL v2 license.
 */

#include <linux/module.h>
#include <linux/buffer_head.h>
#include <trace/fs.h>

#include "../ltt-type-serializer.h"

void probe_fs_buffer_wait_start(void *_data, struct buffer_head *bh)
{
	trace_mark_tp(fs, buffer_wait_start, fs_buffer_wait_start,
		probe_fs_buffer_wait_start, "bh %p", bh);
}

void probe_fs_buffer_wait_end(void *_data, struct buffer_head *bh)
{
	trace_mark_tp(fs, buffer_wait_end, fs_buffer_wait_end,
		probe_fs_buffer_wait_end, "bh %p", bh);
}

void probe_fs_exec(void *_data, char *filename)
{
	trace_mark_tp(fs, exec, fs_exec, probe_fs_exec, "filename %s",
		filename);
}

void probe_fs_ioctl(void *_data, unsigned int fd, unsigned int cmd, unsigned long arg)
{
	trace_mark_tp(fs, ioctl, fs_ioctl, probe_fs_ioctl,
		"fd %u cmd %u arg %lu", fd, cmd, arg);
}

void probe_fs_open(void *_data, int fd, char *filename)
{
	trace_mark_tp(fs, open, fs_open, probe_fs_open,
		"fd %d filename %s", fd, filename);
}

void probe_fs_close(void *_data, unsigned int fd)
{
	trace_mark_tp(fs, close, fs_close, probe_fs_close, "fd %u", fd);
}

void probe_fs_lseek(void *_data, unsigned int fd, long offset, unsigned int origin)
{
	trace_mark_tp(fs, lseek, fs_lseek, probe_fs_lseek,
		"fd %u offset %ld origin %u", fd, offset, origin);
}

void probe_fs_llseek(void *_data, unsigned int fd, loff_t offset, unsigned int origin)
{
	trace_mark_tp(fs, llseek, fs_llseek, probe_fs_llseek,
		"fd %u offset %lld origin %u", fd,
		(long long)offset, origin);
}

void probe_fs_read(void *_data, unsigned int fd, char __user *buf, size_t count,
		ssize_t ret);

DEFINE_MARKER_TP(fs, read, fs_read, probe_fs_read,
	"count %zu fd %u");

notrace void probe_fs_read(void *_data, unsigned int fd, char __user *buf, size_t count,
		ssize_t ret)
{
	struct marker *marker;
	struct serialize_sizet_int data;

	data.f1 = count;
	data.f2 = fd;

	marker = &GET_MARKER(fs, read);
	ltt_specialized_trace(marker, marker->single.probe_private,
		&data, serialize_sizeof(data), sizeof(size_t));
}

void probe_fs_write(void *_data, unsigned int fd, char __user *buf, size_t count,
		ssize_t ret);

DEFINE_MARKER_TP(fs, write, fs_write, probe_fs_write,
	"count %zu fd %u");

notrace void probe_fs_write(void *_data, unsigned int fd, char __user *buf, size_t count,
		ssize_t ret)
{
	struct marker *marker;
	struct serialize_sizet_int data;

	data.f1 = count;
	data.f2 = fd;

	marker = &GET_MARKER(fs, write);
	ltt_specialized_trace(marker, marker->single.probe_private,
		&data, serialize_sizeof(data), sizeof(size_t));
}

void probe_fs_pread64(void *_data, unsigned int fd, char __user *buf, size_t count,
		loff_t pos, ssize_t ret)
{
	trace_mark_tp(fs, pread64, fs_pread64, probe_fs_pread64,
		"fd %u count %zu pos %llu",
		fd, count, (unsigned long long)pos);
}

void probe_fs_pwrite64(void *_data, unsigned int fd, const char __user *buf,
		size_t count, loff_t pos, ssize_t ret)
{
	trace_mark_tp(fs, pwrite64, fs_pwrite64, probe_fs_pwrite64,
		"fd %u count %zu pos %llu",
		fd, count, (unsigned long long)pos);
}

void probe_fs_readv(void *_data, unsigned long fd, const struct iovec __user *vec,
		unsigned long vlen, ssize_t ret)
{
	trace_mark_tp(fs, readv, fs_readv, probe_fs_readv,
		"fd %lu vlen %lu", fd, vlen);
}

void probe_fs_writev(void *_data, unsigned long fd, const struct iovec __user *vec,
		unsigned long vlen, ssize_t ret)
{
	trace_mark_tp(fs, writev, fs_writev, probe_fs_writev,
		"fd %lu vlen %lu", fd, vlen);
}

void probe_fs_select(void *_data, int fd, struct timespec *end_time)
{
	struct timespec tmptime;

	if (end_time) {
		tmptime = *end_time;
	} else {
		tmptime.tv_sec = -1L;
		tmptime.tv_nsec = -1L;
	}

	trace_mark_tp(fs, select, fs_select, probe_fs_select,
		"fd %d end_time_sec %ld end_time_nsec %ld", fd,
			tmptime.tv_sec, tmptime.tv_nsec);
}

void probe_fs_poll(void *_data, int fd)
{
	trace_mark_tp(fs, pollfd, fs_poll, probe_fs_poll,
		"fd %d", fd);
}

MODULE_LICENSE("GPL and additional rights");
MODULE_AUTHOR("Mathieu Desnoyers");
MODULE_DESCRIPTION("FS Tracepoint Probes");
