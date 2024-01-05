//
//    FILE: ra_two_sensors.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-06
// PURPOSE: show working of runningAverage for two sensors
//     URL: https://github.com/RobTillaart/RunningAverage


#include "RunningAverage.h"


RunningAverage RAT(10);
RunningAverage RAH(10);

int samples = 0;

float temperature = 25.0;
float humidity = 40.0;


void setup(void)
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("RUNNINGAVERAGE_LIB_VERSION: ");
  Serial.println(RUNNINGAVERAGE_LIB_VERSION);

  //  explicitly start clean
  RAT.clear(); 
  RAH.clear();
}


void loop(void)
{
  //  random function simulates 2 sensors
  temperature = temperature - 1 + random(0, 200) * 0.01;  //  fluctuate +- 1°C
  humidity = humidity - 0.2 + random(0, 400) * 0.001;     //  fluctuate +- 0.2 %

  RAT.addValue(temperature);
  RAH.addValue(humidity);

  //  print a header every 20 lines
  if (samples % 20 == 0)
  {
    Serial.println("\nCNT\tT\tTavg\tH\tHavg");
  }
  samples++;

  Serial.print(samples);
  Serial.print('\t');
  Serial.print(temperature, 1);
  Serial.print('\t');
  Serial.print(RAT.getAverage(), 2);
  Serial.print('\t');
  Serial.print(humidity, 1);
  Serial.print('\t');
  Serial.print(RAH.getAverage(), 2);
  Serial.println();

  delay(500);
}


//  -- END OF FILE --

