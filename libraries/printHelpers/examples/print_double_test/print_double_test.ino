//
//    FILE: print_double_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo program SCI
//     URL: https://github.com/RobTillaart/printHelpers
//
//  find the smallest and largest double
//  test e.g. with UNO R4 Wifi as it supports 8 byte double.
//  see - https://forum.arduino.cc/t/ovf-when-multiplying-doubles/1396786


#include "printHelpers.h"

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("PRINTHELPERS_LIB_VERSION: ");
  Serial.println(PRINTHELPERS_LIB_VERSION);
  Serial.println();

  Serial.println(sizeof(float));
  Serial.println(sizeof(double));

  union td
  {
    double d;
    int64_t i;
  } x;

  x.i = 1;
  Serial.println(sci(x.d, 16));
  Serial.println(sci(-x.d, 16));

  x.i = 0xFFEFFFFFFFFFFFFF;
  Serial.println(sci(x.d, 16));
  Serial.println(sci(-x.d, 16));

  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --
