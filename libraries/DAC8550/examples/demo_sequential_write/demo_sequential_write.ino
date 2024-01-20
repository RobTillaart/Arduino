//
//    FILE: demo_sequential_write.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo DAC8550 library Arduino
//     URL: https://github.com/RobTillaart/DAC8550


#include "DAC8550.h"


DAC8550 myDAC(7);


uint32_t lastTime = 0;
uint16_t state = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("DAC8550_LIB_VERSION: ");
  Serial.println(DAC8550_LIB_VERSION);

  SPI.begin();

  myDAC.begin();
}


void loop()
{
  //  square wave - freq 10 Hz
  if (millis() - lastTime > 100)
  {
    lastTime = millis();
    if (state == 0)
    {
      state = 1;
      myDAC.setValue(0);
    }
    else
    {
      state = 0;
      myDAC.setValue(65535);
    }
  }
}

//  -- END OF FILE --
