//
//    FILE: ML8511_cumulative_joule.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo UV sensor - EXPERIMENTAL
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


#include "ML8511.h"

#define ANALOGPIN     A0
#define ENABLEPIN     7

ML8511 light(ANALOGPIN, ENABLEPIN);


float joulePerCM = 0;
float interval = 2.5;   //  in seconds.

uint32_t lastTime = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.println();
  Serial.println("UV ML8511 - cumulative joule/cm2");

  // manually enable / disable the sensor.
  light.enable();

  light.setDUVfactor(1.80);    // calibrate your sensor

  Serial.println();
  Serial.print("time");
  Serial.print("\tmW/cm^2");
  Serial.print("\tDUV idx");
  Serial.print("\tcum j/cm^2");
  Serial.println();
}


void loop()
{
  //  make a measurement and a print every interval.
  if (millis() - lastTime >= (interval * 1000))
  {
    lastTime += (interval * 1000);
    float UV = light.getUV();
    float DUV = light.estimateDUVindex(UV);
    joulePerCM += UV * interval;

    Serial.print(lastTime * 0.001, 1);
    Serial.print("\t");
    Serial.print(UV, 3);
    Serial.print("\t");
    Serial.print(DUV, 1);
    Serial.print("\t");
    Serial.print(joulePerCM, 1);
    Serial.println();
  }
}


//  -- END OF FILE --
