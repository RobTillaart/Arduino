//
//    FILE: map2colour_wavelength.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: map2colour demo rainbow
//     URL: https://github.com/RobTillaart/map2colour

//  demo simulates a conversion of wavelength in nanometer to RGB color 
//  think of it as a rainbow.
//  note the mapping is not exact as not all colors exist in RGB space.


#include "Arduino.h"
#include "map2colour.h"


map2colour mcp(14);


//  should be in increasing order; and 7 elements
//  pressure in mbar
float values[14] = { 400, 415, 460, 465, 490, 495, 545, 550, 575, 580, 610, 615, 675, 780 };
uint32_t colours[14] =
{
  //  COLOR        wavelength (nm) + descriptive color
  0x00000000,  //  400  black
  0x002500FF,  //  415  purple
  
  0x000800FF,  //  460
  0x000003FF,  //  465  blue
  
  0x0000E9FF,  //  490
  0x0000FFD7,  //  495  cyan
  
  0x0000FF19,  //  545  green
  0x0004FF00,  //  550
  
  0x00C2FF00,  //  575  yellow
  0x00FFEA00,  //  580
  
  0x00FF0300,  //  610  red
  0x00FF0008,  //  615
  
  0x00FF002C,  //  675
  0x00000000,  //  780  black
};


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("MAP2COLOUR_LIB_VERSION: ");
  Serial.println(MAP2COLOUR_LIB_VERSION);
  Serial.println();

  mcp.begin(values, colours);
  for (int i = 380; i < 800; i++)
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
}


//  -- END OF FILE --
