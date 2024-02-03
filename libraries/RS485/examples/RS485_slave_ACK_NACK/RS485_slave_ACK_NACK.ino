//    FILE: RS485_slave_controller.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/RS485

//  This is the code for a master (to be used with slave example)
//  Best is it to use on a MEGA or another board with multiple hardware Serials.
//  The master should be connected with one slave e.g. an UNO
//
//  The application is (too) simple,
//     if the slave receives a printable char it returns an ACK
//     else an NACK


#include "Arduino.h"
#include "RS485.h"

const uint8_t sendPin  = 4;
const uint8_t deviceID = 0;

//  use a 2nd Serial port.
//  RS485 rs485(&Serial2, sendPin, deviceID);
RS485 rs485(&Serial, sendPin, deviceID);


void setup()
{
  Serial.begin(38400);
  while (!Serial);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("RS485_LIB_VERSION: ");
  Serial.println(RS485_LIB_VERSION);

}


void loop()
{
  if (rs485.available())
  {
    char c = rs485.read();

    if (isPrintable(c))
    {
      rs485.write(ASCII_ACK);
    }
    else
    {
      rs485.write(ASCII_NAK);
    }

  }
}


//  -- END OF FILE --
