#ifndef __UART_H
#define __UART_H

#if(_UART_SUPPORT == _ON)
#include <stdio.h>                /* prototype declarations for I/O functions */	
#define MAX_BUFF_SIZE (100)

struct command {
  char *name;
  void (*function)(char *str);
  char *syntax;
  //char state_needed;
  //char showinfeat;
};

enum
{
   RCV_EMPTY,                              // No data packet
   RCV_READY                               // Data packet received
};

//extern BYTE gB_RcvCount ;
//extern BYTE gB_RcvStatus;

extern void UartHandler(void);
void UserInterfaceUartIntHandler_SERIALPORT(void);


#endif




#endif