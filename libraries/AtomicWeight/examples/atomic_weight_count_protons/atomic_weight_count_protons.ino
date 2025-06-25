//    FILE: atomic_weight_count_protons.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/AtomicWeight
//

#include "Arduino.h"
#include "AtomicWeight.h"


PTOE ptoe;


void setup()
{
  while (!Serial);
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("ATOMIC_WEIGHT_LIB_VERSION: ");
  Serial.println(ATOMIC_WEIGHT_LIB_VERSION);
  Serial.println();
  Serial.println("Formula\tProt\tNeut");
  Serial.println();

  count("O");
  count("O2");
  count("O3");
  count("H2O");
  count("YBa2Cu3O7");
  count("C6H6O6");
}


void loop()
{
}


void count(char * formula)
{
  Serial.print(formula);
  Serial.print("\t");
  Serial.print(protons(formula));
  Serial.print("\t");
  Serial.print(neutrons(formula));
  Serial.print("\n");
}

uint32_t protons(char * formula)
{
  uint32_t prot = 0;
  int nr = ptoe.splitElements(formula);
  for (int i = 0; i < nr; i++)
  {
    int elem = ptoe.element(i);
    float weight = ptoe.weight(formula, ptoe.name(elem));
    prot += weight / ptoe.weight(elem) * ptoe.protons(elem);
  }
  return prot;
}


uint32_t neutrons(char * formula)
{
  uint32_t neut = 0;
  int nr = ptoe.splitElements(formula);
  for (int i = 0; i < nr; i++)
  {
    int elem = ptoe.element(i);
    float weight = ptoe.weight(formula, ptoe.name(elem));
    neut += weight / ptoe.weight(elem) * ptoe.neutrons(elem);
  }
  return neut;
}

uint32_t electrons(char * formula)
{
  return protons(formula);
}



//  -- END OF FILE --
