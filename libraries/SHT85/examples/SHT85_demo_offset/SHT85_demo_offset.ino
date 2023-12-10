//
//    FILE: SHT85_demo_offset.ino
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

  //  uint16_t stat = sht.readStatus();
  //  Serial.print(stat, HEX);
  //  Serial.println();
  Serial.println("OffT\t OffH\t temp\t hum");

  sht.setTemperatureOffset((random(100) - 50) * 0.01);
  sht.setHumidityOffset((random(100) - 50) * 0.01);
}


void loop()
{
  if (millis() - last >= 1000)
  {
    last = millis();
    sht.read();

    Serial.print(sht.getTemperatureOffset(), 2);
    Serial.print("\t");
    Serial.print(sht.getHumidityOffset(), 2);
    Serial.print("\t");
    Serial.print(sht.getTemperature(), 2);
    Serial.print("\t");
    Serial.println(sht.getHumidity(), 2);
  }
}


void loop2()
{
  if (millis() - last >= 1000)
  {
    last = millis();
    sht.read();

    //  just add awfull noisy offset +-0.5 degrees C
    sht.setTemperatureOffset((random(100) - 50) * 0.01);
    sht.setHumidityOffset((random(100) - 50) * 0.01);

    Serial.print(sht.getTemperatureOffset(), 2);
    Serial.print("\t");
    Serial.print(sht.getHumidityOffset(), 2);
    Serial.print("\t");
    Serial.print(sht.getTemperature(), 2);
    Serial.print("\t");
    Serial.println(sht.getHumidity(), 2);
  }
}


//  -- END OF FILE --
