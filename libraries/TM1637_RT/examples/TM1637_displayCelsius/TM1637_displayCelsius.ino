//
//    FILE: TM1637_displayCelsius.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo TM1637 library
//     URL: https://github.com/RobTillaart/TM1637_RT


#include "TM1637.h"

TM1637 TM;

int temperature = 0;

void setup()
{
  while(!Serial);
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("TM1637_LIB_VERSION: ");
  Serial.println(TM1637_LIB_VERSION);
  Serial.println();

  TM.begin(7, 6, 4);       //  clock pin, data pin, #digits
}


void loop()
{
  //  adjust brightness to temperature, just because it can be done.
  if (temperature < 0) TM.setBrightness(0);
  else TM.setBrightness(temperature / 20);

  //  simulate temperature
  //  colon indicate overflow or underflow.
  TM.displayCelsius(temperature, (temperature < -9) || (temperature > 99));
  temperature++;
  if (temperature == 125) temperature = -20;
  delay(100);
}


//  -- END OF FILE --
