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
*  permission of MediaTek Inc. (C) 2008
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
 *   mt6573_pm_factory.c
 *
 * Project:
 * --------
 *   MT6573
 *
 * Description:
 * ------------
 *   MT6573 Sleep  
 *
 * Author:
 * -------
 *   Chun-Wei Chen (mtk03506)
 *
 ****************************************************************************/

/******************************************************************************
 * MT6573 Power Factory Mode Support 
 *****************************************************************************/

#include <linux/autoconf.h>
#include <linux/kernel.h>
#include <linux/mm.h>
#include <linux/interrupt.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/pm.h>
#include <linux/suspend.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/delay.h>
#include <linux/wait.h>
#include <linux/leds.h>

#include "mach/mt6573_reg_base.h"
#include "mach/irqs.h"
#include "mach/mt6573_pll.h"
#include "mach/mt6573_typedefs.h"
#include "mach/sync_write.h"
#include "mach/mt6573_ost_sm.h"

#include "pmu6573_hw.h"
#include "pmu6573_sw.h"
#include "upmu_common_sw.h"
#include "cust_leds.h"

/*****************************************************************************
 * REGISTER
 ****************************************************************************/


/*****************************************************************************
 * LOCAL CONST DEFINATION
 ****************************************************************************/


/******************************************************************************
 * Gloabal Variable Defination
 *****************************************************************************/
static struct mtk_irq_mask mask;

extern int mt65xx_leds_brightness_set(enum mt65xx_led_type type, enum led_brightness level);
extern int mt6573_irq_mask_all(struct mtk_irq_mask *mask);
extern int mt6573_irq_mask_restore(struct mtk_irq_mask *mask);
extern int DISP_PanelEnable(BOOL bEnable);
extern int DISP_PowerEnable(BOOL bEnable);
 
#ifdef IDLE_LOW_POWER_TEST
void enable_low_power_settings(void)
{
    int ret;
    printk("mt6573_pm_factory: enable low power settings\n");
        
    //ARM 169MHz
    PLL_Fsel(MT65XX_APMCU_PLL, APMCU_F8_MHZ);
    
    //BL
    mt65xx_leds_brightness_set(MT65XX_LED_TYPE_LCD, 0);
    
    //Turn Off LCD 
    DISP_PanelEnable(FALSE);
    DISP_PowerEnable(FALSE);	

    //Save interrupt status 
    ret = mt6573_irq_mask_all(&mask);
    if (!ret) {
        printk("success to mask all irq lines\n");
    } else {
        printk("fail to mask all irq lines\n");
    }
   
    mt6573_irq_unmask(MT6573_KEYPAD_IRQ_LINE);
}
#endif

#ifdef IDLE_LOW_POWER_TEST
void disable_low_power_settings(void)
{
    int turbo_mode, ret;
    printk("mt6573_pm_factory: disable low power settings\n");
    
    turbo_mode = (DRV_Reg32(0xF7024104) & 0x10000000) >> 28;
    
    //Restore interrupt mask
    ret = mt6573_irq_mask_restore(&mask);
    if (!ret) {
        printk("success to restore all irq lines\n");
    } else {
        printk("fail to restore all irq lines\n");
    }

    //Turn On LCD  
    DISP_PowerEnable(TRUE);
    DISP_PanelEnable(TRUE);	
    
    //BL
    mt65xx_leds_brightness_set(MT65XX_LED_TYPE_LCD, LED_FULL);
    
    if (turbo_mode)
    {
        //ARM 806MHz
        PLL_Fsel(MT65XX_APMCU_PLL, APMCU_F1_TM_MHZ);
    }
    else
    {
        //ARM 676MHz
        PLL_Fsel(MT65XX_APMCU_PLL, APMCU_F1_MHZ);
    }
}
#endif

static int __init pm_factory_init(void)
{
    /* */
    return 0;
}

static void __exit pm_factory_exit(void)
{
    /* */
}

module_init(pm_factory_init);
module_exit(pm_factory_exit);

MODULE_DESCRIPTION("Power management factory mode driver for mt6573");
MODULE_LICENSE("GPL");

