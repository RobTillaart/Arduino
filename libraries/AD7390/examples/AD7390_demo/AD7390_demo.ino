//
//    FILE: AD7390_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/AD7390


#include "AD7390.h"

uint32_t start, stop;


//  select, reset, data, clock == SOFTWARE SPI
//  AD7390 myDAC(6, 7, 11, 13);

//  select, reset, &SPI === HW SPI UNO clock = 13, data = 11
AD7390 myDAC(6, 7, &SPI);


void setup()
{
  //  while(!Serial);
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AD7390_LIB_VERSION: ");
  Serial.println(AD7390_LIB_VERSION);
  Serial.println();

  SPI.begin();
  myDAC.begin(0);

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
  myDAC.setValue(0);
  delay(2000);

  Serial.println("2047");
  myDAC.setValue(2047);
  delay(2000);

  Serial.println("4095");
  myDAC.setValue(4095);
  delay(2000);
}


//  Simple sinus
void test_sinus()
{
  Serial.println(__FUNCTION__);
  delay(10);

  start = millis();
  uint32_t i = 0;
  while (millis() - start < 10000)
  {
    int8_t value = 2047 * sin(i * TWO_PI / 100);
    myDAC.setValue(2047 + value);
    i++;
  }
}

//  straightforward sawtooth.
void test_sawtooth()
{
  Serial.println(__FUNCTION__);
  delay(10);

  start = millis();
  uint16_t i = 0;
  while (millis() - start < 25500)
  {
    if (i >= 4095) i = 0;
    myDAC.setValue(i++);  //  auto wrap is fast...
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
    myDAC.setValue(i++);  //  auto wrap is fast...
  }
  stop = micros();
  Serial.print("1000 x setValue():\t");
  Serial.println(stop - start);
  delay(10);

  volatile int x = 0;
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x += myDAC.getValue();
  }
  stop = micros();
  Serial.print("1000 x getValue():\t");
  Serial.println(stop - start);
  delay(10);
}


//  -- END OF FILE --
