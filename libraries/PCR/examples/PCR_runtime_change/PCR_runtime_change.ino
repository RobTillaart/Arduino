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


  //  configure PCR process
  //  adjust timing and temperature to your needs.
  pcr.setInitial(98, 10);      //  temperature, seconds
  pcr.setDenature(94.5, 5);    //  temperature, seconds
  pcr.setAnnealing(54.2, 2);   //  temperature, seconds
  pcr.setExtension(75.0, 3);   //  temperature, seconds
  pcr.setElongation(75.0, 3);  //  temperature, seconds
  pcr.setHold(8.0);            //  temperature only

  pcr.reset(10);  //  iterations.
  Serial.print("Estimated time (seconds): ");
  Serial.println(pcr.timeLeft());

  //  run the PCR process.
  bool flagFive = false;
  while (pcr.getPCRState() != PCR_STATE_HOLD)
  {
    float temp = getTemperature();
    pcr.process(temp);

    //  increase time for last 5 iterations.
    if ((pcr.iterationsLeft() == 5) && (flagFive == false))
    {
      flagFive = true;
      pcr.setDenature(94.5, 7.5);     //  temperature, seconds
      pcr.setAnnealing(54.2, 4.25);   //  temperature, seconds
      pcr.setExtension(75.0, 5.75);   //  temperature, seconds
      Serial.print("Estimated time (seconds): ");
      Serial.println(pcr.timeLeft());
    }
  }

  Serial.println("PCR done");
}


void loop()
{
  // One needs to call next two lines to ensure temperature in HOLD state
  float temp = getTemperature();
  pcr.process(temp);

  delay(1000);
}



//  -- END OF FILE --
