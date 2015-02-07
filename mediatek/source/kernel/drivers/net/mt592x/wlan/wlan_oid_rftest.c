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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/wlan_oid_rftest.c#1 $
*/

/*! \file wlan_oid_rftest.c
    \brief This file contains the WLAN RFTEST OID processing routines of
           Windows driver for  MediaTek Inc. 802.11 Wireless LAN Adapters.
*/

/******************************************************************************
* Copyright (c) 2007 MediaTek Inc.
*
* All rights reserved. Copying, compilation, modification, distribution
* or any other use whatsoever of this material is strictly prohibited
* except in accordance with a Software License Agreement with
* MediaTek Inc.
*******************************************************************************
*/

/******************************************************************************
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
*******************************************************************************
*/

/*
** $Log: wlan_oid_rftest.c $
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\10 2009-10-02 16:56:37 GMT mtk01089
**  update setting preferred antenna path when leaving rftest mode
**  \main\maintrunk.MT5921\9 2009-10-02 16:53:47 GMT mtk01089
**  Set antenna path to WiFi when entering rftest mode and set path to BT when leaving rftest test mode.
**  \main\maintrunk.MT5921\8 2009-08-24 10:53:50 GMT mtk01089
**  Meta mode does not validate 32K calibration result. A workaounrd is required to add 32K calibration test.
**  \main\maintrunk.MT5921\7 2008-12-08 21:27:10 GMT mtk01461
**  Fix lint warning - Null Pointer
**  \main\maintrunk.MT5921\6 2008-10-22 10:55:05 GMT mtk01461
**  Update for lint diagnosis support
**  \main\maintrunk.MT5921\5 2008-08-27 11:45:54 GMT mtk01104
**  Remove not supported code in wlanoidRftestSetTestMode()
**  \main\maintrunk.MT5921\4 2008-02-04 17:05:15 GMT mtk01461
**  Refine ARB_IF_IN_RFTEST_STATE
**  \main\maintrunk.MT5921\3 2007-12-26 14:26:17 GMT mtk01385
**  1. Skip AutoTest Set command while ARB is not in RFTEST mode.
**  \main\maintrunk.MT5921\2 2007-11-30 16:31:08 GMT mtk01425
**  1. Fix compiling warning
**  \main\maintrunk.MT5921\1 2007-11-19 10:09:30 GMT mtk01385
**
**
*/

/******************************************************************************
*                         C O M P I L E R   F L A G S
*******************************************************************************
*/

/******************************************************************************
*                    E X T E R N A L   R E F E R E N C E S
*******************************************************************************
*/
#include "precomp.h"

/******************************************************************************
*                              C O N S T A N T S
*******************************************************************************
*/

/******************************************************************************
*                             D A T A   T Y P E S
*******************************************************************************
*/

/******************************************************************************
*                            P U B L I C   D A T A
*******************************************************************************
*/

/******************************************************************************
*                           P R I V A T E   D A T A
*******************************************************************************
*/

/******************************************************************************
*                                 M A C R O S
*******************************************************************************
*/

/******************************************************************************
*                   F U N C T I O N   D E C L A R A T I O N S
*******************************************************************************
*/

/******************************************************************************
*                              F U N C T I O N S
*******************************************************************************
*/

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to request the driver to enter the
*        RF test mode.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[in] pvSetBuffer Pointer to the buffer that holds the data to be set.
* \param[in] u4SetBufferLen The length of the set buffer.
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*   bytes read from the set buffer. If the call failed due to invalid length of
*   the set buffer, returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS       success
* \retval WLAN_STATUS_INVALID_DATA  data is not invalid
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidRftestSetTestMode (
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID             pvSetBuffer,
    IN  UINT_32           u4SetBufferLen,
    OUT PUINT_32          pu4SetInfoLen
    )
{
    P_PARAM_RFTEST_INFO_T  prRfTestInfo;
#if CFG_SDIO_DEVICE_DRIVER_WO_NDIS
    BOOL fgStatus = FALSE;
#endif

    DEBUGFUNC("wlanoidRftestSetTestMode");

    ASSERT(prAdapter);
    ASSERT(pvSetBuffer);
    ASSERT(pu4SetInfoLen);

    *pu4SetInfoLen = 0;

    if (u4SetBufferLen == 0 ||
        u4SetBufferLen == sizeof(prRfTestInfo->u4Length)) {
        /* If setBufferLen is zero, we need to load EEPROM */
        arbFsmRunEventRftestEnterTestMode(prAdapter, NULL, 0);

#if CFG_SDIO_DEVICE_DRIVER_WO_NDIS
        // Calibrate 32K slow clock
        /* meta mode does not run into 32K validation and there is no return code. Therefore, we need to invoke calibration here. */
        fgStatus = nicpmCalSlowClock(prAdapter, &prAdapter->rPmInfo.rSlowClkCnt);

        if(fgStatus == FALSE){
            return WLAN_STATUS_FAILURE;
        }
#endif

#if !(CFG_SDIO_DEVICE_DRIVER_WO_NDIS)
        /* Currently no idea how to handle meta mode. However, in normal build, entering test mode
           means going to test wifi. set preferred antenna path to wifi.
        */
#if PTA_NEW_BOARD_DESIGN
        if(prAdapter->rPtaInfo.fgSingleAntenna){
            nicPtaSetAnt(prAdapter, TRUE);
        }
#endif
#endif

        return WLAN_STATUS_SUCCESS;
    }
    /* MT5921 does not support EEPROM content change by this oid cmd */

    prRfTestInfo = pvSetBuffer;

    DBGLOG(REQ, ERROR, ("Invalid data. nicInfoContentLen: %ld, Length:%ld\n",
        prRfTestInfo->u4NicInfoContentLen,
        prRfTestInfo->u4Length));

    return WLAN_STATUS_INVALID_DATA;
}   /* wlanoidRftestSetTestMode */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to request the driver to abort the
*        RF test mode.
*
* \param[in] pvAdapter Pointer to the Adapter structure.
* \param[in] setBuffer_p Pointer to the buffer that holds the data to be set.
* \param[in] setBufferLen The length of the set buffer.
* \param[out] setInfoLen_p If the call is successful, returns the number of
*   bytes read from the set buffer. If the call failed due to invalid length of
*   the set buffer, returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidRftestSetAbortTestMode (
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID             pvSetBuffer,
    IN  UINT_32           u4SetBufferLen,
    OUT PUINT_32          pu4SetInfoLen
    )
{
    DEBUGFUNC("wlanoidRftestSetAbortTestMode");

    ASSERT(prAdapter);
    ASSERT(pvSetBuffer);
    ASSERT(pu4SetInfoLen);

    *pu4SetInfoLen = 0;

    arbFsmRunEventRftestAbortTestMode(prAdapter);

#if !(CFG_SDIO_DEVICE_DRIVER_WO_NDIS)
        /* Currently no idea how to handle meta mode. However, in normal build, entering test mode
           means going to test wifi. set preferred antenna path to wifi.
        */
#if PTA_NEW_BOARD_DESIGN
    if(prAdapter->rPtaInfo.fgSingleAntenna){
        nicPtaSetAnt(prAdapter, FALSE);
    }
#endif
#endif

    return WLAN_STATUS_SUCCESS;
}   /* rftestSetAbortTestMode */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to request the driver to Config Auto Test Mode.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[in] pvSetBuffer Pointer to the buffer that holds the data to be set.
* \param[in] u4SetBufferLen The length of the set buffer.
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*   bytes read from the set buffer. If the call failed due to invalid length of
*   the set buffer, returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS        success
* \retval WLAN_STATUS_INVALID_LENGTH buffer length is not matched
* \retval WLAN_STATUS_NOT_ACCEPTED   fail because not in test mode
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidRftestSetAutoTest (
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID             pvSetBuffer,
    IN  UINT_32           u4SetBufferLen,
    OUT PUINT_32          pu4SetInfoLen
    )
{
    P_PARAM_MTK_WIFI_TEST_STRUC_T  prRfATInfo = \
                            (P_PARAM_MTK_WIFI_TEST_STRUC_T)pvSetBuffer;

    DEBUGFUNC("wlanoidRftestSetAutoTest");

    ASSERT(prAdapter);
    ASSERT(pvSetBuffer);
    ASSERT(pu4SetInfoLen);

    if (!IS_ARB_IN_RFTEST_STATE(prAdapter)) {
        return WLAN_STATUS_NOT_ACCEPTED;
    }

    *pu4SetInfoLen = 0;

    if (u4SetBufferLen != sizeof(PARAM_MTK_WIFI_TEST_STRUC_T)) {
        DBGLOG(REQ, ERROR, ("Invalid data. SetBufferLen: %ld.\n",
                  u4SetBufferLen));
        return WLAN_STATUS_INVALID_LENGTH;
    }

    return arbFsmRunEventRftestSetAutoTest(prAdapter, prRfATInfo);
}   /* wlanoidRftestSetAutoTest */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to query Auto Test Mode status.
*
* \param[in] prAdapter Pointer to the Adapter structure.
* \param[in] pvQueryBuf Pointer to the buffer that holds the result of the query
* \param[in] u4QueryBufLen The length of the query buffer.
* \param[out] pu4QueryInfoLen If the call is successful, returns the number of
*                       bytes written into the query buffer. If the call
*                       failed due to invalid length of the query buffer,
*                       returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS        success
* \retval WLAN_STATUS_INVALID_LENGTH buffer length is not matched
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanoidRftestQueryAutoTest (
    IN  P_ADAPTER_T       prAdapter,
    IN  PVOID             pvQueryBuf,
    IN  UINT_32           u4QueryBufLen,
    OUT PUINT_32          pu4QueryInfoLen
    )
{
    P_PARAM_MTK_WIFI_TEST_STRUC_T  prRfATInfo;

    DEBUGFUNC("wlanoidRftestQueryAutoTest");

    ASSERT(prAdapter);
    ASSERT(pvQueryBuf);
    ASSERT(pu4QueryInfoLen);

    *pu4QueryInfoLen = sizeof(PARAM_MTK_WIFI_TEST_STRUC_T);

    if (u4QueryBufLen != sizeof(PARAM_MTK_WIFI_TEST_STRUC_T)) {
        DBGLOG(REQ, ERROR, ("Invalid data. QueryBufferLen: %ld.\n",
                  u4QueryBufLen));
        return WLAN_STATUS_INVALID_LENGTH;
    }

    prRfATInfo = (P_PARAM_MTK_WIFI_TEST_STRUC_T)pvQueryBuf;

    return arbFsmRunEventRftestQueryAutoTest(prAdapter, prRfATInfo);
}   /* wlanoidRftestQueryAutoTest */

