//
//    FILE: AD7367_fastRead_array.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: performance fastRead()
//     URL: https://github.com/RobTillaart/AD7367
//
//  not tested with hardware yet

#include "AD7367.h"

//  select, clock, convert, busy, data0, data1
//  adjust pins if needed
AD7367 AD(5, 6, 7, 8, 9, 10);

//  100 samples for 2 channels.
int left[100];
int right[100];

uint32_t start, stop;

void setup()
{
  while (!Serial);
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print(F("AD7367_LIB_VERSION: "));
  Serial.println(AD7367_LIB_VERSION);
  Serial.println();

  AD.begin();

  delay(100);
  start = micros();
  for (int i = 0; i < 100; i++)
  {
    AD.fastRead(left[i], right[i]);
  }
  stop = micros();
  for (int i = 0; i < 100; i++)
  {
    Serial.print(left[i]);
    Serial.print("\t");
    Serial.print(right[i]);
    Serial.println();
  }
  Serial.print("TIME: ");
  Serial.println(stop - start);
}


void loop()
{
}


//  -- END OF FILE --
