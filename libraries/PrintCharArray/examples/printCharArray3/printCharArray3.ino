//
//    FILE: printCharArray3.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
// PURPOSE: demo with XML writer
//     URL: https://github.com/RobTillaart/PrintCharArray
//
//  HISTORY:
//  0.1.0   2017-12-09  initial version
//  0.1.1   2020-04-30  minor refactor
//  0.3.0   2021-01-06  free() -> available()

#include "PrintCharArray.h"

#include "XMLWriter.h"    //   https://github.com/RobTillaart/XMLWriter

PrintCharArray ps(250);
XMLWriter XML(&ps);

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  ps.clear();

  XML.header();
  XML.comment("Weather in Nebraska");
  XML.tagOpen("Data");
  XML.writeNode("Date", "20131106");
  XML.writeNode("Time", "11:42");
  XML.writeNode("Temp", "23.4");
  XML.writeNode("Humi", "50%");
  XML.writeNode("Rain", "10mm");
  XML.writeNode("Sun", "40");
  XML.tagClose();
  XML.flush();

  // write the XML generated in one call
  Serial.println(ps.getBuffer());
  Serial.println(ps.available());

}

void loop()
{

}

// -- END OF FILE --
