//
//    FILE: DS2438_resetAccumulators.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/DS2438


#include "DS2438.h"


#define ONE_WIRE_BUS          2

OneWire   oneWire(ONE_WIRE_BUS);
DS2438    bm(&oneWire);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("DS2438_LIB_VERSION: ");
  Serial.println(DS2438_LIB_VERSION);
  Serial.println();

  bm.begin();
  Serial.println(bm.isConnected());


  Serial.println("\nBefore resetAccumulators");
  Serial.println("\nCCA/DCA");
  Serial.println("  Charge: ");
  Serial.println(bm.readCCA());
  Serial.println("Discharge: ");
  Serial.println(bm.readDCA());
  Serial.println("    Delta: ");
  Serial.println(bm.readCCA() - bm.readDCA());

  Serial.println(bm.readEEPROM(36));
  Serial.println(bm.readEEPROM(37));
  Serial.println(bm.readEEPROM(38));
  Serial.println(bm.readEEPROM(39));

  bm.resetAccumulators();

  Serial.println("\nAfter resetAccumulators");
  Serial.println("\nCCA/DCA");
  Serial.println("  Charge: ");
  Serial.println(bm.readCCA());
  Serial.println("Discharge: ");
  Serial.println(bm.readDCA());
  Serial.println("    Delta: ");
  Serial.println(bm.readCCA() - bm.readDCA());

  Serial.println(bm.readEEPROM(36));
  Serial.println(bm.readEEPROM(37));
  Serial.println(bm.readEEPROM(38));
  Serial.println(bm.readEEPROM(39));


  bm.setCCA(15625);
  bm.setDCA(31250);

  Serial.println("\nAfter setCCA/DCA");
  Serial.println("\nCCA/DCA");
  Serial.println("  Charge: ");
  Serial.println(bm.readCCA());
  Serial.println("Discharge: ");
  Serial.println(bm.readDCA());
  Serial.println("    Delta: ");
  Serial.println(bm.readCCA() - bm.readDCA());

  Serial.println(bm.readEEPROM(36));
  Serial.println(bm.readEEPROM(37));
  Serial.println(bm.readEEPROM(38));
  Serial.println(bm.readEEPROM(39));

  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --
