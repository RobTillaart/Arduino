//
//    FILE: raw_demo_equal_weight.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2024-06-30
// PURPOSE: show working of RunAvgWeight with equal weights
//     URL: https://github.com/RobTillaart/RunAvgWeight


#include "RunAvgWeight.h"


RunAvgWeight myRA(10);
int samples = 0;


void setup(void)
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("RUNAVGWEIGHT_LIB_VERSION: ");
  Serial.println(RUNAVGWEIGHT_LIB_VERSION);

  myRA.clear();  //   explicitly start clean

  for (int i = 0; i < 10; i++)
  {
    myRA.addValue(i * 0.01 + 1 );
    //    Serial.print(myRA.getCount());
    //    Serial.print("\t");
    //    Serial.print(myRA.getAverage(), 3);
    //    Serial.print("\t");
    Serial.print(myRA.getStandardDeviation(), 3);
    Serial.print("\t");
    Serial.println(myRA.getMaxInBuffer(), 3);
  }
}


void loop(void)
{
  long rn = random(0, 1000);
  myRA.addValue(rn * 0.001);
  samples++;
  Serial.print(samples);
  Serial.print("\t Running Average: ");
  Serial.println(myRA.getAverage(), 3);
  
  if (samples == 300)
  {
    samples = 0;
    myRA.clear();
    Serial.println();
  }
  delay(10);
}


//  -- END OF FILE --
