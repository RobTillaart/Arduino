//
//    FILE: AD5144A_test_write.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/AD5144A


#include "AD5144A.h"

//  select the right type
//  adjust address
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

  //  will generate 20+ lines
  //  decrease step 50 to 1 to test all
  for (int value = 0; value < 256; value += 50)
  {
    for (int potMeter = 0; potMeter < AD.pmCount(); potMeter++)
    {
      Serial.print(value);
      Serial.print("\t");
      Serial.print(AD.write(potMeter, value));
      Serial.print("\t");
      Serial.print(potMeter);
      Serial.print("\t");
      Serial.print(AD.read(potMeter));
      Serial.print("\t");
      Serial.print(AD.readBackRDAC(potMeter));
      Serial.println();
    }
  }
  Serial.println("done...");
}


void loop()
{
}


//  -- END OF FILE --

