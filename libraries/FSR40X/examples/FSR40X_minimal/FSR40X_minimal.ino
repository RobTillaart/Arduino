//
//    FILE: FSR40X_minimal.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: minimal sketch
//     URL: https://github.com/RobTillaart/FSR40X
//
//  looks good in Serial plotter.

#include "FSR40X.h"


FSR40X FSR(A0, 5.0, 1023);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("FSR40X_LIB_VERSION: ");
  Serial.println(FSR40X_LIB_VERSION);
  Serial.println();

  //  start with known calibration, 10 kOhm as default
  //  adjust to your needs
  FSR.begin(10000);
}


void loop()
{
  Serial.println(FSR.readNewton());
  delay(100);
}


//  -- END OF FILE --
