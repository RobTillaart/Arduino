//
//    FILE: M62429_interactive.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo volume IC FM62429


#include "M62429.h"

uint32_t start, stop;

M62429  AMP;

uint8_t attn = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  AMP.begin(4, 5);  //  data, clock

  //  sweep to start
  /*
    for (int v = 0; v < 256; v++)
    {
    AMP.setVolume(2, v);
    delay(10);
    }
    for (int v = 255; v > 0; v--)
    {
    AMP.setVolume(2, v);
    delay(10);
    }
  */
}


void loop()
{
  //  Serial.println("M62429 interactive");
  //  Serial.println("D = decr -1");
  //  Serial.println("I = incr +1");
  //  Serial.println("0 = 0");
  //  Serial.println("* = max");

  while (! Serial.available());

  uint8_t cmd = tolower(Serial.read());
  switch (cmd)
  {
    case 'd':
      AMP.decr();
      break;
    case 'i':
      AMP.incr();
      break;
    case '0':
      AMP.setVolume(2, 0);
      break;
    case '*':
      AMP.setVolume(2, 255);
      break;
    default:
      Serial.println("UNK");
      break;
  }
  int vol = AMP.getVolume(2);
  Serial.println(vol);
  delay(10);
}


//  -- END OF FILE --
