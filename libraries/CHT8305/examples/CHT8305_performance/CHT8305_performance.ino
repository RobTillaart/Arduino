//
//    FILE: CHT8305_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: I2C performance for CHT8305 I2C humidity & temperature sensor
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

uint32_t start, stop;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("CHT8305_LIB_VERSION: ");
  Serial.println(CHT8305_LIB_VERSION);
  Serial.println();
  delay(100);

  Wire.begin();
  CHT.begin();
  delay(1000);

  Serial.println("Note: reading temperature is blocking!\n");

  Serial.println("SPEED\tREAD\tREAD_T\tREAD_H");
  for (uint32_t speed = 100000; speed <= 800000; speed += 50000)
  {
    Wire.setClock(speed);

    start = micros();
    CHT.read();
    stop = micros();
    Serial.print(speed);
    Serial.print("\t");
    Serial.print(stop - start);
    delay(1000);

    start = micros();
    CHT.readTemperature();
    stop = micros();
    Serial.print("\t");
    Serial.print(stop - start);
    delay(1000);

    start = micros();
    CHT.readHumidity();
    stop = micros();
    Serial.print("\t");
    Serial.print(stop - start);
    Serial.print("\n");
    delay(1000);
  }
}


void loop()
{
}


//  -- END OF FILE --
