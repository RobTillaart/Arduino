//    FILE: Metronome_tick_tock.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo Metronome library
//     URL: https://github.com/RobTillaart/Metronome
//
// uses two LEDs to indicate the tick (GREEN) and tock (RED).
// could also drive other devices.

#include "Metronome.h"

//  two colors to differentiate between "tick and tock"
#define GREEN_LED_PIN     12
#define RED_LED_PIN       13

Metronome M(GREEN_LED_PIN, RED_LED_PIN);


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
  M.setMeasure(4);
  M.start();
}


void loop()
{
  // call as often as possible eg every millisecond
  M.check();
}


//  -- END OF FILE --

