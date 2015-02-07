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

/******************************************************************************
 * mt6573_gpt.c - This file is for the GPT/XGPT module !
 *
 * DESCRIPTION: -
 *     This file is a kernel module that includes essential functions about
 *     GPT/XGPT module !
 *
 * modification history
 * ----------------------------------------
 * 2010/08/24, v0.1 by Terry Chang
 * 2010/09/01, v0.2 by Terry Chang
 * ----------------------------------------
 ******************************************************************************/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/spinlock.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/cnt32_to_63.h>
#include <linux/proc_fs.h>

#include <asm/tcm.h>
#include <asm/delay.h>

#include <mach/mt6573_reg_base.h>
#include <mach/mt6573_gpt.h>
#include <mach/timer.h>
#include <mach/irqs.h>

/******************************************************************************
 Debug Control
******************************************************************************/

//#define MT6573_GPT_XGPT_DEBUG
#ifdef MT6573_GPT_XGPT_DEBUG
#define GPT_DEBUG printk
#define XGPT_DEBUG printk
#else
#define GPT_DEBUG(x,...)
#define XGPT_DEBUG(x,...)
#endif

// mask it when using 26MHz
#define XGPT_CLOCK_32K  
#ifdef XGPT_CLOCK_32K
	XGPT_NUM g_XGPT = XGPT4; 
	#define XGPT_CLOCK_VALUE 32768
#else 
  XGPT_NUM g_XGPT = XGPT1; 	
  #define XGPT_CLOCK_VALUE (26 * 1000 * 1000)
#endif


/* GPT registers */
#define MT6573_GPT1_CON         (APMCU_GPTIMER_BASE + 0x0000)
#define MT6573_GPT1_DAT         (APMCU_GPTIMER_BASE + 0x0004)
#define MT6573_GPT2_CON         (APMCU_GPTIMER_BASE + 0x0008)
#define MT6573_GPT2_DAT         (APMCU_GPTIMER_BASE + 0x000c)
#define MT6573_GPT_STA          (APMCU_GPTIMER_BASE + 0x0010)
#define MT6573_GPT1_PRESCALE    (APMCU_GPTIMER_BASE + 0x0014)
#define MT6573_GPT2_PRESCALE    (APMCU_GPTIMER_BASE + 0x0018)
#define MT6573_GPT3_CON         (APMCU_GPTIMER_BASE + 0x001c)
#define MT6573_GPT3_DAT         (APMCU_GPTIMER_BASE + 0x0020)
#define MT6573_GPT3_PRESCALE    (APMCU_GPTIMER_BASE + 0x0024)
#define MT6573_GPT4_CON         (APMCU_GPTIMER_BASE + 0x0028)
#define MT6573_GPT4_DAT         (APMCU_GPTIMER_BASE + 0x002c)

/* XGPT registers */
#define MT6573_XGPT_IRQEN       (APXGPT_BASE + 0x0000)
#define MT6573_XGPT_IRQSTA      (APXGPT_BASE + 0x0004)
#define MT6573_XGPT_IRQACK      (APXGPT_BASE + 0x0008)
#define MT6573_XGPT1_CON        (APXGPT_BASE + 0x0010)
#define MT6573_XGPT1_PRESCALE   (APXGPT_BASE + 0x0014)
#define MT6573_XGPT1_COUNT      (APXGPT_BASE + 0x0018)
#define MT6573_XGPT1_COMPARE    (APXGPT_BASE + 0x001c)
#define MT6573_XGPT2_CON        (APXGPT_BASE + 0x0020)
#define MT6573_XGPT2_PRESCALE   (APXGPT_BASE + 0x0024)
#define MT6573_XGPT2_COUNT      (APXGPT_BASE + 0x0028)
#define MT6573_XGPT2_COMPARE    (APXGPT_BASE + 0x002c)
#define MT6573_XGPT3_CON        (APXGPT_BASE + 0x0030)
#define MT6573_XGPT3_PRESCALE   (APXGPT_BASE + 0x0034)
#define MT6573_XGPT3_COUNT      (APXGPT_BASE + 0x0038)
#define MT6573_XGPT3_COMPARE    (APXGPT_BASE + 0x003c)
#define MT6573_XGPT4_CON        (APXGPT_BASE + 0x0040)
#define MT6573_XGPT4_PRESCALE   (APXGPT_BASE + 0x0044)
#define MT6573_XGPT4_COUNT      (APXGPT_BASE + 0x0048)
#define MT6573_XGPT4_COMPARE    (APXGPT_BASE + 0x004c)
#define MT6573_XGPT5_CON        (APXGPT_BASE + 0x0050)
#define MT6573_XGPT5_PRESCALE   (APXGPT_BASE + 0x0054)
#define MT6573_XGPT5_COUNT      (APXGPT_BASE + 0x0058)
#define MT6573_XGPT5_COMPARE    (APXGPT_BASE + 0x005c)
#define MT6573_XGPT6_CON        (APXGPT_BASE + 0x0060)
#define MT6573_XGPT6_PRESCALE   (APXGPT_BASE + 0x0064)
#define MT6573_XGPT6_COUNT      (APXGPT_BASE + 0x0068)
#define MT6573_XGPT6_COMPARE    (APXGPT_BASE + 0x006c)
#define MT6573_XGPT7_CON        (APXGPT_BASE + 0x0070)
#define MT6573_XGPT7_PRESCALE   (APXGPT_BASE + 0x0074)
#define MT6573_XGPT7_COUNT      (APXGPT_BASE + 0x0078)
#define MT6573_XGPT7_COMPARE    (APXGPT_BASE + 0x007c)

/******************************************************************************
 GPT-Related Setting
******************************************************************************/

#define GPT_CON_ENABLE1 0x8000
#define GPT_CON_ENABLE2 0x0001

const UINT32 g_gpt_addr_con[GPT_TOTAL_COUNT] = { MT6573_GPT1_CON, MT6573_GPT2_CON,
MT6573_GPT3_CON, MT6573_GPT4_CON };

const UINT32 g_gpt_addr_clk[GPT_TOTAL_COUNT] = { MT6573_GPT1_PRESCALE, MT6573_GPT2_PRESCALE,
MT6573_GPT3_PRESCALE, 0 };

const UINT32 g_gpt_addr_dat[GPT_TOTAL_COUNT] = { MT6573_GPT1_DAT, MT6573_GPT2_DAT,
MT6573_GPT3_DAT, MT6573_GPT4_DAT };

static UINT32 g_gpt_status[GPT_TOTAL_COUNT] = { NOT_USED, NOT_USED, NOT_USED, NOT_USED };

static DEFINE_SPINLOCK(g_gpt_lock);
static unsigned long g_gpt_flags;

/******************************************************************************
 XGPT-Related Setting
******************************************************************************/

#define XGPT_CON_ENABLE 0x0001
#define XGPT_CON_CLEAR 0x0002

const UINT32 g_xgpt_mask[XGPT_TOTAL_COUNT] = { 0x0001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040 };

const UINT32 g_xgpt_addr_con[XGPT_TOTAL_COUNT] = { MT6573_XGPT1_CON, MT6573_XGPT2_CON,
MT6573_XGPT3_CON, MT6573_XGPT4_CON, MT6573_XGPT5_CON, MT6573_XGPT6_CON, MT6573_XGPT7_CON };

const UINT32 g_xgpt_addr_clk[XGPT_TOTAL_COUNT] = { MT6573_XGPT1_PRESCALE, MT6573_XGPT2_PRESCALE,
MT6573_XGPT3_PRESCALE, MT6573_XGPT4_PRESCALE, MT6573_XGPT5_PRESCALE, MT6573_XGPT6_PRESCALE, MT6573_XGPT7_PRESCALE };

const UINT32 g_xgpt_addr_cnt[XGPT_TOTAL_COUNT] = { MT6573_XGPT1_COUNT, MT6573_XGPT2_COUNT,
MT6573_XGPT3_COUNT, MT6573_XGPT4_COUNT, MT6573_XGPT5_COUNT, MT6573_XGPT6_COUNT, MT6573_XGPT7_COUNT };

const UINT32 g_xgpt_addr_compare[XGPT_TOTAL_COUNT] = { MT6573_XGPT1_COMPARE, MT6573_XGPT2_COMPARE,
MT6573_XGPT3_COMPARE, MT6573_XGPT4_COMPARE, MT6573_XGPT5_COMPARE, MT6573_XGPT6_COMPARE, MT6573_XGPT7_COMPARE };

static UINT32 g_xgpt_status[XGPT_TOTAL_COUNT] = { NOT_USED, NOT_USED,
NOT_USED, NOT_USED, NOT_USED, NOT_USED, NOT_USED };

static DEFINE_SPINLOCK(g_xgpt_lock);
static unsigned long g_xgpt_flags;

/******************************************************************************
 Timer Handler
******************************************************************************/

//GPT1~2 Handle Function
static GPT_Func g_gpt_func;

//XGPT2~7 Handle Function
static XGPT_Func g_xgpt_func;

/******************************************************************************
 Tasklet that will call user registered call-back function
******************************************************************************/

static void GPT1_Tasklet(unsigned long arg)
{
    if (g_gpt_func.gpt1_func != NULL)
    {
        g_gpt_func.gpt1_func(GPT1);
    }
    else
    {   printk("g_gpt_func.gpt1_fun (arg:%lu) = NULL!\n", arg);
    }
}

static void GPT2_Tasklet(unsigned long arg)
{
    if (g_gpt_func.gpt2_func != NULL)
    {
        g_gpt_func.gpt2_func(GPT2);
    }
    else
    {   printk("g_gpt_func.gpt2_fun (arg:%lu) = NULL!\n", arg);
    }
}

static void XGPT2_Tasklet(unsigned long arg)
{
    if (g_xgpt_func.xgpt2_func != NULL)
    {
        g_xgpt_func.xgpt2_func(XGPT2);
    }
    else
    {   printk("g_xgpt_func.xgpt2_fun (arg:%lu) = NULL!\n", arg);
    }
}

static void XGPT3_Tasklet(unsigned long arg)
{
    if (g_xgpt_func.xgpt3_func != NULL)
    {
        g_xgpt_func.xgpt3_func(XGPT3);
    }
    else
    {   printk("g_xgpt_func.xgpt3_fun (arg:%lu) = NULL!\n", arg);
    }
}

static void XGPT4_Tasklet(unsigned long arg)
{
    if (g_xgpt_func.xgpt4_func != NULL)
    {
        g_xgpt_func.xgpt4_func(XGPT4);
    }
    else
    {   printk("g_xgpt_func.xgpt4_fun (arg:%lu) = NULL!\n", arg);
    }
}

static void XGPT5_Tasklet(unsigned long arg)
{
    if (g_xgpt_func.xgpt5_func != NULL)
    {
        g_xgpt_func.xgpt5_func(XGPT5);
    }
    else
    {   printk("g_xgpt_func.xgpt5_fun (arg:%lu) = NULL!\n", arg);
    }
}

static void XGPT6_Tasklet(unsigned long arg)
{
    if (g_xgpt_func.xgpt6_func != NULL)
    {
        g_xgpt_func.xgpt6_func(XGPT6);
    }
    else
    {   printk("g_xgpt_func.xgpt6_fun (arg:%lu) = NULL!\n", arg);
    }
}

static void XGPT7_Tasklet(unsigned long arg)
{
    if (g_xgpt_func.xgpt7_func != NULL)
    {
        g_xgpt_func.xgpt7_func(XGPT7);
    }
    else
    {   printk("g_xgpt_func.xgpt7_fun (arg:%lu) = NULL!\n", arg);
    }
}

static DECLARE_TASKLET(g_gpt1_tlet, GPT1_Tasklet, 0);
static DECLARE_TASKLET(g_gpt2_tlet, GPT2_Tasklet, 0);
static DECLARE_TASKLET(g_xgpt2_tlet, XGPT2_Tasklet, 0);
static DECLARE_TASKLET(g_xgpt3_tlet, XGPT3_Tasklet, 0);
static DECLARE_TASKLET(g_xgpt4_tlet, XGPT4_Tasklet, 0);
static DECLARE_TASKLET(g_xgpt5_tlet, XGPT5_Tasklet, 0);
static DECLARE_TASKLET(g_xgpt6_tlet, XGPT6_Tasklet, 0);
static DECLARE_TASKLET(g_xgpt7_tlet, XGPT7_Tasklet, 0);

/******************************************************************************
 * DESCRIPTION:
 *   Check whether GPT is running or not
 * PARAMETERS:
 *   GPT number
 * RETURNS:
 *   TRUE : running
 *   FALSE: stop
 ******************************************************************************/
BOOL GPT_IsStart(GPT_NUM numGPT)
{
    UINT32 mask = GPT_CON_ENABLE1;

    if (numGPT == GPT3 || numGPT == GPT4)
        mask = GPT_CON_ENABLE2;

    return (DRV_Reg32(g_gpt_addr_con[numGPT]) & mask) ? TRUE : FALSE;
}

/******************************************************************************
 * DESCRIPTION:
 *   Start GPT Timer
 * PARAMETERS:
 *   GPT number
 ******************************************************************************/
void GPT_Start(GPT_NUM numGPT)
{
    if (numGPT != GPT3 && numGPT != GPT4) {
        spin_lock_irqsave(&g_gpt_lock, g_gpt_flags);

        DRV_SetReg32(g_gpt_addr_con[numGPT], GPT_CON_ENABLE1);
        g_gpt_status[numGPT] = USED;

        spin_unlock_irqrestore(&g_gpt_lock, g_gpt_flags);
    }
}

/******************************************************************************
 * DESCRIPTION:
 *   Stop GPT Timer
 * PARAMETERS:
 *   GPT number (GPT1~2)
 ******************************************************************************/
void GPT_Stop(GPT_NUM numGPT)
{
    if (numGPT != GPT3 && numGPT != GPT4) {
        spin_lock_irqsave(&g_gpt_lock, g_gpt_flags);

       	DRV_ClrReg32(g_gpt_addr_con[numGPT], GPT_CON_ENABLE1);
       	g_gpt_status[numGPT] = NOT_USED;

        spin_unlock_irqrestore(&g_gpt_lock, g_gpt_flags);
    }
}

/******************************************************************************
 * DESCRIPTION:
 *   This function is used to set GPT mode
 *   (GPT_ONE_SHOT,GPT_REPEAT)
 * PARAMETERS:
 *   GPT number (GPT1~2) and GPT Mode
 ******************************************************************************/
void GPT_SetOpMode(GPT_NUM numGPT, GPT_CON_MODE mode)
{
    UINT32 gptMode;

    if (numGPT != GPT3 && numGPT != GPT4) {
        spin_lock_irqsave(&g_gpt_lock, g_gpt_flags);

        gptMode = DRV_Reg32(g_gpt_addr_con[numGPT]) & 0xbfff;   //clear mode bit
        gptMode |= mode;
        DRV_WriteReg32(g_gpt_addr_con[numGPT], gptMode);

        spin_unlock_irqrestore(&g_gpt_lock, g_gpt_flags);
    }
}

/******************************************************************************
 * DESCRIPTION:
 *   This function is used to get GPT mode
 *   (GPT_ONE_SHOT,GPT_REPEAT)
 * PARAMETERS:
 *   GPT number (GPT1~2)
 * RETURNS:
 *   GPT Mode
 ******************************************************************************/
GPT_CON_MODE GPT_GetOpMode(GPT_NUM numGPT)
{
    UINT32 u4Mode;

    u4Mode = DRV_Reg32(g_gpt_addr_con[numGPT]) & 0x4000;    //get mode bit

    return u4Mode;
}

/******************************************************************************
 * DESCRIPTION:
 *   This function is used to set GPT clock divisor
 *   (GPT_CLK_DIV_1,GPT_CLK_DIV_2,GPT_CLK_DIV_4,GPT_CLK_DIV_8,
 *    GPT_CLK_DIV_16,GPT_CLK_DIV_32,GPT_CLK_DIV_64,GPT_CLK_DIV_128)
 * PARAMETERS:
 *   GPT number (GPT1~2) and clock divisor
 ******************************************************************************/
void GPT_SetClkDivisor(GPT_NUM numGPT, GPT_CLK_DIV clkDiv)
{
    if (numGPT != GPT3 && numGPT != GPT4) {
        spin_lock_irqsave(&g_gpt_lock, g_gpt_flags);

        DRV_WriteReg32(g_gpt_addr_clk[numGPT], clkDiv);

        spin_unlock_irqrestore(&g_gpt_lock, g_gpt_flags);
    }
}

/******************************************************************************
 * DESCRIPTION:
 *   This function is used to get GPT clock divisor
 *   (GPT_CLK_DIV_1,GPT_CLK_DIV_2,GPT_CLK_DIV_4,GPT_CLK_DIV_8,
 *    GPT_CLK_DIV_16,GPT_CLK_DIV_32,GPT_CLK_DIV_64,GPT_CLK_DIV_128)
 * PARAMETERS:
 *   GPT number (GPT1~2)
 * RETURNS:
 *   GPT clock divisor
 ******************************************************************************/
GPT_CLK_DIV GPT_GetClkDivisor(GPT_NUM numGPT)
{
    if (numGPT != GPT4)
        return DRV_Reg32(g_gpt_addr_clk[numGPT]);

    return 0;
}

/******************************************************************************
 * DESCRIPTION:
 *   This function is used to set GPT timeout value
 * PARAMETERS:
 *   GPT number (GPT1~2)
 ******************************************************************************/
void GPT_SetTimeout(GPT_NUM numGPT, UINT32 u4Dat)
{
    if (numGPT != GPT3 && numGPT != GPT4) {
        spin_lock_irqsave(&g_gpt_lock, g_gpt_flags);

       	DRV_WriteReg32(g_gpt_addr_dat[numGPT], u4Dat);

        spin_unlock_irqrestore(&g_gpt_lock, g_gpt_flags);
    }
}

/******************************************************************************
 * DESCRIPTION:
 *   This function is used to get GPT timeout value
 * PARAMETERS:
 *   GPT number (GPT1~2)
 * RETURNS:
 *   GPT counter value
 ******************************************************************************/
UINT32 GPT_GetTimeout(GPT_NUM numGPT)
{
    return DRV_Reg32(g_gpt_addr_dat[numGPT]);
}

/******************************************************************************
 * DESCRIPTION:
 *   This function is used to config GPT register
 *   (1) mode
 *   (2) clkDiv
 *   (3) bIrqEnable
 *   (4) u4Compare
 * PARAMETERS:
 *   GPT configuration data structure
 * RETURNS:
 *   TRUE : config GPT pass
 *   FALSE: config GPT fail
 ******************************************************************************/
BOOL GPT_Config(GPT_CONFIG config)
{
    GPT_NUM num = config.num;
    GPT_CON_MODE mode = config.mode;
    GPT_CLK_DIV clkDiv = config.clkDiv;
    UINT32 u4Timeout = config.u4Timeout;
    BOOL bRet = TRUE;

    if (num == GPT3 || num == GPT4)
   	{
   	    printk("GPT_Config : MT6573 GPT3 and GPT4 shouldn't be used\n");
        return FALSE;
   	}

   	if (GPT_IsStart(num))
   	{
   	    printk("GPT_Config : MT6573 GPT%d is already in use\n", num + 1);
   	    return FALSE;
   	}
   	else
   	{   GPT_DEBUG("GPT_Config : MT6573 GPT%d is free to use\n", num + 1);
   	}

    GPT_SetOpMode(num, mode);
    if (GPT_GetOpMode(num) != mode)
    {
        bRet = FALSE;
    }

    GPT_SetClkDivisor(num, clkDiv);
    if (GPT_GetClkDivisor(num) != clkDiv)
    {
        bRet = FALSE;
    }

    //GPT interrupt is enable

    GPT_SetTimeout(num, u4Timeout);
    if (GPT_GetTimeout(num) != u4Timeout)
    {
        bRet = FALSE;
    }

    return bRet;
}

/******************************************************************************
 * DESCRIPTION:
 *   Register GPT1~2 interrupt handler (call back function)
 * PARAMETERS:
 *   GPT number (GPT1~2) and handler
 ******************************************************************************/
void GPT_Init(GPT_NUM timerNum, void (*GPT_Callback)(UINT16))
{
    if (timerNum == GPT1)
    {
        g_gpt_func.gpt1_func = GPT_Callback;
    }
    else if (timerNum == GPT2)
    {
        g_gpt_func.gpt2_func = GPT_Callback;
    }
}

/******************************************************************************
 *   GPT LISR to handle GPT1~2 interrupt
 *   ( it will schedule corresonding GPT tasklet )
 ******************************************************************************/
static irqreturn_t __tcmfunc GPT_LISR(int irq, void *dev_id)
{
    UINT32 u4GPT;

    u4GPT = DRV_Reg32(MT6573_GPT_STA);
    GPT_DEBUG("GPT_LISR : MT6573_GPT_STA = %x\n", u4GPT);

    if (u4GPT & 0x0001)
    {
        tasklet_schedule(&g_gpt1_tlet);
    }
    if (u4GPT & 0x0002)
    {
        tasklet_schedule(&g_gpt2_tlet);
    }

   	return IRQ_HANDLED;
}

/******************************************************************************
 * DESCRIPTION:
 *   Enable Interrupt of XGPT
 * PARAMETERS:
 *   XGPT Number (XGPT2~7)
 ******************************************************************************/
void XGPT_EnableIRQ(XGPT_NUM numXGPT)
{
    if (numXGPT != g_XGPT) {
        spin_lock_irqsave(&g_xgpt_lock, g_xgpt_flags);

        DRV_SetReg32(MT6573_XGPT_IRQEN, g_xgpt_mask[numXGPT]);

        spin_unlock_irqrestore(&g_xgpt_lock, g_xgpt_flags);
    }
}

/******************************************************************************
 * DESCRIPTION:
 *   Disable Interrupt of XGPT
 * PARAMETERS:
 *   XGPT Number (XGPT2~7)
 ******************************************************************************/
void XGPT_DisableIRQ(XGPT_NUM numXGPT)
{
    if (numXGPT != g_XGPT) {
        spin_lock_irqsave(&g_xgpt_lock, g_xgpt_flags);

        DRV_ClrReg32(MT6573_XGPT_IRQEN, g_xgpt_mask[numXGPT]);

        spin_unlock_irqrestore(&g_xgpt_lock, g_xgpt_flags);
    }
}

/******************************************************************************
 * DESCRIPTION:
 *   Check XGPT Interrupt is enable or disable
 * PARAMETERS:
 *   XGPT Number (XGPT1~7)
 * RETURNS:
 *   TRUE : Interrupt is enabled
 *   FALSE: Interrupt is not enabled
 ******************************************************************************/
BOOL XGPT_IsIRQEnable(XGPT_NUM numXGPT)
{
    return (DRV_Reg32(MT6573_XGPT_IRQEN) & g_xgpt_mask[numXGPT]) ? TRUE : FALSE;
}

/******************************************************************************
 * DESCRIPTION:
 *   This function is to read IRQ status. if none of gpt channel has issued an interrupt
 *   ,then the return value is XGPT_TOTAL_COUNT.
 *   Otherwise, the return value would be the number of gpt has issued an interrupt
 * RETURNS:
 *   numXGPT : XGPT Number
 *           (XGPT1,XGPT2,XGPT3,XGPT4,XGPT5,XGPT6,XGPT7)
 ******************************************************************************/
static XGPT_NUM __tcmfunc XGPT_Get_IRQSTA(void)
{
    BOOL sta;
    UINT32 numXGPT;

    sta = DRV_Reg32(MT6573_XGPT_IRQSTA);
    XGPT_DEBUG("XGPT_IRQ 0x%x 2:\r\n", sta);
    
    for (numXGPT = XGPT1; numXGPT < XGPT_TOTAL_COUNT; numXGPT++)
    {
        if (sta & g_xgpt_mask[numXGPT])
            break;
    }

    return numXGPT;
}

/******************************************************************************
 * DESCRIPTION:
 *   This function is used to check XGPT's IRQ status
 * PARAMETERS:
 *   XGPT number (XGPT1~7)
 * RETURNS:
 *   TRUE : xgpt channel has issued an interrupt.
 *   FALSE: xgpt channel hasn't issued an interrupt.
 ******************************************************************************/
BOOL XGPT_Check_IRQSTA(XGPT_NUM numXGPT)
{
    BOOL sta;

    sta = DRV_Reg32(MT6573_XGPT_IRQSTA);
    XGPT_DEBUG("XGPT_IRQ 0x%x 1:\r\n", sta);
    return (sta & g_xgpt_mask[numXGPT]);
}

/******************************************************************************
 * DESCRIPTION:
 *   Clean IRQ status bit by writing IRQ ack bit
 * PARAMETERS:
 *   XGPT number
 ******************************************************************************/
static void __tcmfunc XGPT_AckIRQ(XGPT_NUM numXGPT)
{
    spin_lock(&g_xgpt_lock);

    DRV_WriteReg32(MT6573_XGPT_IRQACK, g_xgpt_mask[numXGPT]);

    spin_unlock(&g_xgpt_lock);
}

/******************************************************************************
 * DESCRIPTION:
 *   Check whether XGPT is running or not
 * PARAMETERS:
 *   XGPT number
 * RETURNS:
 *   TRUE : running
 *   FALSE: stop
 ******************************************************************************/
BOOL XGPT_IsStart(XGPT_NUM numXGPT)
{
    return (DRV_Reg32(g_xgpt_addr_con[numXGPT]) & XGPT_CON_ENABLE) ? TRUE : FALSE;
}

/******************************************************************************
 * DESCRIPTION:
 *   Start XGPT Timer
 * PARAMETERS:
 *   XGPT number
 ******************************************************************************/
void XGPT_Start(XGPT_NUM numXGPT)
{
    if (numXGPT != g_XGPT) {
        spin_lock_irqsave(&g_xgpt_lock, g_xgpt_flags);

        DRV_SetReg32(g_xgpt_addr_con[numXGPT], XGPT_CON_ENABLE | XGPT_CON_CLEAR);
        g_xgpt_status[numXGPT] = USED;

        spin_unlock_irqrestore(&g_xgpt_lock, g_xgpt_flags);
    }
}

void XGPT_Restart(XGPT_NUM numXGPT)
{
    if (numXGPT != g_XGPT) {
        spin_lock_irqsave(&g_xgpt_lock, g_xgpt_flags);

        DRV_SetReg32(g_xgpt_addr_con[numXGPT], XGPT_CON_ENABLE);
        g_xgpt_status[numXGPT] = USED;

        spin_unlock_irqrestore(&g_xgpt_lock, g_xgpt_flags);
    }
}

/******************************************************************************
 * DESCRIPTION:
 *   Stop XGPT Timer
 * PARAMETERS:
 *   XGPT number (XGPT2~7)
 ******************************************************************************/
void XGPT_Stop(XGPT_NUM numXGPT)
{
    if (numXGPT != g_XGPT) {
        spin_lock_irqsave(&g_xgpt_lock, g_xgpt_flags);

        DRV_ClrReg32(g_xgpt_addr_con[numXGPT], XGPT_CON_ENABLE);
        g_xgpt_status[numXGPT] = NOT_USED;

        spin_unlock_irqrestore(&g_xgpt_lock, g_xgpt_flags);
    }
}

/******************************************************************************
 * DESCRIPTION:
 *   This function is used to get XGPT counter
 * PARAMETERS:
 *   XGPT number (XGPT1~7)
 * RETURNS:
 *   XGPT counter value
 ******************************************************************************/
UINT32 XGPT_GetCounter(XGPT_NUM numXGPT)
{
    UINT32 cnt1, cnt2;

    spin_lock_irqsave(&g_xgpt_lock, g_xgpt_flags);

    /* SW workaround in E1 */
    cnt1 = DRV_Reg32(g_xgpt_addr_cnt[numXGPT]);
    while (1) {
        cnt2 = DRV_Reg32(g_xgpt_addr_cnt[numXGPT]);
        if (cnt2 == cnt1)
            break;
        cnt1 = cnt2;
    }

    spin_unlock_irqrestore(&g_xgpt_lock, g_xgpt_flags);

    return cnt1;
}

/******************************************************************************
 * DESCRIPTION:
 *   This function is used to clean XGPT counter value
 *   If it has been started, stop the timer.
 *   After cleaning XGPT counter value, restart this XGPT counter again
 * PARAMETERS:
 *   XGPT number
 ******************************************************************************/
void XGPT_ClearCount(XGPT_NUM numXGPT)
{
    BOOL bIsStarted;

    if (numXGPT != g_XGPT) {
        //In order to get the counter as 0 after the clear command
        //Stop the timer if it has been started.
        //after get the counter as 0, restore the timer status
        bIsStarted = XGPT_IsStart(numXGPT);
        if (bIsStarted)
            XGPT_Stop(numXGPT);

        spin_lock_irqsave(&g_xgpt_lock, g_xgpt_flags);

        DRV_SetReg32(g_xgpt_addr_con[numXGPT], XGPT_CON_CLEAR);

        spin_unlock_irqrestore(&g_xgpt_lock, g_xgpt_flags);

        //After setting the clear command, it needs to wait one cycle time of the clock source to become 0
        while (XGPT_GetCounter(numXGPT) != 0){}

        if (bIsStarted)
            XGPT_Restart(numXGPT);
    }
}

/******************************************************************************
 * DESCRIPTION:
 *   This function is used to set XGPT mode
 *   (XGPT_ONE_SHOT,XGPT_REPEAT,XGPT_KEEP_GO,XGPT_FREE_RUN)
 * PARAMETERS:
 *   XGPT number (XGPT2~7) and XGPT Mode
 ******************************************************************************/
void XGPT_SetOpMode(XGPT_NUM numXGPT, XGPT_CON_MODE mode)
{
    UINT32 gptMode;

    if (numXGPT != g_XGPT)
    {
        spin_lock_irqsave(&g_xgpt_lock, g_xgpt_flags);

        gptMode = DRV_Reg32(g_xgpt_addr_con[numXGPT]) & (~XGPT_FREE_RUN);
        gptMode |= mode;
        DRV_WriteReg32(g_xgpt_addr_con[numXGPT], gptMode);

        spin_unlock_irqrestore(&g_xgpt_lock, g_xgpt_flags);
    }
}

/******************************************************************************
 * DESCRIPTION:
 *   This function is used to get XGPT mode
 *   (XGPT_ONE_SHOT,XGPT_REPEAT,XGPT_KEEP_GO,XGPT_FREE_RUN)
 * PARAMETERS:
 *   XGPT number (XGPT1~7)
 * RETURNS:
 *   XGPT Mode
 ******************************************************************************/
XGPT_CON_MODE XGPT_GetOpMode(XGPT_NUM numXGPT)
{
    UINT32 u4Con;
    XGPT_CON_MODE mode = XGPT_ONE_SHOT;

    u4Con = DRV_Reg32(g_xgpt_addr_con[numXGPT]) & XGPT_FREE_RUN;
    if (u4Con == XGPT_FREE_RUN)
        mode = XGPT_FREE_RUN;
    else if (u4Con == XGPT_KEEP_GO)
        mode = XGPT_KEEP_GO;
    else if (u4Con == XGPT_REPEAT)
        mode = XGPT_REPEAT;

    return mode;
}

/******************************************************************************
 * DESCRIPTION:
 *   This function is used to set XGPT clock divisor
 *   (XGPT_CLK_DIV_1,XGPT_CLK_DIV_2,XGPT_CLK_DIV_4,XGPT_CLK_DIV_8,
 *    XGPT_CLK_DIV_16,XGPT_CLK_DIV_32,XGPT_CLK_DIV_64,XGPT_CLK_DIV_128)
 * PARAMETERS:
 *   XGPT number (XGPT2~7) and clock divisor
 ******************************************************************************/
void XGPT_SetClkDivisor(XGPT_NUM numXGPT, XGPT_CLK_DIV clkDiv)
{
    if (numXGPT != g_XGPT)
    {
        spin_lock_irqsave(&g_xgpt_lock, g_xgpt_flags);

        DRV_WriteReg32(g_xgpt_addr_clk[numXGPT], clkDiv);

        spin_unlock_irqrestore(&g_xgpt_lock, g_xgpt_flags);
    }
}

/******************************************************************************
 * DESCRIPTION:
 *   This function is used to get XGPT clock divisor
 *   (XGPT_CLK_DIV_1,XGPT_CLK_DIV_2,XGPT_CLK_DIV_4,XGPT_CLK_DIV_8,
 *    XGPT_CLK_DIV_16,XGPT_CLK_DIV_32,XGPT_CLK_DIV_64,XGPT_CLK_DIV_128)
 * PARAMETERS:
 *   XGPT number (XGPT1~7)
 * RETURNS:
 *   XGPT clock divisor
 ******************************************************************************/
XGPT_CLK_DIV XGPT_GetClkDivisor(XGPT_NUM numXGPT)
{
    return DRV_Reg32(g_xgpt_addr_clk[numXGPT]);
}

/******************************************************************************
 * DESCRIPTION:
 *   This function is used to set XGPT compare
 * PARAMETERS:
 *   XGPT number (XGPT2~7)
 ******************************************************************************/
void XGPT_SetCompare(XGPT_NUM numXGPT, UINT32 u4Compare)
{
    if (numXGPT != g_XGPT)
    {
        spin_lock_irqsave(&g_xgpt_lock, g_xgpt_flags);

        DRV_WriteReg32(g_xgpt_addr_compare[numXGPT], u4Compare);

        spin_unlock_irqrestore(&g_xgpt_lock, g_xgpt_flags);
    }
}

/******************************************************************************
 * DESCRIPTION:
 *   This function is used to get XGPT compare
 * PARAMETERS:
 *   XGPT number (XGPT1~7)
 * RETURNS:
 *   XGPT counter value
 ******************************************************************************/
UINT32 XGPT_GetCompare(XGPT_NUM numXGPT)
{
    return DRV_Reg32(g_xgpt_addr_compare[numXGPT]);
}

/******************************************************************************
 * DESCRIPTION:
 *   This function is used to reset XGPT register
 * PARAMETERS:
 *   XGPT number (XGPT2~7)
 ******************************************************************************/
void XGPT_Reset(XGPT_NUM numXGPT)
{
    //cannot reset XGPT1
    //Reset XGPT1 will cause sysmten timer fail
    if (numXGPT == g_XGPT)
    {
        printk("XGPT_Reset : cannot reset system timer (g_XGPT)\n");
        return;
    }

    //(1) stop XGPT
    XGPT_Stop(numXGPT);

    //(2) Clean XGPT counter
    XGPT_ClearCount(numXGPT);

    //(3) Disbale Interrupt
    XGPT_DisableIRQ(numXGPT);

    //(4) Default mode should be one shot
    XGPT_SetOpMode(numXGPT, XGPT_ONE_SHOT);

    //(5) Default Clock Divisor should be XGPT_CLK_DIV_1
    XGPT_SetClkDivisor(numXGPT, XGPT_CLK_DIV_1);

    //(6) Clean XGPT Comparator
    XGPT_SetCompare(numXGPT, 0);
}

/******************************************************************************
 * DESCRIPTION:
 *   This function is used to config XGPT register
 *   (1) mode
 *   (2) clkDiv
 *   (3) bIrqEnable
 *   (4) u4Compare
 * PARAMETERS:
 *   XGPT configuration data structure
 * RETURNS:
 *   TRUE : config XGPT pass
 *   FALSE: config XGPT fail
 ******************************************************************************/
BOOL XGPT_Config(XGPT_CONFIG config)
{
    XGPT_NUM num = config.num;
    XGPT_CON_MODE mode = config.mode;
    XGPT_CLK_DIV clkDiv = config.clkDiv;
    BOOL bIrqEnable = config.bIrqEnable;
    UINT32 u4Compare = config.u4Compare;
    BOOL bRet = TRUE;

    if (num == g_XGPT)
    {
        printk("XGPT_Config : MT6573 g_XGPT shouldn't be used\n");
        return FALSE;
    }

    if (XGPT_IsStart(num))
    {
        printk("XGPT_Config : MT6573 XGPT%d is already in use\n", num + 1);
        return FALSE;
    }
    else
    {   XGPT_DEBUG("XGPT_Config : MT6573 XGPT%d is free to use\n", num + 1);
    }

    XGPT_SetOpMode(num, mode);
    if (XGPT_GetOpMode(num) != mode)
    {
        bRet = FALSE;
    }

    XGPT_SetClkDivisor(num, clkDiv);
    if (XGPT_GetClkDivisor(num) != clkDiv)
    {
        bRet = FALSE;
    }

    if (bIrqEnable)
        XGPT_EnableIRQ(num);
    else
        XGPT_DisableIRQ(num);

    XGPT_SetCompare(num, u4Compare);
    if (XGPT_GetCompare(num) != u4Compare)
    {
        bRet = FALSE;
    }

    return bRet;
}

/******************************************************************************
 * DESCRIPTION:
 *   Register XGPT2~7 interrupt handler (call back function)
 * PARAMETERS:
 *   XGPT number (XGPT2~7) and handler
 ******************************************************************************/
void XGPT_Init(XGPT_NUM timerNum, void (*XGPT_Callback)(UINT16))
{
    if (timerNum == XGPT2)
    {
        g_xgpt_func.xgpt2_func = XGPT_Callback;
    }
    else if (timerNum == XGPT3)
    {
        g_xgpt_func.xgpt3_func = XGPT_Callback;
    }
    else if (timerNum == XGPT4)
    {
        g_xgpt_func.xgpt4_func = XGPT_Callback;
    }
    else if (timerNum == XGPT5)
    {
        g_xgpt_func.xgpt5_func = XGPT_Callback;
    }
    else if (timerNum == XGPT6)
    {
        g_xgpt_func.xgpt6_func = XGPT_Callback;
    }
    else if (timerNum == XGPT7)
    {
        g_xgpt_func.xgpt7_func = XGPT_Callback;
    }
}

/******************************************************************************
 *   XGPT LISR to handle XGPT2~7 interrupt
 *   In this function, it will schedule corresonding XGPT tasklet
 ******************************************************************************/
static irqreturn_t __tcmfunc XGPT_LISR(int irq, void *dev_id)
{
    struct clock_event_device *evt = dev_id;
    XGPT_NUM numXGPT;

    numXGPT = XGPT_Get_IRQSTA();
    XGPT_AckIRQ(numXGPT);

XGPT_DEBUG("event_handler: 0x%x\n", evt->event_handler);
#ifdef XGPT_CLOCK_32K
    if(numXGPT == g_XGPT){
    	evt->event_handler(evt);
    	return IRQ_HANDLED;
    }
#endif
	
    switch (numXGPT)
    {
        case XGPT1:
            evt->event_handler(evt);
            break;
        case XGPT2:
            tasklet_schedule(&g_xgpt2_tlet);
            break;
        case XGPT3:
            tasklet_schedule(&g_xgpt3_tlet);
            break;
        case XGPT4:
            tasklet_schedule(&g_xgpt4_tlet);
            break;
        case XGPT5:
            tasklet_schedule(&g_xgpt5_tlet);
            break;
        case XGPT6:
            tasklet_schedule(&g_xgpt6_tlet);
            break;
        case XGPT7:
            tasklet_schedule(&g_xgpt7_tlet);
            break;
        default:
            break;
    }

    return IRQ_HANDLED;
}

/******************************************************************************
 Initialize GPT/XGPT Module
******************************************************************************/

static void mt6573_gpt_init(void);
static void mt6573_xgpt_init(void);

unsigned long long sched_clock(void)
{
	unsigned long long v = cnt32_to_63(DRV_Reg32(MT6573_GPT4_DAT));

	/* the <<1 gets rid of the cnt_32_to_63 top bit saving on a bic insn */
	// 1000000000 / 26000000 = 1000 / 26
	v *= 1000 << 1;
	do_div(v, 26 << 1);

	return v;
}

static cycle_t mt6573_gpt_read(struct clocksource *cs)
{
    return DRV_Reg32(MT6573_GPT4_DAT);
}

static int mt6573_xgpt_set_next_event(unsigned long cycles,
                                      struct clock_event_device *evt)
{
    unsigned long ctrl;
    unsigned int count = 5000;
    //ctrl = DRV_Reg32(MT6573_XGPT1_CON);
    ctrl = DRV_Reg32(g_xgpt_addr_con[g_XGPT]);

    //if(DRV_Reg32(MT6573_XGPT1_PRESCALE)){
    //	printk("[Dynamic]: Error!!! xgpt1 not run in 26 MHz!!!\r\n");
    //}

    //disable xgpt first. 
    ctrl &= (~XGPT_CON_ENABLE); 
    ctrl |= XGPT_CON_CLEAR; 
    //DRV_WriteReg32(MT6573_XGPT1_CON, ctrl);    
    DRV_WriteReg32(g_xgpt_addr_con[g_XGPT], ctrl);  
    while (XGPT_GetCounter(g_XGPT) != 0){if(count-- == 0) break;}  
    
    //the evt is the cycle need to wait, we just set it to compare.
    //DRV_WriteReg32(MT6573_XGPT1_COMPARE, cycles);
    DRV_WriteReg32(g_xgpt_addr_compare[g_XGPT], cycles);
    //if(cycles > XGPT_CLOCK_VALUE/10){
    XGPT_DEBUG("idle cycles time XGPT%d, count:0x%x\n", g_XGPT+1, cycles);
    //}		    
    ctrl |= XGPT_CON_ENABLE;
    //DRV_WriteReg32(MT6573_XGPT1_CON, ctrl);  
    DRV_WriteReg32(g_xgpt_addr_con[g_XGPT], ctrl);   	
    // wait for clear count
	
    return 0;
}

int XGPT_Set_Next_Compare(unsigned long cycles)
{
    return mt6573_xgpt_set_next_event(cycles, NULL);
}

static void mt6573_xgpt_set_mode(enum clock_event_mode mode,
                                 struct clock_event_device *evt)
{
    unsigned long ctrl;	
    
    //ctrl = DRV_Reg32(MT6573_XGPT1_CON);
    ctrl = DRV_Reg32(g_xgpt_addr_con[g_XGPT]);
    

    switch (mode) {
    case CLOCK_EVT_MODE_PERIODIC:
        // reset counter value		
        ctrl |= XGPT_CON_CLEAR;				
        // clear xgpt mode		
        ctrl = ctrl & (~XGPT_FREE_RUN);		
        // set xgpt for repeat mode		
        ctrl |= XGPT_REPEAT;		

        // enable interrupt		
        //DRV_SetReg32(MT6573_XGPT_IRQEN, 0x0001);		
        DRV_SetReg32(MT6573_XGPT_IRQEN, 0x1<<g_XGPT);		

        // enable xgpt		
        ctrl |= XGPT_CON_ENABLE;	
        DRV_WriteReg32(g_xgpt_addr_con[g_XGPT], ctrl); 		
        //DRV_WriteReg32(MT6573_XGPT1_CON, ctrl); 	
        break;

    case CLOCK_EVT_MODE_ONESHOT:
        // reset counter value		
        ctrl |= XGPT_CON_CLEAR;		
        // clear xgpt mode		
        ctrl = ctrl & (~XGPT_FREE_RUN);		
        // set xgpt for repeat mode		
        ctrl |= XGPT_ONE_SHOT;		

        // enable interrupt 		
        //DRV_SetReg32(MT6573_XGPT_IRQEN, 0x0001);				
        DRV_SetReg32(MT6573_XGPT_IRQEN, 0x1<<g_XGPT);	

        // enable xgpt		
        ctrl |= XGPT_CON_ENABLE;	
        //DRV_WriteReg32(MT6573_XGPT1_CON, ctrl); 	
        DRV_WriteReg32(g_xgpt_addr_con[g_XGPT], ctrl); 		
        break;

    case CLOCK_EVT_MODE_UNUSED:
    case CLOCK_EVT_MODE_SHUTDOWN:
    case CLOCK_EVT_MODE_RESUME:
        break;
    }
}

struct mt65xx_clock mt6573_gpt =
{
    .clockevent =
    {
        .name = NULL,
    },
    .clocksource =
    {
        .name   = "mt6573-gpt",
        .rating = 300,
        .read   = mt6573_gpt_read,
        .mask   = CLOCKSOURCE_MASK(32),
        .shift  = 26,
        .flags  = CLOCK_SOURCE_IS_CONTINUOUS,
    },
    .irq =
    {
        .name       = "mt6573-gpt",
        .flags      = IRQF_DISABLED | IRQF_TIMER | IRQF_IRQPOLL,
        .handler    = (irq_handler_t)GPT_LISR,
        .irq        = MT6573_APARM_GPTTIMER_IRQ_LINE,
    },
    .init_func = mt6573_gpt_init,
};

struct mt65xx_clock mt6573_xgpt =
{
    .clockevent =
    {
        .name           = "mt6573-xgpt",
        .features       = CLOCK_EVT_FEAT_ONESHOT,
        .shift          = 20,
        .rating         = 300,
        .set_next_event = mt6573_xgpt_set_next_event,
        .set_mode       = mt6573_xgpt_set_mode,
    },
    .clocksource =
    {
        .name = NULL,
    },
    .irq =
    {
        .name       = "mt6573-xgpt",
        .flags      = IRQF_DISABLED | IRQF_TIMER | IRQF_IRQPOLL,
        .handler    = (irq_handler_t)XGPT_LISR,
        .dev_id     = &mt6573_xgpt.clockevent,
        .irq        = MT6573_APXGPT_IRQ_LINE,
    },
    .init_func = mt6573_xgpt_init,
};

static void mt6573_gpt_init(void)
{
    struct clocksource *cs = &mt6573_gpt.clocksource;

    cs->mult = clocksource_hz2mult(26000000, cs->shift);

    spin_lock_irqsave(&g_gpt_lock, g_gpt_flags);

    //set interrupt sensitive
    mt65xx_irq_set_sens(MT6573_APARM_GPTTIMER_IRQ_LINE, MT65xx_LEVEL_SENSITIVE); 

    DRV_WriteReg32(MT6573_GPT4_CON, 0x0000);    /* stop and clear */
    DRV_WriteReg32(MT6573_GPT4_CON, 0x0001);    /* start FREERUN mode */
    g_gpt_status[GPT4] = USED;

    spin_unlock_irqrestore(&g_gpt_lock, g_gpt_flags);
}

static void mt6573_xgpt_init(void)
{
    struct clock_event_device *evt = &mt6573_xgpt.clockevent;

    //evt->mult = div_sc(26000000, NSEC_PER_SEC, evt->shift);
    evt->mult = div_sc(XGPT_CLOCK_VALUE, NSEC_PER_SEC, evt->shift);
    evt->max_delta_ns = clockevent_delta2ns(0xffffffff, evt);
    evt->min_delta_ns = clockevent_delta2ns(3, evt);
    evt->cpumask = cpumask_of(0);
		
    spin_lock_irqsave(&g_xgpt_lock, g_xgpt_flags);

    //set interrupt sensitive
    mt65xx_irq_set_sens(MT6573_APXGPT_IRQ_LINE, MT65xx_LEVEL_SENSITIVE);
    
    //DRV_WriteReg32(MT6573_XGPT1_CON, 0x0012);   /* stop and clear */
    DRV_WriteReg32(g_xgpt_addr_con[g_XGPT], 0x0012);   /* stop and clear */
    
    //DRV_WriteReg32(MT6573_XGPT_IRQACK, 0x0001); /* ack old irq */
    DRV_WriteReg32(MT6573_XGPT_IRQACK, 0x0001<<g_XGPT); /* ack old irq */

    //DRV_SetReg32(MT6573_XGPT_IRQEN, 0x0001);
    DRV_SetReg32(MT6573_XGPT_IRQEN, 0x0001<<g_XGPT);
    
    //DRV_WriteReg32(MT6573_XGPT1_PRESCALE, 0x0000);          /* 26M */
    DRV_WriteReg32(g_xgpt_addr_clk[g_XGPT], 0x0000);    
    
    //DRV_WriteReg32(MT6573_XGPT1_COMPARE, 26000000 / HZ);    /* 26000000 / 100 = 260000 */
    DRV_WriteReg32(g_xgpt_addr_compare[g_XGPT], XGPT_CLOCK_VALUE / HZ);

    DRV_WriteReg32(g_xgpt_addr_con[g_XGPT], 0x0013); 
    //DRV_WriteReg32(MT6573_XGPT1_CON, 0x0013);   /* start REPEAT mode */
    
    //g_xgpt_status[XGPT1] = USED;
    g_xgpt_status[g_XGPT] = USED;

    spin_unlock_irqrestore(&g_xgpt_lock, g_xgpt_flags);

    XGPT_DEBUG("XGPT%d_COMPARE = %d, HZ = %d\n",g_XGPT+1, DRV_Reg32(g_xgpt_addr_compare[g_XGPT]), HZ);
    XGPT_DEBUG("mult<0x%x>, shift<0x%x>\r\n", evt->mult, evt->shift);
    XGPT_DEBUG("10ms -> 0x%x\r\n", (10*1000*1000 * evt->mult) >> evt->shift);    
}

static int GPT_Proc(char *page, char **start, off_t off, int count, int *eof, void *data)
{
    char *p = page;
    int len = 0;

    p += sprintf(p, "\n(HW Timer) GPT Status :\n");
    p += sprintf(p, "=========================================\n");
    p += sprintf(p, "0 = disable, 1 = enable\n");
    p += sprintf(p, "GPT1 : %d\n", GPT_IsStart(GPT1));
    p += sprintf(p, "GPT2 : %d\n", GPT_IsStart(GPT2));
    p += sprintf(p, "GPT3 : %d\n", GPT_IsStart(GPT3));
    p += sprintf(p, "GPT4 : %d\n", GPT_IsStart(GPT4));

    *start = page + off;

    len = p - page;
    if (len > off)
        len -= off;
    else
        len = 0;

    return len < count ? len : count;
}

static int XGPT_Proc(char *page, char **start, off_t off, int count, int *eof, void *data)
{
    char *p = page;
    int len = 0;

    p += sprintf(p, "\n(HW Timer) XGPT Status :\n");
    p += sprintf(p, "=========================================\n");
    p += sprintf(p, "0 = disable, 1 = enable\n");
    p += sprintf(p, "XGPT1 : %d\n", XGPT_IsStart(XGPT1));
    p += sprintf(p, "XGPT2 : %d\n", XGPT_IsStart(XGPT2));
    p += sprintf(p, "XGPT3 : %d\n", XGPT_IsStart(XGPT3));
    p += sprintf(p, "XGPT4 : %d\n", XGPT_IsStart(XGPT4));
    p += sprintf(p, "XGPT5 : %d\n", XGPT_IsStart(XGPT5));
    p += sprintf(p, "XGPT6 : %d\n", XGPT_IsStart(XGPT6));
    p += sprintf(p, "XGPT7 : %d\n", XGPT_IsStart(XGPT7));

    *start = page + off;

    len = p - page;
    if (len > off)
        len -= off;
    else
        len = 0;

    return len < count ? len : count;
}

static int __init mt6573_gpt_xgpt_init(void)
{
    //Crate proc entry at /proc/gpt_stat
    create_proc_read_entry("gpt_stat", S_IRUGO, NULL, GPT_Proc, NULL);

    //Crate proc entry at /proc/xgpt_stat
    create_proc_read_entry("xgpt_stat", S_IRUGO, NULL, XGPT_Proc, NULL);
        
    return 0;
}

module_init(mt6573_gpt_xgpt_init);

EXPORT_SYMBOL(GPT_IsStart);
EXPORT_SYMBOL(GPT_Start);
EXPORT_SYMBOL(GPT_Stop);
EXPORT_SYMBOL(GPT_SetOpMode);
EXPORT_SYMBOL(GPT_GetOpMode);
EXPORT_SYMBOL(GPT_SetClkDivisor);
EXPORT_SYMBOL(GPT_GetClkDivisor);
EXPORT_SYMBOL(GPT_SetTimeout);
EXPORT_SYMBOL(GPT_GetTimeout);
EXPORT_SYMBOL(GPT_Config);
EXPORT_SYMBOL(GPT_Init);

EXPORT_SYMBOL(XGPT_EnableIRQ);
EXPORT_SYMBOL(XGPT_DisableIRQ);
EXPORT_SYMBOL(XGPT_IsIRQEnable);
EXPORT_SYMBOL(XGPT_Check_IRQSTA);
EXPORT_SYMBOL(XGPT_IsStart);
EXPORT_SYMBOL(XGPT_Start);
EXPORT_SYMBOL(XGPT_Restart);
EXPORT_SYMBOL(XGPT_Stop);
EXPORT_SYMBOL(XGPT_GetCounter);
EXPORT_SYMBOL(XGPT_ClearCount);
EXPORT_SYMBOL(XGPT_SetOpMode);
EXPORT_SYMBOL(XGPT_GetOpMode);
EXPORT_SYMBOL(XGPT_SetClkDivisor);
EXPORT_SYMBOL(XGPT_GetClkDivisor);
EXPORT_SYMBOL(XGPT_SetCompare);
EXPORT_SYMBOL(XGPT_GetCompare);
EXPORT_SYMBOL(XGPT_Reset);
EXPORT_SYMBOL(XGPT_Config);
EXPORT_SYMBOL(sched_clock);
EXPORT_SYMBOL(XGPT_Init);

MODULE_DESCRIPTION("MT6573 GPT/XGPT Driver v0.2");
MODULE_LICENSE("GPL");
