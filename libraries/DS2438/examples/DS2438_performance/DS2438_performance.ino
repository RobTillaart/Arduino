//
//    FILE: DS2438_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: minimal test DS2438 library battery monitor
//     URL: https://github.com/RobTillaart/DS2438


#include "DS2438.h"


#define ONE_WIRE_BUS          2

OneWire   oneWire(ONE_WIRE_BUS);
DS2438    bm(&oneWire);

uint32_t start, stop;


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
    Serial.println();
  }

  delay(100);
  start = micros();
  bm.readTemperature();
  stop = micros();
  Serial.print("readTemperature: \t");
  Serial.println(stop - start);

  delay(100);
  start = micros();
  bm.readVDD();
  stop = micros();
  Serial.print("readVDD: \t");
  Serial.println(stop - start);

  delay(100);
  start = micros();
  bm.readVAD();
  stop = micros();
  Serial.print("readVAD: \t");
  Serial.println(stop - start);

  delay(100);
  bm.setResistor(0.01);
  bm.enableCurrentMeasurement();
  start = micros();
  bm.getConfigRegister();
  stop = micros();
  Serial.print("getConfigRegister: \t");
  Serial.println(stop - start);
  delay(30);

  delay(100);
  start = micros();
  bm.readCurrent();
  stop = micros();
  Serial.print("readCurrent: \t");
  Serial.println(stop - start);

  delay(100);
  start = micros();
  bm.readCurrentOffset();
  stop = micros();
  Serial.print("readCurrentOffset: \t");
  Serial.println(stop - start);

  delay(100);
  start = micros();
  bm.readElapsedTimeMeter();
  stop = micros();
  Serial.print("readElapsedTimeMeter: \t");
  Serial.println(stop - start);

  delay(100);
  start = micros();
  bm.readDisconnectTime();
  stop = micros();
  Serial.print("readDisconnectTime: \t");
  Serial.println(stop - start);

  delay(100);
  start = micros();
  bm.readEndOfChargeTime();
  stop = micros();
  Serial.print("readEndOfChargeTime: \t");
  Serial.println(stop - start);

  delay(100);
  start = micros();
  bm.readThreshold();
  stop = micros();
  Serial.print("readThreshold: \t");
  Serial.println(stop - start);

  delay(100);
  start = micros();
  bm.readRemaining();
  stop = micros();
  Serial.print("readRemaining: \t");
  Serial.println(stop - start);

  delay(100);
  start = micros();
  bm.readCCA();
  stop = micros();
  Serial.print("readCCA: \t");
  Serial.println(stop - start);

  delay(100);
  start = micros();
  bm.readDCA();
  stop = micros();
  Serial.print("readDCA: \t");
  Serial.println(stop - start);

  delay(100);
  start = micros();
  for (int addr = 0; addr < 10; addr++)
  {
    bm.writeEEPROM(addr, 100 + addr);
  }
  stop = micros();
  Serial.print("writeEEPROM (10x): \t");
  Serial.println(stop - start);

  delay(100);
  start = micros();
  for (int addr = 0; addr < 10; addr++)
  {
    bm.readEEPROM(addr);
  }
  stop = micros();
  Serial.print("readEEPROM (10x): \t");
  Serial.println(stop - start);

  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --
