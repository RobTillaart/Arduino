//
//    FILE: SHT85_duo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/SHT85
//
// TOPVIEW SHT85  (check datasheet)
//            +-------+
// +-----\    | SDA 4 -----
// | +-+  ----+ GND 3 -----
// | +-+  ----+ +5V 2 -----
// +-----/    | SCL 1 -----
//            +-------+


#include "SHT85.h"

#define SHT85_ADDRESS   0x44

uint32_t start;
uint32_t stop;

SHT85 sht1;
SHT85 sht2;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("SHT_LIB_VERSION: \t");
  Serial.println(SHT_LIB_VERSION);

  Wire.begin();
  sht1.begin(0x44);
  sht2.begin(0x45);
  Wire.setClock(100000);

  uint16_t stat = sht1.readStatus();
  Serial.print(stat, HEX);
  Serial.println();
  stat = sht2.readStatus();
  Serial.print(stat, HEX);
  Serial.println();
  Serial.println();
}


void loop()
{
  Serial.print(millis());
  sht1.read();         // default = true/fast       slow = false
  Serial.print("\t0x44\t");
  Serial.print(sht1.getTemperature(), 1);
  Serial.print("\t");
  Serial.print(sht1.getHumidity(), 1);

  sht2.read();
  Serial.print("\t0x45\t");
  Serial.print(sht2.getTemperature(), 1);
  Serial.print("\t");
  Serial.println(sht2.getHumidity(), 1);
  delay(100);
}


// -- END OF FILE --

