//
//    FILE: GPXWriterTest.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: simple GPX writer
//     URL: https://github.com/RobTillaart/XMLWriter


#include <XMLWriter.h>

XMLWriter GPX(&Serial);

char buffer[24];


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("XMLWRITER_LIB_VERSION: ");
  Serial.println(XMLWRITER_LIB_VERSION);
  Serial.println();

  uint32_t start = micros();
  GPXTest();
  uint32_t stop = micros();
  Serial.println();
  Serial.println(stop - start);
}


void loop()
{
}


//  redo https://en.wikipedia.org/wiki/GPS_Exchange_Format example
void GPXTest()
{
  GPX.setIndentSize(3);  //  odd indents are possible, 3 is nice!

  GPX.header();
  GPX.comment("GPXWriterTest.ino\nThis is a demo of the XMLWriter lib for Arduino", MULTILINE); // == true (default == false)

  GPX.tagStart("gpx");
  {
    GPX.tagField("xmlns", "http://www.topografix.com/GPX/1/1");
    GPX.tagField("version", "1.1");
    GPX.tagField("creator", "Wikipedia");
    GPX.newLine();
    GPX.tagField("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
    GPX.newLine();
    GPX.tagField("xsi:schemaLocation", "http://www.topografix.com/GPX/1/1 http://www.topografix.com/GPX/1/1/gpx.xsd");
  }
  GPX.incrIndent();
  {
    GPX.tagEnd(NEWLINE, NOSLASH);
    {
      GPX.comment("Comments look like this");
      GPX.tagOpen("metadata");
      {
        GPX.writeNode("name", "Data name");
        GPX.writeNode("desc", "Valid GPX example without special characters");
        GPX.tagOpen("author");
        {
          GPX.writeNode("name", "Author name");
        }
        GPX.tagClose();
      }
      GPX.tagClose();


      GPX.tagStart("wpt");
      {
        GPX.tagField("lat", "52.518611");
        GPX.tagField("lon", "13.376111");
      }
      GPX.tagEnd(NEWLINE, NOSLASH);
      GPX.incrIndent();
      {
        GPX.writeNode("ele", "35.0");
        GPX.writeNode("time", "2011-12-31T23:59:59Z");
        GPX.writeNode("name", "Reichstag (Berlin)");
        GPX.writeNode("sym", "City");
      }
      GPX.decrIndent();
      GPX.tagStart("/wpt");
      GPX.tagEnd(NEWLINE, NOSLASH);


      GPX.tagStart("wpt");
      {
        GPX.tagField("lat", "48.208031");
        GPX.tagField("lon", "16.358128");
      }
      GPX.tagEnd(NEWLINE, NOSLASH);
      GPX.incrIndent();
      {
        GPX.writeNode("ele", "179");
        GPX.writeNode("time", "2011-12-31T23:59:59Z");
        GPX.writeNode("name", "Parlament (Wien)");
        GPX.writeNode("sym", "City");
      }
      GPX.decrIndent();
      GPX.tagStart("/wpt");
      GPX.tagEnd(NEWLINE, NOSLASH);

      GPX.tagStart("wpt");
      {
        GPX.tagField("lat", "46.9466");
        GPX.tagField("lon", "7.44412");
      }
      GPX.tagEnd(NEWLINE, NOSLASH);
      GPX.incrIndent();
      {
        GPX.writeNode("ele", "179");
        GPX.writeNode("time", "2011-12-31T23:59:59Z");
        GPX.writeNode("name", "Bundeshaus (Bern)");
        GPX.writeNode("sym", "City");
      }
      GPX.decrIndent();
      GPX.tagStart("/wpt");
      GPX.tagEnd(NEWLINE, NOSLASH);
    }
  }
  GPX.decrIndent();
  GPX.tagStart("/gpx");
  GPX.tagEnd(NEWLINE, NOSLASH);
  GPX.flush();
}


//  -- END OF FILE --
