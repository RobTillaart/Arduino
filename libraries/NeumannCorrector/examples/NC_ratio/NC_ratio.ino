//    FILE: NC_ratio.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: determine in-out ratio for random() function.
//     URL: https://github.com/RobTillaart/NeumannCorrector


#include "NeumannCorrector.h"

NeumannCorrector NC;
uint32_t count = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("NEUMANNCORRECTOR_LIB_VERSION: ");
  Serial.println(NEUMANNCORRECTOR_LIB_VERSION);

  for (uint32_t n = 0; n < 1000000; n++)
  {
    NC.add(random(256));
    if (NC.available() >= 8)
    {
      count++;
      NC.get();
    }
    if ((n % 1000) == 0)
    {
      Serial.print(n);
      Serial.print("\t");
      Serial.println((1.0 * count) / n, 5);
    }
  }
  Serial.println(count * 1e-6, 4);
  Serial.println(millis());
  Serial.println("\ndone");
}

void loop()
{
}


//  -- END OF FILE --
