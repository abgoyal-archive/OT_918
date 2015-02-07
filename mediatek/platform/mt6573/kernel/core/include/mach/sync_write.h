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

#ifndef __MT6573_SYNC_WRITE_H__
#define __MT6573_SYNC_WRITE_H__

#if defined(__KERNEL__)

#include <linux/io.h>
#include <asm/cacheflush.h>
#include <asm/system.h>

/*
 * Define macros.
 */

/*
 * NoteXXX: On the MT6573 platform, the early response function of L2CC isn't working.
 *          This is because the core is ARM11 (not CA9) and AWUSERSx[11] is alway 0.
 *          Thus a dsb is sufficient for us to do the data synchronization barrier. 
 *          There is no need to perform a outer cache sync operation.
 */
#define mt65xx_reg_sync_writel(v, a) \
        do {    \
            writel((v), (a));   \
            dsb();  \
            outer_sync();   \
        } while (0)

#define mt65xx_reg_sync_writew(v, a) \
        do {    \
            writew((v), (a));   \
            dsb();  \
            outer_sync();   \
        } while (0)

#define mt65xx_reg_sync_writeb(v, a) \
        do {    \
            writeb((v), (a));   \
            dsb();  \
            outer_sync();   \
        } while (0)

#else   /* __KERNEL__ */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define dsb()   \
        do {    \
            __asm__ __volatile__ ("mcr p15, 0, %0, c7, c10, 4" \
                                  : : "r" (0) : "memory"); \
        } while (0)

#define outer_sync()    \
        do {    \
            int fd; \
            char buf[] = "1";   \
            fd = open("/sys/bus/platform/drivers/outercache/outer_sync", O_WRONLY); \
            if (fd != -1) {  \
                write(fd, buf, strlen(buf)); \
            }   \
        } while (0)

#define mt65xx_reg_sync_writel(v, a) \
        do {    \
            *(volatile unsigned int *)(a) = (v);    \
            __asm__ __volatile__ ("mcr p15, 0, %0, c7, c10, 4" \
                                  : : "r" (0) : "memory"); \
            outer_sync();   \
        } while (0)

#define mt65xx_reg_sync_writew(v, a) \
        do {    \
            *(volatile unsigned short *)(a) = (v);    \
            __asm__ __volatile__ ("mcr p15, 0, %0, c7, c10, 4" \
                                  : : "r" (0) : "memory"); \
            outer_sync();   \
        } while (0)

#define mt65xx_reg_sync_writeb(v, a) \
        do {    \
            *(volatile unsigned char *)(a) = (v);    \
            __asm__ __volatile__ ("mcr p15, 0, %0, c7, c10, 4" \
                                  : : "r" (0) : "memory"); \
            outer_sync();   \
        } while (0)

#endif  /* __KERNEL__ */

#endif  /* !__MT6573_SYNC_WRITE_H__ */

