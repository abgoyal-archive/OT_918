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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/typedef.h#1 $
*/

/*! \file   typedef.h
    \brief  Declaration of data type and return values of internal protocol stack.

    In this file we declare the data type and return values which will be exported
    to the GLUE Layer.
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
** $Log: typedef.h $
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\24 2008-10-30 09:30:30 GMT mtk01084
**  modify for the compiler warning
**  \main\maintrunk.MT5921\23 2008-10-27 14:21:28 GMT mtk01084
**  fix the LINT warning
**  \main\maintrunk.MT5921\22 2008-09-02 10:56:46 GMT mtk01461
**  Update driver for code review
**  \main\maintrunk.MT5921\21 2008-04-24 22:44:41 GMT mtk01461
**  move define of param filter to wlan_oid.h
**  \main\maintrunk.MT5921\20 2008-03-18 13:44:20 GMT mtk01088
**  add rf table type declaration
**  \main\maintrunk.MT5921\19 2008-02-29 15:13:52 GMT mtk01088
**  add variable for sw port control
**  \main\maintrunk.MT5921\18 2007-11-30 16:40:25 GMT mtk01425
**  1. Add FILTER-related symbol
**  \main\maintrunk.MT5921\17 2007-11-26 19:32:53 GMT mtk01461
**  Unify SCAN
**  \main\maintrunk.MT5921\16 2007-11-06 20:01:33 GMT mtk01088
**  add the HW Error flag (from WPDD)
**  \main\maintrunk.MT5921\15 2007-11-02 00:50:49 GMT mtk01461
**  Unify TX Path for Normal and IBSS Power Save + IBSS neighbor learning
**  \main\maintrunk.MT5921\14 2007-10-30 09:57:43 GMT mtk01425
**  1. Add WLAN_STATUS_MULTICAST_FULL and TABLE_ENTRY_T
** Revision 1.5  2007/07/17 12:55:40  MTK01088
** add define for WLAN_STATUS
**
** Revision 1.4  2007/07/05 07:25:31  MTK01461
** Add Linux initial code, modify doc, add 11BB, RF init code
**
** Revision 1.3  2007/07/04 13:02:21  MTK01088
** add WLAN_STATUS define
**
** Revision 1.2  2007/06/25 06:16:23  MTK01461
** Update illustrations, gl_init.c, gl_kal.c, gl_kal.h, gl_os.h and RX API
**
*/

#ifndef _TYPEDEF_H
#define _TYPEDEF_H

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
#define WLAN_STATUS_SUCCESS                     ((WLAN_STATUS) 0x00000000L)
#define WLAN_STATUS_PENDING                     ((WLAN_STATUS) 0x00000103L)
#define WLAN_STATUS_NOT_ACCEPTED                ((WLAN_STATUS) 0x00010003L)

#define WLAN_STATUS_MEDIA_CONNECT               ((WLAN_STATUS) 0x4001000BL)
#define WLAN_STATUS_MEDIA_DISCONNECT            ((WLAN_STATUS) 0x4001000CL)
#define WLAN_STATUS_MEDIA_SPECIFIC_INDICATION   ((WLAN_STATUS) 0x40010012L)

#define WLAN_STATUS_SCAN_COMPLETE               ((WLAN_STATUS) 0x60010001L)
#define WLAN_STATUS_MSDU_OK                     ((WLAN_STATUS) 0x60010002L)

/* TODO(Kevin): double check if 0x60010001 & 0x60010002 is proprietary */
#define WLAN_STATUS_ROAM_OUT_FIND_BEST          ((WLAN_STATUS) 0x60010101L)
#define WLAN_STATUS_ROAM_DISCOVERY              ((WLAN_STATUS) 0x60010102L)

#define WLAN_STATUS_FAILURE                     ((WLAN_STATUS) 0xC0000001L)
#define WLAN_STATUS_RESOURCES                   ((WLAN_STATUS) 0xC000009AL)
#define WLAN_STATUS_NOT_SUPPORTED               ((WLAN_STATUS) 0xC00000BBL)

#define WLAN_STATUS_MULTICAST_FULL              ((WLAN_STATUS) 0xC0010009L)
#define WLAN_STATUS_INVALID_PACKET              ((WLAN_STATUS) 0xC001000FL)
#define WLAN_STATUS_ADAPTER_NOT_READY           ((WLAN_STATUS) 0xC0010011L)
#define WLAN_STATUS_INVALID_LENGTH              ((WLAN_STATUS) 0xC0010014L)
#define WLAN_STATUS_INVALID_DATA                ((WLAN_STATUS) 0xC0010015L)
#define WLAN_STATUS_BUFFER_TOO_SHORT            ((WLAN_STATUS) 0xC0010016L)

/* NIC status flags */
#define ADAPTER_FLAG_HW_ERR                     0x00400000

/* Type Length */
#define TL_IPV4     0x0008
#define TL_IPV6     0xDD86


/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/
/* Type definition for GLUE_INFO structure */
typedef struct _GLUE_INFO_T     GLUE_INFO_T, *P_GLUE_INFO_T;

/* Type definition for WLAN STATUS */
typedef UINT_32                 WLAN_STATUS, *P_WLAN_STATUS;

/* Type definition for ADAPTER structure */
typedef struct _ADAPTER_T       ADAPTER_T, *P_ADAPTER_T;

/* Type definition for MSDU_INFO structure, a SW resource for outgoing packet */
typedef struct _MSDU_INFO_T     MSDU_INFO_T, *P_MSDU_INFO_T;

/* Type definition for Pointer to OS Native Packet */
typedef struct _NATIVE_PACKET   *P_NATIVE_PACKET;

/* Type definition for STA_RECORD_T structure to handle the connectivity and packet reception
 * for a particular STA.
 */
typedef struct _STA_RECORD_T    STA_RECORD_T, *P_STA_RECORD_T;

/* Type definition for BSS_DESC_T structure, to describe parameter sets of a particular BSS */
typedef struct _BSS_DESC_T      BSS_DESC_T, *P_BSS_DESC_T;


/* Type definition for PEER_BSS_INFO_T structure, to describe parameter sets of a Peer BSS
 * which we are going to join with or merge into.
 */
typedef struct _PEER_BSS_INFO_T PEER_BSS_INFO_T, *P_PEER_BSS_INFO_T;

/* Type definition for BSS_INFO_T structure, to describe parameter sets of current BSS which
 * we are associated with or created for AdHoc Mode.
 */
typedef struct _BSS_INFO_T      BSS_INFO_T, *P_BSS_INFO_T;

/* Type definition for INT_EVENT_MAP_T structure, to describe parameter sets of the interrupt
   event with the interrupt status and register .
 */
//4 2007/10/05, mikewu, Move this back to nic.h, we don't want it to be seen in glue layer
//typedef const struct _INT_EVENT_MAP_T INT_EVENT_MAP_T, *P_INT_EVENT_MAP_T;


typedef struct _SCAN_REQ_CONFIG_T   SCAN_REQ_CONFIG_T, *P_SCAN_REQ_CONFIG_T;


/* PACKET_INFO_T is used by Glue Layer to send a cluster of packet information to
 * the Internal Protocol Stack to reduce the parameters of a function call.
 */
typedef struct _PACKET_INFO_T {
    P_NATIVE_PACKET prPacket;
    BOOLEAN         fgIs802_11;
    BOOLEAN         fgIs1x;
    UINT_8          ucTID;
    UINT_8          ucMacHeaderLength;
    UINT_16         u2PayloadLength;
    PUINT_8         pucDestAddr;
} PACKET_INFO_T, *P_PACKET_INFO_T;




/* Following typedef should be removed later, because Glue Layer should not
 * be aware of following data type.
 */
typedef struct _SW_RFB_T        SW_RFB_T, *P_SW_RFB_T, **PP_SW_RFB_T;

typedef struct _EEPROM_CTRL_T    EEPROM_CTRL_T, *P_EEPROM_CTRL_T;

typedef struct _REG_ENTRY_T     REG_ENTRY_T, *P_REG_ENTRY_T;
typedef struct _TABLE_ENTRY_T       TABLE_ENTRY_T, *P_TABLE_ENTRY_T;
typedef struct _TABLE_RF_ENTRY_T       TABLE_RF_ENTRY_T, *P_TABLE_RF_ENTRY_T;



/* Type definition for function pointer of management frame */
typedef VOID (*PROCESS_RX_MGT_FUNCTION)(P_ADAPTER_T, P_SW_RFB_T);

typedef VOID (*IST_EVENT_FUNCTION)(P_ADAPTER_T);

/* Type definition for function pointer of timer handler */
typedef VOID (*PFN_TIMER_CALLBACK)(IN P_ADAPTER_T);


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
#define PACKET_INFO_INIT(_prPacketInfo, \
                         _fgIs802_11, \
                         _fgIs802_1x, \
                         _prPacketDescriptor, \
                         _ucTID, \
                         _ucMacHeaderLength, \
                         _u2PayloadLength, \
                         _pucDestAddr \
                         ) \
        { \
        ((P_PACKET_INFO_T)(_prPacketInfo))->prPacket = (_prPacketDescriptor); \
        ((P_PACKET_INFO_T)(_prPacketInfo))->fgIs802_11 = (_fgIs802_11); \
        ((P_PACKET_INFO_T)(_prPacketInfo))->fgIs1x = (_fgIs802_1x); \
        ((P_PACKET_INFO_T)(_prPacketInfo))->ucTID = (_ucTID); \
        ((P_PACKET_INFO_T)(_prPacketInfo))->ucMacHeaderLength = (_ucMacHeaderLength); \
        ((P_PACKET_INFO_T)(_prPacketInfo))->u2PayloadLength = (_u2PayloadLength); \
        ((P_PACKET_INFO_T)(_prPacketInfo))->pucDestAddr = (_pucDestAddr); \
        };

#define PACKET_INFO_PAYLOAD_LEN(prPacketInfo)   (((P_PACKET_INFO_T)prPacketInfo)->u2PayloadLength)

/*******************************************************************************
*                  F U N C T I O N   D E C L A R A T I O N S
********************************************************************************
*/

/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/
#endif /* _TYPEDEF_H */


