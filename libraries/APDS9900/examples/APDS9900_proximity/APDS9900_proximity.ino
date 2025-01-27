//
//    FILE: APDS9900_proximity.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour
//     URL: https://github.com/RobTillaart/APDS9900
//
//  DATASHEET: page 10 + 11

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
  Serial.println();

  Wire.begin();
  apds.begin();

  //  startup parameters
  Serial.print("Prox  time:\t");
  Serial.println(apds.getProximityTime());
  Serial.print("Prox  pcnt:\t");
  Serial.println(apds.getProximityPulseCount());
  Serial.print("Prox diode:\t");
  Serial.println(apds.getProximityDiodeSelect());
  Serial.print("Prox  gain:\t");
  Serial.println(apds.getProximityGain());

  delay(1000);

  //  set parameters.
  apds.setProximityTime(3);          //  page 19  3 milliseconds = preferred
  apds.setProximityPulseCount(1);    //  page 21
  apds.setProximityDiodeSelect(2);   //  page 22 control register must be 2
  apds.setProximityGain(0);          //  page 22 control register must be 0

}


void loop()
{
  delay(200);
  Serial.print(apds.getPROX_DATA());
  Serial.println();
}


//  -- END OF FILE --
