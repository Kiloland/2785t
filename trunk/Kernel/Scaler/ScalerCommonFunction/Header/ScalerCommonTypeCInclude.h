/*   modification,  distribution,  or  otherwise  is strictly prohibited. The   */
/*   Software  shall  be  kept  strictly  in  confidence,  and  shall  not be   */
/*   disclosed to or otherwise accessed by any third party.                     */
/*   c<2003> - <2011>                                                           */
/*   The Software is provided "AS IS" without any warranty of any kind,         */
/*   express, implied, statutory or otherwise.                                  */
/********************************************************************************/

#if((_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON))
//----------------------------------------------------------------------------------------------------
// ID Code      : ScalerCommonTypeCInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern WORD g_usSlop;
extern BYTE g_ucoffset;
extern bit g_bsign;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern EnumTypeCAttachStatus ScalerTypeCGetCcAttach(BYTE ucInputPort);

#endif  // End of #if((_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON))

