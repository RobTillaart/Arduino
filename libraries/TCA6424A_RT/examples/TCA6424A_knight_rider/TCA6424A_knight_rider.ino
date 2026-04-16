//
//    FILE: TCA6424A_knight_rider.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/TCA6424A_RT
//
//  connect 24 LEDs to the 24 pins with appropriate resistors.

#include "TCA6424A.h"


TCA6424A tca(0x20);

int pin = 1;
int direction = 1;
uint32_t lastTime = 0;

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

  //  Set all pins as outputs
  tca.setPinMode24(0x000000);
  //  Set all pins to OFF
  tca.digitalWrite24(0x000000);

  Serial.print(millis());
  Serial.println(": config done..");
}


void loop(void)
{
  if (millis() - lastTime >= 125)
  {
    lastTime = millis();
    int prevPin = pin;
    //  need to flip direction?
    if (pin >= 23 || pin <= 0) direction = -direction;
    pin = pin + direction;
    //  adjust active led
    tca.digitalWrite1(pin, 1);
    tca.digitalWrite1(prevPin, 0);
    Serial.println(pin);
  }

  //  other tasks
}


//  -- END OF FILE --
