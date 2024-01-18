//
//    FILE: GY521_raw_cooked.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: output raw and cooked data from sensor for analyzing.
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

  Serial.println("\n\tACCELEROMETER\t\tGYROSCOPE\t\tTEMP\tANGLES\t\t\tPRY");
  Serial.println("\tax\tay\taz\tgx\tgy\tgz\tT\tX\tY\tZ\tPITCH\tROLL\tYAW");
}


void loop()
{
  sensor.read();
  float ax    = sensor.getAccelX();
  float ay    = sensor.getAccelY();
  float az    = sensor.getAccelZ();
  float gx    = sensor.getGyroX();
  float gy    = sensor.getGyroY();
  float gz    = sensor.getGyroZ();
  float t     = sensor.getTemperature();

  float pitch = sensor.getPitch();
  float roll  = sensor.getRoll();
  float yaw   = sensor.getYaw();

  float x     = sensor.getAngleX();
  float y     = sensor.getAngleY();
  float z     = sensor.getAngleZ();

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
  Serial.print('\t');
  Serial.print(x, 1);
  Serial.print('\t');
  Serial.print(y, 1);
  Serial.print('\t');
  Serial.print(z, 1);
  Serial.print('\t');
  Serial.print(pitch, 3);
  Serial.print('\t');
  Serial.print(roll, 3);
  Serial.print('\t');
  Serial.print(yaw, 3);
  Serial.println();

  counter++;
  delay(1000);
}


//  -- END OF FILE --
