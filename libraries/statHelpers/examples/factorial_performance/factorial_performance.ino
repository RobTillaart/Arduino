//
//    FILE: factorial_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2020-07-01
//     URL: https://github.com/RobTillaart/statHelpers


#include "statHelpers.h"
#include "printHelpers.h"  //  to print large numbers....


uint32_t start, duration1, duration2, duration3;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("STATHELPERS_LIB_VERSION: ");
  Serial.println(STATHELPERS_LIB_VERSION);
  Serial.println();


  int m = 35;
  int decimals = 7;
  if (sizeof(double) == 8)
  {
    m = 175;
    decimals = 15;
  }

  Serial.println("PERFORMANCE");
  Serial.println("I\tT1\tT2\tT3");
  delay(10);

  for (int i = 0; i < m; i++)
  {
    start = micros();
    double d1 = dfactorialReference(i);
    duration1 = micros() - start;
    start = micros();
    double d2 = dfactorial(i);
    duration2 = micros() - start;
    start = micros();
    double d3 = stirling(i);
    duration3 = micros() - start;

    Serial.print(i);
    Serial.print('\t');
    Serial.print(duration1);
    Serial.print('\t');
    Serial.print(duration2);
    Serial.print('\t');
    Serial.print(duration3);
    Serial.print('\t');
    Serial.print(sci(d1, decimals));
    Serial.print('\t');
    Serial.print(sci(d2, decimals));
    Serial.print('\t');
    Serial.print(sci(d3, decimals));
    Serial.println();
    delay(10);
  }
  Serial.println("\n Done...");
}


void loop()
{
}


//  -- END OF FILE --

