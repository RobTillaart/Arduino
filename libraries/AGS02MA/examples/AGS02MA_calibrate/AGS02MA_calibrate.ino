//
//    FILE: AGS02MA_calibrate.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: test application
//    DATE: 2021-08-12
//     URL: https://github.com/RobTillaart/AGS02MA
//

#include "AGS02MA.h"


uint32_t start, stop;


AGS02MA AGS(26);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  Serial.print("AGS02MA_LIB_VERSION: ");
  Serial.println(AGS02MA_LIB_VERSION);
  Serial.println();

  Wire.begin();

  bool b = AGS.begin();
  Serial.print("BEGIN:\t");
  Serial.println(b);

  Serial.println("Place the device outside in open air for 6 minutes");
  Serial.println("Take a drink and relax ;)");
  Serial.println();

  start = millis();
  while(millis() - start < 360000UL)
  {
    delay(15000);
    Serial.println(millis() - start);
  }

  // returns 1 if successful written
  b = AGS.zeroCalibration();
  Serial.print("CALIB:\t");
  Serial.println(b);

  Serial.println("Calibration done");
}


void loop()
{
}


// -- END OF FILE --
