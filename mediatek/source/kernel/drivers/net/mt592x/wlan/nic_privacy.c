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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/nic_privacy.c#2 $
*/

/*! \file   "net_privacy.c"
    \brief  This file including the driver privacy function.

    This file provided the macros and functions library support for the wlan_oid.c,
    rsn.c and wlan_table.c.
    
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
** $Log: nic_privacy.c $
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\35 2009-07-24 16:00:46 GMT mtk01090
**  Remove obsolete lines
**  \main\maintrunk.MT5921\34 2008-11-19 11:53:08 GMT mtk01088
**  fixed some lint warning
**  \main\maintrunk.MT5921\33 2008-10-27 18:53:42 GMT mtk01088
**  adjust the code, to avoid the lint warnning
**  \main\maintrunk.MT5921\32 2008-09-17 11:23:09 GMT mtk01088
**  fixed the compiling warning
**  \main\maintrunk.MT5921\31 2008-09-10 14:06:13 GMT mtk01088
**  check the compiling error
**  \main\maintrunk.MT5921\30 2008-09-09 20:09:40 GMT mtk01088
**  adjust the code to meet the code review
**  \main\maintrunk.MT5921\29 2008-09-09 10:51:00 GMT mtk01088
**  adjust the match entry rule
**  \main\maintrunk.MT5921\28 2008-09-01 17:00:29 GMT mtk01088
**  use the define to instead of the variable, and also add the assert check
**  \main\maintrunk.MT5921\27 2008-08-05 17:35:18 GMT mtk01088
**  the QoS and Antenna bit needed to take care while using template entry
**  \main\maintrunk.MT5921\26 2008-07-14 16:23:19 GMT mtk01088
**  fixed the prefast warning
**  \main\maintrunk.MT5921\25 2008-07-14 16:12:42 GMT mtk01088
**  fixed the prefast warning,
**  \main\maintrunk.MT5921\24 2008-07-11 12:17:48 GMT mtk01088
**  update the entry used flag
**  \main\maintrunk.MT5921\23 2008-06-16 20:28:19 GMT MTK01088
**  let the template entry not enable the Tv and Tkv for legacy
**  \main\maintrunk.MT5921\22 2008-06-14 11:24:27 GMT MTK01088
**  remove the template wlan table entry define
**  \main\maintrunk.MT5921\21 2008-02-29 15:32:09 GMT mtk01088
**  update the sw variable for sw port control, and not to set to HW wlan table
**  \main\maintrunk.MT5921\20 2008-02-29 13:20:39 GMT mtk01088
**  refine function name and delete non-used code
**  \main\maintrunk.MT5921\19 2008-02-12 23:00:45 GMT mtk01461
**  Add TX auto fragmentation for BT support
**  \main\maintrunk.MT5921\18 2008-02-12 15:58:54 GMT mtk01088
**  add the cipher is TKIP for condition check
**  \main\maintrunk.MT5921\17 2008-02-12 15:53:11 GMT mtk01088
**  rename the flag for CFG_LIMIT_TX_RATE_FOR_TKIP_TXOP_AT_FPGA
**  \main\maintrunk.MT5921\16 2008-02-12 15:49:38 GMT mtk01088
**  Do the rate update again (limit to max 36M) for cipher is TKIP and associate to a QoS AP
**  \main\maintrunk.MT5921\15 2008-02-01 10:21:06 GMT mtk01385
**  1. Fix WinCE 4.2 compiling error.
**  \main\maintrunk.MT5921\14 2008-01-21 09:53:11 GMT mtk01088
**  fixed the compiling error
**  \main\maintrunk.MT5921\13 2008-01-18 16:34:11 GMT mtk01088
**  \main\maintrunk.MT5921\12 2008-01-03 19:33:37 GMT mtk01088
**  fixed the compared error while add DLS or ad-hoc sta 
**  \main\maintrunk.MT5921\11 2007-11-26 21:50:51 GMT mtk01385
**  1. fix pass parameter bug.
**  \main\maintrunk.MT5921\10 2007-11-20 11:54:40 GMT mtk01088
**  add function to invlide key while countermeasure
**  \main\maintrunk.MT5921\9 2007-11-20 11:04:56 GMT mtk01088
**  fixed the direct set wlan table bug
**  \main\maintrunk.MT5921\8 2007-11-17 15:12:44 GMT mtk01385
**  1. fix input parament type typo. 
**  \main\maintrunk.MT5921\7 2007-11-08 20:37:41 GMT mtk01088
**  add the macthed function with keyid
**  \main\maintrunk.MT5921\6 2007-11-06 20:29:10 GMT mtk01088
**  add wep key for null mac address
** Revision 1.5  2007/07/16 02:49:34  MTK01088
** change function name
**
** Revision 1.4  2007/07/09 06:45:51  MTK01088
** update the function related with secuirty operation
**
** Revision 1.3  2007/07/04 10:20:33  MTK01088
** update privacy function for nic layer
**
** Revision 1.2  2007/07/03 08:32:52  MTK01088
** left hw-related code here, other put back to mgmt/privacy.c
**
** Revision 1.1  2007/06/28 12:53:08  MTK01088
** move the privacy.c from mgmt directory to nic directory, also rename
**
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
/* key type */
typedef enum _ENUM_KEY_TYPE_T {
    ENUM_KEY_TYPE_DEFAULT_KEY,
    ENUM_KEY_TYPE_GROUP_KEY    = ENUM_KEY_TYPE_DEFAULT_KEY,
    ENUM_KEY_TYPE_PAIRWISE_KEY,
    ENUM_KEY_TYPE_MAX
} ENUM_KEY_TYPE_T, *P_ENUM_KEY_TYPE_T;

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
* \brief This routine is called to initialize the privacy-related
*        parameters.
*
* \param[in] prAdapter Pointer to the adapter structure
*
* \retval NONE
*/
/*----------------------------------------------------------------------------*/
VOID
nicPrivacyInitialize (
    IN P_ADAPTER_T prAdapter
    )
{
    UINT_8      i;
    
    DEBUGFUNC("nicPrivacyInitialize");

    ASSERT(prAdapter);

    /* Clear Driver adapter key and HW wlan table content */
    for (i = 0; i < WLAN_TABLE_SIZE; i++) {
        kalMemZero((PVOID)&prAdapter->arWlanCtrl[i], sizeof(WLAN_ENTRY_CTRL_T));
    }
    halWlanTableInit(prAdapter);

}   /* nicPrivacyInitialize */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to enable the HW Tx Port control function
*
* \param[in] prAdapter Pointer to the adapter structure
*
* \return NONE
*/
/*----------------------------------------------------------------------------*/
VOID
nicPrivacyEnableHwTxPortControl (
    IN P_ADAPTER_T prAdapter
    )
{
    UINT_32                    u4tmp = 0;

    DEBUGFUNC("nicPrivacyEnableHwTxPortControl");
    
    ASSERT(prAdapter);

    HAL_MCR_RD(prAdapter, MCR_HCR, &u4tmp);
    HAL_MCR_WR(prAdapter, MCR_HCR, HCR_1X_CK_EN | u4tmp);

}   /* nicPrivacyEnableHwTxPortControl */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used before add/update a WLAN entry.
*        Info the WLAN Table has available entry for this request
*        The DA and RV is set will successful acquired, TV is by fgTxKey value
*
* \param[in]  prAdapter Pointer to the Adapter structure
* \param[in]  fgTxKey The key is used for Tx trasnmit key 
* \param[in]  pucBssid Pointer to the address 
* \param[in]  u4KeyId the key id, setting from oid 
* \param[in]  prSta the P_STA_RECORD_T for store 
* \param[out] pucEntryIndex The entry to be used 
*
* \retval TRUE Aquire a entry ok
* \retval FALSE fail to got a free entry
*
* \note
*     WLAN_TABLE_TEMPLATE_ENTRY is reserved for handshake template used
*     Called by:
*                1. Associate response with success 
*                2. Add DLS request for make sure available entry.
*                3. Ah-hoc add a new STA to WLAN Table
*/
/*----------------------------------------------------------------------------*/
BOOLEAN
nicPrivacySeekForEntry (
    IN  P_ADAPTER_T         prAdapter,
    IN  BOOLEAN             fgTxKey,
    IN  PUINT_8             pucBssid,
    IN  UINT_32             u4KeyId,              
    IN  P_STA_RECORD_T      prSta,
    OUT PUINT_8             pucEntryIndex
    )
{
    UCHAR                   i = 0;
    P_SW_KEY_STRUC_T        prSwKey = NULL;
    P_WT_CTRL_STRUC_T       prCtrl = NULL;
    UCHAR                   aucBcAddr[] = BC_MAC_ADDR;
    UCHAR                   aucNullAddr[] = NULL_MAC_ADDR;

    DEBUGFUNC("nicPrivacySeekForEntry");

    ASSERT(prAdapter);
    ASSERT(pucEntryIndex);

    if (pucBssid == NULL) {
        return FALSE;
    }
    
    *pucEntryIndex = WLAN_TABLE_SET_ALL;

    if (fgTxKey) {
        if (kalMemCmp(pucBssid, aucBcAddr, MAC_ADDR_LEN) == 0 ||
            kalMemCmp(pucBssid, aucNullAddr, MAC_ADDR_LEN) == 0) {
            *pucEntryIndex = WLAN_TABLE_DEFAULT_ENTRY;
        }
        else if (kalMemCmp(prAdapter->rBssInfo.aucBSSID, pucBssid, MAC_ADDR_LEN) == 0){
            *pucEntryIndex = WLAN_TABLE_DEFAULT_ENTRY;
        }
        else { /* DLS Case or IBSS WEP and WPA */
            for (i = WLAN_TABLE_TEMPLATE_ENTRY + 1 ; i < WLAN_TABLE_SIZE; i++) {
                prSwKey = (P_SW_KEY_STRUC_T)&prAdapter->arWlanCtrl[i].rSWKey;

                if (prAdapter->arWlanCtrl[i].fgUsed == FALSE) {
                    *pucEntryIndex = i;
                    break;
                }
                if (kalMemCmp(prSwKey->aucAddr, pucBssid, MAC_ADDR_LEN) == 0) {
                    if (prSwKey->ucKeyId == (u4KeyId & BITS(0,1))){
                        *pucEntryIndex = i;
                        break;
                    }
                }
            }
        }
    }
    else {
        /* Windows use BSSID to set BC key */
        for (i = WLAN_TABLE_SIZE - 1 ; i > WLAN_TABLE_TEMPLATE_ENTRY; i--) {
            prSwKey = (P_SW_KEY_STRUC_T)&prAdapter->arWlanCtrl[i].rSWKey;

            if (prAdapter->arWlanCtrl[i].fgUsed == FALSE) {
                *pucEntryIndex = i;
                break;
            }
            if (kalMemCmp(prSwKey->aucAddr, pucBssid, MAC_ADDR_LEN) == 0) {
                if (prSwKey->ucKeyId == (u4KeyId & BITS(0,1))){
                    *pucEntryIndex = i;
                    break;
                }
            }
        }
    }

    if (*pucEntryIndex == WLAN_TABLE_SET_ALL) {
        DBGLOG(NIC, WARN, ("No available wlan table entry !!\n"));
        ASSERT(FALSE);
        return FALSE;
    }
    else {
        /* For Windows, Add legacy key before SSID, will use entry 0 for fgTxKey == TRUE 
           And After Join Success, the initial will clear the setting */
        prSwKey = (P_SW_KEY_STRUC_T)&prAdapter->arWlanCtrl[*pucEntryIndex].rSWKey;
        prCtrl = (P_WT_CTRL_STRUC_T)&prAdapter->arWlanCtrl[*pucEntryIndex].rCtrl;

        if (prSwKey)
            kalMemCopy(prSwKey->aucAddr, pucBssid, MAC_ADDR_LEN);

        if ((prAdapter->rConnSettings.eAuthMode < AUTH_MODE_WPA) &&
            (*pucEntryIndex == WLAN_TABLE_TEMPLATE_ENTRY)) {
            prCtrl->fgTV = FALSE;
        }
        else {   
            prCtrl->fgTV = fgTxKey;
        }
        prCtrl->fgRV = TRUE;

        prAdapter->arWlanCtrl[*pucEntryIndex].fgUsed = TRUE;

        /* save the sta record pointer */
        prAdapter->arWlanCtrl[*pucEntryIndex].prSta = prSta;
    }

    DBGLOG(NIC, TRACE, ("entry %d alloced\n", *pucEntryIndex));
 
    return TRUE;
} /* nicPrivacySeekForEntry */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to found a WLAN entry by the bssid.
*
* \param[in]  prAdapter Pointer to the Adapter structure
* \param[in]  pucBssid Pointer to the address 
* \param[out] pucEntryIndex The matched entry 
*
* \retval TRUE Matched entry
* \retval FALSE fail to got a matched entry
*
*/
/*----------------------------------------------------------------------------*/
BOOLEAN
nicPrivacyMatchForEntry (
    IN  P_ADAPTER_T         prAdapter,
    IN  PUINT_8             pucBssid,
    IN  UINT_8              ucKeyId,
    OUT PUINT_8             pucEntryIndex
    )
{
    CHAR                    i = 0;
    P_SW_KEY_STRUC_T        prSwKey = NULL;
    BOOLEAN                 fgMatch = FALSE;
    
    DEBUGFUNC("nicPrivacyMatchForEntry");

    ASSERT(prAdapter);
    ASSERT(pucEntryIndex);
    
    if (pucBssid == NULL) {
        return FALSE;
    }
    
    *pucEntryIndex = WLAN_TABLE_SET_ALL;

    for (i = 0; i < WLAN_TABLE_SIZE; i++) {
        prSwKey = (P_SW_KEY_STRUC_T)&prAdapter->arWlanCtrl[i].rSWKey;

        if (kalMemCmp(prSwKey->aucAddr, pucBssid, MAC_ADDR_LEN) == 0 &&
            prAdapter->arWlanCtrl[i].fgUsed == TRUE) {
            *pucEntryIndex = i;
            fgMatch = TRUE;
            break;
        }
    }
    
    if (*pucEntryIndex == WLAN_TABLE_SET_ALL) { /* Broadcast */
        if (privacyTransmitKeyExist(prAdapter) && 
            ucKeyId == (prAdapter->rConnSettings.rMib.dot11WEPDefaultKeyID) && 
            prAdapter->arWlanCtrl[WLAN_TABLE_DEFAULT_ENTRY].fgUsed == TRUE)  {
                *pucEntryIndex = WLAN_TABLE_DEFAULT_ENTRY;
                fgMatch = TRUE;
        }
        else {

            for (i = WLAN_TABLE_SIZE - 1; i >= WLAN_TABLE_SIZE - 4 ; i--) {
                prSwKey = (P_SW_KEY_STRUC_T)&prAdapter->arWlanCtrl[i].rSWKey;
            
                if (prSwKey->ucKeyId == ucKeyId &&
                    prAdapter->arWlanCtrl[i].fgUsed == TRUE) {
                    *pucEntryIndex = i;
                    fgMatch = TRUE;
                    break;
                }
            }
        }
    }

    if (fgMatch == FALSE)
        return FALSE;
    
    DBGLOG(NIC, TRACE, ("entry %d matched\n", *pucEntryIndex));
    
    return TRUE;
} /* nicPrivacyMatchForEntry */


/*----------------------------------------------------------------------------*/
/*!
* \brief Do the key invalid.
*
* \param[in] prAdapter Pointer to the adapter structure
*
* \retval BOOLEAN
*/
/*----------------------------------------------------------------------------*/
BOOLEAN
nicPrivacyInvalidKey (
    IN P_ADAPTER_T          prAdapter,
    IN PUINT_8              pucBssid
   )
{
    P_WLAN_ENTRY_CTRL_T     prWlanCtrl;
    UINT_8                  ucEntryIndex;  

    DEBUGFUNC("nicPrivacyInvalidKey");

    ASSERT(prAdapter);
    
    if (nicPrivacyMatchForEntry(prAdapter,
                                pucBssid, 
                                0,
                                &ucEntryIndex) == FALSE){
        return FALSE;
    }

    prWlanCtrl = &prAdapter->arWlanCtrl[ucEntryIndex];

    prWlanCtrl->rCtrl.fgT1X = TRUE;
    prWlanCtrl->rCtrl.fgR1X = TRUE;
    prWlanCtrl->rCtrl.fgTKV = FALSE;
    prWlanCtrl->rSWKey.ucCipher = CIPHER_SUITE_NONE;

    nicPrivacyDumpWlanTable(prAdapter, ucEntryIndex);
    if (halWlanTableAccess(prAdapter,
                          (PVOID)prWlanCtrl,
                           ucEntryIndex, 
                           HWTDR_UPDATE_MODE_0) == FALSE) {
        ASSERT(FALSE);
    }
    return TRUE;
} /* nicPrivacyInvalidKey */


/*----------------------------------------------------------------------------*/
/*!
* \brief Do the port control setting.
*
* \param[in] prAdapter Pointer to the adapter structure
* \param[in] pucBssid The address to matched the wlan table entry
* \param[in] Block or Open the Tx data path
* \param[in] Block or Open the Rx data path
*
* \return none
*/
/*----------------------------------------------------------------------------*/
VOID
nicPrivacyPortControl (
    IN P_ADAPTER_T        prAdapter,
    IN PUINT_8            pucBssid,
    IN BOOLEAN            fgTxPort,
    IN BOOLEAN            fgRxPort
   )
{
    P_WT_CTRL_STRUC_T     prCtrl;
    UINT_8                ucEntryIndex;  

    DEBUGFUNC("nicPrivacyPortControl");

    ASSERT(prAdapter);
    
    if (nicPrivacyMatchForEntry(prAdapter,
                                pucBssid, 
                                0,
                               &ucEntryIndex) == FALSE){
        if (kalMemCmp(prAdapter->rBssInfo.aucBSSID, pucBssid, MAC_ADDR_LEN) == 0)
            ucEntryIndex = WLAN_TABLE_DEFAULT_ENTRY;
        else {
            return;
        }
    }
    
    prCtrl = (P_WT_CTRL_STRUC_T)&prAdapter->arWlanCtrl[ucEntryIndex].rCtrl;

    if (prAdapter->rSecInfo.fgBlockOnlyAPTraffic) {
        prAdapter->rSecInfo.fgBlockTxTraffic = fgTxPort;
        prAdapter->rSecInfo.fgBlockRxTraffic = fgRxPort;
    }
    else {
        prCtrl->fgT1X = fgTxPort;
        prCtrl->fgR1X = fgRxPort;
    }

    return;
} /* nicPrivacyPortControl */


/*----------------------------------------------------------------------------*/
/*!
* \brief Update the wlan table entry.
*
* \param[in] prAdapter Pointer to the adapter structure
* \param[in] pucBSSID the AP or STA address to be set
* \param[in] prSta The STA record pointer to stored
* \param[in] fgQoS the QoS setting
* \param[in] fgAntenna the Antenna setting
* \param[in] pucMuar the muar index setting
* \param[in] pucRate1 the rate 1 setting
* \param[in] pucRate2 the rate 2 setting
* \param[in] pucRate3 the rate 3 setting
* \param[in] pucRate4 the rate 4 setting
*
* \retval BOOLEAN
*/
/*----------------------------------------------------------------------------*/
BOOLEAN
nicPrivacyUpdateBySta (
    IN P_ADAPTER_T           prAdapter,
    IN PUINT_8               pucBSSID,
    IN P_STA_RECORD_T        prSta,
    IN PBOOLEAN              pfgQoS,
    IN PBOOLEAN              pfgAntenna,
    IN PUINT_8               pucMuar,
    IN PUINT_8               pucRate1,
    IN PUINT_8               pucRate2,
    IN PUINT_8               pucRate3,
    IN PUINT_8               pucRate4
    )
{
    UINT_8                   ucEntryIndex;
    P_SW_KEY_STRUC_T         prSwKey = NULL, prDefSwKey = NULL;
    P_WT_CTRL_STRUC_T        prCtrl = NULL, prDefCtrl = NULL;

    DEBUGFUNC("nicPrivacyUpdateBySta");

    ASSERT(prAdapter);
    
    if (nicPrivacySeekForEntry(prAdapter,
                               TRUE,
                               (PUINT_8)pucBSSID, 
                               0,
                               prSta,
                               &ucEntryIndex) == FALSE){
        return FALSE;
    }

    prCtrl = (P_WT_CTRL_STRUC_T)&prAdapter->arWlanCtrl[ucEntryIndex].rCtrl;
    prSwKey = (P_SW_KEY_STRUC_T)&prAdapter->arWlanCtrl[ucEntryIndex].rSWKey;

    prDefCtrl = (P_WT_CTRL_STRUC_T)&prAdapter->arWlanCtrl[WLAN_TABLE_DEFAULT_ENTRY].rCtrl;
    prDefSwKey = (P_SW_KEY_STRUC_T)&prAdapter->arWlanCtrl[WLAN_TABLE_DEFAULT_ENTRY].rSWKey;


    if (pfgQoS) {                                
        prCtrl->fgQoS = *pfgQoS;
    }  

    if (pfgAntenna) {                                
        prCtrl->fgAntenna = *pfgAntenna;
    }

    if (pucMuar) {                                
        prCtrl->ucMuar = *pucMuar;
    }
    
    if (pucRate1) {                                
        prCtrl->ucRate1 = *pucRate1;
    }
    if (pucRate2) {                                
        prCtrl->ucRate2 = *pucRate2;
    }    
    if (pucRate3) {                                
        prCtrl->ucRate3 = *pucRate3;
    }    
    if (pucRate4) {                                
        prCtrl->ucRate4 = *pucRate4;
    }        

    /* The IBSS WEP & WPA-NONE, the key should copy to the entry */
    if (prAdapter->rConnSettings.eOPMode == NET_TYPE_IBSS &&
        prAdapter->rConnSettings.eEncStatus != ENUM_WEP_DISABLED) {
        if (privacyTransmitKeyExist(prAdapter) && ucEntryIndex !=0 ) {
            prCtrl->fgRKV = 
                prAdapter->arWlanCtrl[WLAN_TABLE_DEFAULT_ENTRY].rCtrl.fgRKV;
            if ((prAdapter->rConnSettings.eAuthMode < AUTH_MODE_WPA) &&
                (ucEntryIndex == WLAN_TABLE_TEMPLATE_ENTRY)){
                prCtrl->fgTKV = FALSE;
            }
            else {     
                prCtrl->fgTKV = prDefCtrl->fgTKV;
            }
            prSwKey->ucRCA1 = prDefSwKey->ucRCA1;
            prSwKey->fgRCA2 = prDefSwKey->fgRCA2;
            prSwKey->fgRCID = prDefSwKey->fgRCID;
            prSwKey->ucKeyId = prDefSwKey->ucKeyId;
            prSwKey->ucCipher= prDefSwKey->ucCipher;
            
            kalMemCopy(&prSwKey->aucKeyMaterial[0],
                prDefSwKey->aucKeyMaterial,
                TKIP_KEY_LEN - ( 2 * MIC_KEY_LEN));
            kalMemCopy(&prSwKey->aucRxMicMaterial[0],
                &prDefSwKey->aucRxMicMaterial[0],
                MIC_KEY_LEN);
            kalMemCopy(&prSwKey->aucTxMicMaterial[0],
                &prDefSwKey->aucTxMicMaterial[0],
                MIC_KEY_LEN);
            
        }
    }

    nicPrivacyDumpWlanTable(prAdapter, ucEntryIndex);

    return halWlanTableAccess(prAdapter, 
                             (PVOID)&prAdapter->arWlanCtrl[ucEntryIndex],
                              ucEntryIndex,
                              HWTDR_UPDATE_MODE_3);     /* Set key into H/W key table */

} /* nicPrivacyUpdateBySta */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function set key into both MIB and H/W key table
*
* \param[in] prAdapter Pointer to the adapter object data area.
* \param[in] fgPairwise TRUE pairwise key FALSE, group key
* \param[in] pucBssid BSSID
* \param[in] prSta The STA record pointer to stored
* \param[in] ucKeyId key ID
* \param[in] pucKeyMaterial key material
* \param[in] ucKeyLen key length
* \param[in] ucCipherMode Cipher mode
* \param[in] ucTxMicOffset TKIP MIC key material offset for TX
* \param[in] ucRxMicOffset TKIP MIC key material offset for RX
*
* \retval BOOLEAN
*/
/*----------------------------------------------------------------------------*/
BOOLEAN
nicPrivacySetKeyEntry (
    IN P_ADAPTER_T          prAdapter,
    IN BOOLEAN              fgTxKey,
    IN PUINT_8              pucBssid,
    IN UINT_8               ucKeyId,
    IN PUINT_8              pucKeyMaterial,
    IN UINT_8               ucKeyLen,
    IN UINT_8               ucCipherMode,
    IN UINT_8               ucTxMicOffset,
    IN UINT_8               ucRxMicOffset
    )
{
    P_WLAN_ENTRY_CTRL_T     prWlanCtrl;
    P_SW_KEY_STRUC_T        prSwKey = NULL;
    P_WT_CTRL_STRUC_T       prCtrl = NULL;
    UINT_8                  ucEntryIndex;
    P_STA_RECORD_T          prSta;
    UINT_8                  aucBCAddr[] = BC_MAC_ADDR;
    
    DEBUGFUNC("nicPrivacySetKeyEntry");

    ASSERT(prAdapter); 
    ASSERT(pucBssid);
    ASSERT(pucKeyMaterial); 

    prSta = staRecGetStaRecordByAddr(prAdapter, pucBssid);
    
    nicPrivacySeekForEntry(prAdapter, 
                           fgTxKey,
                           pucBssid, 
                           ucKeyId,
                           prSta,
                           &ucEntryIndex);

    prWlanCtrl = &prAdapter->arWlanCtrl[ucEntryIndex];
    prSwKey = &prWlanCtrl->rSWKey;
    prCtrl = &prWlanCtrl->rCtrl;

    /* !!! Do This will clear the QoS,... setting */
    //kalMemZero(prCfgKey, sizeof(WLAN_ENTRY_CTRL_T));

    /* Pairwise key always uses 0 as key ID */
    switch (ucCipherMode) {
        case CIPHER_SUITE_NONE: /* FALL THROUGH */
        case CIPHER_SUITE_WEP40: /* FALL THROUGH */
        case CIPHER_SUITE_TKIP: /* FALL THROUGH */
        case CIPHER_SUITE_TKIP_WO_MIC: /* FALL THROUGH */
        case CIPHER_SUITE_CCMP: /* FALL THROUGH */
        case CIPHER_SUITE_WEP104: /* FALL THROUGH */
        case CIPHER_SUITE_WEP128: /* FALL THROUGH */
            prSwKey->ucCipher = ucCipherMode;
            break;
        default:
            DBGLOG(RSN, WARN, ("Unknown Cipher mode %d\n", ucCipherMode));
            prSwKey->ucCipher = CIPHER_SUITE_NONE;
            break;
    }

    prSwKey->ucKeyId = ucKeyId;

    kalMemCopy(prSwKey->aucAddr, pucBssid, MAC_ADDR_LEN);
    kalMemCopy(prSwKey->aucKeyMaterial, pucKeyMaterial, TKIP_KEY_LEN - (MIC_KEY_LEN * 2));

    kalMemCopy(prSwKey->aucRxMicMaterial, pucKeyMaterial + ucRxMicOffset, MIC_KEY_LEN);
    kalMemCopy(prSwKey->aucTxMicMaterial, pucKeyMaterial + ucTxMicOffset, MIC_KEY_LEN);

    if (fgTxKey) {
        if (kalMemCmp(pucBssid, aucBCAddr, MAC_ADDR_LEN) == 0) {
            prSwKey->ucRCA1 = HWTDR_RCA1_MUAR_BC;
        }
        else {            
            prSwKey->ucRCA1 = HWTDR_RCA1_MUAR_ONLY;
        }
        prCtrl->fgTV = TRUE;
        prCtrl->fgTKV = TRUE;
    }
    else {
        prSwKey->ucRCA1 = HWTDR_RCA1_MUAR_BC;
        prSwKey->fgRCA2 = FALSE;
    }

    prSwKey->fgRCID = TRUE;
    prCtrl->fgRV = TRUE;
    prCtrl->fgRKV = TRUE;

    nicPrivacyDumpWlanTable(prAdapter, ucEntryIndex);

    return halWlanTableAccess(prAdapter, 
                             (PVOID)prWlanCtrl,
                              ucEntryIndex,
                              HWTDR_UPDATE_MODE_3);     /* Set key into H/W key table */
  
} /* nicPrivacySetIpcKeyEntry */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function set key into both MIB and H/W key table
*
* \param[in] prAdapter Pointer to the adapter object data area.
* \param[in] pucBssid BSSID
* \param[in] pucKeyMaterial key material
* \param[in] ucKeyLen key length
* \param[in] ucCipherMode Cipher mode
* \param[in] ucTxMicOffset TKIP MIC key material offset for TX
* \param[in] ucRxMicOffset TKIP MIC key material offset for RX
*
* \retval none
*/
/*----------------------------------------------------------------------------*/
VOID
nicPrivacySetKeyToTemplateEntry (
    IN P_ADAPTER_T          prAdapter,
    IN PUINT_8              pucBssid,
    IN PUINT_8              pucKeyMaterial,
    IN UINT_8               ucKeyLen,
    IN UINT_8               ucCipherMode,
    IN UINT_8               ucTxMicOffset,
    IN UINT_8               ucRxMicOffset
    )
{
    P_WLAN_ENTRY_CTRL_T     prWlanCtrl;
    P_SW_KEY_STRUC_T        prSwKey = NULL;
    P_WT_CTRL_STRUC_T       prCtrl = NULL;
    P_WT_CTRL_STRUC_T       prOrgCtrl = NULL;
    UINT_8                  ucEntryIndex;

    DEBUGFUNC("nicPrivacySetKeyToTemplateEntry");

    ucEntryIndex = WLAN_TABLE_TEMPLATE_ENTRY;

    ASSERT(prAdapter);
    ASSERT(pucBssid);
    ASSERT(pucKeyMaterial);

    if (!nicPrivacyGetWlanIndexByAddr(prAdapter, pucBssid, &ucEntryIndex)) {
        ASSERT(FALSE);
    }

    prWlanCtrl = &prAdapter->arWlanCtrl[WLAN_TABLE_TEMPLATE_ENTRY];
    prSwKey = &prWlanCtrl->rSWKey;
    prCtrl = &prWlanCtrl->rCtrl;
    prOrgCtrl = &prAdapter->arWlanCtrl[ucEntryIndex].rCtrl;

    kalMemZero(prWlanCtrl, sizeof(WLAN_ENTRY_CTRL_T));

    switch (ucCipherMode) {
        case CIPHER_SUITE_NONE: /* FALL THROUGH */
        case CIPHER_SUITE_WEP40: /* FALL THROUGH */
        case CIPHER_SUITE_TKIP: /* FALL THROUGH */
        case CIPHER_SUITE_TKIP_WO_MIC: /* FALL THROUGH */
        case CIPHER_SUITE_CCMP: /* FALL THROUGH */
        case CIPHER_SUITE_WEP104: /* FALL THROUGH */
        case CIPHER_SUITE_WEP128: /* FALL THROUGH */
            prSwKey->ucCipher = ucCipherMode;
            break;
        default:
            DBGLOG(RSN, WARN, ("Unknown Cipher mode %d\n", ucCipherMode));
            prSwKey->ucCipher = CIPHER_SUITE_NONE;
            break;
    }

    prSwKey->ucKeyId = 0;

    kalMemCopy(prSwKey->aucAddr, pucBssid, MAC_ADDR_LEN);
    kalMemCopy(prSwKey->aucKeyMaterial, pucKeyMaterial, TKIP_KEY_LEN - (MIC_KEY_LEN * 2));

    kalMemCopy(prSwKey->aucRxMicMaterial, pucKeyMaterial + ucRxMicOffset, MIC_KEY_LEN);
    kalMemCopy(prSwKey->aucTxMicMaterial, pucKeyMaterial + ucTxMicOffset, MIC_KEY_LEN);

    prCtrl->fgQoS = prOrgCtrl->fgQoS;
    prCtrl->fgAntenna = prOrgCtrl->fgAntenna;
    prCtrl->ucMuar = prOrgCtrl->ucMuar;
    prCtrl->ucRate1 = prOrgCtrl->ucRate1;
    prCtrl->ucRate2 = prOrgCtrl->ucRate2;
    prCtrl->ucRate3 = prOrgCtrl->ucRate3;
    prCtrl->ucRate4 = prOrgCtrl->ucRate4;

    prSwKey->ucRCA1 = HWTDR_RCA1_MUAR_ONLY;
    prSwKey->fgRCA2 = TRUE;
    prSwKey->fgRCID = TRUE;
    prCtrl->fgTV = FALSE;
    prCtrl->fgRKV = TRUE;
    prCtrl->fgRV = TRUE;

    if (prAdapter->rSecInfo.fgBlockOnlyAPTraffic) {
        //check the bssid is ap?
        prAdapter->rSecInfo.fgBlockTxTraffic = TRUE;
        prAdapter->rSecInfo.fgBlockRxTraffic = FALSE;
    }
    else {
        prCtrl->fgT1X = TRUE;
        prCtrl->fgR1X = FALSE;
    }

    nicPrivacyDumpWlanTable(prAdapter, WLAN_TABLE_TEMPLATE_ENTRY);

    /* Set key into H/W key table */
    if (!halWlanTableAccess(prAdapter, 
                             (PVOID)prWlanCtrl,
                              WLAN_TABLE_TEMPLATE_ENTRY,
                              HWTDR_UPDATE_MODE_3)) {
                              
    }
  
} /* nicPrivacySetKeyToTemplateEntry */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function return the stored sta record pointer and index at w table
*
* \param[in]  prAdapter Pointer to the adapter object data area.
* \param[in]  pucBssid The Mac address to search for invalid
* \param[out] pucWlanIndex The entry to be found.
*
* \retval TRUE Find entry
* \retval FALSE Not found or entry not used
*/
/*----------------------------------------------------------------------------*/
P_STA_RECORD_T
nicPrivacyGetWlanIndexByAddr (
    IN  P_ADAPTER_T          prAdapter,
    IN  PUINT_8              pucBssid,
    OUT PUINT_8              pucWlanIndex
    )
{
    UINT_8                   i;
    PUINT_8                  pucAddr;

    ASSERT(prAdapter);
    ASSERT(pucBssid);
    ASSERT(pucWlanIndex);
    
    for (i = 0; i < WLAN_TABLE_SIZE; i++) {
        pucAddr = &prAdapter->arWlanCtrl[i].rSWKey.aucAddr[0];

        if (prAdapter->arWlanCtrl[i].fgUsed &&
            kalMemCmp(pucAddr, pucBssid, MAC_ADDR_LEN) == 0) {
            *pucWlanIndex = i;
            break;
        }
    }

    if (i >= WLAN_TABLE_SIZE) {
        return NULL;
    }

    return prAdapter->arWlanCtrl[i].prSta;
} /* nicPrivacyGetWlanIndexByAddr */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function return the stored sta record pointer according to the given
*        index at w table
*
* \param[in]  prAdapter Pointer to the adapter object data area.
* \param[in]  ucWlanIndex index at w table.
*
* \retval !NULL Find entry
* \retval NULL Not found or entry not used
*/
/*----------------------------------------------------------------------------*/
P_STA_RECORD_T
nicPrivacyGetStaRecordByWlanIndex (
    IN  P_ADAPTER_T         prAdapter,
    IN  UINT_8              ucWlanIndex
    )
{
    P_WLAN_ENTRY_CTRL_T prWlanCtrl;

    ASSERT(prAdapter);

    if (ucWlanIndex < WLAN_TABLE_SIZE) {
        prWlanCtrl = &prAdapter->arWlanCtrl[ucWlanIndex];

        return prWlanCtrl->prSta;
    }
#if DBG
    else {
        ASSERT(FALSE);
    }
#endif /* DBG */

    return (P_STA_RECORD_T)NULL;

} /* nicPrivacyGetStaRecordByWlanIndex */


/*----------------------------------------------------------------------------*/
/*!
* \brief Invalid the wlan table entry Rx.
*
* \param[in] prAdapter Pointer to the adapter structure
* \param[in] pucBssid The Mac address to search for invalid
*
* \retval BOOLEAN
*/
/*----------------------------------------------------------------------------*/
BOOLEAN
nicPrivacyCopyFromTemplateEntry (
    IN P_ADAPTER_T          prAdapter
    )
{
    PUINT_8                 pucBssid;
    UINT_8                  ucEntry;
    P_WLAN_ENTRY_CTRL_T     prWlanCtrl, prOrgCfgEntry;

    DEBUGFUNC("nicPrivacyCopyFromTemplateEntry");

    ASSERT(prAdapter);
    
    pucBssid = &prAdapter->arWlanCtrl[WLAN_TABLE_TEMPLATE_ENTRY].rSWKey.aucAddr[0];
    
    if (nicPrivacyMatchForEntry(prAdapter, 
                               pucBssid, 
                               0,
                               &ucEntry) == FALSE){
        return FALSE;
    }

    /* Open the port for orginal entry */
    nicPrivacyPortControl(prAdapter, pucBssid, FALSE, FALSE);
    
    prOrgCfgEntry = &prAdapter->arWlanCtrl[WLAN_TABLE_TEMPLATE_ENTRY];
    prWlanCtrl = &prAdapter->arWlanCtrl[ucEntry];

    kalMemCopy((PVOID)prWlanCtrl, prOrgCfgEntry, sizeof(WLAN_ENTRY_CTRL_T));
    prWlanCtrl->rCtrl.fgTV = TRUE;
    prWlanCtrl->rCtrl.fgTKV = TRUE;

    prAdapter->arWlanCtrl[ucEntry].fgUsed = TRUE;

    nicPrivacyDumpWlanTable(prAdapter, ucEntry);

    return halWlanTableAccess(prAdapter, 
                             (PVOID)prWlanCtrl, 
                              ucEntry,
                              HWTDR_UPDATE_MODE_3);
    
}


/*----------------------------------------------------------------------------*/
/*!
* \brief Invalid the wlan table entry Rx.
*
* \param[in] prAdapter Pointer to the adapter structure
* \param[in] pucBssid The Mac address to search for invalid
*
* \return none
*/
/*----------------------------------------------------------------------------*/
VOID
nicPrivacyInvalidEntryRx (
    IN P_ADAPTER_T          prAdapter,
    IN PUINT_8              pucBssid
    )
{
    UINT_8                  ucEntry;
    
    DEBUGFUNC("nicPrivacyInvalidEntryRx");

    ASSERT(prAdapter);

    if (nicPrivacyMatchForEntry(prAdapter, 
                           pucBssid, 
                           0,
                           &ucEntry) == FALSE){
        return;                   
    }

    /* Invalid entry 0 for AP, x for DLS rv=0 */
    prAdapter->arWlanCtrl[ucEntry].rCtrl.fgRV = FALSE;

    nicPrivacyDumpWlanTable(prAdapter, ucEntry);

    if (!halWlanTableAccess(prAdapter, 
        (PVOID)&prAdapter->arWlanCtrl[ucEntry], 
        ucEntry, 
        HWTDR_UPDATE_MODE_0)) {
        DBGLOG(NIC, TRACE, ("Access Wlan table failed\n"));
    }

    return;
} /* nicPrivacyValidEntry */


/*----------------------------------------------------------------------------*/
/*!
* \brief Valid the wlan table entry.
*
* \param[in] prAdapter Pointer to the adapter structure
*
* \retval BOOLEAN
*/
/*----------------------------------------------------------------------------*/
VOID
nicPrivacyInvalidTemplateEntry (
    IN P_ADAPTER_T          prAdapter
    )
{
    DEBUGFUNC("nicPrivacyInvalidTemplateEntry");

    ASSERT(prAdapter);
    
    prAdapter->arWlanCtrl[WLAN_TABLE_TEMPLATE_ENTRY].rCtrl.fgTV = FALSE;
    prAdapter->arWlanCtrl[WLAN_TABLE_TEMPLATE_ENTRY].rCtrl.fgRV = FALSE;

    nicPrivacyDumpWlanTable(prAdapter, WLAN_TABLE_TEMPLATE_ENTRY);

    if (!halWlanTableAccess(prAdapter, 
        (PVOID)&prAdapter->arWlanCtrl[WLAN_TABLE_TEMPLATE_ENTRY], 
        WLAN_TABLE_TEMPLATE_ENTRY, 
        HWTDR_UPDATE_MODE_0)){
    }

    return;
} /* nicPrivacyInvalidTemplateEntry */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function to set the WLAN_ENTRY_CTRL_T structure to wlan table
*        The function will not set to adapter variable.
*
* \param[in] prAdapter Pointer to the adapter object data area.
* \param[in] ucEntry The entry to be set.
* \param[in] the sta record to stoted.
* \param[in] prWTCtrl Pointer to the P_WT_CTRL_STRUC_T structure
* \param[in] prSwKey Pointer to the P_SW_KEY_STRUC_T structure
*
*/
/*----------------------------------------------------------------------------*/
BOOLEAN
nicPrivacySetWlanTable (
    IN  P_ADAPTER_T          prAdapter,
    IN  UINT_8               ucEntry,
    IN  P_STA_RECORD_T       prSta,
    IN  P_WT_CTRL_STRUC_T    prWTCtrl,
    IN  P_SW_KEY_STRUC_T     prSwKey
    )
{
    P_WLAN_ENTRY_CTRL_T      prWlanEntry;

    ASSERT(prAdapter);
    ASSERT(prWTCtrl);
    ASSERT(prSwKey);

    prWlanEntry = &prAdapter->arWlanCtrl[ucEntry];
        
    kalMemZero((PUINT_8)prWlanEntry, sizeof(WLAN_ENTRY_CTRL_T));

    /* Assign the variable here */
    prWlanEntry->fgUsed = TRUE;
    prWlanEntry->prSta = prSta;

    kalMemCopy((PUINT_8)&prWlanEntry->rCtrl, prWTCtrl, sizeof(WT_CTRL_STRUC_T));
    kalMemCopy((PUINT_8)&prWlanEntry->rSWKey, prSwKey, sizeof(SW_KEY_STRUC_T));
    
    return halWlanTableAccess(prAdapter, 
                              (PVOID)prWlanEntry,
                              ucEntry,
                              HWTDR_UPDATE_MODE_3);
}


/*----------------------------------------------------------------------------*/
/*!
* \brief This function to set the WLAN_ENTRY_CTRL_T structure to wlan table
*        The function will not set to adapter variable.
*
* \param[in] prAdapter Pointer to the adapter object data area.
* \param[in] ucEntry The entry to be clear.
*
*/
/*----------------------------------------------------------------------------*/
BOOLEAN
nicPrivacyClearWlanTable (
    IN  P_ADAPTER_T          prAdapter,
    IN  UINT_8               ucEntry
    )
{
    P_WLAN_ENTRY_CTRL_T      prWlanEntry;

    ASSERT(prAdapter);
    
    prWlanEntry = &prAdapter->arWlanCtrl[ucEntry];
        
    kalMemZero((PUINT_8)prWlanEntry, sizeof(WLAN_ENTRY_CTRL_T));

    /* Assign the variable here */
    prWlanEntry->fgUsed = FALSE;
    prWlanEntry->prSta = NULL;
    
    return halWlanTableAccess(prAdapter, 
                              (PVOID)prWlanEntry,
                              ucEntry,
                              HWTDR_UPDATE_MODE_3);
}


/*----------------------------------------------------------------------------*/
/*!
* \brief This function dump the WLAN_TABLE_T structure
*
* \param[in] prAdapter Pointer to the adapter object data area.
* \param[in] ucEntry The entry to be dump.
*
*/
/*----------------------------------------------------------------------------*/
VOID
nicPrivacyDumpWlanTable (
    IN  P_ADAPTER_T          prAdapter,
    IN  UINT_8               ucEntry
    )
{
#if DBG
    UINT_8                   i;
    UINT_8                   ucMinIndex, ucMaxIndex;
    P_WT_CTRL_STRUC_T        prCtrl;
    P_SW_KEY_STRUC_T         prKey;

    DEBUGFUNC("nicPrivacyDumpWlanTable");

    ASSERT(prAdapter);
    
    if (ucEntry >= WLAN_TABLE_SIZE && ucEntry != WLAN_TABLE_SET_ALL)
        return;
    
    if (ucEntry == WLAN_TABLE_SET_ALL) {
        ucMinIndex = WLAN_TABLE_DEFAULT_ENTRY;
        ucMaxIndex = WLAN_TABLE_SIZE - 1;
    }
    else  {
        ucMinIndex = ucEntry;
        ucMaxIndex = ucEntry;
    }
    
    for (i=ucMinIndex; i<=ucMaxIndex; i++) {
        prCtrl = &prAdapter->arWlanCtrl[i].rCtrl;
        prKey = &prAdapter->arWlanCtrl[i].rSWKey;
        
        DBGLOG(HAL, TRACE, ("=============================================\n"));
        DBGLOG(HAL, TRACE, ("Index %d\n", i));
        DBGLOG(HAL, TRACE, ("TV %d TKV %d T1x %d\n", 
                            prCtrl->fgTV, prCtrl->fgTKV, prCtrl->fgT1X));
        DBGLOG(HAL, TRACE, ("RV %d RKV %d R1x %d\n", 
                            prCtrl->fgRV, prCtrl->fgRKV, prCtrl->fgR1X));
        DBGLOG(HAL, TRACE, ("RCA1 %d RCA2 %d RCID %d\n", 
                            prKey->ucRCA1, prKey->fgRCA2, prKey->fgRCID));
        DBGLOG(HAL, TRACE, ("Cipher %d KeyId %d \n", 
                            prKey->ucCipher, prKey->ucKeyId));
        DBGLOG(HAL, TRACE, ("Q %d A %d IKV %d\n", 
                            prCtrl->fgQoS, prCtrl->fgAntenna, prKey->fgIKV));
        DBGLOG(HAL, TRACE, ("Rate1 %02x Rate2 %02x Rate3 %02x Rate4 %02x \n", 
                            prCtrl->ucRate1, prCtrl->ucRate2, prCtrl->ucRate3, prCtrl->ucRate4));
        DBGLOG(HAL, TRACE, ("DA " MACSTR" muar %d\n", 
                            MAC2STR(prKey->aucAddr), prCtrl->ucMuar));
        DBGLOG_MEM8(HAL, TRACE, prKey->aucKeyMaterial, TKIP_KEY_LEN - (MIC_KEY_LEN * 2));
        DBGLOG_MEM8(HAL, TRACE, prKey->aucRxMicMaterial, MIC_KEY_LEN);
        DBGLOG_MEM8(HAL, TRACE, prKey->aucTxMicMaterial, MIC_KEY_LEN);
        
    }
#endif
}
