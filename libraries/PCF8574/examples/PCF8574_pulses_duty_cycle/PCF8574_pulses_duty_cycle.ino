//
//    FILE: PCF8574_pulses_duty_cycle.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo 8 channel pulses with duty cycle
//     URL: https://github.com/RobTillaart/PCF8574
//          https://github.com/RobTillaart/printHelpers
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
//  high- and lowTimes can be adjusted to your needs
//  optional make time arrays uint8_t or uint32_t
//  times are in milliseconds, period[i] is highTimes[i] + lowTimes[i]
//  can be derived from frequency (period = 1000 / frequency)
//  low = dc * period; high = period - low;
uint16_t highTimes[8] = { 100, 10, 40, 75, 200, 1000, 1, 99 };
uint16_t lowTimes[8]  = { 10, 100, 30, 40, 50, 60, 1, 80 };
uint32_t lastTimes[8] = { 0 };
uint8_t val = 0x00;

uint32_t lastCheck = 0;


void setup()
{
  Serial.begin(500000);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("PCF8574_LIB_VERSION: ");
  Serial.println(PCF8574_LIB_VERSION);
  Serial.println();

  Wire.begin();
  Wire.setClock(400000);

  PCF_01.begin();
  PCF_01.write8(val);
}


void loop()
{
  uint32_t now = millis();

  //  update at most once per millisecond.
  if (now - lastCheck > 0)
  {
    lastCheck = now;
    uint8_t previous = val;
    uint8_t mask = 1;
    for (int i = 0; i < 8; i++, mask <<= 1)
    {
      uint8_t state = (val & mask) > 0;
      uint16_t last = now - lastTimes[i];
      //  LOW
      if ((state == 0) && (last >= lowTimes[i]))
      {
        lastTimes[i] = now;
        val ^= mask;
      }
      else if ((state == 1) && (last >= highTimes[i]))
      {
        lastTimes[i] = now;
        val ^= mask;
      }
    }

    //  only update if a new value is created.
    if (val != previous)
    {
      PCF_01.write8(val);
    }
    //  Serial Monitor
    //  Serial.print(now);
    //  Serial.print("\t");
    //  Serial.println(bin(val));

    //  Serial plotter
    for (int i = 0; i < 8; i++)
    {
      int v = 5 * i;
      if (val & (1 << i)) v += 2;
      Serial.print(v);
      Serial.print("\t");
    }
    Serial.println();
  }

}


//  -- END OF FILE --
