//
//    FILE: countdown_adaptive_display.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: http://forum.arduino.cc/index.php?topic=356253
//          https://github.com/RobTillaart/CountDown


#include "CountDown.h"

CountDown CD;

int wait = 2000;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("COUNTDOWN_LIB_VERSION: ");
  Serial.println(COUNTDOWN_LIB_VERSION);
  Serial.println();


  CD.start(0, 0, 2);  //  2 minutes => unit is MINUTES
}


void loop()
{
  Serial.print("Remaining: ");
  Serial.print(CD.remaining());
  Serial.print(" ");
  Serial.println(CD.getUnits());

  //  switch units and poll frequency for last minute.
  if ((CD.remaining() == 1) && (CD.getUnits() == 'M'))
  {
    wait = 1000;
    CD.stop();
    CD.start(0, 0, 0, 59);
  }
  delay(wait);
}


//  -- END OF FILE --
