//
//    FILE: countdown_overflow_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test overflow behavior (micros is fastest to test)
//     URL: http://forum.arduino.cc/index.php?topic=356253
//          https://github.com/RobTillaart/CountDown


#include "CountDown.h"

CountDown CD(CountDown::MICROS);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("COUNTDOWN_LIB_VERSION: ");
  Serial.println(COUNTDOWN_LIB_VERSION);

  //  wait for almost overflow ~70 minutes !!
  while (micros() < 4290000000UL)
  {
    Serial.println(micros());
    delay(1000);
  }
  Serial.println("----------------------");
  
  CD.setResolution(CountDown::MICROS);
  CD.start(1 * 60 * 1000000UL);  //  1 minute = 60 seconds
}


void loop()
{
  Serial.print("Remaining: ");
  Serial.print(CD.remaining());
  Serial.print(" ");
  Serial.println(CD.getUnits());
  delay(1000);
}


//  -- END OF FILE --
