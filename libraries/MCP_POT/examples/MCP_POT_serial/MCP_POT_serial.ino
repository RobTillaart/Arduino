//
//    FILE: MCP_POT_serial.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo control the device though serial commands.
//     URL: https://github.com/RobTillaart/MCP_POT


#include "MCP_POT.h"


//  select, reset, shutdown, data, clock == SOFTWARE SPI
MCP_POT pot(10, 11, 12, 8, 9);

//  select, reset, shutdown, &SPI === HW SPI UNO clock = 13, data = 11
// MCP_POT pot(5, 6, 7, &SPI);


long value = 0;
uint8_t pm = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  SPI.begin();
  pot.begin();
}


void loop()
{
  handleSerial();
}


void handleSerial()
{
  if (Serial.available())
  {
    uint8_t c = Serial.read();
    //  process digits
    if ((c >= '0') && (c <= '9'))
    {
      value *= 10;
      value += (c - '0');
    }
    //  set the value
    if (c == 'S')
    {
      //  incorrect conversion formula for 100 KΩ
      uint8_t ohm = value / 400;
      pot.setValue(pm, ohm);
      value = 0;
    }
    //  set minimum / zero
    if (c == 'z')
    {
      pot.setValue(pm, 0);
      value = 0;
    }
    //  set maximum
    if (c == 'M')
    {
      pot.setValue(pm, 255);
      value = 0;
    }
    //  reset both to middle
    if (c == 'R')
    {
      pot.reset();
      value = 0;
    }
    //  select pm 0
    if (c == 'A')
    {
      pm = 0;
    }
    //  select pm 1
    if (c == 'B')
    {
      pm = 1;
    }
    //  debug
    if (c == 'V')
    {
      Serial.println(value);
    }
    //  print current pot settings
    if (c == 'G')
    {
      Serial.print("POT 0 = ");
      Serial.println(pot.getValue(0));
      Serial.print("POT 1 = ");
      Serial.println(pot.getValue(1));
    }
    //  print current pot setting
    if (c == 'P')
    {
      if (pot.isPowerOn())
      {
        pot.powerOff();
        Serial.println("powerOff");
      }
      else
      {
        pot.powerOn();
        Serial.println("powerOn");
      }
    }
  }
}



//  -- END OF FILE --
