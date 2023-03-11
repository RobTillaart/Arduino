//
//    FILE: HX_MP_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: HX711_MP demo
//     URL: https://github.com/RobTillaart/HX711


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

  Serial.println("\nUNCALIBRATED");
  delay(1000);

  measure(10);


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

  Serial.println("\nCALIBRATED");
  delay(1000);
  measure(10);

  Serial.println("\nSLEEP");
  scale.power_down();
  delay(2000);
  scale.power_up();
  Serial.println("\nWAKE UP");
  delay(1000);
  measure(10);

  //
  //  PERFORMANCE
  //  100x get_units(1) = 9404352  (UNO)
  //  VAL: 0.05
  //
  Serial.println("\nPERFORMANCE");
  delay(10);
  start = micros();
  f = 0;
  for (int i = 0; i < 100; i++)
  {
    f = scale.get_units(1);
  }
  stop = micros();
  Serial.print("100x get_units(1) = ");
  Serial.println(stop - start);
  Serial.print("  VAL: ");
  Serial.println(f, 2);

  Serial.println("\nPRECISION");
  f = 0;
  for (int i = 0; i < 100; i++)
  {
    f += scale.get_units(1);
  }
  Serial.print("  VAL:");
  Serial.println(f * 0.01, 4);
}


void loop()
{
  //  continuous scale 4x per second
  //  f = scale.get_units(5);
  //  Serial.println(f);
  //  delay(250);
}


void measure(uint8_t cnt)
{
  Serial.print("  RAW: ");
  Serial.println(scale.read());
  Serial.print("  AVG: ");
  Serial.println(scale.read_average(cnt));
  Serial.print("VALUE: ");
  Serial.println(scale.get_value(cnt));
  Serial.print("UNITS: ");
  Serial.println(scale.get_units(cnt), 1);
}


//  -- END OF FILE --
