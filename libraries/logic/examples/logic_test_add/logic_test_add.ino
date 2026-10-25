//
//    FILE: logic_test_add.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test behaviour add() and remove()
//     URL: https://github.com/RobTillaart/logic


#include "logic.h"

logic LGC;


void setup()
{
  while(!Serial);
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("LOGIC_LIB_VERSION: ");
  Serial.println(LOGIC_LIB_VERSION);
  Serial.println();

  //  start with empty table
  LGC.setTable(0);

  //  add entries
  LGC.add(LGC.index(true, true));
  LGC.add(LGC.index(false, false, true));
  //  dump table
  Serial.print("\ntable: \t");
  Serial.println(LGC.getTable(), HEX);

  Serial.println("\nTEST AND");
  Serial.println(LGC.eval(0, 0));
  Serial.println(LGC.eval(0, 1));
  Serial.println(LGC.eval(1, 0));
  Serial.println(LGC.eval(1, 1));
  Serial.println(LGC.eval(0, 0, 1));
  Serial.println(LGC.eval(0, 1, 1));

  //  remove entry
  LGC.remove(LGC.index(true, true));
  // dumpt table
  Serial.print("\ntable: \t");
  Serial.println(LGC.getTable(), HEX);

  Serial.println("\nTEST REMOVE");
  Serial.println(LGC.eval(0, 0));
  Serial.println(LGC.eval(0, 1));
  Serial.println(LGC.eval(1, 0));
  Serial.println(LGC.eval(1, 1));
  Serial.println(LGC.eval(0, 0, 1));
  Serial.println(LGC.eval(0, 1, 1));

  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --
