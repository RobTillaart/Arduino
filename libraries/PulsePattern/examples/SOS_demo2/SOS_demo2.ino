//
//    FILE: SOS_demo2.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2012-11-23
// PURPOSE: demo of the PulsePattern Library
//          uses timer1
//     URL: https://github.com/RobTillaart/PulsePattern


#include "PulsePattern.h"


//  a pattern consists of durations of LOW and HIGH periods
//  so the first line of the SOSpattern is
//  500 units LOW, 500 units HIGH etc.
//  for a duty cycle of 50% LOW and HIGH should have equal periods
//  NOTE max period = 4095.
//       min period = about 12
uint16_t SOSpattern[] =
{
  500,500,500,500,500,1500,      //  SOS in Morse-code
  1500,500,1500,500,1500,1500,
  500,500,500,500,500,1500
};


uint8_t patternSize = 18;
uint8_t startLevel = LOW;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.println("PULSEPATTERN_LIB_VERSION: ");
  Serial.println(PULSEPATTERN_LIB_VERSION);
  Serial.println();

  //  as the prescaler = 1024 the periods of the pattern are a
  //  few percent less than a millisecond
  PPGenerator.init(13, SOSpattern, patternSize, startLevel, PRESCALE_1024);
  PPGenerator.start();
}


void loop()
{
  //  dummy code
  Serial.println(millis());
  delay(1000);
}


//  -- END OF FILE --

