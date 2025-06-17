//
//    FILE: AD7390_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: measure primary performance 
//     URL: https://github.com/RobTillaart/AD7390


#include "AD7390.h"

uint32_t start, stop;


//  select, reset, data, clock == SOFTWARE SPI
AD7390 myDAC(6, 7, 11, 13);

//  select, reset, &SPI === HW SPI UNO clock = 13, data = 11
// AD7390 myDAC(6, 7, &SPI);


void setup()
{
  //  while(!Serial);
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AD7390_LIB_VERSION: ");
  Serial.println(AD7390_LIB_VERSION);
  Serial.println();

  SPI.begin();
  myDAC.begin(0);

  test_timing();

  Serial.println("\nDone...");
}


void loop()
{
}

void test_timing()
{
  Serial.println(__FUNCTION__);
  delay(10);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    myDAC.setValue(i);
  }
  stop = micros();
  Serial.print("1000 x setValue():\t");
  Serial.println(stop - start);
  delay(10);

  volatile int x = 0;
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x += myDAC.getValue();
  }
  stop = micros();
  Serial.print("1000 x getValue():\t");
  Serial.println(stop - start);
  delay(10);

    start = micros();
  for (int i = 0; i < 1000; i++)
  {
    myDAC.setPercentage(i * 0.1);
  }
  stop = micros();
  Serial.print("1000 x setPercentage():\t");
  Serial.println(stop - start);
  delay(10);


}


//  -- END OF FILE --
