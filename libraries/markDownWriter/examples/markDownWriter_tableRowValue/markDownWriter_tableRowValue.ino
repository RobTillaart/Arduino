//
//    FILE: markDownWriter_tableRowValue.ino
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
  mdw.chapter("demo table fields");

  //  table headers (max 11 chars)
  char hdrs[][12] = { "day", "temperature", "humidity" };
  char align[] = "LRR";  //  shorter
  char days[][10] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

  mdw.tableHeader(3, hdrs, align);

  //  table values
  for (int i = 0; i < 7; i++)
  {
    float temp = 20.0 + random(50) * 0.1;
    int hum = 40 + random(10);
    mdw.tableRowStart();
    mdw.tableRowValue(days[i]);
    mdw.tableRowValue(temp, 1);
    mdw.tableRowValue(hum);
    mdw.tableRowEnd();
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
