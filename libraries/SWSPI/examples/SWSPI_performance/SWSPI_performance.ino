//
//    FILE: SWSPI_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test
//     URL: https://github.com/RobTillaart/SWSPI

#include "SWSPI.h"

SWSPI myspi(9, 10, 13);

uint8_t selectPin = 8;

uint32_t start, stop;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("SWSPI_LIB_VERSION: ");
  Serial.println(SWSPI_LIB_VERSION);
  Serial.println();

  myspi.begin();
  //  init select pin.
  pinMode(selectPin,  OUTPUT);

  Serial.println("\nMODE 0");
  {
    delay(100);
    start = micros();
    myspi.beginTransaction(LSBFIRST, 0);
    digitalWrite(selectPin, LOW);
    myspi.transfer(0x55);
    digitalWrite(selectPin, HIGH);
    myspi.endTransaction();
    stop = micros();
    Serial.println(stop - start);
    delay(100);
    start = micros();
    myspi.beginTransaction(MSBFIRST, 0);
    digitalWrite(selectPin, LOW);
    myspi.transfer(0x55);
    digitalWrite(selectPin, HIGH);
    myspi.endTransaction();
    stop = micros();
    Serial.println(stop - start);
    delay(100);
  }

  Serial.println("\nMODE 1");
  {
    delay(100);
    start = micros();
    myspi.beginTransaction(LSBFIRST, 1);
    digitalWrite(selectPin, LOW);
    myspi.transfer(0x55);
    digitalWrite(selectPin, HIGH);
    myspi.endTransaction();
    stop = micros();
    Serial.println(stop - start);
    delay(100);
    start = micros();
    myspi.beginTransaction(MSBFIRST, 1);
    digitalWrite(selectPin, LOW);
    myspi.transfer(0x55);
    digitalWrite(selectPin, HIGH);
    myspi.endTransaction();
    stop = micros();
    Serial.println(stop - start);
    delay(100);
  }

  Serial.println("\nMODE 2");
  {
    delay(100);
    start = micros();
    myspi.beginTransaction(LSBFIRST, 2);
    digitalWrite(selectPin, LOW);
    myspi.transfer(0x55);
    digitalWrite(selectPin, HIGH);
    myspi.endTransaction();
    stop = micros();
    Serial.println(stop - start);
    delay(100);
    start = micros();
    myspi.beginTransaction(MSBFIRST, 2);
    digitalWrite(selectPin, LOW);
    myspi.transfer(0x55);
    digitalWrite(selectPin, HIGH);
    myspi.endTransaction();
    stop = micros();
    Serial.println(stop - start);
    delay(100);
  }

  Serial.println("\nMODE 3");
  {
    delay(100);
    start = micros();
    myspi.beginTransaction(LSBFIRST, 3);
    digitalWrite(selectPin, LOW);
    myspi.transfer(0x55);
    digitalWrite(selectPin, HIGH);
    myspi.endTransaction();
    stop = micros();
    Serial.println(stop - start);
    delay(100);
    start = micros();
    myspi.beginTransaction(MSBFIRST, 3);
    digitalWrite(selectPin, LOW);
    myspi.transfer(0x55);
    digitalWrite(selectPin, HIGH);
    myspi.endTransaction();
    stop = micros();
    Serial.println(stop - start);
    delay(100);
  }

  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --
