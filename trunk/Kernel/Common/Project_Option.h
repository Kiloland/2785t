/********************************************************************************/
/*   The  Software  is  proprietary,  confidential,  and  valuable to Realtek   */
/*   Semiconductor  Corporation  ("Realtek").  All  rights, including but not   */
/*   limited  to  copyrights,  patents,  trademarks, trade secrets, mask work   */
/*   rights, and other similar rights and interests, are reserved to Realtek.   */
/*   Without  prior  written  consent  from  Realtek,  copying, reproduction,   */
/*   modification,  distribution,  or  otherwise  is strictly prohibited. The   */
/*   Software  shall  be  kept  strictly  in  confidence,  and  shall  not be   */
/*   disclosed to or otherwise accessed by any third party.                     */
/*   c<2003> - <2012>                                                           */
/*   The Software is provided "AS IS" without any warranty of any kind,         */
/*   express, implied, statutory or otherwise.                                  */
/********************************************************************************/

//----------------------------------------------------------------------------------------------------
// ID Code      : Project_Option.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __PROJECT_OPTION_H__
#define __PROJECT_OPTION_H__

//--------------------------------------------------
// PWM Option
//--------------------------------------------------
#if((_MCU_PWM_BIT_SUPPORT == _PWM_8BIT) || (_MCU_PWM_BIT_SUPPORT == _PWM_12BIT))

#define MCU_ADJUST_8BIT_PWM_DUTY(x, y)                          {\
                                                                    (((x) == _PWM0) ? (MCU_FF4A_PWM0H_DUT = (y)) :\
                                                                     (((x) == _PWM1) ? (MCU_FF4B_PWM1H_DUT = (y)) :\
                                                                      (((x) == _PWM2) ? (MCU_FF4D_PWM2H_DUT = (y)) :\
                                                                       (((x) == _PWM3) ? (MCU_FF4E_PWM3H_DUT = (y)) :\
                                                                        (((x) == _PWM4) ? (MCU_FF50_PWM4H_DUT = (y)) :\
                                                                         (MCU_FF51_PWM5H_DUT = (y)))))));\
                                                                }


#define MCU_GET_8BIT_PWM_DUTY(x)                                (((x) == _PWM0) ? MCU_FF4A_PWM0H_DUT :\
                                                                  (((x) == _PWM1) ? MCU_FF4B_PWM1H_DUT :\
                                                                    (((x) == _PWM2) ? MCU_FF4D_PWM2H_DUT :\
                                                                     (((x) == _PWM3) ? MCU_FF4E_PWM3H_DUT :\
                                                                      (((x) == _PWM4) ? MCU_FF50_PWM4H_DUT :\
                                                                       MCU_FF51_PWM5H_DUT)))))

#endif

#if(_MCU_PWM_BIT_SUPPORT == _PWM_12BIT)

#define MCU_ADJUST_12BIT_PWM_DUTY(x, y)                         {\
                                                                    (((x) == _PWM0) ? (MCU_FF4C_PWM01L_DUT = ((((BYTE)(y)) & 0x0F) | (MCU_FF4C_PWM01L_DUT & 0xF0)), MCU_FF4A_PWM0H_DUT = (BYTE)((y) >> 4), MCU_FF46_PWML |= _BIT7) :\
                                                                     (((x) == _PWM1) ? (MCU_FF4C_PWM01L_DUT = ((((BYTE)((y) << 4)) & 0xF0) | (MCU_FF4C_PWM01L_DUT & 0x0F)), MCU_FF4B_PWM1H_DUT = (BYTE)((y) >> 4), MCU_FF46_PWML |= _BIT7) :\
                                                                      (((x) == _PWM2) ? (MCU_FF4F_PWM23L_DUT = ((((BYTE)(y)) & 0x0F) | (MCU_FF4F_PWM23L_DUT & 0xF0)), MCU_FF4D_PWM2H_DUT = (BYTE)((y) >> 4), MCU_FF46_PWML |= _BIT7) :\
                                                                       (((x) == _PWM3) ? (MCU_FF4F_PWM23L_DUT = ((((BYTE)((y) << 4)) & 0xF0) | (MCU_FF4F_PWM23L_DUT & 0x0F)), MCU_FF4E_PWM3H_DUT = (BYTE)((y) >> 4), MCU_FF46_PWML |= _BIT7) :\
                                                                        (((x) == _PWM4) ? (MCU_FF52_PWM45L_DUT = ((((BYTE)(y)) & 0x0F) | (MCU_FF52_PWM45L_DUT & 0xF0)), MCU_FF50_PWM4H_DUT = (BYTE)((y) >> 4), MCU_FF46_PWML |= _BIT7) :\
                                                                         (MCU_FF52_PWM45L_DUT = ((((BYTE)((y) << 4)) & 0xF0) | (MCU_FF52_PWM45L_DUT & 0x0F)), MCU_FF51_PWM5H_DUT = (BYTE)((y) >> 4), MCU_FF46_PWML |= _BIT7))))));\
                                                                }


#define MCU_GET_12BIT_PWM_DUTY(x)                               (((x) == _PWM0) ? (WORD)((((WORD)(MCU_FF4A_PWM0H_DUT)) << 4) | (((WORD)(MCU_FF4C_PWM01L_DUT)) & 0x000F)) :\
                                                                 (((x) == _PWM1) ? (WORD)((((WORD)(MCU_FF4B_PWM1H_DUT)) << 4) | ((((WORD)(MCU_FF4C_PWM01L_DUT)) & 0x00F0) >> 4)) :\
                                                                  (((x) == _PWM2) ? (WORD)((((WORD)(MCU_FF4D_PWM2H_DUT)) << 4) | (((WORD)(MCU_FF4F_PWM23L_DUT)) & 0x000F)) :\
                                                                   (((x) == _PWM3) ? (WORD)((((WORD)(MCU_FF4E_PWM3H_DUT)) << 4) | ((((WORD)(MCU_FF4F_PWM23L_DUT)) & 0x00F0) >> 4)) :\
                                                                    (((x) == _PWM4) ? (WORD)((((WORD)(MCU_FF50_PWM4H_DUT)) << 4) | (((WORD)(MCU_FF52_PWM45L_DUT)) & 0x000F)) :\
                                                                     (WORD)((((WORD)(MCU_FF51_PWM5H_DUT)) << 4) | ((((WORD)(MCU_FF52_PWM45L_DUT)) & 0x00F0) >> 4)))))))
#endif

//--------------------------------------------------
// OverScan Option
//--------------------------------------------------
#define _OVERSCAN_SUPPORT                                       ((_OVERSCAN_VGA_SUPPORT == _ON) ||\
                                                                 (_OVERSCAN_DVI_SUPPORT == _ON) ||\
                                                                 (_OVERSCAN_HDMI_SUPPORT == _ON) ||\
                                                                 (_OVERSCAN_DP_SUPPORT == _ON))

//--------------------------------------------------
// Force Even/Odd Mode Option
//--------------------------------------------------
#if((_SCALER_TYPE == _RL6369_SERIES) ||\
    (_SCALER_TYPE == _RL6432_SERIES) ||\
    (_SCALER_TYPE == _RL6463_SERIES) ||\
    (_SCALER_TYPE == _RL6492_SERIES))
#undef _FORMAT_CONVERSION_FORCE_EO_MODE
#define _FORMAT_CONVERSION_FORCE_EO_MODE                        _OFF
#endif

//-------------------------------------------------
// FreeSync Option
//-------------------------------------------------
#define _FREESYNC_SUPPORT                                       ((_DP_FREESYNC_SUPPORT == _ON) ||\
                                                                 (_HDMI_FREESYNC_SUPPORT == _ON))

//-------------------------------------------------
// FreeSync II Option
//-------------------------------------------------
#define _FREESYNC_II_SUPPORT                                    ((_DP_FREESYNC_II_SUPPORT == _ON) ||\
                                                                 (_HDMI_FREESYNC_II_SUPPORT == _ON))

//-------------------------------------------------
// HDR10 Option
//-------------------------------------------------
#define _HDR10_SUPPORT                                          ((_DP_HDR10_SUPPORT == _ON) ||\
                                                                 (_HDMI_HDR10_SUPPORT == _ON))

//-------------------------------------------------
// BAKCLIGHT DIMMING Option
//-------------------------------------------------
#define _BACKLIGHT_DIMMING_SUPPORT                              ((_LOCAL_DIMMING_SUPPORT == _ON) ||\
                                                                 (_GLOBAL_DIMMING_SUPPORT == _ON))

//-------------------------------------------------
// DP ULTRA HDR Option
//-------------------------------------------------
#define _DP_ULTRA_HDR_SUPPORT                                   ((_DP_HDR10_SUPPORT == _ON) ||\
                                                                 (_DP_FREESYNC_II_SUPPORT == _ON))

//-------------------------------------------------
// HDMI ULTRA HDR Option
//-------------------------------------------------
#define _HDMI_ULTRA_HDR_SUPPORT                                 ((_HDMI_HDR10_SUPPORT == _ON) ||\
                                                                 (_HDMI_FREESYNC_II_SUPPORT == _ON))

//-------------------------------------------------
// ULTRA HDR Option
//-------------------------------------------------
#define _ULTRA_HDR_SUPPORT                                      ((_HDR10_SUPPORT == _ON) ||\
                                                                 (_FREESYNC_II_SUPPORT == _ON))

//-------------------------------------------------
// Highlight Window for OD Option
//-------------------------------------------------
#define _HIGHLIGHT_WINDOW_SUPPORT_FOR_OD                        ((_OD_SUPPORT == _ON) &&\
                                                                 (_ASPECT_ORIGINAL_MODE_SUPPORT == _ON))

//-------------------------------------------------
// Scale Up
//-------------------------------------------------
#if(_SCALER_TYPE == _RL6369_SERIES)

#if(_FREESYNC_SUPPORT == _ON)
#define _VSU_3L_SUPPORT                                         _ON
#define _VSU_96TAPS_SUPPORT                                     _ON
#else
#define _VSU_3L_SUPPORT                                         _OFF
#define _VSU_96TAPS_SUPPORT                                     _OFF
#endif

#elif(_SCALER_TYPE == _RL6410_SERIES)
#define _VSU_3L_SUPPORT                                         _OFF
#define _VSU_96TAPS_SUPPORT                                     _OFF
#elif((_SCALER_TYPE == _RL6432_SERIES) ||\
      (_SCALER_TYPE == _RL6492_SERIES))
#define _VSU_3L_SUPPORT                                         _OFF
#define _VSU_96TAPS_SUPPORT                                     _OFF
#elif(_SCALER_TYPE == _RLE0779_SERIES)
#define _VSU_3L_SUPPORT                                         _OFF
#define _VSU_96TAPS_SUPPORT                                     _OFF
#elif(_SCALER_TYPE == _RL6449_SERIES)
#define _VSU_3L_SUPPORT                                         _OFF
#define _VSU_96TAPS_SUPPORT                                     _OFF
#elif(_SCALER_TYPE == _RL6463_SERIES)
#define _VSU_3L_SUPPORT                                         _ON
#define _VSU_96TAPS_SUPPORT                                     _ON
#endif

//-------------------------------------------------
// IAPS Gain Option
//-------------------------------------------------
#if(_IAPS_SUPPORT == _ON)

#if(_IAPS_GAIN_COMPENSATION_TYPE == _IAPS_GAIN_COMPENSATION_GEN_0)
#define _DCR_SOURCE                                             _DCR_BEFORE_DCC
#elif(_IAPS_GAIN_COMPENSATION_TYPE == _IAPS_GAIN_COMPENSATION_GEN_1)
#define _DCR_SOURCE                                             _DCR_BEFORE_IAPSGAIN
#endif

#elif(_DCR_SUPPORT == _ON)
#define _DCR_SOURCE                                             _DCR_BEFORE_DCC
#endif

//-------------------------------------------------
// Hue and Saturation Option
//-------------------------------------------------
#define _SATURATION_CENTER                                      ((_SATURATION_MAX + _SATURATION_MIN) / 2)
#define _HUE_CENTER                                             ((_HUE_MAX + _HUE_MIN) / 2)

//-------------------------------------------------
// OGC and OCC (On-Line Calibration) Option
//-------------------------------------------------
#if((_OUTPUT_GAMMA_TABLE_TYPE == _OUTPUT_GAMMA_GEN_0) && (_INPUT_GAMMA_TABLE_TYPE == _INPUT_GAMMA_GEN_0))
#define _OGC_GEN_TYPE                                           _OGC_GEN_0
#elif((_OUTPUT_GAMMA_TABLE_TYPE == _OUTPUT_GAMMA_GEN_1) && (_INPUT_GAMMA_TABLE_TYPE == _INPUT_GAMMA_GEN_1))
#define _OGC_GEN_TYPE                                           _OGC_GEN_1
#else
#define _OGC_GEN_TYPE                                           _GEN_NONE
#endif

//-------------------------------------------------
// Color IP Enable Option
//-------------------------------------------------
#define _COLOR_IP_COLOR_CONVERT                                 ((_ULTRA_VIVID_SUPPORT == _ON) ||\
                                                                 (_COLOR_FORMAT_CONVERT == _ON) ||\
                                                                 (_RGB_QUANTIZATION_RANGE_SUPPORT == _ON) ||\
                                                                 (_YCC_QUANTIZATION_RANGE_SUPPORT == _ON) ||\
                                                                 (_M_DOMAIN_FORCE_YUV_FORMAT == _ON))

//--------------------------------------------------
// DCR DCC Option
//--------------------------------------------------
#define _COLOR_IP_DCR                                           ((_DCR_SUPPORT == _ON) ||\
                                                                 (_IAPS_SUPPORT == _ON) ||\
                                                                 (_BACKLIGHT_DIMMING_SUPPORT == _ON))

#define _COLOR_IP_DCC_HISTOGRAM                                 ((_DCC_HISTOGRM_INFO == _ON) ||\
                                                                 (_ULTRA_HDR_SUPPORT == _ON))

#define _COLOR_IP_DCC                                           ((_DCC_FUNCTION == _ON) ||\
                                                                 (_HDR10_LIGHT_ENHANCE_SUPPORT == _ON) ||\
                                                                 ((_IAPS_SUPPORT == _ON) &&\
                                                                  (_IAPS_GAIN_COMPENSATION_TYPE == _IAPS_GAIN_COMPENSATION_GEN_0)))

//-------------------------------------------------
// EDID Address Option
//-------------------------------------------------
#define _EDID_A0_ADDRESS_EEPROM                                 (_EDID_ADDRESS_EEPROM)
#define _EDID_D0_ADDRESS_EEPROM                                 (_EDID_A0_ADDRESS_EEPROM + ((_A0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ? _A0_EMBEDDED_DDCRAM_MAX_SIZE : 0))
#define _EDID_D1_ADDRESS_EEPROM                                 (_EDID_D0_ADDRESS_EEPROM + ((_D0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ? _D0_EMBEDDED_DDCRAM_MAX_SIZE : 0))
#define _EDID_D2_ADDRESS_EEPROM                                 (_EDID_D1_ADDRESS_EEPROM + ((_D1_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ? _D1_EMBEDDED_DDCRAM_MAX_SIZE : 0))
#define _EDID_D3_ADDRESS_EEPROM                                 (_EDID_D2_ADDRESS_EEPROM + ((_D2_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ? _D2_EMBEDDED_DDCRAM_MAX_SIZE : 0))
#define _EDID_D4_ADDRESS_EEPROM                                 (_EDID_D3_ADDRESS_EEPROM + ((_D3_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ? _D3_EMBEDDED_DDCRAM_MAX_SIZE : 0))
#define _EDID_D5_ADDRESS_EEPROM                                 (_EDID_D4_ADDRESS_EEPROM + ((_D4_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ? _D4_EMBEDDED_DDCRAM_MAX_SIZE : 0))
#define _EDID_D6_ADDRESS_EEPROM                                 (_EDID_D5_ADDRESS_EEPROM + ((_D5_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ? _D5_EMBEDDED_DDCRAM_MAX_SIZE : 0))
#define _EDID_D0_MHL_ADDRESS_EEPROM                             (_EDID_D6_ADDRESS_EEPROM + ((_D6_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ? _D6_EMBEDDED_DDCRAM_MAX_SIZE : 0))
#define _EDID_D1_MHL_ADDRESS_EEPROM                             (_EDID_D0_MHL_ADDRESS_EEPROM + ((_D0_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ? _D0_MHL_EMBEDDED_DDCRAM_SIZE : 0))
#define _EDID_D2_MHL_ADDRESS_EEPROM                             (_EDID_D1_MHL_ADDRESS_EEPROM + ((_D1_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ? _D1_MHL_EMBEDDED_DDCRAM_SIZE : 0))
#define _EDID_D3_MHL_ADDRESS_EEPROM                             (_EDID_D2_MHL_ADDRESS_EEPROM + ((_D2_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ? _D2_MHL_EMBEDDED_DDCRAM_SIZE : 0))
#define _EDID_D4_MHL_ADDRESS_EEPROM                             (_EDID_D3_MHL_ADDRESS_EEPROM + ((_D3_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ? _D3_MHL_EMBEDDED_DDCRAM_SIZE : 0))
#define _EDID_D5_MHL_ADDRESS_EEPROM                             (_EDID_D4_MHL_ADDRESS_EEPROM + ((_D4_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ? _D4_MHL_EMBEDDED_DDCRAM_SIZE : 0))
#define _EDID_END_ADDRESS_EEPROM                                (_EDID_D5_MHL_ADDRESS_EEPROM + ((_D5_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ? _D5_MHL_EMBEDDED_DDCRAM_SIZE : 0))

#define _EDID_A0_ADDRESS_FLASH                                  (_EDID_ADDRESS_FLASH)
#define _EDID_D0_ADDRESS_FLASH                                  (_EDID_A0_ADDRESS_FLASH + ((_A0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ? _A0_EMBEDDED_DDCRAM_MAX_SIZE : 0))
#define _EDID_D1_ADDRESS_FLASH                                  (_EDID_D0_ADDRESS_FLASH + ((_D0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ? _D0_EMBEDDED_DDCRAM_MAX_SIZE : 0))
#define _EDID_D2_ADDRESS_FLASH                                  (_EDID_D1_ADDRESS_FLASH + ((_D1_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ? _D1_EMBEDDED_DDCRAM_MAX_SIZE : 0))
#define _EDID_D3_ADDRESS_FLASH                                  (_EDID_D2_ADDRESS_FLASH + ((_D2_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ? _D2_EMBEDDED_DDCRAM_MAX_SIZE : 0))
#define _EDID_D4_ADDRESS_FLASH                                  (_EDID_D3_ADDRESS_FLASH + ((_D3_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ? _D3_EMBEDDED_DDCRAM_MAX_SIZE : 0))
#define _EDID_D5_ADDRESS_FLASH                                  (_EDID_D4_ADDRESS_FLASH + ((_D4_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ? _D4_EMBEDDED_DDCRAM_MAX_SIZE : 0))
#define _EDID_D6_ADDRESS_FLASH                                  (_EDID_D5_ADDRESS_FLASH + ((_D5_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ? _D5_EMBEDDED_DDCRAM_MAX_SIZE : 0))
#define _EDID_D0_MHL_ADDRESS_FLASH                              (_EDID_D6_ADDRESS_FLASH + ((_D6_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ? _D6_EMBEDDED_DDCRAM_MAX_SIZE : 0))
#define _EDID_D1_MHL_ADDRESS_FLASH                              (_EDID_D0_MHL_ADDRESS_FLASH + ((_D0_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ? _D0_MHL_EMBEDDED_DDCRAM_SIZE : 0))
#define _EDID_D2_MHL_ADDRESS_FLASH                              (_EDID_D1_MHL_ADDRESS_FLASH + ((_D1_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ? _D1_MHL_EMBEDDED_DDCRAM_SIZE : 0))
#define _EDID_D3_MHL_ADDRESS_FLASH                              (_EDID_D2_MHL_ADDRESS_FLASH + ((_D2_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ? _D2_MHL_EMBEDDED_DDCRAM_SIZE : 0))
#define _EDID_D4_MHL_ADDRESS_FLASH                              (_EDID_D3_MHL_ADDRESS_FLASH + ((_D3_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ? _D3_MHL_EMBEDDED_DDCRAM_SIZE : 0))
#define _EDID_D5_MHL_ADDRESS_FLASH                              (_EDID_D4_MHL_ADDRESS_FLASH + ((_D4_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ? _D4_MHL_EMBEDDED_DDCRAM_SIZE : 0))
#define _EDID_END_ADDRESS_FLASH                                 (_EDID_D5_MHL_ADDRESS_FLASH + ((_D5_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ? _D5_MHL_EMBEDDED_DDCRAM_SIZE : 0))

//-------------------------------------------------
// VGA Digital Filter Option
//-------------------------------------------------
#define _DIGITAL_FILTER_SUPPORT                                 ((_DIG_FILTER_PHASE_ENABLE == _ENABLE) ||\
                                                                 (_DIG_FILTER_NSMEAR_ENABLE == _ENABLE) ||\
                                                                 (_DIG_FILTER_PSMEAR_ENABLE == _ENABLE) ||\
                                                                 (_DIG_FILTER_NRING_ENABLE == _ENABLE) ||\
                                                                 (_DIG_FILTER_PRING_ENABLE == _ENABLE) ||\
                                                                 (_DIG_FILTER_ENHANCE_PHASE_ENABLE == _ENABLE))

//-------------------------------------------------
// DP Link Rate Adjust Set
//-------------------------------------------------
#define DP_LINK_RATE_ADJUST(x, y)                               (((x) == _DP_FOUR_LANE) ? (((y) > 7200) ? _DP_LINK_HBR3 : (((y) > 3600) ? _DP_LINK_HBR2 : _DP_LINK_HBR)) :\
                                                                 (((x) == _DP_TWO_LANE) ? (((y) > 3600) ? _DP_LINK_HBR3 : (((y) > 1800) ? _DP_LINK_HBR2 : _DP_LINK_HBR)) :\
                                                                 (((y) > 1800) ? _DP_LINK_HBR3 : (((y) > 900) ? _DP_LINK_HBR2 : _DP_LINK_HBR))))

//-------------------------------------------------
// TMDS Clock On Line Measure Lower Boundary Set
//-------------------------------------------------
#ifndef _TMDS_CLOCK_MEASURE_LOWER_BOUNDARY
#define _TMDS_CLOCK_MEASURE_LOWER_BOUNDARY                      25
#endif

//--------------------------------------------------
// MHL Option
//--------------------------------------------------
#define _MHL_UCP_SUPPORT                                        ((_MHL2_UCP_SUPPORT == _ON) ||\
                                                                 (_MHL3_UCP_SUPPORT == _ON))

//--------------------------------------------------
// HDCP 2.2 Option
//--------------------------------------------------
#if((_TMDS_HDCP_2_2_SUPPORT == _ON) || (_DP_HDCP_2_2_SUPPORT == _ON))
#define _HDCP_2_2_SUPPORT                                       _ON
#define _HDCP_2_2_ERRATA_TEST_SUPPORT                           _OFF   // Use for HDCP 2.2 Kernel Function (Page 63) Off-Line Verify
#define _HDCP_2_2_TX_RSA3072_MODE                               _OFF   // Use for RSA 3072 bit-mode Verify (define _HDCP_2_2_ERRATA_TEST_SUPPORT need to turn-on & _HDCP_2_2_TX_RRMODN_BY_HW need to turn-off)
#define _HDCP_2_2_TX_RRMODN_BY_HW                               _OFF   // Use for RRMODN by HW Mode Verify (define _HDCP_2_2_ERRATA_TEST_SUPPORT & _HDCP_2_2_TX_RSA3072_MODE need to turn-on)
#define _HDCP_2_2_TX_ERRATA_TEST_SUPPORT                        _OFF
#else
#define _HDCP_2_2_SUPPORT                                       _OFF
#define _HDCP_2_2_ERRATA_TEST_SUPPORT                           _OFF
#define _HDCP_2_2_TX_RSA3072_MODE                               _OFF
#define _HDCP_2_2_TX_RRMODN_BY_HW                               _OFF
#define _HDCP_2_2_TX_ERRATA_TEST_SUPPORT                        _OFF
#endif

//-------------------------------------------------
// Type C SRC Default Curent Provide Option
//-------------------------------------------------
#if((_TYPE_C_EMB_PORT_ROLE == _TYPE_C_PORT_SRC_ONLY) || (_TYPE_C_EMB_PORT_ROLE == _TYPE_C_PORT_DRP))
#define _TYPE_C_SRC_DEF_CUR                                     _TYPE_C_SRC_DEF_3P0A
#else
#define _TYPE_C_SRC_DEF_CUR                                     _TYPE_C_SRC_DEF_USB
#endif

//-------------------------------------------------
// Type C DRP Preference Option
//-------------------------------------------------
#if(_TYPE_C_EMB_PORT_ROLE == _TYPE_C_PORT_DRP)
#define _TYPE_C_DRP_PREFER                                      _TYPE_C_DRP_TRY_SNK
#else
#define _TYPE_C_DRP_PREFER                                      _TYPE_C_DRP_NO_PREFERENCE
#endif

//-------------------------------------------------
// Audio Option
//-------------------------------------------------
#if(_AUDIO_SUPPORT == _OFF)
#undef _EMBEDDED_DAC_SUPPORT
#undef _LINE_IN_SUPPORT
#undef _SLEEP_AUDIO_SUPPORT
#define _EMBEDDED_DAC_SUPPORT                                   _OFF
#define _LINE_IN_SUPPORT                                        _OFF
#define _SLEEP_AUDIO_SUPPORT                                    _OFF
#endif

//-------------------------------------------------
// Audio Line In Option
//-------------------------------------------------
#define _LINE_IN_VOLUME_CENTER                                  ((_LINE_IN_VOLUME_MAX + _LINE_IN_VOLUME_MIN) / 2)

//-------------------------------------------------
// Audio Digital Option
//-------------------------------------------------
#define _DIGITAL_VOLUME_CENTER                                  ((_DIGITAL_VOLUME_MAX + _DIGITAL_VOLUME_MIN) / 2)

//-------------------------------------------------
// MCU Speed Up Option
//-------------------------------------------------
#define _MCU_SPEED_UP_SUPPORT                                   (_LOCAL_DIMMING_SUPPORT == _ON)

//--------------------------------------------------
// MCU CKCON Option
//--------------------------------------------------
#if(_MCU_SPEED_UP_SUPPORT == _ON)
#define _CKCON_MCU_SLOW_CYCLE                                   _CKCON_MOVX_9_CYCLE
#else
#define _CKCON_MCU_SLOW_CYCLE                                   _CKCON_MOVX_DEFAULT_CYCLE
#endif

//-------------------------------------------------
// Eizo Cache Power Saving Option
//-------------------------------------------------
#if((_SCALER_TYPE == _RL6410_SERIES) ||\
    (_SCALER_TYPE == _RL6449_SERIES) ||\
    (_SCALER_TYPE == _RLE0779_SERIES) ||\
    (_SCALER_TYPE == _RL6463_SERIES) ||\
    (_SCALER_TYPE == _RL6492_SERIES))
#undef _CACHE_PS_SWITCH
#define _CACHE_PS_SWITCH                                        _ENABLE
#endif

//--------------------------------------------------
// QC Option
//--------------------------------------------------
#include "QC_Option.h"

//--------------------------------------------------
// Auto Test Option
//--------------------------------------------------
#include "AT_Option.h"

#endif // End of #ifndef __PROJECT_OPTION_H__
