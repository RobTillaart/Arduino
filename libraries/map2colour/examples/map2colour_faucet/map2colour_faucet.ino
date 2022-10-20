//
//    FILE: map2colour_faucet.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: map2colour demo
//     URL: https://github.com/RobTillaart/map2colour


//  demo simulates a temperature of a faucet mapped upon 2 colours.
//  blue = cold, black is middle, red is hot


#include "Arduino.h"
#include "map2colour.h"


map2colour mct;

//  values must be 7 elements in increasing order.
float values[7] = { 0,  10,  15,  25,  40,  100,  125 };
uint32_t faucet[7] =
{
  M2C_BLUE, M2C_BLUE, M2C_BLACK, M2C_BLACK, M2C_RED, M2C_RED, M2C_RED
};


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MAP2COLOUR_LIB_VERSION: ");
  Serial.println(MAP2COLOUR_LIB_VERSION);
  Serial.println();

  mct.begin(values, faucet);

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
