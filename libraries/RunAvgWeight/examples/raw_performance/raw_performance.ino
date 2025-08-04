//
//    FILE: raw_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: show working of RunAvgWeight
//     URL: https://github.com/RobTillaart/RunAvgWeight


#include "RunAvgWeight.h"


RunAvgWeight myRA(20);
int samples = 0;

uint32_t start, stop;
volatile float f;

void setup(void)
{
  while (!Serial); //  for Leonardo a.o.
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("RUNAVGWEIGHT_LIB_VERSION: ");
  Serial.println(RUNAVGWEIGHT_LIB_VERSION);
  Serial.println();


  start = micros();
  myRA.clear();
  stop = micros();
  Serial.print("CLEAR:\t\t");
  Serial.println(stop - start);
  delay(100);


  for (int i = 0; i < 20; i++)
  {
    float value = i * 0.01 + 1;
    float weight = sqrt(i);
    myRA.addValue(value, weight);
  }

  start = micros();
  myRA.addValue(10, 2);
  stop = micros();
  Serial.print("ADDVALUE:\t");
  Serial.println(stop - start);
  delay(100);

  start = micros();
  f = myRA.getFastAverage();
  stop = micros();
  Serial.print("FASTAVG:\t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println(f, 4);
  delay(100);

  start = micros();
  f = myRA.getAverage();
  stop = micros();
  Serial.print("AVERAGE:\t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println(f, 4);
  delay(100);

  start = micros();
  f = myRA.getStandardDeviation();
  stop = micros();
  Serial.print("STD_DEV:\t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println(f, 4);
  delay(100);

  start = micros();
  f = myRA.getMinInBuffer();
  stop = micros();
  Serial.print("MIN_BUF:\t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println(f, 4);
  delay(100);

  start = micros();
  f = myRA.getMaxInBuffer();
  stop = micros();
  Serial.print("MAX_BUF:\t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println(f, 4);
  delay(100);

  /*
    Serial.println();
    for (int i = 0; i < myRA.getSize(); i++)
    {
      Serial.print(i);
      Serial.print("\t");
      Serial.println(myRA.getElementValue(i));
    }
  */
  Serial.println("\ndone...");
}


void loop(void)
{
}


//  -- END OF FILE --
