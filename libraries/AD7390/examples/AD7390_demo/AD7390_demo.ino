//
//    FILE: AD7390_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/AD7390


#include "AD7390.h"

uint32_t start;

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

  test_extremes();
  test_sinus();
  test_sawtooth();

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

  Serial.println("2047");
  myDAC.setValue(2047);

  Serial.println("4095");
  myDAC.setValue(4095);
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
    int16_t value = 2047 * sin(i * TWO_PI / 100);
    myDAC.setValue(2047 + value);
    Serial.println(2047 + value);
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
  while (millis() - start < 10000)
  {
    if (i >= 4095) i = 0;
    myDAC.setValue(i++);
    Serial.println(i);
    delay(1);
  }
}


//  -- END OF FILE --
