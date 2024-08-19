//
//    FILE: raw_test.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2024-06-30
// PURPOSE: show working of RunAvgWeight
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
  Serial.println();

  myRA.clear();  //  explicitly start clean

  for (int i = 0; i < 20; i++)
  {
    float value = i * 0.01 + 1;
    float weight = sqrt(i);
    myRA.addValue(value, weight);

    Serial.print(value);
    Serial.print("\t");
    Serial.print(weight);
    Serial.print("\t");
    Serial.print(myRA.getCount());
    Serial.print("\t");
    Serial.print(myRA.getSumValues(), 3);
    Serial.print("\t");
    Serial.print(myRA.getSumWeights(), 3);
    Serial.print("\t\t");
    Serial.print(myRA.getFastAverage(), 3);
    Serial.print("\t");
    Serial.print(myRA.getAverage(), 3);
    Serial.println();
  }
  Serial.println();
  Serial.println();

  for (int i = 0; i < 10; i++)
  {
    Serial.print(i);
    Serial.print("\t");
    Serial.print(myRA.getValue(i), 3);
    Serial.print("\t");
    Serial.print(myRA.getWeight(i), 3);
    Serial.println();
  }
  Serial.println();

  Serial.print("SIZE:\t");
  Serial.println(myRA.getSize());
  Serial.print("COUNT:\t");
  Serial.println(myRA.getCount());
  Serial.println();

  //  first do fast to see if it is right
  //  if done after getAverage() it is same by definition.
  Serial.print("AVG(f):\t");
  Serial.println(myRA.getFastAverage(), 5);
  Serial.print("AVG:\t");
  Serial.println(myRA.getAverage(), 5);
  Serial.println();

  Serial.print("STDDEV:\t");
  Serial.println(myRA.getStandardDeviation(), 5);
  Serial.print("ERROR:\t");
  Serial.println(myRA.getStandardError(), 5);
  Serial.println();

  Serial.print("MIN:\t");
  Serial.println(myRA.getMin(), 3);
  Serial.print("MININB:\t");
  Serial.println(myRA.getMinInBuffer(), 3);
  Serial.println();

  Serial.print("MAX:\t");
  Serial.println(myRA.getMax(), 3);
  Serial.print("MAXINB:\t");
  Serial.println(myRA.getMaxInBuffer(), 3);
  Serial.println();

  Serial.print("SUMVAL:\t");
  Serial.println(myRA.getSumValues(), 3);
  Serial.print("SUMWGT:\t");
  Serial.println(myRA.getSumWeights(), 3);
  Serial.print("RATIO:\t");
  Serial.println(myRA.getSumValues() / myRA.getSumWeights(), 3);
  Serial.println();

}


void loop(void)
{

}


//  -- END OF FILE --
