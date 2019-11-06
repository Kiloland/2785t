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
// ID Code      : RL6432_Series_ODGetStatus.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "RL6432_Series_ODLibInternalInclude.h"

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
EnumFunctionOnOFF ScalerODGetStatus(void);
BYTE ScalerODGetDeltaGain(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

//--------------------------------------------------
// Description  : Get OD on/off status
// Input Value  : None
// Output Value : _FUNCTION_ON/_FUNCTION_OFF
//--------------------------------------------------
EnumFunctionOnOFF ScalerODGetStatus(void)
{
    return (ScalerGetBit(P3_A1_LS_CTRL0, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6)) ? _FUNCTION_ON : _FUNCTION_OFF;
}


//--------------------------------------------------
// Description  : Get OD delta gain
// Input Value  : None
// Output Value : Delta gain
//--------------------------------------------------
BYTE ScalerODGetDeltaGain(void)
{
    return ScalerGetByte(P3_A3_DELTA_GAIN);
}


