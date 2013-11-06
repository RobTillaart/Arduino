//
//    FILE: XMLWriterTest.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.00
// PURPOSE: make a simple XML generating lib
//    DATE: 2013-11-06
//     URL:
//
// Released to the public domain
//

#include <XMLWriter.h>

XMLWriter XML(&Serial);

char buffer[24];

void setup()
{
    Serial.begin(115200);

    XML.header();
    XML.comment("XMLWriterTest.ino\n This is a demo of a simple XML lib for Arduino");

    XML.tagOpen("Arduino", "42");

    XML.tagOpen("Ports");
    doAnalogPorts("before");
    doDigitalPorts();
    doAnalogPorts("after");
    XML.tagClose();

    doWeather();

    XML.tagClose();
}

void doAnalogPorts(char* name)
{
    XML.comment("The analog ports are multiplexed", true);
    XML.tagOpen("Analog", name);
    XML.writeNode("Analog0", itoa(analogRead(A0), buffer, 10));
    XML.writeNode("Analog1", itoa(analogRead(A1), buffer, 10));
    XML.writeNode("Analog2", itoa(analogRead(A2), buffer, 10));
    XML.tagClose();
}

void doDigitalPorts()
{
    XML.comment("The digital ports are not multiplexed", true);
    XML.tagOpen("Digital");
    XML.writeNode("D1", itoa(digitalRead(1), buffer, 10));
    XML.writeNode("D13", itoa(digitalRead(13), buffer, 10));
    XML.writeNode("D10", itoa(digitalRead(10), buffer, 10));
    XML.tagClose();
}

void doWeather()
{
    XML.comment("The weather in Nebraska", true);
    XML.tagOpen("Weather");
    XML.writeNode("Date", "20131106");
    XML.writeNode("Time", "11:42");
    XML.writeNode("Temp", "23.4");
    XML.writeNode("Humi", "50%");
    XML.writeNode("Rain", "10mm");
    XML.writeNode("Sun", "40");
    XML.tagClose();
}

void loop()
{
}
