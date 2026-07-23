//
//    FILE: termialFloat.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo difference termial and termialFloat for real numbers.
//     URL: https://github.com/RobTillaart/statHelpers
//
//  best viewed in Serial plotter

#include "statHelpers.h"
#include "printHelpers.h"  //  to print large numbers....


uint32_t start, duration1, duration2;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("STATHELPERS_LIB_VERSION: ");
  Serial.println(STATHELPERS_LIB_VERSION);
  Serial.println();

  //
  //  prevent rounding effects by using integers as loop index.
  //  effectively this loop is -25 => 25 step 0.1
  for (int n = -250; n <= 250; n += 1)
  {
    if (n < 0) Serial.print(-1 * (int32_t)termial(-n / 10));
    else       Serial.print(termial(n / 10));
    Serial.print('\t');
    Serial.print(termialFloat(n / 10.0));
    Serial.println();
  }
  Serial.println();

  Serial.println("done");
}


void loop()
{
}


//  -- END OF FILE --
