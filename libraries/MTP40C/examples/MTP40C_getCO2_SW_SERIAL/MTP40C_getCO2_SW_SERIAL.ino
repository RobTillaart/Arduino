//
//    FILE: MTP40C_getCO2_SW_SERIAL.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo of MTP40C library
//    DATE: 2021-08-21
//     URL: https://github.com/RobTillaart/MTP40C
//


#include "MTP40C.h"
#include "SoftwareSerial.h"

SoftwareSerial sws(3, 2);
MTP40C mtp(&sws);

int lines = 10;


void setup()
{
  // DEBUG SERIAL
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MTP40_LIB_VERSION:\t");
  Serial.println(MTP40_LIB_VERSION);

  // SERIAL OF MTP40C SENSOR
  sws.begin(19200);
  if ( mtp.begin() == false)           // default address 0x64
  {
    Serial.println("could not connect!");
    while (1);
  }

}


void loop()
{
  if (lines == 10)
  {
    lines = 0;
    Serial.println("\nTIME\tCO2 LEVEL");
  }

  if (millis() - mtp.lastRead() >= 5000)
  {
    Serial.print(millis());
    Serial.print("\t");
    Serial.print(mtp.getGasConcentration());
    Serial.println();
    lines++;
  }
}


// -- END OF FILE --

