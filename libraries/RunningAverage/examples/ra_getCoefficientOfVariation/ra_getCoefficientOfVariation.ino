//
//    FILE: ra_getCoefficientOfVariation.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: show working of runningAverage
//     URL: https://github.com/RobTillaart/RunningAverage


#include "RunningAverage.h"


RunningAverage myRA(10);
int samples = 0;


RunningAverage A(60);
RunningAverage B(60);
RunningAverage C(60);


void setup(void)
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("RUNNINGAVERAGE_LIB_VERSION: ");
  Serial.println(RUNNINGAVERAGE_LIB_VERSION);

  myRA.clear();  //   explicitly start clean

  for (int i = 0; i < 10; i++)
  {
    myRA.add(i * 0.01 + 1 );
    Serial.print(myRA.getCount());
    Serial.print("\t");
    Serial.print(myRA.getAverage(), 3);
    Serial.print("\t");
    Serial.print(myRA.getStandardDeviation(), 3);
    Serial.print("\t");
    Serial.print(myRA.getStandardDeviation() / myRA.getAverage(), 3);
    Serial.print("\t");
    Serial.println(myRA.getCoefficientOfVariation(), 3);
  }
  Serial.println();


  Serial.println();
  Serial.println("Show effect of changing average and standard deviation.");
  Serial.println("- A is reference");
  Serial.println("- B has same stdev, distribution is 'smaller' (sharper)");
  Serial.println("- C has same average, distribution is 'wider'");
  Serial.println();

  A.clear();
  B.clear();
  C.clear();

  for (int i = 0; i <= 50; i++)
  {
    A.add((i - 25) * 1.0 + 100);  //  reference
    B.add((i - 25) * 1.0 + 200);  //  change average
    C.add((i - 25) * 3.0 + 100);  //  change stddev
  }
  Serial.println("\tA\tB\tC");
  Serial.print("AVG\t");
  Serial.print(A.getAverage(), 3);
  Serial.print("\t");
  Serial.print(B.getAverage(), 3);
  Serial.print("\t");
  Serial.println(C.getAverage(), 3);

  Serial.print("STDEV\t");
  Serial.print(A.getStandardDeviation(), 3);
  Serial.print("\t");
  Serial.print(B.getStandardDeviation(), 3);
  Serial.print("\t");
  Serial.println(C.getStandardDeviation(), 3);

  Serial.print("COFVAR\t");
  Serial.print(A.getCoefficientOfVariation(), 3);
  Serial.print("\t");
  Serial.print(B.getCoefficientOfVariation(), 3);
  Serial.print("\t");
  Serial.println(C.getCoefficientOfVariation(), 3);


  delay(10000);
}


void loop(void)
{
}


//  -- END OF FILE --
