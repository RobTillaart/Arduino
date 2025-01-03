//    FILE: atomic_weight_minerals.ino
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
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);
  Serial.println();

  Serial.println();
  Serial.println("IGNEOUS ROCK");
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
  Serial.println("SEDIMENTARY ROCK");
  Serial.println("NAME\tWEIGHT\tFORMULA\n");
  printMineral("JADEITE", JADEITE);
  printMineral("GOETHITE", GOETHITE);
  printMineral("KAOLINITE", KAOLINITE);
  printMineral("CALCITE", CALCITE);
  printMineral("ARAGONITE", ARAGONITE);
  printMineral("DOLOMITE", DOLOMITE);
  printMineral("MAGNESITE", MAGNESITE);  
  printMineral("SIDERITE", SIDERITE);
  printMineral("RHODOCHROSITE", RHODOCHROSITE);
  printMineral("HALITE", HALITE);
  printMineral("SYLVITE", SYLVITE);
  printMineral("GYPSUM", GYPSUM);
  printMineral("ANHYDRITE", ANHYDRITE);
  printMineral("FLUORAPATITE", FLUORAPATITE);
  Serial.println();
  Serial.println();
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
