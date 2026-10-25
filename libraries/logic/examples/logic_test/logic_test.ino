//
//    FILE: logic_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour
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

  LGC.setTable(0b1000);
  Serial.println("\nTEST AND");
  Serial.println(LGC.eval(0, 0));
  Serial.println(LGC.eval(0, 1));
  Serial.println(LGC.eval(1, 0));
  Serial.println(LGC.eval(1, 1));

  LGC.setTable(0b1110);
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

  LGC.setTable(0x68);  //  0b01101000
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

  //  note this table value is ~symmetric around middle
  LGC.setTable(0xFEE8E880);  //  0b1111 1110 1110 1000 1110 1000 1000 0000
  Serial.println("\nTEST 5 bit - at least 3 out of 5");
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

  /////////////////////////////////////////////
  //  last test as a loop
  LGC.setTable(0xFEE8E880);  //  0b1111 1110 1110 1000 1110 1000 1000 0000
  Serial.println("\nTEST 5 bit - at least 3 out of 5");
  for (int i = 0; i < 32; i++)
  {
    Serial.println(LGC.eval(i & 1, i & 2, i & 4, i & 8, i & 16));
  }

}


void loop()
{
}


//  -- END OF FILE --
