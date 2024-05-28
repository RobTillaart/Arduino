//
//    FILE: HC4067_write.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: Demo for HC4067 16 channel (simple) multiplexer
//     URL: https://github.com/RobTillaart/HC4067


#include "HC4067.h"

HC4067 mp(4, 5, 6, 7, 3);  //  explicitly set enable pin (3)


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("HC4067 LIBRARY VERSION: ");
  Serial.println(HC4067_LIB_VERSION);
  Serial.println();

  delay(1000);

  pinMode(8, OUTPUT);
  digitalWrite(8, HIGH);

  Serial.println(mp.isEnabled());
  mp.enable();
  Serial.println(mp.isEnabled());
  mp.disable();
  Serial.println(mp.isEnabled());
  mp.enable();
  delay(1000);
}


void loop()
{
  // rotate over the channels
  for (uint8_t channel = 0; channel < 16; channel++)
  {
    mp.setChannel(channel);
    Serial.println(channel);
    delay(250);
  }

  //  Toggle the OUTPUT
  digitalWrite(8, digitalRead(8));
}


//  -- END OF FILE --
