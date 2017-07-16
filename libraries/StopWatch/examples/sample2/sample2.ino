//
//    FILE: sample2.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: sample demo stopwatch class
//    DATE: 
//     URL:
//
// Released to the public domain
//

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