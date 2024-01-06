//
//    FILE: TM1637_pchar.ino
//  AUTHOR: Richard Jones
// PURPOSE: demo TM1637 library
//    DATE: 4 October 2022
//     URL: https://github.com/radionerd

//  Demonstration of how to display char *buff
//  Status: Experimental. Tested on STM32F103C8T6 Blue Pill and Arduino Nano only


#include "TM1637.h"

const int DISPLAY_DIGITS_6 = 6;

TM1637 TM;


void setup()
{
  Serial.begin(115200);
  delay(1000);
  Serial.println(__FILE__);

  //  set clock pin, data pin to your own board pin names
  //  e.g.  myTM.begin(PB8, PB9 , DISPLAY_DIGITS_6 );
  TM.begin( 14, 15 , DISPLAY_DIGITS_6 );  //  clock pin, data pin, and digits

  TM.setBrightness(2);
  
}


void loop()
{
  char buff[20];
  static int seconds;
  sprintf(buff,"Sec=%02x", seconds++&0xFF );
  TM.displayPChar(buff);  //  send buffer to display
  Serial.println(buff);   //       and serial port.
  delay(1000);
}


//  -- END OF FILE --
