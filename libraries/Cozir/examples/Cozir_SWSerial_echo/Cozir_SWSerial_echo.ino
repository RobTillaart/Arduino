//
//    FILE: Cozir_SWSerial_echo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo of Cozir sensor
//     URL: https://github.com/RobTillaart/Cozir
//
//    NOTE: software serial is less reliable than hardware serial
//
//  The purpose of this sketch is to talk lowest level to the COZIR sensor.
//  one can send the low level commands (datasheet) directly to the device.
//  NOTE: this can cause (unwanted) side effects, so use with care.


#include "Arduino.h"
#include "cozir.h"         //  not mandatory
#include "SoftwareSerial.h"

SoftwareSerial sws(3, 2);  //  RX, TX, optional inverse logic


void setup()
{
  sws.begin(9600);

  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println();

}


void loop()
{
  if (Serial.available())
  {
    sws.write(Serial.read());
  }
  if (sws.available())
  {
    Serial.write(sws.read());
  }
}


//  -- END OF FILE --
