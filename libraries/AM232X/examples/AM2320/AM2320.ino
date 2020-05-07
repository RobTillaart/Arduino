//
//    FILE: AM2320.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
// PURPOSE: AM2320 demo sketch for AM2320 I2C humidity & temperature sensor
//
// HISTORY:
// 0.1.0   2017-12-11 initial version
// 0.1.1   2020-05-03 updated to 0.2.0 version of lib.
//

#include <AM232X.h>

AM232X AM2320;

void setup()
{
  Wire.begin();

  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("LIBRARY VERSION: ");
  Serial.println(AM232X_LIB_VERSION);
  Serial.println();

  Serial.println("Type,\tStatus,\tHumidity (%),\tTemperature (C)");
}

void loop()
{
  // READ DATA
  Serial.print("AM2320, \t");
  int status = AM2320.read();
  switch (status)
  {
  case AM232X_OK:
    Serial.print("OK,\t");
    break;
  default:
    Serial.print(status);
    Serial.print("\t");
    break;
  }
  // DISPLAY DATA, sensor only returns one decimal.
  Serial.print(AM2320.getHumidity(), 1);
  Serial.print(",\t");
  Serial.println(AM2320.getTemperature(), 1);

  delay(2000);
}

// -- END OF FILE --
