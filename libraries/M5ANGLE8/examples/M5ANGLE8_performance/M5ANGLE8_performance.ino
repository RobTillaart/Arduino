//
//    FILE: M5ANGLE8_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: meansurement performance
//     URL: https://github.com/RobTillaart/M5ANGLE8


#include "m5angle8.h"


M5ANGLE8 MM;

uint32_t start, stop;
uint16_t x;

void setup()
{
  Serial.begin(115200);
  Serial.print("M5ANGLE8_LIB_VERSION: ");
  Serial.println(M5ANGLE8_LIB_VERSION);
  delay(100);

  Wire.begin();
  MM.begin();

  for (uint32_t speed = 100000; speed <= 500000; speed += 100000)
  {
    Wire.setClock(speed);
    Serial.println();
    Serial.print("I2C:\t");
    Serial.println(speed);
    performance();
  }
}


void performance()
{
  start = micros();
  for (int i = 0; i < 100; i++)
  {
    for (int ch = 0; ch < 8; ch++)
    {
      MM.writeRGB(ch, 128, 128, 128, 50);
    }
  }
  stop = micros();
  Serial.print("writeRGB:\t");
  Serial.println((stop - start) / 800.0);
  MM.allOff();
  delay(100);

  start = micros();
  for (int i = 0; i < 100; i++)
  {
    MM.allOff();
  }
  stop = micros();
  Serial.print("allOff:\t\t");
  Serial.println((stop - start) / 100.0);
  delay(100);

  start = micros();
  for (int i = 0; i < 100; i++)
  {
    x = MM.inputSwitch();
  }
  stop = micros();
  Serial.print("inputSwitch:\t");
  Serial.println((stop - start) / 100.0);
  delay(100);

  start = micros();
  for (int i = 0; i < 100; i++)
  {
    x = MM.analogRead(3);
  }
  stop = micros();
  Serial.print("a-read H:\t");
  Serial.println((stop - start) / 100.0);
  delay(100);

  start = micros();
  for (int i = 0; i < 100; i++)
  {
    x = MM.analogRead(3, 8);
  }
  stop = micros();
  Serial.print("a-read L:\t");
  Serial.println((stop - start) / 100.0);
  delay(100);
}


void loop()
{
  //  for (int ch = 0; ch < 8; ch++)
  //  {
  //    Serial.print(MM.analogRead(ch));
  //    Serial.print("\t");
  //  }
  //  Serial.print(MM.inputSwitch());
  //  Serial.print("\n");
  //  delay(10);
}


//  -- END OF FILE --
