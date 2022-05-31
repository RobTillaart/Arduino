//
//    FILE: SHEXA_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo SHEX hex dump class
//    DATE: 2022-05-28


#include "SHEX.h"


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("SHEX_LIB_VERSION: ");
  Serial.println(SHEX_LIB_VERSION);

  Serial.println("\nNORMAL\n");
  for (int i = 0; i < 64; i++)
  {
    Serial.print(random(127));
    Serial.print('\t');
    if ((i % 16) == 0) Serial.println();
  }

  Serial.println("\n\nSHEX ASCII TEST");
  SHEXA shex(&Serial, 16);
  shex.setCountDigits(5);
  shex.print("abcdefghijklmnopqrstuvwxyz");
  shex.flushASCII();
  shex.restartOutput();

  shex.print("abcdefghijklmnopqrstuv");
  shex.flushASCII();
  shex.restartOutput();


  Serial.println("\n Done...\n");
}


void loop()
{
}


// -- END OF FILE --
