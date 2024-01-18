//
//    FILE: GY521_pitch_roll_yaw.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo pitch roll yaw
//     URL: https://github.com/RobTillaart/GY521


#include "GY521.h"

GY521 sensor(0x68);

uint32_t counter = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("GY521_LIB_VERSION: ");
  Serial.println(GY521_LIB_VERSION);
  Serial.println("warning: Pitch roll yaw is work in progress.");

  Wire.begin();

  delay(100);
  while (sensor.wakeup() == false)
  {
    Serial.print(millis());
    Serial.println("\tCould not connect to GY521: please check the GY521 address (0x68/0x69)");
    delay(1000);
  }

  sensor.setAccelSensitivity(2);  //  8g
  sensor.setGyroSensitivity(1);   //  500 degrees/s
  sensor.setThrottle();
  Serial.println("start...");

  // uint32_t startCalibrate = micros();
  sensor.calibrate(100);
  //  Serial.print("Duration: ");
  //  Serial.println(micros() - startCalibrate);

  //  set calibration values from calibration sketch.
  //  sensor.axe = 0.574;
  //  sensor.aye = -0.002;
  //  sensor.aze = -1.043;
  //  sensor.gxe = 10.702;
  //  sensor.gye = -6.436;
  //  sensor.gze = -0.676;
}


void loop()
{
  sensor.read();
  float pitch = sensor.getPitch();
  float roll  = sensor.getRoll();
  float yaw   = sensor.getYaw();

  if (counter % 10 == 0)
  {
    Serial.println("\nCNT\tPITCH\tROLL\tYAW");
  }

  Serial.print(counter);
  Serial.print('\t');
  Serial.print(pitch, 3);
  Serial.print('\t');
  Serial.print(roll, 3);
  Serial.print('\t');
  Serial.print(yaw, 3);
  Serial.println();

  counter++;
}


//  -- END OF FILE --

