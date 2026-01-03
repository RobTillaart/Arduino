//    FILE: RS485_master_controller.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/RS485

//  This is the code for a master (to be used with slave example)
//  Best is it to use on a MEGA or another board with multiple hardware Serials.
//  The master should be connected with one slave e.g. an UNO


#include "Arduino.h"
#include "RS485.h"

const uint8_t sendPin  = 4;
const uint8_t deviceID = 0;

//  use a 2nd Serial port.
//  RS485 rs485(&Serial2, sendPin, deviceID);
RS485 rs485(&Serial, sendPin, deviceID);


//  for receiving (must be global)
uint8_t ID;
uint8_t arr[32];
uint8_t len;


void setup()
{
  Serial.begin(38400);
  while (!Serial);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("RS485_LIB_VERSION: ");
  Serial.println(RS485_LIB_VERSION);
  Serial.println();
}


void loop()
{
  if (Serial.available())
  {
    char c = Serial.read();
    switch(c)
    {
      //  digital read
      case '2':
        rs485.send(1, "DR2", 3);
        break;
      case '3':
        rs485.send(1, "DR3", 3);
        break;
      case '4':
        rs485.send(1, "DR4", 3);
        break;

      //  digital write
      case 'H':
        rs485.send(1, "DW7H", 4);
        break;
      case 'L':
        rs485.send(1, "DW7L", 4);
        break;

      //  analog read
      case 'A':
        rs485.send(1, "AR0", 3);
        break;
      case 'B':
        rs485.send(1, "AR1", 3);
        break;
    }
  }

//  if (rs485.receive(ID, arr, len))
//  {
//    arr[len] = 0;
//    Serial.print("RECV:\t");
//    Serial.print(ID);
//    Serial.print("\t");
//    Serial.println((char*) arr);
//  }
}


//  -- END OF FILE --
