//
//    FILE: markDownWriter_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/markDownWriter
//     URL: https://github.com/RobTillaart/Temperature


#include "markDownWriter.h"

markDownWriter mdw(&Serial);  //  default Serial


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("MARKDOWNWRITER_LIB_VERSION: ");
  Serial.println(MARKDOWNWRITER_LIB_VERSION);
  Serial.println();

  mdw.reset();

  mdw.title("MARK DOWN WRITER DEMO");
  mdw.chapter("lookup table dewpoint + humidex");

  //  table headers (max 11 chars)
  char hdrs[][12] = { "temperature", "humidity", "dewPoint", "humidex"};
  char align[] = "CCRR"; //  shorter

  mdw.tableHeader(4, hdrs, align);

  //  table values
  for (float temp = 0.0; temp <= 50; temp += 10)
  {
    for (int hum = 10; hum < 95; hum += 10)
    {
      float v[10];
      v[0] = temp;
      v[1] = hum;
      v[2] = dewPointFast(v[0], v[1]);
      v[3] = humidex(v[0], v[1]);
      mdw.tableValues(v, 1);
    }
  }

  mdw.println();
  mdw.print("Table created with: ");
  mdw.URL("markDownWriter", "https://github.com/RobTillaart/markDownWriter");
  mdw.println();
  mdw.println();

  mdw.flush();
}


void loop()
{
}

//  from temperature library
float dewPointFast(float celsius, float humidity)
{
  float a = 17.271;
  float b = 237.7;
  float temp = (a * celsius) / (b + celsius) + log(humidity / 100);
  float Td = (b * temp) / (a - temp);
  return Td;
}

float humidex(float celsius, float dewPoint)
{
  float e = 19.833625 - 5417.753 / (273.16 + dewPoint);
  float h = celsius + 3.3941 * exp(e) - 5.555;
  return h;
}


//  -- END OF FILE --
