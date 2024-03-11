//
//    FILE: KT0803_sweep_2_seconds.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: minimal demo
//     URL: https://github.com/RobTillaart/KT0803


#include "Arduino.h"
#include "Wire.h"
#include "KT0803.h"


KT0803 FM_SEND;


void setup()
{
  Serial.begin(115200);
  while(!Serial);

  Wire.begin();
  FM_SEND.begin();
  FM_SEND.setMute(false);
}

void loop()
{
  //  adjust to your local allowed frequencies
  for (float freq = 88.0; freq <= 108.0; freq += 0.1)
  {
    FM_SEND.setFrequency(freq);
    delay(2000);
  }
}


//  -- END OF FILE --
