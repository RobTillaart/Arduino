//
//    FILE: MTP40F_PWM_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo of MTP40F PWM interface
//     URL: https://github.com/RobTillaart/MTP40F
//
//  TODO TEST WITH MTP40F SENSOR
//
//  Connect the PWM output to the interrupt pin 2 or 3 of the UNO.
//  other processors interrupts pins work slightly different


volatile uint32_t start = 0;
volatile uint16_t duration = 0;
uint8_t interruptPin = 3;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), mtp40F_irq, CHANGE);
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
void mtp40F_irq()
{
  if (digitalRead(interruptPin) == HIGH) start = millis();
  else duration = millis() - start;
}


//  ppm == 0     is a pulse length of 2 millis.
//  ppm == 2000  is a pulse length of 1002 millis.
//  every 2 ppm adds 1 millis
uint16_t duration2PPM(uint16_t d)
{
  return (d - 2) * 2;
}


//  -- END OF FILE --

