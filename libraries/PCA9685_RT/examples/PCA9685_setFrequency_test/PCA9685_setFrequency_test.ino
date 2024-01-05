//
//    FILE: PCA9685_setFrequency_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test PCA9685 library
//     URL: https://github.com/RobTillaart/PCA9685_RT
//
//  sets one channel to max PWM 0..4095
//  and connect the output to an interrupt pin 2
//  to see the frequency of the PWM


#include "PCA9685.h"


PCA9685 PCA(0x40);

const uint8_t IRQ_PIN = 2;
volatile uint16_t count = 0;
uint32_t lastTime = 0;
uint16_t freq = 24;

uint8_t lines = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PCA9685_LIB_VERSION: ");
  Serial.println(PCA9685_LIB_VERSION);
  Serial.println();

  Wire.begin();
  PCA.begin();

  pinMode(IRQ_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(IRQ_PIN), irq, RISING);  //  CHANGE

  PCA.setFrequency(PCA9685_MIN_FREQ);   //  == 24
  PCA.setPWM(15, 0, 4095);              //  gives 2 changes per interval

  Serial.println("\nSET\tGET\tGET%\tIRQ\tIRQ%");
}


//  INTERRUPT ROUTINE TO COUNT THE PULSES
void irq()
{
  count++;
}


void loop()
{
  uint32_t now = millis();
  if (now - lastTime >= 1000)
  {
    lastTime += 1000;
    //  make a working copy of count
    noInterrupts();
    uint16_t t = count;
    count = 0;
    interrupts();

    Serial.print(freq);
    Serial.print("\t");
    Serial.print(PCA.getFrequency(false));
    Serial.print("\t");
    Serial.print(100.0 * PCA.getFrequency(false) / freq, 1);
    Serial.print("\t");
    Serial.print(t);
    Serial.print("\t");
    Serial.print(100.0 * t / freq, 1);
    Serial.print("\n");

    freq += 4;
    //  page 25 datasheet; PCA9685_MAX_FREQ, PCA9685_MIN_FREQ
    if (freq >= 1526) freq = 24;
    PCA.setFrequency(freq);
    PCA.setPWM(15, 0, 4095);

    lines++;
    if (lines == 20)
    {
      Serial.println("\nSET\tGET\tGET%\tIRQ\tIRQ%");
      lines = 0;
    }
  }
}


//  -- END OF FILE --

