//
//    FILE: ADC122S_stand_alone.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test
//     URL: https://github.com/RobTillaart/ADC08XS


#include "Arduino.h"
#include "SPI.h"


uint16_t val;

uint8_t selectPin = 4;


int readADC(uint8_t channel)
{
  uint8_t chan = 0x08;
  if (channel != 0) chan = 0x00;

  digitalWrite(selectPin, LOW);
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE3));
  uint16_t data = SPI.transfer(chan);
  data <<= 8;
  data += SPI.transfer(0);
  SPI.endTransaction();
  digitalWrite(selectPin, HIGH);

  return data;
}


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  SPI.begin();

  pinMode(selectPin, OUTPUT);
  digitalWrite(selectPin, HIGH);
}


void loop()
{
  val = readADC(0);
  Serial.print("0\t");
  Serial.print(val);
  delay(1000);

  val = readADC(0);
  Serial.print("\t");
  Serial.print(val);
  delay(1000);

  val = readADC(0);
  Serial.print("\t");
  Serial.println(val);
  delay(1000);

  val = readADC(1);
  Serial.print("1\t");
  Serial.print(val);
  delay(1000);

  val = readADC(1);
  Serial.print("\t");
  Serial.print(val);
  delay(1000);

  val = readADC(1);
  Serial.print("\t");
  Serial.println(val);
  delay(1000);

  delay(2000);
}


//  -- END OF FILE --
