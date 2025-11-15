//
//    FILE: ADC122S_read_2_channel.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo triple read
//     URL: https://github.com/RobTillaart/ADC08XS


#include "ADC08XS.h"

//  Arduino UNO
const int dataout = 11;
const int datain = 12;
const int clockPin = 13;

ADC122S adc;  //  use HWSPI
// ADC122S adc(datain, dataout, clockPin);  //  use SWSPI

uint16_t val;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("ADC08XS_LIB_VERSION: ");
  Serial.println(ADC08XS_LIB_VERSION);
  Serial.println();

  if (adc.usesHWSPI())
  {
    SPI.begin();
  }

  adc.begin(4);  //  select pin
  // adc.setSPIspeed(4000000);

  Serial.println(adc.maxChannel());
  Serial.println(adc.maxValue());
}


void loop()
{
  val = adc.read(0);
  Serial.print("0\t");
  Serial.print(val);
  val = adc.read(0);
  Serial.print("\t");
  Serial.print(val);
  val = adc.read(0);
  Serial.print("\t");
  Serial.println(val * 3.7032 / 4095, 4);  //  adjust voltage ...


  val = adc.read(1);
  Serial.print("1\t");
  Serial.print(val);
  val = adc.read(1);
  Serial.print("\t");
  Serial.print(val);
  val = adc.read(1);
  Serial.print("\t");
  Serial.println(val);

  delay(1000);
}


//  -- END OF FILE --
