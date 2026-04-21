//
//    FILE: FSLP_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/FSLP


#include "FSLP.h"

//
//  FSLP(pin1, pin2, pin3, extraPin)
//  pin1 = GPIO/ADC
//  pin2 = GPIO
//  pin3 = GPIO/ADC
//  ePin = GPIO
//
//  FSLP(uint8_t sense, uint8_t drive1, uint8_t drive2, uint8_t gpio)
//
FSLP fslp(14, 4, 15, 5);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("FSLP_LIB_VERSION: ");
  Serial.println(FSLP_LIB_VERSION);
  Serial.println();
  delay(100);

  //  optional tuning.
  //  fslp.setStabilizationDelay(5);
  //  fslp.setPressureFactor(32);
}


void loop()
{
  float pres = fslp.readPressure(3);
  if (pres != 0)
  {
    float pos = fslp.readPosition(3);
    Serial.print(millis());
    Serial.print("\t");
    Serial.print(pres);
    Serial.print("\t");
    Serial.println(pos);
  }
}


//  -- END OF FILE --
