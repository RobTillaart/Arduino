//
//    FILE: XMLWriterPrint_4.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo Print interface - PROGMEM strings
//    DATE: 2020-07-07
//     URL: https://github.com/RobTillaart/XMLWriter


#include <XMLWriter.h>

XMLWriter XML(&Serial);

#define NUMBERZ           (F("1.2.3.4.5"))


void setup()
{
  Serial.begin(115200);
  XML.setConfig(XMLWRITER_COMMENT | XMLWRITER_INDENT);
  XML.header();
  XML.comment("XMLWriter Print interface - PROGMEM F macro");
  XML.tagOpen("P");
  XML.tagOpen("F Macro");
  XML.indent();
  XML.println(F("string from PROGMEM"));
  XML.tagClose();
  XML.tagOpen("F Macro");
  XML.indent();
  XML.println(NUMBERZ);
  XML.tagClose();
  XML.tagClose();
  XML.flush();
}


void loop()
{
}


// -- END OF FILE --

