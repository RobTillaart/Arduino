//
//    FILE: SHEX_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo SHEX hex dump class
//    DATE: 2020-05-24


#include "SHEX.h"


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  Serial.println("\nNORMAL\n");
  for (int i = 0; i < 64; i++)
  {
    Serial.print(random(127));
    Serial.print('\t');
    if ((i % 16) == 0) Serial.println();
  }


  Serial.println("\n\nSHEX\n");
  SHEX shex(&Serial, 16);

  for (int i = 0; i < 300; i++)
  {
    char c = random(150);
    shex.print(c);
  }


  Serial.println("\n\nSHEX modified\n");
  shex.setBytesPerLine(60);
  shex.setSeparator('-');
  shex.setCountFlag(false);

  for (int i = 0; i < 600; i++)
  {
    char c = random(150);
    shex.print(c);
  }

  Serial.println("\n Done...\n");
}


void loop()
{
}


// -- END OF FILE --

