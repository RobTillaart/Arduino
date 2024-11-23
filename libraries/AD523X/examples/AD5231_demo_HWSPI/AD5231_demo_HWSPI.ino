//
//    FILE: AD5231_demo_HWSPI.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/AD523X


#include "AD523X.h"


uint32_t start, stop;

//  select, reset, dataIn, dataOut, clock == SOFTWARE SPI
//  AD5235 pot(10, 255, 7, 8, 9);  //  no reset.
AD5231 pot = AD5231(6, 7);     //  HW SPI by default


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

  Serial.print("\tusesHWSPI:\t");
  Serial.println(pot.usesHWSPI());

  test_sinus();
  test_sawtooth();

  pot.setSPIspeed(500000);
  test_timing();
  pot.setSPIspeed(1000000);
  test_timing();
  pot.setSPIspeed(2000000);
  test_timing();
  pot.setSPIspeed(4000000);
  test_timing();
  pot.setSPIspeed(8000000);
  test_timing();
  pot.setSPIspeed(16000000);    //  no effect on 16 MHz UNO
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
    pot.setValue(1, 512 + value / 2);
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
  for (int i = 0; i < 250; i++)
  {
    x += pot.getValue(0);
    // x += pot.getValue(1);
  }
  stop = micros();
  Serial.print("1000 x getValue():\t");
  Serial.println(stop - start);
  delay(10);
}


//  -- END OF FILE --
