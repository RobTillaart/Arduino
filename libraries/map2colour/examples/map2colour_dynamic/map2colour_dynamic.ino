//
//    FILE: map2colour_dynamic.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: map2colour demo
//     URL: https://github.com/RobTillaart/map2colour


#include "Arduino.h"
#include "map2colour.h"


map2colour mc(12);


//  must be in increasing order
float values[12] = { 0, 33, 66, 100, 150, 200, 250, 300, 400, 600, 800, 1024 };

//  arbitrary colors
uint32_t colmap[12] =
{
  M2C_BLACK,  M2C_SILVER,  M2C_GRAY,
  M2C_WHITE,  M2C_MAROON,  M2C_RED,
  M2C_PURPLE, M2C_FUCHSIA, M2C_GREEN,
  M2C_LIME,   M2C_OLIVE,   M2C_YELLOW
};



void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MAP2COLOUR_LIB_VERSION: ");
  Serial.println(MAP2COLOUR_LIB_VERSION);
  Serial.println();

  //  load the values array
  mc.begin(values, colmap);

  //  show the interpolating
  for (float i = 0; i < 1024; i += 10)
  {
    uint32_t rgb = mc.map2RGB(i);
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
