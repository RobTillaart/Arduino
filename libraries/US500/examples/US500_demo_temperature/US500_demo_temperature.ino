//
//    FILE: US500_demo_temperature.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/US500
//
//    NOTE: this sketch needs a MEGA or another board that supports multiple
//          hardware serial ports named Serial1, Serial2, etc.


#include "US500.h"

US500 US(&Serial1);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("US500_LIB_VERSION: ");
  Serial.println(US500_LIB_VERSION);
  Serial.println();

  //  initialize sensor
  Serial1.begin(9600);
  delay(100);
  US.startMeasurement();
}


void loop()
{
  float temp = US.getTemperature();
  Serial.println(temp, 2);
  if (temp < 0)
  {
    if (temp == US500_CMD_ERROR) Serial.println(" CMD_ERROR");
    if (temp == US500_CRC_ERROR) Serial.println(" CRC_ERROR");
    if (temp == US500_TIMEOUT_ERROR) Serial.println(" TIMEOUT_ERROR");
    //  flush after error
    US.flush();
    delay(1000);
    return;
  }

  delay(2000);
}


//  -- END OF FILE --
