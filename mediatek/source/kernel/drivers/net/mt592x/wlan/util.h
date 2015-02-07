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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/util.h#1 $
*/

/*! \file   "util.c"
    \brief  This file provide utility function declairations for the driver

*/

/*******************************************************************************
* Copyright (c) 2007 MediaTek Inc.
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

/*
** $Log: util.h $
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\6 2008-08-11 14:07:56 GMT mtk01084
**  modify driver to meeting coding rules
*/

#ifndef _UTIL_H
#define _UTIL_H


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

/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/
#define PROTO_TCP 0x6
#define PROTO_UDP 0x11

#define MAC_ADDR_LEN  6

#define IPv4_ADDR_LEN 4

#define IPv6_ADDR_LEN 16

/* Ethernet Frame Structure */
typedef struct _eth_hdr_t_ {
    UINT_8      aucDestAddr[MAC_ADDR_LEN];
    UINT_8      aucSrcAddr[MAC_ADDR_LEN];
    UINT_16     u2TypeLen;
    UINT_8      aucData[1];
} __KAL_ATTRIB_PACKED__ eth_hdr_t, *peth_hdr_t;



typedef struct _ipv4_hdr_t_ {
    unsigned char hdrlen:4;
    unsigned char version:4;
    unsigned char tos;
    unsigned short len;
    unsigned short id;
    unsigned short flagfragoffset;
    unsigned char ttl;
    unsigned char proto;
    unsigned short hdrchecksum;
    unsigned int src;
    unsigned int dest;
} ipv4_hdr_t, *pipv4_hdr_t;

typedef struct _ipv6_hdr_t_ {
    unsigned char priority:4;
    unsigned char version:4;
    unsigned char flow_lbl[3];
    unsigned short payload_len;
    unsigned char next_hdr;
    unsigned char hop_limit;
    unsigned char saddr[16];
    unsigned char daddr[16];
} ipv6_hdr_t, *pipv6_hdr_t;

typedef struct _tcp_hdr_t_ {
    unsigned short source;
    unsigned short dest;
    unsigned int seq;
    unsigned int ack_seq;
    unsigned short fin:1,
                   syn:1,
                   rst:1,
                   psh:1,
                   ack:1,
                   urg:1,
                   ece:1,
                   cwr:1,
                   resl:4,
                   doff:4;
    unsigned short window;
    unsigned short check;
    unsigned short urg_ptr;
} tcp_hdr_t, *ptcp_hdr_t;

typedef struct _udp_hdr_t_ {
    unsigned short source;
    unsigned short dest;
    unsigned short len;
    unsigned short check;
} udp_hdr_t, *pudp_hdr_t;

typedef struct _ipv6_pseudo_hdr_t_ {
    unsigned char saddr[16];
    unsigned char daddr[16];
    unsigned int payload_len;
    unsigned char reserved[3];
    unsigned char next_hdr;
} ipv6_pseudo_hdr_t, *pipv6_pseudo_hdr_t;

typedef struct _ipv4_pseudo_hdr_t_ {
    unsigned int saddr;
    unsigned int daddr;
    unsigned int payload_len;
    unsigned char reserved[3];
    unsigned char next_hdr;
} ipv4_pseudo_hdr_t, *pipv4_pseudo_hdr_t;

typedef struct _ipv6_ext_hdr_t_ {
    unsigned char next_hdr;
    unsigned char len;
} ipv6_ext_hdr_t, *pipv6_ext_hdr_t;



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

/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/
UINT_32
utilComputeCSUM (
    IN PUINT_8 pucInput,
    IN UINT_32 u4Size,
    IN UINT_32 u4CSUM
    );

BOOLEAN
utilValidateTCPChecksum (
    IN PUINT_8 pucSAddr,
    IN PUINT_8 pucDAddr,
    IN UINT_8 ucAddrlen,
    IN PUINT_8 pucDatagram,
    IN UINT_32 ucDatalen
    );

BOOLEAN
utilValidateUDPChecksum (
    IN PUINT_8 pucSAddr,
    IN PUINT_8 pucDAddr,
    IN UINT_8 ucAddrlen,
    IN PUINT_8 pucDatagram,
    IN UINT_32 ucDatalen
    );


BOOLEAN
utilValidateIPv4Checksum (
    IN PUINT_8 pucDatagram,
    IN PUINT_8 pucProto,
    OUT P_ENUM_CSUM_RESULT_T peL4CSUMRes
    );

BOOLEAN
utilValidateIPv6Checksum (
    IN PUINT_8 pucDatagram,
    IN PUINT_8 pucProto,
    OUT P_ENUM_CSUM_RESULT_T peL4CSUMRes
    );

VOID
utilGenIPv4CSUM (
    IN PUINT_8 pucData
    );

VOID
utilGenIPv6CSUM (
    IN PUINT_8 pucData
    );

VOID
utilGenTCPCSUM (
    IN PUINT_8 pucData,
    IN UINT_32 u4Size,
    IN UINT_32 u4IPCSUM
    );

VOID
utilGenUDPCSUM (
    IN PUINT_8 pucData,
    IN UINT_32 u4Size,
    IN UINT_32 u4IPCSUM
    );

VOID
utilTxComputeCSUM (
    IN PUINT_8 pucPacket,
    IN UINT_32 u4PktLen
    );

VOID
utilRxComputeCSUM (
    IN PUINT_8 pucEtherPkt,
    IN UINT_16 u2PktLen,
    OUT ENUM_CSUM_RESULT_T aeCSUM[]
    );


#endif /* _UTIL_H */

