//
//    FILE: ra_array.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: show working of an array of runningAverage objects
//     URL: https://github.com/RobTillaart/RunningAverage


#include "RunningAverage.h"

//  note the differrent sizes.
//RunningAverage RA0(10);
//RunningAverage RA1(15);
//RunningAverage RA2(20);
//RunningAverage RA3(10);
//RunningAverage RA4(15);
//RunningAverage RA5(20);
//
//RunningAverage RA[6] = { RA0, RA1, RA2, RA3, RA4, RA5 };

RunningAverage RA[6] = 
{
  RunningAverage(5),
  RunningAverage(7),
  RunningAverage(9),
  RunningAverage(11),
  RunningAverage(13),
  RunningAverage(15),
};

uint32_t samples = 0;


void setup(void)
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("RUNNINGAVERAGE_LIB_VERSION: ");
  Serial.println(RUNNINGAVERAGE_LIB_VERSION);
  Serial.println();

  //  explicitly start clean
  for (int i = 0; i < 6; i++)
  {
    RA[i].clear();
  }

  //  check different sizes.
  for (int i = 0; i < 6; i++)
  {
    Serial.print('\t');
    Serial.print(RA[i].getSize());
  }
  Serial.println();
}


void loop(void)
{
  //  read 6 ADC's
  for (int i = 0; i < 6; i++)
  {
    int value = analogRead(A0 + i);
    //  optional conversion here
    RA[i].addValue(value);
    //Serial.print(value);
    //Serial.print("\t");
  }
  //Serial.println();

  //  print a separator every 20 lines
  if (samples % 20 == 0)
  {
    Serial.println("\n");
  }
  samples++;

  Serial.print(samples);
  for (int i = 0; i < 6; i++)
  {
    Serial.print('\t');
    Serial.print(RA[i].getAverage(), 2);
  }
  Serial.println();

  delay(50);
}


//  -- END OF FILE --
