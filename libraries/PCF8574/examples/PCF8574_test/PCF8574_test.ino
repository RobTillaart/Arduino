//
//    FILE: PCF8574_test.ino
//  AUTHOR: Rob Tillaart
//    DATE: 7-febr-2013
// PURPOSE: test PCF8574 library
//     URL: https://github.com/RobTillaart/PCF8574


#include "PCF8574.h"

PCF8574 PCF_01(0x38);


void doHigh()
{
  PCF_01.write(4, HIGH);
  int x = PCF_01.read8();
  Serial.print("Read ");
  Serial.println(x, HEX);
}


void doLow()
{
  PCF_01.write(4, LOW);
  int x = PCF_01.read8();
  Serial.print("Read ");
  Serial.println(x, HEX);
}


void doToggle()
{
  PCF_01.toggle(4);
  int x = PCF_01.read8();
  Serial.print("Read ");
  Serial.println(x, HEX);
}


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PCF8574_LIB_VERSION:\t");
  Serial.println(PCF8574_LIB_VERSION);

  Wire.begin();

  PCF_01.begin();

  int x = PCF_01.read8();
  Serial.print("Read ");
  Serial.println(x, HEX);
  delay(1000);
}


void loop()
{
  Serial.println("HLT");
  while (Serial.available() == 0);
  switch (Serial.read())
  {
    case 'H': doHigh(); break;
    case 'L': doLow(); break;
    case 'T': doToggle(); break;
  }
}


//  -- END OF FILE --

