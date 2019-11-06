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
// ID Code      : UserCommonInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#define __USER_COMMON_INTERFACE__

#include "UserCommonHDRInterface.h"
#include "UserCommonLocalDimmingInterface.h"
#include "UserCommonSeamlessChgInterface.h"
#include "UserCommonDataExchangeInterface.h"

// alant
//--------------------------
#include "uart.h"
//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)

#define UserCommonNVRamSaveSystemData()                 UserCommonEepromSaveSystemData()
#define UserCommonNVRamRestoreSystemData()              UserCommonEepromRestoreSystemData()

#if(_VGA_SUPPORT == _ON)
#define UserCommonNVRamLoadADCSetting(x)                UserCommonEepromLoadADCSetting(x)
#endif

#else

#define UserCommonNVRamSaveSystemData()                 UserCommonFlashSaveSystemData()
#define UserCommonNVRamRestoreSystemData()              UserCommonFlashRestoreSystemData()

#if(_VGA_SUPPORT == _ON)
#define UserCommonNVRamLoadADCSetting(x)                UserCommonFlashLoadADCSetting(x)
#endif

#endif

//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************
//----------------------------------------------------------------------------------------
// Extern functions from UserCommonAdjust.c
//----------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------
// Extern functions from UserCommonDdcciFunction.c
//----------------------------------------------------------------------------------------
extern void UserCommonDdcciHandler(void);

#if(_CODE_DIGITAL_SIGNATURE_SUPPORT != _SIGNATURE_TYPE_OFF)
#if(_CODE_DIGITAL_SIGNATURE_SUPPORT == _SIGNATURE_TYPE_EXTERNAL)
extern void UserCommonSignExterMoveKey(void);
#endif

#if((_CODE_DIGITAL_SIGNATURE_SUPPORT == _SIGNATURE_TYPE_INTERNAL) && (_FLASH_PARTITION_TYPE == _FLASH_PARTITION_BOOT))
extern void UserCommonSignHandler(void);
extern BYTE UserCommonSignGetSwitchUserBank(void);
#endif

#if((_CODE_DIGITAL_SIGNATURE_SUPPORT == _SIGNATURE_TYPE_INTERNAL) && (_FLASH_PARTITION_TYPE == _FLASH_PARTITION_USER))
extern void UserCommonSignInterMoveKey(void);
#endif
#endif

//----------------------------------------------------------------------------------------
// Extern functions from UserCommonInterface.c
//----------------------------------------------------------------------------------------
extern bit UserCommonInterfaceGetDisplaySettingBacklightAction(void);
extern void UserCommonInterfacePanelPowerAction(BYTE ucEvent);
#if(_TRANSLATOR_SUPPORT == _OFF)
extern void UserCommonInterfaceAdjustColorProc(void);
#endif
extern void UserCommonInterfaceOsdActiveProc(void);
extern void UserCommonInterfaceOsdResetProc(void);
#if(_FRC_SUPPORT == _ON)
extern void UserCommonInterfaceGetDVMaxMinFreq(StructDVCustomizedFreq *pstDVCustomizedFreq);
#endif
#if(_OVERSCAN_SUPPORT == _ON)
extern void UserCommonAdjustOverScan(void);
#endif

#if(_TRANSLATOR_SUPPORT == _OFF)
extern void UserCommonInterfaceAdjustInputTiming(void);
extern void UserCommonInterfaceAdjustDisplayTiming(void);
extern bit UserCommonInterfaceReadyForActive(void);
#endif

#if(_VGA_SUPPORT == _ON)
extern void UserCommonInterfaceAdjustADCData(void);

#if(_YPBPR_SUPPORT == _ON)
extern bit UserCommonInterfaceCheckHDTVMode(BYTE ucModeNumber);
#endif

#endif

extern bit UserCommonInterfaceCheckResolutionNoSupport(void);
extern bit UserCommonInterfaceCheckNoSupport(void);
extern bit UserCommonInterfaceCheckFakeSaving(void);

#if((_FREESYNC_SUPPORT == _ON) && (_TRANSLATOR_SUPPORT == _OFF))
extern void UserCommonInterfaceFreeSyncSupportSwitch(void);
#endif

#if(_DDCCI_CODE_REDUCTION == _OFF)
#if(_DEBUG_MESSAGE_SUPPORT == _OFF)
extern void UserCommonInterfaceDdcciIntGetData_EXINT1(void);
#endif
#endif

#if(_SYSTEM_LOW_POWER_IDLE_SUPPORT == _ON)
extern bit UserCommonInterfaceGetRunDdcciCommand(void);
#endif

extern void UserCommonInterfaceOsdPowerOnInitial(void);

#if(_WRITE_EDID_TO_SYSTEM_EEPROM == _ON)
extern void UserCommonInterfaceNVRamRestoreEDID(void);
#endif

#if(_EMBEDDED_EDID_SUPPORT == _ON)
extern void UserCommonInterfaceLoadEmbeddedEdidData(void);
#endif

#if((_FLASH_WRITE_FUNCTION_SUPPORT == _ON) && (_HW_PC99_SUPPORT == _ON))
extern void UserCommonInterfacePC99EDIDWriteCommandData(void);
#endif

#if(_HDMI_MULTI_EDID_SUPPORT == _ON)
extern void UserCommonInterfaceHDMIMultiEdidInitial(void);
#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)
extern void UserCommonInterfaceGetHDCPKeyBKsv(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray);
extern void UserCommonInterfaceGetHDCPKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);

#if(_HDCP_2_2_SUPPORT == _ON)
extern void UserCommonInterfaceGetHdcp2Certrx(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonInterfaceGetHdcp2RSADkey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonInterfaceGetHdcp2RSARRModN(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonInterfaceGetHdcp2RSAKPriv(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonInterfaceGetHdcp2RSANpinv(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonInterfaceGetHdcp2LCKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#if((_DP_HDCP_2_2_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
extern void UserCommonInterfaceGetDpTxHdcp2RRMODN(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonInterfaceGetDpTxHdcp2DcpLlcN(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonInterfaceGetDpTxHdcp2EKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonInterfaceGetDpTxHdcp2NPinv(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#endif
#if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)
extern void UserCommonInterfaceGetHdcp2KpubKm(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#endif
#endif

#if(_DP_TX_SUPPORT == _ON)
extern void UserCommonInterfaceGetTxHDCPKeyAKsv(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray);
extern void UserCommonInterfaceGetTxHDCPKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#endif

#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
extern void UserCommonInterfaceNVRamRestoreHDCP(void);
#endif

#if(_DP_SUPPORT == _ON)
extern void UserCommonInterfaceDpAuxSet(void);
#endif
#endif // End of #if(_DIGITAL_PORT_SUPPORT == _ON)

extern void UserCommonInterfaceOsdHandler(void);
extern void UserCommonInterfaceInitial(void);

#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
#if(_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
#endif // End of #if(_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)

extern void UserCommonInterfaceTypeCPinAssignSuccessProc(BYTE ucInputPort, EnumTypeCPinCfgType enumPinAssignment);
#if(_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON)
extern EnumTypeCEmbPdoReference UserCommonInterfaceTypeCPdoReference(BYTE ucInputPort);
extern WORD UserCommonInterfaceTypeCGetMaxPower(BYTE ucInputPort);
extern EnumTypeCPdoNumber UserCommonInterfaceTypeCGetPdoCount(BYTE ucInputPort);
extern void UserCommonInterfaceTypeCGetPdoInfo(BYTE ucInputPort, BYTE ucPdoIndex, StructTypeCUserSrcPDO *pstTypeCUserPdo);
#if(_TYPE_C_EMB_VBUS_PROTECT_MODE == _VBUS_PROTECT_BY_USER)
extern void UserCommonInterfaceTypeCGetProtectInfo(BYTE ucInputPort, BYTE ucPdoIndex, StructTypeCUserProtectInfo *pstTypeCUserProtectInfo);
#endif // End of #if(_TYPE_C_EMB_VBUS_PROTECT_MODE == _VBUS_PROTECT_BY_USER)
#endif // End of #if(_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON)
#endif // End of #if((_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) || (_DP_TYPE_C_CONNECTOR_SUPPORT == _ON))

//----------------------------------------------------------------------------------------
// Extern functions from UserCommonNVRamSystem.c
//----------------------------------------------------------------------------------------
extern BYTE UserCommonNVRamGetSystemData(EnumSystemDataItemDataType enumDataType);
extern void UserCommonNVRamSetSystemData(EnumSystemDataItemDataType enumDataType, BYTE ucValue);

#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
extern void UserCommonEepromSaveSystemData(void);
#else
extern void UserCommonFlashSaveSystemData(void);
#endif

#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
extern void UserCommonEepromRestoreSystemData(void);
#else
extern void UserCommonFlashRestoreSystemData(void);
#endif

#if((_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF) && (_VGA_SUPPORT == _ON))
extern void UserCommonEepromLoadADCSetting(EnumColorSpace enumColorFormat);
#else
extern void UserCommonFlashLoadADCSetting(EnumColorSpace enumColorFormat);
#endif

//----------------------------------------------------------------------------------------
// Extern functions from UserModeSearch.c
//----------------------------------------------------------------------------------------
#if (_VGA_SUPPORT == _ON)
extern BYTE UserCommonModeSearchModeVGA(void);
extern BYTE UserCommonModeSearchGetModeVideoType(BYTE ucIndex);
#endif

//----------------------------------------------------------------------------------------
// Extern functions from UserInterface.c
//----------------------------------------------------------------------------------------
extern void UserInterfaceTimerEventProc(EnumScalerTimerEventID enumEventID);

//-------------------------------------------------------
// for RTD Tool IIC Debug
//-------------------------------------------------------
#if(_DEBUG_IIC_BY_USERINTERFACE == _ON)
extern bit UserInterfaceDebugIIC(BYTE ucType, BYTE *pucDdcciArray, BYTE *pucReturnValue);
#endif

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

#if(_DDCCI_CODE_REDUCTION == _OFF)
#if(_DEBUG_MESSAGE_SUPPORT == _OFF)
extern BYTE UserInterfaceGetFactoryCommand_EXINT1(void);
extern BYTE UserCommonInterfaceGetDdcciStatus_EXINT1(void);
#endif
#endif

//-------------------------------------------------------
// EDID & HDCP
//-------------------------------------------------------
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
extern void UserInterfaceAdjustWaitPanelT1(void);
extern void UserInterfaceAdjustWaitPanelT2(void);
extern void UserInterfaceAdjustWaitPanelT3(void);
extern void UserInterfaceAdjustWaitPanelT4(void);
extern void UserInterfaceAdjustWaitPanelT5(void);

//-------------------------------------------------------
//
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
extern EnumUserForceFakePowerOff UserInterfaceGetFakePowerOffStatus(void);
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

//-------------------------------------------------------
// Display Timing
//-------------------------------------------------------
extern void UserInterfaceDisplayInitialization(void);
extern void UserInterfaceAdjustInputTiming(void);

#if(_UNDERSCAN_SUPPORT == _ON)
extern bit UserInterfaceAdjustUnderScan(void);
#endif

extern void UserInterfaceAdjustDisplayTiming(void);

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
#endif

#if(_DCR_SUPPORT == _ON)
extern void UserInterfaceAdjustDCRHandler(void);
#endif

#if(_DCC_HISTOGRM_INFO == _ON)
extern void UserInterfaceDCCHistogramHandler(void);
#endif

#if(_IAPS_SUPPORT == _ON)
extern void UserInterfaceAdjustIAPSHandler(void);
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

#if(_VGA_FORCE_DISPLAY == _ON)
extern BYTE UserInterfaceModeSearchModeVGA(void);
#endif

#endif

#if(_MHL_SUPPORT == _ON)
extern bit UserInterfaceAdjustMHLMscRCPProc(BYTE ucKeyCode);
#endif

extern EnumFreeSyncSupport UserInterfaceGetFreeSyncEnable(EnumSourceSearchPort enumSourcePort);

#if(_HDR10_SUPPORT == _ON)
extern EnumHDR10ModeDef UserInterfaceHDRGetHDR10ModeStatus(EnumSourceSearchPort enumSourcePort);
#endif

#if(_DP_SUPPORT == _ON)
extern EnumDpVersionType UserInterfaceGetDPVersion(BYTE ucInputPort);
extern EnumDpLaneCount UserInterfaceGetDpLaneCount(BYTE ucInputPort);
extern EnumDPMSTPort UserInterfaceGetDpMSTCapablePort(void);

#if((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
extern bit UserInterfaceGetDpCloneOutputStatus(void);
#endif

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) || (_DP_EMBEDDED_SWITCH_SUPPORT_TYPE == _DP_EMBEDDED_SWITCH_2_DP))
extern BYTE UserInterfaceGetDpSwitchSelectPort(void);
#endif

#if(_DP_EMBEDDED_SWITCH_SUPPORT_TYPE == _DP_EMBEDDED_SWITCH_2_DP)
extern void UserInterfaceEmbeddedDpSwitch(void);
#endif

#endif // End of #if(_DP_SUPPORT == _ON)

#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
extern bit UserInterfaceGetHdmi5VStatus(BYTE ucInputPort);
#endif

#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_EIZO_STYLE)
extern bit UserInterfaceAdjustOsdCheckTotalSearchFinish(void);
extern void UserInterfaceAdjustSourceSearchTime(void);
extern WORD UserInterfaceGetEizoSearchFinishTime(void);
#endif

#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
extern BYTE UserInterfaceGetHpSourceSwitchOsdEventTime(BYTE ucSourceScanType);
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
extern bit UserInterfaceGetAudioDACKeepDepopState(void);
#endif

#if(_SLEEP_AUDIO_SUPPORT == _ON)
extern bit UserInterfaceGetAudioStandAloneStatus(void);
#endif

extern void UserInterfaceAdjustAudioResetProc(void);
extern void UserInterfaceAdjustAudioPowerProc(EnumPowerStatus enumPowStatus);
extern void UserInterfaceAdjustAudioAmpMuteProc(bit bMute);

#if((_LINE_IN_SUPPORT == _ON) && (_HW_AUDIO_LINE_IN_TO_DIGITAL_LR_SWAP == _ON))
extern void UserInterfaceSwapExternalAudioCodecInput(bit bSwap);
#endif
#endif // End of #if(_AUDIO_SUPPORT == _ON)

#if((_OGC_SUPPORT == _ON) || (_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON) || (_UNIFORMITY_SUPPORT == _ON))
extern void UserInterfaceAdjustBeforeDisplayCalibration(EnumCaliType enumMode);
extern void UserInterfaceAdjustAfterDisplayCalibration(EnumCaliType enumMode);
#endif

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
extern EnumAIOModernStandbyMode UserInterfaceGetAIOModernStandbyMode(void);
#endif

#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
//----------------------------------------------------------------------------------------
// Extern functions from UserCommonPortControllerEmbedded.c
//----------------------------------------------------------------------------------------
#if(_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON)
#if(_USB3_RETIMER_SUPPORT == _ON)
extern EnumUSBPDSupportStatus UserCommonPortControllerGetUsbPDStatus(void);
extern EnumUSBPSSupportStatus UserCommonPortControllerGetUsbPSStatus(void);
#endif
#if(_DP_USB_HUB_SUPPORT == _ON)
extern EnumHubInputPort UserCommonPortControllerGetHubInputPort(BYTE ucInputPort);
#endif
#endif

//----------------------------------------------------------------------------------------
// Extern functions from UserCommonPortControllerCommon.c
//----------------------------------------------------------------------------------------
extern EnumTypeCAttachStatus UserCommonPortControllerGetCcAttach(BYTE ucInputPort);
extern EnumTypeCAltModeStatus UserCommonPortControllerGetAltModeReady(BYTE ucInputPort);
extern bit UserCommonPortControllerUpdateConfig(BYTE ucInputPort, EnumTypeCMultiFuncStatus enumMultiFunc, EnumTypeCPinCfgCapType enumPinAssignmentCap);

#if(_D0_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
extern void UserCommonPortControllerSetD0I2CDetection(void);
extern void UserCommonPortControllerRestartD0I2CDetection(WORD usTime);
#endif

#if(_D1_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
extern void UserCommonPortControllerSetD1I2CDetection(void);
extern void UserCommonPortControllerRestartD1I2CDetection(WORD usTime);
#endif

#if(_D6_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
extern void UserCommonPortControllerSetD6I2CDetection(void);
extern void UserCommonPortControllerRestartD6I2CDetection(WORD usTime);
#endif

extern void UserCommonPortControllerPinMappingSetting(BYTE ucInputPort, BYTE ucPinAssignType);

#if((_PORT_CONTROLLER_RTS5400_SERIES_SUPPORT == _ON) || (_PORT_CONTROLLER_USERDECITION_SUPPORT == _ON))
extern EnumTypeCPortCtrlReconnectStatus UserCommonPortControllerGetPowerOnReconnectStatus(EnumPowerAction enumSwitch);
#endif

//----------------------------------------------------------------------------------------
// Extern functions from UserCommonPortControllerRts5400.c/UserCommonPortControllerUser.c
//----------------------------------------------------------------------------------------
#if(_PORT_CONTROLLER_RTS5400_SERIES_SUPPORT == _ON)
extern bit UserCommonPortControllerGet5400InfoByI2C(BYTE ucInputPort, Enum5400InfoType enum5400InfoType, BYTE *pucReadInfo);
extern bit UserCommonPortControllerGet5400PinAssignment(BYTE ucInputPort, EnumTypeCPinCfgType *penumPinAssignment);
extern bit UserCommonPortController5400Reconnect(BYTE ucInputPort);
extern bit UserCommonPortControllerEnable5400VenderCommand(BYTE ucInputPort);
#endif

#if(_PORT_CONTROLLER_USERDECITION_SUPPORT == _ON)
extern bit UserCommonPortControllerGetUserPinAssignment(BYTE ucInputPort, EnumTypeCPinCfgType *penumPinAssignment);
extern bit UserCommonPortControllerUserReconnect(BYTE ucInputPort);
#endif

//----------------------------------------------------------------------------------------
// Extern functions from UserCommonUsbHub.c
//----------------------------------------------------------------------------------------
#if(_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
extern bit UserCommonUsbHubSetSSMode(BYTE ucInputPort, bit bEn);
extern EnumHubDspDetectStatus UserCommonUsbHubDetectDFPStatus(BYTE ucInputPort);
extern WORD UserCommonUsbHubSetPollingStep(BYTE ucInputPort);
#if(_BILLBOARD_HUB_SUPPORT == _ON)
extern void UserCommonUsbHubBillboardControl(BYTE ucInputPort, EnumBillboardCtrl enumAtion);
#endif
#endif  // End of #if(_BILLBOARD_HUB_SUPPORT == _ON)
#endif  // End of #if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

//----------------------------------------------------------------------------------------
// Extern functions from RTD2014UserTypecInterface.c
//----------------------------------------------------------------------------------------
#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
extern EnumTypeCU3ModeType UserInterfaceTypeCGetOsdU3ModeSelection(BYTE ucInputPort);
extern EnumTypeCPinCfgCapType UserInterfaceTypeCGetPinConfigType(BYTE ucInputPort, EnumTypeCU3ModeType enumU3ModeSel);
extern void UserInterfaceTypeCPinAssignSuccessProc(BYTE ucInputPort, EnumTypeCPinCfgType enumPinAssignment);

#if(_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
extern bit UserInterfaceTypeCHubProcSupport(BYTE ucInputPort);
extern void UserInterfaceTypeCOsdHubProc(BYTE ucInputPort);
extern WORD UserInterfaceTypeCUsbHubSetPollingStep(BYTE ucInputPort);
extern bit UserInterfaceTypeCUsbHubDetectDFPStatusUserFlow(BYTE ucInputPort);
extern bit UserInterfaceTypeCUsbHubSetSSMode(BYTE ucInputPort, bit bEn);
extern EnumHubDspDetectStatus UserInterfaceTypeCUsbHubDetectDFPStatus(BYTE ucInputPort);
#endif // End of #if(_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)

#if(_PORT_CONTROLLER_USERDECITION_SUPPORT == _ON)
extern bit UserInterfaceTypeCPortControllerReconnect(BYTE ucInputPort);
extern EnumTypeCUserPortCtrlFailureType UserInterfaceTypeCGetPinCfgType(BYTE ucInputPort, EnumTypeCPinCfgType *penumPinCfgtype);
#endif // End of #if(_PORT_CONTROLLER_USERDECITION_SUPPORT == _ON)
#endif // End of #if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

//----------------------------------------------------------------------------------------
// Extern functions from UserKey.c
//----------------------------------------------------------------------------------------
extern void UserInterfaceKeyHandler(void);

//----------------------------------------------------------------------------------------
// Extern functions from UserBoot.c
//----------------------------------------------------------------------------------------
#if((_FLASH_PARTITION_TYPE == _FLASH_PARTITION_BOOT) && (_CODE_DIGITAL_SIGNATURE_SUPPORT == _SIGNATURE_TYPE_OFF))
extern BYTE UserInterfaceGetUserCodeLocation(void);
#endif

//----------------------------------------------------------------------------------------
// Extern functions from UserCommonHDR.c
//----------------------------------------------------------------------------------------
extern void UserCommonHDRHandler(void);

//----------------------------------------------------------------------------------------
// Extern functions from UserCommonLocalDimming.c
//----------------------------------------------------------------------------------------
extern void UserCommonLocalDimmingHandler(void);

//----------------------------------------------------------------------------------------
// Extern functions from UserCommonGlobalDimming.c
//----------------------------------------------------------------------------------------
extern void UserCommonGlobalDimmingHandler(void);

//----------------------------------------------------------------------------------------
// Extern functions from UserCommonSeamlessChgHandler.c
//----------------------------------------------------------------------------------------
extern void UserCommonSeamlessChgHandler(void);
