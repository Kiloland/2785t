/*   modification,  distribution,  or  otherwise  is strictly prohibited. The   */
/*   Software  shall  be  kept  strictly  in  confidence,  and  shall  not be   */
/*   disclosed to or otherwise accessed by any third party.                     */
/*   c<2003> - <2011>                                                           */
/*   The Software is provided "AS IS" without any warranty of any kind,         */
/*   express, implied, statutory or otherwise.                                  */
/********************************************************************************/
#if((_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON))
//----------------------------------------------------------------------------------------------------
// ID Code      : ScalerCommonTypeCInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// INTERFACE STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************
extern void ScalerTypeCHandler(BYTE ucInputPort, BYTE ucModeState);
extern EnumTypeCAttachStatus ScalerTypeCGetCcAttach(BYTE ucInputPort);
#if(_USB3_RETIMER_SUPPORT == _ON)
extern EnumTypeCAttachStatus ScalerTypeCSearchCcAttach(void);
#endif
extern EnumTypeCAltModeStatus ScalerTypeCGetAltModeReady(BYTE ucInputPort);
extern bit ScalerTypeCGetPinAssignment(BYTE ucInputPort, EnumTypeCPinCfgType *penumPinAssignment);
extern bit ScalerTypeCReconnect(BYTE ucInputPort);
extern bit ScalerTypeCUpdateConfig(BYTE ucInputPort, EnumTypeCMultiFuncStatus enumMultiFunc, EnumTypeCPinCfgCapType enumPinAssignmentCap);
extern void ScalerTypeCIntHandler_EXINT0(void);
extern void ScalerTypeCPowerSwitch(EnumPowerAction enumPowerAction);
extern void ScalerTypeCSrcPdoInitial(BYTE ucInputPort);
extern void ScalerTypeCSetMaxPower(BYTE ucInputPort, WORD usMaxPower);
extern void ScalerTypeCSetPdoCnt(BYTE ucInputPort, BYTE ucPdoCnt);
#if(_TYPE_C_EMB_VBUS_PROTECT_MODE == _VBUS_PROTECT_BY_USER)
extern BYTE ScalerTypeCGetPdoCnt(BYTE ucInputPort);
#endif
extern EnumPdoCheck ScalerTypeCCheckPdoCountChange(BYTE ucInputPort, BYTE ucPdoCount);
extern EnumPdoCheck ScalerTypeCCheckPdoChange(BYTE ucInputPort, BYTE ucPdoIndex, StructTypeCUserSrcPDO stTypeCUserPdo);
extern void ScalerTypeCSetFixPdo(BYTE ucInputPort, BYTE ucPdoIndex, BYTE ucVoltage, BYTE ucMaxCur);
#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
extern void ScalerTypeCSetPpsPdo(BYTE ucInputPort, BYTE ucPdoIndex, BYTE ucMinVol, BYTE ucMaxVol, BYTE ucMaxCur);
#endif
#if(_TYPE_C_EMB_VBUS_PROTECT_MODE == _VBUS_PROTECT_BY_USER)
extern void ScalerTypeCSetProtectInfo(BYTE ucInputPort, BYTE ucPdoIndex, StructTypeCUserProtectInfo stTypeCUserProtectInfo);
#endif
extern void ScalerTypeCSetPdSystemEvent(BYTE ucInputPort, EnumPDSysEvent enumPdSysEvent);
#endif // End of #if((_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON))

