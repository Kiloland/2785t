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
// ID Code      : UserCommonPortControllerRts5400.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_PORTCONTROLLER5400__

#include "UserCommonInclude.h"

#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#if(_PORT_CONTROLLER_RTS5400_SERIES_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//--------------------------------------------------
// Definition of Type-C 5400 Related Macro
//--------------------------------------------------
#define GET_TYPE_C_5400_DATA_ROLE(x)                        (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].enumDataRole)
#define SET_TYPE_C_5400_DATA_ROLE(x, y)                     (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].enumDataRole = (y))


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    EnumTypeCDataRole enumDataRole;
}StructPortController5400Info;

//****************************************************************************
// CODE TABLES
//****************************************************************************
// Write Command && Read Command
#if(_TYPE_C_RTS5400_SERIES_SPEC_VER_SEL >= _RTS5400_SERIES_FW_SPEC_VERSION_V0D7)
code StructSMBusWRGetICStatus tSMBusWrCmdGetICStatus[1] = {{0x3A, 0x03, 0x08, 0x00, 0x01}};
code StructSMBusRDGetICStatus tSMBusRdCmdGetICStatus[1] = {{0x80, 0x02, 0x00}};

code StructSMBusWRReadDPLanes tSMBusWrCmdReadDpCapVdoSelf[1] = {{0x08, 0x04, 0x9A, 0x00, 0x01, 0x0C}};
code StructSMBusWRReadDPLanes tSMBusWrCmdReadDpCapVdoPartner[1] = {{0x08, 0x04, 0x9A, 0x00, 0x09, 0x0C}};
code StructSMBusRDReadDPLanesCfg tSMBusRdCmdDPCapVdo[1] = {{0x80, 0x05, 0x45, 0x04, 0x00, 0x00}};

code StructSMBusWRGetStatus tSMBusWrGetStatus[1] = {{0x09, 0x03, 0x00, 0x00, 0x0E}};
code StructSMBusRDGetStatus tSMBusRDGetStatus[1] = {{0x80, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};

code StructSMBusWRReadDPLanes tSMBusWrCmdReadDPCfgVdoSelf[1] = {{0x08, 0x04, 0x9A, 0x00, 0x01, 0x0E}};
code StructSMBusWRReadDPLanes tSMBusWrCmdReadDPCfgVdoPartner[1] = {{0x08, 0x04, 0x9A, 0x00, 0x09, 0x0E}};
code StructSMBusRDReadDPLanesCfg tSMBusRdCmdReadDPCfgVdo[1] = {{0x80, 0x05, 0x06, 0x04, 0x00, 0x00}};
#else
code StructSMBusWRGetICStatus tSMBusWrCmdGetICStatus[1] = {{0x3A, 0x01, 0x14}};
code StructSMBusRDGetICStatus tSMBusRdCmdGetICStatus[1] = {{0x80, 0x15, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
#endif

code StructSMBusWRSetDPLanes tSMBusWrCmdSetDPCapVdoSelf[1] = {{0x08, 0x08, 0x1A, 0x00, 0x01, 0x0C, 0x45, 0x00, 0x08, 0x00}};

code StructSMBusWRSetDPLanes tSMBusWrCmdSetDPCfgVdoSelf[1] = {{0x08, 0x08, 0x1A, 0x00, 0x01, 0x0E, 0x05, 0x04, 0x00, 0x00}};

code StructSMBusWRSetDPMultiFunction tSMBusWrCmdSetDPMultiFunction[1] = {{0x08, 0x08, 0x1A, 0x00, 0x01, 0x0D, 0x18, 0x00, 0x00, 0x00}};
code StructSMBusWRReadDPMultiFunction tSMBusWrCmdReadDPMultiFunction[1] = {{0x08, 0x04, 0x9A, 0x00, 0x01, 0x0D}};
code StructSMBusRDReadDPMultiFunction tSMBusRdCmdDPMultiFunction[1] = {{0x80, 0x05, 0x08, 0x00, 0x00, 0x00}};

code StructSMBusWRReconnect tSMBusWrCmdSetReconnect[1] = {{0x08, 0x03, 0x1F, 0x00, 0x01}};

code StructSMBusRDCommandReadyStatus tSMBusRdCmdCommandReadyStatus[1] = {{0x00, 0x00}};

code StructSMBusRDReadDPLanes tSMBusRdCmdDPlanes[1] = {{0x80, 0x05, 0x45, 0x00, 0x08, 0x00}};

#if(_TYPE_C_RTS5400_SERIES_PDO_INFO_SUPPORT == _ON)
code StructSMBusWRGetPDOStatus tSMBusWrCmdGetPDOPartnerStatus[1] = {{0x08, 0x03, 0x83, 0x00, 0xE3}};
code StructSMBusRDGetPDOStatus tSMBusRdCmdGetPDOPartnerStatus[1] = {{0x80, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
#endif

code StructSMBusWRGetCableInfo tSMBusWrCmdGetCableInfo[1] = {{0x08, 0x01, 0xA8}};
code StructSMBusRDGetCableInfo tSMBusRdCmdGetCableInfo[1] = {{0x80, 0x05, 0x00, 0x00, 0x00, 0x00}};

code StructSMBusWREnableVenderCommand tSMBusWrCmdEnableVenderCommand[1] = {{0x01, 0x03, 0xDA, 0x0B, 0x01}};

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructPortController5400Info g_pstTypeC5400Info[_TYPE_C_PORT_VALID];

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
#if(_D0_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
EnumTypeCAttachStatus UserCommonPortControllerGetD0CcAttachByI2C(void);
EnumTypeCAltModeStatus UserCommonPortControllerGetD0AltModeReadyByI2C(void);
#endif
#endif

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
#if(_D1_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
EnumTypeCAttachStatus UserCommonPortControllerGetD1CcAttachByI2C(void);
EnumTypeCAltModeStatus UserCommonPortControllerGetD1AltModeReadyByI2C(void);
#endif
#endif

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
#if(_D6_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
EnumTypeCAttachStatus UserCommonPortControllerGetD6CcAttachByI2C(void);
EnumTypeCAltModeStatus UserCommonPortControllerGetD6AltModeReadyByI2C(void);
#endif
#endif

bit UserCommonPortControllerGet5400PinAssignment(BYTE ucInputPort, EnumTypeCPinCfgType *penumPinAssignment);
BYTE UserCommonPortControllerGetPCAddr(BYTE ucInputPort);
bit UserCommonPortControllerGet5400InfoByI2C(BYTE ucInputPort, Enum5400InfoType enum5400InfoType, BYTE *pucReadInfo);
bit UserCommonPortControllerWrite5400Command(BYTE ucInputPort, BYTE ucSlaveAddr, Enum5400InfoType enum5400InfoType);
bit UserCommonPortControllerRead5400Command(BYTE ucInputPort, BYTE ucSlaveAddr, Enum5400InfoType enum5400InfoType);
EnumTypeCPinCfgType UserCommonPortControllerDecode5400PinAssignment(BYTE ucPdInfo);

bit UserCommonPortController5400Reconnect(BYTE ucInputPort);
bit UserCommonPortControllerConfig5400PinAssignment(BYTE ucInputPort, EnumTypeCPinCfgCapType enumPinAssignment);
bit UserCommonPortControllerConfig5400MultiFunction(BYTE ucInputPort, EnumTypeCMultiFuncStatus enumMultiFunction);

#if(_TYPE_C_RTS5400_SERIES_PDO_INFO_SUPPORT == _ON)
bit UserCommonPortControllerGet5400PDOStatus(BYTE ucInputPort, BYTE *pucVoltage, BYTE *pucCurrent);
#endif

bit UserCommonPortControllerEnable5400VenderCommand(BYTE ucInputPort);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
#if(_D0_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
//--------------------------------------------------
// Description  : Get D0 CC Attached Info
// Input Value  : ucInputPort --> Inputput
// Output Value : CC Attach (_TRUE / _FALSE)
//--------------------------------------------------
EnumTypeCAttachStatus UserCommonPortControllerGetD0CcAttachByI2C(void)
{
    BYTE ucReadInfo = 0x00;

    // Return _TRUE if D0 Port is Currently Lit Up From DP Source
    if((SysSourceGetInputPort() == _D0_INPUT_PORT) && (SysSourceGetSourceType() == _SOURCE_DP))
    {
        return _TYPE_C_ATTACH;
    }

    // Use I2C to Update CC Status Every 500ms, Otherwise Return Status in Source Handler
    if(GET_D0_DP_TYPE_C_DETECT_CC_ATTACH() == _FALSE)
    {
        return (EnumTypeCAttachStatus)GET_D0_CABLE_STATUS();
    }

    // CLR Type-C Detect CC Attach Flag, Wait At Least 500ms to Read 5400 Info Via IIC
    CLR_D0_DP_TYPE_C_DETECT_CC_ATTACH();
    ScalerTimerActiveTimerEvent(SEC(0.5), _SYSTEM_TIMER_EVENT_D0_TYPE_C_CABLE_DETECT);

    // Read 5400 Info Via IIC Command
    if(UserCommonPortControllerGet5400InfoByI2C(_D0_INPUT_PORT, _5400_CC_ATTACH, &ucReadInfo) == _SUCCESS)
    {
        if(ucReadInfo == _TYPE_C_ATTACH)
        {
            return _TYPE_C_ATTACH;
        }
        else
        {
            return _TYPE_C_UNATTACH;
        }
    }
    else
    {
        DebugMessageSystem("8. Read 5400 D0 CC Attach By IIC Fail", 0);

        return _TYPE_C_UNATTACH;
    }
}

//--------------------------------------------------
// Description  : Get D0 Alt Mode Ready Info Through I2C
// Input Value  : None
// Output Value : CC Attach (_TRUE / _FALSE)
//--------------------------------------------------
EnumTypeCAltModeStatus UserCommonPortControllerGetD0AltModeReadyByI2C(void)
{
    BYTE ucReadInfo = 0x00;

    // Return _TRUE if D0 Port is Currently Lit Up From DP Source
    if((SysSourceGetInputPort() == _D0_INPUT_PORT) && (SysSourceGetSourceType() == _SOURCE_DP))
    {
        return _TYPE_C_ALT_MODE_READY;
    }

    // Use I2C to Update Alt. Mode Status Every 500ms, Otherwise Return Status in Source Handler
    if(GET_D0_DP_TYPE_C_DETECT_ALT_MODE() == _FALSE)
    {
        return (EnumTypeCAltModeStatus)GET_D0_DP_TYPE_C_ALTMODE_STATUS();
    }

    // CLR Type-C Detect Alt Mode Flag, Wait At Least 500ms to Read 5400 PD Info Via IIC
    CLR_D0_DP_TYPE_C_DETECT_ALT_MODE();
    ScalerTimerActiveTimerEvent(SEC(0.5), _SYSTEM_TIMER_EVENT_D0_TYPE_C_CABLE_DETECT);

    // Read 5400 Info Via IIC Command
    if(UserCommonPortControllerGet5400InfoByI2C(_D0_INPUT_PORT, _5400_ALT_MODE_READY, &ucReadInfo) == _SUCCESS)
    {
        if(ucReadInfo == _TYPE_C_ALT_MODE_READY)
        {
            return _TYPE_C_ALT_MODE_READY;
        }
        else
        {
            return _TYPE_C_ALT_MODE_NOT_READY;
        }
    }
    else
    {
        DebugMessageSystem("8. Read 5400 D0 Alt Mode Ready By IIC Fail", 0);

        return _TYPE_C_ALT_MODE_NOT_READY;
    }
}

#endif  // End of #if(_D0_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
#endif  // End of #if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
#if(_D1_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
//--------------------------------------------------
// Description  : Get D1 CC Attached Info
// Input Value  : ucInputPort --> Inputput
// Output Value : CC Attach (_TRUE / _FALSE)
//--------------------------------------------------
EnumTypeCAttachStatus UserCommonPortControllerGetD1CcAttachByI2C(void)
{
    BYTE ucReadInfo = 0x00;

    // Current Lit Up Port is _D1_INPUT_PORT,
    if((SysSourceGetInputPort() == _D1_INPUT_PORT) && (SysSourceGetSourceType() == _SOURCE_DP))
    {
        return _TRUE;
    }

    // Use I2C to Update CC Status Every 500ms, Otherwise Return Status in Source Handler
    if(GET_D1_DP_TYPE_C_DETECT_CC_ATTACH() == _FALSE)
    {
        return (EnumTypeCAttachStatus)GET_D1_CABLE_STATUS();
    }

    // CLR Type-C Detect CC Attach Flag, Wait At Least 500ms to Read 5400 Info Via IIC
    CLR_D1_DP_TYPE_C_DETECT_CC_ATTACH();
    ScalerTimerActiveTimerEvent(SEC(0.5), _SYSTEM_TIMER_EVENT_D1_TYPE_C_CABLE_DETECT);

    // Read 5400 Info Via IIC Command
    if(UserCommonPortControllerGet5400InfoByI2C(_D1_INPUT_PORT, _5400_CC_ATTACH, &ucReadInfo) == _SUCCESS)
    {
        if(ucReadInfo == _TYPE_C_ATTACH)
        {
            return _TYPE_C_ATTACH;
        }
        else
        {
            return _TYPE_C_UNATTACH;
        }
    }
    else
    {
        DebugMessageSystem("8. Read 5400 D1 CC Attach By IIC Fail", 0);

        return _TYPE_C_UNATTACH;
    }
}

//--------------------------------------------------
// Description  : Get D1 Alt Mode Ready Info Through I2C
// Input Value  : None
// Output Value : CC Attach (_TRUE / _FALSE)
//--------------------------------------------------
EnumTypeCAltModeStatus UserCommonPortControllerGetD1AltModeReadyByI2C(void)
{
    BYTE ucReadInfo = 0x00;

    // Return _TRUE if D0 Port is Currently Lit Up From DP Source
    if((SysSourceGetInputPort() == _D1_INPUT_PORT) && (SysSourceGetSourceType() == _SOURCE_DP))
    {
        return _TYPE_C_ALT_MODE_READY;
    }

    // Use I2C to Update Alt. Mode Status Every 500ms, Otherwise Return Status in Source Handler
    if(GET_D1_DP_TYPE_C_DETECT_ALT_MODE() == _FALSE)
    {
        return (EnumTypeCAltModeStatus)GET_D1_DP_TYPE_C_ALTMODE_STATUS();
    }

    // CLR Type-C Detect Alt Mode Flag, Wait At Least 500ms to Read 5400 PD Info Via IIC
    CLR_D1_DP_TYPE_C_DETECT_ALT_MODE();
    ScalerTimerActiveTimerEvent(SEC(0.5), _SYSTEM_TIMER_EVENT_D1_TYPE_C_CABLE_DETECT);

    // Read 5400 Info Via IIC Command
    if(UserCommonPortControllerGet5400InfoByI2C(_D1_INPUT_PORT, _5400_ALT_MODE_READY, &ucReadInfo) == _SUCCESS)
    {
        if(ucReadInfo == _TYPE_C_ALT_MODE_READY)
        {
            return _TYPE_C_ALT_MODE_READY;
        }
        else
        {
            return _TYPE_C_ALT_MODE_NOT_READY;
        }
    }
    else
    {
        DebugMessageSystem("8. Read 5400 D1 Alt Mode Ready By IIC Fail", 0);

        return _TYPE_C_ALT_MODE_NOT_READY;
    }
}

#endif // End of #if(_D1_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
#endif // End of #if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
#if(_D6_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
//--------------------------------------------------
// Description  : Get D6 CC Attached Info
// Input Value  : ucInputPort --> Inputput
// Output Value : CC Attach (_TRUE / _FALSE)
//--------------------------------------------------
EnumTypeCAttachStatus UserCommonPortControllerGetD6CcAttachByI2C(void)
{
    BYTE ucReadInfo = 0x00;

    // Current Lit Up Port is _D6_INPUT_PORT,
    if((SysSourceGetInputPort() == _D6_INPUT_PORT) && (SysSourceGetSourceType() == _SOURCE_DP))
    {
        return _TYPE_C_ATTACH;
    }

    // Use I2C to Update CC Status Every 500ms, Otherwise Return Status in Source Handler
    if(GET_D6_DP_TYPE_C_DETECT_CC_ATTACH() == _FALSE)
    {
        return (EnumTypeCAttachStatus)GET_D6_CABLE_STATUS();
    }

    // CLR Type-C Detect CC Attach Flag, Wait At Least 500ms to Read 5400 Info Via IIC
    CLR_D6_DP_TYPE_C_DETECT_CC_ATTACH();
    ScalerTimerActiveTimerEvent(SEC(0.5), _SYSTEM_TIMER_EVENT_D6_TYPE_C_CABLE_DETECT);

    // Read 5400 Info Via IIC Command
    if(UserCommonPortControllerGet5400InfoByI2C(_D6_INPUT_PORT, _5400_CC_ATTACH, &ucReadInfo) == _SUCCESS)
    {
        if(ucReadInfo == _TYPE_C_ATTACH)
        {
            return _TYPE_C_ATTACH;
        }
        else
        {
            return _TYPE_C_UNATTACH;
        }
    }
    else
    {
        DebugMessageSystem("8. Read 5400 D6 CC Attach By IIC Fail", 0);

        return _TYPE_C_UNATTACH;
    }
}

//--------------------------------------------------
// Description  : Get D6 Alt Mode Ready Info Through I2C
// Input Value  : None
// Output Value : CC Attach (_TRUE / _FALSE)
//--------------------------------------------------
EnumTypeCAltModeStatus UserCommonPortControllerGetD6AltModeReadyByI2C(void)
{
    BYTE ucReadInfo = 0x00;

    // Return _TRUE if D0 Port is Currently Lit Up From DP Source
    if((SysSourceGetInputPort() == _D6_INPUT_PORT) && (SysSourceGetSourceType() == _SOURCE_DP))
    {
        return _TYPE_C_ALT_MODE_READY;
    }

    // Use I2C to Update Alt. Mode Status Every 500ms, Otherwise Return Status in Source Handler
    if(GET_D6_DP_TYPE_C_DETECT_ALT_MODE() == _FALSE)
    {
        return (EnumTypeCAltModeStatus)GET_D6_DP_TYPE_C_ALTMODE_STATUS();
    }

    // CLR Type-C Detect Alt Mode Flag, Wait At Least 500ms to Read 5400 PD Info Via IIC
    CLR_D6_DP_TYPE_C_DETECT_ALT_MODE();
    ScalerTimerActiveTimerEvent(SEC(0.5), _SYSTEM_TIMER_EVENT_D6_TYPE_C_CABLE_DETECT);

    // Read 5400 Info Via IIC Command
    if(UserCommonPortControllerGet5400InfoByI2C(_D6_INPUT_PORT, _5400_ALT_MODE_READY, &ucReadInfo) == _SUCCESS)
    {
        if(ucReadInfo == _TYPE_C_ALT_MODE_READY)
        {
            return _TYPE_C_ALT_MODE_READY;
        }
        else
        {
            return _TYPE_C_ALT_MODE_NOT_READY;
        }
    }
    else
    {
        DebugMessageSystem("8. Read 5400 D6 Alt Mode Ready By IIC Fail", 0);

        return _TYPE_C_ALT_MODE_NOT_READY;
    }
}

#endif // End of #if(_D6_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
#endif // End of #if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)


//--------------------------------------------------
// Description  : Return Port Controller Alt Mode Pin Assignment to SysTypeC
// Input Value  : None
// Output Value : _SUCCESS / _FAIL
//--------------------------------------------------
bit UserCommonPortControllerGet5400PinAssignment(BYTE ucInputPort, EnumTypeCPinCfgType *penumPinAssignment)
{
    BYTE ucDataRole = 0x00;
    BYTE ucPinAssignment = _TYPE_C_PIN_ASSIGNMENT_NONE;

    // Get Data Role Info
    if(UserCommonPortControllerGet5400InfoByI2C(ucInputPort, _5400_DATA_ROLE, &ucDataRole) == _FAIL)
    {
        return _FAIL;
    }

    // Set Data Role
    DebugMessageSystem("8. Get 5400 Data Role = ", ucDataRole);

    if(ucDataRole == _TYPE_C_DFP_U)
    {
        SET_TYPE_C_5400_DATA_ROLE(ucInputPort, _TYPE_C_DFP_U);
    }
    else
    {
        SET_TYPE_C_5400_DATA_ROLE(ucInputPort, _TYPE_C_UFP_U);
    }

    // Get Pin Assignment
    if(UserCommonPortControllerGet5400InfoByI2C(ucInputPort, _5400_PIN_ASSIGNMENT, &ucPinAssignment) == _FAIL)
    {
        return _FAIL;
    }

    *penumPinAssignment = (EnumTypeCPinCfgType)ucPinAssignment;

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Get Port Controller Slave Address
// Input Value  : ucInputPort --> Input Port
// Output Value : Slave Address
//--------------------------------------------------
BYTE UserCommonPortControllerGetPCAddr(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
        case _D0_INPUT_PORT:
            return _D0_DP_TYPE_C_PORT_CTRL_SLAVE_ADDR;

        case _D1_INPUT_PORT:
            return _D1_DP_TYPE_C_PORT_CTRL_SLAVE_ADDR;

        case _D2_INPUT_PORT:
            return _D2_DP_TYPE_C_PORT_CTRL_SLAVE_ADDR;

        case _D6_INPUT_PORT:
            return _D6_DP_TYPE_C_PORT_CTRL_SLAVE_ADDR;

        default:
            break;
    }

    return _D0_DP_TYPE_C_PORT_CTRL_SLAVE_ADDR;
}

//--------------------------------------------------
// Description  : Read 5400/5411 Info by SMBus
// Input Value  : None
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
bit UserCommonPortControllerGet5400InfoByI2C(BYTE ucInputPort, Enum5400InfoType enum5400InfoType, BYTE *pucReadInfo)
{
    BYTE ucSlaveAddr = UserCommonPortControllerGetPCAddr(ucInputPort);

    // Write Command to 5400 According to Different Required Info Type
    if(UserCommonPortControllerWrite5400Command(ucInputPort, ucSlaveAddr, enum5400InfoType) == _FAIL)
    {
        DebugMessageSystem("8. IIC Write Command to 5400 Fail", 0);

        return _FAIL;
    }

    // Polling Write Command Operation Status
    if(UserCommonTypecCommunicationPollingPDReady(ucSlaveAddr, 100, ucInputPort) == _FAIL)
    {
        DebugMessageSystem("8. IIC Polling 5400 Fail", 0);

        return _FAIL;
    }

    // Read Info From 5400 According to Different Required Info Type
    if(UserCommonPortControllerRead5400Command(ucInputPort, ucSlaveAddr, enum5400InfoType) == _FAIL)
    {
        DebugMessageSystem("8. IIC Read 5400 Info Fail", 0);

        return _FAIL;
    }

    // Decode Required Info According to Required Info
    switch(enum5400InfoType)
    {
        case _5400_CC_ATTACH:

            if((g_unSMBusRdDataPool.stRdGetICStatus.ucPDTypeCStatus & _BIT3) == _BIT3)
            {
                *pucReadInfo = _TYPE_C_ATTACH;
            }
            else
            {
                *pucReadInfo = _TYPE_C_UNATTACH;
            }

            break;

        case _5400_ALT_MODE_READY:

            if((g_unSMBusRdDataPool.stRdGetStatus.ucByte13_AltModeStatus & 0x07) == 0x06)
            {
                *pucReadInfo = _TYPE_C_ALT_MODE_READY;
            }
            else
            {
                *pucReadInfo = _TYPE_C_ALT_MODE_NOT_READY;
            }

            break;

        case _5400_DATA_ROLE:

            if(((g_unSMBusRdDataPool.stRdGetStatus.ucByte10_DFP_UFP & (_BIT2 | _BIT1 | _BIT0)) == _BIT2) || ((g_unSMBusRdDataPool.stRdGetStatus.ucByte10_DFP_UFP & (_BIT2 | _BIT1 | _BIT0)) == _BIT1))
            {
                *pucReadInfo = _TYPE_C_DFP_U;
            }
            else
            {
                *pucReadInfo = _TYPE_C_UFP_U;
            }

            break;

        case _5400_POWER_ROLE:

            if((g_unSMBusRdDataPool.stRdGetStatus.ucByte4 & (_BIT6)) == _BIT6)
            {
                *pucReadInfo = _TYPE_C_POWER_SRC;
            }
            else
            {
                *pucReadInfo = _TYPE_C_POWER_SNK;
            }

            break;

        case _5400_CONNECT_FUJITSU:

            if((g_unSMBusRdDataPool.stRdGetStatus.ucByte13_AltModeStatus & _BIT7) == _BIT7)
            {
                *pucReadInfo = _TRUE;
            }
            else
            {
                *pucReadInfo = _FALSE;
            }

            break;

        case _5400_PIN_ASSIGNMENT:

            *pucReadInfo = (BYTE)(UserCommonPortControllerDecode5400PinAssignment(g_unSMBusRdDataPool.stRdDPlanesCfg.ucDPCfgPinConfig));

            if(*pucReadInfo == _TYPE_C_PIN_ASSIGNMENT_NONE)
            {
                return _FAIL;
            }

            break;

        case _5400_CABLE_VID:

            // ========================= Example ===========================
            // BYTE ucVidInfo[2] = {0x00, 0x00};
            // UserCommonPortControllerGet5400InfoByI2C(_D0_INPUT_PORT, _5400_CABLE_VID, &ucVidInfo);
            // ucVidInfo[0] = Vid_High / ucVidInfo[1] = Vid_Low
            // =============================================================
            *pucReadInfo = g_unSMBusRdDataPool.stRdGetCableInfo.ucVid_High;
            *(pucReadInfo + 1) = g_unSMBusRdDataPool.stRdGetCableInfo.ucVid_Low;

            break;

        case _5400_CABLE_PID:

            *pucReadInfo = g_unSMBusRdDataPool.stRdGetCableInfo.ucPid_High;
            *(pucReadInfo + 1) = g_unSMBusRdDataPool.stRdGetCableInfo.ucPid_Low;


            break;

        default:

            return _FAIL;

            break;
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Write SMBus Command to 5400
// Input Value  : ucInputPort, ucSlaveAddr, enum5400InfoType
// Output Value : Communication Result (Fail/Success)
//--------------------------------------------------
bit UserCommonPortControllerWrite5400Command(BYTE ucInputPort, BYTE ucSlaveAddr, Enum5400InfoType enum5400InfoType)
{
    bit bResult = _FAIL;

    switch(enum5400InfoType)
    {
        case _5400_CC_ATTACH:

            // UserCommonPortControllerGetPCStatus : tSMBusWrCmdGetICStatus
            bResult = UserCommonTypecCommunicationWrite(ucSlaveAddr, tSMBusWrCmdGetICStatus[0].ucCommandCode, 1, tSMBusWrCmdGetICStatus[0].ucDataLength + 1, &(tSMBusWrCmdGetICStatus[0].ucDataLength), ucInputPort);

            break;

        case _5400_ALT_MODE_READY:
        case _5400_DATA_ROLE:
        case _5400_POWER_ROLE:
        case _5400_CONNECT_FUJITSU:

            // UserCommonPortControllerGetStatus : tSMBusWrGetStatus
            bResult = UserCommonTypecCommunicationWrite(ucSlaveAddr, tSMBusWrGetStatus[0].ucCommandCode, 1, tSMBusWrGetStatus[0].ucDataLength + 1, ((BYTE *)&tSMBusWrGetStatus[0].ucDataLength), ucInputPort);

            break;

        case _5400_PIN_ASSIGNMENT:

            // UserCommonPortControllerGetPCCfgVdoSelf (tSMBusWrCmdReadDPCfgVdoSelf) + UserCommonPortControllerGetCapVdoSrc (tSMBusWrCmdReadDPCfgVdoPartner)
            if(GET_TYPE_C_5400_DATA_ROLE(ucInputPort) == _TYPE_C_DFP_U)
            {
                bResult = UserCommonTypecCommunicationWrite(ucSlaveAddr, tSMBusWrCmdReadDPCfgVdoSelf[0].ucCommandCode, 1, tSMBusWrCmdReadDPCfgVdoSelf[0].ucDataLength + 1, ((BYTE *)&tSMBusWrCmdReadDPCfgVdoSelf[0].ucDataLength), ucInputPort);
            }
            else
            {
                bResult = UserCommonTypecCommunicationWrite(ucSlaveAddr, tSMBusWrCmdReadDPCfgVdoPartner[0].ucCommandCode, 1, tSMBusWrCmdReadDPCfgVdoPartner[0].ucDataLength + 1, ((BYTE *)&tSMBusWrCmdReadDPCfgVdoPartner[0].ucDataLength), ucInputPort);
            }

            break;

        case _5400_CABLE_VID:
        case _5400_CABLE_PID:

            bResult = UserCommonTypecCommunicationWrite(ucSlaveAddr, tSMBusWrCmdGetCableInfo[0].ucCommandCode, 1, tSMBusWrCmdGetCableInfo[0].ucDataLength + 1, &(tSMBusWrCmdGetCableInfo[0].ucDataLength), ucInputPort);

            break;

        default:

            break;
    }

    return bResult;
}

//--------------------------------------------------
// Description  : Read Info From 5400
// Input Value  : ucInputPort, ucSlaveAddr, enum5400InfoType
// Output Value : Communication Result (Fail/Success)
//--------------------------------------------------
bit UserCommonPortControllerRead5400Command(BYTE ucInputPort, BYTE ucSlaveAddr, Enum5400InfoType enum5400InfoType)
{
    bit bResult = _FAIL;

    switch(enum5400InfoType)
    {
        case _5400_CC_ATTACH:

            // UserCommonPortControllerGetPCStatus : tSMBusWrCmdGetICStatus
            bResult = UserCommonTypecCommunicationRead(ucSlaveAddr, tSMBusRdCmdGetICStatus[0].ucCommandCode, 1, tSMBusRdCmdGetICStatus[0].ucDataLength, &(g_unSMBusRdDataPool.stRdGetICStatus.ucByte7), ucInputPort);

            g_unSMBusRdDataPool.stRdGetICStatus.ucCommandCode = tSMBusRdCmdGetICStatus[0].ucCommandCode;

            break;

        case _5400_ALT_MODE_READY:
        case _5400_DATA_ROLE:
        case _5400_POWER_ROLE:
        case _5400_CONNECT_FUJITSU:

            // UserCommonPortControllerGetStatus : tSMBusWrGetStatus
            bResult = UserCommonTypecCommunicationRead(ucSlaveAddr, tSMBusRDGetStatus[0].ucCommandCode, 1, tSMBusRDGetStatus[0].ucDataLength, &(g_unSMBusRdDataPool.stRdGetStatus.ucDataLength), ucInputPort);

            g_unSMBusRdDataPool.stRdGetStatus.ucCommandCode = tSMBusRDGetStatus[0].ucCommandCode;

            break;

        case _5400_PIN_ASSIGNMENT:

            // UserCommonPortControllerGetPCCfgVdoSelf (tSMBusWrCmdReadDPCfgVdoSelf) + UserCommonPortControllerGetCapVdoSrc (tSMBusWrCmdReadDPCfgVdoPartner)
            bResult = UserCommonTypecCommunicationRead(ucSlaveAddr, tSMBusRdCmdReadDPCfgVdo[0].ucCommandCode, 1, tSMBusRdCmdReadDPCfgVdo[0].ucDataLength, &(g_unSMBusRdDataPool.stRdDPlanesCfg.ucDataLength), ucInputPort);

            g_unSMBusRdDataPool.stRdDPlanesCfg.ucCommandCode = tSMBusRdCmdReadDPCfgVdo[0].ucCommandCode;

            break;

        case _5400_CABLE_VID:
        case _5400_CABLE_PID:

            bResult = UserCommonTypecCommunicationRead(ucSlaveAddr, tSMBusRdCmdGetCableInfo[0].ucCommandCode, 1, tSMBusRdCmdGetCableInfo[0].ucDataLength, &(g_unSMBusRdDataPool.stRdGetCableInfo.ucDataLength), ucInputPort);

            g_unSMBusRdDataPool.stRdGetCableInfo.ucCommandCode = tSMBusRdCmdGetCableInfo[0].ucCommandCode;

            break;

        default:

            break;
    }

    return bResult;
}

//--------------------------------------------------
// Description  : Decode Pin Assignment According to 5400 PD Info
// Input Value  : ucPdInfo --> Data Role BYTE From PD Info
// Output Value : EnumTypeCPinCfgtType : _TYPE_C_PIN_ASSIGNMENT_C / D / E
//--------------------------------------------------
EnumTypeCPinCfgType UserCommonPortControllerDecode5400PinAssignment(BYTE ucPdInfo)
{
    // Is it possible to Merge DFP/UFP Flow together, and maybe use "Switch case"
    if((ucPdInfo & _BIT5) == _BIT5) // Pin Assignment F 2 lane only
    {
        return _TYPE_C_PIN_ASSIGNMENT_F;
    }
    else if((ucPdInfo & _BIT4) == _BIT4) // Pin Assignment E (google cable case)
    {
        return _TYPE_C_PIN_ASSIGNMENT_E;
    }
    else if((ucPdInfo & _BIT3) == _BIT3) // Pin Assignment D 2 lane only, Spec require sink report capability include C  mode
    {
        return _TYPE_C_PIN_ASSIGNMENT_D;
    }
    else if((ucPdInfo & _BIT2) == _BIT2) // Pin Assignment C 4 lane only
    {
        return _TYPE_C_PIN_ASSIGNMENT_C;
    }
    else
    {
        DebugMessageSystem("8. Decode 5400 Pin Assignment Info Error", ucPdInfo);
        return _TYPE_C_PIN_ASSIGNMENT_NONE;
    }
}

//--------------------------------------------------
// Description  : Ask User Port Controller to Reconnect
// Input Value  : ucInputPort --> Input Port
// Output Value : Operation result (Fail/Success)
//--------------------------------------------------
bit UserCommonPortController5400Reconnect(BYTE ucInputPort)
{
    BYTE ucSlaveAddr = UserCommonPortControllerGetPCAddr(ucInputPort);

    if(UserCommonTypecCommunicationWrite(ucSlaveAddr, tSMBusWrCmdSetReconnect[0].ucCommandCode, 1, tSMBusWrCmdSetReconnect[0].ucDataLength + 1, &(tSMBusWrCmdSetReconnect[0].ucDataLength), ucInputPort) == _FAIL)
    {
        DebugMessageSystem("ReConnet Fail Wr fail", 1);

        return _FAIL;
    }

    // Polling Write Command Operation Status
    if(UserCommonTypecCommunicationPollingPDReady(ucSlaveAddr, 500, ucInputPort) == _FAIL)
    {
        DebugMessageSystem("ReConnet Polling Fail ", 1);

        return _FAIL;
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Config Pin Assignment to 5400 Port Controller
// Input Value  : ucInputPort / ucPinAssignment / ucDataRole
// Output Value : Operation result (Fail/Success)
//--------------------------------------------------
bit UserCommonPortControllerConfig5400PinAssignment(BYTE ucInputPort, EnumTypeCPinCfgCapType enumPinAssignment)
{
    StructSMBusWRSetDPLanes stDpLaneConfigPar;
    BYTE ucSlaveAddr = UserCommonPortControllerGetPCAddr(ucInputPort);

    if(GET_TYPE_C_5400_DATA_ROLE(ucInputPort) == _TYPE_C_DFP_U)
    {
        memcpy(&stDpLaneConfigPar, &tSMBusWrCmdSetDPCfgVdoSelf[0], tSMBusWrCmdSetDPCfgVdoSelf[0].ucDataLength + 2);

        stDpLaneConfigPar.ucDPCapVDOByte1 = enumPinAssignment;
    }
    else
    {
        memcpy(&stDpLaneConfigPar, &tSMBusWrCmdSetDPCapVdoSelf[0], tSMBusWrCmdSetDPCapVdoSelf[0].ucDataLength + 2);

        stDpLaneConfigPar.ucDPCapVDOByte2 = enumPinAssignment;
    }

    // Execute Write Command
    if(UserCommonTypecCommunicationWrite(ucSlaveAddr, stDpLaneConfigPar.ucCommandCode, 1, stDpLaneConfigPar.ucDataLength + 1, &stDpLaneConfigPar.ucDataLength, ucInputPort) == _FAIL)
    {
        return _FAIL;
    }

    // Polling Write Command Operation Status
    if(UserCommonTypecCommunicationPollingPDReady(ucSlaveAddr, 100, ucInputPort) == _FAIL)
    {
        return _FAIL;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Config Multi-Function Bit to 5400 Port Controller
// Input Value  : ucInputPort / Nulti-Function Bit
// Output Value : Operation result (Fail/Success)
//--------------------------------------------------
bit UserCommonPortControllerConfig5400MultiFunction(BYTE ucInputPort, EnumTypeCMultiFuncStatus enumMultiFunction)
{
    StructSMBusWRSetDPMultiFunction stMultiFunction;
    BYTE ucSlaveAddr = UserCommonPortControllerGetPCAddr(ucInputPort);

    memcpy(&stMultiFunction, &tSMBusWrCmdSetDPMultiFunction[0], tSMBusWrCmdSetDPMultiFunction[0].ucDataLength + 2);

    // Only UFP Shoud Set Multi Function Preferred Bit
    // BIT[7:5] Reserved, BIT[6] : Exit Mode, BIT[5] USB Config Req, BIT[4] Multi-Function, BIT[3] DP Enable, BIT[2] Power Low, BIT[1:0] Connect Status (b'10 UFP_D Connected)
    if((GET_TYPE_C_5400_DATA_ROLE(ucInputPort) == _TYPE_C_UFP_U) && (enumMultiFunction == _TYPE_C_MULTI_FUNC_PREFER))
    {
        // Set to Multifunction Prefer
        stMultiFunction.ucDPCapVDOByte0 = 0x1A;
    }
    else
    {
        // Set to Multifunction Not Prefer
        stMultiFunction.ucDPCapVDOByte0 = 0x0A;
    }

    // Execute Write Command
    if(UserCommonTypecCommunicationWrite(ucSlaveAddr, stMultiFunction.ucCommandCode, 1, stMultiFunction.ucDataLength + 1, &stMultiFunction.ucDataLength, ucInputPort) == _FAIL)
    {
        return _FAIL;
    }

    // Polling Write Command Operation Status
    if(UserCommonTypecCommunicationPollingPDReady(ucSlaveAddr, 100, ucInputPort) == _FAIL)
    {
        return _FAIL;
    }

    return _TRUE;
}

#if(_TYPE_C_RTS5400_SERIES_PDO_INFO_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Read 5400 PDO Status
// Input Value  : ucInputPort, Voltage (100mV) / Current (50mA)
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
bit UserCommonPortControllerGet5400PDOStatus(BYTE ucInputPort, BYTE *pucVoltage, BYTE *pucCurrent)
{
    BYTE ucSlaveAddr = UserCommonPortControllerGetPCAddr(ucInputPort);

    // Check if Alt Mode is Ready
    if(SysTypeCGetAltModeReady(ucInputPort) == _FALSE)
    {
        return _FAIL;
    }

    // Execute Write Command
    if(UserCommonTypecCommunicationWrite(ucSlaveAddr, tSMBusWrCmdGetPDOPartnerStatus[0].ucCommandCode, 1, tSMBusWrCmdGetPDOPartnerStatus[0].ucDataLength + 1, ((BYTE *)&tSMBusWrCmdGetPDOPartnerStatus[0].ucDataLength), ucInputPort) == _FAIL)
    {
        return _FAIL;
    }

    // Polling Write Command Operation Status
    if(UserCommonTypecCommunicationPollingPDReady(ucSlaveAddr, 100, ucInputPort) == _FAIL)
    {
        return _FAIL;
    }

    // Read Back Device Reply Data
    if(UserCommonTypecCommunicationRead(ucSlaveAddr, tSMBusRdCmdGetPDOPartnerStatus[0].ucCommandCode, 1, tSMBusRdCmdGetPDOPartnerStatus[0].ucDataLength, &(g_unSMBusRdDataPool.stRdGetPDOStatus.ucDataLength), ucInputPort) == _FAIL)
    {
        return _FAIL;
    }

    // Fill in Original Subcommand Code for g_unSMBusRdDataPool structure
    g_unSMBusRdDataPool.stRdGetPDOStatus.ucCommandCode = tSMBusRdCmdGetPDOPartnerStatus[0].ucCommandCode;

    // Convert Voltage From 1V to 100mV
    *pucVoltage = ((((g_unSMBusRdDataPool.stRdGetPDOStatus.ucByte1 & 0xFC) >> 2) + ((g_unSMBusRdDataPool.stRdGetPDOStatus.ucByte2 & 0xFF) << 6)) * 10);

    // Convert Curent From 1A to 50mA
    *pucCurrent = (g_unSMBusRdDataPool.stRdGetPDOStatus.ucByte0 + ((g_unSMBusRdDataPool.stRdGetPDOStatus.ucByte1 & 0x03) << 8)) * 20;

    return _TRUE;
}
#endif

//--------------------------------------------------
// Description  : Enable 5400 Port Controller Vender Command
// Input Value  : ucInputPort --> Input Port
// Output Value : Operation result (Fail/Success)
//--------------------------------------------------
bit UserCommonPortControllerEnable5400VenderCommand(BYTE ucInputPort)
{
    BYTE ucSlaveAddr = UserCommonPortControllerGetPCAddr(ucInputPort);

    if(UserCommonTypecCommunicationWrite(ucSlaveAddr, tSMBusWrCmdEnableVenderCommand[0].ucCommandCode, 1, tSMBusWrCmdEnableVenderCommand[0].ucDataLength + 1, &(tSMBusWrCmdEnableVenderCommand[0].ucDataLength), ucInputPort) == _FAIL)
    {
        return _FAIL;
    }

    // Polling Write Command Operation Status
    if(UserCommonTypecCommunicationPollingPDReady(ucSlaveAddr, 100, ucInputPort) == _FAIL)
    {
        return _FAIL;
    }

    return _SUCCESS;
}
#endif // End of #if(_PORT_CONTROLLER_RTS5400_SERIES_SUPPORT == _ON)
#endif // End of #if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
