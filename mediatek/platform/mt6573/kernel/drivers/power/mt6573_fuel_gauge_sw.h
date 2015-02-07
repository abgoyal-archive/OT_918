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
 *    mt6573_fuel_gauge_sw.h
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
 * removed!
 * removed!
 *
 *
 *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *============================================================================
 ****************************************************************************/

#ifndef __FUEL_GAUGE_6573_SW_H__
#define __FUEL_GAUGE_6573_SW_H__

// =====================================================================================
// Enum

typedef enum
{
	NO_ACTION_ON_RESET = 0,
	CLEAR_RESET_DETECTION
}fg_reset_sw_control_enum;

typedef enum
{
	NO_ACTION_ON_BIT = 0,
	CLEAR_BIT
}fg_sw_clear_bit_enum;

typedef enum
{
	CMD_NO_ACTION = 0,
	CMD_READ_FG_DATA
}fg_sw_read_command_enum;

typedef enum
{
	BEHAVIOR_CONTINUE = 0,
	BEHAVIOR_RESET_TO_ZERO
}fg_sw_control_fg_behavior_enum;

typedef enum
{
	TIME_CONTINUE = 0,
	TIME_RESET_TO_ZERO
}fg_sw_reset_fg_time_enum;

typedef enum
{
	CHARGE_CONTINUE = 0,
	CHARGE_RESET_TO_ZERO
}fg_sw_reset_fg_charge_enum;

typedef enum
{
	T_X_2048 = 0,
	T_X_0512 = 1,
	T_X_1025 = 2,
	T_X_4096 = 3
}fg_calibration_rate_enum;

typedef enum
{
	DISABLE_AUTO_CALIBRATION = 0,
	FORCE_AUTO_CALIBRATION = 1,
	AUTO_CALIBRATION = 2
}fg_calibration_type_enum;

typedef enum
{
	FG_IDLE = 0,
	FG_ACTIVE = 1
}fg_active_enum;

typedef enum
{
	HW_ERROR = 0,
	HIGHER_THAN_THD = 1,
	LOWER_THAN_THD = 2
}fg_interrupt_check_enum;

// =====================================================================================
// HW Common API

// FGADC CON 0
void fg_reset_sw_control(fg_reset_sw_control_enum val);
void fg_sw_clear(fg_sw_clear_bit_enum val);
kal_uint16 fg_get_data_ready_status(void);
void fg_sw_read_command(fg_sw_read_command_enum val);
void fg_sw_control_fg_behavior(fg_sw_control_fg_behavior_enum val);
void fg_sw_reset_fg_time(fg_sw_reset_fg_time_enum val);
void fg_sw_reset_fg_charge(fg_sw_reset_fg_charge_enum val);
void fg_interrupt_enable(kal_bool enable);
void fg_set_auto_calibration_rate(fg_calibration_rate_enum val);
void fg_set_calibration_type(fg_calibration_type_enum val);
void fg_set_hw_active(fg_active_enum val);

// FGADC CON 1
kal_uint16 fg_get_car(void);

// FGADC CON 2
kal_uint16 fg_get_nter(void);

// FGADC CON 3
void fg_set_battery_low_threshold(kal_uint16 val);

// FGADC CON 4
void fg_set_battery_full_threshold(kal_uint16 val);

// FGADC CON 5
kal_uint16 fg_get_current(void);

// FGADC CON 6
void fg_set_adjust_offset_value(kal_uint16 val);

// FGADC CON 7
fg_interrupt_check_enum fg_get_higher_or_lower_thd(void);
kal_uint16 fg_get_reset_detect_debug(void);
void fg_adc_auto_reset(kal_uint16 val);
void fg_dig_test(kal_uint16 val);
void fg_fir_2_bypass(kal_uint16 val);
void fg_fir_1_bypass(kal_uint16 val);
void fg_set_over_sampling_rate(kal_uint16 val);

#endif // #ifndef __FUEL_GAUGE_6573_SW_H__

