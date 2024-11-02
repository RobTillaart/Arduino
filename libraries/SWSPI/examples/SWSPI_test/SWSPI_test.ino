//
//    FILE: SWSPI_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test
//     URL: https://github.com/RobTillaart/SWSPI

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
    myspi.transfer("hello", 5);
    digitalWrite(selectPin, HIGH);
    myspi.endTransaction();
  }

  Serial.println("\nMODE 1");
  {
    myspi.beginTransaction(LSBFIRST, 1);
    digitalWrite(selectPin, LOW);
    myspi.transfer("hello", 5);
    digitalWrite(selectPin, HIGH);
    myspi.endTransaction();
  }

  Serial.println("\nMODE 2");
  {
    myspi.beginTransaction(LSBFIRST, 2);
    digitalWrite(selectPin, LOW);
    myspi.transfer("hello", 5);
    digitalWrite(selectPin, HIGH);
    myspi.endTransaction();
  }

  Serial.println("\nMODE 3");
  {
    myspi.beginTransaction(LSBFIRST, 3);
    digitalWrite(selectPin, LOW);
    myspi.transfer("hello", 5);
    digitalWrite(selectPin, HIGH);
    myspi.endTransaction();
  }

}


void loop()
{
}


//  -- END OF FILE --
