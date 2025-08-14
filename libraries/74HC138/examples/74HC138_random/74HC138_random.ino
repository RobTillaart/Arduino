//
//    FILE: 74HC138_random.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test random lines.
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
  Serial.println();

  selector.enable();
}


void loop()
{
  selector.setLine(random(8));
  Serial.println(selector.getLine());
  delay(random(200));
}


//  -- END OF FILE --
