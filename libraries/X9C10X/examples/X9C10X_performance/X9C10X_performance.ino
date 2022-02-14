//
//    FILE: X9C10X_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo

#include "Arduino.h"
#include "X9C10X.h"


X9C10X pot(12345);  //  100KΩ  (ALT-234)

uint32_t start, stop;

volatile uint8_t pos;
volatile uint32_t ohm;

void setup()
{
  Serial.begin(115200);
  while (!Serial);

  Serial.println();
  Serial.print("X9C10X_LIB_VERSION: ");
  Serial.println(X9C10X_LIB_VERSION);

  pot.begin(8, 9, 10, 0);  // pulse, direction, select, position

  start = micros();
  pos = pot.getPosition();
  stop = micros();
  Serial.print("getPosition:\t");
  Serial.println(stop - start);
  delay(100);

  Serial.println("\nfrom 0 to ...");
  pot.setPosition(0);
  start = micros();
  pot.setPosition(33);
  stop = micros();
  Serial.print("setPosition(33):\t");
  Serial.println(stop - start);
  delay(100);

  pot.setPosition(0);
  start = micros();
  pot.setPosition(66);
  stop = micros();
  Serial.print("setPosition(66):\t");
  Serial.println(stop - start);
  delay(100);

  pot.setPosition(0);
  start = micros();
  pot.setPosition(99);
  stop = micros();
  Serial.print("setPosition(99):\t");
  Serial.println(stop - start);
  delay(100);

  Serial.println("\nfrom n to m");
  pot.setPosition(0);
  start = micros();
  pot.setPosition(33);
  stop = micros();
  Serial.print("setPosition(33):\t");
  Serial.println(stop - start);
  delay(100);

  start = micros();
  pot.setPosition(66);
  stop = micros();
  Serial.print("setPosition(66):\t");
  Serial.println(stop - start);
  delay(100);

  start = micros();
  pot.setPosition(99);
  stop = micros();
  Serial.print("setPosition(99):\t");
  Serial.println(stop - start);
  delay(100);

  Serial.println();
  start = micros();
  ohm = pot.getMaxOhm();
  stop = micros();
  Serial.print("getMaxOhm():\t");
  Serial.println(stop - start);
  delay(100);

  start = micros();
  ohm = pot.getOhm();
  stop = micros();
  Serial.print("getOhm():\t");
  Serial.println(stop - start);
  delay(100);

  Serial.println();
  pot.setPosition(0);
  start = micros();
  for (int i = 0; i < 10; i++) pot.incr();
  stop = micros();
  Serial.print("10 x incr():\t");
  Serial.println(stop - start);
  delay(100);

  pot.setPosition(50);
  start = micros();
  for (int i = 0; i < 10; i++) pot.decr();
  stop = micros();
  Serial.print("10 x decr():\t");
  Serial.println(stop - start);
  delay(100);
}


void loop()
{
}


// -- END OF FILE --
