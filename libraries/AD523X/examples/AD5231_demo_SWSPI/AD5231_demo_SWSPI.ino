//
//    FILE: AD5231_demo_SWSPI.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/AD523X


#include "AD523X.h"


uint32_t start, stop;

#define TWOPI    (3.14159265 * 2)

//  select, reset, dataIn, dataOut, clock == SOFTWARE SPI
AD5231 pot(10, 255, 7, 8, 9);  //  no reset.
//  AD5231 pot = AD5231(6, 7);     //  HW SPI by default


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AD523X_LIB_VERSION:\t");
  Serial.println(AD523X_LIB_VERSION);
  Serial.println();

  pot.begin(4);

  Serial.print("\tusesHWSPI:\t");
  Serial.println(pot.usesHWSPI());

  test_sinus();
  test_sawtooth();

  test_timing();

  Serial.println("\nDone...");
}


void loop()
{
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
    int16_t value = 511 * sin(i * TWO_PI / 100);
    pot.setValue(0, 512 + value);
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
    pot.setValue(0, value++);
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
    pot.setValue(0, i & 1023);
  }
  stop = micros();
  Serial.print("1000 x setValue():\t");
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
  for (int i = 0; i < 1000; i++)
  {
    x += pot.getValue(0);
  }
  stop = micros();
  Serial.print("1000 x getValue():\t");
  Serial.println(stop - start);
  delay(10);
}


//  -- END OF FILE --
