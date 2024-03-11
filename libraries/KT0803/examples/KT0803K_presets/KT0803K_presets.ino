//
//    FILE: KT0803K_minimal.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: minimal demo hardcoded presets
//     URL: https://github.com/RobTillaart/KT0803


#include "Arduino.h"
#include "Wire.h"
#include "KT0803.h"


KT0803K FM_SEND;

//  hardcoded presets adjust to your need.
//  note: presets by channel would take half the memory
float preset[10] =
{
  88.6, 91.3, 92.2, 96.0, 97.3,
  98.8, 100.1, 100.3, 105.4, 107.6
};


void setup()
{
  Serial.begin(115200);
  while (!Serial);

  Wire.begin();

  FM_SEND.begin(preset[0], false);
}


void loop()
{
  if (Serial.available())
  {
    char c = Serial.read();

    if (c == 'm') FM_SEND.setMute(false);
    if (c == 'M') FM_SEND.setMute(true);
    //  select preset  0..9
    int  p = c - '0';  //  convert to digit
    if ((0 <= p) && (p <= 9)) FM_SEND.setFrequency(preset[p]);
  }
}


//  -- END OF FILE --
