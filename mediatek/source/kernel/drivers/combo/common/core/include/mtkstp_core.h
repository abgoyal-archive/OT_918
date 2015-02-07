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


#ifndef __MTKSTP_INTERNAL_H__
#define __MTKSTP_INTERNAL_H__

#include "mtkstp.h"

#define MTKSTP_CRC_SIZE 	(2)
#define MTKSTP_HEADER_SIZE  (4)
#define MTKSTP_SEQ_SIZE     (8)

/*#define MTKSTP_WINSIZE      (4)*/
#define MTKSTP_WINSIZE      (7)
#define MTKSTP_TX_TIMEOUT   (180) /*TODO: Baudrate to decide this*/
#define MTKSTP_RETRY_LIMIT  (10)

#define INDEX_INC(idx)  \
{                       \
    idx++;              \
    idx &= 0x7;         \
}

#define INDEX_DEC(idx)  \
{                       \
    idx--;              \
    idx &= 0x7;         \
}

typedef enum
{
    MTKSTP_SYNC = 0,
    MTKSTP_SEQ,
    MTKSTP_ACK,
    MTKSTP_NAK,
    MTKSTP_TYPE,
    MTKSTP_LENGTH,
    MTKSTP_CHECKSUM,
    MTKSTP_DATA,
    MTKSTP_CRC1,
    MTKSTP_CRC2,
    MTKSTP_RESYNC1,
    MTKSTP_RESYNC2,
    MTKSTP_RESYNC3,
    MTKSTP_RESYNC4,
    MTKSTP_FW_MSG,
} mtkstp_parser_state;


typedef struct
{
    mtkstp_parser_state  state;
    UINT8            seq;
    UINT8            ack;
    UINT8            nak;
    UINT8            type;
    UINT16           length;
    UINT8            checksum;
    UINT16           crc;
} mtkstp_parser_context_struct;


typedef struct
{
    UINT8           txseq;  // last tx pkt's seq + 1
    UINT8           txack;  // last tx pkt's ack
    UINT8           rxack;  // last rx pkt's ack
    UINT8           winspace;   // current sliding window size
    UINT8           expected_rxseq;  // last rx pkt's seq + 1
    UINT8           retry_times;
} mtkstp_sequence_context_struct;

typedef struct
{
    MTK_WCN_MUTEX           mtx;
    UINT8           buffer[MTKSTP_BUFFER_SIZE];
    UINT32          read_p;
    UINT32          write_p;
} mtkstp_ring_buffer_struct;

typedef struct
{
    UINT8  inband_rst_set;
    UINT32 rx_counter;  // size of current processing pkt in rx_buf[]
    UINT8  rx_buf[MTKSTP_BUFFER_SIZE];  // input buffer of STP, room for current processing pkt
    UINT32 tx_read;     // read ptr of tx_buf[]
    UINT32 tx_write;    // write ptr of tx_buf[]
    UINT8  tx_buf[MTKSTP_BUFFER_SIZE];  // output buffer of STP
    UINT32 tx_start_addr[MTKSTP_SEQ_SIZE];  // ptr of each pkt in tx_buf[]
    UINT32 tx_length[MTKSTP_SEQ_SIZE];      // length of each pkt in tx_buf[]
    mtkstp_ring_buffer_struct ring[MTKSTP_MAX_TASK_NUM];    // ring buffers for each function driver
    mtkstp_parser_context_struct parser;        // current rx pkt's content
    mtkstp_sequence_context_struct sequence;    // state machine's current status
    MTK_WCN_MUTEX stp_mutex;
    MTK_WCN_TIMER tx_timer; // timer for tx timeout handling
}mtkstp_context_struct;

#endif

