//
//    FILE: rain_interrupt.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo rain_interrupt digital out
//     URL: https://github.com/RobTillaart/RAIN


#include "rain.h"

#define ANALOGPIN         A0
#define POWERPIN          7
#define DIGIOUT_IRQ       2

RAIN  RS(ANALOGPIN, POWERPIN);

volatile bool waterDetected = false;


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);
  Serial.print("RAIN_LIB_VERSION: ");
  Serial.println(RAIN_LIB_VERSION);
  Serial.println("EXPERIMENTAL:");

  RS.begin(5.000, 1023);

  attachInterrupt(digitalPinToInterrupt(DIGIOUT_IRQ), isr, FALLING);
}


void loop()
{
  if (waterDetected)
  {
    Serial.print(millis());
    Serial.print('\t');
    Serial.print(RS.read(), 3);
    Serial.print('\t');
    Serial.print(RS.getLevel());
    Serial.print('\n');
    waterDetected = false;
  }
  delay(100);
  //  other code here
}


void isr()
{
  waterDetected = true;
}


// -- END OF FILE --
