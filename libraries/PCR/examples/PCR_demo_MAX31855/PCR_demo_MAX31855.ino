//
//    FILE: PCR_demo_MAX31855.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: PCR demo, using a thermocouple MAX31855 as temperature sensor.
//     URL: https://github.com/RobTillaart/PCR
//
//  adjust pins to your hardware setup.


#include "PCR.h"
PCR pcr(8, 9);  //  heatPin, coolPin


//    https://github.com/RobTillaart/MAX31855_RT
#include "MAX31855.h"
uint8_t selectPin = 7;
MAX31855 thermoCouple(selectPin, &SPI);  //  HW SPI


float getTemperature()
{
  //  no status or error handling yet
  thermoCouple.read();;
  float temp = thermoCouple.getTemperature();
  return temp;
}


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("PCR_LIB_VERSION: ");
  Serial.println(PCR_LIB_VERSION);
  Serial.print("MAX31855_VERSION: ");
  Serial.println(MAX31855_VERSION);
  Serial.println();


  //  initialize the temperature sensor
  SPI.begin();
  thermoCouple.begin();
  delay(1000);  //  wait a second to get a first reading.


  //  configure PCR process
  //  adjust timing and temperature to your needs.
  pcr.setInitial(98, 10);      //  temperature, seconds
  pcr.setDenature(94.5, 5);    //  temperature, seconds
  pcr.setAnnealing(54.2, 2);   //  temperature, seconds
  pcr.setExtension(75.0, 3);   //  temperature, seconds
  pcr.setElongation(75.0, 3);  //  temperature, seconds
  pcr.setHold(8.0);            //  temperature only

  pcr.reset(15);  //  iterations.
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
