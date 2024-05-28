//
//    FILE: HC4067_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: Demo for HC4067 16 channel (simple) multiplexer
//          read 16 buttons / switches.
//     URL: https://github.com/RobTillaart/HC4067


#include "HC4067.h"

HC4067 mp(4, 5, 6, 7);  //  no enable pin defined connect to GND.

const int inputPin = 10;
uint16_t values;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("HC4067 LIBRARY VERSION: ");
  Serial.println(HC4067_LIB_VERSION);
  Serial.println();

  pinMode(inputPin, INPUT);

}


void loop()
{
  int channel = 16;
  values = 0;
  while (channel > 0)
  {
    channel--;
    mp.setChannel(channel);
    values <<= 1;
    if (digitalRead(inputPin) == HIGH) values += 1;
  }
  Serial.println(values, HEX);
  delay(1000);
}


//  -- END OF FILE --
