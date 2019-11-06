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
// ID Code      : SysDP.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SYSTEM_DP__

#include "SysInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//--------------------------------------------------
// Definitions of mode search status
//--------------------------------------------------


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
#if(_DP_SUPPORT == _ON)
void SysDpRxHandler(void);
void SysDpJudgeHPDToggle(void);
void SysDpDcOffHPDToggleProc(EnumPowerAction enumSwitch);
#endif

#if(_DP_TX_SUPPORT == _ON)
void SysDpTxHandler(void);
bit SysDpTxCloneOutputStatus(void);
#if(_DP_HDCP_2_2_SUPPORT == _ON)
void SysDpTxHdcp2Handler(void);
#endif
#endif

#if(_DP_MST_SUPPORT == _ON)
void SysDpMstHandler(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_DP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Rx Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysDpRxHandler(void)
{
#if(_DP_TX_SUPPORT == _ON)
    ScalerSyncDpTxHdcpUpstreamSwitchProc(SysSourceGetInputPort());
#endif

    ScalerSyncDpCapabilitySwitchProc();

    // DP Judge HPD Toggle
    SysDpJudgeHPDToggle();

#if((_DP_TX_SUPPORT == _ON) && (_DP_HDCP_2_2_SUPPORT == _ON))
    if(GET_POWER_STATUS() == _POWER_STATUS_NORMAL)
    {
        ScalerSyncDpHdcpRepeaterCapableProc(SysSourceGetInputPort(), GET_PORT_TYPE(SysSourceGetInputPortType(SysSourceGetInputPort())));
    }
#endif

    ScalerDpHotPlugHandler();

#if(_DP_EMBEDDED_SWITCH_SUPPORT_TYPE == _DP_EMBEDDED_SWITCH_2_DP)

    // Set Embedded switch select to the target after HPD low of current port toggled by HotPlugHandler
    if(GET_DP_EMBEDDED_SWITCH_SELECT() != GET_DP_EMBEDDED_SWITCH_TARGET())
    {
        ScalerDpEmbeddedSwitchSetting(GET_DP_EMBEDDED_SWITCH_TARGET());
    }
#endif

#if(_DP_TX_SUPPORT == _ON)
    if(GET_MODE_STATE() == _MODE_STATUS_ACTIVE)
    {
        ScalerDpTxCloneOutputProc(SysSourceGetInputPort(), GET_PORT_TYPE(SysSourceGetInputPortType(SysSourceGetInputPort())), SysDpTxCloneOutputStatus());
    }
#endif
}

//--------------------------------------------------
// Description  : Decide DP Rx Judge HPD Toggle
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysDpJudgeHPDToggle(void)
{
    if(GET_DP_DC_OFF_HPD_TOGGLE_FLAG() == _TRUE)
    {
        CLR_DP_DC_OFF_HPD_TOGGLE_FLAG();

        switch(GET_POWER_STATUS())
        {
            case _POWER_STATUS_OFF:

                ScalerDpJudgeHPDToggle(_POWER_ACTION_NORMAL_TO_OFF);
                break;

            case _POWER_STATUS_NORMAL:

                if(GET_POWER_SWITCH_TO_FAKE_OFF() == _TRUE)
                {
                    ScalerDpJudgeHPDToggle(_POWER_ACTION_NORMAL_TO_FAKE_OFF);
                }
                else
                {
#if(_DP_MST_SUPPORT == _ON)
                    if(GET_DP_RX_MST_DC_OFF_HPD_TOGGLE_HOLD() == _FALSE)
#endif
                    {
                        ScalerDpJudgeHPDToggle(_POWER_ACTION_OFF_TO_NORMAL);
                    }
                }

                break;

            default:

                break;
        }
    }
}

//--------------------------------------------------
// Description  : Decide DP Rx Dc Off Set HPD Toggle Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysDpDcOffHPDToggleProc(EnumPowerAction enumSwitch)
{
    switch(enumSwitch)
    {
        case _POWER_ACTION_OFF_TO_NORMAL:
        case _POWER_ACTION_FAKE_OFF_TO_NORMAL:

            SET_DP_DC_OFF_HPD_TOGGLE_FLAG();

            break;

        default:

            break;
    }
}
#endif // End of #if(_DP_SUPPORT == _ON)

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Tx Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysDpTxHandler(void)
{
    if(GET_POWER_STATUS() == _POWER_STATUS_NORMAL)
    {
        // HPD Detection Function
        ScalerDpTxHPDProc();

        ScalerDpTxJudgeHandler();

        ScalerDpTxModeHandler();

#if(_DP_MST_SUPPORT == _ON)
        ScalerDpHDCPHandler();
#endif

#if(_DP_HDCP_2_2_SUPPORT == _ON)
        SysDpTxHdcp2Handler();
#endif
    }
}

//--------------------------------------------------
// Description  : Decide whether to Clone output to DP Tx
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit SysDpTxCloneOutputStatus(void)
{
    if(UserInterfaceGetDpCloneOutputStatus() == _FALSE)
    {
        return _FALSE;
    }

    if(ScalerSyncDpTxCloneOutputPortCheck(SysSourceGetInputPort()) == _FALSE)
    {
        return _FALSE;
    }

    if(GET_PORT_TYPE(SysSourceGetInputPortType(SysSourceGetInputPort())) == _PORT_DP)
    {
#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D0_DP_MST_PORT_SUPPORT == _OFF))
        if(SysSourceGetInputPort() == _D0_INPUT_PORT)
        {
            return _FALSE;
        }
#endif

#if((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_DP_MST_PORT_SUPPORT == _OFF))
        if(SysSourceGetInputPort() == _D1_INPUT_PORT)
        {
            return _FALSE;
        }
#endif
    }

    return _TRUE;
}

#if(_DP_HDCP_2_2_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Rx MST Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysDpTxHdcp2Handler(void)
{
    BYTE pucDpTxHdcp2Key[384];

    if(GET_DP_TX_HDCP2_LOAD_KEY_EN() == _TRUE)
    {
        CLR_DP_TX_HDCP2_LOAD_KEY_EN();

        ScalerDpTxHdcp2DcpLlcRsaInit();

        UserCommonInterfaceGetDpTxHdcp2RRMODN(0, 0x180, pucDpTxHdcp2Key);
        ScalerDpTxHdcp2LoadKeyProc(_DP_TX_HDCP2_KEY_RRMODN, pucDpTxHdcp2Key);

        UserCommonInterfaceGetDpTxHdcp2DcpLlcN(0, 0x180, pucDpTxHdcp2Key);
        ScalerDpTxHdcp2LoadKeyProc(_DP_TX_HDCP2_KEY_DCP_LLC_N, pucDpTxHdcp2Key);

        ScalerDpTxHdcp2LoadKeyProc(_DP_TX_HDCP2_KEY_EKEY1, pucDpTxHdcp2Key);

        UserCommonInterfaceGetDpTxHdcp2EKey(0, 0x80, pucDpTxHdcp2Key);
        ScalerDpTxHdcp2LoadKeyProc(_DP_TX_HDCP2_KEY_EKEY2, pucDpTxHdcp2Key);

        UserCommonInterfaceGetDpTxHdcp2NPinv(0, 0x04, pucDpTxHdcp2Key);
        ScalerDpTxHdcp2LoadKeyProc(_DP_TX_HDCP2_KEY_NPINV, pucDpTxHdcp2Key);

        SET_DP_TX_HDCP2_LOAD_KEY_FINISH();
    }
}
#endif
#endif

#if(_DP_MST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Rx MST Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysDpMstHandler(void)
{
    if(GET_POWER_STATUS() == _POWER_STATUS_NORMAL)
    {
        ScalerDpRxMstHandler();

#if(_DP_TX_SUPPORT == _ON)
        ScalerDpTxMstHandler();
#endif

        ScalerDpRxMstStreamsHandler();

        if(SysPowerGetPowerStatus() != _POWER_STATUS_OFF)
        {
            ScalerDpRxMstStreamMuxChangeHandler();
        }
    }
}
#endif
