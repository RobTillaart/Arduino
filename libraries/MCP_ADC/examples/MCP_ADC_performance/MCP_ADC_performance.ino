//
//    FILE: MCP_ADC_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: simple performance measurement.
//     URL: https://github.com/RobTillaart/MCP_ADC
//
//  Note the deltaRead() does 1 or 2 differential reads depending
//  on positive of negative delta between 2 pins.
//  Therefore timing might differ substantially.


#include "MCP_ADC.h"

MCP3002 mcp2;
MCP3004 mcp4;
MCP3008 mcp8(11, 12, 13);  //  software SPI
// MCP3008 mcp8;           //  hardware SPI
MCP3202 mcp22;
MCP3204 mcp24;
MCP3208 mcp28;

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MCP_ADC_LIB_VERSION: ");
  Serial.println(MCP_ADC_LIB_VERSION);

  SPI.begin();

  mcp2.begin(8);
  mcp4.begin(9);
  mcp8.begin(10);

  Serial.println();

  Serial.println("ADC\tCHAN\tMAXVALUE");
  Serial.print("mcp2\t");
  Serial.print(mcp2.channels());
  Serial.print("\t");
  Serial.println(mcp2.maxValue());

  Serial.print("mcp4\t");
  Serial.print(mcp4.channels());
  Serial.print("\t");
  Serial.println(mcp4.maxValue());

  Serial.print("mcp8\t");
  Serial.print(mcp8.channels());
  Serial.print("\t");
  Serial.println(mcp8.maxValue());

  Serial.print("mcp22\t");
  Serial.print(mcp22.channels());
  Serial.print("\t");
  Serial.println(mcp22.maxValue());

  Serial.print("mcp24\t");
  Serial.print(mcp24.channels());
  Serial.print("\t");
  Serial.println(mcp24.maxValue());

  Serial.print("mcp28\t");
  Serial.print(mcp28.channels());
  Serial.print("\t");
  Serial.println(mcp28.maxValue());


  Serial.println("\nTiming in micros().\n");
  delay(10);

  test_1();
  test_2();
  test_3();

  //  on UNO there is no difference above 8MHz (half CPU clock)
  Serial.println("***************************************\n");
  for (int s = 1; s <= 16; s *= 2)
  {
    Serial.println(s * 1000000UL);
    mcp8.setSPIspeed(s * 1000000UL);
    test_3();
  }

  //  on UNO there is no difference above 8MHz (half CPU clock)
  Serial.println("***************************************\n");
  for (int s = 1; s <= 16; s *= 2)
  {
    Serial.println(s * 1000000UL);
    mcp22.setSPIspeed(s * 1000000UL);
    test_4();
  }

  //  on UNO there is no difference above 8MHz (half CPU clock)
  Serial.println("***************************************\n");
  for (int s = 1; s <= 16; s *= 2)
  {
    Serial.println(s * 1000000UL);
    mcp24.setSPIspeed(s * 1000000UL);
    test_5();
  }

  //  on UNO there is no difference above 8MHz (half CPU clock)
  Serial.println("***************************************\n");
  for (int s = 1; s <= 16; s *= 2)
  {
    Serial.println(s * 1000000UL);
    mcp28.setSPIspeed(s * 1000000UL);
    test_6();
  }

  Serial.println("done...");
}


void loop()
{
}


void test_1()
{
  uint32_t val = 0;

  start = micros();
  for (int channel = 0 ; channel < mcp2.channels(); channel++)
  {
    val += mcp2.read(channel);
  }
  stop = micros();
  Serial.print("mcp2.read()\t2x: \t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  for (int channel = 0 ; channel < mcp2.channels(); channel++)
  {
    val += mcp2.differentialRead(channel);
  }
  stop = micros();
  Serial.print("mcp2.differentialRead() 2x: \t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  for (int channel = 0 ; channel < mcp2.channels(); channel++)
  {
    val += mcp2.deltaRead(channel);
  }
  stop = micros();
  Serial.print("mcp2.deltaRead()\t2x: \t");
  Serial.println(stop - start);
  Serial.println();
  delay(10);
}


void test_2()
{
  uint32_t val = 0;

  start = micros();
  for (int channel = 0 ; channel < mcp4.channels(); channel++)
  {
    val += mcp4.read(channel);
  }
  stop = micros();
  Serial.print("mcp4.read()\t4x: \t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  for (int channel = 0 ; channel < mcp4.channels(); channel++)
  {
    val += mcp4.differentialRead(channel);
  }
  stop = micros();
  Serial.print("mcp4.differentialRead() 4x: \t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  for (int channel = 0 ; channel < mcp4.channels(); channel++)
  {
    val += mcp4.deltaRead(channel);
  }
  stop = micros();
  Serial.print("mcp4.deltaRead()\t4x: \t");
  Serial.println(stop - start);
  Serial.println();
  delay(10);
}


void test_3()
{
  uint32_t val = 0;

  start = micros();
  for (int channel = 0; channel < mcp8.channels(); channel++)
  {
    val += mcp8.read(channel);
  }
  stop = micros();
  Serial.print("mcp8.read()\t8x: \t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  for (int channel = 0; channel < mcp8.channels(); channel++)
  {
    val += mcp8.differentialRead(channel);
  }
  stop = micros();
  Serial.print("mcp8.differentialRead() 8x: \t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  for (int channel = 0; channel < mcp8.channels(); channel++)
  {
    val += mcp8.deltaRead(channel);
  }
  stop = micros();
  Serial.print("mcp8.deltaRead()\t8x: \t");
  Serial.println(stop - start);
  Serial.println();
  delay(10);
}


void test_4()
{
  uint32_t val = 0;

  start = micros();
  for (int channel = 0; channel < mcp22.channels(); channel++)
  {
    val += mcp22.read(channel);
  }
  stop = micros();
  Serial.print("mcp22.read()\t2x: \t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  for (int channel = 0; channel < mcp22.channels(); channel++)
  {
    val += mcp22.differentialRead(channel);
  }
  stop = micros();
  Serial.print("mcp22.differentialRead() 2x: \t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  for (int channel = 0; channel < mcp22.channels(); channel++)
  {
    val += mcp22.deltaRead(channel);
  }
  stop = micros();
  Serial.print("mcp22.deltaRead()\t2x: \t");
  Serial.println(stop - start);
  Serial.println();
  delay(10);
}


void test_5()
{
  uint32_t val = 0;

  start = micros();
  for (int channel = 0; channel < mcp24.channels(); channel++)
  {
    val += mcp24.read(channel);
  }
  stop = micros();
  Serial.print("mcp24.read()\t4x: \t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  for (int channel = 0; channel < mcp24.channels(); channel++)
  {
    val += mcp24.differentialRead(channel);
  }
  stop = micros();
  Serial.print("mcp24.differentialRead() 4x: \t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  for (int channel = 0; channel < mcp24.channels(); channel++)
  {
    val += mcp24.deltaRead(channel);
  }
  stop = micros();
  Serial.print("mcp24.deltaRead()\t4x: \t");
  Serial.println(stop - start);
  Serial.println();
  delay(10);
}


void test_6()
{
  uint32_t val = 0;

  start = micros();
  for (int channel = 0; channel < mcp28.channels(); channel++)
  {
    val += mcp28.read(channel);
  }
  stop = micros();
  Serial.print("mcp28.read()\t8x: \t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  for (int channel = 0; channel < mcp28.channels(); channel++)
  {
    val += mcp28.differentialRead(channel);
  }
  stop = micros();
  Serial.print("mcp28.differentialRead() 8x: \t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  for (int channel = 0; channel < mcp28.channels(); channel++)
  {
    val += mcp28.deltaRead(channel);
  }
  stop = micros();
  Serial.print("mcp28.deltaRead()\t8x: \t");
  Serial.println(stop - start);
  Serial.println();
  delay(10);
}


//  -- END OF FILE --
