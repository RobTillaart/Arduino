//
//    FILE: minmax_dampening.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/minmax
//
//  use plotter to get a view

#include "MINMAX.h"


MINMAX mm;

uint32_t start, stop;

float n = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MINMAX_LIB_VERSION: ");
  Serial.println(MINMAX_LIB_VERSION);
  Serial.println();

  mm.reset();
  mm.setAutoResetCount(10000);


}


void loop()
{
  //  mm.setDampening(1);
  //  int r = random(n--) - 500;
  //  if (n <= 0) n = 1000;

  mm.setDampening(0.5);
  int r = sin(n) * 100 + 100;
  n += 0.01;
  mm.add(r);

  Serial.print(r);
  Serial.print("\t");
  Serial.print(mm.minimum());
  Serial.print("\t");
  Serial.print(mm.maximum());
  Serial.print("\n");

  delay(10);
}


//  -- END OF FILE --
