//
//    FILE: demo_running_correlation.ino.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2020-05-18
// PURPOSE: demo of the Correlation Library
//     URL: https://github.com/RobTillaart/Correlation


#include "Correlation.h"

Correlation C;


void setup()
{
  //  while(!Serial);  //  uncomment if needed
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("CORRELATION_LIB_VERSION: ");
  Serial.println(CORRELATION_LIB_VERSION);
  Serial.println();

  //  when internal table is full, no new values are added
  //  resulting in stabilization of the regression parameters A and B
  C.clear();
  C.setRunningCorrelation(false);
  for (int i = 0; i <= 1000; i++)
  {
    C.add(i, 10 * sin(i * 0.01));
	if (i % 25 == 0) report();
  }
  Serial.println();
  Serial.println();

  //  when internal table is full, values are overwritten and
  //  there is no stabilization of the regression parameters A and B
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


//  -- END OF FILE --

