//
//    FILE: HX_MP_performance2.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: HX711_MP demo
//     URL: https://github.com/RobTillaart/HX711_MP


#include "HX711_MP.h"


//  10 calibration points
//  all user defined.
HX711_MP scale(10);

//  adjust pins to your setup.
uint8_t dataPin = 16;
uint8_t clockPin = 17;


uint32_t start, stop;
volatile float f;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("HX711_MP_LIB_VERSION: ");
  Serial.println(HX711_MP_LIB_VERSION);
  Serial.println();

  scale.begin(dataPin, clockPin);

  //  Calibration
  //  adjust the calibration data to your sensor
  //  setCalibrate(index, rawRead, weight);
  scale.setCalibrate(0, 1000, -10000);
  scale.setCalibrate(1, 1300, 0);
  scale.setCalibrate(2, 2000, 20000);
  scale.setCalibrate(3, 4000, 30000);
  scale.setCalibrate(4, 5000, 40000);
  scale.setCalibrate(5, 5200, 50000);
  scale.setCalibrate(6, 6000, 60000);
  scale.setCalibrate(7, 6500, 70000);
  scale.setCalibrate(8, 6750, 80000);
  scale.setCalibrate(9, 6900, 90000);
  delay(10);

  measure();

  Serial.println("Done...");
}


void loop()
{
}


void measure()
{
  Serial.println("Counting get_units() calls for 1 minute...");
  delay(10);

  uint32_t count = 0;
  uint32_t start = millis();
  while (millis() - start < 60000)
  {
    if (scale.is_ready())
    {
      count++;
      scale.get_units(1);
    }
  }
  Serial.print("calls per minute: ");
  Serial.println(count);
  Serial.print("calls per second: ");
  Serial.println(count / 60.0);
}


//  -- END OF FILE --
