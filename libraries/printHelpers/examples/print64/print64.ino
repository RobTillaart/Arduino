//
//    FILE: print64.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo print 64 bit integers
//     URL: https://github.com/RobTillaart/printHelpers


#include "printHelpers.h"


uint64_t llx = 1311768467284833366;
int64_t  lly = 0xFFFFFFFFFFFFFFFF;
uint64_t a = 0;

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PRINTHELPERS_VERSION: ");
  Serial.println(PRINTHELPERS_VERSION);
  Serial.println();

  delay(100);

  Serial.println("BASE\tTIME  base < 10 support depends on internal buffer size");
  for (uint8_t base = 2; base < 37; base++)
  {
    start = micros();
    print64(llx, base);
    stop = micros();
    Serial.print(base);
    Serial.print("\t");
    Serial.print(stop - start);
    Serial.println();
    delay(10);
  }

  Serial.println("\nsome numbers");
  Serial.println("--------------");
  Serial.println(print64(llx));
  Serial.println(print64(a));
  Serial.println(print64(llx, HEX));
  Serial.println(print64(llx, 2));
  Serial.println(print64(llx, 36));
  Serial.println(print64(0xFFFFFFFFFFFFFFFF, 2));
  Serial.println(print64(0xFFFFFFFFFFFFFFFF, 10));
  Serial.println(print64(lly));

  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --

