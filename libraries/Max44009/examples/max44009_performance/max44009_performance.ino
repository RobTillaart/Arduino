//
//    FILE: max44009_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo of max44009 library
//     URL: https://github.com/RobTillaart/MAX44009
//
//  This measurement is indicative for the I2C speed
//  It might be affected by the intensity.


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

  for (uint32_t clock = 100000; clock <= 800000; clock += 100000)
  {
    delay(1000);  //  wait for new measurement.
    test(clock);
  }
}


void test(uint32_t clock)
{
  Wire.setClock(clock);
  //  time the measurement
  start = micros();
  float lux = myLux.getLux();
  stop = micros();
  //  print results.
  Serial.print(clock);
  Serial.print("\t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(lux);
  Serial.println();
}


void loop()
{
}


//  -- END OF FILE --
