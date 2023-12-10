//
//    FILE: SHT85_demo_async.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo async interface
//     URL: https://github.com/RobTillaart/SHT85
//
// TOPVIEW SHT85  (check datasheet)
//            +-------+
// +-----\    | SDA 4 -----
// | +-+  ----+ GND 3 -----
// | +-+  ----+ +5V 2 -----
// +-----/    | SCL 1 -----
//            +-------+


//  TODO verify with HW


#include "SHT85.h"

#define SHT85_ADDRESS         0x44

SHT85 sht(SHT85_ADDRESS);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("SHT_LIB_VERSION: \t");
  Serial.println(SHT_LIB_VERSION);

  Wire.begin();
  Wire.setClock(100000);
  sht.begin();

  uint16_t stat = sht.readStatus();
  Serial.print(stat, HEX);
  Serial.println();

  sht.requestData();
}


void loop()
{
  if (sht.dataReady())
  {
    sht.readData();
    Serial.print("\t");
    Serial.print(micros());
    Serial.print("\t");
    Serial.print(sht.lastRequest());
    Serial.print("\t");
    Serial.print(sht.getTemperature(), 1);
    Serial.print("\t");
    Serial.println(sht.getHumidity(), 1);
    sht.requestData();
  }
  delay(10000);  //  do not call sensor too often (see datasheet)
}


//  -- END OF FILE --

