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
// ID Code      : ScalerSync.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_SYNC__

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
#if(_DDR_BURN_IN_TEST == _ON)
bit g_bDDRDdomainGetGlobalCrc = _FALSE;
BYTE g_pucDDRDDomainM1CRCValue[6];
BYTE g_pucDDRDDomainM2CRCValue[6];
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if(_ADC_SUPPORT == _ON)
void ScalerSyncAdcApllPowerDown(void);
void ScalerSyncAdcPowerProc(EnumPowerAction enumPowerAction);
#endif

#if(_DDR_BURN_IN_TEST == _ON)
void ScalerSyncDDRBurnInCRCTest(void);
BYTE ScalerSyncDDRResultCRC(void);
void ScalerSyncDDREnableCRCFunction(bit bEnable);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_ADC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Power Down VGA Function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncAdcApllPowerDown(void)
{
    // Power down APLL
    ScalerSetBit(P1_AF_PLL_WD, ~_BIT0, _BIT0);

    // Power down APLL by Misc Control
    ScalerSetBit(P1_F2_APLL_MISC, ~_BIT7, _BIT7);

    // Power down ADC VCM/ADC clock/SOG Power/RGB Channel
    ScalerSetBit(P0_C6_ADC_POWER, ~(_BIT7 | _BIT6 | _BIT5 | _BIT2 | _BIT1 | _BIT0), 0x00);
}

//--------------------------------------------------
// Description  : VGA Power Proc
// Input Value  : enumPowerAction --> Power Action
// Output Value : None
//--------------------------------------------------
void ScalerSyncAdcPowerProc(EnumPowerAction enumPowerAction)
{
    switch(enumPowerAction)
    {
        case _POWER_ACTION_AC_ON_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_NORMAL:
        case _POWER_ACTION_PS_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_FAKE_OFF:

            // ADC Bandgap Enable
            ScalerADCBandgap(_ON);

#if(_VGA_SUPPORT == _ON)
            // _BIT3: H-Sync Stable Debounce Tolerance, 0 --> +-2 Crystal Cycle, 1: +- 4 Crytal Cycle
            // Current Set P0_4F[3] = 1 In PS and Set P0_4F[3] = 0 in Normal,
            // In order to solve H-Sync not stable when worked on some 6463 PCB Version
            ScalerSetBit(P0_4F_STABLE_MEASURE, ~_BIT3, 0x00);
#endif

            break;

        case _POWER_ACTION_NORMAL_TO_PS:

            // Power down ADC/APLL
            ScalerSyncAdcApllPowerDown();

            // ADC Bandgap Disable
            ScalerADCBandgap(_OFF);

#if(_VGA_SUPPORT == _ON)
            // Schmitt trigger setting old mode in power saving.
            ScalerSetByte(P0_F4_HS_SCHMITT_TRIGGE_CTRL, 0xC2);

            // _BIT3: H-Sync Stable Debounce Tolerance, 0 --> +-2 Crystal Cycle, 1: +- 4 Crytal Cycle
            // Current Set P0_4F[3] = 1 In PS and Set P0_4F[3] = 0 in Normal,
            // In order to solve H-Sync not stable when worked on some 6463 PCB Version
            ScalerSetBit(P0_4F_STABLE_MEASURE, ~_BIT3, _BIT3);

            // Disable Sync proc clock
            ScalerSetBit(P0_47_SYNC_SELECT, ~_BIT7, _BIT7);
#endif

            break;

        case _POWER_ACTION_NORMAL_TO_OFF:
        case _POWER_ACTION_AC_ON_TO_OFF:
        case _POWER_ACTION_PS_TO_OFF:

            // Power down ADC/APLL
            ScalerSyncAdcApllPowerDown();

            // ADC Bandgap Disable
            ScalerADCBandgap(_OFF);

#if(_VGA_SUPPORT == _ON)
            // Schmitt trigger setting old mode in power saving.
            ScalerSetByte(P0_F4_HS_SCHMITT_TRIGGE_CTRL, 0x42);

            // Disable sync pulse detect
            ScalerSyncProcPulseDetectEnable(_DISABLE);

            // Disable Sync proc clock
            ScalerSetBit(P0_47_SYNC_SELECT, ~_BIT7, _BIT7);
#endif

            break;

        default:
            break;
    }
}
#endif

#if(_DDR_BURN_IN_TEST == _ON)
//--------------------------------------------------
// Description  : ScalerDDR3BurnInCRCTest
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncDDRBurnInCRCTest(void)
{
    // Disable Global Double
    ScalerGlobalDoubleBufferEnable(_DISABLE);

    // Disable Watch Dog
    ScalerGlobalWatchDog(_DISABLE);

    // Disabe I/D dither
    ScalerColorIDitherEnable(_FUNCTION_OFF);
    ScalerColorDDitherEnable(_FUNCTION_OFF);

    PCB_LED_ACTIVE();

    while(_TRUE)
    {
        BYTE ucResultCRC = ScalerSyncDDRResultCRC();

        if(ucResultCRC == _SUCCESS)
        {
            DebugMessageMemoryPhaseCal("CRC PASS", ucResultCRC);
        }
        else
        {
            DebugMessageMemoryPhaseCal("CRC FAIL", ucResultCRC);

            switch(ucResultCRC)
            {
                case (_BIT7 | _BIT3):
                    // I/M/D M1 + M2 CRC fail
                    PCB_LED_OFF();
                    break;

                case _BIT3:
                    // I/M/D M1 CRC fail
                    PCB_LED_ON();
                    break;

                case _BIT7:
                    // I/M/D M2 CRC fail
                    PCB_LED_IDLE();
                    break;

                default:
                    break;
            }

            while(_TRUE)
            {
                ScalerDebug();
            }
        }

        ScalerDebug();
    }
}

//--------------------------------------------------
// Description  : ScalerDDR3ResultCRC
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerSyncDDRResultCRC(void)
{
    BYTE ucCRCRegOffset = 0;
    BYTE ucResult = 0;
    BYTE pucIDomainM1CRCValue[6] = {0};
    BYTE pucMDomainM1CRCValue[6] = {0};
    BYTE pucDDomainM1CRCValue[6] = {0};

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
    BYTE pucIDomainM2CRCValue[6] = {0};
    BYTE pucMDomainM2CRCValue[6] = {0};
    BYTE pucDDomainM2CRCValue[6] = {0};
#endif

    ScalerSyncDDREnableCRCFunction(_ON);

    //===========================================
    // Get I-domain CRC
    //===========================================
    // Wait until IVS_START
    ScalerTimerWaitForEvent(_EVENT_IVS);
    ScalerTimerWaitForEvent(_EVENT_IVS);

    // Read I-domain CRC (First 6 Bytes of M1 and M2 CRC)
    for(ucCRCRegOffset = 0; ucCRCRegOffset < sizeof(pucIDomainM1CRCValue); ucCRCRegOffset++)
    {
        pucIDomainM1CRCValue[ucCRCRegOffset] = ScalerGetByte(P36_01_I_MAIN1_CRC_1 + ucCRCRegOffset);

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
        pucIDomainM2CRCValue[ucCRCRegOffset] = ScalerGetByte(P36_07_I_MAIN2_CRC_1 + ucCRCRegOffset);
#endif
    }

    //===========================================
    // Get M-domain CRC
    //===========================================
    // Wait until DVS_START
    ScalerTimerWaitForEvent(_EVENT_DVS);
    ScalerTimerWaitForEvent(_EVENT_DVS);

    // Read M-domain CRC (First 6 Bytes of M1 and M2 CRC)
    for(ucCRCRegOffset = 0; ucCRCRegOffset < sizeof(pucMDomainM1CRCValue); ucCRCRegOffset++)
    {
        pucMDomainM1CRCValue[ucCRCRegOffset] = ScalerGetByte(P36_41_M_M1_CRC_1 + ucCRCRegOffset);

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
        pucMDomainM2CRCValue[ucCRCRegOffset] = ScalerGetByte(P36_47_M_M2_CRC_1 + ucCRCRegOffset);
#endif
    }

    //===========================================
    // Get D-domain CRC
    //===========================================
    // Wait until DVS_START
    ScalerTimerWaitForEvent(_EVENT_DVS);
    ScalerTimerWaitForEvent(_EVENT_DVS);

    if(g_bDDRDdomainGetGlobalCrc == _FALSE)
    {
        // Read First D-domain CRC (First 6 Bytes of M1 and M2 CRC)
        for(ucCRCRegOffset = 0; ucCRCRegOffset < sizeof(g_pucDDRDDomainM1CRCValue); ucCRCRegOffset++)
        {
            g_pucDDRDDomainM1CRCValue[ucCRCRegOffset] = ScalerGetByte(P36_2D_D_MAIN1_CRC_1 + ucCRCRegOffset);

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
            g_pucDDRDDomainM2CRCValue[ucCRCRegOffset] = ScalerGetByte(P36_33_D_MAIN2_CRC_1 + ucCRCRegOffset);
#endif
        }

        g_bDDRDdomainGetGlobalCrc = _TRUE;
    }

    // Read D-domain CRC (First 3 Bytes of M1 and M2 CRC)
    for(ucCRCRegOffset = 0; ucCRCRegOffset < sizeof(pucDDomainM1CRCValue); ucCRCRegOffset++)
    {
        pucDDomainM1CRCValue[ucCRCRegOffset] = ScalerGetByte(P36_2D_D_MAIN1_CRC_1 + ucCRCRegOffset);

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
        pucDDomainM2CRCValue[ucCRCRegOffset] = ScalerGetByte(P36_33_D_MAIN2_CRC_1 + ucCRCRegOffset);
#endif
    }

    //===========================================
    // Compare I/M/D-domain CRC with  M-domain CRC
    //===========================================
    // I/M/D M1 CRC
    if((memcmp(pucIDomainM1CRCValue, pucMDomainM1CRCValue, sizeof(pucIDomainM1CRCValue)) != 0) ||
       (memcmp(pucDDomainM1CRCValue, g_pucDDRDDomainM1CRCValue, sizeof(pucIDomainM1CRCValue)) != 0))
    {
        ucResult |= _BIT3;
    }

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
    // I/M/D M2 CRC
    if((memcmp(pucIDomainM2CRCValue, pucMDomainM2CRCValue, sizeof(pucIDomainM2CRCValue)) != 0) ||
       (memcmp(pucDDomainM2CRCValue, g_pucDDRDDomainM2CRCValue, sizeof(pucIDomainM2CRCValue)) != 0))
    {
        ucResult |= _BIT7;
    }
#endif

    ScalerSyncDDREnableCRCFunction(_OFF);

    if(ucResult == 0x00)
    {
        return _SUCCESS;
    }
    else
    {
        return ucResult;
    }
}

//--------------------------------------------------
// Description  : ScalerDDR3EnableCRCFunction
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncDDREnableCRCFunction(bit bEnable)
{
    if(bEnable == _ON)
    {
        // Enable M1, M2 I-domain CRC output
        ScalerSetByte(P36_00_I_CRC_CTRL, 0x8C);

        // Enable M1, M2 M-domain CRC output
        ScalerSetByte(P36_40_M_CRC_CTRL, 0x0C);

        // Enable M1, M2 D-domain CRC output
        ScalerSetByte(P36_2C_D_CRC_CTRL, 0x0C);
    }
    else
    {
        // Disable M1, M2 I-domain CRC output
        ScalerSetByte(P36_00_I_CRC_CTRL, 0x00);

        // Disable M1, M2 M-domain CRC output
        ScalerSetByte(P36_40_M_CRC_CTRL, 0x00);

        // Disable M1, M2 D-domain CRC output
        ScalerSetByte(P36_2C_D_CRC_CTRL, 0x00);
    }
}
#endif // End of #if(_DDR_BURN_IN_TEST == _ON)


