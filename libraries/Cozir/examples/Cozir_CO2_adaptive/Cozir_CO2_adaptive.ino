//
//    FILE: Cozir_CO2_adaptive.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo of Cozir lib
//     URL: https://github.com/RobTillaart/Cozir
//
//    NOTE: this sketch needs a MEGA or a Teensy that supports a second
//          Serial port named Serial1
//  The sketch updates the polling interval depending on the level of CO2
//  when higher the interval wil be shorter.


#include "cozir.h"


COZIR czr(&Serial1);


uint32_t lastPrint = 0;
uint32_t interval  = 1000;  //  milliseconds


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
  uint32_t now = millis();
  if (now - lastPrint > interval)
  {
    lastPrint = now;
    uint32_t co2 = czr.CO2();
    co2 *= czr.getPPMFactor();  //  most of time PPM = one.
    Serial.print(interval);
    Serial.print("\t");
    Serial.print("CO2 = ");
    Serial.println(co2);
    updateInterval(co2);
  }
  delay(1000);
}


void updateInterval(uint16_t co2)
{
  if      (co2 <  100) interval =  1000;  //  catch zero readings.
  else if (co2 <  600) interval = 10000;
  else if (co2 <  700) interval =  9000;
  else if (co2 <  800) interval =  8000;
  else if (co2 <  900) interval =  7000;
  else if (co2 < 1000) interval =  6000;
  else if (co2 < 1100) interval =  5000;
  else if (co2 < 1200) interval =  4000;
  else if (co2 < 1300) interval =  3000;
  else if (co2 < 1400) interval =  2000;
  else interval = 1000;
}


//  -- END OF FILE --
