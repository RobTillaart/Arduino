//
//    FILE: HeartBeat_SRF05_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo distance sensor
//     URL: https://github.com/RobTillaart/HeartBeat
//          https://github.com/RobTillaart/SRF05


//  HEARTBEAT
#include "HeartBeat.h"
const int buzzer  = 13;  //  also build in LED UNO
HeartBeat HB;


//  DISTANCE SENSOR
#include "SRF05.h"
const int trigger = 7;
const int echo    = 6;
SRF05 SRF(trigger, echo);


uint32_t lastTime = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("HEARTBEAT_LIB_VERSION: ");
  Serial.println(HEARTBEAT_LIB_VERSION);
  Serial.print("    SRF05_LIB_VERSION: ");
  Serial.println(SRF05_LIB_VERSION);

  HB.begin(buzzer, 0.1);  // very low frequency
  HB.setDutyCycle(10);    // short pulses

  SRF.setCorrectionFactor(1.035);
}


void loop()
{
  HB.beat();

  if (millis() - lastTime > 250)      // 4 times per second
  {
    lastTime = millis();
    //  map 0..5 meter ==> 10..0 Hz
    float freq = 10 - SRF.getMeter() * 2;
    HB.setFrequency(freq);
    Serial.println(freq);
  }
}


// -- END OF FILE --
