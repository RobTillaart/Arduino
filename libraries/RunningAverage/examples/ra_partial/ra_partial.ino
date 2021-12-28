//
//    FILE: ra_partial.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2021-05-26
// PUPROSE: demonstrate partial use of internal buffer


#include "RunningAverage.h"

RunningAverage myRA(25);
int samples = 0;


void setup(void)
{
  Serial.begin(115200);
  Serial.println("Demo RunningAverage lib");
  Serial.print("Version: ");
  Serial.println(RUNNINGAVERAGE_LIB_VERSION);

  myRA.clear();
  for (uint16_t i = 0; i < 30; i++)
  {
    myRA.addValue(i);
    Serial.print(i);
    Serial.print("\t");
    Serial.print(myRA.getCount());
    Serial.print("\t");
    Serial.print(myRA.getAverage());
    Serial.println();
  }
  Serial.println();

  myRA.setPartial(20);
  for (uint16_t i = 0; i < 30; i++)
  {
    myRA.addValue(i);
    Serial.print(i);
    Serial.print("\t");
    Serial.print(myRA.getCount());
    Serial.print("\t");
    Serial.print(myRA.getAverage());
    Serial.println();
  }
  Serial.println();

  myRA.setPartial(50);
  for (uint16_t i = 0; i < 30; i++)
  {
    myRA.addValue(i);
    Serial.print(i);
    Serial.print("\t");
    Serial.print(myRA.getCount());
    Serial.print("\t");
    Serial.print(myRA.getAverage());
    Serial.println();
  }
  Serial.println();

  myRA.setPartial(10);
  for (uint16_t i = 0; i < 30; i++)
  {
    myRA.addValue(i);
    Serial.print(i);
    Serial.print("\t");
    Serial.print(myRA.getCount());
    Serial.print("\t");
    Serial.print(myRA.getAverage());
    Serial.println();
  }
  Serial.println();

  myRA.setPartial();
  for (uint16_t i = 0; i < 30; i++)
  {
    myRA.addValue(i);
    Serial.print(i);
    Serial.print("\t");
    Serial.print(myRA.getCount());
    Serial.print("\t");
    Serial.print(myRA.getAverage());
    Serial.println();
  }
  Serial.println();
}


void loop(void)
{
}


// -- END OF FILE --

