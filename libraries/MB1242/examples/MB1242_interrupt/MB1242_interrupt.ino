//
//    FILE: MB1242_interrupt.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test status pin via interrupt
//     URL: https://github.com/RobTillaart/MB1242
//
//  Connect device status pin (pin 2) to interrupt pin of the MCU

#include "MB1242.h"


MB1242 MB(0x70);
volatile bool ready = false;
const int interruptPin = 2;   //  adjust if needed.

void MB_IRQ()
{
  ready = true;
}


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("MB1242_LIB_VERSION: ");
  Serial.println(MB1242_LIB_VERSION);
  Serial.println();
  delay(100);

  attachInterrupt(digitalPinToInterrupt(interruptPin), MB_IRQ, FALLING);

  Wire.begin();
  MB.begin();

  MB.requestDistance();
}


void loop()
{
  if (ready)
  {
    Serial.println(MB.readCM());
    ready = false;
    MB.requestDistance();
  }
}


//  -- END OF FILE --
