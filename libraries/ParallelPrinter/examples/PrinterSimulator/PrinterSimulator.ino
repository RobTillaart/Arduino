//
//    FILE: PrinterSimulator.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo
//    DATE: 2020-06-24
//    (c) : MIT

// Simple parallel printer simulator, prints to serial...
// version could be made with a shiftin register ....

#include "Arduino.h"

uint8_t STROBE = 2;
uint8_t BUSY   = 13;
uint8_t OOP    = 10;
uint8_t dataPins[] = { 3, 4, 5, 6, 7, 8, 9, 10 };

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  pinMode(STROBE, INPUT);
  pinMode(OOP,    OUTPUT);
  pinMode(BUSY,   OUTPUT);  // build in LED UNO.

  for (uint8_t i = 0; i < 8; i++)
  {
    pinMode(dataPins[i], INPUT);
  }

  digitalWrite(OOP, HIGH);  // HIGH is OK
  digitalWrite(BUSY, HIGH); // BUSY during startup

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

  digitalWrite(BUSY, LOW);
  while (digitalRead(STROBE) == HIGH) yield();
  for (int i = 0; i < 8; i++)
  {
    x <<= 1;
    if (digitalRead(dataPins[i]) == HIGH) x += 1;
  }
  while (digitalRead(STROBE) == LOW) yield();
  digitalWrite(BUSY, HIGH);

  // process data
  Serial.write(x);
}

// -- END OF FILE --
