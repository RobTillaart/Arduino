//
//    FILE: max44009_setContinuousMode.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo of max44009 library
//     URL: https://github.com/RobTillaart/MAX44009
//
//  note that lux values are repeated a number of times
//  if read faster than the integration time.
//  So it makes no sense to call getLux() more than once
//  per integration time.
//  NB the getLux() call takes a bit more than 1 millisecond


#include "Max44009.h"


Max44009 myLux(0x4A);

uint32_t lastDisplay = 0;
uint32_t start = 0;
uint32_t stop = 0;
int count = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MAX44009_LIB_VERSION: ");
  Serial.println(MAX44009_LIB_VERSION);
  Serial.println();

  Wire.begin();

  myLux.setContinuousMode();
}


void loop()
{
  uint32_t interval = 100;
  if (millis() - lastDisplay >= interval)
  {
    lastDisplay += interval;
    count++;
    //  time the measurement
    start = micros();
    float lux = myLux.getLux();
    stop = micros();

    int error = myLux.getError();
    if (error != 0)
    {
      Serial.print("Error:\t");
      Serial.println(error);
    }
    else
    {
      Serial.print("lux:\t");
      Serial.print(lux);
      Serial.print("\ttime:\t");
      Serial.print(stop - start);
      Serial.println();
    }
  }
  if (count == 5) 
  {
    myLux.clrContinuousMode();
  }
  if (count == 10)
  {
    count = 0;
    myLux.setContinuousMode();
  }
}


//  -- END OF FILE --

