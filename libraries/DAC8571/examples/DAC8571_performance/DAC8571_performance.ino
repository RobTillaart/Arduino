//
//    FILE: DAC8571_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: performance measurement I2C speed.
//     URL: https://github.com/RobTillaart/DAC8571
//
// NOTE: output is written in markdown format of a table
//       (so easy to include in the readme.md ;)
//       can be changed to tab based or comma based output


#include "DAC8571.h"

DAC8571 dev(0x4E);

uint32_t start, stop;

volatile uint16_t x;


void setup()
{
  Serial.begin(115200);
  while(!Serial);
  delay(2000);

  Serial.println(__FILE__);
  Serial.print("DAC8571_LIB_VERSION: ");
  Serial.println(DAC8571_LIB_VERSION);

  Wire.begin();

  dev.begin();

  if (! dev.isConnected())
  {
    Serial.println("\nFailed to connect\n");
    // while(1);
  }
  delay(100);

  Serial.print("Address: ");
  Serial.println(dev.getAddress(), HEX);
  Serial.println();

  test1();

  //  to elaborate
  test_write_array(100000);
  test_write_array(200000);
  test_write_array(300000);
  test_write_array(400000);
  test_write_array(500000);
  test_write_array(600000);
  test_write_array(700000);

  Serial.println("\ndone...");
}


void loop()
{
}


/////////////////////////////////////////////////////////////////////////

void test1()
{
  Serial.println(F("| Wire clock | write() | read() |"));
  Serial.println(F("|:----------:|:-------:|:------:|"));
  for (uint8_t i = 1; i <= 14; i++)
  {
    uint32_t clk = 50000UL * i;
    Wire.setClock(clk);
    Serial.print("| ");
    Serial.print(clk);
    Serial.print(" | ");

    test_write();
    test_read();

    Serial.println();
  }
  Serial.println();
}


void test_write()
{
  delay(100);  //  flush all output
  start = micros();
  for (uint16_t i = 0; i < 1000; i++)
  {
    uint16_t val = i;
    dev.write(val);
  }
  stop = micros();

  Serial.print((stop - start) * 0.001);
  Serial.print(" | ");
}


void test_read()
{
  delay(100);  //  flush all output
  start = micros();
  for (uint16_t i = 0; i < 1000; i++)
  {
    x = dev.read();
  }
  stop = micros();

  Serial.print((stop - start) * 0.001);
  Serial.print(" | ");
}


void test_write_array(uint32_t clk)
{
  Wire.setClock(clk);
  uint16_t arr[10];
  for (int i = 0; i < 10; i++) arr[i] = i * 10;

  delay(100);  //  flush all output
  start = micros();
  for (uint16_t i = 0; i < 1000; i++)
  {
    dev.write(arr, 10);
  }
  stop = micros();

  Serial.print(clk);
  Serial.print("   ");
  Serial.print((stop - start) * 0.001);
  Serial.print("   ");
  Serial.println((stop - start) * 0.0001);
}


//  -- END OF FILE --
