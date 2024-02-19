//
//    FILE: LineFormatter_histogram.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo LineFormatter class
//     URL: https://github.com/RobTillaart/LineFormatter


#include "LineFormatter.h"

LineFormatter L;

int x;

void setup()
{
  Serial.begin(115200);
  L.println();
  L.println(__FILE__);
  L.print("LINEFORMATTER_LIB_VERSION: ");
  L.println(LINEFORMATTER_LIB_VERSION);
  L.repeat(3, '\n');

  L.addTab(10);
  L.addTab(35);
  L.addTab(60);
}


void loop()
{
  L.repeat(3, '\n');

  //  header
  L.println("port\t0%\t50%\t100%");
  L.repeat(12, "----+", 1);

  //  data
  L.print("R0");
  L.tab();
  L.repeat(random(1000) / 20, '>', 1);
  L.print("R1");
  L.tab();
  L.repeat(random(1000) / 20, '>', 1);
  L.print("R2");
  L.tab();
  L.repeat(random(1000) / 20, '>', 1);


  delay(1000);
}




//  -- END OF FILE --
