//
//    FILE: TSL235R_demo.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
// PURPOSE: demo
//    DATE: 2021-05-29


// NOTE
// This code will work up to ~150KHz on an Arduino UNO
// above that frequency the interrupt saturate the processor.


// Digital Pin layout ARDUINO
// =============================
//  2     IRQ 0    - to TSL235R
// 
// PIN 1 - GND
// PIN 2 - VDD - 5V
// PIN 3 - SIGNAL


#include "TSL235R.h"


TSL235R  mySensor;

volatile uint32_t cnt = 0;
uint32_t oldcnt = 0;
uint32_t t = 0;
uint32_t lastMeasurement = 0;


void count_irq()
{
  cnt++;
}


///////////////////////////////////////////////////////////////////
//
// SETUP
//
void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  pinMode(2, INPUT_PULLUP);
  attachInterrupt(0, count_irq, FALLING);

  mySensor.setWavelength(450);
}


void loop()
{
  uint32_t now = millis();
  if (now - lastMeasurement >= 1000)
  {
    lastMeasurement = now;
    t = cnt;
    uint32_t Hz = t - oldcnt;
    oldcnt = t;
    
    Serial.print("Hz: ");
    Serial.print(Hz);
    Serial.print("\t");
    Serial.print(mySensor.irradiance(Hz));   // assumption 1 second
    Serial.println(" uW/cm2");
  }
}

// -- END OF FILE --
