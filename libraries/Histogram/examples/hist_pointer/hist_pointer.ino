//
//    FILE: hist_pointer.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo histogram pointer
//     URL: https://github.com/RobTillaart/Histogram


#include "histogram.h"

//  boundaries does not need to be equally distributed.
float a[] = {
  0, 50, 125, 200, 250, 350, 500
};
float b[] = {
  0, 100, 200, 300, 325, 350, 375, 400
};

Histogram histA(7, a);
Histogram histB(8, b);
Histogram *phist;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("HISTOGRAM_LIB_VERSION: ");
  Serial.println(HISTOGRAM_LIB_VERSION);
  Serial.println();

  phist = &histA;

}


void loop()
{
  phist->clear();
  for (int i = 0; i < 10000; i++)
  {
    int x = random(600) - 50;
    phist->add(x);
  }

  Serial.print(phist->count());
  for (uint16_t i = 0; i < phist->size(); i++)
  {
    Serial.print("\t");
    Serial.print(phist->frequency(i), 2);
  }
  Serial.println();

  //  swap
  if (phist == &histA) phist = &histB;
  else phist = &histA;
}


//  -- END OF FILE --
