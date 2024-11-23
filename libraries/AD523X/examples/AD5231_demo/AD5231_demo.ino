//
//    FILE: AD5231_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/AD523X


#include "AD523X.h"

uint32_t start, stop;


//  select, reset, dataIn, dataOut, clock == SOFTWARE SPI
//  AD5231 pot(10, 255, 7, 8, 9);

//  select, reset, &SPI === HW SPI UNO clock = 13, data = 11
AD5231 pot = AD5231(6, 7, &SPI);


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

  Serial.println("511");
  pot.setValue(0, 511);
  delay(2000);

  Serial.println("1023");
  pot.setValue(0, 1023);
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
    pot.setValue(i);
  }
  stop = micros();
  Serial.print("1000 x setValue(value):\t");
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
