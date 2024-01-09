//
//    FILE: FRAM_readUntil.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo to read until a separator is found.
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
  len = readUntil(address, buffer, 32, '\n');
  while ( len > 0 )
  {
    Serial.print(len);
    Serial.print("\t");
    Serial.println(buffer);
    address = address + len + 1;

    if (address >= sizeInBytes)
    {
      Serial.println("End of FRAM");
      break;
    }
    len = readUntil(address, buffer, 32, '\n');
  }
  Serial.println("done");

  delay(100);
  uint32_t start = micros();
  len = readUntil(0x04, buffer, 32, '\n');
  uint32_t stop = micros();
  Serial.println(stop - start);

  delay(100);
  start = micros();
  len = readUntilByte(0x04, buffer, 32, '\n');
  stop = micros();
  Serial.println(stop - start);
}


void loop()
{
}


//  block mode implementation (faster)
//  returns length of the buffer 
//  returns -1 if it does not fit.
int32_t readUntil(uint32_t address, char * buf, uint16_t buflen, char separator)
{
  //  read and fill the buffer at once.
  fram.read(address, (uint8_t *)buf, buflen);
  for (uint16_t length = 0; length < buflen; length++)
  {
    if (buf[length] == separator)
    {
      buf[length] = 0;    //  replace separator => \0 EndChar
      return length;
    }
  }
  //  entry does not fit in given buffer.
  return (int32_t)-1;
}


//  byte per byte implementation. (slow).
//  returns length of line in buffer or -1 if it does not fit.
int32_t readUntilByte(uint32_t address, char * buf, uint16_t buflen, char separator)
{
  uint32_t addr = address;
  for (uint16_t length = 0; length < buflen; length++)
  {
    buf[length] = (char) fram.read8(addr++);
    if (buf[length] == separator)
    {
      buf[length] = 0;    //  replace \n => \0 EndChar
      return length;
    }
  }
  //  entry does not fit in given buffer.
  return -1;
}


//  -- END OF FILE --
