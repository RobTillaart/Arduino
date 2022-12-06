//
//    FILE: rain_digital_out.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo digital out DO pin
//     URL: https://github.com/RobTillaart/RAIN


#include "rain.h"

#define ANALOGPIN         A0
#define POWERPIN          7
#define DIGIOUT           8

RAIN  RS(ANALOGPIN, POWERPIN);


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);
  Serial.print("RAIN_LIB_VERSION: ");
  Serial.println(RAIN_LIB_VERSION);
  Serial.println("EXPERIMENTAL:");

  RS.begin(5.000, 1023);

  pinMode(DIGIOUT, INPUT_PULLUP);
}


void loop()
{
  if (digitalRead(DIGIOUT) == LOW)
  {
    Serial.print(millis());
    Serial.print('\t');
    Serial.print(RS.read(), 3);
    Serial.print('\t');
    Serial.print(RS.getLevel());
    Serial.print('\n');
  }
  delay(100);
  //  other code here
}


// -- END OF FILE --
