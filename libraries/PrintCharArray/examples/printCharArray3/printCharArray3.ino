//
//    FILE: printCharArray3.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo with XML writer
//     URL: https://github.com/RobTillaart/PrintCharArray
//          https://github.com/RobTillaart/XMLWriter


#include "PrintCharArray.h"

#include "XMLWriter.h"          //  https://github.com/RobTillaart/XMLWriter

PrintCharArray ps(250);
XMLWriter XML(&ps);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PRINTCHARARRAY_VERSION: ");
  Serial.println(PRINTCHARARRAY_VERSION);
  Serial.println();

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

  //  write the XML generated in one call
  Serial.println(ps.getBuffer());
  Serial.println(ps.available());
}


void loop()
{
}


//  -- END OF FILE --

