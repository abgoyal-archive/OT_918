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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/hal_wlantable.c#2 $
*/

/*! \file   "hal_wlantable.c"
    \brief  Put all the wlan table access related function for hal here

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
** $Log: hal_wlantable.c $
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\18 2009-08-18 22:56:39 GMT mtk01090
**  Add Linux SDIO (with mmc core) support.
**  Add Linux 2.6.21, 2.6.25, 2.6.26.
**  Fix compile warning in Linux.
**  \main\maintrunk.MT5921\17 2008-12-01 18:22:18 GMT mtk01088
**  fixed the lint "possible using null pointer" warning
**  \main\maintrunk.MT5921\16 2008-10-29 10:58:30 GMT mtk01088
**  update the code for lint issue
**  \main\maintrunk.MT5921\15 2008-09-17 11:23:56 GMT mtk01088
**  remove non-used code
**  \main\maintrunk.MT5921\14 2008-09-01 17:02:56 GMT mtk01088
**  use the define instead of the variable, add assert check
**  \main\maintrunk.MT5921\13 2008-07-14 16:13:36 GMT mtk01088
**  fixed the prefast warning
**  \main\maintrunk.MT5921\12 2008-04-22 23:02:26 GMT mtk01084
**  modify port access function prototype
**  \main\maintrunk.MT5921\11 2008-03-24 09:14:06 GMT mtk01088
**  The wlan table init function use mode 0
**  \main\maintrunk.MT5921\10 2008-03-23 09:49:35 GMT mtk01088
**  adjust the wlan table busy check function
**  \main\maintrunk.MT5921\9 2008-03-21 20:46:47 GMT mtk01088
**  use loop to check the wlan table busy issue
**  \main\maintrunk.MT5921\8 2008-03-20 12:06:15 GMT mtk01084
**  remove un-used line
**  \main\maintrunk.MT5921\7 2008-02-29 15:33:38 GMT mtk01088
**  update the sw variable for sw port control, and not to set to HW wlan table
**  \main\maintrunk.MT5921\6 2008-02-29 13:24:49 GMT mtk01088
**  fixed type error
**  \main\maintrunk.MT5921\5 2008-02-01 10:43:28 GMT mtk01385
**  1. Fix WinCE 4.2 compiling error.
**  \main\maintrunk.MT5921\4 2007-11-06 20:32:08 GMT mtk01088
**  use new macro to check the HW status
** Revision 1.5  2007/07/16 02:47:57  MTK01088
** delete non-used code
**
** Revision 1.4  2007/07/09 06:43:02  MTK01088
** update the function related with wlan table operation
**
** Revision 1.3  2007/07/04 10:18:35  MTK01088
** update wlan table function
**
** Revision 1.2  2007/07/03 08:29:39  MTK01088
** rename the function
** add some code for access wlan table
**
** Revision 1.1  2007/06/28 12:52:15  MTK01088
** add the wlan table function to hal_wlantable.c
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
*
* \brief This routine is called to initialize the wlan table
*        The index need to be set before use it
*
* \param[in] prAdapter  Pointer to the Adapter structure
*
* \return none
*
* \note
*/
/*----------------------------------------------------------------------------*/
VOID
halWlanTableInit (
    IN  P_ADAPTER_T          prAdapter
    )
{
    WLAN_ENTRY_CTRL_T        rWTEntry;
    UINT_8                   i;

    DEBUGFUNC("halWlanTableInit");

    ASSERT(prAdapter);
    
    kalMemZero((PVOID)&rWTEntry, sizeof(WLAN_ENTRY_CTRL_T));

    for (i = 0; i < WLAN_TABLE_SIZE; i++) {
        if (!halWlanTableAccess(prAdapter, (PVOID)&rWTEntry, i, HWTDR_UPDATE_MODE_0)) {
            DBGLOG(RSN, TRACE, ("Wlan Table Initial failed\n"));
        }
    }

}/* halWlanTableInit */


/*----------------------------------------------------------------------------*/
/*!
* \brief used to check the wlan table can be access by Driver,
*        CIR WT_BUSY bit is used to indicate this.
*
* \param[in] prAdapter pointer to the Adapter handler
*
* \retval TRUE The wlan table can be access (not busy)
* \retval FALSE The HW is now occupied the wlan table
*/
/*----------------------------------------------------------------------------*/
BOOLEAN
halWlanTableBusyStatus (
    IN P_ADAPTER_T          prAdapter
    )
{
    UINT_32 u4temp, i;

    DEBUGFUNC("halWlanTableBusyStatus");

    ASSERT(prAdapter);
    
    kalUdelay(3);

    HAL_MCR_RD(prAdapter, MCR_CIR, &u4temp);

    if (WLAN_WT_IS_BUSY(u4temp)){
        for (i=0; i< 10; i++) {
            kalUdelay(3);
            HAL_MCR_RD(prAdapter, MCR_CIR, &u4temp);
            if (WLAN_WT_IS_BUSY(u4temp)){
                DBGLOG(HAL, INFO, ("Busy (%08lx)!!!!\n", u4temp));
            }
            else {
                DBGLOG(HAL, INFO, ("ok (%08lx)!!!!\n", u4temp));
                break;
            }
        }
        if (i==10) {
            DBGLOG(HAL, TRACE, ("Wlan Table is busy!!!!\n"));
            return FALSE;
        }
    }

    return TRUE;
} /* halWlanTableBusyStatus */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used for trasform the driver storage setting to
*        spec defined HW wlan table structure to add a WLAN entry to H/W.
*        It will return entry add request is success or fail
*
* \param[in] prAdapter Pointer to the Adapter structure
* \param[in] pvWlanCtrl Pointer to the driver defined structure 
* \param[in] ucEntryIndex the entry to be access
* \param[in] ucMode the entry update mode to be use
*
* retval TRUE The entry have add to the WLAN Table
* retval FALSE No entry left for add, and for debug, verify the content
*
*  \note
*/
/*----------------------------------------------------------------------------*/
BOOLEAN
halWlanTableAccess (
    IN  P_ADAPTER_T         prAdapter,
    IN  PVOID               pvWlanCtrl,
    IN  UCHAR               ucEntryIndex,
    IN  UCHAR               ucMode
    )
{
    HW_WLAN_TABLE_T         rWKey;
    P_WLAN_ENTRY_CTRL_T     prWlanCtrl;
    P_SW_KEY_STRUC_T        prSwKey;
    P_WT_CTRL_STRUC_T       prCtrl;
    UINT_32                 u4Ctrl = 0;
    UINT_8                  ucUpdateLen = 0;
    BOOLEAN                 fgResult = TRUE;

    DEBUGFUNC("halWlanTableAccess");

    ASSERT(prAdapter);
    ASSERT(pvWlanCtrl);
    
    if (pvWlanCtrl == NULL ||
        ucEntryIndex > WLAN_TABLE_SIZE || /* max wlan table entry */
        ucMode > HWTDR_UPDATE_MODE_3 /* max wlan table update mode */) {
        ASSERT(FALSE);
    }

    prWlanCtrl = (P_WLAN_ENTRY_CTRL_T)pvWlanCtrl;

    prSwKey = &prWlanCtrl->rSWKey;
    prCtrl = &prWlanCtrl->rCtrl;

    switch (ucMode) {
    case HWTDR_UPDATE_MODE_0:
        ucUpdateLen = HWTDR_UPDATE_MODE_0_SZ;
        break;
    case HWTDR_UPDATE_MODE_1:
        ucUpdateLen = HWTDR_UPDATE_MODE_1_SZ;
        break;
    case HWTDR_UPDATE_MODE_2:
        ucUpdateLen = HWTDR_UPDATE_MODE_2_SZ;
        break;
    case HWTDR_UPDATE_MODE_3:
        ucUpdateLen = HWTDR_UPDATE_MODE_3_SZ;
        break;
    default :
        break;
    }

    ASSERT(prSwKey && prCtrl);

    u4Ctrl = u4Ctrl | (ucEntryIndex & MASK_HWTDR_TINDEX) | ((ucMode & BITS(0,1)) << HWTDR_MODE_OFFSET);
    u4Ctrl = u4Ctrl | (prCtrl->fgTV << HWTDR_TV_OFFSET);
    u4Ctrl = u4Ctrl | (prCtrl->fgTKV << HWTDR_TKV_OFFSET);
#if 1 /* Always use SW Port Control */
    u4Ctrl = u4Ctrl | (0 << HWTDR_T1X_OFFSET);
#endif
    u4Ctrl = u4Ctrl | (prCtrl->fgRV << HWTDR_RV_OFFSET);
    u4Ctrl = u4Ctrl | (prCtrl->fgRKV << HWTDR_RKV_OFFSET);
    u4Ctrl = u4Ctrl | ((prSwKey->ucRCA1 & BITS(0,1)) << HWTDR_RCA1_OFFSET);
    u4Ctrl = u4Ctrl | (prSwKey->fgRCA2 << HWTDR_RCA2_OFFSET);
    u4Ctrl = u4Ctrl | (prSwKey->fgRCID << HWTDR_RCID_OFFSET);
#if 1 /* Always use SW Port Control */
    u4Ctrl = u4Ctrl | (0 << HWTDR_R1X_OFFSET);
#endif
    u4Ctrl = u4Ctrl | (prCtrl->fgQoS << HWTDR_Q_OFFSET);
    u4Ctrl = u4Ctrl | (prCtrl->fgAntenna << HWTDR_A_OFFSET);
    u4Ctrl = u4Ctrl | (prSwKey->fgIKV << HWTDR_IKV_OFFSET);
    u4Ctrl = u4Ctrl | ((prSwKey->ucCipher & BITS(0,3)) << HWTDR_CIPHER_OFFSET);
    u4Ctrl = u4Ctrl | ((prSwKey->ucKeyId & BITS(0,1)) << HWTDR_KID_OFFSET);

    rWKey.u4Ctrl = u4Ctrl;

    if (ucMode >= HWTDR_UPDATE_MODE_1) {
        rWKey.u4Rate = prCtrl->ucRate1 |
                      (prCtrl->ucRate2 << 6) |
                      (prCtrl->ucRate3 << 12) |
                      (prCtrl->ucRate4 << 18);
    }

    if (ucMode >= HWTDR_UPDATE_MODE_2) {
        rWKey.ucMUAR_ID = (0 & BITS(0,5));
        rWKey.ucReserved = 0;
        kalMemCopy(rWKey.aucAddr, prSwKey->aucAddr, MAC_ADDR_LEN);
    }
    if (ucMode == HWTDR_UPDATE_MODE_3) {
        kalMemCopy(&rWKey.aucKey[0], prSwKey->aucKeyMaterial, TKIP_KEY_LEN);
    }

    if (halWlanTableBusyStatus(prAdapter)== FALSE) {
        ASSERT(FALSE);
    }

    HAL_PORT_WR(prAdapter,
                MCR_HWTDR,
               (UINT_16)ucUpdateLen,
               (PUCHAR)&rWKey,
               (UINT_16)ucUpdateLen);

    if (!fgResult) {
        goto BUS_ERROR;
    }

    if (halWlanTableBusyStatus(prAdapter)== FALSE) {
        ASSERT(FALSE);
    }

    if (halWlanTableVerify(prAdapter,
                (PUINT_8)&rWKey,
                ucEntryIndex,
                ucUpdateLen) == FALSE){
        goto BUS_ERROR;
    }

    return TRUE;
BUS_ERROR:
    DBGLOG(HAL, ERROR, ("Write bus error\n"));

    return FALSE;
} /* halWlanTableAccess */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used for verify the WLAN Table.
*
* \param[in] prAdapter Pointer to the Adapter structure
* \param[in] prWKey Pointer to the wlan entry structure
* \param[in] ucEntryIndex Specific entry for 0 ~ 12
* \param[in] ucLen The compared len for entry
*
* \retval TRUE The compare ok
* \retval FALSE The compare fail
*
*  \note
*/
/*----------------------------------------------------------------------------*/
BOOLEAN
halWlanTableVerify (
    IN  P_ADAPTER_T         prAdapter,
    IN  PUINT_8             pucWKey,
    IN  UCHAR               ucEntryIndex,
    IN  UCHAR               ucLen
    )
{
    UINT_32         u4Value = 0;
    UINT_8          ucTmpWlanEntry[HWTDR_UPDATE_MODE_3_SZ];
    BOOLEAN         fgResult = TRUE;

    DEBUGFUNC("halWlanTableVerify");

    ASSERT(prAdapter);
    ASSERT(pucWKey);
    
    if (ucEntryIndex > WLAN_TABLE_SIZE /* max wlan table entry */ ||
        ucLen > HWTDR_UPDATE_MODE_3_SZ /* max wlan table entry len */) {
        ASSERT(FALSE);
    }

    u4Value = ucEntryIndex;
    u4Value |= HWTCR_W_RMODE;

    HAL_MCR_WR(prAdapter, MCR_HWTCR, u4Value);

    HAL_PORT_RD(prAdapter, MCR_HWTDR, ucLen,
                (PUCHAR)&ucTmpWlanEntry[0], ucLen);

    if (!fgResult) {
        return FALSE;
    }

    if ((kalMemCmp(&pucWKey[1], &ucTmpWlanEntry[1], ucLen - 1) != 0)) {
        DBGLOG(HAL, ERROR, ("Wlan table verified fail!!\n"));
        DBGLOG_MEM8(HAL, TRACE, (PUINT_8)&pucWKey[0], ucLen);
        DBGLOG(HAL, TRACE, ("=============================================\n"));
        DBGLOG_MEM8(HAL, TRACE, (PUINT_8)&ucTmpWlanEntry[0], ucLen);
        ASSERT(FALSE);
        return FALSE;
    }
    return TRUE;

} /* halWlanTableVerify */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is used to dump the specific wlan table content.
*
* \param[in] prAdapter Pointer to the Adapter structure
* \param[in] ucEntryIndex Specific entry for 0 ~ 12
*
* \return none
*
*  \note
*/
/*----------------------------------------------------------------------------*/
VOID
halWlanTableDump(
    IN  P_ADAPTER_T         prAdapter,
    IN  UCHAR               ucEntryIndex
    )
{
    UINT_32         u4Value = 0;
#if DBG
    UINT_8          ucTmpWlanEntry[HWTDR_UPDATE_MODE_3_SZ];
#endif /* DBG */

    DEBUGFUNC("halWlanTableDump");

    ASSERT(prAdapter);
    
    if (ucEntryIndex > WLAN_TABLE_SIZE /* max wlan table entry */ ) {
        DBGLOG(HAL, WARN, ("Not support this entry index \n"));
    }

    u4Value = ucEntryIndex;
    u4Value |= HWTCR_W_RMODE;

    HAL_MCR_WR(prAdapter, MCR_HWTCR, u4Value);

    DBGLOG(RSN, WARN, ("Wlan table index %d\n", ucEntryIndex));
    DBGLOG_MEM8(TX, TRACE, (PUINT_8)&ucTmpWlanEntry[0], HWTDR_UPDATE_MODE_3_SZ);

}

