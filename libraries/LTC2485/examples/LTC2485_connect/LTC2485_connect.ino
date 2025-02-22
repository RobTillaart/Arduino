//
//    FILE: LTC2485_connect.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: detect device on I2C bus
//     URL: https://github.com/RobTillaart/LTC2485


#include "Wire.h"
#include "LTC2485.h"

LTC2485 LTC(0x14);  //  all address lines GND


void setup()
{
  while(!Serial);
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("LTC2485_LIB_VERSION: ");
  Serial.println(LTC2485_LIB_VERSION);
  Serial.println();

  Wire.begin();
  Wire.setClock(100000);
  LTC.begin();
}


void loop()
{
  while (!LTC.isConnected())
  {
    Serial.println("Could not connect to device");
    delay(2000);
  }

  Serial.print(millis());
  Serial.print("\taddress: ");
  Serial.println(LTC.getAddress());

  delay(2000);
}


//  -- END OF FILE --
