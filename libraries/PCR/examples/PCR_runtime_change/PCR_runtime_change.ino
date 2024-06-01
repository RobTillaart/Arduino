//
//    FILE: PCR_demo_runtime_change.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: PCR demo, changing parameters run time.
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
  pcr.setElongation(75.0, 3);  //  temp, seconds
  pcr.setHold(8.0);            //  temp only

  pcr.reset(10);  //  iterations.
  Serial.print("Estimated time (seconds): ");
  Serial.println(pcr.timeLeft());

  bool flagFive = false;
  while (pcr.iterationsLeft() > 0)
  {
    float temp = getTemperature();
    pcr.process(temp);

    //  increase time for last 5 iterations.
    if ((pcr.iterationsLeft() == 5) && (flagFive == false))
    {
      flagFive = true;
      pcr.setDenature(94.5, 7.5);     //  temp, seconds
      pcr.setAnnealing(54.2, 4.25);   //  temp, seconds
      pcr.setExtension(75.0, 5.75);   //  temp, seconds
      Serial.print("Estimated time (seconds): ");
      Serial.println(pcr.timeLeft());
    }
  }

  Serial.println("done");
}


void loop()
{
}



//  -- END OF FILE --
