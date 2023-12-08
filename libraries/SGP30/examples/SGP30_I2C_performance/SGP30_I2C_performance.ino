//
//    FILE: SGP30_I2C_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo SGP30
//     URL: https://github.com/RobTillaart/SGP30
//          https://www.adafruit.com/product/3709


#include "SGP30.h"


SGP30 SGP;

uint32_t start, stop;

void setup()
{
  Serial.begin(115200);
  while (!Serial) {
    delay(1);
    yield();
  };

  Serial.println(__FILE__);
  Serial.print("SGP30_LIB_VERSION: ");
  Serial.println(SGP30_LIB_VERSION);
  Serial.println();

  Wire.begin();

  Serial.print("BEGIN:\t");
  Serial.println(SGP.begin());
  Serial.print("TEST:\t");
  Serial.println(SGP.measureTest());

  delay(1000);

  //  has 12 millisecond delay build in...
  Serial.println("\nMEASURE()");
  for (uint32_t sp = 100000; sp <= 500000; sp += 50000)
  {
    Wire.setClock(sp);
    start = micros();
    SGP.measure(false);
    stop = micros();
    Serial.print(sp);
    Serial.print("\t");
    Serial.println(stop - start);
    delay(1000);
  }


  //  has 40 millisecond delay build in...
  Serial.println("\nMEASURE()");
  for (uint32_t sp = 100000; sp <= 500000; sp += 50000)
  {
    Wire.setClock(sp);
    start = micros();
    SGP.measure(true);
    stop = micros();
    Serial.print(sp);
    Serial.print("\t");
    Serial.println(stop - start);
    delay(1000);
  }


  Serial.println("\nREQUEST()");
  for (uint32_t sp = 100000; sp <= 500000; sp += 50000)
  {
    Wire.setClock(sp);
    start = micros();
    SGP.request();
    stop = micros();
    Serial.print(sp);
    Serial.print("\t");
    Serial.println(stop - start);
    delay(1000);
  }


  Serial.println("\nREAD()");
  for (uint32_t sp = 100000; sp <= 500000; sp += 50000)
  {
    Wire.setClock(sp);
    start = micros();
    SGP.read();
    stop = micros();
    Serial.print(sp);
    Serial.print("\t");
    Serial.println(stop - start);
    SGP.request();
    delay(1000);
  }
}


void loop()
{
}


//  -- END OF FILE --

