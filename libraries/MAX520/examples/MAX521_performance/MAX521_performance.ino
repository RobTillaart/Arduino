//
//    FILE: MAX521_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo MAX521
//     URL: https://github.com/RobTillaart/MAX520


#include "MAX520.h"

//  adjust address if needed
//  MAX520 0x20..0x27
//  MAX521 0x20..0x23
MAX521 mx(0x20);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MAX520_LIB_VERSION:\t");
  Serial.println(MAX520_LIB_VERSION);
  Serial.println();

  Wire.begin();

  mx.begin();

  Serial.println("Clock\tTime (us)");
  for (uint32_t speed = 50000; speed <= 500000; speed += 50000)
  {
    test_1(speed);
  }
  Wire.setClock(100000);
  Serial.println("\done");
}


void loop()
{
}

void test_1(uint32_t speed)
{
  //  wait to flush Serial
  delay(100);

  Wire.setClock(speed);
  uint32_t start = micros();
  for (int value = 0; value < 256; value++)
  {
    mx.write(0, value);
  }
  uint32_t stop = micros();

  Serial.print("Write(ch, value)");
  Serial.print("\t");
  Serial.print(speed);
  Serial.print("\t");
  Serial.print((stop - start) / 256.0, 2);
  Serial.print("\n");
  delay(100);

  uint8_t values[8] = { 0, 42, 85, 127, 170, 212, 255 };
  start = micros();
  for (int value = 0; value < 10; value++)
  {
    mx.write(values);
  }
  stop = micros();

  Serial.print("Write(values)");
  Serial.print("\t");
  Serial.print(speed);
  Serial.print("\t");
  Serial.print((stop - start) / 10.0, 2);
  Serial.print("\n");
  delay(100);
}


//  -- END OF FILE --
