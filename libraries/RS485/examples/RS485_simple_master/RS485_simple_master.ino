//    FILE: RS485_simple_master.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: simple master
//     URL: https://github.com/RobTillaart/RS485

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
    char cmd = random(3);     //  0,1,2
    rs485.print(cmd);
  }
  if (rs485.available() > 0)
  {
    int status = rs485.read();
    Serial.println(status);
  }
}


// -- END OF FILE --
