//
//    FILE: HX710A_demo_async.ino
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
  //  start async call
  HX.request();
}


void loop()
{
  if (HX.is_ready())
  {
    int32_t value = HX.fetch(false);
    Serial.print(millis());
    Serial.print("\t VALUE: \t");
    Serial.print(value);
    Serial.println();
    //  next async call
    HX.request();
  }

  //  do other stuff here

}


//  -- END OF FILE --
