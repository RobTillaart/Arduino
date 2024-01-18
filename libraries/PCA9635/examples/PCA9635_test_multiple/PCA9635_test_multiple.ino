//
//    FILE: PCA9635_test_multiple.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test PCA9635 library
//     URL: https://github.com/RobTillaart/PCA9635


#include "PCA9635.h"


PCA9635 ledArray(0x20);
PCA9635 ledArray2(0x21);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PCA9635_LIB_VERSION: ");
  Serial.println(PCA9635_LIB_VERSION);
  Serial.println();

  Wire.begin();

  ledArray.begin();
  ledArray2.begin();

  Serial.print(millis());
  Serial.print("\t");
  Serial.println("Test - write1 - I");
  for (int channel = 0; channel < ledArray.channelCount(); channel++)
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
    for (int channel = 0; channel < ledArray.channelCount(); channel++)
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


//  -- END OF FILE --

