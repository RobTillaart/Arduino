//
//    FILE: HTU21_getHumidityCompensated.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/SHT2x


#include "Wire.h"
#include "SHT2x.h"

HTU21 sht;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("SHT2x_LIB_VERSION: \t");
  Serial.println(SHT2x_LIB_VERSION);
  Serial.println();

  Wire.begin();
  sht.begin();

  uint8_t stat = sht.getStatus();
  Serial.print(stat, HEX);
  Serial.println();
}


void loop()
{
  sht.read();

  Serial.print(sht.getTemperature(), 1);
  Serial.print("\t");
  Serial.print(sht.getHumidity(), 1);
  Serial.print("\t");
  Serial.println(sht.getHumidityCompensated(), 1);
  delay(1000);
}


//  -- END OF FILE --
