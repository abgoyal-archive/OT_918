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


/*! \file   WMT_exp.h
    \brief  Declaration of functions provided by WMT_DRV

    Any definitions in this file will be shared among GLUE Layer and internal Driver Stack.
*/

/*******************************************************************************
* Copyright (c) 2009 MediaTek Inc.
*
* All rights reserved. Copying, compilation, modification, distribution
* or any other use whatsoever of this material is strictly prohibited
* except in accordance with a Software License Agreement with
* MediaTek Inc.
********************************************************************************
*/

/*******************************************************************************
* LEGAL DISCLAIMER
*
* BY OPENING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND
* AGREES THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK
* SOFTWARE") RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE
* PROVIDED TO BUYER ON AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY
* DISCLAIMS ANY AND ALL WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT
* LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
* PARTICULAR PURPOSE OR NONINFRINGEMENT. NEITHER DOES MEDIATEK PROVIDE
* ANY WARRANTY WHATSOEVER WITH RESPECT TO THE SOFTWARE OF ANY THIRD PARTY
* WHICH MAY BE USED BY, INCORPORATED IN, OR SUPPLIED WITH THE MEDIATEK
* SOFTWARE, AND BUYER AGREES TO LOOK ONLY TO SUCH THIRD PARTY FOR ANY
* WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE
* FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S SPECIFICATION OR TO
* CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
*
* BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE
* LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL
* BE, AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT
* ISSUE, OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY
* BUYER TO MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
*
* THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE
* WITH THE LAWS OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT
* OF LAWS PRINCIPLES.  ANY DISPUTES, CONTROVERSIES OR CLAIMS ARISING
* THEREOF AND RELATED THERETO SHALL BE SETTLED BY ARBITRATION IN SAN
* FRANCISCO, CA, UNDER THE RULES OF THE INTERNATIONAL CHAMBER OF COMMERCE
* (ICC).
********************************************************************************
*/

#ifndef _WMT_EXP_H
#define _WMT_EXP_H

/*******************************************************************************
*                         C O M P I L E R   F L A G S
********************************************************************************
*/

/*******************************************************************************
*                    E X T E R N A L   R E F E R E N C E S
********************************************************************************
*/

/*******************************************************************************
*                              C O N S T A N T S
********************************************************************************
*/

#define DEFAULT_WMT_MSG_CNT 0x10

typedef enum _ENUM_WMTDRV_TYPE_T {
    WMTDRV_TYPE_BT = 0,
    WMTDRV_TYPE_FM = 1,
    WMTDRV_TYPE_GPS = 2,
    WMTDRV_TYPE_WIFI = 3,
    WMTDRV_TYPE_WMT = 4,
    WMTDRV_TYPE_STP = 5,
    WMTDRV_TYPE_SDIO1 = 6,
    WMTDRV_TYPE_SDIO2 = 7,
    WMTDRV_TYPE_LPBK = 8,
    WMTDRV_TYPE_MAX
} ENUM_WMTDRV_TYPE_T, *P_ENUM_WMTDRV_TYPE_T;

typedef enum _ENUM_CMD_TYPE_T {
    WMTDRV_CMD_ASSERT = 0,
    WMTDRV_CMD_EXCEPTION = 1,
    WMTDRV_CMD_COEXDBG_00 = 2,
    WMTDRV_CMD_COEXDBG_01 = 3,
    WMTDRV_CMD_COEXDBG_02 = 4,
    WMTDRV_CMD_COEXDBG_03 = 5,
    WMTDRV_CMD_COEXDBG_04 = 6,
    WMTDRV_CMD_COEXDBG_05 = 7,
    WMTDRV_CMD_COEXDBG_06 = 8,
    WMTDRV_CMD_COEXDBG_07 = 9,
    WMTDRV_CMD_COEXDBG_08 = 10,
    WMTDRV_CMD_COEXDBG_09 = 11,
    WMTDRV_CMD_COEXDBG_10 = 12,
    WMTDRV_CMD_COEXDBG_11 = 13,
    WMTDRV_CMD_COEXDBG_12 = 14,
    WMTDRV_CMD_COEXDBG_13 = 15,
    WMTDRV_CMD_COEXDBG_14 = 16,
    WMTDRV_CMD_COEXDBG_15 = 17,    
    WMTDRV_CMD_MAX
} ENUM_WMTDRV_CMD_T, *P_ENUM_WMTDRV_CMD_T;

typedef enum _ENUM_WMTMSG_TYPE_T {
    WMTMSG_TYPE_POWER_ON = 0,
    WMTMSG_TYPE_POWER_OFF = 1,
    WMTMSG_TYPE_RESET = 2,
    WMTMSG_TYPE_STP_RDY= 3,
    WMTMSG_TYPE_HW_FUNC_ON= 4,
    WMTMSG_TYPE_MAX
} ENUM_WMTMSG_TYPE_T, *P_ENUM_WMTMSG_TYPE_T;

typedef enum _ENUM_WMTDSNS_TYPE_T{
    WMTDSNS_FM_DISABLE = 0, 
    WMTDSNS_FM_ENABLE = 1,
    WMTDSNS_MAX
} ENUM_WMTDSNS_TYPE_T, *P_ENUM_WMTDSNS_TYPE_T;

typedef enum _ENUM_WMTTHERM_TYPE_T{
	WMTTHERM_ZERO = 0,
	WMTTHERM_ENABLE = WMTTHERM_ZERO + 1,
	WMTTHERM_READ = WMTTHERM_ENABLE + 1,	
    WMTTHERM_DISABLE = WMTTHERM_READ + 1,
    WMTTHERM_MAX
}ENUM_WMTTHERM_TYPE_T, *P_ENUM_WMTTHERM_TYPE_T;

typedef enum _ENUM_WMTHWVER_TYPE_T{
    WMTHWVER_MT6620_E1 = 0x0,
    WMTHWVER_MT6620_E2 = 0x1,
    WMTHWVER_MT6620_E3 = 0x2,
    WMTHWVER_MT6620_E4 = 0x3,
    WMTHWVER_MT6620_E5 = 0x4,
    WMTHWVER_MT6620_E6 = 0x5,
    WMTHWVER_MT6620_MAX,
    WMTHWVER_INVALID = 0xff
} ENUM_WMTHWVER_TYPE_T, *P_ENUM_WMTHWVER_TYPE_T;

typedef enum _ENUM_WMTRSTMSG_TYPE_T{
    WMTRSTMSG_RESET_START = 0x0,
    WMTRSTMSG_RESET_END = 0x1,
    WMTRSTMSG_RESET_MAX,
    WMTRSTMSG_RESET_INVALID = 0xff
} ENUM_WMTRSTMSG_TYPE_T, *P_ENUM_WMTRSTMSG_TYPE_T;

typedef enum _ENUM_WMTRSTSRC_TYPE_T{
    WMTRSTSRC_RESET_BT = 0x0,
    WMTRSTSRC_RESET_FM = 0x1,
    WMTRSTSRC_RESET_GPS = 0x2,
    WMTRSTSRC_RESET_WIFI = 0x3,
    WMTRSTSRC_RESET_STP = 0x4,
    WMTRSTSRC_RESET_TEST = 0x5,
    WMTRSTSRC_RESET_MAX 
} ENUM_WMTRSTSRC_TYPE_T, *P_ENUM_WMTRSTSRC_TYPE_T;

typedef enum _ENUM_WMTRSTRET_TYPE_T{
    WMTRSTRET_SUCCESS = 0x0,
    WMTRSTRET_FAIL = 0x1,
    WMTRSTRET_ONGOING = 0x2,
    WMTRSTRET_MAX
} ENUM_WMTRSTRET_TYPE_T, *P_ENUM_WMTRSTRET_TYPE_T;


/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/
typedef void (*PF_WMT_CB)(
    ENUM_WMTDRV_TYPE_T, /* Source driver type */
    ENUM_WMTDRV_TYPE_T, /* Destination driver type */
    ENUM_WMTMSG_TYPE_T, /* Message type */
    void *, /* READ-ONLY buffer. Buffer is allocated and freed by WMT_drv. Client
            can't touch this buffer after this function return. */
    unsigned int /* Buffer size in unit of byte */
    );

typedef struct _WMT_REGISTER_CLIENT
{
    /* IOCTL_WMT_REGISTER_CLIENT */
    ENUM_WMTDRV_TYPE_T eType;
    PF_WMT_CB pWmtCb;
} WMT_REGISTER_CLIENT, *P_WMT_REGISTER_CLIENT;

typedef struct _WMTDRV_MSG
{
    ENUM_WMTDRV_TYPE_T eSrcType;
    ENUM_WMTDRV_TYPE_T eDestType;
    ENUM_WMTMSG_TYPE_T eMsgType;
    unsigned char aucMsgBuf[16];
    unsigned int dwBufSize;
} WMTDRV_MSG, *P_WMTDRV_MSG;

/*******************************************************************************
*                            P U B L I C   D A T A
********************************************************************************
*/

/*******************************************************************************
*                           P R I V A T E   D A T A
********************************************************************************
*/
/*******************************************************************************
*                                 M A C R O S
********************************************************************************
*/

/*******************************************************************************
*                  F U N C T I O N   D E C L A R A T I O N S
********************************************************************************
*/

/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/
extern MTK_WCN_BOOL wmt_cdev_hw_rst(VOID);
extern MTK_WCN_BOOL wmt_cdev_sw_rst(INT32 baud_set, INT32 full_set);
extern int wmt_cdev_rstmsg_snd(ENUM_WMTRSTMSG_TYPE_T msg);

extern int mtk_wcn_wmt_client_reg (ENUM_WMTDRV_TYPE_T eType, PF_WMT_CB pCb, PVOID pTypeCb);
extern int mtk_wcn_wmt_client_unreg(ENUM_WMTDRV_TYPE_T eType);
extern MTK_WCN_BOOL mtk_wcn_wmt_func_on (ENUM_WMTDRV_TYPE_T eType);
extern MTK_WCN_BOOL mtk_wcn_wmt_func_off (ENUM_WMTDRV_TYPE_T eType);
extern MTK_WCN_BOOL mtk_wcn_wmt_cmd_test (ENUM_WMTDRV_CMD_T cmd);
extern INT32 mtk_wcn_wmt_cmd_test_ext (ENUM_WMTDRV_CMD_T cmd, UINT8 *addr, UINT32 count);
extern MTK_WCN_BOOL mtk_wcn_wmt_dsns_ctrl (ENUM_WMTDSNS_TYPE_T eType);
extern ENUM_WMTRSTRET_TYPE_T mtk_wcn_wmt_combo_rst(ENUM_WMTRSTSRC_TYPE_T src);
extern int mtk_wcn_wmt_msgcb_reg(ENUM_WMTDRV_TYPE_T eType,PF_WMT_CB pCb);
extern int mtk_wcn_wmt_msgcb_unreg(ENUM_WMTDRV_TYPE_T eType);
extern ENUM_WMTHWVER_TYPE_T mtk_wcn_wmt_hwver_get(VOID);

extern INT8 mtk_wcn_wmt_therm_ctrl (ENUM_WMTTHERM_TYPE_T eCtrlType);

#endif /* _WMT_EXP_H */

