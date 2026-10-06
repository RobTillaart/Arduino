//    FILE: print_fixedLength.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test printing with fixed space for float
//     URL: https://github.com/RobTillaart/printHelpers

#include "printHelpers.h"

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);

  //  test length errors
  Serial.println(fixedLength(PI, 56));
  Serial.println(fixedLength(PI, 56, false));

  //  test values
  Serial.println(fixedLength(PI, 6));
  Serial.println(fixedLength(PI, 6, false));
  Serial.println(fixedLength(-PI, 6));
  Serial.println(fixedLength(-PI, 6, false));
  Serial.println(fixedLength(12345.6f, 6));
  Serial.println(fixedLength(12345.6f, 6, false));
  Serial.println(fixedLength(123456.5f, 6));
  Serial.println(fixedLength(123456.5f, 6, false));
  Serial.println(fixedLength(123.0f, 6));
  Serial.println(fixedLength(123.0f, 6, false));
  Serial.println(fixedLength(EULER, 9));
  Serial.println(fixedLength(EULER, 9, false));
  Serial.println();

  //  test rounding
  Serial.println(fixedLength(1.23456, 6));
  Serial.println(fixedLength(1.23456, 6, false));
  Serial.println();

  //  test overflow
  Serial.println(fixedLength(1e6, 6));
  Serial.println(fixedLength(-1e6, 6, false));
  Serial.println(fixedLength(4294967295.0f, 8, false));
  Serial.println(4294967295.0f, 2);
  Serial.println();
  Serial.println(fixedLength(99999995.0f, 8, false));
  Serial.println(fixedLength(99999999.0f, 8, false));
  Serial.println(99999999.0f, 2);
  Serial.println();

  delay(1000);
  start = micros();
  char *p = fixedLength(1.23456, 6);
  stop = micros();
  Serial.print("TIME:\t");
  Serial.println(stop - start);
  Serial.println(p);

  delay(1000);
  start = micros();
  p = fixedLength(1.23456, 6, false);
  stop = micros();
  Serial.print("TIME:\t");
  Serial.println(stop - start);
  Serial.println(p);

  delay(1000);
  start = micros();
  p = fixedLength(12345.6, 6);
  stop = micros();
  Serial.print("TIME:\t");
  Serial.println(stop - start);
  Serial.println(p);

  delay(1000);
  start = micros();
  p = fixedLength(12345.6, 6, false);
  stop = micros();
  Serial.print("TIME:\t");
  Serial.println(stop - start);
  Serial.println(p);

  Serial.println("\ndone...");
}

void loop()
{
}


//  -- END OF FILE --
