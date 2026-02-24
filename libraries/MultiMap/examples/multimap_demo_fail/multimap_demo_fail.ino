//
//    FILE: multimap_demo_fail.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: minimal demo
//     URL: https://github.com/RobTillaart/MultiMap
//
//  compare to multimap_demo_big.ino.
//
//  View this demo on the serial plotter how it fails (at least on UNO R3)
//  due to a mix of signed and unsigned math.
//  If you need this mapping and it fails for you 
//  the interpolation in MultiMap.h needs the casting line.


#include "MultiMap.h"

//  note mixed signs
uint16_t in[300];
int16_t out[300];


void setup()
{
  //  while(!Serial);
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("MULTIMAP_LIB_VERSION: ");
  Serial.println(MULTIMAP_LIB_VERSION);
  Serial.println();

  Serial.println("X\tY");

  for (int i = 0; i < 300; i++)
  {
    in[i] = i * 3;
    out[i] = 32767 * sin(i * 0.1);
  }

  for (int i = 0; i <= 500; i++)
  {
    int16_t y = multiMap<uint16_t, int16_t>(i, in, out, 300);
    Serial.print(i);
    Serial.print("\t");
    Serial.println(y * 0.01);
  }
}


void loop()
{
}


//  -- END OF FILE --
