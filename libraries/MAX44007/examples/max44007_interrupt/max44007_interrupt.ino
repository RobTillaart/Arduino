//
//    FILE: Max44007_interrupt.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo of Max44007 library
//     URL: https://github.com/RobTillaart/MAX44007


#include "Max44007.h"


Max44007 myLux(0x5A);

uint32_t lastDisplay = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MAX44007_LIB_VERSION: ");
  Serial.println(MAX44007_LIB_VERSION);
  Serial.println();

  Wire.begin();

  myLux.setContinuousMode();

  myLux.setHighThreshold(30);
  Serial.print("HighThreshold:\t");
  Serial.println(myLux.getHighThreshold());

  myLux.setLowThreshold(10);
  Serial.print("LowThreshold:\t");
  Serial.println(myLux.getLowThreshold());

  myLux.setThresholdTimer(2);

  myLux.enableInterrupt();
}


void loop()
{
  uint32_t interval = 1000;
  if (millis() - lastDisplay >= interval)
  {
    lastDisplay += interval;
    float lux = myLux.getLux();
    int error = myLux.getError();
    int status = myLux.getInterruptStatus();
    if (error != 0)
    {
      Serial.print("Error:\t");
      Serial.println(error);
    }
    else
    {
      Serial.print("lux:\t");
      Serial.print(lux);
      if (status == 1) 
      {
        Serial.println("\tIRQ occurred");
      }
      else 
      {
        Serial.println();
      }
    }
  }
}


//  -- END OF FILE --

