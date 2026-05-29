//
//    FILE: I2C_ABP2_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/I2C_ABP2


#include "I2C_ABP2.h"


I2C_ABP2 pres(0x28);

uint32_t start, stop;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("I2C_ABP2_LIB_VERSION: ");
  Serial.println(I2C_ABP2_LIB_VERSION);
  Serial.println();

  Wire.begin();
  if (pres.begin(0, 4.0) == false)
  {
    Serial.print("Error: Cannot find device: ");
    Serial.println(pres.getAddress());
  }
  delay(100);

  Serial.println("\nSpeed\trequest\tread");
  test(100000);
  test(200000);
  test(300000);
  test(400000);

  Serial.println();
}


void loop()
{
  if (millis() - pres.lastRead() > 1000)
  {
    pres.request();
    delay(10);
    if (I2C_ABP2_OK == pres.read())
    {
      Serial.print(pres.lastRead());
      Serial.print("\t");
      Serial.print(pres.getState(), HEX);
      Serial.print("\t");
      Serial.print(pres.getMilliBar(), 2);
      Serial.print("\t");
      Serial.print(pres.getCelsius(), 2);
      Serial.print("\n");
    }
  }
}


void test(uint32_t speed)
{
  Wire.setClock(speed);
  Serial.print(speed);
  delay(100);

  start = micros();
  pres.request();
  stop = micros();
  Serial.print("\t");
  Serial.print(stop - start);
  delay(100);

  start = micros();
  pres.read();
  stop = micros();
  Serial.print("\t");
  Serial.println(stop - start);
  delay(100);
}

//  -- END OF FILE --
