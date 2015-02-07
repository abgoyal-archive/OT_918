/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. and/or its licensors.
 * Without the prior written permission of MediaTek inc. and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 */
/* MediaTek Inc. (C) 2011. All rights reserved.
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

#ifndef _SBCHK_BASE_H
#define _SBCHK_BASE_H

/**************************************************************************
 *  HASH CONFIGURATION
 **************************************************************************/
#define HASH_OUTPUT_LEN                     (20)

/**************************************************************************
 *  SBCHK ENGINE PATH
 **************************************************************************/
#define SBCHK_ENGINE_PATH                   "/system/bin/sbchk"

/**************************************************************************
 *  SBCHK ENGINE CHECK
 **************************************************************************/
#define SBCHK_ENGINE_HASH_CHECK             (0)

/**************************************************************************
 *  SBCHK ENGINE HASH VALUE
 **************************************************************************/
#if SBCHK_ENGINE_HASH_CHECK

#error must fill the hash value of '/system/bin/sbchk'

/* 
   Kernel will compare these two hash values to check if 
   the current '/system/bin/sbchk' is the one you expect.

   To ensure the hash value you fill is right. 
   The steps to obtain hash value are listed below;
   
   (1) Turn off SBCHK_ENGINE_HASH_CHECK
   
   (2) Download images and record kernel log   
   
   (3) Find the string pattern '[SBCHK_BASE]' in kernel log   
   
   (4) The hash value of current '/system/bin/sbchk' is calculated       
   
       [SBCHK_BASE] Calculate the hash value of '/system/bin/sbchk' =
       xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx       
       
   (5) Fill hash value in SBCHK_ENGINE_HASH     
   
   However, the object of '/system/bin/sbchk' may be changed
   if compile tool chain is updated or customer modify this user space program  
   
   Before delivering boot image, 
   please double check if the hash value should be updated or not.
*/

//#define SBCHK_ENGINE_HASH "3a816d2e275818cb12b839a10e838a1e10d729f7"
#define SBCHK_ENGINE_HASH ?????????????????????????????????????

#endif

/**************************************************************************
 *  ERROR CODE
 **************************************************************************/
#define SEC_OK                              (0x0000)
#define SBCHK_BASE_ENGINE_OPEN_FAIL         (0x1000)
#define SBCHK_BASE_ENGINE_READ_FAIL         (0x1001)
#define SBCHK_BASE_HASH_INIT_FAIL           (0x1002)
#define SBCHK_BASE_HASH_DATA_FAIL           (0x1003)
#define SBCHK_BASE_HASH_CHECK_FAIL          (0x1004)

/**************************************************************************
 *  EXTERNAL FUNCTION
 **************************************************************************/
extern void sbchk_base(void);

#endif   /*_SBCHK_BASE*/
