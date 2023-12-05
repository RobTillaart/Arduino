//
//    FILE: asdx_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/I2C_ASDX


#include "I2C_ASDX.h"


//  adjust to type of sensor  (address, psi)
I2C_ASDX sensor(0x58, 100);

uint32_t start, stop;
volatile uint32_t pressure = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("I2C_ASDX_VERSION: ");
  Serial.println(I2C_ASDX_VERSION);

  Wire.begin();
  if (sensor.begin() == false)
  {
    Serial.print("Cannot find sensor:\t");
    Serial.print(sensor.getAddress());
    Serial.println("Check wires or try another address.");
    while(1);
  }

  //  flush all Serial.
  delay(100);

  start = millis();
  for (int i = 0; i < 1000; i++)
  {
    sensor.read();                    //  note no error handling
    pressure = sensor.getPressure();  //  milliBar
  }
  stop = millis();
  Serial.print("1000 x read() + getPressure() :  ");
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

