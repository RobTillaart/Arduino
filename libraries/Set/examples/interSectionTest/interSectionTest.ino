//
//    FILE: set_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo set intersection union and diff
//    DATE: 2014-11-09
//     URL: https://github.com/RobTillaart/SET


#include "set.h"


Set setA, setB;
volatile bool b;


void setup()
{
    Serial.begin(115200);
    Serial.print("Start set_demo : ");
    Serial.println(SET_LIB_VERSION);
    Serial.println();

    Serial.println("\n\nintersection test");
    randomSeed(1);
    setA.clear();
    setB.clear();
    for (int i=0; i<150; i++)
    {
      setA.add(random(256));
      setB.add(random(256));
    }
    Serial.println(setA.count());
    Serial.println(setB.count());
    setA *= setB;
    for (int i=0; i<4; i++)
    {
      for (int j=0; j<64; j++)
      {
        Serial.print(setA.has(i*64+j));
      }
      Serial.println();
    }
    Serial.println(setA.count());
    Serial.println();


    Serial.println("\n\nunion test");
    randomSeed(1);
    setA.clear();
    setB.clear();
    for (int i=0; i<150; i++)
    {
      setA.add(random(256));
      setB.add(random(256));
    }
    Serial.println(setA.count());
    Serial.println(setB.count());
    setA += setB;
    for (int i=0; i<4; i++)
    {
      for (int j=0; j<64; j++)
      {
        Serial.print(setA.has(i*64+j));
      }
      Serial.println();
    }
    Serial.println(setA.count());
    Serial.println();


    Serial.println("\n\ndiff test");
    randomSeed(1);
    setA.clear();
    setB.clear();
    for (int i=0; i<150; i++)
    {
      setA.add(random(256));
      setB.add(random(256));
    }
    Serial.println(setA.count());
    Serial.println(setB.count());
    setA -= setB;
    for (int i=0; i<4; i++)
    {
      for (int j=0; j<64; j++)
      {
        Serial.print(setA.has(i*64+j));
      }
      Serial.println();
    }
    Serial.println(setA.count());
    Serial.println();

    Serial.println("done...");
    Serial.println();
}


void loop()
{
}


// -- END OF FILE --

