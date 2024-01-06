//
//    FILE: print_sci.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo program SCI
//     URL: https://github.com/RobTillaart/printHelpers


#include "printHelpers.h"


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PRINTHELPERS_VERSION: ");
  Serial.println(PRINTHELPERS_VERSION);
  Serial.println();

  Serial.println(sizeof(float));
  Serial.println(sizeof(double));


  double c = 2.99792458E8;   //  speed of light;
  double m = 7.34767309E20;  //  mass of moon
  double E = m * c * c;

  Serial.println();
  Serial.println("     Mass moon M = 7.34767309E+20");
  Serial.println("Speed of light c = 2.99792458E+8");
  Serial.println("         Print E = Mc^2 = 6.6037592413026551656653076E+37 \n");

  Serial.print(" normal print:\t");
  Serial.println(E, 4);
  Serial.println("Cannot handle floats / doubles > MAXLONG\n");


#if defined(ARDUINO_ARCH_AVR)
  char buffer[200];
  Serial.print("dtostrf print:\t");
  Serial.println(dtostrf(E, 4, 4, buffer));
  Serial.println("Has no scientific notation\n");

  Serial.print("dtostre print:\t");
  Serial.println(dtostre(E, buffer, 4, 0 ));
  Serial.print("dtostre print:\t");
  Serial.println(dtostre(E, buffer, 16, 0 ));
  Serial.println("Limited to 7 decimals\n");
#endif


  Serial.print("    sci print:\t");
  Serial.println(sci(E, 4));
  Serial.print("    sci print:\t");
  Serial.println(sci(E, 16));
  Serial.println("limited only by precision float\n");


  Serial.print("    eng print:\t");
  Serial.println(eng(E, 4));
  Serial.print("    eng print:\t");
  Serial.println(eng(E, 16));
  Serial.println("limited only by precision float\n");


  E /= 100; // more interesting effect
  Serial.println("scieng() is not meant to use directly");
  Serial.println("it works well up exponent multiple of 1..9");
  Serial.println("some values for em have their esthetics too.\n");
  for (int em = 1; em < 10; em++)
  {
    Serial.print(em);
    Serial.print("\t");
    Serial.println(scieng(E, 8, em));
  }
  Serial.println();
  
  if (sizeof(double) == 8)
  {
    while (E < 1e308)
    {
      E *= 1e5;
      Serial.println(sci(E, 16));
    }
  }

  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --

