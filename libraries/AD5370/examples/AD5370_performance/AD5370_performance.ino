//
//    FILE: AD5370_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/AD5370


#include "AD5370.h"
#include "SPI.h"

//  hardware SPI
//  (select, reset, clear, &SPI)  // latter optional
//  software SPI
//  (select, reset, clear, dataIn, dataOut, clock)
AD5370 dac40(8, 9, 10);  //  HW SPI

uint32_t start, stop;

void setup()
{
  while (!Serial);
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AD5370_LIB_VERSION: ");
  Serial.println(AD5370_LIB_VERSION);
  Serial.println();

  SPI.begin();
  dac40.begin();

  testSetDac();

  Serial.println("\ndone...");
}

void loop()
{
}

void testSetDac()
{
  Serial.println("SETDAC\nSPI\tTIME");
  for (uint32_t speed = 250000; speed <= 16000000; speed *= 2)
  {
    dac40.setSPIspeed(speed);
    delay(100);
    start = micros();
    for (int i = 0; i < 1000; i++)
    {
      dac40.setDAC(i & 31, i);
    }
    stop = micros();
    Serial.print(speed);
    Serial.print("\t");
    Serial.println(stop - start);
  }
}


//  -- END OF FILE --
