//
//    FILE: PCA9685_setFrequency_offset.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test PCA9685 library
//     URL: https://github.com/RobTillaart/PCA9685_RT
//
//  This sketch is to determine the offset needed to get te best matching
//  value for offset to match the wanted frequency.
//
//  connect PWM line 15 to IRQ line 2 to monitor the real frequency
//  set the frequency to the value you want.
//  use the + and - keys to adjust the frequency to get the wanted frequency.
//
//  Note: the higher the frequency, the more inaccurate the real frequency,


#include "PCA9685.h"


PCA9685 PCA(0x40);

const uint8_t IRQ_PIN = 2;
volatile uint16_t count = 0;
uint32_t lastTime = 0;


uint16_t freq = 200;  //  adjust to freq needed  (between 24..1526 )
int offset = 0;
int lines = 0;


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
  attachInterrupt(digitalPinToInterrupt(IRQ_PIN), irq, RISING);

  PCA.setFrequency(freq, offset);
  PCA.setPWM(15, 0, 4095);    //  gives 2 changes per interval

  Serial.println("\nSET\tIRQ\tIRQ%\tOFFSET");
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
    Serial.print(t);
    Serial.print("\t");
    Serial.print(100.0 * t / freq, 1);
    Serial.print("\t");
    Serial.print(offset);
    Serial.print("\n");

    lines++;
    if (lines == 20)
    {
      Serial.println("\nSET\tIRQ\tIRQ%\tOFFSET");
      lines = 0;
    }
  }

  if (Serial.available())
  {
    char c = Serial.read();
    if (c == '+') offset++;
    if (c == '-') offset--;
    PCA.setFrequency(freq, offset);
    PCA.setPWM(15, 0, 4095);
  }

}


//  -- END OF FILE --

