//
//    FILE: SWSPI_test_input.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test
//     URL: https://github.com/RobTillaart/SWSPI
//
//  Connect pin 9 to 10 for easy test.
/*
  SWSPI_LIB_VERSION: 0.1.1
  MODE 0
  AA
  MODE 1
  55
  MODE 2
  AA
  MODE 3
  55
*/

#include "SWSPI.h"

SWSPI myspi(9, 10, 13);

uint8_t selectPin = 8;

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
    myspi.beginTransaction(LSBFIRST, 0);
    digitalWrite(selectPin, LOW);
    Serial.println(myspi.transfer(0x55), HEX);
    digitalWrite(selectPin, HIGH);
    myspi.endTransaction();
  }

  Serial.println("\nMODE 1");
  {
    myspi.beginTransaction(LSBFIRST, 1);
    digitalWrite(selectPin, LOW);
    Serial.println(myspi.transfer(0x55), HEX);
    digitalWrite(selectPin, HIGH);
    myspi.endTransaction();
  }

  Serial.println("\nMODE 2");
  {
    myspi.beginTransaction(LSBFIRST, 2);
    digitalWrite(selectPin, LOW);
    Serial.println(myspi.transfer(0x55), HEX);
    digitalWrite(selectPin, HIGH);
    myspi.endTransaction();
  }

  Serial.println("\nMODE 3");
  {
    myspi.beginTransaction(LSBFIRST, 3);
    digitalWrite(selectPin, LOW);
    Serial.println(myspi.transfer(0x55), HEX);
    digitalWrite(selectPin, HIGH);
    myspi.endTransaction();
  }

  //////////////////////////////////////////////////////
  //
  //  16 bit test  0xF399 = 1111 0011 1001 1001
  //               0x137F = 0001 0011 0111 1111

  Serial.println("\nMODE 0");
  {
    myspi.beginTransaction(LSBFIRST, 0);
    digitalWrite(selectPin, LOW);
    Serial.println(myspi.transfer16(0xF399), HEX);
    digitalWrite(selectPin, HIGH);
    myspi.endTransaction();
  }

  Serial.println("\nMODE 1");
  {
    myspi.beginTransaction(LSBFIRST, 1);
    digitalWrite(selectPin, LOW);
    Serial.println(myspi.transfer16(0xF399), HEX);
    digitalWrite(selectPin, HIGH);
    myspi.endTransaction();
  }

  Serial.println("\nMODE 2");
  {
    myspi.beginTransaction(LSBFIRST, 2);
    digitalWrite(selectPin, LOW);
    Serial.println(myspi.transfer16(0xF399), HEX);
    digitalWrite(selectPin, HIGH);
    myspi.endTransaction();
  }

  Serial.println("\nMODE 3");
  {
    myspi.beginTransaction(LSBFIRST, 3);
    digitalWrite(selectPin, LOW);
    Serial.println(myspi.transfer16(0xF399), HEX);
    digitalWrite(selectPin, HIGH);
    myspi.endTransaction();
  }

}


void loop()
{
}


//  -- END OF FILE --
