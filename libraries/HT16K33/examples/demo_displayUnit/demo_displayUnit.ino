//
//    FILE: demo_displayUnit.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
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
  seg.begin();

  seg.displayOn();
  seg.setDigits(4);

  //  default followed by HT16K33_SPACE
  seg.displayUnit(1.23, 0);             //  no unit
  seg.displayUnit(1.23, 1);
  seg.displayUnit(1.23, 2);
  Serial.println();

  //  now followed by HT16K33_A
  seg.displayUnit(1.23, 0, HT16K33_A);  //   Ampere
  seg.displayUnit(1.23, 1, HT16K33_A);
  seg.displayUnit(1.23, 2, HT16K33_A);
  Serial.println();

  seg.displayUnit(-1.23, 0, HT16K33_C);  //  Celsius
  seg.displayUnit(-1.23, 1, HT16K33_C);
  seg.displayUnit(-1.23, 2, HT16K33_C);
  Serial.println();

  seg.displayUnit(12.3, 0, HT16K33_F);   //  Fahrenheit
  seg.displayUnit(12.3, 1, HT16K33_F);
  seg.displayUnit(12.3, 2, HT16K33_F);
  Serial.println();

  seg.displayUnit(12.3, 0, HT16K33_TOP_C);   //  c
  seg.displayUnit(12.3, 1, HT16K33_TOP_C);
  seg.displayUnit(12.3, 2, HT16K33_TOP_C);
  Serial.println();
  
  seg.displayUnit(12.3, 0, HT16K33_DEGREE);   //  °
  seg.displayUnit(12.3, 1, HT16K33_DEGREE);
  seg.displayUnit(12.3, 2, HT16K33_DEGREE);
  Serial.println();
  
  Serial.println("done");

}


void loop()
{
}


// -- END OF FILE --
