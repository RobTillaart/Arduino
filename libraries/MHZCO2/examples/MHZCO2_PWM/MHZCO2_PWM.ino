//
//    FILE: MHZCO2_PWM.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo MHZ library / sensor
//    DATE: 2020-09-01


/*
   DATASHEET P.?
   Conversion between PWM output and concentration,
   use interrupt pin 3 of Arduino UNO.
*/


#include "Arduino.h"
#include "MHZCO2.h"


//  adjust to calibrate.
const float MAX_CONCENTRATION = 2000.0;

volatile uint16_t width;


void IRQ()
{
  static uint32_t start = 0;
  int v = digitalRead(3);
  if (v == HIGH) start = millis();
  else width = millis() - start;
}


uint16_t PWM_concentration()
{
  noInterrupts();
  uint16_t TimeHigh = width;  //  milliseconds
  interrupts();

  uint16_t concentration = round(((TimeHigh - 2) * MAX_CONCENTRATION) * 0.001);
  return concentration;
}


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MHZCO2_LIB_VERSION: ");
  Serial.println(MHZCO2_LIB_VERSION);
  
  attachInterrupt(digitalPinToInterrupt(3), IRQ, CHANGE);
}


void loop()
{
  Serial.println(PWM_concentration());
  delay(1000);
}


//  -- END OF FILE --

