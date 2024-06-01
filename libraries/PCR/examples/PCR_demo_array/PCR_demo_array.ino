//
//    FILE: PCR_demo_array.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: extended PCR demo, adds initialization, elongation and final hold
//     URL: https://github.com/RobTillaart/PCR
//
//  adjust timing and temperature.

#include "PCR.h"

//  heatPin, coolPin
PCR pcr[3] = { PCR(8, 9), PCR(10, 11), PCR(12, 13) };


float getTemperature(int i)
{
  return 65 + i;  // just dummy for now.
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
  pcr[0].setInitial(98, 10000);      //  temp, ms
  pcr[0].setDenature(94.5, 5000);    //  temp, ms
  pcr[0].setAnnealing(54.2, 2000);   //  temp, ms
  pcr[0].setExtension(75.0, 3000);   //  temp, ms
  pcr[0].setElongation(75.0, 3000);  //  temp, ms
  pcr[0].setHold(8.0);               //  temp only

  pcr[1].setInitial(97, 8000);
  pcr[1].setDenature(94, 4000);
  pcr[1].setAnnealing(54, 2000);
  pcr[1].setExtension(70.0, 2000);
  pcr[1].setElongation(70.0, 2000);
  pcr[1].setHold(8.0);

  pcr[2].setInitial(96, 15000);
  pcr[2].setDenature(93, 8000);
  pcr[2].setAnnealing(53, 4000);
  pcr[2].setExtension(75.0, 4000);
  pcr[2].setElongation(75.0, 4000);
  pcr[2].setHold(8.0);

  pcr[0].reset(15);  //  iterations.
  pcr[1].reset(15);
  pcr[2].reset(15);
  Serial.print("Estimated time (ms): ");
  Serial.print(pcr[0].timeLeft());
  Serial.print("\t");
  Serial.print(pcr[1].timeLeft());
  Serial.print("\t");
  Serial.print(pcr[2].timeLeft());
  Serial.print("\n");

  while (true)
  {
    for (int i = 0; i < 3; i++)
    {
      float temp = getTemperature(i);
      pcr[i].process(temp);
    }
  }

  Serial.println("done");
}


void loop()
{
}



//  -- END OF FILE --
