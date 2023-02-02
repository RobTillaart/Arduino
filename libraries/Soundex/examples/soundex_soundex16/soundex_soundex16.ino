//
//    FILE: soundex_soundex16.ino
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
  delay(1000);

  Serial.println("\nTrichloroethylene");
  start = micros();
  char * p = SDX.soundex("Trichloroethylene");
  stop = micros();
  Serial.print(p);
  Serial.print("\t");
  Serial.println(stop - start);
  delay(100);

  start = micros();
  p = SDX.soundex("Trichloroethylene");
  stop = micros();
  Serial.print(p);
  Serial.print("\t");
  Serial.println(stop - start);
  delay(100);

  start = micros();
  uint16_t v16 = SDX.soundex16("Trichloroethylene");
  stop = micros();
  Serial.print(v16);
  Serial.print("\t");
  Serial.println(stop - start);
  delay(100);

  start = micros();
  uint32_t v32 = SDX.soundex32("Trichloroethylene");
  stop = micros();
  Serial.print(v32);
  Serial.print("\t");
  Serial.println(stop - start);
  delay(100);

  Serial.println();

  Serial.println("\nExamples from wikipedia");
  Serial.println(SDX.soundex16("Robert"), HEX);     //  A203
  Serial.println(SDX.soundex16("Rupert"), HEX);     //  A203
  Serial.println(SDX.soundex16("Rubin"), HEX);      //  A1BD
  Serial.println(SDX.soundex16("Tymczak"), HEX);    //  B956
  Serial.println(SDX.soundex16("Pfister"), HEX);    //  901A
  Serial.println(SDX.soundex16("Honeyman"), HEX);   //  4972

  Serial.println();
  Serial.println("\nSoundex32 - 3 chemicals");
  Serial.println(SDX.soundex32("Trichloroethylene"), HEX);       //  2FE4F75B
  Serial.println(SDX.soundex32("pentacarbon decahydrate"), HEX); //  25F6EB97
  Serial.println(SDX.soundex32("deoxyribonucleic acid"), HEX);   //  835BD86

  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --
