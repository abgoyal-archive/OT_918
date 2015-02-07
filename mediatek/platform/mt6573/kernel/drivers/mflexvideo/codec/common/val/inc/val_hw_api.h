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

/** 
 * @file 
 *   val_hw_api.h 
 *
 * @par Project:
 *   MFlexVideo 
 *
 * @par Description:
 *   Video Abstraction Layer HW APIs
 *
 * @par Author:
 *   Jackal Chen (mtk02532)
 *
 * @par $Revision: #5 $
 * @par $Modtime:$
 * @par $Log:$
 *
 */

#ifndef _VAL_HW_API_H_
#define _VAL_HW_API_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "val_types.h"
#include "mfv_drv_base.h"

/*=============================================================================
 *                             Function Declaration
 *===========================================================================*/

/**
* @par Function       
*   eVideoRegIsr
* @par Description    
*   register isr function  
* @param              
*   a_prParam         [IN/OUT]   The VAL_ISR_T structure
* @param              
*   a_u4ParamSize     [IN]       The size of VAL_ISR_T
* @par Returns        
*   VAL_RESULT_T
*/
VAL_RESULT_T eVideoRegIsr(
    VAL_ISR_T *a_prParam, 
    VAL_UINT32_T a_u4ParamSize
);

/**
* @par Function       
*   eVideoFreeIsr
* @par Description    
*   free isr function  
* @param              
*   a_prParam         [IN/OUT]   The VAL_ISR_T structure
* @param              
*   a_u4ParamSize     [IN]       The size of VAL_ISR_T
* @par Returns        
*   VAL_RESULT_T
*/
VAL_RESULT_T eVideoFreeIsr(
    VAL_ISR_T *a_prParam, 
    VAL_UINT32_T a_u4ParamSize
);

/**
* @par Function       
*   eVideoCleanCache
* @par Description    
*   clean cache for given memory range  
* @param              
*   a_prParam         [IN/OUT]   The VAL_CACHE_T structure
* @param              
*   a_u4ParamSize     [IN]       The size of VAL_CACHE_T
* @par Returns        
*   VAL_RESULT_T
*/
VAL_RESULT_T eVideoCleanCache(
    VAL_CACHE_T *a_prParam, 
    VAL_UINT32_T a_u4ParamSize
);

/**
* @par Function       
*   eVideoFlushCache
* @par Description    
*   flush cache for given memory range  
* @param              
*   a_prParam         [IN/OUT]   The VAL_CACHE_T structure
* @param              
*   a_u4ParamSize     [IN]       The size of VAL_CACHE_T
* @par Returns        
*   VAL_RESULT_T
*/
VAL_RESULT_T eVideoFlushCache(
    VAL_CACHE_T *a_prParam, 
    VAL_UINT32_T a_u4ParamSize
);

/**
* @par Function       
*   eVideoMfvWriteReg
* @par Description    
*   write MFV register
* @param              
*   a_prParam         [IN/OUT]   The MFV_DRV_CMD_T structure
* @param              
*   a_u4ParamSize     [IN]       The size of MFV_DRV_CMD_T
* @par Returns        
*   VAL_RESULT_T
*/
VAL_RESULT_T eVideoMfvWriteReg(
    MFV_DRV_CMD_T   *a_prParam, 
    VAL_UINT32_T    a_u4ParamSize
);

/**
* @par Function       
*   eVideoMfvReadReg
* @par Description    
*   read MFV register
* @param              
*   a_prParam         [IN/OUT]   The MFV_DRV_CMD_T structure
* @param              
*   a_u4ParamSize     [IN]       The size of MFV_DRV_CMD_T
* @par Returns        
*   VAL_RESULT_T
*/
VAL_RESULT_T eVideoMfvReadReg(
    MFV_DRV_CMD_T   *a_prParam, 
    VAL_UINT32_T    a_u4ParamSize
);

/**
* @par Function       
*   eVideoMfvWriteSysRam
* @par Description    
*   write MFV sys ram
* @param              
*   a_prParam         [IN/OUT]   The MFV_DRV_CMD_T structure
* @param              
*   a_u4ParamSize     [IN]       The size of MFV_DRV_CMD_T
* @par Returns        
*   VAL_RESULT_T
*/
VAL_RESULT_T eVideoMfvWriteSysRam(
    MFV_DRV_CMD_T   *a_prParam, 
    VAL_UINT32_T    a_u4ParamSize
);

/**
* @par Function       
*   eVideoMfvWriteSysRamRange
* @par Description    
*   write MFV sys ram range
* @param              
*   a_prParam         [IN/OUT]   The MFV_DRV_CMD_T structure
* @param              
*   a_u4ParamSize     [IN]       The size of MFV_DRV_CMD_T
* @par Returns        
*   VAL_RESULT_T
*/
VAL_RESULT_T eVideoMfvWriteSysRamRange(
    MFV_DRV_CMD_T   *a_prParam, 
    VAL_UINT32_T    a_u4ParamSize
);

/**
* @par Function       
*   eMfvReadReg
* @par Description    
*   read MFV sys ram
* @param              
*   a_prParam         [IN/OUT]   The MFV_DRV_CMD_T structure
* @param              
*   a_u4ParamSize     [IN]       The size of MFV_DRV_CMD_T
* @par Returns        
*   VAL_RESULT_T
*/
VAL_RESULT_T eVideoMfvReadSysRam(
    MFV_DRV_CMD_T   *a_prParam, 
    VAL_UINT32_T    a_u4ParamSize
);

/**
* @par Function       
*   u4MfvHWRead
* @par Description    
*   read MFV HW address
* @param              
*   a_u4Addr        [IN]    The read address (Physical address)
* @par Returns        
*   VAL_UINT32_T    [OUT]   The read value
*/
VAL_UINT32_T u4MfvHWRead(
    VAL_UINT32_T   a_u4Addr
);

/**
* @par Function       
*   u4MfvHWRead
* @par Description    
*   write MFV HW address
* @param              
*   a_u4Addr        [IN]    The write address (Physical address)
* @param              
*   a_u4Value       [IN]    The value to be write
* @par Returns        
*   VAL_UINT32_T    
*/
VAL_UINT32_T u4MfvHWWrite(
    VAL_UINT32_T   a_u4Addr,
    VAL_UINT32_T   a_u4Value
);

#ifdef __cplusplus
}
#endif

#endif // #ifndef _VAL_HW_API_H_
