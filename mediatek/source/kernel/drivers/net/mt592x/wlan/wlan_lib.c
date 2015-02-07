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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/wlan_lib.c#2 $
*/

/*! \file   wlan_lib.c
    \brief  Internal driver stack will export the required procedures here for GLUE Layer.

    This file contains all routines which are exported from MediaTek 802.11 Wireless
    LAN driver stack to GLUE Layer.
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
** $Log: wlan_lib.c $
 *
 * 09 03 2010 enlai.chu
 * [ALPS00003550] [YuSu]WAPI feature
 * For WAPI feature
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\86 2009-09-03 11:31:39 GMT mtk01088
**  add the function for wapi
**  \main\maintrunk.MT5921\85 2009-07-06 20:15:06 GMT mtk01088
**  add a function to query now driver's wapi mode status
**  \main\maintrunk.MT5921\84 2009-06-11 17:50:04 GMT mtk01725
**  Test connectivity of GPIO_0 & GPIO_2 with INT_N in wlanISR().
**  \main\maintrunk.MT5921\83 2009-04-28 22:58:51 GMT mtk01104
**  Remove kalIndicateStatusAndComplete() in wlanAdapterStart()
**  \main\maintrunk.MT5921\82 2009-04-24 09:07:51 GMT mtk01088
**  mark the code not used at linux supplicant v0.6.7
**  \main\maintrunk.MT5921\81 2009-04-16 21:06:15 GMT mtk01084
**  prevent compile error
**  \main\maintrunk.MT5921\80 2009-04-16 20:03:07 GMT mtk01084
**  add power control on wlanStartAdapter()
**  \main\maintrunk.MT5921\79 2009-02-05 12:31:51 GMT mtk01725
**  Add a MCR R/W to workaround this issue. The workaround is only applied under RFTest mode to avoid affect normal driver.
**  \main\maintrunk.MT5921\78 2009-02-04 16:45:26 GMT mtk01725
**  Add wlanAdapterStart, wlanAdapterDestroy for META mode driver.
**  \main\maintrunk.MT5921\77 2009-01-05 09:54:04 GMT mtk01725
**  Add an OID set SLT mode. Change function name of SLT OID result query.
**  \main\maintrunk.MT5921\76 2008-12-11 16:10:15 GMT mtk01088
**  remove non-used code
**  \main\maintrunk.MT5921\75 2008-12-01 18:05:51 GMT mtk01088
**  fixed the possible using null pointer lint warning
**  \main\maintrunk.MT5921\74 2008-11-21 23:55:38 GMT mtk01725
**  \main\maintrunk.MT5921\73 2008-11-21 22:58:04 GMT mtk01725
**  \main\maintrunk.MT5921\72 2008-10-23 21:43:24 GMT mtk01088
**  add the kal interrupt done for indigo s3c2442
**  \main\maintrunk.MT5921\71 2008-09-19 11:12:08 GMT mtk01088
**  The driver have to store the SPI default setting before halt
**  \main\maintrunk.MT5921\70 2008-09-10 14:58:30 GMT mtk01088
**  add a function for card ejected
**  \main\maintrunk.MT5921\69 2008-08-25 18:28:10 GMT mtk01088
**  before unload driver, call disassociate to connected AP, to avoid the AP still keep the sta record.
**  \main\maintrunk.MT5921\68 2008-08-11 14:07:44 GMT mtk01084
**  modify driver to meeting coding rules
**  \main\maintrunk.MT5921\67 2008-08-11 09:32:32 GMT mtk01461
**  Update for Driver Review
**  \main\maintrunk.MT5921\66 2008-08-05 01:50:31 GMT mtk01461
**  Add support for linux statistics
**  \main\maintrunk.MT5921\65 2008-08-01 18:04:03 GMT mtk01088
**  This is a called by check for hang function check Card is removal,
**  If HW error occur, do Tx queue release, the reason is the Halt function is called before all Tx/Rx request is complete free and completed queued packet at wait queue
**  \main\maintrunk.MT5921\64 2008-08-01 13:28:53 GMT mtk01084
**  Prevent redundent driver assertion in driver logic when BUS is detached
**  \main\maintrunk.MT5921\63 2008-06-13 22:50:49 GMT mtk01461
**  Add comment - WLAN_STATUS_SUCCESS for wlanSendPacket()
**  \main\maintrunk.MT5921\62 2008-06-01 17:32:38 GMT mtk01084
**  remove un-used function
**  \main\maintrunk.MT5921\61 2008-06-01 14:03:18 GMT mtk01084
**  modify the caller on arbFsmRunEventIST() due to interface changed
**  \main\maintrunk.MT5921\60 2008-05-31 00:17:12 GMT mtk01104
**  Remove PTA query function
**  \main\maintrunk.MT5921\59 2008-05-30 15:48:28 GMT mtk01461
**  Add Assert()
**  \main\maintrunk.MT5921\58 2008-05-30 15:14:10 GMT mtk01084
**  modify apfnOidQueryHandlerWOHwAccess[] table
**  \main\maintrunk.MT5921\57 2008-05-29 14:12:20 GMT mtk01084
**  1. modify wlanAdapterStart() interface
**  2. modify OID handler path
**  \main\maintrunk.MT5921\56 2008-05-23 09:38:25 GMT mtk01084
**  Check ACPI state on wlanISR, and not to invoke IST when it is under D3
**  \main\maintrunk.MT5921\55 2008-05-22 10:48:19 GMT mtk01461
**  Change RCV_ERROR OID to withoutHWAccess to reduce the frequence of HW Access
**  \main\maintrunk.MT5921\54 2008-05-22 00:17:00 GMT mtk01461
**  \main\maintrunk.MT5921\53 2008-05-20 10:32:11 GMT mtk01084
**  add wlanoidQueryLowPowerSltResult() for SLT test for LP
**  \main\maintrunk.MT5921\52 2008-05-03 12:04:04 GMT mtk01461
**  Fix [WHQL] 2c_PerformanceBlast, move MediaConnect OID to Glue Layer, revise OID_GEN_LINK_SPEED to query SW variable.
**  \main\maintrunk.MT5921\51 2008-04-29 10:10:39 GMT mtk01084
**  temporarily allow rx counter update on OID query
**  \main\maintrunk.MT5921\50 2008-04-28 17:17:15 GMT mtk01084
**  remove un-necessary OID query to cause LP own-back
**  \main\maintrunk.MT5921\49 2008-04-24 22:30:40 GMT mtk01461
**  Remove wlanRxMulticast related functions
**  \main\maintrunk.MT5921\48 2008-04-24 11:58:01 GMT mtk01461
**  Fix multicast setting in Linux and add comment
**  \main\maintrunk.MT5921\47 2008-04-23 14:11:18 GMT mtk01461
**  Add QueryDesiredRateSet to WOHW access array
**  \main\maintrunk.MT5921\46 2008-04-22 16:22:25 GMT mtk01084
**  no need to own back from wlanoidQueryMediaConnectStatus()
**  \main\maintrunk.MT5921\45 2008-03-31 20:59:57 GMT mtk01461
**  Add some query OID to WOHW array
**  \main\maintrunk.MT5921\44 2008-03-31 16:42:57 GMT mtk01084
**  prevent memory free duplicately when unload
**  \main\maintrunk.MT5921\43 2008-03-28 10:39:58 GMT mtk01461
**  Add wlanoidQuerySupportedRates in WOHwAccess array
**  \main\maintrunk.MT5921\42 2008-03-26 15:31:46 GMT mtk01461
**  Rename the beacon ioctl for linux
**  \main\maintrunk.MT5921\41 2008-03-20 11:41:47 GMT mtk01084
**  modify set IP address function arguments
**  \main\maintrunk.MT5921\40 2008-03-19 15:21:13 GMT mtk01461
**  Add CFG_TCP_IP_CHKSUM_OFFLOAD flag if set to 0
**  \main\maintrunk.MT5921\39 2008-03-18 11:58:20 GMT mtk01084
**  add function description
**  \main\maintrunk.MT5921\38 2008-03-11 14:50:16 GMT mtk01461
**  Add Set Beacon Interval oid for adhoc
**  \main\maintrunk.MT5921\37 2008-02-25 15:03:07 GMT mtk01385
**  1. Add disconnect event when adapter start.
**  \main\maintrunk.MT5921\36 2008-02-21 22:49:47 GMT mtk01084
**  add related function
**  \main\maintrunk.MT5921\35 2008-02-12 23:38:23 GMT mtk01461
**  Enable Set RTS threshold oid for windows(remove #if 0)
**  \main\maintrunk.MT5921\34 2008-01-31 22:32:07 GMT mtk01385
**  1. Fix CE 4.2 compiling error.
**  \main\maintrunk.MT5921\33 2008-01-22 22:48:01 GMT mtk01084
**  invoke macros for control PM under TX path
**  \main\maintrunk.MT5921\32 2007-12-16 19:13:34 GMT mtk01084
**  check the arb state for set PM related work on stopping adapter
**  \main\maintrunk.MT5921\31 2007-11-30 16:18:57 GMT mtk01425
**  1. Modify wlanRxSetMulticastList
**  2. Add wlanRxSetBroadcast
**  \main\maintrunk.MT5921\30 2007-11-27 19:57:57 GMT mtk01084
**  invoke arbUnInit() at stopping adapter function
**  \main\maintrunk.MT5921\29 2007-11-27 11:55:34 GMT mtk01084
**  modify lines in checking element number
**  \main\maintrunk.MT5921\28 2007-11-26 21:06:33 GMT mtk01385
**  1. Add statistics functions.
**  \main\maintrunk.MT5921\27 2007-11-26 19:20:02 GMT mtk01461
**  Check OS Packet length before calling ARB Event Tx
**  \main\maintrunk.MT5921\26 2007-11-22 19:02:00 GMT mtk01425
**  1. Add wlanSetCSUMOffload for windows
**  \main\maintrunk.MT5921\25 2007-11-21 17:02:49 GMT mtk01084
**  modify for PS profile setting table
**  \main\maintrunk.MT5921\24 2007-11-15 11:17:10 GMT mtk01088
**  move the enalbe global int to reset procedure
**  \main\maintrunk.MT5921\23 2007-11-14 16:30:48 GMT mtk01084
**  not to polling CIR bit for LP_state in wlanISR()
**  \main\maintrunk.MT5921\22 2007-11-07 18:34:10 GMT mtk01461
**  Revise naming of nicTxRelease()
**  \main\maintrunk.MT5921\21 2007-11-06 18:58:54 GMT mtk01385
**  mark LP check in wlanISR() due to it is reasonable.
**  \main\maintrunk.MT5921\20 2007-11-05 16:54:56 GMT mtk01425
**  1. Add nicRxUninitialize to wlanAdapterStop to release os packet buffer
**  \main\maintrunk.MT5921\19 2007-11-02 00:48:39 GMT mtk01461
**  Unify TX Path for Normal and IBSS Power Save + IBSS neighbor learning
**  \main\maintrunk.MT5921\18 2007-11-01 14:53:14 GMT mtk01084
**  modify the profile naming
**  \main\maintrunk.MT5921\17 2007-10-30 11:17:32 GMT mtk01425
**  1. Restore to version 14
**  \main\maintrunk.MT5921\16 2007-10-30 09:16:32 GMT mtk01425
**  1. Add a reset type parameter to arbFsmRunEventReset
**  \main\maintrunk.MT5921\15 2007-10-30 09:13:23 GMT mtk01425
**  1. Release queued packet of each station when unloading the driver
**  2. Add wlanSetPromiscuousMode, wlanRxAllMulticast, wlanRxNoMulticast and wlanRxSetMulticastList functions
** Revision 1.3  2007/07/05 07:25:29  MTK01461
** Add Linux initial code, modify doc, add 11BB, RF init code
**
** Revision 1.2  2007/06/27 02:18:49  MTK01461
** Update SCAN_FSM, Initial(Can Load Module), Proc(Can do Reg R/W), TX API
**
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
BOOLEAN fgIsBusAccessFailed = FALSE;

/*******************************************************************************
*                           P R I V A T E   D A T A
********************************************************************************
*/

/* OID set handlers without the need to access HW register */
PFN_OID_HANDLER_FUNC apfnOidSetHandlerWOHwAccess[] = {
    wlanoidSetFrequency,
    wlanoidSetChannel,
    wlanoidSetBeaconInterval,
#if 0 /* SUPPORT_WPS */
    wlanoidSetAppIE,
    wlanoidSetFrameFilter
#endif /* SUPPORT_WPS */
};

/* OID query handlers without the need to access HW register */
PFN_OID_HANDLER_FUNC apfnOidQueryHandlerWOHwAccess[] = {
    wlanoidQueryPermanentAddr,
    wlanoidQueryCurrentAddr,
    wlanoidQueryBssid,
    wlanoidQuerySsid,
    wlanoidQueryInfrastructureMode,
    wlanoidQueryAuthMode,
    wlanoidQueryEncryptionStatus,
    wlanoidQueryPmkid,
    wlanoidQueryNetworkTypeInUse,
    wlanoidQueryRssi,
    wlanoidQueryBssidList,
    wlanoidQueryAcpiDevicePowerState,
    wlanoidQueryLinkSpeed,
    wlanoidQueryXmitOk,
    wlanoidQueryRcvOk,
    wlanoidQueryXmitError,
    wlanoidQueryRcvError,
    wlanoidQueryXmitOneCollision,
    wlanoidQueryXmitMoreCollisions,
    wlanoidQueryXmitMaxCollisions,

    wlanoidQueryVoipConnectionStatus,

    wlanoidQuerySupportedRates,
    wlanoidQueryDesiredRates,

    wlanoidQuery802dot11PowerSaveProfile,

    wlanoidQueryRoamingFunction,
    wlanoidQueryBeaconInterval,
    wlanoidQueryAtimWindow,
    wlanoidQueryFrequency,
#if CFG_LP_PATTERN_SEARCH_SLT
    wlanoidQuerySltResult,
    wlanoidSetSltMode,
#endif
    wlanoidQueryStatisticsForLinux,
};

/*******************************************************************************
*                                 M A C R O S
********************************************************************************
*/

/*******************************************************************************
*                  F U N C T I O N   D E C L A R A T I O N S
********************************************************************************
*/

/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/
/*----------------------------------------------------------------------------*/
/*!
* \brief This is a private routine, which is used to check if HW access is needed
*        for the OID query/ set handlers.
*
* \param[IN] pfnOidHandler Pointer to the OID handler.
* \param[IN] fgSetInfo     It is a Set information handler.
*
* \retval TRUE This function needs HW access
* \retval FALSE This function does not need HW access
*/
/*----------------------------------------------------------------------------*/
BOOLEAN
wlanIsHandlerNeedHwAccess (
    IN PFN_OID_HANDLER_FUNC pfnOidHandler,
    IN BOOLEAN              fgSetInfo
    )
{
    PFN_OID_HANDLER_FUNC* apfnOidHandlerWOHwAccess;
    UINT_32 i;
    UINT_32 u4NumOfElem;

    if (fgSetInfo) {
        apfnOidHandlerWOHwAccess = apfnOidSetHandlerWOHwAccess;
        u4NumOfElem = sizeof(apfnOidSetHandlerWOHwAccess) / sizeof(PFN_OID_HANDLER_FUNC);
    }
    else {
        apfnOidHandlerWOHwAccess = apfnOidQueryHandlerWOHwAccess;
        u4NumOfElem = sizeof(apfnOidQueryHandlerWOHwAccess) / sizeof(PFN_OID_HANDLER_FUNC);
    }

    for (i = 0; i < u4NumOfElem; i++) {
        if (apfnOidHandlerWOHwAccess[i] == pfnOidHandler) {
            return FALSE;
        }
    }

    return TRUE;
}   /* wlanIsHandlerNeedHwAccess */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to set flag for later handling card
*        ejected event.
*
* \param[in] prAdapter Pointer to the Adapter structure.
*
* \return (none)
*
* \note When surprised removal happens, Glue layer should invoke this
*       function to notify WPDD not to do any hw access.
*/
/*----------------------------------------------------------------------------*/
VOID
wlanCardEjected (
    IN P_ADAPTER_T         prAdapter
    )
{
    DEBUGFUNC("wlanCardEjected");
    INITLOG(("\n"));

    ASSERT(prAdapter);

    /* mark that the card is being ejected, NDIS will shut us down soon */
    HAL_SET_FLAG(prAdapter->rArbInfo, ADAPTER_FLAG_HW_ERR);

    nicTxRelease(prAdapter);

} /* wlanCardEjected */


/*----------------------------------------------------------------------------*/
/*!
* \brief Create adapter object
*
* \param prAdapter This routine is call to allocate the driver software objects.
*                  If fails, return NULL.
* \retval NULL If it fails, NULL is returned.
* \retval NOT NULL If the adapter was initialized successfully.
*/
/*----------------------------------------------------------------------------*/
P_ADAPTER_T
wlanAdapterCreate (
    IN P_GLUE_INFO_T prGlueInfo
    )
{
    P_ADAPTER_T prAdpater = (P_ADAPTER_T)NULL;

    DEBUGFUNC("wlanAdapterCreate");

    do {
        prAdpater = (P_ADAPTER_T)kalMemAlloc(sizeof(ADAPTER_T));

        if (!prAdpater) {
            DBGLOG(INIT, ERROR, ("Allocate ADAPTER memory ==> FAILED\n"));
            break;
        }

        kalMemZero(prAdpater, sizeof(ADAPTER_T));
        prAdpater->prGlueInfo = prGlueInfo;

    } while (FALSE);

    return prAdpater;
} /* wlanAdapterCreate */

#if CFG_SDIO_DEVICE_DRIVER_WO_NDIS

/*----------------------------------------------------------------------------*/
/*!
* \brief Destroy adapter object
*
* \param prAdapter This routine is call to destroy the driver software objects.
*                  If fails, return NULL.
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
wlanAdapterDestroy (
    IN P_ADAPTER_T prAdapter
    )
{

    if (!prAdapter) {
        return;
    }
    else {
        P_RFTEST_INFO_T prRfTestInfo;
        P_RX_CTRL_T prRxCtrl;
        P_TX_CTRL_T prTxCtrl;

        prRxCtrl = &prAdapter->rRxCtrl;
        prTxCtrl = &prAdapter->rTxCtrl;
        prRfTestInfo = &prAdapter->rRFTestInfo;

        if (prRxCtrl->pucRxCached) {
            kalMemFree(prRxCtrl->pucRxCached, prRxCtrl->u4RxCachedSize);
        }

        if (prTxCtrl->pucTxCached) {
            kalMemFree(prTxCtrl->pucTxCached, prTxCtrl->u4TxCachedSize);
        }

        if (prRfTestInfo->pucTxCached) {
            kalMemFree(prRfTestInfo->pucTxCached, prRfTestInfo->u4TxCachedSize);
        }

        kalMemFree(prAdapter, sizeof(ADAPTER_T));
    }

    return;
} /* wlanAdapterDestroy */

/*----------------------------------------------------------------------------*/
/*!
* \brief Initialize the adapter. The sequence is
*        1. Disable interrupt
*        2. Read adapter configuration from EEPROM and registry, verify chip ID.
*        3. Create NIC Tx/Rx resource.
*        4. Initialize the chip
*        5. Initialize the protocol
*        6. Enable Interrupt
*
* \param prAdapter      Pointer of Adapter Data Structure
*
* \retval WLAN_STATUS_SUCCESS: Success
* \retval WLAN_STATUS_FAILURE: Failed
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanAdapterStart (
    IN P_ADAPTER_T prAdapter,
    IN P_REG_INFO_T prRegInfo
    )
{
    WLAN_STATUS rStatus = WLAN_STATUS_FAILURE;
    P_PTA_INFO_T prPtaInfo;
    P_PTA_PARAM_T prPtaParam;


    ASSERT(prAdapter);

    DEBUGFUNC("wlanAdapterStart");

    prPtaInfo = &prAdapter->rPtaInfo;
    prPtaParam  = &prPtaInfo->rPtaParam;

    prPtaInfo->fgSingleAntenna = TRUE;
    prPtaInfo->u4PTAWireMode = PTA_SW_1_WIRE_MODE;
    prPtaParam->u4BtCR0 = 0;
    prPtaParam->u4BtCR1 = 0;
    prPtaParam->u4BtCR2 = 0;
    prPtaParam->u4BtCR3 = 0;

    //4 <1> Initial ARB Fsm.
    if ((rStatus = arbFsmInit(prAdapter) ) != WLAN_STATUS_SUCCESS) {
        return rStatus;
    }

    arbFsmRunEventReset(prAdapter);


    /*==================================================*/

    return rStatus;
} /* wlanAdapterStart */
#else

/*----------------------------------------------------------------------------*/
/*!
* \brief Destroy adapter object
*
* \param prAdapter This routine is call to destroy the driver software objects.
*                  If fails, return NULL.
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
wlanAdapterDestroy (
    IN P_ADAPTER_T prAdapter
    )
{

    if (!prAdapter) {
        return;
    }

    kalMemFree(prAdapter, sizeof(ADAPTER_T));

    return;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief Initialize the adapter. The sequence is
*        1. Disable interrupt
*        2. Read adapter configuration from EEPROM and registry, verify chip ID.
*        3. Create NIC Tx/Rx resource.
*        4. Initialize the chip
*        5. Initialize the protocol
*        6. Enable Interrupt
*
* \param prAdapter      Pointer of Adapter Data Structure
*
* \retval WLAN_STATUS_SUCCESS: Success
* \retval WLAN_STATUS_FAILURE: Failed
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanAdapterStart (
    IN P_ADAPTER_T prAdapter,
    IN P_REG_INFO_T prRegInfo
    )
{
    WLAN_STATUS u4Status = WLAN_STATUS_SUCCESS;


    ASSERT(prAdapter);

    ARB_ACQUIRE_POWER_CONTROL_FROM_PM(prAdapter);

    do {
        if ((u4Status = arbFsmInit(prAdapter, prRegInfo) ) != WLAN_STATUS_SUCCESS) {
            break;
        }

        // Trigger ARB FSM.
        arbFsmRunEventReset(prAdapter);

#if defined(LINUX)
        kalUpdateMACAddress(prAdapter->prGlueInfo,
                            prAdapter->aucMacAddress);
#endif /* LINUX */
    } while (FALSE);

    ARB_RECLAIM_POWER_CONTROL_TO_PM(prAdapter);

    return u4Status;
} /* wlanAdapterStart */
#endif

/*----------------------------------------------------------------------------*/
/*!
* \brief Uninitialize the adapter
*
* \param prAdapter      Pointer of Adapter Data Structure
*
* \retval WLAN_STATUS_SUCCESS: Success
* \retval WLAN_STATUS_FAILURE: Failed
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanAdapterStop (
    IN P_ADAPTER_T prAdapter
    )
{
    WLAN_STATUS u4Status = WLAN_STATUS_SUCCESS;

    ASSERT(prAdapter);
    /* Due to there's a trap condition for not permitting to do HW access under ACPI-D3,
     * here's a flag for preventing this case in the adapter stop procedure.
     * This is a easier method for not to effect subroutine-internal mechanism.
     */
    if (prAdapter->rAcpiState == ACPI_STATE_D3) {
         fgIsBusAccessFailed = TRUE;
    }

    ARB_ACQUIRE_POWER_CONTROL_FROM_PM(prAdapter);

    /* To disassociate connected AP, to avoid whql unload load driver test error */
    if (prAdapter->eConnectionState == MEDIA_STATE_CONNECTED) {
        arbFsmRunEventJoinDisassoc(prAdapter);
    }

    nicDisableInterrupt(prAdapter);

    arbFsmUnInit(prAdapter);

    nicTxRelease(prAdapter);

    nicRxUninitialize(prAdapter);

    ARB_RECLAIM_POWER_CONTROL_TO_PM(prAdapter);

    nicReleaseAdapterMemory(prAdapter);

#if defined(_HIF_SPI)
    /* Note: restore the SPI Mode Select from 32 bit to default */
    nicRestoreSpiDefMode(prAdapter);
#endif

    return u4Status;
} /* wlanAdapterStop */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function is called by ISR (interrupt).
*
* \param prAdapter      Pointer of Adapter Data Structure
*
* \retval TRUE: NIC's interrupt
* \retval FALSE: Not NIC's interrupt
*/
/*----------------------------------------------------------------------------*/
BOOL
wlanISR (
    IN P_ADAPTER_T prAdapter,
    IN BOOLEAN fgGlobalIntrCtrl
    )
{
    ASSERT(prAdapter);

    if (prAdapter->rAcpiState != ACPI_STATE_D3) {
#if CFG_TEST_IO_PIN
        if (IS_ARB_IN_RFTEST_STATE(prAdapter)) {
            if (!prAdapter->fgIntVarified) {
                UINT_32 u4TmpValue = 0, u4ScrOriVal = 0;
                HAL_MCR_RD(prAdapter, MCR_SCR, &u4TmpValue);
                u4ScrOriVal = u4TmpValue;

                if ((u4TmpValue & SCR_BT_ACT_SEL) ||
                        (u4TmpValue & SCR_GPIO0_ENABLE_OUTPUT_MODE) ||
                        (u4TmpValue & SCR_GPIO2_ENABLE_OUTPUT_MODE)) {

                    u4TmpValue &= ~(SCR_GPIO0_ENABLE_OUTPUT_MODE);
                    u4TmpValue &= ~(SCR_GPIO2_ENABLE_OUTPUT_MODE);
                    u4TmpValue &= ~(SCR_BT_ACT_SEL);
                    HAL_MCR_WR(prAdapter, MCR_SCR, u4TmpValue);
                    HAL_MCR_RD(prAdapter, MCR_SCR, &u4TmpValue);
                }

                if (u4TmpValue & SCR_GPIO0_RDATA) {
                    /* GPIO_0 Fail. */
                    prAdapter->u4IntIORslt &= ~(BIT(0));
                }
                else {
                    /* GPIO_0 OK. */
                    prAdapter->u4IntIORslt |= BIT(0);
                }

                if (u4TmpValue & SCR_GPIO2_RDATA) {
                    /* GPIO_2 Fail. */
                    prAdapter->u4IntIORslt &= ~(BIT(1));
                }
                else {
                    /* GPIO_2 OK. */
                    prAdapter->u4IntIORslt |= BIT(1);
                }

                HAL_MCR_WR(prAdapter, MCR_SCR, u4ScrOriVal);

                prAdapter->fgIntVarified = TRUE;
            }
        }
#endif

        if (fgGlobalIntrCtrl) {
            nicDisableInterrupt(prAdapter);
        }
        return TRUE;
    }
    else {
        DBGLOG(HAL, WARN, ("wlanISR triggered on ACPI-D3\n"));
        return FALSE;
    }
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This function is called by IST (task_let).
*
* \param prAdapter      Pointer of Adapter Data Structure
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
wlanIST (
    IN P_ADAPTER_T prAdapter
    )
{
    ASSERT(prAdapter);

    if (arbFsmRunEventIST(prAdapter)) {
        nicEnableInterrupt(prAdapter);
    }

    return;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This function will take KAL_MSDU_INFO_T which carry some informations of
*        incoming frame from GLUE Layer and notify the ARBITER to send packet.
*
* \param prAdapter      Pointer of Adapter Data Structure
* \param prKalMsduInfo  Pointer of KAL_MSDU_INFO_T
*
* \retval WLAN_STATUS_SUCCESS   : MSDU was written to HW TX FIFO and be freed(SendComplete) immediately.
* \retval WLAN_STATUS_PENDING   : MSDU is pending in SW Queues to wait for previous frame finishing
                                  their transmission and release buffer.
* \retval WLAN_STATUS_FAILURE   : Get failure while access HW TX FIFO or been rejected.
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanSendPacket (
    IN P_ADAPTER_T          prAdapter,
    IN P_PACKET_INFO_T      prPacketInfo
    )
{
    WLAN_STATUS rStatus;


    ASSERT(prAdapter);
    ASSERT(prPacketInfo);
    ASSERT(prPacketInfo->ucTID < TID_NUM);

    //4 <1> Check acceptable TX length if OS send unexpected large packets.
    if ((prPacketInfo->ucMacHeaderLength + prPacketInfo->u2PayloadLength) > CFG_TX_MAX_PKT_SIZE) {
        return WLAN_STATUS_FAILURE;
    }

#if 0 // NOTE: for optimization for power issue, this is removed to TX module inside
    ARB_ACQUIRE_POWER_CONTROL_FROM_PM(prAdapter);
#else
    ARB_ACQUIRE_POWER_CONTROL_FROM_PM_IN_OS_TX_PATH(prAdapter);
#endif

    rStatus = arbFsmRunEventTxMsduFromOs(prAdapter, prPacketInfo);

    ARB_RECLAIM_POWER_CONTROL_TO_PM(prAdapter);

    return rStatus;

} /* end of wlanSendPacket() */

/*----------------------------------------------------------------------------*/
/*!
* \brief Return the packet buffer and reallocate one to the RFB
*
* \param prAdapter      Pointer of Adapter Data Structure
* \param pvPacket       Pointer of returned packet
*
* \retval WLAN_STATUS_SUCCESS: Success
* \retval WLAN_STATUS_FAILURE: Failed
*/
/*----------------------------------------------------------------------------*/
VOID
wlanReturnPacket (
    IN P_ADAPTER_T prAdapter,
    IN PVOID pvPacket
    )
{
    P_RX_CTRL_T prRxCtrl;
    P_SW_RFB_T prSWRfb = NULL;

    ASSERT(prAdapter);
    prRxCtrl = &prAdapter->rRxCtrl;

    if (pvPacket) {
        kalPacketFree(prAdapter->prGlueInfo, pvPacket);
    }
    if (QUEUE_IS_NOT_EMPTY(&prRxCtrl->rFreeRFBWOBuffList)) {
        QUEUE_REMOVE_HEAD(&prRxCtrl->rFreeRFBWOBuffList, prSWRfb, P_SW_RFB_T);
        if(!prSWRfb){
            return;
        }
        if(nicRxSetupRFB(prAdapter, prSWRfb)){
            QUEUE_INSERT_HEAD(&prRxCtrl->rFreeRFBWOBuffList, &prSWRfb->rQueEntry);
            return;
        }
        nicRxReturnRFB(prAdapter, prSWRfb);
    }
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This function is a required function that returns information about
*        the capabilities and status of the driver and/or its network adapter.
*
* \param[IN] prAdapter        Pointer to the Adapter structure.
* \param[IN] pfnOidQryHandler Function pointer for the OID query handler.
* \param[IN] pvInfoBuf        Points to a buffer for return the query information.
* \param[IN] u4QueryBufferLen Specifies the number of bytes at pvInfoBuf.
* \param[OUT] pu4QueryInfoLen  Points to the number of bytes it written or is needed.
*
* \retval WLAN_STATUS_xxx Different WLAN_STATUS code returned by different handlers.
*
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanQueryInformation (
    IN P_ADAPTER_T          prAdapter,
    IN PFN_OID_HANDLER_FUNC pfnOidQryHandler,
    IN PVOID                pvInfoBuf,
    IN UINT_32              u4InfoBufLen,
    OUT PUINT_32            pu4QryInfoLen
    )
{
    WLAN_STATUS status = WLAN_STATUS_FAILURE;

    ASSERT(prAdapter);
    ASSERT(pu4QryInfoLen);

    if (wlanIsHandlerNeedHwAccess(pfnOidQryHandler, FALSE) && !IS_ARB_IN_RFTEST_STATE(prAdapter)) {
        ARB_ACQUIRE_POWER_CONTROL_FROM_PM(prAdapter);
        status = pfnOidQryHandler(prAdapter,
                                    pvInfoBuf,
                                    u4InfoBufLen,
                                    pu4QryInfoLen);

        ARB_RECLAIM_POWER_CONTROL_TO_PM(prAdapter);
    }
    else {
        status = pfnOidQryHandler(prAdapter,
                                    pvInfoBuf,
                                    u4InfoBufLen,
                                    pu4QryInfoLen);
    }

    return status;

}

/*----------------------------------------------------------------------------*/
/*!
* \brief This function is a required function that allows bound protocol drivers,
*        or NDIS, to request changes in the state information that the miniport
*        maintains for particular object identifiers, such as changes in multicast
*        addresses.
*
* \param[IN] prAdapter     Pointer to the Glue info structure.
* \param[IN] pfnOidSetHandler     Points to the OID set handlers.
* \param[IN] pvInfoBuf     Points to a buffer containing the OID-specific data for the set.
* \param[IN] u4InfoBufLen  Specifies the number of bytes at prSetBuffer.
* \param[OUT] pu4SetInfoLen Points to the number of bytes it read or is needed.
*
* \retval WLAN_STATUS_xxx Different WLAN_STATUS code returned by different handlers.
*
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanSetInformation (
    IN P_ADAPTER_T          prAdapter,
    IN PFN_OID_HANDLER_FUNC pfnOidSetHandler,
    IN PVOID                pvInfoBuf,
    IN UINT_32              u4InfoBufLen,
    OUT PUINT_32            pu4SetInfoLen
    )
{
    WLAN_STATUS status = WLAN_STATUS_FAILURE;

    ASSERT(prAdapter);
    ASSERT(pu4SetInfoLen);

    if (wlanIsHandlerNeedHwAccess(pfnOidSetHandler, TRUE) && !IS_ARB_IN_RFTEST_STATE(prAdapter)) {
        ARB_ACQUIRE_POWER_CONTROL_FROM_PM(prAdapter);

        status = pfnOidSetHandler(prAdapter,
                                    pvInfoBuf,
                                    u4InfoBufLen,
                                    pu4SetInfoLen);

        ARB_RECLAIM_POWER_CONTROL_TO_PM(prAdapter);
    }
    else {
        status = pfnOidSetHandler(prAdapter,
                                    pvInfoBuf,
                                    u4InfoBufLen,
                                    pu4SetInfoLen);
    }
    return status;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This function is called to set RX filter to Promiscuous Mode.
*
* \param[IN] prAdapter        Pointer to the Adapter structure.
* \param[IN] fgEnablePromiscuousMode Enable/ disable RX Promiscuous Mode.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
wlanSetPromiscuousMode (
    IN P_ADAPTER_T  prAdapter,
    IN BOOLEAN      fgEnablePromiscuousMode
    )
{
    ASSERT(prAdapter);

    if(fgEnablePromiscuousMode) {
        nicRxEnablePromiscuousMode(prAdapter);
    }
    else {
        nicRxDisablePromiscuousMode(prAdapter);
    }
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This function is called to set RX filter to allow to receive
*        broadcast address packets.
*
* \param[IN] prAdapter        Pointer to the Adapter structure.
* \param[IN] fgEnableBroadcast Enable/ disable broadcast packet to be received.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
wlanRxSetBroadcast (
    IN P_ADAPTER_T  prAdapter,
    IN BOOLEAN      fgEnableBroadcast
    )
{
    ASSERT(prAdapter);

    nicRxSetBroadcast(prAdapter, fgEnableBroadcast);
}


#if SUPPORT_WAPI
/*----------------------------------------------------------------------------*/
/*!
* \brief This function will set the prAdapter->fgUseWapi value.
*
* \param prAdapter      Pointer of Adapter Data Structure
*
* \retval None.
*/
/*----------------------------------------------------------------------------*/
VOID
wlanSetWapiMode (
    IN P_ADAPTER_T          prAdapter,
    IN UINT_32              u4UseWapi
    )
{
    DEBUGFUNC("wlanSetWapiMode");
    ASSERT(prAdapter);

    if (u4UseWapi) {
        prAdapter->fgUseWapi = TRUE;
        prAdapter->rSecInfo.fgPrivacyCheckDisable = TRUE;
	    prAdapter->rSecInfo.fgBlockTxTraffic = TRUE;
        prAdapter->rSecInfo.fgBlockRxTraffic = TRUE;
    }
    else {
        prAdapter->fgUseWapi = FALSE;
        prAdapter->rSecInfo.fgPrivacyCheckDisable = FALSE;
        prAdapter->rSecInfo.fgBlockTxTraffic = FALSE;
        prAdapter->rSecInfo.fgBlockRxTraffic = FALSE;
    }
}


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will query the prAdapter->fgUseWapi value.
*
* \param prAdapter      Pointer of Adapter Data Structure
*
* \retval TRUE  : The driver running at WAPI mode.
* \retval FALSE : The driver running at Wi-Fi mode.
*/
/*----------------------------------------------------------------------------*/
BOOLEAN
wlanQueryWapiMode (
    IN P_ADAPTER_T          prAdapter
    )
{
    DEBUGFUNC("wlanQueryWapiMode");
    ASSERT(prAdapter);

    return prAdapter->fgUseWapi;
}
#endif
