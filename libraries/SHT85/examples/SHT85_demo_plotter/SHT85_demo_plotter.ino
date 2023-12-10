//
//    FILE: SHT85_demo_plotter.ino
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

#define SHT85_ADDRESS       0x44

uint32_t start;
uint32_t stop;

uint16_t count = 0;
uint32_t last = 0;

//  SHT85 sht(SHT85_ADDRESS, &Wire1);
SHT85 sht(SHT85_ADDRESS);


void setup()
{
  Serial.begin(115200);
  //  Serial.println(__FILE__);
  //  Serial.print("SHT_LIB_VERSION: \t");
  //  Serial.println(SHT_LIB_VERSION);

  Wire.begin();
  Wire.setClock(100000);
  sht.begin();

  //  uint16_t stat = sht.readStatus();
  //  Serial.print(stat, HEX);
  //  Serial.println();
  Serial.println("count\t time\t temp\t hum");
}


void loop()
{
  start = micros();
  sht.read();         //  default = true/fast       slow = false
  stop = micros();

  Serial.print("\t");
  Serial.print(count++);
  Serial.print("\t");
  Serial.print((stop - start) * 0.001, 3);
  Serial.print("\t");
  Serial.print(sht.getTemperature(), 2);
  Serial.print("\t");
  Serial.println(sht.getHumidity(), 2);
  if (millis() - last >= 1000)
  {
    last = millis();
    count = 0;
  }
}


//  -- END OF FILE --
