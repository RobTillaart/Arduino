//
//    FILE: sample2.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: sample demo stopwatch class
//    DATE: 2011-01-04
//     URL: https://github.com/RobTillaart/StopWatch_RT


#include <StopWatch.h>


StopWatch sw_millis;    // MILLIS (default)
StopWatch sw_micros(StopWatch::MICROS);
StopWatch sw_secs(StopWatch::SECONDS);


void setup()
{
    Serial.begin(115200);
    sw_millis.start();
    sw_micros.start();
    sw_secs.start();
}


void loop()
{
    Serial.print("sw_millis=");
    Serial.print(sw_millis.elapsed());
    Serial.print("\tsw_micros=");
    Serial.print(sw_micros.elapsed());
    Serial.print("\tsw_secs=");
    Serial.print(sw_secs.elapsed());
    Serial.println();

    delay(1000);
}


// -- END OF FILE --

