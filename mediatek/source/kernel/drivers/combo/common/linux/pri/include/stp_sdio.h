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

/*
** $Id: $
*/

/*! \file   "stp_sdio.h"
    \brief


*/

/*
** $Log: $
*/

#ifndef _STP_SDIO_H
#define _STP_SDIO_H
/*******************************************************************************
*                         C O M P I L E R   F L A G S
********************************************************************************
*/


/*******************************************************************************
*                    E X T E R N A L   R E F E R E N C E S
********************************************************************************
*/
#include "mtk_porting.h"

/*******************************************************************************
*                              C O N S T A N T S
********************************************************************************
*/
/* Common HIF register address */
#define CCIR		(0x0000)
#define CHLPCR		(0x0004)
#define CSDIOCSR	(0x0008)
#define CHCR		(0x000c)
#define CHISR		(0x0010)
#define CHIER		(0x0014)
#define CTDR		(0x0018)
#define CRDR		(0x001c)
#define CTFSR		(0x0020)
#define CRPLR		(0x0024)

/* Common HIF register bit field address */
/* CHLPCR */
#define C_FW_OWN_REQ_CLR    (0x00000200)
#define C_FW_OWN_REQ_SET    (0x00000100)
#define C_FW_INT_EN_CLR     (0x00000002)
#define C_FW_INT_EN_SET     (0x00000001)
/* CHIER */
#define CHISR_EN_15_7       (0x0000ff80)
#define CHISR_EN_3_0        (0x0000000f)
/* CHISR */
#define RX_PKT_LEN          (0xffff0000)
#define FIRMWARE_INT        (0x0000fe00)
#define TX_FIFO_OVERFLOW    (0x00000100)
#define FW_INT_IND_INDICATOR (0x00000080)
#define TX_COMPLETE_COUNT   (0x00000070)
#define TX_UNDER_THOLD      (0x00000008)
#define TX_EMPTY            (0x00000004)
#define RX_DONE             (0x00000002)
#define FW_OWN_BACK_INT     (0x00000001)

#define STP_SDIO_BLK_SIZE       (512)
#define STP_SDIO_TX_BUF_CNT     (7)
#define STP_SDIO_TX_FIFO_SIZE   (2080)
#define STP_SDIO_RX_FIFO_SIZE   (2304)
#define STP_SDIO_TX_PKT_LIST_SIZE (7)

#define STP_SDIO_TX_ENTRY_SIZE (256*5)
/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/
/* HIF's local packet buffer variables for Tx/Rx */
typedef struct _MTK_WCN_STP_SDIO_PKT_BUF {
	UINT8 tx_buf[STP_SDIO_TX_BUF_CNT][STP_SDIO_TX_ENTRY_SIZE];   /* Tx local ring buffer */
	UINT8 rx_buf[STP_SDIO_RX_FIFO_SIZE]; /* Rx local ring buffer */
	UINT8 rd_idx;  /* Tx ring buffer read index */
	UINT8 wr_idx;  /* Tx ring buffer write index */
	MTK_WCN_BOOL full_flag; /* Tx ring buffer full flag (TRUE: full, FALSE: not full) */
	spinlock_t rd_idx_lock; /* spin lock for Tx ring buffer read index */
	unsigned long rd_irq_flag; /* save interrupt status flag for Tx ring buf spin lock */
	wait_queue_head_t fullwait_q; /* wait queue head for Tx ring buf full case */
} MTK_WCN_STP_SDIO_PKT_BUF;

/* Tx packet list information */
typedef struct _MTK_WCN_STP_SDIO_Tx_Pkt_LIST {
    UINT16 pkt_size_list[STP_SDIO_TX_PKT_LIST_SIZE];
    UINT8 pkt_rd_idx;
    UINT8 pkt_wr_idx;
} MTK_WCN_STP_SDIO_Tx_Pkt_LIST;

/* STP HIF firmware information */
typedef struct _MTK_WCN_STP_SDIO_FIRMWARE_INFO {
    UINT32 tx_fifo_size;    /* Current Tx FIFO size */
    UINT8 tx_packet_num;    /* Limit the tx packet num from 0~7 */
} MTK_WCN_STP_SDIO_FIRMWARE_INFO;

/* STP SDIO private information */
typedef struct _MTK_WCN_STP_SDIO_PRIVATE_INFO {
    UINT8 stp_sdio_host_idx;
} MTK_WCN_STP_SDIO_PRIVATE_INFO;

/* STP SDIO host information */
typedef struct _MTK_WCN_STP_SDIO_HIF_HOSTINFO {
		MTK_WCN_HIF_SDIO_CLTCTX sdio_cltctx;
		MTK_WCN_STP_SDIO_PKT_BUF pkt_buf;
		MTK_WCN_STP_SDIO_Tx_Pkt_LIST tx_pkt_list;
		UINT16 rx_ptk_len; /* Rx packet len (unit of byte) gotten from CHISR */
		MTK_WCN_BOOL rx_intr_mask;  /* Rx interrupt mask (TRUE:masked, FALSE:un-masked) */
		MTK_WCN_STP_SDIO_FIRMWARE_INFO firmware_info;
		MTK_WCN_STP_SDIO_PRIVATE_INFO private_info;
        struct work_struct tx_work;
		struct work_struct rx_work;
} MTK_WCN_STP_SDIO_HIF_HOSTINFO;

#if 0
/* Elements in CHISR */
struct _MTK_WCN_STP_SDIO_CHISR_INFO {
    UINT16 u2RxPktLen;
    UINT8 ucFwInt;
    MTK_WCN_BOOL bTxFifoOverflow;
    MTK_WCN_BOOL bFwInt;
    UINT8 ucTxCompleteCount;
    MTK_WCN_BOOL bTxFifoUnderThold;
    MTK_WCN_BOOL bTxEmpty;
    MTK_WCN_BOOL bRxDoneInt;
    MTK_WCN_BOOL bFwOwnBackInt;
};
#endif

#if 0 /* error code definitions */
/* error code returned by hif_sdio driver (use NEGATIVE number) */
typedef enum {
    HIF_SDIO_ERR_SUCCESS = 0,
    HIF_SDIO_ERR_FAIL, /* generic error */
    HIF_SDIO_ERR_INVALID_PARAM,
    HIF_SDIO_ERR_DUPLICATED,
    HIF_SDIO_ERR_UNSUP_MANF_ID,
    HIF_SDIO_ERR_UNSUP_CARD_ID,
    HIF_SDIO_ERR_INVALID_FUNC_NUM,
    HIF_SDIO_ERR_INVALID_BLK_SZ,
} MTK_WCN_HIF_SDIO_ERR ;
#endif

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
*                   F U N C T I O N   D E C L A R A T I O N S
********************************************************************************
*/

/*!
 * \brief MTK hif sdio client registration function
 *
 * Client uses this function to do hif sdio registration
 *
 * \param pinfo     a pointer of client's information
 *
 * \retval 0    register successfully
 * \retval < 0  error code
 */
extern INT32 mtk_wcn_hif_sdio_client_reg (
    const MTK_WCN_HIF_SDIO_CLTINFO *pinfo
    );

/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/
#endif /* _STP_SDIO_H */



