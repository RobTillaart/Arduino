//    FILE: atomic_weight_formula.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/AtomicWeight


#include "Arduino.h"
#include "AtomicWeight.h"


PTOE ptoe;

char formula0[24] = "C6H6O6";
char formula1[24] = "((COH)3)2";
char formula2[24] = "H2SO4";
char formula3[24] = "CuO2";
char formula4[24] = "(COH)3(COH)2COH";
char formula5[24] = "(CH)6O6";
char formula6[24] = "xH2";        //  fails => 0;
char formula7[24] = "(CuO2)0.25";
char formula8[24] = "(Mg0.4Fe1.6)2.0SiO4";   //  Olivine mineral


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

  Serial.print("NaCl");
  Serial.print(" \t");
  Serial.println(ptoe.weight("NaCl"));

  Serial.print(formula0);
  Serial.print(" \t");
  Serial.println(ptoe.weight(formula0));

  Serial.print(formula1);
  Serial.print(" \t");
  Serial.println(ptoe.weight(formula1));

  Serial.print(formula2);
  Serial.print(" \t");
  Serial.println(ptoe.weight(formula2));

  Serial.print(formula3);
  Serial.print(" \t");
  Serial.println(ptoe.weight(formula3));

  Serial.print(formula4);
  Serial.print(" \t");
  Serial.println(ptoe.weight(formula4));

  Serial.print(formula5);
  Serial.print(" \t");
  Serial.println(ptoe.weight(formula5));

  Serial.print(formula6);
  Serial.print(" \t");
  Serial.println(ptoe.weight(formula6));

  Serial.print(formula7);
  Serial.print(" \t");
  Serial.println(ptoe.weight(formula7));

  Serial.print(formula8);
  Serial.print(" \t");
  Serial.println(ptoe.weight(formula8));

  Serial.print("()");
  Serial.print(" \t");
  Serial.println(ptoe.weight("()"));

  Serial.print("(H2O)");
  Serial.print(" \t");
  Serial.println(ptoe.weight("(H2O)"));

  Serial.print("(H2O)255");
  Serial.print(" \t");
  Serial.println(ptoe.weight("(H2O)255"));

  Serial.print("(H2O)255.0");
  Serial.print(" \t");
  Serial.println(ptoe.weight("(H2O)255.0"));
}


void loop()
{
}


//  -- END OF FILE --

