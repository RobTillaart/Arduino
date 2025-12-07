//
//    FILE: MS4525DO_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/MS4525DO_RT


#include "MS4525DO.h"


MS4525DO sensor(0x28);

uint32_t start, stop;
volatile float pressure = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("MS4525DO_LIB_VERSION: ");
  Serial.println(MS4525DO_LIB_VERSION);
  Serial.println();

  Wire.begin();
  if (sensor.begin(100) == false)
  {
    Serial.print("Cannot find sensor:\t");
    Serial.print(sensor.getAddress());
    Serial.print(" - state: ");
    Serial.println(sensor.state());
    Serial.println("Check wires or try another address.");
    while(1);
  }

  //  flush all Serial.
  delay(100);

  start = millis();
  for (int i = 0; i < 1000; i++)
  {
    sensor.read();                    //  note no error handling
    pressure = sensor.getMilliBar();  //  milliBar
  }
  stop = millis();
  Serial.print("1000 x read() + getMilliBar() :  ");
  Serial.println(stop - start);
  Serial.print("                   ErrorCount :  ");
  Serial.println(sensor.errorCount());
  Serial.print("                     Pressure :  ");
  Serial.println(pressure);

  Serial.println("\nDone...");
}


void loop()
{
}


//  -- END OF FILE --
