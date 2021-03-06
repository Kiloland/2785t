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
// ID Code      : ScalerColorLibInternalInclude.h
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "ScalerFunctionCommonInclude.h"
#include "ScalerColorLibInterface.h"
#include "ScalerCommonRegLibInclude.h"
#include "ScalerCommonNVRamLibInclude.h"
#if(_SCALER_TYPE == _RL6369_SERIES)
#include "RL6369_Series_ColorLibInclude.h"
#elif(_SCALER_TYPE == _RL6410_SERIES)
#include "RL6410_Series_ColorLibInclude.h"
#elif(_SCALER_TYPE == _RL6432_SERIES)
#include "RL6432_Series_ColorLibInclude.h"
#elif(_SCALER_TYPE == _RL6449_SERIES)
#include "RL6449_Series_ColorLibInclude.h"
#elif(_SCALER_TYPE == _RL6463_SERIES)
#include "RL6463_Series_ColorLibInclude.h"
#elif(_SCALER_TYPE == _RL6492_SERIES)
#include "RL6492_Series_ColorLibInclude.h"
#endif


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
// HLW Window Detection
extern void ScalerColorDCCSetMeasureRegion(EnumHLWType enumHLWType);

