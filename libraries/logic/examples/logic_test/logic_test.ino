//
//    FILE: logic_test.ino
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

  LGC.setTable(0b0001);
  Serial.println("\nTEST AND");
  Serial.println(LGC.eval(0, 0));
  Serial.println(LGC.eval(0, 1));
  Serial.println(LGC.eval(1, 0));
  Serial.println(LGC.eval(1, 1));

  LGC.setTable(0b0111);
  Serial.println("\nTEST OR");
  Serial.println(LGC.eval(0, 0));
  Serial.println(LGC.eval(0, 1));
  Serial.println(LGC.eval(1, 0));
  Serial.println(LGC.eval(1, 1));

  LGC.setTable(0b0110);
  Serial.println("\nTEST XOR");
  Serial.println(LGC.eval(0, 0));
  Serial.println(LGC.eval(0, 1));
  Serial.println(LGC.eval(1, 0));
  Serial.println(LGC.eval(1, 1));

  LGC.setTable(0x18);
  Serial.println("\nTEST 3 bit");
  Serial.println(LGC.eval(0, 0, 0));
  Serial.println(LGC.eval(0, 0, 1));
  Serial.println(LGC.eval(0, 1, 0));
  Serial.println(LGC.eval(0, 1, 1));
  Serial.println(LGC.eval(1, 0, 0));
  Serial.println(LGC.eval(1, 0, 1));
  Serial.println(LGC.eval(1, 1, 0));
  Serial.println(LGC.eval(1, 1, 1));

  LGC.setTable(0xF05AC001);
  Serial.println("\nTEST 5 bit");
  Serial.println(LGC.eval(0, 0, 0, 0, 0));
  Serial.println(LGC.eval(0, 0, 0, 0, 1));
  Serial.println(LGC.eval(0, 0, 0, 1, 0));
  Serial.println(LGC.eval(0, 0, 0, 1, 1));
  Serial.println(LGC.eval(0, 0, 1, 0, 0));
  Serial.println(LGC.eval(0, 0, 1, 0, 1));
  Serial.println(LGC.eval(0, 0, 1, 1, 0));
  Serial.println(LGC.eval(0, 0, 1, 1, 1));
  Serial.println(LGC.eval(0, 1, 0, 0, 0));
  Serial.println(LGC.eval(0, 1, 0, 0, 1));
  Serial.println(LGC.eval(0, 1, 0, 1, 0));
  Serial.println(LGC.eval(0, 1, 0, 1, 1));
  Serial.println(LGC.eval(0, 1, 1, 0, 0));
  Serial.println(LGC.eval(0, 1, 1, 0, 1));
  Serial.println(LGC.eval(0, 1, 1, 1, 0));
  Serial.println(LGC.eval(0, 1, 1, 1, 1));
  Serial.println(LGC.eval(1, 0, 0, 0, 0));
  Serial.println(LGC.eval(1, 0, 0, 0, 1));
  Serial.println(LGC.eval(1, 0, 0, 1, 0));
  Serial.println(LGC.eval(1, 0, 0, 1, 1));
  Serial.println(LGC.eval(1, 0, 1, 0, 0));
  Serial.println(LGC.eval(1, 0, 1, 0, 1));
  Serial.println(LGC.eval(1, 0, 1, 1, 0));
  Serial.println(LGC.eval(1, 0, 1, 1, 1));
  Serial.println(LGC.eval(1, 1, 0, 0, 0));
  Serial.println(LGC.eval(1, 1, 0, 0, 1));
  Serial.println(LGC.eval(1, 1, 0, 1, 0));
  Serial.println(LGC.eval(1, 1, 0, 1, 1));
  Serial.println(LGC.eval(1, 1, 1, 0, 0));
  Serial.println(LGC.eval(1, 1, 1, 0, 1));
  Serial.println(LGC.eval(1, 1, 1, 1, 0));
  Serial.println(LGC.eval(1, 1, 1, 1, 1));
  
}


void loop()
{
}


//  -- END OF FILE --
