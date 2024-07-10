//
//    FILE: MCP4261_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/MCP4261


#include "MCP4261.h"


uint32_t start, stop;


//  select, shutdown, dataIn, dataOut, clock == SOFTWARE SPI
// MCP4261 pot(10, 6, 7, 8, 9);

//  select, shutdown, &SPI === HW SPI UNO clock = 13, dataOut = 11
MCP4261 pot(10, 6, &SPI);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  SPI.begin();

  pot.begin();

  test_extremes();
  test_sinus();
  test_sawtooth();
  test_incr_decr();

  Serial.println("\nDone...");
}


void loop()
{
  test_incr_decr();
}


void test_extremes()
{
  Serial.println(__FUNCTION__);
  delay(10);

  Serial.println("0");
  pot.setValue(0, 0);
  delay(2000);

  Serial.println(MCP42XX_MIDDLE_VALUE);
  pot.setValue(0, MCP42XX_MIDDLE_VALUE);
  delay(2000);

  Serial.println(MCP42XX_MAX_VALUE);
  pot.setValue(0, MCP42XX_MAX_VALUE);
  delay(2000);
}


//  connect all A GND and B 5V
//  every W will have a different signal (same freq).
void test_sinus()
{
  Serial.println(__FUNCTION__);
  delay(10);

  start = millis();
  uint32_t i = 0;
  while (millis() - start < 10000)
  {
    int8_t value = 127 * sin(i * TWO_PI / 100);
    pot.setValue(0, 128 + value);
    pot.setValue(1, 128 + value / 2);
    i++;
  }
}

//  straightforward sawtooth.
void test_sawtooth()
{
  Serial.println(__FUNCTION__);
  delay(10);

  for (int i = 0; i < 255; i++)
  {
    pot.setValue(0, i);  //  auto wrap is fast...
    pot.setValue(1, i++);  //  auto wrap is fast...
    delay(100);
  }
}


void test_incr_decr()
{
  Serial.println(__FUNCTION__);
  delay(10);
  pot.setValue(0, 0);
  for (int i = 0; i < 255; i++)
  {
    pot.incrValue(0);
    pot.incrValue(1);
    delay(100);
  }
  for (int i = 0; i < 255; i++)
  {
    pot.decrValue(0);
    pot.decrValue(1);
    delay(100);
  }
}


//  -- END OF FILE --
