//
//    FILE: PCT2075_fan_control.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo PCT2075 temperature sensor
//     URL: https://github.com/RobTillaart/PCT2075
//
//  connect OS pin to a fan, use an approproate relay etc
//          alternative, connect an LED (with 220 Ohm resistor).
//  

#include "PCT2075.h"

PCT2075 pct(0x37);

uint32_t lastTime = 0;
float temperature = 0;

void setup()
{
  while (!Serial);
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PCT2075_LIB_VERSION: ");
  Serial.println(PCT2075_LIB_VERSION);
  Serial.println();

  Wire.begin();

  bool b = pct.begin();
  Serial.print("BEGIN:\t");
  Serial.println(b);

  //  CONFIGURE FAN PARAMETERS
  pct.setOSComparatorMode();   //  explicit
  pct.setOSPolarityHIGH();     //  OS goes HIGH in alarm
  pct.setHysteresis(25);       //  LOWER threshold (switches OFF)
  pct.setOverTemperature(30);  //  UPPER threshold (switches ON)
}


void loop()
{
  temperature = pct.getTemperature();
  Serial.println(temperature);
  delay(1000);
}



//  -- END OF FILE --
