//
//    FILE: XMLWriterDemo01.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: XML writer demo
//    DATE: 2016-03-16
//     URL: https://github.com/RobTillaart/XMLWriter


#include <XMLWriter.h>

XMLWriter XML(&Serial);


void setup()
{
  Serial.begin(115200);

  double p = random(100) * 1.0;
  double y = random(100) * 1.0;
  double r = random(100) * 1.0;

  uint32_t start = micros();
  shoot(p, y, r);
  uint32_t stop = micros();
  Serial.println();
  Serial.println(stop - start);
}


void shoot(double p, double y, double r)
{
  uint8_t ID = 0;

  XML.header();
  XML.comment("Demo opening tag with multiple fields");
  XML.tagOpen("shoot");

  XML.comment("use nodes for every field");
  XML.tagOpen("position");
  XML.writeNode("id", ID++);
  XML.writeNode("pitch", p);
  XML.writeNode("yaw", y);
  XML.writeNode("roll", r);
  XML.writeNode("Date", "20160316");
  XML.writeNode("Time", "101534");
  XML.tagClose();  // position

  XML.comment("use tagfields in tag");
  XML.tagStart("position");
  XML.tagField("id", ID++);
  XML.tagField("pitch", p);
  XML.tagField("yaw", y);
  XML.tagField("roll", r);
  XML.tagField("Date", "20160316");
  XML.tagField("Time", "101534");
  XML.tagEnd();

  XML.comment("use manual indent and raw output");
  XML.tagStart("position");
  XML.tagField("id", ID++);
  XML.tagField("pitch", p);
  XML.tagField("yaw", y);
  XML.tagField("roll", r);
  XML.tagEnd(NEWLINE, NOSLASH);
  XML.incrIndent();
  XML.indent();
  XML.raw("20160316\n");
  XML.indent();
  XML.raw("101534\n");
  XML.decrIndent();
  XML.tagStart("/position");
  XML.tagEnd(NEWLINE, NOSLASH);

  XML.comment("use manual indent + nodes");
  XML.tagStart("position");
  XML.tagField("id", ID++);
  XML.tagField("pitch", p);
  XML.tagField("yaw", y);
  XML.tagField("roll", r);
  XML.tagEnd(NEWLINE, NOSLASH);
  XML.incrIndent();
  XML.writeNode("Date", "20160316");
  XML.writeNode("Time", "101534");
  XML.decrIndent();
  XML.tagStart("/position");
  XML.tagEnd(NEWLINE, NOSLASH);

  XML.comment("test escape() codes");
  XML.tagOpen("supported");
  XML.writeNode("ampersand", "&");
  XML.writeNode("lessthan", "<");
  XML.writeNode("greaterthan", ">");
  XML.writeNode("quote", "\"");
  XML.writeNode("apostrophe", "\'");
  XML.tagClose();

  XML.tagClose();  // shoot
  XML.flush();
}


void loop()
{
}


// -- END OF FILE --

