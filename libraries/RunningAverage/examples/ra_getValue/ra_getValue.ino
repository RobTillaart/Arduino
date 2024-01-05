//
//    FILE: ra_getValue.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2020-01-15
// PURPOSE: demonstrate access in order of the values added
//     URL: https://github.com/RobTillaart/RunningAverage


#include "RunningAverage.h"


RunningAverage myRA(10);
int samples = 0;


void setup(void)
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("RUNNINGAVERAGE_LIB_VERSION: ");
  Serial.println(RUNNINGAVERAGE_LIB_VERSION);
  myRA.clear();  //  explicitly start clean
}


void loop(void)
{
  Serial.println();

  myRA.clear();
  for (uint16_t i = 0; i < 7; i++)
  {
    myRA.addValue(i);
  }

  Serial.print("\t getValue 0..getCount(): ");
  for (uint16_t i = 0; i < myRA.getCount(); i++)
  {
    Serial.print("\t");
    Serial.print(myRA.getValue(i), 0);
  }
  Serial.println();

  //  note first values (0..2) will be overwritten by 10..12
  myRA.clear();
  for (uint16_t i = 0; i < 13; i++)
  {
    myRA.addValue(i);
  }

  Serial.print("\t getValue 0..getCount(): ");
  for (uint16_t i = 0; i < myRA.getCount(); i++)
  {
    Serial.print("\t");
    Serial.print(myRA.getValue(i), 0);
  }
  Serial.println();

  Serial.print("\t get last 5 elements added: ");
  int last = myRA.getCount() - 1;     //  -1 as first idx == 0
  for (int i = last; i > last - 5 && i >= 0; i--)
  {
    Serial.print("\t");
    Serial.print(myRA.getValue(i), 0);
  }
  Serial.println();

  delay(1000);
}


//  -- END OF FILE --

