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
  Serial.println(__FILE__);
  Serial.print("DS2438_LIB_VERSION: ");
  Serial.println(DS2438_LIB_VERSION);
  Serial.println();


  bm.begin();
  Serial.println(bm.isConnected());


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
  delay(30);
  bm.readCurrent();
  Serial.println(bm.getCurrent());


  Serial.println("\nTime");
  Serial.println(bm.readElapsedTimeMeter());
  Serial.println(bm.readDisconnectTime());
  Serial.println(bm.readEndOfChargeTime());


  Serial.println("\nThresshold");
  Serial.println(bm.readThreshold());


  Serial.println("\nCCA/DCA");
  Serial.println(bm.readCCA());
  Serial.println(bm.readDCA());


  Serial.println("\nEEPROM");
  for (int addr = 0; addr < 40; addr++)
  {
    bm.writeEEPROM(addr, 100 + addr);
  }
  for (int addr = 0; addr < 40; addr++)
  {
    if (addr % 8 == 0) Serial.println();
    Serial.print(bm.readEEPROM(addr));
  }
  Serial.println();


  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --
