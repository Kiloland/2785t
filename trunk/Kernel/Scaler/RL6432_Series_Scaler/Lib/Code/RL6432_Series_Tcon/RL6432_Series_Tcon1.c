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
// ID Code      : RL6432_Series_Tcon1.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "RL6432_Series_TconLibInternalInclude.h"

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
void ScalerTcon1Enable(bit bEnable);
void ScalerTcon1Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

//--------------------------------------------------
// Description  : Set Tcon1 local enable
// Input Value  : bEnable --> enable
// Output Value : None
//--------------------------------------------------
void ScalerTcon1Enable(bit bEnable)
{
    ScalerSetDataPortBit(P15_A3_TCON_ADDR, _P15_A4_PT_28_TC1_CTRL, ~(_BIT7), ((BYTE)bEnable << 7));
}

//--------------------------------------------------
// Description  : Set Tcon1 Region
// Input Value  : usHstart --> Horizon start
//                usHend --> Horizon end
//                usVstart --> Vertical start
//                usVend --> Vertical end
// Output Value : None
//--------------------------------------------------
void ScalerTcon1Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend)
{
    usVstart &= 0x1FFF;
    usVend &= 0x1FFF;

    usHstart &= 0x1FFF;
    usHend &= 0x1FFF;

    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_20_TC1_VS_MSB, HIBYTE(usVstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_21_TC1_VS_LSB, LOBYTE(usVstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_22_TC1_VE_MSB, HIBYTE(usVend));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_23_TC1_VE_LSB, LOBYTE(usVend));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_24_TC1_HS_MSB, HIBYTE(usHstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_25_TC1_HS_LSB, LOBYTE(usHstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_26_TC1_HE_MSB, HIBYTE(usHend));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_27_TC1_HE_LSB, LOBYTE(usHend));
}

