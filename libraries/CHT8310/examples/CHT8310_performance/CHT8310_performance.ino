//
//    FILE: CHT8310_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: measure performance CHT8310 I2C humidity & temperature sensor
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
uint32_t start, stop;

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
  delay(1000);

  for (uint32_t speed = 50000; speed <= 600000; speed += 50000)
  {
    Wire.setClock(speed);
    testPerformance(speed);
  }
}


void testPerformance(uint32_t speed)
{
  Serial.println();
  Serial.println(speed);
  delay(100);

  start = micros();
  CHT.read();
  stop = micros();
  Serial.print("READ:\t");
  Serial.println(stop - start);
  delay(500);

  start = micros();
  CHT.readTemperature();
  stop = micros();
  Serial.print("READ T:\t");
  Serial.println(stop - start);
  delay(500);

  start = micros();
  CHT.readHumidity();
  stop = micros();
  Serial.print("READ H:\t");
  Serial.println(stop - start);
  delay(500);
  
  start = micros();
  uint16_t m = CHT.getManufacturer();
  stop = micros();
  Serial.print("M:");
  Serial.print(m, HEX);
  Serial.print(":\t");
  Serial.println(stop - start);
  delay(500);
}


void loop()
{
}


//  -- END OF FILE --
