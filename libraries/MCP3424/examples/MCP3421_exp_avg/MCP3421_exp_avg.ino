//
//    FILE: MCP3421_exp_avg.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: create higher resolution from exponential average of 16 bit samples
//     URL: https://github.com/RobTillaart/MCP3424
//
//  by taking the exponential average of multiple 16 bits samples one
//  can get some extra bits of resolution.
//
//  make it visual with Serial plotter.

#include "MCP3424.h"

MCP3421 mcp;
uint32_t lastRead = 0;

float expAvg = 0;


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
    //  next line is for testing purpose (16 bits assumed)
    raw = 32767 * sin(now * 1e-3);
    //  raw = mcp.read();
    //  scale the raw measurement to an 18 bit sample
    //  12 bit => * 64
    //  14 bit => * 16
    //  16 bit => * 4
    //  take exponential average.
    expAvg += (raw*4 - expAvg) * 0.6;
    float uV = expAvg * 15.625e-0;  //  18 bits  gain=1
    Serial.print(raw);
    Serial.print("\t");
    Serial.print(expAvg);
    Serial.print("\t");
    //  Serial.print(uV, 3);  //  optional.
    Serial.println();
  }
}


//  -- END OF FILE --
