//
//    FILE: AD5204_demo.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo
//    DATE: 2020-07-24
//     URL: https://github.com/RobTillaart/AD520X

#include "AD520X.h"

uint32_t start, stop;

#define TWOPI    (3.14159265 * 2)

// select, reset, shutdown, data, clock
// AD5204 pot(10, 255, 255, 8, 9);  // SW SPI
AD5204 pot = AD5204(10, 12, 13);     // HW SPI

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  pot.begin(4);

  test_sinus();
  test_sawtooth();
  test_timing();

  Serial.println("\nDone...");
}

void loop()
{
}

// connect all A GND and B 5V
// every W will have a different signal (same freq).
void test_sinus()
{
  Serial.println(__FUNCTION__);
  delay(10);

  start = millis();
  uint32_t i = 0;
  while (millis() - start < 10000)
  {
    uint8_t value = 127 * sin(i * TWOPI / 100);
    pot.setValue(0, 128 + value);
    pot.setValue(1, 128 + value / 2);
    pot.setValue(2, 64  + value / 2);
    pot.setValue(3, 192 + value / 2);
    pot.setValue(4, 224 + value / 4);
    pot.setValue(5, 128 - value);
    i++;
  }
}

// straightforward sawtooth.
void test_sawtooth()
{
  Serial.println(__FUNCTION__);
  delay(10);

  start = millis();
  uint8_t i = 0;
  while (millis() - start < 10000)
  {
    pot.setValue(0, i++); // autowrap is fast...
  }
}

void test_timing()
{
  Serial.println(__FUNCTION__);
  delay(10);

  start = micros();
  for (int i = 0; i < 10000; i++)
  {
    pot.setValue(0, i++); // autowrap is fast...
  }
  stop = micros();
  Serial.print("10000 x setValue():\t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    pot.setAll(i++);
  }
  stop = micros();
  Serial.print("1000 x setAll():\t");
  Serial.println(stop - start);
  delay(10);

  volatile int x = 0;
  start = micros();
  for (int i = 0; i < 250; i++)
  {
    x += pot.getValue(0);
    x += pot.getValue(1);
    x += pot.getValue(2);
    x += pot.getValue(3);
  }
  stop = micros();
  Serial.print("1000 x getValue():\t");
  Serial.println(stop - start);
  delay(10);

}

// -- END OF FILE --
