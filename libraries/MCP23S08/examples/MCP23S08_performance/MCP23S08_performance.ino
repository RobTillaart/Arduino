//
//    FILE: MCP23S08_performance.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2021-12-30
// PUPROSE: test MCP23017 library


#include "MCP23S08.h"
#include "SPI.h"

// MCP23S08 MCP(10, 12, 11, 13);  //  SW SPI address 0x00
MCP23S08 MCP(10);           //  HW SPI address 0x00

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.print("MCP23S08_LIB_VERSION: ");
  Serial.println(MCP23S08_LIB_VERSION);
  Serial.println();
  delay(100);

  SPI.begin();
  bool b = MCP.begin();
  Serial.print("BEGIN: ");
  Serial.println(b);

  Serial.print("HWSPI: ");
  Serial.println(MCP.usesHWSPI());

  MCP.pinMode8(0x00);  // 0 = output , 1 = input

  Serial.println("\ntime in microseconds\n");
  delay(100);


  Serial.print("TEST digitalWrite(0, value):\t");
  delay(100);
  start = micros();
  for (int i = 0; i < 8; i++)
  {
    MCP.digitalWrite(0, i & 0x01);  // alternating HIGH/LOW
  }
  stop = micros();
  Serial.println((stop - start) / 8.0);


  Serial.print("TEST digitalWrite(pin, value):\t");
  delay(100);
  start = micros();
  for (int pin = 0; pin < 8; pin++)
  {
    MCP.digitalWrite(pin, 1 - pin % 2); //  alternating HIGH/LOW
  }
  stop = micros();
  Serial.println((stop - start) / 8.0);


  Serial.print("TEST digitalRead(pin):\t");
  delay(100);
  volatile int val = 0;
  start = micros();
  for (int pin = 0; pin < 8; pin++)
  {
    val = MCP.digitalRead(pin);
  }
  stop = micros();
  Serial.println((stop - start) / 8.0);
  Serial.println(val);            //  keep build CI compiler happy
  Serial.println();


  //////////////////////////////////////////////////
  //
  // write8 read8 interface
  //
  Serial.print("TEST write8(mask):\t");
  delay(100);
  start = micros();
  MCP.write8(0xAA); // alternating HIGH/LOW
  stop = micros();
  Serial.println(stop - start);


  Serial.print("TEST read8():\t");
  delay(100);
  start = micros();
  volatile int val8 = MCP.read8();
  stop = micros();
  Serial.println(stop - start);
  Serial.println(val8);           //  keep build CI compiler happy
  Serial.println();

  Serial.println("\ndone...");
}


void loop()
{
}


// -- END OF FILE --
