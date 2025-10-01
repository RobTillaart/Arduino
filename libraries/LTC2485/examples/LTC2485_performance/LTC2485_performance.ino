//
//    FILE: LTC2485_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo monitoring internal temperature and VCC
//     URL: https://github.com/RobTillaart/LTC2485


#include "Wire.h"
#include "LTC2485.h"


//  adjust address if needed
//  0x14  CA1 = LOW  CA0 = HIGH
LTC2485 LTC(0x16);

float VREF = 1.8;

uint32_t start, stop;

volatile float volts;


void setup()
{
  while(!Serial);
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print(F("LTC2485_LIB_VERSION: "));
  Serial.println(LTC2485_LIB_VERSION);
  Serial.println();

  Wire.begin();
  Wire.setClock(100000);

  LTC.begin(VREF);
  delay(200);

  while (!LTC.isConnected())
  {
    Serial.println("Could not connect to device");
    delay(2000);
  }

  Serial.println();
  Serial.println("speed\tmicros");
  for (uint32_t speed = 50000; speed <= 600000; speed += 50000)
  {
    Wire.setClock(speed);
    delay(1000);  //  flush serial and wait for next conversion.
    start = micros();
    volts = LTC.getVolts();
    stop = micros();
    Serial.print(speed);
    Serial.print("\t");
    Serial.println(stop - start);
  }
  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --
