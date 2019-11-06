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
// ID Code      : UserCommonPortControllerUser.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_PORTCONTROLLERUSER__

#include "UserCommonInclude.h"

#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#if(_PORT_CONTROLLER_USERDECITION_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)
#if(_D0_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
EnumTypeCAttachStatus UserCommonPortControllerGetD0CcAttachByI2C(void);
EnumTypeCAltModeStatus UserCommonPortControllerGetD0AltModeReadyByI2C(void);
#endif
#endif

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)
#if(_D1_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
EnumTypeCAttachStatus UserCommonPortControllerGetD1CcAttachByI2C(void);
EnumTypeCAltModeStatus UserCommonPortControllerGetD1AltModeReadyByI2C(void);
#endif
#endif

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)
#if(_D6_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
EnumTypeCAttachStatus UserCommonPortControllerGetD6CcAttachByI2C(void);
EnumTypeCAltModeStatus UserCommonPortControllerGetD6AltModeReadyByI2C(void);
#endif
#endif

bit UserCommonPortControllerGetUserPinAssignment(BYTE ucInputPort, EnumTypeCPinCfgType *penumPinAssignment);
bit UserCommonPortControllerUserReconnect(BYTE ucInputPort);
bit UserCommonPortControllerConfigUserPinAssignment(BYTE ucInputPort, EnumTypeCPinCfgCapType enumPinAssignment);
bit UserCommonPortControllerConfigUserMultiFunction(BYTE ucInputPort, EnumTypeCMultiFuncStatus enumMultiFunction);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)
#if(_D0_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
//--------------------------------------------------
// Description  : Get D0 CC Attached Info Through I2C
// Input Value  : None
// Output Value : CC Attach (_TRUE / _FALSE)
//--------------------------------------------------
EnumTypeCAttachStatus UserCommonPortControllerGetD0CcAttachByI2C(void)
{
    return _TYPE_C_UNATTACH;
}

//--------------------------------------------------
// Description  : Get D0 Alt Mode Ready Info Through I2C
// Input Value  : None
// Output Value : CC Attach (_TRUE / _FALSE)
//--------------------------------------------------
EnumTypeCAltModeStatus UserCommonPortControllerGetD0AltModeReadyByI2C(void)
{
    return _TYPE_C_ALT_MODE_NOT_READY;
}

#endif  // End of #if(_D0_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
#endif  // End of #if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)
#if(_D1_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
//--------------------------------------------------
// Description  : Get D1 CC Attached Info Through I2C
// Input Value  : None
// Output Value : CC Attach (_TRUE / _FALSE)
//--------------------------------------------------
EnumTypeCAttachStatus UserCommonPortControllerGetD1CcAttachByI2C(void)
{
    return _TYPE_C_UNATTACH;
}

//--------------------------------------------------
// Description  : Get D1 Alt Mode Ready Info Through I2C
// Input Value  : None
// Output Value : CC Attach (_TRUE / _FALSE)
//--------------------------------------------------
EnumTypeCAltModeStatus UserCommonPortControllerGetD1AltModeReadyByI2C(void)
{
    return _TYPE_C_ALT_MODE_NOT_READY;
}
#endif  // End of #if(_D1_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
#endif  // End of #if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)
#if(_D6_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
//--------------------------------------------------
// Description  : Get D6 CC Attached Info Through I2C
// Input Value  : None
// Output Value : CC Attach (_TRUE / _FALSE)
//--------------------------------------------------
EnumTypeCAttachStatus UserCommonPortControllerGetD6CcAttachByI2C(void)
{
    return _TYPE_C_UNATTACH;
}

//--------------------------------------------------
// Description  : Get D6 Alt Mode Ready Info Through I2C
// Input Value  : None
// Output Value : CC Attach (_TRUE / _FALSE)
//--------------------------------------------------
EnumTypeCAltModeStatus UserCommonPortControllerGetD6AltModeReadyByI2C(void)
{
    return _TYPE_C_ALT_MODE_NOT_READY;
}
#endif  // End of #if(_D6_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
#endif  // End of #if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)

//--------------------------------------------------
// Description  : Return Port Controller Alt Mode Pin Assignment to SysTypeC
// Input Value  : None
// Output Value : _SUCCESS / _FAIL
//--------------------------------------------------
bit UserCommonPortControllerGetUserPinAssignment(BYTE ucInputPort, EnumTypeCPinCfgType *penumPinAssignment)
{
    EnumTypeCPinCfgType enumPinCfgtype = _TYPE_C_PIN_ASSIGNMENT_C;

    // Read User Port Controller Alt Mode Pin Assignment Info
    if(UserInterfaceTypeCGetPinCfgType(ucInputPort, &enumPinCfgtype) == _TYPE_C_USER_PORT_CTRL_COMMUNICATION_FAIL)
    {
        DebugMessageSystem("8. Get User Port Controller Pin Assignment Type Fail", 0);

        return _FAIL;
    }

    *penumPinAssignment = enumPinCfgtype;

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Ask User Port Controller to Reconnect
// Input Value  : ucInputPort --> Input Port
// Output Value : Operation result (Fail/Success)
//--------------------------------------------------
bit UserCommonPortControllerUserReconnect(BYTE ucInputPort)
{
    // Should We Re-Name this Function to : "UserInterfaceTypeCPortControllerReconnect"
    return UserInterfaceTypeCPortControllerReconnect(ucInputPort);
}

//--------------------------------------------------
// Description  : Config Pin Assignment to User Port Controller
// Input Value  : ucInputPort --> Input Port
// Output Value : Operation result (Fail/Success)
//--------------------------------------------------
bit UserCommonPortControllerConfigUserPinAssignment(BYTE ucInputPort, EnumTypeCPinCfgCapType enumPinAssignment)
{
    ucInputPort = ucInputPort;
    enumPinAssignment = enumPinAssignment;

    return _TRUE;
}

//--------------------------------------------------
// Description  : Config Multi-Function Bit to User Port Controller
// Input Value  : ucInputPort --> Input Port
// Output Value : Operation result (Fail/Success)
//--------------------------------------------------
bit UserCommonPortControllerConfigUserMultiFunction(BYTE ucInputPort, EnumTypeCMultiFuncStatus enumMultiFunction)
{
    ucInputPort = ucInputPort;
    enumMultiFunction = enumMultiFunction;

    return _TRUE;
}

#endif // End of #if(_PORT_CONTROLLER_USERDECITION_SUPPORT == _ON)
#endif // End of #if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
