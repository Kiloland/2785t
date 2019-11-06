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
// ID Code      : ScalerGlobalInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of System Clock Frequency
//--------------------------------------------------
#define _GDI_CLK_DIV                                (ScalerGetBit(P80_06_GDI_CLK_DIVIDER, (_BIT3 | _BIT2 | _BIT1 | _BIT0))) // GDI Clock Divider
#define _SYS_CLK_DIV                                (ScalerGetBit(P0_22_M1_FIFO_CLOCK_SELECT, (_BIT6 | _BIT5 | _BIT4 | _BIT3)) >> 3) // System Clock Divider
#define _SYS_CLK_KHZ                                (DWORD)((bit)ScalerGetBit(P0_22_M1_FIFO_CLOCK_SELECT, _BIT2) ? (((DWORD)1000 * _M2PLL_CLK_MHZ) / _SYS_CLK_DIV) : (_SYS_USE_ISO_CLK ? _INTERNAL_OSC_XTAL : _EXT_XTAL))

#if(_WD_TIMER_INT_SUPPORT == _ON)
//--------------------------------------------------
// Definitation of Global Xtal Clk Switch
//--------------------------------------------------
#define SET_GLOBAL_XTAL_CLK_SWITCH(x)               (g_enumGlobalXtalClkSelect = (x))
#define GET_GLOBAL_XTAL_CLK_SWITCH()                (g_enumGlobalXtalClkSelect)
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#if(_WD_TIMER_INT_SUPPORT == _ON)
//--------------------------------------------------
// Enumerations of Global Xtal Clk Switch
//--------------------------------------------------
typedef enum
{
    _GLOBAL_XTAL_CLK_SEL_UNCHANGE = 0x00,
    _GLOBAL_XTAL_CLK_SEL_TO_EXTERNAL,
    _GLOBAL_XTAL_CLK_SEL_TO_INTERNAL,
} EnumGlobalXtalClkSelect;
#endif

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_WD_TIMER_INT_SUPPORT == _ON)
extern EnumGlobalXtalClkSelect g_enumGlobalXtalClkSelect;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerGlobalIRQControl(bit bEn);
extern void ScalerGlobalOsdInitial(void);

#if(((_OD_SUPPORT == _ON) && (_FRC_SUPPORT == _ON)) || (_XTALESS_SUPPORT == _ON))
extern void ScalerGlobalSetInterrupt(EnumIRQ enumIRQType, BYTE ucEn);
#endif

#if((_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_I) ||\
    ((_LOCAL_DIMMING_SUPPORT == _ON) && (_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_III)))
extern bit ScalerGlobalGetDDomainDBStatus(void);
#endif

#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_I)
extern bit ScalerGlobalGetIDomainDBStatus(void);

#if(_FRC_SUPPORT == _ON)
extern void ScalerGlobalIDDomainDBSetBufferAddress(void);
#endif
#endif

