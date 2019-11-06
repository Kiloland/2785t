#include "UserCommonInclude.h"
#include "uart.h"
#include <stdio.h>                /* prototype declarations for I/O functions */
#include <string.h>
#include <stdlib.h>
#include "w74m00av.h" 
#if(_UART_SUPPORT == _ON)
///////////////////////////////


// set
void s_help(char *params);
void s_rootkey(char*para);

//void s_power(char *para);
//void s_contrast(char *para) ;
//void s_brightness(char *para) ;
//void s_sharpness(char *para) ;
void s_backlight(char *para) ;
void s_reset(char *para) ;

//void s_colortemp(char *para) ;
//void s_tiling(char*para);
//void s_aspect(char*para);
//void s_pattern(char*para);


//void g_colorinfo(char*para);
// get
//void g_power(char *para);
//void g_contrast(char *para) ;
//void g_brightness(char* para);
//void g_sharpness(char *para) ;
void g_backlight(char *para) ;
//void g_colortemp(char *para) ;
//void g_aspect(char*para);
//void g_paneltime(char*para);

BYTE acRecvBuf[MAX_BUFF_SIZE]={0};
BYTE g_pucUartData[MAX_BUFF_SIZE]={0};
BYTE gB_RcvCount=0 ;  // alant add
BYTE gB_RcvStatus=RCV_EMPTY;
BYTE gB_dummy ;

///////////////////////////////////////
const struct command commands[] = {

//  {"s_contrast", s_contrast, "s_contrast 0~100\r\n"},
//  {"s_brightness", s_brightness, "s_brightness 0~100\r\n"},
//  {"s_sharpness", s_sharpness, "s_sharpness 0~4\r\n"},
    {"s_backlight", s_backlight, "s_backlight 0~100\r\n"},
//  {"s_power",s_power,"s_power 0/1\r\n"} ,
    {"reset",s_reset,"reset:user reset\r\n"} ,
//  {"s_colortemp", s_colortemp, "s_colortemp 0~5\r\n"},
//  {"s_tiling", s_tiling, "s_tiling row column pos\r\n"},
//  {"s_aspect", s_aspect, "s_aspect 0~4\r\n"},
//  {"s_pattern", s_pattern, "s_pattern 0/1 r(0~255) g(0~255) b(0~255)\r\n"}, 
    {"s_rootkey", s_rootkey, "s_rootkey \r\n"},

 // {"g_colorinfo", g_colorinfo, "g_colorinfo : colorspace colorrange colorimetry \r\n"},
   
 // {"g_colortemp", g_colortemp, "g_colortemp:get colotemp value\r\n"},
 // {"g_power",g_power,"g_power:get power status\r\n"} ,
 // {"g_contrast",g_contrast,"g_contrast:get contrast value\r\n"} ,
 // {"g_brightness",g_brightness,"g_brightness:get brightness value\r\n"} ,
 // {"g_sharpness", g_sharpness, "g_sharpness:get sharpness value \r\n"},
   {"g_backlight", g_backlight, "g_backlight:get backlight value\r\n"},
 // {"g_aspect", g_aspect, "g_aspect:get aspect ratio value\r\n"},
 // {"g_paneltime", g_paneltime, "g_paneltime:get panel time (hour min)\r\n"},

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
void g_paneltime(char *para) 
{
 // WORD u32Para;
  para= NULL;
 // u32Para =GET_OSD_ASPECT_RATIO_TYPE(UserAdjustGetSelectRegionPort());
  printf("%d %bd\r\n" , GET_PANEL_TIME_HOUR() , GET_PANEL_TIME_MIN());  

}
void g_aspect(char *para) 
{
  WORD u32Para;
  para= NULL;
  u32Para =GET_OSD_ASPECT_RATIO_TYPE();
  printf("%d\r\n" , u32Para);  

}

void s_aspect(char*para)
{

  WORD u32Para;

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
void s_reset(char *para) 
{
  para =NULL;
  OsdDispOsdReset();
  sendOK();

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
void g_contrast(char *para) 
{

  WORD u32Para;
  para= NULL;
  u32Para = UserCommonAdjustRealValueToPercent(GET_OSD_CONTRAST(), _CONTRAST_MAX, _CONTRAST_MIN, _CONTRAST_CENTER);
  printf("%d\r\n" , u32Para);  
 
}

void s_contrast(char *para) 
{

    WORD u32Para;

    if (para == NULL)
    {
        return;
    }
#if 1	
//printf("\r\n con value =%s \r\n" , para);
   u32Para = atoi(para);
//printf("b : contrast value =%d \r\n" , u32Para);
   // range check

   if(u32Para>=0 && u32Para<=100)
   {
    u32Para = UserCommonAdjustPercentToRealValue(u32Para, _CONTRAST_MAX, _CONTRAST_MIN, _CONTRAST_CENTER);
     SET_OSD_CONTRAST(u32Para);
   //  printf("a : contrast value =%d \r\n" , u32Para);
    // UserAdjustContrast(GET_OSD_SYSTEM _SELECT_REGION(), u32Para);
     UserAdjustContrast(GET_OSD_CONTRAST());
       UserAdjustBrightness(GET_OSD_BRIGHTNESS());
     //SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
      sendOK();	
   }
   else{
	  sendERR();

   }
 #endif  
}
void g_brightness(char *para) 
{

  WORD u32Para;
  para= NULL;
  u32Para = UserCommonAdjustRealValueToPercent(GET_OSD_BRIGHTNESS(), _BRIGHTNESS_MAX, _BRIGHTNESS_MIN, _BRIGHTNESS_CENTER);
  printf("%d\r\n" , u32Para);  
 
}
void s_brightness(char *para) 
{

    WORD u32Para;

    if (para == NULL)
    {
        return;
    }

  //  printf("\r\n bri value =%s \r\n" , para);
   u32Para = atoi(para);

    // range check
   if(u32Para>=0 && u32Para<=100)
   {
      u32Para = UserCommonAdjustPercentToRealValue(u32Para, _BRIGHTNESS_MAX, _BRIGHTNESS_MIN, _BRIGHTNESS_CENTER);
      SET_OSD_BRIGHTNESS(u32Para);
   //   printf("bri value =%d \r\n" , u32Para);
    // UserAdjustBrightness(GET_OSD_SYSTEM_SELECT_REGION(), u32Para);
      UserAdjustBrightness(GET_OSD_BRIGHTNESS());
      UserAdjustContrast(GET_OSD_CONTRAST());
     // SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
        sendOK();	
   }
   else{
   sendERR();	

   }
}
void g_sharpness(char *para) 
{

    WORD u32Para;

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
	   //SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_INPUTPORTDATA_MSG);
      sendOK();

   }
   else{

	 sendERR();

   }
}

#endif
void s_reset(char *para) 
{
  para =NULL;
  OsdDispOsdReset();
  sendOK();

}

void g_backlight(char *para) 
{

  WORD u32Para;
  para= NULL;
  u32Para = UserCommonAdjustRealValueToPercent(GET_OSD_BACKLIGHT(), _BACKLIGHT_MAX, _BACKLIGHT_MIN, _BACKLIGHT_CENTER);
  printf("%d\r\n" , u32Para);  
 
}
void s_backlight(char *para) 
{

    WORD u32Para;

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

void s_help(char *params)
{
	int i;
	//char acBuf[64]={0};
	params=NULL;
   // printf("support command list\r\n");

	for (i = 0; commands[i].name; i++){

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
			// gB_RcvStatus = RCV_READY;	
	       // gB_RcvComplete =1 ;
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