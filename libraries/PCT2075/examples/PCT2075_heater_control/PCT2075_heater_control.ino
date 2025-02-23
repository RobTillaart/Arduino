//
//    FILE: PCT2075_heater_control.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo PCT2075 temperature sensor
//     URL: https://github.com/RobTillaart/PCT2075
//
//  connect OS pin to a heater, use an approproate relay etc
//          alternative, connect an LED (with 220 Ohm resistor).
//          e.g. to control an aquarium between 22C and 24C

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
  pct.setOSPolarityLOW();      //  OS goes HIGH in alarm
  pct.setHysteresis(22);       //  LOWER threshold (switches ON)
  pct.setOverTemperature(24);  //  UPPER threshold (switches OFF)
}


void loop()
{
  temperature = pct.getTemperature();
  Serial.println(temperature);
  delay(1000);
}



//  -- END OF FILE --
