//
//    FILE: MCP23008_digitalWrite.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test MCP23008 library
//     URL: https://github.com/RobTillaart/MCP23008


#include "MCP23008.h"


MCP23008 MCP(0x27);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MCP23008_LIB_VERSION: ");
  Serial.println(MCP23008_LIB_VERSION);
  Serial.println();
  delay(100);

  Wire.begin();

  MCP.begin();

  pinMode(8, INPUT);     //  use pin8 to read back MCP.pin0

  MCP.pinMode8(0x00);    //  0 = output,  1 = input
  MCP.write8(0xFF);
  Wire.setClock(100000);

  Serial.println("TEST write1(0) - note bitorder");
  for (int i = 0; i < 8; i++)
  {
    MCP.write1(0, i % 2);          //  alternating HIGH/LOW
    Serial.print(i % 2);
    Serial.print(digitalRead(8));  //  read back status.
    Serial.print('\t');
    delay(250);
  }
  MCP.write1(0, LOW);
  Serial.println();
  Serial.println();


  Serial.println("TEST read back");
  for (int pin = 0; pin < 8; pin++)
  {
    int val = MCP.read1(pin);
    Serial.print(val);
    Serial.print('\t');
  }
  Serial.println();
  Serial.println(MCP.read8(), HEX);
  Serial.println();


  Serial.println("TEST write1(pin) - note bitorder");
  for (int pin = 0; pin < 8; pin++)
  {
    MCP.write1(pin, 1 - pin % 2);  //  alternating HIGH/LOW
    Serial.print(1 - pin % 2);
    Serial.print('\t');
  }
  Serial.println();
  Serial.println();


  Serial.println("TEST read back");
  Serial.println(digitalRead(8));
  for (int pin = 0; pin < 8; pin++)
  {
    int val = MCP.read1(pin);
    Serial.print(val);
    Serial.print('\t');
  }
  Serial.println();
  Serial.println(MCP.read8(), HEX);
  Serial.println();
}


void loop()
{
}


//  -- END OF FILE --

