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
// ID Code      : RL6432_Series_TimerFunction.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"

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
void ScalerTimerClrEventStatus(EnumWaitEventType enumEvent);
BYTE ScalerTimerGetEventStatus(EnumWaitEventType enumEvent);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Clear Event Status
// Input Value  : enumEvent   --> Specified event
// Output Value : None
//--------------------------------------------------
void ScalerTimerClrEventStatus(EnumWaitEventType enumEvent)
{
    switch(enumEvent)
    {
        case _EVENT_DEN_START:
            // Total
            ScalerSetBit(P0_05_IRQ_CTRL1, ~(_BIT6 | _BIT4 | _BIT2), _BIT2);
            break;

        case _EVENT_DEN_STOP:
            // Total
            ScalerSetBit(P0_05_IRQ_CTRL1, ~(_BIT6 | _BIT4 | _BIT2), _BIT4);
            break;

        case _EVENT_ALL:
            ScalerSetBit(P0_05_IRQ_CTRL1, ~(_BIT6 | _BIT4 | _BIT2), (_BIT4 | _BIT2));
            ScalerSetByte(P0_03_STATUS1, (_BIT7 | _BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
            break;

        case _EVENT_IVS:
        case _EVENT_IEN_STOP:
        default:
            ScalerSetByte(P0_03_STATUS1, enumEvent);
            break;
    }
}

//--------------------------------------------------
// Description  : Hold until the specified event occurs
// Input Value  : enumEvent   --> Specified event
// Output Value : Return _TRUE if event occurs
//--------------------------------------------------
BYTE ScalerTimerGetEventStatus(EnumWaitEventType enumEvent)
{
    switch(enumEvent)
    {
        case _EVENT_DEN_START:
            // Total
            return ((ScalerGetByte(P0_05_IRQ_CTRL1) & _BIT2) << 2);

        case _EVENT_DEN_STOP:
            // Total
            return ((ScalerGetByte(P0_05_IRQ_CTRL1) & _BIT4) << 1);

        case _EVENT_ALL:
            return (((ScalerGetByte(P0_05_IRQ_CTRL1) & _BIT2) << 2) |
                    ((ScalerGetByte(P0_05_IRQ_CTRL1) & _BIT4) << 1) |
                    (ScalerGetByte(P0_03_STATUS1) & (_BIT7 | _BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0)));

        case _EVENT_IVS:
        case _EVENT_IEN_STOP:
        default:
            return (ScalerGetByte(P0_03_STATUS1) & enumEvent);
    }
}

