//
//    FILE: HX_get_noise_statistics.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: HX711 noise meansurement
//     URL: https://github.com/RobTillaart/HX711
//
//  This example uses - https://github.com/RobTillaart/Statistic
//
//  The purpse of this sketch is to measure the noise of your system.
//  This is done by making 1000 measurements.
//  From these some basic statistics are caculated so one can see 
//  how much digits are significant and how much noise there is.
//
//  First one need to calibrate the loadcell and fill in the data
//  use - HX_calibration.ino to get the numbers.
//  Then run this program.
//
//  example output 
//    5 KG loadcell
//
//  COUNT   MIN   MAX   AVG   VAR   PDEV  UDEV
//  ...
//  1000  -0.7148 1.1891  -0.0158 0.2187  0.4676  0.4678
//
//  the scale.tare is averaged over 100 measurements (first loop)
//  so on a scale from 0..5000 gram
//  the average zero point drift = -0.0158 gram
//  the stddev is below 0.5 gram
//  MAX - MIN => ~1.9 gram
//  so accurate in order of 1 gram (about two stddev)


#include "HX711.h"
HX711 scale;
uint8_t dataPin = 6;
uint8_t clockPin = 7;


#include "Statistic.h"
statistic::Statistic<float, uint32_t, true> myStats;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("HX711_LIB_VERSION:\t");
  Serial.println(HX711_LIB_VERSION);
  Serial.print("STATISTIC_LIB_VERSION:\t");
  Serial.println(STATISTIC_LIB_VERSION);
  Serial.println();

  scale.begin(dataPin, clockPin);

  //  statistics on raw data
  myStats.clear();
  scale.set_raw_mode();
  Serial.println();
  Serial.println("\tCOUNT \tMIN \tMAX \tAVG \tVAR \tPDEV \tUDEV");
  for (uint32_t i = 1; i <= 100; i++)
  {
    float value = scale.read();
    myStats.add(value);
    if (i % 10 == 0)
    {
      Serial.print("\t");
      Serial.print(myStats.count());
      Serial.print("\t");
      Serial.print(myStats.minimum(), 4);
      Serial.print("\t");
      Serial.print(myStats.maximum(), 4);
      Serial.print("\t");
      Serial.print(myStats.average(), 4);
      Serial.print("\t");
      Serial.print(myStats.variance(), 4);
      Serial.print("\t");
      Serial.print(myStats.pop_stdev(), 4);
      Serial.print("\t");
      Serial.print(myStats.unbiased_stdev(), 4);
      Serial.println();
    }
  }


  //  TODO find an in-sketch solution for this calibration.
  //  use HX_calibration.ino for now
  //  load cell factor 20 KG
  //  scale.set_scale(127.15);  // TODO you need to calibrate this yourself.
  
  //  load cell factor 5 KG
  scale.set_scale(449.076354);

  //  reset the scale to zero = 0  normally call scale.tare(30);
  //  use the average from previous loop as tare offset
  scale.set_offset(myStats.average());

  //  for which weight measure the noise?
  while (Serial.available()) Serial.read();
  Serial.println("\nApply weight and press enter\n");
  while (!Serial.available());
  Serial.read();
  


  //  statistics on average data
  myStats.clear();
  scale.set_average_mode();
  Serial.println();
  Serial.println("\tCOUNT \tMIN \tMAX \tAVG \tVAR \tPDEV \tUDEV");
  for (uint32_t i = 1; i <= 1000; i++)
  {
    float value = scale.get_units(1);
    myStats.add(value);
    if (i % 100 == 0)
    {
      Serial.print("\t");
      Serial.print(myStats.count());
      Serial.print("\t");
      Serial.print(myStats.minimum(), 4);
      Serial.print("\t");
      Serial.print(myStats.maximum(), 4);
      Serial.print("\t");
      Serial.print(myStats.average(), 4);
      Serial.print("\t");
      Serial.print(myStats.variance(), 4);
      Serial.print("\t");
      Serial.print(myStats.pop_stdev(), 4);
      Serial.print("\t");
      Serial.print(myStats.unbiased_stdev(), 4);
      Serial.println();
    }
  }
}


void loop()
{
}


//  -- END OF FILE --
