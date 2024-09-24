//
//    FILE: TLC5917_demo_setChannel.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo basic usage
//     URL: https://github.com/RobTillaart/TLC5917


//            TLC5917
//          +----u----+
//    GND   | 1    16 |  VDD
//    SDI   | 2    15 |  R-EXT
//    CLK   | 3    14 |  SDO
//    LE    | 4    13 |  OE
//    OUT0  | 5    12 |  OUT7
//    OUT1  | 6    11 |  OUT6
//    OUT2  | 7    10 |  OUT5
//    OUT3  | 8    09 |  OUT4
//          +---------+


#include "TLC5917.h"


const int DEVICES = 1;
const int CLOCK   = 13;
const int DATA    = 12;
const int LATCH   = 11;
const int ENABLE  = 10;

TLC5917 tlc(DEVICES, CLOCK, DATA, LATCH, ENABLE);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("TLC5917_LIB_VERSION: \t");
  Serial.println(TLC5917_LIB_VERSION);
  Serial.println();

  Serial.println(sizeof(tlc));

  if (tlc.begin() == false)
  {
    Serial.println("error");
    while (1);
  }

  Serial.print("Channels: ");
  Serial.println(tlc.channelCount());

  tlc.enable();
}


void loop()
{
  uint8_t arr[DEVICES];
  for (int idx = 0; idx < DEVICES; idx++)
  {
    arr[idx] = random(256);
  }
  tlc.setChannel(arr);
  tlc.write();
  delay(100);
}


//  -- END OF FILE --
