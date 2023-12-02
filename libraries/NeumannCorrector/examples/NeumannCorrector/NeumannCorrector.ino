//
//    FILE: NeumannCorrector.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: Neumann corrector for random streams
//     URL: https://github.com/RobTillaart/NeumannCorrector
//     URL: https://github.com/RobTillaart/DEVRANDOM


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
  NC.add(random(256));  //  constantly add entropy

  if (millis() - last >= 100)
  {
    last = millis();
    if (NC.available() >= 8)
    {
      Serial.println(NC.get());
    }
  }
}


//  -- END OF FILE --
