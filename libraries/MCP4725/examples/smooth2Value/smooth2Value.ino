//
//    FILE: smooth2Value.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.00
// PURPOSE: test mcp4725 lib
//    DATE: 2013-12-01
//     URL:
//
// Released to the public domain
//

#include <Wire.h>
#include "MCP4725.h"

MCP4725 DAC(0x62);  // 0x62 or 0x63

void setup() 
{
  Serial.begin(115200);

  Serial.print("MCP4725 test program: ");
  Serial.println(MCP4725_VERSION);

  DAC.begin();

  Serial.print("\nValue:\t");
  Serial.println(DAC.getValue());
  Serial.println();


  Serial.println("smooth2Value(2000, 10)");
  DAC.smooth2Value(2000, 10);
  Serial.print("Value:\t");
  Serial.println(DAC.getValue());
  Serial.println();

  Serial.println("smooth2Value(100, 50)");
  DAC.smooth2Value(100, 10);
  Serial.print("Value:\t");
  Serial.println(DAC.getValue());
  Serial.println();


  //////////////////////////////////////////////////
  Serial.println("\n\nPERFORMANCE\n");
  Serial.print("TWBR:\t");
  Serial.println(TWBR);
  Serial.println();

  uint32_t start = micros();
  for (int i=0; i< 100; i++)
  {
    DAC.smooth2Value(i*10, 10);
  }
  uint32_t end = micros();
  Serial.print("100x  DAC.smooth2Value(i*10, 10):\t");
  Serial.println(end - start);

  Serial.print("\nDone... (start triangle mode)");
}

void loop() 
{
  // different gradients
  DAC.smooth2Value(4095, 4096);
  DAC.smooth2Value(0, 4096);
  DAC.smooth2Value(4095, 2048);
  DAC.smooth2Value(0, 2048);
  DAC.smooth2Value(4095, 1024);
  DAC.smooth2Value(0, 1024);
}


int smooth2Value(uint16_t value, uint8_t steps)
{
  static int _lastValue = 0;

  // speed optimization
  if (value == _lastValue) return 0;
  if (value > MCP4725_MAXVALUE) return MCP4725_VALUE_ERROR;
  if (steps == 0) steps++;

  uint16_t delta = (value - _lastValue)/steps;
  if (delta > 0)
  {
    uint16_t v = _lastValue;
    for (int i=0; i < steps-1; i++)
    {
      v += delta;
      DAC.setValue(v);
    }
  }
  // be sure to get the end value right
  int rv = DAC.setValue(value);
  _lastValue = value;
  return rv;
}

