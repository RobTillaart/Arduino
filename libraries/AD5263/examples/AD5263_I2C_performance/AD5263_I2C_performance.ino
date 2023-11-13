//
//    FILE: AD5263_I2C_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: AD5263 demo program
//     URL: https://github.com/RobTillaart/AD5263


#include "AD5263.h"

AD5263 AD01(0x2C);  //  AD0 & AD1 == GND

uint32_t start, stop;
volatile uint8_t x = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AD5263_LIB_VERSION: ");
  Serial.println(AD5263_LIB_VERSION);
  Serial.println();

  Wire.begin();

  Serial.println("\nWRITE");
  delay(10);
  for (uint32_t speed = 100000; speed <= 600000; speed += 50000)
  {
    Wire.setClock(speed);
    bool b = AD01.begin();
    if (b == true)
    {
      start = micros();
      AD01.write(0, 0x55);
      stop = micros();
      Serial.print("|  ");
      Serial.print(speed);
      Serial.print("  |  ");
      Serial.println(stop - start);
    }
    delay(100);
  }


  Serial.println("\nREAD");
  delay(10);
  for (uint32_t speed = 100000; speed <= 600000; speed += 50000)
  {
    Wire.setClock(speed);
    bool b = AD01.begin();
    if (b == true)
    {
      start = micros();
      x = AD01.read(0);
      stop = micros();
      Serial.print("|  ");
      Serial.print(speed);
      Serial.print("  |  ");
      Serial.println(stop - start);
    }
    delay(100);
  }
}


void loop()
{
}


//  -- END OF FILE --
