//
//    FILE: PCF8591_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2020-07-22
//     URL: https://github.com/RobTillaart/PCF8591


#include "PCF8591.h"

PCF8591 dev(0x48);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PCF8591_LIB_VERSION: ");
  Serial.println(PCF8591_LIB_VERSION);

  Wire.begin();
  Wire.setClock(100000UL);

  dev.begin();
}


void loop()
{
  test_DAC();
  delay(1000);
  test_ADC_mode(0);
  delay(1000);

  //  differential modes, check datasheet
  test_ADC_mode(1);
  delay(1000);
  test_ADC_mode(2);
  delay(1000);
  test_ADC_mode(3);
  delay(1000);
}


void test_DAC()
{
  Serial.println(__FUNCTION__);
  Serial.println("--------------");
  dev.enableDAC();
  for (int i = 0; i < 5000; i++)
  {
    uint8_t val = 127 + 127 * sin(i * 0.01);
    Serial.println(val);
    dev.write(val);
    delay(1);              //  just to slow the effect
  }
  dev.disableDAC();
  Serial.println();
}


void test_ADC_mode(uint8_t mode)
{
  uint8_t channels[] = {4, 3, 3, 2 };  //  channels per mode
  Serial.println(__FUNCTION__);
  Serial.println("--------------");
  Serial.println("CH0\tCH1\tCH2\tCH3");
  for (int m = 0; m < 20; m++)
  {
    for (uint8_t i = 0; i < channels[mode]; i++)
    {
      Serial.print(dev.read(i, mode));
      Serial.print('\t');
    }
    Serial.println();
  }
  Serial.println();
}


//  -- END OF FILE --
