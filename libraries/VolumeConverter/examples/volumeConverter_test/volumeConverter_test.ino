//
//    FILE: volumeConverter_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2022-12-05


#include "VolumeConverter.h"

VolumeConverter VC;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("VOLUMECONVERTER_LIB_VERSION: ");
  Serial.println(VOLUMECONVERTER_LIB_VERSION);
  Serial.println();

  convert(100);
  delay(5000);
}



void loop()
{
  float n = random(1000000) * 0.001;
  convert(n);
  delay(1000);
}



void convert(float n)
{
  VC.setLiters(n);

  Serial.print("liters:\t\t");
  Serial.println(VC.getLiters(), 4);
  Serial.print("milliLiters:\t");
  Serial.println(VC.getMilliLiters(), 4);
  Serial.print("cubic meter:\t");
  Serial.println(VC.getCubicMeters(), 4);
  Serial.print("long ton:\t");
  Serial.println(VC.getLongTons(), 4);
  Serial.print("short ton:\t");
  Serial.println(VC.getShortTons(), 4);
  Serial.print("barrels:\t");
  Serial.println(VC.getBarrels(), 4);
  Serial.print("gallons:\t");
  Serial.println(VC.getGallons(), 4);
  Serial.print("quarts:\t\t");
  Serial.println(VC.getQuarts(), 4);
  Serial.print("pints:\t\t");
  Serial.println(VC.getPints(), 4);
  Serial.print("cups:\t\t");
  Serial.println(VC.getCups(), 4);
  Serial.print("fluid ounce:\t");
  Serial.println(VC.getFluidOunces(), 4);
  Serial.print("table spoons:\t");
  Serial.println(VC.getTableSpoons(), 4);
  Serial.print("tea spoons:\t");
  Serial.println(VC.getTeaSpoons(), 4);

  Serial.println("\n");
}


//  -- END OF FILE --
