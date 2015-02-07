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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/privacy.c#2 $
*/

/*! \file   "privacy.c"
    \brief  This file including the protocol layer privacy function.

    This file provided the macros and functions library support for the 
    protocol layer security setting from wlan_oid.c and for parse.c and
    rsn.c and nic_privacy.c
    
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
** $Log: privacy.c $
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\33 2009-07-06 20:33:58 GMT mtk01088
**  adding the code for wpi related variable initialize
**  \main\maintrunk.MT5921\32 2009-04-29 19:46:11 GMT mtk01088
**  fixed the cipher by encryption status instead of length while at wpa-none
**  \main\maintrunk.MT5921\31 2008-12-04 20:02:15 GMT mtk01088
**  remove non-used code and fixed the lint warning
**  \main\maintrunk.MT5921\30 2008-11-19 11:49:46 GMT mtk01088
**  fixed some lint warning, and rename some variable with pre-fix to avoid the misunderstanding
**  \main\maintrunk.MT5921\29 2008-10-27 19:55:49 GMT mtk01088
**  avoide the lint compiling warnning
**  \main\maintrunk.MT5921\28 2008-10-27 18:00:51 GMT mtk01088
**  adjust the code flow to fixed the lint warnning
**  \main\maintrunk.MT5921\27 2008-09-09 10:49:53 GMT mtk01088
**  adjust the pointer to meet the code review
**  \main\maintrunk.MT5921\26 2008-08-29 18:04:57 GMT mtk01088
**  let the variable with define
**  \main\maintrunk.MT5921\25 2008-08-15 20:07:23 GMT mtk01088
**  add assert for function check
**  use define instead variable
**  \main\maintrunk.MT5921\24 2008-08-06 21:46:07 GMT mtk01088
**  clear all wlan table entry expect some filed needed to store
**  \main\maintrunk.MT5921\23 2008-08-06 15:26:39 GMT mtk01088
**  fixed the structure size
**  \main\maintrunk.MT5921\22 2008-08-05 21:59:39 GMT mtk01088
**  only remove the key material and related setting
**  \main\maintrunk.MT5921\21 2008-07-31 11:48:01 GMT mtk01088
**  not to zero the DA address while driver clear key (by linux)
**  \main\maintrunk.MT5921\20 2008-05-22 19:45:21 GMT MTK01088
**  move the mib to connection setting structure, adjust the code not to clear mib for privacy initialize
**  \main\maintrunk.MT5921\19 2008-04-01 20:31:10 GMT mtk01088
**  Not clear the QoS and antenna bit at wlan table while remove key
**  \main\maintrunk.MT5921\18 2008-03-31 13:23:43 GMT mtk01088
**  fixed the WPA-None Tx/Rx mic key issue
**  \main\maintrunk.MT5921\17 2008-03-18 09:59:04 GMT mtk01088
**  add function to clear pmkid candidate and cache
**  \main\maintrunk.MT5921\16 2008-03-10 17:04:34 GMT mtk01088
**  While remove transmit key, use bit 30 as check, not use address
**  \main\maintrunk.MT5921\15 2008-03-05 09:28:34 GMT mtk01088
**  move the code location for security connection setting
**  \main\maintrunk.MT5921\14 2008-03-03 18:11:51 GMT mtk01088
**  reset only the sec related variable at connecting setting
**  \main\maintrunk.MT5921\13 2008-03-03 16:31:09 GMT mtk01088
**  reset to default setting while oid reloaddefault
**  \main\maintrunk.MT5921\12 2008-02-29 15:22:51 GMT mtk01088
**  add oid reload default support
**  delete non-used code
**  \main\maintrunk.MT5921\11 2008-02-01 09:36:54 GMT mtk01385
**  1. Fix WinCE 4.2 compiling error.
**  \main\maintrunk.MT5921\10 2007-12-26 20:24:53 GMT mtk01088
**  Do the pmkid candicate after add group key
**  \main\maintrunk.MT5921\9 2007-11-20 10:52:57 GMT mtk01088
**  keep the T1X R1X even at clear key
**  \main\maintrunk.MT5921\8 2007-11-08 20:23:36 GMT mtk01088
**  add the support for tx fragment update info function
**  \main\maintrunk.MT5921\7 2007-11-06 20:23:15 GMT mtk01088
**  fixed the error
** Revision 1.7  2007/07/17 12:57:30  MTK01088
** add function for default key exist and remove key
**
** Revision 1.6  2007/07/16 02:43:03  MTK01088
** remove non-used code
** add check whether the handshake is needed function
**
** Revision 1.5  2007/07/09 06:38:31  MTK01088
** update the function related with security module
**
** Revision 1.4  2007/07/04 10:16:24  MTK01088
** add function
**
** Revision 1.3  2007/07/03 08:24:53  MTK01088
** left the protocol layer function for security module here at mgmt directory
**
** Revision 1.2  2007/06/27 12:37:57  MTK01088
** add the function for sec fsm transition wlan table control
**
** Revision 1.1  2007/06/27 06:27:49  MTK01088
** add the privacy related file
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
privacyInitialize (
    IN P_ADAPTER_T prAdapter
    )
{
    DEBUGFUNC("privacyInitialize");

    ASSERT(prAdapter);
    
#if CFG_TX_FRAGMENT
    txFragInfoUpdateForPrivacy (prAdapter, FALSE, FALSE);
#endif
    
    prAdapter->rConnSettings.rMib.dot11TranmitKeyAvailable = FALSE;

    prAdapter->rBssInfo.u4RsnSelectedGroupCipher = 0;
    prAdapter->rBssInfo.u4RsnSelectedPairwiseCipher = 0;
    prAdapter->rBssInfo.u4RsnSelectedAKMSuite = 0;

#if SUPPORT_WAPI
    /* Todo:: Clear the wapimode if the oid set wapi is supported */
    /* Flag to info this assoc info is set */
    if (prAdapter->fgUseWapi) {
        prAdapter->prGlueInfo->u2WapiAssocInfoIESz = 0;
        prAdapter->rSecInfo.fgBlockTxTraffic = FALSE;
        prAdapter->rSecInfo.fgBlockRxTraffic = FALSE;
    }
#endif

    nicPrivacyInitialize(prAdapter);
}   /* privacyInitialize */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to initialize the pmkid 
*        parameters.
*
* \param[in] prAdapter Pointer to the adapter structure
*
* \retval NONE
*/
/*----------------------------------------------------------------------------*/
VOID
privacyClearPmkid (
    IN P_ADAPTER_T prAdapter
    )
{
    P_SEC_INFO_T prSecInfo;

    DEBUGFUNC("privacyClearPmkid");

    ASSERT(prAdapter);
    
    prSecInfo = &prAdapter->rSecInfo;
    ASSERT(prSecInfo);

    prSecInfo->u4PmkidCandicateCount = 0;
    prSecInfo->u4PmkidCacheCount = 0;
    kalMemZero((PVOID)prSecInfo->arPmkidCandicate, sizeof(PMKID_CANDICATE_T) * CFG_MAX_PMKID_CACHE);
    kalMemZero((PVOID)prSecInfo->arPmkidCache, sizeof(PMKID_ENTRY_T) * CFG_MAX_PMKID_CACHE);
}


/*----------------------------------------------------------------------------*/
/*!
* \brief Whether WPA, or WPA2 but not WPA-None is enabled.
*
* \param[in] prAdapter Pointer to the adapter structure
*
* \retval BOOLEAN
*/
/*----------------------------------------------------------------------------*/
BOOLEAN
privacyRsnKeyHandshakeEnabled (
    IN P_ADAPTER_T prAdapter
    )
{
    P_CONNECTION_SETTINGS_T prConnSettings;
    
    ASSERT(prAdapter);

    prConnSettings = &prAdapter->rConnSettings;

    ASSERT(prConnSettings);
    
    ASSERT(prConnSettings->eEncStatus < ENUM_ENCRYPTION3_KEY_ABSENT);

    if (prConnSettings->eEncStatus == ENUM_ENCRYPTION_DISABLED) {
        return FALSE;
    }

    ASSERT(prConnSettings->eAuthMode < AUTH_MODE_NUM);
    if ((prConnSettings->eAuthMode >= AUTH_MODE_WPA) &&
        (prConnSettings->eAuthMode != AUTH_MODE_WPA_NONE)) {
        return TRUE;
    }

    return FALSE;
} /* privacyRsnKeyHandshakeEnabled */


/*----------------------------------------------------------------------------*/
/*!
* \brief Return whether the transmit key alread installed.
*
* \param[in] prAdapter Pointer to the adapter structure
*
* \retval TRUE Default key or Transmit key installed
*         FALSE Default key or Transmit key not installed
* 
* \note: 
*/
/*----------------------------------------------------------------------------*/
BOOLEAN
privacyTransmitKeyExist (
    IN P_ADAPTER_T prAdapter
    )
{

    ASSERT(prAdapter);

    if (prAdapter->rConnSettings.rMib.dot11TranmitKeyAvailable){
        return TRUE;
    }
    else { 
        return FALSE;
    }
} /* privacyTransmitKeyExist */


/*----------------------------------------------------------------------------*/
/*!
* \brief Whether 802.11 privacy is enabled.
*
* \param[in] prAdapter Pointer to the adapter structure
*
* \retval BOOLEAN
*/
/*----------------------------------------------------------------------------*/
BOOLEAN
privacyEnabled (
    IN P_ADAPTER_T prAdapter
    )
{
    DEBUGFUNC("privacyEnabled");

    ASSERT(prAdapter);
    ASSERT(prAdapter->rConnSettings.eEncStatus < ENUM_ENCRYPTION3_KEY_ABSENT);

    switch (prAdapter->rConnSettings.eEncStatus) {
        case ENUM_ENCRYPTION_DISABLED:
            return FALSE;
        case ENUM_ENCRYPTION1_ENABLED:
        case ENUM_ENCRYPTION2_ENABLED:
        case ENUM_ENCRYPTION3_ENABLED:
            return TRUE;
        default:
            DBGLOG(RSN, ERROR, ("Unknown encryption setting %d\n",
                prAdapter->rConnSettings.eEncStatus));
            break;
    }
    return FALSE;
} /* privacyEnabled */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine will enable/disable the cipher suite
*
* \param[in] prAdapter Pointer to the adapter object data area.
* \param[in] u4CipherSuitesFlags flag for cipher suite
*
* \retval none
*/
/*----------------------------------------------------------------------------*/
VOID
privacySetCipherSuite (
    IN P_ADAPTER_T prAdapter,
    IN UINT_32     u4CipherSuitesFlags
    )
{
    UINT_32 i;
    P_DOT11_RSNA_CONFIG_PAIRWISE_CIPHERS_ENTRY prEntry;
    P_IEEE_802_11_MIB_T prMib;

    ASSERT(prAdapter);

    prMib = &prAdapter->rConnSettings.rMib;

    ASSERT(prMib);
    
    if (u4CipherSuitesFlags == CIPHER_FLAG_NONE) {
        /* Disable all the pairwise cipher suites. */
        for (i = 0; i < MAX_NUM_SUPPORTED_CIPHER_SUITES; i++) {
            prMib->dot11RSNAConfigPairwiseCiphersTable[i].dot11RSNAConfigPairwiseCipherEnabled =
                FALSE;
        }

        /* Update the group cipher suite. */
        prMib->dot11RSNAConfigGroupCipher = WPA_CIPHER_SUITE_NONE;

        return;
    }

    for (i = 0; i < MAX_NUM_SUPPORTED_CIPHER_SUITES; i++) {
        prEntry = &prMib->dot11RSNAConfigPairwiseCiphersTable[i];

        switch (prEntry->dot11RSNAConfigPairwiseCipher) {
            case WPA_CIPHER_SUITE_WEP40:
            case RSN_CIPHER_SUITE_WEP40:
                 if (u4CipherSuitesFlags & CIPHER_FLAG_WEP40) {
                     prEntry->dot11RSNAConfigPairwiseCipherEnabled = TRUE;
                 }
                 else {
                     prEntry->dot11RSNAConfigPairwiseCipherEnabled = FALSE;
                 }
                 break;

            case WPA_CIPHER_SUITE_TKIP:
            case RSN_CIPHER_SUITE_TKIP:
                 if (u4CipherSuitesFlags & CIPHER_FLAG_TKIP) {
                     prEntry->dot11RSNAConfigPairwiseCipherEnabled = TRUE;
                 }
                 else {
                     prEntry->dot11RSNAConfigPairwiseCipherEnabled = FALSE;
                 }
                 break;

            case WPA_CIPHER_SUITE_CCMP:
            case RSN_CIPHER_SUITE_CCMP:
                 if (u4CipherSuitesFlags & CIPHER_FLAG_CCMP) {
                     prEntry->dot11RSNAConfigPairwiseCipherEnabled = TRUE;
                 }
                 else {
                     prEntry->dot11RSNAConfigPairwiseCipherEnabled = FALSE;
                 }
                 break;

            case WPA_CIPHER_SUITE_WEP104:
            case RSN_CIPHER_SUITE_WEP104:
                 if (u4CipherSuitesFlags & CIPHER_FLAG_WEP104) {
                     prEntry->dot11RSNAConfigPairwiseCipherEnabled = TRUE;
                 }
                 else {
                     prEntry->dot11RSNAConfigPairwiseCipherEnabled = FALSE;
                 }
                 break;
            default:
                 break;
        }
    }

    /* Update the group cipher suite. */
    if (rsnSearchSupportedCipher(prAdapter, WPA_CIPHER_SUITE_CCMP, &i)) {
        prMib->dot11RSNAConfigGroupCipher = WPA_CIPHER_SUITE_CCMP;
    }
    else if (rsnSearchSupportedCipher(prAdapter, WPA_CIPHER_SUITE_TKIP, &i)) {
        prMib->dot11RSNAConfigGroupCipher = WPA_CIPHER_SUITE_TKIP;
    }
    else if (rsnSearchSupportedCipher(prAdapter, WPA_CIPHER_SUITE_WEP104, &i)) {
        prMib->dot11RSNAConfigGroupCipher = WPA_CIPHER_SUITE_WEP104;
    }
    else if (rsnSearchSupportedCipher(prAdapter, WPA_CIPHER_SUITE_WEP40, &i)) {
        prMib->dot11RSNAConfigGroupCipher = WPA_CIPHER_SUITE_WEP40;
    }
    else {
        prMib->dot11RSNAConfigGroupCipher = WPA_CIPHER_SUITE_NONE;
    }

}   /* privacySetCipherSuite */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to reload the available default
*        WEP keys from the permanent storage.
*
* \param[in] prAdapter Pointer to the adapter structure
*
* \retval none
*/
/*----------------------------------------------------------------------------*/
VOID
privacyReloadDefaultWepKeys (
    IN P_ADAPTER_T prAdapter
    )
{
    DEBUGFUNC("privacyReloadDefaultWepKeys");

    DBGLOG(MGT, INFO, ("\n"));

    ASSERT(prAdapter);

    privacySetCipherSuite(prAdapter, CIPHER_FLAG_NONE);

    prAdapter->rConnSettings.eAuthMode = AUTH_MODE_OPEN;
    prAdapter->rConnSettings.eEncStatus = ENUM_ENCRYPTION_DISABLED;

    /* Clear Driver key and HW wlan table content */
    privacyInitialize(prAdapter);
    
}   /* privacyReloadDefaultWepKeys */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called by arbiter set the key from oid to HW.
*
* \param[in] prAdapter Pointer to the adapter structure
* \param[in] prNewKey The oid add key setting structure
*
* \retval none
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
privacySetKeyEntry (
    IN P_ADAPTER_T          prAdapter,
    IN P_PARAM_KEY_T        prNewKey
    )
{
    UINT_8                  ucKeyId;
    PUINT_8                 pucBssid;
    UINT_8                  ucCipher = 0;
    WLAN_STATUS             status = WLAN_STATUS_SUCCESS;
    UINT_8                  ucTxMicOffset;
    UINT_8                  ucRxMicOffset;
    BOOLEAN                 fgResult;
    P_CONNECTION_SETTINGS_T prConnSettings;     
    P_SEC_INFO_T            prSecInfo;

    DEBUGFUNC("privacySetKeyEntry");

    ASSERT(prAdapter);
    ASSERT(prNewKey);

    prConnSettings = &prAdapter->rConnSettings;

    prSecInfo = &prAdapter->rSecInfo;

    ucKeyId = (UCHAR)(prNewKey->u4KeyIndex & 0x000000ff);

    ASSERT(ucKeyId < MAX_KEY_NUM);

    if (prConnSettings->eAuthMode == AUTH_MODE_WPA_NONE) {
        ucTxMicOffset = MIC_RX_KEY_OFFSET;
        ucRxMicOffset = MIC_RX_KEY_OFFSET;
    }
    else {
        if (prNewKey->u4KeyIndex & IS_AUTHENTICATOR) {
            /* authenticator */
            ucTxMicOffset = MIC_RX_KEY_OFFSET;
            ucRxMicOffset = MIC_TX_KEY_OFFSET;
        }
        else {
            /* supplicant */
            ucTxMicOffset = MIC_TX_KEY_OFFSET;
            ucRxMicOffset = MIC_RX_KEY_OFFSET;
        }
    }

    /* Bit 31: 1 = Transmit key, 0 = non-transmit key
       Bit 30: 1 = Pairwise key, 0 = Group key */
    pucBssid = (PUINT_8)prNewKey->arBSSID;
    switch (prNewKey->u4KeyIndex & BITS(30,31)) {
    case 0x00000000:   /* 00, Group key that is receive only */
    case IS_TRANSMIT_KEY :      /* 10, Group key that can be used to transmit */
         if (((pucBssid[0] == 0xff) && (pucBssid[1] == 0xff) && 
              (pucBssid[2] == 0xff) && (pucBssid[3] == 0xff) && 
              (pucBssid[4] == 0xff) && (pucBssid[5] == 0xff)) ||
             (EQUAL_MAC_ADDR(pucBssid, prAdapter->rBssInfo.aucBSSID))) {
            switch (prConnSettings->eAuthMode) {
                /* Legacy only supports WEP */
            case AUTH_MODE_OPEN:
            case AUTH_MODE_SHARED:
            case AUTH_MODE_AUTO_SWITCH:
                if (prNewKey->u4KeyLength == WEP_40_LEN) {
                    ucCipher = CIPHER_SUITE_WEP40;
                }
                else if (prNewKey->u4KeyLength == WEP_104_LEN) {
                    ucCipher = CIPHER_SUITE_WEP104;
                }
                else if (prNewKey->u4KeyLength == LEGACY_KEY_MAX_LEN) {
                    ucCipher = CIPHER_SUITE_WEP128;
                }
                break;

            case AUTH_MODE_WPA:
            case AUTH_MODE_WPA_PSK:
            case AUTH_MODE_WPA2:
            case AUTH_MODE_WPA2_PSK:
                ucCipher =
                    GET_SELECTOR_TYPE(prAdapter->rBssInfo.u4RsnSelectedGroupCipher);
                break;

            /* WPA None Set Keys without handshaking */
            case AUTH_MODE_WPA_NONE:
                if (prAdapter->rConnSettings.eEncStatus == ENUM_ENCRYPTION2_ENABLED) {
                    ucCipher = CIPHER_SUITE_TKIP;
                }
                else if (prAdapter->rConnSettings.eEncStatus == ENUM_ENCRYPTION3_ENABLED) {
                    ucCipher = CIPHER_SUITE_CCMP;
                }
                else {
                    if (prNewKey->u4KeyLength == CCMP_KEY_LEN) {
                        ucCipher = CIPHER_SUITE_CCMP;
                    }
                    else if (prNewKey->u4KeyLength == TKIP_KEY_LEN) {
                        ucCipher = CIPHER_SUITE_TKIP;
                    }
                }
                break;

            default:
                DBGLOG(RSN, ERROR, ("Unknown authentication mode %d\n", 
                    prConnSettings->eAuthMode));
                ucCipher = CIPHER_SUITE_NONE;
                break;
            }
            
            fgResult = nicPrivacySetKeyEntry(prAdapter,
                                 (prNewKey->u4KeyIndex & IS_TRANSMIT_KEY) ? TRUE : FALSE,
                                  pucBssid,
                                 (UINT_8)ucKeyId,
                                  prNewKey->aucKeyMaterial,
                                 (UINT_8)prNewKey->u4KeyLength,
                                  ucCipher,
                                  ucTxMicOffset,
                                  ucRxMicOffset);
            if (fgResult == FALSE) {
                DBGLOG(RSN, WARN, ("Add key return resource issue\n"));
                return WLAN_STATUS_RESOURCES;
            }

            /* Check bit 31 if default group key used to transmit */
            if (prNewKey->u4KeyIndex & IS_TRANSMIT_KEY) {
                /* Set default Tx key index */
                prConnSettings->rMib.dot11WEPDefaultKeyID = (UINT_8)ucKeyId;
                prConnSettings->rMib.dot11TranmitKeyAvailable = TRUE;
#if CFG_TX_FRAGMENT
                {
                BOOLEAN fgIsTkipCipher = FALSE;
                if (ucCipher == CIPHER_SUITE_TKIP){
                    fgIsTkipCipher = TRUE;
                }
                txFragInfoUpdateForPrivacy(prAdapter, TRUE, fgIsTkipCipher);
                }
#endif
            }

            /* If the authentication mode is WPA2 or WPA2PSK, and after
               the group key is plumbed to driver, then we set the
               indication PMKID flag */
            if (prConnSettings->eAuthMode == AUTH_MODE_WPA2) {
                  ARB_CANCEL_TIMER(prAdapter, prSecInfo->rPreauthenticationTimer);
                  ARB_SET_TIMER(prAdapter,
                      prSecInfo->rPreauthenticationTimer,
                  SEC_TO_MSEC(WAIT_TIME_IND_PMKID_CANDICATE_SEC));
             }
         }
         break;

    case BIT(30): /* 01, Illegal combination */
         status = WLAN_STATUS_INVALID_DATA;
         break;

    case BITS(30,31): /* 11, Pairwise key that can be used to transmit */
        if ((ucKeyId != 0) ||
            ((pucBssid[0] == 0xff) && (pucBssid[1] == 0xff) && (pucBssid[2] == 0xff) &&
             (pucBssid[3] == 0xff) && (pucBssid[4] == 0xff) && (pucBssid[5] == 0xff))) {
            status = WLAN_STATUS_INVALID_DATA;
        }
        else {
            if (prConnSettings->eAuthMode < AUTH_MODE_WPA) {
                if (prNewKey->u4KeyLength == WEP_40_LEN) {
                    ucCipher = CIPHER_SUITE_WEP40;
                }
                else if (prNewKey->u4KeyLength == WEP_104_LEN) {
                    ucCipher = CIPHER_SUITE_WEP104;
                }
                else if (prNewKey->u4KeyLength == LEGACY_KEY_MAX_LEN) {
                    ucCipher = CIPHER_SUITE_WEP128;
                }
            }
            else {
                ucCipher =
                    GET_SELECTOR_TYPE(prAdapter->rBssInfo.u4RsnSelectedPairwiseCipher);
            }

            /* Set default Tx key index */
            if (EQUAL_MAC_ADDR(pucBssid, prAdapter->rBssInfo.aucBSSID)) {
                prConnSettings->rMib.dot11WEPDefaultKeyID = (UINT_8)ucKeyId;
                prConnSettings->rMib.dot11TranmitKeyAvailable = TRUE;
            }

            if (secFsmRunEventPTKInstalled(prAdapter, 
                                           pucBssid,
                                           prNewKey->aucKeyMaterial,
                                          (UINT_8)prNewKey->u4KeyLength,
                                           ucCipher,
                                           ucTxMicOffset,
                                           ucRxMicOffset) == FALSE) {
                /* for key handshake, set to template entry */
                } 
#if CFG_TX_FRAGMENT
            {
            BOOLEAN fgIsTkipCipher = FALSE;
            if (ucCipher == CIPHER_SUITE_TKIP){
                fgIsTkipCipher = TRUE;
            }
            txFragInfoUpdateForPrivacy(prAdapter, TRUE, fgIsTkipCipher);
            }
#endif    
        }
        break;
    default:
        break;
    }

    if (status == WLAN_STATUS_SUCCESS) {
        if (prNewKey->u4KeyIndex & IS_UNICAST_KEY) {
            /* Reset TSC */
        }
    } /* if() */

    return status;
}


/*----------------------------------------------------------------------------*/
/*!
* \brief This function clear key
*
* \param[in] prAdapter Pointer to the adapter object data area.
* \param[in] fgPairwise TRUE, pairwise key. FALSE, group key
* \param[in] pucBssid BSSID
* \param[in] ucKeyId Key ID
*
* \retval none
*/
/*----------------------------------------------------------------------------*/
VOID
privacyClearKeyEntry (
    IN P_ADAPTER_T          prAdapter,
    IN BOOLEAN              fgPairwise,
    IN PUINT_8              pucBssid,
    IN UINT_8               ucKeyId
    )
{
    UINT_8                  aucKeyMaterial[MAX_KEY_LEN];
    UINT_8                  ucEntryIndex;
    P_WLAN_ENTRY_CTRL_T     prWlanCtrl;
    P_WT_CTRL_STRUC_T       prCtrl;

    DEBUGFUNC("privacySetIpcKeyEntry");

    ASSERT(prAdapter);
    ASSERT(ucKeyId < MAX_KEY_NUM);

    kalMemZero((PVOID)&aucKeyMaterial[0], MAX_KEY_LEN);
    
    if (fgPairwise /* && (EQUAL_MAC_ADDR(pucBssid, prAdapter->rBssInfo.aucBSSID))*/) {
        prAdapter->rConnSettings.rMib.dot11WEPDefaultKeyID = 0;
        prAdapter->rConnSettings.rMib.dot11TranmitKeyAvailable = FALSE;
    }

    if (nicPrivacyMatchForEntry(prAdapter,
                            pucBssid,
                            ucKeyId,
                            &ucEntryIndex)) {
        UINT_8              ucMac[6], ucMuar, ucRate1, ucRate2, ucRate3, ucRate4;                    
        BOOLEAN             fgUsed = FALSE, fgT1X= FALSE, fgR1X = FALSE, fgQoS = FALSE, fgAntenna = FALSE;
        P_STA_RECORD_T prSta;

        prWlanCtrl = &prAdapter->arWlanCtrl[ucEntryIndex];
        if (fgPairwise) {
            fgUsed = prWlanCtrl->fgUsed;
        }

        prCtrl = &prWlanCtrl->rCtrl;
        ASSERT(prCtrl);

        fgT1X = prCtrl->fgT1X;
        fgR1X = prCtrl->fgR1X;
        fgQoS = prCtrl->fgQoS;
        ucMuar = prCtrl->ucMuar;
        ucRate1 = prCtrl->ucRate1;
        ucRate2 = prCtrl->ucRate2;
        ucRate3 = prCtrl->ucRate3;
        ucRate4 = prCtrl->ucRate4;
        fgAntenna = prCtrl->fgAntenna;

        prSta = prAdapter->arWlanCtrl[ucEntryIndex].prSta;

        kalMemCopy(&ucMac[0], (PVOID)prAdapter->arWlanCtrl[ucEntryIndex].rSWKey.aucAddr, MAC_ADDR_LEN);
        kalMemZero((PVOID)&prAdapter->arWlanCtrl[ucEntryIndex], sizeof(WLAN_ENTRY_CTRL_T));
        kalMemCopy(prAdapter->arWlanCtrl[ucEntryIndex].rSWKey.aucAddr, (PVOID)&ucMac[0], MAC_ADDR_LEN);

        prAdapter->arWlanCtrl[ucEntryIndex].prSta = prSta;

        if (fgPairwise) {
            prWlanCtrl->fgUsed = fgUsed;
        }
        prCtrl->fgT1X = fgT1X;
        prCtrl->fgR1X = fgR1X;
        prCtrl->fgQoS = fgQoS;
        prCtrl->fgAntenna = fgAntenna;
        prCtrl->ucMuar = ucMuar;
        prCtrl->ucRate1 = ucRate1;
        prCtrl->ucRate2 = ucRate2;
        prCtrl->ucRate3 = ucRate3;
        prCtrl->ucRate4 = ucRate4;
        
        nicPrivacyDumpWlanTable(prAdapter, ucEntryIndex);

        /* Set key into H/W key table */
        if (!halWlanTableAccess(prAdapter, 
                           (PVOID)prWlanCtrl,
                           ucEntryIndex,
                           3)) {
            DBGLOG(RSN, TRACE, ("Fail to clear key !\n"));
        }
    }
    else {
        DBGLOG(RSN, TRACE, ("No matched Wlan Table to remove!!\n"));
    }

    return;
} /* privacyClearKeyEntry */

