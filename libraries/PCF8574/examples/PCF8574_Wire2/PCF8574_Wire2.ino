//
//    FILE: PCF8574_Wire2.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2016-04-30
//
// PUPROSE: demo 
//

#include "PCF8574.h"

// adjust addresses if needed
PCF8574 PCF(0x39, &Wire2);

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PCF8574_LIB_VERSION:\t");
  Serial.println(PCF8574_LIB_VERSION);

  if (!PCF.begin())
  {
    Serial.println("could not initialize...");
  }
  if (!PCF.isConnected())
  {
    Serial.println("=> not connected");
    while(1);
  }

  int x = PCF.read8();
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

void doHigh()
{
  PCF.write(4, HIGH);
  int x = PCF.read8();
  Serial.print("Read ");
  Serial.println(x, HEX);
}

void doLow()
{
  PCF.write(4, LOW);
  int x = PCF.read8();
  Serial.print("Read ");
  Serial.println(x, HEX);
}

void doToggle()
{
  PCF.toggle(4);
  int x = PCF.read8();
  Serial.print("Read ");
  Serial.println(x, HEX);
}


// -- END OF FILE --
