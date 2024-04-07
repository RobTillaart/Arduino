//    FILE: atomic_count_atomPercentage.ino
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
char formula6[24] = "xH2";           //  fails => 0;



void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);
  Serial.print("ATOMIC_WEIGHT_LIB_VERSION: ");
  Serial.println(ATOMIC_WEIGHT_LIB_VERSION);


  //  COUNT
  Serial.println(ptoe.count("C"));
  Serial.println(ptoe.count("C", "C"));
  Serial.println(ptoe.count("H2SO4"));
  Serial.println(ptoe.count("H2SO4", "C"));
  Serial.println(ptoe.count("H2SO4", "H"));
  Serial.println(ptoe.count("H2SO4", "S"));
  Serial.println(ptoe.count("H2SO4", "O"));


  //  PERCENTAGE
  Serial.println("\nform.\telem.\tperc.\n");
  Serial.print("C");
  Serial.print(" \t C \t");
  Serial.println(ptoe.atomPercentage("C", "C"));

  Serial.print("C6");
  Serial.print(" \t C \t");
  Serial.println(ptoe.atomPercentage("C6", "C"));

  Serial.print("He6");
  Serial.print(" \t C \t");
  Serial.println(ptoe.atomPercentage("He6", "C"));

  Serial.print("NaCl");
  Serial.print(" \t Na \t");
  Serial.println(ptoe.atomPercentage("NaCl", "Na"));

  Serial.print("NaCl");
  Serial.print(" \t Cl \t");
  Serial.println(ptoe.atomPercentage("NaCl", "Cl"));

  Serial.print(formula0);
  Serial.print(" \t H \t");
  Serial.println(ptoe.atomPercentage(formula0, "H"));

  Serial.print(formula1);
  Serial.print(" \t H \t");
  Serial.println(ptoe.atomPercentage(formula1, "H"));

  Serial.print(formula2);
  Serial.print(" \t H \t");;
  Serial.println(ptoe.atomPercentage(formula2, "H"));

  Serial.print(formula3);
  Serial.print(" \t H \t");
  Serial.println(ptoe.atomPercentage(formula3, "Cu"));

  Serial.print(formula3);
  Serial.print(" \t H \t");
  Serial.println(ptoe.atomPercentage(formula3, "O"));

  Serial.print(formula4);
  Serial.print(" \t H \t");
  Serial.println(ptoe.atomPercentage(formula4, "H"));

  Serial.print(formula5);
  Serial.print(" \t H \t");
  Serial.println(ptoe.atomPercentage(formula5, "O"));

  Serial.print(formula6);
  Serial.print(" \t H \t");
  Serial.println(ptoe.atomPercentage(formula6, "H"));

}


void loop()
{
}



//  -- END OF FILE --
