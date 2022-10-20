//
//    FILE: map2colour_gradient_break.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: map2colour demo
//     URL: https://github.com/RobTillaart/map2colour


#include "Arduino.h"
#include "map2colour.h"


map2colour mc;

//  note that 128 appears twice.
float values[7] = { 0, 32, 64, 128, 128, 256, 512 };
uint32_t colours[7] = { M2C_BLUE, M2C_AQUA, M2C_LIME, M2C_BLUE, M2C_RED, M2C_YELLOW, M2C_GREEN};

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MAP2COLOUR_LIB_VERSION: ");
  Serial.println(MAP2COLOUR_LIB_VERSION);
  Serial.println();

  //  load the values array and colours array
  mc.begin(values, colours);

  //  show the interpolating - note the break between 128 and 129.
  for (float i = 0; i < 512; i++)
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
