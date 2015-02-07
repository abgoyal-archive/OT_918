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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/qos_enhance.c#1 $
*/

/*! \file   "qos_enhance.h"
    \brief  This file includes the QoS related enhancement functions

    The file contains the function for used in QoS enabled BSS or IBSS to parse
    and check the WMM Parameter IEs.
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
** $Log: qos_enhance.c $
 *
 * 07 10 2010 renbang.jiang
 * [ALPS00121785][Need Patch] [Volunteer Patch] use NVRAM to save Wi-Fi custom data 
 * .
 *
 * 06 28 2010 renbang.jiang
 * [ALPS00224814][Wi-Fi][FT]Can't lanuch the CMCC AU website, but the reference phone is OK. 
 * disable WMMPS in default.
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\14 2008-12-01 20:49:43 GMT mtk01461
**  \main\maintrunk.MT5921\13 2008-12-01 18:42:53 GMT mtk01088
**  fixed the "possible use of null pointer" by lint check
**  \main\maintrunk.MT5921\12 2008-11-28 17:34:49 GMT mtk01088
**  fixed the lint warning
**  \main\maintrunk.MT5921\11 2008-08-20 00:16:29 GMT mtk01461
**  Update for Driver Review
**  \main\maintrunk.MT5921\10 2008-08-19 09:23:17 GMT mtk01084
**  modify for coding rule conformance
**  \main\maintrunk.MT5921\9 2008-04-01 23:53:04 GMT mtk01461
**  Add comments and fix typo
**  \main\maintrunk.MT5921\8 2008-03-14 19:04:44 GMT mtk01084
**  modify function name
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

extern WIFI_CFG_DATA gPlatformCfg;

/*******************************************************************************
*                              C O N S T A N T S
********************************************************************************
*/
/* WMM Test Plan 1.4 Appendix F */
const WMM_AC_PARAM_T arDefaultWmmParamFor11agSTA[AC_NUM] = {
    {AC_BE, ACM_FLAG_ADM_NOT_REQUIRED, 3, 4, 10, 0},
    {AC_BK, ACM_FLAG_ADM_NOT_REQUIRED, 7, 4, 10, 0},
    {AC_VI, ACM_FLAG_ADM_NOT_REQUIRED, 2, 3, 4,  94},
    {AC_VO, ACM_FLAG_ADM_NOT_REQUIRED, 2, 2, 3,  47}};

const WMM_AC_PARAM_T arDefaultWmmParamFor11bSTA[AC_NUM] = {
    {AC_BE, ACM_FLAG_ADM_NOT_REQUIRED, 3, 4, 10, 0},
    {AC_BK, ACM_FLAG_ADM_NOT_REQUIRED, 7, 4, 10, 0},
    {AC_VI, ACM_FLAG_ADM_NOT_REQUIRED, 2, 3, 4,  188},
    {AC_VO, ACM_FLAG_ADM_NOT_REQUIRED, 2, 2, 3,  102}};

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
* \brief Initialize the WMM INFO structure with default WMM Parameter according
*        to PHY type.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
* \param[in] fgIs802_11b    Update parameters for 802.11b.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
qosWmmInfoInit (
    IN P_WMM_INFO_T prWmmInfo,
    IN BOOLEAN fgIs802_11b
    )
{

    ASSERT(prWmmInfo);

    kalMemZero(prWmmInfo, sizeof(WMM_INFO_T) - sizeof(prWmmInfo->arWmmAcParams));

    if (fgIs802_11b) {
        kalMemCopy((PVOID)prWmmInfo->arWmmAcParams,
                   (PVOID)arDefaultWmmParamFor11bSTA,
                   sizeof(arDefaultWmmParamFor11bSTA));
    }
    else {
        kalMemCopy((PVOID)prWmmInfo->arWmmAcParams,
                   (PVOID)arDefaultWmmParamFor11agSTA,
                   sizeof(arDefaultWmmParamFor11agSTA));
    }

    return;
} /* end of qosWmmInfoInit() */


/*----------------------------------------------------------------------------*/
/*!
* \brief Check QoS capability according to the WMM Information Element.
*
* \param[in] pucBuf         Pointer to the buffer of WMM Information Element.
* \param[out] pucWmmFlag    Pointer to the variable of Internal WMM Flags.
*
* \retval TRUE  Parse IE ok
* \retval FALSE Parse IE fail
*/
/*----------------------------------------------------------------------------*/
BOOLEAN
qosCheckQoSCapabilityByWMMInfoElem (
    IN PUINT_8 pucBuf,
    OUT PUINT_8 pucWmmFlag
    )
{
    P_IE_WMM_INFO_ELEM_T prIeWmmInfoElem ;

    DEBUGFUNC("qosCheckQoSCapbilityByWMMInfoElem");


    ASSERT(pucBuf);
    ASSERT(pucWmmFlag);
    prIeWmmInfoElem = (P_IE_WMM_INFO_ELEM_T)pucBuf;

    /* Verify the length of the WMM Information Element. */
    if (prIeWmmInfoElem->ucLength != ELEM_MAX_LEN_WMM_INFO) {
        DBGLOG(MGT, LOUD, ("Invalid WMM Information Element length %d\n",
            prIeWmmInfoElem->ucLength));
        return FALSE;
    }

    *pucWmmFlag = WMM_FLAG_SUPPORT_WMM;

    if(gPlatformCfg.rWifiCustom.ucWmmPsEnable){
        if (prIeWmmInfoElem->ucQosInfo & WMM_QOS_INFO_UAPSD) {
            *pucWmmFlag |= WMM_FLAG_SUPPORT_UAPSD;
        }
	}

    return TRUE;

} /* end of qosCheckQoSCapabilityByWMMInfoElem() */


/*----------------------------------------------------------------------------*/
/*!
* \brief Check QoS capability according to the WMM Parameter Element. This is used
*        by SCAN for parsing Beacons, we don't have to deal with the AC Parameters
*        in this phase.
*
* \param[in] pucBuf         Pointer to the buffer of WMM Parameter Element.
* \param[out] pucWmmFlag    Pointer to the variable of Internal WMM Flags.
*
* \retval TRUE  Parse IE ok
* \retval FALSE Parse IE fail
*/
/*----------------------------------------------------------------------------*/
BOOLEAN
qosCheckQoSCapabilityByWMMParamElem (
    IN PUINT_8 pucBuf,
    OUT PUINT_8 pucWmmFlag
    )
{
    P_IE_WMM_PARAM_ELEM_T prIeWmmParamElem;

    DEBUGFUNC("qosCheckQoSCapbilityByWMMParamElem");


    ASSERT(pucBuf);
    ASSERT(pucWmmFlag);
    prIeWmmParamElem = (P_IE_WMM_PARAM_ELEM_T)pucBuf;

    /* Verify the length of the WME Parameter element. */
    if (prIeWmmParamElem->ucLength != ELEM_MAX_LEN_WMM_PARAM) {
        DBGLOG(MGT, LOUD, ("Invalid WMM Parameter Element length %d\n",
            prIeWmmParamElem->ucLength));
        return FALSE;
    }

    *pucWmmFlag = WMM_FLAG_SUPPORT_WMM;
	
    if(gPlatformCfg.rWifiCustom.ucWmmPsEnable){
        if (prIeWmmParamElem->ucQosInfo & WMM_QOS_INFO_UAPSD) {
            *pucWmmFlag |= WMM_FLAG_SUPPORT_UAPSD;
        }
    }
    return TRUE;

} /* end of qosCheckQoSCapabilityByWMMParamElem() */


/*----------------------------------------------------------------------------*/
/*!
* \brief Parse WMM Parameter Element and save to WMM Information structure.
*
* \param[in] pucBuf         Pointer to the buffer of WMM Parameter Element.
* \param[out] pucWmmFlag    Pointer to the variable of WMM Information structure.
*
* \retval TRUE  Parse IE ok
* \retval FALSE Parse IE fail
*/
/*----------------------------------------------------------------------------*/
BOOLEAN
qosParseWMMParamElem (
    IN PUINT_8 pucBuf,
    IN OUT P_WMM_INFO_T prWmmInfo
    )
{
    P_IE_WMM_PARAM_ELEM_T prIeWmmParamElem;
    P_WMM_AC_PARAM_RECORD_T prParamRecord;
    P_WMM_AC_PARAM_T prAcParam;
    UINT_32 i;

    DEBUGFUNC("qosParseWMMParamElem");


    ASSERT(pucBuf);
    ASSERT(prWmmInfo);
    prIeWmmParamElem = (P_IE_WMM_PARAM_ELEM_T)pucBuf;

    /* Verify the length of the WMM Parameter element. */
    if (prIeWmmParamElem->ucLength != ELEM_MAX_LEN_WMM_PARAM) {
        DBGLOG(MGT, LOUD, ("Invalid WMM Parameter length %d\n",
            prIeWmmParamElem->ucLength));
        return FALSE;
    }

    /* Check AC Parameters Records. */
    if ((prIeWmmParamElem->ucAcParamBEAciAifsn & WMM_ACIAIFSN_ACI) != WMM_ACI_AC_BE) {
        DBGLOG(MGT, LOUD, ("Invalid AC Parameters BE\n"));
        return FALSE;
    }

    if ((prIeWmmParamElem->ucAcParamBKAciAifsn & WMM_ACIAIFSN_ACI) != WMM_ACI_AC_BK) {
        DBGLOG(MGT, LOUD, ("Invalid AC Parameters BK\n"));
        return FALSE;
    }

    if ((prIeWmmParamElem->ucAcParamVIAciAifsn & WMM_ACIAIFSN_ACI) != WMM_ACI_AC_VI) {
        DBGLOG(MGT, LOUD, ("Invalid AC Parameters VI\n"));
        return FALSE;
    }

    if ((prIeWmmParamElem->ucAcParamVOAciAifsn & WMM_ACIAIFSN_ACI) != WMM_ACI_AC_VO) {
        DBGLOG(MGT, LOUD, ("Invalid AC Parameters VO\n"));
        return FALSE;
    }

    /* Update the WMM parameters. */
    prWmmInfo->ucWmmFlag = WMM_FLAG_SUPPORT_WMM;


    prWmmInfo->ucWmmParamSetCount =
        prIeWmmParamElem->ucQosInfo & WMM_QOS_INFO_PARAM_SET_CNT;

    DBGLOG(MGT, TRACE, ("WMM Parameter: Parameter Set Count = 0x%02x.\n",
        prWmmInfo->ucWmmParamSetCount));


    /* Update the AC parameters for AC_BE, AC_BK, AC_VI, and AC_VO. */
    for (i = AC_BE; i < AC_NUM; i++) {
        switch (i) {
        case AC_BE:
            prParamRecord =
                (P_WMM_AC_PARAM_RECORD_T)&prIeWmmParamElem->ucAcParamBEAciAifsn;
            break;

        case AC_BK:
            prParamRecord =
                (P_WMM_AC_PARAM_RECORD_T)&prIeWmmParamElem->ucAcParamBKAciAifsn;
            break;

        case AC_VI:
            prParamRecord =
                (P_WMM_AC_PARAM_RECORD_T)&prIeWmmParamElem->ucAcParamVIAciAifsn;
            break;

        case AC_VO:
            prParamRecord =
                (P_WMM_AC_PARAM_RECORD_T)&prIeWmmParamElem->ucAcParamVOAciAifsn;
            break;

        default:
            /* Won't reach here */
            return FALSE;
        }

        prAcParam = &prWmmInfo->arWmmAcParams[i];

        prAcParam->ucAci = (prParamRecord->ucAciAifsn & WMM_ACIAIFSN_ACI) >> WMM_ACIAIFSN_ACI_OFFSET;
        if (prParamRecord->ucAciAifsn & WMM_ACIAIFSN_ACM) {
            prAcParam->ucAcmFlag = ACM_FLAG_ADM_REQUIRED;
        }
        else {
            prAcParam->ucAcmFlag = ACM_FLAG_ADM_NOT_REQUIRED;
        }
        prAcParam->ucAifsn = prParamRecord->ucAciAifsn & WMM_ACIAIFSN_AIFSN;

        prAcParam->ucECWmin = prParamRecord->ucECWminECWmax &
            WMM_ECWMINECWMAX_ECWMIN;
        prAcParam->ucECWmax = (prParamRecord->ucECWminECWmax &
            WMM_ECWMINECWMAX_ECWMAX) >> WMM_ECWMINECWMAX_ECWMAX_OFFSET;

        WLAN_GET_FIELD_16(&prParamRecord->u2TxopLimit, &prAcParam->u2TxopLimit);

        DBGLOG(MGT, TRACE,
            ("WMM Parameter: ACI=%d, ACM=%d, AIFSN=%d, CWmin=%d, CWmax=%d, TXOPLimit=%d .\n",
                prAcParam->ucAci,
                prAcParam->ucAcmFlag,
                prAcParam->ucAifsn,
                ECW_TO_CW(prAcParam->ucECWmin),
                ECW_TO_CW(prAcParam->ucECWmax),
                prAcParam->u2TxopLimit));
    }

    prWmmInfo->ucWmmFlag |= WMM_FLAG_AC_PARAM_PRESENT;

    if(gPlatformCfg.rWifiCustom.ucWmmPsEnable){
        if (prIeWmmParamElem->ucQosInfo & WMM_QOS_INFO_UAPSD) {
            prWmmInfo->ucWmmFlag |= WMM_FLAG_SUPPORT_UAPSD;
        }
    }

    DBGLOG(MGT, TRACE, ("WMM Flags: %02x.\n", prWmmInfo->ucWmmFlag));


    return TRUE;

} /* end of qosParseWMMParamElem() */


/*----------------------------------------------------------------------------*/
/*!
* \brief Construct WMM Information Element for used in Assocation Request frame.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
* \param[in] ucWmmFlag      Internal WMM Flags from target BSS Descriptor.
* \param[out] pucBuffer     Pointer to the buffer of WMM Information Element.
*
* \retval IE length of WMM Information Element
*/
/*----------------------------------------------------------------------------*/
UINT_8
qosConstructWMMInfoElem (
    IN P_ADAPTER_T prAdapter,
    IN UINT_8 ucWmmFlag,
    IN OUT PUINT_8 pucBuffer
    )
{
    P_IE_WMM_INFO_ELEM_T prIeWmmInfo;
    P_PM_PROFILE_SETUP_INFO_T prPmProfSetupInfo;

    UINT_32 ucUapsd[] = {
        WMM_QOS_INFO_BE_UAPSD,
        WMM_QOS_INFO_BK_UAPSD,
        WMM_QOS_INFO_VI_UAPSD,
        WMM_QOS_INFO_VO_UAPSD
    };
    UINT_8 aucWfaOui[] = VENDOR_OUI_WFA;


    ASSERT(prAdapter);
    ASSERT(pucBuffer);
    prIeWmmInfo = (P_IE_WMM_INFO_ELEM_T)pucBuffer;
    prPmProfSetupInfo = &prAdapter->rPmInfo.rPmProfSetupInfo;

    prIeWmmInfo->ucId = ELEM_ID_WMM;
    prIeWmmInfo->ucLength = ELEM_MAX_LEN_WMM_INFO;

    /* WMM-2.2.1 WMM Information Element Field Values */
    prIeWmmInfo->aucOui[0] = aucWfaOui[0];
    prIeWmmInfo->aucOui[1] = aucWfaOui[1];
    prIeWmmInfo->aucOui[2] = aucWfaOui[2];
    prIeWmmInfo->ucOuiType = VENDOR_OUI_TYPE_WMM;
    prIeWmmInfo->ucOuiSubtype = VENDOR_OUI_SUBTYPE_WMM_INFO;

    prIeWmmInfo->ucVersion = VERSION_WMM;
    prIeWmmInfo->ucQosInfo = 0;

    if (ucWmmFlag & WMM_FLAG_SUPPORT_UAPSD) {
        UINT_8 ucQosInfo = 0;
        ENUM_AC_T eQueNum;

        /* Static U-APSD setting */
        for (eQueNum = AC_BE; eQueNum <= AC_VO; eQueNum++) {
            if (PM_IS_AC_QUEUE_DELIVERY_AND_TRIGGER_ENABLED(prAdapter, eQueNum)) {
                ucQosInfo |= (UINT_8)ucUapsd[eQueNum];
            }
        }

        switch (prPmProfSetupInfo->ucUapsdSp) {
        case WMM_MAX_SP_LENGTH_ALL:
            ucQosInfo |= WMM_QOS_INFO_MAX_SP_ALL;
            break;
        case WMM_MAX_SP_LENGTH_2:
            ucQosInfo |= WMM_QOS_INFO_MAX_SP_2;
            break;
        case WMM_MAX_SP_LENGTH_4:
            ucQosInfo |= WMM_QOS_INFO_MAX_SP_4;
            break;
        case WMM_MAX_SP_LENGTH_6:
            ucQosInfo |= WMM_QOS_INFO_MAX_SP_6;
            break;
        default:
            WARNLOG(("U-APSD should not have this Service Period: %d\n",
                        prPmProfSetupInfo->ucUapsdSp));
        }
        WMM_INFO_IE(prIeWmmInfo)->ucQosInfo = ucQosInfo;
    }

    return (ELEM_HDR_LEN + ELEM_MAX_LEN_WMM_INFO);

} /* end of qosConstructWMMInfoElem() */


/*----------------------------------------------------------------------------*/
/*!
* \brief Update GRANTED Admission Control from given WMM Information structure, and
*        then also update NIC Layer to change settings of TX Queues.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
* \param[in] pucWmmFlag     Pointer to the variable of WMM Information structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
qosUpdateWMMParametersAndAssignAllowedACI (
    IN P_ADAPTER_T prAdapter,
    IN P_WMM_INFO_T prWmmInfo
    )
{
    const UINT_8 aucACI2ACPriority[] = {
                AC_BE_PRIORITY, /* Index by ACI */
                AC_BK_PRIORITY,
                AC_VI_PRIORITY,
                AC_VO_PRIORITY
                };

    const UINT_8 aucACPriority2ACI[] = {
                AC_BK, /* Index by AC Priority */
                AC_BE,
                AC_VI,
                AC_VO
                };

    UINT_8 aucACI2AdmittedACI[] = {
                AC_BE, /* Index by ACI */
                AC_BK,
                AC_VI,
                AC_VO
                };
    UINT_32 u4ACI;
    INT_32 j;

    DEBUGFUNC("qosUpdateWMMParametersAndAssignAllowedACI");


    ASSERT(prAdapter);
    ASSERT(prWmmInfo);

    //4 <1> Update GRANTED Admission Control ACI mapping table
    /* Loop by ACI */
    for (u4ACI = AC_BE; u4ACI < AC_NUM; u4ACI++) {
        if ((prWmmInfo->arWmmAcParams[u4ACI].ucAcmFlag & (ACM_FLAG_ADM_GRANTED | ACM_FLAG_ADM_REQUIRED))
            == ACM_FLAG_ADM_REQUIRED) {
            BOOLEAN fgIsFindAllowedAC = FALSE;


            /* Loop by lower priority */
            for (j = (aucACI2ACPriority[u4ACI] - 1); (j >= AC_BK_PRIORITY && j <= AC_VO_PRIORITY); j--) {
                UINT_8 ucAcmFlag = prWmmInfo->arWmmAcParams[aucACPriority2ACI[j]].ucAcmFlag;

                if ((ucAcmFlag == ACM_FLAG_ADM_NOT_REQUIRED) ||
                    ((ucAcmFlag & (ACM_FLAG_ADM_GRANTED | ACM_FLAG_ADM_REQUIRED)) ==
                        (ACM_FLAG_ADM_GRANTED | ACM_FLAG_ADM_REQUIRED))) {

                    fgIsFindAllowedAC = TRUE;
                    break;
                }
            }

            if (!fgIsFindAllowedAC) {
                /* TODO(Kevin): should we use the BK for this not granted AC ?
                 * ucACI2AdmittedACI[i] = ucACPriority2ACI[AC_BK_PRIORITY];
                 */
                DBGLOG(MGT, WARN,
                    ("Can not find allowed AC for not granted AC - %ld\n", u4ACI));
            }
            else if (j >= AC_BK_PRIORITY) {
                aucACI2AdmittedACI[u4ACI] = aucACPriority2ACI[j];
                //printk("t1 %d\n", aucACI2AdmittedACI[u4ACI]);
            }
        }
    }

    nicTxQoSAssignAdmittedTXQ(prAdapter,
                              aucACI2AdmittedACI);

    nicTxQoSUpdateTXQParameters(prAdapter,
                                prWmmInfo->arWmmAcParams);

    return;
} /* end of qosUpdateWMMParametersAndAssignAllowedACI() */



