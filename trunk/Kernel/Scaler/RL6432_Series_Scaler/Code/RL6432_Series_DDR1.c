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
// ID Code      : RL6432_Series_DDR1.c No.0000
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

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR1)
void ScalerDDR1PowerEnable(bit bOn);
void ScalerDDR1MemoryType(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR1)
//--------------------------------------------------
// Description  : DDR1 ScalerDDR1PowerMode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDR1PowerEnable(bit bOn)
{
    if(bOn == _ON)
    {
        // Config for DDR1 mode
        ScalerSetBit(P4_00_SDDR_CTRL, ~_BIT0, 0x00);

        // Enable OP power
        ScalerSetBit(P4_00_SDDR_CTRL, ~_BIT1, 0x00);

        // DDR Vref select internal
        ScalerSetBit(P4_00_SDDR_CTRL, ~_BIT4, 0x00);

        // Enable DQ low different amplifier
        ScalerSetBit(P4_00_SDDR_CTRL, ~_BIT2, 0x00);

        // Enable DQ high different amplifier
        ScalerSetBit(P4_00_SDDR_CTRL, ~_BIT3, 0x00);

        // Enable Pad power on
        ScalerSetBit(P4_00_SDDR_CTRL, ~_BIT5, _BIT5);

        // Disable Second OP power
        ScalerSetBit(P4_10_SDDR_CTRL, ~_BIT1, _BIT1);

#if(_MEMORY_SIZE_CONFIG == _4M_16BIT_DDR1_2PCS)

        // Config for Second DDR1 mode
        ScalerSetBit(P4_10_SDDR_CTRL, ~_BIT0, 0x00);

        // Enable Second OP power
        ScalerSetBit(P4_10_SDDR_CTRL, ~_BIT1, 0x00);

        // DDR Second Vref select internal
        ScalerSetBit(P4_10_SDDR_CTRL, ~_BIT4, 0x00);

        // Enable Second DQ low different amplifier
        ScalerSetBit(P4_10_SDDR_CTRL, ~_BIT2, 0x00);

        // Enable Second DQ high different amplifier
        ScalerSetBit(P4_10_SDDR_CTRL, ~_BIT3, 0x00);

        // Enable Second Pad power on
        ScalerSetBit(P4_10_SDDR_CTRL, ~_BIT5, _BIT5);
#endif

        // Disable DDR1 CKE force low into Power down mode
        ScalerSetBit(P4_A6_SDR_SLEW_RATE, ~_BIT1, 0x00);

        // Precharge power down mode select
        ScalerSetBit(P4_B7_SDR_POWER_CTRL0, ~(_BIT5 | _BIT4), 0x00);

        // Delay Time us [5,x] Waiting for DDR setting
        DELAY_5US();

        // Inactive power down
        ScalerSetBit(P4_B7_SDR_POWER_CTRL0, ~_BIT7, 0x00);
    }
    else
    {
        // DDR Vref select internal
        ScalerSetBit(P4_00_SDDR_CTRL, ~_BIT4, 0x00);

        // Enable DQ low different amplifier
        ScalerSetBit(P4_00_SDDR_CTRL, ~_BIT2, 0x00);

        // Enable DQ high different amplifier
        ScalerSetBit(P4_00_SDDR_CTRL, ~_BIT3, 0x00);

        if(ScalerGlobalGetIDCode() >= _RL6432_VER_C_ID_CODE)
        {
            // Disable OP power
            ScalerSetBit(P4_00_SDDR_CTRL, ~_BIT1, _BIT1);
        }
        else
        {
            // Enable OP power
            ScalerSetBit(P4_00_SDDR_CTRL, ~_BIT1, 0x00);
        }

        // Enable Pad power on
        ScalerSetBit(P4_00_SDDR_CTRL, ~_BIT5, _BIT5);

        // DDR Second Vref select internal
        ScalerSetBit(P4_10_SDDR_CTRL, ~_BIT4, 0x00);

        // Enable Second DQ low different amplifier
        ScalerSetBit(P4_10_SDDR_CTRL, ~_BIT2, 0x00);

        // Enable Second DQ high different amplifier
        ScalerSetBit(P4_10_SDDR_CTRL, ~_BIT3, 0x00);

        if(ScalerGlobalGetIDCode() >= _RL6432_VER_C_ID_CODE)
        {
            // Disable Second OP power
            ScalerSetBit(P4_10_SDDR_CTRL, ~_BIT1, _BIT1);
        }
        else
        {
            // Enable Second OP power
            ScalerSetBit(P4_10_SDDR_CTRL, ~_BIT1, 0x00);
        }

        // Enable Second Pad power on
        ScalerSetBit(P4_10_SDDR_CTRL, ~_BIT5, _BIT5);

        // Deep Power Down mode select
        ScalerSetBit(P4_B7_SDR_POWER_CTRL0, ~(_BIT5 | _BIT4), _BIT5);

        // Delay Time us [5,x] Waiting for DDR setting
        DELAY_5US();

        // Active power down
        ScalerSetBit(P4_B7_SDR_POWER_CTRL0, ~_BIT7, _BIT7);

        // Enable DDR1 CKE force low into Power down mode
        ScalerSetBit(P4_A6_SDR_SLEW_RATE, ~_BIT1, _BIT1);

        // Disable DQ low different amplifier
        ScalerSetBit(P4_00_SDDR_CTRL, ~_BIT2, _BIT2);

        // Disable DQ high different amplifier
        ScalerSetBit(P4_00_SDDR_CTRL, ~_BIT3, _BIT3);

        // DDR Vref select external
        ScalerSetBit(P4_00_SDDR_CTRL, ~_BIT4, _BIT4);

        // Disable Pad power off
        ScalerSetBit(P4_00_SDDR_CTRL, ~_BIT5, 0x00);

        // Disable DQ low different amplifier
        ScalerSetBit(P4_10_SDDR_CTRL, ~_BIT2, _BIT2);

        // Disable DQ high different amplifier
        ScalerSetBit(P4_10_SDDR_CTRL, ~_BIT3, _BIT3);

        // DDR Vref select external
        ScalerSetBit(P4_10_SDDR_CTRL, ~_BIT4, _BIT4);

        // Disable Pad power off
        ScalerSetBit(P4_10_SDDR_CTRL, ~_BIT5, 0x00);
    }
}

//--------------------------------------------------
// Description  : DDR1 system initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDR1MemoryType(void)
{
#if(_MEMORY_SIZE_CONFIG == _4M_16BIT_DDR1_1PC)

    // Set DDR1 Memory Type & Control CAS Latency = 1.5
    ScalerSetBit(P4_A5_SDR_MEM_TYPE, ~(_BIT7 | _BIT6 | _BIT5 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT1));

    // Set DDR1 Read SRAM Length
    ScalerSetByte(P4_BD_SDR_MCU_RD_LEN, 0x02);

#elif(_MEMORY_SIZE_CONFIG == _4M_16BIT_DDR1_2PCS)

    // Set DDR1 Memory Type & Control CAS Latency = 1.5
    ScalerSetBit(P4_A5_SDR_MEM_TYPE, ~(_BIT7 | _BIT6 | _BIT5 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT1));

    // Set DDR1 Read SRAM Length
    ScalerSetByte(P4_BD_SDR_MCU_RD_LEN, 0x01);

#endif
}

#endif // End of #if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR1)
