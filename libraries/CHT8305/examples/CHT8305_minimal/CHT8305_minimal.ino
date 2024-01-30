//
//    FILE: CHT8305_minimal.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: Demo for CHT8305 I2C humidity & temperature sensor
//     URL: https://github.com/RobTillaart/CHT8305

//  Always check datasheet - front view
//
//          +---------------+
//  VCC ----| VCC           |
//  SDA ----| SDA  CHT8305  |   CHECK DATASHEET.
//  GND ----| GND           |
//  SCL ----| SCL           |
//   ?  ----| AD0           |   ? depends on address to select
//          |               |
//  IRQ ----| ALERT         |   only if enabled.
//          +---------------+
//
//  check datasheet
//  VCC     RED
//  GND     BLACK
//  SDA     YELLOW
//  SCL     WHITE


#include "CHT8305.h"

CHT8305 CHT(0x40);   //  CHT8305_DEFAULT_ADDRESS = 0x40


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("CHT8305_LIB_VERSION: ");
  Serial.println(CHT8305_LIB_VERSION);
  Serial.println();

  Wire.begin();
  Wire.setClock(400000);
  CHT.begin();

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
    Serial.print(CHT.getHumidity());
    Serial.print('\t');
    Serial.println(CHT.getTemperature());
  }
}


//  -- END OF FILE --
