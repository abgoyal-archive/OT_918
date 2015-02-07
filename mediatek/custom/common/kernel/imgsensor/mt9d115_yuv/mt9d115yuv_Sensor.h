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
 *   sensor.h
 *
 * Project:
 * --------
 *   DUMA
 *
 * Description:
 * ------------
 *   Header file of Sensor driver
 *
 *
 * Author:
 * -------
 *   PC Huang (MTK02204)
 *
 *============================================================================
 *             HISTORY
 * Below this line, this part is controlled by CC/CQ. DO NOT MODIFY!!
 *------------------------------------------------------------------------------
 * $Revision:$
 * $Modtime:$
 * $Log:$
 *
 * Mar 4 2010 mtk70508
 * [DUMA00154792] Sensor driver
 * 
 *
 * Feb 24 2010 mtk01118
 * [DUMA00025869] [Camera][YUV I/F & Query feature] check in camera code
 * 
 *
 * Aug 5 2009 mtk01051
 * [DUMA00009217] [Camera Driver] CCAP First Check In
 * 
 *
 * Apr 7 2009 mtk02204
 * [DUMA00004012] [Camera] Restructure and rename camera related custom folders and folder name of came
 * 
 *
 * Mar 26 2009 mtk02204
 * [DUMA00003515] [PC_Lint] Remove PC_Lint check warnings of camera related drivers.
 * 
 *
 * Mar 2 2009 mtk02204
 * [DUMA00001084] First Check in of MT6516 multimedia drivers
 * 
 *
 * Feb 24 2009 mtk02204
 * [DUMA00001084] First Check in of MT6516 multimedia drivers
 * 
 *
 * Dec 27 2008 MTK01813
 * DUMA_MBJ CheckIn Files
 * created by clearfsimport
 *
 * Dec 10 2008 mtk02204
 * [DUMA00001084] First Check in of MT6516 multimedia drivers
 * 
 *
 * Oct 27 2008 mtk01051
 * [DUMA00000851] Camera related drivers check in
 * Modify Copyright Header
 *
 *
 *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by CC/CQ. DO NOT MODIFY!!
 *============================================================================
 ****************************************************************************/
/* SENSOR FULL SIZE */
#ifndef __SENSOR_H
#define __SENSOR_H

typedef enum _MT9D115_OP_TYPE_ {
        MT9D115_MODE_NONE,
        MT9D115_MODE_PREVIEW,
        MT9D115_MODE_CAPTURE,
        MT9D115_MODE_QCIF_VIDEO,
        MT9D115_MODE_CIF_VIDEO,
        MT9D115_MODE_QVGA_VIDEO
    } MT9D115_OP_TYPE;

extern MT9D115_OP_TYPE MT9D115_g_iMT9D115_Mode;


/* SENSOR FULL/PV SIZE */
#define MT9D115_IMAGE_SENSOR_FULL_WIDTH_DRV   1600
#define MT9D115_IMAGE_SENSOR_FULL_HEIGHT_DRV  1200
#define MT9D115_IMAGE_SENSOR_PV_WIDTH_DRV     (MT9D115_IMAGE_SENSOR_FULL_WIDTH_DRV / 2)
#define MT9D115_IMAGE_SENSOR_PV_HEIGHT_DRV    (MT9D115_IMAGE_SENSOR_FULL_HEIGHT_DRV / 2)

/* SENSOR HORIZONTAL/VERTICAL ACTIVE REGION */
#define MT9D115_IMAGE_SENSOR_FULL_HACTIVE     MT9D115_IMAGE_SENSOR_FULL_WIDTH_DRV /* 1600 */
#define MT9D115_IMAGE_SENSOR_FULL_VACTIVE     MT9D115_IMAGE_SENSOR_FULL_HEIGHT_DRV /* 1200 */
#define MT9D115_IMAGE_SENSOR_PV_HACTIVE       MT9D115_IMAGE_SENSOR_PV_WIDTH_DRV /* 800 */
#define MT9D115_IMAGE_SENSOR_PV_VACTIVE       MT9D115_IMAGE_SENSOR_PV_HEIGHT_DRV /* 600 */

/* SENSOR HORIZONTAL/VERTICAL BLANKING IN ONE PERIOD */
#if (defined(DRV_ISP_YUV_BURST_MODE_SUPPORT))
#define MT9D115_IMAGE_SENSOR_FULL_HBLANKING   634 /* MT6253 capture frame rate limit to 9fps */
#else
#define MT9D115_IMAGE_SENSOR_FULL_HBLANKING   380
#endif
#define MT9D115_IMAGE_SENSOR_FULL_VBLANKING   93
#define MT9D115_IMAGE_SENSOR_PV_HBLANKING     550
#define MT9D115_IMAGE_SENSOR_PV_VBLANKING     91

/* SENSOR PIXEL/LINE NUMBERS IN ONE PERIOD */
#define MT9D115_FULL_PERIOD_PIXEL_NUMS        (MT9D115_IMAGE_SENSOR_FULL_HACTIVE + MT9D115_IMAGE_SENSOR_FULL_HBLANKING) /* 53: 2234, other: 1980 */
#define MT9D115_FULL_PERIOD_LINE_NUMS         (MT9D115_IMAGE_SENSOR_FULL_VACTIVE + MT9D115_IMAGE_SENSOR_FULL_VBLANKING) /* 1293 */
#define MT9D115_PV_PERIOD_PIXEL_NUMS          (MT9D115_IMAGE_SENSOR_PV_HACTIVE + MT9D115_IMAGE_SENSOR_PV_HBLANKING) /* 1350 */
#define MT9D115_PV_PERIOD_LINE_NUMS           (MT9D115_IMAGE_SENSOR_PV_VACTIVE + MT9D115_IMAGE_SENSOR_PV_VBLANKING) /* 691 */

/* SENSOR START/END POSITION */
#define MT9D115_FULL_X_START                  8
#define MT9D115_FULL_Y_START                  6
#define MT9D115_IMAGE_SENSOR_FULL_WIDTH       (MT9D115_IMAGE_SENSOR_FULL_HACTIVE - MT9D115_FULL_X_START * 2) /* 1584 */
#define MT9D115_IMAGE_SENSOR_FULL_HEIGHT      (MT9D115_IMAGE_SENSOR_FULL_VACTIVE - MT9D115_FULL_Y_START * 2) /* 1188 */
#define MT9D115_PV_X_START                    (MT9D115_FULL_X_START / 2) /* 4 */
#define MT9D115_PV_Y_START                    (MT9D115_FULL_Y_START / 2) /* 3 */
#define MT9D115_IMAGE_SENSOR_PV_WIDTH         (MT9D115_IMAGE_SENSOR_PV_HACTIVE - MT9D115_PV_X_START * 2) /* 792 */
#define MT9D115_IMAGE_SENSOR_PV_HEIGHT        (MT9D115_IMAGE_SENSOR_PV_VACTIVE - MT9D115_PV_Y_START * 2) /* 594 */


/* AE TARGET ZERO when EV = 0. MUST BE > 40 !!! */
#define MT9D115_AE_TARGET_ZERO                67

/* ANALOG GAIN BASE */
#define MT9D115_ANALOG_GAIN_BASE              0x10 /* 1x: reg / 0x10 */

/* LIMIT OF ANALOG GAIN: if too large will cause yellow frame!!! */
#define MT9D115_MAX_ANALOG_GAIN               (MT9D115_ANALOG_GAIN_BASE * 10)

/* 50HZ/60HZ */
#define MT9D115_NUM_50HZ                      50
#define MT9D115_NUM_60HZ                      60

/* SENSOR READ/WRITE ID */
#define MT9D115_SLV1_WRITE_ID                 0x78
#define MT9D115_SLV1_READ_ID                  0x79
#define MT9D115_SLV2_WRITE_ID                 0x7A
#define MT9D115_SLV2_READ_ID                  0x7B

#define MT9D115_SENSOR_ID                       0x2580


struct MT9D115_sensor_STRUCT
{
  kal_uint32 banding;
  kal_uint32 effect;
  kal_uint32 exposure;
  kal_uint32 wb;
  kal_uint8 mirror;
  kal_bool night_mode;
  kal_bool video_frame;
  kal_bool pv_mode;
  kal_bool video_mode;
  kal_bool initial;
  kal_bool first_pv;
  kal_uint16 normal_fps; /* normal mode min fps */
  kal_uint16 night_fps; /* night mode min fps */
#ifndef MT9D115_HW_SCCB
  kal_uint8 write_id;
  kal_uint8 read_id;
#endif
  kal_uint32 pclk;
  kal_uint16 shutter;
  kal_uint16 pv_frame_height;
  kal_uint16 pv_line_length;
  kal_uint16 cap_frame_height;
  kal_uint16 cap_line_length;
};
extern 	struct MT9D115_sensor_STRUCT MT9D115_sensor;
/* FRAME RATE UNIT */
#define MT9D115_FRAME_RATE_UNIT               10

//export functions
UINT32 MT9D115Open(void);
UINT32 MT9D115GetResolution(MSDK_SENSOR_RESOLUTION_INFO_STRUCT *pSensorResolution);
UINT32 MT9D115GetInfo(MSDK_SCENARIO_ID_ENUM ScenarioId, MSDK_SENSOR_INFO_STRUCT *pSensorInfo, MSDK_SENSOR_CONFIG_STRUCT *pSensorConfigData);
UINT32 MT9D115Control(MSDK_SCENARIO_ID_ENUM ScenarioId, MSDK_SENSOR_EXPOSURE_WINDOW_STRUCT *pImageWindow, MSDK_SENSOR_CONFIG_STRUCT *pSensorConfigData);
UINT32 MT9D115FeatureControl(MSDK_SENSOR_FEATURE_ENUM FeatureId, UINT8 *pFeaturePara,UINT32 *pFeatureParaLen);
UINT32 MT9D115Close(void);

#endif /* __SENSOR_H */
