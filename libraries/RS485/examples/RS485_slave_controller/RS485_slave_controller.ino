//    FILE: RS485_slave_controller.ino
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
  Serial.print("RS485_LIB_VERSION: ");
  Serial.println(RS485_LIB_VERSION);
}


void loop()
{
  if (rs485.receive(ID, buffer, len))
  {
    buffer[len] = 0;
    //  DIGITAL READ
    if (strcmp((char*)buffer, "DR2") == 0)
    {
      int value = digitalRead(2);
      sprintf((char*)buffer, "DR2: %d", value);
    }
    else if (strcmp((char*)buffer, "DR3") == 0)
    {
      int value = digitalRead(3);
      sprintf((char*)buffer, "DR3: %d", value);
    }
    else if (strcmp((char*)buffer, "DR4") == 0)
    {
      int value = digitalRead(4);
      sprintf((char*)buffer, "DR4: %d", value);
    }

    //  DIGITAL WRITE
    else if (strcmp((char*)buffer, "DW7H") == 0)
    {
      digitalWrite(7, HIGH);
      sprintf((char*)buffer, "DW7: H");
    }
    else if (strcmp((char*)buffer, "DW7L") == 0)
    {
      digitalWrite(7, LOW);
      sprintf((char*)buffer, "DW7: L");
    }

    //  ANALOG READ
    else if (strcmp((char*)buffer, "AR0") == 0)
    {
      int value = analogRead(A0);
      sprintf((char*)buffer, "AR0: %d", value);
    }
    else if (strcmp((char*)buffer, "AR1") == 0)
    {
      int value = analogRead(A1);
      sprintf((char*)buffer, "AR1: %d", value);
    }
    else
    {
      sprintf((char*)buffer, "INVALID");
    }
    rs485.send(ID, buffer, strlen((char*)buffer));
  }
}


//  -- END OF FILE --
