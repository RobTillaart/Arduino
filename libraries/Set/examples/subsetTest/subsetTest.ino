//
//    FILE: subsetTest.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2014-11-09
//     URL: https://github.com/RobTillaart/SET


#include "set.h"


void setup()
{
    Serial.begin(115200);
    Serial.print("Start set_demo : ");
    Serial.println(SET_LIB_VERSION);
    Serial.println();

    Serial.println("\n\nSubSet test");
    Set setE;
    for (int i = 0; i < 5; i++) setE.add(i);

    Set setF(setE);

    Serial.println(setE.count());
    Serial.println(setF.count());

    Serial.println(setE <= setF?"subset":"no subset");
    Serial.println(setF <= setE?"subset":"no subset");

    setF.add(6);
    Serial.println(setE <= setF?"subset":"no subset");
    Serial.println(setF <= setE?"subset":"no subset");

    setF.sub(3);
    Serial.println(setE <= setF?"subset":"no subset");
    Serial.println(setF <= setE?"subset":"no subset");

    Serial.println();

    Serial.println("\ndone...");
    Serial.println();
}


void loop()
{
}


// -- END OF FILE --

