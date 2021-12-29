//
//    FILE: TSL235R_multi_alternate.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2021-05-29
//
// NOTE
//   This code will work up to ~150 KHz on an Arduino UNO
//
// NOTE
//   in the demo we alternate the two interrupt pins to be able
//   to have a larger range per sensor. 
//   The price is that the values are behind at least a second.
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

volatile uint32_t pulses = 0;
uint32_t t = 0;
uint32_t lastMeasurement = 0;


uint8_t  irq_select = 0;

void count_irq()
{
  pulses++;
}


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);

  mySensor_450.setWavelength(450);
  mySensor_650.setWavelength(650);

  irq_select = 0;
  attachInterrupt(0, count_irq, FALLING);
  lastMeasurement = millis();
}


void loop()
{
  if (millis() - lastMeasurement >= 1000)
  {
    if (irq_select == 0)
    {
      detachInterrupt(irq_select);  // 0
      Serial.print("irradiance (0):\t");
      Serial.print(mySensor_450.irradiance(pulses));   // assumption 1 second
      Serial.println(" uW/cm2");
      pulses = 0;
      irq_select = 1;
      attachInterrupt(irq_select, count_irq, FALLING);
    }
    else
    {
      detachInterrupt(irq_select);  // 1
      Serial.print("irradiance (1):\t");
      Serial.print(mySensor_650.irradiance(pulses));   // assumption 1 second
      Serial.println(" uW/cm2");
      pulses = 0;
      irq_select = 0;
      attachInterrupt(irq_select, count_irq, FALLING);
    }
    lastMeasurement = millis();
  }

  // ...
}


// -- END OF FILE --

