//
//    FILE: Cozir_MEGA_3_channel_CO2.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo of Cozir lib
//     URL: https://github.com/RobTillaart/Cozir
//
//    NOTE: this sketch needs a MEGA or another board that supports three 
//          hardware serial ports named Serial1, Serial2, Serial3.


#include "Arduino.h"
#include "cozir.h"

COZIR czr[3] = { COZIR(&Serial1), COZIR(&Serial2), COZIR(&Serial3)};
uint16_t lastCO2[3] = {0, 0, 0};

uint32_t lastRead = 0;


void setup()
{
  Serial.begin(115200);
  Serial.print("COZIR_LIB_VERSION: ");
  Serial.println(COZIR_LIB_VERSION);
  Serial.println();
  
  Serial.println("...initializing serial ports...");
  Serial1.begin(9600);
  Serial2.begin(9600);
  Serial3.begin(9600);

  Serial.print("...initializing COZIR objects...");
  for (int i = 0; i < 3; i++)
  { 
    Serial.print(i);
    czr[i].init();
  }
  Serial.println();
  
  //  set to polling explicitly.
  Serial.print("...set POLLING mode...");
  for (int i = 0; i < 3; i++)
  {
    Serial.print(i);
    czr[i].setOperatingMode(CZR_POLLING);
  }
  Serial.println();

}


void loop()
{
  if (millis() - lastRead >= 1000)
  {
    for (int i = 0; i < 3; i++)
    {
      lastCO2[i] = czr[i].CO2();  //  add  * czr.getPPMFactor();  most of time PPM = one.
      Serial.print(lastCO2[i]);
      Serial.print("\t");
    }
    Serial.println();
  }

  //  insert other code here
}


//  -- END OF FILE --
