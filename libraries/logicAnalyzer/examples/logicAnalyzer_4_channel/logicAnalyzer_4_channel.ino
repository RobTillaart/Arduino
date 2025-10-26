//
//    FILE: logicAnalyzer_4_channel.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/logicAnalyzer


#include "logicAnalyzer.h"


logicAnalyzer LA;

uint8_t dataPins[] = { 8, 9, 10, 11 };

void setup()
{
  Serial.begin(1000000);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("LOGICANALYZER_LIB_VERSION: ");
  Serial.println(LOGICANALYZER_LIB_VERSION);
  Serial.println();

  LA.configPins(dataPins, 4);
}


void loop()
{
  LA.sample();
  LA.plot();
  if (millis() >= 10000)
  {
    Serial.println(LA.getCount());
    while (1);
  }
}


//  -- END OF FILE --
