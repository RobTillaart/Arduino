//
//    FILE: SHT85_I2C_speed.ino
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
  for (uint32_t clk = 50000; clk < 550000; clk += 50000)
  {
    Wire.setClock(clk);
    start = micros();
    sht.read();         //  default = true/fast       slow = false
    stop = micros();
    Serial.print(clk);
    Serial.print("\t");
    Serial.println((stop - start) * 0.001);
    delay(100);
  }
  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --
