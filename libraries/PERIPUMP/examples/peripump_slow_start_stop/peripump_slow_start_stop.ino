//
//    FILE: peripump_slow_start_stop.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/PERIPUMP.git
//


#include "PERIPUMP.h"

PERIPUMP pump(5);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PERIPUMP_LIB_VERSION: ");
  Serial.println(PERIPUMP_LIB_VERSION);

  pump.begin();
  pump.stop();

  pump.setPercentage(100);
  delay(2000);
  pump.stop();
  delay(1000);
  pump.setPercentage(-100);
  delay(2000);
  pump.stop();
  delay(1000);

  pump.setPercentage(10);
  Serial.println(pump.getPercentage());
  delay(2000);
  pump.setPercentage(20);
  Serial.println(pump.getPercentage());
  delay(2000);
  pump.setPercentage(30);
  Serial.println(pump.getPercentage());
  delay(2000);
  pump.setPercentage(40);
  Serial.println(pump.getPercentage());
  delay(2000);
  pump.setPercentage(50);
  Serial.println(pump.getPercentage());
  delay(2000);
  pump.setPercentage(60);
  Serial.println(pump.getPercentage());
  delay(2000);
  pump.setPercentage(70);
  Serial.println(pump.getPercentage());
  delay(2000);
  pump.setPercentage(80);
  Serial.println(pump.getPercentage());
  delay(2000);
  pump.setPercentage(90);
  Serial.println(pump.getPercentage());
  delay(2000);
  pump.setPercentage(100);
  Serial.println(pump.getPercentage());
  delay(2000);




  //  pump.setPercentage(0);
  //  Serial.print(millis());
  //  Serial.print('\t');
  //  Serial.print(pump.getPercentage());
  //  Serial.println();
  //
  //  //  take 0.5 seconds to go to 100%
  //  slowStart(100.0, 5000);
  //  Serial.print(millis());
  //  Serial.print('\t');
  //  Serial.print(pump.getPercentage());
  //  Serial.println();
  //  delay(1000);
  //
  //  slowStop(2000);
  //  Serial.print(millis());
  //  Serial.print('\t');
  //  Serial.print(pump.getPercentage());
  //  Serial.println();
  //  delay(1000);
  //
  //  slow(0, 100, 5000);
  //  Serial.print(millis());
  //  Serial.print('\t');
  //  Serial.print(pump.getPercentage());
  //  Serial.println();
  //  delay(1000);
  //
  //  slowStop(10000);
  //  Serial.print(millis());
  //  Serial.print('\t');
  //  Serial.print(pump.getPercentage());
  //  Serial.println();
  //  delay(1000);

  pump.stop();
  delay(1000);
}

void loop()
{
}

void slowStart(float perc, uint32_t mils)
{
  slow(0, perc, mils);
}


void slowStop(uint32_t mils)
{
  slow(pump.getPercentage(), 0, mils);
}


//  blocking slow speed adjustment
uint32_t slow(float percStart, float percStop, uint32_t mils)
{
  uint32_t count = 0;
  uint32_t start = micros();
  float step = (percStop - percStart) / (mils * 1000.0);
  while (micros() - start < (mils * 1000))
  {
    float speed = percStart + step * (micros() - start);
    pump.setPercentage(speed);
    //  Serial.println(speed);
    count++;
  }
  pump.setPercentage(percStop);
  //  Serial.println(count);
  return count;
}


//  -- END OF FILE --
