//
//    FILE: map2colour_pressure.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: map2colour demo
//     URL: https://github.com/RobTillaart/map2colour


//  demo simulates a pressure sensor and its mapping on three colours
//  pressure 950,  990,   1010,  1030    1050, 2000, 2000
//           RED  YELLOW  GREEN  YELLOW  RED  WHITE  WHITE


#include "Arduino.h"
#include "map2colour.h"


map2colour mcp;


//  should be in increasing order; and 7 elements
//  pressure in mbar
float values[7] = { 950, 990, 1010, 1030, 1050, 2000, 2500 };
uint32_t colours[7] =
{
  M2C_RED, M2C_YELLOW, M2C_GREEN, M2C_YELLOW, M2C_RED, M2C_WHITE, M2C_WHITE
};


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MAP2COLOUR_LIB_VERSION: ");
  Serial.println(MAP2COLOUR_LIB_VERSION);
  Serial.println();

  mcp.begin(values, colours);
  for (int i = 950; i < 1050; i++)
  {
    uint32_t rgb = mcp.map2RGB(i);
    Serial.print(i);
    Serial.print("\t");
    Serial.println(rgb, HEX);
  }
  Serial.println();
}


void loop()
{
  float pressure = 950 + random(100);  //  add your sensor
  uint32_t rgb = mcp.map2RGB(pressure);
  Serial.print("P: ");
  Serial.println(rgb, HEX);            //  replace with PWM-RGB led 
  delay(1000);
}


// -- END OF FILE --
