//     FILE: atomic_weight_minerals_3.ino
//   AUTHOR: Rob Tillaart
//  PURPOSE: demo
//      URL: https://github.com/RobTillaart/AtomicWeight
//
//  Note this sketch uses a lot of RAM for the char arrays used.
//  Arduino UNO warns
//  Could be solved by implementing "PROGMEM" formulas

#include "Arduino.h"
#include "AtomicWeight.h"
#include "minerals.h"


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


  Serial.println("METAMORPHISM (15)");
  Serial.println("NAME\tWEIGHT\tFORMULA\n");

  printWeight("PERICLASE", PERICLASE);
  printWeight("MONTICELLITE", MONTICELLITE);
  printWeight("MERWINITE", MERWINITE);
  printWeight("LARNITE", LARNITE);
  printWeight("SPURRITE", SPURRITE);
  printWeight("TILLEYITE", TILLEYITE);
  printWeight("RANKINITE", RANKINITE);
  printWeight("PHLOGOPITE", PHLOGOPITE);
  printWeight("ANNIITE", ANNIITE);
  Serial.println();


  Serial.println("ECONOMIC MINERALS (16)");
  Serial.println("NAME\tWEIGHT\tFORMULA\n");

  printWeight("ACANTHITE", ACANTHITE);
  printWeight("PROUSTITE", PROUSTITE);
  printWeight("PYRARGTRITE", PYRARGTRITE);
  printWeight("GALENA", GALENA);
  printWeight("SPHALERITE", SPHALERITE);
  printWeight("BORNITE", BORNITE);
  printWeight("CHALCOCITE", CHALCOCITE);
  printWeight("MARCASITE", MARCASITE);
  printWeight("MOLYBDENITE", MOLYBDENITE);
  printWeight("BROCHANTHITE", BROCHANTHITE);
  printWeight("ARSENOPYRITE", ARSENOPYRITE);
  printWeight("BAUXITE", BAUXITE);
  printWeight("DIASPORE", DIASPORE);
  printWeight("GIBBSITE", GIBBSITE);
  printWeight("BOEHMITE", BOEHMITE);
  printWeight("FLUORITE", FLUORITE);
  printWeight("BARITE", BARITE);
  printWeight("CELESTITE", CELESTITE);
  printWeight("SPODUMENE", SPODUMENE);
  printWeight("KUNZITE", KUNZITE);
  Serial.println();


  Serial.println("SOME GEMS (16)");
  Serial.println("NAME\tWEIGHT\tFORMULA\n");
  printWeight("RUBY", RUBY);
  printWeight("SAPPHIRE", SAPPHIRE);
  printWeight("BERYL", BERYL);
  printWeight("EMERALD", EMERALD);
  printWeight("HELIODOR", HELIODOR);
  printWeight("AQUAMARINE", AQUAMARINE);
  printWeight("JADE", JADE);
  printWeight("TURQOISE", TURQOISE);
  printWeight("CALAVERITE", CALAVERITE);
  Serial.println();

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
