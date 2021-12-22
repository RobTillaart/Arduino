//
//    FILE: MTP40D_I2C_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo of MTP40D I2C interface
//    DATE: 2021-08-27
//     URL: https://github.com/RobTillaart/MTP40C
//
//
//  TODO TEST WITH SENSOR
//  do not expect this to work yet


#include "Wire.h"

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
}


void loop()
{
  uint16_t ppm = readMTP40D(0x62);
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
  2. Send an address to write(slave address + R/W=0x62) and check responses;
  3. Send a read command (0x52) and check the responses;
  4. Send a stop signal;
  5. Send a start signal;
  6. Send an address to read (slave address + R/W(1) =0x63) and check responses;
  7. Read 7 bytes from the module and send responses;
  8. Send a stop signal.
*/


uint16_t readMTP40D(uint8_t address)
{
  Wire.beginTransmission(address);
  Wire.write(0x52);
  if (Wire.endTransmission() != 0) return 0;

  if (Wire.requestFrom(address + 1, 7) == 7)
  {
    // read 0x08
    Wire.read();

    uint16_t ppm = Wire.read() * 256;
    ppm += Wire.read();
    // read 4x 0x00
    Wire.read();
    Wire.read();
    Wire.read();
    Wire.read();
    return ppm;
  }
  return 0;
}


// -- END OF FILE --
