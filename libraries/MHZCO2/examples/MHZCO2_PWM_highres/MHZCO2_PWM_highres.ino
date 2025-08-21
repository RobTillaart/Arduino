//
//    FILE: MHZCO2_PWM_highres.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo MHZ library / sensor
//     URL: https://github.com/RobTillaart/MHZCO2
//
//  This example measures the HIGH and PERIOD timing in microseconds.
//  It uses the actual period length and returns the PPM as float.

/*
   DATASHEET P.?
   Conversion between PWM output and concentration,
   use interrupt pin 3 of Arduino UNO.
*/


#include "Arduino.h"
#include "MHZCO2.h"


//  adjust to calibrate.
const float MAX_CONCENTRATION = 2000.0;


//  interrupt variables
volatile uint32_t period;
volatile uint32_t width;


void IRQ()
{
  static uint32_t lastPeriod = 0;
  static uint32_t start = 0;

  uint32_t now = micros();
  if (digitalRead(3) == HIGH)
  {
    period = now - lastPeriod;
    start = now;
  }
  else
  {
    width = micros() - start;
  }
}


float CO2_PPM()
{
  noInterrupts();
  uint32_t TimeHigh = width;     //  microseconds
  uint32_t TimePeriod = period;  //  microseconds
  interrupts();

  float concentration = (MAX_CONCENTRATION * (TimeHigh - 2000)) / (TimePeriod - 4000);
  return concentration;
}


void setup()
{
  // while (!Serial);  //  uncomment if needed
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("MHZCO2_LIB_VERSION: ");
  Serial.println(MHZCO2_LIB_VERSION);
  Serial.println();

  attachInterrupt(digitalPinToInterrupt(3), IRQ, CHANGE);
}


void loop()
{
  Serial.println(CO2_PPM(), 1);
  delay(1000);
}


//  -- END OF FILE --
