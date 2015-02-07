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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/dump.c#1 $
*/

/*! \file   "dump.c"
    \brief  Provide memory dump function for debugging.

    Provide memory dump function for debugging.
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
** $Log: dump.c $
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\8 2008-10-22 10:54:00 GMT mtk01461
**  Update for lint diagnosis support
**  \main\maintrunk.MT5921\7 2008-08-10 18:47:42 GMT mtk01461
**  Update for Driver Review
**  \main\maintrunk.MT5921\6 2008-03-31 21:56:12 GMT mtk01461
**  Update comment
**  \main\maintrunk.MT5921\5 2007-10-25 17:44:23 GMT mtk01461
** Revision 1.1.1.1  2007/06/22 08:09:05  MTK01461
** no message
**
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
#if DBG
/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to dump a segment of memory in bytes.
*
* \param[in] pucStartAddr   Pointer to the starting address of the memory to be dumped.
* \param[in] u4Length       Length of the memory to be dumped.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
dumpMemory8 (
    IN PUINT_8  pucStartAddr,
    IN UINT_32  u4Length
    )
{
    ASSERT(pucStartAddr);

    LOG_FUNC("DUMP8 ADDRESS: %08lx, Length: %ld\n", (UINT_32)pucStartAddr, u4Length);

    while (u4Length > 0) {
        if (u4Length >= 16) {
            LOG_FUNC("(%08lx) %02x %02x %02x %02x  %02x %02x %02x %02x - %02x %02x %02x %02x  %02x %02x %02x %02x\n",
                (UINT_32)pucStartAddr,
                pucStartAddr[ 0], pucStartAddr[ 1], pucStartAddr[ 2], pucStartAddr[ 3],
                pucStartAddr[ 4], pucStartAddr[ 5], pucStartAddr[ 6], pucStartAddr[ 7],
                pucStartAddr[ 8], pucStartAddr[ 9], pucStartAddr[10], pucStartAddr[11],
                pucStartAddr[12], pucStartAddr[13], pucStartAddr[14], pucStartAddr[15]);
            u4Length -= 16;
            pucStartAddr += 16;
        }
        else {
            switch (u4Length) {
            case 1:
                LOG_FUNC("(%08lx) %02x\n",
                    (UINT_32)pucStartAddr,
                    pucStartAddr[ 0]);
                break;
            case 2:
                LOG_FUNC("(%08lx) %02x %02x\n",
                    (UINT_32)pucStartAddr,
                    pucStartAddr[ 0], pucStartAddr[ 1]);
                break;
            case 3:
                LOG_FUNC("(%08lx) %02x %02x %02x\n",
                    (UINT_32)pucStartAddr,
                    pucStartAddr[ 0], pucStartAddr[ 1], pucStartAddr[ 2]);
                break;
            case 4:
                LOG_FUNC("(%08lx) %02x %02x %02x %02x\n",
                    (UINT_32)pucStartAddr,
                    pucStartAddr[ 0], pucStartAddr[ 1], pucStartAddr[ 2], pucStartAddr[ 3]);
                break;
            case 5:
                LOG_FUNC("(%08lx) %02x %02x %02x %02x  %02x\n",
                    (UINT_32)pucStartAddr,
                    pucStartAddr[ 0], pucStartAddr[ 1], pucStartAddr[ 2], pucStartAddr[ 3],
                    pucStartAddr[ 4]);
                break;
            case 6:
                LOG_FUNC("(%08lx) %02x %02x %02x %02x  %02x %02x\n",
                    (UINT_32)pucStartAddr,
                    pucStartAddr[ 0], pucStartAddr[ 1], pucStartAddr[ 2], pucStartAddr[ 3],
                    pucStartAddr[ 4], pucStartAddr[ 5]);
                break;
            case 7:
                LOG_FUNC("(%08lx) %02x %02x %02x %02x  %02x %02x %02x\n",
                    (UINT_32)pucStartAddr,
                    pucStartAddr[ 0], pucStartAddr[ 1], pucStartAddr[ 2], pucStartAddr[ 3],
                    pucStartAddr[ 4], pucStartAddr[ 5], pucStartAddr[ 6]);
                break;
            case 8:
                LOG_FUNC("(%08lx) %02x %02x %02x %02x  %02x %02x %02x %02x\n",
                    (UINT_32)pucStartAddr,
                    pucStartAddr[ 0], pucStartAddr[ 1], pucStartAddr[ 2], pucStartAddr[ 3],
                    pucStartAddr[ 4], pucStartAddr[ 5], pucStartAddr[ 6], pucStartAddr[ 7]);
                break;
            case 9:
                LOG_FUNC("(%08lx) %02x %02x %02x %02x  %02x %02x %02x %02x - %02x\n",
                    (UINT_32)pucStartAddr,
                    pucStartAddr[ 0], pucStartAddr[ 1], pucStartAddr[ 2], pucStartAddr[ 3],
                    pucStartAddr[ 4], pucStartAddr[ 5], pucStartAddr[ 6], pucStartAddr[ 7],
                    pucStartAddr[ 8]);
                break;
            case 10:
                LOG_FUNC("(%08lx) %02x %02x %02x %02x  %02x %02x %02x %02x - %02x %02x\n",
                    (UINT_32)pucStartAddr,
                    pucStartAddr[ 0], pucStartAddr[ 1], pucStartAddr[ 2], pucStartAddr[ 3],
                    pucStartAddr[ 4], pucStartAddr[ 5], pucStartAddr[ 6], pucStartAddr[ 7],
                    pucStartAddr[ 8], pucStartAddr[ 9]);
                break;
            case 11:
                LOG_FUNC("(%08lx) %02x %02x %02x %02x  %02x %02x %02x %02x - %02x %02x %02x\n",
                    (UINT_32)pucStartAddr,
                    pucStartAddr[ 0], pucStartAddr[ 1], pucStartAddr[ 2], pucStartAddr[ 3],
                    pucStartAddr[ 4], pucStartAddr[ 5], pucStartAddr[ 6], pucStartAddr[ 7],
                    pucStartAddr[ 8], pucStartAddr[ 9], pucStartAddr[10]);
                break;
            case 12:
                LOG_FUNC("(%08lx) %02x %02x %02x %02x  %02x %02x %02x %02x - %02x %02x %02x %02x\n",
                    (UINT_32)pucStartAddr,
                    pucStartAddr[ 0], pucStartAddr[ 1], pucStartAddr[ 2], pucStartAddr[ 3],
                    pucStartAddr[ 4], pucStartAddr[ 5], pucStartAddr[ 6], pucStartAddr[ 7],
                    pucStartAddr[ 8], pucStartAddr[ 9], pucStartAddr[10], pucStartAddr[11]);
                break;
            case 13:
                LOG_FUNC("(%08lx) %02x %02x %02x %02x  %02x %02x %02x %02x - %02x %02x %02x %02x  %02x\n",
                    (UINT_32)pucStartAddr,
                    pucStartAddr[ 0], pucStartAddr[ 1], pucStartAddr[ 2], pucStartAddr[ 3],
                    pucStartAddr[ 4], pucStartAddr[ 5], pucStartAddr[ 6], pucStartAddr[ 7],
                    pucStartAddr[ 8], pucStartAddr[ 9], pucStartAddr[10], pucStartAddr[11],
                    pucStartAddr[12]);
                break;
            case 14:
                LOG_FUNC("(%08lx) %02x %02x %02x %02x  %02x %02x %02x %02x - %02x %02x %02x %02x  %02x %02x\n",
                    (UINT_32)pucStartAddr,
                    pucStartAddr[ 0], pucStartAddr[ 1], pucStartAddr[ 2], pucStartAddr[ 3],
                    pucStartAddr[ 4], pucStartAddr[ 5], pucStartAddr[ 6], pucStartAddr[ 7],
                    pucStartAddr[ 8], pucStartAddr[ 9], pucStartAddr[10], pucStartAddr[11],
                    pucStartAddr[12], pucStartAddr[13]);
                break;
            case 15:
                LOG_FUNC("(%08lx) %02x %02x %02x %02x  %02x %02x %02x %02x - %02x %02x %02x %02x  %02x %02x %02x\n",
                    (UINT_32)pucStartAddr,
                    pucStartAddr[ 0], pucStartAddr[ 1], pucStartAddr[ 2], pucStartAddr[ 3],
                    pucStartAddr[ 4], pucStartAddr[ 5], pucStartAddr[ 6], pucStartAddr[ 7],
                    pucStartAddr[ 8], pucStartAddr[ 9], pucStartAddr[10], pucStartAddr[11],
                    pucStartAddr[12], pucStartAddr[13], pucStartAddr[14]);
                break;
            default:
                break;
            }
            u4Length = 0;
        }
    }

    LOG_FUNC("\n");

    return;
} /* end of dumpMemory8() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to dump a segment of memory in double words.
*
* \param[in] pucStartAddr   Pointer to the starting address of the memory to be dumped.
* \param[in] u4Length       Length of the memory to be dumped.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
dumpMemory32 (
    IN PUINT_32 pu4StartAddr,
    IN UINT_32  u4Length)
{
    PUINT_8 pucAddr;


    ASSERT(pu4StartAddr);

    LOG_FUNC("DUMP32 ADDRESS: %08lx, Length: %ld\n", (UINT_32)pu4StartAddr, u4Length);

    if (IS_NOT_ALIGN_4((UINT_32)pu4StartAddr)) {
        UINT_32 u4ProtrudeLen = sizeof(UINT_32) - ((UINT_32)pu4StartAddr % 4);


        u4ProtrudeLen = ((u4Length < u4ProtrudeLen) ? u4Length: u4ProtrudeLen);
        LOG_FUNC("pu4StartAddr is not at DW boundary.\n");
        pucAddr = (PUINT_8) &pu4StartAddr[0];

        switch (u4ProtrudeLen) {
            case 1:
                LOG_FUNC("(%08lx) %02x------\n",
                   (UINT_32)pu4StartAddr,
                   pucAddr[0]);
                break;
            case 2:
                LOG_FUNC("(%08lx) %02x%02x----\n",
                   (UINT_32)pu4StartAddr,
                   pucAddr[1], pucAddr[0]);
                break;
            case 3:
                LOG_FUNC("(%08lx) %02x%02x%02x--\n",
                   (UINT_32)pu4StartAddr,
                   pucAddr[2], pucAddr[1], pucAddr[0]);
                break;
            default:
                break;
        }

        u4Length -= u4ProtrudeLen;
        pu4StartAddr = (PUINT_32)((UINT_32)pu4StartAddr + u4ProtrudeLen);
    }

    while (u4Length > 0) {
        if (u4Length >= 16) {
            LOG_FUNC("(%08lx) %08lx %08lx %08lx %08lx\n",
                (UINT_32)pu4StartAddr,
                pu4StartAddr[0], pu4StartAddr[1], pu4StartAddr[2], pu4StartAddr[3]);
            pu4StartAddr += 4;
            u4Length -= 16;
        }
        else {
            switch (u4Length) {
            case 1:
                 pucAddr = (PUINT_8) &pu4StartAddr[0];
                 LOG_FUNC("(%08lx) ------%02x\n",
                    (UINT_32)pu4StartAddr,
                    pucAddr[0]);
                 break;
            case 2:
                 pucAddr = (PUINT_8) &pu4StartAddr[0];
                 LOG_FUNC("(%08lx) ----%02x%02x\n",
                    (UINT_32)pu4StartAddr,
                    pucAddr[1], pucAddr[0]);
                 break;
            case 3:
                 pucAddr = (PUINT_8) &pu4StartAddr[0];
                 LOG_FUNC("(%08lx) --%02x%02x%02x\n",
                    (UINT_32)pu4StartAddr,
                    pucAddr[2], pucAddr[1], pucAddr[0]);
                 break;
            case 4:
                 LOG_FUNC("(%08lx) %08lx\n",
                    (UINT_32)pu4StartAddr,
                    pu4StartAddr[0]);
                 break;
            case 5:
                 pucAddr = (PUINT_8) &pu4StartAddr[1];
                 LOG_FUNC("(%08lx) %08lx ------%02x\n",
                    (UINT_32)pu4StartAddr,
                    pu4StartAddr[0],
                    pucAddr[0]);
                 break;
            case 6:
                 pucAddr = (PUINT_8) &pu4StartAddr[1];
                 LOG_FUNC("(%08lx) %08lx ----%02x%02x\n",
                    (UINT_32)pu4StartAddr,
                    pu4StartAddr[0],
                    pucAddr[1], pucAddr[0]);
                 break;
            case 7:
                 pucAddr = (PUINT_8) &pu4StartAddr[1];
                 LOG_FUNC("(%08lx) %08lx --%02x%02x%02x\n",
                    (UINT_32)pu4StartAddr,
                    pu4StartAddr[0],
                    pucAddr[2], pucAddr[1], pucAddr[0]);
                 break;
            case 8:
                 LOG_FUNC("(%08lx) %08lx %08lx\n",
                    (UINT_32)pu4StartAddr,
                    pu4StartAddr[0], pu4StartAddr[1]);
                 break;
            case 9:
                 pucAddr = (PUINT_8) &pu4StartAddr[2];
                 LOG_FUNC("(%08lx) %08lx %08lx ------%02x\n",
                    (UINT_32)pu4StartAddr,
                    pu4StartAddr[0], pu4StartAddr[1],
                    pucAddr[0]);
                 break;
            case 10:
                 pucAddr = (PUINT_8) &pu4StartAddr[2];
                 LOG_FUNC("(%08lx) %08lx %08lx ----%02x%02x\n",
                    (UINT_32)pu4StartAddr,
                    pu4StartAddr[0], pu4StartAddr[1],
                    pucAddr[1], pucAddr[0]);
                 break;
            case 11:
                 pucAddr = (PUINT_8) &pu4StartAddr[2];
                 LOG_FUNC("(%08lx) %08lx %08lx --%02x%02x%02x\n",
                    (UINT_32)pu4StartAddr,
                    pu4StartAddr[0], pu4StartAddr[1],
                    pucAddr[2], pucAddr[1], pucAddr[0]);
                 break;
            case 12:
                 LOG_FUNC("(%08lx) %08lx %08lx %08lx\n",
                    (UINT_32)pu4StartAddr,
                    pu4StartAddr[0], pu4StartAddr[1], pu4StartAddr[2]);
                 break;
            case 13:
                 pucAddr = (PUINT_8) &pu4StartAddr[3];
                 LOG_FUNC("(%08lx) %08lx %08lx %08lx ------%02x\n",
                    (UINT_32)pu4StartAddr,
                    pu4StartAddr[0], pu4StartAddr[1], pu4StartAddr[2],
                    pucAddr[0]);
                 break;
            case 14:
                 pucAddr = (PUINT_8) &pu4StartAddr[3];
                 LOG_FUNC("(%08lx) %08lx %08lx %08lx ----%02x%02x\n",
                     (UINT_32)pu4StartAddr,
                     pu4StartAddr[0], pu4StartAddr[1], pu4StartAddr[2],
                     pucAddr[1], pucAddr[0]);
                 break;
            case 15:
                 pucAddr = (PUINT_8) &pu4StartAddr[3];
                 LOG_FUNC("(%08lx) %08lx %08lx %08lx --%02x%02x%02x\n",
                     (UINT_32)pu4StartAddr,
                     pu4StartAddr[0], pu4StartAddr[1], pu4StartAddr[2],
                     pucAddr[2], pucAddr[1], pucAddr[0]);
                 break;
            default:
                break;
            }
            u4Length = 0;
        }
    }

    return;
} /* end of dumpMemory32() */
#endif /* DBG */


