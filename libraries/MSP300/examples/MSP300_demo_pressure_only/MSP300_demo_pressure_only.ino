//
//    FILE: MSP300_demo_pressure_only.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: minimal demo pressure only
//     URL: https://github.com/RobTillaart/MSP300


#include "MSP300.h"


MSP300 MSP(0x28);
uint32_t lastTime = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.println();
  Serial.println("MSP300_LIB_VERSION: ");
  Serial.println(MSP300_LIB_VERSION);
  Serial.println();

  Wire.begin();
  Wire.setClock(400000);

  bool b = MSP.begin(100);
  Serial.println(b ? "true" : "false");
  Serial.println(MSP.isConnected());
  Serial.println();
}


void loop()
{
  if (millis() - lastTime > 1000)
  {
    lastTime = millis();
    uint32_t x = MSP.readP();
    Serial.print(x, HEX);
    Serial.print('\t');
    Serial.print(MSP.getStatus());
    Serial.print('\t');
    Serial.print(MSP.getPressure(), 3);
    Serial.print('\n');
  }

  delay(100);
}


//  -- END OF FILE --
