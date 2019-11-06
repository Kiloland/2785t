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
// ID Code      : ScalerDPRx0_ComboPhy.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"

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
#if(_D0_DP_EXIST == _ON)
BYTE g_ucDpRx0PhyCtsCtrl;
StructDpLanesMapping g_stDpRx0LanesMapping;
#endif

BYTE g_ucDpRx0EQCRC;
BYTE g_ucDpValidLaneCount;


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if(_D0_DP_EXIST == _ON)
void ScalerDpRx0ChangeDpcdVersion(EnumDpVersionType enumDpVersion, EnumDPMSTPort enumDpRxMstPort);
void ScalerDpRx0CpIRQ(EnumDpRxBStatusType enumBStatusType);
bit ScalerDpRx0DecodeCheck(void);
void ScalerDpRx0SetNoVideoStreamIRQ(bit bEn);
void ScalerDpRx0DpcdLinkStatusReset(EnumDpResetStatus enumDpResetStatus);
bit ScalerDpRx0FifoCheck(EnumDpFifoCheckCondition enumFifoCheckCondition);
void ScalerDpRx0HDCPBlockReset(void);
bit ScalerDpRx0HdcpCheck(void);
bit ScalerDpRx0HdcpCheckValid(void);
bit ScalerDpRx0HdcpCheckEnabled(void);
bit ScalerDpRx0HdcpReAuthStatusCheck(void);
void ScalerDpRx0Initial(EnumDpVersionType enumDpVersion, EnumDpLaneCount enumDpLaneCount, EnumDPMSTPort enumDpRxMstPort, EnumFreeSyncSupport enumFreeSyncSupport);
void ScalerDpRx0SetDpLaneMapping(BYTE ucLanetype);
bit ScalerDpRx0MarginLinkCheck(void);
void ScalerDpRx0LinkStatusIRQ(void);
void ScalerDpRx0AuxSet(void);
bit ScalerDpRx0PSPreDetect(void);
bit ScalerDpRx0PhyCtsTp2Check(void);
void ScalerDpRx0SetFifoIRQ(bit bEn);
void ScalerDpRx0SetFifoWD(bit bEn);
void ScalerDpRx0HpdIrqAssert(void);
EnumDpHotPlugTime ScalerDpRx0BeforeHpdToggleProc(EnumDpHotPlugAssertType enumHpdType);
void ScalerDpRx0AfterHpdToggleProc(void);
void ScalerDpRx0CancelValidSignalDetectTimerEvent(void);

#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_D0_DP_EXIST == _ON)
//--------------------------------------------------
// Description  : Dp Version Switch
// Input Value  : _DP_VERSION_1_1 or _DP_VERSION_1_2
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0ChangeDpcdVersion(EnumDpVersionType enumDpVersion, EnumDPMSTPort enumDpRxMstPort)
{
    enumDpRxMstPort = _DP_MST_NO_PORT;

    if(enumDpVersion >= _DP_VERSION_1_2)
    {
        // DPCD Version
        ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x00, _DP_VERSION_1_2);

        // Set EXTENDED_RECEIVER_CAPABILITY_FIELD_PRESENT bit
        ScalerDpRx0SetDpcdBitValue(0x00, 0x00, 0x0E, ~_BIT7, 0x00);

        if(_D0_DP_LINK_CLK_RATE > _DP_HIGH_SPEED2_540MHZ)
        {
            ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x01, _DP_LINK_HBR2);
        }
        else
        {
            ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x01, _D0_DP_LINK_CLK_RATE);
        }

        // _BIT3:0, Down Stream Port Counter
        pData[0] = ScalerDpRx0GetDpcdInfo(0x00, 0x00, 0x07);
        ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x07, ((pData[0] & ~(_BIT3 | _BIT2 | _BIT1 | _BIT0)) | _DP_1_2_DOWN_STREAM_PORT_COUNT));

        // _BIT7 = 1: Always IEEE OUI Support Under DP1.2
        ScalerDpRx0SetDpcdBitValue(0x00, 0x00, 0x07, ~_BIT7, _BIT7);

        // Sink IEEE OUI
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x00, _DP_1_2_SINK_RTK_IEEE_OUI_L);
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x01, _DP_1_2_SINK_RTK_IEEE_OUI_M);
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x02, _DP_1_2_SINK_RTK_IEEE_OUI_H);

        // Sink IEEE OUI LSB For DP1.2
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x03, _DP_1_2_SINK_RTK_ID_STRING_0);
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x04, _DP_1_2_SINK_RTK_ID_STRING_1);
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x05, _DP_1_2_SINK_RTK_ID_STRING_2);
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x06, _DP_1_2_SINK_RTK_ID_STRING_3);
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x07, _DP_1_2_SINK_RTK_ID_STRING_4);
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x08, _DP_1_2_SINK_RTK_ID_STRING_5);

        // Sink HW/FW Version
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x09, _DP_1_2_SINK_RTK_HW_VERSION);
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x0A, _DP_1_2_SINK_RTK_FW_VERSION_H);
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x0B, _DP_1_2_SINK_RTK_FW_VERSION_L);
    }
    else
    {
        // DPCD Version
        ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x00, _DP_VERSION_1_1);

        // Set EXTENDED_RECEIVER_CAPABILITY_FIELD_PRESENT bit
        ScalerDpRx0SetDpcdBitValue(0x00, 0x00, 0x0E, ~_BIT7, 0x00);

        if(_D0_DP_LINK_CLK_RATE > _DP_HIGH_SPEED_270MHZ)
        {
            ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x01, _DP_LINK_HBR);
        }
        else
        {
            ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x01, _D0_DP_LINK_CLK_RATE);
        }

        // _BIT3:0, Down Stream Port Counter
        pData[0] = ScalerDpRx0GetDpcdInfo(0x00, 0x00, 0x07);
        ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x07, ((pData[0] & ~(_BIT3 | _BIT2 | _BIT1 | _BIT0)) | _DP_1_1_DOWN_STREAM_PORT_COUNT));

#if(_DP_SINK_VER11_OUI_SUPPORT == _ON)
        // _BIT7 = 1: IEEE OUI Support
        ScalerDpRx0SetDpcdBitValue(0x00, 0x00, 0x07, ~_BIT7, _BIT7);

        // Sink IEEE OUI
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x00, _DP_1_1_SINK_RTK_IEEE_OUI_L);
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x01, _DP_1_1_SINK_RTK_IEEE_OUI_M);
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x02, _DP_1_1_SINK_RTK_IEEE_OUI_H);
#else
        // _BIT7 = 0: IEEE OUI Not Support
        ScalerDpRx0SetDpcdBitValue(0x00, 0x00, 0x07, ~_BIT7, 0x00);

        // Sink IEEE OUI For DP1.1
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x00, 0x00);
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x01, 0x00);
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x02, 0x00);
#endif

        // Sink IEEE OUI LSB For DP1.1
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x03, _DP_1_1_SINK_RTK_ID_STRING_0);
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x04, _DP_1_1_SINK_RTK_ID_STRING_1);
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x05, _DP_1_1_SINK_RTK_ID_STRING_2);
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x06, _DP_1_1_SINK_RTK_ID_STRING_3);
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x07, _DP_1_1_SINK_RTK_ID_STRING_4);
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x08, _DP_1_1_SINK_RTK_ID_STRING_5);

        // Sink HW/FW Version For DP1.1
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x09, _DP_1_1_SINK_RTK_HW_VERSION);
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x0A, _DP_1_1_SINK_RTK_FW_VERSION_H);
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x0B, _DP_1_1_SINK_RTK_FW_VERSION_L);
    }

    if(ScalerDpRx0GetDpcdInfo(0x00, 0x00, 0x01) >= _DP_LINK_HBR2)
    {
        // TPS3 Support
        ScalerDpRx0SetDpcdBitValue(0x00, 0x00, 0x02, ~_BIT6, _BIT6);
    }
    else
    {
        // TPS3 NonSupport
        ScalerDpRx0SetDpcdBitValue(0x00, 0x00, 0x02, ~_BIT6, 0x00);
    }

    // Set TRAINING_AUX_RD_INTERVAL = 400us for EQ phase
    ScalerDpRx0SetDpcdBitValue(0x00, 0x00, 0x0E, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _DP_LT_AUX_RD_INTVL_EQ_400US);
}
//--------------------------------------------------
// Description  : DP Content Protection Interrupt Request
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0CpIRQ(EnumDpRxBStatusType enumBStatusType)
{
    // Link Status CPIRQ Flag
    ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x01, (ScalerDpRx0GetDpcdInfo(0x00, 0x02, 0x01) | _BIT2));

    // Set B Status
    ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x29, (ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x29) | enumBStatusType));

    if((enumBStatusType == _DP_HDCP_BSTATUS_LINK_INTEGRITY_FAIL) || (enumBStatusType == _DP_HDCP_BSTATUS_REAUTH_REQ))
    {
        // Reset HDCP Block
        ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT0, _BIT0);
        ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT0, 0x00);

        SET_DP_RX0_AUX_MANUAL_MODE();

        // Clear Aksv
        ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x07, 0x00);
        ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x08, 0x00);
        ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x09, 0x00);
        ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x0A, 0x00);
        ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x0B, 0x00);

        SET_DP_RX0_AUX_AUTO_MODE();
    }

    ScalerDpRx0HpdIrqAssert();
}
//--------------------------------------------------
// Description : check DP 8b/10b Decode Error
// Input Value  : None
// Output Value : True --> ok, False --> 8b/10b Decode Error
//--------------------------------------------------
bit ScalerDpRx0DecodeCheck(void)
{
    pData[1] = 3;

    while(pData[1] > 0)
    {
        // Clear 8b/10b Decode Error Flag
        ScalerSetBit(PB_06_DECODE_10B8B_ERROR, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

        // Delay Time us [150,x]
        DELAY_XUS(150);

        switch(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)
        {
            case _DP_ONE_LANE:

                if(((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0) && (ScalerGetBit(PB_06_DECODE_10B8B_ERROR, _BIT0) == 0x00)) ||
                   ((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1) && (ScalerGetBit(PB_06_DECODE_10B8B_ERROR, _BIT1) == 0x00)) ||
                   ((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2) && (ScalerGetBit(PB_06_DECODE_10B8B_ERROR, _BIT2) == 0x00)) ||
                   ((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3) && (ScalerGetBit(PB_06_DECODE_10B8B_ERROR, _BIT3) == 0x00)))
                {
                    return _TRUE;
                }

                break;

            case _DP_TWO_LANE:

                if(((((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0) && (GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE1)) || ((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1) && (GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE0))) &&
                    (ScalerGetBit(PB_06_DECODE_10B8B_ERROR, (_BIT1 | _BIT0)) == 0x00)) ||
                   ((((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0) && (GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE2)) || ((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2) && (GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE0))) &&
                    (ScalerGetBit(PB_06_DECODE_10B8B_ERROR, (_BIT2 | _BIT0)) == 0x00)) ||
                   ((((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0) && (GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE3)) || ((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3) && (GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE0))) &&
                    (ScalerGetBit(PB_06_DECODE_10B8B_ERROR, (_BIT3 | _BIT0)) == 0x00)) ||
                   ((((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1) && (GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE2)) || ((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2) && (GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE1))) &&
                    (ScalerGetBit(PB_06_DECODE_10B8B_ERROR, (_BIT2 | _BIT1)) == 0x00)) ||
                   ((((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1) && (GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE3)) || ((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3) && (GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE1))) &&
                    (ScalerGetBit(PB_06_DECODE_10B8B_ERROR, (_BIT3 | _BIT1)) == 0x00)) ||
                   ((((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2) && (GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE3)) || ((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3) && (GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE2))) &&
                    (ScalerGetBit(PB_06_DECODE_10B8B_ERROR, (_BIT3 | _BIT2)) == 0x00)))
                {
                    return _TRUE;
                }

                break;

            case _DP_FOUR_LANE:

                if(ScalerGetBit(PB_06_DECODE_10B8B_ERROR, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) == 0x00)
                {
                    return _TRUE;
                }

                break;

            default:

                return _FALSE;

                break;
        }

        pData[1]--;
    }

    DebugMessageRx0("7. DP 8b/10b Decode Error", 0);

    return _FALSE;
}

//--------------------------------------------------
// Description  : Enable DP Fifo Under/OverFlow IRQ
// Input Value  : _ENABLE/ DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0SetNoVideoStreamIRQ(bit bEn)
{
    // VB-ID[3] Change Flag
    ScalerSetBit(PB6_36_DP_GLB_STATUS, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT6);

    // VB-ID[3] Change IRQ
    ScalerSetBit(PB6_3B_DP_IRQ_CTRL1, ~_BIT4, ((bEn == _ENABLE) ? _BIT4 : 0x00));
}

//--------------------------------------------------
// Description  : DPCD Link Status Field Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0DpcdLinkStatusReset(EnumDpResetStatus enumDpResetStatus)
{
    pData[0] = ScalerGetByte(PB7_D0_AUX_MODE_SET);

    SET_DP_RX0_AUX_MANUAL_MODE();

    if(enumDpResetStatus == _DP_DPCD_LINK_STATUS_INITIAL)
    {
        // Set DPCD 00600h to 0x01
        ScalerDpRx0SetDpcdBitValue(0x00, 0x06, 0x00, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
    }

    ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x02, 0x00);
    ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x03, 0x00);
    ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x04, 0x80);
    ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x05, 0x00);
    ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x06, 0x00);
    ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x07, 0x00);

    SET_DP_RX0_LINK_TRAINING_STATUS(_DP_LINK_TRAINING_NONE);

    CLR_DP_RX0_BACKUP_PD_LINK_STATUS_FLG();

    if((pData[0] & _BIT1) == _BIT1)
    {
        SET_DP_RX0_AUX_AUTO_MODE();
    }
}
//--------------------------------------------------
// Description  : DP Video Fifo Check
// Input Value  : Fifo Check Condition
// Output Value : True --> Fifo not over/underflow
//--------------------------------------------------
bit ScalerDpRx0FifoCheck(EnumDpFifoCheckCondition enumFifoCheckCondition)
{
    if(enumFifoCheckCondition == _DP_FIFO_DELAY_CHECK)
    {
        ScalerSetBit(PB5_21_PG_CTRL_1, ~(_BIT4 | _BIT2 | _BIT0), (_BIT4 | _BIT2 | _BIT0));

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
        if(GET_AIO_MODERN_STANDBY_MODE() == _FALSE)
#endif
        {
            ScalerTimerDelayXms(_DP_TWO_FRAME_TIME_MAX);

            pData[0] = 0;

            while(pData[0] < 6)
            {
                ScalerTimerDelayXms(10);

                if((ScalerGetBit(PB5_21_PG_CTRL_1, _BIT4) == _BIT4) || (ScalerGetBit(PB5_21_PG_CTRL_1, _BIT2) == _BIT2))
                {
                    return _FALSE;
                }

                pData[0]++;
            }
        }
    }
    else
    {
        if((ScalerGetBit(PB5_21_PG_CTRL_1, _BIT4) == _BIT4) || (ScalerGetBit(PB5_21_PG_CTRL_1, _BIT2) == _BIT2))
        {
            return _FALSE;
        }
    }

    if(ScalerGetBit(PB6_3B_DP_IRQ_CTRL1, _BIT4) == 0x00)
    {
        // Enable DP No Video Stream IRQ
        ScalerDpRx0SetNoVideoStreamIRQ(_ENABLE);
    }

    if(ScalerDpRx0GetDpcdBitInfo(0x00, 0x02, 0x05, _BIT0) == 0x00)
    {
        // Set DP Receive Port0 In Sync
        ScalerDpRx0SinkStatusSet(_DP_SINK_REVEICE_PORT0, _DP_SINK_IN_SYNC);
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : HDCP Reset For Dp Rx0
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0HDCPBlockReset(void)
{
    // Reset HDCP Block
    ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT0, _BIT0);
    ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT0, 0x00);

    ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x29, 0x00);
    ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x2A, 0x00);
    ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x2B, 0x00);

    for(pData[0] = 0; pData[0] < 20; pData[0]++)
    {
        ScalerDpRx0SetDpcdValue(0x06, 0x80, (0x14 + pData[0]), 0x00);
    }

    for(pData[0] = 0; pData[0] < 15; pData[0]++)
    {
        ScalerDpRx0SetDpcdValue(0x06, 0x80, (0x2C + pData[0]), 0x00);
    }

    SET_DP_RX0_AUX_MANUAL_MODE();

    // Clear Aksv
    ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x07, 0x00);
    ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x08, 0x00);
    ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x09, 0x00);
    ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x0A, 0x00);
    ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x0B, 0x00);

    SET_DP_RX0_AUX_AUTO_MODE();
}

//--------------------------------------------------
// Description  : Check DP Link Integrity
// Input Value  : None
// Output Value : FALSE => DP Link Integrity Fail
//--------------------------------------------------
bit ScalerDpRx0HdcpCheck(void)
{
    if((ScalerGetByte(PB_1E_HDCP_INTGT_VRF_ANS_MSB) != 0x00) && (ScalerGetByte(PB_1F_HDCP_INTGT_VRF_ANS_LSB) != 0x00) &&
       (ScalerGetByte(PB_1E_HDCP_INTGT_VRF_ANS_MSB) != 0x53) && (ScalerGetByte(PB_1F_HDCP_INTGT_VRF_ANS_LSB) != 0x1F) &&
       ((ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x07) != 0x00) ||
        (ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x08) != 0x00) ||
        (ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x09) != 0x00) ||
        (ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x0A) != 0x00) ||
        (ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x0B) != 0x00)))
    {
        if((ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x11) & _BIT2) == 0x00)
        {
            return _FALSE;
        }

        if(ScalerDpRx0HdcpMeasureCheck() == _FALSE)
        {
            return _FALSE;
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Check whether HDCP is valid
// Input Value  : None
// Output Value : TRUE => HDCP valid
//--------------------------------------------------
bit ScalerDpRx0HdcpCheckValid(void)
{
    if(ScalerGetBit(PB_20_HDCP_DEBUG, (_BIT7 | _BIT6 | _BIT5)) == (_BIT7 | _BIT6 | _BIT5))
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check whether HDCP is enabled
// Input Value  : None
// Output Value : TRUE => HDCP Enabled
//--------------------------------------------------
bit ScalerDpRx0HdcpCheckEnabled(void)
{
    if(ScalerGetBit(PB_20_HDCP_DEBUG, (_BIT7 | _BIT5)) == (_BIT7 | _BIT5))
    {
        if((ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x07) != 0x00) ||
           (ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x08) != 0x00) ||
           (ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x09) != 0x00) ||
           (ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x0A) != 0x00) ||
           (ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x0B) != 0x00))
        {
            return _TRUE;
        }
    }

    return _FALSE;
}
//--------------------------------------------------
// Description  : Check DP Hdcp ReAuth Process
// Input Value  : None
// Output Value : TRUE or FALSE
//--------------------------------------------------
bit ScalerDpRx0HdcpReAuthStatusCheck(void)
{
    if((ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x07) != 0x00) || (ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x08) != 0x00) ||
       (ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x09) != 0x00) || (ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x0A) != 0x00) ||
       (ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x0B) != 0x00))
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}
//--------------------------------------------------
// Description  : Initial Setting for DP
// Input Value  : _DP_VERSION_1_1 or _DP_VERSION_1_2
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0Initial(EnumDpVersionType enumDpVersion, EnumDpLaneCount enumDpLaneCount, EnumDPMSTPort enumDpRxMstPort, EnumFreeSyncSupport enumFreeSyncSupport)
{
    ScalerDpRx0AuxIntInitial();

    ScalerDpRx0DpcdInitial(enumDpVersion, enumDpLaneCount, enumDpRxMstPort, enumFreeSyncSupport);

#if(_DP_ASSR_MODE_SUPPORT == _ON)
    SET_DP_RX0_AUX_MANUAL_MODE();
    ScalerDpRx0SetDpcdValue(0x00, 0x01, 0x0A, 0x00);
    SET_DP_RX0_AUX_AUTO_MODE();
#endif

    SET_DP_RX0_LINK_TRAINING_STATUS(_DP_LINK_TRAINING_NONE);

    SET_DP_RX0_FAKE_LINK_TRAINING();

    SET_DP_RX_TARGET_MST_PORT(enumDpRxMstPort);
    SET_DP_RX_D0_PORT_TARGET_VERSION(enumDpVersion);
    SET_DP_RX_D0_PORT_TARGET_LANE_COUNT(enumDpLaneCount);

    ScalerDpRx0SetDpLaneMapping(_DP_LANE_MAPPING_NORMAL_TYPE);
}

//--------------------------------------------------
// Description  : Set DP Lane Mapping Type
// Input Value  : ucLanetype --> Lane Mapping Type
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0SetDpLaneMapping(BYTE ucLanetype)
{
    if(ucLanetype == _DP_LANE_MAPPING_TYPE_C_ASSIGNMENT_E_TYPE)
    {
        // Lane 0 <--> Lane 2
        // Lane 1 <--> Lane 3
        SET_DP_RX0_PCB_LANE0_MAPPING(_D0_DP_PCB_LANE2_MAPPING);
        SET_DP_RX0_PCB_LANE1_MAPPING(_D0_DP_PCB_LANE3_MAPPING);
        SET_DP_RX0_PCB_LANE2_MAPPING(_D0_DP_PCB_LANE0_MAPPING);
        SET_DP_RX0_PCB_LANE3_MAPPING(_D0_DP_PCB_LANE1_MAPPING);
        SET_DP_RX0_PCB_LANE0_PN_SWAP(!_D0_DP_PCB_LANE0_PN_SWAP);
        SET_DP_RX0_PCB_LANE1_PN_SWAP(!_D0_DP_PCB_LANE1_PN_SWAP);
        SET_DP_RX0_PCB_LANE2_PN_SWAP(!_D0_DP_PCB_LANE2_PN_SWAP);
        SET_DP_RX0_PCB_LANE3_PN_SWAP(!_D0_DP_PCB_LANE3_PN_SWAP);

#if(_D0_DP_TYPE_C_PIN_E_AUXPN_SWAP == _SWAP_BY_SCALER)
        // Enable Aux Digital Phy PN Swap
        ScalerSetBit(PB7_72_AUX_DIG_PHY2, ~_BIT0, _BIT0);
#else
        // Disable Aux Digital Phy PN Swap
        ScalerSetBit(PB7_72_AUX_DIG_PHY2, ~_BIT0, 0x00);
#endif
    }
    else // Normal Cable Mode
    {
        SET_DP_RX0_PCB_LANE0_MAPPING(_D0_DP_PCB_LANE0_MAPPING);
        SET_DP_RX0_PCB_LANE1_MAPPING(_D0_DP_PCB_LANE1_MAPPING);
        SET_DP_RX0_PCB_LANE2_MAPPING(_D0_DP_PCB_LANE2_MAPPING);
        SET_DP_RX0_PCB_LANE3_MAPPING(_D0_DP_PCB_LANE3_MAPPING);
        SET_DP_RX0_PCB_LANE0_PN_SWAP(_D0_DP_PCB_LANE0_PN_SWAP);
        SET_DP_RX0_PCB_LANE1_PN_SWAP(_D0_DP_PCB_LANE1_PN_SWAP);
        SET_DP_RX0_PCB_LANE2_PN_SWAP(_D0_DP_PCB_LANE2_PN_SWAP);
        SET_DP_RX0_PCB_LANE3_PN_SWAP(_D0_DP_PCB_LANE3_PN_SWAP);

        // Disable Aux Digital Phy PN Swap
        ScalerSetBit(PB7_72_AUX_DIG_PHY2, ~_BIT0, 0x00);
    }
}

//--------------------------------------------------
// Description  : DP Margin Link Check
// Input Value  : None
// Output Value : _TRUE : Link ok ; _FALSE : Margin Link
//--------------------------------------------------
bit ScalerDpRx0MarginLinkCheck(void)
{
    return _TRUE;
}

//--------------------------------------------------
// Description  : Dp Interrupt Request
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0LinkStatusIRQ(void)
{
    SET_DP_RX0_AUX_MANUAL_MODE();

    if((GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_LINK_TRAINING_FAIL) || (GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_LINK_STATUS_FAIL))
    {
        ScalerDpRx0DpcdLinkStatusReset(_DP_DPCD_LINK_STATUS_IRQ);

        SET_DP_RX0_AUX_AUTO_MODE();

        ScalerDpRx0HDCPBlockReset();

        if((ScalerDpRx0GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) != _BIT1) &&
           (ScalerDpRx0GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) != (_BIT2 | _BIT0)))
        {
            if(GET_DP_EMBEDDED_SWITCH_SELECT() == _D0_INPUT_PORT)
            {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_HDCP_LONG_HOTPLUG_EVENT);
#endif
            }
            else if(GET_DP_EMBEDDED_SWITCH_SELECT() == _D1_INPUT_PORT)
            {
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_HDCP_LONG_HOTPLUG_EVENT);
#endif
            }
            else if(GET_DP_EMBEDDED_SWITCH_SELECT() == _D2_INPUT_PORT)
            {
#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX2_HDCP_LONG_HOTPLUG_EVENT);
#endif
            }

            ScalerDpRx0HpdIrqAssert();
        }
    }

    SET_DP_RX0_AUX_AUTO_MODE();
}

//-------------------------------------------------------
// Description  : Set Aux Diff mode or Single-eneded mode
// Input Value  : None
// Output Value : None
//-------------------------------------------------------
void ScalerDpRx0AuxSet(void)
{
#if(_HW_DP_AUX_SINGLE_ENDED_MODE_SUPPORT == _ON)
    if(GET_DP_AUX_DIFF_MODE() == _FALSE)
    {
        // Set TX VLDO = 1.05V, Open AUX ADJR_P, Rx Common Mode from 3.3V
        ScalerSetByte(PB7_61_AUX_1, ((_DP_AUX_SWING_1050_MV << 5) | _BIT4));

        // [5]Enable Single-Ended Mode, [4:3]Aux Vth-->50mV, [0]Aux 50ohm auto K(Enable Big_Z0_P)
        ScalerSetByte(PB7_62_AUX_2, 0x29);

        // [4]Enable Big_Z0_N, [3:0]Open ADJR_N
        ScalerSetBit(PB7_66_AUX_6, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);
    }
    else
#endif
    {
        // Set TX VLDO = 1.05V, Rx Common Mode from 3.3V
        ScalerSetBit(PB7_61_AUX_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ((_DP_AUX_SWING_1050_MV << 5) | _BIT4));

        // [5]Disable Single-Ended Mode, [4:3]Aux Vth-->50mV, [0]Aux 50ohm auto K(Enable Big_Z0_P)
        ScalerSetByte(PB7_62_AUX_2, 0x09);

        // [4]Enable Big_Z0_N
        ScalerSetBit(PB7_66_AUX_6, ~_BIT4, _BIT4);

        // AUX RX0 P Channel Resistance Setting
        ScalerSetBit(PB7_61_AUX_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_AUX_ADJR_SETTING());

        // AUX RX0 N Channel Resistance Setting
        ScalerSetBit(PB7_66_AUX_6, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_AUX_ADJR_SETTING());
    }
}

//--------------------------------------------------
// Description  : Signal Detection for DP(Power Saving)
// Input Value  : None
// Output Value : True : DP Signal Detected
//              : False : No Signal
//--------------------------------------------------
bit ScalerDpRx0PSPreDetect(void)
{
    // Back to noraml for DP PHY CTS
    if(GET_DP_RX0_PHY_CTS_FLG() == _TRUE)
    {
        return _TRUE;
    }

    if(GET_DP_RX0_VALID_VIDEO_CHECK() == _TRUE)
    {
        DebugMessageRx0("7. Valid Video Check", 0);

        return _TRUE;
    }

    if(GET_DP_RX0_PS_AUX_TOGGLE() == _TRUE)
    {
        DebugMessageRx0("7. Power Saving Aux Handshake", 0);

        return _TRUE;
    }

    if(GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_NORMAL_LINK_TRAINING_PASS)
    {
        DebugMessageRx0("7. Normal Link Training under Fake Power Saving Case", 0);

        return _TRUE;
    }

    if(((GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_FAKE_LINK_TRAINING_PASS) &&
        ((ScalerDpRx0GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) != _BIT1) &&
         (ScalerDpRx0GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) != (_BIT2 | _BIT0)))) ||
       (GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_FAKE_LINK_TRAINING_PASS_VBIOS))
    {
#if((_SLEEP_AUDIO_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_DP)))

        if(ScalerAudioGetDigitalAudioSource(_D0_INPUT_PORT) == _DIGITAL_AUDIO_SOURCE_DP)
        {
            DebugMessageAudio("00. DP Power Saving Audio : Idle Pattern Case", ScalerAudioGetDigitalAudioSource(_D0_INPUT_PORT));
            return _TRUE;
        }
#endif
        DebugMessageRx0("7. Idle Pattern Case", 0);

        return _TRUE;
    }

    return _FALSE;
}
//--------------------------------------------------
// Description  : Check Dp Training Pattern 2 for PHY CTS
// Input Value  : None
// Output Value : TRUE --> TP2 Pass
//--------------------------------------------------
bit ScalerDpRx0PhyCtsTp2Check(void)
{
    ScalerTimerDelayXms(10);

    switch(g_ucDpRx0PhyCtsCtrl & 0x30)
    {
        case 0x00: // Lane0 Test

            ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), 0x00);

            break;

        case 0x10: // Lane1 Test

            ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), _BIT3);

            break;

        case 0x20: // Lane2 Test

            ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), _BIT4);

            break;

        case 0x30: // Lane3 Test

            ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));

            break;

        default:
            break;
    }

    // Mac Use Xtal Clk
    ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT6, _BIT6);

    // Clear EQ-CRC
    ScalerSetBit(PB_12_EQ_CRC_1, ~(_BIT7 | _BIT6), _BIT6);

    // Start Calculate EQ-CRC
    ScalerSetBit(PB_12_EQ_CRC_1, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    ScalerTimerDelayXms(2);

    ScalerSetByte(PB7_A1_AUX_RESERVE1, ScalerGetByte(PB_12_EQ_CRC_1));
    ScalerSetByte(PB7_A2_AUX_RESERVE2, ScalerGetByte(PB_13_EQ_CRC_2));
    ScalerSetByte(PB7_A3_AUX_RESERVE3, g_ucDpRx0PhyCtsCtrl & 0x30);

    ScalerSetBit(PB_12_EQ_CRC_1, ~(_BIT7 | _BIT6), _BIT6);

    switch(g_ucDpRx0PhyCtsCtrl & 0x30)
    {
        case 0x00: // Lane0 Test

            pData[0] = 0x01;

            break;

        case 0x10: // Lane1 Test

            pData[0] = 0x02;

            break;

        case 0x20: // Lane2 Test

            pData[0] = 0x04;

            break;

        case 0x30: // Lane3 Test

            pData[0] = 0x08;

            break;

        default:

            pData[0] = 0x00;

            break;
    }

    if((ScalerGetByte(PB7_A1_AUX_RESERVE1) & pData[0]) != 0x00)
    {
        return _TRUE;
    }

    return _FALSE;
}
//--------------------------------------------------
// Description  : Enable DP Fifo Under/OverFlow IRQ
// Input Value  : _ENABLE/ DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0SetFifoIRQ(bit bEn)
{
    ScalerSetBit(PB6_3A_DP_IRQ_CTRL0, ~(_BIT1 | _BIT0), ((bEn == _ENABLE) ? (_BIT1 | _BIT0) : 0x00));
}
//--------------------------------------------------
// Description  : Enable DP Fifo Under/OverFlow Watch Dog
// Input Value  : _ENABLE/ DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0SetFifoWD(bit bEn)
{
    ScalerSetBit(PB6_38_DP_VWD_CTRL, ~(_BIT5 | _BIT4), ((bEn == _ENABLE) ? (_BIT5 | _BIT4) : 0x00));
}

//--------------------------------------------------
// Description  : Dp IRQ Assert Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0HpdIrqAssert(void)
{
    BYTE ucBackUp = 0;

    ucBackUp = ScalerGetByte(PB7_D0_AUX_MODE_SET);

    if((GET_DP_EMBEDDED_SWITCH_SELECT() == _D0_INPUT_PORT) && (PCB_D0_HOTPLUG_DETECT() == _D0_HOT_PLUG_HIGH))
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        SET_DP_RX0_AUX_MANUAL_MODE();

        PCB_D0_HOTPLUG(_D0_HOT_PLUG_LOW);

        // Default = 750us
        switch(GET_DP_IRQ_TIME_10US())
        {
            case 55:
                DELAY_XUS(500);
                break;

            case 60:
                DELAY_XUS(546);
                break;

            case 65:
                DELAY_XUS(588);
                break;

            case 70:
                DELAY_XUS(634);
                break;

            case 75:
                DELAY_XUS(682);
                break;

            case 80:
                DELAY_XUS(728);
                break;

            case 85:
                DELAY_XUS(768);
                break;

            case 90:
                DELAY_XUS(816);
                break;

            case 95:
                DELAY_XUS(862);
                break;

            default:
                DELAY_XUS(682);
                break;
        }

        PCB_D0_HOTPLUG(_D0_HOT_PLUG_HIGH);

        if((ucBackUp & _BIT1) == _BIT1)
        {
            SET_DP_RX0_AUX_AUTO_MODE();
        }
#endif
    }
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
    else if((GET_DP_EMBEDDED_SWITCH_SELECT() == _D1_INPUT_PORT) && (PCB_D1_HOTPLUG_DETECT() == _D1_HOT_PLUG_HIGH))
    {
        SET_DP_RX0_AUX_MANUAL_MODE();

        PCB_D1_HOTPLUG(_D1_HOT_PLUG_LOW);

        // Default = 750us
        switch(GET_DP_IRQ_TIME_10US())
        {
            case 55:
                DELAY_XUS(500);
                break;

            case 60:
                DELAY_XUS(546);
                break;

            case 65:
                DELAY_XUS(588);
                break;

            case 70:
                DELAY_XUS(634);
                break;

            case 75:
                DELAY_XUS(682);
                break;

            case 80:
                DELAY_XUS(728);
                break;

            case 85:
                DELAY_XUS(768);
                break;

            case 90:
                DELAY_XUS(816);
                break;

            case 95:
                DELAY_XUS(862);
                break;

            default:
                DELAY_XUS(682);
                break;
        }

        PCB_D1_HOTPLUG(_D1_HOT_PLUG_HIGH);

        if((ucBackUp & _BIT1) == _BIT1)
        {
            SET_DP_RX0_AUX_AUTO_MODE();
        }
    }
#endif
#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
    else if((GET_DP_EMBEDDED_SWITCH_SELECT() == _D2_INPUT_PORT) && (PCB_D2_HOTPLUG_DETECT() == _D2_HOT_PLUG_HIGH))
    {
        SET_DP_RX0_AUX_MANUAL_MODE();

        PCB_D2_HOTPLUG(_D2_HOT_PLUG_LOW);

        // Default = 750us
        switch(GET_DP_IRQ_TIME_10US())
        {
            case 55:
                DELAY_XUS(500);
                break;

            case 60:
                DELAY_XUS(546);
                break;

            case 65:
                DELAY_XUS(588);
                break;

            case 70:
                DELAY_XUS(634);
                break;

            case 75:
                DELAY_XUS(682);
                break;

            case 80:
                DELAY_XUS(728);
                break;

            case 85:
                DELAY_XUS(768);
                break;

            case 90:
                DELAY_XUS(816);
                break;

            case 95:
                DELAY_XUS(862);
                break;

            default:
                DELAY_XUS(682);
                break;
        }

        PCB_D2_HOTPLUG(_D2_HOT_PLUG_HIGH);

        if((ucBackUp & _BIT1) == _BIT1)
        {
            SET_DP_RX0_AUX_AUTO_MODE();
        }
    }
#endif

    // For Meeting Spec of HPD_IRQ Minimum Spacing >= 2 ms
    ScalerTimerDelayXms(3);
}

//--------------------------------------------------
// Description  : Dp Before Hpd Toggle Process
// Input Value  : EnumDpHotPlugAssertType
// Output Value : None
//--------------------------------------------------
EnumDpHotPlugTime ScalerDpRx0BeforeHpdToggleProc(EnumDpHotPlugAssertType enumHpdType)
{
    if(enumHpdType == _DP_HPD_NONE)
    {
        return _DP_HPD_TIME_NONE;
    }

    ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_RX0_DP_LINK_TRAINING_REBUILD_PHY);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_VALID_SIGNAL_DETECT_CHECK);

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_HOTPLUG_ASSERTED);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_HDCP_LONG_HOTPLUG_EVENT);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_LINK_STATUS_IRQ);
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_HOTPLUG_ASSERTED);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_HDCP_LONG_HOTPLUG_EVENT);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_LINK_STATUS_IRQ);
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX2_HOTPLUG_ASSERTED);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX2_HDCP_LONG_HOTPLUG_EVENT);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX2_LINK_STATUS_IRQ);
#endif

    if(enumHpdType == _DP_HPD_ASSERTED)
    {
        switch(GET_DP_EMBEDDED_SWITCH_SELECT())
        {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

            case _D0_INPUT_PORT:

                if(PCB_D0_HOTPLUG_DETECT() == _D0_HOT_PLUG_HIGH)
                {
                    return _DP_HPD_TIME_NONE;
                }

                break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

            case _D1_INPUT_PORT:

                if(PCB_D1_HOTPLUG_DETECT() == _D1_HOT_PLUG_HIGH)
                {
                    return _DP_HPD_TIME_NONE;
                }

                break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)

            case _D2_INPUT_PORT:

                if(PCB_D2_HOTPLUG_DETECT() == _D2_HOT_PLUG_HIGH)
                {
                    return _DP_HPD_TIME_NONE;
                }

                break;
#endif

            default:

                return _DP_HPD_TIME_NONE;
        }
    }
    else
    {
        ScalerDpRx0AVMute();

        ScalerDpRx0DpcdLinkStatusReset(_DP_DPCD_LINK_STATUS_INITIAL);
    }

    if(enumHpdType == _DP_HPD_LOW)
    {
        DebugMessageRx0("_D0_HOT_PLUG_LOW", 0);

        switch(GET_DP_EMBEDDED_SWITCH_SELECT())
        {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

            case _D0_INPUT_PORT:

                PCB_D0_HOTPLUG(_D0_HOT_PLUG_LOW);

                break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

            case _D1_INPUT_PORT:

                PCB_D1_HOTPLUG(_D1_HOT_PLUG_LOW);

                break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)

            case _D2_INPUT_PORT:

                PCB_D2_HOTPLUG(_D2_HOT_PLUG_LOW);

                break;
#endif

            default:
                break;
        }

        return _DP_HPD_TIME_NONE;
    }
    else if(enumHpdType == _DP_HPD_LOW_RESET_AUX)
    {
        // Reset Aux
        ScalerSetBit(PB7_C0_DPCD_CTRL, ~_BIT7, _BIT7);

        DebugMessageRx0("_D0_HOT_PLUG_LOW", 0);

        switch(GET_DP_EMBEDDED_SWITCH_SELECT())
        {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

            case _D0_INPUT_PORT:

                PCB_D0_HOTPLUG(_D0_HOT_PLUG_LOW);

                break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

            case _D1_INPUT_PORT:

                PCB_D1_HOTPLUG(_D1_HOT_PLUG_LOW);

                break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)

            case _D2_INPUT_PORT:

                PCB_D2_HOTPLUG(_D2_HOT_PLUG_LOW);

                break;
#endif

            default:
                break;
        }

        return _DP_HPD_TIME_NONE;
    }

    // Reset DDC0
    MCU_FF1F_DDC0_DDC_CONTROL_1 |= _BIT1;

    // Release Aux
    ScalerSetBit(PB7_C0_DPCD_CTRL, ~_BIT7, 0x00);

#if(_DP_FREESYNC_SUPPORT == _ON)
    SET_DP_RX0_AUX_MANUAL_MODE();
    ScalerDpRx0SetDpcdValue(0x00, 0x01, 0x07, 0x00);
    SET_DP_RX0_AUX_AUTO_MODE();
#endif

    ScalerDpRx0HDCPUnplugReset();

#if(_DP_ASSR_MODE_SUPPORT == _ON)
    SET_DP_RX0_AUX_MANUAL_MODE();
    ScalerDpRx0SetDpcdValue(0x00, 0x01, 0x0A, 0x00);
    SET_DP_RX0_AUX_AUTO_MODE();
#endif

    if(enumHpdType == _DP_LONG_HPD_EVENT)
    {
        return _DP_LONG_HPD_TIME;
    }
    else if(enumHpdType == _DP_HDCP_LONG_HPD_EVENT)
    {
        return _DP_HDCP_LONG_HPD_TIME;
    }
    else if(enumHpdType == _DP_MST_LONG_HPD_EVENT)
    {
        return _DP_MST_LONG_HPD_TIME;
    }
    else if(enumHpdType == _DP_HPD_ASSERTED)
    {
        return _DP_HPD_ASSERTED_TIME;
    }

    return _DP_HPD_TIME_NONE;
}

//--------------------------------------------------
// Description  : Dp After Hpd Toggle Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0AfterHpdToggleProc(void)
{
    // Reset Aux
    ScalerSetBit(PB7_C0_DPCD_CTRL, ~_BIT7, _BIT7);

    // Release Aux
    ScalerSetBit(PB7_C0_DPCD_CTRL, ~_BIT7, 0x00);

    SET_DP_RX0_AUX_MANUAL_MODE();

    if((GET_DP_RX0_LINK_TRAINING_STATUS() != _DP_NORMAL_LINK_TRAINING_PASS) && (GET_DP_RX0_LINK_TRAINING_STATUS() != _DP_FAKE_LINK_TRAINING_PASS))
    {
        ScalerDpRx0SetDpcdValue(0x00, 0x01, 0x00, 0x00);
        ScalerDpRx0SetDpcdValue(0x00, 0x01, 0x01, (ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x01) & 0xE0));
    }

    SET_DP_RX0_AUX_AUTO_MODE();

#if(_DP_EMBEDDED_SWITCH_SUPPORT_TYPE == _DP_EMBEDDED_SWITCH_2_DP)
    if(GET_DP_AUTO_SEARCH_SWITCH() == _FALSE)
#endif
    {
        if(((GET_DP_EMBEDDED_SWITCH_SELECT() == _D0_INPUT_PORT) && (ScalerSyncDpCableStatus(_D0_INPUT_PORT) == _TRUE)) ||
           ((GET_DP_EMBEDDED_SWITCH_SELECT() == _D1_INPUT_PORT) && (ScalerSyncDpCableStatus(_D1_INPUT_PORT) == _TRUE)) ||
           ((GET_DP_EMBEDDED_SWITCH_SELECT() == _D2_INPUT_PORT) && (ScalerSyncDpCableStatus(_D2_INPUT_PORT) == _TRUE)))
        {
            ScalerTimerActiveTimerEvent(SEC(1.2), _SCALER_TIMER_EVENT_DP_RX0_VALID_SIGNAL_DETECT_CHECK);
        }
    }
}

//--------------------------------------------------
// Description  : Dp Rx0 Cancel ValidSignalDetect TimerEvent
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0CancelValidSignalDetectTimerEvent(void)
{
#if(_D0_DP_EXIST == _ON)
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_VALID_SIGNAL_DETECT_CHECK);
#endif
#if(_D1_DP_EXIST == _ON)
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_VALID_SIGNAL_DETECT_CHECK);
#endif
}

#endif
