//
//    FILE: PCA9552_digitalRead.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2023-07-18
// PURPOSE: test PCA9552 library
//     URL: https://github.com/RobTillaart/PCA9552
//
//  Connect pin 0 to 4 to either +5V or to GND
//  to read LOW/HIGH values


#include "Arduino.h"
#include "Wire.h"
#include "PCA9552.h"


PCA9552 leds(0x62);


void setup()
{
  Serial.begin(115200);
  Serial.print("PCA9552_LIB_VERSION: ");
  Serial.println(PCA9552_LIB_VERSION);
  Serial.println();

  if (leds.begin() == false)
  {
    Serial.println("Could not connect.");
    while (1);
  }

  for (int pin = 0; pin < leds.outputCount(); pin++)
  {
    leds.pinMode(pin, INPUT);
  }
}


void loop()
{
  for (int pin = 0; pin < leds.outputCount(); pin++)
  {
    int x = leds.digitalRead(pin);
    Serial.print(x);
    Serial.print('\t');
  }
  Serial.println();
  delay(100);
}


//  -- END OF FILE --
