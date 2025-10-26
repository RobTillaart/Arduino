//
//    FILE: logicAnalyzer_4_channel_inject.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test mix sampling and injecting
//     URL: https://github.com/RobTillaart/logicAnalyzer
//
//  EXPERIMENTAL - use Serial plotter

#include "logicAnalyzer.h"


logicAnalyzer LA;

uint8_t dataPins[] = { 8, 9, 10, 11 };
uint32_t rawData = 0;

void setup()
{
  Serial.begin(1000000);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("LOGICANALYZER_LIB_VERSION: ");
  Serial.println(LOGICANALYZER_LIB_VERSION);
  Serial.println();

  LA.configPins(dataPins, 4);
  LA.setChannels(10);  //  4 datachannels + 2 empty lines + 4 inject.
}


void loop()
{
  //  generate random raw data
  rawData = random(16) << 6;  //  lower 4 lines (apparently)
  //  sample IO lines.
  rawData |= LA.sample();   //  upper 4 lines (apparently)
  //  inject
  LA.inject(rawData);
  //  plot
  LA.plot();
  //  if (millis() >= 10000)
  //  {
  //    Serial.println(LA.getCount());
  //    while (1);
  //  }
}


//  -- END OF FILE --
