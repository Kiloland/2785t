#include "UserCommonInclude.h"
#include "uart.h"
#include <string.h>
#include <stdlib.h>
#include "w74m00av.h" 
#if(_UART_SUPPORT == _ON)
///////////////////////////////


// set
void s_help(char *params);
void s_rootkey(char*para);

//void s_power(char *para);
void s_contrast(char *para) ;
void s_brightness(char *para) ;
void s_sharpness(char *para) ;
void s_backlight(char *para) ;
void s_reset(char *para) ;
void s_secureboot(char *para);
void s_pq(char* para);
void s_gamma(char* para);
void s_gdata(char*para);
void s_rotate(char*para);

//void s_colortemp(char *para) ;
//void s_tiling(char*para);
void s_aspect(char*para);
//void s_pattern(char*para);

/*
void s_resetbuffer(char*para);*/
void s_checksum(char*para);


//void g_colorinfo(char*para);
// get
//void g_power(char *para);
void g_contrast(char *para) ;
void g_brightness(char* para);
void g_sharpness(char *para) ;
void g_backlight(char *para) ;
//void g_colortemp(char *para) ;
void g_aspect(char*para);
void g_paneltime(char*para);
void g_nvram(char*para);

#define TEST_ARGS_SPLIT " "

BYTE acRecvBuf[MAX_BUFF_SIZE]={0};
BYTE g_pucUartData[MAX_BUFF_SIZE]={0};
BYTE gB_RcvCount=0 ;  // alant add
BYTE gB_RcvStatus=RCV_EMPTY;
BYTE gB_dummy ;

///////////////////////////////////////
const struct command commands[] = {

  {"s_contrast", s_contrast, "s_contrast 0~100\r\n"},
  {"s_brightness", s_brightness, "s_brightness 0~100\r\n"},
  {"s_sharpness", s_sharpness, "s_sharpness 0~4\r\n"},
    {"s_backlight", s_backlight, "s_backlight 0~100\r\n"},
//  {"s_power",s_power,"s_power 0/1\r\n"} ,
    {"reset",s_reset,"reset:user reset\r\n"} ,
//  {"s_colortemp", s_colortemp, "s_colortemp 0~5\r\n"},
//  {"s_tiling", s_tiling, "s_tiling row column pos\r\n"},
  {"s_aspect", s_aspect, "s_aspect 0~4\r\n"},
//  {"s_pattern", s_pattern, "s_pattern 0/1 r(0~255) g(0~255) b(0~255)\r\n"}, 
    {"s_rootkey", s_rootkey, "s_rootkey " " \r\n"},
	{"s_secureboot", s_secureboot, "s_rootkey \r\n"},
	{"s_pq", s_pq, "s_pq 0~1\r\n"},
	{"s_gamma", s_gamma, "s_gamma 0~6\r\n"},
	{"s_gdata", s_gdata, "s_gdata \r\n"},
	{"s_rotate", s_rotate, "s_rotate angle(0~3) size(0~2)\r\n"},
	{"s_pq", s_pq, "s_pq 0~1\r\n"},
	{"s_gamma", s_gamma, "s_gamma 0~6\r\n"},
//	{"s_s", s_resetbuffer, "s_s \r\n"},
	{"s_crc", s_checksum, "s_crc idx crc	\r\n"},
	{"s_gdata", s_gdata, "s_gdata: \r\n"},

 // {"g_colorinfo", g_colorinfo, "g_colorinfo : colorspace colorrange colorimetry \r\n"},
   
 // {"g_colortemp", g_colortemp, "g_colortemp:get colotemp value\r\n"},
 // {"g_power",g_power,"g_power:get power status\r\n"} ,
  {"g_contrast",g_contrast,"g_contrast:get contrast value\r\n"} ,
  {"g_brightness",g_brightness,"g_brightness:get brightness value\r\n"} ,
  {"g_sharpness", g_sharpness, "g_sharpness:get sharpness value \r\n"},
   {"g_backlight", g_backlight, "g_backlight:get backlight value\r\n"},
  {"g_aspect", g_aspect, "g_aspect:get aspect ratio value\r\n"},
  {"g_paneltime", g_paneltime, "g_paneltime:get panel time (hour min)\r\n"},
	  {"g_nvram", g_nvram, "g_nvram:gamma idx, channel(rgb)\r\n"},

  {"help", s_help,"help:show function\r\n"} ,

   {NULL, NULL, NULL}
	
};


static void sendOK(void){
	printf("OK\r\n");	 


}

static void sendERR(void){ // para error
	printf("ERR\r\n");	 

}
static void sendEmpty(void)
{
	printf("\r\n");	 

}
/*
static void sendUnsupport(void){

    printf("ERR 0\r\n");	 

}*/
#if 0
void g_colorinfo(char*para)
{

	para= NULL;
//   BYTE u32Para;



  printf("%bd %bd %bd \r\n", 
  ScalerColorGetColorSpace(SysRegionGetPortType(GET_OSD_SYSTEM_DISPLAY_REGION())) ,
  ScalerColorGetRGBQuantizationRange(SysRegionGetPortType(GET_OSD_SYSTEM_DISPLAY_REGION())), 
  ScalerColorGetColorimetry(SysRegionGetPortType(GET_OSD_SYSTEM_DISPLAY_REGION()))
);
  // if(u32Para) {
  //    ScalerColorSetRGBLimitRange(SysRegionGetPortType(GET_OSD_SYSTEM_DISPLAY_REGION()), _TRUE);
    //    sendOK(); 
  // 	}
  // else{
 //ScalerColorSetRGBLimitRange(SysRegionGetPortType(GET_OSD_SYSTEM_DISPLAY_REGION()), _FALSE);
   //  sendOK(); 
  // }

}
void s_pattern(char*para)
{
WORD gB_on=0 ,gB_r=0, gB_g=0, gB_b=0 ; 
	
   if(para==NULL) return ;

	sscanf(para,  "%d" TEST_ARGS_SPLIT "%d" TEST_ARGS_SPLIT "%d" TEST_ARGS_SPLIT "%d",			 
	&gB_on ,  &gB_r, &gB_g, &gB_b); // format string

   if(gB_on) {
   
        ScalerDDomainPatternGenAdjustColor(gB_r, gB_g, gB_b);
        ScalerDDomainPatternGenEnable(_ENABLE);
        ScalerDDomainBackgroundEnable( _DISABLE);
        sendOK(); 
   	}
   else{
   ScalerDDomainPatternGenEnable(_DISABLE);
     sendOK(); 
   }

}


#if 0 
void s_tiling(char*para)
{
   
   if(para==NULL) return ;

 
   sscanf(para,  "%d" TEST_ARGS_SPLIT "%d" TEST_ARGS_SPLIT "%d",			
     &gB_hnum, &gB_vnum, &gB_pos); // format string

 // printf("%d %d %d\r\n",gB_hnum,gB_vnum, gB_pos); 
    SET_OSD_ASPECT_RATIO_TYPE(UserAdjustGetSelectRegionPort(), 0); // full mode

    UserAdjustResetDisplayByPort(GET_OSD_SYSTEM_DISPLAY_REGION());


}
#endif

void s_colortemp(char *para) 
{
   WORD u32Para;

    if (para == NULL)
    {
        return;
    }

   u32Para = atoi(para);

   if(u32Para>=0 && u32Para<=5)
    {
           SET_COLOR_TEMP_TYPE( u32Para);
		   RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());
           //RTDNVRamLoadColorSetting(GET_OSD_SELECT_REGION());
           UserAdjustContrast( GET_OSD_CONTRAST());
		  // SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
           sendOK(); 
   }
   else{
  sendERR();

   }


}
void g_colortemp(char *para) 
{
  WORD u32Para;
  para= NULL;
  u32Para = GET_COLOR_TEMP_TYPE();
  printf("%d\r\n" , u32Para);  

}

/*
void g_power(char *para) // power command
{

    para =NULL;
      
   if(SysPowerGetPowerStatus() != _POWER_STATUS_OFF) { 
        printf("1\r\n");                    
       }
   else{

      printf("0\r\n");
   }
    


}
void s_power(char *para) // power command
{

    BYTE u32Para;

    if (para == NULL)
    {
        return;
    }

   u32Para = atoi(para);

    if (0 == u32Para)
    {
       // power off
          if(SysPowerGetPowerStatus() != _POWER_STATUS_OFF) {
                 // power off
              SysPowerSetTargetPowerStatus(_POWER_STATUS_OFF);
              UserCommonEepromSaveSystemData();   
              sendOK(); 

              return ;
                    
           }
    }
    
   if (1 == u32Para)
    {
      //power on
       if(SysPowerGetPowerStatus() == _POWER_STATUS_OFF){
           SET_OSD_STATE(_MENU_NONE);
           SET_OSD_IN_FACTORY_MENU_STATUS(_FALSE);
           SysPowerSetTargetPowerStatus(_POWER_STATUS_NORMAL);
            UserCommonEepromSaveSystemData();
            sendOK(); 
        return ;
       }		
        
    }

   sendERR();   

}
*/


#endif
void g_paneltime(char *para) 
{
 // WORD u32Para;
  para= NULL;
 // u32Para =GET_OSD_ASPECT_RATIO_TYPE(UserAdjustGetSelectRegionPort());
  printf("%d %bd\r\n" , GET_PANEL_TIME_HOUR() , GET_PANEL_TIME_MIN());  

}

void g_aspect(char *para) 
{
//  BYTE u32Para;
  para= NULL;
//  u32Para =GET_OSD_ASPECT_RATIO_TYPE();
  printf("%d\r\n" , GET_OSD_ASPECT_RATIO_TYPE());  

}

void s_aspect(char*para)
{

  BYTE u32Para;

   if (para == NULL)
   {
	   return;
   }

  u32Para = atoi(para);

  if(u32Para>=0 && u32Para<=4)
   {
	  SET_OSD_ASPECT_RATIO_TYPE( u32Para);
	 // UserAdjustResetDisplayByPort(GET_OSD_SYSTEM_DISPLAY_REGION());
	 // SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_INPUTPORTDATA_MSG);
	    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
      sendOK(); 
  }
  else{
 sendERR();

  }


}

void s_rotate(char*para)
{

	BYTE gB_rotate=0 ,gB_size=0 ; 
		
	if(para==NULL) return ;
	
     sscanf(para,  "%d" TEST_ARGS_SPLIT "%d" ,	&gB_rotate ,  &gB_size); // format string
		
     SET_OSD_DISP_ROTATE(gB_rotate); // 0,1,2,3
	 SET_OSD_DISP_ROTATION_SIZE_TYPE(gB_size); // 0,1,2
	 SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
	 SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

    sendOK(); 
}

void g_contrast(char *para) 
{

  BYTE u32Para;
  para= NULL;
  u32Para = UserCommonAdjustRealValueToPercent(GET_OSD_CONTRAST(), _CONTRAST_MAX, _CONTRAST_MIN, _CONTRAST_CENTER);
  printf("%d\r\n" , u32Para);  
 
}

void s_contrast(char *para) 
{

    BYTE u32Para;

    if (para == NULL)
    {
        return;
    }


   u32Para = atoi(para);

   if(u32Para<=100)
   {
    u32Para = UserCommonAdjustPercentToRealValue(u32Para, _CONTRAST_MAX, _CONTRAST_MIN, _CONTRAST_CENTER);
     SET_OSD_CONTRAST(u32Para);
 
     UserAdjustContrast(GET_OSD_CONTRAST());
     UserAdjustBrightness(GET_OSD_BRIGHTNESS());
     SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
      sendOK();	
   }
   else{
	  sendERR();

   }
 
}
void g_brightness(char *para) 
{

  BYTE u32Para;
  para= NULL;
  u32Para = UserCommonAdjustRealValueToPercent(GET_OSD_BRIGHTNESS(), _BRIGHTNESS_MAX, _BRIGHTNESS_MIN, _BRIGHTNESS_CENTER);
  printf("%d\r\n" , u32Para);  
 
}
void s_brightness(char *para) 
{

    BYTE u32Para;

    if (para == NULL)
    {
        return;
    }

  //  printf("\r\n bri value =%s \r\n" , para);
   u32Para = atoi(para);

    // range check
   if( u32Para<=100)
   {
      u32Para = UserCommonAdjustPercentToRealValue(u32Para, _BRIGHTNESS_MAX, _BRIGHTNESS_MIN, _BRIGHTNESS_CENTER);
      SET_OSD_BRIGHTNESS(u32Para);
   //   printf("bri value =%d \r\n" , u32Para);
    // UserAdjustBrightness(GET_OSD_SYSTEM_SELECT_REGION(), u32Para);
      UserAdjustBrightness(GET_OSD_BRIGHTNESS());
      UserAdjustContrast(GET_OSD_CONTRAST());
      SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
        sendOK();	
   }
   else{
   sendERR();	

   }
}
void g_sharpness(char *para) 
{

    BYTE u32Para;

    para=NULL;

    u32Para =GET_OSD_SHARPNESS();
    printf("%d\r\n" , u32Para); 

}
void s_sharpness(char *para) 
{

    BYTE u32Para;

    if (para == NULL)
    {
        return;
    }

   u32Para = atoi(para);
    // range check
   if(u32Para>=0 && u32Para<=4)
   {
	  SET_OSD_SHARPNESS(u32Para);
	   
	  UserCommonAdjustSharpness(SysSourceGetInputPort());
	   SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
      sendOK();

   }
   else
   {
	 sendERR();
   }
}

void s_reset(char *para) 
{
  para =NULL;
  OsdDispOsdReset();
  sendOK();

}
void s_secureboot(char *para)
{

  para =NULL;
#if(_SECURE_BOOT == _ON)     
  secure_boot(0);
#endif
  sendOK();

}
void s_pq(char* para)
{
  BYTE u32Para = atoi(para);

  if(u32Para)
  {
	  ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
	  UserCommonAdjustGammaRegionEnable(_FUNCTION_OFF);
	  

	  ScalerColorSRGBEnable(_FUNCTION_ON);// 3x3 matrix
	  ScalerColorDCCEnable(_FUNCTION_ON);
	  ScalerColorICMEnable(_FUNCTION_ON);

	  if(GET_OSD_GAMMA() != _GAMMA_OFF)
	  {
	    UserAdjustGamma(GET_OSD_GAMMA());
		
	  }
	  
	   ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
	   UserCommonAdjustGammaRegionEnable(_FUNCTION_ON);

  }
  else // pq off
  {
		  ScalerColorSRGBEnable(_FUNCTION_OFF);// 3x3 matrix
		  ScalerColorBrightnessEnable(_FUNCTION_OFF);
		  ScalerColorContrastEnable(_FUNCTION_OFF);
	  
		//  ScalerColorSpaceConvertIDomainEnable(_OFF);
		//  ScalerColorSpaceConvertDDomainEnable(_OFF);
		  ScalerColorDCCEnable(_FUNCTION_OFF);
		  ScalerColorICMEnable(_FUNCTION_OFF);



  }
   sendOK();

}
void s_gamma(char* para)
{
	BYTE u32Para = atoi(para);
	if(u32Para > _GAMMA_AMOUNT){
	  sendERR(); return ;
	  }

	ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
	UserCommonAdjustGammaRegionEnable(_FUNCTION_OFF);

    
    if(u32Para <= _GAMMA_AMOUNT)
    {
        UserAdjustGamma(u32Para);
        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
        UserCommonAdjustGammaRegionEnable(_FUNCTION_ON);
		SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
    }	

	sendOK();


}
void s_gdata(char*para)
{

  BYTE idx , i=0;
  BYTE channel;
  BYTE gidx =0 ;
  BYTE buf_in[80];
  //------------------
  idx= para[0]-0x30;
  channel = para[1]-0x30;
  gidx = para[2]-0x30;
 
  //---------------------------
  for(i=0; i<80 ;i++)
  {
	  buf_in[i] = para[3+i];

  }
  // trasmit gdata completely
  // save gamma data to eeprom directly
 RTDNVRamSaveGammaModeData(idx,  channel ,  gidx , sizeof(buf_in) , buf_in);

 sendOK();

}

void g_backlight(char *para) 
{

  BYTE u32Para;
  para= NULL;
  u32Para = UserCommonAdjustRealValueToPercent(GET_OSD_BACKLIGHT(), _BACKLIGHT_MAX, _BACKLIGHT_MIN, _BACKLIGHT_CENTER);
  printf("%d\r\n" , u32Para);  
 
}
void s_backlight(char *para) 
{

    BYTE u32Para;

    if (para == NULL)
    {
        return;
    }

   u32Para = atoi(para);
    // range check
   if(u32Para>=0 && u32Para<=100)
   {
	   u32Para = UserCommonAdjustPercentToRealValue(u32Para, _BACKLIGHT_MAX, _BACKLIGHT_MIN, _BACKLIGHT_CENTER);
	   SET_OSD_BACKLIGHT(u32Para);
       UserAdjustBacklight(GET_OSD_BACKLIGHT());
	   SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

     sendOK();
   }
     else{

	   sendERR();

   }
}

void s_rootkey(char*para)
{

   //WORD u32Para;
   para = NULL;
#if(_SECURE_BOOT == _ON)   
   WB_RPMC_WrRootKey(0,"WINDBOND");
#endif
   sendOK(); 

}
void g_nvram(char *para) 
{
   BYTE para1 ;
   BYTE para2 ;
   int i;
   BYTE buf[320]; 

 // sscanf(para,  "%d" TEST_ARGS_SPLIT "%d" ,&para1, &para2); // format string
  para1 = para[0]-0x30 ;
  // para[1] = 0x20
  para2 = para[2] - 0x30 ;

  //printf("%bd %bd\r\n" , para1, para2);  

  RTDNVRamLoadGammaModeData(para1,para2,buf);

  for (i = 0; i < 320; i += 8)
  {
 	printf("%b02x,%b02x,%b02x,%b02x,%b02x,%b02x,%b02x,%b02x \r\n", buf[i], buf[i + 1], buf[i + 2], buf[i + 3], buf[i+4], buf[i + 5], buf[i + 6], buf[i + 7]);
  }

}
/*
void s_resetbuffer(char*para)
{
   
   para= NULL;
   sendOK(); 
}*/
void s_checksum(char*para)
{

   BYTE crc=0 ;
   int i =0 ,k=0;
   BYTE buf[320];
   para= NULL;
  for(k=0 ; k<6 ;k++)
  { 
     crc= 0;
	 memset(buf , 0 , 320);
	 
     RTDNVRamLoadGammaModeData(k,0,buf);
   
	 for (i = 0; i < 320; i ++)
	 {
		crc+= buf[i];
	 }
	// printf("crc = %bX\r\n", crc);
	
    RTDEepromSaveGammaCRC(k,&crc);
  }



}

void s_help(char *params)
{
	int i;
	//char acBuf[64]={0};
	params=NULL;
   // printf("support command list\r\n");

	for (i = 0; commands[i].name; i++)
	{

		printf("%s",commands[i].syntax);

	}
}
	

char putchar(char c)  
{

 return ScalerMcuUartWrite((BYTE)c);
}

static void cutto(char *str, int len , int buf_size)
{
	int size;// = -len + 1;

	size = buf_size - len + 1;
	memmove(str, str + len,  size);
	memset(str+size-1 , '\0' , len);

}
static char* trimgarbage(char*str)
{
	char *p;  /* strlen("ALLOWCOMMAND_XXXX") + 1 == 18 */
	p = str;			/* Remove garbage in the string */
	
	while (*p)
	{
		if ((unsigned char) *p <= 32 || (unsigned char) *p ==0x7F) p++;
		else{
			break;
		}
	}	

    return p;
}

static void remove_trim(char*str , int buf_size)
{
	char* p;
	int size;
	p = str;


	while (((*p == ' ') || (*p == '\t')))//while ((*p) && ((*p == ' ') || (*p == '\t')))
	{
		p++;
	}
	size = buf_size - (p - str) + 1;
//	memmove(str, p, strlen(str) - (p - str) + 1);
	memmove(str, p, size);
	memset(str + (size - 1), '\0', (p - str));

}
static bit  parsecmd(char *str)
{
	int i;
//	char*p;
	
	str=trimgarbage(str);
	//str = strtok(str,"\r\n");
	
	for (i = 0; commands[i].name; i++) 
       {	/* Parse command */
		if (!strncmp(str, commands[i].name, strlen(commands[i].name))) 
		{
                   
			cutto(str, strlen(commands[i].name),MAX_BUFF_SIZE);
			remove_trim(str,MAX_BUFF_SIZE);
			commands[i].function(str); // pass parameter to command
			return _TRUE ;
			
		}
		else // handle unsupported command
		{

		}
	}
		
   if(!strlen(str))
    { 
      // handle enter key only
      sendEmpty();
      return _TRUE ;
    }  	
  
  return _FALSE ;

}


static void StopRcvMsg(void)
{
   gB_RcvStatus = RCV_READY;						// stop receiving messages

}


static void StartRcvMsg(void)
{
   gB_RcvStatus = RCV_EMPTY;						// start receiving messages

}
/*
static bit is_uartbuf_ready(BYTE* buf , BYTE buf_len)
{
 bit ret = _FALSE;
 int count ;
 // WORD usPresentTime = g_usTimerCounter;
 
 if((buf_len > 1) && buf[buf_len-1] == '\n' && buf[buf_len-1] == '\r')
 {
   ret = _TRUE;
 
 }
  return ret ; 
}
*/
static bit is_uart_message_complete(void)
{
  return gB_RcvStatus;

}
void UserInterfaceUartIntHandler_SERIALPORT(void)
{

 
  if(RI)
  {
	if ((gB_RcvStatus == RCV_EMPTY) &&	   // Packet not received yet
		 (gB_RcvCount < MAX_BUFF_SIZE))	 // Buffer not ful
	{									   
		g_pucUartData[gB_RcvCount] = SBUF;// Get data from UART
        
		gB_RcvCount++;


       if((gB_RcvCount > 1) && g_pucUartData[gB_RcvCount-1] == '\n' && g_pucUartData[gB_RcvCount-2] == '\r')  // if(is_uartbuf_ready(g_pucUartData,gB_RcvCount))
	   {
            StopRcvMsg();
            memcpy(acRecvBuf, g_pucUartData, gB_RcvCount);
            memset(g_pucUartData , 0 ,MAX_BUFF_SIZE);
		    gB_RcvCount =0 ;			

	    }
		

        if ((gB_RcvCount % MAX_BUFF_SIZE) ==0) 
		{
            gB_RcvCount =0 ;
        }

	}
	else
	{
		gB_dummy = SBUF; // clear the buffer

	}
	
    RI =0 ;
    
  }

}
void UartHandler(void)
{
     UserInterfaceUartIntHandler_SERIALPORT();

    if(is_uart_message_complete())
    { 
 
       if(!parsecmd(acRecvBuf))// parse command
       {
            sendERR();
       }

	   memset(acRecvBuf , 0 ,MAX_BUFF_SIZE);
       StartRcvMsg();
    }	

 
}
#endif // end uart
