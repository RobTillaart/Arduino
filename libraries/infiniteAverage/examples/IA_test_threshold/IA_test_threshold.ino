//
//    FILE: IA_test_threshold.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2021-12-20


#include "infiniteAverage.h"

IAVG iavg;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  iavg.reset();
  for (int i = 0; i < 1000; i++)
  {
    iavg.add(1.0 * i);
  }
  Serial.print(iavg.count());
  Serial.print("\t");
  Serial.print(iavg.whole());
  Serial.print("\t");
  Serial.print(iavg.average());
  Serial.print("\n");

  // shows the effects of small thresholds with non-uniform data
  for (uint32_t th = 2048; th <= 1000000UL; th *= 2)
  {
    iavg.reset();
    iavg.setDivideThreshold(th);
    for (int i = 0; i < 1000; i++)
    {
      iavg.add(1.0 * i);
    }
    Serial.print(th);
    Serial.print("\t");
    Serial.print(iavg.count());
    Serial.print("\t");
    Serial.print(iavg.whole());
    Serial.print("\t");
    Serial.print(iavg.average());
    Serial.print("\n");
  }
}


void loop()
{
}


// -- END OF FILE --
