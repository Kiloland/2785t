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
// ID Code      : UserCommonInterface.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_INTERFACE__

#include "UserCommonInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************
//--------------------------------------------------
// EDID DATA TABLE
//--------------------------------------------------
#include "./EDID/EdidTableList.h"

#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
#include "./EDID/EdidTableA0.h"
#endif

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
#include "./EDID/EdidTableD0.h"
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
#include "./EDID/EdidTableD1.h"
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
#include "./EDID/EdidTableD2.h"
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
#include "./EDID/EdidTableD3.h"
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
#include "./EDID/EdidTableD4.h"
#endif

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
#include "./EDID/EdidTableD5.h"
#endif

#if(_D6_INPUT_PORT_TYPE != _D6_NO_PORT)
#include "./EDID/EdidTableD6.h"
#endif

#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
#include "./EDID/EdidTableMhlD0.h"
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
#include "./EDID/EdidTableMhlD1.h"
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
#include "./EDID/EdidTableMhlD2.h"
#endif

#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)
#include "./EDID/EdidTableMhlD3.h"
#endif

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
#include "./EDID/EdidTableMhlD4.h"
#endif

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
#include "./EDID/EdidTableMhlD5.h"
#endif

//--------------------------------------------------
// HDCP KEY TABLE
//--------------------------------------------------
#if((_DIGITAL_PORT_SUPPORT == _ON) && ((_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON) ||\
    ((_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_CODE) || ((_HDCP_2_2_SUPPORT == _ON) && (_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_CODE)))))

#include "HdcpRxKey.h"

#if(_DP_TX_SUPPORT == _ON)
#include "HdcpTxKey.h"
#endif

#endif


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
BYTE g_ucDigitalHPosition;
BYTE g_ucDigitalVPosition;
BYTE g_ucPanelPowerInfo;
bit g_bFailSafeMode = 0;

#if(_VGA_SUPPORT == _ON)
BYTE g_ucVgaCheckCounter;
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void UserCommonInterfaceUncallFunction(void);
void UserCommonInterfaceOsdPowerOnInitial(void);
bit UserCommonInterfaceGetDisplaySettingBacklightAction(void);
void UserCommonInterfacePanelPowerAction(BYTE ucEvent);

#if(_TRANSLATOR_SUPPORT == _OFF)
void UserCommonInterfaceAdjustActiveByPassColorProc(void);
void UserCommonInterfaceAdjustColorProc(void);
#endif
void UserCommonInterfaceOsdActiveProc(void);
void UserCommonInterfaceOsdResetProc(void);
#if(_FRC_SUPPORT == _ON)
void UserCommonInterfaceGetDVMaxMinFreq(StructDVCustomizedFreq *pstDVCustomizedFreq);
#endif

#if(_TRANSLATOR_SUPPORT == _OFF)
void UserCommonInterfaceAdjustInputTiming(void);
void UserCommonInterfaceAdjustDisplayTiming(void);
bit UserCommonInterfaceReadyForActive(void);
#endif

#if(_VGA_SUPPORT == _ON)
void UserCommonInterfaceAdjustADCData(void);

#if(_YPBPR_SUPPORT == _ON)
bit UserCommonInterfaceCheckHDTVMode(BYTE ucModeNumber);
#endif
#endif

bit UserCommonInterfaceCheckResolutionNoSupport(void);
bit UserCommonInterfaceCheckNoSupport(void);
bit UserCommonInterfaceCheckFakeSaving(void);

#if((_FREESYNC_SUPPORT == _ON) && (_TRANSLATOR_SUPPORT == _OFF))
void UserCommonInterfaceFreeSyncSupportSwitch(void);
#endif

#if(_DDCCI_CODE_REDUCTION == _OFF)
#if(_DEBUG_MESSAGE_SUPPORT == _OFF)
void UserCommonInterfaceDdcciIntGetData_EXINT1(void);
BYTE UserCommonInterfaceGetDdcciStatus_EXINT1(void);

#if((_HDMI_FREESYNC_SUPPORT == _ON) && (_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE))
BYTE UserCommonInterfaceDdcciHDMIFreesyncHandle_EXINT1(void);
#endif
#endif
#endif

#if(_SYSTEM_LOW_POWER_IDLE_SUPPORT == _ON)
bit UserCommonInterfaceGetRunDdcciCommand(void);
#endif

// EDID
#if(_WRITE_EDID_TO_SYSTEM_EEPROM == _ON)
void UserCommonInterfaceNVRamRestoreEDID(void);
#endif

#if(_EMBEDDED_EDID_SUPPORT == _ON)
void UserCommonInterfaceLoadEmbeddedEdidData(void);
void UserCommonInterfaceLoadEmbeddedEdidDataByPort(EnumInputPortEdid enumInputPort);
#if(_DP_SUPPORT == _ON)
void UserCommonInterfaceDPSwitchEdid(BYTE ucSelectedPort);
#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_HDR10_SUPPORT == _ON))
void UserCommonInterfaceDPSwitchAllPortEdid(void);
#endif
#endif
#endif

#if((_FLASH_WRITE_FUNCTION_SUPPORT == _ON) && (_HW_PC99_SUPPORT == _ON))
void UserCommonInterfacePC99EDIDWriteCommandData(void);
#endif

#if(_HDMI_MULTI_EDID_SUPPORT == _ON)
void UserCommonInterfaceHDMISwitchEdid(BYTE ucInputport, EnumEdidSelection enumHDMIEDIDSelection);
#if((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI_HDR10_SUPPORT == _ON))
void UserCommonInterfaceHDMISwitchAllPortEdid(void);
#endif
EnumHdmiEdidLocation UserCommonInterfaceHDMIGetMultiEdidLocated(BYTE ucInputport, EnumEdidSelection enumHDMIEDIDSelection);
BYTE UserCommonInterfaceGetHdmiEdidCount(BYTE ucInputport);
#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_WRITE_EDID_LOCATION_BY_USER_SUPPORT == _ON))
void UserCommonInterfaceHDMIReloadEdid(BYTE ucInputport);
#endif
void UserCommonInterfaceHDMIBeforeReloadEdid(BYTE ucInputport, EnumEdidSelection enumHDMIEDIDSelection);
void UserCommonInterfaceHDMIAfterReloadEdid(BYTE ucInputport, EnumEdidSelection enumHDMIEDIDSelection);
void UserCommonInterfaceHDMIMultiEdidInitial(void);
void UserCommonInterfaceHDMISwitchMultiEeprom(BYTE ucInputPort, EnumEdidSelection enumHDMIEDIDSelection);
#endif

// HDCP
#if(_DIGITAL_PORT_SUPPORT == _ON)
void UserCommonInterfaceGetHDCPKeyBKsv(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray);
void UserCommonInterfaceGetHDCPKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);

#if(_HDCP_2_2_SUPPORT == _ON)
void UserCommonInterfaceGetHdcp2Certrx(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
void UserCommonInterfaceGetHdcp2RSADkey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
void UserCommonInterfaceGetHdcp2RSARRModN(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)
void UserCommonInterfaceGetHdcp2KpubKm(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#endif
void UserCommonInterfaceGetHdcp2RSAKPriv(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
void UserCommonInterfaceGetHdcp2RSANpinv(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
void UserCommonInterfaceGetHdcp2LCKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#if((_DP_HDCP_2_2_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
void UserCommonInterfaceGetDpTxHdcp2RRMODN(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
void UserCommonInterfaceGetDpTxHdcp2DcpLlcN(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
void UserCommonInterfaceGetDpTxHdcp2EKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
void UserCommonInterfaceGetDpTxHdcp2NPinv(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#endif
#endif

#if(_DP_TX_SUPPORT == _ON)
void UserCommonInterfaceGetTxHDCPKeyAKsv(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray);
void UserCommonInterfaceGetTxHDCPKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#endif

#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
void UserCommonInterfaceNVRamRestoreHDCP(void);
#endif

#if(_DP_SUPPORT == _ON)
void UserCommonInterfaceDpAuxSet(void);
void UserCommonInterfaceDpVersionSwitch(BYTE ucInputPort, EnumDpVersionType enumDpVersion, EnumDPMSTPort enumDpRxMstPort);
#endif

#endif // End of #if(_DIGITAL_PORT_SUPPORT == _ON)

#if(_DP_TX_BLOCK_CONTROL_BEFORE_STREAM_OUTPUT == _ON)
void UserCommonInterfaceCloneModeSwitch(bit bClone);
#endif

void UserCommonInterfaceOsdHandler(void);
void UserCommonInterfaceInitial(void);

#if(_RGB_QUANTIZATION_RANGE_SUPPORT == _ON)
bit UserCommonInterfaceGetRGBQuantizationLimitRangeStatus(EnumColorRGBQuantization enumColorRGBQuantization);
#endif

#if(_TRANSLATOR_SUPPORT == _OFF)
EnumColorSpace UserCommonInterfaceGetColorFormat(void);
#endif

#if(_DP_MST_SUPPORT == _ON)
void UserCommonInterfaceMstRx0Rx1switch(EnumDPMSTPort enumMstCapablePort);
#endif

#if((_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) || (_DP_TYPE_C_CONNECTOR_SUPPORT == _ON))
void UserCommonInterfaceTypeCSetCapabilityChangeFlag(BYTE ucInputPort);
#endif // End of #if((_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) || (_DP_TYPE_C_CONNECTOR_SUPPORT == _ON))

#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
void UserCommonInterfaceTypeCPinAssignSuccessProc(BYTE ucInputPort, EnumTypeCPinCfgType enumPinAssignment);
#if(_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON)
EnumTypeCEmbPdoReference UserCommonInterfaceTypeCPdoReference(BYTE ucInputPort);
WORD UserCommonInterfaceTypeCGetMaxPower(BYTE ucInputPort);
EnumTypeCPdoNumber UserCommonInterfaceTypeCGetPdoCount(BYTE ucInputPort);
void UserCommonInterfaceTypeCGetPdoInfo(BYTE ucInputPort, BYTE ucPdoIndex, StructTypeCUserSrcPDO *pstTypeCUserPdo);
#if(_TYPE_C_EMB_VBUS_PROTECT_MODE == _VBUS_PROTECT_BY_USER)
void UserCommonInterfaceTypeCGetProtectInfo(BYTE ucInputPort, BYTE ucPdoIndex, StructTypeCUserProtectInfo *pstTypeCUserProtectInfo);
#endif // End of #if(_TYPE_C_EMB_VBUS_PROTECT_MODE == _VBUS_PROTECT_BY_USER)
#endif // End of #if(_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON)
#endif // End of #if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)

void UserCommonInterfaceDdcciSwitch(EnumDDCCIDebugMode enumMode, BYTE ucInputPort);

#if(_TWO_CHIP_DATA_EXCHANGE_MODE != _DATA_EXCHANGE_MODE_NONE)
void UserCommonInterfaceDataExchangeAllDataReset(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Uncall Function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonInterfaceUncallFunction(void)
{
    bit bUncall = _FALSE;

    if(bUncall == _TRUE)
    {
        SysStartUpCheck();

        UserCommonAdjust10bitPanelCompensate(0);

        ScalerSyncSetDdcForceNack(_D2_INPUT_PORT, _OFF);

        ScalerSyncGetDdcForceNackStatus(_D2_INPUT_PORT);

#if(_HDMI_MULTI_EDID_SUPPORT == _ON)
        UserCommonInterfaceHDMISwitchEdid(_D2_INPUT_PORT, _EDID_INDEX_0);
#if((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI_HDR10_SUPPORT == _ON))
        UserCommonInterfaceHDMISwitchAllPortEdid();
#endif
#endif

#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_DP_SUPPORT == _ON))
        UserCommonInterfaceDPSwitchEdid(_D0_INPUT_PORT);
#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_HDR10_SUPPORT == _ON))
        UserCommonInterfaceDPSwitchAllPortEdid();
#endif
#endif

#if(_FLASH_WRITE_FUNCTION_SUPPORT == _ON)
#if(_HW_PC99_SUPPORT == _ON)
        UserCommonInterfacePC99EDIDWriteCommandData();
#endif
        UserCommonFlashErasePage(0x00, 0x00);
        UserCommonFlashWrite(0x00, 0x00, 1, &pData[0]);
#endif

#if(_FLASH_PARTITION_TYPE == _FLASH_PARTITION_USER)
        SysMainStartUserCode(0);
#endif

        SysModeSetResetTarget(_MODE_ACTION_NONE);
        SysSourceSwitchInputPort(UserCommonNVRamGetSystemData(_SEARCH_PORT));
        SysSourceSetScanType(UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE));
        SysSourceGetCableDetect(UserCommonNVRamGetSystemData(_SEARCH_PORT));

        ScalerTimerSearchActiveTimerEvent(0);
        UserCommonInterfaceGetDisplaySettingBacklightAction();

#if(_HDMI_SUPPORT == _ON)
        ScalerTMDSHdmiGetAVIInfo(UserCommonNVRamGetSystemData(_SEARCH_PORT), _AVI_INFO_COLOR_SPACE);
#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)
        ScalerSyncHdcpCheckEnabled(UserCommonNVRamGetSystemData(_SEARCH_PORT));
        ScalerSyncDigitalGetColorimetryChanged(_D0_INPUT_PORT);
        ScalerSyncDigitalGetColorimetryExtChanged(_D0_INPUT_PORT);
        ScalerSyncDigitalGetQuantizationChanged(_D0_INPUT_PORT);
        ScalerSyncDigitalClrColorimetryChanged(_D0_INPUT_PORT);
        ScalerSyncDigitalClrColorimetryExtChanged(_D0_INPUT_PORT);
        ScalerSyncDigitalClrQuantizationChanged(_D0_INPUT_PORT);
#endif

#if(_VGA_SUPPORT == _ON)
        ScalerSyncProcGetSyncPad();
#endif

        UserCommonAdjustRealValueToPercent(0, 0, 0, 0);
        UserCommonAdjustPercentToRealValue(0, 0, 0, 0);

#if(_AUDIO_SUPPORT == _ON)
        ScalerAudioSamplingFreqDetect(_D0_INPUT_PORT);
#endif

#if(_DP_SUPPORT == _ON)
        ScalerDpVersionSwitch(_D0_INPUT_PORT, _DP_VERSION_1_1, _DP_MST_NO_PORT);
        ScalerDpLaneCountSwitch(_D0_INPUT_PORT, _DP_LINK_4_LANE);
        ScalerDpEdidSwitch(_D0_INPUT_PORT);
        ScalerDpGetPowerStatus(_D0_INPUT_PORT);
        ScalerDpGetLaneCount(_D0_INPUT_PORT);
        ScalerDpGetLinkRate(_D0_INPUT_PORT);
        ScalerDpGetLaneVoltageSwingLv(_D0_INPUT_PORT, _DP_LANE_0);
        ScalerDpGetLanePreEmpLv(_D0_INPUT_PORT, _DP_LANE_0);
        ScalerDpGetSrcMstEnable(_D0_INPUT_PORT);
        UserCommonInterfaceDpVersionSwitch(_D0_INPUT_PORT, _DP_VERSION_1_1, _DP_MST_NO_PORT);

#if(_DP_MST_SUPPORT == _ON)
        UserCommonInterfaceMstRx0Rx1switch(_DP_MST_NO_PORT);
#endif

#endif

#if(_DP_TX_SUPPORT == _ON)
        ScalerDpTxGetDownstreamHPDStatus();
#endif

#if(_FREESYNC_SUPPORT == _ON)
        UserCommonInterfaceFreeSyncSupportSwitch();
#endif

        UserCommonInterfaceDdcciSwitch(_DDCCI_MODE, _D0_INPUT_PORT);

        SysSourceGetSourceType();

#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_WRITE_EDID_LOCATION_BY_USER_SUPPORT == _ON))
        UserInterfaceGetEmbeddedEDIDData(_A0_INPUT_PORT_EDID);
#endif

#if(_TRANSLATOR_SUPPORT == _OFF)
        ScalerDDomainPatternGenEnable(_DISABLE);
        ScalerDDomainPatternGenAdjustColor(0x00, 0x00, 0x00);

#if(_AUDIO_SUPPORT == _ON)
        UserInterfaceGetAudioMuteStatus();
#endif

#if(_OD_SUPPORT == _ON)
        ScalerODGetStatus();
        ScalerODGetDeltaGain();
        ScalerODGetSupportStatus();
#endif

#if(_FRC_SUPPORT == _OFF)
        ScalerGlobalGetDBStatus();
#endif

#if(((_DDR3_PHASE_CALIBRATION == _ON) && (_MEMORY_PHASE_CALIBRATION_MODE == _MEMORY_PHASE_CALIBRATION_FRC_MODE)) && (_DDR3_PHASE_CHECK == _ON))
        ScalerDDR3PhaseCalibrationFRCMode();
#endif

        UserCommonAdjustHPosition(0);
        UserCommonAdjustVPosition(0);

        ScalerOsdDoubleFunction(0, 0);
        ScalerOsdMapRotation(0, 0, 0, 0, 0, 0);

        UserCommonInterfaceAdjustActiveByPassColorProc();
#endif // End of #if(_TRANSLATOR_SUPPORT == _OFF)

#if(_DP_SUPPORT == _ON)
        UserCommonInterfaceDpAuxSet();
#endif

#if(_D0_TMDS_SUPPORT == _ON)
        ScalerTMDSHotPlugEvent(_D0_INPUT_PORT);
#endif

#if(_D1_TMDS_SUPPORT == _ON)
        ScalerTMDSHotPlugEvent(_D1_INPUT_PORT);
#endif

#if(_D2_TMDS_SUPPORT == _ON)
        ScalerTMDSHotPlugEvent(_D2_INPUT_PORT);
#endif

#if(_D3_TMDS_SUPPORT == _ON)
        ScalerTMDSHotPlugEvent(_D3_INPUT_PORT);
#endif

#if(_D4_TMDS_SUPPORT == _ON)
        ScalerTMDSHotPlugEvent(_D4_INPUT_PORT);
#endif

#if(_D5_TMDS_SUPPORT == _ON)
        ScalerTMDSHotPlugEvent(_D5_INPUT_PORT);
#endif

#if(_D0_HDMI_SUPPORT == _ON)
        ScalerSyncTMDSEdidSwitch(_D0_INPUT_PORT);
        ScalerSyncHDMIDdcCheckBusy(_D0_INPUT_PORT, _DELAY_30US_TIMESCALE, 1, 1500);
#endif

#if(_D1_HDMI_SUPPORT == _ON)
        ScalerSyncTMDSEdidSwitch(_D1_INPUT_PORT);
        ScalerSyncHDMIDdcCheckBusy(_D1_INPUT_PORT, _DELAY_30US_TIMESCALE, 1, 1500);
#endif

#if(_D2_HDMI_SUPPORT == _ON)
        ScalerSyncTMDSEdidSwitch(_D2_INPUT_PORT);
        ScalerSyncHDMIDdcCheckBusy(_D2_INPUT_PORT, _DELAY_30US_TIMESCALE, 1, 1500);
#endif

#if(_D3_HDMI_SUPPORT == _ON)
        ScalerSyncTMDSEdidSwitch(_D3_INPUT_PORT);
        ScalerSyncHDMIDdcCheckBusy(_D3_INPUT_PORT, _DELAY_30US_TIMESCALE, 1, 1500);
#endif

#if(_D4_HDMI_SUPPORT == _ON)
        ScalerSyncTMDSEdidSwitch(_D4_INPUT_PORT);
        ScalerSyncHDMIDdcCheckBusy(_D4_INPUT_PORT, _DELAY_30US_TIMESCALE, 1, 1500);
#endif

#if(_D5_HDMI_SUPPORT == _ON)
        ScalerSyncTMDSEdidSwitch(_D5_INPUT_PORT);
        ScalerSyncHDMIDdcCheckBusy(_D5_INPUT_PORT, _DELAY_30US_TIMESCALE, 1, 1500);
#endif

#if((_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) || (_DP_TYPE_C_CONNECTOR_SUPPORT == _ON))
        UserCommonInterfaceTypeCSetCapabilityChangeFlag(_D0_INPUT_PORT);
#endif

#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        SysTypeCGetPinAssignment(_D0_INPUT_PORT);
#if((_USB_HUB_RTS5411_SERIES_SUPPORT == _ON) && (_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON))
        UserCommonUsbHubGetDspInfo(_HUB_DSP0);
#endif

#if((_PORT_CONTROLLER_RTS5400_SERIES_SUPPORT == _ON) && (_TYPE_C_RTS5400_SERIES_PDO_INFO_SUPPORT == _ON))
        UserCommonPortControllerGet5400PDOStatus(_D0_INPUT_PORT, &pData[0], &pData[1]);
#endif

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        ScalerTypeCRx0PdGetPdoStatus(&pData[0], &pData[1]);
#endif
#endif // End of #if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_TYPE_C_PMIC_HW_IIC_SUPPORT == _ON)
        ScalerTypeCPmicIICRead(0, 0, 0, 0, pData);
#endif

#if(_HW_FLASH_ACCESS_METHOD == _XDATA_MAP_ACCESS)
        ScalerSyncVGAUseEmbeddedEDID();
        ScalerSyncVGADdcCheckBusyAndForceNack();
#endif

#if(_EFUSE_SUPPORT == _ON)
        ScalerEfuseGetData(_EFUSE_NONE, 1, &pData[0]);
#endif

#if(_HW_IIC_SUPPORT == _ON)
        ScalerMcuHwIICConfigSetting(_HW_IIC_SPEED);
#endif

        UserInterfaceGetFreeSyncEnable(_D0_INPUT_PORT);

#if(_FREESYNC_II_SUPPORT == _ON)
        UserCommonHDRGetFreesynIIStatus();
        UserCommonHDRGetFreeSyncIILDDisable();
        UserCommonHDRGetFreeSyncIIEOTFType();
#endif

#if(_RGB_QUANTIZATION_RANGE_SUPPORT == _ON)
        UserCommonInterfaceGetRGBQuantizationLimitRangeStatus(_RGB_QUANTIZATION_FULL_RANGE);
#endif

#if(_TRANSLATOR_SUPPORT == _ON)
#if(_FREESYNC_SUPPORT == _ON)
        ScalerFreeSyncGetFreeSyncInfo(_D0_INPUT_PORT, _SPD_INFO_FREESYNC_ENABLE);
#endif
#endif

#if(_TWO_CHIP_DATA_EXCHANGE_MODE != _DATA_EXCHANGE_MODE_NONE)
        UserCommonDataExchangeReadReply(pData, 0);
        UserCommonInterfaceDataExchangeAllDataReset();
        UserCommonDataExchangeSendData(pData, 0);
        UserCommonDataExchangeGetData(_DATA_EXCHAGNE_CMD_NONE, pData, 0);
        UserCommonDataExchangeInit();
#endif

#if(_GLOBAL_DIMMING_SUPPORT == _ON)
        UserCommonGlobalDimmingEnable(_DISABLE);
#endif

#if(_FLASH_READ_FUNCTION_SUPPORT == _ON)
        UserCommonFlashRead(0x00, 0x00, 1, pData);
#endif

#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _ON)
        UserCommonEepromIICRead(0x00, 0x0000, 4, 16, pData, 0, 0);
        UserCommonEepromIICWrite(0x00, 0x0000, 4, 16, pData, 0, 0, 16);
#endif

#if(_SOURCE_BACKGROUND_DETECT_SUPPORT == _ON)
        SysSourceBgGetInputPort();
        SysSourceBgGetJudge();
#endif
    }
}

//--------------------------------------------------
// Description  : User initial LUT/Latch/SRAM tabled ata
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonInterfaceOsdPowerOnInitial(void)
{
    // User Power On Initial
    UserInterfaceAdjustOsdPowerOnInitial();

#if((_DCR_SUPPORT == _ON) || (_IAPS_SUPPORT == _ON))
    ScalerColorDCRSetSource();
#endif

    // Adjust DCC Histogram Settings
#if(_DCC_HISTOGRM_INFO == _ON)
    ScalerColorDCCHistoSetting();
#endif

    // Adjust IAPSGain Histogram Settings
#if(_IAPS_SUPPORT == _ON)
#if(_IAPS_GAIN_COMPENSATION_TYPE == _IAPS_GAIN_COMPENSATION_GEN_0)
// DCC Manual mode Initial
#elif(_IAPS_GAIN_COMPENSATION_TYPE == _IAPS_GAIN_COMPENSATION_GEN_1)
    ScalerColorIAPSGainSoftClampAdjust(_IAPS_GAIN_CLAMP_FACTOR);
    ScalerColorIAPSGainValueAdjust(_IAPS_CONTRAST_TARGET);
#endif
#endif

#if(_HDR10_LIGHT_ENHANCE_SUPPORT == _ON)
    ScalerColorIAPSGainSoftClampAdjust(_IAPS_GAIN_CLAMP_FACTOR);
    ScalerColorIAPSGainValueAdjust(_IAPS_CONTRAST_TARGET);
#endif

    // Adjust D Dither Table
#if(_D_DITHER_SUPPORT == _ON)
    UserCommonAdjustDDither();
#endif

#if(_SCALING_DOWN_TYPE == _SD_GEN_1)
    ScalerScalingSetScalingDownCoef();
#endif

#if((_ULTRA_VIVID_SUPPORT == _ON) && (_ULTRA_VIVID_TABLE_TYPE == _ULTRA_VIVID_GEN_3))
    ScalerColorUltraVividInitial();
#endif
}

//--------------------------------------------------
// Description  : Get backlight staus when performing display setting
// Input Value  : None
// Output Value : _ENABLE or _DISABLE
//--------------------------------------------------
bit UserCommonInterfaceGetDisplaySettingBacklightAction(void)
{
#if(_PANEL_STYLE == _PANEL_VBO)

#if(_VBO_BACKLIGHT_BY_USER == _ENABLE)
    return UserInterfaceGetDisplaySettingBacklightAction();
#else
    return _DISABLE;
#endif

#else

    return UserInterfaceGetDisplaySettingBacklightAction();

#endif
}

//--------------------------------------------------
// Description  : Power Power On/Off Sequence
// Input Value  : ucEvent --> _PANEL_ON
//                            _PANEL_OFF
//                            _BACKLIGHT_ON
//                            _BACKLIGHT_OFF
// Output Value : None
//--------------------------------------------------
void UserCommonInterfacePanelPowerAction(BYTE ucEvent)
{
#if(_PANEL_POWER_SEQUENCE_CONTROL_BY_USER == _ON)

    UserInterfacePanelPowerAction(ucEvent);

#else

    switch(ucEvent)
    {
        case _PANEL_ON:

            if(GET_PANELPOWERSTATUS() == _PANEL_POWER_OFF_STATE)
            {
                // Check T6
                ScalerTimerWaitForActiveTimerEvent(_USER_TIMER_EVENT_PANEL_POWER_OFF);

                // LCD Power on
                PCB_PANEL_POWER(_PANEL_CONTROL_ON);

                UserInterfaceAdjustWaitPanelT1();

#if(_PANEL_STYLE == _PANEL_DPTX)
                // Panel DPTx Power Sequence Check Point
                ScalerDisplayDPTxPowerSequenceProc(_DPTX_POWER_SEQUENCE_PANEL_ON);

                // Set Dptx PHY
                ScalerDisplayDPTxPhyInitial();

                UserInterfaceAdjustWaitPanelT2();

                if(ScalerDisplayDPTxLinkSequence() == _FAIL)
                {
#if(_PANEL_DPTX_FORCE_OUTPUT_SUPPORT == _ON)
                    ScalerDisplayDPTxLinkSignalForceOutput();
#endif
                }
#endif
            }

            if(GET_PANELPOWERSTATUS() != _BACKLIGHT_ON_ALREADY)
            {
#if(_PANEL_STYLE == _PANEL_LVDS)

                // LVDS Power On
                ScalerDisplayLvdsPower(_ON);

                UserInterfaceAdjustWaitPanelT2();

                // LVDS PLL(Data) On
                ScalerDisplayLvdsPLL(_ON);

                // Wait Event for Backlight On
                ScalerTimerActiveTimerEvent(_PANEL_POWER_ON_T3, _USER_TIMER_EVENT_PANEL_BACKLIGHT_ON);

                SET_PANELPOWERSTATUS(_WAITING_FOR_BACKLIGHT);

#elif(_PANEL_STYLE == _PANEL_TTL)

                UserInterfaceAdjustWaitPanelT2();

                // TTL Power On
                ScalerDisplayTtlPower(_ON);

                // Wait Event for Backlight On
                ScalerTimerActiveTimerEvent(_PANEL_POWER_ON_T3, _USER_TIMER_EVENT_PANEL_BACKLIGHT_ON);

                SET_PANELPOWERSTATUS(_WAITING_FOR_BACKLIGHT);

#elif(_PANEL_STYLE == _PANEL_VBO)

                // Set Vby1 PHY
                ScalerDisplayVboAnalogPhyConrol(_ENABLE);

                // Set HTPDN control by H/W
                ScalerDisplayVboHtpdnSetFwControl(_DISABLE);

                UserInterfaceAdjustWaitPanelT2();

                ScalerDisplayVboHtpdnHandler();

                // Set Panel Fast Off Enable
                ScalerDisplayVboPanelSetFastOff(_ENABLE);

                // Wait Event for Backlight On
                ScalerTimerActiveTimerEvent(_PANEL_POWER_ON_T3, _USER_TIMER_EVENT_PANEL_BACKLIGHT_ON);

                SET_PANELPOWERSTATUS(_WAITING_FOR_BACKLIGHT);

#elif(_PANEL_STYLE == _PANEL_DPTX)

                ScalerDisplayDPTxStreamHanlder(_ENABLE);

                // Panel DPTx Power Sequence Check Point
                ScalerDisplayDPTxPowerSequenceProc(_DPTX_POWER_SEQUENCE_PANEL_ON);

                // Wait Event for Backlight On
                ScalerTimerActiveTimerEvent(_PANEL_POWER_ON_T3, _USER_TIMER_EVENT_PANEL_BACKLIGHT_ON);

                SET_PANELPOWERSTATUS(_WAITING_FOR_BACKLIGHT);

#endif  // #if(_PANEL_STYLE == _PANEL_LVDS)
            }

            break;

        case _PANEL_OFF:

            if(GET_PANELPOWERSTATUS() != _PANEL_POWER_OFF_STATE)
            {
#if(_PANEL_STYLE == _PANEL_LVDS)

                PCB_BACKLIGHT_POWER(_LIGHT_CONTROL_OFF);

                UserInterfaceAdjustWaitPanelT4();

                ScalerDisplayLvdsPLL(_OFF);

                ScalerDisplayLvdsPower(_OFF);

                UserInterfaceAdjustWaitPanelT5();

#elif(_PANEL_STYLE == _PANEL_TTL)

                PCB_BACKLIGHT_POWER(_LIGHT_CONTROL_OFF);

                UserInterfaceAdjustWaitPanelT4();

                ScalerDisplayTtlPower(_OFF);

                UserInterfaceAdjustWaitPanelT5();

#elif(_PANEL_STYLE == _PANEL_VBO)

                PCB_BACKLIGHT_POWER(_LIGHT_CONTROL_OFF);

                // HTDPN fail before CDR lock, or CDR fail during ALN training, then set panel fast off
                if(ScalerDisplayVboPanelFastOffCheck() != _ENABLE)
                {
                    UserInterfaceAdjustWaitPanelT4();
                }

                // Force disable video output
                ScalerDisplayVboForceVideoOutput(_DISABLE);

                // Vby1 Phy Disable
                ScalerDisplayVboAnalogPhyConrol(_DISABLE);

                // Set HTPDN control by F/W, pull high
                ScalerDisplayVboHtpdnSetFwControl(_ENABLE);

                UserInterfaceAdjustWaitPanelT5();

#elif(_PANEL_STYLE == _PANEL_DPTX)

                PCB_BACKLIGHT_POWER(_LIGHT_CONTROL_OFF);

                // Panel DPTx Power Sequence Check Point
                ScalerDisplayDPTxPowerSequenceProc(_DPTX_POWER_SEQUENCE_BACKLIGHT_OFF);

                UserInterfaceAdjustWaitPanelT4();

                // Set IDLE Pattern
                ScalerDisplayDPTxStreamHanlder(_DISABLE);

                // Panel DPTx Power Sequence Check Point
                ScalerDisplayDPTxPowerSequenceProc(_DPTX_POWER_SEQUENCE_IDLE_PATTERN);

                UserInterfaceAdjustWaitPanelT5();

                // Disable DPTx Spread Spectrum
                ScalerDisplayDPTxSSCSet(_DISABLE);

                ScalerDisplayDPTxAnalogPhyConrol(_DISABLE);

#endif // #if(_PANEL_STYLE == _PANEL_LVDS)

                PCB_PANEL_POWER(_PANEL_CONTROL_OFF);

                ScalerTimerActiveTimerEvent(_PANEL_POWER_OFF_T6, _USER_TIMER_EVENT_PANEL_POWER_OFF);

                SET_PANELPOWERSTATUS(_PANEL_POWER_OFF_STATE);

                ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_PANEL_BACKLIGHT_ON);
            }

            break;

        case _BACKLIGHT_ON:

            if(GET_PANELPOWERSTATUS() == _PANEL_POWER_OFF_STATE)
            {
                // Check T6
                ScalerTimerWaitForActiveTimerEvent(_USER_TIMER_EVENT_PANEL_POWER_OFF);

                // LCD Power on
                PCB_PANEL_POWER(_PANEL_CONTROL_ON);

                UserInterfaceAdjustWaitPanelT1();

#if(_PANEL_STYLE == _PANEL_LVDS)

                // LVDS Power On
                ScalerDisplayLvdsPower(_ON);

                UserInterfaceAdjustWaitPanelT2();

                // LVDS PLL(Data) On
                ScalerDisplayLvdsPLL(_ON);

                // Wait Delay for Backlight On
                UserInterfaceAdjustWaitPanelT3();

                PCB_BACKLIGHT_POWER(_LIGHT_CONTROL_ON);

                SET_PANELPOWERSTATUS(_BACKLIGHT_ON_ALREADY);

#elif(_PANEL_STYLE == _PANEL_TTL)

                UserInterfaceAdjustWaitPanelT2();

                // TTL Power On
                ScalerDisplayTtlPower(_ON);

                // Wait Delay for Backlight On
                UserInterfaceAdjustWaitPanelT3();

                PCB_BACKLIGHT_POWER(_LIGHT_CONTROL_ON);

                SET_PANELPOWERSTATUS(_BACKLIGHT_ON_ALREADY);

#elif(_PANEL_STYLE == _PANEL_VBO)

                // Set Vby1 PHY
                ScalerDisplayVboAnalogPhyConrol(_ENABLE);

                // Set HTPDN control by H/W
                ScalerDisplayVboHtpdnSetFwControl(_DISABLE);

                UserInterfaceAdjustWaitPanelT2();

                ScalerDisplayVboHtpdnHandler();

                UserInterfaceAdjustWaitPanelT3();

                ScalerDisplayVboLocknHandler();

                PCB_BACKLIGHT_POWER(_LIGHT_CONTROL_ON);

                SET_PANELPOWERSTATUS(_BACKLIGHT_ON_ALREADY);

                // Set Panel Fast Off Disable
                ScalerDisplayVboPanelSetFastOff(_DISABLE);

#elif(_PANEL_STYLE == _PANEL_DPTX)

                // Panel DPTx Power Sequence Check Point
                ScalerDisplayDPTxPowerSequenceProc(_DPTX_POWER_SEQUENCE_PANEL_ON);

                // Set Dptx PHY
                ScalerDisplayDPTxPhyInitial();

                UserInterfaceAdjustWaitPanelT2();

                if(ScalerDisplayDPTxLinkSequence() == _FAIL)
                {
#if(_PANEL_DPTX_FORCE_OUTPUT_SUPPORT == _ON)
                    ScalerDisplayDPTxLinkSignalForceOutput();
#endif
                }

                // Set Video Stream parameter
                ScalerDisplayDPTxStreamHanlder(_ENABLE);

                // Panel DPTx Power Sequence Check Point
                ScalerDisplayDPTxPowerSequenceProc(_DPTX_POWER_SEQUENCE_VIDEO_PATTERN);

                // Wait Delay for Backlight On
                UserInterfaceAdjustWaitPanelT3();

                PCB_BACKLIGHT_POWER(_LIGHT_CONTROL_ON);

                // Panel DPTx Power Sequence Check Point
                ScalerDisplayDPTxPowerSequenceProc(_DPTX_POWER_SEQUENCE_BACKLIGHT_ON);

                SET_PANELPOWERSTATUS(_BACKLIGHT_ON_ALREADY);

#endif // #if(_PANEL_STYLE == _PANEL_LVDS)
            }
            else if(GET_PANELPOWERSTATUS() == _PANEL_BACKLIGHT_OFF)
            {
#if(_PANEL_STYLE == _PANEL_LVDS)

                // LVDS PLL(Data) On
                ScalerDisplayLvdsPLL(_ON);

#elif(_PANEL_STYLE == _PANEL_TTL)

                // TTL Power On
                ScalerDisplayTtlPower(_ON);

#elif(_PANEL_STYLE == _PANEL_DPTX)

                ScalerDisplayDPTxStreamHanlder(_ENABLE);

#endif // #if(_PANEL_STYLE == _PANEL_LVDS)

                // Wait Delay for Backlight On
                UserInterfaceAdjustWaitPanelT3();

                PCB_BACKLIGHT_POWER(_LIGHT_CONTROL_ON);

                SET_PANELPOWERSTATUS(_BACKLIGHT_ON_ALREADY);
            }
            else
            {
                ScalerTimerWaitForActiveTimerEvent(_USER_TIMER_EVENT_PANEL_BACKLIGHT_ON);

#if(_PANEL_STYLE == _PANEL_LVDS)

                PCB_BACKLIGHT_POWER(_LIGHT_CONTROL_ON);

                SET_PANELPOWERSTATUS(_BACKLIGHT_ON_ALREADY);

#elif(_PANEL_STYLE == _PANEL_TTL)

                PCB_BACKLIGHT_POWER(_LIGHT_CONTROL_ON);

                SET_PANELPOWERSTATUS(_BACKLIGHT_ON_ALREADY);

#elif(_PANEL_STYLE == _PANEL_VBO)

                ScalerDisplayVboLocknHandler();

                PCB_BACKLIGHT_POWER(_LIGHT_CONTROL_ON);

                SET_PANELPOWERSTATUS(_BACKLIGHT_ON_ALREADY);

                // Set Panel Fast Off Disable
                ScalerDisplayVboPanelSetFastOff(_DISABLE);

#elif(_PANEL_STYLE == _PANEL_DPTX)

                PCB_BACKLIGHT_POWER(_LIGHT_CONTROL_ON);

                // Panel DPTx Power Sequence Check Point
                ScalerDisplayDPTxPowerSequenceProc(_DPTX_POWER_SEQUENCE_BACKLIGHT_ON);

                SET_PANELPOWERSTATUS(_BACKLIGHT_ON_ALREADY);

#endif // #if(_PANEL_STYLE == _PANEL_LVDS)
            }

            break;

        case _BACKLIGHT_OFF:

            if((GET_PANELPOWERSTATUS() != _PANEL_POWER_OFF_STATE) &&
               (GET_PANELPOWERSTATUS() != _PANEL_BACKLIGHT_OFF))
            {
                PCB_BACKLIGHT_POWER(_LIGHT_CONTROL_OFF);

#if(_PANEL_STYLE == _PANEL_LVDS)

                UserInterfaceAdjustWaitPanelT4();

                ScalerDisplayLvdsPLL(_OFF);

#elif(_PANEL_STYLE == _PANEL_TTL)

                UserInterfaceAdjustWaitPanelT4();

                ScalerDisplayTtlPower(_OFF);

#elif(_PANEL_STYLE == _PANEL_DPTX)

                UserInterfaceAdjustWaitPanelT4();

                ScalerDisplayDPTxStreamHanlder(_DISABLE);

#endif // #if(_PANEL_STYLE == _PANEL_LVDS)

                SET_PANELPOWERSTATUS(_PANEL_BACKLIGHT_OFF);
            }

            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_PANEL_BACKLIGHT_ON);

            break;

        default:

            break;
    }
#endif
}

#if(_TRANSLATOR_SUPPORT == _OFF)
//--------------------------------------------------
// Description  : Set color in bypass normal active process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonInterfaceAdjustActiveByPassColorProc(void)
{
#if(_OD_SUPPORT == _ON)
    ScalerODEnable(UserInterfaceGetODEnableStatus());
#endif

#if(_SHARPNESS_SUPPORT == _ON)
    UserCommonAdjustSharpness(SysSourceGetInputPort());
#endif

#if(_ULTRA_VIVID_SUPPORT == _ON)
    UserInterfaceAdjustUltraVividProc(_DB_APPLY_NO_POLLING);
#endif

#if(_LOCAL_DIMMING_SUPPORT == _ON)
#if((_ASPECT_RATIO_SUPPORT == _ON) || (_ASPECT_ORIGINAL_MODE_SUPPORT == _ON))
    if(UserInterfaceGetLocalDimmingStatus() == _LD_ENABLE)
    {
        UserCommonLocalDimmingAspectRatioAdjust();
    }
#endif
#endif

    UserInterfaceAdjustActiveByPassColorProc();
}

//--------------------------------------------------
// Description  : Set User Required Color Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonInterfaceAdjustColorProc(void)
{
#if(_COLOR_PROCESS_CONTROL_BY_USER == _ON)

    UserInterfaceAdjustColorProc();

#else

#if(_COLORIMETRY_SEAMLESS_CHANGE_SUPPORT == _ON)
    UserCommonSeamlessChgAdjust(_SEAMLESS_BACKUP_SETTING);
#endif

    if(UserInterfaceGetActiveByPassStatus() == _TRUE)
    {
        UserCommonInterfaceAdjustActiveByPassColorProc();

        return;
    }

    if(ScalerTimerWaitForEvent(_EVENT_DEN_STOP) == _FALSE)
    {
        return;
    }

#if(_RGB_QUANTIZATION_RANGE_SUPPORT == _ON)
    UserCommonAdjustRGBQuantizationRange();
#endif

#if(_YCC_QUANTIZATION_RANGE_SUPPORT == _ON)
    if(UserInterfaceGetYCCQuantizationFullRangeStatus(ScalerColorGetYCCQuantizationRange()) == _TRUE)
    {
        ScalerColorSetYCCFullRange(_TRUE);
    }
    else
    {
        ScalerColorSetYCCFullRange(_FALSE);
    }
#endif

#if(_COLOR_IP_COLOR_CONVERT == _ON)
#if((_COLOR_CONVERSION_TYPE == _COLOR_CONVERSION_GEN_0) || (_COLOR_CONVERSION_TYPE == _COLOR_CONVERSION_GEN_1) || (_COLOR_CONVERSION_TYPE == _COLOR_CONVERSION_GEN_2))
    ScalerColorSpaceConvertLoadTable();
#endif
#endif

#if(_COLOR_IP_DCR == _ON)
    // Enable DCR
    ScalerColorDCREnable(_FUNCTION_ON);
#endif

    // Adjust Digital Filter
#if(_VGA_SUPPORT == _ON)
    if(SysSourceGetSourceType() == _SOURCE_VGA)
    {
#if(_DIGITAL_FILTER_SUPPORT == _ON)
        ScalerColorDigitalFilterAdjust();
        ScalerColorDigitalFilterEnable(_FUNCTION_ON);
#endif

#if(_RINGING_FILTER_SUPPORT == _ON)
        UserCommonAdjustRingingFilter();
#endif

#if(_DIG_FILTER_ENHANCE_PHASE_ENABLE == _ENABLE)
        UserCommonAdjustDigitalFilterEnhancePhase();
#endif
    }
    else
    {
#if(_RINGING_FILTER_SUPPORT == _ON)
        ScalerColorRingingFilterOff();
#endif

        ScalerColorDigitalFilterEnable(_FUNCTION_OFF);
    }
#endif  // End of #if(_VGA_SUPPORT == _ON)

    // Color Sampling
    ScalerColor422To444();



    UserInterfaceAdjustColorProc();

#if(_SHARPNESS_SUPPORT == _OFF)
    ScalerScalingSetScalingUpCoef();
#endif

    // Adjust Normalize Factor, should after HLW setting
#if(_DCC_FUNCTION == _ON)
    ScalerColorDCCNormalizeFactorAdjust();
#endif

    // Adjust IAPSGain
#if(_IAPS_SUPPORT == _ON)
#if(_IAPS_GAIN_COMPENSATION_TYPE == _IAPS_GAIN_COMPENSATION_GEN_0)
    ScalerColorDCCEnable(_FUNCTION_ON);
#elif(_IAPS_GAIN_COMPENSATION_TYPE == _IAPS_GAIN_COMPENSATION_GEN_1)
    ScalerColorIAPSGainEnable(_FUNCTION_ON);
#endif
#endif

#if(_HDR10_LIGHT_ENHANCE_SUPPORT == _ON)
    ScalerColorIAPSGainEnable(_FUNCTION_ON);
#endif

#if(_GLOBAL_HUE_SATURATION == _ON)
    ScalerColorSRGBEnable(_FUNCTION_ON);
#endif

#if(_I_DITHER_SUPPORT == _ON)
    // Adjust I Dithering
    UserCommonAdjustIDither();

    ScalerColorIDitherEnable(_FUNCTION_ON);
#endif

#if(_D_DITHER_SUPPORT == _ON)
#if(_D_DITHER_FREERUNEN_SUPPORT == _DISABLE)
    ScalerColorDDitherEnable(_FUNCTION_ON);
#endif
#endif // End of #if(_D_DITHER_SUPPORT == _ON)

#if(_ULTRA_HDR_SUPPORT == _ON)
    UserCommonHDRAdjust(_HDR_FLOW_COLOR_PROC_INITIAL);
#endif

#if(_LOCAL_DIMMING_SUPPORT == _ON)
    if(UserInterfaceGetLocalDimmingStatus() == _LD_ENABLE)
    {
        UserCommonLocalDimmingInitialSetting(_ENABLE);

        if(UserCommonLocalDimmingGetEnableStatus() == _LD_ENABLE)
        {
            ScalerColorPanelUniformityEnable(_FUNCTION_ON);
            SET_LD_ACTION_MODE_STATUS(_LD_ACTION_MODE_DIMMING);
        }
        else
        {
            SET_LD_ACTION_MODE_STATUS(_LD_ACTION_MODE_NORNAL);
        }
    }
    else
    {
        UserCommonLocalDimmingInitialSetting(_DISABLE);
        SET_LD_ACTION_MODE_STATUS(_LD_ACTION_MODE_NORNAL);
    }
#endif

#if((_LOCAL_DIMMING_SUPPORT == _ON) && (_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_III))
    // D domain DB be effective
    if(ScalerGlobalGetDDomainDBStatus() == _ENABLE)
    {
        ScalerColorDDomainDBApply(_DB_APPLY_POLLING);
    }
#endif

#if(_GLOBAL_DIMMING_SUPPORT == _ON)
    if(UserCommonGlobalDimmingGetEnableStatus() == _GD_ENABLE)
    {
        UserCommonGlobalDimmingInitialSetting(_ENABLE);
    }
#endif
#endif
}
#endif

//--------------------------------------------------
// Description  : OSD Fix Active Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonInterfaceOsdActiveProc(void)
{
#if(_VGA_SUPPORT == _ON)
    if(SysSourceGetSourceType() == _SOURCE_VGA)
    {
        UserCommonAdjustHPosition(GET_VGA_MODE_ADJUST_H_POSITION());
        UserCommonAdjustVPosition(GET_VGA_MODE_ADJUST_V_POSITION());
        UserCommonAdjustClock(GET_VGA_MODE_ADJUST_CLOCK());
        UserCommonAdjustPhase(GET_VGA_MODE_ADJUST_PHASE());
    }
#endif

#if(_FRC_SUPPORT == _ON)
    ScalerFRCWaitWriteFrameBufFinish();
#endif

    UserInterfaceAdjustOsdActiveProc();
}

//--------------------------------------------------
// Description  : OSD Fix Reset Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonInterfaceOsdResetProc(void)
{
    // Turn off backlight
    if(UserInterfaceGetLogoStatus() == _OFF)
    {
#if(_PANEL_POW_SEQ_FAST_MODE == _ON)
        UserCommonInterfacePanelPowerAction(_BACKLIGHT_OFF);
#else
        UserCommonInterfacePanelPowerAction(_PANEL_OFF);
#endif
    }

#if(_AUDIO_SUPPORT == _ON)
    UserInterfaceAdjustAudioResetProc();
#endif

    UserInterfaceAdjustOsdResetProc();

#if(_VGA_SUPPORT == _ON)
    g_ucVgaCheckCounter = 30;
#endif

// Turn Off Color Functions
#if((_GAMMA_FUNCTION == _ON) || (_PCM_FUNCTION == _ON))
    ScalerColorOutputGammaEnable(_FUNCTION_OFF);
#endif

#if(_RGB_GAMMA_FUNCTION == _ON)
    ScalerColorRGBOutputGammaInitial();
    ScalerColorRGBOutputGammaEnable(_FUNCTION_OFF);
#endif

#if((_GLOBAL_HUE_SATURATION == _ON) || (_PCM_FUNCTION == _ON))
    ScalerColorSRGBEnable(_FUNCTION_OFF);
#endif

#if(_PCM_FUNCTION == _ON)
    ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);
#endif

#if(_RGB_3D_GAMMA == _ON)
    ScalerColorRGB3DGammaEnable(_FUNCTION_OFF);
#endif

#if(_ICM_SUPPORT == _ON)
    ScalerColorICMEnable(_FUNCTION_OFF);
#endif

#if(_COLOR_IP_DCC == _ON)
    ScalerColorDCCEnable(_FUNCTION_OFF);
#endif

#if(_YPEAKING_SUPPORT == _ON)
    ScalerColorYpeaking(_OFF);
#endif

#if(_VGA_SUPPORT == _ON)
    ScalerColorDigitalFilterEnable(_FUNCTION_OFF);

#if(_RINGING_FILTER_SUPPORT == _ON)
    ScalerColorRingingFilterOff();
#endif

#endif

#if(_COLOR_IP_DCR == _ON)
    ScalerColorDCREnable(_FUNCTION_OFF);
#endif

#if(_IAPS_SUPPORT == _ON)
#if(_IAPS_GAIN_COMPENSATION_TYPE == _IAPS_GAIN_COMPENSATION_GEN_1)
    ScalerColorIAPSGainEnable(_FUNCTION_OFF);
#endif
#endif

#if(_HDR10_LIGHT_ENHANCE_SUPPORT == _ON)
    ScalerColorIAPSGainEnable(_FUNCTION_OFF);
#endif

#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
    ScalerColorHLWEnable(_FUNCTION_OFF, _DB_APPLY_NO_POLLING);
#endif

#if(_BRIGHTNESS_SUPPORT == _ON)
    ScalerColorBrightnessEnable(_FUNCTION_OFF);
#endif

#if(_CONTRAST_SUPPORT == _ON)
    ScalerColorContrastEnable(_FUNCTION_OFF);
#endif

#if(_I_DITHER_SUPPORT == _ON)
    ScalerColorIDitherEnable(_FUNCTION_OFF);
#endif

#if(_D_DITHER_SUPPORT == _ON)
#if(_D_DITHER_FREERUNEN_SUPPORT == _DISABLE)
    ScalerColorDDitherEnable(_FUNCTION_OFF);
#endif
#endif

#if(_ULTRA_VIVID_SUPPORT == _ON)
    ScalerColorUltraVividEnable(_FUNCTION_OFF, _DB_APPLY_POLLING);
#endif

#if(_COLOR_IP_COLOR_CONVERT == _ON)
    ScalerColorSpaceConvertIDomainEnable(_OFF);
    ScalerColorSpaceConvertDDomainEnable(_OFF);
#endif

#if(_UNIFORMITY_SUPPORT == _ON)
    ScalerColorPanelUniformityEnable(_FUNCTION_OFF);
#endif

#if(_LOCAL_DIMMING_SUPPORT == _ON)
    UserCommonLocalDimmingInitialSetting(_DISABLE);
#endif

#if(_GLOBAL_DIMMING_SUPPORT == _ON)
    UserCommonGlobalDimmingInitialSetting(_DISABLE);
#endif
}

#if(_FRC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Adjust Max/Min Freq according to latency
// Input Value  : None
// Output Value : MaxMin Freq
//--------------------------------------------------
void UserCommonInterfaceGetDVMaxMinFreq(StructDVCustomizedFreq *pstDVCustomizedFreq)
{
    pstDVCustomizedFreq->b1FORCETOFREERUN = _DISABLE;
    pstDVCustomizedFreq->usMaxFreq = _PANEL_MAX_FRAME_RATE;
    pstDVCustomizedFreq->usTypFreq = _PANEL_TYP_FRAME_RATE;
    pstDVCustomizedFreq->usMinFreq = _PANEL_MIN_FRAME_RATE;

    UserInterfaceGetDVMaxMinFreq(pstDVCustomizedFreq);

#if(_FORCE_TO_FREE_RUN_SUPPORT == _ON)
    pstDVCustomizedFreq->b1FORCETOFREERUN = _ENABLE;
#endif
}
#endif

#if(_TRANSLATOR_SUPPORT == _OFF)
//--------------------------------------------------
// Description  : Modify Input Timing Based on User Requirement
// Input Value  : Current Input Timing Info
// Output Value : Modified Input Timing
//--------------------------------------------------
void UserCommonInterfaceAdjustInputTiming(void)
{
    UserInterfaceAdjustInputTiming();

#if(_UNDERSCAN_SUPPORT == _ON)
    UserCommonAdjustUnderScan();
#endif

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
    UserCommonAdjustRotationInputSize();
#endif

#if(_OVERSCAN_SUPPORT == _ON)
    UserCommonAdjustOverScan();
#endif
}

//--------------------------------------------------
// Description  : Modify Display Timing Based on User Requirement
// Input Value  : Display region
// Output Value : None
//--------------------------------------------------
void UserCommonInterfaceAdjustDisplayTiming(void)
{
#if(_ASPECT_RATIO_SUPPORT == _ON)
    UserCommonAdjustAspectRatio();
#endif

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
    UserCommonAdjustRotationDisplaySize();
#endif

    UserInterfaceAdjustDisplayTiming();
}

//--------------------------------------------------
// Description  : User Judge Ready to Active
// Input Value  : None
// Output Value : True --> Ready to Active
//                False --> Not Ready to Active
//--------------------------------------------------
bit UserCommonInterfaceReadyForActive(void)
{
#if(_PANEL_POW_SEQ_FAST_MODE == _ON)
    if((GET_PANELPOWERSTATUS() != _READY_FOR_BACKLIGHT) && (GET_PANELPOWERSTATUS() != _BACKLIGHT_ON_ALREADY))
    {
        return _FALSE;
    }
#endif

#if(_VGA_SUPPORT == _ON)
    if(SysSourceGetSourceType() == _SOURCE_VGA)
    {
        if(UserInterfaceGetFirstAutoConfigStatus() == _TRUE)
        {
            if((g_ucVgaCheckCounter > 0) && (UserCommonAutoMeasureMultiTimes() == _FALSE))
            {
                g_ucVgaCheckCounter--;

                return _FALSE;
            }
        }
    }
#endif

    return _TRUE;
}
#endif

#if(_VGA_SUPPORT == _ON)
//--------------------------------------------------
// Description  : ADC Parameters Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonInterfaceAdjustADCData(void)
{
    // Adjust Gain
    ScalerADCGainAdjust(g_stAdcData.pucAdcGainMSB, g_stAdcData.pucAdcGainLSB);

    // Adjust Offset
    ScalerADCOffsetAdjust(g_stAdcData.pucAdcOffsetMSB, g_stAdcData.pucAdcOffsetLSB);
}

#if(_YPBPR_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get color rimetry
// Input Value  : ucModeNumber --> Target Mode Number
// Output Value : _TRUE --> current mode is HD TV Mode
//--------------------------------------------------
bit UserCommonInterfaceCheckHDTVMode(BYTE ucModeNumber)
{
    switch(ucModeNumber)
    {
        case _MODE_720x480p_60HZ:
        case _MODE_1440x480i_60HZ:
        case _MODE_720x576p_50HZ:
        case _MODE_1440x576i_50HZ:

            return _FALSE;

        case _MODE_1280x720p_60HZ:
        case _MODE_1920x1080i_50HZ:
        case _MODE_1920x1080i_60HZ:
        case _MODE_1920x1080p_50HZ:
        case _MODE_1920x1080p_60HZ:
        case _MODE_1920x1080i_50HZ_2:
        case _MODE_1280x720p_50HZ:

            return _TRUE;

        default:

            return _FALSE;
    }
}
#endif // End of #if(_YPBPR_SUPPORT == _ON)
#endif

//--------------------------------------------------
// Description  : Check Whther to support this timing
// Input Value  : None
// Output Value : TRUE => Go to No Support State
//--------------------------------------------------
bit UserCommonInterfaceCheckResolutionNoSupport(void)
{
    SET_FAIL_SAFE_MODE(_FALSE);

    if((GET_INPUT_TIMING_HWIDTH() == 0x00) || (GET_INPUT_TIMING_VHEIGHT() == 0x00))
    {
        return _TRUE;
    }

    if((GET_INPUT_TIMING_HFREQ() < _OOR_H_FREQ_LOWER_BOUND) || (GET_INPUT_TIMING_HFREQ() > _OOR_H_FREQ_UPPER_BOUND) ||
       (GET_INPUT_TIMING_VFREQ() > _OOR_V_FREQ_UPPER_BOUND) ||
       (GET_INPUT_TIMING_VHEIGHT() < _OOR_V_HEIGHT_LOWER_BOUND) || (GET_INPUT_TIMING_HWIDTH() > _OOR_H_WIDTH_UPPER_BOUND))
    {
        return _TRUE;
    }

    // Fail Save Mode
    if((GET_INPUT_TIMING_HFREQ() < _FAIL_SAVE_H_FREQ_LOWER_BOUND) || (GET_INPUT_TIMING_HFREQ() > _FAIL_SAVE_H_FREQ_UPPER_BOUND) ||
       (GET_INPUT_TIMING_VFREQ() > _FAIL_SAVE_V_FREQ_UPPER_BOUND))
    {
        SET_FAIL_SAFE_MODE(_TRUE);
    }

    if(GET_INPUT_TIMING_VFREQ() < _OOR_V_FREQ_LOWER_BOUND)
    {
        return _TRUE;
    }

    if(GET_INPUT_TIMING_VFREQ() < _FAIL_SAVE_V_FREQ_LOWER_BOUND)
    {
        SET_FAIL_SAFE_MODE(_TRUE);
    }

    return _FALSE;
}
//--------------------------------------------------
// Description  : Check Whther to support this timing
// Input Value  : None
// Output Value : TRUE => Go to No Support State
//--------------------------------------------------
bit UserCommonInterfaceCheckNoSupport(void)
{
    if(UserCommonInterfaceCheckResolutionNoSupport() == _TRUE)
    {
        return _TRUE;
    }

    switch(SysSourceGetSourceType())
    {
#if(_VGA_SUPPORT == _ON)

        case _SOURCE_VGA:

            if(ScalerSyncGetInputPixelClk() >= _INPUTCLOCK_RANG_VGA)
            {
                return _TRUE;
            }

            break;

#endif

#if(_DVI_SUPPORT == _ON)

        case _SOURCE_DVI:

            if(ScalerSyncGetInputPixelClk() >= _INPUTCLOCK_RANG_DVI)
            {
                return _TRUE;
            }

            break;
#endif

#if(_HDMI_SUPPORT == _ON)

        case _SOURCE_HDMI:

            if(ScalerSyncGetInputPixelClk() >= _INPUTCLOCK_RANG_HDMI)
            {
                return _TRUE;
            }

            if(ScalerTMDSYUV420SupportCheck(SysSourceGetInputPort()) == _FALSE)
            {
                return _TRUE;
            }

            break;

#endif

#if(_DP_SUPPORT == _ON)
        case _SOURCE_DP:

#if(_DP_DYNAMIC_ADJUST_LINK_RATE_SUPPORT == _ON)
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
            if(SysSourceGetInputPort() == _D0_INPUT_PORT)
            {
                if(ScalerSyncGetInputPixelClk() >= _INPUTCLOCK_RANG_USBC)
                {
                    return _TRUE;
                }

                break;
            }
#endif

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
            if(SysSourceGetInputPort() == _D1_INPUT_PORT)
            {
                if(ScalerSyncGetInputPixelClk() >= _INPUTCLOCK_RANG_USBC)
                {
                    return _TRUE;
                }

                break;
            }
#endif
#endif

            if(ScalerSyncGetInputPixelClk() >= _INPUTCLOCK_RANG_DP)
            {
                return _TRUE;
            }

            break;
#endif

        default:
            break;
    }

    return (UserInterfaceGetdNoSupportStatus());
}

//--------------------------------------------------
// Description  : Check Fake Saving Status
// Input Value  : None
// Output Value : _TRUE ==> POWER STATUS FAKE SAVING, _FALSE ==> POWER STATUS SAVING
//--------------------------------------------------
bit UserCommonInterfaceCheckFakeSaving(void)
{
    if(SysPowerCheckFakeSaving() == _TRUE)
    {
        return _TRUE;
    }

    return _FALSE;
}

#if((_FREESYNC_SUPPORT == _ON) && (_TRANSLATOR_SUPPORT == _OFF))
//--------------------------------------------------
// Description  : FreeSync Support Switch
// Input Value  : Check Status
// Output Value : None
//--------------------------------------------------
void UserCommonInterfaceFreeSyncSupportSwitch(void)
{
#if(((_D0_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON)) ||\
    ((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_DP_FREESYNC_SUPPORT == _ON)))
    ScalerFreeSyncSupportSwitch(_D0_INPUT_PORT, UserInterfaceGetFreeSyncEnable(_D0_INPUT_PORT));
#endif

#if(((_D1_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON)) ||\
    ((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_DP_FREESYNC_SUPPORT == _ON)))
    ScalerFreeSyncSupportSwitch(_D1_INPUT_PORT, UserInterfaceGetFreeSyncEnable(_D1_INPUT_PORT));
#endif

#if(((_D2_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON)) ||\
    ((_D2_INPUT_PORT_TYPE == _D2_DP_PORT) && (_DP_FREESYNC_SUPPORT == _ON)))
    ScalerFreeSyncSupportSwitch(_D2_INPUT_PORT, UserInterfaceGetFreeSyncEnable(_D2_INPUT_PORT));
#endif

#if((_D3_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
    ScalerFreeSyncSupportSwitch(_D3_INPUT_PORT, UserInterfaceGetFreeSyncEnable(_D3_INPUT_PORT));
#endif

#if((_D4_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
    ScalerFreeSyncSupportSwitch(_D4_INPUT_PORT, UserInterfaceGetFreeSyncEnable(_D4_INPUT_PORT));
#endif

#if((_D5_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
    ScalerFreeSyncSupportSwitch(_D5_INPUT_PORT, UserInterfaceGetFreeSyncEnable(_D5_INPUT_PORT));
#endif

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_DP_FREESYNC_SUPPORT == _ON))
    ScalerFreeSyncSupportSwitch(_D6_INPUT_PORT, UserInterfaceGetFreeSyncEnable(_D6_INPUT_PORT));
#endif

#if(_D0_TWO_CHIP_DATA_EXCHANGE_MODE != _DATA_EXCHANGE_MODE_NONE)
#if(_DP_FREESYNC_SUPPORT == _ON)
    if(UserInterfaceGetFreeSyncEnable(_D0_INPUT_PORT) == _FREESYNC_SUPPORT_ON)
    {
        g_stD0DataExchange.unionDataExchangeItem.stDpFreeSync.enumFreeSyncOnOff = _DATA_EXCHANGE_DP_FREESYNC_SUPPORT_ON;
    }
    else
    {
        g_stD0DataExchange.unionDataExchangeItem.stDpFreeSync.enumFreeSyncOnOff = _DATA_EXCHANGE_DP_FREESYNC_SUPPORT_OFF;
    }

    SET_DATA_EXCHANGE_EVENT_MESSAGE(_DATA_EXCHAGNE_CMD_DP_FREESYNC_STATUS);
#endif
#endif
}
#endif

#if(_DDCCI_CODE_REDUCTION == _OFF)
#if(_DEBUG_MESSAGE_SUPPORT == _OFF)
//--------------------------------------------------
// Description  : Get DDC-CI Data in Interrupt Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonInterfaceDdcciIntGetData_EXINT1(void) using 2
{
    BYTE ucTemp = 0;

    // Clear Unused DDCCI IRQ Flag
    SET_DDCCI_STATUS2(GET_DDCCI_STATUS2() & ~(_BIT5 | _BIT4));

    if(GET_RUN_DDCCI_COMMAND() == _SUCCESS)
    {
        // Clear Flags
        if((GET_DDCCI_STATUS1() & _BIT1) == _BIT1)
        {
            CLR_DDCCI_STATUS1(_BIT1);
        }

        if((GET_DDCCI_STATUS1() & _BIT2) == _BIT2)
        {
            ucTemp = GET_DDCCI_DATA_IN();
        }
    }
    else
    {
        SET_RUN_DDCCI_COMMAND_SRC(_DDCCI_CMD_SRC_I2C);

        if(GET_DDCCI_SLAVE_ADDRESS() == _DDCCI_DEST_ADDRESS)
        {
            SET_RUN_DDCCI_COMMAND((bit)ScalerMcuDdcciIntGetData_EXINT1(g_pucDdcciRxBuf));

#if((_HDMI_FREESYNC_SUPPORT == _ON) && (_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE))
            if(GET_RUN_DDCCI_COMMAND() == _SUCCESS)
            {
                if(UserCommonInterfaceDdcciHDMIFreesyncHandle_EXINT1() == _TRUE)
                {
                    SET_RUN_DDCCI_COMMAND(_FAIL);
                }
            }
#endif
        }
        else
        {
            SET_RUN_DDCCI_COMMAND((bit)UserInterfaceGetFactoryCommand_EXINT1());
        }
    }
}

//--------------------------------------------------
// Description  : Get DDC-CI Status in Interrupt Process
// Input Value  : None
// Output Value : _TURE or _False
//--------------------------------------------------
BYTE UserCommonInterfaceGetDdcciStatus_EXINT1(void) using 2
{
    if((bit)UserInterfaceGetDdcciStatus_EXINT1() == _ON)
    {
        return _TRUE;
    }

#if(_CODE_DIGITAL_SIGNATURE_SUPPORT != _SIGNATURE_TYPE_OFF)
    if((bit)ScalerDebugGetDdcciSwitchState_EXINT1() == _TRUE)
    {
        return _TRUE;
    }
#endif

    return _FALSE;
}


#if((_HDMI_FREESYNC_SUPPORT == _ON) && (_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE))
//--------------------------------------------------
// Description  : Get HDMI Freesync support
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE UserCommonInterfaceDdcciHDMIFreesyncHandle_EXINT1(void) using 2
{
    BYTE ucDdcciCount = 0;

    if(UserInterfaceDdcciHDMIFreesyncOpcode_EXINT1() == _TRUE)
    {
        if(g_pucDdcciRxBuf[_DDCCI_COMMAND] == _DDCCI_CMD_SET_VCP_FEATURE)
        {
            ScalerSyncSetHDMIFREESYNCVcp_EXINT1(g_pucDdcciRxBuf[_DDCCI_SET_HIGH_BYTE]);
        }

        if(g_pucDdcciRxBuf[_DDCCI_COMMAND] == _DDCCI_CMD_GET_VCP_FEATURE)
        {
            g_pucDdcciTxBuf[_DDCCI_SOURCE] = 0x6E;
            g_pucDdcciTxBuf[_DDCCI_LENGTH] = 0x88;
            g_pucDdcciTxBuf[_DDCCI_COMMAND] = 0x02;
            g_pucDdcciTxBuf[_DDCCI_RESULT_CODE] = 0x00;
            g_pucDdcciTxBuf[_DDCCI_SINK_OPCODE] = g_pucDdcciRxBuf[_DDCCI_SOURCE_OPCODE];
            g_pucDdcciTxBuf[_DDCCI_TYPE_CODE] = 0x00;
            g_pucDdcciTxBuf[_DDCCI_MAX_HIGH_BYTE] = 0x00;
            g_pucDdcciTxBuf[_DDCCI_MAX_LOW_BYTE] = 0x00;
            g_pucDdcciTxBuf[_DDCCI_PRESENT_HIGH_BYTE] = ScalerSyncGetHDMIFREESYNCVcp_EXINT1();
            g_pucDdcciTxBuf[_DDCCI_PRESENT_LOW_BYTE] = ScalerFreeSyncHDMIGetFreeSyncSupport_EXINT1(ScalerMcuDdcciGetInputPort_EXINT1());

            g_pucDdcciTxBuf[_DDCCI_PRESENT_LOW_BYTE + 1] = (((0xB4 ^ g_pucDdcciTxBuf[_DDCCI_SINK_OPCODE]) ^ g_pucDdcciTxBuf[_DDCCI_PRESENT_HIGH_BYTE]) ^ g_pucDdcciTxBuf[_DDCCI_PRESENT_LOW_BYTE]);

            // Enable mcu write
            MCU_FF2A_IIC_IRQ_CONTROL2 |= (_BIT6 | _BIT5);

            while(ucDdcciCount < 11)
            {
                // Load data to DDC-CI buffer
                MCU_FF26_IIC_DATA_OUT = g_pucDdcciTxBuf[ucDdcciCount++];
            }

            // Disable mcu write
            MCU_FF2A_IIC_IRQ_CONTROL2 &= ~_BIT5;

            // Clear buffer for new message
            memset(g_pucDdcciRxBuf, 0, _DDCCI_RXBUF_LENGTH);
        }

        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}
#endif

#endif
#endif

#if(_SYSTEM_LOW_POWER_IDLE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Run DDCCI command
// Input Value  : None
// Output Value : _ON => DDCCI Support ON
//--------------------------------------------------
bit UserCommonInterfaceGetRunDdcciCommand(void)
{
#if(_DDCCI_CODE_REDUCTION == _OFF)
    return GET_RUN_DDCCI_COMMAND();
#else
    return _FALSE;
#endif
}
#endif


#if(_WRITE_EDID_TO_SYSTEM_EEPROM == _ON)
//--------------------------------------------------
// Description  : Restore default EDID
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonInterfaceNVRamRestoreEDID(void)
{
    BYTE ucCount = 0;
    BYTE pucBuffer[16] = {0};

#if(_EDID_TABLE_LOCATED_IN_FLASH == _ON)
    UserCommonFlashErasePage(_EDID_FLASH_BANK, _EDID_TABLE_FLASH_PAGE);
#endif

// A0 EDID-----------------------------------------------------------------------------------------------------------
#if((_A0_INPUT_PORT_TYPE != _A0_NO_PORT) && (_A0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) && ((_A0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) || (_A0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)))
    for(ucCount = 0; ucCount < (_A0_EMBEDDED_DDCRAM_MAX_SIZE / sizeof(pucBuffer)); ucCount++)
    {
        memcpy(pucBuffer, tEDID_TABLE_A0 + ucCount * sizeof(pucBuffer), sizeof(pucBuffer));
#if(_A0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM)
        UserCommonEepromRestoreEDID(_EDID_A0_ADDRESS_EEPROM + ucCount * sizeof(pucBuffer), sizeof(pucBuffer), pucBuffer);
#elif(_A0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)
        UserCommonFlashRestoreEDID(_EDID_A0_ADDRESS_FLASH + ucCount * sizeof(pucBuffer), sizeof(pucBuffer), pucBuffer);
#endif
    }
#endif

// D0 EDID-----------------------------------------------------------------------------------------------------------
#if((_D0_INPUT_PORT_TYPE != _D0_NO_PORT) && (_D0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) && ((_D0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) || (_D0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)))
    for(ucCount = 0; ucCount < (_D0_EMBEDDED_DDCRAM_MAX_SIZE / sizeof(pucBuffer)); ucCount++)
    {
        memcpy(pucBuffer, tEDID_TABLE_D0 + ucCount * sizeof(pucBuffer), sizeof(pucBuffer));
#if(_D0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM)
        UserCommonEepromRestoreEDID(_EDID_D0_ADDRESS_EEPROM + ucCount * sizeof(pucBuffer), sizeof(pucBuffer), pucBuffer);
#elif(_D0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)
        UserCommonFlashRestoreEDID(_EDID_D0_ADDRESS_FLASH + ucCount * sizeof(pucBuffer), sizeof(pucBuffer), pucBuffer);
#endif
    }
#endif

// D1 EDID-----------------------------------------------------------------------------------------------------------
#if((_D1_INPUT_PORT_TYPE != _D1_NO_PORT) && (_D1_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) && ((_D1_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) || (_D1_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)))
    for(ucCount = 0; ucCount < (_D1_EMBEDDED_DDCRAM_MAX_SIZE / sizeof(pucBuffer)); ucCount++)
    {
        memcpy(pucBuffer, tEDID_TABLE_D1 + ucCount * sizeof(pucBuffer), sizeof(pucBuffer));
#if(_D1_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM)
        UserCommonEepromRestoreEDID(_EDID_D1_ADDRESS_EEPROM + ucCount * sizeof(pucBuffer), sizeof(pucBuffer), pucBuffer);
#elif(_D1_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)
        UserCommonFlashRestoreEDID(_EDID_D1_ADDRESS_FLASH + ucCount * sizeof(pucBuffer), sizeof(pucBuffer), pucBuffer);
#endif
    }
#endif

// D2 EDID-----------------------------------------------------------------------------------------------------------
#if((_D2_INPUT_PORT_TYPE != _D2_NO_PORT) && (_D2_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) && ((_D2_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) || (_D2_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)))
    for(ucCount = 0; ucCount < (_D2_EMBEDDED_DDCRAM_MAX_SIZE / sizeof(pucBuffer)); ucCount++)
    {
        memcpy(pucBuffer, tEDID_TABLE_D2 + ucCount * sizeof(pucBuffer), sizeof(pucBuffer));
#if(_D2_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM)
        UserCommonEepromRestoreEDID(_EDID_D2_ADDRESS_EEPROM + ucCount * sizeof(pucBuffer), sizeof(pucBuffer), pucBuffer);
#elif(_D2_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)
        UserCommonFlashRestoreEDID(_EDID_D2_ADDRESS_FLASH + ucCount * sizeof(pucBuffer), sizeof(pucBuffer), pucBuffer);
#endif
    }
#endif

// D3 EDID-----------------------------------------------------------------------------------------------------------
#if((_D3_INPUT_PORT_TYPE != _D3_NO_PORT) && (_D3_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) && ((_D3_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) || (_D3_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)))
    for(ucCount = 0; ucCount < (_D3_EMBEDDED_DDCRAM_MAX_SIZE / sizeof(pucBuffer)); ucCount++)
    {
        memcpy(pucBuffer, tEDID_TABLE_D3 + ucCount * sizeof(pucBuffer), sizeof(pucBuffer));
#if(_D3_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM)
        UserCommonEepromRestoreEDID(_EDID_D3_ADDRESS_EEPROM + ucCount * sizeof(pucBuffer), sizeof(pucBuffer), pucBuffer);
#elif(_D3_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)
        UserCommonFlashRestoreEDID(_EDID_D3_ADDRESS_FLASH + ucCount * sizeof(pucBuffer), sizeof(pucBuffer), pucBuffer);
#endif
    }
#endif

// D4 EDID-----------------------------------------------------------------------------------------------------------
#if((_D4_INPUT_PORT_TYPE == _D4_NO_PORT) && (_D4_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) && ((_D4_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) || (_D4_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)))
    for(ucCount = 0; ucCount < (_D4_EMBEDDED_DDCRAM_MAX_SIZE / sizeof(pucBuffer)); ucCount++)
    {
        memcpy(pucBuffer, tEDID_TABLE_D4 + ucCount * sizeof(pucBuffer), sizeof(pucBuffer));
#if(_D4_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM)
        UserCommonEepromRestoreEDID(_EDID_D4_ADDRESS_EEPROM + ucCount * sizeof(pucBuffer), sizeof(pucBuffer), pucBuffer);
#elif(_D4_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)
        UserCommonFlashRestoreEDID(_EDID_D4_ADDRESS_FLASH + ucCount * sizeof(pucBuffer), sizeof(pucBuffer), pucBuffer);
#endif
    }
#endif

// D5 EDID-----------------------------------------------------------------------------------------------------------
#if((_D5_INPUT_PORT_TYPE != _D5_NO_PORT) && (_D5_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) && ((_D5_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) || (_D5_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)))
    for(ucCount = 0; ucCount < (_D5_EMBEDDED_DDCRAM_MAX_SIZE / sizeof(pucBuffer)); ucCount++)
    {
        memcpy(pucBuffer, tEDID_TABLE_D5 + ucCount * sizeof(pucBuffer), sizeof(pucBuffer));
#if(_D5_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM)
        UserCommonEepromRestoreEDID(_EDID_D5_ADDRESS_EEPROM + ucCount * sizeof(pucBuffer), sizeof(pucBuffer), pucBuffer);
#elif(_D5_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)
        UserCommonFlashRestoreEDID(_EDID_D5_ADDRESS_FLASH + ucCount * sizeof(pucBuffer), sizeof(pucBuffer), pucBuffer);
#endif
    }
#endif

// D6 EDID-----------------------------------------------------------------------------------------------------------
#if((_D6_INPUT_PORT_TYPE != _D6_NO_PORT) && (_D6_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) && ((_D6_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) || (_D6_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)))
    for(ucCount = 0; ucCount < (_D6_EMBEDDED_DDCRAM_MAX_SIZE / sizeof(pucBuffer)); ucCount++)
    {
        memcpy(pucBuffer, tEDID_TABLE_D6 + ucCount * sizeof(pucBuffer), sizeof(pucBuffer));
#if(_D6_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM)
        UserCommonEepromRestoreEDID(_EDID_D6_ADDRESS_EEPROM + ucCount * sizeof(pucBuffer), sizeof(pucBuffer), pucBuffer);
#elif(_D6_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)
        UserCommonFlashRestoreEDID(_EDID_D6_ADDRESS_FLASH + ucCount * sizeof(pucBuffer), sizeof(pucBuffer), pucBuffer);
#endif
    }
#endif

// D0 MHL EDID-------------------------------------------------------------------------------------------------------
#if((_D0_INPUT_PORT_TYPE != _D0_NO_PORT) && (_D0_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && ((_D0_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) || (_D0_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)))
    for(ucCount = 0; ucCount < (_D0_MHL_EMBEDDED_DDCRAM_SIZE / sizeof(pucBuffer)); ucCount++)
    {
        memcpy(pucBuffer, tEDID_TABLE_D0_MHL + ucCount * sizeof(pucBuffer), sizeof(pucBuffer));
#if(_D0_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM)
        UserCommonEepromRestoreEDID(_EDID_D0_MHL_ADDRESS_EEPROM + ucCount * sizeof(pucBuffer), sizeof(pucBuffer), pucBuffer);
#elif(_D0_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)
        UserCommonFlashRestoreEDID(_EDID_D0_MHL_ADDRESS_FLASH + ucCount * sizeof(pucBuffer), sizeof(pucBuffer), pucBuffer);
#endif
    }
#endif

// D1 MHL EDID-------------------------------------------------------------------------------------------------------
#if((_D1_INPUT_PORT_TYPE != _D1_NO_PORT) && (_D1_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && ((_D1_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) || (_D1_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)))
    for(ucCount = 0; ucCount < (_D1_MHL_EMBEDDED_DDCRAM_SIZE / sizeof(pucBuffer)); ucCount++)
    {
        memcpy(pucBuffer, tEDID_TABLE_D1_MHL + ucCount * sizeof(pucBuffer), sizeof(pucBuffer));
#if(_D1_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM)
        UserCommonEepromRestoreEDID(_EDID_D1_MHL_ADDRESS_EEPROM + ucCount * sizeof(pucBuffer), sizeof(pucBuffer), pucBuffer);
#elif(_D1_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)
        UserCommonFlashRestoreEDID(_EDID_D1_MHL_ADDRESS_FLASH + ucCount * sizeof(pucBuffer), sizeof(pucBuffer), pucBuffer);
#endif
    }
#endif

// D2 MHL EDID-------------------------------------------------------------------------------------------------------
#if((_D2_INPUT_PORT_TYPE != _D2_NO_PORT) && (_D2_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && ((_D2_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) || (_D2_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)))
    for(ucCount = 0; ucCount < (_D2_MHL_EMBEDDED_DDCRAM_SIZE / sizeof(pucBuffer)); ucCount++)
    {
        memcpy(pucBuffer, tEDID_TABLE_D2_MHL + ucCount * sizeof(pucBuffer), sizeof(pucBuffer));
#if(_D2_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM)
        UserCommonEepromRestoreEDID(_EDID_D2_MHL_ADDRESS_EEPROM + ucCount * sizeof(pucBuffer), sizeof(pucBuffer), pucBuffer);
#elif(_D2_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)
        UserCommonFlashRestoreEDID(_EDID_D2_MHL_ADDRESS_FLASH + ucCount * sizeof(pucBuffer), sizeof(pucBuffer), pucBuffer);
#endif
    }
#endif

// D3 MHL EDID-------------------------------------------------------------------------------------------------------
#if((_D3_INPUT_PORT_TYPE != _D3_NO_PORT) && (_D3_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && ((_D3_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) || (_D3_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)))
    for(ucCount = 0; ucCount < (_D3_MHL_EMBEDDED_DDCRAM_SIZE / sizeof(pucBuffer)); ucCount++)
    {
        memcpy(pucBuffer, tEDID_TABLE_D3_MHL + ucCount * sizeof(pucBuffer), sizeof(pucBuffer));
#if(_D3_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM)
        UserCommonEepromRestoreEDID(_EDID_D3_MHL_ADDRESS_EEPROM + ucCount * sizeof(pucBuffer), sizeof(pucBuffer), pucBuffer);
#elif(_D3_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)
        UserCommonFlashRestoreEDID(_EDID_D3_MHL_ADDRESS_FLASH + ucCount * sizeof(pucBuffer), sizeof(pucBuffer), pucBuffer);
#endif
    }
#endif

// D4 MHL EDID-------------------------------------------------------------------------------------------------------
#if((_D4_INPUT_PORT_TYPE != _D4_NO_PORT) && (_D4_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && ((_D4_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) || (_D4_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)))
    for(ucCount = 0; ucCount < (_D4_MHL_EMBEDDED_DDCRAM_SIZE / sizeof(pucBuffer)); ucCount++)
    {
        memcpy(pucBuffer, tEDID_TABLE_D4_MHL + ucCount * sizeof(pucBuffer), sizeof(pucBuffer));
#if(_D4_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM)
        UserCommonEepromRestoreEDID(_EDID_D4_MHL_ADDRESS_EEPROM + ucCount * sizeof(pucBuffer), sizeof(pucBuffer), pucBuffer);
#elif(_D4_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)
        UserCommonFlashRestoreEDID(_EDID_D4_MHL_ADDRESS_FLASH + ucCount * sizeof(pucBuffer), sizeof(pucBuffer), pucBuffer);
#endif
    }
#endif

// D5 MHL EDID-------------------------------------------------------------------------------------------------------
#if((_D5_INPUT_PORT_TYPE != _D5_NO_PORT) && (_D5_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && ((_D5_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) || (_D5_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)))
    for(ucCount = 0; ucCount < (_D5_MHL_EMBEDDED_DDCRAM_SIZE / sizeof(pucBuffer)); ucCount++)
    {
        memcpy(pucBuffer, tEDID_TABLE_D5_MHL + ucCount * sizeof(pucBuffer), sizeof(pucBuffer));
#if(_D5_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM)
        UserCommonEepromRestoreEDID(_EDID_D5_MHL_ADDRESS_EEPROM + ucCount * sizeof(pucBuffer), sizeof(pucBuffer), pucBuffer);
#elif(_D5_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)
        UserCommonFlashRestoreEDID(_EDID_D5_MHL_ADDRESS_FLASH + ucCount * sizeof(pucBuffer), sizeof(pucBuffer), pucBuffer);
#endif
    }
#endif
}
#endif // End of #if(_WRITE_EDID_TO_SYSTEM_EEPROM == _ON)

#if(_EMBEDDED_EDID_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set Embedded EDID Data of AC ON
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonInterfaceLoadEmbeddedEdidData(void)
{
// A0 EDID-----------------------------------------------------------------------------------------------------------
#if((_A0_INPUT_PORT_TYPE != _A0_NO_PORT) && (_A0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))

    UserCommonInterfaceLoadEmbeddedEdidDataByPort(_A0_INPUT_PORT_EDID);

    // DDC Force Nack Off
    ScalerSyncSetDdcForceNack(_A0_INPUT_PORT, _OFF);

#endif // End of #if((_A0_INPUT_PORT_TYPE != _A0_NO_PORT) && (_A0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))

// D6 EDID-----------------------------------------------------------------------------------------------------------
#if((_D6_INPUT_PORT_TYPE != _D6_NO_PORT) && (_D6_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))

    UserCommonInterfaceLoadEmbeddedEdidDataByPort(_D6_INPUT_PORT_EDID);

#endif // End of #if((_D6_INPUT_PORT_TYPE != _D6_NO_PORT) && (_D6_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))

// D0 EDID-----------------------------------------------------------------------------------------------------------
#if((_D0_INPUT_PORT_TYPE != _D0_NO_PORT) && (_D0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))

    UserCommonInterfaceLoadEmbeddedEdidDataByPort(_D0_INPUT_PORT_EDID);

#if(_D0_HDMI_MULTI_EDID_SUPPORT == _ON)
    if(UserCommonInterfaceHDMIGetMultiEdidLocated(_D0_INPUT_PORT, UserInterfaceGetMultiHdmiEdidIndex(_D0_INPUT_PORT)) != _HDMI_EDID_EXTERNAL)
#endif
    {
        // DDC Force Nack Off
        ScalerSyncSetDdcForceNack(_D0_INPUT_PORT, _OFF);
    }

#endif // End of #if((_D0_INPUT_PORT_TYPE != _D0_NO_PORT) && (_D0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))

// D1 EDID-----------------------------------------------------------------------------------------------------------
#if((_D1_INPUT_PORT_TYPE != _D1_NO_PORT) && (_D1_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))

    UserCommonInterfaceLoadEmbeddedEdidDataByPort(_D1_INPUT_PORT_EDID);

#if(_D1_HDMI_MULTI_EDID_SUPPORT == _ON)
    if(UserCommonInterfaceHDMIGetMultiEdidLocated(_D1_INPUT_PORT, UserInterfaceGetMultiHdmiEdidIndex(_D1_INPUT_PORT)) != _HDMI_EDID_EXTERNAL)
#endif
    {
        // DDC Force Nack Off
        ScalerSyncSetDdcForceNack(_D1_INPUT_PORT, _OFF);
    }

#endif // End of #if((_D1_INPUT_PORT_TYPE != _D1_NO_PORT) && (_D1_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))

// D2 EDID-----------------------------------------------------------------------------------------------------------
#if((_D2_INPUT_PORT_TYPE != _D2_NO_PORT) && (_D2_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))

    UserCommonInterfaceLoadEmbeddedEdidDataByPort(_D2_INPUT_PORT_EDID);

#if(_D2_HDMI_MULTI_EDID_SUPPORT == _ON)
    if(UserCommonInterfaceHDMIGetMultiEdidLocated(_D2_INPUT_PORT, UserInterfaceGetMultiHdmiEdidIndex(_D2_INPUT_PORT)) != _HDMI_EDID_EXTERNAL)
#endif
    {
        // DDC Force Nack Off
        ScalerSyncSetDdcForceNack(_D2_INPUT_PORT, _OFF);
    }

#endif // End of #if((_D2_INPUT_PORT_TYPE != _D2_NO_PORT) && (_D2_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))

// D3 EDID-----------------------------------------------------------------------------------------------------------
#if((_D3_INPUT_PORT_TYPE != _D3_NO_PORT) && (_D3_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))

    UserCommonInterfaceLoadEmbeddedEdidDataByPort(_D3_INPUT_PORT_EDID);

#if(_D3_HDMI_MULTI_EDID_SUPPORT == _ON)
    if(UserCommonInterfaceHDMIGetMultiEdidLocated(_D3_INPUT_PORT, UserInterfaceGetMultiHdmiEdidIndex(_D3_INPUT_PORT)) != _HDMI_EDID_EXTERNAL)
#endif
    {
        // DDC Force Nack Off
        ScalerSyncSetDdcForceNack(_D3_INPUT_PORT, _OFF);
    }

#endif // End of #if((_D3_INPUT_PORT_TYPE != _D3_NO_PORT) && (_D3_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))

// D4 EDID-----------------------------------------------------------------------------------------------------------
#if((_D4_INPUT_PORT_TYPE != _D4_NO_PORT) && (_D4_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))

    UserCommonInterfaceLoadEmbeddedEdidDataByPort(_D4_INPUT_PORT_EDID);

#if(_D4_HDMI_MULTI_EDID_SUPPORT == _ON)
    if(UserCommonInterfaceHDMIGetMultiEdidLocated(_D4_INPUT_PORT, UserInterfaceGetMultiHdmiEdidIndex(_D4_INPUT_PORT)) != _HDMI_EDID_EXTERNAL)
#endif
    {
        // DDC Force Nack Off
        ScalerSyncSetDdcForceNack(_D4_INPUT_PORT, _OFF);
    }

#endif // End of #if((_D4_INPUT_PORT_TYPE != _D4_NO_PORT) && (_D4_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))

// D5 EDID-----------------------------------------------------------------------------------------------------------
#if((_D5_INPUT_PORT_TYPE != _D5_NO_PORT) && (_D5_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))

    UserCommonInterfaceLoadEmbeddedEdidDataByPort(_D5_INPUT_PORT_EDID);

#if(_D5_HDMI_MULTI_EDID_SUPPORT == _ON)
    if(UserCommonInterfaceHDMIGetMultiEdidLocated(_D5_INPUT_PORT, UserInterfaceGetMultiHdmiEdidIndex(_D5_INPUT_PORT)) != _HDMI_EDID_EXTERNAL)
#endif
    {
        // DDC Force Nack Off
        ScalerSyncSetDdcForceNack(_D5_INPUT_PORT, _OFF);
    }

#endif // End of #if((_D5_INPUT_PORT_TYPE != _D5_NO_PORT) && (_D5_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))

// D0 MHL EDID--------------------------------------------------------------------------------------------------------
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
    UserCommonInterfaceLoadEmbeddedEdidDataByPort(_D0_INPUT_PORT_MHL_EDID);
#endif

// D1 MHL EDID--------------------------------------------------------------------------------------------------------
#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
    UserCommonInterfaceLoadEmbeddedEdidDataByPort(_D1_INPUT_PORT_MHL_EDID);
#endif

// D2 MHL EDID--------------------------------------------------------------------------------------------------------
#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
    UserCommonInterfaceLoadEmbeddedEdidDataByPort(_D2_INPUT_PORT_MHL_EDID);
#endif

// D3 MHL EDID--------------------------------------------------------------------------------------------------------
#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)
    UserCommonInterfaceLoadEmbeddedEdidDataByPort(_D3_INPUT_PORT_MHL_EDID);
#endif

// D4 MHL EDID--------------------------------------------------------------------------------------------------------
#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
    UserCommonInterfaceLoadEmbeddedEdidDataByPort(_D4_INPUT_PORT_MHL_EDID);
#endif

// D5 MHL EDID--------------------------------------------------------------------------------------------------------
#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
    UserCommonInterfaceLoadEmbeddedEdidDataByPort(_D5_INPUT_PORT_MHL_EDID);
#endif
}

//--------------------------------------------------
// Description  : Set Embedded EDID Data for Input Port
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonInterfaceLoadEmbeddedEdidDataByPort(EnumInputPortEdid enumInputPort)
{
    switch(enumInputPort)
    {
// A0 EDID-----------------------------------------------------------------------------------------------------------
#if((_A0_INPUT_PORT_TYPE != _A0_NO_PORT) && (_A0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))
        case _A0_INPUT_PORT_EDID:

#if(_A0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE)
            memset(MCU_DDCRAM_A0, 0, _A0_EMBEDDED_DDCRAM_MAX_SIZE);
            memcpy(MCU_DDCRAM_A0, tEDID_TABLE_A0, _A0_EMBEDDED_DDCRAM_MAX_SIZE);
#elif(_A0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM)
            UserCommonNVRamRead(_EDID_A0_ADDRESS_EEPROM, _A0_EMBEDDED_DDCRAM_MAX_SIZE, MCU_DDCRAM_A0);
#elif(_A0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)
            UserCommonFlashRead(_EDID_FLASH_BANK, (_EDID_A0_ADDRESS_FLASH), _A0_EMBEDDED_DDCRAM_MAX_SIZE, MCU_DDCRAM_A0);
#elif(_A0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)
            UserInterfaceGetEmbeddedEDIDData(_A0_INPUT_PORT_EDID);
#endif

            break;
#endif

// D0 EDID-----------------------------------------------------------------------------------------------------------
#if((_D0_INPUT_PORT_TYPE != _D0_NO_PORT) && (_D0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))
        case _D0_INPUT_PORT_EDID:

#if(_D0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE)
            memset(MCU_DDCRAM_D0, 0, _D0_EMBEDDED_DDCRAM_MAX_SIZE);
            memcpy(MCU_DDCRAM_D0, tEDID_TABLE_D0, _D0_EMBEDDED_DDCRAM_MAX_SIZE);
#elif(_D0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM)
            UserCommonNVRamRead(_EDID_D0_ADDRESS_EEPROM, _D0_EMBEDDED_DDCRAM_MAX_SIZE, MCU_DDCRAM_D0);
#elif(_D0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)
            UserCommonFlashRead(_EDID_FLASH_BANK, (_EDID_D0_ADDRESS_FLASH), _D0_EMBEDDED_DDCRAM_MAX_SIZE, MCU_DDCRAM_D0);
#elif(_D0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)
            UserInterfaceGetEmbeddedEDIDData(_D0_INPUT_PORT_EDID);
#endif

            break;
#endif

// D1 EDID-----------------------------------------------------------------------------------------------------------
#if((_D1_INPUT_PORT_TYPE != _D1_NO_PORT) && (_D1_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))
        case _D1_INPUT_PORT_EDID:

#if(_D1_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE)
            memset(MCU_DDCRAM_D1, 0, _D1_EMBEDDED_DDCRAM_MAX_SIZE);
            memcpy(MCU_DDCRAM_D1, tEDID_TABLE_D1, _D1_EMBEDDED_DDCRAM_MAX_SIZE);
#elif(_D1_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM)
            UserCommonNVRamRead(_EDID_D1_ADDRESS_EEPROM, _D1_EMBEDDED_DDCRAM_MAX_SIZE, MCU_DDCRAM_D1);
#elif(_D1_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)
            UserCommonFlashRead(_EDID_FLASH_BANK, (_EDID_D1_ADDRESS_FLASH), _D1_EMBEDDED_DDCRAM_MAX_SIZE, MCU_DDCRAM_D1);
#elif(_D1_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)
            UserInterfaceGetEmbeddedEDIDData(_D1_INPUT_PORT_EDID);
#endif

            break;
#endif

// D2 EDID-----------------------------------------------------------------------------------------------------------
#if((_D2_INPUT_PORT_TYPE != _D2_NO_PORT) && (_D2_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))
        case _D2_INPUT_PORT_EDID:

#if(_D2_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE)
            memset(MCU_DDCRAM_D2, 0, _D2_EMBEDDED_DDCRAM_MAX_SIZE);
            memcpy(MCU_DDCRAM_D2, tEDID_TABLE_D2, _D2_EMBEDDED_DDCRAM_MAX_SIZE);
#elif(_D2_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM)
            UserCommonNVRamRead(_EDID_D2_ADDRESS_EEPROM, _D2_EMBEDDED_DDCRAM_MAX_SIZE, MCU_DDCRAM_D2);
#elif(_D2_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)
            UserCommonFlashRead(_EDID_FLASH_BANK, (_EDID_D2_ADDRESS_FLASH), _D2_EMBEDDED_DDCRAM_MAX_SIZE, MCU_DDCRAM_D2);
#elif(_D2_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)
            UserInterfaceGetEmbeddedEDIDData(_D2_INPUT_PORT_EDID);
#endif

            break;
#endif

// D3 EDID-----------------------------------------------------------------------------------------------------------
#if((_D3_INPUT_PORT_TYPE != _D3_NO_PORT) && (_D3_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))
        case _D3_INPUT_PORT_EDID:

#if(_D3_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE)
            memset(MCU_DDCRAM_D3, 0, _D3_EMBEDDED_DDCRAM_MAX_SIZE);
            memcpy(MCU_DDCRAM_D3, tEDID_TABLE_D3, _D3_EMBEDDED_DDCRAM_MAX_SIZE);
#elif(_D3_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM)
            UserCommonNVRamRead(_EDID_D3_ADDRESS_EEPROM, _D3_EMBEDDED_DDCRAM_MAX_SIZE, MCU_DDCRAM_D3);
#elif(_D3_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)
            UserCommonFlashRead(_EDID_FLASH_BANK, (_EDID_D3_ADDRESS_FLASH), _D3_EMBEDDED_DDCRAM_MAX_SIZE, MCU_DDCRAM_D3);
#elif(_D3_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)
            UserInterfaceGetEmbeddedEDIDData(_D3_INPUT_PORT_EDID);
#endif

            break;
#endif

// D4 EDID-----------------------------------------------------------------------------------------------------------
#if((_D4_INPUT_PORT_TYPE != _D4_NO_PORT) && (_D4_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))
        case _D4_INPUT_PORT_EDID:

#if(_D4_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE)
            memset(MCU_DDCRAM_D4, 0, _D4_EMBEDDED_DDCRAM_MAX_SIZE);
            memcpy(MCU_DDCRAM_D4, tEDID_TABLE_D4, _D4_EMBEDDED_DDCRAM_MAX_SIZE);
#elif(_D4_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM)
            UserCommonNVRamRead(_EDID_D4_ADDRESS_EEPROM, _D4_EMBEDDED_DDCRAM_MAX_SIZE, MCU_DDCRAM_D4);
#elif(_D4_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)
            UserCommonFlashRead(_EDID_FLASH_BANK, (_EDID_D4_ADDRESS_FLASH), _D4_EMBEDDED_DDCRAM_MAX_SIZE, MCU_DDCRAM_D4);
#elif(_D4_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)
            UserInterfaceGetEmbeddedEDIDData(_D4_INPUT_PORT_EDID);
#endif

            break;
#endif

// D5 EDID-----------------------------------------------------------------------------------------------------------
#if((_D5_INPUT_PORT_TYPE != _D5_NO_PORT) && (_D5_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))
        case _D5_INPUT_PORT_EDID:

#if(_D5_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE)
            memset(MCU_DDCRAM_D5, 0, _D5_EMBEDDED_DDCRAM_MAX_SIZE);
            memcpy(MCU_DDCRAM_D5, tEDID_TABLE_D5, _D5_EMBEDDED_DDCRAM_MAX_SIZE);
#elif(_D5_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM)
            UserCommonNVRamRead(_EDID_D5_ADDRESS_EEPROM, _D5_EMBEDDED_DDCRAM_MAX_SIZE, MCU_DDCRAM_D5);
#elif(_D5_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)
            UserCommonFlashRead(_EDID_FLASH_BANK, (_EDID_D5_ADDRESS_FLASH), _D5_EMBEDDED_DDCRAM_MAX_SIZE, MCU_DDCRAM_D5);
#elif(_D5_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)
            UserInterfaceGetEmbeddedEDIDData(_D5_INPUT_PORT_EDID);
#endif

            break;
#endif

// D6 EDID-----------------------------------------------------------------------------------------------------------
#if((_D6_INPUT_PORT_TYPE != _D6_NO_PORT) && (_D6_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))
        case _D6_INPUT_PORT_EDID:

#if(_D6_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE)
            memset(MCU_DDCRAM_D6, 0, _D6_EMBEDDED_DDCRAM_MAX_SIZE);
            memcpy(MCU_DDCRAM_D6, tEDID_TABLE_D6, _D6_EMBEDDED_DDCRAM_MAX_SIZE);
#elif(_D6_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM)
            UserCommonNVRamRead(_EDID_D6_ADDRESS_EEPROM, _D6_EMBEDDED_DDCRAM_MAX_SIZE, MCU_DDCRAM_D6);
#elif(_D6_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)
            UserCommonFlashRead(_EDID_FLASH_BANK, (_EDID_D6_ADDRESS_FLASH), _D6_EMBEDDED_DDCRAM_MAX_SIZE, MCU_DDCRAM_D6);
#elif(_D6_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)
            UserInterfaceGetEmbeddedEDIDData(_D6_INPUT_PORT_EDID);
#endif

            break;
#endif

// D0 MHL EDID--------------------------------------------------------------------------------------------------------
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
#if(_D0_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE)
        case _D0_INPUT_PORT_MHL_EDID:

#if(_D0_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE)
            memcpy(MCU_DDCRAM_MHL_D0, tEDID_TABLE_D0_MHL, _D0_MHL_EMBEDDED_DDCRAM_SIZE);
#elif(_D0_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM)
            UserCommonNVRamRead(_EDID_D0_MHL_ADDRESS_EEPROM, _D0_MHL_EMBEDDED_DDCRAM_SIZE, MCU_DDCRAM_MHL_D0);
#elif(_D0_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)
            UserCommonFlashRead(_EDID_FLASH_BANK, (_EDID_D0_MHL_ADDRESS_FLASH), _D0_MHL_EMBEDDED_DDCRAM_SIZE, MCU_DDCRAM_MHL_D0);
#elif(_D0_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)
            UserInterfaceGetEmbeddedEDIDData(_D0_INPUT_PORT_MHL_EDID);
#endif

            break;
#endif
#endif

// D1 MHL EDID--------------------------------------------------------------------------------------------------------
#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
#if(_D1_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE)
        case _D1_INPUT_PORT_MHL_EDID:

#if(_D1_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE)
            memcpy(MCU_DDCRAM_MHL_D1, tEDID_TABLE_D1_MHL, _D1_MHL_EMBEDDED_DDCRAM_SIZE);
#elif(_D1_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM)
            UserCommonNVRamRead(_EDID_D1_MHL_ADDRESS_EEPROM, _D1_MHL_EMBEDDED_DDCRAM_SIZE, MCU_DDCRAM_MHL_D1);
#elif(_D1_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)
            UserCommonFlashRead(_EDID_FLASH_BANK, (_EDID_D1_MHL_ADDRESS_FLASH), _D1_MHL_EMBEDDED_DDCRAM_SIZE, MCU_DDCRAM_MHL_D1);
#elif(_D1_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)
            UserInterfaceGetEmbeddedEDIDData(_D1_INPUT_PORT_MHL_EDID);
#endif

            break;
#endif
#endif

// D2 MHL EDID--------------------------------------------------------------------------------------------------------
#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
#if(_D2_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE)
        case _D2_INPUT_PORT_MHL_EDID:

#if(_D2_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE)
            memcpy(MCU_DDCRAM_MHL_D2, tEDID_TABLE_D2_MHL, _D2_MHL_EMBEDDED_DDCRAM_SIZE);
#elif(_D2_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM)
            UserCommonNVRamRead(_EDID_D2_MHL_ADDRESS_EEPROM, _D2_MHL_EMBEDDED_DDCRAM_SIZE, MCU_DDCRAM_MHL_D2);
#elif(_D2_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)
            UserCommonFlashRead(_EDID_FLASH_BANK, (_EDID_D2_MHL_ADDRESS_FLASH), _D2_MHL_EMBEDDED_DDCRAM_SIZE, MCU_DDCRAM_MHL_D2);
#elif(_D2_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)
            UserInterfaceGetEmbeddedEDIDData(_D2_INPUT_PORT_MHL_EDID);
#endif

            break;
#endif
#endif

// D3 MHL EDID--------------------------------------------------------------------------------------------------------
#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)
#if(_D3_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE)
        case _D3_INPUT_PORT_MHL_EDID:

#if(_D3_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE)
            memcpy(MCU_DDCRAM_MHL_D3, tEDID_TABLE_D3_MHL, _D3_MHL_EMBEDDED_DDCRAM_SIZE);
#elif(_D3_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM)
            UserCommonNVRamRead(_EDID_D3_MHL_ADDRESS_EEPROM, _D3_MHL_EMBEDDED_DDCRAM_SIZE, MCU_DDCRAM_MHL_D3);
#elif(_D3_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)
            UserCommonFlashRead(_EDID_FLASH_BANK, (_EDID_D3_MHL_ADDRESS_FLASH), _D3_MHL_EMBEDDED_DDCRAM_SIZE, MCU_DDCRAM_MHL_D3);
#elif(_D3_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)
            UserInterfaceGetEmbeddedEDIDData(_D3_INPUT_PORT_MHL_EDID);
#endif

            break;
#endif
#endif

// D4 MHL EDID--------------------------------------------------------------------------------------------------------
#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
#if(_D4_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE)
        case _D4_INPUT_PORT_MHL_EDID:

#if(_D4_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE)
            memcpy(MCU_DDCRAM_MHL_D4, tEDID_TABLE_D4_MHL, _D4_MHL_EMBEDDED_DDCRAM_SIZE);
#elif(_D4_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM)
            UserCommonNVRamRead(_EDID_D4_MHL_ADDRESS_EEPROM, _D4_MHL_EMBEDDED_DDCRAM_SIZE, MCU_DDCRAM_MHL_D4);
#elif(_D4_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)
            UserCommonFlashRead(_EDID_FLASH_BANK, (_EDID_D4_MHL_ADDRESS_FLASH), _D4_MHL_EMBEDDED_DDCRAM_SIZE, MCU_DDCRAM_MHL_D4);
#elif(_D4_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)
            UserInterfaceGetEmbeddedEDIDData(_D4_INPUT_PORT_MHL_EDID);
#endif

            break;
#endif
#endif

// D5 MHL EDID--------------------------------------------------------------------------------------------------------
#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
#if(_D5_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE)
        case _D5_INPUT_PORT_MHL_EDID:

#if(_D5_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE)
            memcpy(MCU_DDCRAM_MHL_D5, tEDID_TABLE_D5_MHL, _D5_MHL_EMBEDDED_DDCRAM_SIZE);
#elif(_D5_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM)
            UserCommonNVRamRead(_EDID_D5_MHL_ADDRESS_EEPROM, _D5_MHL_EMBEDDED_DDCRAM_SIZE, MCU_DDCRAM_MHL_D5);
#elif(_D5_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)
            UserCommonFlashRead(_EDID_FLASH_BANK, (_EDID_D5_MHL_ADDRESS_FLASH), _D5_MHL_EMBEDDED_DDCRAM_SIZE, MCU_DDCRAM_MHL_D5);
#elif(_D5_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)
            UserInterfaceGetEmbeddedEDIDData(_D5_INPUT_PORT_MHL_EDID);
#endif

            break;
#endif
#endif

        default:
            break;
    }
}

#if(_DP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set DP Embedded EDID Data
// Input Value  : ucSelectedPort
// Output Value : None
//--------------------------------------------------
void UserCommonInterfaceDPSwitchEdid(BYTE ucSelectedPort)
{
    switch(ucSelectedPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

        case _D0_INPUT_PORT:

            UserCommonInterfaceLoadEmbeddedEdidDataByPort(_D0_INPUT_PORT_EDID);
            ScalerDpEdidSwitch(_D0_INPUT_PORT);

            break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

        case _D1_INPUT_PORT:

            UserCommonInterfaceLoadEmbeddedEdidDataByPort(_D1_INPUT_PORT_EDID);
            ScalerDpEdidSwitch(_D1_INPUT_PORT);

            break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)

        case _D2_INPUT_PORT:

            UserCommonInterfaceLoadEmbeddedEdidDataByPort(_D2_INPUT_PORT_EDID);
            ScalerDpEdidSwitch(_D2_INPUT_PORT);

            break;
#endif

#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)

        case _D6_INPUT_PORT:

            UserCommonInterfaceLoadEmbeddedEdidDataByPort(_D6_INPUT_PORT_EDID);
            ScalerDpEdidSwitch(_D6_INPUT_PORT);

            break;
#endif

        default:
            break;
    }
}

#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_HDR10_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Switch DP ports Embedded EDID Data
// Input Value  : void
// Output Value : None
//--------------------------------------------------
void UserCommonInterfaceDPSwitchAllPortEdid(void)
{
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
    UserCommonInterfaceDPSwitchEdid(_D0_INPUT_PORT);
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
    UserCommonInterfaceDPSwitchEdid(_D1_INPUT_PORT);
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
    UserCommonInterfaceDPSwitchEdid(_D2_INPUT_PORT);
#endif

#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
    UserCommonInterfaceDPSwitchEdid(_D6_INPUT_PORT);
#endif
}
#endif

#endif // End of #if(_DP_SUPPORT == _ON)

#endif // End of #if(_EMBEDDED_EDID_SUPPORT == _ON)

#if((_FLASH_WRITE_FUNCTION_SUPPORT == _ON) && (_HW_PC99_SUPPORT == _ON))
//--------------------------------------------------
// Description  : PC99 EDID Write Command Data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonInterfacePC99EDIDWriteCommandData(void)
{
    BYTE pucPC99CommandData[] =
    {
        #include "./Pc99CommandTable.h"
    };

    UserCommonFlashWrite(_HW_PC99_WRITE_EDID_COMMAND_BANK_INDEX, _HW_PC99_WRITE_EDID_COMMAND_ADDR_START, sizeof(pucPC99CommandData), pucPC99CommandData);
}
#endif // End of #if((_FLASH_WRITE_FUNCTION_SUPPORT == _ON) && (_HW_PC99_SUPPORT == _ON))

#if(_HDMI_MULTI_EDID_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Switch HDMI EDID from user OSD
// Input Value  : ucInputport
//                enumHDMIEDIDSelection --> Edid Index
// Output Value : None
//--------------------------------------------------
void UserCommonInterfaceHDMISwitchEdid(BYTE ucInputport, EnumEdidSelection enumHDMIEDIDSelection)
{
    // Before Reload Edid Process
    UserCommonInterfaceHDMIBeforeReloadEdid(ucInputport, enumHDMIEDIDSelection);

    // Reload Edid Process
#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_WRITE_EDID_LOCATION_BY_USER_SUPPORT == _ON))
    UserCommonInterfaceHDMIReloadEdid(ucInputport);
#endif

    // After Reload Edid Process
    UserCommonInterfaceHDMIAfterReloadEdid(ucInputport, enumHDMIEDIDSelection);

    // HPD Trigger Event Set
    ScalerSyncTMDSEdidSwitch(ucInputport);
}

#if((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI_HDR10_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Switch HDMI EDID from user OSD
// Input Value  : ucInputport
//                enumHDMIEDIDSelection --> Edid Index
// Output Value : None
//--------------------------------------------------
void UserCommonInterfaceHDMISwitchAllPortEdid(void)
{
#if(_D0_HDMI_MULTI_EDID_SUPPORT == _ON)
    UserCommonInterfaceHDMISwitchEdid(_D0_INPUT_PORT, UserInterfaceGetMultiHdmiEdidIndex(_D0_INPUT_PORT));
#endif

#if(_D1_HDMI_MULTI_EDID_SUPPORT == _ON)
    UserCommonInterfaceHDMISwitchEdid(_D1_INPUT_PORT, UserInterfaceGetMultiHdmiEdidIndex(_D1_INPUT_PORT));
#endif

#if(_D2_HDMI_MULTI_EDID_SUPPORT == _ON)
    UserCommonInterfaceHDMISwitchEdid(_D2_INPUT_PORT, UserInterfaceGetMultiHdmiEdidIndex(_D2_INPUT_PORT));
#endif

#if(_D3_HDMI_MULTI_EDID_SUPPORT == _ON)
    UserCommonInterfaceHDMISwitchEdid(_D3_INPUT_PORT, UserInterfaceGetMultiHdmiEdidIndex(_D3_INPUT_PORT));
#endif

#if(_D4_HDMI_MULTI_EDID_SUPPORT == _ON)
    UserCommonInterfaceHDMISwitchEdid(_D4_INPUT_PORT, UserInterfaceGetMultiHdmiEdidIndex(_D4_INPUT_PORT));
#endif

#if(_D5_HDMI_MULTI_EDID_SUPPORT == _ON)
    UserCommonInterfaceHDMISwitchEdid(_D5_INPUT_PORT, UserInterfaceGetMultiHdmiEdidIndex(_D5_INPUT_PORT));
#endif
}
#endif

//--------------------------------------------------
// Description  : Get the HDMI Port Edid location
// Input Value  : ucInputport
// Output Value : location of the Edid index
//--------------------------------------------------
EnumHdmiEdidLocation UserCommonInterfaceHDMIGetMultiEdidLocated(BYTE ucInputport, EnumEdidSelection enumHDMIEDIDSelection)
{
    ucInputport -= _D0_INPUT_PORT;

    if(enumHDMIEDIDSelection < _HDMI_EXT_EDID_MAX_CNT)
    {
        return UserInterfaceGetMultiHdmiEdidLocated(ucInputport, enumHDMIEDIDSelection);
    }
    else
    {
        return _HDMI_EDID_EMBEDDED;
    }
}

//--------------------------------------------------
// Description  : Get the HDMI Port Edid Max Count
// Input Value  : ucInputport
// Output Value : Max Cnt of the Port
//--------------------------------------------------
BYTE UserCommonInterfaceGetHdmiEdidCount(BYTE ucInputport)
{
    switch(ucInputport)
    {
#if(_D0_HDMI_MULTI_EDID_SUPPORT == _ON)
        case _D0_INPUT_PORT:
            return _D0_MAX_HDMI_EDID_COUNT;
            break;
#endif

#if(_D1_HDMI_MULTI_EDID_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            return _D1_MAX_HDMI_EDID_COUNT;
            break;
#endif

#if(_D2_HDMI_MULTI_EDID_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            return _D2_MAX_HDMI_EDID_COUNT;
            break;
#endif

#if(_D3_HDMI_MULTI_EDID_SUPPORT == _ON)
        case _D3_INPUT_PORT:
            return _D3_MAX_HDMI_EDID_COUNT;
            break;
#endif

#if(_D4_HDMI_MULTI_EDID_SUPPORT == _ON)
        case _D4_INPUT_PORT:
            return _D4_MAX_HDMI_EDID_COUNT;
            break;
#endif

#if(_D5_HDMI_MULTI_EDID_SUPPORT == _ON)
        case _D5_INPUT_PORT:
            return _D5_MAX_HDMI_EDID_COUNT;
            break;
#endif

        default:
            return 1;
            break;
    }
    return 0;
}


#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_WRITE_EDID_LOCATION_BY_USER_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Switch HDMI EDID process -- Reload Edid
// Input Value  : enumHDMIEDIDSelection --> Edid Index
//                ucInputport
// Output Value : None
//--------------------------------------------------
void UserCommonInterfaceHDMIReloadEdid(BYTE ucInputport)
{
    switch(ucInputport)
    {
#if((_D0_HDMI_SUPPORT == _ON) &&\
    (_D0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER) &&\
    (_D0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))
        case _D0_INPUT_PORT:

            UserInterfaceGetEmbeddedEDIDData(_D0_INPUT_PORT_EDID);
            break;
#endif

#if((_D1_HDMI_SUPPORT == _ON) &&\
    (_D1_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER) &&\
    (_D1_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))
        case _D1_INPUT_PORT:

            UserInterfaceGetEmbeddedEDIDData(_D1_INPUT_PORT_EDID);


            break;
#endif

#if((_D2_HDMI_SUPPORT == _ON) &&\
    (_D2_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER) &&\
    (_D2_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))
        case _D2_INPUT_PORT:

            UserInterfaceGetEmbeddedEDIDData(_D2_INPUT_PORT_EDID);

            break;
#endif

#if((_D3_HDMI_SUPPORT == _ON) &&\
    (_D3_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER) &&\
    (_D3_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))
        case _D3_INPUT_PORT:

            UserInterfaceGetEmbeddedEDIDData(_D3_INPUT_PORT_EDID);

            break;
#endif

#if((_D4_HDMI_SUPPORT == _ON) &&\
    (_D4_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER) &&\
    (_D4_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))
        case _D4_INPUT_PORT:

            UserInterfaceGetEmbeddedEDIDData(_D4_INPUT_PORT_EDID);

            break;
#endif

#if((_D5_HDMI_SUPPORT == _ON) &&\
    (_D5_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER) &&\
    (_D5_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))
        case _D5_INPUT_PORT:

            UserInterfaceGetEmbeddedEDIDData(_D5_INPUT_PORT_EDID);

            break;
#endif

        default:

            break;
    }
}
#endif

//--------------------------------------------------
// Description  : Switch HDMI EDID process before reload Edid
// Input Value  : enumHDMIEDIDSelection --> Edid Index
//                ucInputport
// Output Value : None
//--------------------------------------------------
void UserCommonInterfaceHDMIBeforeReloadEdid(BYTE ucInputport, EnumEdidSelection enumHDMIEDIDSelection)
{
    bit b1DdcStatus = 0;

    b1DdcStatus = ScalerSyncGetDdcForceNackStatus(ucInputport);

    // Check for Ddc Busy
    ScalerSyncHDMIDdcCheckBusy(ucInputport, _DELAY_30US_TIMESCALE, 1, 1500);

    // Force nack Ddc Channel
    ScalerSyncSetDdcForceNack(ucInputport, _ON);

    if(b1DdcStatus == _FALSE)
    {
        BYTE ucEdidCount = UserCommonInterfaceGetHdmiEdidCount(ucInputport);

        if(ucEdidCount > 1)
        {
            if(UserCommonInterfaceHDMIGetMultiEdidLocated(ucInputport, enumHDMIEDIDSelection) != _HDMI_EDID_EXTERNAL)
            {
                BYTE ucTempEEPROM = 0;
                BYTE ucLoopStop = MINOF(ucEdidCount, _HDMI_EXT_EDID_MAX_CNT);

                for(ucTempEEPROM; ucTempEEPROM < ucLoopStop; ++ucTempEEPROM)
                {
                    if(UserCommonInterfaceHDMIGetMultiEdidLocated(ucInputport, ucTempEEPROM) == _HDMI_EDID_EXTERNAL)
                    {
                        UserCommonInterfaceHDMISwitchMultiEeprom(ucInputport, ucTempEEPROM);
                        break;
                    }
                }
            }
        }
    }
}

//--------------------------------------------------
// Description  : Switch HDMI EDID process after reload Edid
// Input Value  : enumHDMIEDIDSelection --> Edid Index
//                ucInputport
// Output Value : None
//--------------------------------------------------
void UserCommonInterfaceHDMIAfterReloadEdid(BYTE ucInputport, EnumEdidSelection enumHDMIEDIDSelection)
{
    BYTE ucEdidCount = UserCommonInterfaceGetHdmiEdidCount(ucInputport);

    // If Target Edid: External--> Open the Target Eeprom
    UserCommonInterfaceHDMISwitchMultiEeprom(ucInputport, enumHDMIEDIDSelection);

    if(ucEdidCount > 1)
    {
        if(UserCommonInterfaceHDMIGetMultiEdidLocated(ucInputport, enumHDMIEDIDSelection) != _HDMI_EDID_EXTERNAL)
        {
            ScalerSyncSetDdcForceNack(ucInputport, _OFF);
        }
    }
}

//--------------------------------------------------
// Description  : All port external EDID switch turn on/off
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonInterfaceHDMIMultiEdidInitial(void)
{
#if(_D0_HDMI_MULTI_EDID_SUPPORT == _ON)
    // D0_Setting
    UserCommonInterfaceHDMISwitchMultiEeprom(_D0_INPUT_PORT, UserInterfaceGetMultiHdmiEdidIndex(_D0_INPUT_PORT));
#endif

#if(_D1_HDMI_MULTI_EDID_SUPPORT == _ON)
    // D1_Setting
    UserCommonInterfaceHDMISwitchMultiEeprom(_D1_INPUT_PORT, UserInterfaceGetMultiHdmiEdidIndex(_D1_INPUT_PORT));
#endif

#if(_D2_HDMI_MULTI_EDID_SUPPORT == _ON)
    // D2_Setting
    UserCommonInterfaceHDMISwitchMultiEeprom(_D2_INPUT_PORT, UserInterfaceGetMultiHdmiEdidIndex(_D2_INPUT_PORT));
#endif

#if(_D3_HDMI_MULTI_EDID_SUPPORT == _ON)
    // D3_Setting
    UserCommonInterfaceHDMISwitchMultiEeprom(_D3_INPUT_PORT, UserInterfaceGetMultiHdmiEdidIndex(_D3_INPUT_PORT));
#endif

#if(_D4_HDMI_MULTI_EDID_SUPPORT == _ON)
    // D4_Setting
    UserCommonInterfaceHDMISwitchMultiEeprom(_D4_INPUT_PORT, UserInterfaceGetMultiHdmiEdidIndex(_D4_INPUT_PORT));
#endif

#if(_D5_HDMI_MULTI_EDID_SUPPORT == _ON)
    // D5_Setting
    UserCommonInterfaceHDMISwitchMultiEeprom(_D5_INPUT_PORT, UserInterfaceGetMultiHdmiEdidIndex(_D5_INPUT_PORT));
#endif
}

//--------------------------------------------------
// Description  : Multi Edid switch
// Input Value  : Input TMDS Port
//                enumHDMIEDIDSelection --> Edid Index
// Output Value : None
//--------------------------------------------------
void UserCommonInterfaceHDMISwitchMultiEeprom(BYTE ucInputPort, EnumEdidSelection enumHDMIEDIDSelection)
{
    BYTE ucEdidCount = UserCommonInterfaceGetHdmiEdidCount(ucInputPort);

    if(ucEdidCount > 1)
    {
        PCB_MULTI_EDID_SWITCH(ucInputPort, enumHDMIEDIDSelection);

        if(UserCommonInterfaceHDMIGetMultiEdidLocated(ucInputPort, enumHDMIEDIDSelection) != _HDMI_EDID_EXTERNAL)
        {
            // Turn off All External Edid's GPO
            PCB_MULTI_EDID_ALL_SWITCH_OFF(ucInputPort);
        }
    }
}

#endif // End of #if(_HDMI_MULTI_EDID_SUPPORT == _ON)

#if(_DIGITAL_PORT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get HDCP Bksv
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonInterfaceGetHDCPKeyBKsv(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray)
{
    ucSubAddr = ucSubAddr;
    ucLength = ucLength;
    pucReadArray = pucReadArray;

#if(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_CODE)
    memcpy(pucReadArray, tHDCP_KEY_BKSV + ucSubAddr, ucLength);
#elif((_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM) || (_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_FLASH))
    UserCommonNVRamGetHDCPKeyBKsv(ucSubAddr, ucLength, pucReadArray);
#elif(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_USER)
    UserInterfaceGetHDCPKeyBksvByUser(ucSubAddr, ucLength, pucReadArray);
#elif(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_EFUSE)
    ScalerSyncGetEfuseHDCPKeyBKsv(ucSubAddr, ucLength, pucReadArray);
#endif
}

//--------------------------------------------------
// Description  : Get HDCP Key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonInterfaceGetHDCPKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;

#if(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_CODE)
    memcpy(pucReadArray, tHDCP_KEY_TABLE + usSubAddr, usLength);
#elif((_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM) || (_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_FLASH))
    UserCommonNVRamGetHDCPKey(usSubAddr, usLength, pucReadArray);
#elif(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_USER)
    UserInterfaceGetHDCPKeyByUser(usSubAddr, usLength, pucReadArray);
#elif(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_EFUSE)
    ScalerSyncGetEfuseHDCPKey(usSubAddr, usLength, pucReadArray);
#endif
}

#if(_HDCP_2_2_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get HDCP Bksv
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonInterfaceGetHdcp2Certrx(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;

#if(_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_CODE)
    memcpy(pucReadArray, tHDCP2_Certrx + usSubAddr, usLength);
#elif((_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM) || (_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH))
    UserCommonNVRamGetHdcp2Certrx(usSubAddr, usLength, pucReadArray);
#elif(_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_USER)
    UserInterfaceGetHdcp2CertrxByUser(usSubAddr, usLength, pucReadArray);
#endif
}

//--------------------------------------------------
// Description  : Get HDCP Bksv
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonInterfaceGetHdcp2RSADkey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;

#if(_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_CODE)
    memcpy(pucReadArray, tHDCP2_DKey + usSubAddr, usLength);
#elif((_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM) || (_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH))
    UserCommonNVRamGetHdcp2RSADkey(usSubAddr, usLength, pucReadArray);
#elif(_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_USER)
    UserInterfaceGetHdcp2RSADkeyByUser(usSubAddr, usLength, pucReadArray);
#endif
}

//--------------------------------------------------
// Description  : Get HDCP Bksv
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonInterfaceGetHdcp2RSARRModN(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;

#if(_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_CODE)
    memcpy(pucReadArray, tHDCP2_RRMODN + usSubAddr, usLength);
#elif((_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM) || (_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH))
    UserCommonNVRamGetHdcp2RSARRModN(usSubAddr, usLength, pucReadArray);
#elif(_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_USER)
    UserInterfaceGetHdcp2RSARRModNByUser(usSubAddr, usLength, pucReadArray);
#endif
}

#if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get HDCP KpubKm for Verify
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonInterfaceGetHdcp2KpubKm(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;

#if(_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_CODE)
    memcpy(pucReadArray, tHDCP2_KpubKm + usSubAddr, usLength);
#endif
}
#endif

//--------------------------------------------------
// Description  : Get HDCP Bksv
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonInterfaceGetHdcp2RSAKPriv(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;

#if(_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_CODE)
    memcpy(pucReadArray, tHDCP2_KPriv + usSubAddr, usLength);
#elif((_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM) || (_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH))
    UserCommonNVRamGetHdcp2RSAKPriv(usSubAddr, usLength, pucReadArray);
#elif(_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_USER)
    UserInterfaceGetHdcp2RSAKPrivByUser(usSubAddr, usLength, pucReadArray);
#endif
}

//--------------------------------------------------
// Description  : Get HDCP Bksv
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonInterfaceGetHdcp2RSANpinv(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;

#if(_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_CODE)
    memcpy(pucReadArray, tHDCP2_NPINV + usSubAddr, usLength);
#elif((_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM) || (_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH))
    UserCommonNVRamGetHdcp2RSANpinv(usSubAddr, usLength, pucReadArray);
#elif(_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_USER)
    UserInterfaceGetHdcp2RSANpinvByUser(usSubAddr, usLength, pucReadArray);
#endif
}

//--------------------------------------------------
// Description  : Get HDCP Bksv
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonInterfaceGetHdcp2LCKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;

#if(_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_CODE)
    memcpy(pucReadArray, tHDCP2_LCKey + usSubAddr, usLength);
#elif((_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM) || (_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH))
    UserCommonNVRamGetHdcp2LCKey(usSubAddr, usLength, pucReadArray);
#elif(_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_USER)
    UserInterfaceGetHdcp2LCKeyByUser(usSubAddr, usLength, pucReadArray);
#endif
}

#if((_DP_HDCP_2_2_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Get HDCP2.2 TX KEY -- RRMODN
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonInterfaceGetDpTxHdcp2RRMODN(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;

#if(_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_CODE)
    memcpy(pucReadArray, (tTX_HDCP2_RRMODN + (usSubAddr)), usLength);
#elif((_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM) || (_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH))
    UserCommonNVRamGetTxHdcp2RRMODN(usSubAddr, usLength, pucReadArray);
#elif(_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_USER)
    UserInterfaceGetDpTxHdcp2RRMODNByUser(usSubAddr, usLength, pucReadArray);
#endif
}

//--------------------------------------------------
// Description  : Get HDCP2.2 TX KEY -- DCP_LLC_N
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonInterfaceGetDpTxHdcp2DcpLlcN(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;

#if(_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_CODE)
    memcpy(pucReadArray, (tTX_HDCP2_DCP_LLC_N + (usSubAddr)), usLength);
#elif((_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM) || (_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH))
    UserCommonNVRamGetTxHdcp2DcpLlcN(usSubAddr, usLength, pucReadArray);
#elif(_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_USER)
    UserInterfaceGetDpTxHdcp2DcpLlcNByUser(usSubAddr, usLength, pucReadArray);
#endif
}

//--------------------------------------------------
// Description  : Get HDCP2.2 TX KEY -- E_Key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonInterfaceGetDpTxHdcp2EKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;

#if(_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_CODE)
    memcpy(pucReadArray, (tTX_HDCP2_EKEY + (usSubAddr)), usLength);
#elif((_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM) || (_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH))
    UserCommonNVRamGetTxHdcp2EKey(usSubAddr, usLength, pucReadArray);
#elif(_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_USER)
    UserInterfaceGetDpTxHdcp2EKeyByUser(usSubAddr, usLength, pucReadArray);
#endif
}

//--------------------------------------------------
// Description  : Get HDCP2.2 TX KEY -- NP_INV
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonInterfaceGetDpTxHdcp2NPinv(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;

#if(_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_CODE)
    memcpy(pucReadArray, (tTX_HDCP2_NPINV + (usSubAddr)), usLength);
#elif((_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM) || (_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH))
    UserCommonNVRamGetTxHdcp2NPinv(usSubAddr, usLength, pucReadArray);
#elif(_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_USER)
    UserInterfaceGetDpTxHdcp2NPinvByUser(usSubAddr, usLength, pucReadArray);
#endif
}
#endif
#endif

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get HDCP Aksv
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonInterfaceGetTxHDCPKeyAKsv(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray)
{
    ucSubAddr = ucSubAddr;
    ucLength = ucLength;
    pucReadArray = pucReadArray;

#if(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_CODE)
    memcpy(pucReadArray, tTX_HDCP_KEY_AKSV + ucSubAddr, ucLength);
#elif((_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM) || (_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_FLASH))
    UserCommonNVRamGetTxHDCPKeyAKsv(ucSubAddr, ucLength, pucReadArray);
#elif(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_USER)
    UserInterfaceGetTxHDCPKeyAksvByUser(ucSubAddr, ucLength, pucReadArray);
#endif
}
//--------------------------------------------------
// Description  : Get HDCP Key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonInterfaceGetTxHDCPKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;

#if(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_CODE)
    memcpy(pucReadArray, tTX_HDCP_KEY_TABLE + usSubAddr, usLength);
#elif((_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM) || (_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_FLASH))
    UserCommonNVRamGetTxHDCPKey(usSubAddr, usLength, pucReadArray);
#elif(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_USER)
    UserInterfaceGetTxHDCPKeyByUser(usSubAddr, usLength, pucReadArray);
#endif
}
#endif // End of #if(_DP_TX_SUPPORT == _ON)

#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
//--------------------------------------------------
// Description  : Restore default HDCP Key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonInterfaceNVRamRestoreHDCP(void)
{
    BYTE ucCount = 0;
    BYTE pucBuffer[16] = {0};

#if((_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_FLASH) || (_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM))
#if((_FLASH_WRITE_FUNCTION_SUPPORT == _ON) && (_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_FLASH))
    if((_RX_HDCP_1_4_KEY_FLASH_BANK != _EDID_FLASH_BANK) || (_RX_HDCP_1_4_TABLE_FLASH_PAGE != _EDID_TABLE_FLASH_PAGE))
    {
        UserCommonFlashErasePage(_RX_HDCP_1_4_KEY_FLASH_BANK, _RX_HDCP_1_4_TABLE_FLASH_PAGE);
    }
#endif

    // Dump BKSV into NVRAM
    memcpy(pucBuffer, tHDCP_KEY_BKSV, sizeof(tHDCP_KEY_BKSV));
    UserCommonNVRamRestoreHDCP1P4(0, sizeof(tHDCP_KEY_BKSV), pucBuffer);

    // Dump HDCP Key into NVRAM
    for(ucCount = 0; ucCount < 20; ucCount++)
    {
        memcpy(pucBuffer, tHDCP_KEY_TABLE + ucCount * sizeof(pucBuffer), sizeof(pucBuffer));

        UserCommonNVRamRestoreHDCP1P4(5 + ucCount * sizeof(pucBuffer), sizeof(pucBuffer), pucBuffer);
    }
#endif // End of #if((_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_FLASH) || (_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM))

#if((_HDCP_2_2_SUPPORT == _ON) && ((_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH) || (_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM)))
#if((_FLASH_WRITE_FUNCTION_SUPPORT == _ON) && (_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH))
    if((_RX_HDCP_2_2_KEY_FLASH_BANK != _EDID_FLASH_BANK) || (_RX_HDCP_2_2_TABLE_FLASH_PAGE != _EDID_TABLE_FLASH_PAGE))
    {
        UserCommonFlashErasePage(_RX_HDCP_2_2_KEY_FLASH_BANK, _RX_HDCP_2_2_TABLE_FLASH_PAGE);
    }
#endif

    // Restore Certrx to NVRAM
    for(ucCount = 0; ucCount < 33; ucCount++)
    {
        if(ucCount < 32)
        {
            memcpy(pucBuffer, tHDCP2_Certrx + ucCount * sizeof(pucBuffer), sizeof(pucBuffer));
            UserCommonNVRamRestoreHDCP2(ucCount * sizeof(pucBuffer), sizeof(pucBuffer), pucBuffer);
        }
        else
        {
            memcpy(pucBuffer, tHDCP2_Certrx + ucCount * sizeof(pucBuffer), 10);
            UserCommonNVRamRestoreHDCP2(512, 10, pucBuffer);
        }
    }

    // Restore Kpriv to NVRAM
    for(ucCount = 0; ucCount < 20; ucCount++)
    {
        memcpy(pucBuffer, tHDCP2_KPriv + ucCount * sizeof(pucBuffer), sizeof(pucBuffer));
        UserCommonNVRamRestoreHDCP2(522 + ucCount * sizeof(pucBuffer), sizeof(pucBuffer), pucBuffer);
    }

    // Restore RRMODN to NVRAM
    for(ucCount = 0; ucCount < 8; ucCount++)
    {
        memcpy(pucBuffer, tHDCP2_RRMODN + ucCount * sizeof(pucBuffer), sizeof(pucBuffer));
        UserCommonNVRamRestoreHDCP2(842 + ucCount * sizeof(pucBuffer), sizeof(pucBuffer), pucBuffer);
    }

    // Restore Npinv to NVRAM
    memcpy(pucBuffer, tHDCP2_NPINV, sizeof(tHDCP2_NPINV));
    UserCommonNVRamRestoreHDCP2(970, sizeof(tHDCP2_NPINV), pucBuffer);

    // Restore RSA D key to NVRAM
    for(ucCount = 0; ucCount < 8; ucCount++)
    {
        memcpy(pucBuffer, tHDCP2_DKey + ucCount * sizeof(pucBuffer), sizeof(pucBuffer));
        UserCommonNVRamRestoreHDCP2(974 + ucCount * sizeof(pucBuffer), sizeof(pucBuffer), pucBuffer);
    }

    // Restore LC key to NVRAM
    memcpy(pucBuffer, tHDCP2_LCKey, sizeof(tHDCP2_LCKey));
    UserCommonNVRamRestoreHDCP2(1102, sizeof(tHDCP2_LCKey), pucBuffer);

#endif // End of #if((_HDCP_2_2_SUPPORT == _ON) && ((_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH) || (_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM)))

#if(_DP_TX_SUPPORT == _ON)

#if((_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_FLASH) || (_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM))
#if(_FLASH_WRITE_FUNCTION_SUPPORT == _ON)
    if(((_TX_HDCP_1_4_KEY_FLASH_BANK != _EDID_FLASH_BANK) || (_TX_HDCP_1_4_TABLE_FLASH_PAGE != _EDID_TABLE_FLASH_PAGE)) &&
       ((_TX_HDCP_1_4_KEY_FLASH_BANK != _RX_HDCP_1_4_KEY_FLASH_BANK) || (_TX_HDCP_1_4_TABLE_FLASH_PAGE != _RX_HDCP_1_4_TABLE_FLASH_PAGE)))
    {
        UserCommonFlashErasePage(_TX_HDCP_1_4_KEY_FLASH_BANK, _TX_HDCP_1_4_TABLE_FLASH_PAGE);
    }
#endif

    // Dump BKSV into NVRam
    memcpy(pucBuffer, tTX_HDCP_KEY_AKSV, sizeof(tTX_HDCP_KEY_AKSV));
    UserCommonNVRamRestoreTxHDCP1P4(0, sizeof(tTX_HDCP_KEY_AKSV), pucBuffer);

    // Dump HDCP Key into NVRam
    for(ucCount = 0; ucCount < 20; ucCount++)
    {
        memcpy(pucBuffer, tTX_HDCP_KEY_TABLE + ucCount * sizeof(pucBuffer), sizeof(pucBuffer));
        UserCommonNVRamRestoreTxHDCP1P4(5 + ucCount * sizeof(pucBuffer), sizeof(pucBuffer), pucBuffer);
    }
#endif // End of #if((_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_FLASH) || (_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM))

#if((_HDCP_2_2_SUPPORT == _ON) && ((_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH) || (_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM)))
#if(_FLASH_WRITE_FUNCTION_SUPPORT == _ON)
    if(((_TX_HDCP_2_2_KEY_FLASH_BANK != _EDID_FLASH_BANK) || (_TX_HDCP_2_2_TABLE_FLASH_PAGE != _EDID_TABLE_FLASH_PAGE)) &&
       ((_TX_HDCP_2_2_KEY_FLASH_BANK != _RX_HDCP_2_2_KEY_FLASH_BANK) || (_TX_HDCP_2_2_TABLE_FLASH_PAGE != _RX_HDCP_2_2_TABLE_FLASH_PAGE)))
    {
        UserCommonFlashErasePage(_TX_HDCP_2_2_KEY_FLASH_BANK, _TX_HDCP_2_2_TABLE_FLASH_PAGE);
    }
#endif

    // Restore RRMODN to NVRAM (384-Bytes)
    for(ucCount = 0; ucCount < 24; ucCount++)
    {
        memcpy(pucBuffer, tTX_HDCP2_RRMODN + ucCount * sizeof(pucBuffer), sizeof(pucBuffer));
        UserCommonNVRamRestoreTxHDCP2(ucCount * sizeof(pucBuffer), sizeof(pucBuffer), pucBuffer);
    }

    // Restore DCPLLCN to NVRAM (384-Bytes)
    for(ucCount = 0; ucCount < 24; ucCount++)
    {
        memcpy(pucBuffer, tTX_HDCP2_DCP_LLC_N + ucCount * sizeof(pucBuffer), sizeof(pucBuffer));
        UserCommonNVRamRestoreTxHDCP2(384 + ucCount * sizeof(pucBuffer), sizeof(pucBuffer), pucBuffer);
    }

    // Restore EKEY to NVRAM (128-Bytes)
    for(ucCount = 0; ucCount < 8; ucCount++)
    {
        memcpy(pucBuffer, tTX_HDCP2_EKEY + ucCount * sizeof(pucBuffer), sizeof(pucBuffer));
        UserCommonNVRamRestoreTxHDCP2(768 + ucCount * sizeof(pucBuffer), sizeof(pucBuffer), pucBuffer);
    }

    // Restore Npinv to NVRAM (4-Bytes)
    memcpy(pucBuffer, tTX_HDCP2_NPINV, sizeof(tTX_HDCP2_NPINV));
    UserCommonNVRamRestoreTxHDCP2(896, sizeof(tTX_HDCP2_NPINV), pucBuffer);

#endif // End of #if((_HDCP_2_2_SUPPORT == _ON) && ((_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH) || (_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM)))

#endif // End of #if(_DP_TX_SUPPORT == _ON)
}
#endif // End of #if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)

#if(_DP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set Dp Aux Diff Mode or single-ended mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonInterfaceDpAuxSet(void)
{
#if(_D0_DP_EXIST == _ON)
    ScalerDpRx0AuxSet();
#endif

#if(_D1_DP_EXIST == _ON)
    ScalerDpRx1AuxSet();
#endif
}

//--------------------------------------------------
// Description  : Dp Version Switch
// Input Value  : DP input port, _DP_VERSION_1_1 or _DP_VERSION_1_2
// Output Value : None
//--------------------------------------------------
void UserCommonInterfaceDpVersionSwitch(BYTE ucInputPort, EnumDpVersionType enumDpVersion, EnumDPMSTPort enumDpRxMstPort)
{
    DebugMessageSystem("DP Version", enumDpVersion);

    ScalerDpVersionSwitch(ucInputPort, enumDpVersion, enumDpRxMstPort);

#if(_D0_TWO_CHIP_DATA_EXCHANGE_MODE != _DATA_EXCHANGE_MODE_NONE)
    switch(ucInputPort)
    {
        case _D0_INPUT_PORT:
            switch(enumDpVersion)
            {
                case _DP_VERSION_1_0:
                    g_stD0DataExchange.unionDataExchangeItem.stDpVersion.enumVersion = _DATA_EXCHANGE_DP_VERSION_1_0;
                    break;

                case _DP_VERSION_1_1:
                    g_stD0DataExchange.unionDataExchangeItem.stDpVersion.enumVersion = _DATA_EXCHANGE_DP_VERSION_1_1;
                    break;

                case _DP_VERSION_1_2:
                    g_stD0DataExchange.unionDataExchangeItem.stDpVersion.enumVersion = _DATA_EXCHANGE_DP_VERSION_1_2;
                    break;

                case _DP_VERSION_1_4:
                    g_stD0DataExchange.unionDataExchangeItem.stDpVersion.enumVersion = _DATA_EXCHANGE_DP_VERSION_1_4;
                    break;

                default:
                    g_stD0DataExchange.unionDataExchangeItem.stDpVersion.enumVersion = _DATA_EXCHANGE_DP_VERSION_1_1;
                    break;
            }

            if(enumDpRxMstPort == _DP_MST_RX0_PORT)
            {
                g_stD0DataExchange.unionDataExchangeItem.stDpVersion.enumMstPort = _DATA_EXCHANGE_DP_MST_RX0_PORT;
            }
            else
            {
                g_stD0DataExchange.unionDataExchangeItem.stDpVersion.enumMstPort = _DATA_EXCHANGE_DP_MST_NO_PORT;
            }

            SET_DATA_EXCHANGE_EVENT_MESSAGE(_DATA_EXCHAGNE_CMD_DP_VERSION);

            break;

        default:
        case _D1_INPUT_PORT:
        case _D6_INPUT_PORT:
            break;
    }
#endif
}
#endif

#endif // End of #if(_DIGITAL_PORT_SUPPORT == _ON)

#if(_DP_TX_BLOCK_CONTROL_BEFORE_STREAM_OUTPUT == _ON)
//--------------------------------------------------
// Description  : OSD Clone Mode Switch
// Input Value  : Clone Mode on/off
// Output Value : None
//--------------------------------------------------
void UserCommonInterfaceCloneModeSwitch(bit bClone)
{
    DebugMessageSystem("DP Clone Mode Switch", bClone);

    ScalerDpTxCloneModeSwitch(bClone);
}
#endif

//--------------------------------------------------
// Description  : OSD Handler, executed in the main loop
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonInterfaceOsdHandler(void)
{
#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if(ScalerSyncCheckUrgentEvent() == _FALSE)
#endif
    {
        UserOsdHandler();
        SysModeClrModeStateChange();

#if((_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON))
        SysTypeCOsdHubProc();
#endif

#if(_TWO_CHIP_DATA_EXCHANGE_MODE != _DATA_EXCHANGE_MODE_NONE)
        UserCommonDataExchangeHandler();
#endif
    }

#if(_PANEL_STYLE == _PANEL_VBO)
    ScalerDisplayVboPanelBacklightReTurnOn();
#endif

#if(_CODE_DIGITAL_SIGNATURE_SUPPORT != _SIGNATURE_TYPE_OFF)
    UserCommonSignDdcciHandler();
#endif
}

//--------------------------------------------------
// Description  : User related operation
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonInterfaceInitial(void)
{
    // Call Uncalled Function for Compile Warning
    UserCommonInterfaceUncallFunction();
    UserInterfaceUncallFunction();

    // Flash write protect
#if(_FLASH_WR_PROTECT == _ON)
    UserCommonFlashWRProtect();
#endif

#if(_DEVICE_LED_DRIVER_TYPE != _DEVICE_LED_DRIVER_NONE)
    ExternalDeviceInterfaceLedDriverInitial();
#endif

    UserInterfaceInitial();

#if((_MEMORY_TYPE_CONFIG == _MEMORY_DDR3) && (_DDR3_MULTIPHASE_EXIST == _ON))
    // Update DDR3 phase data from user
    UserInterfaceUpdateDDR3PhaseData();
#endif
}

#if(_RGB_QUANTIZATION_RANGE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Quantization Range at HDR support
// Input Value  : None
// Output Value : True or False
//--------------------------------------------------
bit UserCommonInterfaceGetRGBQuantizationLimitRangeStatus(EnumColorRGBQuantization enumColorRGBQuantization)
{
#if(_HDR10_SUPPORT == _ON)
    if(UserCommonHDRGetHDR10Status() == _HDR10_ON)
    {
        switch(enumColorRGBQuantization)
        {
            case _RGB_QUANTIZATION_FULL_RANGE:
            default:

                return _FALSE;

            case _RGB_QUANTIZATION_LIMIT_RANGE:
            case _RGB_QUANTIZATION_DEFAULT_RANGE:
            case _RGB_QUANTIZATION_RESERVED:

                return _TRUE;
        }
    }
    else
#endif
    {
        switch(enumColorRGBQuantization)
        {
            case _RGB_QUANTIZATION_FULL_RANGE:
            case _RGB_QUANTIZATION_DEFAULT_RANGE:
            case _RGB_QUANTIZATION_RESERVED:
            default:

                return _FALSE;

            case _RGB_QUANTIZATION_LIMIT_RANGE:

                return _TRUE;
        }
    }
}
#endif

#if(_TRANSLATOR_SUPPORT == _OFF)
//--------------------------------------------------
// Description  : Return Color Format by User or Not
// Input Value  : None
// Output Value : Color Format
//--------------------------------------------------
EnumColorSpace UserCommonInterfaceGetColorFormat(void)
{
    EnumColorSpace enumColorSpace = ScalerColorGetColorSpace();

    if(ScalerColorGetColorSpaceRGB(UserInterfaceGetColorFormat()) ==
       ScalerColorGetColorSpaceRGB(enumColorSpace))
    {
        return enumColorSpace;
    }

    return UserInterfaceGetColorFormat();
}
#endif

#if(_DP_MST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Mst Rx0 Rx1 Capable Port
// Input Value  : _DP_MST_RX0_PORT or _DP_MST_RX1_PORT
// Output Value : None
//--------------------------------------------------
void UserCommonInterfaceMstRx0Rx1switch(EnumDPMSTPort enumMstCapablePort)
{
    DebugMessageMst("MST Rx0 Rx1 Switch to", enumMstCapablePort);

    ScalerDpRxMstRx0Rx1switch(enumMstCapablePort);

#if(_D0_TWO_CHIP_DATA_EXCHANGE_MODE != _DATA_EXCHANGE_MODE_NONE)
#if(_DP_MST_SUPPORT == _ON)
    switch(enumMstCapablePort)
    {
        case _DP_MST_RX0_PORT:

            g_stD0DataExchange.unionDataExchangeItem.stMstOnOff.enumMstPort = _DATA_EXCHANGE_DP_MST_RX0_PORT;
            SET_DATA_EXCHANGE_EVENT_MESSAGE(_DATA_EXCHAGNE_CMD_MST_ON_OFF);

            DebugMessageSystem("OSD -- MST On/Off Switch", g_stD0DataExchange.unionDataExchangeItem.stMstOnOff.enumMstPort);

            break;

        default:
        case _DP_MST_RX1_PORT:
        case _DP_MST_RX6_PORT:
            g_stD0DataExchange.unionDataExchangeItem.stMstOnOff.enumMstPort = _DATA_EXCHANGE_DP_MST_NO_PORT;
            SET_DATA_EXCHANGE_EVENT_MESSAGE(_DATA_EXCHAGNE_CMD_MST_ON_OFF);

            DebugMessageSystem("OSD -- MST On/Off Switch", g_stD0DataExchange.unionDataExchangeItem.stMstOnOff.enumMstPort);

            break;
    }
#endif
#endif
}
#endif

#if((_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) || (_DP_TYPE_C_CONNECTOR_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Set Capability Change Flag For External Use
// Input Value  : ucInputPort --> Inputput
// Output Value : None
//--------------------------------------------------
void UserCommonInterfaceTypeCSetCapabilityChangeFlag(BYTE ucInputPort)
{
    ucInputPort = ucInputPort;

#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
    SysTypeCSetCapabilityChangeFlag(ucInputPort, _TYPE_C_U3_MODE_CHG);

#if(_D0_TWO_CHIP_DATA_EXCHANGE_MODE != _DATA_EXCHANGE_MODE_NONE)
    switch(ucInputPort)
    {
        case _D0_INPUT_PORT:
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
            if(UserInterfaceTypeCGetOsdU3ModeSelection(_D0_INPUT_PORT) == _TYPE_C_U3_ON)
            {
                g_stD0DataExchange.unionDataExchangeItem.stU3Mode.enumTypeCU3OnOff = _DATA_EXCHANGE_U3_ON;
            }
            else
            {
                g_stD0DataExchange.unionDataExchangeItem.stU3Mode.enumTypeCU3OnOff = _DATA_EXCHANGE_U3_OFF;
            }

            SET_DATA_EXCHANGE_EVENT_MESSAGE(_DATA_EXCHAGNE_CMD_U3_ON_OFF);

            DebugMessageSystem("OSD -- U3 On/Off Switch", g_stD0DataExchange.unionDataExchangeItem.stU3Mode.enumTypeCU3OnOff);
#endif

            break;

        default:
        case _D1_INPUT_PORT:
        case _D6_INPUT_PORT:
            break;
    }
#endif // #if(_D0_TWO_CHIP_DATA_EXCHANGE_MODE != _DATA_EXCHANGE_MODE_NONE)
#endif // End of #if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
}

//--------------------------------------------------
// Description  : Switch DP EDID According to Alt. Mode Pin Assignment
// Input Value  : ucInputPort --> Inputput, enumPinAssignment Pin Assignment
// Output Value : None
//--------------------------------------------------
void UserCommonInterfaceTypeCPinAssignSuccessProc(BYTE ucInputPort, EnumTypeCPinCfgType enumPinAssignment)
{
    UserInterfaceTypeCPinAssignSuccessProc(ucInputPort, enumPinAssignment);
}

#endif // End Of #if((_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) || (_DP_TYPE_C_CONNECTOR_SUPPORT == _ON))

#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
#if(_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get TypeC PDO From User / Kernel
// Input Value  : ucInputPort --> Inputput
// Output Value : None
//--------------------------------------------------
EnumTypeCEmbPdoReference UserCommonInterfaceTypeCPdoReference(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            // Source Capability Defined By User or Kernel Default
            return UserInterfaceTypeCPdoReference(_D0_INPUT_PORT);

            break;
#endif

        default:
            break;
    }
    return _TYPE_C_PDO_FROM_KERNEL;
}

//--------------------------------------------------
// Description  : Get TypeC Max Power Defined By User
// Input Value  : ucInputPort --> Inputput
// Output Value : None
//--------------------------------------------------
WORD UserCommonInterfaceTypeCGetMaxPower(BYTE ucInputPort)
{
    return UserInterfaceTypeCGetMaxPower(ucInputPort);
}

//--------------------------------------------------
// Description  : Get TypeC Number of PDOs Defined By User
// Input Value  : ucInputPort --> Inputput
// Output Value : None
//--------------------------------------------------
EnumTypeCPdoNumber UserCommonInterfaceTypeCGetPdoCount(BYTE ucInputPort)
{
    return UserInterfaceTypeCGetPdoCount(ucInputPort);
}

//--------------------------------------------------
// Description  : Get TypeC PDO Info Defined By User
// Input Value  : ucInputPort --> Inputput
// Output Value : None
//--------------------------------------------------
void UserCommonInterfaceTypeCGetPdoInfo(BYTE ucInputPort, BYTE ucPdoIndex, StructTypeCUserSrcPDO *pstTypeCUserPdo)
{
    StructTypeCUserSrcPDO stTypeCUserPdo;
    stTypeCUserPdo.enumPdoType = _PD_FIX_SUPPLY_PDO;
    stTypeCUserPdo.ucMaxCurrent = 0;
    stTypeCUserPdo.ucMaxVoltage = 0;
    stTypeCUserPdo.ucMinVoltage = 0;

    UserInterfaceTypeCGetPdoInfo(ucInputPort, ucPdoIndex, &stTypeCUserPdo);

    *pstTypeCUserPdo = stTypeCUserPdo;
}

#if(_TYPE_C_EMB_VBUS_PROTECT_MODE == _VBUS_PROTECT_BY_USER)
//--------------------------------------------------
// Description  : Get TypeC PDO Info Defined By User
// Input Value  : ucInputPort --> Inputput
// Output Value : None
//--------------------------------------------------
void UserCommonInterfaceTypeCGetProtectInfo(BYTE ucInputPort, BYTE ucPdoIndex, StructTypeCUserProtectInfo *pstTypeCUserProtectInfo)
{
    StructTypeCUserProtectInfo stTypeCUserProtectInfo;
    stTypeCUserProtectInfo.ucOcpCurRatio = 0;

    UserInterfaceTypeCGetProtectInfo(ucInputPort, ucPdoIndex, &stTypeCUserProtectInfo);

    *pstTypeCUserProtectInfo = stTypeCUserProtectInfo;
}
#endif // End of #if(_TYPE_C_EMB_VBUS_PROTECT_MODE == _VBUS_PROTECT_BY_USER)
#endif // End of #if(_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON)
#endif // End of #if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)

//--------------------------------------------------
// Description  : DDC-CI Switch
// Input Value  : bOn --> _ON / _OFF
// Output Value : None
//--------------------------------------------------
void UserCommonInterfaceDdcciSwitch(EnumDDCCIDebugMode enumMode, BYTE ucInputPort)
{
    ScalerMcuDdcciSwitchPort(enumMode, ucInputPort);

#if(_D0_TWO_CHIP_DATA_EXCHANGE_MODE != _DATA_EXCHANGE_MODE_NONE)
    g_stD0DataExchange.unionDataExchangeItem.stDdcciMode.b1DdcciStatus = (enumMode == _DDCCI_MODE ? _ON : _OFF);
    SET_DATA_EXCHANGE_EVENT_MESSAGE(_DATA_EXCHAGNE_CMD_DDC_CI_MODE);
    DebugMessageSystem("OSD -- DDC-CI Switch", g_stD0DataExchange.unionDataExchangeItem.stDdcciMode.b1DdcciStatus);
#endif
}

#if(_TWO_CHIP_DATA_EXCHANGE_MODE != _DATA_EXCHANGE_MODE_NONE)
//--------------------------------------------------
// Description  : All Data Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonInterfaceDataExchangeAllDataReset(void)
{
#if(_D0_TWO_CHIP_DATA_EXCHANGE_MODE != _DATA_EXCHANGE_MODE_NONE)
    g_stD0DataExchange.unionDataExchangeItem.stOsdReset.stDdcciStatus.b1DdcciStatus = (UserInterfaceGetDdcciMode() == _DDCCI_MODE ? _ON : _OFF);
    g_stD0DataExchange.unionDataExchangeItem.stOsdReset.stDcoffHpdMode.b1DPHotPlugDCOffHigh = UserCommonNVRamGetSystemData(_DP_HOT_PLUG_DC_OFF_HIGH);
    g_stD0DataExchange.unionDataExchangeItem.stOsdReset.stAuxDiffMode.b1DPAuxDiffMode = UserCommonNVRamGetSystemData(_DP_AUX_DIFF_MODE);
    g_stD0DataExchange.unionDataExchangeItem.stOsdReset.stAuxAdjr.b4DPAuxAdjrSetting = UserCommonNVRamGetSystemData(_DP_AUX_ADJR_SETTING);
    g_stD0DataExchange.unionDataExchangeItem.stOsdReset.stIrqTime.ucDpIrqTime_10us = UserCommonNVRamGetSystemData(_DP_IRQ_TIME);

#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
    if(UserInterfaceTypeCGetOsdU3ModeSelection(_D0_INPUT_PORT) == _TYPE_C_U3_ON)
    {
        g_stD0DataExchange.unionDataExchangeItem.stOsdReset.stU3Mode.enumTypeCU3OnOff = _DATA_EXCHANGE_U3_ON;
    }
    else
    {
        g_stD0DataExchange.unionDataExchangeItem.stOsdReset.stU3Mode.enumTypeCU3OnOff = _DATA_EXCHANGE_U3_OFF;
    }
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
    if(UserInterfaceGetFreeSyncEnable(_D0_INPUT_PORT) == _FREESYNC_SUPPORT_ON)
    {
        g_stD0DataExchange.unionDataExchangeItem.stOsdReset.stDpFreeSync.enumFreeSyncOnOff = _DATA_EXCHANGE_DP_FREESYNC_SUPPORT_ON;
    }
    else
    {
        g_stD0DataExchange.unionDataExchangeItem.stOsdReset.stDpFreeSync.enumFreeSyncOnOff = _DATA_EXCHANGE_DP_FREESYNC_SUPPORT_OFF;
    }
#endif

    switch(UserInterfaceGetDPVersion(_D0_INPUT_PORT))
    {
        case _DP_VERSION_1_0:
            g_stD0DataExchange.unionDataExchangeItem.stOsdReset.stDpVersion.enumVersion = _DATA_EXCHANGE_DP_VERSION_1_0;
            break;

        case _DP_VERSION_1_1:
            g_stD0DataExchange.unionDataExchangeItem.stOsdReset.stDpVersion.enumVersion = _DATA_EXCHANGE_DP_VERSION_1_1;
            break;

        case _DP_VERSION_1_2:
            g_stD0DataExchange.unionDataExchangeItem.stOsdReset.stDpVersion.enumVersion = _DATA_EXCHANGE_DP_VERSION_1_2;
            break;

        case _DP_VERSION_1_4:
            g_stD0DataExchange.unionDataExchangeItem.stOsdReset.stDpVersion.enumVersion = _DATA_EXCHANGE_DP_VERSION_1_4;
            break;

        default:
            g_stD0DataExchange.unionDataExchangeItem.stOsdReset.stDpVersion.enumVersion = _DATA_EXCHANGE_DP_VERSION_1_1;
            break;
    }

#if(_DP_MST_SUPPORT == _ON)
    switch(UserInterfaceGetDpMSTCapablePort())
    {
        case _DP_MST_RX0_PORT:

            g_stD0DataExchange.unionDataExchangeItem.stOsdReset.stMstOnOff.enumMstPort = _DATA_EXCHANGE_DP_MST_RX0_PORT;

            break;

        default:
        case _DP_MST_RX1_PORT:
        case _DP_MST_RX6_PORT:
            g_stD0DataExchange.unionDataExchangeItem.stOsdReset.stMstOnOff.enumMstPort = _DATA_EXCHANGE_DP_MST_NO_PORT;

            break;
    }
#endif

    SET_DATA_EXCHANGE_EVENT_MESSAGE(_DATA_EXCHAGNE_CMD_ALL_DATA_RESET);

#endif // End of #if(_D0_TWO_CHIP_DATA_EXCHANGE_MODE != _DATA_EXCHANGE_MODE_NONE)

    DebugMessageSystem("OSD -- Reset", 1);
}
#endif

