//
//    FILE: Cozir_CO2_only.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo of Cozir lib
//     URL: https://github.com/RobTillaart/Cozir
//
//    NOTE: this sketch needs a MEGA or a Teensy that supports a second
//          Serial port named Serial1


#include "Arduino.h"
#include "cozir.h"


COZIR czr(&Serial1);


void setup()
{
  Serial1.begin(9600);
  czr.init();

  Serial.begin(115200);
  Serial.print("COZIR_LIB_VERSION: ");
  Serial.println(COZIR_LIB_VERSION);
  Serial.println();

  //  set to polling explicitly.
  czr.setOperatingMode(CZR_POLLING);
  delay(1000);
}


void loop()
{
  uint32_t c = czr.CO2();
  c *= czr.getPPMFactor();  //  most of time PPM = one.
  Serial.print("CO2 =\t");
  Serial.println(c);
  delay(1000);
}


//  -- END OF FILE --
