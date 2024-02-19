//
//    FILE: LineFormatter_test_table.ino
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

  L.printRuler(80);

  for (int i = 0; i < 5; i++)
  {
    L.println("\ta\ta\ta\ta");
  }
  L.repeat(2, '\n');


  L.clearTabs();
  for (int pos = 1; pos < 80; pos += 8)
  {
    if (L.addTab(pos) == false)
    {
      Serial.println("tabstop array == full or pos == 0");
    }
  }
  L.print("TabCount:\t");
  L.println(L.getTabCount());
  L.printRuler(80);

  for (int i = 0; i < 5; i++)
  {
    L.println("\ta\ta\ta\ta");
  }
  L.repeat(2, '\n');

  for (int pos = 1; pos < 80; pos += 16)
  {
    if (L.removeTab(pos) == false)
    {
      Serial.print("error: ");
      Serial.println(pos);
    }
  }
  L.print("TabCount:\t");
  L.println(L.getTabCount());
  L.printRuler(80);

  for (int i = 0; i < 5; i++)
  {
    L.println("\ta\ta\ta\ta");
  }
  L.repeat(2, '\n');


  L.println("Done...");
}


void loop()
{
}


//  -- END OF FILE --
