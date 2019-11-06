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
// ID Code      : RL6432_Series_Tcon3.c No.0000
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
void ScalerTcon3Enable(bit bEnable);
void ScalerTcon3Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

//--------------------------------------------------
// Description  : Set Tcon3 local enable
// Input Value  : bEnable --> enable
// Output Value : None
//--------------------------------------------------
void ScalerTcon3Enable(bit bEnable)
{
    ScalerSetDataPortBit(P15_A3_TCON_ADDR, _P15_A4_PT_48_TC3_CTRL, ~(_BIT7), ((BYTE)bEnable << 7));
}

//--------------------------------------------------
// Description  : Set Tcon3 Region
// Input Value  : usHstart --> Horizon start
//                usHend --> Horizon end
//                usVstart --> Vertical start
//                usVend --> Vertical end
// Output Value : None
//--------------------------------------------------
void ScalerTcon3Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend)
{
    usVstart &= 0x1FFF;
    usVend &= 0x1FFF;

    usHstart &= 0x1FFF;
    usHend &= 0x1FFF;

    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_40_TC3_VS_MSB, HIBYTE(usVstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_41_TC3_VS_LSB, LOBYTE(usVstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_42_TC3_VE_MSB, HIBYTE(usVend));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_43_TC3_VE_LSB, LOBYTE(usVend));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_44_TC3_HS_MSB, HIBYTE(usHstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_45_TC3_HS_LSB, LOBYTE(usHstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_46_TC3_HE_MSB, HIBYTE(usHend));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_47_TC3_HE_LSB, LOBYTE(usHend));
}

