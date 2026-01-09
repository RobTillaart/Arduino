//
//    FILE: SRF05_determine_speed_of_sound.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo distance sensor
//     URL: https://github.com/RobTillaart/SRF05
//
//  Place two distance sensor at an exact distance of each other.
//  In the code below 500 millimetre is used.
//
//  Assign all trigger pins of one pair to the same pin.
//  By reading the duration of both sensors and subtract them and
//  divide by two (single path) one can determine the speed of the wind.
//
//  With one pair one need to measure in the direction of the wind.
//  By doing the measurements with 2 pairs at a 90 degree angle and
//  some vector math one can get the speed of the wind at any angle.
//
//  Be aware that if the devices aren't connected well it may block.
//
//  To be tested with hardware.


#include "SRF05.h"

const int trigger1 = 7;
const int trigger2 = 8;
//  to investigate if echo pins can be shared.
const int echo1 = 9;
const int echo2 = 10;
const int echo3 = 11;
const int echo4 = 12;

SRF05 SRF_A1(trigger1, echo1);
SRF05 SRF_A2(trigger1, echo2);
SRF05 SRF_B1(trigger2, echo3);
SRF05 SRF_B2(trigger2, echo4);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("SRF05_LIB_VERSION: ");
  Serial.println(SRF05_LIB_VERSION);
  Serial.println();

  //  correct for temp and humidity
  //  SRF_A1.setCorrectionFactor(1.035);
  //  SRF_A2.setCorrectionFactor(1.035);
  //  SRF_B1.setCorrectionFactor(1.035);
  //  SRF_B2.setCorrectionFactor(1.035);
}


void loop()
{
  //  first pair
  float s1 = SRF_A1.determineSpeedOfSound(0.500);  //  500 millimetre
  float s2 = SRF_A2.determineSpeedOfSound(0.500);  //  500 millimetre
  float sA = (s1 - s2) / 2;

  //  second pair
  s1 = SRF_B1.determineSpeedOfSound(0.500);  //  500 millimetre
  s2 = SRF_B2.determineSpeedOfSound(0.500);  //  500 millimetre
  float sB = (s1 - s2) / 2;
  float result = hypot(sA, sB);
  float angle = atan2(sA, sB);

  //  optional one can add a low pass filter to average the measurements.

  // Serial.print(millis());
  //  Serial.print('\t');
  Serial.print(sA);
  Serial.print('\t');
  Serial.print(sB);
  Serial.print('\t');
  Serial.print(angle);
  Serial.print('\t');
  Serial.println(result);
  delay(100);
}


//  -- END OF FILE --
