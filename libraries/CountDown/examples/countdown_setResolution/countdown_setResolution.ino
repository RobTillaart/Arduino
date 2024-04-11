//
//    FILE: countdown_setResolution.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: http://forum.arduino.cc/index.php?topic=356253
//          https://github.com/RobTillaart/CountDown
//


#include "CountDown.h"

CountDown CD;


void setup()
{
    Serial.begin(115200);
    Serial.println(__FILE__);
    Serial.print("COUNTDOWN_LIB_VERSION: ");
    Serial.println(COUNTDOWN_LIB_VERSION);

    CD.setResolution(CountDown::MINUTES);
    //  countdown 1 minutes
    CD.start(1);
}


void loop()
{
  static uint32_t last_remaining = 0;
  if (last_remaining != CD.remaining() || CD.remaining() == 0 )
  {
    Serial.println();
    last_remaining = CD.remaining();
  }
  Serial.print(' ');
  Serial.print(CD.remaining());
  delay(5000);   //  every 5 seconds
}


//  -- END OF FILE --

