//
//    FILE: PCA9685_allOFF_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test PCA9685 library
//     URL: https://github.com/RobTillaart/PCA9685_RT
//
//  sets all channels to a PWM
//  then switches them all off
//  you can check it by testing all channels.


#include "PCA9685.h"


PCA9685 PCA(0x40);

const uint8_t PIN = 2;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PCA9685_LIB_VERSION: ");
  Serial.println(PCA9685_LIB_VERSION);
  Serial.println();

  Wire.begin();
  PCA.begin();

  pinMode(PIN, INPUT_PULLUP);
  for (int channel = 0; channel < PCA.channelCount(); channel++)
  {
    PCA.setPWM(channel, 0, 1000);
  }
  delay(100);  //  to be sure they started.
  PCA.allOFF();

  //  delay(100);
  //  PCA.reset();  //  needed to reset the allOFF()
  //  for (int channel = 0; channel < 16; channel++)
  //  {
  //    PCA.write1(channel, HIGH);
  //  }
}


void loop()
{
  Serial.println(digitalRead(PIN));  //  you can measure all pins
}


//  -- END OF FILE --

