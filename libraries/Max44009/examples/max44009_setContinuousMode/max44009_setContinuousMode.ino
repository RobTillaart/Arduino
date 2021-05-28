//
//    FILE: max44009_setContinuousMode.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo of max44009 library
//    DATE: 2020-01-30
//
// Released to the public domain
//

// note that lux values are repeated a number of times
// if read faster than the integration time.
// So it makes no sense to call getLux() more than once
// per integration time.
// NB the getLux() call takes a bit more than 1 millisecond


#include "Wire.h"
#include "Max44009.h"

Max44009 myLux(0x4A);

uint32_t lastDisplay = 0;
uint32_t start = 0;
uint32_t stop = 0;
int count = 0;


void setup()
{
  Serial.begin(115200);
  Serial.print("\nStart max44009_setContinuousMode : ");
  Serial.println(MAX44009_LIB_VERSION);

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
    start = micros();
    float lux = myLux.getLux();
    stop = micros();
    int err = myLux.getError();
    if (err != 0)
    {
      Serial.print("Error:\t");
      Serial.println(err);
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
  if (count == 5) myLux.clrContinuousMode();
  if (count == 10)
  {
    count = 0;
    myLux.setContinuousMode();
  }
}


// -- END OF FILE --
