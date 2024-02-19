//
//    FILE: LineFormatter_Ethernet.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo LineFormatter for EthernetClient
//     URL: https://github.com/RobTillaart/LineFormatter


#include "LineFormatter.h"

#include "SPI.h"
#include "Ethernet.h"

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip( 192, 168, 1, 177);

const int EthernetPIN = 10;

EthernetServer server(80);    //  change to your configuration

char httpRequest[40];
uint8_t reqCnt;


////////////////////////////////////////////////////////////////////
//
//  HTTP HELPER CODE
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
//  Based upon webServer example demo
//
void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("LINEFORMATTER_LIB_VERSION: ");
  Serial.println(LINEFORMATTER_LIB_VERSION);
  Serial.println();

  //  Ethernet.init(pin) to configure the CS pin
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
  //  listen for incoming clients
  EthernetClient client = server.available();

  if (client)
  {
    Serial.print("\n<CONNECTION>\n  ");
    //  Serial.println(client.remoteIP());
    //  Serial.println(client.remotePort());

    //  an http request ends with a blank line
    boolean currentLineIsBlank = true;
    reqCnt = 0;
    while (client.connected())
    {
      if (client.available())
      {
        char c = client.read();
        Serial.write(c);        //  collect HHTP request here..
        if (reqCnt < 39)
        {
          httpRequest[reqCnt++] = c;
          httpRequest[reqCnt] = 0;
        }

        //  if you've gotten to the end of the line (received a newline
        //  character) and the line is blank, the http request has ended,
        //  so you can send a reply
        if (c == '\n' && currentLineIsBlank)
        {
          if (strstr(httpRequest, "table1.txt"))
          {
            uint32_t start = micros();
            //  send a standard http response header
            HTTP_header(&client, "text/txt", true, 5);
            LineFormatter LF(&client);

            test_table_1(&LF);

            uint32_t stop = micros();
            Serial.println(stop - start);
            Serial.println(LF.getLineCount());
            Serial.println(LF.getLineCount() * 1e6 / (stop - start));
            break;
          }
          if (strstr(httpRequest, "table2.txt"))
          {
            uint32_t start = micros();
            //  send a standard http response header
            HTTP_header(&client, "text/txt", true, 5);
            LineFormatter LF(&client);

            test_table_2(&LF);

            uint32_t stop = micros();
            Serial.println(stop - start);
            Serial.println(LF.getLineCount());
            Serial.println(LF.getLineCount() * 1e6 / (stop - start));
            break;
          }

          //  default page is simple HTML
          //  send a standard http response header
          HTTP_header(&client, "text/html", true, 5);

          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.println("<head>");
          client.println("<title>Demo LineFormatter</title>");
          client.println("</head>");
          client.println("<body>");
          client.println("<h1>Demo LineFormatter for EthernetClient</h1>");
          client.println("<p>Get <a href=\"table1.txt\">TXT 1</a>.</p>");
          client.println("<p>Get <a href=\"table2.txt\">TXT 2</a>.</p>");
          client.println("</body>");
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          Serial.print("  ");
          //  you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          //  you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    //  give the web browser time to receive the data
    delay(1);
    client.stop();
    Serial.println("</CONNECTION>");
  }
}


void test_table_1(LineFormatter L)
{
  L.println();
  L.println(__FUNCTION__);
  L.repeat(strlen(__FUNCTION__), "=", 2);

  L.clearTabs();
  L.addTab(3);
  L.addTab(10);
  L.addTab(20);
  L.addTab(30);
  L.addRelTab(6);
  L.addRelTab(6);
  L.addRelTab(10);
  L.addRelTab(6);
  L.addRelTab(6);

  int measurement = 1;

  L.println("\tIdx\tTime\tValue\tA0\tA1\tA2\tA3\tA4\tA5");
  L.repeat(8, "----+----|", 1);

  L.setAutoNewLine(5);
  for (int i = 0; i < 20; i++)
  {
    if (i == 10)
    {
      L.println("switch to normal tab behaviour");
      L.repeat(8, "----+----|", 1);
      L.clearTabs();   //  just to show diff
    }

    L.tab();
    L.print(measurement++);
    L.tab();
    L.print(millis());
    L.tab();
    L.print(random(12345));
    L.tab();
    L.print(analogRead(A0));
    L.tab();
    L.print(analogRead(A1));
    L.tab();
    L.print(analogRead(A2));
    L.tab();
    L.print(analogRead(A3));
    L.tab();
    L.print(analogRead(A4));
    L.tab();
    L.print(analogRead(A5));
    L.println();
    //  delay(random(100));
  }
  L.repeat(8, "----+----|", 1);
  L.setAutoNewLine(0);

  L.repeat(3, '\n');
}


void test_table_2(LineFormatter L)
{
  L.println();
  L.println(__FUNCTION__);
  L.repeat(strlen(__FUNCTION__), "=", 2);

  L.clearTabs();
  L.addTab(3);
  L.addTab(10);
  L.addTab(20);
  L.addTab(30);
  L.addRelTab(6);
  L.addRelTab(6);
  L.addRelTab(10);
  L.addRelTab(6);
  L.addRelTab(6);
  //  L.println(L.getTabCount());

  int measurement = 1;

  L.println("\tIdx\tTime\tValue\tA0\tA1\tA2\tA3\tA4\tA5");
  L.repeat(7, "----+----|", 1);

  L.setAutoNewLine(5);
  for (int i = 0; i < 20; i++)
  {
    L.tab();
    L.print(measurement++);
    if (i % 5 == 0)
    {
      L.tab();
      L.print(millis());
      L.tab();
      L.print(random(12345));
    }
    else
    {
      L.tab(2);
    }
    L.tab();
    L.print(analogRead(A0));
    L.tab();
    L.print(analogRead(A1));
    L.tab();
    L.print(analogRead(A2));
    L.tab();
    L.print(analogRead(A3));
    L.tab();
    L.print(analogRead(A4));
    L.tab();
    L.print(analogRead(A5));
    L.println();
    //  delay(random(100));
  }
  L.repeat(7, "----+----|", 1);
  L.setAutoNewLine(0);

  L.repeat(3, '\n');
}


//  -- END OF FILE --
