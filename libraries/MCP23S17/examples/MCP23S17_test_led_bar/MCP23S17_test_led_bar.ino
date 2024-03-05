//
//    FILE: MCP23S17_test_led_bar.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo MCP23S17 control of LED bar
//     URL: https://github.com/RobTillaart/MCP23S17
//
//  control of a 10-line LED bar, via pin 0..9  (Think VU meter etc)
//  2 different methods, one by one versus 16 bit mask
//  bit mask is faster (~6x) for both HW SPI and SW SPI


#include "MCP23S17.h"


//  MCP23S17 MCP(10, 12, 11, 13);  //  SW SPI address 0x00
MCP23S17 MCP(10);           //  HW SPI address 0x00

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.print("MCP23S17_LIB_VERSION: ");
  Serial.println(MCP23S17_LIB_VERSION);
  Serial.println();
  delay(100);

  SPI.begin();

  bool b = MCP.begin();
  Serial.println(b ? "true" : "false");

  //  all pins output
  MCP.pinMode16(0x0000);  //  0 = output, 1 = input
  delay(100);
}


void loop()
{
  int x = analogRead(A0);  //  0 .. 1023
  delay(100);

  start = micros();
  ledbar_1(x / 100);       //  0 .. 10
  stop = micros();
  Serial.print("Time 1:\t");
  Serial.println(stop - start);
  delay(1000);

  start = micros();
  ledbar_2(x / 100);       //  0 .. 10
  stop = micros();
  Serial.print("Time 2:\t");
  Serial.println(stop - start);
  Serial.println();
  delay(1000);
}


void ledbar_1(int x)
{
  //  set leds one at a time.
  int i = 0;
  while (i++ < x)
  {
    MCP.write1(i, HIGH);
  }
  while (i++ < 10) MCP.write1(i, LOW);
}


void ledbar_2(int x)
{
  //  use 16 bit bit mask.
  uint16_t n = (1 << x) - 1;
  MCP.write16(n);
}

//  -- END OF FILE --
