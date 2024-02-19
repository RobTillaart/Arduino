//
//    FILE: LineFormatter_SDcard.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo LineFormatter for SDcard
//     URL: https://github.com/RobTillaart/LineFormatter


#include "SPI.h"
#include "SD.h"

//  SPI     PINS UNO
//  MOSI     11
//  MISO     12
//  CLOCK    13
//  CS       10

#define CS          10      //  adjust this ChipSelect line if needed !

#include "LineFormatter.h"


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("LINEFORMATTER_LIB_VERSION: ");
  Serial.println(LINEFORMATTER_LIB_VERSION);
  Serial.println();

  //  initialize the SD card
  if (!SD.begin(CS))
  {
    Serial.println("Error: SD card failure");
    while (1);
  }

  //  remove file for proper timing
  SD.remove("data.txt");
  delay(1000);

  File logfile = SD.open("data.txt", FILE_WRITE);
  if (!logfile)
  {
    Serial.println("Error: SD card failure");
    while (1);
  }

  LineFormatter LF(&logfile);
  test_table(&LF);
  logfile.close();

  Serial.println("\nDone...");
}


void loop()
{
}


void test_table(LineFormatter L)
{
  L.println();
  L.println(__FUNCTION__);
  L.repeat(strlen(__FUNCTION__), "=", 2);

  L.clearTabs();
  L.addTab(3);
  L.addTab(10);
  L.addTab(20);
  L.addTab(30);
  L.addRelTab(6);
  L.addRelTab(6);
  L.addRelTab(10);
  L.addRelTab(6);
  L.addRelTab(6);
  //  L.println(L.getTabCount());

  int measurement = 1;

  L.println("\tIdx\tTime\tValue\tA0\tA1\tA2\tA3\tA4\tA5");
  L.repeat(7, "----+----|", 1);

  L.setAutoNewLine(5);
  for (int i = 0; i < 100; i++)
  {
    Serial.print('.');
    if (i && (i % 20 == 0)) Serial.println();

    L.tab();
    L.print(measurement++);
    if (i % 5 == 0)
    {
      L.tab();
      L.print(millis());
      L.tab();
      L.print(random(12345));
    }
    else
    {
      L.tab(2);
    }
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
  }
  L.repeat(7, "----+----|", 1);
  L.setAutoNewLine(0);

  L.repeat(3, '\n');
}


//  -- END OF FILE --
