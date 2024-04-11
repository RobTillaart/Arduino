//
//    FILE: printString.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo experimental
//     URL: https://github.com/RobTillaart/PrintString


#include "PrintString.h"
#include "XMLWriter.h"      //  https://github.com/RobTillaart/XMLWriter

PrintString ps;
XMLWriter XML(&ps);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  ps.println("Hello World");
  ps.println(3.14159265, 4);
  Serial.println(ps.getString());

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

  Serial.println(ps.getString());
  
  Serial.println("done...");
}


void loop()
{
}


//  -- END OF FILE --

