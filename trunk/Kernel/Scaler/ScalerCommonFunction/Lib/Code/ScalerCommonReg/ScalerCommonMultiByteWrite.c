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
// ID Code      : ScalerCommonMultiByteWrite.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "ScalerCommonRegLibInternalInclude.h"

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

void ScalerWrite(WORD usAddr, WORD usLength, BYTE *pucArray, bit bAutoInc);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

//--------------------------------------------------
// Description  : Write a data array into registers
// Input Value  : usAddr    --> Start address of register
//                usLength  --> Numbers of data we want to write
//                pArray    --> Pointer of the writing data array
//                bAutoInc  --> Address auto increasing select
// Output Value : None
//--------------------------------------------------
void ScalerWrite(WORD usAddr, WORD usLength, BYTE *pucArray, bit bAutoInc)
{
    if(usLength != 0)
    {
        if(bAutoInc == _AUTOINC)
        {
            memcpy((BYTE xdata *)usAddr, pucArray, usLength);
        }
        else
        {
            WORD usIndex = 0;

            for(usIndex = 0; usIndex < usLength; usIndex++)
            {
                ScalerSetByte(usAddr, pucArray[usIndex]);
            }
        }
    }
}
