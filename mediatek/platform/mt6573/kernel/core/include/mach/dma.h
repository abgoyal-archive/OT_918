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

#ifndef __ASM_ARCH_DMA_H
#define __ASM_ARCH_DMA_H

#define MAX_DMA_ADDRESS 0xffffffff
#define MAX_DMA_CHANNELS 0

#endif  /* !__ASM_ARCH_DMA_H */

#ifndef __MT6573_DMA_H__
#define __MT6573_DMA_H__

/* define DMA channels */
enum { 
    G_DMA_1 = 0, G_DMA_2,
    P_DMA_MSDC_1, P_DMA_MSDC_2, P_DMA_MSDC_3, P_DMA_MSDC_4,
    P_DMA_SIM1, P_DMA_SIM2,
    P_DMA_I2C1, P_DMA_I2C2,
    P_DMA_IRDA,
    P_DMA_UART1_TX, P_DMA_UART1_RX,
    P_DMA_UART2_TX, P_DMA_UART2_RX,
    P_DMA_UART3_TX, P_DMA_UART3_RX,
    P_DMA_UART4_TX, P_DMA_UART4_RX,
};

/* define DMA error code */
enum {
    DMA_ERR_CH_BUSY = 1,
    DMA_ERR_INVALID_CH = 2,
    DMA_ERR_CH_FREE = 3,
    DMA_ERR_NO_FREE_CH = 4,
    DMA_ERR_INV_CONFIG = 5,
};

/* define DMA config flag */
typedef enum 
{
    ALL = 0,
    SRC,
    DST,
    SRC_AND_DST
} DMA_CONF_FLAG;

/* define DMA burst length */
enum 
{ 
    DMA_CON_BURST_SINGLE = 0x00000000, 
    DMA_CON_BURST_2BEAT = 0x00010000, 
    DMA_CON_BURST_3BEAT = 0x00020000,
    DMA_CON_BURST_4BEAT = 0x00030000,
    DMA_CON_BURST_5BEAT = 0x00040000,
    DMA_CON_BURST_6BEAT = 0x00050000,
    DMA_CON_BURST_7BEAT = 0x00060000,
    DMA_CON_BURST_8BEAT = 0x00070000
};

/* define GDMA configurations */
struct mt65xx_gdma_conf
{
    unsigned int count;
    int iten;
    unsigned int burst;
    int dinc;
    int sinc;
    unsigned int limiter;
    unsigned int src;
    unsigned int dst;
    int wpen;
    int wpsd;
    unsigned int wplen;
    unsigned int wpto;
};

/* define DMA ISR callback function's prototype */
typedef void (*DMA_ISR_CALLBACK)(void *);

/* define GDMA running status query function */
#define mt65xx_gdma_running(c) (readl(AP_DMA_BASE + 0x0080 * ((c) + 1) + 0x0008) != 0)

extern int mt65xx_req_peri_dma(int channel, DMA_ISR_CALLBACK cb, void *data);
extern int mt65xx_req_vff_dma(int channel, DMA_ISR_CALLBACK cb, void *data);
extern int mt65xx_req_gdma(DMA_ISR_CALLBACK cb, void *data);
extern int mt65xx_config_gdma(int channel, struct mt65xx_gdma_conf *config, DMA_CONF_FLAG flag);
extern int mt65xx_start_gdma(int channel);
extern int mt65xx_stop_gdma(int channel);
extern int mt65xx_free_gdma(int channel);
extern void mt65xx_dma_running_status(void);

/*
 * NoteXXX: Implementation below is obsolete and deprecated.
 */

#include <linux/types.h>

typedef u32 INFO;

typedef enum
{
    DMA_FALSE = 0,
    DMA_TRUE
} DMA_BOOL;

typedef enum
{
    DMA_OK = 0,
    DMA_FAIL
} DMA_STATUS;

typedef enum
{
    REMAINING_LENGTH = 0, /* not valid for virtual FIFO */
    VF_READPTR,           /* only valid for virtual FIFO */
    VF_WRITEPTR,          /* only valid for virtual FIFO */
    VF_FFCNT,             /* only valid for virtual FIFO */
    VF_ALERT,             /* only valid for virtual FIFO */
    VF_EMPTY,             /* only valid for virtual FIFO */
    VF_FULL,              /* only valid for virtual FIFO */
    VF_PORT
} INFO_TYPE;

/* MASTER */   
/* keep for backward compatibility only */
#define DMA_CON_MASTER_SIM2         (0  << 20)
#define DMA_CON_MASTER_MSDC0        (1  << 20)
#define DMA_CON_MASTER_MSDC1        (2  << 20)
#define DMA_CON_MASTER_IRDATX       (3  << 20)
#define DMA_CON_MASTER_IRDARX       (4  << 20)
#define DMA_CON_MASTER_UART0TX      (5  << 20)
#define DMA_CON_MASTER_UART0RX      (6  << 20)
#define DMA_CON_MASTER_UART1TX      (7  << 20)
#define DMA_CON_MASTER_UART1RX      (8  << 20)
#define DMA_CON_MASTER_UART2TX      (9  << 20)
#define DMA_CON_MASTER_UART2RX      (10 << 20)
#define DMA_CON_MASTER_NFITX        (11 << 20)
#define DMA_CON_MASTER_NFIRX        (12 << 20)
#define DMA_CON_MASTER_VFE          (13 << 20)
#define DMA_CON_MASTER_I2CTX        (14 << 20)
#define DMA_CON_MASTER_I2CRX        (15 << 20)
#define DMA_CON_MASTER_UART3TX      (16 << 20)
#define DMA_CON_MASTER_UART3RX      (17 << 20)
#define DMA_CON_MASTER_MSDC2        (18 << 20)

/* burst */
#define DMA_CON_BURST_SINGLE 0x00000000
#define DMA_CON_BURST_2BEAT 0x00010000
#define DMA_CON_BURST_3BEAT 0x00020000
#define DMA_CON_BURST_4BEAT 0x00030000
#define DMA_CON_BURST_5BEAT 0x00040000
#define DMA_CON_BURST_6BEAT 0x00050000
#define DMA_CON_BURST_7BEAT 0x00060000
#define DMA_CON_BURST_8BEAT 0x00070000

/* size */                        
/* keep for backward compatibility only */
#define DMA_CON_SIZE_BYTE           	0x00000000
#define DMA_CON_SIZE_SHORT          	0x00000001
#define DMA_CON_SIZE_LONG           	0x00000002

/*
 *  configuration structure
 */

/*
 *  Full-Size    Half-Size    Virtual FIFO
 *          -            -               -
 *        SRC            -               -
 *        DST            -               -
 *       WPPT         WPPT               -
 *       WPTO         WPTO               - 
 *      COUNT        COUNT           COUNT
 *        CON          CON             CON
 *      START        START           START
 *     INTSTA       INTSTA          INTSTA
 *     ACKINT       ACKINT          ACKINT
 *       RLCT         RLCT            RLCT
 *    LIMITER      LIMITER         LIMITER
 *          -      PGMADDR         PGMADDR
 *          -            -           WRPTR
 *          -            -           RDPTR
 *          -            -           FFCNT
 *          -            -           FFSTA
 *          -            -          ALTLEN
 *          -            -          FFSIZE
 */

/*
 * ========================================
 * Definition
 * ========================================
 *    count: For full-size DMA channel and half-size DMA channel, it means the
 *           amount of data (in bytes) of current transfer. 
 *           But for virtual FIFO, it means the amount of data stored before 
 *           the interrupt is issued.
 *      mas: Obsolete.
 *     iten: TRUE: interrupt mode, FALSE: polling mode
 *    burst: Burst mode, use the symbolic symbols defined above to pass this 
 *           parameter. It means the number of beats before DMA controller 
 *           releases the bus.
 *     dreq: Obsolete.
 *     dinc: TRUE: destination address increases after a transfer. FALSE: 
 *           doesn't increase.
 *     sinc: TRUE: source address increases after a transfer. FALSE: doesn't 
 *           increase.
 *     size: Obsolete.
 *  limiter: Used to suppress DMA bus utilization. Range: 0 ~ 1023. Default: 0.
 *           At this time, simply pass 0 would be ok.
 *     data: The user data to be used in callback function.
 * callback: If the DMA channel is set to interrupt mode, then this function 
 *           will be called when DMA transfer is complete.
 * src, dst: Only valid for full-size DMA channel, used to set source and 
 *           destination addresses.
 *     wpen: Wrapping function enable/disable. TRUE: enable, FALSE: disable.
 *     wpsd: Choose the wrapping side. 0: wrap at source, 1: wrap at 
 *           destination.
 *     wppt: When the wrapping function is enabled, this value determines the amount of 
 *           transfer count from start address to jumping point.
 *     wpto: When the wrapping function is enabled, this value determines the 
 *           address where DMA transfer jumps to.
 *  pgmaddr: Only valid for half-size DMA channel and virtual FIFO. The address
 *           that could be chosen by programmer.
 *      dir: Only valid for half-size DMA channel and virtual FIFO. Indicates
 *           the data flow direction. write: from master to pgmaddr, read: from
 *           pgmaddr to master. 0: read, 1: write.
 *      b2w: Obsolete.
 *   altlen: Only valid for virtual FIFO. If the amount of data stored in 
 *           virtual exceeds this value, then DMA controller will issue an 
 *           alert signal to activate UART flow control is UART module supports 
 *           it.
 *   ffsize: Only valid for virtual FIFO. Determines the size of virtual FIFO.
 */

struct mt_dma_conf{             /*   full-size    half-size    virtual-FIFO */
    
    u32 count;                  /*           o            o               o */
    u32   mas;                  /*           o            o               o */
    DMA_BOOL iten;              /*           o            o               o */
    u32 burst;                  /*           o            o               o */
    DMA_BOOL dreq;              /*           o            o               o */
    DMA_BOOL dinc;              /*           o            o               o */
    DMA_BOOL sinc;              /*           o            o               o */
    u8 size;                    /*           o            o               o */
    u8 limiter;                 /*           o            o               o */
    void *data;                 /*           o            o               o */
    void (*callback)(void *);   /*           o            o               o */  
    u32 src;                    /*           o            x               x */
    u32 dst;                    /*           o            x               x */
    DMA_BOOL wpen;              /*           o            o               x */
    DMA_BOOL wpsd;              /*           o            o               x */
    u16 wppt;                   /*           o            o               x */
    u32 wpto;                   /*           o            o               x */
    u32 pgmaddr;                /*           x            o               o */
    DMA_BOOL dir;               /*           x            o               o */
    DMA_BOOL b2w;               /*           x            o               x */
    u8 altlen;                  /*           x            x               o */
    u16 ffsize;                 /*           x            x               o */
};

/* 
 * Function: 
 *    Request a full size type DMA channel.
 */
struct mt_dma_conf *mt_request_full_size_dma(void);

/* 
 * Function: 
 *    Request a full size type DMA channel.
 */
struct mt_dma_conf *mt_request_half_size_dma(void);

/* 
 * Function: 
 *    Request a half size type DMA channel.
 */
struct mt_dma_conf *mt_request_falf_size_dma(void);

/* 
 * Function: 
 *    Request a virual fifo type DMA channel with a specific channel.
 */
struct mt_dma_conf *mt_request_virtual_fifo_dma(unsigned int vf_dma_ch);

/*
 * Function: 
 *   Free the DMA channel previously granted.
 */
void mt_free_dma(struct mt_dma_conf *);

/*
 * Function: 
 *   Activate DMA transfer by the settings written into DMA controller
 *   registers. Note that before calling this function, you must call 
 *   mt_config_dma function to write the configuration stored in struct mt_dma_conf
 *   back into DMA controller registers.
 */
void mt_start_dma(struct mt_dma_conf *);

/*
 * Function:
 *   Stop DMA transfer of the granted channel.
 */
void mt_stop_dma(struct mt_dma_conf *);

/*
 * Function:
 *   Write the configuration stored in struct mt_dma_conf back into DMA 
 *   controller registers.
 */
DMA_STATUS mt_config_dma(struct mt_dma_conf *, DMA_CONF_FLAG flag);

/*
 * Function:
 *    Reset the configuration of the granted DMA channel. 
 */
void mt_reset_dma(struct mt_dma_conf *);

/*
 * Function:
 *    Get information of the granted DMA channel. The information is stored in
 *    INFO *info.
 * Returns:
 *    Whether the query succeeds.
 *       DMA_SUCCESS: success
 *       DMA_FAIL: fail
 */
DMA_STATUS mt_get_info(struct mt_dma_conf *, INFO_TYPE type, INFO *info);

#endif  /* !__MT6573_DMA_H__ */

