//
//    FILE: stopwatch_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: sample demo stopwatch class
//    DATE: 2022-09-08
//     URL: https://github.com/RobTillaart/StopWatch_RT


#include <StopWatch.h>

StopWatch myStopwatch;

//  configure to your needs
#define RUNPIN      13
#define STARTPIN    7
#define STOPPIN     6
#define RESETPIN    5

uint32_t lastDisplay = 0;
uint32_t lastTimeDisplayed = -1;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("STOPWATCH_LIB_VERSION: ");
  Serial.println(STOPWATCH_LIB_VERSION);

  pinMode(RUNPIN, OUTPUT);          // indicator stopwatch is running
  digitalWrite(RUNPIN, LOW);
  pinMode(STARTPIN, INPUT_PULLUP);
  pinMode(STOPPIN, INPUT_PULLUP);
  pinMode(RESETPIN, INPUT_PULLUP);
}


void loop()
{
  //  HANDLE IO PINS
  if (digitalRead(STARTPIN) == LOW) myStopwatch.start();
  if (digitalRead(STOPPIN) == LOW) myStopwatch.stop();
  if (digitalRead(RESETPIN) == LOW) myStopwatch.reset();

  //  HANDLE RUNNINGLED
  digitalWrite(RUNPIN, myStopwatch.isRunning());

  //  HANDLE DISPLAY
  if (millis() - lastDisplay > 100)
  {
    lastDisplay = millis();
    uint32_t ti = myStopwatch.elapsed();
    if (ti != lastTimeDisplayed)
    {
      lastTimeDisplayed = ti;
      Serial.print("TIME: ");
      Serial.println(ti);
    }
  }

  //  do other stuff here
}


// -- END OF FILE --
