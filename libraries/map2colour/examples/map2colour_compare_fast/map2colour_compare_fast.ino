//
//    FILE: map2colour_compare_fast.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: map2colour demo
//     URL: https://github.com/RobTillaart/map2colour


#include "Arduino.h"
#include "map2colour.h"


map2colour mc;
map2colourFast mcf;

// should be in increasing order
float values[7] = { 0, 32, 64, 128, 256, 512, 1024 };


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MAP2COLOUR_LIB_VERSION: ");
  Serial.println(MAP2COLOUR_LIB_VERSION);
  Serial.println();

  // load the values array
  mc.begin(values);
  mcf.begin(values);

  Serial.println();
  Serial.println();
  Serial.println("map2RGB");

  //  show the interpolating
  for (float i = 0; i <= 1024; i++)
  {
    uint32_t rgb1 = mc.map2RGB(i);
    uint32_t rgb2 = mcf.map2RGB(i);
    Serial.print(i);
    Serial.print("\t");
    Serial.print(rgb1, HEX);
    Serial.print("\t");
    Serial.print(rgb2, HEX);
    Serial.print("\t");
    Serial.println((rgb1 == rgb2) ? "" : "<<<<");  //  fails
  }
  Serial.println();
  Serial.println();
  Serial.println("map2_565");

  //  show the interpolating
  for (float i = 0; i <= 1024; i++)
  {
    uint16_t rgb1 = mc.map2_565(i);
    uint16_t rgb2 = mcf.map2_565(i);
    Serial.print(i);
    Serial.print("\t");
    Serial.print(rgb1, HEX);
    Serial.print("\t");
    Serial.print(rgb2, HEX);
    Serial.print("\t");
    Serial.println((rgb1 == rgb2) ? "" : "<<<<");  //  fails
  }
  Serial.println();
  Serial.println();

  Serial.println("Done...");
}


void loop()
{

}


// -- END OF FILE --
