//
//    FILE: termialFloat_range_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: verify exact range for termialFloat()
//     URL: https://github.com/RobTillaart/statHelpers
//
/*
 * output looks like
 * 5793  16782321  16782320.00
 * 5794  16788115  16788116.00
 * 5797  16805503  16805504.00
 * 5798  16811301  16811300.00
 * 5801  16828701  16828700.00
 * 5802  16834503  16834504.00
 * 5805  16851915  16851916.00
 * 5806  16857721  16857720.00
 * 5809  16875145  16875144.00
 * 5810  16880955  16880956.00
 */

#include "statHelpers.h"


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("STATHELPERS_LIB_VERSION: ");
  Serial.println(STATHELPERS_LIB_VERSION);
  Serial.println();

  int errors = 0;
  for (uint16_t i = 0; i < 65534; i++)
  {
    //  force unsigned integer comparison!
    if (termial(i) != uint32_t(termialFloat(i)))
    {
      Serial.print(i);
      Serial.print("\t");
      Serial.print(termial(i));
      Serial.print("\t");
      Serial.print(termialFloat(i));
      Serial.print("\n");  
      errors++;
    }

    if (errors >= 10) break;
  }

  Serial.println("done");
}


void loop()
{
}


//  -- END OF FILE --
