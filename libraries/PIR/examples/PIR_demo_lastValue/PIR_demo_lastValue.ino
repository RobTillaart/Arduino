//
//    FILE: PIR_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo pir sensor class
//     URL: https://github.com/RobTillaart/PIR


#include "PIR.h"

PIR  P;

void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);
  Serial.print("PIR_LIB_VERSION: ");
  Serial.println(PIR_LIB_VERSION);

  //  add 3 PIR sensors
  P.add(3);
  P.add(4);
  P.add(5);
}


void loop()
{
  uint8_t lastValue = P.lastValue();
  uint8_t newValue = P.read();
  if (newValue != lastValue)          //  change detected?
  {
    Serial.print(millis());
    Serial.print("\t");
    Serial.println(newValue, HEX);
  }
  delay(100);
}


//  -- END OF FILE --
