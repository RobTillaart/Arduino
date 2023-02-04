//
//    FILE: DMM_ohm_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo DMM
//     URL: https://github.com/RobTillaart/DMM
//
//     SCHEMA
//
//     [GND] ----[ R reference ]----[A0]----[ R unknown ]----[+5V]
//

#include "DMM.h"


DMM dmm;


void setup()
{
  while (!Serial);
  Serial.begin(115200); 
  Serial.println(__FILE__);
  Serial.print("DMM_LIB_VERSION: ");
  Serial.println(DMM_LIB_VERSION);

  dmm.begin(A0, 5.000, 1023);  //  Arduino UNO, adjust if needed
  dmm.setReferenceR(998);      //  R reference, adjust if needed
}


void loop()
{
  float voltage = dmm.readVolts();
  float ohm = dmm.readOhm(3);
  float Kohm = dmm.readKiloOhm(3);
  Serial.print("voltage: ");
  Serial.print(voltage);
  Serial.print("\tohm: ");    //  Ω 
  Serial.print(ohm);
  Serial.print("\tKohm: ");
  Serial.print(Kohm);
  Serial.println();

  delay(1000);
}


//  -- END OF FILE --
