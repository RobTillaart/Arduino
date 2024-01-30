//
//    FILE: MAX471_demo
//  AUTHOR: Rob Tillaart
// PURPOSE: demo MAX471
//     URL: https://github.com/RobTillaart/MAX471_RT


#include "MAX471.h"

MAX471 mx(A0, A1);

uint32_t lastTime = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("MAX471_LIB_VERSION: ");
  Serial.println(MAX471_LIB_VERSION);

  mx.begin(5.0, 1023);
}


void loop()
{
  if (millis() - lastTime >= 1000)
  {
    lastTime = millis();
    Serial.print(mx.readCurrent());
    Serial.print("\t");
    Serial.print(mx.readVoltage());
    Serial.print("\t");
    Serial.print(mx.calcPower());
    Serial.print("\n");
  }
}


//  -- END OF FILE --
