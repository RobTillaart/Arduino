//
//    FILE: CHT8305_getVoltage.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: Demo for CHT8305 I2C humidity & temperature sensor
//          monitor voltage.

//  for use with plotter

//  Always check datasheet - front view
//
//          +---------------+
//  VCC ----| VCC           |
//  SDA ----| SDA  CHT8305  |
//  GND ----| GND           |
//  SCL ----| SCL           |
//   ?  ----| AD0           |   ? depends on address to select
//          |               |
//  IRQ ----| ALERT         |   only if enabled.
//          +---------------+


#include "CHT8305.h"

CHT8305 CHT;


void setup()
{
  CHT.begin(0x40);   //  default address

  Wire.setClock(400000);

  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("CHT8305_LIB_VERSION: ");
  Serial.println(CHT8305_LIB_VERSION);
  Serial.println();

  Serial.println("voltage\t us");
  delay(1000);
}


void loop()
{
  if (millis() - CHT.lastRead() >= 100)
  {
    // READ DATA
    uint32_t start = micros();
    float voltage = CHT.getVoltage();
    uint32_t stop = micros();

    Serial.print(voltage, 3);
    Serial.print("\t\t");
    Serial.print(stop - start);
    Serial.print("\n");
  }
}


// -- END OF FILE --
