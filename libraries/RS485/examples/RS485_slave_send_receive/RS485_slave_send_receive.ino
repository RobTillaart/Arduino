//    FILE: RS485_slave_send_receive.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo slave of send / receive
//     URL: https://github.com/RobTillaart/RS485

//  This is the code for a slave (to be used with master example)
//  Best is it to use on a MEGA or another board with multiple hardware Serials.
//  The master should be connected with two slaves
//  slave 2 is waiting for temperature requests.
//  slave 1 is waiting for humidity requests.
//
//  Note that Serial is used for debugging messages, so better use
//  a 2nd Serial for the RS485 bus. 
//  otherwise some binary messages will show up in the Serial monitor.


#include "Arduino.h"
#include "RS485.h"


const uint8_t sendPin  = 4;
const uint8_t deviceID = 1;


//  use a 2nd Serial port.
RS485 rs485(&Serial, sendPin, deviceID);


//  for receiving (must be global)
uint8_t ID;
uint8_t buffer[32];
uint8_t len;


void setup()
{
  Serial.begin(38400);
  while (!Serial);
  Serial.println();
  Serial.println(__FILE__);

  rs485.setMicrosPerByte(38400);
}


void loop()
{
  if (rs485.receive(ID, buffer, len))
  {
    buffer[len] = 0;
    //  Serial.print("RECV: ");
    //  Serial.println((char*) buffer);
    if (strcmp((char*)buffer, "Get Humidity") == 0)
    {
      int humidity = 50 + random(10);
      sprintf((char*)buffer, "HUM: %d", humidity);
      rs485.send(ID, buffer, strlen((char*)buffer));
    }
    if (strcmp((char*)buffer, "Get Temperature") == 0)
    {
      int temperature = 15 + random(10);
      sprintf((char*)buffer, "TEM: %d", temperature);
      rs485.send(ID, buffer, strlen((char*)buffer));
    }
  }
}


//  -- END OF FILE --
