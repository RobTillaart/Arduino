//
//    FILE: MCP3424_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: basic test API calls.
//     URL: https://github.com/RobTillaart/MCP3424
//
//  needs a device connected to be able to test.
//

#include "MCP3424.h"

MCP3424 mcp;

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("MCP3424_LIB_VERSION: ");
  Serial.println(MCP3424_LIB_VERSION);
  Serial.println();

  Wire.begin();
  Wire.setTimeout(10000);
  mcp.begin();

  Serial.println();
  Serial.print("Address:\t");
  Serial.println(mcp.getAddress(), HEX);
  Serial.print("Connect:\t");
  Serial.println(mcp.isConnected());
  Serial.print("Channels:\t");
  Serial.println(mcp.getMaxChannels());
  Serial.print("Gain:\t");
  Serial.println(mcp.getGain());
  Serial.print("Bits:\t");
  Serial.println(mcp.getResolution());
  Serial.println();
  delay(100);

  for (uint32_t speed = 100000; speed <= 800000; speed += 100000)
  {
    Wire.setClock(speed);
    Serial.print("\nI2C CLOCK: \t");
    Serial.println(speed);
    test();
  }

  Serial.println("\ndone...");
}


void loop()
{
}


void test()
{
  //  test gain
  start = micros();
  mcp.setGain(2);
  stop = micros();
  Serial.print("SETGAIN: \t");
  Serial.println(stop - start);
  delay(10);

  //  test read for different resolutions.
  for (uint8_t res = 18; res >= 12; res -= 2)
  {
    start = micros();
    mcp.setResolution(res);
    stop = micros();
    Serial.print("RES_");
    Serial.print(res);
    Serial.print(": \t");
    Serial.println(stop - start);
    delay(10);

    start = micros();
    mcp.read();
    stop = micros();
    Serial.print("READ: \t\t");
    Serial.println(stop - start);
    delay(10);

    //  milli and micro volts are identical code.
    start = micros();
    mcp.readVolts();
    stop = micros();
    Serial.print("VOLTS: \t\t");
    Serial.println(stop - start);
    delay(10);
  }
}

//  -- END OF FILE --
