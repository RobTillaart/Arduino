//
//    FILE: TSL235R_non_interrupt_UNO.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo polling with direct port access = AVR.UNO specific!
//    DATE: 2021-06-03
//
// NOTE
//   This code will work up to ~1700 kHz (3800 uW/cm2) on an Arduino UNO
//   above that pulses come in faster than the code can reliably handle
//
// NOTE
//   the code is UNO specific as it uses low level PORT manipulations
//   the code is blocking and not suitable for low level of radiance.
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
  while (cnt < 60000)
  {
    while (PIND & 0x04);             // wait for LOW      AVR.UNO specific !!
    cnt++;
    while ((PIND & 0x04) == 0x00);   // wait for HIGH
  }
  uint32_t duration = micros() - start;
  float freq = (1e6 * cnt) / duration;

  Serial.print("Hz: ");
  Serial.print(freq);
  Serial.print("\t");
  Serial.print(mySensor.irradiance_HS(cnt, duration));
  // Serial.print(mySensor.irradiance(freq));
  Serial.println(" uW/cm2");
}


// -- END OF FILE --

