//    FILE: atomic_weight_bases.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/AtomicWeight
//
//  Note this sketch uses a lot of RAM for the char arrays used.
//  Arduino UNO warns
//  Could be solved by implementing"PROGMEM" formulas


#include"AtomicWeight.h"
#include"acids.h"


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

  Serial.println("BASES");
  Serial.println("NAME\tWEIGHT\tFORMULA\n");

  printWeight("ALUMININUM_HYDROXIDE", ALUMININUM_HYDROXIDE);
  printWeight("AMMONIA", AMMONIA);
  printWeight("AMMONIUM_HYDROXIDE", AMMONIUM_HYDROXIDE);
  printWeight("ANILINE", ANILINE);
  printWeight("BARIUM_HYDROXIDE", BARIUM_HYDROXIDE);
  printWeight("CALCIUM_HYDROXIDE", CALCIUM_HYDROXIDE);
  printWeight("CESIUM_HYDROXIDE", CESIUM_HYDROXIDE);
  printWeight("FERRIC_HYDROXIDE", FERRIC_HYDROXIDE);
  printWeight("LEAD_HYDROXIDE", LEAD_HYDROXIDE);
  printWeight("LITHIUM_HYDROXIDE", LITHIUM_HYDROXIDE);
  printWeight("MAGNESIUM_HYDROXIDE", MAGNESIUM_HYDROXIDE);
  printWeight("METHYLAMINE", METHYLAMINE);
  printWeight("POTASSIUM_HYDROXIDE", POTASSIUM_HYDROXIDE);
  printWeight("PYRIDINE", PYRIDINE);
  printWeight("RUBIDIUM_HYDROXIDE", RUBIDIUM_HYDROXIDE);
  printWeight("SODIUM_HYDROXIDE", SODIUM_HYDROXIDE);
  printWeight("STRONTIUM_HYDROXIDE", STRONTIUM_HYDROXIDE);
  printWeight("ZINC_HYDROXIDE", ZINC_HYDROXIDE);
  printWeight("BETA_MERCAPTO_ETHANOL", BETA_MERCAPTO_ETHANOL);
  printWeight("SODIUM_BICARBONATE", SODIUM_BICARBONATE);
  printWeight("SODIUM_CARBONATE", SODIUM_CARBONATE);
  printWeight("CALCIUM_CARBONATE", CALCIUM_CARBONATE);

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
