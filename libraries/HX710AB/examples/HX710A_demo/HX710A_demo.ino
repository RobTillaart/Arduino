//
//    FILE: HX710A_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/HX710AB


#include "HX710AB.h"

//  adjust pins to your setup
uint8_t dataPin = 6;
uint8_t clockPin = 7;

HX710A HX(dataPin, clockPin);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("HX710AB_LIB_VERSION: ");
  Serial.println(HX710AB_LIB_VERSION);
  Serial.println();

  HX.begin();
}


void loop()
{
  int32_t value = HX.read(false);
  Serial.print("VALUE: \t");
  Serial.print(value);
  Serial.println();
  delay(1000);
  
  value = HX.read(true);
  Serial.print("TEMP: \t");
  Serial.print(value);
  Serial.println();
  delay(1000);
}


//  -- END OF FILE --
