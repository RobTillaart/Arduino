//
//    FILE: CRC16_test_modbus.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/CRC


#include "CRC16.h"

CRC16 crc(CRC16_MODBUS_POLYNOME,
          CRC16_MODBUS_INITIAL,
          CRC16_MODBUS_XOR_OUT,
          CRC16_MODBUS_REV_IN,
          CRC16_MODBUS_REV_OUT);

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  //  uint8_t arr[12] = { 0xFE, 0x03, 0x14, 0x00, 0x01, 0x00, 0x55, 0xA5 };
  uint8_t arr[12] = { 0xFE, 0x10, 0x04, 0x00, 0x01, 0x00, 0x01, 0x60, 0x00, 0x42, 0x58 };

  for (int i = 0; i < 9; i++)
  {
    crc.add(arr[i]);
  }
  Serial.println(crc.calc(), HEX);

}


void loop()
{
}


//  -- END OF FILE --
