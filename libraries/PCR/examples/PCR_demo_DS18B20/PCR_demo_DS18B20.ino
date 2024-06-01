//
//    FILE: PCR_demo_DS18B20.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: PCR demo, using DS18B20 as temperature sensor.
//     URL: https://github.com/RobTillaart/PCR
//
//  adjust pins to your hardware setup.


#include "PCR.h"
PCR pcr(8, 9);  //  heatPin, coolPin


//  https://github.com/RobTillaart/DS18B20_RT
//  http://www.pjrc.com/teensy/td_libs_OneWire
#include "DS18B20.h"

#define ONE_WIRE_BUS      2

OneWire oneWire(ONE_WIRE_BUS);
DS18B20 sensor(&oneWire);



float getTemperature()
{
  static float temp = sensor.getTempC();
  if (sensor.isConversionComplete())
  {
    temp = sensor.getTempC();
    //  request a new measurement.
    sensor.requestTemperatures();
  }
  return temp;
}


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("PCR_LIB_VERSION: ");
  Serial.println(PCR_LIB_VERSION);
  Serial.print("DS18B20_LIB_VERSION: ");
  Serial.println(DS18B20_LIB_VERSION);
  Serial.println();


  //  initialize the temperature sensor
  sensor.begin();
  sensor.setResolution(10);  //  10 bit ==> 0.25 degrees precision
  sensor.requestTemperatures();
  delay(1000);  //  wait a second to get a first measurement.


  //  configure PCR process
  //  adjust timing and temperature to your needs.
  pcr.setInitial(98, 10);      //  temp, seconds
  pcr.setDenature(94.5, 5);    //  temp, seconds
  pcr.setAnnealing(54.2, 2);   //  temp, seconds
  pcr.setExtension(75.0, 3);   //  temp, seconds
  pcr.setElongation(75.0, 5);  //  temp, seconds
  pcr.setHold(8.0);            //  temp only

  pcr.reset(15);  //  iterations.
  Serial.print("Estimated time (ms): ");
  Serial.println(pcr.timeLeft());

  //  run the PCR process.
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
