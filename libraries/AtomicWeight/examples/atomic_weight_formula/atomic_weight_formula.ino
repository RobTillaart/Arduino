//    FILE: atomic_weight_formula.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/AtomicWeight

#include "Arduino.h"
#include "AtomicWeight.h"


PTOE ptoe;

char formula1[24] = "C6H6O6";
char formula2[24] = "H2SO4";
char formula3[24] = "HHSOOOO";

void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);
  Serial.print("ATOMIC_WEIGHT_LIB_VERSION: ");
  Serial.println(ATOMIC_WEIGHT_LIB_VERSION);

  Serial.print("C");
  Serial.print(" \t");
  Serial.println(ptoe.weight("C"));

  Serial.print("C6");
  Serial.print(" \t");
  Serial.println(ptoe.weight("C6"));

  Serial.print("He6");
  Serial.print(" \t");
  Serial.println(ptoe.weight("He6"));

  Serial.print("O6");
  Serial.print(" \t");
  Serial.println(ptoe.weight("O6"));

  Serial.print(formula1);
  Serial.print(" \t");
  Serial.println(ptoe.weight(formula1));

  Serial.print(formula2);
  Serial.print(" \t");
  Serial.println(ptoe.weight(formula2));

  Serial.print(formula3);
  Serial.print(" \t");
  Serial.println(ptoe.weight(formula3));
}

void loop()
{
}


// -- END OF FILE --
