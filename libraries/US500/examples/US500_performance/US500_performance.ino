//
//    FILE: US500_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/US500
//
//    NOTE: this sketch needs a MEGA or another board that supports multiple
//          hardware serial ports named Serial1, Serial2, etc.


#include "US500.h"

US500 US(&Serial1);

uint32_t start, stop;

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
  US.setMaxDistance(5000);  //  15-50 cm.
  US.startMeasurement();
}


void loop()
{
  /*
    delay(1000);
    start = millis();
    float dist = US.getDistance();
    stop = millis();

    Serial.print(stop - start);
    Serial.print("\t");
    Serial.println(dist, 2);
  */

  delay(1000);
  start = millis();
  float temp = US.getTemperature();
  stop = millis();

  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println(temp, 2);


}


//  -- END OF FILE --
