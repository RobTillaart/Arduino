//
//    FILE: map2colour_intensity.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: map2colour demo
//    DATE: 2021-12-06
//     URL: https://github.com/RobTillaart/map2colour


// demo simulates a temperature mapped upon 1 colour intensity.
// low temperature = no colour, higher is more intense RED


#include "Arduino.h"
#include "map2colour.h"


map2colour mct;

// values must be 7 elements in increasing order
float values[7] = { 20,    100,  125,  150,  200,  250,  300 };
uint32_t colours[7] =
{
  M2C_BLACK, M2C_RED, M2C_RED, M2C_RED, M2C_RED, M2C_RED, M2C_RED
};


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  mct.begin(values, colours);

  for (int i = -20; i < 125; i++)
  {
    uint32_t rgb = mct.map2RGB(i);
    Serial.print(i);
    Serial.print("\t");
    Serial.println(rgb, HEX);
  }
  Serial.println();
}


void loop()
{
}


// -- END OF FILE --
