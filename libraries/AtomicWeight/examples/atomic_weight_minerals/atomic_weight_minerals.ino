//    FILE: atomic_weight_minerals.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/AtomicWeight


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

  Serial.println("\ndone...");
}


void loop()
{
}


void printMineral(char * name, char * formula)
{
  Serial.print(name);
  Serial.print("\t");
  Serial.print(ptoe.weight(formula));
  Serial.print("\t");
  Serial.println(formula);
}

//  -- END OF FILE --
