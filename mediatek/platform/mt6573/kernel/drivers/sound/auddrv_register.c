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


/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2009
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
/*******************************************************************************
 *
 * Filename:
 * ---------
 *   auddrv_afe_reg.c
 *
 * Project:
 * --------
 *   MT6573 Android
 *
 * Description:
 * ------------
 *   AudioSys AFE HW function
 *
 * Author:
 * -------
 *   Stan Huang (mtk01728)
 *
 *
 *------------------------------------------------------------------------------
 * $Revision$
 * $Modtime:$
 * $Log:$
 *
 *
 *******************************************************************************/

/*****************************************************************************
*                     C O M P I L E R   F L A G S
******************************************************************************
*/

/*****************************************************************************
*                E X T E R N A L   R E F E R E N C E S
******************************************************************************
*/
#include <mach/mt6573_typedefs.h>
#include <linux/spinlock.h>

#include <linux/kernel.h>
#include <linux/io.h>
#include <asm/system.h>

#include "auddrv_register.h"
#include "auddrv_def.h"

/*****************************************************************************
*                          C O N S T A N T S
******************************************************************************
*/

/*****************************************************************************
*                         D A T A   T Y P E S
******************************************************************************
*/

/*****************************************************************************
*                        F U N C T I O N   D E F I N I T I O N
******************************************************************************
*/
void Afe_Set_Reg(kal_uint32 offset, kal_uint32 value , kal_uint32 mask)
{
   volatile kal_uint32 address = (AFE_BASE+offset);
   volatile kal_uint32 *AFE_Register = (volatile kal_uint32*)address;

   volatile kal_uint32 val_tmp;
   PRINTK_AFE_REG("Afe_Set_Reg offset=%x, value=%x, mask=%x \n",offset,value,mask);
   val_tmp = READ_REGISTER_UINT32(AFE_Register);
   val_tmp &= (~mask);
   mt65xx_reg_sync_writel(val_tmp,AFE_Register);
   val_tmp = READ_REGISTER_UINT32(AFE_Register);
   val_tmp |= (value&mask);
   mt65xx_reg_sync_writel(val_tmp,AFE_Register);

/*
   *AFE_Register &= (~mask);
   dsb();
   *AFE_Register |= (value&mask);
   dsb();
*/
}

kal_uint32 Afe_Get_Reg(kal_uint32 offset)
{
   volatile kal_uint32 address = (AFE_BASE+offset);
   volatile kal_uint32 *Analog_Register = (volatile kal_uint32 *)address;
   volatile kal_uint32 val_tmp;
   val_tmp = READ_REGISTER_UINT32(Analog_Register);
   PRINTK_AFE_REG("Afe_Get_Reg offset=%x, value=%d \n",offset,*value);
   return val_tmp;
}

void Ana_Set_Reg(kal_uint32 offset, kal_uint32 value, kal_uint32 mask)
{
   volatile kal_uint32 address = (offset);
   volatile kal_uint32 *Analog_Register = (volatile kal_uint32 *)address;

   volatile kal_uint32 val_tmp;
   PRINTK_ANA_REG("Ana_Set_Reg offset=%x, value=%x, mask=%x \n",offset,value,mask);
   val_tmp = READ_REGISTER_UINT32(Analog_Register);
   val_tmp &= (~mask);
   mt65xx_reg_sync_writel(val_tmp,Analog_Register);
   val_tmp = READ_REGISTER_UINT32(Analog_Register);
   val_tmp |= (value&mask);
   mt65xx_reg_sync_writel(val_tmp,Analog_Register);

/*
   *Analog_Register &= (~mask);
   dsb();
   *Analog_Register |= (value&mask);
   dsb();
*/
}

kal_uint32 Ana_Get_Reg(kal_uint32 offset)
{
   volatile kal_uint32 *value;
   UINT32 address = (offset);
   PRINTK_ANA_REG("Ana_Get_Reg offset=%x \n",offset);

   value = (volatile kal_uint32  *)(address);
   return *value;
}

// TBD...
void Afe_Enable_Memory_Power()
{
   // No need to enable memory power
   return;
}

// TBD...
void Afe_Disable_Memory_Power()
{
   // No need to disable memory power
   return;
}




