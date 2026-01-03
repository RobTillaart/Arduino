//    FILE: RS485_sniffer.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: simple sniffer prints data as hex dump
//     URL: https://github.com/RobTillaart/RS485

//  use a 2nd Serial port.
//  or only connect the RX of the MAX485.
//
//  Note this sniffer if not 100% fool proof, known issues are
//  - no detection of buffer overrun etc
//  - ASCII output is only printed after 16 bytes are decoded.
//  - still might be useful for debugging.


#include "Arduino.h"
#include "RS485.h"


const uint8_t sendPin  = 4;    //  not used, listening only.
const uint8_t deviceID = 250;  //  not used, maybe in future.


//  use a 2nd Serial port.
//  or only connect the RX of the MAX485.
RS485 rs485(&Serial, sendPin, deviceID);


const uint8_t LED = 13;
uint8_t status = LOW;

uint32_t count = 0;

char buffer[17];


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("RS485_LIB_VERSION: ");
  Serial.println(RS485_LIB_VERSION);
  Serial.println();

  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
}


void loop()
{
  if (rs485.available() > 0)
  {
    //  toggle on receive
    digitalWrite(LED, !digitalRead(LED));

    if (count % 4 == 0)
    {
      Serial.print(' ');
    }
    if (count % 16 == 0)
    {
      Serial.print("   ");
      Serial.println(buffer);
      if (count % 160 == 0)
      {
        Serial.println();
      }
      Serial.print(count, HEX);
      Serial.print('\t');
    }


    int x = rs485.read();

    //  HEX DUMP PART
    if (x < 0x10) Serial.print('0');
    Serial.print(x, HEX);
    Serial.print(" ");

    //  fill ASCII buffer
    buffer[count % 16] = isprint(x) ? x : '.';
    buffer[count % 16 + 1] = 0;

    count++;
  }
}


//  -- END OF FILE --
