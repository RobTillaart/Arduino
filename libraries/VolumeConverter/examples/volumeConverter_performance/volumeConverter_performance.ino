//
//    FILE: volumeConverter_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: measure single step conversion vs two step conversion
//     URL: https://github.com/RobTillaart/VolumeConverter


#include "VolumeConverter.h"

VolumeConverter VC;

uint32_t start, stop;

float sum;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("VOLUMECONVERTER_LIB_VERSION: ");
  Serial.println(VOLUMECONVERTER_LIB_VERSION);
  Serial.println();
  delay(100);

  sum = 0;
  float n = random(1000000) * 0.001;
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    VC.setGallons(n);
    sum += VC.getLongTons();
  }
  stop = micros();
  Serial.print("TWO STEP (us):\t");
  Serial.println(stop - start);
  Serial.println(sum);
  delay(100);

  sum = 0;
  VC.setLiters(1);
  float LT2G = VC.getLongTons() / VC.getGallons();
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    sum += LT2G * n;
  }
  stop = micros();
  Serial.print("ONE STEP (us):\t");
  Serial.println(stop - start);
  Serial.println(sum);
  delay(100);

  Serial.println("\ndone...");
}


void loop()
{
}

//  -- END OF FILE --
