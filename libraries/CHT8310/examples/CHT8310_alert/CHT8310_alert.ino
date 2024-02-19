//
//    FILE: CHT8310_minimal.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: Demo for CHT8310 I2C humidity & temperature sensor
//     URL: https://github.com/RobTillaart/CHT8310

//  Always check datasheet - front view
//
//          +---------------+
//  VCC ----| VCC           |
//  SDA ----| SDA  CHT8310  |   CHECK DATASHEET.
//  GND ----| GND           |
//  SCL ----| SCL           |
//   ?  ----| AD0           |
//          |               |
//      ----|               |
//          +---------------+
//
//  check datasheet
//  VCC     RED
//  GND     BLACK
//  SDA     YELLOW
//  SCL     WHITE


#include "CHT8310.h"

CHT8310 CHT(0x40);   //  CHT8310_DEFAULT_ADDRESS = 0x40 TODO


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("CHT8310_LIB_VERSION: ");
  Serial.println(CHT8310_LIB_VERSION);
  Serial.println();

  Wire.begin();
  Wire.setClock(100000);
  CHT.begin();

  //  set temperature limits
  CHT.setTemperatureHighLimit(30);
  CHT.setTemperatureLowLimit(15);

  //  set humidity limits
  CHT.setHumidityHighLimit(70);
  CHT.setHumidityLowLimit(40);

  delay(1000);
}


void loop()
{
  if (millis() - CHT.lastRead() >= 1000)
  {
    //  READ DATA
    CHT.read();

    Serial.print(millis());
    Serial.print('\t');
    Serial.print(CHT.getStatusRegister(), HEX);
    Serial.print('\t');
    Serial.print(CHT.getHumidity());
    Serial.print('\t');
    Serial.println(CHT.getTemperature());
  }
}


//  -- END OF FILE --
