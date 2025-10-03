//
//    FILE: CHT832X_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: measure performance CHT832X I2C humidity & temperature sensor
//     URL: https://github.com/RobTillaart/CHT832X

//  Always check datasheet for connections


#include "CHT832X.h"


CHT832X CHT;
uint32_t start, stop;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print(F("CHT832X_LIB_VERSION: "));
  Serial.println(CHT832X_LIB_VERSION);
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
