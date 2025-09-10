//
//    FILE: CHT832X_crc8_check.ino
//  AUTHOR: rob tillaart
// PURPOSE: Check CRC CHT832X with known values
//     URL: https://github.com/RobTillaart/CHT832X


//  Code from CHT832X.cpp + datasheet

uint8_t _crc8(uint16_t data)
{
  uint8_t _crc = 0xFF;
  uint8_t value = (data >> 8);  //  MSB first
  uint8_t n = 2;
  while (n--)
  {
    _crc ^= value;
    for (uint8_t i = 8; i; i--)
    {
      if (_crc & (1 << 7))
      {
        _crc <<= 1;
        _crc ^= 0x31;
      }
      else
      {
        _crc <<= 1;
      }
    }
    value = (data & 0xFF);  //  LSB
  }
  return _crc;
}


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.println();

  Serial.println("Expected output: 6F 53 06 00 96\n");

  //  CRC specs  Page 20
  Serial.println(_crc8(0xABCD), HEX);  //  0x6F
  //  MANUFACTURER Page 18
  Serial.println(_crc8(0x5959), HEX);  //  0x53
  //  HEATER Page 17
  Serial.println(_crc8(0x3FFF), HEX);  //  0x06
  Serial.println(_crc8(0x03FF), HEX);  //  0x00
  Serial.println(_crc8(0x009F), HEX);  //  0x96

  Serial.println("\ndone...");
}

void loop()
{
}


//  -- END OF FILE --
