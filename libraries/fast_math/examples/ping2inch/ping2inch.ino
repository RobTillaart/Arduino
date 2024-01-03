//
//    FILE: ping2inch.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2022-12-09
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


  Serial.print("ping2inch fast\t");
  delay(10);
  start = micros();
  for (uint16_t i = 0; i < 10000; i++)
  {
    q = ping2inch(i);
  }
  stop = micros();
  Serial.println((stop - start) / 10000.0, 4);
  delay(10);


  Serial.print("ping2quarter ref\t");
  delay(10);
  start = micros();
  for (uint16_t i = 0; i < 10000; i++)
  {
    q = i / 18.6764705875;
  }
  stop = micros();
  Serial.println((stop - start) / 10000.0, 4);
  delay(10);


  Serial.print("ping2quarter fast\t");
  delay(10);
  start = micros();
  for (uint16_t i = 0; i < 10000; i++)
  {
    q = ping2quarter(i);
  }
  stop = micros();
  Serial.println((stop - start) / 10000.0, 4);
  delay(10);


  Serial.print("ping2sixteenths ref\t");
  delay(10);
  start = micros();
  for (uint16_t i = 0; i < 10000; i++)
  {
    q = i / 4.669117646875;
  }
  stop = micros();
  Serial.println((stop - start) / 10000.0, 4);
  delay(10);


  Serial.print("ping2sixteenths fast\t");
  delay(10);
  start = micros();
  for (uint16_t i = 0; i < 10000; i++)
  {
    q = ping2sixteenths(i);
  }
  stop = micros();
  Serial.println((stop - start) / 10000.0, 4);
  delay(10);


  Serial.println("\nverify I");
  for (uint16_t i = 0; i < 200; i += 10)
  {
    Serial.print(i);
    Serial.print("\t");
    //  Serial.print(i / 75);
    Serial.print(i / 74.70588235, 1);
    Serial.print("\t");
    Serial.print(ping2inch(i));
    Serial.print("\t");
    Serial.print((1.0 * ping2inch(i)) / (i / 74.70588235), 2 );
    Serial.print("\t\t");
    Serial.print(i / 18.6764705875, 0);
    Serial.print("\t");
    Serial.print(ping2quarter(i));
    Serial.print("\t");
    Serial.print((1.0 * ping2quarter(i)) / (i / 18.6764705875), 2 );
    Serial.print("\t\t");
    Serial.print(i / 4.669117646875, 0);
    Serial.print("\t");
    Serial.print(ping2sixteenths(i));
    Serial.print("\t");
    Serial.print((1.0 * ping2sixteenths(i)) / (i / 4.669117646875), 2 );
    Serial.print("\t");
    Serial.println();
  }

  Serial.println("\nverify II");
  for (uint16_t i = 200; i < 1000; i += 50)
  {
    Serial.print(i);
    Serial.print("\t");
    //  Serial.print(i / 75);
    Serial.print(i / 74.70588235, 1);
    Serial.print("\t");
    Serial.print(ping2inch(i));
    Serial.print("\t");
    Serial.print((1.0 * ping2inch(i)) / (i / 74.70588235), 2 );
    Serial.print("\t\t");
    Serial.print(i / 18.6764705875, 0);
    Serial.print("\t");
    Serial.print(ping2quarter(i));
    Serial.print("\t");
    Serial.print((1.0 * ping2quarter(i)) / (i / 18.6764705875), 2 );
    Serial.print("\t\t");
    Serial.print(i / 4.669117646875, 0);
    Serial.print("\t");
    Serial.print(ping2sixteenths(i));
    Serial.print("\t");
    Serial.print((1.0 * ping2sixteenths(i)) / (i / 4.669117646875), 2 );
    Serial.print("\t");
    Serial.println();
  }

  Serial.println("\nverify III");
  for (uint16_t i = 1000; i <= 30000; i += 1000)
  {
    Serial.print(i);
    Serial.print("\t");
    //  Serial.print(i / 75);
    Serial.print(i / 74.70588235, 1);
    Serial.print("\t");
    Serial.print(ping2inch(i));
    Serial.print("\t");
    Serial.print((1.0 * ping2inch(i)) / (i / 74.70588235), 2 );
    Serial.print("\t\t");
    Serial.print(i / 18.6764705875, 0);
    Serial.print("\t");
    Serial.print(ping2quarter(i));
    Serial.print("\t");
    Serial.print((1.0 * ping2quarter(i)) / (i / 18.6764705875), 2 );
    Serial.print("\t\t");
    Serial.print(i / 4.669117646875, 0);
    Serial.print("\t");
    Serial.print(ping2sixteenths(i));
    Serial.print("\t");
    Serial.print((1.0 * ping2sixteenths(i)) / (i / 4.669117646875), 2 );
    Serial.print("\t");
    Serial.println();
  }
}

void loop()
{
}


//  -- END OF FILE --
