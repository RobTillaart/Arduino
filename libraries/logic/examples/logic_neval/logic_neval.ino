//
//    FILE: logic_neval.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour 
//     URL: https://github.com/RobTillaart/logic
//
//  in this sketch there are three conditions and 
//  there are two out of 8 combinations that need action.
//  The neval() function converts the bools to the index of the truth table
//  which can be used in a switch() statement.
 

#include "logic.h"

logic LGC;


void setup()
{
  //  while(!Serial);  //  uncomment if needed
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("LOGIC_LIB_VERSION: ");
  Serial.println(LOGIC_LIB_VERSION);
  Serial.println();

  //  fill the truth table.
  LGC.setTable(0x18);  //  ((1 << 4) | (1 << 5))
}


void loop()
{
  //  evaluate your three base conditions (simulated by random)
  bool a = random(2);
  bool b = random(2);
  bool c = random(2);

  //  print the case under test
  Serial.print(a);
  Serial.print(b);
  Serial.print(c);
  Serial.print("\t");
  
  switch (LGC.neval(a, b, c))
  {
    case 4:  //  handle case 100
      Serial.println("Y");
      break;
    case 5:  //  handle case 101
      Serial.println("YY");
      break;
    default:  // handle other cases
      Serial.println("nop");
      break;
  }
  delay(1000);

}


//  -- END OF FILE --
