//
//    FILE: XMLWriterPrint_1.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo Print interface
//    DATE: 2020-07-07
//     URL: https://github.com/RobTillaart/XMLWriter


#include <XMLWriter.h>

XMLWriter XML(&Serial);

char buffer[24];


void setup()
{
  Serial.begin(115200);

  XML.newLine(0);
  XML.print("\n");
  XML.header();
  XML.comment("XMLWriter Print interface");
  XML.setConfig(0);  // no indent, no (further) comments

  //   The {} and indentations are not mandatory 
  //   however they shows the XML structure in the code...

  XML.tagOpen("Order");
  {

    XML.println();
    XML.tagOpen("Address stamp");
    {
      XML.println("Mr. D. Bowie\nSpiderstreet 42\n54321 Mars");
    }
    XML.tagClose();

    XML.println();

    XML.tagOpen("Actions");
    {
      XML.println("[ ] Two tickets for Central Park");
      XML.println("[ ] Diner at the Ritz");
      XML.println("[ ] Surprise Hotel");
    }
    XML.tagClose();
    XML.println();
  }
  XML.tagClose();
  XML.flush();
}


void loop()
{
}


// -- END OF FILE --

