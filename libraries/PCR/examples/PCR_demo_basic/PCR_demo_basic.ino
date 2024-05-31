//
//    FILE: PCR_demo_basic.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: basic PCR demo
//     URL: https://github.com/RobTillaart/ACD10


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

  pcr.setDenature(94.5, 1000);   //  temp, ms
  pcr.setAnnealing(54.2, 1000);  //  temp, ms
  pcr.setExtension(75.0, 1000);  //  temp, ms

  pcr.reset(5);  //  iterations.

  //  endless loop
  while (true)
  {
    float temp = getTemperature();
    pcr.process(temp);

    if (pcr.iterationsLeft() == 0)
    {
      //  optional break out of loop or stay in HOLD state;
      //  display end state reached, ring a bell etc.
      //  break;
    }
  }
}


void loop()
{
}



//  -- END OF FILE --
