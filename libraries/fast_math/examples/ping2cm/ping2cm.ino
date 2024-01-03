//
//    FILE: ping2cm.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2013-05-11
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

  Serial.print("pingRef\t");
  delay(10);
  start = micros();
  for (uint16_t i = 0; i < 10000; i++)
  {
    q = i / 29.41176;
  }
  stop = micros();
  Serial.println((stop - start) / 10000.0, 4);
  delay(10);

  Serial.print("ping2cm\t");
  delay(10);
  start = micros();
  for (uint16_t i = 0; i < 10000; i++)
  {
    q = ping2cm(i);
  }
  stop = micros();
  Serial.println((stop - start) / 10000.0, 4);
  delay(10);

  Serial.print("ping2mm\t");
  delay(10);
  start = micros();
  for (uint16_t i = 0; i < 10000; i++)
  {
    q = ping2mm(i);
  }
  stop = micros();
  Serial.println((stop - start) / 10000.0, 4);
  delay(100);

  Serial.print("ping2cm32\t");
  delay(10);
  start = micros();
  for (uint16_t i = 0; i < 10000; i++)
  {
    q = ping2cm32(i);
  }
  stop = micros();
  Serial.println((stop - start) / 10000.0, 4);
  delay(10);

  Serial.print("ping2mm32\t");
  delay(10);
  start = micros();
  for (uint16_t i = 0; i < 10000; i++)
  {
    q = ping2mm32(i);
  }
  stop = micros();
  Serial.println((stop - start) / 10000.0, 4);
  delay(100);

  Serial.println("\n=======================================");
  Serial.println("\nverify - 16 bit - up to 10 meter");
  for (uint16_t i = 100; i < 30000; i *= 1.1)
  {
    Serial.print(i);
    Serial.print("\t");
    Serial.print(i * 0.034, 1);
    Serial.print("\t");
    Serial.print(ping2cm(i));
    Serial.print("\t");
    Serial.print((1.0 * ping2cm(i)) / (i * 0.034) );
    Serial.print("\t\t");
    Serial.print(i * 0.34, 1);
    Serial.print("\t");
    Serial.print(ping2mm(i));
    Serial.print("\t");
    Serial.print((1.0 * ping2mm(i)) / (i * 0.34) );
    Serial.println();
  }


  Serial.println("\nverify - 32 bit - up to 100 meter");
  for (uint32_t i = 100; i <= 300000; i *= 1.1)
  {
    Serial.print(i);
    Serial.print("\t");
    Serial.print(i * 0.034, 1);
    Serial.print("\t");
    Serial.print(ping2cm32(i));
    Serial.print("\t");
    Serial.print((1.0 * ping2cm32(i)) / (i * 0.034) );
    Serial.print("\t\t");
    Serial.print(i * 0.34, 1);
    Serial.print("\t");
    Serial.print(ping2mm32(i));
    Serial.print("\t");
    Serial.print((1.0 * ping2mm32(i)) / (i * 0.34) );
    Serial.println();
  }

}

void loop()
{
}


//  -- END OF FILE --
