//
//    FILE: GY521_performance_calibrate.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: read angleX, angleY, angleZ
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
  // while (sensor.wakeup() == false)
  {
    Serial.print(millis());
    Serial.println("\tCould not connect to GY521: please check the GY521 address (0x68/0x69)");
    delay(1000);
  }
  sensor.setAccelSensitivity(0);  //  2g
  sensor.setGyroSensitivity(0);   //  250 degrees/s
  sensor.setThrottle(false);

  test(100);
}


void loop()
{
  Serial.println("\n\tTIME\tACCELEROMETER\t\tGYROSCOPE");
  for (uint16_t times = 20; times <= 500; times += 20)
  {
    test(times);
  }
}



void test(uint16_t times)
{
  //  flush all output
  delay(100);
  uint32_t start = micros();
  sensor.calibrate(times);
  uint32_t duration = micros() - start;

  //  print results
  Serial.print(times);
  Serial.print('\t');
  Serial.print(duration);
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
}


//  -- END OF FILE --
