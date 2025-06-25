//     FILE: atomic_weight_minerals_2.ino
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


  Serial.println("METAMORPHIC ROCK (14)");
  Serial.println("NAME\tWEIGHT\tFORMULA\n");

  printMineral("PYROPE", PYROPE);
  printMineral("ALMANDINE", ALMANDINE);
  printMineral("SPESSARTINE", SPESSARTINE);
  printMineral("GROSSULAR", GROSSULAR);
  printMineral("ANDRADITE", ANDRADITE);
  printMineral("UVAROVITE", UVAROVITE);
  printMineral("ANDALUSITE", ANDALUSITE);
  printMineral("MULLITE", MULLITE);
  printMineral("SILLIMANITE", SILLIMANITE);
  printMineral("KYANITE", KYANITE);
  printMineral("STAUROLITE", STAUROLITE);
  printMineral("ANTHOPHYLLITE", ANTHOPHYLLITE);
  printMineral("CUMMINGTONITE", CUMMINGTONITE);
  printMineral("GRUNERITE", GRUNERITE);
  printMineral("TREMOLITE", TREMOLITE);
  printMineral("FERROACTINOLITE", FERROACTINOLITE);
  printMineral("GLAUCAPHANE", GLAUCAPHANE);
  printMineral("RHODONITE", RHODONITE);
  printMineral("TALC", TALC);
  printMineral("CHLORITE", CHLORITE);
  printMineral("ANTIGORITE", ANTIGORITE);
  printMineral("CHRYSOLITE", CHRYSOLITE);
  printMineral("GRAPHITE", GRAPHITE);
  printMineral("EPIDOTE", EPIDOTE);
  printMineral("CLINOZOISITE", CLINOZOISITE);
  printMineral("CORDEIRITE", CORDEIRITE);
  printMineral("VESUVIANITE", VESUVIANITE);
  printMineral("TITANITE", TITANITE);
  printMineral("SCAPOLITE", SCAPOLITE);
  printMineral("LAWSONITE", LAWSONITE);
  printMineral("PUMPELLYITE", PUMPELLYITE);
  printMineral("TOPAZ", TOPAZ);
  printMineral("CHABAZITE", CHABAZITE);

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
