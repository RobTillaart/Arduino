//
//    FILE: ACD10_manual_calibration.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo manual calibration mode
//     URL: https://github.com/RobTillaart/ACD10


#include "ACD10.h"

ACD10 mySensor(&Wire);  //  explicit default, not needed.

uint16_t CO2VALUE = 410;

void setup()
{
  //  while(!Serial);  //  uncomment if needed
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("ACD10_LIB_VERSION: ");
  Serial.println(ACD10_LIB_VERSION);
  Serial.println();

  Wire.begin();
  mySensor.begin();

  //  sensor is default in auto calibration mode
  //  make it explicit manual
  Serial.print("Set manual calibration: ");
  if (mySensor.setCalibrationMode(ACD10_CALIBRATE_MANUAL))
  {
    Serial.println("OK.");
  }
  else
  {
    Serial.println("FAIL.");
    Serial.println("Check your hardware setup and restart.");
  }
  Serial.println();


  //  set known value outdoors
  //  configure calibration value.
  Serial.println("Place device in open air.");
  Serial.println("Set open CO2 air value (around 400-420).");
  Serial.println("+ - s == start, r = reset.");
  bool start = false;
  while (!start)
  {
    while (Serial.available() == 0);
    int c = Serial.read();
    if (c == '+') CO2VALUE++;
    if (c == '-') CO2VALUE--;
    if (c == 'r') CO2VALUE = 410;
    if (c == 's') start = true;
    Serial.println(CO2VALUE);
  }
  Serial.println("Start calibrating...");
  Serial.println();

  Serial.print("Write calibration value: ");
  Serial.print(CO2VALUE);
  if (mySensor.setManualCalibration(CO2VALUE))
  {
    Serial.println(" FAILED.");
  }
  else
  {
    Serial.println(" OK.");
  }

  uint16_t value = mySensor.readManualCalibration();
  Serial.print("Read back calibration value: ");
  Serial.println(value);
  if (value == CO2VALUE)
  {
    Serial.println("Calibration succes.");
  }
  else
  {
    Serial.print("Calibration failed. Redo.");
  }


  //  wait 20 minutes.
  for (int n = 20; n > 0; n--)
  {
    Serial.print("Minutes left: ");
    Serial.println(n);
    delay(60000UL);
  }
  Serial.println();
  Serial.println();
  Serial.println("Done...");
}


void loop()
{
}


//  -- END OF FILE --
