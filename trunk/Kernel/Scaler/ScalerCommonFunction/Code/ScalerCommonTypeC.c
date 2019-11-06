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
// ID Code      : ScalerCommonTypeC.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"

#if((_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON))
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

#if((_TYPE_C_EMB_PORT_ROLE == _TYPE_C_PORT_SNK_ONLY) && ((_TYPE_C_EMB_DC_OFF_OPTION == _TYPE_C_DC_OFF_POWER_BANK_CC) || (_TYPE_C_EMB_DC_OFF_OPTION == _TYPE_C_DC_OFF_POWER_BANK_PD)))
#warning "Type-C Port Role = SNK-Only and DC Off Option = Power Bank CC/PD will force CC as SRC-Only when DC Off !!!!"
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
//
//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerTypeCHandler(BYTE ucInputPort, BYTE ucModeState);
EnumTypeCAttachStatus ScalerTypeCGetCcAttach(BYTE ucInputPort);
#if(_USB3_RETIMER_SUPPORT == _ON)
EnumTypeCAttachStatus ScalerTypeCSearchCcAttach(void);
#endif
EnumTypeCAltModeStatus ScalerTypeCGetAltModeReady(BYTE ucInputPort);
bit ScalerTypeCGetPinAssignment(BYTE ucInputPort, EnumTypeCPinCfgType *penumPinAssignment);
bit ScalerTypeCReconnect(BYTE ucInputPort);
bit ScalerTypeCUpdateConfig(BYTE ucInputPort, EnumTypeCMultiFuncStatus enumMultiFunc, EnumTypeCPinCfgCapType enumPinAssignmentCap);
void ScalerTypeCIntHandler_EXINT0(void);
void ScalerTypeCPowerSwitch(EnumPowerAction enumPowerAction);
void ScalerTypeCSrcPdoInitial(BYTE ucInputPort);
void ScalerTypeCSetMaxPower(BYTE ucInputPort, WORD usMaxPower);
void ScalerTypeCSetPdoCnt(BYTE ucInputPort, BYTE ucPdoCnt);
#if(_TYPE_C_EMB_VBUS_PROTECT_MODE == _VBUS_PROTECT_BY_USER)
BYTE ScalerTypeCGetPdoCnt(BYTE ucInputPort);
#endif
EnumPdoCheck ScalerTypeCCheckPdoCountChange(BYTE ucInputPort, BYTE ucPdoCount);
EnumPdoCheck ScalerTypeCCheckPdoChange(BYTE ucInputPort, BYTE ucPdoIndex, StructTypeCUserSrcPDO stTypeCUserPdo);
void ScalerTypeCSetFixPdo(BYTE ucInputPort, BYTE ucPdoIndex, BYTE ucVoltage, BYTE ucMaxCur);
#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
void ScalerTypeCSetPpsPdo(BYTE ucInputPort, BYTE ucPdoIndex, BYTE ucMinVol, BYTE ucMaxVol, BYTE ucMaxCur);
#endif
#if(_TYPE_C_EMB_VBUS_PROTECT_MODE == _VBUS_PROTECT_BY_USER)
void ScalerTypeCSetProtectInfo(BYTE ucInputPort, BYTE ucPdoIndex, StructTypeCUserProtectInfo stTypeCUserProtectInfo);
#endif
void ScalerTypeCSetPdSystemEvent(BYTE ucInputPort, EnumPDSysEvent enumPdSysEvent);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Type C Handler Process
// Input Value  : ucInputPort --> Inputput
// Output Value : None
//--------------------------------------------------
void ScalerTypeCHandler(BYTE ucInputPort, BYTE ucModeState)
{
    ucModeState = ucModeState;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            ScalerTypeCRx0CcHandler(ucModeState);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Return Port Controller CC Attach Status to SysTypeC
// Input Value  : None
// Output Value : CC Attach (_TRUE / _FALSE)
//--------------------------------------------------
EnumTypeCAttachStatus ScalerTypeCGetCcAttach(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            return GET_CC_RX0_ATTACHED();
#endif

        default:

            return _TYPE_C_UNATTACH;
    }
}

#if(_USB3_RETIMER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Return Port Controller Alt Mode Ready Status to SysTypeC
// Input Value  : None
// Output Value : CC Attach (_TRUE / _FALSE)
//--------------------------------------------------
EnumTypeCAttachStatus ScalerTypeCSearchCcAttach(void)
{
    EnumTypeCAttachStatus enumCcAttach = _TYPE_C_UNATTACH;

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)

    enumCcAttach = (enumCcAttach | GET_CC_RX0_ATTACHED());

#endif

    return enumCcAttach;
}
#endif

//--------------------------------------------------
// Description  : Return Port Controller Alt Mode Ready Status to SysTypeC
// Input Value  : None
// Output Value : CC Attach (_TRUE / _FALSE)
//--------------------------------------------------
EnumTypeCAltModeStatus ScalerTypeCGetAltModeReady(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            if(ScalerTypeCRx0PdGetAltModeReady() == _TRUE)
            {
                return _TYPE_C_ALT_MODE_READY;
            }
            else
            {
                return _TYPE_C_ALT_MODE_NOT_READY;
            }
#endif

        default:

            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Return Port Controller Alt Mode Pin Assignment to SysTypeC
// Input Value  : None
// Output Value : _SUCCESS / _FAIL
//--------------------------------------------------
bit ScalerTypeCGetPinAssignment(BYTE ucInputPort, EnumTypeCPinCfgType *penumPinAssignment)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            *penumPinAssignment = ScalerTypeCRx0PdGetPinAssignment();
            return _SUCCESS;
#endif

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D1_INPUT_PORT:

            return _SUCCESS;
#endif

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D6_INPUT_PORT:

            return _SUCCESS;
#endif

        default:

            return _FAIL;
    }
}

//--------------------------------------------------
// Description  : Type C Reconnect Process
// Input Value  : ucInputPort
// Output Value : _SUCCESS / _FAIL
//--------------------------------------------------
bit ScalerTypeCReconnect(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            SET_TYPE_C_ERROR_RECOVERY();

            return _SUCCESS;
#endif

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D1_INPUT_PORT:

            return _SUCCESS;
#endif

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D6_INPUT_PORT:

            return _SUCCESS;
#endif

        default:

            return _FAIL;
    }
}

//--------------------------------------------------
// Description  : Type C Configuration Update
// Input Value  : ucInputPort
// Output Value : _SUCCESS / _FAIL
//--------------------------------------------------
bit ScalerTypeCUpdateConfig(BYTE ucInputPort, EnumTypeCMultiFuncStatus enumMultiFunc, EnumTypeCPinCfgCapType enumPinAssignmentCap)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            ScalerTypeCRx0PdSetPinAssignmentCapability(enumPinAssignmentCap);
            ScalerTypeCRx0PdSetMultiFunctionBit(enumMultiFunc);

            return _SUCCESS;
#endif

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D1_INPUT_PORT:

            return _SUCCESS;
#endif

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D6_INPUT_PORT:

            return _SUCCESS;
#endif

        default:

            return _FAIL;
    }
}

//--------------------------------------------------
// Description  : Type C Interrupt Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCIntHandler_EXINT0(void) using 1
{
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
    ScalerTypeCPowerIntHandler_EXINT0();
    ScalerTypeCRx0CcIntHandler_EXINT0();
    ScalerTypeCRx0PdIntHandler_EXINT0();

    if((ScalerTypeCRx0CcIntClrCheck_EXINT0() == _TRUE) && (ScalerTypeCRx0PdIntClrCheck_EXINT0() == _TRUE))
    {
        MCU_FD29_UFP_DPF_IRQ_STATUS |= _BIT7;

        // Toggle Type C IRQ En to Prevent from IRQ Miss
        ScalerSetBit_EXINT(P6F_10_ADI_IRQ_CTRL, ~_BIT1, 0x00);
        ScalerSetBit_EXINT(P6F_10_ADI_IRQ_CTRL, ~_BIT1, _BIT1);
    }
#endif
}


//--------------------------------------------------
// Description  : Type C Power Switch Process
// Input Value  : enumPowerAction
// Output Value : None
//--------------------------------------------------
void ScalerTypeCPowerSwitch(EnumPowerAction enumPowerAction)
{
    enumPowerAction = enumPowerAction;

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
    ScalerTypeCRx0CcPowerSwitch(enumPowerAction);
    ScalerTypeCRx0PdPowerSwitch(enumPowerAction);
#endif
}

//--------------------------------------------------
// Description  : Type C Initial PDO For Source
// Input Value  : ucInputPort --> Inputput
// Output Value : None
//--------------------------------------------------
void ScalerTypeCSrcPdoInitial(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            ScalerTypeCRx0PdSrcPdoInitial();

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Type C Set Source Max Supply Power
// Input Value  : ucInputPort, usMaxPower in 0.1W
// Output Value : None
//--------------------------------------------------
void ScalerTypeCSetMaxPower(BYTE ucInputPort, WORD usMaxPower)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            ScalerTypeCRx0PdSetMaxPower(usMaxPower);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Type C Set Number of PDO Counts
// Input Value  : ucInputPort, Number of PDO Counts (1~7)
// Output Value : None
//--------------------------------------------------
void ScalerTypeCSetPdoCnt(BYTE ucInputPort, BYTE ucPdoCnt)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            ScalerTypeCRx0PdSetPdoCnt(ucPdoCnt);

            break;
#endif

        default:

            break;
    }
}

#if(_TYPE_C_EMB_VBUS_PROTECT_MODE == _VBUS_PROTECT_BY_USER)
//--------------------------------------------------
// Description  : Get Number of PDOs in PD FW (May Be User/Kernel-Defined)
// Input Value  : ucInputPort
// Output Value : Number of PDO Counts (1~7)
//--------------------------------------------------
BYTE ScalerTypeCGetPdoCnt(BYTE ucInputPort)
{
    BYTE ucPdoCnt = 0;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            ucPdoCnt = ScalerTypeCRx0PdGetPdoCnt();

            break;
#endif

        default:

            break;
    }

    return ucPdoCnt;
}
#endif

//--------------------------------------------------
// Description  : Type C Check PDO Count Change
// Input Value  : ucInputPort, ucPdoCount
// Output Value : EnumPdoCheck
//--------------------------------------------------
EnumPdoCheck ScalerTypeCCheckPdoCountChange(BYTE ucInputPort, BYTE ucPdoCount)
{
    EnumPdoCheck enumSrcCapPdoChange = _TYPE_C_PDO_NO_CHANGE;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            enumSrcCapPdoChange = ScalerTypeCRx0PdCheckPdoCountChange(ucPdoCount);

            break;
#endif

        default:

            enumSrcCapPdoChange = _TYPE_C_PDO_NO_CHANGE;

            break;
    }

    return enumSrcCapPdoChange;
}

//--------------------------------------------------
// Description  : Type C Check PDO Change
// Input Value  : ucInputPort, ucPdoIndex, stTypeCUserPdo
// Output Value : EnumPdoCheck
//--------------------------------------------------
EnumPdoCheck ScalerTypeCCheckPdoChange(BYTE ucInputPort, BYTE ucPdoIndex, StructTypeCUserSrcPDO stTypeCUserPdo)
{
    EnumPdoCheck enumSrcCapPdoChange = _TYPE_C_PDO_NO_CHANGE;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            enumSrcCapPdoChange = ScalerTypeCRx0PdCheckPdoChange(ucPdoIndex, stTypeCUserPdo);

            break;
#endif

        default:

            enumSrcCapPdoChange = _TYPE_C_PDO_NO_CHANGE;

            break;
    }

    return enumSrcCapPdoChange;
}

//--------------------------------------------------
// Description  : Type C Set Fix Supply PDO
// Input Value  : ucInputPort, ucPdoIndex, ucVoltage(100mV), ucMaxCur(50mA)
// Output Value : None
//--------------------------------------------------
void ScalerTypeCSetFixPdo(BYTE ucInputPort, BYTE ucPdoIndex, BYTE ucVoltage, BYTE ucMaxCur)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            ScalerTypeCRx0PdSetFixPdo(ucPdoIndex, (WORD)ucVoltage, (WORD)ucMaxCur);

            break;
#endif

        default:

            break;
    }
}

#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Type C Set PPS PDO
// Input Value  : ucInputPort, ucPdoIndex, ucVoltage(100mV), ucMaxCur(50mA)
// Output Value : None
//--------------------------------------------------
void ScalerTypeCSetPpsPdo(BYTE ucInputPort, BYTE ucPdoIndex, BYTE ucMinVol, BYTE ucMaxVol, BYTE ucMaxCur)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            ScalerTypeCRx0PdSetArgumentedPdo(ucPdoIndex, ucMinVol, ucMaxVol, ucMaxCur);

            break;
#endif

        default:

            break;
    }
}
#endif

#if(_TYPE_C_EMB_VBUS_PROTECT_MODE == _VBUS_PROTECT_BY_USER)
//--------------------------------------------------
// Description  : Type C Set Protect Info
// Input Value  : ucInputPort, ucPdoIndex, StructTypeCUserProtectInfo
// Output Value : None
//--------------------------------------------------
void ScalerTypeCSetProtectInfo(BYTE ucInputPort, BYTE ucPdoIndex, StructTypeCUserProtectInfo stTypeCUserProtectInfo)
{
    ucPdoIndex = ucPdoIndex;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            ScalerTypeCRx0PdSetProtectInfo(ucPdoIndex, stTypeCUserProtectInfo);

            break;
#endif

        default:

            break;
    }
}
#endif

//--------------------------------------------------
// Description  : Type C Set Source Capability Change Flag
// Input Value  : ucInputPort
// Output Value : None
//--------------------------------------------------
void ScalerTypeCSetPdSystemEvent(BYTE ucInputPort, EnumPDSysEvent enumPdSysEvent)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            ScalerTypeCRx0PdSetSystemEvent(enumPdSysEvent);

            break;
#endif

        default:

            break;
    }
}

#endif // End of #if((_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON))
