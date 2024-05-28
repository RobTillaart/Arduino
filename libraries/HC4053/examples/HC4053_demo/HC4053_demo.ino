//
//    FILE: HC4053_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: Demo for HC4051 8 channel (simple) multiplexer
//     URL: https://github.com/RobTillaart/HC4053


#include "HC4053.h"

HC4053 mp(4, 5, 6);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("HC4053 LIBRARY VERSION: ");
  Serial.println(HC4053_LIB_VERSION);
  Serial.println();

  delay(1000);
}


void loop()
{
  mp.setChannelA(0);
  Serial.println(analogRead(A0));
  delay(100);

  mp.setChannelB(0);
  Serial.println(analogRead(A1));
  delay(100);

  mp.setChannelC(0);
  Serial.println(analogRead(A2));
  delay(100);

  mp.setChannelA(1);
  Serial.println(analogRead(A0));
  delay(100);

  mp.setChannelB(1);
  Serial.println(analogRead(A1));
  delay(100);

  mp.setChannelC(1);
  Serial.println(analogRead(A2));
  delay(100);


  Serial.println();
}


//  -- END OF FILE --
