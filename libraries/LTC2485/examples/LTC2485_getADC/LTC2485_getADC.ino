//
//    FILE: LTC2485_getADC.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: minimal test
//     URL: https://github.com/RobTillaart/LTC2485


#include "Wire.h"
#include "LTC2485.h"


//  adjust address if needed
//  0x14  CA1 = LOW  CA0 = HIGH
LTC2485 LTC(0x16);

float VREF = 1.8;


void setup()
{
  while(!Serial);
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print(F("LTC2485_LIB_VERSION: "));
  Serial.println(LTC2485_LIB_VERSION);
  Serial.println();

  Wire.begin();
  Wire.setClock(100000);

  LTC.begin(VREF);
  delay(200);
}


void loop()
{
  while (!LTC.isConnected())
  {
    Serial.print("Could not connect to device ");
    Serial.println(LTC.getAddress());
    delay(2000);
  }
  Serial.print(millis());
  Serial.print("\tADC: ");
  Serial.println(LTC.getADC());
  Serial.println();

  delay(2000);
}


//  -- END OF FILE --
