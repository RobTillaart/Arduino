//
//    FILE: ML8511_DUV_index.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo UV sensor
//    DATE: 2020-06-21
//     URL: https://github.com/RobTillaart/ML8511
//
//        BREAKOUT
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

ML8511 light(ANALOGPIN, ENABLEPIN);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println("UV UltraViolet ML8511");

  // manually enable / disable the sensor.
  light.enable();

  light.setDUVfactor(1.80);    // calibrate your sensor

  Serial.print("\tmW cm^2");
  Serial.print("\tDUV index");
  Serial.println();
}


void loop()
{
  float UV = light.getUV();
  float DUV = light.estimateDUVindex(UV);
  Serial.print(UV, 4);
  Serial.print("\t");
  Serial.print(DUV, 1);
  Serial.println();
  delay(1000);
}


// -- END OF FILE --

