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
// ID Code      : RTD2785T_DEMO_V1_3_1A1DPmDP1H1DUALDVI_LVDS_eDP.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#if(_PCB_TYPE == _RTD2785T_DEMO_V1_3_1A1DPmDP1H1DUALDVI_LVDS_eDP)


///////////////////
// External Xtal //
///////////////////

//--------------------------------------------------
// External Xtal Define
//--------------------------------------------------
#define _EXT_XTAL                               _XTAL14318K


///////////////////////
// Input Port Config //
///////////////////////

//--------------------------------------------------
// A0 Input Port
//--------------------------------------------------
#define _A0_INPUT_PORT_TYPE                                 _A0_VGA_PORT
#define _A0_EMBEDDED_DDCRAM_MAX_SIZE            _EDID_SIZE_128
#define _A0_EMBEDDED_DDCRAM_LOCATION            _EDID_TABLE_LOCATION_CODE

//--------------------------------------------------
// D0 Input Port
//--------------------------------------------------
#define _D0_INPUT_PORT_TYPE                                 _D0_DP_PORT
#define _D0_DDC_CHANNEL_SEL                              _DDC0
#define _D0_EMBEDDED_DDCRAM_MAX_SIZE            _EDID_SIZE_256
#define _D0_EMBEDDED_DDCRAM_LOCATION            _EDID_TABLE_LOCATION_CODE
#define _D0_DP_CONNECTOR_TYPE                           _DP_CONNECTOR_NORMAL
#define _D0_DP_LINK_CLK_RATE                              _DP_HIGH_SPEED2_540MHZ
#define _D0_DP_MAIN_LINK_LANES                          _DP_FOUR_LANE

//--------------------------------------------------
// D1 Input Port
//--------------------------------------------------
#define _D1_INPUT_PORT_TYPE                                 _D1_HDMI_PORT
#define _D1_DDC_CHANNEL_SEL                              _DDC1
#define _D1_EMBEDDED_DDCRAM_MAX_SIZE            _EDID_SIZE_256
#define _D1_EMBEDDED_DDCRAM_LOCATION            _EDID_TABLE_LOCATION_CODE


//--------------------------------------------------
// D2 Input Port
//--------------------------------------------------
#define _D2_INPUT_PORT_TYPE                              _D2_NO_PORT//   _D2_DUAL_DVI_PORT
#define _D2_DDC_CHANNEL_SEL                               _DDC2
#define _D2_EMBEDDED_DDCRAM_MAX_SIZE            _EDID_SIZE_128
#define _D2_EMBEDDED_DDCRAM_LOCATION            _EDID_TABLE_LOCATION_CODE

//--------------------------------------------------
// D3 Input Port
//--------------------------------------------------
#define _D3_INPUT_PORT_TYPE                                 _D3_NO_PORT
#define _D3_DDC_CHANNEL_SEL                               _DDC3
#define _D3_EMBEDDED_DDCRAM_MAX_SIZE            _EDID_SIZE_128
#define _D3_EMBEDDED_DDCRAM_LOCATION            _EDID_TABLE_LOCATION_CODE




///////////////
// TMDS Port //
///////////////

//--------------------------------------------------
// TMDS Signal Swap Options
//--------------------------------------------------
#define _D1_TMDS_BR_SWAP                        _ON
#define _D1_TMDS_PN_SWAP                        _ON


#define _D2_TMDS_BR_SWAP                        _ON
#define _D2_TMDS_PN_SWAP                        _ON

#define _D3_TMDS_BR_SWAP                        _ON
#define _D3_TMDS_PN_SWAP                        _ON



/////////////
// DP Port //
/////////////

//--------------------------------------------------
// DP Lane & PN Swap Option
//--------------------------------------------------
#define _D0_DP_PCB_LANE0_MAPPING                _DP_SCALER_LANE0
#define _D0_DP_PCB_LANE1_MAPPING                _DP_SCALER_LANE1
#define _D0_DP_PCB_LANE2_MAPPING                _DP_SCALER_LANE2
#define _D0_DP_PCB_LANE3_MAPPING                _DP_SCALER_LANE3
#define _D0_DP_PCB_LANE0_PN_SWAP                _OFF
#define _D0_DP_PCB_LANE1_PN_SWAP                _OFF
#define _D0_DP_PCB_LANE2_PN_SWAP                _OFF
#define _D0_DP_PCB_LANE3_PN_SWAP                _OFF

#define _D1_DP_PCB_LANE0_MAPPING                _DP_SCALER_LANE0
#define _D1_DP_PCB_LANE1_MAPPING                _DP_SCALER_LANE1
#define _D1_DP_PCB_LANE2_MAPPING                _DP_SCALER_LANE2
#define _D1_DP_PCB_LANE3_MAPPING                _DP_SCALER_LANE3
#define _D1_DP_PCB_LANE0_PN_SWAP                _OFF
#define _D1_DP_PCB_LANE1_PN_SWAP                _OFF
#define _D1_DP_PCB_LANE2_PN_SWAP                _OFF
#define _D1_DP_PCB_LANE3_PN_SWAP                _OFF

#define _DPTX_PCB_LANE0_MAPPING                 _DP_SCALER_LANE0
#define _DPTX_PCB_LANE1_MAPPING                 _DP_SCALER_LANE1
#define _DPTX_PCB_LANE2_MAPPING                 _DP_SCALER_LANE2
#define _DPTX_PCB_LANE3_MAPPING                 _DP_SCALER_LANE3
#define _DPTX_PCB_LANE0_PN_SWAP                 _OFF
#define _DPTX_PCB_LANE1_PN_SWAP                 _OFF
#define _DPTX_PCB_LANE2_PN_SWAP                 _OFF
#define _DPTX_PCB_LANE3_PN_SWAP                 _OFF




/////////////////////////////
// Search Group & Priority //
/////////////////////////////

//--------------------------------------------------
// Input Port Search Group Define
//--------------------------------------------------
#define _A0_INPUT_PORT_GROUP                    _INPUT_PORT_GROUP_0
#define _D0_INPUT_PORT_GROUP                    _INPUT_PORT_GROUP_0
#define _D1_INPUT_PORT_GROUP                    _INPUT_PORT_GROUP_0
//#define _D2_INPUT_PORT_GROUP                    _INPUT_PORT_GROUP_0
//#define _D3_INPUT_PORT_GROUP                    _INPUT_PORT_GROUP_0

//--------------------------------------------------
// Input Port Search Priority Define (Must Start From Valid Port)
//--------------------------------------------------
#define _INPUT_PORT_SEARCH_PRI_0                _A0_INPUT_PORT
#define _INPUT_PORT_SEARCH_PRI_1                _D0_INPUT_PORT
#define _INPUT_PORT_SEARCH_PRI_2                _D1_INPUT_PORT
//#define _INPUT_PORT_SEARCH_PRI_3                _D2_INPUT_PORT
//#define _INPUT_PORT_SEARCH_PRI_4                _D3_INPUT_PORT


////////////////////
// For LVDS Panel //
////////////////////

//--------------------------------------------------
// LVDS Port Config
//--------------------------------------------------
#if(_LVDS_OUTPUT_PORT == _LVDS_2_PORT)
#define _LVDS_PORT_SEL                                  _LVDS_2_PORT_AB
#define _LVDS_PORT_MIRROR                             _DISABLE
#define _LVDS_PORT_AB_SWAP                          _DISABLE
#define _LVDS_PORT_CD_SWAP                         _DISABLE
#define _LVDS_PN_SWAP                                    _DISABLE
#elif(_LVDS_OUTPUT_PORT == _LVDS_4_PORT)

#endif

//--------------------------------------------------
// LVDS Driving Config
//--------------------------------------------------
#define _LVDS_DRIV_CONTROL                      _LVDS_DRIV_CONTROL_3_0
#define _LVDS_VCM_CONTROL                       _LVDS_VCM_NORMAL
#define _LVDS_SR_CONTROL                        _LVDS_SR_CONTROL_0
#define _LVDS_PRE_EMPHASIS_CONTROL              _LVDS_PRE_EMPHASIS_0
#define _LVDS_TERMINATION_CONTROL               _DISABLE

//--------------------------------------------------
// LVDS SSC Config
//--------------------------------------------------
#define _LVDS_SPREAD_RANGE                      0//10
#define _LVDS_SPREAD_SPEED                      _SPEED_33K


/////////////////////////
// eDPTx 1.1 HBR Panel //
/////////////////////////

//--------------------------------------------------
// eDPTx 1.1 HBR Main Link Config
//--------------------------------------------------
#define _PANEL_DPTX_1_1_LANE_SWAP                   _ENABLE
#define _PANEL_DPTX_1_1_LANE_PN_SWAP              _DISABLE
#define _PANEL_DPTX_1_1_SWING_LEVEL                 _DP_SWING_800_MV
#define _PANEL_DPTX_1_1_PREEMPHASIS_LEVEL       _DP_PREEMPHASIS_0_DB

//--------------------------------------------------
// eDPTx 1.1 HBR SSC Config
//--------------------------------------------------
#define _PANEL_DPTX_1_1_SPREAD_RANGE            0//5
#define _PANEL_DPTX_1_1_SPREAD_SPEED            _SPEED_33K


/////////
// PWM //
/////////

//--------------------------------------------------
// PWM Setting
//--------------------------------------------------
#define _PWM_DUT_RESOLUTION                     _PWM_8BIT

#define _BACKLIGHT_PWM                          _PWM5
#define _BACKLIGHT_PWM_INVERSE                  _ON

#define _PWM0_EN                                _OFF
#define _PWM1_EN                                _OFF
#define _PWM2_EN                                _OFF
#define _PWM3_EN                                _OFF
#define _PWM4_EN                                _OFF
#define _PWM5_EN                                _ON

#define _PWM0_PSAV_EN                           _OFF
#define _PWM1_PSAV_EN                           _OFF
#define _PWM2_PSAV_EN                           _OFF
#define _PWM3_PSAV_EN                           _OFF
#define _PWM4_PSAV_EN                           _OFF
#define _PWM5_PSAV_EN                           _OFF

#define _PWM0_PDOW_EN                           _OFF
#define _PWM1_PDOW_EN                           _OFF
#define _PWM2_PDOW_EN                           _OFF
#define _PWM3_PDOW_EN                           _OFF
#define _PWM4_PDOW_EN                           _OFF
#define _PWM5_PDOW_EN                           _OFF

#define _PWM0_RST_BY_DVS                        _OFF
#define _PWM1_RST_BY_DVS                        _OFF
#define _PWM2_RST_BY_DVS                        _OFF
#define _PWM3_RST_BY_DVS                        _OFF
#define _PWM4_RST_BY_DVS                        _OFF
#define _PWM5_RST_BY_DVS                        _ON
#define _PWM_RST_BY_TCON                        _OFF


/////////////////
// SW & HW IIC //
/////////////////

//--------------------------------------------------
// Sofware and Hardware IIC Option
//--------------------------------------------------
#define _SW_IIC_SUPPORT                        _OFF
#define _SW_IIC_CLK_DIV                         _DIV_1

#define _HW_IIC_SUPPORT                         _ON
#define _HW_IIC_SPEED                           _HW_IIC_LOW_SPEED_100K


///////////////////
// System Eeprom //
///////////////////

//--------------------------------------------------
// Eeprom System Data Storage Option
//--------------------------------------------------
#define _EEPROM_TYPE                            _EEPROM_24LC16
#define _EEPROM_SLAVE_ADDRESS                   0xA0
#define _PCB_SYS_EEPROM_IIC                     _HW_IIC_PIN_210_211


//////////
// Misc //
//////////

//--------------------------------------------------
// AD Key Option
//--------------------------------------------------
#define _AD_KEY_SUPPORT                         _ON

//--------------------------------------------------
// Low Speed ADC Option
//--------------------------------------------------
#define _LOW_SPEED_ADC_SUPPORT                  _ON


//////////////////////
// Series Pin Share //
//////////////////////

//--------------------------------------------------
//  RL6432 216 Pin Share
//--------------------------------------------------
// HDMI_CABLE_DETECT_3
#define _PIN_1                                  (0 & 0x0F) // Page 10-0x00[2:0]
// 0 ~ 6 (0: P1D0i<I>,    1: P1D0o<PP>,   2: P1D0o<OD>, 3: test4b_out0,
//        4: test4b_out1, 5: test4b_out2, 6: test4b_out3)

// CBUS/HDMI_HPD_3
#define _PIN_3                                  (2 & 0x0F) // Page 10-0x01[2:0]
// 0 ~ 2 (0: P1D1i<I>, 1: P1D1o<PP>, 2: P1D1o<OD> & d3_hdmi_hpd_int<I>)

// CBUS/HDMI_HPD_2
#define _PIN_15                                 (2 & 0x0F) // Page 10-0x02[2:0]
// 0 ~ 2 (0: P1D2i<I>, 1: P1D2o<PP>, 2: P1D2o<OD> & d2_hdmi_hpd_int <I>)

// DP_CABLE_DET_0
#define _PIN_53                                 (0 & 0x0F) // Page 10-0x03[2:0]
// 0 ~ 7 (0: P1D3i<I>,    1: P1D3o<PP>,   2: P1D3o<OD>, 3: tcon[0], 4: test4b_out0,
//        5: test4b_out1, 6: test4b_out2, 7: test4b_out3)

// DP_CABLE_DET_1
#define _PIN_54                                 (0 & 0x0F) // Page 10-0x04[2:0]
// 0 ~ 7 (0: P1D4i<I>,    1: P1D4o<PP>,   2: P1D4o<OD>, 3: tcon[8],  4: test4b_out0,
//        5: test4b_out1, 6: test4b_out2, 7: test4b_out3)

// DDCSCL_VGA
#define _PIN_66                                 (8 & 0x0F) // Page 10-0x05[2:0]
// 0 ~ 8 (0: P1D5i<I>, 1: P1D5o<PP>, 2: P1D5o<OD>, 8: DDCSCLVGA)

// DDCSDA_VGA
#define _PIN_67                                 (8 & 0x0F) // Page 10-0x06[2:0]
// 0 ~ 8 (0: P1D6i<I>, 1: P1D6o<PP>, 2: P1D6o<OD>, 8: DDCSDAVGA)

// VGA_CABLE_DET//MUTE
#define _PIN_68                                 (2 & 0x0F) // Page 10-0x07[2:0]
// 0 ~ 2 (0: P1D7i<I>, 1: P1D7o<PP>,   2: P1D7o<OD>, 3: pwm0 <PP>,  4: pwm0 <OD>,
//        5: tcon[4],  6: test4b_out2, 7: test4b_out3)

// AUX_CHP_0
#define _PIN_71                                 (3 & 0x0F) // Page 10-0x08[2:0]
// 0 ~ 3 (0: P3D0i<I>, 1: Reserved, 2: P3D0o<OD>, 3: AUXp0)

// AUX_CHN_0
#define _PIN_72                                 (3 & 0x0F) // Page 10-0x09[2:0]
// 0 ~ 3 (0: P3D1i<I>, 1: Reserved, 2: P3D1o<OD>, 3: AUXn0)

// AUX_CHP_1// //DDCSCL1
#define _PIN_73                                (8 & 0x0F) // Page 10-0x0A[2:0]
// 0 ~ 8 (0: P3D2i<I>, 1: Reserved, 2: P3D2o<OD>, 3: AUXp1, 8:DDCSCL1)

// AUX_CHN_1 //DDSSDA1 
#define _PIN_74                               (8 & 0x0F) // Page 10-0x0B[2:0]
// 0 ~ 8 (0: P3D3i<I>, 1: Reserved, 2: P3D1o<OD>, 3: AUXn1, 8: DDSSDA1)

//ADC_KEY1
#define _PIN_91                                 (3 & 0x0F) // Page 10-0x0C[2:0]
// 0 ~ 6 (0: P3D4i<I>,     1: P3D4o<PP>, 2: P3D4o<OD>, 3: a_adc0_0, 4: int0,
//        5: test4b_out0 , 6:test4b_out1)

// ADC_KEY2
#define _PIN_92                                 (3 & 0x0F) // Page 10-0x0D[2:0]
// 0 ~ 6 (0: P3D5i<I>,     1: P3D5o<PP>, 2: P3D5o<OD>, 3: a_adc1_0, 4: int1,
//        5: test4b_out2 , 6:test4b_out3)

// MHL_DETECT_3
#define _PIN_93                                 (0 & 0x0F) // Page 10-0x0E[2:0]
// 0 ~ 6 (0: P3D6i<I>,     1: P3D6o<PP>, 2: P3D6o<OD>, 3: a_adc2_0, 4: tcon[9],
//        5: test4b_out0 , 6:test4b_out1)

// MHL_DETECT_2
#define _PIN_94                                 (0 & 0x0F) // Page 10-0x0F[2:0]
// 0 ~ 6 (0: P3D7i<I>,     1: P3D7o<PP>, 2: P3D7o<OD>, 3: a_adc3_0, 4: tcon[10],
//        5: test4b_out2 , 6:test4b_out3)

// DPTX_AUX_P
#define _PIN_89                                 (3 & 0x0F) // Page 10-0x10[2:0]
// 0 ~ 3 (0: P4D0i<I>, 1: P4D0o<PP>, 2: P4D0o<OD>, 3: DPTX_aux_ch_p)

// DPTX_AUX_N
#define _PIN_90                                 (3 & 0x0F) // Page 10-0x11[2:0]
// 0 ~ 3 (0: P4D1i<I>, 1: P4D1o<PP>, 2: P4D1o<OD>, 3: DPTX_aux_ch_n)

// AUDIO_HOUTL
#define _PIN_99                                 (3 & 0x0F) // Page 10-0x12[2:0]
// 0 ~ 5 (0: P4D2i<I>, 1: P4D2o<PP>, 2: P4D2o<OD>, 3: Audio_houtl, 4: sd2, 5: spdif2)

// AUDIO_HOUTR
#define _PIN_100                                (3 & 0x0F) // Page 10-0x13[2:0]
// 0 ~ 5 (0: P4D3i<I>, 1: P4D3o<PP>, 2: P4D3o<OD>, 3: Audio_houtr, 4: sd3, 5: spdif3)

// LINE_INL
#define _PIN_103                                (3 & 0x0F) // Page 10-0x14[2:0]
// 0 ~ 4 (0: P4D4i<I>, 1: P4D4o<PP>, 2: P4D4o<OD>, 3: line_inl, 4: ws)

// LINE_INR
#define _PIN_104                                (3 & 0x0F) // Page 10-0x15[2:0]
// 0 ~ 4 (0: P4D5i<I>, 1: P4D5o<PP>, 2: P4D5o<OD>, 3: line_inr, 4: sck)

// AUDIO_REF
#define _PIN_105                                (3 & 0x0F) // Page 10-0x16[2:0]
// 0 ~ 4 (0: P4D6i<I>, 1: P4D6o<PP>, 2: P4D6o<OD>, 3: Audio_ref, 4: mck)

// AUDIO_SOUTL
#define _PIN_106                                (3 & 0x0F) // Page 10-0x17[2:0]
// 0 ~ 5 (0: P4D7i<I>, 1: P4D7o<PP>, 2: P4D7o<OD>, 3: Audio_soutl, 4: sd0,
//        5: spdif0)

// AUDIO_SOUTR
#define _PIN_107                                (3 & 0x0F) // Page 10-0x18[2:0]
// 0 ~ 5 (0: P5D0i<I>, 1: P5D0o<PP>, 2: P5D0o<OD>, 3: Audio_soutr, 4: sd1,
//        5: spdif1)

// DPTX_AUX_P_2
#define _PIN_174_OFF_REGION                     (6 & 0x0F) // Page 10-0x19[2:0]
// 0 ~ 6 (0: P5D1i<I>, 1: P5D1o<PP>, 2: P5D1o<OD>, 3: PWM3<PP>, 4: PWM3<OD>,
//        5: tcon[6],  6: DPTX_aux_ch_p_1)

// DPTX_AUX_N_2
#define _PIN_175_OFF_REGION                     (6 & 0x0F) // Page 10-0x1A[2:0]
// 0 ~ 6 (0: P5D2i<I>, 1: P5D2o<PP>, 2: P5D2o<OD>, 3: PWM1<PP>, 4: PWM1<OD>,
//        5: TCON[7],  6: DPTX_aux_ch_n_1)

// TX2_HPD_2
#define _PIN_173_OFF_REGION                     (3 & 0x0F) // Page 10-0x1B[2:0]
// 0 ~ 4 (0: P5D3i<I>, 1: P5D3o<PP>, 2: P5D3o<OD>, 3: DPTX_hpd1_org, 4:  tcon[8])

// AUDIO_SDA (NC)
#define _PIN_164_OFF_REGION                     (2 & 0x0F) // Page 10-0x1C[2:0]
// 0 ~ 6 (0: P5D4i<I>,   1: P5D4o<PP>, 2: P5D4o<OD>, 3: ws, 4: tcon[12],
//        5:test4b_out0, 6: test4b_out1)

// AUDIO_SCL (NC)
#define _PIN_165_OFF_REGION                     (2 & 0x0F) // Page 10-0x1D[2:0]
// 0 ~ 5 (0: P5D5i<I>,    1: P5D5o<PP>, 2: P5D5o<OD>, 3: sck, 4: tcon[13] ,
//        5: test4b_out2, 6:  test4b_out3)

// NC
#define _PIN_166_OFF_REGION                     (1 & 0x0F) // Page 10-0x1E[2:0]
// 0 ~ 7 (0: P5D6i<I>,    1: P5D6o<PP>,  2: P5D6o<OD>, 3: mck, 4: test4b_out0 ,
//        5: test4b_out1, 6: test4b_out2 7: test4b_out3)

// NC
#define _PIN_167_OFF_REGION                     (1 & 0x0F) // Page 10-0x1F[2:0]
// 0 ~ 6 (0: P5D7i<I>,    1: P5D7o<PP>, 2: P5D7o<OD>, 3: spdif0, 4: sd0,
//        5: test4b_out0, 6: test4b_out1)

// NC
#define _PIN_168_OFF_REGION                     (1 & 0x0F) // Page 10-0x20[2:0]
// 0 ~ 8  (0: P6D0i<I>, 1: P6D0o<PP>, 2: P6D0o<OD>, 3: clko, 4: t0, 8: usb_spi_clk)

// MUTE (NC)
#define _PIN_169_OFF_REGION                     (0 & 0x0F) // Page 10-0x21[2:0]
// 0 ~ 8  (0: P6D1i<I>, 1: P6D1o<PP>, 2: P6D1o<OD>, 3: int0, 4: t1, 5: dena,
//         8: usb_spi_si )

// Panel_ON
#define _PIN_170_OFF_REGION                     (1 & 0x0F) // Page 10-0x22[2:0]
// 0 ~ 8  (0: P6D2i<I>, 1: P6D2o<PP>, 2: P6D2o<OD>, 3: int1, 4: t2, 5: DCLK,
//         8: usb_spi_so)

// NC// onBACKLITE
#define _PIN_171_OFF_REGION                     (2 & 0x0F) // Page 10-0x23[2:0]
// 0 ~ 8  (0: P6D3i<I>, 1: P6D3o<PP>, 2: P6D3o<OD>, 3: IRQB, 4: DVS,
//         8: usb_spi_ceb0)

// panel
#define _PIN_172_OFF_REGION                     (2 & 0x0F) // Page 10-0x24[2:0]
// 0 ~ 8 (0: P6D4i<I>, 1: P6D4o<PP>, 2: P6D4o<OD>, 3: T2ex, 4: DHS,
//        8: usb_spi_ceb1)

// ADJBACKLITE
#define _PIN_178_OFF_REGION                     (3 & 0x0F) // Page 10-0x25[2:0]
// 0 ~ 7 (0: P6D5i<I>, 1: P6D5o<PP>,   2: P6D5o<OD>, 3: PWM5<PP>, 4: PWM5<OD>,
//        5: TCON[2],  6: test4b_out0, 7: test4b_out1)

// MY_DP_EN
#define _PIN_179_OFF_REGION                     (1 & 0x0F) // Page 10-0x26[2:0]
// 0 ~ 8 (0: P6D6i<I>, 1: P6D6o<PP>, 2: P6D6o<OD>, 3: TCON[6],
//        4: IHS_after_scaling_down, 8: IICSCL1)

// DP5V_ON
#define _PIN_180_OFF_REGION                     (0 & 0x0F) // Page 10-0x27[2:0]
// 0 ~ 8 (0: P6D7i<I>, 1: P6D7o<PP>, 2: P6D7o<OD>, 3: tcon[7],
//        4: IVS_after_scaling_down, 8: IICSDA1)

// DP33V_ON (NC)
#define _PIN_183_OFF_REGION                     (1 & 0x0F) // Page 10-0x28[2:0]
// 0 ~ 4 (0: P7D0i<I>, 1: P7D0o<PP>, 2: P7D0o<OD>, 3: tcon[5],
//        4: IENA_after_scaling_down)

// FLASH_WP
#define _PIN_189                                (1 & 0x0F) // Page 10-0x29[2:0]
// 0 ~ 2 (0: P7D1i<I>, 1: P7D1o<PP>, 2: P7D1o<OD>)

// VBUS_EN_2
#define _PIN_192                                (1 & 0x0F) // Page 10-0x2A[2:0]
// 0 ~ 6 (0: P7D2i<I>, 1: P7D2o<PP>, 2: P7D2o<OD>, 3: PWM2<PP>, 4: PWM2<OD>,
//        5: TCON[1],  6: IRDA_in )

// VBUS_EN_3
#define _PIN_193                                (1 & 0x0F) // Page 10-0x2B[2:0]
// 0 ~ 7 (0: P7D3i<I>, 1: P7D3o<PP>,  2: P7D3o<OD>, 3: PWM4<PP>, 4: PWM4<OD>,
//        5: TCON[3],  6:Test4b_out2, 7: Test4b_out3)

// HDMI_MHL_SEL_2
#define _PIN_194                                (2 & 0x0F) // Page 10-0x2C[2:0]
// 0 ~ 7 (0: P7D4i<I>, 1: P7D4o<PP>, 2: P7D4o<OD>, 3: tcon[5], 4: pwm_out,
//        5: Test4b_out1, 6: Test4b_out2, 7: Test4b_out3)

// HDMI_MHL_SEL_3
#define _PIN_195                                (2 & 0x0F) // Page 10-0x2D[2:0]
// 0 ~ 7 (0: P7D5i<I>,    1: P7D5o<PP>,   2: P7D5o<OD>, 3: tcon[4], 4: pwm_in,
//        5: Test4b_out1, 6: Test4b_out2, 7: Test4b_out3)

// DPTX_HPD
#define _PIN_196                                (3 & 0x0F) // Page 10-0x2E[2:0]
// 0 ~ 7 (0: P7D6i<I>,    1: P7D6o<PP>,   2: P7D6o<OD>, 3: DPTX_hpd_org, 4: Test4b_out0,
//        5: Test4b_out1, 6: Test4b_out2, 7: Test4b_out3)

//DDR_PW_EN
#define _PIN_197                                (2 & 0x0F) // Page 10-0x2F[2:0]
// 0 ~ 5 (0: P7D7i<I>, 1: P7D7o<PP>, 2: P7D7o<OD>, 3: PWM5<PP>, 4: PWM5<OD>,
//        5: TCON[11])

// VCCK_OFF_EN
#define _PIN_198                                (2 & 0x0F) // Page 10-0x30[2:0]
// 0 ~ 8 (0: P8D0i<I>, 1: P8D0o<PP>, 2: P8D0o<OD>, 3: PWM4<PP>, 4: PWM4<OD>,
//        5: TCON[11], 8: IICSCL2)

// EDID_WP
#define _PIN_199                                (2 & 0x0F) // Page 10-0x31[2:0]
// 0 ~ 8 (0: P8D1i<I>, 1: P8D1o<PP>, 2: P8D1o<OD>, 3: PWM3<PP>, 4: PWM3<OD>,
//        5: TCON[0],  8: IICSDA2)

// DP_HOT_PLUG_0
#define _PIN_201                                (1 & 0x0F) // Page 10-0x32[2:0]
// 0 ~ 8 (0: P8D2i<I>,    1: P8D2o<PP>,   2: P8D2o<OD>,   3:  int0, 4: Test4b_out0,
//        5: Test4b_out1, 6: Test4b_out2, 7: Test4b_out3, 8: TXD)

// DP_HOT_PLUG_1
#define _PIN_200                                (1 & 0x0F) // Page 10-0x33[2:0]
// 0 ~ 8 (0: P8D3i<I>,    1: P8D3o<PP>,   2: P8D3o<OD>,   3: int1, 4: Test4b_out0,
//        5: Test4b_out1, 6: Test4b_out2, 7: Test4b_out3, 8: RXD)

// DP_SINK_ASS_N0
#define _PIN_202                                (0 & 0x0F) // Page 10-0x34[2:0]
// 0 ~ 7 (0: P8D4i<I>,    1: P8D4o<PP>,   2: P8D4o<OD>, 3: tcon[13], 4: Test4b_out0,
//        5: Test4b_out1, 6: Test4b_out2, 7: Test4b_out3)

// DP_SINK_ASS_P0
#define _PIN_203                                (0 & 0x0F) // Page 10-0x35[2:0]
// 0 ~ 7 (0: P8D5i<I>,    1: P8D5o<PP>,   2: P8D5o<OD>, 3: tcon[12], 4: Test4b_out0,
//        5: Test4b_out1, 6: Test4b_out2, 7: Test4b_out3)

// DP_SINK_ASS_N1
#define _PIN_204                                (0 & 0x0F) // Page 10-0x36[2:0]
// 0 ~ 7 (0: P8D6i<I>,    1: P8D6o<PP>,   2: P8D6o<OD>, 3:  tcon[10], 4: Test4b_out0,
//        5: Test4b_out1, 6: Test4b_out2, 7: Test4b_out3)

// DP_SINK_ASS_P1
#define _PIN_205                                (0 & 0x0F) // Page 10-0x37[2:0]
// 0 ~ 7 (0: P8D7i<I>,    1: P8D7o<PP>,   2: P8D7o<OD>, 3: tcon[9] , 4: Test4b_out0,
//        5: Test4b_out1, 6: Test4b_out2, 7: Test4b_out3)

// NC
#define _PIN_208                                (0 & 0x0F) // Page 10-0x38[2:0]
// 0 ~ 7 (0: P9D0i<I>,    1: Reserved,    2: Reserved, 4: Test4b_out0,
//        5: Test4b_out1, 6: Test4b_out2, 7: Test4b_out3)

// EEPROM_WP
#define _PIN_209                                (2 & 0x0F) // Page 10-0x39[2:0]
// 0 ~ 5 (0: P9D1i<I>, 1: P9D1o<PP>, 2: P9D1o<OD>, 3: PWM2<PP>, 4: PWM2<OD>
//        5: TCON[3])

// EESCL
#define _PIN_210                                (8 & 0x0F) // Page 10-0x3A[2:0]
// 0 ~ 8 (0: P9D2i<I>, 1: P9D2o<PP>, 2: P9D2o<OD>, 3: PWM0<PP>, 4: PWM0<OD>
//        5: TCON[1],  8: EEIICSCL)

// EESDA
#define _PIN_211                                (8 & 0x0F) // Page 10-0x3B[2:0]
// 0 ~ 8 (0: P9D3i<I>, 1: P9D3o<PP>, 2: P9D3o<OD>, 3: PWM1<PP>, 4: PWM1<OD>,
//        5: TCON[2],  8:EEIICSDA)

// DDCSCL_2
#define _PIN_212                                (8 & 0x0F) // Page 10-0x3C[2:0]
// 0 ~ 8 (0: P9D4i<I>, 1: Reserved, 2: P9D4o<OD>, 8: DDCSCL2)

// DDCSDA_2
#define _PIN_213                                (8 & 0x0F) // Page 10-0x3D[2:0]
// 0 ~ 8 (0: P9D5i<I>, 1: Reserved, 2: P9D5o<OD>, 8: DDCSDA2)

// DDCSCL_3
#define _PIN_214                                (8 & 0x0F) // Page 10-0x3E[2:0]
// 0 ~ 8 (0: P9D6i<I>, 1: Reserved, 2: P9D6o<OD>, 8: DDCSCL3)

// DDCSDA_3
#define _PIN_215                                (8 & 0x0F) // Page 10-0x3F[2:0]
// 0 ~ 8 (0: P9D7i<I>, 1: Reserved, 2: P9D7o<OD>, 8: DDCSDA3)

// HDMI_CABLE_DETECT_2//dp_hpd
#define _PIN_216                                (1 & 0x0F) // Page 10-0x40[2:0]
// 0 ~ 6 (0: PAD0i<I>,    1: PAD0o<PP>, 2: PAD0o<OD>, 3: Test4b_out0, 4: Test4b_out1,
//        5: Test4b_out2, 6: Test4b_out3)

// TXB4P
#define _PIN_139_OFF_REGION                     (4 & 0x0F) // Page 10-0x45[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PAD1i<I>, 2: PAD1o<PP>, 3: PAD1o<OD>, 4: TXB4+_10b)

// TXB4N
#define _PIN_140_OFF_REGION                     (4 & 0x0F) // Page 10-0x46[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PAD2i<I>, 2: PAD2o<PP>, 3: PAD2o<OD>, 4: TXB4-_10b)

// TXB3P
#define _PIN_141_OFF_REGION                     (4 & 0x0F) // Page 10-0x47[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PAD3i<I>, 2: PAD3o<PP>, 3: PAD3o<OD>, 4: TXB3+_10b)

// TXB3N
#define _PIN_142_OFF_REGION                     (4 & 0x0F) // Page 10-0x48[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PAD4i<I>, 2: PAD4o<PP>, 3: PAD4o<OD>, 4: TXB3-_10b)

// TXB2P
#define _PIN_143_OFF_REGION                     (4 & 0x0F) // Page 10-0x49[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PAD5i<I>, 2: PAD5o<PP>, 3: PAD5o<OD>, 4: TXB2+_10b)

// TXB2N
#define _PIN_144_OFF_REGION                     (4 & 0x0F) // Page 10-0x4A[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PAD6i<I>, 2: PAD6o<PP>, 3: PAD6o<OD>, 4: TXB2-_10b)

// TXB1P
#define _PIN_145_OFF_REGION                     (4 & 0x0F) // Page 10-0x4B[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PAD7i<I>, 2: PAD7o<PP>, 3: PAD7o<OD>, 4: TXB1+_10b)

// TXB1N
#define _PIN_146_OFF_REGION                     (4 & 0x0F) // Page 10-0x4C[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PBD0i<I>, 2: PBD0o<PP>, 3: PBD0o<OD>, 4: TXB1-_10b)

// TXB0P
#define _PIN_147_OFF_REGION                     (4 & 0x0F) // Page 10-0x4D[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PBD1i<I>, 2: PBD1o<PP>, 3: PBD1o<OD>, 4: TXB0+_10b)

// TXB0N
#define _PIN_148_OFF_REGION                     (4 & 0x0F) // Page 10-0x4E[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PBD2i<I>, 2: PBD2o<PP>, 3: PBD2o<OD>, 4: TXB0-_10b)

// TXA4P
#define _PIN_150_OFF_REGION                     (4 & 0x0F) // Page 10-0x4F[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PBD3i<I>, 2: PBD3o<PP>, 3: PBD3o<OD>, 4: TXA4+_10b)

// TXA4N
#define _PIN_151_OFF_REGION                     (4 & 0x0F) // Page 10-0x50[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PBD4i<I>, 2: PBD4o<PP>, 3: PBD4o<OD>, 4: TXA4+_10b)

// TXA3P
#define _PIN_152_OFF_REGION                     (4 & 0x0F) // Page 10-0x51[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PBD5i<I>, 2: PBD5o<PP>, 3: PBD5o<OD>, 4: TXA3+_10b)

// TXA3N
#define _PIN_153_OFF_REGION                     (4 & 0x0F) // Page 10-0x52[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PBD6i<I>, 2: PBD6o<PP>, 3: PBD6o<OD>, 4: TXA3-_10b)

// TXACP
#define _PIN_154_OFF_REGION                     (4 & 0x0F) // Page 10-0x53[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PBD7i<I>, 2: PBD7o<PP>, 3: PBD7o<OD>, 4: TXAC+_10b)

// TXACN
#define _PIN_155_OFF_REGION                     (4 & 0x0F) // Page 10-0x54[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PCD0i<I>, 2: PCD0o<PP>, 3: PCD0o<OD>, 4: TXAC-_10b)

// TXA2P
#define _PIN_156_OFF_REGION                     (4 & 0x0F) // Page 10-0x55[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PCD1i<I>, 2: PCD1o<PP>, 3: PCD1o<OD>, 4: TXA2+_10b)

// TXA2N
#define _PIN_157_OFF_REGION                     (4 & 0x0F) // Page 10-0x56[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PCD2i<I>, 2: PCD2o<PP>, 3: PCD2o<OD>, 4: TXA2-_10b)

// TXA1P
#define _PIN_158_OFF_REGION                     (4 & 0x0F) // Page 10-0x57[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PCD3i<I>, 2: PCD3o<PP>, 3: PCD3o<OD>, 4: TXA1+_10b)

// TXA1N
#define _PIN_159_OFF_REGION                     (4 & 0x0F) // Page 10-0x58[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PCD4i<I>, 2: PCD4o<PP>, 3: PCD4o<OD>, 4: TXA1-_10b)

// TXA0P
#define _PIN_160_OFF_REGION                     (4 & 0x0F) // Page 10-0x59[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PCD5i<I>, 2: PCD5o<PP>, 3: PCD5o<OD>, 4: TXA0+_10b)

// TXA0N
#define _PIN_161_OFF_REGION                     (4 & 0x0F) // Page 10-5A[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PCD6i<I>, 2: PCD6o<PP>, 3: PCD6o<OD>, 4: TXA0-_10b)

// LED1
#define _PIN_97                                 (2 & 0x0F) // Page 10-0x5B[2:0]
// 0 ~ 5 (0: PCD7i<I>, 1: PCD7o<PP>, 2: PCD7o<OD>, 3: PWM1<PP>, 4: PWM1<OD>,
//        5: PWM_out )

// LED2
#define _PIN_98                                 (2 & 0x0F) // Page 10-0x5C[2:0]
// 0 ~ 3 (0: PDD0i<I>, 1: PDD0o<PP>, 2: PDD0o<OD>, 3: PWM_in)



//////////////////////
// GPIO Power Macro //
//////////////////////

//-----------------------------------------------
// Macro of Pcb GPIO ON/OFF Region Initial Setting
//-----------------------------------------------
#define PCB_ON_REGION_GPIO_SETTING_POWER_AC_ON(){\
                                                }

#define PCB_OFF_REGION_GPIO_SETTING_POWER_AC_PD_PS_ON()\
                                                {\
                                                }

#define PCB_GPIO_SETTING_POWER_NORMAL()         {\
                                                }

#define PCB_GPIO_SETTING_POWER_SAVING()         {\
                                                }

#define PCB_GPIO_SETTING_POWER_DOWN()           {\
                                                }


/////////////////////
// PCB Power Macro //
/////////////////////

//-----------------------------------------------
// Macro of VCCK_OFF Power Control
//-----------------------------------------------
#define bVCCKOFFPOWER                           (MCU_FE20_PORT80_PIN_REG) // Pin_198, P8.0
#define DDRPOWEREN                                (MCU_FE1F_PORT77_PIN_REG) //pin197

#define _VCCK_OFF_POWER_ON                      1
#define _VCCK_OFF_POWER_OFF                     0

#define PCB_VCCK_OFF_POWER(x)                   {\
                                                    bVCCKOFFPOWER = (x);\
                                                    DDRPOWEREN = (x);\
                                                }

//-----------------------------------------------
// Macro of 12V to 5V Regulator for MyDP or MHL
//-----------------------------------------------
#define bREGULATOR_5V                           (MCU_FE16_PORT66_PIN_REG) // Pin_179, P6.6

#define _REGULATOR_5V_ON                        0
#define _REGULATOR_5V_OFF                       1

#define PCB_REGULATOR_5V_OUT(x)                 {\
                                                    bREGULATOR_5V = (x);\
                                                }


///////////////////////
// Panel Power Macro //
///////////////////////

//--------------------------------------------------
// Macro of Panel Power Up/Down
//--------------------------------------------------
#define bPANELPOWER                           (MCU_FE14_PORT64_PIN_REG) // Pin_172, P6.4

#define _PANEL_CONTROL_ON                       0
#define _PANEL_CONTROL_OFF                      1

#define PCB_PANEL_POWER(x)                      {\
                                                    bPANELPOWER = (x);\
                                                }

#define PCB_PANEL_POWER_DETECT()                (bPANELPOWER)

//--------------------------------------------------
// Macro of Light Power Up/Down
//--------------------------------------------------
#define bBACKLIGHTPOWER                        (MCU_FE13_PORT63_PIN_REG) // Pin_171, P6.3

#define _LIGHT_CONTROL_ON                       0
#define _LIGHT_CONTROL_OFF                      1

#define PCB_BACKLIGHT_POWER_PIN(x)              {\
                                                    bBACKLIGHTPOWER = (x);\
                                                }

#define PCB_BACKLIGHT_POWER(x)                  {\
                                                    if((x) == _LIGHT_CONTROL_ON)\
                                                    {\
                                                        ScalerTimerActiveTimerEvent(SEC(60), _USER_TIMER_EVENT_PANEL_USED_TIMER);\
                                                        ScalerMcuPwmAdjustFrequency(_BACKLIGHT_PWM, (((DWORD)_PANEL_TYP_FRAME_RATE * 60) / 100));\
                                                    }\
                                                    else\
                                                    {\
                                                        ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_PANEL_USED_TIMER);\
                                                    }\
                                                    PCB_BACKLIGHT_POWER_PIN(x)\
                                                }


/////////////////////////
// Write Protect Macro //
/////////////////////////

//-----------------------------------------------
// Macro of Flash write protect pin
//-----------------------------------------------
#define bFLASH_WRITE_PROTECT                    (MCU_FE19_PORT71_PIN_REG) // Pin_189, P7.1

#define _FLASH_WRITE_PROTECT_ENABLE             0
#define _FLASH_WRITE_PROTECT_DISABLE            1

#define PCB_FLASH_WRITE_PROTECT(x)              {\
                                                    bFLASH_WRITE_PROTECT = (x);\
                                                }

//-----------------------------------------------
// Macro of System Eeprom WP High/Low
//-----------------------------------------------
#define bEEPROM_WRITE_PROTECT                   (MCU_FE29_PORT91_PIN_REG) // Pin_209, P9.1

#define _EEPROM_WP_ENABLE                       1
#define _EEPROM_WP_DISABLE                      0

#define PCB_EEPROM_WRITE_PROTECT(x)             {\
                                                    bEEPROM_WRITE_PROTECT = (x);\
                                                }

#define PCB_EEPROM_WRITE_PROTECT_DETECT()       (bEEPROM_WRITE_PROTECT)

//-----------------------------------------------
// Macro of EDID Eeprom WP High/Low
//-----------------------------------------------
#define bEDID_WRITE_PROTECT                     (MCU_FE21_PORT81_PIN_REG) // Pin_199, P8.1

#define _EDID_EEPROM_WP_ENABLE                  1
#define _EDID_EEPROM_WP_DISABLE                 0

#define PCB_A0_EDID_EEPROM_WRITE_PROTECT(x)     {\
                                                    bEDID_WRITE_PROTECT = (x);\
                                                }

#define PCB_D1_EDID_EEPROM_WRITE_PROTECT(x)     {\
                                                    bEDID_WRITE_PROTECT = (x);\
                                                }

#define PCB_D2_EDID_EEPROM_WRITE_PROTECT(x)     {\
                                                    bEDID_WRITE_PROTECT = (x);\
                                                }

#define PCB_D3_EDID_EEPROM_WRITE_PROTECT(x)     {\
                                                    bEDID_WRITE_PROTECT = (x);\
                                                }


////////////////////////
// Cable Status Macro //
////////////////////////

//-----------------------------------------------
// Macro of Input Cable Connect
//-----------------------------------------------
#define bD0_DP_PIN15_CONNECT                    (MCU_FE25_PORT85_PIN_REG)  // Pin_203, P8.5
#define bD0_DP_PIN16_CONNECT                    (P1_3)                  // Pin_53, P1.3
#define bD0_DP_PIN17_CONNECT                    (MCU_FE24_PORT84_PIN_REG)  // Pin_202, P8.4


//#define bD1_DP_PIN15_CONNECT                    (MCU_FE27_PORT87_PIN_REG) // Pin_205, P8.7
//#define bD1_DP_PIN16_CONNECT                    (P1_4)                 // Pin_54, P1.4
//#define bD1_DP_PIN17_CONNECT                    (MCU_FE26_PORT86_PIN_REG) // Pin_204, P8.6

#define bA0_CONNECT                             (P1_7)  // Pin_68, P1.7
#define bD0_CONNECT                             (((bit)bD0_DP_PIN15_CONNECT == _TRUE) && ((bit)bD0_DP_PIN16_CONNECT == _TRUE) && ((bit)bD0_DP_PIN17_CONNECT == _FALSE))
#define bD1_CONNECT                             (P3_7) //pin94    (((bit)bD1_DP_PIN15_CONNECT == _TRUE) && ((bit)bD1_DP_PIN16_CONNECT == _TRUE) && ((bit)bD1_DP_PIN17_CONNECT == _FALSE))
#define bD2_CONNECT                           (P1_0)  // PIN_1, P1.0  (MCU_FE30_PORTA0_PIN_REG) // PIN_216, PA.0
#define bD3_CONNECT                             (P1_0)  // PIN_1, P1.0

#define PCB_A0_PIN()                            (0)//(bA0_CONNECT)
#define PCB_D0_PIN()                            (bD0_CONNECT)
#define PCB_D1_PIN()                            (bD1_CONNECT)
#define PCB_D2_PIN()                            (bD2_CONNECT)
#define PCB_D3_PIN()                            (0)

//-----------------------------------------------
// Macro of DP Source Power
//-----------------------------------------------
#define GET_PCB_D0_DP_SOURCE_POWER()            (bD0_DP_PIN17_CONNECT)
//#define GET_PCB_D1_DP_SOURCE_POWER()            (bD1_DP_PIN17_CONNECT)

//-----------------------------------------------
// Macro of MHL Cable Connect
//-----------------------------------------------
//#define bD1_MHL_CONNECT                         (P3_7) // Pin_94, P3.7
//#define bD2_MHL_CONNECT                         (P3_7) // Pin_94, P3.7
//#define bD3_MHL_CONNECT                         (P3_6) // Pin_93, P3.6

//#define PCB_D1_MHL_DETECT()                     (1)//(bD2_MHL_CONNECT)
//#define PCB_D2_MHL_DETECT()                     (1)//(bD2_MHL_CONNECT)
//#define PCB_D3_MHL_DETECT()                     (1)//(bD3_MHL_CONNECT)


////////////////////
// Hot Plug Macro //
////////////////////

//-----------------------------------------------
// Macro of Digital Hot Plug High/Low
//-----------------------------------------------
#define bD0_HPD                                (MCU_FE30_PORTA0_PIN_REG) // Pin_216, PA.0
#define bD1_HPD                                 (P1_2) // Pin_15, P1.2// 
#define bD2_HPD                                 (P1_1) // Pin_3, P1.1
#define bD3_HPD                                 (P1_1) // Pin_3, P1.1

#define _D0_HOT_PLUG_HIGH                       1
#define _D0_HOT_PLUG_LOW                        0

#define _D1_HOT_PLUG_HIGH                       1
#define _D1_HOT_PLUG_LOW                        0

#define _D2_HOT_PLUG_HIGH                       1
#define _D2_HOT_PLUG_LOW                        0

#define _D3_HOT_PLUG_HIGH                       1
#define _D3_HOT_PLUG_LOW                        0

#define PCB_D0_HOTPLUG(x)                       {\
                                                    bD0_HPD = (x);\
                                                }

#define PCB_D1_HOTPLUG(x)                       {\
                                                    bD1_HPD = (x);\
                                                }

#define PCB_D2_HOTPLUG(x)                       {\
                                                    bD2_HPD = (x);\
                                                }

#define PCB_D3_HOTPLUG(x)                       {\
                                                    bD3_HPD = (x);\
                                                }

#define PCB_D0_HOTPLUG_DETECT()                 (bD0_HPD)
#define PCB_D1_HOTPLUG_DETECT()                 (bD1_HPD)
#define PCB_D2_HOTPLUG_DETECT()                 (bD2_HPD)
#define PCB_D3_HOTPLUG_DETECT()                 (bD3_HPD)


///////////////
// MHL Macro //
///////////////

//-----------------------------------------------
// Macro of HDMI/MHL Switch
//-----------------------------------------------
#define bD2_TMDS_SWITCH                         (MCU_FE1C_PORT74_PIN_REG) // Pin_194, P7.4
#define bD3_TMDS_SWITCH                         (MCU_FE1D_PORT75_PIN_REG) // Pin_195, P7.5

#define _TMDS_SWITCH_MHL_CBUS                   0
#define _TMDS_SWITCH_HDMI_HPD                   1

#define PCB_D2_HDMI_MHL_SWITCH(x)               {\
                                                    bD2_TMDS_SWITCH = (x);\
                                                }

#define PCB_D3_HDMI_MHL_SWITCH(x)               {\
                                                    bD3_TMDS_SWITCH = (x);\
                                                }

//-----------------------------------------------
// Macro of MHL VBus Switch
//-----------------------------------------------
#define bD2_MHL_VBUS_SWITCH                     (MCU_FE1A_PORT72_PIN_REG) // Pin_192, P7.2
#define bD3_MHL_VBUS_SWITCH                     (MCU_FE1B_PORT73_PIN_REG) // Pin_193, P7.3

#define _MHL_VBUS_ON                            1
#define _MHL_VBUS_OFF                           0

#define PCB_D2_MHL_VBUS_SWITCH(x)               {\
                                                    bD2_MHL_VBUS_SWITCH = (x);\
                                                }

#define PCB_D3_MHL_VBUS_SWITCH(x)               {\
                                                    bD3_MHL_VBUS_SWITCH = (x);\
                                                }

#define PCB_GET_D2_MHL_VBUS_SWITCH()            (bD2_MHL_VBUS_SWITCH)
#define PCB_GET_D3_MHL_VBUS_SWITCH()            (bD3_MHL_VBUS_SWITCH)


///////////////
// PWM Macro //
///////////////

//-----------------------------------------------
// Macro of Pcb PWM Inital Setting
//-----------------------------------------------
#define PCB_PWM_SETTING()                       {\
                                                    ScalerMcuPwmAdjustFrequency(_BACKLIGHT_PWM, 240);\
                                                }

#if(_PWM_DUT_RESOLUTION == _PWM_8BIT)

#define PCB_BACKLIGHT_PWM(x)                    {\
                                                    MCU_ADJUST_8BIT_PWM_DUTY(_BACKLIGHT_PWM, (x));\
                                                }

#define PCB_GET_BACKLIGHT_PWM()                 (MCU_GET_8BIT_PWM_DUTY(_BACKLIGHT_PWM))

#elif(_PWM_DUT_RESOLUTION == _PWM_12BIT)

#define PCB_BACKLIGHT_PWM(x)                    {\
                                                    MCU_ADJUST_12BIT_PWM_DUTY(_BACKLIGHT_PWM, (x));\
                                                }

#define PCB_GET_BACKLIGHT_PWM()                 (MCU_GET_12BIT_PWM_DUTY(_BACKLIGHT_PWM))

#endif


///////////////
// LED Macro //
///////////////

//--------------------------------------------------
// Macro of LED On/Off
//--------------------------------------------------
#define bLED1                                   (MCU_FE47_PORTC7_PIN_REG) // Pin_97, PC.7
#define bLED2                                   (MCU_FE48_PORTD0_PIN_REG) // Pin_98, PD.0

#define _LED_ON                                 0
#define _LED_OFF                                1

#define PCB_LED_AC_ON_INITIAL()                 {\
                                                    bLED1 = _LED_OFF;\
                                                    bLED2 = _LED_OFF;\
                                                }

#define PCB_LED_ACTIVE()                        {\
                                                    bLED1 = _LED_ON;\
                                                    bLED2 = _LED_OFF;\
                                                }

#define PCB_LED_IDLE()                          {\
                                                    bLED1 = _LED_OFF;\
                                                    bLED2 = _LED_ON;\
                                                }

#define PCB_LED_POWER_SAVING()                  {\
                                                    bLED1 = _LED_OFF;\
                                                    bLED2 = _LED_ON;\
                                                }

#define PCB_LED_ON()                            {\
                                                    bLED1 = _LED_OFF;\
                                                    bLED2 = _LED_ON;\
                                                }

#define PCB_LED_OFF()                           {\
                                                    bLED1 = _LED_OFF;\
                                                    bLED2 = _LED_OFF;\
                                                }

#define PCB_LED_TYPE1()                         {\
                                                    bLED1 = _LED_ON;\
                                                }

#define PCB_LED_TYPE2()                         {\
                                                    bLED2 = _LED_ON;\
                                                }

#define PCB_LED_TYPE3()                         {\
                                                }

#define PCB_LED_TYPE4()                         {\
                                                }

#define PCB_LED_TYPE5()                         {\
                                                }

#define PCB_LED_TYPE_FLASH()                    {\
                                                }


//////////////////
// AD Key Macro //
//////////////////

//-----------------------------------------------
// Macro of Keypad Setting
//-----------------------------------------------
#define AD_KEY1                                 (MCU_FF09_ADC_A0_CONVERT_RESULT) // Pin_91
#define AD_KEY2                                 (MCU_FF0A_ADC_A1_CONVERT_RESULT) // Pin_92

#define PCB_ADKEY1()                            (AD_KEY1)
#define PCB_ADKEY2()                            (AD_KEY2)

#if(0)
#define PCB_KEY_STATE(ucV0, ucV1,ucV2, ucV3, ucKeyState)   {}

#else

#define PCB_KEY_STATE(ucV0, ucV1,ucV2, ucV3, ucKeyState)   {\
                                                   if((0x6E <= (ucV2)) && ((ucV2) < 0x83))\
                                                    {\
                                                        (ucKeyState) |= _LEFT_KEY_MASK;\
                                                    }\
                                                    if((0x2E <= (ucV2)) && ((ucV2) < 0x43))\
                                                    {\
                                                        (ucKeyState) |= _RIGHT_KEY_MASK;\
                                                    }\
                                                    if((0xAE <= (ucV2)) && ((ucV2) < 0xC5))\
                                                    {\
                                                        (ucKeyState) |= _EXIT_KEY_MASK;\
                                                    }\
                                                     if((0x00 <= (ucV2)) && ((ucV2) < 0x10))\
                                                    {\
                                                        (ucKeyState) |= _POWER_KEY_MASK;\
                                                    }\
                                                    if((0x00 <= (ucV1)) && ((ucV1) < 0x10))\
                                                    {\
                                                        (ucKeyState) |= _MENU_KEY_MASK;\
                                                    }\
                                                }
#endif


//-----------------------------------------------
// Macro of PCB Audio AMP Control
//-----------------------------------------------
sbit bPCBAMPMUTECONTROL         =             P1^7;  //pin68

#define _AMP_MUTE_ON                            1
#define _AMP_MUTE_OFF                           0

#define PCB_AMP_MUTE(x)                         {\
                                                    bPCBAMPMUTECONTROL = (x);\
                                                 }



#endif // End of #if(_PCB_TYPE == _RTD2785T_DEMO_V1_3_1A1DPmDP1H1DUALDVI_LVDS_eDP)
