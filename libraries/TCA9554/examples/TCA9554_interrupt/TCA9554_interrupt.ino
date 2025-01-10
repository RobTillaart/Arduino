//
//    FILE: TCA9554_interrupt.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test TCA9554 interrupt
//     URL: https://github.com/RobTillaart/TCA9554
//
//  See datasheet 
//  - 9.3.3 Interrupt (INT) Output
//  - timing see page 13

#include "TCA9554.h"


TCA9554 TCA(0x27);

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
  Serial.print("TCA9554_LIB_VERSION: ");
  Serial.println(TCA9554_LIB_VERSION);
  Serial.println();

  Wire.begin();
  TCA.begin();

  Serial.println("Set pinMode8 INPUT");
  TCA.pinMode8(0xFF);

  //  Arduino UNO interrupt, adapt to your board
  //  https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
  pinMode(2, INPUT);
  attachInterrupt(0, tca_irq, FALLING);  //  TODO verify
}


void loop()
{
  if (flag)
  {
    flag = false;
    for (int pin = 0; pin < 8; pin++)
    {
      int val = TCA.read1(pin);
      Serial.print(val);
      Serial.print('\t');
    }

    Serial.println();
  }
}


//  -- END OF FILE --
