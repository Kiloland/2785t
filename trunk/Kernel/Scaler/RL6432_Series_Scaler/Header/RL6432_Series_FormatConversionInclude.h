/********************************************************************************/
/*   The  Software  is  proprietary,  confidential,  and  valuable to Realtek   */
/*   Semiconductor  Corporation  ("Realtek").  All  rights, including but not   */
/*   limited  to  copyrights,  patents,  trademarks, trade secrets, mask work   */
/*   rights, and other similar rights and interests, are reserved to Realtek.   */
/*   Without  prior  written  consent  from  Realtek,  copying, reproduction,   */
/*   modification,  distribution,  or  otherwise  is strictly prohibited. The   */
/*   Software  shall  be  kept  strictly  in  confidence,  and  shall  not be   */
/*   disclosed to or otherwise accessed by any third party.                     */
/*   c<2003> - <2011>                                                           */
/*   The Software is provided "AS IS" without any warranty of any kind,         */
/*   express, implied, statutory or otherwise.                                  */
/********************************************************************************/

//----------------------------------------------------------------------------------------------------
// ID Code      : RL6432_Series_FormatConversionInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _FC_SOURCE_SST = 0x00,
    _FC_SOURCE_ADC = _BIT1,
    _FC_SOURCE_D0 = (_BIT1 | _BIT0),
    _FC_SOURCE_D1 = _BIT2,
    _FC_SOURCE_D2 = (_BIT2 | _BIT0),
    _FC_SOURCE_D3 = (_BIT2 | _BIT1),
    _FC_SOURCE_DUAL_DVI = (_BIT3 | _BIT1),
    _FC_SOURCE_NONE = 0xFF,
} EnumFormatConversionSourceType;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

extern void ScalerFmtCnvInitialSetting(EnumSourceSearchPort enumSourceSearchPort);
extern EnumFormatConversionSourceType ScalerFmtCnvGetSourceType(void);
