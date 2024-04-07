//    FILE: atomic_weight_massPercentage.ino
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
char formula6[24] = "xH2";         //  fails => 0;



void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);
  Serial.print("ATOMIC_WEIGHT_LIB_VERSION: ");
  Serial.println(ATOMIC_WEIGHT_LIB_VERSION);

  Serial.println("\nform.\telem.\tperc.\n");
  Serial.print("C");
  Serial.print(" \t C \t");
  Serial.println(ptoe.massPercentage("C", "C"));

  Serial.print("C6");
  Serial.print(" \t C \t");
  Serial.println(ptoe.massPercentage("C6", "C"));

  Serial.print("He6");
  Serial.print(" \t C \t");
  Serial.println(ptoe.massPercentage("He6", "C"));

  Serial.print("NaCl");
  Serial.print(" \t Na \t");
  Serial.println(ptoe.massPercentage("NaCl", "Na"));

  Serial.print("NaCl");
  Serial.print(" \t Cl \t");
  Serial.println(ptoe.massPercentage("NaCl", "Cl"));

  Serial.print(formula0);
  Serial.print(" \t H \t");
  Serial.println(ptoe.massPercentage(formula0, "H"));

  Serial.print(formula1);
  Serial.print(" \t H \t");
  Serial.println(ptoe.massPercentage(formula1, "H"));

  Serial.print(formula2);
  Serial.print(" \t H \t");;
  Serial.println(ptoe.massPercentage(formula2, "H"));

  Serial.print(formula3);
  Serial.print(" \t H \t");
  Serial.println(ptoe.massPercentage(formula3, "H"));

  Serial.print(formula4);
  Serial.print(" \t H \t");
  Serial.println(ptoe.massPercentage(formula4, "H"));

  Serial.print(formula5);
  Serial.print(" \t H \t");
  Serial.println(ptoe.massPercentage(formula5, "H"));

  Serial.print(formula6);
  Serial.print(" \t H \t");
  Serial.println(ptoe.massPercentage(formula6, "H"));

}


void loop()
{
}



//  -- END OF FILE --
