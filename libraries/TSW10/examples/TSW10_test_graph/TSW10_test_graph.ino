//
//    FILE: TSW10_test_graph.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/TSW10


#include "TSW10.h"

TSW10 turbidity(A0);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("TSW10_LIB_VERSION: ");
  Serial.println(TSW10_LIB_VERSION);
  Serial.println();

  turbidity.begin(5.0, 1023);

  for (float volts = 2.50; volts < 5.0; volts += 0.05)
  {
    Serial.print(volts);
    Serial.print("\t");
    Serial.print(turbidity.volts2NTU(volts));
    Serial.println();
  }
}


void loop()
{
}


//  -- END OF FILE --
