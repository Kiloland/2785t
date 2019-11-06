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
// ID Code      : RL6432_Series_ColorPanelUniformityAdjust.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "RL6432_Series_ColorLibInternalInclude.h"

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
void ScalerColorPanelUniformityAdjust(BYTE *pucUNILUT, WORD usUNILUTSize, BYTE ucBankNum, EnumUniformityModeSelect enumUniformityMode);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Load Panel Uniformity LUT
// Input Value  : LUT, Bank number, EnumUniformityModeSelect
// Output Value : None
//--------------------------------------------------
void ScalerColorPanelUniformityAdjust(BYTE *pucUNILUT, WORD usUNILUTSize, BYTE ucBankNum, EnumUniformityModeSelect enumUniformityMode)
{
    // Set uniformity mode
    ScalerSetBit(P34_00_UN_GLOBAL_CTRL, ~_BIT1, (enumUniformityMode << 1));

    // Enable uniformity access
    ScalerSetBit(P34_00_UN_GLOBAL_CTRL, ~_BIT2, _BIT2);

    // Load uniformity gain LUT
    ScalerBurstWrite(pucUNILUT, usUNILUTSize, ucBankNum, P34_08_UN_GAIN_LUT_ACCESS_PORT, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

    // Disable uniformity access
    ScalerSetBit(P34_00_UN_GLOBAL_CTRL, ~_BIT2, 0x00);
}

