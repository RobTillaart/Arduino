//
//    FILE: PCR_demo_extended.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: extended PCR demo, adds initialization, elongation and final hold
//     URL: https://github.com/RobTillaart/PCR
//
//  adjust timing and temperature.

#include "PCR.h"


PCR pcr(8, 9);  //  heatPin, coolPin


float getTemperature()
{
  return 65;
}

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("PCR_LIB_VERSION: ");
  Serial.println(PCR_LIB_VERSION);
  Serial.println();

  //  configure all phases
  pcr.setInitial(98, 10);      //  temp, seconds
  pcr.setDenature(94.5, 5);    //  temp, seconds
  pcr.setAnnealing(54.2, 2);   //  temp, seconds
  pcr.setExtension(75.0, 3);   //  temp, seconds
  pcr.setElongation(75.0, 5);  //  temp, seconds
  pcr.setHold(8.0);            //  temp only

  pcr.reset(15);  //  iterations.
  Serial.print("Estimated time (ms): ");
  Serial.println(pcr.timeLeft());

  while (pcr.iterationsLeft() > 0)
  {
    float temp = getTemperature();
    pcr.process(temp);
  }

  Serial.println("done");
}


void loop()
{
}



//  -- END OF FILE --
