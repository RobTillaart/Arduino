//
//    FILE: XMLWriterSDcard.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: XML writing to SD card
//    DATE: 2020-04-24
//     URL: https://github.com/RobTillaart/XMLWriter
//
// Note: this application will write to the SD card immediately 
// and it will append to the data.xml file every time started.


#include <SPI.h>
#include <SD.h>
// SPI       PINS
// MOSI       11
// MISO       12
// CLOCK      13
// CS         10
#define CS                  10      // adjust this ChipSelect line if needed !

#include <XMLWriter.h>

char buffer[24];


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  // initialize the SD card
  if (!SD.begin(CS))
  {
    Serial.println("Error: SD card failure");
    while(1);
  }

  // remove file for proper timing
  SD.remove("data.xml");
  delay(1000);


  uint32_t start = micros();
  File logfile = SD.open("data.xml", FILE_WRITE);
  if (!logfile)
  {
    Serial.println("Error: SD card failure");
    while(1);
  }

  XMLWriter XML(&logfile);
  XML.header();
  XML.comment("XMLWriterSDcard.ino\nThis is a demo of a simple XML lib for Arduino", true);
  XML.tagOpen("Arduino", "42");
  XML.tagOpen("Ports");
  AnalogPorts(&XML, "measurement");
  DigitalPorts(&XML);
  XML.tagClose();
  XML.tagClose();
  XML.flush();

  logfile.close();

  uint32_t stop = micros();
  Serial.println();
  Serial.println(stop - start);
  Serial.println("Done...");
}


// casting to keep some compilers happy
void AnalogPorts(XMLWriter* xw, const char* name)
{
  xw->comment("The analog ports are multiplexed");
  xw->tagOpen("Analog", name);
  xw->writeNode("Analog0", itoa(analogRead(A0), buffer, 10));
  xw->writeNode("Analog1", (uint16_t) analogRead(A1));
  xw->writeNode("Analog2", (double) (5.0*analogRead(A2))/1023);  // default nr decimals = 2
  xw->writeNode("Analog3", (double) (5.0*analogRead(A2))/1023, (uint8_t)3);
  xw->tagClose();
}


void DigitalPorts(XMLWriter* xw)
{
  xw->comment("The digital ports are not multiplexed");
  xw->tagOpen("Digital");
  xw->writeNode("D1", itoa(digitalRead(1), buffer, 10));
  xw->writeNode("D13", (uint8_t)digitalRead(13));
  xw->tagClose();
}


void loop()
{
}


// -- END OF FILE --

