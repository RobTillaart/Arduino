//
//    FILE: PP595_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo IO based upon 74HC595 for data pins.
//     URL: https://github.com/RobTillaart/ParallelPrinter


#include "ParallelPrinter.h"

//  IO PINS FOR PRINTER
uint8_t strobe = 13;
uint8_t busy = 2;
uint8_t oop = 12;
//  74HC595 specific pins
uint8_t data = 8;
uint8_t latch = 9;
uint8_t clk = 10;


PP595 PP(strobe, busy, oop, data, latch, clk);

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.println("PARALLELPRINTER_VERSION: ");
  Serial.println(PARALLELPRINTER_VERSION);
  Serial.println();


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
  PP.formFeed();
  for (int i = 0; i < 10; i++) PP.println("Hello World");
  delay(100);
}


void test2()
{
  Serial.println(__FUNCTION__);
  PP.setLineFeed(3);
  PP.formFeed();
  for (int i = 0; i < 30; i++) PP.println("Hello World");
  delay(100);
}


void test3()
{
  Serial.println(__FUNCTION__);
  PP.setLineFeed(2);
  PP.formFeed();

  //  PP.setTabSize(0);
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


//  -- END OF FILE --
