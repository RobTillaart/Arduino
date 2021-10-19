//
//    FILE: AM2320.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.2
// PURPOSE: AM2320 demo sketch for AM2320 I2C humidity & temperature sensor
//
// HISTORY:
// 0.1.0   2017-12-11  initial version
// 0.1.1   2020-05-03  updated to 0.2.0 version of lib.
// 0.1.2   2021-01-28  added begin() ++

//  Bottom view
//       +---+
//  VDD  |o  |
//  SDA  |o  |
//  GND  |o  |
//  SCL  |o  |
//       +---+
//
// do not forget pull up resistors between SDA, SCL and VDD.


#include <AM232X.h>

AM232X AM2320;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("LIBRARY VERSION: ");
  Serial.println(AM232X_LIB_VERSION);
  Serial.println();

  if (! AM2320.begin() )
  {
    Serial.println("Sensor not found");
    while (1);
  }

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
