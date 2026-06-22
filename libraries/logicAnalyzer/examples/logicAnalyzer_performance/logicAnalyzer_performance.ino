//
//    FILE: logicAnalyzer_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/logicAnalyzer


#include "logicAnalyzer.h"


logicAnalyzer LA;

uint8_t dataPins[] = { 8, 9, 10, 11 };

uint32_t start, stop;


void setup()
{
  Serial.begin(1000000);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("LOGICANALYZER_LIB_VERSION: ");
  Serial.println(LOGICANALYZER_LIB_VERSION);
  Serial.println();
  delay(100);

  LA.configPins(dataPins, 4);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    LA.sample();
    LA.plot();
  }
  stop = micros();
  Serial.print("TIME:\t");
  Serial.println(stop - start);
  Serial.print("COUNT:\t");
  Serial.println(LA.getCount());
  delay(5000);
}


void loop()
{
}


//  -- END OF FILE --
