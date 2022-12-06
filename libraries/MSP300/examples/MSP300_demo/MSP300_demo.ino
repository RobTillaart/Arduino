//
//    FILE: MSP300_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: minimal demo pressure transducer
//     URL: https://github.com/RobTillaart/MSP300


#include "MSP300.h"


MSP300 MSP(0x2C);
uint32_t lastTime = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.println();
  Serial.println(MSP300_LIB_VERSION);

  Wire.begin();
  Wire.setClock(400000);

  bool b = MSP.begin(100);
  Serial.println(b ? "true" : "false");
  Serial.println(MSP.isConnected());
}


void loop()
{
  if (millis() - lastTime > 1000)
  {
    lastTime = millis();
    uint32_t x = MSP.readPT();
    Serial.print(x, HEX);
    Serial.print('\t');
    Serial.print(MSP.getPressure(), 3);
    Serial.print('\t');
    Serial.print(MSP.getTemperature(), 3);
    Serial.print('\n');
  }

  delay(100);
}


//  -- END OF FILE --
