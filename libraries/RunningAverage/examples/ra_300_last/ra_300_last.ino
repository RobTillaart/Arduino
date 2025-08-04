//
//    FILE: ra_300.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2021-05-26
// PURPOSE: demonstrate large (16 bit) buffer
//     URL: https://github.com/RobTillaart/RunningAverage


#include "RunningAverage.h"


RunningAverage myRA(300);
int samples = 0;


void setup(void)
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("RUNNINGAVERAGE_LIB_VERSION: ");
  Serial.println(RUNNINGAVERAGE_LIB_VERSION);
  Serial.println();

  delay(10);
  //  explicitly start clean
  myRA.clear();

  for (uint16_t i = 0; i < 1000; i++)
  {
    myRA.addValue(i);    //  random(1000));  (i);
    //    Serial.print(i);
    //    Serial.print("\t");
    //    Serial.print(myRA.getCount());
    //    Serial.print("\t");
    //    Serial.print(myRA.getAverage());
    //    Serial.println();
  }

  Serial.println();
  for (uint16_t i = 1; i < 1000; i++)
  {
    Serial.print(i);
    Serial.print("\t");
    Serial.print(myRA.getMinInBufferLast(i));
    Serial.print("\t");
    Serial.print(myRA.getAverageLast(i));
    Serial.print("\t");
    Serial.print(myRA.getMaxInBufferLast(i));
    Serial.println();
  }
}


void loop(void)
{
}


//  -- END OF FILE --

