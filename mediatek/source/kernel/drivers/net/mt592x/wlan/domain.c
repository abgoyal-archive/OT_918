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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/domain.c#1 $
*/

/*! \file domain.c
    \brief This file contains the regulatory domain related routines of Windows driver
           for MediaTek Inc. 802.11 Wireless LAN Adapters.
*/

/*******************************************************************************
** Copyright (c) 2005-2007 MediaTek Inc.
**
** All rights reserved. Copying, compilation, modification, distribution
** or any other use whatsoever of this material is strictly prohibited
** except in accordance with a Software License Agreement with
** MediaTek Inc.
********************************************************************************
*/
/*
** $Log: domain.c $
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\10 2008-10-27 15:01:55 GMT mtk01084
**  fix LINT warning
**  \main\maintrunk.MT5921\9 2008-08-21 16:42:30 GMT mtk01461
**  Update for Driver Review
**  \main\maintrunk.MT5921\8 2008-08-11 21:25:36 GMT mtk01084
**  modify for coding rules conformance
**  \main\maintrunk.MT5921\7 2008-08-03 17:18:52 GMT mtk01084
**  remove compiler warning on Linux compiler
**  \main\maintrunk.MT5921\6 2008-07-30 22:32:33 GMT mtk01084
**  modify the mechanism on determining obscured regulation domain
**  \main\maintrunk.MT5921\5 2008-07-14 13:38:07 GMT mtk01084
**  fix compiling warning on Linux
**  \main\maintrunk.MT5921\4 2008-07-10 20:48:30 GMT mtk01084
**  fix compiler error
**  \main\maintrunk.MT5921\3 2008-07-10 16:37:44 GMT mtk01084
**  support 802.11d related functions
**  \main\maintrunk.MT5921\2 2008-07-08 11:28:06 GMT mtk01084
**  Initial version
**
*/

/*******************************************************************************
*                E X T E R N A L   R E F E R E N C E S
********************************************************************************
*/
#include "precomp.h"

/*******************************************************************************
*                          C O N S T A N T S
********************************************************************************
*/

/*******************************************************************************
*                         D A T A   T Y P E S
********************************************************************************
*/
#if CFG_SUPPORT_802_11D
/*! \brief used for selecting domain */
typedef struct _VALID_DOMAIN_T {
    UINT_16 countryCode;    /*!< 2-byte country code */
    UINT_8  count;  /*!< number of scan results announce this country code */
    UINT_8  index;  /*!< the index of first scan result carry this country code */
} VALID_DOMAIN_T, P_VALID_DOMAIN_T;
#endif

/*******************************************************************************
*                        P U B L I C   D A T A
********************************************************************************
*/

/*******************************************************************************
*                       P R I V A T E   D A T A
********************************************************************************
*/

/*******************************************************************************
*                             M A C R O S
********************************************************************************
*/

/*******************************************************************************
*              F U N C T I O N   D E C L A R A T I O N S
********************************************************************************
*/

/*******************************************************************************
*                          F U N C T I O N S
********************************************************************************
*/
#if CFG_SUPPORT_802_11D
/*----------------------------------------------------------------------------*/
/*!
* \brief Parse the given country information element buffer and store regulatory
*        information to the output buffer.
*
* Parse Country IE and store results to the given DOMAIN_INFO_ENTRY buffer. Only
* format is checked.
*
* \param[in] pCountryIE Pointer to the country information element
* \param[out] pDomainInfo Pointer to the DOMAIN_INFO_ENTRY structure to store the
*   regulatory information acquired from pCountryIE
*
* \retval TRUE Succeeded
* \retval FALSE If any format error is found in the country info elem. The
*               pDomainInfo buffer is left unchanged.
*/
/*----------------------------------------------------------------------------*/
BOOLEAN
domainParseCountryInfoElem (
    IN P_IE_COUNTRY_T pCountryIE,
    OUT P_DOMAIN_INFO_ENTRY pDomainInfo
    )
{
    UINT_32 i/*, j*/;
    UINT_32 u4TripletCount;
    PUINT_8 pucTriplet;
    P_DOMAIN_SUBBAND_INFO pSubbandInfo;
    P_COUNTRY_INFO_TRIPLET_T pCountryInfoTriplet;
    P_COUNTRY_INFO_SUBBAND_TRIPLET_T pSubbandTriplet;
    DOMAIN_INFO_ENTRY localDomainInfo;

    DEBUGFUNC("domainParseCountryInfoElem");

    ASSERT(pDomainInfo);
    ASSERT(pCountryIE);

    /* Verify the length of the Country Information element. */
    if (pCountryIE->ucLength < ELEM_MIN_LEN_COUNTRY_INFO) {
        DBGLOG(MGT, LOUD,
               ("Invalid Country Information length %d\n",
               pCountryIE->ucLength));
        return FALSE;
    }

    kalMemZero(&localDomainInfo, sizeof(DOMAIN_INFO_ENTRY));
    localDomainInfo.u2CountryCode =
        ((UINT_16)pCountryIE->aucCountryStr[0] << 8) |
        (UINT_16)pCountryIE->aucCountryStr[1];

    pucTriplet = (PUINT_8)&pCountryIE->arSubbandTriplet[0];
//    j = 0;
    /* Minus 1 for 3-octet country string */
    u4TripletCount = (UINT_32)(pCountryIE->ucLength /
        ELEM_ID_COUNTRY_INFO_SUBBAND_TRIPLET_LEN_FIXED) - 1;
    DBGLOG(MGT, LOUD, ("u4TripletCount %ld\n", u4TripletCount));

    /* Note: Only process for 1 subband for supporting 2.4GHz only */
    u4TripletCount = 1;
    pSubbandInfo = &localDomainInfo.rBand24;

    for (i = 0; i < u4TripletCount; i++) {
        pCountryInfoTriplet = (P_COUNTRY_INFO_TRIPLET_T)pucTriplet;
        if (pCountryInfoTriplet->ucParam1 >= 201) {
            /* This is a Regulatory Triplet. TODO. */
        }
        else {
            pSubbandTriplet = (P_COUNTRY_INFO_SUBBAND_TRIPLET_T)pucTriplet;

            pSubbandInfo->ucFirstChannelNum = pSubbandTriplet->ucFirstChnlNum;
            pSubbandInfo->ucNumChannels     = pSubbandTriplet->ucNumOfChnl;
            pSubbandInfo->cMaxTxPowerLevel  = pSubbandTriplet->cMaxTxPwrLv;
        }

        /* For compiler packing issue, iterate on PUINT_8 pucTriplet rather than
        ** struct *P_COUNTRY_INFO_TRIPLET_T.
        */
        pucTriplet += ELEM_ID_COUNTRY_INFO_TRIPLET_LEN_FIXED;
    }

    kalMemCopy(pDomainInfo, &localDomainInfo, sizeof(DOMAIN_INFO_ENTRY));
    return TRUE;
} /* domainParseCountryInfoElem */

/*----------------------------------------------------------------------------*/
/*!
* \brief Construct a Country Information element and fill it to the given buffer
*
* \param[in] prAdapter Pointer to the Adapter structure
* \param[out] pucInfoElem Pointer to the buffer for the Country Information
*                        element
* \param[out] pucInfoElemLen Pointer to the length of the Country Information
*                           element
* \return (none)
*
*/
/*----------------------------------------------------------------------------*/
VOID
domainConstructCountryInfoElem (
    IN P_ADAPTER_T prAdapter,
    OUT PUINT_8 pucInfoElem,
    OUT PUINT_8 pucInfoElemLen
    )
{
    P_BSS_INFO_T prBssInfo;
    UINT_8 ucLen;
    P_DOMAIN_SUBBAND_INFO pSubbandInfo;
//    P_COUNTRY_INFO_SUBBAND_TRIPLET_T pSubbandTriplet;
//    UINT_32 i;

    DEBUGFUNC("domainConstructCountryInfoElem");

    ASSERT(prAdapter);
    ASSERT(pucInfoElem);
    ASSERT(pucInfoElemLen);

    prBssInfo = &prAdapter->rBssInfo;

    COUNTRY_IE(pucInfoElem)->ucId = ELEM_ID_COUNTRY_INFO;

    /* Fill the Country String field. */
    COUNTRY_IE(pucInfoElem)->aucCountryStr[0] =
        (UINT_8)(prBssInfo->rDomainInfo.u2CountryCode >> 8);
    COUNTRY_IE(pucInfoElem)->aucCountryStr[1] =
        (UINT_8)(prBssInfo->rDomainInfo.u2CountryCode & 0x00FF);
    COUNTRY_IE(pucInfoElem)->aucCountryStr[2] = ' ';
    ucLen = 3;

    /* Fill the First Channel Number, Number of Channels, and Maximum Transmit
       Power Level fields for each subband. */
#if 0
    for (i = 0; i < 2; ++i) {
        pSubbandInfo = &prBssInfo->rDomainInfo.rBand24[i];

        if (pSubbandInfo->ucFirstChannelNum && pSubbandInfo->ucNumChannels) {
            COUNTRY_IE(pucInfoElem)->arSubbandTriplet[i].ucFirstChnlNumber =
                pSubbandInfo->ucFirstChannelNum;
            COUNTRY_IE(pucInfoElem)->arSubbandTriplet[i].ucNumOfChnls =
                pSubbandInfo->ucNumChannels;
                // NOTE: type not match (sign -> un-sign)
            COUNTRY_IE(pucInfoElem)->arSubbandTriplet[i].ucMaxTxPowerLevel =
                pSubbandInfo->cMaxTxPowerLevel;

            ucLen += ELEM_ID_COUNTRY_INFO_SUBBAND_TRIPLET_LEN_FIXED;
        }
    }
#else
        pSubbandInfo = &prBssInfo->rDomainInfo.rBand24;

        if (pSubbandInfo->ucFirstChannelNum && pSubbandInfo->ucNumChannels) {
            COUNTRY_IE(pucInfoElem)->arSubbandTriplet[0].ucFirstChnlNum =
                pSubbandInfo->ucFirstChannelNum;
            COUNTRY_IE(pucInfoElem)->arSubbandTriplet[0].ucNumOfChnl =
                pSubbandInfo->ucNumChannels;
            // NOTE: type not match (sign -> un-sign)
            COUNTRY_IE(pucInfoElem)->arSubbandTriplet[0].cMaxTxPwrLv =
                pSubbandInfo->cMaxTxPowerLevel;

            ucLen += ELEM_ID_COUNTRY_INFO_SUBBAND_TRIPLET_LEN_FIXED;
        }
#endif

    /* Fill the pad, if needed. P_IE_COUNTRY_T */
    if (ucLen & 1) {
#if 1   /* Fix klocwork array boundary checking issue */
        pucInfoElem[OFFSET_OF(IE_COUNTRY_T, aucCountryStr) + ucLen] = 0;
#else
        *(PUINT_8)(&COUNTRY_IE(pucInfoElem)->aucCountryStr[0] + ucLen) = 0;
#endif
        ucLen += 1;
    }

    /* Fill the Length field. */
    COUNTRY_IE(pucInfoElem)->ucLength = ucLen;

    *pucInfoElemLen = ucLen + 2;
} /* domainConstructCountryInfoElem */

/*----------------------------------------------------------------------------*/
/*!
* \brief Try to resolve the domain information from the scan result, by comparing
*        the "country" IE in the beacon/ probe responses.
*
* \param[in] prAdapter    Pointer of Adapter Data Structure
* \param[out] pDomainInfo Pointer to the DOMAIN_INFO_ENTRY structure to store the
*                         regulatory information acquired from pCountryIE
*
* \retval TRUE There is valid domain information from the scan result
* \retval FALSE There is no valid domain information from the scan result.
*/
/*----------------------------------------------------------------------------*/
BOOLEAN
domainGetDomainInfoByScanResult (
    IN P_ADAPTER_T prAdapter,
    OUT P_DOMAIN_INFO_ENTRY pDomainInfo
    )
{
    DOMAIN_INFO_ENTRY   rDomainInfo;
    P_BSS_DESC_T prBssDesc = NULL;
    P_SCAN_INFO_T prScanInfo;
    P_LINK_T prBSSDescList;
    BOOLEAN fgIsDomainValid = FALSE;
    BOOLEAN fgIsChannelValid = FALSE;
    UINT_32 i;

    ASSERT(prAdapter);
    ASSERT(pDomainInfo);

    prScanInfo =  &prAdapter->rScanInfo;
    prBSSDescList = &prScanInfo->rBSSDescList;

    LINK_FOR_EACH_ENTRY(prBssDesc, prBSSDescList, rLinkEntry, BSS_DESC_T) {

        BSS_DESC_CHK_GUID(prBssDesc);

        DBGLOG(SCAN, TRACE, ("BSS DESC(%#lx): MAC: "MACSTR"\n",
            (UINT_32)prBssDesc, MAC2STR(prBssDesc->aucBSSID)));

        if (prBssDesc->prIECountry) {
            if (domainParseCountryInfoElem(prBssDesc->prIECountry, &rDomainInfo)) {
                if (fgIsDomainValid) {
                    if (pDomainInfo->u2CountryCode != rDomainInfo.u2CountryCode) {
                        fgIsDomainValid = FALSE;
                        break;
                    }
                }
                kalMemCopy(pDomainInfo, &rDomainInfo, sizeof(rDomainInfo));
                fgIsDomainValid = TRUE;
            }
        }
    }

    /* It also validates if the channel of the scanned BSSs is valid for the resolved domain */
    if (fgIsDomainValid) {
        LINK_FOR_EACH_ENTRY(prBssDesc, prBSSDescList, rLinkEntry, BSS_DESC_T) {

            BSS_DESC_CHK_GUID(prBssDesc);

            fgIsChannelValid = FALSE;

            for (i = 0; i < prAdapter->u2NicOpChnlNum; i++) {
                if ((prBssDesc->eBand == prAdapter->arNicOpChnList[i].eBand) &&
                    (prBssDesc->ucChannelNum == prAdapter->arNicOpChnList[i].ucChannelNum)) {

                    fgIsChannelValid = TRUE;
                    break;
                }
            }

            if (!fgIsChannelValid) {
                break;
            }
        }
    }

    return fgIsDomainValid & fgIsChannelValid;
}
#endif


