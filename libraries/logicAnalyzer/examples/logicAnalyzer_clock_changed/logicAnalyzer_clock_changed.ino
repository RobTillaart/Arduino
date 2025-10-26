//
//    FILE: logicAnalyzer_clock_changed.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour
//     URL: https://github.com/RobTillaart/logicAnalyzer
//
//  this example only makes a sample and plots it when the clock pin changes.
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
}


void loop()
{
  if (LA.clockChanged())
  {
    LA.sample();
    LA.plot();
    //  plot extra pixels per clock pulse. (might look better).
    //  for (int i = 0; i < 4; i++) LA.plot();
  }
}


//  -- END OF FILE --
