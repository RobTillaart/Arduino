//
//    FILE: PCF8574_pulses.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo 8 channel pulses
//     URL: https://github.com/RobTillaart/PCF8574
//     URL: https://github.com/RobTillaart/printHelpers
//
//    NOTE: HIGH BAUDRATE OVER SERIAL
//          using Serial prints reduces performance


#include "PCF8574.h"
#include "printHelpers.h"

PCF8574 PCF_01(0x38);


//  This version is based upon millis() as I2C writes take time.
//  An SPI variant with e.g. MCP23S08 would write definitely faster.
//  time step with SPI might be in 100 micros range.
//
//  toggleTimes can be adjusted to your needs
uint32_t toggleTimes[8] = { 100, 200, 40, 75, 200, 1000, 666, 99 };
uint32_t lastTimes[8] = { 0 };
uint8_t val = 0x00;


void setup()
{
  Serial.begin(500000);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("PCF8574_LIB_VERSION: ");
  Serial.println(PCF8574_LIB_VERSION);
  Serial.println();

  Wire.begin();

  PCF_01.begin();
  PCF_01.write8(val);
}


void loop()
{
  uint32_t now = millis();
  uint8_t previous = val;
  for (int i = 0; i < 8; i++)
  {
    if ( now - lastTimes[i] >= toggleTimes[i])
    {
      lastTimes[i] = now;
      val ^= (1 << i);
    }
  }

  //  only update if a new value is created.
  if (val != previous)
  {
    PCF_01.write8(val);
  }
  //  Serial Monitor
  //    Serial.print(now);
  //    Serial.print("\t");
  //    Serial.println(bin(val));

  //  Serial plotter
  for (int i = 0; i < 8; i++)
  {
    int v = 5 * i;
    if (val & (1 << i)) v += 2;
    Serial.print(v);
    Serial.print("\t");
  }
  Serial.println();
  delay(5);
}


//  -- END OF FILE --
