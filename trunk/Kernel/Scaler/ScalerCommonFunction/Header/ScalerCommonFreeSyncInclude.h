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
// ID Code      : ScalerCommonFreeSyncInclude.h No.0000
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

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_FREESYNC_SUPPORT == _ON)
#if(_DP_SUPPORT == _ON)
#if(_DP_FREESYNC_SUPPORT == _ON)
extern WORD ScalerFreeSyncDpGetHSPeriod(EnumSourceSearchPort enumSourceSearchPort);
extern WORD ScalerFreeSyncDpGetHSW(EnumSourceSearchPort enumSourceSearchPort);
extern WORD ScalerFreeSyncDpGetVFreq(EnumSourceSearchPort enumSourceSearchPort);
extern WORD ScalerFreeSyncDpGetVSPeriod(EnumSourceSearchPort enumSourceSearchPort);

#if(_D0_DP_EXIST == _ON)
extern BYTE ScalerFreeSyncDpRx0GetAmdSpdInfo(EnumAmdSpdInfoContent enumContent);
extern WORD ScalerFreeSyncDpRx0GetBStoHSDelay(WORD usDpHtotal);
extern void ScalerFreeSyncDpRx0GetSPDVfreqMaxMin(void);
#endif

#if(_D1_DP_EXIST == _ON)
extern BYTE ScalerFreeSyncDpRx1GetAmdSpdInfo(EnumAmdSpdInfoContent enumContent);
extern WORD ScalerFreeSyncDpRx1GetBStoHSDelay(WORD usDpHtotal);
extern void ScalerFreeSyncDpRx1GetSPDVfreqMaxMin(void);
#endif
#endif
#endif

#if(_HDMI_SUPPORT == _ON)
#if(_HDMI_FREESYNC_SUPPORT == _ON)
#if(_HDMI_MAC_PAGE2_USE == _ON)
extern BYTE ScalerFreeSyncHDMIRx0GetAmdSpdInfo(EnumAmdSpdInfoContent enumContent);
#endif

#if(_HDMI_MAC_PAGE71_USE == _ON)
extern BYTE ScalerFreeSyncHDMIRx2GetAmdSpdInfo(EnumAmdSpdInfoContent enumContent, bit bD1Combo);
#endif

#if(_HDMI_MAC_PAGE72_USE == _ON)
extern BYTE ScalerFreeSyncHDMIRx3GetAmdSpdInfo(EnumAmdSpdInfoContent enumContent);
#endif

#if(_HDMI_MAC_PAGE73_USE == _ON)
extern BYTE ScalerFreeSyncHDMIRx4GetAmdSpdInfo(EnumAmdSpdInfoContent enumContent);
#endif

#if(_HDMI_MAC_PAGE74_USE == _ON)
extern BYTE ScalerFreeSyncHDMIRx5GetAmdSpdInfo(EnumAmdSpdInfoContent enumContent);
#endif
#endif // End of #if(_HDMI_FREESYNC_SUPPORT == _ON)
#endif // End of #if(_HDMI_SUPPORT == _ON)

#endif
