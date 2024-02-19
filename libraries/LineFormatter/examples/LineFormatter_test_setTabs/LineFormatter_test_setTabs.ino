//
//    FILE: LineFormatter_test_setTabs.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo LineFormatter class
//     URL: https://github.com/RobTillaart/LineFormatter


#include "LineFormatter.h"

LineFormatter L;


void setup()
{
  Serial.begin(115200);
  L.println();
  L.println(__FILE__);
  L.print("LINEFORMATTER_LIB_VERSION: ");
  L.println(LINEFORMATTER_LIB_VERSION);
  L.repeat(3, '\n');

  test_table_1();
  test_ruler();

  L.clearTabs();
  L.addTab(15);
  L.print("LineCount:\t");
  L.println(L.getLineCount());
  L.print("TabCount:\t");
  L.println(L.getTabCount());
  L.repeat(2, '\n');

  L.println("Done...");
}


void loop()
{
}


void test_ruler()
{
  L.println();
  L.println(__FUNCTION__);
  L.repeat(strlen(__FUNCTION__), "=", 2);

  uint8_t myTabs[9] = {3, 10, 12, 30, 36, 42, 52, 58, 64};
  L.setTabs(myTabs, 9);

  L.printRuler(100);
  L.clearTabs();
  L.printRuler(100);

  L.repeat(3, '\n');
}


void test_table_1()
{
  L.println();
  L.println(__FUNCTION__);
  L.repeat(strlen(__FUNCTION__), "=", 2);

  //  SET TABS ALL AT ONCE
  uint8_t myTabs[9] = {3, 10, 20, 30, 36, 42, 52, 58, 64};
  L.setTabs(myTabs, 9);
  
  //  HEADER
  L.println("\tIdx\tTime\tValue\tA0\tA1\tA2\tA3\tA4\tA5");
  L.repeat(8, "----+----|", 1);
  
  //  add empty line every 5 lines
  L.setAutoNewLine(5);

  //  DUMP THE DATA
  int measurement = 1;
  for (int i = 0; i < 20; i++)
  {
    if (i == 10)
    {
      L.println("switch to normal tab behaviour");
      L.clearTabs();   // just to show diff
    }

    L.tab();
    L.print(measurement++);
    L.tab();
    L.print(millis());
    L.tab();
    L.print(random(12345));
    L.tab();
    L.print(analogRead(A0));
    L.tab();
    L.print(analogRead(A1));
    L.tab();
    L.print(analogRead(A2));
    L.tab();
    L.print(analogRead(A3));
    L.tab();
    L.print(analogRead(A4));
    L.tab();
    L.print(analogRead(A5));
    L.println();
    delay(random(100));
  }
  L.setAutoNewLine(0);

  L.repeat(3, '\n');
}

//  -- END OF FILE --
