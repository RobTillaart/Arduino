//
//    FILE: demo_running_correlation.ino.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2020-05-18
// VERSION: 0.1.0
// PUPROSE: demo of the Correlation Library
//

#include "Correlation.h"

Correlation C;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  // when internal table is full, no new values are added
  // resulting in stabilization of the regression params A and B
  C.clear();
  C.setRunningCorrelation(false);
  for (int i = 0; i <= 1000; i++)
  {
    C.add(i, 10 * sin(i * 0.01));
	if (i % 25 == 0) report();
  }
  Serial.println();
  Serial.println();

  // when internal table is full, values are overwritten and 
  // there is no stabilization of the regression params A and B
  C.clear();
  C.setRunningCorrelation(true);
  for (int i = 0; i <= 1000; i++)
  {
    C.add(i, 10 * sin(i *0.01));
	if (i % 25 == 0) report();
  }
  Serial.println();
  Serial.println();

  Serial.println("\nDone...");
}

void report()
{
  C.calculate();
  Serial.print("\t");
  Serial.print(C.getA(), 2);
  Serial.print("\t\t");
  Serial.print(C.getB(), 2);
  Serial.print("\t\t");
  Serial.print(C.getRsquare(), 4);
  Serial.print("\t\t");
  Serial.print(C.getEsquare(), 2);
  Serial.println();
}

void loop()
{

}

// -- END OF FILE --
