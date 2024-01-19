//
//    FILE: AD5204_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2020-07-24
//     URL: https://github.com/RobTillaart/AD520X


#include "AD520X.h"

uint32_t start, stop;


//  select, reset, shutdown, data, clock == SOFTWARE SPI
//  AD5206 pot(10, 255, 255, 8, 9);

//  select, reset, shutdown, &SPI === HW SPI UNO clock = 13, data = 11
AD5206 pot = AD5206(5, 6, 7, &SPI);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  SPI.begin();
  pot.begin(4);

  //  test_extremes();
  //  test_sinus();
  //  test_sawtooth();
  test_timing();

  Serial.println("\nDone...");
}


void loop()
{
}

void test_extremes()
{
  Serial.println(__FUNCTION__);
  delay(10);

  Serial.println("0");
  pot.setValue(0, 0);
  delay(2000);

  Serial.println("127");
  pot.setValue(0, 127);
  delay(2000);

  Serial.println("255");
  pot.setValue(0, 255);
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
    pot.setValue(2, 64  + value / 2);
    pot.setValue(3, 192 + value / 2);
    pot.setValue(4, 224 + value / 4);
    pot.setValue(5, 128 - value);
    i++;
  }
}

//  straightforward sawtooth.
void test_sawtooth()
{
  Serial.println(__FUNCTION__);
  delay(10);

  start = millis();
  uint8_t i = 0;
  while (millis() - start < 25500)
  {
    pot.setValue(0, i++);  //  auto wrap is fast...
    delay(100);
  }
}


void test_timing()
{
  Serial.println(__FUNCTION__);
  delay(10);

  start = micros();
  for (int i = 0; i < 10000; i++)
  {
    pot.setValue(0, i++);  //  auto wrap is fast...
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


//  -- END OF FILE --
