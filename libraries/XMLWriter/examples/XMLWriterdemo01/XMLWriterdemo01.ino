//
//    FILE: XMLWriterDemo01.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.00
// PURPOSE: XML writer demo
//    DATE: 2016-03-16
//     URL:
//
// Released to the public domain
//

#include <XMLWriter.h>

XMLWriter XML(&Serial);

void setup()
{
  Serial.begin(115200);

  float p = random(100) * 1.0;
  float y = random(100) * 1.0;
  float r = random(100) * 1.0;

  shoot(p, y, r);
}

void shoot(float p, float y, float r)
{
  XML.header();
  XML.comment("Demo opening tag with multiple fields");
  XML.tagOpen("shoot");

  XML.comment("use nodes for every field");
  XML.tagOpen("position");
  XML.writeNode("id", 0);
  XML.writeNode("pitch", p);
  XML.writeNode("yaw", y);
  XML.writeNode("roll", r);
  XML.writeNode("Date", "20160316");
  XML.writeNode("Time", "101534");
  XML.tagClose();  // position

  XML.comment("use tagfields in tag");
  XML.tagStart("position");
  XML.tagField("id", 1);
  XML.tagField("pitch", p);
  XML.tagField("yaw", y);
  XML.tagField("roll", r);
  XML.tagField("Date", "20160316");
  XML.tagField("Time", "101534");
  XML.tagEnd();

  XML.comment("use manual indent and raw output");
  XML.tagStart("position");
  XML.tagField("id", 2);
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
  XML.tagField("id", 3);
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

  XML.tagClose();  // shoot
}

void loop()
{
}
