//
//    FILE: FRAM_readLine.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo to read al line until a newline
//          returned value will include the newline '\n'
//     URL: https://github.com/RobTillaart/FRAM_I2C
//   ISSUE: See issue #30 for some backgrounder.
//
//
//  - fill the FRAM with some text lines 
//  - this sketch assumes e.g. produced by FRAM_logging.ino
//  - last written position uint32_t at addres 0..3
//  - log entry: plain text separated by '\n' (newline).


#include "FRAM.h"


FRAM fram;

uint32_t sizeInBytes = 0;

char buffer[32];


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("FRAM_LIB_VERSION: ");
  Serial.println(FRAM_LIB_VERSION);

  Wire.begin();

  //  Can we find FRAM on the I2C bus?
  int rv = fram.begin(0x50);
  if (rv != 0)
  {
    Serial.print("INIT ERROR: ");
    Serial.println(rv);
  }

  //  Get size in bytes to know when to stop.
  sizeInBytes = fram.getSize() * 1024;

  //  assuming FRAM is filled with FRAM_logging.ino
  //  first entry is starts at 0x04 => address next entry is written in [0..3]
  int len = 0;
  uint16_t address = 4;
  len = fram.readLine(address, buffer, 32);
  while ( len >= 0 )
  {
    Serial.print(len);
    Serial.print("\t");
    Serial.print(buffer);
    address = address + len;

    if (address >= sizeInBytes)
    {
      Serial.println("End of FRAM");
      break;
    }
    len = fram.readLine(address, buffer, 32);
  }
  Serial.println("done");

  delay(100);
  uint32_t start = micros();
  len = fram.readUntil(0x04, buffer, 32, '\n');
  uint32_t stop = micros();
  Serial.println(stop - start);

  delay(100);
  start = micros();
  len = fram.readLine(address, buffer, 32);
  stop = micros();
  Serial.println(stop - start);
}


void loop()
{
}


//  -- END OF FILE --
