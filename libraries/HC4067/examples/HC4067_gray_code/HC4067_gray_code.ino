//
//    FILE: HC4067_gray_code.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: Demo for HC4067 16 channel (simple) multiplexer
//     URL: https://github.com/RobTillaart/HC4067
//
//  By using GRAY codes for channel selection
//  there is only one address line changed at a time.
//  There might be projects where this is useful,
//  e.g. switching 16 outputs HIGH without ghosting
//  Pro: it is fastest channel switching possible
//  Con: it is not consecutive order of channels unless wired in GRAY order.
//
//  SCHEMA:
//  Connect A0 to multiplexer.


#include "HC4067.h"

HC4067 mp(4, 5, 6, 7, 8);  //  explicitly set enable pin (8)

//
//  GRAY table 0..15
//  note: sub-arrays 0..1, 0..3, 0..7 are also GRAY tables
//
//  GRAY decimal: 0, 1, 3, 2, 6, 7, 5, 4, 12, 13, 15, 14, 10, 11, 9, 8
uint8_t gray[16] = {
  0b0000, 0b0001, 0b0011, 0b0010, 0b0110, 0b0111, 0b0101, 0b0100,
  0b1100, 0b1101, 0b1111, 0b1110, 0b1010, 0b1011, 0b1001, 0b1000
};

//  reverse for completeness
uint8_t ungray[16] = { 0, 1, 3, 2, 7, 6, 4, 5, 15, 14, 12, 13, 8, 9, 11, 10 };


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("HC4067_LIB_VERSION: ");
  Serial.println(HC4067_LIB_VERSION);
  Serial.println();

  delay(1000);
  mp.enable();
}


void loop()
{
  for (uint8_t channel = 0; channel < 16; channel++)
  {
    int grayChannel = gray[channel];
    mp.setChannel(grayChannel);
    Serial.print(grayChannel);
    Serial.print("\t");
    Serial.print(ungray[grayChannel]);
    Serial.print("\t");
    Serial.println(analogRead(A0));
    delay(100);
  }
  Serial.println();
}


//  -- END OF FILE --
