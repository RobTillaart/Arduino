//
//    FILE: asdx_performance.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
// PURPOSE: demo
//    DATE: 2020-06-18
//     URL: https://github.com/RobTillaart/I2C_ASDX

#include "I2C_ASDX.h"

// adjust to type of sensor  (address, psi)
I2C_ASDX sensor(0x58, 100);

uint32_t start, stop;
volatile uint32_t pressure = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  sensor.begin();

  if (!sensor.available())
  {
    Serial.println("sensor not found, check connections");
    while (1);
  }

  start = millis();
  for (int i = 0; i < 1000; i++)
  {
    sensor.read();                    // note no errorhandling
    pressure = sensor.getPressure();  // milliBar
  }
  stop = millis();
  Serial.print("1000 x read() + getPressure() :  ");
  Serial.println(stop - start);
  Serial.print("                   ErrorCount :  ");
  Serial.println(sensor.errorCount());

  Serial.println("\nDone...");
}

void loop()
{
}

// =- END OF FILE --
