//
//    FILE: XMLWriterSting.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/PrintString
//     URL: https://github.com/RobTillaart/XMLWriter


#include "PrintString.h"
#include "XMLWriter.h"      // https://github.com/RobTillaart/XMLWriter

PrintString ps;
XMLWriter XML(&ps);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PRINTSTRING_VERSION:\t");
  Serial.println(PRINTSTRING_VERSION);
  Serial.print("XMLWRITER_VERSION:\t");
  Serial.println(XMLWRITER_VERSION);

  ps.println("Hello World");
  ps.println(3.14159265, 4);
  String s1 = ps.getString();
  Serial.println(s1);

  ps.clear();
  ps.println(3.14159265, 4);
  ps.println("Hello World");
  Serial.println(ps.getString());

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

  String s2 = ps.getString();
  Serial.println(s2);
  
  Serial.println("done...");
}


void loop()
{
}


//  -- END OF FILE --
