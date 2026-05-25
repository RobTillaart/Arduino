//
//    FILE: A02YYM_PWM_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test code for a A02YY "PWM" device
//          does not use the library.
//     URL: https://github.com/RobTillaart/A02YYUW
//          https://www.dypcn.com/uploads/A02-Output-Interfaces.pdf


#include "Arduino.h"

//  myRX, myTX does not conflict with ESP32 RX / TX
uint8_t myRX = 4;
uint8_t myTX = 3;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  //  Serial.print("A02YYUW_LIB_VERSION: ");
  //  Serial.println(A02YYUW_LIB_VERSION);
  Serial.println();

  pinMode(myRX, OUTPUT);
  digitalWrite(myRX, HIGH);
  pinMode(myTX, INPUT);
  //  wait for TX LOW
  while (digitalRead(myTX) == HIGH);
}


void loop()
{
  digitalWrite(myRX, LOW);
  delay(5);
  digitalWrite(myRX, HIGH);

  while (digitalRead(myTX) == LOW);
  uint32_t start = micros();
  while (digitalRead(myTX) == HIGH);
  uint32_t stop = micros();

  uint32_t duration = stop - start;
  float centimetres = duration / 57.5;

  Serial.print(millis());
  Serial.print("\t");
  Serial.println(centimetres, 1);

  delay(1000);
}


//  -- END OF FILE --
