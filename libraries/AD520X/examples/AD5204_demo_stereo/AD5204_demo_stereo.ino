//
//    FILE: AD5204_demo_stereo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/AD520X


#include "AD520X.h"

uint32_t start, stop;


//  select, reset, shutdown, data, clock
//  AD5204 pot(10, 255, 255, 8, 9);  //  SW SPI
AD5204 pot = AD5204(10, 12, 13);     //  HW SPI  (default SPI)


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("AD520X_LIB_VERSION: ");
  Serial.println(AD520X_LIB_VERSION);
  Serial.println();

  SPI.begin();
  pot.begin(4);

  //  test_sinus();
  //  test_sawtooth();
  test_timing();

  Serial.println("\nDone...");
}


void loop()
{
}


//  connect all A GND and B 5V
//  there will be three pairs of different signals (same freq).
void test_sinus()
{
  Serial.println(__FUNCTION__);
  delay(10);

  start = millis();
  uint32_t i = 0;
  while (millis() - start < 10000)
  {
    uint8_t value = 127 * sin(i * TWO_PI / 100);
    pot.setValue(0, 1, 128 + value);
    //  no need for pm's to be adjacent
    pot.setValue(2, 5, 128 - value);
    pot.setValue(4, 3, 128);  //  constant is allowed.
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
  while (millis() - start < 10000)
  {
    pot.setValue(0, 5, i++);  //  auto wrap is fast...
  }
}


void test_timing()
{
  Serial.println(__FUNCTION__);
  delay(10);

  start = micros();
  for (int i = 0; i < 10000; i++)
  {
    pot.setValue(0, i);  //  auto wrap is fast...
  }
  stop = micros();
  Serial.print("10000 x setValue(0, value):\t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  for (int i = 0; i < 10000; i++)
  {
    pot.setValue(0, 1, i);  //  auto wrap is fast...
  }
  stop = micros();
  Serial.print("10000 x setValue(0, 1, value):\t");
  Serial.println(stop - start);
  delay(10);


  start = micros();
  for (int i = 0; i < 10000; i++)
  {
    pot.setValue(0, i);  //  auto wrap is fast...
    pot.setValue(0, i);  //  auto wrap is fast...
  }
  stop = micros();
  Serial.print("10000 x 2x setValue(0, value):\t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  for (int i = 0; i < 10000; i++)
  {
    pot.setPercentage(0, 50);  //  auto wrap is fast...
  }
  stop = micros();
  Serial.print("10000 x setPercentage(0, value):\t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  for (int i = 0; i < 10000; i++)
  {
    pot.setPercentage(0, 1, 50);  //  auto wrap is fast...
  }
  stop = micros();
  Serial.print("10000 x setPercentage(0, 1, value):\t");
  Serial.println(stop - start);
  delay(10);


  start = micros();
  for (int i = 0; i < 10000; i++)
  {
    pot.setPercentage(0, 50);
    pot.setPercentage(0, 50);
  }
  stop = micros();
  Serial.print("10000 x 2x setPercentage(0, value):\t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  for (int i = 0; i < 10000; i++)
  {
    pot.setAll(i++);
  }
  stop = micros();
  Serial.print("10000 x setAll():\t");
  Serial.println(stop - start);
  delay(10);

  volatile int x = 0;
  start = micros();
  for (int i = 0; i < 2500; i++)
  {
    x += pot.getValue(0);
    x += pot.getValue(1);
    x += pot.getValue(2);
    x += pot.getValue(3);
  }
  stop = micros();
  Serial.print("10000 x getValue():\t");
  Serial.println(stop - start);
  delay(10);
}


//  -- END OF FILE --
