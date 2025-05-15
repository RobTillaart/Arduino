//    FILE: Metronome_potmeter.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo control BPM with potmeter
//     URL: https://github.com/RobTillaart/Metronome
//
//  uses build in LED Arduino UNO to indicate the BPM
//  uses a potentiometer to set the BPM.

#include "Metronome.h"

#define LED_PIN       13

Metronome M(LED_PIN);

int BPM = 120;

uint32_t lastTime = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("METRONOME_LIB_VERSION: ");
  Serial.println(METRONOME_LIB_VERSION);
  Serial.println();

  M.begin();
  M.setBeatsPerMinute(BPM);
  M.start();
}


void loop()
{
  uint32_t now = millis();
  //  reading the potmeter 10x per second.
  if (now - lastTime >= 100)
  {
    lastTime = now;
    BPM = analogRead(A0) / 3;  //  0..340
    M.setBeatsPerMinute(BPM);
  }
  // call as often as possible eg every millisecond
  M.check();
}


//  -- END OF FILE --

