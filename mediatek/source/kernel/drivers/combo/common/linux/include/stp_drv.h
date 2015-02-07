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

#ifndef _STP_DRV_H_
#define _STP_DRV_H_

#include "mtk_porting.h"

#define CFG_DBG_GPIO_PINS 0

/* Platform DEPENDENT configurations: MT6516 GPIO pin name */
#define GPIO_65xx(x) (GPIO##x)
#define GPIO_PLATFORM(x) GPIO_65xx(x)

/* Platform independent configurations */
#define DBG_TIE_DIR 0x40000000UL
#define DBG_LOW 0x0UL
#define DBG_HIGH 0x1UL
#define DBG_TIE_LOW (DBG_TIE_DIR | DBG_LOW)
#define DBG_TIE_HIGH (DBG_TIE_DIR | DBG_HIGH)

#define DBG_TOGGLE(x) (0x80000000UL | x)
#define DBG_TOGGLE_NUM(x) (x & 0xFFF)

#define GPIO_INVALID 0xFFFF
typedef enum {
    IDX_ERR = 0,
    IDX_STP_RX_RESYNC,
    IDX_STP_RX_PROC,
    IDX_STP_GPS_IND,
    IDX_STP_MTX_BT,
    IDX_STP_MTX_FM, /* 5 */
    IDX_STP_MTX_GPS,
    IDX_STP_MTX_WIFI,
    IDX_STP_MTX_WMT,
    IDX_STP_MTX_STP,
    IDX_STP_ACK_PROC, /*10 */
    IDX_BT_TX,
    IDX_BT_RX,
    IDX_GPS_RX,
    IDX_GPS_2,
    IDX_GPS_3,
    IDX_GPS_TX,
    IDX_STP_MAX
} DBG_PIN;

#define DBG_MTX_OFFSET (IDX_STP_MTX_BT) /* index of mutex0 */

#if CFG_DBG_GPIO_PINS
extern void mtk_wcn_stp_debug_gpio_assert(UINT32 dwIndex, UINT32 dwMethod);
#else
static inline void mtk_wcn_stp_debug_gpio_assert(UINT32 dwIndex, UINT32 dwMethod) {};
#endif


/* export for HIF driver */
typedef INT32 (*MTK_WCN_STP_IF_TX)(const UINT8 *data, UINT32 size, UINT32 *written_size);
typedef void (*MTK_WCN_STP_IF_RX)(const UINT8 *data, INT32 size);
extern int mtk_wcn_stp_register_if_tx(MTK_WCN_STP_IF_TX func);
extern int mtk_wcn_stp_register_if_rx(MTK_WCN_STP_IF_RX func);
extern int mtk_wcn_sys_if_rx(UINT8 *data, INT32 size);

/* export for STP client driver */
typedef void (*MTK_WCN_STP_EVENT_CB)(void);
extern int mtk_wcn_stp_register_event_cb(int type, MTK_WCN_STP_EVENT_CB func);
extern int mtk_wcn_stp_register_tx_event_cb(int type, MTK_WCN_STP_EVENT_CB func);
extern MTK_WCN_BOOL mtk_wcn_stp_dbg_level(UINT32 dbglevel);
#endif

