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

#include <asm/io.h>
#include <linux/spinlock.h>
#include <linux/interrupt.h>
#include <linux/types.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <asm/tcm.h>
#include <asm/uaccess.h>
    
#include "mach/mt6573_reg_base.h"
#include "mach/irqs.h"
#include "mach/mt6573_eint.h"
#include "mach/dma.h"
#include "mach/sync_write.h"
#include "mach/mt6573_pll.h"
#include "mach/mt6573_typedefs.h"
#include "mach/mtkpm.h"
#include "mach/mt6573_ost_sm.h"

#include "pmu6573_hw.h"
#include "pmu6573_sw.h"
#include "upmu_common_sw.h"
    
/*******************************************************************
 * Extern Variable DEFINATIONS
 *******************************************************************/

/**********************************************************************
 * Extern FUNCTION DEFINATIONS
 *******************************************************************/
extern void upmu_ldo_enable(upmu_ldo_list_enum ldo, kal_bool enable);
extern void upmu_ldo_vol_sel(upmu_ldo_list_enum ldo, upmu_ldo_vol_enum vol);

/**********************************************************************
* Debug Message Settings
*****************************************************************/

/* Debug message event */
#define DBG_PMAPI_MASK       (CM_DBG_FLAG)

#if 1
#define MSG(evt, fmt, args...) \
do {    \
    if ((DBG_PMAPI_##evt) & DBG_PMAPI_MASK) { \
        printk(fmt, ##args); \
    } \
} while(0)

#define MSG_FUNC_ENTRY(f)    MSG(ENTER, "<PMAPI FUNC>: %s\n", __FUNCTION__)
#else
#define MSG(evt, fmt, args...) do{}while(0)
#define MSG_FUNC_ENTRY(f)       do{}while(0)
#endif

/****************************************************************
 * FUNCTION DEFINATIONS
 *******************************************************************/

bool hwPowerOn(MT65XX_POWER powerId, MT65XX_POWER_VOLTAGE powervol, char *mode_name)
{
    UINT32 i = 0;    
    if(powerId >= MT65XX_POWER_COUNT_END)
    {
        MSG(PMIC,"[MT65XX PMU] Error!! powerId is wrong\r\n");
        return FALSE;
    }
    for (i = 0; i< MAX_DEVICE; i++)
    {
        if (!strcmp(g_MT6573_BusHW.Power[powerId].mod_name[i], NON_OP))
        {
            MSG(PMIC,"[%s] acquire powerId:%d index:%d mod_name: %s\r\n", 
                __FUNCTION__,powerId, i, mode_name);            
            sprintf(g_MT6573_BusHW.Power[powerId].mod_name[i] , "%s", mode_name);
            break ;
        }
        /* already it */
        #if 0
        else if (!strcmp(g_MT6573_BusHW.Power[powerId].mod_name[i], mode_name))
        {
            MSG(CG,"[%d] Power already register\r\n",powerId );        
        }
        #endif
    }    
    g_MT6573_BusHW.Power[powerId].dwPowerCount++ ;
    /* We've already enable this LDO before */
    if(g_MT6573_BusHW.Power[powerId].dwPowerCount > 1)
    {
        return TRUE;
    }    
    /* Turn on PMU LDO*/
    MSG(CG,"[%d] PMU LDO Enable\r\n",powerId );            

    if ((powerId == MT65XX_POWER_LDO_VIBR)
    	||(powerId == MT65XX_POWER_LDO_VCAMA)
    	||(powerId == MT65XX_POWER_LDO_VCAMD)
    	||(powerId == MT65XX_POWER_LDO_VCAMA2)
    	||(powerId == MT65XX_POWER_LDO_VCAMD2)
    	)
	    upmu_ldo_vol_sel(powerId, powervol);

    upmu_ldo_enable(powerId, KAL_TRUE);
    
    return TRUE; 
}

bool hwPowerDown(MT65XX_POWER powerId, char *mode_name)
{
    UINT32 i;
    BOOL bFind = FALSE;    
    if(powerId >= MT65XX_POWER_COUNT_END)
    {
        MSG(PMIC,"%s:%s:%d powerId:%d is wrong\r\n",__FILE__,__FUNCTION__, 
            __LINE__ , powerId);
        return FALSE;
    }    
    if(g_MT6573_BusHW.Power[powerId].dwPowerCount == 0)
    {
        MSG(PMIC,"%s:%s:%d powerId:%d (g_MT6573_BusHW.dwPowerCount[powerId] = 0)\r\n", 
            __FILE__,__FUNCTION__,__LINE__ ,powerId);
        return FALSE;
    }
    for (i = 0; i< MAX_DEVICE; i++)
    {
        if (!strcmp(g_MT6573_BusHW.Power[powerId].mod_name[i], mode_name))
        {
            MSG(PMIC,"[%s] powerId:%d index:%d mod_name: %s\r\n", 
                __FUNCTION__,powerId, i, mode_name);            
            sprintf(g_MT6573_BusHW.Power[powerId].mod_name[i] , "%s", NON_OP);
            bFind = TRUE;
            break ;
        }
    }   
    if(!bFind)
    {
        MSG(PMIC,"[%s] Cannot find [%d] master is [%s]\r\n",__FUNCTION__,powerId, mode_name);        
        return TRUE;
    }        
    g_MT6573_BusHW.Power[powerId].dwPowerCount--;
    if(g_MT6573_BusHW.Power[powerId].dwPowerCount > 0)
    {
        return TRUE;
    }
    /* Turn off PMU LDO*/
    MSG(CG,"[%d] PMU LDO Disable\r\n",powerId );            
    upmu_ldo_enable(powerId, KAL_FALSE);

    return TRUE;    
}

