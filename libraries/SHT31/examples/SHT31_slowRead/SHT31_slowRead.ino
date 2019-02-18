//
//    FILE: SHT31_slowRead.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.0.1
// PURPOSE: demo
//
// HISTORY:

#include "Wire.h"
#include "SHT31.h"

uint32_t start;
uint32_t stop;

SHT31 sht;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("SHT31_LIB_VERSION: \t");
  Serial.println(SHT31_LIB_VERSION);

  Wire.begin();
  sht.begin(0x44);
  Wire.setClock(100000);
  uint16_t stat = sht.readStatus();
  Serial.print(stat, HEX);
}

void loop()
{
  start = micros();
  sht.read(false);         // default = true/fast       slow = false
  stop = micros();
  Serial.print("\t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(sht.temperature, 1);
  Serial.print("\t");
  Serial.println(sht.humidity, 1);
  delay(100);
}