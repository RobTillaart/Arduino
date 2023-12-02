//    FILE: NC_001.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: pseudo random noise from analogWrite + Neumann Corrector
//     URL: https://github.com/RobTillaart/NeumannCorrector


#include "NeumannCorrector.h"

NeumannCorrector NC;
uint32_t last = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("NEUMANNCORRECTOR_LIB_VERSION: ");
  Serial.println(NEUMANNCORRECTOR_LIB_VERSION);
}

void loop()
{
  NC.add(randomizer());  //  constantly add entropy
  delay(1000);
  if (NC.available() >= 8)
  {
    Serial.println(NC.get());
  }
}


//  timing of analogWrite (on AVR) seems not fully deterministic.
//  so use it to harvest some pseudo random bits.
uint8_t randomizer()
{
  uint8_t value = 0;
  for (int i = 0; i < 8; i++)
  {
    uint32_t start = micros();
    analogWrite(9, micros());
    uint32_t stop = micros();
    Serial.println(stop - start);
    value <<= 1;
    value |= (((stop - start) >> 2) & 1);
  }
  return value;
}


//  -- END OF FILE --
