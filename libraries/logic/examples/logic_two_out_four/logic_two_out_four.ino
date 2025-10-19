//
//    FILE: logic_two_out_four.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/logic


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

  //  LGC.setTable(0b0001011001101000);
  LGC.setTable(0x1668);
  Serial.println("\nTEST exact two out of four (0x1668)");
  Serial.println(LGC.eval(0, 0, 0, 0)); 
  Serial.println(LGC.eval(0, 0, 0, 1));
  Serial.println(LGC.eval(0, 0, 1, 0));
  Serial.println(LGC.eval(0, 0, 1, 1));
  Serial.println(LGC.eval(0, 1, 0, 0));
  Serial.println(LGC.eval(0, 1, 0, 1));
  Serial.println(LGC.eval(0, 1, 1, 0));
  Serial.println(LGC.eval(0, 1, 1, 1));
  Serial.println(LGC.eval(1, 0, 0, 0));
  Serial.println(LGC.eval(1, 0, 0, 1));
  Serial.println(LGC.eval(1, 0, 1, 0));
  Serial.println(LGC.eval(1, 0, 1, 1));
  Serial.println(LGC.eval(1, 1, 0, 0));
  Serial.println(LGC.eval(1, 1, 0, 1));
  Serial.println(LGC.eval(1, 1, 1, 0));
  Serial.println(LGC.eval(1, 1, 1, 1));

  //  LGC.setTable(0b1111111011101000);
  LGC.setTable(0xFEE8);
  Serial.println("\nTEST at least two out of four (0xFEE8)");
  Serial.println(LGC.eval(0, 0, 0, 0)); 
  Serial.println(LGC.eval(0, 0, 0, 1));
  Serial.println(LGC.eval(0, 0, 1, 0));
  Serial.println(LGC.eval(0, 0, 1, 1));
  Serial.println(LGC.eval(0, 1, 0, 0));
  Serial.println(LGC.eval(0, 1, 0, 1));
  Serial.println(LGC.eval(0, 1, 1, 0));
  Serial.println(LGC.eval(0, 1, 1, 1));
  Serial.println(LGC.eval(1, 0, 0, 0));
  Serial.println(LGC.eval(1, 0, 0, 1));
  Serial.println(LGC.eval(1, 0, 1, 0));
  Serial.println(LGC.eval(1, 0, 1, 1));
  Serial.println(LGC.eval(1, 1, 0, 0));
  Serial.println(LGC.eval(1, 1, 0, 1));
  Serial.println(LGC.eval(1, 1, 1, 0));
  Serial.println(LGC.eval(1, 1, 1, 1));
}


void loop()
{
}


//  -- END OF FILE --
