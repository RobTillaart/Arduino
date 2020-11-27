//
//    FILE: PCA9635_test_multiple.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2018-02-18
// VERSION: 0.2.0
// PUPROSE: test PCA9635 library
//

#include "PCA9635.h"
#include <Wire.h>

PCA9635 ledArray(0x20);
PCA9635 ledArray2(0x21);

void setup()
{
  Serial.begin(115200);
  Serial.print("PCA9635 LIB version: ");
  Serial.println(PCA9635_LIB_VERSION);
  Serial.println();

  ledArray.begin();
  ledArray2.begin();

  Serial.print(millis());
  Serial.print("\t");
  Serial.println("Test - write1 - I");
  for (int channel = 0; channel < 16; channel++)
  {
    for (int pwm = 0; pwm < 256; pwm++)
    {
      ledArray.write1(channel, pwm);
      ledArray2.write1(channel, pwm);
    }
  }
  Serial.print(millis());
  Serial.print("\t");
  Serial.println("Test - write 1 - II");
  for (int pwm = 0; pwm < 256; pwm++)
  {
    for (int channel = 0; channel < 16; channel++)
    {
      ledArray.write1(channel, pwm);
      ledArray2.write1(channel, pwm);
    }
  }

  Serial.println("done...");
}

void loop()
{

}

// -- END OF FILE --
