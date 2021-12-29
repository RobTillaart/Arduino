//
//    FILE: XMLWriterDefaultSerial.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: make a simple XML generating lib
//    DATE: 2020-04-24
//     URL: https://github.com/RobTillaart/XMLWriter


#include <XMLWriter.h>

XMLWriter XML;

char buffer[24];


void setup()
{
  Serial.begin(115200);
  uint32_t start = micros();
  XML.header();
  XML.comment("XMLWriterTest.ino\nThis is a demo of a simple XML lib for Arduino", true);

  XML.tagOpen("Arduino", "42");

  XML.tagOpen("Ports");
  AnalogPorts("before");
  DigitalPorts();
  AnalogPorts("after");
  XML.tagClose();

  Weather();
  Weather2();
  DataTypes();

  XML.tagClose();
  XML.flush();

  uint32_t stop = micros();
  Serial.println();
  Serial.println(stop - start);
}


void Weather2()
{
  XML.comment("The weather in South Africa");
  for (int i = 0; i < 10; i++)
  {
    XML.tagStart("Weather");
    XML.tagField("Date", "20131106");
    XML.tagField("Time", "1:42");
    XML.tagField("Temp", "23.4");
    XML.tagField("Humi", "50%");
    XML.tagField("Rain", "10mm");
    XML.tagField("Sun", "40");
    XML.tagEnd();
  }
}


void Weather()
{
  XML.comment("The weather in Nebraska");
  XML.tagOpen("Weather");
  XML.writeNode("Date", "20131106");
  XML.writeNode("Time", "11:42");
  XML.writeNode("Temp", "23.4");
  XML.writeNode("Humi", "50%");
  XML.writeNode("Rain", "10mm");
  XML.writeNode("Sun", "40");
  XML.tagClose();
}


// casting to keep some compilers happy
void AnalogPorts(const char* name)
{
  XML.comment("The analog ports are multiplexed");
  XML.tagOpen("Analog", name);
  XML.writeNode("Analog0", itoa(analogRead(A0), buffer, 10));
  XML.writeNode("Analog1", (uint16_t) analogRead(A1));
  // default nr decimals = 2
  XML.writeNode("Analog2", (double) (5.0 * analogRead(A2)) / 1023); 
  XML.writeNode("Analog3", (double) (5.0 * analogRead(A3)) / 1023, (uint8_t)3);  
  XML.tagClose();
}


// casting to keep some compilers happy
void DigitalPorts()
{
  XML.comment("The digital ports are not multiplexed");
  XML.tagOpen("Digital");
  XML.writeNode("D1", itoa(digitalRead(1), buffer, 10));
  XML.writeNode("D13", (uint8_t) digitalRead(13));
  XML.tagClose();
}


void DataTypes()
{
  XML.comment("Testing dataTypes I");
  XML.tagOpen("Datatypes");
  XML.writeNode("Bool", 1 == 1);
  XML.writeNode("Bool", 1 == 0);
  XML.writeNode("BIN", 42, BIN);
  XML.writeNode("DEC", 42, DEC);
  XML.writeNode("HEX", 42, HEX);
  XML.writeNode("OCT", 42, OCT);
  XML.tagClose();

  XML.comment("Testing dataTypes II");
  for (int i = 0; i < 3; i++)
  {
    XML.tagStart("dataTypes");
    XML.tagField("Bool", 1 == 1);
    XML.tagField("Bool", 1 == 0);
    int x = analogRead(A0);
    XML.tagField("BIN", x, BIN);
    XML.tagField("DEC", x, DEC);
    XML.tagField("HEX", x, HEX);
    XML.tagField("OCT", x, OCT);
    XML.tagEnd();
  }
}


void loop()
{
}


// -- END OF FILE --

