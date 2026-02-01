//
//    FILE: RunningMinMax.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo basic usage
//     URL: https://github.com/RobTillaart/RunningMinMax


#include "RunningMinMax.h"


RunningMinMax samples = RunningMinMax(5);


void setup()
{
  while (!Serial);  //  Wait for serial port to connect. Needed for Leonardo + MKR1010.
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print(F("RUNNING_MINMAX_LIB_VERSION: "));
  Serial.println(RUNNING_MINMAX_LIB_VERSION);
  Serial.println();
}


void loop()
{
  test1();
}


void test1()
{
  uint16_t x = analogRead(A0);

  samples.add(x);
  uint16_t l = samples.getMinimum();
  uint16_t a = samples.getAverage();
  uint16_t h = samples.getMaximum();

//  Serial.print(millis());
//  Serial.print("\t");
  Serial.print(x);
  Serial.print("\t");
  Serial.print(l);
  Serial.print("\t");
  Serial.print(a);
  Serial.print("\t");
  Serial.println(h);
  delay(100);
}


//  -- END OF FILE --
