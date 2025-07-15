//    FILE: atomic_weight_minerals_0.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/AtomicWeight
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

  Serial.println("IGNEOUS ROCK (7)");
  Serial.println("NAME\tWEIGHT\tFORMULA\n");

  printWeight("ALBITE", ALBITE);
  printWeight("ANORTHITE", ANORTHITE);
  printWeight("MICROLINE", MICROLINE);
  printWeight("QUARTZ", QUARTZ);
  printWeight("NEPHELINE", NEPHELINE);
  printWeight("KALSILITE", KALSILITE);
  printWeight("LEUCITE", LEUCITE);
  printWeight("AEGIRINE", AEGIRINE);
  printWeight("SODALITE", SODALITE);
  printWeight("ENSTATITE", ENSTATITE);
  printWeight("FERROSILITE", FERROSILITE);
  printWeight("PIGEONITE", PIGEONITE);
  printWeight("DIOPSIDE", DIOPSIDE);
  printWeight("WOLLASTONITE", WOLLASTONITE);
  printWeight("TREMOLITE", TREMOLITE);
  printWeight("MUSCOVITE", MUSCOVITE);
  printWeight("PHOLOGOPITE", PHOLOGOPITE);
  printWeight("FORSTERITE", FORSTERITE);
  printWeight("FAYALITE", FAYALITE);
  printWeight("ZIRCON", ZIRCON);
  printWeight("AKERMANITE", AKERMANITE);
  printWeight("MAGNETITE", MAGNETITE);
  printWeight("ULVOSPINEL", ULVOSPINEL);
  printWeight("ILMENITE", ILMENITE);
  printWeight("SPINEL", SPINEL);
  printWeight("CHROMITE", CHROMITE);
  printWeight("HEMATITE", HEMATITE);
  printWeight("CORUNDUM", CORUNDUM);
  printWeight("RUTILE", RUTILE);
  printWeight("URANINITE", URANINITE);
  printWeight("PYRITE", PYRITE);
  printWeight("CHALCOPYRITE", CHALCOPYRITE);
  printWeight("HYDROXYAPATITE", HYDROXYAPATITE);

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
