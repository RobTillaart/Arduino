//
//    FILE: test_float_decimals.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test decimal point for floats.
//     URL: http://www.adafruit.com/products/1002
//     URL: https://github.com/RobTillaart/HT16K33


#include "HT16K33.h"

HT16K33 seg(0x70);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("HT16K33_LIB_VERSION: ");
  Serial.println(HT16K33_LIB_VERSION);

  Wire.begin();
  Wire.setClock(100000);

  if (! seg.begin())
  {
    Serial.println("not connected");
  }
  seg.displayOn();

  seg.displayFloat(1.945, 3);
  delay(1000);
  seg.displayFloat(1.945, 2);
  delay(1000);
  seg.displayFloat(1.945, 1);
  delay(1000);
  seg.displayFloat(1.945, 0);
  delay(1000);
}


void loop()
{
  test_printfloat();
  Serial.println("---------------");
  delay(1000);
}


void test_printfloat()
{
  uint8_t decimals = 3;
  for (int i = -2000; i < 2000; i++)
  {
    float f = i * 0.001;
    seg.displayFloat(f, decimals);
    delay(2);
  }

  decimals = 2;
  for (int i = -2000; i < 2000; i++)
  {
    float f = i * 0.001;
    seg.displayFloat(f, decimals);
    delay(2);
  }

  decimals = 1;
  for (int i = -2000; i < 2000; i++)
  {
    float f = i * 0.001;
    seg.displayFloat(f, decimals);
    delay(2);
  }

  decimals = 0;
  for (int i = -2000; i < 2000; i++)
  {
    float f = i * 0.001;
    seg.displayFloat(f, decimals);
    delay(2);
  }

}


// -- END OF FILE --

