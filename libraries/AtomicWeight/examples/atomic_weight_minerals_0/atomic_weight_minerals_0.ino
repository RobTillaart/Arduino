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

  printMineral("ALBITE", ALBITE);
  printMineral("ANORTHITE", ANORTHITE);
  printMineral("MICROLINE", MICROLINE);
  printMineral("QUARTZ", QUARTZ);
  printMineral("NEPHELINE", NEPHELINE);
  printMineral("KALSILITE", KALSILITE);
  printMineral("LEUCITE", LEUCITE);
  printMineral("AEGIRINE", AEGIRINE);
  printMineral("SODALITE", SODALITE);
  printMineral("ENSTATITE", ENSTATITE);
  printMineral("FERROSILITE", FERROSILITE);
  printMineral("PIGEONITE", PIGEONITE);
  printMineral("DIOPSIDE", DIOPSIDE);
  printMineral("WOLLASTONITE", WOLLASTONITE);
  printMineral("TREMOLITE", TREMOLITE);
  printMineral("MUSCOVITE", MUSCOVITE);
  printMineral("PHOLOGOPITE", PHOLOGOPITE);
  printMineral("FORSTERITE", FORSTERITE);
  printMineral("FAYALITE", FAYALITE);
  printMineral("ZIRCON", ZIRCON);
  printMineral("AKERMANITE", AKERMANITE);
  printMineral("MAGNETITE", MAGNETITE);
  printMineral("ULVOSPINEL", ULVOSPINEL);
  printMineral("ILMENITE", ILMENITE);
  printMineral("SPINEL", SPINEL);
  printMineral("CHROMITE", CHROMITE);
  printMineral("HEMATITE", HEMATITE);
  printMineral("CORUNDUM", CORUNDUM);
  printMineral("RUTILE", RUTILE);
  printMineral("URANINITE", URANINITE);
  printMineral("PYRITE", PYRITE);
  printMineral("CHALCOPYRITE", CHALCOPYRITE);
  printMineral("HYDROXYAPATITE", HYDROXYAPATITE);

  Serial.println();
  Serial.println("\ndone...");
}


void loop()
{
}


void printMineral(const char * name, const char * formula)
{
  Serial.print(name);
  Serial.print("\t");
  Serial.print(ptoe.weight(formula));
  Serial.print("\t");
  Serial.println(formula);
}

//  -- END OF FILE --
