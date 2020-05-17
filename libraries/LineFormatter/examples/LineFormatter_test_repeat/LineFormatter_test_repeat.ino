//
//    FILE: LineFormatter_test_repeat.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo LineFormatter class
//     URL: https://github.com/RobTillaart/LineFormatter
//
// HISTORY:
// 0.1.0   2020-05-14 initial version
//

#include "LineFormatter.h"

LineFormatter L;

void setup()
{
  Serial.begin(115200);
  L.println(__FILE__);

  L.println();
  L.println("Make a simple tabular output");
  L.repeat(3, "\n");  // 3 newlines

  test_repeat();
  test_graph();
  test_setMaxLength();

  L.println("Done...");
}

void loop()
{
}

///////////////////////////////////////////////////////////////////

void test_repeat()
{
  L.println();
  L.println(__FUNCTION__);
  L.repeat(strlen(__FUNCTION__), "=", 2); 

  L.repeat(10, ">");
  L.print(" REPEAT DEMO ");
  L.repeat(10, "<", 1);
  L.repeat(5, "----+----|", 1);
  L.repeat(5, "    +    +", 1);
  L.repeat(5, "    +    +", 1);
  L.repeat(5, "    +    +", 1);
  L.repeat(5, "    +    +", 1);
  L.repeat(5, "----+----|", 3);

  L.repeat(5, " 2 4 6 8 0", 2);
  L.repeat(20, "- + ", 1);

  L.repeat(3, '\n');
}

void test_graph()
{
  L.println();
  L.println(__FUNCTION__);
  L.repeat(strlen(__FUNCTION__), "=", 2); 


  for (int i = 0; i < 30; i++)
  {
    uint8_t n = 40 + 20 * sin(i * 0.3);
    L.repeat(n, ' ');
    L.println('*');
  }
  L.repeat(3, '\n');
}

void test_setMaxLength()
{
  L.println();
  L.println(__FUNCTION__);
  L.repeat(strlen(__FUNCTION__), "=", 2); 


  L.setMaxLength(20);
  L.print("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz");
  L.setMaxLength(0);
  L.repeat(3, '\n');
}


// -- END OF FILE --
