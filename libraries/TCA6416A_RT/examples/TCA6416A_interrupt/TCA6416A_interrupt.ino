//
//    FILE: TCA6416A_interrupt.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/TCA6408A_RT


#include "TCA6416A.h"


TCA6416A tca(0x20);

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
  Serial.print("TCA6416A_LIB_VERSION: ");
  Serial.println(TCA6416A_LIB_VERSION);
  Serial.println();

  Wire.begin();
  Wire.setClock(400000);

  if (tca.begin() == false)
  {
    Serial.println("No TCA found.");
    while (1);
  }

  //  Set all pins as inputs
  tca.setPinMode16(0xFFFF);
  tca.setPolarity16(0xFFFF);
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
    int value = tca.digitalRead16();
    Serial.print(millis());
    Serial.print(": \t");
    Serial.println(value, HEX);
    IRQflag = false;
  }
}


//  -- END OF FILE --
