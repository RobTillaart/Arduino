//
//    FILE: MTP40D_PWM_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo of MTP40D PWM interface
//    DATE: 2021-08-27
//     URL: https://github.com/RobTillaart/MTP40C
//
//
//  TODO TEST WITH MTP40D SENSOR
//
// Connect the PWM output to the interrupt pin 2 or 3 of the UNO.
// other processors interrupts pins work slightly different


volatile uint32_t start = 0;
volatile uint16_t duration = 0;
uint8_t interruptPin = 3;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), mtp40D_irq, CHANGE);
}


void loop()
{
  uint16_t d = duration;
  uint16_t ppm = duration2PPM(d);
  Serial.print(d);
  Serial.print("\t");
  Serial.println(ppm);

  delay(2000);
}


////////////////////////////////////////////////////////////////////////////
//
// PWM CAPTURE IRQ + CONVERSION FUNCTION
//
void mtp40D_irq()
{
  if (digitalRead(interruptPin) == HIGH) start = millis();
  else duration = millis() - start;
}


// ppm == 0 is a pulselengtm of 2000 micros.
// every 10 ppm adds 2000 micros
// 1002000 micros = 5000 ppm
uint16_t duration2PPM(uint16_t duration)
{
  return ((duration - 1) >> 1 ) * 10;
}


// -- END OF FILE --

