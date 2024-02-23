//
//    FILE: 74HC138_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/74HC138


#include "74HC138.h"


DEV_74HC138 selector(5, 6, 7);

uint8_t line = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("LIB_74HC138_VERSION: ");
  Serial.println(LIB_74HC138_VERSION);

  selector.enable();
}


void loop()
{
  Serial.println(selector.getLine());
  delay(100);
  selector.setLine(line);
  line++;
  if (line >= 8) line = 0;
  delay(1000);
}


//  -- END OF FILE --
