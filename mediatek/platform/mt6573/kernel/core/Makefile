# Copyright Statement:
#
# This software/firmware and related documentation ("MediaTek Software") are
# protected under relevant copyright laws. The information contained herein
# is confidential and proprietary to MediaTek Inc. and/or its licensors.
# Without the prior written permission of MediaTek inc. and/or its licensors,
# any reproduction, modification, use or disclosure of MediaTek Software,
# and information contained herein, in whole or in part, shall be strictly prohibited.

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


#
# Makefile for the linux kernel.
#

#obj-y := core.o irq.o system.o timer.o mt6573_devs.o mt6573_board.o dma.o mt6573_eint.o mt6573_boot.o

obj-y := core.o irq.o system.o timer.o mt6573_devs.o mt6573_board.o dma.o mt6573_boot.o mt6573_gpt.o mt6573_eint.o mt6573_auxadc.o mt6573_gpt.o
obj-y += mt6573_gpio.o mt6573_pwm.o
#obj-y += mt6573_auxadc.o mt6573_gpt.o mt6573_pwm.o
obj-y += mt6573_pm_api.o mt6573_ost.o mtkpm.o cpufreq-mt6573.o mt6573_pm_factory.o mt6573_sleep.o mt6573_pm_log.o mt6573_avs_thermal.o mt6573_clock_manager.o mt6573_pm_ldo.o mt6573_dcm.o
obj-$(CONFIG_MT65XX_TRACER) += mt6573_mon.o arm11_perf_mon.o mt6573_emi_bm.o 
obj-y += mt6573_MDP.o mt6573_sysram.o
obj-y += mt6573_isp.o
obj-y += mt6573_eis.o
obj-y += mt6573_fdvt.o
obj-y += mt6573_wdt.o
obj-y += mt_rfkill.o
ifneq ($(MTK_EMMC_SUPPORT),yes)
obj-y += sbchk_base.o
endif
obj-y += outercache.o mt6573_emi_bwl.o mt6573_emi_mpu.o
obj-y += flush_dcache_all.o inner_flush_dcache_all.o
# MTK COMBO chip or not
ifneq ($(CONFIG_MTK_COMBO),)
ifeq ($(CONFIG_MTK_COMBO),n)
#mt_bt.c should not be built on all MT6573 project[mt_bt.c must be compiled after btwlanem.c is built ]
#obj-y += mt_bt.o
else
obj-y += mt_combo.o
endif
else
#mt_bt.c should not be built on all MT6573 project[mt_bt.c must be compiled after btwlanem.c is built ]
#obj-y += mt_bt.o
endif
obj-y += arm_pwr_test.o arm_pwr_test_asm.o

ccflags-y += -I$(MTK_PATH_PLATFORM)/drivers/power \
             -I$(MTK_PATH_SOURCE)/drivers/power \
             -I$(MTK_PATH_SOURCE)/drivers/sound \
             -I$(MTK_PATH_PLATFORM)/drivers/sound \
             -I$(MTK_PATH_SOURCE)/drivers/wdk
