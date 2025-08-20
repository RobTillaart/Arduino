//
//    FILE: HeartBeat_ACS712_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo distance sensor
//
//     URL: https://github.com/RobTillaart/HeartBeat
//          https://github.com/RobTillaart/ACS712


//  HEARTBEAT
#include "HeartBeat.h"
const int buzzer = 13;  //  also build in LED UNO
HeartBeat HB;


//  CURRENT SENSOR
//  Arduino UNO has 5.0 volt with a max ADC value of 1023 steps
//  ACS712 5A  uses 185 mV per A
//  ACS712 20A uses 100 mV per A
//  ACS712 30A uses  66 mV per A
#include "ACS712.h"
ACS712  ACS(A0, 5.0, 1023, 100);  //  analog pin, maxV, maxADC, mV/A


uint32_t lastTime = 0;


void setup()
{
  while (!Serial);
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("HEARTBEAT_LIB_VERSION: ");
  Serial.println(HEARTBEAT_LIB_VERSION);
  Serial.print("   ACS712_LIB_VERSION: ");
  Serial.println(ACS712_LIB_VERSION);
  Serial.println();

  HB.begin(buzzer, 0.1);  //  very low frequency
  HB.setDutyCycle(10);    //  short pulses

  ACS.autoMidPoint();
}


void loop()
{
  HB.beat();

  int mA = ACS.mA_DC();  //  Direct Current
  //  int mA = ACS.mA_AC();  //  Alternating Current
  Serial.println(mA);    //  print e.g. for plotter.

  if (millis() - lastTime > 250)      //  update 4 times per second
  {
    lastTime = millis();
    //  map 0..20000 mA ==> 0..20 Hz
    float freq = mA * 0.001;
    HB.setFrequency(freq);
  }

  delay(10);
}


//  -- END OF FILE --
