//
//    FILE: APDS9900_minimal.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour
//     URL: https://github.com/RobTillaart/APDS9900


#include "APDS9900.h"
#include "Wire.h"

APDS9900 apds;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("APDS9900_LIB_VERSION: ");
  Serial.println(APDS9900_LIB_VERSION);

  Wire.begin();
  apds.begin();

  Serial.println("LUX \tALSC \tIR \t PROX\t ");
}


void loop()
{

  Serial.print("\t");
  Serial.print(apds.getLux());
  Serial.print("\t");
  Serial.print(apds.getALS_CDATA());
  Serial.print("\t");
  Serial.print(apds.getALS_IRDATA());
  Serial.print("\t");
  Serial.print(apds.getPROX_DATA());
  Serial.println();

  delay(2000);
}


//  -- END OF FILE --
