/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. and/or its licensors.
 * Without the prior written permission of MediaTek inc. and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 *
 * MediaTek Inc. (C) 2010. All rights reserved.
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

/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2005
*
*  BY OPENING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
*  THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
*  RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON
*  AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
*  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
*  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
*  NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
*  SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
*  SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK ONLY TO SUCH
*  THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
*  NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S
*  SPECIFICATION OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
*
*  BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE
*  LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
*  AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
*  OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY BUYER TO
*  MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
*
*  THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE
*  WITH THE LAWS OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF
*  LAWS PRINCIPLES.  ANY DISPUTES, CONTROVERSIES OR CLAIMS ARISING THEREOF AND
*  RELATED THERETO SHALL BE SETTLED BY ARBITRATION IN SAN FRANCISCO, CA, UNDER
*  THE RULES OF THE INTERNATIONAL CHAMBER OF COMMERCE (ICC).
*
*****************************************************************************/

/*****************************************************************************
 *
 * Filename:
 * ---------
 *    mt6573_fuel_gauge_hw.h
 *
 * Project:
 * --------
 *   Maui_Software
 *
 * Description:
 * ------------
 *   This file is intended for 6573 fuel gauge driver.
 *
 * Author:
 * -------
 * -------
 *
 *============================================================================
 *             HISTORY
 * Below this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *------------------------------------------------------------------------------
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *============================================================================
 ****************************************************************************/

#ifndef __FUEL_GAUGE_6573_HW_H__
#define __FUEL_GAUGE_6573_HW_H__

#define FGADC_CON0    (0xF702EB80)
#define FGADC_CON1    (0xF702EB84)
#define FGADC_CON2    (0xF702EB88)
#define FGADC_CON3    (0xF702EB8C)
#define FGADC_CON4    (0xF702EB90)
#define FGADC_CON5    (0xF702EB94)
#define FGADC_CON6    (0xF702EB98)
#define FGADC_CON7    (0xF702EB9C)

#define PLL_CON6_BASE_ADDR		(0xF702E118)
#define FG_PLL_CON0_BASE_ADDR	(0xF702E340)

//#define UNIT_FGCURRENT 	(146718) 	// 146.718 uA
//#define UNIT_FGTIME 	(16) 		// 0.16s
//#define UNIT_FGCHARGE 	(6574581) 	// 0.006574581 uAh

#define UNIT_FGCURRENT 	(158122) 	// 158.122 uA
//#define UNIT_FGCURRENT 	(158935) 	// 158.935 uA
#define UNIT_FGTIME 	(16) 		// 0.16s
//#define UNIT_FGCHARGE 	(21961412) 	// 0.021961412 uAh //6329
#define UNIT_FGCHARGE 	(7085603) 	// 0.007085603 uAh //6573

//FGADC CON 0
#define FG_SW_RSTCLR_MASK        0x0001
#define FG_SW_RSTCLR_SHIFT       0

#define FG_SW_CLEAR_MASK        0x0002
#define FG_SW_CLEAR_SHIFT       1

#define FG_LATCHDATA_ST_MASK        0x0004
#define FG_LATCHDATA_ST_SHIFT       2

#define FG_SW_READ_PRE_MASK        0x0008
#define FG_SW_READ_PRE_SHIFT       3

#define FG_SW_CR_MASK        0x0010
#define FG_SW_CR_SHIFT       4

#define FG_TIME_RST_MASK        0x0020
#define FG_TIME_RST_SHIFT       5

#define FG_CHARGE_RST_MASK        0x0040
#define FG_CHARGE_RST_SHIFT       6

#define FG_INT_EN_MASK        0x0080
#define FG_INT_EN_SHIFT       7

#define FG_AUTOCALRATE_MASK        0x0300
#define FG_AUTOCALRATE_SHIFT       8

#define FG_CAL_MASK        0x0C00
#define FG_CAL_SHIFT       10

#define FG_ON_MASK        0x1000
#define FG_ON_SHIFT       12

//FGADC CON 1
#define FG_CAR_MASK        0xFFFF
#define FG_CAR_SHIFT       0

//FGADC CON 2
#define FG_NTER_MASK        0xFFFF
#define FG_NTER_SHIFT       0

//FGADC CON 3
#define FG_BLTR_MASK        0xFFFF
#define FG_BLTR_SHIFT       0

//FGADC CON 4
#define FG_BFTR_MASK        0xFFFF
#define FG_BFTR_SHIFT       0

//FGADC CON 5
#define FG_CURRENT_OUT_MASK        0xFFFF
#define FG_CURRENT_OUT_SHIFT       0

//FGADC CON 6
#define FG_ADJUST_OFFSET_VALUE_MASK        0xFFFF
#define FG_ADJUST_OFFSET_VALUE_SHIFT       0

//FGADC CON 7
#define FG_ISR_MASK        0x0003
#define FG_ISR_SHIFT       0

#define FG_ADC_RSTDETECT_MASK        0x0004
#define FG_ADC_RSTDETECT_SHIFT       2

#define FG_ADC_AUTORST_MASK        0x0008
#define FG_ADC_AUTORST_SHIFT       3

#define FG_DIG_TEST_MASK        0x0010
#define FG_DIG_TEST_SHIFT       4

#define FG_FIR2BYPASS_MASK        0x0020
#define FG_FIR2BYPASS_SHIFT       5

#define FG_FIR1BYPASS_MASK        0x0040
#define FG_FIR1BYPASS_SHIFT       6

#define FG_OSR_MASK        0x0380
#define FG_OSR_SHIFT       7

#endif // #ifndef __FUEL_GAUGE_6573_HW_H__

