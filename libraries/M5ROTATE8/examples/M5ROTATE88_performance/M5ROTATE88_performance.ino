//
//    FILE: M5ROTATE8_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: measurement performance
//     URL: https://github.com/RobTillaart/M5ROTATE8


#include "m5rotate8.h"


M5ROTATE8 MM;

uint32_t start, stop;
uint16_t x;


void performance()
{
  start = micros();
  for (int i = 0; i < 100; i++)
  {
    for (int ch = 0; ch < 8; ch++)
    {
      MM.writeRGB(ch, 128, 128, 128);
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
    x = MM.getAbsCounter(3);
  }
  stop = micros();
  Serial.print("getAbsCounter:\t");
  Serial.println((stop - start) / 100.0);
  delay(100);

  start = micros();
  for (int i = 0; i < 100; i++)
  {
    x = MM.getRelCounter(5);
  }
  stop = micros();
  Serial.print("getRelCounter:\t");
  Serial.println((stop - start) / 100.0);
  delay(100);

  start = micros();
  for (int i = 0; i < 100; i++)
  {
    x = MM.getKeyPressed(7);
  }
  stop = micros();
  Serial.print("getKeyPressed:\t");
  Serial.println((stop - start) / 100.0);
  delay(100);

  start = micros();
  for (int i = 0; i < 100; i++)
  {
    x = MM.setAbsCounter(1, 1000);
  }
  stop = micros();
  Serial.print("setAbsCounter:\t");
  Serial.println((stop - start) / 100.0);
  delay(100);

  start = micros();
  for (int i = 0; i < 100; i++)
  {
    x = MM.resetCounter(1);
  }
  stop = micros();
  Serial.print("resetCounter:\t");
  Serial.println((stop - start) / 100.0);
  delay(100);

  Serial.println("\ndone...");
}


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("M5ROTATE8_LIB_VERSION: ");
  Serial.println(M5ROTATE8_LIB_VERSION);
  delay(100);

  Wire.begin();
  MM.begin();

  for (uint32_t speed = 100000; speed <= 400000; speed += 100000)
  {
    Wire.setClock(speed);
    Serial.println();
    Serial.print("I2C:\t");
    Serial.println(speed);
    performance();
  }
}


void loop()
{
}


//  -- END OF FILE --
