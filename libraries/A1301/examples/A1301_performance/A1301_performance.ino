//
//    FILE: A1301_performance
//  AUTHOR: Rob Tillaart
// PURPOSE: demo A1301 A1302 magnetometer.
//     URL: https://github.com/RobTillaart/A1301


#include "A1301.h"

A1301 mm(A0);

volatile float x;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("A1301_LIB_VERSION: ");
  Serial.println(A1301_LIB_VERSION);
  delay(100);

  mm.begin(5000, 1023);

  uint32_t start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x = mm.read();
  }
  uint32_t stop = micros();
  Serial.print("read():\t");
  Serial.print((stop - start) * 0.001);
  Serial.println(" us.");

}


void loop()
{
}


//  -- END OF FILE --
