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
  while (!Serial); //  uncomment if needed
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("LOGIC_LIB_VERSION: ");
  Serial.println(LOGIC_LIB_VERSION);
  Serial.println();

  LGC.setTable(-1);
  Serial.println(LGC.getTable(), HEX);
  delay(1000);

  //  fill the truth table.
  LGC.setTable(0x68);  //  (1 << 3 + 1 << 5 + 1 << 6)
  Serial.println(LGC.getTable(), HEX);
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
  Serial.print(LGC.neval(a, b, c));
  Serial.print("\t");

  switch (LGC.neval(a, b, c))
  {
    case 3:  //  handle case 110
      Serial.println("Y");
      break;
    case 5:  //  handle case 101
      Serial.println("YY");
      break;
    case 6:  //  handle case 011
      Serial.println("YYY");
      break;
    default:  // handle other cases
      Serial.println("nop");
      break;
  }
  delay(100);

}


//  -- END OF FILE --
