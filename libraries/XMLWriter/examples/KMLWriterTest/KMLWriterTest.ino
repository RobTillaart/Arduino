//
//    FILE: KMLWriterTest.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: simple KML writer
//    DATE: 2015-05-21
//     URL: https://github.com/RobTillaart/XMLWriter


#include <XMLWriter.h>

XMLWriter KML(&Serial);

char buffer[24];


void setup()
{
  Serial.begin(115200);

  uint32_t start = micros();
  KMLTest();
  uint32_t stop = micros();
  Serial.println();
  Serial.println(stop - start);
}


void loop()
{
}


void KMLTest()
{
  KML.setIndentSize(2);

  KML.header();
  KML.comment("KMLWriterTest.ino\nThis is a demo of the XMLWriter lib for Arduino", MULTILINE); // == true (default == false)

  KML.tagStart("kml");
  KML.tagField("xmlns", "http://earth.google.com/kml/2.0");
  KML.tagEnd(NEWLINE, NOSLASH);

  KML.tagOpen("Document");
  KML.tagOpen("Placemark");
  KML.writeNode("name", "MyOffice");

  // should be a function
  KML.tagOpen("LookAt");
  KML.writeNode("longitude", "8.853193712983327");
  KML.writeNode("latitude", "53.10919982492059");
  KML.writeNode("range", "500000");
  KML.writeNode("tilt", "0");
  KML.writeNode("heading", "0");
  KML.tagClose();

  // should be a function
  KML.tagOpen("Point");
  KML.writeNode("coordinates", "8.853193712983327,53.10919982492059,10");
  KML.tagClose();

  KML.tagClose();  // Placemark
  KML.tagClose();  // Document

  KML.tagStart("/kml");
  KML.tagEnd(NEWLINE, NOSLASH);
  KML.flush();
}


/* output
<!--
KMLWriterTest.ino
This is a demo of the XMLWriter lib for Arduino
 -->
<?xml version="1.0" encoding="UTF-8"?>
<kml xmlns="http://earth.google.com/kml/2.0">
<Document>
  <Placemark>
    <name>MyOffice</name>
    <LookAt>
      <longitude>8.853193712983327</longitude>
      <latitude>53.10919982492059</latitude>
      <range>500000</range>
      <tilt>0</tilt>
      <heading>0</heading>
    </LookAt>
    <Point>
      <coordinates>8.853193712983327,53.10919982492059,10</coordinate>
    </Point>
  </Placemark>
</Document>
</kml>
*/


// -- END OF FILE --

