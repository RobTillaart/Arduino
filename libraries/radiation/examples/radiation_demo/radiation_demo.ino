//
//    FILE: radiation_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/radiation


#include "radiation.h"


radiation R;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("RADIATION_LIB_VERSION: ");
  Serial.println(RADIATION_LIB_VERSION);
  Serial.println();

  R.setGray(123);
  Serial.println(R.getRad(), 4);
  R.setMilliGray(123);
  Serial.println(R.getMilliRad(), 4);
  R.setMicroGray(123);
  Serial.println(R.getMicroRad(), 4);


  R.setRem(123);
  Serial.println(R.getSievert(), 4);
  R.setMilliRem(123);
  Serial.println(R.getMilliSievert(), 4);
  R.setMicroRem(123);
  Serial.println(R.getMicroSievert(), 4);
}


void loop()
{

  delay(2000);
}


//  -- END OF FILE --
