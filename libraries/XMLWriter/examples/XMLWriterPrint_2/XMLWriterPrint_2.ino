//
//    FILE: XMLWriterPrint_2.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo Print interface - use it to print "unsupported" and Printable data types
//     URL: https://github.com/RobTillaart/XMLWriter
//


#include <XMLWriter.h>
#include <printHelpers.h>   //  https://github.com/RobTillaart/printHelpers

XMLWriter XML(&Serial);

uint64_t big = 112233445566778899;
double   large = 5.46372819E30;

char buffer[24];


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("XMLWRITER_LIB_VERSION: ");
  Serial.println(XMLWRITER_LIB_VERSION);
  Serial.println();

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


//  -- END OF FILE --

