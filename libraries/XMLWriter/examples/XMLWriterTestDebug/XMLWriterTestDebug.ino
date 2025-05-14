//
//    FILE: XMLWriterTestDebug.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test debug() output
//     URL: https://github.com/RobTillaart/XMLWriter


#include <XMLWriter.h>

XMLWriter XML(&Serial);


void setup()
{
  Serial.begin(115200);

  XML.header();
  
  //  compile time constants into XML
  XML.comment(__DATE__);
  XML.comment(__TIME__);
  XML.comment(__FILE__);
  XML.comment(__FUNCTION__);

  XML.debug();
  XML.newLine();
  XML.debug();

  XML.flush();

  Serial.println("done...");
}


void loop()
{
}


//  -- END OF FILE --
