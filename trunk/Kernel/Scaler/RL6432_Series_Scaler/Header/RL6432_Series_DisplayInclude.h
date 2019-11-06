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
// ID Code      : RL6432_Series_DisplayInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#define _LVDS_TXCD_OUTPUT_DATA_PORT_ADDR            (P39_03_LVDS_DISPLAY_CONV_CTRL2)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_PANEL_STYLE == _PANEL_LVDS)
extern void ScalerDisplayLvdsInitialTable(void);
extern void ScalerDisplayLvdsPadPower(bit bOn);

#if((_LVDS_PORT_SEL == _LVDS_1_PORT_A) || (_LVDS_PORT_SEL == _LVDS_1_PORT_B) || (_LVDS_PORT_SEL == _LVDS_2_PORT_AB) || (_LVDS_PORT_SEL == _LVDS_4_PORT_ABCD))
extern void ScalerDisplayLvdsSetVcoBand(BYTE ucVcoBand);
extern void ScalerDisplayLvdsSetPhaseBand(BYTE ucPhaseBand);
#endif

extern bit ScalerDisplayGetLvdsPowerStatus(void);
extern void ScalerDisplayLvdsPLL(bit bOn);

#elif(_PANEL_STYLE == _PANEL_DPTX)
extern void ScalerDisplayUseLvdsPadPower(bit bOn);
#endif

