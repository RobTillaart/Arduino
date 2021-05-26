//
//    FILE: AD5144A_test_write.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo
//    DATE: 2021-04-30
//     URL: https://github.com/RobTillaart/AD5144A


#include "AD5144A.h"

// select the right type
// adjust address
AD5144A AD(0x77);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  Wire.begin();
  if (AD.begin() == false)
  {
    Serial.println("device not found");
    return;
  }

  // will generate 20+ lines
  // decrease step 50 to 1 to test all
  for (int val = 0; val < 256; val+= 50)
  {
    for (int p = 0; p < AD.pmCount(); p++)
    {
      Serial.print(val);
      Serial.print("\t");
      Serial.print(AD.write(p, val));
      Serial.print("\t");
      Serial.print(p);
      Serial.print("\t");
      Serial.print(AD.read(p));
      Serial.print("\t");
      Serial.print(AD.readBackRDAC(p));
      Serial.println();
    }
  }
  Serial.println("done...");
}


void loop()
{
}


// -- END OF FILE --
