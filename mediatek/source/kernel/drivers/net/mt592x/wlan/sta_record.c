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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/sta_record.c#1 $
*/

/*! \file   "sta_record.c"
    \brief  This file contain the management function of adjacent station records.

		A station record is represent a STA including non-AP STA and AP, when we
	receive a frame, driver will update the information to the corresponding STA
    record for connection & frame reception handling.
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
** $Log: sta_record.c $
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\22 2008-12-01 21:06:52 GMT mtk01461
**  Fix Lint Warning 613: Possible use of null pointer 'pucCurrBuf'
**  \main\maintrunk.MT5921\21 2008-12-01 18:20:06 GMT mtk01088
**  remove non-used code
**  \main\maintrunk.MT5921\20 2008-11-28 16:51:12 GMT mtk01088
**  fixed the lint warning
**  \main\maintrunk.MT5921\19 2008-08-25 13:55:27 GMT mtk01461
**  Update driver for Code Review
**  \main\maintrunk.MT5921\18 2008-07-10 14:09:00 GMT mtk01461
**  Fix the warning msg for prefast
**  \main\maintrunk.MT5921\17 2008-06-02 20:21:35 GMT mtk01461
**  Add Invalid List check for error handling if LIST was not initialized
**  \main\maintrunk.MT5921\16 2008-05-30 18:54:30 GMT mtk01461
**  Remove staRecGetStaRecordByLastActivityForIBSS()
**  \main\maintrunk.MT5921\15 2008-03-29 13:56:34 GMT mtk01461
**  Add MAGIC GUID for Link List
**  \main\maintrunk.MT5921\14 2008-03-23 22:49:02 GMT mtk01461
**  Add remove StaRecord and search last activity for IBSS
**  \main\maintrunk.MT5921\13 2008-03-19 15:22:07 GMT mtk01461
**  Add defragment buffer clean up path in STA_RECORD_T
**  \main\maintrunk.MT5921\12 2008-03-13 15:32:07 GMT mtk01461
**  Refine the relationship between SCAN result and STA record, lifetime, aging policy etc
**  \main\maintrunk.MT5921\11 2008-02-01 10:10:44 GMT mtk01385
**  1. Fix WinCE 4.2 compiling error.
**  \main\maintrunk.MT5921\10 2008-01-24 15:02:13 GMT mtk01461
**  Update initial value for SEQ_CTRL saved value
**  \main\maintrunk.MT5921\9 2008-01-07 15:06:55 GMT mtk01461
**  Add PhyType & AdHocMode Selection Support
**  \main\maintrunk.MT5921\8 2007-11-13 17:06:23 GMT mtk01461
**  Fix the unexpected assert after chip reset - add memzero to sta rec initial
**  \main\maintrunk.MT5921\7 2007-11-02 00:57:20 GMT mtk01461
**  Unify TX Path for Normal and IBSS Power Save + IBSS neighbor learning
**  \main\maintrunk.MT5921\6 2007-10-25 18:05:15 GMT mtk01461
**  Add VOIP SCAN Support  & Refine Roaming
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
* \brief Initialize the list head of Station Record and free list.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
staRecInitialize (
    IN P_ADAPTER_T prAdapter
    )
{
    P_STA_INFO_T prStaInfo;
    PUINT_8 pucMemHandle;
    P_STA_RECORD_T prStaRec;
    UINT_32 i;


    ASSERT(prAdapter);
    prStaInfo = &prAdapter->rStaInfo;

    //4 <0> Clear allocated memory.
    kalMemZero((PVOID) prStaInfo->pucStaRecCached, prStaInfo->u4StaRecCachedSize);

    ASSERT(IS_ALIGN_4((UINT_32)prStaInfo->pucStaRecCached));

    pucMemHandle = prStaInfo->pucStaRecCached;

    LINK_INITIALIZE(&prStaInfo->rFreeStaRecList);

    for (i = 0; i < CFG_MAX_NUM_STA_RECORD; i++) {

        prStaRec = (P_STA_RECORD_T)pucMemHandle;

        STA_RECORD_SET_GUID(prStaRec);

        LINK_INSERT_TAIL(&prStaInfo->rFreeStaRecList, &prStaRec->rLinkEntry);

        pucMemHandle += ALIGN_4(sizeof(STA_RECORD_T));
    }

    /* Check if the memory allocation consist with this initialization function */
    ASSERT((UINT_32)(pucMemHandle - prStaInfo->pucStaRecCached) == prStaInfo->u4StaRecCachedSize);

    for (i = 0; i < STA_RECORD_HASH_NUM; i++) {
        LINK_INITIALIZE(&prStaInfo->arValidStaRecList[i]);
    }

    prStaInfo->ucValidStaRecNum = 0;

    return;
} /* end of staRecInitialize() */


/*----------------------------------------------------------------------------*/
/*!
* \brief Find the corresponding Station Record according to given Address.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
* \param[in] pucStaAddr Given Address.
*
* \return   Pointer to Station Record, if found. NULL, if not found
*/
/*----------------------------------------------------------------------------*/
P_STA_RECORD_T
staRecGetStaRecordByAddr (
    IN P_ADAPTER_T prAdapter,
    IN PUINT_8 pucStaAddr
    )
{
    P_STA_INFO_T prStaInfo;
    P_LINK_T prValidStaRecList;
    P_STA_RECORD_T prStaRec;


    ASSERT(prAdapter);
    ASSERT(pucStaAddr);
    prStaInfo = &prAdapter->rStaInfo;

    if (pucStaAddr) {
        /* To get the proper valid list through hash function */
        prValidStaRecList = &prStaInfo->arValidStaRecList[STA_RECORD_HASH_FUNC(pucStaAddr)];

        /* Check if such STA record exists in a valid list */
        LINK_FOR_EACH_ENTRY(prStaRec, prValidStaRecList, rLinkEntry, STA_RECORD_T) {

            STA_RECORD_CHK_GUID(prStaRec);

            if (EQUAL_MAC_ADDR(pucStaAddr, prStaRec->aucMacAddr)) {
                return prStaRec;
            }
        }
    }

    return (P_STA_RECORD_T)NULL;

} /* end of staRecGetStaRecordByAddr() */


/*----------------------------------------------------------------------------*/
/*!
* \brief Add a new Station Record to the list or get current exist one according
*        to given Address.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
* \param[in] pucStaAddr Given Address.
*
* \return   Pointer to Station Record, if found. It shouldn't return NULL.
*/
/*----------------------------------------------------------------------------*/
P_STA_RECORD_T
staRecGetStaRecordByAddrOrAddIfNotExist (
    IN P_ADAPTER_T prAdapter,
    IN PUINT_8 pucStaAddr
    )
{
    P_STA_INFO_T prStaInfo;
    P_LINK_T prValidStaRecList;
    P_LINK_T prFreeStaRecList;
    P_STA_RECORD_T prStaRec;
    UINT_32 i;


    ASSERT(prAdapter);
    ASSERT(pucStaAddr);
    prStaInfo = &prAdapter->rStaInfo;

    //4 <1> To get the proper valid list through hash function
    prValidStaRecList = &prStaInfo->arValidStaRecList[STA_RECORD_HASH_FUNC(pucStaAddr)];

    //4 <2> Check if such STA record exists in a valid list
    LINK_FOR_EACH_ENTRY(prStaRec, prValidStaRecList, rLinkEntry, STA_RECORD_T) {

        STA_RECORD_CHK_GUID(prStaRec);

        if (EQUAL_MAC_ADDR(prStaRec->aucMacAddr, pucStaAddr)) {
            return prStaRec;
        }
    }

    //4 <2> No such Record, try to alloc an entry of BSS Desc for this new BSS.
    do {
        prFreeStaRecList = &prStaInfo->rFreeStaRecList;

        /* Attempt to allocate a free station record from the free list. */
        LINK_REMOVE_HEAD(prFreeStaRecList, prStaRec, P_STA_RECORD_T);
        if (prStaRec) {
            break;
        }

        //4 <2.1> Remove the timeout one.
        staRecRemoveStaRecordByPolicy(prAdapter, (STA_RECORD_RM_POLICY_EXCLUDE_STATE_3 | \
                                                  STA_RECORD_RM_POLICY_TIMEOUT));

        //4 <2.2> Try to get an entry again.
        LINK_REMOVE_HEAD(prFreeStaRecList, prStaRec, P_STA_RECORD_T);
        if (prStaRec) {
            break;
        }

        //4 <2.3> Remove the oldest one.
        staRecRemoveStaRecordByPolicy(prAdapter, (STA_RECORD_RM_POLICY_EXCLUDE_STATE_3 | \
                                                  STA_RECORD_RM_POLICY_OLDEST));

        //4 <2.4> Try to get an entry again.
        LINK_REMOVE_HEAD(prFreeStaRecList, prStaRec, P_STA_RECORD_T);
        if (prStaRec) {
            break;
        }

        /* TODO(Kevin): Actually we will encounter this case if all of the 32 STA_RECORD_Ts
         * are occupied by 1 AP + 31 DLS STAs. Because they are STATE_3.
         */
        ASSERT(prStaRec);
    }
    while (FALSE);


    if (prStaRec) {

        STA_RECORD_CHK_GUID(prStaRec);

        /* Clear the acquired station record. */
        kalMemZero((PVOID)prStaRec, sizeof(STA_RECORD_T));

        STA_RECORD_SET_GUID(prStaRec);

        /* Fill address. */
        COPY_MAC_ADDR(prStaRec->aucMacAddr, pucStaAddr);

        /* Fill the initial STA state. */
        prStaRec->ucStaState = STA_STATE_1;

        /* Fill the initial Status/Reason Code. */
        prStaRec->u2StatusCode = STATUS_CODE_SUCCESSFUL;
        prStaRec->u2ReasonCode = REASON_CODE_RESERVED;

        /* Fill the initial SEQ_CTRL_NUM of previous frame. */
        prStaRec->u2LastRxSeqCtrl = INVALID_SEQ_CTRL_NUM;
        for (i = 0; i < TID_NUM; i++) {
            prStaRec->u2TIDLastRxSeqCtrl[i] = INVALID_SEQ_CTRL_NUM;
        }

        /* Set the power management mode of the STA to Active mode. */
        //prStaRec->ucPowerMgtMode = PWR_MGT_MODE_AM;

        /* To get the proper valid list through hash function */
        prValidStaRecList = &prStaInfo->arValidStaRecList[STA_RECORD_HASH_FUNC(pucStaAddr)];

        /* Add this STA record to the valid STA record list -
         * Let the entry with recent activity in the head.
         */
        LINK_INSERT_HEAD(prValidStaRecList, &prStaRec->rLinkEntry);

        /* Increase the counter of valid STA record */
        prStaInfo->ucValidStaRecNum++;

        DBGLOG(MGT, TRACE, ("Add record for STA ["MACSTR"]\n", \
            MAC2STR(pucStaAddr)));

        DBGLOG(MGT, INFO, ("STA record allocated number = %d\n", \
            prStaInfo->ucValidStaRecNum));
    }

    return prStaRec;

} /* end of staRecGetStaRecordByAddrOrAddIfNotExist() */


/*----------------------------------------------------------------------------*/
/*!
* \brief Remove a Station Record from the according to given Removing Policy
*
* \param[in] prAdapter      Pointer to the Adapter structure.
* \param[in] u4RemovePolicy Removing Policy.
*
* \return   (none)
*/
/*----------------------------------------------------------------------------*/
VOID
staRecRemoveStaRecordByPolicy (
    IN P_ADAPTER_T prAdapter,
    IN UINT_32 u4RemovePolicy
    )
{
    P_STA_INFO_T prStaInfo;
    P_LINK_T prValidStaRecList;
    P_STA_RECORD_T prStaRec;
    P_FRAG_INFO_T prFragInfo;
    UINT_32 i, j;

    DEBUGFUNC("staRecRemoveStaRecordByPolicy");


    ASSERT(prAdapter);
    prStaInfo = &prAdapter->rStaInfo;

    if (u4RemovePolicy & STA_RECORD_RM_POLICY_TIMEOUT) {
        P_STA_RECORD_T prStaRecNext;
        OS_SYSTIME rCurrentTime;


        GET_CURRENT_SYSTIME(&rCurrentTime);

        for (i = 0; i < STA_RECORD_HASH_NUM; i++) {
            prValidStaRecList = &prStaInfo->arValidStaRecList[i];

            LINK_FOR_EACH_ENTRY_SAFE(prStaRec, prStaRecNext, prValidStaRecList, rLinkEntry, STA_RECORD_T) {

                STA_RECORD_CHK_GUID(prStaRec);

                if ((u4RemovePolicy & STA_RECORD_RM_POLICY_EXCLUDE_STATE_3) &&
                    (prStaRec->ucStaState == STA_STATE_3)) {
                    /* NOTE: Don't remove the Peer STA which is in STATE_3.
                     * e.g. 1. AP, 2. DLS, 3. Default Entry(BSSID) for AdHoc Mode.
                     */
                    continue;
                }

                if (CHECK_FOR_TIMEOUT(rCurrentTime, prStaRec->rUpdateTime,
                    SEC_TO_SYSTIME(STA_RECORD_TIMEOUT_SEC))) {

                    for (j = 0; j < MAX_NUM_CONCURRENT_FRAGMENTED_MSDUS; j++) {
                        prFragInfo = &prStaRec->rFragInfo[j];

                        if (prFragInfo->pr1stFrag) {
                            nicRxReturnRFB(prAdapter, prFragInfo->pr1stFrag);
                            prFragInfo->pr1stFrag = (P_SW_RFB_T)NULL;
                        }
                    }

                    /* Remove this BSS Desc from the BSS Desc list */
                    LINK_REMOVE_KNOWN_ENTRY(prValidStaRecList, prStaRec);

                    DBGLOG(MGT, TRACE, ("Remove Sta Record ["MACSTR"]\n", \
                        MAC2STR(prStaRec->aucMacAddr)));

                    /* Decrease the counter of valid STA record */
                    prStaInfo->ucValidStaRecNum--;

                    /* Return this BSS Desc to the free BSS Desc list. */
                    LINK_INSERT_TAIL(&prStaInfo->rFreeStaRecList, &prStaRec->rLinkEntry);
                }
            }
        }
    }
    else if (u4RemovePolicy & STA_RECORD_RM_POLICY_OLDEST) {
        P_STA_RECORD_T prStaRecOldest = (P_STA_RECORD_T)NULL;
        P_LINK_T prValidStaRecListOldest = (P_LINK_T)NULL;


        for (i = 0; i < STA_RECORD_HASH_NUM; i++) {
            prValidStaRecList = &prStaInfo->arValidStaRecList[i];

            LINK_FOR_EACH_ENTRY(prStaRec, prValidStaRecList, rLinkEntry, STA_RECORD_T) {

                STA_RECORD_CHK_GUID(prStaRec);

                if ((u4RemovePolicy & STA_RECORD_RM_POLICY_EXCLUDE_STATE_3) &&
                    (prStaRec->ucStaState == STA_STATE_3)) {
                    /* NOTE: Don't remove the Peer STA which is in STATE_3.
                     * e.g. 1. AP, 2. DLS, 3. Default Entry(BSSID) for AdHoc Mode.
                     */
                    continue;
                }

                if (!prStaRecOldest) { /* 1st element */
                    prStaRecOldest = prStaRec;
                    prValidStaRecListOldest = prValidStaRecList;
                    continue;
                }

                if (TIME_BEFORE(prStaRec->rUpdateTime, prStaRecOldest->rUpdateTime)) {
                    prStaRecOldest = prStaRec;
                    prValidStaRecListOldest = prValidStaRecList;
                }
            }
        }

        if (prStaRecOldest) {

            for (j = 0; j < MAX_NUM_CONCURRENT_FRAGMENTED_MSDUS; j++) {
                prFragInfo = &prStaRec->rFragInfo[j];

                if (prFragInfo->pr1stFrag) {
                    nicRxReturnRFB(prAdapter, prFragInfo->pr1stFrag);
                    prFragInfo->pr1stFrag = (P_SW_RFB_T)NULL;
                }
            }

            /* Remove this Sta Record from the BSS Desc list */
            LINK_REMOVE_KNOWN_ENTRY(prValidStaRecListOldest, prStaRecOldest);

            DBGLOG(MGT, TRACE, ("Remove Sta Record ["MACSTR"]\n", \
                MAC2STR(prStaRecOldest->aucMacAddr)));

            /* Decrease the counter of valid STA record */
            prStaInfo->ucValidStaRecNum--;

            /* Return this BSS Desc to the free BSS Desc list. */
            LINK_INSERT_TAIL(&prStaInfo->rFreeStaRecList, &prStaRecOldest->rLinkEntry);
        }
    }
    else if (u4RemovePolicy & STA_RECORD_RM_POLICY_ENTIRE) {
        P_STA_RECORD_T prStaRecNext;

        for (i = 0; i < STA_RECORD_HASH_NUM; i++) {
            prValidStaRecList = &prStaInfo->arValidStaRecList[i];

            LINK_FOR_EACH_ENTRY_SAFE(prStaRec, prStaRecNext, prValidStaRecList, rLinkEntry, STA_RECORD_T) {

                STA_RECORD_CHK_GUID(prStaRec);

                if ((u4RemovePolicy & STA_RECORD_RM_POLICY_EXCLUDE_STATE_3) &&
                    (prStaRec->ucStaState == STA_STATE_3)) {
                    /* NOTE: Don't remove the Peer STA which is in STATE_3.
                     * e.g. 1. AP, 2. DLS, 3. Default Entry(BSSID) for AdHoc Mode.
                     */
                    continue;
                }

                for (j = 0; j < MAX_NUM_CONCURRENT_FRAGMENTED_MSDUS; j++) {
                    prFragInfo = &prStaRec->rFragInfo[j];

                    if (prFragInfo->pr1stFrag) {
                        nicRxReturnRFB(prAdapter, prFragInfo->pr1stFrag);
                        prFragInfo->pr1stFrag = (P_SW_RFB_T)NULL;
                    }
                }

                /* Remove this BSS Desc from the BSS Desc list */
                LINK_REMOVE_KNOWN_ENTRY(prValidStaRecList, prStaRec);

                DBGLOG(MGT, TRACE, ("Remove Sta Record ["MACSTR"]\n", \
                    MAC2STR(prStaRec->aucMacAddr)));

                /* Decrease the counter of valid STA record */
                prStaInfo->ucValidStaRecNum--;

                /* Return this BSS Desc to the free BSS Desc list. */
                LINK_INSERT_TAIL(&prStaInfo->rFreeStaRecList, &prStaRec->rLinkEntry);
            }
        }

    }

    return;
} /* end of staRecRemoveStaRecordByPolicy() */


/*----------------------------------------------------------------------------*/
/*!
* \brief Remove a Station Record for IBSS, we'll keep a Station Record with STA_STATE_3
*        for keep current BSSID while lost connection.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
*
* \return   (none)
*/
/*----------------------------------------------------------------------------*/
VOID
staRecRemoveStaRecordForIBSS (
    IN P_ADAPTER_T prAdapter
    )
{
    P_STA_INFO_T prStaInfo;
    P_LINK_T prValidStaRecList;
    P_STA_RECORD_T prStaRec;
    P_STA_RECORD_T prStaRecNext;
    P_FRAG_INFO_T prFragInfo;
    UINT_32 i, j;

    DEBUGFUNC("staRecRemoveStaRecordForIBSS");


    ASSERT(prAdapter);
    prStaInfo = &prAdapter->rStaInfo;


    for (i = 0; i < STA_RECORD_HASH_NUM; i++) {
        prValidStaRecList = &prStaInfo->arValidStaRecList[i];

        LINK_FOR_EACH_ENTRY_SAFE(prStaRec, prStaRecNext, prValidStaRecList, rLinkEntry, STA_RECORD_T) {

            STA_RECORD_CHK_GUID(prStaRec);

            if (prStaRec->ucStaState == STA_STATE_3) {
                /* NOTE: STA with STATE_3 in IBSS is represent as the Default Entry
                 * (BSSID), no such peer exist actually.
                 */
                continue;
            }

            for (j = 0; j < MAX_NUM_CONCURRENT_FRAGMENTED_MSDUS; j++) {
                prFragInfo = &prStaRec->rFragInfo[j];

                if (prFragInfo->pr1stFrag) {
                    nicRxReturnRFB(prAdapter, prFragInfo->pr1stFrag);
                    prFragInfo->pr1stFrag = (P_SW_RFB_T)NULL;
                }
            }

            /* Remove this BSS Desc from the BSS Desc list */
            LINK_REMOVE_KNOWN_ENTRY(prValidStaRecList, prStaRec);

            DBGLOG(MGT, TRACE, ("Remove Sta Record ["MACSTR"]\n", \
                MAC2STR(prStaRec->aucMacAddr)));

            /* Decrease the counter of valid STA record */
            prStaInfo->ucValidStaRecNum--;

            /* Return this BSS Desc to the free BSS Desc list. */
            LINK_INSERT_TAIL(&prStaInfo->rFreeStaRecList, &prStaRec->rLinkEntry);
        }
    }

    return;
} /* end of staRecRemoveStaRecordForIBSS() */


/*----------------------------------------------------------------------------*/
/*!
* \brief Reset all STA_STATE flag for all Station Records.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
*
* \return   (none)
*/
/*----------------------------------------------------------------------------*/
VOID
staRecRemoveStateFlagOfAllStaRecords (
    IN P_ADAPTER_T prAdapter
    )
{
    P_STA_INFO_T prStaInfo;
    P_LINK_T prValidStaRecList;
    P_STA_RECORD_T prStaRec;
    UINT_32 i;


    ASSERT(prAdapter);
    prStaInfo = &prAdapter->rStaInfo;

    for (i = 0; i < STA_RECORD_HASH_NUM; i++) {
        prValidStaRecList = &prStaInfo->arValidStaRecList[i];

        if (LINK_IS_VALID(prValidStaRecList)) {
            LINK_FOR_EACH_ENTRY(prStaRec, prValidStaRecList, rLinkEntry, STA_RECORD_T) {

                STA_RECORD_CHK_GUID(prStaRec);

                prStaRec->ucStaState = STA_STATE_1;
            }
        }
    }

    return;
} /* end of staRecRemoveStateFlagOfAllStaRecords() */


/*----------------------------------------------------------------------------*/
/*!
* \brief Reset all Status and Reason Code for all Station Records.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
*
* \return   (none)
*/
/*----------------------------------------------------------------------------*/
VOID
staRecClearStatusAndReasonCode (
    IN P_ADAPTER_T prAdapter
    )
{
    P_STA_INFO_T prStaInfo;
    P_LINK_T prValidStaRecList;
    P_STA_RECORD_T prStaRec;
    UINT_32 i;


    ASSERT(prAdapter);
    prStaInfo = &prAdapter->rStaInfo;

    for (i = 0; i < STA_RECORD_HASH_NUM; i++) {
        prValidStaRecList = &prStaInfo->arValidStaRecList[i];

        /* Check if the prValidStaRecList is valid, skip if the prValidStaRecList has not been
         * initiated.
         */
        if (LINK_IS_VALID(prValidStaRecList)) {
            LINK_FOR_EACH_ENTRY(prStaRec, prValidStaRecList, rLinkEntry, STA_RECORD_T) {

                STA_RECORD_CHK_GUID(prStaRec);

                prStaRec->u2StatusCode = STATUS_CODE_SUCCESSFUL;
                prStaRec->u2ReasonCode = REASON_CODE_RESERVED;
                prStaRec->ucJoinFailureCount = 0;
            }
        }
    }

    return;
} /* end of staRecClearStatusAndReasonCode() */


/*----------------------------------------------------------------------------*/
/*!
* \brief Check the defragment buffer of all Station Records for housekeeping.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
*
* \return   (none)
*/
/*----------------------------------------------------------------------------*/
VOID
staRecCheckDefragBufOfAllStaRecords (
    IN P_ADAPTER_T prAdapter
    )
{
    P_STA_INFO_T prStaInfo;
    P_LINK_T prValidStaRecList;
    P_STA_RECORD_T prStaRec;
    P_FRAG_INFO_T prFragInfo;
    OS_SYSTIME rCurrentTime;
    P_RX_CTRL_T prRxCtrl;
    BOOLEAN fgIsDefragQueNonEmpty;
    UINT_32 i, j;

    DEBUGFUNC("staRecCheckDefragBufOfAllStaRecords");

    ASSERT(prAdapter);
    prStaInfo = &prAdapter->rStaInfo;
    prRxCtrl = &prAdapter->rRxCtrl;

    GET_CURRENT_SYSTIME(&rCurrentTime);

    fgIsDefragQueNonEmpty = FALSE;

    for (i = 0; i < STA_RECORD_HASH_NUM; i++) {
        prValidStaRecList = &prStaInfo->arValidStaRecList[i];

        LINK_FOR_EACH_ENTRY(prStaRec, prValidStaRecList, rLinkEntry, STA_RECORD_T) {

            STA_RECORD_CHK_GUID(prStaRec);

            for (j = 0; j < MAX_NUM_CONCURRENT_FRAGMENTED_MSDUS; j++) {

                prFragInfo = &prStaRec->rFragInfo[j];

                if (prFragInfo->pr1stFrag) {

                    /* I. If the receive timer for the MSDU or MMPDU that is stored in the
                     * fragments queue exceeds dot11MaxReceiveLifetime, we discard the
                     * uncompleted fragments.
                     * II. If we didn't receive the last MPDU for a period, we use
                     * this function for remove frames.
                     */
                    if (CHECK_FOR_EXPIRATION(rCurrentTime,
                        prFragInfo->rReceiveLifetimeLimit)) {

                        nicRxReturnRFB(prAdapter, prFragInfo->pr1stFrag);

                        prFragInfo->pr1stFrag = (P_SW_RFB_T)NULL;
                    }
                    else {
                        fgIsDefragQueNonEmpty = TRUE;
                    }
                }
            }
        }
    }

    prRxCtrl->fgIsDefragQueNonEmpty = fgIsDefragQueNonEmpty;

    return;
} /* end of staRecCheckDefragBufOfAllStaRecords() */


#if CFG_DBG_STA_RECORD
/*----------------------------------------------------------------------------*/
/*!
* \brief This function is used to print current status of Station Record usage.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
* \param[in] pucBuffer      Pointer to the message buffer.
* \param[out] pu4Count      Pointer to the buffer of message length count.
*
* \return   (none)
*/
/*----------------------------------------------------------------------------*/
VOID
staRecQueryStatus (
    IN P_ADAPTER_T prAdapter,
    IN PUINT_8 pucBuffer,
    OUT PUINT_32 pu4Count
    )
{
    P_STA_INFO_T prStaInfo;
    P_LINK_T prValidStaRecList;
    P_STA_RECORD_T prStaRec;
    PUINT_8 pucCurrBuf = pucBuffer;
    UINT_32 i;


    ASSERT(prAdapter);
    if (pucBuffer) {} /* For Windows, we'll print directly instead of sprintf() */
    ASSERT(pu4Count);
  
    prStaInfo = &prAdapter->rStaInfo;

    SPRINTF(pucCurrBuf, ("\n\nSTA RECORD STATUS:"));
    SPRINTF(pucCurrBuf, ("\n=================="));
#if CFG_IBSS_POWER_SAVE
    {
        UINT_32 j;

        SPRINTF(pucCurrBuf, ("\n                      TC0       TC1       TC2       TC3      TCS0       TC4"));
        SPRINTF(pucCurrBuf, ("\n---------------------------------------------------------------------------"));
        SPRINTF(pucCurrBuf, ("\nBMC WAIT QUEUE :"));
        for (j = 0; j < TC_NUM; j++) {
            SPRINTF(pucCurrBuf, ("%9ld ", prStaInfo->arGcStaWaitQueue[j].u4NumElem));
        }
        SPRINTF(pucCurrBuf, ("\n* fgIsAllAdhocStaAwake : %d",
            prStaInfo->fgIsAllAdhocStaAwake));
        SPRINTF(pucCurrBuf, ("\n"));
    }
#endif /* CFG_IBSS_POWER_SAVE */

    SPRINTF(pucCurrBuf, ("\nFREE STA RECORD LIST          :%8ld",
        prStaInfo->rFreeStaRecList.u4NumElem));

    SPRINTF(pucCurrBuf, ("\nTOTAL VALID STA RECORD NUM    :%8d",
        prStaInfo->ucValidStaRecNum));


    for (i = 0; i < STA_RECORD_HASH_NUM; i++) {
        prValidStaRecList = &prStaInfo->arValidStaRecList[i];

    SPRINTF(pucCurrBuf, ("\nVALID STA RECORD LIST[%ld]      :%8ld",
        i, prValidStaRecList->u4NumElem));

        LINK_FOR_EACH_ENTRY(prStaRec, prValidStaRecList, rLinkEntry, STA_RECORD_T) {

            SPRINTF(pucCurrBuf, ("\nSTA MAC ADDR ["MACSTR"]: \n    STATE = %s",
                MAC2STR(prStaRec->aucMacAddr),
                ((prStaRec->ucStaState == STA_STATE_3) ? "STA_STATE_3" :
                 ((prStaRec->ucStaState == STA_STATE_2) ? "STA_STATE_2" :
                  ((prStaRec->ucStaState == STA_STATE_1) ? "STA_STATE_1" : "STA_STATE_UNKNOWN"))) ));

            SPRINTF(pucCurrBuf, ("\n    STATUS CODE = %d", prStaRec->u2StatusCode));
            SPRINTF(pucCurrBuf, ("\n    REASON CODE = %d", prStaRec->u2ReasonCode));
#if CFG_IBSS_POWER_SAVE
            {
                UINT_32 j;


                SPRINTF(pucCurrBuf, ("\n                      TC0       TC1       TC2       TC3      TCS0       TC4"));
                SPRINTF(pucCurrBuf, ("\n---------------------------------------------------------------------------"));
                SPRINTF(pucCurrBuf, ("\nSTA WAIT QUEUE :"));
                for (j = 0; j < TC_NUM; j++) {
                    SPRINTF(pucCurrBuf, ("%9ld ", prStaRec->arStaWaitQueue[j].u4NumElem));
                }
                SPRINTF(pucCurrBuf, ("\n* fgIsAdhocStaAwake : %d",
                    prStaRec->fgIsAdhocStaAwake));
                SPRINTF(pucCurrBuf, ("\n"));
            }
#endif /* CFG_IBSS_POWER_SAVE */
        }
    }

    SPRINTF(pucCurrBuf, ("\n"));

    *pu4Count = (UINT_32)((UINT_32)pucCurrBuf - (UINT_32)pucBuffer);

    return;

} /* end of staRecQueryStatus() */
#endif /* CFG_DBG_STA_RECORD */




