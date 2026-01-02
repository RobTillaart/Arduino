//
//    FILE: HeartBeat_DHT22_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo temperature sensor
//     URL: https://github.com/RobTillaart/HeartBeat
//          https://github.com/RobTillaart/DHTNEW


//  HEARTBEAT
#include "HeartBeat.h"
const int buzzer = 13;  //  also build in LED UNO
HeartBeat HB;


//  DHT22 temperature and humidity sensor
#include "dhtnew.h"
DHTNEW mySensor(5);


uint32_t lastTime = 0;


void setup()
{
  while (!Serial);
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("HEARTBEAT_LIB_VERSION: ");
  Serial.println(HEARTBEAT_LIB_VERSION);
  Serial.print("   DHTNEW_LIB_VERSION: ");
  Serial.println(DHTNEW_LIB_VERSION);
  Serial.println();

  HB.begin(buzzer, 0.1);  //  very low frequency
  HB.setDutyCycle(10);    //  short pulses
}


void loop()
{
  HB.beat();

  if (millis() - lastTime >= 2000)
  {
    lastTime = millis();

    int chk = mySensor.read();
    //  optional error handling based on chk

    //  DISPLAY DATA
    Serial.print(mySensor.getHumidity(), 1);
    Serial.print(",\t");
    Serial.println(mySensor.getTemperature(), 1);

    float tmp = mySensor.getTemperature();
    //  frequency depends on temperature
    if (tmp <= 1) HB.setFrequency(20);
    else HB.setFrequency(tmp / 3);
  }
}


//  -- END OF FILE --
