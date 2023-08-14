//
//    FILE: MCP23S17_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test MCP23S17 library
//     URL: https://github.com/RobTillaart/MCP23S17


#include "MCP23S17.h"
#include "SPI.h"

// MCP23S17 MCP(10, 12, 11, 13);  //  SW SPI address 0x00
MCP23S17 MCP(10);           //  HW SPI address 0x00

uint32_t start, stop;

volatile int val1;
volatile int val8;
volatile uint16_t val16;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.print("MCP23S17_test version: ");
  Serial.println(MCP23S17_LIB_VERSION);
  Serial.println();
  delay(100);

  SPI.begin();
  bool b = MCP.begin();
  Serial.println(b ? "true" : "false");

  Serial.print("HWSPI: ");
  Serial.println(MCP.usesHWSPI());

  MCP.setSPIspeed(10000000);

  MCP.pinMode8(0, 0x00);  //  0 = output , 1 = input
  MCP.pinMode8(1, 0x00);

  Serial.println("\ntime in microseconds\n");
  delay(100);


  Serial.print("TEST digitalWrite(0, value):\t");
  delay(100);
  start = micros();
  for (int i = 0; i < 16; i++)
  {
    MCP.digitalWrite(0, i & 0x01);  //  alternating HIGH/LOW
  }
  stop = micros();
  Serial.println((stop - start) / 16.0);


  Serial.print("TEST digitalWrite(pin, value):\t");
  delay(100);
  start = micros();
  for (int pin = 0; pin < 16; pin++)
  {
    MCP.digitalWrite(pin, 1 - pin % 2);  //  alternating HIGH/LOW
  }
  stop = micros();
  Serial.println((stop - start) / 16.0);


  Serial.print("TEST digitalRead(pin):\t");
  delay(100);
  start = micros();
  for (int pin = 0; pin < 16; pin++)
  {
    val1 = MCP.digitalRead(pin);
  }
  stop = micros();
  Serial.println((stop - start) / 16.0);
  Serial.println();


  //////////////////////////////////////////////////
  //
  //  write8 read8 interface
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
  val8 = MCP.read8(0);
  val8 = MCP.read8(1);
  stop = micros();
  Serial.println((stop - start) / 2.0);
  Serial.println();


  //////////////////////////////////////////////////
  //
  //  write16 read16 interface
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
  val16 = MCP.read16();
  stop = micros();
  Serial.println((stop - start) / 2.0);
  Serial.println();

  //  keep compiler happy
  Serial.print("VAL1:\t");
  Serial.println(val1);
  Serial.print("VAL8:\t");
  Serial.println(val8);
  Serial.print("VAL16:\t");
  Serial.println(val16);

  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --
