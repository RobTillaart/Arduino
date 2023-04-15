//    FILE: atomic_grams_moles.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo conversion grams <> moles. Creates a lookup table.
//     URL: https://github.com/RobTillaart/AtomicWeight


#include "Arduino.h"
#include "AtomicWeight.h"


PTOE ptoe;

char formula[24] = "KOH";
//  char formula[24] = "NaCl";


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println();
  Serial.println(__FILE__);

  Serial.print("\n\t");
  Serial.print(formula);
  Serial.println(" moles to grams");
  float moles2grams = ptoe.moles2grams(formula);  //  default 1 mole.
  for (int i = 1; i <= 40; i++)
  {
    if (i % 20 == 1) Serial.println("\n\tMOLES\t\tGRAMS");
    float moles = i * 0.100;
    float grams = moles * moles2grams;
    Serial.print("\t");
    Serial.print(moles, 2);
    Serial.print("\t\t");
    Serial.println(grams, 2);
  }

  Serial.println("\n==========================================================\n");
  Serial.print("\n\t");
  Serial.print(formula);
  Serial.println(" grams to moles");
  float grams2moles = ptoe.grams2moles(formula);  //  default 1 gram.
  for (int i = 1; i <= 40; i++)
  {
    if (i % 20 == 1) Serial.println("\n\tGRAMS\t\tMOLES");
    float grams = i * 5;
    float moles = grams * grams2moles;
    Serial.print("\t");
    Serial.print(grams, 2);
    Serial.print("\t\t");
    Serial.println(moles, 4);
  }

  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --
