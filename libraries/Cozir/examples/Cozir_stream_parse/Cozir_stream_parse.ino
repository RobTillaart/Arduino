//
//    FILE: Cozir_stream_parse.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo of Cozir lib
//     URL: https://github.com/RobTillaart/Cozir
//
//    NOTE: this sketch needs a MEGA or a Teensy that supports a second
//          Serial port named Serial1
//
//          to be used with the Serial Plotter.


#include "Arduino.h"
#include "cozir.h"


COZIR czr(&Serial1);
C0ZIRParser czrp;


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
  czrp.init();

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
  //  czr.setOutputFields(CZR_HUMIDITY | CZR_RAWTEMP | CZR_RAWCO2);
  delay(1000);
}


void loop()
{
  //  inject commands to check robustness
  if (Serial.available())
  {
    Serial1.write(Serial.read());
  }
  if (Serial1.available())
  {
    char c = Serial1.read();
    //  Serial.print(c);
    field = czrp.nextChar(c);
    if (field != 0)
    {
      //  shows all values
      //  Serial.print(czrp.celsius());
      //  Serial.print("\t");
      //  Serial.print(czrp.humidity());
      //  Serial.print("\t");
      Serial.print(czrp.CO2());
      Serial.print("\t");
      Serial.print(czrp.CO2Raw());
      Serial.println();
    }
  }
}


//  -- END OF FILE --
