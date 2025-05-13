//    FILE: Metronome_simple.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo Metronome library
//     URL: https://github.com/RobTillaart/Metronome


#include "Metronome.h"

Metronome M(13);

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("METRONOME_LIB_VERSION: ");
  Serial.println(METRONOME_LIB_VERSION);
  Serial.println();

  M.begin();
  M.setBeatsPerMinute(120);
  M.setMeasure(6);
  M.start();
}

void loop()
{
  // call as often as possible eg every millisecond
  M.check();
}
