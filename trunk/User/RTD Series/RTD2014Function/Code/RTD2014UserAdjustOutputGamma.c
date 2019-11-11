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
// ID Code      : RTD2014UserAdjustOutputGamma.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_ADJUST_OUTPUT_GAMMA__

#include "UserCommonInclude.h"
//#include "ScalerColorLibInternalInclude.h"
#include  "ScalerFunctionCommonInclude.h"


#include "w74m00av.h"

#if(_OSD_TYPE == _REALTEK_2014_OSD)

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
#if(_GAMMA_FUNCTION == _ON)
void UserAdjustGamma(BYTE ucGamma);
#endif


//-------------------------------------------------------
// PCM
//-------------------------------------------------------
#if(_PCM_FUNCTION == _ON)
void UserAdjustPCM(BYTE ucPCM);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_GAMMA_FUNCTION == _ON)

#if 1  // alant

extern void ScalerColorOutputGammaChannelCtrl(BYTE ucColorChannel, WORD usOffset, bit bLocation);
extern void ScalerBurstWrite(BYTE *pucAddress, WORD usWriteLength, BYTE ucBankNum, WORD usHostAddr, BYTE ucTableType, bit bTableLocation);


#define _GAMMA_TABLE_SIZE                       2052
#define _GAMMA_WRITE_TO_SRAM                    0
#define _GAMMA_WRITE_TO_LATCH                   1


//----------------------------------------------------------------------------
// customized function

void uncompress(uint8_t pgamma[320] , uint8_t buf[2052]) // 256*10bit to 1024*14bit
{
	uint16_t i, k, decimal;
	uint16_t Now[8];
	uint32_t Start, End;
	uint32_t idx = 0;
	//uint8_t a, b;
	
	decimal = pgamma[0];
	
	Start = ((pgamma[1] << 2) + (pgamma[0] & 0x03)) << 4;//14 bit --0
	
	for (i = 2; i < 319; i++)//1016
	{
		if ((i % 5) == 0)
		{
			decimal = pgamma[i];//0x3f
			i++;
		
		}
	
		End = ((pgamma[i] << 2) + (decimal & 0x03)) << 4;//14 bit  --0x35c0
		decimal >>= 2;//0x0f

		for (k = 0; k < 4; k++)
		{
			Now[k] = (End * k + (4 - k) * Start) >> 2;//14 bit
			//if(i<=50)
			buf[idx] = Now[k] >> 8;
			buf[idx + 1] = Now[k] & 0x00FF;
			//printf("0x%x , 0x%x \r\n", buf[idx], buf[idx + 1]);
			idx=idx+2;
			//printf("now[k]=0x%x\r\n", buf[idx], buf[idx+1]);
		}
		
		Start = End;

		
	}
	
	End = (((pgamma[319] << 2) + (decimal & 0x03)) << 4) + 0x0F;//14 bit
	
	for (k = 0; k < 8; k++)//8 
	{
		Now[k] = (End * k + (8 - k) * Start) >> 3;//14 bit
		buf[idx] = Now[k] >> 8;
		buf[idx + 1] = Now[k] & 0x00FF;

		idx = idx + 2;
	}

	//printf("idx=%d \r\n",idx);
	Now[7] = End;

//	a= buf[2040];
//	b= buf[2041];
	
	buf[2042] = buf[2040];
	buf[2043] = buf[2041];

	buf[2044] = buf[2040];
	buf[2045] = buf[2041];

	buf[2046] =buf[2040];
	buf[2047] =buf[2041];
	
	buf[2048] = buf[2040];
	buf[2049] = buf[2041];

	buf[2050] = 0;
	buf[2051] = 0;



}



static BYTE calucalte_checksum(BYTE *buf , int len)
{

 BYTE i ;
 BYTE crc=0 ;
 
	  
 for(i=0 ; i<len ; i++ ) 
 {
   crc= crc+ buf[i];
 }
 
 return crc ;

}


bit check_checksum(BYTE ucGamma, BYTE* pucGammaTableArray)
{

	  bit ret = _FALSE;
	  BYTE buf_out ;
	  BYTE crc=0;
#if 1
	 switch(ucGamma)
	 {
	    default:
        case 0:
			 UserCommonEepromRead(GAMMA_MODE1_ADDRESS_START, 1, (BYTE *)(&buf_out));
		break;
		case 1:
			 UserCommonEepromRead(GAMMA_MODE2_ADDRESS_START, 1, (BYTE *)(&buf_out));
		break;
		case 2:
			 UserCommonEepromRead(GAMMA_MODE3_ADDRESS_START, 1, (BYTE *)(&buf_out));
		break;
		case 3:
			 UserCommonEepromRead(GAMMA_MODE4_ADDRESS_START, 1, (BYTE *)(&buf_out));
		break;
		case 4:
			 UserCommonEepromRead(GAMMA_MODE5_ADDRESS_START, 1, (BYTE *)(&buf_out));
		break;
		case 5:
			 UserCommonEepromRead(GAMMA_MODE6_ADDRESS_START, 1, (BYTE *)(&buf_out));
		break;
	 }
	 
      crc = calucalte_checksum(pucGammaTableArray, sizeof(pucGammaTableArray));
	
     if(buf_out == crc)
	 	ret= _TRUE;

	 // printf("buf_out = %bd \r\n", buf_out);
#endif	 
	  return ret ;
}


void NewScalerColorOutputGammaAdjust(BYTE ucGamma, BYTE ucBankNum)
{
	
	BYTE pucGammaTableArray[320] ;
	BYTE pgamma[2052] ;


    if(ScalerGetBit(P0_67_GAMMA_CTRL_SETA, _BIT6) == _BIT6) // Gamma On
    {
        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
        ScalerColorOutputGammaEnable(_FUNCTION_OFF);

        // Load gamma table of R Channel
        //----------------------------
        memset(pucGammaTableArray ,0 , sizeof(pucGammaTableArray));
        memset(pgamma ,0 , sizeof(pgamma));
	
        RTDEepromLoadGammaModeData(ucGamma , _GAMMA_RED_CHANNEL ,pucGammaTableArray );
		//--------------------
		if(!check_checksum(ucGamma,pucGammaTableArray)) // checksum fail
	    {
			 UserCommonAdjustGamma(tGAMMA_TABLE[ucGamma - 1], GET_CURRENT_BANK_NUMBER());
			return;
	     }

		
	    uncompress(pucGammaTableArray, pgamma);

		ScalerColorOutputGammaChannelCtrl(_GAMMA_RED_CHANNEL, 0x0000, _GAMMA_WRITE_TO_SRAM);
        ScalerBurstWrite(pgamma, _GAMMA_TABLE_SIZE, ucBankNum, P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

        // Load gamma table of G Channel
        //------------------------------------
        memset(pucGammaTableArray ,0 , sizeof(pucGammaTableArray));
        memset(pgamma ,0 , sizeof(pgamma));
		
        RTDEepromLoadGammaModeData(ucGamma , _GAMMA_GREEN_CHANNEL ,pucGammaTableArray );
		uncompress(pucGammaTableArray, pgamma);
		  
        ScalerColorOutputGammaChannelCtrl(_GAMMA_GREEN_CHANNEL, 0x0000, _GAMMA_WRITE_TO_SRAM);
        ScalerBurstWrite(pgamma + _GAMMA_TABLE_SIZE, _GAMMA_TABLE_SIZE, ucBankNum, P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

        // Load gamma table of B Channel
        //-------------------
        memset(pucGammaTableArray ,0 , sizeof(pucGammaTableArray));
        memset(pgamma ,0 , sizeof(pgamma));

        RTDEepromLoadGammaModeData(ucGamma , _GAMMA_BLUE_CHANNEL ,pucGammaTableArray );
		uncompress(pucGammaTableArray, pgamma);
		  
        ScalerColorOutputGammaChannelCtrl(_GAMMA_BLUE_CHANNEL, 0x0000, _GAMMA_WRITE_TO_SRAM);
        ScalerBurstWrite(pgamma + (_GAMMA_TABLE_SIZE * 2), _GAMMA_TABLE_SIZE, ucBankNum, P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

        // Disable Port Access
        ScalerSetBit(P0_67_GAMMA_CTRL_SETA, ~_BIT7, 0x00);

        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
        ScalerColorOutputGammaEnable(_FUNCTION_ON);
    }
    else
    {
#if 0    
        // Load gamma table of R Channel
        ScalerColorOutputGammaChannelCtrl(_GAMMA_RED_CHANNEL, 0x0000, _GAMMA_WRITE_TO_SRAM);
        ScalerBurstWrite(pucGammaTableArray, _GAMMA_TABLE_SIZE, ucBankNum, P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

        // Load gamma table of G Channel
        ScalerColorOutputGammaChannelCtrl(_GAMMA_GREEN_CHANNEL, 0x0000, _GAMMA_WRITE_TO_SRAM);
        ScalerBurstWrite(pucGammaTableArray + _GAMMA_TABLE_SIZE, _GAMMA_TABLE_SIZE, ucBankNum, P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

        // Load gamma table of B Channel
        ScalerColorOutputGammaChannelCtrl(_GAMMA_BLUE_CHANNEL, 0x0000, _GAMMA_WRITE_TO_SRAM);
        ScalerBurstWrite(pucGammaTableArray + (_GAMMA_TABLE_SIZE * 2), _GAMMA_TABLE_SIZE, ucBankNum, P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
#endif
        // Disable Port Access
        ScalerSetBit(P0_67_GAMMA_CTRL_SETA, ~_BIT7, 0x00);
    }

}




#endif


//--------------------------------------------------
// Description  : Adjust Gamma
// Input Value  : Gamma type
// Output Value : None
//--------------------------------------------------
void UserAdjustGamma(BYTE ucGamma)
{
#if(_OGC_SUPPORT == _ON)
    BYTE ucGammaBankNum = 0;
    WORD usGammaBankAddr = 0;
#endif

    if(ucGamma != _GAMMA_OFF)
    {
#if(_OGC_SUPPORT == _ON)
        ucGammaBankNum = UserCommonAdjustOGCBank(ucGamma - 1, _OGC_NORMAL_BACKLIGHT_TYPE);
        usGammaBankAddr = UserCommonAdjustOGCAddr(ucGamma - 1, _OGC_NORMAL_BACKLIGHT_TYPE);

        UserCommonAdjustGamma(g_pucDISP_CALIBRATION_FLASH + usGammaBankAddr, ucGammaBankNum);

        RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());
        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);

#if(_CONTRAST_SUPPORT == _ON)
        UserAdjustContrast(GET_OSD_CONTRAST());
#endif

#if(_BRIGHTNESS_SUPPORT == _ON)
        UserAdjustBrightness(GET_OSD_BRIGHTNESS());
#endif



#else

#if(_RGB_GAMMA_FUNCTION == _ON)
        ScalerColorRGBOutputGammaEnable(_FUNCTION_OFF);
#endif
      
	
	    NewScalerColorOutputGammaAdjust(ucGamma-1, GET_CURRENT_BANK_NUMBER());
        
        //UserCommonAdjustGamma(tGAMMA_TABLE[ucGamma - 1], GET_CURRENT_BANK_NUMBER());

#if(_RGB_GAMMA_FUNCTION == _ON)
        UserAdjustRGBGamma(ucGamma);
        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
        ScalerColorRGBOutputGammaEnable(_FUNCTION_ON);
#endif

#endif // End of #if(_OGC_SUPPORT == _ON)
    }
}
#endif

#if(_PCM_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Adjust PCM
// Input Value  : ucPCM
// Output Value : None
//--------------------------------------------------
void UserAdjustPCM(BYTE ucPCM)
{
    if(ucPCM != _PCM_OSD_NATIVE)
    {
#if(_OCC_SUPPORT == _ON)
        if(ucPCM == _PCM_OSD_SRGB)
        {
            UserCommonAdjustPCM(_PCM_SRGB, _NULL_POINTER, g_pucDISP_CALIBRATION_FLASH + _OCC_GAMMA10_ADDRESS, g_pucDISP_CALIBRATION_FLASH + _OCC_SRGBMATRIX_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
        }
        else if(ucPCM == _PCM_OSD_ADOBE_RGB)
        {
            UserCommonAdjustPCM(_PCM_ADOBE_RGB, _NULL_POINTER, g_pucDISP_CALIBRATION_FLASH + _OCC_GAMMA10_ADDRESS, g_pucDISP_CALIBRATION_FLASH + _OCC_ADOBEMATRIX_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
        }

#if(_RGB_3D_GAMMA == _ON)
        else if(ucPCM == _PCM_OSD_SOFT_PROFT)
        {
            UserCommonAdjustPCM(_PCM_SOFT_PROFT, _NULL_POINTER, g_pucDISP_CALIBRATION_FLASH + _OCC_GAMMA10_ADDRESS, g_pucDISP_CALIBRATION_FLASH + _OCC_SOFTPROOF_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
        }
#endif // End of #if(_RGB_3D_GAMMA == _ON)

        else
#endif // End of #if(_OCC_SUPPORT == _ON)
        {
            UserCommonAdjustPCM(_PCM_USER_MODE, tPCM_USER_TABLE[(ucPCM - _PCM_OSD_USER) * 3], tPCM_USER_TABLE[((ucPCM - _PCM_OSD_USER) * 3) + 1], tPCM_USER_TABLE[((ucPCM - _PCM_OSD_USER) * 3) + 2], GET_CURRENT_BANK_NUMBER(), _OCC_COLORMATRIX_TABLE_SIZE);
        }
    }
}
#endif  // End of #if(_PCM_FUNCTION == _ON)
#endif // End of #if(_OSD_TYPE == _REALTEK_2014_OSD)
