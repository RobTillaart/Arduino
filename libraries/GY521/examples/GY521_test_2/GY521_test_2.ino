//
//    FILE: GY521_test_2.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test set/get functions
//     URL: https://github.com/RobTillaart/GY521


#include "GY521.h"

GY521 sensor(0x68);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("GY521_LIB_VERSION: ");
  Serial.println(GY521_LIB_VERSION);

  Wire.begin();

  delay(100);
  if (sensor.wakeup() == false)
  {
    Serial.println("\tCould not connect to GY521: please check the GY521 address (0x68/0x69)");
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

  for (uint16_t n = 0; n < 1000; n++)  //  0 - 1 second.
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


//  -- END OF FILE --

