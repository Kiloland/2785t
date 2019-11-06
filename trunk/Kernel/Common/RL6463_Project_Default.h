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
// ID Code      : RL6463_Project_Default.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


/////////////
// General //
/////////////

//--------------------------------------------------
// Pcb Option
//--------------------------------------------------
#ifndef _PCB_TYPE
#define _PCB_TYPE                                               _RL6463_PCB_EXAMPLE_128_PIN
#endif

//--------------------------------------------------
// Panel Option
//--------------------------------------------------
#ifndef _PANEL_TYPE
#define _PANEL_TYPE                                             _PANEL_NONE
#endif

#ifndef _PANEL_POW_SEQ_FAST_MODE
#define _PANEL_POW_SEQ_FAST_MODE                                _ON
#endif

//==================== START ======================
#ifndef _PANEL_POWER_ON_BEFORE_COLOR_SETTING
#define _PANEL_POWER_ON_BEFORE_COLOR_SETTING                    _OFF
#endif
//===================== END =======================

//--------------------------------------------------
// Osd Option
//--------------------------------------------------
#ifndef _OSD_TYPE
#define _OSD_TYPE                                               _NONE_OSD
#endif

//--------------------------------------------------
// OSD Window & Font Align to DEN Option
//--------------------------------------------------
#ifndef _OSD_POSITION_OFFSET_CORRECTION
#define _OSD_POSITION_OFFSET_CORRECTION                         _OFF
#endif

//--------------------------------------------------
// OSD Position Align Option
//--------------------------------------------------
#ifndef _OSD_POSITION_SELF_ALIGNMENT
#define _OSD_POSITION_SELF_ALIGNMENT                            _OFF
#endif

//==================== START ======================

//--------------------------------------------------
// Scaler or Translator Option
//--------------------------------------------------
#ifndef _TRANSLATOR_SUPPORT
#define _TRANSLATOR_SUPPORT                                     _OFF
#endif

//--------------------------------------------------
// Flash Partition
//--------------------------------------------------
#ifndef _FLASH_PARTITION_TYPE
#define _FLASH_PARTITION_TYPE                                   _FLASH_PARTITION_NONE
#endif

//===================== END =======================


///////////
// DDCCI //
///////////

//-------------------------------------------------
// DDCCI Option
//-------------------------------------------------
#ifndef _DDCCI_RXBUF_LENGTH
#define _DDCCI_RXBUF_LENGTH                                     16
#endif

#ifndef _DDCCI_TXBUF_LENGTH
#define _DDCCI_TXBUF_LENGTH                                     16
#endif

#ifndef _DDCCI_TIMEOUT_LIMIT
#define _DDCCI_TIMEOUT_LIMIT                                    50 // 0~65535ms
#endif

#ifndef _CAPABILITIES_STRING_VGA
#define _CAPABILITIES_STRING_VGA                                "(prot(monitor)type(LCD)model(RTK)cmds(01 02 03 07 0C E3 F3)vcp(02)mswhql(1)asset_eep(40)mccs_ver(2.2))"
#endif

#ifndef _CAPABILITIES_STRING_DVI
#define _CAPABILITIES_STRING_DVI                                "(prot(monitor)type(LCD)model(RTK)cmds(01 02 03 07 0C E3 F3)vcp(02)mswhql(1)asset_eep(40)mccs_ver(2.2))"
#endif

#ifndef _CAPABILITIES_STRING_HDMI
#define _CAPABILITIES_STRING_HDMI                               "(prot(monitor)type(LCD)model(RTK)cmds(01 02 03 07 0C E3 F3)vcp(02)mswhql(1)asset_eep(40)mccs_ver(2.2))"
#endif

#ifndef _CAPABILITIES_STRING_DP
#define _CAPABILITIES_STRING_DP                                 "(prot(monitor)type(LCD)model(RTK)cmds(01 02 03 07 0C E3 F3)vcp(02)mswhql(1)asset_eep(40)mccs_ver(2.2))"
#endif

//-------------------------------------------------
// DDCCI Auto Switch Option
//-------------------------------------------------
#ifndef _DDCCI_AUTO_SWITCH_SUPPORT
#define _DDCCI_AUTO_SWITCH_SUPPORT                              _OFF
#endif

//==================== START ======================

//-------------------------------------------------
// DDCCI On Line Display Calibration OP Code Option
//-------------------------------------------------
#ifndef _DDCCI_OPCODE_VCP_DISP_CALIBRATION
#define _DDCCI_OPCODE_VCP_DISP_CALIBRATION                      0xFC
#endif

//===================== END =======================


/////////////////////
// Display Setting //
/////////////////////

//-------------------------------------------------
// Embedded Memory Size Option
//-------------------------------------------------
#ifndef _EMBEDDED_MEMORY_SIZE_CONFIG
#define _EMBEDDED_MEMORY_SIZE_CONFIG                            _EMBEDDED_MEMORY_SIZE_NONE
#endif

//-------------------------------------------------
// OD Option
//-------------------------------------------------
#ifndef _OD_SUPPORT
#define _OD_SUPPORT                                             _OFF
#endif

//-------------------------------------------------
// FRC Option
//-------------------------------------------------
#ifndef _FRC_SUPPORT
#define _FRC_SUPPORT                                            _OFF
#endif

//--------------------------------------------------
// Aspect Ratio Option
//--------------------------------------------------
#ifndef _ASPECT_RATIO_SUPPORT
#define _ASPECT_RATIO_SUPPORT                                   _OFF
#endif

//==================== START ======================
#ifndef _ASPECT_RATIO_WITHOUT_MUTE
#define _ASPECT_RATIO_WITHOUT_MUTE                              _OFF
#endif
//===================== END =======================

//--------------------------------------------------
// Overscan Option
//--------------------------------------------------
#ifndef _OVERSCAN_VGA_SUPPORT
#define _OVERSCAN_VGA_SUPPORT                                   _OFF
#endif

#ifndef _OVERSCAN_DVI_SUPPORT
#define _OVERSCAN_DVI_SUPPORT                                   _OFF
#endif

#ifndef _OVERSCAN_HDMI_SUPPORT
#define _OVERSCAN_HDMI_SUPPORT                                  _OFF
#endif

#ifndef _OVERSCAN_DP_SUPPORT
#define _OVERSCAN_DP_SUPPORT                                    _OFF
#endif

#ifndef _OVERSCAN_H_RATIO
#define _OVERSCAN_H_RATIO                                       30
#endif

#ifndef _OVERSCAN_V_RATIO
#define _OVERSCAN_V_RATIO                                       30
#endif

//-------------------------------------------------
// Adjust H & V Position Max Range Option
//-------------------------------------------------
#ifndef _MAX_H_POSITION_RANGE
#define _MAX_H_POSITION_RANGE                                   100 // Pixel
#endif

#ifndef _MAX_V_POSITION_RANGE
#define _MAX_V_POSITION_RANGE                                   100 // Line
#endif

//==================== START ======================

//-------------------------------------------------
// Force Display Free Run Option --> For Last Line Issue Panel
//-------------------------------------------------
#ifndef _FORCE_TO_FREE_RUN_SUPPORT
#define _FORCE_TO_FREE_RUN_SUPPORT                              _OFF
#endif

//-------------------------------------------------
// Disable MN Frame Sync -> Force to Free Run
//-------------------------------------------------
#ifndef _MN_FRAMESYNC_FORCE_TO_FREERUN
#define _MN_FRAMESYNC_FORCE_TO_FREERUN                          _OFF
#endif

//--------------------------------------------------
// Display Frame Sync Line Buffer Option
//--------------------------------------------------
#ifndef _FRAME_SYNC_LINE_BUFFER_SUPPORT
#define _FRAME_SYNC_LINE_BUFFER_SUPPORT                         _ON
#endif

//-------------------------------------------------
// Freeze Mode Option
//-------------------------------------------------
#ifndef _FREEZE_SUPPORT
#define _FREEZE_SUPPORT                                         _OFF
#endif

//--------------------------------------------------
// Display Frame Sync Frame Buffer Latency Option
//--------------------------------------------------
#ifndef _DISP_LATENCY_ADJUST_SUPPORT
#define _DISP_LATENCY_ADJUST_SUPPORT                            _OFF
#endif

//-------------------------------------------------
// Display PLL Jitter Margin
//-------------------------------------------------
#ifndef _DPLL_JITTER_MARGIN
#define _DPLL_JITTER_MARGIN                                     _DPLL_1_PERCENT_JITTER_MARGIN
#endif

//-------------------------------------------------
// Eizo Request Dclk Accuracy
//-------------------------------------------------
#ifndef _DCLK_ACCURACY
#define _DCLK_ACCURACY                                          _OFF
#endif

//===================== END =======================


////////////////////
// Color Function //
////////////////////

//--------------------------------------------------
// Digital Functional Option
//--------------------------------------------------
#ifndef _I_DITHER_SUPPORT
#define _I_DITHER_SUPPORT                                       _OFF
#endif

#ifndef _D_DITHER_SUPPORT
#define _D_DITHER_SUPPORT                                       _OFF
#endif

#ifndef _GAMMA_FUNCTION
#define _GAMMA_FUNCTION                                         _OFF
#endif

#ifndef _COLOR_FORMAT_CONVERT
#define _COLOR_FORMAT_CONVERT                                   _OFF
#endif

#ifndef _RGB_QUANTIZATION_RANGE_SUPPORT
#define _RGB_QUANTIZATION_RANGE_SUPPORT                         _OFF
#endif
//==================== START ======================
#ifndef _RGB_QUANTIZATION_DEFAULT_RANGE_JUDGE_BY_USER
#define _RGB_QUANTIZATION_DEFAULT_RANGE_JUDGE_BY_USER           _OFF
#endif
//===================== END ======================

#ifndef _YCC_QUANTIZATION_RANGE_SUPPORT
#define _YCC_QUANTIZATION_RANGE_SUPPORT                         _OFF
#endif

#ifndef _ULTRA_VIVID_SUPPORT
#define _ULTRA_VIVID_SUPPORT                                    _OFF
#endif

#ifndef _DCR_SUPPORT
#define _DCR_SUPPORT                                            _OFF
#endif

#ifndef _DCC_FUNCTION
#define _DCC_FUNCTION                                           _OFF
#endif

#ifndef _DCC_HISTOGRM_INFO
#define _DCC_HISTOGRM_INFO                                      _OFF
#endif

#ifndef _ICM_SUPPORT
#define _ICM_SUPPORT                                            _OFF
#endif

#ifndef _ICM_BRI_SUPPORT
#define _ICM_BRI_SUPPORT                                        _OFF
#endif

#ifndef _SIX_COLOR_SUPPORT
#define _SIX_COLOR_SUPPORT                                      _OFF
#endif

#ifndef _HIGHLIGHT_WINDOW_SUPPORT
#define _HIGHLIGHT_WINDOW_SUPPORT                               _OFF
#endif

#ifndef _RINGING_FILTER_SUPPORT
#define _RINGING_FILTER_SUPPORT                                 _OFF
#endif

#ifndef _SHARPNESS_SUPPORT
#define _SHARPNESS_SUPPORT                                      _OFF
#endif

#ifndef _CONTRAST_SUPPORT
#define _CONTRAST_SUPPORT                                       _OFF
#endif

#ifndef _BRIGHTNESS_SUPPORT
#define _BRIGHTNESS_SUPPORT                                     _OFF
#endif

//==================== START ======================
#ifndef _ADCNR_SUPPORT
#define _ADCNR_SUPPORT                                          _ON
#endif
//===================== END ======================

//==================== START ======================
#ifndef _SIX_COLOR_ICM_TYPE
#define _SIX_COLOR_ICM_TYPE                                     _SIX_COLOR_ICM_NORMAL_MODE
#endif
//===================== END ======================

//-------------------------------------------------
// Hue and Saturation Option
//-------------------------------------------------
#ifndef _GLOBAL_HUE_SATURATION
#define _GLOBAL_HUE_SATURATION                                  _OFF
#endif

#ifndef _HUE_MAX
#define _HUE_MAX                                                230
#endif

#ifndef _HUE_MIN
#define _HUE_MIN                                                30
#endif

#ifndef _SATURATION_MAX
#define _SATURATION_MAX                                         200
#endif

#ifndef _SATURATION_MIN
#define _SATURATION_MIN                                         0
#endif

//--------------------------------------------------
// Y Peaking Option
//--------------------------------------------------
#ifndef _YPEAKING_SUPPORT
#define _YPEAKING_SUPPORT                                       _OFF
#endif

#ifndef _YPEAKING_CORING_MIN
#define _YPEAKING_CORING_MIN                                    3     // effective:0~31
#endif

#ifndef _YPEAKING_MAX_POS
#define _YPEAKING_MAX_POS                                       20    // effective:0~255
#endif

#ifndef _YPEAKING_MAX_NEG
#define _YPEAKING_MAX_NEG                                       (-40) // effective:-128~127
#endif

//-------------------------------------------------
// IAPS Option
//-------------------------------------------------
#ifndef _IAPS_SUPPORT
#define _IAPS_SUPPORT                                           _OFF
#endif

//==================== START ======================
#ifndef _IAPS_CONTRAST_TARGET
#define _IAPS_CONTRAST_TARGET                                   0x2000
#endif

#ifndef _IAPS_GAIN_CLAMP_FACTOR
#define _IAPS_GAIN_CLAMP_FACTOR                                 0xB0
#endif
//===================== END ======================


////////////////////////////////////////
// Off-Line Display Color Calibration //
////////////////////////////////////////

//-------------------------------------------------
// PCM (Load Code Table) Option
//-------------------------------------------------
#ifndef _PCM_FUNCTION
#define _PCM_FUNCTION                                           _OFF
#endif


////////////////////////////////////////
// On-Line Display Color Calibration //
////////////////////////////////////////

//-------------------------------------------------
// OGC and OCC (On-Line Calibration) Option
//-------------------------------------------------
#ifndef _OCC_SUPPORT
#define _OCC_SUPPORT                                            _OFF
#endif

#ifndef _OGC_SUPPORT
#define _OGC_SUPPORT                                            _OFF
#endif

#ifndef _OGC_DICOM_SUPPORT
#define _OGC_DICOM_SUPPORT                                      _OFF
#endif

#ifndef _OGC_TOTAL_GAMMA
#define _OGC_TOTAL_GAMMA                                        1 // 1/2/3/4/5
#endif

#ifndef _OGC_TOTAL_CT
#define _OGC_TOTAL_CT                                           1
#endif

#ifndef _OGC_FLASH_BANK
#define _OGC_FLASH_BANK                                         0
#endif

#ifndef _OGC_FLASH_PAGE
#define _OGC_FLASH_PAGE                                         0
#endif


////////////
// Eeprom //
////////////

//-------------------------------------------------
// Eeprom Access Function Option
//-------------------------------------------------
#ifndef _EEPROM_ACCESS_FUNCTION_SUPPORT
#define _EEPROM_ACCESS_FUNCTION_SUPPORT                         _OFF
#endif

#ifndef _EEPROM_KERNEL_START_ADDRESS
#define _EEPROM_KERNEL_START_ADDRESS                            (_EEPROM_PAGE0_BANK0)
#endif


///////////
// Flash //
///////////

//-------------------------------------------------
// Flash Clock Option
//-------------------------------------------------
#ifndef _FLASH_CLK_SPEED
#define _FLASH_CLK_SPEED                                        _FLASH_FAST_SPEED
#endif

//-------------------------------------------------
// Flash Access Function Option
//-------------------------------------------------
#ifndef _FLASH_WRITE_FUNCTION_SUPPORT
#define _FLASH_WRITE_FUNCTION_SUPPORT                           _OFF
#endif

#ifndef _FLASH_READ_FUNCTION_SUPPORT
#define _FLASH_READ_FUNCTION_SUPPORT                            _OFF
#endif

#ifndef _FLASH_TYPE_W25X20A_OR_W25X21CL
#define _FLASH_TYPE_W25X20A_OR_W25X21CL                         _FLASH_W25X20A
#endif

#ifndef _FLASH_TYPE_W25X40CL_OR_W25X41CL
#define _FLASH_TYPE_W25X40CL_OR_W25X41CL                        _FLASH_W25X40CL
#endif

#ifndef _FLASH_TYPE_GD25Q16C_OR_GD25Q16
#define _FLASH_TYPE_GD25Q16C_OR_GD25Q16                         _FLASH_GD25Q16C
#endif

#ifndef _FLASH_TYPE_MX25L3206E_OR_MX25L3233F_OR_KH25L3236F
#define _FLASH_TYPE_MX25L3206E_OR_MX25L3233F_OR_KH25L3236F      _FLASH_MX25L3233F
#endif

#ifndef _FLASH_TYPE_GD25Q40B_OR_GD25Q41B
#define _FLASH_TYPE_GD25Q40B_OR_GD25Q41B                        _FLASH_GD25Q41B
#endif

#ifndef _FLASH_TYPE_W25Q16DV_OR_W25Q16JVSIQ
#define _FLASH_TYPE_W25Q16DV_OR_W25Q16JVSIQ                     _FLASH_W25Q16JVSIQ
#endif

#ifndef _FLASH_TYPE_FM25Q08_OR_FM25Q08A
#define _FLASH_TYPE_FM25Q08_OR_FM25Q08A                         _FLASH_FM25Q08A
#endif

#ifndef _FLASH_TYPE_BY25D40C_OR_BY25D40ASTIG
#define _FLASH_TYPE_BY25D40C_OR_BY25D40ASTIG                    _FLASH_BY25D40C
#endif

//-------------------------------------------------
// EEPROM Emulation Option
//-------------------------------------------------
#ifndef _SYSTEM_EEPROM_EMULATION_SUPPORT
#define _SYSTEM_EEPROM_EMULATION_SUPPORT                        _OFF
#endif

#ifndef _SYSTEM_EEPROM_EMULATION_FLASH_BANK
#define _SYSTEM_EEPROM_EMULATION_FLASH_BANK                     0
#endif

#ifndef _SYSTEM_EEPROM_EMULATION_START_PAGE
#define _SYSTEM_EEPROM_EMULATION_START_PAGE                     0
#endif

#ifndef _SYSTEM_EEPROM_EMULATION_END_PAGE
#define _SYSTEM_EEPROM_EMULATION_END_PAGE                       0
#endif

#ifndef _START_OF_PAGEID
#define _START_OF_PAGEID                                        _PAGEID_0
#endif

#ifndef _END_OF_PAGEID
#define _END_OF_PAGEID                                          _PAGEID_0
#endif

#ifndef _CHECKSUM_VERSIONCODE_ID
#define _CHECKSUM_VERSIONCODE_ID                                _PAGEID_0
#endif


//////////
// EDID //
//////////

//-------------------------------------------------
// EDID Location Option
//-------------------------------------------------
#ifndef _EDID_ADDRESS_EEPROM
#define _EDID_ADDRESS_EEPROM                                    (_EEPROM_PAGE0_BANK0)
#endif

#ifndef _EDID_ADDRESS_FLASH
#define _EDID_ADDRESS_FLASH                                     (0)
#endif

#ifndef _EDID_FLASH_BANK
#define _EDID_FLASH_BANK                                        (0)
#endif

//==================== START ======================
#ifndef _WRITE_EDID_TO_SYSTEM_EEPROM
#define _WRITE_EDID_TO_SYSTEM_EEPROM                            _OFF
#endif
//===================== END =======================


//////////////
// HDCP Key //
//////////////

//-------------------------------------------------
// HDCP Key Location Option
//-------------------------------------------------
#ifndef _HDCP_1_4_KEY_LOCATION
#define _HDCP_1_4_KEY_LOCATION                                  _TABLE_LOCATION_SYSTEM_EEPROM
#endif

#ifndef _RX_HDCP_1_4_KEY_ADDRESS_EEPROM
#define _RX_HDCP_1_4_KEY_ADDRESS_EEPROM                         (_EEPROM_PAGE0_BANK0)
#endif

#ifndef _RX_HDCP_1_4_KEY_ADDRESS_FLASH
#define _RX_HDCP_1_4_KEY_ADDRESS_FLASH                          (0)
#endif

#ifndef _RX_HDCP_1_4_KEY_FLASH_BANK
#define _RX_HDCP_1_4_KEY_FLASH_BANK                             (0)
#endif

//==================== START ======================
#ifndef _WRITE_HDCP_TO_SYSTEM_EEPROM
#define _WRITE_HDCP_TO_SYSTEM_EEPROM                            _OFF
#endif
//===================== END =======================


///////////////////
// System Source //
///////////////////

//-------------------------------------------------
// System Auto Search Style Option
//-------------------------------------------------
#ifndef _SOURCE_AUTO_SEARCH_STYLE
#define _SOURCE_AUTO_SEARCH_STYLE                               _SOURCE_POLLING_IN_SEARCH_STATE
#endif

//-------------------------------------------------
// System Source Search Time Option
//-------------------------------------------------
#ifndef _SOURCE_DEFAULT_SEARCH_TIME_VGA
#define _SOURCE_DEFAULT_SEARCH_TIME_VGA                         SEC(0.5)
#endif

#ifndef _SOURCE_DEFAULT_SEARCH_TIME_HDMI
#define _SOURCE_DEFAULT_SEARCH_TIME_HDMI                        SEC(2)
#endif

#ifndef _SOURCE_DEFAULT_SEARCH_TIME_DVI
#define _SOURCE_DEFAULT_SEARCH_TIME_DVI                         SEC(2)
#endif

#ifndef _SOURCE_DEFAULT_SEARCH_TIME_DP
#define _SOURCE_DEFAULT_SEARCH_TIME_DP                          SEC(3)
#endif

//==================== START ======================

//-------------------------------------------------
// System Default Search Time for all Port --> (_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_IN_SEARCH_STATE)
//-------------------------------------------------
#ifndef _SOURCE_DEFAULT_SEARCH_TIME_ALL_PORT
#define _SOURCE_DEFAULT_SEARCH_TIME_ALL_PORT                    SEC(2)
#endif

//-------------------------------------------------
// System Default Search Time When No Cable Option
//-------------------------------------------------
#ifndef _SOURCE_DEFAULT_SEARCH_TIME_VGA_NO_CABLE
#define _SOURCE_DEFAULT_SEARCH_TIME_VGA_NO_CABLE                SEC(0.5)
#endif

#ifndef _SOURCE_DEFAULT_SEARCH_TIME_HDMI_NO_CABLE
#define _SOURCE_DEFAULT_SEARCH_TIME_HDMI_NO_CABLE               SEC(2)
#endif

#ifndef _SOURCE_DEFAULT_SEARCH_TIME_DVI_NO_CABLE
#define _SOURCE_DEFAULT_SEARCH_TIME_DVI_NO_CABLE                SEC(2)
#endif

#ifndef _SOURCE_DEFAULT_SEARCH_TIME_DP_NO_CABLE
#define _SOURCE_DEFAULT_SEARCH_TIME_DP_NO_CABLE                 SEC(3)
#endif

//-------------------------------------------------
// System Required Time for External or Embedded DP Switch
//-------------------------------------------------
#ifndef _SOURCE_DP_SWITCH_TIMEOUT_TIME
#define _SOURCE_DP_SWITCH_TIMEOUT_TIME                          SEC(4)
#endif

//--------------------------------------------------
// Double Check NVRAM Port When Searching In Polling Mode Option
//--------------------------------------------------
#ifndef _SOURCE_DOUBLE_CHECK_NVRAM_PORT_SUPPORT
#define _SOURCE_DOUBLE_CHECK_NVRAM_PORT_SUPPORT                 _OFF
#endif

#ifndef _SOURCE_DOUBLE_CHECK_SEARCH_TIME_NVRAM_PORT
#define _SOURCE_DOUBLE_CHECK_SEARCH_TIME_NVRAM_PORT             SEC(0.5)
#endif

//===================== END =======================


//////////////////
// System Judge //
//////////////////

//-------------------------------------------------
// System Display Setting Check Time Option
//-------------------------------------------------
#ifndef _WAIT_TIME_TO_ACTIVE_VGA
#define _WAIT_TIME_TO_ACTIVE_VGA                                SEC(0.05)
#endif

#ifndef _WAIT_TIME_TO_ACTIVE_DVI
#define _WAIT_TIME_TO_ACTIVE_DVI                                SEC(0.1)
#endif

#ifndef _WAIT_TIME_TO_ACTIVE_HDMI
#define _WAIT_TIME_TO_ACTIVE_HDMI                               SEC(0.1)
#endif

#ifndef _WAIT_TIME_TO_ACTIVE_DP
#define _WAIT_TIME_TO_ACTIVE_DP                                 SEC(0.1)
#endif

//--------------------------------------------------
// System Support Timing Option
//--------------------------------------------------
#ifndef _OOR_H_FREQ_UPPER_BOUND
#define _OOR_H_FREQ_UPPER_BOUND                                 2200 // Unit in 0.1 kHZ
#endif

#ifndef _OOR_H_FREQ_LOWER_BOUND
#define _OOR_H_FREQ_LOWER_BOUND                                 100  // Unit in 0.1 kHZ
#endif

#ifndef _OOR_V_FREQ_UPPER_BOUND
#define _OOR_V_FREQ_UPPER_BOUND                                 1500 // Unit in 0.1 HZ
#endif

#ifndef _OOR_V_FREQ_LOWER_BOUND
#define _OOR_V_FREQ_LOWER_BOUND                                 230  // Unit in 0.1 HZ
#endif

#ifndef _OOR_H_WIDTH_UPPER_BOUND
#define _OOR_H_WIDTH_UPPER_BOUND                                4096 // Unit in pixel
#endif

#ifndef _OOR_V_HEIGHT_LOWER_BOUND
#define _OOR_V_HEIGHT_LOWER_BOUND                               240  // Unit in line
#endif

#ifndef _FAIL_SAVE_H_FREQ_UPPER_BOUND
#define _FAIL_SAVE_H_FREQ_UPPER_BOUND                           2200 // Unit in 0.1 kHZ
#endif

#ifndef _FAIL_SAVE_H_FREQ_LOWER_BOUND
#define _FAIL_SAVE_H_FREQ_LOWER_BOUND                           110  // Unit in 0.1 kHZ
#endif

#ifndef _FAIL_SAVE_V_FREQ_UPPER_BOUND
#define _FAIL_SAVE_V_FREQ_UPPER_BOUND                           1500 // Unit in 0.1 HZ
#endif

#ifndef _FAIL_SAVE_V_FREQ_LOWER_BOUND
#define _FAIL_SAVE_V_FREQ_LOWER_BOUND                           230  // Unit in 0.1 HZ
#endif

#ifndef _INPUTCLOCK_RANG_VGA
#define _INPUTCLOCK_RANG_VGA                                    2100 // Unit in 0.1 MHz
#endif

#ifndef _INPUTCLOCK_RANG_DVI
#define _INPUTCLOCK_RANG_DVI                                    2250 // Unit in 0.1 MHz
#endif

#ifndef _INPUTCLOCK_RANG_HDMI
#define _INPUTCLOCK_RANG_HDMI                                   2250 // Unit in 0.1 MHz
#endif

#ifndef _INPUTCLOCK_RANG_DP
#define _INPUTCLOCK_RANG_DP                                     2250 // Unit in 0.1 MHz
#endif

#ifndef _INPUTCLOCK_RANG_USBC
#define _INPUTCLOCK_RANG_USBC                                   2250 // Unit in 0.1 MHz
#endif


//////////////////
// System Power //
//////////////////
//==================== START ======================

//--------------------------------------------------
// Power Fake Off to Off Timeout
//--------------------------------------------------
#ifndef _POWER_FAKE_OFF_TO_OFF_TIMEOUT
#define _POWER_FAKE_OFF_TO_OFF_TIMEOUT                          SEC(8)
#endif

//===================== END =======================


/////////
// VGA //
/////////

//--------------------------------------------------
// VGA YPBPR Option
//--------------------------------------------------
#ifndef _YPBPR_SUPPORT
#define _YPBPR_SUPPORT                                          _ON
#endif

#ifndef _SOG_SUPPORT
#define _SOG_SUPPORT                                            _ON
#endif

#ifndef _VGA_COMPOSITE_SUPPORT
#define _VGA_COMPOSITE_SUPPORT                                  _ON
#endif

//--------------------------------------------------
// VGA Mode Search condition reference by picture width Option
//--------------------------------------------------
#ifndef _MODE_SEARCH_BY_ACTIVE_MEASURE_SUPPORT
#define _MODE_SEARCH_BY_ACTIVE_MEASURE_SUPPORT                  _OFF
#endif

//--------------------------------------------------
// VGA Auto Adjust Clock Setup Option
//--------------------------------------------------
#ifndef _AUTO_CLOCK_STEP
#define _AUTO_CLOCK_STEP                                        2  // 1 or 2
#endif

#ifndef _AUTO_CLOCK_RANGE
#define _AUTO_CLOCK_RANGE                                       95 // Set Clock Non-adjusting Range (%) by the active region
#endif

#ifndef _AUTO_TOLERANCE_PIXEL
#define _AUTO_TOLERANCE_PIXEL                                   2  // Definitions Of tolerance pixel for Auto Clock
#endif

#ifndef _AUTO_CLOCK_SAVE_VALUE_OPTION
#define _AUTO_CLOCK_SAVE_VALUE_OPTION                           _CLOCK_SAVE_PERCENT_VALUE
#endif

//--------------------------------------------------
// VGA Gain & Offset Defualt Option
//--------------------------------------------------
#ifndef _ADC_RGB_DEFAULT_RED_GAIN
#define _ADC_RGB_DEFAULT_RED_GAIN                               128
#endif

#ifndef _ADC_RGB_DEFAULT_GREEN_GAIN
#define _ADC_RGB_DEFAULT_GREEN_GAIN                             128
#endif

#ifndef _ADC_RGB_DEFAULT_BLUE_GAIN
#define _ADC_RGB_DEFAULT_BLUE_GAIN                              128
#endif

#ifndef _ADC_RGB_DEFAULT_RED_OFFSET
#define _ADC_RGB_DEFAULT_RED_OFFSET                             128
#endif

#ifndef _ADC_RGB_DEFAULT_GREEN_OFFSET
#define _ADC_RGB_DEFAULT_GREEN_OFFSET                           128
#endif

#ifndef _ADC_RGB_DEFAULT_BLUE_OFFSET
#define _ADC_RGB_DEFAULT_BLUE_OFFSET                            128
#endif

#ifndef _ADC_YPBPR_DEFAULT_Y_GAIN
#define _ADC_YPBPR_DEFAULT_Y_GAIN                               159
#endif

#ifndef _ADC_YPBPR_DEFAULT_PB_GAIN
#define _ADC_YPBPR_DEFAULT_PB_GAIN                              154
#endif

#ifndef _ADC_YPBPR_DEFAULT_PR_GAIN
#define _ADC_YPBPR_DEFAULT_PR_GAIN                              154
#endif

#ifndef _ADC_YPBPR_DEFAULT_Y_OFFSET
#define _ADC_YPBPR_DEFAULT_Y_OFFSET                             112
#endif

#ifndef _ADC_YPBPR_DEFAULT_PB_OFFSET
#define _ADC_YPBPR_DEFAULT_PB_OFFSET                            128
#endif

#ifndef _ADC_YPBPR_DEFAULT_PR_OFFSET
#define _ADC_YPBPR_DEFAULT_PR_OFFSET                            128
#endif

//==================== START ======================
#ifndef _ADC_RGB_DEFAULT_PGA_VALUE
#define _ADC_RGB_DEFAULT_PGA_VALUE                              8 // 0 ~ 15
#endif

#ifndef _ADC_YPBPR_DEFAULT_PGA_VALUE
#define _ADC_YPBPR_DEFAULT_PGA_VALUE                            8 // 0 ~ 15
#endif
//===================== END =======================

//--------------------------------------------------
// VGA Self-Calibration Option
//--------------------------------------------------
#ifndef _ADC_SELF_CALIBRATION
#define _ADC_SELF_CALIBRATION                                   _OFF
#endif

#ifndef _CALIBRATION_R_GAIN_BIAS
#define _CALIBRATION_R_GAIN_BIAS                                (0)  // Needs modification for EVERY single source
#endif

#ifndef _CALIBRATION_G_GAIN_BIAS
#define _CALIBRATION_G_GAIN_BIAS                                (0)  // Needs modification for EVERY single source
#endif

#ifndef _CALIBRATION_B_GAIN_BIAS
#define _CALIBRATION_B_GAIN_BIAS                                (0)  // Needs modification for EVERY single source
#endif

#ifndef _CALIBRATION_R_OFFSET_BIAS
#define _CALIBRATION_R_OFFSET_BIAS                              (-3) // Needs modification for EVERY single source
#endif

#ifndef _CALIBRATION_G_OFFSET_BIAS
#define _CALIBRATION_G_OFFSET_BIAS                              (-3) // Needs modification for EVERY single source
#endif

#ifndef _CALIBRATION_B_OFFSET_BIAS
#define _CALIBRATION_B_OFFSET_BIAS                              (-3) // Needs modification for EVERY single source
#endif

//==================== START ======================
#ifndef _SELF_CALIBRATION_CLK
#define _SELF_CALIBRATION_CLK                                   (148) // MHz
#endif
//===================== END =======================

//--------------------------------------------------
// VGA YPBPR Auto Color Method Option
//--------------------------------------------------
#ifndef _YPBPR_AUTO_METHOD
#define _YPBPR_AUTO_METHOD                                      _YPBPR_AUTO_BY_SOURCE
#endif

#ifndef _AUTO_PB_GAIN_BIAS
#define _AUTO_PB_GAIN_BIAS                                      (5)
#endif

#ifndef _AUTO_PR_GAIN_BIAS
#define _AUTO_PR_GAIN_BIAS                                      (5)
#endif

#ifndef _AUTO_Y_GAIN_BIAS
#define _AUTO_Y_GAIN_BIAS                                       (0)
#endif

#ifndef _AUTO_PB_OFFSET_BIAS
#define _AUTO_PB_OFFSET_BIAS                                    (-8)
#endif

#ifndef _AUTO_PR_OFFSET_BIAS
#define _AUTO_PR_OFFSET_BIAS                                    (-8)
#endif

#ifndef _AUTO_Y_OFFSET_BIAS
#define _AUTO_Y_OFFSET_BIAS                                     (-16)
#endif

//--------------------------------------------------
// VGA Digital Filter Option
//--------------------------------------------------
#ifndef _DIG_FILTER_NSMEAR_ENABLE
#define _DIG_FILTER_NSMEAR_ENABLE                               _ENABLE
#endif

#ifndef _DIG_FILTER_PSMEAR_ENABLE
#define _DIG_FILTER_PSMEAR_ENABLE                               _ENABLE
#endif

#ifndef _DIG_FILTER_NRING_ENABLE
#define _DIG_FILTER_NRING_ENABLE                                _ENABLE
#endif

#ifndef _DIG_FILTER_PRING_ENABLE
#define _DIG_FILTER_PRING_ENABLE                                _ENABLE
#endif

#ifndef _DIG_FILTER_EXTENSION_ENABLE
#define _DIG_FILTER_EXTENSION_ENABLE                            _ENABLE
#endif

#ifndef _DIG_FILTER_ENHANCE_PHASE_ENABLE
#define _DIG_FILTER_ENHANCE_PHASE_ENABLE                        _ENABLE
#endif

//==================== START ======================

//--------------------------------------------------
// VGA Digital Phase Filter Option
//--------------------------------------------------
#ifndef _DIG_FILTER_PHASE_ENABLE
#define _DIG_FILTER_PHASE_ENABLE                                _ENABLE
#endif

#ifndef _DIG_FILTER_PHASE_THD
#define _DIG_FILTER_PHASE_THD                                   192 // effective:0~255
#endif

#ifndef _DIG_FILTER_PHASE_DIV_VALUE
#define _DIG_FILTER_PHASE_DIV_VALUE                             0   // effective:0~3
#endif

#ifndef _DIG_FILTER_PHASE_HIGHFREQ_ADCCLOCKTHD
#define _DIG_FILTER_PHASE_HIGHFREQ_ADCCLOCKTHD                  0   // effective:0~210 (MHz)
#endif

#ifndef _DIG_FILTER_PHASE_HIGHFREQ_THD
#define _DIG_FILTER_PHASE_HIGHFREQ_THD                          160 // effective:0~255
#endif

#ifndef _DIG_FILTER_PHASE_HIGHFREQ_DIV_VALUE
#define _DIG_FILTER_PHASE_HIGHFREQ_DIV_VALUE                    0   // effective:0~3
#endif

//--------------------------------------------------
// VGA Chroma Pattern 12 Option
//--------------------------------------------------
#ifndef _VGA_CHROMA_PATTERN12_SUPPORT
#define _VGA_CHROMA_PATTERN12_SUPPORT                           _OFF
#endif

//--------------------------------------------------
// VGA 25MHz Noise Reduce by SF/SHA LPF Option
//--------------------------------------------------
#ifndef _VGA_ADC_SF_SHA_LPF_UNDER_25MHZ_SUPPORT
#define _VGA_ADC_SF_SHA_LPF_UNDER_25MHZ_SUPPORT                 _OFF
#endif

//===================== END =======================

//==================== START ======================
#ifndef _FREESYNC_GET_IVTOTAL_BY_SPD
#define _FREESYNC_GET_IVTOTAL_BY_SPD                            _OFF
#endif
//===================== END =======================


////////////////
// DVI & HDMI //
////////////////

//--------------------------------------------------
// DVI & HDMI Option
//--------------------------------------------------
#ifndef _DVI_DE_ONLY_SUPPORT
#define _DVI_DE_ONLY_SUPPORT                                    _OFF
#endif

#ifndef _HDMI_FROM_DVI_CONNECT
#define _HDMI_FROM_DVI_CONNECT                                  _OFF
#endif

#ifndef _HDMI_FREESYNC_SUPPORT
#define _HDMI_FREESYNC_SUPPORT                                  _OFF
#endif

//==================== START ======================
#ifndef _HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD
#define _HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD                 _MCCS_SWITCH_MODE
#endif

//--------------------------------------------------
// TMDS Z0's HPD DDC Check Optional
//--------------------------------------------------
#ifndef _TMDS_DDC_CHECK_BUSY_BEFORE_HPD
#define _TMDS_DDC_CHECK_BUSY_BEFORE_HPD                         _OFF
#endif

#ifndef _HDMI_FREESYNC_MCCS_VCP
#define _HDMI_FREESYNC_MCCS_VCP                                 0xE6
#endif
//===================== END =======================

//--------------------------------------------------
// HDMI CTS Option
//--------------------------------------------------
#ifndef _TMDS_HDCP_FEATURE
#define _TMDS_HDCP_FEATURE                                      _HDCP_FEATURE_BY_INPUT
#endif

#ifndef _TMDS_Z0_POWER_SAVING_OPTION
#define _TMDS_Z0_POWER_SAVING_OPTION                            _ALL_CHANNEL_CONNECTED_FOR_CTS
#endif

//==================== START ======================
#ifndef _D0_TMDS_Z0_IMPEDANCE_OPTION
#define _D0_TMDS_Z0_IMPEDANCE_OPTION                            _NORMAL_100_OHM
#endif

#ifndef _D1_TMDS_Z0_IMPEDANCE_OPTION
#define _D1_TMDS_Z0_IMPEDANCE_OPTION                            _NORMAL_100_OHM
#endif
//===================== END =======================


////////
// DP //
////////

//-------------------------------------------------
// DP Capability Option
//-------------------------------------------------
#ifndef _DP_FREESYNC_SUPPORT
#define _DP_FREESYNC_SUPPORT                                    _OFF
#endif

//==================== START ======================

//--------------------------------------------------
// DP HBR & RBR Link Training Force Marginal Link(N+1)
//--------------------------------------------------
#ifndef _DP_HBR_RBR_LT_FORCE_MARGINAL_LINK
#define _DP_HBR_RBR_LT_FORCE_MARGINAL_LINK                      _ON
#endif

//--------------------------------------------------
//  GDI Passive DFE Fine Tune Flow
//--------------------------------------------------
#if(_HW_DP_GDI_RX0_DFE_TYPE == _PASSIVE_DFE)
#ifndef _DP_RX0_PASSIVE_DFE_FINE_TUNE_TYPE
#define _DP_RX0_PASSIVE_DFE_FINE_TUNE_TYPE                      _FINE_TUNE_DFE_BY_1_LANE
#endif
#endif

#if(_HW_DP_GDI_RX1_DFE_TYPE == _PASSIVE_DFE)
#ifndef _DP_RX1_PASSIVE_DFE_FINE_TUNE_TYPE
#define _DP_RX1_PASSIVE_DFE_FINE_TUNE_TYPE                      _FINE_TUNE_DFE_BY_1_LANE
#endif
#endif

//--------------------------------------------------
// DP ASSR Option
//--------------------------------------------------
#ifndef _DP_ASSR_MODE_SUPPORT
#define _DP_ASSR_MODE_SUPPORT                                   _OFF
#endif

//--------------------------------------------------
// DP Aux Reply Timeout by User Option
//--------------------------------------------------
#ifndef _DP_AUX_REPLY_TIMEOUT_BY_USER
#define _DP_AUX_REPLY_TIMEOUT_BY_USER                           _OFF
#endif

#ifndef _DP_AUX_REPLY_TIMEOUT_USER_SETTING
#define _DP_AUX_REPLY_TIMEOUT_USER_SETTING                      0x0D
#endif

//--------------------------------------------------
// DP Power OFF HDCP Support
//--------------------------------------------------
#ifndef _DP_POWER_OFF_HDCP_SUPPORT
#define _DP_POWER_OFF_HDCP_SUPPORT                              _OFF
#endif

//--------------------------------------------------
// DP pull-up Long HPD or not (after CPIRQ) by User Option
//--------------------------------------------------
#ifndef _DP_LONG_HPD_AFTER_CPIRQ_SUPPORT
#define _DP_LONG_HPD_AFTER_CPIRQ_SUPPORT                        _ON
#endif

//===================== END =======================


///////////
// Audio //
///////////

//-------------------------------------------------
// Audio Option
//-------------------------------------------------
#ifndef _AUDIO_SUPPORT
#define _AUDIO_SUPPORT                                          _OFF
#endif

//-------------------------------------------------
// Audio DAC Option
//-------------------------------------------------
#ifndef _EMBEDDED_DAC_SUPPORT
#define _EMBEDDED_DAC_SUPPORT                                   _OFF
#endif

//==================== START ======================
#ifndef _DAC_SPEAKER_OUTPUT_SUPPORT
#define _DAC_SPEAKER_OUTPUT_SUPPORT                             _ON // Should be _OFF if the related pinout is used as GPIO funtion
#endif

#ifndef _DAC_HP_OUTPUT_SUPPORT
#define _DAC_HP_OUTPUT_SUPPORT                                  _ON // Should be _OFF if the related pinout is used as GPIO funtion
#endif

#ifndef _DAC_SPEAKER_OUTPUT_SWAP
#define _DAC_SPEAKER_OUTPUT_SWAP                                _OFF
#endif

#ifndef _DAC_HP_OUTPUT_SWAP
#define _DAC_HP_OUTPUT_SWAP                                     _OFF
#endif

#ifndef _DAC_DEPOP_TO_NORMAL_WAIT_TIME
#define _DAC_DEPOP_TO_NORMAL_WAIT_TIME                          SEC(0.1)
#endif

#ifndef _DAC_DITHER_FUNCTION_LEVEL
#define _DAC_DITHER_FUNCTION_LEVEL                              _AUDIO_DAC_DITHER_LEVEL_OFF
#endif
//===================== END =======================

//-------------------------------------------------
// Audio Line In Option
//-------------------------------------------------
#ifndef _LINE_IN_SUPPORT
#define _LINE_IN_SUPPORT                                        _OFF
#endif

#ifndef _LINE_IN_DAC_AOUT_GAIN_DB
#define _LINE_IN_DAC_AOUT_GAIN_DB                               _AUDIO_DAC_OUTPUT_GAIN_0_DB // 0dB, 1.5dB for each step, Max Gain: 'b111(10.5dB)
#endif

#ifndef _LINE_IN_DAC_HPOUT_GAIN_DB
#define _LINE_IN_DAC_HPOUT_GAIN_DB                              _AUDIO_DAC_OUTPUT_GAIN_0_DB // 0dB, 1.5dB for each step, Max Gain: 'b111(10.5dB)
#endif

#ifndef _LINE_IN_BOOST_GAIN_DB
#define _LINE_IN_BOOST_GAIN_DB                                  0x17                        // 0dB, 1.5dB for each step, Max Gain: 0x3F(30dB)
#endif

#ifndef _LINE_IN_VOLUME_MAX
#define _LINE_IN_VOLUME_MAX                                     0x3FFF                      // MAX: 0x3FFF
#endif

#ifndef _LINE_IN_VOLUME_MIN
#define _LINE_IN_VOLUME_MIN                                     0x0000
#endif

//==================== START ======================

//--------------------------------------------------
// Audio Line In AA DAC Bypass Option
//--------------------------------------------------
#ifndef _LINE_IN_AA_PATH_SUPPORT
#define _LINE_IN_AA_PATH_SUPPORT                                _OFF
#endif

//===================== END =======================

//-------------------------------------------------
// Audio Digital Option
//-------------------------------------------------
#ifndef _DIGITAL_DAC_AOUT_GAIN_DB
#define _DIGITAL_DAC_AOUT_GAIN_DB                               _AUDIO_DAC_OUTPUT_GAIN_0_DB // 0dB, 1.5dB for each step, Max Gain: 'b111(10.5dB)
#endif

#ifndef _DIGITAL_DAC_HPOUT_GAIN_DB
#define _DIGITAL_DAC_HPOUT_GAIN_DB                              _AUDIO_DAC_OUTPUT_GAIN_0_DB // 0dB, 1.5dB for each step, Max Gain: 'b111(10.5dB)
#endif

#ifndef _DIGITAL_VOLUME_MAX
#define _DIGITAL_VOLUME_MAX                                     0x3FFF                      // MAX: 0x3FFF
#endif

#ifndef _DIGITAL_VOLUME_MIN
#define _DIGITAL_VOLUME_MIN                                     0x0000
#endif

//-------------------------------------------------
// Audio PS Option
//-------------------------------------------------
#ifndef _SLEEP_AUDIO_SUPPORT
#define _SLEEP_AUDIO_SUPPORT                                    _OFF
#endif

#ifndef _PS_AUDIO_INPUT
#define _PS_AUDIO_INPUT                                         _PS_AUDIO_LINE_IN
#endif

//==================== START ======================

//--------------------------------------------------
// Digital Volume Control Option --> For Audio Mute
//--------------------------------------------------
#ifndef _DVC_ADJUST_TYPE
#define _DVC_ADJUST_TYPE                                        _DB_GAIN
#endif

#ifndef _DB_GAIN_DOWN_VALUE
#define _DB_GAIN_DOWN_VALUE                                     _DB_GAIN_1_8_DB   // For _DB_GAIN
#endif

#ifndef _DB_GAIN_UP_VALUE
#define _DB_GAIN_UP_VALUE                                       _DB_GAIN_1_8_DB   // For _DB_GAIN
#endif

#ifndef _VOLUME_STEP_SIZE_VALUE
#define _VOLUME_STEP_SIZE_VALUE                                 (0x0040 & 0x3FFF) // For _VOLUME_STEP_SIZE
#endif

#ifndef _DVC_VOLUME_MUTE_TIMER
#define _DVC_VOLUME_MUTE_TIMER                                  400 // ms
#endif

//--------------------------------------------------
// Audio Manual Sampling Frequency Option
//--------------------------------------------------
#ifndef _AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT
#define _AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT                     _OFF
#endif

#ifndef _FIX_SAMPLING_FREQ_TYPE
#define _FIX_SAMPLING_FREQ_TYPE                                 _FIX_FREQ_48KHZ
#endif

//--------------------------------------------------
// Switch Audio Source to Line In When Entering Power Saving Mode Option
//--------------------------------------------------
#ifndef _SWITCH_TO_LINE_IN_AUDIO_IN_POWER_SAVING_MODE
#define _SWITCH_TO_LINE_IN_AUDIO_IN_POWER_SAVING_MODE           _OFF
#endif

//--------------------------------------------------
// Don't Mute Line in Audio While Switching DP/HDMI Port
//--------------------------------------------------
#ifndef _NO_MUTE_LINE_IN_AUDIO_WHILE_SWITCHING_DIGITAL_PORT
#define _NO_MUTE_LINE_IN_AUDIO_WHILE_SWITCHING_DIGITAL_PORT     _OFF
#endif

//-------------------------------------------------
// Audio Hard Gain Option
//-------------------------------------------------
#ifndef _AUDIO_DVC_ADJUST_HARD_GAIN_SUPPORT
#define _AUDIO_DVC_ADJUST_HARD_GAIN_SUPPORT                     _OFF
#endif

#ifndef _LINE_IN_HARD_GAIN_VALUE
#define _LINE_IN_HARD_GAIN_VALUE                                _HARD_GAIN_0_DB
#endif

#ifndef _DIGITAL_HARD_GAIN_VALUE
#define _DIGITAL_HARD_GAIN_VALUE                                _HARD_GAIN_0_DB
#endif

//-------------------------------------------------
// Audio Digital Output(I2S/SPDIF) Adjust Volume Option
//-------------------------------------------------
#ifndef _DIGITAL_AUDIO_OUTPUT_ADJUST_VOLUME_SUPPORT
#define _DIGITAL_AUDIO_OUTPUT_ADJUST_VOLUME_SUPPORT             _OFF
#endif

//===================== END =======================


///////////////////
// Misc Function //
///////////////////

//-------------------------------------------------
// Instant Timer Events Option
//-------------------------------------------------
#ifndef _INSTANT_TIMER_EVENT_0
#define _INSTANT_TIMER_EVENT_0                                  _OFF
#endif

#ifndef _INSTANT_TIMER_EVENT_1
#define _INSTANT_TIMER_EVENT_1                                  _OFF
#endif

//==================== START ======================

//--------------------------------------------------
// Code Digital Signature Support Option
//--------------------------------------------------
#ifndef _CODE_DIGITAL_SIGNATURE_SUPPORT
#define _CODE_DIGITAL_SIGNATURE_SUPPORT                         _SIGNATURE_TYPE_OFF
#endif

//--------------------------------------------------
// Code Digital Signature Vendor Type
//--------------------------------------------------
#ifndef _CODE_DIGITAL_SIGNATURE_VENDOR_TYPE
#define _CODE_DIGITAL_SIGNATURE_VENDOR_TYPE                     _SIGNATURE_VENDOR_NONE
#endif

//--------------------------------------------------
// UART Option
//--------------------------------------------------
#ifndef _UART_SUPPORT
#define _UART_SUPPORT                                           _OFF
#endif

#ifndef _UART_BAUD_RATE_POWER_NORMAL
#define _UART_BAUD_RATE_POWER_NORMAL                            9600 // 9600/19200/14400/28800/38400/56000 Baud (Unit in Baud)
#endif

#ifndef _UART_BAUD_RATE_POWER_SAVING
#define _UART_BAUD_RATE_POWER_SAVING                            9600 // 9600/19200/14400/28800/38400/56000 Baud (Unit in Baud)
#endif

//-------------------------------------------------
// System Timer 250us Option --> SW IR Application
//-------------------------------------------------
#ifndef _SYSTEM_TIMER_QUARTER_RESOLUTION
#define _SYSTEM_TIMER_QUARTER_RESOLUTION                        _OFF
#endif

//--------------------------------------------------
//  Factory Debug Option --> Extern ScalerSetByte, ScalerGetByte, ScalerSetBit, ScalerGetBit to User
//--------------------------------------------------
#ifndef _FACTORY_DEBUG_SUPPORT
#define _FACTORY_DEBUG_SUPPORT                                  _OFF
#endif

//--------------------------------------------------
// Display Garbage Prevent Method Option
//--------------------------------------------------
#ifndef _DISPLAY_PREVENT_GARBAGE_METHOD
#define _DISPLAY_PREVENT_GARBAGE_METHOD                         _GARBAGE_PREVENT_BY_WATCH_DOG
#endif

//-------------------------------------------------
// Panel Power Sequence Control by User Option
//-------------------------------------------------
#ifndef _PANEL_POWER_SEQUENCE_CONTROL_BY_USER
#define _PANEL_POWER_SEQUENCE_CONTROL_BY_USER                   _OFF
#endif

//-------------------------------------------------
// Color Process Control by User Option
//-------------------------------------------------
#ifndef _COLOR_PROCESS_CONTROL_BY_USER
#define _COLOR_PROCESS_CONTROL_BY_USER                          _OFF
#endif

//-------------------------------------------------
// Flash Enable Write protect Option
//-------------------------------------------------
#ifndef _FLASH_WR_PROTECT
#define _FLASH_WR_PROTECT                                       _OFF
#endif


/////////
// AIO //
/////////

//-------------------------------------------------
// AIO Modern Standby Support Option
//-------------------------------------------------
#ifndef _AIO_MODERN_STANDBY_SUPPORT
#define _AIO_MODERN_STANDBY_SUPPORT                             _OFF
#endif


//////////
// Acer //
//////////

//-------------------------------------------------
// Acer TMDS Toggle HPD & Z0 Option
//-------------------------------------------------
#ifndef _TMDS_TOGGLE_HPD_Z0_FOR_ACER
#define _TMDS_TOGGLE_HPD_Z0_FOR_ACER                            _OFF
#endif


//////////
// Asus //
//////////

//-------------------------------------------------
// Asus Auto Search Time Option --> (_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_ASUS_STYLE)
//-------------------------------------------------
#ifndef _SOURCE_ASUS_START_AUTO_TIME
#define _SOURCE_ASUS_START_AUTO_TIME                            SEC(2)
#endif


//////////
// DELL //
//////////

//--------------------------------------------------
// DELL DP D3 Options --> for DELL
//--------------------------------------------------
#ifndef _DP_DELL_D3_TEST_SUPPORT
#define _DP_DELL_D3_TEST_SUPPORT                                _OFF
#endif

//--------------------------------------------------
// DELL DP Dynamic Adjust Link Rate --> for DELL
//--------------------------------------------------
#ifndef _DP_DYNAMIC_ADJUST_LINK_RATE_SUPPORT
#define _DP_DYNAMIC_ADJUST_LINK_RATE_SUPPORT                    _OFF
#endif


/////////////
// PHILIPS //
/////////////

//--------------------------------------------------
// PHILIPS Pixel-shift Support Option
//--------------------------------------------------
#ifndef _PIXEL_SHIFT_SUPPORT
#define _PIXEL_SHIFT_SUPPORT                                    _OFF
#endif


////////
// HP //
////////

//--------------------------------------------------
// HP Source Scan Define Option
//--------------------------------------------------
#ifndef _HP_SOURCE_SCAN_SUPPORT
#define _HP_SOURCE_SCAN_SUPPORT                                 _OFF
#endif

#ifndef _HP_SOURCE_SCAN_TYPE
#define _HP_SOURCE_SCAN_TYPE                                    _HP_SOURCE_SCAN_TYPE_F
#endif


//////////
// Eizo //
//////////

//--------------------------------------------------
// Eizo System Eeprom Customization Option
//--------------------------------------------------
#ifndef _USER_SYSTEM_EEPROM_CUSTOMIZATION
#define _USER_SYSTEM_EEPROM_CUSTOMIZATION                       _OFF
#endif

//--------------------------------------------------
// Eizo DP Sink Support OUI Under Ver1.1 Option
//--------------------------------------------------
#ifndef _DP_SINK_VER11_OUI_SUPPORT
#define _DP_SINK_VER11_OUI_SUPPORT                              _ON
#endif

//--------------------------------------------------
// Eizo DP DPCD Down Stream Port Count
//--------------------------------------------------
#ifndef _DP_1_1_DOWN_STREAM_PORT_COUNT
#define _DP_1_1_DOWN_STREAM_PORT_COUNT                          0x00
#endif

#ifndef _DP_1_2_DOWN_STREAM_PORT_COUNT
#define _DP_1_2_DOWN_STREAM_PORT_COUNT                          0x00
#endif

//--------------------------------------------------
// Eizo DP Ver1.1 DPCD Table Value of Sink IEEE OUI Option
//--------------------------------------------------
#ifndef _DP_1_1_SINK_RTK_IEEE_OUI_L
#define _DP_1_1_SINK_RTK_IEEE_OUI_L                             0x00
#endif

#ifndef _DP_1_1_SINK_RTK_IEEE_OUI_M
#define _DP_1_1_SINK_RTK_IEEE_OUI_M                             0xE0
#endif

#ifndef _DP_1_1_SINK_RTK_IEEE_OUI_H
#define _DP_1_1_SINK_RTK_IEEE_OUI_H                             0x4C
#endif

#ifndef _DP_1_1_SINK_RTK_ID_STRING_0
#define _DP_1_1_SINK_RTK_ID_STRING_0                            0x00
#endif

#ifndef _DP_1_1_SINK_RTK_ID_STRING_1
#define _DP_1_1_SINK_RTK_ID_STRING_1                            0x00
#endif

#ifndef _DP_1_1_SINK_RTK_ID_STRING_2
#define _DP_1_1_SINK_RTK_ID_STRING_2                            0x00
#endif

#ifndef _DP_1_1_SINK_RTK_ID_STRING_3
#define _DP_1_1_SINK_RTK_ID_STRING_3                            0x00
#endif

#ifndef _DP_1_1_SINK_RTK_ID_STRING_4
#define _DP_1_1_SINK_RTK_ID_STRING_4                            0x00
#endif

#ifndef _DP_1_1_SINK_RTK_ID_STRING_5
#define _DP_1_1_SINK_RTK_ID_STRING_5                            0x00
#endif

//--------------------------------------------------
// Eizo DP Ver1.1 DPCD Table Value Of Sink HW/FW Version Option
//--------------------------------------------------
#ifndef _DP_1_1_SINK_RTK_HW_VERSION
#define _DP_1_1_SINK_RTK_HW_VERSION                             0x00
#endif

#ifndef _DP_1_1_SINK_RTK_FW_VERSION_H
#define _DP_1_1_SINK_RTK_FW_VERSION_H                           0x00
#endif

#ifndef _DP_1_1_SINK_RTK_FW_VERSION_L
#define _DP_1_1_SINK_RTK_FW_VERSION_L                           0x00
#endif

//--------------------------------------------------
// Eizo DP Ver1.2 DPCD Table Value of Sink IEEE OUI Option
//--------------------------------------------------
#ifndef _DP_1_2_SINK_RTK_IEEE_OUI_L
#define _DP_1_2_SINK_RTK_IEEE_OUI_L                             0x00
#endif

#ifndef _DP_1_2_SINK_RTK_IEEE_OUI_M
#define _DP_1_2_SINK_RTK_IEEE_OUI_M                             0xE0
#endif

#ifndef _DP_1_2_SINK_RTK_IEEE_OUI_H
#define _DP_1_2_SINK_RTK_IEEE_OUI_H                             0x4C
#endif

#ifndef _DP_1_2_SINK_RTK_ID_STRING_0
#define _DP_1_2_SINK_RTK_ID_STRING_0                            0x44
#endif

#ifndef _DP_1_2_SINK_RTK_ID_STRING_1
#define _DP_1_2_SINK_RTK_ID_STRING_1                            0x70
#endif

#ifndef _DP_1_2_SINK_RTK_ID_STRING_2
#define _DP_1_2_SINK_RTK_ID_STRING_2                            0x31
#endif

#ifndef _DP_1_2_SINK_RTK_ID_STRING_3
#define _DP_1_2_SINK_RTK_ID_STRING_3                            0x2E
#endif

#ifndef _DP_1_2_SINK_RTK_ID_STRING_4
#define _DP_1_2_SINK_RTK_ID_STRING_4                            0x32
#endif

#ifndef _DP_1_2_SINK_RTK_ID_STRING_5
#define _DP_1_2_SINK_RTK_ID_STRING_5                            0x00
#endif

//--------------------------------------------------
// Eizo DP Ver1.2 DPCD Table Value Of Sink HW/FW Version Option
//--------------------------------------------------
#ifndef _DP_1_2_SINK_RTK_HW_VERSION
#define _DP_1_2_SINK_RTK_HW_VERSION                             0x00
#endif

#ifndef _DP_1_2_SINK_RTK_FW_VERSION_H
#define _DP_1_2_SINK_RTK_FW_VERSION_H                           0x00
#endif

#ifndef _DP_1_2_SINK_RTK_FW_VERSION_L
#define _DP_1_2_SINK_RTK_FW_VERSION_L                           0x00
#endif

//--------------------------------------------------
// Eizo DP DPCD Table Value Of Branch IEEE OUI Option
//--------------------------------------------------
#ifndef _DP_BRANCH_RTK_IEEE_OUI_L
#define _DP_BRANCH_RTK_IEEE_OUI_L                               0x00
#endif

#ifndef _DP_BRANCH_RTK_IEEE_OUI_M
#define _DP_BRANCH_RTK_IEEE_OUI_M                               0xE0
#endif

#ifndef _DP_BRANCH_RTK_IEEE_OUI_H
#define _DP_BRANCH_RTK_IEEE_OUI_H                               0x4C
#endif

#ifndef _DP_BRANCH_RTK_ID_STRING_0
#define _DP_BRANCH_RTK_ID_STRING_0                              0x44
#endif

#ifndef _DP_BRANCH_RTK_ID_STRING_1
#define _DP_BRANCH_RTK_ID_STRING_1                              0x70
#endif

#ifndef _DP_BRANCH_RTK_ID_STRING_2
#define _DP_BRANCH_RTK_ID_STRING_2                              0x31
#endif

#ifndef _DP_BRANCH_RTK_ID_STRING_3
#define _DP_BRANCH_RTK_ID_STRING_3                              0x2E
#endif

#ifndef _DP_BRANCH_RTK_ID_STRING_4
#define _DP_BRANCH_RTK_ID_STRING_4                              0x32
#endif

#ifndef _DP_BRANCH_RTK_ID_STRING_5
#define _DP_BRANCH_RTK_ID_STRING_5                              0x00
#endif

//--------------------------------------------------
// Eizo DP DPCD Table Value Of Branch HW/FW Version Option
//--------------------------------------------------
#ifndef _DP_BRANCH_RTK_HW_VERSION
#define _DP_BRANCH_RTK_HW_VERSION                               0x00
#endif

#ifndef _DP_BRANCH_RTK_FW_VERSION_H
#define _DP_BRANCH_RTK_FW_VERSION_H                             0x00
#endif

#ifndef _DP_BRANCH_RTK_FW_VERSION_L
#define _DP_BRANCH_RTK_FW_VERSION_L                             0x00
#endif

//-------------------------------------------------
// Eizo DDCCI Code Reduction Option
//-------------------------------------------------
#ifndef _DDCCI_CODE_REDUCTION
#define _DDCCI_CODE_REDUCTION                                   _OFF
#endif

//-------------------------------------------------
// Eizo Required Time to Search Finish Option
//-------------------------------------------------
#ifndef _SOURCE_EIZO_SEARCH_FINISH_TIME
#define _SOURCE_EIZO_SEARCH_FINISH_TIME                         SEC(10)
#endif

//--------------------------------------------------
// Eizo VGA Force Display Option
//--------------------------------------------------
#ifndef _VGA_FORCE_DISPLAY
#define _VGA_FORCE_DISPLAY                                      _OFF
#endif

//-------------------------------------------------
// Eizo LVDS Setting Control
//-------------------------------------------------
#ifndef _LVDS_SETTING_CONTROL_BY_USER
#define _LVDS_SETTING_CONTROL_BY_USER                           _DISABLE
#endif

//-------------------------------------------------
// Eizo LVDS Driving Current Control (Active when _LVDS_SETTING_CONTROL_BY_USER == _ENABLE)
//-------------------------------------------------
#ifndef _LVDS_DRIV_CURRENT_USER_ADUST
#define _LVDS_DRIV_CURRENT_USER_ADUST                           0x02
#endif

//-------------------------------------------------
// Eizo LVDS Driving Double Current Control (Active when _LVDS_SETTING_CONTROL_BY_USER == _ENABLE)
//-------------------------------------------------
#ifndef _LVDS_PORTA_DATA0_DRIV_2X_USER_CTRL
#define _LVDS_PORTA_DATA0_DRIV_2X_USER_CTRL                     _DISABLE
#endif

#ifndef _LVDS_PORTA_DATA1_DRIV_2X_USER_CTRL
#define _LVDS_PORTA_DATA1_DRIV_2X_USER_CTRL                     _DISABLE
#endif

#ifndef _LVDS_PORTA_DATA2_DRIV_2X_USER_CTRL
#define _LVDS_PORTA_DATA2_DRIV_2X_USER_CTRL                     _DISABLE
#endif

#ifndef _LVDS_PORTA_DATA3_DRIV_2X_USER_CTRL
#define _LVDS_PORTA_DATA3_DRIV_2X_USER_CTRL                     _DISABLE
#endif

#ifndef _LVDS_PORTA_DATA4_DRIV_2X_USER_CTRL
#define _LVDS_PORTA_DATA4_DRIV_2X_USER_CTRL                     _DISABLE
#endif

#ifndef _LVDS_PORTB_DATA0_DRIV_2X_USER_CTRL
#define _LVDS_PORTB_DATA0_DRIV_2X_USER_CTRL                     _DISABLE
#endif

#ifndef _LVDS_PORTB_DATA1_DRIV_2X_USER_CTRL
#define _LVDS_PORTB_DATA1_DRIV_2X_USER_CTRL                     _DISABLE
#endif

#ifndef _LVDS_PORTB_DATA2_DRIV_2X_USER_CTRL
#define _LVDS_PORTB_DATA2_DRIV_2X_USER_CTRL                     _DISABLE
#endif

#ifndef _LVDS_PORTB_CLK_DRIV_2X_USER_CTRL
#define _LVDS_PORTB_CLK_DRIV_2X_USER_CTRL                       _DISABLE
#endif

#ifndef _LVDS_PORTB_DATA3_DRIV_2X_USER_CTRL
#define _LVDS_PORTB_DATA3_DRIV_2X_USER_CTRL                     _DISABLE
#endif

#ifndef _LVDS_PORTB_DATA4_DRIV_2X_USER_CTRL
#define _LVDS_PORTB_DATA4_DRIV_2X_USER_CTRL                     _DISABLE
#endif

//-------------------------------------------------
// Eizo LVDS Output Termination Control (Active when _LVDS_SETTING_CONTROL_BY_USER == _ENABLE)
//-------------------------------------------------
#ifndef _LVDS_PORTA_DATA0_TERMINATION_USER_ADJUST
#define _LVDS_PORTA_DATA0_TERMINATION_USER_ADJUST               0x03
#endif

#ifndef _LVDS_PORTA_DATA1_TERMINATION_USER_ADJUST
#define _LVDS_PORTA_DATA1_TERMINATION_USER_ADJUST               0x03
#endif

#ifndef _LVDS_PORTA_DATA2_TERMINATION_USER_ADJUST
#define _LVDS_PORTA_DATA2_TERMINATION_USER_ADJUST               0x03
#endif

#ifndef _LVDS_PORTA_DATA3_TERMINATION_USER_ADJUST
#define _LVDS_PORTA_DATA3_TERMINATION_USER_ADJUST               0x03
#endif

#ifndef _LVDS_PORTA_DATA4_TERMINATION_USER_ADJUST
#define _LVDS_PORTA_DATA4_TERMINATION_USER_ADJUST               0x03
#endif

#ifndef _LVDS_PORTB_DATA0_TERMINATION_USER_ADJUST
#define _LVDS_PORTB_DATA0_TERMINATION_USER_ADJUST               0x03
#endif

#ifndef _LVDS_PORTB_DATA1_TERMINATION_USER_ADJUST
#define _LVDS_PORTB_DATA1_TERMINATION_USER_ADJUST               0x03
#endif

#ifndef _LVDS_PORTB_DATA2_TERMINATION_USER_ADJUST
#define _LVDS_PORTB_DATA2_TERMINATION_USER_ADJUST               0x03
#endif

#ifndef _LVDS_PORTB_CLK_TERMINATION_USER_ADJUST
#define _LVDS_PORTB_CLK_TERMINATION_USER_ADJUST                 0x03
#endif

#ifndef _LVDS_PORTB_DATA3_TERMINATION_USER_ADJUST
#define _LVDS_PORTB_DATA3_TERMINATION_USER_ADJUST               0x03
#endif

#ifndef _LVDS_PORTB_DATA4_TERMINATION_USER_ADJUST
#define _LVDS_PORTB_DATA4_TERMINATION_USER_ADJUST               0x03
#endif

//-------------------------------------------------
// Eizo LVDS Pull Down Control (Active when _LVDS_SETTING_CONTROL_BY_USER == _ENABLE)
//-------------------------------------------------
#ifndef _LVDS_PORTA_WEAKLY_PULL_DOWN_USER_CONTROL
#define _LVDS_PORTA_WEAKLY_PULL_DOWN_USER_CONTROL               _DISABLE
#endif

#ifndef _LVDS_PORTA_STRONGLY_PULL_DOWN_USER_CONTROL
#define _LVDS_PORTA_STRONGLY_PULL_DOWN_USER_CONTROL             _DISABLE
#endif

#ifndef _LVDS_PORTB_WEAKLY_PULL_DOWN_USER_CONTROL
#define _LVDS_PORTB_WEAKLY_PULL_DOWN_USER_CONTROL               _DISABLE
#endif

#ifndef _LVDS_PORTB_STRONGLY_PULL_DOWN_USER_CONTROL
#define _LVDS_PORTB_STRONGLY_PULL_DOWN_USER_CONTROL             _DISABLE
#endif


////////
// LG //
////////

//--------------------------------------------------
//  LG DP Power Management
//--------------------------------------------------
#ifndef _DP_POWER_MANAGEMENT_FOR_FAST_DISPLAY_RECOVER
#define _DP_POWER_MANAGEMENT_FOR_FAST_DISPLAY_RECOVER           _OFF
#endif

//===================== END =======================

