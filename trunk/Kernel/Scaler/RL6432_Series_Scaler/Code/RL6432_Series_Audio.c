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
// ID Code      : RL6432_Series_Audio.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"

#if(_AUDIO_SUPPORT == _ON)

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
StructAudioDigitalInfo g_stAudioD0DigtalInfo;
#endif

#if((_D1_HDMI_SUPPORT == _ON) || (_D1_DP_EXIST == _ON))
StructAudioDigitalInfo g_stAudioD1DigtalInfo;
#endif

#if(_D2_HDMI_SUPPORT == _ON)
StructAudioDigitalInfo g_stAudioD2DigtalInfo;
#endif

#if(_D3_HDMI_SUPPORT == _ON)
StructAudioDigitalInfo g_stAudioD3DigtalInfo;
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerAudioDigitalAudioInitial(void);
void ScalerAudioDisableAudioPLL(void);
void ScalerAudioDigitalDetect(void);
bit ScalerAudioGetAudioDetected(BYTE ucInputPort);
EnumAudioSamplingFreqPacket ScalerAudioSamplingFreqDetect(BYTE ucInputPort);
bit ScalerAudioLPCMCheckData(BYTE ucInputPort);
void ScalerAudioDigitalOutputMute(bit bMute);
void ScalerAudioWatchDogProc(bit bOn, BYTE ucInputPort);
void ScalerAudioLoadStableICodeEvent(EnumScalerTimerEventID enumEventID);
void ScalerAudioSourceInputSwitch(EnumAudioInputSource enumAudioSource, BYTE ucInputPort);
EnumSourceSearchPort ScalerAudioGetDigitalAudioPortMapping(void);

#if((_D1_HDMI_SUPPORT == _ON) || (_D1_DP_EXIST == _ON))
void ScalerAudioD1LoadInitialICode(void);
void ScalerAudioD1LoadStableICodeEvent(void);
void ScalerAudioD1DigitalDetectProc(void);
bit ScalerAudioD1GetAudioDetected(void);
EnumAudioSamplingFreqType ScalerAudioD1SamplingFreqDetect(void);
void ScalerAudioD1WatchDogProc(bit bOn);

#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
void ScalerAudioD1InternalAudioGenSwitch(bit bOn);
bit ScalerAudioD1GetInternalAudioGenEnable(void);
#endif
#endif

#if(_HDMI_SUPPORT == _ON)
#if((_D1_HDMI_SUPPORT == _ON) || (_D2_HDMI_SUPPORT == _ON))
void ScalerAudioD2HDMIAudioInitial(void);
void ScalerAudioD2SetAudioPLL(void);
#endif

#if(_D2_HDMI_SUPPORT == _ON)
EnumAudioSamplingFreqType ScalerAudioD2SamplingFreqDetect(void);
#endif

bit ScalerAudioLPCMCheckInfo(BYTE ucInputPort);
#endif

#if(_DP_SUPPORT == _ON)
void ScalerAudioDPDigitalOutputProc(bit bEnable, BYTE ucInputPort);

#if(_D0_DP_EXIST == _ON)
void ScalerAudioD0SetAudioPLL(void);
void ScalerAudioD0LoadInitialICode(void);
void ScalerAudioD0LoadStableICodeEvent(void);
void ScalerAudioD0DigitalDetectProc(void);
bit ScalerAudioD0GetAudioDetected(void);
EnumAudioSamplingFreqType ScalerAudioD0SamplingFreqDetect(void);
void ScalerAudioD0WatchDogProc(bit bOn);
#endif

#if(_D1_DP_EXIST == _ON)
void ScalerAudioD1SetAudioPLL(void);
#endif
#endif

#if(_SLEEP_AUDIO_SUPPORT == _ON)
#if((_DP_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_DP)))
BYTE ScalerAudioGetDigitalAudioSource(BYTE ucInputPort);
#endif
#endif

#if(_LINE_IN_SUPPORT == _ON)
void ScalerAudioADCInitial(void);
#endif

#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
void ScalerAudioInternalAudioGenSwitch(bit bOn, BYTE ucInputPort);
bit ScalerAudioGetInternalAudioGenEnable(BYTE ucInputPort);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Initial HDMI/DP audio setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioDigitalAudioInitial(void)
{
#if(_D0_DP_EXIST == _ON)
    ScalerAudioD0DPAudioInitial();
#endif

#if(_D1_DP_EXIST == _ON)
    ScalerAudioD1DPAudioInitial();
#endif

#if((_D1_HDMI_SUPPORT == _ON) || (_D2_HDMI_SUPPORT == _ON))
    ScalerAudioD2HDMIAudioInitial();
#endif

#if(_D3_HDMI_SUPPORT == _ON)
    ScalerAudioD3HDMIAudioInitial();
#endif
}

//--------------------------------------------------
// Description  : Disable Auido PLL Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioDisableAudioPLL(void)
{
#if(_LINE_IN_SUPPORT == _ON)
    // Power Down ADC PLL
    ScalerSetBit(PBF_BD_MN_SCLKG_PLL_PWR, ~_BIT7, _BIT7);
#endif

#if(_D0_DP_EXIST == _ON)
    // Power Down D0 DPLL
    ScalerSetBit(PB6_D3_MN_SCLKG_PLL_PWR, ~_BIT7, _BIT7);
#endif

#if(_D1_DP_EXIST == _ON)
    // Power Down D1 DPLL
    ScalerSetBit(PB9_D3_MN_SCLKG_PLL_PWR, ~_BIT7, _BIT7);
#endif

#if((_D1_HDMI_SUPPORT == _ON) || (_D2_HDMI_SUPPORT == _ON))
    // Power Down D2 DPLL
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_38_PORT_PAGE71_HDMI_DPCR0, ~_BIT7, _BIT7);
#endif

#if(_D3_HDMI_SUPPORT == _ON)
    // Power Down D3 DPLL
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_38_PORT_PAGE72_HDMI_DPCR0, ~_BIT7, _BIT7);
#endif
}

//--------------------------------------------------
// Description  : Detect digital audio for HDMI/DP interface
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioDigitalDetect(void)
{
#if(_D0_DP_EXIST == _ON)
    ScalerAudioD0DigitalDetectProc();
#endif

#if((_D1_HDMI_SUPPORT == _ON) || (_D1_DP_EXIST == _ON))
    ScalerAudioD1DigitalDetectProc();
#endif

#if(_D2_HDMI_SUPPORT == _ON)
    ScalerAudioD2DigitalDetectProc();
#endif

#if(_D3_HDMI_SUPPORT == _ON)
    ScalerAudioD3DigitalDetectProc();
#endif
}

//--------------------------------------------------
// Description  : Get Audio Detected
// Input Value  : None
// Output Value : TRUE => Audio Detected
//--------------------------------------------------
bit ScalerAudioGetAudioDetected(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
        case _D0_INPUT_PORT:

#if((_D6_INPUT_PORT_TYPE != _D6_NO_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        case _D6_INPUT_PORT:
#endif

#if(_D0_DP_EXIST == _ON)
            return ScalerAudioD0GetAudioDetected();
#endif

        case _D1_INPUT_PORT:

#if((_D1_HDMI_SUPPORT == _ON) || (_D1_DP_EXIST == _ON))
            return ScalerAudioD1GetAudioDetected();
#endif

        case _D2_INPUT_PORT:

#if(_D2_HDMI_SUPPORT == _ON)
            return ScalerAudioD2GetAudioDetected();
#endif

        case _D3_INPUT_PORT:

#if(_D3_HDMI_SUPPORT == _ON)
            return ScalerAudioD3GetAudioDetected();
#endif

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Detect Audio Sampling Freq
// Input Value  : ucInputPort
// Output Value : Audio Sampling Freq
//--------------------------------------------------
EnumAudioSamplingFreqPacket ScalerAudioSamplingFreqDetect(BYTE ucInputPort)
{
    EnumAudioSamplingFreqType enumSamplingFreqType = _AUDIO_FREQ_NO_AUDIO;

    switch(ucInputPort)
    {
        case _D0_INPUT_PORT:

#if((_D6_INPUT_PORT_TYPE != _D6_NO_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        case _D6_INPUT_PORT:
#endif

#if(_D0_DP_EXIST == _ON)
            enumSamplingFreqType = ScalerAudioD0SamplingFreqDetect();
#endif
            break;

        case _D1_INPUT_PORT:

#if((_D1_HDMI_SUPPORT == _ON) || (_D1_DP_EXIST == _ON))
            enumSamplingFreqType = ScalerAudioD1SamplingFreqDetect();
#endif
            break;

        case _D2_INPUT_PORT:

#if(_D2_HDMI_SUPPORT == _ON)
            enumSamplingFreqType = ScalerAudioD2SamplingFreqDetect();
#endif
            break;

        case _D3_INPUT_PORT:

#if(_D3_HDMI_SUPPORT == _ON)
            enumSamplingFreqType = ScalerAudioD3SamplingFreqDetect();
#endif
            break;

        default:
            break;
    }

    switch(enumSamplingFreqType)
    {
        case _AUDIO_FREQ_32K:
            return _AUDIO_FREQ_PACKET_32K;

        case _AUDIO_FREQ_44_1K:
            return _AUDIO_FREQ_PACKET_44_1K;

        case _AUDIO_FREQ_48K:
            return _AUDIO_FREQ_PACKET_48K;

        case _AUDIO_FREQ_64K:
            return _AUDIO_FREQ_PACKET_64K;

        case _AUDIO_FREQ_88_2K:
            return _AUDIO_FREQ_PACKET_88_2K;

        case _AUDIO_FREQ_96K:
            return _AUDIO_FREQ_PACKET_96K;

        case _AUDIO_FREQ_128K:
            return _AUDIO_FREQ_PACKET_128K;

        case _AUDIO_FREQ_176_4K:
            return _AUDIO_FREQ_PACKET_176_4K;

        case _AUDIO_FREQ_192K:
            return _AUDIO_FREQ_PACKET_192K;

        default:
            break;
    }

    return _AUDIO_FREQ_PACKET_NO_AUDIO;
}

//--------------------------------------------------
// Description  : Check Audio whether Audio LPCM By Audio Data
// Input Value  : ucSourceType
// Output Value : _TRUE => LPCM
//--------------------------------------------------
bit ScalerAudioLPCMCheckData(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
        case _D0_INPUT_PORT:

#if((_D6_INPUT_PORT_TYPE != _D6_NO_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        case _D6_INPUT_PORT:
#endif

#if(_D0_DP_EXIST == _ON)
            pData[0] = ScalerGetByte(PB6_B0_DP_AUD_CTRL);

            if((((pData[0] & _BIT5) == 0x00) && ((pData[0] & _BIT4) == _BIT4)) ||
               (((pData[0] & _BIT5) == _BIT5) && ((pData[0] & _BIT4) == 0x00)))
            {
                return _TRUE;
            }
#endif
            break;

        case _D1_INPUT_PORT:

#if(_D1_HDMI_SUPPORT == _ON)
            if(ScalerGetBit(P71_CB_HDMI_SR, _BIT4) == 0x00)
            {
                return _TRUE;
            }
#elif(_D1_DP_EXIST == _ON)
            pData[0] = ScalerGetByte(PB9_B0_DP_AUD_CTRL);

            if((((pData[0] & _BIT5) == 0x00) && ((pData[0] & _BIT4) == _BIT4)) ||
               (((pData[0] & _BIT5) == _BIT5) && ((pData[0] & _BIT4) == 0x00)))
            {
                return _TRUE;
            }
#endif
            break;

        case _D2_INPUT_PORT:

#if(_D2_HDMI_SUPPORT == _ON)
            if(ScalerGetBit(P71_CB_HDMI_SR, _BIT4) == 0x00)
            {
                return _TRUE;
            }
#endif
            break;

        case _D3_INPUT_PORT:

#if(_D3_HDMI_SUPPORT == _ON)
            if(ScalerGetBit(P72_CB_HDMI_SR, _BIT4) == 0x00)
            {
                return _TRUE;
            }
#endif
            break;

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Switch Digital Audio Output Mute
// Input Value  : _ON => Mute On
// Output Value : None
//--------------------------------------------------
void ScalerAudioDigitalOutputMute(bit bMute)
{
    bMute = bMute;

    switch(ScalerAudioGetDigitalAudioPortMapping())
    {
        case _D0_INPUT_PORT:

#if((_D6_INPUT_PORT_TYPE != _D6_NO_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        case _D6_INPUT_PORT:
#endif

#if(_D0_DP_EXIST == _ON)
            ScalerAudioDPDigitalOutputProc(~bMute, _D0_INPUT_PORT);
#endif
            break;

        case _D1_INPUT_PORT:

#if(_D1_HDMI_SUPPORT == _ON)
            ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_30_PORT_PAGE71_HDMI_AVMCR, ~_BIT5, (BYTE)(~bMute) << 5);
#elif(_D1_DP_EXIST == _ON)
            ScalerAudioDPDigitalOutputProc(~bMute, _D1_INPUT_PORT);
#endif
            break;

        case _D2_INPUT_PORT:

#if(_D2_HDMI_SUPPORT == _ON)
            ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_30_PORT_PAGE71_HDMI_AVMCR, ~_BIT5, (BYTE)(~bMute) << 5);
#endif
            break;

        case _D3_INPUT_PORT:

#if(_D3_HDMI_SUPPORT == _ON)
            ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_30_PORT_PAGE72_HDMI_AVMCR, ~_BIT5, (BYTE)(~bMute) << 5);
#endif
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Audio Watch Dog Proc
// Input Value  : bOn
// Output Value : None
//--------------------------------------------------
void ScalerAudioWatchDogProc(bit bOn, BYTE ucInputPort)
{
    bOn = bOn;

#if(_LINE_IN_SUPPORT == _ON)
    if(ScalerAudioGetInputSource() == _DIGITAL_AUDIO)
#endif
    {
        switch(ucInputPort)
        {
            case _D0_INPUT_PORT:

#if((_D6_INPUT_PORT_TYPE != _D6_NO_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
            case _D6_INPUT_PORT:
#endif

#if(_D0_DP_EXIST == _ON)
                ScalerAudioD0WatchDogProc(bOn);
                DebugMessageAudio("Audio D0: WatchDog", bOn);
#endif
                break;

            case _D1_INPUT_PORT:

#if((_D1_HDMI_SUPPORT == _ON) || (_D1_DP_EXIST == _ON))
                ScalerAudioD1WatchDogProc(bOn);
                DebugMessageAudio("Audio D1: WatchDog", bOn);
#endif
                break;

            case _D2_INPUT_PORT:

#if(_D2_HDMI_SUPPORT == _ON)
                ScalerAudioD2WatchDogProc(bOn);
                DebugMessageAudio("Audio D2: WatchDog", bOn);
#endif
                break;

            case _D3_INPUT_PORT:

#if(_D3_HDMI_SUPPORT == _ON)
                ScalerAudioD3WatchDogProc(bOn);
                DebugMessageAudio("Audio D3: WatchDog", bOn);
#endif
                break;

            default:
                break;
        }
    }
}

//--------------------------------------------------
// Description  : Timer Event to Load Stable I Code
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioLoadStableICodeEvent(EnumScalerTimerEventID enumEventID)
{
    switch(enumEventID)
    {
#if(_D0_DP_EXIST == _ON)
        case _SCALER_TIMER_EVENT_AUDIO_D0_LOAD_STABLE_I_CODE:

            ScalerAudioD0LoadStableICodeEvent();
            break;
#endif

#if((_D1_HDMI_SUPPORT == _ON) || (_D1_DP_EXIST == _ON))
        case _SCALER_TIMER_EVENT_AUDIO_D1_LOAD_STABLE_I_CODE:

            ScalerAudioD1LoadStableICodeEvent();
            break;
#endif

#if(_D2_HDMI_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_AUDIO_D2_LOAD_STABLE_I_CODE:

            ScalerAudioD2LoadStableICodeEvent();
            break;
#endif

#if(_D3_HDMI_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_AUDIO_D3_LOAD_STABLE_I_CODE:

            ScalerAudioD3LoadStableICodeEvent();
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Switch audio Input (AIN / DAC)
// Input Value  : bAudioSource
// Output Value : None
//--------------------------------------------------
void ScalerAudioSourceInputSwitch(EnumAudioInputSource enumAudioSource, BYTE ucInputPort)
{
    if(enumAudioSource == _DIGITAL_AUDIO)
    {
        // Select DAC Mux to Digital input
        ScalerSetBit(P6_D1_DA_MUTE, ~_BIT3, 0x00);

#if(_LINE_IN_SUPPORT == _ON)
        // Power down Audio ADC PLL
        ScalerSetBit(PBF_BD_MN_SCLKG_PLL_PWR, ~_BIT7, _BIT7);

#if(_LINE_IN_AA_PATH_SUPPORT == _ON)
        // Set DAC Path
        ScalerSetByte(P6_E0_REG_MUX_ANA_OUT, 0x00);
#endif
#endif
        if(ucInputPort == _D0_INPUT_PORT)
        {
            ScalerAudioInputPortSwitch(_AUDIO_FROM_D0_PORT);
        }
        else if(ucInputPort == _D1_INPUT_PORT)
        {
#if(_D1_DP_EXIST == _ON)
            ScalerAudioInputPortSwitch(_AUDIO_FROM_D1_PORT);
#elif(_D1_HDMI_SUPPORT == _ON)
            ScalerAudioInputPortSwitch(_AUDIO_FROM_D2_PORT);
#endif
        }
        else if(ucInputPort == _D2_INPUT_PORT)
        {
            ScalerAudioInputPortSwitch(_AUDIO_FROM_D2_PORT);
        }
        else if(ucInputPort == _D3_INPUT_PORT)
        {
            ScalerAudioInputPortSwitch(_AUDIO_FROM_D3_PORT);
        }
#if((_D6_INPUT_PORT_TYPE != _D6_NO_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        else if(ucInputPort == _D6_INPUT_PORT)
        {
            ScalerAudioInputPortSwitch(_AUDIO_FROM_D0_PORT);
        }
#endif
        // Reset DVC Counter
        ScalerSetBit(P8_A0_DVC_EN, ~_BIT6, _BIT6);
        ScalerSetBit(P8_A0_DVC_EN, ~_BIT6, 0x00);

#if(_EMBEDDED_DAC_SUPPORT == _ON)
        // Set AOUT and HPOUT Gain After DAC Block
        ScalerAudioDACSetOutputGain(_AUDIO_DAC_OUTPUT_SPEAKER, _DIGITAL_DAC_AOUT_GAIN_DB);
        ScalerAudioDACSetOutputGain(_AUDIO_DAC_OUTPUT_HEADPHONE, _DIGITAL_DAC_HPOUT_GAIN_DB);
#endif

#if(_AUDIO_DVC_ADJUST_HARD_GAIN_SUPPORT == _ON)
        // Set Hard Gain for Digital Audio
        ScalerSetBit(P8_A9_DVC_GAIN_DONE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _DIGITAL_HARD_GAIN_VALUE);
#endif
    }
#if(_LINE_IN_SUPPORT == _ON)
    else if(enumAudioSource == _LINE_IN_AUDIO)
    {
        // Enable Audio ADC PLL
        ScalerAudioSetADCAudioPLL();

        // Select DAC Mux to ADC input
        ScalerSetBit(P6_D1_DA_MUTE, ~_BIT3, _BIT3);

        // Switch port to Audio ADC
        ScalerAudioInputPortSwitch(_AUDIO_FROM_ADC_PORT);

        // Reset DVC Counter
        ScalerSetBit(P8_A0_DVC_EN, ~_BIT6, _BIT6);
        ScalerSetBit(P8_A0_DVC_EN, ~_BIT6, 0x00);

#if(_EMBEDDED_DAC_SUPPORT == _ON)
        // Set AOUT and HPOUT Gain After DAC Block
        ScalerAudioDACSetOutputGain(_AUDIO_DAC_OUTPUT_SPEAKER, _LINE_IN_DAC_AOUT_GAIN_DB);
        ScalerAudioDACSetOutputGain(_AUDIO_DAC_OUTPUT_HEADPHONE, _LINE_IN_DAC_HPOUT_GAIN_DB);
#endif

#if(_LINE_IN_AA_PATH_SUPPORT == _ON)
        // Set A-A Path
        ScalerSetByte(P6_E0_REG_MUX_ANA_OUT, 0xAA);
#endif

#if(_AUDIO_DVC_ADJUST_HARD_GAIN_SUPPORT == _ON)
        // Set Hard Gain for Line in Audio
        ScalerSetBit(P8_A9_DVC_GAIN_DONE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _LINE_IN_HARD_GAIN_VALUE);
#endif
    }
#endif
}

//--------------------------------------------------
// Description  : Get Current Audio Port
// Input Value  : None
// Output Value : Input Port
//--------------------------------------------------
EnumSourceSearchPort ScalerAudioGetDigitalAudioPortMapping(void)
{
    switch(ScalerAudioGetDigitalAudioPort(_AUDIO_DAC_OUT))
    {
        case _AUDIO_FROM_D0_PORT:

#if((_D6_INPUT_PORT_TYPE != _D6_NO_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
            if(GET_D6_SWITCH_SELECT() == _D0_INPUT_PORT)
            {
                return _D0_INPUT_PORT;
            }
            else if(GET_D6_SWITCH_SELECT() == _D6_INPUT_PORT)
            {
                return _D6_INPUT_PORT;
            }
#endif
            return _D0_INPUT_PORT;

        case _AUDIO_FROM_D1_PORT:

            return _D1_INPUT_PORT;

        case _AUDIO_FROM_D2_PORT:

#if(_D1_HDMI_SUPPORT == _ON)
            if(CHECK_TMDS_DPHY_SWITCH(_D1_INPUT_PORT) == _TRUE)
            {
                return _D1_INPUT_PORT;
            }
            else
#endif
            {
                return _D2_INPUT_PORT;
            }

        case _AUDIO_FROM_D3_PORT:

            return _D3_INPUT_PORT;

        default:
            break;
    }

    return _NO_INPUT_PORT;
}

#if((_D1_HDMI_SUPPORT == _ON) || (_D1_DP_EXIST == _ON))
//--------------------------------------------------
// Description  : Load initial I Code
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioD1LoadInitialICode(void)
{
#if(_D1_HDMI_SUPPORT == _ON)
    // Set high byte of I code for boundary tracking for HDMI audio
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_24_PORT_PAGE71_HDMI_ICBPSR0, HIBYTE(_INITIAL_I_CODE));

    // Set low byte of I code for boundary tracking for HDMI audio
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_25_PORT_PAGE71_HDMI_ICBPSR1, LOBYTE(_INITIAL_I_CODE));
#elif(_D1_DP_EXIST == _ON)
    // Set high byte of I code for boundary tracking for DP audio
    ScalerSetByte(PB9_83_AUD_BDRY_2, HIBYTE(_INITIAL_I_CODE));

    // Set low byte of I code for boundary tracking for DP audio
    ScalerSetByte(PB9_84_AUD_BDRY_3, LOBYTE(_INITIAL_I_CODE));
#endif

    DebugMessageAudio("Load initial I code", _INITIAL_I_CODE);
}

//--------------------------------------------------
// Description  : Timer Event to Load Stable I Code
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioD1LoadStableICodeEvent(void)
{
#if(_D1_HDMI_SUPPORT == _ON)
    // Set high byte of I code for boundary tracking
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_24_PORT_PAGE71_HDMI_ICBPSR0, HIBYTE(_STABLE_I_CODE));

    // Set low byte of I code for boundary tracking
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_25_PORT_PAGE71_HDMI_ICBPSR1, LOBYTE(_STABLE_I_CODE));
#elif(_D1_DP_EXIST == _ON)
    // Set high byte of I code for boundary tracking for DP audio
    ScalerSetByte(PB9_83_AUD_BDRY_2, HIBYTE(_STABLE_I_CODE));

    // Set low byte of I code for boundary tracking for DP audio
    ScalerSetByte(PB9_84_AUD_BDRY_3, LOBYTE(_STABLE_I_CODE));
#endif

    DebugMessageAudio("Load stable I code", _STABLE_I_CODE);
}

//--------------------------------------------------
// Description  : Detect D1 digital audio for HDMI/DP interface
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioD1DigitalDetectProc(void)
{
#if(_D1_DP_EXIST == _ON)
    if(GET_DP_RX1_LINK_TRAINING_STATUS() != _DP_NORMAL_LINK_TRAINING_PASS)
    {
        CLR_AUDIO_D1_PACKET_DETECT();
        SET_D1_DIGITAL_AUDIO_SOURCE(_DIGITAL_AUDIO_SOURCE_NONE);

        if(GET_AUDIO_D1_ICODE_RELOADED() == _TRUE)
        {
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_AUDIO_D1_LOAD_STABLE_I_CODE);

            ScalerAudioD1LoadInitialICode();

            CLR_AUDIO_D1_ICODE_RELOADED();
        }

        return;
    }
#endif

    if(ScalerAudioD1SamplingFreqDetect() != 0x00)
    {
#if(_D1_HDMI_SUPPORT == _ON)

        SET_AUDIO_D1_PACKET_DETECT();
        SET_D1_DIGITAL_AUDIO_SOURCE(_DIGITAL_AUDIO_SOURCE_HDMI);

#elif(_D1_DP_EXIST == _ON)

        if(ScalerGetBit(PB9_01_DP_VBID, _BIT4) == 0x00)
        {
            SET_AUDIO_D1_PACKET_DETECT();
            SET_D1_DIGITAL_AUDIO_SOURCE(_DIGITAL_AUDIO_SOURCE_DP);

            // Set DP Receive Port1 In Sync
            ScalerDpRx1SinkStatusSet(_DP_SINK_REVEICE_PORT1, _DP_SINK_IN_SYNC);
        }
        else
        {
            CLR_AUDIO_D1_PACKET_DETECT();
            SET_D1_DIGITAL_AUDIO_SOURCE(_DIGITAL_AUDIO_SOURCE_NONE);

            // Set DP Receive Port1 In Sync
            ScalerDpRx1SinkStatusSet(_DP_SINK_REVEICE_PORT1, _DP_SINK_OUT_OF_SYNC);
        }
#endif

        if(GET_AUDIO_D1_ICODE_RELOADED() == _FALSE)
        {
            ScalerTimerReactiveTimerEvent(_AUDIO_DYNAMIC_I_CODE_TIMER_MS, _SCALER_TIMER_EVENT_AUDIO_D1_LOAD_STABLE_I_CODE);

            SET_AUDIO_D1_ICODE_RELOADED();
        }
    }
    else
    {
#if(_D1_DP_EXIST == _ON)
        if(GET_D1_DIGITAL_AUDIO_SOURCE() == _DIGITAL_AUDIO_SOURCE_DP)
        {
            // Set DP Receive Port1 Out Of Sync
            ScalerDpRx1SinkStatusSet(_DP_SINK_REVEICE_PORT1, _DP_SINK_OUT_OF_SYNC);
        }
#endif
        CLR_AUDIO_D1_PACKET_DETECT();
        SET_D1_DIGITAL_AUDIO_SOURCE(_DIGITAL_AUDIO_SOURCE_NONE);

        if(GET_AUDIO_D1_ICODE_RELOADED() == _TRUE)
        {
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_AUDIO_D1_LOAD_STABLE_I_CODE);

            ScalerAudioD1LoadInitialICode();

            CLR_AUDIO_D1_ICODE_RELOADED();
        }
    }

#if(_D1_DP_EXIST == _ON)
    // Check Audio Sampling Frequency Change
    if(ScalerGetBit(PB9_50_AUD_FREQUENY_DET_0, _BIT5) == _BIT5)
    {
        ScalerSetBit(PB9_50_AUD_FREQUENY_DET_0, ~_BIT5, _BIT5);

        // Audio DVC Setting
        ScalerAudioD1DPSetDVCMode(_DB_GAIN, ScalerAudioSamplingFreqDetect(_D1_INPUT_PORT));
    }
#endif
}

//--------------------------------------------------
// Description  : Get D1 Audio Detected
// Input Value  : None
// Output Value : TRUE => Audio Detected
//--------------------------------------------------
bit ScalerAudioD1GetAudioDetected(void)
{
    // Check audio packet
    if(GET_AUDIO_D1_PACKET_DETECT() == _FALSE)
    {
        DebugMessageAudio("False : D1 Audio Packet", 0);
        return _FALSE;
    }

#if(_D1_HDMI_SUPPORT == _ON)
    // Check AVMute
    if(ScalerGetBit(P71_CB_HDMI_SR, _BIT6) == _BIT6)
    {
        DebugMessageAudio("False : D1 AVMute", 0);
        return _FALSE;
    }

    // Check HDMI audio FIFO overflow and underflow
    if(ScalerGetBit(P71_CB_HDMI_SR, (_BIT2 | _BIT1)) != 0x00)
    {
        DebugMessageAudio("False : D1 HDMI Audio FIFO", ScalerGetBit(P71_CB_HDMI_SR, (_BIT2 | _BIT1)));

        if(ScalerGetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_31_PORT_PAGE71_HDMI_WDCR0, (_BIT2 | _BIT1)) == 0x00)
        {
            // Clear HDMI audio FIFO overflow and underflow status
            ScalerSetBit(P71_CB_HDMI_SR, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));

            if(ScalerGetBit(P71_CB_HDMI_SR, (_BIT2 | _BIT1)) != 0x00)
            {
                DebugMessageAudio("False : D1 HDMI Audio FSM Reset", ScalerGetBit(P71_CB_HDMI_SR, (_BIT2 | _BIT1)));

                // Set Double Buffer bit
                ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_10_PORT_PAGE71_HDMI_CMCR, ~_BIT4, _BIT4);

                // Clear HDMI audio FIFO overflow and underflow status
                ScalerSetBit(P71_CB_HDMI_SR, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));
            }
        }

        return _FALSE;
    }

#elif(_D1_DP_EXIST == _ON)
    if(ScalerGetBit(PB9_74_AUD_FSM_CTRL_0, _BIT7) == 0x00)
    {
        DebugMessageAudio("False : D1 DP Audio Fsm Disable", 0);

        return _FALSE;
    }

    // Check DP audio buffer overflow and underflow
    if(ScalerGetBit(PB9_70_AUD_BUFFER_CTRL_0, (_BIT1 | _BIT0)) != 0x00)
    {
        DebugMessageAudio("False : D1 DP Audio Buffer", ScalerGetBit(PB9_70_AUD_BUFFER_CTRL_0, (_BIT1 | _BIT0)));

        if(ScalerGetBit(PB9_39_DP_AWD_CTRL, (_BIT7 | _BIT6)) == 0x00)
        {
            // Clear audio FIFO overflow and underflow status
            ScalerSetBit(PB9_70_AUD_BUFFER_CTRL_0, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

            // Waiting for 2ms(Audio Freq. Detect || Audio FIFO Write (1/2 FIFO depth = 64 packet)) + 1ms(Audio Stable Time Count = 5 x 200us)
            ScalerTimerDelayXms(3);

            if(ScalerGetBit(PB9_70_AUD_BUFFER_CTRL_0, (_BIT1 | _BIT0)) != 0x00)
            {
                DebugMessageAudio("False : D1 DP Audio FSM Reset", ScalerGetBit(PB9_70_AUD_BUFFER_CTRL_0, (_BIT1 | _BIT0)));

                // Reset Audio FSM
                ScalerSetBit(PB9_74_AUD_FSM_CTRL_0, ~_BIT7, 0x00);

                // Clear audio FIFO overflow and underflow status
                ScalerSetBit(PB9_70_AUD_BUFFER_CTRL_0, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                // Enable Audio FSM
                ScalerSetBit(PB9_74_AUD_FSM_CTRL_0, ~_BIT7, _BIT7);

                // Waiting for 2ms(Audio Freq. Detect || Audio FIFO Write (1/2 FIFO depth = 64 packet)) + 1ms(Audio Stable Time Count = 5 x 200us)
                ScalerTimerDelayXms(3);
            }
        }

        return _FALSE;
    }
#endif

    return _TRUE;
}

//--------------------------------------------------
// Description  : Detect D1 Audio Sampling Freq
// Input Value  : None
// Output Value : Audio Sampling Freq
//--------------------------------------------------
EnumAudioSamplingFreqType ScalerAudioD1SamplingFreqDetect(void)
{
#if(_D1_HDMI_SUPPORT == _ON)
    if(CHECK_TMDS_DPHY_SWITCH(_D1_INPUT_PORT) != _TRUE)
    {
        return _AUDIO_FREQ_NO_AUDIO;
    }
#endif

#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
    if(ScalerAudioD1GetInternalAudioGenEnable() == _ENABLE)
    {
        // For Audio test pattern
        SET_AUDIO_D1_SAMPLING_FREQ(_AUDIO_FREQ_48K);
        return _AUDIO_FREQ_48K;
    }
#endif

    // Initial the value for checker
    pData[0] = 0;

#if(_D1_HDMI_SUPPORT == _ON)
    pData[0] = ScalerGetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_8B_PORT_PAGE71_AUDIO_FREQ_RESULT, (_BIT3 | _BIT2 | _BIT1 | _BIT0));
#elif(_D1_DP_EXIST == _ON)
    pData[0] = (ScalerGetBit(PB9_61_AUD_SAMPLE_CNT_0, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4);
#endif

#if(_EMBEDDED_DAC_SUPPORT == _ON)
    if(pData[0] != GET_AUDIO_D1_SAMPLING_FREQ())
    {
        if(pData[0] <= _AUDIO_FREQ_64K)
        {
            ScalerSetBit(P6_D4_DA_CLK_CTRL, ~(_BIT7 | _BIT6), 0x00);
        }
        else if(pData[0] <= _AUDIO_FREQ_128K)
        {
            ScalerSetBit(P6_D4_DA_CLK_CTRL, ~(_BIT7 | _BIT6), _BIT6);
        }
        else
        {
            ScalerSetBit(P6_D4_DA_CLK_CTRL, ~(_BIT7 | _BIT6), _BIT7);
        }
    }
#endif

    SET_AUDIO_D1_SAMPLING_FREQ(pData[0]);

    return pData[0];
}

//--------------------------------------------------
// Description  : D1 Audio Watch Dog Proc
// Input Value  : bOn
// Output Value : None
//--------------------------------------------------
void ScalerAudioD1WatchDogProc(bit bOn)
{
    if(bOn == _ON)
    {
#if(_D1_HDMI_SUPPORT == _ON)
        // Clear audio FIFO overflow and underflow status
        ScalerSetBit(P71_CB_HDMI_SR, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));

        // Enable Audio Watch Dog for FIFO Overflow/Underflow
        ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_31_PORT_PAGE71_HDMI_WDCR0, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));
#elif(_D1_DP_EXIST == _ON)
        // Clear audio buffer overflow and underflow status
        ScalerSetBit(PB9_70_AUD_BUFFER_CTRL_0, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

        // Enable Audio FSM
        ScalerSetBit(PB9_74_AUD_FSM_CTRL_0, ~_BIT7, _BIT7);

        // Enable Audio Watch Dog for Buffer Overflow/Underflow
        ScalerSetBit(PB9_39_DP_AWD_CTRL, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
#endif
    }
    else
    {
#if(_D1_HDMI_SUPPORT == _ON)
        // Disable Audio Watch Dog for FIFO Overflow/Underflow
        ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_31_PORT_PAGE71_HDMI_WDCR0, ~(_BIT2 | _BIT1), 0x00);

#elif(_D1_DP_EXIST == _ON)
        // Disable Audio Watch Dog for Buffer Overflow/Underflow
        ScalerSetBit(PB9_39_DP_AWD_CTRL, ~(_BIT7 | _BIT6), 0x00);

        if(ScalerGetBit(PB9_70_AUD_BUFFER_CTRL_0, (_BIT1 | _BIT0)) != 0x00)
        {
            DebugMessageAudio("WD : D1 DP Audio Over/Underflow", ScalerGetBit(PB9_70_AUD_BUFFER_CTRL_0, (_BIT1 | _BIT0)));

            // Reset Audio FSM
            ScalerSetBit(PB9_74_AUD_FSM_CTRL_0, ~_BIT7, 0x00);

            // Clear audio FIFO overflow and underflow status
            ScalerSetBit(PB9_70_AUD_BUFFER_CTRL_0, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

            // Enable Audio FSM
            ScalerSetBit(PB9_74_AUD_FSM_CTRL_0, ~_BIT7, _BIT7);

            // Waiting for 2ms(Audio Freq. Detect || Audio FIFO Write (1/2 FIFO depth = 64 packet)) + 1ms(Audio Stable Time Count = 5 x 200us)
            ScalerTimerDelayXms(3);
        }
#endif
    }
}

#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : D1 Auido Speaker Testing Process
// Input Value  : Enable or Disable
// Output Value : None
//--------------------------------------------------
void ScalerAudioD1InternalAudioGenSwitch(bit bOn)
{
    if(bOn == _ON)
    {
        DebugMessageAudio("D1 Audio Test On", ScalerGetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_03_PORT_PAGE71_HDMI_AFCR, _BIT4));

        // Disable audio FIFO and Enable audio internal generator
        ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_03_PORT_PAGE71_HDMI_AFCR, ~(_BIT6 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);

        // Disbale DPLL Freq. Tuning
        ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_3A_PORT_PAGE71_HDMI_DPCR2, ~_BIT1, 0x00);

        // Set S code
        ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_12_PORT_PAGE71_HDMI_SCAPR, _HDMI_SAMPLING_FREQ_48K_GROUP_S_CODE);

        // Set D code
        ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_13_PORT_PAGE71_HDMI_DCAPR0, HIBYTE(_HDMI_SAMPLING_FREQ_48K_GROUP_D_CODE));
        ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_14_PORT_PAGE71_HDMI_DCAPR1, LOBYTE(_HDMI_SAMPLING_FREQ_48K_GROUP_D_CODE));

        // Disable sample freq. detection and auto load S code / D code
        ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_8A_PORT_PAGE71_AUDIO_FREQDET, ~(_BIT7 | _BIT6), 0x00);

        // Enable double buffer
        ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_10_PORT_PAGE71_HDMI_CMCR, ~_BIT4, _BIT4);

        ScalerAudioDigitalOutputMute(_OFF);
    }
    else
    {
        DebugMessageAudio("D1 Aduio Test Off", ScalerGetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_03_PORT_PAGE71_HDMI_AFCR, _BIT4));

        ScalerAudioDigitalOutputMute(_ON);

        // Enable sample freq. detection and auto load S code
        ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_8A_PORT_PAGE71_AUDIO_FREQDET, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

        // Enable double buffer
        ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_10_PORT_PAGE71_HDMI_CMCR, ~_BIT4, _BIT4);

        // Enable DPLL Freq. Tuning
        ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_3A_PORT_PAGE71_HDMI_DPCR2, ~_BIT1, _BIT1);

        // Enable audio FIFO and Disable audio internal generator
        ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_03_PORT_PAGE71_HDMI_AFCR, ~(_BIT6 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT2 | _BIT1));
    }
}

//--------------------------------------------------
// Description  : Get Whether Internal Audio Pattern Gen is Enabled
// Input Value  : None
// Output Value : _ENABLE or _DISABLE
//--------------------------------------------------
bit ScalerAudioD1GetInternalAudioGenEnable(void)
{
    if(ScalerGetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_03_PORT_PAGE71_HDMI_AFCR, _BIT4) == _BIT4)
    {
        return _ENABLE;
    }
    else
    {
        return _DISABLE;
    }
}
#endif // End of #if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
#endif // End of #if((_D1_HDMI_SUPPORT == _ON) || (_D1_DP_EXIST == _ON))

#if(_HDMI_SUPPORT == _ON)
#if((_D1_HDMI_SUPPORT == _ON) || (_D2_HDMI_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Initial 2 HDMI audio setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioD2HDMIAudioInitial(void)
{
    ScalerAudioD2SetAudioPLL();

    // Disable sine wave generator
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_03_PORT_PAGE71_HDMI_AFCR, ~_BIT4, 0x00);

    // Disable AVMUTE function and enable Audio FIFO Tracking main control (I/P code)
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_31_PORT_PAGE71_HDMI_WDCR0, ~(_BIT7 | _BIT5), _BIT5);

    // Enable FIFO Boundary Tracking, Enable Trend Tracking
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_15_PORT_PAGE71_HDMI_PSCR, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT2));

    // Enable SDM
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_2D_PORT_PAGE71_HDMI_AAPNR, ~_BIT1, _BIT1);

    // Set auto gain delay mode and final gain = full gain
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_07_PORT_PAGE71_HDMI_MAG_M_FINAL, ~_BIT3, 0x00);

    // Set wait time for load parameter
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_0A_PORT_PAGE71_AUDIO_LD_P_TIME_M, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_0B_PORT_PAGE71_AUDIO_LD_P_TIME_N, 0x10);

    // Set ZCD timeout
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_0D_PORT_PAGE71_ZCD_TIMEOUT, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _ZCD_TIMEOUT_DEFAULT);

    // Set Boundary Address = 5 for Boundary Tracking
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_1B_PORT_PAGE71_HDMI_FBR, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));

    // Set I code of trend
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_20_PORT_PAGE71_HDMI_ICTPSR0, 0x00);
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_21_PORT_PAGE71_HDMI_ICTPSR1, 0x02);

    // Set P code of trend
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_22_PORT_PAGE71_HDMI_PCTPSR0, 0x7F);
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_23_PORT_PAGE71_HDMI_PCTPSR1, 0xFF);

    // Set I code of boundary
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_24_PORT_PAGE71_HDMI_ICBPSR0, HIBYTE(_INITIAL_I_CODE));
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_25_PORT_PAGE71_HDMI_ICBPSR1, LOBYTE(_INITIAL_I_CODE));

    // Set P code of boundary
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_26_PORT_PAGE71_HDMI_PCBPSR0, 0x7F);
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_27_PORT_PAGE71_HDMI_PCBPSR1, 0xFF);

    // Audio Normal Output
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_30_PORT_PAGE71_HDMI_AVMCR, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));

    // Disable Audio Watchdog for FIFO Overflow/Underflow
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_31_PORT_PAGE71_HDMI_WDCR0, ~(_BIT2 | _BIT1), 0x00);

    // Set X Value
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_32_PORT_PAGE71_HDMI_WDCR1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Set Y Value
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_33_PORT_PAGE71_HDMI_WDCR2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Bit2: When no audio or changing sampling rate, AFSM load double buffer one more.
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_9F_PORT_PAGE71_PRESET_AFSM_MOD, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2));

    // Seperate the detected sampling frequency
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_8B_PORT_PAGE71_AUDIO_FREQ_RESULT, ~(_BIT6 | _BIT5 | _BIT4), 0x00);

    // Set 2ms for auto frequency detecttion
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_8C_PORT_PAGE71_AUDIO_FREQ_RESULT_M, ~(_BIT6 | _BIT5), _BIT5);

    // Change audio clk divider according to SYSCLK = 27MHz
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_8E_PORT_PAGE71_XTAL_DIV, _AUTO_FREQ_DETECT_XTAL_DIV);

    // Set threshold to sepeerate sampling frequency
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_90_PORT_PAGE71_TH1, 0x00);
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_91_PORT_PAGE71_TH2, 0x28);
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_92_PORT_PAGE71_TH3, 0x4C);
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_93_PORT_PAGE71_TH4, 0x5C);
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_94_PORT_PAGE71_TH5, 0x70);

#if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _ON)

    // Disable Auto Load S Code
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_8A_PORT_PAGE71_AUDIO_FREQDET, ~_BIT6, 0x00);

#if(_FIX_SAMPLING_FREQ_TYPE == _FIX_FREQ_32KHZ)

    // Set S code for 32kHz
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_12_PORT_PAGE71_HDMI_SCAPR, _HDMI_SAMPLING_FREQ_32K_GROUP_S_CODE);

    // Set D code for 32kHz
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_13_PORT_PAGE71_HDMI_DCAPR0, HIBYTE(_HDMI_SAMPLING_FREQ_32K_GROUP_D_CODE));
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_14_PORT_PAGE71_HDMI_DCAPR1, LOBYTE(_HDMI_SAMPLING_FREQ_32K_GROUP_D_CODE));

#elif(_FIX_SAMPLING_FREQ_TYPE == _FIX_FREQ_44_1KHZ)

    // Set S code for 44.1kHz
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_12_PORT_PAGE71_HDMI_SCAPR, _HDMI_SAMPLING_FREQ_44K_GROUP_S_CODE);

    // Set D code for 44.1kHz
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_13_PORT_PAGE71_HDMI_DCAPR0, HIBYTE(_HDMI_SAMPLING_FREQ_44K_GROUP_D_CODE));
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_14_PORT_PAGE71_HDMI_DCAPR1, LOBYTE(_HDMI_SAMPLING_FREQ_44K_GROUP_D_CODE));

#else // _FIX_SAMPLING_FREQ_TYPE == _FIX_FREQ_48KHZ

    // Set S code for 48kHz
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_12_PORT_PAGE71_HDMI_SCAPR, _HDMI_SAMPLING_FREQ_48K_GROUP_S_CODE);

    // Set D code for 48kHz
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_13_PORT_PAGE71_HDMI_DCAPR0, HIBYTE(_HDMI_SAMPLING_FREQ_48K_GROUP_D_CODE));
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_14_PORT_PAGE71_HDMI_DCAPR1, LOBYTE(_HDMI_SAMPLING_FREQ_48K_GROUP_D_CODE));

#endif

    // Set Double Buffer bit
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_10_PORT_PAGE71_HDMI_CMCR, ~_BIT4, _BIT4);

    // Load D code
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_31_PORT_PAGE71_HDMI_WDCR0, ~_BIT6, _BIT6);
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_31_PORT_PAGE71_HDMI_WDCR0, ~_BIT6, 0x00);

#else

    // Set S code for auto load mode
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_95_PORT_PAGE71_PRESET_S_CODE0, _HDMI_SAMPLING_FREQ_32K_GROUP_S_CODE);
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_96_PORT_PAGE71_PRESET_S_CODE1, _HDMI_SAMPLING_FREQ_44K_GROUP_S_CODE);
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_97_PORT_PAGE71_PRESET_S_CODE2, _HDMI_SAMPLING_FREQ_48K_GROUP_S_CODE);

    // Set D code for auto load mode
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_99_PORT_PAGE71_PRESET_D_CODE_0, HIBYTE(_HDMI_SAMPLING_FREQ_32K_GROUP_D_CODE));
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_9A_PORT_PAGE71_PRESET_D_CODE_1, LOBYTE(_HDMI_SAMPLING_FREQ_32K_GROUP_D_CODE));
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_9B_PORT_PAGE71_PRESET_D_CODE_2, HIBYTE(_HDMI_SAMPLING_FREQ_44K_GROUP_D_CODE));
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_9C_PORT_PAGE71_PRESET_D_CODE_3, LOBYTE(_HDMI_SAMPLING_FREQ_44K_GROUP_D_CODE));
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_9D_PORT_PAGE71_PRESET_D_CODE_4, HIBYTE(_HDMI_SAMPLING_FREQ_48K_GROUP_D_CODE));
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_9E_PORT_PAGE71_PRESET_D_CODE_5, LOBYTE(_HDMI_SAMPLING_FREQ_48K_GROUP_D_CODE));

    // Enable Auto Load S Code
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_8A_PORT_PAGE71_AUDIO_FREQDET, ~_BIT6, _BIT6);

    // Set The Manual S code = 1
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_12_PORT_PAGE71_HDMI_SCAPR, 0x81);

    // Set Double Buffer bit
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_10_PORT_PAGE71_HDMI_CMCR, ~_BIT4, _BIT4);

#endif // End of #if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _ON)

    // Enable Audio Freq Detect
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_8A_PORT_PAGE71_AUDIO_FREQDET, ~_BIT7, _BIT7);

    // Enable SPDIF/I2S Output
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_62_PORT_PAGE71_HDMI_AOCR, 0xFF);

#if(_D1_HDMI_SUPPORT == _ON)
    CLR_AUDIO_D1_ICODE_RELOADED();
#endif

#if(_D2_HDMI_SUPPORT == _ON)
    CLR_AUDIO_D2_ICODE_RELOADED();
#endif
}

//--------------------------------------------------
// Description  : Initial 2 Auido PLL Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioD2SetAudioPLL(void)
{
    // DPLL power down
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_38_PORT_PAGE71_HDMI_DPCR0, ~_BIT7, _BIT7);

    // Set M code
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_11_PORT_PAGE71_HDMI_MCAPR, (_AUDIO_PLL_M - 2));

    // Set O code
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_38_PORT_PAGE71_HDMI_DPCR0, ~(_BIT5 | _BIT4), 0x00);

    // Set K code and enable double buffer
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_10_PORT_PAGE71_HDMI_CMCR, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | ((_AUDIO_PLL_K - 2) & 0x0F)));

    // Initial VCO Band = 10
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_3A_PORT_PAGE71_HDMI_DPCR2, ~(_BIT4 | _BIT3), _BIT4);

    // Set MN PLL Path1 => [2]: 1 = Path1, 0 = Path2
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_3A_PORT_PAGE71_HDMI_DPCR2, ~(_BIT7 | _BIT2), _BIT2);

    // DPLL VCORSTB Set to Normal
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_3B_PORT_PAGE71_HDMI_DPCR3, ~_BIT0, _DPLL_VCORSTB_NORMAL_VALUE);

    // DPLL power up
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_38_PORT_PAGE71_HDMI_DPCR0, ~_BIT7, 0x00);

    // Delay 2000us
    ScalerTimerDelayXms(2);

    // DPLL CMP enable
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_38_PORT_PAGE71_HDMI_DPCR0, ~_BIT0, _BIT0);

    // Delay 1000us
    ScalerTimerDelayXms(2);

    // DPLL latch calibration enable
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_38_PORT_PAGE71_HDMI_DPCR0, ~_BIT1, _BIT1);

    // Delay 1000us
    ScalerTimerDelayXms(2);

    // DPLL calibration validated
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_38_PORT_PAGE71_HDMI_DPCR0, ~_BIT2, _BIT2);
}
#endif // End of #if((_D1_HDMI_SUPPORT == _ON) || (_D2_HDMI_SUPPORT == _ON))

#if(_D2_HDMI_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Detect D2 Audio Sampling Freq
// Input Value  : None
// Output Value : Audio Sampling Freq
//--------------------------------------------------
EnumAudioSamplingFreqType ScalerAudioD2SamplingFreqDetect(void)
{
#if(_D1_HDMI_SUPPORT == _ON)
    if(CHECK_TMDS_DPHY_SWITCH(_D2_INPUT_PORT) != _TRUE)
    {
        return _AUDIO_FREQ_NO_AUDIO;
    }
#endif

#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
    if(ScalerAudioD2GetInternalAudioGenEnable() == _ENABLE)
    {
        // For Audio test pattern
        SET_AUDIO_D2_SAMPLING_FREQ(_AUDIO_FREQ_48K);
        return _AUDIO_FREQ_48K;
    }
#endif

    pData[0] = ScalerGetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_8B_PORT_PAGE71_AUDIO_FREQ_RESULT, (_BIT3 | _BIT2 | _BIT1 | _BIT0));

#if(_EMBEDDED_DAC_SUPPORT == _ON)
    if(pData[0] != GET_AUDIO_D2_SAMPLING_FREQ())
    {
        if(pData[0] <= _AUDIO_FREQ_64K)
        {
            ScalerSetBit(P6_D4_DA_CLK_CTRL, ~(_BIT7 | _BIT6), 0x00);
        }
        else if(pData[0] <= _AUDIO_FREQ_128K)
        {
            ScalerSetBit(P6_D4_DA_CLK_CTRL, ~(_BIT7 | _BIT6), _BIT6);
        }
        else
        {
            ScalerSetBit(P6_D4_DA_CLK_CTRL, ~(_BIT7 | _BIT6), _BIT7);
        }
    }
#endif

    SET_AUDIO_D2_SAMPLING_FREQ(pData[0]);

    return pData[0];
}

#endif // End of #if(_D2_HDMI_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Check Audio whether Audio LPCM By Info Frame
// Input Value  : ucSourceType
// Output Value : _TRUE => LPCM
//--------------------------------------------------
bit ScalerAudioLPCMCheckInfo(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
        case _D0_INPUT_PORT:

            break;

        case _D1_INPUT_PORT:

#if(_D1_HDMI_SUPPORT == _ON)
            ScalerGetDataPortByte(P71_CD_HDMI_PSAP, 0x15, 1, pData, _NON_AUTOINC);

            if(((pData[0] & 0xF0) == 0x00) || ((pData[0] & 0xF0) == 0x10))
            {
                return _TRUE;
            }
#endif
            break;

        case _D2_INPUT_PORT:

#if(_D2_HDMI_SUPPORT == _ON)
            ScalerGetDataPortByte(P71_CD_HDMI_PSAP, 0x15, 1, pData, _NON_AUTOINC);

            if(((pData[0] & 0xF0) == 0x00) || ((pData[0] & 0xF0) == 0x10))
            {
                return _TRUE;
            }
#endif
            break;

        case _D3_INPUT_PORT:

#if(_D3_HDMI_SUPPORT == _ON)
            ScalerGetDataPortByte(P72_CD_HDMI_PSAP, 0x15, 1, pData, _NON_AUTOINC);

            if(((pData[0] & 0xF0) == 0x00) || ((pData[0] & 0xF0) == 0x10))
            {
                return _TRUE;
            }
#endif
            break;

        default:
            break;
    }

    return _FALSE;
}
#endif

#if(_DP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Audio Digital Output Process
// Input Value  : Enable and Input port
// Output Value : None
//--------------------------------------------------
void ScalerAudioDPDigitalOutputProc(bit bEnable, BYTE ucInputPort)
{
#if(_LINE_IN_SUPPORT == _ON)
    if(ScalerAudioGetInputSource() == _DIGITAL_AUDIO)
#endif
    {
        switch(ucInputPort)
        {
            case _D0_INPUT_PORT:

#if((_D6_INPUT_PORT_TYPE != _D6_NO_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
            case _D6_INPUT_PORT:
#endif

#if(_D0_DP_EXIST == _ON)
                ScalerAudioD0DPDigitalOutputProc(bEnable);
#endif
                break;

            case _D1_INPUT_PORT:

#if(_D1_DP_EXIST == _ON)
                ScalerAudioD1DPDigitalOutputProc(bEnable);
#endif
                break;

            default:
                break;
        }
    }
}

#if(_D0_DP_EXIST == _ON)
//--------------------------------------------------
// Description  : Initial D0 Auido PLL Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioD0SetAudioPLL(void)
{
    // DPLL power down
    ScalerSetBit(PB6_D3_MN_SCLKG_PLL_PWR, ~_BIT7, _BIT7);

    // Set M code
    ScalerSetByte(PB6_D1_MN_SCLKG_DIVM, (_AUDIO_PLL_M - 2));

    // Set O code
    ScalerSetBit(PB6_D3_MN_SCLKG_PLL_PWR, ~(_BIT1 | _BIT0), 0x00);

    // Set N(K) code and enable double buffer
    ScalerSetByte(PB6_D2_MN_SCLKG_DIVN, (_AUDIO_PLL_K - 2));

    // Initial VCO Band = 10
    ScalerSetBit(PB6_D5_MN_SCLKG_PLL_WD, ~(_BIT4 | _BIT3), _BIT4);

    // Set MN PLL Path1 => [2]: 1 = Path1, 0 = Path2
    ScalerSetBit(PB6_D5_MN_SCLKG_PLL_WD, ~(_BIT7 | _BIT2), _BIT2);

    // DPLL VCORSTB Set to Normal
    ScalerSetBit(PB6_D6_MN_SCLKG_PLL_INSEL, ~_BIT0, _DPLL_VCORSTB_NORMAL_VALUE);

    // DPLL power up
    ScalerSetBit(PB6_D3_MN_SCLKG_PLL_PWR, ~_BIT7, 0x00);

    // Delay 2000us
    ScalerTimerDelayXms(2);

    // DPLL CMP enable
    ScalerSetBit(PB6_D3_MN_SCLKG_PLL_PWR, ~_BIT2, _BIT2);

    // Delay at least 1000us
    ScalerTimerDelayXms(2);

    // DPLL latch calibration enable
    ScalerSetBit(PB6_D3_MN_SCLKG_PLL_PWR, ~_BIT3, _BIT3);

    // Delay at least 1000us
    ScalerTimerDelayXms(2);

    // DPLL calibration validated
    ScalerSetBit(PB6_D3_MN_SCLKG_PLL_PWR, ~_BIT4, _BIT4);
}

//--------------------------------------------------
// Description  : Load initial I Code
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioD0LoadInitialICode(void)
{
    // Set high byte of I code for boundary tracking for DP audio
    ScalerSetByte(PB6_83_AUD_BDRY_2, HIBYTE(_INITIAL_I_CODE));

    // Set low byte of I code for boundary tracking for DP audio
    ScalerSetByte(PB6_84_AUD_BDRY_3, LOBYTE(_INITIAL_I_CODE));

    DebugMessageAudio("Load initial I code", _INITIAL_I_CODE);
}

//--------------------------------------------------
// Description  : Timer Event to Load Stable I Code
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioD0LoadStableICodeEvent(void)
{
    // Set high byte of I code for boundary tracking for DP audio
    ScalerSetByte(PB6_83_AUD_BDRY_2, HIBYTE(_STABLE_I_CODE));

    // Set low byte of I code for boundary tracking for DP audio
    ScalerSetByte(PB6_84_AUD_BDRY_3, LOBYTE(_STABLE_I_CODE));

    DebugMessageAudio("Load stable I code", _STABLE_I_CODE);
}

//--------------------------------------------------
// Description  : Detect D0 digital audio for HDMI/DP interface
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioD0DigitalDetectProc(void)
{
    if(GET_DP_RX0_LINK_TRAINING_STATUS() != _DP_NORMAL_LINK_TRAINING_PASS)
    {
        CLR_AUDIO_D0_PACKET_DETECT();
        SET_D0_DIGITAL_AUDIO_SOURCE(_DIGITAL_AUDIO_SOURCE_NONE);

        if(GET_AUDIO_D0_ICODE_RELOADED() == _TRUE)
        {
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_AUDIO_D0_LOAD_STABLE_I_CODE);

            ScalerAudioD0LoadInitialICode();

            CLR_AUDIO_D0_ICODE_RELOADED();
        }

        return;
    }

    if(ScalerAudioD0SamplingFreqDetect() != 0x00)
    {
        if(ScalerGetBit(PB6_01_DP_VBID, _BIT4) == 0x00)
        {
            SET_AUDIO_D0_PACKET_DETECT();
            SET_D0_DIGITAL_AUDIO_SOURCE(_DIGITAL_AUDIO_SOURCE_DP);

            // Set DP Receive Port1 In Sync
            ScalerDpRx0SinkStatusSet(_DP_SINK_REVEICE_PORT1, _DP_SINK_IN_SYNC);
        }
        else
        {
            CLR_AUDIO_D0_PACKET_DETECT();
            SET_D0_DIGITAL_AUDIO_SOURCE(_DIGITAL_AUDIO_SOURCE_NONE);

            // Set DP Receive Port1 Out Of Sync
            ScalerDpRx0SinkStatusSet(_DP_SINK_REVEICE_PORT1, _DP_SINK_OUT_OF_SYNC);
        }

        if(GET_AUDIO_D0_ICODE_RELOADED() == _FALSE)
        {
            ScalerTimerReactiveTimerEvent(_AUDIO_DYNAMIC_I_CODE_TIMER_MS, _SCALER_TIMER_EVENT_AUDIO_D0_LOAD_STABLE_I_CODE);

            SET_AUDIO_D0_ICODE_RELOADED();
        }
    }
    else
    {
        if(GET_D0_DIGITAL_AUDIO_SOURCE() == _DIGITAL_AUDIO_SOURCE_DP)
        {
            // Set DP Receive Port1 Out Of Sync
            ScalerDpRx0SinkStatusSet(_DP_SINK_REVEICE_PORT1, _DP_SINK_OUT_OF_SYNC);
        }

        CLR_AUDIO_D0_PACKET_DETECT();
        SET_D0_DIGITAL_AUDIO_SOURCE(_DIGITAL_AUDIO_SOURCE_NONE);

        if(GET_AUDIO_D0_ICODE_RELOADED() == _TRUE)
        {
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_AUDIO_D0_LOAD_STABLE_I_CODE);

            ScalerAudioD0LoadInitialICode();

            CLR_AUDIO_D0_ICODE_RELOADED();
        }
    }

    // Check Audio Sampling Frequency Change
    if(ScalerGetBit(PB6_50_AUD_FREQUENY_DET_0, _BIT5) == _BIT5)
    {
        ScalerSetBit(PB6_50_AUD_FREQUENY_DET_0, ~_BIT5, _BIT5);

        // Audio DVC Setting
        ScalerAudioD0DPSetDVCMode(_DB_GAIN, ScalerAudioSamplingFreqDetect(_D0_INPUT_PORT));
    }
}

//--------------------------------------------------
// Description  : Get D0 Audio Detected
// Input Value  : None
// Output Value : TRUE => Audio Detected
//--------------------------------------------------
bit ScalerAudioD0GetAudioDetected(void)
{
    // Check audio packet
    if(GET_AUDIO_D0_PACKET_DETECT() == _FALSE)
    {
        DebugMessageAudio("False : D0 Audio Packet", 0);
        return _FALSE;
    }

    if(ScalerGetBit(PB6_74_AUD_FSM_CTRL_0, _BIT7) == 0x00)
    {
        DebugMessageAudio("False : D0 DP Audio Fsm Disable", 0);

        return _FALSE;
    }

    // Check DP audio buffer overflow and underflow
    if(ScalerGetBit(PB6_70_AUD_BUFFER_CTRL_0, (_BIT1 | _BIT0)) != 0x00)
    {
        DebugMessageAudio("False : D0 DP Audio Buffer", ScalerGetBit(PB6_70_AUD_BUFFER_CTRL_0, (_BIT1 | _BIT0)));

        if(ScalerGetBit(PB6_39_DP_AWD_CTRL, (_BIT7 | _BIT6)) == 0x00)
        {
            // Clear audio FIFO overflow and underflow status
            ScalerSetBit(PB6_70_AUD_BUFFER_CTRL_0, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

            // Waiting for 2ms(Audio Freq. Detect || Audio FIFO Write (1/2 FIFO depth = 64 packet)) + 1ms(Audio Stable Time Count = 5 x 200us)
            ScalerTimerDelayXms(3);

            if(ScalerGetBit(PB6_70_AUD_BUFFER_CTRL_0, (_BIT1 | _BIT0)) != 0x00)
            {
                DebugMessageAudio("False : D0 DP Audio FSM Reset", ScalerGetBit(PB6_70_AUD_BUFFER_CTRL_0, (_BIT1 | _BIT0)));

                // Reset Audio FSM
                ScalerSetBit(PB6_74_AUD_FSM_CTRL_0, ~_BIT7, 0x00);

                // Clear audio FIFO overflow and underflow status
                ScalerSetBit(PB6_70_AUD_BUFFER_CTRL_0, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                // Enable Audio FSM
                ScalerSetBit(PB6_74_AUD_FSM_CTRL_0, ~_BIT7, _BIT7);

                // Waiting for 2ms(Audio Freq. Detect || Audio FIFO Write (1/2 FIFO depth = 64 packet)) + 1ms(Audio Stable Time Count = 5 x 200us)
                ScalerTimerDelayXms(3);
            }
        }

        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Detect D0 Audio Sampling Freq
// Input Value  : None
// Output Value : Audio Sampling Freq
//--------------------------------------------------
EnumAudioSamplingFreqType ScalerAudioD0SamplingFreqDetect(void)
{
#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
    if(ScalerAudioD0GetInternalAudioGenEnable() == _ENABLE)
    {
        // For Audio test pattern
        SET_AUDIO_D0_SAMPLING_FREQ(_AUDIO_FREQ_48K);
        return _AUDIO_FREQ_48K;
    }
#endif

    pData[0] = (ScalerGetBit(PB6_61_AUD_SAMPLE_CNT_0, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4);

#if(_EMBEDDED_DAC_SUPPORT == _ON)
    if(pData[0] != GET_AUDIO_D0_SAMPLING_FREQ())
    {
        if(pData[0] <= _AUDIO_FREQ_64K)
        {
            ScalerSetBit(P6_D4_DA_CLK_CTRL, ~(_BIT7 | _BIT6), 0x00);
        }
        else if(pData[0] <= _AUDIO_FREQ_128K)
        {
            ScalerSetBit(P6_D4_DA_CLK_CTRL, ~(_BIT7 | _BIT6), _BIT6);
        }
        else
        {
            ScalerSetBit(P6_D4_DA_CLK_CTRL, ~(_BIT7 | _BIT6), _BIT7);
        }
    }
#endif

    SET_AUDIO_D0_SAMPLING_FREQ(pData[0]);

    return pData[0];
}

//--------------------------------------------------
// Description  : D0 Audio Watch Dog Proc
// Input Value  : bOn
// Output Value : None
//--------------------------------------------------
void ScalerAudioD0WatchDogProc(bit bOn)
{
    if(bOn == _ON)
    {
        // Clear audio buffer overflow and underflow status
        ScalerSetBit(PB6_70_AUD_BUFFER_CTRL_0, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

        // Enable Audio Watch Dog for Buffer Overflow/Underflow
        ScalerSetBit(PB6_39_DP_AWD_CTRL, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    }
    else
    {
        // Disable Audio Watch Dog for Buffer Overflow/Underflow
        ScalerSetBit(PB6_39_DP_AWD_CTRL, ~(_BIT7 | _BIT6), 0x00);

        if(ScalerGetBit(PB6_70_AUD_BUFFER_CTRL_0, (_BIT1 | _BIT0)) != 0x00)
        {
            DebugMessageAudio("WD : D0 DP Audio Over/Underflow", ScalerGetBit(PB6_70_AUD_BUFFER_CTRL_0, (_BIT1 | _BIT0)));

            // Reset Audio FSM
            ScalerSetBit(PB6_74_AUD_FSM_CTRL_0, ~_BIT7, 0x00);

            // Clear audio FIFO overflow and underflow status
            ScalerSetBit(PB6_70_AUD_BUFFER_CTRL_0, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

            // Enable Audio FSM
            ScalerSetBit(PB6_74_AUD_FSM_CTRL_0, ~_BIT7, _BIT7);

            // Waiting for 2ms(Audio Freq. Detect || Audio FIFO Write (1/2 FIFO depth = 64 packet)) + 1ms(Audio Stable Time Count = 5 x 200us)
            ScalerTimerDelayXms(3);
        }
    }
}
#endif // End Of #if(_D0_DP_EXIST == _ON)

#if(_D1_DP_EXIST == _ON)
//--------------------------------------------------
// Description  : Initial D1 Auido PLL Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioD1SetAudioPLL(void)
{
    // DPLL power down
    ScalerSetBit(PB9_D3_MN_SCLKG_PLL_PWR, ~_BIT7, _BIT7);

    // Set M code
    ScalerSetByte(PB9_D1_MN_SCLKG_DIVM, (_AUDIO_PLL_M - 2));

    // Set O code
    ScalerSetBit(PB9_D3_MN_SCLKG_PLL_PWR, ~(_BIT1 | _BIT0), 0x00);

    // Set N(K) code and enable double buffer
    ScalerSetByte(PB9_D2_MN_SCLKG_DIVN, (_AUDIO_PLL_K - 2));

    // Initial VCO Band = 10
    ScalerSetBit(PB9_D5_MN_SCLKG_PLL_WD, ~(_BIT4 | _BIT3), _BIT4);

    // Set MN PLL Path1 => [2]: 1 = Path1, 0 = Path2
    ScalerSetBit(PB9_D5_MN_SCLKG_PLL_WD, ~(_BIT7 | _BIT2), _BIT2);

    // DPLL VCORSTB Set to Normal
    ScalerSetBit(PB9_D6_MN_SCLKG_PLL_INSEL, ~_BIT0, _DPLL_VCORSTB_NORMAL_VALUE);

    // DPLL power up
    ScalerSetBit(PB9_D3_MN_SCLKG_PLL_PWR, ~_BIT7, 0x00);

    // Delay 2000us
    ScalerTimerDelayXms(2);

    // DPLL CMP enable
    ScalerSetBit(PB9_D3_MN_SCLKG_PLL_PWR, ~_BIT2, _BIT2);

    // Delay 1000us
    ScalerTimerDelayXms(2);

    // DPLL latch calibration enable
    ScalerSetBit(PB9_D3_MN_SCLKG_PLL_PWR, ~_BIT3, _BIT3);

    // Delay 1000us
    ScalerTimerDelayXms(2);

    // DPLL calibration validated
    ScalerSetBit(PB9_D3_MN_SCLKG_PLL_PWR, ~_BIT4, _BIT4);
}
#endif
#endif

#if(_SLEEP_AUDIO_SUPPORT == _ON)
#if((_DP_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_DP)))
//--------------------------------------------------
// Description  : Get Current Digital Audio Source
// Input Value  : None
// Output Value : Digital Audio Source
//--------------------------------------------------
BYTE ScalerAudioGetDigitalAudioSource(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
        case _D0_INPUT_PORT:

#if((_D6_INPUT_PORT_TYPE != _D6_NO_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        case _D6_INPUT_PORT:
#endif

#if(_D0_DP_EXIST == _ON)
            return GET_D0_DIGITAL_AUDIO_SOURCE();
#endif

        case _D1_INPUT_PORT:

#if((_D1_HDMI_SUPPORT == _ON) || (_D1_DP_EXIST == _ON))
            return GET_D1_DIGITAL_AUDIO_SOURCE();
#endif

        case _D2_INPUT_PORT:

#if(_D2_HDMI_SUPPORT == _ON)
            return GET_D2_DIGITAL_AUDIO_SOURCE();
#endif

        case _D3_INPUT_PORT:

#if(_D3_HDMI_SUPPORT == _ON)
            return GET_D3_DIGITAL_AUDIO_SOURCE();
#endif

        default:
            break;
    }

    return _DIGITAL_AUDIO_SOURCE_NONE;
}
#endif
#endif // End of #if(_SLEEP_AUDIO_SUPPORT == _ON)

#if(_LINE_IN_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Initial Audio ADC
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioADCInitial(void)
{
    // Enable ADDA Loop, High Pass Filter and Set ADC ZCD Type
    ScalerSetBit(P6_B4_AD_CTRL, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), (_BIT6 | _BIT3));

    // Power On ADC
    ScalerSetBit(P6_B0_REG_ADC_POWER, ~_BIT7, _BIT7);

    // Power On Input Buffer and Mbias
    ScalerSetBit(P6_C0_REG_DAC_POWER0, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

    // Enable ADC Op Offset Cancellation and Enable Dither
    ScalerSetBit(P6_B2_REG_ADC_CTRL, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT0));

    // Set ADC Front End Gain(-4.2dB)
    ScalerSetByte(P6_B3_REG_AFE_GAIN, 0x33);

    // Set Vref for Buffer Mode
    ScalerSetBit(P6_C9_REG_ANA_RESERVE0, ~(_BIT3 | _BIT2), _BIT3);

    // ADC Unmute and Set Boost Gain
    ScalerSetByte(P6_B5_AD_MUTE, 0x00);

    // Set AD Gail of L Ch
    ScalerSetBit(P6_B6_AD_GAIN_L, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _LINE_IN_BOOST_GAIN_DB);

    // Set AD Gail of R Ch
    ScalerSetBit(P6_B7_AD_GAIN_R, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _LINE_IN_BOOST_GAIN_DB);

    // Set Double Buffer
    ScalerSetBit(P6_B6_AD_GAIN_L, ~_BIT7, _BIT7);

    // Set Sampling Frequency "48kHz" For S/PDIF Output From ADC In
    ScalerSetBit(P6_E2_AD_SPDIF_CS_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _AUDIO_SPDIF_FS_48KHZ);

    // Set Channel Count "2 ch" For S/PDIF Output From ADC In
    ScalerSetBit(P6_E3_AD_SPDIF_CS_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

    // Enable I2S Output for ADC In
    ScalerSetBit(P6_E7_AD_I2S_CTRL, ~_BIT7, _BIT7);
}
#endif

#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Auido Speaker Testing Process
// Input Value  : Enable or Disable
// Output Value : None
//--------------------------------------------------
void ScalerAudioInternalAudioGenSwitch(bit bOn, BYTE ucInputPort)
{
    switch(ucInputPort)
    {
        case _D0_INPUT_PORT:

#if((_D6_INPUT_PORT_TYPE != _D6_NO_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        case _D6_INPUT_PORT:
#endif
            break;

        case _D1_INPUT_PORT:

#if(_D1_HDMI_SUPPORT == _ON)
            ScalerAudioD2InternalAudioGenSwitch(bOn);
#endif
            break;

        case _D2_INPUT_PORT:

#if(_D2_HDMI_SUPPORT == _ON)
            ScalerAudioD2InternalAudioGenSwitch(bOn);
#endif
            break;

        case _D3_INPUT_PORT:

#if(_D3_HDMI_SUPPORT == _ON)
            ScalerAudioD3InternalAudioGenSwitch(bOn);
#endif
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get Whether Internal Audio Pattern Gen is Enabled
// Input Value  : None
// Output Value : _ENABLE or _DISABLE
//--------------------------------------------------
bit ScalerAudioGetInternalAudioGenEnable(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
        case _D0_INPUT_PORT:

#if((_D6_INPUT_PORT_TYPE != _D6_NO_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        case _D6_INPUT_PORT:
#endif
            break;

        case _D1_INPUT_PORT:

#if(_D1_HDMI_SUPPORT == _ON)
            return ScalerAudioD2GetInternalAudioGenEnable();
#endif

        case _D2_INPUT_PORT:

#if(_D2_HDMI_SUPPORT == _ON)
            return ScalerAudioD2GetInternalAudioGenEnable();
#endif

        case _D3_INPUT_PORT:

#if(_D3_HDMI_SUPPORT == _ON)
            return ScalerAudioD3GetInternalAudioGenEnable();
#endif

        default:
            break;
    }

    return _DISABLE;
}

#endif // End of #if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
#endif // End of #if(_AUDIO_SUPPORT == _ON)
