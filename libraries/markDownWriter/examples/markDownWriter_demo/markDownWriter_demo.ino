//
//    FILE: markDownWriter_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/markDownWriter


#include "markDownWriter.h"


markDownWriter mdw(&Serial);  //  default Serial


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("MARKDOWNWRITER_LIB_VERSION: ");
  Serial.println(MARKDOWNWRITER_LIB_VERSION);
  Serial.println();

  mdw.reset();

  mdw.title("MARK DOWN WRITER");
  mdw.chapter("Introduction");
  mdw.println("Lorem ipsum ...");

  mdw.chapter("History");
  mdw.println("Long long time ago in a galaxy far away...");
  mdw.line();
  mdw.println("... tada");

  mdw.chapter("Test style");
  mdw.boldOn();
  mdw.print("this should be bold.");
  mdw.boldOff();
  mdw.italicOn();
  mdw.print("this should be italic.");
  mdw.italicOff();
  mdw.println();

  mdw.boldItalicOn();
  mdw.print("this should be italic and bold.");
  mdw.boldItalicOff();
  mdw.println();


  mdw.chapter("Test simple table");

  //  table headers
  char hdrs[][12] = { "X", "Y", "angle", "length", "color" };
  char align[] = { 'C', 'C', 'R', 'R', 'L' };
  mdw.tableHeader(5, hdrs, align);

  //  table values
  for (int i = 0; i < 7; i = i + 3)
  {
    float v[5];
    v[0] = i;
    v[1] = i * sqrt(i);
    v[2] = atan2(v[1], v[0]);
    v[3] = hypot(v[0], v[1]);
    v[4] = random(255);
    mdw.tableValues(v, 0);
  }
  //  2 decimals
  for (int i = 0; i < 7; i = i + 3)
  {
    float v[5];
    v[0] = i;
    v[1] = i * sqrt(i);
    v[2] = atan2(v[1], v[0]);
    v[3] = hypot(v[0], v[1]);
    v[4] = random(255);
    mdw.tableValues(v);
  }
  //  4 decimals
  for (int i = 0; i < 7; i = i + 3)
  {
    float v[5];
    v[0] = i;
    v[1] = i * sqrt(i);
    v[2] = atan2(v[1], v[0]);
    v[3] = hypot(v[0], v[1]);
    v[4] = random(255);
    mdw.tableValues(v, 4);
  }

  mdw.chapter("Test link");
  mdw.URL("Google", "http://www.google.com");
  mdw.println();
  mdw.println();
  mdw.link("http://www.google.com");

  mdw.flush();
}


void loop()
{
}


//  -- END OF FILE --
