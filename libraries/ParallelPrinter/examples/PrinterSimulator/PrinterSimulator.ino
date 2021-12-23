//
//    FILE: PrinterSimulator.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2020-06-24
//
// Simple parallel printer simulator, prints to serial...
// version could be made with a shiftin register ....


#include "Arduino.h"


uint8_t PIN_STROBE = 2;
uint8_t PIN_BUSY   = 13;
uint8_t PIN_OOP    = 10;
uint8_t dataPins[] = { 3, 4, 5, 6, 7, 8, 9, 10 };


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  pinMode(PIN_STROBE, INPUT);
  pinMode(PIN_OOP,    OUTPUT);
  pinMode(PIN_BUSY,   OUTPUT);  // build in LED UNO.

  for (uint8_t i = 0; i < 8; i++)
  {
    pinMode(dataPins[i], INPUT);
  }

  digitalWrite(PIN_OOP, HIGH);  // HIGH is OK
  digitalWrite(PIN_BUSY, HIGH); // BUSY during startup

  delay(5000);              // do startup thingies.
}


void loop()
{
  handleInput();
  // do other things here
}


void handleInput()
{
  uint8_t x = 0;

  digitalWrite(PIN_BUSY, LOW);
  while (digitalRead(PIN_STROBE) == HIGH) yield();
  for (int i = 0; i < 8; i++)
  {
    x <<= 1;
    if (digitalRead(dataPins[i]) == HIGH) x += 1;
  }
  while (digitalRead(PIN_STROBE) == LOW) yield();
  digitalWrite(PIN_BUSY, HIGH);

  // process data
  Serial.write(x);
}


// -- END OF FILE --

