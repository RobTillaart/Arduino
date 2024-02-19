//
//    FILE: CHT8310_test_offset.ino
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

  //  should print 0.00 twice
  Serial.println(CHT.getTemperatureOffset());
  Serial.println(CHT.getHumidityOffset());
  Serial.println();

  CHT.setTemperatureOffset(+273.15);  //  adjusts temperature to Kelvin 
  CHT.setHumidityOffset(-50);         //  extreme just for demo
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
