//    FILE: M61538FP_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo M61538FP 6 channel volume processor.
//     URL: https://github.com/RobTillaart/M61538FP
//
//  need to uncomment the serial.print in sendData() => in the .h file.

#include "M61538FP.h"

//  adjust pins if needed
const uint8_t dataPin = 6;
const uint8_t clockPin = 7;

M61538FP vp(dataPin, clockPin);



void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("M61538FP_LIB_VERSION: ");
  Serial.println(M61538FP_LIB_VERSION);
  Serial.println();

  vp.begin();
  delay(300);

  vp.setVolumeAll(10, 30, 50, 70, 90, 100);
  delay(1000);

  vp.setVolumeAll(0, 0, 3, 6, 10, 10);
  delay(1000);

  vp.muteAll();
  delay(1000);

  //  as the mapping is logarithmic and cache is int,
  //  the read back of volume is not perfect.
  Serial.println("\n read back volume");
  for (uint16_t vol = 0; vol <= 100; vol++)
  {
    vp.setVolumeFrontLeft(vol);
    Serial.print(vol);
    Serial.print('\t');
    Serial.print(vp.getVolumeFrontLeft());
    Serial.print('\t');
    Serial.print(vp.getAttnFrontLeft());
    Serial.print('\t');
    Serial.println(vp.getVolumeFrontLeft() - vol);
  }


  //  test read back attenuation
  Serial.println("\n read back attenuation");
  for (uint16_t i = 0; i <= 96; i++)
  {
    vp.setAttnFrontLeft(i);
    Serial.print(i);
    Serial.print('\t');
    Serial.print(vp.getAttnFrontLeft());
    Serial.print('\t');
    Serial.println(vp.getAttnFrontLeft() - i);
  }

}

void loop()
{

}


//  -- END OF FILE --
