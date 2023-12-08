//
//    FILE: mcp4725_multiple.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test MCP4725 lib
//     URL: https://github.com/RobTillaart/MCP4725
//
//  simple example to control more than 2 devices over
//  a single I2C bus without multiplexer.
//  The A0 address pin is used as a SELECT pin.
//
//  Every MCP device has its own object and can be 
//  accessed accordingly.
//
//  To be tested / confirmed working with hardware.


#include "Wire.h"
#include "MCP4725.h"

//  assume the 4 devices have the same A1 and A2
//  hard-coded address bits. (par 7.2 datasheet)
//  we will access all devices with as 0x63.
MCP4725 MCP0(0x63);
MCP4725 MCP1(0x63);
MCP4725 MCP2(0x63);
MCP4725 MCP3(0x63);

//  connect the select pins to the A0 pins
//  of the four MCP4725's
uint8_t selectPin[4] = { 4, 5, 6, 7 };


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MCP4725_VERSION: ");
  Serial.println(MCP4725_VERSION);

  Wire.begin();

  for (int i = 0; i < 4; i++)
  {
    pinMode(selectPin[i], OUTPUT);
    digitalWrite(selectPin[i], LOW);
  }

  select(0);
  MCP0.begin();
  select(1);
  MCP1.begin();
  select(2);
  MCP2.begin();
  select(3);
  MCP3.begin();
}


void select(uint8_t nr)
{
  for (int i = 0; i < 4; i++)
  {
    if (i != nr) digitalWrite(selectPin[i], LOW);
    else         digitalWrite(selectPin[i], HIGH);
  }
}


void loop()
{
  int x = analogRead(A0);  //  to create an output value.

  //  select one DAC and set the value.
  select(0);
  MCP0.setValue(x);
  delay(250);

  select(1);
  MCP1.setValue(x * 2);
  delay(250);

  select(2);
  MCP2.setValue(x * 3);
  delay(250);

  select(3);
  MCP3.setValue(x * 4);
  delay(250);  
}


//  -- END OF FILE --
