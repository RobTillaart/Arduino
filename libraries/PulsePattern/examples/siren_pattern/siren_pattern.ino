//
//    FILE: siren_pattern.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2012-11-23
// PURPOSE: demo of the PulsePattern Library
//          uses timer1


#include "PulsePattern.h"

// a pattern consists of durations of LOW and HIGH periods
// NOTE max period = 4095.
//      min period = about 12
uint16_t pattern[] =
{
  1500, 1500, 1400, 1400, 1300, 1300, 1200, 1200, 1100, 1100,
  1000, 1000, 900, 900, 800, 800, 700, 700, 600, 600,
  500, 500, 400, 400, 300, 300, 200, 200, 100, 100
};


uint8_t patternSize = 30;
uint8_t startLevel = LOW;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  PPGenerator.init(13, pattern, patternSize, startLevel, PRESCALE_1024);
  PPGenerator.start();
}


void loop()
{
  Serial.println(millis());
  delay(1000);
}


// -- END OF FILE --

