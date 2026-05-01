//
//    FILE: US4000_demo_distance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/US500
//
//    NOTE: this sketch needs a MEGA or another board that supports multiple
//          hardware serial ports named Serial1, Serial2, etc.


#include "US4000.h"

US4000 US(&Serial1);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("US4000_LIB_VERSION: ");
  Serial.println(US4000_LIB_VERSION);
  Serial.println();

  //  initialize sensor
  Serial1.begin(9600);
  US.setMaxDistance(5000);  //  50 cm.
  US.startMeasurement();
}


void loop()
{
  float dist = US.getDistance();
  if (dist < 0)
  {
    if (dist == US4000_CMD_ERROR) Serial.println("CMD_ERROR");
    if (dist == US4000_CRC_ERROR) Serial.println("CRC_ERROR");
    if (dist == US4000_TIMEOUT_ERROR) Serial.println("TIMEOUT_ERROR");
    delay(1000);
    return;
  }
  Serial.println(dist, 2);

  delay(2000);
}


//  -- END OF FILE --
