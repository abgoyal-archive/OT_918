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

/* linux/arch/arm/mach-mt6516/mt6516_rfkill.c
 *
 * (C) Copyright 2008
 * MediaTek <www.mediatek.com>
 * JinKwan Huang <jk.huang@mediatek.com>
 *
 * MT6516 RFKILL Driver -- Control bluetooth power
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*******************************************************************************
*                E X T E R N A L   R E F E R E N C E S
********************************************************************************
*/
#include <linux/kernel.h>
#include <linux/module.h>
#include <mach/mt6573_gpio.h>
#include <mach/mt_combo.h>
#include <cust_gpio_usage.h>
#include <mach/mt6573_boot.h>
#include <mach/mt6573_pll.h>
extern void combo_audio_pin_conf(COMBO_AUDIO_STATE state);

/*******************************************************************************
*                          C O N S T A N T S
********************************************************************************
*/

/*******************************************************************************
*                       P R I V A T E   D A T A
********************************************************************************
*/
static void (*cmb_bgf_eirq_cb)(void) = NULL;
static int (*cmb_audio_ctrl_cb)(u32, u32) = NULL;
static void (*cmb_func_ctrl_cb)(u32, u32) = NULL;
static void (*cmb_binfo_ctrl_cb)(u32, u32) = NULL;
static COMBO_AUDIO_STATE cmb_audio_state = COMBO_AUDIO_STATE_0;

/*******************************************************************************
*                          F U N C T I O N S
********************************************************************************
*/
int mt_combo_init (struct combo_ctrl *ctrl)
{
    if (!ctrl || ctrl->size != sizeof(struct combo_ctrl)) {
        printk(KERN_WARNING "[COMBO] invalid ctrl:0x%p size(%d)\n", ctrl, (ctrl) ? ctrl->size: 0);
        return -1;
    }

    printk(KERN_INFO "[COMBO] mt_combo_init ctrl:0x%p size(%d)\n", ctrl, ctrl->size);

    cmb_bgf_eirq_cb = ctrl->bgf_eirq_cb;
    cmb_audio_ctrl_cb = ctrl->audio_ctrl_cb;
    cmb_func_ctrl_cb = ctrl->func_ctrl_cb;
    cmb_binfo_ctrl_cb = ctrl->binfo_ctrl_cb;

    return 0;
}
EXPORT_SYMBOL(mt_combo_init);

int mt_combo_deinit (struct combo_ctrl *ctrl)
{
    cmb_bgf_eirq_cb = NULL;
    cmb_audio_ctrl_cb = NULL;
    cmb_func_ctrl_cb = NULL;
    cmb_binfo_ctrl_cb = NULL;
    cmb_audio_state = COMBO_AUDIO_STATE_0;
    return 0;
}
EXPORT_SYMBOL(mt_combo_deinit);

/* stub functions for kernel interrupt handler */
void mt_combo_bgf_eirq_handler (void* par)
{
    printk(KERN_INFO "[COMBO]mt_combo_bgf_eirq_handler \n");

        /* avoid the early interrupt before we register the eirq_handler */
    if (cmb_bgf_eirq_cb){
        cmb_bgf_eirq_cb();
    }

    return;
}

/* stub functions for kernel to control audio path pin mux */
int mt_combo_audio_ctrl_ex (COMBO_AUDIO_STATE state, u32 clt_ctrl)
{
    int ret = -1;
    int pin_share = 1;//I2S, PCM Pin sharing ?
    int pin_flag = 0;
    
    if (get_chip_eco_ver() == CHIP_E1) {
        pin_share = 1;
        pin_flag |= COMBO_AUDIO_PIN_SHARE;
        printk(KERN_INFO "[COMBO] CHIP_E1 PCM/I2S pin_share configruation \n");

    }
    else{ //E1 later
        pin_share = 0;
        pin_flag |= COMBO_AUDIO_PIN_SEPARATE;
        printk(KERN_INFO "[COMBO] CHIP_E2 PCM/I2S pin_separate configruation \n");

    }
    
    /* FIXME:host first or chip first? */

    /* set host side first */
    switch (state) {
    case COMBO_AUDIO_STATE_0:
        /* BT_PCM_OFF & FM line in/out */
        pin_flag |= COMBO_AUDIO_BT_PCM_OFF;
        pin_flag |= COMBO_AUDIO_FM_LINEIN;
#if 0        
        if(pin_share){
            mt_set_gpio_mode(GPIO_PCM_DAICLK_PIN, GPIO_PCM_DAICLK_PIN_M_GPIO);
            mt_set_gpio_dir(GPIO_PCM_DAICLK_PIN, GPIO_DIR_OUT);
            mt_set_gpio_out(GPIO_PCM_DAICLK_PIN, GPIO_OUT_ZERO);

            mt_set_gpio_mode(GPIO_PCM_DAIPCMOUT_PIN, GPIO_PCM_DAIPCMOUT_PIN_M_GPIO);
            mt_set_gpio_dir(GPIO_PCM_DAIPCMOUT_PIN, GPIO_DIR_OUT);
            mt_set_gpio_out(GPIO_PCM_DAIPCMOUT_PIN, GPIO_OUT_ZERO);

            mt_set_gpio_mode(GPIO_PCM_DAIPCMIN_PIN, GPIO_PCM_DAIPCMIN_PIN_M_GPIO);
            mt_set_gpio_dir(GPIO_PCM_DAIPCMIN_PIN, GPIO_DIR_OUT);
            mt_set_gpio_out(GPIO_PCM_DAIPCMIN_PIN, GPIO_OUT_ZERO);

            mt_set_gpio_mode(GPIO_PCM_DAISYNC_PIN, GPIO_PCM_DAISYNC_PIN_M_GPIO);
            mt_set_gpio_dir(GPIO_PCM_DAISYNC_PIN, GPIO_DIR_OUT);
            mt_set_gpio_out(GPIO_PCM_DAISYNC_PIN, GPIO_OUT_ZERO);
        } else {
            /*BT_PCM_OFF*/ 
            mt_set_gpio_mode(GPIO_PCM_DAICLK_PIN, GPIO_PCM_DAICLK_PIN_M_GPIO);
            mt_set_gpio_dir(GPIO_PCM_DAICLK_PIN, GPIO_DIR_OUT);
            mt_set_gpio_out(GPIO_PCM_DAICLK_PIN, GPIO_OUT_ZERO);

            mt_set_gpio_mode(GPIO_PCM_DAIPCMOUT_PIN, GPIO_PCM_DAIPCMOUT_PIN_M_GPIO);
            mt_set_gpio_dir(GPIO_PCM_DAIPCMOUT_PIN, GPIO_DIR_OUT);
            mt_set_gpio_out(GPIO_PCM_DAIPCMOUT_PIN, GPIO_OUT_ZERO);

            mt_set_gpio_mode(GPIO_PCM_DAIPCMIN_PIN, GPIO_PCM_DAIPCMIN_PIN_M_GPIO);
            mt_set_gpio_dir(GPIO_PCM_DAIPCMIN_PIN, GPIO_DIR_OUT);
            mt_set_gpio_out(GPIO_PCM_DAIPCMIN_PIN, GPIO_OUT_ZERO);

            mt_set_gpio_mode(GPIO_PCM_DAISYNC_PIN, GPIO_PCM_DAISYNC_PIN_M_GPIO);
            mt_set_gpio_dir(GPIO_PCM_DAISYNC_PIN, GPIO_DIR_OUT);
            mt_set_gpio_out(GPIO_PCM_DAISYNC_PIN, GPIO_OUT_ZERO);

            /*FM_I2S1_OFF*/
            mt_set_gpio_mode(GPIO200, GPIO_PCM_DAIPCMOUT_PIN_M_GPIO);
            mt_set_gpio_dir(GPIO200, GPIO_DIR_OUT);
            mt_set_gpio_out(GPIO200, GPIO_OUT_ZERO);

            mt_set_gpio_mode(GPIO201, GPIO_PCM_DAIPCMIN_PIN_M_GPIO);
            mt_set_gpio_dir(GPIO201, GPIO_DIR_OUT);
            mt_set_gpio_out(GPIO201, GPIO_OUT_ZERO);

            mt_set_gpio_mode(GPIO202, GPIO_PCM_DAISYNC_PIN_M_GPIO);
            mt_set_gpio_dir(GPIO202, GPIO_DIR_OUT);
            mt_set_gpio_out(GPIO202, GPIO_OUT_ZERO);
        }
#endif
        //printk(KERN_DEBUG "[COMBO] disable BT-PCM\n");
        break;
    case COMBO_AUDIO_STATE_1:

        pin_flag |= COMBO_AUDIO_BT_PCM_ON;
        pin_flag |= COMBO_AUDIO_FM_LINEIN;
#if 0  
        if(pin_share){
            /* BT_PCM_ON & FM line in/out */
            mt_set_gpio_mode(GPIO_PCM_DAICLK_PIN, GPIO_PCM_DAICLK_PIN_M_CLK);
            mt_set_gpio_mode(GPIO_PCM_DAIPCMOUT_PIN, GPIO_PCM_DAIPCMOUT_PIN_M_DAIPCMOUT);
            mt_set_gpio_mode(GPIO_PCM_DAIPCMIN_PIN, GPIO_PCM_DAIPCMIN_PIN_M_DAIPCMIN);
            mt_set_gpio_mode(GPIO_PCM_DAISYNC_PIN, GPIO_PCM_DAISYNC_PIN_M_DAISYNC);
        } else {
            /* BT_PCM_ON */
            mt_set_gpio_mode(GPIO_PCM_DAICLK_PIN, GPIO_PCM_DAICLK_PIN_M_CLK);
            mt_set_gpio_mode(GPIO_PCM_DAIPCMOUT_PIN, GPIO_PCM_DAIPCMOUT_PIN_M_DAIPCMOUT);
            mt_set_gpio_mode(GPIO_PCM_DAIPCMIN_PIN, GPIO_PCM_DAIPCMIN_PIN_M_DAIPCMIN);
            mt_set_gpio_mode(GPIO_PCM_DAISYNC_PIN, GPIO_PCM_DAISYNC_PIN_M_DAISYNC);
        
            /*FM_I2S1_OFF*/
            mt_set_gpio_mode(GPIO200, GPIO_PCM_DAIPCMOUT_PIN_M_GPIO);
            mt_set_gpio_dir(GPIO200, GPIO_DIR_OUT);
            mt_set_gpio_out(GPIO200, GPIO_OUT_ZERO);

            mt_set_gpio_mode(GPIO201, GPIO_PCM_DAIPCMIN_PIN_M_GPIO);
            mt_set_gpio_dir(GPIO201, GPIO_DIR_OUT);
            mt_set_gpio_out(GPIO201, GPIO_OUT_ZERO);

            mt_set_gpio_mode(GPIO202, GPIO_PCM_DAISYNC_PIN_M_GPIO);
            mt_set_gpio_dir(GPIO202, GPIO_DIR_OUT);
            mt_set_gpio_out(GPIO202, GPIO_OUT_ZERO);
        }
        //printk(KERN_DEBUG "[COMBO] enable BT-PCM\n");
#endif        
        break;
    case COMBO_AUDIO_STATE_2:

        pin_flag |= COMBO_AUDIO_BT_PCM_OFF;
        pin_flag |= COMBO_AUDIO_FM_I2S;
#if 0  
        if(pin_share){
            /* FM I2S ON*/
            mt_set_gpio_mode(GPIO_I2S0_CK_PIN, GPIO_I2S0_CK_PIN_M_I2S0_CK);
            mt_set_gpio_mode(GPIO_I2S0_DAT_PIN, GPIO_I2S0_DAT_PIN_M_I2S0_DAT);
            mt_set_gpio_mode(GPIO_I2S0_WS_PIN, GPIO_I2S0_WS_PIN_M_I2S0_WS);
            /* BT_PCM_OFF */
            mt_set_gpio_mode(GPIO_PCM_DAIPCMIN_PIN, GPIO_PCM_DAIPCMIN_PIN_M_GPIO);
            mt_set_gpio_dir(GPIO_PCM_DAIPCMIN_PIN, GPIO_DIR_IN);
            mt_set_gpio_out(GPIO_PCM_DAIPCMIN_PIN, 0);
        } else {
            /*FM_I2S_ON*/
            mt_set_gpio_mode(GPIO200, GPIO_MODE_03);
            mt_set_gpio_mode(GPIO201, GPIO_MODE_03);
            mt_set_gpio_mode(GPIO202, GPIO_MODE_03);

            /*BT_PCM_OFF*/ 
            mt_set_gpio_mode(GPIO_PCM_DAICLK_PIN, GPIO_PCM_DAICLK_PIN_M_GPIO);
            mt_set_gpio_dir(GPIO_PCM_DAICLK_PIN, GPIO_DIR_OUT);
            mt_set_gpio_out(GPIO_PCM_DAICLK_PIN, GPIO_OUT_ZERO);

            mt_set_gpio_mode(GPIO_PCM_DAIPCMOUT_PIN, GPIO_PCM_DAIPCMOUT_PIN_M_GPIO);
            mt_set_gpio_dir(GPIO_PCM_DAIPCMOUT_PIN, GPIO_DIR_OUT);
            mt_set_gpio_out(GPIO_PCM_DAIPCMOUT_PIN, GPIO_OUT_ZERO);

            mt_set_gpio_mode(GPIO_PCM_DAIPCMIN_PIN, GPIO_PCM_DAIPCMIN_PIN_M_GPIO);
            mt_set_gpio_dir(GPIO_PCM_DAIPCMIN_PIN, GPIO_DIR_OUT);
            mt_set_gpio_out(GPIO_PCM_DAIPCMIN_PIN, GPIO_OUT_ZERO);

            mt_set_gpio_mode(GPIO_PCM_DAISYNC_PIN, GPIO_PCM_DAISYNC_PIN_M_GPIO);
            mt_set_gpio_dir(GPIO_PCM_DAISYNC_PIN, GPIO_DIR_OUT);
            mt_set_gpio_out(GPIO_PCM_DAISYNC_PIN, GPIO_OUT_ZERO);
        }
#endif
		break;        
    case COMBO_AUDIO_STATE_3:
        //printk(KERN_DEBUG "[COMBO] enable FM-I2S and disable BT-PCM\n");
        pin_flag |= COMBO_AUDIO_BT_PCM_ON;
        pin_flag |= COMBO_AUDIO_FM_I2S;
#if 0
        if(pin_share){

        } else {
            /*FM_I2S_ON*/
            mt_set_gpio_mode(GPIO200, GPIO_MODE_03);
            mt_set_gpio_mode(GPIO201, GPIO_MODE_03);
            mt_set_gpio_mode(GPIO202, GPIO_MODE_03);

            /* BT_PCM_ON */
            mt_set_gpio_mode(GPIO_PCM_DAICLK_PIN, GPIO_PCM_DAICLK_PIN_M_CLK);
            mt_set_gpio_mode(GPIO_PCM_DAIPCMOUT_PIN, GPIO_PCM_DAIPCMOUT_PIN_M_DAIPCMOUT);
            mt_set_gpio_mode(GPIO_PCM_DAIPCMIN_PIN, GPIO_PCM_DAIPCMIN_PIN_M_DAIPCMIN);
            mt_set_gpio_mode(GPIO_PCM_DAISYNC_PIN, GPIO_PCM_DAISYNC_PIN_M_DAISYNC);
        }
#endif
        break;
    default:
        /* FIXME: move to cust folder? */
        printk(KERN_INFO "[COMBO] audio_ctrl invalid state [%d]\n", cmb_audio_state);
        return -1;
        break;
    }
	combo_audio_pin_conf(state);
    printk(KERN_INFO "[COMBO] cmb_audio_ctrl_cb = %p, clt_ctrl= %d\n",
        cmb_audio_ctrl_cb, clt_ctrl);

    /* chip side */
    if (cmb_audio_ctrl_cb && clt_ctrl) {
        ret = cmb_audio_ctrl_cb(state, pin_flag);
    }
    else {
        if (cmb_audio_ctrl_cb) {
            /* skip case */
            ret = 0;
        }
    }

    printk(KERN_INFO "[COMBO] audio_ctrl [%d]->[%d] ret(%d, %d)\n",
        cmb_audio_state, state, ret, (cmb_audio_ctrl_cb) ? 1 : 0);
    cmb_audio_state = state;

    return ret;
}
EXPORT_SYMBOL(mt_combo_audio_ctrl_ex);


void mt_combo_func_ctrl (u32 type, u32 on) {
    if (cmb_func_ctrl_cb) {
        cmb_func_ctrl_cb(type, on);
    }
    else {
        printk(KERN_WARNING "[COMBO] cmb_func_ctrl_cb null \n");
    }
}
EXPORT_SYMBOL(mt_combo_func_ctrl);

void mt_combo_binfo_ctrl (u32 idx, u32 value) {
    if (cmb_binfo_ctrl_cb) {
        cmb_binfo_ctrl_cb(idx, value);
    }
    else {
        printk(KERN_WARNING "[COMBO] cmb_func_binfo_cb null \n");
    }    
}
EXPORT_SYMBOL(mt_combo_binfo_ctrl);

/*platform-related APIs*/
//void clr_device_working_ability(UINT32 clockId, MT6573_STATE state);
//void set_device_working_ability(UINT32 clockId, MT6573_STATE state);

static int _mt_combo_plt_do_deep_idle(COMBO_IF src, int enter){

    int ret = -1;

    const char *combo_if_name[] =
    {   "COMBO_IF_UART", 
        "COMBO_IF_MSDC"   
    };

    if(src != COMBO_IF_UART && src!= COMBO_IF_MSDC){
        printk(KERN_WARNING "[COMBO][%s] src = %d is error\n", __FUNCTION__, src);
        return ret;
    }
    
    if(src >= 0 && src < COMBO_IF_MAX){
        printk(KERN_INFO "[COMBO][%s] src = %s, to enter deep idle? %d \n", 
            __FUNCTION__, 
            combo_if_name[src], 
            enter);
    }

    /*TODO: For Common SDIO configuration, we need to do some judgement between STP and WIFI 
            to decide if the msdc will enter deep idle safely*/

    switch(src){
        case COMBO_IF_UART:            
            if(enter == 0){
		clr_device_working_ability(MT65XX_PDN_PERI_UART3, SLOW_IDLE_STATE);
		clr_device_working_ability(MT65XX_PDN_PERI_UART3, DEEP_IDLE_STATE);
            } else {
		set_device_working_ability(MT65XX_PDN_PERI_UART3, SLOW_IDLE_STATE);
		set_device_working_ability(MT65XX_PDN_PERI_UART3, DEEP_IDLE_STATE);
            }
            ret = 0;
            break;            

        case COMBO_IF_MSDC:
            if(enter == 0){
		clr_device_working_ability(MT65XX_PDN_PERI_MSDC2, SLOW_IDLE_STATE);
		clr_device_working_ability(MT65XX_PDN_PERI_MSDC2, DEEP_IDLE_STATE);
            } else {
		set_device_working_ability(MT65XX_PDN_PERI_MSDC2, SLOW_IDLE_STATE);
		set_device_working_ability(MT65XX_PDN_PERI_MSDC2, DEEP_IDLE_STATE);
            }
            ret = 0;
            break;

        default:
            ret = -1;
            break;
    }

    return ret;
}

int mt_combo_plt_enter_deep_idle(COMBO_IF src){
    return _mt_combo_plt_do_deep_idle(src, 1);
}
EXPORT_SYMBOL(mt_combo_plt_enter_deep_idle);

int mt_combo_plt_exit_deep_idle(COMBO_IF src){
    return _mt_combo_plt_do_deep_idle(src, 0);
}    
EXPORT_SYMBOL(mt_combo_plt_exit_deep_idle);
