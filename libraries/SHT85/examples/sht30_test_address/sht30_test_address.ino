//    FILE: sht30_test_address.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: Check both addresses
//     URL: https://github.com/RobTillaart/SHT85


#include "SHT85.h"

uint32_t start;
uint32_t stop;

SHT30 sht1(0x44);
SHT30 sht2(0x45);


void setup()
{
  //  while(!Serial);  //  uncomment if needed
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("SHT_LIB_VERSION: \t");
  Serial.println(SHT_LIB_VERSION);
  Serial.println();

  Wire.begin();
  Wire.setClock(100000);
  sht1.begin();
  sht2.begin();

  Serial.println("\nCONNECT");
  Serial.println(sht1.isConnected());
  Serial.println(sht2.isConnected());

  Serial.println("\nSTATUS");
  uint16_t stat = sht1.readStatus();
  Serial.print(stat, HEX);
  Serial.println();
  stat = sht2.readStatus();
  Serial.print(stat, HEX);
  Serial.println();

  delay(1000);
}


void loop()
{
  start = micros();
  sht1.read();         //  default = true/fast       slow = false
  stop = micros();
  Serial.print("SHT1:\t");
  Serial.print((stop - start) * 0.001);
  Serial.print("\t");
  Serial.print(sht1.getTemperature(), 1);
  Serial.print("\t");
  Serial.println(sht1.getHumidity(), 1);
  delay(100);

  start = micros();
  sht2.read();         //  default = true/fast       slow = false
  stop = micros();
  Serial.print("SHT2:\t");
  Serial.print((stop - start) * 0.001);
  Serial.print("\t");
  Serial.print(sht2.getTemperature(), 1);
  Serial.print("\t");
  Serial.println(sht2.getHumidity(), 1);
  delay(100);
}


//  -- END OF FILE --