//
//    FILE: LineFormatter_test_getTabs.ino
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

  uint8_t myTabs[10] = {8, 16, 24, 32, 40, 48, 56, 64, 72, 80};
  L.setTabs(myTabs, 10);
  print_table();

  int size = L.getTabs(myTabs);

  L.println();
  L.print("shift 4 places to right");
  L.println();
  
  for (int i = 0; i < size; i++) myTabs[i] += 4;
  L.setTabs(myTabs, 10);
  print_table();

  L.println("Done...");
}


void loop()
{
}


void print_table()
{
  //  HEADER
  L.println("\tIdx\tTime\tValue\tA0\tA1\tA2\tA3\tA4\tA5");
  L.repeat(10, "----+----|", 1);

  //  add empty line every 5 lines
  L.setAutoNewLine(5);

  //  DUMP THE DATA
  int measurement = 1;
  for (int i = 0; i < 10; i++)
  {
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

  L.repeat(2, '\n');
}

//  -- END OF FILE --
