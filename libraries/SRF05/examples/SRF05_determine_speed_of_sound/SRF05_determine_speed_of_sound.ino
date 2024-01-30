//
//    FILE: SRF05_determine_speed_of_sound.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo distance sensor
//    DATE: 2021-05-17
//     URL: https://github.com/RobTillaart/SRF05
//
//  place distance sensor at exactly 1 metre = 1000 millimetre of a reflecting wall
//  use setCorrectionFactor() to adjust
//  IDEA - potentiometer 0..1023 maps to 0.900 .. 1.100


#include "SRF05.h"

const int trigger = 7;
const int echo    = 6;

SRF05 SRF(trigger, echo);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("SRF05_LIB_VERSION: ");
  Serial.println(SRF05_LIB_VERSION);
  Serial.println();

  //  SRF.setCorrectionFactor(1.035);
}


void loop()
{
  static uint32_t prev = millis();
  float s = SRF.determineSpeedOfSound(1.000);  //  1000 millimetre
  uint32_t now = millis();
  Serial.print(now - prev);
  Serial.print("\t");
  Serial.print(1.000);
  Serial.print("\t");
  Serial.println(s, 1);
  prev = now;
}


//  -- END OF FILE --

