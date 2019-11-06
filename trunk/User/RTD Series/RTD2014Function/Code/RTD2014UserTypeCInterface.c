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
// ID Code      : RTD2014UserTypeCInterface.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_TYPECINTERFACE__

#include "UserCommonInclude.h"

#if(_OSD_TYPE == _REALTEK_2014_OSD)
#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of Usb Hub Polling Par
//--------------------------------------------------
#define _USB_D0_HUB_POLLING_DEVICE_STEP         500 // Unit: ms
#define _USB_D1_HUB_POLLING_DEVICE_STEP         500 // Unit: ms
#define _USB_D2_HUB_POLLING_DEVICE_STEP         500 // Unit: ms
#define _USB_D6_HUB_POLLING_DEVICE_STEP         500 // Unit: ms
#define _USB_DX_HUB_POLLING_DEVICE_STEP         500 // Unit: ms

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
EnumTypeCU3ModeType UserInterfaceTypeCGetOsdU3ModeSelection(BYTE ucInputPort);
EnumTypeCPinCfgCapType UserInterfaceTypeCGetPinConfigType(BYTE ucInputPort, EnumTypeCU3ModeType enumU3ModeSel);
void UserInterfaceTypeCPinAssignSuccessProc(BYTE ucInputPort, EnumTypeCPinCfgType enumPinAssignment);

#if(_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
bit UserInterfaceTypeCHubProcSupport(BYTE ucInputPort);
void UserInterfaceTypeCOsdHubProc(BYTE ucInputPort);
WORD UserInterfaceTypeCUsbHubSetPollingStep(BYTE ucInputPort);
bit UserInterfaceTypeCUsbHubDetectDFPStatusUserFlow(BYTE ucInputPort);
bit UserInterfaceTypeCUsbHubSetSSMode(BYTE ucInputPort, bit bEn);
EnumHubDspDetectStatus UserInterfaceTypeCUsbHubDetectDFPStatus(BYTE ucInputPort);
#if(_BILLBOARD_HUB_SUPPORT == _ON)
void UserInterfaceTypeCUsbHubBillboardControl(BYTE ucInputPort, EnumBillboardCtrl enumAtion);
#endif
#endif // End of #if(_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)

#if((_PORT_CTRL_RTS_DET_CONNECTION_BY_USER == _ON) || (_PORT_CTRL_USER_DET_CONNECTION_BY_USER == _ON))
EnumTypeCAttachStatus UserInterfaceTypeCGetPortControllerCcAttach(BYTE ucInputPort);
EnumTypeCAltModeStatus UserInterfaceTypeCGetPortControllerAltModeReady(BYTE ucInputPort);
#endif  // End of #if((_PORT_CTRL_RTS_DET_CONNECTION_BY_USER == _ON) || (_PORT_CTRL_USER_DET_CONNECTION_BY_USER == _ON))

#if(_PORT_CONTROLLER_USERDECITION_SUPPORT == _ON)
bit UserInterfaceTypeCPortControllerReconnect(BYTE ucInputPort);
EnumTypeCUserPortCtrlFailureType UserInterfaceTypeCGetPinCfgType(BYTE ucInputPort, EnumTypeCPinCfgType *penumPinCfgtype);
#endif // End of #if(_USB_HUB_USERDECITION_SUPPORT == _ON)

#if(_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON)
EnumTypeCEmbPdoReference UserInterfaceTypeCPdoReference(BYTE ucInputPort);
WORD UserInterfaceTypeCGetMaxPower(BYTE ucInputPort);
EnumTypeCPdoNumber UserInterfaceTypeCGetPdoCount(BYTE ucInputPort);
void UserInterfaceTypeCGetPdoInfo(BYTE ucInputPort, BYTE ucPdoIndex, StructTypeCUserSrcPDO *pstTypeCUserPdo);
#if(_TYPE_C_EMB_VBUS_PROTECT_MODE == _VBUS_PROTECT_BY_USER)
void UserInterfaceTypeCGetProtectInfo(BYTE ucInputPort, BYTE ucPdoIndex, StructTypeCUserProtectInfo *pstTypeCUserProtectInfo);
#endif
#if(_DP_USB_HUB_SUPPORT == _ON)
EnumHubInputPort UserInterfaceTypeCHubInputPort(BYTE ucInputPort);
#endif
#endif

#if((_PORT_CONTROLLER_RTS5400_SERIES_SUPPORT == _ON) || (_PORT_CONTROLLER_USERDECITION_SUPPORT == _ON))
#if(_TWO_CHIP_DATA_EXCHANGE_MODE == _DATA_EXCHANGE_MODE_NONE)
EnumTypeCPortCtrlReconnectStatus UserInterfaceTypeCPortControllerGetPowerOnReconnectStatus(EnumPowerAction enumSwitch);
#endif
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Get OSD Type-C U3 Mode Selection
// Input Value  : ucInputPort --> Input Port
// Output Value : Return Type-C U3 Mode Selection
//--------------------------------------------------
EnumTypeCU3ModeType UserInterfaceTypeCGetOsdU3ModeSelection(BYTE ucInputPort)
{
    EnumTypeCU3ModeType enumTypeCMode = _TYPE_C_U3_OFF;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _D0_INPUT_PORT:
            enumTypeCMode = GET_OSD_D0_TYPE_C_U3_MODE();
            break;
#endif

#if(_D1_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            enumTypeCMode = GET_OSD_D1_TYPE_C_U3_MODE();
            break;
#endif

#if(_D2_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            enumTypeCMode = GET_OSD_D2_TYPE_C_U3_MODE();
            break;
#endif


#if(_D6_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _D6_INPUT_PORT:
            enumTypeCMode = GET_OSD_D6_TYPE_C_U3_MODE();
            break;
#endif
        default:
            break;
    }

    return enumTypeCMode;
}

//--------------------------------------------------
// Description  : User Decide Sink Pin Config Type
// Input Value  : ucInputPort --> Input Port
// Output Value : Pin Config Capability Type
//--------------------------------------------------
EnumTypeCPinCfgCapType UserInterfaceTypeCGetPinConfigType(BYTE ucInputPort, EnumTypeCU3ModeType enumU3ModeSel)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            switch(enumU3ModeSel)
            {
                case _TYPE_C_U3_ON:

                    // Decide Sink Pin Config Type Capability is _TYPE_C_PIN_ASSIGNMENT_CAP_CDE
                    return _TYPE_C_PIN_ASSIGNMENT_CAP_CDE;

                default:
                case _TYPE_C_U3_OFF:

                    // Decide Sink Pin Config Type Capability is _TYPE_C_PIN_ASSIGNMENT_CAP_CE
                    return _TYPE_C_PIN_ASSIGNMENT_CAP_CE;
            }
#endif

#if(_D1_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            switch(enumU3ModeSel)
            {
                case _TYPE_C_U3_ON:

                    // Decide Sink Pin Config Type Capability is _TYPE_C_PIN_ASSIGNMENT_CAP_CDE
                    return _TYPE_C_PIN_ASSIGNMENT_CAP_CDE;

                default:
                case _TYPE_C_U3_OFF:

                    // Decide Sink Pin Config Type Capability is _TYPE_C_PIN_ASSIGNMENT_CAP_CE
                    return _TYPE_C_PIN_ASSIGNMENT_CAP_CE;
            }
#endif

#if(_D6_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _D6_INPUT_PORT:

            switch(enumU3ModeSel)
            {
                case _TYPE_C_U3_ON:

                    // Decide Sink Pin Config Type Capability is _TYPE_C_PIN_ASSIGNMENT_CAP_CDE
                    return _TYPE_C_PIN_ASSIGNMENT_CAP_CDE;

                default:
                case _TYPE_C_U3_OFF:

                    // Decide Sink Pin Config Type Capability is _TYPE_C_PIN_ASSIGNMENT_CAP_CE
                    return _TYPE_C_PIN_ASSIGNMENT_CAP_CE;
            }
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Switch DP EDID Process by User
// Input Value  : ucInputPort --> Inputput, enumPinAssignment Pin Assignment
// Output Value : None
//--------------------------------------------------
void UserInterfaceTypeCPinAssignSuccessProc(BYTE ucInputPort, EnumTypeCPinCfgType enumPinAssignment)
{
    ucInputPort = ucInputPort;
    enumPinAssignment = enumPinAssignment;
}

#if(_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : User Decide Wether Support USB Hub
// Input Value  : ucInputPort --> Input Port
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit UserInterfaceTypeCHubProcSupport(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            if(GET_OSD_D0_TYPE_C_U3_MODE() == _TYPE_C_U3_ON)
            {
                return _TRUE;
            }
#endif

#if(_D1_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)

        case _D1_INPUT_PORT:

            if(GET_OSD_D1_TYPE_C_U3_MODE() == _TYPE_C_U3_ON)
            {
                return _TRUE;
            }
#endif

#if(_D2_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            if(GET_OSD_D2_TYPE_C_U3_MODE() == _TYPE_C_U3_ON)
            {
                return _TRUE;
            }
#endif

#if(_D6_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _D6_INPUT_PORT:

            if(GET_OSD_D6_TYPE_C_U3_MODE() == _TYPE_C_U3_ON)
            {
                return _TRUE;
            }
#endif

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : User decided how many lanes to switch
// Input Value  : ucInputPort --> Input Port
//                _BIT0 : 1 --> Hub Port0 U3 Device Plug In,  0 --> Hub Port0 U3 Device Plug off
//                _BIT1 : 1 --> Hub Port1 U3 Device Plug In,  0 --> Hub Port1 U3 Device Plug off
//                _BIT2 : 1 --> Hub Port2 U3 Device Plug In,  0 --> Hub Port2 U3 Device Plug off
//                _BIT3 : 1 --> Hub Port3 U3 Device Plug In,  0 --> Hub Port3 U3 Device Plug off
//                _BIT4 ~ _BIT7 : Useless
// Output Value : None
//--------------------------------------------------
void UserInterfaceTypeCOsdHubProc(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
        case _D0_INPUT_PORT:
            // Here: User Can Use "UserCommonUsbHubGetDspInfo(_HUB_DSP0)" to Create Draw Notice U3 Device Menu Event
            break;

        case _D1_INPUT_PORT:
            // Here: User Can Use "UserCommonUsbHubGetDspInfo(_HUB_DSP0)" to Create Draw Notice U3 Device Menu Event
            break;

        case _D6_INPUT_PORT:
            // Here: User Can Use "UserCommonUsbHubGetDspInfo(_HUB_DSP0)" to Create Draw Notice U3 Device Menu Event
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : User Set Usb Hub Polling SS Device Step
// Input Value  : ucInputPort --> Input Port
// Output Value : Usb Hub Polling Step Par.
//--------------------------------------------------
WORD UserInterfaceTypeCUsbHubSetPollingStep(BYTE ucInputPort)
{
    if(ucInputPort == _D0_INPUT_PORT)
    {
        return _USB_D0_HUB_POLLING_DEVICE_STEP;
    }
    else if(ucInputPort == _D1_INPUT_PORT)
    {
        return _USB_D1_HUB_POLLING_DEVICE_STEP;
    }
    else if(ucInputPort == _D2_INPUT_PORT)
    {
        return _USB_D2_HUB_POLLING_DEVICE_STEP;
    }
    else if(ucInputPort == _D6_INPUT_PORT)
    {
        return _USB_D6_HUB_POLLING_DEVICE_STEP;
    }
    else
    {
        return _USB_DX_HUB_POLLING_DEVICE_STEP;
    }
}

//--------------------------------------------------
// Description  : Usb Hub RTS5400 Series User Flow Support
// Input Value  : ucInputPort --> Input Port
// Output Value : _TRUE: User Flow, _FALSE: Kernal Flow
//--------------------------------------------------
bit UserInterfaceTypeCUsbHubDetectDFPStatusUserFlow(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            return _FALSE;

            break;
#endif

#if(_D1_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)

        case _D1_INPUT_PORT:

            return _FALSE;

            break;
#endif

#if(_D6_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _D6_INPUT_PORT:

            return _FALSE;

            break;
#endif

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Set Usb Hub into SS Mode
// Input Value  : None
// Output Value : Operation result (Fail/Success)
//--------------------------------------------------
bit UserInterfaceTypeCUsbHubSetSSMode(BYTE ucInputPort, bit bEn)
{
    ucInputPort = ucInputPort;
    bEn = bEn;

    return _TRUE;
}

//--------------------------------------------------
// Description  : Detect Usb Hub SS Device Plug In
// Input Value  : ucInputPort --> Input Port
// Output Value : Return SS Device Info.
//                _BIT0 : 1 --> Hub Port0 U3 Device Plug In,  0 --> Hub Port0 U3 Device Plug off
//                _BIT1 : 1 --> Hub Port1 U3 Device Plug In,  0 --> Hub Port1 U3 Device Plug off
//                _BIT2 : 1 --> Hub Port2 U3 Device Plug In,  0 --> Hub Port2 U3 Device Plug off
//                _BIT3 : 1 --> Hub Port3 U3 Device Plug In,  0 --> Hub Port3 U3 Device Plug off
//                _BIT4 ~ _BIT7 : Useless
//--------------------------------------------------
EnumHubDspDetectStatus UserInterfaceTypeCUsbHubDetectDFPStatus(BYTE ucInputPort)
{
    ucInputPort = ucInputPort;

    return _HUB_DSP_DEVICE_NO_CHANGE;
}

#if(_BILLBOARD_HUB_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Hub Billboard Control
// Input Value  : _TYPE_C_BB_DISABLE / _TYPE_C_BB_ENABLE
// Output Value : None
//--------------------------------------------------
void UserInterfaceTypeCUsbHubBillboardControl(BYTE ucInputPort, EnumBillboardCtrl enumAtion)
{
    enumAtion = enumAtion;

    switch(ucInputPort)
    {
        case _D0_INPUT_PORT:
            // Here: User Enable / Disable Hub Billboard
            break;

        case _D1_INPUT_PORT:
            // Here: User Enable / Disable Hub Billboard
            break;

        case _D6_INPUT_PORT:
            // Here: User Enable / Disable Hub Billboard
            break;

        default:
            break;
    }
}
#endif // End of #if(_BILLBOARD_HUB_SUPPORT == _ON)
#endif // End of #if(_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)

#if((_PORT_CTRL_RTS_DET_CONNECTION_BY_USER == _ON) || (_PORT_CTRL_USER_DET_CONNECTION_BY_USER == _ON))
//--------------------------------------------------
// Description  : Type-C Port Controller CC Attach Detectd By User Define
// Input Value  : enumSourcePort --> _D0_INPUT_PORT / _D1_INPUT_PORT...
// Output Value : _TYPE_C_ATTACH / _TYPE_C_UNATTACH
//--------------------------------------------------
EnumTypeCAttachStatus UserInterfaceTypeCGetPortControllerCcAttach(BYTE ucInputPort)
{
    EnumTypeCAttachStatus enumCcAttachResult = _TYPE_C_UNATTACH;

    // User Can Use Their Own Way to Decide Port Controller CC Attach or Not, For Example
    // enumCcAttachResult = (GPIO == HIGH) ? _TYPE_C_UNATTACH : _TYPE_C_ATTACH;

    switch(ucInputPort)
    {
#if(((_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)) && (_D0_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_USER_FUNCIOIN))
        case _D0_INPUT_PORT:
#endif
#if(((_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)) && (_D1_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_USER_FUNCIOIN))
        case _D1_INPUT_PORT:
#endif
#if(((_D2_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D2_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)) && (_D2_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_USER_FUNCIOIN))
        case _D2_INPUT_PORT:
#endif
#if(((_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)) && (_D6_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_USER_FUNCIOIN))
        case _D6_INPUT_PORT:
#endif
        default:

            enumCcAttachResult = _TYPE_C_UNATTACH;

            break;
    }

    return enumCcAttachResult;
}

//--------------------------------------------------
// Description  : Type-C Port Controller Alt Mode Ready Detectd By User Define
// Input Value  : enumSourcePort --> _D0_INPUT_PORT / _D1_INPUT_PORT...
// Output Value : _TYPE_C_ALT_MODE_READY / _TYPE_C_ALT_MODE_NOT_READY
//--------------------------------------------------
EnumTypeCAltModeStatus UserInterfaceTypeCGetPortControllerAltModeReady(BYTE ucInputPort)
{
    EnumTypeCAltModeStatus enumAltModeReadyResult = _TYPE_C_ALT_MODE_NOT_READY;

    // User Can Use Their Own Way to Decide Port Controller Alt Mode Ready or Not, For Example
    // enumCcAttachResult = (GPIO == HIGH) ? _TYPE_C_ALT_MODE_NOT_READY : _TYPE_C_ALT_MODE_READY;

    switch(ucInputPort)
    {
#if(((_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)) && (_D0_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_USER_FUNCIOIN))
        case _D0_INPUT_PORT:
#endif
#if(((_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)) && (_D1_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_USER_FUNCIOIN))
        case _D1_INPUT_PORT:
#endif
#if(((_D2_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D2_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)) && (_D2_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_USER_FUNCIOIN))
        case _D2_INPUT_PORT:
#endif
#if(((_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)) && (_D6_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_USER_FUNCIOIN))
        case _D6_INPUT_PORT:
#endif
        default:

            enumAltModeReadyResult = _TYPE_C_ALT_MODE_NOT_READY;

            break;
    }

    return enumAltModeReadyResult;
}
#endif  // End of #if((_PORT_CTRL_RTS_DET_CONNECTION_BY_USER == _ON) || (_PORT_CTRL_USER_DET_CONNECTION_BY_USER == _ON))

#if(_PORT_CONTROLLER_USERDECITION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Port Controller Reconnect
// Input Value  : ucInputPort --> Input Port
// Output Value : return _TRUE / __FALSE
//--------------------------------------------------
bit UserInterfaceTypeCPortControllerReconnect(BYTE ucInputPort)
{
    ucInputPort = ucInputPort;

    return _TRUE;
}

//--------------------------------------------------
// Description  : Port Controller Config Type
// Input Value  : ucInputPort --> Input Port
//                penumPinCfgtype --> Pin Assignment Type
// Output Value : return failure type
//--------------------------------------------------
EnumTypeCUserPortCtrlFailureType UserInterfaceTypeCGetPinCfgType(BYTE ucInputPort, EnumTypeCPinCfgType *penumPinCfgtype)
{
    ucInputPort = ucInputPort; // Avoiding Warning
    *penumPinCfgtype = _TYPE_C_PIN_ASSIGNMENT_C;

    // Example:
    /*
        if(UserGetPortcontrollerConfigPinAssignmentTypeFunc(penumPinCfgtype) == _TRUE)
        {
            return _TYPE_C_USER_PORT_CTRL_COMMUNICATION_SUCCESS;
        }
        else
        {
            return _TYPE_C_USER_PORT_CTRL_COMMUNICATION_FAIL;
        }
    */

    return _TYPE_C_USER_PORT_CTRL_COMMUNICATION_FAIL;
}
#endif // End of #if(_PORT_CONTROLLER_USERDECITION_SUPPORT == _ON)

#if(_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get TypeC PDO From User / Kernel
// Input Value  : ucInputPort --> Input Port
// Output Value : return PDO from USER / KERNEL
//--------------------------------------------------
EnumTypeCEmbPdoReference UserInterfaceTypeCPdoReference(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            // Source Capability Defined By User or Kernel Default
            return _TYPE_C_PDO_FROM_USER;

            break;
#endif

        default:
            break;
    }
    return _TYPE_C_PDO_FROM_KERNEL;
}

//--------------------------------------------------
// Description  : Embedded Port Controller Max Power
// Input Value  : ucInputPort --> Input Port
// Output Value : return Max Power (Unit = 0.1W)
//--------------------------------------------------
WORD UserInterfaceTypeCGetMaxPower(BYTE ucInputPort)
{
    // Max Power Range From 0 ~ 100W
    WORD usEmbTypeCMaxPower = 0;

    // User can use "UserCommonUsbHubGetDspInfo(_HUB_DSP0)" to Create ucHubDeviceCnt logic

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            // User Can Define Different Max Power According to Device Count
            // Default Max Power = 270 * 0.1 = 27W
            usEmbTypeCMaxPower = 270;

            break;
#endif

        default:

            // Default Max Power = 270 * 0.1 = 27W
            usEmbTypeCMaxPower = 270;

            break;
    }

    return usEmbTypeCMaxPower;
}

//--------------------------------------------------
// Description  : Embedded Port Controller PDO Count
// Input Value  : ucInputPort --> Input Port
// Output Value : return Number of PDOs
//--------------------------------------------------
EnumTypeCPdoNumber UserInterfaceTypeCGetPdoCount(BYTE ucInputPort)
{
    // User can use "UserCommonUsbHubGetDspInfo(_HUB_DSP0)" to Create ucHubDeviceCnt logic

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:


#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
            // PPS Support : Default 2 Fix + 1 PPS PDO = 3 PDOs
            return _TYPE_C_PDO_NUM_3;
#else
            // No PPS Support : Default 2 Fix PDO
            return _TYPE_C_PDO_NUM_2;
#endif

            break;
#endif

        default:

            return _TYPE_C_PDO_NUM_2;

            break;
    }
}

//--------------------------------------------------
// Description  : Embedded Port Controller PDO Info
// Input Value  : ucInputPort --> Input Port
//                ucPdoIndex --> PDO Index
//                ucHubDeviceCnt --> Num of USB Device Connected
//                *pstTypeCUserPdo --> PDO Info
// Output Value : None
//--------------------------------------------------
void UserInterfaceTypeCGetPdoInfo(BYTE ucInputPort, BYTE ucPdoIndex, StructTypeCUserSrcPDO *pstTypeCUserPdo)
{
    // User can use "UserCommonUsbHubGetDspInfo()" to Create ucHubDeviceCnt logic

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            switch(ucPdoIndex)
            {
                // =============================== WARNING ===============================
                // 1st PDO Must Be Fix Supply PDO @ 5V
                // ALL PDO Type Must Be In Order : Fix -> PPS
                // ALL PDO Voltage in Same Type Must Be In Order : Lowest To Highest
                // User Can Define Different PDO According to Device Count
                // =======================================================================

                case _TYPE_C_PDO_NUM_1:

                    // ----------------------- 1st PDO ------------------------
                    // PDO Type = Fix Supply PDO, Must Be 5V (Max = 5A)
                    // Max Voltage (Unit = 100mV) : 50 * 100mV = 5V
                    // Max Current (Unit = 50mA)  : 60 *  50mA = 3A
                    // --------------------------------------------------------
                    pstTypeCUserPdo->enumPdoType = _PD_FIX_SUPPLY_PDO;
                    pstTypeCUserPdo->ucMaxVoltage = 50;
                    pstTypeCUserPdo->ucMaxCurrent = 60;

                    break;

                case _TYPE_C_PDO_NUM_2:

                    // ----------------------- 2nd PDO ------------------------
                    // PDO Type = Fix Supply PDO (Max = 20V / 5A)
                    // Max Voltage (Unit = 100mV) : 90 * 100mV = 9V
                    // Max Current (Unit = 50mA)  : 60 *  50mA = 3A
                    // --------------------------------------------------------
                    pstTypeCUserPdo->enumPdoType = _PD_FIX_SUPPLY_PDO;
                    pstTypeCUserPdo->ucMaxVoltage = 90;
                    pstTypeCUserPdo->ucMaxCurrent = 60;

                    break;

                case _TYPE_C_PDO_NUM_3:

#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
                    // -------------- 3rd PDO (PPS PDO Example) ---------------
                    // PDO Type = Fix Supply PDO (Max = 20V / 5A)
                    // Spec 9V Prog PDO = 3~11V @ 3A
                    // Min Voltage (Unit = 100mV) : 30 * 100mV = 3V
                    // Max Voltage (Unit = 100mV) : 90 * 100mV = 9V
                    // Max Current (Unit = 50mA)  : 60 *  50mA = 3A
                    // --------------------------------------------------------
                    pstTypeCUserPdo->enumPdoType = _PD_3_PROGRAMMABLE_PDO;
                    pstTypeCUserPdo->ucMinVoltage = 30;
                    pstTypeCUserPdo->ucMaxVoltage = 90;
                    pstTypeCUserPdo->ucMaxCurrent = 60;
#endif
                    break;

                case _TYPE_C_PDO_NUM_4:
                case _TYPE_C_PDO_NUM_5:
                case _TYPE_C_PDO_NUM_6:
                case _TYPE_C_PDO_NUM_7:
                default:

                    break;
            }


            break;
#endif  // End of #if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)

        default:

            break;
    }
}

#if(_TYPE_C_EMB_VBUS_PROTECT_MODE == _VBUS_PROTECT_BY_USER)
//--------------------------------------------------
// Description  : Embedded Port Controller Protect Info
// Input Value  : ucInputPort --> Input Port
//                ucPdoIndex --> PDO Index
//                *pstTypeCUserProtectInfo --> Protect Info
// Output Value : None
//--------------------------------------------------
void UserInterfaceTypeCGetProtectInfo(BYTE ucInputPort, BYTE ucPdoIndex, StructTypeCUserProtectInfo *pstTypeCUserProtectInfo)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            switch(ucPdoIndex)
            {
                case _TYPE_C_PDO_NUM_1:

                    pstTypeCUserProtectInfo->ucOcpCurRatio = 105;

                    break;

                case _TYPE_C_PDO_NUM_2:

                    pstTypeCUserProtectInfo->ucOcpCurRatio = 105;

                    break;

                case _TYPE_C_PDO_NUM_3:

#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
                    pstTypeCUserProtectInfo->ucOcpCurRatio = 105;
#endif
                    break;

                case _TYPE_C_PDO_NUM_4:
                case _TYPE_C_PDO_NUM_5:
                case _TYPE_C_PDO_NUM_6:
                case _TYPE_C_PDO_NUM_7:
                default:

                    break;
            }

            break;
#endif

        default:
            break;
    }
}
#endif

#if(_DP_USB_HUB_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Return Hub Input Port to Kernel
// Input Value  : ucInputPort
// Output Value : EnumHubInputPort
//--------------------------------------------------
EnumHubInputPort UserInterfaceTypeCHubInputPort(BYTE ucInputPort)
{
    EnumHubInputPort enumHubInputPort = _HUB_UFP_TYPE_C_INPUT_PORT;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_USB_HUB_TYPE != _USB_HUB_NONE)
        case _D0_INPUT_PORT:

            if(GET_USER_USB_HUB_UFP_SWITCH() == _HUB_UFP_TYPE_C_INPUT_PORT)
            {
                enumHubInputPort = _HUB_UFP_TYPE_C_INPUT_PORT;
            }
            else
            {
                enumHubInputPort = _HUB_UFP_NOT_TYPE_C_INPUT_PORT;
            }

            break;
#endif

        default:

            break;
    }

    return enumHubInputPort;
}
#endif
#endif // End of #if(_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON)

#if((_PORT_CONTROLLER_RTS5400_SERIES_SUPPORT == _ON) || (_PORT_CONTROLLER_USERDECITION_SUPPORT == _ON))
#if(_TWO_CHIP_DATA_EXCHANGE_MODE == _DATA_EXCHANGE_MODE_NONE)
EnumTypeCPortCtrlReconnectStatus UserInterfaceTypeCPortControllerGetPowerOnReconnectStatus(EnumPowerAction enumSwitch)
{
    switch(enumSwitch)
    {
        case _POWER_ACTION_OFF_TO_NORMAL:
        case _POWER_ACTION_PS_TO_NORMAL:

            if(GET_TYPE_C_PORT_CTRL_POWER_OFF_FLG() == _TRUE)
            {
                return _TYPE_C_PORT_CTRL_RECONNECT;
            }
            else
            {
                return _TYPE_C_PORT_CTRL_NO_RECONNECT;
            }

            break;

        default:

            return _TYPE_C_PORT_CTRL_NO_RECONNECT;

            break;
    }

    return _TYPE_C_PORT_CTRL_NO_RECONNECT;
}
#endif
#endif // End of #if((_PORT_CONTROLLER_RTS5400_SERIES_SUPPORT == _ON) || (_PORT_CONTROLLER_USERDECITION_SUPPORT == _ON))

#endif // End of #if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
#endif // End of #if(_OSD_TYPE == _REALTEK_2014_OSD)
