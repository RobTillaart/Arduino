//
//    FILE: smooth2Value.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test mcp4725 lib
//     URL: https://github.com/RobTillaart/MCP4725


#include "Wire.h"
#include "MCP4725.h"

MCP4725 MCP(0x62);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MCP4725_VERSION: ");
  Serial.println(MCP4725_VERSION);

  Wire.begin();

  MCP.begin();

  Serial.print("\nValue:\t");
  Serial.println(MCP.getValue());
  Serial.println();


  Serial.println("smooth2Value(2000, 10)");
  smooth2Value(2000, 10);
  Serial.print("Value:\t");
  Serial.println(MCP.getValue());
  Serial.println();

  Serial.println("smooth2Value(100, 50)");
  smooth2Value(100, 10);
  Serial.print("Value:\t");
  Serial.println(MCP.getValue());
  Serial.println();


  //////////////////////////////////////////////////
  Serial.println("\n\nPERFORMANCE\n");

  uint32_t start = micros();
  for (int i = 0; i < 100; i++)
  {
    smooth2Value(i * 10, 10);
  }
  uint32_t end = micros();
  Serial.print("100x  MCP.smooth2Value(i*10, 10):\t");
  Serial.println(end - start);

  Serial.print("\nDone... (start triangle mode)");
}


void loop()
{
  //  different gradients
  smooth2Value(4095, 4096);
  smooth2Value(0, 4096);
  smooth2Value(4095, 2048);
  smooth2Value(0, 2048);
  smooth2Value(4095, 1024);
  smooth2Value(0, 1024);
}


int smooth2Value(uint16_t value, uint16_t steps)
{
  if (value > MCP4725_MAXVALUE) return MCP4725_VALUE_ERROR;

  if (steps > 1)
  {
    uint16_t startValue = MCP.getValue();
    float delta = (1.0 * (value - startValue)) / steps;

    for (uint16_t i = 0; i < steps - 1; i++)
    {
      MCP.setValue( round(startValue + i * delta) );
    }
  }
  //  get the end value right
  return MCP.setValue(value);
}


//  -- END OF FILE --

