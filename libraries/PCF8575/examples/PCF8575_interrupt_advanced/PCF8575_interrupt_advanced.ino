//
//    FILE: PCF8575_interrupt_advanced.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test PCF8575 library
//     URL: https://github.com/RobTillaart/PCF8575
//
//  TEST SETUP
//   Connect INT pin of the PCF8575 to UNO pin 2
//
//   (from figure 4 datasheet
//   Place a pull up resistor 4K7 between pin and 5V
//   Place a capacitor 10-400 pF between pin and GND


#include "PCF8575.h"

PCF8575 PCF(0x20);


////////////////////////////////////
//
//  INTERRUPT ROUTINE + FLAG
//
const int IRQPIN = 2;

volatile uint8_t interruptCount = 0;

void pcf_irq()
{
  interruptCount++;
}


////////////////////////////////////
//
//  MAIN CODE
//
void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PCF8575_LIB_VERSION: ");
  Serial.println(PCF8575_LIB_VERSION);

  Wire.begin();
  PCF.begin();

  pinMode(IRQPIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(IRQPIN), pcf_irq, FALLING);
}


void loop()
{
  uint32_t now = millis();

  //  make a local copy of the counter.
  noInterrupts();
  uint8_t irq_count = interruptCount;
  interruptCount = 0;
  interrupts();

  if (irq_count > 0)
  {
    if (irq_count > 1)
    {
      Serial.print("IRQ missed: ");
      Serial.println(irq_count - 1);  //  as last will be handled
    }
    uint16_t x = PCF.read16();
    Serial.print("READ:\t");
    Serial.print('\t');
    Serial.print(now);
    Serial.print('\t');
    Serial.println(x, HEX);
  }

  //  simulate doing other things here.
  //  uses to a large delay to miss IRQ's on purpose.
  delay(1000);
}


//  -- END OF FILE --

