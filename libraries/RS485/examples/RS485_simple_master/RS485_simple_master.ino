//    FILE: RS485_simple_master.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: simple master
//     URL: https://github.com/RobTillaart/RS485

//  this is the code of a simple master  (needs simple slave)
//  it send one of 3 (single char) commands to the slave
//  '0' == set LED LOW
//  '1' == set LED HIGH
//  '2' == request status.
//
//  print debug messages SEND and RECV with data.
//  Note that one needs a 2nd Serial port for nice debugging.
//  (or an LCD screen whatever).


#include "Arduino.h"
#include "RS485.h"


const uint8_t sendPin  = 4;
const uint8_t deviceID = 0;


RS485 rs485(&Serial, sendPin);  //  uses default deviceID


uint32_t lastCommand = 0;


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);

  rs485.setMicrosPerByte(115200);
}


void loop()
{
  if (millis() - lastCommand >= 2000)
  {
    lastCommand = millis();
    char cmd = '0' + random(3);     //  sends 0, 1, 2 as character  (not as value)
    rs485.print(cmd);
    Serial.print("SEND: ");
    Serial.println(cmd);
  }
  if (rs485.available() > 0)
  {
    int status = rs485.read();
    Serial.print("RECV: ");
    Serial.println(status);
  }
}


//  -- END OF FILE --

