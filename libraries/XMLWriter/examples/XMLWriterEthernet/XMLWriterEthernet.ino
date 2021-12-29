//
//    FILE: XMLWriterEthernet.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo XML writer for EthernetClient
//    DATE: 2020-04-24
//     URL: https://github.com/RobTillaart/XMLWriter


#include <XMLWriter.h>

#include <SPI.h>
#include <Ethernet.h>


byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip( 192, 168, 1, 177);

const int EthernetPIN = 10;

EthernetServer server(80);    // change to your config

char httpRequest[40];
uint8_t reqCnt;


////////////////////////////////////////////////////////////////////
//
// HTTP HELPER CODE
//
void HTTP_header(EthernetClient* cl, const char *contentType, bool keepAlive = false, int refresh = 5)
{
  cl->println("HTTP/1.1 200 OK");
  cl->print("Content-Type: ");
  cl->println( contentType  );
  cl->println("Connection: ");
  cl->println(keepAlive ? "keep-alive" : "close");
  cl->println("Refresh: ");
  cl->println(refresh);
  cl->println();
}



////////////////////////////////////////////////////////////////////
//
// Based upon webServer example demo
//
void setup()
{

  Serial.begin(115200);
  Serial.println(__FILE__);

  // Ethernet.init(pin) to configure the CS pin
  Ethernet.init(EthernetPIN);
  Ethernet.begin(mac, ip);

  if (Ethernet.hardwareStatus() == EthernetNoHardware)
  {
    Serial.println("No hardware found");
    while (1);
  }

  Serial.println(Ethernet.hardwareStatus());
  Serial.println(Ethernet.linkStatus());

  if (Ethernet.linkStatus() == LinkOFF)
  {
    Serial.println("Cable is not connected.");
    Serial.println("Connect cable");
  }
  while (Ethernet.linkStatus() == LinkOFF); // wait for cable

  server.begin();
  Serial.print("ServerIP: ");
  Serial.println(Ethernet.localIP());
}


void loop()
{
  // listen for incoming clients
  EthernetClient client = server.available();

  if (client)
  {
    Serial.print("\n<CONNECTION>\n  ");
    // Serial.println(client.remoteIP());
    // Serial.println(client.remotePort());

    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    reqCnt = 0;
    while (client.connected())
    {
      if (client.available())
      {
        char c = client.read();
        Serial.write(c);  // collect HHTP request here..
        if (reqCnt < 39)
        {
          httpRequest[reqCnt++] = c;
          httpRequest[reqCnt] = 0;
        }

        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank)
        {
          if (strstr(httpRequest, "1.xml"))
          {
            uint32_t start = micros();
            // send a standard http response header
            HTTP_header(&client, "text/xml", true, 5);
            XMLWriter XML(&client, 250);

            // XML body
            XML.header();
            XML.comment("XMLWriterTest.ino\nThis is a demo of a simple XML lib for Arduino", true);

            // use of {} to get indentation that follows the XML (sort of)
            // it adds no code size, but improves readability a lot
            XML.tagOpen("Arduino", "42");
            {
              XML.tagOpen("Ports");
              {
                AnalogPorts(&XML, "before");
                DigitalPorts(&XML);
                AnalogPorts(&XML, "after");
              }
              XML.tagClose();
            }
            XML.tagClose();
            XML.flush();
            uint32_t stop = micros();
            Serial.println(stop - start);
            Serial.println(XML.bytesWritten());
            Serial.println(XML.bytesWritten() * 1e6 / (stop - start));
            break;
          }
          if (strstr(httpRequest, "2.xml"))
          {
            uint32_t start = micros();
            // send a standard http response header
            HTTP_header(&client, "text/xml", true, 5);
            XMLWriter XML(&client, 250);

            // XML body
            XML.header();
            XML.comment("XMLWriterTest.ino\nThis is a demo of a simple XML lib for Arduino", true);

            // use of {} to get indentation that follows the XML (sort of)
            // it adds no code size, but improves readability a lot
            XML.tagOpen("Arduino", "102");
            {
              Weather(&XML);
              Weather2(&XML);
              DataTypes(&XML);
            }
            XML.tagClose();
            XML.flush();
            uint32_t stop = micros();
            Serial.println(stop - start);
            Serial.println(XML.bytesWritten());
            Serial.println(XML.bytesWritten() * 1e6 / (stop - start));
            break;
          }

          // default page is simple HTML
          // send a standard http response header
          HTTP_header(&client, "text/html", true, 5);

          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.println("<head>");
          client.println("<title>Demo XML writer</title>");
          client.println("</head>");
          client.println("<body>");
          client.println("<h1>Demo XML writer for EthernetClient</h1>");
          client.println("<p>Get <a href=\"1.xml\">XML 1</a>.</p>");
          client.println("<p>Get <a href=\"2.xml\">XML 2</a>.</p>");
          client.println("</body>");
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          Serial.print("  ");
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    client.stop();
    Serial.println("</CONNECTION>");
  }
}


////////////////////////////////////////////////////////////////////
//
// XML CODE
//
void Weather2(XMLWriter* xw)
{
  xw->comment("The weather in South Africa");
  for (int i = 0; i < 10; i++)
  {
    xw->tagStart("Weather");
    xw->tagField("Date", "20131106");
    xw->tagField("Time", "1:42");
    xw->tagField("Temp", "23.4");
    xw->tagField("Humi", "50%");
    xw->tagField("Rain", "10mm");
    xw->tagField("Sun", "40");
    xw->tagEnd();
  }
}


void Weather(XMLWriter* xw)
{
  xw->comment("The weather in Nebraska");
  xw->tagOpen("Weather");
  xw->writeNode("Date", "20131106");
  xw->writeNode("Time", "11:42");
  xw->writeNode("Temp", "23.4");
  xw->writeNode("Humi", "50%");
  xw->writeNode("Rain", "10mm");
  xw->writeNode("Sun", "40");
  xw->tagClose();
}


// casting to keep some compilers happy
void AnalogPorts(XMLWriter* xw, const char* name)
{
  char buffer[24];

  xw->comment("The analog ports are multiplexed");
  xw->tagOpen("Analog", name);
  xw->writeNode("Analog0", itoa(analogRead(A0), buffer, 10));
  xw->writeNode("Analog1", (uint16_t) analogRead(A1));
  xw->writeNode("Analog2", (double) (5.0 * analogRead(A2)) / 1023); // default nr decimals = 2
  xw->writeNode("Analog3", (double) (5.0 * analogRead(A2)) / 1023, (uint8_t)3);
  xw->tagClose();
}


// casting to keep some compilers happy
void DigitalPorts(XMLWriter* xw)
{
  char buffer[24];

  xw->comment("The digital ports are not multiplexed");
  xw->tagOpen("Digital");
  xw->writeNode("D1", itoa(digitalRead(1), buffer, 10));
  xw->writeNode("D13", (uint8_t) digitalRead(13));
  xw->tagClose();
}


void DataTypes(XMLWriter* xw)
{
  xw->comment("Testing dataTypes I");
  xw->tagOpen("Datatypes");
  xw->writeNode("BoolT", 1 == 1);
  xw->writeNode("BoolF", 1 == 0);
  xw->writeNode("BIN", 42, BIN);
  xw->writeNode("DEC", 42, DEC);
  xw->writeNode("HEX", 42, HEX);
  xw->writeNode("OCT", 42, OCT);
  xw->tagClose();

  xw->comment("Testing dataTypes II");
  for (int i = 0; i < 3; i++)
  {
    xw->tagStart("dataTypes");
    xw->tagField("BoolT", 1 == 1);
    xw->tagField("BoolF", 1 == 0);
    int x = analogRead(A0);
    xw->tagField("BIN", x, BIN);
    xw->tagField("DEC", x, DEC);
    xw->tagField("HEX", x, HEX);
    xw->tagField("OCT", x, OCT);
    xw->tagEnd();
  }
}


// -- END OF FILE --

