//
//    FILE: TSL235R_non_interrupt.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo polling
//    DATE: 2021-06-03
//
// NOTE
//   This code will work up to ~150 kHz on an Arduino UNO
//   above that pulses come in faster than digitalRead 
//   can reliably handle
//
// Digital Pin layout ARDUINO
// =============================
//  2 - to TSL235R
//
// PIN 1 - GND
// PIN 2 - VDD - 5V
// PIN 3 - SIGNAL


#include "TSL235R.h"


TSL235R  mySensor;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  pinMode(2, INPUT_PULLUP);
  mySensor.setWavelength(450);
}


void loop()
{
  uint16_t cnt = 0;
  uint32_t start = micros();
  while (cnt < 50000)
  {
    while (digitalRead(2) == HIGH);  // wait for LOW
    cnt++;
    while (digitalRead(2) == LOW);   // wait for HIGH
  }
  uint32_t duration = micros() - start;
  float freq = (1e6 * cnt) / duration;

  Serial.print("Hz: ");
  Serial.print(freq);
  Serial.print("\t");
  Serial.print(mySensor.irradiance(freq));   // assumption 1 second
  Serial.println(" uW/cm2");
}


// -- END OF FILE --

