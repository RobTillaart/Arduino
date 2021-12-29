//
//    FILE: XMLWriterPrint_3.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo Print interface - Printable data types
//    DATE: 2020-07-07
//     URL: https://github.com/RobTillaart/XMLWriter
//
//  example works for UNO but does not compile for ESP, 
//  to investigate [complex vs Complex]


#include <XMLWriter.h>
#include <Complex.h>   // https://github.com/RobTillaart/Complex

XMLWriter XML(&Serial);

Complex c(3, 5);

char buffer[24];


void setup()
{
  Serial.begin(115200);
  XML.setConfig(XMLWRITER_COMMENT | XMLWRITER_INDENT);
  XML.header();
  XML.comment("XMLWriter Print interface - Printable interface");
  XML.tagOpen("P");
  XML.tagOpen("Complex");
  XML.indent();
  XML.println(c);
  XML.tagClose();
  XML.tagOpen("Complex");
  XML.indent();
  XML.println(c.c_sqrt());
  XML.tagClose();
  XML.tagClose();
  XML.flush();
}


void loop()
{
}


// -- END OF FILE --

