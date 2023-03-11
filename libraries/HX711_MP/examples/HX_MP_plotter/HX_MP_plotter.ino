//
//    FILE: HX_MP_plotter.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: HX711 demo
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
  // Serial.println(__FILE__);
  // Serial.print("HX711_MP_LIB_VERSION: ");
  // Serial.println(HX711_MP_LIB_VERSION);
  // Serial.println();

  scale.begin(dataPin, clockPin);

  //  Calibration
  //  adjust the data to your measurements
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

  for (uint32_t raw = 0; raw <= 7000; raw += 20)
  {
    Serial.print(raw);
    Serial.print("\t");
    Serial.println(scale.testCalibration(raw));
  }
  delay(5000);
}


void loop()
{
  // continuous scale 4x per second
  f = scale.get_units(5);
  Serial.println(f);
  delay(250);
}


//  -- END OF FILE --
