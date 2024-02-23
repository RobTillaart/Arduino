//
//    FILE: 74HC154_prev_next.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/74HC154


#include "74HC154.h"


DEV_74HC154 selector(5, 6, 7, 8);

uint8_t line = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("LIB_74HC154_VERSION: ");
  Serial.println(LIB_74HC154_VERSION);

  selector.enable();
}


void loop()
{
  for (int i = 0; i < 30; i++)
  {
    Serial.println(selector.getLine());
    selector.nextLine();
    delay(100);
  }
  for (int i = 0; i < 30; i++)
  {
    Serial.println(selector.getLine());
    selector.prevLine();
    delay(100);
  }

}


//  -- END OF FILE --
