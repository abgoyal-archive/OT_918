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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/qos_enhance.h#1 $
*/

/*! \file   "qos_enhance.h"
    \brief  In this file we define the function prototype used for WMM or 802.11e

    The file contains the function declarations and defines for used in QoS
    enabled BSS or IBSS.
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
** $Log: qos_enhance.h $
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\11 2008-10-16 15:53:53 GMT mtk01461
**  Update driver to fix lint warning
**  \main\maintrunk.MT5921\10 2008-08-21 00:18:51 GMT mtk01461
**  Update for Driver Review
**  \main\maintrunk.MT5921\9 2008-08-20 20:59:48 GMT mtk01461
**  Update for Driver Review
**  \main\maintrunk.MT5921\8 2008-08-19 09:23:20 GMT mtk01084
**  modify for coding rule conformance
**  \main\maintrunk.MT5921\7 2008-07-25 17:16:28 GMT mtk01461
**  Replace #pragma pack(4) by #pragma pack(), can't use pack(pop), warnning by Linux Colibri Build Env.
**  \main\maintrunk.MT5921\6 2008-04-01 23:52:48 GMT mtk01461
**  Update comment and the typo QoS function call
**
*/
#ifndef _QOS_ENHANCE_H
#define _QOS_ENHANCE_H

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
/* WMM FLAGS */
#define WMM_FLAG_SUPPORT_WMM                BIT(0)
#define WMM_FLAG_SUPPORT_WMMSA              BIT(1)
#define WMM_FLAG_AC_PARAM_PRESENT           BIT(2)
#define WMM_FLAG_SUPPORT_UAPSD              BIT(3)

/* WMM Admission Control Mandatory FLAGS */
#define ACM_FLAG_ADM_NOT_REQUIRED           0
#define ACM_FLAG_ADM_GRANTED                BIT(0)
#define ACM_FLAG_ADM_REQUIRED               BIT(1)

/* WMM Power Saving FLAGS */
#define AC_FLAG_TRIGGER_ENABLED             BIT(1)
#define AC_FLAG_DELIVERY_ENABLED            BIT(2)


/* WMM-2.2.1 WMM Information Element */
#define ELEM_MAX_LEN_WMM_INFO               7

/* WMM-2.2.2 WMM Parameter Element */
#define ELEM_MAX_LEN_WMM_PARAM              24


/* WMM-2.2.1 WMM QoS Info field */
#define WMM_QOS_INFO_PARAM_SET_CNT          BITS(0,3) /* Sent by AP */
#define WMM_QOS_INFO_UAPSD                  BIT(7)

#define WMM_QOS_INFO_VO_UAPSD               BIT(0) /* Sent by non-AP STA */
#define WMM_QOS_INFO_VI_UAPSD               BIT(1)
#define WMM_QOS_INFO_BK_UAPSD               BIT(2)
#define WMM_QOS_INFO_BE_UAPSD               BIT(3)
#define WMM_QOS_INFO_MAX_SP_LEN_MASK        BITS(5,6)
#define WMM_QOS_INFO_MAX_SP_ALL             0
#define WMM_QOS_INFO_MAX_SP_2               BIT(5)
#define WMM_QOS_INFO_MAX_SP_4               BIT(6)
#define WMM_QOS_INFO_MAX_SP_6               BITS(5,6)

/* -- definitions for Max SP length field */
#define WMM_MAX_SP_LENGTH_ALL               0
#define WMM_MAX_SP_LENGTH_2                 2
#define WMM_MAX_SP_LENGTH_4                 4
#define WMM_MAX_SP_LENGTH_6                 6


/* WMM-2.2.2 WMM ACI/AIFSN field */
/* -- subfields in the ACI/AIFSN field */
#define WMM_ACIAIFSN_AIFSN                  BITS(0,3)
#define WMM_ACIAIFSN_ACM                    BIT(4)
#define WMM_ACIAIFSN_ACI                    BITS(5,6)
#define WMM_ACIAIFSN_ACI_OFFSET             5

/* -- definitions for ACI field */
#define WMM_ACI_AC_BE                       0
#define WMM_ACI_AC_BK                       BIT(5)
#define WMM_ACI_AC_VI                       BIT(6)
#define WMM_ACI_AC_VO                       BITS(5,6)

#define WMM_ACI(_AC)                        (_AC << WMM_ACIAIFSN_ACI_OFFSET)

/* -- definitions for ECWmin/ECWmax field */
#define WMM_ECWMINECWMAX_ECWMIN             BITS(0,3)
#define WMM_ECWMINECWMAX_ECWMAX             BITS(4,7)
#define WMM_ECWMINECWMAX_ECWMAX_OFFSET      4



/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/
/* WMM-2.2.2 WMM ACI to AC coding */
typedef enum _ENUM_AC_T {
    AC_BE = 0,
    AC_BK,
    AC_VI,
    AC_VO,
    AC_NUM
} ENUM_AC_T, *P_ENUM_AC_T;

typedef enum _ENUM_AC_PRIORITY_T {
    AC_BK_PRIORITY = 0,
    AC_BE_PRIORITY,
    AC_VI_PRIORITY,
    AC_VO_PRIORITY
} ENUM_AC_PRIORITY_T, *P_ENUM_AC_PRIORITY_T;


/* WMM-2.2.1 WMM Information Element */
typedef struct _IE_WMM_INFO_ELEM_T {
    UINT_8      ucId;                   /*!< Element ID */
    UINT_8      ucLength;               /*!< Length */
    UINT_8      aucOui[3];              /*!< OUI */
    UINT_8      ucOuiType;              /*!< OUI Type */
    UINT_8      ucOuiSubtype;           /*!< OUI Subtype */
    UINT_8      ucVersion;              /*!< Version */
    UINT_8      ucQosInfo;              /*!< QoS Info field */
    UINT_8      ucDummy[3];             /*!< Dummy for pack */
} IE_WMM_INFO_ELEM_T, *P_IE_WMM_INFO_ELEM_T;


/* WMM-2.2.1 WMM AC Parameters Record Format */
typedef struct _WMM_AC_PARAM_RECORD_T {
    UINT_8      ucAciAifsn;             /*!< ACI/AIFSN */
    UINT_8      ucECWminECWmax;         /*!< ECWmin/ECWmax */
    UINT_16     u2TxopLimit;            /*!< TXOP Limit */
} WMM_AC_PARAM_RECORD_T, *P_WMM_AC_PARAM_RECORD_T;


/* WMM-2.2.1 WMM Parameter Element */
typedef struct _IE_WMM_PARAM_ELEM_T {
    UINT_8      ucId;                   /*!< Element ID */
    UINT_8      ucLength;               /*!< Length */
    UINT_8      aucOui[3];              /*!< OUI */
    UINT_8      ucOuiType;              /*!< OUI Type */
    UINT_8      ucOuiSubtype;           /*!< OUI Subtype */
    UINT_8      ucVersion;              /*!< Version */
    UINT_8      ucQosInfo;              /*!< QoS Info field */
    UINT_8      ucReserved;
    /* AC Parameters Record AC_BE */
    UINT_8      ucAcParamBEAciAifsn;
    UINT_8      ucAcParamBEEcwminEcwmax;
    UINT_16     u2AcParamBETxopLimit;
    /* AC Parameters Record AC_BK */
    UINT_8      ucAcParamBKAciAifsn;
    UINT_8      ucAcParamBKEcwminEcwmax;
    UINT_16     u2AcParamBKTxopLimit;
    /* AC Parameters Record AC_VI */
    UINT_8      ucAcParamVIAciAifsn;
    UINT_8      ucAcParamVIEcwminEcwmax;
    UINT_16     u2AcParamVITxopLimit;
    /* AC Parameters Record AC_VO */
    UINT_8      ucAcParamVOAciAifsn;
    UINT_8      ucAcParamVOEcwminEcwmax;
    UINT_16     u2AcParamVOTxopLimit;
    UINT_8      ucDummy[2];             /*!< Dummy for pack */
}IE_WMM_PARAM_ELEM_T, *P_IE_WMM_PARAM_ELEM_T;


/*! \brief Store BSS Info's WMM AC Parameters */
typedef struct _WMM_AC_PARAM_T {
    UINT_8      ucAci;                  /*!< AC index (ACI) */
    UINT_8      ucAcmFlag;              /*!< Admission Control Mandatory (ACM) */
    UINT_8      ucAifsn;                /*!< AIFSN */
    UINT_8      ucECWmin;               /*!< ECWmin */
    UINT_8      ucECWmax;               /*!< ECWmax */
    UINT_16     u2TxopLimit;            /*!< TXOP limit */
} WMM_AC_PARAM_T, *P_WMM_AC_PARAM_T;


/*! \brief Store BSS Info's WMM settings */
typedef struct _WMM_INFO_T {
    UINT_8              ucWmmFlag;
    UINT_8              ucWmmParamSetCount;
    UINT_8              aucAcFlags[AC_NUM];     /*!< BIT definition refers to AC_FLAG. 0:AC_BE 1:AC_BK 2:AC_VI 3:AC_VO */
    WMM_AC_PARAM_T      arWmmAcParams[AC_NUM];  /*!< Total 4 ACs */
} WMM_INFO_T, *P_WMM_INFO_T;


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
#define WMM_INFO_IE(fp)             ((P_IE_WMM_INFO_ELEM_T) fp)
#define WMM_PARAM_IE(fp)            ((P_IE_WMM_PARAM_ELEM_T) fp)

/*******************************************************************************
*                   F U N C T I O N   D E C L A R A T I O N S
********************************************************************************
*/
VOID
qosWmmInfoInit (
    IN P_WMM_INFO_T prWmmInfo,
    IN BOOLEAN fgIs802_11b
    );

BOOLEAN
qosCheckQoSCapabilityByWMMInfoElem (
    IN PUINT_8 pucBuf,
    OUT PUINT_8 pucWmmFlag
    );

BOOLEAN
qosCheckQoSCapabilityByWMMParamElem (
    IN PUINT_8 pucBuf,
    OUT PUINT_8 pucWmmFlag
    );

BOOLEAN
qosParseWMMParamElem (
    IN PUINT_8 pucBuf,
    OUT P_WMM_INFO_T prWmmInfo
    );

UINT_8
qosConstructWMMInfoElem (
    IN P_ADAPTER_T prAdapter,
    IN UINT_8 ucWmmFlag,
    IN OUT PUINT_8 pucBuffer
    );

VOID
qosUpdateWMMParametersAndAssignAllowedACI (
    IN P_ADAPTER_T prAdapter,
    IN P_WMM_INFO_T prWmmInfo
    );

/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/
__KAL_INLINE__ VOID
qosDataTypeCheck (
    VOID
    )
{
    /* NOTE: We didn't pack following data structure, check the expected size */
    DATA_STRUC_INSPECTING_ASSERT(sizeof(IE_WMM_INFO_ELEM_T) == (2+7+(3)));
    DATA_STRUC_INSPECTING_ASSERT(sizeof(WMM_AC_PARAM_RECORD_T) == 4);
    DATA_STRUC_INSPECTING_ASSERT(sizeof(IE_WMM_PARAM_ELEM_T) == (2+24+(2)));

    return;
}

#endif /* _QOS_ENHANCE_H */

