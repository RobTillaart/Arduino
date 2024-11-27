//
//    FILE: TEMT6000_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2024-11-26
//     URL: https://github.com/RobTillaart/TEMT6000


#include "TEMT6000.h"

//  assumes AVR UNO
//  adjust to your boards ADC
TEMT6000 lux(A0, 5, 1023);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("TEMT6000_LIB_VERSION: ");
  Serial.println(TEMT6000_LIB_VERSION);
  Serial.println();

  for (float angle = 0; angle <= 90; angle += 0.2)
  {
    Serial.print(angle);
    Serial.print("\t");
    Serial.print(lux.readRaw());
    Serial.print("\t");
    Serial.println(lux.readLUX(1, angle));
    delay(20);
  }
}


void loop()
{
}


//  -- END OF FILE --
