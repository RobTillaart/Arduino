//
//    FILE: TSL235R_multi.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2021-05-29
//
// NOTE
//   the max number of interrupt an Arduino UNO can handle
//   is in the order of ~150 KHz for all interrupts.
//
// Digital Pin layout ARDUINO
// =============================
//  2     IRQ 0    - to TSL235R
//  3     IRQ 1    - to TSL235R
//
// PIN 1 - GND
// PIN 2 - VDD - 5V
// PIN 3 - SIGNAL


#include "TSL235R.h"


TSL235R  mySensor_450;
TSL235R  mySensor_650;

volatile uint32_t cnt1 = 0;
volatile uint32_t cnt2 = 0;
uint32_t oldcnt1 = 0;
uint32_t oldcnt2 = 0;
uint32_t t = 0;
uint32_t lastMeasurement = 0;


void count_irq1()
{
  cnt1++;
}


void count_irq2()
{
  cnt2++;
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
  pinMode(3, INPUT_PULLUP);
  attachInterrupt(0, count_irq1, RISING);
  attachInterrupt(1, count_irq2, RISING);

  mySensor_450.setWavelength(450);
  mySensor_650.setWavelength(650);
}


void loop()
{
  uint32_t now = millis();
  if (now - lastMeasurement >= 1000)
  {
    lastMeasurement = now;

    t = cnt1;
    uint32_t Hz = t - oldcnt1;
    oldcnt1 = t;
    Serial.print("irradiance 450 nm:\t");
    Serial.print(mySensor_450.irradiance(Hz));
    Serial.println(" uW/cm2");

    t = cnt2;
    Hz = t - oldcnt2;
    oldcnt2 = t;
    Serial.print("irradiance 650 nm:\t");
    Serial.print(mySensor_650.irradiance(Hz));
    Serial.println(" uW/cm2");
  }
}


// -- END OF FILE --

