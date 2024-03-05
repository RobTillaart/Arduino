//
//    FILE: MCP23017_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test MCP23017 library
//     URL: https://github.com/RobTillaart/MCP23017_RT


#include "MCP23017.h"


MCP23017 MCP(0x27);

uint32_t start, stop;


void setup()
{
  Serial.begin(230400);
  Serial.println();
  Serial.print("MCP23017_LIB_VERSION: ");
  Serial.println(MCP23017_LIB_VERSION);
  Serial.println();
  delay(100);

  Wire.begin();
  bool b = MCP.begin();
  Serial.print("BEGIN: ");
  Serial.println(b);

  MCP.pinMode8(0, 0x00);  //  0 = output , 1 = input
  MCP.pinMode8(1, 0x00);

  Serial.println("\ntime in microseconds\n");
  delay(100);


  Serial.print("TEST write1(0, value):\t");
  delay(100);
  start = micros();
  for (int i = 0; i < 16; i++)
  {
    MCP.write1(0, i & 0x01);  //  alternating HIGH/LOW
  }
  stop = micros();
  Serial.println((stop - start) / 16.0);


  Serial.print("TEST write1(pin, value):\t");
  delay(100);
  start = micros();
  for (int pin = 0; pin < 16; pin++)
  {
    MCP.write1(pin, 1 - pin % 2);  //  alternating HIGH/LOW
  }
  stop = micros();
  Serial.println((stop - start) / 16.0);


  Serial.print("TEST read1(pin):\t");
  delay(100);
  start = micros();
  volatile int val = 0;
  for (int pin = 0; pin < 16; pin++)
  {
    val = MCP.read1(pin);
  }
  stop = micros();
  Serial.println((stop - start) / 16.0);
  Serial.println(val);           //  keep build CI compiler happy
  Serial.println();


  //////////////////////////////////////////////////
  //
  // write8 read8 interface
  //
  Serial.print("TEST write8(port, mask):\t");
  delay(100);
  start = micros();
  MCP.write8(0, 0xAA);  //  alternating HIGH/LOW
  MCP.write8(1, 0xAA);  //  alternating HIGH/LOW
  stop = micros();
  Serial.println((stop - start) / 2.0);


  Serial.print("TEST read8(port):\t");
  delay(100);
  start = micros();
  volatile int val8 = MCP.read8(0);
  val8 = MCP.read8(1);
  stop = micros();
  Serial.println((stop - start) / 2.0);
  Serial.println(val8);           //  keep build CI compiler happy
  Serial.println();

  
  //////////////////////////////////////////////////
  //
  // write16 read16 interface
  //
  Serial.print("TEST write16(mask):\t");
  delay(100);
  start = micros();
  MCP.write16(0xAAAA);  //  alternating HIGH/LOW
  stop = micros();
  Serial.println((stop - start) / 2.0);


  Serial.print("TEST read16():\t");
  delay(100);
  start = micros();
  volatile uint16_t val16 = MCP.read16();
  stop = micros();
  Serial.println((stop - start) / 2.0);
  Serial.println(val16);           //  keep build CI compiler happy
  Serial.println();

  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --
