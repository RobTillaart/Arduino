//
//    FILE: MCP23008_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test MCP23008 library
//     URL: https://github.com/RobTillaart/MCP23008


#include "MCP23008.h"


MCP23008 MCP(0x27);

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MCP23008_LIB_VERSION: ");
  Serial.println(MCP23008_LIB_VERSION);
  Serial.println();
  delay(100);

  Wire.begin();
  bool b = MCP.begin();
  Serial.print("BEGIN: ");
  Serial.println(b);

  MCP.pinMode8(0x00);  //  0 = output , 1 = input

  Serial.println("\ntime in microseconds\n");
  delay(100);


  Serial.print("TEST write1(0, value):\t");
  delay(100);
  start = micros();
  for (int i = 0; i < 8; i++)
  {
    MCP.write1(i, i & 0x01);  //  alternating HIGH/LOW
  }
  stop = micros();
  Serial.println((stop - start) / 8.0);


  Serial.print("TEST write1(pin, value):\t");
  delay(100);
  start = micros();
  for (int pin = 0; pin < 8; pin++)
  {
    MCP.write1(pin, 1 - pin % 2);  //  alternating HIGH/LOW
  }
  stop = micros();
  Serial.println((stop - start) / 8.0);


  Serial.print("TEST read1(pin):\t");
  delay(100);
  volatile int val = 0;
  start = micros();
  for (int pin = 0; pin < 8; pin++)
  {
    val = MCP.read1(pin);
  }
  stop = micros();
  Serial.println((stop - start) / 8.0);
  Serial.println(val);
  Serial.println();


  //////////////////////////////////////////////////
  //
  //  write8 read8 interface
  //
  Serial.print("TEST write8(mask):\t");
  delay(100);
  start = micros();
  MCP.write8(0xAA);  //  alternating HIGH/LOW
  stop = micros();
  Serial.println(stop - start);


  Serial.print("TEST read8():\t");
  delay(100);
  start = micros();
  volatile int val8 = MCP.read8();
  stop = micros();
  Serial.println(stop - start);
  Serial.println(val8);
  Serial.println();

  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --
