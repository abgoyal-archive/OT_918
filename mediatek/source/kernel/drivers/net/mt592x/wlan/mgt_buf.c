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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/mgt_buf.c#1 $
*/

/*! \file   "mgt_buf.c"
    \brief  This file contain the management function of internal frame buffer
            for Management Frame.

        Before transmitting any MMPDU from Protocol Stack, we need to allocate a
    frame buffer and compose the MMPDU frame body on it. After TX done event, this
    frame buffer should also be return to the management function.
        If system try to unload the driver, those pre-allocated frame buffers
    should be released to system first.
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
** $Log: mgt_buf.c $
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\14 2008-12-01 20:59:38 GMT mtk01461
**  Fix Lint Warning 613: Possible use of null pointer.
**  \main\maintrunk.MT5921\13 2008-11-28 16:22:07 GMT mtk01088
**  fixed the lint warning
**  \main\maintrunk.MT5921\12 2008-08-12 19:08:36 GMT mtk01461
**  Update for Driver Review
**  \main\maintrunk.MT5921\11 2008-07-07 13:39:26 GMT mtk01461
**  Fix the out of valid index problem in mgtBufInitialize(), this will overwrite other data structure(WLAN Table) during register reset.
**  \main\maintrunk.MT5921\10 2008-03-29 20:33:42 GMT mtk01461
**  Remove ASSERT(pucBuffer) in mgtBufQueryStatus() for non sprintf case
**  \main\maintrunk.MT5921\9 2008-03-26 23:23:59 GMT mtk01461
**  Update comment
**  \main\maintrunk.MT5921\8 2008-02-01 09:35:43 GMT mtk01385
**  1. Fix WinCE 4.2 compiling error.
**  \main\maintrunk.MT5921\7 2007-11-13 17:07:55 GMT mtk01461
**  Fix the unexpected assert after chip reset - add memzero to mgt buf initial
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
* \brief This function is used to initial the memory pool for MGMT frame.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
mgtBufInitialize (
    IN P_ADAPTER_T prAdapter
    )
{
    P_MGT_BUF_INFO_T prMgtBufInfo;
    PUINT_8 pucMemHandle;
    P_MGT_PACKET_T prMgtPacket;
    UINT_32 i;


    ASSERT(prAdapter);
    prMgtBufInfo = &prAdapter->rMgtBufInfo;

    //4 <0> Clear allocated memory.
    kalMemZero((PVOID) prMgtBufInfo->pucMgtBufCached, prMgtBufInfo->u4MgtBufCachedSize);

    ASSERT(IS_ALIGN_4((UINT_32)prMgtBufInfo->pucMgtBufCached));
    prMgtBufInfo->pucMgtBufPoolCached = prMgtBufInfo->pucMgtBufCached +
                                        MGT_PACKET_DESCRIPTORS_SIZE;


    /* Initial MGT Buffer allocation lookup table, for example:
     * 5 memory blocks are represented as 00011111'B.
     * = (BIT(5) - 1) (but we'll encounter a problem of allocating 32 blocks in this formula)
     * = (BIT(4) | (BIT(4)-1))
     */
    for (i = 0; i <= MAX_NUM_OF_MGT_BUF_BLOCKS; i++) {
        prMgtBufInfo->rMgtBufBlocksToBitsTable[i] =
            (BUF_BITMAP)(i ? (BIT(i-1) | (BIT(i-1) - 1)) : 0);
    }

    /* Setup available memory blocks.(8 memory blocks = 11111111'B */
    prMgtBufInfo->rFreeMgtBufBlocksBitmap =
        (BUF_BITMAP)(BIT(MAX_NUM_OF_MGT_BUF_BLOCKS-1) | (BIT(MAX_NUM_OF_MGT_BUF_BLOCKS-1) - 1));


    pucMemHandle = prMgtBufInfo->pucMgtBufCached;

    QUEUE_INITIALIZE(&prMgtBufInfo->rFreeMgtPacketList);
    for (i = 0; i < MAX_NUM_OF_MGT_PACKETS; i++) {
        prMgtPacket = (P_MGT_PACKET_T)pucMemHandle;

        prMgtPacket->rAllocatedMgtBufBlocksBitmap = 0;
        QUEUE_INSERT_TAIL(&prMgtBufInfo->rFreeMgtPacketList, &prMgtPacket->rQueEntry);

        pucMemHandle += ALIGN_4(sizeof(MGT_PACKET_T));
    }

    /* Check if the memory allocation consist with this initialization function */
    ASSERT(pucMemHandle == prMgtBufInfo->pucMgtBufPoolCached);

    return;

} /* end of mgtBufInitialize() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function is used to initial the memory pool for MGT frame.
*        (e.g. MMPDU or NULL Data Frame)
*
* \param[in] prAdapter      Pointer to the Adapter structure.
* \param[in] u4Length       Length of the frame buffer to allocate.
*
* \retval NULL      Pointer to the valid MGT Packet handler
* \retval !NULL     Fail to allocat MGT Packet
*/
/*----------------------------------------------------------------------------*/
P_MGT_PACKET_T
mgtBufAllocateMgtPacket (
    IN P_ADAPTER_T prAdapter,
    IN UINT_32 u4Length
    )
{
    P_MGT_BUF_INFO_T prMgtBufInfo;
    UINT_32 u4BlockNum;
    BUF_BITMAP rRequiredBitmap = 0;
    P_MGT_PACKET_T prMgtPacket = (P_MGT_PACKET_T)NULL;
    PUINT_8 pucBuffer;
    UINT_32 i;

    DEBUGFUNC("mgtBufAllocateMgtPacket");


    ASSERT(prAdapter);
    prMgtBufInfo = &prAdapter->rMgtBufInfo;

    do {

        /* No available MGMT PACKET Descriptor */
        if (QUEUE_IS_EMPTY(&prMgtBufInfo->rFreeMgtPacketList)) {
            break;
        }

        ASSERT(u4Length);

        u4Length += MGT_PACKET_RESERVED_SIZE; /* reserved space */
        u4Length += (MGT_BUF_BLOCK_SIZE - 1);
        u4BlockNum = u4Length >> MGT_BUF_BLOCK_SIZE_IN_POWER_OF_2;
        /* Will use shift instruction if denominator is power of 2 */

        ASSERT(u4BlockNum <= MAX_NUM_OF_MGT_BUF_BLOCKS);

        if ((u4BlockNum > 0) && (u4BlockNum <= MAX_NUM_OF_MGT_BUF_BLOCKS)) {

            /* Convert number of block into bit cluster */
            rRequiredBitmap = prMgtBufInfo->rMgtBufBlocksToBitsTable[u4BlockNum];

            for (i = 0;
                 i <= (MAX_NUM_OF_MGT_BUF_BLOCKS - u4BlockNum);
                 i++ , rRequiredBitmap <<= 1) {

                /* Have available memory blocks */
                if ((prMgtBufInfo->rFreeMgtBufBlocksBitmap & rRequiredBitmap) == rRequiredBitmap) {

                    QUEUE_REMOVE_HEAD(&prMgtBufInfo->rFreeMgtPacketList, prMgtPacket, P_MGT_PACKET_T);
                    if (!prMgtPacket) {
                        DBGLOG(MGT, ERROR, ("Free MGT Packet Queue Error !\n"));
                        break;
                    }

                    /* Clear corresponding bits of allocated memory blocks */
                    prMgtBufInfo->rFreeMgtBufBlocksBitmap &= ~rRequiredBitmap;

#if CFG_TX_DBG_MGT_BUF
                    /* Update maximux allocated depth */
                    if (prMgtBufInfo->ucMaxAllocatedDepth < (UINT_8)(u4BlockNum + i)) {
                        prMgtBufInfo->ucMaxAllocatedDepth = (UINT_8)(u4BlockNum + i);
                    }
#endif /* CFG_TX_DBG_MGT_BUF */

                    /* Store corresponding bits of allocated memory blocks */
                    prMgtPacket->rAllocatedMgtBufBlocksBitmap = rRequiredBitmap;

                    /* Return the start address of allocated memory */
                    pucBuffer = prMgtBufInfo->pucMgtBufPoolCached + \
                                MGT_BUF_BLOCKS_SIZE(i);

                    /* Setup initial value in MGMT_PACKET_T */
                    prMgtPacket->pucHead = pucBuffer;
                    prMgtPacket->pucEnd = pucBuffer + \
                                          MGT_BUF_BLOCKS_SIZE(u4BlockNum);
                    prMgtPacket->pucData = pucBuffer + MGT_PACKET_RESERVED_SIZE;
                    prMgtPacket->pucTail = prMgtPacket->pucData;

                    break;
                }
            }

        }

    }
    while (FALSE);

    return prMgtPacket;

} /* end of mgtBufAllocateMgtPacket() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function is used to free the MGT Packet to the MGT memory pool.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
* \param[in] prMgtPacket    MGT Packet handler
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
mgtBufFreeMgtPacket (
    IN P_ADAPTER_T prAdapter,
    IN P_MGT_PACKET_T prMgtPacket
    )
{
    P_MGT_BUF_INFO_T prMgtBufInfo

    DEBUGFUNC("mgtBufFreeMgtPacket");


    ASSERT(prAdapter);
    ASSERT(prMgtPacket);
    prMgtBufInfo = &prAdapter->rMgtBufInfo;

    if (prMgtPacket) {

        /* Memory should not overlap */
        ASSERT((prMgtBufInfo->rFreeMgtBufBlocksBitmap & \
            prMgtPacket->rAllocatedMgtBufBlocksBitmap) == 0);

        /* Set corresponding bits of released memory blocks */
        prMgtBufInfo->rFreeMgtBufBlocksBitmap |= prMgtPacket->rAllocatedMgtBufBlocksBitmap;

        /* Clear corresponding bits of released memory blocks */
        prMgtPacket->rAllocatedMgtBufBlocksBitmap = 0;

        QUEUE_INSERT_TAIL(&prMgtBufInfo->rFreeMgtPacketList, &prMgtPacket->rQueEntry);
    }

    return;

} /* end of mgtBufFreeMgtPacket() */


#if CFG_TX_DBG_MGT_BUF
/*----------------------------------------------------------------------------*/
/*!
* \brief This function is used to print current status of MGT memory pool usage.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
* \param[in] pucBuffer      Pointer to the message buffer.
* \param[out] pu4Count      Pointer to the buffer of message length count.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
mgtBufQueryStatus (
    IN P_ADAPTER_T prAdapter,
    IN PUINT_8 pucBuffer,
    OUT PUINT_32 pu4Count
    )
{
    P_MGT_BUF_INFO_T prMgtBufInfo;
    PUINT_8 pucCurrBuf = pucBuffer;
    UINT_32 u4FreeMgtBufBlocks = 0;
    UINT_32 i;


    ASSERT(prAdapter);
    prMgtBufInfo = &prAdapter->rMgtBufInfo;
    if (pucBuffer) {} /* For Windows, we'll print directly instead of sprintf() */
    ASSERT(pu4Count);

    SPRINTF(pucCurrBuf, ("\n\nMGT BUFFER STATUS:"));
    SPRINTF(pucCurrBuf, ("\n=================="));
    SPRINTF(pucCurrBuf, ("\nFREE MGMT PACKET LIST         :%8ld",
        prMgtBufInfo->rFreeMgtPacketList.u4NumElem));


    for (i = 0; i < MAX_NUM_OF_MGT_BUF_BLOCKS; i++) {
        if (prMgtBufInfo->rFreeMgtBufBlocksBitmap & BIT(i)) {
            u4FreeMgtBufBlocks++;
        }
    }

    SPRINTF(pucCurrBuf, ("\nFREE MGMT BUFFER SIZE(bytes)  :%8ld",
        u4FreeMgtBufBlocks * MGT_BUF_BLOCK_SIZE));
    SPRINTF(pucCurrBuf, ("\nFREE MGMT BUFFER BLOCK BITMAP :%08lx",
        (UINT_32)prMgtBufInfo->rFreeMgtBufBlocksBitmap));
    SPRINTF(pucCurrBuf, ("\nMAXIMUM ALLOCATED DEPTH(bytes):%8ld",
        (UINT_32)prMgtBufInfo->ucMaxAllocatedDepth * MGT_BUF_BLOCK_SIZE));

    SPRINTF(pucCurrBuf, ("\n\n"));

    *pu4Count = (UINT_32)((UINT_32)pucCurrBuf - (UINT_32)pucBuffer);

    return;

} /* end of mgtBufQueryStatus() */
#endif /* CFG_TX_DBG_MGT_BUF */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function is used to check if the reserved head room size is larger
*        then given length.
*
* \param[in] prMgtPacket    MGT Packet handler
* \param[in] u4Length       Length to check
*
* \retval TRUE      The reserved head room size is >= given length.
* \retval FALSE     The reserved head room size is < given length
*/
/*----------------------------------------------------------------------------*/
BOOLEAN
mgtPacketCheckHeadroom (
    IN P_MGT_PACKET_T prMgtPacket,
    IN UINT_32 u4Length
    )
{
    ASSERT(prMgtPacket);

    return (BOOLEAN)((u4Length <= (UINT_32)(prMgtPacket->pucData - prMgtPacket->pucHead)) ? TRUE : FALSE);

} /* end of mgtPacketCheckHeadroom() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function is used to update current frame length to MGT Packet Handle.
*        And we'll do ASSERT here to indicate that data may be overwriten to unknown
*        area.
*
* \param[in] prMgtPacket    MGT Packet handler
* \param[in] u4Length       Frame length to be update
*
* \retval NULL      The frame length exceed the maximum length of MGT Packet Buffer.
* \retval !NULL     Pointer to the MGT Packet Buffer.
*/
/*----------------------------------------------------------------------------*/
PUINT_8
mgtPacketPut (
    IN P_MGT_PACKET_T prMgtPacket,
    IN UINT_32 u4Length
    )
{
    PUINT_8 pucBuffer;


    ASSERT(prMgtPacket);
    pucBuffer = prMgtPacket->pucTail;

    if (((UINT_32)pucBuffer + u4Length) > (UINT_32)(prMgtPacket->pucEnd)) {
        ASSERT_REPORT(0, ("Frame size %ld exceed the limit of allocated frame buffer\n", u4Length));
        pucBuffer = (PUINT_8)NULL;
    }
    else {
        prMgtPacket->pucTail += u4Length;
    }

    return pucBuffer;

} /* end of mgtPacketPut() */


#if 0 /* RESERVE */
/*----------------------------------------------------------------------------*/
/*!
* \brief This function is used to remove the reserved head room of MGT Packet.
*
* \param[in] prMgtPacket    MGT Packet handler
* \param[in] u4Length       Length of reserved head room to be remove
*
* \retval NULL      Can't remove the head room of given length.
* \retval !NULL     Successful remove head room and return new Packet Buffer Pointer.
*/
/*----------------------------------------------------------------------------*/
PUINT_8
mgtPacketPush (
    IN P_MGT_PACKET_T prMgtPacket,
    IN UINT_32 u4Length
    )
{
    PUINT_8 pucBuffer;


    ASSERT(prMgtPacket);

    if ((prMgtPacket->pucData - u4Length) < prMgtPacket->pucHead) {
        ASSERT_REPORT(0, ("No succifucent head room for %ld bytes.\n", u4Length));
        pucBuffer = (PUINT_8)NULL;
    }
    else {
        prMgtPacket->pucData -= u4Length;
        pucBuffer = prMgtPacket->pucData;
    }

    return pucBuffer;

} /* end of mgtPacketPush() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function is used to reserve a fixed head room size.
*
* \param[in] prMgtPacket    MGT Packet handler
* \param[in] u4Length       Length to reserve
*
* \retval TRUE      Successful reserve head room of given length.
* \retval FALSE     Can't reserve head room of given length.
*/
/*----------------------------------------------------------------------------*/
BOOLEAN
mgtPacketReserveHeadroom (
    IN P_MGT_PACKET_T prMgtPacket,
    IN UINT_32 u4Length
    )
{
    ASSERT(prMgtPacket);

    if (u4Length > (UINT_32)(prMgtPacket->pucEnd - prMgtPacket->pucTail)) {
        ASSERT_REPORT(0, ("No succifucent space for %ld bytes of head room.\n", u4Length));
        return FALSE;
    }
    else {
        prMgtPacket->pucData += u4Length;
        prMgtPacket->pucTail += u4Length;
    }

    return TRUE;

} /* end of mgtPacketReserveHeadroom() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function is used to get the reserved head room size before the first
*        byte of current frame.
*
* \param[in] prMgtPacket    MGT Packet handler
*
* \return   Reserved head room size
*/
/*----------------------------------------------------------------------------*/
UINT_32
mgtPacketHeadroomLength (
    IN P_MGT_PACKET_T prMgtPacket
    )
{
    ASSERT(prMgtPacket);

    return (UINT_32)(prMgtPacket->pucData - prMgtPacket->pucHead);

} /* end of mgtPacketHeadroomLength() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function is used to calculate current frame length.
*
* \param[in] prMgtPacket    MGT Packet handler
*
* \return   Current frame length
*/
/*----------------------------------------------------------------------------*/
UINT_32
mgtPacketLength (
    IN P_MGT_PACKET_T prMgtPacket
    )
{
    ASSERT(prMgtPacket);

    return (UINT_32)(prMgtPacket->pucTail - prMgtPacket->pucData);

} /* end of mgtPacketLength() */
#endif


