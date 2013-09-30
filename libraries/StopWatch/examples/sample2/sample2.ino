#include <StopWatch.h>

StopWatch sw_millis;    // MILLIS (default)
StopWatch sw_micros(StopWatch::MICROS);
StopWatch sw_secs(StopWatch::SECONDS);

void setup() 
{
    Serial.begin(9600);
    sw_millis.start();
    sw_micros.start();
    sw_secs.start();
}


void loop() 
{
    Serial.print("sw_millis=");
    Serial.println(sw_millis.elapsed());
    Serial.print("sw_micros=");
    Serial.println(sw_micros.elapsed());
    Serial.print("sw_secs=");
    Serial.println(sw_secs.elapsed());
   
    delay(1000);
}