//
//    FILE: MSP300_fast_pressure.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: fast pressure reading
//     URL: https://github.com/RobTillaart/MSP300
//
//  datasheet states 1 ms refresh time so lets try.

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
  //  try a sample every millisecond
  if (micros() - lastTime >= 1000)
  {
    lastTime = micros();
    MSP.readP();
    Serial.println(MSP.getPressure(), 1);
  }
}


//  -- END OF FILE --
