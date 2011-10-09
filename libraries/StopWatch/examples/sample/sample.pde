#include <StopWatch.h>

StopWatch MySW;
StopWatch SWarray[5];

void setup()
{
  Serial.begin(115200);
  Serial.println("Stopwatch demo");
  Serial.print("Version: ");
  Serial.println(STOPWATCH_LIB_VERSION);

  SWarray[0].start();
}

void loop()
{
  Serial.println(MySW.isRunning());
  delay(100);

  MySW.start();
  Serial.println(MySW.isRunning());  
  Serial.println("START 1");
  for(int i=0; i<5; i++)
  {
    delay(10);
    Serial.println(MySW.value());
  }

  MySW.stop();
  Serial.println(MySW.isRunning());
  Serial.println("STOP");
  for(int i=0; i<5; i++)
  {
    delay(10);
    Serial.println(MySW.value());
  }

  MySW.start();
  Serial.println(MySW.isRunning());    
  Serial.println("START 2");
  for(int i=0; i<5; i++)
  {
    delay(10);
    Serial.println(MySW.value());
  }  
  MySW.reset();
  Serial.println(MySW.isRunning());
  Serial.println("RESET");

  MySW.start();
  Serial.println(MySW.isRunning());
  Serial.println("START 3");
  for(int i=0; i<5; i++)
  {
    delay(10);
    Serial.println(MySW.value());
  }

  switch(MySW.state())
  {
    case STOPWATCH_RESET: 
      Serial.println("reset");  // e.g. disable stop/reset
      break;
    case STOPWATCH_RUNNING: 
      Serial.println("running"); // display laptime
      break;
    case STOPWATCH_STOPPED: 
      Serial.println("stopped"); // display finaltime
      break;
    default: 
      Serial.println("unknown");
      break;
  }

  delay(3000);
  Serial.print(" >>>  laptime loop() : ");
  Serial.println(SWarray[0].value());  
}
