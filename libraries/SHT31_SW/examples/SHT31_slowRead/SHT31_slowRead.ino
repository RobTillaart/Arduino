//
//    FILE: SHT31_slowRead.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/SHT31_SW


#include "SoftWire.h"
#include "SHT31_SW.h"

#define SHT31_ADDRESS   0x44


SoftWire sw(6, 7);

uint32_t start;
uint32_t stop;

SHT31_SW sht;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("SHT31_SW_LIB_VERSION: \t");
  Serial.println(SHT31_SW_LIB_VERSION);

  sw.begin();
  sht.begin(SHT31_ADDRESS, &sw);
  sw.setClock(100000);

  uint16_t stat = sht.readStatus();
  Serial.print(stat, HEX);
  Serial.println();
}


void loop()
{
  start = micros();
  sht.read(false);         //  default = true/fast       slow = false
  stop = micros();
  Serial.print("\t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(sht.getTemperature(), 1);
  Serial.print("\t");
  Serial.println(sht.getHumidity(), 1);
  delay(100);
}


//  -- END OF FILE --

