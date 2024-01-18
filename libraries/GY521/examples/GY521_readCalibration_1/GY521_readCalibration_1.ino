//
//    FILE: GY521_readCalibration_1.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: read the calibration values / errors for a flat sensor.
//     URL: https://github.com/RobTillaart/GY521


#include "GY521.h"

GY521 sensor(0x68);

uint32_t counter = 0;

float ax, ay, az;
float gx, gy, gz;
float t;


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
  //  adjust when needed.
  sensor.setAccelSensitivity(0);  //  2g
  sensor.setGyroSensitivity(0);   //  250 degrees/s
  sensor.setThrottle(false);

  //  set all calibration errors to zero
  sensor.axe = 0;
  sensor.aye = 0;
  sensor.aze = 0;
  sensor.gxe = 0;
  sensor.gye = 0;
  sensor.gze = 0;

  Serial.println("\n\nReading calibration numbers...");
}


void loop()
{
  ax = ay = az = 0;
  gx = gy = gz = 0;
  t = 0;
  for (int i = 0; i < 20; i++)
  {
    sensor.read();
    ax -= sensor.getAccelX();
    ay -= sensor.getAccelY();
    az -= sensor.getAccelZ();
    gx -= sensor.getGyroX();
    gy -= sensor.getGyroY();
    gz -= sensor.getGyroZ();
    t += sensor.getTemperature();
  }

  if (counter % 10 == 0)
  {
    Serial.println("\n\tACCELEROMETER\t\tGYROSCOPE\t\tTEMPERATURE");
    Serial.print('\t');
    Serial.print(sensor.axe, 3);
    Serial.print('\t');
    Serial.print(sensor.aye, 3);
    Serial.print('\t');
    Serial.print(sensor.aze, 3);
    Serial.print('\t');
    Serial.print(sensor.gxe, 3);
    Serial.print('\t');
    Serial.print(sensor.gye, 3);
    Serial.print('\t');
    Serial.print(sensor.gze, 3);
    Serial.print('\n');
    Serial.println("\taxe\taye\taze\tgxe\tgye\tgze\tT");
  }

  Serial.print(counter);
  Serial.print('\t');
  Serial.print(ax * 0.05, 3);
  Serial.print('\t');
  Serial.print(ay * 0.05, 3);
  Serial.print('\t');
  Serial.print(az * 0.05, 3);
  Serial.print('\t');
  Serial.print(gx * 0.05, 3);
  Serial.print('\t');
  Serial.print(gy * 0.05, 3);
  Serial.print('\t');
  Serial.print(gz * 0.05, 3);
  Serial.print('\t');
  Serial.print(t * 0.05, 2);
  Serial.println();

  //  adjust calibration errors so table should get all zero's.
  sensor.axe += ax * 0.05;
  sensor.aye += ay * 0.05;
  sensor.aze += az * 0.05;
  sensor.gxe += gx * 0.05;
  sensor.gye += gy * 0.05;
  sensor.gze += gz * 0.05;

  counter++;
  delay(100);
}


//  -- END OF FILE --

