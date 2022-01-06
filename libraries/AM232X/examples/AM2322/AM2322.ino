//
//    FILE: AM2322.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo sketch for AM2322 I2C humidity & temperature sensor
//
//  AM232X PIN layout             AM2315 COLOR
//  ============================================
//   bottom view  DESCRIPTION     COLOR
//       +---+
//       |o  |       VDD          RED
//       |o  |       SDA          YELLOW
//       |o  |       GND          BLACK
//       |o  |       SCL          GREY
//       +---+
//
// do not forget pull up resistors between SDA, SCL and VDD.


#include "AM232X.h"

AM232X AM2322;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("LIBRARY VERSION: ");
  Serial.println(AM232X_LIB_VERSION);
  Serial.println();

  if (! AM2322.begin() )
  {
    Serial.println("Sensor not found");
    while (1);
  }
  AM2322.wakeUp();
  delay(2000);

  Serial.println("Type,\tStatus,\tHumidity (%),\tTemperature (C)");
}


void loop()
{
  // READ DATA
  Serial.print("AM2322, \t");
  int status = AM2322.read();
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
  Serial.print(AM2322.getHumidity(), 1);
  Serial.print(",\t");
  Serial.println(AM2322.getTemperature(), 1);

  delay(2000);
}


// -- END OF FILE --
