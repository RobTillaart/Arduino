//
//    FILE: ADC08XS_read.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/ADC08XS


#include "ADC08XS.h"


ADC082S adc01;           //  use HWSPI
ADC124S adc02(5, 6, 7);  //  use SWSPI

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("ADC08XS_LIB_VERSION: ");
  Serial.println(ADC08XS_LIB_VERSION);

  SPI.begin();

  adc01.begin(10);
  adc02.begin(4);

  Serial.println();
  Serial.println("ADC\tMAXVALUE");
  Serial.print("adc01\t");
  Serial.println(adc01.maxValue());
  delay(10);
  start = micros();
  uint16_t val = adc01.read(0);
  stop = micros();
  Serial.print("hwspi:\t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println(val);

  Serial.print("adc02\t");
  Serial.println(adc02.maxValue());
  delay(10);
  start = micros();
  val = adc02.read(0);
  stop = micros();
  Serial.print("swspi:\t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println(val);

  Serial.println();
}


void loop()
{
  uint16_t val0 = adc01.read(0);
  uint16_t val1 = adc01.read(1);
  Serial.print("adc01:\t");
  Serial.print(val0);
  Serial.print("\t");
  Serial.println(val1);

  Serial.print("adc02:\t");
  for (uint8_t ch = 0 ; ch < adc02.maxChannel(); ch++)
  {
    uint16_t val = adc02.read(ch);
    Serial.print(val);
    Serial.print("\t");
  }
  Serial.println();

  delay(5000);
}


//  -- END OF FILE --
