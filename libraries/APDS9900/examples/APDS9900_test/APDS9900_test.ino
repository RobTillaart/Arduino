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
  Serial.println();

  Wire.begin();
  apds.begin();

  delay(12);  //  page 14 

  //  dump default settings
  Serial.print("Address:\t");
  Serial.println(apds.getAddress(), HEX);   //  0x39 (57)
  Serial.print("Connected:\t");
  Serial.println(apds.isConnected(), HEX);  //  0x01
  Serial.print("Revision:\t");
  Serial.println(apds.getRevision(), HEX);  //  0x01
  Serial.print("DeviceID:\t");
  Serial.println(apds.getDeviceID(), HEX);  //  0x29 for APDS9900, 0x20 for APDS9901
  Serial.print("  Status:\t");
  Serial.println(apds.getStatus(), HEX);    //  ??
  Serial.println();

  Serial.print("Time in ms\n");
  Serial.print("Integration time:\t");
  Serial.println(apds.getIntegrationTime());
  apds.setIntegrationTime(21);
  Serial.print("Integration time:\t");
  Serial.println(apds.getIntegrationTime());

  Serial.print("  Proximity time:\t");
  Serial.println(apds.getProximityTime());
  apds.setProximityTime(3);
  Serial.print("  Proximity time:\t");
  Serial.println(apds.getProximityTime());

  Serial.print("       Wait time:\t");
  Serial.println(apds.getWaitTime());
  apds.setWaitTime(84);
  Serial.print("       Wait time:\t");
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
}


void loop()
{
  delay(2000);

  Serial.println("\tLUX \tALSC \tIR \t PROX");
  Serial.print("\t");
  Serial.print(apds.getLux());
  Serial.print("\t");
  Serial.print(apds.getALS_CDATA());
  Serial.print("\t");
  Serial.print(apds.getALS_IRDATA());
  Serial.print("\t");
  Serial.print(apds.getPROX_DATA());
  Serial.println();
}


//  -- END OF FILE --
