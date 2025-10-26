//
//    FILE: logicAnalyzer_inject.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour of inject
//     URL: https://github.com/RobTillaart/logicAnalyzer
//

#include "logicAnalyzer.h"


logicAnalyzer LA;

uint32_t rawData = 0;

void setup()
{
  Serial.begin(1000000);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("LOGICANALYZER_LIB_VERSION: ");
  Serial.println(LOGICANALYZER_LIB_VERSION);
  Serial.println();

  //  needed to set channels for inject(), 32 is the maximum.
  //  LA.setChannels(8);
  LA.setChannels(32);
}


void loop()
{
  //  generate random raw data
  int x = random(32);
  rawData ^= (1UL << x);
  
  LA.inject(rawData);
  LA.plot();
//  if (millis() >= 10000)
//  {
//    Serial.println(LA.getCount());
//    while (1);
//  }
}


//  -- END OF FILE --
