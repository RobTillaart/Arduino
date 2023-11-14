//
//    FILE: MTP40F_PWM_demo_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test of PWM duration formula MTP40F PWM interface
//     URL: https://github.com/RobTillaart/MTP40F

//  This sketch is meant to test the PWM conversion formula.
//  Written for an Arduino UNO.
//  - it first loops through all possible values.
//  - then it generates a random pulse length (within range) on pin 7
//  - connect pin 7 to interrupt pin 3 as test.
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

  //  Formula test
  for (uint16_t d = 2; d < 1004; d += 2)
  {
    Serial.print(d);
    Serial.print('\t');
    Serial.println(duration2PPM(d));
  }
}


void loop()
{
  //  generate random pulses 
  //  connect pin 7 to interrupt pin as test.
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);
  delay(random(1000) + 2);
  digitalWrite(7, LOW);

  uint16_t d = duration;
  uint16_t ppm = duration2PPM(d);
  Serial.print(d);
  Serial.print("\t");
  Serial.println(ppm);
}


////////////////////////////////////////////////////////////////////////////
//
// PWM CAPTURE IRQ
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
