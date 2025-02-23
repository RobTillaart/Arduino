//
//    FILE: PCT2075_shutdown.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo PCT2075 temperature sensor
//     URL: https://github.com/RobTillaart/PCT2075
//
//  sensor makes one sample per minute.
//

#include "PCT2075.h"

PCT2075 pct(0x37);

uint32_t lastTime = 0;
float temperature = 0;

void setup()
{
  while (!Serial);
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PCT2075_LIB_VERSION: ");
  Serial.println(PCT2075_LIB_VERSION);
  Serial.println();

  Wire.begin();

  bool b = pct.begin();
  Serial.print("BEGIN:\t");
  Serial.println(b);

  //  go into "sleep" mode
  pct.shutDown();
}


void loop()
{
  if (millis() - lastTime >= 60000)
  {
    lastTime = millis();
    pct.wakeUp();
    delay(29);  //  wait at least 28 milliseconds. (blocking I know)
    temperature = pct.getTemperature();
    Serial.println(temperature);
    pct.shutDown();
  }
  // do other tasks here
  delay(1000);
}



//  -- END OF FILE --
