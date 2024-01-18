//
//    FILE: GY521_two_sensors.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: read angleX, angleY, angleZ from two sensors
//     URL: https://github.com/RobTillaart/GY521


#include "GY521.h"

GY521 sensor1(0x68);
GY521 sensor2(0x69);

uint32_t counter = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("GY521_LIB_VERSION: ");
  Serial.println(GY521_LIB_VERSION);

  Wire.begin();

  //  INITIALIZE SENSOR 1
  delay(100);
  while (sensor1.wakeup() == false)
  {
    Serial.print(millis());
    Serial.println("\tCould not connect to sensor1: please check the GY521 address (0x68/0x69)");
    delay(1000);
  }
  sensor1.setAccelSensitivity(2);  //  8g
  sensor1.setGyroSensitivity(1);   //  500 degrees/s

  sensor1.setThrottle();
  Serial.println("start...");

  //  set calibration values from calibration sketch.
  sensor1.axe = 0.574;
  sensor1.aye = -0.002;
  sensor1.aze = -1.043;
  sensor1.gxe = 10.702;
  sensor1.gye = -6.436;
  sensor1.gze = -0.676;

  //  INITIALIZE SENSOR 2
  delay(100);
  while (sensor2.wakeup() == false)
  {
    Serial.print(millis());
    Serial.println("\tCould not connect to sensor2: please check the GY521 address (0x68/0x69)");
    delay(1000);
  }
  sensor2.setAccelSensitivity(2);  //  8g
  sensor2.setGyroSensitivity(1);   //  500 degrees/s

  sensor2.setThrottle();
  Serial.println("start...");

  //  set calibration values from calibration sketch.
  sensor2.axe = 0.574;
  sensor2.aye = -0.002;
  sensor2.aze = -1.043;
  sensor2.gxe = 10.702;
  sensor2.gye = -6.436;
  sensor2.gze = -0.676;

}


void loop()
{
  //  READ SENSOR 1
  sensor1.read();
  float x1 = sensor1.getAngleX();
  float y1 = sensor1.getAngleY();
  float z1 = sensor1.getAngleZ();

  //  READ SENSOR 2
  sensor2.read();
  float x2 = sensor1.getAngleX();
  float y2 = sensor1.getAngleY();
  float z2 = sensor1.getAngleZ();

  //  OPTIONAL TIME / NR
  //  Serial.print(millis);
  //  Serial.print('\t');
  //  Serial.print(counter);
  //  Serial.print('\t');
  Serial.print(x1, 1);
  Serial.print('\t');
  Serial.print(y1, 1);
  Serial.print('\t');
  Serial.print(z1, 1);
  Serial.print('\t');
  Serial.print('\t');
  Serial.print(x2, 1);
  Serial.print('\t');
  Serial.print(y2, 1);
  Serial.print('\t');
  Serial.print(z2, 1);
  Serial.println();

  counter++;
}


//  -- END OF FILE --
