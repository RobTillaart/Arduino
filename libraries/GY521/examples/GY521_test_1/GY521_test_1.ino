//
//    FILE: GY521_test_1.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: minimal demo to test working of the sensor.
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
  Serial.println();

  Wire.begin();

  delay(100);
  while (sensor.wakeup() == false)
  {
    Serial.print(millis());
    Serial.println("\tCould not connect to GY521: please check the GY521 address (0x68/0x69)");
    delay(1000);
  }
  sensor.setAccelSensitivity(0);  //  2g
  sensor.setGyroSensitivity(0);   //  250 degrees/s

  sensor.setThrottle();
  Serial.println("start...");

  //  set calibration values from calibration sketch.
  sensor.axe = 0;
  sensor.aye = 0;
  sensor.aze = 0;
  sensor.gxe = 0;
  sensor.gye = 0;
  sensor.gze = 0;
}


void loop()
{
  sensor.read();
  float ax = sensor.getAccelX();
  float ay = sensor.getAccelY();
  float az = sensor.getAccelZ();
  float gx = sensor.getGyroX();
  float gy = sensor.getGyroY();
  float gz = sensor.getGyroZ();
  float t = sensor.getTemperature();

  if (counter % 10 == 0)
  {
    Serial.println("\n\tACCELEROMETER\t\tGYROSCOPE\t\tTEMPERATURE");
    Serial.println("\tax\tay\taz\tgx\tgy\tgz\tT");
  }

  Serial.print(counter);
  Serial.print('\t');
  Serial.print(ax, 3);
  Serial.print('\t');
  Serial.print(ay, 3);
  Serial.print('\t');
  Serial.print(az, 3);
  Serial.print('\t');
  Serial.print(gx, 3);
  Serial.print('\t');
  Serial.print(gy, 3);
  Serial.print('\t');
  Serial.print(gz, 3);
  Serial.print('\t');
  Serial.print(t, 3);
  Serial.println();

  counter++;
  delay(1000);
}


//  -- END OF FILE --

