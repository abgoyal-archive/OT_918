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
 *
 * Filename:
 * ---------
 *    pmu6573_hw.h
 *
 * Project:
 * --------
 *   Android_Software
 *
 * Description:
 * ------------
 *   This file is intended for PMIC 6573 driver.
 *
 * Author:
 * -------
 * -------
 *
 ****************************************************************************/

#ifndef __PMU6573_HW_H__
#define __PMU6573_HW_H__
#include <mach/pmic_features.h>
#include <mach/mt6573_reg_base.h>

#if defined(PMIC_6573_REG_API)

//#define PMU_BASE        0x7002F000
#define PMU_BASE		MIXEDSYS1_BASE
#define PMU_END         (PMU_BASE+0x1000)

///////////////////////////////////////////////////////////////////////////////
// 1. Data Retention group
#define RETENTION_CON0    (PMU_BASE + 0x0080)

///////////////////////////////////////////////////////////////////////////////
// 2. Low Power Oscillator group
#define LPOSC_CON0    (PMU_BASE + 0x0100)

///////////////////////////////////////////////////////////////////////////////
// 3. STRUP  group
#define STRUP_CON0    (PMU_BASE + 0x0200)

///////////////////////////////////////////////////////////////////////////////
// 4. LDO 1 group
#define VA28_CON0    (PMU_BASE + 0x0710)
#define VA25_CON0    (PMU_BASE + 0x0720)
#define VA12_CON0    (PMU_BASE + 0x0620)
#define VRTC_CON0    (PMU_BASE + 0x0628)
#define VMIC_CON0    (PMU_BASE + 0x0630)
#define VTV_CON0    (PMU_BASE + 0x0638)
#define VAUDN_CON0    (PMU_BASE + 0x0640)
#define VAUDP_CON0    (PMU_BASE + 0x0650)
#define PMUA_CON0    (PMU_BASE + 0x0680)

///////////////////////////////////////////////////////////////////////////////
// 5. LDO 2 group
#define VRF_CON0    (PMU_BASE + 0x0700)
#define VCAMA_CON0    (PMU_BASE + 0x0730)
#define VCAMD_CON0    (PMU_BASE + 0x0740)
#define VIO_CON0    (PMU_BASE + 0x0750)
#define VUSB_CON0    (PMU_BASE + 0x0760)
#define VSIM_CON0    (PMU_BASE + 0x0780)
#define VSIM2_CON0    (PMU_BASE + 0x0790)
#define VIBR_CON0    (PMU_BASE + 0x07B0)
#define VMC_CON0    (PMU_BASE + 0x07C0)
#define VCAMA2_CON0    (PMU_BASE + 0x07D0)
#define VCAMD2_CON0    (PMU_BASE + 0x07E0)
#define VM12_CON0    (PMU_BASE + 0x0800)
#define VM12_INT_CON0    (PMU_BASE + 0x0810)

///////////////////////////////////////////////////////////////////////////////
// 6. BUCK group
#define VCORE_CON0    (PMU_BASE + 0x0900)
#define VIO1V8_CON0    (PMU_BASE + 0x0920)
#define VAPROC_CON0    (PMU_BASE + 0x0940)
#define VRF1V8_CON0    (PMU_BASE + 0x0960)

///////////////////////////////////////////////////////////////////////////////
// 7. BOOST group
#define PMIC_BB_CON0    (PMU_BASE + 0x0B00)

///////////////////////////////////////////////////////////////////////////////
// 8. KPLED group
#define KPLED_CON0    (PMU_BASE + 0x0C80)

///////////////////////////////////////////////////////////////////////////////
// 9. OC group
#define PMIC_OC_CON0    (PMU_BASE + 0x0E00)

///////////////////////////////////////////////////////////////////////////////
// 10. CHR
#define CHR_CON0    (PMU_BASE + 0x0A00)

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#endif // #if defined(PMIC_6573_REG_API)

#endif // #ifndef __PMU6573_HW_H__

