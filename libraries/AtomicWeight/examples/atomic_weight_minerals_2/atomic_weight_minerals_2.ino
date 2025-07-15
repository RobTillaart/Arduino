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

  printWeight("PYROPE", PYROPE);
  printWeight("ALMANDINE", ALMANDINE);
  printWeight("SPESSARTINE", SPESSARTINE);
  printWeight("GROSSULAR", GROSSULAR);
  printWeight("ANDRADITE", ANDRADITE);
  printWeight("UVAROVITE", UVAROVITE);
  printWeight("ANDALUSITE", ANDALUSITE);
  printWeight("MULLITE", MULLITE);
  printWeight("SILLIMANITE", SILLIMANITE);
  printWeight("KYANITE", KYANITE);
  printWeight("STAUROLITE", STAUROLITE);
  printWeight("ANTHOPHYLLITE", ANTHOPHYLLITE);
  printWeight("CUMMINGTONITE", CUMMINGTONITE);
  printWeight("GRUNERITE", GRUNERITE);
  printWeight("TREMOLITE", TREMOLITE);
  printWeight("FERROACTINOLITE", FERROACTINOLITE);
  printWeight("GLAUCAPHANE", GLAUCAPHANE);
  printWeight("RHODONITE", RHODONITE);
  printWeight("TALC", TALC);
  printWeight("CHLORITE", CHLORITE);
  printWeight("ANTIGORITE", ANTIGORITE);
  printWeight("CHRYSOLITE", CHRYSOLITE);
  printWeight("GRAPHITE", GRAPHITE);
  printWeight("EPIDOTE", EPIDOTE);
  printWeight("CLINOZOISITE", CLINOZOISITE);
  printWeight("CORDEIRITE", CORDEIRITE);
  printWeight("VESUVIANITE", VESUVIANITE);
  printWeight("TITANITE", TITANITE);
  printWeight("SCAPOLITE", SCAPOLITE);
  printWeight("LAWSONITE", LAWSONITE);
  printWeight("PUMPELLYITE", PUMPELLYITE);
  printWeight("TOPAZ", TOPAZ);
  printWeight("CHABAZITE", CHABAZITE);

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
