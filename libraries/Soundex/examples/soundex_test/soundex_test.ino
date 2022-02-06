//
//    FILE: soundex_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo


#include "Arduino.h"
#include "Soundex.h"

Soundex SDX;

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  while (!Serial);

  Serial.println();
  Serial.print("SOUNDEX_LIB_VERSION: ");
  Serial.println(SOUNDEX_LIB_VERSION);
  delay(100);
  
  start = micros();
  char * p = SDX.soundex("soundex");
  stop = micros();
  Serial.print(p);
  Serial.print("\t");
  Serial.println(stop - start);

  // examples from wikipedia
  Serial.println(SDX.soundex("Robert"));    // R163
  Serial.println(SDX.soundex("Rupert"));    // R163
  Serial.println(SDX.soundex("Rubin"));     // R150
  Serial.println(SDX.soundex("Tymczak"));   // T522
  Serial.println(SDX.soundex("Pfister"));   // P236
  Serial.println(SDX.soundex("Honeyman"));  // H555

  SDX.setLength(10);
  // e.g. for long chemical names
  Serial.println(SDX.soundex("Trichloroethylene"));       // T624634500
  Serial.println(SDX.soundex("pentacarbon decahydrate")); // P532615323
  Serial.println(SDX.soundex("deoxyribonucleic acid"));   // D261524223
}


void loop()
{
}


// -- END OF FILE --
