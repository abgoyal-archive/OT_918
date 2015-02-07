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

#include "mach/mt6573_reg_base.h"
#include "mach/mt6573_typedefs.h"

#ifndef __G2D_6573_REG_H__
#define __G2D_6573_REG_H__

#define G2D_base                                    G2D_BASE

#define REG_G2D_FMODE_CON                           *(volatile kal_uint32 *)(G2D_base + 0x0000)
#define REG_G2D_SMODE_CON                           *(volatile kal_uint32 *)(G2D_base + 0x0004)
#define REG_G2D_COM_CON                             *(volatile kal_uint32 *)(G2D_base + 0x0008)
#define REG_G2D_IRQ_CON                             *(volatile kal_uint32 *)(G2D_base + 0x000C)
#define REG_G2D_COM_STA                             *(volatile kal_uint32 *)(G2D_base + 0x0010)

#define REG_G2D_SLOW_DOWN                           *(volatile kal_uint32 *)(G2D_base + 0x001C)

#define REG_G2D_SRC_BASE                            *(volatile kal_uint32 *)(G2D_base + 0x0030)
#define REG_G2D_SRC_PITCH                           *(volatile kal_uint32 *)(G2D_base + 0x0034)
#define REG_G2D_SRC_XY                              *(volatile kal_uint32 *)(G2D_base + 0x0038)
#define REG_G2D_SRC_SIZE                            *(volatile kal_uint32 *)(G2D_base + 0x003C)
#define REG_G2D_SRC_KEY                             *(volatile kal_uint32 *)(G2D_base + 0x0040)

#define REG_G2D_DST_BASE                            *(volatile kal_uint32 *)(G2D_base + 0x0060)
#define REG_G2D_DST_PITCH                           *(volatile kal_uint32 *)(G2D_base + 0x0064)
#define REG_G2D_DST_XY0                             *(volatile kal_uint32 *)(G2D_base + 0x0068)
#define REG_G2D_DST_SIZE                            *(volatile kal_uint32 *)(G2D_base + 0x006C)
#define REG_G2D_DST_AVO_CLR                         *(volatile kal_uint32 *)(G2D_base + 0x0070)
#define REG_G2D_DST_REP_CLR                         *(volatile kal_uint32 *)(G2D_base + 0x0074)

#define REG_G2D_PAT_BASE                            *(volatile kal_uint32 *)(G2D_base + 0x0090)
#define REG_G2D_PAT_PITCH                           *(volatile kal_uint32 *)(G2D_base + 0x0094)
#define REG_G2D_PAT_XY                              *(volatile kal_uint32 *)(G2D_base + 0x0098)
#define REG_G2D_PAT_SIZE                            *(volatile kal_uint32 *)(G2D_base + 0x009C)
#define REG_G2D_PAT_XYOFS                           *(volatile kal_uint32 *)(G2D_base + 0x00A0)

#define REG_G2D_MSK_BASE                            *(volatile kal_uint32 *)(G2D_base + 0x00C0)
#define REG_G2D_MSK_PITCH                           *(volatile kal_uint32 *)(G2D_base + 0x00C4)
#define REG_G2D_MSK_XY                              *(volatile kal_uint32 *)(G2D_base + 0x00C8)
#define REG_G2D_MSK_SIZE                            *(volatile kal_uint32 *)(G2D_base + 0x00CC)
#define REG_G2D_MSK_XYOFS                           *(volatile kal_uint32 *)(G2D_base + 0x00D0)

#define REG_G2D_IDX_BASE                            *(volatile kal_uint32 *)(G2D_base + 0x00F0)

#define REG_G2D_CLIP_MIN                            *(volatile kal_uint32 *)(G2D_base + 0x0100)
#define REG_G2D_CLIP_MAX                            *(volatile kal_uint32 *)(G2D_base + 0x0104)

#define REG_G2D_RECTANGLE_FILL_START_COLOR          *(volatile kal_uint32 *)(G2D_base + 0x0110)
#define REG_G2D_FGCLR                               *(volatile kal_uint32 *)(G2D_base + 0x0110)
#define REG_G2D_BGCLR                               *(volatile kal_uint32 *)(G2D_base + 0x0114)
#define REG_G2D_ROP_CODE                            *(volatile kal_uint32 *)(G2D_base + 0x0118)

//#define REG_G2D_INDEX_COLOR_BUFFER_ADDR           *(volatile kal_uint32 *)(G2D_base + 0x0430)

//#define REG_G2D_CUR_RD_ADDR                       *(volatile kal_uint32 *)(G2D_base + 0x044c)
#define REG_G2D_SAD_SUM                             *(volatile kal_uint32 *)(G2D_base + 0x0130)
#define REG_G2D_SAD_PAR                             *(volatile kal_uint32 *)(G2D_base + 0x0134)

#define REG_G2D_EXE_ID_0                            *(volatile kal_uint32 *)(G2D_base + 0x0138)
#define REG_G2D_EXE_ID_1                            *(volatile kal_uint32 *)(G2D_base + 0x013C)

#define REG_G2D_AULB_0201                           *(volatile kal_uint32 *)(G2D_base + 0x0090)
#define REG_G2D_AULB_03                             *(volatile kal_uint32 *)(G2D_base + 0x0094)
#define REG_G2D_AULB_0504                           *(volatile kal_uint32 *)(G2D_base + 0x0098)
#define REG_G2D_AULB_0706                           *(volatile kal_uint32 *)(G2D_base + 0x009C)
#define REG_G2D_AULB_0908                           *(volatile kal_uint32 *)(G2D_base + 0x00A0)
#define REG_G2D_AULB_1110                           *(volatile kal_uint32 *)(G2D_base + 0x00C0)
#define REG_G2D_AULB_12                             *(volatile kal_uint32 *)(G2D_base + 0x00C4)
#define REG_G2D_AULB_1413                           *(volatile kal_uint32 *)(G2D_base + 0x00C8)
#define REG_G2D_AULIB_0201                          *(volatile kal_uint32 *)(G2D_base + 0x00CC)
#define REG_G2D_AULIB_0403                          *(volatile kal_uint32 *)(G2D_base + 0x00D0)
#define REG_G2D_AULIB_0605                          *(volatile kal_uint32 *)(G2D_base + 0x00F0)
#define REG_G2D_AULIB_0807                          *(volatile kal_uint32 *)(G2D_base + 0x0160)
#define REG_G2D_AULIB_1009                          *(volatile kal_uint32 *)(G2D_base + 0x0164)
#define REG_G2D_AULIB_1211                          *(volatile kal_uint32 *)(G2D_base + 0x0168)
#define REG_G2D_AULIB_1413                          *(volatile kal_uint32 *)(G2D_base + 0x016C)

#define REG_RMMU_MMU_CON                            *(volatile kal_uint32 *)(G2D_base + 0x0800)
#define REG_RMMU_VIR_BASE                           *(volatile kal_uint32 *)(G2D_base + 0x0804)
#define REG_RMMU_PAGE_BASE                          *(volatile kal_uint32 *)(G2D_base + 0x0808)
#define REG_RMMU_PAGE_SIZE                          *(volatile kal_uint32 *)(G2D_base + 0x080C)
#define REG_RMMU_INT_BASE                           *(volatile kal_uint32 *)(G2D_base + 0x0810)
#define REG_RMMU_INT_SIZE                           *(volatile kal_uint32 *)(G2D_base + 0x0814)
#define REG_RMMU_RESET                              *(volatile kal_uint32 *)(G2D_base + 0x0820)
#define REG_RMMU_STA                                *(volatile kal_uint32 *)(G2D_base + 0x0824)
#define REG_RMMU_IRQ_FLAG                           *(volatile kal_uint32 *)(G2D_base + 0x0830)

// G2D_FMODE_CON
#define G2D_FMODE_CON_PAT_CLR_MODE_MASK                 0x0000E000
    #define G2D_FMODE_CON_PAT_CLR_LUT_DIS                           0x00000000
    #define G2D_FMODE_CON_PAT_CLR_RGB565                            0x00002000
    #define G2D_FMODE_CON_PAT_CLR_ARGB8888                          0x00004000
    #define G2D_FMODE_CON_PAT_CLR_RGB888                            0x00006000
#define G2D_FMODE_CON_PAT_SWAP                          0x00001000
#define G2D_FMODE_CON_SRC_CLR_MODE_MASK                 0x00000E00
    #define G2D_FMODE_CON_SRC_CLR_LUT_DIS                           0x00000000
    #define G2D_FMODE_CON_SRC_CLR_RGB565                            0x00000200
    #define G2D_FMODE_CON_SRC_CLR_ARGB8888                          0x00000400
    #define G2D_FMODE_CON_SRC_CLR_RGB888                            0x00000600
    #define G2D_FMODE_CON_SRC_CLR_PARGB8888                         0x00000C00
#define G2D_FMODE_CON_SRC_SWAP                          0x00000100
#define G2D_FMODE_CON_DST_CLR_MODE_MASK                 0x000000E0
    #define G2D_FMODE_CON_DST_CLR_LUT_DIS                           0x00000000
    #define G2D_FMODE_CON_DST_CLR_RGB565                            0x00000020
    #define G2D_FMODE_CON_DST_CLR_ARGB8888                          0x00000040
    #define G2D_FMODE_CON_DST_CLR_RGB888                            0x00000060
    #define G2D_FMODE_CON_DST_CLR_PARGB8888                         0x000000C0
#define G2D_FMODE_CON_DST_SWAP                          0x00000010
#define G2D_FMODE_CON_ENG_MODE_MASK                     0x0000000F
    #define G2D_FMODE_CON_ENG_RECTFILL                              0x00000000
    #define G2D_FMODE_CON_ENG_BITBLT                                0x00000005

// G2D_SMODE_CON
#define G2D_SMODE_CON_FNBG                              0x40000000
#define G2D_SMODE_CON_FMSB_FIRST                        0x20000000
#define G2D_SMODE_CON_CLR_REPEN                         0x08000000
#define G2D_SMODE_CON_BB_MODE_MASK                      0x03000000
    #define G2D_SMODE_CON_BB_NORMAL                                 0x00000000
    #define G2D_SMODE_CON_BB_ALPHA_BLEND                            0x01000000
    #define G2D_SMODE_CON_BB_ROP3                                   0x02000000
    #define G2D_SMODE_CON_BB_ROP4                                   0x03000000
#define G2D_SMODE_CON_ALPHA_MASK                        0x00FF0000
#define G2D_SMODE_CON_FONT_IDX                          0x00008000
#define G2D_SMODE_CON_BIDX_EN                           0x00004000
#define G2D_SMODE_CON_BIDX_MASK                         0x00003000
    #define G2D_SMODE_CON_BIDX_1_BIT                                0x00000000
    #define G2D_SMODE_CON_BIDX_2_BIT                                0x00001000
    #define G2D_SMODE_CON_BIDX_4_BIT                                0x00002000
    #define G2D_SMODE_CON_BIDX_8_BIT                                0x00003000
#define G2D_SMODE_CON_SRC_SCAN_MASK                     0x000000F0
#define G2D_SMODE_CON_DST_SCAN_MASK                     0x0000000F

// G2D_COM_CON
#define G2D_COM_CON_TIDLE_RST                           0x00008000
#define G2D_COM_CON_ALP_TRP                             0x00000100
#define G2D_COM_CON_DSTKEY_EN                           0x00000080
#define G2D_COM_CON_SAD_EN                              0x00000010
#define G2D_COM_CON_CLP_EN                              0x00000004
#define G2D_COM_CON_SRCKEY_EN                           0x00000002
#define G2D_COM_CON_RST                                 0x00000001

// G2D_IRQ_CON
#define G2D_IRQ_CON_EN                                  0x00000001

// G2D_COM_STA
#define G2D_COM_STA_TBUSY                               0x00000002
#define G2D_COM_STA_BUSY                                0x00000001

// REG_RMMU_MMU_CON
#define G2D_RMMU_MMU_CON_EN                             0x00000001
#define G2D_RMMU_MMU_CON_BYPASS                         0x00000002
#define G2D_RMMU_MMU_CON_FWD                            0x00000004
#define G2D_RMMU_MMU_CON_WRAP                           0x00000008
#define G2D_RMMU_IRQ_FLAG_MASK                          0x00000003

#define G2D_READ_BURST_TYPE_MASK                            0x30000000
#define G2D_WRITE_BURST_TYPE_MASK                           0x0E000000
#define G2D_SLOW_DOWN_COUNT_MASK                            0x0000FFFF
#define G2D_SLOW_DOWN_ENABLE_BIT                            0x80000000

#define G2D_SAD_PARAMETER_WIDTH_MOD_MASK                    0x00000300
#define G2D_SAD_PARAMETER_DST_X_OFFSET_MASK                 0x00000030
#define G2D_SAD_PARAMETER_SRC_X_OFFSET_MASK                 0x00000003


#define RESET_G2D_ENGINE                                                                                        \
  do {                                                                                                          \
    REG_G2D_COM_CON |= G2D_COM_CON_RST ;                                                \
    REG_G2D_COM_CON &= ~G2D_COM_CON_RST;                                                \
  } while(0)

#define ENABLE_G2D_ENGINE_INT                                                                                   \
  do {                                                                                                          \
    REG_G2D_IRQ_CON = 1;                                                                                       \
  } while(0)

#define DISABLE_G2D_ENGINE_INT                                                                                  \
  do {                                                                                                          \
    REG_G2D_IRQ_CON = 0;                                                                                       \
  } while(0)  

/// for command queue
/*
#define REG_G2D_CMQ_CTRL                                    *(volatile kal_uint32 *)(GCMQ_base + 0x0000)

#define G2D_CMQ_STATUS_REG                                  (GCMQ_base + 0x0004)
#define G2D_CMQ_DATA_REG                                    (GCMQ_base + 0x0008)
#define G2D_CMQ_BASE_ADDR_REG                               (GCMQ_base + 0x000C)
#define G2D_CMQ_BUFFER_LENGTH_REG                           (GCMQ_base + 0x0010)

#define ENABLE_G2D_CMQ                                                                                          \
  do {                                                                                                          \
    REG_G2D_CMQ_CTRL=1;                                                                                         \
  } while(0) 

#define DISABLE_G2D_CMQ                                                                                         \
  do {                                                                                                          \
    REG_G2D_CMQ_CTRL &=0xFE;                                                                                    \
  } while(0)


/// for command queue

#define G2D_CMQ_LENGTH                                          256
#define REG_G2D_CMQ_CTRL                                        *(volatile kal_uint32 *)(GCMQ_base + 0x0000)
#define REG_G2D_CMQ_STATUS                                      *(volatile kal_uint32 *)(GCMQ_base + 0x0004)
#define REG_G2D_CMQ_QUEUE_BASE_ADDR                             *(volatile kal_uint32 *)(GCMQ_base + 0x000C)
#define REG_G2D_CMQ_QUEUE_LENGTH                                *(volatile kal_uint32 *)(GCMQ_base + 0x0010)
#define REG_G2D_CMQ_QUEUE_WRITE_POINTER                         *(volatile kal_uint32 *)(GCMQ_base + 0x0014)
#define REG_G2D_CMQ_QUEUE_CURRENT_POINTER                       *(volatile kal_uint32 *)(GCMQ_base + 0x0018)

#define REG_G2D_CMQ_STATUS_QUEUE_IS_EMPTY_BIT                   0x00010000
#define REG_G2D_CMQ_CTRL_BURST_MODE_BIT                         0x00000002
                                    

#define G2D_CMQ_LENGTH                     256

#define G2D_CMQ_FIRE_MODE_CTRL_REG_ADDR         (0x0100 << 16)
#define G2D_CMQ_SUBMODE_CTRL_REG_ADDR           (0x0104 << 16)
#define G2D_CMQ_2D_COMMON_CTRL_REG_ADDR         (0x0108 << 16)
#define G2D_CMQ_FIRE_CTRL_REG_ADDR              (0x0100 << 16)
#define G2D_CMQ_SUBMODE_CTRL_REG_ADDR           (0x0104 << 16)
#define G2D_CMQ_COMM_CTRL_REG_ADDR              (0x0108 << 16)
#define G2D_CMQ_INT_CTRL_REG_ADDR               (0x010C << 16)
#define G2D_CMQ_STATUS_REG_ADDR                 (0x0110 << 16)
#define G2D_CMQ_SRC_BASE_ADDRESS_REG_ADDR       (0x0200 << 16)
#define G2D_CMQ_TRIANGLE_SLOPE_L_REG_ADDR       (0x0200 << 16)
#define G2D_CMQ_SRC_PITCH_REG_ADDR              (0x0204 << 16)
#define G2D_CMQ_SRC_XY_REG_ADDR                 (0x0208 << 16)
#define G2D_CMQ_SRC_WIDTH_HEIGHT_REG_ADDR       (0x020C << 16)
#define G2D_CMQ_SRC_KEY_COLOR_REG_ADDR          (0x0210 << 16)
#define G2D_CMQ_AVOIDANCE_COLOR_REG_ADDR        (0x0214 << 16)
#define G2D_CMQ_REPLACEMENT_COLOR_REG_ADDR      (0x0218 << 16)
#define G2D_CMQ_DST_BASE_ADDRESS_REG_ADDR       (0x0300 << 16)
#define G2D_CMQ_DST_PITCH_REG_ADDR              (0x0304 << 16)
#define G2D_CMQ_DST_XY_REG_ADDR                 (0x0308 << 16)
#define G2D_CMQ_XY_START_REG_ADDR               (0x0308 << 16)
#define G2D_CMQ_CIRCLE_CENTER_REG_ADDR          (0x0308 << 16)
#define G2D_CMQ_BEZIER_XY_START_REG_ADDR        (0x0308 << 16)
#define G2D_CMQ_XY_END_REG_ADDR                 (0x030C << 16)
#define G2D_CMQ_CIRCLE_RADIUS_REG_ADDR          (0x030C << 16)
#define G2D_CMQ_BEZIER_XY_MIDDLE_REG_ADDR       (0x030C << 16)
#define G2D_CMQ_TRIANGLE_Y_END_REG_ADDR         (0x030C << 16)
#define G2D_CMQ_BEZIER_XY_END_REG_ADDR          (0x0310 << 16)
#define G2D_CMQ_DST_WIDTH_HEIGHT_REG_ADDR       (0x0318 << 16)
#define G2D_CMQ_POLYGON_PAT_START_XY_REG_ADDR   (0x0320 << 16)
#define G2D_CMQ_POLYGON_PAT_PITCH_REG_ADDR      (0x0324 << 16)
#define G2D_CMQ_START_COLOR_REG_ADDR            (0x0400 << 16)
#define G2D_CMQ_PAT_FG_COLOR_REG_ADDR           (0x0400 << 16)
#define G2D_CMQ_PAT_BG_COLOR_REG_ADDR           (0x0404 << 16)
#define G2D_CMQ_LINE_XY_SQRT_REG_ADDR           (0x0404 << 16)
#define G2D_CMQ_CLP_MIN_REG_ADDR                (0x0408 << 16)
#define G2D_CMQ_CLP_MAX_REG_ADDR                (0x040C << 16)
#define G2D_CMQ_ALPHA_GRADIENT_X_REG_ADDR       (0x0410 << 16)
#define G2D_CMQ_RED_GRADIENT_X_REG_ADDR         (0x0414 << 16)
#define G2D_CMQ_BEZIER_SUBDIV_TIME_REG_ADDR     (0x0414 << 16)
#define G2D_CMQ_GREEN_GRADIENT_X_REG_ADDR       (0x0418 << 16)
#define G2D_CMQ_BLUE_GRADIENT_X_REG_ADDR        (0x0418 << 16)
#define G2D_CMQ_ALPHA_GRADIENT_Y_REG_ADDR       (0x0420 << 16)
#define G2D_CMQ_RED_GRADIENT_Y_REG_ADDR         (0x0424 << 16)
#define G2D_CMQ_GREEN_GRADIENT_Y_REG_ADDR       (0x0428 << 16)
#define G2D_CMQ_BLUE_GRADIENT_Y_REG_ADDR        (0x042C << 16)
#define G2D_CMQ_BEZIER_BUFFER_ADDR_REG_ADDR     (0x0430 << 16)
#define G2D_CMQ_LINE_COPY_MASK_ADDR_REG_ADDR    (0x0430 << 16)
#define G2D_CMQ_TRIANGLE_SLOPE_R_REG_ADDR       (0x0430 << 16)
#define G2D_CMQ_POLYGON_EDGE_BUFFER_REG_ADDR    (0x0434 << 16)
#define G2D_CMQ_POLYGON_PAT_BUFFER_REG_ADDR     (0x0438 << 16)
#define G2D_CMQ_TILT_BASE_REG_ADDR              (0x0700 << 16)
*/

#endif /* g2d_drv_6573.h */


