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

#include <linux/interrupt.h>
#include <linux/wait.h>
#include <asm/tcm.h>

#include <mach/mt6573_typedefs.h>
#include <mach/mt6573_reg_base.h>
#include <mach/mt6573_irq.h>
#include <mach/mt6573_pll.h>

#include "pmu6573_hw.h"
#include "pmu6573_sw.h"

#include "tve_reg.h"
#include "tve_drv.h"

#include "mtkfb.h"


#if defined(MTK_TVOUT_SUPPORT)

#define TVE_PARAMETE_V2

PTVE_REGS const TVE_REG = (PTVE_REGS)(TVE_BASE);

static BOOL s_isTvePowerOn  = FALSE;
static TVE_TV_TYPE s_tvType = TVE_NTSC;
static TVE_REGS regBackup;

#define TVE_REG_OFFSET(r)       offsetof(TVE_REGS, r)
#define REG_ADDR(base, offset)  (((BYTE *)(base)) + (offset))

const UINT32 BACKUP_TVE_REG_OFFSETS[] =
{
    TVE_REG_OFFSET(MODE),
    TVE_REG_OFFSET(SCALE_CON),
    TVE_REG_OFFSET(DAC_CON),
    TVE_REG_OFFSET(BURST),
    TVE_REG_OFFSET(FREQ),
    TVE_REG_OFFSET(SLEW),
    
    TVE_REG_OFFSET(YLPFC),
    TVE_REG_OFFSET(YLPFD),
    TVE_REG_OFFSET(YLPFE),
    TVE_REG_OFFSET(CLPFA),
    TVE_REG_OFFSET(CLPFB),
    TVE_REG_OFFSET(CLPFC),

    TVE_REG_OFFSET(GAMMAA),
    TVE_REG_OFFSET(GAMMAB),
    TVE_REG_OFFSET(GAMMAC),
    TVE_REG_OFFSET(GAMMAD),
    TVE_REG_OFFSET(GAMMAE),

    TVE_REG_OFFSET(CMPCODE),
    TVE_REG_OFFSET(PLUG),
};

static void _BackupTVERegisters(void)
{
    TVE_REGS *reg = &regBackup;
    UINT32 i;
    
    for (i = 0; i < ARY_SIZE(BACKUP_TVE_REG_OFFSETS); ++ i)
    {
        OUTREG32(REG_ADDR(reg, BACKUP_TVE_REG_OFFSETS[i]),
                 AS_UINT32(REG_ADDR(TVE_REG, BACKUP_TVE_REG_OFFSETS[i])));
    }
}

static void _RestoreTVERegisters(void)
{
    TVE_REGS *reg = &regBackup;
    UINT32 i;

    for (i = 0; i < ARY_SIZE(BACKUP_TVE_REG_OFFSETS); ++ i)
    {
        OUTREG32(REG_ADDR(TVE_REG, BACKUP_TVE_REG_OFFSETS[i]),
                 AS_UINT32(REG_ADDR(reg, BACKUP_TVE_REG_OFFSETS[i])));
    }
}

static void _ResetBackupedTVERegisterValues(void)
{
    TVE_REGS *regs = &regBackup;
    memset((void*)regs, 0, sizeof(TVE_REGS));

    OUTREG32(&regs->SCALE_CON,  0x00045A5A);
    OUTREG32(&regs->BURST,      0x0000003A);
    OUTREG32(&regs->FREQ,       0x0DD0010F);
    OUTREG32(&regs->SLEW,       0x00C806A4);

    OUTREG32(&regs->YLPFC,      0x32020000);
    OUTREG32(&regs->YLPFD,      0x021E3D25);
    OUTREG32(&regs->YLPFE,      0x90B4FFC7);

    OUTREG32(&regs->CLPFA,      0x180D1001);
    OUTREG32(&regs->CLPFB,      0x25342021);
    OUTREG32(&regs->CLPFC,      0x0000273C);
    
    OUTREG32(&regs->GAMMAB,     0x0314018A);
    OUTREG32(&regs->GAMMAC,     0x0629049E);
    OUTREG32(&regs->GAMMAD,     0x093D07B3);
    OUTREG32(&regs->GAMMAE,     0x0C520AC8);

    OUTREG32(&regs->CMPCODE,    0x00000FFF);
    OUTREG32(&regs->RESET,      0x00000001);
}


static __tcmfunc irqreturn_t _TVE_InterruptHandler(int irq, void *dev_id)
{   
    return IRQ_HANDLED;
}


TVE_STATUS TVE_Init(void)
{
    // TVE controller would NOT reset register as default values
    // Do it by SW here
    //
    _ResetBackupedTVERegisterValues();

    if (request_irq(MT6573_TVE_IRQ_LINE,
                    (irq_handler_t)_TVE_InterruptHandler,
                    0, "mt6573-tve", NULL) < 0)
    {
        printk("[TVE][ERROR] fail to request TVE irq\n"); 
        return TVE_STATUS_ERROR;
    }

    // Disable TVDAC defaultly
    OUTREG32(VTV_CON0, 0x0);
    OUTREG32(MIXEDSYS0_BASE + 0xBC0, 0x0);
    OUTREG32(MIXEDSYS0_BASE + 0xBC4, 0x0);

    return TVE_STATUS_OK;
}


TVE_STATUS TVE_Deinit(void)
{
    TVE_Disable();
    TVE_PowerOff();

    return TVE_STATUS_OK;
}


TVE_STATUS TVE_PowerOn()
{
    if (!s_isTvePowerOn)
    {
        BOOL ret = hwEnablePLL(MT65XX_3G_PLL, "TVE");
        ASSERT(ret);
        ret = hwEnablePLL(MT65XX_TV_PLL, "TVE");
        ASSERT(ret);
        ret = hwEnableClock(MT65XX_PDN_MM_TVE, "TVE");
        ASSERT(ret);
        
        _RestoreTVERegisters();
        s_isTvePowerOn = TRUE;
    }

    return TVE_STATUS_OK;
}


TVE_STATUS TVE_PowerOff()
{
    if (s_isTvePowerOn)
    {
        BOOL ret = TRUE;
        _BackupTVERegisters();

        ret = hwDisableClock(MT65XX_PDN_MM_TVE, "TVE");
        ASSERT(ret);
        ret = hwDisablePLL(MT65XX_TV_PLL, "TVE");
        ASSERT(ret);
        ret = hwDisablePLL(MT65XX_3G_PLL, "TVE");
        ASSERT(ret);

        s_isTvePowerOn = FALSE;
    }

    return TVE_STATUS_OK;
}


TVE_STATUS TVE_Enable(void)
{
    TVE_REG_MODE mode = TVE_REG->MODE;
    mode.ENCON = 1;
    OUTREG32(&TVE_REG->MODE, AS_UINT32(&mode));

    /* TVDAC enable
       TVDAC control is moved to MIXEDSYS
    */
    OUTREG32(VTV_CON0, 0x5);
    OUTREG32(MIXEDSYS0_BASE + 0xBC0, 0x1FF2);
    OUTREG32(MIXEDSYS0_BASE + 0xBC4, 0x0);
    OUTREG32(&TVE_REG->DAC_CON, 0x0);
    
    return TVE_STATUS_OK;
}


TVE_STATUS TVE_Disable(void)
{
    TVE_REG_MODE mode = TVE_REG->MODE;
    mode.ENCON = 0;
    OUTREG32(&TVE_REG->MODE, AS_UINT32(&mode));

    /* TVDAC disable
       TVDAC control is moved to MIXEDSYS
    */
    OUTREG32(VTV_CON0, 0x0);
    OUTREG32(MIXEDSYS0_BASE + 0xBC0, 0x0);
    OUTREG32(MIXEDSYS0_BASE + 0xBC4, 0x0);

    return TVE_STATUS_OK;
}


TVE_STATUS TVE_SetTvType(TVE_TV_TYPE type)
{
    {
        TVE_REG_MODE MODE = TVE_REG->MODE;
        MODE.TVTYPE = (TVE_NTSC == type) ? TVE_NTSC : TVE_PAL;
        OUTREG32(&TVE_REG->MODE, AS_UINT32(&MODE));
    }

    if (TVE_NTSC == type) {
        OUTREG32(&TVE_REG->FREQ, ((0xdd0<<16)|0x10f));
    } else {
        OUTREG32(&TVE_REG->FREQ, ((0x80d<<16)|0x150));
    }

    s_tvType = type;

    return TVE_STATUS_OK;
}


TVE_STATUS TVE_EnableColorBar(BOOL enable)
{
    TVE_REG_MODE mode = TVE_REG->MODE;
    mode.CBON = enable ? 1 : 0;
    OUTREG32(&TVE_REG->MODE, AS_UINT32(&mode));

    return TVE_STATUS_OK;
}

#if defined (TVE_PARAMETE_V2)
TVE_STATUS TVE_ResetDefaultSettings(void)
{
    if (!s_isTvePowerOn) return TVE_STATUS_OK;
        
    OUTREG32(&TVE_REG->BURST, 0x3c);

    OUTREG32(&TVE_REG->DAC_CON, 0x0);
    
    //OUTREG32(&TVE_REG->SCALE_CON, 0x47050); // Scale of UV
    OUTREG32(&TVE_REG->SCALE_CON, 0x45840); // Scale of UV

    //OUTREG32(&TVE_REG->GAMMAB, (605<<16)|302);
    //OUTREG32(&TVE_REG->GAMMAC, (1210<<16)|907);
    //OUTREG32(&TVE_REG->GAMMAD, (1815<<16)|1512);
    //OUTREG32(&TVE_REG->GAMMAE, (2420<<16)|2117);

    OUTREG32(&TVE_REG->GAMMAB, 0x02440122);
    OUTREG32(&TVE_REG->GAMMAC, 0x04880366);
    OUTREG32(&TVE_REG->GAMMAD, 0x06cc05aa);
    OUTREG32(&TVE_REG->GAMMAE, 0x091007ee);

    
    OUTREG32(&TVE_REG->YLPFC, 0x32020000);
    OUTREG32(&TVE_REG->YLPFD, 0x021E3D25);
    OUTREG32(&TVE_REG->YLPFE, 0x90B4FFC7);

    OUTREG32(&TVE_REG->CLPFA, 0x180D1001);
    OUTREG32(&TVE_REG->CLPFB, 0x25342021);
    OUTREG32(&TVE_REG->CLPFC, 0x0000273C);

    {
        TVE_REG_MODE MODE = {0};

		MODE.SETUP  = 1;            // Turn on 7.5 IRE

		MODE.SYDEL = 1;
		MODE.YDEL  = 2;

        //MODE.CLPON  = 1;            // Turn on Chroma LPS
        
		MODE.TVTYPE = s_tvType;

        OUTREG32(&TVE_REG->MODE, AS_UINT32(&MODE));
    }

    TVE_SetTvType(s_tvType);

    return TVE_STATUS_OK;
}
#else
TVE_STATUS TVE_ResetDefaultSettings(void)
{
    if (!s_isTvePowerOn) return TVE_STATUS_OK;
        
    OUTREG32(&TVE_REG->BURST, 0x3d);

    OUTREG32(&TVE_REG->DAC_CON, 0x0);
    
    OUTREG32(&TVE_REG->SCALE_CON, 0x47050); // Scale of UV

    OUTREG32(&TVE_REG->GAMMAB, (605<<16)|302);
    OUTREG32(&TVE_REG->GAMMAC, (1210<<16)|907);
    OUTREG32(&TVE_REG->GAMMAD, (1815<<16)|1512);
    OUTREG32(&TVE_REG->GAMMAE, (2420<<16)|2117);
    
    OUTREG32(&TVE_REG->YLPFC, 0x32020000);
    OUTREG32(&TVE_REG->YLPFD, 0x021E3D25);
    OUTREG32(&TVE_REG->YLPFE, 0x90B4FFC7);

    OUTREG32(&TVE_REG->CLPFA, 0x180D1001);
    OUTREG32(&TVE_REG->CLPFB, 0x25342021);
    OUTREG32(&TVE_REG->CLPFC, 0x0000273C);

    {
        TVE_REG_MODE MODE = {0};

        MODE.SETUP  = 1;            // Turn on 7.5 IRE
        MODE.CLPON  = 1;            // Turn on Chroma LPS
        MODE.TVTYPE = s_tvType;

        OUTREG32(&TVE_REG->MODE, AS_UINT32(&MODE));
    }

    TVE_SetTvType(s_tvType);

    return TVE_STATUS_OK;
}
#endif



TVE_STATUS TVE_DumpRegisters(void)
{
    UINT32 i;

    printk("---------- Start dump TVE registers ----------\n"
           "TVE_BASE: 0x%08x\n", TVE_BASE);
    
    for (i = 0; i < sizeof(TVE_REGS); i += 4)
    {
        printk("TVE+%04x : 0x%08x\n", i, INREG32(TVE_BASE + i));
    }

    return TVE_STATUS_OK;
}

#endif
