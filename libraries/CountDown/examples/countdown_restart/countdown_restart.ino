//
//    FILE: countdown_restart.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo restart
//     URL: https://github.com/RobTillaart/CountDown


#include "CountDown.h"

CountDown cdt;  //  default millis

uint8_t lines = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("COUNTDOWN_LIB_VERSION: ");
  Serial.println(COUNTDOWN_LIB_VERSION);

  cdt.start(10000UL);
}


void loop()
{
  //  time for a new sample
  if (cdt.remaining() == 0)   
  {
    //  restart countDownTimer same values
    cdt.restart();   
    //  make a sample and print it.        
    Serial.print(millis());
    Serial.print("\t");
    Serial.println(analogRead(A0));
  }
}


//  -- END OF FILE --
