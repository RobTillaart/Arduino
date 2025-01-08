//
//    FILE: APDS9900_test.ino
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

  //  dump default settings
  Serial.print("Address:\t");
  Serial.println(apds.getAddress());
  Serial.print("Revision:\t");
  Serial.println(apds.getRevision());
  Serial.print("DeviceID:\t");
  Serial.println(apds.getDeviceID());
  Serial.print("  Status:\t");
  Serial.println(apds.getStatus());
  Serial.println();

  Serial.print("Integration time:\t");
  Serial.println(apds.getIntegrationTime());
  Serial.print("  Proximity time:\t");
  Serial.println(apds.getProximityTime());
  Serial.print("      Wait time:\t");
  Serial.println(apds.getWaitTime());
  Serial.println();

  Serial.print("  Led drive:\t");
  Serial.println(apds.getLedDriveStrength());
  Serial.print("Proxy diode:\t");
  Serial.println(apds.getProximityDiodeSelect());
  Serial.print(" Proxy gain:\t");
  Serial.println(apds.getProximityGain());
  Serial.print("   ALS gain:\t");
  Serial.println(apds.getALSGain());
  Serial.println();
  Serial.println();
  delay(2000);

  Serial.println("LUX \tALSC \tIR \t PROX\t ");
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


void loop()
{
}


//  -- END OF FILE --
