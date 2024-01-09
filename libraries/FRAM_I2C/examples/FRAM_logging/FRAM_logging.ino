//
//    FILE: FRAM_logging.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo persistant logging in FRAM.
//     URL: https://github.com/RobTillaart/FRAM_I2C
//
//
//  experimental code
//  TODO - read back sketch.
//
//  last written position uint32_t at addres 0..3
//  log entry: plain text separated by newlines.
//             timestamp + \t + random number +\n
// wraps around if FRAM full => might give corrupted one corrupted line.
//


#include "FRAM.h"

FRAM fram;

uint32_t start;
uint32_t stop;

uint32_t sizeInBytes = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("FRAM_LIB_VERSION: ");
  Serial.println(FRAM_LIB_VERSION);

  Wire.begin();

  int rv = fram.begin(0x50);
  if (rv != 0)
  {
    Serial.print("INIT ERROR: ");
    Serial.println(rv);
  }

  //  get size in bytes
  sizeInBytes = fram.getSize() * 1024;
  //  clear FRAM
  for (uint32_t addr = 0; addr < sizeInBytes; addr++)
  {
    fram.write8(addr, 0x00);
  }
  //  set initial entry.
  fram.write32(0, 0x00000004);

  for (int i = 0; i < 10; i++)
  {
    char buffer[24];
    sprintf(buffer, "%ld\t%ld\n", millis(), random(1000000000UL));
    Serial.print(buffer);
    log2fram(buffer);
    delay(1000);
  }
}


void loop()
{
}


void log2fram(char * str)
{
  uint32_t len  = strlen(str);
  //  might skip reading logaddr and make it static.
  uint32_t logaddr = fram.read32(0);

  //  if beyond size -> start at begin
  if (logaddr + len > sizeInBytes) logaddr = 0x04;  

  fram.write(logaddr, (uint8_t *)str, len);
  logaddr += len;
  fram.write32(0, logaddr);
}


//  -- END OF FILE --
