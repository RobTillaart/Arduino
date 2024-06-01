//
//    FILE: PCR_demo_aquarium.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: using PCR class to control temperature in a tropic aquarium
//     URL: https://github.com/RobTillaart/PCR
//
//  Warning: example takes a day to do one cycle. Adjust timing to see effect.


#include "PCR.h"


PCR pcr(8, 9);  //  heatPin, coolPin


float getTemperature()
{
  return 30;  //  dummy, to be elaborated.
}

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("PCR_LIB_VERSION: ");
  Serial.println(PCR_LIB_VERSION);
  Serial.println();

  //  split 86400 seconds over three temperature levels
  pcr.setDenature(32, 23200);   //  temp, seconds
  pcr.setAnnealing(29, 43200);  //  temp, seconds
  pcr.setExtension(27, 20000);  //  temp, seconds

  //  just one cycle a day.
  pcr.reset(1);
}


void loop()
{
  while (true)
  {
    float temp = getTemperature();
    pcr.process(temp);
    //  break after a full cycle / day.
    if (pcr.iterationsLeft() == 0) break;
  }
  //  do next cycle / day.
  pcr.reset(1);
}


//  -- END OF FILE --
