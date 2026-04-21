//
//    FILE: fastTrig_3_phase.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test the threePhase256
//     URL: https://github.com/RobTillaart/FastTrig
//
//  sketch to visually show 3 phases 120 degrees.
//  use IDE.plotter to view.


#include "FastTrig.h"


uint32_t start, stop;

int phase1, phase2, phase3;

volatile int i;

void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("FAST_TRIG_LIB_VERSION: ");
  Serial.println(FAST_TRIG_LIB_VERSION);
  Serial.println();

  //  clean plotter buffer
  for (int i = 0; i < 500; i++)
  {
    Serial.print(0);
    Serial.print("\t");
    Serial.print(0);
    Serial.print("\t");
    Serial.print(0);
    Serial.print("\t");
    Serial.print(0);
    Serial.print("\t");
    Serial.print(0);
    Serial.print("\t");
    Serial.print(0);
    Serial.print("\t");
    Serial.println();
  }

  //  output performance (angle 0..90)
  //  67  235 -31 -204  9124  = 3 calls
  //  67  235 -31 -204  5484  = 1 call  (~40% faster)
  delay(100);
  int angle = random(1000);
  start = micros();
  for (i = 0; i < 1000; i++)
  {
    phase1 = isin256(angle);
    phase2 = isin256(angle + 120);
    phase3 = isin256(angle + 240);
  }
  stop = micros();

  Serial.print(angle);
  Serial.print('\t');
  Serial.print(phase1);
  Serial.print('\t');
  Serial.print(phase2);
  Serial.print('\t');
  Serial.print(phase3);
  Serial.print('\t');
  Serial.println(stop - start);
  delay(100);

  start = micros();
  for (i = 0; i < 1000; i++)
  {
    threePhase256(angle, &phase1, &phase2, &phase3);
  }
  stop = micros();

  Serial.print(angle);
  Serial.print('\t');
  Serial.print(phase1);
  Serial.print('\t');
  Serial.print(phase2);
  Serial.print('\t');
  Serial.print(phase3);
  Serial.print('\t');
  Serial.println(stop - start);
  delay(100);

  while (1);
  Serial.println("P1\tP2\tP3");
}


void loop()
{
  uint32_t now = millis();
  float freq = 10;
  int angle = fmod(freq * (now * 360e-3), 360);

  //  phase1 = isin256(angle);
  //  phase2 = isin256(angle + 120);
  //  phase3 = isin256(angle + 240);

  threePhase256(angle, &phase1, &phase2, &phase3);

  Serial.print(now);
  Serial.print('\t');
  Serial.print(phase1);
  Serial.print('\t');
  Serial.print(phase2);
  Serial.print('\t');
  Serial.print(phase3);
  Serial.println();
}


//  -- END OF FILE --
