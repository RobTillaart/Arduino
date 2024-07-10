//
//    FILE: MCP4261_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/MCP4261
//
//  under investigation.

#include "MCP4261.h"


uint32_t start, stop;


//  select, shutdown, dataIn, dataOut, clock == SOFTWARE SPI
MCP4261 pot(10, 6, 7, 8, 9);

//  select, shutdown, &SPI === HW SPI UNO clock = 13, data = 11
//  MCP4261 pot(10, 6, &SPI);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MCP4261_LIB_VERSION: ");
  Serial.println(MCP4261_LIB_VERSION);
  Serial.println();

  SPI.begin();

  pot.begin();
  pot.setSPIspeed(1000000);
  test_timing();
  pot.setSPIspeed(2000000);
  test_timing();
  pot.setSPIspeed(4000000);
  test_timing();
  pot.setSPIspeed(8000000);
  test_timing();

  Serial.println("\nDone...");
}


void loop()
{
}



void test_timing()
{
  Serial.println();
  Serial.println(__FUNCTION__);
  Serial.print("SPI:\t");
  Serial.println(pot.getSPIspeed());
  delay(100);

  start = micros();
  for (int i = 0; i < 250; i++)
  {
    pot.setValue(0, 42);
    pot.setValue(1, 43);
  }
  stop = micros();
  Serial.print("500 x setValue():\t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println((stop - start) / 500.0);
  delay(100);

  volatile int x = 0;
  start = micros();
  for (int i = 0; i < 250; i++)
  {
    x += pot.getValue(0);
    x += pot.getValue(1);
  }
  stop = micros();
  Serial.print("500 x getValue():\t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println((stop - start) / 500.0);
  delay(100);

  start = micros();
  for (int i = 0; i < 250; i++)
  {
    x += pot.getValueDevice(0);
    x += pot.getValueDevice(1);
  }
  stop = micros();
  Serial.print("500 x getValueDevice():\t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println((stop - start) / 500.0);
  delay(100);

  pot.setValue(0);
  start = micros();
  for (int i = 0; i < 250; i++)
  {
    pot.incrValue(0);
    pot.incrValue(1);
  }
  stop = micros();
  Serial.print("500 x incrValue():\t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println((stop - start) / 500.0);
  delay(100);

  pot.setValue(255);
  start = micros();
  for (int i = 0; i < 250; i++)
  {
    pot.decrValue(0);
    pot.decrValue(1);
  }
  stop = micros();
  Serial.print("500 x decrValue():\t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println((stop - start) / 500.0);
  delay(100);
}


//  -- END OF FILE --
