//
//    FILE: equalTest.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo equality operators
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

    Serial.println("\n\nequal test");
    randomSeed(1);
    setA.clear();
    setB.clear();
    Serial.println(setA == setB?"true":"false");
    setB.add(0);
    Serial.println(setA == setB?"true":"false");
    Serial.println(setA == setA?"true":"false");

    Set setC(setB);
    Serial.println(setC == setB?"true":"false");
    Serial.println(setC.count());

    Set setD = setB;
    Serial.println(setD != setB?"unequal":"equal");
    Serial.println(setD == setB?"true":"false");
    Serial.println(setD.count());

    setD = setA;
    Serial.println(setD == setB?"true":"false");
    Serial.println(setD.count());

    Serial.println("done...");
    Serial.println();
}


void loop()
{
}


// -- END OF FILE --

