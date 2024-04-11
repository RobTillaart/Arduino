//
//    FILE: Cozir_stream_CO2.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo of Cozir lib - stand alone stream parsing.
//     URL: https://github.com/RobTillaart/Cozir
//
//    NOTE: this sketch needs a MEGA or a Teensy that supports a second
//          Serial port named Serial1
//
//          to be used with the Serial Plotter.


#include "Arduino.h"
#include "cozir.h"

COZIR czr(&Serial1);


uint32_t F_CO2 = 0;       //  CO2  FILTERED
uint32_t R_CO2 = 0;       //  CO2  RAW
uint32_t tmp = 0;         //  temporary buffer

//  0 = none
//  Z = filtered co2
//  z = raw co2
uint8_t field = 0;        //  which field is parsed

uint32_t lastPrint = 0;   //  last time fields are displayed.


void setup()
{
  Serial1.begin(9600);
  czr.init();

  Serial.begin(115200);
  //  Serial.print("COZIR_LIB_VERSION: ");
  //  Serial.println(COZIR_LIB_VERSION);
  //  Serial.println();

  Serial.print("FILTERED\t");
  Serial.println("RAW");
  Serial.println();

  //  set to streaming explicitly.
  czr.setOperatingMode(CZR_STREAMING);
  //  set digi-filter on an average value
  czr.setDigiFilter(16);
  //  select RAW and FILTERED CO2
  czr.setOutputFields(CZR_DEFAULT);
  delay(1000);
}


void loop()
{
  if (Serial1.available())
  {
    char c = Serial1.read();
    switch (c)
    {
      case 'Z':   //  FILTERED CO2
        field = 'Z';
        break;
      case 'z':   //  RAW CO2
        field = 'z';
        break;
      case '0' ... '9':
        tmp *= 10;
        tmp += c - '0';
        break;
      case ' ':
      case '\n':
      case '\r':
        if (tmp > 0 && field == 'Z') F_CO2 = tmp;
        if (tmp > 0 && field == 'z') R_CO2 = tmp;
        tmp = 0;
        break;
      default:
        break;
    }
  }

  if (millis() - lastPrint > 500)
  {
    lastPrint += 500;
    Serial.print(F_CO2);
    Serial.print("\t");
    Serial.print(R_CO2);
    Serial.println();
  }
}


//  -- END OF FILE --
