//
//    FILE: MTP40F_I2C_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo of MTP40F I2C interface
//     URL: https://github.com/RobTillaart/MTP40F
//
//
//  TODO TEST WITH SENSOR
//  do not expect this to work yet
//
//  Tested with an MTP40F (slave address 0x32) - PR#7 (MTP40C lib)
//  - reading the gas concentration (command 0x03, three byte response) works
//  - reading and writing of other values doesn't work (the device always returns zeroes)


#include "Wire.h"

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  Wire.begin();
}


void loop()
{
  uint16_t ppm = readMTP40F(0x32);  //  address with I2C scanner
  Serial.print("PPM: ");
  Serial.println(ppm);

  delay(4000);
}


////////////////////////////////////////////////////////////////////////////
//
// MINIMAL I2C READ
//

/*
  Timing sequence of the master:
  1. Send a start signal;
  2. Send an address to write(slave address + R/W(0) = 0x64) and check responses;
  3. Send a read command (0x52) and check the responses;
  4. Send a stop signal;
  5. Send a start signal;
  6. Send an address to read (slave address + R/W(1) = 0x65) and check responses;
  7. Read 7 bytes from the module and send responses;
  8. Send a stop signal.
*/


uint16_t readMTP40F(int address)
{
  Wire.beginTransmission(address);
  Wire.write(0x03);
  if (Wire.endTransmission() != 0) return 0;

  if (Wire.requestFrom(address, 3) == 3)
  {
    uint16_t ppm = Wire.read() * 256;
    ppm += Wire.read();
    uint8_t status = Wire.read();
    if (status == 0xFF) Serial.print(" - error - ");
    return ppm;
  }
  return 0;
}


//  -- END OF FILE --
