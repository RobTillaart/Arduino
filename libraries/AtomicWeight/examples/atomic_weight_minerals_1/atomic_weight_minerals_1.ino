//    FILE: atomic_weight_minerals_1.ino
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

  Serial.println("SEDIMENTARY ROCK (11)");
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
