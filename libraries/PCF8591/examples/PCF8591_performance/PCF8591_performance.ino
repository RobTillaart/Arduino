//
//    FILE: PCF8591_demo.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo
//    DATE: 2020-07-22
//     URL: https://github.com/RobTillaart/PCF8591

// NOTE: output is written in markdown format of a table
//       can be changed to tab based or comma based output

#include "PCF8591.h"

PCF8591 dev(0x48);

uint32_t start, stop;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  Wire.begin();

#if defined (ESP8266) || defined(ESP32)
  dev.begin(21, 22);  // adjust pins if needed.
#else
  dev.begin();
#endif

  if (! dev.isConnected())
  {
    Serial.println("\nFailed to connect\n");
    // while(1);
  }
  delay(100);

  test1();
  test2();
}

void loop()
{
}

/////////////////////////////////////////////////////////////////////////

void test1()
{
  Serial.println(F("| - Wire clock KHz - | - analogWrite() us - | - analogRead() us - |"));
  Serial.println(F("|:----:|:----:|:----:|"));
  for (uint8_t i = 1; i < 14; i++)
  {
    uint32_t clk = 50000UL * i;
    Serial.print("| ");
    Serial.print(clk/1000);
    Wire.setClock(clk);
    test_DAC();
    delay(10);
    test_ADC();
    delay(10);
    Serial.println(" |");
  }
  Serial.println();
}

void test2()
{
  Serial.println(F("| - Wire clock KHz - | - analogWrite() OK% - | - analogRead() OK% - |"));
  Serial.println(F("|:----:|:----:|:----:|"));
  for (uint8_t i = 1; i < 14; i++)
  {
    uint32_t clk = 50000UL * i;
    Serial.print("| ");
    Serial.print(clk/1000);
    Wire.setClock(clk);
    test_DAC_error();
    delay(10);
    test_ADC_error();
    delay(10);
    Serial.println(" |");
  }
  Serial.println();
}

void test_DAC()
{
  dev.enableDAC();
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    uint8_t val = i % 127;
    dev.analogWrite(val);
  }
  stop = micros();
  dev.disableDAC();
  Serial.print(" | ");
  Serial.print((stop - start) * 0.001);
}

void test_ADC()
{
  volatile uint8_t x = 0;
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x = dev.analogRead(2);
  }
  stop = micros();
  Serial.print(" | ");
  Serial.print((stop - start) * 0.001);
}

void test_DAC_error()
{
  float perc = 0;
  dev.enableDAC();
  for (int i = 0; i < 1000; i++)
  {
    uint8_t val = i % 127;
    dev.analogWrite(val);
    if (dev.lastError() == PCF8591_OK) perc += 0.1;
  }
  dev.disableDAC();
  Serial.print(" | ");
  Serial.print(perc);
}

void test_ADC_error()
{
  float perc = 0;
  volatile uint8_t x = 0;
  for (int i = 0; i < 1000; i++)
  {
    x = dev.analogRead(2);
    if (dev.lastError() == PCF8591_OK) perc += 0.1;
  }
  Serial.print(" | ");
  Serial.print(perc);
}

// -- END OF FILE --
