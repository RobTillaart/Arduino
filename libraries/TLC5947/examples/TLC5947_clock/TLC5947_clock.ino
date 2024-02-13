//
//      FILE: TLC5947_clock.ino
//    AUTHOR: Rob Tillaart
//   PURPOSE: demo visual clock.
//       URL: https://github.com/RobTillaart/TLC5947

//  Every output is one hour
//  The intensity is the nr of minutes

#include "TLC5947.h"

int DEVICES = 1;
const int CLOCK = 13;
const int DATA  = 12;
const int LATCH = 11;
const int BLANK = 10;

TLC5947 tlc(DEVICES, CLOCK, DATA, LATCH, BLANK);

//  should of course be read from an RTC
int hour = 12;
int minutes = 59;
int seconds = 0;

uint32_t lastTime = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("TLC5947_LIB_VERSION: \t");
  Serial.println(TLC5947_LIB_VERSION);

  tlc.begin();
  tlc.enable();
}


void loop()
{
  uint32_t now = millis();

  if (now - lastTime > 1000)
  {
    lastTime += 1000;
    seconds++;
    if (seconds >= 60)
    {
      seconds = 0;
      minutes++;
    }
    if (minutes >= 60)
    {
      minutes = 0;
      hour++;
    }
    if (hour >= 24)
    {
      hour = 0;
    }
    for (int h = 0; h < tlc.getChannels(); h++)
    {
      if (h <= hour) tlc.setPWM(h, 4095);
      else tlc.setPWM(h, 0);
    }
    tlc.setPWM(hour, (minutes * 4095UL) / 60);  //  might need to be gamma corrected.
    tlc.write();
  }

}


//  -- END OF FILE --
