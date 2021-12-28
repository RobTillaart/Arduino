//
//    FILE: stopwatch_resolution.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: sample demo stopwatch class
//    DATE: 2020-05-08
//     URL: https://github.com/RobTillaart/StopWatch_RT


#include <StopWatch.h>

StopWatch MySW;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println(STOPWATCH_LIB_VERSION);

  MySW.start();
  delay(5000);
  Serial.print("TIME: ");
  Serial.println(MySW.elapsed());
  Serial.print(" RES: ");
  Serial.println(MySW.resolution());
  Serial.println();
}


void loop()
{
  simple_test(StopWatch::MICROS);
  simple_test(StopWatch::MILLIS);
  simple_test(StopWatch::SECONDS);
  simple_test(StopWatch::MINUTES);
}


void simple_test(StopWatch::Resolution res)
{
  MySW.setResolution(res);  // note: includes an automatic reset() 
  MySW.start();
  delay(2500);
  Serial.print("TIME: ");
  Serial.println(MySW.elapsed());
  Serial.print(" RES: ");
  Serial.println(MySW.resolution());
  Serial.println();
}


// -- END OF FILE --

