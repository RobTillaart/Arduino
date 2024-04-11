//
//    FILE: Cozir_SWSerial_CO2_only.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo of Cozir lib (>= 0.1.06)
//     URL: https://github.com/RobTillaart/Cozir
//
//    NOTE: software serial is less reliable than hardware serial


#include "Arduino.h"
#include "cozir.h"
#include "SoftwareSerial.h"

SoftwareSerial sws(3, 2);  //  RX, TX, optional inverse logic

COZIR czr(&sws);


void setup()
{
  sws.begin(9600);
  czr.init();

  Serial.begin(115200);
  Serial.print("COZIR_LIB_VERSION: ");
  Serial.println(COZIR_LIB_VERSION);
  Serial.println();

  // set to polling explicitly.
  czr.setOperatingMode(CZR_POLLING);
  delay(1000);
}


void loop()
{
  uint32_t c = czr.CO2();
  Serial.print("CO2 =\t");
  Serial.println(c);
  delay(1000);
}


//  -- END OF FILE --
