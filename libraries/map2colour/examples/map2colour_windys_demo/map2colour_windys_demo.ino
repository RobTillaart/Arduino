//
//    FILE: map2colour_windys_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/map2colour
//          https://github.com/RobTillaart/map2colour/issues/9

#include "Arduino.h"
#include "map2colour.h"

map2colour mc(13);

// float windys_values[] = { -70, -55, -40, -25, -15, -8.33, -3.89, 0, 1, 10, 21, 30, 45};  //  Celsius
float windys_values[13] = { -94,-67,-40,-13,5,17,25,32,34,50,70,86,116};  //  Fahrenheit.
uint32_t windys_colour[13] =
{
  0x734669, 0xcaacc3, 0xa24691, 0x8f59a9, 0x9ddbd9, 0x6abfb5, 0x64a6bd, 
  0x5d85c6, 0x447d63, 0x809318, 0xf3b704, 0xe85319, 0x470e00
};


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MAP2COLOUR_LIB_VERSION: ");
  Serial.println(MAP2COLOUR_LIB_VERSION);
  Serial.println();

  //  load the windys arrays
  mc.begin(windys_values, windys_colour);

  //  show the interpolating
  for (float i = -100; i < 125; i += 5)
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
