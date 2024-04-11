//
//    FILE: countdown_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: http://forum.arduino.cc/index.php?topic=356253
//          https://github.com/RobTillaart/CountDown
//


#include "CountDown.h"

CountDown CD(CountDown::MINUTES);

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("COUNTDOWN_LIB_VERSION: ");
  Serial.println(COUNTDOWN_LIB_VERSION);

  delay(random(2000));
  start = millis();
  CD.start(3);
  Serial.println(start);

  while (CD.remaining() > 0 )
  {
    // Serial.print(millis());
    // Serial.print("\t");
    // Serial.println(CD.remaining() );
    // delay(100);
  }
  Serial.println(millis() - start);  //  SHOULD PRINT 180000

  Serial.println(CD.remaining());
  Serial.println("done...");
}


void loop()
{
}


//  -- END OF FILE --

