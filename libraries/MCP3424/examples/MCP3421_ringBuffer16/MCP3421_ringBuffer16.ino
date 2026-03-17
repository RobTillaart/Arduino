//
//    FILE: MCP3421_ringBuffer16.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: create faster 18 bits from multiple 16 bits
//     URL: https://github.com/RobTillaart/MCP3424
//
//  in theory you can calculate an extra bits by averaging 4 measurements.
//  this would mean you can get 2 extra bits by averaging 16 measurements.
//  drawback is a phase shift (delay) in the temperatures read.
//  so might be useful - or not.
//
//  make it visual with Serial plotter.

#include "MCP3424.h"

MCP3421 mcp;
uint32_t lastRead = 0;

//  ringBuffer with 16 elements.
class RING16
{
  public:
    RING16()
    {
      _size = 16;
      _index = 0;
      _sum = 0;
    }

    void add(int32_t value)
    {
      _sum -= _buffer[_index];
      _buffer[_index] = value;
      _sum += value;
      _index++;
      if (_index >= _size) _index = 0;
    }

    float average()
    {
      return (4.0 * _sum) / _size;
    }

  private:
    int32_t _buffer[16];
    int _size = 16;
    int _index = 0;
    int32_t _sum = 0;
};

RING16 ring;


void setup()
{
  while (!Serial);
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("MCP3424_LIB_VERSION: ");
  Serial.println(MCP3424_LIB_VERSION);
  Serial.println();

  Wire.begin();
  Wire.setTimeout(10000);
  if (mcp.begin() == false)
  {
    Serial.println("Could not connect...");
    // while (1);
  }

  mcp.setResolution(16);
  //  plotter header
  Serial.println("16bit, 18bit, , ,");
}


void loop()
{
  int32_t raw;
  uint32_t now = millis();
  if (now - lastRead >= 70)  //  16 bit interval
  {
    lastRead = now;
    //  next line is for testing purpose
    //  use plotter to see phase shift.
    raw = 32767 * sin(now * 1e-3);
    //  raw = mcp.read();
    ring.add(raw);
    float avg = ring.average();
    float uV = avg * 15.625e-0;  //  18 bits  gain=1
    Serial.print(raw);
    Serial.print("\t");
    Serial.print(avg);
    Serial.print("\t");
    //  Serial.print(uV, 3);  //  optional.
    Serial.println();
  }
}


//  -- END OF FILE --
