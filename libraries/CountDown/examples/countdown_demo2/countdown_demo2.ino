//
//    FILE: countdown_demo2.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.00
// PURPOSE: demo
//    DATE: 2015-10-28
//     URL: http://forum.arduino.cc/index.php?topic=356253
//
// Released to the public domain
//

#include "CountDown.h"

CountDown CD[5];

void setup()
{
    Serial.begin(115200);
    Serial.print("Start ");
    Serial.println(__FILE__);

    for (int i = 0; i < 5; i++)
    {
        CD[i].start(10000UL * i);
    }
    delay(1234);
    CD[3].stop();
}

void loop()
{
    for (int i = 0; i < 5; i++)
    {
        Serial.print("\t");
        Serial.print(CD[i].remaining());
    }
    for (int i = 0; i < 5; i++)
    {
        Serial.print("\t");
        Serial.print(CD[i].isRunning());
    }
    Serial.println();

    if (CD[1].isRunning() == false && CD[3].isRunning() == false)
    {
        uint32_t x = CD[3].remaining();
        CD[3].start(x);
    }

    delay(250);
}
