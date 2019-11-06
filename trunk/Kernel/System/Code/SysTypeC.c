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
// ID Code      : SysTypeC.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SYSTEM_TYPC_C__

#include "SysInclude.h"
#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Time of Type-C Cable Recheck After Reconnected When DP_TYPE_C_CONNECTION_CHECK_WAY != _DISCRETE_PORT_CTRL_USE_GPIO
//--------------------------------------------------
#define _TYPE_C_RESTART_CHECK_CABLE_STATUS_TIME         500 // Restart time 0.5s for after type-c reconnected
#define _TYPE_C_ENABLE_BILLBOARD_TIME                   1000 // Timeout Enable Billboard After CC Attach

#define GET_TYPE_C_STATE(x)                             (g_pstTypeCStatus[SysTypeCGetTypeCIndex(x)].enumTypeCState)
#define SET_TYPE_C_STATE(x, y)                          (g_pstTypeCStatus[SysTypeCGetTypeCIndex(x)].enumTypeCState = (y))

#define GET_TYPE_C_PIN_ASSIGNMENT(x)                    (g_pstTypeCStatus[SysTypeCGetTypeCIndex(x)].enumSPinAssignment)
#define SET_TYPE_C_PIN_ASSIGNMENT(x, y)                 (g_pstTypeCStatus[SysTypeCGetTypeCIndex(x)].enumSPinAssignment = (y))

#define GET_TYPE_C_CAPABILITY_CHG(x)                    (g_pstTypeCStatus[SysTypeCGetTypeCIndex(x)].ucCapChangeFlag)
#define SET_TYPE_C_CAPABILITY_CHG(x, y)                 (g_pstTypeCStatus[SysTypeCGetTypeCIndex(x)].ucCapChangeFlag = (g_pstTypeCStatus[SysTypeCGetTypeCIndex(x)].ucCapChangeFlag | (y)))
#define CLR_TYPE_C_CAPABILITY_CHG(x, y)                 (g_pstTypeCStatus[SysTypeCGetTypeCIndex(x)].ucCapChangeFlag = (g_pstTypeCStatus[SysTypeCGetTypeCIndex(x)].ucCapChangeFlag & (~(y))))

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _TYPE_C_UNATTACH_STATE = 0x00,
    _TYPE_C_ATTACHED_STATE = 0x01,
    _TYPE_C_ALT_MODE_READY_STATE = 0x02,
    _TYPE_C_RECONNECT_STATE = 0x03,
}EnumTypeCState;

// USB Type-C Related Status
typedef struct
{
    EnumTypeCState enumTypeCState;
    // -----------------------------
    EnumTypeCPinCfgType enumSPinAssignment;
    // -----------------------------
    BYTE ucCapChangeFlag;
}StructTypeCStatus;

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructTypeCStatus g_pstTypeCStatus[_TYPE_C_PORT_VALID];

#if(_D0_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
StructUsbHubInfo g_stD0UsbHubInfo;
#endif

#if(_D1_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
StructUsbHubInfo g_stD1UsbHubInfo;
#endif

#if(_D6_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
StructUsbHubInfo g_stD6UsbHubInfo;
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void SysTypeCInitial(void);
void SysTypeCHandler(void);
void SysTypeCUFPHandler(BYTE ucInputPort);
void SysTypeCPowerSwitch(EnumPowerAction enumSwitch);
EnumPdoCheck SysTypeCSetPortCtrlSourceCap(BYTE ucInputPort);
EnumTypeCAttachStatus SysTypeCGetPortControllerCcAttach(BYTE ucInputPort);
EnumTypeCAltModeStatus SysTypeCGetPortControllerAltModeReady(BYTE ucInputPort);
bit SysTypeCGetPortControllerPinAssignment(BYTE ucInputPort);
void SysTypeCSetDpLaneMapping(BYTE ucInputPort, EnumTypeCPinCfgType enumPinAssignment);
bit SysTypeCheckCapabilityChange(BYTE ucInputPort, EnumTypeCCapChgStatus enumCapability);
void SysTypeCUsbCapabilityChangeProc(BYTE ucInputPort);
void SysTypeCSrcCapabilityChangeProc(BYTE ucInputPort);
bit SysTypeCReconnect(BYTE ucInputPort);
void SysTypeCReconnectTransition(BYTE ucInputPort);
bit SysTypeCUpdatePortControllerConfig(BYTE ucInputPort);
bit SysTypeCGetCcAttach(BYTE ucInputPort);
bit SysTypeCGetAltModeReady(BYTE ucInputPort);
EnumTypeCPinCfgType SysTypeCGetPinAssignment(BYTE ucInputPort);
BYTE SysTypeCGetTypeCIndex(BYTE ucInputPort);
EnumDpLaneCount SysTypeCGetAltModeLaneCnt(EnumTypeCPinCfgType enumPinAssignment);
void SysTypeCSwitchOSDLaneCount(BYTE ucInputPort, EnumDpLaneCount enumDpLaneCount);
void SysTypeCSetCapabilityChangeFlag(BYTE ucInputPort, EnumTypeCCapChgStatus enumCapability);
void SysTypeCClrCapabilityChangeFlag(BYTE ucInputPort, EnumTypeCCapChgStatus enumCapability);

#if(((_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D0_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK != _DISCRETE_PORT_CTRL_USE_SMBUS)) || ((_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D1_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK != _DISCRETE_PORT_CTRL_USE_SMBUS)) || ((_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D6_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK != _DISCRETE_PORT_CTRL_USE_SMBUS)))
void SysTypeCSwitchToUnattachState(BYTE ucInputPort);
#endif
void SysTypeCCancelUnattachTimerEvent(BYTE ucInputPort);

#if(_BILLBOARD_SUPPORT == _ON)
void SysTypeCStartBillboardTimer(BYTE ucInputPort, WORD usTimeoutCnt);
void SysTypeCCancelBillboardTimer(BYTE ucInputPort);
void SysTypeCBillboardControl(BYTE ucInputPort, EnumBillboardCtrl enumAtion);
#endif

#if(_DP_USB_HUB_SUPPORT == _ON)
void SysTypeCUsbHubProc(BYTE ucInputPort);
#endif
#if(_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
void SysTypeCUsbHubDetectProc(BYTE ucInputPort);
void SysTypeCUsbHubConfigProc(BYTE ucInputPort, BYTE ucDpLanes);
WORD SysTypeCGetUsbHubSetU3ReadyDelayTime(BYTE ucInputPort);

#if(_D0_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
void SysTypeCD0UsbHubDetectProc(void);
#endif
#if(_D1_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
void SysTypeCD1UsbHubDetectProc(void);
#endif
#if(_D6_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
void SysTypeCD6UsbHubDetectProc(void);
#endif

void SysTypeCOsdHubProc(void);
#endif

#if(_DP_USB_HUB_SUPPORT == _ON)
void SysTypeCHubInputSwitchProc(BYTE ucInputPort);
#endif

#endif // End of #if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
//--------------------------------------------------
// Description  : TypeC AC On Initial Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysTypeCInitial(void)
{
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

    SET_TYPE_C_STATE(_D0_INPUT_PORT, _TYPE_C_UNATTACH_STATE);
    SET_TYPE_C_PIN_ASSIGNMENT(_D0_INPUT_PORT, _TYPE_C_PIN_ASSIGNMENT_NONE);
    SysTypeCClrCapabilityChangeFlag(_D0_INPUT_PORT, _TYPE_C_ALL_STATUS_CHG);
    SysTypeCSetCapabilityChangeFlag(_D0_INPUT_PORT, _TYPE_C_HUB_INPUT_SWITCH_CHG);
    SysTypeCSetPortCtrlSourceCap(_D0_INPUT_PORT);

    DebugMessageSystem("8. [TYPE C] <Step 0/2> D0 CC Unattach", _TYPE_C_ATTACHED_STATE);

#if(_D0_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
    UserCommonPortControllerSetD0I2CDetection();
#endif
#endif  // End Of #if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)


#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

    SET_TYPE_C_STATE(_D1_INPUT_PORT, _TYPE_C_UNATTACH_STATE);
    SET_TYPE_C_PIN_ASSIGNMENT(_D1_INPUT_PORT, _TYPE_C_PIN_ASSIGNMENT_NONE);
    SysTypeCClrCapabilityChangeFlag(_D1_INPUT_PORT, _TYPE_C_ALL_STATUS_CHG);
    SysTypeCSetCapabilityChangeFlag(_D1_INPUT_PORT, _TYPE_C_HUB_INPUT_SWITCH_CHG);
    SysTypeCSetPortCtrlSourceCap(_D1_INPUT_PORT);

    DebugMessageSystem("8. [TYPE C] <Step 0/2> D1 CC Unattach", _TYPE_C_ATTACHED_STATE);

#if(_D1_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
    UserCommonPortControllerSetD1I2CDetection();
#endif
#endif // End Of #if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)


#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

    SET_TYPE_C_STATE(_D6_INPUT_PORT, _TYPE_C_UNATTACH_STATE);
    SET_TYPE_C_PIN_ASSIGNMENT(_D6_INPUT_PORT, _TYPE_C_PIN_ASSIGNMENT_NONE);
    SysTypeCClrCapabilityChangeFlag(_D6_INPUT_PORT, _TYPE_C_ALL_STATUS_CHG);
    SysTypeCSetCapabilityChangeFlag(_D6_INPUT_PORT, _TYPE_C_HUB_INPUT_SWITCH_CHG);
    SysTypeCSetPortCtrlSourceCap(_D6_INPUT_PORT);

    DebugMessageSystem("8. [TYPE C] <Step 0/2> D6 CC Unattach", _TYPE_C_ATTACHED_STATE);

#if(_D6_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
    UserCommonPortControllerSetD6I2CDetection();
#endif
#endif // End Of #if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
}

//--------------------------------------------------
// Description  : PD/CC Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysTypeCHandler(void)
{
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
    // 1. Run PD/CC Proc (For Embedded Port Controller Only)
    ScalerTypeCHandler(_D0_INPUT_PORT, GET_MODE_STATE());

#if(_USB3_RETIMER_SUPPORT == _ON)
    ScalerUSB3RetimerHandler(GET_POWER_STATUS());
#endif
#endif

    // 2. Run DFP Proc According to Port Controller Status (For All Type-C Ports)
    SysTypeCUFPHandler(_D0_INPUT_PORT);

#if(_D0_DP_TYPE_C_USB_HUB_TYPE != _USB_HUB_NONE)
    // 3. Run Hub Proc to Detect if Any Device Connect to Hub
    SysTypeCUsbHubProc(_D0_INPUT_PORT);
#endif
#endif  // End Of #if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)


#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
    ScalerTypeCHandler(_D1_INPUT_PORT, GET_MODE_STATE());
#endif

    SysTypeCUFPHandler(_D1_INPUT_PORT);

#if(_D1_DP_TYPE_C_USB_HUB_TYPE != _USB_HUB_NONE)
    SysTypeCUsbHubProc(_D1_INPUT_PORT);
#endif
#endif  // End Of #if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)


#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
    ScalerTypeCHandler(_D6_INPUT_PORT, GET_MODE_STATE());
#endif

    SysTypeCUFPHandler(_D6_INPUT_PORT);

#if(_D6_DP_TYPE_C_USB_HUB_TYPE != _USB_HUB_NONE)
    SysTypeCUsbHubProc(_D6_INPUT_PORT);
#endif
#endif  // End Of #if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
}

//--------------------------------------------------
// Description  : Type-C Handler Used to Sync Port Controller and Scaler
// Input Value  : ucInputPort --> Inputput
// Output Value : None
//--------------------------------------------------
void SysTypeCUFPHandler(BYTE ucInputPort)
{
    switch(GET_TYPE_C_STATE(ucInputPort))
    {
        case _TYPE_C_UNATTACH_STATE:

            // Check if CC Attached
            if(SysTypeCGetPortControllerCcAttach(ucInputPort) == _TYPE_C_ATTACH)
            {
                DebugMessageSystem("8. [TYPE C] <Step 1/2> CC Attach, Alt Mode Not Ready", _TYPE_C_UNATTACH_STATE);

                SET_TYPE_C_STATE(ucInputPort, _TYPE_C_ATTACHED_STATE);

#if(_BILLBOARD_SUPPORT == _ON)
                // Enable Billboard Function if Alt Mode Not Successfully Entered
                SysTypeCStartBillboardTimer(ucInputPort, _TYPE_C_ENABLE_BILLBOARD_TIME);
#endif
            }
            else
            {
#if(_BILLBOARD_SUPPORT == _ON)
                // Cancel Timer Event(TURN ON BB)
                SysTypeCCancelBillboardTimer(ucInputPort);

                // Disable Billboard When CC Unattach
                SysTypeCBillboardControl(ucInputPort, _TYPE_C_BB_DISABLE);
#endif
            }

            break;

        case _TYPE_C_ATTACHED_STATE:

            // Check if CC Attached
            if(SysTypeCGetPortControllerCcAttach(ucInputPort) == _TYPE_C_ATTACH)
            {
                // Check if PD Has Entered Alt. Mode (Wait For PD Power Contract / Swap / Alt Mode Flow)
                if(SysTypeCGetPortControllerAltModeReady(ucInputPort) == _TYPE_C_ALT_MODE_READY)
                {
#if(_BILLBOARD_SUPPORT == _ON)
                    // Cancel Timer Event(TURN ON BB)
                    SysTypeCCancelBillboardTimer(ucInputPort);
#endif

                    // 1. Get Alt. Mode Pin Assignment and Proc Related Setting (Lane Mapping or Swap)
                    if(SysTypeCGetPortControllerPinAssignment(ucInputPort) == _SUCCESS)
                    {
                        // 2. Set DP lANE Mapping According to Pin Assignment
                        SysTypeCSetDpLaneMapping(ucInputPort, GET_TYPE_C_PIN_ASSIGNMENT(ucInputPort));

                        // 3. Update OSD Lane Count According to Alt. Mode Pin Assignment
                        SysTypeCSwitchOSDLaneCount(ucInputPort, SysTypeCGetAltModeLaneCnt(GET_TYPE_C_PIN_ASSIGNMENT(ucInputPort)));
                        // SysTypeCSwitchSysDataLaneCount();

                        // 4. Switch DP Lane Count According to Alt. Mode Pin Assignment
                        ScalerDpLaneCountSwitch(ucInputPort, SysTypeCGetAltModeLaneCnt(GET_TYPE_C_PIN_ASSIGNMENT(ucInputPort)));
                        DebugMessageSystem("8. [TYPE C] ==========> Set DP Lane Count", SysTypeCGetAltModeLaneCnt(GET_TYPE_C_PIN_ASSIGNMENT(ucInputPort)));

                        // 5. Switch DP EDID According to Alt. Mode Pin Assignment
                        UserCommonInterfaceTypeCPinAssignSuccessProc(ucInputPort, GET_TYPE_C_PIN_ASSIGNMENT(ucInputPort));

                        DebugMessageSystem("8. [TYPE C] <Step 2/2> Alt Mode Ready", _TYPE_C_ATTACHED_STATE);

                        SET_TYPE_C_STATE(ucInputPort, _TYPE_C_ALT_MODE_READY_STATE);
                    }
                }
                else
                {
                    if(SysTypeCheckCapabilityChange(ucInputPort, _TYPE_C_SRC_CAP_CHG) == _TRUE)
                    {
                        // Check Whether Source Capability Has Been Changed or Not
                        SysTypeCSrcCapabilityChangeProc(ucInputPort);
                    }
                }
            }
            else
            {
                DebugMessageSystem("8. [TYPE C] <Step 0/2> CC Unattach", _TYPE_C_ATTACHED_STATE);

                SET_TYPE_C_STATE(ucInputPort, _TYPE_C_UNATTACH_STATE);
            }

            break;

        case _TYPE_C_ALT_MODE_READY_STATE:

            // Check if CC Attached
            if(SysTypeCGetPortControllerCcAttach(ucInputPort) == _TYPE_C_ATTACH)
            {
                // Check Whether USB Capability Has Been Changeed or Not
                if(SysTypeCheckCapabilityChange(ucInputPort, _TYPE_C_U3_MODE_CHG) == _TRUE)
                {
                    DebugMessageSystem("8. [TYPE C] ==========> Cap Change : Checking U3 Mode. . .", _TYPE_C_ALT_MODE_READY_STATE);
                    SysTypeCUsbCapabilityChangeProc(ucInputPort);
                }
                else
                {
                    // 1. Check if Still in Alt Mode
                    if(SysTypeCGetPortControllerAltModeReady(ucInputPort) != _TYPE_C_ALT_MODE_READY)
                    {
                        DebugMessageSystem("8. [TYPE C] <Step 1/2> CC Attach, Alt Mode Not Ready", _TYPE_C_ALT_MODE_READY_STATE);

                        // Config Lane Mapping to USB + DP Mode, and Back to Attached State to Wait for Alt. Mode Ready
                        SET_TYPE_C_STATE(ucInputPort, _TYPE_C_ATTACHED_STATE);
                    }

                    // 2. Check Whether Source Capability Has Been Changed or Not
                    if(SysTypeCheckCapabilityChange(ucInputPort, _TYPE_C_SRC_CAP_CHG) == _TRUE)
                    {
                        SysTypeCSrcCapabilityChangeProc(ucInputPort);
                    }
                }
            }
            else
            {
                DebugMessageSystem("8. [TYPE C] <Step 0/2> CC Unattach", _TYPE_C_ALT_MODE_READY_STATE);

                SET_TYPE_C_STATE(ucInputPort, _TYPE_C_UNATTACH_STATE);
            }

            break;

        case _TYPE_C_RECONNECT_STATE:

            if(SysTypeCGetPortControllerCcAttach(ucInputPort) == _TYPE_C_ATTACH)
            {
                if(SysTypeCGetPortControllerAltModeReady(ucInputPort) == _TYPE_C_ALT_MODE_READY)
                {
                    if(SysTypeCheckCapabilityChange(ucInputPort, _TYPE_C_U3_MODE_CHG) == _TRUE)
                    {
                        if(SysTypeCReconnect(ucInputPort) == _SUCCESS)
                        {
                            SysTypeCClrCapabilityChangeFlag(ucInputPort, _TYPE_C_U3_MODE_CHG);

                            // State Transition After Reconnect
                            SysTypeCReconnectTransition(ucInputPort);
                        }
                    }
                }
                else
                {
                    SET_TYPE_C_STATE(ucInputPort, _TYPE_C_ATTACHED_STATE);
                    DebugMessageSystem("8. [TYPE C] <Step 1/2> CC Attach, Alt Mode Not Ready", _TYPE_C_RECONNECT_STATE);
                }
            }
            else
            {
                // If Port Controller Switch to Unattach in 500ms, Cancel Unatach Timer Event
                SysTypeCCancelUnattachTimerEvent(ucInputPort);

                SET_TYPE_C_STATE(ucInputPort, _TYPE_C_UNATTACH_STATE);
                DebugMessageSystem("8. [TYPE C] <Step 0/2> CC Unattach", _TYPE_C_RECONNECT_STATE);
            }

            break;

        default:

            // Error Handling ?????

            break;
    }
}

//--------------------------------------------------
// Description  : Set Capability Change Power Switch Proc
// Input Value  : enumSwitch
// Output Value : None
//--------------------------------------------------
void SysTypeCPowerSwitch(EnumPowerAction enumSwitch)
{
    switch(enumSwitch)
    {
        case _POWER_ACTION_AC_ON_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_NORMAL:
        case _POWER_ACTION_FAKE_OFF_TO_NORMAL:
        case _POWER_ACTION_PS_TO_NORMAL:
        case _POWER_ACTION_FAKE_PS_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_FAKE_OFF:

#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            // Embedded Type-C : Update Port Ctrl. Pin Assignment
            if(SysTypeCUpdatePortControllerConfig(_D0_INPUT_PORT) != _SUCCESS)
            {
                DebugMessageSystem("8. [TYPE C] ==========x Power Switch, Update Embedded Type-C Config Fail ! ! !", enumSwitch);
            }
#elif((_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER))
            if(UserCommonPortControllerGetPowerOnReconnectStatus(enumSwitch) == _TYPE_C_PORT_CTRL_RECONNECT)
            {
                // 5400/User Port Ctrl : Set Capability Change Flag to Check Pin Assignment
                SysTypeCSetCapabilityChangeFlag(_D0_INPUT_PORT, _TYPE_C_U3_MODE_CHG);
            }

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            // 5400 Port Ctrl  : Enable Vender Command
            if(UserCommonPortControllerEnable5400VenderCommand(_D0_INPUT_PORT) != _SUCCESS)
            {
                DebugMessageSystem("8. [TYPE C] ==========> Power Switch, Enable Vender Command Fail ! ! !", enumSwitch);
            }
#endif  // End of #if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
#endif  // End of #if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
#endif  // End of #if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            // Embedded Type-C : Update Port Ctrl. Pin Assignment
            if(SysTypeCUpdatePortControllerConfig(_D1_INPUT_PORT) != _SUCCESS)
            {
                DebugMessageSystem("8. [TYPE C] ==========x Power Switch, Update Embedded Type-C Config Fail ! ! !", enumSwitch);
            }
#elif((_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER))
            if(UserCommonPortControllerGetPowerOnReconnectStatus(enumSwitch) == _TYPE_C_PORT_CTRL_RECONNECT)
            {
                // 5400/User Port Ctrl : Set Capability Change Flag to Check Pin Assignment
                SysTypeCSetCapabilityChangeFlag(_D1_INPUT_PORT, _TYPE_C_U3_MODE_CHG);
            }

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            // 5400 Port Ctrl  : Enable Vender Command
            if(UserCommonPortControllerEnable5400VenderCommand(_D1_INPUT_PORT) != _SUCCESS)
            {
                DebugMessageSystem("8. [TYPE C] ==========> Power Switch, Enable Vender Command Fail ! ! !", enumSwitch);
            }
#endif  // End of #if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
#endif  // End of #if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
#endif  // End of #if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            // Embedded Type-C : Update Port Ctrl. Pin Assignment
            if(SysTypeCUpdatePortControllerConfig(_D6_INPUT_PORT) != _SUCCESS)
            {
                DebugMessageSystem("8. [TYPE C] ==========x Power Switch, Update Embedded Type-C Config Fail ! ! !", enumSwitch);
            }
#elif((_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER))
            if(UserCommonPortControllerGetPowerOnReconnectStatus(enumSwitch) == _TYPE_C_PORT_CTRL_RECONNECT)
            {
                // 5400/User Port Ctrl : Set Capability Change Flag to Check Pin Assignment
                SysTypeCSetCapabilityChangeFlag(_D6_INPUT_PORT, _TYPE_C_U3_MODE_CHG);
            }

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            // 5400 Port Ctrl  : Enable Vender Command
            if(UserCommonPortControllerEnable5400VenderCommand(_D6_INPUT_PORT) != _SUCCESS)
            {
                DebugMessageSystem("8. [TYPE C] ==========> Power Switch, Enable Vender Command Fail ! ! !", enumSwitch);
            }
#endif  // End of #if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
#endif  // End of #if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
#endif  // End of #if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON)
            ScalerTypeCPowerSwitch(enumSwitch);
#endif
#if(_USB3_RETIMER_SUPPORT == _ON)
            if(ScalerUSB3RetimerGetHubUfpStatus() == _HUB_UFP_TYPE_C_INPUT_PORT)
            {
                ScalerUSB3RetimerPowerSwitch(enumSwitch);
            }
#endif

            DebugMessageSystem("8. [TYPE C] ==========> Power Switch, Set Cap Change ! ! !", enumSwitch);

            break;

        case _POWER_ACTION_AC_ON_TO_OFF:
        case _POWER_ACTION_NORMAL_TO_OFF:
        case _POWER_ACTION_NORMAL_TO_FAKE_OFF:
        case _POWER_ACTION_PS_TO_OFF:

#if(_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON)
            ScalerTypeCPowerSwitch(enumSwitch);
#endif
#if(_USB3_RETIMER_SUPPORT == _ON)
            if(ScalerUSB3RetimerGetHubUfpStatus() == _HUB_UFP_TYPE_C_INPUT_PORT)
            {
                ScalerUSB3RetimerPowerSwitch(enumSwitch);
            }
#endif

            break;

        case _POWER_ACTION_NORMAL_TO_PS:

#if(_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON)
            ScalerTypeCPowerSwitch(enumSwitch);
#endif
#if(_USB3_RETIMER_SUPPORT == _ON)
            if(ScalerUSB3RetimerGetHubUfpStatus() == _HUB_UFP_TYPE_C_INPUT_PORT)
            {
                ScalerUSB3RetimerPowerSwitch(enumSwitch);
            }
#endif

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Initial State Set Up Port Ctrl SRC/SNK Capability
// Input Value  : ucInputPort --> Inputput
// Output Value : None
//--------------------------------------------------
EnumPdoCheck SysTypeCSetPortCtrlSourceCap(BYTE ucInputPort)
{
    BYTE ucPdoCount = 0;
    BYTE ucPdoIndex = 0;
    StructTypeCUserSrcPDO stTypeCUserPdo;
    EnumPdoCheck enumSrcCapPdoChange = _TYPE_C_PDO_NO_CHANGE;
#if(_TYPE_C_EMB_VBUS_PROTECT_MODE == _VBUS_PROTECT_BY_USER)
    StructTypeCUserProtectInfo stTypeCUserProtectInfo;
#endif

    ucPdoCount = ucPdoCount;
    ucPdoIndex = ucPdoIndex;
    stTypeCUserPdo = stTypeCUserPdo;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)

            // 1. Get PDO Info From User / Kernel
            if(UserCommonInterfaceTypeCPdoReference(_D0_INPUT_PORT) == _TYPE_C_PDO_FROM_USER)
            {
                // 2. Get Max Power [Unit = 0.1 W]
                ScalerTypeCSetMaxPower(_D0_INPUT_PORT, UserCommonInterfaceTypeCGetMaxPower(_D0_INPUT_PORT));

                // 3. Get Total Number of PDO (Enumeration Range 1 ~ 7)
                ucPdoCount = UserCommonInterfaceTypeCGetPdoCount(_D0_INPUT_PORT);
                if(ScalerTypeCCheckPdoCountChange(_D0_INPUT_PORT, ucPdoCount) == _TYPE_C_PDO_CHANGE)
                {
                    ScalerTypeCSetPdoCnt(_D0_INPUT_PORT, ucPdoCount);
                    enumSrcCapPdoChange = _TYPE_C_PDO_CHANGE;
                }

                // 4. Get PDO Info and Write to Port Controller
                for(ucPdoIndex = 1; ucPdoIndex <= ucPdoCount; ucPdoIndex++)
                {
                    // Set PDO to Default Value
                    stTypeCUserPdo.enumPdoType = _PD_FIX_SUPPLY_PDO;
                    stTypeCUserPdo.ucMaxCurrent = 0;
                    stTypeCUserPdo.ucMaxVoltage = 0;
                    stTypeCUserPdo.ucMinVoltage = 0;

                    // Get User 1st - 7th PDO Info
                    UserCommonInterfaceTypeCGetPdoInfo(_D0_INPUT_PORT, ucPdoIndex, &stTypeCUserPdo);

                    if(ScalerTypeCCheckPdoChange(_D0_INPUT_PORT, ucPdoIndex, stTypeCUserPdo) == _TYPE_C_PDO_CHANGE)
                    {
                        if(stTypeCUserPdo.enumPdoType == _PD_FIX_SUPPLY_PDO)
                        {
                            ScalerTypeCSetFixPdo(_D0_INPUT_PORT, ucPdoIndex, stTypeCUserPdo.ucMaxVoltage, stTypeCUserPdo.ucMaxCurrent);
                        }
#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
                        else if(stTypeCUserPdo.enumPdoType == _PD_3_PROGRAMMABLE_PDO)
                        {
                            ScalerTypeCSetPpsPdo(_D0_INPUT_PORT, ucPdoIndex, stTypeCUserPdo.ucMinVoltage, stTypeCUserPdo.ucMaxVoltage, stTypeCUserPdo.ucMaxCurrent);
                        }
#endif  // End of #if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)

                        enumSrcCapPdoChange = _TYPE_C_PDO_CHANGE;

                        // Debug Message
                        DebugMessageSystem("8. [TYPE C] <PDO> ======== PDO Num ========", ucPdoIndex);
                        DebugMessageSystem("8. [TYPE C] <PDO> Voltage (1V)", (stTypeCUserPdo.ucMaxVoltage / 10));
                        DebugMessageSystem("8. [TYPE C] <PDO> Current (0.01A)", ((stTypeCUserPdo.ucMaxCurrent * 10) / 2));
                    }
                }
            }
            else
            {
                // Source PDO Defined By Kernel (PDP = 27W / 5V@3A + 9V@3A)
                ScalerTypeCSrcPdoInitial(_D0_INPUT_PORT);
            }

#if(_TYPE_C_EMB_VBUS_PROTECT_MODE == _VBUS_PROTECT_BY_USER)
            ucPdoCount = ScalerTypeCGetPdoCnt(_D0_INPUT_PORT);

            for(ucPdoIndex = 1; ucPdoIndex <= ucPdoCount; ucPdoIndex++)
            {
                UserCommonInterfaceTypeCGetProtectInfo(_D0_INPUT_PORT, ucPdoIndex, &stTypeCUserProtectInfo);
                ScalerTypeCSetProtectInfo(_D0_INPUT_PORT, ucPdoIndex, stTypeCUserProtectInfo);
            }
#endif

#endif
            break;
#endif  // End of #if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            break;
#endif  // End of #if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D6_INPUT_PORT:

            break;
#endif  // End of #if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

        default:

            break;
    }

    return enumSrcCapPdoChange;
}

//--------------------------------------------------
// Description  : Get Port Controller CC Attached Info (5400 & User : From GPIO / Embedded From : CC Attach Flag)
// Input Value  : ucInputPort --> Inputput
// Output Value : CC Attach Status (_TRUE / _FALSE)
//--------------------------------------------------
EnumTypeCAttachStatus SysTypeCGetPortControllerCcAttach(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            return ScalerTypeCGetCcAttach(ucInputPort);

#elif((_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER))
            return UserCommonPortControllerGetCcAttach(ucInputPort);
#endif
            break;
#endif  // End of #if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            return ScalerTypeCGetCcAttach(ucInputPort);

#elif((_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER))
            return UserCommonPortControllerGetCcAttach(ucInputPort);
#endif
            break;
#endif  // End of #if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D6_INPUT_PORT:

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            return ScalerTypeCGetCcAttach(ucInputPort);
#elif((_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER))
            return UserCommonPortControllerGetCcAttach(ucInputPort);
#endif
            break;
#endif  // End of #if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

        default:

            return _TYPE_C_UNATTACH;

            break;
    }
    return _TYPE_C_UNATTACH;
}

//--------------------------------------------------
// Description  : Get Port Controller Alt. Mode Ready Info (5400 & User : From GPIO / Embedded From : Alt Mode Ready Flag)
// Input Value  : ucInputPort --> Inputput
// Output Value : Alt. Mode Ready Status (_TRUE / _FALSE)
//--------------------------------------------------
EnumTypeCAltModeStatus SysTypeCGetPortControllerAltModeReady(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            return ScalerTypeCGetAltModeReady(ucInputPort);
#elif((_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER))
            return UserCommonPortControllerGetAltModeReady(ucInputPort);
#endif
            break;
#endif

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            return ScalerTypeCGetAltModeReady(ucInputPort);
#elif((_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER))
            return UserCommonPortControllerGetAltModeReady(ucInputPort);
#endif
            break;
#endif

#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D6_INPUT_PORT:

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            return ScalerTypeCGetAltModeReady(ucInputPort);
#elif((_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER))
            return UserCommonPortControllerGetAltModeReady(ucInputPort);
#endif
            break;
#endif

        default:

            return _TYPE_C_ALT_MODE_NOT_READY;

            break;
    }
    return _TYPE_C_ALT_MODE_NOT_READY;
}

//--------------------------------------------------
// Description  : Get Port Controller Pin Assignment (5400 & User : From I2C / Embedded From : Pin Assignment Flag)
// Input Value  : ucInputPort --> Inputput
// Output Value : Reconnect Status (_SUCCESS / _FAIL)
//--------------------------------------------------
bit SysTypeCGetPortControllerPinAssignment(BYTE ucInputPort)
{
    EnumTypeCPinCfgType enumPinAssignment = _TYPE_C_PIN_ASSIGNMENT_NONE;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            if(ScalerTypeCGetPinAssignment(_D0_INPUT_PORT, &enumPinAssignment) == _SUCCESS)
#elif(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            if(UserCommonPortControllerGet5400PinAssignment(_D0_INPUT_PORT, &enumPinAssignment) == _SUCCESS)
#elif(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)
            if(UserCommonPortControllerGetUserPinAssignment(_D0_INPUT_PORT, &enumPinAssignment) == _SUCCESS)
#endif
            {
                DebugMessageSystem("8. [TYPE C] ==========> Get Port Ctrl Pin Assignment (C:4 / D:8):", enumPinAssignment);

                SET_TYPE_C_PIN_ASSIGNMENT(_D0_INPUT_PORT, enumPinAssignment);

                return _SUCCESS;
            }
            else
            {
                SET_TYPE_C_PIN_ASSIGNMENT(_D0_INPUT_PORT, _TYPE_C_PIN_ASSIGNMENT_NONE);

                return _FAIL;
            }

            break;
#endif  // End of #if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            if(ScalerTypeCGetPinAssignment(_D1_INPUT_PORT, &enumPinAssignment) == _SUCCESS)
#elif(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            if(UserCommonPortControllerGet5400PinAssignment(_D1_INPUT_PORT, &enumPinAssignment) == _SUCCESS)
#elif(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)
            if(UserCommonPortControllerGetUserPinAssignment(_D1_INPUT_PORT, &enumPinAssignment) == _SUCCESS)
#endif
            {
                DebugMessageSystem("8. [TYPE C] ==========> SysTypeC Get Port Ctrl Pin Assignment :", enumPinAssignment);

                SET_TYPE_C_PIN_ASSIGNMENT(_D1_INPUT_PORT, enumPinAssignment);

                return _SUCCESS;
            }
            else
            {
                SET_TYPE_C_PIN_ASSIGNMENT(_D1_INPUT_PORT, _TYPE_C_PIN_ASSIGNMENT_NONE);

                return _FAIL;
            }

            break;
#endif  // End of #if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D6_INPUT_PORT:

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            if(ScalerTypeCGetPinAssignment(_D6_INPUT_PORT, &enumPinAssignment) == _SUCCESS)
#elif(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            if(UserCommonPortControllerGet5400PinAssignment(_D6_INPUT_PORT, &enumPinAssignment) == _SUCCESS)
#elif(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)
            if(UserCommonPortControllerGetUserPinAssignment(_D6_INPUT_PORT, &enumPinAssignment) == _SUCCESS)
#endif
            {
                DebugMessageSystem("8. [TYPE C] ==========> SysTypeC Get Port Ctrl Pin Assignment :", enumPinAssignment);

                SET_TYPE_C_PIN_ASSIGNMENT(_D6_INPUT_PORT, enumPinAssignment);

                return _SUCCESS;
            }
            else
            {
                SET_TYPE_C_PIN_ASSIGNMENT(_D6_INPUT_PORT, _TYPE_C_PIN_ASSIGNMENT_NONE);

                return _FAIL;
            }

            break;
#endif  // End of #if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

        default:

            DebugMessageSystem("8. [TYPE C] ==========X SysTypeC Get Port Corl with Invalid Port :", ucInputPort);

            SET_TYPE_C_PIN_ASSIGNMENT(ucInputPort, _TYPE_C_PIN_ASSIGNMENT_NONE);

            return _FAIL;

            break;
    }
    return _FAIL;
}

//--------------------------------------------------
// Description  : Set DP Lane Mapping According to 5400 / User Pin Assignment
// Input Value  : ucInputPort --> Inputput
// Output Value : None
//--------------------------------------------------
void SysTypeCSetDpLaneMapping(BYTE ucInputPort, EnumTypeCPinCfgType enumPinAssignment)
{
    ucInputPort = ucInputPort;
    enumPinAssignment = enumPinAssignment;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:

#if((_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER))

            // Adjust Lane Mapping According to User Port Controller Pin Assignment
            if(enumPinAssignment == _TYPE_C_PIN_ASSIGNMENT_E)
            {
                DebugMessageSystem("8. [TYPE C] ==========> Adjust Lane Mapping = Pin Assignment E Mapping", enumPinAssignment);

                UserCommonPortControllerPinMappingSetting(ucInputPort, _DP_LANE_MAPPING_TYPE_C_ASSIGNMENT_E_TYPE);
            }
            else
            {
                DebugMessageSystem("8. [TYPE C] ==========> Adjust Lane Mapping = Normal Mapping", enumPinAssignment);

                UserCommonPortControllerPinMappingSetting(ucInputPort, _DP_LANE_MAPPING_NORMAL_TYPE);
            }
#endif

            break;
#endif  // End of #if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:

#if((_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER))

            // Adjust Lane Mapping According to User Port Controller Pin Assignment
            if(enumPinAssignment == _TYPE_C_PIN_ASSIGNMENT_E)
            {
                DebugMessageSystem("8. [TYPE C] ==========> Adjust Lane Mapping = Pin Assignment E Mapping", enumPinAssignment);

                UserCommonPortControllerPinMappingSetting(ucInputPort, _DP_LANE_MAPPING_TYPE_C_ASSIGNMENT_E_TYPE);
            }
            else
            {
                DebugMessageSystem("8. [TYPE C] ==========> Adjust Lane Mapping = Normal Mapping", enumPinAssignment);

                UserCommonPortControllerPinMappingSetting(ucInputPort, _DP_LANE_MAPPING_NORMAL_TYPE);
            }
#endif


            break;
#endif  // End of #if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D6_INPUT_PORT:

#if((_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER))

            // Adjust Lane Mapping According to User Port Controller Pin Assignment
            if(enumPinAssignment == _TYPE_C_PIN_ASSIGNMENT_E)
            {
                DebugMessageSystem("8. [TYPE C] ==========> Adjust Lane Mapping = Pin Assignment E Mapping", enumPinAssignment);

                UserCommonPortControllerPinMappingSetting(ucInputPort, _DP_LANE_MAPPING_TYPE_C_ASSIGNMENT_E_TYPE);
            }
            else
            {
                DebugMessageSystem("8. [TYPE C] ==========> Adjust Lane Mapping = Normal Mapping", enumPinAssignment);

                UserCommonPortControllerPinMappingSetting(ucInputPort, _DP_LANE_MAPPING_NORMAL_TYPE);
            }
#endif


            break;
#endif  // End of #if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

        default:

            DebugMessageSystem("8. [TYPE C] ==========X SysTypeC Set Lane Mapping with Invalid Port :", ucInputPort);

            break;
    }
}

//--------------------------------------------------
// Description  : Check if Specific Capability Has Been Changed
// Input Value  : ucInputPort --> Inputput, ucInputPort --> Inputput
// Output Value : None
//--------------------------------------------------
bit SysTypeCheckCapabilityChange(BYTE ucInputPort, EnumTypeCCapChgStatus enumCapability)
{
    switch(enumCapability)
    {
        case _TYPE_C_HUB_INPUT_SWITCH_CHG:

            if((GET_TYPE_C_CAPABILITY_CHG(ucInputPort) & _TYPE_C_HUB_INPUT_SWITCH_CHG) == _TYPE_C_HUB_INPUT_SWITCH_CHG)
            {
#if(_USB3_RETIMER_SUPPORT == _ON)
                // Updata Hub UFP Status marco
                ScalerUSB3RetimerSetHubUfpStatus(UserCommonPortControllerGetHubInputPort(ucInputPort));
#endif

                return _TRUE;
            }
            else
            {
                return _FALSE;
            }

            break;

        case _TYPE_C_U3_MODE_CHG:

            if((GET_TYPE_C_CAPABILITY_CHG(ucInputPort) & _TYPE_C_U3_MODE_CHG) == _TYPE_C_U3_MODE_CHG)
            {
                return _TRUE;
            }
            else
            {
                return _FALSE;
            }

            break;

        case _TYPE_C_SRC_CAP_CHG:

            if((GET_TYPE_C_CAPABILITY_CHG(ucInputPort) & _TYPE_C_SRC_CAP_CHG) == _TYPE_C_SRC_CAP_CHG)
            {
                return _TRUE;
            }
            else
            {
                return _FALSE;
            }

            break;

        default:

            return _FALSE;

            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check if Current Config Matches the Latest Requirement, and Set to Reconnect State
// Input Value  : ucInputPort --> Inputput
// Output Value : None
//--------------------------------------------------
void SysTypeCUsbCapabilityChangeProc(BYTE ucInputPort)
{
    if(GET_TYPE_C_PIN_ASSIGNMENT(ucInputPort) != _TYPE_C_PIN_ASSIGNMENT_E)
    {
        if(((UserInterfaceTypeCGetOsdU3ModeSelection(ucInputPort) == _TYPE_C_U3_ON) && (GET_TYPE_C_PIN_ASSIGNMENT(ucInputPort) != _TYPE_C_PIN_ASSIGNMENT_D)) ||
           ((UserInterfaceTypeCGetOsdU3ModeSelection(ucInputPort) == _TYPE_C_U3_OFF) && (GET_TYPE_C_PIN_ASSIGNMENT(ucInputPort) == _TYPE_C_PIN_ASSIGNMENT_D)))
        {
            // 1. Update Prot Controller (5400/User/Embedded) Config
            if(SysTypeCUpdatePortControllerConfig(ucInputPort) == _SUCCESS)
            {
                // 2. Switch to Reconnect State
                DebugMessageSystem("8. [TYPE C] ==========> U3 Mode Mismatch, RECONNECT", 0);

                SET_TYPE_C_STATE(ucInputPort, _TYPE_C_RECONNECT_STATE);
            }
        }
        else
        {
            // Current Config Matched the Latest Capability
            SysTypeCClrCapabilityChangeFlag(ucInputPort, _TYPE_C_U3_MODE_CHG);
            DebugMessageSystem("8. [TYPE C] ==========> USB Mode Check Pass, Clear Cap Change", 1);
        }
    }
    else
    {
        // Pin Assignment E Cable, Ignore Capability Change, Since Port Controller Should Alway Choose E (No USB3)
        SysTypeCClrCapabilityChangeFlag(ucInputPort, _TYPE_C_U3_MODE_CHG);
        DebugMessageSystem("8. [TYPE C] ==========> USB Mode Check Pass", 1);
    }
}

//--------------------------------------------------
// Description  : Request Port Controller to Re-Send Src Capability Message
// Input Value  : ucInputPort --> Inputput
// Output Value : None
//--------------------------------------------------
void SysTypeCSrcCapabilityChangeProc(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            // Request Embedded TypeC to Send Src Cap
            ScalerTypeCSetPdSystemEvent(_D0_INPUT_PORT, _PD_SYS_EVENT_SEND_SRC_CAP);
#endif
            break;
#endif

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            break;
#endif

#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D6_INPUT_PORT:

            break;
#endif

        default:

            break;
    }

    // Clear Source Capability Change Flag
    SysTypeCClrCapabilityChangeFlag(ucInputPort, _TYPE_C_SRC_CAP_CHG);
}

//--------------------------------------------------
// Description  : Request Port Controller to Reconnect
// Input Value  : ucInputPort --> Inputput
// Output Value : Reconnect Status (_SUCCESS / _FAIL)
//--------------------------------------------------
bit SysTypeCReconnect(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            return ScalerTypeCReconnect(_D0_INPUT_PORT);
#elif(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            return UserCommonPortController5400Reconnect(_D0_INPUT_PORT);
#elif(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)
            return UserCommonPortControllerUserReconnect(_D0_INPUT_PORT);
#endif
            break;
#endif

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            return ScalerTypeCReconnect(_D1_INPUT_PORT);
#elif(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            return UserCommonPortController5400Reconnect(_D1_INPUT_PORT);
#elif(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)
            return UserCommonPortControllerUserReconnect(_D1_INPUT_PORT);
#endif
            break;
#endif

#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D6_INPUT_PORT:

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            return ScalerTypeCReconnect(_D6_INPUT_PORT);
#elif(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            return UserCommonPortController5400Reconnect(_D6_INPUT_PORT);
#elif(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)
            return UserCommonPortControllerUserReconnect(_D6_INPUT_PORT);
#endif
            break;
#endif

        default:

            return _FAIL;

            break;
    }
    return _FAIL;
}

//--------------------------------------------------
// Description  : Transit Type C State After Reconnect Success
// Input Value  : ucInputPort --> Inputput
// Output Value : Reconnect Status (_SUCCESS / _FAIL)
//--------------------------------------------------
void SysTypeCReconnectTransition(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:
#if(_D0_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
            // Set CC Attach & Alt Mode Ready to False
            SET_D0_CABLE_STATUS(_FALSE);
            SET_D0_DP_TYPE_C_ALTMODE_STATUS(_FALSE);

            // Set TypeC State to Unattach
            SET_TYPE_C_STATE(_D0_INPUT_PORT, _TYPE_C_UNATTACH_STATE);

            // Restart CC Attach & Alt. Mode Ready Detection By I2C Later
            UserCommonPortControllerRestartD0I2CDetection(_TYPE_C_RESTART_CHECK_CABLE_STATUS_TIME);
#else
            // If Port Controller Not Switch to Unattach in 500ms, Force Switch to Unattach State
            ScalerTimerActiveTimerEvent(SEC(0.5), _SYSTEM_TIMER_EVENT_D0_TYPE_C_UNATTACH);
#endif
            break;
#endif  // End of #if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:
#if(_D1_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
            // Set CC Attach & Alt Mode Ready to False
            SET_D1_CABLE_STATUS(_FALSE);
            SET_D1_DP_TYPE_C_ALTMODE_STATUS(_FALSE);

            // Set TypeC State to Unattach
            SET_TYPE_C_STATE(_D1_INPUT_PORT, _TYPE_C_UNATTACH_STATE);

            // Restart CC Attach & Alt. Mode Ready Detection By I2C Later
            UserCommonPortControllerRestartD1I2CDetection(_TYPE_C_RESTART_CHECK_CABLE_STATUS_TIME);
#else
            // If Port Controller Not Switch to Unattach in 500ms, Force Switch to Unattach State
            ScalerTimerActiveTimerEvent(SEC(0.5), _SYSTEM_TIMER_EVENT_D1_TYPE_C_UNATTACH);
#endif
            break;
#endif  // End of #if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D6_INPUT_PORT:
#if(_D6_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
            // Set CC Attach & Alt Mode Ready to False
            SET_D6_CABLE_STATUS(_FALSE);
            SET_D6_DP_TYPE_C_ALTMODE_STATUS(_FALSE);

            // Set TypeC State to Unattach
            SET_TYPE_C_STATE(_D6_INPUT_PORT, _TYPE_C_UNATTACH_STATE);

            // Restart CC Attach & Alt. Mode Ready Detection By I2C Later
            UserCommonPortControllerRestartD6I2CDetection(_TYPE_C_RESTART_CHECK_CABLE_STATUS_TIME);
#else
            // If Port Controller Not Switch to Unattach in 500ms, Force Switch to Unattach State
            ScalerTimerActiveTimerEvent(SEC(0.5), _SYSTEM_TIMER_EVENT_D6_TYPE_C_UNATTACH);
#endif
            break;
#endif  // End of #if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Update Port Controller Configuration
// Input Value  : ucInputPort --> Inputput
// Output Value : Reconnect Status (_SUCCESS / _FAIL)
//--------------------------------------------------
bit SysTypeCUpdatePortControllerConfig(BYTE ucInputPort)
{
    // Default Set U3 Mode to OFF
    EnumTypeCU3ModeType enumU3Mode = _TYPE_C_U3_OFF;
    EnumTypeCMultiFuncStatus enumMultiFunc = _TYPE_C_MULTI_FUNC_NOT_PREFER;
    EnumTypeCPinCfgCapType enumPinAssignmentCap = _TYPE_C_PIN_ASSIGNMENT_CAP_NONE;

    // Update U3 Mode / Multi-Function Bit / Pin Assignment Capability (From User)
    if(UserInterfaceTypeCGetOsdU3ModeSelection(ucInputPort) == _TYPE_C_U3_ON)
    {
        enumU3Mode = _TYPE_C_U3_ON;
        enumMultiFunc = _TYPE_C_MULTI_FUNC_PREFER;
    }

    enumPinAssignmentCap = UserInterfaceTypeCGetPinConfigType(ucInputPort, enumU3Mode);

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            return ScalerTypeCUpdateConfig(_D0_INPUT_PORT, enumMultiFunc, enumPinAssignmentCap);
#elif((_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER))
            return UserCommonPortControllerUpdateConfig(_D0_INPUT_PORT, enumMultiFunc, enumPinAssignmentCap);
#endif
            break;
#endif

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            return ScalerTypeCUpdateConfig(_D1_INPUT_PORT, enumMultiFunc, enumPinAssignmentCap);
#elif((_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER))
            return UserCommonPortControllerUpdateConfig(_D1_INPUT_PORT, enumMultiFunc, enumPinAssignmentCap);
#endif
            break;
#endif

#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D6_INPUT_PORT:

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            return ScalerTypeCUpdateConfig(_D6_INPUT_PORT, enumMultiFunc, enumPinAssignmentCap);
#elif((_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER))
            return UserCommonPortControllerUpdateConfig(_D6_INPUT_PORT, enumMultiFunc, enumPinAssignmentCap);
#endif
            break;
#endif

        default:

            return _FAIL;

            break;
    }
    return _FAIL;
}

//--------------------------------------------------
// Description  : Return CC Attached Status to SysSource According to SysTypeC State
// Input Value  : ucInputPort --> Inputput
// Output Value : CC Attach Status (_TRUE / _FALSE)
//--------------------------------------------------
bit SysTypeCGetCcAttach(BYTE ucInputPort)
{
    switch(GET_TYPE_C_STATE(ucInputPort))
    {
        case _TYPE_C_ATTACHED_STATE:
        case _TYPE_C_ALT_MODE_READY_STATE:

            return _TRUE;

            break;

        case _TYPE_C_UNATTACH_STATE:

#if(_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON)
            return ScalerTypeCRx0CcGetACOnDeviceDetect();
#else
            return _FALSE;
#endif

            break;

        default:

            return _FALSE;

            break;

        case _TYPE_C_RECONNECT_STATE:

            // CC Attach Status Not Change : Return Status From SysSource
            switch(ucInputPort)
            {
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
                case _D0_INPUT_PORT:

                    return GET_D0_CABLE_STATUS();

                    break;
#endif

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
                case _D1_INPUT_PORT:

                    return GET_D1_CABLE_STATUS();

                    break;
#endif

#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
                case _D6_INPUT_PORT:

                    return GET_D6_CABLE_STATUS();

                    break;
#endif

                default:

                    return _FALSE;

                    break;
            }

            break;
    }
    return _FALSE;
}

//--------------------------------------------------
// Description  : Return Alt Mode Ready Statsu to SysSource According to SysTypeC State
// Input Value  : ucInputPort --> Inputput
// Output Value : CC Attach Status (_TRUE / _FALSE)
//--------------------------------------------------
bit SysTypeCGetAltModeReady(BYTE ucInputPort)
{
    switch(GET_TYPE_C_STATE(ucInputPort))
    {
        case _TYPE_C_ALT_MODE_READY_STATE:

            return _TRUE;

            break;

        case _TYPE_C_UNATTACH_STATE:
        case _TYPE_C_ATTACHED_STATE:
        default:

            return _FALSE;

            break;

        case _TYPE_C_RECONNECT_STATE:

            // Alt Mode Status Not Change : Return Status From SysSource
            switch(ucInputPort)
            {
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
                case _D0_INPUT_PORT:

                    return GET_D0_DP_TYPE_C_ALTMODE_STATUS();

                    break;
#endif

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
                case _D1_INPUT_PORT:

                    return GET_D1_DP_TYPE_C_ALTMODE_STATUS();

                    break;
#endif

#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
                case _D6_INPUT_PORT:

                    return GET_D6_DP_TYPE_C_ALTMODE_STATUS();

                    break;
#endif

                default:

                    return _FALSE;

                    break;
            }

            break;
    }
    return _FALSE;
}

//--------------------------------------------------
// Description  : Return Port Controller Negotiated Pin Assignment
// Input Value  : ucInputPort --> Inputput
// Output Value : Pin Assignment (Retern None When Alt Mode Not Ready Yet)
//--------------------------------------------------
EnumTypeCPinCfgType SysTypeCGetPinAssignment(BYTE ucInputPort)
{
    EnumTypeCPinCfgType enumPinAssignment = _TYPE_C_PIN_ASSIGNMENT_NONE;

    if(SysTypeCGetAltModeReady(ucInputPort) == _TRUE)
    {
        enumPinAssignment = GET_TYPE_C_PIN_ASSIGNMENT(ucInputPort);
    }

    return enumPinAssignment;
}

//--------------------------------------------------
// Description  : Trnaslate ucInputPort into Type-C Port Index For Macro Usage
// Input Value  : ucInputPort
// Output Value : Type-C Port Index
//--------------------------------------------------
BYTE SysTypeCGetTypeCIndex(BYTE ucInputPort)
{
    BYTE ucIndex = 0x00;

#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

    if(ucInputPort == _D0_INPUT_PORT)
    {
        return ucIndex;
    }
    else
    {
        ucIndex = ucIndex + 1;
    }

#endif

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

    if(ucInputPort == _D1_INPUT_PORT)
    {
        return ucIndex;
    }
    else
    {
        ucIndex = ucIndex + 1;
    }

#endif

#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

    if(ucInputPort == _D6_INPUT_PORT)
    {
        return ucIndex;
    }

#endif

    // ucInputPort Invalid : Show Warning Message
    DebugMessageSystem("8. [TYPE C] ==========X Invalid InputPort For TypeC Index", ucInputPort);

    return ucIndex;
}

//--------------------------------------------------
// Description  : Trnaslate Alt. Mode Pin Assignment to DP Lane Count
// Input Value  : ucPinAssignment
// Output Value : EnumDpLaneCount -> _DP_LINK_1_LANE / _DP_LINK_2_LANE / _DP_LINK_4_LANE
//--------------------------------------------------
EnumDpLaneCount SysTypeCGetAltModeLaneCnt(EnumTypeCPinCfgType enumPinAssignment)
{
    EnumDpLaneCount enumAltModeLaneCnt = _DP_LINK_4_LANE;
    switch(enumPinAssignment)
    {
        case _TYPE_C_PIN_ASSIGNMENT_C:
        case _TYPE_C_PIN_ASSIGNMENT_E:

            enumAltModeLaneCnt = _DP_LINK_4_LANE;

            break;

        case _TYPE_C_PIN_ASSIGNMENT_D:

            enumAltModeLaneCnt = _DP_LINK_2_LANE;

            break;


        default:

            break;
    }

    return enumAltModeLaneCnt;
}

//--------------------------------------------------
// Description  : Update OSD Lane Count
// Input Value  : ucInputPort --> Inputput, enumDpLaneCount : _DP_LINK_1_LANE / _DP_LINK_2_LANE / _DP_LINK_4_LANE
// Output Value : NONE
//--------------------------------------------------
void SysTypeCSwitchOSDLaneCount(BYTE ucInputPort, EnumDpLaneCount enumDpLaneCount)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            UserCommonNVRamSetSystemData(_DP_D0_LANES, enumDpLaneCount);

            break;
#endif

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            UserCommonNVRamSetSystemData(_DP_D1_LANES, enumDpLaneCount);

            break;
#endif

#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D6_INPUT_PORT:

            UserCommonNVRamSetSystemData(_DP_D6_LANES, enumDpLaneCount);

            break;
#endif

        default:
            break;
    }

    UserCommonNVRamSaveSystemData();
}

//--------------------------------------------------
// Description  : Set Capability Change Flag
// Input Value  : ucInputPort --> Inputput, enumCapability --> Target Capability
// Output Value : NONE
//--------------------------------------------------
void SysTypeCSetCapabilityChangeFlag(BYTE ucInputPort, EnumTypeCCapChgStatus enumCapability)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            SET_TYPE_C_CAPABILITY_CHG(_D0_INPUT_PORT, enumCapability);

            break;
#endif

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            SET_TYPE_C_CAPABILITY_CHG(_D1_INPUT_PORT, enumCapability);

            break;
#endif

#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D6_INPUT_PORT:

            SET_TYPE_C_CAPABILITY_CHG(_D6_INPUT_PORT, enumCapability);

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Clear Capability Change Flag
// Input Value  : ucInputPort --> Inputput, enumCapability --> Target Capability
// Output Value : NONE
//--------------------------------------------------
void SysTypeCClrCapabilityChangeFlag(BYTE ucInputPort, EnumTypeCCapChgStatus enumCapability)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            CLR_TYPE_C_CAPABILITY_CHG(_D0_INPUT_PORT, enumCapability);

            break;
#endif

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            CLR_TYPE_C_CAPABILITY_CHG(_D1_INPUT_PORT, enumCapability);

            break;
#endif

#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D6_INPUT_PORT:

            CLR_TYPE_C_CAPABILITY_CHG(_D6_INPUT_PORT, enumCapability);

            break;
#endif

        default:
            break;
    }
}

#if(((_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D0_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK != _DISCRETE_PORT_CTRL_USE_SMBUS)) || ((_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D1_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK != _DISCRETE_PORT_CTRL_USE_SMBUS)) || ((_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D6_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK != _DISCRETE_PORT_CTRL_USE_SMBUS)))
//--------------------------------------------------
// Description  : Set Type C State to Unattach State
// Input Value  : ucInputPort --> Inputput
// Output Value : NONE
//--------------------------------------------------
void SysTypeCSwitchToUnattachState(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if((_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D0_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK != _DISCRETE_PORT_CTRL_USE_SMBUS))
        case _D0_INPUT_PORT:

            SET_TYPE_C_STATE(_D0_INPUT_PORT, _TYPE_C_UNATTACH_STATE);
            DebugMessageSystem("8. [TYPE C] <Step 0/2> CC Unattach", _TYPE_C_RECONNECT_STATE);

            break;
#endif

#if((_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D1_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK != _DISCRETE_PORT_CTRL_USE_SMBUS))
        case _D1_INPUT_PORT:

            SET_TYPE_C_STATE(_D1_INPUT_PORT, _TYPE_C_UNATTACH_STATE);
            DebugMessageSystem("8. [TYPE C] <Step 0/2> CC Unattach", _TYPE_C_RECONNECT_STATE);

            break;
#endif

#if((_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D6_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK != _DISCRETE_PORT_CTRL_USE_SMBUS))
        case _D6_INPUT_PORT:

            SET_TYPE_C_STATE(_D6_INPUT_PORT, _TYPE_C_UNATTACH_STATE);
            DebugMessageSystem("8. [TYPE C] <Step 0/2> CC Unattach", _TYPE_C_RECONNECT_STATE);

            break;
#endif

        default:
            break;
    }
}
#endif  // End of #if(((_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D0_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK != _DISCRETE_PORT_CTRL_USE_SMBUS)) || ((_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D1_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK != _DISCRETE_PORT_CTRL_USE_SMBUS)) || ((_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D6_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK != _DISCRETE_PORT_CTRL_USE_SMBUS)))

//--------------------------------------------------
// Description  : Cancel Timer Event Which Set Type C to Unattach State
// Input Value  : ucInputPort --> Inputput
// Output Value : NONE
//--------------------------------------------------
void SysTypeCCancelUnattachTimerEvent(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if((_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D0_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK != _DISCRETE_PORT_CTRL_USE_SMBUS))
        case _D0_INPUT_PORT:

            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_D0_TYPE_C_UNATTACH);

            break;
#endif

#if((_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D1_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK != _DISCRETE_PORT_CTRL_USE_SMBUS))
        case _D1_INPUT_PORT:

            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_D1_TYPE_C_UNATTACH);

            break;
#endif

#if((_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D6_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK != _DISCRETE_PORT_CTRL_USE_SMBUS))
        case _D6_INPUT_PORT:

            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_D6_TYPE_C_UNATTACH);

            break;
#endif

        default:

            break;
    }
}

#if(_BILLBOARD_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Type-C Start Billboard ON Timer
// Input Value  : ucInputPort / Timer Timeout Count
// Output Value : None
//--------------------------------------------------
void SysTypeCStartBillboardTimer(BYTE ucInputPort, WORD usTimeoutCnt)
{
    switch(ucInputPort)
    {
#if((_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D0_BILLBOARD_SUPPORT == _ON))
        case _D0_INPUT_PORT:

            ScalerTimerActiveTimerEvent(usTimeoutCnt, _SYSTEM_TIMER_EVENT_D0_ENABLE_BILLBOARD);

            break;
#endif  // End of #if((_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D0_BILLBOARD_SUPPORT))

#if((_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D1_BILLBOARD_SUPPORT == _ON))
        case _D1_INPUT_PORT:

            ScalerTimerActiveTimerEvent(usTimeoutCnt, _SYSTEM_TIMER_EVENT_D1_ENABLE_BILLBOARD);

            break;
#endif  // End of #if((_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D1_BILLBOARD_SUPPORT))

#if((_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D6_BILLBOARD_SUPPORT == _ON))
        case _D6_INPUT_PORT:

            ScalerTimerActiveTimerEvent(usTimeoutCnt, _SYSTEM_TIMER_EVENT_D6_ENABLE_BILLBOARD);

            break;
#endif  // End of #if((_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D6_BILLBOARD_SUPPORT))

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Type-C Cancel Billboard ON Timer
// Input Value  : ucInputPort
// Output Value : None
//--------------------------------------------------
void SysTypeCCancelBillboardTimer(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if((_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D0_BILLBOARD_SUPPORT == _ON))
        case _D0_INPUT_PORT:

            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_D0_ENABLE_BILLBOARD);

            break;
#endif  // End of #if((_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D0_BILLBOARD_SUPPORT == _ON))

#if((_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D1_BILLBOARD_SUPPORT == _ON))
        case _D1_INPUT_PORT:

            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_D1_ENABLE_BILLBOARD);

            break;
#endif  // End of #if((_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D1_BILLBOARD_SUPPORT == _ON))

#if((_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D6_BILLBOARD_SUPPORT == _ON))
        case _D6_INPUT_PORT:

            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_D6_ENABLE_BILLBOARD);

            break;
#endif  // End of #if((_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D6_BILLBOARD_SUPPORT == _ON))

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Type-C Billboard Control
// Input Value  : _TYPE_C_BB_DISABLE / _TYPE_C_BB_ENABLE
// Output Value : None
//--------------------------------------------------
void SysTypeCBillboardControl(BYTE ucInputPort, EnumBillboardCtrl enumAtion)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:
#if(_D0_DP_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_SCALER)
            // Turn On Scaler Billboard
            ScalerBBPllPower(enumAtion);
#elif((_D0_DP_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_HUB) && (_D0_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT))
            // Turn On Hub Billboard
            UserCommonUsbHubBillboardControl(_D0_INPUT_PORT, enumAtion);
#endif
            break;
#endif  // End of #if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D1_INPUT_PORT:

#if(_D1_DP_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_SCALER)
            // Turn On Scaler Billboard
            ScalerBBPllPower(enumAtion);

#elif((_D1_DP_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_HUB) && (_D1_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT))
            // Turn On Hub Billboard
            UserCommonUsbHubBillboardControl(_D1_INPUT_PORT, enumAtion);
#endif
            break;
#endif  // End of #if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D6_INPUT_PORT:

#if(_D6_DP_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_SCALER)
            // Turn On Scaler Billboard
            ScalerBBPllPower(enumAtion);

#elif((_D6_DP_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_HUB) && (_D6_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT))
            // Turn On Hub Billboard
            UserCommonUsbHubBillboardControl(_D6_INPUT_PORT, enumAtion);
#endif
            break;
#endif  // End of #if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)

        default:

            break;
    }
}
#endif // End of #if(_BILLBOARD_SUPPORT == _ON)

#if(_DP_USB_HUB_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Type-C Usb Hub Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysTypeCUsbHubProc(BYTE ucInputPort)
{
    // Process Hub UFP Switch
    if(SysTypeCheckCapabilityChange(ucInputPort, _TYPE_C_HUB_INPUT_SWITCH_CHG) == _TRUE)
    {
        SysTypeCHubInputSwitchProc(ucInputPort);
        SysTypeCClrCapabilityChangeFlag(ucInputPort, _TYPE_C_HUB_INPUT_SWITCH_CHG);

        DebugMessageSystem("9. [USB HUB] Hub UFP Switch To", ScalerUSB3RetimerGetHubUfpStatus());
    }

#if(_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
    // Detect Hub Connected Device Only When : "CC Attached" & "(Alt Mode Not Ready) or (Alt Mode Ready & Pin D)"
    if((UserInterfaceTypeCHubProcSupport(ucInputPort) == _TRUE) && (SysTypeCGetPortControllerCcAttach(ucInputPort) == _TYPE_C_ATTACH))
    {
        SysTypeCUsbHubDetectProc(ucInputPort);
        SysTypeCUsbHubConfigProc(ucInputPort, SysTypeCGetAltModeLaneCnt(GET_TYPE_C_PIN_ASSIGNMENT(ucInputPort)));
    }
#endif
}
#endif // End of #if(_DP_USB_HUB_SUPPORT == _ON)

#if(_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Detect Usb Hub Info
// Input Value  : ucInputPort --> Input Port
// Output Value : None
//--------------------------------------------------
void SysTypeCUsbHubDetectProc(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            SysTypeCD0UsbHubDetectProc();

            break;
#endif

#if(_D1_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            SysTypeCD1UsbHubDetectProc();

            break;
#endif


#if(_D6_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
        case _D6_INPUT_PORT:

            SysTypeCD6UsbHubDetectProc();

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Adjust Type-C Dp Lanes
// Input Value  : ucInputPort --> Input Port
//                ucDpLanes   --> Target Dp Lanes
// Output Value : None
//--------------------------------------------------
void SysTypeCUsbHubConfigProc(BYTE ucInputPort, BYTE ucDpLanes)
{
    if(ucDpLanes == _DP_LINK_2_LANE)
    {
        switch(ucInputPort)
        {
#if(_D0_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
            case _D0_INPUT_PORT:

                if(GET_D0_USB_HUB_MODE_STATE() != _USB_MODE_STATUS_SS_STATE)
                {
                    if(UserCommonUsbHubSetSSMode(_D0_INPUT_PORT, _ENABLE) == _TRUE)
                    {
                        SET_D0_USB_HUB_MODE_STATE(_USB_MODE_STATUS_SS_STATE);
                        ScalerTimerReactiveTimerEvent(SysTypeCGetUsbHubSetU3ReadyDelayTime(_D0_INPUT_PORT), _SYSTEM_TIMER_EVENT_D0_USBHUB_DETECT);
                    }
                }

                break;
#endif

#if(_D1_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
            case _D1_INPUT_PORT:

                if(GET_D1_USB_HUB_MODE_STATE() != _USB_MODE_STATUS_SS_STATE)
                {
                    if(UserCommonUsbHubSetSSMode(_D1_INPUT_PORT, _ENABLE) == _TRUE)
                    {
                        SET_D1_USB_HUB_MODE_STATE(_USB_MODE_STATUS_SS_STATE);
                        ScalerTimerReactiveTimerEvent(SysTypeCGetUsbHubSetU3ReadyDelayTime(_D1_INPUT_PORT), _SYSTEM_TIMER_EVENT_D1_USBHUB_DETECT);
                    }
                }

                break;
#endif

#if(_D6_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
            case _D6_INPUT_PORT:

                if(GET_D6_USB_HUB_MODE_STATE() != _USB_MODE_STATUS_SS_STATE)
                {
                    if(UserCommonUsbHubSetSSMode(_D6_INPUT_PORT, _ENABLE) == _TRUE)
                    {
                        SET_D6_USB_HUB_MODE_STATE(_USB_MODE_STATUS_SS_STATE);
                        ScalerTimerReactiveTimerEvent(SysTypeCGetUsbHubSetU3ReadyDelayTime(_D6_INPUT_PORT), _SYSTEM_TIMER_EVENT_D6_USBHUB_DETECT);
                    }
                }

                break;
#endif

            default:
                break;
        }
    }
    else
    {
        switch(ucInputPort)
        {
#if(_D0_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
            case _D0_INPUT_PORT:

                if(GET_D0_USB_HUB_MODE_STATE() != _USB_MODE_STATUS_DETECT_SS_STATE)
                {
                    if(UserCommonUsbHubSetSSMode(_D0_INPUT_PORT, _DISABLE) == _TRUE)
                    {
                        SET_D0_USB_HUB_MODE_STATE(_USB_MODE_STATUS_DETECT_SS_STATE);
                        ScalerTimerReactiveTimerEvent(SysTypeCGetUsbHubSetU3ReadyDelayTime(_D0_INPUT_PORT), _SYSTEM_TIMER_EVENT_D0_USBHUB_DETECT);
                    }
                }

                break;
#endif

#if(_D1_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
            case _D1_INPUT_PORT:

                if(GET_D1_USB_HUB_MODE_STATE() != _USB_MODE_STATUS_DETECT_SS_STATE)
                {
                    if(UserCommonUsbHubSetSSMode(_D1_INPUT_PORT, _DISABLE) == _TRUE)
                    {
                        SET_D1_USB_HUB_MODE_STATE(_USB_MODE_STATUS_DETECT_SS_STATE);
                        ScalerTimerReactiveTimerEvent(SysTypeCGetUsbHubSetU3ReadyDelayTime(_D1_INPUT_PORT), _SYSTEM_TIMER_EVENT_D1_USBHUB_DETECT);
                    }
                }

                break;
#endif

#if(_D6_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
            case _D6_INPUT_PORT:

                if(GET_D6_USB_HUB_MODE_STATE() != _USB_MODE_STATUS_DETECT_SS_STATE)
                {
                    if(UserCommonUsbHubSetSSMode(_D6_INPUT_PORT, _DISABLE) == _TRUE)
                    {
                        SET_D6_USB_HUB_MODE_STATE(_USB_MODE_STATUS_DETECT_SS_STATE);
                        ScalerTimerReactiveTimerEvent(SysTypeCGetUsbHubSetU3ReadyDelayTime(_D6_INPUT_PORT), _SYSTEM_TIMER_EVENT_D6_USBHUB_DETECT);
                    }
                }

                break;
#endif
            default:
                break;
        }
    }
}

//--------------------------------------------------
// Description  : Set Usb Hub Config U3 Delay Time
// Input Value  : ucInputPort --> Input Port
// Output Value : Usb Hub Info
//--------------------------------------------------
WORD SysTypeCGetUsbHubSetU3ReadyDelayTime(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)

        case _D0_INPUT_PORT:

            if(UserInterfaceTypeCUsbHubDetectDFPStatusUserFlow(_D0_INPUT_PORT) == _TRUE)
            {
                return SEC(0);
            }
            else
            {
                return SEC(2);
            }
#endif

#if(_D1_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)

        case _D1_INPUT_PORT:

            if(UserInterfaceTypeCUsbHubDetectDFPStatusUserFlow(_D1_INPUT_PORT) == _TRUE)
            {
                return SEC(0);
            }
            else
            {
                return SEC(2);
            }
#endif

#if(_D6_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
        case _D6_INPUT_PORT:

            if(UserInterfaceTypeCUsbHubDetectDFPStatusUserFlow(_D6_INPUT_PORT) == _TRUE)
            {
                return SEC(0);
            }
            else
            {
                return SEC(2);
            }
#endif

        default:
            break;
    }

    return SEC(0);
}

#if(_D0_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Detect SS Device
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysTypeCD0UsbHubDetectProc(void)
{
    CLR_D0_USB_HUB_PLUG_DEVICE_CHANGE_FLG();

    switch(GET_D0_USB_HUB_MODE_STATE())
    {
        case _USB_MODE_STATUS_INITIAL:

            SET_D0_USB_HUB_MODE_STATE(_USB_MODE_STATUS_DETECT_SS_STATE);
            SET_D0_USB_HUB_SS_DEVICE_DETECT_FLG();

            break;

        case _USB_MODE_STATUS_DETECT_SS_STATE:
        case _USB_MODE_STATUS_SS_STATE:

            if(GET_D0_USB_HUB_SS_DEVICE_DETECT_FLG() == _TRUE)
            {
                CLR_D0_USB_HUB_SS_DEVICE_DETECT_FLG();
                ScalerTimerActiveTimerEvent(UserCommonUsbHubSetPollingStep(_D0_INPUT_PORT), _SYSTEM_TIMER_EVENT_D0_USBHUB_DETECT);

                if(UserCommonUsbHubDetectDFPStatus(_D0_INPUT_PORT) == _HUB_DSP_DEVICE_CHANGE)
                {
                    SET_D0_USB_HUB_PLUG_DEVICE_CHANGE_FLG();

                    DebugMessageSystem("8. [TYPE C] <HUB> D0 Hub Info Change", GET_D0_USB_HUB_PLUG_DEVICE_CHANGE_FLG());
                }
            }

            break;

        default:
        case _USB_MODE_STATUS_PS_STATE:
        case _USB_MODE_STATUS_PD_STATE:

            break;
    }
}
#endif // End of #if(_D0_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)

#if(_D1_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Detect SS Device
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysTypeCD1UsbHubDetectProc(void)
{
    CLR_D1_USB_HUB_PLUG_DEVICE_CHANGE_FLG();

    switch(GET_D1_USB_HUB_MODE_STATE())
    {
        case _USB_MODE_STATUS_INITIAL:

            SET_D1_USB_HUB_MODE_STATE(_USB_MODE_STATUS_DETECT_SS_STATE);
            SET_D1_USB_HUB_SS_DEVICE_DETECT_FLG();

            break;

        case _USB_MODE_STATUS_DETECT_SS_STATE:
        case _USB_MODE_STATUS_SS_STATE:

            if(GET_D1_USB_HUB_SS_DEVICE_DETECT_FLG() == _TRUE)
            {
                CLR_D1_USB_HUB_SS_DEVICE_DETECT_FLG();
                ScalerTimerActiveTimerEvent(UserCommonUsbHubSetPollingStep(_D1_INPUT_PORT), _SYSTEM_TIMER_EVENT_D1_USBHUB_DETECT);

                if(UserCommonUsbHubDetectDFPStatus(_D1_INPUT_PORT) == _HUB_DSP_DEVICE_CHANGE)
                {
                    SET_D1_USB_HUB_PLUG_DEVICE_CHANGE_FLG();

                    DebugMessageSystem("8. [TYPE C] <HUB> D1 Hub Info Change", GET_D1_USB_HUB_PLUG_DEVICE_CHANGE_FLG);
                }
            }

            break;

        default:
        case _USB_MODE_STATUS_PS_STATE:
        case _USB_MODE_STATUS_PD_STATE:

            break;
    }
}
#endif // End of #if(_D1_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)

#if(_D6_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Detect SS Device
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysTypeCD6UsbHubDetectProc(void)
{
    CLR_D6_USB_HUB_PLUG_DEVICE_CHANGE_FLG();

    switch(GET_D6_USB_HUB_MODE_STATE())
    {
        case _USB_MODE_STATUS_INITIAL:

            SET_D6_USB_HUB_MODE_STATE(_USB_MODE_STATUS_DETECT_SS_STATE);
            SET_D6_USB_HUB_SS_DEVICE_DETECT_FLG();

            break;

        case _USB_MODE_STATUS_DETECT_SS_STATE:
        case _USB_MODE_STATUS_SS_STATE:

            if(GET_D6_USB_HUB_SS_DEVICE_DETECT_FLG() == _TRUE)
            {
                CLR_D6_USB_HUB_SS_DEVICE_DETECT_FLG();
                ScalerTimerActiveTimerEvent(UserCommonUsbHubSetPollingStep(_D6_INPUT_PORT), _SYSTEM_TIMER_EVENT_D6_USBHUB_DETECT);

                if(UserCommonUsbHubDetectDFPStatus(_D6_INPUT_PORT) == _HUB_DSP_DEVICE_CHANGE)
                {
                    SET_D6_USB_HUB_PLUG_DEVICE_CHANGE_FLG();

                    DebugMessageSystem("8. [TYPE C] <HUB> D6 Hub Info Change", GET_D6_USB_HUB_PLUG_DEVICE_CHANGE_FLG);
                }
            }

            break;

        default:
        case _USB_MODE_STATUS_PS_STATE:
        case _USB_MODE_STATUS_PD_STATE:

            break;
    }
}
#endif // End of #if(_D6_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)

//--------------------------------------------------
// Description  : For OSD Handler to do Process According to USB Hub Info
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysTypeCOsdHubProc(void)
{
#if(_D0_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
    if(GET_D0_USB_HUB_PLUG_DEVICE_CHANGE_FLG() == _HUB_DSP_DEVICE_CHANGE)
    {
        UserInterfaceTypeCOsdHubProc(_D0_INPUT_PORT);

        // 1. Get Latest Source Capability from Port Controller
        if(SysTypeCSetPortCtrlSourceCap(_D0_INPUT_PORT) == _TYPE_C_PDO_CHANGE)
        {
            // 2. Set Flag to Request Port Ctrl to Re-Send Source Capability Message
            SysTypeCSetCapabilityChangeFlag(_D0_INPUT_PORT, _TYPE_C_SRC_CAP_CHG);
        }

        CLR_D0_USB_HUB_PLUG_DEVICE_CHANGE_FLG();
    }
#endif

#if(_D1_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
    if(GET_D1_USB_HUB_PLUG_DEVICE_CHANGE_FLG() == _HUB_DSP_DEVICE_CHANGE)
    {
        UserInterfaceTypeCOsdHubProc(_D1_INPUT_PORT);

        CLR_D1_USB_HUB_PLUG_DEVICE_CHANGE_FLG();
    }
#endif

#if(_D6_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
    if(GET_D6_USB_HUB_PLUG_DEVICE_CHANGE_FLG() == _HUB_DSP_DEVICE_CHANGE)
    {
        UserInterfaceTypeCOsdHubProc(_D6_INPUT_PORT);

        CLR_D6_USB_HUB_PLUG_DEVICE_CHANGE_FLG();
    }
#endif
}

#endif // End of #if(_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)

#if(_DP_USB_HUB_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Control Retimer/Hub Enable/Disable
// Input Value  : ucInputPort
// Output Value : None
//--------------------------------------------------
void SysTypeCHubInputSwitchProc(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_USB_HUB_TYPE != _USB_HUB_NONE)
        case _D0_INPUT_PORT:

#if(_USB3_RETIMER_SUPPORT == _ON)
            ScalerUSB3RetimerHubUfpSwitchProc(ScalerUSB3RetimerGetHubUfpStatus());
#endif

            break;
#endif

        default:

            break;
    }
}
#endif
#endif // End of #if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

