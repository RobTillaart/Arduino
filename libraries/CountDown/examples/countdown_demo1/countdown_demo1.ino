//
//    FILE: countdown_demo.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.00
// PURPOSE: demo
//    DATE: 2015-10-28
//     URL: http://forum.arduino.cc/index.php?topic=356253
//
// Released to the public domain
//

#include "CountDown.h"

CountDown CD(CountDown::SECONDS);

void setup()
{
    Serial.begin(115200);
    Serial.print("Start ");
    Serial.println(__FILE__);

    CD.start(5);

    while (CD.remaining() > 0 && CD.isRunning() )
    {
        Serial.println(CD.remaining() );
        if (CD.remaining() < 2) CD.stop();
    }
    Serial.println(CD.remaining());
    Serial.println("done...");
}

void loop()
{
}
