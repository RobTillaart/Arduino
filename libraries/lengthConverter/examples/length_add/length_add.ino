//
//    FILE: length_add.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour - simple random converter.
//     URL: https://github.com/RobTillaart/LengthConverter


#include "lengthConverter.h"

lengthConverter LC(0);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("LENGTHCONVERTER_LIB_VERSION: ");
  Serial.println(LENGTHCONVERTER_LIB_VERSION);
  Serial.println();
}


void loop()
{
  float x = -5 + random(10000) * 0.001;
  LC.addMeter(x);
  Serial.print(x, 3);
  Serial.print("\t");
  Serial.println(LC.getInch(), 3);
  delay(1000);
}


//  -- END OF FILE --
