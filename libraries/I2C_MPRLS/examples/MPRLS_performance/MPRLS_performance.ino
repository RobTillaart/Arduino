//
//    FILE: MPRLS_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/I2C_MPRLS


#include "I2C_MPRLS.h"


//  adjust address of sensor if needed
I2C_MPRLS sensor(0x58);

uint32_t start, stop;
volatile float pressure = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("I2C_MPRLS_LIB_VERSION: ");
  Serial.println(I2C_MPRLS_LIB_VERSION);
  Serial.println();

  Wire.begin();
  if (sensor.begin(25) == false)  //  implicit minPressure of 0
  {
    Serial.print("Cannot find sensor:\t");
    Serial.print(sensor.getAddress());
    Serial.print(" - state: ");
    Serial.println(sensor.getState());
    Serial.println("Check wires or try another address.");
    while(1);
  }

  //  flush all Serial.
  delay(100);

  start = millis();
  for (int i = 0; i < 1000; i++)
  {
    sensor.read();                    //  note no error handling
    pressure = sensor.getPressure();
  }
  stop = millis();
  Serial.print("1000 x read() + getPressure() :  ");
  Serial.println(stop - start);
  Serial.print("                   ErrorCount :  ");
  Serial.println(sensor.errorCount());
  Serial.print("                     Pressure :  ");
  Serial.println(pressure);


  for (uint32_t speed = 100000; speed < 500000; speed += 100000)
  {
    test(speed);
  }

  Serial.println("\nDone...");
}


void loop()
{
}


void test(uint32_t speed)
{
  delay(100);
  Wire.setClock(speed);
  start = millis();
  for (int i = 0; i < 1000; i++)
  {
    sensor.read();                    //  note no error handling
    pressure = sensor.getPressure();
  }
  stop = millis();
  Serial.print("I2C speed : ");
  Serial.println(speed);
  Serial.print("1000 x    : ");
  Serial.println(stop - start);
  Serial.print("E-Count   : ");
  Serial.println(sensor.errorCount());
  Serial.print(" Pressure : ");
  Serial.println(pressure);
}

//  -- END OF FILE --
