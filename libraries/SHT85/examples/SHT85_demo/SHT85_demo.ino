//
//    FILE: SHT85_demo.ino
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

#define SHT85_ADDRESS         0x44

uint32_t start;
uint32_t stop;

SHT85 sht(SHT85_ADDRESS);


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
  sht.begin();

  uint16_t stat = sht.readStatus();
  Serial.print(stat, HEX);
  Serial.println();

  uint32_t ser;
  bool b = sht.getSerialNumber(ser, true);
  if (b)
  {
    Serial.print(ser, HEX);
    Serial.println();
  }
  else
  {
    Serial.println("Error: could not get serial number.");
  }
  delay(1000);
}


void loop()
{
  start = micros();
  sht.read();         //  default = true/fast       slow = false
  stop = micros();

  Serial.print("\t");
  Serial.print((stop - start) * 0.001);
  Serial.print("\t");
  Serial.print(sht.getTemperature(), 1);
  Serial.print("\t");
  Serial.println(sht.getHumidity(), 1);
  delay(100);
}


//  -- END OF FILE --

