//
//    FILE: KT0803_minimal.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: minimal demo
//     URL: https://github.com/RobTillaart/TinyKT0803


#include "TinyKT0803.h"


TinyKT0803 FM_SEND;


void setup()
{
  //  Tiny only supports SWSerial 
  //  Serial.begin(115200);
  //  while(!Serial);

  TinyWireM.begin();
  //  give I2C time to initialize
  delay(500);

  FM_SEND.begin();
  FM_SEND.setChannel(2000);  // * 0.05 = 100.00 MHz
  FM_SEND.setMute(false);
}

void loop()
{
}


//  -- END OF FILE --
