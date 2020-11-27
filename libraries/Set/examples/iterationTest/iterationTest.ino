//
//    FILE: iterationTest.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.00
// PURPOSE: demo first, next, last, prev
//    DATE: 2014-11-09
//     URL:
//
// Released to the public domain
//

#include "set.h"

Set myset;
Set setA, setB;


volatile bool b;

void setup()
{
    Serial.begin(115200);
    Serial.print("Start set_demo : ");
    Serial.println(SET_LIB_VERSION);
    Serial.println();

    Serial.println("\n\niterate over set test");
    randomSeed(1);
    setA.clr();
    for (int i=0; i<10; i++)
    {
        setA.add(random(256));
    }
    Serial.println(setA.count());
    int n = setA.first();
    while (n != -1)
    {
        Serial.print(n);
        Serial.print('\t');
        n = setA.next();
    }
    Serial.println();

    n = setA.last();
    while (n != -1)
    {
        Serial.print(n);
        Serial.print('\t');
        n = setA.prev();
    }
    Serial.println();

    Serial.println("done...");
    Serial.println();
}

void loop()
{
}

