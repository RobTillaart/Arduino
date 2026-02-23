//
//    FILE: DS2438_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: minimal test DS2438 library battery monitor
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
  if (!bm.isDS2438())
  {
    Serial.print("Pin ");
    Serial.print(ONE_WIRE_BUS);
    Serial.println(" has no DS2438 attached.");
    Serial.println("Check connections and restart.");
    while(1);
  }

  Serial.println("\nTemperature");
  bm.readTemperature();
  Serial.println(bm.getTemperature());


  Serial.println("\nVoltage");
  bm.readVDD();
  Serial.println(bm.getVDD());
  bm.readVAD();
  Serial.println(bm.getVAD());


  Serial.println("\nCurrent");
  bm.setResistor(0.01);
  bm.enableCurrentMeasurement();
  delay(10);
  Serial.print("STATUS: ");
  Serial.println(bm.getConfigRegister(), HEX);
  delay(30);
  bm.readCurrent();
  Serial.println(bm.getCurrent());
  Serial.println(bm.readCurrentOffset());


  Serial.println("\nTime");
  Serial.println(bm.readElapsedTimeMeter());
  Serial.println(bm.readDisconnectTime());
  Serial.println(bm.readEndOfChargeTime());

  Serial.println("\nThreshold");
  Serial.println(bm.readThreshold());
  Serial.println("Remaining: ");
  Serial.println(bm.readRemaining());

  Serial.println("\nCCA/DCA");
  Serial.println("  Charge: ");
  Serial.println(bm.readCCA());
  Serial.println("Discharge: ");
  Serial.println(bm.readDCA());
  Serial.println("    Delta: ");
  Serial.println(bm.readCCA() - bm.readDCA());
  Serial.println("Remaining: ");
  Serial.println(bm.readRemaining());


  Serial.println("\nEEPROM");
  Serial.println("Do NOT write the last 4 EEPROM bytes == persistent store of CCA and CDA");
  for (int addr = 0; addr < 36; addr++)
  {
    bm.writeEEPROM(addr, 100 + addr);
  }
  for (int addr = 0; addr < 36; addr++)
  {
    if (addr % 8 == 0) Serial.println();
    Serial.print(bm.readEEPROM(addr));
    Serial.print(' ');
  }
  Serial.println();


  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --
