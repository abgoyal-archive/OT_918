# Copyright Statement:
#
# This software/firmware and related documentation ("MediaTek Software") are
# protected under relevant copyright laws. The information contained herein
# is confidential and proprietary to MediaTek Inc. and/or its licensors.
# Without the prior written permission of MediaTek inc. and/or its licensors,
# any reproduction, modification, use or disclosure of MediaTek Software,
# and information contained herein, in whole or in part, shall be strictly prohibited.
#
# MediaTek Inc. (C) 2010. All rights reserved.
#
# BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
# THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
# RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER ON
# AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
# NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
# SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
# SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
# THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
# THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
# CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
# SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
# STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
# CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
# AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
# OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
# MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
#
# The following software/firmware and/or related documentation ("MediaTek Software")
# have been modified by MediaTek Inc. All revisions are subject to any receiver's
# applicable license agreements with MediaTek Inc.


# LTTng tracing probes

ifdef CONFIG_FTRACE
CFLAGS_REMOVE_kernel-trace.o = -pg
CFLAGS_REMOVE_mm-trace.o = -pg
CFLAGS_REMOVE_fs-trace.o = -pg
CFLAGS_REMOVE_ipc-trace.o = -pg
CFLAGS_REMOVE_lockdep-trace.o = -pg
CFLAGS_REMOVE_rcu-trace.o = -pg
CFLAGS_REMOVE_syscall-trace.o = -pg
CFLAGS_REMOVE_trap-trace.o = -pg
CFLAGS_REMOVE_pm-trace.o = -pg
endif

obj-m += kernel-trace.o mm-trace.o fs-trace.o ipc-trace.o lockdep-trace.o \
	 rcu-trace.o syscall-trace.o trap-trace.o pm-trace.o

ifeq ($(CONFIG_NET),y)
ifdef CONFIG_FTRACE
CFLAGS_REMOVE_net-trace.o = -pg
CFLAGS_REMOVE_net-extended-trace.o = -pg
endif
obj-m += net-trace.o net-extended-trace.o
endif

ifdef CONFIG_JBD2
ifdef CONFIG_FTRACE
CFLAGS_REMOVE_jbd2-trace.o = -pg
endif
obj-m += jbd2-trace.o
endif

#ifdef CONFIG_EXT4_FS
#ifdef CONFIG_FTRACE
#CFLAGS_REMOVE_ext4-trace.o = -pg
#endif
#obj-$(CONFIG_LTT_TRACEPROBES)	+= ext4-trace.o
#endif

ifdef CONFIG_BLOCK
ifdef CONFIG_FTRACE
CFLAGS_REMOVE_block-trace.o = -pg
endif
obj-m += block-trace.o
endif


