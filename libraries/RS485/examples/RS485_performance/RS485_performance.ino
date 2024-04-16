//    FILE: RS485_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: simple performance test for write(array, length)
//     URL: https://github.com/RobTillaart/RS485

//  minimal test to see how fast data can be send over the
//  RS485 bus at a given baud rate of 4800. (adjust if needed).


#include "Arduino.h"
#include "RS485.h"


RS485 rs485(&Serial, 4);  //  uses default deviceID 0

uint32_t start, stop = 0;


void setup()
{
  Serial.begin(4800);
  while (!Serial);
  //  Serial.println();
  //  Serial.println(__FILE__);
  //  Serial.print("RS485_LIB_VERSION: ");
  //  Serial.println(RS485_LIB_VERSION);
  
  test(4800);

  Serial.println("\ndone...");
}


void loop()
{
}


void test(uint32_t baudrate)
{
  Serial.begin(baudrate);

  delay(10);
  char buffer[64] = "123456789012345678901234567890123456789012345678901234567890";

  start = micros();
  rs485.write((uint8_t *)buffer, 60);
  stop = micros();
  Serial.print("BAUD:\t");
  Serial.print(baudrate);
  Serial.print("\tTIME: ");
  Serial.println(stop - start);
}


//  -- END OF FILE --

