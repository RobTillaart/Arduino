//    FILE: RS485_simple_slave.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: simple listening slave
//     URL: https://github.com/RobTillaart/RS485

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
    if (c == '0') status = LOW;
    if (c == '1') status = HIGH;
    if (c == '2') rs485.print(status);
    digitalWrite(LED, status);
  }
}


// -- END OF FILE --
