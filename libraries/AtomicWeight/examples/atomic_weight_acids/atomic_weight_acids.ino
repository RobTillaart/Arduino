//    FILE: atomic_weight_acids.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/AtomicWeight
//
//  Note this sketch uses a lot of RAM for the char arrays used.
//  Arduino UNO warns
//  Could be solved by implementing "PROGMEM" formulas


#include "AtomicWeight.h"
#include "acids.h"


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

  Serial.println("ACIDS");
  Serial.println("NAME\tWEIGHT\tFORMULA\n");

  printWeight("CHLORIC_ACID", CHLORIC_ACID);
  printWeight("CHLOROUS_ACID", CHLOROUS_ACID);
  printWeight("FORMIC_ACID", FORMIC_ACID);
  printWeight("HYDROBROMIC_ACID", HYDROBROMIC_ACID);
  printWeight("HYDROCHLORIC_ACID", HYDROCHLORIC_ACID);
  printWeight("HYDROFLUORIC_ACID", HYDROFLUORIC_ACID);
  printWeight("HYDROIODIC_ACID", HYDROIODIC_ACID);
  printWeight("NITRIC_ACID", NITRIC_ACID);
  printWeight("NITROUS_ACID", NITROUS_ACID);
  printWeight("PERCHLORIC_ACID", PERCHLORIC_ACID);
  printWeight("PHOSPHORIC_ACID", PHOSPHORIC_ACID);
  printWeight("PHOSPHOROUS_ACID", PHOSPHOROUS_ACID);
  printWeight("SULFERIC_ACID", SULFERIC_ACID);
  printWeight("SULFEROUS_ACID", SULFEROUS_ACID);

  Serial.println();
  Serial.println("\ndone...");
}


void loop()
{
}


void printWeight(const char * name, const char * formula)
{
  Serial.print(name);
  Serial.print("\t");
  Serial.print(ptoe.weight(formula));
  Serial.print("\t");
  Serial.println(formula);
}


//  -- END OF FILE --
