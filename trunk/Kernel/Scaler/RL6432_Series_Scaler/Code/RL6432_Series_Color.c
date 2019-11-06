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
// ID Code      : RL6432_Series_Color.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_D_DITHER_SUPPORT == _ON)
#define _DDITHER_TEMPORAL_ENABLE                _ENABLE
#endif // end of #if(_D_DITHER_SUPPORT == _ON)

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
#if(_D_DITHER_SUPPORT == _ON)
void ScalerColorDDitherAdjust(BYTE code *pucDitherTable, BYTE code *pucSeqTable, BYTE code *pucTempoTable, BYTE ucBankAddress);
#endif

#if(_UNIFORMITY_SUPPORT == _ON)
void ScalerColorPanelUniformityInitial(BYTE ucLUTMode);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_D_DITHER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Adjust D Dither Common Setting
// Input Value  :
//                pucDitherTable : Dither Table Pointer
//                pucSeqTable : Seq Table Pointer
//                pucTempoTable : Temporal Table Pointer
//                ucBankAddress : Bank Address
// Output Value : None
//--------------------------------------------------
void ScalerColorDDitherAdjust(BYTE code *pucDitherTable, BYTE code *pucSeqTable, BYTE code *pucTempoTable, BYTE ucBankAddress)
{
    DWORD ulSettingOption = 0x00000000;
    BYTE ucKeepNFrame = _DDITHER_KEEP_1_FRAME;

    ScalerColorDDitherLoadDitherTable(pucDitherTable, ucBankAddress);

#if((_D_DITHER_MULTI_SEQ_ENABLE == _ENABLE) || (_D_DITHER_SERIES_SEQ_ENABLE == _ENABLE) || (_D_DITHER_ADVANCE_SETTING_ENABLE == _ENABLE))
    ScalerColorDDitherLoadSeqTable(pucSeqTable, 192, ucBankAddress);
#else
    ScalerColorDDitherLoadSeqTable(pucSeqTable, 48, ucBankAddress);
#endif

    ScalerColorDDitherLoadTempoTable(pucTempoTable, ucBankAddress);

#if(((_D_DITHER_MULTI_SEQ_ENABLE == _ENABLE) && (_D_DITHER_SERIES_SEQ_ENABLE == _DISABLE)) ||\
    (_D_DITHER_SHARE_SEQ_ENABLE == _ENABLE) || (_D_DITHER_SEQ_INV_ENABLE == _ENABLE) ||\
    (_D_DITHER_V_FRAME_MOD == _ENABLE) || (_D_DITHER_H_FRAME_MOD == _ENABLE))

    switch(_D_DITHER_SUPER_PIXEL_SIZE)
    {
        case _DDITHER_SUPER_PIXEL_2X2:
            if((_PANEL_DISP_BIT_MODE == _PANEL_DISP_18_BIT) || (_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT))
            {
                ucKeepNFrame = _DDITHER_KEEP_4_FRAME;
            }
            else
            {
                ucKeepNFrame = _DDITHER_KEEP_16_FRAME;
            }
            break;

        case _DDITHER_SUPER_PIXEL_2X4:
        case _DDITHER_SUPER_PIXEL_4X2:
            if((_PANEL_DISP_BIT_MODE == _PANEL_DISP_18_BIT) || (_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT))
            {
                ucKeepNFrame = _DDITHER_KEEP_2_FRAME;
            }
            else
            {
                ucKeepNFrame = _DDITHER_KEEP_8_FRAME;
            }
            break;

        case _DDITHER_SUPER_PIXEL_4X4:
            if((_PANEL_DISP_BIT_MODE == _PANEL_DISP_18_BIT) || (_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT))
            {
                ucKeepNFrame = _DDITHER_KEEP_1_FRAME;
            }
            else
            {
                ucKeepNFrame = _DDITHER_KEEP_4_FRAME;
            }
            break;

        case _DDITHER_SUPER_PIXEL_4X8:
        case _DDITHER_SUPER_PIXEL_8X4:
            if((_PANEL_DISP_BIT_MODE == _PANEL_DISP_18_BIT) || (_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT))
            {
                ucKeepNFrame = _DDITHER_KEEP_1_FRAME;
            }
            else
            {
                ucKeepNFrame = _DDITHER_KEEP_2_FRAME;
            }
            break;

        default:
            ucKeepNFrame = _DDITHER_KEEP_1_FRAME;
            break;
    }

#endif

    ulSettingOption = (_D_DITHER_6BIT_PANEL_FUNC_ENABLE << 7) | (_DDITHER_TEMPORAL_ENABLE << 4) | (_D_DITHER_V_FRAME_MOD << 1) | _D_DITHER_H_FRAME_MOD;
    ulSettingOption = ulSettingOption | (((DWORD)((ucKeepNFrame << 4) | _D_DITHER_SUPER_PIXEL_SIZE)) << 8);
    ulSettingOption = ulSettingOption | (((DWORD)((_D_DITHER_SERIES_SEQ_ENABLE << 3) | (_D_DITHER_MULTI_SEQ_ENABLE << 2))) << 16);
    ulSettingOption = ulSettingOption | (((DWORD)((_D_DITHER_SHARE_SEQ_ENABLE << 3) | (_D_DITHER_SEQ_INV_ENABLE << 1) | _D_DITHER_SEQ_INV_MODE)) << 24);

    ScalerColorDDitherLoadSetting(ulSettingOption);
}
#endif // #if(_D_DITHER_SUPPORT == _ON)

#if(_UNIFORMITY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Initial Panel Uniformity Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorPanelUniformityInitial(BYTE ucLUTMode)
{
    BYTE ucMultiLUTMode = 0;
    ScalerSetBit(P34_00_UN_GLOBAL_CTRL, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), (((_PANEL_UNIFORMITY_HOR_INTERVAL / 64) << 5) | ((_PANEL_UNIFORMITY_VER_INTERVAL / 64) << 3)));
    switch(ucLUTMode)
    {
        default:
            break;

        case _UNIFORMITY_1LEVEL:

            ucMultiLUTMode = 0;
            break;

        case _UNIFORMITY_2LEVEL:

            ucMultiLUTMode = 1;
            break;

        case _UNIFORMITY_4LEVEL:

            ucMultiLUTMode = 2;
            break;
    }
    ScalerSetBit(P34_01_UN_MULTI_LUT_CTRL, ~(_BIT1 | _BIT0), (ucMultiLUTMode & 0x03));

    ScalerSetByte(P34_02_UN_GAIN_LUT_HOR_GRIDS, _PANEL_UNIFORMITY_HOR_GRIDS);
    ScalerSetByte(P34_03_UN_GAIN_LUT_VER_GRIDS, _PANEL_UNIFORMITY_VER_GRIDS);
    ScalerSetByte(P34_04_UN_GAIN_LUT_HOR_OFFSET, _PANEL_UNIFORMITY_HOR_OFFSET);
    ScalerSetByte(P34_05_UN_GAIN_LUT_VER_OFFSET, _PANEL_UNIFORMITY_VER_OFFSET);
}
#endif // End of #if(_UNIFORMITY_SUPPORT == _ON)
