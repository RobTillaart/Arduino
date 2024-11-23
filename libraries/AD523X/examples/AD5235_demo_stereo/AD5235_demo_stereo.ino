//
//    FILE: AD5235_demo_stereo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/AD523X


#include "AD523X.h"

uint32_t start, stop;


//  select, reset, dataIn, dataOut, clock == SOFTWARE SPI
//  AD5235 pot(10, 255, 7, 8, 9);  //  no reset.
AD5235 pot = AD5235(6, 7);     //  HW SPI by default


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AD523X_LIB_VERSION:\t");
  Serial.println(AD523X_LIB_VERSION);
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
    uint8_t value = 511 * sin(i * TWO_PI / 100);
    pot.setValue(0, 512 + value);
    pot.setValue(1, 512 - value/2);
    i++;
  }
}

//  straightforward sawtooth.
void test_sawtooth()
{
  Serial.println(__FUNCTION__);
  delay(10);

  start = millis();
  uint16_t value = 0;
  while (millis() - start < 25500)
  {
    pot.setValue(0, value);
    pot.setValue(1, 1023 - value);
    value &= 1023;
    delay(100);
  }
}


void test_timing()
{
  Serial.println(__FUNCTION__);
  delay(10);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    pot.setAll(i);
  }
  stop = micros();
  Serial.print("1000 x setAll(value):\t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    pot.setValue(0, i);
    pot.setValue(1, i);
  }
  stop = micros();
  Serial.print("2000 x setValue(0, value):\t");
  Serial.println(stop - start);
  delay(10);


  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    pot.setPercentage(0, 50);
  }
  stop = micros();
  Serial.print("1000 x setPercentage(0, value):\t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    pot.setPercentageAll(50);
  }
  stop = micros();
  Serial.print("1000 x setPercentageAll(50):\t");
  Serial.println(stop - start);
  delay(10);


  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    pot.setPercentage(0, 50);
    pot.setPercentage(1, 50);
  }
  stop = micros();
  Serial.print("1000 x 2x setPercentage(0, value):\t");
  Serial.println(stop - start);
  delay(10);

  volatile int x = 0;
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x += pot.getValue(0);
    x += pot.getValue(1);
  }
  stop = micros();
  Serial.print("1000 x 2x getValue():\t");
  Serial.println(stop - start);
  delay(10);
}


//  -- END OF FILE --
