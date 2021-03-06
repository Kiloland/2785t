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
// ID Code      : ScalerColorPCMInputGammaLoadTable.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "ScalerColorLibInternalInclude.h"

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
void ScalerColorPCMInputGammaLoadTable(BYTE ucSelect);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Adjust Input gamma
// Input Value  : 0-sRGB, 1-Adobe, 2-UserDefine, 3-SoftProof
// Output Value : None
//--------------------------------------------------
void ScalerColorPCMInputGammaLoadTable(BYTE ucSelect)
{
    EnumPCMType enumPCMMode = ucSelect;
    ScalerColorPCMInputGammaAdjust((BYTE *)ScalerColorPCMGetTableAddress(enumPCMMode), ScalerColorPCMGetTableBank());
}
