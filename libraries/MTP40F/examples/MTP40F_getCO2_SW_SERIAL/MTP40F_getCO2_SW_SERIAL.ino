//
//    FILE: MTP40F_getCO2_SW_SERIAL.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo of MTP40F library
//     URL: https://github.com/RobTillaart/MTP40F
//


#include "MTP40F.h"
#include "SoftwareSerial.h"

SoftwareSerial sws(7, 6);
MTP40F mtp(&sws);

int lines = 10;


void setup()
{
  // DEBUG SERIAL
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MTP40F_LIB_VERSION:\t");
  Serial.println(MTP40F_LIB_VERSION);

  // SERIAL OF MTP40F SENSOR
  sws.begin(9600);
  if ( mtp.begin() == false)
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


//  -- END OF FILE --
