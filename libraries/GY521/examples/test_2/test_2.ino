//
//    FILE: test_2.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: test set/get
//    DATE: 2020-08-06


#include "GY521.h"

GY521 sensor(0x69);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  Wire.begin();

  delay(100);
  if (sensor.wakeup() == false)
  {
    Serial.println("Could not conect to GY521");
  }

  Serial.println("ACCEL TEST");
  for (uint8_t n = 0; n < 4; n++)
  {
    sensor.setAccelSensitivity(n);
    uint8_t p = sensor.getAccelSensitivity();
    if (n != p)
    {
      Serial.print("\tAccel err:\t");
      Serial.print(n);
      Serial.print("\t");
      Serial.println(p);
    }
  }

  Serial.println("GYRO TEST");
  for (uint8_t n = 0; n < 4; n++)
  {
    sensor.setGyroSensitivity(n);
    uint8_t p = sensor.getGyroSensitivity();
    if (n != p)
    {
      Serial.print("\tGyro err:\t");
      Serial.print(n);
      Serial.print("\t");
      Serial.println(p);
    }
  }

  Serial.println("THROTTLE TEST");
  sensor.setThrottle();
  if (sensor.getThrottle() == false)
  {
    Serial.println("\tThrot:\ttrue");
  }
  sensor.setThrottle(false);
  if (sensor.getThrottle() == true)
  {
    Serial.println("\tThrot err:\tfalse");
  }

  for (uint16_t n = 0; n < 1000; n++)  // 0 - 1 second.
  {
    sensor.setThrottleTime(n);
    if (sensor.getThrottleTime() != n)
    {
      Serial.print("\tTT err:\t");
      Serial.println(n);
    }
  }

  Serial.println("\nDone...");
}


void loop()
{
}


// -- END OF FILE --

