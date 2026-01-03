//    FILE: RS485_SWS_master_send_receive.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo master of send / receive
//     URL: https://github.com/RobTillaart/RS485

//  VERY EXPERIMENTAL

//  This is the code for a master (to be used with slave example)
//  Best is it to use on a MEGA or another board with multiple hardware Serials.
//  The master should be connected with two slaves
//  slave 2 is requested for temperature
//  slave 1 is requested for humidity
//
//  Note that Serial is used for debugging messages, so better use
//  a 2nd Serial for the RS485 bus.
//  otherwise some binary messages will show up in the Serial monitor.


#include "Arduino.h"
#include "RS485.h"
#include "SoftwareSerial.h"

const uint8_t sendPin  = 4;
const uint8_t deviceID = 0;

SoftwareSerial SWS(6, 7);  //  RX, TX


//  use Software Serial
RS485 rs485(&SWS, sendPin, deviceID);


//  times of last requests.
uint32_t lastT = 0;
uint32_t lastH = 2000;


//  for receiving (must be global)
uint8_t ID;
uint8_t buffer[32];
uint8_t len;


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("RS485_LIB_VERSION: ");
  Serial.println(RS485_LIB_VERSION);
  Serial.println();

  SWS.begin(38400);
}


void loop()
{
  if (millis() - lastT >= 5000)
  {
    lastT = millis();
    char msg[] = "Get Temperature";
    rs485.send(2, (uint8_t *)msg, strlen(msg));
    Serial.print("SEND: ");
    Serial.println(msg);
  }

  if (millis() - lastH >= 5000)
  {
    lastH = millis();
    char msg[] = "Get Humidity";
    rs485.send(1, (uint8_t *)msg, strlen(msg));
    Serial.print("SEND: ");
    Serial.println(msg);
  }

  if (rs485.receive(ID, buffer, len))
  {
    buffer[len] = 0;
    Serial.print("RECV: ");
    Serial.println((char*) buffer);
  }
}


//  -- END OF FILE --
