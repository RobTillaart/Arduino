//
//    FILE: ML8511_low_power.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo UV sensor
//    DATE: 2020-02-17
//     URL: https://github.com/RobTillaart/ML8511
//
// BREAKOUT
//      +-------+--+
//  VIN |o      +-+| mounting hole
//  3V3 |o      +-+|
//  GND |o         |
//  OUT |o         |
//   EN |o       S |  Sensor
//      +----------+
//
//   EN = ENABLE


#include <Arduino.h>
#include <ML8511.h>

#define ANALOGPIN     A0
#define ENABLEPIN     7

// to use LOW POWER mode the enable pin is mandatory.
ML8511 light(ANALOGPIN, ENABLEPIN);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println("UV UltraViolet ML8511");
}


void loop()
{
  float UV = light.getUV(LOW);   // Automatic low power.
  Serial.print(UV, 4);
  Serial.println(" mW cm^2");
  delay(1000);
}


// -- END OF FILE --

