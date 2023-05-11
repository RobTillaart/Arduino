//    FILE: RS485_simple_slave.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: simple listening slave
//     URL: https://github.com/RobTillaart/RS485

//  this is the code of a simple slave  (needs simple master)
//  it receives one of 3 (single char) commands to the slave
//  '0' == set LED LOW.
//  '1' == set LED HIGH.
//  '2' == return status to master.
//
//  print debug messages SEND and RECV with data.
//  Note that one needs a 2nd Serial port for nice debugging.
//  (or an LCD screen whatever).


#include "Arduino.h"
#include "RS485.h"


const uint8_t sendPin  = 4;
const uint8_t deviceID = 1;


RS485 rs485(&Serial, sendPin, deviceID);


const uint8_t LED = 13;
uint8_t status = LOW;


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);

  rs485.setMicrosPerByte(115200);

  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
}


void loop()
{
  if (rs485.available() > 0)
  {
    int c = rs485.read();
    Serial.print("RECV: ");
    Serial.println(c);

    if (c == '0') status = LOW;
    if (c == '1') status = HIGH;
    if (c == '2')
    {
      Serial.print("SEND: ");
      Serial.println(status);
      rs485.print(status);
    }
    digitalWrite(LED, status);
  }
}


//  -- END OF FILE --

