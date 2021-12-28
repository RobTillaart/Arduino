//
//    FILE: ra_300.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2021-05-26
// PUPROSE: demonstrate large (16 bit) buffer


#include "RunningAverage.h"

RunningAverage myRA(300);
int samples = 0;


void setup(void)
{
  Serial.begin(115200);
  Serial.println("Demo RunningAverage lib");
  Serial.print("Version: ");
  Serial.println(RUNNINGAVERAGE_LIB_VERSION);
  
  myRA.clear();
  for (uint16_t i = 0; i < 1000; i++)
  {
    myRA.addValue(i);
    Serial.print(i);
    Serial.print("\t");
    Serial.print(myRA.getCount());
    Serial.print("\t");
    Serial.print(myRA.getAverage());
    Serial.println();
  }
}


void loop(void)
{
}


// -- END OF FILE --

