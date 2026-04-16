//
//    FILE: TCA6424A_interrupt.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/TCA6424A_RT


#include "TCA6424A.h"


TCA6424A tca(0x20);

//  interrupt 
uint8_t IRQpin = 2;
volatile bool IRQflag = false;

void flag() 
{
  IRQflag = true;
}


//////////////////////////////////
void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("TCA6424A_LIB_VERSION: ");
  Serial.println(TCA6424A_LIB_VERSION);
  Serial.println();

  Wire.begin();
  Wire.setClock(400000);

  if (tca.begin() == false)
  {
    Serial.println("No TCA found.");
    while (1);
  }

  //  Set all pins as inputs
  tca.setPinMode24(0xFFFFFF);
  tca.setPolarity24(0xFFFFFF);
  Serial.print(millis());
  Serial.println(": config done..");

  pinMode(IRQpin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(IRQpin), flag, FALLING);
}


void loop(void)
{
  //  if IRQ has set the flag, print new values.
  if (IRQflag == true)
  {
    uint32_t value = tca.digitalRead24();
    Serial.print(millis());
    Serial.print(": \t");
    Serial.println(value, HEX);
    IRQflag = false;
  }
}


//  -- END OF FILE --
