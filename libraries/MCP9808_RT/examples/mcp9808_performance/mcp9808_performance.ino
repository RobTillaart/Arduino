//
//    FILE: mcp9808_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2020-11-13


#include "mcp9808.h"

MCP9808 ts(24);

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MCP9808_LIB_VERSION: ");
  Serial.println(MCP9808_LIB_VERSION);

  Wire.begin();

  // UNO can do max 850 Kbits / sec
  Serial.println("\nCLOCK\tTEMP\tMICROS");
  for (uint32_t speed = 50000; speed < 875000; speed += 25000)
  {
    Wire.setClock(speed);

    delay(500);
    start = micros();
    float f = ts.getTemperature();
    stop = micros();
    Serial.print(speed / 1000);
    Serial.print('\t');
    Serial.print(f, 3);
    Serial.print('\t');
    Serial.print(stop - start);
    Serial.println();
  }
  Serial.println();
}


void loop()
{
}


// -- END OF FILE --
