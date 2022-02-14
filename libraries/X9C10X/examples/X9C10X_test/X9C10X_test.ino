//
//    FILE: X9C10X_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo


#include "Arduino.h"
#include "X9C10X.h"

X9C10X pot(12345);  //  100KΩ  (ALT-234)

void setup()
{
  Serial.begin(115200);
  while (!Serial);

  Serial.println();
  Serial.print("X9C10X_LIB_VERSION: ");
  Serial.println(X9C10X_LIB_VERSION);

  pot.begin(8, 9, 10, 0);  // pulse, direction, select, position

  Serial.print("POS:\t0\t");
  Serial.println(pot.getPosition());
  Serial.print("VAL:\t\t");
  Serial.print(pot.getOhm());
  Serial.println(" Ω");
  Serial.println();

  pot.setPosition(50);
  Serial.print("POS:\t50\t");
  Serial.println(pot.getPosition());
  Serial.print("VAL:\t\t");
  Serial.print(pot.getOhm());
  Serial.println(" Ω");
  Serial.println();

  pot.setPosition(110);
  Serial.print("POS:\t110\t");
  Serial.println(pot.getPosition());
  Serial.print("VAL:\t\t");
  Serial.print(pot.getOhm());
  Serial.println(" Ω");
  Serial.print("OHM:\t\t");
  Serial.print(pot.getMaxOhm());
  Serial.println(" Ω");
  Serial.println();

  pot.setPosition(0);
  Serial.print("POS:\t0\t");
  Serial.println(pot.getPosition());
  Serial.print("VAL:\t\t");
  Serial.print(pot.getOhm());
  Serial.println(" Ω");
  Serial.print("OHM:\t\t");
  Serial.print(pot.getMaxOhm());
  Serial.println(" Ω");
  Serial.println();

  for (uint8_t i = 0; i < 100; i++)
  {
    pot.incr();
    Serial.print(i);
    Serial.print("\t");
    Serial.print(pot.getPosition());
    Serial.print("\t");
    Serial.println(pot.getOhm());
  }
  Serial.println();

  for (uint8_t i = 0; i < 100; i++)
  {
    pot.decr();
    Serial.print(i);
    Serial.print("\t");
    Serial.print(pot.getPosition());
    Serial.print("\t");
    Serial.println(pot.getOhm());
  }
  Serial.println();

}


void loop()
{
}


// -- END OF FILE --
