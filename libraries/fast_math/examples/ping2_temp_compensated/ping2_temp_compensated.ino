//
//    FILE: ping2_temp_compensated.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2022-12-25
// PURPOSE: test fast routines for PING))) sensor
//     URL: https://github.com/RobTillaart/fast_math


#include "Arduino.h"
#include "fast_math.h"


uint32_t start, stop;
volatile uint32_t q = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("FASTMATH_LIB_VERSION: ");
  Serial.println(FASTMATH_LIB_VERSION);
  Serial.println();
  delay(10);

  Serial.print("ping2cm ref\t");
  delay(10);
  start = micros();
  for (uint16_t i = 0; i < 10000; i++)
  {
    q = i / 29.41176;
  }
  stop = micros();
  Serial.println((stop - start) / 10000.0, 4);
  delay(10);

  Serial.print("ping2cm_tempC\t");
  delay(10);
  start = micros();
  for (uint16_t i = 0; i < 10000; i++)
  {
    q = ping2cm_tempC(i, 20);
  }
  stop = micros();
  Serial.println((stop - start) / 10000.0, 4);
  delay(10);



  Serial.print("ping2inch ref\t");
  delay(10);
  start = micros();
  for (uint16_t i = 0; i < 10000; i++)
  {
    q = i / 74.70588235;
  }
  stop = micros();
  Serial.println((stop - start) / 10000.0, 4);
  delay(10);

  Serial.print("ping2inch_tempC\t");
  delay(10);
  start = micros();
  for (uint16_t i = 0; i < 10000; i++)
  {
    q = ping2inch_tempC(i, 20);
  }
  stop = micros();
  Serial.println((stop - start) / 10000.0, 4);
  delay(10);

  Serial.print("ping2inch_tempF\t");
  delay(10);
  start = micros();
  for (uint16_t i = 0; i < 10000; i++)
  {
    q = ping2inch_tempC(i, 68);
  }
  stop = micros();
  Serial.println((stop - start) / 10000.0, 4);
  delay(10);


  Serial.println("\n==============================================");

  Serial.println("\ndelta ping2cm_tempC");
  for (uint16_t temp = 0; temp < 40; temp++)
  {
    Serial.print(temp);
    Serial.print("\t");
    Serial.print(15000 / 29.41176, 1);
    Serial.print("\t");
    Serial.print(ping2cm_tempC(15000, temp));
    Serial.print("\t");
    Serial.print(ping2cm_tempC(15000, temp) / (15000 / 29.41176) );
    Serial.println();
  }

  Serial.println("\ndelta ping2inch_tempC");
  for (uint16_t temp = 0; temp < 40; temp++)
  {
    Serial.print(temp);
    Serial.print("\t");
    Serial.print(15000 / 74.70588235, 1);
    Serial.print("\t");
    Serial.print(ping2inch_tempC(15000, temp));
    Serial.print("\t");
    Serial.print(ping2inch_tempC(15000, temp) / (15000 / 74.70588235));
    Serial.println();
  }


  Serial.println("\ndelta ping2inch_tempF");
  for (uint16_t temp = 32; temp < 100; temp += 2)
  {
    Serial.print(temp);
    Serial.print("\t");
    Serial.print(15000 / 74.70588235, 1);
    Serial.print("\t");
    Serial.print(ping2inch_tempF(15000, temp));
    Serial.print("\t");
    Serial.print(ping2inch_tempF(15000, temp) / (15000 / 74.70588235));
    Serial.println();
  }

}

void loop()
{
}


//  -- END OF FILE --
