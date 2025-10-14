//
//    FILE: PCR_demo_extended.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: extended PCR demo, adds initialization, elongation and final hold
//     URL: https://github.com/RobTillaart/PCR
//
//  adjust timing and temperature.

#include "PCR.h"


PCR pcr(8, 9, 13);  //  heatPin, coolPin, signalPin (built-in LED UNO = 13)


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
  pcr.setElongation(75.0, 5);  //  temperature, seconds
  pcr.setHold(8.0);            //  temperature only

  pcr.reset(5);  //  iterations.
  Serial.print("Estimated time (seconds): ");
  Serial.println(pcr.timeLeft());

  //  run the PCR process.
  while (pcr.getPCRState() != PCR_STATE_HOLD)
  {
    float temp = getTemperature();
    pcr.process(temp);
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
