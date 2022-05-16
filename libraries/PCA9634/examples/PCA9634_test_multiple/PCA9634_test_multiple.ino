//
//    FILE: PCA9634_test_multiple.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2022-01-03
// PURPOSE: test PCA9634 library


#include "Arduino.h"
#include "Wire.h"
#include "PCA9634.h"


PCA9634 ledArray(0x20);
PCA9634 ledArray2(0x21);


void setup()
{
  Serial.begin(115200);
  Serial.print("PCA9634 LIB version: ");
  Serial.println(PCA9634_LIB_VERSION);
  Serial.println();

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


// -- END OF FILE --

