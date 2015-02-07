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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/bss.c#2 $
*/

/*! \file   "bss.c"
    \brief  This file contain the management function of BSS

        This file contain some management function in BSS' point of view.
    (Infrastructure)
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
** $Log: bss.c $
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\23 2009-04-03 14:49:30 GMT mtk01461
**  Revert previous change, and do remove Scan Record at arbFsmRunEventConnectionDiagnosis
**  \main\maintrunk.MT5921\22 2009-04-03 00:09:04 GMT mtk01461
**  Remove current BSS if do abort to reduce the redundant auth retry
**  \main\maintrunk.MT5921\21 2009-02-18 21:01:36 GMT mtk01461
**  Add RSN/WPA IE change detection
**  \main\maintrunk.MT5921\20 2009-02-18 19:17:40 GMT mtk01461
**  Update condition of Beacon change detection
**  \main\maintrunk.MT5921\19 2009-02-16 23:45:06 GMT mtk01461
**  Revise comment
**  \main\maintrunk.MT5921\18 2009-02-16 15:51:25 GMT mtk01461
**  Revise code to flush scan result while performing ABORT event
**  \main\maintrunk.MT5921\17 2009-02-13 21:02:13 GMT mtk01461
**  Add Capability change detection & SSID change detection
**  \main\maintrunk.MT5921\16 2008-12-01 21:02:32 GMT mtk01461
**  \main\maintrunk.MT5921\15 2008-12-01 18:16:39 GMT mtk01088
**  fixed the "possible using null pointer" lint warning
**  \main\maintrunk.MT5921\14 2008-11-28 16:21:07 GMT mtk01088
**  fixed the lint warning
**  \main\maintrunk.MT5921\13 2008-10-22 10:58:14 GMT mtk01461
**  Update for lint diagnosis support
**  \main\maintrunk.MT5921\12 2008-09-12 11:24:13 GMT mtk01461
**  Refine code - Add CFG_TX_FRAGMENT
**  \main\maintrunk.MT5921\11 2008-08-27 22:36:53 GMT mtk01461
**  \main\maintrunk.MT5921\10 2008-08-21 16:43:46 GMT mtk01461
**  \main\maintrunk.MT5921\9 2008-03-31 21:00:47 GMT mtk01461
**  Add comment
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

extern PHY_ATTRIBUTE_T rPhyAttributes[];

/*******************************************************************************
*                              C O N S T A N T S
********************************************************************************
*/
#if DBG
/*lint -save -e64 Type mismatch */
static PUINT_8 apucDebugRateIndex[] = {
    DISP_STRING("RATE_1M_INDEX"),
    DISP_STRING("RATE_2M_INDEX"),
    DISP_STRING("RATE_5_5M_INDEX"),
    DISP_STRING("RATE_11M_INDEX"),
    DISP_STRING("RATE_22M_INDEX"),
    DISP_STRING("RATE_33M_INDEX"),
    DISP_STRING("RATE_6M_INDEX"),
    DISP_STRING("RATE_9M_INDEX"),
    DISP_STRING("RATE_12M_INDEX"),
    DISP_STRING("RATE_18M_INDEX"),
    DISP_STRING("RATE_24M_INDEX"),
    DISP_STRING("RATE_36M_INDEX"),
    DISP_STRING("RATE_48M_INDEX"),
    DISP_STRING("RATE_54M_INDEX")
};
/*lint -restore */
#endif /* DBG */

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
* \brief This function is used to process Beacon from current associated AP.
*        Including ShortSlotTime, ERP and WMM detection.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
* \param[in] prBSSDesc  Pointer to the BSS Descriptor.
* \param[in] prSWRfb    Pointer to the receiving frame buffer.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
bssProcessBeacon (
    IN P_ADAPTER_T prAdapter,
    IN P_BSS_DESC_T prBSSDesc,
    IN P_SW_RFB_T prSwRfb
    )
{
    P_BSS_INFO_T prBssInfo;
    P_WLAN_BEACON_FRAME_T prWlanBeaconFrame;
    P_CONNECTION_SETTINGS_T prConnSettings;
    P_STA_RECORD_T prStaRec = NULL;
    UINT_16 u2CapInfoChanges;
    
    DEBUGFUNC("bssProcessBeacon");


    ASSERT(prAdapter);
    ASSERT(prBSSDesc);
    ASSERT(prSwRfb);
    prBssInfo = &prAdapter->rBssInfo;
    prWlanBeaconFrame = (P_WLAN_BEACON_FRAME_T)prSwRfb->pvHeader;
    prConnSettings = &prAdapter->rConnSettings;

    //4 <1> Check if the BSS_DESC_T is IBSS.
    if (prBSSDesc->eBSSType != BSS_TYPE_INFRASTRUCTURE) {
        return;
    }

    //4 <2> Check if the BSS_DESC_T's BSSID is identical to mine.
    if (UNEQUAL_MAC_ADDR(prBssInfo->aucBSSID, prBSSDesc->aucBSSID)) {
        return;
    }

    //4 <3> Change detection of SSID
    if ((!prBSSDesc->fgIsHiddenSSID) &&
        UNEQUAL_SSID(prBssInfo->aucSSID, prBssInfo->ucSSIDLen,
                     prBSSDesc->aucSSID, prBSSDesc->ucSSIDLen)) {

        /* NOTE(Kevin): If AP change its SSID without notification, we should
         * leave this BSS immediately.
         */
        arbFsmRunEventAbort(prAdapter, TRUE);
        return;
    }

    //4 <4> Change detection of channel
    if (prBSSDesc->ucChannelNum != prBssInfo->ucChnl) {

        /* NOTE(Kevin): If AP change its CHANNEL without notification, we should
         * leave this BSS immediately.
         */
        arbFsmRunEventAbort(prAdapter, TRUE);
        return;
    }

    //4 <5> Change detection of BSS Capability
    u2CapInfoChanges = prBssInfo->u2CapInfo ^ prBSSDesc->u2CapInfo;
    if (u2CapInfoChanges) {
        DBGLOG(JOIN, INFO,
            ("Capability changed: Before=%04X After=%04X\n", prBssInfo->u2CapInfo, prBSSDesc->u2CapInfo));
    }

    //4 <5.1> Change detection of Privacy Bit
    if (u2CapInfoChanges & CAP_INFO_PRIVACY) {

        arbFsmRunEventAbort(prAdapter, TRUE);
        return;
    }

    //4 <6> Change detection of RSN/WPA IE
    if (prBssInfo->fgIsWPAorWPA2Enabled) {
        if (!(prBSSDesc->prIEWPA) && !(prBSSDesc->prIERSN)) {
            arbFsmRunEventAbort(prAdapter, TRUE);
            return;
        }
    }

    //4 <7> Get the STA_RECORD_T of TA, the TA should equal to BSSID for AP
    prStaRec = staRecGetStaRecordByAddr(prAdapter, prWlanBeaconFrame->aucSrcAddr);

    if (prStaRec) {
        /* Update the record activity time. */
        GET_CURRENT_SYSTIME(&prStaRec->rUpdateTime);
    }

    ASSERT(prStaRec);

    //4 <8> Change detection of ShortSlotTime setting according to 7.3.1.4
    {
        BOOLEAN fgUseShortSlotTime;

        fgUseShortSlotTime = (prBSSDesc->u2CapInfo & CAP_INFO_SHORT_SLOT_TIME) ? TRUE: FALSE;
        if ((fgUseShortSlotTime && !prBssInfo->fgUseShortSlotTime) ||
            (!fgUseShortSlotTime && prBssInfo->fgUseShortSlotTime)) {

            prBssInfo->fgUseShortSlotTime = fgUseShortSlotTime;

            if (prConnSettings->fgIsShortSlotTimeOptionEnable) {

                /* Honor the ShortSlotTime settings from current BSS capability */
                nicSetSlotTime(prAdapter,
                               prBSSDesc->ePhyType,
                               fgUseShortSlotTime);
            }
#if DBG
            else if (fgUseShortSlotTime) {
                DBGLOG(JOIN, INFO,
                    ("Use ShortSlotTime in current BSS, but fgIsShortSlotTimeOptionEnable == FALSE\n"));
            }
#endif /* DBG */
        }
    }


    //4 <9> Change detection of ERP value
    if (prBSSDesc->fgIsERPPresent) {
        BOOLEAN fgIsPreambleModeChanged = FALSE;
        BOOLEAN fgIsProtectionChanged = FALSE;
        UINT_8 RTSRateIndex;


        //4 <9.1> Check  if the contain of ERP was changed.
        if (prBssInfo->fgIsERPPresent) {

            // Check if USER enable it. If not, ignore the ERP change.
            if (prBssInfo->fgIsShortPreambleAllowed) {

                if ((prBSSDesc->ucERP & ERP_INFO_BARKER_PREAMBLE_MODE) !=
                    (prBssInfo->ucERP & ERP_INFO_BARKER_PREAMBLE_MODE)) {

                    fgIsPreambleModeChanged = TRUE;

                    prBssInfo->fgUseShortPreamble =
                        (prBSSDesc->ucERP & ERP_INFO_BARKER_PREAMBLE_MODE) ? FALSE : TRUE;
                }
            }

            if ((prBssInfo->ucERP & ERP_INFO_USE_PROTECTION) !=
                (prBSSDesc->ucERP & ERP_INFO_USE_PROTECTION)) {

                fgIsProtectionChanged = TRUE;

            }

        }
        //4 <9.2> If we never get ERP before.
        else {
            /* NOTE(Kevin 2007/12/24): For the case of Zyxel AP.
             * 1. This AP may have no ERP Info. in its ProbeResp Frame.
             * 2. If we use the ProbeResp as BSS_DESC_T for JOIN, we may have
             *    prBssInfo->fgIsERPPresent == FALSE;
             * 3. Once receive the Beacon Frame from this AP, we can see the
             *    ERP Info.
             */

            BOOLEAN fgUseShortPreamble;


            DBGLOG(JOIN, INFO, ("prBssInfo->fgIsERPPresent == FALSE, Update ERP after JOIN\n"));

            /* Update RTS/CTS_to_self Protection Rate Index. */
            if (!rateGetHighestRateIndexFromRateSet(
                    prBssInfo->u2BSSBasicRateSet & RATE_SET_HR_DSSS,
                    &prBssInfo->ucRTSProtectionRateIndex)) {

                /* Set default setting for ERP */
                prBssInfo->ucRTSProtectionRateIndex = RATE_SET_BIT_11M;
            }

            if ((prBssInfo->fgIsShortPreambleAllowed) &&
                ((prConnSettings->ePreambleType == PREAMBLE_TYPE_SHORT) || /* Short Preamble Option Enable is TRUE */
                 ((prConnSettings->ePreambleType == PREAMBLE_TYPE_AUTO) &&
                  (prBSSDesc->u2CapInfo & CAP_INFO_SHORT_PREAMBLE)))) {

                fgUseShortPreamble =
                    (prBSSDesc->ucERP & ERP_INFO_BARKER_PREAMBLE_MODE) ? FALSE : TRUE;

                if (fgUseShortPreamble != prBssInfo->fgUseShortPreamble) {

                    fgIsPreambleModeChanged = TRUE;

                    prBssInfo->fgUseShortPreamble = fgUseShortPreamble;
                }
            }

            if (prBSSDesc->ucERP & ERP_INFO_USE_PROTECTION) {

                fgIsProtectionChanged = TRUE;

            }

            prBssInfo->fgIsERPPresent = TRUE;

        }


        if (fgIsProtectionChanged) {

            if (prBSSDesc->ucERP & ERP_INFO_USE_PROTECTION) {
                prBssInfo->fgIsProtection = TRUE;

                nicRateEnableProtection(prAdapter, CTS_PROTECTION_TYPE_802_11);

            }
            else {
                prBssInfo->fgIsProtection = FALSE;

                nicRateDisableProtection(prAdapter);

            }
        }

        RTSRateIndex = ((prBssInfo->fgIsProtection) ?
            prBssInfo->ucRTSProtectionRateIndex : prBssInfo->ucRTSRateIndex);

        if (fgIsProtectionChanged || fgIsPreambleModeChanged) {
            nicRateSetCTSRTSRate(prAdapter,
                                 RTSRateIndex,
                                 prBssInfo->fgUseShortPreamble);
        }

        if (fgIsPreambleModeChanged) {
            nicRateSetBasicRate(prAdapter,
                                prBssInfo->ucBasicRateIndex,
                                prBssInfo->fgUseShortPreamble);

            prStaRec->fgIsShortPreambleOptionEnable =
                prBssInfo->fgUseShortPreamble;

            if (nicSetHwBySta(prAdapter, prStaRec) == FALSE) {
                ASSERT(FALSE);
            }
        }

#if CFG_TX_FRAGMENT
        if (prConnSettings->fgIsEnableTxAutoFragmentForBT &&
            (fgIsProtectionChanged || fgIsPreambleModeChanged)) {
            txRateSetInitForBT(prAdapter, prStaRec);
        }
#endif /* CFG_TX_FRAGMENT */

        prBssInfo->ucERP = prBSSDesc->ucERP; // Always update ERP

    }


    //4 <10> Change detection of WMM attributes
    if (prBssInfo->fgIsWmmAssoc && prBSSDesc->prIeWmmParamElem) {
        UINT_8 ucWmmParamSetCount =
            (prBSSDesc->prIeWmmParamElem->ucQosInfo) & WMM_QOS_INFO_PARAM_SET_CNT;

        if (prBssInfo->rWmmInfo.ucWmmParamSetCount != ucWmmParamSetCount) {
            WMM_INFO_T rWmmInfo;

            DBGLOG(JOIN, INFO, ("ucWmmParamSetCount changed, previous = %d, current = %d\n",
                prBssInfo->rWmmInfo.ucWmmParamSetCount, ucWmmParamSetCount));

            if (qosParseWMMParamElem((PUINT_8)prBSSDesc->prIeWmmParamElem, &rWmmInfo)) {

                if (rWmmInfo.ucWmmFlag & WMM_FLAG_AC_PARAM_PRESENT) {
                    kalMemCopy(&prBssInfo->rWmmInfo,
                               &rWmmInfo,
                               sizeof(WMM_INFO_T));
                }
                else {
                    kalMemCopy(&prBssInfo->rWmmInfo,
                               &rWmmInfo,
                               OFFSET_OF(WMM_INFO_T, arWmmAcParams));
                               /* sizeof(WMM_INFO_T) - sizeof(rWmmInfo.arWmmAcParams) */
                }
            }
        }
    }

    return;
} /* end of bssProcessBeacon() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function is used to update TX Rate according to the setting from
*        current BSS.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
bssUpdateTxRateForControlFrame (
    IN P_ADAPTER_T prAdapter
    )
{
    P_BSS_INFO_T prBssInfo;
    UINT_8 ucRateIndex;

    DEBUGFUNC("bssUpdateTxRateForControlFrame");


    ASSERT(prAdapter);
    prBssInfo = &prAdapter->rBssInfo;

    //4 <1> Lowest Basic Rate
    if (rateGetLowestRateIndexFromRateSet(prBssInfo->u2BSSBasicRateSet, &ucRateIndex)) {

        prBssInfo->ucBasicRateIndex = ucRateIndex;
    }
    else {
        /* Error handling -
         * Can't locate lowest Rate Index From Rate Set, setup a default value according to
         * current PHY_TYPE.
         */
        if (prBssInfo->ePhyType == PHY_TYPE_OFDM_INDEX) {
            prBssInfo->ucBasicRateIndex = RATE_SET_BIT_6M;
        }
        else {
            prBssInfo->ucBasicRateIndex = RATE_SET_BIT_1M;
        }
    }

    DBGLOG(MGT, INFO, ("prBssInfo->ucBasicRateIndex = %s\n",
        apucDebugRateIndex[prBssInfo->ucBasicRateIndex]));

    nicRateSetBasicRate(prAdapter,
                        prBssInfo->ucBasicRateIndex,
                        prBssInfo->fgUseShortPreamble);


    //4 <2> Highest Basic Rate for RTS/CTS Rate
    // Find a proper rate index used for RTS threshold.
    if (rateGetHighestRateIndexFromRateSet(
            prBssInfo->u2BSSBasicRateSet,
            &ucRateIndex)) {
        prBssInfo->ucRTSRateIndex = ucRateIndex;
    }
    else {
        /* Error handling */
        if (prBssInfo->ePhyType == PHY_TYPE_OFDM_INDEX) {
            prBssInfo->ucRTSRateIndex = RATE_SET_BIT_6M;
        }
        else {
            prBssInfo->ucRTSRateIndex = RATE_SET_BIT_1M;
        }
    }


    //4 <3> Highest HR_DSSS Basic Rate for RTS/CTS Protection Rate
    // Find a proper rate index used for RTS/CTS or CTS_to_self protection.
    if (prBssInfo->fgIsERPPresent) { // Associated to an ERP AP.
        if (rateGetHighestRateIndexFromRateSet(
                prBssInfo->u2BSSBasicRateSet & RATE_SET_HR_DSSS,
                &ucRateIndex)) {

            prBssInfo->ucRTSProtectionRateIndex = ucRateIndex;
        }
        else {
            /* Set default setting for ERP */
            prBssInfo->ucRTSProtectionRateIndex = RATE_SET_BIT_11M;
        }

        if (prBssInfo->ucERP & ERP_INFO_USE_PROTECTION) {
            prBssInfo->fgIsProtection = TRUE;

            nicRateEnableProtection(prAdapter, CTS_PROTECTION_TYPE_802_11);

            nicRateSetCTSRTSRate(prAdapter,
                                 prBssInfo->ucRTSProtectionRateIndex,
                                 prBssInfo->fgUseShortPreamble);
        }
        else {
            prBssInfo->fgIsProtection = FALSE;

            nicRateDisableProtection(prAdapter);

            nicRateSetCTSRTSRate(prAdapter,
                                 prBssInfo->ucRTSRateIndex,
                                 prBssInfo->fgUseShortPreamble);
        }

    }
    else {
        prBssInfo->fgIsProtection = FALSE;

        nicRateDisableProtection(prAdapter);

        nicRateSetCTSRTSRate(prAdapter,
                             prBssInfo->ucRTSRateIndex,
                             prBssInfo->fgUseShortPreamble);

        prBssInfo->ucRTSProtectionRateIndex = prBssInfo->ucRTSRateIndex;
        /* Actually we won't use ucRTSProtectionRateIndex if fgIsERPPresent is FALSE.
         * We update it anyway in case wrongly use of it.
         */
    }

    DBGLOG(MGT, INFO, ("prBssInfo->fgIsProtection = %d\n", prBssInfo->fgIsProtection));

    DBGLOG(MGT, INFO, ("prBssInfo->ucRTSProtectionRateIndex = %s\n",
        apucDebugRateIndex[prBssInfo->ucRTSProtectionRateIndex]));
    DBGLOG(MGT, INFO, ("prBssInfo->ucRTSRateIndex = %s\n",
        apucDebugRateIndex[prBssInfo->ucRTSRateIndex]));


    //4 <4> ACK Rate (CTS Rate for RTS)
    {
        UINT_8 aucAckCtsRateIndex[RATE_NUM];

        rateSetAckCtsDataRatesFromRateSet(prBssInfo->u2OperationalRateSet,
                                          prBssInfo->u2BSSBasicRateSet,
                                          aucAckCtsRateIndex);

#if DBG
        {
            UINT_32 i;

            for (i = 0; i < RATE_NUM; i++) {
                DBGLOG(MGT, INFO, ("%s's ACK rate = %s\n", apucDebugRateIndex[i],
                    apucDebugRateIndex[aucAckCtsRateIndex[i]]));
            }
        }
#endif /* DBG */

        nicRateSetAckCtsRate(prAdapter,
                             aucAckCtsRateIndex,
                             prBssInfo->fgUseShortPreamble);
    }

    return;

} /* end of bssUpdateTxRateForControlFrame() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function is used to handle BSS Descriptors and STA Records when we
*        leave current BSS.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
bssLeave (
    IN P_ADAPTER_T prAdapter
    )
{
    P_BSS_INFO_T prBssInfo;


    ASSERT(prAdapter);
    prBssInfo = &prAdapter->rBssInfo;

    //4 <1> Remove connection flag of current BSS' BSS_DESC
    /* Let this scan record can be flushed if it was inactive for a period.
     */
    scanRemoveConnectionFlagOfBssDescByBssid(prAdapter, prBssInfo->aucBSSID);
#if 0
    //4 <1> Flush all BSS_DESC_T including current BSS's BSS_DESC_T
    scanRemoveBssDescsByPolicy(prAdapter, SCAN_RM_POLICY_ENTIRE);
#endif

    //4 <2> Remove STATE_3 flag of all the associated STA_RECORD_Ts (AP, DLSs)
    staRecRemoveStateFlagOfAllStaRecords(prAdapter);

    return;
} /* end of bssLeave() */


