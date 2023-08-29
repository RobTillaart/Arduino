//
//    FILE: weightConverter_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2022-12-05


#include "weight.h"

const float accuracy = 0.0001;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println();

  weightConverter WC;

  WC.setKilogram(1);
  Serial.print(WC.getKilogram(), 4);
  Serial.print("\t");
  Serial.println(WC.getGram(), 4);

  WC.setGram(1);
  Serial.print(WC.getGram(), 4);
  Serial.print("\t");
  Serial.println(WC.getGram(), 4);

  WC.setLBS(1);
  Serial.print(WC.getLBS(), 4);
  Serial.print("\t");
  Serial.println(WC.getGram(), 4);

  WC.setStone(1);
  Serial.print(WC.getStone(), 4);
  Serial.print("\t");
  Serial.println(WC.getGram(), 4);

  WC.setOunce(1);
  Serial.print(WC.getOunce(), 4);
  Serial.print("\t");
  Serial.println(WC.getGram(), 4);

  WC.setLongTonUK(1);
  Serial.print(WC.getLongTonUK(), 4);
  Serial.print("\t");
  Serial.println(WC.getGram(), 4);

  WC.setShortTonUS(1);
  Serial.print(WC.getShortTonUS(), 4);
  Serial.print("\t");
  Serial.println(WC.getGram(), 4);

  WC.setQuarterUK(1);
  Serial.print(WC.getQuarterUK(), 4);
  Serial.print("\t");
  Serial.println(WC.getGram(), 4);

  WC.setQuarterUS(1);
  Serial.print(WC.getQuarterUS(), 4);
  Serial.print("\t");
  Serial.println(WC.getGram(), 4);

  WC.setSlug(1);
  Serial.print(WC.getSlug(), 4);
  Serial.print("\t");
  Serial.println(WC.getGram(), 4);

  WC.setTroyPound(1);
  Serial.print(WC.getTroyPound(), 4);
  Serial.print("\t");
  Serial.println(WC.getGram(), 4);

  WC.setTroyOunce(1);
  Serial.print(WC.getTroyOunce(), 4);
  Serial.print("\t");
  Serial.println(WC.getGram(), 4);

  WC.setRobie(1);
  Serial.print(WC.getRobie(), 4);
  Serial.print("\t");
  Serial.println(WC.getGram(), 4);

  WC.setDram(1);
  Serial.print(WC.getDram(), 4);
  Serial.print("\t");
  Serial.println(WC.getGram(), 4);

  WC.setDrachme(1);
  Serial.print(WC.getDrachme(), 4);
  Serial.print("\t");
  Serial.println(WC.getGram(), 4);

  WC.setPoint(1);
  Serial.print(WC.getPoint(), 4);
  Serial.print("\t");
  Serial.println(WC.getGram(), 4);

  WC.setGrain(1);
  Serial.print(WC.getGrain(), 4);
  Serial.print("\t");
  Serial.println(WC.getGram(), 4);

  WC.setCarat(1);
  Serial.print(WC.getCarat(), 4);
  Serial.print("\t");
  Serial.println(WC.getGram(), 4);


  Serial.print("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --

