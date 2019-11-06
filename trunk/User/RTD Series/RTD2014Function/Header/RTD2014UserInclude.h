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
// ID Code      : RTD2014UserInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "RTD2014UserModeTable.h"
#include "RTD2014UserInterfaceHDR.h"
#include "RTD2014UserInterfaceDimming.h"
#include "RTD2014UserInterfaceLocalDimming.h"
#include "RTD2014UserInterfaceGlobalDimming.h"

#if(_OSD_TYPE == _REALTEK_2014_OSD)

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************

//--------------------------------------------------
// Definitions of VGA Filter Table
//--------------------------------------------------
#if(_DIG_FILTER_ENHANCE_PHASE_ENABLE == _ENABLE)
#define _DIGITAL_FILTER_ENHANCE_PHASE_TABLE         "DigFilterEnhancePhaseTable.h"
#endif

#if(_RINGING_FILTER_SUPPORT == _ON)
#define _RINGING_FILTER_TABLE                       "RingingFilterTable.h"
#endif

//--------------------------------------------------
// Definitions of Flash Item Length For Each Page
//--------------------------------------------------
#define _DATA_ITEM_LENGTH                           16
#define _PAGE_INFO_LENGTH                           16

//---------------------------------------------------------
// OSD Rotate Type
//---------------------------------------------------------
#define _OSD_ROTATE_OFF                             0
#define _OSD_ROTATE_SOFTWARE                        1
#define _OSD_ROTATE_HARDWARE                        2

//--------------------------------------------------
// Definitions of DCR THD Setting
//--------------------------------------------------
#define _DCR_THESHOLD1                              0x20
#define _DCR_THESHOLD2                              0x180

//--------------------------------------------------
// MACRO for Type-C Port Controller
//--------------------------------------------------
#if((_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && ((_PORT_CONTROLLER_RTS5400_SERIES_SUPPORT == _ON) || (_PORT_CONTROLLER_USERDECITION_SUPPORT == _ON)))
#if(_TWO_CHIP_DATA_EXCHANGE_MODE == _DATA_EXCHANGE_MODE_NONE)
#define GET_TYPE_C_PORT_CTRL_POWER_OFF_FLG()        (g_bTypeCPortControllerPowerOffFlag)
#define SET_TYPE_C_PORT_CTRL_POWER_OFF_FLG()        (g_bTypeCPortControllerPowerOffFlag = _TRUE)
#define CLR_TYPE_C_PORT_CTRL_POWER_OFF_FLG()        (g_bTypeCPortControllerPowerOffFlag = _FALSE)
#endif
#endif

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if((_FLASH_PARTITION_TYPE == _FLASH_PARTITION_USER) && (_CODE_DIGITAL_SIGNATURE_SUPPORT == _SIGNATURE_TYPE_OFF))
extern BYTE code tFLASH_PARTITION_BOOTTABLE[];
#endif

extern code void (*OperationTable[])(void);

#if((_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && ((_PORT_CONTROLLER_RTS5400_SERIES_SUPPORT == _ON) || (_PORT_CONTROLLER_USERDECITION_SUPPORT == _ON)))
#if(_TWO_CHIP_DATA_EXCHANGE_MODE == _DATA_EXCHANGE_MODE_NONE)
extern bit g_bTypeCPortControllerPowerOffFlag;
#endif
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _FLASH_ITEMID_VGA_ADC_DATA = 0x0000, // 0
    _FLASH_ITEMID_YPBPR_ADC_DATA,
    _FLASH_ITEMID_SYSTEM_DATA,
    _FLASH_ITEMID_PANEL_INDEX,
    _FLASH_ITEMID_OSD_DATA_START,
    _FLASH_ITEMID_OSD_DATA_0 = _FLASH_ITEMID_OSD_DATA_START,
    _FLASH_ITEMID_OSD_DATA_1, // 5
    _FLASH_ITEMID_OSD_DATA_END = _FLASH_ITEMID_OSD_DATA_1,
    _FLASH_ITEMID_BRICON_SRC0_VGA,
    _FLASH_ITEMID_BRICON_SRC1_VIDEO,
    _FLASH_ITEMID_BRICON_SRC2_DVI,
    _FLASH_ITEMID_BRICON_SRC3_HDMI,
    _FLASH_ITEMID_BRICON_SRC4_DP, // 10
    _FLASH_ITEMID_COLORPROC0_9300,
    _FLASH_ITEMID_COLORPROC1_7500,
    _FLASH_ITEMID_COLORPROC2_6500,
    _FLASH_ITEMID_COLORPROC3_5800,
    _FLASH_ITEMID_COLORPROC4_SRGB, // 15
    _FLASH_ITEMID_COLORPROC5_USER,
    _FLASH_ITEMID_SIXCOLOR_DATA,
    _FLASH_ITEMID_PANEL_DATA,
    _FLASH_ITEMID_MODE_USER_DATA, // 19
    _FLASH_ITEMID_MODE_USER_DATA_END = _FLASH_ITEMID_MODE_USER_DATA + _MODE_SLOT_AMOUNT - 1 // 34
} EnumFlashItemIDType;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
// alant add 
//------------------------------------------------------------------------------------------------------




//----------------------------------------------------------------------------------------
// Extern functions from UserAdjust.c
//----------------------------------------------------------------------------------------
#ifndef __USER_ADJUST__

//-------------------------------------------------------
// Y-Peaking
//-------------------------------------------------------
#if(_YPEAKING_SUPPORT == _ON)
extern void UserInterfaceAdjustYpeaking(void);
#endif

//-------------------------------------------------------
// OD measure
//-------------------------------------------------------
#if(_FREESYNC_OD_MEASURE == _ON)
extern void UserAdjustFREESYNCODMeasure(void);
#endif


//-------------------------------------------------------
// Adjust Backlight
//-------------------------------------------------------
extern void UserAdjustBacklight(WORD usBacklight);

//-------------------------------------------------------
// Dp Load Edid Related
//-------------------------------------------------------
#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_WRITE_EDID_LOCATION_BY_USER_SUPPORT == _ON))
extern EnumEdidSelection UserAdjustGetDpEdidIndex(BYTE ucInputPort);
#endif

//-------------------------------------------------------
// Audio Related
//-------------------------------------------------------
#if(_AUDIO_SUPPORT == _ON)
extern void UserAdjustAudioMuteSwitch(void);
extern void UserAdjustAudioVolume(BYTE ucVolume);
extern WORD UserAdjustAudioVolumeMapping(BYTE ucVolume);
#endif // End of #if(_AUDIO_SUPPORT == _ON)

//-------------------------------------------------------
// DCR
//-------------------------------------------------------
#if(_DCR_SUPPORT == _ON)
extern void UserInterfaceAdjustDCRHandler(void);
#if(_LD_TUNNEL_DETECT_SUPPORT == _ON)
extern void UserAdjustDCRTHD(void);
#endif
#endif

//-------------------------------------------------------
// DCC
//-------------------------------------------------------
#if(_DCC_FUNCTION == _ON)
extern void UserAdjustDCC(BYTE ucColorEffect);
#endif // End of #if(_DCC_FUNCTION == _ON)

#if(_DCC_HISTOGRM_INFO == _ON)
extern void UserInterfaceDCCHistogramHandler(void);
#endif

//-------------------------------------------------------
// IAPS
//-------------------------------------------------------
#if(_IAPS_SUPPORT == _ON)
extern void UserInterfaceAdjustIAPSHandler(void);
#endif

//-------------------------------------------------------
// ICM
//-------------------------------------------------------
#if(_ICM_SUPPORT == _ON)
extern void UserAdjustICM(BYTE ucColorEffect);
#endif

#if(_SCM_SUPPORT == _ON)
extern void UserAdjustSCM(BYTE ucColorEffect);
#endif

#if((_DCC_FUNCTION == _ON) || (_ICM_SUPPORT == _ON) || (_SCM_SUPPORT == _ON) || (_SIX_COLOR_SUPPORT == _ON))
extern void UserAdjustColorEffectMode(void);
#endif

//-------------------------------------------------------
// CTS / BRI
//-------------------------------------------------------
#if(_CONTRAST_SUPPORT == _ON)
extern void UserAdjustContrast(WORD usContrast);
#endif

#if(_BRIGHTNESS_SUPPORT == _ON)
extern void UserAdjustBrightness(WORD usBrightness);
#endif

//-------------------------------------------------------
// sRGB
//-------------------------------------------------------
#if(_GLOBAL_HUE_SATURATION == _ON)
extern void UserAdjustGlobalHueSat(SWORD shHue, WORD usSat);
#endif

//-------------------------------------------------------
// OD
//-------------------------------------------------------
#if(_OD_SUPPORT == _ON)
extern void UserAdjustOD(void);
#endif

//-------------------------------------------------------
// HLW
//-------------------------------------------------------
#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
extern void UserAdjustHLWinType(BYTE ucHLWinType);
extern void UserAdjustHLWinType5Move(void);
extern void UserAdjustHighLightWindowEffectSpace(void);
#endif

//-------------------------------------------------------
// IR
//-------------------------------------------------------
#if(_IR_SUPPORT == _IR_HW_SUPPORT)
extern void UserAdjusIR(void);
#endif

//-------------------------------------------------------
// DP
//-------------------------------------------------------
#if(_DP_EMBEDDED_SWITCH_SUPPORT_TYPE == _DP_EMBEDDED_SWITCH_2_DP)
extern void UserAdjustEmbeddedDpSwitch(void);
#endif

//-------------------------------------------------------
// Type-C Port Controller
//-------------------------------------------------------
#if((_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && ((_PORT_CONTROLLER_RTS5400_SERIES_SUPPORT == _ON) || (_PORT_CONTROLLER_USERDECITION_SUPPORT == _ON)))
#if(_TWO_CHIP_DATA_EXCHANGE_MODE == _DATA_EXCHANGE_MODE_NONE)
extern void UserAjustTypeCPowerControl(EnumPowerAction enumSwitch);
#endif
#endif

//-------------------------------------------------------
// SDRToHDR
//-------------------------------------------------------
#if(_SDR_TO_HDR_SUPPORT == _ON)
extern void UserAdjustSDRToHDR(bit bOn);
#endif
#endif // End of #ifndef __USER_ADJUST__

#ifndef __USER_ADJUST_3D_GAMMA__
//-------------------------------------------------------
// 3D Gamma
//-------------------------------------------------------
#if(_RGB_3D_GAMMA == _ON)
extern void UserAdjust3DGamma(BYTE uc3DGammaMode);
#endif
#endif

#ifndef __USER_ADJUST_OUTPUT_GAMMA__
//-------------------------------------------------------
// Output Gamma
//-------------------------------------------------------
#if(_GAMMA_FUNCTION == _ON)
extern void UserAdjustGamma(BYTE ucGamma);
#endif
//-------------------------------------------------------
// PCM
//-------------------------------------------------------
#if(_PCM_FUNCTION == _ON)
extern void UserAdjustPCM(BYTE ucPCM);
#endif

//-------------------------------------------------------
// Pixel Shift
//-------------------------------------------------------
#if(_PIXEL_SHIFT_SUPPORT== _ON)
extern void UserAdjustPixelShifting(void);
#endif

#endif

#ifndef __USER_ADJUST_RGB_GAMMA__
//-------------------------------------------------------
// RGB Output Gamma
//-------------------------------------------------------
#if(_RGB_GAMMA_FUNCTION == _ON)
extern void UserAdjustRGBGamma(BYTE ucGamma);
#endif
#endif


#ifndef __USER_ADJUST_UNIFORMITY__
//-------------------------------------------------------
// Unifomity
//-------------------------------------------------------
#if(_UNIFORMITY_SUPPORT == _ON)
extern void UserAdjustPanelUniformityMode(BYTE ucUniformity);
#endif
#endif

//----------------------------------------------------------------------------------------
// Extern functions from UserInterface.c
//----------------------------------------------------------------------------------------
#ifndef __USER_INTERFACE__

extern void UserInterfaceTimerEventProc(EnumScalerTimerEventID enumEventID);

//-------------------------------------------------------
// INT
//-------------------------------------------------------
#if(_INSTANT_TIMER_EVENT_0 == _ON)
extern void UserInterfaceTimer0InstantAccess_EXINT(void);
#endif

#if(_INSTANT_TIMER_EVENT_1 == _ON)
extern void UserInterfaceTimer1InstantAccess_EXINT(void);
#endif

#if(_SYSTEM_TIMER_QUARTER_RESOLUTION == _ON)
extern void UserInterfaceTimer2InstantAccess_EXINT(void);
#endif

#if(_UART_SUPPORT == _ON)
extern void UserInterfaceUartIntHandler_SERIALPORT(void);
#endif

#if(_DEBUG_MESSAGE_SUPPORT == _OFF)
extern BYTE UserInterfaceGetDdcciStatus_EXINT1(void);
extern BYTE UserInterfaceGetFactoryCommand_EXINT1(void);

#if((_HDMI_FREESYNC_SUPPORT == _ON) && (_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE))
extern BYTE UserInterfaceDdcciHDMIFreesyncOpcode_EXINT1(void);
#endif
#endif

//-------------------------------------------------------
// EDID & HDCP
//-------------------------------------------------------
#if(_HDMI_MULTI_EDID_SUPPORT == _ON)
extern EnumHdmiEdidLocation UserInterfaceGetMultiHdmiEdidLocated(BYTE ucInputport, BYTE ucEdidIndex);
extern EnumEdidSelection UserInterfaceGetMultiHdmiEdidIndex(BYTE ucInputPort);
#endif

#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_WRITE_EDID_LOCATION_BY_USER_SUPPORT == _ON))
extern void UserInterfaceGetEmbeddedEDIDData(EnumInputPortEdid enumInputPort);
#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)
#if(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_USER)
extern void UserInterfaceGetHDCPKeyBksvByUser(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray);
extern void UserInterfaceGetHDCPKeyByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);

#if(_DP_TX_SUPPORT == _ON)
extern void UserInterfaceGetTxHDCPKeyAksvByUser(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray);
extern void UserInterfaceGetTxHDCPKeyByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#endif
#endif

#if((_HDCP_2_2_SUPPORT == _ON) && (_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_USER))
extern void UserInterfaceGetHdcp2CertrxByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserInterfaceGetHdcp2RSADkeyByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserInterfaceGetHdcp2RSARRModNByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserInterfaceGetHdcp2RSAKPrivByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserInterfaceGetHdcp2RSANpinvByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserInterfaceGetHdcp2LCKeyByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#if((_DP_HDCP_2_2_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
extern void UserInterfaceGetDpTxHdcp2RRMODNByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserInterfaceGetDpTxHdcp2DcpLlcNByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserInterfaceGetDpTxHdcp2EKeyByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserInterfaceGetDpTxHdcp2NPinvByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#endif
#endif
#endif


//-------------------------------------------------------
// Wait for Panel Power Sequence Delay
//-------------------------------------------------------
#if(_PANEL_POWER_SEQUENCE_CONTROL_BY_USER == _ON)
extern void UserInterfacePanelPowerAction(BYTE ucEvent);
#endif

extern void UserInterfaceAdjustWaitPanelT1(void);
extern void UserInterfaceAdjustWaitPanelT2(void);
extern void UserInterfaceAdjustWaitPanelT3(void);
extern void UserInterfaceAdjustWaitPanelT4(void);
extern void UserInterfaceAdjustWaitPanelT5(void);

//-------------------------------------------------------
// Misc
//-------------------------------------------------------
extern void UserInterfaceUncallFunction(void);
extern void UserInterfaceInitial(void);

extern void UserInterfacePowerSwitch(EnumPowerAction enumSwitch);
extern void UserInterfaceKeyPadLedControl(BYTE ucKeyPadLed);

//-------------------------------------------------------
// User Information
//-------------------------------------------------------
extern bit UserInterfaceGetLogoStatus(void);
extern bit UserInterfaceGetdNoSupportStatus(void);
extern bit UserInterfaceGetDclkNoSupportStatus(void);
extern bit UserInterfaceGetActiveByPassStatus(void);
extern bit UserInterfaceGetCableResetStatus(void);
extern bit UserInterfaceGetForcePSStatus(void);
extern bit UserInterfaceGetIntoPSStatus(void);
extern EnumUserForceFakePS UserInterfaceGetFakePSStatus(void);
extern bit UserInterfaceGetNVRamDataStatus(EnumNvramCheckType enumNvramCheckType);
extern bit UserInterfaceGetDisplaySettingBacklightAction(void);

extern EnumColorSpace UserInterfaceGetColorFormat(void);

#if(_OVERSCAN_SUPPORT == _ON)
extern bit UserInterfaceGetOverScanStatus(void);
#endif

#if(_ASPECT_RATIO_SUPPORT == _ON)
extern EnumAspectRatioType UserInterfaceGetAspectRatioType(void);
extern void UserInterfaceGetAspectRatio(WORD *pusHRatio, WORD *pusVRatio);
extern void UserInterfaceAdjustAspectRatio(void);
#if(_ASPECT_RATIO_WITHOUT_MUTE == _ON)
extern WORD UserInterfaceGetAspectRatioMinDVHeight(void);
#endif

#if(_ASPECT_ORIGINAL_MODE_SUPPORT == _ON)
extern BYTE UserInterfaceGetAspectRatioOriginalRatio(void);
#endif

#endif

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
extern EnumRotationType UserInterfaceGetRotationDegree(void);
extern EnumRotationDisplayType UserInterfaceGetRotationDisplayType(void);
#endif

#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
extern BYTE UserInterfaceGetDisplayLatencyRatio(void);
#endif

#if(_FRC_SUPPORT == _ON)
extern void UserInterfaceGetDVMaxMinFreq(StructDVCustomizedFreq *pstDVCustomizedFreq);
#endif

#if(_OD_SUPPORT == _ON)
extern EnumFunctionOnOFF UserInterfaceGetODEnableStatus(void);
#endif

#if((_MEMORY_TYPE_CONFIG == _MEMORY_DDR3) && (_DDR3_MULTIPHASE_EXIST == _ON))
extern void UserInterfaceUpdateDDR3PhaseData(void);
#endif

#if(_USER_SYSTEM_EEPROM_CUSTOMIZATION == _ON)
extern bit UserInterfaceSystemEepromReadCustomProc(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern bit UserInterfaceSystemEepromWriteCustomProc(WORD usSubAddr, WORD usLength, BYTE *pucWriteArray);
#endif

//-------------------------------------------------------
// Display Timing
//-------------------------------------------------------
extern void UserInterfaceDisplayInitialization(void);
extern void UserInterfaceAdjustInputTiming(void);
extern void UserInterfaceAdjustDisplayTiming(void);

#if(_UNDERSCAN_SUPPORT == _ON)
extern bit UserInterfaceAdjustUnderScan(void);
#endif

//-------------------------------------------------------
// Color
//-------------------------------------------------------
#if((_RGB_QUANTIZATION_RANGE_SUPPORT == _ON) && (_RGB_QUANTIZATION_DEFAULT_RANGE_JUDGE_BY_USER == _ON))
extern bit UserInterfaceGetRGBQuantizationLimitRangeStatus(EnumColorRGBQuantization enumColorRGBQuantization);
#endif

#if(_YCC_QUANTIZATION_RANGE_SUPPORT == _ON)
extern bit UserInterfaceGetYCCQuantizationFullRangeStatus(EnumColorYCCQuantization enumColorYCCQuantization);
#endif

extern void UserInterfaceAdjustActiveByPassColorProc(void);
extern void UserInterfaceAdjustColorProc(void);

#if(_ULTRA_VIVID_SUPPORT == _ON)
extern void UserInterfaceAdjustUltraVivid(void);
extern void UserInterfaceAdjustUltraVividProc(EnumDBApply enumDBApply);
#endif

#if(_SHARPNESS_SUPPORT == _ON)
extern code BYTE *UserInterfaceGetSharpnessCoef(EnumSUCoefType enumSUCoefType, EnumSourceSearchPort enumSourceSearchPort);
extern BYTE UserInterfaceGetSharpnessCoefBankNum(void);
extern bit UserInterfaceSharpnessBypassCheck(void);
#endif
//-------------------------------------------------------
// Osd
//-------------------------------------------------------
extern void UserInterfaceAdjustOsdPowerOnInitial(void);
extern void UserInterfaceAdjustOsdActiveProc(void);
extern void UserInterfaceAdjustOsdResetProc(void);

//-------------------------------------------------------
// Interfaces
//-------------------------------------------------------
#if(_VGA_SUPPORT == _ON)
extern BYTE UserInterfaceGetVGAConfuseMode(BYTE ucModeIndex);
extern bit UserInterfaceGetLoadModeTableDefaultStatus(void);
extern bit UserInterfaceGetFirstAutoConfigStatus(void);
extern void UserInterfaceGetAutoConfigPercentage(BYTE ucAutoPercentage);

extern bit UserInterfaceSkipAutoVpos(void);
extern bit UserInterfaceSkipAutoHpos(void);
#endif

#if(_MHL_SUPPORT == _ON)
extern bit UserInterfaceAdjustMHLMscRCPProc(BYTE ucKeyCode);
#endif

extern EnumFreeSyncSupport UserInterfaceGetFreeSyncEnable(EnumSourceSearchPort enumSourcePort);

#if(_DP_SUPPORT == _ON)
extern EnumDpVersionType UserInterfaceGetDPVersion(BYTE ucInputPort);
extern EnumDpLaneCount UserInterfaceGetDpLaneCount(BYTE ucInputPort);
extern EnumDPMSTPort UserInterfaceGetDpMSTCapablePort(void);

#if(_DP_EMBEDDED_SWITCH_SUPPORT_TYPE == _DP_EMBEDDED_SWITCH_2_DP)
extern void UserInterfaceEmbeddedDpSwitch(void);
#endif
#endif // End of #if(_DP_SUPPORT == _ON)

#if(_USB3_RETIMER_SUPPORT == _ON)
extern EnumUSBPDSupportStatus UserInterfaceGetUSBPDSupportStatus(void);
extern EnumUSBPSSupportStatus UserInterfaceGetUSBPSSupportStatus(void);
#endif

//-------------------------------------------------------
// AUDIO
//-------------------------------------------------------
#if(_AUDIO_SUPPORT == _ON)
extern bit UserInterfaceGetAudioReadyToPlayStatus(void);
extern bit UserInterfaceGetAudioMuteStatus(void);
extern EnumAudioInputSource UserInterfaceGetAudioSource(void);
extern bit UserInterfaceGetAudioNonLPCMStatus(void);
extern WORD UserInterfaceGetAudioVolume(void);

#if(_EMBEDDED_DAC_SUPPORT == _ON)
extern EnumAudioDACOutput UserInterfaceGetAudioDACOutput(void);
#endif

#if(_SLEEP_AUDIO_SUPPORT == _ON)
extern bit UserInterfaceGetAudioStandAloneStatus(void);
#endif

extern void UserInterfaceAdjustAudioResetProc(void);
extern void UserInterfaceAdjustAudioPowerProc(EnumPowerStatus enumPowStatus);
extern void UserInterfaceAdjustAudioAmpMuteProc(bit bMute);
#endif // End of #if(_AUDIO_SUPPORT == _ON)
#endif // End of #ifndef __USER_INTERFACE__

//-------------------------------------------------------
// RTD2014UserTypeCInterface.c
//-------------------------------------------------------
#ifndef __USER_TYPECINTERFACE__

#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
extern EnumTypeCU3ModeType UserInterfaceTypeCGetOsdU3ModeSelection(BYTE ucInputPort);
extern void UserInterfaceTypeCPinAssignSuccessProc(BYTE ucInputPort, EnumTypeCPinCfgType enumPinAssignment);

#if(_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
extern bit UserInterfaceTypeCHubProcSupport(BYTE ucInputPort);
extern void UserInterfaceTypeCOsdHubProc(BYTE ucInputPort);
extern WORD UserInterfaceTypeCUsbHubSetPollingStep(BYTE ucInputPort);
extern bit UserInterfaceTypeCUsbHubDetectDFPStatusUserFlow(BYTE ucInputPort);
extern bit UserInterfaceTypeCUsbHubSetSSMode(BYTE ucInputPort, bit bEn);
extern EnumHubDspDetectStatus UserInterfaceTypeCUsbHubDetectDFPStatus(BYTE ucInputPort);
#if(_BILLBOARD_HUB_SUPPORT == _ON)
extern void UserInterfaceTypeCUsbHubBillboardControl(BYTE ucInputPort, EnumBillboardCtrl enumAtion);
#endif
#endif // End of #if(_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)

#if((_PORT_CTRL_RTS_DET_CONNECTION_BY_USER == _ON) || (_PORT_CTRL_USER_DET_CONNECTION_BY_USER == _ON))
EnumTypeCAttachStatus UserInterfaceTypeCGetPortControllerCcAttach(BYTE ucInputPort);
EnumTypeCAltModeStatus UserInterfaceTypeCGetPortControllerAltModeReady(BYTE ucInputPort);
#endif  // End of #if((_PORT_CTRL_RTS_DET_CONNECTION_BY_USER == _ON) || (_PORT_CTRL_USER_DET_CONNECTION_BY_USER == _ON))

#if(_PORT_CONTROLLER_USERDECITION_SUPPORT == _ON)
extern bit UserInterfaceTypeCPortControllerReconnect(BYTE ucInputPort);
extern EnumTypeCUserPortCtrlFailureType UserInterfaceTypeCGetPinCfgType(BYTE ucInputPort, EnumTypeCPinCfgType *penumPinCfgtype);
#endif // End of #if(_USB_HUB_USERDECITION_SUPPORT == _ON)

#if(_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON)
extern EnumTypeCEmbPdoReference UserInterfaceTypeCPdoReference(BYTE ucInputPort);
extern WORD UserInterfaceTypeCGetMaxPower(BYTE ucInputPort);
extern EnumTypeCPdoNumber UserInterfaceTypeCGetPdoCount(BYTE ucInputPort);
extern void UserInterfaceTypeCGetPdoInfo(BYTE ucInputPort, BYTE ucPdoIndex, StructTypeCUserSrcPDO *pstTypeCUserPdo);
#if(_TYPE_C_EMB_VBUS_PROTECT_MODE == _VBUS_PROTECT_BY_USER)
extern void UserInterfaceTypeCGetProtectInfo(BYTE ucInputPort, BYTE ucPdoIndex, StructTypeCUserProtectInfo *pstTypeCUserProtectInfo);
#endif
#if(_DP_USB_HUB_SUPPORT == _ON)
extern EnumHubInputPort UserInterfaceTypeCHubInputPort(BYTE ucInputPort);
#endif
#endif // End of #if(_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON)

#if((_PORT_CONTROLLER_RTS5400_SERIES_SUPPORT == _ON) || (_PORT_CONTROLLER_USERDECITION_SUPPORT == _ON))
#if(_TWO_CHIP_DATA_EXCHANGE_MODE == _DATA_EXCHANGE_MODE_NONE)
extern EnumTypeCPortCtrlReconnectStatus UserInterfaceTypeCPortControllerGetPowerOnReconnectStatus(EnumPowerAction enumSwitch);
#endif
#endif

#endif // End of #if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
#endif // End of #ifndef __USER_TYPECINTERFACE__

#endif//#if(_OSD_TYPE == _REALTEK_2014_OSD)

