//
//    FILE: AD56X8_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: performance test
//     URL: https://github.com/RobTillaart/AD56X8


#include "AD56X8.h"


AD56X8 AD16_HW(8);
AD56X8 AD16_SW(9, 10, 11);

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AD56X8_LIB_VERSION: ");
  Serial.println(AD56X8_LIB_VERSION);

  SPI.begin();
  AD16_HW.begin();
  AD16_SW.begin();

  Serial.print("HWSPI: ");
  Serial.println(AD16_HW.usesHWSPI());
  Serial.print("HWSPI: ");
  Serial.println(AD16_SW.usesHWSPI());
  delay(10);

  //  test setValue()
  start = micros();
  for (uint16_t i = 0; i < 1000; i++)
  {
    AD16_HW.setValue(0, i);
  }
  stop = micros();
  Serial.print("HW SetValue:\t");
  Serial.println((stop - start) * 0.001);
  delay(10);

  start = micros();
  for (uint16_t i = 0; i < 1000; i++)
  {
    AD16_SW.setValue(0, i);
  }
  stop = micros();
  Serial.print("SW SetValue:\t");
  Serial.println((stop - start) * 0.001);
  delay(10);

  Serial.println("\nHW SPI performance\n------------------");
  for (uint32_t speed = 100000; speed <= 16000000; speed *= 2)
  {
    AD16_HW.setSPIspeed(speed);
    start = micros();
    for (uint16_t i = 0; i < 1000; i++)
    {
      AD16_HW.setValue(0, i);
    }
    stop = micros();
    Serial.print(speed);
    Serial.print("\tHW SetValue:\t");
    Serial.println((stop - start) * 0.001);
    delay(10);
  }

  Serial.println("\nDone...");
}


void loop()
{
}


//  -- END OF FILE --
