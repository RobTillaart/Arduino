//
//    FILE: stopwatch_printable.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: sample demo stopwatch class
//    DATE: 2021-01-08
//     URL: https://github.com/RobTillaart/StopWatch_RT


#include <StopWatch.h>


StopWatch stopwatch;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println(STOPWATCH_LIB_VERSION);

  stopwatch.setResolution(StopWatch::MICROS);
  test_printTo();
  stopwatch.setResolution(StopWatch::MILLIS);
  test_printTo();
  stopwatch.setResolution(StopWatch::SECONDS);
  test_printTo();
  stopwatch.setResolution(StopWatch::MINUTES);
  test_printTo();
}


void loop()
{
}


void test_printTo()
{
  stopwatch.start();
  delay(2000);
  Serial.print("TIME: ");
  Serial.println(stopwatch);  // printable interface
  Serial.print("TIME: ");
  Serial.println(stopwatch.elapsed());
}


// -- END OF FILE --

