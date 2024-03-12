//
//    FILE: TCA9555_interrupt.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test TCA9555 interrupt
//     URL: https://github.com/RobTillaart/TCA9555
//
//  See datasheet 
//  - 9.3.3 Interrupt (INT) Output
//  - timing see page 13

#include "TCA9555.h"


TCA9555 TCA(0x27);

uint8_t INT_PIN = 2;
volatile bool flag = false;


void tca_irq()
{
  flag = true;
}


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("TCA9555_LIB_VERSION: ");
  Serial.println(TCA9555_LIB_VERSION);
  Serial.println();

  Wire.begin();
  TCA.begin();

  Serial.println("Set pinMode16 INPUT");
  TCA.pinMode16(0xFFFF);

  //  Arduino UNO interrupt, adapt to your board
  //  https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
  pinMode(2, INPUT);
  attachInterrupt(0, tca_irq, FALLING);  //  todo verify
}


void loop()
{
  if (flag)
  {
    for (int pin = 0; pin < 16; pin++)
    {
      int val = TCA.read1(pin);
      Serial.print(val);
      Serial.print('\t');
    }
    Serial.println();
  }
}


//  -- END OF FILE --
