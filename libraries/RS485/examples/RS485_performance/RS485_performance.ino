//    FILE: RS485_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: simple performance test for write(array, length)
//     URL: https://github.com/RobTillaart/RS485

#include "Arduino.h"
#include "RS485.h"

RS485 rs485(&Serial, 4);  //  uses default deviceID

uint32_t start, stop = 0;

void setup()
{
  Serial.begin(4800);
  while (!Serial);
  // Serial.println(__FILE__);

  test(4800);
}

void loop()
{
}


void test(uint32_t baudrate)
{
  char buffer[64] = "123456789012345678901234567890123456789012345678901234567890";
  rs485.setMicrosPerByte(baudrate);
  start = micros();
  rs485.write((uint8_t *)buffer, 60);
  stop = micros();
  Serial.print("\nTIME: ");
  Serial.println(stop - start);
}

// -- END OF FILE --
