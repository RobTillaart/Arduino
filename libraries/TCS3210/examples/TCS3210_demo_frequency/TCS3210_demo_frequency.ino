//
//    FILE: TCS3210_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test TC3210 library
//     URL: https://github.com/RobTillaart/TCS3210

#include "TCS3210.h"

//  S0, S1, S2, S3, OE, data
TCS3210 TCS(3, 4, 5, 6, 7, 8);

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("TCS3210_LIB_VERSION: ");
  Serial.println(TCS3210_LIB_VERSION);
  Serial.println();

  TCS.begin();

}


void loop()
{
  Serial.print(millis());
  Serial.print("\t");

  TCS.selectNone();
  Serial.print(TCS.getFrequency());
  Serial.print("\t");

  TCS.selectRed();
  Serial.print(TCS.getFrequency());
  Serial.print("\t");

  TCS.selectGreen();
  Serial.print(TCS.getFrequency());
  Serial.print("\t");

  TCS.selectBlue();
  Serial.print(TCS.getFrequency());
  Serial.print("\n");
}


//  -- END OF FILE --
