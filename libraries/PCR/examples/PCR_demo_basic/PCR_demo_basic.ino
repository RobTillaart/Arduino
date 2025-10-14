//
//    FILE: PCR_demo_basic.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: basic PCR demo
//     URL: https://github.com/RobTillaart/PCR


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

  //  configure PCR process
  //  adjust timing and temperature to your needs.
  pcr.setDenature(94.5, 1);   //  temperature, seconds
  pcr.setAnnealing(54.2, 2);  //  temperature, seconds
  pcr.setExtension(75.0, 3);  //  temperature, seconds

  pcr.reset(5);  //  iterations.

  //  endless loop
  while (true)
  {
    float temp = getTemperature();
    pcr.process(temp);

    if (pcr.getPCRState() == PCR_STATE_HOLD)
    {
      //  optional break out of loop or stay in HOLD state;
      //  display end state reached, ring a bell etc.
      //  break;
    }
  }
}


void loop()
{
  // One needs to call next two lines to ensure temperature in HOLD state
  float temp = getTemperature();
  pcr.process(temp);

  delay(1000);
}



//  -- END OF FILE --
