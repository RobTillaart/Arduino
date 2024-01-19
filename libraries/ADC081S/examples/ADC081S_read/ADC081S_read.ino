//
//    FILE: ADC081S_read.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/ADC081S


#include "ADC081S.h"


ADC081S adc01;        //  use HWSPI
ADC081S adc02(6, 7);  //  use SWSPI

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("ADC081S_LIB_VERSION: ");
  Serial.println(ADC081S_LIB_VERSION);

  SPI.begin();
  adc01.begin(10);
  adc02.begin(5);

  Serial.println();
  Serial.println("ADC\tMAXVALUE");
  Serial.print("adc01\t");
  Serial.println(adc01.maxValue());
  delay(10);
  start = micros();
  uint16_t val = adc01.read();
  stop = micros();
  Serial.print("hwspi:\t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println(val);

  Serial.print("adc02\t");
  Serial.println(adc02.maxValue());
  delay(10);
  start = micros();
  val = adc02.read();
  stop = micros();
  Serial.print("swspi:\t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println(val);

  Serial.println();
}


void loop()
{
  Serial.print("adc01:\t");
  uint16_t val = adc01.read();
  Serial.println(val);

  Serial.print("adc02:\t");
  val = adc02.read();
  Serial.println(val);

  delay(5000);
}


//  -- END OF FILE --
