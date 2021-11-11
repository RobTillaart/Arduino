//
//    FILE: XMLWriterPrint_2.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
// PURPOSE: demo Print interface - use it to print "unsupported" and Printable data types 
//    DATE: 2020-07-07
//     URL: https://github.com/RobTillaart/XMLWriter
//


#include <XMLWriter.h>
#include <printHelpers.h>   // https://github.com/RobTillaart/printHelpers

XMLWriter XML(&Serial);

uint64_t big = 112233445566778899;
double   large = 5.46372819E30;

char buffer[24];


void setup()
{
  Serial.begin(115200);

  XML.setConfig(XMLWRITER_COMMENT | XMLWRITER_INDENT);
  XML.header();
  XML.comment("XMLWriter Print interface - to inject not supported datatypes");
  XML.tagOpen("unprintable");
  XML.tagOpen("uint64_t ");
  XML.indent();
  XML.println(print64(big));
  XML.tagClose();
  XML.tagOpen("scientific");
  XML.indent();
  XML.println(sci(large, 6));
  XML.tagClose();
  XML.tagClose();

  XML.flush();
}


void loop()
{
}


// -- END OF FILE --

