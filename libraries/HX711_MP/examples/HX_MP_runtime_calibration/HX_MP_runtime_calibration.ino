//
//    FILE: HX_MP_runtime_calibration.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: HX711 demo
//     URL: https://github.com/RobTillaart/HX711_MP
//
//  Note: this example is not fool proof, just to get the idea.

#include "HX711_MP.h"


//  3 calibration points
//  all user defined.
HX711_MP scale(3);


//  adjust pins to your setup.
uint8_t dataPin  = 16;
uint8_t clockPin = 17;
uint8_t PIN_UP   = 18;
uint8_t PIN_DOWN = 19;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("HX711_MP_LIB_VERSION: ");
  Serial.println(HX711_MP_LIB_VERSION);
  Serial.println();

  scale.begin(dataPin, clockPin);

  //  Calibration
  //  adjust the data to your measurements
  //  setCalibrate(index, rawRead, weight);
  scale.setCalibrate(0, 1000, 0);
  scale.setCalibrate(1, 1500, 250);
  scale.setCalibrate(2, 2000, 500);

  pinMode(PIN_UP, INPUT_PULLUP);
  pinMode(PIN_DOWN, INPUT_PULLUP);
  delay(5000);
}


void loop()
{
  Serial.print("WEIGHT:\t");
  Serial.println(scale.get_units(5));

  //  adjustment for index 1  (hard coded)
  if (digitalRead(PIN_UP) == LOW)
  {
    float raw = scale.adjustCalibrateRaw(1, +10);
    Serial.print("RAW:\t");
    Serial.println(raw);
  }
  if (digitalRead(PIN_DOWN) == LOW)
  {
    float raw = scale.adjustCalibrateRaw(1, -10);
    Serial.print("RAW:\t");
    Serial.println(raw);
  }

  delay(250);
}


//  -- END OF FILE --
