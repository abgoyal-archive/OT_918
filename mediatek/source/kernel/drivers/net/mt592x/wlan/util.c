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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/util.c#2 $
*/

/*! \file   "util.c"
    \brief  This file provide utility functions for the driver

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
** $Log: util.c $
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\19 2009-08-18 22:55:50 GMT mtk01090
**  Add Linux SDIO (with mmc core) support.
**  Add Linux 2.6.21, 2.6.25, 2.6.26.
**  Fix compile warning in Linux.
**  \main\maintrunk.MT5921\18 2008-12-08 21:38:24 GMT mtk01461
**  Remove Lint Warning - Excessive shift value to a constant
**  \main\maintrunk.MT5921\17 2008-12-08 20:30:36 GMT mtk01425
**  1. Update for lint
**  \main\maintrunk.MT5921\16 2008-12-01 17:18:38 GMT mtk01088
**  fixed lint warninig
**  \main\maintrunk.MT5921\15 2008-08-11 14:35:41 GMT mtk01084
**  modify for meeting coding rules
**  \main\maintrunk.MT5921\14 2008-08-11 14:08:03 GMT mtk01084
**  modify driver to meeting coding rules
**  \main\maintrunk.MT5921\13 2008-02-01 13:00:15 GMT mtk01385
**  1. modify debug message output formatting.
**  \main\maintrunk.MT5921\12 2008-02-01 11:36:35 GMT mtk01385
**  1. fix CE 4.2 compiling error.
**  \main\maintrunk.MT5921\11 2008-01-31 22:31:14 GMT mtk01385
**  1. Fix CE 4.2 compiling error.
**  \main\maintrunk.MT5921\10 2007-12-24 14:53:52 GMT mtk01425
**  1. Change the parameter of utilValidateIPv6Checksum and utilValidateIPv4Checksum
**  2. Fix incorrect return value for IP fragment packets
**  \main\maintrunk.MT5921\9 2007-11-09 16:29:26 GMT mtk01425
**  1. Fix CSUM offloading when tx UDP IP fragment
**  \main\maintrunk.MT5921\8 2007-11-09 12:18:44 GMT mtk01425
**  1. Fix software tx csum offload bug
**  \main\maintrunk.MT5921\7 2007-11-09 11:32:54 GMT mtk01425
**  1. Fix csum bug in utilTxComputeCSUM
**  \main\maintrunk.MT5921\6 2007-11-09 10:59:14 GMT mtk01425
**  1. Update ntohl and ntohs to unified ones
**  \main\maintrunk.MT5921\5 2007-11-06 18:27:41 GMT mtk01425
**  1. Update for Tx Fragment
**  \main\maintrunk.MT5921\4 2007-10-26 10:33:10 GMT mtk01425
**  \main\maintrunk.MT5921\3 2007-10-24 10:24:11 GMT mtk01425
**  Test comment
*/

/*******************************************************************************
*                         C O M P I L E R   F L A G S
********************************************************************************
*/

/*******************************************************************************
*                    E X T E R N A L   R E F E R E N C E S
********************************************************************************
*/
#include "precomp.h"

/*******************************************************************************
*                              C O N S T A N T S
********************************************************************************
*/

/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/

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

/*----------------------------------------------------------------------------*/
/*!
* \brief This routines is called to compute checksum used by TCP/ IP.
*
* \param[in] pucInput Pointer to the data to be used to calculate checksum.
* \param[in] u4Size Size of the data to be used to calculate checksum.
* \param[in] u4CSUM The original checksum value.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
UINT_32
utilComputeCSUM (
    IN PUINT_8 pucInput,
    IN UINT_32 u4Size,
    IN UINT_32 u4CSUM
    )
{

    PUINT_16 pu2Input;
    UINT_32 u4Sum = 0;
    UINT_32 u4WordLen = 0;
//    UINT_8  ucTemp = 0;

    UINT_32 i = 0;
    UINT_16 u2Trail = 0; /* Fix Klocwork ABR warning */

    ASSERT(pucInput);

    u4Sum = u4CSUM;
    pu2Input = (PUINT_16)pucInput;

#if 1
    /* Fix Klocwork warning: array bound violation
    * "ucTemp = pucInput[u4Size];" access address beyond the input buffer!
    */
    u4WordLen = u4Size / 2;

    if (u4Size % 2 != 0) {
        u2Trail = (UINT_16)pucInput[u4Size-1];
        u2Trail <<= 8;
    }

    for (i = 0; i < u4WordLen; i++) {
        u4Sum += pu2Input[i];
    }
    /* add trail word (0 if length is even) */
    u4Sum += u2Trail;

#else
    if (u4Size % 2 != 0) {
        u4WordLen = (u4Size / 2) + 1;
    }
    else {
        u4WordLen = u4Size / 2;
    }

    for (i = 0; i < u4WordLen; i++) {
        if (i == u4WordLen-1) {
            ucTemp = pucInput[u4Size];
            pucInput[u4Size] = 0;
        }
        u4Sum += pu2Input[i];
    }
    pucInput[u4Size] = ucTemp;
#endif

    return u4Sum;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routines is called to validate checksum which is used by TCP.
*
* \param[in] pucSAddr Pointer to the IP source address.
* \param[in] pucDAddr Pointer to the IP destination address.
* \param[in] ucAddrlen Address length.
* \param[in] pucDatagram Pointer to the datagram to be calculating checksum.
* \param[in] u4Datalen Data length.
*
* \return TRUE TCP Checksum Correct
* \return FALSE TCP Checksum Error
*/
/*----------------------------------------------------------------------------*/
BOOLEAN
utilValidateTCPChecksum (
    IN PUINT_8 pucSAddr,
    IN PUINT_8 pucDAddr,
    IN UINT_8 ucAddrlen,
    IN PUINT_8 pucDatagram,
    IN UINT_32 u4Datalen
    )
{
    UINT_32 u4CSUM32 = 0;

    DEBUGFUNC("utilValidateTCPChecksum");

    ASSERT(pucSAddr);
    ASSERT(pucDAddr);

    u4CSUM32 = utilComputeCSUM(pucDatagram, u4Datalen, 0);
    u4CSUM32 = utilComputeCSUM(pucSAddr, ucAddrlen, u4CSUM32);
    u4CSUM32 = utilComputeCSUM(pucDAddr, ucAddrlen, u4CSUM32);
    u4CSUM32 += (HTONL(u4Datalen)&0xffff) + ((HTONL(u4Datalen)>>16) & 0xffff);
/*lint -save -e572 Excessive shift value (precision 0 shifted right by 16) Kevin: shift a constant */
    u4CSUM32 += (HTONL(0x6UL)&0xffff) + ((HTONL(0x6UL)>>16) & 0xffff);
/*lint -restore */

    while (u4CSUM32 > 0xffff) {
        u4CSUM32 = (u4CSUM32 >> 16) + (u4CSUM32 & 0xffff);
    }
    if (u4CSUM32 != 0xffff) {
        DBGLOG(RX, LOUD, ("TCP Checksum Error!\n"));
        return FALSE;
    }
    else {
        DBGLOG(RX, LOUD, ("TCP Checksum Correct!\n"));
        return TRUE;
    }


}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routines is called to validate checksum which is used by UDP.
*
* \param[in] pucSAddr Pointer to the IP source address.
* \param[in] pucDAddr Pointer to the IP destination address.
* \param[in] ucAddrlen Address length.
* \param[in] pucDatagram Pointer to the datagram to be calculating checksum.
* \param[in] u4Datalen Data length.
*
* \return TRUE UDP Checksum Correct
* \return FALSE UDP Checksum Error
*/
/*----------------------------------------------------------------------------*/
BOOLEAN
utilValidateUDPChecksum (
    IN PUINT_8 pucSAddr,
    IN PUINT_8 pucDAddr,
    IN UINT_8 ucAddrlen,
    IN PUINT_8 pucDatagram,
    IN UINT_32 ucDatalen
    )
{
    UINT_32 u4CSUM32 = 0;

    DEBUGFUNC("utilValidateUDPChecksum");

    ASSERT(pucSAddr);
    ASSERT(pucDAddr);

    u4CSUM32 = utilComputeCSUM(pucDatagram, ucDatalen, 0);
    u4CSUM32 = utilComputeCSUM(pucSAddr, ucAddrlen, u4CSUM32);
    u4CSUM32 = utilComputeCSUM(pucDAddr, ucAddrlen, u4CSUM32);
    u4CSUM32 += (HTONL(ucDatalen)&0xffff) + ((HTONL(ucDatalen)>>16) & 0xffff);
/*lint -save -e572 Excessive shift value (precision 0 shifted right by 16) Kevin: shift a constant */
    u4CSUM32 += (HTONL(0x11UL)&0xffff) + ((HTONL(0x11UL)>>16) & 0xffff);
/*lint -restore */

    while (u4CSUM32 > 0xffff) {
        u4CSUM32 = (u4CSUM32 >> 16) + (u4CSUM32 & 0xffff);
    }
    if (u4CSUM32 != 0xffff) {

        DBGLOG(RX, LOUD, ("UDP Checksum Error!\n"));
        return FALSE;
    }
    else {
        DBGLOG(RX, LOUD, ("UDP Checksum Correct!\n"));
        return TRUE;
    }

}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routines is called to validate checksum which is used by IPv6.
*
* \param[in] pucDatagram Pointer to the datagram to be calculating checksum.
* \param[in] pucProto Pointer to the protocol ID.
* \param[out] peL4CSUMRes The status flag of the checksum validating result.
*
* \return TRUE IPv6 Checksum Correct
* \return FALSE IPv6 Checksum Error
*/
/*----------------------------------------------------------------------------*/
BOOLEAN
utilValidateIPv6Checksum (
    IN PUINT_8 pucDatagram,
    IN PUINT_8 pucProto,
    OUT P_ENUM_CSUM_RESULT_T peL4CSUMRes
    )
{
    UINT_32 hdr_len = sizeof(ipv6_hdr_t);

    pipv6_hdr_t prHdr;
    pipv6_ext_hdr_t prExtHdr;
    unsigned char next_hdr;
    unsigned short payload_len;

    DEBUGFUNC("utilValidateIPv6Checksum");

    ASSERT(pucDatagram);
    ASSERT(pucProto);
    ASSERT(peL4CSUMRes);

    prHdr = (pipv6_hdr_t)pucDatagram;
    prExtHdr = (pipv6_ext_hdr_t)(pucDatagram+hdr_len);
    next_hdr = prHdr->next_hdr;
    payload_len = NTOHS(prHdr->payload_len);

    *peL4CSUMRes = CSUM_RES_NONE;

    //Parse extension header
    while (next_hdr != 0x6 && next_hdr != 0x11) {
        next_hdr = prExtHdr->next_hdr;
        hdr_len = prExtHdr->len+1;
        prExtHdr = (pipv6_ext_hdr_t)((PUINT_8)prExtHdr+(prExtHdr->len+1));
        payload_len -= (prExtHdr->len+1);
        /*Todo: Parse routing header */
    }

    *pucProto = prHdr->next_hdr;
    if (prHdr->next_hdr == 0x6) {
        *peL4CSUMRes = (utilValidateTCPChecksum(
            (PUINT_8)prHdr->saddr, (PUINT_8)prHdr->daddr, 16, pucDatagram+hdr_len, payload_len
        ))?CSUM_RES_SUCCESS:CSUM_RES_FAILED;
    }
    else if (prHdr->next_hdr == 0x11) {
        *peL4CSUMRes = (utilValidateUDPChecksum(
            (PUINT_8)prHdr->saddr, (PUINT_8)prHdr->daddr, 16, pucDatagram+hdr_len, payload_len
        ))?CSUM_RES_SUCCESS:CSUM_RES_FAILED;

    }
    else {
        DBGLOG(RX, LOUD, ("Unknow transport layer protocol (%#x)\n", prHdr->next_hdr));
    }
    return TRUE;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routines is called to validate checksum which is used by IPv4.
*
* \param[in] pucDatagram Pointer to the datagram to be calculating checksum.
* \param[in] pucProto Pointer to the protocol ID.
* \param[out] peL4CSUMRes The status flag of the checksum validating result.
*
* \return TRUE IPv4 Checksum Correct
* \return FALSE IPv4 Checksum Error
*/
/*----------------------------------------------------------------------------*/
BOOLEAN
utilValidateIPv4Checksum (
    IN PUINT_8 pucDatagram,
    IN PUINT_8 pucProto,
    OUT P_ENUM_CSUM_RESULT_T peL4CSUMRes
    )
{
    UINT_32 hdr_len;
    pipv4_hdr_t prHdr;
    UINT_32 csum32 = 0;

    DEBUGFUNC("utilValidateIPv4Checksum");

    ASSERT(pucDatagram);
    ASSERT(pucProto);
    ASSERT(peL4CSUMRes);

    hdr_len = (pucDatagram[0] & 0xf)*4;
    prHdr = (pipv4_hdr_t)pucDatagram;

    *peL4CSUMRes = CSUM_RES_NONE;

    csum32 = utilComputeCSUM(pucDatagram, hdr_len, 0);
    while(csum32 > 0xffff) {
        csum32 = (csum32 >> 16) + (csum32 & 0xffff);
    }
    if(csum32 != 0xffff) {
        DBGLOG(RX, LOUD, ("IPv4 Header Checksum Error!\n"));
        return FALSE;
    }
    else{
        //printk("IPv4 Header Checksum Correct!\n");
    }

    DBGLOG(RX, LOUD, ("IPv4(%ld), Tx_Proto(%d): ", NTOHS(prHdr->len)-hdr_len, prHdr->proto));

    if (prHdr->flagfragoffset != 0x40) {
        DBGLOG(RX, LOUD, (", ip fragment(%#x)\n", prHdr->flagfragoffset));
        return TRUE;
    }

    *pucProto = prHdr->proto;
    if(prHdr->proto == 0x6) {
        *peL4CSUMRes = (utilValidateTCPChecksum(
            (PUINT_8)&prHdr->src, (PUINT_8)&prHdr->dest, 4, pucDatagram+hdr_len, NTOHS(prHdr->len)-hdr_len
        ))?CSUM_RES_SUCCESS:CSUM_RES_FAILED;
    }
    else if (prHdr->proto == 0x11) {
        *peL4CSUMRes= (utilValidateUDPChecksum(
            (PUINT_8)&prHdr->src, (PUINT_8)&prHdr->dest, 4, pucDatagram+hdr_len, NTOHS(prHdr->len)-hdr_len
        ))?CSUM_RES_SUCCESS:CSUM_RES_FAILED;
    }
    else {
        DBGLOG(RX, LOUD, ("Unknow transport layer protocol (%#x)\n", prHdr->proto));
    }
    return TRUE;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routines is called to generate checksum which is used by IPv6.
*
* \param[in] pucData Pointer to the datagram to be calculating checksum.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
utilGenIPv6CSUM (
    IN PUINT_8 pucData
    )
{
    pipv6_hdr_t prHdr;
    UINT_32 u4IPPseudoHdrCSUM = 0;
    //UINT_32 u4L4Datalen = NTOHS(prHdr->payload_len) - sizeof(ipv6_hdr_t);
    UINT_32 hdr_len = sizeof(ipv6_hdr_t);
    pipv6_ext_hdr_t prExtHdr;
    unsigned char next_hdr;
    unsigned long payload_len;

    ASSERT(pucData);

    prHdr = (pipv6_hdr_t)pucData;
    prExtHdr = (pipv6_ext_hdr_t)(pucData+hdr_len);
    next_hdr = prHdr->next_hdr;
    payload_len = NTOHS(prHdr->payload_len);

    while (next_hdr != 0x6 && next_hdr != 0x11) {
        next_hdr = prExtHdr->next_hdr;
        hdr_len = prExtHdr->len+1;
        prExtHdr = (pipv6_ext_hdr_t)((PUINT_8)prExtHdr+(prExtHdr->len+1));
        payload_len -= (prExtHdr->len+1);
        /*Todo: Parse routing header */
    }

    u4IPPseudoHdrCSUM = utilComputeCSUM((PUINT_8)prHdr->daddr, IPv6_ADDR_LEN, u4IPPseudoHdrCSUM);
    u4IPPseudoHdrCSUM = utilComputeCSUM((PUINT_8)prHdr->saddr, IPv6_ADDR_LEN, u4IPPseudoHdrCSUM);
    u4IPPseudoHdrCSUM += (HTONL(payload_len)&0xffff) + ((HTONL(payload_len)>>16) & 0xffff);

    if (next_hdr == PROTO_TCP) {
/*lint -save -e572 Excessive shift value (precision 0 shifted right by 16) Kevin: shift a constant */
        u4IPPseudoHdrCSUM += (HTONL(0x6)&0xffff) + ((HTONL(0x6)>>16) & 0xffff);
/*lint -restore */
        utilGenTCPCSUM(pucData+hdr_len, payload_len, u4IPPseudoHdrCSUM);
    }
    else if (next_hdr == PROTO_UDP) {
/*lint -save -e572 Excessive shift value (precision 0 shifted right by 16) Kevin: shift a constant */
        u4IPPseudoHdrCSUM += (HTONL(0x11)&0xffff) + ((HTONL(0x11)>>16) & 0xffff);
/*lint -restore */
        utilGenUDPCSUM(pucData+hdr_len, payload_len, u4IPPseudoHdrCSUM);
    }
    else {

    }
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routines is called to generate checksum which is used by IPv4.
*
* \param[in] pucData Pointer to the datagram to be calculating checksum.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
utilGenIPv4CSUM (
    IN PUINT_8 pucData
    )
{
    pipv4_hdr_t prHdr;

    UINT_32 hdr_len;
    UINT_32 csum32 = 0;
    PUINT_8 pucL4Pkt;
    UINT_32 u4IPPseudoHdrCSUM = 0;
    UINT_32 u4L4Datalen;

    ASSERT(pucData);

    hdr_len = (pucData[0] & 0xf)*4;
    prHdr = (pipv4_hdr_t)pucData;
    pucL4Pkt = pucData + sizeof(ipv4_hdr_t);
    u4L4Datalen = NTOHS(prHdr->len) - sizeof(ipv4_hdr_t);

    prHdr->hdrchecksum = 0;
    csum32 = utilComputeCSUM(pucData, hdr_len, 0);
    while(csum32 > 0xffff){
        csum32 = (csum32 >> 16) + (csum32 & 0xffff);
    }
    csum32 = (~csum32 & 0xffff);
    prHdr->hdrchecksum = (UINT_16)(csum32 & 0xffff);

    //u4IPPseudoHdrCSUM = utilComputeCSUM(pucData, NTOHS(prHdr->len) - sizeof(ipv4_hdr_t), 0);
    u4IPPseudoHdrCSUM = utilComputeCSUM((PUINT_8)&prHdr->dest, IPv4_ADDR_LEN, u4IPPseudoHdrCSUM);
    u4IPPseudoHdrCSUM = utilComputeCSUM((PUINT_8)&prHdr->src, IPv4_ADDR_LEN, u4IPPseudoHdrCSUM);
    u4IPPseudoHdrCSUM += (UINT_16)(HTONL(u4L4Datalen)&0xffff) + (UINT_16)((HTONL(u4L4Datalen)>>16) & 0xffff);


    if (prHdr->flagfragoffset == 0x40) {
        if (prHdr->proto == PROTO_TCP) {
/*lint -save -e572 Excessive shift value (precision 0 shifted right by 16) Kevin: shift a constant */
            u4IPPseudoHdrCSUM += (HTONL(0x6)&0xffff) + ((HTONL(0x6)>>16) & 0xffff);
/*lint -restore */
            utilGenTCPCSUM(pucL4Pkt, u4L4Datalen, u4IPPseudoHdrCSUM);
        }
        else if (prHdr->proto == PROTO_UDP) {
/*lint -save -e572 Excessive shift value (precision 0 shifted right by 16) Kevin: shift a constant */
            u4IPPseudoHdrCSUM += (HTONL(0x11)&0xffff) + ((HTONL(0x11)>>16) & 0xffff);
/*lint -restore */
            utilGenUDPCSUM(pucL4Pkt, u4L4Datalen, u4IPPseudoHdrCSUM);
        }
        else {

        }
    }
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routines is called to generate checksum which is used by TCP,
*        the result will be appened into the TCP checksum field.
*
* \param[in] pucData Pointer to the datagram to be calculating checksum.
* \param[in] u4Size Length of the datagram to be calculating checksum.
* \param[in] u4IPCSUM IP checksum value.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
utilGenTCPCSUM (
    IN PUINT_8 pucData,
    IN UINT_32 u4Size,
    IN UINT_32 u4IPCSUM
    )
{
    ptcp_hdr_t tcp;
    UINT_32 CSUM = 0;

    ASSERT(pucData);
    tcp = (ptcp_hdr_t)pucData;

    tcp->check = 0;
    if(u4Size < sizeof(tcp_hdr_t)){
        ASSERT(0);
        return;
    }

    CSUM = utilComputeCSUM(pucData, u4Size, u4IPCSUM);

    while(CSUM > 0xffff){
        CSUM = (CSUM >> 16) + (CSUM & 0xffff);
    }
    CSUM = (~CSUM & 0xffff);

    tcp->check = (UINT_16)CSUM;

}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routines is called to generate checksum which is used by UDP,
*        the result will be appened into the UDP checksum field.
*
* \param[in] pucData Pointer to the datagram to be calculating checksum.
* \param[in] u4Size Length of the datagram to be calculating checksum.
* \param[in] u4IPCSUM IP checksum value.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
utilGenUDPCSUM (
    IN PUINT_8 pucData,
    IN UINT_32 u4Size,
    IN UINT_32 u4IPCSUM
    )
{
    pudp_hdr_t udp;
    UINT_32 CSUM = 0;

    ASSERT(pucData);
    udp = (pudp_hdr_t)pucData;

    udp->check = 0;
    if(u4Size < sizeof(udp_hdr_t)){
        ASSERT(0);
        return;
    }

    CSUM = utilComputeCSUM(pucData, u4Size, u4IPCSUM);

    while(CSUM > 0xffff){
        CSUM = (CSUM >> 16) + (CSUM & 0xffff);
    }

    CSUM = (~CSUM & 0xffff);

    if(CSUM == 0){
        CSUM = 0xffff;
    }

    udp->check = (UINT_16)CSUM;

}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routines is called to validating checksum of the RX packets.
*
* \param[in] pucEtherPkt Pointer to the ethernet datagram to be calculating checksum.
* \param[in] u2PktLen Length of the datagram to be calculating checksum.
* \param[out] aeCSUM The status flag of the checksum validating result.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
utilRxComputeCSUM (
    IN PUINT_8 pucEtherPkt,
    IN UINT_16 u2PktLen,
    OUT ENUM_CSUM_RESULT_T aeCSUM[]
    )
{
    UINT_16 u2Proto = 0;
    peth_hdr_t prEtherHdr;
    PUINT_8 pucDatagram = 0;
    UINT_8 ucProto = 0;
    //BOOLEAN fgL4ProtoRes = FALSE;
    ENUM_CSUM_RESULT_T eL4CSUMRes = CSUM_RES_FAILED;

    DEBUGFUNC("utilRxComputeCSUM");

    ASSERT(pucEtherPkt);
    ASSERT(aeCSUM);

    prEtherHdr = (peth_hdr_t)pucEtherPkt;

    u2Proto = prEtherHdr->u2TypeLen;
    pucDatagram = prEtherHdr->aucData;


    if(u2Proto == TL_IPV4) {
        aeCSUM[CSUM_TYPE_IPV6] = CSUM_RES_NONE;
        if (utilValidateIPv4Checksum(pucDatagram, &ucProto, &eL4CSUMRes)){
            aeCSUM[CSUM_TYPE_IPV4] = CSUM_RES_SUCCESS;
        }
        else {
            aeCSUM[CSUM_TYPE_IPV4] = CSUM_RES_FAILED;
        }
    }
    else if (u2Proto == TL_IPV6) {
        aeCSUM[CSUM_TYPE_IPV4] = CSUM_RES_NONE;
        if (utilValidateIPv6Checksum(pucDatagram, &ucProto, &eL4CSUMRes)){
            aeCSUM[CSUM_TYPE_IPV6] = CSUM_RES_SUCCESS;
        }
        else {
            aeCSUM[CSUM_TYPE_IPV6] = CSUM_RES_FAILED;
        }
    }
    else {
        DBGLOG(RX, LOUD, ("UNKNOW L3 Header"));
        aeCSUM[CSUM_TYPE_IPV6] = CSUM_RES_NONE;
        aeCSUM[CSUM_TYPE_IPV4] = CSUM_RES_NONE;
    }
    if(ucProto == 0x6) {
        aeCSUM[CSUM_TYPE_TCP] = eL4CSUMRes;//?CSUM_RES_SUCCESS:CSUM_RES_FAILED;
    }
    else if (ucProto == 0x11) {
        aeCSUM[CSUM_TYPE_UDP] = eL4CSUMRes;//?CSUM_RES_SUCCESS:CSUM_RES_FAILED;
    }
    else {
        aeCSUM[CSUM_TYPE_UDP] = CSUM_RES_NONE;
        aeCSUM[CSUM_TYPE_TCP] = CSUM_RES_NONE;
    }


}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routines is called to generate checksum,
*        the result will be appened into the UDP checksum field.
*
* \param[in] pucPacket Pointer to the ethernet datagram to be calculating checksum.
* \param[in] u2PktLen Length of the datagram to be calculating checksum.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
utilTxComputeCSUM (
    IN PUINT_8 pucPacket,
    IN UINT_32 u4PktLen
    )
{

    peth_hdr_t prEtherPkt;

    ASSERT(pucPacket);
    prEtherPkt = (peth_hdr_t)pucPacket;

    if(prEtherPkt && u4PktLen > 14) {
        if (prEtherPkt->u2TypeLen == TL_IPV4) {
            utilGenIPv4CSUM(prEtherPkt->aucData);
        }
        else if (prEtherPkt->u2TypeLen == TL_IPV6) {
            utilGenIPv6CSUM(prEtherPkt->aucData);
        }
        else {

        }
    }

}



