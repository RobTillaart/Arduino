//
//    FILE: GPXWriterTest.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: simple GPX writer
//     URL: https://github.com/RobTillaart/XMLWriter


#include <XMLWriter.h>

XMLWriter GPX(&Serial);

struct WPT
{
  float latitude;
  float longitude;
  float elevation;
  char time[24];
  char name[24];
  char symbol[12];
} wpt[3] =
{
  {
    52.518611, 13.376111, 35.0,
    "2011-12-31T23:59:59Z",
    "Reichstag (Berlin)",
    "City"
  },
  {
    48.208031, 16.358128, 179,
    "2011-12-31T23:59:59Z",
    "Parlament (Wien)",
    "City"
  },
  {
    46.9466, 7.44412, 179,
    "2011-12-31T23:59:59Z",
    "Bundeshaus (Bern)",
    "City"
  }
};


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


//  example from https://en.wikipedia.org/wiki/GPS_Exchange_Format
void GPXTest()
{
  GPX.setIndentSize(1);  //  odd indents are possible, 3 is nice!

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


      for (int i = 0; i < 3; i++)
      {
        GPX.tagStart("wpt");
        {
          //  cast needed due to ambiguity API.
          GPX.tagField("lat", wpt[i].latitude, (uint8_t)6);
          GPX.tagField("lon", wpt[i].longitude, (uint8_t)6);
        }
        GPX.tagEnd(NEWLINE, NOSLASH);
        GPX.incrIndent();
        {
          GPX.writeNode("ele", wpt[i].elevation, (uint8_t)1);
          GPX.writeNode("time", wpt[i].time);
          GPX.writeNode("name", wpt[i].name);
          GPX.writeNode("sym", wpt[i].symbol);
        }
        GPX.decrIndent();
        GPX.tagStart("/wpt");
        GPX.tagEnd(NEWLINE, NOSLASH);
      }
      //  end for loop.
    }
  }
  GPX.decrIndent();
  GPX.tagStart("/gpx");
  GPX.tagEnd(NEWLINE, NOSLASH);
  GPX.flush();
}


//  -- END OF FILE --
