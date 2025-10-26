//
//    FILE: logicAnalyzer_clock_high_low.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour
//     URL: https://github.com/RobTillaart/logicAnalyzer
//
//  this example only makes a sample and plots it when the clock pin is LOW.
//

#include "logicAnalyzer.h"


logicAnalyzer LA;

uint8_t dataPins[] = { 8, 9, 10, 11 };
uint8_t clockPin = 7;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("LOGICANALYZER_LIB_VERSION: ");
  Serial.println(LOGICANALYZER_LIB_VERSION);
  Serial.println();

  LA.configPins(dataPins, 4);
  LA.configClock(clockPin);

  //  initialize internal clock state
  LA.clockChanged();

  //  while(LA.clockHIGH());  //  wait for trigger.
}


void loop()
{
  //  optional use LA.clockHIGH()
  //
  //  while instead of if gives very tight loop
  if (LA.clockLOW())
  {
    LA.sample();
    LA.plot();
  }
}


//  -- END OF FILE --
