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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/nic_eeprom.h#2 $
*/

/*! \file   "nic_eeprom.h"
    \brief  The declaration of nic eeprom functions

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
** $Log: nic_eeprom.h $
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\9 2009-06-24 11:24:46 GMT mtk01090
**  Add build option BUILD_USE_EEPROM and compile option CFG_SUPPORT_EXT_CONFIG for NVRAM support
**  \main\maintrunk.MT5921\8 2008-11-13 20:35:01 GMT mtk01104
**  Set xtal trim to correct default value if EEPROM is invalid
**  \main\maintrunk.MT5921\7 2008-08-31 11:51:34 GMT mtk01104
**  For some coding alignment
**  \main\maintrunk.MT5921\6 2008-08-02 16:22:01 GMT mtk01104
**  Add GPIO1,2 daisy chain related definition and variable
**  \main\maintrunk.MT5921\5 2008-04-10 23:55:49 GMT mtk01385
**  1. adopt EEPROM version 3 setting.
**  \main\maintrunk.MT5921\4 2008-03-31 00:28:04 GMT mtk01385
**  1. Add flag to indicate EEPROM is exist/valid or not.
**  \main\maintrunk.MT5921\3 2008-02-25 16:08:41 GMT mtk01385
**  1. add eeprom get available phy type set function.
**  \main\maintrunk.MT5921\2 2008-01-31 17:33:30 GMT mtk01385
**  1. Init version.
*/
#ifndef _NIC_EEPROM_H
#define _NIC_EEPROM_H

/*******************************************************************************
*                         C O M P I L E R   F L A G S
********************************************************************************
*/



/*******************************************************************************
*                              C O N S T A N T S
********************************************************************************
*/
/*EEPROM section*/
/* Host interface dependent  */
/* SDIO */
#define EEPROM_SDIO_CCCR                        0x01 /* SDIO[3:0], CCCR[3:0], 4'h0, SD[3:0] */
#define EEPROM_SDIO_SRW                         0x02 /* SRW, S4MI, SCSI, SDC, SMB, LSC, 4BLS, SMPC, SHS 7'h0 */
#define EEPROM_SDIO_IO_CODE                     0x03 /* 4'h0, IO code[3:0], 8'h0 */
#define EEPROM_SDIO_SPS                         0x04 /* 7'h0, SPS, 8'h0 */
#define EEPROM_SDIO_OCR_LOWER                   0x05 /* OCR[7:0], OCR[15:8] */
#define EEPROM_SDIO_OCR_HIGHER                  0x06 /* OCR[23:16], 8'h0 */
#define EEPROM_DEBUG                            0x07 /*2'h0, debug_en, dbg_port2_sel, dbg_port1_sel, dbg_port0_sel, dbg_byte_sel[1:0], hif_debug_sel[7:0]*/
#define EEPROM_SDRAM_CFG                        0x08 /*2'h0, RC4_SRAM_DLY, TR_SRAM_DLY, WT_SRAM_DLY, PTN_SRAM_DLY, MAC_SRAM_DLY, BBP_SRAM_DLY*/
/*MP chip*/
#define EEPROM_SDIO_HIF_CTL_MP                  0x09 /*7'h0,sdio_test_option,4'h0, hif_ctrl_odc, hif_data_odc*/
#define EEPROM_CIS_START_MP                     0x0A /* CIS0 start(b15~b8), reserved(b7~b0) */
#define EEPROM_CIS_LEN_MP                       0x0B /* [15:8]: CIS 1 length, [7:0]: CIS 0 length */
/*MPW chip*/
#define EEPROM_CIS_START_MPW                    0x09 /* CIS0 start(b15~b8), reserved(b7~b0) */
#define EEPROM_CIS_LEN_MPW                      0x0A /* [15:8]: CIS 1 length, [7:0]: CIS 0 length */
#define EEPROM_INTERFACE_CFG_CHKSUM             0x0C /* checksum(b15~b8), reserved(b7~b0) */
#define EEPROM_CHECKSUM_MASK                    BITS(8,15)
#define EEPROM_REG_DOMAIN                       0x0F /* regulatory domain */
#define EEPROM_OSC_STABLE_TIME                  0x10 /* OSC Stable Time in us */
#define EEPROM_LED_MODE_XTAL_FREQ_TRIM          0x11 /* LED configuration and XTAL_Freq_Trim*/
#define EEPROM_LED_MODE_MASK                    BITS(0,3)
#define EEPROM_LED_MODE_DISABLE                 0x0000
#define EEPROM_LED_MODE_1                       0x0001
#define EEPROM_LED_MODE_2                       0x0002
#define EEPROM_XTAL_FREQ_MASK                   BITS(8,15)
#define EEPROM_XTAL_FREQ_OFFSET                 8
#define EEPROM_CLK_CFG_VERSION                  0x12 /* Slow clock Config and EEPROM Version*/
#define EEPROM_LAYOUT_VERSION_MASK              BITS(8,15)
#define EEPROM_LAYOUT_VERSION_OFFSET            8
#define EEPROM_LAYOUT_VERSION_1                 (1<<EEPROM_LAYOUT_VERSION_OFFSET)
#define EEPROM_LAYOUT_VERSION_2                 (2<<EEPROM_LAYOUT_VERSION_OFFSET)
#define EEPROM_LAYOUT_VERSION_3                 (3<<EEPROM_LAYOUT_VERSION_OFFSET)
#define EEPROM_SLOW_CLK_CFG_MASK                BIT(0)
#define EEPROM_SLOW_CLK_CFG_INTERNAL         0
#define EEPROM_SLOW_CLK_CFG_EXTERNAL        1


#define EEPROM_MAC_ADDR_BYTE_1_0                0x13 /* MAC address [15:0] */
#define EEPROM_MAC_ADDR_BYTE_3_2                0x14 /* MAC address [31:16] */
#define EEPROM_MAC_ADDR_BYTE_5_4                0x15 /* MAC address [47:32] */
#define EEPROM_THERMO_USAGE_BAND_SEL            0x16 /* Thermo-Sensor Usage & Band Selection*/
#define EEPROM_BAND_MODE_MASK                   BITS(0,1)
#define EEPROM_PHY_MODE_G                       0x0000
#define EEPROM_PHY_MODE_A_G                     0x0001
#define EEPROM_PHY_MODE_A                       0x0002
#define EEPROM_PHY_MODE_RESERVED                0x0003
#define EEPROM_THERMO_ALC_EN_MASK               BIT(8)
#define EEPROM_THERMO_ALC_EN                    BIT(8)
#define EEPROM_THERMO_LNA_EN_MASK               BIT(9)
#define EEPROM_THERMO_LNA_EN                    BIT(9)
#define EEPROM_THERMO_VGA_SLOPE                 0x17 /* Thermo-Sensor Slope & VGA Gain Slope*/
#define EEPROM_VGA_SLOPE_MASK                   BITS(0,7)
#define EEPROM_VGA_SLOPE_OFFSET                 0
#define EEPROM_THERMO_SLOPE_MASK                BITS(8,15)
#define EEPROM_THERMO_SLOPE_OFFSET              8/* CCK TX Power Gain Table for 2.4G band */
#define EEPROM_THERMO_SLOPE_DEFAULT_VALUE       0x0A
#define EEPROM_VGA_THERMO_SLOPE_BASE            20
#define EEPROM_2G_CCK_TXPWR_GAIN_START          0x18 /*Tuple {TX power gain, EIRP, thermo-value} CCK in each 2.4G channel.*/
#define EEPROM_2G_CCK_TXPWR_GAIN_END            0x2C/* OFDM TX Power Gain Table for 2.4G band */
#define EEPROM_2G_OFDM0_TXPWR_GAIN_START        0x2D  /*Tuple {TX power gain, EIRP, thermo-value} OFDM 6_9M in each 2.4G channel.*/
#define EEPROM_2G_OFDM0_TXPWR_GAIN_END          0x41
#define EEPROM_2G_OFDM1_TXPWR_GAIN_START        0x42  /*Tuple {TX power gain, EIRP, thermo-value} OFDM 12_18M in each 2.4G channel.*/
#define EEPROM_2G_OFDM1_TXPWR_GAIN_END          0x56
#define EEPROM_2G_OFDM2_TXPWR_GAIN_START        0x57  /*Tuple {TX power gain, EIRP, thermo-value} OFDM 24_36M in each 2.4G channel.*/
#define EEPROM_2G_OFDM2_TXPWR_GAIN_END          0x6B
#define EEPROM_2G_OFDM3_TXPWR_GAIN_START        0x6C  /*Tuple {TX power gain, EIRP, thermo-value} OFDM 48_54M in each 2.4G channel.*/
#define EEPROM_2G_OFDM3_TXPWR_GAIN_END          0x80/*RX LNA Control Threshold*/
#define EEPROM_LNA_CONTROL_THRESHOLD_START      0x81  /*Tuple {LNA_Turbo temperature difference, LNA_Restore temperature difference, Thermo-value}.*/
#define EEPROM_LNA_CONTROL_THRESHOLD_END        0x82/*2.4G RCPI Offset Table*/
#define EEPROM_2G_RCPI_OFFSET_TABLE_START       0x83  /*Compensate for the RCPI value with -128 ~ +127 about RF variant in each 2.4G channel.*/
#define EEPROM_2G_RCPI_OFFSET_TABLE_END         0x89/* EEPROM offset for NIC setting section checksum */
#define EEPROM_NIC_CHKSUM_ADD_DW                0x9F
#define EEPROM_NIC_CHKSUM_MASK                  BITS(8,15)
#define EEPROM_NIC_CHKSUM_START_ADD_DW          0x0D/* EEPROM offset for HIF section checksum */
#define EEPROM_HIF_CHKSUM_MP                    0x0C
#define EEPROM_HIF_CHKSUM_MASK_MP               BITS(8,15)
#define EEPROM_HIF_CHKSUM_START_MP              0x01
#define EEPROM_HIF_CHKSUM_MPW                   0x0B
#define EEPROM_HIF_CHKSUM_MASK_MPW              BITS(8,15)
#define EEPROM_HIF_CHKSUM_START_MPW             0x01

/* Default values if EEPROM is not valid */
#define EEPROM_XTAL_TRIM_VAL_DEFAULT            0x40
#define EEPROM_OSC_STABLE_TIME_VAL_DEFAULT      1900    /* unit of us */
#define EEPROM_ALC_USE_THERMO_EN_VAL_DEFAULT    TRUE
#define EEPROM_LNA_USE_THERMO_EN_VAL_DEFAULT    TRUE
#define EEPROM_DAISY_CHAIN_VAL_DEFAULT          0x00

/*++version 3.0*/
#define EEPROM_V3_THERMO_INFO                      0x81
#define EEPROM_V3_THERMO_INFO_ABS_TEMP_MASK        BITS(0,7)
#define EEPROM_V3_THERMO_INFO_ABS_TEMP_OFFSET      0
#define EEPROM_V3_THERMO_INFO_THERMO_VALUE_MASK    BITS(8,15)
#define EEPROM_V3_THERMO_INFO_THERMO_VALUE_OFFSET  8
#define EEPROM_V3_THERMO_INFO_ABS_TEMP_DEFAULT     25
#define EEPROM_V3_THERMO_INFO_THERMO_VAL_DEFAULT   28
/*--version 3.0*/

#define EEPROM_RATE_GROUP_CCK                   0x0
#define EEPROM_RATE_GROUP_OFDM_6_9M             0x1
#define EEPROM_RATE_GROUP_OFDM_12_18M           0x2
#define EEPROM_RATE_GROUP_OFDM_24_36M           0x3
#define EEPROM_RATE_GROUP_OFDM_48_54M           0x4
#define EEPROM_RATE_GROUP_NUM                   5

/* The masked result is 8-bit value comparision */
#define EEPROM_DAISY                            0x82
#define EEPROM_DAISY_GPIO1_MASK                 BIT(0)
#define EEPROM_DAISY_GPIO1_DAISY                BIT(0)
#define EEPROM_DAISY_GPIO1_UNSPEC               0
#define EEPROM_DAISY_GPIO2_MASK                 BIT(1)
#define EEPROM_DAISY_GPIO2_DAISY                BIT(1)
#define EEPROM_DAISY_GPIO2_UNSPEC               0

/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/


struct _EEPROM_CTRL_T {
    UINT_8         ucID;   /* ? */
    UINT_8         ucQD;   /* ? */

    /* The following values will be extracted from EEPROM, othwise
     * use default value
     */
    UINT_8         aucMacAddress[MAC_ADDR_LEN];
    UINT_8         ucDaisyChain;
    UINT_8         ucXtalTrim;
    UINT_8         ucLedBlinkMode;  /* Phase out */
    UINT_8         ucSlowClkCfg;    /* Phase out, always use external clock */
    UINT_8         ucBandSelect;
    UINT_8         ucVgaGainSlop;   /* Slope of TX VGA gain steps relative to
                                     * 20 degrees temperature increment
                                     */
    UINT_8         ucThermoSensorSlop;  /* Slope of Thermo-Sensor value relative
                                         * to 20 degrees temperature increment
                                         */
    INT_8          cAbsTemp;
    UINT_8         ucThermoValue;   /*The corresponding thermo value with cAbsTemp */
    UINT_16        u2OscStableTimeUs;
    BOOLEAN        fgAlcUseThermoEn;
    BOOLEAN        fgLnaUseThermoEn;
    UINT_32        u4RegulationDomain;

    /* Not used for MT5921 internal RF */
    UINT_32        u4RFInitTable_24_Size;
    PUINT_32       pu4RFInitTable_24;

    PUINT_32       pu4EepromChCfgTable_24;
    BOOLEAN        fgIsEepromValid;
};

/* Per Channel Tx configuration structure in EEPROM */
typedef struct _EEPROM_TX_CFG_ENTRY {
    UINT_8      ucPowerGain;
    UINT_8      ucEIRP;
    UINT_8      ucThermoVal;
} EEPROM_TX_CFG_ENTRY, *P_EEPROM_TX_CFG_ENTRY;

/* Rx configuration structure in EEPROM */
typedef struct _EEPROM_LNA_CFG_ENTRY {
    UINT_8      ucTurboTempDiff;
    UINT_8      ucRestoreTempDiff;
    UINT_8      ucThermoVal;
} EEPROM_LNA_CFG_ENTRY, *P_EEPROM_LNA_CFG_ENTRY;


/* Per Channel configuration structure from EEPROM*/
typedef struct _EEPROM_CHANNEL_CFG_ENTRY {
    UINT_8                  ucChannelNum;
    UINT_32                 u4ChannelFreq;
    ENUM_BAND_T             eBand;
    EEPROM_TX_CFG_ENTRY     rTxCfg[EEPROM_RATE_GROUP_NUM];
    INT_8                   cRcpiOffset;
} EEPROM_CHANNEL_CFG_ENTRY, *P_EEPROM_CHANNEL_CFG_ENTRY;


/*******************************************************************************
*                    E X T E R N A L   R E F E R E N C E S
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
#if CFG_SUPPORT_EXT_CONFIG
WLAN_STATUS
nicExtReadCfg (
    IN P_ADAPTER_T prAdapter,
    OUT P_EEPROM_CTRL_T prEEPROMCtrl
    );
#endif

WLAN_STATUS
nicEepromReadCfg (
    IN P_ADAPTER_T prAdapter,
    OUT P_EEPROM_CTRL_T prEEPROMCtrl
    );

UINT_16
nicEepromLoad (
    IN  P_ADAPTER_T prAdapter,
    OUT PUINT_8     paucEeprom,
    IN  UINT_16     u2EepromSzIn
    );

VOID
nicEepromCalculateChecksumByte (
    IN  PUINT_8 paucEepromBuf,
    IN  UINT_16 u2LenByte,
    OUT PUINT_8 pucRetChksum
    );

BOOL
nicEepromVerify (
    IN  P_ADAPTER_T prAdapter,
    IN  PUINT_8     paucEepromBuf
    );

BOOL
nicEepromStoreCfgV2 (
    IN  P_ADAPTER_T prAdapter,
    IN  PUINT_16       pau2Eeprom,
    OUT P_EEPROM_CTRL_T prEEPROMCtrl
    );

VOID
nicEepromGetAvailablePhyTypeSet (
    IN  P_EEPROM_CTRL_T prEEPROMCtrl,
    OUT PUINT_16        pu2AvailablePhyTypeSet
    );

BOOL
nicEepromStoreCfgV3 (
    IN  P_ADAPTER_T prAdapter,
    IN  PUINT_16       pau2Eeprom,
    OUT P_EEPROM_CTRL_T prEEPROMCtrl
    );

#endif /* _NIC_EEPROM_H */


