//
//    FILE: ParPrinter_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2020-05-26


#include "ParallelPrinter.h"

ParallelPrinter PP;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  PP.begin();
  test1();
  test2();
  test3();
  Serial.println("\ndone...");
}


void loop()
{
}


void test1()
{
  Serial.println(__FUNCTION__);
  PP.formfeed();
  for (int i = 0; i < 10; i++) PP.println("Hello World");
  delay(100);
}


void test2()
{
  Serial.println(__FUNCTION__);
  PP.setLineFeed(3);
  PP.formfeed();
  for (int i = 0; i < 30; i++) PP.println("Hello World");
  delay(100);
}


void test3()
{
  Serial.println(__FUNCTION__);
  PP.setLineFeed(2);
  PP.formfeed();

  //PP.setTabSize(0);
  PP.printLineNumber(true);
  for (int i = 0; i < 100; i++) PP.print("Hello World ");
  PP.printLineNumber(false);
  for (int i = 0; i < 100; i++) PP.print("Hello World ");

  PP.setTabSize(4);
  PP.printLineNumber(true);
  for (int i = 0; i < 100; i++) PP.print("Hello World ");
  PP.printLineNumber(false);
  for (int i = 0; i < 100; i++) PP.print("Hello World ");

  PP.setTabSize(6);
  PP.printLineNumber(true);
  for (int i = 0; i < 300; i++) PP.print("Hello World ");
  PP.printLineNumber(false);
  for (int i = 0; i < 100; i++) PP.print("Hello World ");

  PP.setTabSize(8);
  PP.printLineNumber(true);
  for (int i = 0; i < 100; i++) PP.print("Hello World ");
  PP.printLineNumber(false);
  for (int i = 0; i < 100; i++) PP.print("Hello World ");

  delay(100);
}


// -- END OF FILE --

