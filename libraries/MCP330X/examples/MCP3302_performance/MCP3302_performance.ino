//
//    FILE: MCP3302_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: simple performance measurement.
//     URL: https://github.com/RobTillaart/MCP330X
//


#include "MCP330X.h"

MCP3302 mcp2;
MCP3302 mcp2s(11, 12, 13);  //  software SPI
MCP3304 mcp4;
MCP3304 mcp4s(10, 12, 13);  //  software SPI

uint32_t start, stop;


void setup()
{
  //  while (!Serial);  //  uncomment if needed
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("MCP330X_LIB_VERSION: ");
  Serial.println(MCP330X_LIB_VERSION);
  Serial.println();


  SPI.begin();

  mcp2.begin(7);
  mcp2s.begin(8);
  mcp4.begin(9);
  mcp4s.begin(10);

  Serial.println();

  Serial.println("ADC\tCHAN\tMAXVALUE");
  Serial.print("mcp2\t");
  Serial.print(mcp2.channels());
  Serial.print("\t");
  Serial.println(mcp2.maxValue());

  Serial.print("mcp2s\t");
  Serial.print(mcp2s.channels());
  Serial.print("\t");
  Serial.println(mcp2s.maxValue());

  Serial.print("mcp4\t");
  Serial.print(mcp4.channels());
  Serial.print("\t");
  Serial.println(mcp4.maxValue());

  Serial.print("mcp4s\t");
  Serial.print(mcp4s.channels());
  Serial.print("\t");
  Serial.println(mcp4s.maxValue());


  Serial.println("\nTiming in micros().\n");
  delay(10);

  test_2();
  test_2s();
  test_4();
  test_4s();

  //  on UNO there is no difference above 8MHz (half CPU clock)
  Serial.println("***************************************\n");
  for (int s = 1; s <= 16; s *= 2)
  {
    Serial.println(s * 1000000UL);
    mcp2.setSPIspeed(s * 1000000UL);
    test_2();
  }

  Serial.println("\ndone...");
}


void loop()
{
}


void test_2()
{
  Serial.println();
  Serial.println(__FUNCTION__);
  int32_t value = 0;

  start = micros();
  for (int channel = 0 ; channel < mcp2.channels(); channel++)
  {
    value += mcp2.read(channel);
  }
  stop = micros();
  Serial.print("mcp2.read()\t4x: \t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  for (int channel = 0 ; channel < mcp2.channels(); channel++)
  {
    value += mcp2.differentialRead(channel);
  }
  stop = micros();
  Serial.print("mcp2.diffRead() 4x: \t");
  Serial.println(stop - start);

  delay(10);
}


void test_2s()
{
  Serial.println();
  Serial.println(__FUNCTION__);
  int32_t value = 0;

  start = micros();
  for (int channel = 0 ; channel < mcp2s.channels(); channel++)
  {
    value += mcp2s.read(channel);
  }
  stop = micros();
  Serial.print("mcp2s.read()\t4x: \t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  for (int channel = 0 ; channel < mcp2s.channels(); channel++)
  {
    value += mcp2s.differentialRead(channel);
  }
  stop = micros();
  Serial.print("mcp2s.diffRead() 4x: \t");
  Serial.println(stop - start);
  delay(10);
}


void test_4()
{
  Serial.println();
  Serial.println(__FUNCTION__);
  int32_t value = 0;

  start = micros();
  for (int channel = 0 ; channel < mcp4.channels(); channel++)
  {
    value += mcp4.read(channel);
  }
  stop = micros();
  Serial.print("mcp4.read()\t8x: \t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  for (int channel = 0 ; channel < mcp4.channels(); channel++)
  {
    value += mcp4.differentialRead(channel);
  }
  stop = micros();
  Serial.print("mcp4.diffRead() 8x: \t");
  Serial.println(stop - start);
  delay(10);
}


void test_4s()
{
  Serial.println();
  Serial.println(__FUNCTION__);
  int32_t value = 0;

  start = micros();
  for (int channel = 0 ; channel < mcp4s.channels(); channel++)
  {
    value += mcp4s.read(channel);
  }
  stop = micros();
  Serial.print("mcp4s.read()\t8x: \t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  for (int channel = 0 ; channel < mcp4s.channels(); channel++)
  {
    value += mcp4s.differentialRead(channel);
  }
  stop = micros();
  Serial.print("mcp4s.diffRead() 8x: \t");
  Serial.println(stop - start);
  delay(10);
}


//  -- END OF FILE --
